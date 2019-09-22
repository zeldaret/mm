'''
Resources:
http://www.cs.unibo.it/~solmi/teaching/arch_2002-2003/AssemblyLanguageProgDoc.pdf
https://github.com/pathscale/binutils/blob/5c2c133020e41fc4aadd80a99156d2cea4754b96/include/coff/sym.h
https://github.com/pathscale/binutils/blob/5c2c133020e41fc4aadd80a99156d2cea4754b96/include/coff/symconst.h
https://github.com/pathscale/binutils/blob/5c2c133020e41fc4aadd80a99156d2cea4754b96/gas/ecoff.c
https://github.com/pathscale/binutils/blob/5c2c133020e41fc4aadd80a99156d2cea4754b96/bfd/ecoff.c
https://github.com/pathscale/absoft/blob/master/svn/trunk/ekopath-gcc/ekopath-gcc-4.2.0/gcc/mips-tdump.c
'''

import os
import struct
import collections
import sys

OFFSET = 0 # TODO why are the offsets in the symbolic header off by some amount?

indent_level = 0
is_comment = False

symbol_type_list = [
    'stNil', 'stGlobal', 'stStatic', 'stParam', 'stLocal', 'stLabel', 'stProc', 'stBlock',
    'stEnd', 'stMember', 'stTypedef', 'stFile', 'INVALID', 'INVALID', 'stStaticProc', 'stConstant',
    'stStaParam', 'INVALID', 'INVALID', 'INVALID', 'INVALID', 'INVALID', 'INVALID', 'INVALID',
    'INVALID', 'INVALID', 'stStruct', 'stUnion', 'stEnum', 'INVALID', 'INVALID', 'INVALID',
    'INVALID', 'INVALID', 'stIndirect']
storage_class_list = ['scNil', 'scText', 'scData', 'scBss', 'scRegister', 'scAbs', 'scUndefined', 'reserved',
    'scBits', 'scDbx', 'scRegImage', 'scInfo', 'scUserStruct', 'scSData', 'scSBss', 'scRData',
    'scVar', 'scCommon', 'scSCommon', 'scVarRegister', 'scVariant', 'scUndefined', 'scInit']
basic_type_c_list = ['nil', 'addr', 'signed char', 'unsigned char', 'short', 'unsigned short', 'int', 'unsigned int',
    'long', 'unsigned long', 'float', 'double', 'struct', 'union', 'enum', 'typedef',
    'range', 'set', 'complex', 'double complex', 'indirect', 'fixed decimal', 'float decimal', 'string',
    'bit', 'picture', 'void', 'long long', 'unsigned long long', 'INVALID', 'long', 'unsigned long',
    'long long', 'unsigned long long', 'addr', 'int64', 'unsigned int64']

def increase_indent():
    global indent_level
    indent_level += 1

def decrease_indent():
    global indent_level
    indent_level -= 1

def set_is_comment(set_to):
    global is_comment
    old = is_comment
    is_comment = set_to
    return old

def get_indent():
    global indent_level
    global is_comment
    ret = '//' if is_comment else ''
    for i in range(indent_level):
        ret += '    '
    return ret

def read_uint32_be(file_data, offset):
    return struct.unpack('>I', file_data[offset:offset+4])[0]

def read_uint16_be(file_data, offset):
    return struct.unpack('>H', file_data[offset:offset+2])[0]

def read_uint8_be(file_data, offset):
    return struct.unpack('>B', file_data[offset:offset+1])[0]

def read_elf_header(file_data, offset):
    Header = collections.namedtuple('ElfHeader',
                                    '''e_magic e_class e_data e_version e_osabi e_abiversion e_pad
                                       e_type e_machine e_version2 e_entry e_phoff e_shoff e_flags
                                       e_ehsize e_phentsize e_phnum e_shentsize e_shnum e_shstrndx''')
    return Header._make(struct.unpack('>I5B7s2H5I6H', file_data[offset:offset+52]))

def read_elf_section_header(file_data, offset):
    Header = collections.namedtuple('SectionHeader',
                                    '''sh_name sh_type sh_flags sh_addr sh_offset sh_size sh_link
                                       sh_info sh_addralign sh_entsize''')
    return Header._make(struct.unpack('>10I', file_data[offset:offset+40]))

def read_symbolic_header(file_data, offset):
    Header = collections.namedtuple('SymbolicHeader',
                                    '''magic vstamp ilineMax cbLine cbLineOffset idnMax cbDnOffset
                                       ipdMax cbPdOffset isymMax cbSymOffset ioptMax cbOptOffset
                                       iauxMax cbAuxOffset issMax cbSsOffset issExtMax cbSsExtOffset
                                       ifdMax cbFdOffset crfd cbRfdOffset iextMax cbExtOffset''')
    return Header._make(struct.unpack('>2H23I', file_data[offset:offset+96]))

# TODO find a better solution for the bitfield
def read_file_descriptor(file_data, offset):
    if 'init' not in read_file_descriptor.__dict__:
        read_file_descriptor.cache = {}
        read_file_descriptor.header = collections.namedtuple('FileDescriptor',
                                       '''adr rss issBase cbSs isymBase csym ilineBase cline ioptBase
                                       copt ipdFirst cpd iauxBase caux rfdBase crfd XXX_bitfield
                                       cbLineOffset cbLine''')
        read_file_descriptor.init = True
    if offset in read_file_descriptor.cache:
        return read_file_descriptor.cache[offset]
    read_file_descriptor.cache[offset] = read_file_descriptor.header._make(
        struct.unpack('>I2iI6iHh4iI2I', file_data[offset:offset+72]))
    return read_file_descriptor.cache[offset]

def read_procedure_descriptor(file_data, offset):
    Header = collections.namedtuple('ProcedureDescriptor',
                                    '''adr isym iline regmask regoffset iopt fregmask fregoffset
                                       frameoffset framereg pcreg lnLow lnHigh cbLineOffset''')
    return Header._make(struct.unpack('>I8i2h2iI', file_data[offset:offset+52]))

def read_symbol(file_data, offset):
    if 'init' not in read_symbol.__dict__:
        read_symbol.cache = {}
        read_symbol.header = collections.namedtuple('Symbol', '''iss value st sc index''')
        read_symbol.init = True
    if offset in read_symbol.cache:
        return read_symbol.cache[offset]
    (word0, word1, word2) = struct.unpack('>iII', file_data[offset:offset+12])
    read_symbol.cache[offset] = read_symbol.header._make((
        word0, word1, (word2 >> 26) & 0x3F, (word2 >> 21) & 0x1F, word2 & 0xFFFFF))
    return read_symbol.cache[offset]

def read_auxiliary_symbol(file_data, offset):
    if 'init' not in read_auxiliary_symbol.__dict__:
        read_auxiliary_symbol.cache = {}
        read_auxiliary_symbol.header = collections.namedtuple('AuxSymbol',
            '''ti rndx dnLow dnHigh isym iss width count''')
        read_auxiliary_symbol.type_info = collections.namedtuple('TypeInfo',
            '''fBitfield continued bt tq4 tq5 tq0 tq1 tq2 tq3''')
        read_auxiliary_symbol.rel_sym = collections.namedtuple('RelativeSymbol', '''rfd index''')
        read_auxiliary_symbol.init = True
    if offset in read_auxiliary_symbol.cache:
        return read_auxiliary_symbol.cache[offset]
    word0 = struct.unpack('>I', file_data[offset:offset+4])[0]
    read_auxiliary_symbol.cache[offset] = read_auxiliary_symbol.header._make((
        read_auxiliary_symbol.type_info._make(((word0 >> 31) & 1, (word0 >> 30) & 1, (word0 >> 24) & 0x3F, (word0 >> 20) & 0xF, (word0 >> 16) & 0xF, (word0 >> 12) & 0xF, (word0 >> 8) & 0xF, (word0 >> 4) & 0xF, word0 & 0xF)),
        read_auxiliary_symbol.rel_sym._make(((word0 >> 20) & 0xFFF, word0 & 0xFFFFF)),
        word0, word0, word0, word0, word0, word0))
    return read_auxiliary_symbol.cache[offset]

def read_string(file_data, offset):
    current_offset = 0
    current_string = b''
    while True:
        char = struct.unpack('c', file_data[offset+current_offset:offset+current_offset+1])[0]
        if char == b'\0':
            return current_string.decode('ascii')
        else:
            current_string += char
        current_offset += 1

def get_symbol_name_from_aux(file_data, fd, symbolic_header, aux_num, search_for_typedef):
    aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + aux_num)*4)
    fd_num = aux.rndx.rfd
    next_aux = aux_num+1
    if fd_num == 4095:
        aux2 = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + next_aux)*4)
        fd_num = aux2.isym
        next_aux = next_aux+1;
    fd2 = read_file_descriptor(file_data, symbolic_header.cbFdOffset - OFFSET + fd_num*72)
    sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + (fd2.isymBase + aux.rndx.index)*12)
    ret = ''
    #print('%r' % (aux,));
    #print('%r' % (aux2,));
    #print('%r' % (sym,));
    if sym.st == 26 or sym.st == 27: #stStruct, stunion
        ret = get_struct_or_union_string(file_data, fd2, symbolic_header, fd2.isymBase + aux.rndx.index, search_for_typedef)
    elif sym.st == 28: #stEnum:
        ret = get_enum_string(file_data, fd2, symbolic_header, fd2.isymBase + aux.rndx.index)
    else:
        ret = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd2.issBase + sym.iss)
    return (ret, next_aux)

def get_type_string(file_data, fd, symbolic_header, aux_num, name, search_for_typedef):
    ret = ''
    aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + aux_num)*4)
    #print('');
    #print('%r' % (aux,));
    next_aux = aux_num+1
    has_bitfield = aux.ti.fBitfield == 1
    bitwidth = 0
    if has_bitfield:
        bit_aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + next_aux)*4)
        bitwidth = bit_aux.isym
        next_aux = next_aux+1
    if aux.ti.bt == 12: # btStruct
        (ret, next_aux) = get_symbol_name_from_aux(file_data, fd, symbolic_header, next_aux, search_for_typedef)
    elif aux.ti.bt == 13: # btUnion
        (ret, next_aux) = get_symbol_name_from_aux(file_data, fd, symbolic_header, next_aux, search_for_typedef)
    elif aux.ti.bt == 15: # btTypedef
        (ret, next_aux) = get_symbol_name_from_aux(file_data, fd, symbolic_header, next_aux, search_for_typedef)
    elif aux.ti.bt == 14: # btEnum
        (ret, next_aux) = get_symbol_name_from_aux(file_data, fd, symbolic_header, next_aux, search_for_typedef)
    else:
        ret = basic_type_c_list[aux.ti.bt]

    tq_list = (aux.ti.tq0, aux.ti.tq1, aux.ti.tq2, aux.ti.tq3, aux.ti.tq4, aux.ti.tq5)

    # TODO this is very naive and probably does not work in a large amount of cases
    last_was_proc = False # if we see a tqProc, assume the next will be a tqPtr
    for tq in tq_list:
        if tq == 0: # tqNil
            break;
        elif tq == 1: # tqPtr
            if last_was_proc:
                last_was_proc = False
                continue
            ret += '*'
        elif tq == 2: # tqProc
            last_was_proc = True
            name = '(*%s)(... /* ECOFF does not store param types */)' % name
        elif tq == 3: # tqArray
            next_aux += 2 # todo what does this skip over? (Apparantly the type of the index, so always int for C)
            array_low_aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + next_aux)*4)
            array_high_aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + next_aux+1)*4)
            stride_aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + next_aux+2)*4)
            next_aux += 3
            if array_high_aux.dnHigh == 0xFFFFFFFF:
                name += '[]'
            else:
                name += '[%d]' % (array_high_aux.dnHigh + 1)
        elif tq == 4: # tqFar
            print('ERROR tqFar in get_type_name')
        elif tq == 5: # tqVol
            ret = 'volatile ' + ret
        elif tq == 6: # tqConst
            ret = 'const ' + ret
    if has_bitfield:
        name += ' : %d' % bitwidth
    return ret + ' ' + name

def get_enum_string(file_data, fd, symbolic_header, enum_sym_num):
    ret = ''
    start_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + enum_sym_num*12)
    if start_sym.st != 28:
        print('ERROR unkown type in get_enum_string start:%d' % start_sym.st)
        return ret
    ret += 'enum {\n'
    increase_indent()
    sym_num = enum_sym_num + 1
    while sym_num < fd.isymBase + start_sym.index:
        sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
        if sym.st == 8: # stEnd
            decrease_indent()
            ret += get_indent()
            ret += '}'
        elif sym.st == 9: # stMember
            name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + sym.iss)
            ret += get_indent()
            ret += '%s = %d,\n' % (name, sym.value)
        else:
            print('ERROR unkown type in get_enum_string:%d' % sym.st)
            break
        sym_num += 1
    return ret

def get_struct_or_union_string(file_data, fd, symbolic_header, union_sym_num, search_for_typedef):
    ret = ''
    start_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + union_sym_num*12)
    if search_for_typedef:
        typedef_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + (fd.isymBase + start_sym.index)*12)
        if typedef_sym.st == 10: # stTypedef
            return read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + typedef_sym.iss)
        else:
            name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + start_sym.iss)
            if name != '':
                return name
    if start_sym.st == 26: # stStruct
        ret += 'struct {\n'
        increase_indent()
    elif start_sym.st == 27: # stUnion
        ret += 'union {\n'
        increase_indent()
    else:
        print('ERROR unkown type in get_struct_or_union_string start:%d' % start_sym.st)
        return ret
    sym_num = union_sym_num + 1
    while sym_num < fd.isymBase + start_sym.index:
        sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
        if sym.st == 8: # stEnd
            decrease_indent()
            ret += get_indent()
            ret += '}'
        elif sym.st == 9: # stMember
            name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + sym.iss)
            ret += get_indent()
            ret += '/* 0x%X */ %s;\n' % (sym.value // 8, get_type_string(file_data, fd, symbolic_header, sym.index, name, True))
        elif sym.st == 26 or sym.st == 27: #stStruct, stUnion
            sym_num = fd.isymBase + sym.index
            continue
        elif sym.st == 34: # stIndirect
            # TODO what even is a stIndirect?
            sym_num += 1
        else:
            print('ERROR unkown type in get_struct_or_union_string:%d' % sym.st)
            break
        sym_num += 1
    return ret

def print_typedef_symbols(file_data, fd, symbolic_header, typedef_sym_num):
    typedef_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + typedef_sym_num*12)
    if typedef_sym.st != 10: # stTypedef
        print('ERROR expected stTypedef symbol in print_typedef_symbols, found:%d' % typedef_sym.st)
        return
    name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + typedef_sym.iss)
    print('typedef %s;' % get_type_string(file_data, fd, symbolic_header, typedef_sym.index, name, False))

def print_procedure(file_data, fd, symbolic_header, proc_sym_num):
    proc_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + proc_sym_num*12)
    proc_name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + proc_sym.iss)
    print('%s(' % get_type_string(file_data, fd, symbolic_header, proc_sym.index+1, proc_name, True), end='')
    sym_num = proc_sym_num+1
    param_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
    first = True
    while param_sym.st == 3: # stParam
        param_name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + param_sym.iss)
        print('%s%s' % ('' if first else ', ',
                        get_type_string(file_data, fd, symbolic_header, param_sym.index, param_name, True)),
               end='')
        sym_num += 1
        param_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
        first = False

    print(');')
    comment_old = set_is_comment(True)
    while sym_num < fd.isymBase + fd.csym:
        sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
        sym_num += 1
        if sym.st == 7: # stBlock
            print('%s{' % get_indent())
            increase_indent()
        elif sym.st == 8: # stEnd
            if proc_name == read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + sym.iss):
                set_is_comment(comment_old)
                return sym_num
            decrease_indent()
            print('%s}' % get_indent())
        elif sym.st == 4: # stLocal
            local_name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + sym.iss)
            is_reg = sym.sc == 4 # scRegister
            print('%s%s%s;' % (get_indent(),
                'register ' if is_reg else '',
                get_type_string(file_data, fd, symbolic_header, sym.index, local_name, True)))
        elif sym.st == 2: # stStatic
            static_name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + sym.iss)
            print('%sstatic %s;' % (get_indent(),get_type_string(file_data, fd, symbolic_header, sym.index, static_name, True)))
        elif sym.st == 5: # stLabel
            static_name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + sym.iss)
            print('%sLabel: %s @ %d;' % (get_indent(), static_name, sym.value))
        elif sym.st == 6: # stProc
            # multiple name for function?
            sym_num = print_procedure(file_data, fd, symbolic_header, sym_num-1)
        elif sym.st == 26 or sym.st == 27: #stStruct, stUnion
            sym_num = fd.isymBase + sym.index
        elif sym.st == 34: # stIndirect
            # TODO what even is a stIndirect?
            sym_num += 1
        else:
            print('ERROR unkown st in print_procedure: %d' % sym.st)
    set_is_comment(comment_old)
    return sym_num

def print_symbols(file_data, fd, symbolic_header):
    sym_num = fd.isymBase
    while sym_num < fd.isymBase + fd.csym:
        root_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
        if root_sym.st == 11: # stFile
            file_name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + root_sym.iss)
            print('// begin file %s\n' %  file_name)
            sym_num += 1
            leaf_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
            while leaf_sym.st != 8: # stEnd
                if leaf_sym.st == 26 or leaf_sym.st == 27 or leaf_sym.st == 28: # stStruct, stUnion, stEnum
                    sym_num = fd.isymBase + leaf_sym.index
                    print('')
                elif leaf_sym.st == 10: # stTypedef
                    print_typedef_symbols(file_data, fd, symbolic_header, sym_num)
                    sym_num += 1
                    print('')
                elif leaf_sym.st == 6 or leaf_sym.st == 14: # stProc, stStaticProc
                    # TODO how do stProc and stStaticProc differ? stStaticProc isn't exported?
                    sym_num = print_procedure(file_data, fd, symbolic_header, sym_num)
                    print('')
                elif leaf_sym.st == 2: # stStatic
                    static_name = read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + leaf_sym.iss)
                    if leaf_sym.sc == 2 or leaf_sym.sc == 3 or leaf_sym.sc == 15: # scData, scBss, scRData
                        if leaf_sym.index != 0xFFFFF: # looks like it's an invalid value for .s files
                            print('static %s;\n' % get_type_string(file_data, fd, symbolic_header, leaf_sym.index, static_name, True))
                        else:
                            print('static %s;\n' % static_name)
                    else:
                         print('ERROR unkown sc for stStatic in print_symbols: %d' % leaf_sym.sc)
                    sym_num += 1
                else:
                    print('ERROR unkown st in leaf_sym in print_symbols: %d' % leaf_sym.st)
                    sym_num += 1
                leaf_sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
            sym_num = fd.isymBase + root_sym.index
            print('// end file %s' %  file_name)
        else:
            print('ERROR expected st of stFile as only root type in print_symbols:%d' % root_sym.st)
            return

def main():
    global OFFSET
    if len(sys.argv) < 2:
        return # TODO print usage

    filename = sys.argv[1]

    try:
        with open(filename, 'rb') as f:
            file_data = f.read()
    except IOError:
        print('failed to read file ' + filename)
        return

    elf_header = read_elf_header(file_data, 0)
    section_headers = []
    debug_index = 0xFFFFFFFF
    #print('%r' % (elf_header,))
    for i in range(elf_header.e_shnum):
        section_headers.append(read_elf_section_header(file_data, elf_header.e_shoff + i*40))
        #print('%r' % (section_headers[i],))
        if section_headers[i].sh_type == 0x70000005:
            debug_index = i

    if debug_index != 0xFFFFFFFF:
        symbolic_header = read_symbolic_header(file_data, section_headers[debug_index].sh_offset)
        file_descriptors = []
        print('%r' % (symbolic_header,))
        # Set offset by assuming that there are no optimization symbols so cbOptOffset points to the start of the symbolic header
        OFFSET = symbolic_header.cbOptOffset - section_headers[debug_index].sh_offset
        print('Using OFFSET of %d' % OFFSET)
        #for sym_num in range(symbolic_header.isymMax):
            #sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
            #print('%d:%r' % (sym_num, (sym,)));
        #for aux_num in range(symbolic_header.iauxMax):
            #aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + aux_num*4)
            #print('%d:%r' % (aux_num, (aux,)));
        for file_num in range(symbolic_header.ifdMax):
            fd = read_file_descriptor(file_data, symbolic_header.cbFdOffset - OFFSET + file_num*72)
            file_descriptors.append(fd)
        for file_num in range(symbolic_header.ifdMax):
            fd = read_file_descriptor(file_data, symbolic_header.cbFdOffset - OFFSET + file_num*72)
            print('%r' % (fd,))
            print('    name:%s' % read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + fd.rss))

            print('    procedures:')
            for proc_num in range(fd.ipdFirst, fd.ipdFirst + fd.cpd):
                pd = read_procedure_descriptor(file_data, symbolic_header.cbPdOffset - OFFSET + proc_num*52)
                print('        %r' % ((pd,)))

            print('    symbols:')
            for sym_num in range(fd.isymBase, fd.isymBase + fd.csym):
                sym = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + sym_num*12)
                print('        %r' % ((sym,)))
                print('            name:%s' % read_string(file_data, symbolic_header.cbSsOffset - OFFSET + fd.issBase + sym.iss))
                print('            type:%s(%d)' % (symbol_type_list[sym.st], sym.st))
                print('            storage class:%s(%d)' % (storage_class_list[sym.sc], sym.sc))
                if sym.st == 3 or sym.st == 4 or sym.st == 9 or sym.st == 10 or sym.st == 28: # stParam, stLocal, stMember, stTypedef, stEnum
                    aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + sym.index)*4)
                    print('            %r' % ((aux,)))
                    offset = 0
                    if aux.ti.fBitfield == 1:
                        bitfield_aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + sym.index + 1)*4)
                        print('            %r' % ((bitfield_aux,)))
                        offset = 1
                    if aux.ti.bt == 12 or aux.ti.bt == 13  or aux.ti.bt == 14 or aux.ti.bt == 15: # btStruct, btUnion, btEnum, btTypedef
                        aux2 = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + sym.index + 1 + offset)*4)
                        print('            %r' % ((aux2,)))
                        if aux2.rndx.rfd == 4095:
                            aux3 = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + sym.index + 2 + offset)*4)
                            print('            %r' % ((aux3,)))
                            sym2 = read_symbol(file_data, symbolic_header.cbSymOffset - OFFSET + (file_descriptors[aux3.isym].isymBase + aux2.rndx.index)*12)
                            print('                %r' % (sym2,))
                            print('                    name:%s' % read_string(file_data, symbolic_header.cbSsOffset - OFFSET + file_descriptors[aux3.isym].issBase + sym2.iss))
                if sym.st == 6: # stProc
                    # TODO what is the first aux symbol for?
                    aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + sym.index)*4)
                    type_aux = read_auxiliary_symbol(file_data, symbolic_header.cbAuxOffset - OFFSET + (fd.iauxBase + sym.index+1)*4)
                    print('            %r' % ((aux,)))
                    print('            %r' % ((type_aux,)))

            print('    pretty print:')
            print_symbols(file_data, fd, symbolic_header)


main()