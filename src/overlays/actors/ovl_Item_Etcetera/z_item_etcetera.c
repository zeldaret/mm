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

void ItemEtcetera_WaitForObject(ItemEtcetera* this, GlobalContext* globalCtx);
void func_8092009C(ItemEtcetera* this, GlobalContext* globalCtx);
void func_809200F8(ItemEtcetera* this, GlobalContext* globalCtx);
void ItemEtcetera_DrawThroughLens(Actor* thisx, GlobalContext* globalCtx);
void ItemEtcetera_Draw(Actor* thisx, GlobalContext* globalCtx);

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

static s16 sObjectIds[] = {
    OBJECT_GI_BOTTLE, OBJECT_GI_BOTTLE, OBJECT_GI_BOTTLE,  OBJECT_GI_BOTTLE, OBJECT_GI_BOTTLE,
    OBJECT_GI_BOTTLE, OBJECT_GI_KEY,    OBJECT_GI_M_ARROW, OBJECT_GI_RUPY,   OBJECT_GI_RUPY,
    OBJECT_GI_RUPY,   OBJECT_GI_RUPY,   OBJECT_GI_HEARTS,  OBJECT_GI_KEY,
};
static s16 sDrawItemIndices[] = {
    GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_BOTTLE, GID_01,
    GID_47,     GID_4F,     GID_50,     GID_51,     GID_53,     GID_13,     GID_01,
};

static s16 sGetItemIds[] = {
    GI_BOTTLE, GI_BOTTLE, GI_BOTTLE, GI_BOTTLE, GI_BOTTLE, GI_BOTTLE, GI_KEY_SMALL,
    GI_25,     GI_NONE,   GI_NONE,   GI_NONE,   GI_NONE,   GI_NONE,   GI_NONE,
};

void ItemEtcetera_SetupAction(ItemEtcetera* this, ItemEtceteraActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ItemEtcetera_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ItemEtcetera* this = THIS;
    s32 type = ITEMETCETERA_GET_FF(&this->actor);
    s32 objBankIndex = Object_GetIndex(&globalCtx->objectCtx, sObjectIds[type]);

    if (objBankIndex < 0) {
        // assert on debug
    } else {
        this->objIndex = objBankIndex;
    }
    this->giDrawId = sDrawItemIndices[type];
    this->itemID = sGetItemIds[type];
    this->futureActionFunc = func_8092009C;
    this->drawFunc = ItemEtcetera_Draw;
    Actor_SetScale(&this->actor, 0.25f);
    ItemEtcetera_SetupAction(this, ItemEtcetera_WaitForObject);
    switch (type) {
        case ITEM_ETC_ARROW_FIRE:
            Actor_SetScale(&this->actor, 0.5f);
            this->actor.draw = NULL;
            this->actor.shape.yOffset = 50.0f;
            break;
        case ITEM_ETC_RUPEE_GREEN_CHEST_GAME:
        case ITEM_ETC_RUPEE_BLUE_CHEST_GAME:
        case ITEM_ETC_RUPEE_RED_CHEST_GAME:
        case ITEM_ETC_RUPEE_PURPLE_CHEST_GAME:
        case ITEM_ETC_HEART_PIECE_CHEST_GAME:
        case ITEM_ETC_KEY_SMALL_CHEST_GAME:
            Actor_SetScale(&this->actor, 0.5f);
            this->futureActionFunc = func_809200F8;
            this->drawFunc = ItemEtcetera_DrawThroughLens;
            this->actor.world.pos.y += 15.0f;
        default:
            break;
    }
}

void ItemEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ItemEtcetera_WaitForObject(ItemEtcetera* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex)) {
        this->actor.objBankIndex = this->objIndex;
        this->actor.draw = this->drawFunc;
        this->actionFunc = this->futureActionFunc;
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
    if (Flags_GetTreasure(globalCtx, ITEMETCETERA_GET_TREASUREFLAG(&this->actor))) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ItemEtcetera_Update(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ItemEtcetera_DrawThroughLens(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;

    if (globalCtx->actorCtx.unk4 == 100) {
        func_800B8050(&this->actor, globalCtx, 0);
        func_800B8118(&this->actor, globalCtx, 0);
        GetItem_Draw(globalCtx, this->giDrawId);
    }
}

void ItemEtcetera_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* this = THIS;

    func_800B8050(&this->actor, globalCtx, 0);
    func_800B8118(&this->actor, globalCtx, 0);
    GetItem_Draw(globalCtx, this->giDrawId);
}
