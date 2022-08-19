/*
 * File: z_boss_07.c
 * Overlay: ovl_Boss_07
 * Description: Majora
 */

#include "z_boss_07.h"
#include "overlays/actors/ovl_Obj_Tsubo/z_obj_tsubo.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss07*)thisx)

#define FACING_ANGLE(actor1, actor2) ((s16)((actor1)->shape.rot.y - (actor2)->shape.rot.y + 0x8000))

#define EFFECT_COUNT 50

typedef enum {
    /* 0 */ REMAINS_ODOLWA,
    /* 1 */ REMAINS_GYORG,
    /* 2 */ REMAINS_GOHT,
    /* 3 */ REMAINS_TWINMOLD,
    /* 4 */ REMAINS_COUNT
} RemainsIndex;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x02 */ s16 scroll;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f vel;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ UNK_TYPE1 unk28[4];
    /* 0x2C */ s16 alpha;
    /* 0x2E */ UNK_TYPE1 unk2E[2];
    /* 0x30 */ s16 isFading;
    /* 0x32 */ UNK_TYPE1 unk32[2];
    /* 0x34 */ f32 scale;
    /* 0x38 */ UNK_TYPE1 unk38[0x10];
} Boss07Effect; // size = 0x48

typedef enum {
    /* 0 */ MAJORA_EFFECT_NONE,
    /* 1 */ MAJORA_EFFECT_FLAME
} Boss07EffectType;

typedef enum {
   MAJORAS_WRATH_ATTACK_0,
   MAJORAS_WRATH_ATTACK_1,
   MAJORAS_WRATH_ATTACK_2,
   MAJORAS_WRATH_ATTACK_3,
   MAJORAS_WRATH_ATTACK_4,
   MAJORAS_WRATH_ATTACK_5,
   MAJORAS_WRATH_ATTACK_6,
   MAJORAS_WRATH_ATTACK_7,
   MAJORAS_WRATH_ATTACK_MAX,
} Boss07WrathActionStates;

typedef enum {
    MAJORAS_INCARNATION_STATE_0,
    MAJORAS_INCARNATION_STATE_1,
    MAJORAS_INCARNATION_STATE_2,
    MAJORAS_INCARNATION_STATE_MAX,
} Boss07IncarnationActionStates;

typedef enum {
    MAJORAS_MASK_SPIN_STATE_0,
    MAJORAS_MASK_SPIN_STATE_1,
    MAJORAS_MASK_SPIN_STATE_2,
    MAJORAS_MASK_SPIN_STATE_MAX,
} Boss07MaskSpinStates;

typedef enum {
    MAJORAS_MASK_BEAM_STATE_0,
    MAJORAS_MASK_BEAM_STATE_1,
    MAJORAS_MASK_BEAM_STATE_2,
    MAJORAS_MASK_BEAM_STATE_3,
    MAJORAS_MASK_BEAM_STATE_4,
    MAJORAS_MASK_BEAM_STATE_5,
    MAJORAS_MASK_BEAM_STATE_MAX,
} Boss07MaskBeamStates;

typedef enum {
    MAJORAS_PROJECTILE_STATE_0,
    MAJORAS_PROJECTILE_STATE_1,
    MAJORAS_PROJECTILE_STATE_MAX,
} Boss07ProjectileStates;

typedef enum {
    MAJORAS_REMAINS_STATE_0,
    MAJORAS_REMAINS_STATE_1,
    MAJORAS_REMAINS_STATE_2,
    MAJORAS_REMAINS_STATE_3,
    MAJORAS_REMAINS_STATE_10=10,
    MAJORAS_REMAINS_STATE_20=20,
} Boss07RemainsStates;

typedef enum {
    MAJORAS_TOP_STATE_0,
    MAJORAS_TOP_STATE_1,
    MAJORAS_TOP_STATE_MAX,
} Boss07TopState;

#if 1 // function prototypes
void Boss07_RandVec3fXZ(Vec3f* arg0, f32 arg1);
void Boss07_Incarnation_AvoidPlayer(Boss07* this);
void Boss07_Mask_ClearBeam(Boss07* this);

void Boss07_Init(Actor* thisx, PlayState* play);
void Boss07_Destroy(Actor* thisx, PlayState* play);

void Boss07_Wrath_Update(Actor* thisx, PlayState* play);
void Boss07_Static_Update(Actor* thisx, PlayState* play);
void Boss07_Remains_Update(Actor* thisx, PlayState* play);
void Boss07_Top_Update(Actor* thisx, PlayState* play);
void Boss07_Projectile_Update(Actor* thisx, PlayState* play);
void Boss07_Mask_Update(Actor* thisx, PlayState* play);
void Boss07_Incarnation_Update(Actor* thisx, PlayState* play);
void Boss07_Afterimage_Update(Actor* thisx, PlayState* play);

void Boss07_Wrath_Draw(Actor* thisx, PlayState* play);
void Boss07_Static_Draw(Actor* thisx, PlayState* play);
void Boss07_Remains_Draw(Actor* thisx, PlayState* play);
void Boss07_Top_Draw(Actor* thisx, PlayState* play);
void Boss07_Projectile_Draw(Actor* thisx, PlayState* play);
void Boss07_Mask_Draw(Actor* thisx, PlayState* play);
void Boss07_Incarnation_Draw(Actor* thisx, PlayState* play);
void Boss07_Afterimage_Draw(Actor* thisx, PlayState* play);

void Boss07_Wrath_SetupIntro(Boss07* this, PlayState* play);
void Boss07_Wrath_Intro(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupDeath(Boss07* this, PlayState* play);
void Boss07_Wrath_Death(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupSpawnTop(Boss07* this, PlayState* play);
void Boss07_Wrath_SpawnTop(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupStunned(Boss07* this, PlayState* play);
void Boss07_Wrath_Stunned(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupDamaged(Boss07* this, PlayState* play, u8 damage, u8 effect);
void Boss07_Wrath_Damaged(Boss07* this, PlayState* play);

void Boss07_Wrath_ThrowPlayer(Boss07* this, PlayState* play);
void Boss07_Wrath_Dodge(Boss07* this, PlayState* play, u8 arg2);
void Boss07_Wrath_SetupSidestep(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupShock(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupGrab(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupAttack(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupIdle(Boss07* this, PlayState* play, s16 delay);
void Boss07_Wrath_SetupJump(Boss07* this, PlayState* play);
void Boss07_Wrath_SetupFlip(Boss07* this, PlayState* play);
void Boss07_Wrath_Idle(Boss07* this, PlayState* play);
void Boss07_Wrath_StartJump(Boss07* this, PlayState* play);
void Boss07_Wrath_Jump(Boss07* this, PlayState* play);
void Boss07_Wrath_Flip(Boss07* this, PlayState* play);
void Boss07_Wrath_Sidestep(Boss07* this, PlayState* play);
void Boss07_Wrath_Attack(Boss07* this, PlayState* play);
void Boss07_Wrath_Grab(Boss07* this, PlayState* play);
void Boss07_Wrath_GrabPlayer(Boss07* this, PlayState* play);
void Boss07_Wrath_Shock(Boss07* this, PlayState* play);
void Boss07_Wrath_ShockStun(Boss07* this, PlayState* play);

void Boss07_Wrath_MakeShadowTex(u8* shadowTex, Boss07* this, PlayState* play);
void Boss07_Wrath_DrawShadowTex(u8* shadowTex, Boss07* this, PlayState* play);
void Boss07_Wrath_MakeShadowCircles(Boss07* this, u8* shadowTex, f32 weight);

void Boss07_Mask_SetupIdle(Boss07* this, PlayState* play);
void Boss07_Mask_Idle(Boss07* this, PlayState* play);
void Boss07_Mask_SetupSpin(Boss07* this, PlayState* play);
void Boss07_Mask_Spin(Boss07* this, PlayState* play);
void Boss07_Mask_SetupBeam(Boss07* this, PlayState* play);
void Boss07_Mask_Beam(Boss07* this, PlayState* play);
void Boss07_Mask_SetupStunned(Boss07* this, PlayState* play);
void Boss07_Mask_Stunned(Boss07* this, PlayState* play);
void Boss07_Mask_SetupDamaged(Boss07* this, PlayState* play, u8 arg2, Actor* hitActor);
void Boss07_Mask_Damaged(Boss07* this, PlayState* play);
void Boss07_Mask_SetupIntro(Boss07* this, PlayState* play);
void Boss07_Mask_Intro(Boss07* this, PlayState* play);
void Boss07_Mask_SetupDeath(Boss07* this, PlayState* play);
void Boss07_Mask_Death(Boss07* this, PlayState* play);

void Boss07_Incarnation_SetupAttack(Boss07* this, PlayState* play);
void Boss07_Incarnation_SetupHopak(Boss07* this, PlayState* play);
void Boss07_Incarnation_SetupMoonwalk(Boss07* this, PlayState* play);
void Boss07_Incarnation_SetupPirouette(Boss07* this, PlayState* play);
void Boss07_Incarnation_Taunt(Boss07* this, PlayState* play);
void Boss07_Incarnation_Stunned(Boss07* this, PlayState* play);
void Boss07_Incarnation_Damaged(Boss07* this, PlayState* play);
void Boss07_Incarnation_Run(Boss07* this, PlayState* play);
void Boss07_Incarnation_Attack(Boss07* this, PlayState* play);
void Boss07_Incarnation_Hopak(Boss07* this, PlayState* play);
void Boss07_Incarnation_Moonwalk(Boss07* this, PlayState* play);
void Boss07_Incarnation_Pirouette(Boss07* this, PlayState* play);
void Boss07_Incarnation_Death(Boss07* this, PlayState* play);
void Boss07_Incarnation_SetupDamaged(Boss07* this, PlayState* play, u8 arg2, u8 arg3);
void Boss07_Incarnation_SetupStunned(Boss07* this, PlayState* play, s16 arg2);
void Boss07_Incarnation_SetupDeath(Boss07* this, PlayState* play);
void Boss07_Incarnation_SetupRun(Boss07* this, PlayState* play);
void Boss07_Incarnation_SetupTaunt(Boss07* this, PlayState* play);
void Boss07_Incarnation_SetupIntro(Boss07* this, PlayState* play);
void Boss07_Incarnation_Intro(Boss07* this, PlayState* play);

void Boss07_Remains_SetupIntro(Boss07* this, PlayState* play);
void Boss07_Remains_Intro(Boss07* this, PlayState* play);
void Boss07_Remains_SetupFly(Boss07* this, PlayState* play);
void Boss07_Remains_Fly(Boss07* this, PlayState* play);
void Boss07_Remains_SetupStunned(Boss07* this, PlayState* play);
void Boss07_Remains_Stunned(Boss07* this, PlayState* play);

void Boss07_Top_Thrown(Boss07* this, PlayState* play);
void Boss07_Top_Ground(Boss07* this, PlayState* play);
void Boss07_Top_SetupThrown(Boss07* this, PlayState* play);
void Boss07_Top_SetupGround(Boss07* this, PlayState* play);

void Boss07_Static_UpdateEffects(PlayState* play);
void Boss07_Static_DrawEffects(PlayState* play);
#endif

static s16 sColorsYRGB[4][3] = {
    { 255, 255, 100 }, // light yellow
    { 255, 100, 100 }, // light red
    { 100, 255, 100 }, // light green
    { 100, 100, 255 }, // light blue
};

static s16 sColorsWhite[4][3] = {
    { 255, 255, 255 }, // white
    { 255, 255, 255 }, // white
    { 255, 255, 255 }, // white
    { 255, 255, 255 }, // white
};

#include "z_boss_07_dmgtbl.c"

const ActorInit Boss_07_InitVars = {
    ACTOR_BOSS_07,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS07,
    sizeof(Boss07),
    (ActorFunc)Boss07_Init,
    (ActorFunc)Boss07_Destroy,
    (ActorFunc)Boss07_Wrath_Update,
    (ActorFunc)Boss07_Wrath_Draw,
};

#include "z_boss_07_colchk.c"

static Vec3f sSfxPoint;
static u8 sHeartbeatTimer;
static s32 sWhipSegCount;
static Boss07* sMajorasWrath;
static Boss07* sMajoraStatic;
static Boss07* sMajorasMask;
static Boss07* sBossRemains[REMAINS_COUNT];
static u8 sKillProjectiles;
static u8 sMusicStartTimer;
static Boss07Effect sEffects[EFFECT_COUNT];
static s32 sSeed0;
static s32 sSeed1;
static s32 sSeed2;

void Boss07_Remains_DamageSfx(Boss07* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FOLLOWERS_DAMAGE);
}

void Boss07_InitRand(s32 seedInit0, s32 seedInit1, s32 seedInit2) {
    sSeed0 = seedInit0;
    sSeed1 = seedInit1;
    sSeed2 = seedInit2;
}

f32 Boss07_RandZeroOne(void) {
    // Wichmann-Hill algorithm
    f32 randFloat;

    sSeed0 = (sSeed0 * 171) % 30269;
    sSeed1 = (sSeed1 * 172) % 30307;
    sSeed2 = (sSeed2 * 170) % 30323;

    randFloat = (sSeed0 / 30269.0f) + (sSeed1 / 30307.0f) + (sSeed2 / 30323.0f);
    while (randFloat >= 1.0f) {
        randFloat -= 1.0f;
    }
    return fabsf(randFloat);
}

void Boss07_SpawnEffect(PlayState* play, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 arg4) {
    s32 i;
    Boss07Effect* effect = (Boss07Effect*)play->specialEffects;

    for (i = 0; i < ARRAY_COUNT(sEffects); i++, effect++) {
        if (effect->type == MAJORA_EFFECT_NONE) {
            effect->type = MAJORA_EFFECT_FLAME;
            effect->pos = *pos;
            effect->vel = *vel;
            effect->accel = *accel;
            effect->scale = arg4 / 1000.0f;
            effect->isFading = 0;
            effect->alpha = 0;
            effect->scroll = Rand_ZeroFloat(1000.0f);
            break;
        }
    }
}

void Boss07_UpdateSpheres(s32 index, ColliderJntSph* collider, Vec3f* pos) {
    collider->elements[index].dim.worldSphere.center.x = pos->x;
    collider->elements[index].dim.worldSphere.center.y = pos->y;
    collider->elements[index].dim.worldSphere.center.z = pos->z;
    collider->elements[index].dim.worldSphere.radius =
        collider->elements[index].dim.modelSphere.radius * collider->elements[index].dim.scale;
}

s32 Boss07_IsFacingPlayer(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y)) < 0x3000) &&
        (ABS_ALT((s16)(this->actor.yawTowardsPlayer - (s16)(player->actor.shape.rot.y + 0x8000))) < 0x3000)) {
        return true;
    }
    return false;
}

void Boss07_SmoothStop(Boss07* this, f32 maxStep) {
    Math_ApproachZeroF(&this->actor.speedXZ, 1.0f, maxStep);
    if (this->actor.bgCheckFlags & 0x18) {
        this->actor.speedXZ = 0.0f;
    }
}

void Boss07_RandVec3fXZ(Vec3f* dst, f32 length) {
    Matrix_RotateYF(Rand_ZeroFloat(2 * M_PI), MTXMODE_NEW);
    Matrix_MultVecZ(length, dst);
}

void Boss07_SpawnDust(Boss07* this, PlayState* play, u8 spawnInterval, u8 mode) {
    static Color_RGBA8 sDarkOrange = { 60, 50, 20, 255 };
    static Color_RGBA8 sDarkRed = { 40, 30, 30, 255 };
    u8 i;

    if (!(this->actionTimer & spawnInterval) && ((spawnInterval == 0) || (this->actor.speedXZ > 1.0f))) {
        for (i = 0; i < 2; i++) {
            Vec3f pos;
            Vec3f vel;
            Vec3f accel;

            vel.x = randPlusMinusPoint5Scaled(5.0f);
            vel.y = Rand_ZeroFloat(2.0f) + 1.0f;
            vel.z = randPlusMinusPoint5Scaled(5.0f);
            accel.x = accel.z = 0.0f;
            accel.y = -0.1f;
            pos.y = Rand_ZeroFloat(10.0f) + 3.0f;
            if (mode) {
                pos.x = this->actor.focus.pos.x + randPlusMinusPoint5Scaled(150.0f);
                pos.z = this->actor.focus.pos.z + randPlusMinusPoint5Scaled(150.0f);
            } else {
                pos.z = this->unk_1788[i].z + randPlusMinusPoint5Scaled(20.0f);
                pos.x = this->unk_1788[i].x + randPlusMinusPoint5Scaled(20.0f);
            }
            func_800B0EB0(play, &pos, &vel, &accel, &sDarkOrange, &sDarkRed, Rand_ZeroFloat(150.0f) + 350.0f, 10,
                          Rand_ZeroFloat(5.0f) + 14.0f);
        }
    }
}

void Boss07_MovePlayer(PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (SQXZ(player->actor.world.pos) < SQ(80.0f)) {
        player->actor.world.pos.z = 90.0f;
    }
}

void Boss07_SpawnDustAtPos(PlayState* play, Vec3f* spawnPos, u8 count) {
    static Color_RGBA8 sDarkOrange = { 60, 50, 20, 255 };
    static Color_RGBA8 sDarkRed = { 40, 30, 30, 255 };
    u8 i;

    for (i = 0; i < count; i++) {
        Vec3f pos;
        Vec3f vel;
        Vec3f accel;

        vel.x = randPlusMinusPoint5Scaled(3.0f);
        vel.y = Rand_ZeroFloat(2.0f) + 1.0f;
        vel.z = randPlusMinusPoint5Scaled(3.0f);
        accel.x = accel.z = 0.0f;
        accel.y = -0.1f;
        pos.x = spawnPos->x + randPlusMinusPoint5Scaled(30.0f);
        pos.y = spawnPos->y + 15.0f + randPlusMinusPoint5Scaled(30.0f);
        pos.z = spawnPos->z + randPlusMinusPoint5Scaled(30.0f);
        func_800B0EB0(play, &pos, &vel, &accel, &sDarkOrange, &sDarkRed, Rand_ZeroFloat(50.0f) + 100.0f, 10,
                      Rand_ZeroFloat(5.0f) + 14.0f);
    }
}

void Boss07_Wrath_Dodge(Boss07* this, PlayState* play, u8 arg2) {
    Player* player = GET_PLAYER(play);

    if ((this->unk_15C == 0) &&
        (((this->actionFunc != Boss07_Wrath_Flip) && (this->actionFunc != Boss07_Wrath_StartJump) &&
          (this->actionFunc != Boss07_Wrath_Jump)) ||
         arg2)) {
        if (Rand_ZeroOne() < 0.5f) {
            Boss07_Wrath_SetupFlip(this, play);
        } else {
            Boss07_Wrath_SetupJump(this, play);
        }
        this->unk_158 = 10;
        this->unk_F7E = 0;
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 101;
            player->actor.parent = NULL;
            player->csMode = 0;
        }
    }
}

void Boss07_Wrath_CheckExplosives(Boss07* this, PlayState* play) {
    Actor* explosive = play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        f32 dx = explosive->world.pos.x - this->actor.world.pos.x;
        f32 dy = explosive->world.pos.y - this->actor.world.pos.y;
        f32 dz = explosive->world.pos.z - this->actor.world.pos.z;

        if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 200.0f) {
            Boss07_Wrath_Dodge(this, play, false);
            break;
        }
        explosive = explosive->next;
    }
}

void Boss07_Wrath_BlastWhip(Vec3f* bombPos, Vec3f* pos, Vec3f* pull) {
    s32 i;
    f32 push;
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3f sp50;

    sp50.x = 0.0f;

    for (i = 0; i < sWhipSegCount; i++, pos++, pull++) {
        dx = pos->x - bombPos->x;
        dy = pos->y - bombPos->y;
        dz = pos->z - bombPos->z;

        if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 300.0f) {

            push = 300.0f - sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
            push = CLAMP_MAX(push, 200.0f);

            sp50.y = push;
            sp50.z = push;
            Matrix_RotateYF(Math_Acot2F(dz, dx), MTXMODE_NEW);
            Matrix_MultVec3f(&sp50, pull);
        }
    }
}

void Boss07_Wrath_BombWhips(Boss07* this, PlayState* play) {
    Actor* explosive = play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        if (explosive->params == 1) {
            Boss07_Wrath_BlastWhip(&explosive->world.pos, this->rightWhip.pos, this->rightWhip.pull);
            Boss07_Wrath_BlastWhip(&explosive->world.pos, this->leftWhip.pos, this->leftWhip.pull);
        }
        explosive = explosive->next;
    }
}

static Vec3f sRemainsStart[REMAINS_COUNT] = {
    { 70.0f, 70.0f, -70.0f },
    { 24.0f, 88.0f, -70.0f },
    { -24.0f, 88.0f, -70.0f },
    { -70.0f, 70.0f, -70.0f },
};
static Vec3s sRemainsEnd[REMAINS_COUNT] = {
    { 712, 0xD500, -416 },
    { -712, 0x2B00, -420 },
    { 702, 0xAB00, 415 },
    { -712, 0x5500, 416 },
}; // y value here is y rotation, not position

void Boss07_Init(Actor* thisx, PlayState* play2) {
    static s16 sRemainsParams[REMAINS_COUNT] = {
        MAJORA_REMAINS + REMAINS_ODOLWA,
        MAJORA_REMAINS + REMAINS_GYORG,
        MAJORA_REMAINS + REMAINS_GOHT,
        MAJORA_REMAINS + REMAINS_TWINMOLD,
    };    
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;

    if (this->actor.params == MAJORA_STATIC) {
        this->actor.update = Boss07_Static_Update;
        this->actor.draw = Boss07_Static_Draw;
        this->actor.flags &= ~1;
        sMajoraStatic = this;
        sKillProjectiles = false;
        play->envCtx.lightSettingOverride = 0;
        play->envCtx.unk_E0 = 2;
        return;
    }

    if (this->actor.params == MAJORA_BOSS) {
        this->actor.params = MAJORA_MASK;
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x,
                    this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, MAJORA_STATIC);
        play->specialEffects = (void*)sEffects;

        for (i = 0; i < ARRAY_COUNT(sEffects); i++) {
            sEffects[i].type = 0;
        }
        for (i = 0; i < ARRAY_COUNT(sBossRemains); i++) {
            sBossRemains[i] = NULL;
        }
    }
    this->actor.targetMode = 5;
    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.gravity = -2.5f;

    if (thisx->params >= MAJORA_REMAINS) {
        this->actor.update = Boss07_Remains_Update;
        this->actor.draw = Boss07_Remains_Draw;

        sBossRemains[thisx->params - MAJORA_REMAINS] = this;
        if (gSaveContext.eventInf[6] & 2) {
            Actor_SetScale(&this->actor, 0.03f);
            this->actor.world.pos.x = sRemainsEnd[this->actor.params - MAJORA_REMAINS].x;
            this->actor.world.pos.y = 370.0f;
            this->actor.world.pos.z = sRemainsEnd[this->actor.params - MAJORA_REMAINS].z;
            this->actor.shape.rot.y = sRemainsEnd[this->actor.params - MAJORA_REMAINS].y;
            Boss07_Remains_SetupFly(this, play);
        } else {
            Boss07_Remains_SetupIntro(this, play);
        }
        this->actor.flags &= ~1;
        this->actor.colChkInfo.damageTable = &sRemainsDmgTable;
        return;
    }

    if (this->actor.params == MAJORA_TOP) {
        static EffectTireMarkInit sTopTireMarkInit = { 0, 40, { 0, 0, 15, 200 } };

        this->actor.update = Boss07_Top_Update;
        this->actor.draw = Boss07_Top_Draw;
        Boss07_Top_SetupThrown(this, play);
        this->actor.colChkInfo.damageTable = &sTopDmgTable;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, KREG(55) + 9.0f);
        this->actor.shape.shadowAlpha = 180;
        Collider_InitAndSetCylinder(play, &this->cyl2, &this->actor, &sTopCylInit);
        Effect_Add(play, &this->effectIndex, 4, 0, 0, &sTopTireMarkInit);
        this->actor.flags &= ~1;
        return;
    } 

    if ((this->actor.params == MAJORA_REMAINS_SHOT) || (this->actor.params == MAJORA_INCARNATION_SHOT)) {
        this->actor.update = Boss07_Projectile_Update;
        this->actor.draw = Boss07_Projectile_Draw;
        this->actor.flags &= ~1;
        Collider_InitAndSetCylinder(play, &this->cyl2, &this->actor, &sShotCylInit);
        func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_ENEMY);
        this->unk_181C = Rand_ZeroFloat(3.99f);
        return;
    }

    if ((this->actor.params == MAJORA_MASK) || (this->actor.params == MAJORA_MASK_CS)) {
        this->actor.colChkInfo.damageTable = &sMaskDmgTable;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 15.0f);
        SkelAnime_Init(play, &this->skelAnime, &gMajorasMaskSkel, &gMajorasMaskFloatingAnim, this->jointTable,
                        this->morphTable, MAJORAS_MASK_LIMB_MAX);
        if (this->actor.params == MAJORA_MASK) {
            static EffectTireMarkInit sMaskTireMarkInit = { 0, 40, { 0, 0, 15, 200 } };

            this->actor.update = Boss07_Mask_Update;
            this->actor.draw = Boss07_Mask_Draw;
            Effect_Add(play, &this->effectIndex, 4, 0, 0, &sMaskTireMarkInit);
            sMajorasMask = this;
            if (gSaveContext.eventInf[6] & 2) {
                this->actor.world.pos.x = 0.0f;
                this->actor.world.pos.y = sREG(17) + 277.0f;
                this->actor.world.pos.z = -922.5f;
                Boss07_Mask_SetupIdle(this, play);
                this->moveTarget.x = 0.0f;
                this->moveTarget.y = 200.0f;
                this->moveTarget.z = 0.0f;
                this->unk_170 = 0.0f;
                this->timers[0] = 50;
                this->timers[2] = 200;
                this->unk_1888 = 50;
                this->actor.flags |= 1;
                sMusicStartTimer = 20;
            } else {
                Boss07_Mask_SetupIntro(this, play);
            }
            Collider_InitAndSetQuad(play, &this->quad1, &this->actor, &sMaskQuadInit1);
            Collider_InitAndSetQuad(play, &this->quad2, &this->actor, &sMaskQuadInit2);
            this->actor.colChkInfo.health = 14;
            for (i = 0; i < ARRAY_COUNT(sRemainsParams); i++) {
                Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, 0.0f, 0.0f, 0.0f, 0, 0, 0,
                            sRemainsParams[i]);
            }
        }
        return;
    }

    if ((this->actor.params == MAJORA_INCARNATION) || (this->actor.params == MAJORA_AFTERIMAGE)) {
        Actor_SetScale(&this->actor, 0.015000001f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gMajorasIncarnationSkel,
                            &gMajorasIncarnationTauntDance1Anim, this->jointTable, this->morphTable,
                            MAJORAS_INCARNATION_LIMB_MAX);
        if (this->actor.params == MAJORA_AFTERIMAGE) {
            this->timers[0] = this->actor.world.rot.z;
            this->actor.world.rot.z = 0;
            this->actor.update = Boss07_Afterimage_Update;
            this->actor.draw = Boss07_Afterimage_Draw;
            this->actor.flags &= ~1;
        } else {
            this->actor.colChkInfo.damageTable = &sIncarnationDmgTable;
            this->actor.colChkInfo.health = 30;
            this->actor.update = Boss07_Incarnation_Update;
            this->actor.draw = Boss07_Incarnation_Draw;
            Collider_InitAndSetJntSph(play, &this->sph1, &this->actor, &sIncarnationJntSphInit1,
                                        this->sphElems1);
            ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 80.0f);
            this->subCamIndex = this->actor.shape.rot.z;
            if (this->subCamIndex != 0) {
                Boss07_Incarnation_SetupIntro(this, play);
            } else {
                Boss07_Incarnation_SetupTaunt(this, play);
                this->unk_14A = 1;
                for (i = 0; i < 4; i++) {
                    this->unk_17B8[i] = 1.0f;
                }
                play->envCtx.lightBlend = 0.0f;
            }
            this->unk_17E0 = 1.0f;
            this->unk_17E4 = 1.0f;
            this->unk_17F0 = 1.0f;
            this->unk_17F4 = 1.0f;
        }
        return;
    }

    sMajorasWrath = this;
    this->actor.colChkInfo.health = 40;
    this->actor.colChkInfo.damageTable = &sWrathDmgTable;
    Actor_SetScale(&this->actor, 0.01f);
    this->subCamIndex = this->actor.shape.rot.z;
    if (this->subCamIndex != 0) {
        Boss07_Wrath_SetupIntro(this, play);
    } else {
        Boss07_Wrath_SetupIdle(this, play, 50);
        this->whipScale = 1.0f;
        Audio_QueueSeqCmd(NA_BGM_MAJORAS_WRATH | 0x8000);
    }
    SkelAnime_InitFlex(play, &this->skelAnime, &gMajorasWrathSkel, &gMajorasWrathIdleAnim,
                        this->jointTable, this->morphTable, MAJORAS_WRATH_LIMB_MAX);
    Collider_InitAndSetJntSph(play, &this->sph1, &this->actor, &sWrathJntSphInit1, this->sphElems1);
    Collider_InitAndSetJntSph(play, &this->sph2, &this->actor, &sWrathJntSphInit2, this->sphElems2);
    Collider_InitAndSetCylinder(play, &this->cyl1, &this->actor, &sWrathCylInit);

    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;

    sWhipSegCount = 44;
    this->unk_17E0 = 1.0f;    
}

void Boss07_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    switch (this->actor.params) {
        case MAJORA_WRATH:
            Collider_DestroyQuad(play, &this->quad1);
            Collider_DestroyQuad(play, &this->quad2);
        case MAJORA_TOP:
            Effect_Destroy(play, this->effectIndex);
            break;
    }
}

void Boss07_Wrath_SetupIntro(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_Intro;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasWrathHeavyBreathingAnim, 0.0f);
    this->actor.flags &= ~1;
    this->unk_17D8 = 0x7F00;
    this->unk_15C = 20;
    this->unk_17E8 = 5120.0f;
}

void Boss07_Wrath_Intro(Boss07* this, PlayState* play) {
    static f32 sCamPoints[5][3] = {
        { 40.0f, 400.0f, 110.0f }, { 80.0f, 450.0f, 110.0f }, { 100.0f, 400.0f, 110.0f },
        { 60.0f, 390.0f, 110.0f }, { 30.0f, 430.0f, 110.0f },
    };
    this->unk_15C = 20;
    SkelAnime_Update(&this->skelAnime);
    this->unk_ABC8++;
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    switch (this->csState) {
        case 0:
            this->unk_ABC8 = 0;
            this->csState = 1;
            this->subCamNextAt.z = 0.f;
            this->subCamNextEye.x = 0.0;
            this->subCamNextEye.y = KREG(17) + 100.0f - 30.0f + 80.0f;
            this->subCamNextEye.z = KREG(18) + 270.0f - 150.0f + 30.0f - 50.0f;
            this->subCamNextAt.x = 0.0f;
            this->subCamNextAt.y = 180.0f;
        case 1:
            if (this->unk_ABC8 < 40) {
                sHeartbeatTimer = 3;
            }
            if (this->unk_ABC8 > 20) {
                if (this->unk_ABC8 == 21) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_GROW_HEAD_OLD);
                }
                Math_ApproachS(&this->unk_17D8, 0, 5, 0x1000);
                this->unk_17DA = Math_SinS(this->unk_ABC8 * 0x1000) * this->unk_17E8;
                this->unk_17DC = Math_SinS(this->unk_ABC8 * 0xB00) * this->unk_17E8 * 0.5f;
                if (this->unk_ABC8 > 40) {
                    Math_ApproachZeroF(&this->unk_17E8, 1.0f, 200.0f);
                }
            }
            if (this->unk_ABC8 > 60) {
                Player* player = GET_PLAYER(play);
                s32 dataIndex = 0;
                if (0) {}

                if (player->transformation == PLAYER_FORM_GORON) {
                    dataIndex = 1;
                } else if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
                    dataIndex = 2;
                } else if (player->transformation == PLAYER_FORM_ZORA) {
                    dataIndex = 3;
                } else if (player->transformation == PLAYER_FORM_DEKU) {
                    dataIndex = 4;
                }

                Math_ApproachF(&this->subCamNextEye.y, sCamPoints[dataIndex][0], 0.075f, this->subCamSpeedMod * 7.0f);
                Math_ApproachF(&this->subCamNextEye.z, sCamPoints[dataIndex][1], 0.075f, this->subCamSpeedMod * 17.0f);
                Math_ApproachF(&this->subCamNextAt.y, sCamPoints[dataIndex][2], 0.075f, this->subCamSpeedMod * 7.0f);
                Math_ApproachF(&this->subCamSpeedMod, 1.0f, 1.0f, 0.01f);
                if (this->unk_ABC8 == 70) {
                    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathIntroAnim, -15.0f);
                    this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathIntroAnim);
                    func_8019FE1C(&this->actor.projectedPos, NA_SE_EV_ICE_PILLAR_RISING, 1.0f);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_SHOUT);
                }
                if (this->unk_ABC8 >= 110) {
                    Math_ApproachF(&this->whipScale, 1.0f, 1.0f, 0.05f);
                    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.01f * 80;
                    this->leftWhip.drag = this->rightWhip.drag = 1.0f;
                }
                if (this->unk_ABC8 == 127) {
                    this->whipScale = 1.0f;
                }
                if (this->unk_ABC8 == 120) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP2_OLD);
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_KICK_OLD);
                    func_8019FE74(&gSfxVolume, 0.0f, 0x3C);
                }
                if (this->unk_ABC8 == 112) {
                    Audio_QueueSeqCmd(NA_BGM_MAJORAS_WRATH | 0x8000);
                }
                if (this->unk_ABC8 == 137) {
                    TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt,
                                           Lib_SegmentedToVirtual(&gMajorasWrathTitleCardTex), 0xA0, 0xB4, 0x80, 0x28);
                }
                if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
                    s32 i;
                    Camera* sp48 = Play_GetCamera(play, 0);

                    this->csState = 0;
                    Boss07_Wrath_SetupIdle(this, play, 50);
                    sp48->eye = this->subCamEye;
                    sp48->eyeNext = this->subCamEye;
                    sp48->at = this->subCamAt;
                    func_80169AFC(play, this->subCamIndex, 0);
                    this->subCamIndex = 0;
                    Cutscene_End(play, &play->csCtx);
                    func_800B7298(play, &this->actor, 6);
                    this->actor.flags |= 1;
                    func_80165690();
                    if (sBossRemains[REMAINS_ODOLWA] != NULL) {
                        for (i = 0; i < ARRAY_COUNT(sBossRemains); i++) {
                            func_800BC154(play, &play->actorCtx, &sBossRemains[i]->actor, ACTORCAT_BOSS);
                        }
                    }
                }
            }
            break;
    }
    Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
    Matrix_MultVec3f(&this->subCamNextAt, &this->subCamAt);
    if (this->subCamIndex != 0) {
        ShrinkWindow_SetLetterboxTarget(0x1B);
        Play_SetCameraAtEye(play, this->subCamIndex, &this->subCamAt, &this->subCamEye);
    }
}

void Boss07_Wrath_SetupDeath(Boss07* this, PlayState* play) {
    s32 i;

    Audio_QueueSeqCmd(NA_BGM_STOP | 0x10000);
    Boss07_MovePlayer(play);
    this->actionFunc = Boss07_Wrath_Death;
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDeathAnim, 0.0f);
    this->actor.flags &= ~1;
    this->csState = 0;
    this->unk_ABC8 = 0;
    if (sBossRemains[REMAINS_ODOLWA] != NULL) {
        for (i = 0; i < 4; i++) {
            sBossRemains[i]->actionState = MAJORAS_REMAINS_STATE_2;
        }
    }
    this->unk_15C = 1000;
}

void Boss07_Wrath_Death(Boss07* this, PlayState* play) {
    s32 i;
    s32 spC0 = 0;
    Vec3f spB4;
    Vec3f spA8 = { 0.0f, 0.0f, 0.0f };
    f32 spA4 = 0.0f, spA0 = 0.1f;
    Camera* camera = Play_GetCamera(play, 0);

    this->unk_15C = 1000;
    Boss07_SmoothStop(this, 1.0f);
    switch (this->csState) {
        case 0:
            if (ActorCutscene_GetCurrentIndex() != -1) {
                break;
            }
            Cutscene_Start(play, &play->csCtx);
            func_800B7298(play, &this->actor, 1);
            this->subCamIndex = Play_CreateSubCamera(play);
            Play_ChangeCameraStatus(play, 0, 1);
            Play_ChangeCameraStatus(play, this->subCamIndex, 7);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_DEAD_ROD);
        case 1:
            this->unk_ABC8 = 0;
            this->csState = 2;
            this->subCamEye.x = camera->eye.x;
            this->subCamEye.y = camera->eye.y;
            this->subCamEye.z = camera->eye.z;
            this->subCamAt.x = camera->at.x;
            this->subCamAt.y = camera->at.y;
            this->subCamAt.z = camera->at.z;
            this->subCamRotY = this->actor.shape.rot.y * M_PI / 0x8000;
            this->subCamRotVel = this->subCamSpeedMod = sMajoraStatic->unk_180C = 0.0f;
            Boss07_InitRand(1, 0x71AC, 0x263A);
            for (i = 0; i < ARRAY_COUNT(this->deathLightScale); i++) {
                this->deathLightScale[i] = Boss07_RandZeroOne() - 1.0f;
            }
            func_8016566C(150);
        case 2:
            if (this->unk_ABC8 == 20) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            if (this->unk_ABC8 == 40) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            if (this->unk_ABC8 == 60) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            if (this->unk_ABC8 == 80) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            spB4.x = 0.0f;
            spB4.y = -90.0f;
            spB4.z = 350.0f;
            this->subCamNextAt.x = this->actor.focus.pos.x;
            this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f;
            this->subCamNextAt.z = this->actor.focus.pos.z;

            if ((this->unk_ABC8 >= 50) && (this->unk_ABC8 < 80)) {
                if (this->unk_ABC8 == 50) {
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_WIND1_OLD);
                }
                spB4.x = 30.0f;
                spB4.z = 120.0f;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f + 30.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            } else if ((this->unk_ABC8 >= 80) && (this->unk_ABC8 < 110)) {
                if (this->unk_ABC8 == 80) {
                    this->skelAnime.curFrame -= 30.0f;
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_WIND2_OLD);
                }
                spB4.x = -10.0f;
                spB4.z = 150.0f;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f - 60.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            } else if ((this->unk_ABC8 >= 110) && (this->unk_ABC8 < 140)) {
                if (this->unk_ABC8 == 110) {
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_WIND3_OLD);
                }
                spB4.x = -70.0f;
                spB4.z = 110.0f;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f + 30.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            }
            if (this->unk_ABC8 >= (sREG(15) + 140)) {
                this->csState = 4;
                this->subCamEyeModY = sREG(16) + 270.0f + 50.0f;
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_FLOAT);
            } else {
                break;
            }
        case 4:
            if ((this->unk_ABC8 >= (sREG(90) + 260)) && (this->unk_ABC8 < (sREG(91) + 370))) {
                spC0 = KREG(14) + 1;
                this->subCamRotY = this->actor.shape.rot.y * M_PI / 0x8000;
                spB4.x = 0.0f;
                spB4.y = this->subCamEyeModY + -190.0f;
                spB4.z = sREG(17) + 390.0f - 380.0f;

                this->subCamNextAt.x = this->actor.focus.pos.x;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f - 60.0f + sREG(18) + 130.0f;
                this->subCamNextAt.z = this->actor.focus.pos.z;

                Math_ApproachF(&this->subCamEyeModY, sREG(19) + 240.0f, 0.05f, 1.0f + (sREG(20) * 0.1f));
                spA4 = 2000.0f;
                spA0 = 1.0f;

                this->unk_1D8 = KREG(81) + 10;
                this->unk_AB48 = 1;
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EV_BURN_OUT - SFX_FLAG);
            } else {
                spB4.x = 0.0f;
                spB4.y = -190.0f;
                spB4.z = 390.0f;
                this->subCamNextAt.x = this->actor.focus.pos.x;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f - 60.0f;
                this->subCamNextAt.z = this->actor.focus.pos.z;
                this->unk_1D8 = 0;
                if (this->unk_ABC8 > 330) {
                    spA4 = 2000.0f;
                    spA0 = 1.0f;
                }
                Math_ApproachZeroF(&this->actor.world.pos.x, 0.1f, this->subCamSpeedMod);
                Math_ApproachZeroF(&this->actor.world.pos.z, 0.1f, this->subCamSpeedMod);
                Math_ApproachF(&this->subCamSpeedMod, 5.0f, 1.0f, 0.1f);
            }
            if (this->unk_ABC8 >= 260) {
                f32 sp98;
                f32 sp94;
                s16 temp_a0;

                if (this->unk_ABC8 == 260) {
                    func_801A479C(&sSfxPoint, NA_SE_EN_LAST3_DEAD_LIGHTS_OLD, 0x3C);
                }

                play->envCtx.fillScreen = 1;
                play->envCtx.screenFillColor[0] = play->envCtx.screenFillColor[1] =
                    play->envCtx.screenFillColor[2] = 255;
                if (this->unk_ABC8 < 350) {
                    sp98 = 0.5f;
                    sp94 = 0.02f;
                    play->envCtx.screenFillColor[3] = 0;
                } else {
                    sp98 = 5.0f;
                    sp94 = 0.1f;
                    temp_a0 = (this->unk_ABC8 * 2) - 700;
                    if (temp_a0 > 250) {
                        temp_a0 = 250;
                    }
                    play->envCtx.screenFillColor[3] = temp_a0;
                    if (this->unk_ABC8 == 400) {
                        func_8019FE74(&gSfxVolume, 0.0f, 90);
                    }
                    if (this->unk_ABC8 == (KREG(94) + 440)) {
                        play->nextEntranceIndex = 0x5400;
                        gSaveContext.nextCutsceneIndex = 0xFFF7;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                    }
                }
                if (this->unk_ABC8 > 300) {
                    sMajoraStatic->unk_1808 = 1;
                    Math_ApproachF(&sMajoraStatic->unk_180C, 30.0f, 0.1f, 1.5f);
                    sMajoraStatic->unk_1810 = this->bodyPartsPos[2];
                    Math_ApproachF(&this->unk_AB4C, 1.0f, 0.1f, 0.05f);
                    for (i = 0; i < ARRAY_COUNT(this->deathLightScale); i++) {
                        Math_ApproachF(&this->deathLightScale[i], sp98, 1.0f, sp94);
                    }
                    Math_ApproachF(&play->envCtx.lightBlend, 1.0f, 1.0f, 0.1f);
                }
            }
            this->subCamRotY += this->subCamRotVel;
            this->subCamRotVel += 0.0004f;
            if (this->subCamRotVel > 0.02f) {
                this->subCamRotVel = 0.02f;
            }
            if (this->unk_ABC8 >= (sREG(93) + 180)) {
                Vec3f sp84 = { 0.0f, 10.0f, 0.0f };
                Vec3f sp78 = { 0.0f, -0.5f, 0.0f };
                Vec3f sp6C;
                f32 sp68;

                play_sound(NA_SE_EV_EARTHQUAKE_LAST2 - SFX_FLAG);
                if (spC0 == 0) {
                    sp68 = 2.0f;
                } else {
                    sp68 = (KREG(53) * 0.01f) + 0.2f;
                }
                spA8.x = Math_SinS(this->unk_ABC8 * 0x7000) * sp68;
                spA8.y = Math_SinS(this->unk_ABC8 * 0x5000) * sp68 * 2.5f;
                spA8.z = Math_CosS(this->unk_ABC8 * 0x8000) * sp68;
                for (i = 0; i < 2; i++) {
                    sp6C.x = randPlusMinusPoint5Scaled(500.0f) + this->actor.world.pos.x;
                    sp6C.y = Rand_ZeroFloat(50.0f) + this->actor.world.pos.y + 200.0f;
                    sp6C.z = randPlusMinusPoint5Scaled(500.0f) + this->actor.world.pos.z;
                    EffectSsHahen_Spawn(play, &sp6C, &sp84, &sp78, 0, Rand_ZeroFloat(5.0f) + 20.0f, -1, 0xA, NULL);
                }
            }
            if (this->unk_ABC8 >= (sREG(94) + 290)) {
                this->unk_1D8 = KREG(86) + 25;
                Math_ApproachZeroF(&this->whipScale, 1.0f, 0.015f);
            }
            break;
    }
    Matrix_RotateYF(this->subCamRotY, MTXMODE_NEW);
    Matrix_MultVec3f(&spB4, &this->subCamNextEye);
    this->subCamNextEye.x += this->actor.focus.pos.x;
    this->subCamNextEye.y += this->actor.focus.pos.y;
    this->subCamNextEye.z += this->actor.focus.pos.z;

    Math_ApproachF(&this->subCamEye.x, this->subCamNextEye.x, spA0, 40.0f + spA4);
    Math_ApproachF(&this->subCamEye.y, this->subCamNextEye.y, spA0, 40.0f + spA4);
    Math_ApproachF(&this->subCamEye.z, this->subCamNextEye.z, spA0, 40.0f + spA4);

    Math_ApproachF(&this->subCamAt.x, this->subCamNextAt.x, spA0, 70.0f + spA4);
    Math_ApproachF(&this->subCamAt.y, this->subCamNextAt.y, spA0, 70.0f + spA4);
    Math_ApproachF(&this->subCamAt.z, this->subCamNextAt.z, spA0, 70.0f + spA4);
    if (this->subCamIndex != 0) {
        Vec3f sp5C;

        sp5C.x = this->subCamAt.x + spA8.x;
        sp5C.y = this->subCamAt.y + spA8.y;
        sp5C.z = this->subCamAt.z + spA8.z;
        Play_SetCameraAtEye(play, this->subCamIndex, &sp5C, &this->subCamEye);
    }
    SkelAnime_Update(&this->skelAnime);
    this->unk_ABC8++;
}

void Boss07_Wrath_SetupIdle(Boss07* this, PlayState* play, s16 delay) {
    this->actionFunc = Boss07_Wrath_Idle;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasWrathIdleAnim, -10.0f);
    if (delay != 0) {
        this->timers[0] = delay;
    } else {
        this->timers[0] = Rand_ZeroFloat(30.0f);
    }
    this->actor.flags |= 1;
}

void Boss07_Wrath_Idle(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    this->rightWhip.stiffness = this->leftWhip.stiffness = 0.7f;
    this->rightWhip.gravity = this->leftWhip.gravity = -15.0f;
    this->rightWhip.drag = this->leftWhip.drag = 2.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    if ((this->actor.xzDistToPlayer <= 200.0f) && (player->actor.world.pos.y < 10.0f)) {
        if (Rand_ZeroOne() < 0.3f) {
            this->actor.xzDistToPlayer = 250.0f;
        }
        Boss07_Wrath_SetupAttack(this, play);
    } else if (this->timers[0] == 0) {
        if (KREG(78) == 1) {
            Boss07_Wrath_SetupSpawnTop(this, play);
        } else if ((s8)this->actor.colChkInfo.health >= 28) {
            Boss07_Wrath_SetupAttack(this, play);
        } else if (((s8)this->actor.colChkInfo.health <= 12) && (Rand_ZeroOne() < 0.65f)) {
            Boss07_Wrath_SetupSpawnTop(this, play);
        } else if (Rand_ZeroOne() < 0.3f) {
            Boss07_Wrath_SetupGrab(this, play);
        } else {
            Boss07_Wrath_SetupAttack(this, play);
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    this->unk_174 = true;
}

void Boss07_Wrath_SetupJump(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_StartJump;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathBackflipAnim, -5.0f);
    this->actionTimer = 0;
}

void Boss07_Wrath_StartJump(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    if (this->actionTimer == 1) {
        this->actor.velocity.y = 35.0f;
        this->actor.world.rot.y = Math_Acot2F(-this->actor.world.pos.z, -this->actor.world.pos.x) * (0x8000 / M_PI);
        this->actionFunc = Boss07_Wrath_Jump;
        this->actor.speedXZ = 20.0f;
    }
}

void Boss07_Wrath_Jump(Boss07* this, PlayState* play) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MIBOSS_JUMP2 - SFX_FLAG);
    if (this->actionTimer == 13) {
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_LAUGH_OLD);
    }
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        Boss07_Wrath_SetupIdle(this, play, 1);
        this->unk_156 = 5;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x4000);
}

void Boss07_Wrath_SetupFlip(Boss07* this, PlayState* play) {
    f32 dx;
    f32 dz;
    s16 temp;
    Vec3f sp30;
    s32 pad;

    this->actionFunc = Boss07_Wrath_Flip;
    this->actor.velocity.y = 25.0f;
    dx = 0.0f - this->actor.world.pos.x;
    dz = 0.0f - this->actor.world.pos.z;

    temp = this->actor.yawTowardsPlayer - (s16)(Math_Acot2F(dz, dx) * (0x8000 / M_PI));
    if (temp < 0) {
        dx = 200.0f;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathFlipLeftAnim, -5.0f);
    } else {
        dx = -200.0f;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathFlipRightAnim, -5.0f);
    }
    Matrix_RotateYS(this->actor.yawTowardsPlayer, MTXMODE_NEW);
    Matrix_MultVecX(dx, &sp30);
    dx = sp30.x - this->actor.world.pos.x;
    dz = sp30.z - this->actor.world.pos.z;
    this->actor.world.rot.y = Math_Acot2F(dz, dx) * (0x8000 / M_PI);
    this->actionTimer = 0;
    this->actor.speedXZ = 17.0f;
}

void Boss07_Wrath_Flip(Boss07* this, PlayState* play) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MIBOSS_JUMP2 - SFX_FLAG);
    SkelAnime_Update(&this->skelAnime);
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    if ((this->actionTimer == 10) && (Rand_ZeroOne() < 0.5f)) {
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_LAUGH_OLD);
    }
    if ((this->actor.velocity.y < 0.0f) && (this->actor.bgCheckFlags & 1)) {
        if (Rand_ZeroOne() < 0.3f) {
            Boss07_Wrath_Dodge(this, play, true);
        } else {
            Boss07_Wrath_SetupIdle(this, play, 1);
            this->actor.speedXZ = 5.0f;
        }
        this->unk_156 = 5;
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x4000);
}

void Boss07_Wrath_SetupSidestep(Boss07* this, PlayState* play) {
    f32 phi_f12;
    f32 phi_f14;
    s32 pad;
    s16 sp22;

    this->actionFunc = Boss07_Wrath_Sidestep;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasWrathSidestepAnim, -5.0f);
    phi_f14 = -this->actor.world.pos.x;
    phi_f12 = -this->actor.world.pos.z;
    sp22 = this->actor.yawTowardsPlayer - (s16)(Math_Acot2F(phi_f12, phi_f14) * (0x8000 / M_PI));
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
    if (sp22 < 0) {
        this->skelAnime.playSpeed = 1.0f;
        phi_f14 = 300.0f;
    } else {
        this->skelAnime.playSpeed = -1.0f;
        phi_f14 = -300.0f;
    }
    Matrix_MultVecX(phi_f14, &this->moveTarget);
    this->moveTarget.x += this->actor.world.pos.x;
    this->moveTarget.z += this->actor.world.pos.z;
    this->timers[1] = 21;
    this->unk_158 = 10;
    this->unk_170 = 0.0f;
    this->unk_ABCC = 0;
}

void Boss07_Wrath_Sidestep(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actionTimer == 20) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_KICK_OLD);
    }
    this->unk_ABCC++;
    if ((this->unk_ABCC % 16) == 0) {
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
    }
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    Math_ApproachF(&this->actor.world.pos.x, this->moveTarget.x, 0.8f, this->unk_170);
    Math_ApproachF(&this->actor.world.pos.z, this->moveTarget.z, 0.8f, this->unk_170);
    Math_ApproachF(&this->unk_170, 20.0f, 1.0f, 10.0f);
    if (this->timers[1] == 0) {
        if (Rand_ZeroOne() < 0.3f) {
            Boss07_Wrath_SetupSidestep(this, play);
        } else {
            Boss07_Wrath_SetupIdle(this, play, 1);
        }
    }
}

void Boss07_Wrath_SetupAttack(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->actionFunc = Boss07_Wrath_Attack;
    this->timers[1] = 0;
    if (player->stateFlags3 & 0x100) {
        this->actionState = MAJORAS_WRATH_ATTACK_4;
    } else if (this->actor.xzDistToPlayer <= 300.0f) {
        if (this->actor.xzDistToPlayer <= 200.0f) {
            this->actionState = MAJORAS_WRATH_ATTACK_7;
        } else {
            this->actionState = MAJORAS_WRATH_ATTACK_4;
        }
    } else {
        this->actionState = Rand_ZeroFloat(6.99f);
        if (((s8)this->actor.colChkInfo.health >= 28) && ((this->actionState == MAJORAS_WRATH_ATTACK_1) || (this->actionState == MAJORAS_WRATH_ATTACK_2))) {
            this->actionState = MAJORAS_WRATH_ATTACK_0;
        }
    }
    switch (this->actionState) {
        case MAJORAS_WRATH_ATTACK_0:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathShortSingleWhipAttackAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathShortSingleWhipAttackAnim);
            break;
        case MAJORAS_WRATH_ATTACK_1:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathWhipFlurryAttackAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathWhipFlurryAttackAnim);
            break;
        case MAJORAS_WRATH_ATTACK_2:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDoubleWhipAttackAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathDoubleWhipAttackAnim);
            break;
        case MAJORAS_WRATH_ATTACK_3:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathLongSingleWhipAttackAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathLongSingleWhipAttackAnim);
            break;
        case MAJORAS_WRATH_ATTACK_4:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathSpinAttackAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathSpinAttackAnim);
            Boss07_RandVec3fXZ(&this->moveTarget, 650.0f);
            this->unk_170 = 0.0f;
            break;
        case MAJORAS_WRATH_ATTACK_5:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathTauntAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathTauntAnim);
            break;
        case MAJORAS_WRATH_ATTACK_6:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathThreeAttackComboAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathThreeAttackComboAnim);
            break;
        case MAJORAS_WRATH_ATTACK_7:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathKickAnim, -5.0f);
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathKickAnim);
            break;
    }
    this->actionTimer = 0;
}

void Boss07_Wrath_Attack(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.01f * 80;
    this->leftWhip.gravity = this->rightWhip.gravity = -5.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->leftWhip.drag = this->rightWhip.drag = 1.0f;
    if (this->actionTimer > 20) {
        this->unk_174 = true;
    }
    switch (this->actionState) {
        case MAJORAS_WRATH_ATTACK_0:
            if (this->actionTimer == (s16)(KREG(92) + 1)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if ((this->actionTimer >= 15) && (this->actionTimer < 18)) {
                this->rightWhip.tension = 500.0f;
            }
            if (this->actionTimer == 9) {
                this->unk_14F = 11;
            }
            if (this->actionTimer == 1) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP_OLD);
            }
            if (this->actionTimer == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
            }
            break;
        case MAJORAS_WRATH_ATTACK_1:
            if (this->actionTimer == (s16)(KREG(91) + 3)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_THROW_OLD);
            }
            if ((this->actionTimer >= 8) && (this->actionTimer <= 55)) {
                this->leftWhip.tension = this->rightWhip.tension = 300.0f;
                if ((((this->actionTimer + 2) % 4) == 0) && (Rand_ZeroOne() < 0.5f)) {
                    play_sound(NA_SE_EN_LAST3_ROD_FLOOR_OLD);
                }
                if ((this->actionTimer % 4) == 0) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
                }
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            }
            break;
        case MAJORAS_WRATH_ATTACK_2:
            if (this->actionTimer == (s16)(KREG(84) + 5)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if ((this->actionTimer >= 32) && (this->actionTimer <= 38)) {
                this->rightWhip.tension = 300.0f;
                this->leftWhip.tension = 300.0f;
            }
            if (this->actionTimer == 28) {
                this->unk_14F = 11;
            }
            if (this->actionTimer == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP_OLD);
            }
            if (this->actionTimer == 32) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
            }
            break;
        case MAJORAS_WRATH_ATTACK_3:
            if (this->actionTimer == (s16)(KREG(84) + 5)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if ((this->actionTimer > 30) && (this->actionTimer <= 35)) {
                this->rightWhip.tension = 1200.0f;
            }
            if (this->actionTimer == 23) {
                this->unk_14F = 11;
            }
            Math_ApproachF(&this->unk_184, -0.1f, 0.5f, 0.1f);
            Math_ApproachF(&this->unk_188, 0.3f, 0.5f, 0.1f);
            if (this->actionTimer == 5) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP_OLD);
            }
            if (this->actionTimer == 30) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
            }
            break;
        case MAJORAS_WRATH_ATTACK_4:
            if ((this->actionTimer > 16) && (this->actionTimer <= 40)) {
                this->leftWhip.tension = this->rightWhip.tension = 200.0f;
                if ((this->actionTimer % 8) == 0) {
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_KOMA_OLD);
                }
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_DANCE_OLD - SFX_FLAG);
                Math_ApproachF(&this->actor.world.pos.x, this->moveTarget.x, 0.1f, this->unk_170);
                Math_ApproachF(&this->actor.world.pos.z, this->moveTarget.z, 0.1f, this->unk_170);
                Math_ApproachF(&this->unk_170, 20.0f, 1.0f, 4.0f);
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x2000);
                this->unk_174 = false;
            }
            break;
        case MAJORAS_WRATH_ATTACK_7:
            this->unk_174 = false;
            if (this->actionTimer == 3) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_KICK_OLD);
            }
            break;
        case MAJORAS_WRATH_ATTACK_5:
            this->rightWhip.stiffness = this->leftWhip.stiffness = 0.7f;
            this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            this->unk_174 = true;
            break;
        case MAJORAS_WRATH_ATTACK_6:
            if (this->actionTimer == (s16)(KREG(85) + 5)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if ((this->actionTimer >= 14) && (this->actionTimer < 19)) {
                this->rightWhip.tension = 150.0f;
            }
            if ((this->actionTimer >= 23) && (this->actionTimer < 29)) {
                this->leftWhip.tension = 200.0f;
            }
            if ((this->actionTimer >= 43) && (this->actionTimer < 49)) {
                this->rightWhip.tension = 200.0f;
            }
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            if (this->actionTimer == 20) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP_OLD);
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if (this->actionTimer == 5) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP2_OLD);
            }
            if (this->actionTimer == 41) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            break;
    }
    if (Animation_OnFrame(&this->skelAnime, this->unk_1D4) || (this->timers[1] == 1)) {
        Boss07_Wrath_SetupIdle(this, play, 0);
    }
}

void Boss07_Wrath_SetupGrab(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_Grab;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathGrabAnim, -5.0f);
    this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathGrabAnim);
    this->actionTimer = 0;
}

void Boss07_Wrath_Grab(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x800, 3, 0x2000);
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.01f * 80;
    this->leftWhip.drag = this->rightWhip.drag = 1.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->rightWhip.gravity = -5.0f;
    this->leftWhip.gravity = -15.0f;
    if ((this->actionTimer >= 14) && (this->actionTimer <= 18)) {
        this->rightWhip.tension = 500.0f;
    }
    if (this->actionTimer >= 18) {
        Boss07_Wrath_SetupIdle(this, play, Rand_ZeroFloat(20.0f) + 20.0f);
        play_sound(NA_SE_EN_LAST3_ROD_MID_OLD);
    }
}

void Boss07_Wrath_GrabPlayer(Boss07* this, PlayState* play) {
    s32 sp2C;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    player->actor.world.pos = this->unk_F80;
    this->actor.flags &= ~1;
    this->unk_15A = 20;
    this->unk_F7C++;
    if (this->actionTimer > (s16)(46 - this->unk_F7E)) {
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_THROW_OLD);
        play_sound(NA_SE_EN_LAST3_COIL_ATTACK_OLD);
        this->actionFunc = Boss07_Wrath_ThrowPlayer;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathThrowAnim, -5.0f);
        this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathThrowAnim);
        this->actionTimer = 0;
    }
    if ((func_800B64FC(play, 1000.0f, &this->actor.world.pos, &sp2C) >= 0.0f) && (sp2C == 1)) {
        Boss07_Wrath_SetupShock(this, play);
    }
}

void Boss07_Wrath_ThrowPlayer(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 phi_f0;
    f32 phi_f2;
    s32 sp30;

    SkelAnime_Update(&this->skelAnime);
    this->unk_15A = 20;
    if (this->actionTimer == 6) {
        this->unk_F7E = 0;
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 101;
            player->actor.parent = NULL;
            player->csMode = 0;
            if (player->transformation == PLAYER_FORM_DEKU) {
                phi_f0 = 23.0f;
                phi_f2 = 20.0f;
            } else if (player->transformation == PLAYER_FORM_GORON) {
                phi_f0 = 15.0f;
                phi_f2 = 10.0f;
            } else if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
                phi_f0 = 10.0f;
                phi_f2 = 3.0f;
            } else {
                phi_f0 = 20.0f;
                phi_f2 = 15.0f;
            }
            func_800B8D50(play, NULL, phi_f0, this->actor.yawTowardsPlayer + 0x9000, phi_f2, 0x10);
        }
    }
    if (this->actionTimer < 7) {
        player->actor.world.pos = this->unk_F80;
        if ((func_800B64FC(play, 1000.0f, &this->actor.world.pos, &sp30) >= 0.0f) && (sp30 == 1)) {
            Boss07_Wrath_SetupShock(this, play);
        }
    }
    if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
        Boss07_Wrath_SetupIdle(this, play, 0);
    }
}

void Boss07_Wrath_SetupShock(Boss07* this, PlayState* play) {
    s32 temp_v0;
    s32 temp_v1;

    this->actionFunc = Boss07_Wrath_Shock;

    temp_v0 = this->unk_F7E + 10;
    this->unk_780 = this->unk_784 = temp_v0;

    temp_v1 = sWhipSegCount - 1;
    if (temp_v1 < temp_v0) {
        this->unk_780 = this->unk_784 = temp_v1;
    }
    this->actionTimer = 0;
    play_sound(NA_SE_EV_ELECTRIC_EXPLOSION);
}

void Boss07_Wrath_Shock(Boss07* this, PlayState* play) {
    s32 i;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    player->actor.world.pos = this->unk_F80;
    this->actor.flags &= ~1;
    this->unk_15A = 20;
    if (this->actionTimer <= (s16)(46 - this->unk_F7E)) {
        this->unk_F7C++;
    }
    for (i = 0; i < 4; i++) {
        if (this->unk_784 != 0) {
            this->unk_784--;
        }
    }
    if (this->unk_784 == 0) {
        Math_ApproachF(&play->envCtx.lightBlend, 1.0f, 1.0f, 0.3f);
        Math_ApproachF(&this->unk_32C, 5.0f, 0.5f, 3.0f);
        play_sound(NA_SE_EN_BIRI_SPARK - SFX_FLAG);
    } else {
        this->unk_32C = 0.01f;
    }
    if (this->unk_32C > 4.0f) {
        this->actionFunc = Boss07_Wrath_ShockStun;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathStunAnim, -10.0f);
        this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathStunAnim);
        this->unk_F7E = 0;
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 101;
            player->actor.parent = NULL;
            player->csMode = 0;
        }
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                    this->actor.focus.pos.y - 10.0f, this->actor.focus.pos.z, 0, 0, 0, 4);
        this->actionTimer = 0;
    }
}

void Boss07_Wrath_ShockStun(Boss07* this, PlayState* play) {
    s32 i;

    SkelAnime_Update(&this->skelAnime);
    this->unk_15A = 20;
    for (i = 0; i < 2; i++) {
        DECR(this->unk_780);
    }
    if (this->actionTimer < 70) {
        Math_ApproachF(&this->unk_32C, 5.0f, 0.5f, 3.0f);
        Math_ApproachF(&this->unk_330, 2.5f, 0.5f, 2.0f);
        play_sound(NA_SE_EN_BIRI_SPARK - SFX_FLAG);
        Math_ApproachF(&play->envCtx.lightBlend, 1.0f, 1.0f, 0.3f);
    }
    if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
        Boss07_Wrath_Dodge(this, play, true);
    }
}

void Boss07_Wrath_SetupStunned(Boss07* this, PlayState* play) {
    if (this->actionFunc != Boss07_Wrath_Stunned) {
        this->actionFunc = Boss07_Wrath_Stunned;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathStunAnim, -10.0f);
        this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathStunAnim);
    }
    this->unk_158 = 10;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_DAMAGE_OLD);
}

void Boss07_Wrath_SetupSpawnTop(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_SpawnTop;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathReleaseTopAnim, -5.0f);
    this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathReleaseTopAnim);
    this->actionTimer = 0;
}

void Boss07_Wrath_SpawnTop(Boss07* this, PlayState* play) {
    this->unk_15A = 20;
    if (this->actionTimer < (s16)(KREG(40) + 14)) {
        this->unk_778 += 6;
        if (this->unk_778 > 44) {
            this->unk_778 = 44;
        }
    }
    if (this->actionTimer == 8) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, MAJORA_TOP);
    }
    if (1) {}
    if (this->actionTimer == 10) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
    }
    if (this->actionTimer == (s16)(KREG(40) + 18)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_KOMA_OLD);
    }
    if ((this->actionTimer < (s16)(KREG(40) + 14)) || ((s16)(KREG(41) + 17) < this->actionTimer)) {
        SkelAnime_Update(&this->skelAnime);
    }
    if ((this->actionTimer >= (s16)(KREG(40) + 14)) &&
        ((this->actionTimer <= (s16)(KREG(41) + 17)) || ((s16)(KREG(42) + 21) <= this->actionTimer))) {
        this->unk_778 -= KREG(39) + 5;
        if (this->unk_778 < 0) {
            this->unk_778 = 0;
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, KREG(8) * 0x100 + this->actor.yawTowardsPlayer + 0xF00, 3, 0x2000);
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.01f * 80;
    this->leftWhip.drag = this->rightWhip.drag = 1.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->rightWhip.gravity = -5.0f;
    this->leftWhip.gravity = -15.0f;

    if (((s16)(KREG(43) + 12) <= this->actionTimer) && (this->actionTimer <= (s16)(KREG(44) + 17))) {
        this->rightWhip.tension = KREG(6) + 500.0f;
    }
    if (this->actionTimer >= (s16)(KREG(45) + 36)) {
        Boss07_Wrath_SetupIdle(this, play, Rand_ZeroFloat(20.0f) + 20.0f);
    }
}

void Boss07_Wrath_Stunned(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_COMMON_WEAKENED - SFX_FLAG);
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.7f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
        Boss07_Wrath_Dodge(this, play, true);
    }
}

void Boss07_Wrath_SetupDamaged(Boss07* this, PlayState* play, u8 damage, u8 effect) {
    if ((s8)this->actor.colChkInfo.health >= 0) {
        this->actor.colChkInfo.health -= damage;
    }
    if ((s8)this->actor.colChkInfo.health <= 0) {
        if (KREG(19) != 0) {
            Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_DEAD_OLD);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_DEAD_OLD);
        }
        this->unk_148 = true;
        Enemy_StartFinishingBlow(play, &this->actor);
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_DAMAGE2_OLD);
        if (this->actionFunc != Boss07_Wrath_Damaged) {
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDamageAnim, -10.0f);
            this->actionFunc = Boss07_Wrath_Damaged;
            this->unk_1D4 = Animation_GetLastFrame(&gMajorasWrathDamageAnim);
            this->unk_ABCC = 0;
        } else if (effect == 14) {
            if (this->skelAnime.curFrame <= (this->unk_1D4 - 5.0f)) {
                this->unk_158 = 30;
            } else {
                Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDamageAnim, -5.0f);
            }
        }
    }
}

void Boss07_Wrath_Damaged(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->unk_ABCC++;
    if ((this->unk_ABCC % 16) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WALK2_OLD);
    }
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.stiffness = this->rightWhip.stiffness = 0.7f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
        Boss07_Wrath_Dodge(this, play, true);
    }
}

void Boss07_Wrath_WhipCollisionCheck(Vec3f* arg0, f32 arg1, Boss07* this, PlayState* play) {
    s32 i;
    s32 sp98 = -1;
    Player* player = GET_PLAYER(play);
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3f sp7C;

    if ((arg1 >= 50.0f) && (this->unk_15A == 0)) {
        Actor* prop = play->actorCtx.actorLists[ACTORCAT_PROP].first;

        while (prop != NULL) {
            if (prop->id == ACTOR_OBJ_TSUBO) {
                for (i = 10; i < sWhipSegCount; i += 3) {
                    dx = prop->world.pos.x - arg0[i].x;
                    dy = prop->world.pos.y + 10.0f - arg0[i].y;
                    dz = prop->world.pos.z - arg0[i].z;

                    if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < (KREG(38) + 60.0f)) {
                        ((ObjTsubo*)prop)->unk_19B = 1;
                        Boss07_SpawnDustAtPos(play, &prop->world.pos, 10);
                    }
                }
            }
            prop = prop->next;
        }
    }
    if ((arg1 >= 50.0f) && (this->unk_15A == 0) && (!(player->stateFlags3 & 0x100) || (this->actionState == MAJORAS_WRATH_ATTACK_4))) {
        if ((func_800B64FC(play, 1000.0f, &this->actor.world.pos, &sp98) >= 0.0f) && (sp98 != 1)) {
            sp98 = -1;
        }
        for (i = 10; i < sWhipSegCount; i += 3) {
            dx = player->actor.world.pos.x - arg0[i].x;
            dy = player->actor.world.pos.y + 30.0f - arg0[i].y;
            dz = player->actor.world.pos.z - arg0[i].z;

            dy *= 1.75f;

            if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 140.0f) {
                if ((this->actionFunc == Boss07_Wrath_Grab) && (sp98 != 1) && !(player->stateFlags3 & 0x1000) &&
                    (520.0f <= this->actor.xzDistToPlayer) && (this->actor.xzDistToPlayer <= 900.0f)) {
                    if (play->grabPlayer(play, player)) {
                        f32 dx1;
                        f32 dy1;
                        f32 dz1;
                        f32 dxz1;

                        player->actor.parent = &this->actor;
                        Audio_PlaySfxGeneral(NA_SE_VO_LI_DAMAGE_S, &player->actor.projectedPos, 4, &D_801DB4B0,
                                             &D_801DB4B0, &gSfxDefaultReverb);
                        this->unk_F7C = 0;
                        this->unk_F7E = ((this->actor.xzDistToPlayer - 300.0f) / 22.0f) + 10.0f;
                        dx1 = player->actor.world.pos.x - this->rightWhip.basePos.x;
                        dy1 = player->actor.world.pos.y - this->rightWhip.basePos.y + 50.0f;
                        dz1 = player->actor.world.pos.z - this->rightWhip.basePos.z;
                        dxz1 = sqrtf(SQ(dx1) + SQ(dz1));
                        this->unk_F8C = Math_Acot2F(dz1, dx1);
                        this->unk_F90 = -Math_Acot2F(dxz1, dy1);
                        this->actionFunc = Boss07_Wrath_GrabPlayer;
                        this->actionTimer = 0;
                        this->rightWhip.tension = 0.0f;
                        play_sound(NA_SE_EN_LAST3_GET_LINK_OLD);
                    }
                } else if ((player->stateFlags1 & 0x400000) && Boss07_IsFacingPlayer(this, play)) {
                    player->unk_B80 = 10.0f;
                    player->unk_B84 = this->actor.yawTowardsPlayer;
                    play_sound(NA_SE_IT_SHIELD_BOUND);
                    this->unk_15A = 4;
                } else {
                    func_800B8D50(play, NULL, 5.0f, this->actor.shape.rot.y, 0.0f, 8);
                    this->unk_15A = 20;
                }
                sp7C = player->actor.world.pos;

                sp7C.x += randPlusMinusPoint5Scaled(30.0f);
                sp7C.y += randPlusMinusPoint5Scaled(30.0f) + 20.0f;
                sp7C.z += randPlusMinusPoint5Scaled(30.0f);
                EffectSsHitmark_SpawnFixedScale(play, 0, &sp7C);
                Boss07_SpawnDustAtPos(play, &player->actor.world.pos, 7);
                break;
            }
        }
    }
}

void Boss07_Wrath_CollisionCheck(Boss07* this, PlayState* play) {
    s32 i;
    s32 j;
    u8 damage;
    Player* player = GET_PLAYER(play);

    if (this->unk_15C == 0) {
        if (this->sph2.elements[0].info.toucherFlags & 2) {
            this->sph2.elements[0].info.toucherFlags &= ~2;
            player->unk_B84 = this->actor.yawTowardsPlayer;
            player->unk_B80 = 20.0f;
            Boss07_SpawnDustAtPos(play, &player->actor.world.pos, 12);
            play_sound(NA_SE_IT_HOOKSHOT_STICK_OBJ);
        }
        for (i = 0; i < ARRAY_COUNT(this->sphElems1); i++) {
            if (this->sph1.elements[i].info.bumperFlags & 2) {
                for (j = 0; j < ARRAY_COUNT(this->sphElems1); j++) {
                    this->sph1.elements[j].info.bumperFlags &= ~2;
                }
                if (this->unk_1804 == 10) {
                    this->unk_1806 = 0;
                }
                switch (this->actor.colChkInfo.damageEffect) {
                    case 3:
                        this->unk_1805 = 10;
                        break;
                    case 2:
                        this->unk_1805 = 1;
                        break;
                    case 4:
                        this->unk_1805 = 20;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 4);
                        break;
                    case 10:
                        this->unk_1805 = 40;
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                        break;
                    case 9:
                        this->unk_1805 = 30;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 3, 4);
                        break;
                }
                damage = this->actor.colChkInfo.damage;
                if ((this->actionFunc == Boss07_Wrath_Stunned) || (this->actionFunc == Boss07_Wrath_Damaged)) {
                    if ((this->actionFunc == Boss07_Wrath_Stunned) && (this->actor.colChkInfo.damageEffect != 14) &&
                        (this->actor.colChkInfo.damageEffect != 13) && (this->actor.colChkInfo.damageEffect != 9) &&
                        (this->actor.colChkInfo.damageEffect != 12)) {
                        Boss07_Wrath_SetupStunned(this, play);
                        this->unk_15C = 6;
                    } else {
                        this->unk_15E = 15;
                        this->unk_15C = (this->actor.colChkInfo.damageEffect == 12) ? 15 : 5;
                        Boss07_Wrath_SetupDamaged(this, play, damage, this->actor.colChkInfo.damageEffect);
                    }
                } else {
                    this->unk_15C = 15;
                    Boss07_Wrath_SetupStunned(this, play);
                    this->unk_F7E = 0;
                    if (&this->actor == player->actor.parent) {
                        player->unk_AE8 = 101;
                        player->actor.parent = NULL;
                        player->csMode = 0;
                    }
                }
                break;
            }
        }
    }
}

void Boss07_Wrath_BreakIce(Boss07* this, PlayState* play) {
    static Color_RGBA8 sLightCyan = { 170, 255, 255, 255 };
    static Color_RGBA8 sLightBlue = { 200, 200, 255, 255 };
    static Vec3f sIceAccel = { 0.0f, -1.0f, 0.0f };
    Vec3f pos;
    Vec3f vel;
    s32 i;

    SoundSource_PlaySfxAtFixedWorldPos(play, this->bodyPartsPos, 30, NA_SE_EV_ICE_BROKEN);
    for (i = 0; i < 30; i++) {
        vel.x = randPlusMinusPoint5Scaled(7.0f);
        vel.z = randPlusMinusPoint5Scaled(7.0f);
        vel.y = Rand_ZeroFloat(6.0f) + 4.0f;

        pos.x = this->bodyPartsPos[i / 2].x + vel.x;
        pos.y = this->bodyPartsPos[i / 2].y + vel.y;
        pos.z = this->bodyPartsPos[i / 2].z + vel.z;
        EffectSsEnIce_Spawn(play, &pos, Rand_ZeroFloat(1.0f) + 1.5f, &vel, &sIceAccel, &sLightCyan, &sLightBlue,
                            30);
    }
}

void Boss07_Wrath_DamageEffects(Boss07* this, PlayState* play) {
    DECR(this->unk_1806);

    switch (this->unk_1805) {
        case 0:
            this->unk_1804 = 0;
            this->unk_1806 = 0;
            this->unk_1800 = 0.0f;
            break;
        case 1:
            this->unk_1804 = 0;
            this->unk_1806 = 40;
            this->unk_1800 = 1.0f;
            this->unk_17F8 = 0.0f;
            this->unk_1805++;
            Actor_SetColorFilter(&this->actor, 0x4000, 120, 0, 60);
        case 2:
            if (this->unk_1806 == 0) {
                Math_ApproachZeroF(&this->unk_1800, 1.0f, 0.02f);
                if (this->unk_1800 == 0.0f) {
                    this->unk_1805 = 0;
                }
            } else {
                Math_ApproachF(&this->unk_17F8, 1.0f, 0.1f, 0.5f);
            }
            break;
        case 10:
            this->unk_1804 = 11;
            this->unk_1806 = 40;
            this->unk_1800 = 1.0f;
            this->unk_17FC = 1.0f;
            this->unk_17F8 = 0.0f;
            this->unk_1805++;
        case 11:
            if (this->unk_1806 == 0) {
                Boss07_Wrath_BreakIce(this, play);
                this->unk_1805 = 0;
            } else {
                if (this->unk_1806 == 50) {
                    this->unk_1804 = 10;
                }
                Math_ApproachF(&this->unk_17F8, 1.0f, 1.0f, 0.08f);
                Math_ApproachF(&this->unk_17FC, 1.0f, 0.05f, 0.05f);
            }
            break;
            if (1) {
                case 20:
                    this->unk_1804 = 20;
                    this->unk_1806 = 40;
                    this->unk_17F8 = 1.0f;
            } else {
                case 30:
                    this->unk_1804 = 21;
                    this->unk_1806 = 40;
                    this->unk_17F8 = 3.0f;
            }
            this->unk_1800 = 1.0f;
            this->unk_1805 = 21;
        case 21:
            if (this->unk_1806 == 0) {
                Math_ApproachZeroF(&this->unk_17F8, 1.0f, 0.03f);
                if (this->unk_17F8 == 0.0f) {
                    this->unk_1805 = 0;
                    this->unk_1800 = 0.0f;
                }
            } else {
                Math_ApproachF(&this->unk_17F8, 1.5f, 0.5f, 0.5f);
            }
            break;
        case 40:
            this->unk_1804 = 30;
            this->unk_1806 = 50;
            this->unk_1800 = 1.0f;
            this->unk_17F8 = (KREG(18) * 0.1f) + 1.0f;
            this->unk_1805++;
        case 41:
            if (this->unk_1806 == 0) {
                Math_ApproachZeroF(&this->unk_17F8, 1.0f, 0.05f);
                if (this->unk_17F8 == 0.0f) {
                    this->unk_1805 = 0;
                    this->unk_1800 = 0.0f;
                }
            }
            break;
    }
}

void Boss07_Wrath_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;
    Player* player = GET_PLAYER(play);

    play->envCtx.unk_C1 = 2;
    play->envCtx.unk_C2 = 0;
    this->actor.hintId = 52;
    Math_ApproachF(&play->envCtx.lightBlend, 0.0f, 1.0f, 0.03f);
    this->unk_149 = true;
    Math_Vec3f_Copy(&sSfxPoint, &this->actor.projectedPos);
    if (KREG(63) == 0) {
        this->unk_174 = false;
        this->actionTimer++;
        Actor_SetScale(&this->actor, 0.015f);
        Math_ApproachZeroF(&this->unk_184, 1.0f, 0.02f);
        Math_ApproachZeroF(&this->unk_188, 1.0f, 0.02f);
        for (i = 0; i < 3; i++) {
            DECR(this->timers[i]);
        }
        DECR(this->unk_15A);
        DECR(this->unk_158);
        DECR(this->unk_15C);
        DECR(this->unk_15E);
        DECR(this->unk_156);

        Math_ApproachZeroF(&this->unk_32C, 1.0f, 0.2f);
        Math_ApproachZeroF(&this->unk_330, 1.0f, 0.04f);
        this->actionFunc(this, play);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 100.0f, 100.0f, 5);
        if (this->unk_14F != 0) {
            this->unk_14F--;
            if ((this->actionFunc == Boss07_Wrath_Attack) && (this->unk_14F == 0)) {
                play_sound(NA_SE_EN_LAST3_ROD_FLOOR_OLD);
            }
        }
    } else {
        sWhipSegCount = 45;
    }
    Boss07_Wrath_WhipCollisionCheck(this->rightWhip.pos, this->rightWhip.tension, this, play);
    Boss07_Wrath_WhipCollisionCheck(this->leftWhip.pos, this->leftWhip.tension, this, play);
    if (this->unk_158 != 0) {
        for (i = 0; i < ARRAY_COUNT(this->sphElems1); i++) {
            this->sph1.elements[i].info.bumperFlags &= ~2;
        }
    }
    Boss07_Wrath_CollisionCheck(this, play);
    if (this->unk_15C != 0) {
        this->unk_778 = 0;
    }
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->sph1.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->sph1.base);
    if ((this->actionFunc == Boss07_Wrath_Attack) && (this->actionState == MAJORAS_WRATH_ATTACK_7) && (this->actionTimer >= 6)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->sph2.base);
    } else {
        if (this->unk_174 && Boss07_IsFacingPlayer(this, play)) {
            if ((player->unk_D57 == 4) && (player->itemActionParam != 0xC)) {
                if ((this->actor.xzDistToPlayer >= 400.0f) && (Rand_ZeroOne() < 0.5f)) {
                    Boss07_Wrath_SetupSidestep(this, play);
                } else {
                    Boss07_Wrath_Dodge(this, play, false);
                }
            }
            if ((player->unk_ADC != 0) && (this->actor.xzDistToPlayer <= 150.0f)) {
                Boss07_Wrath_Dodge(this, play, false);
            }
        }
        if ((this->actionFunc != Boss07_Wrath_Stunned) && (this->actionFunc != Boss07_Wrath_Damaged)) {
            if ((player->stateFlags3 & 0x00001000) && !(player->stateFlags3 & 0x00080000) &&
                (this->actor.xzDistToPlayer <= 250.0f)) {
                Boss07_Wrath_Dodge(this, play, false);
            }
        }
    }
    if (this->unk_174) {
        Boss07_Wrath_CheckExplosives(this, play);
    }
    Boss07_Wrath_BombWhips(this, play);
    if (KREG(88) || this->unk_148) {
        KREG(88) = false;
        this->unk_148 = false;
        Boss07_Wrath_SetupDeath(this, play);
    }
    if (this->unk_1D8 != 0) {
        u16* sp74 = SEGMENTED_TO_VIRTUAL(gMajorasWrathEarTex);
        u16* sp70 = SEGMENTED_TO_VIRTUAL(gMajoraStripesTex);
        u16* sp6C = SEGMENTED_TO_VIRTUAL(gMajorasWrathMouthTex);
        u16* sp68 = SEGMENTED_TO_VIRTUAL(gMajoraBloodshotEyeTex);
        u16* sp64 = SEGMENTED_TO_VIRTUAL(gMajorasWrathEyeTex);
        u16* sp60 = SEGMENTED_TO_VIRTUAL(gMajorasMaskWithNormalEyesTex);
        u16* sp5C = SEGMENTED_TO_VIRTUAL(gMajoraVeinsTex);
        u16* sp58 = SEGMENTED_TO_VIRTUAL(gMajoraHandTex);
        u16* sp54 = SEGMENTED_TO_VIRTUAL(gMajoraBodyTex);

        for (i = 0; i < this->unk_1D8; i++) {
            s32 sp50;
            s32 sp4C;
            s32 sp48;
            s32 sp44;

            sp44 = Rand_ZeroFloat(0x100 - 0.01f);
            sp4C = Rand_ZeroFloat(0x200 - 0.01f);
            sp48 = Rand_ZeroFloat(0x400 - 0.01f);
            sp50 = Rand_ZeroFloat(0x800 - 0.01f);

            sp74[sp44] = sp70[sp4C] = sp6C[sp48] = sp68[sp48] = sp64[sp50] = sp60[sp50] = sp5C[sp50] = sp58[sp50] =
                sp54[sp50] = 0;
        }
    }
    Boss07_Wrath_DamageEffects(this, play);
    if ((this->unk_156 == 1) || (this->unk_156 == 4)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WALK2_OLD);
    }
    if ((player->actor.world.pos.y > 100.0f) && (player->actor.world.pos.z < KREG(82) + -850.0f)) {
        player->actor.world.pos.z = KREG(82) + -850.0f;
    }
    if (player->actor.world.pos.y < -300.0f) {
        player->actor.world.pos.x = player->actor.world.pos.y = player->actor.world.pos.z = 0.0f;
    }
}

void Boss07_UpdateWhips(Boss07* this, PlayState* play, Vec3f* base, Vec3f* pos, Vec3f* rot, Vec3f* pull,
                        f32 gravity, f32 stiffness, f32 drag, f32 tension, Vec3s* baseRot, s16 argB, f32 scale,
                        s32 whipHand) {
    s32 i;
    s32 phi_s6;
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f22;
    f32 phi_f0;
    Vec3f* temp = pull;
    f32 temp1;
    Vec3f spB8 = { 0.0f, 0.0f, 0.0f };
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;

    spB8.z = 22.0f * scale;

    for (i = 0; i < (s16)sWhipSegCount; i++, pull++) {
        if (i == 0) {
            pos[0] = *base;
        } else {
            Math_ApproachF(&pull->x, 0.0f, 1.0f, drag);
            Math_ApproachF(&pull->y, 0.0f, 1.0f, drag);
            Math_ApproachF(&pull->z, 0.0f, 1.0f, drag);
        }
    }
    spAC.z = 20.0f;
    Matrix_RotateYS(baseRot->y, MTXMODE_NEW);
    Matrix_RotateXS(baseRot->x, MTXMODE_APPLY);
    Matrix_RotateZS(baseRot->z, MTXMODE_APPLY);
    Matrix_RotateYS(0x4000, MTXMODE_APPLY);
    Matrix_MultVecZ(spAC.z, &sp94);
    if (argB != 0) {
        spAC.z = 200.0f;
        Matrix_RotateYF(this->unk_F8C, MTXMODE_NEW);
        Matrix_RotateXFApply(this->unk_F90);
    } else {
        spAC.z = tension;
    }
    Matrix_MultVecZ(spAC.z, &sp7C);

    pos++;
    rot++;
    pull = temp + 1;
    phi_s6 = 0;

    for (i = 1; i < (s16)sWhipSegCount; i++, pull++, pos++, rot++) {
        if (i < 6) {
            sp88.x = (6 - i) * sp94.x * 0.2f;
            sp88.y = (6 - i) * sp94.y * 0.2f;
            sp88.z = (6 - i) * sp94.z * 0.2f;
        } else if (argB != 0) {
            if (argB <= i && i < (s16)(argB + this->unk_F7C)) {
                sp88.y = 0.0f;
                sp88.x = sinf(this->actor.yawTowardsPlayer * M_PI / 0x8000 + (phi_s6 * 1.4f)) * 100.0f;
                sp88.z = cosf(this->actor.yawTowardsPlayer * M_PI / 0x8000 + (phi_s6 * 1.4f)) * 100.0f;
                sp7C = gZeroVec3f;
                phi_s6++;
            }
        } else {
            sp88 = gZeroVec3f;
        }
        temp_f24 = pos->x + pull->x - (pos - 1)->x + sp88.x + sp7C.x;
        phi_f0 = pos->y + pull->y + gravity + sp88.y + sp7C.y;
        phi_f0 = CLAMP_MIN(phi_f0, 2.0f);
        temp_f26 = phi_f0 - (pos - 1)->y;
        temp_f20 = pos->z + pull->z - (pos - 1)->z + sp88.z + sp7C.z;
        temp_f22 = Math_Acot2F(temp_f20, temp_f24);
        temp1 = -Math_Acot2F(sqrtf(SQ(temp_f24) + SQ(temp_f20)), temp_f26);
        (rot - 1)->y = temp_f22;
        (rot - 1)->x = temp1;
        Matrix_RotateYF(temp_f22, MTXMODE_NEW);
        Matrix_RotateXFApply(temp1);
        Matrix_MultVecZ(spB8.z, &spA0);
        if (1) {}
        temp_f24 = pos->x;
        temp_f26 = pos->y;
        temp_f20 = pos->z;

        pos->x = (pos - 1)->x + spA0.x;
        pos->y = (pos - 1)->y + spA0.y;
        pos->z = (pos - 1)->z + spA0.z;

        if ((i != 0) && (i == argB)) {
            spAC.x = 15.0f;
            spAC.y = -30.0f;
            spAC.z = -12.0f;
            Matrix_MultVec3f(&spAC, &spA0);
            this->unk_F80.x = pos->x + spA0.x;
            this->unk_F80.y = pos->y + spA0.y;
            this->unk_F80.z = pos->z + spA0.z;
        } else if ((whipHand == 0) && (this->actionFunc == Boss07_Wrath_SpawnTop)) {
            if (i == KREG(90) + sWhipSegCount - this->unk_778 + 1) {
                spAC.x = KREG(60);
                spAC.y = KREG(61);
                spAC.z = KREG(62);
                Matrix_MultVec3f(&spAC, &spA0);
                this->unk_F80.x = pos->x + spA0.x;
                this->unk_F80.y = pos->y + spA0.y;
                this->unk_F80.z = pos->z + spA0.z;
            }
        }
        pull->x = (pos->x - temp_f24) * stiffness;
        pull->y = (pos->y - temp_f26) * stiffness;
        pull->z = (pos->z - temp_f20) * stiffness;
        if (pull->x > 200.0f) {
            pull->x = 200.0f;
        }
        if (pull->x < -200.0f) {
            pull->x = -200.0f;
        }
        if (pull->y > 200.0f) {
            pull->y = 200.0f;
        }
        if (pull->y < -200.0f) {
            pull->y = -200.0f;
        }
        if (pull->z > 200.0f) {
            pull->z = 200.0f;
        }
        if (pull->z < -200.0f) {
            pull->z = -200.0f;
        }
    }
}

void Boss07_DrawWhips(Boss07* this, PlayState* play, Vec3f* pos, Vec3f* rot, f32 arg4, s32 hand) {
    s32 phi_s6;
    s32 i;
    f32 phi_f12;
    s32 pad[2];
    Vec3f* vec2 = pos;
    Vec3f* vec3 = rot;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasMaskWhipShadowMaterialDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sREG(48) + 45, 35, 75, 255);
    phi_s6 = (hand == 0) ? this->unk_778 : 0;
    for (i = 0; i < (sWhipSegCount - phi_s6) - 1; i++, pos++, rot++) {
        Matrix_Translate(pos->x, 0.0f, pos->z, MTXMODE_NEW);
        Matrix_Scale(1.0f, 0.0f, 1.0f, MTXMODE_APPLY);
        Matrix_RotateYF(rot->y, MTXMODE_APPLY);
        Matrix_RotateXFApply(rot->x);
        phi_f12 = (i > 24) ? 0.025f : ((f32)(24 - i) * 1 * 0.001f) + 0.025f;
        Matrix_Scale(phi_f12, phi_f12, ((2 * arg4) + 0.5f) * 0.01f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathWhipModelDL);
    }
    pos = vec2;
    rot = vec3;
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathWhipMaterialDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 155, 155, 80, 255);
    for (i = 0; i < (sWhipSegCount - phi_s6) - 1; i++, pos++, rot++) {
        Matrix_Translate(pos->x, pos->y, pos->z, MTXMODE_NEW);
        Matrix_RotateYF(rot->y, MTXMODE_APPLY);
        Matrix_RotateXFApply(rot->x);
        phi_f12 = (i > 24) ? 0.025f : ((f32)(24 - i) * 1 * 0.001f) + 0.025f;
        Matrix_Scale(phi_f12, phi_f12, ((2 * arg4) + 0.5f) * 0.01f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathWhipModelDL);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

s32 Boss07_Wrath_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                  Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_WRATH_LIMB_HEAD) {
        rot->x += this->unk_17DA;
        rot->y += this->unk_17D8;
        rot->z += this->unk_17DC;
    }
    return false;
}

void Boss07_Wrath_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static s8 sLimbColliderIndex[30] = {
        -1, -1, 2, -1, 7, -1, 8, -1, -1, 9, -1, 10, -1, -1, 1, -1, 5, -1, 6, -1, -1, 3, -1, 4, -1, -1, 0, -1, -1, -1,
    };
    static Vec3f sWrathColliderOffsets[11] = {
        { 1000.0f, 0.0f, 500.0f }, { 2000.0f, 0.0f, 0.0f }, { 1000.0f, 0.0f, 500.0f }, { 2000.0f, 0.0f, 0.0f },
        { 2000.0f, 0.0f, 0.0f },   { 2000.0f, 0.0f, 0.0f }, { 2000.0f, 0.0f, 0.0f },   { 2000.0f, 0.0f, 0.0f },
        { 2000.0f, 0.0f, 0.0f },   { 2000.0f, 0.0f, 0.0f }, { 2000.0f, 0.0f, 0.0f },
    };
    static s8 sWrathBodyParts[30] = {
        -1, -1, 2, -1, 12, -1, 13, 14, -1, 9, -1, 10, 11, -1, 1, -1, 6, 7, 8, -1, -1, 3, 4, 5, -1, -1, 0, -1, -1, -1,
    };
    static Vec3f sWhipOffset = { 1000.0f, 100.0f, 0.0f };
    Boss07* this = THIS;
    s8 sp6B;
    Vec3f sp5C;
    MtxF sp1C;

    sp6B = sWrathBodyParts[limbIndex];
    if (sp6B >= 0) {
        Matrix_MultZero(&this->bodyPartsPos[sp6B]);
    }
    sp6B = sLimbColliderIndex[limbIndex];
    if (sp6B >= 0) {
        if (this->unk_158 != 0) {
            Matrix_MultVecZ(100000.0f, &sp5C);
        } else {
            Matrix_MultVec3f(&sWrathColliderOffsets[sp6B], &sp5C);
        }
        Boss07_UpdateSpheres(sp6B, &this->sph1, &sp5C);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_HEAD) {
        Matrix_MultZero(&this->actor.focus.pos);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_HAND) {
        Matrix_MultVec3f(&sWhipOffset, &this->rightWhip.basePos);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_LOWER_ARM_ROOT) {
        Matrix_Get(&sp1C);
        Matrix_MtxFToYXZRot(&sp1C, &this->rightWhip.baseRot, 0);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_LEFT_HAND) {
        Matrix_MultVec3f(&sWhipOffset, &this->leftWhip.basePos);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_LEFT_LOWER_ARM_ROOT) {
        Matrix_Get(&sp1C);
        Matrix_MtxFToYXZRot(&sp1C, &this->leftWhip.baseRot, 0);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_FOOT) {
        Matrix_MultZero(&sp5C);
        Boss07_UpdateSpheres(0, &this->sph2, &sp5C);
    }
}

void Boss07_Wrath_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    Boss07* this = THIS;

    if ((limbIndex == MAJORAS_WRATH_LIMB_PELVIS) || (limbIndex == MAJORAS_WRATH_LIMB_LEFT_THIGH) ||
        (limbIndex == MAJORAS_WRATH_LIMB_LEFT_SHIN) || (limbIndex == MAJORAS_WRATH_LIMB_LEFT_FOOT) ||
        (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_THIGH) || (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_SHIN) ||
        (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_FOOT) || (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_UPPER_ARM) ||
        (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_FOREARM) || (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_HAND) ||
        (limbIndex == MAJORAS_WRATH_LIMB_LEFT_UPPER_ARM) || (limbIndex == MAJORAS_WRATH_LIMB_LEFT_FOREARM) ||
        (limbIndex == MAJORAS_WRATH_LIMB_LEFT_HAND) || (limbIndex == MAJORAS_WRATH_LIMB_HEAD)) {
        Matrix_Scale(1.0f, this->unk_17E0, this->unk_17E0, MTXMODE_APPLY);
    }
}

void Boss07_DrawShocks(Boss07* this, PlayState* play) {
    s32 i;
    GraphicsContext* gfxCtx;

    OPEN_DISPS(gfxCtx = play->state.gfxCtx);
    if ((this->unk_32C > 0.0f) || (this->unk_330 > 0.0f)) {
        func_8012C2DC(play->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 0, 0);

        if (this->unk_32C > 0.0f) {
            gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
            for (i = 0; i < ARRAY_COUNT(this->bodyPartsPos); i++) {
                Matrix_Translate(this->bodyPartsPos[i].x, this->bodyPartsPos[i].y, this->bodyPartsPos[i].z,
                                 MTXMODE_NEW);
                Matrix_ReplaceRotation(&play->billboardMtxF);
                Matrix_Scale(this->unk_32C, this->unk_32C, this->unk_32C, MTXMODE_APPLY);
                Matrix_RotateZF(Rand_ZeroFloat(2.0f * M_PI), MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
            }
            for (i = this->unk_780; i >= this->unk_784; i--) {
                Matrix_Translate(this->rightWhip.pos[i].x, this->rightWhip.pos[i].y, this->rightWhip.pos[i].z, 0);
                Matrix_ReplaceRotation(&play->billboardMtxF);
                Matrix_Scale(1.5f, 1.5f, 1.5f, MTXMODE_APPLY);
                Matrix_RotateZF(Rand_ZeroFloat(2.0f * M_PI), MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
            }
        }
        if (this->unk_330 > 0.0f) {
            gSPDisplayList(POLY_XLU_DISP++, gLightOrb2DL);
            for (i = 0; i < 2 * ARRAY_COUNT(this->bodyPartsPos); i++) {
                Matrix_Translate(this->bodyPartsPos[i / 2].x + randPlusMinusPoint5Scaled(30.0f),
                                 this->bodyPartsPos[i / 2].y + randPlusMinusPoint5Scaled(30.0f),
                                 this->bodyPartsPos[i / 2].z + randPlusMinusPoint5Scaled(30.0f), MTXMODE_NEW);
                Matrix_Scale(this->unk_330, this->unk_330, this->unk_330, MTXMODE_APPLY);
                Matrix_RotateXFApply(Rand_ZeroFloat(2.0f * M_PI));
                Matrix_RotateZF(Rand_ZeroFloat(2.0f * M_PI), MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
            }
        }
    }
    CLOSE_DISPS(gfxCtx);
}

void Boss07_DrawDeathLights(Boss07* this, PlayState* play, Vec3f* arg2) {
    s32 i;
    f32 temp_f12_2;
    f32 temp_f20;
    GraphicsContext* gfxCtx;
    s16* temp;

    OPEN_DISPS(gfxCtx = play->state.gfxCtx);

    if (this->unk_AB4C > 0.0f) {
        Boss07_InitRand(1, 0x71B8, 0x263A);
        POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);
        gDPSetCombineMode(POLY_XLU_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        for (i = 0; i < ARRAY_COUNT(this->deathLightScale); i++) {
            temp = sColorsYRGB[0];
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, temp[0], temp[1], temp[2], 40);
            temp_f20 = (Boss07_RandZeroOne() * 40.0f) - 30.0f;
            Matrix_Translate(this->bodyPartsPos[2].x, this->bodyPartsPos[2].y - 30.0f + 50.0f + temp_f20 + 25.0f,
                             this->bodyPartsPos[2].z, MTXMODE_NEW);
            Matrix_Translate(arg2->x, arg2->y + temp_f20, arg2->z, MTXMODE_NEW);
            Matrix_RotateYF(Boss07_RandZeroOne() * M_PI * 2.0f, MTXMODE_APPLY);
            Matrix_RotateXFApply(-0.024999999f * temp_f20);
            Matrix_RotateZF(Boss07_RandZeroOne() * M_PI * 2.0f, MTXMODE_APPLY);
            if (this->deathLightScale[i] > 0.0f) {
                Matrix_Scale(this->deathLightScale[i], 1.0f, 12.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gMajorasWrathDeathLightModelDL);
            }
        }
        func_8012C2DC(play->state.gfxCtx);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, (u8)(220 + sREG(18)), (u8)(170 + sREG(16)));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, (u8)(100 + sREG(22)), 128);

        Matrix_Translate(this->bodyPartsPos[2].x, this->bodyPartsPos[2].y, this->bodyPartsPos[2].z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_RotateZS(play->gameplayFrames * 0x80, MTXMODE_APPLY);
        temp_f12_2 = (sREG(17) + 800) * 0.01f * this->unk_AB4C;
        Matrix_Scale(temp_f12_2, temp_f12_2, 1.0f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
    }
    CLOSE_DISPS(gfxCtx);
}

void Boss07_Static_DrawLight(Boss07* this, PlayState* play) {
    s32 pad;
    GraphicsContext* gfxCtx;
    f32 sp54;
    f32 sp50;
    Player* player;

    OPEN_DISPS(gfxCtx = play->state.gfxCtx);
    player = GET_PLAYER(play);

    if (this->unk_AB44 > 0.0f) {
        func_8012C2DC(play->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)(sREG(52) + 255));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 0, 0);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);

        if (player->transformation == PLAYER_FORM_GORON) {
            sp54 = -10.0f;
            sp50 = -20.0f;
        } else {
            sp54 = sp50 = 0.0f;
        }
        if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
            sp54 -= 43.0f;
        }

        Matrix_Translate(player->actor.world.pos.x,
                         player->actor.world.pos.y + Player_GetHeight(player) - 20.0f + sp54 + sREG(60),
                         player->actor.world.pos.z + sREG(61) - 15.0f + sp50, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);

        Matrix_Scale(this->unk_AB44, this->unk_AB44, this->unk_AB44, MTXMODE_APPLY);
        Matrix_RotateZS(play->gameplayFrames * 0x40, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
    }
    CLOSE_DISPS(gfxCtx);
}

void Boss07_Wrath_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    u8* shadowTex = GRAPH_ALLOC(play->state.gfxCtx, sizeof(u8[0x40][0x40]));

    OPEN_DISPS(play->state.gfxCtx);
    Vec3f sp58;

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    Matrix_RotateYF(this->unk_184, MTXMODE_APPLY);
    Matrix_RotateXFApply(this->unk_188);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   (s32)this->skelAnime.dListCount, Boss07_Wrath_OverrideLimbDraw,
                                   Boss07_Wrath_PostLimbDraw, Boss07_Wrath_TransformLimbDraw, &this->actor);
    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);

    if (((KREG(63) == 0) || (KREG(63) == 2)) && this->unk_149) {
        Boss07_UpdateWhips(this, play, &this->rightWhip.basePos, this->rightWhip.pos, this->rightWhip.rot,
                           this->rightWhip.pull, this->rightWhip.gravity, this->rightWhip.stiffness,
                           this->rightWhip.drag, this->rightWhip.tension, &this->rightWhip.baseRot, this->unk_F7E,
                           this->whipScale, 0);
        Boss07_UpdateWhips(this, play, &this->leftWhip.basePos, this->leftWhip.pos, this->leftWhip.rot,
                           this->leftWhip.pull, this->leftWhip.gravity, this->leftWhip.stiffness, this->leftWhip.drag,
                           this->leftWhip.tension, &this->leftWhip.baseRot, 0, this->whipScale, 1);
    }
    Boss07_DrawWhips(this, play, this->rightWhip.pos, this->rightWhip.rot, this->whipScale, 0);
    Boss07_DrawWhips(this, play, this->leftWhip.pos, this->leftWhip.rot, this->whipScale, 1);
    if (this->unk_AB48 == 0) {
        Boss07_Wrath_MakeShadowTex(shadowTex, this, play);
        Boss07_Wrath_DrawShadowTex(shadowTex, this, play);
    }
    Boss07_DrawShocks(this, play);
    sp58.x = this->bodyPartsPos[2].x;
    sp58.y = this->bodyPartsPos[2].y - 30.0f + 50.0f;
    sp58.z = this->bodyPartsPos[2].z;
    Boss07_DrawDeathLights(this, play, &sp58);
    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, 0xF, this->unk_17F8, this->unk_17FC,
                            this->unk_1800, this->unk_1804);
    this->unk_149 = false;
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Wrath_MakeShadowCircles(Boss07* this, u8* shadowTex, f32 weight) {
    static s32 sShadowWidths6[6] = { 1, 2, 3, 3, 2, 1 };
    static s32 sShadowWidths7[7] = { 2, 3, 4, 4, 4, 3, 2 };
    static s32 sShadowWidths8[8] = { 2, 3, 4, 4, 4, 4, 3, 2 };
    static s32 sShadowWidths12[12] = { 2, 4, 5, 5, 6, 6, 6, 6, 5, 5, 4, 2 };
    static s32 sBodyPartsIndex[15] = { 1, -1, 1, 1, 3, 4, 1, 6, 7, 2, 9, 10, 2, 12, 13 };
    static u8 sShadowSize[15] = { 3, 2, 2, 1, 3, 3, 1, 3, 3, 1, 0, 3, 1, 0, 3 };
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_v0;
    s32 phi_a0;
    s32 phi_a3;
    s32 j = 0;
    s32 i;
    Vec3f lerp;
    Vec3f sp74;
    Vec3f sp68;

    for (i = 0; i < ARRAY_COUNT(this->bodyPartsPos); i++) {
        if ((weight == 0.0f) || ((j = sBodyPartsIndex[i]) >= 0)) {
            if (weight > 0.0f) {
                VEC3F_LERPIMPDST(&lerp, &this->bodyPartsPos[i], &this->bodyPartsPos[j], weight);

                sp74.x = lerp.x - this->actor.world.pos.x;
                sp74.y = lerp.y - this->actor.world.pos.y + 76.0f + 30.0f + 30.0f + 100.0f;
                sp74.z = lerp.z - this->actor.world.pos.z;
            } else {
                sp74.x = this->bodyPartsPos[i].x - this->actor.world.pos.x;
                sp74.y = this->bodyPartsPos[i].y - this->actor.world.pos.y + 76.0f + 30.0f + 30.0f + 100.0f;
                sp74.z = this->bodyPartsPos[i].z - this->actor.world.pos.z;
            }
            Matrix_MultVec3f(&sp74, &sp68);

            sp68.x *= 0.2f;
            sp68.y *= 0.2f;
            temp_t0 = (u16)(s32)(sp68.x + 32.0f);
            temp_t1 = (u16)((s32)sp68.y << 6);

            if (sShadowSize[i] == 2) {
                for (j = 0, phi_a3 = -0x180; j < 12; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths12[j]; phi_a0 < sShadowWidths12[j]; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTex[temp_v0] = 255;
                        }
                    }
                }
            } else if (sShadowSize[i] == 1) {
                for (j = 0, phi_a3 = -0x100; j < 8; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths8[j]; phi_a0 < sShadowWidths8[j]; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTex[temp_v0] = 255;
                        }
                    }
                }
            } else if (sShadowSize[i] == 0) {
                for (j = 0, phi_a3 = -0xC0; j < 7; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths7[j]; phi_a0 < sShadowWidths7[j] - 1; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTex[temp_v0] = 255;
                        }
                    }
                }
            } else {
                for (j = 0, phi_a3 = -0x80; j < 6; j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths6[j]; phi_a0 < sShadowWidths6[j] - 1; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x1000)) {
                            shadowTex[temp_v0] = 255;
                        }
                    }
                }
            }
        }
    }
}

void Boss07_Wrath_MakeShadowTex(u8* shadowTex, Boss07* this, PlayState* play) {
    s32 i;
    s32* shadowTex32 = (s32*)shadowTex;

    for (i = 0; i < 0x400; i++, shadowTex32++) {
        *shadowTex32 = 0;
    }
    Matrix_RotateXFNew(1.0f);
    for (i = 0; i < 6; i++) {
        Boss07_Wrath_MakeShadowCircles(this, shadowTex, i / 5.0f);
    }
}

void Boss07_Wrath_DrawShadowTex(u8* shadowTex, Boss07* this, PlayState* play) {
    s32 pad[2];
    f32 phi_f0;
    GraphicsContext* pad3 = play->state.gfxCtx;

    OPEN_DISPS(pad3);

    func_8012C28C(play->state.gfxCtx);
    phi_f0 = (400.0f - this->actor.world.pos.y) * 0.0025f;
    phi_f0 = CLAMP_MIN(phi_f0, 0.0f);
    phi_f0 = CLAMP_MAX(phi_f0, 1.0f);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(s32)(phi_f0 * 80.0f) & 0xFF);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    Matrix_Translate(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z - 20.0f, MTXMODE_NEW);
    Matrix_Scale(1.75f, 1.0f, 1.75f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathShadowMaterialDL);
    gDPLoadTextureBlock(POLY_OPA_DISP++, shadowTex, G_IM_FMT_I, G_IM_SIZ_8b, 0x40, 0x40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathShadowModelDL);
    CLOSE_DISPS(pad3);
}

void Boss07_Incarnation_AvoidPlayer(Boss07* this) {
    s32 phi_v0 = (Rand_ZeroOne() < 0.5f) ? 0x4000 : -0x4000;

    Matrix_RotateYS(this->actor.yawTowardsPlayer + phi_v0, MTXMODE_NEW);
    Matrix_MultVecZ(200.0f, &this->moveTarget);
    this->timers[1] = 30;
    this->moveTarget.x += this->actor.world.pos.x;
    this->moveTarget.z += this->actor.world.pos.z;
    this->unk_170 = 20000.0f;
}

void Boss07_Incarnation_SetupIntro(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Intro;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationJerkingAnim, 0.0f);
    this->actor.flags &= ~1;
    this->unk_17D8 = 0x6E00;
}

void Boss07_Incarnation_Intro(Boss07* this, PlayState* play) {
    s32 i;
    f32 sp58;

    SkelAnime_Update(&this->skelAnime);
    this->unk_ABC8++;
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    sp58 = Math_SinS(this->actionTimer * 0x4500) * 0.3f;
    switch (this->csState) {
        case 0:
            this->unk_ABC8 = 0;
            this->csState = 1;
            this->subCamNextAt.z = 0.0f;
        case 1:
            this->csState = 2;
            this->unk_ABC8 = 0;
            this->subCamNextEye.x = 70.0f;
            this->subCamNextEye.y = 70.0f;
            this->subCamNextEye.z = 150.0f;
            this->subCamNextAt.x = 20.0f;
            this->subCamNextAt.y = 80.0f;
            break;
        case 2:
            if (this->unk_ABC8 >= 20) {
                if (this->unk_ABC8 == 20) {
                    this->unk_17C8[3] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(&this->unk_17B8[3], 1.0f + (this->unk_17C8[3] * sp58), 1.0f, 0.5f);
            }
            if (this->unk_ABC8 > 40) {
                this->csState = 3;
                this->unk_ABC8 = 0;
            }
            break;
        case 3:
            Math_ApproachF(&this->subCamNextEye.x, 0.0f, 0.05f, this->subCamSpeedMod * 40.0f);
            Math_ApproachF(&this->subCamNextEye.y, 100.0f, 0.05f, this->subCamSpeedMod * 30.0f);
            Math_ApproachF(&this->subCamNextEye.z, 270.0f, 0.05f, this->subCamSpeedMod * 150.0f);
            Math_ApproachF(&this->subCamNextAt.x, 0.0f, 0.05f, this->subCamSpeedMod * 20.0f);
            Math_ApproachF(&this->subCamNextAt.y, 100.0f, 0.05f, this->subCamSpeedMod * 20.0f);
            Math_ApproachF(&this->subCamSpeedMod, 0.05f, 1.0f, 0.002f);
            if (this->unk_ABC8 >= 20) {
                if (this->unk_ABC8 == 20) {
                    this->unk_17C8[2] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(&this->unk_17B8[2], 1.0f + (this->unk_17C8[2] * sp58), 1.0f, 0.5f);
            }
            if (this->unk_ABC8 >= 50) {
                if (this->unk_ABC8 == 50) {
                    this->unk_17C8[1] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(&this->unk_17B8[1], 1.0f + (this->unk_17C8[1] * sp58), 1.0f, 0.5f);
            }
            if (this->unk_ABC8 >= 60) {
                if (this->unk_ABC8 == 60) {
                    this->unk_17C8[0] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(this->unk_17B8, 1.0f + (this->unk_17C8[0] * sp58), 1.0f, 0.5f);
            }
            if (this->unk_ABC8 == 80) {
                this->csState = 4;
                this->unk_ABC8 = 0;
                for (i = 0; i < 4; i++) {
                    this->unk_17B8[i] = 1.0f;
                }
            }
            break;
        case 4:
            this->subCamNextEye.x = 0.0f;
            this->subCamNextEye.y = 120.0f;
            this->subCamNextEye.z = 140.0f;
            this->subCamNextAt.y = 170.0f;
            if (this->unk_ABC8 >= 10) {
                if (this->unk_ABC8 == 10) {
                    this->unk_17C8[3] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_GROW_HEAD);
                }
                Math_ApproachS(&this->unk_17D8, (this->unk_17C8[3] * sp58) * 0x6000, 1, 0x4000);
            }
            if (this->unk_ABC8 == 30) {
                this->csState = 5;
                this->unk_ABC8 = 0;
                this->subCamSpeedMod = 0.0f;
                this->unk_1D4 = 1000.0f;
                func_80165690();
            }
            break;
        case 5:
            if (this->unk_ABC8 == 20) {
                Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationIntroDanceAnim, 0.0f);
                this->unk_1D4 = Animation_GetLastFrame(&gMajorasIncarnationIntroDanceAnim);
            }
            if (this->unk_ABC8 >= 20) {
                sREG(28) = this->unk_ABC8;
                if ((this->unk_ABC8 == (KREG(16) + 28)) || (this->unk_ABC8 == (KREG(17) + 60))) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_UAUOO2_OLD);
                }
                if ((this->unk_ABC8 == (KREG(18) + 38)) || (this->unk_ABC8 == (KREG(19) + 48)) ||
                    (this->unk_ABC8 == (KREG(20) + 68)) || (this->unk_ABC8 == (KREG(21) + 78))) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_GYM_B_OLD);
                }
                if (this->unk_ABC8 == (KREG(38) + 93)) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_UAUOO_OLD);
                }
            }
            if (this->unk_ABC8 == 45) {
                TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt,
                                       Lib_SegmentedToVirtual(&gMajorasIncarnationTitleCardTex), 0xA0, 0xB4, 0x80,
                                       0x28);
            }
            if (this->unk_ABC8 == 20) {
                Audio_QueueSeqCmd(NA_BGM_MAJORAS_INCARNATION | 0x8000);
                this->unk_14A = 1;
                play->envCtx.lightBlend = 0.0f;
            }
            Math_ApproachF(&this->subCamNextEye.x, -80.0f, 0.05f, this->subCamSpeedMod * 80.0f);
            Math_ApproachF(&this->subCamNextEye.y, 20.0f, 0.05f, this->subCamSpeedMod * 60.0f);
            Math_ApproachF(&this->subCamNextEye.z, 220.0f, 0.05f, this->subCamSpeedMod * 180.0f);
            Math_ApproachF(&this->subCamNextAt.y, 110.0f, 0.05f, this->subCamSpeedMod * 80.0f);
            Math_ApproachF(&this->subCamSpeedMod, 0.1f, 1.0f, 0.005f);
            if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
                Camera* sp54 = Play_GetCamera(play, 0);

                this->csState = 0;
                Boss07_Incarnation_SetupTaunt(this, play);
                sp54->eye = this->subCamEye;
                sp54->eyeNext = this->subCamEye;
                sp54->at = this->subCamAt;
                func_80169AFC(play, this->subCamIndex, 0);
                this->subCamIndex = 0;
                Cutscene_End(play, &play->csCtx);
                func_800B7298(play, &this->actor, 6);
                this->actor.flags |= 1;
            }
            break;
    }
    for (i = 0; i < ARRAY_COUNT(this->unk_17C8); i++) {
        Math_ApproachZeroF(&this->unk_17C8[i], 0.5f, 0.1f);
    }
    Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
    Matrix_MultVec3f(&this->subCamNextAt, &this->subCamAt);
    if (this->subCamIndex != 0) {
        ShrinkWindow_SetLetterboxTarget(0x1B);
        Play_SetCameraAtEye(play, this->subCamIndex, &this->subCamAt, &this->subCamEye);
    }
}

void Boss07_Incarnation_SetupTaunt(Boss07* this, PlayState* play) {
    static AnimationHeader* sTauntAnims[3] = {
        &gMajorasIncarnationTauntDance1Anim,
        &gMajorasIncarnationTauntDance2Anim,
        &gMajorasIncarnationTauntJumpAnim,
    };

    this->actionFunc = Boss07_Incarnation_Taunt;
    this->actionState = Rand_ZeroFloat(MAJORAS_INCARNATION_STATE_MAX - 0.001f);
    Animation_MorphToLoop(&this->skelAnime, sTauntAnims[this->actionState], -10.0f);
    this->actor.flags |= 1;
    this->timers[0] = Rand_ZeroFloat(50.0f) + 50.0f;
}

void Boss07_Incarnation_Taunt(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->actionState < MAJORAS_INCARNATION_STATE_2) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WAIT_OLD - SFX_FLAG);
    } else if ((this->actionState == MAJORAS_INCARNATION_STATE_2) && Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_JUMP_OLD);
    }
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    Math_ApproachS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 5, 0x2000);
    if ((this->timers[0] == 0) || (player->unk_D57 == 4) || (this->actor.xzDistToPlayer <= 300.0f)) {
        Boss07_Incarnation_SetupRun(this, play);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_SURPRISED_OLD);
    }
    Boss07_SpawnDust(this, play, 1, false);
}

void Boss07_Incarnation_SetupStunned(Boss07* this, PlayState* play, s16 arg2) {
    if (this->actionFunc != Boss07_Incarnation_Stunned) {
        this->actionFunc = Boss07_Incarnation_Stunned;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationFallOverStartAnim, -10.0f);
        this->unk_1D4 = Animation_GetLastFrame(&gMajorasIncarnationFallOverStartAnim);
    }
    this->unk_158 = 10;
    this->timers[0] = arg2;
    this->timers[1] = 12;
}

void Boss07_Incarnation_Stunned(Boss07* this, PlayState* play) {
    this->actor.shape.shadowAlpha = 0;
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 1.0f);
    if (this->timers[1] == 1) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_HIPLOOP_LAND);
    }
    if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
        Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationFallOverLoopAnim, -5.0f);
        this->unk_1D4 = 1000.0f;
    }
    if (this->unk_1D4 == 1000.0f) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_BIRD_OLD - SFX_FLAG);
    }
    if (this->timers[0] == 0) {
        Boss07_Incarnation_SetupTaunt(this, play);
    }
    Boss07_SpawnDust(this, play, 1, true);
}

void Boss07_Incarnation_SetupDamaged(Boss07* this, PlayState* play, u8 arg2, u8 arg3) {
    if (this->actionFunc != Boss07_Incarnation_Damaged) {
        this->actionFunc = Boss07_Incarnation_Damaged;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationDamageAnim, -2.0f);
        this->unk_1D4 = Animation_GetLastFrame(&gMajorasIncarnationDamageAnim);
    } else if (arg3 == 14) {
        if (this->skelAnime.curFrame <= (this->unk_1D4 - 5.0f)) {
            this->unk_158 = 30;
            this->unk_15C = 30;
        } else {
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationDamageAnim, -2.0f);
        }
    }

    if (this->actor.colChkInfo.health != 0) {
        this->actor.colChkInfo.health -= arg2;
        if ((s8)this->actor.colChkInfo.health <= 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_DEAD_OLD);
            this->unk_148 = true;
            this->unk_15C = 100;
            this->unk_158 = 100;
            Enemy_StartFinishingBlow(play, &this->actor);
            return;
        }
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_DAMAGE2_OLD);
}

void Boss07_Incarnation_Damaged(Boss07* this, PlayState* play) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_BIRD2_OLD - SFX_FLAG);
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
        Boss07_Incarnation_SetupRun(this, play);
    }
    Boss07_SpawnDust(this, play, 1, false);
}

void Boss07_Incarnation_SetupRun(Boss07* this, PlayState* play) {
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationRunAnim, -2.0f);
    this->actionFunc = Boss07_Incarnation_Run;
    this->timers[0] = Rand_ZeroFloat(100.0f) + 150.0f;
    Boss07_Incarnation_AvoidPlayer(this);
}

void Boss07_Incarnation_Run(Boss07* this, PlayState* play) {
    f32 sp34;
    f32 sp30;
    s32 sp2C;

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WALK_OLD - SFX_FLAG);
    this->unk_AB40++;
    if (this->unk_AB40 >= 2) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WALK2_OLD);
        this->unk_AB40 = 0;
    }
    SkelAnime_Update(&this->skelAnime);
    if ((func_800B64FC(play, 5.0f, &this->actor.world.pos, &sp2C) >= 0.0f) && (sp2C == 0)) {
        Boss07_Incarnation_SetupStunned(this, play, 50);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_DAMAGE_OLD);
    } else {
        sp34 = this->moveTarget.x - this->actor.world.pos.x;
        sp30 = this->moveTarget.z - this->actor.world.pos.z;
        if ((this->timers[1] == 0) || (SQ(sp34) + SQ(sp30) < SQ(173.20508f))) { // 100 * sqrt(3)
            if (Rand_ZeroOne() < 0.3f) {
                f32 temp_f0 = Rand_ZeroOne();

                if (temp_f0 < 0.25f) {
                    Boss07_Incarnation_SetupAttack(this, play);
                } else if (temp_f0 < 0.5f) {
                    Boss07_Incarnation_SetupHopak(this, play);
                } else if (temp_f0 < 0.75f) {
                    Boss07_Incarnation_SetupMoonwalk(this, play);
                } else if (temp_f0 < 1.0f) {
                    Boss07_Incarnation_SetupPirouette(this, play);
                }
            } else if (Rand_ZeroOne() < 0.01f) {
                Boss07_Incarnation_SetupStunned(this, play, 50);
            } else {
                Boss07_RandVec3fXZ(&this->moveTarget, 500.0f);
                this->timers[1] = Rand_ZeroFloat(50.0f) + 20.0f;
                this->unk_170 = 0.0f;
            }
        }
        Math_ApproachS(&this->actor.world.rot.y, Math_Atan2S(sp34, sp30), 5, this->unk_170);
        Math_ApproachF(&this->unk_170, 4000.0f, 1.0f, 500.0f);
        Math_ApproachF(&this->actor.speedXZ, 25.0f, 1.0f, 20.0f);
        if (this->timers[0] == 0) {
            Boss07_Incarnation_SetupTaunt(this, play);
        }
        if ((this->actor.xzDistToPlayer < 200.0f) && (this->timers[2] == 0)) {
            Boss07_Incarnation_AvoidPlayer(this);
            this->timers[0] = 50;
            this->timers[2] = 50;
        }
        Boss07_SpawnDust(this, play, 3, false);
        this->unk_18D6 = 5;
    }
}

void Boss07_Incarnation_SetupAttack(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Attack;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationEnergyBallAttackAnim, -5.0f);
    this->timers[0] = Rand_ZeroFloat(50.0f) + 30.0f;
    this->unk_188C = 0.0f;
}

void Boss07_Incarnation_Attack(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 3.0f);
    Math_ApproachS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 3, 0x3000);
    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->unk_17A0.x, this->unk_17A0.y,
                    this->unk_17A0.z, 0, 0, 0, MAJORA_INCARNATION_SHOT);
    }
    if (Animation_OnFrame(&this->skelAnime, 9.0f)) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->unk_17AC.x, this->unk_17AC.y,
                    this->unk_17AC.z, 0, 0, 0, MAJORA_INCARNATION_SHOT);
    }
    if (this->timers[0] == 0) {
        Boss07_Incarnation_SetupRun(this, play);
    }
    Boss07_SpawnDust(this, play, 1, false);
}

void Boss07_Incarnation_SetupHopak(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Hopak;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationSquattingDanceAnim, -5.0f);
    this->timers[0] = Rand_ZeroFloat(100.0f) + 100.0f;
    this->timers[1] = 0;
    this->unk_ABC8 = 0;
}

void Boss07_Incarnation_Hopak(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        if ((this->unk_ABC8 % 2) == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_UAUOO1_OLD);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_UAUOO2_OLD);
        }
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_JUMP_OLD);
        this->unk_ABC8++;
    }
    Math_ApproachF(&this->actor.speedXZ, KREG(67) + 10.0f, 1.0f, 3.0f);
    if (this->timers[1] == 0) {
        if ((this->actionTimer == 0) && (Rand_ZeroOne() < 0.7f)) {
            if (Rand_ZeroOne() < 0.75f) {
                this->unk_180 = randPlusMinusPoint5Scaled(0x10000);
            } else {
                this->unk_180 = this->actor.yawTowardsPlayer;
            }
        }
        if (this->actor.bgCheckFlags & 8) {
            this->timers[1] = 20;
            this->unk_180 = this->actor.yawTowardsPlayer;
        }
    }
    Math_ApproachS(&this->actor.world.rot.y, this->unk_180, 0xA, 0x1800);
    if ((this->timers[0] == 0) || (this->actor.xzDistToPlayer <= 200.0f)) {
        Boss07_Incarnation_SetupRun(this, play);
        if (this->timers[0] != 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_SURPRISED_OLD);
        }
    }
    Boss07_SpawnDust(this, play, 7, false);
}

void Boss07_Incarnation_SetupMoonwalk(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Moonwalk;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationMoonwalkAnim, -10.0f);
    this->timers[0] = Rand_ZeroFloat(50.0f) + 70.0f;
    this->timers[1] = 0;
}

void Boss07_Incarnation_Moonwalk(Boss07* this, PlayState* play) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_MOONWALK_OLD - SFX_FLAG);
    SkelAnime_Update(&this->skelAnime);
    Math_ApproachF(&this->actor.speedXZ, KREG(69) + -10.0f, 1.0f, 3.0f);
    if (this->timers[1] == 0) {
        if ((this->actionTimer == 0) && (Rand_ZeroOne() < 0.5f)) {
            if (Rand_ZeroOne() < 0.75f) {
                this->unk_180 = randPlusMinusPoint5Scaled(65536.0f);
            } else {
                this->unk_180 = this->actor.yawTowardsPlayer + 0x8000;
            }
        }
        if ((this->actor.bgCheckFlags & 8) != 0) {
            this->timers[1] = 20;
            this->unk_180 = this->actor.yawTowardsPlayer + 0x8000;
        }
    }
    Math_ApproachS(&this->actor.world.rot.y, this->unk_180, 0xA, 0x1000);
    if (this->timers[0] == 0) {
        Boss07_Incarnation_SetupRun(this, play);
    }
    Boss07_SpawnDust(this, play, 7, false);
}

void Boss07_Incarnation_SetupPirouette(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Pirouette;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationPirouetteAnim, -10.0f);
    this->timers[0] = Rand_ZeroFloat(70.0f) + 70.0f;
    this->timers[1] = 0;
}

void Boss07_Incarnation_Pirouette(Boss07* this, PlayState* play) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_BALLET_OLD - SFX_FLAG);
    SkelAnime_Update(&this->skelAnime);
    Math_ApproachF(&this->actor.speedXZ, KREG(69) + 10.0f, 1.0f, 1.0f);
    if (this->timers[1] == 0) {
        if (((this->actionTimer % 0x40) == 0) && (Rand_ZeroOne() < 0.5f)) {
            if (Rand_ZeroOne() < 0.75f) {
                this->unk_180 = randPlusMinusPoint5Scaled(65536.0f);
            } else {
                this->unk_180 = this->actor.yawTowardsPlayer;
            }
        }
        if (this->actor.bgCheckFlags & 8) {
            this->timers[1] = 20;
            this->unk_180 = this->actor.yawTowardsPlayer;
        }
    }
    Math_ApproachS(&this->actor.world.rot.y, this->unk_180, 0xA, 0x1000);
    if ((this->timers[0] == 0) || (this->actor.xzDistToPlayer <= 200.0f)) {
        Boss07_Incarnation_SetupRun(this, play);
        if (this->timers[0] != 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_SURPRISED_OLD);
        }
    }
    this->actor.shape.rot.y += 0x2000;
}

void Boss07_Incarnation_SetupDeath(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Death;
    Boss07_MovePlayer(play);
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationDamageAnim, -2.0f);
    this->unk_1D4 = Animation_GetLastFrame(&gMajorasIncarnationDamageAnim);
    this->csState = 0;
    this->unk_ABC8 = 0;
    this->actor.flags &= ~1;
    this->unk_15C = 20;
}

void Boss07_Incarnation_Death(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u8 sp4B = 0;

    this->unk_15C = 20;
    this->unk_ABC8++;
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 3.0f);
    switch (this->csState) {
        case 0:
            if (ActorCutscene_GetCurrentIndex() != -1) {
                break;
            }
            Cutscene_Start(play, &play->csCtx);
            func_800B7298(play, &this->actor, 7);
            this->subCamIndex = Play_CreateSubCamera(play);
            Play_ChangeCameraStatus(play, 0, 1);
            Play_ChangeCameraStatus(play, this->subCamIndex, 7);
            this->unk_ABC8 = 0;
            this->csState = 10;
            func_8016566C(150);
        case 10:
            sHeartbeatTimer = 5;
            this->subCamNextEye.x = 0.0f;
            this->subCamNextEye.y = 30.0f;
            this->subCamNextEye.z = 210.0f;
            this->subCamNextAt.x = 0.0f;
            this->subCamNextAt.y = 150.0f;
            this->subCamNextAt.z = 0.0f;
            Math_ApproachF(&this->actor.world.pos.x, 0.0f, 0.1f, 5.0f);
            Math_ApproachF(&this->actor.world.pos.z, 0.0f, 0.1f, 5.0f);
            if (Animation_OnFrame(&this->skelAnime, this->unk_1D4)) {
                this->unk_ABC8 = 0;
                this->csState = 1;
                Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationFinalHitAnim, -5.0f);
            }
            break;
        case 1:
            sHeartbeatTimer = 5;
            this->subCamNextAt.y = (Math_SinS(this->unk_ABC8 * 0x700) * 15.0f) + 150.0f;
            if (this->unk_ABC8 == 40) {
                this->unk_ABC8 = 0;
                this->csState = 2;
                this->subCamNextEye.x = -30.0f;
                this->subCamNextEye.y = 120.0f;
                this->subCamNextEye.z = 110.0f;
                this->subCamNextAt.x = -70.0f;
                this->subCamNextAt.y = 150.0f;
                this->subCamNextAt.z = -20.0f;
                this->unk_17E8 = 1.0f;
                this->unk_17EC = 0.4f;
                Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationPumpingUpAnim, -5.0f);
                this->actor.shape.rot.y = 0;
                this->actor.world.rot.y = this->actor.shape.rot.y;
                Math_ApproachF(&this->actor.world.pos.x, 0.0f, 1.0f, 200.0f);
                Math_ApproachF(&this->actor.world.pos.z, 0.0f, 1.0f, 200.0f);
                player->actor.world.pos.x = this->actor.world.pos.x;
                player->actor.world.pos.z = this->actor.world.pos.z + 300.0f;
                player->actor.world.rot.y = player->actor.shape.rot.y = -0x8000;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_PUMP_UP_OLD);
            }
            break;
        case 2:
            sHeartbeatTimer = 5;
            sp4B = 1;
            if (this->unk_ABC8 == 40) {
                this->unk_ABC8 = 0;
                this->csState = 3;
                this->subCamNextEye.x = 30.0f;
                this->subCamNextEye.y = 120.0f;
                this->subCamNextEye.z = 110.0f;
                this->subCamNextAt.x = 50.0f;
                this->subCamNextAt.y = 150.0f;
                this->subCamNextAt.z = -20.0f;
                this->unk_17E8 = 1.0f;
                this->unk_17EC = 0.4f;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_PUMP_UP_OLD);
            }
            break;
        case 3:
            sHeartbeatTimer = 5;
            sp4B = 1;
            if (this->unk_ABC8 == 40) {
                this->unk_ABC8 = 0;
                this->csState = 4;
                this->subCamNextEye.x = 0.0f;
                this->subCamNextEye.y = 90.0f;
                this->subCamNextEye.z = 110.0f;
                this->subCamNextAt.x = 0.0f;
                this->subCamNextAt.y = 90.0f;
                this->subCamNextAt.z = 0.0f;
                this->unk_17E8 = 1.0f;
                this->unk_17EC = 0.4f;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_PUMP_UP_OLD);
            }
            break;
        case 4:
            sHeartbeatTimer = 5;
            sp4B = 2;
            if (this->unk_ABC8 == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_PUMP_UP_OLD);
            }
            if (this->unk_ABC8 == 40) {
                Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x,
                            this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, this->subCamIndex, MAJORA_WRATH);
                Actor_MarkForDeath(&this->actor);
            }
            break;
    }
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
    Matrix_MultVec3f(&this->subCamNextAt, &this->subCamAt);
    if (sp4B == 1) {
        this->unk_17E0 = (Math_SinS(this->unk_ABC8 * 0x3000) * this->unk_17EC) + this->unk_17E8;
        Math_ApproachF(&this->unk_17E8, 2.0f, 1.0f, 0.05f);
        Math_ApproachZeroF(&this->unk_17EC, 1.0f, 0.01f);
    } else if (sp4B == 2) {
        this->unk_17E4 = (Math_SinS(this->unk_ABC8 * 0x3000) * this->unk_17EC) + this->unk_17E8;
        Math_ApproachF(&this->unk_17E8, 2.0f, 1.0f, 0.05f);
        Math_ApproachZeroF(&this->unk_17EC, 1.0f, 0.01f);
    }
    this->unk_17F0 = (Math_SinS(this->unk_ABC8 * 0x2000) * 0.1f) + 1.0f;
    this->unk_17F4 = (Math_CosS(this->unk_ABC8 * 0x2000) * 0.1f) + 1.0f;
    if (this->subCamIndex != 0) {
        ShrinkWindow_SetLetterboxTarget(0x1B);
        Play_SetCameraAtEye(play, this->subCamIndex, &this->subCamAt, &this->subCamEye);
    }
}

void Boss07_Incarnation_CollisionCheck(Boss07* this, PlayState* play) {
    s32 i;
    s32 j;
    u8 damage;

    if (this->unk_15C == 0) {
        for (i = 0; i < ARRAY_COUNT(this->sphElems1); i++) {
            if (this->sph1.elements[i].info.bumperFlags & 2) {
                for (j = 0; j < ARRAY_COUNT(this->sphElems1); j++) {
                    this->sph1.elements[j].info.bumperFlags &= ~2;
                }
                if (this->unk_1804 == 10) {
                    this->unk_1806 = 0;
                }
                switch (this->actor.colChkInfo.damageEffect) {
                    case 3:
                        this->unk_1805 = 10;
                        break;
                    case 2:
                        this->unk_1805 = 1;
                        break;
                    case 4:
                        this->unk_1805 = 20;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 4);
                        break;
                    case 10:
                        this->unk_1805 = 40;
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                        break;
                    case 9:
                        this->unk_1805 = 30;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 3, 4);
                        break;
                }

                if ((this->actionFunc == Boss07_Incarnation_Stunned) ||
                    (this->actionFunc == Boss07_Incarnation_Damaged)) {
                    this->unk_15C = (this->actor.colChkInfo.damageEffect == 12) ? 15 : 5;
                    damage = this->actor.colChkInfo.damage;
                    Boss07_Incarnation_SetupDamaged(this, play, damage, this->actor.colChkInfo.damageEffect);
                    this->unk_15E = 15;
                } else {
                    this->unk_15C = 15;
                    Boss07_Incarnation_SetupStunned(this, play, 150);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_DAMAGE_OLD);
                }
                break;
            }
        }
    }
}

void Boss07_Afterimage_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    if (DECR(this->timers[0]) == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void Boss07_Incarnation_Update(Actor* thisx, PlayState* play2) {
    static u8 D_80A08198[8] = { 1, 0, 3, 0, 4, 0, 5, 0 };
    static u8 D_80A081A0[8] = { 0, 3, 0, 4, 0, 5, 0, 1 };
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;

    this->actor.hintId = 51;
    this->actionTimer++;
    Math_Vec3f_Copy(&sSfxPoint, &this->actor.projectedPos);
    if (this->unk_14A == 1) {
        s32 pad;

        Math_ApproachF(&play->envCtx.lightBlend, 1.0f, 1.0f, 0.1f);
        if (play->envCtx.lightBlend == 1.0f) {
            play->envCtx.lightBlend = 0.0f;
            this->unk_14B++;
            if (this->unk_14B >= 8) {
                this->unk_14B = 0;
            }
        }
        play->envCtx.unk_C2 = D_80A08198[this->unk_14B];
        play->envCtx.unk_C1 = D_80A081A0[this->unk_14B];
    }
    Math_ApproachF(&play->envCtx.lightBlend, 0.0f, 1.0f, 0.03f);
    if (KREG(63) == 0) {
        this->unk_174 = false;
        this->actor.shape.shadowAlpha = 130;
        for (i = 0; i < 3; i++) {
            DECR(this->timers[i]);
        }
        DECR(this->unk_15C);
        DECR(this->unk_15E);
        DECR(this->unk_158);
        DECR(this->unk_18D6);

        Math_ApproachZeroF(&this->unk_330, 1.0f, 0.04f);
        this->actionFunc(this, play);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 200.0f, 100.0f, 5);
        if (this->unk_148 || KREG(88)) {
            KREG(88) = false;
            this->unk_148 = false;
            Audio_QueueSeqCmd(NA_BGM_STOP | 0x10000);
            Boss07_Incarnation_SetupDeath(this, play);
        }
    }
    if (this->unk_158 != 0) {
        for (i = 0; i < ARRAY_COUNT(this->sphElems1); i++) {
            this->sph1.elements[i].info.bumperFlags &= ~BUMP_HIT;
        }
    }
    Boss07_Incarnation_CollisionCheck(this, play);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->sph1.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->sph1.base);
    if (this->actionFunc != Boss07_Incarnation_Pirouette) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 1, 0x1000);
    }
    if ((this->unk_18D6 != 0) && !(this->actionTimer & 1)) {
        Boss07* afterimage =
            (Boss07*)Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_BOSS_07,
                                        this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                        this->actor.world.rot.x, this->actor.world.rot.y, 7, MAJORA_AFTERIMAGE);

        if (afterimage != NULL) {
            for (i = 0; i < MAJORAS_INCARNATION_LIMB_MAX; i++) {
                afterimage->skelAnime.jointTable[i] = this->skelAnime.jointTable[i];
            }
        }
    }
    Boss07_Wrath_DamageEffects(this, play);
}

void Boss07_Afterimage_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    Boss07* sp34 = (Boss07*)this->actor.parent;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 100, 155, 900, 1099);
    SkelAnime_DrawFlexOpa(play, sp34->skelAnime.skeleton, this->skelAnime.jointTable, sp34->skelAnime.dListCount,
                          NULL, NULL, &this->actor);
    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    CLOSE_DISPS(play->state.gfxCtx);
}

s32 Boss07_Incarnation_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                        Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_INCARNATION_LIMB_EYESTALK) {
        rot->y += this->unk_17D8;
    }
    return false;
}

void Boss07_Incarnation_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static s8 sLimbColliderIndex[30] = {
        -1, -1, -1, 1, -1, 9, -1, 10, -1, -1, 5, -1, 6, -1, 1, 3, -1, 4, -1, -1, 7, -1, 8, -1, 0, -1, -1, -1, -1, -1,
    };
    static s8 sLimbPumpIndex[30] = {
        -1, -1, -1, -1, 2, -1, -1, -1, -1, 0,  -1, -1, -1, -1, 1,
        -1, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };
    static Vec3f sIncarnationColliderOffsets[11] = {
        { 2000.0f, 0.0f, 0.0f }, { 3500.0f, -1000.0f, 0.0f }, { 100000.0f, 100000.0f, 100000.0f },
        { 4000.0f, 0.0f, 0.0f }, { 4000.0f, 0.0f, 0.0f },     { 4000.0f, 0.0f, 0.0f },
        { 4000.0f, 0.0f, 0.0f }, { 4000.0f, 0.0f, 0.0f },     { 4000.0f, 0.0f, 0.0f },
        { 4000.0f, 0.0f, 0.0f }, { 4000.0f, 0.0f, 0.0f },
    };
    static s8 sLimbBodyPartIndex[32] = {
        -1, -1, -1, 1,  2,  9,  -1, 10, 11, -1, 6,  -1, 7,  8,  1, 3,
        -1, 4,  5,  -1, 12, -1, 13, 14, 0,  -1, -1, -1, -1, -1, 0, 0,
    };

    Boss07* this = THIS;
    Vec3f sp28;
    s8 i;

    if (limbIndex == MAJORAS_INCARNATION_LIMB_EYESTALK) {
        Matrix_MultZero(&this->actor.focus.pos);
    }
    i = sLimbBodyPartIndex[limbIndex];
    if (i >= 0) {
        Matrix_MultZero(&this->bodyPartsPos[i]);
    }
    i = sLimbColliderIndex[limbIndex];
    if (i >= 0) {
        if (this->unk_158 != 0) {
            Matrix_MultVecZ(100000.0f, &sp28);
        } else {
            Matrix_MultVec3f(&sIncarnationColliderOffsets[i], &sp28);
        }
        Boss07_UpdateSpheres(i, &this->sph1, &sp28);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_FOOT) {
        Matrix_MultZero(&this->unk_1788[0]);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_FOOT) {
        Matrix_MultZero(&this->unk_1788[1]);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_HAND) {
        Matrix_MultZero(&this->unk_17AC);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_HAND) {
        Matrix_MultZero(&this->unk_17A0);
    }
    i = sLimbPumpIndex[limbIndex];
    if (i >= 0) {
        Matrix_Scale(this->unk_17B8[i], this->unk_17B8[i], this->unk_17B8[i], MTXMODE_APPLY);
    }
}

void Boss07_Incarnation_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_INCARNATION_LIMB_MASK) {
        Matrix_Scale(this->unk_17F4, this->unk_17F0, 1.0f, MTXMODE_APPLY);
    }
    if ((limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_UPPER_ARM) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_FOREARM) || (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_HAND) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_FOREARM) || (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_HAND)) {
        Matrix_Scale(1.0f, this->unk_17E0, this->unk_17E0, MTXMODE_APPLY);
    }
    if ((limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_THIGH) || (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_SHIN) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_FOOT) || (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_THIGH) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_SHIN) || (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_FOOT)) {
        Matrix_Scale(1.0f, this->unk_17E4, this->unk_17E4, MTXMODE_APPLY);
    }
}

void Boss07_Incarnation_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, Boss07_Incarnation_OverrideLimbDraw,
                                   Boss07_Incarnation_PostLimbDraw, Boss07_Incarnation_TransformLimbDraw, &this->actor);
    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, 0xF, this->unk_17F8, this->unk_17FC,
                            this->unk_1800, this->unk_1804);
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Mask_SetupIdle(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Idle;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasMaskFloatingAnim, -20.0f);
    this->timers[2] = Rand_ZeroFloat(150.0f) + 60.0f;
    this->unk_1870 = 1.0f;
}

void Boss07_Mask_Idle(Boss07* this, PlayState* play) {
    s16 sp36;
    s16 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 pad;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_FLOAT_OLD - SFX_FLAG);
    if (this->timers[0] == 0) {
        if (this->timers[2] == 0) {
            if (((s8)this->actor.colChkInfo.health <= 8) && (player->transformation != PLAYER_FORM_FIERCE_DEITY) && (Rand_ZeroOne() < 0.75f)) {
                Boss07_Mask_SetupBeam(this, play);
            } else {
                Boss07_Mask_SetupSpin(this, play);
            }
        } else if (Rand_ZeroOne() < 0.15f) {
            this->unk_18C = 2.0f;
            this->timers[0] = Rand_ZeroFloat(50.0f) + 30.0f;
        } else {
            Boss07_RandVec3fXZ(&this->moveTarget, 500.0f);
            this->moveTarget.y = Rand_ZeroFloat(350.0f) + 100.0f;
            this->timers[0] = Rand_ZeroFloat(50.0f) + 20.0f;
            this->unk_170 = 0.0f;
            this->unk_18C = Rand_ZeroFloat(12.0f) + 3.0f;
        }
    }
    sp30 = this->moveTarget.x - this->actor.world.pos.x;
    sp2C = this->moveTarget.y - this->actor.world.pos.y;
    sp28 = this->moveTarget.z - this->actor.world.pos.z;
    sp34 = Math_Atan2S(sp30, sp28);
    sp36 = Math_Atan2S(sp2C, sqrtf(SQ(sp30) + SQ(sp28)));
    sp36 += (s16)(Math_SinS(this->actionTimer * 0x1388) * 4000.0f);
    Math_ApproachS(&this->actor.world.rot.y, sp34, 0xA, this->unk_170);
    Math_ApproachS(&this->actor.world.rot.x, sp36, 5, this->unk_170);
    Math_ApproachF(&this->unk_170, 2000.0f, 1.0f, 100.0f);
    Math_ApproachF(&this->actor.speedXZ, this->unk_18C, 1.0f, 1.0f);
    if (this->timers[1] != 0) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x3000);
    } else if (this->unk_18C < 7.0f) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x2000);
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 5, 0x2000);
    }
    if ((player->unk_D57 == 4) && (Rand_ZeroOne() < 0.8f)) {
        this->timers[1] = 20;
    }
    Math_ApproachS(&this->actor.shape.rot.x, 0, 0xA, 0x200);
    Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x400);
    if (this->unk_148 || KREG(88)) {
        KREG(88) = false;
        this->unk_148 = false;
        Audio_QueueSeqCmd(NA_BGM_STOP | 0x10000);
        Boss07_Mask_SetupDeath(this, play);
    }
}

void Boss07_Mask_SetupSpin(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Spin;
    this->actionState = MAJORAS_MASK_SPIN_STATE_0;
    this->csState = 0;
    this->timers[0] = 30;
    this->unk_18D4 = 0;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_ATTACK_OLD);
}

void Boss07_Mask_Spin(Boss07* this, PlayState* play) {
    s16 sp36;
    s16 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    Player* player = GET_PLAYER(play);

    this->actor.shape.rot.z -= this->unk_18D4;
    switch (this->actionState) {
        case MAJORAS_MASK_SPIN_STATE_0:
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            Boss07_SmoothStop(this, 1.0f);
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 0xA, 0x100);
            Math_ApproachS(&this->unk_18D4, 0x2000, 1, 0x100);
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_SPIN_STATE_1;
                this->actor.world.rot.x = 0;
                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                this->timers[0] = 100;
                this->timers[1] = 20;
                this->unk_170 = 0.0f;
            }
            break;
        case MAJORAS_MASK_SPIN_STATE_1:
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 0xA, 0x400);
            Math_ApproachS(&this->unk_18D4, 0x2000, 1, 0x200);
            if (this->timers[1] != 0) {
                this->moveTarget.x = player->actor.world.pos.x;
                this->moveTarget.y = player->actor.world.pos.y + 10.0f;
                this->moveTarget.z = player->actor.world.pos.z;
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_ROLLING_OLD - SFX_FLAG);
            }
            sp30 = this->moveTarget.x - this->actor.world.pos.x;
            sp2C = this->moveTarget.y - this->actor.world.pos.y;
            sp28 = this->moveTarget.z - this->actor.world.pos.z;
            sp34 = Math_Atan2S(sp30, sp28);
            sp24 = sqrtf(SQ(sp30) + SQ(sp28));
            sp36 = Math_Atan2S(sp2C, sp24);
            Math_ApproachS(&this->actor.world.rot.y, sp34, 0xA, this->unk_170);
            Math_ApproachS(&this->actor.world.rot.x, sp36, 0xA, this->unk_170);
            Math_ApproachF(&this->unk_170, 3000.0f, 1.0f, 100.0f);
            Math_ApproachF(&this->actor.speedXZ, 20.0f, 1.0f, 2.0f);
            if (((this->csState == 0) && (sp24 < 100.0f)) || (this->timers[0] == 0)) {
                if (Rand_ZeroOne() < 0.25f) {
                    this->actionState = MAJORAS_MASK_SPIN_STATE_2;
                    this->timers[0] = 30;
                } else {
                    Boss07_RandVec3fXZ(&this->moveTarget, 500.0f);
                    this->moveTarget.y = Rand_ZeroFloat(100.0f) + 100.0f;
                    if (Rand_ZeroOne() < 0.3f) {
                        this->timers[1] = 20;
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_ATTACK_2ND_OLD);
                        this->csState = 1;
                    } else {
                        this->timers[1] = 0;
                        this->csState = 0;
                    }
                    this->timers[0] = 50;
                    this->unk_170 = 0.0f;
                }
            }
            break;
        case MAJORAS_MASK_SPIN_STATE_2:
            Math_ApproachS(&this->unk_18D4, 0, 1, 0x100);
            Math_ApproachS(&this->actor.world.rot.x, 0x2000, 0xA, 0x7D0);
            Boss07_SmoothStop(this, 0.5f);
            if (this->timers[0] == 0) {
                Boss07_Mask_SetupIdle(this, play);
            }
    }
}

void Boss07_Mask_SetupStunned(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Stunned;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasMaskJerkingAnim, -10.0f);
    this->timers[0] = 100;
    this->unk_170 = 0.0f;
}

void Boss07_Mask_Stunned(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_COMMON_WEAKENED - SFX_FLAG);
    Boss07_SmoothStop(this, 0.5f);
    Math_ApproachS(&this->actor.shape.rot.x, -0x1000 + 0x4B0 * Math_SinS(this->actionTimer * 0xBB8), 5, 0x800);
    Math_ApproachS(&this->actor.shape.rot.z, -0x1000 + 0x3E8 * Math_SinS(this->actionTimer * 0x9C4), 5, 0x800);
    if (this->actor.world.pos.y > 51.0f) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_FALL_OLD - SFX_FLAG);
    }
    Math_ApproachF(&this->actor.world.pos.y, 50.0f + 10.0f * Math_SinS(this->actionTimer * 0x5DC), 0.1f, this->unk_170);
    Math_ApproachF(&this->unk_170, 15.0f, 1.0f, 1.0f);

    if ((this->timers[0] > 30) || ((this->timers[0] & 2) != 0)) {
        this->unk_1884 = 1;
    }
    if (this->timers[0] == 0) {
        Boss07_Mask_SetupIdle(this, play);
        this->timers[2] = 100;
    }
}

void Boss07_Mask_SetupDamaged(Boss07* this, PlayState* play, u8 damage, Actor* arg3) {
    Player* player = GET_PLAYER(play);

    this->actionFunc = Boss07_Mask_Damaged;
    this->timers[0] = 40;
    if (damage) {
        this->actor.speedXZ = 30.0f;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
        this->unk_18D4 = 0x1500;
    } else {
        if (player->stateFlags3 & 0x200) {
            this->actor.speedXZ = 20.0f;
            this->actor.velocity.y = 20.0f;
        } else {
            this->actor.speedXZ = 13.0f;
            this->actor.velocity.y = 10.0f;
            if (arg3 != NULL) {
                this->actor.world.rot.y = arg3->world.rot.y;
            }
        }
        this->unk_18D4 = 0x1000;
    }
    this->actor.colChkInfo.health -= damage;
    if ((s8)this->actor.colChkInfo.health <= 0) {
        this->timers[0] = 30;
    }
    this->timers[1] = 30;
}

void Boss07_Mask_Damaged(Boss07* this, PlayState* play) {
    this->unk_15C = 20;
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        Boss07_SmoothStop(this, 1.0f);
        Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 1, 0x1000);
        Math_ApproachS(&this->unk_18D4, 0, 1, 0x100);
    } else {
        this->actor.shape.rot.x += 0x2000;
    }
    this->actor.shape.rot.z += this->unk_18D4;
    if ((this->timers[0] > 30) || ((this->timers[0] & 2) != 0)) {
        this->unk_1884 = 1;
    }
    if ((this->timers[0] == 15) && ((s8)this->actor.colChkInfo.health < 10)) {
        this->unk_774 = true;
    }
    if (this->timers[0] == 0) {
        Boss07_Mask_SetupIdle(this, play);
        if ((s8)this->actor.colChkInfo.health <= 0) {
            this->unk_148 = true;
            Enemy_StartFinishingBlow(play, &this->actor);
            Audio_StopSfxByPos(&this->actor.projectedPos);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEAD_OLD);
        } else {
            this->moveTarget.x = this->actor.world.pos.x;
            this->moveTarget.y = 200.0f;
            this->moveTarget.z = this->actor.world.pos.z;
            this->actor.world.rot.x = 0x3000;
            this->timers[0] = 50;
            this->timers[2] = 100;
            this->unk_18C = 6.0f;
            this->unk_170 = 0.0f;
        }
    }
}

void Boss07_Mask_ClearBeam(Boss07* this) {
    this->unk_188C = 0.0f;
    this->unk_1890 = 0.0f;
    this->unk_1894 = 0.0f;
    this->unk_1898 = 0.0f;
    this->unk_18C0 = 0.0f;
}

void Boss07_Mask_SetupBeam(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Beam;
    this->actionState = MAJORAS_MASK_BEAM_STATE_0;
    this->timers[0] = 30;
    this->unk_170 = 0.0f;
}

void Boss07_Mask_Beam(Boss07* this, PlayState* play) {
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f12;
    f32 sp180;
    f32 phi_f24;
    s16 phi_s0;
    s16 sp178;
    Vec3f sp16C;
    Vec3f sp160;
    Player* player = GET_PLAYER(play);
    CollisionPoly* sp158;
    Vec3f sp14C;
    u8 sp14B = 0;
    s32 sp144;

    this->unk_15C = 20;
    Boss07_SmoothStop(this, 0.5f);
    Math_ApproachF(&this->actor.world.pos.y, 300.0f, 0.05f, 1.0f);
    Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x400);
    if ((player->unk_730 != NULL) && (player->stateFlags1 & 0x400000)) {
        phi_f24 = (player->transformation == PLAYER_FORM_HUMAN) ? 20 : 30.0f;
    } else {
        phi_f24 = (player->transformation == PLAYER_FORM_HUMAN) ? 8.0f : 15.0f;
    }
    phi_s0 = (player->stateFlags1 & 0x400000) ? 1 : 10;
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, phi_s0, this->unk_170);
    temp_f20 = player->actor.world.pos.x - this->actor.world.pos.x;
    temp_f12 = player->actor.world.pos.y - this->actor.world.pos.y + phi_f24;
    temp_f22 = player->actor.world.pos.z - this->actor.world.pos.z;
    Math_ApproachS(&this->actor.shape.rot.x, -Math_Atan2S(temp_f12, sqrtf(SQ(temp_f20) + SQ(temp_f22))), phi_s0,
                   this->unk_170);
    Math_ApproachF(&this->unk_170, 4000.0f, 1.0f, 200.0f);
    this->unk_1874 = 1;
    switch (this->actionState) {
        case MAJORAS_MASK_BEAM_STATE_0:
            if (this->timers[0] == 25) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST1_BLOW_OLD);
            }
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_BEAM_STATE_1;
                this->timers[0] = 6;
                this->unk_1898 = 1.0f;
            }
            break;
        case MAJORAS_MASK_BEAM_STATE_1:
            Math_ApproachF(&this->unk_188C, 1.0f, 1.0f, 0.2f);
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_BEAM_STATE_2;
                this->timers[0] = 8;
            }
            break;
        case MAJORAS_MASK_BEAM_STATE_2:
            play_sound(NA_SE_EN_LAST1_BEAM_OLD - SFX_FLAG);
            Math_ApproachF(&this->unk_1890, 1.0f, 0.2f, 0.2f);
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_BEAM_STATE_3;
                this->timers[0] = 100;
            }
            break;
        case MAJORAS_MASK_BEAM_STATE_3:
        case MAJORAS_MASK_BEAM_STATE_4:
            play_sound(NA_SE_EN_LAST1_BEAM_OLD - SFX_FLAG);
        case MAJORAS_MASK_BEAM_STATE_5:
            Math_ApproachF(&this->unk_1890, 1.0f, 0.2f, 0.2f);
            temp_f20 = player->actor.world.pos.x - this->unk_189C.x;
            temp_f12 = player->actor.world.pos.y - this->unk_189C.y + 20.0f;
            temp_f22 = player->actor.world.pos.z - this->unk_189C.z;
            sp180 = sqrtf(SQ(temp_f20) + SQ(temp_f12) + SQ(temp_f22));
            Math_ApproachF(&this->unk_1894, sp180 * 0.2f, 1.0f, 7.0f);

            if (BgCheck_EntityLineTest1(&play->colCtx, &this->unk_189C, &this->unk_18A8, &sp14C, &sp158, 1, 1, 1,
                                        1, &sp144) &&
                (this->actionState != MAJORAS_MASK_BEAM_STATE_5)) {
                Vec3f sp138;
                Vec3f sp12C;
                Vec3f sp120;

                sp138.x = randPlusMinusPoint5Scaled(20.0f) + sp14C.x;
                sp138.y = randPlusMinusPoint5Scaled(20.0f) + sp14C.y;
                sp138.z = randPlusMinusPoint5Scaled(20.0f) + sp14C.z;
                sp12C.x = 0.0f;
                sp12C.y = 6.0f;
                sp12C.z = 0.0f;
                sp120.x = sp12C.x * -0.05f;
                sp120.y = sp12C.y * -0.05f;
                sp120.z = sp12C.z * -0.05f;
                Boss07_SpawnEffect(play, &sp138, &sp12C, &sp120, Rand_ZeroFloat(10.0f) + 25.0f);
                sp14B = true;
            }
            sp16C.x = player->actor.world.pos.x - this->unk_189C.x;
            sp16C.y = player->actor.world.pos.y - this->unk_189C.y + 10.0f;
            sp16C.z = player->actor.world.pos.z - this->unk_189C.z;
            Matrix_RotateXS(-this->actor.shape.rot.x, MTXMODE_NEW);
            Matrix_RotateYS(-this->actor.shape.rot.y, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp16C, &sp160);
            if ((fabsf(sp160.x) < 20.0f) && (fabsf(sp160.y) < 50.0f) && (sp160.z > 40.0f) &&
                (sp160.z <= (this->unk_1894 * 20))) {
                if (Player_HasMirrorShieldEquipped(play) && (player->transformation == PLAYER_FORM_HUMAN) &&
                    (player->stateFlags1 & 0x400000) && (FACING_ANGLE(&player->actor, &this->actor) < 0x2000) &&
                    (FACING_ANGLE(&player->actor, &this->actor) > -0x2000)) {
                    Vec3s sp118;

                    this->unk_1894 = sp180 * 0.05f;
                    Math_ApproachF(&this->unk_18C0, sp180 * 0.2f, 1.0f, 7.0f);
                    Matrix_MtxFToYXZRot(&player->shieldMf, &sp118, 0);
                    sp118.y += 0x8000;
                    sp118.x = -sp118.x;
                    if (this->actionState == MAJORAS_MASK_BEAM_STATE_3) {
                        this->actionState = MAJORAS_MASK_BEAM_STATE_4;
                        this->unk_18C4 = sp118.x;
                        this->unk_18C6 = sp118.y;
                    } else {
                        player->unk_B84 = this->actor.yawTowardsPlayer;
                        player->unk_B80 = this->unk_1898 * 0.5f;
                        sMajoraStatic->unk_1808 = 1;
                        sMajoraStatic->unk_180C = this->unk_1898 * 30.0f;
                        sMajoraStatic->unk_1810 = this->unk_18A8;
                        Math_ApproachS(&this->unk_18C4, sp118.x, 2, 0x2000);
                        Math_ApproachS(&this->unk_18C6, sp118.y, 2, 0x2000);
                        sp16C.x = this->actor.world.pos.x - this->unk_18A8.x;
                        sp16C.y = this->actor.world.pos.y - this->unk_18A8.y;
                        sp16C.z = this->actor.world.pos.z - this->unk_18A8.z;
                        sp180 = sqrtf(SQXYZ(sp16C));
                        Matrix_RotateXS(-this->unk_18C4, MTXMODE_NEW);
                        Matrix_RotateYS(-this->unk_18C6, MTXMODE_APPLY);
                        Matrix_Push();
                        Matrix_MultVec3f(&sp16C, &sp160);
                        if ((fabsf(sp160.x) < 60.0f) && (fabsf(sp160.y) < 60.0f) && (sp160.z > 40.0f) &&
                            (sp160.z <= (this->unk_18C0 * 16.666668f)) && (this->actionState != MAJORAS_MASK_BEAM_STATE_5)) {
                            s32 phi_s0_2;
                            Vec3f sp108;
                            Vec3f spFC;
                            Vec3f spF0;

                            this->unk_18D8 += 2;
                            this->unk_18C0 = sp180 * 0.062f;
                            if (this->unk_18D8 < 10) {
                                sp108.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(40.0f);
                                sp108.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(40.0f);
                                sp108.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(40.0f);
                                spFC.x = 0.0f;
                                spFC.y = 6.0f;
                                spFC.z = 0.0f;
                                spF0.x = spFC.x * -0.05f;
                                spF0.y = spFC.y * -0.05f;
                                spF0.z = spFC.z * -0.05f;
                                Boss07_SpawnEffect(play, &sp108, &spFC, &spF0, Rand_ZeroFloat(10.0f) + 25.0f);
                                this->unk_15E |= 0xA;
                            } else {
                                this->unk_15C = 50;
                                this->unk_15E = 15;
                                Audio_StopSfxByPos(&this->actor.projectedPos);
                                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DAMAGE2_OLD);
                                Boss07_Mask_SetupDamaged(this, play, 2, NULL);
                                Boss07_Mask_ClearBeam(this);
                                for (phi_s0_2 = 0; phi_s0_2 < 20; phi_s0_2++) {
                                    sp108.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(50.0f);
                                    sp108.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(50.0f);
                                    sp108.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(50.0f);
                                    spFC.x = randPlusMinusPoint5Scaled(20.0f);
                                    spFC.y = randPlusMinusPoint5Scaled(20.0f);
                                    spFC.z = randPlusMinusPoint5Scaled(20.0f);
                                    spF0.x = spFC.x * -0.05f;
                                    spF0.y = spFC.y * -0.05f;
                                    spF0.z = spFC.z * -0.05f;
                                    Boss07_SpawnEffect(play, &sp108, &spFC, &spF0, Rand_ZeroFloat(10.0f) + 25.0f);
                                }
                                if ((s8)this->actor.colChkInfo.health <= 0) {
                                    this->unk_18D6 = 200;
                                } else {
                                    this->unk_18D6 = 60;
                                }
                            }
                        }
                        Matrix_Pop();
                        for (sp178 = 0; sp178 < ARRAY_COUNT(sBossRemains); sp178++) {
                            if (sBossRemains[sp178]->actionState >= MAJORAS_REMAINS_STATE_2) {
                                continue;
                            }
                            sp16C.x = sBossRemains[sp178]->actor.world.pos.x - this->unk_18A8.x;
                            sp16C.y = sBossRemains[sp178]->actor.world.pos.y - this->unk_18A8.y;
                            sp16C.z = sBossRemains[sp178]->actor.world.pos.z - this->unk_18A8.z;
                            sp180 = sqrtf(SQXYZ(sp16C));
                            Matrix_MultVec3f(&sp16C, &sp160);
                            if ((fabsf(sp160.x) < 60.0f) && (fabsf(sp160.y) < 60.0f) && (sp160.z > 40.0f) &&
                                (sp160.z <= (this->unk_18C0 * 16.666668f)) && (this->actionState != MAJORAS_MASK_BEAM_STATE_5)) {
                                s32 pad;
                                Vec3f spE0;
                                Vec3f spD4;
                                Vec3f spC8;

                                this->unk_18D8 += 2;
                                this->unk_18C0 = sp180 * 0.062f;
                                if (this->unk_18D8 < 5) {
                                    spE0.x = sBossRemains[sp178]->actor.world.pos.x + randPlusMinusPoint5Scaled(40.0f);
                                    spE0.y = sBossRemains[sp178]->actor.world.pos.y + randPlusMinusPoint5Scaled(40.0f);
                                    spE0.z = sBossRemains[sp178]->actor.world.pos.z + randPlusMinusPoint5Scaled(40.0f);
                                    spD4.x = 0.0f;
                                    spD4.y = 6.0f;
                                    spD4.z = 0.0f;
                                    spC8.x = spD4.x * -0.05f;
                                    spC8.y = spD4.y * -0.05f;
                                    spC8.z = spD4.z * -0.05f;

                                    Boss07_SpawnEffect(play, &spE0, &spD4, &spC8, Rand_ZeroFloat(10.0f) + 25.0f);
                                    sBossRemains[sp178]->unk_15E |= 0xA;
                                } else {
                                    sBossRemains[sp178]->actionState = MAJORAS_REMAINS_STATE_2;
                                    sBossRemains[sp178]->unk_18D6 = 60;
                                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FOLLOWERS_DEAD);
                                    for (pad = 0; pad < 20; pad++) {
                                        spE0.x =
                                            sBossRemains[sp178]->actor.world.pos.x + randPlusMinusPoint5Scaled(50.0f);
                                        spE0.y =
                                            sBossRemains[sp178]->actor.world.pos.y + randPlusMinusPoint5Scaled(50.0f);
                                        spE0.z =
                                            sBossRemains[sp178]->actor.world.pos.z + randPlusMinusPoint5Scaled(50.0f);
                                        spD4.x = randPlusMinusPoint5Scaled(20.0f);
                                        spD4.y = randPlusMinusPoint5Scaled(20.0f);
                                        spD4.z = randPlusMinusPoint5Scaled(20.0f);
                                        spC8.x = spD4.x * -0.05f;
                                        spC8.y = spD4.y * -0.05f;
                                        spC8.z = spD4.z * -0.05f;
                                        Boss07_SpawnEffect(play, &spE0, &spD4, &spC8,
                                                           Rand_ZeroFloat(10.0f) + 25.0f);
                                    }
                                }
                            }
                        }
                        if (BgCheck_EntityLineTest1(&play->colCtx, &this->unk_18A8, &this->unk_18B4, &sp14C,
                                                    &sp158, 1, 1, 1, 1, &sp144) &&
                            (this->actionState != MAJORAS_MASK_BEAM_STATE_5)) {
                            Vec3f spBC;
                            Vec3f spB0;
                            Vec3f spA4;

                            sp14B = true;
                            spBC.x = randPlusMinusPoint5Scaled(20.0f) + sp14C.x;
                            spBC.y = randPlusMinusPoint5Scaled(20.0f) + sp14C.y;
                            spBC.z = randPlusMinusPoint5Scaled(20.0f) + sp14C.z;
                            spB0.x = 0.0f;
                            spB0.y = 6.0f;
                            spB0.z = 0.0f;
                            spA4.x = spB0.x * -0.05f;
                            spA4.y = spB0.y * -0.05f;
                            spA4.z = spB0.z * -0.05f;

                            Boss07_SpawnEffect(play, &spBC, &spB0, &spA4, Rand_ZeroFloat(10.0f) + 25.0f);
                        }
                    }
                } else if (!player->isBurning && (this->actionState != MAJORAS_MASK_BEAM_STATE_5)) {
                    s32 pad2;

                    func_800B8D50(play, &this->actor, 5.0f, this->actor.shape.rot.y, 0.0f, 0x10);
                    for (pad2 = 0; pad2 < 18; pad2++) {
                        player->flameTimers[pad2] = Rand_S16Offset(0, 200);
                    }
                    player->isBurning = true;
                    func_800B8E58(player, player->ageProperties->unk_92 + NA_SE_VO_LI_DEMO_DAMAGE);
                }
            }
            if (sp14B) {
                if (sp14C.y == 0.0f) {
                    temp_f20 = this->unk_18E0.x - sp14C.x;
                    temp_f22 = this->unk_18E0.z - sp14C.z;
                    func_800AE930(&play->colCtx, Effect_GetByIndex(this->effectIndex), &sp14C, 15.0f,
                                  Math_Atan2S(temp_f20, temp_f22), sp158, sp144);
                    this->unk_18EC = 1;
                }
                this->unk_18E0 = sp14C;
            }
            if (this->actionState != MAJORAS_MASK_BEAM_STATE_5) {
                if (this->timers[0] == 0) {
                    this->actionState = MAJORAS_MASK_BEAM_STATE_5;
                    this->timers[0] = 20;
                }
            } else {
                Math_ApproachZeroF(&this->unk_1898, 1.0f, 0.05f);
                if (this->timers[0] == 0) {
                    Boss07_Mask_SetupIdle(this, play);
                    this->timers[2] = 100;
                    Boss07_Mask_ClearBeam(this);
                }
            }
            break;
    }
}

void Boss07_Mask_SetupIntro(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Intro;
    this->actor.world.pos.x = 0.0f;
    this->actor.world.pos.y = 300.0f;
    this->actor.world.pos.z = -922.5f;
    this->unk_160 = KREG(75) + 150;
    func_8016566C(this->unk_160);
}

static Vec3s sIntroCamEyes[4] = {
    { 616, 402, -46 },
    { -622, 380, -86 },
    { 400, 300, 463 },
    { -400, 470, 496 },
};
static Vec3s sIntroCamAts[4] = {
    { 646, 394, -150 },
    { -648, 380, -190 },
    { 502, 321, 438 },
    { -500, 445, 468 },
};

void Boss07_Mask_Intro(Boss07* this, PlayState* play) {
    f32 sp8C = 0.0f;
    Player* player = GET_PLAYER(play);

    this->unk_ABC8++;
    SREG(90) = this->unk_160;
    this->unk_1884 = 1;
    switch (this->csState) {
        case 0:
            this->actor.world.pos.x = 0.0f;
            this->actor.world.pos.y = 277.0f;
            this->actor.world.pos.z = -922.5f;
            if (!((player->actor.world.pos.z < 700.0f) && (ActorCutscene_GetCurrentIndex() == -1))) {
                break;
            }
            Cutscene_Start(play, &play->csCtx);
            func_800B7298(play, &this->actor, 7);
            this->subCamIndex = Play_CreateSubCamera(play);
            Play_ChangeCameraStatus(play, CAM_ID_MAIN, CAM_STATUS_WAIT);
            Play_ChangeCameraStatus(play, this->subCamIndex, CAM_STATUS_ACTIVE);
            this->unk_ABC8 = 0;
            this->csState = 1;
            this->unk_160 = KREG(76) + 150;
        case 1:
            if (this->unk_ABC8 >= 20) {
                func_8019F128(NA_SE_EV_LIGHT_GATHER - SFX_FLAG);
                Math_ApproachF(&sMajoraStatic->unk_AB44, sREG(50) + 1.0f, 0.05f, sREG(51) + 0.05f);
            }
            if (this->unk_ABC8 == 35) {
                func_800B7298(play, &this->actor, 0xF);
            }
            player->actor.world.pos.x = 0.0f;
            player->actor.world.pos.z = 700.0f;
            player->actor.shape.rot.y = -0x8000;
            player->actor.world.rot.y = player->actor.shape.rot.y;
            this->subCamEye.x = 0.0f;
            this->subCamEye.y = Player_GetHeight(player) + player->actor.world.pos.y - 24.0f;
            this->subCamEye.z = player->actor.world.pos.z - 60.0f;
            this->subCamAt.x = player->actor.world.pos.x;
            this->subCamAt.y = Player_GetHeight(player) + player->actor.world.pos.y - 20.0f;
            this->subCamAt.z = player->actor.world.pos.z;
            if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
                this->subCamAt.y -= 30.0f;
            }
            if (this->unk_ABC8 == 75) {
                this->unk_ABC8 = 0;
                this->csState = 2;
                this->subCamEye.x = player->actor.world.pos.x;
                this->subCamEye.y = player->actor.world.pos.y + 20.0f;
                this->subCamEye.z = player->actor.world.pos.z - 60.0f + 120.0f;
                this->subCamAt.x = player->actor.world.pos.x;
                this->subCamAt.y = player->actor.world.pos.y + 24.0f + 5.0f;
                this->subCamAt.z = player->actor.world.pos.z;
            }
        
            break;
        case 2:
            this->unk_160 = KREG(77) + 150;
            if (this->unk_ABC8 >= 20) {
                Math_ApproachZeroF(&sMajoraStatic->unk_AB44, 1.0f, 0.05f);
            }
            if (this->unk_ABC8 == 20) {
                sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_STATE_1;
                sBossRemains[REMAINS_GYORG]->actionState = MAJORAS_REMAINS_STATE_1;
                sBossRemains[REMAINS_GOHT]->actionState = MAJORAS_REMAINS_STATE_1;
                sBossRemains[REMAINS_TWINMOLD]->actionState = MAJORAS_REMAINS_STATE_1;
            }
            if (this->unk_ABC8 == 0) {
                func_800B7298(play, &this->actor, 7);
            }
            if (this->unk_ABC8 == 120) {
                func_800B7298(play, &this->actor, 0x15);
            }
            if (this->unk_ABC8 >= 0x1FU) {
                Math_ApproachF(&this->subCamAt.y, player->actor.world.pos.y + 24.0f + 20.0f, 0.05f, this->subCamSpeedMod);
                Math_ApproachF(&this->subCamSpeedMod, 1.0f, 1.0f, 0.01f);
            }
            if (this->unk_ABC8 >= 160) {
                if (this->unk_ABC8 == 160) {
                    sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_STATE_2;
                    sBossRemains[REMAINS_GYORG]->actionState = MAJORAS_REMAINS_STATE_2;
                    sBossRemains[REMAINS_GOHT]->actionState = MAJORAS_REMAINS_STATE_2;
                    sBossRemains[REMAINS_TWINMOLD]->actionState = MAJORAS_REMAINS_STATE_2;
                }
                if (this->unk_ABC8 == 161) {
                    sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_STATE_3;
                }
                if ((this->unk_ABC8 == 180) || (this->unk_ABC8 == 200) || (this->unk_ABC8 == 220)) {
                    this->unk_ABCC++;
                    sBossRemains[this->unk_ABCC]->actionState = MAJORAS_REMAINS_STATE_3;
                }
                this->subCamEye.x = sIntroCamEyes[this->unk_ABCC].x;
                this->subCamEye.y = sIntroCamEyes[this->unk_ABCC].y;
                this->subCamEye.z = sIntroCamEyes[this->unk_ABCC].z;
                this->subCamAt.x = sIntroCamAts[this->unk_ABCC].x;
                this->subCamAt.y = sIntroCamAts[this->unk_ABCC].y;
                this->subCamAt.z = sIntroCamAts[this->unk_ABCC].z;
                if (this->unk_ABC8 == 250) {
                    this->csState = 3;
                    this->unk_ABC8 = 0;
                    this->subCamEye.x = this->actor.world.pos.x;
                    this->subCamEye.y = this->actor.world.pos.y;
                    this->subCamEye.z = 300.0f;
                    this->subCamAt.x = this->actor.world.pos.x;
                    this->subCamAt.y = this->actor.world.pos.y;
                    this->subCamAt.z = this->actor.world.pos.z;
                    Boss07_Remains_SetupFly(sBossRemains[REMAINS_ODOLWA], play);
                    Boss07_Remains_SetupFly(sBossRemains[REMAINS_GYORG], play);
                    Boss07_Remains_SetupFly(sBossRemains[REMAINS_GOHT], play);
                    Boss07_Remains_SetupFly(sBossRemains[REMAINS_TWINMOLD], play);
                    this->subCamSpeedMod = 0.0f;
                    sMajoraStatic->unk_AB44 = 0.0f;
                    Audio_QueueSeqCmd(NA_BGM_STOP | 0xA0000);
                }
            }
            break;
        case 3:
            this->unk_160 = KREG(78) + 150;
            if (this->unk_ABC8 >= 15) {
                Math_ApproachF(&this->subCamEye.z, -700.0f, 0.4f, 100.0f);
            }
            if (this->unk_ABC8 >= 55) {
                if (this->unk_ABC8 == 55) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_B_PAMET_BREAK);
                }
                this->unk_1884 = 0;
            }
            if (this->unk_ABC8 >= 75) {
                s32 i;
                Vec3f sp78 = { 0.0f, 0.0f, 0.0f };
                Vec3f sp6C = { 0.0f, -0.5f, 0.0f };
                Vec3f sp60;

                if (this->unk_ABC8 == 75) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEMO_WALL);
                }
                sp8C = 2.0f * (this->unk_ABC8 % 2);
                if ((this->unk_ABC8 % 2) != 0) {
                    this->actor.world.pos.x += 2.0f;
                } else {
                    this->actor.world.pos.x -= 2.0f;
                }
                for (i = 0; i < 3; i++) {
                    sp60.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(110.0f);
                    sp60.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(110.0f);
                    sp60.z = this->actor.world.pos.z + 10.0f;
                    EffectSsHahen_Spawn(play, &sp60, &sp78, &sp6C, 0, (Rand_ZeroOne() * 5.0f) + 10.0f, -1, 10,
                                        NULL);
                }
            }
            if (this->unk_ABC8 == 110) {
                this->csState = 4;
                this->unk_ABC8 = 0;
                this->subCamEye.x = this->actor.world.pos.x + 200.0f;
                this->subCamEye.y = this->actor.world.pos.y;
                this->subCamEye.z = this->actor.world.pos.z + 400.0f;
                player->actor.world.pos.z = 0.0f;
                func_800B7298(play, &this->actor, 1);
                this->unk_160 = KREG(74) + 200;
            }
            break;
        case 4:
            this->unk_1884 = 0;
            if (this->unk_ABC8 >= 10) {
                Math_ApproachS(&this->unk_160, KREG(72), 1, KREG(73) + 2);
                if (this->unk_ABC8 == 10) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEMO_BREAK);
                }
                SkelAnime_Update(&this->skelAnime);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_FLOAT_OLD - SFX_FLAG);
                Math_ApproachF(&this->unk_1870, 1.0f, 1.0f, 0.02f);
                Math_ApproachF(&this->actor.world.pos.z, -642.5f, 0.05f, 30.0f);
                Math_ApproachF(&this->actor.world.pos.y, 350.0f, 0.03f, 2.0f);
                if (this->unk_ABC8 == 55) {
                    TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt,
                                           Lib_SegmentedToVirtual(&gMajorasMaskTitleCardTex), 0xA0, 0xB4, 0x80, 0x28);
                }
                if (this->unk_ABC8 == 30) {
                    Audio_QueueSeqCmd(NA_BGM_MAJORAS_MASK | 0x8000);
                }
                if (this->unk_ABC8 > 100) {
                    Math_ApproachF(&this->subCamEye.x, player->actor.world.pos.x + 40.0f, 0.1f,
                                   this->subCamSpeedMod * 20.0f);
                    Math_ApproachF(&this->subCamEye.y, player->actor.world.pos.y + 10.0f, 0.1f,
                                   this->subCamSpeedMod * 20.0f);
                    Math_ApproachF(&this->subCamEye.z, player->actor.world.pos.z + 90.0f, 0.1f,
                                   this->subCamSpeedMod * 60.0f);
                    Math_ApproachF(&this->subCamSpeedMod, 1.0f, 1.0f, 0.03f);
                }
                if (this->unk_ABC8 == 175) {
                    Camera* sp5C = Play_GetCamera(play, 0);

                    this->csState = 0;
                    Boss07_Mask_SetupIdle(this, play);
                    this->timers[0] = 50;
                    this->timers[2] = 200;
                    this->unk_1888 = 50;
                    this->moveTarget.x = 0.0f;
                    this->moveTarget.y = 200.0f;
                    this->moveTarget.z = 0.0f;
                    this->unk_170 = 0.0f;
                    sp5C->eye = this->subCamEye;
                    sp5C->eyeNext = this->subCamEye;
                    sp5C->at = this->subCamAt;
                    func_80169AFC(play, this->subCamIndex, 0);
                    this->subCamIndex = 0;
                    Cutscene_End(play, &play->csCtx);
                    func_800B7298(play, &this->actor, 6);
                    this->actor.flags |= 1;
                    gSaveContext.eventInf[6] |= 2;
                    func_80165690();
                }
            } else if ((this->unk_ABC8 % 2) != 0) {
                this->actor.world.pos.x += 2.0f;
            } else {
                this->actor.world.pos.x -= 2.0f;
            }
            Math_ApproachF(&this->subCamAt.x, this->actor.world.pos.x, 0.05f, 10.0f);
            Math_ApproachF(&this->subCamAt.y, this->actor.world.pos.y, 0.05f, 10.0f);
            Math_ApproachF(&this->subCamAt.z, this->actor.world.pos.z, 0.05f, 10.0f);
            break;
    }
    if (this->subCamIndex != 0) {
        Vec3f sp50;

        ShrinkWindow_SetLetterboxTarget(0x1B);
        sp50.x = this->subCamAt.x;
        sp50.y = this->subCamAt.y + sp8C;
        sp50.z = this->subCamAt.z;
        Play_SetCameraAtEye(play, this->subCamIndex, &sp50, &this->subCamEye);
    }
}

void Boss07_Mask_SetupDeath(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Death;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasMaskJerkingAnim, -10.0f);
    this->actor.world.rot.y = this->actor.shape.rot.y =
        Math_Acot2F(-this->actor.world.pos.z, -this->actor.world.pos.x) * (0x8000 / M_PI);
    this->csState = 0;
    this->unk_ABC8 = 0;
    this->actor.flags &= ~1;
    this->unk_15C = 20;
}

void Boss07_Mask_Death(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp60;
    Vec3f sp54;

    this->unk_ABC8++;
    this->unk_15C = 20;
    this->unk_1884 = 1;
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 0.5f);
    Math_ApproachF(&this->actor.world.pos.x, 0.0f, 0.05f, 5.0f);
    Math_ApproachF(&this->actor.world.pos.z, 0.0f, 0.05f, 5.0f);
    Math_ApproachF(&this->actor.world.pos.y, 130.0f, 0.05f, 3.0f);
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    switch (this->csState) {
        case 0:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                Cutscene_Start(play, &play->csCtx);
                func_800B7298(play, &this->actor, 1U);
                this->subCamIndex = Play_CreateSubCamera(play);
                Play_ChangeCameraStatus(play, 0, 1);
                Play_ChangeCameraStatus(play, this->subCamIndex, 7);
                this->unk_ABC8 = 0;
                this->csState = 1;
                this->subCamNextAt.z = 0.0f;
                this->unk_18D6 = 120;
                func_8016566C(150);
                this->subCamNextEye.x = 0.0f;
                this->subCamNextEye.y = -30.0f;
                this->subCamNextEye.z = 270.0f;
                this->subCamNextAt.x = 0.0f;
                this->subCamNextAt.y = -30.0f;
                Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
                Matrix_MultVec3f(&this->subCamNextAt, &this->subCamAt);
            } else {
                break;
            }
        case 1:
            player->actor.world.pos.x = 0.0f;
            player->actor.world.pos.z = BREG(87) + 250.0f;
            player->actor.world.rot.y = player->actor.shape.rot.y = -0x8000;

            this->unk_1874 = 2;
            if (this->unk_ABC8 > 60) {
                Math_ApproachS(&this->actor.shape.rot.x, 0, 0xA, 0x200);
                Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x200);
                Math_ApproachZeroF(&this->unk_1870, 1.0f, 0.01f);
            } else {
                this->actor.shape.rot.x += 0x1000;
                this->actor.shape.rot.z += 0x1200;
                Math_ApproachZeroF(&this->unk_1870, 1.0f, 0.005f);
            }
            if (this->unk_ABC8 > 130) {
                this->csState = 2;
            } else {
                break;
            }
        case 2:
            Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, 0.0f, 0.0f, 0.0f, 0, this->actor.shape.rot.y,
                        this->subCamIndex, MAJORA_INCARNATION);
            Actor_MarkForDeath(&this->actor);
            break;
    }

    Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
    Matrix_MultVec3f(&this->subCamNextAt, &sp60);
    Math_ApproachF(&this->subCamAt.x, sp60.x, 0.1f, 10.0f);
    Math_ApproachF(&this->subCamAt.y, sp60.y, 0.1f, 10.0f);
    Math_ApproachF(&this->subCamAt.z, sp60.z, 0.1f, 10.0f);
    if (this->subCamIndex != 0) {
        ShrinkWindow_SetLetterboxTarget(0x1B);
        sp54 = this->subCamEye;
        if (sp54.y < 30.0f) {
            sp54.y = 30.0f;
        }
        Play_SetCameraAtEye(play, this->subCamIndex, &this->subCamAt, &sp54);
    }
}

void Boss07_Mask_CollisionCheck(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    ColliderInfo* hitbox;
    u8 damage;
    Actor* hitActor;

    if (this->unk_15C == 0) {
        if (this->quad1.base.acFlags & AC_HIT) {
            this->quad1.base.acFlags &= ~AC_HIT;
            this->unk_186C = 7;
        }
        if (this->quad2.base.acFlags & AC_HIT) {
            this->quad2.base.acFlags &= ~AC_HIT;
            this->unk_186C = 15;
            if ((this->actionFunc == Boss07_Mask_Stunned) || (player->stateFlags3 & 0x200)) {
                hitActor = this->quad2.base.ac;
                hitbox = this->quad2.info.acHitInfo;
                damage = (hitbox->toucher.dmgFlags & 0xF7CFFFFF) ? this->actor.colChkInfo.damage : 0;
                this->unk_15C = 50;
                this->unk_15E = 15;
                Audio_StopSfxByPos(&this->actor.projectedPos);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DAMAGE2_OLD);
                Boss07_Mask_SetupDamaged(this, play, damage, hitActor);
            } else {
                this->unk_15C = 15;
                Audio_StopSfxByPos(&this->actor.projectedPos);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DAMAGE1_OLD);
                Boss07_Mask_SetupStunned(this, play);
            }
        }
    }
}

void Boss07_Mask_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;
    Player* player = GET_PLAYER(play);
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    f32 sp68;

    this->actor.hintId = 50;
    if (sMusicStartTimer != 0) {
        sMusicStartTimer--;
        if (sMusicStartTimer == 0) {
            Audio_QueueSeqCmd(NA_BGM_MAJORAS_MASK | 0x8000);
        }
    }
    Math_Vec3f_Copy(&sSfxPoint, &this->actor.projectedPos);
    if ((sMajoraStatic == NULL) || (sMajoraStatic->subCamIndex == 0)) {
        this->unk_149 = true;
        play->envCtx.unk_C1 = 2;
        play->envCtx.unk_C2 = 0;
        Math_ApproachF(&play->envCtx.lightBlend, this->unk_1898, 1.0f, 0.1f);
        this->actionTimer++;
        if (KREG(63) == 0) {
            this->unk_174 = false;
            this->unk_1884 = 0;
            this->unk_1874 = 0;
            Actor_SetScale(&this->actor, 0.1f);
            this->actor.focus.pos = this->actor.world.pos;
            for (i = 0; i < 3; i++) {
                DECR(this->timers[i]);
            }
            DECR(this->unk_186C);
            DECR(this->unk_15C);
            DECR(this->unk_15E);
            DECR(this->unk_18D6);
            DECR(this->unk_18D8);

            this->unk_18EC = 0;
            this->actionFunc(this, play);
            if ((this->unk_18EC == 0) && (this->unk_18ED != 0)) {
                func_800AEF44(Effect_GetByIndex(this->effectIndex));
            }
            this->unk_18ED = this->unk_18EC;
            if (this->actionFunc != Boss07_Mask_Intro) {
                if (this->actionFunc != Boss07_Mask_Damaged) {
                    Actor_UpdateVelocityWithoutGravity(&this->actor);
                    Actor_UpdatePos(&this->actor);
                } else {
                    if (this->actor.bgCheckFlags & 1) {
                        this->actor.velocity.y = 0.0f;
                    }
                    Actor_MoveWithGravity(&this->actor);
                }
                if (this->unk_1888 == 0) {
                    Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 60.0f, 100.0f, 5);
                } else {
                    this->unk_1888--;
                }
            }
        } else {
            this->actor.colChkInfo.health = 0;
        }
        Boss07_Mask_CollisionCheck(this, play);
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
        sp6C.x = -55.0f;
        sp6C.y = 55.0f;
        sp6C.z = 10.0f;
        Matrix_MultVec3f(&sp6C, &sp9C);
        sp6C.x = -55.0f;
        sp6C.y = -55.0f;
        Matrix_MultVec3f(&sp6C, &sp90);
        sp6C.x = 55.0f;
        sp6C.y = 55.0f;
        Matrix_MultVec3f(&sp6C, &sp84);
        sp6C.x = 55.0f;
        sp6C.y = -55.0f;
        Matrix_MultVec3f(&sp6C, &sp78);
        Collider_SetQuadVertices(&this->quad1, &sp9C, &sp90, &sp84, &sp78);

        sp68 = (player->stateFlags3 & 0x200) ? 70.0f : 40.0f;
        sp6C.x = -sp68;
        sp6C.y = sp68;
        sp6C.z = -10.0f;
        Matrix_MultVec3f(&sp6C, &sp9C);
        sp6C.x = -sp68;
        sp6C.y = -sp68;
        Matrix_MultVec3f(&sp6C, &sp90);
        sp6C.x = sp68;
        sp6C.y = sp68;
        Matrix_MultVec3f(&sp6C, &sp84);
        sp6C.x = sp68;
        sp6C.y = -sp68;
        Matrix_MultVec3f(&sp6C, &sp78);
        Collider_SetQuadVertices(&this->quad2, &sp9C, &sp90, &sp84, &sp78);

        if (player->stateFlags3 & 0x200) {
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->quad2.base);
        } else {
            if ((this->actionFunc != Boss07_Mask_Stunned) && (this->actionFunc != Boss07_Mask_Damaged)) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->quad1.base);
            }
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->quad2.base);
            if (this->actionFunc == Boss07_Mask_Spin) {
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->quad1.base);
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->quad2.base);
            }
        }
        if (this->unk_18D6 != 0) {
            Vec3f sp5C;
            Vec3f sp50;
            Vec3f sp44;
            f32 sp40 = (this->actionFunc == Boss07_Mask_Death) ? 130.0f : 80.0f;

            sp5C.x = randPlusMinusPoint5Scaled(sp40) + this->actor.world.pos.x;
            sp5C.y = randPlusMinusPoint5Scaled(sp40) + this->actor.world.pos.y;
            sp5C.z = randPlusMinusPoint5Scaled(sp40) + this->actor.world.pos.z;
            sp50.x = 0.0f;
            sp50.y = 5.0f;
            sp50.z = 0.0f;
            sp44.x = sp50.x * -0.05f;
            sp44.y = sp50.y * -0.05f;
            sp44.z = sp50.z * -0.05f;
            Boss07_SpawnEffect(play, &sp5C, &sp50, &sp44, Rand_ZeroFloat(10.0f) + 25.0f);
            Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EV_BURN_OUT - SFX_FLAG);
        }
    }
}

void Boss07_Mask_UpdateTentacles(Boss07* this, PlayState* play, Vec3f* base, Vec3f* pos, Vec3f* rot,
                                 Vec3f* pull, Vec3f* arg6, f32 arg7, u8 arg8, f32 arg9) {
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 phi_f0;
    f32 phi_f2;
    f32 temp_f26;
    s32 i;
    f32 temp1;
    f32 temp2;
    Vec3f sp98 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp8C;
    Vec3f sp80;
    Vec3f* sp7C = pull;

    if (this->unk_1874 != 0) {
        for (i = 0; i < MAJORA_TENT_LENGTH; i++) {
            Matrix_Push();
            Matrix_RotateZF(arg9, MTXMODE_APPLY);
            sp98.x = Math_SinS((2 * i + this->actionTimer) * 0x1600) * 10;
            sp98.y = 10.0f;
            sp98.z = 0.0f;
            Matrix_MultVec3f(&sp98, &sp8C);
            pos[i].x += sp8C.x;
            pos[i].y += sp8C.y;
            pos[i].z += sp8C.z;
            Matrix_Pop();
        }
    }
    for (i = 0; i < MAJORA_TENT_LENGTH; i++, pull++) {
        if (i == 0) {
            pos[0] = *base;
        } else {
            Math_ApproachF(&pull->x, 0.0f, 1.0f, 1.0f);
            Math_ApproachF(&pull->y, 0.0f, 1.0f, 1.0f);
            Math_ApproachF(&pull->z, 0.0f, 1.0f, 1.0f);
        }
    }

    pos++;
    rot++;
    pull = sp7C + 1;
    sp98.x = sp98.y = 0.0f;
    sp98.z = arg7 * 23.0f;
    for (i = 1; i < MAJORA_TENT_LENGTH; i++, pull++, pos++, rot++) {
        if (i < MAJORA_TENT_LENGTH / 2) {
            sp80.x = arg6->x * (MAJORA_TENT_LENGTH / 2 - i) * 0.2f;
            sp80.y = arg6->y * (MAJORA_TENT_LENGTH / 2 - i) * 0.2f;
            sp80.z = arg6->z * (MAJORA_TENT_LENGTH / 2 - i) * 0.2f;
        } else {
            sp80 = gZeroVec3f;
        }
        temp_f24 = pos->x + pull->x - (pos - 1)->x + sp80.x;
        if (this->unk_1874 != 0) {
            phi_f0 = 0.0f;
        } else if ((arg8 != 0) && ((this->actor.world.pos.y - 30.0f) < (pos - 1)->y)) {
            phi_f0 = -30.0f;
        } else {
            phi_f0 = -3.0f - ((s32)(i % 8U) * 0.05f);
        }
        phi_f2 = pos->y + pull->y + phi_f0 + sp80.y;
        if (phi_f2 < 2.0f) {
            phi_f2 = 2.0f;
        }
        temp_f22 = phi_f2 - (pos - 1)->y;
        temp_f20 = pos->z + pull->z - (pos - 1)->z + sp80.x;
        temp_f26 = Math_Acot2F(temp_f20, temp_f24);
        temp2 = sqrtf(SQ(temp_f24) + SQ(temp_f20));
        temp1 = -Math_Acot2F(temp2, temp_f22);
        (rot - 1)->y = temp_f26;
        (rot - 1)->x = temp1;
        Matrix_RotateYF(temp_f26, MTXMODE_NEW);
        Matrix_RotateXFApply(temp1);
        Matrix_MultVecZ(sp98.z, &sp8C);
        temp_f24 = pos->x;
        temp_f22 = pos->y;
        temp_f20 = pos->z;
        pos->x = (pos - 1)->x + sp8C.x;
        pos->y = (pos - 1)->y + sp8C.y;
        pos->z = (pos - 1)->z + sp8C.z;
        pull->x = (pos->x - temp_f24) * 0.85f;
        pull->y = (pos->y - temp_f22) * 0.85f;
        pull->z = (pos->z - temp_f20) * 0.85f;
    }
}

void Boss07_Mask_DrawTentacles(Boss07* this, PlayState* play, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5) {
    s32 i;
    f32 phi_f12;

    OPEN_DISPS(play->state.gfxCtx);
    for (i = 0; i < MAJORA_TENT_LENGTH - 1; i++, arg2++, arg3++) {
        Matrix_Translate(arg2->x, arg2->y, arg2->z, MTXMODE_NEW);
        Matrix_RotateYF(arg3->y, MTXMODE_APPLY);
        Matrix_RotateXFApply(arg3->x);
        Matrix_RotateZF(arg5, MTXMODE_APPLY);
        if (i <= (MAJORA_TENT_LENGTH - 1) / 2) {
            phi_f12 = 0.035f;
        } else {
            phi_f12 = 0.035f - (i - (MAJORA_TENT_LENGTH - 1) / 2) * 60.0f * 0.0001f;
        }
        Matrix_Scale(phi_f12, phi_f12, arg4 * 0.01f * 2.3f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gMajorasMaskTentacleModelDL);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Mask_DrawBeam(Boss07* this, PlayState* play) {
    s32 pad[4];

    OPEN_DISPS(play->state.gfxCtx);
    if (this->actionFunc == Boss07_Mask_Beam) {
        gSPSegment(POLY_XLU_DISP++, 12,
                   Gfx_TexScroll(play->state.gfxCtx, 0, (this->actionTimer * -15) % 0x100U, 0x20, 0x40));
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 60, 200);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 128);
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_Push();
        Matrix_Push();
        Matrix_Push();

        Matrix_Translate(250.0f, 0.0f, 200.0f, MTXMODE_APPLY);
        Matrix_RotateYS(-0xA00, MTXMODE_APPLY);
        Matrix_Scale(this->unk_1898 * 0.05f, this->unk_1898 * 0.05f, this->unk_188C * 0.05f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);
        Matrix_Pop();

        Matrix_Translate(-250.0f, 0.0f, 200.0f, MTXMODE_APPLY);
        Matrix_RotateYS(0xA00, MTXMODE_APPLY);
        Matrix_Scale(this->unk_1898 * 0.05f, this->unk_1898 * 0.05f, this->unk_188C * 0.05f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
        Matrix_Pop();

        Matrix_Translate(0.0f, 0.0f, 1200.0f, MTXMODE_APPLY);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(this->unk_1890 * 40.0f * this->unk_1898, this->unk_1890 * 40.0f * this->unk_1898, 0.0f,
                     MTXMODE_APPLY);
        Matrix_RotateZS(this->actionTimer * 0x100, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 60, sREG(89) + 80);
        Matrix_Scale(6.0f, 6.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateZS(0x4000, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 60, 200);
        Matrix_Pop();

        Matrix_Translate(0.0f, 0.0f, 1150.0f, MTXMODE_APPLY);
        Matrix_MultZero(&this->unk_189C);
        Matrix_Scale(this->unk_1898 * 0.05f, this->unk_1898 * 0.05f, (this->unk_1894 * 0.01f) - 0.01f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);
        Matrix_MultVecZ(20100.0f, &this->unk_18A8);
        if (this->unk_18C0 > 0.0f) {
            Vec3f sp50;

            Matrix_MultVecZ(20000.0f, &sp50);
            Matrix_Translate(this->unk_18A8.x, this->unk_18A8.y, this->unk_18A8.z, MTXMODE_NEW);
            Matrix_RotateYS(this->unk_18C6, MTXMODE_APPLY);
            Matrix_RotateXS(this->unk_18C4, MTXMODE_APPLY);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_Scale(this->unk_1898 * 0.05f, this->unk_1898 * 0.05f, this->unk_18C0 * 0.01f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);

            Matrix_MultVecZ(20100.0f, &this->unk_18B4);
            Matrix_Translate(sp50.x, sp50.y, sp50.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(this->unk_1898 * 5.0f, this->unk_1898 * 5.0f, 0.0f, MTXMODE_APPLY);
            Matrix_RotateZS(this->actionTimer * 0x100, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
            gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
        }
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Mask_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_MASK_LIMB_FACE) {
        Matrix_MultVecX(500.0f, &this->unk_1878);
    }
}

void Boss07_Mask_Draw(Actor* thisx, PlayState* play2) {
    static void* D_80A082E0[2] = { gMajorasMaskWithNormalEyesTex, gMajorasMaskWithDullEyesTex };
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;
    s32 phi_s6;
    f32 temp_f20;
    f32 temp_f22;
    f32 phi_f24;

    OPEN_DISPS(play->state.gfxCtx);
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    f32 pad2;

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    temp_f20 = this->unk_186C * (M_PI / 4.0f) * 0.06666667f;
    temp_f22 = Math_SinS(this->unk_186C * 0x3500) * temp_f20 * 0.5f;
    Matrix_RotateYF(Math_SinS(this->unk_186C * 0x4500) * temp_f20, MTXMODE_APPLY);
    Matrix_RotateXFApply(temp_f22);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    gSPSegment(POLY_OPA_DISP++, 8, Lib_SegmentedToVirtual(D_80A082E0[this->unk_1884]));
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, Boss07_Mask_PostLimbDraw,
                      &this->actor);
    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasMaskTentacleMaterialDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 155, 155, 80, 255);

    phi_s6 = ((this->actionFunc == Boss07_Mask_Idle) &&
              (ABS_ALT((s16)(this->actor.world.rot.y - this->actor.shape.rot.y)) > 0x4000))
                 ? 1
                 : 0;

    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_MultVecZ(-3.0f, &sp90);
    spA8.x = 0.0f;
    spA8.y = 20.0f;
    spA8.z = -2.0f;
    phi_f24 = 0.0f;
    for (i = 0; i < MAJORA_TENT_COUNT; i++) {
        Matrix_Push();
        Matrix_Push();
        Matrix_RotateZF(phi_f24, MTXMODE_APPLY);
        Matrix_MultVec3f(&spA8, &sp9C);
        this->tentacles[i].base.x = this->unk_1878.x + sp9C.x;
        this->tentacles[i].base.y = this->unk_1878.y + sp9C.y;
        this->tentacles[i].base.z = this->unk_1878.z + sp9C.z;

        pad2 = (1 - (i * 0.008f)) * this->unk_1870;
        Matrix_Pop();
        if (this->unk_149) {
            Boss07_Mask_UpdateTentacles(this, play, &this->tentacles[i].base, this->tentacles[i].pos,
                                        this->tentacles[i].rot, this->tentacles[i].pull, &sp90, pad2, phi_s6, phi_f24);
        }
        Boss07_Mask_DrawTentacles(this, play, this->tentacles[i].pos, this->tentacles[i].rot, pad2, i * 0.9f);
        phi_f24 += 0.5f;
        spA8.y += 1.0f;

        Matrix_Pop();
    }
    Boss07_Mask_DrawBeam(this, play);
    this->unk_149 = false;
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Projectile_Update(Actor* thisx, PlayState* play2) {
    s32 i;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    PlayState* play = play2;
    Boss07* this = THIS;
    f32 pad;
    Player* player = GET_PLAYER(play);

    this->actionTimer++;
    if (this->actor.params == MAJORA_REMAINS_SHOT) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FOLLOWERS_BEAM - SFX_FLAG);
    }
    if (KREG(63) == 0) {
        Actor_SetScale(&this->actor, 3.5f);
        if (this->actionState == MAJORAS_PROJECTILE_STATE_0) {
            sp58 = player->actor.world.pos.x - this->actor.world.pos.x;
            sp54 = player->actor.world.pos.y - this->actor.world.pos.y + 20.0f;
            sp50 = player->actor.world.pos.z - this->actor.world.pos.z;

            this->actor.world.rot.y = Math_Atan2S(sp58, sp50);
            pad = sqrtf(SQ(sp58) + SQ(sp50));
            this->actor.world.rot.x = Math_Atan2S(sp54, pad);
            this->actionState = MAJORAS_PROJECTILE_STATE_1;
            this->actor.speedXZ = 30.0f;
            func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_ENEMY);
            if (this->actor.params == MAJORA_INCARNATION_SHOT) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_FIRE_OLD);
            }
        }
        for (i = 0; i < 3; i++) {
            DECR(this->timers[i]);
        }
        Actor_UpdateVelocityWithoutGravity(&this->actor);
        Actor_UpdatePos(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 31.0f, 100.0f, 7);
        this->actor.shape.rot.z += 0x1200;
        if ((this->actor.bgCheckFlags & 0x19) || (this->cyl2.base.atFlags & 2) || (this->cyl2.base.atFlags & 2) ||
            sKillProjectiles) {
            Actor_MarkForDeath(&this->actor);
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, this->unk_181C,
                        CLEAR_TAG_SMALL_LIGHT_RAYS);
        }
        Collider_UpdateCylinder(&this->actor, &this->cyl2);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->cyl2.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->cyl2.base);
    }
}

void Boss07_Projectile_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, sColorsWhite[this->unk_181C][0], sColorsWhite[this->unk_181C][1],
                    sColorsWhite[this->unk_181C][2], 255);
    gDPSetEnvColor(POLY_XLU_DISP++, sColorsYRGB[this->unk_181C][0], sColorsYRGB[this->unk_181C][1],
                   sColorsYRGB[this->unk_181C][2], 128);
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, 0.0f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
    gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Remains_CollisionCheck(Boss07* this, PlayState* play) {
    Vec3f sp2C;
    ColliderInfo* hitbox;

    if ((this->unk_15C == 0) && (this->cyl2.base.acFlags & 2)) {
        this->cyl2.base.acFlags &= ~2;
        this->unk_15C = 15;
        hitbox = this->cyl2.info.acHitInfo;
        if (hitbox->toucher.dmgFlags & 0x80) {
            Boss07_Remains_SetupStunned(this, play);
        } else {
            u8 damage = this->actor.colChkInfo.damage;

            this->actor.colChkInfo.health -= damage;
            this->unk_15E = 15;
            this->actionFunc = Boss07_Remains_Fly;
            if ((s8)this->actor.colChkInfo.health <= 0) {
                this->actionState = MAJORAS_REMAINS_STATE_2;
                this->unk_18DA = 1;
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FOLLOWERS_DEAD);
            } else {
                this->actionState = MAJORAS_REMAINS_STATE_10;
                this->timers[0] = 0xF;
                Boss07_Remains_DamageSfx(this);
            }
            Matrix_RotateYS(this->actor.yawTowardsPlayer, MTXMODE_NEW);
            Matrix_MultVecZ(-20.0f, &sp2C);
            this->unk_18CC = sp2C.x;
            this->unk_18D0 = sp2C.z;
        }
    }
}

void Boss07_Remains_SetupIntro(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Remains_Intro;
}

void Boss07_Remains_Intro(Boss07* this, PlayState* play) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 phi_f2;
    s32 pad;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    Player* player = GET_PLAYER(play);

    switch (this->actionState) {
        case 0:
            Actor_SetScale(&this->actor, 0.0f);
            this->actor.world.pos.x = player->actor.world.pos.x;
            this->actor.world.pos.y = player->actor.world.pos.y + 30.0f;
            this->actor.world.pos.z = player->actor.world.pos.z;
            if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
                this->actor.world.pos.y += 30.0f + KREG(48);
            }
            this->moveTarget.x = sRemainsStart[this->actor.params - MAJORA_REMAINS].x + player->actor.world.pos.x;
            this->moveTarget.y = sRemainsStart[this->actor.params - MAJORA_REMAINS].y + player->actor.world.pos.y;
            this->moveTarget.z = sRemainsStart[this->actor.params - MAJORA_REMAINS].z + player->actor.world.pos.z;
            sp54 = this->moveTarget.x - this->actor.world.pos.x;
            sp50 = this->moveTarget.y - this->actor.world.pos.y;
            sp4C = this->moveTarget.z - this->actor.world.pos.z;
            this->actor.world.rot.y = Math_Atan2S(sp54, sp4C);
            this->actor.world.rot.x = Math_Atan2S(sp50, sqrtf(SQ(sp54) + SQ(sp4C)));
            this->unk_AB40 = Rand_ZeroFloat(100.0f);
            break;
        case 1:
            this->unk_ABC8++;
            this->unk_AB40++;
            this->unk_18C8 += 0x200;
            Math_ApproachF(&this->unk_188C, 1.2f, 1.0f, 0.1f);
            Math_ApproachF(&this->actor.scale.x, 0.004f, 0.5f, 0.0002f);
            this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
            if (this->unk_ABC8 > 90) {
                this->moveTarget.x = sRemainsEnd[this->actor.params - MAJORA_REMAINS].x;
                this->moveTarget.y = 370.0f;
                this->moveTarget.z = sRemainsEnd[this->actor.params - MAJORA_REMAINS].z;
                sp38 = 20.0f;
                sp34 = 0.5f;
                sp40 = 4096.0f;
                sp3C = 400.0f;
                phi_f2 = 0.0f;
            } else {
                phi_f2 = Math_SinS(this->unk_AB40 * 0x300) * 20.0f;
                sp38 = 1.0f;
                sp34 = 0.1f;
                sp40 = 1500.0f;
                sp3C = 100.0f;
            }
            sp54 = this->moveTarget.x - this->actor.world.pos.x;
            sp50 = this->moveTarget.y - this->actor.world.pos.y + phi_f2;
            sp4C = this->moveTarget.z - this->actor.world.pos.z;
            sp30 = Math_Atan2S(sp54, sp4C);
            sp32 = Math_Atan2S(sp50, sqrtf(SQ(sp54) + SQ(sp4C)));
            Math_ApproachS(&this->actor.world.rot.y, sp30, 5, this->unk_170);
            Math_ApproachS(&this->actor.world.rot.x, sp32, 5, this->unk_170);
            Math_ApproachF(&this->unk_170, sp40, 1.0f, sp3C);
            Math_ApproachF(&this->actor.speedXZ, sp38, 1.0f, sp34);
            Actor_UpdateVelocityWithoutGravity(&this->actor);
            Actor_UpdatePos(&this->actor);
            this->actor.shape.rot = this->actor.world.rot;
            break;
        case 2:
            Actor_SetScale(&this->actor, 0.0f);
            this->unk_188C = 0.0f;
            this->actor.speedXZ = 0.0f;
            this->actor.world.pos.x = sRemainsEnd[this->actor.params - MAJORA_REMAINS].x * 0.6f;
            this->actor.world.pos.y = 370.0f;
            this->actor.world.pos.z = sRemainsEnd[this->actor.params - MAJORA_REMAINS].z * 0.6f;
            this->actor.shape.rot.y = sRemainsEnd[this->actor.params - MAJORA_REMAINS].y;
            this->unk_ABCC = 0;
            break;
        case 3:
            this->unk_ABCC++;
            if (this->unk_ABCC == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FOLLOWERS_STAY);
            }
            Actor_SetScale(&this->actor, 0.03f);
            Math_ApproachF(&this->actor.world.pos.x, sRemainsEnd[this->actor.params - MAJORA_REMAINS].x, 0.5f, 40.0f);
            Math_ApproachF(&this->actor.world.pos.z, sRemainsEnd[this->actor.params - MAJORA_REMAINS].z, 0.5f, 22.0f);
            break;
    }
}

void Boss07_Remains_SetupFly(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Remains_Fly;
    this->actor.gravity = -0.75f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
    Collider_InitAndSetCylinder(play, &this->cyl2, &this->actor, &sRemainsCylInit);
    this->actor.colChkInfo.health = 5;
    this->actionState = MAJORAS_REMAINS_STATE_0;
}

void Boss07_Remains_Fly(Boss07* this, PlayState* play) {
    s16 sp7E;
    s16 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    s32 pad;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;

    switch (this->actionState) {
        case MAJORAS_REMAINS_STATE_20:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MUJURA_FOLLOWERS_FLY - SFX_FLAG);
            this->timers[0] = 80;
            this->timers[2] = 100.0f + Rand_ZeroFloat(100.0f);
            this->unk_18C = 5.0f;
            this->actor.speedXZ = 5.0f;
            this->moveTarget = gZeroVec3f;
            this->actor.world.rot.y = Math_Atan2S(-this->actor.world.pos.x, -this->actor.world.pos.z);
            this->actionState = 1;
            this->unk_1888 = 100;
            this->cyl2.base.colType = 3;
            this->actor.flags |= 0x201;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEMO_BREAK);
            break;
        case MAJORAS_REMAINS_STATE_1:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MUJURA_FOLLOWERS_FLY - SFX_FLAG);
            if (this->timers[2] == 0) {
                this->unk_18DB = 1;
                this->timers[2] = Rand_ZeroFloat(200.0f) + 100.0f;
            }
            if (this->timers[0] == 0) {
                if (Rand_ZeroOne() < 0.35f) {
                    this->unk_18C = 1.0f;
                    this->timers[0] = Rand_ZeroFloat(50.0f) + 30.0f;
                } else {
                    Boss07_RandVec3fXZ(&this->moveTarget, 500.0f);
                    this->moveTarget.y = Rand_ZeroFloat(350.0f) + 100.0f;
                    this->timers[0] = Rand_ZeroFloat(50.0f) + 20.0f;
                    this->unk_170 = 0.0f;
                    this->unk_18C = Rand_ZeroFloat(5.0f) + 5.0f;
                }
            }
            sp78 = this->moveTarget.x - this->actor.world.pos.x;
            sp74 = this->moveTarget.y - this->actor.world.pos.y;
            sp70 = this->moveTarget.z - this->actor.world.pos.z;
            sp7C = Math_Atan2S(sp78, sp70);
            sp7E = Math_Atan2S(sp74, sqrtf(SQ(sp78) + SQ(sp70)));
            sp7E += (s16)(Math_SinS(this->actionTimer * 0x1388) * 4000.0f);
            Math_ApproachS(&this->actor.world.rot.y, sp7C, 0xA, this->unk_170);
            Math_ApproachS(&this->actor.world.rot.x, sp7E, 5, this->unk_170);
            Math_ApproachF(&this->unk_170, 2000.0f, 1.0f, 100.0f);
            Math_ApproachF(&this->actor.speedXZ, this->unk_18C, 1.0f, 1.0f);
            if ((this->unk_18C < 8.0f) && (Play_InCsMode(play) == 0)) {
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            } else {
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 0xA, 0x1000);
            }
            Actor_UpdateVelocityWithoutGravity(&this->actor);
            Actor_UpdatePos(&this->actor);
            if (this->unk_1888 == 0) {
                Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 100.0f, 100.0f, 5);
            } else {
                this->unk_1888--;
            }
            Boss07_Remains_CollisionCheck(this, play);
            break;
        case MAJORAS_REMAINS_STATE_2:
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 1, 0x500);
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 100.0f, 100.0f, 5);
            if (this->actor.bgCheckFlags & 1) {
                if (this->unk_18DA != 0) {
                    this->unk_18D6 |= 4;
                }
                Math_ApproachF(&this->actor.scale.z, 0.0f, 1.0f, 0.001f);
                if (this->actor.scale.z == 0.0f) {
                    this->actionState = 3;
                    this->actor.draw = NULL;
                    this->actor.flags &= ~1;
                }
                Boss07_SmoothStop(this, 2.0f);
            } else {
                this->actor.shape.rot.z += 0x200;
            }
            break;
        case MAJORAS_REMAINS_STATE_10:
            Actor_MoveWithGravity(&this->actor);
            this->actor.world.pos.y -= 50.0f;
            this->actor.prevPos.y -= 50.0f;
            Actor_UpdateBgCheckInfo(play, &this->actor, 35.0f, 60.0f, 60.0f, 5);
            this->actor.world.pos.y += 50.0f;
            this->actor.prevPos.y += 50.0f;
            if (this->timers[0] == 0) {
                this->actionState = 1;
            }
            break;
        case MAJORAS_REMAINS_STATE_0:
            break;
    }
    if (this->actionState < MAJORAS_REMAINS_STATE_2) {
        Collider_UpdateCylinder(&this->actor, &this->cyl2);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->cyl2.base);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->cyl2.base);
    }
    if (this->unk_18DB != 0) {
        this->unk_18DB = 0;
        if ((Boss07_IsFacingPlayer(this, play) != 0) && (sMajorasMask->actionFunc != Boss07_Mask_Beam)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, MAJORA_REMAINS_SHOT);
        }
    }
    if (this->unk_18D6 != 0) {
        sp60.x = randPlusMinusPoint5Scaled(80.0f) + this->actor.world.pos.x;
        sp60.z = randPlusMinusPoint5Scaled(80.0f) + this->actor.world.pos.z;
        if (this->unk_18DA != 0) {
            sp48.x = sp48.z = 0.0f;
            sp48.y = 0.03f;
            sp60.y = Rand_ZeroFloat(10.0f) + this->actor.world.pos.y;
            EffectSsKFire_Spawn(play, &sp60, &gZeroVec3f, &sp48, Rand_ZeroFloat(30.0f) + 30.0f, 0);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        } else {
            sp60.y = (Rand_ZeroFloat(30.0f) + this->actor.world.pos.y) - 15.0f;
            sp54.x = 0.0f;
            sp54.y = 5.0f;
            sp54.z = 0.0f;
            sp48.x = sp54.x * -0.05f;
            sp48.y = sp54.y * -0.05f;
            sp48.z = sp54.z * -0.05f;
            Boss07_SpawnEffect(play, &sp60, &sp54, &sp48, Rand_ZeroFloat(10.0f) + 25.0f);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
        }
    }
}

void Boss07_Remains_SetupStunned(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Remains_Stunned;
    this->timers[0] = 50;
    this->actor.speedXZ = 0.0f;
}

void Boss07_Remains_Stunned(Boss07* this, PlayState* play) {
    Boss07_Remains_CollisionCheck(this, play);
    Collider_UpdateCylinder(&this->actor, &this->cyl2);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->cyl2.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->cyl2.base);
    if (this->timers[0] == 0) {
        this->actionFunc = Boss07_Remains_Fly;
        this->actionState = MAJORAS_REMAINS_STATE_1;
    }
}

void Boss07_Remains_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;

    this->actionTimer++;
    for (i = 0; i < 3; i++) {
        DECR(this->timers[i]);
    }
    DECR(this->unk_18D6);
    DECR(this->unk_15C);
    DECR(this->unk_15E);
    this->actionFunc(this, play);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.world.pos.x += this->unk_18CC;
    this->actor.world.pos.z += this->unk_18D0;
    Math_ApproachZeroF(&this->unk_18CC, 1.0f, 1.0f);
    Math_ApproachZeroF(&this->unk_18D0, 1.0f, 1.0f);
}

void Boss07_Remains_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    f32 sp64;
    f32 sp60;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    sp64 = this->unk_15C * (M_PI / 4.0f) * 0.06666667f;
    sp60 = Math_SinS(this->unk_15C * 0x3500) * sp64 * 0.5f;
    Matrix_RotateYF(Math_SinS(this->unk_15C * 0x4500) * sp64, MTXMODE_APPLY);
    Matrix_RotateXFApply(sp60);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (this->actor.params) {
        case MAJORA_REMAINS + REMAINS_ODOLWA:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskOdolwaDL);
            break;
        case MAJORA_REMAINS + REMAINS_GYORG:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskGyorgDL);
            break;
        case MAJORA_REMAINS + REMAINS_GOHT:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskGohtDL);
            break;
        case MAJORA_REMAINS + REMAINS_TWINMOLD:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskTwinmoldDL);
            break;
    }
    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    if (this->actionFunc == Boss07_Remains_Intro) {
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, 200);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 100, 128);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(this->unk_188C, this->unk_188C, 0.0f, MTXMODE_APPLY);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_RotateZS(this->unk_18C8, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Top_SetupThrown(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Top_Thrown;
    this->actor.gravity = 0.0f;
    this->unk_17C = (sREG(42) * 0.01f) + 0.9f;
    this->timers[0] = 200;
}

void Boss07_Top_Thrown(Boss07* this, PlayState* play) {
    if (sMajorasWrath->actionFunc == Boss07_Wrath_SpawnTop) {
        Math_Vec3f_Copy(&this->actor.world.pos, &sMajorasWrath->unk_F80);
        this->actor.world.pos.y -= 25.0f + sREG(78);
    }
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 50.0f, 80.0f, 1);
    if ((sMajorasWrath->actionTimer >= (s16)(KREG(50) + 21)) || (sMajorasWrath->unk_15C != 0)) {
        Boss07_Top_SetupGround(this, play);
    } else if (this->actor.bgCheckFlags & 8) {
        Boss07_Top_SetupGround(this, play);
        this->actor.speedXZ = -15.0f;
        CollisionCheck_SpawnShieldParticles(play, &this->actor.focus.pos);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
    }
}

void Boss07_Top_SetupGround(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Top_Ground;
    this->actor.gravity = -2.0f;
    if (sMajorasWrath->unk_15C != 0) {
        this->timers[0] = sREG(47) + 80;
        this->timers[1] = sREG(77) + 150;
    } else {
        this->timers[0] = sREG(47) + 300;
        this->timers[1] = sREG(77) + 370;
        this->actor.velocity.y = (sREG(43) * 0.1f) + 15.0f;
        this->actor.speedXZ = (sREG(44) * 0.1f) + -3.0f;
    }
    this->actor.world.rot.y = (sREG(45) * 0x1000) + sMajorasWrath->actor.shape.rot.y;
    this->actor.shape.rot.z = Rand_ZeroFloat((sREG(29) + 10) * 256.0f);
}

void Boss07_Top_Ground(Boss07* this, PlayState* play) {
    f32 sp4C;
    f32 sp48;

    func_8019FAD8(&this->actor.projectedPos, NA_SE_EN_LAST3_KOMA_OLD - SFX_FLAG, this->unk_17C * 1.1111112f);
    Actor_MoveWithGravity(&this->actor);
    this->actor.world.pos.x += this->unk_18CC;
    this->actor.world.pos.z += this->unk_18D0;
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 40.0f, 80.0f, 5);
    if ((this->unk_158 == 0) && (this->actor.bgCheckFlags & 8)) {
        this->unk_158 = 10;
        if (this->unk_17C > 0.01f) {
            if (this->unk_17C < 0.45f) {
                this->actor.speedXZ *= -1.0f;
            } else {
                this->actor.speedXZ = -10.0f;
            }
            CollisionCheck_SpawnShieldParticles(play, &this->actor.focus.pos);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
        }
    }
    if (this->actor.bgCheckFlags & 1) {
        if (this->timers[0] < (s16)(sREG(24) + 70)) {
            if (this->timers[0] >= (s16)(sREG(25) + 35)) {
                Math_ApproachZeroF(&this->actor.speedXZ, 1.0f, (sREG(17) * 0.01f) + 0.1f);
                Math_ApproachS(&this->actor.shape.rot.z, (sREG(19) * 0x800) + 0x2000, 1, sREG(18) + 416);
                Math_ApproachZeroF(&this->unk_17C, 1.0f, (sREG(16) * 0.0001f) + 0.005f);
                Math_ApproachS(&this->unk_180, (sREG(20) * 0x800) + 0x2000, 1, (sREG(21) * 16) + 192);
            } else if (this->timers[0] == 0) {
                Math_ApproachZeroF(&this->actor.speedXZ, 1.0f, (sREG(26) * 0.01f) + 0.5f);
                Math_ApproachS(&this->actor.shape.rot.z, (sREG(19) * 0x800) + 0x2000, 1, 0x800);
                Math_ApproachZeroF(&this->unk_17C, 1.0f, (sREG(27) * 0.001f) + 0.024f);
                Math_ApproachS(&this->unk_180, 0, 2, sREG(28) + 106);
            } else {
                Math_ApproachF(&this->actor.speedXZ, sREG(22) + 10.0f, 1.0f, (sREG(23) * 0.01f) + 0.6f);
                Math_ApproachS(&this->actor.shape.rot.z, (sREG(19) * 0x800) + 0x2000, 1, sREG(18) + 1040);
                Math_ApproachZeroF(&this->unk_17C, 1.0f, (sREG(16) * 0.0001f) + 0.005f);
                Math_ApproachS(&this->unk_180, (sREG(29) * 0x800) - 0x800, 1, (sREG(30) * 16) + 832);
            }
            this->actor.world.rot.y += this->unk_180;
        } else {
            Math_ApproachS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x300);
            Math_ApproachF(&this->actor.speedXZ, (sREG(48) * 0.1f) + 2.0f + 8.0f, 1.0f,
                           (sREG(46) * 0.01f) + 0.100000024f + 0.2f);
        }
        Math_ApproachZeroF(&this->unk_18CC, 1.0f, 1.0f);
        Math_ApproachZeroF(&this->unk_18D0, 1.0f, 1.0f);
        if (this->actor.velocity.y < (sREG(40) + -2.0f)) {
            this->actor.velocity.y *= -(0.5f + (sREG(41) * 0.01f));
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
            CollisionCheck_SpawnShieldParticles(play, &this->actor.world.pos);
            this->actor.speedXZ *= 0.5f + (sREG(57) * 0.01f);
        } else {
            this->actor.velocity.y = -0.5f;
        }
        sp4C = this->actor.prevPos.x - this->actor.world.pos.x;
        sp48 = this->actor.prevPos.z - this->actor.world.pos.z;
        func_800AE930(&play->colCtx, Effect_GetByIndex(this->effectIndex), &this->actor.world.pos, 3.0f,
                      Math_Atan2S(sp4C, sp48), this->actor.floorPoly, this->actor.floorBgId);
        this->actionState = MAJORAS_TOP_STATE_1;
    } else if (this->actionState != MAJORAS_TOP_STATE_0) {
        this->actionState = MAJORAS_TOP_STATE_0;
        func_800AEF44(Effect_GetByIndex(this->effectIndex));
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->timers[1] == 0) {
        EnBom* bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, this->actor.world.pos.x,
                                          this->actor.world.pos.y + 25.0f, this->actor.world.pos.z, 0, 0, 0, 0);

        if (bomb != NULL) {
            bomb->timer = 0;
        }
        Actor_MarkForDeath(&this->actor);
    } else if (this->timers[1] == 25) {
        this->unk_15E = 25;
        func_800BC154(play, &play->actorCtx, &this->actor, 3);
    }
}

void Boss07_Top_Collide(Boss07* this, PlayState* play) {
    s32 i;
    Boss07* top;
    f32 dx;
    f32 dy;
    f32 dz;

    if (this->unk_158 == 0) {
        top = (Boss07*)play->actorCtx.actorLists[ACTORCAT_BOSS].first;

        while (top != NULL) {
            if ((this != top) && (top->actor.params == MAJORA_TOP) && (top->unk_158 == 0)) {
                dx = top->actor.world.pos.x - this->actor.world.pos.x;
                dy = top->actor.world.pos.y - this->actor.world.pos.y;
                dz = top->actor.world.pos.z - this->actor.world.pos.z;

                if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < (sREG(28) + 50.0f)) {
                    top->unk_158 = this->unk_158 = 10;
                    this->actor.world.rot.y = Math_Atan2S(dx, dz);
                    top->actor.world.rot.y = this->actor.world.rot.y + 0x7FFF;
                    if (this->timers[0] > 0) {
                        this->actor.speedXZ = -10.0f;
                    } else {
                        this->actor.speedXZ = -5.0f;
                        this->unk_17C = (sREG(89) * 0.01f) + 0.2f;
                        this->unk_180 = 0x800;
                    }
                    if (top->timers[0] > 0) {
                        top->actor.speedXZ = -10.0f;
                    } else {
                        top->actor.speedXZ = -5.0f;
                        top->unk_17C = (sREG(89) * 0.01f) + 0.2f;
                        top->unk_180 = 0x800;
                    }
                    CollisionCheck_SpawnShieldParticles(play, &this->actor.focus.pos);
                    CollisionCheck_SpawnShieldParticles(play, &top->actor.focus.pos);
                    if (this->timers[0] > 80) {
                        this->actor.shape.rot.z = randPlusMinusPoint5Scaled((sREG(29) + 20) * 256.0f);
                        for (i = 0; i < 5; i++) {
                            DECR(this->timers[0]);
                            DECR(this->timers[1]);
                        }
                    }
                    if (top->timers[0] > 80) {
                        top->actor.shape.rot.z = randPlusMinusPoint5Scaled((sREG(29) + 20) * 256.0f);
                        for (i = 0; i < 5; i++) {
                            DECR(top->timers[0]);
                            DECR(top->timers[1]);
                        }
                    }
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_SHIELD_REFLECT_SW);
                    break;
                }
            }
            top = (Boss07*)top->actor.next;
        }
    }
}

void Boss07_Top_CollisionCheck(Boss07* this, PlayState* play) {
    s32 sp3C;
    s32 sp38 = 0;
    Player* player = GET_PLAYER(play);
    s32 pad[3];

    if (this->cyl2.base.acFlags & 2) {
        this->cyl2.base.acFlags &= ~2;
        if (this->unk_15C == 0) {
            this->unk_15C = 5;
            if ((this->actor.colChkInfo.damageEffect == 13) || (this->actor.colChkInfo.damageEffect == 10)) {
                if (this->actor.colChkInfo.damageEffect == 13) {
                    player->unk_B84 = this->actor.yawTowardsPlayer;
                    player->unk_B80 = 20.0f;
                }
                if (this->timers[0] > 40) {
                    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                    if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
                        this->actor.speedXZ = -30.0f;
                        this->actor.velocity.y = 10.0f;
                        if ((s16)(sREG(47) + 100) < this->timers[0]) {
                            this->timers[0] = sREG(47) + 100;
                            this->timers[1] = sREG(77) + 170;
                        }
                    } else if (this->actor.colChkInfo.damageEffect == 10) {
                        this->actor.speedXZ = -15.0f;
                    } else {
                        this->actor.speedXZ = -7.0f;
                    }
                }
            } else if (this->actor.colChkInfo.damageEffect == 12) {
                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                this->actor.speedXZ = 2.0f * -player->actor.speedXZ;
                sp38 = 1;
            } else if (this->actor.colChkInfo.damageEffect == 11) {
                this->actor.world.rot.y = Math_Atan2S(this->cyl2.base.ac->world.pos.x - this->actor.world.pos.x,
                                                      this->cyl2.base.ac->world.pos.z - this->actor.world.pos.z);
                this->actor.speedXZ = -20.0f;
                this->actor.velocity.y = sREG(55) + 15.0f;
                sp38 = 1;
            }
        }
    }
    if (this->actor.bgCheckFlags & 1) {
        if ((func_800B64FC(play, 5.0f, &this->actor.world.pos, &sp3C) >= 0.0f) && (sp3C == 0)) {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            this->actor.velocity.y = sREG(55) + 25.0f;
            sp38 = 1;
        }
    }
    if (sp38 && (this->timers[0] > 90)) {
        this->actor.shape.rot.z = randPlusMinusPoint5Scaled((sREG(29) + 30) * 256.0f);
        this->timers[0] = Rand_ZeroFloat(10.0f) + 70.0f;
        this->timers[1] = this->timers[0] + 70;
    }
}

void Boss07_Top_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    this->actionTimer++;
    DECR(this->timers[0]);
    DECR(this->timers[1]);
    DECR(this->unk_15E);
    DECR(this->unk_15C);
    DECR(this->unk_158);
    this->actionFunc(this, play);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
    this->actor.focus.pos.y += 25.0f;
    Boss07_Top_CollisionCheck(this, play);
    Collider_UpdateCylinder(&this->actor, &this->cyl2);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->cyl2.base);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->cyl2.base);
    Boss07_Top_Collide(this, play);
    this->unk_178 -= this->unk_17C;
    if (this->unk_178 < -2.0f * M_PI) {
        this->unk_178 += 2.0f * M_PI;
    }
    if (sMajorasWrath->actionFunc == Boss07_Wrath_Death) {
        Actor_MarkForDeath(&this->actor);
    }
    Math_ApproachF(&this->actor.scale.x, (sREG(77) * 0.001f) + 0.06f, 1.0f, 0.012f);
    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void Boss07_Top_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    if ((this->unk_15E % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 780, 1099);
    }
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_RotateYF(this->unk_178, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathTopDL);
    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Static_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    Boss07_Static_UpdateEffects(play);

    if (sHeartbeatTimer != 0) {
        sHeartbeatTimer--;
    dummy_label:; //!@fake
        play_sound(NA_SE_EN_LAST2_HEARTBEAT_OLD - SFX_FLAG);
    }
    if (this->unk_1808 != 0) {
        D_801F4E32 = 1;
        D_801F4E38 = this->unk_1810;
        D_801F4E44 = this->unk_180C;
        D_801F4E48 = 10.0f;
        D_801F4E4C = 0;
        this->unk_1808 = 0;
    } else {
        D_801F4E32 = 0;
    }
    this->unk_ABC8++;
    switch (this->csState) {
        case 0:
            if ((sMajorasMask != NULL) && sMajorasMask->unk_774) {
                this->csState = 1;
                this->unk_ABC8 = 0;
            }
            break;
        case 1:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                Cutscene_Start(play, &play->csCtx);
                func_800B7298(play, &this->actor, 7);
                this->subCamIndex = Play_CreateSubCamera(play);
                Play_ChangeCameraStatus(play, 0, 1);
                Play_ChangeCameraStatus(play, this->subCamIndex, 7);
                this->unk_ABC8 = 0;
                this->csState = 2;
                func_8016566C(150);
                this->subCamEye.x = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 2:
            if (this->unk_ABC8 == 20) {
                sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_STATE_20;
            }
            this->subCamAt.x = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                this->csState = 3;
                this->unk_ABC8 = 0;
                this->subCamEye.x = sBossRemains[REMAINS_GYORG]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_GYORG]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_GYORG]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 3:
            if (this->unk_ABC8 == 20) {
                sBossRemains[REMAINS_GYORG]->actionState = MAJORAS_REMAINS_STATE_20;
            }
            this->subCamAt.x = sBossRemains[REMAINS_GYORG]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_GYORG]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_GYORG]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                this->csState = 4;
                this->unk_ABC8 = 0;
                this->subCamEye.x = sBossRemains[REMAINS_GOHT]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_GOHT]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_GOHT]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 4:
            if (this->unk_ABC8 == 20) {
                sBossRemains[REMAINS_GOHT]->actionState = MAJORAS_REMAINS_STATE_20;
            }
            this->subCamAt.x = sBossRemains[REMAINS_GOHT]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_GOHT]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_GOHT]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                this->csState = 5;
                this->unk_ABC8 = 0;
                this->subCamEye.x = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case 5:
            if (this->unk_ABC8 == 20) {
                sBossRemains[REMAINS_TWINMOLD]->actionState = MAJORAS_REMAINS_STATE_20;
            }
            this->subCamAt.x = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.z;
            if (this->unk_ABC8 == 40) {
                Camera* camera = Play_GetCamera(play, CAM_ID_MAIN);
                s32 i;

                this->csState = 6;
                this->unk_ABC8 = 0;
                camera->eye = this->subCamEye;
                camera->eyeNext = this->subCamEye;
                camera->at = this->subCamAt;
                func_80169AFC(play, this->subCamIndex, 0);
                this->subCamIndex = SUB_CAM_ID_DONE;
                Cutscene_End(play, &play->csCtx);
                func_800B7298(play, &this->actor, 6);
                func_80165690();
                for (i = 0; i < ARRAY_COUNT(sBossRemains); i++) {
                    func_800BC154(play, &play->actorCtx, &sBossRemains[i]->actor, ACTORCAT_ENEMY);
                }
            }
            break;
        case 6:
            break;
    }
    if (this->subCamIndex != 0) {
        if (this->unk_ABC8 < 20) {
            s32 j;

            for (j = 0; j < ARRAY_COUNT(sBossRemains); j++) {
                if ((this->unk_ABC8 % 2) != 0) {
                    sBossRemains[j]->actor.world.pos.x += 2.0f;
                    sBossRemains[j]->actor.world.pos.z += 2.0f;
                } else {
                    sBossRemains[j]->actor.world.pos.x -= 2.0f;
                    sBossRemains[j]->actor.world.pos.z -= 2.0f;
                }
            }
        }
        ShrinkWindow_SetLetterboxTarget(27);
        Play_SetCameraAtEye(play, this->subCamIndex, &this->subCamAt, &this->subCamEye);
    }
}

void Boss07_Static_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    Boss07_Static_DrawEffects(play);
    Boss07_Static_DrawLight(this, play);
}

void Boss07_Static_UpdateEffects(PlayState* play) {
    Boss07Effect* effect = (Boss07Effect*)play->specialEffects;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sEffects); i++, effect++) {
        if (effect->type != MAJORA_EFFECT_NONE) {
            effect->scroll++;

            effect->pos.x += effect->vel.x;
            effect->pos.y += effect->vel.y;
            effect->pos.z += effect->vel.z;

            effect->vel.x += effect->accel.x;
            effect->vel.y += effect->accel.y;
            effect->vel.z += effect->accel.z;
            if (effect->type == MAJORA_EFFECT_FLAME) {
                if (effect->isFading) {
                    effect->alpha -= (i % 8U) + 13;
                    if (effect->alpha <= 0) {
                        effect->alpha = 0;
                        effect->type = MAJORA_EFFECT_NONE;
                    }
                } else {
                    effect->alpha += 300;
                    if (effect->alpha >= 255) {
                        effect->alpha = 255;
                        effect->isFading++;
                    }
                }
            }
        }
    }
}

void Boss07_Static_DrawEffects(PlayState* play) {
    Boss07Effect* effect = (Boss07Effect*)play->specialEffects;
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    s32 i;

    OPEN_DISPS(gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    for (i = 0; i < ARRAY_COUNT(sEffects); i++, effect++) {
        if (effect->type > MAJORA_EFFECT_NONE) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 20, 0, effect->alpha);
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 215, 255, 128);
            gSPSegment(POLY_XLU_DISP++, 8,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, (3 * effect->scroll) % 0x80U,
                                        (15 * -effect->scroll) % 0x100U, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));
            Matrix_Translate(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(effect->scale, effect->scale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskFireDL);
        }
    }
    CLOSE_DISPS(gfxCtx);
}
