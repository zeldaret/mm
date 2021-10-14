#include "z_en_hakurock.h"
#include "overlays/actors/ovl_Boss_Hakugin/z_boss_hakugin.h"

#define FLAGS 0x00000030

#define THIS ((EnHakurock*)thisx)

void EnHakurock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80B21BE0(BossHakugin* arg0, Vec3f* arg1, s32 arg2);
void func_80B21EA4(EnHakurock* this, s32 arg1);
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

// static ColliderCylinderInit sCylinderInit = {
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

// sColChkInfoInit
static CollisionCheckInfoInit D_80B22AAC = { 0, 60, 60, MASS_IMMOVABLE };

extern Gfx D_06011100[];
extern Gfx D_06011178[];

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

void EnHakurock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHakurock* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B21BE0(BossHakugin* parent, Vec3f* arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < 180; i++) {
        BossHakuginParticle* temp_s0 = &parent->unk_9F8[i];
        if (temp_s0->unk_18 < 0) {
            // Stack variables need to be here unfortunately
            s16 sp2E;
            s16 sp2C;
            f32 sp28;
            Math_Vec3f_Copy(&temp_s0->unk_0, arg1);
            sp2C = Rand_S16Offset(0x1000, 0x3000);
            sp2E = ((u32)Rand_Next() >> 0x10);
            sp28 = Rand_ZeroFloat(5.0f) + 10.0f;
            temp_s0->unk_C.x = (sp28 * Math_CosS(sp2C)) * Math_SinS(sp2E);
            temp_s0->unk_C.y = (Math_SinS(sp2C) * sp28);
            temp_s0->unk_C.z = (sp28 * Math_CosS(sp2C)) * Math_CosS(sp2E);
            if ((arg2 == 1) || (arg2 == 3)) {
                temp_s0->unk_24 = ((Rand_ZeroFloat(5.0f) + 25.0f) * 0.0012f);
                temp_s0->unk_0.x = ((Rand_ZeroFloat(2.0f) + 9.0f) * temp_s0->unk_C.x) + arg1->x;
                temp_s0->unk_0.y = ((Rand_ZeroFloat(2.0f) + 3.0f) * temp_s0->unk_C.y) + arg1->y;
                temp_s0->unk_0.z = ((Rand_ZeroFloat(2.0f) + 9.0f) * temp_s0->unk_C.z) + arg1->z;
                temp_s0->unk_1A = 1;
            } else {
                temp_s0->unk_24 = ((Rand_ZeroFloat(5.0f) + 18.0f) * 0.0001f);
                temp_s0->unk_0.x = ((Rand_ZeroFloat(2.0f) + 3.0f) * temp_s0->unk_C.x) + arg1->x;
                temp_s0->unk_0.y = ((Rand_ZeroFloat(3.0f) + 1.0f) * temp_s0->unk_C.y) + arg1->y;
                temp_s0->unk_0.z = ((Rand_ZeroFloat(2.0f) + 3.0f) * temp_s0->unk_C.z) + arg1->z;
                temp_s0->unk_1A = 0;
            }
            temp_s0->unk_1C.x = (Rand_Next() >> 0x10);
            temp_s0->unk_1C.y = (Rand_Next() >> 0x10);
            temp_s0->unk_1C.z = (Rand_Next() >> 0x10);
            temp_s0->unk_18 = 0x28;
            return;
        }
    }
}

void func_80B21EA4(EnHakurock* this, s32 arg1) {
    Vec3f sp4C;
    s32 i;
    f32 scaleFactor;
    s32 tmp;
    s32 phi_s5;

    if (arg1 == 0) {
        for (i = 0; i < 20; i++) {
            func_80B21BE0(this->actor.parent, &this->actor.world.pos, arg1);
        }
    } else if (arg1 == 2) {
        for (i = 0; i < 10; i++) {
            func_80B21BE0(this->actor.parent, &this->actor.world.pos, arg1);
        }
    } else {
        Math_Vec3f_Copy(&sp4C, &this->actor.world);
        scaleFactor = this->actor.scale.x * 600.0f;
        if (arg1 == 1) {
            sp4C.y -= scaleFactor;
            i = 0;
        } else {
            i = 1;
        }

        for (; i < 3; i++) {
            tmp = (i * 5) + 5;
            for (phi_s5 = 0; phi_s5 < tmp; phi_s5++) {
                func_80B21BE0(this->actor.parent, &sp4C, arg1);
            }
            sp4C.y += scaleFactor;
        }
    }
}

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
    this->unk_148 = 10;
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
    Player* player = PLAYER;
    s16 angle;

    this->actor.draw = func_80B229A4;
    angle = (Rand_Next() >> 0x13) + player->actor.shape.rot.y;
    this->actor.shape.rot.y = (Rand_Next() >> 0x10);
    this->actor.world.pos.x = (Math_SinS(angle) * 600.0f) + player->actor.world.pos.x;
    this->actor.world.pos.y = player->actor.world.pos.y + 700.0f;
    this->actor.world.pos.z = (Math_CosS(angle) * 600.0f) + player->actor.world.pos.z;
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

void func_80B22500(EnHakurock* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->unk_148 > 0) {
        this->unk_148--;
        if ((this->unk_148 & 1) == 0) {
            this->actor.world.pos.y = (sin_rad(this->unk_148 * 0.15707964f) * 4.0f) + this->actor.floorHeight;
        } else {
            this->actor.world.pos.y = this->actor.floorHeight;
        }
    }
    if (this->collider.base.ocFlags1 & 2) {
        if ((this->collider.base.oc == this->actor.parent) ||
            ((this->collider.base.oc->id == 0x1EA) && (this->collider.base.oc->params == 2))) {
            func_80B21EA4(this, 3);
            func_80B21FFC(this);
        } else if ((&player->actor == this->collider.base.oc) && ((player->stateFlags3 & 0x81000) != 0) &&
                   (player->linearVelocity > 8.0f)) {
            player->unk_B08[0] = player->linearVelocity = -5.0f;
            player->unk_B08[1] += (player->linearVelocity * 0.05f);
            player->actor.velocity.y = 5.0f;
            player->currentYaw = player->actor.world.rot.y;
            player->actor.home.rot.y = player->actor.world.rot.y;
            player->actor.shape.rot.y = player->actor.world.rot.y;
            player->unk_B8C = 4;
        }

    } else if ((this->actor.xzDistToPlayer > 1000.0f) && (this->actor.projectedPos.z < 0.0f)) {
        func_80B21FFC(this);
    }
}

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

void EnHakurock_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHakurock* this = THIS;
    s16 rockParams;

    this->actionFunc(this, globalCtx);
    rockParams = this->actor.params;
    if ((rockParams == 1) || (rockParams == 2)) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, this->collider.dim.radius, 0.0f, 0x85U);
        if (this->actor.floorHeight == -32000.0f) {
            func_80B21FFC(this);
        } else {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider);
        }
    } else if ((rockParams == 3) || (rockParams == 4)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider);
    }
}

void func_80B228F4(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x80, 255, 185, 24, 255);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, &D_0406AB30);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80B229A4(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    SysMatrix_InsertTranslation(-100.0f, 0.0f, 0.0f, 1);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06011100);
    gSPDisplayList(POLY_OPA_DISP++, D_06011178);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
