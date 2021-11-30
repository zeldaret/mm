#include "global.h"

extern u16* D_801FBB9C;
extern u16* D_801FBBA0;
extern u16* D_801FBBB4;
extern u16* D_801FBBB8;
extern u16* D_801FBBBC;
extern void* D_801FBBC0;
extern s16 D_801FBBD0;
extern s16 D_801FBBD2;
extern s8 D_801FBBD4;

typedef struct {
    /* 0x00 */ u32 unk_00;
    /* 0x00 */ u32 unk_04;
} CmpDmaBssStruct;

static CmpDmaBssStruct D_801FBBE0;

void func_80178750(void) {
    gFramebuffers[1] = D_801FBB9C;
    gFramebuffers[0] = D_801FBBA0;
    gZBufferPtr = *gZBuffer;
    D_801FBB90 = gWorkBuffer;
    gGfxSPTaskOutputBufferPtr = *gGfxSPTaskOutputBuffer;
    gGfxSPTaskOutputBufferSize = gGfxSPTaskOutputBufferEnd;
    D_801FBBCC = SCREEN_WIDTH;
    D_801FBBCE = SCREEN_HEIGHT;
    D_801FBBD0 = 0;
    D_801FBBD2 = 0;
    D_801FBBD4 = 0;
    gScreenWidth = D_801FBBCC;
    gScreenHeight = D_801FBBCE;
    D_801FBB88 = &osViModeNtscLan1;
}

void func_80178818(void) {
    s32 width;
    s32 height;

    gFramebuffers[1] = D_801FBBB4;
    gFramebuffers[0] = D_801FBBB8;
    gZBufferPtr = D_801FBBBC;
    D_801FBB90 = D_801FBBC0;
    gGfxSPTaskOutputBufferPtr = *gGfxSPTaskOutputBuffer2;
    gGfxSPTaskOutputBufferSize = gGfxSPTaskOutputBufferEnd2;

    if (1) {}

    D_801FBBCC = SCREEN_WIDTH_HIGH_RES;
    D_801FBBCE = SCREEN_HEIGHT_HIGH_RES;

    D_801FBBD0 = 30;
    D_801FBBD2 = 10;

    gScreenWidth = D_801FBBCC;
    gScreenHeight = D_801FBBCE;

    if ((D_801FBBCC == 640) && (D_801FBBCE == 480)) {
        D_801FBB88 = &osViModeNtscHpf1;
    } else {
    dummy:
        width = D_801FBBCC - 610;
        height = D_801FBBCE - 470;

        func_8014026C(&D_801FBB30, -1, osTvType, 0, 1, 0, 1, D_801FBBCC, D_801FBBCE, 30, width, 10, height);
        D_801FBB88 = &D_801FBB30;
    }
    D_801FBBD4 = 1;
}

#ifdef NON_MATCHING
// need to reload gFramebuffer1, volatile not working?
void func_80178978(void) {
    D_801FBB9C = (u16*)gFramebuffer1;
    D_801FBBA0 = (u16*)gFramebuffer0;
    D_801FBBB4 = (u16*)gFramebuffer1;
    D_801FBBB8 = D_80780000;
    func_80178750();
}
#else
void func_80178978(void);
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178978.s")
#endif

void func_801789D4(void) {
    gFramebuffers[0] = NULL;
    gFramebuffers[1] = NULL;
}

u32 SysCfb_GetFbPtr(s32 index) {
    if (index < 2) {
        return gFramebuffers[index];
    }
    return 0;
}

u16* SysCfb_GetZBuffer(void) {
    return gZBufferPtr;
}

void* func_80178A24(void) {
    return D_801FBB90;
}

s32 func_80178A34(s32 arg0, s32 arg1) {
    u16* zBuff = SysCfb_GetZBuffer();
    s32 ret;

    if (zBuff != NULL) {
        ret = *(zBuff + arg0 + (arg1 * D_801FBBCC));
    } else {
        ret = 0;
    }
    return ret;
}

s32 func_80178A94(s32 arg0, s32 arg1) {
    return func_800F50D4(func_80178A34(arg0, arg1) * 4) >> 3;
}

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

#ifdef NON_MATCHING
// Some constants re-ordered at the top
void func_80178AC0(u16* arg0, s32* arg1, u32 arg2) {
    Struct1_80178AC0 spC;
    Struct2_80178AC0 sp8;
    Struct2_80178AC0 sp4;
    s32* phi_v0 = arg1;
    u16* phi_v1 = arg0;
    u32 tempsp4;
    u32 tempsp8;
    s32* phi_a0;

    if ((u32)((u8*)arg1 - (arg2 & 0xFFFFFFFFFFFFFFFF)) >= (u32)arg1) {
        return;
    }

    phi_a0 = (s32*)((u8*)arg1 - arg2);

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
    } while ((u32)phi_a0 < (u32)arg1);
}
#else
void func_80178AC0(u16* arg0, s32* arg1, u32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/code/sys_cmpdma/func_80178AC0.s")
#endif

void func_80178C80(u8* vrom, s32 arg1, s32* arg2, s32* arg3, s32* arg4) {
    u32 sp24;
    u32 temp_v0;

    DmaMgr_DMARomToRam(vrom, (void*)&D_801FBBE0, 4);

    sp24 = D_801FBBE0.unk_00;
    temp_v0 = arg1 * 4;

    if ((sp24 - 4) < temp_v0) {
        *arg2 = vrom;
        *arg3 = 0;
    } else if (temp_v0 == 0) {
        DmaMgr_DMARomToRam(vrom + 4, (void*)&D_801FBBE0, 4);
        *arg2 = vrom + sp24;
        *arg3 = D_801FBBE0.unk_00;
    } else {
        DmaMgr_DMARomToRam(temp_v0 + vrom, (void*)&D_801FBBE0, 8);
        *arg2 = D_801FBBE0.unk_00 + vrom + sp24;
        *arg3 = D_801FBBE0.unk_04 - D_801FBBE0.unk_00;
    }
    *arg4 = 0;
}

void func_80178D7C(s32 romStart, s32 size, void* dst) {
    if (size != 0) {
        Yaz0_Decompress(romStart, dst, size);
    }
}

void func_80178DAC(u32 vrom, s32 arg1, s32 arg2, s32 arg3) {
    s32 romStart;
    s32 size;
    s32 sp24;
    void* dst;

    func_80178C80(vrom, arg1, &romStart, &size, &sp24);
    if (sp24 & 1) {
        dst = SystemArena_Malloc(0x1000);
        func_80178D7C(romStart, size, dst);
        func_80178AC0(dst, arg2, arg3);
        SystemArena_Free(dst);
    } else {
        func_80178D7C(romStart, size, arg2);
    }
}

void func_80178E3C(u32 vrom, s32 arg1, s32 arg2, s32 arg3) {
    func_80178DAC(DmaMgr_TranslateVromToRom(vrom), arg1, arg2, arg3);
}

void func_80178E7C(u32 arg0, s32 arg1, s32 arg2) {
    u32 temp_s2 = DmaMgr_TranslateVromToRom(arg0);
    u32 i;
    u32 end;
    s32 phi_s1;
    u32 var;

    DmaMgr_DMARomToRam(temp_s2, (void*)&D_801FBBE0, sizeof(u32));

    var = D_801FBBE0.unk_00;
    phi_s1 = arg1;
    end = (var >> 2) - 1;

    for (i = 0; i < end; i++) {
        func_80178DAC(temp_s2, i, phi_s1, 0);
        phi_s1 = D_8009BE20;
    }
}
