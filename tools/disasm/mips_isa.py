# Register IDs
MIPS_REG_R0 = MIPS_REG_F0 = 0
MIPS_REG_AT = MIPS_REG_F1 = 1
MIPS_REG_V0 = MIPS_REG_F2 = 2
MIPS_REG_V1 = MIPS_REG_F3 = 3
MIPS_REG_A0 = MIPS_REG_F4 = 4
MIPS_REG_A1 = MIPS_REG_F5 = 5
MIPS_REG_A2 = MIPS_REG_F6 = 6
MIPS_REG_A3 = MIPS_REG_F7 = 7
MIPS_REG_T0 = MIPS_REG_F8 = 8
MIPS_REG_T1 = MIPS_REG_F9 = 9
MIPS_REG_T2 = MIPS_REG_F10 = 10
MIPS_REG_T3 = MIPS_REG_F11 = 11
MIPS_REG_T4 = MIPS_REG_F12 = 12
MIPS_REG_T5 = MIPS_REG_F13 = 13
MIPS_REG_T6 = MIPS_REG_F14 = 14
MIPS_REG_T7 = MIPS_REG_F15 = 15
MIPS_REG_S0 = MIPS_REG_F16 = 16
MIPS_REG_S1 = MIPS_REG_F17 = 17
MIPS_REG_S2 = MIPS_REG_F18 = 18
MIPS_REG_S3 = MIPS_REG_F19 = 19
MIPS_REG_S4 = MIPS_REG_F20 = 20
MIPS_REG_S5 = MIPS_REG_F21 = 21
MIPS_REG_S6 = MIPS_REG_F22 = 22
MIPS_REG_S7 = MIPS_REG_F23 = 23
MIPS_REG_T8 = MIPS_REG_F24 = 24
MIPS_REG_T9 = MIPS_REG_F25 = 25
MIPS_REG_K0 = MIPS_REG_F26 = 26
MIPS_REG_K1 = MIPS_REG_F27 = 27
MIPS_REG_GP = MIPS_REG_F28 = 28
MIPS_REG_SP = MIPS_REG_F29 = 29
MIPS_REG_FP = MIPS_REG_F30 = 30
MIPS_REG_RA = MIPS_REG_F31 = 31

# Instruction Unique IDs
MIPS_INS_SLL       = 0
MIPS_INS_SRL       = 1
MIPS_INS_SRA       = 2
MIPS_INS_SLLV      = 3
MIPS_INS_SRLV      = 4
MIPS_INS_SRAV      = 5
MIPS_INS_JR        = 6
MIPS_INS_JALR      = 7
MIPS_INS_SYSCALL   = 8
MIPS_INS_BREAK     = 9
MIPS_INS_SYNC      = 10
MIPS_INS_MFHI      = 11
MIPS_INS_MTHI      = 12
MIPS_INS_MFLO      = 13
MIPS_INS_MTLO      = 14
MIPS_INS_DSLLV     = 15
MIPS_INS_DSRLV     = 16
MIPS_INS_DSRAV     = 17
MIPS_INS_MULT      = 18
MIPS_INS_MULTU     = 19
MIPS_INS_DIV       = 20
MIPS_INS_DIVU      = 21
MIPS_INS_DMULT     = 22
MIPS_INS_DMULTU    = 23
MIPS_INS_DDIV      = 24
MIPS_INS_DDIVU     = 25
MIPS_INS_ADD       = 26
MIPS_INS_ADDU      = 27
MIPS_INS_SUB       = 28
MIPS_INS_SUBU      = 29
MIPS_INS_AND       = 30
MIPS_INS_OR        = 31
MIPS_INS_XOR       = 32
MIPS_INS_NOR       = 33
MIPS_INS_SLT       = 34
MIPS_INS_SLTU      = 35
MIPS_INS_DADD      = 36
MIPS_INS_DADDU     = 37
MIPS_INS_DSUB      = 38
MIPS_INS_DSUBU     = 39
MIPS_INS_TGE       = 40
MIPS_INS_TGEU      = 41
MIPS_INS_TLT       = 42
MIPS_INS_TLTU      = 43
MIPS_INS_TEQ       = 44
MIPS_INS_TNE       = 45
MIPS_INS_DSLL      = 46
MIPS_INS_DSRL      = 47
MIPS_INS_DSRA      = 48
MIPS_INS_DSLL32    = 49
MIPS_INS_DSRL32    = 50
MIPS_INS_DSRA32    = 51
MIPS_INS_BLTZ      = 52
MIPS_INS_BGEZ      = 53
MIPS_INS_BLTZL     = 54
MIPS_INS_BGEZL     = 55
MIPS_INS_TGEI      = 56
MIPS_INS_TGEIU     = 57
MIPS_INS_TLTI      = 58
MIPS_INS_TLTIU     = 59
MIPS_INS_TEQI      = 60
MIPS_INS_TNEI      = 61
MIPS_INS_BLTZAL    = 62
MIPS_INS_BGEZAL    = 63
MIPS_INS_BLTZALL   = 64
MIPS_INS_BGEZALL   = 65
MIPS_INS_J         = 66
MIPS_INS_JAL       = 67
MIPS_INS_BEQ       = 68
MIPS_INS_BNE       = 69
MIPS_INS_BLEZ      = 70
MIPS_INS_BGTZ      = 71
MIPS_INS_ADDI      = 72
MIPS_INS_ADDIU     = 73
MIPS_INS_SLTI      = 74
MIPS_INS_SLTIU     = 75
MIPS_INS_ANDI      = 76
MIPS_INS_ORI       = 77
MIPS_INS_XORI      = 78
MIPS_INS_LUI       = 79
MIPS_INS_MFC0      = 80
MIPS_INS_MTC0      = 81
MIPS_INS_TLBR      = 82
MIPS_INS_TLBWI     = 83
MIPS_INS_TLBWR     = 84
MIPS_INS_TLBP      = 85
MIPS_INS_ERET      = 86
MIPS_INS_MFC1      = 87
MIPS_INS_DMFC1     = 88
MIPS_INS_CFC1      = 89
MIPS_INS_MTC1      = 90
MIPS_INS_DMTC1     = 91
MIPS_INS_CTC1      = 92
MIPS_INS_BC1F      = 93
MIPS_INS_BC1T      = 94
MIPS_INS_BC1FL     = 95
MIPS_INS_BC1TL     = 96
MIPS_INS_ADD_S     = 97
MIPS_INS_SUB_S     = 98
MIPS_INS_MUL_S     = 99
MIPS_INS_DIV_S     = 100
MIPS_INS_SQRT_S    = 101
MIPS_INS_ABS_S     = 102
MIPS_INS_MOV_S     = 103
MIPS_INS_NEG_S     = 104
MIPS_INS_ROUND_L_S = 105
MIPS_INS_TRUNC_L_S = 106
MIPS_INS_CEIL_L_S  = 107
MIPS_INS_FLOOR_L_S = 108
MIPS_INS_ROUND_W_S = 109
MIPS_INS_TRUNC_W_S = 110
MIPS_INS_CEIL_W_S  = 111
MIPS_INS_FLOOR_W_S = 112
MIPS_INS_CVT_D_S   = 113
MIPS_INS_CVT_W_S   = 114
MIPS_INS_CVT_L_S   = 115
MIPS_INS_C_F_S     = 116
MIPS_INS_C_UN_S    = 117
MIPS_INS_C_EQ_S    = 118
MIPS_INS_C_UEQ_S   = 119
MIPS_INS_C_OLT_S   = 120
MIPS_INS_C_ULT_S   = 121
MIPS_INS_C_OLE_S   = 122
MIPS_INS_C_ULE_S   = 123
MIPS_INS_C_SF_S    = 124
MIPS_INS_C_NGLE_S  = 125
MIPS_INS_C_SEQ_S   = 126
MIPS_INS_C_NGL_S   = 127
MIPS_INS_C_LT_S    = 128
MIPS_INS_C_NGE_S   = 129
MIPS_INS_C_LE_S    = 130
MIPS_INS_C_NGT_S   = 131
MIPS_INS_ADD_D     = 132
MIPS_INS_SUB_D     = 133
MIPS_INS_MUL_D     = 134
MIPS_INS_DIV_D     = 135
MIPS_INS_SQRT_D    = 136
MIPS_INS_ABS_D     = 137
MIPS_INS_MOV_D     = 138
MIPS_INS_NEG_D     = 139
MIPS_INS_ROUND_L_D = 140
MIPS_INS_TRUNC_L_D = 141
MIPS_INS_CEIL_L_D  = 142
MIPS_INS_FLOOR_L_D = 143
MIPS_INS_ROUND_W_D = 144
MIPS_INS_TRUNC_W_D = 145
MIPS_INS_CEIL_W_D  = 146
MIPS_INS_FLOOR_W_D = 147
MIPS_INS_CVT_S_D   = 148
MIPS_INS_CVT_W_D   = 149
MIPS_INS_CVT_L_D   = 150
MIPS_INS_C_F_D     = 151
MIPS_INS_C_UN_D    = 152
MIPS_INS_C_EQ_D    = 153
MIPS_INS_C_UEQ_D   = 154
MIPS_INS_C_OLT_D   = 155
MIPS_INS_C_ULT_D   = 156
MIPS_INS_C_OLE_D   = 157
MIPS_INS_C_ULE_D   = 158
MIPS_INS_C_SF_D    = 159
MIPS_INS_C_NGLE_D  = 160
MIPS_INS_C_SEQ_D   = 161
MIPS_INS_C_NGL_D   = 162
MIPS_INS_C_LT_D    = 163
MIPS_INS_C_NGE_D   = 164
MIPS_INS_C_LE_D    = 165
MIPS_INS_C_NGT_D   = 166
MIPS_INS_CVT_S_W   = 167
MIPS_INS_CVT_D_W   = 168
MIPS_INS_CVT_S_L   = 169
MIPS_INS_CVT_D_L   = 170
MIPS_INS_BEQL      = 171
MIPS_INS_BNEL      = 172
MIPS_INS_BLEZL     = 173
MIPS_INS_BGTZL     = 174
MIPS_INS_DADDI     = 175
MIPS_INS_DADDIU    = 176
MIPS_INS_LDL       = 177
MIPS_INS_LDR       = 178
MIPS_INS_LB        = 179
MIPS_INS_LH        = 180
MIPS_INS_LWL       = 181
MIPS_INS_LW        = 182
MIPS_INS_LBU       = 183
MIPS_INS_LHU       = 184
MIPS_INS_LWR       = 185
MIPS_INS_LWU       = 186
MIPS_INS_SB        = 187
MIPS_INS_SH        = 188
MIPS_INS_SWL       = 189
MIPS_INS_SW        = 190
MIPS_INS_SDL       = 191
MIPS_INS_SDR       = 192
MIPS_INS_SWR       = 193
MIPS_INS_CACHE     = 194
MIPS_INS_LL        = 195
MIPS_INS_LWC1      = 196
MIPS_INS_LLD       = 197
MIPS_INS_LDC1      = 198
#MIPS_INS_INVALID   = 199
MIPS_INS_LD        = 200
MIPS_INS_SC        = 201
MIPS_INS_SWC1      = 202
MIPS_INS_SCD       = 203
MIPS_INS_SDC1      = 204
MIPS_INS_SD        = 206

# Pseudo-Instruction Unique IDs
MIPS_INS_BEQZ = 207
MIPS_INS_BNEZ = 208
MIPS_INS_B    = 209
MIPS_INS_NOP  = 210
MIPS_INS_MOVE = 211
MIPS_INS_NEGU = 212
MIPS_INS_NOT  = 213

# Invalid Instruction Unique ID
MIPS_INS_INVALID   = -1

# Op IDs
# MIPS_OP_RS  = 0
# MIPS_OP_RT  = 0
# MIPS_OP_RD  = 0
# MIPS_OP_IMM = 0

# Register Names

mips_gpr_names = [
    "$zero",
    "$at",
    "$v0", "$v1",
    "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9",
    "$k0", "$k1",
    "$gp",
    "$sp",
    "$fp",
    "$ra",
]

mips_cop0_names = [
    "Index"     , "Random"    , "EntryLo0"  , "EntryLo1"  ,
    "Context"   , "PageMask"  , "Wired"     , "Reserved07",
    "BadVaddr"  , "Count"     , "EntryHi"   , "Compare"   ,
    "Status"    , "Cause"     , "EPC"       , "PRevID"    ,
    "Config"    , "LLAddr"    , "WatchLo"   , "WatchHi"   ,
    "XContext"  , "Reserved21", "Reserved22", "Reserved23",
    "Reserved24", "Reserved25", "PErr"      , "CacheErr"  ,
    "TagLo"     , "TagHi"     , "ErrorEPC"  , "Reserved31",
]

numeric_fpr_names = [
    "$f0", "$f1", "$f2", "$f3",
    "$f4", "$f5", "$f6", "$f7", "$f8", "$f9", "$f10", "$f11",
    "$f12", "$f13", "$f14", "$f15",
    "$f16", "$f17", "$f18", "$f19",
    "$f20", "$f21", "$f22", "$f23", "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30",
    "$31", # Floating-point control/status register
]

o32_fpr_names = [
    "$fv0", "$fv0f", "$fv1", "$fv1f",
    "$ft0", "$ft0f", "$ft1", "$ft1f", "$ft2", "$ft2f", "$ft3", "$ft3f",
    "$fa0", "$fa0f", "$fa1", "$fa1f",
    "$ft4", "$ft4f", "$ft5", "$ft5f",
    "$fs0", "$fs0f", "$fs1", "$fs1f", "$fs2", "$fs2f", "$fs3", "$fs3f", "$fs4", "$fs4f", "$fs5",
    "$31", # Floating-point control/status register
]

mips_fpr_names = numeric_fpr_names

# Instruction field fetching

def sign_extend_16(value):
    return (value & 0x7FFF) - (value & 0x8000)

def mask_shift(v, s, w):
    return (v >> s) & ((1 << w) - 1)

mips_get_field    = lambda raw,vaddr : mask_shift(raw, 26,  6)
mips_get_special  = lambda raw,vaddr : mask_shift(raw,  0,  6)
mips_get_cop0     = lambda raw,vaddr : mask_shift(raw, 21,  5)
mips_get_cop1     = lambda raw,vaddr : mask_shift(raw, 21,  5)
mips_get_regimm   = lambda raw,vaddr : mask_shift(raw, 16,  5)
mips_get_tlb      = lambda raw,vaddr : mask_shift(raw,  0,  5)
mips_get_function = lambda raw,vaddr : mask_shift(raw,  0,  6)

mips_get_cond    = lambda raw,vaddr : mask_shift(raw,  0,  4)
mips_get_fc      = lambda raw,vaddr : mask_shift(raw,  2,  2)
mips_get_fd      = lambda raw,vaddr : mask_shift(raw,  6,  5)
mips_get_fs      = lambda raw,vaddr : mask_shift(raw, 11,  5)
mips_get_ft      = lambda raw,vaddr : mask_shift(raw, 16,  5)
mips_get_fmt     = lambda raw,vaddr : mask_shift(raw, 21,  5)
mips_get_ndtf    = lambda raw,vaddr : mask_shift(raw, 16,  2)

mips_get_target  = lambda raw,vaddr : (0x80000000 | (mask_shift(raw, 0, 26) << 2))
mips_get_offset  = lambda raw,vaddr : vaddr + 4 + sign_extend_16(mask_shift(raw, 0, 16)) * 4
mips_get_imm     = lambda raw,vaddr : mask_shift(raw,  0, 16)

mips_get_base    = lambda raw,vaddr : mask_shift(raw, 21,  5)

mips_get_cd      = lambda raw,vaddr : mask_shift(raw, 11,  5)

mips_get_code    = lambda raw,vaddr : (mask_shift(raw,  6, 20) << 6) >> 16
mips_get_op      = lambda raw,vaddr : mask_shift(raw, 16,  5)

mips_get_sa      = lambda raw,vaddr : mask_shift(raw,  6,  5)

mips_get_rd      = lambda raw,vaddr : mask_shift(raw, 11,  5)
mips_get_rs      = lambda raw,vaddr : mask_shift(raw, 21,  5)
mips_get_rt      = lambda raw,vaddr : mask_shift(raw, 16,  5)

# Formatting

class MipsInsn:

    def __init__(self, raw, vaddr, values):
        self.raw = raw
        self.vaddr = vaddr

        if values is None:
            values = MIPS_INS_INVALID, f"/* Invalid Instruction: 0x{raw:08X} */", ()

        self.id, self.mnemonic, self.fields = values

        self.code = self.sa = self.op = self.cd = self.rd = self.rs = self.rt = self.fd = self.fs = self.ft = self.imm = self.offset = self.base = self.target = None

        for field in self.fields:
            self.value_forname(field)

        self.op_str = self.format_insn()

        if self.id == MIPS_INS_SLL and self.rd == MIPS_REG_R0 and self.rt == MIPS_REG_R0 and self.sa == 0:
            self.id = MIPS_INS_NOP
            self.mnemonic = "nop"
            self.fields = ()
        elif self.id == MIPS_INS_BEQ and self.rs == MIPS_REG_R0 and self.rt == MIPS_REG_R0:
            self.id = MIPS_INS_B
            self.mnemonic = "b"
            self.fields = ("offset",)
        elif self.id == MIPS_INS_OR and self.rt == MIPS_REG_R0:
            self.id = MIPS_INS_MOVE
            self.mnemonic = "move"
            self.fields = ("rd","rs")
        elif self.id == MIPS_INS_BEQ and self.rt == MIPS_REG_R0:
            self.id = MIPS_INS_BEQZ
            self.mnemonic = "beqz"
            self.fields = ("rs","offset")
        elif self.id == MIPS_INS_BNE and self.rt == MIPS_REG_R0:
            self.id = MIPS_INS_BNEZ
            self.mnemonic = "bnez"
            self.fields = ("rs","offset")
        elif self.id == MIPS_INS_SUBU and self.rs == MIPS_REG_R0:
            self.id = MIPS_INS_NEGU
            self.mnemonic = "negu"
            self.fields = ("rd","rt")
        elif self.id == MIPS_INS_NOR and self.rt == MIPS_REG_R0:
            self.id = MIPS_INS_NOT
            self.mnemonic = "not"
            self.fields = ("rd","rs")

        self.op_str = self.format_insn()

    def value_forname(self, name):
        field_setters = {
            'code'   : self.set_code,
            'sa'     : self.set_sa,
            'op'     : self.set_op,
            'cd'     : self.set_cd,
            'rd'     : self.set_rd,
            'rs'     : self.set_rs,
            'rt'     : self.set_rt,
            'fd'     : self.set_fd,
            'fs'     : self.set_fs,
            'ft'     : self.set_ft,
            'imm'    : self.set_imm,
            'offset' : self.set_offset,
            'base'   : self.set_base,
            'offset(base)' : self.set_offset_base,
            'target' : self.set_target,
        }

        return field_setters[name]()

    def format_field(self, field):
        def format_hex(v, signed, zeros, no_zero):
            if abs(v) < 10:
                if v == 0 and no_zero:
                    return ""
                return f"{v}"
            elif not signed:
                return f"0x{v:{f'0{zeros}' if zeros > 0 else ''}x}"
            else:
                return f"{v:#x}"

        format_handlers = {
            'code' : (lambda insn : f'{insn.code}' if insn.code != 0 else ''),
            'cd' : (lambda insn : mips_cop0_names[insn.cd]),
            'rd' : (lambda insn : mips_gpr_names[insn.rd]),
            'rs' : (lambda insn : mips_gpr_names[insn.rs]),
            'rt' : (lambda insn : mips_gpr_names[insn.rt]),
            'fd' : (lambda insn : mips_fpr_names[insn.fd]),
            'fs' : (lambda insn : mips_fpr_names[insn.fs]),
            'ft' : (lambda insn : mips_fpr_names[insn.ft]),
            'sa' : (lambda insn : format_hex(insn.sa, True, 0, False)),
            'op' : (lambda insn : format_hex(insn.op, False, 0, False)),
            'imm' : (lambda insn : format_hex(insn.imm, True, 0, False)),
            'offset(base)' : (lambda insn : f'{format_hex(insn.imm, True, 0, True)}({mips_gpr_names[insn.base]})'),
            'offset'       : (lambda insn : f'{format_hex(insn.offset, True, 0, False)}'),
            'target'       : (lambda insn : f'{format_hex(insn.target, False, 0, False)}')
        }

        return format_handlers[field](self)

    def format_insn(self):
        return ", ".join([self.format_field(field) for field in self.fields])

    def __str__(self):
        return f"{self.mnemonic:12}{self.op_str}"

    def set_code(self):
        self.code = mips_get_code(self.raw, self.vaddr)
        return self.code

    def set_sa(self):
        self.sa = mips_get_sa(self.raw, self.vaddr)
        return self.sa

    def set_op(self):
        self.op = mips_get_op(self.raw, self.vaddr)
        return self.op

    def set_cd(self):
        self.cd = mips_get_cd(self.raw, self.vaddr)
        return self.cd

    def set_rd(self):
        self.rd = mips_get_rd(self.raw, self.vaddr)
        return self.rd

    def set_rs(self):
        self.rs = mips_get_rs(self.raw, self.vaddr)
        return self.rs

    def set_rt(self):
        self.rt = mips_get_rt(self.raw, self.vaddr)
        return self.rt

    def set_fd(self):
        self.fd = mips_get_fd(self.raw, self.vaddr)
        return self.fd

    def set_fs(self):
        self.fs = mips_get_fs(self.raw, self.vaddr)
        return self.fs

    def set_ft(self):
        self.ft = mips_get_ft(self.raw, self.vaddr)
        return self.ft

    def set_imm(self):
        do_sign_extend = [  MIPS_INS_ADDIU, MIPS_INS_SLTI, MIPS_INS_ADDI, MIPS_INS_DADDIU, 
                            MIPS_INS_LB, MIPS_INS_LBU, 
                            MIPS_INS_LH, MIPS_INS_LHU, 
                            MIPS_INS_LW, MIPS_INS_LWL, MIPS_INS_LWR, MIPS_INS_LWU, 
                            MIPS_INS_LWC1, 
                            MIPS_INS_LD, MIPS_INS_LDL, MIPS_INS_LDR, 
                            MIPS_INS_LDC1, 
                            MIPS_INS_LL, MIPS_INS_LLD, 
                            MIPS_INS_SB, 
                            MIPS_INS_SH, 
                            MIPS_INS_SW, MIPS_INS_SWL, MIPS_INS_SWR, 
                            MIPS_INS_SWC1, 
                            MIPS_INS_SD, MIPS_INS_SDL, MIPS_INS_SDR, 
                            MIPS_INS_SDC1, 
                            MIPS_INS_SC, MIPS_INS_SCD,
                        ]

        self.imm = mips_get_imm(self.raw, self.vaddr)
        if self.id in do_sign_extend: # sign extended immediates
            self.imm = sign_extend_16(self.imm)
        return self.imm

    def set_offset(self):
        self.offset = mips_get_offset(self.raw, self.vaddr)
        return self.offset

    def set_base(self):
        self.base = mips_get_base(self.raw, self.vaddr)
        return self.base

    def set_offset_base(self):
        self.set_imm()
        self.set_base()
        return self.imm, self.base

    def set_target(self):
        self.target = mips_get_target(self.raw, self.vaddr)
        return self.target

def fetch_insn(raw, vaddr, insn_set, func):
    insn = insn_set.get(func(raw, vaddr), None) # default none for invalid instruction encoding

    if insn is not None and type(insn[1]) == dict: # extra decoding required
        insn = fetch_insn(raw, vaddr, insn[1], insn[0])
    return insn

def decode_insn(raw, vaddr):
    return MipsInsn(raw, vaddr, fetch_insn(raw, vaddr, mips_insns, mips_get_field))

mips_insns = {
    0b000000: (mips_get_special, {
        0b000000: (MIPS_INS_SLL,     "sll",     ("rd","rt","sa")),
        0b000010: (MIPS_INS_SRL,     "srl",     ("rd","rt","sa")),
        0b000011: (MIPS_INS_SRA,     "sra",     ("rd","rt","sa")),
        0b000100: (MIPS_INS_SLLV,    "sllv",    ("rd","rt","rs")),
        0b000110: (MIPS_INS_SRLV,    "srlv",    ("rd","rt","rs")),
        0b000111: (MIPS_INS_SRAV,    "srav",    ("rd","rt","rs")),
        0b001000: (MIPS_INS_JR,      "jr",      ("rs",         )),
        0b001001: (MIPS_INS_JALR,    "jalr",    ("rs",         )), # technically also rd but it's always $ra
        0b001100: (MIPS_INS_SYSCALL, "syscall", (              )),
        0b001101: (MIPS_INS_BREAK,   "break",   ("code",       )),
        0b001111: (MIPS_INS_SYNC,    "sync",    (              )),
        0b010000: (MIPS_INS_MFHI,    "mfhi",    ("rd",         )),
        0b010001: (MIPS_INS_MTHI,    "mthi",    ("rs",         )),
        0b010010: (MIPS_INS_MFLO,    "mflo",    ("rd",         )),
        0b010011: (MIPS_INS_MTLO,    "mtlo",    ("rs",         )),
        0b010100: (MIPS_INS_DSLLV,   "dsllv",   ("rd","rt","rs")),
        0b010110: (MIPS_INS_DSRLV,   "dsrlv",   ("rd","rt","rs")),
        0b010111: (MIPS_INS_DSRAV,   "dsrav",   ("rd","rt","rs")),
        0b011000: (MIPS_INS_MULT,    "mult",    ("rs","rt"     )),
        0b011001: (MIPS_INS_MULTU,   "multu",   ("rs","rt"     )),
        0b011010: (MIPS_INS_DIV,     "div",     ("rd","rs","rt")), # for some reason gas hates div instructions 
        0b011011: (MIPS_INS_DIVU,    "divu",    ("rd","rs","rt")), #    with the correct number of operands
        0b011100: (MIPS_INS_DMULT,   "dmult",   ("rs","rt"     )),
        0b011101: (MIPS_INS_DMULTU,  "dmultu",  ("rs","rt"     )),
        0b011110: (MIPS_INS_DDIV,    "ddiv",    ("rd","rs","rt")),
        0b011111: (MIPS_INS_DDIVU,   "ddivu",   ("rd","rs","rt")),
        0b100000: (MIPS_INS_ADD,     "add",     ("rd","rs","rt")),
        0b100001: (MIPS_INS_ADDU,    "addu",    ("rd","rs","rt")),
        0b100010: (MIPS_INS_SUB,     "sub",     ("rd","rs","rt")),
        0b100011: (MIPS_INS_SUBU,    "subu",    ("rd","rs","rt")),
        0b100100: (MIPS_INS_AND,     "and",     ("rd","rs","rt")),
        0b100101: (MIPS_INS_OR,      "or",      ("rd","rs","rt")),
        0b100110: (MIPS_INS_XOR,     "xor",     ("rd","rs","rt")),
        0b100111: (MIPS_INS_NOR,     "nor",     ("rd","rs","rt")),
        0b101010: (MIPS_INS_SLT,     "slt",     ("rd","rs","rt")),
        0b101011: (MIPS_INS_SLTU,    "sltu",    ("rd","rs","rt")),
        0b101100: (MIPS_INS_DADD,    "dadd",    ("rd","rs","rt")),
        0b101101: (MIPS_INS_DADDU,   "daddu",   ("rd","rs","rt")),
        0b101110: (MIPS_INS_DSUB,    "dsub",    ("rd","rs","rt")),
        0b101111: (MIPS_INS_DSUBU,   "dsubu",   ("rd","rs","rt")),
        0b110000: (MIPS_INS_TGE,     "tge",     ("rs","rt"     )),
        0b110001: (MIPS_INS_TGEU,    "tgeu",    ("rs","rt"     )),
        0b110010: (MIPS_INS_TLT,     "tlt",     ("rs","rt"     )),
        0b110011: (MIPS_INS_TLTU,    "tltu",    ("rs","rt"     )),
        0b110100: (MIPS_INS_TEQ,     "teq",     ("rs","rt"     )),
        0b110110: (MIPS_INS_TNE,     "tne",     ("rs","rt"     )),
        0b111000: (MIPS_INS_DSLL,    "dsll",    ("rd","rt","sa")),
        0b111010: (MIPS_INS_DSRL,    "dsrl",    ("rd","rt","sa")),
        0b111011: (MIPS_INS_DSRA,    "dsra",    ("rd","rt","sa")),
        0b111100: (MIPS_INS_DSLL32,  "dsll32",  ("rd","rt","sa")),
        0b111110: (MIPS_INS_DSRL32,  "dsrl32",  ("rd","rt","sa")),
        0b111111: (MIPS_INS_DSRA32,  "dsra32",  ("rd","rt","sa")),
    }),
    0b000001: (mips_get_regimm, {
        0b00000: (MIPS_INS_BLTZ,    "bltz",    ("rs","offset")),
        0b00001: (MIPS_INS_BGEZ,    "bgez",    ("rs","offset")),
        0b00010: (MIPS_INS_BLTZL,   "bltzl",   ("rs","offset")),
        0b00011: (MIPS_INS_BGEZL,   "bgezl",   ("rs","offset")),
        0b01000: (MIPS_INS_TGEI,    "tgei",    ("rs","imm"   )),
        0b01001: (MIPS_INS_TGEIU,   "tgeiu",   ("rs","imm"   )),
        0b01010: (MIPS_INS_TLTI,    "tlti",    ("rs","imm"   )),
        0b01011: (MIPS_INS_TLTIU,   "tltiu",   ("rs","imm"   )),
        0b01100: (MIPS_INS_TEQI,    "teqi",    ("rs","imm"   )),
        0b01110: (MIPS_INS_TNEI,    "tnei",    ("rs","imm"   )),
        0b10000: (MIPS_INS_BLTZAL,  "bltzal",  ("rs","offset")),
        0b10001: (MIPS_INS_BGEZAL,  "bgezal",  ("rs","offset")),
        0b10010: (MIPS_INS_BLTZALL, "bltzall", ("rs","offset")),
        0b10011: (MIPS_INS_BGEZALL, "bgezall", ("rs","offset")),
    }),
    0b000010: (MIPS_INS_J,     "j",     ("target",         )),
    0b000011: (MIPS_INS_JAL,   "jal",   ("target",         )),
    0b000100: (MIPS_INS_BEQ,   "beq",   ("rs","rt","offset")),
    0b000101: (MIPS_INS_BNE,   "bne",   ("rs","rt","offset")),
    0b000110: (MIPS_INS_BLEZ,  "blez",  ("rs","offset"     )),
    0b000111: (MIPS_INS_BGTZ,  "bgtz",  ("rs","offset"     )),
    0b001000: (MIPS_INS_ADDI,  "addi",  ("rt","rs","imm"   )),
    0b001001: (MIPS_INS_ADDIU, "addiu", ("rt","rs","imm"   )),
    0b001010: (MIPS_INS_SLTI,  "slti",  ("rt","rs","imm"   )),
    0b001011: (MIPS_INS_SLTIU, "sltiu", ("rt","rs","imm"   )),
    0b001100: (MIPS_INS_ANDI,  "andi",  ("rt","rs","imm"   )),
    0b001101: (MIPS_INS_ORI,   "ori",   ("rt","rs","imm"   )),
    0b001110: (MIPS_INS_XORI,  "xori",  ("rt","rs","imm"   )),
    0b001111: (MIPS_INS_LUI,   "lui",   ("rt","imm"        )),
    0b010000: (mips_get_cop0, {
        0b00000: (MIPS_INS_MFC0, "mfc0", ("rt","cd")),
        0b00100: (MIPS_INS_MTC0, "mtc0", ("rt","cd")),
        0b10000: (mips_get_tlb, {
            0b000001: (MIPS_INS_TLBR,  "tlbr",  ()),
            0b000010: (MIPS_INS_TLBWI, "tlbwi", ()),
            0b000110: (MIPS_INS_TLBWR, "tlbwr", ()),
            0b001000: (MIPS_INS_TLBP,  "tlbp",  ()),
            0b011000: (MIPS_INS_ERET,  "eret",  ()),
        }),
    }),
    0b010001: (mips_get_cop1, {
        0b00000: (MIPS_INS_MFC1,  "mfc1",  ("rt","fs")),
        0b00001: (MIPS_INS_DMFC1, "dmfc1", ("rt","fs")),
        0b00010: (MIPS_INS_CFC1,  "cfc1",  ("rt","fs")),
        0b00100: (MIPS_INS_MTC1,  "mtc1",  ("rt","fs")),
        0b00101: (MIPS_INS_DMTC1, "dmtc1", ("rt","fs")),
        0b00110: (MIPS_INS_CTC1,  "ctc1",  ("rt","fs")),
        0b01000: (mips_get_ndtf, {
            0b00: (MIPS_INS_BC1F,  "bc1f",  ("offset",)),
            0b01: (MIPS_INS_BC1T,  "bc1t",  ("offset",)),
            0b10: (MIPS_INS_BC1FL, "bc1fl", ("offset",)),
            0b11: (MIPS_INS_BC1TL, "bc1tl", ("offset",)),
        }),
        0b010000: (mips_get_function, {
            0b000000: (MIPS_INS_ADD_S,     "add.s",     ("fd","fs","ft")),
            0b000001: (MIPS_INS_SUB_S,     "sub.s",     ("fd","fs","ft")),
            0b000010: (MIPS_INS_MUL_S,     "mul.s",     ("fd","fs","ft")),
            0b000011: (MIPS_INS_DIV_S,     "div.s",     ("fd","fs","ft")),
            0b000100: (MIPS_INS_SQRT_S,    "sqrt.s",    ("fd","fs"     )),
            0b000101: (MIPS_INS_ABS_S,     "abs.s",     ("fd","fs"     )),
            0b000110: (MIPS_INS_MOV_S,     "mov.s",     ("fd","fs"     )),
            0b000111: (MIPS_INS_NEG_S,     "neg.s",     ("fd","fs"     )),
            0b001000: (MIPS_INS_ROUND_L_S, "round.l.s", ("fd","fs"     )),
            0b001001: (MIPS_INS_TRUNC_L_S, "trunc.l.s", ("fd","fs"     )),
            0b001010: (MIPS_INS_CEIL_L_S,  "ceil.l.s",  ("fd","fs"     )),
            0b001011: (MIPS_INS_FLOOR_L_S, "floor.l.s", ("fd","fs"     )),
            0b001100: (MIPS_INS_ROUND_W_S, "round.w.s", ("fd","fs"     )),
            0b001101: (MIPS_INS_TRUNC_W_S, "trunc.w.s", ("fd","fs"     )),
            0b001110: (MIPS_INS_CEIL_W_S,  "ceil.w.s",  ("fd","fs"     )),
            0b001111: (MIPS_INS_FLOOR_W_S, "floor.w.s", ("fd","fs"     )),
            0b100001: (MIPS_INS_CVT_D_S,   "cvt.d.s",   ("fd","fs"     )),
            0b100100: (MIPS_INS_CVT_W_S,   "cvt.w.s",   ("fd","fs"     )),
            0b100101: (MIPS_INS_CVT_L_S,   "cvt.l.s",   ("fd","fs"     )),
            0b110000: (MIPS_INS_C_F_S,     "c.f.s",     ("fs","ft"     )),
            0b110001: (MIPS_INS_C_UN_S,    "c.un.s",    ("fs","ft"     )),
            0b110010: (MIPS_INS_C_EQ_S,    "c.eq.s",    ("fs","ft"     )),
            0b110011: (MIPS_INS_C_UEQ_S,   "c.ueq.s",   ("fs","ft"     )),
            0b110100: (MIPS_INS_C_OLT_S,   "c.olt.s",   ("fs","ft"     )),
            0b110101: (MIPS_INS_C_ULT_S,   "c.ult.s",   ("fs","ft"     )),
            0b110110: (MIPS_INS_C_OLE_S,   "c.ole.s",   ("fs","ft"     )),
            0b110111: (MIPS_INS_C_ULE_S,   "c.ule.s",   ("fs","ft"     )),
            0b111000: (MIPS_INS_C_SF_S,    "c.sf.s",    ("fs","ft"     )),
            0b111001: (MIPS_INS_C_NGLE_S,  "c.ngle.s",  ("fs","ft"     )),
            0b111010: (MIPS_INS_C_SEQ_S,   "c.seq.s",   ("fs","ft"     )),
            0b111011: (MIPS_INS_C_NGL_S,   "c.ngl.s",   ("fs","ft"     )),
            0b111100: (MIPS_INS_C_LT_S,    "c.lt.s",    ("fs","ft"     )),
            0b111101: (MIPS_INS_C_NGE_S,   "c.nge.s",   ("fs","ft"     )),
            0b111110: (MIPS_INS_C_LE_S,    "c.le.s",    ("fs","ft"     )),
            0b111111: (MIPS_INS_C_NGT_S,   "c.ngt.s",   ("fs","ft"     )),
        }),
        0b010001: (mips_get_function, {
            0b000000: (MIPS_INS_ADD_D,     "add.d",     ("fd","fs","ft")),
            0b000001: (MIPS_INS_SUB_D,     "sub.d",     ("fd","fs","ft")),
            0b000010: (MIPS_INS_MUL_D,     "mul.d",     ("fd","fs","ft")),
            0b000011: (MIPS_INS_DIV_D,     "div.d",     ("fd","fs","ft")),
            0b000100: (MIPS_INS_SQRT_D,    "sqrt.d",    ("fd","fs"     )),
            0b000101: (MIPS_INS_ABS_D,     "abs.d",     ("fd","fs"     )),
            0b000110: (MIPS_INS_MOV_D,     "mov.d",     ("fd","fs"     )),
            0b000111: (MIPS_INS_NEG_D,     "neg.d",     ("fd","fs"     )),
            0b001000: (MIPS_INS_ROUND_L_D, "round.l.d", ("fd","fs"     )),
            0b001001: (MIPS_INS_TRUNC_L_D, "trunc.l.d", ("fd","fs"     )),
            0b001010: (MIPS_INS_CEIL_L_D,  "ceil.l.d",  ("fd","fs"     )),
            0b001011: (MIPS_INS_FLOOR_L_D, "floor.l.d", ("fd","fs"     )),
            0b001100: (MIPS_INS_ROUND_W_D, "round.w.d", ("fd","fs"     )),
            0b001101: (MIPS_INS_TRUNC_W_D, "trunc.w.d", ("fd","fs"     )),
            0b001110: (MIPS_INS_CEIL_W_D,  "ceil.w.d",  ("fd","fs"     )),
            0b001111: (MIPS_INS_FLOOR_W_D, "floor.w.d", ("fd","fs"     )),
            0b100000: (MIPS_INS_CVT_S_D,   "cvt.s.d",   ("fd","fs"     )),
            0b100100: (MIPS_INS_CVT_W_D,   "cvt.w.d",   ("fd","fs"     )),
            0b100101: (MIPS_INS_CVT_L_D,   "cvt.l.d",   ("fd","fs"     )),
            0b110000: (MIPS_INS_C_F_D,     "c.f.d",     ("fs","ft"     )),
            0b110001: (MIPS_INS_C_UN_D,    "c.un.d",    ("fs","ft"     )),
            0b110010: (MIPS_INS_C_EQ_D,    "c.eq.d",    ("fs","ft"     )),
            0b110011: (MIPS_INS_C_UEQ_D,   "c.ueq.d",   ("fs","ft"     )),
            0b110100: (MIPS_INS_C_OLT_D,   "c.olt.d",   ("fs","ft"     )),
            0b110101: (MIPS_INS_C_ULT_D,   "c.ult.d",   ("fs","ft"     )),
            0b110110: (MIPS_INS_C_OLE_D,   "c.ole.d",   ("fs","ft"     )),
            0b110111: (MIPS_INS_C_ULE_D,   "c.ule.d",   ("fs","ft"     )),
            0b111000: (MIPS_INS_C_SF_D,    "c.sf.d",    ("fs","ft"     )),
            0b111001: (MIPS_INS_C_NGLE_D,  "c.ngle.d",  ("fs","ft"     )),
            0b111010: (MIPS_INS_C_SEQ_D,   "c.seq.d",   ("fs","ft"     )),
            0b111011: (MIPS_INS_C_NGL_D,   "c.ngl.d",   ("fs","ft"     )),
            0b111100: (MIPS_INS_C_LT_D,    "c.lt.d",    ("fs","ft"     )),
            0b111101: (MIPS_INS_C_NGE_D,   "c.nge.d",   ("fs","ft"     )),
            0b111110: (MIPS_INS_C_LE_D,    "c.le.d",    ("fs","ft"     )),
            0b111111: (MIPS_INS_C_NGT_D,   "c.ngt.d",   ("fs","ft"     )),
        }),
        0b010100: (mips_get_function, {
            0b100000: (MIPS_INS_CVT_S_W, "cvt.s.w", ("fd","fs")),
            0b100001: (MIPS_INS_CVT_D_W, "cvt.d.w", ("fd","fs")),
        }),
        0b010101: (mips_get_function, {
            0b100000: (MIPS_INS_CVT_S_L, "cvt.s.l", ("fd","fs")),
            0b100001: (MIPS_INS_CVT_D_L, "cvt.d.l", ("fd","fs")),
        }),
    }),
    0b010100: (MIPS_INS_BEQL,   "beql",   ("rs","rt","offset" )),
    0b010101: (MIPS_INS_BNEL,   "bnel",   ("rs","rt","offset" )),
    0b010110: (MIPS_INS_BLEZL,  "blezl",  ("rs","offset"      )),
    0b010111: (MIPS_INS_BGTZL,  "bgtzl",  ("rs","offset"      )),
    0b011000: (MIPS_INS_DADDI,  "daddi",  ("rt","rs","imm"    )),
    0b011001: (MIPS_INS_DADDIU, "daddiu", ("rt","rs","imm"    )),
    0b011010: (MIPS_INS_LDL,    "ldl",    ("rt","offset(base)")),
    0b011011: (MIPS_INS_LDR,    "ldr",    ("rt","offset(base)")),
    0b100000: (MIPS_INS_LB,     "lb",     ("rt","offset(base)")),
    0b100001: (MIPS_INS_LH,     "lh",     ("rt","offset(base)")),
    0b100010: (MIPS_INS_LWL,    "lwl",    ("rt","offset(base)")),
    0b100011: (MIPS_INS_LW,     "lw",     ("rt","offset(base)")),
    0b100100: (MIPS_INS_LBU,    "lbu",    ("rt","offset(base)")),
    0b100101: (MIPS_INS_LHU,    "lhu",    ("rt","offset(base)")),
    0b100110: (MIPS_INS_LWR,    "lwr",    ("rt","offset(base)")),
    0b100111: (MIPS_INS_LWU,    "lwu",    ("rt","offset(base)")),
    0b101000: (MIPS_INS_SB,     "sb",     ("rt","offset(base)")),
    0b101001: (MIPS_INS_SH,     "sh",     ("rt","offset(base)")),
    0b101010: (MIPS_INS_SWL,    "swl",    ("rt","offset(base)")),
    0b101011: (MIPS_INS_SW,     "sw",     ("rt","offset(base)")),
    0b101100: (MIPS_INS_SDL,    "sdl",    ("rt","offset(base)")),
    0b101101: (MIPS_INS_SDR,    "sdr",    ("rt","offset(base)")),
    0b101110: (MIPS_INS_SWR,    "swr",    ("rt","offset(base)")),
    0b101111: (MIPS_INS_CACHE,  "cache",  ("op","offset(base)")),
    0b110000: (MIPS_INS_LL,     "ll",     ("rt","offset(base)")),
    0b110001: (MIPS_INS_LWC1,   "lwc1",   ("ft","offset(base)")),
    0b110100: (MIPS_INS_LLD,    "lld",    ("rt","offset(base)")),
    0b110101: (MIPS_INS_LDC1,   "ldc1",   ("ft","offset(base)")),
    # ldc2
    0b110111: (MIPS_INS_LD,     "ld",     ("rt","offset(base)")),
    0b111000: (MIPS_INS_SC,     "sc",     ("rt","offset(base)")),
    0b111001: (MIPS_INS_SWC1,   "swc1",   ("ft","offset(base)")),
    0b111100: (MIPS_INS_SCD,    "scd",    ("rt","offset(base)")),
    0b111101: (MIPS_INS_SDC1,   "sdc1",   ("ft","offset(base)")),
    # sdc2
    0b111111: (MIPS_INS_SD,     "sd",     ("rt","offset(base)")),
}
