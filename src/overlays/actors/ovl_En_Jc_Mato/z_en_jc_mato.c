/*
 * File: z_en_jc_mato.c
 * Overlay: ovl_en_jc_mato
 * Description: Boat Cruise Target
 */

#include "z_en_jc_mato.h"

#define FLAGS 0x00004030

#define THIS ((EnJcMato*)thisx)

void EnJcMato_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJcMato_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJcMato_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJcMato_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80B9DEE0(EnJcMato* this, GlobalContext* globalCtx);
void func_80B9DFC8(EnJcMato* this);
void func_80B9DFDC(EnJcMato* this, GlobalContext* globalCtx);

const ActorInit En_Jc_Mato_InitVars = {
    ACTOR_EN_JC_MATO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnJcMato),
    (ActorFunc)EnJcMato_Init,
    (ActorFunc)EnJcMato_Destroy,
    (ActorFunc)EnJcMato_Update,
    (ActorFunc)EnJcMato_Draw,
};

// was D_80B9E210
ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 15 }, 100 },
};

DamageTable EnJcMatoDamageTable = {
    0x01, 0x01, 0x01, 0x01, 0x01, 0xF1, 0x01, 0x01, 0x01, 0x01, 0x01, 0xF1, 0xF1, 0xF1, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
};

s32 func_80B9DEE0(EnJcMato* this, GlobalContext* globalCtx) {
    this->collider.dim.worldSphere.center.x = this->JcMatoPos.x;
    this->collider.dim.worldSphere.center.y = this->JcMatoPos.y;
    this->collider.dim.worldSphere.center.z = this->JcMatoPos.z;
    if ((this->collider.base.acFlags & 2) && !this->hitFlag && (this->actor.colChkInfo.damageEffect == 0xF)) {
        this->collider.base.acFlags &= 0xFFFD;
        Audio_PlayActorSound2(&this->actor, 0x4807);
        globalCtx->interfaceCtx.unk25C = 1;
        this->hitFlag = 1;
        return 1;
    } else {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
        return 0;
    }
}

void func_80B9DFC8(EnJcMato* this) {
    this->actionFunc = func_80B9DFDC;
}

void func_80B9DFDC(EnJcMato* this, GlobalContext* globalCtx) {
    s16 phi_v1;

    if (this->hitFlag != 0) {
        if (this->unk1A0 == 0) {
            phi_v1 = 0;
        } else {
            this->unk1A0 -= 1;
            phi_v1 = this->unk1A0;
        }
        if (phi_v1 == 0) {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void EnJcMato_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnJcMato* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
    Collider_InitSphere(globalCtx, &this->collider);
    Collider_SetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);
    this->collider.dim.worldSphere.radius = 0xF;
    this->actor.colChkInfo.damageTable = &EnJcMatoDamageTable;
    Actor_SetScale(&this->actor, 0.008f);
    this->hitFlag = 0;
    this->unk1A0 = 25;
    func_80B9DFC8(this);
}

void EnJcMato_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJcMato* this = THIS;

    Collider_DestroySphere(globalCtx, &this->collider);
}

void EnJcMato_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnJcMato* this = THIS;

    this->actionFunc(this, globalCtx);
    if (!(gSaveContext.owl.unk4 & 1)) {
        func_80B9DEE0(this, globalCtx);
    }
}

extern Gfx D_06000390[];
Vec3f D_80B9E25C = { 0.0f, -2500.0f, 0.0f };

void EnJcMato_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnJcMato* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000390);
    SysMatrix_MultiplyVector3fByState(&D_80B9E25C, &this->JcMatoPos);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
