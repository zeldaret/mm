/*
 * File: z_kaleido_map.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu: Map Page
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

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
s16 D_8082B4BC[] = {
    0x0043,
    0x0051,
    0x005F,
    0x006D,
};
s16 D_8082B4C4 = 0x7B;
s16 D_8082B4C8 = 30;
s16 D_8082B4CC = 0;
s16 D_8082B4D0 = 0xF;
s16 D_8082B4D4 = 0;
s16 D_8082B4D8 = 0xFF;
f32 D_8082B4DC = 100.0f;
TexturePtr D_8082B4E0[] = {
    0x02008998, 0x0C001B80, 0x02008998, 0x0C001B80, 0x02009598, 0x0C002780, 0x02009598, 0x0C002780,
    0x0200A198, 0x0C003380, 0x0200A198, 0x0C003380, 0x0200AD98, 0x0C003F80, 0x0200AD98, 0x0C003F80,
};
s32 D_8082B520[] = {
    0xFF6EA05A,
    0xFF6478FF,
    0xFFF5F55A,
};
s32 D_8082B52C[] = {
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFE1AA00,
};
s32 D_8082B538[] = {
    0x00000400,
    0x00000000,
    0x00000000,
    0x00000000,
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawDungeonMap.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateDungeonCursor.s")

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
    0x0005, 0x0004, 0x0006, 0x0000, 0x0008, 0x0005, 0x0004, 0x0006, 0x0000, 0x0008,
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawWorldMap.s")

u16 D_8082B5E0[] = {
    0xAF, 0xB3, 0xAA, 0xB1, 0xA9, 0xB2, 0xA8, 0xB0, 0xAC, 0xAE,
};
#ifdef NON_EQUIVALENT
void KaleidoScope_UpdateWorldMapCursor(PlayState* play) {
    static u16 D_8082B5F4 = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 oldCursorPoint;

    if ((pauseCtx->state == PAUSE_STATE_6) && (pauseCtx->unk_200 == 0) && (pauseCtx->pageIndex == PAUSE_MAP)) {
        pauseCtx->cursorColorSet = 0;
        oldCursorPoint = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];

        if (gSaveContext.buttonStatus[4] != BTN_DISABLED) {
            gSaveContext.buttonStatus[4] = BTN_DISABLED;
            gSaveContext.unk_3F22 = 0;
            Interface_ChangeAlpha(50);
        }

        if (pauseCtx->cursorSpecialPos == 0) {
            if (pauseCtx->stickRelX > 30) {
                pauseCtx->unk_298 = 4.0f;
                D_8082B5F4 = 0;

                do {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP]++;
                    if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] >= 11) {
                        KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                        pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                        break;
                    }
                } while (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0);
            } else if (pauseCtx->stickRelX < -30) {
                pauseCtx->unk_298 = 4.0f;
                D_8082B5F4 = 0;

                do {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP]--;
                    if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] < 0) {
                        KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                        pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                        break;
                    }
                } while (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0);
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
                    pauseCtx->unk_298 = 4.0f;

                    do {
                        pauseCtx->cursorPoint[PAUSE_WORLD_MAP]++;
                        if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] >= 11) {
                            KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                            pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                            break;
                        }
                    } while (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0);

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
                pauseCtx->unk_298 = 4.0f;

                do {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP]--;
                    if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] < 0) {
                        KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                        pauseCtx->cursorItem[PAUSE_MAP] = PAUSE_ITEM_NONE;
                        break;
                    }
                } while (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0);

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
            pauseCtx->unk_298 = 4.0f;
            D_8082B5F4 = 0;
            do {
                pauseCtx->cursorPoint[PAUSE_WORLD_MAP]++;
                if (pauseCtx->cursorPoint[PAUSE_WORLD_MAP] >= 10) {
                    pauseCtx->cursorPoint[PAUSE_WORLD_MAP] = 0;
                }
            } while (pauseCtx->worldMapPoints[pauseCtx->cursorPoint[PAUSE_WORLD_MAP]] == 0);
        } else if (pauseCtx->stickRelX < -30) {
            pauseCtx->unk_298 = 4.0f;
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
#else
u16 D_8082B5F4 = 0;
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateWorldMapCursor.s")
#endif
