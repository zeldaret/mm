/*
 * File: z_item_etcetera.c
 * Overlay: ovl_Item_Etcetera
 * Description: Leftover OoT Collectible Items (bottle, key, Fire Arrow, etc.)
 */

#include "z_item_etcetera.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ItemEtcetera*)thisx)

void ItemEtcetera_Init(Actor* thisx, GlobalContext* globalCtx);
void ItemEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ItemEtcetera_Update(Actor* thisx, GlobalContext* globalCtx);

void ItemEtcetera_SetupAction(ItemEtcetera* this, ItemEtceteraActionFunc actionFunc);
void func_80920044(ItemEtcetera* this, GlobalContext* globalCtx);
void func_8092009C(ItemEtcetera* this, GlobalContext* globalCtx);
void func_809200F8(ItemEtcetera* this, GlobalContext* globalCtx);
void func_80920164(Actor* thisx, GlobalContext* globalCtx);
void func_809201BC(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Item_Etcetera_InitVars = {
    ACTOR_ITEM_ETCETERA,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ItemEtcetera),
    (ActorFunc)ItemEtcetera_Init,
    (ActorFunc)ItemEtcetera_Destroy,
    (ActorFunc)ItemEtcetera_Update,
    (ActorFunc)NULL,
};

static s16 D_80920230[] = {
    OBJECT_GI_BOTTLE, OBJECT_GI_BOTTLE, OBJECT_GI_BOTTLE,  OBJECT_GI_BOTTLE, OBJECT_GI_BOTTLE,
    OBJECT_GI_BOTTLE, OBJECT_GI_KEY,    OBJECT_GI_M_ARROW, OBJECT_GI_RUPY,   OBJECT_GI_RUPY,
    OBJECT_GI_RUPY,   OBJECT_GI_RUPY,   OBJECT_GI_HEARTS,  OBJECT_GI_KEY,
};
static s16 D_8092024C[] = {
    GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_01,
    GID_47,     GID_4F,     GID_50,     GID_51,     GID_53,     GID_13,     GID_01,
};

static s16 D_80920268[] = {
    GI_5A, GI_5A, GI_5A, GI_5A, GI_5A, GI_5A, GI_KEY_SMALL, GI_25, GI_NONE, GI_NONE, GI_NONE, GI_NONE, GI_NONE, GI_NONE,
};

void ItemEtcetera_SetupAction(ItemEtcetera* this, ItemEtceteraActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ItemEtcetera_Init(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;
    s32 pad;
    s32 params;
    s32 index;

    params = ITEMETCETERA_GET_FF(&this->actor);
    index = Object_GetIndex(&globalCtx->objectCtx, D_80920230[params]);
    if (index >= 0) {
        this->objIndex = index;
    }
    this->itemDrawIndex = D_8092024C[params];
    this->itemID = D_80920268[params];
    this->funcSetup = func_8092009C;
    this->drawFunc = func_809201BC;
    Actor_SetScale(&this->actor, 0.25f);
    ItemEtcetera_SetupAction(this, func_80920044);
    switch (params) {
        case 7:
            Actor_SetScale(&this->actor, 0.5f);
            this->actor.draw = NULL;
            this->actor.shape.yOffset = 50.0f;
            break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            Actor_SetScale(&this->actor, 0.5f);
            this->funcSetup = func_809200F8;
            this->drawFunc = func_80920164;
            this->actor.world.pos.y += 15.0f;
            break;
    }
}

void ItemEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80920044(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex)) {
        this->actor.objBankIndex = this->objIndex;
        this->actor.draw = this->drawFunc;
        this->actionFunc = this->funcSetup;
    }
}

void func_8092009C(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        Actor_PickUp(&this->actor, globalCtx, this->itemID, 30.0f, 50.0f);
    }
}

void func_809200F8(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (Flags_GetTreasure(globalCtx, ITEMETCETERA_GET_TREASURE(&this->actor))) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ItemEtcetera_Update(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;

    this->actionFunc(this, globalCtx);
}

void func_80920164(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;

    if (globalCtx->actorCtx.unk4 == 100) {
        func_800B8050(&this->actor, globalCtx, 0);
        func_800B8118(&this->actor, globalCtx, 0);
        GetItem_Draw(globalCtx, this->itemDrawIndex);
    }
}

void func_809201BC(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;

    func_800B8050(&this->actor, globalCtx, 0);
    func_800B8118(&this->actor, globalCtx, 0);
    GetItem_Draw(globalCtx, this->itemDrawIndex);
}
