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
    (ActorFunc)BgIkanaRay_Draw,
};

ColliderCylinderInit bgIkanaRayCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_OTHER,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00200000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 90, 420, -420, { 0, 0, 0 } },
};

InitChainEntry bgIkanaRayCompInit[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgIkanaRay_Init(Actor* thisx, GlobalContext* globalCtx) {
    ColliderCylinder* collision = &THIS->collision;
    u32 pad;

    Actor_ProcessInitChain(thisx, bgIkanaRayCompInit);

    Collider_InitCylinder(globalCtx, collision);
    Collider_SetCylinder(globalCtx, collision, thisx, &bgIkanaRayCylinderInit);
    Collider_UpdateCylinder(thisx, &THIS->collision);

    THIS->animatedTextures = (AnimatedMaterial*)Lib_SegmentedToVirtual(object_ikana_obj_001228);

    if (Flags_GetSwitch(globalCtx, THIS->base.params & 0x7F) != 0) {
        BgIkanaRay_SetActivated(THIS);
    } else {
        BgIkanaRay_SetDeactivated(THIS);
    }
}

void BgIkanaRay_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ColliderCylinder* collision = &THIS->collision;
    Collider_DestroyCylinder(globalCtx, collision);
}

void BgIkanaRay_SetDeactivated(BgIkanaRay* this) {
    this->base.draw = NULL;
    this->base.flags |= 0x10;
    this->update = BgIkanaRay_UpdateCheckForActivation;
}

void BgIkanaRay_UpdateCheckForActivation(BgIkanaRay* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->base.params & 0x7F) != 0) {
        BgIkanaRay_SetActivated(this);
    }
}

void BgIkanaRay_SetActivated(BgIkanaRay* this) {
    this->base.draw = (ActorFunc)BgIkanaRay_Draw;
    this->base.flags &= 0xFFFFFFEF;
    this->update = BgIkanaRay_UpdateActivated;
}

void BgIkanaRay_UpdateActivated(BgIkanaRay* this, GlobalContext* globalCtx) {
    CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collision.base);
}

void BgIkanaRay_Update(Actor* thisx, GlobalContext* globalCtx) {
    THIS->update(THIS, globalCtx);
}

void BgIkanaRay_Draw(Actor* thisx, GlobalContext* globalCtx) {
    AnimatedMat_Draw(globalCtx, THIS->animatedTextures);
    func_800BE03C(globalCtx, object_ikana_obj_001100);
}
