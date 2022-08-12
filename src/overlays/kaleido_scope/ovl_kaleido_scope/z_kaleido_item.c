/*
 * File: z_kaleido_item.c
 * Overlay: ovl_kaleido_scope
 * Description:
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

s16 sEquipState = 0;
s16 sEquipAnimTimer = 0;
s16 sEquipMoveTimer = 10;

u8 gSlotTransformReqs[5][24] = {
    {
        false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, true,  true,  true,  true,  true,  true,
    },
    {
        true, false, false, false, false, true, false, false, false, false, false, true,
        true, true,  true,  false, false, true, true,  true,  true,  true,  true,  true,
    },
    {
        true,  false, false, false, false, true, false, false, false, false, false, true,
        false, true,  true,  false, false, true, true,  true,  true,  true,  true,  true,
    },
    {
        true,  false, false, false, false, true, false, false, false, true, false, true,
        false, true,  true,  false, false, true, true,  true,  true,  true, true,  true,
    },
    {
        true,  true, true, true, true, true, true, true, true, true, true, true,
        false, true, true, true, true, true, true, true, true, true, true, true,
    },
};

s16 D_8082B444[] = {
    0x005F, 0x003E, 0x005F, 0x0080, 0x00A1, 0x00C2, 0x003E, 0x005F,
};

s16 D_8082B454[] = {
    0x0055, 0x0075, 0x0075, 0x0075, 0x0075, 0x0075, 0x0096, 0x0096,
};

Gfx* func_8010CD98(Gfx* displayListHead, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                   s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy);

void KaleidoScope_DrawAmmoCount(PauseContext* pauseCtx, GraphicsContext* gfxCtx, s16 item, u16 arg3) {
    s16 i;
    s16 ammo;

    OPEN_DISPS(gfxCtx);

    if (item == ITEM_PICTO_BOX) {
        if (!(((void)0, gSaveContext.save.inventory.questItems) & (gBitFlags[QUEST_PICTOGRAPH]))) {
            ammo = 0;
        } else {
            ammo = 1;
        }
    } else {
        ammo = AMMO(item);
    }

    gDPPipeSync(POLY_OPA_DISP++);

    if (!gSlotTransformReqs[((void)0, gSaveContext.save.playerForm)][SLOT(item)]) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 100, 100, 100, pauseCtx->alpha);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);
        if (ammo == 0) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 130, 130, 130, pauseCtx->alpha);
        } else if (((item == ITEM_BOMB) && (AMMO(item) == CUR_CAPACITY(UPG_BOMB_BAG))) ||
                   ((item == ITEM_BOW) && (AMMO(item) == CUR_CAPACITY(UPG_QUIVER))) ||
                   ((item == ITEM_STICK) && (AMMO(item) == CUR_CAPACITY(UPG_STICKS))) ||
                   ((item == ITEM_NUT) && (AMMO(item) == CUR_CAPACITY(UPG_NUTS))) ||
                   ((item == ITEM_BOMBCHU) && (AMMO(item) == CUR_CAPACITY(UPG_BOMB_BAG))) ||
                   ((item == ITEM_POWDER_KEG) && (ammo == 1)) || ((item == ITEM_PICTO_BOX) && (ammo == 1)) ||
                   ((item == ITEM_MAGIC_BEANS) && (ammo == 20))) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 120, 255, 0, pauseCtx->alpha);
        }
    }

    for (i = 0; ammo >= 10; i++) {
        ammo -= 10;
    }

    gDPPipeSync(POLY_OPA_DISP++);

    if (i != 0) {
        POLY_OPA_DISP = func_8010CD98(POLY_OPA_DISP, ((u8*)gAmmoDigit0Tex + (8 * 8 * i)), 8, 8, D_8082B444[arg3],
                                      D_8082B454[arg3], 8, 8, 1 << 10, 1 << 10);
    }
    POLY_OPA_DISP = func_8010CD98(POLY_OPA_DISP, ((u8*)gAmmoDigit0Tex + (8 * 8 * ammo)), 8, 8, D_8082B444[arg3] + 6,
                                  D_8082B454[arg3], 8, 8, 1 << 10, 1 << 10);

    CLOSE_DISPS(gfxCtx);
}

void KaleidoScope_SetCursorVtx(PauseContext* pauseCtx, u16 index, Vtx* vtx) {
    pauseCtx->cursorVtx[0].v.ob[0] = vtx[index].v.ob[0];
    pauseCtx->cursorVtx[0].v.ob[1] = vtx[index].v.ob[1];
}

// Part of KaleidoScope_DrawItemSelect
s16 sMagicArrowEffectsR[] = { 255, 100, 255 };
s16 sMagicArrowEffectsG[] = { 0, 100, 255 };
s16 sMagicArrowEffectsB[] = { 0, 255, 100 };
void func_8081B6EC(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;
    u16 i;
    u16 j;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C8AC(play->state.gfxCtx);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

    for (i = 0, j = 24 * 4; i < 3; i++, j += 4) {
        if (GET_CUR_FORM_BTN_ITEM(i + 1) != ITEM_NONE) {
            if (GET_CUR_FORM_BTN_SLOT(i + 1) < 24) {
                gSPVertex(POLY_OPA_DISP++, &pauseCtx->itemVtx[j], 4, 0);
                POLY_OPA_DISP = func_8010DC58(POLY_OPA_DISP, gEquippedItemOutlineTex, 32, 32, 0);
            }
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    for (j = 0, i = 0; i < 24; i++, j += 4) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

        if (((void)0, gSaveContext.save.inventory.items[i]) != ITEM_NONE) {
            if ((pauseCtx->unk_200 == 0) && (pauseCtx->pageIndex == PAUSE_ITEM) && (pauseCtx->cursorSpecialPos == 0) &&
                gSlotTransformReqs[(void)0, gSaveContext.save.playerForm][i]) {
                if ((sEquipState == 2) && (i == 3)) {

                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sMagicArrowEffectsR[pauseCtx->equipTargetItem - 0xB5],
                                    sMagicArrowEffectsG[pauseCtx->equipTargetItem - 0xB5],
                                    sMagicArrowEffectsB[pauseCtx->equipTargetItem - 0xB5], pauseCtx->alpha);

                    pauseCtx->itemVtx[j + 0].v.ob[0] = pauseCtx->itemVtx[j + 2].v.ob[0] =
                        pauseCtx->itemVtx[j + 0].v.ob[0] - 2;
                    pauseCtx->itemVtx[j + 1].v.ob[0] = pauseCtx->itemVtx[j + 3].v.ob[0] =
                        pauseCtx->itemVtx[j + 0].v.ob[0] + 0x20;
                    pauseCtx->itemVtx[j + 0].v.ob[1] = pauseCtx->itemVtx[j + 1].v.ob[1] =
                        pauseCtx->itemVtx[j + 0].v.ob[1] + 2;
                    pauseCtx->itemVtx[j + 2].v.ob[1] = pauseCtx->itemVtx[j + 3].v.ob[1] =
                        pauseCtx->itemVtx[j + 0].v.ob[1] - 0x20;

                } else if (i == pauseCtx->cursorSlot[0]) {
                    pauseCtx->itemVtx[j + 0].v.ob[0] = pauseCtx->itemVtx[j + 2].v.ob[0] =
                        pauseCtx->itemVtx[j + 0].v.ob[0] - 2;
                    pauseCtx->itemVtx[j + 1].v.ob[0] = pauseCtx->itemVtx[j + 3].v.ob[0] =
                        pauseCtx->itemVtx[j + 0].v.ob[0] + 0x20;
                    pauseCtx->itemVtx[j + 0].v.ob[1] = pauseCtx->itemVtx[j + 1].v.ob[1] =
                        pauseCtx->itemVtx[j + 0].v.ob[1] + 2;
                    pauseCtx->itemVtx[j + 2].v.ob[1] = pauseCtx->itemVtx[j + 3].v.ob[1] =
                        pauseCtx->itemVtx[j + 0].v.ob[1] - 0x20;
                }
            }

            gSPVertex(POLY_OPA_DISP++, &pauseCtx->itemVtx[j + 0], 4, 0);
            KaleidoScope_DrawQuadTextureRGBA32(play->state.gfxCtx,
                                               gItemIcons[((void)0, gSaveContext.save.inventory.items[i])], 32, 32, 0);
        }
    }

    if (pauseCtx->pageIndex == 0) {
        if ((pauseCtx->state == 6) && ((pauseCtx->unk_200 == 0) || (pauseCtx->unk_200 == 3)) &&
            (pauseCtx->state != 7) && ((pauseCtx->state < 8) || (pauseCtx->state >= 0x13))) {
            func_8012C628(play->state.gfxCtx);
            gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

            for (j = 0, i = 0; i < 24; i++) {
                if (gAmmoItems[i] != ITEM_NONE) {
                    if (((void)0, gSaveContext.save.inventory.items[i]) != ITEM_NONE) {
                        KaleidoScope_DrawAmmoCount(pauseCtx, play->state.gfxCtx,
                                                   ((void)0, gSaveContext.save.inventory.items[i]), j);
                    }
                    j++;
                }
            }
            func_8012C8AC(play->state.gfxCtx);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

u8 D_8082B47C[] = {
    ITEM_MASK_FIERCE_DEITY, ITEM_MASK_GORON, ITEM_MASK_ZORA, ITEM_MASK_DEKU, ITEM_NONE,
};
void KaleidoScope_DrawItemSelect(PlayState* play) {
    s32 pad;
    PauseContext* pauseCtx = &play->pauseCtx;
    MessageContext* msgCtx = &play->msgCtx;
    u16 vtxIndex;
    u16 cursorItem;
    u16 cursorSlot;
    u8 index;
    s16 cursorPoint;
    s16 cursorX;
    s16 cursorY;
    s16 oldCursorPoint;
    s16 moveCursorResult;
    s16 pad2;

    pauseCtx->cursorColorSet = 0;
    pauseCtx->nameColorSet = 0;

    if ((pauseCtx->state == 6) && (pauseCtx->unk_200 == 0) && (pauseCtx->pageIndex == 0) && (pauseCtx->unk_2B9 == 0)) {
        moveCursorResult = 0;
        oldCursorPoint = pauseCtx->cursorPoint[PAUSE_ITEM];

        cursorItem = pauseCtx->cursorItem[PAUSE_ITEM];

        if (pauseCtx->cursorSpecialPos == 0) {
            pauseCtx->cursorColorSet = 2;

            if (ABS_ALT(pauseCtx->stickRelX) > 30) {
                cursorPoint = pauseCtx->cursorPoint[PAUSE_ITEM];
                cursorX = pauseCtx->cursorX[PAUSE_ITEM];
                cursorY = pauseCtx->cursorY[PAUSE_ITEM];

                while (moveCursorResult == 0) {
                    if (pauseCtx->stickRelX < -30) {
                        pauseCtx->unk_298 = 4.0f;
                        if (pauseCtx->cursorX[PAUSE_ITEM] != 0) {
                            pauseCtx->cursorX[PAUSE_ITEM]--;
                            pauseCtx->cursorPoint[PAUSE_ITEM]--;
                            moveCursorResult = 1;

                        } else {
                            pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                            pauseCtx->cursorY[PAUSE_ITEM]++;

                            if (pauseCtx->cursorY[PAUSE_ITEM] >= 4) {
                                pauseCtx->cursorY[PAUSE_ITEM] = 0;
                            }

                            pauseCtx->cursorPoint[PAUSE_ITEM] =
                                pauseCtx->cursorX[PAUSE_ITEM] + (pauseCtx->cursorY[PAUSE_ITEM] * 6);

                            if (pauseCtx->cursorPoint[PAUSE_ITEM] >= 24) {
                                pauseCtx->cursorPoint[PAUSE_ITEM] = pauseCtx->cursorX[PAUSE_ITEM];
                            }

                            if (cursorY == pauseCtx->cursorY[PAUSE_ITEM]) {
                                pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                                pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;

                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);

                                moveCursorResult = 2;
                            }
                        }
                    } else if (pauseCtx->stickRelX > 30) {
                        pauseCtx->unk_298 = 4.0f;
                        if (pauseCtx->cursorX[PAUSE_ITEM] < 5) {
                            pauseCtx->cursorX[PAUSE_ITEM]++;
                            pauseCtx->cursorPoint[PAUSE_ITEM]++;
                            moveCursorResult = 1;
                        } else {
                            pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                            pauseCtx->cursorY[PAUSE_ITEM]++;

                            if (pauseCtx->cursorY[PAUSE_ITEM] >= 4) {
                                pauseCtx->cursorY[PAUSE_ITEM] = 0;
                            }

                            pauseCtx->cursorPoint[PAUSE_ITEM] =
                                pauseCtx->cursorX[PAUSE_ITEM] + (pauseCtx->cursorY[PAUSE_ITEM] * 6);

                            if (pauseCtx->cursorPoint[PAUSE_ITEM] >= 24) {
                                pauseCtx->cursorPoint[PAUSE_ITEM] = pauseCtx->cursorX[PAUSE_ITEM];
                            }

                            if (cursorY == pauseCtx->cursorY[PAUSE_ITEM]) {
                                pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                                pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;

                                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);

                                moveCursorResult = 2;
                            }
                        }
                    }
                }

                if (moveCursorResult == 1) {
                    cursorItem = gSaveContext.save.inventory.items[pauseCtx->cursorPoint[PAUSE_ITEM]];
                }
            }
        } else if (pauseCtx->cursorSpecialPos == PAUSE_CURSOR_PAGE_LEFT) {
            if (pauseCtx->stickRelX > 30) {
                func_80821A04(play);
                cursorY = 0;
                cursorX = 0;
                cursorPoint = 0;

                while (true) {
                    if (gSaveContext.save.inventory.items[cursorPoint] != ITEM_NONE) {
                        pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;
                        pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                        pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                        moveCursorResult = 1;
                        break;
                    }

                    cursorY++;
                    cursorPoint += 6;
                    if (cursorY < 4) {
                        continue;
                    }

                    cursorY = 0;
                    cursorPoint = cursorX + 1;
                    cursorX = cursorPoint;
                    if (cursorX < 6) {
                        continue;
                    }

                    KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_RIGHT);
                    break;
                }
            }
        } else if (pauseCtx->stickRelX < -30) {
            func_80821A04(play);
            cursorX = 5;
            cursorPoint = 5;
            cursorY = 0;

            while (true) {
                if (gSaveContext.save.inventory.items[cursorPoint] != 0xFF) {
                    pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;
                    pauseCtx->cursorX[PAUSE_ITEM] = cursorX;
                    pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                    moveCursorResult = 1;
                    break;
                }

                cursorY++;
                cursorPoint += 6;
                if (cursorY < 4) {
                    continue;
                }

                cursorY = 0;
                cursorPoint = cursorX - 1;
                cursorX = cursorPoint;
                if (cursorX >= 0) {
                    continue;
                }

                KaleidoScope_MoveCursorToSpecialPos(play, PAUSE_CURSOR_PAGE_LEFT);
                break;
            }
        }

        if (pauseCtx->cursorSpecialPos == 0) {
            if (ABS_ALT(pauseCtx->stickRelY) > 30) {
                moveCursorResult = 0;

                cursorPoint = pauseCtx->cursorPoint[PAUSE_ITEM];
                cursorY = pauseCtx->cursorY[PAUSE_ITEM];

                while (moveCursorResult == 0) {
                    if (pauseCtx->stickRelY > 30) {
                        moveCursorResult = 2;
                        if (pauseCtx->cursorY[PAUSE_ITEM] != 0) {
                            pauseCtx->cursorY[PAUSE_ITEM]--;
                            pauseCtx->unk_298 = 4.0f;
                            pauseCtx->cursorPoint[PAUSE_ITEM] -= 6;
                            moveCursorResult = 1;
                        } else {
                            pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                            pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;
                        }
                    } else if (pauseCtx->stickRelY < -30) {
                        moveCursorResult = 2;
                        if (pauseCtx->cursorY[PAUSE_ITEM] < 3) {
                            pauseCtx->cursorY[PAUSE_ITEM]++;
                            pauseCtx->unk_298 = 4.0f;
                            pauseCtx->cursorPoint[PAUSE_ITEM] += 6;
                            moveCursorResult = 1;
                        } else {
                            pauseCtx->cursorY[PAUSE_ITEM] = cursorY;
                            pauseCtx->cursorPoint[PAUSE_ITEM] = cursorPoint;
                        }
                    }
                }
            }

            cursorSlot = pauseCtx->cursorPoint[PAUSE_ITEM];
            pauseCtx->cursorColorSet = 2;

            if (moveCursorResult == 1) {
                cursorItem = gSaveContext.save.inventory.items[pauseCtx->cursorPoint[PAUSE_ITEM]];
            } else if (moveCursorResult != 2) {
                cursorItem = gSaveContext.save.inventory.items[pauseCtx->cursorPoint[PAUSE_ITEM]];
            }

            if (cursorItem == ITEM_NONE) {
                cursorItem = PAUSE_ITEM_NONE;
                pauseCtx->cursorColorSet = 0;
            }

            if ((cursorItem != (u32)PAUSE_ITEM_NONE) && (msgCtx->msgLength == 0)) {
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

            pauseCtx->cursorItem[PAUSE_ITEM] = cursorItem;
            pauseCtx->cursorSlot[PAUSE_ITEM] = cursorSlot;

            if (cursorItem != PAUSE_ITEM_NONE) {
                if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && (pauseCtx->unk_2B9 == 0) &&
                    (pauseCtx->state == 6) && (pauseCtx->unk_200 == 0) &&
                    CHECK_BTN_ANY(CONTROLLER1(&play->state)->press.button, BTN_CLEFT | BTN_CDOWN | BTN_CRIGHT)) {
                    if (gSaveContext.save.playerForm != 4) {
                        if (1) {}
                        if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_CLEFT)) {
                            if (D_8082B47C[((void)0, gSaveContext.save.playerForm)] ==
                                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT)) {
                                play_sound(NA_SE_SY_ERROR);
                                return;
                            }
                        } else if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_CDOWN)) {
                            if (D_8082B47C[((void)0, gSaveContext.save.playerForm)] ==
                                BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN)) {
                                play_sound(NA_SE_SY_ERROR);
                                return;
                            }
                        } else if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_CRIGHT) &&
                                   (D_8082B47C[((void)0, gSaveContext.save.playerForm)] ==
                                    BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT))) {
                            play_sound(NA_SE_SY_ERROR);
                            return;
                        }
                    }

                    if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_CLEFT)) {
                        if ((Player_GetCurMaskItemId(play) != ITEM_NONE) &&
                            (Player_GetCurMaskItemId(play) == BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT))) {
                            play_sound(NA_SE_SY_ERROR);
                            return;
                        }
                        pauseCtx->equipTargetCBtn = 0;
                    } else if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_CDOWN)) {
                        if ((Player_GetCurMaskItemId(play) != ITEM_NONE) &&
                            (Player_GetCurMaskItemId(play) == BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN))) {
                            play_sound(NA_SE_SY_ERROR);
                            return;
                        }
                        pauseCtx->equipTargetCBtn = 1;
                    } else if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_CRIGHT)) {
                        if ((Player_GetCurMaskItemId(play) != ITEM_NONE) &&
                            (Player_GetCurMaskItemId(play) == BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT))) {
                            play_sound(NA_SE_SY_ERROR);
                            return;
                        }
                        pauseCtx->equipTargetCBtn = 2;
                    }
                    pauseCtx->equipTargetItem = cursorItem;
                    pauseCtx->equipTargetSlot = cursorSlot;
                    pauseCtx->unk_200 = 3;
                    vtxIndex = cursorSlot * 4;
                    pauseCtx->equipAnimX = pauseCtx->itemVtx[vtxIndex].v.ob[0] * 10;
                    pauseCtx->equipAnimY = pauseCtx->itemVtx[vtxIndex].v.ob[1] * 10;
                    pauseCtx->equipAnimAlpha = 255;
                    sEquipAnimTimer = 0;
                    sEquipState = 3;
                    sEquipMoveTimer = 10;

                    if ((pauseCtx->equipTargetItem == ITEM_ARROW_FIRE) ||
                        (pauseCtx->equipTargetItem == ITEM_ARROW_ICE) ||
                        (pauseCtx->equipTargetItem == ITEM_ARROW_LIGHT)) {
                        index = 0;
                        if (pauseCtx->equipTargetItem == ITEM_ARROW_ICE) {
                            index = 1;
                        }
                        if (pauseCtx->equipTargetItem == ITEM_ARROW_LIGHT) {
                            index = 2;
                        }
                        play_sound(NA_SE_SY_SET_FIRE_ARROW + index);
                        pauseCtx->equipTargetItem = 0xB5 + index;
                        pauseCtx->equipAnimAlpha = sEquipState = 0;
                        sEquipMoveTimer = 6;
                    } else {
                        play_sound(NA_SE_SY_DECIDE);
                    }
                } else if ((pauseCtx->debugEditor == DEBUG_EDITOR_NONE) && (pauseCtx->state == 6) &&
                           (pauseCtx->unk_200 == 0) && CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) &&
                           (msgCtx->msgLength == 0)) {
                    pauseCtx->unk_2B9 = 1;
                    if (pauseCtx->cursorY[PAUSE_ITEM] < 2) {
                        func_801514B0(play, 0x1700 + pauseCtx->cursorItem[PAUSE_ITEM], 3);
                    } else {
                        func_801514B0(play, 0x1700 + pauseCtx->cursorItem[PAUSE_ITEM], 1);
                    }
                }
            }
        } else {
            pauseCtx->cursorItem[PAUSE_ITEM] = PAUSE_ITEM_NONE;
        }

        if (oldCursorPoint != pauseCtx->cursorPoint[PAUSE_ITEM]) {
            play_sound(NA_SE_SY_CURSOR);
        }
    } else if ((pauseCtx->unk_200 == 3) && (pauseCtx->pageIndex == 0)) {
        pauseCtx->cursorColorSet = 2;
    }
}

s16 sCButtonPosX[] = { 660, 900, 1140 };
s16 sCButtonPosY[] = { 1100, 920, 1100 };
s32 D_8082B494 = 0;
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateItemEquip.s")
