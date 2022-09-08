#include "global.h"
#include "system_malloc.h"

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178750.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178818.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178978.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_801789D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/SysCfb_GetFbPtr.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/SysCfb_GetZBuffer.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178A94.s")

typedef union {
    struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };
    s32 rgba;
} Struct1_80178AC0;

typedef union {
    u16 a, b;
    s32 ab;
} Struct2_80178AC0;

typedef struct {
    /* 0x00 */ u32 data1;
    /* 0x00 */ u32 data2;
} CmpDmaBssStruct;

// static CmpDmaBssStruct D_801FBBE0;
extern CmpDmaBssStruct D_801FBBE0;

#ifdef NON_MATCHING
// Some constants re-ordered at the top
void func_80178AC0(u16* src, void* dst, u32 size) {
    Struct1_80178AC0 spC;
    Struct2_80178AC0 sp8;
    Struct2_80178AC0 sp4;
    s32* phi_v0 = dst;
    u16* phi_v1 = src;
    u32 tempsp4;
    u32 tempsp8;
    s32* phi_a0;

    if ((u32)((u8*)dst - (size & 0xFFFFFFFFFFFFFFFF)) >= (u32)dst) {
        return;
    }

    phi_a0 = (s32*)((u8*)dst - size);

    do {
        sp8.a = *(phi_v1++);
        phi_a0++;

        if ((sp8.a & 1) == 1) {
            tempsp8 = sp8.ab;

            spC.r = ((tempsp8 >> 0x1B) * 0xFF) / 31;
            spC.g = (((tempsp8 << 5) >> 0x1B) * 0xFF) / 31;
            spC.b = (((tempsp8 << 0xA) >> 0x1B) * 0xFF) / 31;
            spC.a = 0xFF;

        } else if (sp8.a == 0) {
            spC.rgba = 0;

        } else {
            sp4.a = sp8.a;
            sp8.a = *(phi_v1++);

            tempsp4 = sp4.ab;
            tempsp8 = sp8.ab;

            spC.r = ((tempsp8 >> 0x1B) * 8) | (tempsp4 >> 0x1D);
            spC.g = (((tempsp8 << 5) >> 0x1B) * 8) | ((tempsp4 * 8) >> 0x1D);
            spC.b = (((tempsp8 << 0xA) >> 0x1B) * 8) | ((tempsp4 << 6) >> 0x1D);
            tempsp8 = sp8.a;
            spC.a = ((tempsp8 & 1) << 7) | ((((tempsp4 << 9) >> 0x1B) * 0x7F) / 63);
        }

        *(phi_v0++) = spC.rgba;
    } while ((u32)phi_a0 < (u32)dst);
}
#else
void func_80178AC0(u16* src, void* dst, u32 size);
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178AC0.s")
#endif

void func_80178C80(u8* vrom, s32 id, s32* start, s32* size, s32* flag) {
    u32 dataStart;
    u32 refOff;

    DmaMgr_DmaRomToRam(vrom, (void*)&D_801FBBE0, sizeof(u32));

    dataStart = D_801FBBE0.data1;
    refOff = id * sizeof(u32);

    // if id is >= idMax
    if (refOff > (dataStart - 4)) {
        *start = vrom;
        *size = 0;
    } else if (refOff == 0) {
        // get offset start of next file, i.e. size of first file
        DmaMgr_DmaRomToRam(vrom + 4, (void*)&D_801FBBE0, sizeof(u32));
        *start = vrom + dataStart;
        *size = D_801FBBE0.data1;
    } else {
        // get offset start, offset end from dataStart
        DmaMgr_DmaRomToRam(refOff + vrom, (void*)&D_801FBBE0, sizeof(u32) * 2);
        *start = D_801FBBE0.data1 + vrom + dataStart;
        *size = D_801FBBE0.data2 - D_801FBBE0.data1;
    }
    *flag = 0;
}

void func_80178D7C(s32 romStart, s32 size, void* dst) {
    if (size != 0) {
        Yaz0_Decompress(romStart, dst, size);
    }
}

void func_80178DAC(u32 vrom, s32 id, void* dst, s32 size) {
    s32 romStart;
    s32 compressedSize;
    s32 flag;

    func_80178C80(vrom, id, &romStart, &compressedSize, &flag);
    if (flag & 1) {
        void* temp = SystemArena_Malloc(0x1000);
        func_80178D7C(romStart, compressedSize, temp);
        func_80178AC0(temp, dst, size);
        SystemArena_Free(temp);
    } else {
        func_80178D7C(romStart, compressedSize, dst);
    }
}

void func_80178E3C(uintptr_t vrom, s32 id, void* dst, s32 size) {
    func_80178DAC(DmaMgr_TranslateVromToRom(vrom), id, dst, size);
}

void func_80178E7C(uintptr_t vrom, void* dst, s32 arg2) {
    u32 temp_s2 = DmaMgr_TranslateVromToRom(vrom);
    u32 i;
    u32 end;
    s32 phi_s1;
    u32 var;

    DmaMgr_DmaRomToRam(temp_s2, (void*)&D_801FBBE0, sizeof(u32));

    var = D_801FBBE0.data1;
    phi_s1 = dst;
    end = (var >> 2) - 1;

    for (i = 0; i < end; i++) {
        func_80178DAC(temp_s2, i, phi_s1, 0);
        phi_s1 = D_8009BE20;
    }
}
