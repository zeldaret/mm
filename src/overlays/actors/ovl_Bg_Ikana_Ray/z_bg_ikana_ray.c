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

static ColliderCylinderInit sCylinderInit = {
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

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgIkanaRay_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaRay* this = THIS;
    ColliderCylinder* collision = &this->collision;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitCylinder(globalCtx, collision);
    Collider_SetCylinder(globalCtx, collision, &this->actor, &sCylinderInit);
    Collider_UpdateCylinder(&this->actor, &this->collision);

    this->animatedTextures = (AnimatedMaterial*)Lib_SegmentedToVirtual(object_ikana_obj_001228);

    if (Flags_GetSwitch(globalCtx, this->actor.params & 0x7F)) {
        BgIkanaRay_SetActivated(this);
    } else {
        BgIkanaRay_SetDeactivated(this);
    }
}

void BgIkanaRay_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaRay* this = THIS;

    ColliderCylinder* collision = &this->collision;
    Collider_DestroyCylinder(globalCtx, collision);
}

void BgIkanaRay_SetDeactivated(BgIkanaRay* this) {
    this->actor.draw = NULL;
    this->actor.flags |= 0x10;
    this->update = BgIkanaRay_UpdateCheckForActivation;
}

void BgIkanaRay_UpdateCheckForActivation(BgIkanaRay* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, this->actor.params & 0x7F)) {
        BgIkanaRay_SetActivated(this);
    }
}

void BgIkanaRay_SetActivated(BgIkanaRay* this) {
    this->actor.draw = BgIkanaRay_Draw;
    this->actor.flags &= ~0x10;
    this->update = BgIkanaRay_UpdateActivated;
}

void BgIkanaRay_UpdateActivated(BgIkanaRay* this, GlobalContext* globalCtx) {
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collision.base);
}

void BgIkanaRay_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaRay* this = THIS;

    this->update(this, globalCtx);
}

void BgIkanaRay_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaRay* this = THIS;

    AnimatedMat_Draw(globalCtx, this->animatedTextures);
    func_800BE03C(globalCtx, object_ikana_obj_001100);
}
