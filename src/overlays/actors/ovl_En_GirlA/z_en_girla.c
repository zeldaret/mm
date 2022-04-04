/*
 * File: z_en_girla.c
 * Overlay: obj_En_Girla
 * Description: Shop Items
 */

#include "z_en_girla.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnGirlA*)thisx)

void EnGirlA_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnGirlA_InitalUpdate(EnGirlA* this, GlobalContext* globalCtx);
void EnGirlA_Update2(EnGirlA* this, GlobalContext* globalCtx);

s32 EnGirlA_CanBuyPotionRed(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyPotionGreen(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyPotionBlue(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyArrows(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyNuts(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyShieldHero(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyStick(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyMaskAllNight(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyBombBagCuriosityShop(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyBombBag20BombShop(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyBombBag30BombShop(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyBombchus(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyBombs(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyBottle(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuySword(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyShieldMirror(GlobalContext* globalCtx, EnGirlA* this);
s32 EnGirlA_CanBuyFairy(GlobalContext* globalCtx, EnGirlA* this);

void EnGirlA_BuyBottleItem(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyArrows(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyNuts(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyShieldHero(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyStick(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyMaskAllNight(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyBombBag(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyBombchus(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyBombs(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyBottle(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuySword(GlobalContext* globalCtx, EnGirlA* this);
void EnGirlA_BuyShieldMirror(GlobalContext* globalCtx, EnGirlA* this);

void EnGirlA_BuyFanfare(GlobalContext* globalCtx, EnGirlA* this);

const ActorInit En_GirlA_InitVars = {
    ACTOR_EN_GIRLA,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGirlA),
    (ActorFunc)EnGirlA_Init,
    (ActorFunc)EnGirlA_Destroy,
    (ActorFunc)EnGirlA_Update,
    (ActorFunc)NULL,
};

static ShopItemEntry sShopItemEntries[] = {
    { OBJECT_GI_LIQUID, GID_POTION_RED, func_800B8050, 1, 0X083F, 0X0840, GI_POTION_RED, EnGirlA_CanBuyPotionRed,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_GREEN, func_800B8050, 1, 0X0841, 0X0842, GI_POTION_GREEN, EnGirlA_CanBuyPotionGreen,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_BLUE, func_800B8050, 1, 0X0843, 0X0844, GI_POTION_BLUE, EnGirlA_CanBuyPotionBlue,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOTTLE_04, GID_FAIRY, func_800B8050, 1, 0X06B6, 0X06B7, GI_FAIRY, EnGirlA_CanBuyFairy,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_ARROW, GID_ARROWS_LARGE, func_800B8050, 50, 0X06BA, 0X06BB, GI_ARROWS_40, EnGirlA_CanBuyArrows,
      EnGirlA_BuyArrows, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_GREEN, func_800B8050, 1, 0X06B2, 0X06B3, GI_POTION_GREEN, EnGirlA_CanBuyPotionGreen,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, func_800B8050, 1, 0X06AE, 0X06AF, GI_SHIELD_HERO, EnGirlA_CanBuyShieldHero,
      EnGirlA_BuyShieldHero, EnGirlA_BuyFanfare },
    { OBJECT_GI_STICK, GID_STICK, NULL, 1, 0X06B4, 0X06B5, GI_STICKS_1, EnGirlA_CanBuyStick, EnGirlA_BuyStick,
      EnGirlA_BuyFanfare },
    { OBJECT_GI_ARROW, GID_ARROWS_MEDIUM, func_800B8050, 30, 0X06B8, 0X06B9, GI_ARROWS_30, EnGirlA_CanBuyArrows,
      EnGirlA_BuyArrows, EnGirlA_BuyFanfare },
    { OBJECT_GI_NUTS, GID_NUTS, func_800B8118, 10, 0X06B0, 0X06B1, GI_NUTS_10, EnGirlA_CanBuyNuts, EnGirlA_BuyNuts,
      EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_RED, func_800B8050, 1, 0X06AC, 0X06AD, GI_POTION_RED, EnGirlA_CanBuyPotionRed,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOTTLE_04, GID_FAIRY, func_800B8050, 1, 0X06D3, 0X06D4, GI_FAIRY, EnGirlA_CanBuyFairy,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_ARROW, GID_ARROWS_MEDIUM, func_800B8050, 30, 0X06D5, 0X06D6, GI_ARROWS_30, EnGirlA_CanBuyArrows,
      EnGirlA_BuyArrows, EnGirlA_BuyFanfare },
    { OBJECT_GI_ARROW, GID_ARROWS_LARGE, func_800B8050, 50, 0X06D7, 0X06D8, GI_ARROWS_40, EnGirlA_CanBuyArrows,
      EnGirlA_BuyArrows, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_GREEN, func_800B8050, 1, 0X06CF, 0X06D0, GI_POTION_GREEN, EnGirlA_CanBuyPotionGreen,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_NUTS, GID_NUTS, func_800B8118, 10, 0X06CD, 0X06CE, GI_NUTS_10, EnGirlA_CanBuyNuts, EnGirlA_BuyNuts,
      EnGirlA_BuyFanfare },
    { OBJECT_GI_STICK, GID_STICK, NULL, 1, 0X06D1, 0X06D2, GI_STICKS_1, EnGirlA_CanBuyStick, EnGirlA_BuyStick,
      EnGirlA_BuyFanfare },
    { OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, func_800B8050, 1, 0X06CB, 0X06CC, GI_SHIELD_HERO, EnGirlA_CanBuyShieldHero,
      EnGirlA_BuyShieldHero, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_RED, func_800B8050, 1, 0X06C9, 0X06CA, GI_POTION_RED, EnGirlA_CanBuyPotionRed,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_MASK06, GID_MASK_ALL_NIGHT, func_800B8050, 1, 0X29D9, 0X29DA, GI_MASK_ALL_NIGHT,
      EnGirlA_CanBuyMaskAllNight, EnGirlA_BuyMaskAllNight, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_20, func_800B8050, 1, 0X29DB, 0X29DC, GI_BOMB_BAG_20,
      EnGirlA_CanBuyBombBagCuriosityShop, EnGirlA_BuyBombBag, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_30, func_800B8050, 2, 0X29DB, 0X29DC, GI_BOMB_BAG_30,
      EnGirlA_CanBuyBombBagCuriosityShop, EnGirlA_BuyBombBag, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_40, func_800B8050, 3, 0X29DB, 0X29DC, GI_BOMB_BAG_40,
      EnGirlA_CanBuyBombBagCuriosityShop, EnGirlA_BuyBombBag, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_20, func_800B8050, 1, 0X0654, 0X0655, GI_BOMB_BAG_20,
      EnGirlA_CanBuyBombBag20BombShop, EnGirlA_BuyBombBag, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMBPOUCH, GID_BOMB_BAG_30, func_800B8050, 2, 0X0656, 0X0657, GI_BOMB_BAG_30,
      EnGirlA_CanBuyBombBag30BombShop, EnGirlA_BuyBombBag, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMB_2, GID_BOMBCHU, func_800B8050, 10, 0X0652, 0X0653, GI_BOMBCHUS_10, EnGirlA_CanBuyBombchus,
      EnGirlA_BuyBombchus, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMB_1, GID_BOMB, func_800B8050, 10, 0X0650, 0X0651, GI_BOMBS_10, EnGirlA_CanBuyBombs, EnGirlA_BuyBombs,
      EnGirlA_BuyFanfare },
    { OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, func_800B8050, 1, 0X12DB, 0X12DC, GI_SHIELD_HERO, EnGirlA_CanBuyShieldHero,
      EnGirlA_BuyShieldHero, EnGirlA_BuyFanfare },
    { OBJECT_GI_ARROW, GID_ARROWS_SMALL, func_800B8050, 10, 0X12DD, 0X12DE, GI_ARROWS_10, EnGirlA_CanBuyArrows,
      EnGirlA_BuyArrows, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_RED, func_800B8050, 1, 0X12DF, 0X12E0, GI_POTION_RED, EnGirlA_CanBuyPotionRed,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMB_1, GID_BOMB, func_800B8050, 10, 0X0BC5, 0X0BC6, GI_BOMBS_10, EnGirlA_CanBuyBombs, EnGirlA_BuyBombs,
      EnGirlA_BuyFanfare },
    { OBJECT_GI_ARROW, GID_ARROWS_SMALL, func_800B8050, 10, 0X0BC7, 0X0BC8, GI_ARROWS_10, EnGirlA_CanBuyArrows,
      EnGirlA_BuyArrows, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_RED, func_800B8050, 1, 0X0BC9, 0X0BCA, GI_POTION_RED, EnGirlA_CanBuyPotionRed,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOMB_1, GID_BOMB, func_800B8050, 10, 0X0BCB, 0X0BCC, GI_BOMBS_10, EnGirlA_CanBuyBombs, EnGirlA_BuyBombs,
      EnGirlA_BuyFanfare },
    { OBJECT_GI_ARROW, GID_ARROWS_SMALL, func_800B8050, 10, 0X0BCD, 0X0BCE, GI_ARROWS_10, EnGirlA_CanBuyArrows,
      EnGirlA_BuyArrows, EnGirlA_BuyFanfare },
    { OBJECT_GI_LIQUID, GID_POTION_RED, func_800B8050, 1, 0X0BCF, 0X0BD0, GI_POTION_RED, EnGirlA_CanBuyPotionRed,
      EnGirlA_BuyBottleItem, EnGirlA_BuyFanfare },
    { OBJECT_GI_BOTTLE, GID_BOTTLE, func_800B8050, 1, 0X29F8, 0X29F9, GI_BOTTLE, EnGirlA_CanBuyBottle,
      EnGirlA_BuyBottle, EnGirlA_BuyFanfare },
    { OBJECT_GI_SWORD_4, GID_SWORD_GREAT_FAIRY, func_800B8050, 4, 0X29F2, 0X29F3, GI_SWORD_GREAT_FAIRY,
      EnGirlA_CanBuySword, EnGirlA_BuySword, EnGirlA_BuyFanfare },
    { OBJECT_GI_SWORD_1, GID_SWORD_KOKIRI, func_800B8050, 1, 0X29F4, 0X29F5, GI_SWORD_KOKIRI, EnGirlA_CanBuySword,
      EnGirlA_BuySword, EnGirlA_BuyFanfare },
    { OBJECT_GI_SWORD_2, GID_SWORD_RAZOR, func_800B8050, 2, 0X29F4, 0X29F5, GI_SWORD_RAZOR, EnGirlA_CanBuySword,
      EnGirlA_BuySword, EnGirlA_BuyFanfare },
    { OBJECT_GI_SWORD_3, GID_SWORD_GILDED, func_800B8050, 3, 0X29F4, 0X29F5, GI_SWORD_GILDED, EnGirlA_CanBuySword,
      EnGirlA_BuySword, EnGirlA_BuyFanfare },
    { OBJECT_GI_SHIELD_2, GID_SHIELD_HERO, func_800B8050, 1, 0X29F6, 0X29F7, GI_SHIELD_HERO_2, EnGirlA_CanBuyShieldHero,
      EnGirlA_BuyShieldHero, EnGirlA_BuyFanfare },
    { OBJECT_GI_SHIELD_3, GID_SHIELD_MIRROR, func_800B8050, 1, 0X29F6, 0X29F7, GI_SHIELD_MIRROR,
      EnGirlA_CanBuyShieldMirror, EnGirlA_BuyShieldMirror, EnGirlA_BuyFanfare },
};

void EnGirlA_SetupAction(EnGirlA* this, EnGirlAActionFunc action) {
    this->actionFunc = action;
}

void EnGirlA_InitObjIndex(EnGirlA* this, GlobalContext* globalCtx) {
    s16 params = this->actor.params;

    //! @bug: Condition is impossible, && should be an ||
    if (params >= SI_MAX && params < SI_POTION_RED_1) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->objIndex = Object_GetIndex(&globalCtx->objectCtx, sShopItemEntries[params].objectId);
    if (this->objIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.params = params;
    this->mainActionFunc = EnGirlA_InitalUpdate;
}

void EnGirlA_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGirlA* this = THIS;

    EnGirlA_InitObjIndex(this, globalCtx);
}

void EnGirlA_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

s32 EnGirlA_CanBuyPotionRed(GlobalContext* globalCtx, EnGirlA* this) {
    if (!Interface_HasEmptyBottle()) {
        return CANBUY_RESULT_NEED_EMPTY_BOTTLE;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyPotionGreen(GlobalContext* globalCtx, EnGirlA* this) {
    if (!Interface_HasEmptyBottle()) {
        return CANBUY_RESULT_NEED_EMPTY_BOTTLE;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyPotionBlue(GlobalContext* globalCtx, EnGirlA* this) {
    if (!(gSaveContext.save.weekEventReg[53] & 8)) {
        return CANBUY_RESULT_CANNOT_GET_NOW;
    }
    if (!Interface_HasEmptyBottle()) {
        return CANBUY_RESULT_NEED_EMPTY_BOTTLE;
    }
    if (!(gSaveContext.save.weekEventReg[53] & 0x10)) {
        return CANBUY_RESULT_SUCCESS_2;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyArrows(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_UPG_VALUE(UPG_QUIVER) == 0) {
        return CANBUY_RESULT_CANNOT_GET_NOW_2;
    }
    if (AMMO(ITEM_BOW) >= CUR_CAPACITY(UPG_QUIVER)) {
        return CANBUY_RESULT_NO_ROOM_2;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyNuts(GlobalContext* globalCtx, EnGirlA* this) {
    if (CUR_CAPACITY(UPG_NUTS) != 0 && CUR_CAPACITY(UPG_NUTS) <= AMMO(ITEM_NUT)) {
        return CANBUY_RESULT_NO_ROOM;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    if (func_80114978(ITEM_NUT) == ITEM_NONE) {
        return CANBUY_RESULT_SUCCESS_1;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyShieldHero(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_EQUIP_VALUE(EQUIP_SHIELD) != 0) {
        return CANBUY_RESULT_NO_ROOM;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_1;
}

s32 EnGirlA_CanBuyStick(GlobalContext* globalCtx, EnGirlA* this) {
    if (CUR_CAPACITY(UPG_STICKS) != 0 && AMMO(ITEM_STICK) >= CUR_CAPACITY(UPG_STICKS)) {
        return CANBUY_RESULT_NO_ROOM;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    if (func_80114978(ITEM_STICK) == ITEM_NONE) {
        return CANBUY_RESULT_SUCCESS_1;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyMaskAllNight(GlobalContext* globalCtx, EnGirlA* this) {
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyBombBagCuriosityShop(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) >= 2) {
        return CANBUY_RESULT_CANNOT_GET_NOW;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyBombBag20BombShop(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) == 1) {
        return CANBUY_RESULT_ALREADY_HAVE;
    }
    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) >= 2) {
        return CANBUY_RESULT_HAVE_BETTER;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_1;
}

s32 EnGirlA_CanBuyBombBag30BombShop(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) == 2) {
        return CANBUY_RESULT_ALREADY_HAVE;
    }
    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) == 3) {
        return CANBUY_RESULT_HAVE_BETTER;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_1;
}

s32 EnGirlA_CanBuyBombchus(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
        return CANBUY_RESULT_CANNOT_GET_NOW;
    }
    if (AMMO(ITEM_BOMBCHU) >= CUR_CAPACITY(UPG_BOMB_BAG)) {
        return CANBUY_RESULT_NO_ROOM;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    if (func_80114978(ITEM_BOMBCHU) == ITEM_NONE) {
        return CANBUY_RESULT_SUCCESS_1;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyBombs(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
        return CANBUY_RESULT_CANNOT_GET_NOW;
    }
    if (AMMO(ITEM_BOMB) >= CUR_CAPACITY(UPG_BOMB_BAG)) {
        return CANBUY_RESULT_NO_ROOM;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

s32 EnGirlA_CanBuyBottle(GlobalContext* globalCtx, EnGirlA* this) {
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_1;
}

s32 EnGirlA_CanBuySword(GlobalContext* globalCtx, EnGirlA* this) {
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_1;
}

s32 EnGirlA_CanBuyShieldMirror(GlobalContext* globalCtx, EnGirlA* this) {
    if (GET_CUR_EQUIP_VALUE(EQUIP_SHIELD) != 0) {
        return CANBUY_RESULT_NO_ROOM;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_1;
}

s32 EnGirlA_CanBuyFairy(GlobalContext* globalCtx, EnGirlA* this) {
    if (!Interface_HasEmptyBottle()) {
        return CANBUY_RESULT_NEED_EMPTY_BOTTLE;
    }
    if (gSaveContext.save.playerData.rupees < globalCtx->msgCtx.unk1206C) {
        return CANBUY_RESULT_NEED_RUPEES;
    }
    return CANBUY_RESULT_SUCCESS_2;
}

void EnGirlA_BuyBottleItem(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->actor.params) {
        case SI_POTION_RED_1:
        case SI_POTION_RED_2:
        case SI_POTION_RED_3:
        case SI_POTION_RED_4:
        case SI_POTION_RED_5:
        case SI_POTION_RED_6:
            Item_Give(globalCtx, ITEM_POTION_RED);
            break;
        case SI_POTION_GREEN_1:
        case SI_POTION_GREEN_2:
        case SI_POTION_GREEN_3:
            Item_Give(globalCtx, ITEM_POTION_GREEN);
            break;
        case SI_POTION_BLUE:
            Item_Give(globalCtx, ITEM_POTION_BLUE);
            break;
        case SI_FAIRY_1:
        case SI_FAIRY_2:
            Item_Give(globalCtx, ITEM_FAIRY);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyArrows(GlobalContext* globalCtx, EnGirlA* this) {
    func_80115A14(ITEM_BOW, this->itemParams);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyNuts(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->itemParams) {
        case 5:
            Item_Give(globalCtx, ITEM_NUTS_5);
            break;
        case 10:
            Item_Give(globalCtx, ITEM_NUTS_10);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyShieldHero(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, ITEM_SHIELD_HERO);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyStick(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, ITEM_STICK);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyMaskAllNight(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, ITEM_MASK_ALL_NIGHT);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyBombBag(GlobalContext* globalCtx, EnGirlA* this) {
    //! @bug: Bomb Bag parameters in sShopItemEntries are 1 2 3, not 20 21 22
    switch (this->itemParams) {
        case 20:
            Item_Give(globalCtx, ITEM_BOMB_BAG_20);
            break;
        case 21:
            Item_Give(globalCtx, ITEM_BOMB_BAG_30);
            break;
        case 22:
            Item_Give(globalCtx, ITEM_BOMB_BAG_40);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyBombchus(GlobalContext* globalCtx, EnGirlA* this) {
    if (this->itemParams == 10) {
        Item_Give(globalCtx, ITEM_BOMBCHUS_10);
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyBombs(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->itemParams) {
        case 5:
            Item_Give(globalCtx, ITEM_BOMBS_5);
            break;
        case 10:
            Item_Give(globalCtx, ITEM_BOMBS_10);
            break;
        case 20:
            Item_Give(globalCtx, ITEM_BOMBS_20);
            break;
        case 30:
            Item_Give(globalCtx, ITEM_BOMBS_30);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyBottle(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, ITEM_BOTTLE);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuySword(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->itemParams) {
        case 1:
            Item_Give(globalCtx, ITEM_SWORD_KOKIRI);
            break;
        case 2:
            Item_Give(globalCtx, ITEM_SWORD_RAZOR);
            break;
        case 3:
            Item_Give(globalCtx, ITEM_SWORD_GILDED);
            break;
        case 4:
            Item_Give(globalCtx, ITEM_SWORD_GREAT_FAIRY);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_BuyShieldMirror(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, ITEM_SHIELD_MIRROR);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

// Fanfare is handled by ovl_en_ossan
void EnGirlA_BuyFanfare(GlobalContext* globalCtx, EnGirlA* this) {
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void EnGirlA_DoNothing(EnGirlA* this, GlobalContext* globalCtx) {
}

void EnGirlA_InitItem(GlobalContext* globalCtx, EnGirlA* this) {
    ShopItemEntry* shopItem = &sShopItemEntries[this->actor.params];

    this->actor.textId = shopItem->descriptionTextId;
    this->isOutOfStock = false;
    this->actor.draw = EnGirlA_Draw;
}

void EnGirlA_Bought(GlobalContext* globalCtx, EnGirlA* this) {
    this->isOutOfStock = true;
    this->actor.draw = NULL;
}

void EnGirlA_Restock(GlobalContext* globalCtx, EnGirlA* this) {
    this->isOutOfStock = false;
    this->actor.draw = EnGirlA_Draw;
}

// Left over from OOT
s32 EnGirlA_TrySetMaskItemDescription(EnGirlA* this, GlobalContext* globalCtx) {
    return false;
}

void EnGirlA_InitalUpdate(EnGirlA* this, GlobalContext* globalCtx) {
    s16 params = this->actor.params;
    ShopItemEntry* shopItem = &sShopItemEntries[params];

    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex)) {
        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.objBankIndex = this->objIndex;
        this->actor.textId = shopItem->descriptionTextId;
        this->choiceTextId = shopItem->choiceTextId;

        // EnGirlA_TrySetMaskItemDescription always returns false
        if (!EnGirlA_TrySetMaskItemDescription(this, globalCtx)) {
            EnGirlA_InitItem(globalCtx, this);
        }

        this->boughtFunc = EnGirlA_Bought;
        this->restockFunc = EnGirlA_Restock;
        this->getItemId = shopItem->getItemId;
        this->canBuyFunc = shopItem->canBuyFunc;
        this->buyFunc = shopItem->buyFunc;
        this->buyFanfareFunc = shopItem->buyFanfareFunc;
        this->unk1C0 = 0;
        this->itemParams = shopItem->params;
        this->drawFunc = shopItem->drawFunc;
        this->getItemDrawId = shopItem->getItemDrawId;
        this->actor.flags &= ~ACTOR_FLAG_1;
        Actor_SetScale(&this->actor, 0.25f);
        this->actor.shape.yOffset = 24.0f;
        this->actor.shape.shadowScale = 4.0f;
        this->actor.floorHeight = this->actor.home.pos.y;
        this->actor.gravity = 0.0f;
        EnGirlA_SetupAction(this, EnGirlA_DoNothing);
        this->isInitialized = true;
        this->mainActionFunc = EnGirlA_Update2;
        this->isSelected = false;
        this->rotY = 0;
        this->initialRotY = this->actor.shape.rot.y;
    }
}

void EnGirlA_Update2(EnGirlA* this, GlobalContext* globalCtx) {
    Actor_SetScale(&this->actor, 0.25f);
    this->actor.shape.yOffset = 24.0f;
    this->actor.shape.shadowScale = 4.0f;
    EnGirlA_TrySetMaskItemDescription(this, globalCtx);
    this->actionFunc(this, globalCtx);
    Actor_SetFocus(&this->actor, 5.0f);
    this->actor.shape.rot.x = 0;
    if (this->isSelected) {
        this->rotY += 0x1F4;
    } else {
        Math_SmoothStepToS(&this->rotY, 0, 0xA, 0x7D0, 0);
    }
}

void EnGirlA_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGirlA* this = THIS;

    this->mainActionFunc(this, globalCtx);
}

void EnGirlA_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnGirlA* this = THIS;

    Matrix_RotateY(this->rotY, MTXMODE_APPLY);
    if (this->drawFunc != NULL) {
        this->drawFunc(&this->actor, globalCtx, 0);
    }
    GetItem_Draw(globalCtx, this->getItemDrawId);
}
