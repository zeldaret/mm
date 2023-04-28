#include "global.h"

extern int TEXEL0;
extern int PRIMITIVE;
extern int ENVIRONMENT;

// Segment 0x07 schedule_dma_static_test
extern TexturePtr D_07000000;
extern TexturePtr D_07000800;
extern TexturePtr D_07001000;
extern TexturePtr D_07001800;
extern TexturePtr D_07002000;
extern TexturePtr D_07002800;
extern TexturePtr D_07003000;
extern TexturePtr D_07003800;
extern TexturePtr D_07004000;
extern TexturePtr D_07004800;
extern TexturePtr D_07005000;
extern TexturePtr D_07005800;
extern TexturePtr D_07006000;
extern TexturePtr D_07006800;
extern TexturePtr D_07007000;
extern TexturePtr D_07007800;
extern TexturePtr D_07008000;
extern TexturePtr D_07008800;
extern TexturePtr D_07009000;
extern TexturePtr D_07009800;
extern TexturePtr D_0700AC00;
extern TexturePtr D_0700AEA0;

// Segment 0x08 schedule_static
extern TexturePtr D_08000000;
extern TexturePtr D_08000100;
extern TexturePtr D_08000700;
extern TexturePtr D_08000880;
extern TexturePtr D_08000A40;
extern TexturePtr D_08001240;
extern TexturePtr D_080012C0;
extern TexturePtr D_08001340;
extern TexturePtr D_08001358;
extern TexturePtr D_080013D8;
extern TexturePtr D_080017D8;
extern TexturePtr D_08001898;
extern TexturePtr D_080018B0;
extern TexturePtr D_080018D0;
extern TexturePtr D_08001950;
extern TexturePtr D_08001CD0;
extern TexturePtr D_08001DB0;
extern TexturePtr D_08001E90;
extern TexturePtr D_08001F70;
extern TexturePtr D_08002078;
extern TexturePtr D_08002100;
extern TexturePtr D_08002188;
extern TexturePtr D_08002210;
extern TexturePtr D_08002298;
extern TexturePtr D_08002320;
extern TexturePtr D_080023A8;
extern TexturePtr D_08002430;
extern TexturePtr D_080024B8;
extern TexturePtr D_08002540;
extern TexturePtr D_080025C8;
extern TexturePtr D_08002650;
extern TexturePtr D_08002A70;
extern TexturePtr D_08002E90;
extern TexturePtr D_080032B0;

#define BOMBERSNOTEBOOK_ENTRY(pos, day, index, startTime, endTime) \
    ((pos)&0xF000) | (((day)&0xF) << 8) | ((index)&0xFF), (startTime), (endTime)
#define BOMBERSNOTEBOOK_ENTRY_END 0x9999

#define BOMBERSNOTEBOOK_ENTRY_POS_CENTER 0x0000
#define BOMBERSNOTEBOOK_ENTRY_POS_BELOW 0x4000
#define BOMBERSNOTEBOOK_ENTRY_POS_ABOVE 0x8000

typedef enum {
    /* 0 */ BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    /* 1 */ BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    /* 2 */ BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON
} BombersNotebookEntryIcon;

#define BOMBERSNOTEBOOK_WEEKEVENTREG_NONE 0xFFF0
#define BOMBERSNOTEBOOK_WEEKEVENTREG_SPECIAL 0xFFF1

// sBombersNotebookEntries
u16 D_801D0D80[][30] = {
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 36, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 37, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 2, 36, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 2, 37, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 3, 36, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 3, 37, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 20, CLOCK_TIME(13, 45), CLOCK_TIME(16, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 21, CLOCK_TIME(14, 30), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 22, CLOCK_TIME(23, 30), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 23, CLOCK_TIME(23, 30), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 26, CLOCK_TIME(17, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 26, CLOCK_TIME(6, 0), CLOCK_TIME(12, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 50, CLOCK_TIME(5, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 25, CLOCK_TIME(16, 30), CLOCK_TIME(22, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 27, CLOCK_TIME(18, 0), CLOCK_TIME(19, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 50, CLOCK_TIME(5, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 3, 33, CLOCK_TIME(13, 0), CLOCK_TIME(22, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 3, 34, CLOCK_TIME(13, 0), CLOCK_TIME(22, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 45, CLOCK_TIME(22, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 51, CLOCK_TIME(0, 30), CLOCK_TIME(1, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 28, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 29, CLOCK_TIME(2, 30), CLOCK_TIME(5, 15)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 30, CLOCK_TIME(2, 30), CLOCK_TIME(5, 15)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 2, 31, CLOCK_TIME(18, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 2, 32, CLOCK_TIME(18, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 38, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 38, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 38, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 44, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 44, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 35, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 48, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 48, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 48, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 48, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 43, CLOCK_TIME(15, 0), CLOCK_TIME(0, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 24, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 24, CLOCK_TIME(6, 0), CLOCK_TIME(12, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 43, CLOCK_TIME(15, 0), CLOCK_TIME(0, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 49, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 39, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 39, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 40, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 40, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 40, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 41, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 42, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 2, 41, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 2, 42, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 52, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 52, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 52, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 46, CLOCK_TIME(6, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 46, CLOCK_TIME(6, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 46, CLOCK_TIME(6, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 47, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 47, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 31, CLOCK_TIME(18, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 47, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 53, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 53, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 53, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 54, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 54, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
};

s16 D_801D1230[] = { 0x78, 0x78, 0x10E, 0x1A4 };
TexturePtr D_801D1238[] = { &D_08002650, &D_08002A70, &D_08002E90 };
s32 D_801D1244[] = {
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
    BOMBERSNOTEBOOK_ENTRY_ICON_MASK,
};
s32 D_801D12D0[] = { 0x10, 0x18, 0x20 };
s32 D_801D12DC[] = { 0x10, 0x1C, 0x1C };
u16 D_801D12E8[] = {
    WEEKEVENTREG_75_10,
    WEEKEVENTREG_50_08,
    WEEKEVENTREG_50_20,
    WEEKEVENTREG_50_20,
    BOMBERSNOTEBOOK_WEEKEVENTREG_SPECIAL,
    WEEKEVENTREG_50_80,
    WEEKEVENTREG_51_01,
    WEEKEVENTREG_51_20,
    WEEKEVENTREG_21_20,
    WEEKEVENTREG_22_01,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    WEEKEVENTREG_52_01,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    WEEKEVENTREG_80_10,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_WEEKEVENTREG_NONE,
};

// SPScisTextureRectangle
void func_8016AC10(Gfx** gfxP, s32 rxl, s32 ryl, s32 rxh, s32 ryh, s32 tile, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    s32 xl = rxl - (D_801FBBD0 << 2);
    s32 yl = ryl - (D_801FBBD2 << 2);
    s32 xh = rxh - (D_801FBBD0 << 2);
    s32 yh = ryh - (D_801FBBD2 << 2);
    Gfx* gfx = *gfxP;

    gSPScisTextureRectangle(gfx++, xl, yl, xh, yh, tile, s, t, dsdx, dtdy);

    *gfxP = gfx;
}

s16 D_801D1330[][3] = {
    { 116, 134, 146 },
    { 158, 156, 131 },
    { 174, 141, 151 },
};

#ifdef NON_MATCHING
// DrawColumnHeaders
void func_8016AE1C(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 i;
    s32 x0;
    s32 xl;
    s32 xh;

    x0 = 120;
    gDPLoadTextureBlock(gfx++, &D_080017D8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 24, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for (i = 0, xl = x0 << 2, xh = xl + (143 << 2); i < 3; i++, xh += 150 << 2, xl += 150 << 2) {
        gDPSetPrimColor(gfx++, 0, 0, D_801D1330[i][0], D_801D1330[i][1], D_801D1330[i][2], 192);
        func_8016AC10(&gfx, xl, 74 << 2, xh, 98 << 2, 0, 0, 0, 0x400, 0x400);
    }

    x0 = 124;
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    for (i = 0, xl = x0 << 2, xh = xl + (48 << 2); i < 3; i++, xh += 150 << 2, xl += 150 << 2) {
        gDPLoadTextureBlock(gfx++, D_801D1238[i], G_IM_FMT_IA, G_IM_SIZ_8b, 48, 22, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        func_8016AC10(&gfx, xl, 77 << 2, xh, 99 << 2, 0, 0, 0, 0x400, 0x400);
    }

    x0 += 48;
    gDPLoadTextureBlock_4b(gfx++, &D_08001F70, G_IM_FMT_IA, 48, 11, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for (i = 0, xl = x0 << 2, xh = xl + (48 << 2); i < 3; i++, xh += 150 << 2, xl += 150 << 2) {
        func_8016AC10(&gfx, xl, 86 << 2, xh, 97 << 2, 0, 0, 0, 0x400, 0x400);
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}
#else
void func_8016AE1C(Gfx**);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016AE1C.s")
#endif

s16 D_801D1344[][3] = {
    { 165, 183, 195 }, { 140, 158, 170 }, { 197, 195, 172 }, { 172, 170, 147 }, { 223, 190, 200 }, { 190, 165, 175 },
};
// DrawColumnBackgrounds
void func_8016B278(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s16* color;
    s32 i;
    s32 j;
    s32 k;
    s32 x0;
    s32 xl;
    s32 xh;
    s32 pad[2];

    gDPLoadTextureBlock_4b(gfx++, &D_08001340, G_IM_FMT_I, 48, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    color = D_801D1344[0];
    for (i = 0, x0 = 120; i < 3; x0 += 150, i++) {
        xl = x0 << 2;
        xh = xl + (48 << 2);
        for (j = 0; j < 2; j++) {
            gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], 192);
            for (k = 0; k < 2; k++) {
                func_8016AC10(&gfx, xl, 104 << 2, xh, 480 << 2, 0, 0, 0, 0x400, 0x400);
                xl += 36 << 2;
                xh += 36 << 2;
            }
            color += 3;
        }
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

TexturePtr D_801D1368[] = { &D_08000000, &D_0700AC00, &D_0700AEA0 };
s16 D_801D1374[][3] = {
    { 255, 255, 0 },
    { 141, 255, 182 },
    { 255, 100, 60 },
};

#ifdef NON_MATCHING
// DrawEntries
void func_8016B4B0(Gfx** gfxP, s32 arg1, s32 arg2) {
    Gfx* sp1AC;
    s32 var_s0;
    s32 sp1A4;
    s32 sp1A0;
    s32 sp194;
    u16* sp84;
    s32 xl;
    s32 yl;

    s32 var_s3;
    s32 var_t0;
    s32 var_s5;

    sp1AC = *gfxP;
    sp84 = D_801D0D80[arg1];
    sp1A0 = false;

    while (true) {
        if (sp84[0] == BOMBERSNOTEBOOK_ENTRY_END) {
            if (!sp1A0) {
                gDPPipeSync(sp1AC++);
                gDPSetCombineLERP(sp1AC++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                                  PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                gDPSetPrimColor(sp1AC++, 0, 0, 0, 0, 0, 255);
                gDPSetEnvColor(sp1AC++, 0, 0, 0, 255);
                gDPLoadTextureBlock(sp1AC++, &D_08000100, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 48, 0, G_TX_MIRROR | G_TX_WRAP,
                                    G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                xl = (arg2 << 2) + (1 << 2);
                func_8016AC10(&sp1AC, 567 << 2, xl, 599 << 2, xl + (48 << 2), 0, 0, 0, 0x400, 0x400);
                gDPPipeSync(sp1AC++);
                gDPSetPrimColor(sp1AC++, 0, 0, 255, 255, 255, 255);
                gDPSetEnvColor(sp1AC++, 255, 0, 0, 255);
                xl = (arg2 << 2) - (1 << 2);
                func_8016AC10(&sp1AC, 565 << 2, xl, 597 << 2, xl + (48 << 2), 0, 0, 0, 0x400, 0x400);
                gDPPipeSync(sp1AC++);
                gDPSetCombineMode(sp1AC++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetEnvColor(sp1AC++, 0, 0, 0, 255);
            }
            break;
        }

        if (sp84[0] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
            var_t0 = 8;
        } else if (sp84[0] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW) {
            var_t0 = 0x18;
        } else { // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
            var_t0 = 0x10;
        }

        var_s0 = D_801D1230[(sp84[0] & 0xF00) >> 8] + (((sp84[1] - CLOCK_TIME(6, 0)) & 0xFFFF) / 455);
        var_s3 = D_801D1230[(sp84[0] & 0xF00) >> 8] + (((sp84[2] - CLOCK_TIME(6, 0)) & 0xFFFF) / 455);
        var_s5 = var_s3 - var_s0;
        if (var_s5 < 8) {
            var_s0 = (var_s0 + var_s5) - 8;
            var_s3 = var_s0 + 8;
        }

        // Black shadow
        gDPSetPrimColor(sp1AC++, 0, 0, 0, 0, 0, 255);
        gDPLoadTextureBlock(sp1AC++, &D_08001240, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        xl = (var_s0 << 2) + (2 << 2);
        yl = ((arg2 + var_t0) << 2) + (2 << 2);
        func_8016AC10(&sp1AC, xl, yl, xl + (4 << 2), yl + (16 << 2), 0, 0, 0, 0x400, 0x400);
        xl = (var_s3 << 2) - (2 << 2);
        yl = ((arg2 + var_t0) << 2) + (2 << 2);
        func_8016AC10(&sp1AC, xl, yl, xl + (4 << 2), yl + (16 << 2), 0, 0x80, 0, 0x400, 0x400);
        if ((var_s5 - 8) > 0) {
            gDPLoadTextureBlock(sp1AC++, &D_080012C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                                G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            xl = (var_s0 << 2) + (6 << 2);
            yl = ((arg2 + var_t0) << 2) + (2 << 2);
            func_8016AC10(&sp1AC, xl, yl, xl + ((var_s5 - 8) << 2), yl + (16 << 2), 0, 0, 0, 0x400, 0x400);
        }

        // Blue Box
        gDPSetPrimColor(sp1AC++, 0, 0, 255, 255, 255, 255);
        gDPLoadTextureBlock(sp1AC++, &D_08001240, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        xl = (var_s0 << 2) + (0 << 2);
        yl = ((arg2 + var_t0) << 2) + (0 << 0);
        func_8016AC10(&sp1AC, xl, yl, xl + (4 << 2), yl + (16 << 2), 0, 0, 0, 0x400, 0x400);
        xl = (var_s3 << 2) - (4 << 2);
        yl = ((arg2 + var_t0) << 2) + (0 << 2);
        func_8016AC10(&sp1AC, xl, yl, xl + (4 << 2), yl + (16 << 2), 0, 0x80, 0, 0x400, 0x400);
        if ((var_s5 - 8) > 0) {
            gDPLoadTextureBlock(sp1AC++, &D_080012C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                                G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            xl = (var_s0 << 2) + (4 << 2);
            yl = ((arg2 + var_t0) << 2) + (0 << 2);
            func_8016AC10(&sp1AC, xl, yl, xl + ((var_s5 - 8) << 2), yl + (16 << 2), 0, 0, 0, 0x400, 0x400);
        }
        if (CHECK_WEEKEVENTREG(sBombersNotebookEventWeekEventFlags[sp84[0] & 0xFF])) {
            sp1A4 = D_801D1244[(sp84[0] & 0xFF) - 20];
            if (var_s5 < D_801D12D0[sp1A4]) {
                sp194 = (((var_s0 - D_801D12D0[sp1A4]) + var_s3) - var_s0) + 3;
            } else {
                sp194 = ((var_s5 - D_801D12D0[sp1A4]) / 2) + var_s0;
            }

            if ((sp1A4 == BOMBERSNOTEBOOK_ENTRY_ICON_MASK) || (sp1A4 == BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON)) {
                if (sp84[0] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
                    var_t0 -= 12;
                } else if (!(sp84[0] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW)) { // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
                    var_t0 -= 6;
                }
            }
            gDPLoadTextureBlock(sp1AC++, D_801D1368[sp1A4], G_IM_FMT_IA, G_IM_SIZ_8b, D_801D12D0[sp1A4],
                                D_801D12DC[sp1A4], 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK,
                                G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(sp1AC++, 0, 0, 0, 0, 0, 255);

            xl = (sp194 << 2) + (2 << 2);
            yl = ((arg2 + var_t0) << 2) + (2 << 2);
            func_8016AC10(&sp1AC, xl, yl, xl + (D_801D12D0[sp1A4] << 2), yl + (D_801D12DC[sp1A4] << 2), 0, 0, 0, 0x400,
                          0x400);
            if (D_801D12E8[(sp84[0] & 0xFF) - 20] == BOMBERSNOTEBOOK_WEEKEVENTREG_NONE) {
                gDPSetPrimColor(sp1AC++, 0, 0, D_801D1374[sp1A4][0], D_801D1374[sp1A4][1], D_801D1374[sp1A4][2], 255);
            } else if (D_801D12E8[(sp84[0] & 0xFF) - 20] == BOMBERSNOTEBOOK_WEEKEVENTREG_SPECIAL) {
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_27_02) || CHECK_WEEKEVENTREG(WEEKEVENTREG_27_04) ||
                    CHECK_WEEKEVENTREG(WEEKEVENTREG_27_08) || CHECK_WEEKEVENTREG(WEEKEVENTREG_27_10) ||
                    CHECK_WEEKEVENTREG(WEEKEVENTREG_27_20)) {
                    gDPSetPrimColor(sp1AC++, 0, 0, D_801D1374[sp1A4][0], D_801D1374[sp1A4][1], D_801D1374[sp1A4][2],
                                    255);
                } else {
                    gDPSetPrimColor(sp1AC++, 0, 0, 155, 155, 155, 255);
                }
            } else {
                if (CHECK_WEEKEVENTREG(D_801D12E8[(sp84[0] & 0xFF) - 20])) {
                    gDPSetPrimColor(sp1AC++, 0, 0, D_801D1374[sp1A4][0], D_801D1374[sp1A4][1], D_801D1374[sp1A4][2],
                                    255);
                } else {
                    gDPSetPrimColor(sp1AC++, 0, 0, 155, 155, 155, 255);
                }
            }
            xl = (sp194 << 2) + (0 << 2);
            yl = ((arg2 + var_t0) << 2) + (0 << 2);
            func_8016AC10(&sp1AC, xl, yl, xl + (D_801D12D0[sp1A4] << 2), yl + (D_801D12DC[sp1A4] << 2), 0, 0, 0, 0x400,
                          0x400);
            gDPSetPrimColor(sp1AC++, 0, 0, 255, 255, 255, 255);
        } else {
            sp1A0 = true;
        }
        sp84 += 3;
    }

    *gfxP = sp1AC;
}
#else
void func_8016B4B0(Gfx** gfxP, s32 arg1, s32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016B4B0.s")
#endif

TexturePtr D_801D1388[] = {
    &D_07009800, &D_07000000, &D_07000800, &D_07001000, &D_07001800, &D_07002000, &D_07002800,
    &D_07003000, &D_07003800, &D_07004000, &D_07004800, &D_07005000, &D_07005800, &D_07006000,
    &D_07006800, &D_07007000, &D_07007800, &D_07008000, &D_07008800, &D_07009000,
};

#ifdef NON_MATCHING
// DrawRows
void func_8016C344(BombersNotebook* this, Gfx** gfxP) {
    static s16 D_801D13D8 = 0;
    static s16 D_801D13DC = 0;
    static s16 D_801D13E0 = 0;
    static s16 D_801D13E4 = 10;
    static s16 D_801D13E8 = 0;
    static s16 D_801D13EC[2] = { 100, 0 };
    static s16 D_801D13F0[2] = { 80, 0 };
    static s16 D_801D13F4[2] = { 255, 0 };

    Gfx* sp13C = *gfxP;
    s32 var_t1;
    s32 sp134;
    s32 sp130;
    s32 sp12C;
    f32 sp128;
    s32 sp124;
    s32 var_s0;
    s32 var_s3;
    s16 colorStep;
    s32 xl;
    s32 yl;

    colorStep = ABS_ALT(D_801D13D8 - D_801D13EC[D_801D13E8]) / D_801D13E4;
    if (D_801D13D8 >= D_801D13EC[D_801D13E8]) {
        D_801D13D8 -= colorStep;
    } else {
        D_801D13D8 += colorStep;
    }

    colorStep = ABS_ALT(D_801D13DC - D_801D13F0[D_801D13E8]) / D_801D13E4;
    if (D_801D13DC >= D_801D13F0[D_801D13E8]) {
        D_801D13DC -= colorStep;
    } else {
        D_801D13DC += colorStep;
    }

    colorStep = ABS_ALT(D_801D13E0 - D_801D13F4[D_801D13E8]) / D_801D13E4;
    if (D_801D13E0 >= D_801D13F4[D_801D13E8]) {
        D_801D13E0 -= colorStep;
    } else {
        D_801D13E0 += colorStep;
    }

    D_801D13E4--;
    if (D_801D13E4 == 0) {
        D_801D13E4 = 10;
        D_801D13D8 = D_801D13EC[D_801D13E8];
        D_801D13DC = D_801D13F0[D_801D13E8];
        D_801D13E0 = D_801D13F4[D_801D13E8];
        D_801D13E8 ^= 1;
    }

    var_s3 = this->unk_A8 + 107;
    if (this->unk_9C >= 0xC) {
        sp134 = 0x14;
        sp130 = this->unk_9C;
    } else {
        sp134 = this->unk_9C + 8;
        sp130 = sp134 - 8;
    }

    for (var_s0 = sp130; var_s0 < sp134; var_s0++) {
        gDPSetPrimColor(sp13C++, 0, 0, 255, 255, 255, 255);
        if (CHECK_WEEKEVENTREG(sBombersNotebookEventWeekEventFlags[var_s0])) {
            gDPLoadTextureBlock(sp13C++, D_801D1388[var_s0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(sp13C++, &D_08000A40, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        }

        if ((var_s0 == (this->unk_94 + sp130)) && (this->unk_A4 == 0)) {
            var_t1 = 64;
            sp128 = 200.0f;
            sp12C = 56;
            sp124 = 8;
        } else {
            var_t1 = 48;
            sp128 = 150.0f;
            sp12C = 48;
            sp124 = 0;
        }

        xl = (57 << 2) - (sp124 << 2);
        yl = (var_s3 << 2) - (sp124 << 2);
        func_8016AC10(&sp13C, xl, yl, xl + (var_t1 << 2), yl + (var_t1 << 2), 0, 0, 0, 1024.0f / (sp128 / 100.0f),
                      1024.0f / (sp128 / 100.0f));
        if ((var_s0 == (this->unk_94 + sp130)) && (this->unk_A4 == 0)) {
            gDPSetPrimColor(sp13C++, 0, 0, D_801D13D8, D_801D13DC, D_801D13E0, 255);
        } else {
            gDPSetPrimColor(sp13C++, 0, 0, 0, 0, 0, 60);
        }
        gDPLoadTextureBlock(sp13C++, &D_080018B0, G_IM_FMT_I, G_IM_SIZ_8b, 8, 4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        xl = (sp12C << 2) + (57 << 2);
        yl = (var_s3 << 2) + (22 << 2);
        func_8016AC10(&sp13C, xl, yl, xl + ((470 - sp124) << 2), yl + (4 << 2), 0, 0, 0, 0x400, 0x400);
        gDPLoadTextureBlock_4b(sp13C++, &D_08001358, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        xl = ((sp12C - sp124) << 2) + (527 << 2);
        yl = (var_s3 << 2) + (16 << 2);
        func_8016AC10(&sp13C, xl, yl, xl + (16 << 2), yl + (16 << 2), 0, 0, 0, 0x400, 0x400);
        if (CHECK_WEEKEVENTREG(sBombersNotebookEventWeekEventFlags[var_s0])) {
            gDPPipeSync(sp13C++);
            gDPSetRenderMode(sp13C++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            gDPSetPrimColor(sp13C++, 0, 0, 255, 255, 255, 255);

            func_8016B4B0(&sp13C, var_s0, var_s3);

            gDPPipeSync(sp13C++);
            gDPSetRenderMode(sp13C++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }
        var_s3 += 52;
    }
    gDPPipeSync(sp13C++);
    *gfxP = sp13C;
}
#else
static s16 D_801D13D8 = 0;
static s16 D_801D13DC = 0;
static s16 D_801D13E0 = 0;
static s16 D_801D13E4 = 10;
static s16 D_801D13E8 = 0;
static s16 D_801D13EC[2] = { 100, 0 };
static s16 D_801D13F0[2] = { 80, 0 };
static s16 D_801D13F4[2] = { 255, 0 };
void func_8016C344(BombersNotebook* this, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016C344.s")
#endif

TexturePtr D_801D13F8[] = {
    &D_08002078, &D_08002100, &D_08002188, &D_08002210, &D_08002298,
    &D_08002320, &D_080023A8, &D_08002430, &D_080024B8, &D_08002540,
};
u8 D_801D1420[] = { 13, 8, 12, 13, 14, 13, 12, 12, 13, 12 };
s16 D_801D142C[] = { 16, 12, 9, 0 };

#ifdef NON_MATCHING
#define TEST(day) (((day) == 0) ? 1 : (day))
// DrawTimeOfDay
void func_8016CD4C(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 sp260;
    s32 sp25C;
    s32 sp258;
    s32 sp254;
    s32 sp250;
    s32 sp248;
    s32 sp244;
    s32 sp240;
    u16 var_a1;

    var_a1 = (((void)0, gSaveContext.save.time) - CLOCK_TIME(6, 0));
    if (CURRENT_DAY == 0) {
        var_a1 = 0;
    }
    sp260 = D_801D1230[CURRENT_DAY] + (var_a1 / 455);
    if ((TEST(CURRENT_DAY) == 1) ||
        ((TEST(CURRENT_DAY) == 2) && (((void)0, gSaveContext.save.time) < CLOCK_TIME(12, 0)))) {
        sp260 -= 0x20;
        sp254 = sp260 + 0x20;
    } else if ((TEST(CURRENT_DAY) == 2) && (var_a1 >= (CLOCK_TIME(17, 0) - CLOCK_TIME(6, 0))) &&
               (var_a1 <= (CLOCK_TIME(19, 0) - CLOCK_TIME(6, 0)))) {
        sp260 -= 0x40;
        sp254 = sp260 + 0x40;
    } else {
        sp260 -= 0x60;
        sp254 = sp260 + 0x60;
    }

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_08001950, G_IM_FMT_IA, 64, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, sp260 << 2, 42 << 2, (sp260 << 2) + (128 << 2), 70 << 2, 0, 0, 0, 0x400, 0x400);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPLoadTextureBlock_4b(gfx++, &D_080032B0, G_IM_FMT_I, 96, 20, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    func_8016AC10(&gfx, (sp260 << 2) + (16 << 2), 47 << 2, (sp260 << 2) + (112 << 2), 67 << 2, 0, 0, 0, 0x400, 0x400);
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    if (((TEST(CURRENT_DAY) >= 3) || ((TEST(CURRENT_DAY) == 2) && (var_a1 > (CLOCK_TIME(18, 0) - CLOCK_TIME(6, 0)))))) {
        sp25C = sp260 - 159;
        sp258 = sp260 - 17;
    } else {
        sp25C = sp260 + 130;
        sp258 = sp260 + 113;
    }
    gDPLoadTextureBlock_4b(gfx++, &D_08001CD0, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, sp25C << 2, 42 << 2, (sp25C << 2) + (16 << 2), 70 << 2, 0, 0, 0, 0x400, 0x400);
    gDPLoadTextureBlock_4b(gfx++, &D_08001E90, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, (sp25C << 2) + (16 << 2), 42 << 2, (sp25C << 2) + (141 << 2), 70 << 2, 0, 0, 0, 0x400, 0x400);
    gDPLoadTextureBlock_4b(gfx++, &D_08001DB0, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, (sp25C << 2) + (141 << 2), 42 << 2, (sp25C << 2) + (157 << 2), 70 << 2, 0, 0, 0, 0x400, 0x400);
    gDPLoadTextureBlock(gfx++, D_801D1238[TEST(CURRENT_DAY) - 1], G_IM_FMT_IA, G_IM_SIZ_8b, 48, 22, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    func_8016AC10(&gfx, (sp25C + D_801D142C[TEST(CURRENT_DAY) - 1]) << 2, 46 << 2,
                  ((sp25C + D_801D142C[TEST(CURRENT_DAY) - 1]) << 2) + (48 << 2), 68 << 2, 0, 0, 0, 0x400, 0x400);

    gDPSetPrimColor(gfx++, 0, 0, 150, 150, 150, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_08001358, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, (sp25C << 2) + (56 << 2), 48 << 2, (sp25C << 2) + (72 << 2), 0x100, 0, 0, 0, 0x400, 0x400);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    sp244 = 0;
    sp248 = ((void)0, gSaveContext.save.time) / 2730;
    if (CURRENT_DAY == 0) {
        sp248 = 6;
    }
    sp240 = sp248;
    do {
        if (sp248 >= 10) {
            sp244++;
            sp248 -= 10;
        }
    } while (sp248 >= 10);

    gDPLoadTextureBlock_4b(gfx++, D_801D13F8[sp244], G_IM_FMT_I, 16, 17, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, (sp25C + 75) << 2, 48 << 2, ((sp25C + 75) << 2) + (16 << 2), 65 << 2, 0, 0, 0, 0x400, 0x400);

    sp250 = sp25C + 75 + D_801D1420[sp244];
    gDPLoadTextureBlock_4b(gfx++, D_801D13F8[sp248], G_IM_FMT_I, 16, 17, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, sp250 << 2, 48 << 2, (sp250 << 2) + (16 << 2), 65 << 2, 0, 0, 0, 0x400, 0x400);
    sp250 += D_801D1420[sp248];
    gDPLoadTextureBlock_4b(gfx++, &D_080025C8, G_IM_FMT_I, 16, 17, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, sp250 << 2, 48 << 2, (sp250 << 2) + (16 << 2), 65 << 2, 0, 0, 0, 0x400, 0x400);

    sp244 = 0;
    if (CURRENT_DAY == 0) {
        sp248 = (16384.0f - (sp240 * 2730.6667f)) / 45.511112f;
    } else {
        sp248 = (((void)0, gSaveContext.save.time) - (sp240 * 2730.6667f)) / 45.511112f;
    }
    do {
        if (sp248 >= 10) {
            sp244++;
            sp248 -= 10;
        }
    } while (sp248 >= 10);

    gDPLoadTextureBlock_4b(gfx++, D_801D13F8[sp244], G_IM_FMT_I, 16, 17, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    sp250 += 7;
    func_8016AC10(&gfx, sp250 << 2, 48 << 2, (sp250 << 2) + (16 << 2), 65 << 2, 0, 0, 0, 0x400, 0x400);
    sp250 += D_801D1420[sp244];
    gDPLoadTextureBlock_4b(gfx++, D_801D13F8[sp248], G_IM_FMT_I, 16, 17, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, sp250 << 2, 48 << 2, (sp250 << 2) + (16 << 2), 65 << 2, 0, 0, 0, 0x400, 0x400);

    // Connecting Bar? (Between time of day text box and the time box)
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPLoadTextureBlock(gfx++, &D_08000880, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 14, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, sp258 << 2, 49 << 2, (sp258 << 2) + (32 << 2), 63 << 2, 0, 0, 0, 0x400, 0x400);

    // Red Line
    gDPSetPrimColor(gfx++, 0, 0, 242, 0, 14, 255);
    gDPLoadTextureBlock(gfx++, &D_08001898, G_IM_FMT_I, G_IM_SIZ_8b, 8, 1, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, sp254 << 2, 74 << 2, (sp254 << 2) + (32 << 2), 490 << 2, 0, 0, 0, 0x400, 0x400);

    // Red Triangle
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gfx++, 200, 0, 0, 255);
    gDPLoadTextureBlock(gfx++, &D_08000700, G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    func_8016AC10(&gfx, (sp254 << 2) - (11 << 2), 70 << 2, (sp254 << 2) + (13 << 2), 86 << 2, 0, 0, 0, 0x400, 0x400);
    gDPPipeSync(gfx++);
    *gfxP = gfx;
}
#else
void func_8016CD4C(Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016CD4C.s")
#endif

#ifdef NON_MATCHING
// DrawCursor
void func_8016E40C(BombersNotebook* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_t0;
    s32 var_v0;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    u16* temp_t0;

    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 255, 205, 55, 255);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_080018D0, G_IM_FMT_IA, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                           4, 4, G_TX_NOLOD, G_TX_NOLOD);

    if (this->unk_98 == 0) {
        func_8016AC10(&gfx, 47 << 2, (this->unk_94 * 208) + (97 << 2), 63 << 2, (this->unk_94 * 208) + (113 << 2), 0, 0,
                      0, 0x400, 0x400);
        func_8016AC10(&gfx, 98 << 2, (this->unk_94 * 208) + (97 << 2), 114 << 2, (this->unk_94 * 208) + (113 << 2), 0,
                      0x200, 0, 0x400, 0x400);
        func_8016AC10(&gfx, 47 << 2, (this->unk_94 * 208) + (147 << 2), 63 << 2, (this->unk_94 * 208) + (163 << 2), 0,
                      0, 0x200, 0x400, 0x400);
        func_8016AC10(&gfx, 98 << 2, (this->unk_94 * 208) + (147 << 2), 114 << 2, (this->unk_94 * 208) + (163 << 2), 0,
                      0x200, 0x200, 0x400, 0x400);
    } else {
        temp_t0 = &D_801D0D80[this->unk_94 + this->unk_9C][this->unk_98 - 3];
        if (temp_t0[0] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
            sp84 = 8;
        } else if (temp_t0[0] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW) {
            sp84 = 0x18;
        } else { // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
            sp84 = 0x10;
        }
        var_v0 = D_801D1230[(temp_t0[0] & 0xF00) >> 8] + (((temp_t0[1] - CLOCK_TIME(6, 0)) & 0xFFFF) / 455);
        var_a0 = D_801D1230[(temp_t0[0] & 0xF00) >> 8] + (((temp_t0[2] - CLOCK_TIME(6, 0)) & 0xFFFF) / 455);
        var_a1 = var_a0 - var_v0;
        if (var_a1 < 8) {
            var_v0 = ((var_v0 + var_a0) - var_v0) - 8;
            var_a0 = var_v0 + 8;
            var_a1 = var_a0 - var_v0;
        }
        temp_v1_2 = D_801D1244[(temp_t0[0] & 0xFF) - 20];
        if (var_a1 < D_801D12D0[temp_v1_2]) {
            var_t0 = (((var_v0 - D_801D12D0[temp_v1_2]) + var_a0) - var_v0) + 3;
        } else {
            var_t0 = ((var_a1 - D_801D12D0[temp_v1_2]) / 2) + var_v0;
        }
        if (temp_v1_2 == BOMBERSNOTEBOOK_ENTRY_ICON_EXCLAMATION_POINT) {
            sp8C = var_t0 - 8;
        } else {
            sp8C = var_t0 - 9;
        }
        sp88 = ((this->unk_94 * 52) + 107) - 8;
        if ((temp_v1_2 == BOMBERSNOTEBOOK_ENTRY_ICON_MASK) || (temp_v1_2 == BOMBERSNOTEBOOK_ENTRY_ICON_RIBBON)) {
            if (temp_t0[0] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
                sp84 -= 0xC;
            } else if (!(temp_t0[0] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW)) { // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
                sp84 -= 6;
            }
        }
        func_8016AC10(&gfx, sp8C << 2, (sp88 + sp84) << 2, (sp8C << 2) + (16 << 2), ((sp88 + sp84) << 2) + (16 << 2), 0,
                      0, 0, 0x400, 0x400);
        func_8016AC10(&gfx, (D_801D12D0[temp_v1_2] + sp8C) << 2, (sp88 + sp84) << 2,
                      ((D_801D12D0[temp_v1_2] + sp8C) << 2) + (16 << 2), ((sp88 + sp84) << 2) + (16 << 2), 0, 0x200, 0,
                      0x400, 0x400);
        func_8016AC10(&gfx, sp8C << 2, (D_801D12DC[temp_v1_2] + sp88 + sp84) << 2, (sp8C << 2) + (16 << 2),
                      ((D_801D12DC[temp_v1_2] + sp88 + sp84) << 2) + (16 << 2), 0, 0, 0x200, 0x400, 0x400);
        func_8016AC10(&gfx, (D_801D12D0[temp_v1_2] + sp8C) << 2, (D_801D12DC[temp_v1_2] + sp88 + sp84) << 2,
                      ((D_801D12D0[temp_v1_2] + sp8C) << 2) + (16 << 2),
                      ((D_801D12DC[temp_v1_2] + sp88 + sp84) << 2) + (16 << 2), 0, 0x200, 0x200, 0x400, 0x400);
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}
#else
void func_8016E40C(BombersNotebook* this, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016E40C.s")
#endif

#ifdef NON_MATCHING
// DrawArrows
void func_8016EA90(BombersNotebook* this, Gfx** gfxP) {
    static s16 D_801D1434 = 0;
    static s16 D_801D1438 = 100;
    static s16 D_801D143C = 255;
    static s16 D_801D1440 = 0;
    static s16 D_801D1444 = 100;
    static s16 D_801D1448 = 255;
    static s16 D_801D144C = 0;
    static s16 D_801D1450 = 0;
    static s16 D_801D1454 = 6;
    static s16 D_801D1458 = 6;
    static s16 D_801D145C = 0;
    static s16 D_801D1460 = 0;
    static s16 D_801D1464[2] = { 175, 100 };
    static s16 D_801D1468[2] = { 205, 255 };
    Gfx* gfx = *gfxP;
    s32 xl;
    s16 colorStep;

    gDPPipeSync(gfx++);
    gDPLoadTextureBlock(gfx++, &D_08000700, G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, 4, G_TX_NOLOD, G_TX_NOLOD);

    colorStep = ABS_ALT(D_801D1438 - D_801D1464[D_801D144C]) / D_801D1454;
    if (D_801D1438 >= D_801D1464[D_801D144C]) {
        D_801D1438 -= colorStep;
    } else {
        D_801D1438 += colorStep;
    }

    colorStep = ABS_ALT(D_801D143C - D_801D1468[D_801D144C]) / D_801D1454;
    if (D_801D143C >= D_801D1468[D_801D144C]) {
        D_801D143C -= colorStep;
    } else {
        D_801D143C += colorStep;
    }

    D_801D1454--;
    if (D_801D1454 == 0) {
        D_801D145C ^= 6;
        D_801D1454 = 6;
        D_801D1438 = D_801D1464[D_801D144C];
        D_801D143C = D_801D1468[D_801D144C];
        D_801D144C ^= 1;
    }

    colorStep = ABS_ALT(D_801D1444 - D_801D1464[D_801D1450]) / D_801D1458;
    if (D_801D1444 >= D_801D1464[D_801D1450]) {
        D_801D1444 -= colorStep;
    } else {
        D_801D1444 += colorStep;
    }

    colorStep = ABS_ALT(D_801D1448 - D_801D1468[D_801D1450]) / D_801D1458;
    if (D_801D1448 >= D_801D1468[D_801D1450]) {
        D_801D1448 -= colorStep;
    } else {
        D_801D1448 += colorStep;
    }

    D_801D1458--;
    if (D_801D1458 == 0) {
        D_801D1460 ^= 6;
        D_801D1458 = 6;
        D_801D1444 = D_801D1464[D_801D1450];
        D_801D1448 = D_801D1468[D_801D1450];
        D_801D1450 ^= 1;
    }

    if (this->unk_9C != 0) {
        xl = (-D_801D145C << 2) + (83 << 2);
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, D_801D1434, D_801D1438, D_801D143C, 255);
        gDPSetEnvColor(gfx++, D_801D1434, D_801D1438, D_801D143C, 255);
        func_8016AC10(&gfx, 46 << 2, xl, 70 << 2, xl + (16 << 2), 0, 0, 0x200, 0x400, 0x400);
    }

    if (this->unk_9C < 16) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, D_801D1440, D_801D1444, D_801D1448, 255);
        gDPSetEnvColor(gfx++, D_801D1440, D_801D1444, D_801D1448, 255);
        xl = (D_801D1460 << 2) + (319 << 2);
        func_8016AC10(&gfx, 46 << 2, xl, 70 << 2, xl + (16 << 2), 0, 0, 0, 0x400, 0x400);
    }
    gDPPipeSync(gfx++);
    *gfxP = gfx;
}
#else
static s16 D_801D1434 = 0;
static s16 D_801D1438 = 100;
static s16 D_801D143C = 255;
static s16 D_801D1440 = 0;
static s16 D_801D1444 = 100;
static s16 D_801D1448 = 255;
static s16 D_801D144C = 0;
static s16 D_801D1450 = 0;
static s16 D_801D1454 = 6;
static s16 D_801D1458 = 6;
static s16 D_801D145C = 0;
static s16 D_801D1460 = 0;
static s16 D_801D1464[2] = { 175, 100 };
static s16 D_801D1468[2] = { 205, 255 };
void func_8016EA90(BombersNotebook* this, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016EA90.s")
#endif

void BombersNotebook_Draw(BombersNotebook* this, GraphicsContext* gfxCtx) {
    Gfx* gfx;
    s32 pad[2];

    func_8012CF0C(gfxCtx, this->unk_00 != 2, false, 0, 0, 0);

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;

    if (this->unk_00 == 2) {
        gSPSegment(gfx++, 0x07, this->unk_40);
        gSPSegment(gfx++, 0x08, this->unk_88);
        gfx = func_8012C600(gfx);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 215, 255);
        gDPSetEnvColor(gfx++, 100, 100, 100, 255);
        gDPLoadTextureBlock(gfx++, &D_080013D8, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

        func_8016AC10(&gfx, 0 << 2, 0 << 2, 640 << 2, 480 << 2, 0, 0, 0, 0x200, 0x200);

        gDPPipeSync(gfx++);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

        func_8016AE1C(&gfx);
        func_8016B278(&gfx);

        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 86, 600, 450);
        func_8016C344(this, &gfx);

        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, D_0E000000.setScissor);

        func_8016CD4C(&gfx);

        if (this->unk_A4 == 0) {
            func_8016E40C(this, &gfx);
        }
        func_8016EA90(this, &gfx);
    }
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

void func_8016F4EC(BombersNotebook* this, s32 flag) {
    switch (this->unk_00) {
        case 0:
            if (this->unk_40 == NULL) {
                break;
            }
            CmpDma_LoadAllFiles(this->unk_44, this->unk_40, this->unk_48);
            osCreateMesgQueue(&this->unk_6C, this->unk_84, ARRAY_COUNT(this->unk_84));
            DmaMgr_SendRequestImpl(&this->unk_4C, this->unk_88, this->unk_8C, this->unk_90, 0, &this->unk_6C, NULL);
            this->unk_00 = 1;
            // fall-through
        case 1:
            if (osRecvMesg(&this->unk_6C, NULL, flag) == 0) {
                this->unk_00 = 2;
            }
    }
}

u16 D_801D146C[55] = {
    0x21DD, 0x21CA, 0x21CB, 0x21CC, 0x21CD, 0x21CE, 0x21CF, 0x21D0, 0x21D1, 0x21D2, 0x21D3, 0x21D4,
    0x21D5, 0x21D6, 0x21D7, 0x21D8, 0x21D9, 0x21DA, 0x21DB, 0x21DC, //

    0x2198, 0x2199, 0x219A, 0x219B, 0x219C, 0x219D, 0x219E, 0x219F, 0x21A0, 0x21A1, 0x21A2, 0x21A3,
    0x21A4, 0x21A5, 0x21A6, 0x21A7, 0x21A8, 0x21A9, 0x21AA, 0x21AB, 0x21AC, 0x21AD, 0x21AE, 0x21AF,
    0x21B0, 0x21B1, 0x21B2, 0x21B3, 0x21B4, 0x21B5, 0x21B6, 0x21B7, 0x21B8, 0x21B9, 0x21BA,
};

#ifdef NON_MATCHING
void BombersNotebook_Update(PlayState* play, BombersNotebook* this, Input* input) {
    static s16 D_801D14DC = 0;
    static s16 D_801D14E0 = 0;
    static s16 D_801D14E4 = 0;
    static s16 D_801D14E8 = 0;
    s32 sp2C = input->rel.stick_x;
    s32 sp28 = input->rel.stick_y;
    s32 sp24;

    this->unk_44 = SEGMENT_ROM_START(schedule_dma_static_test);
    this->unk_48 = SEGMENT_ROM_SIZE(schedule_dma_static_old);
    this->unk_8C = SEGMENT_ROM_START(schedule_static);
    this->unk_90 = SEGMENT_ROM_SIZE(schedule_static);

    if (this->unk_40 == NULL) {
        this->unk_40 = ZeldaArena_Malloc(this->unk_48);
    }

    if (this->unk_88 == NULL) {
        this->unk_88 = ZeldaArena_Malloc(this->unk_90);
    }

    func_8016F4EC(this, 0);

    if (this->unk_00 == 2) {
        if (sp2C < -30) {
            if (D_801D14E4 == -1) {
                D_801D14DC--;
                if (D_801D14DC < 0) {
                    D_801D14DC = 2;
                } else {
                    sp2C = 0;
                }
            } else {
                D_801D14DC = 10;
                D_801D14E4 = -1;
            }
        } else if (sp2C > 30) {
            if (D_801D14E4 == 1) {
                D_801D14DC--;
                if (D_801D14DC < 0) {
                    D_801D14DC = 2;
                } else {
                    sp2C = 0;
                }
            } else {
                D_801D14DC = 10;
                D_801D14E4 = 1;
            }
        } else {
            D_801D14E4 = 0;
        }

        if (sp28 < -30) {
            if (D_801D14E8 == -1) {
                D_801D14E0--;
                if (D_801D14E0 < 0) {
                    D_801D14E0 = 2;
                } else {
                    sp28 = 0;
                }
            } else {
                D_801D14E0 = 10;
                D_801D14E8 = -1;
            }
        } else if (sp28 > 30) {
            if (D_801D14E8 == 1) {
                D_801D14E0--;
                if (D_801D14E0 < 0) {
                    D_801D14E0 = 2;
                } else {
                    sp28 = 0;
                }
            } else {
                D_801D14E0 = 10;
                D_801D14E8 = 1;
            }
        } else {
            D_801D14E8 = 0;
        }
        if (this->unk_A4 == 0) {
            if (CHECK_WEEKEVENTREG(sBombersNotebookEventWeekEventFlags[this->unk_94 + this->unk_9C])) {
                sp24 = this->unk_98;
                if (sp2C > 30) {
                    while (true) {
                        sp24 += 3;
                        if (D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] == BOMBERSNOTEBOOK_ENTRY_END) {
                            while (true) {
                                sp24 -= 3;
                                if (sp24 == 0) {
                                    play_sound(NA_SE_SY_ERROR);
                                    break;
                                }
                                if (CHECK_WEEKEVENTREG(
                                        sBombersNotebookEventWeekEventFlags
                                            [D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] & 0xFF])) {
                                    play_sound(NA_SE_SY_ERROR);
                                    break;
                                }
                            }
                            break;
                        }
                        if (CHECK_WEEKEVENTREG(
                                sBombersNotebookEventWeekEventFlags[D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] &
                                                                    0xFF])) {
                            play_sound(NA_SE_SY_CURSOR);
                            break;
                        }
                    }
                } else if (sp2C < -30) {
                    while (sp24 != 0) {
                        sp24 -= 3;
                        if (CHECK_WEEKEVENTREG(
                                sBombersNotebookEventWeekEventFlags[D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] &
                                                                    0xFF])) {
                            play_sound(NA_SE_SY_CURSOR);
                            break;
                        }
                    }
                }
                this->unk_98 = sp24;
                if (this->unk_98 != 0) {
                    if (play->msgCtx.currentTextId !=
                        D_801D146C[D_801D0D80[this->unk_94 + this->unk_9C][this->unk_98 - 3] & 0xFF]) {
                        Message_ContinueTextbox(
                            play, D_801D146C[D_801D0D80[this->unk_94 + this->unk_9C][this->unk_98 - 3] & 0xFF]);
                    }
                } else {
                    if (play->msgCtx.currentTextId != D_801D146C[this->unk_94 + this->unk_9C]) {
                        Message_ContinueTextbox(play, D_801D146C[this->unk_94 + this->unk_9C]);
                    }
                }
            } else {
                Message_CloseTextbox(play);
            }

            if (sp28 < -30) {
                if (this->unk_94 < 3) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->unk_98 = 0;
                    this->unk_94++;
                } else if (this->unk_9C < 0x10) {
                    if (D_801D14E8 == -1) {
                        this->unk_A4 = -0x18;
                    } else {
                        this->unk_A4 = -0xC;
                    }
                    this->unk_A8 = 0;
                    this->unk_98 = 0;
                }
            } else if (sp28 > 30) {
                if (this->unk_94 > 0) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->unk_98 = 0;
                    this->unk_94--;
                } else if (this->unk_9C != 0) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->unk_9C--;
                    if (D_801D14E8 == 1) {
                        this->unk_A4 = 0x18;
                    } else {
                        this->unk_A4 = 0xC;
                    }
                    this->unk_A8 = -0x30;
                    this->unk_98 = 0;
                }
            }
        } else if (this->unk_A4 < 0) {
            this->unk_A8 += this->unk_A4;
            if (ABS_ALT(this->unk_A8) >= 0x30) {
                play_sound(NA_SE_SY_CURSOR);
                this->unk_A8 = 0;
                this->unk_A4 = 0;
                this->unk_9C++;
            }
        } else {
            this->unk_A8 += this->unk_A4;
            if (this->unk_A8 == 0) {
                this->unk_A8 = 0;
                this->unk_A4 = 0;
            }
        }
    }
}
#else
static s16 D_801D14DC = 0;
static s16 D_801D14E0 = 0;
static s16 D_801D14E4 = 0;
static s16 D_801D14E8 = 0;
void BombersNotebook_Update(PlayState* play, BombersNotebook* this, Input* input);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/BombersNotebook_Update.s")
#endif

void BombersNotebook_Init(BombersNotebook* this) {
    bzero(this, sizeof(BombersNotebook));
}

void BombersNotebook_Destroy(BombersNotebook* this) {
    if (this->unk_00 == 1) {
        func_8016F4EC(this, true);
    }
    if (this->unk_40 != NULL) {
        ZeldaArena_Free(this->unk_40);
        this->unk_40 = NULL;
    }
}
