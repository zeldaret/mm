/*
 * File: z_en_pametfrog.c
 * Overlay: En_Pametfrog
 * Description: Gekko & Snapper Miniboss: Gekko
 */

#include "z_en_pametfrog.h"
#include "overlays/actors/ovl_En_Bigpamet/z_en_bigpamet.h"
#include "overlays/effects/ovl_Effect_Ss_Hahen/z_eff_ss_hahen.h"

#define FLAGS 0x00000035

#define THIS ((EnPametfrog*)thisx)

void EnPametfrog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnPametfrog_JumpWaterEffects(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_RearOnSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_RearOnSnapperWave(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupRearOnSnapperWave(EnPametfrog* this);
void EnPametfrog_RearOnSnapperWave(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupRearOnSnapperRise(EnPametfrog* this);
void EnPametfrog_RearOnSnapperRise(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_FallOffSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupJumpToWall(EnPametfrog* this);
void EnPametfrog_JumpToWall(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupWallCrawl(EnPametfrog* this);
void EnPametfrog_WallCrawl(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupWallPause(EnPametfrog* this);
void EnPametfrog_WallPause(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupClimbDownWall(EnPametfrog* this);
void EnPametfrog_ClimbDownWall(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupRunToSnapper(EnPametfrog* this);
void EnPametfrog_RunToSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupJumpOnSnapper(EnPametfrog* this);
void EnPametfrog_JumpOnSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupLandOnSnapper(EnPametfrog* this);
void EnPametfrog_LandOnSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_FallInAir(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_FallOnGround(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupFallOnGround(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupDefeatGekko(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_DefeatGekko(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupDefeatSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_DefeatSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupSpawnFrog(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SpawnFrog(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_PlayCutscene(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupLookAround(EnPametfrog* this);
void EnPametfrog_LookAround(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupJumpToLink(EnPametfrog* this);
void EnPametfrog_JumpToLink(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupMeleeAttack(EnPametfrog* this);
void EnPametfrog_MeleeAttack(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupCutscene(EnPametfrog* this);
void EnPametfrog_Damage(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_Stun(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupCallSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_CallSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupSnapperSpawn(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SnapperSpawn(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_SetupTransitionGekkoSnapper(EnPametfrog* this, GlobalContext* globalCtx);
void EnPametfrog_TransitionGekkoSnapper(EnPametfrog* this, GlobalContext* globalCtx);

extern AnimationHeader D_06000994; // Begin Rear on Snapper
extern AnimationHeader D_06001B08; // Call Snapper
extern AnimationHeader D_06001E14; // Crawl on Wall
extern AnimationHeader D_06001F20; // Falling
extern AnimationHeader D_060030E4; // Get up from Back
extern AnimationHeader D_0600347C; // Jab Punch
extern AnimationHeader D_060039C4; // Jump on Ground
extern AnimationHeader D_06003F28; // Kick
extern AnimationHeader D_06004298; // Fall on Back
extern AnimationHeader D_06004680; // Idle
extern AnimationHeader D_06004894; // Jump on Snapper
extern AnimationHeader D_06004D50; // Continue Rear on Snapper
extern AnimationHeader D_060050B8; // Squeeze Body
extern AnimationHeader D_060052EC; // Land on Snapper
extern AnimationHeader D_06005694; // Wiggle
extern AnimationHeader D_06005D54; // Head Knockback
extern AnimationHeader D_060066B4; // Look Around
extern AnimationHeader D_060070C4; // Hook Punch
extern FlexSkeletonHeader D_0600DF98;
extern AnimationHeader D_0600F048; // Windup Punch
extern AnimationHeader D_0600F990; // Melee Ready Stance

const ActorInit En_Pametfrog_InitVars = {
    ACTOR_EN_PAMETFROG,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnPametfrog),
    (ActorFunc)EnPametfrog_Init,
    (ActorFunc)EnPametfrog_Destroy,
    (ActorFunc)EnPametfrog_Update,
    (ActorFunc)EnPametfrog_Draw,
};

typedef enum {
    /* 0x0 */ GEKKO_DMGEFF_NONE,
    /* 0x1 */ GEKKO_DMGEFF_STUN,
    /* 0x2 */ GEKKO_DMGEFF_FIRE,
    /* 0x3 */ GEKKO_DMGEFF_ICE,
    /* 0x4 */ GEKKO_DMGEFF_LIGHT,
    /* 0x5 */ GEKKO_DMGEFF_ZORA_BARRIER,
} EnPametfrogDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, GEKKO_DMGEFF_STUN),
    /* Deku Stick     */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(0, GEKKO_DMGEFF_STUN),
    /* Goron punch    */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(2, GEKKO_DMGEFF_FIRE),
    /* Ice arrow      */ DMG_ENTRY(2, GEKKO_DMGEFF_ICE),
    /* Light arrow    */ DMG_ENTRY(2, GEKKO_DMGEFF_LIGHT),
    /* Goron spikes   */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(0, GEKKO_DMGEFF_STUN),
    /* Deku bubble    */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(2, GEKKO_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, GEKKO_DMGEFF_STUN),
    /* Zora barrier   */ DMG_ENTRY(0, GEKKO_DMGEFF_ZORA_BARRIER),
    /* Normal shield  */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, GEKKO_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, GEKKO_DMGEFF_NONE),
};

static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 32 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_WOOD,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 25 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT6,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    2,
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInit = { 3, 30, 60, 50 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 69, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(targetArrowOffset, -13221, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 10, ICHAIN_STOP),
};

// gSaveContext.weekEventReg[KEY] = VALUE
// KEY | VALUE
static s32 isFrogReturnedFlags[] = {
    (32 << 8) | 0x40, // Woodfall Temple Frog Returned
    (32 << 8) | 0x80, // Great Bay Temple Frog Returned
    (33 << 8) | 0x01, // Southern Swamp Frog Returned
    (33 << 8) | 0x02, // Laundry Pool Frog Returned
};

void EnPametfrog_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPametfrog* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 55.0f);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInit);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600DF98, &D_0600F990, this->limbDrawTable,
                     this->transitionDrawTable, 24);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colElement);
    this->params = CLAMP(this->actor.params, 1, 4);
    if (Actor_GetRoomCleared(globalCtx, globalCtx->roomCtx.currRoom.num)) {
        Actor_MarkForDeath(&this->actor);
        if (!(gSaveContext.weekEventReg[isFrogReturnedFlags[this->actor.params - 1] >> 8] &
              (u8)isFrogReturnedFlags[this->actor.params - 1])) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_MINIFROG, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, this->params);
        }
    } else {
        for (i = 0; i < 2; i++) {
            this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius;
        }

        if (Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_BIGPAMET,
                               this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0,
                               0) == NULL) {
            Actor_MarkForDeath(&this->actor);
        } else {
            this->actor.params = GEKKO_PRE_SNAPPER;
            EnPametfrog_SetupLookAround(this);
        }
    }
}

void EnPametfrog_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPametfrog* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

u8 EnPametfrog_Vec3fNormalize(Vec3f* vec) {
    f32 magnitude = Math3D_Vec3fMagnitude(vec);

    if (magnitude < 0.0001f) {
        return false;
    } else {
        Math_Vec3f_Scale(vec, 1.0f / magnitude);
        return true;
    }
}

void EnPametfrog_ChangeColliderFreeze(EnPametfrog* this) {
    this->drawEffect = GEKKO_DRAW_EFFECT_FROZEN;
    this->collider.base.colType = COLTYPE_HIT3;
    this->collider.elements->info.elemType = ELEMTYPE_UNK0;
    this->unk_2C8 = 0.75f;
    this->unk_2CC = 1.125f;
    this->unk_2C4 = 1.0f;
}

void EnPametfrog_ChangeColliderThaw(EnPametfrog* this, GlobalContext* globalCtx) {
    this->freezeTimer = 0;
    if (this->drawEffect == GEKKO_DRAW_EFFECT_FROZEN) {
        this->drawEffect = GEKKO_DRAW_EFFECT_NONE;
        this->collider.base.colType = COLTYPE_HIT6;
        this->collider.elements->info.elemType = ELEMTYPE_UNK1;
        this->unk_2C4 = 0.0f;
        func_800BF7CC(globalCtx, &this->actor, this->limbPos, 12, 2, 0.3f, 0.2f);
    }
}

void EnPametfrog_JumpWaterEffects(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f pos;

    if (this->actor.yDistToWater > 0.0f) {
        pos.x = this->actor.world.pos.x;
        pos.z = this->actor.world.pos.z;
        pos.y = this->actor.world.pos.y + this->actor.yDistToWater;
        EffectSsGRipple_Spawn(globalCtx, &pos, 150, 550, 0);
        pos.y += 8.0f;
        EffectSsGSplash_Spawn(globalCtx, &pos, NULL, NULL, 0, 550);
    }
}

void EnPametfrog_IdleWaterEffects(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f pos;

    if ((this->actor.yDistToWater > 0.0f) && ((globalCtx->gameplayFrames % 14) == 0)) {
        pos.x = this->actor.world.pos.x;
        pos.z = this->actor.world.pos.z;
        pos.y = this->actor.world.pos.y + this->actor.yDistToWater;
        EffectSsGRipple_Spawn(globalCtx, &pos, 150, 550, 0);
    }
}

void func_8086A238(EnPametfrog* this) {
    MtxF unkMtx;

    unkMtx.xx = this->unk_2E8.x;
    unkMtx.xy = this->unk_2E8.y;
    unkMtx.xz = this->unk_2E8.z;
    unkMtx.yx = this->unk_2DC.x;
    unkMtx.yy = this->unk_2DC.y;
    unkMtx.yz = this->unk_2DC.z;
    unkMtx.zx = this->unk_2D0.x;
    unkMtx.zy = this->unk_2D0.y;
    unkMtx.zz = this->unk_2D0.z;

    func_8018219C(&unkMtx, &this->actor.shape.rot, 0);
    this->actor.world.rot.x = -this->actor.shape.rot.x;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.z = this->actor.shape.rot.z;
}

s32 func_8086A2CC(EnPametfrog* this, CollisionPoly* floorPoly) {
    Vec3f floorNorm;
    Vec3f vec2;
    f32 rotation;
    f32 arg0;

    this->actor.floorPoly = floorPoly;
    floorNorm.x = COLPOLY_GET_NORMAL(floorPoly->normal.x);
    floorNorm.y = COLPOLY_GET_NORMAL(floorPoly->normal.y);
    floorNorm.z = COLPOLY_GET_NORMAL(floorPoly->normal.z);
    arg0 = DOTXYZ(&floorNorm, &this->unk_2DC);
    if (fabsf(arg0) >= 1.0f) {
        return false;
    }

    rotation = func_80086C48(arg0);
    if (rotation < 0.0001f) {
        return false;
    }

    Math3D_CrossProduct(&this->unk_2DC, &floorNorm, &vec2);
    EnPametfrog_Vec3fNormalize(&vec2);
    SysMatrix_InsertRotationAroundUnitVector_f(rotation, &vec2, 0);
    SysMatrix_MultiplyVector3fByState(&this->unk_2E8, &vec2);
    Math_Vec3f_Copy(&this->unk_2E8, &vec2);
    Math3D_CrossProduct(&this->unk_2E8, &floorNorm, &this->unk_2D0);
    EnPametfrog_Vec3fNormalize(&this->unk_2D0);
    Math_Vec3f_Copy(&this->unk_2DC, &floorNorm);
    return true;
}

void EnPametfrog_ShakeCamera(EnPametfrog* this, GlobalContext* globalCtx, f32 magShakeXZ, f32 magShakeY) {
    Camera* subCamera = Play_GetCamera(globalCtx, this->subCamId);
    s16 subCamYaw = BINANG_ROT180(Camera_GetCamDirYaw(subCamera));
    Vec3f subCamEye;

    subCamEye.x = (Math_SinS(subCamYaw) * magShakeXZ) + subCamera->at.x;
    subCamEye.y = subCamera->at.y + magShakeY;
    subCamEye.z = (Math_CosS(subCamYaw) * magShakeXZ) + subCamera->at.z;
    Play_CameraSetAtEye(globalCtx, this->subCamId, &subCamera->at, &subCamEye);
}

void EnPametfrog_StopCutscene(EnPametfrog* this, GlobalContext* globalCtx) {
    Camera* subCamera;

    if (this->subCamId != SUBCAM_FREE) {
        subCamera = Play_GetCamera(globalCtx, this->subCamId);
        Play_CameraSetAtEye(globalCtx, MAIN_CAM, &subCamera->at, &subCamera->eye);
        this->subCamId = SUBCAM_FREE;
        ActorCutscene_Stop(this->cutscene);
        func_800B724C(globalCtx, &this->actor, 6);
    }
}

void EnPametfrog_PlaceSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    CollisionPoly* poly;
    u32 bgId;
    Vec3f vec1;
    Vec3f vec2;
    Vec3f vec3;
    Actor* child;

    poly = NULL;
    this->actor.child->world.pos.x = (Math_SinS(this->actor.shape.rot.y) * 300.0f) + this->actor.world.pos.x;
    this->actor.child->world.pos.z = (Math_CosS(this->actor.shape.rot.y) * 300.0f) + this->actor.world.pos.z;
    this->actor.child->shape.rot.y = BINANG_ROT180(this->actor.shape.rot.y);
    vec2.x = this->actor.child->world.pos.x;
    vec2.y = this->actor.child->world.pos.y + 50.0f;
    vec2.z = this->actor.child->world.pos.z;
    vec3.x = this->actor.child->world.pos.x;
    vec3.y = this->actor.child->world.pos.y - 150.0f;
    vec3.z = this->actor.child->world.pos.z;
    if (func_800C55C4(&globalCtx->colCtx, &vec2, &vec3, &vec1, &poly, 0, 1, 0, 1, &bgId) != 0) {
        this->actor.child->floorHeight = vec1.y;
    } else {
        this->actor.child->floorHeight = this->actor.home.pos.y;
    }

    child = this->actor.child;
    child->world.pos.y = child->floorHeight - 60.0f;
}

void EnPametfrog_JumpOnGround(EnPametfrog* this, GlobalContext* globalCtx) {
    if (func_801378B8(&this->skelAnime, 1.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_JUMP);
    } else if (func_801378B8(&this->skelAnime, 11.0f)) {
        EnPametfrog_JumpWaterEffects(this, globalCtx);
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_WALK_WATER);
    }
}

void EnPametfrog_ApplyMagicArrowEffects(EnPametfrog* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_FIRE) {
        this->drawEffect = GEKKO_DRAW_EFFECT_NONE;
        this->unk_2C4 = 3.0f;
        this->unk_2C8 = 0.75f;
    } else if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_LIGHT) {
        this->drawEffect = GEKKO_DRAW_EFFECT_LIGHT_ORBS;
        this->unk_2C8 = 0.75f;
        this->unk_2C4 = 3.0f;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                    this->collider.elements[0].info.bumper.hitPos.x, this->collider.elements[0].info.bumper.hitPos.y,
                    this->collider.elements[0].info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
    } else if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_ICE) {
        EnPametfrog_ChangeColliderFreeze(this);
    }
}

void EnPametfrog_ApplyElectricStun(EnPametfrog* this) {
    this->freezeTimer = 40;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_COMMON_FREEZE);
    func_800BCB70(&this->actor, 0, 255, 0, 40);
    this->drawEffect = GEKKO_DRAW_EFFECT_ELECTRIC_STUN;
    this->unk_2C8 = 0.75f;
    this->unk_2C4 = 2.0f;
}

void EnPametfrog_ApplyStun(EnPametfrog* this) {
    this->freezeTimer = 40;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_COMMON_FREEZE);
    func_800BCB70(&this->actor, 0, 255, 0, 40);
}

void EnPametfrog_SetupRearOnSnapper(EnPametfrog* this) {
    if (this->actionFunc == EnPametfrog_RearOnSnapperRise) {
        SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06005694);
    } else if (this->actionFunc == EnPametfrog_RearOnSnapperWave) {
        SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060052EC);
    } else {
        SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06004680);
    }

    this->actor.flags &= ~1;
    this->actor.params = GEKKO_ON_SNAPPER;
    this->actionFunc = EnPametfrog_RearOnSnapper;
}

void EnPametfrog_RearOnSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    Actor* actor;
    Vec3f rearingPoint;
    s32 pad;

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        if (Rand_ZeroOne() < 0.5f) {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06004D50);
        } else {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06004680);
        }
    }

    actor = func_800BC270(globalCtx, &this->actor, 60.0f, 0x138B0);
    if (actor != NULL) {
        rearingPoint.x = this->actor.world.pos.x;
        rearingPoint.y = this->actor.world.pos.y + 10.0f;
        rearingPoint.z = this->actor.world.pos.z;
        if (actor->world.rot.x < Actor_PitchToPoint(actor, &rearingPoint)) {
            EnPametfrog_SetupRearOnSnapperWave(this);
        } else {
            EnPametfrog_SetupRearOnSnapperRise(this);
        }
    }
}

void EnPametfrog_SetupRearOnSnapperWave(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06004894);
    this->timer = 15;
    this->actionFunc = EnPametfrog_RearOnSnapperWave;
}

void EnPametfrog_RearOnSnapperWave(EnPametfrog* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) && this->timer > 0) {
        this->timer--;
        if (this->timer == 0) {
            EnPametfrog_SetupRearOnSnapper(this);
        }
    }
}

void EnPametfrog_SetupRearOnSnapperRise(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060050B8);
    this->timer = 10;
    this->actor.params = GEKKO_REAR_ON_SNAPPER;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->actor.shape.rot.y = this->actor.child->world.rot.y;
    this->actionFunc = EnPametfrog_RearOnSnapperRise;
}

void EnPametfrog_RearOnSnapperRise(EnPametfrog* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->timer--;
    if (this->timer == 0) {
        EnPametfrog_SetupRearOnSnapper(this);
    } else {
        this->actor.world.pos.y =
            Math_SinS(this->timer * 0xCCC) * 100.0f + (((EnBigpamet*)this->actor.child)->unk_2AC + 46.0f);
    }
}

void EnPametfrog_SetupFallOffSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f subCamEye;
    s16 yaw;

    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06001F20);
    this->actor.params = GEKKO_FALL_OFF_SNAPPER;
    this->actor.speedXZ = 7.0f;
    this->actor.velocity.y = 15.0f;
    this->actor.world.rot.y = BINANG_ROT180(this->actor.child->world.rot.y);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actor.flags |= 1;
    this->timer = 30;
    this->collider.base.ocFlags1 |= OC1_ON;
    yaw = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    subCamEye.x = (Math_SinS(yaw) * 300.0f) + this->actor.focus.pos.x;
    subCamEye.y = this->actor.focus.pos.y + 100.0f;
    subCamEye.z = (Math_CosS(yaw) * 300.0f) + this->actor.focus.pos.z;
    Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.focus.pos, &subCamEye);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_DAMAGE);
    this->actionFunc = EnPametfrog_FallOffSnapper;
}

void EnPametfrog_FallOffSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    f32 sin;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.shape.rot.x += 0x800;
    this->actor.shape.rot.z += 0x1000;
    if (this->timer != 0) {
        this->timer--;
    }

    sin = sin_rad(this->timer * (M_PI / 3)) * ((0.02f * (this->timer * (1.0f / 6.0f))) + 0.005f) + 1.0f;
    EnPametfrog_ShakeCamera(this, globalCtx, 300.0f * sin, 100.0f * sin);
    if (this->actor.bgCheckFlags & 1) {
        EnPametfrog_StopCutscene(this, globalCtx);
        EnPametfrog_SetupJumpToWall(this);
    }
}

void EnPametfrog_SetupJumpToWall(EnPametfrog* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060039C4, 2.0f, 0.0f, 0.0f, 0, -2.0f);
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->actor.bgCheckFlags &= ~8;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_VOICE2);
    this->actionFunc = EnPametfrog_JumpToWall;
}

void EnPametfrog_JumpToWall(EnPametfrog* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    EnPametfrog_JumpOnGround(this, globalCtx);
    if ((this->actor.bgCheckFlags & 1) && (this->actor.bgCheckFlags & 8) && (this->actor.wallBgId == BGCHECK_SCENE) &&
        (COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.y) < 0.5f)) {
        EnPametfrog_SetupWallCrawl(this);
    } else if (!(this->actor.bgCheckFlags & 1) ||
               ((this->skelAnime.animCurrentFrame > 1.0f) && (this->skelAnime.animCurrentFrame < 12.0f))) {
        this->actor.speedXZ = 12.0f;
    } else {
        this->actor.speedXZ = 0.0f;
    }
}

void EnPametfrog_SetupWallCrawl(EnPametfrog* this) {
    if (this->actionFunc == EnPametfrog_JumpToWall) {
        SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001E14);
        this->collider.base.acFlags |= AC_ON;
        this->unk_2D0.x = 0.0f;
        this->unk_2D0.z = 0.0f;
        this->actor.gravity = 0.0f;
        this->actor.world.pos.y = this->actor.focus.pos.y;
        this->unk_2D0.y = 1.0f;
        Math_Vec3f_Copy(&this->actor.colChkInfo.displacement, &D_801D15B0);
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
        this->unk_2DC.x = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
        this->unk_2DC.y = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.y);
        this->unk_2DC.z = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);
        Math3D_CrossProduct(&this->unk_2DC, &this->unk_2D0, &this->unk_2E8);
        EnPametfrog_Vec3fNormalize(&this->unk_2E8);
        Math3D_CrossProduct(&this->unk_2E8, &this->unk_2DC, &this->unk_2D0);
        EnPametfrog_Vec3fNormalize(&this->unk_2D0);
        func_8086A238(this);
        this->actor.floorPoly = this->actor.wallPoly;
        this->wallPauseTimer = 10;
    } else {
        this->skelAnime.animPlaybackSpeed = 1.0f;
    }

    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_RUNAWAY);
    this->actor.speedXZ = 8.0f;
    this->timer = Rand_S16Offset(35, 15);
    this->actionFunc = EnPametfrog_WallCrawl;
}

void EnPametfrog_WallCrawl(EnPametfrog* this, GlobalContext* globalCtx) {
    CollisionPoly* poly1 = NULL;
    CollisionPoly* poly2 = NULL;
    Vec3f vec1;
    Vec3f vec2;
    Vec3f worldPos1;
    Vec3f worldPos2;
    f32 doubleSpeedXZ;
    u32 bgId1;
    u32 bgId2;
    s32 isSuccess = false;

    if (this->freezeTimer > 0) {
        this->freezeTimer--;
    } else {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        this->timer--;
        this->actor.speedXZ = 8.0f;
        doubleSpeedXZ = this->actor.speedXZ * 2.0f;
        vec1.x = this->actor.world.pos.x + this->unk_2DC.x * 2.0f;
        vec1.y = this->actor.world.pos.y + this->unk_2DC.y * 2.0f;
        vec1.z = this->actor.world.pos.z + this->unk_2DC.z * 2.0f;
        vec2.x = this->actor.world.pos.x - this->unk_2DC.x * 25.0f;
        vec2.y = this->actor.world.pos.y - this->unk_2DC.y * 25.0f;
        vec2.z = this->actor.world.pos.z - this->unk_2DC.z * 25.0f;
        if (func_800C55C4(&globalCtx->colCtx, &vec1, &vec2, &worldPos2, &poly2, 1, 1, 1, 1, &bgId2) != 0) {
            vec2.x = this->unk_2D0.x * doubleSpeedXZ + vec1.x;
            vec2.y = this->unk_2D0.y * doubleSpeedXZ + vec1.y;
            vec2.z = this->unk_2D0.z * doubleSpeedXZ + vec1.z;
            if (func_800C55C4(&globalCtx->colCtx, &vec1, &vec2, &worldPos1, &poly1, 1, 1, 1, 1, &bgId1) != 0) {
                isSuccess = func_8086A2CC(this, poly1);
                Math_Vec3f_Copy(&this->actor.world.pos, &worldPos1);
                this->actor.floorBgId = bgId1;
                this->actor.speedXZ = 0.0f;
            } else {
                if (this->actor.floorPoly != poly2) {
                    isSuccess = func_8086A2CC(this, poly2);
                }
                Math_Vec3f_Copy(&this->actor.world.pos, &worldPos2);
                this->actor.floorBgId = bgId2;
            }
        } else {
            EnPametfrog_SetupClimbDownWall(this);
        }

        if (isSuccess) {
            func_8086A238(this);
        }

        if (func_801378B8(&this->skelAnime, 15.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_BOMCHU_WALK);
        }

        if (((globalCtx->gameplayFrames % 60) == 0) && (Rand_ZeroOne() < 0.8f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_REAL);
        }

        if ((this->timer == 0) ||
            ((this->actor.world.pos.y < (this->actor.home.pos.y + 200.0f)) && (this->unk_2D0.y <= 0.0f))) {
            this->wallPauseTimer--;
            if (this->wallPauseTimer == 0) {
                EnPametfrog_SetupClimbDownWall(this);
            } else {
                EnPametfrog_SetupWallPause(this);
            }
        }
    }
}

void EnPametfrog_SetupWallPause(EnPametfrog* this) {
    s32 pad;
    f32 randFloat;

    this->actor.speedXZ = 0.0f;
    this->skelAnime.animPlaybackSpeed = 1.5f;
    if (this->timer != 0) {
        this->wallRotation = this->unk_2E8.y > 0.0f ? (M_PI / 30) : (-M_PI / 30);
    } else {
        randFloat = Rand_ZeroFloat(0x2000);
        this->wallRotation = (Rand_ZeroOne() < 0.5f ? -1 : 1) * (0x1000 + randFloat) * (M_PI / (15 * 0x8000));
    }
    this->timer = 15;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_RUNAWAY2);
    this->actionFunc = EnPametfrog_WallPause;
}

void EnPametfrog_WallPause(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f vec;

    if (this->freezeTimer > 0) {
        this->freezeTimer--;
    } else {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        this->timer--;
        SysMatrix_InsertRotationAroundUnitVector_f(this->wallRotation, &this->unk_2DC, 0);
        SysMatrix_MultiplyVector3fByState(&this->unk_2D0, &vec);
        Math_Vec3f_Copy(&this->unk_2D0, &vec);
        Math3D_CrossProduct(&this->unk_2DC, &this->unk_2D0, &this->unk_2E8);
        func_8086A238(this);
        if (((globalCtx->gameplayFrames % 60) == 0) && (Rand_ZeroOne() < 0.8f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_REAL);
        }

        if (this->timer == 0) {
            EnPametfrog_SetupWallCrawl(this);
        }
    }
}

void EnPametfrog_SetupClimbDownWall(EnPametfrog* this) {
    s16 yaw;

    SkelAnime_ChangeAnim(&this->skelAnime, &D_060039C4, 0.0f, 0.0f, SkelAnime_GetFrameCount(&D_060039C4.common), 2,
                         0.0f);
    this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, this->actor.child);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->actor.colChkInfo.mass = 50;
    this->actor.speedXZ = 5.0f;
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -1.0f;
    yaw = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    this->actor.world.pos.x += 30.0f * Math_SinS(yaw);
    this->actor.world.pos.z += 30.0f * Math_CosS(yaw);
    this->actor.bgCheckFlags &= ~1;
    this->actor.params = GEKKO_RETURN_TO_SNAPPER;
    this->actionFunc = EnPametfrog_ClimbDownWall;
}

void EnPametfrog_ClimbDownWall(EnPametfrog* this, GlobalContext* globalCtx) {
    s16 yaw;

    if (this->actor.bgCheckFlags & 1) {
        EnPametfrog_SetupRunToSnapper(this);
    } else if (this->actor.floorHeight == BGCHECK_Y_MIN) {
        yaw = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
        this->actor.world.pos.x += 5.0f * Math_SinS(yaw);
        this->actor.world.pos.z += 5.0f * Math_CosS(yaw);
        if (this->actor.world.pos.y < (this->actor.home.pos.y - 5.0f)) {
            this->actor.world.pos.y = this->actor.home.pos.y;
        }
    }
}

void EnPametfrog_SetupRunToSnapper(EnPametfrog* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060039C4, 2.0f, 0.0f, 0.0f, 0, -2.0f);
    this->actor.params = GEKKO_RETURN_TO_SNAPPER;
    this->actionFunc = EnPametfrog_RunToSnapper;
}

void EnPametfrog_RunToSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    EnPametfrog_JumpOnGround(this, globalCtx);
    this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, this->actor.child);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (!(this->actor.bgCheckFlags & 1) ||
        ((this->skelAnime.animCurrentFrame > 1.0f) && (this->skelAnime.animCurrentFrame < 12.0f))) {
        this->actor.speedXZ = 12.0f;
    } else {
        this->actor.speedXZ = 0.0f;
    }

    if ((this->actor.child->params == 1) && (Actor_XZDistanceBetweenActors(&this->actor, this->actor.child) < 120.0f) &&
        func_801378B8(&this->skelAnime, 0.0f)) {
        EnPametfrog_SetupJumpOnSnapper(this);
    }
}

void EnPametfrog_SetupJumpOnSnapper(EnPametfrog* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06004680, 6.0f);
    this->timer = 6;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.shape.rot.y = Actor_YawBetweenActors(&this->actor, this->actor.child);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.params = GEKKO_JUMP_ON_SNAPPER;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_GREET);
    this->actionFunc = EnPametfrog_JumpOnSnapper;
}

void EnPametfrog_JumpOnSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    f32 temp_f0;
    EnBigpamet* bigpamet;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->timer--;
    if (this->timer == 0) {
        EnPametfrog_SetupLandOnSnapper(this);
    } else {
        bigpamet = (EnBigpamet*)this->actor.child;
        temp_f0 = 1.0f / this->timer;
        this->actor.world.pos.x -= (this->actor.world.pos.x - bigpamet->actor.world.pos.x) * temp_f0;
        this->actor.world.pos.z -= (this->actor.world.pos.z - bigpamet->actor.world.pos.z) * temp_f0;
        this->actor.world.pos.y =
            Math_SinS((-this->timer * 0x1000) + 0x6000) * 65.0f + ((EnBigpamet*)this->actor.child)->unk_2AC;
    }
}

void EnPametfrog_SetupLandOnSnapper(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06000994);
    this->actor.shape.rot.y = this->actor.child->shape.rot.y;
    this->actor.params = GEKKO_ON_SNAPPER;
    this->actionFunc = EnPametfrog_LandOnSnapper;
}

void EnPametfrog_LandOnSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        EnPametfrog_StopCutscene(this, globalCtx);
        EnPametfrog_SetupRearOnSnapper(this);
    }
}

void EnPametfrog_SetupFallInAir(EnPametfrog* this, GlobalContext* globalCtx) {
    s16 yaw;
    Vec3f subCamEye;
    f32 xzDist;

    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06001F20);
    if (this->actor.colChkInfo.health > 0) {
        this->actor.params = GEKKO_RETURN_TO_SNAPPER;
    }

    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->collider.base.acFlags &= ~AC_ON;
    this->timer = 10;
    if (this->actor.colChkInfo.health == 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_DEAD);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_DAMAGE);
    }

    func_800BCB70(&this->actor, 0x4000, 255, 0, 16);
    yaw = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    this->actor.world.pos.x += 30.0f * Math_SinS(yaw);
    this->actor.world.pos.z += 30.0f * Math_CosS(yaw);
    if (this->subCamId != SUBCAM_FREE) {
        xzDist = sqrtf(SQXZ(&this->unk_2DC));
        if (xzDist > 0.001f) {
            xzDist = 200.0f / xzDist;
        } else {
            xzDist = 200.0f;
            this->unk_2DC.x = 1.0f;
            this->unk_2DC.z = 0.0f;
        }

        subCamEye.x = this->actor.world.pos.x + (xzDist * this->unk_2DC.x);
        subCamEye.y = (this->actor.world.pos.y + this->actor.home.pos.y) * 0.5f;
        subCamEye.z = this->actor.world.pos.z + (xzDist * this->unk_2DC.z);
        Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.world.pos, &subCamEye);
    }

    this->actionFunc = EnPametfrog_FallInAir;
}

void EnPametfrog_FallInAir(EnPametfrog* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.colorFilterTimer = 0x10;
    if (this->timer > 0) {
        this->timer--;
        if (this->timer == 0) {
            this->actor.gravity = -1.0f;
            this->actor.colChkInfo.mass = 50;
        }
    } else {
        this->spinYaw += 0xF00;
        if (this->subCamId != SUBCAM_FREE) {
            Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.world.pos, &Play_GetCamera(globalCtx, this->subCamId)->eye);
        }

        if (this->actor.bgCheckFlags & 1) {
            EnPametfrog_SetupFallOnGround(this, globalCtx);
        }
    }
}

void EnPametfrog_SetupFallOnGround(EnPametfrog* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06004298);
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.y += this->spinYaw;
    this->actor.shape.rot.z = 0;
    this->spinYaw = 0;
    this->timer = 5;
    EnPametfrog_ChangeColliderThaw(this, globalCtx);
    EnPametfrog_JumpWaterEffects(this, globalCtx);
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_WALK_WATER);
    this->actionFunc = EnPametfrog_FallOnGround;
}

void EnPametfrog_FallOnGround(EnPametfrog* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        if (this->skelAnime.animCurrentSeg == &D_06004298) {
            if (this->actor.colChkInfo.health == 0) {
                this->timer--;
                if (this->timer == 0) {
                    EnPametfrog_SetupDefeatGekko(this, globalCtx);
                }
            } else {
                SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060030E4);
            }
        } else {
            EnPametfrog_SetupRunToSnapper(this);
        }
    }
}

void EnPametfrog_SetupDefeatGekko(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f subCamEye;
    s16 yaw = Actor_YawToPoint(this->actor.child, &this->actor.home.pos);
    s16 yawDiff = this->actor.yawTowardsPlayer - yaw;

    yaw = yawDiff > 0 ? yaw - 0x2000 : yaw + 0x2000;
    subCamEye.x = this->actor.child->focus.pos.x + 150.0f * Math_SinS(yaw);
    subCamEye.y = this->actor.child->focus.pos.y + 20.0f;
    subCamEye.z = this->actor.child->focus.pos.z + 150.0f * Math_CosS(yaw);
    Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.child->focus.pos, &subCamEye);
    this->actor.params = GEKKO_DEFEAT;
    this->timer = 38;
    this->actionFunc = EnPametfrog_DefeatGekko;
}

void EnPametfrog_DefeatGekko(EnPametfrog* this, GlobalContext* globalCtx) {
    this->actor.colorFilterTimer = 16;
    if (this->timer > 0) {
        this->timer--;
        if (this->timer == 0) {
            EnPametfrog_SetupDefeatSnapper(this, globalCtx);
        }
    }
}

void EnPametfrog_SetupDefeatSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f subCamEye;
    s16 yaw = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    s16 yawDiff = this->actor.yawTowardsPlayer - yaw;

    yaw = yawDiff > 0 ? yaw - 0x2000 : yaw + 0x2000;
    subCamEye.x = this->actor.world.pos.x + Math_SinS(yaw) * 150.0f;
    subCamEye.y = this->actor.world.pos.y + 20.0f;
    subCamEye.z = this->actor.world.pos.z + Math_CosS(yaw) * 150.0f;
    Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.world.pos, &subCamEye);
    this->timer = 20;
    this->actionFunc = EnPametfrog_DefeatSnapper;
}

void EnPametfrog_DefeatSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    this->timer--;
    Actor_SetScale(&this->actor, this->timer * 0.00035000002f);
    this->actor.colorFilterTimer = 16;
    EnPametfrog_ShakeCamera(this, globalCtx, (this->timer * 3.75f) + 75.0f, (this->timer * 0.5f) + 10.0f);
    if (this->timer == 0) {
        EnPametfrog_SetupSpawnFrog(this, globalCtx);
    }
}

void EnPametfrog_SetupSpawnFrog(EnPametfrog* this, GlobalContext* globalCtx) {
    static Vec3f sAccel = { 0.0f, -0.5f, 0.0f };
    static Color_RGBA8 primColor = { 250, 250, 250, 255 };
    static Color_RGBA8 envColor = { 180, 180, 180, 255 };
    s16 yaw = BINANG_ROT180(Camera_GetCamDirYaw(ACTIVE_CAM));
    Vec3f vec1;
    Vec3f vel;
    s32 i;

    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_MINIFROG, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, yaw, 0, this->params);
    vec1.x = (Math_SinS(yaw) * 20.0f) + this->actor.world.pos.x;
    vec1.y = this->actor.world.pos.y + 25.0f;
    vec1.z = (Math_CosS(yaw) * 20.0f) + this->actor.world.pos.z;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    func_800B0DE0(globalCtx, &vec1, &D_801D15B0, &D_801D15B0, &primColor, &envColor, 800, 50);
    func_800F0568(globalCtx, &this->actor.world.pos, 40, NA_SE_EN_NPC_APPEAR);
    Actor_SetRoomClearedTemp(globalCtx, globalCtx->roomCtx.currRoom.num);

    for (i = 0; i < 25; i++) {
        vel.x = randPlusMinusPoint5Scaled(5.0f);
        vel.y = Rand_ZeroFloat(3.0f) + 4.0f;
        vel.z = randPlusMinusPoint5Scaled(5.0f);
        EffectSsHahen_Spawn(globalCtx, &this->actor.world.pos, &vel, &sAccel, 0, Rand_S16Offset(12, 3),
                            HAHEN_OBJECT_DEFAULT, 10, 0);
    }

    this->timer = 40;
    this->actionFunc = EnPametfrog_SpawnFrog;
}

void EnPametfrog_SpawnFrog(EnPametfrog* this, GlobalContext* globalCtx) {
    f32 magShake;

    this->timer--;
    magShake = (sin_rad(this->timer * (M_PI / 5)) * ((0.04f * (this->timer * 0.1f)) + 0.02f)) + 1.0f;
    EnPametfrog_ShakeCamera(this, globalCtx, 75.0f * magShake, 10.0f * magShake);
    if (this->timer == 0) {
        EnPametfrog_StopCutscene(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnPametfrog_SetupCutscene(EnPametfrog* this) {
    if (this->actor.colChkInfo.health == 0) {
        this->cutscene = this->actor.cutscene;
    } else {
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
    }

    ActorCutscene_SetIntentToPlay(this->cutscene);
    this->actionFunc = EnPametfrog_PlayCutscene;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
}

void EnPametfrog_PlayCutscene(EnPametfrog* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        this->subCamId = ActorCutscene_GetCurrentCamera(this->cutscene);
        func_800B724C(globalCtx, &this->actor, 7);
        if (this->actor.colChkInfo.health == 0) {
            if (this->actor.params == GEKKO_PRE_SNAPPER) {
                EnPametfrog_SetupCallSnapper(this, globalCtx);
            } else {
                EnPametfrog_SetupFallInAir(this, globalCtx);
            }
        } else {
            EnPametfrog_SetupFallOffSnapper(this, globalCtx);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void EnPametfrog_SetupLookAround(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060066B4);
    this->collider.base.atFlags &= ~AT_ON;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnPametfrog_LookAround;
}

void EnPametfrog_LookAround(EnPametfrog* this, GlobalContext* globalCtx) {
    EnPametfrog_IdleWaterEffects(this, globalCtx);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 5, 0x400, 0x80);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) && (func_801690CC(globalCtx) == 0)) {
        if (!this->unk_2AE) {
            func_801A2E54(0x38);
            this->unk_2AE = true;
        }
        EnPametfrog_SetupJumpToLink(this);
    }
}

void EnPametfrog_SetupJumpToLink(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_060039C4);
    this->collider.base.acFlags |= AC_ON;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnPametfrog_JumpToLink;
}

void EnPametfrog_JumpToLink(EnPametfrog* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x80);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    EnPametfrog_JumpOnGround(this, globalCtx);
    if (!(this->actor.bgCheckFlags & 1) ||
        (this->skelAnime.animCurrentFrame > 1.0f && this->skelAnime.animCurrentFrame < 12.0f)) {
        this->actor.speedXZ = 8.0f;
    } else {
        this->actor.speedXZ = 0.0f;
    }

    if ((this->collider.base.ocFlags1 & OC1_HIT) && (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) &&
        Actor_IsActorFacingLink(&this->actor, 0x3000) &&
        (this->skelAnime.animCurrentFrame <= 2.0f || this->skelAnime.animCurrentFrame >= 11.0f)) {
        EnPametfrog_SetupMeleeAttack(this);
    }
}

void EnPametfrog_SetupMeleeAttack(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600F990);
    this->timer = 7;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = EnPametfrog_MeleeAttack;
}

static AnimationHeader* sAttackAnimations[] = {
    &D_0600347C, // Jab Punch
    &D_060070C4, // Hook Punch
    &D_06003F28, // Kick
    &D_0600F048, // Windup Punch
};

void EnPametfrog_MeleeAttack(EnPametfrog* this, GlobalContext* globalCtx) {
    EnPametfrog_IdleWaterEffects(this, globalCtx);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        this->timer--;
        if (this->timer == 0) {
            EnPametfrog_SetupLookAround(this);
        } else if (this->timer == 6) {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600F990);
        } else {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, sAttackAnimations[(s32)Rand_ZeroFloat(4.0f) % 4]);
        }
    }

    if ((this->skelAnime.animCurrentSeg == &D_0600347C && func_801378B8(&this->skelAnime, 2.0f)) ||
        (this->skelAnime.animCurrentSeg == &D_060070C4 && func_801378B8(&this->skelAnime, 9.0f)) ||
        (this->skelAnime.animCurrentSeg == &D_06003F28 && func_801378B8(&this->skelAnime, 2.0f)) ||
        ((this->skelAnime.animCurrentSeg == &D_0600F048) && func_801378B8(&this->skelAnime, 27.0f))) {
        this->collider.base.atFlags |= AT_ON;
        if (this->skelAnime.animCurrentSeg == &D_06003F28) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_KICK);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_PUNCH1);
        }
    } else {
        this->collider.base.atFlags &= ~AT_ON;
    }
}

void EnPametfrog_SetupDamage(EnPametfrog* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06005D54, -3.0f);
    this->timer = 20;
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->actor.speedXZ = 10.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_DAMAGE);
    func_800BCB70(&this->actor, 0x4000, 255, 0, 20);
    func_800BE5CC(&this->actor, &this->collider, 0);
    this->actor.shape.rot.y = BINANG_ROT180(this->actor.world.rot.y);
    this->actionFunc = EnPametfrog_Damage;
}

void EnPametfrog_Damage(EnPametfrog* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->timer--;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (this->timer == 0) {
        if (this->actor.colChkInfo.health > 0) {
            EnPametfrog_SetupJumpToLink(this);
        } else {
            EnPametfrog_SetupCutscene(this);
        }
    }
}

void EnPametfrog_SetupStun(EnPametfrog* this) {
    if (this->skelAnime.animCurrentSeg == &D_060039C4) {
        this->skelAnime.animCurrentFrame = 0.0f;
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }

    this->collider.base.atFlags &= ~AT_ON;
    this->actor.speedXZ = 0.0f;

    if (this->actor.colChkInfo.health == 0) {
        this->collider.base.acFlags &= ~AC_ON;
    }

    this->actionFunc = EnPametfrog_Stun;
}

void EnPametfrog_Stun(EnPametfrog* this, GlobalContext* globalCtx) {
    this->freezeTimer--;
    if (this->freezeTimer == 0) {
        EnPametfrog_ChangeColliderThaw(this, globalCtx);
        EnPametfrog_SetupJumpToLink(this);
    } else if (this->freezeTimer == 78) {
        EnPametfrog_ChangeColliderThaw(this, globalCtx);
        this->actor.colorFilterTimer = 0;
        EnPametfrog_SetupCutscene(this);
    }
}

void EnPametfrog_SetupCallSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f subCamEye;
    Vec3f subCamAt;
    s16 yawDiff;

    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06001B08, 3.0f);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FROG_GREET);
    this->actor.flags &= ~1;
    this->actor.colChkInfo.health = 6;
    this->actor.world.rot.y = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    if (yawDiff > 0) {
        this->actor.world.rot.y -= 0x2000;
    } else {
        this->actor.world.rot.y += 0x2000;
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;
    subCamAt.x = this->actor.world.pos.x;
    subCamAt.z = this->actor.world.pos.z;
    subCamAt.y = this->actor.world.pos.y + 45.0f;
    subCamEye.x = (Math_SinS(this->actor.shape.rot.y) * 90.0f) + subCamAt.x;
    subCamEye.z = (Math_CosS(this->actor.shape.rot.y) * 90.0f) + subCamAt.z;
    subCamEye.y = subCamAt.y + 4.0f;

    // Zooms in on Gekko
    Play_CameraSetAtEye(globalCtx, this->subCamId, &subCamAt, &subCamEye);
    this->timer = 0;
    this->actor.hintId = 0x5F;
    this->actionFunc = EnPametfrog_CallSnapper;
}

void EnPametfrog_CallSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        EnPametfrog_SetupSnapperSpawn(this, globalCtx);
    }
}

void EnPametfrog_SetupSnapperSpawn(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f subCamAt;
    Vec3f subCamEye;
    s16 yaw;

    EnPametfrog_PlaceSnapper(this, globalCtx);
    subCamAt.x = this->actor.child->world.pos.x;
    subCamAt.z = this->actor.child->world.pos.z;
    subCamAt.y = this->actor.child->floorHeight + 50.0f;
    if ((s16)(Actor_YawToPoint(&this->actor, &this->actor.home.pos) - this->actor.shape.rot.y) > 0) {
        yaw = this->actor.child->shape.rot.y - 0x1000;
    } else {
        yaw = this->actor.child->shape.rot.y + 0x1000;
    }

    subCamEye.x = (Math_SinS(yaw) * 500.0f) + subCamAt.x;
    subCamEye.y = subCamAt.y + 55.0f;
    subCamEye.z = (Math_CosS(yaw) * 500.0f) + subCamAt.z;

    // Zooms in on Snapper spawn point
    Play_CameraSetAtEye(globalCtx, this->subCamId, &subCamAt, &subCamEye);
    this->quake = Quake_Add(ACTIVE_CAM, 6);
    Quake_SetSpeed(this->quake, 18000);
    Quake_SetQuakeValues(this->quake, 2, 0, 0, 0);
    Quake_SetCountdown(this->quake, 15);
    func_8013ECE0(this->actor.xyzDistToPlayerSq, 120, 20, 10);
    this->timer = 40;
    this->actionFunc = EnPametfrog_SnapperSpawn;
}

void EnPametfrog_SnapperSpawn(EnPametfrog* this, GlobalContext* globalCtx) {
    this->timer--;
    EnPametfrog_ShakeCamera(this, globalCtx, (f32)(this->timer * 7.5f) + 200.0f,
                            ((f32)(this->timer * 2) * (15.0f / 16.0f)) + -20.0f);
    if (this->timer != 0) {
        func_8013ECE0(this->actor.xyzDistToPlayerSq, 120, 20, 10);
    } else {
        EnPametfrog_SetupTransitionGekkoSnapper(this, globalCtx);
    }
}

void EnPametfrog_SetupTransitionGekkoSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    this->actor.params = GEKKO_GET_SNAPPER;
    Quake_RemoveFromIdx(this->quake);
    this->quake = Quake_Add(ACTIVE_CAM, 3);
    Quake_SetSpeed(this->quake, 20000);
    Quake_SetQuakeValues(this->quake, 17, 0, 0, 0);
    Quake_SetCountdown(this->quake, 12);
    func_8013ECE0(this->actor.xyzDistToPlayerSq, 255, 20, 150);
    this->actionFunc = EnPametfrog_TransitionGekkoSnapper;
}

void EnPametfrog_TransitionGekkoSnapper(EnPametfrog* this, GlobalContext* globalCtx) {
    if (this->actor.params == GEKKO_INIT_SNAPPER) {
        func_801A2E54(0x38);
        EnPametfrog_SetupRunToSnapper(this);
    }
}

void EnPametfrog_ApplyDamageEffect(EnPametfrog* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        if ((this->drawEffect != GEKKO_DRAW_EFFECT_FROZEN) ||
            !(this->collider.elements->info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            if (this->actor.params == GEKKO_PRE_SNAPPER) {
                if (func_800BE22C(&this->actor) == 0) {
                    func_801A2ED8();
                }

                if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_ZORA_BARRIER) {
                    EnPametfrog_ApplyElectricStun(this);
                    EnPametfrog_SetupStun(this);
                } else if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_STUN) {
                    EnPametfrog_ApplyStun(this);
                    EnPametfrog_SetupStun(this);
                } else if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_ICE) {
                    EnPametfrog_ChangeColliderFreeze(this);
                    this->freezeTimer = 80;
                    func_800BCB70(&this->actor, 0x4000, 0xFF, 0, 0x50);
                    EnPametfrog_SetupStun(this);
                } else {
                    EnPametfrog_ChangeColliderThaw(this, globalCtx);
                    if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_FIRE) {
                        this->drawEffect = GEKKO_DRAW_EFFECT_NONE;
                        this->unk_2C8 = 0.75f;
                        this->unk_2C4 = 4.0f;
                    } else if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_LIGHT) {
                        this->drawEffect = GEKKO_DRAW_EFFECT_LIGHT_ORBS;
                        this->unk_2C8 = 0.75f;
                        this->unk_2C4 = 4.0f;
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                                    this->collider.elements[0].info.bumper.hitPos.x,
                                    this->collider.elements[0].info.bumper.hitPos.y,
                                    this->collider.elements[0].info.bumper.hitPos.z, 0, 0, 0,
                                    CLEAR_TAG_LARGE_LIGHT_RAYS);
                    }
                    EnPametfrog_SetupDamage(this);
                }
            } else if (func_800BE22C(&this->actor) == 0) {
                this->collider.base.acFlags &= ~AC_ON;
                EnPametfrog_ApplyMagicArrowEffects(this, globalCtx);
                func_800BBA88(globalCtx, &this->actor);
                this->actor.flags &= ~1;
                func_801A2ED8();
                EnPametfrog_SetupCutscene(this);
            } else if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_ZORA_BARRIER) {
                EnPametfrog_ApplyElectricStun(this);
            } else if (this->actor.colChkInfo.damageEffect == GEKKO_DMGEFF_STUN) {
                EnPametfrog_ApplyStun(this);
            } else {
                EnPametfrog_ApplyMagicArrowEffects(this, globalCtx);
                EnPametfrog_SetupFallInAir(this, globalCtx);
            }
        }
    }
}

void EnPametfrog_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnPametfrog* this = THIS;
    f32 unk2C4;
    f32 arg3;

    if (this->actor.params == GEKKO_CUTSCENE) {
        EnPametfrog_SetupCutscene(this);
    } else if (this->actionFunc != EnPametfrog_PlayCutscene) {
        EnPametfrog_ApplyDamageEffect(this, globalCtx);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    this->actionFunc(this, globalCtx);
    if ((this->actionFunc != EnPametfrog_JumpOnSnapper) && (this->actionFunc != EnPametfrog_RearOnSnapperRise)) {
        if (this->actor.gravity < -0.1f) {
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            arg3 = this->actionFunc == EnPametfrog_FallInAir ? 3.0f : 15.0f;
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 25.0f, arg3, 3.0f, 0x1F);
        } else if (this->freezeTimer == 0) {
            Actor_SetVelocityAndMoveXYRotation(&this->actor);
            this->actor.floorHeight = this->actor.world.pos.y;
        }
    }

    if (this->collider.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->collider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->collider.base.ocFlags1 & OC1_ON) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->unk_2C4 > 0.0f) {
        if ((this->drawEffect != GEKKO_DRAW_EFFECT_FROZEN) && (this->actionFunc != EnPametfrog_PlayCutscene)) {
            Math_StepToF(&this->unk_2C4, 0.0f, 0.05f);
            unk2C4 = ((this->unk_2C4 + 1.0f) * 0.375f);
            this->unk_2C8 = unk2C4;
            this->unk_2C8 = unk2C4 > 0.75f ? 0.75f : this->unk_2C8;
        } else if (!Math_StepToF(&this->unk_2CC, 0.75f, (3.0f / 160.0f))) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

/* index -1: Limb Not used
 * index 0:  GEKKO_LIMB_WAIST
 * index 1:  GEKKO_LIMB_L_SHIN
 * index 2:  GEKKO_LIMB_L_FOOT
 * index 3:  GEKKO_LIMB_R_SHIN
 * index 4:  GEKKO_LIMB_R_FOOT
 * index 5:  GEKKO_LIMB_L_UPPER_ARM
 * index 6:  GEKKO_LIMB_L_FOREARM
 * index 7:  GEKKO_LIMB_L_HAND
 * index 8:  GEKKO_LIMB_R_UPPER_ARM
 * index 9:  GEKKO_LIMB_R_FOREARM
 * index 10: GEKKO_LIMB_R_HAND
 * index 11: GEKKO_LIMB_JAW
 */
static s8 limbPosIndex[] = {
    -1, -1, 0, -1, 1, -1, 2, -1, 3, -1, 4, -1, 5, 6, -1, 7, 8, 9, -1, 10, -1, 11, -1, -1,
};

void EnPametfrog_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnPametfrog* this = THIS;
    Vec3f vec;
    Vec3s* center;
    s8 index;

    if (limbIndex == GEKKO_LIMB_HEAD) {
        SysMatrix_GetStateTranslation(&this->actor.focus.pos);
        this->actor.focus.rot.y = this->actor.shape.rot.y;
        SysMatrix_GetStateTranslationAndScaledY(2500.0f, &vec);
        center = &this->collider.elements[0].dim.worldSphere.center;
        center->x = vec.x;
        center->y = vec.y;
        center->z = vec.z;
        center = &this->collider.elements[1].dim.worldSphere.center;
        center->x = (Math_SinS(this->actor.shape.rot.y) * 35.0f) + this->actor.focus.pos.x;
        center->y = this->actor.focus.pos.y - 10.0f;
        center->z = (Math_CosS(this->actor.shape.rot.y) * 35.0f) + this->actor.focus.pos.z;
    }

    index = limbPosIndex[limbIndex];
    if (index != -1) {
        SysMatrix_GetStateTranslation(&this->limbPos[index]);
    }
}

void EnPametfrog_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPametfrog* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    Matrix_RotateY(this->spinYaw, MTXMODE_APPLY);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     EnPametfrog_PostLimbDraw, &this->actor);
    func_800BE680(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->unk_2C8, this->unk_2CC,
                  this->unk_2C4, this->drawEffect);
}
