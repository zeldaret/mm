/*
 * File: z_kaleido_scope_NES.c
 * Overlay: ovl_kaleido_scope
 * Description:
 */

#include "z_kaleido_scope.h"
#include "interface/icon_item_gameover_static/icon_item_gameover_static.h"

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

// bss
extern f32 D_8082DA60[4];
extern f32 D_8082DA70[4];

void* D_8082B700[] = {
    0x08064440, 0x0806E440, 0x08077A40, 0x08081040, 0x0808A640, 0x0D003A00, 0x0806EE40, 0x08078440,
    0x08081A40, 0x0808B040, 0x08065840, 0x0806F840, 0x08078E40, 0x08082440, 0x0808BA40,
};
void* D_8082B73C[] = {
    0x0D004400, 0x08070240, 0x08079840, 0x08082E40, 0x0808C440, 0x0D004E00, 0x08070C40, 0x0807A240,
    0x08083840, 0x0808CE40, 0x0D005800, 0x08071640, 0x0807AC40, 0x08084240, 0x0808D840,
};
void* D_8082B778[] = {
    0x08068040, 0x08072040, 0x0807B640, 0x08084C40, 0x0808E240, 0x0D006200, 0x08072A40, 0x0807C040,
    0x08085640, 0x0808EC40, 0x08069440, 0x08073440, 0x0807CA40, 0x08086040, 0x0808F640,
};
void* D_8082B7B4[] = {
    0x0D006C00, 0x08073E40, 0x0807D440, 0x08086A40, 0x08090040, 0x0D007600, 0x08074840, 0x0807DE40,
    0x08087440, 0x08090A40, 0x0D008000, 0x08075240, 0x0807E840, 0x08087E40, 0x08091440,
};

s16 D_8082B7F0[] = {
    80, 64, 64, 64, 16, 64, 112, 112, 48, 64, 64, 64, 64, 48, 64, 8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,   8,   24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
};
s16 D_8082B838[] = {
    40, 31, 53, 53, 53, 52, 35, 35, 32, 64, 64, 64, 64, 82, 61, 8,  8,  8,
    8,  8,  8,  8,  8,  8,  8,  8,  12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};

s16 D_8082B880 = 0;
s16 D_8082B884 = 0;
s16 D_8082B888 = 0;
s16 D_8082B88C = 255;
s16 D_8082B890 = 0;
s16 D_8082B894 = 0;
s16 D_8082B898 = 0;
s16 D_8082B89C = 0;
s16 D_8082B8A0 = 0;
s16 D_8082B8A4 = 0;
s16 D_8082B8A8 = 255;
s16 D_8082B8AC = 0;
s16 D_8082B8B0 = 0;

s16 sInDungeonScene = false;

f32 D_8082B8B8[] = {
    -4.0f, 4.0f, 4.0f, 4.0f, 4.0f, -4.0f, -4.0f, -4.0f,
};

f32 D_8082B8D8[] = {
    -4.0f, -4.0f, -4.0f, 4.0f, 4.0f, 4.0f, 4.0f, -4.0f,
};

s16 D_8082B8F8[] = {
    PAUSE_MAP, PAUSE_MASK, PAUSE_QUEST, PAUSE_ITEM, PAUSE_MASK, PAUSE_MAP, PAUSE_ITEM, PAUSE_QUEST,
};

f32 D_8082B908 = 0.0f;
f32 D_8082B90C = 0.0f;
f32 D_8082B910 = 40.0f;
f32 D_8082B914 = -40.0f;

s16 D_8082B918 = 0;
s16 D_8082B91C = 0;
s16 D_8082B920 = 10;

u8 D_8082B924[] = {
    0x00, 0x14, 0x00, 0x04, 0x00, 0x14, 0x00, 0x0A, 0x0F, 0x1F, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
    0x07, 0x07, 0x03, 0x0F, 0x07, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0x1F, 0x0F, 0x03, 0x0F, 0x00, 0x00,
};

s16 D_8082B944 = 66;

s16 D_8082B948[][3] = {
    { 255, 255, 255 }, { 255, 255, 255 }, { 255, 255, 0 }, { 255, 255, 0 }, { 100, 150, 255 }, { 100, 255, 255 },
};

s16 D_8082B96C[][3] = {
    { 0, 0, 0 }, { 170, 170, 170 }, { 0, 0, 0 }, { 255, 160, 0 }, { 0, 0, 100 }, { 0, 150, 255 },
};

s16 D_8082B990 = 10;
s16 D_8082B994 = 0;

s32 D_8082B998[] = {
    0x0D003300,
    0x0D002700,
    0x0D002B00,
    0x0D002F00,
};

s32 D_8082B9A8[] = {
    0x0D002B00,
    0x0D002F00,
    0x0D003300,
    0x0D002700,
};

s16 D_8082B9B8[] = {
    180, 210, 255, 220, 100, 100, 150, 220,
};

s16 D_8082B9C8 = 20;
s16 D_8082B9CC = 0;

s16 D_8082B9D0[] = {
    180, 210, 255, 220, 100, 100, 150, 220,
};

s16 D_8082B9E0 = 20;
s16 D_8082B9E4 = 0;

s16 D_8082B9E8[] = { 0, 0 };
s16 D_8082B9EC[] = { 0, 0 };
s16 D_8082B9F0[] = { -21, -104, -76, -48, -104, -40 };
s16 D_8082B9FC[] = { 0, 0 };
s16 D_8082BA00[] = {
    -41, 9, 43, -21, -37, 43, -69, -69, -32, -109, -45, -109, -45, 59,  -5, -70, -52, -11,
    -2,  8, 2,  1,   43,  52, 54,  62,  -80, -64,  -9,  -3,   -7,  -16, -1, 23,  44,  54,
};
s16 D_8082BA48[] = {
    -76, -58, 10, -58, 10, 0,
};
s16 D_8082BA54[] = { 0, 0 };
s16 D_8082BA58[] = { 0, 0 };
s16 D_8082BA5C[] = {
    128, 24, 24, 24, 32, 24,
};
s16 D_8082BA68[] = { 0, 0 };
s16 D_8082BA6C[] = {
    152, 48, 48, 48, 48, 0,
};
s16 D_8082BA78[] = { 0, 0 };
s16 D_8082BA7C[] = { 0, 0 };

s16 D_8082BA80[] = {
    54, -42, -42, -42, -24, 50,
};
s16 D_8082BA8C[] = { 0, 0 };
s16 D_8082BA90[] = {
    11,  22,  -16, -16, -16, 59, 24, 59, -11, -5,  -5, 59, 59, 39, 31,  -10, -36, -19,
    -53, -27, -2,  41,  11,  -3, 45, 18, -8,  -38, 39, 26, 1,  -7, -28, -27, -1,  24,
};
s16 D_8082BAD8[] = {
    36, 10, 10, -6, -6, 0,
};
s16 D_8082BAE4[] = { 0, 0 };
s16 D_8082BAE8[] = { 0, 0 };
s16 D_8082BAEC[] = {
    16, 24, 24, 24, 24, 24,
};
s16 D_8082BAF8[] = { 0, 0 };
s16 D_8082BAFC[] = {
    16, 48, 48, 16, 16, 0,
};

s16* D_8082BB08[] = {
    D_8082B9E8, D_8082B9EC, D_8082B9F0, D_8082B9FC, D_8082BA00, D_8082BA48,
};

s16* D_8082BB20[] = {
    D_8082BA54, D_8082BA58, D_8082BA5C, D_8082BA68, D_8082B7F0, D_8082BA6C,
};

s16* D_8082BB38[] = {
    D_8082BA78, D_8082BA7C, D_8082BA80, D_8082BA8C, D_8082BA90, D_8082BAD8,
};

s16* D_8082BB50[] = {
    D_8082BAE4, D_8082BAE8, D_8082BAEC, D_8082BAF8, D_8082B838, D_8082BAFC,
};

s16 D_8082BB68[] = {
    14, -2, -2, -18, -18, 0,
};

s16 D_8082BB74[] = {
    45, 78,   10,  45,  80,  11,  -109, -87, -65, -41, -19, -18, -109, -87, -65, -41, -19, -18, -103, 7,
    82, -110, -54, -98, -86, -74, -62,  -50, -38, -26, -14, -98, -86,  -74, -62, -50, -38, -26, -14,  0,
};

s16 D_8082BBC4[] = {
    62,  42, 42, 20,  -9,  -9,  -20, -20, -20, -20, -20, -20, 2,   2,   2,   2,   2,   2,   54,  -44,
    -44, 34, 58, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, 0,
};

s16 D_8082BC14[] = {
    32, 32, 32, 32, 32, 32, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32,
    32, 24, 48, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0,
};

s16 D_8082BC64[] = {
    32, 32, 32, 32, 32, 32, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 32, 32,
    32, 24, 48, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0,
};

f32 D_8082BCB4[] = {
    -62.0f, -36.0f, -10.0f, 16.0f, 42.0f, 68.0f,
};
f32 D_8082BCCC[] = { 31.0f, 5.0f, -21.0f, -47.0f };
f32 D_8082BCDC[] = {
    -49.0f, -35.0f, -3.0f, 4.0f, 12.0f, 8.0f, 7.0f, 40.0f, 47.0f, 49.0f, 55.0f,
};
f32 D_8082BD08[] = {
    -15.0f, -36.0f, -23.0f, -49.0f, -29.0f, -8.0f, 25.0f, 2.0f, -9.0f, 28.0f, 7.0f,
};
f32 D_8082BD34[] = {
    -50.0f, -38.0f, 6.0f, 11.0f, 8.0f, 0.0f, 12.0f, 31.0f, 48.0f, 56.0f,
};
f32 D_8082BD5C[] = {
    -14.0f, -39.0f, 23.0f, 11.0f, -8.0f, -15.0f, -31.0f, -30.0f, -10.0f, 11.0f,
};
f32 D_8082BD84[] = {
    -72.0f, -47.0f, -26.0f, -50.0f, -48.0f, -48.0f, -48.0f, -48.0f, -48.0f,
};
f32 D_8082BDA8[] = {
    -47.0f, -47.0f, -47.0f, -30.0f, 33.0f, 22.0f, 11.0f, -2.0f, -13.0f,
};
f32 D_8082BDCC[] = {
    52.0f,  80.0f,  24.0f,  52.0f,  81.0f, 24.0f, -78.0f, -61.0f, -44.0f, -24.0f, -6.0f,  -3.0f,
    -78.0f, -61.0f, -44.0f, -24.0f, -6.0f, -3.0f, -68.0f, 22.0f,  83.0f,  -67.0f, -21.0f,
};
f32 D_8082BE28[] = {
    33.0f,  18.0f,  18.0f,  0.0f,   -23.0f, -23.0f, -29.0f, -29.0f, -29.0f, -29.0f, -29.0f, -29.0f,
    -11.0f, -11.0f, -11.0f, -11.0f, -11.0f, -11.0f, 27.0f,  -53.0f, -53.0f, 14.0f,  26.0f,
};

s16 D_8082BE84 = 0;
s16 D_8082BE88[] = {
    28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
};
s16 D_8082BE9C = 0;
s16 D_8082BEA0 = 0;
s16 D_8082BEA4 = 10;
s16 D_8082BEA8 = 0;
s16 D_8082BEAC = 0;
s16 D_8082BEB0 = 0;
s16 D_8082BEB4 = 0;
s16 D_8082BEB8 = 0;

void func_80821900(s32 arg0, s32 arg1) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), arg1, arg0, 0x400);
}

void func_8082192C(s32 arg0, s32 arg1) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), arg1, arg0, 0xA00);
}

void func_80821958(s32 arg0, s32 arg1) {
    func_80178E3C(SEGMENT_ROM_START(item_name_static), arg1, arg0, 0x400);
}

void func_80821984(PlayState* play, s16 cursorSpecialPos) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->cursorSlot[pauseCtx->pageIndex] = 0;
    pauseCtx->cursorSpecialPos = cursorSpecialPos;
    pauseCtx->pageSwitchTimer = 0;

    play_sound(NA_SE_SY_DECIDE);

    gSaveContext.buttonStatus[0] = BTN_ENABLED;
    gSaveContext.buttonStatus[1] = BTN_DISABLED;
    gSaveContext.buttonStatus[2] = BTN_DISABLED;
    gSaveContext.buttonStatus[3] = BTN_DISABLED;
    gSaveContext.buttonStatus[4] = BTN_DISABLED;

    gSaveContext.unk_3F22 = 0;
    Interface_ChangeAlpha(50);
}

extern u8 D_801C6A98[5][5];

void func_80821A04(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->unk_280 = 0;
    pauseCtx->cursorSpecialPos = 0;

    play_sound(NA_SE_SY_CURSOR);

    pauseCtx->unk_298 = 4.0f;

    // TODO: indexing of D_801C6A98 is likely wrong
    gSaveContext.buttonStatus[0] = BTN_ENABLED;
    gSaveContext.buttonStatus[1] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[2] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[3] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[4] = BTN_ENABLED;

    gSaveContext.unk_3F22 = 0;

    Interface_ChangeAlpha(50);
}

void KaleidoScope_DrawQuadTextureRGBA32(GraphicsContext* gfxCtx, void* texture, u16 width, u16 height, u16 point) {
    OPEN_DISPS(gfxCtx);

    gDPLoadTextureBlock(POLY_OPA_DISP++, texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, height, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, point, point + 2, point + 3, point + 1, 0);

    CLOSE_DISPS(gfxCtx);
}

void KaleidoScope_SwitchPage(PauseContext* pauseCtx, u8 pt) {
    pauseCtx->cursorSlot[pauseCtx->pageIndex] = 0;
    pauseCtx->unk_200 = 1;
    pauseCtx->unk_206 = 0;

    if (!pt) {
        pauseCtx->mode = pauseCtx->pageIndex * 2 + 1;
        play_sound(NA_SE_SY_WIN_SCROLL_LEFT);
        pauseCtx->cursorSpecialPos = PAUSE_CURSOR_PAGE_RIGHT;
    } else {
        pauseCtx->mode = pauseCtx->pageIndex * 2;
        play_sound(NA_SE_SY_WIN_SCROLL_RIGHT);
        pauseCtx->cursorSpecialPos = PAUSE_CURSOR_PAGE_LEFT;
    }

    gSaveContext.buttonStatus[0] = BTN_ENABLED;
    gSaveContext.buttonStatus[1] = BTN_DISABLED;
    gSaveContext.buttonStatus[2] = BTN_DISABLED;
    gSaveContext.buttonStatus[3] = BTN_DISABLED;
    gSaveContext.buttonStatus[4] = BTN_DISABLED;

    gSaveContext.unk_3F22 = 0;
    Interface_ChangeAlpha(50);
}

void KaleidoScope_HandlePageToggles(PlayState* play, Input* input) {
    PauseContext* pauseCtx = &play->pauseCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    if (1) {}

    if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && (pauseCtx->unk_2B9 == 0)) {
        if (CHECK_BTN_ALL(input->cur.button, BTN_DRIGHT) || CHECK_BTN_ALL(input->press.button, BTN_R)) {
            if (interfaceCtx->unk_212 == 6) {
                func_8011552C(play, 0x15);
            }
            KaleidoScope_SwitchPage(pauseCtx, 2);
            return;
        }

        if (CHECK_BTN_ALL(input->cur.button, BTN_DLEFT) || CHECK_BTN_ALL(input->press.button, BTN_Z)) {
            if (interfaceCtx->unk_212 == 6) {
                func_8011552C(play, 0x15);
            }
            KaleidoScope_SwitchPage(pauseCtx, 0);
            return;
        }

        if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            if (pauseCtx->stickRelX < -30) {
                pauseCtx->pageSwitchTimer++;
                if ((pauseCtx->pageSwitchTimer >= 10) || (pauseCtx->pageSwitchTimer == 0)) {
                    KaleidoScope_SwitchPage(pauseCtx, 0);
                }
            } else {
                pauseCtx->pageSwitchTimer = -1;
            }
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) {
            if (pauseCtx->stickRelX > 30) {
                pauseCtx->pageSwitchTimer++;
                if ((pauseCtx->pageSwitchTimer >= 10) || (pauseCtx->pageSwitchTimer == 0)) {
                    KaleidoScope_SwitchPage(pauseCtx, 2);
                }
            } else {
                pauseCtx->pageSwitchTimer = -1;
            }
        }
    }
}

Gfx* KaleidoScope_DrawPageSections(Gfx* gfx, Vtx* vertices, void** textures) {
    s32 i;
    s32 j;

    gSPVertex(gfx++, vertices, 32, 0);

    i = 0;
    j = 0;
    while (j < 32) {
        gDPPipeSync(gfx++);
        gDPLoadTextureBlock(gfx++, textures[i], G_IM_FMT_IA, G_IM_SIZ_8b, 80, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(gfx++, j, j + 2, j + 3, j + 1, 0);

        j += 4;
        i++;
    }

    gSPVertex(gfx++, vertices + 32, 28, 0);

    j = 0;
    while (j < 28) {
        gDPPipeSync(gfx++);
        gDPLoadTextureBlock(gfx++, textures[i], G_IM_FMT_IA, G_IM_SIZ_8b, 80, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(gfx++, j, j + 2, j + 3, j + 1, 0);

        j += 4;
        i++;
    }

    return gfx;
}

void func_801091F0(PlayState*);
void func_808160A0(PlayState*);
void func_8081B6EC(PlayState*);
void func_8081D6DC(PlayState*);
void KaleidoScope_DrawWorldMap(PlayState*);
void func_8081FF80(PlayState*);

#ifdef NON_EQUIVALENT
void KaleidoScope_DrawPages(PlayState* play, GraphicsContext* gfxCtx) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stepR;
    s16 stepG;
    s32 stepB;

    OPEN_DISPS(gfxCtx);

    if ((pauseCtx->state < 8) || (pauseCtx->state >= 0x13)) {
        if (pauseCtx->state != 7) {

            stepR = ABS_ALT(D_8082B890 - D_8082B948[pauseCtx->cursorColorSet + D_8082B994][0]) / D_8082B990;
            stepG = ABS_ALT(D_8082B894 - D_8082B948[pauseCtx->cursorColorSet + D_8082B994][1]) / D_8082B990;
            stepB = ABS_ALT(D_8082B898 - D_8082B948[pauseCtx->cursorColorSet + D_8082B994][2]);

            if (D_8082B890 >= D_8082B948[pauseCtx->cursorColorSet + D_8082B994][0]) {
                D_8082B890 -= stepR;
            } else {
                D_8082B890 += stepR;
            }

            if (D_8082B894 >= D_8082B948[pauseCtx->cursorColorSet + D_8082B994][1]) {
                D_8082B894 -= stepG;
            } else {
                D_8082B894 += stepG;
            }

            if (D_8082B898 >= D_8082B948[pauseCtx->cursorColorSet + D_8082B994][2]) {
                D_8082B898 -= (s16)(stepB / D_8082B990);
            } else {
                D_8082B898 += (s16)(stepB / D_8082B990);
            }

            stepR = ABS_ALT(D_8082B89C - D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][0]) / D_8082B990;
            stepG = ABS_ALT(D_8082B8A0 - D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][1]) / D_8082B990;
            stepB = ABS_ALT(D_8082B8A4 - D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][2]);

            if (D_8082B89C >= D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][0]) {
                D_8082B89C -= stepR;
            } else {
                D_8082B89C += stepR;
            }

            if (D_8082B8A0 >= D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][1]) {
                D_8082B8A0 -= stepG;
            } else {
                D_8082B8A0 += stepG;
            }

            if (D_8082B8A4 >= D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][2]) {
                D_8082B8A4 -= (s16)(stepB / D_8082B990);
            } else {
                D_8082B8A4 += (s16)(stepB / D_8082B990);
            }

            D_8082B990--;

            if (D_8082B990 == 0) {
                D_8082B890 = D_8082B948[pauseCtx->cursorColorSet + D_8082B994][0];
                D_8082B894 = D_8082B948[pauseCtx->cursorColorSet + D_8082B994][1];
                D_8082B898 = D_8082B948[pauseCtx->cursorColorSet + D_8082B994][2];
                D_8082B89C = D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][0];
                D_8082B8A0 = D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][1];
                D_8082B8A4 = D_8082B96C[pauseCtx->cursorColorSet + D_8082B994][2];
                D_8082B994 ^= 1;
                D_8082B990 = 10;
            }
        }

        if ((pauseCtx->pageIndex != PAUSE_ITEM) && (pauseCtx->pageIndex != PAUSE_QUEST)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(0.0f, MTXMODE_NEW);
            Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->unk_210 / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, &D_8082B73C[0]);

            func_8081B6EC(play);
        }

        if ((pauseCtx->pageIndex != PAUSE_MAP) && (pauseCtx->pageIndex != PAUSE_MASK)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(-1.57f, MTXMODE_NEW);
            Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->unk_214 / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, &D_8082B778[0]);

            if (sInDungeonScene) {
                func_8081D6DC(play);
                func_8012C8AC(gfxCtx);
                gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                func_801091F0(play);
            } else {
                KaleidoScope_DrawWorldMap(play);
            }
        }

        if ((pauseCtx->pageIndex != PAUSE_QUEST) && (pauseCtx->pageIndex != PAUSE_ITEM)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(-3.14f, MTXMODE_NEW);
            Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->unk_218 / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, &D_8082B7B4[0]);

            func_808160A0(play);
        }

        if ((pauseCtx->pageIndex != PAUSE_MASK) && (pauseCtx->pageIndex != PAUSE_MAP)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(1.57f, MTXMODE_NEW);
            Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->unk_21C / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, &D_8082B700[0]);

            func_8081FF80(play);
        }

        switch (pauseCtx->pageIndex) {
            case PAUSE_ITEM:
                if (pauseCtx->unk_200 < 0x10) {
                    gDPPipeSync(POLY_OPA_DISP++);

                    gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0,
                                      PRIMITIVE, 0, TEXEL0, 0, SHADE, 0);

                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                    Matrix_RotateYF(0.0f, MTXMODE_NEW);
                    Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
                    Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                    Matrix_RotateXFApply(-pauseCtx->unk_210 / 100.0f);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, &D_8082B73C[0]);

                    func_8081B6EC(play);
                }
                break;

            case PAUSE_MAP:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                Matrix_RotateYF(-1.57f, MTXMODE_NEW);
                Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->unk_214 / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, &D_8082B778[0]);

                if (sInDungeonScene) {
                    func_8081D6DC(play);
                    func_8012C8AC(gfxCtx);

                    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

                    func_801091F0(play);
                } else {
                    Matrix_RotateYF(gGameInfo->data[0x258] / 1000.0f, MTXMODE_NEW);

                    if ((pauseCtx->state == 4) || (pauseCtx->state == 0x16) || (pauseCtx->state >= 0x19) ||
                        ((pauseCtx->state == 7) && ((pauseCtx->unk_208 == 3) || (pauseCtx->unk_208 == 7)))) {
                        Matrix_Translate(0.0f, (gGameInfo->data[0x259] - 0x1F40) / 100.0f,
                                         gGameInfo->data[0x25A] / 100.0f, MTXMODE_APPLY);
                    } else {
                        Matrix_Translate(0.0f, gGameInfo->data[0x259] / 100.0f, gGameInfo->data[0x25A] / 100.0f,
                                         MTXMODE_APPLY);
                    }

                    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                    Matrix_RotateXFApply(-pauseCtx->unk_214 / 100.0f);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    KaleidoScope_DrawWorldMap(play);
                }
                break;

            case PAUSE_QUEST:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

                Matrix_RotateYF(-3.14f, MTXMODE_NEW);
                Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->unk_218 / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, &D_8082B7B4[0]);

                func_808160A0(play);
                break;

            case PAUSE_MASK:
                gDPPipeSync(POLY_OPA_DISP++);

                gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE,
                                  0, TEXEL0, 0, SHADE, 0);

                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

                Matrix_RotateYF(1.57f, MTXMODE_NEW);
                Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
                Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->unk_21C / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, &D_8082B700[0]);

                func_8081FF80(play);
                break;
        }
    }

    CLOSE_DISPS(gfxCtx);
}
#else
void KaleidoScope_DrawPages(PlayState* play, GraphicsContext* gfxCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawPages.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80823350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80824738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808248D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80824B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808256E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8082585C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808259D4.s")

// OoT func_80823A0C
s16 func_80825A50(PlayState* play, Vtx* vtx, s16 arg2, s16 arg3) {
    PauseContext* pauseCtx = &play->pauseCtx;
    GameOverContext* gameOverCtx = &play->gameOverCtx;
    s16* ptr1;
    s16* ptr2;
    s16* ptr3;
    s16* ptr4;
    s16 var_a2;
    s16 var_t3;
    s16 i;
    s16 j;
    s16 k;

    var_t3 = -200;

    for (k = 0, i = 0; i < 3; i++) {
        var_t3 += 80;

        for (var_a2 = 80, j = 0; j < 5; j++, k += 4, var_a2 -= 32) {
            vtx[k + 0].v.ob[0] = vtx[k + 2].v.ob[0] = var_t3;
            vtx[k + 1].v.ob[0] = vtx[k + 3].v.ob[0] = vtx[k + 0].v.ob[0] + 80;

            vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = var_a2 + pauseCtx->offsetY;
            vtx[k + 2].v.ob[1] = vtx[k + 3].v.ob[1] = vtx[k + 0].v.ob[1] - 32;

            vtx[k + 0].v.ob[2] = vtx[k + 1].v.ob[2] = vtx[k + 2].v.ob[2] = vtx[k + 3].v.ob[2] = 0;

            vtx[k + 0].v.flag = vtx[k + 1].v.flag = vtx[k + 2].v.flag = vtx[k + 3].v.flag = 0;

            vtx[k + 0].v.tc[0] = vtx[k + 0].v.tc[1] = 0;
            vtx[k + 1].v.tc[1] = vtx[k + 2].v.tc[0] = 0;
            vtx[k + 1].v.tc[0] = vtx[k + 3].v.tc[0] = 0xA00;
            vtx[k + 2].v.tc[1] = vtx[k + 3].v.tc[1] = 0x400;

            vtx[k + 0].v.cn[0] = vtx[k + 2].v.cn[0] = vtx[k + 0].v.cn[1] = vtx[k + 2].v.cn[1] = vtx[k + 0].v.cn[2] =
                vtx[k + 2].v.cn[2] = 0;

            vtx[k + 1].v.cn[0] = vtx[k + 3].v.cn[0] = vtx[k + 1].v.cn[1] = vtx[k + 3].v.cn[1] = vtx[k + 1].v.cn[2] =
                vtx[k + 3].v.cn[2] = 0;

            vtx[k + 0].v.cn[3] = vtx[k + 2].v.cn[3] = vtx[k + 1].v.cn[3] = vtx[k + 3].v.cn[3] = pauseCtx->alpha;
        }
    }

    if (arg3 != 0) {
        ptr1 = D_8082BB08[arg2];
        ptr2 = D_8082BB20[arg2];
        ptr3 = D_8082BB38[arg2];
        ptr4 = D_8082BB50[arg2];

        for (i = 0; i < arg3; i++, k += 4) {
            vtx[k + 2].v.ob[0] = vtx[k + 0].v.ob[0] = ptr1[i];

            vtx[k + 1].v.ob[0] = vtx[k + 3].v.ob[0] = vtx[k + 0].v.ob[0] + ptr2[i];

            if ((pauseCtx->state < 8) || (pauseCtx->state >= 0x13)) {
                vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = ptr3[i] + pauseCtx->offsetY;
            } else if (gameOverCtx->state == GAMEOVER_INACTIVE) {
                vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = ptr3[i] + pauseCtx->offsetY;
            } else {
                vtx[k + 0].v.ob[1] = vtx[k + 1].v.ob[1] = D_8082BB68[i] + pauseCtx->offsetY;
            }

            vtx[k + 2].v.ob[1] = vtx[k + 3].v.ob[1] = vtx[k + 0].v.ob[1] - ptr4[i];

            vtx[k + 0].v.ob[2] = vtx[k + 1].v.ob[2] = vtx[k + 2].v.ob[2] = vtx[k + 3].v.ob[2] = 0;

            vtx[k + 0].v.flag = vtx[k + 1].v.flag = vtx[k + 2].v.flag = vtx[k + 3].v.flag = 0;

            vtx[k + 0].v.tc[0] = vtx[k + 0].v.tc[1] = vtx[k + 1].v.tc[1] = vtx[k + 2].v.tc[0] = 0;
            vtx[k + 1].v.tc[0] = vtx[k + 3].v.tc[0] = ptr2[i] << 5;
            vtx[k + 2].v.tc[1] = vtx[k + 3].v.tc[1] = ptr4[i] << 5;

            vtx[k + 0].v.cn[0] = vtx[k + 2].v.cn[0] = vtx[k + 0].v.cn[1] = vtx[k + 2].v.cn[1] = vtx[k + 0].v.cn[2] =
                vtx[k + 2].v.cn[2] = 255;

            vtx[k + 1].v.cn[0] = vtx[k + 3].v.cn[0] = vtx[k + 1].v.cn[1] = vtx[k + 3].v.cn[1] = vtx[k + 1].v.cn[2] =
                vtx[k + 3].v.cn[2] = 255;

            vtx[k + 0].v.cn[3] = vtx[k + 2].v.cn[3] = vtx[k + 1].v.cn[3] = vtx[k + 3].v.cn[3] = pauseCtx->alpha;
        }
    }
    return k;
}

void KaleidoScope_InitVertices(PlayState* play, GraphicsContext* gfxCtx) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 i;
    s16 j;
    s16 k;
    s16 var_a3;
    s16 var_t3;

    pauseCtx->offsetY = 0;

    if ((pauseCtx->state == 4) || (pauseCtx->state == 0x16) || (pauseCtx->state >= 0x19) ||
        ((pauseCtx->state == 7) && ((pauseCtx->unk_208 == 3) || (pauseCtx->unk_208 == 7)))) {
        pauseCtx->offsetY = 80;
    }

    if (pauseCtx->pageIndex != PAUSE_QUEST) {
        pauseCtx->itemPageVtx = GRAPH_ALLOC(gfxCtx, 0x3C0);
        func_80825A50(play, pauseCtx->itemPageVtx, 1, 0);

        pauseCtx->itemVtx = GRAPH_ALLOC(gfxCtx, 0x6C0);

        for (k = 0, i = 0, var_t3 = 58; k < 4; k++, var_t3 -= 32) {
            for (var_a3 = -96, j = 0; j < 6; j++, i += 4, var_a3 += 32) {
                pauseCtx->itemVtx[i + 0].v.ob[0] = pauseCtx->itemVtx[i + 2].v.ob[0] = var_a3 + 2;
                pauseCtx->itemVtx[i + 1].v.ob[0] = pauseCtx->itemVtx[i + 3].v.ob[0] =
                    pauseCtx->itemVtx[i + 0].v.ob[0] + 28;

                pauseCtx->itemVtx[i + 0].v.ob[1] = pauseCtx->itemVtx[i + 1].v.ob[1] = var_t3 + pauseCtx->offsetY - 2;
                pauseCtx->itemVtx[i + 2].v.ob[1] = pauseCtx->itemVtx[i + 3].v.ob[1] =
                    pauseCtx->itemVtx[i + 0].v.ob[1] - 28;

                pauseCtx->itemVtx[i + 0].v.ob[2] = pauseCtx->itemVtx[i + 1].v.ob[2] = pauseCtx->itemVtx[i + 2].v.ob[2] =
                    pauseCtx->itemVtx[i + 3].v.ob[2] = 0;

                pauseCtx->itemVtx[i + 0].v.flag = pauseCtx->itemVtx[i + 1].v.flag = pauseCtx->itemVtx[i + 2].v.flag =
                    pauseCtx->itemVtx[i + 3].v.flag = 0;

                pauseCtx->itemVtx[i + 0].v.tc[0] = pauseCtx->itemVtx[i + 0].v.tc[1] = pauseCtx->itemVtx[i + 1].v.tc[1] =
                    pauseCtx->itemVtx[i + 2].v.tc[0] = 0;

                pauseCtx->itemVtx[i + 1].v.tc[0] = pauseCtx->itemVtx[i + 2].v.tc[1] = pauseCtx->itemVtx[i + 3].v.tc[0] =
                    pauseCtx->itemVtx[i + 3].v.tc[1] = 0x400;

                pauseCtx->itemVtx[i + 0].v.cn[0] = pauseCtx->itemVtx[i + 1].v.cn[0] = pauseCtx->itemVtx[i + 2].v.cn[0] =
                    pauseCtx->itemVtx[i + 3].v.cn[0] = pauseCtx->itemVtx[i + 0].v.cn[1] =
                        pauseCtx->itemVtx[i + 1].v.cn[1] = pauseCtx->itemVtx[i + 2].v.cn[1] =
                            pauseCtx->itemVtx[i + 3].v.cn[1] = pauseCtx->itemVtx[i + 0].v.cn[2] =
                                pauseCtx->itemVtx[i + 1].v.cn[2] = pauseCtx->itemVtx[i + 2].v.cn[2] =
                                    pauseCtx->itemVtx[i + 3].v.cn[2] = 255;

                pauseCtx->itemVtx[i + 0].v.cn[3] = pauseCtx->itemVtx[i + 1].v.cn[3] = pauseCtx->itemVtx[i + 2].v.cn[3] =
                    pauseCtx->itemVtx[i + 3].v.cn[3] = 255;
            }
        }

        for (j = 1; j < 4; j++, i += 4) {
            if (GET_CUR_FORM_BTN_SLOT(j) != ITEM_NONE) {
                k = GET_CUR_FORM_BTN_SLOT(j) << 2;

                pauseCtx->itemVtx[i + 0].v.ob[0] = pauseCtx->itemVtx[i + 2].v.ob[0] = pauseCtx->itemVtx[k].v.ob[0] - 2;

                pauseCtx->itemVtx[i + 1].v.ob[0] = pauseCtx->itemVtx[i + 3].v.ob[0] =
                    pauseCtx->itemVtx[i + 0].v.ob[0] + 32;

                pauseCtx->itemVtx[i + 0].v.ob[1] = pauseCtx->itemVtx[i + 1].v.ob[1] = pauseCtx->itemVtx[k].v.ob[1] + 2;

                pauseCtx->itemVtx[i + 2].v.ob[1] = pauseCtx->itemVtx[i + 3].v.ob[1] =
                    pauseCtx->itemVtx[i + 0].v.ob[1] - 32;

                pauseCtx->itemVtx[i + 0].v.ob[2] = pauseCtx->itemVtx[i + 1].v.ob[2] = pauseCtx->itemVtx[i + 2].v.ob[2] =
                    pauseCtx->itemVtx[i + 3].v.ob[2] = 0;

                pauseCtx->itemVtx[i + 0].v.flag = pauseCtx->itemVtx[i + 1].v.flag = pauseCtx->itemVtx[i + 2].v.flag =
                    pauseCtx->itemVtx[i + 3].v.flag = 0;

                pauseCtx->itemVtx[i + 0].v.tc[0] = pauseCtx->itemVtx[i + 0].v.tc[1] = pauseCtx->itemVtx[i + 1].v.tc[1] =
                    pauseCtx->itemVtx[i + 2].v.tc[0] = 0;

                pauseCtx->itemVtx[i + 1].v.tc[0] = pauseCtx->itemVtx[i + 2].v.tc[1] = pauseCtx->itemVtx[i + 3].v.tc[0] =
                    pauseCtx->itemVtx[i + 3].v.tc[1] = 0x400;

                pauseCtx->itemVtx[i + 0].v.cn[0] = pauseCtx->itemVtx[i + 1].v.cn[0] = pauseCtx->itemVtx[i + 2].v.cn[0] =
                    pauseCtx->itemVtx[i + 3].v.cn[0] = pauseCtx->itemVtx[i + 0].v.cn[1] =
                        pauseCtx->itemVtx[i + 1].v.cn[1] = pauseCtx->itemVtx[i + 2].v.cn[1] =
                            pauseCtx->itemVtx[i + 3].v.cn[1] = pauseCtx->itemVtx[i + 0].v.cn[2] =
                                pauseCtx->itemVtx[i + 1].v.cn[2] = pauseCtx->itemVtx[i + 2].v.cn[2] =
                                    pauseCtx->itemVtx[i + 3].v.cn[2] = 255;

                pauseCtx->itemVtx[i + 0].v.cn[3] = pauseCtx->itemVtx[i + 1].v.cn[3] = pauseCtx->itemVtx[i + 2].v.cn[3] =
                    pauseCtx->itemVtx[i + 3].v.cn[3] = pauseCtx->alpha;
            } else {
                pauseCtx->itemVtx[i + 2].v.ob[0] = -300;
                pauseCtx->itemVtx[i + 0].v.ob[0] = pauseCtx->itemVtx[i + 2].v.ob[0];

                pauseCtx->itemVtx[i + 1].v.ob[0] = pauseCtx->itemVtx[i + 3].v.ob[0] =
                    pauseCtx->itemVtx[i + 0].v.ob[0] + 32;

                pauseCtx->itemVtx[i + 0].v.ob[1] = pauseCtx->itemVtx[i + 1].v.ob[1] = 300;
                pauseCtx->itemVtx[i + 2].v.ob[1] = pauseCtx->itemVtx[i + 3].v.ob[1] =
                    pauseCtx->itemVtx[i + 0].v.ob[1] - 32;
            }
        }
    }

    if (pauseCtx->pageIndex != PAUSE_MASK) {
        if (!sInDungeonScene) {
            pauseCtx->mapPageVtx = GRAPH_ALLOC(gfxCtx, 0x1080);
            j = func_80825A50(play, pauseCtx->mapPageVtx, 4, 36);

            for (i = 0, var_t3 = 59; i < 15; i++, j += 4, var_t3 -= 9) {
                pauseCtx->mapPageVtx[j + 2].v.ob[0] = -109;
                pauseCtx->mapPageVtx[j + 0].v.ob[0] = pauseCtx->mapPageVtx[j + 2].v.ob[0];

                pauseCtx->mapPageVtx[j + 1].v.ob[0] = pauseCtx->mapPageVtx[j + 3].v.ob[0] =
                    pauseCtx->mapPageVtx[j + 0].v.ob[0] + 216;

                pauseCtx->mapPageVtx[j + 0].v.ob[1] = pauseCtx->mapPageVtx[j + 1].v.ob[1] = var_t3 + pauseCtx->offsetY;

                pauseCtx->mapPageVtx[j + 2].v.ob[1] = pauseCtx->mapPageVtx[j + 3].v.ob[1] =
                    pauseCtx->mapPageVtx[j + 0].v.ob[1] - 9;

                pauseCtx->mapPageVtx[j + 0].v.ob[2] = pauseCtx->mapPageVtx[j + 1].v.ob[2] =
                    pauseCtx->mapPageVtx[j + 2].v.ob[2] = pauseCtx->mapPageVtx[j + 3].v.ob[2] = 0;

                pauseCtx->mapPageVtx[j + 0].v.flag = pauseCtx->mapPageVtx[j + 1].v.flag =
                    pauseCtx->mapPageVtx[j + 2].v.flag = pauseCtx->mapPageVtx[j + 3].v.flag = 0;

                pauseCtx->mapPageVtx[j + 0].v.tc[0] = pauseCtx->mapPageVtx[j + 0].v.tc[1] =
                    pauseCtx->mapPageVtx[j + 1].v.tc[1] = pauseCtx->mapPageVtx[j + 2].v.tc[0] = 0;

                pauseCtx->mapPageVtx[j + 1].v.tc[0] = pauseCtx->mapPageVtx[j + 3].v.tc[0] = 0x1B00;
                pauseCtx->mapPageVtx[j + 2].v.tc[1] = pauseCtx->mapPageVtx[j + 3].v.tc[1] = 0x120;

                pauseCtx->mapPageVtx[j + 0].v.cn[0] = pauseCtx->mapPageVtx[j + 2].v.cn[0] =
                    pauseCtx->mapPageVtx[j + 0].v.cn[1] = pauseCtx->mapPageVtx[j + 2].v.cn[1] =
                        pauseCtx->mapPageVtx[j + 0].v.cn[2] = pauseCtx->mapPageVtx[j + 2].v.cn[2] =
                            pauseCtx->mapPageVtx[j + 1].v.cn[0] = pauseCtx->mapPageVtx[j + 3].v.cn[0] =
                                pauseCtx->mapPageVtx[j + 1].v.cn[1] = pauseCtx->mapPageVtx[j + 3].v.cn[1] =
                                    pauseCtx->mapPageVtx[j + 1].v.cn[2] = pauseCtx->mapPageVtx[j + 3].v.cn[2] =
                                        pauseCtx->mapPageVtx[j + 0].v.cn[3] = pauseCtx->mapPageVtx[j + 2].v.cn[3] =
                                            pauseCtx->mapPageVtx[j + 1].v.cn[3] = pauseCtx->mapPageVtx[j + 3].v.cn[3] =
                                                pauseCtx->alpha;
            }

            pauseCtx->mapPageVtx[j - 2].v.ob[1] = pauseCtx->mapPageVtx[j - 1].v.ob[1] =
                pauseCtx->mapPageVtx[j - 4].v.ob[1] - 2;

            pauseCtx->mapPageVtx[j - 2].v.tc[1] = pauseCtx->mapPageVtx[j - 1].v.tc[1] = 0x40;

        } else {
            pauseCtx->mapPageVtx = GRAPH_ALLOC(gfxCtx, 0x540);
            func_80825A50(play, pauseCtx->mapPageVtx, 2, 6);
        }
    }

    if (pauseCtx->pageIndex != PAUSE_ITEM) {
        pauseCtx->questPageVtx = GRAPH_ALLOC(gfxCtx, 0x3C0);
        func_80825A50(play, pauseCtx->questPageVtx, 3, 0);

        pauseCtx->questVtx = GRAPH_ALLOC(gfxCtx, 0x9C0);

        for (k = 0, j = 0; j < 39; j++, k += 4) {
            if (j < 6) {
                pauseCtx->questVtx[k + 0].v.ob[0] = pauseCtx->questVtx[k + 2].v.ob[0] = D_8082BB74[j];

                pauseCtx->questVtx[k + 1].v.ob[0] = pauseCtx->questVtx[k + 3].v.ob[0] =
                    pauseCtx->questVtx[k + 0].v.ob[0] + D_8082BC14[j];

                pauseCtx->questVtx[k + 0].v.ob[1] = pauseCtx->questVtx[k + 1].v.ob[1] =
                    D_8082BBC4[j] + pauseCtx->offsetY;

                pauseCtx->questVtx[k + 2].v.ob[1] = pauseCtx->questVtx[k + 3].v.ob[1] =
                    pauseCtx->questVtx[k + 0].v.ob[1] - D_8082BC64[j];
            } else {
                pauseCtx->questVtx[k + 0].v.ob[0] = pauseCtx->questVtx[k + 2].v.ob[0] = D_8082BB74[j] + 2;

                pauseCtx->questVtx[k + 1].v.ob[0] = pauseCtx->questVtx[k + 3].v.ob[0] =
                    pauseCtx->questVtx[k + 0].v.ob[0] + D_8082BC14[j] - 4;

                pauseCtx->questVtx[k + 0].v.ob[1] = pauseCtx->questVtx[k + 1].v.ob[1] =
                    D_8082BBC4[j] + pauseCtx->offsetY - 2;

                pauseCtx->questVtx[k + 2].v.ob[1] = pauseCtx->questVtx[k + 3].v.ob[1] =
                    pauseCtx->questVtx[k + 0].v.ob[1] - D_8082BC64[j] + 4;
            }

            pauseCtx->questVtx[k + 0].v.ob[2] = pauseCtx->questVtx[k + 1].v.ob[2] = pauseCtx->questVtx[k + 2].v.ob[2] =
                pauseCtx->questVtx[k + 3].v.ob[2] = 0;

            pauseCtx->questVtx[k + 0].v.flag = pauseCtx->questVtx[k + 1].v.flag = pauseCtx->questVtx[k + 2].v.flag =
                pauseCtx->questVtx[k + 3].v.flag = 0;

            pauseCtx->questVtx[k + 0].v.tc[0] = pauseCtx->questVtx[k + 0].v.tc[1] = pauseCtx->questVtx[k + 1].v.tc[1] =
                pauseCtx->questVtx[k + 2].v.tc[0] = 0;

            pauseCtx->questVtx[k + 1].v.tc[0] = pauseCtx->questVtx[k + 3].v.tc[0] = D_8082BC14[j] << 5;
            pauseCtx->questVtx[k + 2].v.tc[1] = pauseCtx->questVtx[k + 3].v.tc[1] = D_8082BC64[j] << 5;

            pauseCtx->questVtx[k + 0].v.cn[0] = pauseCtx->questVtx[k + 1].v.cn[0] = pauseCtx->questVtx[k + 2].v.cn[0] =
                pauseCtx->questVtx[k + 3].v.cn[0] = pauseCtx->questVtx[k + 0].v.cn[1] =
                    pauseCtx->questVtx[k + 1].v.cn[1] = pauseCtx->questVtx[k + 2].v.cn[1] =
                        pauseCtx->questVtx[k + 3].v.cn[1] = pauseCtx->questVtx[k + 0].v.cn[2] =
                            pauseCtx->questVtx[k + 1].v.cn[2] = pauseCtx->questVtx[k + 2].v.cn[2] =
                                pauseCtx->questVtx[k + 3].v.cn[2] = 255;

            pauseCtx->questVtx[k + 0].v.cn[3] = pauseCtx->questVtx[k + 1].v.cn[3] = pauseCtx->questVtx[k + 2].v.cn[3] =
                pauseCtx->questVtx[k + 3].v.cn[3] = pauseCtx->alpha;
        }
    }

    if (pauseCtx->pageIndex != PAUSE_MAP) {
        pauseCtx->maskPageVtx = GRAPH_ALLOC(gfxCtx, 0x3C0);
        func_80825A50(play, pauseCtx->maskPageVtx, 0, 0);

        pauseCtx->maskVtx = GRAPH_ALLOC(gfxCtx, 0x6C0);

        for (k = 0, i = 0, var_t3 = 58; k < 4; k++, var_t3 -= 32) {
            for (var_a3 = -96, j = 0; j < 6; j++, i += 4, var_a3 += 32) {
                pauseCtx->maskVtx[i + 0].v.ob[0] = pauseCtx->maskVtx[i + 2].v.ob[0] = var_a3 + 2;
                pauseCtx->maskVtx[i + 1].v.ob[0] = pauseCtx->maskVtx[i + 3].v.ob[0] =
                    pauseCtx->maskVtx[i + 0].v.ob[0] + 28;

                pauseCtx->maskVtx[i + 0].v.ob[1] = pauseCtx->maskVtx[i + 1].v.ob[1] = var_t3 + pauseCtx->offsetY - 2;
                pauseCtx->maskVtx[i + 2].v.ob[1] = pauseCtx->maskVtx[i + 3].v.ob[1] =
                    pauseCtx->maskVtx[i + 0].v.ob[1] - 28;

                pauseCtx->maskVtx[i + 0].v.ob[2] = pauseCtx->maskVtx[i + 1].v.ob[2] = pauseCtx->maskVtx[i + 2].v.ob[2] =
                    pauseCtx->maskVtx[i + 3].v.ob[2] = 0;

                pauseCtx->maskVtx[i + 0].v.flag = pauseCtx->maskVtx[i + 1].v.flag = pauseCtx->maskVtx[i + 2].v.flag =
                    pauseCtx->maskVtx[i + 3].v.flag = 0;

                pauseCtx->maskVtx[i + 0].v.tc[0] = pauseCtx->maskVtx[i + 0].v.tc[1] = pauseCtx->maskVtx[i + 1].v.tc[1] =
                    pauseCtx->maskVtx[i + 2].v.tc[0] = 0;

                pauseCtx->maskVtx[i + 1].v.tc[0] = pauseCtx->maskVtx[i + 2].v.tc[1] = pauseCtx->maskVtx[i + 3].v.tc[0] =
                    pauseCtx->maskVtx[i + 3].v.tc[1] = 0x400;

                pauseCtx->maskVtx[i + 0].v.cn[0] = pauseCtx->maskVtx[i + 1].v.cn[0] = pauseCtx->maskVtx[i + 2].v.cn[0] =
                    pauseCtx->maskVtx[i + 3].v.cn[0] = pauseCtx->maskVtx[i + 0].v.cn[1] =
                        pauseCtx->maskVtx[i + 1].v.cn[1] = pauseCtx->maskVtx[i + 2].v.cn[1] =
                            pauseCtx->maskVtx[i + 3].v.cn[1] = pauseCtx->maskVtx[i + 0].v.cn[2] =
                                pauseCtx->maskVtx[i + 1].v.cn[2] = pauseCtx->maskVtx[i + 2].v.cn[2] =
                                    pauseCtx->maskVtx[i + 3].v.cn[2] = 255;

                pauseCtx->maskVtx[i + 0].v.cn[3] = pauseCtx->maskVtx[i + 1].v.cn[3] = pauseCtx->maskVtx[i + 2].v.cn[3] =
                    pauseCtx->maskVtx[i + 3].v.cn[3] = 255;
            }
        }

        for (j = 1; j < 4; j++, i += 4) {
            if (GET_CUR_FORM_BTN_SLOT(j) != ITEM_NONE) {
                k = (GET_CUR_FORM_BTN_SLOT(j) << 2) - 0x60;

                pauseCtx->maskVtx[i + 0].v.ob[0] = pauseCtx->maskVtx[i + 2].v.ob[0] = pauseCtx->maskVtx[k].v.ob[0] - 2;

                pauseCtx->maskVtx[i + 1].v.ob[0] = pauseCtx->maskVtx[i + 3].v.ob[0] =
                    pauseCtx->maskVtx[i + 0].v.ob[0] + 32;

                pauseCtx->maskVtx[i + 0].v.ob[1] = pauseCtx->maskVtx[i + 1].v.ob[1] = pauseCtx->maskVtx[k].v.ob[1] + 2;

                pauseCtx->maskVtx[i + 2].v.ob[1] = pauseCtx->maskVtx[i + 3].v.ob[1] =
                    pauseCtx->maskVtx[i + 0].v.ob[1] - 32;

                pauseCtx->maskVtx[i + 0].v.ob[2] = pauseCtx->maskVtx[i + 1].v.ob[2] = pauseCtx->maskVtx[i + 2].v.ob[2] =
                    pauseCtx->maskVtx[i + 3].v.ob[2] = 0;

                pauseCtx->maskVtx[i + 0].v.flag = pauseCtx->maskVtx[i + 1].v.flag = pauseCtx->maskVtx[i + 2].v.flag =
                    pauseCtx->maskVtx[i + 3].v.flag = 0;

                pauseCtx->maskVtx[i + 0].v.tc[0] = pauseCtx->maskVtx[i + 0].v.tc[1] = pauseCtx->maskVtx[i + 1].v.tc[1] =
                    pauseCtx->maskVtx[i + 2].v.tc[0] = 0;

                pauseCtx->maskVtx[i + 1].v.tc[0] = pauseCtx->maskVtx[i + 2].v.tc[1] = pauseCtx->maskVtx[i + 3].v.tc[0] =
                    pauseCtx->maskVtx[i + 3].v.tc[1] = 0x400;

                pauseCtx->maskVtx[i + 0].v.cn[0] = pauseCtx->maskVtx[i + 1].v.cn[0] = pauseCtx->maskVtx[i + 2].v.cn[0] =
                    pauseCtx->maskVtx[i + 3].v.cn[0] = pauseCtx->maskVtx[i + 0].v.cn[1] =
                        pauseCtx->maskVtx[i + 1].v.cn[1] = pauseCtx->maskVtx[i + 2].v.cn[1] =
                            pauseCtx->maskVtx[i + 3].v.cn[1] = pauseCtx->maskVtx[i + 0].v.cn[2] =
                                pauseCtx->maskVtx[i + 1].v.cn[2] = pauseCtx->maskVtx[i + 2].v.cn[2] =
                                    pauseCtx->maskVtx[i + 3].v.cn[2] = 255;

                pauseCtx->maskVtx[i + 0].v.cn[3] = pauseCtx->maskVtx[i + 1].v.cn[3] = pauseCtx->maskVtx[i + 2].v.cn[3] =
                    pauseCtx->maskVtx[i + 3].v.cn[3] = pauseCtx->alpha;
            } else {
                pauseCtx->maskVtx[i + 2].v.ob[0] = -300;
                pauseCtx->maskVtx[i + 0].v.ob[0] = pauseCtx->maskVtx[i + 2].v.ob[0];

                pauseCtx->maskVtx[i + 1].v.ob[0] = pauseCtx->maskVtx[i + 3].v.ob[0] =
                    pauseCtx->maskVtx[i + 0].v.ob[0] + 32;

                pauseCtx->maskVtx[i + 0].v.ob[1] = pauseCtx->maskVtx[i + 1].v.ob[1] = 300;
                pauseCtx->maskVtx[i + 2].v.ob[1] = pauseCtx->maskVtx[i + 3].v.ob[1] =
                    pauseCtx->maskVtx[i + 0].v.ob[1] - 32;
            }
        }
    }

    pauseCtx->cursorVtx = GRAPH_ALLOC(play->state.gfxCtx, 20 * sizeof(Vtx));

    for (i = 0; i < 20; i++) {
        pauseCtx->cursorVtx[i].v.ob[0] = pauseCtx->cursorVtx[i].v.ob[1] = pauseCtx->cursorVtx[i].v.ob[2] = 0;

        pauseCtx->cursorVtx[i].v.flag = 0;

        pauseCtx->cursorVtx[i].v.tc[0] = pauseCtx->cursorVtx[i].v.tc[1] = 0;

        pauseCtx->cursorVtx[i].v.cn[0] = pauseCtx->cursorVtx[i].v.cn[1] = pauseCtx->cursorVtx[i].v.cn[2] =
            pauseCtx->cursorVtx[i].v.cn[3] = 255;
    }

    pauseCtx->cursorVtx[1].v.tc[0] = pauseCtx->cursorVtx[2].v.tc[1] = pauseCtx->cursorVtx[3].v.tc[0] =
        pauseCtx->cursorVtx[3].v.tc[1] = pauseCtx->cursorVtx[5].v.tc[0] = pauseCtx->cursorVtx[6].v.tc[1] =
            pauseCtx->cursorVtx[7].v.tc[0] = pauseCtx->cursorVtx[7].v.tc[1] = pauseCtx->cursorVtx[9].v.tc[0] =
                pauseCtx->cursorVtx[10].v.tc[1] = pauseCtx->cursorVtx[11].v.tc[0] = pauseCtx->cursorVtx[11].v.tc[1] =
                    pauseCtx->cursorVtx[13].v.tc[0] = pauseCtx->cursorVtx[14].v.tc[1] =
                        pauseCtx->cursorVtx[15].v.tc[0] = pauseCtx->cursorVtx[15].v.tc[1] = 0x200;

    pauseCtx->cursorVtx[17].v.tc[0] = pauseCtx->cursorVtx[18].v.tc[1] = pauseCtx->cursorVtx[19].v.tc[0] =
        pauseCtx->cursorVtx[19].v.tc[1] = 0x400;

    pauseCtx->unk_1A4 = GRAPH_ALLOC(gfxCtx, 0x1C0);

    if ((pauseCtx->state == 7) || ((pauseCtx->state >= 8) && (pauseCtx->state < 0x13))) {
        pauseCtx->unk_1A0 = GRAPH_ALLOC(gfxCtx, 0x500);
        func_80825A50(play, pauseCtx->unk_1A0, 5, 5);
    }
}

void KaleidoScope_UpdateCursorSize(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 index;

    pauseCtx->cursorVtx[0].v.ob[0] = pauseCtx->cursorVtx[2].v.ob[0] = -8;
    pauseCtx->cursorVtx[1].v.ob[0] = pauseCtx->cursorVtx[3].v.ob[0] = pauseCtx->cursorVtx[0].v.ob[0] + 16;

    pauseCtx->cursorVtx[0].v.ob[1] = pauseCtx->cursorVtx[1].v.ob[1] = 8;
    pauseCtx->cursorVtx[2].v.ob[1] = pauseCtx->cursorVtx[3].v.ob[1] = pauseCtx->cursorVtx[0].v.ob[1] - 16;

    if (pauseCtx->cursorSpecialPos == 0) {
        switch (pauseCtx->pageIndex) {
            case PAUSE_ITEM:
                pauseCtx->unk_288 = D_8082BCB4[pauseCtx->unk_242[0]];
                pauseCtx->unk_28C = D_8082BCCC[pauseCtx->unk_24C[0]];
                pauseCtx->unk_290 = 15.0f;
                pauseCtx->unk_294 = 15.0f;
                break;

            case PAUSE_MAP:
                if (!sInDungeonScene) {
                    if ((pauseCtx->state >= 0x15) && (pauseCtx->state < 0x1A)) {
                        pauseCtx->unk_288 = D_8082BD34[pauseCtx->cursorPoint[4]];
                        pauseCtx->unk_28C = D_8082BD5C[pauseCtx->cursorPoint[4]];
                    } else {
                        pauseCtx->unk_288 = D_8082BCDC[pauseCtx->cursorPoint[4]];
                        pauseCtx->unk_28C = D_8082BD08[pauseCtx->cursorPoint[4]];
                    }
                    if ((pauseCtx->state < 0x15) || (pauseCtx->state >= 0x1A)) {
                        pauseCtx->unk_294 = 10.0f;
                        pauseCtx->unk_290 = 10.0f;
                    } else {
                        pauseCtx->unk_294 = 15.0f;
                        pauseCtx->unk_290 = 15.0f;
                    }
                } else {
                    pauseCtx->unk_288 = D_8082BD84[pauseCtx->cursorPoint[1]];
                    pauseCtx->unk_28C = D_8082BDA8[pauseCtx->cursorPoint[1]];
                    if (pauseCtx->cursorSlot[pauseCtx->pageIndex] >= 4) {
                        pauseCtx->unk_290 = 18.0f;
                        pauseCtx->unk_294 = 12.0f;
                    } else if (pauseCtx->cursorSlot[pauseCtx->pageIndex] == 3) {
                        pauseCtx->unk_294 = 12.0f;
                        pauseCtx->unk_290 = 40.0f;
                    } else {
                        pauseCtx->unk_294 = 15.0f;
                        pauseCtx->unk_290 = 15.0f;
                    }
                }
                break;

            case PAUSE_QUEST:
                if (YREG(69) == 0) {
                    pauseCtx->unk_288 = D_8082BDCC[pauseCtx->cursorPoint[2]];
                    pauseCtx->unk_28C = D_8082BE28[pauseCtx->cursorPoint[2]];
                } else {
                    pauseCtx->unk_288 = YREG(70);
                    pauseCtx->unk_28C = YREG(71);
                }
                pauseCtx->unk_294 = 17.0f;
                pauseCtx->unk_290 = 17.0f;
                if (pauseCtx->cursorSlot[pauseCtx->pageIndex] == 0x17) {
                    pauseCtx->unk_294 = 25.0f;
                    pauseCtx->unk_290 = 25.0f;
                } else if (pauseCtx->cursorSlot[pauseCtx->pageIndex] < 6) {
                    pauseCtx->unk_294 = 18.0f;
                    pauseCtx->unk_290 = 18.0f;
                } else if ((pauseCtx->cursorSlot[pauseCtx->pageIndex] >= 6) &&
                           (pauseCtx->cursorSlot[pauseCtx->pageIndex] < 0x12)) {
                    pauseCtx->unk_294 = 12.0f;
                    pauseCtx->unk_290 = 12.0f;
                }
                break;

            case PAUSE_MASK:
                pauseCtx->unk_288 = D_8082BCB4[pauseCtx->unk_242[3]];
                pauseCtx->unk_28C = D_8082BCCC[pauseCtx->unk_24C[3]];
                pauseCtx->unk_290 = 15.0f;
                pauseCtx->unk_294 = 15.0f;
                break;
        }

        pauseCtx->unk_286 += 0x300;
    } else {
        if (pauseCtx->cursorSpecialPos == 0xA) {
            pauseCtx->unk_288 = -93.0f;
        } else {
            pauseCtx->unk_288 = 101.0f;
        }
        pauseCtx->unk_286 += 0x300;
        pauseCtx->unk_294 = 16.0f;
        pauseCtx->unk_290 = 16.0f;
        pauseCtx->unk_28C = -4.0f;
    }

    if (pauseCtx->unk_290 < pauseCtx->unk_298) {
        pauseCtx->unk_290 = 0;
    } else {
        pauseCtx->unk_290 -= pauseCtx->unk_298;
    }

    if (pauseCtx->unk_294 < pauseCtx->unk_298) {
        pauseCtx->unk_294 = 0.0f;
    } else {
        pauseCtx->unk_294 -= pauseCtx->unk_298;
    }

    if (pauseCtx->unk_298 != 0.0f) {
        pauseCtx->unk_298 -= 1.0f;
    }

    D_8082DA60[0] = Math_SinS(pauseCtx->unk_286) * pauseCtx->unk_290;
    D_8082DA60[1] = Math_SinS(pauseCtx->unk_286 + 0x4000) * pauseCtx->unk_290;
    D_8082DA60[2] = Math_SinS(pauseCtx->unk_286 + 0x8000) * pauseCtx->unk_290;
    D_8082DA60[3] = Math_SinS(pauseCtx->unk_286 + 0xC000) * pauseCtx->unk_290;
    D_8082DA70[0] = Math_CosS(pauseCtx->unk_286) * pauseCtx->unk_294;
    D_8082DA70[1] = Math_CosS(pauseCtx->unk_286 + 0x4000) * pauseCtx->unk_294;
    D_8082DA70[2] = Math_CosS(pauseCtx->unk_286 + 0x8000) * pauseCtx->unk_294;
    D_8082DA70[3] = Math_CosS(pauseCtx->unk_286 + 0xC000) * pauseCtx->unk_294;
}

void KaleidoScope_DrawCursor(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 i;

    OPEN_DISPS(play->state.gfxCtx);

    if ((play->pauseCtx.unk_200 == 0) || (pauseCtx->unk_200 == 8) ||
        ((pauseCtx->pageIndex == 2) &&
         ((pauseCtx->unk_200 < 3) || (pauseCtx->unk_200 == 5) || (pauseCtx->unk_200 == 8)))) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, D_8082B890, D_8082B894, D_8082B898, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, D_8082B89C, D_8082B8A0, D_8082B8A4, 255);

        Matrix_Translate(pauseCtx->unk_288, pauseCtx->unk_28C, -50.0f, MTXMODE_NEW);
        Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

        for (i = 0; i < 4; i++) {
            Matrix_Push();
            Matrix_Translate(D_8082DA60[i], D_8082DA70[i], -50.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPPipeSync(POLY_OPA_DISP++);
            gDPLoadTextureBlock(POLY_OPA_DISP++, &D_08064340, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(POLY_OPA_DISP++, pauseCtx->cursorVtx, 4, 0);
            gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
            Matrix_Pop();
        }

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

#ifdef NON_MATCHING
void KaleidoScope_DrawGameOver(PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    s16 temp;

    OPEN_DISPS(gfxCtx);

    func_8012C628(gfxCtx);

    gDPSetCycleType(POLY_OPA_DISP++, G_CYC_2CYCLE);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_XLU_SURF2);
    gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT,
                      COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 80, D_8082B880, D_8082B884, D_8082B888, D_8082B88C);
    gDPSetEnvColor(POLY_OPA_DISP++, D_8082B8A8, D_8082B8AC, D_8082B8B0, 255);

    temp = D_8082BE84 - 2;

    gDPLoadTextureBlock(POLY_OPA_DISP++, gGameOverP1Tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadMultiBlock(POLY_OPA_DISP++, gGameOverMaskTex, 256, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0,
                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, 5, G_TX_NOLOD, G_TX_NOLOD);

    gDPSetTileSize(POLY_OPA_DISP++, 1, 0, temp & 0x7F, 252, (temp & 0x7F) + 0x7C);

    D_8082BE84 = temp;

    gSPTextureRectangle(POLY_OPA_DISP++, 0x0100, D_8082B944 << 2, 0x0200, (D_8082B944 + 32) << 2, G_TX_RENDERTILE, 0, 0,
                        1 << 10, 1 << 10);

    gDPLoadTextureBlock(POLY_OPA_DISP++, gGameOverP2Tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(POLY_OPA_DISP++, 0x0200, D_8082B944 << 2, 0x0300, (D_8082B944 + 32) << 2, G_TX_RENDERTILE, 0, 0,
                        1 << 10, 1 << 10);

    gDPLoadTextureBlock(POLY_OPA_DISP++, gGameOverP3Tex, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(POLY_OPA_DISP++, 0x0300, D_8082B944 << 2, 0x0400, (D_8082B944 + 32) << 2, G_TX_RENDERTILE, 0, 0,
                        1 << 10, 1 << 10);

    //! FAKE
    temp = D_8082BE84 - 2;
    temp += 0;

    CLOSE_DISPS(gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawGameOver.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Draw.s")

void KaleidoScope_GrayOutTextureRGBA32(u32* texture, u16 pixelCount) {
    u32 rgb;
    u32 gray;
    u16 i;
    s32 j;

    //! FAKE
    if (texture == NULL) {}

    for (i = 0; i < pixelCount; i++) {
        j = i;
        if ((texture[j] & 0xFFFFFF00) != 0) {
            rgb = texture[j] >> 8;
            gray = ((((rgb & 0xFF0000) >> 16) + ((rgb & 0xFF00) >> 7) + (rgb & 0xFF)) / 7) & 0xFF;

            rgb = gray;
            rgb <<= 8;
            rgb |= gray;
            rgb <<= 8;
            rgb |= gray;

            texture[j] = (rgb << 8) | (texture[j] & 0xFF);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80828788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Update.s")
