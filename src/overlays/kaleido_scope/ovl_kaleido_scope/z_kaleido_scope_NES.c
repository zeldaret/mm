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

void func_80178E3C(u8*, s32, s32, s32);

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

    if ((pauseCtx->debugState == 0) && (pauseCtx->unk_2B9 == 0)) {
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
void func_8081E7D8(PlayState*);
void func_8081FF80(PlayState*);
extern void* D_8082B700;
extern void* D_8082B73C;
extern void* D_8082B778;
extern void* D_8082B7B4;
extern s16 D_8082B890;
extern s16 D_8082B894;
extern s16 D_8082B898;
extern s16 D_8082B89C;
extern s16 D_8082B8A0;
extern s16 D_8082B8A4;
extern s16 D_8082B8B4;
extern f32 D_8082B908;
extern s16 D_8082B948[][3];
extern s16 D_8082B96C[][3];
extern s16 D_8082B990;
extern s16 D_8082B994;

// Should be much closer to match with in-function data
#ifdef NON_EQUIVALENT
void KaleidoScope_DrawPages(PlayState* play, GraphicsContext* gfxCtx) {
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stepR;
    s16 stepG;
    s16 stepB;

    OPEN_DISPS(gfxCtx);

    if ((pauseCtx->state < 8) || (pauseCtx->state >= 0x13)) {
        if (pauseCtx->state != 7) {

            stepR = ABS_ALT(D_8082B890 - D_8082B948[pauseCtx->unk_284 + D_8082B994][0]) / D_8082B990;
            stepG = ABS_ALT(D_8082B894 - D_8082B948[pauseCtx->unk_284 + D_8082B994][1]) / D_8082B990;
            stepB = ABS_ALT(D_8082B898 - D_8082B948[pauseCtx->unk_284 + D_8082B994][2]) / D_8082B990;

            if (D_8082B890 >= D_8082B948[pauseCtx->unk_284 + D_8082B994][0]) {
                D_8082B890 -= stepR;
            } else {
                D_8082B890 += stepR;
            }

            if (D_8082B894 >= D_8082B948[pauseCtx->unk_284 + D_8082B994][1]) {
                D_8082B894 -= stepG;
            } else {
                D_8082B894 += stepG;
            }

            if (D_8082B898 >= D_8082B948[pauseCtx->unk_284 + D_8082B994][2]) {
                D_8082B898 -= stepB;
            } else {
                D_8082B898 += stepB;
            }

            stepR = ABS_ALT(D_8082B89C - D_8082B96C[pauseCtx->unk_284 + D_8082B994][0]) / D_8082B990;
            stepG = ABS_ALT(D_8082B8A0 - D_8082B96C[pauseCtx->unk_284 + D_8082B994][1]) / D_8082B990;
            stepB = ABS_ALT(D_8082B8A4 - D_8082B96C[pauseCtx->unk_284 + D_8082B994][2]) / D_8082B990;

            if (D_8082B89C >= D_8082B96C[pauseCtx->unk_284 + D_8082B994][0]) {
                D_8082B89C -= stepR;
            } else {
                D_8082B89C += stepR;
            }

            if (D_8082B8A0 >= D_8082B96C[pauseCtx->unk_284 + D_8082B994][1]) {
                D_8082B8A0 -= stepG;
            } else {
                D_8082B8A0 += stepG;
            }

            if (D_8082B8A4 >= D_8082B96C[pauseCtx->unk_284 + D_8082B994][2]) {
                D_8082B8A4 -= stepB;
            } else {
                D_8082B8A4 += stepB;
            }

            D_8082B990--;

            if (D_8082B990 == 0) {
                D_8082B890 = D_8082B948[pauseCtx->unk_284 + D_8082B994][0];
                D_8082B894 = D_8082B948[pauseCtx->unk_284 + D_8082B994][1];
                D_8082B898 = D_8082B948[pauseCtx->unk_284 + D_8082B994][2];
                D_8082B89C = D_8082B96C[pauseCtx->unk_284 + D_8082B994][0];
                D_8082B8A0 = D_8082B96C[pauseCtx->unk_284 + D_8082B994][1];
                D_8082B8A4 = D_8082B96C[pauseCtx->unk_284 + D_8082B994][2];
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

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, &D_8082B73C);

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

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, &D_8082B778);

            if (D_8082B8B4 != 0) {
                func_8081D6DC(play);
                func_8012C8AC(gfxCtx);
                gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                func_801091F0(play);
            } else {
                func_8081E7D8(play);
            }
        }

        if ((pauseCtx->pageIndex != PAUSE_QUEST) && (pauseCtx->pageIndex != PAUSE_ITEM)) {
            gDPPipeSync(POLY_OPA_DISP++);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, 0, SHADE, 0);
            ;

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 180, 180, 120, 255);

            Matrix_RotateYF(-3.14f, MTXMODE_NEW);
            Matrix_Translate(0.0f, D_8082B908 / 100.0f, -93.0f, MTXMODE_APPLY);
            Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-pauseCtx->unk_218 / 100.0f);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, &D_8082B7B4);

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

            POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, &D_8082B700);

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

                    POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->itemPageVtx, &D_8082B73C);

                    func_8081B6EC(play);

                    return;
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

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->mapPageVtx, &D_8082B778);

                if (D_8082B8B4 != 0) {
                    func_8081D6DC(play);
                    func_8012C8AC(gfxCtx);

                    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

                    func_801091F0(play);
                    break;
                }

                Matrix_RotateYF(gGameInfo->data[0x258] / 1000.0f, MTXMODE_NEW);

                if ((pauseCtx->state == 4) || (pauseCtx->state == 0x16) || (pauseCtx->state >= 0x19) ||
                    ((pauseCtx->state == 7) && ((pauseCtx->unk_208 == 3) || (pauseCtx->unk_208 == 7)))) {
                    Matrix_Translate(0.0f, (gGameInfo->data[0x259] - 0x1F40) / 100.0f, gGameInfo->data[0x25A] / 100.0f,
                                     MTXMODE_APPLY);
                } else {
                    Matrix_Translate(0.0f, gGameInfo->data[0x259] / 100.0f, gGameInfo->data[0x25A] / 100.0f,
                                     MTXMODE_APPLY);
                }

                Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                Matrix_RotateXFApply(-pauseCtx->unk_214 / 100.0f);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                func_8081E7D8(play);
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

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->questPageVtx, &D_8082B7B4);

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

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                POLY_OPA_DISP = KaleidoScope_DrawPageSections(POLY_OPA_DISP, pauseCtx->maskPageVtx, &D_8082B700);

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825A50.s")

// KaleidoScope_InitVertices
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825E28.s")

// KaleidoScope_UpdateCursorSize
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808274DC.s")

// KaleidoScope_DrawCursor
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827A8C.s")

extern s16 D_8082B880;
extern s16 D_8082B884;
extern s16 D_8082B888;
extern s16 D_8082B88C;
extern s16 D_8082B8A8;
extern s16 D_8082B8AC;
extern s16 D_8082B8B0;
extern s16 D_8082B944;
extern s16 D_8082BE84;

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
