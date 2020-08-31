#include <ultra64.h>
#include <global_overlay.h>

ActorInit bgIkanaRayInitData = {
    ACTOR_BG_IKANA_RAY,
    6,
    0,
    0,
    0x0203,
    sizeof(ActorBgIkanaRay),
    (actor_func)BgIkanaRay_Init,
    (actor_func)BgIkanaRay_Destroy,
    (actor_func)BgIkanaRay_Update,
    (actor_func)BgIkanaRay_Draw
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

void BgIkanaRay_Init(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    ColCylinder* collision = &this->collision;
    u32 pad;

    Actor_ProcessInitChain((Actor*)this, bgIkanaRayCompInit);

    Collision_InitCylinderDefault(ctxt, collision);
    Collision_InitCylinderWithData(ctxt, collision, (Actor*)this, &bgIkanaRayCylinderInit);
    Collision_CylinderMoveToActor((Actor*)this, &this->collision);

    this->animatedTextures = (AnimatedTexture*)Lib_PtrSegToVirt(object_ikana_obj_001228);

    if (Actor_GetSwitchFlag(ctxt, this->base.params & 0x7F) != 0) {
        BgIkanaRay_SetActivated(this);
    } else {
        BgIkanaRay_SetDeactivated(this);
    }
}

void BgIkanaRay_Destroy(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    ColCylinder* collision = &this->collision;
    Collision_FiniCylinder(ctxt, collision);
}

void BgIkanaRay_SetDeactivated(ActorBgIkanaRay* this) {
    this->base.draw = NULL;
    this->base.flags |= 0x10;
    this->update = (actor_func)BgIkanaRay_UpdateCheckForActivation;
}

void BgIkanaRay_UpdateCheckForActivation(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    if (Actor_GetSwitchFlag(ctxt, this->base.params & 0x7F) != 0) {
        BgIkanaRay_SetActivated(this);
    }
}

void BgIkanaRay_SetActivated(ActorBgIkanaRay* this) {
    this->base.draw = (actor_func)BgIkanaRay_Draw;
    this->base.flags &= 0xFFFFFFEF;
    this->update = (actor_func)BgIkanaRay_UpdateActivated;
}

void BgIkanaRay_UpdateActivated(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    Collision_AddAT(ctxt, &ctxt->colCheckCtx, &this->collision.base);
}

void BgIkanaRay_Update(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    this->update((Actor*)this, ctxt);
}

void BgIkanaRay_Draw(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    SceneProc_DrawAllSceneAnimatedTextures(ctxt, this->animatedTextures);
    func_800BE03C(ctxt, object_ikana_obj_001100);
}
