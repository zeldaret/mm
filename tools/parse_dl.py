#!/usr/bin/env python3
import argparse, os, struct, ast

setcombine_a_names = [
    'COMBINED', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', '1', 'NOISE',
    '', '', '', '',
    '', '', '', '0',
]
setcombine_b_names = [
    'COMBINED', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', 'CENTER', 'K4',
    '', '', '', '',
    '', '', '', '0',
]
setcombine_c_names = [
    'COMBINED', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', 'SCALE', 'COMBINED_ALPHA',
    'TEXEL0_ALPHA', 'TEXEL1_ALPHA', 'PRIMITIVE_ALPHA', 'SHADE_ALPHA',
    'ENV_ALPHA', 'LOD_FRACTION', 'PRIM_LOD_FRAC', 'K5',
    '', '', '', '',
    '', '', '', '',
    '', '', '', '',
    '', '', '', '0',
]
setcombine_d_names = [
    'COMBINED', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', '1', '0',
    '', '', '', '',
    '', '', '', '',
]
setcombine_Aa_names = [
    'COMBINED', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', '1', '0',
]
setcombine_Ab_names = [
    'COMBINED', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', '1', '0',
]
setcombine_Ac_names = [
    'LOD_FRACTION', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', 'PRIM_LOD_FRAC', '0',
]
setcombine_Ad_names = [
    'COMBINED', 'TEXEL0', 'TEXEL1', 'PRIMITIVE',
    'SHADE', 'ENVIRONMENT', '1', '0',
]
setcombine_predefined = {
    '0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE':'G_CC_PRIMITIVE',
    '0, 0, 0, SHADE, 0, 0, 0, SHADE':'G_CC_SHADE',
    'TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE':'G_CC_MODULATEI',
    'TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0':'G_CC_MODULATEIA',
    'TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0':'G_CC_MODULATEIDECALA',
    'TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE':'G_CC_MODULATEI_PRIM',
    'TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0':'G_CC_MODULATEIA_PRIM',
    'TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0':'G_CC_MODULATEIDECALA_PRIM',
    '0, 0, 0, TEXEL0, 0, 0, 0, SHADE':'G_CC_DECALRGB',
    '0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0':'G_CC_DECALRGBA',
    'ENVIRONMENT, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE':'G_CC_BLENDI',
    'ENVIRONMENT, SHADE, TEXEL0, SHADE, TEXEL0, 0, SHADE, 0':'G_CC_BLENDIA',
    'ENVIRONMENT, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0':'G_CC_BLENDIDECALA',
    'TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, 0, 0, 0, SHADE':'G_CC_BLENDRGBA',
    'TEXEL0, SHADE, TEXEL0_ALPHA, SHADE, 0, 0, 0, TEXEL0':'G_CC_BLENDRGBDECALA',
    '1, 0, TEXEL0, SHADE, 0, 0, 0, SHADE':'G_CC_ADDRGB',
    '1, 0, TEXEL0, SHADE, 0, 0, 0, TEXEL0':'G_CC_ADDRGBDECALA',
    'ENVIRONMENT, 0, TEXEL0, SHADE, 0, 0, 0, SHADE':'G_CC_REFLECTRGB',
    'ENVIRONMENT, 0, TEXEL0, SHADE, 0, 0, 0, TEXEL0':'G_CC_REFLECTRGBDECALA',
    'PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE':'G_CC_HILITERGB',
    'PRIMITIVE, SHADE, TEXEL0, SHADE, PRIMITIVE, SHADE, TEXEL0, SHADE':'G_CC_HILITERGBA',
    'PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0':'G_CC_HILITERGBDECALA',
    '0, 0, 0, SHADE, 0, 0, 0, TEXEL0':'G_CC_SHADEDECALA',
    'PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, SHADE, 0':'G_CC_BLENDPE',
    'PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0':'G_CC_BLENDPEDECALA',
    'ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, SHADE, 0':'_G_CC_BLENDPE',
    'ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0':'_G_CC_BLENDPEDECALA',
    'PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE':'_G_CC_TWOCOLORTEX',
    'PRIMITIVE, TEXEL0, LOD_FRACTION, TEXEL0, PRIMITIVE, TEXEL0, LOD_FRACTION, TEXEL0':'_G_CC_SPARSEST',
    'TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0':'G_CC_TEMPLERP',
    'TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0':'G_CC_TRILERP',
    'TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, TEXEL1, 0':'G_CC_INTERFERENCE',
    'TEXEL0, K4, K5, TEXEL0, 0, 0, 0, SHADE':'G_CC_1CYUV2RGB',
    'TEXEL1, K4, K5, TEXEL1, 0, 0, 0, 0':'G_CC_YUV2RGB',
    '0, 0, 0, COMBINED, 0, 0, 0, COMBINED':'G_CC_PASS2',
    'COMBINED, 0, SHADE, 0, 0, 0, 0, SHADE':'G_CC_MODULATEI2',
    'COMBINED, 0, SHADE, 0, COMBINED, 0, SHADE, 0':'G_CC_MODULATEIA2',
    'COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE':'G_CC_MODULATEI_PRIM2',
    'COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0':'G_CC_MODULATEIA_PRIM2',
    'G_CC_MODULATEI_PRIM2':'G_CC_MODULATERGB_PRIM2',
    'G_CC_MODULATEIA_PRIM2':'G_CC_MODULATERGBA_PRIM2',
    '0, 0, 0, COMBINED, 0, 0, 0, SHADE':'G_CC_DECALRGB2',
    'ENVIRONMENT, SHADE, COMBINED, SHADE, 0, 0, 0, SHADE':'G_CC_BLENDI2',
    'ENVIRONMENT, SHADE, COMBINED, SHADE, COMBINED, 0, SHADE, 0':'G_CC_BLENDIA2',
    'TEXEL0, CENTER, SCALE, 0, 0, 0, 0, 0':'G_CC_CHROMA_KEY2',
    'ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, SHADE':'G_CC_HILITERGB2',
    'ENVIRONMENT, COMBINED, TEXEL0, COMBINED, ENVIRONMENT, COMBINED, TEXEL0, COMBINED':'G_CC_HILITERGBA2',
    'ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, TEXEL0':'G_CC_HILITERGBDECALA2',
    'ENVIRONMENT, COMBINED, TEXEL0, COMBINED, 0, 0, 0, COMBINED':'G_CC_HILITERGBPASSA2',
}

def read_file(name):
    file_data=[]

    try:
        with open(name, 'rb') as f:
            file_data = f.read()
    except IOError:
        print('failed to read file ' + name)
    return file_data


def read_uint16_be(file_data, offset):
    return struct.unpack('>h', file_data[offset:offset+2])[0]


def read_uint32_be(file_data, offset):
    return struct.unpack('>I', file_data[offset:offset+4])[0]


def get_cmd(inst):
    return (inst & 0b11111111000000000000000000000000) >> 24


def get_signed_imm(inst):
    imm = get_imm(inst)
    if (imm & (1 << 15)) != 0:
        imm = -2**15 + (imm & 0b00000000000000000111111111111111)
    return imm

def generate_output(self, path):
    with open(path + '/out', 'w', newline='\n') as f:
        f.write('#include <PR/gbi.h>\n'
                '\n'
                )

class Parser:

    class VertexList:
        def __init__(self, addr, length):
            self.addr = addr
            self.length = length

        def get_last_addr(self):
            return self.addr + self.length * 0x10

    class DisplayList:
        def __init__(self, addr, length):
            self.addr = addr
            self.length = length

        def get_last_addr(self):
            return self.addr + self.length * 8

    class Matrix:
        def __init__(self, addr):
            self.addr = addr

        def get_last_addr(self):
            return self.addr + 0x40

    def __init__(self, base_addr):
        self.base_addr = base_addr
        # TODO keep sorted, is_in_* functions can return early
        self.vertex_lists = []
        self.textures = [] # TODO check overlapping
        self.dls = [] # TODO check overlapping
        self.matrices = [] # TODO check overlapping

    def add_vertex_list(self, addr, length):
        #print('adding 0x{:08X} with length {}'.format(addr, length))
        new_list = self.VertexList(addr, length)
        overlapping_lists = []
        for i in range(length):
            if self.is_in_vertex_list(addr + i * 0x10):
                list = self.get_vertex_list(addr + i * 0x10)
                #print('Found overlapping list at 0x{:08X} with length {}'.format(list[0], list[1]))
                overlapping_lists.append(list)
                self.vertex_lists.remove(list)

        end_addr = new_list.get_last_addr()
        for list in overlapping_lists:
            if list.addr < addr:
                addr = list.addr
            if list.get_last_addr() > end_addr:
                end_addr = list.get_last_addr()

        self.vertex_lists.append(self.VertexList(addr, (end_addr - addr) // 0x10))

    def add_dl(self, addr, length):
        self.dls.append(self.DisplayList(addr, length))

    def add_matrix(self, addr):
        self.matrices.append(self.Matrix(addr))

    def is_in_vertex_list(self, addr):
        for list in self.vertex_lists:
            if (addr >= list.addr) and (addr < list.get_last_addr()):
                return True
        return False

    def is_in_texture(self, addr):
        for texture in self.textures:
            if texture[1] == 0:
                continue # size was not set
            if (addr >= texture[0]) and (addr < (texture[0] + texture[1])):
                return True
        return False

    def is_in_dl(self, addr):
        for dl in self.dls:
            if (addr >= dl.addr) and (addr < dl.get_last_addr()):
                return True
        return False

    def is_in_matrix(self, addr):
        for matrix in self.matrices:
            if (addr >= matrix.addr) and (addr < matrix.get_last_addr()):
                return True
        return False

    def get_vertex_list(self, addr):
        for list in self.vertex_lists:
            if (addr >= list.addr) and (addr < list.get_last_addr()):
                return list
        return None

    def get_texture(self, addr):
        for texture in self.textures:
            if texture[1] == 0:
                continue # size was not set
            if (addr >= texture[0]) and (addr < (texture[0] + texture[1])):
                return texture
        return None

    def get_dl(self, addr):
        for dl in self.dls:
            if (addr >= dl.addr) and (addr < dl.get_last_addr()):
                return dl
        return None

    def get_matrix(self, addr):
        for matrix in self.matrices:
            if (addr >= matrix.addr) and (addr < matrix.get_last_addr()):
                return matrix
        return None

    def parse_cmd(self, w0, w1):
        invalid = (False, False, 'Invalid') # Valid, IsEndOfDl, Print

        cmd = get_cmd(w0)

        # TODO for fields that get shifted before they are placed in microcode (e.g. vertices) , we should check that the lower bits are 0 for validity
        if cmd == 0x00: # G_NOOP
            if w0 == 0:
                if w1 == 0:
                    return (True, False, 'gsDPNoOp()')
                else:
                    return (True, False, 'gsDPNoOpTag({})'.format(w1))
            else:
                return invalid

        if cmd == 0x01: # G_VTX
            if (w0 & 0xFFF00F01)  == 0x01000000:
                vaddr = w1
                numv = (w0 & 0x000FF000) >> 12
                vbidx = ((w0 & 0x000000FE) >> 1) - numv
                if (numv < 1) or (numv > 32) or (vbidx < 0) or (vbidx > 31):
                    return invalid
                self.add_vertex_list(vaddr, numv)
                return (True, False, 'gsSPVertex(0x{:08X}, {}, {})'.format(vaddr, numv, vbidx))
            else:
                return invalid

        if cmd == 0x02: # G_MODIFYVTX
            where = (w0 & 0x00FF0000) >> 16
            vbidx = (w0 & 0x0000FFFF) // 2
            if vbidx > 31:
                return invalid
            if where == 0x10:
                where_str = 'G_MWO_POINT_RGBA'
            elif where == 0x14:
                where_str = 'G_MWO_POINT_ST'
            elif where == 0x18:
                where_str = 'G_MWO_POINT_XYSCREEN'
            elif where == 0x1C:
                where_str = 'G_MWO_POINT_ZSCREEN'
            else:
                return invalid
            return (True, False, 'gsSPModifyVertex({}, {}, 0x{:08X})'.format(vbidx, where_str, w1))

        if cmd == 0x03: # G_CULLDL
            if ((w0 & 0xFFFF0000) == 0x03000000) and ((w1 & 0xFFFF0000) == 0):
                vfirst = (w0 & 0x0000FFFF) // 2
                vlast = (w1 & 0x0000FFFF) // 2
                if vfirst > 31 or vlast > 31:
                    return invalid
                return (True, False, 'gsSPCullDisplayList({}, {})'.format(vfirst, vlast))
            else:
                return invalid

        if cmd == 0x04: # G_BRANCH_Z
            return (True, False, 'gsDPNoOp() # TODO G_BRANCH_Z')

        if cmd == 0x05: # G_TRI1
            if w1 == 0:
                v0 = ((w0 & 0x00FF0000) >> 16) // 2
                v1 = ((w0 & 0x0000FF00) >> 8) // 2
                v2 =  (w0 & 0x000000FF) // 2
                if (v0 < 0) or (v0 > 31):
                    return invalid
                if (v1 < 0) or (v1 > 31):
                    return invalid
                if (v2 < 0) or (v2 > 31):
                    return invalid
                return (True, False, 'gsSP1Triangle({}, {}, {}, 0)'.format(v0, v1, v2))
            else:
                return invalid

        if cmd == 0x06: # G_TRI2
            if (w1 & 0xFF000000) == 0:
                v00 = ((w0 & 0x00FF0000) >> 16) // 2
                v01 = ((w0 & 0x0000FF00) >> 8) // 2
                v02 =  (w0 & 0x000000FF) // 2
                v10 = ((w1 & 0x00FF0000) >> 16) // 2
                v11 = ((w1 & 0x0000FF00) >> 8) // 2
                v12 =  (w1 & 0x000000FF) // 2
                if (v00 < 0) or (v00 > 31):
                    return invalid
                if (v01 < 0) or (v01 > 31):
                    return invalid
                if (v02 < 0) or (v02 > 31):
                    return invalid
                if (v10 < 0) or (v10 > 31):
                    return invalid
                if (v11 < 0) or (v11 > 31):
                    return invalid
                if (v12 < 0) or (v12 > 31):
                    return invalid
                return (True, False, 'gsSP2Triangles({}, {}, {}, 0, {}, {}, {}, 0)'.format(v00, v01, v02, v10, v11, v12))
            else:
                return invalid

        if cmd == 0x07: # G_QUAD
            if (w1 & 0xFF000000) == 0:
                v00 = ((w0 & 0x00FF0000) >> 16) // 2
                v01 = ((w0 & 0x0000FF00) >> 8) // 2
                v02 =  (w0 & 0x000000FF) // 2
                v10 = ((w1 & 0x00FF0000) >> 16) // 2
                v11 = ((w1 & 0x0000FF00) >> 8) // 2
                v12 =  (w1 & 0x000000FF) // 2
                if (v00 < 0) or (v00 > 31):
                    return invalid
                if (v01 < 0) or (v01 > 31):
                    return invalid
                if (v02 < 0) or (v02 > 31):
                    return invalid
                if (v10 < 0) or (v10 > 31):
                    return invalid
                if (v11 < 0) or (v11 > 31):
                    return invalid
                if (v12 < 0) or (v12 > 31):
                    return invalid
                if (v00 != v10) or (v02 != v11):
                    return invalid
                return (True, False, 'gsSPQuadrangle({}, {}, {}, {}, 0)'.format(v00, v01, v02, v12))
            else:
                return invalid

        if cmd == 0xD6: # G_DMA_IO
            return (True, False, 'gsDPNoOp() # TODO G_DMA_IO')

        if cmd == 0xD7: # G_TEXTURE
            if (w0 & 0xFFFFC001) == 0xD7000000:
                level = (w0 & 0x00003800) >> 11
                tile =  (w0 & 0x00000700) >> 8
                on =    (w0 & 0x000000FE) >> 1
                scaleS = (w1 & 0xFFFF0000) >> 16
                scaleT = (w1 & 0x0000FFFF)
                if on != 0 and on != 1:
                    return invalid
                return (True, False, 'gsSPTexture(0x{:04X}, 0x{:04X}, {}, {}, {})'.format(scaleS, scaleT, level, tile, on))
            else:
                return invalid

        if cmd == 0xD8: # G_POPMTX
            if w0 == 0xD8380002:
                num = w1 // 64
                return (True, False, 'sSPPopMatrixN(G_MTX_MODELVIEW, {})'.format(num))
            else:
                return invalid

        if cmd == 0xD9: # G_GEOMETRYMODE
            return (True, False, 'gsDPNoOp() # TODO G_GEOMETRYMODE')

        if cmd == 0xDA: # G_MTX
            if (w0 & 0xFFFFFF00) == 0xDA380000:
                # TODO test other bits that should always be clear
                push = 'G_MTX_NOPUSH' if (w0 & 0b001) != 0 else 'G_MTX_PUSH' # G_MTX_PUSH is flipped in the macro
                mul_or_load = 'G_MTX_LOAD' if (w0 & 0b010) != 0 else 'G_MTX_MUL'
                model_or_proj = 'G_MTX_PROJECTION' if (w0 & 0b100) != 0 else 'G_MTX_MODELVIEW'
                self.add_matrix(w1)
                return (True, False, 'gsSPMatrix(0x{:08X}, {} | {} | {})'.format(w1, push, mul_or_load, model_or_proj))
            else:
                return invalid

        if cmd == 0xDB: # G_MOVEWORD
            return (True, False, 'gsDPNoOp() # TODO G_MOVEWORD')

        if cmd == 0xDC: # G_MOVEMEM
            return (True, False, 'gsDPNoOp() # TODO G_MOVEMEM')

        if cmd == 0xDD: # G_LOAD_UCODE
            return (True, False, 'gsDPNoOp() # TODO G_LOAD_UCODE')

        if cmd == 0xDE: # G_DL
            if (w0 & 0xFF00FFFF)  == 0xDE000000:
                type = (w0 & 0x00FF0000) >> 16
                if type == 0:
                    return (True, False, 'gsSPDisplayList(0x{:08X})'.format(w1))
                elif type == 1:
                    return (True, True, 'gsSPBranchList(0x{:08X})'.format(w1))
                else:
                    return invalid
                return (True, False, 'gsSPVertex(0x{:08X}, {}, {})'.format(vaddr, numv, vbidx))
            else:
                return invalid

        if cmd == 0xDF: # G_ENDDL
            if w0 == 0xDF000000 and w1 == 0:
                return (True, True, 'gsSPEndDisplayList()')
            else:
                return invalid

        if cmd == 0xE0: # G_SPNOOP
            if (w0 == 0xE0000000) and (w1 == 0):
                return (True, False, 'gsSPNoOp()')
            else:
                return invalid

        if cmd == 0xE1: # G_RDPHALF_1
            return (True, False, 'gsDPNoOp() # TODO G_RDPHALF_1')

        if cmd == 0xE2: # G_SETOTHERMODE_L
            if (w0 & 0xFFFF0000) == 0xE2000000:
                shift_base = (w0 & 0x0000FF00) >> 8
                length = (w0 & 0x000000FF) + 1
                shift = 32 - length - shift_base
                data = w1 >> shift
                if shift == 0: # G_MDSFT_ALPHACOMPARE
                    if data == 0:
                        type = 'G_AC_NONE'
                    elif data == 1:
                        type = 'G_AC_THRESHOLD'
                    elif data == 3:
                        type = 'G_AC_DITHER'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetAlphaCompare({})'.format(type))
                elif shift == 2: # G_MDSFT_ZSRCSEL
                    if data == 0:
                        src = 'G_ZS_PIXEL'
                    elif data == 1:
                        src = 'G_ZS_PRIM'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetDepthSource({})'.format(src))
                elif shift == 3: # G_MDSFT_RENDERMODE
                    ##return (True, False, 'gDPSetRenderMode({})'.format(c0, c1))
                    return (True, False, 'gsDPNoOp() # TODO G_MDSFT_RENDERMODE')
                else:
                    return invalid
                return
            else:
                return invalid

        if cmd == 0xE3: # G_SETOTHERMODE_H
            if (w0 & 0xFFFF0000) == 0xE3000000:
                shift_base = (w0 & 0x0000FF00) >> 8
                length = (w0 & 0x000000FF) + 1
                shift = 32 - length - shift_base
                if shift < 0:
                    return invalid
                data = w1 >> shift
                if shift == 0: # G_MDSFT_BLENDMASK
                    return invalid # This is not supported
                elif shift == 4: # G_MDSFT_ALPHADITHER
                    if length != 2:
                        return invalid
                    if data == 0:
                        type = 'G_AD_PATTERN'
                    elif data == 1:
                        type = 'G_AD_NOTPATTERN'
                    elif data == 2:
                        type = 'G_AD_NOISE'
                    elif data == 3:
                        type = 'G_AD_DISABLE'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetAlphaDither({})'.format(mode))
                elif shift == 6: # G_MDSFT_RGBDITHER
                    if length != 2:
                        return invalid
                    if data == 0:
                        type = 'G_CD_MAGICSQ'
                    elif data == 1:
                        type = 'G_CD_BAYER'
                    elif data == 2:
                        type = 'G_CD_NOISE'
                    elif data == 3:
                        type = 'G_CD_DISABLE'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetColorDither({})'.format(mode))
                elif shift == 8: # G_MDSFT_COMBKEY
                    if length != 1:
                        return invalid
                    if data == 0:
                        type = 'G_CK_NONE'
                    elif data == 1:
                        type = 'G_CK_KEY'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetCombineKey({})'.format(type))
                elif shift == 9: # G_MDSFT_TEXTCONV
                    if length != 3:
                        return invalid
                    if data == 0:
                        type = 'G_TC_CONV'
                    elif data == 5:
                        type = 'G_TC_FILTCONV'
                    elif data == 6:
                        type = 'G_TC_FILT'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetTextureConvert({})'.format(type))
                elif shift == 12: # G_MDSFT_TEXTFILT
                    if length != 2:
                        return invalid
                    if data == 0:
                        type = 'G_TF_POINT'
                    elif data == 2:
                        type = 'G_TF_AVERAGE'
                    elif data == 3:
                        type = 'G_TF_BILERP'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetTextureFilter({})'.format(type))
                elif shift == 14: # G_MDSFT_TEXTLUT
                    if length != 2:
                        return invalid
                    if data == 0:
                        type = 'G_TT_NONE'
                    elif data == 2:
                        type = 'G_TT_RGBA16'
                    elif data == 3:
                        type = 'G_TT_IA16'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetTextureLUT({})'.format(type))
                elif shift == 16: # G_MDSFT_TEXTLOD
                    if length != 1:
                        return invalid
                    if data == 0:
                        type = 'G_TL_TILE'
                    elif data == 1:
                        type = 'G_TL_LOD'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetTextureLOD({})'.format(type))
                elif shift == 17: # G_MDSFT_TEXTDETAIL
                    if length != 2:
                        return invalid
                    if data == 0:
                        type = 'G_TD_CLAMP'
                    elif data == 1:
                        type = 'G_TD_SHARPEN'
                    elif data == 2:
                        type = 'G_TD_DETAIL'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetTextureDetail({})'.format(type))
                elif shift == 19: # G_MDSFT_TEXTPERSP
                    if length != 1:
                        return invalid
                    if data == 0:
                        type = 'G_TP_NONE'
                    elif data == 1:
                        type = 'G_TP_PERSP'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetTexturePersp({})'.format(type))
                elif shift == 20: # G_MDSFT_CYCLETYPE
                    if length != 2:
                        return invalid
                    if data == 0:
                        type = 'G_CYC_1CYCLE'
                    elif data == 1:
                        type = 'G_CYC_2CYCLE'
                    elif data == 2:
                        type = 'G_CYC_COPY'
                    elif data == 3:
                        type = 'G_CYC_FILL'
                    else:
                        return invalid
                    return (True, False, 'gsDPSetCycleType({})'.format(type))
                elif shift == 22: # G_MDSFT_COLORDITHER
                    return invalid # G_MDSFT_COLORDITHER was changed to G_MDSFT_RGBDITHER in HW version 2
                elif shift == 23: # G_MDSFT_PIPELINE
                    if length != 1:
                        return invalid
                    if data == 0:
                        mode = 'G_PM_NPRIMITIVE'
                    elif data == 1:
                        mode = 'G_PM_1PRIMITIVE'
                    else:
                        return invalid
                    return (True, False, 'gsDPPipelineMode({})'.format(mode))
                else:
                    return invalid
                return
            else:
                return invalid

        if cmd == 0xE4: # G_TEXRECT
            return (True, False, 'gsDPNoOp() # TODO G_TEXRECT')

        if cmd == 0xE5: # G_TEXRECTFLIP
            return (True, False, 'gsDPNoOp() # TODO G_TEXRECTFLIP')

        if cmd == 0xE6: # G_RDPLOADSYNC
            if (w0 == 0xE6000000) and (w1 == 0):
                return (True, False, 'gsDPLoadSync()')
            else:
                return invalid

        if cmd == 0xE7: # G_RDPPIPESYNC
            if (w0 == 0xE7000000) and (w1 == 0):
                return (True, False, 'gsDPPipeSync()')
            else:
                return invalid

        if cmd == 0xE8: # G_RDPTILESYNC
            if (w0 == 0xE8000000) and (w1 == 0):
                return (True, False, 'gsDPTileSync()')
            else:
                return invalid

        if cmd == 0xE9: # G_RDPFULLSYNC
            if (w0 == 0xE9000000) and (w1 == 0):
                return (True, False, 'gsDPFullSync()')
            else:
                return invalid

        if cmd == 0xEA: # G_SETKEYGB
            return (True, False, 'gsDPNoOp() # TODO G_SETKEYGB')

        if cmd == 0xEB: # G_SETKEYR
            return (True, False, 'gsDPNoOp() # TODO G_SETKEYR')

        if cmd == 0xEC: # G_SETCONVERT
            return (True, False, 'gsDPNoOp() # TODO G_SETCONVERT')

        if cmd == 0xED: # G_SETSCISSOR
            return (True, False, 'gsDPNoOp() # TODO G_SETSCISSOR')

        if cmd == 0xEE: # G_SETPRIMDEPTH
            return (True, False, 'gsDPNoOp() # TODO G_SETPRIMDEPTH')

        if cmd == 0xEF: # G_RDPSETOTHERMODE
            return (True, False, 'gsDPNoOp() # TODO G_RDPSETOTHERMODE')

        if cmd == 0xF0: # G_LOADTLUT
            if (w0 == 0xF0000000) and ((w1 & 0xF8000FFF) == 0):
                tile = (w1 & 0x07000000) >> 24
                count = ((w1 & 0x00FFF000) >> 12) >> 2
                # TODO comment
                assert len(self.textures) > 0
                if self.textures[-1][1] == 0:
                    size_in_bytes = (count * self.textures[-1][2] + 5) // 8 # +5 to round up to byte
                    self.textures[-1] = (self.textures[-1][0], size_in_bytes, self.textures[-1][2])
              #  else:
               #     assert False # TODO
                return (True, False, 'gsDPLoadTLUTCmd({}, {})'.format(tile, count))
            else:
                return invalid

        if cmd == 0xF1: # G_RDPHALF_2
            return (True, False, 'gsDPNoOp() # TODO G_RDPHALF_2')

        if cmd == 0xF2: # G_SETTILESIZE
            if ((w0 & 0xFF000000) == 0xF2000000) and ((w1 & 0xF8000000) == 0):
                uls = (w0 & 0x00FFF000) >> 12
                ult = (w0 & 0x00000FFF)
                tile = (w1 & 0x07000000) >> 24
                lrs = (w1 & 0x00FFF000) >> 12
                lrt = (w1 & 0x00000FFF)
                return (True, False, 'gsDPSetTileSize({}, {}, {}, {}, {})'.format(tile, uls, ult, lrs, lrt))
            else:
                return invalid

        if cmd == 0xF3: # G_LOADBLOCK
            if (w1 & 0xF8000000) == 0:
                uls = (w0 & 0x00FFF000) >> 12
                ult = (w0 & 0x00000FFF)
                tile = (w1 & 0x07000000) >> 16
                texels = (w1 & 0x00FFF000) >> 12
                dxt = (w1 & 0x00000FFF)
                # TODO comment
                assert len(self.textures) > 0
                if self.textures[-1][1] == 0:
                    size_in_bytes = ((texels + 1) * self.textures[-1][2] + 5) // 8 # +5 to round up to byte
                    self.textures[-1] = (self.textures[-1][0], size_in_bytes, self.textures[-1][2])
              #  else:
               #     assert False # TODO
                return (True, False, 'gsDPLoadBlock({}, {}, {}, {}, {})'.format(tile, uls, ult, texels, dxt))
            else:
                return invalid

        if cmd == 0xF4: # G_LOADTILE
            return (True, False, 'gsDPNoOp() # TODO G_LOADTILE')

        if cmd == 0xF5: # G_SETTILE
            # TODO check illegal combinations
            if ((w0 & 0xFF040000) == 0xF5000000) and ((w1 & 0xF8000000) == 0):
                fmt = (w0 & 0x00E00000) >> 21
                siz = (w0 & 0x00180000) >> 19
                line = (w0 & 0x0003FE00) >> 9
                tmem = (w0 & 0x000001FF)
                tile = (w1 & 0x07000000) >> 24
                palette = (w1 & 0x00F00000) >> 20
                cmT = (w1 & 0x000C0000) >> 18
                maskT = (w1 & 0x0003C000) >> 14
                shiftT = (w1 & 0x00003C00) >> 10
                cmS = (w1 & 0x00000300) >> 8
                maskS = (w1 & 0x000000F0) >> 4
                shiftS = (w1 & 0x0000000F)
                if fmt == 0:
                    fmt_str = 'G_IM_FMT_RGBA'
                elif fmt == 1:
                    fmt_str = 'G_IM_FMT_YUV'
                elif fmt == 2:
                    fmt_str = 'G_IM_FMT_CI'
                elif fmt == 3:
                    fmt_str = 'G_IM_FMT_IA'
                elif fmt == 4:
                    fmt_str = 'G_IM_FMT_I'
                else:
                    return invalid
                if siz == 0:
                    siz_str = 'G_IM_SIZ_4b'
                elif siz == 1:
                    siz_str = 'G_IM_SIZ_8b'
                elif siz == 2:
                    siz_str = 'G_IM_SIZ_16b'
                elif siz == 3:
                    siz_str = 'G_IM_SIZ_32b'
                else:
                    return invalid
                mirror_t = 'G_TX_MIRROR' if (cmT & 0b01) != 0 else 'G_TX_NOMIRROR'
                wrap_or_clamp_t = 'G_TX_CLAMP' if (cmT & 0b10) != 0 else 'G_TX_WRAP'
                mirror_s = 'G_TX_MIRROR' if (cmS & 0b01) != 0 else 'G_TX_NOMIRROR'
                wrap_or_clamp_s = 'G_TX_CLAMP' if (cmS & 0b10) != 0 else 'G_TX_WRAP'
                return (True, False, 'gsDPSetTile({}, {}, {}, {}, {}, {}, {} | {}, {}, {}, {} | {}, {}, {})'.format(fmt_str, siz_str, line, tmem, tile, palette, mirror_t, wrap_or_clamp_t, maskT, shiftT, mirror_s, wrap_or_clamp_s, maskS, shiftS))
            else:
                return invalid

        if cmd == 0xF6: # G_FILLRECT
            if ((w0 & 0xFF003003) == 0xF60000) and ((w1 & 0xFF003003) == 0):
                lrx = (w0 & 0x00FFC000) >> 14
                lry = (w0 & 0x00000FFC) >> 2
                ulx = (w1 & 0x00FFC000) >> 14
                uly = (w1 & 0x00000FFC) >> 2
                return (True, False, 'gsDPFillRectangle({}, {}, {}, {})'.format(ulx, uly, lrx, lry))
            else:
                return invalid

        if cmd == 0xF7: # G_SETFILLCOLOR
            if w0 == 0xF7000000:
                return (True, False, 'gsDPSetFillColor(0x{:08X})'.format(w1))
            else:
                return invalid

        if cmd == 0xF8: # G_SETFOGCOLOR
            if w0 == 0xF8000000:
                red = (w1 & 0xFF000000) >> 24
                green = (w1 & 0x00FF0000) >> 16
                blue = (w1 & 0x0000FF00) >> 8
                alpha = (w1 & 0x000000FF)
                return (True, False, 'gsDPSetFogColor({}, {}, {}, {})'.format(red, green, blue, alpha))
            else:
                return invalid

        if cmd == 0xF9: # G_SETBLENDCOLOR
            if w0 == 0xF9000000:
                red = (w1 & 0xFF000000) >> 24
                green = (w1 & 0x00FF0000) >> 16
                blue = (w1 & 0x0000FF00) >> 8
                alpha = (w1 & 0x000000FF)
                return (True, False, 'gsDPBlendColor({}, {}, {}, {})'.format(red, green, blue, alpha))
            else:
                return invalid

        if cmd == 0xFA: # G_SETPRIMCOLOR
            if (w0 & 0xFFFF0000) == 0xFA000000:
                minlevel = (w0 & 0x0000FF00) >> 8
                lodfrac = (w0 & 0x000000FF)
                red = (w1 & 0xFF000000) >> 24
                green = (w1 & 0x00FF0000) >> 16
                blue = (w1 & 0x0000FF00) >> 8
                alpha = (w1 & 0x000000FF)
                return (True, False, 'gsDPSetPrimColor({}, {}, {}, {}, {}, {})'.format(minlevel, lodfrac, red, green, blue, alpha))
            else:
                return invalid

        if cmd == 0xFB: # G_SETENVCOLOR
            if w0 == 0xFB000000:
                red = (w1 & 0xFF000000) >> 24
                green = (w1 & 0x00FF0000) >> 16
                blue = (w1 & 0x0000FF00) >> 8
                alpha = (w1 & 0x000000FF)
                return (True, False, 'gsDPSetEnvColor({}, {}, {}, {})'.format(red, green, blue, alpha))
            else:
                return invalid

        if cmd == 0xFC: # G_SETCOMBINE
            a0 =  (w0 & 0x00F00000) >> 20
            c0 =  (w0 & 0x000F8000) >> 15
            Aa0 = (w0 & 0x00007000) >> 12
            Ac0 = (w0 & 0x00000E00) >> 9
            a1 =  (w0 & 0x000001E0) >> 5
            c1 =  (w0 & 0x0000001F)
            b0 =  (w1 & 0xF0000000) >> 28
            b1 =  (w1 & 0x0F000000) >> 24
            Aa1 = (w1 & 0x00E00000) >> 21
            Ac1 = (w1 & 0x001C0000) >> 18
            d0 =  (w1 & 0x00038000) >> 15
            Ab0 = (w1 & 0x00007000) >> 12
            Ad0 = (w1 & 0x00000E00) >> 9
            d1 =  (w1 & 0x000001C0) >> 6
            Ab1 = (w1 & 0x00000038) >> 3
            Ad1 = (w1 & 0x00000007)
            param_str_c0 = '{}, {}, {}, {}, {}, {}, {}, {}'.format(
                setcombine_a_names[a0],
                setcombine_b_names[b0],
                setcombine_c_names[c0],
                setcombine_d_names[d0],
                setcombine_Aa_names[Aa0],
                setcombine_Ab_names[Ab0],
                setcombine_Ac_names[Ac0],
                setcombine_Ad_names[Ad0],
                )
            if param_str_c0.startswith(',') or (', ,' in param_str_c0): # one of the names was empty, meaning it was invalid
                return invalid
            param_str_c1 = '{}, {}, {}, {}, {}, {}, {}, {}'.format(
                setcombine_a_names[a1],
                setcombine_b_names[b1],
                setcombine_c_names[c1],
                setcombine_d_names[d1],
                setcombine_Aa_names[Aa1],
                setcombine_Ab_names[Ab1],
                setcombine_Ac_names[Ac1],
                setcombine_Ad_names[Ad1],
                )
            if param_str_c1.startswith(',') or (', ,' in param_str_c1): # one of the names was empty, meaning it was invalid
                return invalid
            if (param_str_c0 in setcombine_predefined) and (param_str_c1 in setcombine_predefined):
                return (True, False, 'gsDPSetCombineMode({}, {})'.format(setcombine_predefined[param_str_c0], setcombine_predefined[param_str_c1]))
            else:
                return (True, False, 'gsDPSetCombineLERP({}, {})'.format(param_str_c0, param_str_c1))

        if cmd == 0xFD: # G_SETTIMG
            if (w0 & 0xFF07F000) == 0xFD000000:
                fmt = (w0 & 0x00E00000) >> 21
                siz = (w0 & 0x00180000) >> 19
                width = (w0 & 0x00000FFF) + 1
                # TODO check valid fmt and siz combinations?
                # TODO util functions
                if fmt == 0:
                    fmt_str = 'G_IM_FMT_RGBA'
                elif fmt == 1:
                    fmt_str = 'G_IM_FMT_YUV'
                elif fmt == 2:
                    fmt_str = 'G_IM_FMT_CI'
                elif fmt == 3:
                    fmt_str = 'G_IM_FMT_IA'
                elif fmt == 4:
                    fmt_str = 'G_IM_FMT_I'
                else:
                    return invalid
                if siz == 0:
                    siz_str = 'G_IM_SIZ_4b'
                    siz_bits = 4
                elif siz == 1:
                    siz_str = 'G_IM_SIZ_8b'
                    siz_bits = 8
                elif siz == 2:
                    siz_str = 'G_IM_SIZ_16b'
                    siz_bits = 16
                elif siz == 3:
                    siz_str = 'G_IM_SIZ_32b'
                    siz_bits = 32
                elif siz == 5:
                    siz_str = 'G_IM_SIZ_DD'
                    siz_bits = 0
                    assert False, "TODO G_IM_SIZ_DD size"
                else:
                    return invalid
                self.textures.append((w1, 0, siz_bits))
                return (True, False, 'gsDPSetTextureImage({}, {}, {}, 0x{:08X})'.format(fmt_str, siz_str, width, w1))
            else:
                return invalid

        if cmd == 0xFE: # G_SETZIMG
            if (w0 == 0xFE000000):
                return (True, False, 'gsDPSetDepthImage(0x{:08X})'.format(w1))
            else:
                return invalid

        if cmd == 0xFF: # G_SETCIMG
            return (True, False, 'gsDPNoOp() # TODO G_SETCIMG')

        return invalid

    def find_dls(self, file_info):
        is_in_dl = False
        for i in range(len(file_info) - 1, -1, -1):
            info = file_info[i]
            addr = self.base_addr + i * 8
            if self.is_in_vertex_list(addr) or self.is_in_texture(addr):
                if is_in_dl: # previous dl ended and we are not in a new one
                    self.add_dl(addr + 8, (dl_end_addr - addr) // 8)
                is_in_dl = False
            elif not info[0]:
                if is_in_dl: # previous dl ended and we are not in a new one
                    self.add_dl(addr + 8, (dl_end_addr - addr) // 8)
                is_in_dl = False
            if info[1] and not is_in_dl:
                is_in_dl = True
                dl_end_addr = addr
            elif info[1] and is_in_dl: # previous dl ended and we are in a new one
                self.add_dl(addr + 8, (dl_end_addr - addr) // 8)
                dl_end_addr = addr

        if is_in_dl:
            self.add_dl(self.base_addr, (dl_end_addr - self.base_addr) // 8)

    def extract_models(self, dir, file_data):
        if len(self.dls) == 0:
            return

        for dl in self.dls:
            verts = dict()
            global_vert_index = 1
            active_verts = [None] * 32
            tris = []

            for i in range(dl.length):
                w0 = read_uint32_be(file_data, dl.addr - self.base_addr + i * 8)
                w1 = read_uint32_be(file_data, dl.addr - self.base_addr + i * 8 + 4)

                cmd = get_cmd(w0)

                if cmd == 0x01: # G_VTX
                    vaddr = w1
                    numv = (w0 & 0x000FF000) >> 12
                    vbidx = ((w0 & 0x000000FF) >> 1) - numv
                    for vertex_index in range(numv):
                        vert_addr = vaddr - self.base_addr + vertex_index * 0x10
                        if vert_addr not in verts:
                            x = read_uint16_be(file_data, vert_addr)
                            y = read_uint16_be(file_data, vert_addr + 2)
                            z = read_uint16_be(file_data, vert_addr + 4)
                            verts[vert_addr] = (x, y, z, global_vert_index)
                            global_vert_index += 1
                        active_verts[vbidx + vertex_index] = verts[vert_addr]

                if cmd == 0x05: # G_TRI1
                    v0 = ((w0 & 0x00FF0000) >> 16) // 2
                    v1 = ((w0 & 0x0000FF00) >> 8) // 2
                    v2 =  (w0 & 0x000000FF) // 2
                    tris.append((active_verts[v0][3], active_verts[v1][3], active_verts[v2][3]))

                if cmd == 0x06: # G_TRI2
                    v00 = ((w0 & 0x00FF0000) >> 16) // 2
                    v01 = ((w0 & 0x0000FF00) >> 8) // 2
                    v02 =  (w0 & 0x000000FF) // 2
                    v10 = ((w1 & 0x00FF0000) >> 16) // 2
                    v11 = ((w1 & 0x0000FF00) >> 8) // 2
                    v12 =  (w1 & 0x000000FF) // 2
                    tris.append((active_verts[v00][3], active_verts[v01][3], active_verts[v02][3]))
                    tris.append((active_verts[v10][3], active_verts[v11][3], active_verts[v12][3]))

            if len(verts) > 0 and len(tris) > 0:
                with open('{}/0x{:08X}.obj'.format(dir, dl.addr), 'w') as f:
                    for addr, vert in sorted(verts.items(), key=lambda vert: vert[1][3]):
                        f.write('v {} {} {}\n'.format(vert[0], vert[1], vert[2]))
                    f.write('\n')
                    for tri in tris:
                        f.write('f {} {} {}\n'.format(tri[0], tri[1], tri[2]))


    def parse(self, file_data):
        file_info = []
        for i in range(len(file_data) // 8):
            w0 = read_uint32_be(file_data, i * 8)
            w1 = read_uint32_be(file_data, i * 8 + 4)
            file_info.append(self.parse_cmd(w0, w1))

        self.find_dls(file_info)

        return file_info

    def print_info(self, file_data, file_info):
        num_in_dls = 0
        for dl in self.dls:
            num_in_dls += dl.length
        print('DLs:{}({}) Vertex Lists:{} Textures:{}'.format(len(self.dls), num_in_dls, len(self.vertex_lists), len(self.textures)))
        start_addr = self.base_addr

#        for texture in self.textures:
#            print('0x{:08X} {}'.format(texture[0], texture[1]))

        # TODO assert that vertex lists and textures start on the address
        i = 0
        while(i < len(file_info)):
            addr = start_addr + i*8
            if self.is_in_vertex_list(addr):
                list = self.get_vertex_list(addr)
                print('0x{:08X}: Vertex[{}]'.format(addr, list.length))
#                for vertex in range(list.length):
#                    x = read_uint16_be(file_data, list.addr - self.base_addr + vertex * 0x10)
#                    y = read_uint16_be(file_data, list.addr - self.base_addr + vertex * 0x10 + 2)
#                    z = read_uint16_be(file_data, list.addr - self.base_addr + vertex * 0x10 + 4)
#                    print('{} {} {}'.format(x, y, z))
                i += list.length * 2
                continue
            elif self.is_in_texture(addr):
                length = self.get_texture(addr)[1]
                print('0x{:08X}: Texture(0x{:X} bytes)'.format(addr, length))
                i += (length + 7) // 8 # +7 to align up to double word
                continue
            elif self.is_in_dl(addr):
                length = self.get_dl(addr).length
                print('0x{:08X}: Dl[{}]'.format(addr, length))
                for dl_cmd in range(length):
                    print('    {}'.format(file_info[i+dl_cmd][2]))
                i += length
                continue
            elif self.is_in_matrix(addr):
                print('0x{:08X}: Matrix'.format(addr))
                i += 8
                continue
            else:
                print('0x{:08X}: {}, {}, {}'.format(addr, file_info[i][0], file_info[i][1], file_info[i][2]))
                i += 1
                continue

        #self.extract_models('test/', file_data)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('input', help='input file to parse', metavar='file')
    args = parser.parse_args()

    file_data = read_file(args.input)

    parser = Parser(0x04000000) # TODO take in base addr
    file_info = parser.parse(file_data)
    parser.print_info(file_data, file_info)

