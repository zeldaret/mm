/*
 * File: z_kaleido_collect.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu - Quest Page
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

s32 KaleidoScope_UpdateQuestStatusPoint(PauseContext* pauseCtx, s16 point);

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

s16 D_8082AED0[] = { 120, 60, 2, 80 };

s16 D_8082AED8[] = { 20, 4, 20, 10 };

s16 D_8082AEE0 = 0;

u8 D_8082AEE4[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 D_8082AEF0[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// OoT D_8082A070
s16 D_8082AF04[][4] = {
    { 255, 0, 0, 255 },
    { 255, 70, 0, 150 },
    { 255, 70, 0, 150 },
    { 255, 0, 0, 255 },
};
// OoT D_8082A090
s16 D_8082AF24[][3] = {
    { 0, 0, 0 },  { 0, 0, 0 },  { 0, 0, 0 },    { 0, 0, 0 },   { 0, 0, 0 },   { 0, 0, 0 },
    { 0, 60, 0 }, { 90, 0, 0 }, { 0, 40, 110 }, { 80, 40, 0 }, { 70, 0, 90 }, { 90, 90, 0 },
};
// OoT D_8082A0D8
s16 D_8082AF6C[] = {
    255, 255, 255, 255, 255, 255,
};
// OoT D_8082A0E4
s16 D_8082AF78[] = {
    255, 255, 255, 255, 255, 255,
};
// OoT D_8082A0F0
s16 D_8082AF84[] = {
    150, 150, 150, 150, 150, 150,
};
s16 D_8082AF90 = 20;
s16 D_8082AF94 = 0;
s16 D_8082AF98 = 0;
s16 D_8082AF9C = 0;
s16 D_8082AFA0 = 0;
s16 D_8082AFA4 = 0;
s16 D_8082AFA8 = 20;
s16 D_8082AFAC = 0;

// OoT D_8082A130
TexturePtr D_8082AFB0[] = {
    gOcarinaATex, gOcarinaCDownTex, gOcarinaCRightTex, gOcarinaCLeftTex, gOcarinaCUpTex,
};

// OoT D_8082A164
s16 D_8082AFC4[] = {
    150, 255, 100, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};

// OoT D_8082A17C
s16 D_8082AFDC[] = {
    255, 80, 150, 160, 100, 240, 255, 255, 255, 255, 255, 255,
};

// OoT D_8082A194
s16 D_8082AFF4[] = {
    100, 40, 255, 0, 255, 100, 255, 255, 255, 255, 255, 255,
};

void* D_8082B00C[] = {
    0x08053000, 0x08054000, 0x08055000, 0x08056000, 0x08057000, 0x08058000,
};

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawQuestStatus.s")

#ifdef NON_EQUIVALENT
void KaleidoScope_UpdateQuestCursor(PlayState* play) {
    static s16 D_8082B024 = 1;
    static s16 D_8082B028 = 0;
    static s16 D_8082B02C[][4] = {
        { -1, 3, 2, 1 },   { 0, 4, 3, -2 },    { 0, 5, 22, 3 },   { 0, 4, 2, 1 },     { 1, 20, 5, -2 },
        { 2, 19, 16, 4 },  { 12, -1, -3, 7 },  { 13, -1, 6, 8 },  { 14, -1, 7, 9 },   { 15, -1, 8, 10 },
        { 16, -1, 9, 19 }, { 17, -1, 10, 5 },  { 18, 6, -3, 13 }, { 18, 7, 12, 14 },  { 22, 8, 13, 15 },
        { 22, 9, 14, 16 }, { 22, 10, 15, 5 },  { 22, 11, 16, 5 }, { -1, 12, -3, 22 }, { 5, -1, 10, 20 },
        { 4, -1, 19, -2 }, { 19, 12, -3, 22 }, { -1, 16, 18, 2 },
    };
    PauseContext* pauseCtx = &play->pauseCtx;
    MessageContext* msgCtx = &play->msgCtx;

    s16 sp44;
    s16 var_s0;
    s16 var_v0;
    u16 temp_s0;
    u16 var_s0_6;
    u16 cursorItem;
    s32 pad;

    play->pauseCtx.nameColorSet = 0;
    play->pauseCtx.cursorColorSet = 0;

    if ((play->pauseCtx.state == 6) &&
        ((pauseCtx->unk_200 == 0) || (pauseCtx->unk_200 == 5) || (pauseCtx->unk_200 == 8)) &&
        (pauseCtx->pageIndex == 2) && (pauseCtx->itemDescriptionOn == 0)) {
        if (pauseCtx->cursorSpecialPos == 0) {
            sp44 = pauseCtx->cursorPoint[2];

            if (pauseCtx->stickRelX < -30) {
                if (pauseCtx->unk_200 == 5) {
                    AudioOcarina_SetInstrument(0);
                }
                pauseCtx->cursorShrinkRate = 4.0f;

                var_s0 = D_8082B02C[sp44][2];
                if (var_s0 == -3) {
                    KaleidoScope_MoveCursorToSpecialPos(play, 0xA);
                    pauseCtx->unk_200 = 0;
                    if (play->interfaceCtx.unk_212 == 6) {
                        func_8011552C(play, 0x15);
                    }
                } else {
                    while (var_s0 >= 0) {
                        if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, var_s0) != 0) {
                            break;
                        }
                        var_s0 = D_8082B02C[var_s0][2];
                    }
                    goto block_26;
                }
            } else {
                if (pauseCtx->stickRelX >= 30) {
                    if (pauseCtx->unk_200 == 5) {
                        AudioOcarina_SetInstrument(0);
                    }
                    pauseCtx->cursorShrinkRate = 4.0f;
                    var_s0 = D_8082B02C[sp44][3];
                    if (var_s0 == -2) {
                        KaleidoScope_MoveCursorToSpecialPos(play, 0xB);
                        pauseCtx->unk_200 = 0;
                        return;
                    }
                    while (var_s0 >= 0) {
                        if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, var_s0) != 0) {
                            break;
                        }
                        var_s0 = D_8082B02C[var_s0][3];
                    }
                    goto block_26;
                }
            block_26:
                if (pauseCtx->stickRelY < -30) {
                    if (pauseCtx->unk_200 == 5) {
                        AudioOcarina_SetInstrument(0);
                    }
                    var_s0 = D_8082B02C[sp44][1];
                    while (var_s0 >= 0) {
                        pauseCtx->cursorShrinkRate = 4.0f;
                        if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, var_s0) != 0) {
                            break;
                        }
                        var_s0 = D_8082B02C[var_s0][1];
                    }
                } else if (pauseCtx->stickRelY > 30) {
                    if (pauseCtx->unk_200 == 5) {
                        AudioOcarina_SetInstrument(0);
                    }
                    var_s0 = D_8082B02C[sp44][0];
                    while (var_s0 >= 0) {
                        pauseCtx->cursorShrinkRate = 4.0f;
                        if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, var_s0) != 0) {
                            break;
                        }
                        var_s0 = D_8082B02C[var_s0][0];
                    }
                }

                if (sp44 != pauseCtx->cursorPoint[2]) {
                    pauseCtx->unk_200 = 0;
                    play_sound(0x4809U);
                }
                if (pauseCtx->cursorPoint[2] != 0x16) {
                    if (pauseCtx->cursorPoint[2] < 4) {
                        if (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) {
                            cursorItem = pauseCtx->cursorPoint[2] + 0x5D;
                        } else {
                            cursorItem = 0x3E7;
                        }
                    } else if (pauseCtx->cursorPoint[2] == 0x12) {
                        if (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) {
                            cursorItem = 0x6D;
                        } else {
                            cursorItem = 0x3E7;
                        }
                    } else if (pauseCtx->cursorPoint[2] == 4) {
                        cursorItem = 0x3E7;
                        if (GET_CUR_EQUIP_VALUE(1) != 0) {
                            cursorItem = GET_CUR_EQUIP_VALUE(1) + 0x50;
                        }
                    } else if (pauseCtx->cursorPoint[2] == 5) {
                        cursorItem = 0x3E7;
                        if (GET_CUR_EQUIP_VALUE(0) != 0) {
                            cursorItem = GET_CUR_EQUIP_VALUE(0) + 0x4C;
                        }
                    } else if (pauseCtx->cursorPoint[2] < 0x12) {
                        if (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) {
                            cursorItem = (pauseCtx->cursorPoint[2] + 0x5B) & 0xFFFF;
                        } else if ((pauseCtx->cursorPoint[2] == 7) &&
                                   (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[24])) {
                            cursorItem = 0x73;
                        } else {
                            cursorItem = 0x3E7;
                        }
                    } else if (pauseCtx->cursorPoint[2] == 0x13) {
                        cursorItem = 0x3E7;
                        if (GET_CUR_UPG_VALUE(0) != 0) {
                            cursorItem = GET_CUR_UPG_VALUE(0) + 0x52;
                        }
                    } else if (pauseCtx->cursorPoint[2] == 0x14) {
                        cursorItem = 0x3E7;
                        if (GET_CUR_UPG_VALUE(1) != 0) {
                            cursorItem = GET_CUR_UPG_VALUE(1) + 0x55;
                        }
                    } else {
                        cursorItem = 0x3E7;
                    }
                } else {
                    cursorItem = 0x3E7;
                    if ((GET_SAVE_INVENTORY_QUEST_ITEMS >> QUEST_HEART_PIECE_COUNT) != 0) {
                        cursorItem = 0x6F;
                    }
                }

                temp_s0 = pauseCtx->cursorPoint[2];
                pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
                pauseCtx->cursorSlot[pauseCtx->pageIndex] = temp_s0;

                if ((pauseCtx->debugEditor == 0) && (pauseCtx->state == 6) && (pauseCtx->unk_200 == 0) &&
                    (pauseCtx->cursorSpecialPos == 0)) {
                    if ((temp_s0 >= 6) && (temp_s0 < 0x12)) {
                        if (((GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) ||
                             ((temp_s0 == 7) &&
                              !(GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) &&
                              (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[24]))) &&
                            (msgCtx->msgLength == 0)) {
                            if (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) {
                                var_s0 = pauseCtx->cursorSlot[2];
                            } else {
                                var_s0 = 0x14;
                            }
                            pauseCtx->unk_2A0 = D_801CFCB8[var_s0 - QUEST_SONG_SONATA];
                            D_8082B028 = 0xA;

                            for (var_v0 = 0; var_v0 < 8; var_v0++) {
                                D_8082AEE4[var_v0] = 0xFF;
                                D_8082AEF0[var_v0] = 0;
                            }

                            D_8082AEE0 = 0;
                            AudioOcarina_SetInstrument(1);
                            AudioOcarina_StartDefault((1 << pauseCtx->unk_2A0) | 0x80000000);
                            pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
                            pauseCtx->ocarinaStaff->pos = 0;
                            pauseCtx->ocarinaStaff->state = 0xFF;
                            pauseCtx->unk_2BE[0] = -62;
                            pauseCtx->unk_2BE[1] = -56;
                            pauseCtx->unk_2BE[2] = -49;
                            pauseCtx->unk_2BE[3] = -46;
                            pauseCtx->unk_2BE[4] = -41;
                            pauseCtx->unk_200 = 8;

                            if (play->interfaceCtx.unk_212 != 6) {
                                func_8011552C(play, 6);
                            }

                            AudioOcarina_SetInstrument(0);

                            if (gSaveContext.buttonStatus[4] == 0xFF) {
                                gSaveContext.buttonStatus[4] = 0;
                                gSaveContext.unk_3F22 = 0;
                                Interface_ChangeAlpha(50);
                            }
                        } else {
                            if (play->interfaceCtx.unk_212 != 6) {
                                func_8011552C(play, 6);
                            }
                            if (gSaveContext.buttonStatus[4] != 0xFF) {
                                gSaveContext.buttonStatus[4] = 0xFF;
                                gSaveContext.unk_3F22 = 0;
                                Interface_ChangeAlpha(50);
                            }
                        }
                    } else {
                        if ((temp_s0 == 0x12) && (pauseCtx->cursorItem[2] != 0x3E7)) {
                            if (play->interfaceCtx.unk_212 != 6) {
                                func_8011552C(play, 6);
                            }
                            pauseCtx->cursorColorSet = 4;
                        } else if (play->interfaceCtx.unk_212 == 6) {
                            func_8011552C(play, 0x15);
                        }
                        if ((pauseCtx->cursorItem[2] != 0x3E7) && (msgCtx->msgLength == 0)) {
                            if (gSaveContext.buttonStatus[4] == 0xFF) {
                                gSaveContext.buttonStatus[4] = 0;
                                gSaveContext.unk_3F22 = 0;
                                Interface_ChangeAlpha(50);
                            }
                            if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) &&
                                (msgCtx->msgLength == 0)) {
                                if (pauseCtx->cursorPoint[2] == 0x12) {
                                    play->pauseCtx.unk_1F0 = 1;
                                    pauseCtx->unk_200 = 0x10;
                                    play_sound(0x4808U);
                                } else {
                                    pauseCtx->itemDescriptionOn = true;
                                    if (pauseCtx->cursorYIndex[2] < 2) {
                                        if (pauseCtx->cursorItem[2] < 0x5D) {
                                            func_801514B0(play, pauseCtx->cursorItem[2] + 0x1737, 1);
                                        } else {
                                            func_801514B0(play, pauseCtx->cursorItem[2] + 0x173B, 3);
                                        }
                                    } else {
                                        if (pauseCtx->cursorItem[2] < 0x5D) {
                                            func_801514B0(play, pauseCtx->cursorItem[2] + 0x1737, 1);
                                        } else {
                                            func_801514B0(play, pauseCtx->cursorItem[2] + 0x173B, 1);
                                        }
                                    }
                                }
                            }
                        } else if (gSaveContext.buttonStatus[4] != 0xFF) {
                            gSaveContext.buttonStatus[4] = 0xFF;
                            gSaveContext.unk_3F22 = 0;
                            Interface_ChangeAlpha(50);
                        }
                    }
                } else {
                    if (pauseCtx->unk_200 == 5) {
                        if ((pauseCtx->stickRelX != 0) || (pauseCtx->stickRelY != 0)) {
                            pauseCtx->unk_200 = 0;
                            AudioOcarina_SetInstrument(0);
                        }
                    } else if ((pauseCtx->unk_200 == 8) &&
                               CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) &&
                               (msgCtx->msgLength == 0) && (temp_s0 >= 6) && (temp_s0 < 0x12)) {
                        pauseCtx->unk_200 = 9;
                        D_8082B028 = 0xA;
                    }
                }
                if (pauseCtx->cursorSpecialPos == 0) {
                    if ((pauseCtx->cursorSlot[2] >= 6) && (pauseCtx->cursorSlot[2] < 0x12) &&
                        (((pauseCtx->unk_200 < 3) != 0) || (pauseCtx->unk_200 == 5) || (pauseCtx->unk_200 == 8)) &&
                        (pauseCtx->cursorItem[pauseCtx->pageIndex] != 0x3E7)) {
                        pauseCtx->cursorColorSet = 4;
                        if ((pauseCtx->unk_200 >= 2) && (pauseCtx->unk_200 < 7)) {
                            pauseCtx->cursorColorSet = 0;
                        }
                    }
                }
            }
        } else if (pauseCtx->cursorSpecialPos == 0xA) {
            if (pauseCtx->stickRelX > 30) {
                if (pauseCtx->unk_200 == 5) {
                    AudioOcarina_SetInstrument(0);
                }
                func_80821A04(play);
                pauseCtx->cursorPoint[2] = 0x12;
                cursorItem = 0x3E7;
                if (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[18]) {
                    cursorItem = 0x6D;
                }
                pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
                pauseCtx->cursorSlot[pauseCtx->pageIndex] = (u16)pauseCtx->cursorPoint[2];
            }
        } else if (pauseCtx->stickRelX < -30) {
            if (pauseCtx->unk_200 == 5) {
                AudioOcarina_SetInstrument(0);
            }
            func_80821A04(play);
            pauseCtx->cursorPoint[2] = 1;
            cursorItem = 0x3E7;
            if (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) {
                cursorItem = pauseCtx->cursorPoint[2] + 0x5D;
                if (pauseCtx->cursorPoint[2] != 0) {
                    cursorItem = 0x49;
                }
            }
            pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
            pauseCtx->cursorSlot[pauseCtx->pageIndex] = pauseCtx->cursorPoint[2];
        }
    } else {
        if (pauseCtx->unk_200 == 9) {
            pauseCtx->cursorColorSet = 4;
            D_8082B028--;
            if (D_8082B028 == 0) {
                for (var_v0 = 0; var_v0 < 8; var_v0++) {
                    D_8082AEE4[var_v0] = 0xFF;
                    D_8082AEF0[var_v0] = 0;
                }
                D_8082AEE0 = 0;
                pauseCtx->unk_2BE[0] = -62;
                pauseCtx->unk_2BE[1] = -56;
                pauseCtx->unk_2BE[2] = -49;
                pauseCtx->unk_2BE[3] = -46;
                pauseCtx->unk_2BE[4] = -41;
                var_s0_6 = 0x14;
                if (GET_SAVE_INVENTORY_QUEST_ITEMS & gBitFlags[pauseCtx->cursorPoint[2]]) {
                    var_s0_6 = pauseCtx->cursorSlot[2];
                }
                AudioOcarina_SetInstrument(1U);
                AudioOcarina_SetInstrument(1U);
                // gOcarinaSongItemMap
                pauseCtx->unk_2A0 = D_801CFCB8[var_s0_6 - QUEST_SONG_SONATA];
                AudioOcarina_SetPlaybackSong(pauseCtx->unk_2A0 + 1, 1);
                pauseCtx->unk_200 = 2;
                pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
                pauseCtx->ocarinaStaff->pos = 0;
            }
        }
    }
}
#else
s16 D_8082B024 = 1;
s16 D_8082B028 = 0;
s16 D_8082B02C[][4] = {
    { -1, 3, 2, 1 },    { 0, 4, 3, -2 },   { 0, 5, 22, 3 },   { 0, 4, 2, 1 },     { 1, 20, 5, -2 },  { 2, 19, 16, 4 },
    { 12, -1, -3, 7 },  { 13, -1, 6, 8 },  { 14, -1, 7, 9 },  { 15, -1, 8, 10 },  { 16, -1, 9, 19 }, { 17, -1, 10, 5 },
    { 18, 6, -3, 13 },  { 18, 7, 12, 14 }, { 22, 8, 13, 15 }, { 22, 9, 14, 16 },  { 22, 10, 15, 5 }, { 22, 11, 16, 5 },
    { -1, 12, -3, 22 }, { 5, -1, 10, 20 }, { 4, -1, 19, -2 }, { 19, 12, -3, 22 }, { -1, 16, 18, 2 },
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateQuestCursor.s")
#endif

s32 KaleidoScope_UpdateQuestStatusPoint(PauseContext* pauseCtx, s16 point) {
    pauseCtx->cursorPoint[PAUSE_QUEST] = point;

    return 1;
}
