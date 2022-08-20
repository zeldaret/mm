/*
 * File: z_kaleido_mask.c
 * Overlay: ovl_kaleido_scope
 * Description: Pause Menu - Mask Page
 */

#include "z_kaleido_scope.h"

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

s16 sMaskEquipState = 0;
s16 sMaskEquipMagicArrowSlotHoldTimer = 0;
s16 sMaskEquipAnimTimer = 10;

u8 gMaskPlayerFormSlotRestrictions[PLAYER_FORM_MAX][24] = {
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

u8 D_8082B684[] = {
    0x01, 0x01, 0x00, 0x04, 0x02, 0x02, 0x01, 0x80, 0x01, 0x04, 0x02, 0x10, 0x00, 0x10, 0x02, 0x01,
    0x00, 0x08, 0x01, 0x10, 0x02, 0x04, 0x02, 0x20, 0x00, 0x40, 0x00, 0x80, 0x00, 0x02, 0x01, 0x02,
    0x00, 0x01, 0x02, 0x40, 0x01, 0x20, 0x01, 0x08, 0x00, 0x20, 0x01, 0x40, 0x02, 0x08, 0x02, 0x80,
};
s16 sMaskMagicArrowEffectsR[] = { 255, 100, 255 };
s16 sMaskMagicArrowEffectsG[] = { 0, 100, 255 };
s16 sMaskMagicArrowEffectsB[] = { 0, 255, 100 };
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_DrawMaskSelect.s")

u8 sMaskPlayerFormItems[] = {
    ITEM_MASK_FIERCE_DEITY, ITEM_MASK_GORON, ITEM_MASK_ZORA, ITEM_MASK_DEKU, ITEM_NONE,
};
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateMaskCursor.s")

s16 sMaskCButtonPosX[] = { 660, 900, 1140 };
s16 sMaskCButtonPosY[] = { 1100, 920, 1100 };
s16 sMaskEquipMagicArrowBowSlotHoldTimer = 0;
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_UpdateMaskEquip.s")
