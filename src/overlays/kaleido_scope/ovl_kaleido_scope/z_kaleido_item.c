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

s32 D_8082B3C0 = 0;

s32 D_8082B3C4 = 0;

s16 D_8082B3C8 = 10;

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
    0x0055, 0x0075, 0x0075, 0x0075, 0x0075, 0x0075, 0x0096, 0x0096, 0x00FF, 0x0064,
    0x00FF, 0x0000, 0x0000, 0x0064, 0x00FF, 0x0000, 0x0000, 0x00FF, 0x0064, 0x0000,
};

u8 D_8082B47C[] = {
    0x35, 0x33, 0x34, 0x32, 0xFF,
};

s16 D_8082B484[] = {
    0x0294,
    0x0384,
    0x0474,
    0x0000,
};

s16 D_8082B48C[] = {
    0x044C,
    0x0398,
    0x044C,
    0x0000,
};

s32 D_8082B494[] = { 0, 0, 0 };

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

    if (!gSlotTransformReqs[((void)0, gSaveContext.save.playerForm)][gItemSlots[item]]) {
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

void func_8081B6EC(GraphicsContext* gfxCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081B6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081BCA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081C684.s")
