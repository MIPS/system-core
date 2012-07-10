/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Backtracing functions for mips
 */

#define LOG_TAG "Corkscrew"
//#define LOG_NDEBUG 0

#include "../backtrace-arch.h"
#include "../backtrace-helper.h"
#include <corkscrew/ptrace.h>

#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/exec_elf.h>
#include <cutils/log.h>

/* For PTRACE_GETREGS */
typedef struct {
    /* FIXME: check this definition */
    uint64_t regs[32];
    uint64_t lo;
    uint64_t hi;
    uint64_t epc;
    uint64_t badvaddr;
    uint64_t status;
    uint64_t cause;
} user_regs_struct;

/* Machine context at the time a signal was raised. */
typedef struct ucontext {
    /* FIXME: use correct definition */
    uint32_t sp;
    uint32_t ra;
    uint32_t pc;
} ucontext_t;

/* Unwind state. */
typedef struct {
    uint32_t sp;
    uint32_t ra;
    uint32_t pc;
} unwind_state_t;

uintptr_t rewind_pc_arch(const memory_t* memory, uintptr_t pc) {
    /* FIXME: implement */
      
    return pc;
}

static ssize_t unwind_backtrace_common(const memory_t* memory,
        const map_info_t* map_info_list,
        unwind_state_t* state, backtrace_frame_t* backtrace,
        size_t ignore_depth, size_t max_depth) {
    size_t ignored_frames = 0;
    size_t returned_frames = 0;

    /* FIXME: implement */
    return returned_frames;
}

ssize_t unwind_backtrace_signal_arch(siginfo_t* siginfo, void* sigcontext,
        const map_info_t* map_info_list,
        backtrace_frame_t* backtrace, size_t ignore_depth, size_t max_depth) {
    const ucontext_t* uc = (const ucontext_t*)sigcontext;

    unwind_state_t state;
    state.sp = uc->sp;
    state.pc = uc->pc;
    state.ra = uc->ra;

    memory_t memory;
    init_memory(&memory, map_info_list);
    return unwind_backtrace_common(&memory, map_info_list,
            &state, backtrace, ignore_depth, max_depth);
}

ssize_t unwind_backtrace_ptrace_arch(pid_t tid, const ptrace_context_t* context,
        backtrace_frame_t* backtrace, size_t ignore_depth, size_t max_depth) {

    user_regs_struct regs;	
    if (ptrace(PTRACE_GETREGS, tid, 0, &regs)) {
        return -1;
    }

    unwind_state_t state;
    state.sp = regs.regs[29];
    state.ra = regs.regs[31];
    state.pc = regs.epc;

    memory_t memory;
    init_memory_ptrace(&memory, tid);
    return unwind_backtrace_common(&memory, context->map_info_list,
            &state, backtrace, ignore_depth, max_depth);
}
