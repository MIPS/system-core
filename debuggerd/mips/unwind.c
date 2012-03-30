#include <cutils/logd.h>
#include <sys/ptrace.h>
#include "../utility.h"
#include "mips_utility.h"

struct stackframe {
    int level;
    int depth;
    unsigned int sp;
    unsigned int ra;
    unsigned int pc;
};

#define GET_VALUE(var, ptr)	(var) = ptrace(PTRACE_PEEKTEXT, pid, (void*)(ptr), NULL);

#define DBG(s...) //_LOG(0, 0, "DBG:" s)

static int unwind_frame(pid_t pid, struct stackframe *frame) {
  struct stackframe old_frame = *frame;
  int ra_offset = 0;
  int stack_size = 0;
  unsigned int *addr;

  unsigned int maxcheck = 1024;
  int found_start = 0;
  int immediate;

  DBG("Starting scan using oldframe: pc=0x%08x ra=0x%08x sp=0x%08x\n", old_frame.pc, old_frame.ra, old_frame.sp);
  for (addr = (unsigned int *)frame->pc; maxcheck-- > 0 && !found_start; --addr) {
      unsigned int op;
      GET_VALUE(op, addr);

      DBG("@0x%08x: 0x%08x\n", addr, op);
      switch (op & 0xffff0000) {
      case 0x27bd0000: // addiu sp, imm
	  // looking for stack being decremented
	  immediate = ((((int)op) << 16) >> 16);
	  if (immediate < 0) {
	      stack_size = -immediate;
	      found_start = 1;
	      DBG("Found stack adjustment %d\n", stack_size);
	  }
	  break;
      case 0xafbf0000: // sw ra, imm(sp)
	  ra_offset = ((((int)op) << 16) >> 16);
	  DBG("Found ra offset %d\n", ra_offset);
	  break;
      case 0x3c1c0000: // lui gp
//      case 0x03e00000: // jr ra
	  DBG("Found function boundary\n");
	  found_start = 1;
      default:
	  break;
      }
  }

  if (ra_offset) {
      GET_VALUE(frame->ra, (unsigned long*) (frame->sp + ra_offset));
      DBG("New ra: 0x%08x\n", frame->ra);
  }

  if (stack_size) {
      frame->sp += stack_size;
      DBG("New sp: 0x%08x\n", frame->sp);
  }

  if (frame->pc == frame->ra && stack_size == 0)
      return 1;

  frame->level++;
  frame->pc = frame->ra;

  return 0;
}


int unwind_backtrace_with_ptrace_mips(int tfd, pid_t pid, mapinfo *map,
				      int sp_list[], bool at_fault)
{
    user_regs_struct r;
    struct stackframe frame;
    unsigned int rel_pc;
	 const char *mapname;
	 const char *symname;
	 unsigned int symoffset;

    DBG("Begin unwind_backtrace_with_ptrace_mips\n");

    if(ptrace(PTRACE_GETREGS, pid, 0, &r))
	return 0;

    frame.level = 0;
    frame.depth = 0;
    frame.sp = r.regs[MIPS_REG_SP];
    frame.ra = r.regs[MIPS_REG_RA];
    frame.pc = r.cp0_epc;
    
    do {
	DBG("Current frame #%d: pc=0x%08x ra=0x%08x sp=0x%08x\n", frame.level, frame.pc, frame.ra, frame.sp);
        /* Get symbolic information for this pc */
	syminfo(map, frame.pc, &mapname, &symname, &symoffset);
        if (symname)
	    _LOG(tfd, !at_fault, "         #%02d  pc %08x sp %08x   %s:%s+%d\n", frame.level, frame.pc, frame.sp, mapname, symname, symoffset);
	else
            _LOG(tfd, !at_fault, "         #%02d  pc %08x sp %08x   %s\n", frame.level, frame.pc, frame.sp, mapname);
	sp_list[frame.level] = frame.sp;
    } while (unwind_frame(pid, &frame) == 0 && frame.level < STACK_CONTENT_DEPTH);

    DBG("End unwind_backtrace_with_ptrace_mips\n");

    return frame.level;
}

