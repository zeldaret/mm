/*
 * File: z_obj_aqua.c
 * Overlay: ovl_Obj_Aqua
 * Description: Water poured out of a bottle
 */

#include "z_obj_aqua.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjAqua*)thisx)

void ObjAqua_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjAqua_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ACBC70(ObjAqua* this);
void func_80ACBDCC(ObjAqua* this);
void func_80ACBC8C(ObjAqua* this, GlobalContext* globalCtx);
void func_80ACBD48(ObjAqua* this, GlobalContext* globalCtx);
void func_80ACBDFC(ObjAqua* this, GlobalContext* globalCtx);

void func_80ACBD34(ObjAqua* this);

const ActorInit Obj_Aqua_InitVars = {
    ACTOR_OBJ_AQUA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjAqua),
    (ActorFunc)ObjAqua_Init,
    (ActorFunc)ObjAqua_Destroy,
    (ActorFunc)ObjAqua_Update,
    (ActorFunc)ObjAqua_Draw,
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
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { 6, 10, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_CONTINUE),          ICHAIN_VEC3S(world.rot, 0, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -900, ICHAIN_CONTINUE),   ICHAIN_F32_DIV1000(terminalVelocity, -4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

Vec3f D_80ACC308 = { 1.0f / 1000.0f, 7.0f / 10000.0f, 1.0f / 1000.0f };
Vec3f D_80ACC314 = { 8.6f / 1000.0f, 8.0f / 10000.0f, 8.6f / 1000.0f };
Vec3f D_80ACC320 = { 1.0f / 100.0f, 2.6f / 1000.0f, 1.0f / 100.0f };

void func_80ACB6A0(ObjAqua* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp58;
    s32 angleOffset = 0;
    s32 i;

    sp58.y = this->actor.world.pos.y + this->actor.depthInWater;
    for (i = 0; i < 4; i++) {
        sp58.x = this->actor.world.pos.x + Math_SinS((s32)(Rand_ZeroOne() * 7200.0f) + angleOffset) * 8.0f;
        sp58.z = this->actor.world.pos.z + Math_CosS((s32)(Rand_ZeroOne() * 7200.0f) + angleOffset) * 8.0f;
        EffectSsGSplash_Spawn(globalCtx, &sp58, NULL, NULL, 0, 120);
        angleOffset += 0x4000;
    }
    sp58.x = this->actor.world.pos.x;
    sp58.z = this->actor.world.pos.z;
    EffectSsGSplash_Spawn(globalCtx, &sp58, NULL, NULL, 0, 300);
}

void func_80ACB7F4(ObjAqua* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f effectPos;
    s32 angleOffset = 0;
    s32 i;

    effectPos.y = this->actor.floorHeight;
    for (i = 0; i < 4; i++) {
        effectPos.x = (this->actor.world.pos.x + Math_SinS((s32)(Rand_ZeroOne() * 7200.0f) + angleOffset) * 8.0f);
        effectPos.z = (this->actor.world.pos.z + Math_CosS((s32)(Rand_ZeroOne() * 7200.0f) + angleOffset) * 8.0f);
        EffectSsGSplash_Spawn(globalCtx, &effectPos, NULL, NULL, 0, 120);
        angleOffset += 0x4000;
    }
    effectPos.x = this->actor.world.pos.x;
    effectPos.z = this->actor.world.pos.z;
    EffectSsGSplash_Spawn(globalCtx, &effectPos, NULL, NULL, 0, 300);
}

void func_80ACB940(ObjAqua* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f effectPos;
    Vec3f effectVel;

    effectVel.x = Rand_ZeroOne() - 0.5f;
    effectVel.y = 2.0f;
    effectVel.z = Rand_ZeroOne() - 0.5f;
    effectPos.x = this->actor.world.pos.x + (effectVel.x * 40.0f);
    effectPos.y = this->actor.world.pos.y;
    effectPos.z = this->actor.world.pos.z + (effectVel.z * 40.0f);
    EffectSsIceSmoke_Spawn(globalCtx, &effectPos, &effectVel, &gZeroVec3f, (s32)(Rand_ZeroOne() * 24.0f) + 70);
}

void func_80ACBA10(ObjAqua* this) {
    s32 pad;
    MtxF sp2C;

    func_800C0094(this->actor.floorPoly, this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z,
                  &sp2C);
    func_8018219C(&sp2C, &this->actor.shape.rot, 0);
}

s32 func_80ACBA60(ObjAqua* this, GlobalContext* globalCtx) {
    s32 pad;
    WaterBox* waterBox;
    f32 ySurface;
    s32 bgId;

    if (WaterBox_GetSurfaceImpl(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                &ySurface, &waterBox, &bgId) &&
        (this->actor.world.pos.y < ySurface)) {
        return true;
    }
    return false;
}

void ObjAqua_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjAqua* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.scale.x = 0.0009f;
    this->actor.scale.y = 0.0005f;
    this->actor.scale.z = 0.0009f;
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 60.0f);
    if (1) {};
    this->actor.shape.shadowAlpha = 140;
    this->alpha = 255;
    if (func_80ACBA60(this, globalCtx)) {
        for (i = 0; i < 8; i++) {
            EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, -4.0f, 4.0f, 4.0f,
                                 (Rand_ZeroOne() * 0.09f) + 0.03f);
        }
        func_80ACBDCC(this);
    } else {
        func_80ACBC70(this);
    }
}

void ObjAqua_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjAqua* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80ACBC70(ObjAqua* this) {
    this->counter = 200;
    this->actionFunc = func_80ACBC8C;
}

void func_80ACBC8C(ObjAqua* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 0x21) {
        if (this->actor.bgCheckFlags & 1) {
            func_80ACB7F4(this, globalCtx);
            func_80ACBA10(this);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOTTLE_WATERING);
            func_80ACBD34(this);
        } else {
            func_80ACB6A0(this, globalCtx);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 0x28, NA_SE_EV_BOMB_DROP_WATER);
            Actor_MarkForDeath(&this->actor);
        }
    } else if (this->counter <= 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80ACBD34(ObjAqua* this) {
    this->actionFunc = func_80ACBD48;
}

void func_80ACBD48(ObjAqua* this, GlobalContext* globalCtx) {
    if ((AQUA_HOT(&this->actor) == 1) && (this->alpha > 90)) {
        func_80ACB940(this, globalCtx);
    }
    if (this->alpha > 5) {
        this->alpha -= 5;
    } else {
        this->alpha = 0;
    }
    if (this->actor.shape.shadowAlpha > 2) {
        this->actor.shape.shadowAlpha -= 2;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80ACBDCC(ObjAqua* this) {
    this->actor.gravity = -0.1f;
    this->counter = 40;
    this->alpha = 140;
    this->actionFunc = func_80ACBDFC;
}

void func_80ACBDFC(ObjAqua* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 temp = this->counter;

    this->alpha = (s32)(temp * 3.25f) + 10;
    this->actor.shape.shadowAlpha = this->alpha;
    this->unk_198 += 1000;
    if (AQUA_HOT(&this->actor) == 1) {
        f32 temp_f2 = this->actor.scale.x * 10000.0f;

        EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, temp_f2 * -0.5f, temp_f2, temp_f2,
                             (Rand_ZeroOne() * 0.1f) + 0.03f);
    }
    if (this->counter <= 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjAqua_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjAqua* this = THIS;
    s32 pad;

    if (this->counter > 0) {
        this->counter--;
    }
    this->actionFunc(this, globalCtx);
    if (this->actor.update) {
        if (this->actionFunc == func_80ACBC8C) {
            Math_Vec3f_StepTo(&this->actor.scale, &D_80ACC308, 0.00006f);
        } else if (this->actionFunc == func_80ACBD48) {
            Math_Vec3f_StepTo(&this->actor.scale, &D_80ACC314, 0.00095f);
        } else {
            Math_Vec3f_StepTo(&this->actor.scale, &D_80ACC320, 0.0004f);
        }
        this->actor.velocity.y *= 0.9f;
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 12.0f, 4.0f, 0.0f, 5);
        if (this->actionFunc != func_80ACBDFC) {
            Collider_UpdateCylinder(&this->actor, &this->collider);
            this->collider.dim.radius = this->actor.scale.x * 3000.0f;
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void ObjAqua_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjAqua* this = THIS;
    s32 framesTemp;
    s32 pad;
    s16 yaw = Camera_GetCamDirYaw(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x8000;
    s32 actionFuncTemp = this->actionFunc == func_80ACBDFC;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    framesTemp = ((globalCtx->gameplayFrames & 0x7FFFFFFF) * -0xA) & 0x1FF;
    if (actionFuncTemp) {
        framesTemp >>= 1;
    }
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, framesTemp, 0x20, 0x80));
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 170, 255, 255, this->alpha);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 150, 255, 0);
    if (actionFuncTemp) {
        s16 rotation = Math_SinS(this->unk_198) * 8000.0f;

        Matrix_InsertZRotation_s(rotation, MTXMODE_APPLY);
        Matrix_Scale(1.3f, 1.0f, 1.0f, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(rotation * -1, MTXMODE_APPLY);
        Matrix_Scale(10.0f / 13.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    }
    Matrix_RotateY(yaw, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
