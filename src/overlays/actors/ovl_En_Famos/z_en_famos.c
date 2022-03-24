/*
 * File: z_en_famos.c
 * Overlay: ovl_En_Famos
 * Description: Death Armos (floating statue enemy in Inverted Stone Tower Temple)
 */

#include "z_en_famos.h"
#include "../ovl_En_Bom/z_en_bom.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnFamos*)thisx)

void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808ACB58(EnFamos* this);
void func_808ACD2C(EnFamos* this);
void EnFamos_UpdateFlipStatus(EnFamos* this);
void EnFamos_SetupStillIdle(EnFamos* this);
void EnFamos_SetupPathingIdle(EnFamos* this);
void EnFamos_SetupTurnHome(EnFamos* this);
void EnFamos_SetupReturnHome(EnFamos* this);
void EnFamos_SetupAlert(EnFamos* this);
void EnFamos_SetupChase(EnFamos* this);
void EnFamos_SetupAttackAim(EnFamos* this);
void EnFamos_SetupAttack(EnFamos* this);
void EnFamos_SetupFinishAttack(EnFamos* this);
void func_808ADB4C(EnFamos* this);
void EnFamos_SetupDropAgro(EnFamos* this);
void func_808ADD20(EnFamos* this);
void func_808ADE00(EnFamos* this);
void func_808ADFA4(EnFamos* this);

void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_StillIdle(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_PathingIdle(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_TurnHome(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_ReturnHome(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_Alert(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_Chase(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_AttackAim(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_Attack(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_FinishAttack(EnFamos* this, GlobalContext* globalCtx);
void func_808ADB70(EnFamos* this, GlobalContext* globalCtx);
void EnFamos_DropAgro(EnFamos* this, GlobalContext* globalCtx);
void func_808ADDA8(EnFamos* this, GlobalContext* globalCtx);
void func_808ADE74(EnFamos* this, GlobalContext* globalCtx);
void func_808ADFF0(EnFamos* this, GlobalContext* globalCtx);

s32 EnFamos_IsPlayerSeen(EnFamos* this, GlobalContext* globalCtx);

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

// normal is greenish, flipped its orange/yellowish
#define FAMOS_ANIMATED_MATERIAL_NORMAL 0
#define FAMOS_ANIMATED_MATERIAL_FLIPPED 1
static AnimatedMaterial* sEmblemAnimatedMaterials[] = { gFamosNormalGlowingEmblemAnimTex , gFamosFlippedGlowingEmblemAnimTex };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3500, ICHAIN_STOP),
};

static s32 animatedMaterialsVirtualized = false;

// in savestate KZ its 8040DAE0
void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFamos* this = THIS;
    Path* path;
    s32 sTrue = 1; // required to be separate to match
    int i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (GET_FAMOS_PATH(thisx) != 0xFF) {
        path = &globalCtx->setupPathList[this->actor.params];
        this->pathPoints = Lib_SegmentedToVirtual(path->points);
        this->pathNodeCount = path->count;
        if (this->pathNodeCount == 1) {
            this->pathPoints = NULL;
            this->pathNodeCount = 0;
        }
    }
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawSquare, 30.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gFamosSkeleton, &gFamosLowerSNSAnim, this->jointTable,
                   this->morphTable, 6);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit1);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit2);
    Collider_InitAndSetJntSph(globalCtx, &this->emblemCollider, &this->actor, &sJntSphInit, &this->emblemColliderElements);

    // init animated materials
    if (!animatedMaterialsVirtualized) {
        for (i = 0; i < ARRAY_COUNT(sEmblemAnimatedMaterials); i++) {
            sEmblemAnimatedMaterials[i] = Lib_SegmentedToVirtual(sEmblemAnimatedMaterials[i]);
        }
        animatedMaterialsVirtualized = sTrue;
    }

    this->actor.colChkInfo.mass = 250; // not heavy (heavy = 0xFE/252)
    this->unk1EC = this->actor.world.pos.y;
    this->unk1F0 = (this->actor.shape.rot.x <= 0) ? (200.0f) : (this->actor.shape.rot.x * 40.0f * 0.1f);
    this->actor.shape.rot.x = 0;
    this->actor.world.rot.x = 0;
    this->stableRotation = true;
    this->unk1D8 = 1;
    if (this->pathPoints != NULL) {
        EnFamos_SetupPathingIdle(this);
    } else {
        EnFamos_SetupStillIdle(this);
    }
}

void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFamos* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
    Collider_DestroyJntSph(globalCtx, &this->emblemCollider);
}

// debris?
// todo rename vars
void func_808ACB58(EnFamos* this) {
    EnFamosParticle* particlePtr;
    f32 randFloat;
    s16 randOffset;
    s16 randVelDirection;
    s32 i;

    this->unk1DE = 0x28;
    particlePtr = &this->particles[0];
    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particlePtr++) {
        randVelDirection = Rand_Next() >> 0x10;
        randOffset = Rand_S16Offset(0x1800, 0x2800);
        randFloat = Rand_ZeroFloat(5.0f) + 5.0f;
        particlePtr->velocity.x = randFloat * Math_CosS(randOffset) * Math_SinS(randVelDirection);
        particlePtr->velocity.y = Math_SinS(randOffset) * randFloat + 3.0f;
        particlePtr->velocity.z = randFloat * Math_CosS(randOffset) * Math_CosS(randVelDirection);
        particlePtr->rotation.x = Rand_Next() >> 0x10;
        particlePtr->rotation.y = Rand_Next() >> 0x10;
        particlePtr->rotation.z = Rand_Next() >> 0x10;
        particlePtr->pos.x = (Math_SinS(randVelDirection) * 20.0f) + this->actor.world.pos.x;
        particlePtr->pos.y = this->actor.floorHeight;
        particlePtr->pos.z = (Math_CosS(randVelDirection) * 20.0f) + this->actor.world.pos.z;
        particlePtr->scale = Rand_ZeroFloat(0.0015f) + (2.0f * 0.001f);
    }
}

void func_808ACD2C(EnFamos* this) {
    f32 randFloat;
    s16 randSmaller;
    s16 randVelDirection;
    EnFamosParticle* particlePtr;
    s32 i;

    this->unk1DE = 0x28;
    particlePtr = &this->particles[0];
    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particlePtr++) {
        randVelDirection = Rand_Next() >> 0x10;
        randSmaller = (u32)Rand_Next() >> 0x12;
        randFloat = Rand_ZeroFloat(6.0f) + 7.0f;
        particlePtr->velocity.x = randFloat * Math_CosS(randSmaller) * Math_SinS(randVelDirection);
        particlePtr->velocity.y = Math_SinS(randSmaller) * randFloat + 4.5f;
        particlePtr->velocity.z = randFloat * Math_CosS(randSmaller) * Math_CosS(randVelDirection);
        particlePtr->rotation.x = Rand_Next() >> 0x10;
        particlePtr->rotation.y = Rand_Next() >> 0x10;
        particlePtr->rotation.z = Rand_Next() >> 0x10;
        particlePtr->pos.x = Math_SinS(randVelDirection) * 20.0f + this->actor.world.pos.x;
        particlePtr->pos.y = randPlusMinusPoint5Scaled(60.0f) + (this->actor.world.pos.y + 40.0f);
        particlePtr->pos.z = Math_CosS(randVelDirection) * 20.0f + this->actor.world.pos.z;
        particlePtr->scale = Rand_ZeroFloat(0.002f) + (2.5f * 0.001f);
    }
}

s32 EnFamos_IsPlayerSeen(EnFamos* this, GlobalContext* globalCtx) {
    if (Player_GetMask(globalCtx) != PLAYER_MASK_STONE &&
        Actor_XZDistanceToPoint(&GET_PLAYER(globalCtx)->actor, &this->unk200) < this->unk1F0 &&
        Actor_IsFacingPlayer(&this->actor, 0x5000)) {
        return true;
    } else {
        return false;
    }
}

// KZ: 8040DF30
void EnFamos_UpdateBobbingHeight(EnFamos* this) {
    if (this->hoverClk == 0) {
        this->hoverClk = 30; // half way down decending
    }

    this->hoverClk--;
    this->actor.world.pos.y = (Math_SinS(this->hoverClk * 2184) * 10.0f) + this->unk1EC;

    // is famos upside down
    if (ABS_ALT(this->unk1E6) > 0x4000) {
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT_REVERSE - SFX_FLAG);
    } else {
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT - SFX_FLAG);
    }
}

/**
 * checks if hit with light arrow
 * also checks if previously flipped, handles flip timer
 */
void EnFamos_UpdateFlipStatus(EnFamos* this) {
    u8 famosRotTest;

    if (this->emblemCollider.base.acFlags & AC_HIT) { // light arrow collision, flip 
        this->emblemCollider.base.acFlags &= ~AC_HIT;
        if (this->stableRotation == true) {
            if (this->animatedMaterialIndex != FAMOS_ANIMATED_MATERIAL_NORMAL) {
                this->animatedMaterialIndex = FAMOS_ANIMATED_MATERIAL_NORMAL;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FAMOS_REVERSE2);
            } else {
                this->animatedMaterialIndex = FAMOS_ANIMATED_MATERIAL_FLIPPED;
                this->flippedTimer = 100;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FAMOS_REVERSE1);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_DAMAGE);
            }
            this->stableRotation = false;
        }
    } else if (this->flippedTimer > 0) { // currently flipped, timer remaining
        if (--this->flippedTimer == 0) { // timer finished
            if (this->animatedMaterialIndex != FAMOS_ANIMATED_MATERIAL_NORMAL) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FAMOS_REVERSE2);
            }
            this->animatedMaterialIndex = FAMOS_ANIMATED_MATERIAL_NORMAL;
            this->stableRotation = false;
        }
    }

    if (this->stableRotation == false) {
        if (this->animatedMaterialIndex != FAMOS_ANIMATED_MATERIAL_NORMAL) {
            famosRotTest = Math_ScaledStepToS(&this->unk1E6, -0x8000, 0x1000);
        } else {
            famosRotTest = Math_ScaledStepToS(&this->unk1E6, 0, 0x1000);
        }
        this->stableRotation = famosRotTest; // sets true when flipping is done
    }
}

/**
 * (unused) If Famos path is 0xFF, famos floats still in the air without a path to follow
 */
void EnFamos_SetupStillIdle(EnFamos* this) {
    this->actionFunc = EnFamos_StillIdle;
    this->actor.speedXZ = 0.0f;
}

void EnFamos_StillIdle(EnFamos* this, GlobalContext* globalCtx) {
    EnFamos_UpdateBobbingHeight(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (EnFamos_IsPlayerSeen(this, globalCtx)) {
        EnFamos_SetupAlert(this);
    }
}

void EnFamos_SetupPathingIdle(EnFamos* this) {
    if (this->unk1D8 != 0) {
        if (++this->currentPathNode == this->pathNodeCount) {
            this->currentPathNode = 0;
        }
    } else {
        this->unk1D8 = 1;
    }

    Math_Vec3s_ToVec3f(&this->targetDest, &this->pathPoints[this->currentPathNode]);
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->targetDest);
    this->actionFunc = EnFamos_PathingIdle;
    this->actor.speedXZ = 0.0f;
}

void EnFamos_PathingIdle(EnFamos* this, GlobalContext* globalCtx) {
    EnFamos_UpdateBobbingHeight(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (EnFamos_IsPlayerSeen(this, globalCtx)) {
        EnFamos_SetupAlert(this);
    } else if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200)) {
        EnFamos_SetupReturnHome(this);
    }
}

// kz: 8040E2B0
// armos lost player, turning to face back toward home
void EnFamos_SetupTurnHome(EnFamos* this) {
    this->unk1E4 = Actor_YawToPoint(&this->actor, &this->unk200);
    Math_Vec3f_Copy(&this->targetDest, &this->unk200);
    this->actionFunc = EnFamos_TurnHome;
    this->actor.speedXZ = 0.0f;
}

void EnFamos_TurnHome(EnFamos* this, GlobalContext* globalCtx) {
    EnFamos_UpdateBobbingHeight(this);
    if (EnFamos_IsPlayerSeen(this, globalCtx)) {
        EnFamos_SetupAlert(this);
    } else if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk1E4, 0x200)) {
        EnFamos_SetupReturnHome(this);
    }
}

// flying straight to home location
void EnFamos_SetupReturnHome(EnFamos* this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.x = -Actor_PitchToPoint(&this->actor, &this->targetDest);
    this->actionFunc = EnFamos_ReturnHome;
}

void EnFamos_ReturnHome(EnFamos* this, GlobalContext* globalCtx) {
    f32 distance = Actor_XZDistanceToPoint(&this->actor, &this->targetDest);

    this->actor.shape.rot.y = Actor_YawToPoint(&this->actor, &this->targetDest);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    EnFamos_UpdateBobbingHeight(this);
    if (this->unk1D8 != 0) {
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    if (EnFamos_IsPlayerSeen(this, globalCtx)) {
        EnFamos_SetupAlert(this);
    } else if (distance < 20.0f) {
        if (this->pathPoints != 0) {
            EnFamos_SetupPathingIdle(this);
        } else {
            EnFamos_SetupStillIdle(this);
        }
    } else if (distance < 40.0f) {
        Math_StepToF(&this->actor.speedXZ, 0.5f, 0.3f);
    } else {
        Math_StepToF(&this->actor.speedXZ, 3.0f, 0.3f);
    }
}

// famos first spots player, pauses for a 8 frames figuring out what to do
void EnFamos_SetupAlert(EnFamos* this) {
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->delayTimer = 8;
    this->actor.speedXZ = 0.0f;
    if (this->unk1D8 == 1) {
        this->unk1D8 = 0;
        Math_Vec3f_Copy(&this->unk200, &this->actor.world.pos);
    }
    this->actionFunc = EnFamos_Alert;
}

// famos first spots player !
void EnFamos_Alert(EnFamos* this, GlobalContext* globalCtx) {
    if (ABS_ALT(this->unk1E6) > 0x4000) {
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT_REVERSE - SFX_FLAG);
    } else {
        func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT - SFX_FLAG);
    }

    if (--this->delayTimer == 0) {
        this->actor.world.pos.y = this->unk1EC;
        EnFamos_SetupChase(this);
    } else {
        this->actor.world.pos.y = (Math_SinS(this->delayTimer * 0x1000) * 30.0f) + this->unk1EC;
    }
}

void EnFamos_SetupChase(EnFamos* this) {
    this->hoverClk = 0;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnFamos_Chase;
}

void EnFamos_Chase(EnFamos* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f abovePlayerPos;
    u32 surfaceType;

    EnFamos_UpdateBobbingHeight(this);
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    abovePlayerPos.x = player->actor.world.pos.x;
    abovePlayerPos.y = player->actor.world.pos.y + 100.0f;
    abovePlayerPos.z = player->actor.world.pos.z;
    this->actor.world.rot.x = -Actor_PitchToPoint(&this->actor, &abovePlayerPos);
    Math_StepToF(&this->actor.speedXZ, 6.0f, 0.5f);

    surfaceType = func_800C9B18(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
    if (this->actor.xzDistToPlayer < 30.0f && this->actor.floorHeight > BGCHECK_Y_MIN && surfaceType != 0xC &&
        surfaceType != 0xD) {
        EnFamos_SetupAttackAim(this);

    } else if (Player_GetMask(globalCtx) == PLAYER_MASK_STONE ||
               this->unk1F0 < Actor_XZDistanceToPoint(&GET_PLAYER(globalCtx)->actor, &this->unk200) ||
               Actor_IsFacingPlayer(&this->actor, 0x6000) == 0) {
        EnFamos_SetupDropAgro(this);
    }
}

void EnFamos_SetupAttackAim(EnFamos* this) {
    Animation_PlayOnce(&this->skelAnime, &gFamosShakeAnim);
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AMOS_VOICE);
    this->actionFunc = EnFamos_AttackAim;
}

void EnFamos_AttackAim(EnFamos* this, GlobalContext* globalCtx) {
    func_800B9010(&this->actor, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
    if (SkelAnime_Update(&this->skelAnime)) {
        EnFamos_SetupAttack(this);
    }
}

void EnFamos_SetupAttack(EnFamos* this) {
    this->actor.world.rot.x = -0x4000;
    this->collider1.base.atFlags |= AT_ON;
    this->delayTimer = 4;
    this->actionFunc = EnFamos_Attack;
}

void EnFamos_Attack(EnFamos* this, GlobalContext* globalCtx) {
    s32 hitFloor;
    u32 surfaceType;

    Math_StepToF(&this->actor.speedXZ, 20.0f, 2.0f);
    if (--this->delayTimer == 0) {
        this->emblemCollider.base.acFlags &= ~AC_ON;
    }

    surfaceType = func_800C9B18(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
    hitFloor = this->actor.bgCheckFlags & 1; // on floor
    if (hitFloor || this->actor.floorHeight == BGCHECK_Y_MIN || surfaceType == 0xC || surfaceType == 0xD) {
        this->collider1.base.atFlags &= ~AT_ON;
        this->collider2.base.atFlags |= AT_ON;
        if (hitFloor) {
            func_800DFD04(globalCtx->cameraPtrs[globalCtx->activeCamera], 2, 15, 10);
            func_8013ECE0(this->actor.xyzDistToPlayerSq, 180, 20, 100);
            func_808ACB58(this);
            // spawn crator actor on floor
            Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_TEST, this->actor.world.pos.x,
                               this->actor.floorHeight, this->actor.world.pos.z, 0, 0, 0, 0x0);

            if (this->actor.child != NULL) {
                Actor_SetScale(this->actor.child, 0.015f);
            }

            if (this->animatedMaterialIndex != FAMOS_ANIMATED_MATERIAL_NORMAL) {
                this->unk1E2 = 0x46;
                func_808ADD20(this);
            } else {
                this->unk1E2 = 0x14;
                EnFamos_SetupFinishAttack(this);
            }
        } else {
            this->emblemCollider.base.acFlags |= AC_ON;
            func_808ADB4C(this);
        }
    } else {
        func_800B9010(&this->actor, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
    }
}

// collide with player/ground
void EnFamos_SetupFinishAttack(EnFamos* this) {
    Animation_PlayOnce(&this->skelAnime, &gFamosLowerSNSAnim);
    SkelAnime_Update(&this->skelAnime);
    this->emblemCollider.base.acFlags |= AC_ON;
    this->delayTimer = 3;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_EXPLOSION);
    this->actionFunc = EnFamos_FinishAttack;
}

// collide with player
void EnFamos_FinishAttack(EnFamos* this, GlobalContext* globalCtx) {
    if (this->delayTimer == 0) {
        this->collider2.base.atFlags &= ~AT_ON;
    }
    this->delayTimer--;
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808ADB4C(this);
    }
}

// recover from ground hit?
void func_808ADB4C(EnFamos* this) {
    this->actor.world.rot.x = 0x4000;
    this->actionFunc = func_808ADB70;
    this->actor.speedXZ = 0.0f;
}

// recover from ground hit?
void func_808ADB70(EnFamos* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 5.0f, 0.3f);
    if (this->actor.speedXZ > 1.0f) {
        if (ABS_ALT(this->unk1E6) > 0x4000) {
            func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT_REVERSE - SFX_FLAG);
        } else {
            func_800B9010(&this->actor, NA_SE_EN_FAMOS_FLOAT - SFX_FLAG);
        }
    }

    if (this->unk1EC < this->actor.world.pos.y || this->actor.bgCheckFlags & 0x10) { // touching ceiling
        this->actor.speedXZ = 0.0f;
        EnFamos_SetupChase(this);
    }
}

// scanning side-to-side for player
void EnFamos_SetupDropAgro(EnFamos* this) {
    this->delayTimer = 60;
    this->actionFunc = EnFamos_DropAgro;
    this->actor.speedXZ = 0.0f;
}

void EnFamos_DropAgro(EnFamos* this, GlobalContext* globalCtx) {

    EnFamos_UpdateBobbingHeight(this);
    this->delayTimer--;
    if (EnFamos_IsPlayerSeen(this, globalCtx)) {
        EnFamos_SetupAlert(this);
    } else if (this->delayTimer == 0) {
        EnFamos_SetupTurnHome(this);
    } else {
        // cast req
        this->actor.shape.rot.y = (s32)(Math_SinS(this->delayTimer * 0x888) * 8192.0f) + this->actor.world.rot.y;
    }
}

// 8040ECB4 in kz
void func_808ADD20(EnFamos* this) {
    this->emblemCollider.base.acFlags &= ~AC_ON;
    this->delayTimer = 20;
    this->actor.speedXZ = 0.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 20);
    this->flippedTimer = -1;
    // aiming for players feet?
    this->actor.world.pos.y = this->actor.floorHeight - 60.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EYEGOLE_DEAD);
    this->actionFunc = func_808ADDA8;
}

void func_808ADDA8(EnFamos* this, GlobalContext* globalCtx) {
    if (this->delayTimer == 17) {
        this->collider2.base.atFlags &= ~AT_ON;
    }
    if (this->delayTimer == 0) {
        func_808ADE00(this);
    } else {
        this->delayTimer--;
    }
}

void func_808ADE00(EnFamos* this) {
    this->actor.world.rot.x = 0x4000;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 4);
    this->delayTimer = 25;
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
    if (this->delayTimer == 1) {
        EnBom* blast = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                           this->actor.world.pos.y + 40.0f, this->actor.world.pos.z, 0, 0, 0, 0x0000);
        if (blast != NULL) {
            blast->timer = 0; // instant explosion
        }
        this->delayTimer--;
    } else if (this->delayTimer == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xD0); // random item from table 0xD
        func_808ADFA4(this);
    } else {
        this->delayTimer--;
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
    EnFamosParticle* particlePtr;
    s32 i;

    particlePtr = &this->particles[0];
    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particlePtr++) {
        particlePtr->velocity.y -= 1.0f;
        Math_Vec3f_Sum(&particlePtr->pos, &particlePtr->velocity, &particlePtr->pos);
        // all casts seem required
        particlePtr->rotation.x += (s16)(((u32)Rand_Next() >> 0x17) + 0x700);
        particlePtr->rotation.y += (s16)(((u32)Rand_Next() >> 0x17) + 0x900);
        particlePtr->rotation.z += (s16)(((u32)Rand_Next() >> 0x17) + 0xB00);
    }
}

void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFamos* this = THIS;
    f32 oldHeight;
    s32 hoverClkOld; // where does it change?

    if (this->unk1DE <= 0 || (this->unk1DE--, func_808AE030(this), (this->actionFunc != func_808ADFF0))) {
        hoverClkOld = this->hoverClk;
        EnFamos_UpdateFlipStatus(this);
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

        if (this->flippedTimer >= 0) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 35.0f, 30.0f, 80.0f, 0x1F);
            if (this->actionFunc == EnFamos_Attack && this->animatedMaterialIndex != FAMOS_ANIMATED_MATERIAL_NORMAL &&
                this->actor.bgCheckFlags & 1) { // on floor

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
        if (this->emblemCollider.base.acFlags & AC_ON) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->emblemCollider.base);
        }

        if (this->collider2.base.atFlags & AC_ON) {
            Collider_UpdateCylinder(&this->actor, &this->collider2);
            this->collider2.dim.pos.y = this->actor.floorHeight;
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        }
    }
}

// override limb draw
s32 func_808AE304(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnFamos* this = THIS;

    if (limbIndex == FAMOS_LIMB_BODY) {
        Matrix_InsertTranslation(0.0f, 4000.0f, 0.0f, 1);
        Matrix_InsertZRotation_s(this->unk1E6, 1);
        Matrix_InsertTranslation(0.0f, -4000.0f, 0.0f, 1);

    } else if (this->flippedTimer < 0 && (limbIndex == FAMOS_LIMB_SWORD || limbIndex == FAMOS_LIMB_SHIELD || limbIndex == FAMOS_LIMB_HEAD)) {
        *dList = NULL;
    }

    return 0;
}

// post limb draw
void func_808AE3A8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnFamos* this = THIS;

    if (limbIndex == FAMOS_LIMB_EMBLEM) {
        Matrix_GetStateTranslation(&this->actor.focus.pos);
        Collider_UpdateSpheres(limbIndex, &this->emblemCollider);
    }
}

// draw particles? when/what are these? the dirt it sends flying?
void func_808AE3FC(EnFamos* this, GlobalContext* globalCtx) {
    s32 i;

    if (this->unk1DE > 0) {
        Gfx* dispOpa;
        EnFamosParticle* particlePtr;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        dispOpa = POLY_OPA_DISP;

        gSPDisplayList(&dispOpa[0], &sSetupDL[0x96]);

        gDPSetPrimColor(&dispOpa[1], 0, 0x80, 255, 255, 255, 255);

        gDPSetEnvColor(&dispOpa[2], 255, 255, 255, 255);

        particlePtr = &this->particles[0];
        for (i = 0; i < ARRAY_COUNT(this->particles); i++, particlePtr++) {
            
            Matrix_SetStateRotationAndTranslation(particlePtr->pos.x, particlePtr->pos.y, particlePtr->pos.z,
                                                  &particlePtr->rotation);
            Matrix_Scale(particlePtr->scale, particlePtr->scale, particlePtr->scale, 1);

            gSPMatrix(&dispOpa[3 + (i * 2)], Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPDisplayList(&dispOpa[4 + (i * 2)], &gameplay_keep_DL_06AB30);

        }

        POLY_OPA_DISP = &dispOpa[3 + (20 * 2)];

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnFamos* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    if (this->actionFunc != func_808ADFF0) {
        AnimatedMat_Draw(globalCtx, sEmblemAnimatedMaterials[this->animatedMaterialIndex]);
        SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_808AE304, func_808AE3A8,
                          &this->actor);
        if (this->actor.colorFilterTimer != 0) {
            func_800AE5A0(globalCtx);
        }
    }
    func_808AE3FC(this, globalCtx);
}
