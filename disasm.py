import os
import struct

SPLIT_FILES = True
GENERATE_HEADERS = True

loadHighRefs = {}
loadLowRefs = {}

from objects import *
from functions import *
from variables import *
from files import *

regs = {
    0:"$zero", 1:"$at", 2:"$v0", 3:"$v1", 4:"$a0", 5:"$a1", 6:"$a2", 7:"$a3",
    8:"$t0", 9:"$t1", 10:"$t2", 11:"$t3", 12:"$t4", 13:"$t5", 14:"$t6", 15:"$t7",
    16:"$s0", 17:"$s1", 18:"$s2", 19:"$s3", 20:"$s4", 21:"$s5", 22:"$s6", 23:"$s7",
    24:"$t8", 25:"$t9", 26:"$k0", 27:"$k1", 28:"$gp", 29:"$sp", 30:"$fp", 31:"$ra",
    }

ops = {
    2:"j", 3:"jal", 4:"beq", 5:"bne", 6:"blez", 7:"bgtz",
    8:"addi", 9:"addiu", 10:"slti", 11:"sltiu", 12:"andi", 13:"ori", 14:"xori", 15:"lui",
    20:"beql", 21:"bnel", 22:"blezl", 23:"bgtzl",
    24:"daddi", 25:"daddiu",
    32:"lb", 33:"lh", 34:"lwl", 35:"lw", 36:"lbu", 37:"lhu", 38:"lwr",
    40:"sb", 41:"sh", 42:"swl", 43:"sw", 46:"swr", 47:"cache",
    48:"ll", 49:"lwc1", 50:"lwc2", 51:"pref", 53:"ldc1", 54:"ldc2", 55:"ld",
    56:"sc", 57:"swc1", 58:"swc2", 61:"sdc1", 62:"sdc2", 63:"sd",
    }

funcs = {
    0:"sll", 2:"srl", 3:"sra", 4:"sllv", 6:"srlv", 7:"srav",
    8:"jr", 9:"jalr", 10:"movz", 11:"movn", 12:"syscall", 13:"break", 15:"sync",
    16:"mfhi", 17:"mthi", 18:"mflo", 19:"mtlo", 20:"dsllv", 22:"dsrlv", 23:"dsrav",
    24:"mult", 25:"multu", 26:"div", 27:"divu", 28:"dmult", 29:"dmultu", 30:"ddiv", 31:"ddivu",
    32:"add", 33:"addu", 34:"sub", 35:"subu", 36:"and", 37:"or", 38:"xor", 39:"nor",
    42:"slt", 43:"sltu", 44:"dadd", 45:"daddu",
    48:"tge", 49:"tgeu", 50:"tlt", 51:"tltu", 52:"teq", 54:"tne",
    56:"dsll", 59:"dsra", 60:"dsll32", 63:"dsra32",
    }

branch1reg = {
    0:"bltz", 1:"bgez", 2:"bltzl", 3:"bgezl",
    8:"tgei", 9:"tgeiu", 10:"tlti", 11:"tltiu", 12:"tegi", 14:"tnei",
    16:"bltzal", 17:"bgezal", 18:"bltall", 19:"bgczall",
    }

floats = {
    0:"add", 1:"sub", 2:"mul", 3:"div", 4:"sqrt", 5:"abs", 6:"mov", 7:"neg",
    8:"round.l", 9:"trunc.l", 10:"ceil.l", 11:"floor.l", 12:"round.w", 13:"trunc.w", 14:"ceil.w", 15:"floor.w",
    18:"movz", 19:"movn",
    32:"cvt.s", 33:"cvt.d", 36:"cvt.w", 37:"cvt.l",
    48:"c.f", 49:"c.un", 50:"c.eq", 51:"c.ueq", 52:"c.olt", 53:"c.ult", 54:"c.ole", 55:"c.ule",
    56:"c.sf", 57:"c.ngle", 58:"c.seq", 59:"c.ngl", 60:"c.lt", 61:"c.nge", 62:"c.le", 63:"c.ngt",
    }

def read_file(name):
    file_data=[]

    try:
        with open(name, 'rb') as f:
            file_data = f.read()
    except IOError:
        print('failed to read file ' + name)
    return file_data


def float_reg(num):
    if num == 31:
        return "$31"
    return "$f%d" % num


def get_op(inst):
    return (inst & 0b11111100000000000000000000000000) >> 26


def get_func(inst):
    return (inst & 0b00000000000000000000000000111111)


def get_rs(inst):
    return (inst & 0b00000011111000000000000000000000) >> 21


def get_rt(inst):
    return (inst & 0b00000000000111110000000000000000) >> 16


def get_rd(inst):
    return (inst & 0b00000000000000001111100000000000) >> 11


def get_shift(inst):
    return (inst & 0b00000000000000000000011111000000) >> 6


def get_ft(inst):
    return (inst & 0b00000000000111110000000000000000) >> 16


def get_fs(inst):
    return (inst & 0b00000000000000001111100000000000) >> 11


def get_fd(inst):
    return (inst & 0b00000000000000000000011111000000) >> 6


def get_imm(inst):
    return inst & 0b00000000000000001111111111111111


def get_signed_imm(inst):
    imm = get_imm(inst)
    if (imm & (1 << 15)) != 0:
        imm = -2**15 + (imm & 0b00000000000000000111111111111111)
    return imm


def is_load(inst):
    return get_op(inst) > 31


def get_func_name(addr):
    if addr in known_funcs:
        return known_funcs[addr][0]
    else:
        return "func_%08X" % addr


def get_symbol_name(addr):
    if addr in known_vars and known_vars[addr][0] != "":
        return known_vars[addr][0]
    else:
        return "D_%08X" % addr


def write_header(file):
    file.write(".set noat # allow use of $at\n"
               ".set noreorder # don't insert nops after branches\n"
               ".set gp=64 # allow use of 64bit registers\n"
               ".macro glabel label\n"
               "    .global \label\n"
               "    \label:\n"
               ".endm\n"
               "\n");


# TODO add code_regions?
class Disassembler:

    class File:
        def __init__(self, name, data, vaddr):
            self.name = name
            self.data = data
            self.vaddr = vaddr
            self.size = len(data)

        def get_inst(self, num):
            offset = num*4
            return struct.unpack('>I', self.data[offset:offset+4])[0]

    def __init__(self):
        self.files = list()
        self.objects = set()
        self.functions = set()
        self.labels = set()
        self.vars = set()
        self.data_regions = list()

        self.is_data_cache = {}
        self.is_code_cache = {}

    def load_defaults(self):
        for file in known_files:
            self.add_file(file[0], file[1], file[2])
            self.add_object(file[2]) # assume every file starts with a object and function
            self.add_function(file[2])
            for region in file[3]:
                self.add_data_region(region[0], region[1])

        for addr in known_funcs:
            self.add_function(addr)

        for addr in known_objects:
            self.add_object(addr)
            self.add_function(addr) # assume every object starts with a function

        for addr in known_vars:
            self.add_variable(addr)

    def add_file(self, path, name, vaddr):
        self.files.append(self.File(name, read_file(path), vaddr))
        self.is_data_cache = {}
        self.is_code_cache = {}

    def add_object(self, addr):
        self.objects.add(addr)

    def add_function(self, addr):
        self.functions.add(addr)

    def add_variable(self, addr):
        self.vars.add(addr)

    def add_label(self, addr):
        self.labels.add(addr)

    def add_data_region(self, start, end):
        self.data_regions.append((start, end))
        self.is_data_cache = {}
        self.is_code_cache = {}

    def is_in_data(self, addr):
        if addr in self.is_data_cache:
            return self.is_data_cache[addr]

        start = 0;
        last = len(self.data_regions) - 1
        while start <= last:
            midpoint = (start + last) // 2
            if addr >= self.data_regions[midpoint][0]:
                if addr <= self.data_regions[midpoint][1]:
                    self.is_data_cache[addr] = True
                    return True;
                else:
                    start = midpoint + 1
            else:
                last = midpoint - 1

        self.is_data_cache[addr] = False
        return False

    def is_in_code(self, addr):
        if addr in self.is_code_cache:
            return self.is_code_cache[addr]

        start = 0;
        last = len(self.files) - 1
        while start <= last:
            midpoint = (start + last) // 2
            if addr >= self.files[midpoint].vaddr:
                if addr < (self.files[midpoint].vaddr + self.files[midpoint].size):
                    self.is_code_cache[addr] = not self.is_in_data(addr)
                    return self.is_code_cache[addr];
                else:
                    start = midpoint + 1
            else:
                last = midpoint - 1

        self.is_code_cache[addr] = False
        return False

    def is_in_data_or_undef(self, addr):
        # return true if it is in a defined data region
        if self.is_in_data(addr):
            return True

        # otherwise return false if it is in a file's bounds
        if self.is_in_code(addr):
            return False

        # otherwise it is undefined (return true)
        return True

    def make_label(self, imm, cur):
        addr = (imm*4) + cur + 4
        self.add_label(addr)
        return ".L_%08X" % addr

    def make_func(self, imm, cur):
        addr = (imm*4) + (cur & 0xF0000000)
        self.add_function(addr)
        return get_func_name(addr)

    def make_load(self, addr):
        if self.is_in_data_or_undef(addr):
            return get_symbol_name(addr)
        else:
            return get_func_name(addr)

    # TODO refactor to remove file_addr
    def get_object_name(self, addr, file_addr):
        filename = "";

        for file in self.files:
            if file_addr == file.vaddr:
                filename = file.name

        if filename == "":
            print("Bad file_addr passed to get_object_name: 0x%0X" % addr)
            return

        if SPLIT_FILES:
            if addr in known_objects and known_objects[addr] != "": # no name means object boundary is known but not the name
                return known_objects[addr]
            else:
                return '%s_0x%08X' % (filename, addr)
        else:
            return "%s" % filename

    def guess_functions_from_data(self):
        for file in self.files:
            for i in range(0, file.size // 4):
                word = file.get_inst(i)
                addr = file.vaddr + i*4
                if self.is_in_data(addr) and self.is_in_code(word):
                    self.add_function(word)



    def disassemble(self, path):
        # TODO keep sorted
        self.files = sorted(self.files, key = lambda file: file.vaddr)
        self.data_regions = sorted(self.data_regions, key = lambda region: region[0])

        self.__first_pass()
        self.guess_functions_from_data()
        self.__second_pass(path)

    def __first_pass(self):
        for file in self.files:
            for i in range(0, file.size // 4):
                inst = file.get_inst(i)
                addr = file.vaddr + i*4
                if not self.is_in_data_or_undef(addr):
                    self.disassemble_inst(inst, addr, i, file)

                    if inst == 0x03E00008: # jr $ra
                        next_index = i+2
                        if file.get_inst(next_index) == 0: # nop
                            while file.get_inst(next_index) == 0:
                                next_index += 1

                            new_object_start = file.vaddr + next_index*4 + 15
                            new_object_start -= new_object_start % 16

                            # don't split if it's the start of a data section, it's probably the same object
                            if not self.is_in_data_or_undef(new_object_start):
                                self.add_object(new_object_start)

    def __second_pass(self, path):
        for file in self.files:
            filename = path + '/%s.asm' % self.get_object_name(file.vaddr, file.vaddr);

            with open(filename, 'w') as f:
                write_header(f)

                for i in range(0, file.size // 4):
                    inst = file.get_inst(i)
                    addr = file.vaddr + i*4

                    if addr in self.objects and SPLIT_FILES:
                        f.close();
                        filename = path + '/%s.asm' % self.get_object_name(addr, file.vaddr);
                        f = open(filename, 'w')
                        write_header(f)

                    if addr in self.labels:
                        f.write(".L_%08X:\n" % addr)
                    if addr in self.functions:
                        name = get_func_name(addr)
                        f.write("\nglabel %s\n" % name)
                    if addr in self.vars:
                        name = self.make_load(addr)
                        f.write("glabel %s\n" % name)

                    if not self.is_in_data_or_undef(addr):
                        f.write("/* %06d 0x%08X %08X */ %s\n" % (i, addr, inst, self.disassemble_inst(inst, addr, i, file)))
                    else:
                        f.write("/* %06d 0x%08X */ .word\t0x%08X\n" % (i, addr, inst))

    def determine_load_ref(self, file, inst_i):
        # TODO better detect when the register gets dirty
        pc = file.vaddr + inst_i*4
        cur_inst = file.get_inst(inst_i)

        if get_op(cur_inst) != 15:
            return

        prev_was_jump = False

        for i in range(1, 7): # TODO find a good limit
            next_inst = file.get_inst(inst_i + i)

            if get_op(next_inst) == 15 and get_rt(cur_inst) == get_rt(next_inst):
                return # return if another lui overwrites reg

            if (get_op(next_inst) == 9) and (get_rt(cur_inst) == get_rt(next_inst) == get_rs(next_inst)): # lui + addiu (move pointer)
                addr = (get_imm(cur_inst) << 16) + get_signed_imm(next_inst)
                if self.is_in_data_or_undef(addr):
                    self.add_variable(addr)
                else:
                    self.add_function(addr)
                loadHighRefs[pc] = addr
                loadLowRefs[pc + 4*i] = addr
                return

            elif is_load(next_inst) and (get_rt(cur_inst) == get_rs(next_inst)): # lui + load (load pointer)
                addr = (get_imm(cur_inst) << 16) + get_signed_imm(next_inst)
                if self.is_in_data_or_undef(addr):
                    self.add_variable(addr)
                else:
                    print("Warning: Pointer load location is in code 0x%08X" % addr)
                    self.add_variable(addr)
                loadHighRefs[pc] = addr
                loadLowRefs[pc + 4*i] = addr
                return

            # if this is a jump, mark to return after we evaluate the following instruction
            if prev_was_jump:
                return
            if get_op(next_inst) == 2 or get_op(next_inst) == 3:
                prev_was_jump = True

    def disassemble_inst(self, inst, addr, i, file):
        if inst == 0:
            return "nop"

        dis = ""
        op_num = get_op(inst)

        if op_num == 0:
            func = get_func(inst)
            if func == 1:
                cc = (inst & (7 << 18)) >> 18
                if (inst & (1 << 16)) == 0:
                    dis += "movf\t%s, %s, %d" % (regs[get_rd(inst)], regs[get_rs(inst)], cc)
                else:
                    dis += "movt\t%s, %s, %d" % (regs[get_rd(inst)], regs[get_rs(inst)], cc)
            else:
                if func not in funcs:
                    dis += "func_error: %d" % func
                else:
                    if func == 37 and get_rt(inst) == 0: # or with zero reg is move
                        return "move\t%s, %s" % (regs[get_rd(inst)], regs[get_rs(inst)])
                    dis += "%s\t" % funcs[func]
                    if func == 0 or func == 2 or func == 3 or func == 56 or func == 59 or func == 60 or func == 63: # sll, srl, sra, dsll, dsra dsll32, dsra32
                        dis += "%s, %s, %d" % (regs[get_rd(inst)], regs[get_rt(inst)], get_shift(inst))
                    elif func == 4 or func == 6 or func == 7: # sllv, srlv, srav
                        dis += "%s, %s, %s" % (regs[get_rd(inst)], regs[get_rt(inst)], regs[get_rs(inst)])
                    elif func == 8 or func == 9: # jr, jalr
                        dis += "%s" % regs[get_rs(inst)]
                    elif func == 13: # break
                        dis += "0x%05X" % ((inst & (0xFFFFF << 6)) >> 16) # TODO the error code is 20 bits in the manual, why does gas want something else?
                    elif func == 16 or func == 18: # mfhi, mflo
                        dis += "%s" % regs[get_rd(inst)]
                    elif func == 17 or func == 19: # mthi, mtlo
                        dis += "%s" % regs[get_rs(inst)]
                    elif func == 24 or func == 25 or func == 28 or func == 29: # mult, multu, dmult, dmultu
                        dis += "%s, %s" % (regs[get_rs(inst)], regs[get_rt(inst)])
                    elif func == 26 or func == 27 or func == 30 or func == 31: # div, divu, ddiv, ddivu
                        dis += "$zero, %s, %s" % (regs[get_rs(inst)], regs[get_rt(inst)]) # TODO why does this need $zero for gas to not think it's a macro?
                    elif func == 34 and get_rs(inst) == 0: # sub with $zero is neg
                        dis = "neg\t%s, %s" % (regs[get_rd(inst)], regs[get_rt(inst)])
                    elif func == 35 and get_rs(inst) == 0: # subu with $zero is negu
                        dis = "negu\t%s, %s" % (regs[get_rd(inst)], regs[get_rt(inst)])
                    elif func == 20 or func == 22 or func == 23: # doubleword ops
                        dis += "%s, %s, %s" % (regs[get_rd(inst)], regs[get_rt(inst)], regs[get_rs(inst)])
                    else: # add, sub, logical, etc.
                        dis += "%s, %s, %s" % (regs[get_rd(inst)], regs[get_rs(inst)], regs[get_rt(inst)])
                    # TODO traps

        elif op_num == 1:
            rt = get_rt(inst)
            if rt not in branch1reg:
                dis += "branch1reg_erro: %d" % rt
            else:
                # TODO traps
                dis += "%s\t%s, %s" % (branch1reg[rt], regs[get_rs(inst)], self.make_label(get_signed_imm(inst), addr))

        elif op_num == 16 or op_num == 17 or op_num == 18:
            z = op_num - 16
            rs = get_rs(inst)
            if rs == 0:
                dis += "mfc%d\t%s, %s" % (z, regs[get_rt(inst)], float_reg(get_rd(inst)) if z != 0 else "$%d" % get_rd(inst))
            elif rs == 1:
                dis += "dmfc%d\t%s, %s" % (z, regs[get_rt(inst)], float_reg(get_rd(inst)) if z != 0 else "$%d" % get_rd(inst))
            elif rs == 2:
                dis += "cfc%d\t%s, %s" % (z, regs[get_rt(inst)], float_reg(get_rd(inst)) if z != 0 else "$%d" % get_rd(inst))
            elif rs == 4:
                dis += "mtc%d\t%s, %s" % (z, regs[get_rt(inst)], float_reg(get_rd(inst)) if z != 0 else "$%d" % get_rd(inst))
            elif rs == 5:
                dis += "dmtc%d\t%s, %s" % (z, regs[get_rt(inst)], float_reg(get_rd(inst)) if z != 0 else "$%d" % get_rd(inst))
            elif rs == 6:
                dis += "ctc%d\t%s, %s" % (z, regs[get_rt(inst)], float_reg(get_rd(inst)) if z != 0 else "$%d" % get_rd(inst))
            elif rs == 8:
                dis += "bc%d%s%s %s" % (z, "f" if ((inst & (1 << 16)) == 0) else "t", "" if ((inst & (1 << 17)) == 0) else "l", self.make_label(get_signed_imm(inst), addr))
            elif rs == 16 or rs == 17 or rs == 20 or rs == 21:
                if z == 0:
                    func = get_func(inst)
                    if func == 1:
                        dis += "tlbr"
                    elif func == 2:
                        dis += "tlbwi"
                    elif func == 6:
                        dis += "tlbwr"
                    elif func == 8:
                        dis += "tlbp"
                    elif func == 24:
                        dis += "eret"
                    else:
                        # TODO deret?
                        dis += "cop0_error: %d" % func
                elif z != 1:
                    dis += "cop_error: %d" % z
                else:
                    if rs == 16:
                        f = "s"
                    elif rs == 17:
                        f = "d"
                    elif rs == 20:
                        f = "w"
                    elif rs == 21:
                        f = "l"
                    func = get_func(inst)
                    if func not in floats:
                        dis += "float_error: %d" % func
                    else:
                        dis += "%s.%s\t" % (floats[func], f)
                        if func == 0 or func == 1 or func == 2 or func == 3 or func == 18 or func == 19: # 3 op
                            dis += "%s, %s, %s" % (float_reg(get_fd(inst)), float_reg(get_fs(inst)), float_reg(get_ft(inst)))
                        elif (func == 4 or func == 5 or func == 6 or func == 7 or func == 8 or func == 9  or func == 10 or func == 11 or func == 12
                              or func == 13 or func == 14 or func == 15 or func == 32 or func == 33 or func == 36 or func == 37): # 2 op
                            dis += "%s, %s" % (float_reg(get_fd(inst)), float_reg(get_fs(inst)))
                        elif func == 50 or func == 60 or func == 62: # c.eq, c.lt, c.le
                            dis += "%s, %s" % (float_reg(get_fs(inst)), float_reg(get_ft(inst)))
            else:
                dis += "coproc_error: %d" % rs

        elif op_num not in ops:
            dis += "error: %d" % op_num

        else:
            dis += "%s\t" % ops[op_num]
            if op_num == 2 or op_num == 3: # j, jal
                dis += "%s" % self.make_func(inst & 0x3FFFFFF, addr);
            elif op_num == 4 or op_num == 5 or op_num == 20 or op_num == 21: # beq, bne, beql, bnel
                if op_num == 4 and get_rs(inst) == get_rt(inst) == 0: # beq with both zero regs is a branch always (b %label)
                    dis = "b\t%s" % self.make_label(get_signed_imm(inst), addr)
                else:
                    if get_rt(inst) == 0: # branchs comparing to 0 have a shorthand
                        dis = "%s\t" % ("beqz" if op_num == 4 else "bnez" if op_num == 5 else "beqzl" if op_num == 20 else "bnezl")
                        dis += "%s, %s" % (regs[get_rs(inst)], self.make_label(get_signed_imm(inst), addr))
                    else:
                        dis += "%s, %s, %s" % (regs[get_rs(inst)], regs[get_rt(inst)], self.make_label(get_signed_imm(inst), addr))
            elif op_num == 6 or op_num == 7 or op_num == 22 or op_num == 23: # blez, bgtz, blezl, bgtzl
                dis += "%s, %s" % (regs[get_rs(inst)], self.make_label(get_signed_imm(inst), addr))
            elif op_num == 8 or op_num == 9 or op_num == 10 or op_num == 11 or op_num == 24 or op_num == 25: # addi, addiu, slti, sltiu, daddi, daddiu
                if op_num == 9 and get_rs(inst) == 0: # addiu with reg 0 is load immediate (li)
                    dis = "li\t%s, %d" % (regs[get_rt(inst)], get_signed_imm(inst))
                elif op_num == 9 and addr in loadLowRefs: # addiu loading the lower half of a pointer
                    dis += "%s, %%lo(%s)" % (regs[get_rt(inst)], self.make_load(loadLowRefs[addr]))
                else:
                    dis += "%s, %s, %d" % (regs[get_rt(inst)], regs[get_rs(inst)], get_signed_imm(inst))
            elif op_num == 12 or op_num == 13 or op_num == 14: # andi, ori, xori
                dis += "%s, %s, %#X" % (regs[get_rt(inst)], regs[get_rs(inst)], get_imm(inst))
            elif op_num == 15: # lui
                self.determine_load_ref(file, i)
                if addr in loadHighRefs: # lui loading the higher half of a pointer
                    dis += "%s, %%hi(%s)" % (regs[get_rt(inst)], self.make_load(loadHighRefs[addr]))
                else:
                    dis += "%s, 0x%04X" % (regs[get_rt(inst)], get_imm(inst))
            elif (op_num == 32 or op_num == 33 or op_num == 34 or op_num == 35 or op_num == 38 or op_num == 40 or op_num == 41 or
                 op_num == 42 or op_num == 42 or op_num == 43 or op_num == 46 or op_num == 55 or op_num == 63): # load/stores
                if addr in loadLowRefs: # loading with immediate forming lower half of pointer
                    dis += "%s, %%lo(%s)(%s)" % (regs[get_rt(inst)], self.make_load(loadLowRefs[addr]), regs[get_rs(inst)])
                else:
                    dis += "%s, %#X(%s)" % (regs[get_rt(inst)], get_signed_imm(inst), regs[get_rs(inst)])
            elif op_num == 36 or op_num == 37: # lbu, lhu
                if addr in loadLowRefs: # loading with immediate forming lower half of pointer
                    dis += "%s, %%lo(%s)(%s)" % (regs[get_rt(inst)], self.make_load(loadLowRefs[addr]), regs[get_rs(inst)])
                else:
                    dis += "%s, %#X(%s)" % (regs[get_rt(inst)], get_signed_imm(inst), regs[get_rs(inst)])
            elif (op_num == 49 or op_num == 50 or op_num == 53 or op_num == 54 or op_num == 57 or op_num == 58 or
                  op_num == 61 or op_num == 62): # load/store between co-processors
                if addr in loadLowRefs: # loading with immediate forming lower half of pointer
                    dis += "%s, %%lo(%s)(%s)" % (float_reg(get_rt(inst)), self.make_load(loadLowRefs[addr]), regs[get_rs(inst)])
                else:
                    dis += "%s, %#X(%s)" % (float_reg(get_rt(inst)), get_signed_imm(inst), regs[get_rs(inst)])
            elif op_num == 47: # cache
                if addr in loadLowRefs: # cache op with immediate forming lower half of pointer
                    dis += "0x%02X, %%lo(%s)(%s)" % (get_rt(inst), self.make_load(loadLowRefs[addr]), regs[get_rs(inst)])
                else:
                    dis += "0x%02X, %#X(%s)" % (get_rt(inst), get_signed_imm(inst), regs[get_rs(inst)])

        return dis

    def generate_headers(self, path):
        with open(path + "functions.h", 'w', newline='\n') as f:
            f.write("#ifndef _FUNCTIONS_H_\n#define _FUNCTIONS_H_\n\n");

            f.write('#include <PR/ultratypes.h>\n#include <osint.h>\n#include <viint.h>\n#include <guint.h>\n#include <unk.h>\n#include <structs.h>\n\n');

            for addr in sorted(self.functions):
                if addr in known_funcs:
                    f.write("%s %s(%s); // func_%08X\n" % (known_funcs[addr][1], get_func_name(addr), known_funcs[addr][2], addr));
                else:
                    f.write("// UNK_RET %s(UNK_ARGS);\n" % get_func_name(addr));

            f.write("\n#endif\n");

        with open(path + "variables.h", 'w', newline='\n') as f:
            f.write("#ifndef _VARIABLES_H_\n#define _VARIABLES_H_\n\n");

            f.write('#include <PR/ultratypes.h>\n#include <osint.h>\n#include <viint.h>\n#include <guint.h>\n#include <unk.h>\n#include <structs.h>\n\n');

            for addr in sorted(self.vars):
                if addr in known_vars:
                    f.write("extern %s %s%s; // D_%08X\n" % (known_vars[addr][1], self.make_load(addr), "[]" if known_vars[addr][2] else "", addr));
                else:
                    f.write("//extern UNK_TYPE %s;\n" % self.make_load(addr));

            f.write("\n// extra variables needed for one reason or another\n\n");
            for (name, var_type) in extra_vars:
                f.write("extern %s %s;\n" % (var_type, name));

            f.write("\n#endif\n");

            with open("undef.txt", 'w', newline='\n') as f:
                for addr in sorted(self.vars):
                    f.write("%s = 0x%08X;\n" % (self.make_load(addr), addr));

                # TODO not hard code
                f.write('''
func_8080074C = 0x8080074C;
func_80801B4C = 0x80801B4C;
func_80803F30 = 0x80803F30;
func_80813C98 = 0x80813C98;
func_80815820 = 0x80815820;
func_808283D8 = 0x808283D8;
func_8082895C = 0x8082895C;
func_80841AC4 = 0x80841AC4;
func_808460B8 = 0x808460B8;
func_80846528 = 0x80846528;
func_808470D4 = 0x808470D4;
func_80920340 = 0x80920340;
func_80922430 = 0x80922430;
D_80099AD0_ = 0x80099AD0;'''
                )


if __name__ == "__main__":
    dis = Disassembler()
    dis.load_defaults()
    dis.disassemble('./asm/')
    dis.generate_headers('./')

