#include "z_bg_ikana_ray.h"

#define FLAGS 0x00000000

#define THIS ((BgIkanaRay*)thisx)

void BgIkanaRay_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRay_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRay_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRay_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgIkanaRay_SetDeactivated(BgIkanaRay* this);
void BgIkanaRay_UpdateCheckForActivation(BgIkanaRay* this, GlobalContext* globalCtx);
void BgIkanaRay_SetActivated(BgIkanaRay* this);
void BgIkanaRay_UpdateActivated(BgIkanaRay* this, GlobalContext* globalCtx);

const ActorInit Bg_Ikana_Ray_InitVars = {
    ACTOR_BG_IKANA_RAY,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaRay),
    (ActorFunc)BgIkanaRay_Init,
    (ActorFunc)BgIkanaRay_Destroy,
    (ActorFunc)BgIkanaRay_Update,
    (ActorFunc)BgIkanaRay_Draw
};

// TODO better formatting
ColCylinderInit bgIkanaRayCylinderInit = {
    { 10, 33, 0, 0, 0, 1 },
    { 0, { 0x00200000, 0, 0 }, { 0, 0, 0 }, 25, 0, 1 },
    { 90, 420, 65116}
};

// TODO macro
InitChainEntry  bgIkanaRayCompInit[] = {
    {1, 6, 0x0FC, 4000},
    {1, 6, 0x100, 1000},
    {1, 6, 0x104, 1000},
    {0, 9, 0x058, 100}
};

void BgIkanaRay_Init(Actor* thisx, GlobalContext* globalCtx) {
    ColCylinder* collision = &THIS->collision;
    u32 pad;

    Actor_ProcessInitChain(thisx, bgIkanaRayCompInit);

    Collision_InitCylinderDefault(globalCtx, collision);
    Collision_InitCylinderWithData(globalCtx, collision, thisx, &bgIkanaRayCylinderInit);
    Collision_CylinderMoveToActor(thisx, &THIS->collision);

    THIS->animatedTextures = (AnimatedTexture*)Lib_PtrSegToVirt(object_ikana_obj_001228);

    if (Actor_GetSwitchFlag(globalCtx, THIS->base.params & 0x7F) != 0) {
        BgIkanaRay_SetActivated(THIS);
    } else {
        BgIkanaRay_SetDeactivated(THIS);
    }
}

void BgIkanaRay_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ColCylinder* collision = &THIS->collision;
    Collision_FiniCylinder(globalCtx, collision);
}

void BgIkanaRay_SetDeactivated(BgIkanaRay* this) {
    this->base.draw = NULL;
    this->base.flags |= 0x10;
    this->update = BgIkanaRay_UpdateCheckForActivation;
}

void BgIkanaRay_UpdateCheckForActivation(BgIkanaRay* this, GlobalContext* globalCtx) {
    if (Actor_GetSwitchFlag(globalCtx, this->base.params & 0x7F) != 0) {
        BgIkanaRay_SetActivated(this);
    }
}

void BgIkanaRay_SetActivated(BgIkanaRay* this) {
    this->base.draw = (ActorFunc)BgIkanaRay_Draw;
    this->base.flags &= 0xFFFFFFEF;
    this->update = BgIkanaRay_UpdateActivated;
}

void BgIkanaRay_UpdateActivated(BgIkanaRay* this, GlobalContext* globalCtx) {
    Collision_AddAT(globalCtx, &globalCtx->colCheckCtx, &this->collision.base);
}

void BgIkanaRay_Update(Actor* thisx, GlobalContext* globalCtx) {
    THIS->update(THIS, globalCtx);
}

void BgIkanaRay_Draw(Actor* thisx, GlobalContext* globalCtx) {
    SceneProc_DrawAllSceneAnimatedTextures(globalCtx, THIS->animatedTextures);
    func_800BE03C(globalCtx, object_ikana_obj_001100);
}
