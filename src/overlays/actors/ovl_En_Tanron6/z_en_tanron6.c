#include "z_en_tanron6.h"

#define FLAGS 0x00000005

#define THIS ((EnTanron6*)thisx)

void EnTanron6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTanron6_DoNothing(EnTanron6* this);
void func_80BE60D0(EnTanron6* this, GlobalContext* globalCtx);

const ActorInit En_Tanron6_InitVars = {
    ACTOR_EN_TANRON6,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_TANRON5,
    sizeof(EnTanron6),
    (ActorFunc)EnTanron6_Init,
    (ActorFunc)EnTanron6_Destroy,
    (ActorFunc)EnTanron6_Update,
    (ActorFunc)EnTanron6_Draw,
};

static DamageTable sDamageTable = {
    0xF0, 0xF0, 0x00, 0xF1, 0xE1, 0xE1, 0x00, 0xE1, 0xF0, 0xF0, 0xF0, 0xE1, 0xE1, 0x46, 0xF0, 0xF0,
    0xE1, 0xF0, 0xF0, 0x00, 0x00, 0xF0, 0xE1, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
};

void EnTanron6_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron6* this = THIS;

    this->actor.colChkInfo.mass = 10;
    ActorShape_Init(&this->actor.shape, 0, func_800B3FC0, 19.0f);
    this->actor.colChkInfo.health = 1;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.targetMode = 6;
    EnTanron6_DoNothing(this);
}

void EnTanron6_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnTanron6_DoNothing(EnTanron6* this) {
    this->actionFunc = func_80BE60D0;
}

void func_80BE60D0(EnTanron6* this, GlobalContext* globalCtx) {
}

void EnTanron6_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTanron6* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 40.0f, 40.0f, 0x1D);
}

void EnTanron6_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
