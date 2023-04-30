#include "global.h"
#include "z64bombers_notebook.h"

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

#define BOMBERSNOTEBOOK_ENTRY(pos, day, eventIndex, startTime, endTime) \
    ((pos)&0xF000) | (((day)&0xF) << 8) | ((eventIndex + 20) & 0xFF), (startTime), (endTime)
#define BOMBERSNOTEBOOK_ENTRY_END 0x9999

#define BOMBERSNOTEBOOK_ENTRY_POS_CENTER 0x0000
#define BOMBERSNOTEBOOK_ENTRY_POS_BELOW 0x4000
#define BOMBERSNOTEBOOK_ENTRY_POS_ABOVE 0x8000

typedef enum {
    /* 0 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 1 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 2 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON
} BombersNotebookEventIcon;

#define BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE 0xFFF0
#define BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_DELIVERED_LETTER 0xFFF1

u16 sBombersNotebookEntries[][30] = {
    {
        // Bombers
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 16, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 17, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 2, 16, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 2, 17, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 3, 16, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 3, 17, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Anju
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 0, CLOCK_TIME(13, 45), CLOCK_TIME(16, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 1, CLOCK_TIME(14, 30), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 2, CLOCK_TIME(23, 30), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 3, CLOCK_TIME(23, 30), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 6, CLOCK_TIME(17, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 6, CLOCK_TIME(6, 0), CLOCK_TIME(12, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 30, CLOCK_TIME(5, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Kafei
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 5, CLOCK_TIME(16, 30), CLOCK_TIME(22, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 7, CLOCK_TIME(18, 0), CLOCK_TIME(19, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 30, CLOCK_TIME(5, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Curiosity Shop Man
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 3, 13, CLOCK_TIME(13, 0), CLOCK_TIME(22, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 3, 14, CLOCK_TIME(13, 0), CLOCK_TIME(22, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 25, CLOCK_TIME(22, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Old Lady from Bomb Shop
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 31, CLOCK_TIME(0, 30), CLOCK_TIME(1, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Romani
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 8, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 9, CLOCK_TIME(2, 30), CLOCK_TIME(5, 15)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 10, CLOCK_TIME(2, 30), CLOCK_TIME(5, 15)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Cremia
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 2, 11, CLOCK_TIME(18, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 2, 12, CLOCK_TIME(18, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Mayor Dotour
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 18, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 18, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 18, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Madame Aroma
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 24, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 24, CLOCK_TIME(8, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 15, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Toto
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 28, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 28, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Gorman
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 28, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 28, CLOCK_TIME(22, 0), CLOCK_TIME(5, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Postman
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 23, CLOCK_TIME(15, 0), CLOCK_TIME(0, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 4, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 4, CLOCK_TIME(6, 0), CLOCK_TIME(12, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 23, CLOCK_TIME(15, 0), CLOCK_TIME(0, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 29, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Rosa Sisters
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 19, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 19, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // ???
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 20, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 20, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 20, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Anju's Grandmother
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 1, 21, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 1, 22, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_ABOVE, 2, 21, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_BELOW, 2, 22, CLOCK_TIME(8, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Kamaro
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 32, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 32, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 32, CLOCK_TIME(0, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Grog
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 26, CLOCK_TIME(6, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 26, CLOCK_TIME(6, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 26, CLOCK_TIME(6, 0), CLOCK_TIME(20, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Gorman Brothers
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 27, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 27, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 11, CLOCK_TIME(18, 0), CLOCK_TIME(21, 0)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 27, CLOCK_TIME(6, 0), CLOCK_TIME(18, 0)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Shiro
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 33, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 33, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 3, 33, CLOCK_TIME(6, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
    {
        // Guru-Guru
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 1, 34, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY(BOMBERSNOTEBOOK_ENTRY_POS_CENTER, 2, 34, CLOCK_TIME(18, 0), CLOCK_TIME(5, 59)),
        BOMBERSNOTEBOOK_ENTRY_END,
    },
};

s16 sBombersNotebookDayRectRectLeft[] = { 120, 120, 270, 420 };
TexturePtr sBombersNotebookDayTextures[] = { &D_08002650, &D_08002A70, &D_08002E90 };

s32 sBombersNotebookEventIcons[] = {
    /* 00 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 01 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 02 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 03 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 04 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 05 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 06 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 07 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 08 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 09 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 10 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 11 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 12 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 13 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 14 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 15 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 16 */ BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    /* 17 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 18 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 19 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 20 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 21 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 22 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 23 */ BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    /* 24 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 25 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 26 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 27 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 28 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 29 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 30 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 31 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 32 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 33 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    /* 34 */ BOMBERSNOTEBOOK_EVENT_ICON_MASK,
};
s32 sBombersNotebookEventIconWidths[] = { 16, 24, 32 };
s32 sBombersNotebookEventIconHeights[] = { 16, 28, 28 };
u16 sBombersNotebookEventColorWeekEventFlags[] = {
    /* 00 */ WEEKEVENTREG_75_10,
    /* 01 */ WEEKEVENTREG_50_08,
    /* 02 */ WEEKEVENTREG_50_20,
    /* 03 */ WEEKEVENTREG_50_20,
    /* 04 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_DELIVERED_LETTER,
    /* 05 */ WEEKEVENTREG_50_80,
    /* 06 */ WEEKEVENTREG_51_01,
    /* 07 */ WEEKEVENTREG_51_20,
    /* 08 */ WEEKEVENTREG_21_20,
    /* 09 */ WEEKEVENTREG_22_01,
    /* 10 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 11 */ WEEKEVENTREG_52_01,
    /* 12 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 13 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 14 */ WEEKEVENTREG_80_10,
    /* 15 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 16 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 17 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 18 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 19 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 20 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 21 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 22 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 23 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 24 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 25 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 26 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 27 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 28 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 29 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 30 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 31 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 32 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 33 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    /* 34 */ BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
};

void BombersNotebook_TextureRectangle(Gfx** gfxP, s32 rxl, s32 ryl, s32 rxh, s32 ryh, s32 tile, s32 s, s32 t, s32 dsdx,
                                      s32 dtdy) {
    s32 xl = rxl - (D_801FBBD0 * 4);
    s32 yl = ryl - (D_801FBBD2 * 4);
    s32 xh = rxh - (D_801FBBD0 * 4);
    s32 yh = ryh - (D_801FBBD2 * 4);
    Gfx* gfx = *gfxP;

    gSPScisTextureRectangle(gfx++, xl, yl, xh, yh, tile, s, t, dsdx, dtdy);

    *gfxP = gfx;
}

s16 sBombersNotebookHeaderColors[][3] = {
    { 116, 134, 146 },
    { 158, 156, 131 },
    { 174, 141, 151 },
};

void BombersNotebook_DrawHeaders(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 i;
    s32 rectLeft;

    // Box
    gDPLoadTextureBlock(gfx++, &D_080017D8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 24, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for (i = 0, rectLeft = 120; i < 3; i++, rectLeft += 150) {
        gDPSetPrimColor(gfx++, 0, 0, sBombersNotebookHeaderColors[i][0], sBombersNotebookHeaderColors[i][1],
                        sBombersNotebookHeaderColors[i][2], 192);
        BombersNotebook_TextureRectangle(&gfx, rectLeft * 4, 74 * 4, (rectLeft + 143) * 4, 98 * 4, 0, 0, 0, 0x400,
                                         0x400);
    }

    // Day Texture
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    for (i = 0, rectLeft = 124; i < 3; i++, rectLeft += 150) {
        gDPLoadTextureBlock(gfx++, sBombersNotebookDayTextures[i], G_IM_FMT_IA, G_IM_SIZ_8b, 48, 22, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        BombersNotebook_TextureRectangle(&gfx, rectLeft * 4, 77 * 4, (rectLeft + 48) * 4, 99 * 4, 0, 0, 0, 0x400,
                                         0x400);
    }

    // 18:00
    rectLeft = 172;
    gDPLoadTextureBlock_4b(gfx++, &D_08001F70, G_IM_FMT_IA, 48, 11, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for (i = 0; i < 3; i++) {
        BombersNotebook_TextureRectangle(&gfx, rectLeft * 4, 86 * 4, (rectLeft + 48) * 4, 97 * 4, 0, 0, 0, 0x400,
                                         0x400);
        rectLeft += 150;
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

s16 sBombersNotebookColumnColors[][2][3] = {
    { { 165, 183, 195 }, { 140, 158, 170 } },
    { { 197, 195, 172 }, { 172, 170, 147 } },
    { { 223, 190, 200 }, { 190, 165, 175 } },
};

void BombersNotebook_DrawColumns(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s16* color;
    s32 i;
    s32 j;
    s32 k;
    s32 columnRectLeft;
    s32 subColumnRectLeft;
    s32 pad;

    gDPLoadTextureBlock_4b(gfx++, &D_08001340, G_IM_FMT_I, 48, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    color = &sBombersNotebookColumnColors[0][0][0];
    for (i = 0, columnRectLeft = 120; i < 3; i++, columnRectLeft += 150) {
        subColumnRectLeft = columnRectLeft;
        for (j = 0; j < 2; j++) {
            gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], 192);
            for (k = 0; k < 2; k++) {
                BombersNotebook_TextureRectangle(&gfx, subColumnRectLeft * 4, 104 * 4, (subColumnRectLeft + 48) * 4,
                                                 480 * 4, 0, 0, 0, 0x400, 0x400);
                subColumnRectLeft += 36;
            }
            color += 3;
        }
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

TexturePtr sBombersNotebookEventIconTextures[] = { &D_08000000, &D_0700AC00, &D_0700AEA0 };
s16 sBombersNotebookEntryIconColors[][3] = {
    { 255, 255, 0 },
    { 141, 255, 182 },
    { 255, 100, 60 },
};

void BombersNotebook_DrawEntries(Gfx** gfxP, s32 row, u32 rectTop) {
    Gfx* gfx = *gfxP;
    s32 entryRectLeft;
    u32 eventIcon;
    u32 unfinishedEvent = false;
    u16 startTime;
    u16 endTime;
    s32 j = 0;
    u32 iconRectLeft;
    s32 entryRight;
    u32 yOffset;
    s32 entryWidth;

    while (true) {
        if (sBombersNotebookEntries[row][j] == BOMBERSNOTEBOOK_ENTRY_END) {
            if (!unfinishedEvent) {
                // Completed Stamp
                gDPPipeSync(gfx++);
                gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                                  PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
                gDPSetEnvColor(gfx++, 0, 0, 0, 255);
                gDPLoadTextureBlock(gfx++, &D_08000100, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 48, 0, G_TX_MIRROR | G_TX_WRAP,
                                    G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                BombersNotebook_TextureRectangle(&gfx, 567 * 4, (rectTop + 1) * 4, 599 * 4, (rectTop + 49) * 4, 0, 0, 0,
                                                 0x400, 0x400);
                gDPPipeSync(gfx++);
                gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
                gDPSetEnvColor(gfx++, 255, 0, 0, 255);
                BombersNotebook_TextureRectangle(&gfx, 565 * 4, (rectTop + -1) * 4, 597 * 4, (rectTop + 47) * 4, 0, 0,
                                                 0, 0x400, 0x400);
                gDPPipeSync(gfx++);
                gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetEnvColor(gfx++, 0, 0, 0, 255);
            }
            break;
        }

        if (sBombersNotebookEntries[row][j] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
            yOffset = 8;
        } else if (sBombersNotebookEntries[row][j] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW) {
            yOffset = 24;
        } else { // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
            yOffset = 16;
        }

        startTime = sBombersNotebookEntries[row][j + 1] - CLOCK_TIME(6, 0);
        endTime = sBombersNotebookEntries[row][j + 2] - CLOCK_TIME(6, 0);
        entryRectLeft =
            sBombersNotebookDayRectRectLeft[(sBombersNotebookEntries[row][j] & 0xF00) >> 8] + (startTime / 455);
        entryRight = sBombersNotebookDayRectRectLeft[(sBombersNotebookEntries[row][j] & 0xF00) >> 8] + (endTime / 455);
        entryWidth = entryRight - entryRectLeft - 8;
        if ((entryRight - entryRectLeft) < 8) {
            entryRectLeft = ((entryRectLeft + entryRight) - entryRectLeft) - 8;
            entryRight = entryRectLeft + 8;
        }

        // Shadow
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
        gDPLoadTextureBlock(gfx++, &D_08001240, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        BombersNotebook_TextureRectangle(&gfx, (entryRectLeft + 2) * 4, (rectTop + yOffset + 2) * 4,
                                         (entryRectLeft + 6) * 4, (rectTop + yOffset + 18) * 4, 0, 0, 0, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, (entryRight + -2) * 4, (rectTop + yOffset + 2) * 4, (entryRight + 2) * 4,
                                         (rectTop + yOffset + 18) * 4, 0, 0x80, 0, 0x400, 0x400);
        if (entryWidth > 0) {
            gDPLoadTextureBlock(gfx++, &D_080012C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                                G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            BombersNotebook_TextureRectangle(&gfx, (entryRectLeft + 6) * 4, (rectTop + yOffset + 2) * 4,
                                             (entryRectLeft + 6 + entryWidth) * 4, (rectTop + yOffset + 18) * 4, 0, 0,
                                             0, 0x400, 0x400);
        }

        // Box
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        gDPLoadTextureBlock(gfx++, &D_08001240, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        //! FAKE: the ^ 0
        BombersNotebook_TextureRectangle(&gfx, (entryRectLeft * 4) ^ 0, (rectTop + yOffset) * 4,
                                         (entryRectLeft + 4) * 4, (rectTop + yOffset + 16) * 4, 0, 0, 0, 0x400, 0x400);
        //! FAKE: the ^ 0
        BombersNotebook_TextureRectangle(&gfx, (entryRight + -4) * 4, (rectTop + yOffset) * 4, (entryRight * 4) ^ 0,
                                         (rectTop + yOffset + 16) * 4, 0, 0x80, 0, 0x400, 0x400);
        if (entryWidth > 0) {
            gDPLoadTextureBlock(gfx++, &D_080012C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                                G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            BombersNotebook_TextureRectangle(&gfx, (entryRectLeft + 4) * 4, (rectTop + yOffset) * 4,
                                             (entryRectLeft + 4 + entryWidth) * 4, (rectTop + yOffset + 16) * 4, 0, 0,
                                             0, 0x400, 0x400);
        }

        if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[sBombersNotebookEntries[row][j] & 0xFF])) {
            // Icon
            eventIcon = sBombersNotebookEventIcons[(sBombersNotebookEntries[row][j] & 0xFF) - 20];
            if ((entryRight - entryRectLeft) < sBombersNotebookEventIconWidths[eventIcon]) {
                iconRectLeft =
                    (((entryRectLeft - sBombersNotebookEventIconWidths[eventIcon]) + entryRight) - entryRectLeft) + 3;
            } else {
                iconRectLeft =
                    (((entryRight - entryRectLeft) - sBombersNotebookEventIconWidths[eventIcon]) / 2) + entryRectLeft;
            }

            if ((eventIcon == BOMBERSNOTEBOOK_EVENT_ICON_MASK) || (eventIcon == BOMBERSNOTEBOOK_EVENT_ICON_RIBBON)) {
                if (sBombersNotebookEntries[row][j] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
                    yOffset -= 12;
                } else if (!(sBombersNotebookEntries[row][j] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW)) {
                    // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
                    yOffset -= 6;
                }
            }
            gDPLoadTextureBlock(gfx++, sBombersNotebookEventIconTextures[eventIcon], G_IM_FMT_IA, G_IM_SIZ_8b,
                                sBombersNotebookEventIconWidths[eventIcon], sBombersNotebookEventIconHeights[eventIcon],
                                0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

            BombersNotebook_TextureRectangle(&gfx, (iconRectLeft + 2) * 4, (rectTop + yOffset + 2) * 4,
                                             (iconRectLeft + 2 + sBombersNotebookEventIconWidths[eventIcon]) * 4,
                                             (rectTop + yOffset + 2 + sBombersNotebookEventIconHeights[eventIcon]) * 4,
                                             0, 0, 0, 0x400, 0x400);
            if (sBombersNotebookEventColorWeekEventFlags[(sBombersNotebookEntries[row][j] & 0xFF) - 20] ==
                BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE) {
                gDPSetPrimColor(gfx++, 0, 0, sBombersNotebookEntryIconColors[eventIcon][0],
                                sBombersNotebookEntryIconColors[eventIcon][1],
                                sBombersNotebookEntryIconColors[eventIcon][2], 255);
            } else if (sBombersNotebookEventColorWeekEventFlags[(sBombersNotebookEntries[row][j] & 0xFF) - 20] ==
                       BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_DELIVERED_LETTER) {
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_27_02) || CHECK_WEEKEVENTREG(WEEKEVENTREG_27_04) ||
                    CHECK_WEEKEVENTREG(WEEKEVENTREG_27_08) || CHECK_WEEKEVENTREG(WEEKEVENTREG_27_10) ||
                    CHECK_WEEKEVENTREG(WEEKEVENTREG_27_20)) {
                    gDPSetPrimColor(gfx++, 0, 0, sBombersNotebookEntryIconColors[eventIcon][0],
                                    sBombersNotebookEntryIconColors[eventIcon][1],
                                    sBombersNotebookEntryIconColors[eventIcon][2], 255);
                } else {
                    gDPSetPrimColor(gfx++, 0, 0, 155, 155, 155, 255);
                }
            } else {
                if (CHECK_WEEKEVENTREG(
                        sBombersNotebookEventColorWeekEventFlags[(sBombersNotebookEntries[row][j] & 0xFF) - 20])) {
                    gDPSetPrimColor(gfx++, 0, 0, sBombersNotebookEntryIconColors[eventIcon][0],
                                    sBombersNotebookEntryIconColors[eventIcon][1],
                                    sBombersNotebookEntryIconColors[eventIcon][2], 255);
                } else {
                    gDPSetPrimColor(gfx++, 0, 0, 155, 155, 155, 255);
                }
            }
            BombersNotebook_TextureRectangle(&gfx, iconRectLeft * 4, (rectTop + yOffset) * 4,
                                             (iconRectLeft + sBombersNotebookEventIconWidths[eventIcon]) * 4,
                                             (rectTop + yOffset + sBombersNotebookEventIconHeights[eventIcon]) * 4, 0,
                                             0, 0, 0x400, 0x400);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        } else {
            unfinishedEvent = true;
        }
        j += 3;
    }

    *gfxP = gfx;
}

TexturePtr sBombersNotebookPhotoTextures[] = {
    &D_07009800, &D_07000000, &D_07000800, &D_07001000, &D_07001800, &D_07002000, &D_07002800,
    &D_07003000, &D_07003800, &D_07004000, &D_07004800, &D_07005000, &D_07005800, &D_07006000,
    &D_07006800, &D_07007000, &D_07007800, &D_07008000, &D_07008800, &D_07009000,
};

void BombersNotebook_DrawRows(BombersNotebook* this, Gfx** gfxP) {
    static s16 sBarColorR = 0;
    static s16 sBarColorG = 0;
    static s16 sBarColorB = 0;
    static s16 sBarColorTimer = 10;
    static s16 sBarColorIndex = 0;
    static s16 sBarColorTargetsR[2] = { 100, 0 };
    static s16 sBarColorTargetsG[2] = { 80, 0 };
    static s16 sBarColorTargetsB[2] = { 255, 0 };
    Gfx* gfx = *gfxP;
    s32 photoWidth;
    s32 rowEnd;
    s32 cursorPage;
    u32 barRectLeft;
    f32 photoRectDs;
    u32 photoOffset;
    s32 i;
    u32 rectTop;
    s16 colorStep;

    colorStep = ABS_ALT(sBarColorR - sBarColorTargetsR[sBarColorIndex]) / sBarColorTimer;
    if (sBarColorR >= sBarColorTargetsR[sBarColorIndex]) {
        sBarColorR -= colorStep;
    } else {
        sBarColorR += colorStep;
    }

    colorStep = ABS_ALT(sBarColorG - sBarColorTargetsG[sBarColorIndex]) / sBarColorTimer;
    if (sBarColorG >= sBarColorTargetsG[sBarColorIndex]) {
        sBarColorG -= colorStep;
    } else {
        sBarColorG += colorStep;
    }

    colorStep = ABS_ALT(sBarColorB - sBarColorTargetsB[sBarColorIndex]) / sBarColorTimer;
    if (sBarColorB >= sBarColorTargetsB[sBarColorIndex]) {
        sBarColorB -= colorStep;
    } else {
        sBarColorB += colorStep;
    }

    sBarColorTimer--;
    if (sBarColorTimer == 0) {
        sBarColorTimer = 10;
        sBarColorR = sBarColorTargetsR[sBarColorIndex];
        sBarColorG = sBarColorTargetsG[sBarColorIndex];
        sBarColorB = sBarColorTargetsB[sBarColorIndex];
        sBarColorIndex ^= 1;
    }

    rectTop = this->scrollOffset + 107;
    if (this->cursorPage >= 12) {
        rowEnd = 20;
        i = this->cursorPage;
    } else {
        rowEnd = this->cursorPage + 8;
        i = rowEnd - 8;
    }
    cursorPage = i;
    for (; i < rowEnd; i++, rectTop += 52) {
        // Photo
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[i])) {
            gDPLoadTextureBlock(gfx++, sBombersNotebookPhotoTextures[i], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(gfx++, &D_08000A40, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        }
        if ((i == (this->cursorPageRow + cursorPage)) && (this->scrollAmount == 0)) {
            barRectLeft = 56;
            photoOffset = 8;
            photoRectDs = 200.0f;
            photoWidth = 64;
        } else {
            barRectLeft = 48;
            photoOffset = 0;
            photoRectDs = 150.0f;
            photoWidth = 48;
        }
        BombersNotebook_TextureRectangle(&gfx, (57 - photoOffset) * 4, (rectTop - photoOffset) * 4,
                                         (57 - photoOffset + photoWidth) * 4, (rectTop - photoOffset + photoWidth) * 4,
                                         0, 0, 0, 1024.0f / (photoRectDs / 100.0f), 1024.0f / (photoRectDs / 100.0f));

        // Bar
        if ((i == (this->cursorPageRow + cursorPage)) && (this->scrollAmount == 0)) {
            gDPSetPrimColor(gfx++, 0, 0, sBarColorR, sBarColorG, sBarColorB, 255);
        } else {
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 60);
        }
        gDPLoadTextureBlock(gfx++, &D_080018B0, G_IM_FMT_I, G_IM_SIZ_8b, 8, 4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        BombersNotebook_TextureRectangle(&gfx, (barRectLeft + 57) * 4, (rectTop + 22) * 4,
                                         (barRectLeft - photoOffset + 527) * 4, (rectTop + 26) * 4, 0, 0, 0, 0x400,
                                         0x400);
        gDPLoadTextureBlock_4b(gfx++, &D_08001358, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        BombersNotebook_TextureRectangle(&gfx, (barRectLeft - photoOffset + 527) * 4, (rectTop + 16) * 4,
                                         (barRectLeft - photoOffset + 543) * 4, (rectTop + 32) * 4, 0, 0, 0, 0x400,
                                         0x400);

        if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[i])) {
            gDPPipeSync(gfx++);
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);

            BombersNotebook_DrawEntries(&gfx, i, rectTop);

            gDPPipeSync(gfx++);
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }
    }
    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

TexturePtr sBombersNotebookDigitTextures[] = {
    &D_08002078, &D_08002100, &D_08002188, &D_08002210, &D_08002298,
    &D_08002320, &D_080023A8, &D_08002430, &D_080024B8, &D_08002540,
};
u8 sBombersNotebookDigitRectLeftOffsets[] = { 13, 8, 12, 13, 14, 13, 12, 12, 13, 12 };
s16 sBombersNotebookDayTexRectLeftOffsets[] = { 16, 12, 9 };

#define CURRENT_DAY_MIN_1 ((CURRENT_DAY == 0) ? 1 : CURRENT_DAY)
void BombersNotebook_DrawTimeOfDay(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    u32 timeOfDayRectLeft;
    u32 timeBoxRectLeft;
    u32 connectorRectLeft;
    u32 lineRectLeft;
    u32 digitsRectLeft;
    u16 time;
    s32 onesDigit;
    s32 tensDigit;
    s32 hours;

    time = (((void)0, gSaveContext.save.time) - CLOCK_TIME(6, 0));
    if (CURRENT_DAY == 0) {
        time = 0;
    }
    timeOfDayRectLeft = sBombersNotebookDayRectRectLeft[CURRENT_DAY] + (time / 455);
    if ((CURRENT_DAY_MIN_1 == 1) ||
        ((CURRENT_DAY_MIN_1 == 2) && (((void)0, gSaveContext.save.time) < CLOCK_TIME(12, 0)))) {
        timeOfDayRectLeft -= 32;
        lineRectLeft = timeOfDayRectLeft + 32;
    } else if ((CURRENT_DAY_MIN_1 == 2) && (time >= (CLOCK_TIME(17, 0) - CLOCK_TIME(6, 0))) &&
               (time <= (CLOCK_TIME(19, 0) - CLOCK_TIME(6, 0)))) {
        timeOfDayRectLeft -= 64;
        lineRectLeft = timeOfDayRectLeft + 64;
    } else {
        timeOfDayRectLeft -= 96;
        lineRectLeft = timeOfDayRectLeft + 96;
    }

    // Time of day text box
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_08001950, G_IM_FMT_IA, 64, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, timeOfDayRectLeft * 4, 42 * 4, (timeOfDayRectLeft + 128) * 4, 70 * 4, 0, 0,
                                     0, 0x400, 0x400);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPLoadTextureBlock_4b(gfx++, &D_080032B0, G_IM_FMT_I, 96, 20, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    BombersNotebook_TextureRectangle(&gfx, (timeOfDayRectLeft + 16) * 4, 47 * 4, (timeOfDayRectLeft + 112) * 4, 67 * 4,
                                     0, 0, 0, 0x400, 0x400);

    // Time Box
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    if (((CURRENT_DAY_MIN_1 >= 3) || ((CURRENT_DAY_MIN_1 == 2) && (time > (CLOCK_TIME(18, 0) - CLOCK_TIME(6, 0)))))) {
        timeBoxRectLeft = timeOfDayRectLeft - 159;
        connectorRectLeft = timeOfDayRectLeft - 17;
    } else {
        timeBoxRectLeft = timeOfDayRectLeft + 130;
        connectorRectLeft = timeOfDayRectLeft + 113;
    }

    gDPLoadTextureBlock_4b(gfx++, &D_08001CD0, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, timeBoxRectLeft * 4, 42 * 4, (timeBoxRectLeft + 16) * 4, 70 * 4, 0, 0, 0,
                                     0x400, 0x400);
    gDPLoadTextureBlock_4b(gfx++, &D_08001E90, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (timeBoxRectLeft + 16) * 4, 42 * 4, (timeBoxRectLeft + 141) * 4, 70 * 4, 0,
                                     0, 0, 0x400, 0x400);
    gDPLoadTextureBlock_4b(gfx++, &D_08001DB0, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (timeBoxRectLeft + 141) * 4, 42 * 4, (timeBoxRectLeft + 157) * 4, 70 * 4, 0,
                                     0, 0, 0x400, 0x400);
    gDPLoadTextureBlock(gfx++, sBombersNotebookDayTextures[CURRENT_DAY_MIN_1 - 1], G_IM_FMT_IA, G_IM_SIZ_8b, 48, 22, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    BombersNotebook_TextureRectangle(
        &gfx, (timeBoxRectLeft + sBombersNotebookDayTexRectLeftOffsets[CURRENT_DAY_MIN_1 - 1]) * 4, 46 * 4,
        (timeBoxRectLeft + sBombersNotebookDayTexRectLeftOffsets[CURRENT_DAY_MIN_1 - 1] + 48) * 4, 68 * 4, 0, 0, 0,
        0x400, 0x400);

    gDPSetPrimColor(gfx++, 0, 0, 150, 150, 150, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_08001358, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (timeBoxRectLeft + 56) * 4, 48 * 4, (timeBoxRectLeft + 72) * 4, 0x100, 0, 0,
                                     0, 0x400, 0x400);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

    tensDigit = 0;
    onesDigit = ((void)0, gSaveContext.save.time) / CLOCK_TIME_HOUR;
    if (CURRENT_DAY == 0) {
        onesDigit = 6;
    }
    hours = onesDigit;
    do {
        if (onesDigit >= 10) {
            tensDigit++;
            onesDigit -= 10;
        }
    } while (onesDigit >= 10);

    digitsRectLeft = timeBoxRectLeft + 75;
    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[tensDigit], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, digitsRectLeft * 4, 48 * 4, (digitsRectLeft + 16) * 4, 65 * 4, 0, 0, 0,
                                     0x400, 0x400);

    digitsRectLeft += sBombersNotebookDigitRectLeftOffsets[tensDigit];
    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[onesDigit], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, digitsRectLeft * 4, 48 * 4, (digitsRectLeft + 16) * 4, 65 * 4, 0, 0, 0,
                                     0x400, 0x400);

    digitsRectLeft += sBombersNotebookDigitRectLeftOffsets[onesDigit];
    gDPLoadTextureBlock_4b(gfx++, &D_080025C8, G_IM_FMT_I, 16, 17, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, digitsRectLeft * 4, 48 * 4, (digitsRectLeft + 16) * 4, 65 * 4, 0, 0, 0,
                                     0x400, 0x400);

    digitsRectLeft += 7;
    tensDigit = 0;
    if (CURRENT_DAY == 0) {
        onesDigit = TIME_TO_MINUTES_ALT_F((CLOCK_TIME_F(6, 0) - (hours * CLOCK_TIME_HOUR_F)));
    } else {
        onesDigit = TIME_TO_MINUTES_ALT_F(((void)0, gSaveContext.save.time) - (hours * CLOCK_TIME_HOUR_F));
    }
    do {
        if (onesDigit >= 10) {
            tensDigit++;
            onesDigit -= 10;
        }
    } while (onesDigit >= 10);

    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[tensDigit], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, digitsRectLeft * 4, 48 * 4, (digitsRectLeft + 16) * 4, 65 * 4, 0, 0, 0,
                                     0x400, 0x400);
    digitsRectLeft += sBombersNotebookDigitRectLeftOffsets[tensDigit];
    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[onesDigit], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, digitsRectLeft * 4, 48 * 4, (digitsRectLeft + 16) * 4, 65 * 4, 0, 0, 0,
                                     0x400, 0x400);

    // Connector (Texture that connects time of day text box and the time box)
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPLoadTextureBlock(gfx++, &D_08000880, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 14, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, connectorRectLeft * 4, 49 * 4, (connectorRectLeft + 32) * 4, 63 * 4, 0, 0, 0,
                                     0x400, 0x400);

    // Line
    gDPSetPrimColor(gfx++, 0, 0, 242, 0, 14, 255);
    gDPLoadTextureBlock(gfx++, &D_08001898, G_IM_FMT_I, G_IM_SIZ_8b, 8, 1, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, lineRectLeft * 4, 74 * 4, (lineRectLeft + 32) * 4, 490 * 4, 0, 0, 0, 0x400,
                                     0x400);

    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gfx++, 200, 0, 0, 255);
    gDPLoadTextureBlock(gfx++, &D_08000700, G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (lineRectLeft + -11) * 4, 70 * 4, (lineRectLeft + 13) * 4, 86 * 4, 0, 0, 0,
                                     0x400, 0x400);

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

void BombersNotebook_DrawCursor(BombersNotebook* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 cursorRow;
    s32 cursorEntry;
    s32 entryRight;
    s32 entryRectLeft;
    s32 entryIcon;
    u32 cursorRectLeft;
    u32 cursorRectTop;
    u32 yOffset;
    u16 startTime;
    u16 endTime;

    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 255, 205, 55, 255);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_080018D0, G_IM_FMT_IA, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                           4, 4, G_TX_NOLOD, G_TX_NOLOD);

    if (this->cursorEntry == 0) {
        BombersNotebook_TextureRectangle(&gfx, 47 * 4, (this->cursorPageRow * 52 + 97) * 4, 63 * 4,
                                         (this->cursorPageRow * 52 + 113) * 4, 0, 0, 0, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, 98 * 4, (this->cursorPageRow * 52 + 97) * 4, 114 * 4,
                                         (this->cursorPageRow * 52 + 113) * 4, 0, 0x200, 0, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, 47 * 4, (this->cursorPageRow * 52 + 147) * 4, 63 * 4,
                                         (this->cursorPageRow * 52 + 163) * 4, 0, 0, 0x200, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, 98 * 4, (this->cursorPageRow * 52 + 147) * 4, 114 * 4,
                                         (this->cursorPageRow * 52 + 163) * 4, 0, 0x200, 0x200, 0x400, 0x400);
    } else {
        cursorRow = this->cursorPageRow + this->cursorPage;
        cursorRectTop = (this->cursorPageRow * 52) + 107;
        cursorEntry = this->cursorEntry - 3; // Offset from photo entry
        if (sBombersNotebookEntries[cursorRow][cursorEntry] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
            yOffset = 8;
        } else if (sBombersNotebookEntries[cursorRow][cursorEntry] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW) {
            yOffset = 24;
        } else { // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
            yOffset = 16;
        }

        startTime = sBombersNotebookEntries[cursorRow][cursorEntry + 1] - CLOCK_TIME(6, 0);
        endTime = sBombersNotebookEntries[cursorRow][cursorEntry + 2] - CLOCK_TIME(6, 0);
        entryRectLeft =
            sBombersNotebookDayRectRectLeft[(sBombersNotebookEntries[cursorRow][cursorEntry] & 0xF00) >> 8] +
            (startTime / 455);
        entryRight = sBombersNotebookDayRectRectLeft[(sBombersNotebookEntries[cursorRow][cursorEntry] & 0xF00) >> 8] +
                     (endTime / 455);
        if ((entryRight - entryRectLeft) < 8) {
            entryRectLeft = ((entryRectLeft + entryRight) - entryRectLeft) - 8;
            entryRight = entryRectLeft + 8;
        }
        entryIcon = sBombersNotebookEventIcons[(sBombersNotebookEntries[cursorRow][cursorEntry] & 0xFF) - 20];
        if ((entryRight - entryRectLeft) < sBombersNotebookEventIconWidths[entryIcon]) {
            cursorRectLeft =
                (((entryRectLeft - sBombersNotebookEventIconWidths[entryIcon]) + entryRight) - entryRectLeft) + 3;
        } else {
            cursorRectLeft =
                (((entryRight - entryRectLeft) - sBombersNotebookEventIconWidths[entryIcon]) / 2) + entryRectLeft;
        }
        if (entryIcon == BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT) {
            cursorRectLeft -= 8;
            cursorRectTop -= 8;
        } else {
            cursorRectLeft -= 9;
            cursorRectTop -= 8;
        }
        if ((entryIcon == BOMBERSNOTEBOOK_EVENT_ICON_MASK) || (entryIcon == BOMBERSNOTEBOOK_EVENT_ICON_RIBBON)) {
            if (sBombersNotebookEntries[cursorRow][cursorEntry] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
                yOffset -= 12;
            } else if (!(sBombersNotebookEntries[cursorRow][cursorEntry] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW)) {
                // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
                yOffset -= 6;
            }
        }
        BombersNotebook_TextureRectangle(&gfx, cursorRectLeft * 4, (cursorRectTop + yOffset) * 4,
                                         (cursorRectLeft + 16) * 4, (cursorRectTop + yOffset + 16) * 4, 0, 0, 0, 0x400,
                                         0x400);
        BombersNotebook_TextureRectangle(&gfx, (cursorRectLeft + sBombersNotebookEventIconWidths[entryIcon]) * 4,
                                         (cursorRectTop + yOffset) * 4,
                                         (cursorRectLeft + sBombersNotebookEventIconWidths[entryIcon] + 16) * 4,
                                         (cursorRectTop + yOffset + 16) * 4, 0, 0x200, 0, 0x400, 0x400);
        BombersNotebook_TextureRectangle(
            &gfx, cursorRectLeft * 4, (cursorRectTop + yOffset + sBombersNotebookEventIconHeights[entryIcon]) * 4,
            (cursorRectLeft + 16) * 4, (cursorRectTop + yOffset + sBombersNotebookEventIconHeights[entryIcon] + 16) * 4,
            0, 0, 0x200, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, (cursorRectLeft + sBombersNotebookEventIconWidths[entryIcon]) * 4,
                                         (cursorRectTop + yOffset + sBombersNotebookEventIconHeights[entryIcon]) * 4,
                                         (cursorRectLeft + sBombersNotebookEventIconWidths[entryIcon] + 16) * 4,
                                         (cursorRectTop + yOffset + sBombersNotebookEventIconHeights[entryIcon] + 16) *
                                             4,
                                         0, 0x200, 0x200, 0x400, 0x400);
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

void BombersNotebook_DrawArrows(BombersNotebook* this, Gfx** gfxP) {
    static s16 sUpperArrowColorR = 0;
    static s16 sUpperArrowColorG = 100;
    static s16 sUpperArrowColorB = 255;
    static s16 sLowerArrowColorR = 0;
    static s16 sLowerArrowColorG = 100;
    static s16 sLowerArrowColorB = 255;
    static s16 sUpperArrowColorIndex = 0;
    static s16 sLowerArrowColorIndex = 0;
    static s16 sUpperArrowColorTimer = 6;
    static s16 sLowerArrowColorTimer = 6;
    static s16 sUpperArrowOffsetY = 0;
    static s16 sLowerArrowOffsetY = 0;
    static s16 sArrowColorTargetsG[2] = { 175, 100 };
    static s16 sArrowColorTargetsB[2] = { 205, 255 };
    Gfx* gfx = *gfxP;
    u32 rectTop;
    s16 colorStep;

    gDPPipeSync(gfx++);
    gDPLoadTextureBlock(gfx++, &D_08000700, G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, 4, G_TX_NOLOD, G_TX_NOLOD);

    colorStep = ABS_ALT(sUpperArrowColorG - sArrowColorTargetsG[sUpperArrowColorIndex]) / sUpperArrowColorTimer;
    if (sUpperArrowColorG >= sArrowColorTargetsG[sUpperArrowColorIndex]) {
        sUpperArrowColorG -= colorStep;
    } else {
        sUpperArrowColorG += colorStep;
    }

    colorStep = ABS_ALT(sUpperArrowColorB - sArrowColorTargetsB[sUpperArrowColorIndex]) / sUpperArrowColorTimer;
    if (sUpperArrowColorB >= sArrowColorTargetsB[sUpperArrowColorIndex]) {
        sUpperArrowColorB -= colorStep;
    } else {
        sUpperArrowColorB += colorStep;
    }

    sUpperArrowColorTimer--;
    if (sUpperArrowColorTimer == 0) {
        sUpperArrowOffsetY ^= 6;
        sUpperArrowColorTimer = 6;
        sUpperArrowColorG = sArrowColorTargetsG[sUpperArrowColorIndex];
        sUpperArrowColorB = sArrowColorTargetsB[sUpperArrowColorIndex];
        sUpperArrowColorIndex ^= 1;
    }

    colorStep = ABS_ALT(sLowerArrowColorG - sArrowColorTargetsG[sLowerArrowColorIndex]) / sLowerArrowColorTimer;
    if (sLowerArrowColorG >= sArrowColorTargetsG[sLowerArrowColorIndex]) {
        sLowerArrowColorG -= colorStep;
    } else {
        sLowerArrowColorG += colorStep;
    }

    colorStep = ABS_ALT(sLowerArrowColorB - sArrowColorTargetsB[sLowerArrowColorIndex]) / sLowerArrowColorTimer;
    if (sLowerArrowColorB >= sArrowColorTargetsB[sLowerArrowColorIndex]) {
        sLowerArrowColorB -= colorStep;
    } else {
        sLowerArrowColorB += colorStep;
    }

    sLowerArrowColorTimer--;
    if (sLowerArrowColorTimer == 0) {
        sLowerArrowOffsetY ^= 6;
        sLowerArrowColorTimer = 6;
        sLowerArrowColorG = sArrowColorTargetsG[sLowerArrowColorIndex];
        sLowerArrowColorB = sArrowColorTargetsB[sLowerArrowColorIndex];
        sLowerArrowColorIndex ^= 1;
    }

    if (this->cursorPage != 0) {
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, sUpperArrowColorR, sUpperArrowColorG, sUpperArrowColorB, 255);
        gDPSetEnvColor(gfx++, sUpperArrowColorR, sUpperArrowColorG, sUpperArrowColorB, 255);
        rectTop = (-sUpperArrowOffsetY + 83) * 4;
        BombersNotebook_TextureRectangle(&gfx, 46 * 4, rectTop, 70 * 4, rectTop + (16 * 4), 0, 0, 0x200, 0x400, 0x400);
    }

    if (this->cursorPage < 16) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, sLowerArrowColorR, sLowerArrowColorG, sLowerArrowColorB, 255);
        gDPSetEnvColor(gfx++, sLowerArrowColorR, sLowerArrowColorG, sLowerArrowColorB, 255);
        BombersNotebook_TextureRectangle(&gfx, 46 * 4, (sLowerArrowOffsetY + 319) * 4, 70 * 4,
                                         (sLowerArrowOffsetY + 335) * 4, 0, 0, 0, 0x400, 0x400);
    }
    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

void BombersNotebook_Draw(BombersNotebook* this, GraphicsContext* gfxCtx) {
    Gfx* gfx;
    s32 pad[2];

    func_8012CF0C(gfxCtx, this->loadState != BOMBERSNOTEBOOK_LOAD_STATE_DONE, false, 0, 0, 0);

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;

    if (this->loadState == BOMBERSNOTEBOOK_LOAD_STATE_DONE) {
        gSPSegment(gfx++, 0x07, this->scheduleDmaSegment);
        gSPSegment(gfx++, 0x08, this->scheduleSegment);
        gfx = func_8012C600(gfx);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 215, 255);
        gDPSetEnvColor(gfx++, 100, 100, 100, 255);
        gDPLoadTextureBlock(gfx++, &D_080013D8, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

        BombersNotebook_TextureRectangle(&gfx, 0 * 4, 0 * 4, SCREEN_WIDTH_HIRES * 4, SCREEN_HEIGHT_HIRES * 4, 0, 0, 0,
                                         0x200, 0x200);

        gDPPipeSync(gfx++);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

        BombersNotebook_DrawHeaders(&gfx);
        BombersNotebook_DrawColumns(&gfx);

        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 86, 600, 450);
        BombersNotebook_DrawRows(this, &gfx);

        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, D_0E000000.setScissor);

        BombersNotebook_DrawTimeOfDay(&gfx);

        if (this->scrollAmount == 0) {
            BombersNotebook_DrawCursor(this, &gfx);
        }
        BombersNotebook_DrawArrows(this, &gfx);
    }
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

void BombersNotebook_LoadFiles(BombersNotebook* this, s32 flag) {
    switch (this->loadState) {
        case BOMBERSNOTEBOOK_LOAD_STATE_NONE:
            if (this->scheduleDmaSegment == NULL) {
                break;
            }
            CmpDma_LoadAllFiles(this->scheduleDmaSegmentStart, this->scheduleDmaSegment, this->scheduleDmaSegmentSize);
            osCreateMesgQueue(&this->loadQueue, this->loadMsg, ARRAY_COUNT(this->loadMsg));
            DmaMgr_SendRequestImpl(&this->dmaRequest, this->scheduleSegment, this->scheduleSegmentStart,
                                   this->scheduleSegmentSize, 0, &this->loadQueue, NULL);
            this->loadState = BOMBERSNOTEBOOK_LOAD_STATE_STARTED;
            // fall-through
        case BOMBERSNOTEBOOK_LOAD_STATE_STARTED:
            if (osRecvMesg(&this->loadQueue, NULL, flag) == 0) {
                this->loadState = BOMBERSNOTEBOOK_LOAD_STATE_DONE;
            }
    }
}

u16 sBombersNotebookTextIds[] = {
    /* People */
    /* 00 */ 0x21DD,
    /* 01 */ 0x21CA,
    /* 02 */ 0x21CB,
    /* 03 */ 0x21CC,
    /* 04 */ 0x21CD,
    /* 05 */ 0x21CE,
    /* 06 */ 0x21CF,
    /* 07 */ 0x21D0,
    /* 08 */ 0x21D1,
    /* 09 */ 0x21D2,
    /* 10 */ 0x21D3,
    /* 11 */ 0x21D4,
    /* 12 */ 0x21D5,
    /* 13 */ 0x21D6,
    /* 14 */ 0x21D7,
    /* 15 */ 0x21D8,
    /* 16 */ 0x21D9,
    /* 17 */ 0x21DA,
    /* 18 */ 0x21DB,
    /* 19 */ 0x21DC,

    /* Events (add 20 to get full index) */
    /* 00 */ 0x2198,
    /* 01 */ 0x2199,
    /* 02 */ 0x219A,
    /* 03 */ 0x219B,
    /* 04 */ 0x219C,
    /* 05 */ 0x219D,
    /* 06 */ 0x219E,
    /* 07 */ 0x219F,
    /* 08 */ 0x21A0,
    /* 09 */ 0x21A1,
    /* 10 */ 0x21A2,
    /* 11 */ 0x21A3,
    /* 12 */ 0x21A4,
    /* 13 */ 0x21A5,
    /* 14 */ 0x21A6,
    /* 15 */ 0x21A7,
    /* 16 */ 0x21A8,
    /* 17 */ 0x21A9,
    /* 18 */ 0x21AA,
    /* 19 */ 0x21AB,
    /* 20 */ 0x21AC,
    /* 21 */ 0x21AD,
    /* 22 */ 0x21AE,
    /* 23 */ 0x21AF,
    /* 24 */ 0x21B0,
    /* 25 */ 0x21B1,
    /* 26 */ 0x21B2,
    /* 27 */ 0x21B3,
    /* 28 */ 0x21B4,
    /* 29 */ 0x21B5,
    /* 30 */ 0x21B6,
    /* 31 */ 0x21B7,
    /* 32 */ 0x21B8,
    /* 33 */ 0x21B9,
    /* 34 */ 0x21BA,
};

void BombersNotebook_Update(PlayState* play, BombersNotebook* this, Input* input) {
    static s16 sStickXRepeatTimer = 0;
    static s16 sStickYRepeatTimer = 0;
    static s16 sStickXRepeatState = 0;
    static s16 sStickYRepeatState = 0;
    s32 stickAdjX = input->rel.stick_x;
    s32 stickAdjY = input->rel.stick_y;
    s32 cursorEntryScan;

    this->scheduleDmaSegmentStart = SEGMENT_ROM_START(schedule_dma_static_test);
    this->scheduleDmaSegmentSize = SEGMENT_ROM_SIZE(schedule_dma_static_old);
    this->scheduleSegmentStart = SEGMENT_ROM_START(schedule_static);
    this->scheduleSegmentSize = SEGMENT_ROM_SIZE(schedule_static);

    if (this->scheduleDmaSegment == NULL) {
        this->scheduleDmaSegment = ZeldaArena_Malloc(this->scheduleDmaSegmentSize);
    }

    if (this->scheduleSegment == NULL) {
        this->scheduleSegment = ZeldaArena_Malloc(this->scheduleSegmentSize);
    }

    BombersNotebook_LoadFiles(this, OS_MESG_NOBLOCK);

    if (this->loadState == BOMBERSNOTEBOOK_LOAD_STATE_DONE) {
        if (stickAdjX < -30) {
            if (sStickXRepeatState == -1) {
                sStickXRepeatTimer--;
                if (sStickXRepeatTimer < 0) {
                    sStickXRepeatTimer = 2;
                } else {
                    stickAdjX = 0;
                }
            } else {
                sStickXRepeatTimer = 10;
                sStickXRepeatState = -1;
            }
        } else if (stickAdjX > 30) {
            if (sStickXRepeatState == 1) {
                sStickXRepeatTimer--;
                if (sStickXRepeatTimer < 0) {
                    sStickXRepeatTimer = 2;
                } else {
                    stickAdjX = 0;
                }
            } else {
                sStickXRepeatTimer = 10;
                sStickXRepeatState = 1;
            }
        } else {
            sStickXRepeatState = 0;
        }

        if (stickAdjY < -30) {
            if (sStickYRepeatState == -1) {
                sStickYRepeatTimer--;
                if (sStickYRepeatTimer < 0) {
                    sStickYRepeatTimer = 2;
                } else {
                    stickAdjY = 0;
                }
            } else {
                sStickYRepeatTimer = 10;
                sStickYRepeatState = -1;
            }
        } else if (stickAdjY > 30) {
            if (sStickYRepeatState == 1) {
                sStickYRepeatTimer--;
                if (sStickYRepeatTimer < 0) {
                    sStickYRepeatTimer = 2;
                } else {
                    stickAdjY = 0;
                }
            } else {
                sStickYRepeatTimer = 10;
                sStickYRepeatState = 1;
            }
        } else {
            sStickYRepeatState = 0;
        }

        if (this->scrollAmount == 0) {
            if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[this->cursorPageRow + this->cursorPage])) {
                cursorEntryScan = this->cursorEntry;
                if (stickAdjX > 30) {
                    while (true) {
                        cursorEntryScan += 3;
                        if (sBombersNotebookEntries[this->cursorPageRow + this->cursorPage][cursorEntryScan - 3] ==
                            BOMBERSNOTEBOOK_ENTRY_END) {
                            while (true) {
                                cursorEntryScan -= 3;
                                if (cursorEntryScan == 0) {
                                    play_sound(NA_SE_SY_ERROR);
                                    break;
                                }
                                if (CHECK_WEEKEVENTREG(
                                        gBombersNotebookWeekEventFlags[((sBombersNotebookEntries[this->cursorPageRow +
                                                                                                 this->cursorPage]
                                                                                                [cursorEntryScan - 3] &
                                                                         0xFF) -
                                                                        20) +
                                                                       20])) {
                                    play_sound(NA_SE_SY_ERROR);
                                    break;
                                }
                            }
                            break;
                        }
                        if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags
                                                   [((sBombersNotebookEntries[this->cursorPageRow + this->cursorPage]
                                                                             [cursorEntryScan - 3] &
                                                      0xFF) -
                                                     20) +
                                                    20])) {
                            play_sound(NA_SE_SY_CURSOR);
                            break;
                        }
                    }
                    this->cursorEntry = cursorEntryScan;
                } else if (stickAdjX < -30) {
                    if (cursorEntryScan != 0) {
                        do {
                            cursorEntryScan -= 3;
                            if (CHECK_WEEKEVENTREG(
                                    gBombersNotebookWeekEventFlags[((sBombersNotebookEntries[this->cursorPageRow +
                                                                                             this->cursorPage]
                                                                                            [cursorEntryScan - 3] &
                                                                     0xFF) -
                                                                    20) +
                                                                   20])) {
                                play_sound(NA_SE_SY_CURSOR);
                                break;
                            }
                        } while (cursorEntryScan != 0);
                        this->cursorEntry = cursorEntryScan;
                    }
                }
                if (this->cursorEntry != 0) {
                    if (play->msgCtx.currentTextId !=
                        sBombersNotebookTextIds[((sBombersNotebookEntries[this->cursorPageRow + this->cursorPage]
                                                                         [this->cursorEntry - 3] &
                                                  0xFF) -
                                                 20) +
                                                20]) {
                        Message_ContinueTextbox(
                            play,
                            sBombersNotebookTextIds[sBombersNotebookEntries[this->cursorPageRow + this->cursorPage]
                                                                           [this->cursorEntry - 3] &
                                                    0xFF]);
                    }
                } else {
                    if (play->msgCtx.currentTextId != sBombersNotebookTextIds[this->cursorPageRow + this->cursorPage]) {
                        Message_ContinueTextbox(play, sBombersNotebookTextIds[this->cursorPageRow + this->cursorPage]);
                    }
                }
            } else {
                Message_CloseTextbox(play);
            }

            if (stickAdjY < -30) {
                if (this->cursorPageRow < 3) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->cursorEntry = 0;
                    this->cursorPageRow++;
                } else if (this->cursorPage < 16) {
                    if (sStickYRepeatState == -1) {
                        this->scrollAmount = -24;
                    } else {
                        this->scrollAmount = -12;
                    }
                    this->scrollOffset = 0;
                    this->cursorEntry = 0;
                }
            } else if (stickAdjY > 30) {
                if (this->cursorPageRow > 0) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->cursorEntry = 0;
                    this->cursorPageRow--;
                } else if (this->cursorPage != 0) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->cursorPage--;
                    if (sStickYRepeatState == 1) {
                        this->scrollAmount = 24;
                    } else {
                        this->scrollAmount = 12;
                    }
                    this->scrollOffset = -48;
                    this->cursorEntry = 0;
                }
            }
        } else if (this->scrollAmount < 0) {
            this->scrollOffset += this->scrollAmount;
            if (ABS_ALT(this->scrollOffset) >= 48) {
                play_sound(NA_SE_SY_CURSOR);
                this->scrollOffset = 0;
                this->scrollAmount = 0;
                this->cursorPage++;
            }
        } else {
            this->scrollOffset += this->scrollAmount;
            if (this->scrollOffset == 0) {
                this->scrollOffset = 0;
                this->scrollAmount = 0;
            }
        }
    }
}

void BombersNotebook_Init(BombersNotebook* this) {
    bzero(this, sizeof(BombersNotebook));
}

void BombersNotebook_Destroy(BombersNotebook* this) {
    if (this->loadState == BOMBERSNOTEBOOK_LOAD_STATE_STARTED) {
        BombersNotebook_LoadFiles(this, OS_MESG_BLOCK);
    }
    if (this->scheduleDmaSegment != NULL) {
        ZeldaArena_Free(this->scheduleDmaSegment);
        this->scheduleDmaSegment = NULL;
    }
    //! @bug: Does not free malloc'd memory for schedule segment
}
