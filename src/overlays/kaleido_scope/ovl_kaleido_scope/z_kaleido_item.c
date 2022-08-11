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
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawItemSelect.s")

s16 sCButtonPosX[] = { 660, 900, 1140 };
s16 sCButtonPosY[] = { 1100, 920, 1100 };
s32 D_8082B494 = 0;
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateItemEquip.s")
