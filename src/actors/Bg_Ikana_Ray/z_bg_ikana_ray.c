#include <ultra64.h>
#include <global.h>

ActorInitData bgIkanaRayInitData = {
    0x0256,
    6,
    0,
    0,
    0x0203,
    0, 0,
    sizeof(ActorBgIkanaRay),
    (actor_func)BgIkanaRay_Init,
    (actor_func)BgIkanaRay_Fini,
    (actor_func)BgIkanaRay_Main,
    (actor_func)BgIkanaRay_Draw
};

// TODO better formatting
ColCylinderInit bgIkanaRayCylinderInit = {
    { 10, 33, 0, 0, 0, 1 },
    { 0, { 0x00200000, 0, 0 }, { 0, 0, 0 }, 25, 0, 1 },
    { 90, 420, 65116}
};

// TODO macro
ActorInitVar  bgIkanaRayCompInit[] = {
    {1, 6, 0x0FC, 4000},
    {1, 6, 0x100, 1000},
    {1, 6, 0x104, 1000},
    {0, 9, 0x058, 100}
};

void BgIkanaRay_Init(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    ColCylinder* collision = &this->collision;
    u32 pad;

    Lib_ApplyActorInitVars((Actor*)this, bgIkanaRayCompInit);

    Collision_InitCylinderDefault(ctxt, collision);
    Collision_InitCylinderWithData(ctxt, collision, (Actor*)this, &bgIkanaRayCylinderInit);
    Collision_CylinderMoveToActor((Actor*)this, &this->collision);

    this->animatedTextures = (AnimatedTexture*)Lib_PtrSegToVirt(object_ikana_obj_001228);

    if (Actor_GetSwitchFlag(ctxt, this->base.variable & 0x7F) != 0) {
        BgIkanaRay_SetActivated(this);
    } else {
        BgIkanaRay_SetDeactivated(this);
    }
}

void BgIkanaRay_Fini(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    ColCylinder* collision = &this->collision;
    Collision_FiniCylinder(ctxt, collision);
}

void BgIkanaRay_SetDeactivated(ActorBgIkanaRay* this) {
    this->base.draw = NULL;
    this->base.flags |= 0x10;
    this->update = (actor_func)BgIkanaRay_UpdateCheckForActivation;
}

void BgIkanaRay_UpdateCheckForActivation(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    if (Actor_GetSwitchFlag(ctxt, this->base.variable & 0x7F) != 0) {
        BgIkanaRay_SetActivated(this);
    }
}

void BgIkanaRay_SetActivated(ActorBgIkanaRay* this) {
    this->base.draw = (actor_func)BgIkanaRay_Draw;
    this->base.flags &= 0xFFFFFFEF;
    this->update = (actor_func)BgIkanaRay_UpdateActivated;
}

void BgIkanaRay_UpdateActivated(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    Collision_AddAT(ctxt, &ctxt->collisionContext, &this->collision.base);
}

void BgIkanaRay_Main(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    this->update((Actor*)this, ctxt);
}

void BgIkanaRay_Draw(ActorBgIkanaRay* this, GlobalContext* ctxt) {
    SceneProc_DrawAllSceneAnimatedTextures(ctxt, this->animatedTextures);
    func_800BE03C(ctxt, object_ikana_obj_001100);
}
