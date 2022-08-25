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
s16 D_8082B024 = 1;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawQuestStatus.s")

void KaleidoScope_UpdateQuestCursor(PlayState* play) {
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
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s32 pad;
    s16 var_s0;
    s16 sp44;
    s16 var_v0;
    u16 temp_s0;
    u16 cursorItem;

    pauseCtx->nameColorSet = 0;
    pauseCtx->cursorColorSet = 0;

    if ((pauseCtx->state == PAUSE_STATE_6) &&
        (!pauseCtx->unk_200 || (pauseCtx->unk_200 == 5) || (pauseCtx->unk_200 == 8)) &&
        (pauseCtx->pageIndex == PAUSE_QUEST) && !pauseCtx->itemDescriptionOn) {
        if (pauseCtx->cursorSpecialPos == 0) {
            sp44 = pauseCtx->cursorPoint[PAUSE_QUEST];

            if (pauseCtx->stickRelX < -30) {
                if (pauseCtx->unk_200 == 5) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
                pauseCtx->cursorShrinkRate = 4.0f;

                var_s0 = D_8082B02C[sp44][2];
                if (var_s0 == -3) {
                    KaleidoScope_MoveCursorToSpecialPos(play, 0xA);
                    pauseCtx->unk_200 = 0;
                    if (interfaceCtx->unk_212 == 6) {
                        func_8011552C(play, 0x15);
                    }
                    return;
                } else {
                    while (var_s0 >= 0) {
                        if (KaleidoScope_UpdateQuestStatusPoint(pauseCtx, var_s0) != 0) {
                            break;
                        }
                        var_s0 = D_8082B02C[var_s0][2];
                    }
                }
            } else if (pauseCtx->stickRelX > 30) {
                if (pauseCtx->unk_200 == 5) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
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
            }

            if (pauseCtx->stickRelY < -30) {
                if (pauseCtx->unk_200 == 5) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
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
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
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

            if (sp44 != pauseCtx->cursorPoint[PAUSE_QUEST]) {
                pauseCtx->unk_200 = 0;
                play_sound(NA_SE_SY_CURSOR);
            }

            if (pauseCtx->cursorPoint[PAUSE_QUEST] != 0x16) {
                if (pauseCtx->cursorPoint[PAUSE_QUEST] < 4) {
                    if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                        cursorItem = ITEM_REMAINS_ODOLWA + pauseCtx->cursorPoint[PAUSE_QUEST];
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == QUEST_BOMBERS_NOTEBOOK) {
                    if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                        cursorItem = ITEM_BOMBERS_NOTEBOOK;
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == 4) {
                    if (GET_CUR_EQUIP_VALUE(1) != 0) {
                        cursorItem = (ITEM_SHIELD_HERO - 1) + GET_CUR_EQUIP_VALUE(1);
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == 5) {
                    if (GET_CUR_EQUIP_VALUE(0) != 0) {
                        cursorItem = (ITEM_SWORD_KOKIRI - 1) + GET_CUR_EQUIP_VALUE(0);
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] < 0x12) {
                    if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                        cursorItem = ITEM_WALLET_GIANT + pauseCtx->cursorPoint[PAUSE_QUEST];
                    } else if ((pauseCtx->cursorPoint[PAUSE_QUEST] == 7) &&
                               CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
                        cursorItem = ITEM_SONG_LULLABY_INTRO;
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == 0x13) {
                    if (GET_CUR_UPG_VALUE(0) != 0) {
                        cursorItem = GET_CUR_UPG_VALUE(0) + 0x52;
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else if (pauseCtx->cursorPoint[PAUSE_QUEST] == 0x14) {
                    if (GET_CUR_UPG_VALUE(1) != 0) {
                        cursorItem = GET_CUR_UPG_VALUE(1) + 0x55;
                    } else {
                        cursorItem = PAUSE_ITEM_NONE;
                    }
                } else {
                    cursorItem = PAUSE_ITEM_NONE;
                }
            } else {
                if ((GET_SAVE_INVENTORY_QUEST_ITEMS >> QUEST_HEART_PIECE_COUNT) != 0) {
                    cursorItem = ITEM_HEART_CONTAINER;
                } else {
                    cursorItem = PAUSE_ITEM_NONE;
                }
            }

            temp_s0 = pauseCtx->cursorPoint[PAUSE_QUEST];
            pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
            pauseCtx->cursorSlot[pauseCtx->pageIndex] = temp_s0;

            if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && (pauseCtx->state == PAUSE_STATE_6) &&
                (pauseCtx->unk_200 == 0) && (pauseCtx->cursorSpecialPos == 0)) {
                if ((temp_s0 >= QUEST_SONG_SONATA) && (temp_s0 <= QUEST_SONG_SUN)) {
                    if ((CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST]) ||
                         ((temp_s0 == 7) && !CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST]) &&
                          CHECK_QUEST_ITEM(0x18))) &&
                        (msgCtx->msgLength == 0)) {
                        if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                            temp_s0 = pauseCtx->cursorSlot[PAUSE_QUEST];
                        } else {
                            temp_s0 = 0x14;
                        }

                        pauseCtx->unk_2A0 = gOcarinaSongItemMap[temp_s0 - QUEST_SONG_SONATA];
                        D_8082B028 = 10;

                        for (var_v0 = 0; var_v0 < 8; var_v0++) {
                            D_8082AEE4[var_v0] = 0xFF;
                            D_8082AEF0[var_v0] = 0;
                        }

                        D_8082AEE0 = 0;
                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
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

                        if (interfaceCtx->unk_212 != 6) {
                            func_8011552C(play, 6);
                        }

                        AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);

                        if (gSaveContext.buttonStatus[EQUIP_SLOT_A] == BTN_DISABLED) {
                            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
                            gSaveContext.unk_3F22 = 0;
                            Interface_ChangeAlpha(50);
                        }
                    } else {
                        if (interfaceCtx->unk_212 != 6) {
                            func_8011552C(play, 6);
                        }
                        if (gSaveContext.buttonStatus[EQUIP_SLOT_A] != BTN_DISABLED) {
                            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
                            gSaveContext.unk_3F22 = 0;
                            Interface_ChangeAlpha(50);
                        }
                    }
                } else {
                    if ((temp_s0 == 0x12) && (pauseCtx->cursorItem[PAUSE_QUEST] != PAUSE_ITEM_NONE)) {
                        if (interfaceCtx->unk_212 != 6) {
                            func_8011552C(play, 6);
                        }
                        pauseCtx->cursorColorSet = 4;
                    } else if (interfaceCtx->unk_212 == 6) {
                        func_8011552C(play, 0x15);
                    }

                    if ((pauseCtx->cursorItem[PAUSE_QUEST] != PAUSE_ITEM_NONE) && (msgCtx->msgLength == 0)) {
                        if (gSaveContext.buttonStatus[EQUIP_SLOT_A] == BTN_DISABLED) {
                            gSaveContext.buttonStatus[EQUIP_SLOT_A] = 0;
                            gSaveContext.unk_3F22 = 0;
                            Interface_ChangeAlpha(50);
                        }
                        if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) && (msgCtx->msgLength == 0)) {
                            if (pauseCtx->cursorPoint[PAUSE_QUEST] == 0x12) {
                                play->pauseCtx.unk_1F0 = 1;
                                pauseCtx->unk_200 = 0x10;
                                play_sound(0x4808U);
                            } else {
                                pauseCtx->itemDescriptionOn = true;
                                if (pauseCtx->cursorYIndex[PAUSE_QUEST] < 2) {
                                    if (pauseCtx->cursorItem[PAUSE_QUEST] < ITEM_REMAINS_ODOLWA) {
                                        func_801514B0(play, pauseCtx->cursorItem[PAUSE_QUEST] + 0x1737, 1);
                                    } else {
                                        func_801514B0(play, pauseCtx->cursorItem[PAUSE_QUEST] + 0x173B, 3);
                                    }
                                } else {
                                    if (pauseCtx->cursorItem[PAUSE_QUEST] < ITEM_REMAINS_ODOLWA) {
                                        func_801514B0(play, pauseCtx->cursorItem[PAUSE_QUEST] + 0x1737, 1);
                                    } else {
                                        func_801514B0(play, pauseCtx->cursorItem[PAUSE_QUEST] + 0x173B, 1);
                                    }
                                }
                            }
                        }
                    } else if (gSaveContext.buttonStatus[EQUIP_SLOT_A] != BTN_DISABLED) {
                        gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
                        gSaveContext.unk_3F22 = 0;
                        Interface_ChangeAlpha(50);
                    }
                }
            } else if (pauseCtx->unk_200 == 5) {
                if ((pauseCtx->stickRelX != 0) || (pauseCtx->stickRelY != 0)) {
                    pauseCtx->unk_200 = 0;
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }
            } else if ((pauseCtx->unk_200 == 8) && CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) &&
                       (msgCtx->msgLength == 0) && (temp_s0 >= 6) && (temp_s0 < 0x12)) {
                pauseCtx->unk_200 = 9;
                D_8082B028 = 10;
            }

            if (pauseCtx->cursorSpecialPos == 0) {
                if ((pauseCtx->cursorSlot[PAUSE_QUEST] >= 6) && (pauseCtx->cursorSlot[PAUSE_QUEST] < 0x12) &&
                    ((pauseCtx->unk_200 < 3) || (pauseCtx->unk_200 == 5) || (pauseCtx->unk_200 == 8)) &&
                    (pauseCtx->cursorItem[pauseCtx->pageIndex] != PAUSE_ITEM_NONE)) {
                    pauseCtx->cursorColorSet = 4;
                    if ((pauseCtx->unk_200 >= 2) && (pauseCtx->unk_200 < 7)) {
                        pauseCtx->cursorColorSet = 0;
                    }
                }
            }
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            if (pauseCtx->stickRelX > 30) {
                if (pauseCtx->unk_200 == 5) {
                    AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
                }

                func_80821A04(play);

                pauseCtx->cursorPoint[PAUSE_QUEST] = QUEST_BOMBERS_NOTEBOOK;
                if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                    cursorItem = ITEM_BOMBERS_NOTEBOOK;
                } else {
                    cursorItem = PAUSE_ITEM_NONE;
                }

                temp_s0 = pauseCtx->cursorPoint[PAUSE_QUEST];
                pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
                pauseCtx->cursorSlot[pauseCtx->pageIndex] = temp_s0;
            }
        } else if (pauseCtx->stickRelX < -30) {
            if (pauseCtx->unk_200 == 5) {
                AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_OFF);
            }

            func_80821A04(play);

            pauseCtx->cursorPoint[PAUSE_QUEST] = 1;
            if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                cursorItem = pauseCtx->cursorPoint[PAUSE_QUEST] + 0x5D;
                if (pauseCtx->cursorPoint[PAUSE_QUEST] != 0) {
                    cursorItem = ITEM_MASK_GIANT;
                }
            } else {
                cursorItem = PAUSE_ITEM_NONE;
            }

            temp_s0 = pauseCtx->cursorPoint[PAUSE_QUEST];
            pauseCtx->cursorItem[pauseCtx->pageIndex] = cursorItem;
            pauseCtx->cursorSlot[pauseCtx->pageIndex] = temp_s0;
        }
    } else if (pauseCtx->unk_200 == 9) {
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

            if (CHECK_QUEST_ITEM(pauseCtx->cursorPoint[PAUSE_QUEST])) {
                temp_s0 = pauseCtx->cursorSlot[PAUSE_QUEST];
            } else {
                temp_s0 = 0x14;
            }

            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            AudioOcarina_SetInstrument(OCARINA_INSTRUMENT_DEFAULT);
            pauseCtx->unk_2A0 = gOcarinaSongItemMap[temp_s0 - QUEST_SONG_SONATA];
            AudioOcarina_SetPlaybackSong(pauseCtx->unk_2A0 + 1, 1);
            pauseCtx->unk_200 = 2;
            pauseCtx->ocarinaStaff = AudioOcarina_GetPlaybackStaff();
            pauseCtx->ocarinaStaff->pos = 0;
        }
    }
}

s32 KaleidoScope_UpdateQuestStatusPoint(PauseContext* pauseCtx, s16 point) {
    pauseCtx->cursorPoint[PAUSE_QUEST] = point;

    return 1;
}
