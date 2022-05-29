/*
 * File: z_bg_haka_curtain.c
 * Overlay: ovl_Bg_Haka_Curtain
 * Description: Curtain That Lifts to Reveal Flat's Tomb
 */

#include "z_bg_haka_curtain.h"
#include "objects/object_haka_obj/object_haka_obj.h"

#define FLAGS (ACTOR_FLAG_10)

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
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKA_OBJ,
    sizeof(BgHakaCurtain),
    (ActorFunc)BgHakaCurtain_Init,
    (ActorFunc)BgHakaCurtain_Destroy,
    (ActorFunc)BgHakaCurtain_Update,
    (ActorFunc)BgHakaCurtain_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgHakaCurtain_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgHakaCurtain* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_haka_obj_Colheader_001588);
    if (Flags_GetClear(globalCtx, this->dyna.actor.room)) {
        func_80B6DE80(this);
        return;
    }
    func_80B6DC98(this);
}

void BgHakaCurtain_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgHakaCurtain* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80B6DC98(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DCAC;
}

void func_80B6DCAC(BgHakaCurtain* this, GlobalContext* globalCtx) {
    if (Flags_GetClear(globalCtx, this->dyna.actor.room)) {
        func_80B6DCEC(this);
    }
}

void func_80B6DCEC(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DD00;
}

void func_80B6DD00(BgHakaCurtain* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        func_80B6DD5C(this);
        return;
    }
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
}

void func_80B6DD5C(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DD70;
}

void func_80B6DD70(BgHakaCurtain* this, GlobalContext* globalCtx) {
}

void func_80B6DD80(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DD9C;
    this->dyna.actor.velocity.y = 0.0f;
}

void func_80B6DD9C(BgHakaCurtain* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.world.pos.y < this->dyna.actor.home.pos.y + 150.0f - 30.0f) {
        Math_StepToF(&this->dyna.actor.velocity.y, 1.6f, 0.12f);
    } else {
        Math_StepToF(&this->dyna.actor.velocity.y, 0.8f, 0.05f);
    }
    this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
    if (this->dyna.actor.home.pos.y + 150.0f < this->dyna.actor.world.pos.y) {
        func_80B6DE80(this);
        return;
    }
    func_800B9010(&this->dyna.actor, NA_SE_EV_CURTAIN_DOWN - SFX_FLAG);
}

void func_80B6DE80(BgHakaCurtain* this) {
    this->actionFunc = func_80B6DEA8;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 150.0f;
}

void func_80B6DEA8(BgHakaCurtain* this, GlobalContext* globalCtx) {
}

void BgHakaCurtain_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgHakaCurtain* this = THIS;
    CsCmdActorAction* actorAction;

    if (Cutscene_CheckActorAction(globalCtx, 469)) {
        actorAction = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 469)];
        if (actorAction->startFrame == globalCtx->csCtx.frames && actorAction->action == 2) {
            func_80B6DD80(this);
        }
    }
    this->actionFunc(this, globalCtx);
}

void BgHakaCurtain_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_haka_obj_DL_001410);
}
