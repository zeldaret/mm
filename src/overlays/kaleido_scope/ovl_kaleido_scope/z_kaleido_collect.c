/*
 * File: z_kaleido_collect.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu - Quest Page
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

s32 KaleidoScope_UpdateQuestStatusPoint(PauseContext* pauseCtx, s16 point);

extern TexturePtr D_08061000;
extern TexturePtr D_08062000; // gSongNoteTex

s16 D_8082AED0[] = { 120, 60, 2, 80 };
s16 D_8082AED8[] = { 20, 4, 20, 10 };
s16 D_8082AEE0 = 0;
u8 D_8082AEE4[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
s16 D_8082AEF0[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
s16 D_8082AF04[][4] = {
    { 255, 0, 0, 255 },
    { 255, 70, 0, 150 },
    { 255, 70, 0, 150 },
    { 255, 0, 0, 255 },
};
s16 D_8082AF24[][3] = {
    { 0, 0, 0 },    // QUEST_REMAINS_ODOWLA Target 1
    { 0, 0, 0 },    // QUEST_REMAINS_GOHT Target 1
    { 0, 0, 0 },    // QUEST_REMAINS_GYORG Target 1
    { 0, 0, 0 },    // QUEST_REMAINS_TWINMOLD Target 1
    { 0, 0, 0 },    // Unused
    { 0, 0, 0 },    // Unused
    { 0, 60, 0 },   // QUEST_REMAINS_ODOWLA Target 2
    { 90, 0, 0 },   // QUEST_REMAINS_GOHT Target 2
    { 0, 40, 110 }, // QUEST_REMAINS_GYORG Target 2
    { 80, 40, 0 },  // QUEST_REMAINS_TWINMOLD Target 2
    { 70, 0, 90 },  // Unused
    { 90, 90, 0 },  // Unused
};
s16 D_8082AF6C[] = {
    255, // QUEST_REMAINS_ODOWLA
    255, // QUEST_REMAINS_GOHT
    255, // QUEST_REMAINS_GYORG
    255, // QUEST_REMAINS_TWINMOLD
    255, // Unused
    255, // Unused
};
s16 D_8082AF78[] = {
    255, // QUEST_REMAINS_ODOWLA
    255, // QUEST_REMAINS_GOHT
    255, // QUEST_REMAINS_GYORG
    255, // QUEST_REMAINS_TWINMOLD
    255, // Unused
    255, // Unused
};
s16 D_8082AF84[] = {
    150, // QUEST_REMAINS_ODOWLA
    150, // QUEST_REMAINS_GOHT
    150, // QUEST_REMAINS_GYORG
    150, // QUEST_REMAINS_TWINMOLD
    150, // Unused
    150, // Unused
};
#ifdef NON_MATCHING
// A single small regalloc at the first `Gfx_DrawTexQuadIA8` for the heart piece count (see `gItemIcons`)
void KaleidoScope_DrawQuestStatus(PlayState* play) {
    static s16 D_8082AF90 = 20;
    static s16 D_8082AF94 = 0;
    static s16 D_8082AF98 = 0;
    static s16 D_8082AF9C = 0;
    static s16 D_8082AFA0 = 0;
    static s16 D_8082AFA4 = 0;
    static s16 D_8082AFA8 = 20;
    static s16 D_8082AFAC = 0;
    static TexturePtr sOcarinaButtonTextures[] = {
        gOcarinaATex, gOcarinaCDownTex, gOcarinaCRightTex, gOcarinaCLeftTex, gOcarinaCUpTex,
    };
    static s16 D_8082AFC4[] = {
        150, 255, 100, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    };
    static s16 D_8082AFDC[] = {
        255, 80, 150, 160, 100, 240, 255, 255, 255, 255, 255, 255,
    };
    static s16 D_8082AFF4[] = {
        100, 40, 255, 0, 255, 100, 255, 255, 255, 255, 255, 255,
    };
    static TexturePtr D_8082B00C[][3] = {
        { 0x08053000, 0x08054000, 0x08055000 },
        { 0x08056000, 0x08057000, 0x08058000 },
    };
    static u8 D_8082B024[] = { UPG_QUIVER, UPG_BOMB_BAG };
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 sp1CA;
    s16 sp1C8;
    s16 sp1C6;
    s16 sp1C4;
    s16 var_v1;
    s16 i;
    s16 j;
    s16 var_s3;
    s16 sp1B4[3];
    u16 sp1B2;

    OPEN_DISPS(play->state.gfxCtx);

    KaleidoScope_SetCursorVtx(pauseCtx, pauseCtx->cursorSlot[PAUSE_QUEST] * 4, pauseCtx->questVtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

    // Draw the Boss Remains icons
    D_8082AF90--;
    for (i = 0, j = 0; i < 4; i++, j += 4) {
        if ((D_8082AF94 != 1) && (D_8082AF94 != 3)) {
            var_v1 = (D_8082AF94 != 0) ? (i + 6) : i;

            if (D_8082AF90 != 0) {
                sp1CA = ABS_ALT(D_8082AF6C[i] - D_8082AF24[var_v1][0]) / D_8082AF90;
                sp1C8 = ABS_ALT(D_8082AF78[i] - D_8082AF24[var_v1][1]) / D_8082AF90;
                sp1C6 = ABS_ALT(D_8082AF84[i] - D_8082AF24[var_v1][2]) / D_8082AF90;

                if (D_8082AF6C[i] >= D_8082AF24[var_v1][0]) {
                    D_8082AF6C[i] -= sp1CA;
                } else {
                    D_8082AF6C[i] += sp1CA;
                }
                if (D_8082AF78[i] >= D_8082AF24[var_v1][1]) {
                    D_8082AF78[i] -= sp1C8;
                } else {
                    D_8082AF78[i] += sp1C8;
                }
                if (D_8082AF84[i] >= D_8082AF24[var_v1][2]) {
                    D_8082AF84[i] -= sp1C6;
                } else {
                    D_8082AF84[i] += sp1C6;
                }
            } else {
                D_8082AF6C[i] = D_8082AF24[var_v1][0];
                D_8082AF78[i] = D_8082AF24[var_v1][1];
                D_8082AF84[i] = D_8082AF24[var_v1][2];
            }
        }

        if (CHECK_QUEST_ITEM(i)) {
            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
            gDPSetEnvColor(POLY_OPA_DISP++, D_8082AF6C[i], D_8082AF78[i], D_8082AF84[i], 0);
            gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);
            KaleidoScope_DrawTexQuadRGBA32(play->state.gfxCtx, gItemIcons[ITEM_REMAINS_ODOLWA + i], 32, 32, 0);
        }
    }

    if (D_8082AF90 == 0) {
        D_8082AF90 = D_8082AED0[D_8082AF94];
        if (++D_8082AF94 >= 4) {
            D_8082AF94 = 0;
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (GET_CUR_EQUIP_VALUE(1) != 0) {
        gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);
        KaleidoScope_DrawTexQuadRGBA32(play->state.gfxCtx, gItemIcons[(ITEM_SHIELD_HERO - 1) + GET_CUR_EQUIP_VALUE(1)],
                                       32, 32, 0);
    }

    j += 4;

    if (GET_CUR_EQUIP_VALUE(0) != 0) {
        gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);
        KaleidoScope_DrawTexQuadRGBA32(play->state.gfxCtx, gItemIcons[(ITEM_SWORD_KOKIRI - 1) + GET_CUR_EQUIP_VALUE(0)],
                                       32, 32, 0);
    }

    j += 4;

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);

    gDPLoadTextureBlock(POLY_OPA_DISP++, &D_08062000, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 24, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    for (i = 0; i < 12; i++, j += 4) {
        if (CHECK_QUEST_ITEM(QUEST_SONG_SONATA + i) ||
            ((i == 1) && !CHECK_QUEST_ITEM(QUEST_SONG_SONATA + i) && CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO))) {
            if ((i + 6) == pauseCtx->cursorSlot[PAUSE_QUEST]) {
                pauseCtx->questVtx[j + 0].v.ob[0] = pauseCtx->questVtx[j + 2].v.ob[0] =
                    pauseCtx->questVtx[j + 0].v.ob[0] - 2;

                pauseCtx->questVtx[j + 1].v.ob[0] = pauseCtx->questVtx[j + 3].v.ob[0] =
                    pauseCtx->questVtx[j + 1].v.ob[0] + 4;

                pauseCtx->questVtx[j + 0].v.ob[1] = pauseCtx->questVtx[j + 1].v.ob[1] =
                    pauseCtx->questVtx[j + 0].v.ob[1] + 2;

                pauseCtx->questVtx[j + 2].v.ob[1] = pauseCtx->questVtx[j + 3].v.ob[1] =
                    pauseCtx->questVtx[j + 2].v.ob[1] - 4;
            }

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, D_8082AFC4[i], D_8082AFDC[i], D_8082AFF4[i], pauseCtx->alpha);
            gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);
            gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);

    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
        gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);
        KaleidoScope_DrawTexQuadRGBA32(play->state.gfxCtx, &D_08061000, 32, 32, 0);
    }

    j += 4;

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

    for (i = 0; i < 2; i++, j += 4) {
        gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

        if (GET_CUR_UPG_VALUE(D_8082B024[i]) != 0) {
            KaleidoScope_DrawTexQuadRGBA32(play->state.gfxCtx, D_8082B00C[i][GET_CUR_UPG_VALUE(D_8082B024[i]) - 1], 32,
                                           32, 0);
        }
    }

    j += 4;

    sp1CA = ABS_ALT(D_8082AF98 - D_8082AF04[D_8082AFAC][0]) / D_8082AFA8;
    sp1C8 = ABS_ALT(D_8082AF9C - D_8082AF04[D_8082AFAC][1]) / D_8082AFA8;
    sp1C6 = ABS_ALT(D_8082AFA0 - D_8082AF04[D_8082AFAC][2]) / D_8082AFA8;
    sp1C4 = ABS_ALT(D_8082AFA4 - D_8082AF04[D_8082AFAC][3]) / D_8082AFA8;

    if (D_8082AF98 >= D_8082AF04[D_8082AFAC][0]) {
        D_8082AF98 -= sp1CA;
    } else {
        D_8082AF98 += sp1CA;
    }

    if (D_8082AF9C >= D_8082AF04[D_8082AFAC][1]) {
        D_8082AF9C -= sp1C8;
    } else {
        D_8082AF9C += sp1C8;
    }

    if (D_8082AFA0 >= D_8082AF04[D_8082AFAC][2]) {
        D_8082AFA0 -= sp1C6;
    } else {
        D_8082AFA0 += sp1C6;
    }

    if (D_8082AFA4 >= D_8082AF04[D_8082AFAC][3]) {
        D_8082AFA4 -= sp1C4;
    } else {
        D_8082AFA4 += sp1C4;
    }

    D_8082AFA8--;
    if (D_8082AFA8 == 0) {
        D_8082AF98 = D_8082AF04[D_8082AFAC][0];
        D_8082AF9C = D_8082AF04[D_8082AFAC][1];
        D_8082AFA0 = D_8082AF04[D_8082AFAC][2];
        D_8082AFA4 = D_8082AF04[D_8082AFAC][3];
        D_8082AFA8 = D_8082AED8[D_8082AFAC];
        if (++D_8082AFAC >= 4) {
            D_8082AFAC = 0;
        }
    }

    if ((GET_SAVE_INVENTORY_QUEST_ITEMS >> QUEST_HEART_PIECE_COUNT) != 0) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

        if ((pauseCtx->state == PAUSE_STATE_OPENING_3) || (pauseCtx->state == PAUSE_STATE_UNPAUSE_SETUP)) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, D_8082AF04[0][0], D_8082AF04[0][1], D_8082AF04[0][2],
                            pauseCtx->alpha);
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, D_8082AF98, D_8082AF9C, D_8082AFA0, D_8082AFA4);
        }

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
        gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);

        POLY_OPA_DISP =
            Gfx_DrawTexQuadIA8(POLY_OPA_DISP,
                               gItemIcons[((ITEM_HEART_PIECE_2 - 1) +
                                           ((GET_SAVE_INVENTORY_QUEST_ITEMS & 0xF0000000) >> QUEST_HEART_PIECE_COUNT))],
                               48, 48, 0);
    }

    j += 4;

    if (pauseCtx->state == PAUSE_STATE_MAIN) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

        if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYBACK) {
            pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();

            if (pauseCtx->ocarinaStaff->pos != 0) {
                if (D_8082AEE0 == (pauseCtx->ocarinaStaff->pos - 1)) {
                    D_8082AEE0++;
                    D_8082AEE4[pauseCtx->ocarinaStaff->pos - 1] = pauseCtx->ocarinaStaff->buttonIndex;
                }

                for (i = 0, var_s3 = 0; i < 8; i++, var_s3 += 4, j += 4) {
                    if (D_8082AEE4[i] == OCARINA_BTN_INVALID) {
                        break;
                    }

                    if (D_8082AEF0[i] != 255) {
                        D_8082AEF0[i] += 50;
                        if (D_8082AEF0[i] >= 255) {
                            D_8082AEF0[i] = 255;
                        }
                    }

                    pauseCtx->questVtx[j + 0].v.ob[1] = pauseCtx->questVtx[j + 1].v.ob[1] =
                        pauseCtx->ocarinaButtonsY[D_8082AEE4[i]];

                    pauseCtx->questVtx[j + 2].v.ob[1] = pauseCtx->questVtx[j + 3].v.ob[1] =
                        pauseCtx->questVtx[j + 0].v.ob[1] - 12;

                    gDPPipeSync(POLY_OPA_DISP++);

                    if (D_8082AEE4[i] == OCARINA_BTN_A) {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 80, 150, 255, D_8082AEF0[i]);
                    } else {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 50, D_8082AEF0[i]);
                    }

                    gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);

                    POLY_OPA_DISP = Gfx_DrawTexQuadIA8(POLY_OPA_DISP, sOcarinaButtonTextures[D_8082AEE4[i]], 16, 16, 0);
                }
            }
        } else if (((pauseCtx->mainState >= PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING_INIT) &&
                    (pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING_DONE)) ||
                   (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) {
            sp1C8 = pauseCtx->ocarinaSongIndex;
            sp1CA = gOcarinaSongButtons[sp1C8].numButtons;

            i = j;

            for (var_s3 = 0; var_s3 < sp1CA; var_s3++, j += 4) {
                pauseCtx->questVtx[j + 0].v.ob[1] = pauseCtx->questVtx[j + 1].v.ob[1] =
                    pauseCtx->ocarinaButtonsY[gOcarinaSongButtons[sp1C8].buttonIndex[var_s3]];

                pauseCtx->questVtx[j + 2].v.ob[1] = pauseCtx->questVtx[j + 3].v.ob[1] =
                    pauseCtx->questVtx[j + 0].v.ob[1] - 12;

                gDPPipeSync(POLY_OPA_DISP++);

                if (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG) {
                    if (gOcarinaSongButtons[sp1C8].buttonIndex[var_s3] == 0) {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 80, 150, 255, 200);
                    } else {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 50, 200);
                    }
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 150, 150, 150, 150);
                }

                gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);

                POLY_OPA_DISP = Gfx_DrawTexQuadIA8(
                    POLY_OPA_DISP, sOcarinaButtonTextures[gOcarinaSongButtons[sp1C8].buttonIndex[var_s3]], 16, 16, 0);
            }

            if (pauseCtx->mainState != PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG) {
                pauseCtx->ocarinaStaff = AudioOcarina_GetPlayingStaff();

                if (pauseCtx->ocarinaStaff->pos != 0) {
                    if (D_8082AEE0 == (pauseCtx->ocarinaStaff->pos - 1)) {
                        if (pauseCtx->ocarinaStaff->buttonIndex < 5) {
                            D_8082AEE4[pauseCtx->ocarinaStaff->pos - 1] = pauseCtx->ocarinaStaff->buttonIndex;
                            D_8082AEE4[pauseCtx->ocarinaStaff->pos] = OCARINA_BTN_INVALID;
                            D_8082AEE0++;
                        }
                    }
                }

                j = i + 32;
                var_s3 = 0;
                for (; var_s3 < 8; var_s3++, j += 4) {
                    if (D_8082AEE4[var_s3] == OCARINA_BTN_INVALID) {
                        continue;
                    }

                    if (D_8082AEF0[var_s3] != 255) {
                        D_8082AEF0[var_s3] += 50;
                        if (D_8082AEF0[var_s3] >= 255) {
                            D_8082AEF0[var_s3] = 255;
                        }
                    }

                    pauseCtx->questVtx[j + 0].v.ob[1] = pauseCtx->questVtx[j + 1].v.ob[1] =
                        pauseCtx->ocarinaButtonsY[D_8082AEE4[var_s3]];

                    pauseCtx->questVtx[j + 2].v.ob[1] = pauseCtx->questVtx[j + 3].v.ob[1] =
                        pauseCtx->questVtx[j + 0].v.ob[1] - 12;

                    gDPPipeSync(POLY_OPA_DISP++);

                    if (D_8082AEE4[var_s3] == OCARINA_BTN_A) {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 80, 150, 255, D_8082AEF0[var_s3]);
                    } else {
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 50, D_8082AEF0[var_s3]);
                    }

                    gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[j], 4, 0);

                    POLY_OPA_DISP =
                        Gfx_DrawTexQuadIA8(POLY_OPA_DISP, sOcarinaButtonTextures[D_8082AEE4[var_s3]], 16, 16, 0);
                }

                if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING_INIT) {
                    for (var_s3 = 0; var_s3 < 8; var_s3++) {
                        D_8082AEE4[var_s3] = OCARINA_BTN_INVALID;
                        D_8082AEF0[var_s3] = 0;
                    }

                    D_8082AEE0 = 0;
                    AudioOcarina_SetInstrument(1);
                    AudioOcarina_StartDefault((1 << pauseCtx->ocarinaSongIndex) | 0x80000000);
                    pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
                    pauseCtx->ocarinaStaff->pos = 0;
                    pauseCtx->ocarinaStaff->state = 0xFE;
                    pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING;
                }
            }
        }
    }

    // QUEST_SKULL_TOKEN never properly set
    if (CHECK_QUEST_ITEM(QUEST_SKULL_TOKEN) && ((play->sceneId == 0x27) || (play->sceneId == 0x28))) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

        sp1B4[0] = sp1B4[1] = 0;
        sp1B4[2] = Inventory_GetSkullTokenCount(play->sceneId);

        while (sp1B4[2] >= 100) {
            sp1B4[0]++;
            sp1B4[2] -= 100;
        }

        while (sp1B4[2] >= 10) {
            sp1B4[1]++;
            sp1B4[2] -= 10;
        }

        gSPVertex(POLY_OPA_DISP++, &pauseCtx->questVtx[152], 24, 0);

        for (var_s3 = 0, i = 0; var_s3 < 2; var_s3 += 1) {
            if (var_s3 == 0) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, pauseCtx->alpha);
            } else if (Inventory_GetSkullTokenCount(play->sceneId) == 100) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 200, 50, 50, pauseCtx->alpha);
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
            }

            sp1B2 = false;
            for (j = 0; j < 3; j++, i += 4) {
                if ((j >= 2) || (sp1B4[j] != 0) || sp1B2) {
                    gDPLoadTextureBlock(POLY_OPA_DISP++, ((u8*)gCounterDigit0Tex + (8 * 16 * sp1B4[j])), G_IM_FMT_I,
                                        G_IM_SIZ_8b, 8, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                    gSP1Quadrangle(POLY_OPA_DISP++, i, i + 2, i + 3, i + 1, 0);

                    sp1B2 = true;
                }
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
#else
s16 D_8082AF90 = 20;
s16 D_8082AF94 = 0;
s16 D_8082AF98 = 0;
s16 D_8082AF9C = 0;
s16 D_8082AFA0 = 0;
s16 D_8082AFA4 = 0;
s16 D_8082AFA8 = 20;
s16 D_8082AFAC = 0;
TexturePtr sOcarinaButtonTextures[] = {
    gOcarinaATex, gOcarinaCDownTex, gOcarinaCRightTex, gOcarinaCLeftTex, gOcarinaCUpTex,
};
s16 D_8082AFC4[] = {
    150, 255, 100, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};
s16 D_8082AFDC[] = {
    255, 80, 150, 160, 100, 240, 255, 255, 255, 255, 255, 255,
};
s16 D_8082AFF4[] = {
    100, 40, 255, 0, 255, 100, 255, 255, 255, 255, 255, 255,
};
TexturePtr D_8082B00C[][3] = {
    { 0x08053000, 0x08054000, 0x08055000 },
    { 0x08056000, 0x08057000, 0x08058000 },
};
u8 D_8082B024[] = { UPG_QUIVER, UPG_BOMB_BAG };
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawQuestStatus.s")
#endif

typedef enum {
    /* -3 */ CURSOR_TO_LEFT = -3, // Cursor on the "scroll to left page" position
    /* -2 */ CURSOR_TO_RIGHT,     // Cursor on the "scroll to right page" position
    /* -1 */ CURSOR_NONE          // No position in that direction, cursor stays where it is
} CursorPointNext;

typedef struct {
    /* 0x0 */ s16 up;
    /* 0x2 */ s16 down;
    /* 0x4 */ s16 left;
    /* 0x6 */ s16 right;
} CursorPointDirection;

void KaleidoScope_UpdateQuestCursor(PlayState* play) {
    static s16 D_8082B028 = 0;
    static CursorPointDirection sCursorPointLinks[] = {
        { CURSOR_NONE, QUEST_REMAINS_TWINMOLD, QUEST_REMAINS_GYORG, QUEST_REMAINS_GOHT },     // QUEST_REMAINS_ODOWLA
        { QUEST_REMAINS_ODOWLA, QUEST_SHIELD, QUEST_REMAINS_TWINMOLD, CURSOR_TO_RIGHT },      // QUEST_REMAINS_GOHT
        { QUEST_REMAINS_ODOWLA, QUEST_SWORD, QUEST_HEART_PIECE, QUEST_REMAINS_TWINMOLD },     // QUEST_REMAINS_GYORG
        { QUEST_REMAINS_ODOWLA, QUEST_SHIELD, QUEST_REMAINS_GYORG, QUEST_REMAINS_GOHT },      // QUEST_REMAINS_TWINMOLD
        { QUEST_REMAINS_GOHT, QUEST_BOMB_BAG, QUEST_SWORD, CURSOR_TO_RIGHT },                 // QUEST_SHIELD
        { QUEST_REMAINS_GYORG, QUEST_QUIVER, QUEST_SONG_STORMS, QUEST_SHIELD },               // QUEST_SWORD
        { QUEST_SONG_TIME, CURSOR_NONE, CURSOR_TO_LEFT, QUEST_SONG_LULLABY },                 // QUEST_SONG_SONATA
        { QUEST_SONG_HEALING, CURSOR_NONE, QUEST_SONG_SONATA, QUEST_SONG_BOSSA_NOVA },        // QUEST_SONG_LULLABY
        { QUEST_SONG_EPONA, CURSOR_NONE, QUEST_SONG_LULLABY, QUEST_SONG_ELEGY },              // QUEST_SONG_BOSSA_NOVA
        { QUEST_SONG_SOARING, CURSOR_NONE, QUEST_SONG_BOSSA_NOVA, QUEST_SONG_OATH },          // QUEST_SONG_ELEGY
        { QUEST_SONG_STORMS, CURSOR_NONE, QUEST_SONG_ELEGY, QUEST_QUIVER },                   // QUEST_SONG_OATH
        { QUEST_SONG_SUN, CURSOR_NONE, QUEST_SONG_OATH, QUEST_SWORD },                        // QUEST_SONG_SARIA
        { QUEST_BOMBERS_NOTEBOOK, QUEST_SONG_SONATA, CURSOR_TO_LEFT, QUEST_SONG_HEALING },    // QUEST_SONG_TIME
        { QUEST_BOMBERS_NOTEBOOK, QUEST_SONG_LULLABY, QUEST_SONG_TIME, QUEST_SONG_EPONA },    // QUEST_SONG_HEALING
        { QUEST_HEART_PIECE, QUEST_SONG_BOSSA_NOVA, QUEST_SONG_HEALING, QUEST_SONG_SOARING }, // QUEST_SONG_EPONA
        { QUEST_HEART_PIECE, QUEST_SONG_ELEGY, QUEST_SONG_EPONA, QUEST_SONG_STORMS },         // QUEST_SONG_SOARING
        { QUEST_HEART_PIECE, QUEST_SONG_OATH, QUEST_SONG_SOARING, QUEST_SWORD },              // QUEST_SONG_STORMS
        { QUEST_HEART_PIECE, QUEST_SONG_SARIA, QUEST_SONG_STORMS, QUEST_SWORD },              // QUEST_SONG_SUN
        { CURSOR_NONE, QUEST_SONG_TIME, CURSOR_TO_LEFT, QUEST_HEART_PIECE },                  // QUEST_BOMBERS_NOTEBOOK
        { QUEST_SWORD, CURSOR_NONE, QUEST_SONG_OATH, QUEST_BOMB_BAG },                        // QUEST_QUIVER
        { QUEST_SHIELD, CURSOR_NONE, QUEST_QUIVER, CURSOR_TO_RIGHT },                         // QUEST_BOMB_BAG
        { QUEST_QUIVER, QUEST_SONG_TIME, CURSOR_TO_LEFT, QUEST_HEART_PIECE },                 // QUEST_SKULL_TOKEN
        { CURSOR_NONE, QUEST_SONG_STORMS, QUEST_BOMBERS_NOTEBOOK, QUEST_REMAINS_GYORG },      // QUEST_HEART_PIECE
    };
    PauseContext* pauseCtx = &play->pauseCtx;
    MessageContext* msgCtx = &play->msgCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s32 pad;
    s16 nextCursorPoint;
    s16 oldCursorPoint;
    s16 i;
    u16 cursor;
    u16 cursorItem;

    pauseCtx->nameColorSet = PAUSE_NAME_COLOR_SET_WHITE;
    pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_WHITE;

    // != PAUSE_MAIN_STATE_IDLE
    if ((pauseCtx->state == PAUSE_STATE_MAIN) &&
        (!pauseCtx->mainState || (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) ||
         (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) &&
        (pauseCtx->pageIndex == PAUSE_QUEST) && !pauseCtx->itemDescriptionOn) {
        if (pauseCtx->cursorSpecialPos == 0) {
            oldCursorPoint = pauseCtx->cursorPoint[PAUSE_QUEST];

            if (pauseCtx->stickAdjX < -30) {
                // Move cursor left
                if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
                pauseCtx->cursorShrinkRate = 4.0f;

                nextCursorPoint = sCursorPointLinks[oldCursorPoint].left;
                if (nextCursorPoint == CURSOR_TO_LEFT) {
                    KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                    pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    if (interfaceCtx->unk_212 == 6) {
                        func_8011552C(play, 0x15);
                    }
                    return;
                } else {
                    while (nextCursorPoint > CURSOR_NONE) {
                        if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, nextCursorPoint) != 0) {
                            break;
                        }
                        nextCursorPoint = sCursorPointLinks[nextCursorPoint].left;
                    }
                }
            } else if (pauseCtx->stickAdjX > 30) {
                // Move cursor right
                if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
                pauseCtx->cursorShrinkRate = 4.0f;
                nextCursorPoint = sCursorPointLinks[oldCursorPoint].right;

                if (nextCursorPoint == CURSOR_TO_RIGHT) {
                    KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                    pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    return;
                }

                while (nextCursorPoint > CURSOR_NONE) {
                    if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, nextCursorPoint) != 0) {
                        break;
                    }
                    nextCursorPoint = sCursorPointLinks[nextCursorPoint].right;
                }
            }

            if (pauseCtx->stickAdjY < -30) {
                // Move cursor down
                if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
                nextCursorPoint = sCursorPointLinks[oldCursorPoint].down;

                while (nextCursorPoint > CURSOR_NONE) {
                    pauseCtx->cursorShrinkRate = 4.0f;
                    if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, nextCursorPoint) != 0) {
                        break;
                    }
                    nextCursorPoint = sCursorPointLinks[nextCursorPoint].down;
                }
            } else if (pauseCtx->stickAdjY > 30) {
                // Move cursor up
                if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
                nextCursorPoint = sCursorPointLinks[oldCursorPoint].up;
                while (nextCursorPoint > CURSOR_NONE) {
                    pauseCtx->cursorShrinkRate = 4.0f;
                    if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, nextCursorPoint) != 0) {
                        break;
                    }
                    nextCursorPoint = sCursorPointLinks[nextCursorPoint].up;
                }
            }

            // if the cursor point changed
            if (oldCursorPoint != pauseCtx->cursorPoint[PAUSE_QUEST]) {
                pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                play_sound(NA_SE_SY_CURSOR);
            }

            // Update cursor item and slot
            if (pauseCtx->cursorPoint[PAUSE_QUEST] != QUEST_HEART_PIECE) {
                if (pauseCtx->cursorPoint[PAUSE_QUEST] <= QUEST_REMAINS_TWINMOLD) {
                    // Boss Remains
                    if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                        cursorItem = ITEM_REMAINS_ODOLWA + pauseCtx->cursorPoint[PAUSE_QUEST];
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_BOMBERS_NOTEBOOK) {
                    // Bombers Notebook
                    if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                        cursorItem = ITEM_BOMBERS_NOTEBOOK;
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_SHIELD) {
                    // Shield
                    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD) != EQUIP_VALUE_SHIELD_NONE) {
                        cursorItem = (ITEM_SHIELD_HERO - EQUIP_TYPE_SHIELD) + GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD);
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_SWORD) {
                    // Sword
                    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) != EQUIP_VALUE_SWORD_NONE) {
                        cursorItem =
                            (ITEM_SWORD_KOKIRI - EQUIP_VALUE_SWORD_KOKIRI) + GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD);
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] <= QUEST_SONG_SUN) {
                    // Songs
                    if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                        cursorItem = ITEM_WALLET_GIANT + pauseCtx->cursorPoint[PAUSE_QUEST];
                    } else if ((pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_SONG_LULLABY) &&
                               CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
                        cursorItem = ITEM_SONG_LULLABY_INTRO;
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_QUIVER) {
                    // Quiver Upgrade
                    if (GET_CUR_UPG_VALUE(UPG_QUIVER) != 0) {
                        cursorItem = (ITEM_QUIVER_30 - 1) + GET_CUR_UPG_VALUE(UPG_QUIVER);
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_BOMB_BAG) {
                    // Bomb Bag Upgrade
                    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) != 0) {
                        cursorItem = (ITEM_BOMB_BAG_20 - 1) + GET_CUR_UPG_VALUE(UPG_BOMB_BAG);
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else {
                    cursorItem = PAUSE_ITEM_NONE;
                }
            } else {
                // Heart Piece Count
                if ((GET_SAVE_INVENTORY_QUEST_ITEMS >> QUEST_HEART_PIECE_COUNT) != 0) {
                    cursorItem = ITEM_HEART_CONTAINER;
                } else {
                    cursorItem = PAUSE_ITEM_NONE;
                }
            }

            cursor = pauseCtx->cursorPoint[PAUSE_QUEST];
            pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
            pauseCtx->cursorSlot[pauseCtx->pageIndex] = cursor;

            if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && (pauseCtx->state == PAUSE_STATE_MAIN) &&
                (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) && (pauseCtx->cursorSpecialPos == 0)) {
                if ((cursor >= QUEST_SONG_SONATA) && (cursor <= QUEST_SONG_SUN)) {
                    // Handle part of the ocarina songs playback
                    if ((CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST]) ||
                         ((cursor == QUEST_SONG_LULLABY) && !CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST]) &&
                          CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO))) &&
                        (msgCtx->msgLength == 0)) {
                        if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                            cursor = pauseCtx->cursorSlot[PAUSE_QUEST];
                        } else {
                            cursor = QUEST_BOMB_BAG;
                        }

                        pauseCtx->ocarinaSongIndex = gOcarinaSongItemMap[cursor - QUEST_SONG_SONATA];
                        D_8082B028 = 10;

                        for (i = 0; i < 8; i++) {
                            D_8082AEE4[i] = OCARINA_BTN_INVALID;
                            D_8082AEF0[i] = 0;
                        }

                        D_8082AEE0 = 0;
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
                        AudioOcarina_StartDefault((1 << pauseCtx->ocarinaSongIndex) | 0x80000000);
                        pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
                        pauseCtx->ocarinaStaff->pos = 0;
                        pauseCtx->ocarinaStaff->state = 0xFF;
                        pauseCtx->ocarinaButtonsY[OCARINA_BTN_A] = -62;
                        pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_DOWN] = -56;
                        pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_RIGHT] = -49;
                        pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_LEFT] = -46;
                        pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_UP] = -41;
                        pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG;

                        if (interfaceCtx->unk_212 != 6) {
                            func_8011552C(play, 6);
                        }

                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);

                        if (gSaveContext.buttonStatus[EQUIP_SLOT_A] == BTN_DISABLED) {
                            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
                            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
                            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
                        }
                    } else {
                        if (interfaceCtx->unk_212 != 6) {
                            func_8011552C(play, 6);
                        }
                        if (gSaveContext.buttonStatus[EQUIP_SLOT_A] != BTN_DISABLED) {
                            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
                            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
                            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
                        }
                    }
                } else {
                    if ((cursor == QUEST_BOMBERS_NOTEBOOK) && (pauseCtx->cursorItem[PAUSE_QUEST] != PAUSE_ITEM_NONE)) {
                        if (interfaceCtx->unk_212 != 6) {
                            func_8011552C(play, 6);
                        }
                        pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_BLUE;
                    } else if (interfaceCtx->unk_212 == 6) {
                        func_8011552C(play, 0x15);
                    }

                    if ((pauseCtx->cursorItem[PAUSE_QUEST] != PAUSE_ITEM_NONE) && (msgCtx->msgLength == 0)) {
                        if (gSaveContext.buttonStatus[EQUIP_SLOT_A] == BTN_DISABLED) {
                            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
                            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
                            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
                        }

                        if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) && (msgCtx->msgLength == 0)) {
                            if (pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_BOMBERS_NOTEBOOK) {
                                play->pauseCtx.bombersNotebookOpen = true;
                                pauseCtx->mainState = PAUSE_MAIN_STATE_BOMBERS_NOTEBOOK_OPEN;
                                play_sound(NA_SE_SY_DECIDE);
                            } else {
                                pauseCtx->itemDescriptionOn = true;
                                if (pauseCtx->cursorYIndex[PAUSE_QUEST] < 2) {
                                    if (pauseCtx->cursorItem[PAUSE_QUEST] < ITEM_REMAINS_ODOLWA) {
                                        func_801514B0(play, 0x1737 + pauseCtx->cursorItem[PAUSE_QUEST], 1);
                                    } else {
                                        func_801514B0(play, 0x173B + pauseCtx->cursorItem[PAUSE_QUEST], 3);
                                    }
                                } else {
                                    if (pauseCtx->cursorItem[PAUSE_QUEST] < ITEM_REMAINS_ODOLWA) {
                                        func_801514B0(play, 0x1737 + pauseCtx->cursorItem[PAUSE_QUEST], 1);
                                    } else {
                                        func_801514B0(play, 0x173B + pauseCtx->cursorItem[PAUSE_QUEST], 1);
                                    }
                                }
                            }
                        }
                    } else if (gSaveContext.buttonStatus[EQUIP_SLOT_A] != BTN_DISABLED) {
                        gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
                        gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
                        Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
                    }
                }
            } else if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) {
                // Abort having the player play the song if the stick is moved
                if ((pauseCtx->stickAdjX != 0) || (pauseCtx->stickAdjY != 0)) {
                    pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
            } else if ((pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG) &&
                       CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) && (msgCtx->msgLength == 0) &&
                       (cursor >= QUEST_SONG_SONATA) && (cursor <= QUEST_SONG_SUN)) {
                pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PLAYBACK_INIT;
                D_8082B028 = 10;
            }

            if (pauseCtx->cursorSpecialPos == 0) {
                if ((pauseCtx->cursorSlot[PAUSE_QUEST] >= 6) && (pauseCtx->cursorSlot[PAUSE_QUEST] < 0x12) &&
                    ((pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PLAYBACK) ||
                     (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) ||
                     (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG)) &&
                    (pauseCtx->cursorItem[pauseCtx->pageIndex] != PAUSE_ITEM_NONE)) {
                    pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_BLUE;
                    if ((pauseCtx->mainState >= PAUSE_MAIN_STATE_SONG_PLAYBACK) &&
                        (pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING_DONE)) {
                        pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_WHITE;
                    }
                }
            }
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            if (pauseCtx->stickAdjX > 30) {
                if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }

                func_80821A04(play);

                pauseCtx->cursorPoint[PAUSE_QUEST] = QUEST_BOMBERS_NOTEBOOK;
                if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                    cursorItem = ITEM_BOMBERS_NOTEBOOK;
                } else {
                    cursorItem = PAUSE_ITEM_NONE;
                }

                cursor = pauseCtx->cursorPoint[PAUSE_QUEST];
                pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
                pauseCtx->cursorSlot[pauseCtx->pageIndex] = cursor;
            }
        } else if (pauseCtx->stickAdjX < -30) {
            if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYER_PLAYING) {
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
            }

            func_80821A04(play);

            pauseCtx->cursorPoint[PAUSE_QUEST] = QUEST_REMAINS_GOHT;
            if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                cursorItem = (ITEM_REMAINS_GOHT - 1) + pauseCtx->cursorPoint[PAUSE_QUEST];
                if (pauseCtx->cursorPoint[PAUSE_QUEST] != QUEST_REMAINS_ODOWLA) {
                    // This condition is always true as `cursorPoint` is set three lines above
                    cursorItem = ITEM_MASK_GIANT;
                }
            } else {
                cursorItem = PAUSE_ITEM_NONE;
            }

            cursor = pauseCtx->cursorPoint[PAUSE_QUEST];
            pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
            pauseCtx->cursorSlot[pauseCtx->pageIndex] = cursor;
        }
    } else if (pauseCtx->mainState == PAUSE_MAIN_STATE_SONG_PLAYBACK_INIT) {
        pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_BLUE;
        D_8082B028--;
        if (D_8082B028 == 0) {
            for (i = 0; i < 8; i++) {
                D_8082AEE4[i] = OCARINA_BTN_INVALID;
                D_8082AEF0[i] = 0;
            }
            D_8082AEE0 = 0;

            pauseCtx->ocarinaButtonsY[OCARINA_BTN_A] = -62;
            pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_DOWN] = -56;
            pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_RIGHT] = -49;
            pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_LEFT] = -46;
            pauseCtx->ocarinaButtonsY[OCARINA_BTN_C_UP] = -41;

            if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                cursor = pauseCtx->cursorSlot[PAUSE_QUEST];
            } else {
                cursor = QUEST_BOMB_BAG;
            }

            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            pauseCtx->ocarinaSongIndex = gOcarinaSongItemMap[cursor - QUEST_SONG_SONATA];
            AudioOcarina_SetPlaybackSong(pauseCtx->ocarinaSongIndex + 1, 1);
            pauseCtx->mainState = PAUSE_MAIN_STATE_SONG_PLAYBACK;
            pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
            pauseCtx->ocarinaStaff->pos = 0;
        }
    }
}

s32 KaleidoScope_UpdateQuestStatusPoint(PauseContext* pauseCtx, s16 point) {
    pauseCtx->cursorPoint[PAUSE_QUEST] = point;

    return 1;
}
