/*
 * File: z_en_girla.c
 * Overlay: obj_En_Girla
 * Description: Shop Items
 */

#include "z_en_girla.h"

#define FLAGS 0x00000019

#define THIS ((EnGirlA*)thisx)

void EnGirlA_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808649C8(Actor* thisx, GlobalContext* globalCtx);

void func_80864774(EnGirlA* this, GlobalContext* globalCtx);
void func_808648F8(EnGirlA* this, GlobalContext* globalCtx);

s32 func_80863950(GlobalContext* globalCtx, EnGirlA* this);
s32 func_808639B0(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863A10(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863AAC(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863B4C(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863C08(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863C6C(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863D28(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863D60(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863DC8(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863E48(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863EC8(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80863F94(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80864034(GlobalContext* globalCtx, EnGirlA* this);
s32 func_8086406C(GlobalContext* globalCtx, EnGirlA* this);
s32 func_808640A4(GlobalContext* globalCtx, EnGirlA* this);
s32 func_80864108(GlobalContext* globalCtx, EnGirlA* this);

void func_80864168(GlobalContext* globalCtx, EnGirlA* this);
void func_80864210(GlobalContext* globalCtx, EnGirlA* this);
void func_8086425C(GlobalContext* globalCtx, EnGirlA* this);
void func_808642D4(GlobalContext* globalCtx, EnGirlA* this);
void func_80864320(GlobalContext* globalCtx, EnGirlA* this);
void func_8086436C(GlobalContext* globalCtx, EnGirlA* this);
void func_808643B8(GlobalContext* globalCtx, EnGirlA* this);
void func_8086444C(GlobalContext* globalCtx, EnGirlA* this);
void func_808644A4(GlobalContext* globalCtx, EnGirlA* this);
void func_80864558(GlobalContext* globalCtx, EnGirlA* this);
void func_808645A4(GlobalContext* globalCtx, EnGirlA* this);
void func_80864658(GlobalContext* globalCtx, EnGirlA* this);
void func_808646A4(GlobalContext* globalCtx, EnGirlA* this);

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
    { OBJECT_GI_LIQUID, 0X31, func_800B8050, 1, 0X083F, 0X0840, 0X5B, func_80863950, func_80864168, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X30, func_800B8050, 1, 0X0841, 0X0842, 0X5C, func_808639B0, func_80864168, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X32, func_800B8050, 1, 0X0843, 0X0844, 0X5D, func_80863A10, func_80864168, func_808646A4 },
    { OBJECT_GI_BOTTLE_04, 0X3B, func_800B8050, 1, 0X06B6, 0X06B7, 0X5E, func_80864108, func_80864168, func_808646A4 },
    { OBJECT_GI_ARROW, 0X25, func_800B8050, 50, 0X06BA, 0X06BB, 0X20, func_80863AAC, func_80864210, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X30, func_800B8050, 1, 0X06B2, 0X06B3, 0X5C, func_808639B0, func_80864168, func_808646A4 },
    { OBJECT_GI_SHIELD_2, 0X27, func_800B8050, 1, 0X06AE, 0X06AF, 0X32, func_80863C08, func_808642D4, func_808646A4 },
    { OBJECT_GI_STICK, 0X1A, NULL, 1, 0X06B4, 0X06B5, 0X19, func_80863C6C, func_80864320, func_808646A4 },
    { OBJECT_GI_ARROW, 0X24, func_800B8050, 30, 0X06B8, 0X06B9, 0X1F, func_80863AAC, func_80864210, func_808646A4 },
    { OBJECT_GI_NUTS, 0X11, func_800B8118, 10, 0X06B0, 0X06B1, 0X2A, func_80863B4C, func_8086425C, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X31, func_800B8050, 1, 0X06AC, 0X06AD, 0X5B, func_80863950, func_80864168, func_808646A4 },
    { OBJECT_GI_BOTTLE_04, 0X3B, func_800B8050, 1, 0X06D3, 0X06D4, 0X5E, func_80864108, func_80864168, func_808646A4 },
    { OBJECT_GI_ARROW, 0X24, func_800B8050, 30, 0X06D5, 0X06D6, 0X1F, func_80863AAC, func_80864210, func_808646A4 },
    { OBJECT_GI_ARROW, 0X25, func_800B8050, 50, 0X06D7, 0X06D8, 0X20, func_80863AAC, func_80864210, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X30, func_800B8050, 1, 0X06CF, 0X06D0, 0X5C, func_808639B0, func_80864168, func_808646A4 },
    { OBJECT_GI_NUTS, 0X11, func_800B8118, 10, 0X06CD, 0X06CE, 0X2A, func_80863B4C, func_8086425C, func_808646A4 },
    { OBJECT_GI_STICK, 0X1A, NULL, 1, 0X06D1, 0X06D2, 0X19, func_80863C6C, func_80864320, func_808646A4 },
    { OBJECT_GI_SHIELD_2, 0X27, func_800B8050, 1, 0X06CB, 0X06CC, 0X32, func_80863C08, func_808642D4, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X31, func_800B8050, 1, 0X06C9, 0X06CA, 0X5B, func_80863950, func_80864168, func_808646A4 },
    { OBJECT_GI_MASK06, 0X10, func_800B8050, 1, 0X29D9, 0X29DA, 0X7E, func_80863D28, func_8086436C, func_808646A4 },
    { OBJECT_GI_BOMBPOUCH, 0X17, func_800B8050, 1, 0X29DB, 0X29DC, 0X1B, func_80863D60, func_808643B8, func_808646A4 },
    { OBJECT_GI_BOMBPOUCH, 0X18, func_800B8050, 2, 0X29DB, 0X29DC, 0X1C, func_80863D60, func_808643B8, func_808646A4 },
    { OBJECT_GI_BOMBPOUCH, 0X19, func_800B8050, 3, 0X29DB, 0X29DC, 0X1D, func_80863D60, func_808643B8, func_808646A4 },
    { OBJECT_GI_BOMBPOUCH, 0X17, func_800B8050, 1, 0X0654, 0X0655, 0X1B, func_80863DC8, func_808643B8, func_808646A4 },
    { OBJECT_GI_BOMBPOUCH, 0X18, func_800B8050, 2, 0X0656, 0X0657, 0X1C, func_80863E48, func_808643B8, func_808646A4 },
    { OBJECT_GI_BOMB_2, 0X26, func_800B8050, 10, 0X0652, 0X0653, 0X1A, func_80863EC8, func_8086444C, func_808646A4 },
    { OBJECT_GI_BOMB_1, 0X1E, func_800B8050, 10, 0X0650, 0X0651, 0X16, func_80863F94, func_808644A4, func_808646A4 },
    { OBJECT_GI_SHIELD_2, 0X27, func_800B8050, 1, 0X12DB, 0X12DC, 0X32, func_80863C08, func_808642D4, func_808646A4 },
    { OBJECT_GI_ARROW, 0X23, func_800B8050, 10, 0X12DD, 0X12DE, 0X1E, func_80863AAC, func_80864210, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X31, func_800B8050, 1, 0X12DF, 0X12E0, 0X5B, func_80863950, func_80864168, func_808646A4 },
    { OBJECT_GI_BOMB_1, 0X1E, func_800B8050, 10, 0X0BC5, 0X0BC6, 0X16, func_80863F94, func_808644A4, func_808646A4 },
    { OBJECT_GI_ARROW, 0X23, func_800B8050, 10, 0X0BC7, 0X0BC8, 0X1E, func_80863AAC, func_80864210, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X31, func_800B8050, 1, 0X0BC9, 0X0BCA, 0X5B, func_80863950, func_80864168, func_808646A4 },
    { OBJECT_GI_BOMB_1, 0X1E, func_800B8050, 10, 0X0BCB, 0X0BCC, 0X16, func_80863F94, func_808644A4, func_808646A4 },
    { OBJECT_GI_ARROW, 0X23, func_800B8050, 10, 0X0BCD, 0X0BCE, 0X1E, func_80863AAC, func_80864210, func_808646A4 },
    { OBJECT_GI_LIQUID, 0X31, func_800B8050, 1, 0X0BCF, 0X0BD0, 0X5B, func_80863950, func_80864168, func_808646A4 },
    { OBJECT_GI_BOTTLE, 0X00, func_800B8050, 1, 0X29F8, 0X29F9, 0XA9, func_80864034, func_80864558, func_808646A4 },
    { OBJECT_GI_SWORD_4, 0X68, func_800B8050, 4, 0X29F2, 0X29F3, 0X9B, func_8086406C, func_808645A4, func_808646A4 },
    { OBJECT_GI_SWORD_1, 0X55, func_800B8050, 1, 0X29F4, 0X29F5, 0X9C, func_8086406C, func_808645A4, func_808646A4 },
    { OBJECT_GI_SWORD_2, 0X66, func_800B8050, 2, 0X29F4, 0X29F5, 0X9D, func_8086406C, func_808645A4, func_808646A4 },
    { OBJECT_GI_SWORD_3, 0X67, func_800B8050, 3, 0X29F4, 0X29F5, 0X9E, func_8086406C, func_808645A4, func_808646A4 },
    { OBJECT_GI_SHIELD_2, 0X27, func_800B8050, 1, 0X29F6, 0X29F7, 0X9F, func_80863C08, func_808642D4, func_808646A4 },
    { OBJECT_GI_SHIELD_3, 0X33, func_800B8050, 1, 0X29F6, 0X29F7, 0X33, func_808640A4, func_80864658, func_808646A4 },
};

void func_80863870(EnGirlA* this, EnGirlAActionFunc action) {
    this->actionFunc = action;
}

void func_8086387C(EnGirlA* this, GlobalContext* globalCtx) {
    s16 params = this->actor.params;

    //! @bug: Condition is impossible
    if (params >= 43 && params < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->objIndex = Object_GetIndex(&globalCtx->objectCtx, sShopItemEntries[params].objectId);
    if (this->objIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.params = params;
    this->mainActionFunc = func_80864774;
}

void EnGirlA_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnGirlA* this = THIS;

    func_8086387C(this, globalCtx);
}

void EnGirlA_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

s32 func_80863950(GlobalContext* globalCtx, EnGirlA* this) {
    if (!func_80114E90()) {
        return 3;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_808639B0(GlobalContext* globalCtx, EnGirlA* this) {
    if (!func_80114E90()) {
        return 3;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863A10(GlobalContext* globalCtx, EnGirlA* this) {
    if (!(gSaveContext.weekEventReg[53] & 8)) {
        return 5;
    }
    if (!func_80114E90()) {
        return 3;
    }
    if (!(gSaveContext.weekEventReg[53] & 16)) {
        return 1;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863AAC(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_UPG_VALUE(0x0) == 0) {
        return 6;
    }
    if (AMMO(0x1) >= CUR_CAPACITY(0x0)) {
        return 7;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863B4C(GlobalContext* globalCtx, EnGirlA* this) {
    if (CUR_CAPACITY(0x7) != 0 && AMMO(0x9) >= CUR_CAPACITY(0x7)) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    if (func_80114978(0x9) == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_80863C08(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_EQUIP_VALUE(0x1) != 0) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80863C6C(GlobalContext* globalCtx, EnGirlA* this) {
    if (CUR_CAPACITY(0x6) != 0 && AMMO(0x8) >= CUR_CAPACITY(0x6)) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    if (func_80114978(0x8) == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_80863D28(GlobalContext* globalCtx, EnGirlA* this) {
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863D60(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_UPG_VALUE(0x1) >= 2) {
        return 5;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863DC8(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_UPG_VALUE(0x1) == 1) {
        return 8;
    }
    if (VOID_CUR_UPG_VALUE(0x1) >= 2) {
        return 9;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80863E48(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_UPG_VALUE(0x1) == 2) {
        return 8;
    }
    if (VOID_CUR_UPG_VALUE(0x1) == 3) {
        return 9;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80863EC8(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_UPG_VALUE(0x1) == 0) {
        return 5;
    }
    if (AMMO(0x7) >= CUR_CAPACITY(0x1)) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    if (func_80114978(7) == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_80863F94(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_UPG_VALUE(0x1) == 0) {
        return 5;
    }
    if (AMMO(0x6) >= CUR_CAPACITY(0x1)) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80864034(GlobalContext* globalCtx, EnGirlA* this) {
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_8086406C(GlobalContext* globalCtx, EnGirlA* this) {
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_808640A4(GlobalContext* globalCtx, EnGirlA* this) {
    if (VOID_CUR_EQUIP_VALUE(0x1) != 0) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80864108(GlobalContext* globalCtx, EnGirlA* this) {
    if (!func_80114E90()) {
        return 3;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

void func_80864168(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->actor.params) {
        case 0:
        case 10:
        case 18:
        case 29:
        case 32:
        case 35:
            Item_Give(globalCtx, 0x13);
            break;
        case 1:
        case 5:
        case 14:
            Item_Give(globalCtx, 0x14);
            break;
        case 2:
            Item_Give(globalCtx, 0x15);
            break;
        case 3:
        case 11:
            Item_Give(globalCtx, 0x16);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_80864210(GlobalContext* globalCtx, EnGirlA* this) {
    func_80115A14(1, this->itemParams);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_8086425C(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->itemParams) {
        case 5:
            Item_Give(globalCtx, 0x8D);
            break;
        case 10:
            Item_Give(globalCtx, 0x8E);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808642D4(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, 0x51);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_80864320(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, 0x8);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_8086436C(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, 0x38);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808643B8(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->itemParams) {
        case 20:
            Item_Give(globalCtx, 0x56);
            break;
        case 21:
            Item_Give(globalCtx, 0x57);
            break;
        case 22:
            Item_Give(globalCtx, 0x58);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_8086444C(GlobalContext* globalCtx, EnGirlA* this) {
    if (this->itemParams == 10) {
        Item_Give(globalCtx, 0x98);
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808644A4(GlobalContext* globalCtx, EnGirlA* this) {
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

void func_80864558(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, 0x12);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808645A4(GlobalContext* globalCtx, EnGirlA* this) {
    switch (this->itemParams) {
        case 1:
            Item_Give(globalCtx, 0x4D);
            break;
        case 2:
            Item_Give(globalCtx, 0x4E);
            break;
        case 3:
            Item_Give(globalCtx, 0x4F);
            break;
        case 4:
            Item_Give(globalCtx, 0x10);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_80864658(GlobalContext* globalCtx, EnGirlA* this) {
    Item_Give(globalCtx, 0x52);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808646A4(GlobalContext* globalCtx, EnGirlA* this) {
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808646E4(EnGirlA* this, GlobalContext* globalCtx) {
}

void func_808646F4(GlobalContext* globalCtx, EnGirlA* this) {
    ShopItemEntry* shopItem = &sShopItemEntries[this->actor.params];

    this->actor.textId = shopItem->descriptionTextId;
    this->unk1A0 = 0;
    this->actor.draw = func_808649C8;
}

void func_8086472C(GlobalContext* globalCtx, EnGirlA* this) {
    this->unk1A0 = 1;
    this->actor.draw = NULL;
}

void func_80864744(GlobalContext* globalCtx, EnGirlA* this) {
    this->unk1A0 = 0;
    this->actor.draw = func_808649C8;
}

s32 func_80864760(EnGirlA* this, GlobalContext* globalCtx) {
    return false;
}

void func_80864774(EnGirlA* this, GlobalContext* globalCtx) {
    s16 params = this->actor.params;
    ShopItemEntry* shopItem = &sShopItemEntries[params];

    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex) != 0) {
        this->actor.flags &= ~0x10;
        this->actor.objBankIndex = this->objIndex;
        this->actor.textId = shopItem->descriptionTextId;
        this->choiceTextId = shopItem->choiceTextId;

        // func_80864760 always returns false
        if (!func_80864760(this, globalCtx)) {
            func_808646F4(globalCtx, this);
        }

        this->unk1A4Func = func_8086472C;
        this->unk1A8Func = func_80864744;
        this->getItemId = shopItem->getItemId;
        this->unk1B4Func = shopItem->unk14Func;
        this->unk1B8Func = shopItem->unk18Func;
        this->unk1BCFunc = shopItem->unk1CFunc;
        this->unk1C0 = 0;
        this->itemParams = shopItem->params;
        this->drawFunc = shopItem->drawFunc;
        this->getItemDrawId = shopItem->getItemDrawId;
        this->actor.flags &= ~1;
        Actor_SetScale(&this->actor, 0.25f);
        this->actor.shape.yOffset = 24.0f;
        this->actor.shape.shadowScale = 4.0f;
        this->actor.floorHeight = this->actor.home.pos.y;
        this->actor.gravity = 0.0f;
        func_80863870(this, func_808646E4);
        this->unk194 = 1;
        this->mainActionFunc = func_808648F8;
        this->unk1AC = 0;
        this->rotY = 0;
        this->unk1AE = this->actor.shape.rot.y;
    }
}

void func_808648F8(EnGirlA* this, GlobalContext* globalCtx) {
    Actor_SetScale(&this->actor, 0.25f);
    this->actor.shape.yOffset = 24.0f;
    this->actor.shape.shadowScale = 4.0f;
    func_80864760(this, globalCtx);
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, 5.0f);
    this->actor.shape.rot.x = 0;
    if (this->unk1AC != 0) {
        this->rotY += 500;
    } else {
        Math_SmoothStepToS(&this->rotY, 0, 10, 2000, 0);
    }
}

void EnGirlA_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnGirlA* this = THIS;

    this->mainActionFunc(this, globalCtx);
}

void func_808649C8(Actor* thisx, GlobalContext* globalCtx) {
    EnGirlA* this = THIS;

    Matrix_RotateY(this->rotY, MTXMODE_APPLY);
    if (this->drawFunc != NULL) {
        this->drawFunc(&this->actor, globalCtx, 0);
    }
    GetItem_Draw(globalCtx, this->getItemDrawId);
}
