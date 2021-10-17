#include "z_en_hs2.h"

#define FLAGS 0x00000009

#define THIS ((EnHs2*)thisx)

void EnHs2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnHs2_DoNothing(EnHs2* this, GlobalContext* globalCtx);

const ActorInit En_Hs2_InitVars = {
    ACTOR_EN_HS2,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHs2),
    (ActorFunc)EnHs2_Init,
    (ActorFunc)EnHs2_Destroy,
    (ActorFunc)EnHs2_Update,
    (ActorFunc)EnHs2_Draw,
};

void EnHs2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHs2* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = EnHs2_DoNothing;
}

void EnHs2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnHs2_DoNothing(EnHs2* this, GlobalContext* globalCtx) {
}

void EnHs2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHs2* this = THIS;

    this->actionFunc(this, globalCtx);
}

void EnHs2_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
