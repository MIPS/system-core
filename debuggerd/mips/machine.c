/* system/debuggerd/debuggerd.c
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/exec_elf.h>
#include <sys/stat.h>

#include <cutils/sockets.h>
#include <cutils/properties.h>

#include <linux/input.h>

#include "../utility.h"

#define R(x) ((unsigned int)(x))

static void syminfo(mapinfo *map, unsigned int pc,
		    const char **mapname, const char **symname, unsigned int *symoffset)
{
    const mapinfo *mi;
    unsigned int rel_pc;
    const struct symbol *sym;

    mi = pc_to_mapinfo(map, pc, &rel_pc);

    *mapname = mi ? mi->name : "";

    /* See if we can determine what symbol this stack frame resides in */
    if (mi && mi->symbols != 0)
	sym = symbol_table_lookup(mi->symbols, rel_pc);
    else
	sym = NULL;
    if (sym && sym->name && *sym->name) {
	*symname = sym->name;
	*symoffset = rel_pc - sym->addr;
    }
    else {
	*symname = NULL;
	*symoffset = 0;
    }
}

void dump_stack_and_code(int tfd, int pid, mapinfo *map,
                         int unwind_depth, unsigned int sp_list[],
                         bool at_fault)
{
    unsigned int sp, pc, ra, p, end, data;
    struct pt_regs r;
    int sp_depth;
    bool only_in_tombstone = !at_fault;
    char code_buffer[80];

    if(ptrace(PTRACE_GETREGS, pid, 0, &r)) return;
    sp = R(r.regs[29]);
    pc = R(r.cp0_epc);
    ra = R(r.regs[31]);

    _LOG(tfd, only_in_tombstone, "\ncode around pc:\n");

    p = pc & ~3;
    p -= 32;
    if (p > pc)
        p = 0;
    end = p + 80;
    /* 'end - p' has to be multiples of 16 */
    while (end < p)
        end -= 16;

    /* Dump the code around PC as:
     *  addr       contents
     *  00008d34   fffffcd0 4c0eb530 b0934a0e 1c05447c
     *  00008d44   f7ff18a0 490ced94 68035860 d0012b00
     */
    while (p <  end) {
        int i;

        sprintf(code_buffer, "%08x ", p);
        for (i = 0; i < 4; i++) {
            data = ptrace(PTRACE_PEEKTEXT, pid, (void*)p, NULL);
            sprintf(code_buffer + strlen(code_buffer), "%08x ", data);
            p += 4;
        }
        _LOG(tfd, only_in_tombstone, "%s\n", code_buffer);
    }

    if (ra != pc) {
        _LOG(tfd, only_in_tombstone, "\ncode around ra:\n");

        p = ra & ~3;
        p -= 32;
        if (p > ra)
            p = 0;
        end = p + 80;
        /* 'end - p' has to be multiples of 16 */
        while (end < p)
            end -= 16;

        /* Dump the code around ra as:
         *  addr       contents
         *  00008d34   fffffcd0 4c0eb530 b0934a0e 1c05447c
         *  00008d44   f7ff18a0 490ced94 68035860 d0012b00
         */
        while (p < end) {
            int i;

            sprintf(code_buffer, "%08x ", p);
            for (i = 0; i < 4; i++) {
                data = ptrace(PTRACE_PEEKTEXT, pid, (void*)p, NULL);
                sprintf(code_buffer + strlen(code_buffer), "%08x ", data);
                p += 4;
            }
            _LOG(tfd, only_in_tombstone, "%s\n", code_buffer);
        }
    }

    p = sp - 64;
    if (p > sp)
        p = 0;
    p &= ~3;
    if (unwind_depth != 0) {
        if (unwind_depth < STACK_CONTENT_DEPTH) {
            end = sp_list[unwind_depth-1];
        }
        else {
            end = sp_list[STACK_CONTENT_DEPTH-1];
        }
    }
    else {
        end = p + 256;
        /* 'end - p' has to be multiples of 4 */
        if (end < p)
            end = ~7;
    }

    _LOG(tfd, only_in_tombstone, "\nstack:\n");

    /* If the crash is due to PC == 0, there will be two frames that
     * have identical SP value.
     */
    if (sp_list[0] == sp_list[1]) {
        sp_depth = 1;
    }
    else {
        sp_depth = 0;
    }

    while (p <= end) {
         char *prompt;
         char level[16];
	 const char *mapname;
	 const char *symname;
	 unsigned int symoffset;

         data = ptrace(PTRACE_PEEKTEXT, pid, (void*)p, NULL);
         if (p == sp_list[sp_depth]) {
             sprintf(level, "#%02d", sp_depth++);
             prompt = level;
         }
         else {
             prompt = "   ";
         }

	 syminfo(map, data, &mapname, &symname, &symoffset);

         /* Print the stack content in the log for the first 3 frames. For the
          * rest only print them in the tombstone file.
          */
         if (symname)
	     _LOG(tfd, (sp_depth > 2) || only_in_tombstone,
		  "%s %08x  %08x  %s:%s+%d\n",
		  prompt, p, data, mapname, symname, symoffset);
	 else
	     _LOG(tfd, (sp_depth > 2) || only_in_tombstone,
		  "%s %08x  %08x  %s\n",
		  prompt, p, data, mapname);
         p += 4;
    }
    /* print another 64-byte of stack data after the last frame */

    end = p+64;
    /* 'end - p' has to be multiples of 4 */
    if (end < p)
        end = ~7;

    while (p <= end) {
         data = ptrace(PTRACE_PEEKTEXT, pid, (void*)p, NULL);
         _LOG(tfd, (sp_depth > 2) || only_in_tombstone,
              "    %08x  %08x  %s\n", p, data,
              map_to_name(map, data, ""));
         p += 4;
    }
}

void dump_pc_and_ra(int tfd, int pid, mapinfo *map, int unwound_level,
                    bool at_fault)
{
    struct pt_regs r;
    const char *mapname;
    const char *symname;
    unsigned int symoffset;

    if(ptrace(PTRACE_GETREGS, pid, 0, &r)) {
        _LOG(tfd, !at_fault, "tid %d not responding!\n", pid);
        return;
    }

    if (unwound_level == 0) {
	syminfo(map, R(r.cp0_epc), &mapname, &symname, &symoffset);
	 if (symname)
	     _LOG(tfd, !at_fault, "         #%02d  pc %08x  %s:%s+%d\n",
		  0, R(r.cp0_epc), mapname, symname, symoffset);
	 else
	     _LOG(tfd, !at_fault, "         #%02d  pc %08x  %s\n",
		  0, R(r.cp0_epc), mapname);
    }
    syminfo(map, R(r.regs[31]), &mapname, &symname, &symoffset);
    if (symname)
	_LOG(tfd, !at_fault,     "         #%02d  ra %08x  %s:%s+%d\n",
	     1, R(r.regs[31]), mapname, symname, symoffset);
    else
	_LOG(tfd, !at_fault,     "         #%02d  ra %08x  %s\n",
	     1, R(r.regs[31]), mapname);
}

void dump_registers(int tfd, int pid, bool at_fault)
{
    struct pt_regs r;
    bool only_in_tombstone = !at_fault;

    if(ptrace(PTRACE_GETREGS, pid, 0, &r)) {
	_LOG(tfd, only_in_tombstone,
	     "cannot get registers: %s\n", strerror(errno));
	return;
    }

    _LOG(tfd, only_in_tombstone, " zr %08x  at %08x  v0 %08x  v1 %08x\n",
	 R(r.regs[0]), R(r.regs[1]), R(r.regs[2]), R(r.regs[3]));
    _LOG(tfd, only_in_tombstone, " a0 %08x  a1 %08x  a2 %08x  a3 %08x\n",
	 R(r.regs[4]), R(r.regs[5]), R(r.regs[6]), R(r.regs[7]));
    _LOG(tfd, only_in_tombstone, " t0 %08x  t1 %08x  t2 %08x  t3 %08x\n",
	 R(r.regs[8]), R(r.regs[9]), R(r.regs[10]), R(r.regs[11]));
    _LOG(tfd, only_in_tombstone, " t4 %08x  t5 %08x  t6 %08x  t7 %08x\n",
	 R(r.regs[12]), R(r.regs[13]), R(r.regs[14]), R(r.regs[15]));
    _LOG(tfd, only_in_tombstone, " s0 %08x  s1 %08x  s2 %08x  s3 %08x\n",
	 R(r.regs[16]), R(r.regs[17]), R(r.regs[18]), R(r.regs[19]));
    _LOG(tfd, only_in_tombstone, " s4 %08x  s5 %08x  s6 %08x  s7 %08x\n",
	 R(r.regs[20]), R(r.regs[21]), R(r.regs[22]), R(r.regs[23]));
    _LOG(tfd, only_in_tombstone, " t8 %08x  t9 %08x  k0 %08x  k1 %08x\n",
	 R(r.regs[24]), R(r.regs[25]), R(r.regs[26]), R(r.regs[27]));
    _LOG(tfd, only_in_tombstone, " gp %08x  sp %08x  s8 %08x  ra %08x\n",
	 R(r.regs[28]), R(r.regs[29]), R(r.regs[30]), R(r.regs[31]));
    _LOG(tfd, only_in_tombstone, " hi %08x  lo %08x bva %08x epc %08x\n",
	 R(r.hi), R(r.lo), R(r.cp0_badvaddr), R(r.cp0_epc));
}
