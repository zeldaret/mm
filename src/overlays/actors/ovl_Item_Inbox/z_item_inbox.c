/*
 * File: z_item_inbox.c
 * Overlay: ovl_Item_Inbox
 * Description:
 */

#include "z_item_inbox.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((ItemInbox*)thisx)

void ItemInbox_Init(Actor* thisx, GlobalContext* globalCtx);
void ItemInbox_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ItemInbox_Update(Actor* thisx, GlobalContext* globalCtx);
void ItemInbox_Draw(Actor* thisx, GlobalContext* globalCtx);

void ItemInbox_Idle(ItemInbox* this, GlobalContext* globalCtx);

const ActorInit Item_Inbox_InitVars = {
    ACTOR_ITEM_INBOX,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ItemInbox),
    (ActorFunc)ItemInbox_Init,
    (ActorFunc)ItemInbox_Destroy,
    (ActorFunc)ItemInbox_Update,
    (ActorFunc)ItemInbox_Draw,
};

void ItemInbox_Init(Actor* thisx, GlobalContext* globalCtx) {
    ItemInbox* this = THIS;

    this->actionFunc = ItemInbox_Idle;
    Actor_SetScale(&this->actor, 0.2f);
}

void ItemInbox_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ItemInbox_Idle(ItemInbox* this, GlobalContext* globalCtx) {
    if (Flags_GetTreasure(globalCtx, (this->actor.params >> 8) & 0x1F)) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ItemInbox_Update(Actor* thisx, GlobalContext* globalCtx) {
    ItemInbox* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ItemInbox_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ItemInbox* this = THIS;

    func_800B8050(&this->actor, globalCtx, 0);
    func_800B8118(&this->actor, globalCtx, 0);
    GetItem_Draw(globalCtx, this->actor.params & 0xFF);
}
