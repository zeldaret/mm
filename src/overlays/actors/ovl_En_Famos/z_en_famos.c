/*
 * File: z_en_famos.c
 * Overlay: ovl_En_Famos
 * Description: Death Armos
 */

#include "z_en_famos.h"
#include "../ovl_En_Bom/z_en_bom.h"
#include "objects/object_famos/object_famos.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS ACTOR_FLAG_4 | ACTOR_FLAG_1

#define THIS ((EnFamos*)thisx)

void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808ACB58(EnFamos* this);
void func_808ACD2C(EnFamos* this);
void func_808AD05C(EnFamos* this);
void func_808AD170(EnFamos* this);
void func_808AD1F0(EnFamos* this);
void func_808AD31C(EnFamos* this);
void func_808AD3E8(EnFamos* this);
void func_808AD54C(EnFamos* this);
void func_808AD66C(EnFamos* this);
void func_808AD7EC(EnFamos* this);
void func_808AD888(EnFamos* this);
void func_808ADA74(EnFamos* this);
void func_808ADB4C(EnFamos* this);
void func_808ADC40(EnFamos* this);
void func_808ADD20(EnFamos* this);
void func_808ADE00(EnFamos* this);
void func_808ADFA4(EnFamos* this);

// action funcs
void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);
void func_808AD18C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD294(EnFamos* this, GlobalContext* globalCtx);
void func_808AD378(EnFamos* this, GlobalContext* globalCtx);
void func_808AD42C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD5B0(EnFamos* this, GlobalContext* globalCtx);
void func_808AD68C(EnFamos* this, GlobalContext* globalCtx);
void func_808AD840(EnFamos* this, GlobalContext* globalCtx);
void func_808AD8B8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADAE8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADB70(EnFamos* this, GlobalContext* globalCtx);
void func_808ADC64(EnFamos* this, GlobalContext* globalCtx);
void func_808ADDA8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADE74(EnFamos* this, GlobalContext* globalCtx);
void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);

s32 func_808ACF1C(EnFamos* this, GlobalContext* globalCtx);

s32 func_808AE304(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
void func_808AE3A8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor);
// draw func extension
void func_808AE3FC(EnFamos* this, GlobalContext* globalCtx);

const ActorInit En_Famos_InitVars = {
    ACTOR_EN_FAMOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FAMOS,
    sizeof(EnFamos),
    (ActorFunc)EnFamos_Init,
    (ActorFunc)EnFamos_Destroy,
    (ActorFunc)EnFamos_Update,
    (ActorFunc)EnFamos_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_METAL,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x20000000, 0x04, 0x10 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x04, 0x08 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { 70, 10, 0, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00002000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 2, { { 2500, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00002000, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 2, { { -1500, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    2,
    sJntSphElementsInit,
};

static AnimatedMaterial* D_808AE6B0[] = { gFamosAnimTex1, gFamosAnimTex2 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3500, ICHAIN_STOP),
};

static s32 animatedMaterialsVirtualized = false;

void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFamos* this = THIS;
    Path* path;
    s32 sTrue = 1;
    int i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (this->actor.params != 0xFF) {
        path = &globalCtx->setupPathList[this->actor.params];
        this->pathPoints = Lib_SegmentedToVirtual(path->points);
        this->pathNodeCount = path->count;
        if (this->pathNodeCount == 1) {
            this->pathPoints = NULL;
            this->pathNodeCount = 0;
        }
    }
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawSquare, 30.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gFamosSkeleton, &gFamosLowerSNSAnim, this->limbDrawTbl,
                   this->transitionDrawTbl, 6);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit1);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit2);
    Collider_InitAndSetJntSph(globalCtx, &this->collider3, &this->actor, &sJntSphInit, &this->collider3Elements);

    if (!animatedMaterialsVirtualized) {
        for (i = 0; i < ARRAY_COUNT(D_808AE6B0); i++) {
            D_808AE6B0[i] = Lib_SegmentedToVirtual(D_808AE6B0[i]);
        }
        animatedMaterialsVirtualized = sTrue;
    }

    this->actor.colChkInfo.mass = 0xFA; // not heavy, heavy is 0xFE
    this->unk1EC = this->actor.world.pos.y;
    this->unk1F0 = (this->actor.shape.rot.x <= 0) ? (200.0f) : (this->actor.shape.rot.x * 40.0f * 0.1f);
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;
    this->unk1D5 = 1;
    this->unk1D8 = 1;
    if (this->pathPoints != NULL) {
        func_808AD1F0(this);
    } else {
        func_808AD170(this);
    }
}

void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFamos* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyJntSph(globalCtx, &this->collider3);
}

// debris?
// todo rename vars
void func_808ACB58(EnFamos* this) {
    EnFamosParticle* particlePtr;
    f32 randFloat;
    s16 randOffset;
    s16 randSmall;
    s32 i;

    this->unk1DE = 0x28;
    particlePtr = &this->particles[0];
    for (i = 0; i < 20; ++i, ++particlePtr) {
        randSmall = Rand_Next() >> 0x10;
        randOffset = Rand_S16Offset(0x1800, 0x2800);
        randFloat = Rand_ZeroFloat(5.0f) + 5.0f;
        particlePtr->unkC.x = randFloat * Math_CosS(randOffset) * Math_SinS(randSmall);
        particlePtr->unkC.y = Math_SinS(randOffset) * randFloat + 3.0f;
        particlePtr->unkC.z = randFloat * Math_CosS(randOffset) * Math_CosS(randSmall);
        particlePtr->unk18.x = Rand_Next() >> 0x10;
        particlePtr->unk18.y = Rand_Next() >> 0x10;
        particlePtr->unk18.z = Rand_Next() >> 0x10;
        particlePtr->unk0.x = (Math_SinS(randSmall) * 20.0f) + this->actor.world.pos.x;
        particlePtr->unk0.y = this->actor.floorHeight;
        particlePtr->unk0.z = (Math_CosS(randSmall) * 20.0f) + this->actor.world.pos.z;
        particlePtr->unk20 = Rand_ZeroFloat(0.0015f) + (1 / 500.0f);
    }
}

void func_808ACD2C(EnFamos* this) {
    f32 randFloat;
    s16 randSmaller;
    s16 randSmall;
    EnFamosParticle* particlePtr;
    s32 i;

    this->unk1DE = 0x28;
    particlePtr = &this->particles[0];
    for (i = 0; i < 20; ++i, ++particlePtr) {
        randSmall = Rand_Next() >> 0x10;
        randSmaller = (u32)Rand_Next() >> 0x12;
        randFloat = Rand_ZeroFloat(6.0f) + 7.0f;
        particlePtr->unkC.x = randFloat * Math_CosS(randSmaller) * Math_SinS(randSmall);
        particlePtr->unkC.y = Math_SinS(randSmaller) * randFloat + 4.5f;
        particlePtr->unkC.z = randFloat * Math_CosS(randSmaller) * Math_CosS(randSmall);
        particlePtr->unk18.x = Rand_Next() >> 0x10;
        particlePtr->unk18.y = Rand_Next() >> 0x10;
        particlePtr->unk18.z = Rand_Next() >> 0x10;
        particlePtr->unk0.x = Math_SinS(randSmall) * 20.0f + this->actor.world.pos.x;
        particlePtr->unk0.y = randPlusMinusPoint5Scaled(60.0f) + (this->actor.world.pos.y + 40.0f);
        particlePtr->unk0.z = Math_CosS(randSmall) * 20.0f + this->actor.world.pos.z;
        // not quite 1/400 or 0.0025, 0xB -> 0xA
        particlePtr->unk20 = Rand_ZeroFloat(0.002f) + 0.0025000002f;
    }
}

s32 func_808ACF1C(EnFamos* this, GlobalContext* globalCtx) {
    if (Player_GetMask(globalCtx) != 0x10 &&
        Actor_XZDistanceToPoint(&GET_PLAYER(globalCtx)->actor, &this->unk200) < this->unk1F0 &&
        Actor_IsFacingPlayer(&this->actor, 0x5000)) {
        return true;
    } else {
        return false;
    }
}

void func_808ACF98(EnFamos* this) {
    if (this->hoverClk == 0) {
        this->hoverClk = 30;
    }

    this->hoverClk--;
    this->actor.world.pos.y = (Math_SinS(this->hoverClk * 2184) * 10.0f) + this->unk1EC;

    if (ABS_ALT(this->unk1E6) > 0x4000) {
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT_REVERSE - SFX_FLAG);
    } else {
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT - SFX_FLAG);
    }
}

// todo sfx
void func_808AD05C(EnFamos* this) {
    u8 scalled1E6;

    if (this->collider3.base.acFlags & AC_HIT) {
        this->collider3.base.acFlags &= ~AC_HIT;
        if (this->unk1D5 == 1) {
            if (this->animatedMaterialIndex != 0) {
                this->animatedMaterialIndex = 0;
                Actor_PlaySfxAtPos(&this->actor, 0x3A92U);
            } else {
                this->animatedMaterialIndex = 1;
                this->unk1E0 = 100;
                Actor_PlaySfxAtPos(&this->actor, 0x3A91U);
                Actor_PlaySfxAtPos(&this->actor, 0x3847U);
            }
            this->unk1D5 = 0;
        }
    } else {
        if (this->unk1E0 > 0) {
            if (--this->unk1E0 == 0) {
                if (this->animatedMaterialIndex != 0) {
                    Actor_PlaySfxAtPos(&this->actor, 0x3A92U);
                }
                this->animatedMaterialIndex = 0;
                this->unk1D5 = 0;
            }
        }
    }
    if (this->unk1D5 == 0) {
        if (this->animatedMaterialIndex != 0) {
            scalled1E6 = Math_ScaledStepToS(&this->unk1E6, -0x8000, 0x1000);
        } else {
            scalled1E6 = Math_ScaledStepToS(&this->unk1E6, 0, 0x1000);
        }
        this->unk1D5 = scalled1E6;
    }
}

void func_808AD170(EnFamos* this) {
    this->actionFunc = func_808AD18C;
    this->actor.speedXZ = 0.0f;
}

void func_808AD18C(EnFamos* this, GlobalContext* globalCtx) {
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    }
}

void func_808AD1F0(EnFamos* this) {
    if (this->unk1D8 != 0) {
        if (++this->currentPathNode == this->pathNodeCount) {
            this->currentPathNode = 0;
        }
    } else {
        this->unk1D8 = 1;
    }

    Math_Vec3s_ToVec3f(&this->targetDest, &this->pathPoints[this->currentPathNode]);
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->targetDest);
    this->actionFunc = func_808AD294;
    this->actor.speedXZ = 0.0f;
}

void func_808AD294(EnFamos* this, GlobalContext* globalCtx) {
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
        return;
    }
    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200)) {
        func_808AD3E8(this);
    }
}

void func_808AD31C(EnFamos* this) {
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->unk200);
    Math_Vec3f_Copy(&this->targetDest, &this->unk200);
    this->actionFunc = func_808AD378;
    this->actor.speedXZ = 0.0f;
}

void func_808AD378(EnFamos* this, GlobalContext* globalCtx) {
    func_808ACF98(this);
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    } else if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200)) {
        func_808AD3E8(this);
    }
}

void func_808AD3E8(EnFamos* this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.x = -Actor_PitchToPoint(&this->actor, &this->targetDest);
    this->actionFunc = func_808AD42C;
}

void func_808AD42C(EnFamos* this, GlobalContext* globalCtx) {
    f32 distance = Actor_XZDistanceToPoint(&this->actor, &this->targetDest);

    this->actor.shape.rot.y = Actor_YawToPoint(&this->actor, &this->targetDest);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_808ACF98(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (func_808ACF1C(this, globalCtx)) {
        func_808AD54C(this);
    } else if (distance < 20.0f) {
        if (this->pathPoints != 0) {
            func_808AD1F0(this);
        } else {
            func_808AD170(this);
        }
    } else if (distance < 40.0f) {
        Math_StepToF(&this->actor.speedXZ, 0.5f, 0.3f);
    } else {
        Math_StepToF(&this->actor.speedXZ, 3.0f, 0.3f);
    }
}

void func_808AD54C(EnFamos* this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->unk1DC = 8;
    this->actor.speedXZ = 0.0f;
    if (this->unk1D8 == 1) {
        this->unk1D8 = 0;
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    this->actionFunc = func_808AD5B0;
}

void func_808AD5B0(EnFamos* this, GlobalContext* globalCtx) {
    if (ABS_ALT(this->unk1E6) > 0x4000) {
        func_800B9010(&this->actor, 0x3294);
    } else {
        func_800B9010(&this->actor, 0x3293);
    }

    if (--this->unk1DC == 0) {
        this->actor.world.pos.y = this->unk1EC;
        func_808AD66C(this);
    } else {
        this->actor.world.pos.y = (Math_SinS((this->unk1DC) * 0x1000) * 30.0f) + this->unk1EC;
    }
}

void func_808AD66C(EnFamos* this) {
    this->hoverClk = 0;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808AD68C;
}

void func_808AD68C(EnFamos* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f abovePlayerPos;
    u32 surfaceType;

    func_808ACF98(this);
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    abovePlayerPos.x = player->actor.world.pos.x;
    abovePlayerPos.y = player->actor.world.pos.y + 100.0f;
    abovePlayerPos.z = player->actor.world.pos.z;
    this->actor.world.rot.x = -Actor_PitchToPoint(&this->actor, &abovePlayerPos);
    Math_StepToF(&this->actor.speedXZ, 6.0f, 0.5f);

    surfaceType = func_800C9B18(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
    if (this->actor.xzDistToPlayer < 30.0f && this->actor.floorHeight > -32000.0f && surfaceType != 0xC &&
        surfaceType != 0xD) {
        func_808AD7EC(this);

    } else if ((Player_GetMask(globalCtx) == 0x10) ||
               this->unk1F0 < Actor_XZDistanceToPoint(&GET_PLAYER(globalCtx)->actor, &this->unk200) ||
               Actor_IsFacingPlayer(&this->actor, 0x6000) == 0) {
        func_808ADC40(this);
    }
}

void func_808AD7EC(EnFamos* this) {
    Animation_PlayOnce(&this->skelAnime, &gFamosShakeAnim);
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AMOS_VOICE);
    this->actionFunc = func_808AD840;
}

void func_808AD840(EnFamos* this, GlobalContext* globalCtx) {
    func_800B9010(&this->actor, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808AD888(this);
    }
}

void func_808AD888(EnFamos* this) {
    this->actor.world.rot.x = -0x4000;
    this->collider1.base.atFlags |= AT_ON;
    this->unk1DC = 4;
    this->actionFunc = func_808AD8B8;
}

void func_808AD8B8(EnFamos* this, GlobalContext* globalCtx) {
    s32 hitWall;
    u32 surfaceType;

    Math_StepToF(&this->actor.speedXZ, 20.0f, 2.0f);
    this->unk1DC--;
    if (this->unk1DC == 0) {
        this->collider3.base.acFlags &= ~AC_ON;
    }

    surfaceType = func_800C9B18(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
    hitWall = this->actor.bgCheckFlags & BGCHECK_CHECK_WALL;
    if (hitWall || this->actor.floorHeight == BGCHECK_Y_MIN || surfaceType == 0xC || surfaceType == 0xD) {
        this->collider1.base.atFlags &= ~AT_ON;
        this->collider2.base.atFlags |= AT_ON;
        if (hitWall) {
            func_800DFD04(globalCtx->cameraPtrs[globalCtx->activeCamera], 2, 15, 10);
            func_8013ECE0(this->actor.xyzDistToPlayerSq, 180, 20, 100);
            func_808ACB58(this);
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, 1, this->actor.world.pos.x,
                               this->actor.floorHeight, this->actor.world.pos.z, 0, 0, 0, 0);

            if (this->actor.child != NULL) {
                Actor_SetScale(this->actor.child, 0.015f);
            }

            if (this->animatedMaterialIndex != 0) {
                this->unk1E2 = 0x46;
                func_808ADD20(this);
            } else {
                this->unk1E2 = 0x14;
                func_808ADA74(this);
            }
        } else {
            this->collider3.base.acFlags |= AC_ON;
            func_808ADB4C(this);
        }
    } else {
        func_800B9010(&this->actor, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
    }
}

void func_808ADA74(EnFamos* this) {
    Animation_PlayOnce(&this->skelAnime, &gFamosLowerSNSAnim);
    SkelAnime_Update(&this->skelAnime);
    this->collider3.base.acFlags |= AC_ON;
    this->unk1DC = 3;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_EXPLOSION);
    this->actionFunc = func_808ADAE8;
}

void func_808ADAE8(EnFamos* this, GlobalContext* globalCtx) {
    if (this->unk1DC == 0) {
        this->collider2.base.atFlags &= ~AT_ON;
    }
    this->unk1DC--;
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808ADB4C(this);
    }
}

void func_808ADB4C(EnFamos* this) {
    this->actor.world.rot.x = 0x4000;
    this->actionFunc = func_808ADB70;
    this->actor.speedXZ = 0.0f;
}

void func_808ADB70(EnFamos* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 5.0f, 0.3f);
    if (this->actor.speedXZ > 1.0f) {
        if (ABS_ALT(this->unk1E6) > 0x4000) {
            func_800B9010(&this->actor, 0x3294U);
        } else {
            func_800B9010(&this->actor, 0x3293U);
        }
    }
    if (this->unk1EC < this->actor.world.pos.y || this->actor.bgCheckFlags & BGCHECK_CHECK_DYNA) {
        this->actor.speedXZ = 0.0f;
        func_808AD66C(this);
    }
}

void func_808ADC40(EnFamos* this) {
    this->unk1DC = 60;
    this->actionFunc = func_808ADC64;
    this->actor.speedXZ = 0.0f;
}

void func_808ADC64(EnFamos* this, GlobalContext* globalCtx) {

    func_808ACF98(&this->actor);
    this->unk1DC--;
    if (func_808ACF1C(this, globalCtx) != 0) {
        func_808AD54C(this);
    } else if (this->unk1DC == 0) {
        func_808AD31C(this);
    } else {
        this->actor.shape.rot.y = (s32)(Math_SinS(this->unk1DC * 0x888) * 8192.0f) + this->actor.world.rot.y;
    }
}

void func_808ADD20(EnFamos* this) {
    this->collider3.base.acFlags &= ~AC_ON;
    this->unk1DC = 20;
    this->actor.speedXZ = 0.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 20);
    this->unk1E0 = -1;
    // aiming for players feet?
    this->actor.world.pos.y = this->actor.floorHeight - 60.0f;
    Actor_PlaySfxAtPos(&this->actor, 0x3846);
    this->actionFunc = func_808ADDA8;
}

void func_808ADDA8(EnFamos* this, GlobalContext* globalCtx) {
    if (this->unk1DC == 17) {
        this->collider2.base.atFlags &= ~AT_ON;
    }
    if (this->unk1DC == 0) {
        func_808ADE00(this);
    } else {
        this->unk1DC--;
    }
}

void func_808ADE00(EnFamos* this) {
    this->actor.world.rot.x = 0x4000;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 4);
    this->unk1DC = 25;
    Math_Vec3f_Copy(&this->targetDest, &this->actor.world.pos);
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = func_808ADE74;
}

void func_808ADE74(EnFamos* this, GlobalContext* globalCtx) {

    Math_StepToF(&this->actor.speedXZ, 3.0f, 0.3f);
    if (this->actor.colorFilterTimer == 0) {
        Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 4);
    }

    this->actor.world.pos.x = randPlusMinusPoint5Scaled(5.0f) + this->targetDest.x;
    this->actor.world.pos.z = randPlusMinusPoint5Scaled(5.0f) + this->targetDest.z;
    if (this->unk1DC == 1) {
        EnBom* blast = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                           this->actor.world.pos.y + 40.0f, this->actor.world.pos.z, 0, 0, 0, 0);
        if (blast != NULL) {
            blast->timer = 0; // instant explosion
        }
        this->unk1DC--;
    } else if (this->unk1DC == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xD0);
        func_808ADFA4(this);
    } else {
        this->unk1DC--;
    }
}

void func_808ADFA4(EnFamos* this) {
    func_808ACD2C(this);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.shape.shadowDraw = NULL;
    this->actionFunc = func_808ADFF0;
    this->actor.speedXZ = 0.0f;
}

void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx) {
    Actor* ourChild;

    if (this->unk1DE == 0) {
        ourChild = this->actor.child;
        if (ourChild != NULL) {
            ourChild->parent = NULL;
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void func_808AE030(EnFamos* this) {
    EnFamosParticle* particle;
    s32 i;

    particle = &this->particles[0];
    for (i = 0; i < 20; ++i, ++particle) {
        particle->unkC.y -= 1.0f;
        Math_Vec3f_Sum(&particle->unk0, &particle->unkC, &particle->unk0);
        particle->unk18.x += (s16)(((u32)Rand_Next() >> 0x17) + 0x700);
        particle->unk18.y += (s16)(((u32)Rand_Next() >> 0x17) + 0x900);
        particle->unk18.z += (s16)(((u32)Rand_Next() >> 0x17) + 0xB00);
    }
}

void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFamos* this = THIS;
    f32 oldHeight;
    s32 hoverClkOld;

    if (this->unk1DE <= 0 || (this->unk1DE--, func_808AE030(this), (this->actionFunc != func_808ADFF0))) {
        hoverClkOld = this->hoverClk;
        func_808AD05C(this);
        if (this->unk1E2 > 0) {
            if (--this->unk1E2 == 0) {
                this->actor.child->parent = NULL;
            }
        }

        this->actionFunc(this, globalCtx);
        oldHeight = this->actor.world.pos.y;
        Actor_MoveWithoutGravity(&this->actor);
        if (hoverClkOld != this->hoverClk) {
            this->unk1EC += this->actor.world.pos.y - oldHeight;
        }

        if (this->unk1E0 >= 0) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 35.0f, 30.0f, 80.0f, 0x1F);
            if (this->actionFunc == func_808AD8B8 && this->animatedMaterialIndex != 0 &&
                this->actor.bgCheckFlags & BGCHECK_CHECK_WALL) {
                this->actor.world.pos.y -= 60.0f;
            }
        }

        this->actor.focus.rot.y = this->actor.shape.rot.y;
        Collider_UpdateCylinder(&this->actor, &this->collider1);
        if (this->collider1.base.atFlags & AT_ON) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        }

        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        if (this->collider3.base.acFlags & AC_ON) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider3.base);
        }

        if (this->collider2.base.atFlags & AC_ON) {
            Collider_UpdateCylinder(&this->actor, &this->collider2);
            this->collider2.dim.pos.y = this->actor.floorHeight;
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        }
    }
}

// override limb draw
s32 func_808AE304(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor) {
    EnFamos* this = (EnFamos*)actor;

    if (limbIndex == 1) { // BODY
        Matrix_InsertTranslation(0.0f, 4000.0f, 0.0f, 1);
        Matrix_InsertZRotation_s(this->unk1E6, 1);
        Matrix_InsertTranslation(0.0f, -4000.0f, 0.0f, 1);

    } else if (this->unk1E0 < 0 && (limbIndex == 3 || limbIndex == 4 || limbIndex == 5)) {
        // sword, shield, head (not body and not the emblem)
        *dList = NULL;
    }

    return 0;
}

// post limb draw
void func_808AE3A8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
    EnFamos* this = (EnFamos*)actor;

    if (limbIndex == 2) { // emblem
        Matrix_GetStateTranslation(&actor->focus.pos);
        Collider_UpdateSpheres(limbIndex, &this->collider3);
    }
}

void func_808AE3FC(EnFamos* this, GlobalContext* globalCtx) {
    s32 i;

    if (this->unk1DE > 0) {
        Gfx* dispOpa;
        EnFamosParticle* particle;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        dispOpa = POLY_OPA_DISP;

        gSPDisplayList(&dispOpa[0], &sSetupDL[0x96]);

        gDPSetPrimColor(&dispOpa[1], 0, 0x80, 255, 255, 255, 255);

        gDPSetEnvColor(&dispOpa[2], 255, 255, 255, 255);

        particle = &this->particles[0];
        for (i = 0; i < 20; i++) {
            Matrix_SetStateRotationAndTranslation(particle->unk0.x, particle->unk0.y, particle->unk0.z,
                                                  &particle->unk18);
            Matrix_Scale(particle->unk20, particle->unk20, particle->unk20, 1);

            gSPMatrix(&dispOpa[3 + (i * 2)], Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPDisplayList(&dispOpa[4 + (i * 2)], &gameplay_keep_DL_06AB30);

            particle++;
        }

        POLY_OPA_DISP = &dispOpa[3 + (20 * 2)];

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFamos* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->actionFunc != func_808ADFF0) {
        AnimatedMat_Draw(globalCtx, D_808AE6B0[this->animatedMaterialIndex]);
        SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_808AE304, func_808AE3A8,
                          &this->actor);
        if (this->actor.colorFilterTimer != 0) {
            func_800AE5A0(globalCtx);
        }
    }
    func_808AE3FC(this, globalCtx);
}
