/*
 * File: z_en_mm.c
 * Overlay: ovl_En_Mm
 * Description: Rock Sirloin
 */

#include "z_en_mm.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnMm*)thisx)

void EnMm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80965D3C(EnMm* this, GlobalContext* globalCtx);
void func_80965DB4(EnMm* this, GlobalContext* globalCtx);
void func_8096611C(EnMm* this, GlobalContext* globalCtx);
void EnMm_SetupAction(EnMm* this, EnMmActionFunc actionFunc);

const ActorInit En_Mm_InitVars = {
    ACTOR_EN_MM,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMm),
    (ActorFunc)EnMm_Init,
    (ActorFunc)EnMm_Destroy,
    (ActorFunc)EnMm_Update,
    (ActorFunc)EnMm_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x00 },
        { 0x01000202, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 6, 30, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -1200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 270, ICHAIN_STOP),
};

void EnMm_SetupAction(EnMm* this, EnMmActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_80965BBC(EnMm* this) {
    EnMm_SetupAction(this, func_8096611C);
    this->actor.room = -1;
    if (this->actor.parent->id == ACTOR_PLAYER) {
        gSaveContext.unk_1014 = 1;
    }
}

void EnMm_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;
    EnMmActionFunc action;

    if ((this->actor.params >= 0) && ((!(gSaveContext.save.weekEventReg[37] & 0x10)) ||
                                      (gSaveContext.save.weekEventReg[37] & 8) || (gSaveContext.unk_1014 != 0))) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 50.0f, ActorShadow_DrawCircle, 1.2f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    if (this->actor.parent != NULL) {
        func_80965BBC(this);
        return;
    }
    if (this->actor.cutscene >= 0) {
        action = func_80965D3C;
    } else {
        action = func_80965DB4;
    }
    EnMm_SetupAction(this, action);
}

void EnMm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80965D3C(EnMm* this, GlobalContext* globalCtx) {
    s16 cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);

    if (ActorCutscene_GetCanPlayNext(cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(cutscene, &this->actor);
        EnMm_SetupAction(this, func_80965DB4);
    } else {
        ActorCutscene_SetIntentToPlay(cutscene);
    }
}

void func_80965DB4(EnMm* this, GlobalContext* globalCtx) {
    s16 direction;
    Vec3f sp50;
    s16 unused;
    f32 temp_f14;
    f32 temp_f12;
    f32 temp_f2;
    s32 angle;
    s32 pad;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        func_80965BBC(this);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_PULL_UP_ROCK);
    } else {
        if ((this->actor.velocity.y > 0.0f) && (this->actor.bgCheckFlags & 0x10)) {
            this->actor.velocity.y = 0.0f;
        }

        if ((this->actor.speedXZ != 0.0f) && (this->actor.bgCheckFlags & 8)) {
            angle = BINANG_SUB(this->actor.world.rot.y, BINANG_ROT180(this->actor.wallYaw));
            this->actor.world.rot.y += BINANG_SUB(0x8000, (s16)(angle * 2));
            this->actor.speedXZ *= 0.5f;
            CollisionCheck_SpawnShieldParticles(globalCtx, &this->actor.world.pos);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HUMAN_BOUND);
        }

        if (!(this->actor.bgCheckFlags & 1)) {
            Math_StepToF(&this->actor.speedXZ, 0.0f, 0.08f);
        } else {
            temp_f14 = Math_SinS(this->actor.world.rot.y) * this->actor.speedXZ;
            temp_f12 = Math_CosS(this->actor.world.rot.y) * this->actor.speedXZ;
            func_800B75A0(this->actor.floorPoly, &sp50, &unused);
            temp_f14 += 3.0f * sp50.x;
            temp_f12 += 3.0f * sp50.z;
            temp_f2 = sqrtf(SQ(temp_f14) + SQ(temp_f12));

            if ((temp_f2 < this->actor.speedXZ) ||
                (SurfaceType_GetSlope(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId) == 1)) {
                this->actor.speedXZ = CLAMP_MAX(temp_f2, 16.0f);
                this->actor.world.rot.y = Math_FAtan2F(temp_f12, temp_f14);
            }

            if (!Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f)) {
                direction = this->actor.world.rot.y;
                if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, this->actor.shape.rot.y)) > 0x4000) {
                    direction = BINANG_ROT180(direction);
                }
                Math_ScaledStepToS(&this->actor.shape.rot.y, direction, this->actor.speedXZ * 100.0f);
                this->unk_190 += (s16)(this->actor.speedXZ * 800.0f);
            }

            if (this->actor.bgCheckFlags & 2) {
                if (this->actor.velocity.y < -6.0f) {
                    this->actor.velocity.y *= -0.3f;
                    this->actor.bgCheckFlags &= ~1;
                }

                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HUMAN_BOUND);
            } else {
                Actor_PickUp(&this->actor, globalCtx, GI_NONE, 50.0f, 30.0f);
            }
        }

        Actor_MoveWithGravity(&this->actor);
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_8096611C(EnMm* this, GlobalContext* globalCtx) {
    if (Actor_HasNoParent(&this->actor, globalCtx)) {
        EnMm_SetupAction(this, func_80965DB4);
        this->actor.room = globalCtx->roomCtx.currRoom.num;
        this->actor.bgCheckFlags &= ~1;
        Math_Vec3s_ToVec3f(&this->actor.prevPos, &this->actor.home.rot);
        gSaveContext.unk_1014 = 0;
    } else {
        Math_Vec3f_ToVec3s(&this->actor.home.rot, &this->actor.parent->world.pos);
    }
    Math_ScaledStepToS(&this->unk_190, 0, 2000);
}

void EnMm_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;

    Collider_ResetCylinderAC(globalCtx, &this->collider.base);
    this->actionFunc(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 10.0f, 20.0f, 31);
    Actor_SetFocus(&this->actor, 20.0f);
}

void EnMm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMm* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->unk_190 != 0) {
        s16 rotY = this->actor.world.rot.y - this->actor.shape.rot.y;

        Matrix_RotateY(rotY, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_190, MTXMODE_APPLY);
        Matrix_RotateY(-rotY, MTXMODE_APPLY);
    }
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_055628);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
