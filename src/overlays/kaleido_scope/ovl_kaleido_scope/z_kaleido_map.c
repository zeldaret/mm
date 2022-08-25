/*
 * File: z_kaleido_map.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu: Map Page
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

extern s16 D_8082B7F0[];
extern s16 D_8082B838[];

extern TexturePtr D_09007500;

extern TexturePtr D_0C000000; // gWorldMapImageTex
extern TexturePtr D_0C006C00; // gWorldMapImageTLUT
extern TexturePtr D_0C006E00;
extern TexturePtr D_0C001980;
extern TexturePtr D_0C014668;

void KaleidoScope_DrawDungeonStrayFairyCount(PlayState* play) {
    s16 counterDigits[2];
    s16 rectLeft;
    s16 digitIndex;

    OPEN_DISPS(play->state.gfxCtx);

    // Get digits for max number of stray faries
    counterDigits[1] = 15;
    counterDigits[0] = counterDigits[1] / 10;
    counterDigits[1] -= (s16)(counterDigits[0] * 10);

    // Draw max number of stray faries
    for (rectLeft = 116, digitIndex = 0; digitIndex < 2; digitIndex++, rectLeft += 8) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, 255);

        POLY_OPA_DISP = func_8010D7D0(POLY_OPA_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[digitIndex]), 8,
                                      16, rectLeft + 1, 146, 8, 16, 1 << 10, 1 << 10);

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

        gSPTextureRectangle(POLY_OPA_DISP++, rectLeft * 4, 580, (rectLeft * 4) + 32, 644, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    }

    // Draw Counter slash
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, 255);

    POLY_OPA_DISP =
        func_8010D7D0(POLY_OPA_DISP, gStrayFairyMapCounterSlashTex, 8, 16, 107, 146, 8, 16, 1 << 10, 1 << 10);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

    gSPTextureRectangle(POLY_OPA_DISP++, 424, 580, 456, 644, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    // Get digits for current number of stray faries collected
    counterDigits[1] = gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex];
    counterDigits[0] = counterDigits[1] / 10;
    counterDigits[1] -= (s16)(counterDigits[0] * 10);

    // Draw digits for current number of stray faries collected
    for (rectLeft = 88, digitIndex = 0; digitIndex < 2; digitIndex++, rectLeft += 8) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, 255);

        POLY_OPA_DISP = func_8010D7D0(POLY_OPA_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[digitIndex]), 8,
                                      16, rectLeft + 1, 146, 8, 16, 1 << 10, 1 << 10);

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

        gSPTextureRectangle(POLY_OPA_DISP++, rectLeft * 4, 580, (rectLeft * 4) + 32, 644, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

TexturePtr D_8082B4A0[] = {
    0x09003600,
    0x09003F00,
    0x09004800,
};
TexturePtr D_8082B4AC[] = {
    0x0D000000,
    0x0D000800,
    0x0D001000,
    0x0D001800,
};
s16 D_8082B4BC[] = { 67, 81, 95, 109 };
void KaleidoScope_DrawDungeonMap(PlayState* play) {
    static s16 D_8082B4C4 = 123;
    static s16 D_8082B4C8 = 30;
    static s16 D_8082B4CC = 0;
    static s16 D_8082B4D0 = 15;
    static s16 D_8082B4D4 = 0;
    static s16 D_8082B4D8 = 255;
    static f32 D_8082B4DC = 100.0f;
    static TexturePtr D_8082B4E0[][4] = {
        { 0x02008998, 0x0C001B80, 0x02008998, 0x0C001B80 },
        { 0x02009598, 0x0C002780, 0x02009598, 0x0C002780 },
        { 0x0200A198, 0x0C003380, 0x0200A198, 0x0C003380 },
        { 0x0200AD98, 0x0C003F80, 0x0200AD98, 0x0C003F80 },
    };
    static u8 D_8082B520[][3] = {
        { 255, 110, 160 },
        { 90, 255, 100 },
        { 120, 255, 255 },
        { 245, 245, 90 },
    };
    static u8 D_8082B52C[][3] = {
        { 255, 255, 255 },
        { 255, 255, 255 },
        { 255, 255, 255 },
        { 225, 170, 0 },
    };
    static s32 D_8082B538[] = { 1 << 10, 0, 0, 0 };
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 i;
    s16 j;
    f32 scale;

    OPEN_DISPS(play->state.gfxCtx);

    j = 72 + (pauseCtx->cursorSlot[PAUSE_MAP] * 4);
    KaleidoScope_SetCursorVtx(pauseCtx, j, pauseCtx->mapPageVtx);

    pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
    if (pauseCtx->cursorSpecialPos == 0) {
        if (pauseCtx->cursorPoint[PAUSE_MAP] < 4) {
            pauseCtx->cursorItem[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_MAP] + 0x74;
        }
        pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_MAP];
    }

    gSPVertex(POLY_OPA_DISP++, &pauseCtx->mapPageVtx[60], 16, 0);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA, G_CC_MODULATEIA);

    POLY_OPA_DISP = func_8010DC58(POLY_OPA_DISP, D_8082B4AC[((void)0, gSaveContext.dungeonIndex)], 128, 16, 0);

    gDPPipeSync(POLY_OPA_DISP++);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    for (i = 0, j = 4; i < 4; i++, j += 4) {
        if (i == 3) {
            if ((pauseCtx->pageIndex == PAUSE_MAP) && (pauseCtx->unk_200 == 0)) {
                // If (pauseCtx->state == PAUSE_STATE_6), then the other conditions are redundant and always return true
                if ((pauseCtx->state == PAUSE_STATE_6) && (pauseCtx->state != PAUSE_STATE_7) &&
                    !((pauseCtx->state >= PAUSE_STATE_GAMEOVER_0) && (pauseCtx->state <= PAUSE_STATE_GAMEOVER_10))) {
                    KaleidoScope_SetView(pauseCtx, 0.0f, 0.0f, 64.0f);

                    if (D_8082B4D4 == 0) {
                        D_8082B4D8 -= 6;
                        D_8082B4DC -= 1.0f;
                    } else {
                        D_8082B4D8 += 6;
                        D_8082B4DC += 1.0f;
                    }

                    D_8082B4D0--;
                    if (D_8082B4D0 == 0) {
                        D_8082B4D4 ^= 1;
                        D_8082B4D0 = 0xF;
                    }

                    func_8012C8AC(play->state.gfxCtx);

                    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0,
                                      PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE,
                                      0);

                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, D_8082B520[((void)0, gSaveContext.dungeonIndex)][0],
                                    D_8082B520[((void)0, gSaveContext.dungeonIndex)][1],
                                    D_8082B520[((void)0, gSaveContext.dungeonIndex)][2], D_8082B4D8);
                    gDPSetEnvColor(POLY_OPA_DISP++, D_8082B52C[((void)0, gSaveContext.dungeonIndex)][0],
                                   D_8082B52C[((void)0, gSaveContext.dungeonIndex)][1],
                                   D_8082B52C[((void)0, gSaveContext.dungeonIndex)][2], 0);

                    scale = D_8082B4DC / 100.0f;

                    Matrix_Translate(-83.0f, -29.0f, -128.0f, MTXMODE_NEW);
                    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    pauseCtx->mapPageVtx[76].v.ob[0] = pauseCtx->mapPageVtx[78].v.ob[0] = -16;

                    pauseCtx->mapPageVtx[77].v.ob[0] = pauseCtx->mapPageVtx[79].v.ob[0] =
                        pauseCtx->mapPageVtx[76].v.ob[0] + 32;

                    pauseCtx->mapPageVtx[76].v.ob[1] = pauseCtx->mapPageVtx[77].v.ob[1] = 12;

                    pauseCtx->mapPageVtx[78].v.ob[1] = pauseCtx->mapPageVtx[79].v.ob[1] =
                        pauseCtx->mapPageVtx[76].v.ob[1] - 24;

                    gSPVertex(POLY_OPA_DISP++, &pauseCtx->mapPageVtx[76], 4, 0);

                    POLY_OPA_DISP = func_8010DE38(POLY_OPA_DISP, gStrayFairyGlowingCircleIconTex, 4, 32, 24, 0);
                    KaleidoScope_SetView(pauseCtx, pauseCtx->eye.x, pauseCtx->eye.y, pauseCtx->eye.z);
                    func_8012C628(play->state.gfxCtx);

                    gDPPipeSync(POLY_OPA_DISP++);

                    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, D_8082B4D8);

                    D_8082B4C8--;

                    if (D_8082B4C8 == 0) {
                        D_8082B4CC = (D_8082B4CC + 1) & 3;
                        D_8082B4C8 = 0x22;
                    }

                    gDPLoadTextureBlock(POLY_OPA_DISP++, D_8082B4E0[((void)0, gSaveContext.dungeonIndex)][D_8082B4CC],
                                        G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 24, 0, G_TX_MIRROR | G_TX_WRAP,
                                        G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    gSPTextureRectangle(POLY_OPA_DISP++, 0x00D8, 0x0230, 0x0158, 0x0290, G_TX_RENDERTILE,
                                        D_8082B538[D_8082B4CC], 0, 0x0400, 0x0400);

                    KaleidoScope_DrawDungeonStrayFairyCount(play);
                    func_8012C8AC(play->state.gfxCtx);
                }
            }
        } else {
            if (CHECK_DUNGEON_ITEM(i, gSaveContext.dungeonIndex)) {
                gDPLoadTextureBlock(POLY_OPA_DISP++, D_8082B4A0[i], G_IM_FMT_RGBA, G_IM_SIZ_32b, 24, 24, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);

                gSP1Quadrangle(POLY_OPA_DISP++, j, j + 2, j + 3, j + 1, 0);
            }
        }
    }

    func_80108AF8(play);

    if ((pauseCtx->pageIndex == PAUSE_MAP) && (pauseCtx->unk_200 == 0)) {
        // If (pauseCtx->state == PAUSE_STATE_6), then the other conditions are redundant and always return true
        if ((pauseCtx->state == PAUSE_STATE_6) && (pauseCtx->state != PAUSE_STATE_7) &&
            !((pauseCtx->state >= PAUSE_STATE_GAMEOVER_0) && (pauseCtx->state <= PAUSE_STATE_GAMEOVER_10))) {

            func_8012C628(play->state.gfxCtx);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

            POLY_OPA_DISP =
                func_8010CB80(POLY_OPA_DISP, &D_09007500, 16, 16, 62, D_8082B4BC[XREG(94)], 16, 16, 1 << 10, 1 << 10);

            if (CHECK_DUNGEON_ITEM(1, gSaveContext.dungeonIndex)) {
                POLY_OPA_DISP = func_8010CB80(POLY_OPA_DISP, &D_0C001980, 16, 16, 108, D_8082B4BC[4 - func_80105318()],
                                              16, 16, 1 << 10, 1 << 10);
            }

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

            func_8012C8AC(play->state.gfxCtx);
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);

    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

    CLOSE_DISPS(play->state.gfxCtx);
}

void KaleidoScope_UpdateDungeonCursor(PlayState* play) {
    s32 pad;
    PauseContext* pauseCtx = &play->pauseCtx;
    MessageContext* msgCtx = &play->msgCtx;
    s16 i;
    s16 oldCursorPoint;

    if (pauseCtx->state == PAUSE_STATE_6) {
        if ((pauseCtx->unk_200 == 0) && (pauseCtx->pageIndex == PAUSE_MAP)) {
            pauseCtx->cursorColorSet = 0;
            oldCursorPoint = pauseCtx->cursorPoint[PAUSE_MAP];
            if (pauseCtx->stickRelX > 30) {
                pauseCtx->cursorShrinkRate = 4.0f;
                if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
                    func_80821A04(play);
                    pauseCtx->cursorXIndex[PAUSE_MAP] = 0;
                    pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->unk_256;
                    pauseCtx->cursorPoint[PAUSE_MAP] = pauseCtx->unk_256;
                } else if (pauseCtx->cursorSpecialPos == 0) {
                    if (pauseCtx->cursorXIndex[PAUSE_MAP] == 0) {
                        pauseCtx->cursorXIndex[PAUSE_MAP] = 1;
                        pauseCtx->cursorPoint[PAUSE_MAP] = 3;
                    } else {
                        if (pauseCtx->cursorPoint[PAUSE_MAP] == 3) {
                            pauseCtx->cursorPoint[PAUSE_MAP] = -1;
                        }

                        while (true) {
                            pauseCtx->cursorPoint[PAUSE_MAP]++;
                            if (pauseCtx->cursorPoint[PAUSE_MAP] == 3) {
                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                                break;
                            }
                            if (CHECK_DUNGEON_ITEM(pauseCtx->cursorPoint[PAUSE_MAP], gSaveContext.dungeonIndex)) {
                                break;
                            }
                        }
                    }
                }
            } else if (pauseCtx->stickRelX < -30) {
                pauseCtx->cursorShrinkRate = 4.0f;
                if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_RIGHT) {
                    func_80821A04(play);
                    pauseCtx->cursorXIndex[PAUSE_MAP] = 1;
                    pauseCtx->cursorPoint[PAUSE_MAP] = 2;
                    if (!CHECK_DUNGEON_ITEM(2, gSaveContext.dungeonIndex)) {
                        pauseCtx->cursorPoint[PAUSE_MAP]--;
                        if (!CHECK_DUNGEON_ITEM(1, gSaveContext.dungeonIndex)) {
                            pauseCtx->cursorPoint[PAUSE_MAP]--;
                            if (!CHECK_DUNGEON_ITEM(0, gSaveContext.dungeonIndex)) {
                                pauseCtx->cursorSlot[PAUSE_MAP] = 3;
                                pauseCtx->cursorPoint[PAUSE_MAP] = 3;
                            }
                        }
                    } else {
                        pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_MAP];
                    }
                } else if (pauseCtx->cursorSpecialPos == 0) {
                    if (pauseCtx->cursorXIndex[PAUSE_MAP] == 0) {
                        KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                    } else if (pauseCtx->cursorPoint[PAUSE_MAP] == 3) {
                        pauseCtx->cursorXIndex[PAUSE_MAP] = 0;
                        pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->unk_256;
                        pauseCtx->cursorPoint[PAUSE_MAP] = pauseCtx->unk_256;
                    } else {
                        while (true) {
                            pauseCtx->cursorPoint[PAUSE_MAP]--;
                            if (pauseCtx->cursorPoint[PAUSE_MAP] < 0) {
                                pauseCtx->cursorSlot[PAUSE_MAP] = 3;
                                pauseCtx->cursorPoint[PAUSE_MAP] = 3;
                                break;
                            }
                            if (CHECK_DUNGEON_ITEM(pauseCtx->cursorPoint[PAUSE_MAP], gSaveContext.dungeonIndex)) {
                                break;
                            }
                        }
                    }
                }
            } else {
                if ((pauseCtx->cursorSpecialPos == 0) && (pauseCtx->stickRelY > 30)) {
                    if (pauseCtx->cursorPoint[PAUSE_MAP] >= 4) {
                        for (i = pauseCtx->cursorPoint[PAUSE_MAP] - 5; i >= 0; i--) {
                            if ((gSaveContext.save.permanentSceneFlags[(void)0, gSaveContext.dungeonIndex].unk_14 &
                                 gBitFlags[i]) ||
                                func_801090B0(4 - i)) {
                                pauseCtx->cursorPoint[PAUSE_MAP] = i + 4;
                                pauseCtx->cursorShrinkRate = 4.0f;
                                break;
                            }
                        }
                    } else if (pauseCtx->cursorPoint[PAUSE_MAP] == 3) {
                        pauseCtx->cursorXIndex[PAUSE_MAP] = 0;
                        pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->unk_256;
                        pauseCtx->cursorPoint[PAUSE_MAP] = pauseCtx->unk_256;
                    } else {
                        pauseCtx->cursorSlot[PAUSE_MAP] = 3;
                        pauseCtx->cursorPoint[PAUSE_MAP] = 3;
                    }
                } else if ((pauseCtx->cursorSpecialPos == 0) && (pauseCtx->stickRelY < -30)) {
                    if ((pauseCtx->cursorPoint[PAUSE_MAP] >= 4) && (pauseCtx->cursorPoint[PAUSE_MAP] < 8)) {
                        for (i = pauseCtx->cursorPoint[PAUSE_MAP] - 3; i < 9; i++) {
                            if ((gSaveContext.save.permanentSceneFlags[(void)0, gSaveContext.dungeonIndex].unk_14 &
                                 gBitFlags[i]) ||
                                func_801090B0(4 - i)) {
                                pauseCtx->cursorPoint[PAUSE_MAP] = i + 4;
                                pauseCtx->cursorShrinkRate = 4.0f;
                                break;
                            }
                        }

                    } else if (pauseCtx->cursorXIndex[PAUSE_MAP] == 0) {
                        pauseCtx->cursorXIndex[PAUSE_MAP] = 1;
                        pauseCtx->cursorPoint[PAUSE_MAP] = 3;
                    } else {
                        if (pauseCtx->cursorPoint[PAUSE_MAP] == 3) {
                            pauseCtx->cursorPoint[PAUSE_MAP] = -1;
                        }

                        while (true) {
                            pauseCtx->cursorPoint[PAUSE_MAP]++;
                            if (pauseCtx->cursorPoint[PAUSE_MAP] == 4) {
                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                                break;
                            }
                            if (CHECK_DUNGEON_ITEM(pauseCtx->cursorPoint[PAUSE_MAP], gSaveContext.dungeonIndex)) {
                                break;
                            }
                        }
                    }
                }
            }
            if ((pauseCtx->cursorPoint[PAUSE_MAP] < 4) && (pauseCtx->cursorSpecialPos == 0)) {
                if (gSaveContext.buttonStatus[EQUIP_SLOT_A] == BTN_DISABLED) {
                    gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
                    gSaveContext.unk_3F22 = 0;
                    Interface_ChangeAlpha(50);
                }
            } else if (gSaveContext.buttonStatus[EQUIP_SLOT_A] != BTN_DISABLED) {
                gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
                gSaveContext.unk_3F22 = 0;
                Interface_ChangeAlpha(50);
            }

            if ((pauseCtx->cursorXIndex[PAUSE_MAP] == 0) && (pauseCtx->cursorSpecialPos == 0)) {
                pauseCtx->unk_256 = pauseCtx->cursorPoint[PAUSE_MAP];
            }

            if (pauseCtx->cursorSpecialPos == 0) {
                if ((CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A)) && (msgCtx->msgLength == 0) &&
                    (pauseCtx->cursorPoint[PAUSE_MAP] == 3)) {
                    pauseCtx->itemDescriptionOn = true;
                    func_801514B0(play, 0x17AF, 1);
                } else if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) && (msgCtx->msgLength == 0) &&
                           CHECK_DUNGEON_ITEM(pauseCtx->cursorPoint[PAUSE_MAP], gSaveContext.dungeonIndex)) {
                    pauseCtx->itemDescriptionOn = true;
                    func_801514B0(play, 0x17AC + pauseCtx->cursorPoint[PAUSE_MAP], 1);
                }
            }

            if (oldCursorPoint != pauseCtx->cursorPoint[PAUSE_MAP]) {
                play_sound(NA_SE_SY_CURSOR);
            }
        }
    }
}

TexturePtr D_8082B548[] = {
    0x0C008418, 0x0C009098, 0x0C012898, 0x0C0135D8, 0x0C014318, 0x0C00DE58, 0x0C00EB58, 0x0C00FAA8,
    0x0C009858, 0x0C009E58, 0x0C00AE58, 0x0C00BE58, 0x0C00CE58, 0x0C0109F8, 0x0C011958,
};
s16 D_8082B584[] = {
    0x0000, 0x0000, 0x00FF, 0x00FF, 0x00FF, 0x0000,
};
s16 D_8082B590[] = {
    0x00FF, 0x00FF, 0x0000, 0x0000, 0x0000, 0x00FF,
};
s16 D_8082B59C[] = {
    0x0056, 0x0068, 0x0091, 0x0099, 0x00A3, 0x009F, 0x009D, 0x00C7, 0x00D0, 0x00D2, 0x00DA, 0x0000,
};
s16 D_8082B5B4[] = {
    0x007F, 0x0099, 0x008A, 0x00AB, 0x0092, 0x0077, 0x004D, 0x006A, 0x0078, 0x0049, 0x0063, 0x0000,
};
s16 D_8082B5CC[] = {
    5, 4, 6, 0, 8, 5, 4, 6, 0, 8,
};
// Issues with the iterators (t, i, j, k)
// k appears unused but still shows up as sp46
#ifdef NON_MATCHING
void KaleidoScope_DrawWorldMap(PlayState* play) {
    s16 sceneId;
    s16 t; // sp4C
    s16 i; // sp4A
    s16 j; // sp48
    s16 k; // sp46???
    PauseContext* pauseCtx = &play->pauseCtx;
    u16(*regionSceneIndices)[]; // possibly need a ptr

    OPEN_DISPS(play->state.gfxCtx);

    KaleidoScope_SetCursorVtx(pauseCtx, pauseCtx->cursorSlot[1] * 4, pauseCtx->mapPageVtx);

    if ((pauseCtx->pageIndex == 1) && (pauseCtx->state == 6) &&
        ((pauseCtx->unk_200 == 0) || (pauseCtx->unk_200 == 3)) && (gGameInfo->data[0x246] != 0) &&
        (pauseCtx->state != 7) && ((pauseCtx->state < 8) || (pauseCtx->state >= 0x13))) {

        func_8012C628(play->state.gfxCtx);

        gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
        gDPLoadTLUT_pal256(POLY_OPA_DISP++, &D_0C006C00);
        gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_RGBA16);

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

        for (j = 62, t = 0; t < 16; t++, j += 8) {
            gDPLoadTextureBlock(POLY_OPA_DISP++, (u8*)&D_0C000000 + t * 192 * 9, G_IM_FMT_CI, G_IM_SIZ_8b, 216, 8, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(POLY_OPA_DISP++, 204, j * 4, 1068, (j * 4) + 32, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                1 << 10);
        }

        func_8012C8AC(play->state.gfxCtx);

    } else {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
        gDPLoadTLUT_pal256(POLY_OPA_DISP++, &D_0C006C00);
        gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_RGBA16);

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
        gSPVertex(POLY_OPA_DISP++, &pauseCtx->mapPageVtx[204], 32, 0);

        for (i = 0, t = 0, j = 0; i < 8; i++, t++, j += 4) {
            gDPLoadTextureBlock(POLY_OPA_DISP++, (u8*)&D_0C000000 + t * 216 * 9, G_IM_FMT_CI, G_IM_SIZ_8b, 216, 9, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gSP1Quadrangle(POLY_OPA_DISP++, j, j + 2, j + 3, j + 1, 0);
        }

        gSPVertex(POLY_OPA_DISP++, &pauseCtx->mapPageVtx[236], 28, 0);

        for (i = 0, j = 0; i < 6; i++, t++, j += 4) {
            gDPLoadTextureBlock(POLY_OPA_DISP++, (u8*)&D_0C000000 + t * 216 * 9, G_IM_FMT_CI, G_IM_SIZ_8b, 216, 9, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gSP1Quadrangle(POLY_OPA_DISP++, j, j + 2, j + 3, j + 1, 0);
        }

        gDPLoadTextureBlock(POLY_OPA_DISP++, (u8*)&D_0C000000 + t * 216 * 9, G_IM_FMT_CI, G_IM_SIZ_8b, 216, 2, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gSP1Quadrangle(POLY_OPA_DISP++, j, j + 2, j + 3, j + 1, 0);
    }

    func_8012C8AC(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);

    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 215, 235, 235, pauseCtx->alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 40, 60, 100, 0);

    for (i = 0; i < 15; i++) {
        if (!(((void)0, gSaveContext.save.mapsVisible) & gBitFlags[i])) {

            gSPVertex(POLY_OPA_DISP++, &pauseCtx->mapPageVtx[60 + i * 4], 4, 0);

            POLY_OPA_DISP = func_8010DC58(POLY_OPA_DISP, D_8082B548[i], D_8082B7F0[i], D_8082B838[i], 0);
        }
    }

    if ((pauseCtx->state >= 0x15) && (pauseCtx->state < 0x1A)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, gGameInfo->data[0x597]);
        gDPFillRectangle(POLY_OPA_DISP++, 50, 62, 270, 190);
    }

    func_8012C8AC(play->state.gfxCtx);

    j = 0;
    k = 0;
    if ((pauseCtx->state < 0x15) || (pauseCtx->state >= 0x1A)) {
        gDPLoadTextureBlock(POLY_OPA_DISP++, &D_0C006E00, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, D_8082B584[0], D_8082B584[1], D_8082B584[2], pauseCtx->alpha);

        gDPSetEnvColor(POLY_OPA_DISP++, D_8082B590[0], D_8082B590[1], D_8082B590[2], 0);

        if (gGameInfo->data[0x572] != 0) {
            gSaveContext.save.mapsVisible |= (u16)~0x8000;

            pauseCtx->mapPageVtx[0x78].v.ob[0] = pauseCtx->mapPageVtx[0x7A].v.ob[0] = gGameInfo->data[0x574];

            pauseCtx->mapPageVtx[0x79].v.ob[0] = pauseCtx->mapPageVtx[0x7B].v.ob[0] =
                pauseCtx->mapPageVtx[0x78].v.ob[0] + 8;

            pauseCtx->mapPageVtx[0x78].v.ob[1] = pauseCtx->mapPageVtx[0x79].v.ob[1] = gGameInfo->data[0x575];

            pauseCtx->mapPageVtx[0x7A].v.ob[1] = pauseCtx->mapPageVtx[0x7B].v.ob[1] =
                pauseCtx->mapPageVtx[0x78].v.ob[1] - 8;
        }

        for (i = 0; i < 11; i++, k++, j += 4) {
            if (pauseCtx->worldMapPoints[i] != 0) {
                gSPVertex(POLY_OPA_DISP++, &pauseCtx->mapPageVtx[120 + i * 4], 4, 0);
                gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
            }
        }

    } else {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPLoadTextureBlock(POLY_OPA_DISP++, &D_0C014668, G_IM_FMT_RGBA, G_IM_SIZ_32b, 24, 12, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

        if (gGameInfo->data[0x572] != 0) {
            gSaveContext.save.mapsVisible |= (u16)~0x8000;

            pauseCtx->mapPageVtx[0xA4].v.ob[0] = pauseCtx->mapPageVtx[0xA6].v.ob[0] = gGameInfo->data[0x574];

            pauseCtx->mapPageVtx[0xA5].v.ob[0] = pauseCtx->mapPageVtx[0xA7].v.ob[0] =
                pauseCtx->mapPageVtx[0xA4].v.ob[0] + 24;

            pauseCtx->mapPageVtx[0xA4].v.ob[1] = pauseCtx->mapPageVtx[0xA5].v.ob[1] = gGameInfo->data[0x575];

            pauseCtx->mapPageVtx[0xA6].v.ob[1] = pauseCtx->mapPageVtx[0xA7].v.ob[1] =
                pauseCtx->mapPageVtx[0xA4].v.ob[1] - 12;
        }

        for (i = 0; i < 10; i++, k++, j += 4) {
            if (pauseCtx->worldMapPoints[i] != 0) {
                gSPVertex(POLY_OPA_DISP++, &pauseCtx->mapPageVtx[164 + i * 4], 4, 0);
                gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
            }
        }
    }

    if ((pauseCtx->pageIndex == 1) && (pauseCtx->unk_200 == 0)) {
        if ((pauseCtx->state == 6) && (pauseCtx->state != 7) && ((pauseCtx->state < 8) || (pauseCtx->state >= 0x13))) {
            j = 0;
            i = 0;
            k = play->sceneNum;
            if (k == 7) {
                if (play->roomCtx.currRoom.num == 5) {
                    k = 0x4D;
                } else if ((play->roomCtx.currRoom.num == 6) || (play->roomCtx.currRoom.num == 8) ||
                           (play->roomCtx.currRoom.num == 0xC)) {
                    k = 0x2B;
                } else {
                    k = Entrance_GetSceneNumAbsolute(((void)0, gSaveContext.respawn[3].entrance));
                }
            }

            while (true) {
                if ((gScenesPerRegion[i][j] == 0xFFFF)) {
                    i++;
                    j = 0;
                    if (i == 0xB) {
                        i = 0;
                        if (k == 0x26) {
                            j = play->curSpawn;
                            i = D_8082B5CC[j];
                            break;
                        }

                        while (true) {
                            if (gScenesPerRegion[i][j] == 0xFFFF) {
                                i++;
                                if (i == 0xB) {
                                    break;
                                }
                                j = 0;
                                if (Entrance_GetSceneNumAbsolute(((void)0, gSaveContext.respawn[3].entrance)) ==
                                    gScenesPerRegion[i][j]) {
                                    break;
                                }
                            }
                            j++;
                        }
                        break;
                    }
                }

                if (k == gScenesPerRegion[i][j]) {
                    break;
                }
                j++;
            }

            if (i != 11) {
                KaleidoScope_SetView(pauseCtx, pauseCtx->eye.x, pauseCtx->eye.y, pauseCtx->eye.z);
                func_8012C628(play->state.gfxCtx);

                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

                POLY_OPA_DISP = func_8010CB80(POLY_OPA_DISP, &D_09007500, 16, 16, D_8082B59C[i], D_8082B5B4[i], 16, 16,
                                              1 << 10, 1 << 10);
            }
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);

    CLOSE_DISPS(play->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawWorldMap.s")
#endif

u16 D_8082B5E0[] = {
    0xAF, 0xB3, 0xAA, 0xB1, 0xA9, 0xB2, 0xA8, 0xB0, 0xAC, 0xAE,
};
void KaleidoScope_UpdateWorldMapCursor(PlayState* play) {
    static u16 D_8082B5F4 = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 oldCursorPoint;

    if ((pauseCtx->state == PAUSE_STATE_6) && (pauseCtx->unk_200 == 0) && (pauseCtx->pageIndex == PAUSE_MAP)) {
        pauseCtx->cursorColorSet = 0;
        oldCursorPoint = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];

        if (gSaveContext.buttonStatus[EQUIP_SLOT_A] != BTN_DISABLED) {
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
            gSaveContext.unk_3F22 = 0;
            Interface_ChangeAlpha(50);
        }

        if (pauseCtx->cursorSpecialPos == 0) {
            if (pauseCtx->stickRelX > 30) {
                pauseCtx->cursorShrinkRate = 4.0f;
                D_8082B5F4 = 0;

                while (true) {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP]++;
                    if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] >= 11) {
                        KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                        pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                        break;
                    }
                    if (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] != 0) {
                        break;
                    }
                }
            } else if (pauseCtx->stickRelX < -30) {
                pauseCtx->cursorShrinkRate = 4.0f;
                D_8082B5F4 = 0;

                while (true) {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP]--;
                    if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] < 0) {
                        KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                        pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                        break;
                    }
                    if (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] != 0) {
                        break;
                    }
                }
            } else {
                D_8082B5F4++;
            }

            if (pauseCtx->cursorSpecialPos == 0) {
                pauseCtx->cursorItem[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
                pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_WORLD_MAP] + 0x1F;
            }
        } else {
            pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
            if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
                if (pauseCtx->stickRelX > 30) {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = -1;
                    pauseCtx->cursorSpecialPos = 0;
                    pauseCtx->cursorShrinkRate = 4.0f;

                    while (true) {
                        pauseCtx->cursorPoint[PAUSE_WORLD_MAP]++;
                        if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] >= 11) {
                            KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                            pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                            break;
                        }
                        if (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] != 0) {
                            break;
                        }
                    }

                    if (pauseCtx->cursorSpecialPos == 0) {
                        pauseCtx->cursorItem[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
                        pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_WORLD_MAP] + 0x1F;
                    }
                    play_sound(NA_SE_SY_CURSOR);
                    D_8082B5F4 = 0;
                }
            } else if (pauseCtx->stickRelX < -30) {
                pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = 11;
                pauseCtx->cursorSpecialPos = 0;
                pauseCtx->cursorShrinkRate = 4.0f;

                while (true) {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP]--;
                    if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] < 0) {
                        KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                        pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                        break;
                    }
                    if (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] != 0) {
                        break;
                    }
                }

                if (pauseCtx->cursorSpecialPos == 0) {
                    pauseCtx->cursorItem[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
                    pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_WORLD_MAP] + 0x1F;
                }
                play_sound(NA_SE_SY_CURSOR);
                D_8082B5F4 = 0;
            }
        }

        if (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0) {
            pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
        }
        if (oldCursorPoint != pauseCtx->cursorPoint[PAUSE_WORLD_MAP]) {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if (pauseCtx->state == PAUSE_STATE_17) {
        pauseCtx->cursorColorSet = 4;
        oldCursorPoint = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];

        if (pauseCtx->stickRelX > 30) {
            pauseCtx->cursorShrinkRate = 4.0f;
            D_8082B5F4 = 0;
            do {
                pauseCtx->cursorPoint[PAUSE_WORLD_MAP]++;
                if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] >= 10) {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = 0;
                }
            } while (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0);
        } else if (pauseCtx->stickRelX < -30) {
            pauseCtx->cursorShrinkRate = 4.0f;
            D_8082B5F4 = 0;
            do {
                pauseCtx->cursorPoint[PAUSE_WORLD_MAP]--;
                if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] < 0) {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = 9;
                }
            } while (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0);
        } else {
            D_8082B5F4++;
        }

        pauseCtx->cursorItem[PAUSE_MAP] = D_8082B5E0[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] - 0xA4;
        pauseCtx->cursorSlot[PAUSE_MAP] = pauseCtx->cursorPoint[PAUSE_WORLD_MAP] + 0x1F;

        if (oldCursorPoint != pauseCtx->cursorPoint[PAUSE_WORLD_MAP]) {
            play_sound(NA_SE_SY_CURSOR);
        }
    }
}
