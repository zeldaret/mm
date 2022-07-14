/*
 * File: z_kaleido_debug.c
 * Overlay: ovl_kaleido_scope
 * Description:
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

s16 sCurSection = 0;

s32 D_8082B0F4 = 0;

s16 sSectionPositions[][3] = {
    { 65, 14, 41 },   { 145, 14, 21 },  { 193, 14, 35 },  { 42, 37, 22 },   { 65, 37, 22 },   { 88, 37, 22 },
    { 111, 37, 22 },  { 134, 37, 22 },  { 157, 37, 22 },  { 42, 51, 22 },   { 65, 51, 22 },   { 88, 51, 22 },
    { 111, 51, 22 },  { 134, 51, 22 },  { 157, 51, 22 },  { 42, 65, 22 },   { 65, 65, 22 },   { 88, 65, 22 },
    { 111, 65, 22 },  { 134, 65, 22 },  { 157, 65, 22 },  { 42, 80, 22 },   { 65, 80, 22 },   { 88, 80, 22 },
    { 111, 80, 22 },  { 134, 80, 22 },  { 157, 80, 22 },  { 202, 37, 14 },  { 215, 37, 14 },  { 229, 37, 14 },
    { 243, 37, 14 },  { 257, 37, 14 },  { 271, 37, 14 },  { 202, 51, 14 },  { 215, 51, 14 },  { 229, 51, 14 },
    { 243, 51, 14 },  { 257, 51, 14 },  { 271, 51, 14 },  { 202, 65, 14 },  { 215, 65, 14 },  { 229, 65, 14 },
    { 243, 65, 14 },  { 257, 65, 14 },  { 271, 65, 14 },  { 202, 80, 14 },  { 215, 80, 14 },  { 229, 80, 14 },
    { 243, 80, 14 },  { 257, 80, 14 },  { 271, 80, 14 },  { 42, 111, 14 },  { 54, 111, 14 },  { 66, 111, 14 },
    { 78, 111, 14 },  { 114, 99, 14 },  { 142, 99, 14 },  { 188, 99, 14 },  { 202, 99, 14 },  { 216, 99, 14 },
    { 230, 99, 14 },  { 244, 99, 14 },  { 258, 99, 14 },  { 188, 113, 14 }, { 202, 113, 14 }, { 216, 113, 14 },
    { 230, 113, 14 }, { 244, 113, 14 }, { 258, 113, 14 }, { 272, 113, 14 }, { 54, 141, 14 },  { 112, 134, 14 },
    { 155, 134, 14 }, { 194, 130, 32 }, { 194, 144, 32 }, { 262, 134, 14 }, { 43, 168, 14 },  { 55, 168, 14 },
    { 67, 168, 14 },  { 79, 168, 14 },  { 127, 168, 14 }, { 139, 168, 14 }, { 151, 168, 14 }, { 163, 168, 14 },
    { 202, 168, 22 }, { 223, 168, 22 }, { 244, 168, 22 }, { 265, 168, 22 }, { 42, 202, 14 },  { 73, 202, 14 },
    { 136, 202, 38 }, { 214, 202, 74 }, { 214, 202, 74 },
};

s16 D_8082B328[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B,
    0x000C, 0x000D, 0x000E, 0x000F, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0023,
    0x003E, 0x0038, 0x0047, 0x0045, 0x0040, 0x0032, 0x003A, 0x0046, 0x0039, 0x0042, 0x0048, 0x0033,
    0x003C, 0x003D, 0x0037, 0x003F, 0x0036, 0x0034, 0x0043, 0x0041, 0x003B, 0x0044, 0x0049, 0x0035,
};

s16 D_8082B388[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x001B, 0x0033, 0x0037, 0x0038, 0x0039,
    0x0046, 0x0047, 0x0048, 0x0049, 0x004B, 0x004C, 0x0050, 0x0054, 0x0058,
};

s32 D_8082B3AC = 0;

s32 D_8082B3B0[] = { 0, 0, 0, 0 };

void KaleidoScope_DrawDebugEditorText(Gfx** gfxp) {
    GfxPrint printer;
    s32 pad[2];

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, *gfxp);

    // Rupees
    GfxPrint_SetPos(&printer, 4, 2);
    GfxPrint_SetColor(&printer, 255, 60, 0, 255);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾙﾋﾟｰ");

    // Hearts
    GfxPrint_SetPos(&printer, 15, 2);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾊｰﾄ");
    GfxPrint_SetPos(&printer, 15, 3);
    GfxPrint_Printf(&printer, "%s", "MAX");
    GfxPrint_SetPos(&printer, 21, 3);
    GfxPrint_Printf(&printer, "%s", "NOW");
    GfxPrint_SetPos(&printer, 28, 3);
    GfxPrint_Printf(&printer, "%s", "/4");

    // Items
    GfxPrint_SetPos(&printer, 4, 5);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｱ");
    GfxPrint_SetPos(&printer, 4, 6);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｲ");
    GfxPrint_SetPos(&printer, 4, 7);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾃ");
    GfxPrint_SetPos(&printer, 4, 8);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾑ");

    // Masks
    GfxPrint_SetPos(&printer, 24, 5);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾏ");
    GfxPrint_SetPos(&printer, 24, 6);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｽ");
    GfxPrint_SetPos(&printer, 24, 7);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｸ");

    // Boss (Remains)
    GfxPrint_SetPos(&printer, 4, 13);
    GfxPrint_Printf(&printer, "%s", "BOSS");

    // Sword
    GfxPrint_SetPos(&printer, 13, 13);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｹ");
    GfxPrint_SetPos(&printer, 13, 14);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾝ");

    // Shield
    GfxPrint_SetPos(&printer, 17, 13);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾀ");
    GfxPrint_SetPos(&printer, 17, 14);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾃ");

    // Ocarina (Songs)
    GfxPrint_SetPos(&printer, 21, 13);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｵｶ");
    GfxPrint_SetPos(&printer, 21, 14);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾘﾅ");

    // Schedule (Bombers Notebook)
    GfxPrint_SetPos(&printer, 4, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｽｹｼﾞｭｰﾙ");

    // Quiver
    GfxPrint_SetPos(&printer, 12, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾔ");
    GfxPrint_SetPos(&printer, 12, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾀﾃ");

    // Bomb Bag
    GfxPrint_SetPos(&printer, 16, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾎﾞﾑ");
    GfxPrint_SetPos(&printer, 16, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾌｸﾛ");

    // Gold Skulls
    GfxPrint_SetPos(&printer, 22, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｷﾝ");
    GfxPrint_SetPos(&printer, 22, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｽﾀ");

    // Heart Pieces
    GfxPrint_SetPos(&printer, 29, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾊｰﾄ");
    GfxPrint_SetPos(&printer, 29, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｶｹﾗ");
    GfxPrint_SetPos(&printer, 34, 18);
    GfxPrint_Printf(&printer, "%s", "/4");

    // Keys
    GfxPrint_SetPos(&printer, 4, 21);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｶ");
    GfxPrint_SetPos(&printer, 4, 22);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｷﾞ");

    // Map/Compass
    GfxPrint_SetPos(&printer, 12, 21);
    GfxPrint_Printf(&printer, "%s", "MAP");
    GfxPrint_SetPos(&printer, 12, 22);
    GfxPrint_Printf(&printer, "%s", "ｺﾝﾊﾟ");

    // Fairies
    GfxPrint_SetPos(&printer, 23, 21);
    GfxPrint_Printf(&printer, "%s", "ﾖｳ");
    GfxPrint_SetPos(&printer, 23, 22);
    GfxPrint_Printf(&printer, "%s", "ｾｲ");

    // Life (double defence)
    GfxPrint_SetPos(&printer, 4, 25);
    GfxPrint_Printf(&printer, "%s", "ｲ");
    GfxPrint_SetPos(&printer, 4, 26);
    GfxPrint_Printf(&printer, "%s", "ﾉ");
    GfxPrint_SetPos(&printer, 4, 27);
    GfxPrint_Printf(&printer, "%s", "ﾁ");

    // Magic
    GfxPrint_SetPos(&printer, 8, 25);
    GfxPrint_Printf(&printer, "%s", "ﾏ");
    GfxPrint_SetPos(&printer, 8, 26);
    GfxPrint_Printf(&printer, "%s", "ﾎ");
    GfxPrint_SetPos(&printer, 8, 27);
    GfxPrint_Printf(&printer, "%s", "ｳ");

    // Lottery
    GfxPrint_SetPos(&printer, 13, 25);
    GfxPrint_Printf(&printer, "%s", "ﾀｶﾗ");
    GfxPrint_SetPos(&printer, 13, 26);
    GfxPrint_Printf(&printer, "%s", "ｸｼﾞ");

    // Gold Color (Oceanside Spider House Mask Order)
    GfxPrint_SetPos(&printer, 23, 24);
    GfxPrint_Printf(&printer, "%s", "ｷﾝｲﾛ");

    // Bombers (code)
    GfxPrint_SetPos(&printer, 23, 26);
    GfxPrint_Printf(&printer, "%s", "ﾎﾞﾝ");
    GfxPrint_SetPos(&printer, 23, 27);
    GfxPrint_Printf(&printer, "%s", "ﾊﾞｰｽﾞ");

    *gfxp = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);
}

void KaleidoScope_DrawDigit(PlayState* play, s32 digit, s32 rectLeft, s32 rectTop) {
    OPEN_DISPS(play->state.gfxCtx);

    gDPLoadTextureBlock(POLY_OPA_DISP++, ((u8*)gCounterDigit0Tex + (8 * 16 * digit)), G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(POLY_OPA_DISP++, rectLeft << 2, rectTop << 2, (rectLeft + 8) << 2, (rectTop + 16) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx);
}

void KaleidoScope_DrawDebugEditor(PlayState* play) {
    Gfx* gfx;
    Gfx* gfxRef;
    s32 counterDigits[4];
    s16 slot;
    s16 j;
    s16 i;
    s32 x;
    s32 y;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C628(play->state.gfxCtx);

    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, 220);
    gDPFillRectangle(POLY_OPA_DISP++, 24, 12, 298, 228);
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);

    gfxRef = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(gfxRef);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    KaleidoScope_DrawDebugEditorText(&gfx);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(gfxRef, gfx);
    POLY_OPA_DISP = gfx;

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 0, 0, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    // Current Health Quarter (X / 4)
    KaleidoScope_DrawDigit(play, (((void)0, gSaveContext.save.playerData.health) % 16) / 4, 217, 15);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);

    // Rupees
    counterDigits[0] = counterDigits[1] = counterDigits[2] = 0;
    counterDigits[3] = gSaveContext.save.playerData.rupees;
    while (counterDigits[3] >= 1000) {
        counterDigits[0]++;
        counterDigits[3] -= 1000;
    }

    while (counterDigits[3] >= 100) {
        counterDigits[1]++;
        counterDigits[3] -= 100;
    }

    while (counterDigits[3] >= 10) {
        counterDigits[2]++;
        counterDigits[3] -= 10;
    }

    for (i = 0, x = 68; i < 4; i++, x += 9) {
        KaleidoScope_DrawDigit(play, counterDigits[i], x, 15);
    }

    // Health capacity
    counterDigits[2] = 0;
    counterDigits[3] = gSaveContext.save.playerData.healthCapacity / 0x10;
    while (counterDigits[3] >= 10) {
        counterDigits[2]++;
        counterDigits[3] -= 10;
    }

    KaleidoScope_DrawDigit(play, counterDigits[2], 145, 15);
    KaleidoScope_DrawDigit(play, counterDigits[3], 154, 15);

    // Health
    counterDigits[2] = 0;
    counterDigits[3] = gSaveContext.save.playerData.health / 0x10;
    while (counterDigits[3] >= 10) {
        counterDigits[2]++;
        counterDigits[3] -= 10;
    }

    KaleidoScope_DrawDigit(play, counterDigits[2], 195, 15);
    KaleidoScope_DrawDigit(play, counterDigits[3], 204, 15);

    // Inventory
    for (slot = 0, i = 0, y = 38; i < 4; i++, y += 14) {
        for (j = 0, x = 44; j < 6; j++, slot++, x += 23) {
            counterDigits[3] = 0;
            counterDigits[2] = 0;
            if ((slot == SLOT_BOW) || ((slot >= SLOT_BOMB) && (slot <= SLOT_NUT)) || (slot == SLOT_POWDER_KEG) ||
                (slot == SLOT_MAGIC_BEANS)) {
                counterDigits[3] = AMMO(gAmmoItems[slot]);
            } else if ((slot == SLOT_TRADE_DEED) || (slot == SLOT_TRADE_KEY_MAMA) || (slot == SLOT_TRADE_COUPLE)) {
                counterDigits[3] = gSaveContext.save.inventory.items[slot];
            } else if (slot >= SLOT_BOTTLE_1) {
                counterDigits[3] = gSaveContext.save.inventory.items[slot];
            } else if (gSaveContext.save.inventory.items[slot] != ITEM_NONE) {
                counterDigits[3] = 1;
            }

            if (counterDigits[3] != ITEM_NONE) {
                while (counterDigits[3] >= 10) {
                    counterDigits[2]++;
                    counterDigits[3] -= 10;
                }
            } else {
                counterDigits[2] = counterDigits[3] = 0;
            }

            if (counterDigits[2] != 0) {
                KaleidoScope_DrawDigit(play, counterDigits[2], x, y);
            }
            KaleidoScope_DrawDigit(play, counterDigits[3], x + 9, y);
        }
    }

    // Masks
    for (slot = 0, i = 0, y = 38; i < 4; i++, y += 14) {
        for (j = 0, x = 204; j < 6; j++, slot++, x += 14) {
            counterDigits[2] = 0;

            if (gSaveContext.save.inventory.items[SLOT_MASK_POSTMAN + slot] != ITEM_NONE) {
                counterDigits[2] = 1;
            }
            KaleidoScope_DrawDigit(play, counterDigits[2], x, y);
        }
    }

    // Boss Remains
    for (counterDigits[1] = 44, i = 0; i < 4; i++) {
        counterDigits[2] = 0;
        if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA + i)) {
            counterDigits[2] = 1;
        }
        KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 112);
        counterDigits[1] += 14;
    }

    // Sword
    KaleidoScope_DrawDigit(play, GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD), 116, 100);

    // Shield
    KaleidoScope_DrawDigit(play, GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD), 145, 100);

    // Songs
    for (counterDigits[3] = 100, j = 0, slot = 0; j < 2; j++) {
        for (counterDigits[1] = 190, i = 0; i < 6; i++, slot++) {
            counterDigits[2] = 0;
            if (CHECK_QUEST_ITEM(QUEST_SONG_SONATA + slot)) {
                counterDigits[2] = 1;
            }
            KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], counterDigits[3]);
            counterDigits[1] += 14;
        }
        counterDigits[3] += 14;
    }

    counterDigits[2] = 0;
    counterDigits[3] -= 14;
    if (CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
        counterDigits[2] = 1;
    }
    KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], counterDigits[3]);

    // Bombers Notebook
    counterDigits[2] = 0;
    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
        counterDigits[2] = 1;
    }
    KaleidoScope_DrawDigit(play, counterDigits[2], 56, 142);

    // Quiver
    KaleidoScope_DrawDigit(play, CUR_UPG_VALUE(UPG_QUIVER), 114, 134);

    // Bomb Bag
    KaleidoScope_DrawDigit(play, CUR_UPG_VALUE(UPG_BOMB_BAG), 156, 134);

    // Gold Skulls (Swamp Spider House)
    counterDigits[2] = 0;
    counterDigits[1] = 0;
    counterDigits[3] = Inventory_GetSkullTokenCount(SCENE_KINSTA1);

    while (counterDigits[3] >= 100) {
        counterDigits[3] -= 100;
        counterDigits[1]++;
    }

    while (counterDigits[3] >= 10) {
        counterDigits[3] -= 10;
        counterDigits[2]++;
    }

    KaleidoScope_DrawDigit(play, counterDigits[1], 196, 130);
    KaleidoScope_DrawDigit(play, counterDigits[2], 205, 130);
    KaleidoScope_DrawDigit(play, counterDigits[3], 214, 130);

    // Gold Skulls (Oceans Spider House)
    counterDigits[2] = 0;
    counterDigits[1] = 0;
    counterDigits[3] = Inventory_GetSkullTokenCount(SCENE_KINDAN2);

    while (counterDigits[3] >= 100) {
        counterDigits[3] -= 100;
        counterDigits[1]++;
    }

    while (counterDigits[3] >= 10) {
        counterDigits[3] -= 10;
        counterDigits[2]++;
    }

    KaleidoScope_DrawDigit(play, counterDigits[1], 196, 144);
    KaleidoScope_DrawDigit(play, counterDigits[2], 205, 144);
    KaleidoScope_DrawDigit(play, counterDigits[3], 214, 144);

    // Heart Pieces
    KaleidoScope_DrawDigit(play, (GET_SAVE_INVENTORY_QUEST_ITEMS & 0xF0000000) >> QUEST_HEART_PIECE_COUNT, 264, 134);

    // Keys
    for (counterDigits[1] = 45, i = 0; i < 4; i++) {
        counterDigits[2] = 0;

        if ((counterDigits[3] = DUNGEON_KEY_COUNT(i)) >= 0) {
            while (counterDigits[3] >= 10) {
                counterDigits[2]++;
                counterDigits[3] -= 10;
            }
        } else {
            counterDigits[2] = counterDigits[3] = 0;
        }

        KaleidoScope_DrawDigit(play, counterDigits[3], counterDigits[1], 168);
        counterDigits[1] += 12;
    }

    // Dungeon Items
    for (counterDigits[1] = 129, i = 0; i < 4; i++) {
        counterDigits[2] = gSaveContext.save.inventory.dungeonItems[i] & gEquipMasks[0];
        KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 168);
        counterDigits[1] += 12;
    }

    // Stray Fairies
    for (counterDigits[1] = 202, i = 0; i < 4; i++) {
        counterDigits[3] = gSaveContext.save.inventory.strayFairies[i];
        counterDigits[2] = counterDigits[3] / 10;
        counterDigits[3] -= counterDigits[2] * 10;
        if (counterDigits[2] != 0) {
            KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 168);
        }
        KaleidoScope_DrawDigit(play, counterDigits[3], counterDigits[1] + 9, 168);
        counterDigits[1] += 21;
    }

    // Double Defence
    KaleidoScope_DrawDigit(play, gSaveContext.save.playerData.doubleDefense, 44, 202);

    // Magic
    //! @bug should be gSaveContext.save.playerData.doubleMagic
    KaleidoScope_DrawDigit(play, gSaveContext.save.playerData.doubleDefense, 75, 202);

    // Lottery
    for (counterDigits[1] = 139, i = 0; i < 3; i++) {
        counterDigits[2] = gSaveContext.save.lotteryCodes[0][i];

        KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 184);
        counterDigits[2] = gSaveContext.save.lotteryCodes[1][i];
        KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 198);

        counterDigits[2] = gSaveContext.save.lotteryCodes[2][i];
        KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 212);

        counterDigits[1] += 12;
    }

    // Oceanside Spider House Mask Order
    for (counterDigits[1] = 217, i = 0; i < 6; i++) {
        counterDigits[2] = gSaveContext.save.spiderHouseMaskOrder[i];
        KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 186);

        counterDigits[1] += 12;
    }

    // Bombers code
    for (counterDigits[1] = 220, i = 0; i < 5; i++) {
        counterDigits[2] = gSaveContext.save.bomberCode[i];
        KaleidoScope_DrawDigit(play, counterDigits[2], counterDigits[1], 210);

        counterDigits[1] += 12;
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 200, 120);

    gDPFillRectangle(POLY_OPA_DISP++, sSectionPositions[sCurSection][0], sSectionPositions[sCurSection][1],
                     sSectionPositions[sCurSection][0] + sSectionPositions[sCurSection][2],
                     sSectionPositions[sCurSection][1] + 15);

    CLOSE_DISPS(play->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateDebugEditor.s")
