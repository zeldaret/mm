#include "z_en_hakurock.h"

#define FLAGS 0x00000030

#define THIS ((EnHakurock*)thisx)

void EnHakurock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80B21BE0(EnHakurock* this, Vec3f* arg1, s32 arg2);

void func_80B21FFC(EnHakurock* this);
void func_80B22040(EnHakurock* this, GlobalContext* globalCtx);
void func_80B220A8(EnHakurock* this);
void func_80B221E8(EnHakurock* this, GlobalContext* globalCtx);
void func_80B222AC(EnHakurock* this, GlobalContext* globalCtx);
void func_80B2242C(EnHakurock* this, GlobalContext* globalCtx);
void func_80B224C0(EnHakurock* this);
void func_80B22500(EnHakurock* this, GlobalContext* globalCtx);
void func_80B226AC(EnHakurock* this);
void func_80B22750(EnHakurock* this, GlobalContext* globalCtx);
void func_80B228F4(Actor* thisx, GlobalContext* globalCtx);
void func_80B229A4(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hakurock_InitVars = {
    ACTOR_EN_HAKUROCK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(EnHakurock),
    (ActorFunc)EnHakurock_Init,
    (ActorFunc)EnHakurock_Destroy,
    (ActorFunc)EnHakurock_Update,
    (ActorFunc)NULL,
};
*/

// D_80B22A80
static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HARD,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_NO_PUSH | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x00, 0x00 },
        { 0xF3CFBBFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON,
        OCELEM_ON,
    },
    { 60, 60, -30, { 0, 0, 0 } },
};

static CollisionCheckInfoInit D_80B22AAC = { 0x0000003C, 0x003CFF00, 0x00000000 };

extern Gfx D_0406AB30[];
extern Gfx D_06011100[];
extern Gfx D_06011178[];

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/EnHakurock_Init.asm")
void EnHakurock_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHakurock* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 52.0f);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_80B22AAC);
    if (this->actor.params == 1) {
        this->actor.gravity = -1.5f;
    } else {
        this->collider.base.ocFlags1 &= 0xFFFB;
        this->actor.minVelocityY = -100.0f;
        this->actor.gravity = -7.0f;
    }
    func_80B21FFC(this);
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/EnHakurock_Destroy.asm")
void EnHakurock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHakurock* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B21BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B21EA4.asm")

void func_80B21FFC(EnHakurock* this) {
    this->actor.bgCheckFlags &= 0xFFFE;
    this->collider.base.atFlags &= -3;
    this->collider.base.ocFlags1 &= -3;
    this->actor.draw = NULL;
    this->actor.params = 0;
    this->actionFunc = func_80B22040;
}

void func_80B22040(EnHakurock* this, GlobalContext* globalCtx) {
    if (this->actor.params == 1) {
        func_80B220A8(this);
    } else if (this->actor.params == 2) {
        func_80B222AC(this, globalCtx);
    } else if (this->actor.params == 4) {
        func_80B226AC(this);
    }
}

void func_80B220A8(EnHakurock* this) {
    this->actor.params = 1;
    this->actor.draw = func_80B228F4;
    this->actor.speedXZ = Rand_ZeroFloat(3.5f) + 2.5f;
    this->actor.velocity.y = Rand_ZeroFloat(4.5f) + 18.0f;
    Actor_SetScale(this, (Rand_ZeroFloat(5.0f) + 15.0f) * 0.001f);
    this->actor.world.rot.y = (Rand_Next() >> 0x12) + this->actor.parent->shape.rot.y + 0x8000;
    this->actor.shape.rot.x = (Rand_Next() >> 0x10);
    this->actor.shape.rot.y = (Rand_Next() >> 0x10);
    this->actor.shape.rot.z = (Rand_Next() >> 0x10);
    this->collider.dim.radius = (this->actor.scale.x * 2500.0f);
    this->collider.dim.yShift = -this->collider.dim.radius;
    this->collider.dim.height = this->collider.dim.radius * 2;
    this->unk_148 = 0xA;
    Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
    this->actionFunc = func_80B221E8;
}

void func_80B221E8(EnHakurock* this, GlobalContext* globalCtx) {

    if (this->unk_148 > 0) {
        this->unk_148--;
    }
    this->actor.shape.rot.x += 0x700;
    this->actor.shape.rot.y += 0x900;
    this->actor.shape.rot.z += 0xB00;

    if (this->collider.base.atFlags & 2 || !(this->unk_148 || (this->collider.base.ocFlags1 & 2) == 0) ||
        (this->actor.bgCheckFlags & 1) && (this->actor.velocity.y < 0.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_ROCK_BROKEN);
        func_80B21EA4(this, 0);
        func_80B21FFC(this);
    }
}

void func_80B222AC(EnHakurock* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    s16 angle;

    this->actor.draw = func_80B229A4;
    angle = (Rand_Next() >> 0x13) + player->base.shape.rot.y;
    this->actor.shape.rot.y = (Rand_Next() >> 0x10);
    this->actor.world.pos.x = (Math_SinS(angle) * 600.0f) + player->base.world.pos.x;
    this->actor.world.pos.y = player->base.world.pos.y + 700.0f;
    this->actor.world.pos.z = (Math_CosS(angle) * 600.0f) + player->base.world.pos.z;
    this->actor.shape.shadowScale = 5.0f;
    this->actor.velocity.y = -10.0f;
    Actor_SetScale(&this->actor, (Rand_ZeroFloat(5.0f) + 17.0f) * 0.01f);
    this->actor.scale.x *= 0.6f;
    this->actor.scale.z *= 0.6f;
    this->collider.dim.radius = (this->actor.scale.x * 150.0f);
    this->collider.dim.yShift = (this->actor.scale.y * -750.0f);
    this->collider.dim.height = this->collider.dim.yShift * -2;
    Math_Vec3f_Copy(&this->actor.prevPos, &this->actor.world.pos);
    this->actor.params = 2;
    this->actionFunc = func_80B2242C;
}

void func_80B2242C(EnHakurock* this, GlobalContext* globalCtx) {
    if ((this->collider.base.ocFlags1 & 2) && (this->collider.base.oc == this->actor.parent)) {
        func_80B21EA4(this, 1);
        func_80B21FFC(this);
    } else if ((this->actor.bgCheckFlags & 1)) {
        func_80B21EA4(this, 2);
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_OBJECT_STICK);
        func_80B224C0(this);
    }
}

void func_80B224C0(EnHakurock* this) {
    this->actor.params = 3;
    this->unk_148 = 0xA;
    this->actor.shape.shadowScale = 0.0f;
    this->actor.world.pos.y += 4.0f;
    this->actionFunc = func_80B22500;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B22500.asm")

void func_80B226AC(EnHakurock* this) {
    f32 shiftFactor;

    this->actor.draw = func_80B229A4;
    Actor_SetScale(&this->actor, 0.35f);
    this->actor.scale.y = 0.5f;
    this->collider.dim.radius = (this->actor.scale.x * 270.0f);
    shiftFactor = -750.0f;
    this->collider.dim.yShift = 0.5f * shiftFactor;
    this->unk_148 = 0;
    this->actor.shape.shadowScale = 0.0f;
    this->collider.dim.height = this->collider.dim.yShift * -2;
    this->actionFunc = func_80B22750;
}

void func_80B22750(EnHakurock* this, GlobalContext* globalCtx) {
    if (this->actor.params == 0) {
        func_80B21EA4(this, 3);
        func_80B21FFC(this);
    }
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/EnHakurock_Update.asm")
void EnHakurock_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHakurock* this = THIS;
    s16 rockParams;

    this->actionFunc(this, globalCtx);
    rockParams = this->actor.params; // Params temp is necessary
    if ((rockParams == 1) || (rockParams == 2)) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        func_800B78B8(globalCtx, &this->actor, 30.0f, this->collider.dim.radius, 0.0f, 0x85U);
        if (this->actor.floorHeight == -32000.0f) {
            func_80B21FFC(this);
        } else {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
        }
    } else if ((rockParams == 3) || (rockParams == 4)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B228F4.asm")
// void func_80B228F4(Actor* thisx, GlobalContext* globalCtx)
// {
//     EnHakurock* this = THIS;
//     GraphicsContext *sp24;
//     Gfx *temp_v0;

//     OPEN_DISPS(globalCtx->state.gfxCtx)
//     func_8012C28C(globalCtx->state.gfxCtx);
//     // temp_v0 = sp24->polyOpa.p;
//     // sp24->polyOpa.p = temp_v0 + 8;
//     // temp_v0->words.w0 = 0xFA000080;
//     // temp_v0->words.w1 = 0xFFB918FF;
//     gDPSetPrimColor(POLY_OPA_DISP++, 0, qu08(0.5), 255, 0xB9, 0x18, 0xFF);
//     gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

//     gSPDisplayList(POLY_OPA_DISP++, D_0406AB30);
//     CLOSE_DISPS(globalCtx->state.gfxCtx);
// }

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hakurock_0x80B21B00/func_80B229A4.asm")
void func_80B229A4(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    SysMatrix_InsertTranslation(-100.0f, 0.0f, 0.0f, 1);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06011100);
    gSPDisplayList(POLY_OPA_DISP++, D_06011178);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
