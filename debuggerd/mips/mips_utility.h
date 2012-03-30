/*
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

/* PTRACE_GETREGS/PTRACE_SETREGS */
typedef struct user_regs_struct {
	uint64_t regs[32];
	uint64_t lo;
	uint64_t hi;
	uint64_t cp0_epc;
	uint64_t cp0_badvaddr;
	uint64_t cp0_status;
	uint64_t cp0_cause;
} user_regs_struct;

#define MIPS_REG_SP	29
#define MIPS_REG_RA	31

/* PTRACE_GETFPREGS/PTRACE_SETFPREGS */
typedef struct user_fpregs_struct {
	uint64_t regs[32];
	uint32_t fpcsr;
	uint32_t fir;
} user_fpregs_struct;
