/*
 * File: z_en_syateki_crow.c
 * Overlay: ovl_En_Syateki_Crow
 * Description: Shooting Gallery Guay
 */

#include "z_en_syateki_crow.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"
#include "objects/object_crow/object_crow.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiCrow*)thisx)

void EnSyatekiCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809CA5D4(EnSyatekiCrow* this);
void func_809CA67C(EnSyatekiCrow* this, GlobalContext* globalCtx);
void func_809CA71C(EnSyatekiCrow* this);
void func_809CA840(EnSyatekiCrow* this, GlobalContext* globalCtx);
void func_809CA8E4(EnSyatekiCrow* this, GlobalContext* globalCtx);
void func_809CABC0(EnSyatekiCrow* this, GlobalContext* globalCtx);

static Vec3f D_809CB050 = { 0.0f, 0.0f, 0.0f };

const ActorInit En_Syateki_Crow_InitVars = {
    ACTOR_EN_SYATEKI_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnSyatekiCrow),
    (ActorFunc)EnSyatekiCrow_Init,
    (ActorFunc)EnSyatekiCrow_Destroy,
    (ActorFunc)EnSyatekiCrow_Update,
    (ActorFunc)EnSyatekiCrow_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 60, 0 }, 50 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 3000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 88, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

static Vec3f D_809CB0C0 = { 0.0f, 20.0f, 0.0f };

static Vec3f D_809CB0CC = { 0.0f, 0.0f, 0.0f };

static Vec3f D_809CB0D8 = { 2500.0f, 0.0f, 0.0f };

void EnSyatekiCrow_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnSyatekiCrow* this = THIS;
    Path* path;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s32 i;

    path = syatekiMan->path;
    while (path->unk2 != 0) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    for (i = 0; i < EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor); i++) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGuaySkel, &gGuayFlyAnim, this->jointTable, this->morphTable,
                       OBJECT_CROW_LIMB_MAX);
    Collider_InitJntSph(globalCtx, &this->unk_23C);
    Collider_SetJntSph(globalCtx, &this->unk_23C, &this->actor, &sJntSphInit, &this->unk_25C);
    this->unk_23C.elements->dim.worldSphere.radius = sJntSphInit.elements[0].dim.modelSphere.radius;
    ActorShape_Init(&this->actor.shape, 2000.0f, ActorShadow_DrawCircle, 20.0f);

    if ((path == NULL) || (EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor) >= 0x80)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_1C8 = Lib_SegmentedToVirtual(path->points);
    this->unk_1CC = 1;
    this->unk_1CE = path->count;
    this->unk_1C4 = 0x14;
    this->unk_1BC = 0;
    func_809CA5D4(this);
}

void EnSyatekiCrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiCrow* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->unk_23C);
}

void func_809CA5D4(EnSyatekiCrow* this) {
    Actor_SetScale(&this->actor, 0.03f);
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.world = this->actor.home;
    this->actor.prevPos = this->actor.home.pos;
    this->actor.shape.rot = this->actor.world.rot;
    this->unk_1CC = 1;
    this->actor.draw = NULL;
    this->actionFunc = func_809CA67C;
}

void func_809CA67C(EnSyatekiCrow* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if ((syatekiMan->unk_26A == 1) && (this->unk_1C2 == 1) &&
        (syatekiMan->unk_274 & (1 << EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor)))) {
        func_809CA71C(this);
    } else if (syatekiMan->unk_26A != 1) {
        this->unk_1C2 = 1;
    }

    if ((syatekiMan->unk_274 == 0) && (syatekiMan->unk_274 == 0)) {
        this->unk_1C2 = 1;
    }
}

void func_809CA71C(EnSyatekiCrow* this) {
    Vec3f sp24;
    s16 temp;

    this->actor.world.pos.x = this->unk_1C8[0].x;
    this->actor.world.pos.y = this->unk_1C8[0].y;
    this->actor.world.pos.z = this->unk_1C8[0].z;
    sp24.x = this->unk_1C8[this->unk_1CC].x;
    sp24.y = this->unk_1C8[this->unk_1CC].y;
    sp24.z = this->unk_1C8[this->unk_1CC].z;
    temp = Math_Vec3f_Yaw(&this->actor.world.pos, &sp24);
    this->actor.world.rot.y = temp;
    this->actor.shape.rot.y = temp;
    temp = Math_Vec3f_Pitch(&this->actor.world.pos, &sp24);
    this->actor.shape.rot.x = temp;
    this->actor.world.rot.x = temp;
    this->actor.draw = EnSyatekiCrow_Draw;
    this->actionFunc = func_809CA840;
}

void func_809CA840(EnSyatekiCrow* this, GlobalContext* globalCtx) {
    if (((EN_SYATEKI_CROW_GET_PARAM_F(&this->actor) * 20) + 20) < this->unk_1BC) {
        Actor_PlaySfxAtPos(this->actor.parent, NA_SE_EN_KAICHO_CRY);
        this->unk_1BC = 0;
        this->actor.speedXZ = EN_SYATEKI_CROW_GET_PARAM_F0(&this->actor) + 6.0f;
        this->actor.gravity = -0.5f;
        this->actionFunc = func_809CA8E4;
    } else {
        this->unk_1BC++;
    }
}

void func_809CA8E4(EnSyatekiCrow* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    f32 sp30;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (syatekiMan->unk_26A != 1) {
        func_809CA5D4(this);
        return;
    }

    sp34.x = this->unk_1C8[this->unk_1CC].x;
    sp34.y = this->unk_1C8[this->unk_1CC].y;
    sp34.z = this->unk_1C8[this->unk_1CC].z;

    sp30 = Math_Vec3f_DistXZ(&this->actor.world.pos, &sp34);
    this->unk_1C0 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp34);
    this->unk_1BE = Math_Vec3f_Pitch(&this->actor.world.pos, &sp34);

    if (sp30 > 100.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_1C0, 5, 0x3000, 0x100);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Math_SmoothStepToS(&this->actor.shape.rot.x, this->unk_1BE, 5, 0x3000, 0x100);
        this->actor.world.rot.x = -this->actor.shape.rot.x;
    } else if (this->unk_1CC < (this->unk_1CE - 1)) {
        this->unk_1CC++;
    } else {
        this->unk_1C2 = 0;
        syatekiMan->unk_274 &= ~(1 << EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor));
        func_809CA5D4(this);
    }

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.yOffset = (fabsf(this->skelAnime.curFrame - 3.0f) * 150.0f) + 1700.0f;
    if ((syatekiMan->unk_26C % 90) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_CRY);
    }
}

void func_809CAAF8(EnSyatekiCrow* this) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    syatekiMan->unk_280 += 60;
    this->unk_1C2 = 0;
    this->actor.speedXZ *= Math_CosS(this->actor.world.rot.x);
    this->actor.velocity.y = 0.0f;
    Animation_Change(&this->skelAnime, &gGuayFlyAnim, 0.4f, 0.0f, 0.0f, 1, -3.0f);
    this->actor.bgCheckFlags &= ~1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_DEAD);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
    this->actionFunc = func_809CABC0;
}

void func_809CABC0(EnSyatekiCrow* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    this->actor.colorFilterTimer = 40;

    if (this->actor.colorFilterParams & 0x4000) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
        this->actor.shape.rot.z += 0x1780;
    }

    if (this->unk_1C4 > 20) {
        func_800B3030(globalCtx, &this->actor.world.pos, &D_809CB050, &D_809CB050, this->actor.scale.x * 10000.0f, 0,
                      0);
        syatekiMan->unk_27A++;
        syatekiMan->unk_274 &= ~(1 << EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor));
        func_809CA5D4(this);
    }

    this->unk_1C4++;
}

void func_809CACD0(EnSyatekiCrow* this, GlobalContext* globalCtx) {
    if (this->actionFunc == func_809CA8E4) {
        if (this->unk_23C.base.acFlags & AC_HIT) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            this->unk_1C4 = 0;
            this->unk_23C.base.acFlags &= ~AC_HIT;
            EffectSsExtra_Spawn(globalCtx, &this->actor.world.pos, &D_809CB0C0, &D_809CB0CC, 5, 1);
            func_809CAAF8(this);
        } else {
            this->unk_23C.elements->dim.worldSphere.center.x = this->actor.world.pos.x;
            this->unk_23C.elements->dim.worldSphere.center.y =
                sJntSphInit.elements[0].dim.modelSphere.center.y + this->actor.world.pos.y;
            this->unk_23C.elements->dim.worldSphere.center.z = this->actor.world.pos.z;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_23C.base);
        }
    }
}

void EnSyatekiCrow_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiCrow* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->actionFunc != func_809CABC0) {
        Actor_MoveWithoutGravity(&this->actor);
    } else {
        Actor_MoveWithGravity(&this->actor);
    }

    func_809CACD0(this, globalCtx);
}

s32 EnSyatekiCrow_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                   Actor* thisx) {
    EnSyatekiCrow* this = THIS;

    if (limbIndex == OBJECT_CROW_LIMB_UPPER_TAIL) {
        rot->y += (s16)(3072.0f * sin_rad(this->skelAnime.curFrame * (M_PI / 4)));
    } else if (limbIndex == OBJECT_CROW_LIMB_TAIL) {
        rot->y += (s16)(5120.0f * sin_rad((this->skelAnime.curFrame + 2.5f) * (M_PI / 4)));
    }

    return false;
}

void EnSyatekiCrow_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnSyatekiCrow* this = THIS;
    Vec3f* sp1C;

    if (limbIndex == OBJECT_CROW_LIMB_BODY) {
        Matrix_MultiplyVector3fByState(&D_809CB0D8, &this->unk_144[0]);
        this->unk_144[0].y -= 20.0f;
    } else if ((limbIndex == OBJECT_CROW_LIMB_RIGHT_WING_TIP) || (limbIndex == OBJECT_CROW_LIMB_LEFT_WING_TIP) ||
               (limbIndex == OBJECT_CROW_LIMB_TAIL)) {
        sp1C = &this->unk_144[(limbIndex >> 1) - 1];
        Matrix_MultiplyVector3fByState(&D_809CB050, sp1C);
        sp1C->y -= 20.0f;
    }
}

void EnSyatekiCrow_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiCrow* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnSyatekiCrow_OverrideLimbDraw, EnSyatekiCrow_PostLimbDraw, &this->actor);
}
