/*
 * File: z_kaleido_mask.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu - Mask Page
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

s16 sMaskEquipState = EQUIP_STATE_MAGIC_ARROW_GROW_ORB;

// Timer to hold magic arrow icon over magic arrow slot before moving when equipping.
s16 sMaskEquipMagicArrowSlotHoldTimer = 0;

// Number of frames to move icon from slot to target position when equipping.
s16 sMaskEquipAnimTimer = 10;

u8 gMaskPlayerFormSlotRestrictions[PLAYER_FORM_MAX][NUM_MASK_SLOTS] = {
    // Fierce Deity
    {
        false, // SLOT_MASK_POSTMAN
        false, // SLOT_MASK_ALL_NIGHT
        false, // SLOT_MASK_BLAST
        false, // SLOT_MASK_STONE
        false, // SLOT_MASK_GREAT_FAIRY
        false, // SLOT_MASK_DEKU
        false, // SLOT_MASK_KEATON
        false, // SLOT_MASK_BREMEN
        false, // SLOT_MASK_BUNNY
        false, // SLOT_MASK_DON_GERO
        false, // SLOT_MASK_SCENTS
        false, // SLOT_MASK_GORON
        false, // SLOT_MASK_ROMANI
        false, // SLOT_MASK_CIRCUS_LEADER
        false, // SLOT_MASK_KAFEIS_MASK
        false, // SLOT_MASK_COUPLE
        false, // SLOT_MASK_TRUTH
        false, // SLOT_MASK_ZORA
        false, // SLOT_MASK_KAMARO
        false, // SLOT_MASK_GIBDO
        false, // SLOT_MASK_GARO
        false, // SLOT_MASK_CAPTAIN
        false, // SLOT_MASK_GIANT
        true,  // SLOT_MASK_FIERCE_DEITY
    },
    // Goron
    {
        false, // SLOT_MASK_POSTMAN
        false, // SLOT_MASK_ALL_NIGHT
        false, // SLOT_MASK_BLAST
        false, // SLOT_MASK_STONE
        false, // SLOT_MASK_GREAT_FAIRY
        true,  // SLOT_MASK_DEKU
        false, // SLOT_MASK_KEATON
        false, // SLOT_MASK_BREMEN
        false, // SLOT_MASK_BUNNY
        false, // SLOT_MASK_DON_GERO
        false, // SLOT_MASK_SCENTS
        true,  // SLOT_MASK_GORON
        false, // SLOT_MASK_ROMANI
        false, // SLOT_MASK_CIRCUS_LEADER
        false, // SLOT_MASK_KAFEIS_MASK
        false, // SLOT_MASK_COUPLE
        false, // SLOT_MASK_TRUTH
        true,  // SLOT_MASK_ZORA
        false, // SLOT_MASK_KAMARO
        false, // SLOT_MASK_GIBDO
        false, // SLOT_MASK_GARO
        false, // SLOT_MASK_CAPTAIN
        false, // SLOT_MASK_GIANT
        true,  // SLOT_MASK_FIERCE_DEITY
    },
    // Zora
    {
        false, // SLOT_MASK_POSTMAN
        false, // SLOT_MASK_ALL_NIGHT
        false, // SLOT_MASK_BLAST
        false, // SLOT_MASK_STONE
        false, // SLOT_MASK_GREAT_FAIRY
        true,  // SLOT_MASK_DEKU
        false, // SLOT_MASK_KEATON
        false, // SLOT_MASK_BREMEN
        false, // SLOT_MASK_BUNNY
        false, // SLOT_MASK_DON_GERO
        false, // SLOT_MASK_SCENTS
        true,  // SLOT_MASK_GORON
        false, // SLOT_MASK_ROMANI
        false, // SLOT_MASK_CIRCUS_LEADER
        false, // SLOT_MASK_KAFEIS_MASK
        false, // SLOT_MASK_COUPLE
        false, // SLOT_MASK_TRUTH
        true,  // SLOT_MASK_ZORA
        false, // SLOT_MASK_KAMARO
        false, // SLOT_MASK_GIBDO
        false, // SLOT_MASK_GARO
        false, // SLOT_MASK_CAPTAIN
        false, // SLOT_MASK_GIANT
        true,  // SLOT_MASK_FIERCE_DEITY
    },
    // Deku
    {
        false, // SLOT_MASK_POSTMAN
        false, // SLOT_MASK_ALL_NIGHT
        false, // SLOT_MASK_BLAST
        false, // SLOT_MASK_STONE
        false, // SLOT_MASK_GREAT_FAIRY
        true,  // SLOT_MASK_DEKU
        false, // SLOT_MASK_KEATON
        false, // SLOT_MASK_BREMEN
        false, // SLOT_MASK_BUNNY
        false, // SLOT_MASK_DON_GERO
        false, // SLOT_MASK_SCENTS
        true,  // SLOT_MASK_GORON
        false, // SLOT_MASK_ROMANI
        false, // SLOT_MASK_CIRCUS_LEADER
        false, // SLOT_MASK_KAFEIS_MASK
        false, // SLOT_MASK_COUPLE
        false, // SLOT_MASK_TRUTH
        true,  // SLOT_MASK_ZORA
        false, // SLOT_MASK_KAMARO
        false, // SLOT_MASK_GIBDO
        false, // SLOT_MASK_GARO
        false, // SLOT_MASK_CAPTAIN
        false, // SLOT_MASK_GIANT
        true,  // SLOT_MASK_FIERCE_DEITY
    },
    // Human
    {
        true, // SLOT_MASK_POSTMAN
        true, // SLOT_MASK_ALL_NIGHT
        true, // SLOT_MASK_BLAST
        true, // SLOT_MASK_STONE
        true, // SLOT_MASK_GREAT_FAIRY
        true, // SLOT_MASK_DEKU
        true, // SLOT_MASK_KEATON
        true, // SLOT_MASK_BREMEN
        true, // SLOT_MASK_BUNNY
        true, // SLOT_MASK_DON_GERO
        true, // SLOT_MASK_SCENTS
        true, // SLOT_MASK_GORON
        true, // SLOT_MASK_ROMANI
        true, // SLOT_MASK_CIRCUS_LEADER
        true, // SLOT_MASK_KAFEIS_MASK
        true, // SLOT_MASK_COUPLE
        true, // SLOT_MASK_TRUTH
        true, // SLOT_MASK_ZORA
        true, // SLOT_MASK_KAMARO
        true, // SLOT_MASK_GIBDO
        true, // SLOT_MASK_GARO
        true, // SLOT_MASK_CAPTAIN
        true, // SLOT_MASK_GIANT
        true, // SLOT_MASK_FIERCE_DEITY
    },
};

#define SET_MOON_MASK_BIT(masksGivenOnMoonIndex, masksGivenOnMoonFlag) \
    ((masksGivenOnMoonIndex) << 8 | (masksGivenOnMoonFlag))
#define CHECK_GIVEN_MASK_ON_MOON(maskIndex) \
    (gSaveContext.masksGivenOnMoon[sMasksGivenOnMoonBits[maskIndex] >> 8] & (u8)sMasksGivenOnMoonBits[maskIndex])

u16 sMasksGivenOnMoonBits[] = {
    SET_MOON_MASK_BIT(1, 0x1),  // SLOT_MASK_POSTMAN
    SET_MOON_MASK_BIT(0, 0x4),  // SLOT_MASK_ALL_NIGHT
    SET_MOON_MASK_BIT(2, 0x2),  // SLOT_MASK_BLAST
    SET_MOON_MASK_BIT(1, 0x80), // SLOT_MASK_STONE
    SET_MOON_MASK_BIT(1, 0x4),  // SLOT_MASK_GREAT_FAIRY
    SET_MOON_MASK_BIT(2, 0x10), // SLOT_MASK_DEKU
    SET_MOON_MASK_BIT(0, 0x10), // SLOT_MASK_KEATON
    SET_MOON_MASK_BIT(2, 0x1),  // SLOT_MASK_BREMEN
    SET_MOON_MASK_BIT(0, 0x8),  // SLOT_MASK_BUNNY
    SET_MOON_MASK_BIT(1, 0x10), // SLOT_MASK_DON_GERO
    SET_MOON_MASK_BIT(2, 0x4),  // SLOT_MASK_SCENTS
    SET_MOON_MASK_BIT(2, 0x20), // SLOT_MASK_GORON
    SET_MOON_MASK_BIT(0, 0x40), // SLOT_MASK_ROMANI
    SET_MOON_MASK_BIT(0, 0x80), // SLOT_MASK_CIRCUS_LEADER
    SET_MOON_MASK_BIT(0, 0x2),  // SLOT_MASK_KAFEIS_MASK
    SET_MOON_MASK_BIT(1, 0x2),  // SLOT_MASK_COUPLE
    SET_MOON_MASK_BIT(0, 0x1),  // SLOT_MASK_TRUTH
    SET_MOON_MASK_BIT(2, 0x40), // SLOT_MASK_ZORA
    SET_MOON_MASK_BIT(1, 0x20), // SLOT_MASK_KAMARO
    SET_MOON_MASK_BIT(1, 0x8),  // SLOT_MASK_GIBDO
    SET_MOON_MASK_BIT(0, 0x20), // SLOT_MASK_GARO
    SET_MOON_MASK_BIT(1, 0x40), // SLOT_MASK_CAPTAIN
    SET_MOON_MASK_BIT(2, 0x8),  // SLOT_MASK_GIANT
    SET_MOON_MASK_BIT(2, 0X80), // SLOT_MASK_FIERCE_DEITY
};

s16 sMaskMagicArrowEffectsR[] = { 255, 100, 255 };
s16 sMaskMagicArrowEffectsG[] = { 0, 100, 255 };
s16 sMaskMagicArrowEffectsB[] = { 0, 255, 100 };

void KaleidoScope_DrawMaskSelect(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    u16 i;
    u16 j;

    OPEN_DISPS(play->state.gfxCtx);

    KaleidoScope_SetCursorVtx(pauseCtx, pauseCtx->cursorSlot[PAUSE_MASK] * 4, pauseCtx->maskVtx);

    func_8012C8AC(play->state.gfxCtx);

    // Draw a white box around the items that are equipped on the C buttons
    // Loop over c-buttons (i) and vtx offset (j)
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
    for (i = 0, j = NUM_MASK_SLOTS * 4; i < 3; i++, j += 4) {
        if (GET_CUR_FORM_BTN_ITEM(i + 1) != ITEM_NONE) {
            if (GET_CUR_FORM_BTN_SLOT(i + 1) >= NUM_ITEM_SLOTS) {
                gSPVertex(POLY_OPA_DISP++, &pauseCtx->maskVtx[j], 4, 0);
                POLY_OPA_DISP = func_8010DC58(POLY_OPA_DISP, gEquippedItemOutlineTex, 32, 32, 0);
            }
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);

    // Draw the item icons
    // Loop over slots (i) and vtx offset (j)
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    for (j = 0, i = 0; i < NUM_MASK_SLOTS; i++, j += 4) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

        if (((void)0, gSaveContext.save.inventory.items[i + NUM_ITEM_SLOTS]) != ITEM_NONE) {
            if (!CHECK_GIVEN_MASK_ON_MOON(i)) {
                if ((pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) && (pauseCtx->pageIndex == PAUSE_MASK) &&
                    (pauseCtx->cursorSpecialPos == 0) &&
                    gMaskPlayerFormSlotRestrictions[(void)0, gSaveContext.save.playerForm][i]) {
                    if ((sMaskEquipState == EQUIP_STATE_MAGIC_ARROW_HOVER_OVER_BOW_SLOT) && (i == SLOT_ARROW_ICE)) {
                        // Possible bug:
                        // Supposed to be `SLOT_BOW`, unchanged from OoT, instead increase size of ice arrow icon
                        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0,
                                        sMaskMagicArrowEffectsR[pauseCtx->equipTargetItem - 0xB5],
                                        sMaskMagicArrowEffectsG[pauseCtx->equipTargetItem - 0xB5],
                                        sMaskMagicArrowEffectsB[pauseCtx->equipTargetItem - 0xB5], pauseCtx->alpha);

                        pauseCtx->maskVtx[j + 0].v.ob[0] = pauseCtx->maskVtx[j + 2].v.ob[0] =
                            pauseCtx->maskVtx[j + 0].v.ob[0] - 2;
                        pauseCtx->maskVtx[j + 1].v.ob[0] = pauseCtx->maskVtx[j + 3].v.ob[0] =
                            pauseCtx->maskVtx[j + 0].v.ob[0] + 32;
                        pauseCtx->maskVtx[j + 0].v.ob[1] = pauseCtx->maskVtx[j + 1].v.ob[1] =
                            pauseCtx->maskVtx[j + 0].v.ob[1] + 2;
                        pauseCtx->maskVtx[j + 2].v.ob[1] = pauseCtx->maskVtx[j + 3].v.ob[1] =
                            pauseCtx->maskVtx[j + 0].v.ob[1] - 32;

                    } else if (i == pauseCtx->cursorSlot[PAUSE_MASK]) {
                        // Increase the size of the selected item
                        pauseCtx->maskVtx[j + 0].v.ob[0] = pauseCtx->maskVtx[j + 2].v.ob[0] =
                            pauseCtx->maskVtx[j + 0].v.ob[0] - 2;
                        pauseCtx->maskVtx[j + 1].v.ob[0] = pauseCtx->maskVtx[j + 3].v.ob[0] =
                            pauseCtx->maskVtx[j + 0].v.ob[0] + 32;
                        pauseCtx->maskVtx[j + 0].v.ob[1] = pauseCtx->maskVtx[j + 1].v.ob[1] =
                            pauseCtx->maskVtx[j + 0].v.ob[1] + 2;
                        pauseCtx->maskVtx[j + 2].v.ob[1] = pauseCtx->maskVtx[j + 3].v.ob[1] =
                            pauseCtx->maskVtx[j + 0].v.ob[1] - 32;
                    }
                }

                gSPVertex(POLY_OPA_DISP++, &pauseCtx->maskVtx[j + 0], 4, 0);
                KaleidoScope_DrawTexQuadRGBA32(
                    play->state.gfxCtx, gItemIcons[((void)0, gSaveContext.save.inventory.items[i + NUM_ITEM_SLOTS])],
                    32, 32, 0);
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

u8 sMaskPlayerFormItems[] = {
    ITEM_MASK_FIERCE_DEITY, ITEM_MASK_GORON, ITEM_MASK_ZORA, ITEM_MASK_DEKU, ITEM_NONE,
};

void KaleidoScope_UpdateMaskCursor(PlayState* play) {
    Input* input = CONTROLLER1(&play->state);
    PauseContext* pauseCtx = &play->pauseCtx;
    MessageContext* msgCtx = &play->msgCtx;
    u16 vtxIndex;
    u16 cursorItem;
    u16 cursorSlot;
    s16 cursorPoint;
    s16 cursorXIndex;
    s16 cursorYIndex;
    s16 oldCursorPoint;
    s16 moveCursorResult;
    s16 pad2;

    pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_WHITE;
    pauseCtx->nameColorSet = PAUSE_NAME_COLOR_SET_WHITE;

    if ((pauseCtx->state == PAUSE_STATE_MAIN) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) &&
        (pauseCtx->pageIndex == PAUSE_MASK) && !pauseCtx->itemDescriptionOn) {
        moveCursorResult = PAUSE_CURSOR_RESULT_NONE;
        oldCursorPoint = pauseCtx->cursorPoint[PAUSE_MASK];

        cursorItem = pauseCtx->cursorItem[PAUSE_MASK];

        // Move cursor left/right
        if (pauseCtx->cursorSpecialPos == 0) {
            // cursor is currently on a slot
            pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_YELLOW;

            if (ABS_ALT(pauseCtx->stickAdjX) > 30) {
                cursorPoint = pauseCtx->cursorPoint[PAUSE_MASK];
                cursorXIndex = pauseCtx->cursorXIndex[PAUSE_MASK];
                cursorYIndex = pauseCtx->cursorYIndex[PAUSE_MASK];

                // Search for slot to move to
                while (moveCursorResult == PAUSE_CURSOR_RESULT_NONE) {
                    if (pauseCtx->stickAdjX < -30) {
                        // move cursor left
                        pauseCtx->unk_298 = 4.0f;
                        if (pauseCtx->cursorXIndex[PAUSE_MASK] != 0) {
                            pauseCtx->cursorXIndex[PAUSE_MASK]--;
                            pauseCtx->cursorPoint[PAUSE_MASK]--;
                            moveCursorResult = PAUSE_CURSOR_RESULT_SLOT;
                        } else {
                            pauseCtx->cursorYIndex[PAUSE_MASK]++;

                            if (pauseCtx->cursorYIndex[PAUSE_MASK] >= 4) {
                                pauseCtx->cursorYIndex[PAUSE_MASK] = 0;
                            }

                            pauseCtx->cursorPoint[PAUSE_MASK] =
                                pauseCtx->cursorXIndex[PAUSE_MASK] + (pauseCtx->cursorYIndex[PAUSE_MASK] * 6);

                            if (pauseCtx->cursorPoint[PAUSE_MASK] >= NUM_MASK_SLOTS) {
                                pauseCtx->cursorPoint[PAUSE_MASK] = pauseCtx->cursorXIndex[PAUSE_MASK];
                            }

                            if (cursorYIndex == pauseCtx->cursorYIndex[PAUSE_MASK]) {
                                pauseCtx->cursorXIndex[PAUSE_MASK] = cursorXIndex;
                                pauseCtx->cursorPoint[PAUSE_MASK] = cursorPoint;

                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);

                                moveCursorResult = PAUSE_CURSOR_RESULT_SPECIAL_POS;
                            }
                        }
                    } else if (pauseCtx->stickAdjX > 30) {
                        // move cursor right
                        pauseCtx->unk_298 = 4.0f;
                        if (pauseCtx->cursorXIndex[PAUSE_MASK] <= 4) {
                            pauseCtx->cursorXIndex[PAUSE_MASK]++;
                            pauseCtx->cursorPoint[PAUSE_MASK]++;
                            moveCursorResult = PAUSE_CURSOR_RESULT_SLOT;
                        } else {
                            pauseCtx->cursorYIndex[PAUSE_MASK]++;

                            if (pauseCtx->cursorYIndex[PAUSE_MASK] >= 4) {
                                pauseCtx->cursorYIndex[PAUSE_MASK] = 0;
                            }

                            pauseCtx->cursorPoint[PAUSE_MASK] =
                                pauseCtx->cursorXIndex[PAUSE_MASK] + (pauseCtx->cursorYIndex[PAUSE_MASK] * 6);

                            if (pauseCtx->cursorPoint[PAUSE_MASK] >= NUM_MASK_SLOTS) {
                                pauseCtx->cursorPoint[PAUSE_MASK] = pauseCtx->cursorXIndex[PAUSE_MASK];
                            }

                            if (cursorYIndex == pauseCtx->cursorYIndex[PAUSE_MASK]) {
                                pauseCtx->cursorXIndex[PAUSE_MASK] = cursorXIndex;
                                pauseCtx->cursorPoint[PAUSE_MASK] = cursorPoint;

                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);

                                moveCursorResult = PAUSE_CURSOR_RESULT_SPECIAL_POS;
                            }
                        }
                    }
                }

                if (moveCursorResult == PAUSE_CURSOR_RESULT_SLOT) {
                    cursorItem = gSaveContext.save.inventory.items[pauseCtx->cursorPoint[PAUSE_MASK] + NUM_ITEM_SLOTS];
                    if (CHECK_GIVEN_MASK_ON_MOON(pauseCtx->cursorPoint[PAUSE_MASK])) {
                        cursorItem = ITEM_NONE;
                    }
                }
            }
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            if (pauseCtx->stickAdjX > 30) {
                func_80821A04(play);
                cursorYIndex = 0;
                cursorXIndex = 0;
                cursorPoint = 0; // top row, left column (SLOT_MASK_POSTMAN)

                // Search for slot to move to
                while (true) {
                    // Check if current cursor has an item in its slot
                    if ((gSaveContext.save.inventory.items[cursorPoint + NUM_ITEM_SLOTS] != ITEM_NONE) &&
                        !CHECK_GIVEN_MASK_ON_MOON(cursorPoint)) {
                        pauseCtx->cursorPoint[PAUSE_MASK] = cursorPoint;
                        pauseCtx->cursorXIndex[PAUSE_MASK] = cursorXIndex;
                        pauseCtx->cursorYIndex[PAUSE_MASK] = cursorYIndex;
                        moveCursorResult = PAUSE_CURSOR_RESULT_SLOT;
                        break;
                    }

                    // move 1 row down and retry
                    cursorYIndex++;
                    cursorPoint += 6;
                    if (cursorYIndex < 4) {
                        continue;
                    }

                    // move 1 column right and retry
                    cursorYIndex = 0;
                    cursorPoint = cursorXIndex + 1;
                    cursorXIndex = cursorPoint;
                    if (cursorXIndex < 6) {
                        continue;
                    }

                    // No item available
                    KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                    break;
                }
            }
        } else { // PAUSE_CURSOR_PAGE_RIGHT
            //! FAKE:
            if (1) {}
            if (pauseCtx->stickAdjX < -30) {
                func_80821A04(play);
                cursorXIndex = 5;
                cursorPoint = 5; // top row, right column (SLOT_MASK_DEKU)
                cursorYIndex = 0;

                // Search for slot to move to
                while (true) {
                    // Check if current cursor has an item in its slot
                    if ((gSaveContext.save.inventory.items[cursorPoint + NUM_ITEM_SLOTS] != ITEM_NONE) &&
                        !CHECK_GIVEN_MASK_ON_MOON(cursorPoint)) {
                        pauseCtx->cursorPoint[PAUSE_MASK] = cursorPoint;
                        pauseCtx->cursorXIndex[PAUSE_MASK] = cursorXIndex;
                        pauseCtx->cursorYIndex[PAUSE_MASK] = cursorYIndex;
                        moveCursorResult = PAUSE_CURSOR_RESULT_SLOT;
                        break;
                    }

                    // move 1 row down and retry
                    cursorYIndex++;
                    cursorPoint += 6;
                    if (cursorYIndex < 4) {
                        continue;
                    }

                    // move 1 column left and retry
                    cursorYIndex = 0;
                    cursorPoint = cursorXIndex - 1;
                    cursorXIndex = cursorPoint;
                    if (cursorXIndex >= 0) {
                        continue;
                    }

                    // No item available
                    KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                    break;
                }
            }
        }

        if (pauseCtx->cursorSpecialPos == 0) {
            // move cursor up/down
            if (ABS_ALT(pauseCtx->stickAdjY) > 30) {
                moveCursorResult = PAUSE_CURSOR_RESULT_NONE;

                cursorPoint = pauseCtx->cursorPoint[PAUSE_MASK];
                cursorYIndex = pauseCtx->cursorYIndex[PAUSE_MASK];

                while (moveCursorResult == PAUSE_CURSOR_RESULT_NONE) {
                    if (pauseCtx->stickAdjY > 30) {
                        // move cursor up
                        moveCursorResult = PAUSE_CURSOR_RESULT_SPECIAL_POS;
                        if (pauseCtx->cursorYIndex[PAUSE_MASK] != 0) {
                            pauseCtx->unk_298 = 4.0f;
                            pauseCtx->cursorYIndex[PAUSE_MASK]--;
                            pauseCtx->cursorPoint[PAUSE_MASK] -= 6;
                            moveCursorResult = PAUSE_CURSOR_RESULT_SLOT;
                        } else {
                            pauseCtx->cursorYIndex[PAUSE_MASK] = cursorYIndex;
                            pauseCtx->cursorPoint[PAUSE_MASK] = cursorPoint;
                        }
                    } else if (pauseCtx->stickAdjY < -30) {
                        // move cursor down
                        moveCursorResult = PAUSE_CURSOR_RESULT_SPECIAL_POS;
                        if (pauseCtx->cursorYIndex[PAUSE_MASK] < 3) {
                            pauseCtx->unk_298 = 4.0f;
                            pauseCtx->cursorYIndex[PAUSE_MASK]++;
                            pauseCtx->cursorPoint[PAUSE_MASK] += 6;
                            moveCursorResult = PAUSE_CURSOR_RESULT_SLOT;
                        } else {
                            pauseCtx->cursorYIndex[PAUSE_MASK] = cursorYIndex;
                            pauseCtx->cursorPoint[PAUSE_MASK] = cursorPoint;
                        }
                    }
                }
            }

            cursorSlot = pauseCtx->cursorPoint[PAUSE_MASK];
            pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_YELLOW;

            if (moveCursorResult == PAUSE_CURSOR_RESULT_SLOT) {
                cursorItem = gSaveContext.save.inventory.items[pauseCtx->cursorPoint[PAUSE_MASK] + NUM_ITEM_SLOTS];
                if (CHECK_GIVEN_MASK_ON_MOON(pauseCtx->cursorPoint[PAUSE_MASK])) {
                    cursorItem = ITEM_NONE;
                }
            } else if (moveCursorResult != PAUSE_CURSOR_RESULT_SPECIAL_POS) {
                cursorItem = gSaveContext.save.inventory.items[pauseCtx->cursorPoint[PAUSE_MASK] + NUM_ITEM_SLOTS];
                if (CHECK_GIVEN_MASK_ON_MOON(pauseCtx->cursorPoint[PAUSE_MASK])) {
                    cursorItem = ITEM_NONE;
                }
            }

            if (cursorItem == ITEM_NONE) {
                cursorItem = PAUSE_ITEM_NONE;
                pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_WHITE;
            }

            if ((cursorItem != PAUSE_ITEM_NONE) && (msgCtx->msgLength == 0)) {
                if (gSaveContext.buttonStatus[EQUIP_SLOT_A] == BTN_DISABLED) {
                    gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
                    gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
                    Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
                }
            } else if (gSaveContext.buttonStatus[EQUIP_SLOT_A] != BTN_DISABLED) {
                gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_DISABLED;
                gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
                Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
            }

            pauseCtx->cursorItem[PAUSE_MASK] = cursorItem;
            pauseCtx->cursorSlot[PAUSE_MASK] = cursorSlot;
            if (cursorItem != PAUSE_ITEM_NONE) {
                // Equip item to the C buttons
                if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && !pauseCtx->itemDescriptionOn &&
                    (pauseCtx->state == PAUSE_STATE_MAIN) && (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) &&
                    CHECK_BTN_ANY(input->press.button, BTN_CLEFT | BTN_CDOWN | BTN_CRIGHT)) {

                    // Ensure that a mask is not unequipped while being used
                    if (CHECK_BTN_ALL(input->press.button, BTN_CLEFT)) {
                        if (((Player_GetCurMaskItemId(play) != ITEM_NONE) &&
                             (Player_GetCurMaskItemId(play) == BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT))) ||
                            ((sMaskPlayerFormItems[((void)0, gSaveContext.save.playerForm)] != ITEM_NONE) &&
                             (sMaskPlayerFormItems[((void)0, gSaveContext.save.playerForm)] ==
                              BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT)))) {
                            play_sound(NA_SE_SY_ERROR);
                            return;
                        }
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
                        if (((Player_GetCurMaskItemId(play) != ITEM_NONE) &&
                             (Player_GetCurMaskItemId(play) == BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN))) ||
                            ((sMaskPlayerFormItems[((void)0, gSaveContext.save.playerForm)] != ITEM_NONE) &&
                             (sMaskPlayerFormItems[((void)0, gSaveContext.save.playerForm)] ==
                              BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN)))) {
                            play_sound(NA_SE_SY_ERROR);
                            return;
                        }
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_CRIGHT)) {
                        if (((Player_GetCurMaskItemId(play) != ITEM_NONE) &&
                             (Player_GetCurMaskItemId(play) == BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT))) ||
                            ((sMaskPlayerFormItems[((void)0, gSaveContext.save.playerForm)] != ITEM_NONE) &&
                             (sMaskPlayerFormItems[((void)0, gSaveContext.save.playerForm)] ==
                              BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT)))) {
                            play_sound(NA_SE_SY_ERROR);
                            return;
                        }
                    }

                    if ((Player_GetEnvTimerType(play) >= PLAYER_ENV_TIMER_UNDERWATER_FLOOR) &&
                        (Player_GetEnvTimerType(play) <= PLAYER_ENV_TIMER_UNDERWATER_FREE) &&
                        ((cursorSlot == (SLOT_MASK_DEKU - NUM_ITEM_SLOTS)) ||
                         (cursorSlot == (SLOT_MASK_GORON - NUM_ITEM_SLOTS)))) {
                        play_sound(NA_SE_SY_ERROR);
                        return;
                    }

                    if (CHECK_BTN_ALL(input->press.button, BTN_CLEFT)) {
                        pauseCtx->equipTargetCBtn = PAUSE_EQUIP_C_LEFT;
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
                        pauseCtx->equipTargetCBtn = PAUSE_EQUIP_C_DOWN;
                    } else if (CHECK_BTN_ALL(input->press.button, BTN_CRIGHT)) {
                        pauseCtx->equipTargetCBtn = PAUSE_EQUIP_C_RIGHT;
                    }

                    // Equip item to the C buttons
                    pauseCtx->equipTargetItem = cursorItem;
                    pauseCtx->equipTargetSlot = cursorSlot + NUM_ITEM_SLOTS;
                    pauseCtx->mainState = PAUSE_MAIN_STATE_EQUIP_MASK;
                    vtxIndex = cursorSlot * 4;
                    pauseCtx->equipAnimX = pauseCtx->maskVtx[vtxIndex].v.ob[0] * 10;
                    pauseCtx->equipAnimY = pauseCtx->maskVtx[vtxIndex].v.ob[1] * 10;
                    pauseCtx->equipAnimAlpha = 255;
                    sMaskEquipMagicArrowSlotHoldTimer = 0;
                    sMaskEquipState = EQUIP_STATE_MOVE_TO_C_BTN;
                    sMaskEquipAnimTimer = 10;
                    play_sound(NA_SE_SY_DECIDE);
                } else if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && (pauseCtx->state == PAUSE_STATE_MAIN) &&
                           (pauseCtx->mainState == PAUSE_MAIN_STATE_IDLE) &&
                           CHECK_BTN_ALL(input->press.button, BTN_A) && (msgCtx->msgLength == 0)) {
                    // Give description on item through a message box
                    pauseCtx->itemDescriptionOn = true;
                    if (pauseCtx->cursorYIndex[PAUSE_MASK] < 2) {
                        func_801514B0(play, 0x1700 + pauseCtx->cursorItem[PAUSE_MASK], 3);
                    } else {
                        func_801514B0(play, 0x1700 + pauseCtx->cursorItem[PAUSE_MASK], 1);
                    }
                }
            }
        } else {
            pauseCtx->cursorItem[PAUSE_MASK] = PAUSE_ITEM_NONE;
        }

        if (oldCursorPoint != pauseCtx->cursorPoint[PAUSE_MASK]) {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if ((pauseCtx->mainState == PAUSE_MAIN_STATE_EQUIP_MASK) && (pauseCtx->pageIndex == PAUSE_MASK)) {
        pauseCtx->cursorColorSet = PAUSE_CURSOR_COLOR_SET_YELLOW;
    }
}

s16 sMaskCButtonPosX[] = { 660, 900, 1140 };
s16 sMaskCButtonPosY[] = { 1100, 920, 1100 };

void KaleidoScope_UpdateMaskEquip(PlayState* play) {
    static s16 sMaskEquipMagicArrowBowSlotHoldTimer = 0;
    PauseContext* pauseCtx = &play->pauseCtx;
    Vtx* bowItemVtx;
    u16 offsetX;
    u16 offsetY;

    // Grow glowing orb when equipping magic arrows
    if (sMaskEquipState == EQUIP_STATE_MAGIC_ARROW_GROW_ORB) {
        pauseCtx->equipAnimAlpha += 14;
        if (pauseCtx->equipAnimAlpha > 255) {
            pauseCtx->equipAnimAlpha = 254;
            sMaskEquipState++;
        }
        // Hover over magic arrow slot when the next state is reached
        sMaskEquipMagicArrowSlotHoldTimer = 5;
        return;
    }

    if (sMaskEquipState == EQUIP_STATE_MAGIC_ARROW_HOVER_OVER_BOW_SLOT) {
        sMaskEquipMagicArrowBowSlotHoldTimer--;

        if (sMaskEquipMagicArrowBowSlotHoldTimer == 0) {
            pauseCtx->equipTargetItem -= 0xB5 - ITEM_BOW_ARROW_FIRE;
            pauseCtx->equipTargetSlot = SLOT_BOW;
            sMaskEquipAnimTimer = 6;
            pauseCtx->equipAnimScale = 320;
            pauseCtx->equipAnimShrinkRate = 40;
            sMaskEquipState++;
            play_sound(NA_SE_SY_SYNTH_MAGIC_ARROW);
        }
        return;
    }

    if (sMaskEquipState == EQUIP_STATE_MAGIC_ARROW_MOVE_TO_BOW_SLOT) {
        bowItemVtx = &pauseCtx->itemVtx[12];
        offsetX = ABS_ALT(pauseCtx->equipAnimX - bowItemVtx->v.ob[0] * 10) / sMaskEquipAnimTimer;
        offsetY = ABS_ALT(pauseCtx->equipAnimY - bowItemVtx->v.ob[1] * 10) / sMaskEquipAnimTimer;
    } else {
        offsetX = ABS_ALT(pauseCtx->equipAnimX - sMaskCButtonPosX[pauseCtx->equipTargetCBtn]) / sMaskEquipAnimTimer;
        offsetY = ABS_ALT(pauseCtx->equipAnimY - sMaskCButtonPosY[pauseCtx->equipTargetCBtn]) / sMaskEquipAnimTimer;
    }

    if ((pauseCtx->equipTargetItem >= 0xB5) && (pauseCtx->equipAnimAlpha < 254)) {
        pauseCtx->equipAnimAlpha += 14;
        if (pauseCtx->equipAnimAlpha > 255) {
            pauseCtx->equipAnimAlpha = 254;
        }
        sMaskEquipMagicArrowSlotHoldTimer = 5;
        return;
    }

    if (sMaskEquipMagicArrowSlotHoldTimer == 0) {
        pauseCtx->equipAnimScale -= pauseCtx->equipAnimShrinkRate / sMaskEquipAnimTimer;
        pauseCtx->equipAnimShrinkRate -= pauseCtx->equipAnimShrinkRate / sMaskEquipAnimTimer;

        // Update coordinates of item icon while being equipped
        if (sMaskEquipState == EQUIP_STATE_MAGIC_ARROW_MOVE_TO_BOW_SLOT) {
            // target is the bow slot
            if (pauseCtx->equipAnimX >= (pauseCtx->itemVtx[12].v.ob[0] * 10)) {
                pauseCtx->equipAnimX -= offsetX;
            } else {
                pauseCtx->equipAnimX += offsetX;
            }

            if (pauseCtx->equipAnimY >= (pauseCtx->itemVtx[12].v.ob[1] * 10)) {
                pauseCtx->equipAnimY -= offsetY;
            } else {
                pauseCtx->equipAnimY += offsetY;
            }
        } else {
            // target is the c button
            if (pauseCtx->equipAnimX >= sMaskCButtonPosX[pauseCtx->equipTargetCBtn]) {
                pauseCtx->equipAnimX -= offsetX;
            } else {
                pauseCtx->equipAnimX += offsetX;
            }

            if (pauseCtx->equipAnimY >= sMaskCButtonPosY[pauseCtx->equipTargetCBtn]) {
                pauseCtx->equipAnimY -= offsetY;
            } else {
                pauseCtx->equipAnimY += offsetY;
            }
        }

        sMaskEquipAnimTimer--;
        if (sMaskEquipAnimTimer == 0) {
            if (sMaskEquipState == EQUIP_STATE_MAGIC_ARROW_MOVE_TO_BOW_SLOT) {
                sMaskEquipState++;
                sMaskEquipMagicArrowBowSlotHoldTimer = 4;
                return;
            }

            // Equip mask onto c buttons
            if (pauseCtx->equipTargetCBtn == PAUSE_EQUIP_C_LEFT) {
                // Swap if mask is already equipped on CDown or CRight.
                if (pauseCtx->equipTargetSlot == C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN)) {
                    if ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) & 0xFF) != ITEM_NONE) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) = BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT);
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN) = C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT);
                        Interface_LoadItemIcon(play, EQUIP_SLOT_C_DOWN);
                    } else {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) = ITEM_NONE;
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN) = SLOT_NONE;
                    }
                } else if (pauseCtx->equipTargetSlot == C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT)) {
                    if ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) & 0xFF) != ITEM_NONE) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) = BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT);
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT) = C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT);
                        Interface_LoadItemIcon(play, EQUIP_SLOT_C_RIGHT);
                    } else {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) = ITEM_NONE;
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT) = SLOT_NONE;
                    }
                }

                // Equip mask on CLeft
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) = pauseCtx->equipTargetItem;
                C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT) = pauseCtx->equipTargetSlot;
                Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_LEFT);
            } else if (pauseCtx->equipTargetCBtn == PAUSE_EQUIP_C_DOWN) {
                // Swap if mask is already equipped on CLeft or CRight.
                if (pauseCtx->equipTargetSlot == C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT)) {
                    if ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) & 0xFF) != ITEM_NONE) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) = BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN);
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT) = C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN);
                        Interface_LoadItemIcon(play, EQUIP_SLOT_C_LEFT);
                    } else {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) = ITEM_NONE;
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT) = SLOT_NONE;
                    }
                } else if (pauseCtx->equipTargetSlot == C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT)) {
                    if ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) & 0xFF) != ITEM_NONE) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) = BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN);
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT) = C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN);
                        Interface_LoadItemIcon(play, EQUIP_SLOT_C_RIGHT);
                    } else {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) = ITEM_NONE;
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT) = SLOT_NONE;
                    }
                }

                // Equip mask on CDown
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) = pauseCtx->equipTargetItem;
                C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN) = pauseCtx->equipTargetSlot;
                Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_DOWN);
            } else { // (pauseCtx->equipTargetCBtn == PAUSE_EQUIP_C_RIGHT)
                // Swap if mask is already equipped on CLeft or CDown.
                if (pauseCtx->equipTargetSlot == C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT)) {
                    if ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) & 0xFF) != ITEM_NONE) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) = BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT);
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT) = C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT);
                        Interface_LoadItemIcon(play, EQUIP_SLOT_C_LEFT);
                    } else {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) = ITEM_NONE;
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT) = SLOT_NONE;
                    }
                } else if (pauseCtx->equipTargetSlot == C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN)) {
                    if ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) & 0xFF) != ITEM_NONE) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) = BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT);
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN) = C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT);
                        Interface_LoadItemIcon(play, EQUIP_SLOT_C_DOWN);
                    } else {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) = ITEM_NONE;
                        C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN) = SLOT_NONE;
                    }
                }

                // Equip mask on CRight
                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) = pauseCtx->equipTargetItem;
                C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT) = pauseCtx->equipTargetSlot;
                Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_RIGHT);
            }

            // Reset params
            pauseCtx->mainState = PAUSE_MAIN_STATE_IDLE;
            sMaskEquipAnimTimer = 10;
            pauseCtx->equipAnimScale = 320;
            pauseCtx->equipAnimShrinkRate = 40;
        }
    } else {
        sMaskEquipMagicArrowSlotHoldTimer--;
        if (sMaskEquipMagicArrowSlotHoldTimer == 0) {
            pauseCtx->equipAnimAlpha = 255;
        }
    }
}
