/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine].
 *
 * The Initial Developer of the Original Code is
 * MIPS Technologies Inc
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Chris Dearman <chris@mips.com>
 *   Bhanu Chetlapalli <bhanu@mips.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __ACCMIPS_H__
#define __ACCMIPS_H__

#ifdef    DEBUG
        int tabs;
#define    DBGPRNT_ENTRY()    do {   \
        int i;                       \
        char str[16];                \
        for (i = 0; i < tabs; i++)   \
            str[i] = '\t';           \
        str[i] = '\0';               \
        LOGD("%s\t#ENTRY %s\n", str,__FUNCTION__);\
        tabs++;                      \
    } while (0)
#define    DBGPRNT_EXIT()    do {    \
        tabs--;                      \
        int i;                       \
        char str[16];                \
        for (i = 0; i < tabs; i++)   \
            str[i] = '\t';           \
        str[i] = '\0';               \
        LOGD("%s\t#EXIT  %s\n", str, __FUNCTION__); \
    } while (0)
#define    DBGPRINT        LOGD

#else

#define    DBGPRNT_ENTRY()
#define    DBGPRNT_EXIT()
#define    DBGPRINT

#endif

#define    STACK_ALIGNMENT 8


#if !defined(__mips_soft_float) || __mips_soft_float != 1
#define    MIPS_USE_HARDFLOAT
#endif

    typedef uint64_t RegisterMask;        // REQ: Large enough to hold LastReg-FirstReg bits
#define _rmask_(r)        (1LL<<(r))
    typedef enum {                        // REQ: Register identifiers
        // Register numbers for Native code generator
        ZERO = 0,   AT = 1,   V0 = 2,   V1 = 3,   A0 = 4,   A1 = 5,   A2 = 6,   A3 = 7,
        T0   = 8,   T1 = 9,   T2 = 10,  T3 = 11,  T4 = 12,  T5 = 13,  T6 = 14,  T7 = 15,
        S0   = 16,  S1 = 17,  S2 = 18,  S3 = 19,  S4 = 20,  S5 = 21,  S6 = 22,  S7 = 23,
        T8   = 24,  T9 = 25,  K0 = 26,  K1 = 27,  GP = 28,  SP = 29,  FP = 30,  RA = 31,

        F0   = 32,  F1 = 33,  F2 = 34,  F3 = 35,  F4 = 36,  F5 = 37,  F6 = 38,  F7 = 39,
        F8   = 40,  F9 = 41, F10 = 42, F11 = 43, F12 = 44, F13 = 45, F14 = 46, F15 = 47,
        F16  = 48, F17 = 49, F18 = 50, F19 = 51, F20 = 52, F21 = 53, F22 = 54, F23 = 55,
        F24  = 56, F25 = 57, F26 = 58, F27 = 59, F28 = 60, F29 = 61, F30 = 62, F31 = 63,

        // FP register aliases
        FV0 = F0, FV1 = F2,
        FA0 = F12, FA1 = F14,
        FT0 = F4, FT1 = F6, FT2 = F8, FT3 = F10, FT4 = F16, FT5 = F18,
        FS0 = F20, FS1 = F22, FS2 = F24, FS3 = F26, FS4 = F28, FS5 = F30,

        // Wellknown register names used by code generator
        FirstReg = AT,
        LastReg = F31,

    } Register;

#define GPR(r) ((r)&31)
#define FPR(r) ((r)&31)

#ifdef    DEBUG
#define EMIT(ins, fmt, ...) do {               \
        o4(ins);                               \
        char str[64];                          \
        snprintf(str, 63, fmt, ##__VA_ARGS__); \
        DBGPRINT("%#0x : %s\n", getPC() - 4, str);    \
    } while (0)
#else
#define EMIT(ins, fmt, ...) do {               \
        o4(ins);                               \
    } while (0)
#endif


/* Define registers for easier usage */
#define        MIPS_INT_REG           S0
#define        MIPS_INT_TMPREG        T2
#define        MIPS_INT_TMPREG2       T3
#define        MIPS_INT_FP            FP
#define        MIPS_INT_REG_STACK     T6
#define        MIPS_LINK_REG          T9

#ifdef    MIPS_USE_HARDFLOAT

#define        MIPS_FLOAT_REG         F20
#define        MIPS_FLOAT_REG2        (MIPS_FLOAT_REG + 1)
#define        MIPS_FLOAT_TMPREG      F6
#define        MIPS_FLOAT_TMPREG2     (MIPS_FLOAT_TMPREG + 1)
#define        MIPS_FLOAT_REG_STACK   F8

#else    // Soft Floats
#define        MIPS_INT_REG2          S1
#endif

#define        MIPSABI_BASE_ARGS_SIZE 16
    



// Opcodes: bits 31..26
#define OP_SPECIAL      0x00
#define OP_REGIMM       0x01
#define OP_J            0x02
#define OP_JAL          0x03
#define OP_BEQ          0x04
#define OP_BNE          0x05
#define OP_ADDIU        0x09
#define OP_SLTIU        0x0b
#define OP_ANDI         0x0c
#define OP_ORI          0x0d
#define OP_XORI         0x0e
#define OP_LUI          0x0f
#define OP_COP1         0x11
#define OP_COP1X        0x13
#define OP_SPECIAL2     0x1c
#define OP_LB           0x20
#define OP_LH           0x21
#define OP_LW           0x23
#define OP_LBU          0x24
#define OP_LHU          0x25
#define OP_SB           0x28
#define OP_SH           0x29
#define OP_SW           0x2b
#define OP_LWC1         0x31
#define OP_LDC1         0x35
#define OP_SWC1         0x39
#define OP_SDC1         0x3d
#define    OP_MAX            0x40

// REGIMM: bits 20..16
#define REGIMM_BLTZ     0x00
#define REGIMM_BGEZ     0x01

// COP1: bits 25..21
#define COP1_ADD        0x00
#define COP1_SUB        0x01
#define COP1_MUL        0x02
#define COP1_DIV        0x03
#define COP1_MOV        0x06
#define COP1_NEG        0x07
#define COP1_BC         0x08
#define COP1_TRUNCW     0x0d
#define COP1_CVTS       0x20
#define COP1_CVTD       0x21

// COP1X: bits 5..0
#define COP1X_LDXC1     0x01
#define COP1X_SDXC1     0x09

// SPECIAL: bits 5..0
#define SPECIAL_SLL     0x00
#define SPECIAL_MOVCI   0x01
#define SPECIAL_SRL     0x02
#define SPECIAL_SRA     0x03
#define SPECIAL_SLLV    0x04
#define SPECIAL_SRLV    0x06
#define SPECIAL_SRAV    0x07
#define SPECIAL_JR      0x08
#define SPECIAL_JALR    0x09
#define SPECIAL_MOVN    0x0b
#define SPECIAL_MFHI    0x10
#define SPECIAL_MFLO    0x12
#define SPECIAL_MULT    0x18
#define SPECIAL_DIVU     0x1A
#define SPECIAL_ADDU    0x21
#define SPECIAL_SUBU    0x23
#define SPECIAL_AND     0x24
#define SPECIAL_OR      0x25
#define SPECIAL_XOR     0x26
#define SPECIAL_NOR     0x27
#define SPECIAL_SLT     0x2a
#define SPECIAL_SLTU    0x2b

// SPECIAL2: bits 5..0
#define SPECIAL2_MUL    0x02

// FORMAT: bits 25..21
#define FMT_S           0x10
#define FMT_D           0x11
#define FMT_W           0x14
#define FMT_L           0x15
#define FMT_PS          0x16
#define    FMT_MAX            0x20

// CONDITION: bits 4..0
#define COND_F          0x0
#define COND_UN         0x1
#define COND_EQ         0x2
#define COND_UEQ        0x3
#define COND_OLT        0x4
#define COND_ULT        0x5
#define COND_OLE        0x6
#define COND_ULE        0x7
#define COND_SF         0x8
#define COND_NGLE       0x9
#define COND_SEQ        0xa
#define COND_NGL        0xb
#define COND_LT         0xc
#define COND_NGE        0xd
#define COND_LE         0xe
#define COND_NGT        0xf
#define    COND_MAX        0x10

// Helper definitions to encode different classes of MIPS instructions
// Parameters are in instruction order

#define R_FORMAT(op, rs, rt, rd, re, func)                              \
    (((op)<<26)|(GPR(rs)<<21)|(GPR(rt)<<16)|(GPR(rd)<<11)|((re)<<6)|(func))

#define I_FORMAT(op, rs, rt, simm)                              \
    (((op)<<26)|(GPR(rs)<<21)|(GPR(rt)<<16)|((simm)&0xffff))

#define J_FORMAT(op, index)                     \
    (((op)<<26)|(index))

#define U_FORMAT(op, rs, rt, uimm)                              \
    (((op)<<26)|(GPR(rs)<<21)|(GPR(rt)<<16)|((uimm)&0xffff))

#define F_FORMAT(op, ffmt, ft, fs, fd, func)                            \
    (((op)<<26)|((ffmt)<<21)|(FPR(ft)<<16)|(FPR(fs)<<11)|(FPR(fd)<<6)|(func))

static inline const char * gpn(int no)
{
    static const char *arr[] = {
        "ZERO",  "AT",  "V0",  "V1",  "A0",  "A1",  "A2",  "A3",
          "T0",  "T1",  "T2",  "T3",  "T4",  "T5",  "T6",  "T7",
          "S0",  "S1",  "S2",  "S3",  "S4",  "S5",  "S6",  "S7",
          "T8",  "T9",  "K0",  "K1",  "GP",  "SP",  "S8",  "RA",

          "F0",  "F1",  "F2",  "F3",  "F4",  "F5",  "F6",  "F7",
          "F8",  "F9",  "F10", "F11", "F12", "F13", "F14", "F15",
          "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23",
          "F24", "F25", "F26", "F27", "F28", "F29", "F30", "F31",

    };
    return arr[no];
}

#ifdef    DEBUG
static const char *cname[COND_MAX];
static const char *fname[FMT_MAX];
static const char *oname[OP_MAX];
static void load_mips_ins_names(void) {
    /* Expand this table on demand */

    // CNAMES
    cname[COND_EQ] = "EQ";
    cname[COND_LE] = "LE";
    cname[COND_LT] = "LT";
    // FNAMES
    fname[FMT_D] = "DBL";
    fname[FMT_S] = "SNGL";
    fname[FMT_W] = "WORD";
    // ONAMES
    oname[OP_LB] = "LB";
    oname[OP_LH] = "LH";
    oname[OP_LW] = "LW";
    oname[OP_SW] = "SW";
    oname[OP_SH] = "SH";
    oname[OP_SB] = "SB";
    oname[OP_LWC1] = "LWC1";
    oname[OP_SWC1] = "SWC1";
    oname[OP_LDC1] = "LDC1";
    oname[OP_SDC1] = "SDC1";
    oname[OP_BNE] = "BNE";
    oname[OP_BEQ] = "BEQ";
}
#endif

#define fpn(fr) gpn(fr)

//#define BOFFSET(targ)    (uint32_t(targ - (_nIns+1)))

#define LDST(op, rt, offset, base, line)                                      \
    do { EMIT(I_FORMAT(op, base, rt, offset),             \
                            "%s %s, %d(%s) ;# @ %d", oname[op], gpn(rt), offset, gpn(base), line); } while (0)

#define BX(op, rs, rt, targ, line)                                            \
    do { EMIT(I_FORMAT(op, rs, rt, targ),          \
                          "%s %s, %s, %d ;# @ %d", oname[op], gpn(rt), gpn(rs), targ & 0x0000FFFF, line); } while (0)

// MIPS instructions
// Parameters are in "assembler" order
#define ADDIU(rt, rs, simm, line)                                             \
    do { EMIT(I_FORMAT(OP_ADDIU, rs, rt, simm),            \
                           "ADDIU %s, %s, %d ;# @ %d", gpn(rt), gpn(rs), simm, line); } while (0)

#define ADDU(rd, rs, rt, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_ADDU), \
                           "ADDU %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

/* Implemented with ADDU */
#define    MOV(rd, rs, line)                                    \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, ZERO, rd, 0, SPECIAL_ADDU), \
                           "MOV %s, %s ;# @ %d", gpn(rd), gpn(rs), line); } while (0)

#define AND(rd, rs, rt, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_AND), \
                           "AND %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define ANDI(rt, rs, uimm, line)                                              \
    do { EMIT(U_FORMAT(OP_ANDI, rs, rt, uimm),             \
                           "ANDI %s, %s, 0x%x ;# @ %d", gpn(rt), gpn(rs), ((uimm)&0xffff), line); } while (0)

#define BC1F(targ, line)                                                      \
    do { EMIT(I_FORMAT(OP_COP1, COP1_BC, 0, targ), \
                          "BC1F %d ;# @ %d", targ, line); } while (0)

#define BC1T(targ, line)                                                      \
    do { EMIT(I_FORMAT(OP_COP1, COP1_BC, 1, targ), \
                          "BC1T %d ;# @ %d", targ, line); } while (0)

#define B(targ, line)                 BX(OP_BEQ, ZERO, ZERO, targ, line)
#define BEQ(rs, rt, targ, line)       BX(OP_BEQ, rs, rt, targ, line)
#define BNE(rs, rt, targ, line)       BX(OP_BNE, rs, rt, targ, line)
#define BLEZ(rs, targ, line)          BX(OP_BLEZ, rs, ZERO, targ, line)
#define BGTZ(rs, targ, line)          BX(OP_BGTZ, rs, ZERO, targ, line)
#define BGEZ(rs, targ, line)          BX(OP_REGIMM, rs, REGIMM_BGEZ, targ, line)
#define BLTZ(rs, targ, line)          BX(OP_REGIMM, rs, REGIMM_BLTZ, targ, line)

#define JINDEX(dest) ((uint32_t(dest)>>2)&0x03ffffff)

#define J(dest, line)                                            \
    do { EMIT(J_FORMAT(OP_J, JINDEX(dest)),   \
                           "J %d ;# JINDX=%d @ %d", dest, JINDEX(dest), line); } while (0)

#define JAL(dest, line)                                                    \
    do { EMIT(J_FORMAT(OP_JAL, JINDEX(dest)), \
                           "JAL 0x%x ;# @ %d", uint32_t(dest), line); } while (0)

#define JALR(rs, line)                                                        \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, 0, RA, 0, SPECIAL_JALR), \
                           "JALR %s ;# @ %d", gpn(rs), line); } while (0)

#define JR(rs, line)                                                            \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, 0, 0, 0, SPECIAL_JR), \
                           "JR %s ;# @ %d", gpn(rs), line); } while (0)

#define LB(rt, offset, base, line)                    \
    LDST(OP_LB, rt, offset, base, line)

#define LH(rt, offset, base, line)                    \
    LDST(OP_LH, rt, offset, base, line)

#define LUI(rt, uimm, line)                                                   \
    do { EMIT(U_FORMAT(OP_LUI, 0, rt, uimm),               \
                           "LUI %s, 0x%x ;# @ %d", gpn(rt), ((uimm)&0xffff), line); } while (0)

#define LW(rt, offset, base, line)                    \
    LDST(OP_LW, rt, offset, base, line)

#define MFHI(rd, line)                                                        \
    do { EMIT(R_FORMAT(OP_SPECIAL, 0, 0, rd, 0, SPECIAL_MFHI), \
                           "MFHI %s ;# @ %d", gpn(rd), line); } while (0)

#define MFLO(rd, line)                                                        \
    do { EMIT(R_FORMAT(OP_SPECIAL, 0, 0, rd, 0, SPECIAL_MFLO), \
                           "MFLO %s ;# @ %d", gpn(rd), line); } while (0)

#define MUL(rd, rs, rt, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL2, rs, rt, rd, 0, SPECIAL2_MUL), \
                           "MUL %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define DIVU(rd, rs, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rd, 0, 0, SPECIAL_DIVU), \
                           "DIVU %s, %s ;# @ %d", gpn(rd), gpn(rs), line); } while (0)

#define MULT(rs, rt, line)                                                    \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, 0, 0, SPECIAL_MULT), \
                           "MULT %s, %s ;# @ %d", gpn(rs), gpn(rt), line); } while (0)

#define MOVN(rd, rs, rt, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_MOVN), \
                           "MOVN %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define NEGU(rd, rt, line)                                                    \
    do { EMIT(R_FORMAT(OP_SPECIAL, ZERO, rt, rd, 0, SPECIAL_SUBU), \
                           "NEGU %s, %s ;# @ %d", gpn(rd), gpn(rt), line); } while (0)

#define NOP(line)                                                           \
    do { EMIT(R_FORMAT(OP_SPECIAL, 0, 0, 0, 0, SPECIAL_SLL), \
                            "NOP ;# @ %d", line); } while (0)

/* MIPS III and below sometimes need a NOP immediatly after doing a float comparison,
 * before the flags can be read. */
#ifdef    MIPS_III_AND_BELOW
#define    MIPS_III_NOP_AFTER_FLOAT_CMP(line)    NOP(line)
#else
#define    MIPS_III_NOP_AFTER_FLOAT_CMP(line)
#endif

#define NOR(rd, rs, rt, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_NOR), \
                           "NOR %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define NOT(rd, rs, line)                                                     \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, ZERO, rd, 0, SPECIAL_NOR), \
                           "NOT %s, %s ;# @ %d", gpn(rd), gpn(rs), line); } while (0)

#define OR(rd, rs, rt, line)                                                  \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_OR), \
                           "OR %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define ORI(rt, rs, uimm, line)                                               \
    do { EMIT(U_FORMAT(OP_ORI, rs, rt, uimm),              \
                           "ORI %s, %s, 0x%x ;# @ %d", gpn(rt), gpn(rs), ((uimm)&0xffff), line); } while (0)

#define SLTIU(rt, rs, simm, line)                                             \
    do { EMIT(I_FORMAT(OP_SLTIU, rs, rt, simm),            \
                           "SLTIU %s, %s, %d ;# @ %d", gpn(rt), gpn(rs), simm, line); } while (0)

#define SLT(rd, rs, rt, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_SLT), \
                           "SLT %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define SLTU(rd, rs, rt, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_SLTU), \
                           "SLTU %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define SLL(rd, rt, sa, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, 0, rt, rd, sa, SPECIAL_SLL), \
                           "SLL %s, %s, %d ;# @ %d", gpn(rd), gpn(rt), sa, line); } while (0)

#define SLLV(rd, rt, rs, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_SLLV), \
                            "SLLV %s, %s, %s ;# @ %d", gpn(rd), gpn(rt), gpn(rs), line); } while (0)

#define SRA(rd, rt, sa, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, 0, rt, rd, sa, SPECIAL_SRA), \
                           "SRA %s, %s, %d ;# @ %d", gpn(rd), gpn(rt), sa, line); } while (0)

#define SRAV(rd, rt, rs, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_SRAV), \
                           "SRAV %s, %s, %s ;# @ %d", gpn(rd), gpn(rt), gpn(rs), line); } while (0)

#define SRL(rd, rt, sa, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, 0, rt, rd, sa, SPECIAL_SRL), \
                           "SRL %s, %s, %d ;# @ %d", gpn(rd), gpn(rt), sa, line); } while (0)

#define SRLV(rd, rt, rs, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_SRLV), \
                           "SRLV %s, %s, %s ;# @ %d", gpn(rd), gpn(rt), gpn(rs), line); } while (0)

#define SUBU(rd, rs, rt, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_SUBU), \
                           "SUBU %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define SW(rt, offset, base, line)                    \
    LDST(OP_SW, rt, offset, base, line)

#define SH(rt, offset, base, line)                    \
    LDST(OP_SH, rt, offset, base, line)

#define SB(rt, offset, base, line)                    \
    LDST(OP_SB, rt, offset, base, line)

#define XOR(rd, rs, rt, line)                                                 \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, rt, rd, 0, SPECIAL_XOR), \
                           "XOR %s, %s, %s ;# @ %d", gpn(rd), gpn(rs), gpn(rt), line); } while (0)

#define XORI(rt, rs, uimm, line)                                              \
    do { EMIT(U_FORMAT(OP_XORI, rs, rt, uimm),             \
                           "XORI %s, %s, 0x%x ;# @ %d", gpn(rt), gpn(rs), ((uimm)&0xffff), line); } while (0)


/* FPU instructions */
#ifdef MIPS_USE_HARDFLOAT

#define FOP_FMT2(ffmt, fd, fs, func, name, line)                              \
    do { EMIT(F_FORMAT(OP_COP1, ffmt, 0, fs, fd, func),    \
                           "%s.%s %s, %s ;# @ %d", name, fname[ffmt], fpn(fd), fpn(fs), line); } while (0)

#define FOP_FMT3(ffmt, fd, fs, ft, func, name, line)                          \
    do { EMIT(F_FORMAT(OP_COP1, ffmt, ft, fs, fd, func),   \
                           "%s.%s %s, %s, %s ;# @ %d", name, fname[ffmt], fpn(fd), fpn(fs), fpn(ft), line); } while (0)

#define C_COND_FMT(cond, ffmt, fs, ft, line)                                  \
    do { EMIT(F_FORMAT(OP_COP1, ffmt, ft, fs, 0, 0x30|(cond)), \
                           "C.%s.%s %s, %s ;# @ %d", cname[cond], fname[ffmt], fpn(fs), fpn(ft), line); } while (0)

#define MFC1(rt, fs, line)                                                    \
    do { EMIT(F_FORMAT(OP_COP1, 0, rt, fs, 0, 0),          \
                           "MFC1 %s, %s ;# @ %d", gpn(rt), fpn(fs), line); } while (0)

#define MTC1(rt, fs, line)                                                    \
    do { EMIT(F_FORMAT(OP_COP1, 4, rt, fs, 0, 0),          \
                           "MTC1 %s, %s ;# @ %d", gpn(rt), fpn(fs), line); } while (0)

#define MOVF(rd, rs, cc, line)                                                \
    do { EMIT(R_FORMAT(OP_SPECIAL, rs, (cc)<<2, rd, 0, SPECIAL_MOVCI), \
                           "MOVF %s, %s, $fcc%d ;# @ %d", gpn(rd), gpn(rs), cc, line); } while (0)

#define CVT_D_W(fd, fs, line)                                                 \
    do { EMIT(F_FORMAT(OP_COP1, FMT_W, 0, fs, fd, COP1_CVTD), \
                           "CVT.D.W %s, %s ;# @ %d", fpn(fd), fpn(fs), line); } while (0)

#define CVT_S_W(fd, fs, line)                                                 \
    do { EMIT(F_FORMAT(OP_COP1, FMT_W, 0, fs, fd, COP1_CVTS), \
                           "CVT.S.W %s, %s ;# @ %d", fpn(fd), fpn(fs), line); } while (0)

#define CVT_S_D(fd, fs, line)                                                 \
    do { EMIT(F_FORMAT(OP_COP1, FMT_D, 0, fs, fd, COP1_CVTS), \
                           "CVT.S.D %s, %s ;# @ %d", fpn(fd), fpn(fs), line); } while (0)
#define CVT_D_S(fd, fs, line)                                                 \
    do { EMIT(F_FORMAT(OP_COP1, FMT_S, 0, fs, fd, COP1_CVTD), \
                           "CVT.D.S %s, %s ;# @ %d", fpn(fd), fpn(fs), line); } while (0)

#define TRUNC_W_S(fd, fs, line)                                               \
    do { EMIT(F_FORMAT(OP_COP1, FMT_S, 0, fs, fd, COP1_TRUNCW), \
                           "TRUNC.W.S %s, %s ;# @ %d", fpn(fd), fpn(fs), line); } while (0)

#define TRUNC_W_D(fd, fs, line)                                               \
    do { EMIT(F_FORMAT(OP_COP1, FMT_D, 0, fs, fd, COP1_TRUNCW), \
                           "TRUNC.W.D %s, %s ;# @ %d", fpn(fd), fpn(fs), line); } while (0)


#define LWC1(ft, offset, base, line)  LDST(OP_LWC1, ft, offset, base, line)
#define SWC1(ft, offset, base, line)  LDST(OP_SWC1, ft, offset, base, line)
#define LDC1(ft, offset, base, line)  LDST(OP_LDC1, ft, offset, base, line)
#define SDC1(ft, offset, base, line)  LDST(OP_SDC1, ft, offset, base, line)
#define LDXC1(fd, index, base, line)                                          \
    do { EMIT(R_FORMAT(OP_COP1X, base, index, 0, fd, COP1X_LDXC1), \
                           "LDXC1 %s, %s(%s) ;# @ %d", fpn(fd), gpn(index), gpn(base), line); } while (0)
#define SDXC1(fs, index, base, line)                                          \
    do { EMIT(R_FORMAT(OP_COP1X, base, index, fs, 0, COP1X_SDXC1), \
                           "SDXC1 %s, %s(%s) ;# @ %d", fpn(fs), gpn(index), gpn(base), line); } while (0)

#define C_EQ_D(fs, ft, line)          C_COND_FMT(COND_EQ, FMT_D, fs, ft, line)
#define C_LE_D(fs, ft, line)          C_COND_FMT(COND_LE, FMT_D, fs, ft, line)
#define C_LT_D(fs, ft, line)          C_COND_FMT(COND_LT, FMT_D, fs, ft, line)
#define ADD_D(fd, fs, ft, line)       FOP_FMT3(FMT_D, fd, fs, ft, COP1_ADD, "add", line)
#define DIV_D(fd, fs, ft, line)       FOP_FMT3(FMT_D, fd, fs, ft, COP1_DIV, "div", line)
#define MOV_D(fd, fs, line)           FOP_FMT2(FMT_D, fd, fs, COP1_MOV, "mov", line)
#define MUL_D(fd, fs, ft, line)       FOP_FMT3(FMT_D, fd, fs, ft, COP1_MUL, "mul", line)
#define NEG_D(fd, fs, line)           FOP_FMT2(FMT_D, fd, fs, COP1_NEG, "neg", line)
#define SUB_D(fd, fs, ft, line)       FOP_FMT3(FMT_D, fd, fs, ft, COP1_SUB, "sub", line)

// S variants
#define C_EQ_S(fs, ft, line)          C_COND_FMT(COND_EQ, FMT_S, fs, ft, line)
#define C_LE_S(fs, ft, line)          C_COND_FMT(COND_LE, FMT_S, fs, ft, line)
#define C_LT_S(fs, ft, line)          C_COND_FMT(COND_LT, FMT_S, fs, ft, line)
#define ADD_S(fd, fs, ft, line)       FOP_FMT3(FMT_S, fd, fs, ft, COP1_ADD, "add", line)
#define DIV_S(fd, fs, ft, line)       FOP_FMT3(FMT_S, fd, fs, ft, COP1_DIV, "div", line)
#define MOV_S(fd, fs, line)           FOP_FMT2(FMT_S, fd, fs, COP1_MOV, "mov", line)
#define MUL_S(fd, fs, ft, line)       FOP_FMT3(FMT_S, fd, fs, ft, COP1_MUL, "mul", line)
#define NEG_S(fd, fs, line)           FOP_FMT2(FMT_S, fd, fs, COP1_NEG, "neg", line)
#define SUB_S(fd, fs, ft, line)       FOP_FMT3(FMT_S, fd, fs, ft, COP1_SUB, "sub", line)

#endif

#endif // __ACCMIPS_H__

