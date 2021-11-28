/*
 * File: z_en_talk.c
 * Overlay: ovl_En_Talk
 * Description: Green Target Spot (e.g., Indigo-Go's Poster)
 */

#include "z_en_talk.h"

#define FLAGS 0x00000009

#define THIS ((EnTalk*)thisx)

void EnTalk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTalk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTalk_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80BDE058(EnTalk* this, GlobalContext* globalCtx);
void func_80BDE090(EnTalk* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Talk_InitVars = {
    ACTOR_EN_TALK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTalk),
    (ActorFunc)EnTalk_Init,
    (ActorFunc)EnTalk_Destroy,
    (ActorFunc)EnTalk_Update,
    (ActorFunc)NULL,
};

#endif

void EnTalk_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTalk* this = THIS;
    s8 temp_v0;

    temp_v0 = this->actor.home.rot.x - 0x1;

    if (temp_v0 >= 0x0 && temp_v0 < 0x7) {
        this->actor.targetMode = temp_v0;
    }

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = func_80BDE090;
    this->actor.textId = (this->actor.params & 0x3F) + 0x1C00;
}

void EnTalk_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTalk* this = THIS;
}

void func_80BDE058(EnTalk* this, GlobalContext* globalCtx) {
    if (func_800B867C(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80BDE090;
    }
}

void func_80BDE090(EnTalk* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_80BDE058;
        return;
    }

    if ((this->actor.xzDistToPlayer < 40.0f && Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx) != 0) ||
        this->actor.isTargeted) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }
}

void EnTalk_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTalk* this = THIS;
    this->actionFunc(this, globalCtx);
}
