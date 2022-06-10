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
void func_80920164(ItemEtcetera* this, GlobalContext* globalCtx);
void func_809201BC(ItemEtcetera* this, GlobalContext* globalCtx);

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

static s16 D_80920230[14] = {
    0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 0x86, 0x121, 0x13F, 0x13F, 0x13F, 0x13F, 0x96, 0x86,
};
static s16 D_8092024C[14] = { 0, 0, 0, 0, 0, 0, 1, 0x47, 0x4F, 0x50, 0x51, 0x53, 0x13, 1 };

static s16 D_80920268[20] = {
    0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x3C, 0x25,
};

void ItemEtcetera_SetupAction(ItemEtcetera* this, ItemEtceteraActionFunc actionFunc) {
    this->actionFunc3 = actionFunc;
}

void ItemEtcetera_Init(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;
    s32 pad;
    s32 params;
    s32 index;

    params = ITEMETCETERA_GET_FF(&this->actor);
    index = Object_GetIndex(&globalCtx->objectCtx, D_80920230[params]);
    if (index >= 0) {
        this->unk_14C = index;
    }
    this->unk_148 = D_8092024C[params];
    this->unk_14A = D_80920268[params];
    this->actionFunc = func_8092009C;
    this->actionFunc2 = func_809201BC;
    Actor_SetScale(&this->actor, 0.25f);
    ItemEtcetera_SetupAction(this, func_80920044);
    switch (params) {
        case 7:
            Actor_SetScale(&this->actor, 0.5f);
            this->actor.draw = NULL;
            this->actor.shape.yOffset = 50.0f;
            return;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            Actor_SetScale(&this->actor, 0.5f);
            this->actionFunc = func_809200F8;
            this->actionFunc2 = func_80920164;
            this->actor.world.pos.y += 15.0f;
            /* fallthrough */
        default:
            return;
    }
}

void ItemEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80920044(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_14C)) {
        this->actor.objBankIndex = (u8)this->unk_14C;
        this->actor.draw = (void (*)(Actor*, GlobalContext*))this->actionFunc2;
        this->actionFunc3 = this->actionFunc;
    }
}

void func_8092009C(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    Actor_PickUp(&this->actor, globalCtx, (s32)this->unk_14A, 30.0f, 50.0f);
}

void func_809200F8(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (Flags_GetTreasure(globalCtx, ITEMETCETERA_GET_TREASURE(&this->actor))) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ItemEtcetera_Update(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;

    this->actionFunc3(this, globalCtx);
}

void func_80920164(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk4 == 100) {
        func_800B8050(&this->actor, globalCtx, 0);
        func_800B8118(&this->actor, globalCtx, 0);
        GetItem_Draw(globalCtx, this->unk_148);
    }
}

void func_809201BC(ItemEtcetera* this, GlobalContext* globalCtx) {
    func_800B8050(&this->actor, globalCtx, 0);
    func_800B8118(&this->actor, globalCtx, 0);
    GetItem_Draw(globalCtx, this->unk_148);
}
