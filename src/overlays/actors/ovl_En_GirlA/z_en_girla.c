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

void func_808649C8(Actor* thisx, GlobalContext* globalCtx); // Draw

void func_8086387C(EnGirlA *this, GlobalContext* globalCtx);
void func_80864774(EnGirlA *this, GlobalContext* globalCtx);
void func_808646E4(EnGirlA *this, GlobalContext* globalCtx);
void func_808648F8(EnGirlA *this, GlobalContext* globalCtx);
void func_8086472C(GlobalContext *globalCtx, EnGirlA* this);
void func_80864744(GlobalContext *globalCtx, EnGirlA* this);
s32 func_80864760(EnGirlA *this, GlobalContext* globalCtx);
void func_808646F4(GlobalContext *globalCtx, EnGirlA* this);
void func_80863870(EnGirlA* this, EnGirlAActionFunc action);

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
void func_8086436C(GlobalContext *globalCtx, EnGirlA *this);
void func_808643B8(GlobalContext *globalCtx, EnGirlA *this);
void func_8086444C(GlobalContext *globalCtx, EnGirlA *this);
void func_808644A4(GlobalContext *globalCtx, EnGirlA *this);
void func_80864558(GlobalContext *globalCtx, EnGirlA *this);
void func_808645A4(GlobalContext *globalCtx, EnGirlA *this);
void func_80864658(GlobalContext *globalCtx, EnGirlA *this);
void func_808646A4(GlobalContext *globalCtx, EnGirlA *this);


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


ShopItemEntry D_80864A50[] = {
    {OBJECT_GI_LIQUID, 49, func_800B8050, 1, 0x083f, 0x0840, 91, func_80863950, func_80864168, func_808646A4},
    {OBJECT_GI_LIQUID, 48, func_800B8050, 1, 0x0841, 0x0842, 92, func_808639B0, func_80864168, func_808646A4},
    {OBJECT_GI_LIQUID, 50, func_800B8050, 1, 0x0843, 0x0844, 93, func_80863A10, func_80864168, func_808646A4},
    {OBJECT_GI_BOTTLE_04, 59, func_800B8050, 1, 0x06b6, 0x06b7, 94, func_80864108, func_80864168, func_808646A4},
    {OBJECT_GI_ARROW, 37, func_800B8050, 50, 0x06ba, 0x06bb, 32, func_80863AAC, func_80864210, func_808646A4},
    {OBJECT_GI_LIQUID, 48, func_800B8050, 1, 0x06b2, 0x06b3, 92, func_808639B0, func_80864168, func_808646A4},
    {OBJECT_GI_SHIELD_2, 39, func_800B8050, 1, 0x06ae, 0x06af, 50, func_80863C08, func_808642D4, func_808646A4},
    {OBJECT_GI_STICK, 26, NULL, 1, 0x06b4, 0x06b5, 25, func_80863C6C, func_80864320, func_808646A4},
    {OBJECT_GI_ARROW, 36, func_800B8050, 30, 0x06b8, 0x06b9, 31, func_80863AAC, func_80864210, func_808646A4},
    {OBJECT_GI_NUTS, 17, func_800B8118, 10, 0x06b0, 0x06b1, 42, func_80863B4C, func_8086425C, func_808646A4},
    {OBJECT_GI_LIQUID, 49, func_800B8050, 1, 0x06ac, 0x06ad, 91, func_80863950, func_80864168, func_808646A4},
    {OBJECT_GI_BOTTLE_04, 59, func_800B8050, 1, 0x06d3, 0x06d4, 94, func_80864108, func_80864168, func_808646A4},
    {OBJECT_GI_ARROW, 36, func_800B8050, 30, 0x06d5, 0x06d6, 31, func_80863AAC, func_80864210, func_808646A4},
    {OBJECT_GI_ARROW, 37, func_800B8050, 50, 0x06d7, 0x06d8, 32, func_80863AAC, func_80864210, func_808646A4},
    {OBJECT_GI_LIQUID, 48, func_800B8050, 1, 0x06cf, 0x06d0, 92, func_808639B0, func_80864168, func_808646A4},
    {OBJECT_GI_NUTS, 17, func_800B8118, 10, 0x06cd, 0x06ce, 42, func_80863B4C, func_8086425C, func_808646A4},
    {OBJECT_GI_STICK, 26, NULL, 1, 0x06d1, 0x06d2, 25, func_80863C6C, func_80864320, func_808646A4},
    {OBJECT_GI_SHIELD_2, 39, func_800B8050, 1, 0x06cb, 0x06cc, 50, func_80863C08, func_808642D4, func_808646A4},
    {OBJECT_GI_LIQUID, 49, func_800B8050, 1, 0x06c9, 0x06ca, 91, func_80863950, func_80864168, func_808646A4},
    {OBJECT_GI_MASK06, 16, func_800B8050, 1, 0x29d9, 0x29da, 126, func_80863D28, func_8086436C, func_808646A4},
    {OBJECT_GI_BOMBPOUCH, 23, func_800B8050, 1, 0x29db, 0x29dc, 27, func_80863D60, func_808643B8, func_808646A4},
    {OBJECT_GI_BOMBPOUCH, 24, func_800B8050, 2, 0x29db, 0x29dc, 28, func_80863D60, func_808643B8, func_808646A4},
    {OBJECT_GI_BOMBPOUCH, 25, func_800B8050, 3, 0x29db, 0x29dc, 29, func_80863D60, func_808643B8, func_808646A4},
    {OBJECT_GI_BOMBPOUCH, 23, func_800B8050, 1, 0x0654, 0x0655, 27, func_80863DC8, func_808643B8, func_808646A4},
    {OBJECT_GI_BOMBPOUCH, 24, func_800B8050, 2, 0x0656, 0x0657, 28, func_80863E48, func_808643B8, func_808646A4},
    {OBJECT_GI_BOMB_2, 38, func_800B8050, 10, 0x0652, 0x0653, 26, func_80863EC8, func_8086444C, func_808646A4},
    {OBJECT_GI_BOMB_1, 30, func_800B8050, 10, 0x0650, 0x0651, 22, func_80863F94, func_808644A4, func_808646A4},
    {OBJECT_GI_SHIELD_2, 39, func_800B8050, 1, 0x12db, 0x12dc, 50, func_80863C08, func_808642D4, func_808646A4},
    {OBJECT_GI_ARROW, 35, func_800B8050, 10, 0x12dd, 0x12de, 30, func_80863AAC, func_80864210, func_808646A4},
    {OBJECT_GI_LIQUID, 49, func_800B8050, 1, 0x12df, 0x12e0, 91, func_80863950, func_80864168, func_808646A4},
    {OBJECT_GI_BOMB_1, 30, func_800B8050, 10, 0x0bc5, 0x0bc6, 22, func_80863F94, func_808644A4, func_808646A4},
    {OBJECT_GI_ARROW, 35, func_800B8050, 10, 0x0bc7, 0x0bc8, 30, func_80863AAC, func_80864210, func_808646A4},
    {OBJECT_GI_LIQUID, 49, func_800B8050, 1, 0x0bc9, 0x0bca, 91, func_80863950, func_80864168, func_808646A4},
    {OBJECT_GI_BOMB_1, 30, func_800B8050, 10, 0x0bcb, 0x0bcc, 22, func_80863F94, func_808644A4, func_808646A4},
    {OBJECT_GI_ARROW, 35, func_800B8050, 10, 0x0bcd, 0x0bce, 30, func_80863AAC, func_80864210, func_808646A4},
    {OBJECT_GI_LIQUID, 49, func_800B8050, 1, 0x0bcf, 0x0bd0, 91, func_80863950, func_80864168, func_808646A4},
    {OBJECT_GI_BOTTLE, 0, func_800B8050, 1, 0x29f8, 0x29f9, 169, func_80864034, func_80864558, func_808646A4},
    {OBJECT_GI_SWORD_4, 104, func_800B8050, 4, 0x29f2, 0x29f3, 155, func_8086406C, func_808645A4, func_808646A4},
    {OBJECT_GI_SWORD_1, 85, func_800B8050, 1, 0x29f4, 0x29f5, 156, func_8086406C, func_808645A4, func_808646A4},
    {OBJECT_GI_SWORD_2, 102, func_800B8050, 2, 0x29f4, 0x29f5, 157, func_8086406C, func_808645A4, func_808646A4},
    {OBJECT_GI_SWORD_3, 103, func_800B8050, 3, 0x29f4, 0x29f5, 158, func_8086406C, func_808645A4, func_808646A4},
    {OBJECT_GI_SHIELD_2, 39, func_800B8050, 1, 0x29f6, 0x29f7, 159, func_80863C08, func_808642D4, func_808646A4},
    {OBJECT_GI_SHIELD_3, 51, func_800B8050, 1, 0x29f6, 0x29f7, 51, func_808640A4, func_80864658, func_808646A4},
};


void func_80863870(EnGirlA* this, EnGirlAActionFunc action) {
    this->actionFunc = action;
}

void func_8086387C(EnGirlA *this, GlobalContext *globalCtx) {
    s16 params = this->actor.params;

    //! @bug: Condition is impossible
    if (params >= 43 && params < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk18C = Object_GetIndex(&globalCtx->objectCtx, D_80864A50[params].objectId);
    if (this->unk18C < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actor.params = params;
    this->mainActionFunc = func_80864774;
}

void EnGirlA_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnGirlA *this = THIS;

    func_8086387C(this, globalCtx);
}

void EnGirlA_Destroy(Actor* thisx, GlobalContext* globalCtx){
}

s32 func_80863950(GlobalContext *globalCtx, EnGirlA *this) {
    if (!func_80114E90()) {
        return 3;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_808639B0(GlobalContext *globalCtx, EnGirlA *this) {
    if (!func_80114E90()) {
        return 3;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863A10(GlobalContext *globalCtx, EnGirlA *this) {
    if (!(gSaveContext.weekEventReg[53] & 8)) {
        return 5;
    }
    if (!func_80114E90()) {
        return 3;
    }
    if (!(gSaveContext.weekEventReg[53] & 0x10)) {
        return 1;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863AAC(GlobalContext *globalCtx, EnGirlA *this) {
    if (VOID_CUR_UPG_VALUE(0) == 0) {
        return 6;
    }
    if (AMMO(1) >= CUR_CAPACITY(0)) {
        return 7;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863B4C(GlobalContext *globalCtx, EnGirlA *this) {
    if (CUR_CAPACITY(7) != 0 && AMMO(9) >= CUR_CAPACITY(7)) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    if (func_80114978(9) == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_80863C08(GlobalContext *globalCtx, EnGirlA *this) {
    if (VOID_CUR_EQUIP_VALUE(1) != 0) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80863C6C(GlobalContext *globalCtx, EnGirlA *this) {
    if (CUR_CAPACITY(6) != 0 && AMMO(8) >= CUR_CAPACITY(6)) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    if (func_80114978(8) == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_80863D28(GlobalContext *globalCtx, EnGirlA *this) {
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863D60(GlobalContext *globalCtx, EnGirlA *this) {
    if (VOID_CUR_UPG_VALUE(1) >= 2) {
        return 5;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80863DC8(GlobalContext *globalCtx, EnGirlA *this) {
    if (VOID_CUR_UPG_VALUE(1) == 1) {
        return 8;
    }
    if (VOID_CUR_UPG_VALUE(1) >= 2) {
        return 9;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80863E48(GlobalContext *globalCtx, EnGirlA *this) {
    if (VOID_CUR_UPG_VALUE(1) == 2) {
        return 8;
    }

    if (VOID_CUR_UPG_VALUE(1) == 3) {
        return 9;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80863EC8(GlobalContext *globalCtx, EnGirlA *this) {

    if (VOID_CUR_UPG_VALUE(1) == 0) {
        return 5;
    }
    if (AMMO(7) >= CUR_CAPACITY(1)) {
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

s32 func_80863F94(GlobalContext *globalCtx, EnGirlA *this) {
    if (VOID_CUR_UPG_VALUE(1) == 0) {
        return 5;
    }
    if (AMMO(6) >= CUR_CAPACITY(1)) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

s32 func_80864034(GlobalContext *globalCtx, EnGirlA *this) {
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_8086406C(GlobalContext *globalCtx, EnGirlA *this) {
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_808640A4(GlobalContext *globalCtx, EnGirlA *this) {
    if (VOID_CUR_EQUIP_VALUE(1) != 0) {
        return 2;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 0;
}

s32 func_80864108(GlobalContext *globalCtx, EnGirlA *this) {
    if (!func_80114E90()) {
        return 3;
    }
    if (gSaveContext.rupees < globalCtx->msgCtx.unk1206C) {
        return 4;
    }
    return 1;
}

void func_80864168(GlobalContext *globalCtx, EnGirlA *this) {
    switch(this->actor.params) {
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

void func_80864210(GlobalContext *globalCtx, EnGirlA *this) {
    func_80115A14(1, this->unk1C2);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_8086425C(GlobalContext *globalCtx, EnGirlA *this) {
    switch(this->unk1C2) {
        case 5:
            Item_Give(globalCtx, 0x8D);
            break;
        case 10:
            Item_Give(globalCtx, 0x8E);
            break;
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808642D4(GlobalContext *globalCtx, EnGirlA *this) {
    Item_Give(globalCtx, 0x51);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_80864320(GlobalContext *globalCtx, EnGirlA *this) {
    Item_Give(globalCtx, 8);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_8086436C(GlobalContext *globalCtx, EnGirlA *this) {
    Item_Give(globalCtx, 0x38);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808643B8(GlobalContext *globalCtx, EnGirlA *this) {
    switch(this->unk1C2) {
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

void func_8086444C(GlobalContext *globalCtx, EnGirlA *this) {
    if (this->unk1C2 == 10) {
        Item_Give(globalCtx, 0x98);
    }
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808644A4(GlobalContext *globalCtx, EnGirlA *this) {
    switch(this->unk1C2) {
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

void func_80864558(GlobalContext *globalCtx, EnGirlA *this) {
    Item_Give(globalCtx, 0x12);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808645A4(GlobalContext *globalCtx, EnGirlA *this) {
    switch(this->unk1C2) {
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

void func_80864658(GlobalContext *globalCtx, EnGirlA *this) {
    Item_Give(globalCtx, 0x52);
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808646A4(GlobalContext *globalCtx, EnGirlA *this) {
    func_801159EC(-globalCtx->msgCtx.unk1206C);
}

void func_808646E4(EnGirlA *this, GlobalContext* globalCtx){
}

void func_808646F4(GlobalContext *globalCtx, EnGirlA *this) {
    ShopItemEntry *enGirlAUnkStruct = &D_80864A50[this->actor.params];

    this->actor.textId = enGirlAUnkStruct->descriptionTextId;
    this->unk1A0 = 0;
    this->actor.draw = func_808649C8;
}

void func_8086472C(GlobalContext *globalCtx, EnGirlA *this) {
    this->unk1A0 = 1;
    this->actor.draw = NULL;
}

void func_80864744(GlobalContext *globalCtx, EnGirlA *this) {
    this->unk1A0 = 0;
    this->actor.draw = func_808649C8;
}

s32 func_80864760(EnGirlA *this, GlobalContext* globalCtx) {
    return false;
}

void func_80864774(EnGirlA *this, GlobalContext *globalCtx) {
    s16 params = this->actor.params;
    ShopItemEntry *enGirlAUnkStruct = &D_80864A50[params];

    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk18C) != 0) {
        this->actor.flags &= -0x11;
        this->actor.objBankIndex = this->unk18C;
        this->actor.textId = enGirlAUnkStruct->descriptionTextId;
        this->unk198 = enGirlAUnkStruct->choiceTextId;

        // func_80864760 always returns false
        if (!func_80864760(this, globalCtx)) {
            func_808646F4(globalCtx, this);
        }

        this->unk1A4Func = func_8086472C;
        this->unk1A8Func = func_80864744;
        this->unk19C = enGirlAUnkStruct->unk10;
        this->unk1B4Func = enGirlAUnkStruct->unk14Func;
        this->unk1B8Func = enGirlAUnkStruct->unk18Func;
        this->unk1BCFunc = enGirlAUnkStruct->unk1CFunc;
        this->unk1C0 = 0;
        this->unk1C2 = enGirlAUnkStruct->params;
        this->drawFunc = enGirlAUnkStruct->drawFunc;
        this->unk1C4 = enGirlAUnkStruct->giDrawId;
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
        this->unk1B0 = 0;
        this->unk1AE = this->actor.shape.rot.y;
    }
}

void func_808648F8(EnGirlA *this, GlobalContext *globalCtx) {
    Actor_SetScale(&this->actor, 0.25f);
    this->actor.shape.yOffset = 24.0f;
    this->actor.shape.shadowScale = 4.0f;
    func_80864760(this, globalCtx);
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, 5.0f);
    this->actor.shape.rot.x = 0;
    if (this->unk1AC != 0) {
        this->unk1B0 += 500;
    } else {
        Math_SmoothStepToS(&this->unk1B0, 0, 10, 2000, 0);
    }
}

void EnGirlA_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnGirlA *this = THIS;

    this->mainActionFunc(this, globalCtx);
}

void func_808649C8(Actor *thisx, GlobalContext *globalCtx) {
    EnGirlA *this = THIS;

    Matrix_RotateY(this->unk1B0, MTXMODE_APPLY);
    if (this->drawFunc != NULL) {
        this->drawFunc(&this->actor, globalCtx, 0);
    }
    GetItem_Draw(globalCtx, this->unk1C4);
}
