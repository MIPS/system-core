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

#define DUMP_MEM_FOR_ALL_REGS 0

#define R(x) ((unsigned int)(x))

/*
 * If this isn't clearly a null pointer dereference, dump the
 * /proc/maps entries near the fault address.
 *
 * This only makes sense to do on the thread that crashed.
 */
void show_nearby_maps(int tfd, int pid, mapinfo *map)
{
    siginfo_t si;

    memset(&si, 0, sizeof(si));
    if (ptrace(PTRACE_GETSIGINFO, pid, 0, &si)) {
        _LOG(tfd, false, "cannot get siginfo for %d: %s\n",
            pid, strerror(errno));
        return;
    }
    if (!signal_has_address(si.si_signo))
        return;

    uintptr_t addr = (uintptr_t) si.si_addr;
    addr &= ~0xfff;     /* round to 4K page boundary */
    if (addr == 0)      /* null-pointer deref */
        return;

    _LOG(tfd, false, "\nmemory map around addr %08x:\n", si.si_addr);

    /*
     * Search for a match, or for a hole where the match would be.  The list
     * is backward from the file content, so it starts at high addresses.
     */
    bool found = false;
    mapinfo *next = NULL;
    mapinfo *prev = NULL;
    while (map != NULL) {
        if (addr >= map->start && addr < map->end) {
            found = true;
            next = map->next;
            break;
        } else if (addr >= map->end) {
            /* map would be between "prev" and this entry */
            next = map;
            map = NULL;
            break;
        }

        prev = map;
        map = map->next;
    }

    /*
     * Show "next" then "match" then "prev" so that the addresses appear in
     * ascending order (like /proc/pid/maps).
     */
    if (next != NULL) {
        _LOG(tfd, false, "%08x-%08x %s\n", next->start, next->end, next->name);
    } else {
        _LOG(tfd, false, "(no map below)\n");
    }
    if (map != NULL) {
        _LOG(tfd, false, "%08x-%08x %s\n", map->start, map->end, map->name);
    } else {
        _LOG(tfd, false, "(no map for address)\n");
    }
    if (prev != NULL) {
        _LOG(tfd, false, "%08x-%08x %s\n", prev->start, prev->end, prev->name);
    } else {
        _LOG(tfd, false, "(no map above)\n");
    }
}

/*
 * Dumps a few bytes of memory, starting a bit before and ending a bit
 * after the specified address.
 */
static void dump_memory(int tfd, int pid, uintptr_t addr,
    bool only_in_tombstone)
{
    char code_buffer[64];       /* actual 8+1+((8+1)*4) + 1 == 45 */
    char ascii_buffer[32];      /* actual 16 + 1 == 17 */
    uintptr_t p, end;

    p = addr & ~3;
    p -= 32;
    if (p > addr) {
        /* catch underflow */
        p = 0;
    }
    end = p + 80;
    /* catch overflow; 'end - p' has to be multiples of 16 */
    while (end < p)
        end -= 16;

    /* Dump the code around PC as:
     *  addr     contents                             ascii
     *  00008d34 ef000000 e8bd0090 e1b00000 512fff1e  ............../Q
     *  00008d44 ea00b1f9 e92d0090 e3a070fc ef000000  ......-..p......
     */
    while (p < end) {
        char* asc_out = ascii_buffer;

        sprintf(code_buffer, "%08x ", p);

        int i;
        for (i = 0; i < 4; i++) {
            /*
             * If we see (data == -1 && errno != 0), we know that the ptrace
             * call failed, probably because we're dumping memory in an
             * unmapped or inaccessible page.  I don't know if there's
             * value in making that explicit in the output -- it likely
             * just complicates parsing and clarifies nothing for the
             * enlightened reader.
             */
            long data = ptrace(PTRACE_PEEKTEXT, pid, (void*)p, NULL);
            sprintf(code_buffer + strlen(code_buffer), "%08lx ", data);

            int j;
            for (j = 0; j < 4; j++) {
                /*
                 * Our isprint() allows high-ASCII characters that display
                 * differently (often badly) in different viewers, so we
                 * just use a simpler test.
                 */
                char val = (data >> (j*8)) & 0xff;
                if (val >= 0x20 && val < 0x7f) {
                    *asc_out++ = val;
                } else {
                    *asc_out++ = '.';
                }
            }
            p += 4;
        }
        *asc_out = '\0';
        _LOG(tfd, only_in_tombstone, "%s %s\n", code_buffer, ascii_buffer);
    }

}

void dump_stack_and_code(int tfd, int pid, mapinfo *map,
                         int unwind_depth, unsigned int sp_list[],
                         bool at_fault)
{
    struct pt_regs r;
    int sp_depth;
    bool only_in_tombstone = !at_fault;

    if(ptrace(PTRACE_GETREGS, pid, 0, &r)) return;

    if (DUMP_MEM_FOR_ALL_REGS && at_fault) {
        /*
         * If configured to do so, dump memory around *all* registers
         * for the crashing thread.
         *
         * TODO: remove duplicates.
         */
	static const char REG_NAMES[] = "$0atv0v1a0a1a2a3t0t1t2t3t4t5t6t7s0s1s2s3s4s5s6s7t8t9k0k1gpsps8ra";

        int reg;
        for (reg = 0; reg < 32; reg++) {

	    /* skip uninteresting registers */
	    if (reg == 0 /* $0 */
		|| reg == 26 /* $k0 */
		|| reg == 27 /* $k1 */
		)
		continue;

            uintptr_t addr = r.regs[reg];

            /*
             * Don't bother if it looks like a small int or ~= null, or if
             * it's in the kernel area.
             */
            if (addr < 4096 || addr >= 0x80000000) {
                continue;
            }

            _LOG(tfd, only_in_tombstone, "\nmem near %.2s:\n",
                &REG_NAMES[reg*2]);
            dump_memory(tfd, pid, addr, false);
        }
    } else {
	unsigned int pc = R(r.cp0_epc);
	unsigned int ra = R(r.regs[31]);

	_LOG(tfd, only_in_tombstone, "\ncode around pc:\n");
        dump_memory(tfd, pid, (uintptr_t)pc, only_in_tombstone);
	if (ra != pc) {
	    _LOG(tfd, only_in_tombstone, "\ncode around ra:\n");
	    dump_memory(tfd, pid, (uintptr_t)ra, only_in_tombstone);
	}
    }

    if (at_fault) {
        show_nearby_maps(tfd, pid, map);
    }

    unsigned int p, end;
    unsigned int sp = R(r.regs[29]);

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

         unsigned int data = ptrace(PTRACE_PEEKTEXT, pid, (void*)p, NULL);
	 
         if (p == sp_list[sp_depth]) {
             sprintf(level, "#%02d", sp_depth++);
             prompt = level;
         }
         else {
             prompt = "   ";
         }

	 syminfo(map, data, &mapname, &symname, &symoffset);

         /* Print the stack content in the log for the first 4 frames. For the
          * rest only print them in the tombstone file.
          */
         if (symname)
	     _LOG(tfd, (sp_depth > 3) || only_in_tombstone,
		  "%s %08x  %08x  %s:%s+%d\n",
		  prompt, p, data, mapname, symname, symoffset);
	 else
	     _LOG(tfd, (sp_depth > 3) || only_in_tombstone,
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
	unsigned int data = ptrace(PTRACE_PEEKTEXT, pid, (void*)p, NULL);
	_LOG(tfd, (sp_depth > 3) || only_in_tombstone,
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
