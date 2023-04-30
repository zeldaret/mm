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

s16 sBombersNotebookDayStartX[] = { 120, 120, 270, 420 };
TexturePtr sBombersNotebookDayTextures[] = { &D_08002650, &D_08002A70, &D_08002E90 };

s32 sBombersNotebookEventIcons[] = {
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_RIBBON,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
    BOMBERSNOTEBOOK_EVENT_ICON_MASK,
};
s32 sBombersNotebookEventIconOffsetsX[] = { 16, 24, 32 };
s32 sBombersNotebookEventIconOffsetsY[] = { 16, 28, 28 };
u16 sBombersNotebookEventColorWeekEventFlags[] = {
    WEEKEVENTREG_75_10,
    WEEKEVENTREG_50_08,
    WEEKEVENTREG_50_20,
    WEEKEVENTREG_50_20,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_DELIVERED_LETTER,
    WEEKEVENTREG_50_80,
    WEEKEVENTREG_51_01,
    WEEKEVENTREG_51_20,
    WEEKEVENTREG_21_20,
    WEEKEVENTREG_22_01,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    WEEKEVENTREG_52_01,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    WEEKEVENTREG_80_10,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
    BOMBERSNOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE,
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
    s32 xStart;

    gDPLoadTextureBlock(gfx++, &D_080017D8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 24, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for (i = 0, xStart = 120; i < 3; i++, xStart += 150) {
        gDPSetPrimColor(gfx++, 0, 0, sBombersNotebookHeaderColors[i][0], sBombersNotebookHeaderColors[i][1],
                        sBombersNotebookHeaderColors[i][2], 192);
        BombersNotebook_TextureRectangle(&gfx, xStart * 4, 74 * 4, (xStart + 143) * 4, 98 * 4, 0, 0, 0, 0x400, 0x400);
    }

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    for (i = 0, xStart = 124; i < 3; i++, xStart += 150) {
        gDPLoadTextureBlock(gfx++, sBombersNotebookDayTextures[i], G_IM_FMT_IA, G_IM_SIZ_8b, 48, 22, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        BombersNotebook_TextureRectangle(&gfx, xStart * 4, 77 * 4, (xStart + 48) * 4, 99 * 4, 0, 0, 0, 0x400, 0x400);
    }

    xStart = 172;
    gDPLoadTextureBlock_4b(gfx++, &D_08001F70, G_IM_FMT_IA, 48, 11, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for (i = 0; i < 3; i++) {
        BombersNotebook_TextureRectangle(&gfx, xStart * 4, 86 * 4, (xStart + 48) * 4, 97 * 4, 0, 0, 0, 0x400, 0x400);
        xStart += 150;
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
    s32 columnXStart;
    s32 subColumnXStart;
    s32 pad;

    gDPLoadTextureBlock_4b(gfx++, &D_08001340, G_IM_FMT_I, 48, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    color = &sBombersNotebookColumnColors[0][0][0];
    for (i = 0, columnXStart = 120; i < 3; i++, columnXStart += 150) {
        subColumnXStart = columnXStart;
        for (j = 0; j < 2; j++) {
            gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], 192);
            for (k = 0; k < 2; k++) {
                BombersNotebook_TextureRectangle(&gfx, subColumnXStart * 4, 104 * 4, (subColumnXStart + 48) * 4,
                                                 480 * 4, 0, 0, 0, 0x400, 0x400);
                subColumnXStart += 36;
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

void BombersNotebook_DrawEntries(Gfx** gfxP, s32 row, u32 yStart) {
    Gfx* gfx = *gfxP;
    s32 entryXStart;
    u32 eventIcon;
    u32 unfinishedEvent = false;
    u16 startTime;
    u16 endTime;
    s32 j = 0;
    u32 iconXStart;
    s32 entryXEnd;
    u32 yOffset;
    s32 entryWidth;

    while (true) {
        if (sBombersNotebookEntries[row][j] == BOMBERSNOTEBOOK_ENTRY_END) {
            if (!unfinishedEvent) {
                gDPPipeSync(gfx++);
                gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                                  PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
                gDPSetEnvColor(gfx++, 0, 0, 0, 255);
                gDPLoadTextureBlock(gfx++, &D_08000100, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 48, 0, G_TX_MIRROR | G_TX_WRAP,
                                    G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                BombersNotebook_TextureRectangle(&gfx, 567 * 4, (yStart + 1) * 4, 599 * 4, (yStart + 49) * 4, 0, 0, 0,
                                                 0x400, 0x400);
                gDPPipeSync(gfx++);
                gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
                gDPSetEnvColor(gfx++, 255, 0, 0, 255);
                BombersNotebook_TextureRectangle(&gfx, 565 * 4, (yStart + -1) * 4, 597 * 4, (yStart + 47) * 4, 0, 0, 0,
                                                 0x400, 0x400);
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
        entryXStart = sBombersNotebookDayStartX[(sBombersNotebookEntries[row][j] & 0xF00) >> 8] + (startTime / 455);
        entryXEnd = sBombersNotebookDayStartX[(sBombersNotebookEntries[row][j] & 0xF00) >> 8] + (endTime / 455);
        entryWidth = entryXEnd - entryXStart - 8;
        if ((entryXEnd - entryXStart) < 8) {
            entryXStart = ((entryXStart + entryXEnd) - entryXStart) - 8;
            entryXEnd = entryXStart + 8;
        }

        // Black shadow
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
        gDPLoadTextureBlock(gfx++, &D_08001240, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        BombersNotebook_TextureRectangle(&gfx, (entryXStart + 2) * 4, (yStart + yOffset + 2) * 4, (entryXStart + 6) * 4,
                                         (yStart + yOffset + 18) * 4, 0, 0, 0, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, (entryXEnd + -2) * 4, (yStart + yOffset + 2) * 4, (entryXEnd + 2) * 4,
                                         (yStart + yOffset + 18) * 4, 0, 0x80, 0, 0x400, 0x400);
        if (entryWidth > 0) {
            gDPLoadTextureBlock(gfx++, &D_080012C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                                G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            BombersNotebook_TextureRectangle(&gfx, (entryXStart + 6) * 4, (yStart + yOffset + 2) * 4,
                                             (entryXStart + 6 + entryWidth) * 4, (yStart + yOffset + 18) * 4, 0, 0, 0,
                                             0x400, 0x400);
        }

        // Blue Box
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        gDPLoadTextureBlock(gfx++, &D_08001240, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        //! FAKE: the ^ 0
        BombersNotebook_TextureRectangle(&gfx, (entryXStart * 4) ^ 0, (yStart + yOffset) * 4, (entryXStart + 4) * 4,
                                         (yStart + yOffset + 16) * 4, 0, 0, 0, 0x400, 0x400);
        //! FAKE: the ^ 0
        BombersNotebook_TextureRectangle(&gfx, (entryXEnd + -4) * 4, (yStart + yOffset) * 4, (entryXEnd * 4) ^ 0,
                                         (yStart + yOffset + 16) * 4, 0, 0x80, 0, 0x400, 0x400);
        if (entryWidth > 0) {
            gDPLoadTextureBlock(gfx++, &D_080012C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                                G_TX_MIRROR | G_TX_WRAP, 2, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            BombersNotebook_TextureRectangle(&gfx, (entryXStart + 4) * 4, (yStart + yOffset) * 4,
                                             (entryXStart + 4 + entryWidth) * 4, (yStart + yOffset + 16) * 4, 0, 0, 0,
                                             0x400, 0x400);
        }
        if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[sBombersNotebookEntries[row][j] & 0xFF])) {
            eventIcon = sBombersNotebookEventIcons[(sBombersNotebookEntries[row][j] & 0xFF) - 20];
            if ((entryXEnd - entryXStart) < sBombersNotebookEventIconOffsetsX[eventIcon]) {
                iconXStart =
                    (((entryXStart - sBombersNotebookEventIconOffsetsX[eventIcon]) + entryXEnd) - entryXStart) + 3;
            } else {
                iconXStart =
                    (((entryXEnd - entryXStart) - sBombersNotebookEventIconOffsetsX[eventIcon]) / 2) + entryXStart;
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
                                sBombersNotebookEventIconOffsetsX[eventIcon],
                                sBombersNotebookEventIconOffsetsY[eventIcon], 0, G_TX_MIRROR | G_TX_WRAP,
                                G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

            BombersNotebook_TextureRectangle(&gfx, (iconXStart + 2) * 4, (yStart + yOffset + 2) * 4,
                                             (iconXStart + 2 + sBombersNotebookEventIconOffsetsX[eventIcon]) * 4,
                                             (yStart + yOffset + 2 + sBombersNotebookEventIconOffsetsY[eventIcon]) * 4,
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
            BombersNotebook_TextureRectangle(&gfx, iconXStart * 4, (yStart + yOffset) * 4,
                                             (iconXStart + sBombersNotebookEventIconOffsetsX[eventIcon]) * 4,
                                             (yStart + yOffset + sBombersNotebookEventIconOffsetsY[eventIcon]) * 4, 0,
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
    s32 var_t1;
    s32 sp134;
    s32 sp130;
    u32 sp12C;
    f32 sp128;
    u32 sp124;
    s32 i;
    u32 yStart;
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

    yStart = this->scrollOffset + 107;
    if (this->cursorPage >= 12) {
        sp134 = 20;
        i = this->cursorPage;
    } else {
        sp134 = this->cursorPage + 8;
        i = sp134 - 8;
    }
    sp130 = i;
    for (; i < sp134; i++, yStart += 52) {
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[i])) {
            gDPLoadTextureBlock(gfx++, sBombersNotebookPhotoTextures[i], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(gfx++, &D_08000A40, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        }

        if ((i == (this->cursorPageRow + sp130)) && (this->scrollAmount == 0)) {
            sp12C = 56;
            sp124 = 8;
            sp128 = 200.0f;
            var_t1 = 64;
        } else {
            sp12C = 48;
            sp124 = 0;
            sp128 = 150.0f;
            var_t1 = 48;
        }

        BombersNotebook_TextureRectangle(&gfx, (57 - sp124) * 4, (yStart - sp124) * 4, (57 - sp124 + var_t1) * 4,
                                         (yStart - sp124 + var_t1) * 4, 0, 0, 0, 1024.0f / (sp128 / 100.0f),
                                         1024.0f / (sp128 / 100.0f));
        if ((i == (this->cursorPageRow + sp130)) && (this->scrollAmount == 0)) {
            gDPSetPrimColor(gfx++, 0, 0, sBarColorR, sBarColorG, sBarColorB, 255);
        } else {
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 60);
        }
        gDPLoadTextureBlock(gfx++, &D_080018B0, G_IM_FMT_I, G_IM_SIZ_8b, 8, 4, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        BombersNotebook_TextureRectangle(&gfx, (sp12C + 57) * 4, (yStart + 22) * 4, (sp12C - sp124 + 527) * 4,
                                         (yStart + 26) * 4, 0, 0, 0, 0x400, 0x400);
        gDPLoadTextureBlock_4b(gfx++, &D_08001358, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        BombersNotebook_TextureRectangle(&gfx, (sp12C - sp124 + 527) * 4, (yStart + 16) * 4, (sp12C - sp124 + 543) * 4,
                                         (yStart + 32) * 4, 0, 0, 0, 0x400, 0x400);
        if (CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[i])) {
            gDPPipeSync(gfx++);
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);

            BombersNotebook_DrawEntries(&gfx, i, yStart);

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
u8 sBombersNotebookDigitOffsetsX[] = { 13, 8, 12, 13, 14, 13, 12, 12, 13, 12 };
s16 sBombersNotebookDayTexOffsetsX[] = { 16, 12, 9 };

#define CURRENT_DAY_MIN_1 ((CURRENT_DAY == 0) ? 1 : CURRENT_DAY)
void BombersNotebook_DrawTimeOfDay(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    u32 xStart;
    u32 sp25C;
    u32 sp258;
    u32 lineXStart;
    u32 sp250;
    u16 time;
    s32 sp248;
    s32 sp244;
    s32 sp240;

    time = (((void)0, gSaveContext.save.time) - CLOCK_TIME(6, 0));
    if (CURRENT_DAY == 0) {
        time = 0;
    }
    xStart = sBombersNotebookDayStartX[CURRENT_DAY] + (time / 455);
    if ((CURRENT_DAY_MIN_1 == 1) ||
        ((CURRENT_DAY_MIN_1 == 2) && (((void)0, gSaveContext.save.time) < CLOCK_TIME(12, 0)))) {
        xStart -= 32;
        lineXStart = xStart + 32;
    } else if ((CURRENT_DAY_MIN_1 == 2) && (time >= (CLOCK_TIME(17, 0) - CLOCK_TIME(6, 0))) &&
               (time <= (CLOCK_TIME(19, 0) - CLOCK_TIME(6, 0)))) {
        xStart -= 64;
        lineXStart = xStart + 64;
    } else {
        xStart -= 96;
        lineXStart = xStart + 96;
    }

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_08001950, G_IM_FMT_IA, 64, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 6, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, xStart * 4, 42 * 4, (xStart + 128) * 4, 70 * 4, 0, 0, 0, 0x400, 0x400);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPLoadTextureBlock_4b(gfx++, &D_080032B0, G_IM_FMT_I, 96, 20, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    BombersNotebook_TextureRectangle(&gfx, (xStart + 16) * 4, 47 * 4, (xStart + 112) * 4, 67 * 4, 0, 0, 0, 0x400,
                                     0x400);
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    if (((CURRENT_DAY_MIN_1 >= 3) || ((CURRENT_DAY_MIN_1 == 2) && (time > (CLOCK_TIME(18, 0) - CLOCK_TIME(6, 0)))))) {
        sp25C = xStart - 159;
        sp258 = xStart - 17;
    } else {
        sp25C = xStart + 130;
        sp258 = xStart + 113;
    }
    gDPLoadTextureBlock_4b(gfx++, &D_08001CD0, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, sp25C * 4, 42 * 4, (sp25C + 16) * 4, 70 * 4, 0, 0, 0, 0x400, 0x400);
    gDPLoadTextureBlock_4b(gfx++, &D_08001E90, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (sp25C + 16) * 4, 42 * 4, (sp25C + 141) * 4, 70 * 4, 0, 0, 0, 0x400, 0x400);
    gDPLoadTextureBlock_4b(gfx++, &D_08001DB0, G_IM_FMT_IA, 16, 28, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (sp25C + 141) * 4, 42 * 4, (sp25C + 157) * 4, 70 * 4, 0, 0, 0, 0x400, 0x400);
    gDPLoadTextureBlock(gfx++, sBombersNotebookDayTextures[CURRENT_DAY_MIN_1 - 1], G_IM_FMT_IA, G_IM_SIZ_8b, 48, 22, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (sp25C + sBombersNotebookDayTexOffsetsX[CURRENT_DAY_MIN_1 - 1]) * 4, 46 * 4,
                                     (sp25C + sBombersNotebookDayTexOffsetsX[CURRENT_DAY_MIN_1 - 1] + 48) * 4, 68 * 4,
                                     0, 0, 0, 0x400, 0x400);

    gDPSetPrimColor(gfx++, 0, 0, 150, 150, 150, 255);
    gDPLoadTextureBlock_4b(gfx++, &D_08001358, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (sp25C + 56) * 4, 48 * 4, (sp25C + 72) * 4, 0x100, 0, 0, 0, 0x400, 0x400);
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

    sp250 = sp25C + 75;
    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[sp244], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, sp250 * 4, 48 * 4, (sp250 + 16) * 4, 65 * 4, 0, 0, 0, 0x400, 0x400);

    sp250 += sBombersNotebookDigitOffsetsX[sp244];
    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[sp248], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, sp250 * 4, 48 * 4, (sp250 + 16) * 4, 65 * 4, 0, 0, 0, 0x400, 0x400);

    sp250 += sBombersNotebookDigitOffsetsX[sp248];
    gDPLoadTextureBlock_4b(gfx++, &D_080025C8, G_IM_FMT_I, 16, 17, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, sp250 * 4, 48 * 4, (sp250 + 16) * 4, 65 * 4, 0, 0, 0, 0x400, 0x400);

    sp250 += 7;
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

    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[sp244], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, sp250 * 4, 48 * 4, (sp250 + 16) * 4, 65 * 4, 0, 0, 0, 0x400, 0x400);
    sp250 += sBombersNotebookDigitOffsetsX[sp244];
    gDPLoadTextureBlock_4b(gfx++, sBombersNotebookDigitTextures[sp248], G_IM_FMT_I, 16, 17, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, sp250 * 4, 48 * 4, (sp250 + 16) * 4, 65 * 4, 0, 0, 0, 0x400, 0x400);

    // Connecting Bar? (Between time of day text box and the time box)
    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPLoadTextureBlock(gfx++, &D_08000880, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 14, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, sp258 * 4, 49 * 4, (sp258 + 32) * 4, 63 * 4, 0, 0, 0, 0x400, 0x400);

    // Red Line
    gDPSetPrimColor(gfx++, 0, 0, 242, 0, 14, 255);
    gDPLoadTextureBlock(gfx++, &D_08001898, G_IM_FMT_I, G_IM_SIZ_8b, 8, 1, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, lineXStart * 4, 74 * 4, (lineXStart + 32) * 4, 490 * 4, 0, 0, 0, 0x400,
                                     0x400);

    // Red Triangle
    gDPPipeSync(gfx++);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gfx++, 200, 0, 0, 255);
    gDPLoadTextureBlock(gfx++, &D_08000700, G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    BombersNotebook_TextureRectangle(&gfx, (lineXStart + -11) * 4, 70 * 4, (lineXStart + 13) * 4, 86 * 4, 0, 0, 0,
                                     0x400, 0x400);

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

void BombersNotebook_DrawCursor(BombersNotebook* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 cursorRow;
    s32 cursorEntry;
    s32 entryXEnd;
    s32 entryXStart;
    s32 entryIcon;
    u32 cursorXStart;
    u32 cursorYStart;
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
        cursorYStart = (this->cursorPageRow * 52) + 107;
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
        entryXStart = sBombersNotebookDayStartX[(sBombersNotebookEntries[cursorRow][cursorEntry] & 0xF00) >> 8] +
                      (startTime / 455);
        entryXEnd =
            sBombersNotebookDayStartX[(sBombersNotebookEntries[cursorRow][cursorEntry] & 0xF00) >> 8] + (endTime / 455);
        if ((entryXEnd - entryXStart) < 8) {
            entryXStart = ((entryXStart + entryXEnd) - entryXStart) - 8;
            entryXEnd = entryXStart + 8;
        }
        entryIcon = sBombersNotebookEventIcons[(sBombersNotebookEntries[cursorRow][cursorEntry] & 0xFF) - 20];
        if ((entryXEnd - entryXStart) < sBombersNotebookEventIconOffsetsX[entryIcon]) {
            cursorXStart =
                (((entryXStart - sBombersNotebookEventIconOffsetsX[entryIcon]) + entryXEnd) - entryXStart) + 3;
        } else {
            cursorXStart =
                (((entryXEnd - entryXStart) - sBombersNotebookEventIconOffsetsX[entryIcon]) / 2) + entryXStart;
        }
        if (entryIcon == BOMBERSNOTEBOOK_EVENT_ICON_EXCLAMATION_POINT) {
            cursorXStart -= 8;
            cursorYStart -= 8;
        } else {
            cursorXStart -= 9;
            cursorYStart -= 8;
        }
        if ((entryIcon == BOMBERSNOTEBOOK_EVENT_ICON_MASK) || (entryIcon == BOMBERSNOTEBOOK_EVENT_ICON_RIBBON)) {
            if (sBombersNotebookEntries[cursorRow][cursorEntry] & BOMBERSNOTEBOOK_ENTRY_POS_ABOVE) {
                yOffset -= 12;
            } else if (!(sBombersNotebookEntries[cursorRow][cursorEntry] & BOMBERSNOTEBOOK_ENTRY_POS_BELOW)) {
                // BOMBERSNOTEBOOK_ENTRY_POS_CENTER
                yOffset -= 6;
            }
        }
        BombersNotebook_TextureRectangle(&gfx, cursorXStart * 4, (cursorYStart + yOffset) * 4, (cursorXStart + 16) * 4,
                                         (cursorYStart + yOffset + 16) * 4, 0, 0, 0, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, (cursorXStart + sBombersNotebookEventIconOffsetsX[entryIcon]) * 4,
                                         (cursorYStart + yOffset) * 4,
                                         (cursorXStart + sBombersNotebookEventIconOffsetsX[entryIcon] + 16) * 4,
                                         (cursorYStart + yOffset + 16) * 4, 0, 0x200, 0, 0x400, 0x400);
        BombersNotebook_TextureRectangle(
            &gfx, cursorXStart * 4, (cursorYStart + yOffset + sBombersNotebookEventIconOffsetsY[entryIcon]) * 4,
            (cursorXStart + 16) * 4, (cursorYStart + yOffset + sBombersNotebookEventIconOffsetsY[entryIcon] + 16) * 4,
            0, 0, 0x200, 0x400, 0x400);
        BombersNotebook_TextureRectangle(&gfx, (cursorXStart + sBombersNotebookEventIconOffsetsX[entryIcon]) * 4,
                                         (cursorYStart + yOffset + sBombersNotebookEventIconOffsetsY[entryIcon]) * 4,
                                         (cursorXStart + sBombersNotebookEventIconOffsetsX[entryIcon] + 16) * 4,
                                         (cursorYStart + yOffset + sBombersNotebookEventIconOffsetsY[entryIcon] + 16) *
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
    u32 yStart;
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
        yStart = (-sUpperArrowOffsetY + 83) * 4;
        BombersNotebook_TextureRectangle(&gfx, 46 * 4, yStart, 70 * 4, yStart + (16 * 4), 0, 0, 0x200, 0x400, 0x400);
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
    0x21DD, 0x21CA, 0x21CB, 0x21CC, 0x21CD, 0x21CE, 0x21CF, 0x21D0, 0x21D1, 0x21D2, 0x21D3, 0x21D4,
    0x21D5, 0x21D6, 0x21D7, 0x21D8, 0x21D9, 0x21DA, 0x21DB, 0x21DC, //

    0x2198, 0x2199, 0x219A, 0x219B, 0x219C, 0x219D, 0x219E, 0x219F, 0x21A0, 0x21A1, 0x21A2, 0x21A3,
    0x21A4, 0x21A5, 0x21A6, 0x21A7, 0x21A8, 0x21A9, 0x21AA, 0x21AB, 0x21AC, 0x21AD, 0x21AE, 0x21AF,
    0x21B0, 0x21B1, 0x21B2, 0x21B3, 0x21B4, 0x21B5, 0x21B6, 0x21B7, 0x21B8, 0x21B9, 0x21BA,
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
