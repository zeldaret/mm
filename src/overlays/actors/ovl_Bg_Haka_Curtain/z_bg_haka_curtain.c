#include "z_bg_haka_curtain.h"

#define FLAGS 0x00000010

#define THIS ((BgHakaCurtain*)thisx)

void BgHakaCurtain_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakaCurtain_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakaCurtain_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakaCurtain_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B6DC98(BgHakaCurtain* this);
void func_80B6DCAC(BgHakaCurtain* this, GlobalContext* globalCtx);
void func_80B6DCEC(BgHakaCurtain* this);
void func_80B6DD00(BgHakaCurtain* this, GlobalContext* globalCtx);
void func_80B6DD5C(BgHakaCurtain* this);
void func_80B6DD70(BgHakaCurtain* this, GlobalContext* globalCtx);
void func_80B6DD9C(BgHakaCurtain* this, GlobalContext* globalCtx);
void func_80B6DEA8(BgHakaCurtain* this, GlobalContext* globalCtx);
void func_80B6DE80(BgHakaCurtain* this);

const ActorInit Bg_Haka_Curtain_InitVars = {
    ACTOR_BG_HAKA_CURTAIN,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_HAKA_OBJ,
    sizeof(BgHakaCurtain),
    (ActorFunc)BgHakaCurtain_Init,
    (ActorFunc)BgHakaCurtain_Destroy,
    (ActorFunc)BgHakaCurtain_Update,
    (ActorFunc)BgHakaCurtain_Draw
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(unkFC, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(unk100, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(unk104, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

extern BgMeshHeader D_06001588;
extern UNK_TYPE D_06001410;

void BgHakaCurtain_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgHakaCurtain* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    BcCheck3_BgActorInit(&this->actor, 1);
    BgCheck3_LoadMesh(globalCtx, &this->actor, &D_06001588);
    if (Actor_GetRoomCleared(globalCtx, this->actor.room)) {
        func_80B6DE80(&this->actor);
        return;
    }
    func_80B6DC98(&this->actor);
}

void BgHakaCurtain_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgHakaCurtain* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dynaCollisionIndex);
}

void func_80B6DC98(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DCAC;
}

void func_80B6DCAC(BgHakaCurtain* this, GlobalContext* globalCtx) {
    if (Actor_GetRoomCleared(globalCtx, this->actor.room)) {
        func_80B6DCEC(&this->actor);
    }
}

void func_80B6DCEC(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DD00;
}

void func_80B6DD00(BgHakaCurtain* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        func_80B6DD5C(&this->actor);
        return;
    }
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
}

void func_80B6DD5C(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DD70;
}

void func_80B6DD70(BgHakaCurtain* this, GlobalContext* globalCtx) {
}

void func_80B6DD80(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DD9C;
    this->actor.velocity.y = 0.0f;
}

void func_80B6DD9C(BgHakaCurtain* this, GlobalContext* globalCtx) {
    if (this->actor.currPosRot.pos.y < this->actor.initPosRot.pos.y + 150.0f - 30.0f) {
        Lib_StepTowardsCheck_f(&this->actor.velocity.y, 1.6f, 0.12f);
    } else {
        Lib_StepTowardsCheck_f(&this->actor.velocity.y, 0.8f, 0.05f);
    }
    this->actor.currPosRot.pos.y += this->actor.velocity.y;
    if (this->actor.initPosRot.pos.y + 150.0f < this->actor.currPosRot.pos.y) {
        func_80B6DE80(this);
        return;
    }
    func_800B9010(&this->actor, 0x218D);
}

void func_80B6DE80(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DEA8;
    this->actor.currPosRot.pos.y = this->actor.initPosRot.pos.y + 150.0f;
}

void func_80B6DEA8(BgHakaCurtain* this, GlobalContext* globalCtx) {
}

void BgHakaCurtain_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgHakaCurtain* this = THIS;
    CsCmdActorAction* actorAction;

    if (func_800EE29C(globalCtx, 0x1D5)) {
        actorAction = globalCtx->csCtx.actorActions[func_800EE200(globalCtx, 0x1D5)];
        if (actorAction->startFrame == globalCtx->csCtx.frames && actorAction->unk_0 == 2) {
            func_80B6DD80(this);
        }
    }
    this->actionFunc(this, globalCtx);
}

void BgHakaCurtain_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, &D_06001410);
}
