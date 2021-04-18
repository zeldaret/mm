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

static ColliderSphereInit sSphereInit = {
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

/*
const ActorInit En_Jc_Mato_InitVars = {
    ACTOR_EN_JC_MATO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnJcMato),
    (ActorFunc)EnJcMato_Init,
    (ActorFunc)EnJcMato_Destroy,
    (ActorFunc)EnJcMato_Update,
    (ActorFunc)EnJcMato_Draw
};
*/

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jc_Mato_0x80B9DEE0/func_80B9DEE0.asm")
s32 func_80B9DEE0(EnJcMato* this, GlobalContext* globalCtx) {
    u32 new_var;
    new_var = 1;

    this->collider.dim.worldSphere.center.x = this->unk1A4.x;
    this->collider.dim.worldSphere.center.y = this->unk1A4.y;
    this->collider.dim.worldSphere.center.z = this->unk1A4.z;
    if ((this->collider.base.acFlags & 2) && !this->unk1A2 && (this->actor.colChkInfo.damageEffect == 0xF)) {

        this->collider.base.acFlags &= 0xFFFD;
        Audio_PlayActorSound2(&this->actor, 0x4807);
        globalCtx->interfaceCtx.unk25C = 1;
        this->unk1A2 = new_var;
        return 1;
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    return 0;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jc_Mato_0x80B9DEE0/func_80B9DFC8.asm")
void func_80B9DFC8(EnJcMato* this) {
    this->actionFunc = func_80B9DFDC;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jc_Mato_0x80B9DEE0/func_80B9DFDC.asm")
void func_80B9DFDC(EnJcMato* this, GlobalContext* globalCtx) {
    s16 phi_v1;

    if (this->unk1A2 != 0) {
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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jc_Mato_0x80B9DEE0/EnJcMato_Init.asm")
// void EnJcMato_Init(Actor * thisx, GlobalContext *globalCtx)
// {
//     EnJcMato* this = THIS;

//     ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 24.0f);
//     Collider_InitSphere(globalCtx, &this->collider);
//     Collider_SetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);
//     this->collider.dim.worldSphere.radius = 0xF;
//     this->actor.colChkInfo.damageTable = &D_80B9E23C;
//     Actor_SetScale(&this->actor, 0.008f);
//     this->unk1A2 = 0;
//     this->unk1A0 = 0x19;
//     func_80B9DFC8(this);
// }

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jc_Mato_0x80B9DEE0/EnJcMato_Destroy.asm")
void EnJcMato_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJcMato* this = THIS;

    Collider_DestroySphere(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jc_Mato_0x80B9DEE0/EnJcMato_Update.asm")

// Need data...
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jc_Mato_0x80B9DEE0/EnJcMato_Draw.asm")
// void EnJcMato_Draw(Actor* thisx, GlobalContext* globalCtx) {
//     EnJcMato* this = THIS;

//     func_8012C28C(globalCtx->state.gfxCtx);
//     gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
//     gSPDisplayList(POLY_OPA_DISP++, 0x60003900);
//     SysMatrix_MultiplyVector3fByState(&D_80B9E25C, &this->unk1A4);
// }
