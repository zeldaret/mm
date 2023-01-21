/*
 * File: z_boss_07.c
 * Overlay: ovl_Boss_07
 * Description: Majora
 */

#include "z_boss_07.h"
#include "z64shrink_window.h"
#include "overlays/actors/ovl_Obj_Tsubo/z_obj_tsubo.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_boss07/object_boss07.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss07*)thisx)

#define FACING_ANGLE(actor1, actor2) ((s16)((actor1)->shape.rot.y - (actor2)->shape.rot.y + 0x8000))

#define EFFECT_COUNT 50

#define RIGHT_HAND 0
#define LEFT_HAND 1

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
    /* 0x0 */ MAJORAS_WRATH_DMGEFF_0,
    /* 0x2 */ MAJORAS_WRATH_DMGEFF_2 = 2,
    /* 0x3 */ MAJORAS_WRATH_DMGEFF_3,
    /* 0x4 */ MAJORAS_WRATH_DMGEFF_4,
    /* 0x9 */ MAJORAS_WRATH_DMGEFF_9 = 9,
    /* 0xA */ MAJORAS_WRATH_DMGEFF_A,
    /* 0xC */ MAJORAS_WRATH_DMGEFF_C = 0xC,
    /* 0xD */ MAJORAS_WRATH_DMGEFF_D,
    /* 0xE */ MAJORAS_WRATH_DMGEFF_E,
    /* 0xF */ MAJORAS_WRATH_DMGEFF_F,
} Boss07WrathDamageEffect;

typedef enum {
    /* 0x0 */ MAJORAS_INCARNATION_DMGEFF_0,
    /* 0x2 */ MAJORAS_INCARNATION_DMGEFF_2 = 2,
    /* 0x3 */ MAJORAS_INCARNATION_DMGEFF_3,
    /* 0x4 */ MAJORAS_INCARNATION_DMGEFF_4,
    /* 0x9 */ MAJORAS_INCARNATION_DMGEFF_9 = 9,
    /* 0xA */ MAJORAS_INCARNATION_DMGEFF_A,
    /* 0xC */ MAJORAS_INCARNATION_DMGEFF_C = 0xC,
    /* 0xD */ MAJORAS_INCARNATION_DMGEFF_D,
    /* 0xE */ MAJORAS_INCARNATION_DMGEFF_E,
    /* 0xF */ MAJORAS_INCARNATION_DMGEFF_F,
} Boss07IncarnationDamageEffect;

typedef enum {
    /* 0x0 */ MAJORAS_MASK_DMGEFF_0,
    /* 0x2 */ MAJORAS_MASK_DMGEFF_2 = 2,
    /* 0x3 */ MAJORAS_MASK_DMGEFF_3,
    /* 0x4 */ MAJORAS_MASK_DMGEFF_4,
    /* 0x9 */ MAJORAS_MASK_DMGEFF_9 = 9,
    /* 0xF */ MAJORAS_MASK_DMGEFF_F = 0xF,
} Boss07MaskDamageEffect;

typedef enum {
    /* 0x0 */ MAJORAS_REMAINS_DMGEFF_0,
    /* 0x2 */ MAJORAS_REMAINS_DMGEFF_2 = 2,
    /* 0x3 */ MAJORAS_REMAINS_DMGEFF_3,
    /* 0x4 */ MAJORAS_REMAINS_DMGEFF_4,
    /* 0x9 */ MAJORAS_REMAINS_DMGEFF_9 = 9,
    /* 0xA */ MAJORAS_REMAINS_DMGEFF_A,
    /* 0xC */ MAJORAS_REMAINS_DMGEFF_C = 0xC,
    /* 0xD */ MAJORAS_REMAINS_DMGEFF_D,
    /* 0xE */ MAJORAS_REMAINS_DMGEFF_E,
    /* 0xF */ MAJORAS_REMAINS_DMGEFF_F,
} Boss07RemainsDamageEffect;

typedef enum {
    /* 0x0 */ MAJORAS_TOP_DMGEFF_0,
    /* 0xA */ MAJORAS_TOP_DMGEFF_A = 0xA,
    /* 0xB */ MAJORAS_TOP_DMGEFF_B,
    /* 0xC */ MAJORAS_TOP_DMGEFF_C,
    /* 0xD */ MAJORAS_TOP_DMGEFF_D,
    /* 0xE */ MAJORAS_TOP_DMGEFF_E,
    /* 0xF */ MAJORAS_TOP_DMGEFF_F,
} Boss07TopDamageEffect;

typedef enum {
    /* 0 */ REMAINS_ODOLWA,
    /* 1 */ REMAINS_GYORG,
    /* 2 */ REMAINS_GOHT,
    /* 3 */ REMAINS_TWINMOLD,
    /* 4 */ REMAINS_COUNT
} RemainsIndex;

typedef enum {
    /* 0 */ MAJORAS_EFFECT_NONE,
    /* 1 */ MAJORAS_EFFECT_FLAME
} Boss07EffectType;

typedef enum {
    /* 0 */ MAJORAS_WRATH_QUICK_WHIP,
    /* 1 */ MAJORAS_WRATH_FLURRY,
    /* 2 */ MAJORAS_WRATH_DOUBLE_WHIP,
    /* 3 */ MAJORAS_WRATH_LONG_WHIP,
    /* 4 */ MAJORAS_WRATH_SPIN_ATTACK,
    /* 5 */ MAJORAS_WRATH_TAUNT,
    /* 6 */ MAJORAS_WRATH_THREE_HIT,
    /* 7 */ MAJORAS_WRATH_KICK,
    /* 8 */ MAJORAS_WRATH_ATTACK_MAX,
} Boss07WrathActionState;

typedef enum {
    /* 0 */ MAJORAS_INCARNATION_STATE_0,
    /* 1 */ MAJORAS_INCARNATION_STATE_1,
    /* 2 */ MAJORAS_INCARNATION_STATE_2,
    /* 3 */ MAJORAS_INCARNATION_STATE_MAX,
} Boss07IncarnationActionState;

typedef enum {
    /* 0 */ MAJORAS_MASK_SPIN_START,
    /* 1 */ MAJORAS_MASK_SPIN_ATTACK,
    /* 2 */ MAJORAS_MASK_SPIN_END,
    /* 3 */ MAJORAS_MASK_SPIN_STATE_MAX,
} Boss07MaskSpinState;

typedef enum {
    /* 0 */ MAJORAS_MASK_BEAM_CHARGE,
    /* 1 */ MAJORAS_MASK_BEAM_EYES,
    /* 2 */ MAJORAS_MASK_BEAM_FOCUS,
    /* 3 */ MAJORAS_MASK_BEAM_ACTIVE,
    /* 4 */ MAJORAS_MASK_BEAM_REFLECT,
    /* 5 */ MAJORAS_MASK_BEAM_END,
    /* 6 */ MAJORAS_MASK_BEAM_STATE_MAX,
} Boss07MaskBeamState;

typedef enum {
    /* 0 */ MAJORAS_PROJECTILE_STATE_0,
    /* 1 */ MAJORAS_PROJECTILE_STATE_1,
    /* 2 */ MAJORAS_PROJECTILE_STATE_MAX,
} Boss07ProjectileState;

typedef enum {
    /*  0 */ MAJORAS_REMAINS_WAIT,
    /*  1 */ MAJORAS_REMAINS_FLY,
    /*  2 */ MAJORAS_REMAINS_DEATH,
    /*  3 */ MAJORAS_REMAINS_GONE,
    /* 10 */ MAJORAS_REMAINS_DAMAGED = 10,
    /* 20 */ MAJORAS_REMAINS_ACTIVATE = 20,
} Boss07RemainsState;

typedef enum {
    /* 0 */ MAJORAS_REMAINS_CS_WAIT,
    /* 1 */ MAJORAS_REMAINS_CS_FLY,
    /* 2 */ MAJORAS_REMAINS_CS_ATTACH_WAIT,
    /* 3 */ MAJORAS_REMAINS_CS_ATTACH,
} Boss07RemainsCsState;

typedef enum {
    /* 0 */ MAJORAS_TOP_IN_AIR,
    /* 1 */ MAJORAS_TOP_ON_GROUND,
    /* 2 */ MAJORAS_TOP_STATE_MAX,
} Boss07TopStates;

typedef enum {
    /* 0 */ MAJORAS_MASK_INTRO_STATE_0,
    /* 1 */ MAJORAS_MASK_INTRO_STATE_1,
    /* 2 */ MAJORAS_MASK_INTRO_STATE_2,
    /* 3 */ MAJORAS_MASK_INTRO_STATE_3,
    /* 4 */ MAJORAS_MASK_INTRO_STATE_4,
} Boss07MaskIntroState;

typedef enum {
    /* 0 */ MAJORAS_MASK_DEATH_STATE_0,
    /* 1 */ MAJORAS_MASK_DEATH_STATE_1,
    /* 2 */ MAJORAS_MASK_DEATH_STATE_2,
    /* 3 */ MAJORAS_MASK_DEATH_STATE_3,
    /* 4 */ MAJORAS_MASK_DEATH_STATE_4,
} Boss07MaskDeathState;

typedef enum {
    /* 0 */ MAJORAS_INCARNATION_INTRO_STATE_0,
    /* 1 */ MAJORAS_INCARNATION_INTRO_STATE_1,
    /* 2 */ MAJORAS_INCARNATION_INTRO_STATE_2,
    /* 3 */ MAJORAS_INCARNATION_INTRO_STATE_3,
    /* 4 */ MAJORAS_INCARNATION_INTRO_STATE_4,
    /* 5 */ MAJORAS_INCARNATION_INTRO_STATE_5,
} Boss07IncarnationIntroState;

typedef enum {
    /*  0 */ MAJORAS_INCARNATION_DEATH_STATE_0,
    /*  1 */ MAJORAS_INCARNATION_DEATH_STATE_1,
    /*  2 */ MAJORAS_INCARNATION_DEATH_STATE_2,
    /*  3 */ MAJORAS_INCARNATION_DEATH_STATE_3,
    /*  4 */ MAJORAS_INCARNATION_DEATH_STATE_4,
    /* 10 */ MAJORAS_INCARNATION_DEATH_STATE_10 = 10,
} Boss07IncarnationDeathState;

typedef enum {
    /* 0 */ MAJORAS_WRATH_INTRO_STATE_0,
    /* 1 */ MAJORAS_WRATH_INTRO_STATE_1,
} Boss07WrathIntroState;

typedef enum {
    /* 0 */ MAJORAS_WRATH_DEATH_STATE_0,
    /* 1 */ MAJORAS_WRATH_DEATH_STATE_1,
    /* 2 */ MAJORAS_WRATH_DEATH_STATE_2,
    /* 3 */ MAJORAS_WRATH_DEATH_STATE_3,
    /* 4 */ MAJORAS_WRATH_DEATH_STATE_4,
} Boss07WrathDeathState;

typedef enum {
    /*  0 */ MAJORAS_DAMAGE_STATE_0,
    /*  1 */ MAJORAS_DAMAGE_STATE_1,
    /*  2 */ MAJORAS_DAMAGE_STATE_2,
    /* 10 */ MAJORAS_DAMAGE_STATE_10 = 10,
    /* 11 */ MAJORAS_DAMAGE_STATE_11,
    /* 20 */ MAJORAS_DAMAGE_STATE_20 = 20,
    /* 21 */ MAJORAS_DAMAGE_STATE_21,
    /* 30 */ MAJORAS_DAMAGE_STATE_30 = 30,
    /* 40 */ MAJORAS_DAMAGE_STATE_40 = 40,
    /* 41 */ MAJORAS_DAMAGE_STATE_41,
} Boss07DamageState;

typedef enum {
    /* 0 */ MAJORAS_STATIC_CS_STATE_0,
    /* 1 */ MAJORAS_STATIC_CS_STATE_1,
    /* 2 */ MAJORAS_STATIC_CS_STATE_2,
    /* 3 */ MAJORAS_STATIC_CS_STATE_3,
    /* 4 */ MAJORAS_STATIC_CS_STATE_4,
    /* 5 */ MAJORAS_STATIC_CS_STATE_5,
    /* 6 */ MAJORAS_STATIC_CS_STATE_6,
} Boss07StaticCsState;

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
void Boss07_Wrath_SetupDamaged(Boss07* this, PlayState* play, u8 damage, u8 dmgEffect);
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
void Boss07_Mask_SetupDamaged(Boss07* this, PlayState* play, u8 damage, Actor* hitActor);
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
void Boss07_Incarnation_SetupDamaged(Boss07* this, PlayState* play, u8 damage, u8 dmgEffect);
void Boss07_Incarnation_SetupStunned(Boss07* this, PlayState* play, s16 stunTime);
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

static s16 sShotEnvColors[4][3] = {
    { 255, 255, 100 }, // light yellow
    { 255, 100, 100 }, // light red
    { 100, 255, 100 }, // light green
    { 100, 100, 255 }, // light blue
};

static s16 sShotPrimColors[4][3] = {
    { 255, 255, 255 }, // white
    { 255, 255, 255 }, // white
    { 255, 255, 255 }, // white
    { 255, 255, 255 }, // white
};

#include "z_boss_07_dmgtbl.inc"

ActorInit Boss_07_InitVars = {
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

#include "z_boss_07_colchk.inc"

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

void Boss07_SpawnEffect(PlayState* play, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale) {
    s32 i;
    Boss07Effect* effect = (Boss07Effect*)play->specialEffects;

    for (i = 0; i < ARRAY_COUNT(sEffects); i++, effect++) {
        if (effect->type == MAJORAS_EFFECT_NONE) {
            effect->type = MAJORAS_EFFECT_FLAME;
            effect->pos = *pos;
            effect->vel = *vel;
            effect->accel = *accel;
            effect->scale = scale / 1000.0f;
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

void Boss07_Incarnation_SpawnDust(Boss07* this, PlayState* play, u8 spawnInterval, u8 spawnAtFocus) {
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
            if (spawnAtFocus) {
                pos.x = this->actor.focus.pos.x + randPlusMinusPoint5Scaled(150.0f);
                pos.z = this->actor.focus.pos.z + randPlusMinusPoint5Scaled(150.0f);
            } else {
                pos.z = this->incFeetPos[i].z + randPlusMinusPoint5Scaled(20.0f);
                pos.x = this->incFeetPos[i].x + randPlusMinusPoint5Scaled(20.0f);
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

void Boss07_Wrath_Dodge(Boss07* this, PlayState* play, u8 canCancel) {
    Player* player = GET_PLAYER(play);

    if ((this->invincibilityTimer == 0) &&
        (((this->actionFunc != Boss07_Wrath_Flip) && (this->actionFunc != Boss07_Wrath_StartJump) &&
          (this->actionFunc != Boss07_Wrath_Jump)) ||
         canCancel)) {
        if (Rand_ZeroOne() < 0.5f) {
            Boss07_Wrath_SetupFlip(this, play);
        } else {
            Boss07_Wrath_SetupJump(this, play);
        }
        this->unk_158 = 10;
        this->whipGrabIndex = 0;
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

void Boss07_Wrath_BlastWhip(Vec3f* bombPos, Vec3f* pos, Vec3f* vel) {
    s32 i;
    f32 push;
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3f impulse;

    impulse.x = 0.0f;

    for (i = 0; i < sWhipSegCount; i++, pos++, vel++) {
        dx = pos->x - bombPos->x;
        dy = pos->y - bombPos->y;
        dz = pos->z - bombPos->z;

        if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 300.0f) {

            push = 300.0f - sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
            push = CLAMP_MAX(push, 200.0f);

            impulse.y = push;
            impulse.z = push;
            Matrix_RotateYF(Math_Atan2F_XY(dz, dx), MTXMODE_NEW);
            Matrix_MultVec3f(&impulse, vel);
        }
    }
}

void Boss07_Wrath_BombWhips(Boss07* this, PlayState* play) {
    Actor* explosive = play->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;

    while (explosive != NULL) {
        if (explosive->params == 1) {
            Boss07_Wrath_BlastWhip(&explosive->world.pos, this->rightWhip.pos, this->rightWhip.vel);
            Boss07_Wrath_BlastWhip(&explosive->world.pos, this->leftWhip.pos, this->leftWhip.vel);
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
        MAJORAS_REMAINS + REMAINS_ODOLWA,
        MAJORAS_REMAINS + REMAINS_GYORG,
        MAJORAS_REMAINS + REMAINS_GOHT,
        MAJORAS_REMAINS + REMAINS_TWINMOLD,
    };
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;

    if (this->actor.params == MAJORAS_STATIC) {
        this->actor.update = Boss07_Static_Update;
        this->actor.draw = Boss07_Static_Draw;
        this->actor.flags &= ~ACTOR_FLAG_1;
        sMajoraStatic = this;
        sKillProjectiles = false;
        play->envCtx.lightSettingOverride = 0;
        play->envCtx.unk_E0 = 2;
        return;
    }

    if (this->actor.params == MAJORAS_BOSS) {
        this->actor.params = MAJORAS_MASK;
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, MAJORAS_STATIC);
        play->specialEffects = (void*)sEffects;

        for (i = 0; i < ARRAY_COUNT(sEffects); i++) {
            sEffects[i].type = MAJORAS_EFFECT_NONE;
        }
        for (i = 0; i < ARRAY_COUNT(sBossRemains); i++) {
            sBossRemains[i] = NULL;
        }
    }
    this->actor.targetMode = 5;
    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.gravity = -2.5f;

    if (thisx->params >= MAJORAS_REMAINS) {
        this->actor.update = Boss07_Remains_Update;
        this->actor.draw = Boss07_Remains_Draw;

        sBossRemains[thisx->params - MAJORAS_REMAINS] = this;
        if (gSaveContext.eventInf[6] & 2) {
            Actor_SetScale(&this->actor, 0.03f);
            this->actor.world.pos.x = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].x;
            this->actor.world.pos.y = 370.0f;
            this->actor.world.pos.z = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].z;
            this->actor.shape.rot.y = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].y;
            Boss07_Remains_SetupFly(this, play);
        } else {
            Boss07_Remains_SetupIntro(this, play);
        }
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->actor.colChkInfo.damageTable = &sRemainsDmgTable;
        return;
    }

    if (this->actor.params == MAJORAS_TOP) {
        static EffectTireMarkInit sTopTireMarkInit = { 0, 40, { 0, 0, 15, 200 } };

        this->actor.update = Boss07_Top_Update;
        this->actor.draw = Boss07_Top_Draw;
        Boss07_Top_SetupThrown(this, play);
        this->actor.colChkInfo.damageTable = &sTopDmgTable;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, KREG(55) + 9.0f);
        this->actor.shape.shadowAlpha = 180;
        Collider_InitAndSetCylinder(play, &this->spawnCollider, &this->actor, &sTopCylInit);
        Effect_Add(play, &this->effectIndex, 4, 0, 0, &sTopTireMarkInit);
        this->actor.flags &= ~ACTOR_FLAG_1;
        return;
    }

    if ((this->actor.params == MAJORAS_REMAINS_SHOT) || (this->actor.params == MAJORAS_INCARNATION_SHOT)) {
        this->actor.update = Boss07_Projectile_Update;
        this->actor.draw = Boss07_Projectile_Draw;
        this->actor.flags &= ~ACTOR_FLAG_1;
        Collider_InitAndSetCylinder(play, &this->spawnCollider, &this->actor, &sShotCylInit);
        func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_ENEMY);
        this->shotColorIndex = Rand_ZeroFloat(ARRAY_COUNT(sShotEnvColors) - 0.01f);
        return;
    }

    if ((this->actor.params == MAJORAS_MASK) || (this->actor.params == MAJORAS_MASK_CS)) {
        this->actor.colChkInfo.damageTable = &sMaskDmgTable;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 15.0f);
        SkelAnime_Init(play, &this->skelAnime, &gMajorasMaskSkel, &gMajorasMaskFloatingAnim, this->jointTable,
                       this->morphTable, MAJORAS_MASK_LIMB_MAX);
        if (this->actor.params == MAJORAS_MASK) {
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
                this->vel_170 = 0.0f;
                this->timers[0] = 50;
                this->timers[2] = 200;
                this->noclipTimer = 50;
                this->actor.flags |= ACTOR_FLAG_1;
                sMusicStartTimer = 20;
            } else {
                Boss07_Mask_SetupIntro(this, play);
            }
            Collider_InitAndSetQuad(play, &this->maskFrontCollider, &this->actor, &sMaskQuadInit1);
            Collider_InitAndSetQuad(play, &this->maskBackCollider, &this->actor, &sMaskQuadInit2);
            this->actor.colChkInfo.health = 14;
            for (i = 0; i < ARRAY_COUNT(sRemainsParams); i++) {
                Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, 0.0f, 0.0f, 0.0f, 0, 0, 0, sRemainsParams[i]);
            }
        }
        return;
    }

    if ((this->actor.params == MAJORAS_INCARNATION) || (this->actor.params == MAJORAS_AFTERIMAGE)) {
        Actor_SetScale(&this->actor, 0.015000001f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gMajorasIncarnationSkel, &gMajorasIncarnationTauntDance1Anim,
                           this->jointTable, this->morphTable, MAJORAS_INCARNATION_LIMB_MAX);
        if (this->actor.params == MAJORAS_AFTERIMAGE) {
            this->timers[0] = this->actor.world.rot.z;
            this->actor.world.rot.z = 0;
            this->actor.update = Boss07_Afterimage_Update;
            this->actor.draw = Boss07_Afterimage_Draw;
            this->actor.flags &= ~ACTOR_FLAG_1;
        } else {
            this->actor.colChkInfo.damageTable = &sIncarnationDmgTable;
            this->actor.colChkInfo.health = 30;
            this->actor.update = Boss07_Incarnation_Update;
            this->actor.draw = Boss07_Incarnation_Draw;
            Collider_InitAndSetJntSph(play, &this->bodyCollider, &this->actor, &sIncarnationJntSphInit1,
                                      this->bodyElements);
            ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 80.0f);
            this->subCamIndex = this->actor.shape.rot.z;
            if (this->subCamIndex != SUB_CAM_ID_DONE) {
                Boss07_Incarnation_SetupIntro(this, play);
            } else {
                Boss07_Incarnation_SetupTaunt(this, play);
                this->envEffectOn = 1;
                for (i = 0; i < ARRAY_COUNT(this->unk_17B8); i++) {
                    this->unk_17B8[i] = 1.0f;
                }
                play->envCtx.lightBlend = 0.0f;
            }
            this->armScale = 1.0f;
            this->legScale = 1.0f;
            this->chestScaleY = 1.0f;
            this->chestScaleX = 1.0f;
        }
        return;
    }

    sMajorasWrath = this;
    this->actor.colChkInfo.health = 40;
    this->actor.colChkInfo.damageTable = &sWrathDmgTable;
    Actor_SetScale(&this->actor, 0.01f);
    this->subCamIndex = this->actor.shape.rot.z;
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        Boss07_Wrath_SetupIntro(this, play);
    } else {
        Boss07_Wrath_SetupIdle(this, play, 50);
        this->whipScale = 1.0f;
        Audio_QueueSeqCmd(NA_BGM_MAJORAS_WRATH | 0x8000);
    }
    SkelAnime_InitFlex(play, &this->skelAnime, &gMajorasWrathSkel, &gMajorasWrathIdleAnim, this->jointTable,
                       this->morphTable, MAJORAS_WRATH_LIMB_MAX);
    Collider_InitAndSetJntSph(play, &this->bodyCollider, &this->actor, &sWrathJntSphInit1, this->bodyElements);
    Collider_InitAndSetJntSph(play, &this->kickCollider, &this->actor, &sWrathJntSphInit2, this->kickElements);
    Collider_InitAndSetCylinder(play, &this->unusedCollider, &this->actor, &sWrathCylInit);

    this->leftWhip.mobility = this->rightWhip.mobility = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;

    sWhipSegCount = 44;
    this->armScale = 1.0f;
}

void Boss07_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    switch (this->actor.params) {
            //! @bug this should be MAJORAS_MASK
        case MAJORAS_WRATH:
            Collider_DestroyQuad(play, &this->maskFrontCollider);
            Collider_DestroyQuad(play, &this->maskBackCollider);
        case MAJORAS_TOP:
            Effect_Destroy(play, this->effectIndex);
            break;
    }
}

void Boss07_Wrath_SetupIntro(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_Intro;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasWrathHeavyBreathingAnim, 0.0f);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->csHeadRot.x = 0x7F00;
    this->invincibilityTimer = 20;
    this->unk_17E8 = 0x1400;
}

void Boss07_Wrath_Intro(Boss07* this, PlayState* play) {
    static f32 sCamPoints[5][3] = {
        { 40.0f, 400.0f, 110.0f }, { 80.0f, 450.0f, 110.0f }, { 100.0f, 400.0f, 110.0f },
        { 60.0f, 390.0f, 110.0f }, { 30.0f, 430.0f, 110.0f },
    };
    this->invincibilityTimer = 20;
    SkelAnime_Update(&this->skelAnime);
    this->timer_ABC8++;
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    switch (this->csState) {
        case MAJORAS_WRATH_INTRO_STATE_0:
            this->timer_ABC8 = 0;
            this->csState = MAJORAS_WRATH_INTRO_STATE_1;
            this->subCamNextAt.z = 0.f;
            this->subCamNextEye.x = 0.0;
            this->subCamNextEye.y = KREG(17) + 100.0f - 30.0f + 80.0f;
            this->subCamNextEye.z = KREG(18) + 270.0f - 150.0f + 30.0f - 50.0f;
            this->subCamNextAt.x = 0.0f;
            this->subCamNextAt.y = 180.0f;
        case MAJORAS_WRATH_INTRO_STATE_1:
            if (this->timer_ABC8 < 40) {
                sHeartbeatTimer = 3;
            }
            if (this->timer_ABC8 > 20) {
                if (this->timer_ABC8 == 21) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_GROW_HEAD_OLD);
                }
                Math_ApproachS(&this->csHeadRot.x, 0, 5, 0x1000);
                this->csHeadRot.y = Math_SinS(this->timer_ABC8 * 0x1000) * this->unk_17E8;
                this->csHeadRot.z = Math_SinS(this->timer_ABC8 * 0xB00) * this->unk_17E8 * 0.5f;
                if (this->timer_ABC8 > 40) {
                    Math_ApproachZeroF(&this->unk_17E8, 1.0f, 200.0f);
                }
            }
            if (this->timer_ABC8 > 60) {
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
                if (this->timer_ABC8 == 70) {
                    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathIntroAnim, -15.0f);
                    this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathIntroAnim);
                    func_8019FE1C(&this->actor.projectedPos, NA_SE_EV_ICE_PILLAR_RISING, 1.0f);
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_SHOUT);
                }
                if (this->timer_ABC8 >= 110) {
                    Math_ApproachF(&this->whipScale, 1.0f, 1.0f, 0.05f);
                    this->leftWhip.mobility = this->rightWhip.mobility = 0.01f * 80;
                    this->leftWhip.drag = this->rightWhip.drag = 1.0f;
                }
                if (this->timer_ABC8 == 127) {
                    this->whipScale = 1.0f;
                }
                if (this->timer_ABC8 == 120) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP2_OLD);
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_KICK_OLD);
                    func_8019FE74(&gSfxVolume, 0.0f, 0x3C);
                }
                if (this->timer_ABC8 == 112) {
                    Audio_QueueSeqCmd(NA_BGM_MAJORAS_WRATH | 0x8000);
                }
                if (this->timer_ABC8 == 137) {
                    TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt,
                                           Lib_SegmentedToVirtual(&gMajorasWrathTitleCardTex), 0xA0, 0xB4, 0x80, 0x28);
                }
                if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
                    s32 i;
                    Camera* mainCam = Play_GetCamera(play, CAM_ID_MAIN);

                    this->csState = MAJORAS_WRATH_INTRO_STATE_0;
                    Boss07_Wrath_SetupIdle(this, play, 50);
                    mainCam->eye = this->subCamEye;
                    mainCam->eyeNext = this->subCamEye;
                    mainCam->at = this->subCamAt;
                    func_80169AFC(play, this->subCamIndex, 0);
                    this->subCamIndex = SUB_CAM_ID_DONE;
                    Cutscene_End(play, &play->csCtx);
                    func_800B7298(play, &this->actor, 6);
                    this->actor.flags |= ACTOR_FLAG_1;
                    Play_DisableMotionBlur();
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
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        ShrinkWindow_Letterbox_SetSizeTarget(0x1B);
        Play_SetCameraAtEye(play, this->subCamIndex, &this->subCamAt, &this->subCamEye);
    }
}

void Boss07_Wrath_SetupDeath(Boss07* this, PlayState* play) {
    s32 i;

    Audio_QueueSeqCmd(NA_BGM_STOP | 0x10000);
    Boss07_MovePlayer(play);
    this->actionFunc = Boss07_Wrath_Death;
    this->leftWhip.mobility = this->rightWhip.mobility = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDeathAnim, 0.0f);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->csState = MAJORAS_WRATH_DEATH_STATE_0;
    this->timer_ABC8 = 0;
    if (sBossRemains[REMAINS_ODOLWA] != NULL) {
        for (i = 0; i < ARRAY_COUNT(sBossRemains); i++) {
            sBossRemains[i]->actionState = MAJORAS_REMAINS_DEATH;
        }
    }
    this->invincibilityTimer = 1000;
}

void Boss07_Wrath_Death(Boss07* this, PlayState* play) {
    s32 i;
    s32 spC0 = 0;
    Vec3f spB4;
    Vec3f spA8 = { 0.0f, 0.0f, 0.0f };
    f32 spA4 = 0.0f, spA0 = 0.1f;
    Camera* mainCam = Play_GetCamera(play, CAM_ID_MAIN);

    this->invincibilityTimer = 1000;
    Boss07_SmoothStop(this, 1.0f);
    switch (this->csState) {
        case MAJORAS_WRATH_DEATH_STATE_0:
            if (ActorCutscene_GetCurrentIndex() != -1) {
                break;
            }
            Cutscene_Start(play, &play->csCtx);
            func_800B7298(play, &this->actor, 1);
            this->subCamIndex = Play_CreateSubCamera(play);
            Play_ChangeCameraStatus(play, CAM_ID_MAIN, CAM_STATUS_WAIT);
            Play_ChangeCameraStatus(play, this->subCamIndex, CAM_STATUS_ACTIVE);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_DEAD_ROD);
        case MAJORAS_WRATH_DEATH_STATE_1:
            this->timer_ABC8 = 0;
            this->csState = MAJORAS_WRATH_DEATH_STATE_2;
            this->subCamEye.x = mainCam->eye.x;
            this->subCamEye.y = mainCam->eye.y;
            this->subCamEye.z = mainCam->eye.z;
            this->subCamAt.x = mainCam->at.x;
            this->subCamAt.y = mainCam->at.y;
            this->subCamAt.z = mainCam->at.z;
            this->subCamRotY = this->actor.shape.rot.y * M_PI / 0x8000;
            this->subCamRotVel = this->subCamSpeedMod = sMajoraStatic->lensFlareScale = 0.0f;
            Boss07_InitRand(1, 0x71AC, 0x263A);
            for (i = 0; i < ARRAY_COUNT(this->deathLightScale); i++) {
                this->deathLightScale[i] = Boss07_RandZeroOne() - 1.0f;
            }
            Play_EnableMotionBlur(150);
        case MAJORAS_WRATH_DEATH_STATE_2:
            if (this->timer_ABC8 == 20) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            if (this->timer_ABC8 == 40) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            if (this->timer_ABC8 == 60) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            if (this->timer_ABC8 == 80) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
            }
            spB4.x = 0.0f;
            spB4.y = -90.0f;
            spB4.z = 350.0f;
            this->subCamNextAt.x = this->actor.focus.pos.x;
            this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f;
            this->subCamNextAt.z = this->actor.focus.pos.z;

            if ((this->timer_ABC8 >= 50) && (this->timer_ABC8 < 80)) {
                if (this->timer_ABC8 == 50) {
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_WIND1_OLD);
                }
                spB4.x = 30.0f;
                spB4.z = 120.0f;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f + 30.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            } else if ((this->timer_ABC8 >= 80) && (this->timer_ABC8 < 110)) {
                if (this->timer_ABC8 == 80) {
                    this->skelAnime.curFrame -= 30.0f;
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_WIND2_OLD);
                }
                spB4.x = -10.0f;
                spB4.z = 150.0f;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f - 60.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            } else if ((this->timer_ABC8 >= 110) && (this->timer_ABC8 < 140)) {
                if (this->timer_ABC8 == 110) {
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_WIND3_OLD);
                }
                spB4.x = -70.0f;
                spB4.z = 110.0f;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f + 30.0f;
                spA4 = 200.0f;
                spA0 = 1.0f;
            }
            if (this->timer_ABC8 >= (sREG(15) + 140)) {
                this->csState = MAJORAS_WRATH_DEATH_STATE_4;
                this->subCamEyeModY = sREG(16) + 270.0f + 50.0f;
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_DEAD_FLOAT);
            } else {
                break;
            }
        case MAJORAS_WRATH_DEATH_STATE_4:
            if ((this->timer_ABC8 >= (sREG(90) + 260)) && (this->timer_ABC8 < (sREG(91) + 370))) {
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

                this->bodyDecayRate = KREG(81) + 10;
                this->noShadow = true;
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EV_BURN_OUT - SFX_FLAG);
            } else {
                spB4.x = 0.0f;
                spB4.y = -190.0f;
                spB4.z = 390.0f;
                this->subCamNextAt.x = this->actor.focus.pos.x;
                this->subCamNextAt.y = this->actor.focus.pos.y - 40.0f - 60.0f;
                this->subCamNextAt.z = this->actor.focus.pos.z;
                this->bodyDecayRate = 0;
                if (this->timer_ABC8 > 330) {
                    spA4 = 2000.0f;
                    spA0 = 1.0f;
                }
                Math_ApproachZeroF(&this->actor.world.pos.x, 0.1f, this->subCamSpeedMod);
                Math_ApproachZeroF(&this->actor.world.pos.z, 0.1f, this->subCamSpeedMod);
                Math_ApproachF(&this->subCamSpeedMod, 5.0f, 1.0f, 0.1f);
            }
            if (this->timer_ABC8 >= 260) {
                f32 sp98;
                f32 sp94;
                s16 temp_a0;

                if (this->timer_ABC8 == 260) {
                    func_801A479C(&sSfxPoint, NA_SE_EN_LAST3_DEAD_LIGHTS_OLD, 60);
                }

                play->envCtx.fillScreen = 1;
                play->envCtx.screenFillColor[0] = play->envCtx.screenFillColor[1] = play->envCtx.screenFillColor[2] =
                    255;
                if (this->timer_ABC8 < 350) {
                    sp98 = 0.5f;
                    sp94 = 0.02f;
                    play->envCtx.screenFillColor[3] = 0;
                } else {
                    sp98 = 5.0f;
                    sp94 = 0.1f;
                    temp_a0 = (this->timer_ABC8 * 2) - 700;
                    if (temp_a0 > 250) {
                        temp_a0 = 250;
                    }

                    play->envCtx.screenFillColor[3] = temp_a0;
                    if (this->timer_ABC8 == 400) {
                        func_8019FE74(&gSfxVolume, 0.0f, 90);
                    }
                    if (this->timer_ABC8 == (KREG(94) + 440)) {
                        play->nextEntrance = 0x5400;
                        gSaveContext.nextCutsceneIndex = 0xFFF7;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                    }
                }
                if (this->timer_ABC8 > 300) {
                    sMajoraStatic->lensFlareOn = true;
                    Math_ApproachF(&sMajoraStatic->lensFlareScale, 30.0f, 0.1f, 1.5f);
                    sMajoraStatic->lensFlarePos = this->bodyPartsPos[2];
                    Math_ApproachF(&this->deathOrbScale, 1.0f, 0.1f, 0.05f);
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

            if (this->timer_ABC8 >= (sREG(93) + 180)) {
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
                spA8.x = Math_SinS(this->timer_ABC8 * 0x7000) * sp68;
                spA8.y = Math_SinS(this->timer_ABC8 * 0x5000) * sp68 * 2.5f;
                spA8.z = Math_CosS(this->timer_ABC8 * 0x8000) * sp68;
                for (i = 0; i < 2; i++) {
                    sp6C.x = randPlusMinusPoint5Scaled(500.0f) + this->actor.world.pos.x;
                    sp6C.y = Rand_ZeroFloat(50.0f) + this->actor.world.pos.y + 200.0f;
                    sp6C.z = randPlusMinusPoint5Scaled(500.0f) + this->actor.world.pos.z;
                    EffectSsHahen_Spawn(play, &sp6C, &sp84, &sp78, 0, Rand_ZeroFloat(5.0f) + 20.0f, -1, 10, NULL);
                }
            }
            if (this->timer_ABC8 >= (sREG(94) + 290)) {
                this->bodyDecayRate = KREG(86) + 25;
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
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        Vec3f sp5C;

        sp5C.x = this->subCamAt.x + spA8.x;
        sp5C.y = this->subCamAt.y + spA8.y;
        sp5C.z = this->subCamAt.z + spA8.z;
        Play_SetCameraAtEye(play, this->subCamIndex, &sp5C, &this->subCamEye);
    }
    SkelAnime_Update(&this->skelAnime);
    this->timer_ABC8++;
}

void Boss07_Wrath_SetupIdle(Boss07* this, PlayState* play, s16 delay) {
    this->actionFunc = Boss07_Wrath_Idle;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasWrathIdleAnim, -10.0f);
    if (delay != 0) {
        this->timers[0] = delay;
    } else {
        this->timers[0] = Rand_ZeroFloat(30.0f);
    }
    this->actor.flags |= ACTOR_FLAG_1;
}

void Boss07_Wrath_Idle(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    this->rightWhip.mobility = this->leftWhip.mobility = 0.7f;
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
    this->canDodge = true;
}

void Boss07_Wrath_SetupJump(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_StartJump;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathBackflipAnim, -5.0f);
    this->actionTimer = 0;
}

void Boss07_Wrath_StartJump(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->leftWhip.mobility = this->rightWhip.mobility = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    if (this->actionTimer == 1) {
        this->actor.velocity.y = 35.0f;
        this->actor.world.rot.y = Math_Atan2F_XY(-this->actor.world.pos.z, -this->actor.world.pos.x) * (0x8000 / M_PI);
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
        this->jumpSfxTimer = 5;
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

    temp = this->actor.yawTowardsPlayer - (s16)(Math_Atan2F_XY(dz, dx) * (0x8000 / M_PI));
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
    this->actor.world.rot.y = Math_Atan2F_XY(dz, dx) * (0x8000 / M_PI);
    this->actionTimer = 0;
    this->actor.speedXZ = 17.0f;
}

void Boss07_Wrath_Flip(Boss07* this, PlayState* play) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MIBOSS_JUMP2 - SFX_FLAG);
    SkelAnime_Update(&this->skelAnime);
    this->leftWhip.mobility = this->rightWhip.mobility = 0.7f;
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
        this->jumpSfxTimer = 5;
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
    sp22 = this->actor.yawTowardsPlayer - (s16)(Math_Atan2F_XY(phi_f12, phi_f14) * (0x8000 / M_PI));
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
    this->vel_170 = 0.0f;
    this->timer_ABCC = 0;
}

void Boss07_Wrath_Sidestep(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actionTimer == 20) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_KICK_OLD);
    }
    this->timer_ABCC++;
    if ((this->timer_ABCC % 16) == 0) {
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_WALK2_OLD);
    }
    this->leftWhip.mobility = this->rightWhip.mobility = 0.7f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
    Math_ApproachF(&this->actor.world.pos.x, this->moveTarget.x, 0.8f, this->vel_170);
    Math_ApproachF(&this->actor.world.pos.z, this->moveTarget.z, 0.8f, this->vel_170);
    Math_ApproachF(&this->vel_170, 20.0f, 1.0f, 10.0f);
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
    if (player->stateFlags3 & PLAYER_STATE3_100) {
        this->actionState = MAJORAS_WRATH_SPIN_ATTACK;
    } else if (this->actor.xzDistToPlayer <= 300.0f) {
        if (this->actor.xzDistToPlayer <= 200.0f) {
            this->actionState = MAJORAS_WRATH_KICK;
        } else {
            this->actionState = MAJORAS_WRATH_SPIN_ATTACK;
        }
    } else {
        this->actionState = Rand_ZeroFloat(6.99f);
        if (((s8)this->actor.colChkInfo.health >= 28) &&
            ((this->actionState == MAJORAS_WRATH_FLURRY) || (this->actionState == MAJORAS_WRATH_DOUBLE_WHIP))) {
            this->actionState = MAJORAS_WRATH_QUICK_WHIP;
        }
    }
    switch (this->actionState) {
        case MAJORAS_WRATH_QUICK_WHIP:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathShortSingleWhipAttackAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathShortSingleWhipAttackAnim);
            break;
        case MAJORAS_WRATH_FLURRY:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathWhipFlurryAttackAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathWhipFlurryAttackAnim);
            break;
        case MAJORAS_WRATH_DOUBLE_WHIP:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDoubleWhipAttackAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathDoubleWhipAttackAnim);
            break;
        case MAJORAS_WRATH_LONG_WHIP:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathLongSingleWhipAttackAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathLongSingleWhipAttackAnim);
            break;
        case MAJORAS_WRATH_SPIN_ATTACK:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathSpinAttackAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathSpinAttackAnim);
            Boss07_RandVec3fXZ(&this->moveTarget, 650.0f);
            this->vel_170 = 0.0f;
            break;
        case MAJORAS_WRATH_TAUNT:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathTauntAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathTauntAnim);
            break;
        case MAJORAS_WRATH_THREE_HIT:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathThreeAttackComboAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathThreeAttackComboAnim);
            break;
        case MAJORAS_WRATH_KICK:
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathKickAnim, -5.0f);
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathKickAnim);
            break;
    }
    this->actionTimer = 0;
}

void Boss07_Wrath_Attack(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.mobility = this->rightWhip.mobility = 0.01f * 80;
    this->leftWhip.gravity = this->rightWhip.gravity = -5.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->leftWhip.drag = this->rightWhip.drag = 1.0f;
    if (this->actionTimer > 20) {
        this->canDodge = true;
    }
    switch (this->actionState) {
        case MAJORAS_WRATH_QUICK_WHIP:
            if (this->actionTimer == (s16)(KREG(92) + 1)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if ((this->actionTimer >= 15) && (this->actionTimer < 18)) {
                this->rightWhip.tension = 500.0f;
            }
            if (this->actionTimer == 9) {
                this->whipCrackTimer = 11;
            }
            if (this->actionTimer == 1) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP_OLD);
            }
            if (this->actionTimer == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
            }
            break;
        case MAJORAS_WRATH_FLURRY:
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
        case MAJORAS_WRATH_DOUBLE_WHIP:
            if (this->actionTimer == (s16)(KREG(84) + 5)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if ((this->actionTimer >= 32) && (this->actionTimer <= 38)) {
                this->rightWhip.tension = 300.0f;
                this->leftWhip.tension = 300.0f;
            }
            if (this->actionTimer == 28) {
                this->whipCrackTimer = 11;
            }
            if (this->actionTimer == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_HOP_OLD);
            }
            if (this->actionTimer == 32) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_WIND_OLD);
            }
            break;
        case MAJORAS_WRATH_LONG_WHIP:
            if (this->actionTimer == (s16)(KREG(84) + 5)) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_ROD_OLD);
            }
            if ((this->actionTimer > 30) && (this->actionTimer <= 35)) {
                this->rightWhip.tension = 1200.0f;
            }
            if (this->actionTimer == 23) {
                this->whipCrackTimer = 11;
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
        case MAJORAS_WRATH_SPIN_ATTACK:
            if ((this->actionTimer > 16) && (this->actionTimer <= 40)) {
                this->leftWhip.tension = this->rightWhip.tension = 200.0f;
                if ((this->actionTimer % 8) == 0) {
                    Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_KOMA_OLD);
                }
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_ROD_DANCE_OLD - SFX_FLAG);
                Math_ApproachF(&this->actor.world.pos.x, this->moveTarget.x, 0.1f, this->vel_170);
                Math_ApproachF(&this->actor.world.pos.z, this->moveTarget.z, 0.1f, this->vel_170);
                Math_ApproachF(&this->vel_170, 20.0f, 1.0f, 4.0f);
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x2000);
                this->canDodge = false;
            }
            break;
        case MAJORAS_WRATH_KICK:
            this->canDodge = false;
            if (this->actionTimer == 3) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_KICK_OLD);
            }
            break;
        case MAJORAS_WRATH_TAUNT:
            this->rightWhip.mobility = this->leftWhip.mobility = 0.7f;
            this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            this->canDodge = true;
            break;
        case MAJORAS_WRATH_THREE_HIT:
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
    if (Animation_OnFrame(&this->skelAnime, this->animEndFrame) || (this->timers[1] == 1)) {
        Boss07_Wrath_SetupIdle(this, play, 0);
    }
}

void Boss07_Wrath_SetupGrab(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_Grab;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathGrabAnim, -5.0f);
    this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathGrabAnim);
    this->actionTimer = 0;
}

void Boss07_Wrath_Grab(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer - 0x800, 3, 0x2000);
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.mobility = this->rightWhip.mobility = 0.01f * 80;
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
    player->actor.world.pos = this->whipGrabPos;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->whipCollisionTimer = 20;
    this->whipWrapIndex++;
    if (this->actionTimer > (s16)(46 - this->whipGrabIndex)) {
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_THROW_OLD);
        play_sound(NA_SE_EN_LAST3_COIL_ATTACK_OLD);
        this->actionFunc = Boss07_Wrath_ThrowPlayer;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathThrowAnim, -5.0f);
        this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathThrowAnim);
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
    this->whipCollisionTimer = 20;
    if (this->actionTimer == 6) {
        this->whipGrabIndex = 0;
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
        player->actor.world.pos = this->whipGrabPos;
        if ((func_800B64FC(play, 1000.0f, &this->actor.world.pos, &sp30) >= 0.0f) && (sp30 == 1)) {
            Boss07_Wrath_SetupShock(this, play);
        }
    }
    if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
        Boss07_Wrath_SetupIdle(this, play, 0);
    }
}

void Boss07_Wrath_SetupShock(Boss07* this, PlayState* play) {
    s32 temp_v0;
    s32 temp_v1;

    this->actionFunc = Boss07_Wrath_Shock;

    temp_v0 = this->whipGrabIndex + 10;
    this->whipShockIndexHigh = this->whipShockIndexLow = temp_v0;

    temp_v1 = sWhipSegCount - 1;
    if (temp_v1 < temp_v0) {
        this->whipShockIndexHigh = this->whipShockIndexLow = temp_v1;
    }
    this->actionTimer = 0;
    play_sound(NA_SE_EV_ELECTRIC_EXPLOSION);
}

void Boss07_Wrath_Shock(Boss07* this, PlayState* play) {
    s32 i;
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 2.0f);
    player->actor.world.pos = this->whipGrabPos;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->whipCollisionTimer = 20;
    if (this->actionTimer <= (s16)(46 - this->whipGrabIndex)) {
        this->whipWrapIndex++;
    }
    for (i = 0; i < 4; i++) {
        if (this->whipShockIndexLow != 0) {
            this->whipShockIndexLow--;
        }
    }
    if (this->whipShockIndexLow == 0) {
        Math_ApproachF(&play->envCtx.lightBlend, 1.0f, 1.0f, 0.3f);
        Math_ApproachF(&this->unk_32C, 5.0f, 0.5f, 3.0f);
        play_sound(NA_SE_EN_BIRI_SPARK - SFX_FLAG);
    } else {
        this->unk_32C = 0.01f;
    }
    if (this->unk_32C > 4.0f) {
        this->actionFunc = Boss07_Wrath_ShockStun;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathStunAnim, -10.0f);
        this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathStunAnim);
        this->whipGrabIndex = 0;
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 101;
            player->actor.parent = NULL;
            player->csMode = 0;
        }
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x, this->actor.focus.pos.y - 10.0f,
                    this->actor.focus.pos.z, 0, 0, 0, 4);
        this->actionTimer = 0;
    }
}

void Boss07_Wrath_ShockStun(Boss07* this, PlayState* play) {
    s32 i;

    SkelAnime_Update(&this->skelAnime);
    this->whipCollisionTimer = 20;
    for (i = 0; i < 2; i++) {
        DECR(this->whipShockIndexHigh);
    }
    if (this->actionTimer < 70) {
        Math_ApproachF(&this->unk_32C, 5.0f, 0.5f, 3.0f);
        Math_ApproachF(&this->unk_330, 2.5f, 0.5f, 2.0f);
        play_sound(NA_SE_EN_BIRI_SPARK - SFX_FLAG);
        Math_ApproachF(&play->envCtx.lightBlend, 1.0f, 1.0f, 0.3f);
    }
    if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
        Boss07_Wrath_Dodge(this, play, true);
    }
}

void Boss07_Wrath_SetupStunned(Boss07* this, PlayState* play) {
    if (this->actionFunc != Boss07_Wrath_Stunned) {
        this->actionFunc = Boss07_Wrath_Stunned;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathStunAnim, -10.0f);
        this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathStunAnim);
    }
    this->unk_158 = 10;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_DAMAGE_OLD);
}

void Boss07_Wrath_SetupSpawnTop(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Wrath_SpawnTop;
    Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathReleaseTopAnim, -5.0f);
    this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathReleaseTopAnim);
    this->actionTimer = 0;
}

void Boss07_Wrath_SpawnTop(Boss07* this, PlayState* play) {
    this->whipCollisionTimer = 20;
    if (this->actionTimer < (s16)(KREG(40) + 14)) {
        this->whipTopIndex += 6;
        if (this->whipTopIndex > 44) {
            this->whipTopIndex = 44;
        }
    }
    if (this->actionTimer == 8) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, MAJORAS_TOP);
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
        this->whipTopIndex -= KREG(39) + 5;
        if (this->whipTopIndex < 0) {
            this->whipTopIndex = 0;
        }
    }
    Math_ApproachS(&this->actor.shape.rot.y, KREG(8) * 0x100 + this->actor.yawTowardsPlayer + 0xF00, 3, 0x2000);
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.mobility = this->rightWhip.mobility = 0.01f * 80;
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
    this->leftWhip.mobility = this->rightWhip.mobility = 0.7f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
        Boss07_Wrath_Dodge(this, play, true);
    }
}

void Boss07_Wrath_SetupDamaged(Boss07* this, PlayState* play, u8 damage, u8 dmgEffect) {
    if ((s8)this->actor.colChkInfo.health >= 0) {
        this->actor.colChkInfo.health -= damage;
    }
    if ((s8)this->actor.colChkInfo.health <= 0) {
        if (KREG(19) != 0) {
            Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST3_VOICE_DEAD_OLD);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_DEAD_OLD);
        }
        this->startDeath = true;
        Enemy_StartFinishingBlow(play, &this->actor);
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST3_VOICE_DAMAGE2_OLD);
        if (this->actionFunc != Boss07_Wrath_Damaged) {
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDamageAnim, -10.0f);
            this->actionFunc = Boss07_Wrath_Damaged;
            this->animEndFrame = Animation_GetLastFrame(&gMajorasWrathDamageAnim);
            this->timer_ABCC = 0;
        } else if (dmgEffect == MAJORAS_WRATH_DMGEFF_E) {
            if (this->skelAnime.curFrame <= (this->animEndFrame - 5.0f)) {
                this->unk_158 = 30;
            } else {
                Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasWrathDamageAnim, -5.0f);
            }
        }
    }
}

void Boss07_Wrath_Damaged(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->timer_ABCC++;
    if ((this->timer_ABCC % 16) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WALK2_OLD);
    }
    Boss07_SmoothStop(this, 2.0f);
    this->leftWhip.mobility = this->rightWhip.mobility = 0.7f;
    this->leftWhip.gravity = this->rightWhip.gravity = -15.0f;
    this->leftWhip.drag = this->rightWhip.drag = 2.0f;
    this->leftWhip.tension = this->rightWhip.tension = 0.0f;
    if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
        Boss07_Wrath_Dodge(this, play, true);
    }
}

void Boss07_Wrath_WhipCollisionCheck(Vec3f* whipPos, f32 tension, Boss07* this, PlayState* play) {
    s32 i;
    s32 sp98 = -1;
    Player* player = GET_PLAYER(play);
    f32 dx;
    f32 dy;
    f32 dz;
    Vec3f sp7C;

    if ((tension >= 50.0f) && (this->whipCollisionTimer == 0)) {
        Actor* prop = play->actorCtx.actorLists[ACTORCAT_PROP].first;

        while (prop != NULL) {
            if (prop->id == ACTOR_OBJ_TSUBO) {
                for (i = 10; i < sWhipSegCount; i += 3) {
                    dx = prop->world.pos.x - whipPos[i].x;
                    dy = prop->world.pos.y + 10.0f - whipPos[i].y;
                    dz = prop->world.pos.z - whipPos[i].z;

                    if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < (KREG(38) + 60.0f)) {
                        ((ObjTsubo*)prop)->unk_19B = 1;
                        Boss07_SpawnDustAtPos(play, &prop->world.pos, 10);
                    }
                }
            }
            prop = prop->next;
        }
    }
    if ((tension >= 50.0f) && (this->whipCollisionTimer == 0) &&
        (!(player->stateFlags3 & PLAYER_STATE3_100) || (this->actionState == MAJORAS_WRATH_SPIN_ATTACK))) {
        if ((func_800B64FC(play, 1000.0f, &this->actor.world.pos, &sp98) >= 0.0f) && (sp98 != 1)) {
            sp98 = -1;
        }
        for (i = 10; i < sWhipSegCount; i += 3) {
            dx = player->actor.world.pos.x - whipPos[i].x;
            dy = player->actor.world.pos.y + 30.0f - whipPos[i].y;
            dz = player->actor.world.pos.z - whipPos[i].z;

            dy *= 1.75f;

            if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < 140.0f) {
                if ((this->actionFunc == Boss07_Wrath_Grab) && (sp98 != 1) &&
                    !(player->stateFlags3 & PLAYER_STATE3_1000) && (520.0f <= this->actor.xzDistToPlayer) &&
                    (this->actor.xzDistToPlayer <= 900.0f)) {
                    if (play->grabPlayer(play, player)) {
                        f32 dx1;
                        f32 dy1;
                        f32 dz1;
                        f32 dxz1;

                        player->actor.parent = &this->actor;
                        AudioSfx_PlaySfx(NA_SE_VO_LI_DAMAGE_S, &player->actor.projectedPos, 4,
                                         &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                        this->whipWrapIndex = 0;
                        this->whipGrabIndex = ((this->actor.xzDistToPlayer - 300.0f) / 22.0f) + 10.0f;
                        dx1 = player->actor.world.pos.x - this->rightWhip.basePos.x;
                        dy1 = player->actor.world.pos.y - this->rightWhip.basePos.y + 50.0f;
                        dz1 = player->actor.world.pos.z - this->rightWhip.basePos.z;
                        dxz1 = sqrtf(SQ(dx1) + SQ(dz1));
                        this->unk_F8C = Math_Atan2F_XY(dz1, dx1);
                        this->unk_F90 = -Math_Atan2F_XY(dxz1, dy1);
                        this->actionFunc = Boss07_Wrath_GrabPlayer;
                        this->actionTimer = 0;
                        this->rightWhip.tension = 0.0f;
                        play_sound(NA_SE_EN_LAST3_GET_LINK_OLD);
                    }
                } else if ((player->stateFlags1 & PLAYER_STATE1_400000) && Boss07_IsFacingPlayer(this, play)) {
                    player->unk_B80 = 10.0f;
                    player->unk_B84 = this->actor.yawTowardsPlayer;
                    play_sound(NA_SE_IT_SHIELD_BOUND);
                    this->whipCollisionTimer = 4;
                } else {
                    func_800B8D50(play, NULL, 5.0f, this->actor.shape.rot.y, 0.0f, 8);
                    this->whipCollisionTimer = 20;
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

    if (this->invincibilityTimer == 0) {
        if (this->kickCollider.elements[0].info.toucherFlags & TOUCH_HIT) {
            this->kickCollider.elements[0].info.toucherFlags &= ~TOUCH_HIT;
            player->unk_B84 = this->actor.yawTowardsPlayer;
            player->unk_B80 = 20.0f;
            Boss07_SpawnDustAtPos(play, &player->actor.world.pos, 12);
            play_sound(NA_SE_IT_HOOKSHOT_STICK_OBJ);
        }
        for (i = 0; i < ARRAY_COUNT(this->bodyElements); i++) {
            if (this->bodyCollider.elements[i].info.bumperFlags & BUMP_HIT) {
                for (j = 0; j < ARRAY_COUNT(this->bodyElements); j++) {
                    this->bodyCollider.elements[j].info.bumperFlags &= ~BUMP_HIT;
                }
                if (this->unk_1804 == 10) {
                    this->unk_1806 = 0;
                }
                switch (this->actor.colChkInfo.damageEffect) {
                    case MAJORAS_WRATH_DMGEFF_3:
                        this->unk_1805 = 10;
                        break;
                    case MAJORAS_WRATH_DMGEFF_2:
                        this->unk_1805 = 1;
                        break;
                    case MAJORAS_WRATH_DMGEFF_4:
                        this->unk_1805 = 20;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 4);
                        break;
                    case MAJORAS_WRATH_DMGEFF_A:
                        this->unk_1805 = 40;
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                        break;
                    case MAJORAS_WRATH_DMGEFF_9:
                        this->unk_1805 = 30;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 3, 4);
                        break;
                }
                damage = this->actor.colChkInfo.damage;
                if ((this->actionFunc == Boss07_Wrath_Stunned) || (this->actionFunc == Boss07_Wrath_Damaged)) {
                    if ((this->actionFunc == Boss07_Wrath_Stunned) &&
                        (this->actor.colChkInfo.damageEffect != MAJORAS_WRATH_DMGEFF_E) &&
                        (this->actor.colChkInfo.damageEffect != MAJORAS_WRATH_DMGEFF_D) &&
                        (this->actor.colChkInfo.damageEffect != MAJORAS_WRATH_DMGEFF_9) &&
                        (this->actor.colChkInfo.damageEffect != MAJORAS_WRATH_DMGEFF_C)) {
                        Boss07_Wrath_SetupStunned(this, play);
                        this->invincibilityTimer = 6;
                    } else {
                        this->dmgFogEffectTimer = 15;
                        this->invincibilityTimer =
                            (this->actor.colChkInfo.damageEffect == MAJORAS_WRATH_DMGEFF_C) ? 15 : 5;
                        Boss07_Wrath_SetupDamaged(this, play, damage, this->actor.colChkInfo.damageEffect);
                    }
                } else {
                    this->invincibilityTimer = 15;
                    Boss07_Wrath_SetupStunned(this, play);
                    this->whipGrabIndex = 0;
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
    for (i = 0; i < 2 * ARRAY_COUNT(this->bodyPartsPos); i++) {
        vel.x = randPlusMinusPoint5Scaled(7.0f);
        vel.z = randPlusMinusPoint5Scaled(7.0f);
        vel.y = Rand_ZeroFloat(6.0f) + 4.0f;

        pos.x = this->bodyPartsPos[i / 2].x + vel.x;
        pos.y = this->bodyPartsPos[i / 2].y + vel.y;
        pos.z = this->bodyPartsPos[i / 2].z + vel.z;
        EffectSsEnIce_Spawn(play, &pos, Rand_ZeroFloat(1.0f) + 1.5f, &vel, &sIceAccel, &sLightCyan, &sLightBlue, 30);
    }
}

void Boss07_DamageEffects(Boss07* this, PlayState* play) {
    DECR(this->unk_1806);

    switch (this->unk_1805) {
        case MAJORAS_DAMAGE_STATE_0:
            this->unk_1804 = 0;
            this->unk_1806 = 0;
            this->unk_1800 = 0.0f;
            break;
        case MAJORAS_DAMAGE_STATE_1:
            this->unk_1804 = 0;
            this->unk_1806 = 40;
            this->unk_1800 = 1.0f;
            this->unk_17F8 = 0.0f;
            this->unk_1805++;
            Actor_SetColorFilter(&this->actor, 0x4000, 120, 0, 60);
        case MAJORAS_DAMAGE_STATE_2:
            if (this->unk_1806 == 0) {
                Math_ApproachZeroF(&this->unk_1800, 1.0f, 0.02f);
                if (this->unk_1800 == 0.0f) {
                    this->unk_1805 = 0;
                }
            } else {
                Math_ApproachF(&this->unk_17F8, 1.0f, 0.1f, 0.5f);
            }
            break;
        case MAJORAS_DAMAGE_STATE_10:
            this->unk_1804 = 11;
            this->unk_1806 = 40;
            this->unk_1800 = 1.0f;
            this->unk_17FC = 1.0f;
            this->unk_17F8 = 0.0f;
            this->unk_1805++;
        case MAJORAS_DAMAGE_STATE_11:
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
                case MAJORAS_DAMAGE_STATE_20:
                    this->unk_1804 = 20;
                    this->unk_1806 = 40;
                    this->unk_17F8 = 1.0f;
            } else {
                case MAJORAS_DAMAGE_STATE_30:
                    this->unk_1804 = 21;
                    this->unk_1806 = 40;
                    this->unk_17F8 = 3.0f;
            }
            this->unk_1800 = 1.0f;
            this->unk_1805 = MAJORAS_DAMAGE_STATE_21;
        case MAJORAS_DAMAGE_STATE_21:
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
        case MAJORAS_DAMAGE_STATE_40:
            this->unk_1804 = 30;
            this->unk_1806 = 50;
            this->unk_1800 = 1.0f;
            this->unk_17F8 = (KREG(18) * 0.1f) + 1.0f;
            this->unk_1805++;
        case MAJORAS_DAMAGE_STATE_41:
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
    this->updateWhips = true;
    Math_Vec3f_Copy(&sSfxPoint, &this->actor.projectedPos);
    if (KREG(63) == 0) {
        this->canDodge = false;
        this->actionTimer++;
        Actor_SetScale(&this->actor, 0.015f);
        Math_ApproachZeroF(&this->unk_184, 1.0f, 0.02f);
        Math_ApproachZeroF(&this->unk_188, 1.0f, 0.02f);
        for (i = 0; i < 3; i++) {
            DECR(this->timers[i]);
        }
        DECR(this->whipCollisionTimer);
        DECR(this->unk_158);
        DECR(this->invincibilityTimer);
        DECR(this->dmgFogEffectTimer);
        DECR(this->jumpSfxTimer);

        Math_ApproachZeroF(&this->unk_32C, 1.0f, 0.2f);
        Math_ApproachZeroF(&this->unk_330, 1.0f, 0.04f);
        this->actionFunc(this, play);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 100.0f, 100.0f, 5);
        if (this->whipCrackTimer != 0) {
            this->whipCrackTimer--;
            if ((this->actionFunc == Boss07_Wrath_Attack) && (this->whipCrackTimer == 0)) {
                play_sound(NA_SE_EN_LAST3_ROD_FLOOR_OLD);
            }
        }
    } else {
        sWhipSegCount = 45;
    }
    Boss07_Wrath_WhipCollisionCheck(this->rightWhip.pos, this->rightWhip.tension, this, play);
    Boss07_Wrath_WhipCollisionCheck(this->leftWhip.pos, this->leftWhip.tension, this, play);
    if (this->unk_158 != 0) {
        for (i = 0; i < ARRAY_COUNT(this->bodyElements); i++) {
            this->bodyCollider.elements[i].info.bumperFlags &= ~BUMP_HIT;
        }
    }
    Boss07_Wrath_CollisionCheck(this, play);
    if (this->invincibilityTimer != 0) {
        this->whipTopIndex = 0;
    }
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyCollider.base);
    if ((this->actionFunc == Boss07_Wrath_Attack) && (this->actionState == MAJORAS_WRATH_KICK) &&
        (this->actionTimer >= 6)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->kickCollider.base);
    } else {
        if (this->canDodge && Boss07_IsFacingPlayer(this, play)) {
            if ((player->unk_D57 == 4) && (player->heldItemAction != PLAYER_IA_BOW_LIGHT)) {
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
            if ((player->stateFlags3 & PLAYER_STATE3_1000) && !(player->stateFlags3 & PLAYER_STATE3_80000) &&
                (this->actor.xzDistToPlayer <= 250.0f)) {
                Boss07_Wrath_Dodge(this, play, false);
            }
        }
    }
    if (this->canDodge) {
        Boss07_Wrath_CheckExplosives(this, play);
    }
    Boss07_Wrath_BombWhips(this, play);
    if (KREG(88) || this->startDeath) {
        KREG(88) = false;
        this->startDeath = false;
        Boss07_Wrath_SetupDeath(this, play);
    }
    if (this->bodyDecayRate != 0) {
        u16* sp74 = SEGMENTED_TO_VIRTUAL(gMajorasWrathEarTex);
        u16* sp70 = SEGMENTED_TO_VIRTUAL(gMajoraStripesTex);
        u16* sp6C = SEGMENTED_TO_VIRTUAL(gMajorasWrathMouthTex);
        u16* sp68 = SEGMENTED_TO_VIRTUAL(gMajoraBloodshotEyeTex);
        u16* sp64 = SEGMENTED_TO_VIRTUAL(gMajorasWrathEyeTex);
        u16* sp60 = SEGMENTED_TO_VIRTUAL(gMajorasMaskWithNormalEyesTex);
        u16* sp5C = SEGMENTED_TO_VIRTUAL(gMajoraVeinsTex);
        u16* sp58 = SEGMENTED_TO_VIRTUAL(gMajoraHandTex);
        u16* sp54 = SEGMENTED_TO_VIRTUAL(gMajoraBodyTex);

        for (i = 0; i < this->bodyDecayRate; i++) {
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
    Boss07_DamageEffects(this, play);
    if ((this->jumpSfxTimer == 1) || (this->jumpSfxTimer == 4)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WALK2_OLD);
    }
    if ((player->actor.world.pos.y > 100.0f) && (player->actor.world.pos.z < KREG(82) + -850.0f)) {
        player->actor.world.pos.z = KREG(82) + -850.0f;
    }
    if (player->actor.world.pos.y < -300.0f) {
        player->actor.world.pos.x = player->actor.world.pos.y = player->actor.world.pos.z = 0.0f;
    }
}

/**
 * The whip physics model works by first assuming each point moves freely, using its current velocity and various forces
 * to find the next position. Then, starting from the base of the whip, each point is moved away from the previous point
 * until it is a fixed distance away. The new velocity of each point is found from the scaled difference between its
 * updated position and previous position. The forces applied are
 * - drag, which reduces the magnitude of each velocity component by a fixed amount (or to zero if smaller)
 * - gravity, which applies to the y-component of velocity
 * - tension, an outward force that makes the whip "crack"
 * - additional forces for special movements like wrapping around Link
 * The scaling factor of the velocity is the whip's mobility--how well movements at the base are transmitted to the
 * ends.
 *
 * The algorithm used to implement this physics model is as follows:
 * - Set the position of the 0th point to the position of Wrath's hand (base)
 * - Move each component of each point's velocity towards 0 by drag. Set that component to zero if the magnitude is less
 * than drag.
 * - Calculate the tension force. This points away from Wrath's hand (baserot) for whip movements and towards Link when
 * grabbed
 * - Calculate shaping forces. These are the force from Wrath's hand on the whip base and the force that wraps the whip
 * around Link. Set tension to 0 for the latter segments.
 * - Calculate the provisional position of the point by applying the velocity, forces, and gravity. For the y-component,
 * set a minimum of 2 to not clip through the floor.
 * - Subtract the current position of the previous point along the whip from the calculated position to get the relative
 * vector between them
 * - Set this vector's rotation to the previous point's rot (used by draw so the segments connect).
 * - Calculate a new vector with the same direction and length 22*scale. Add this to the previous point's position to
 * get the final position of the point.
 * - For grab and throw movements, update the position of the grab point.
 * - The point's final velocity is the difference between its current and previous positions, scaled by mobility and
 * with each component's magnitude capped at 200.
 */

void Boss07_Wrath_UpdateWhips(Boss07* this, PlayState* play, Vec3f* base, Vec3f* pos, Vec3f* rot, Vec3f* vel,
                              f32 gravity, f32 mobility, f32 drag, f32 tension, Vec3s* baseRot, s16 grabIndex,
                              f32 scale, s32 hand) {
    s32 i;
    s32 j;
    Vec3f tempPos;
    f32 segYaw;
    f32 tempY;
    Vec3f* vel0 = vel;
    f32 segPitch;
    Vec3f baseSegVec = { 0.0f, 0.0f, 0.0f };
    Vec3f spAC;
    Vec3f segVec;
    Vec3f handForce;
    Vec3f shapeForce;
    Vec3f tensForce;

    baseSegVec.z = 22.0f * scale; // sets the fixed length of each whip segment

    for (i = 0; i < (s16)sWhipSegCount; i++, vel++) {
        if (i == 0) {
            pos[0] = *base;
        } else {
            Math_ApproachF(&vel->x, 0.0f, 1.0f, drag);
            Math_ApproachF(&vel->y, 0.0f, 1.0f, drag);
            Math_ApproachF(&vel->z, 0.0f, 1.0f, drag);
        }
    }
    spAC.z = 20.0f;

    // calculates rotation away from Wrath's hand
    Matrix_RotateYS(baseRot->y, MTXMODE_NEW);
    Matrix_RotateXS(baseRot->x, MTXMODE_APPLY);
    Matrix_RotateZS(baseRot->z, MTXMODE_APPLY);
    Matrix_RotateYS(0x4000, MTXMODE_APPLY);

    Matrix_MultVecZ(spAC.z, &handForce);
    if (grabIndex != 0) {
        spAC.z = 200.0f;
        // replaces the tension direction with the direction from Wrath's hand to Link
        Matrix_RotateYF(this->unk_F8C, MTXMODE_NEW);
        Matrix_RotateXFApply(this->unk_F90);
    } else {
        spAC.z = tension;
    }
    Matrix_MultVecZ(spAC.z, &tensForce);

    pos++;
    rot++;
    vel = vel0 + 1;
    j = 0;

    for (i = 1; i < (s16)sWhipSegCount; i++, vel++, pos++, rot++) {
        if (i < 6) {
            // keeps the whip outward from Wrath's hand near the base
            shapeForce.x = (6 - i) * handForce.x * 0.2f;
            shapeForce.y = (6 - i) * handForce.y * 0.2f;
            shapeForce.z = (6 - i) * handForce.z * 0.2f;
        } else if (grabIndex != 0) {
            // wraps the whip around Link
            if (grabIndex <= i && i < (s16)(grabIndex + this->whipWrapIndex)) {
                shapeForce.y = 0.0f;
                shapeForce.x = sinf(this->actor.yawTowardsPlayer * M_PI / 0x8000 + (j * 1.4f)) * 100.0f;
                shapeForce.z = cosf(this->actor.yawTowardsPlayer * M_PI / 0x8000 + (j * 1.4f)) * 100.0f;
                tensForce = gZeroVec3f;
                j++;
            }
        } else {
            shapeForce = gZeroVec3f;
        }

        // Advances the physics one frame to find the provisional position relative to the previous point
        tempPos.x = pos->x + vel->x - (pos - 1)->x + shapeForce.x + tensForce.x;
        tempY = pos->y + vel->y + gravity + shapeForce.y + tensForce.y;
        if (tempY < 2.0f) {
            tempY = 2.0f;
        }
        // tempY = CLAMP_MIN(tempY, 2.0f);
        tempPos.y = tempY - (pos - 1)->y;
        tempPos.z = pos->z + vel->z - (pos - 1)->z + shapeForce.z + tensForce.z;

        // calculates the rotation angles from the previous point
        segYaw = Math_Atan2F_XY(tempPos.z, tempPos.x);
        segPitch = -Math_Atan2F_XY(sqrtf(SQ(tempPos.x) + SQ(tempPos.z)), tempPos.y);
        (rot - 1)->y = segYaw;
        (rot - 1)->x = segPitch;

        // Sets the position to be in the same direction as the provisional position relative to the previous point, but
        // a fixed distance away
        Matrix_RotateYF(segYaw, MTXMODE_NEW);
        Matrix_RotateXFApply(segPitch);
        Matrix_MultVecZ(baseSegVec.z, &segVec);
        // if (1) {}

        tempPos.x = pos->x;
        tempPos.y = pos->y;
        tempPos.z = pos->z;

        pos->x = (pos - 1)->x + segVec.x;
        pos->y = (pos - 1)->y + segVec.y;
        pos->z = (pos - 1)->z + segVec.z;

        if ((i != 0) && (i == grabIndex)) {
            // Updates the grab point for when Link is grabbed
            spAC.x = 15.0f;
            spAC.y = -30.0f;
            spAC.z = -12.0f;
            Matrix_MultVec3f(&spAC, &segVec);
            this->whipGrabPos.x = pos->x + segVec.x;
            this->whipGrabPos.y = pos->y + segVec.y;
            this->whipGrabPos.z = pos->z + segVec.z;
        } else if ((hand == RIGHT_HAND) && (this->actionFunc == Boss07_Wrath_SpawnTop)) {
            // Updates the grab point when throwing a top
            if (i == KREG(90) + sWhipSegCount - this->whipTopIndex + 1) {
                spAC.x = KREG(60);
                spAC.y = KREG(61);
                spAC.z = KREG(62);
                Matrix_MultVec3f(&spAC, &segVec);
                this->whipGrabPos.x = pos->x + segVec.x;
                this->whipGrabPos.y = pos->y + segVec.y;
                this->whipGrabPos.z = pos->z + segVec.z;
            }
        }

        // calculates the velocity for the next frame
        vel->x = (pos->x - tempPos.x) * mobility;
        vel->y = (pos->y - tempPos.y) * mobility;
        vel->z = (pos->z - tempPos.z) * mobility;

#define CLAMP_VAR(x, xmin, xmax) \
    if (x > (xmax))              \
        x = (xmax);              \
    if (x < (xmin))              \
    x = (xmin)

        // if (vel->x > 200.0f) vel->x = 200.0f;if (vel->x < -200.0f) vel->x = -200.0f;
        CLAMP_VAR(vel->x, -200.0f, 200.0f);
        CLAMP_VAR(vel->y, -200.0f, 200.0f);
        CLAMP_VAR(vel->z, -200.0f, 200.0f);
        // if (vel->x > 200.0f) {
        //     vel->x = 200.0f;
        // }
        // if (vel->x < -200.0f) {
        //     vel->x = -200.0f;
        // }
        // if (vel->y > 200.0f) {
        //     vel->y = 200.0f;
        // }
        // if (vel->y < -200.0f) {
        //     vel->y = -200.0f;
        // }
        // if (vel->z > 200.0f) {
        //     vel->z = 200.0f;
        // }
        // if (vel->z < -200.0f) {
        //     vel->z = -200.0f;
        // }
    }
}

void Boss07_Wrath_DrawWhips(Boss07* this, PlayState* play, Vec3f* pos, Vec3f* rot, f32 zScale, s32 hand) {
    s32 topSegIndex;
    s32 i;
    f32 xyScale;
    s32 pad[2];
    Vec3f* vec2 = pos;
    Vec3f* vec3 = rot;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasMaskWhipShadowMaterialDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sREG(48) + 45, 35, 75, 255);
    topSegIndex = (hand == RIGHT_HAND) ? this->whipTopIndex : 0;
    for (i = 0; i < (sWhipSegCount - topSegIndex) - 1; i++, pos++, rot++) {
        Matrix_Translate(pos->x, 0.0f, pos->z, MTXMODE_NEW);
        Matrix_Scale(1.0f, 0.0f, 1.0f, MTXMODE_APPLY);
        Matrix_RotateYF(rot->y, MTXMODE_APPLY);
        Matrix_RotateXFApply(rot->x);
        xyScale = (i > 24) ? 0.025f : ((f32)(24 - i) * 1 * 0.001f) + 0.025f;
        Matrix_Scale(xyScale, xyScale, ((2 * zScale) + 0.5f) * 0.01f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathWhipModelDL);
    }
    pos = vec2;
    rot = vec3;
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathWhipMaterialDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 155, 155, 80, 255);
    for (i = 0; i < (sWhipSegCount - topSegIndex) - 1; i++, pos++, rot++) {
        Matrix_Translate(pos->x, pos->y, pos->z, MTXMODE_NEW);
        Matrix_RotateYF(rot->y, MTXMODE_APPLY);
        Matrix_RotateXFApply(rot->x);
        xyScale = (i > 24) ? 0.025f : ((f32)(24 - i) * 1 * 0.001f) + 0.025f;
        Matrix_Scale(xyScale, xyScale, ((2 * zScale) + 0.5f) * 0.01f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathWhipModelDL);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

s32 Boss07_Wrath_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_WRATH_LIMB_HEAD) {
        rot->x += this->csHeadRot.y;
        rot->y += this->csHeadRot.x;
        rot->z += this->csHeadRot.z;
    }
    return false;
}

typedef enum {
    MAJORAS_WRATH_PART_NONE = -1,
    MAJORAS_WRATH_PART_HEAD,
    MAJORAS_WRATH_PART_TORSO,
    MAJORAS_WRATH_PART_PELVIS,
    MAJORAS_WRATH_PART_LEFT_UPPER_ARM,
    MAJORAS_WRATH_PART_LEFT_LOWER_ARM_ROOT,
    MAJORAS_WRATH_PART_LEFT_FOREARM,
    MAJORAS_WRATH_PART_RIGHT_UPPER_ARM,
    MAJORAS_WRATH_PART_RIGHT_LOWER_ARM_ROOT,
    MAJORAS_WRATH_PART_RIGHT_FOREARM,
    MAJORAS_WRATH_PART_RIGHT_THIGH,
    MAJORAS_WRATH_PART_RIGHT_SHIN,
    MAJORAS_WRATH_PART_RIGHT_FOOT,
    MAJORAS_WRATH_PART_LEFT_THIGH,
    MAJORAS_WRATH_PART_LEFT_SHIN,
    MAJORAS_WRATH_PART_LEFT_FOOT,
    MAJORAS_WRATH_PART_MAX,
} MajorasWrathBodyPart;

// typedef enum MajorasWrathLimbs {
//     /* -1 */ MAJORAS_WRATH_LIMB_NONE,
//     /* -1 */ MAJORAS_WRATH_LIMB_ROOT,
//     /*  2 */ MAJORAS_WRATH_LIMB_PELVIS,
//     /* -1 */ MAJORAS_WRATH_LIMB_LEFT_LEG_ROOT,
//     /* 12 */ MAJORAS_WRATH_LIMB_LEFT_THIGH,
//     /* -1 */ MAJORAS_WRATH_LIMB_LEFT_LOWER_LEG_ROOT,
//     /* 13 */ MAJORAS_WRATH_LIMB_LEFT_SHIN,
//     /* 14 */ MAJORAS_WRATH_LIMB_LEFT_FOOT,
//     /* -1 */ MAJORAS_WRATH_LIMB_RIGHT_LEG_ROOT,
//     /*  9 */ MAJORAS_WRATH_LIMB_RIGHT_THIGH,
//     /* -1 */ MAJORAS_WRATH_LIMB_RIGHT_LOWER_LEG_ROOT,
//     /* 10 */ MAJORAS_WRATH_LIMB_RIGHT_SHIN,
//     /* 11 */ MAJORAS_WRATH_LIMB_RIGHT_FOOT,
//     /* -1 */ MAJORAS_WRATH_LIMB_TORSO_ROOT,
//     /*  1 */ MAJORAS_WRATH_LIMB_TORSO,
//     /* -1 */ MAJORAS_WRATH_LIMB_RIGHT_ARM_ROOT,
//     /*  6 */ MAJORAS_WRATH_LIMB_RIGHT_UPPER_ARM,
//     /*  7 */ MAJORAS_WRATH_LIMB_RIGHT_LOWER_ARM_ROOT,
//     /*  8 */ MAJORAS_WRATH_LIMB_RIGHT_FOREARM,
//     /* -1 */ MAJORAS_WRATH_LIMB_RIGHT_HAND,
//     /* -1 */ MAJORAS_WRATH_LIMB_LEFT_ARM_ROOT,
//     /*  3 */ MAJORAS_WRATH_LIMB_LEFT_UPPER_ARM,
//     /*  4 */ MAJORAS_WRATH_LIMB_LEFT_LOWER_ARM_ROOT,
//     /*  5 */ MAJORAS_WRATH_LIMB_LEFT_FOREARM,
//     /* -1 */ MAJORAS_WRATH_LIMB_LEFT_HAND,
//     /* -1 */ MAJORAS_WRATH_LIMB_HEAD_ROOT,
//     /*  0 */ MAJORAS_WRATH_LIMB_HEAD,
//     /* -1 */ MAJORAS_WRATH_LIMB_THIRD_EYE,
//     /* -1 */ MAJORAS_WRATH_LIMB_MAX
// } MajorasWrathLimbs;



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
    s8 index;
    Vec3f colliderPos;
    MtxF curMtxF;

    index = sWrathBodyParts[limbIndex];
    if (index >= 0) {
        Matrix_MultZero(&this->bodyPartsPos[index]);
    }
    index = sLimbColliderIndex[limbIndex];
    if (index >= 0) {
        if (this->unk_158 != 0) {
            Matrix_MultVecZ(100000.0f, &colliderPos);
        } else {
            Matrix_MultVec3f(&sWrathColliderOffsets[index], &colliderPos);
        }
        Boss07_UpdateSpheres(index, &this->bodyCollider, &colliderPos);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_HEAD) {
        Matrix_MultZero(&this->actor.focus.pos);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_HAND) {
        Matrix_MultVec3f(&sWhipOffset, &this->rightWhip.basePos);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_LOWER_ARM_ROOT) {
        Matrix_Get(&curMtxF);
        Matrix_MtxFToYXZRot(&curMtxF, &this->rightWhip.baseRot, false);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_LEFT_HAND) {
        Matrix_MultVec3f(&sWhipOffset, &this->leftWhip.basePos);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_LEFT_LOWER_ARM_ROOT) {
        Matrix_Get(&curMtxF);
        Matrix_MtxFToYXZRot(&curMtxF, &this->leftWhip.baseRot, false);
    }
    if (limbIndex == MAJORAS_WRATH_LIMB_RIGHT_FOOT) {
        Matrix_MultZero(&colliderPos);
        Boss07_UpdateSpheres(0, &this->kickCollider, &colliderPos);
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
        Matrix_Scale(1.0f, this->armScale, this->armScale, MTXMODE_APPLY);
    }
}

void Boss07_Wrath_DrawShocks(Boss07* this, PlayState* play) {
    s32 i;
    GraphicsContext* gfxCtx;

    OPEN_DISPS(gfxCtx = play->state.gfxCtx);
    if ((this->unk_32C > 0.0f) || (this->unk_330 > 0.0f)) {
        func_8012C2DC(play->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 0, 0);

        if (this->unk_32C > 0.0f) {
            gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);
            for (i = 0; i < ARRAY_COUNT(this->bodyPartsPos); i++) {
                Matrix_Translate(this->bodyPartsPos[i].x, this->bodyPartsPos[i].y, this->bodyPartsPos[i].z,
                                 MTXMODE_NEW);
                Matrix_ReplaceRotation(&play->billboardMtxF);
                Matrix_Scale(this->unk_32C, this->unk_32C, this->unk_32C, MTXMODE_APPLY);
                Matrix_RotateZF(Rand_ZeroFloat(2.0f * M_PI), MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
            }
            for (i = this->whipShockIndexHigh; i >= this->whipShockIndexLow; i--) {
                Matrix_Translate(this->rightWhip.pos[i].x, this->rightWhip.pos[i].y, this->rightWhip.pos[i].z, 0);
                Matrix_ReplaceRotation(&play->billboardMtxF);
                Matrix_Scale(1.5f, 1.5f, 1.5f, MTXMODE_APPLY);
                Matrix_RotateZF(Rand_ZeroFloat(2.0f * M_PI), MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
            }
        }
        if (this->unk_330 > 0.0f) {
            gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial2DL);
            for (i = 0; i < 2 * ARRAY_COUNT(this->bodyPartsPos); i++) {
                Matrix_Translate(this->bodyPartsPos[i / 2].x + randPlusMinusPoint5Scaled(30.0f),
                                 this->bodyPartsPos[i / 2].y + randPlusMinusPoint5Scaled(30.0f),
                                 this->bodyPartsPos[i / 2].z + randPlusMinusPoint5Scaled(30.0f), MTXMODE_NEW);
                Matrix_Scale(this->unk_330, this->unk_330, this->unk_330, MTXMODE_APPLY);
                Matrix_RotateXFApply(Rand_ZeroFloat(2.0f * M_PI));
                Matrix_RotateZF(Rand_ZeroFloat(2.0f * M_PI), MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
            }
        }
    }
    CLOSE_DISPS(gfxCtx);
}

void Boss07_Wrath_DrawDeathLights(Boss07* this, PlayState* play, Vec3f* pos) {
    s32 i;
    f32 temp_f12_2;
    f32 temp_f20;
    GraphicsContext* gfxCtx;
    s16* temp;

    OPEN_DISPS(gfxCtx = play->state.gfxCtx);

    if (this->deathOrbScale > 0.0f) {
        Boss07_InitRand(1, 0x71B8, 0x263A);
        POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);
        gDPSetCombineMode(POLY_XLU_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        for (i = 0; i < ARRAY_COUNT(this->deathLightScale); i++) {
            temp = sShotEnvColors[0];
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, temp[0], temp[1], temp[2], 40);
            temp_f20 = (Boss07_RandZeroOne() * 40.0f) - 30.0f;
            Matrix_Translate(this->bodyPartsPos[2].x, this->bodyPartsPos[2].y - 30.0f + 50.0f + temp_f20 + 25.0f,
                             this->bodyPartsPos[2].z, MTXMODE_NEW);
            Matrix_Translate(pos->x, pos->y + temp_f20, pos->z, MTXMODE_NEW);
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
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, (u8)(220 + sREG(18)), (u8)(170 + sREG(16)));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, (u8)(100 + sREG(22)), 128);

        Matrix_Translate(this->bodyPartsPos[2].x, this->bodyPartsPos[2].y, this->bodyPartsPos[2].z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_RotateZS(play->gameplayFrames * 0x80, MTXMODE_APPLY);
        temp_f12_2 = (sREG(17) + 800) * 0.01f * this->deathOrbScale;
        Matrix_Scale(temp_f12_2, temp_f12_2, 1.0f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
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

    if (this->introOrbScale > 0.0f) {
        func_8012C2DC(play->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (u8)(sREG(52) + 255));
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 0, 0);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);

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

        Matrix_Scale(this->introOrbScale, this->introOrbScale, this->introOrbScale, MTXMODE_APPLY);
        Matrix_RotateZS(play->gameplayFrames * 0x40, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
    }
    CLOSE_DISPS(gfxCtx);
}

void Boss07_Wrath_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    u8* shadowTex = GRAPH_ALLOC(play->state.gfxCtx, sizeof(u8[0x40][0x40]));

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    if ((this->dmgFogEffectTimer % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    Matrix_RotateYF(this->unk_184, MTXMODE_APPLY);
    Matrix_RotateXFApply(this->unk_188);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, Boss07_Wrath_OverrideLimbDraw, Boss07_Wrath_PostLimbDraw,
                                   Boss07_Wrath_TransformLimbDraw, &this->actor);
    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);

    if (((KREG(63) == 0) || (KREG(63) == 2)) && this->updateWhips) {
        Boss07_Wrath_UpdateWhips(this, play, &this->rightWhip.basePos, this->rightWhip.pos, this->rightWhip.rot,
                                 this->rightWhip.vel, this->rightWhip.gravity, this->rightWhip.mobility,
                                 this->rightWhip.drag, this->rightWhip.tension, &this->rightWhip.baseRot,
                                 this->whipGrabIndex, this->whipScale, RIGHT_HAND);
        Boss07_Wrath_UpdateWhips(this, play, &this->leftWhip.basePos, this->leftWhip.pos, this->leftWhip.rot,
                                 this->leftWhip.vel, this->leftWhip.gravity, this->leftWhip.mobility,
                                 this->leftWhip.drag, this->leftWhip.tension, &this->leftWhip.baseRot, 0,
                                 this->whipScale, LEFT_HAND);
    }
    Boss07_Wrath_DrawWhips(this, play, this->rightWhip.pos, this->rightWhip.rot, this->whipScale, RIGHT_HAND);
    Boss07_Wrath_DrawWhips(this, play, this->leftWhip.pos, this->leftWhip.rot, this->whipScale, LEFT_HAND);
    if (!this->noShadow) {
        Boss07_Wrath_MakeShadowTex(shadowTex, this, play);
        Boss07_Wrath_DrawShadowTex(shadowTex, this, play);
    }
    Boss07_Wrath_DrawShocks(this, play);
    {
        Vec3f sp58;
        sp58.x = this->bodyPartsPos[2].x;
        sp58.y = this->bodyPartsPos[2].y - 30.0f + 50.0f;
        sp58.z = this->bodyPartsPos[2].z;
        Boss07_Wrath_DrawDeathLights(this, play, &sp58);
    }
    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, 15, this->unk_17F8, this->unk_17FC, this->unk_1800,
                            this->unk_1804);
    this->updateWhips = false;
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
            temp_t0 = (u16)(s32)(sp68.x + 32);
            temp_t1 = (u16)((s32)sp68.y * 64);

            if (sShadowSize[i] == 2) {
                for (j = 0, phi_a3 = -6 * 0x40; j < ARRAY_COUNT(sShadowWidths12); j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths12[j]; phi_a0 < sShadowWidths12[j]; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x40 * 0x40)) {
                            shadowTex[temp_v0] = 255;
                        }
                    }
                }
            } else if (sShadowSize[i] == 1) {
                for (j = 0, phi_a3 = -4 * 0x40; j < ARRAY_COUNT(sShadowWidths8); j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths8[j]; phi_a0 < sShadowWidths8[j]; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x40 * 0x40)) {
                            shadowTex[temp_v0] = 255;
                        }
                    }
                }
            } else if (sShadowSize[i] == 0) {
                for (j = 0, phi_a3 = -3 * 0x40; j < ARRAY_COUNT(sShadowWidths7); j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths7[j]; phi_a0 < sShadowWidths7[j] - 1; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x40 * 0x40)) {
                            shadowTex[temp_v0] = 255;
                        }
                    }
                }
            } else {
                for (j = 0, phi_a3 = -2 * 0x40; j < ARRAY_COUNT(sShadowWidths6); j++, phi_a3 += 0x40) {
                    for (phi_a0 = -sShadowWidths6[j]; phi_a0 < sShadowWidths6[j] - 1; phi_a0++) {
                        temp_v0 = temp_t0 + phi_a0 + temp_t1 + phi_a3;
                        if ((temp_v0 >= 0) && (temp_v0 < 0x40 * 0x40)) {
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

    for (i = 0; i < 0x40 * 0x40 / (s32)sizeof(s32); i++, shadowTex32++) {
        *shadowTex32 = 0;
    }
    // angle of light source
    Matrix_RotateXFNew(1.0f);
    for (i = 0; i <= 5; i++) {
        Boss07_Wrath_MakeShadowCircles(this, shadowTex, i / 5.0f);
    }
}

void Boss07_Wrath_DrawShadowTex(u8* shadowTex, Boss07* this, PlayState* play) {
    s32 pad[2];
    f32 phi_f0;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    phi_f0 = (400.0f - this->actor.world.pos.y) * 0.0025f;
    phi_f0 = CLAMP_MIN(phi_f0, 0.0f);
    phi_f0 = CLAMP_MAX(phi_f0, 1.0f); // could be variant of clamp_var
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(s32)(phi_f0 * 80.0f) & 0xFF);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    Matrix_Translate(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z - 20.0f, MTXMODE_NEW);
    Matrix_Scale(1.75f, 1.0f, 1.75f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathShadowMaterialDL);
    gDPLoadTextureBlock(POLY_OPA_DISP++, shadowTex, G_IM_FMT_I, G_IM_SIZ_8b, 0x40, 0x40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathShadowModelDL);
    CLOSE_DISPS(gfxCtx);
}

void Boss07_Incarnation_AvoidPlayer(Boss07* this) {
    s32 phi_v0 = (Rand_ZeroOne() < 0.5f) ? 0x4000 : -0x4000;

    Matrix_RotateYS(this->actor.yawTowardsPlayer + phi_v0, MTXMODE_NEW);
    Matrix_MultVecZ(200.0f, &this->moveTarget);
    this->timers[1] = 30;
    this->moveTarget.x += this->actor.world.pos.x;
    this->moveTarget.z += this->actor.world.pos.z;
    this->vel_170 = 0x4E20;
}

void Boss07_Incarnation_SetupIntro(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Intro;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationJerkingAnim, 0.0f);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->csHeadRot.x = 0x6E00;
}

void Boss07_Incarnation_Intro(Boss07* this, PlayState* play) {
    s32 i;
    f32 sp58;

    SkelAnime_Update(&this->skelAnime);
    this->timer_ABC8++;
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    sp58 = Math_SinS(this->actionTimer * 0x4500) * 0.3f;
    switch (this->csState) {
        case MAJORAS_INCARNATION_INTRO_STATE_0:
            this->timer_ABC8 = 0;
            this->csState = MAJORAS_INCARNATION_INTRO_STATE_1;
            this->subCamNextAt.z = 0.0f;
        case MAJORAS_INCARNATION_INTRO_STATE_1:
            this->csState = MAJORAS_INCARNATION_INTRO_STATE_2;
            this->timer_ABC8 = 0;
            this->subCamNextEye.x = 70.0f;
            this->subCamNextEye.y = 70.0f;
            this->subCamNextEye.z = 150.0f;
            this->subCamNextAt.x = 20.0f;
            this->subCamNextAt.y = 80.0f;
            break;
        case MAJORAS_INCARNATION_INTRO_STATE_2:
            if (this->timer_ABC8 >= 20) {
                if (this->timer_ABC8 == 20) {
                    this->unk_17C8[3] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(&this->unk_17B8[3], 1.0f + (this->unk_17C8[3] * sp58), 1.0f, 0.5f);
            }
            if (this->timer_ABC8 > 40) {
                this->csState = MAJORAS_INCARNATION_INTRO_STATE_3;
                this->timer_ABC8 = 0;
            }
            break;
        case MAJORAS_INCARNATION_INTRO_STATE_3:
            Math_ApproachF(&this->subCamNextEye.x, 0.0f, 0.05f, this->subCamSpeedMod * 40.0f);
            Math_ApproachF(&this->subCamNextEye.y, 100.0f, 0.05f, this->subCamSpeedMod * 30.0f);
            Math_ApproachF(&this->subCamNextEye.z, 270.0f, 0.05f, this->subCamSpeedMod * 150.0f);
            Math_ApproachF(&this->subCamNextAt.x, 0.0f, 0.05f, this->subCamSpeedMod * 20.0f);
            Math_ApproachF(&this->subCamNextAt.y, 100.0f, 0.05f, this->subCamSpeedMod * 20.0f);
            Math_ApproachF(&this->subCamSpeedMod, 0.05f, 1.0f, 0.002f);
            if (this->timer_ABC8 >= 20) {
                if (this->timer_ABC8 == 20) {
                    this->unk_17C8[2] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(&this->unk_17B8[2], 1.0f + (this->unk_17C8[2] * sp58), 1.0f, 0.5f);
            }
            if (this->timer_ABC8 >= 50) {
                if (this->timer_ABC8 == 50) {
                    this->unk_17C8[1] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(&this->unk_17B8[1], 1.0f + (this->unk_17C8[1] * sp58), 1.0f, 0.5f);
            }
            if (this->timer_ABC8 >= 60) {
                if (this->timer_ABC8 == 60) {
                    this->unk_17C8[0] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_TRANSFORM);
                }
                Math_ApproachF(&this->unk_17B8[0], 1.0f + (this->unk_17C8[0] * sp58), 1.0f, 0.5f);
            }
            if (this->timer_ABC8 == 80) {
                this->csState = MAJORAS_INCARNATION_INTRO_STATE_4;
                this->timer_ABC8 = 0;
                for (i = 0; i < ARRAY_COUNT(this->unk_17B8); i++) {
                    this->unk_17B8[i] = 1.0f;
                }
            }
            break;
        case MAJORAS_INCARNATION_INTRO_STATE_4:
            this->subCamNextEye.x = 0.0f;
            this->subCamNextEye.y = 120.0f;
            this->subCamNextEye.z = 140.0f;
            this->subCamNextAt.y = 170.0f;
            if (this->timer_ABC8 >= 10) {
                if (this->timer_ABC8 == 10) {
                    this->unk_17C8[3] = 1.0f;
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_GROW_HEAD);
                }
                Math_ApproachS(&this->csHeadRot.x, (this->unk_17C8[3] * sp58) * 0x6000, 1, 0x4000);
            }
            if (this->timer_ABC8 == 30) {
                this->csState = MAJORAS_INCARNATION_INTRO_STATE_5;
                this->timer_ABC8 = 0;
                this->subCamSpeedMod = 0.0f;
                this->animEndFrame = 1000.0f;
                Play_DisableMotionBlur();
            }
            break;
        case MAJORAS_INCARNATION_INTRO_STATE_5:
            if (this->timer_ABC8 == 20) {
                Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationIntroDanceAnim, 0.0f);
                this->animEndFrame = Animation_GetLastFrame(&gMajorasIncarnationIntroDanceAnim);
            }
            if (this->timer_ABC8 >= 20) {
                sREG(28) = this->timer_ABC8;
                if ((this->timer_ABC8 == (KREG(16) + 28)) || (this->timer_ABC8 == (KREG(17) + 60))) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_UAUOO2_OLD);
                }
                if ((this->timer_ABC8 == (KREG(18) + 38)) || (this->timer_ABC8 == (KREG(19) + 48)) ||
                    (this->timer_ABC8 == (KREG(20) + 68)) || (this->timer_ABC8 == (KREG(21) + 78))) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_GYM_B_OLD);
                }
                if (this->timer_ABC8 == (KREG(38) + 93)) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_UAUOO_OLD);
                }
            }
            if (this->timer_ABC8 == 45) {
                TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt,
                                       Lib_SegmentedToVirtual(&gMajorasIncarnationTitleCardTex), 0xA0, 0xB4, 0x80,
                                       0x28);
            }
            if (this->timer_ABC8 == 20) {
                Audio_QueueSeqCmd(NA_BGM_MAJORAS_INCARNATION | 0x8000);
                this->envEffectOn = 1;
                play->envCtx.lightBlend = 0.0f;
            }
            Math_ApproachF(&this->subCamNextEye.x, -80.0f, 0.05f, this->subCamSpeedMod * 80.0f);
            Math_ApproachF(&this->subCamNextEye.y, 20.0f, 0.05f, this->subCamSpeedMod * 60.0f);
            Math_ApproachF(&this->subCamNextEye.z, 220.0f, 0.05f, this->subCamSpeedMod * 180.0f);
            Math_ApproachF(&this->subCamNextAt.y, 110.0f, 0.05f, this->subCamSpeedMod * 80.0f);
            Math_ApproachF(&this->subCamSpeedMod, 0.1f, 1.0f, 0.005f);
            if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
                Camera* mainCam = Play_GetCamera(play, CAM_ID_MAIN);

                this->csState = MAJORAS_INCARNATION_INTRO_STATE_0;
                Boss07_Incarnation_SetupTaunt(this, play);
                mainCam->eye = this->subCamEye;
                mainCam->eyeNext = this->subCamEye;
                mainCam->at = this->subCamAt;
                func_80169AFC(play, this->subCamIndex, 0);
                this->subCamIndex = SUB_CAM_ID_DONE;
                Cutscene_End(play, &play->csCtx);
                func_800B7298(play, &this->actor, 6);
                this->actor.flags |= ACTOR_FLAG_1;
            }
            break;
    }
    for (i = 0; i < ARRAY_COUNT(this->unk_17C8); i++) {
        Math_ApproachZeroF(&this->unk_17C8[i], 0.5f, 0.1f);
    }
    Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
    Matrix_MultVec3f(&this->subCamNextAt, &this->subCamAt);
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        ShrinkWindow_Letterbox_SetSizeTarget(0x1B);
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
    this->actor.flags |= ACTOR_FLAG_1;
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
    Boss07_Incarnation_SpawnDust(this, play, 1, false);
}

void Boss07_Incarnation_SetupStunned(Boss07* this, PlayState* play, s16 stunTime) {
    if (this->actionFunc != Boss07_Incarnation_Stunned) {
        this->actionFunc = Boss07_Incarnation_Stunned;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationFallOverStartAnim, -10.0f);
        this->animEndFrame = Animation_GetLastFrame(&gMajorasIncarnationFallOverStartAnim);
    }
    this->unk_158 = 10;
    this->timers[0] = stunTime;
    this->timers[1] = 12;
}

void Boss07_Incarnation_Stunned(Boss07* this, PlayState* play) {
    this->actor.shape.shadowAlpha = 0;
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 1.0f);
    if (this->timers[1] == 1) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_HIPLOOP_LAND);
    }
    if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
        Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationFallOverLoopAnim, -5.0f);
        this->animEndFrame = 1000.0f;
    }
    if (this->animEndFrame == 1000.0f) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_BIRD_OLD - SFX_FLAG);
    }
    if (this->timers[0] == 0) {
        Boss07_Incarnation_SetupTaunt(this, play);
    }
    Boss07_Incarnation_SpawnDust(this, play, 1, true);
}

void Boss07_Incarnation_SetupDamaged(Boss07* this, PlayState* play, u8 damage, u8 dmgEffect) {
    if (this->actionFunc != Boss07_Incarnation_Damaged) {
        this->actionFunc = Boss07_Incarnation_Damaged;
        Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationDamageAnim, -2.0f);
        this->animEndFrame = Animation_GetLastFrame(&gMajorasIncarnationDamageAnim);
    } else if (dmgEffect == MAJORAS_INCARNATION_DMGEFF_E) {
        if (this->skelAnime.curFrame <= (this->animEndFrame - 5.0f)) {
            this->unk_158 = 30;
            this->invincibilityTimer = 30;
        } else {
            Animation_MorphToPlayOnce(&this->skelAnime, &gMajorasIncarnationDamageAnim, -2.0f);
        }
    }

    if (this->actor.colChkInfo.health != 0) {
        this->actor.colChkInfo.health -= damage;
        if ((s8)this->actor.colChkInfo.health <= 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_DEAD_OLD);
            this->startDeath = true;
            this->invincibilityTimer = 100;
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
    if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
        Boss07_Incarnation_SetupRun(this, play);
    }
    Boss07_Incarnation_SpawnDust(this, play, 1, false);
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
    this->timer_AB40++;
    if (this->timer_AB40 >= 2) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_WALK2_OLD);
        this->timer_AB40 = 0;
    }
    SkelAnime_Update(&this->skelAnime);
    if ((func_800B64FC(play, 5.0f, &this->actor.world.pos, &sp2C) >= 0.0f) && (sp2C == 0)) {
        Boss07_Incarnation_SetupStunned(this, play, 50);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_DAMAGE_OLD);
    } else {
        sp34 = this->moveTarget.x - this->actor.world.pos.x;
        sp30 = this->moveTarget.z - this->actor.world.pos.z;
        if ((this->timers[1] == 0) || (SQ(sp34) + SQ(sp30) < 30000.0f)) { // dist ~ 173.2
            if (Rand_ZeroOne() < 0.3f) {
                f32 rand = Rand_ZeroOne();

                if (rand < 0.25f) {
                    Boss07_Incarnation_SetupAttack(this, play);
                } else if (rand < 0.5f) {
                    Boss07_Incarnation_SetupHopak(this, play);
                } else if (rand < 0.75f) {
                    Boss07_Incarnation_SetupMoonwalk(this, play);
                } else if (rand < 1.0f) {
                    Boss07_Incarnation_SetupPirouette(this, play);
                }
            } else if (Rand_ZeroOne() < 0.01f) {
                Boss07_Incarnation_SetupStunned(this, play, 50);
            } else {
                Boss07_RandVec3fXZ(&this->moveTarget, 500.0f);
                this->timers[1] = Rand_ZeroFloat(50.0f) + 20.0f;
                this->vel_170 = 0.0f;
            }
        }
        Math_ApproachS(&this->actor.world.rot.y, Math_Atan2S(sp34, sp30), 5, this->vel_170);
        Math_ApproachF(&this->vel_170, 0xFA0, 1.0f, 0x1F4);
        Math_ApproachF(&this->actor.speedXZ, 25.0f, 1.0f, 20.0f);
        if (this->timers[0] == 0) {
            Boss07_Incarnation_SetupTaunt(this, play);
        }
        if ((this->actor.xzDistToPlayer < 200.0f) && (this->timers[2] == 0)) {
            Boss07_Incarnation_AvoidPlayer(this);
            this->timers[0] = 50;
            this->timers[2] = 50;
        }
        Boss07_Incarnation_SpawnDust(this, play, 3, false);
        this->timer_18D6 = 5;
    }
}

void Boss07_Incarnation_SetupAttack(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Attack;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationEnergyBallAttackAnim, -5.0f);
    this->timers[0] = Rand_ZeroFloat(50.0f) + 30.0f;
    this->eyeBeamsZscale = 0.0f;
}

void Boss07_Incarnation_Attack(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 3.0f);
    Math_ApproachS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 3, 0x3000);
    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->incLeftHandPos.x, this->incLeftHandPos.y,
                    this->incLeftHandPos.z, 0, 0, 0, MAJORAS_INCARNATION_SHOT);
    }
    if (Animation_OnFrame(&this->skelAnime, 9.0f)) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->incRightHandPos.x, this->incRightHandPos.y,
                    this->incRightHandPos.z, 0, 0, 0, MAJORAS_INCARNATION_SHOT);
    }
    if (this->timers[0] == 0) {
        Boss07_Incarnation_SetupRun(this, play);
    }
    Boss07_Incarnation_SpawnDust(this, play, 1, false);
}

void Boss07_Incarnation_SetupHopak(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Incarnation_Hopak;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationSquattingDanceAnim, -5.0f);
    this->timers[0] = Rand_ZeroFloat(100.0f) + 100.0f;
    this->timers[1] = 0;
    this->timer_ABC8 = 0;
}

void Boss07_Incarnation_Hopak(Boss07* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        if ((this->timer_ABC8 % 2) == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_UAUOO1_OLD);
        } else {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_VOICE_UAUOO2_OLD);
        }
        Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST2_JUMP_OLD);
        this->timer_ABC8++;
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
    Boss07_Incarnation_SpawnDust(this, play, 7, false);
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
                this->unk_180 = randPlusMinusPoint5Scaled(0x10000);
            } else {
                this->unk_180 = this->actor.yawTowardsPlayer + 0x8000;
            }
        }
        if (this->actor.bgCheckFlags & 8) {
            this->timers[1] = 20;
            this->unk_180 = this->actor.yawTowardsPlayer + 0x8000;
        }
    }
    Math_ApproachS(&this->actor.world.rot.y, this->unk_180, 0xA, 0x1000);
    if (this->timers[0] == 0) {
        Boss07_Incarnation_SetupRun(this, play);
    }
    Boss07_Incarnation_SpawnDust(this, play, 7, false);
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
    this->animEndFrame = Animation_GetLastFrame(&gMajorasIncarnationDamageAnim);
    this->csState = MAJORAS_INCARNATION_DEATH_STATE_0;
    this->timer_ABC8 = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->invincibilityTimer = 20;
}

void Boss07_Incarnation_Death(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u8 sp4B = 0;

    this->invincibilityTimer = 20;
    this->timer_ABC8++;
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 3.0f);
    switch (this->csState) {
        case MAJORAS_INCARNATION_DEATH_STATE_0:
            if (ActorCutscene_GetCurrentIndex() != -1) {
                break;
            }
            Cutscene_Start(play, &play->csCtx);
            func_800B7298(play, &this->actor, 7);
            this->subCamIndex = Play_CreateSubCamera(play);
            Play_ChangeCameraStatus(play, CAM_ID_MAIN, CAM_STATUS_WAIT);
            Play_ChangeCameraStatus(play, this->subCamIndex, CAM_STATUS_ACTIVE);
            this->timer_ABC8 = 0;
            this->csState = MAJORAS_INCARNATION_DEATH_STATE_10;
            Play_EnableMotionBlur(150);
        case MAJORAS_INCARNATION_DEATH_STATE_10:
            sHeartbeatTimer = 5;
            this->subCamNextEye.x = 0.0f;
            this->subCamNextEye.y = 30.0f;
            this->subCamNextEye.z = 210.0f;
            this->subCamNextAt.x = 0.0f;
            this->subCamNextAt.y = 150.0f;
            this->subCamNextAt.z = 0.0f;
            Math_ApproachF(&this->actor.world.pos.x, 0.0f, 0.1f, 5.0f);
            Math_ApproachF(&this->actor.world.pos.z, 0.0f, 0.1f, 5.0f);
            if (Animation_OnFrame(&this->skelAnime, this->animEndFrame)) {
                this->timer_ABC8 = 0;
                this->csState = MAJORAS_INCARNATION_DEATH_STATE_1;
                Animation_MorphToLoop(&this->skelAnime, &gMajorasIncarnationFinalHitAnim, -5.0f);
            }
            break;
        case MAJORAS_INCARNATION_DEATH_STATE_1:
            sHeartbeatTimer = 5;
            this->subCamNextAt.y = (Math_SinS(this->timer_ABC8 * 0x700) * 15.0f) + 150.0f;
            if (this->timer_ABC8 == 40) {
                this->timer_ABC8 = 0;
                this->csState = MAJORAS_INCARNATION_DEATH_STATE_2;
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
        case MAJORAS_INCARNATION_DEATH_STATE_2:
            sHeartbeatTimer = 5;
            sp4B = 1;
            if (this->timer_ABC8 == 40) {
                this->timer_ABC8 = 0;
                this->csState = MAJORAS_INCARNATION_DEATH_STATE_3;
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
        case MAJORAS_INCARNATION_DEATH_STATE_3:
            sHeartbeatTimer = 5;
            sp4B = 1;
            if (this->timer_ABC8 == 40) {
                this->timer_ABC8 = 0;
                this->csState = MAJORAS_INCARNATION_DEATH_STATE_4;
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
        case MAJORAS_INCARNATION_DEATH_STATE_4:
            sHeartbeatTimer = 5;
            sp4B = 2;
            if (this->timer_ABC8 == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_PUMP_UP_OLD);
            }
            if (this->timer_ABC8 == 40) {
                Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 0, 0, this->subCamIndex, MAJORAS_WRATH);
                Actor_Kill(&this->actor);
            }
            break;
    }
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
    Matrix_MultVec3f(&this->subCamNextAt, &this->subCamAt);
    if (sp4B == 1) {
        this->armScale = (Math_SinS(this->timer_ABC8 * 0x3000) * this->unk_17EC) + this->unk_17E8;
        Math_ApproachF(&this->unk_17E8, 2.0f, 1.0f, 0.05f);
        Math_ApproachZeroF(&this->unk_17EC, 1.0f, 0.01f);
    } else if (sp4B == 2) {
        this->legScale = (Math_SinS(this->timer_ABC8 * 0x3000) * this->unk_17EC) + this->unk_17E8;
        Math_ApproachF(&this->unk_17E8, 2.0f, 1.0f, 0.05f);
        Math_ApproachZeroF(&this->unk_17EC, 1.0f, 0.01f);
    }
    this->chestScaleY = (Math_SinS(this->timer_ABC8 * 0x2000) * 0.1f) + 1.0f;
    this->chestScaleX = (Math_CosS(this->timer_ABC8 * 0x2000) * 0.1f) + 1.0f;
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        ShrinkWindow_Letterbox_SetSizeTarget(0x1B);
        Play_SetCameraAtEye(play, this->subCamIndex, &this->subCamAt, &this->subCamEye);
    }
}

void Boss07_Incarnation_CollisionCheck(Boss07* this, PlayState* play) {
    s32 i;
    s32 j;
    u8 damage;

    if (this->invincibilityTimer == 0) {
        for (i = 0; i < ARRAY_COUNT(this->bodyElements); i++) {
            if (this->bodyCollider.elements[i].info.bumperFlags & BUMP_HIT) {
                for (j = 0; j < ARRAY_COUNT(this->bodyElements); j++) {
                    this->bodyCollider.elements[j].info.bumperFlags &= ~BUMP_HIT;
                }
                if (this->unk_1804 == 10) {
                    this->unk_1806 = 0;
                }
                switch (this->actor.colChkInfo.damageEffect) {
                    case MAJORAS_INCARNATION_DMGEFF_3:
                        this->unk_1805 = 10;
                        break;
                    case MAJORAS_INCARNATION_DMGEFF_2:
                        this->unk_1805 = 1;
                        break;
                    case MAJORAS_INCARNATION_DMGEFF_4:
                        this->unk_1805 = 20;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, 4);
                        break;
                    case MAJORAS_INCARNATION_DMGEFF_A:
                        this->unk_1805 = 40;
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
                        break;
                    case MAJORAS_INCARNATION_DMGEFF_9:
                        this->unk_1805 = 30;
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                    this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 3, 4);
                        break;
                }

                if ((this->actionFunc == Boss07_Incarnation_Stunned) ||
                    (this->actionFunc == Boss07_Incarnation_Damaged)) {
                    this->invincibilityTimer =
                        (this->actor.colChkInfo.damageEffect == MAJORAS_INCARNATION_DMGEFF_C) ? 15 : 5;
                    damage = this->actor.colChkInfo.damage;
                    Boss07_Incarnation_SetupDamaged(this, play, damage, this->actor.colChkInfo.damageEffect);
                    this->dmgFogEffectTimer = 15;
                } else {
                    this->invincibilityTimer = 15;
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
        Actor_Kill(&this->actor);
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
    if (this->envEffectOn == 1) {
        s32 pad;

        Math_ApproachF(&play->envCtx.lightBlend, 1.0f, 1.0f, 0.1f);
        if (play->envCtx.lightBlend == 1.0f) {
            play->envCtx.lightBlend = 0.0f;
            this->envEffectTimer++;
            if (this->envEffectTimer >= 8) {
                this->envEffectTimer = 0;
            }
        }
        play->envCtx.unk_C2 = D_80A08198[this->envEffectTimer];
        play->envCtx.unk_C1 = D_80A081A0[this->envEffectTimer];
    }
    Math_ApproachF(&play->envCtx.lightBlend, 0.0f, 1.0f, 0.03f);
    if (KREG(63) == 0) {
        this->canDodge = false;
        this->actor.shape.shadowAlpha = 130;
        for (i = 0; i < ARRAY_COUNT(this->timers); i++) {
            DECR(this->timers[i]);
        }
        DECR(this->invincibilityTimer);
        DECR(this->dmgFogEffectTimer);
        DECR(this->unk_158);
        DECR(this->timer_18D6);

        Math_ApproachZeroF(&this->unk_330, 1.0f, 0.04f);
        this->actionFunc(this, play);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 200.0f, 100.0f, 5);
        if (this->startDeath || KREG(88)) {
            KREG(88) = false;
            this->startDeath = false;
            Audio_QueueSeqCmd(NA_BGM_STOP | 0x10000);
            Boss07_Incarnation_SetupDeath(this, play);
        }
    }
    if (this->unk_158 != 0) {
        for (i = 0; i < ARRAY_COUNT(this->bodyElements); i++) {
            this->bodyCollider.elements[i].info.bumperFlags &= ~BUMP_HIT;
        }
    }
    Boss07_Incarnation_CollisionCheck(this, play);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyCollider.base);
    if (this->actionFunc != Boss07_Incarnation_Pirouette) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 1, 0x1000);
    }
    if ((this->timer_18D6 != 0) && !(this->actionTimer & 1)) {
        Boss07* afterimage = (Boss07*)Actor_SpawnAsChild(
            &play->actorCtx, &this->actor, play, ACTOR_BOSS_07, this->actor.world.pos.x, this->actor.world.pos.y,
            this->actor.world.pos.z, this->actor.world.rot.x, this->actor.world.rot.y, 7, MAJORAS_AFTERIMAGE);

        if (afterimage != NULL) {
            for (i = 0; i < MAJORAS_INCARNATION_LIMB_MAX; i++) {
                afterimage->skelAnime.jointTable[i] = this->skelAnime.jointTable[i];
            }
        }
    }
    Boss07_DamageEffects(this, play);
}

void Boss07_Afterimage_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    Boss07* sp34 = (Boss07*)this->actor.parent;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 100, 155, 900, 1099);
    SkelAnime_DrawFlexOpa(play, sp34->skelAnime.skeleton, this->skelAnime.jointTable, sp34->skelAnime.dListCount, NULL,
                          NULL, &this->actor);
    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
    CLOSE_DISPS(play->state.gfxCtx);
}

s32 Boss07_Incarnation_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                        Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_INCARNATION_LIMB_EYESTALK) {
        rot->y += this->csHeadRot.x;
    }
    return false;
}

// #define IDENTITY(...) __VA_ARGS__
// #define GROUP(...) __VA_ARGS__
// #define EVAL3(x) GROUP(x)
// #define EVAL2(x) EVAL3(EVAL3(EVAL3(GROUP(x))))
// #define EVAL1(x) EVAL2(EVAL2(EVAL2(GROUP(x))))
// #define EVAL(x) EVAL1(EVAL1(EVAL1(GROUP(x))))

// #define MAP_OUT
// #define MAP_END(a,b,...) b
// #define MAP_NULL(...) 
// #define END_TEST(com) 0 , com
// #define GET_SECOND(a, b, ...) b
// #define GET_COMMAND(com, ecom, a, b, ...) GET_SECOND MAP_OUT (END_TEST b (ecom) , com)

// #define CHECK_ARR_VAL_R(val, i, ...) ((val == i) ? 0 : (1 + VALIDATE_ARR MAP_OUT (val, __VA_ARGS__ - 1)))
// #define VALIDATE_ARR(val, ...) (GET_COMMAND (CHECK_ARR_VAL_R, MAP_END, __VA_ARGS__, )  (val, __VA_ARGS__))
// #define CHECK_ARR_VAL(val, ...) CHECK_ARR_VAL_R(val, __VA_ARGS__, -1)

// #define INVERT_ARRAY_R(vals, n, b, ...)   CHECK_ARR_VAL(n, IDENTITY vals) , VALIDATE_INVERSE MAP_OUT (vals, n b, __VA_ARGS__) 
// #define VALIDATE_INVERSE(vals, n, ...) GET_COMMAND  (INVERT_ARRAY_R, MAP_NULL, __VA_ARGS__, )  (vals, n, __VA_ARGS__)
// #define INVERT_ARRAY(count, ...) INVERT_ARRAY_R((__VA_ARGS__), 0, +1, COUNTER_##count)

// #define COUNTER_30 +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1, +1

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
        -1, 4,  5,  -1, 12, -1, 13, 14, 0,  -1, -1, -1, -1, -1
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
        Boss07_UpdateSpheres(i, &this->bodyCollider, &sp28);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_FOOT) {
        Matrix_MultZero(&this->incFeetPos[0]);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_FOOT) {
        Matrix_MultZero(&this->incFeetPos[1]);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_HAND) {
        Matrix_MultZero(&this->incRightHandPos);
    }
    if (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_HAND) {
        Matrix_MultZero(&this->incLeftHandPos);
    }
    i = sLimbPumpIndex[limbIndex];
    if (i >= 0) {
        Matrix_Scale(this->unk_17B8[i], this->unk_17B8[i], this->unk_17B8[i], MTXMODE_APPLY);
    }
}

void Boss07_Incarnation_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_INCARNATION_LIMB_MASK) {
        Matrix_Scale(this->chestScaleX, this->chestScaleY, 1.0f, MTXMODE_APPLY);
    }
    if ((limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_UPPER_ARM) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_FOREARM) || (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_HAND) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_FOREARM) || (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_HAND)) {
        Matrix_Scale(1.0f, this->armScale, this->armScale, MTXMODE_APPLY);
    }
    if ((limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_THIGH) || (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_SHIN) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_RIGHT_FOOT) || (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_THIGH) ||
        (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_SHIN) || (limbIndex == MAJORAS_INCARNATION_LIMB_LEFT_FOOT)) {
        Matrix_Scale(1.0f, this->legScale, this->legScale, MTXMODE_APPLY);
    }
}

void Boss07_Incarnation_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    if ((this->dmgFogEffectTimer % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, Boss07_Incarnation_OverrideLimbDraw,
                                   Boss07_Incarnation_PostLimbDraw, Boss07_Incarnation_TransformLimbDraw, &this->actor);
    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
    Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, 0xF, this->unk_17F8, this->unk_17FC, this->unk_1800,
                            this->unk_1804);
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Mask_SetupIdle(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Idle;
    Animation_MorphToLoop(&this->skelAnime, &gMajorasMaskFloatingAnim, -20.0f);
    this->timers[2] = Rand_ZeroFloat(150.0f) + 60.0f;
    this->tentLengthScale = 1.0f;
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
            if (((s8)this->actor.colChkInfo.health <= 8) && (player->transformation != PLAYER_FORM_FIERCE_DEITY) &&
                (Rand_ZeroOne() < 0.75f)) {
                Boss07_Mask_SetupBeam(this, play);
            } else {
                Boss07_Mask_SetupSpin(this, play);
            }
        } else if (Rand_ZeroOne() < 0.15f) {
            this->flySpeedTarget = 2.0f;
            this->timers[0] = Rand_ZeroFloat(50.0f) + 30.0f;
        } else {
            Boss07_RandVec3fXZ(&this->moveTarget, 500.0f);
            this->moveTarget.y = Rand_ZeroFloat(350.0f) + 100.0f;
            this->timers[0] = Rand_ZeroFloat(50.0f) + 20.0f;
            this->vel_170 = 0.0f;
            this->flySpeedTarget = Rand_ZeroFloat(12.0f) + 3.0f;
        }
    }
    sp30 = this->moveTarget.x - this->actor.world.pos.x;
    sp2C = this->moveTarget.y - this->actor.world.pos.y;
    sp28 = this->moveTarget.z - this->actor.world.pos.z;
    sp34 = Math_Atan2S(sp30, sp28);
    sp36 = Math_Atan2S(sp2C, sqrtf(SQ(sp30) + SQ(sp28)));
    sp36 += (s16)(Math_SinS(this->actionTimer * 0x1388) * 0xFA0);
    Math_ApproachS(&this->actor.world.rot.y, sp34, 0xA, this->vel_170);
    Math_ApproachS(&this->actor.world.rot.x, sp36, 5, this->vel_170);
    Math_ApproachF(&this->vel_170, 0x7D0, 1.0f, 0x64);
    Math_ApproachF(&this->actor.speedXZ, this->flySpeedTarget, 1.0f, 1.0f);
    if (this->timers[1] != 0) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x3000);
    } else if (this->flySpeedTarget < 7.0f) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x2000);
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 5, 0x2000);
    }
    if ((player->unk_D57 == 4) && (Rand_ZeroOne() < 0.8f)) {
        this->timers[1] = 20;
    }
    Math_ApproachS(&this->actor.shape.rot.x, 0, 0xA, 0x200);
    Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x400);
    if (this->startDeath || KREG(88)) {
        KREG(88) = false;
        this->startDeath = false;
        Audio_QueueSeqCmd(NA_BGM_STOP | 0x10000);
        Boss07_Mask_SetupDeath(this, play);
    }
}

void Boss07_Mask_SetupSpin(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Spin;
    this->actionState = MAJORAS_MASK_SPIN_START;
    this->csState = 0;
    this->timers[0] = 30;
    this->spinVel = 0;
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

    this->actor.shape.rot.z -= this->spinVel;
    switch (this->actionState) {
        case MAJORAS_MASK_SPIN_START:
            Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            Boss07_SmoothStop(this, 1.0f);
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 0xA, 0x100);
            Math_ApproachS(&this->spinVel, 0x2000, 1, 0x100);
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_SPIN_ATTACK;
                this->actor.world.rot.x = 0;
                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                this->timers[0] = 100;
                this->timers[1] = 20;
                this->vel_170 = 0.0f;
            }
            break;
        case MAJORAS_MASK_SPIN_ATTACK:
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 0xA, 0x400);
            Math_ApproachS(&this->spinVel, 0x2000, 1, 0x200);
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
            Math_ApproachS(&this->actor.world.rot.y, sp34, 0xA, this->vel_170);
            Math_ApproachS(&this->actor.world.rot.x, sp36, 0xA, this->vel_170);
            Math_ApproachF(&this->vel_170, 0xBB8, 1.0f, 0x64);
            Math_ApproachF(&this->actor.speedXZ, 20.0f, 1.0f, 2.0f);
            if (((this->csState == 0) && (sp24 < 100.0f)) || (this->timers[0] == 0)) {
                if (Rand_ZeroOne() < 0.25f) {
                    this->actionState = MAJORAS_MASK_SPIN_END;
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
                    this->vel_170 = 0.0f;
                }
            }
            break;
        case MAJORAS_MASK_SPIN_END:
            Math_ApproachS(&this->spinVel, 0, 1, 0x100);
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
    this->vel_170 = 0.0f;
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
    Math_ApproachF(&this->actor.world.pos.y, 50.0f + 10.0f * Math_SinS(this->actionTimer * 0x5DC), 0.1f, this->vel_170);
    Math_ApproachF(&this->vel_170, 15.0f, 1.0f, 1.0f);

    if ((this->timers[0] > 30) || ((this->timers[0] & 2) != 0)) {
        this->maskEyeState = 1;
    }
    if (this->timers[0] == 0) {
        Boss07_Mask_SetupIdle(this, play);
        this->timers[2] = 100;
    }
}

void Boss07_Mask_SetupDamaged(Boss07* this, PlayState* play, u8 damage, Actor* hitActor) {
    Player* player = GET_PLAYER(play);

    this->actionFunc = Boss07_Mask_Damaged;
    this->timers[0] = 40;
    if (damage) {
        this->actor.speedXZ = 30.0f;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x8000;
        this->spinVel = 0x1500;
    } else {
        if (player->stateFlags3 & PLAYER_STATE3_200) {
            this->actor.speedXZ = 20.0f;
            this->actor.velocity.y = 20.0f;
        } else {
            this->actor.speedXZ = 13.0f;
            this->actor.velocity.y = 10.0f;
            if (hitActor != NULL) {
                this->actor.world.rot.y = hitActor->world.rot.y;
            }
        }
        this->spinVel = 0x1000;
    }
    this->actor.colChkInfo.health -= damage;
    if ((s8)this->actor.colChkInfo.health <= 0) {
        this->timers[0] = 30;
    }
    this->timers[1] = 30;
}

void Boss07_Mask_Damaged(Boss07* this, PlayState* play) {
    this->invincibilityTimer = 20;
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        Boss07_SmoothStop(this, 1.0f);
        Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 1, 0x1000);
        Math_ApproachS(&this->spinVel, 0, 1, 0x100);
    } else {
        this->actor.shape.rot.x += 0x2000;
    }
    this->actor.shape.rot.z += this->spinVel;
    if ((this->timers[0] > 30) || ((this->timers[0] & 2) != 0)) {
        this->maskEyeState = 1;
    }
    if ((this->timers[0] == 15) && ((s8)this->actor.colChkInfo.health < 10)) {
        this->activateRemains = true;
    }
    if (this->timers[0] == 0) {
        Boss07_Mask_SetupIdle(this, play);
        if ((s8)this->actor.colChkInfo.health <= 0) {
            this->startDeath = true;
            Enemy_StartFinishingBlow(play, &this->actor);
            AudioSfx_StopByPos(&this->actor.projectedPos);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEAD_OLD);
        } else {
            this->moveTarget.x = this->actor.world.pos.x;
            this->moveTarget.y = 200.0f;
            this->moveTarget.z = this->actor.world.pos.z;
            this->actor.world.rot.x = 0x3000;
            this->timers[0] = 50;
            this->timers[2] = 100;
            this->flySpeedTarget = 6.0f;
            this->vel_170 = 0.0f;
        }
    }
}

void Boss07_Mask_ClearBeam(Boss07* this) {
    this->eyeBeamsZscale = 0.0f;
    this->beamFocusOrbScale = 0.0f;
    this->unk_1894 = 0.0f;
    this->beamXYscale = 0.0f;
    this->unk_18C0 = 0.0f;
}

void Boss07_Mask_SetupBeam(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Mask_Beam;
    this->actionState = MAJORAS_MASK_BEAM_CHARGE;
    this->timers[0] = 30;
    this->vel_170 = 0.0f;
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
    Vec3f beamMarkPos;
    u8 sp14B = 0;
    s32 sp144;

    this->invincibilityTimer = 20;
    Boss07_SmoothStop(this, 0.5f);
    Math_ApproachF(&this->actor.world.pos.y, 300.0f, 0.05f, 1.0f);
    Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x400);
    if ((player->targetedActor != NULL) && (player->stateFlags1 & PLAYER_STATE1_400000)) {
        phi_f24 = (player->transformation == PLAYER_FORM_HUMAN) ? 20 : 30.0f;
    } else {
        phi_f24 = (player->transformation == PLAYER_FORM_HUMAN) ? 8.0f : 15.0f;
    }
    phi_s0 = (player->stateFlags1 & PLAYER_STATE1_400000) ? 1 : 10;
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, phi_s0, this->vel_170);
    temp_f20 = player->actor.world.pos.x - this->actor.world.pos.x;
    temp_f12 = player->actor.world.pos.y - this->actor.world.pos.y + phi_f24;
    temp_f22 = player->actor.world.pos.z - this->actor.world.pos.z;
    Math_ApproachS(&this->actor.shape.rot.x, -Math_Atan2S(temp_f12, sqrtf(SQ(temp_f20) + SQ(temp_f22))), phi_s0,
                   this->vel_170);
    Math_ApproachF(&this->vel_170, 0xFA0, 1.0f, 0xC8);
    this->unk_1874 = 1;
    switch (this->actionState) {
        case MAJORAS_MASK_BEAM_CHARGE:
            if (this->timers[0] == 25) {
                Audio_PlaySfxAtPos(&sSfxPoint, NA_SE_EN_LAST1_BLOW_OLD);
            }
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_BEAM_EYES;
                this->timers[0] = 6;
                this->beamXYscale = 1.0f;
            }
            break;
        case MAJORAS_MASK_BEAM_EYES:
            Math_ApproachF(&this->eyeBeamsZscale, 1.0f, 1.0f, 0.2f);
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_BEAM_FOCUS;
                this->timers[0] = 8;
            }
            break;
        case MAJORAS_MASK_BEAM_FOCUS:
            play_sound(NA_SE_EN_LAST1_BEAM_OLD - SFX_FLAG);
            Math_ApproachF(&this->beamFocusOrbScale, 1.0f, 0.2f, 0.2f);
            if (this->timers[0] == 0) {
                this->actionState = MAJORAS_MASK_BEAM_ACTIVE;
                this->timers[0] = 100;
            }
            break;
        case MAJORAS_MASK_BEAM_ACTIVE:
        case MAJORAS_MASK_BEAM_REFLECT:
            play_sound(NA_SE_EN_LAST1_BEAM_OLD - SFX_FLAG);
        case MAJORAS_MASK_BEAM_END:
            Math_ApproachF(&this->beamFocusOrbScale, 1.0f, 0.2f, 0.2f);
            temp_f20 = player->actor.world.pos.x - this->unk_189C.x;
            temp_f12 = player->actor.world.pos.y - this->unk_189C.y + 20.0f;
            temp_f22 = player->actor.world.pos.z - this->unk_189C.z;
            sp180 = sqrtf(SQ(temp_f20) + SQ(temp_f12) + SQ(temp_f22));
            Math_ApproachF(&this->unk_1894, sp180 * 0.2f, 1.0f, 7.0f);

            if (BgCheck_EntityLineTest1(&play->colCtx, &this->unk_189C, &this->unk_18A8, &beamMarkPos, &sp158, 1, 1, 1,
                                        1, &sp144) &&
                (this->actionState != MAJORAS_MASK_BEAM_END)) {
                Vec3f sp138;
                Vec3f sp12C;
                Vec3f sp120;

                sp138.x = randPlusMinusPoint5Scaled(20.0f) + beamMarkPos.x;
                sp138.y = randPlusMinusPoint5Scaled(20.0f) + beamMarkPos.y;
                sp138.z = randPlusMinusPoint5Scaled(20.0f) + beamMarkPos.z;
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
                    (player->stateFlags1 & PLAYER_STATE1_400000) &&
                    (FACING_ANGLE(&player->actor, &this->actor) < 0x2000) &&
                    (FACING_ANGLE(&player->actor, &this->actor) > -0x2000)) {
                    Vec3s sp118;

                    this->unk_1894 = sp180 * 0.05f;
                    Math_ApproachF(&this->unk_18C0, sp180 * 0.2f, 1.0f, 7.0f);
                    Matrix_MtxFToYXZRot(&player->shieldMf, &sp118, 0);
                    sp118.y += 0x8000;
                    sp118.x = -sp118.x;
                    if (this->actionState == MAJORAS_MASK_BEAM_ACTIVE) {
                        this->actionState = MAJORAS_MASK_BEAM_REFLECT;
                        this->beamTargetPitch = sp118.x;
                        this->beamTargetYaw = sp118.y;
                    } else {
                        player->unk_B84 = this->actor.yawTowardsPlayer;
                        player->unk_B80 = this->beamXYscale * 0.5f;
                        sMajoraStatic->lensFlareOn = true;
                        sMajoraStatic->lensFlareScale = this->beamXYscale * 30.0f;
                        sMajoraStatic->lensFlarePos = this->unk_18A8;
                        Math_ApproachS(&this->beamTargetPitch, sp118.x, 2, 0x2000);
                        Math_ApproachS(&this->beamTargetYaw, sp118.y, 2, 0x2000);
                        sp16C.x = this->actor.world.pos.x - this->unk_18A8.x;
                        sp16C.y = this->actor.world.pos.y - this->unk_18A8.y;
                        sp16C.z = this->actor.world.pos.z - this->unk_18A8.z;
                        sp180 = sqrtf(SQXYZ(sp16C));
                        Matrix_RotateXS(-this->beamTargetPitch, MTXMODE_NEW);
                        Matrix_RotateYS(-this->beamTargetYaw, MTXMODE_APPLY);
                        Matrix_Push();
                        Matrix_MultVec3f(&sp16C, &sp160);
                        if ((fabsf(sp160.x) < 60.0f) && (fabsf(sp160.y) < 60.0f) && (sp160.z > 40.0f) &&
                            (sp160.z <= (this->unk_18C0 * 16.666668f)) &&
                            (this->actionState != MAJORAS_MASK_BEAM_END)) {
                            s32 phi_s0_2;
                            Vec3f sp108;
                            Vec3f spFC;
                            Vec3f spF0;

                            this->beamDmgTimer += 2;
                            this->unk_18C0 = sp180 * 0.062f;
                            if (this->beamDmgTimer < 10) {
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
                                this->dmgFogEffectTimer |= 0xA;
                            } else {
                                this->invincibilityTimer = 50;
                                this->dmgFogEffectTimer = 15;
                                AudioSfx_StopByPos(&this->actor.projectedPos);
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
                                    this->timer_18D6 = 200;
                                } else {
                                    this->timer_18D6 = 60;
                                }
                            }
                        }
                        Matrix_Pop();
                        for (sp178 = 0; sp178 < ARRAY_COUNT(sBossRemains); sp178++) {
                            if (sBossRemains[sp178]->actionState >= MAJORAS_REMAINS_DEATH) {
                                continue;
                            }
                            sp16C.x = sBossRemains[sp178]->actor.world.pos.x - this->unk_18A8.x;
                            sp16C.y = sBossRemains[sp178]->actor.world.pos.y - this->unk_18A8.y;
                            sp16C.z = sBossRemains[sp178]->actor.world.pos.z - this->unk_18A8.z;
                            sp180 = sqrtf(SQXYZ(sp16C));
                            Matrix_MultVec3f(&sp16C, &sp160);
                            if ((fabsf(sp160.x) < 60.0f) && (fabsf(sp160.y) < 60.0f) && (sp160.z > 40.0f) &&
                                (sp160.z <= (this->unk_18C0 * 16.666668f)) &&
                                (this->actionState != MAJORAS_MASK_BEAM_END)) {
                                s32 pad;
                                Vec3f spE0;
                                Vec3f spD4;
                                Vec3f spC8;

                                this->beamDmgTimer += 2;
                                this->unk_18C0 = sp180 * 0.062f;
                                if (this->beamDmgTimer < 5) {
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
                                    sBossRemains[sp178]->dmgFogEffectTimer |= 0xA;
                                } else {
                                    sBossRemains[sp178]->actionState = MAJORAS_REMAINS_DEATH;
                                    sBossRemains[sp178]->timer_18D6 = 60;
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
                                        Boss07_SpawnEffect(play, &spE0, &spD4, &spC8, Rand_ZeroFloat(10.0f) + 25.0f);
                                    }
                                }
                            }
                        }
                        if (BgCheck_EntityLineTest1(&play->colCtx, &this->unk_18A8, &this->unk_18B4, &beamMarkPos,
                                                    &sp158, 1, 1, 1, 1, &sp144) &&
                            (this->actionState != MAJORAS_MASK_BEAM_END)) {
                            Vec3f spBC;
                            Vec3f spB0;
                            Vec3f spA4;

                            sp14B = true;
                            spBC.x = randPlusMinusPoint5Scaled(20.0f) + beamMarkPos.x;
                            spBC.y = randPlusMinusPoint5Scaled(20.0f) + beamMarkPos.y;
                            spBC.z = randPlusMinusPoint5Scaled(20.0f) + beamMarkPos.z;
                            spB0.x = 0.0f;
                            spB0.y = 6.0f;
                            spB0.z = 0.0f;
                            spA4.x = spB0.x * -0.05f;
                            spA4.y = spB0.y * -0.05f;
                            spA4.z = spB0.z * -0.05f;

                            Boss07_SpawnEffect(play, &spBC, &spB0, &spA4, Rand_ZeroFloat(10.0f) + 25.0f);
                        }
                    }
                } else if (!player->isBurning && (this->actionState != MAJORAS_MASK_BEAM_END)) {
                    s32 pad2;

                    func_800B8D50(play, &this->actor, 5.0f, this->actor.shape.rot.y, 0.0f, 0x10);
                    for (pad2 = 0; pad2 < ARRAY_COUNT(player->flameTimers); pad2++) {
                        player->flameTimers[pad2] = Rand_S16Offset(0, 200);
                    }
                    player->isBurning = true;
                    func_800B8E58(player, player->ageProperties->voiceSfxIdOffset + NA_SE_VO_LI_DEMO_DAMAGE);
                }
            }
            if (sp14B) {
                if (beamMarkPos.y == 0.0f) {
                    temp_f20 = this->beamMarkLastPos.x - beamMarkPos.x;
                    temp_f22 = this->beamMarkLastPos.z - beamMarkPos.z;
                    func_800AE930(&play->colCtx, Effect_GetByIndex(this->effectIndex), &beamMarkPos, 15.0f,
                                  Math_Atan2S(temp_f20, temp_f22), sp158, sp144);
                    this->beamOn = true;
                }
                this->beamMarkLastPos = beamMarkPos;
            }
            if (this->actionState != MAJORAS_MASK_BEAM_END) {
                if (this->timers[0] == 0) {
                    this->actionState = MAJORAS_MASK_BEAM_END;
                    this->timers[0] = 20;
                }
            } else {
                Math_ApproachZeroF(&this->beamXYscale, 1.0f, 0.05f);
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
    this->motionBlurAlpha = KREG(75) + 150;
    Play_EnableMotionBlur(this->motionBlurAlpha);
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

    this->timer_ABC8++;
    SREG(90) = this->motionBlurAlpha;
    this->maskEyeState = 1;
    switch (this->csState) {
        case MAJORAS_MASK_INTRO_STATE_0:
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
            this->timer_ABC8 = 0;
            this->csState = MAJORAS_MASK_INTRO_STATE_1;
            this->motionBlurAlpha = KREG(76) + 150;
        case MAJORAS_MASK_INTRO_STATE_1:
            if (this->timer_ABC8 >= 20) {
                func_8019F128(NA_SE_EV_LIGHT_GATHER - SFX_FLAG);
                Math_ApproachF(&sMajoraStatic->introOrbScale, sREG(50) + 1.0f, 0.05f, sREG(51) + 0.05f);
            }
            if (this->timer_ABC8 == 35) {
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
            if (this->timer_ABC8 == 75) {
                this->timer_ABC8 = 0;
                this->csState = MAJORAS_MASK_INTRO_STATE_2;
                this->subCamEye.x = player->actor.world.pos.x;
                this->subCamEye.y = player->actor.world.pos.y + 20.0f;
                this->subCamEye.z = player->actor.world.pos.z - 60.0f + 120.0f;
                this->subCamAt.x = player->actor.world.pos.x;
                this->subCamAt.y = player->actor.world.pos.y + 24.0f + 5.0f;
                this->subCamAt.z = player->actor.world.pos.z;
            }

            break;
        case MAJORAS_MASK_INTRO_STATE_2:
            this->motionBlurAlpha = KREG(77) + 150;
            if (this->timer_ABC8 >= 20) {
                Math_ApproachZeroF(&sMajoraStatic->introOrbScale, 1.0f, 0.05f);
            }
            if (this->timer_ABC8 == 20) {
                sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_CS_FLY;
                sBossRemains[REMAINS_GYORG]->actionState = MAJORAS_REMAINS_CS_FLY;
                sBossRemains[REMAINS_GOHT]->actionState = MAJORAS_REMAINS_CS_FLY;
                sBossRemains[REMAINS_TWINMOLD]->actionState = MAJORAS_REMAINS_CS_FLY;
            }
            if (this->timer_ABC8 == 0) {
                func_800B7298(play, &this->actor, 7);
            }
            if (this->timer_ABC8 == 120) {
                func_800B7298(play, &this->actor, 0x15);
            }
            if (this->timer_ABC8 > 30) {
                Math_ApproachF(&this->subCamAt.y, player->actor.world.pos.y + 24.0f + 20.0f, 0.05f,
                               this->subCamSpeedMod);
                Math_ApproachF(&this->subCamSpeedMod, 1.0f, 1.0f, 0.01f);
            }
            if (this->timer_ABC8 >= 160) {
                if (this->timer_ABC8 == 160) {
                    sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_CS_ATTACH_WAIT;
                    sBossRemains[REMAINS_GYORG]->actionState = MAJORAS_REMAINS_CS_ATTACH_WAIT;
                    sBossRemains[REMAINS_GOHT]->actionState = MAJORAS_REMAINS_CS_ATTACH_WAIT;
                    sBossRemains[REMAINS_TWINMOLD]->actionState = MAJORAS_REMAINS_CS_ATTACH_WAIT;
                }
                if (this->timer_ABC8 == 161) {
                    sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_CS_ATTACH;
                }
                if ((this->timer_ABC8 == 180) || (this->timer_ABC8 == 200) || (this->timer_ABC8 == 220)) {
                    this->timer_ABCC++;
                    sBossRemains[this->timer_ABCC]->actionState = MAJORAS_REMAINS_CS_ATTACH;
                }
                this->subCamEye.x = sIntroCamEyes[this->timer_ABCC].x;
                this->subCamEye.y = sIntroCamEyes[this->timer_ABCC].y;
                this->subCamEye.z = sIntroCamEyes[this->timer_ABCC].z;
                this->subCamAt.x = sIntroCamAts[this->timer_ABCC].x;
                this->subCamAt.y = sIntroCamAts[this->timer_ABCC].y;
                this->subCamAt.z = sIntroCamAts[this->timer_ABCC].z;
                if (this->timer_ABC8 == 250) {
                    this->csState = MAJORAS_MASK_INTRO_STATE_3;
                    this->timer_ABC8 = 0;
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
                    sMajoraStatic->introOrbScale = 0.0f;
                    Audio_QueueSeqCmd(NA_BGM_STOP | 0xA0000);
                }
            }
            break;
        case MAJORAS_MASK_INTRO_STATE_3:
            this->motionBlurAlpha = KREG(78) + 150;
            if (this->timer_ABC8 >= 15) {
                Math_ApproachF(&this->subCamEye.z, -700.0f, 0.4f, 100.0f);
            }
            if (this->timer_ABC8 >= 55) {
                if (this->timer_ABC8 == 55) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_B_PAMET_BREAK);
                }
                this->maskEyeState = 0;
            }
            if (this->timer_ABC8 >= 75) {
                s32 i;
                Vec3f sp78 = { 0.0f, 0.0f, 0.0f };
                Vec3f sp6C = { 0.0f, -0.5f, 0.0f };
                Vec3f sp60;

                if (this->timer_ABC8 == 75) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEMO_WALL);
                }
                sp8C = 2.0f * (this->timer_ABC8 % 2);
                if ((this->timer_ABC8 % 2) != 0) {
                    this->actor.world.pos.x += 2.0f;
                } else {
                    this->actor.world.pos.x -= 2.0f;
                }
                for (i = 0; i < 3; i++) {
                    sp60.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(110.0f);
                    sp60.y = this->actor.world.pos.y + randPlusMinusPoint5Scaled(110.0f);
                    sp60.z = this->actor.world.pos.z + 10.0f;
                    EffectSsHahen_Spawn(play, &sp60, &sp78, &sp6C, 0, (Rand_ZeroOne() * 5.0f) + 10.0f, -1, 10, NULL);
                }
            }
            if (this->timer_ABC8 == 110) {
                this->csState = MAJORAS_MASK_INTRO_STATE_4;
                this->timer_ABC8 = 0;
                this->subCamEye.x = this->actor.world.pos.x + 200.0f;
                this->subCamEye.y = this->actor.world.pos.y;
                this->subCamEye.z = this->actor.world.pos.z + 400.0f;
                player->actor.world.pos.z = 0.0f;
                func_800B7298(play, &this->actor, 1);
                this->motionBlurAlpha = KREG(74) + 200;
            }
            break;
        case MAJORAS_MASK_INTRO_STATE_4:
            this->maskEyeState = 0;
            if (this->timer_ABC8 >= 10) {
                Math_ApproachS(&this->motionBlurAlpha, KREG(72), 1, KREG(73) + 2);
                if (this->timer_ABC8 == 10) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEMO_BREAK);
                }
                SkelAnime_Update(&this->skelAnime);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_FLOAT_OLD - SFX_FLAG);
                Math_ApproachF(&this->tentLengthScale, 1.0f, 1.0f, 0.02f);
                Math_ApproachF(&this->actor.world.pos.z, -642.5f, 0.05f, 30.0f);
                Math_ApproachF(&this->actor.world.pos.y, 350.0f, 0.03f, 2.0f);
                if (this->timer_ABC8 == 55) {
                    TitleCard_InitBossName(&play->state, &play->actorCtx.titleCtxt,
                                           Lib_SegmentedToVirtual(&gMajorasMaskTitleCardTex), 0xA0, 0xB4, 0x80, 0x28);
                }
                if (this->timer_ABC8 == 30) {
                    Audio_QueueSeqCmd(NA_BGM_MAJORAS_MASK | 0x8000);
                }
                if (this->timer_ABC8 > 100) {
                    Math_ApproachF(&this->subCamEye.x, player->actor.world.pos.x + 40.0f, 0.1f,
                                   this->subCamSpeedMod * 20.0f);
                    Math_ApproachF(&this->subCamEye.y, player->actor.world.pos.y + 10.0f, 0.1f,
                                   this->subCamSpeedMod * 20.0f);
                    Math_ApproachF(&this->subCamEye.z, player->actor.world.pos.z + 90.0f, 0.1f,
                                   this->subCamSpeedMod * 60.0f);
                    Math_ApproachF(&this->subCamSpeedMod, 1.0f, 1.0f, 0.03f);
                }
                if (this->timer_ABC8 == 175) {
                    Camera* mainCam = Play_GetCamera(play, CAM_ID_MAIN);

                    this->csState = MAJORAS_MASK_INTRO_STATE_0;
                    Boss07_Mask_SetupIdle(this, play);
                    this->timers[0] = 50;
                    this->timers[2] = 200;
                    this->noclipTimer = 50;
                    this->moveTarget.x = 0.0f;
                    this->moveTarget.y = 200.0f;
                    this->moveTarget.z = 0.0f;
                    this->vel_170 = 0.0f;
                    mainCam->eye = this->subCamEye;
                    mainCam->eyeNext = this->subCamEye;
                    mainCam->at = this->subCamAt;
                    func_80169AFC(play, this->subCamIndex, 0);
                    this->subCamIndex = SUB_CAM_ID_DONE;
                    Cutscene_End(play, &play->csCtx);
                    func_800B7298(play, &this->actor, 6);
                    this->actor.flags |= ACTOR_FLAG_1;
                    gSaveContext.eventInf[6] |= 2;
                    Play_DisableMotionBlur();
                }
            } else if ((this->timer_ABC8 % 2) != 0) {
                this->actor.world.pos.x += 2.0f;
            } else {
                this->actor.world.pos.x -= 2.0f;
            }
            Math_ApproachF(&this->subCamAt.x, this->actor.world.pos.x, 0.05f, 10.0f);
            Math_ApproachF(&this->subCamAt.y, this->actor.world.pos.y, 0.05f, 10.0f);
            Math_ApproachF(&this->subCamAt.z, this->actor.world.pos.z, 0.05f, 10.0f);
            break;
    }
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        Vec3f sp50;

        ShrinkWindow_Letterbox_SetSizeTarget(0x1B);
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
        Math_Atan2F_XY(-this->actor.world.pos.z, -this->actor.world.pos.x) * (0x8000 / M_PI);
    this->csState = MAJORAS_MASK_DEATH_STATE_0;
    this->timer_ABC8 = 0;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->invincibilityTimer = 20;
}

void Boss07_Mask_Death(Boss07* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp60;
    Vec3f sp54;

    this->timer_ABC8++;
    this->invincibilityTimer = 20;
    this->maskEyeState = 1;
    SkelAnime_Update(&this->skelAnime);
    Boss07_SmoothStop(this, 0.5f);
    Math_ApproachF(&this->actor.world.pos.x, 0.0f, 0.05f, 5.0f);
    Math_ApproachF(&this->actor.world.pos.z, 0.0f, 0.05f, 5.0f);
    Math_ApproachF(&this->actor.world.pos.y, 130.0f, 0.05f, 3.0f);
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    switch (this->csState) {
        case MAJORAS_MASK_DEATH_STATE_0:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                Cutscene_Start(play, &play->csCtx);
                func_800B7298(play, &this->actor, 1);
                this->subCamIndex = Play_CreateSubCamera(play);
                Play_ChangeCameraStatus(play, CAM_ID_MAIN, CAM_STATUS_WAIT);
                Play_ChangeCameraStatus(play, this->subCamIndex, CAM_STATUS_ACTIVE);
                this->timer_ABC8 = 0;
                this->csState = MAJORAS_MASK_DEATH_STATE_1;
                this->subCamNextAt.z = 0.0f;
                this->timer_18D6 = 120;
                Play_EnableMotionBlur(150);
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
        case MAJORAS_MASK_DEATH_STATE_1:
            player->actor.world.pos.x = 0.0f;
            player->actor.world.pos.z = BREG(87) + 250.0f;
            player->actor.world.rot.y = player->actor.shape.rot.y = -0x8000;

            this->unk_1874 = 2;
            if (this->timer_ABC8 > 60) {
                Math_ApproachS(&this->actor.shape.rot.x, 0, 0xA, 0x200);
                Math_ApproachS(&this->actor.shape.rot.z, 0, 0xA, 0x200);
                Math_ApproachZeroF(&this->tentLengthScale, 1.0f, 0.01f);
            } else {
                this->actor.shape.rot.x += 0x1000;
                this->actor.shape.rot.z += 0x1200;
                Math_ApproachZeroF(&this->tentLengthScale, 1.0f, 0.005f);
            }
            if (this->timer_ABC8 > 130) {
                this->csState = MAJORAS_MASK_DEATH_STATE_2;
            } else {
                break;
            }
        case MAJORAS_MASK_DEATH_STATE_2:
            Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, 0.0f, 0.0f, 0.0f, 0, this->actor.shape.rot.y,
                        this->subCamIndex, MAJORAS_INCARNATION);
            Actor_Kill(&this->actor);
            break;
    }

    Matrix_MultVec3f(&this->subCamNextEye, &this->subCamEye);
    Matrix_MultVec3f(&this->subCamNextAt, &sp60);
    Math_ApproachF(&this->subCamAt.x, sp60.x, 0.1f, 10.0f);
    Math_ApproachF(&this->subCamAt.y, sp60.y, 0.1f, 10.0f);
    Math_ApproachF(&this->subCamAt.z, sp60.z, 0.1f, 10.0f);
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        ShrinkWindow_Letterbox_SetSizeTarget(0x1B);
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

    if (this->invincibilityTimer == 0) {
        if (this->maskFrontCollider.base.acFlags & AC_HIT) {
            this->maskFrontCollider.base.acFlags &= ~AC_HIT;
            this->dmgShakeTimer = 7;
        }
        if (this->maskBackCollider.base.acFlags & AC_HIT) {
            this->maskBackCollider.base.acFlags &= ~AC_HIT;
            this->dmgShakeTimer = 15;
            if ((this->actionFunc == Boss07_Mask_Stunned) || (player->stateFlags3 & PLAYER_STATE3_200)) {
                hitActor = this->maskBackCollider.base.ac;
                hitbox = this->maskBackCollider.info.acHitInfo;
                damage = (hitbox->toucher.dmgFlags & 0xF7CFFFFF) ? this->actor.colChkInfo.damage : 0;
                this->invincibilityTimer = 50;
                this->dmgFogEffectTimer = 15;
                AudioSfx_StopByPos(&this->actor.projectedPos);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DAMAGE2_OLD);
                Boss07_Mask_SetupDamaged(this, play, damage, hitActor);
            } else {
                this->invincibilityTimer = 15;
                AudioSfx_StopByPos(&this->actor.projectedPos);
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
    if ((sMajoraStatic == NULL) || (sMajoraStatic->subCamIndex == SUB_CAM_ID_DONE)) {
        this->updateWhips = true;
        play->envCtx.unk_C1 = 2;
        play->envCtx.unk_C2 = 0;
        Math_ApproachF(&play->envCtx.lightBlend, this->beamXYscale, 1.0f, 0.1f);
        this->actionTimer++;
        if (KREG(63) == 0) {
            this->canDodge = false;
            this->maskEyeState = 0;
            this->unk_1874 = 0;
            Actor_SetScale(&this->actor, 0.1f);
            this->actor.focus.pos = this->actor.world.pos;
            for (i = 0; i < ARRAY_COUNT(this->timers); i++) {
                DECR(this->timers[i]);
            }
            DECR(this->dmgShakeTimer);
            DECR(this->invincibilityTimer);
            DECR(this->dmgFogEffectTimer);
            DECR(this->timer_18D6);
            DECR(this->beamDmgTimer);

            this->beamOn = false;
            this->actionFunc(this, play);
            if (!this->beamOn && this->beamOnLastFrame) {
                func_800AEF44(Effect_GetByIndex(this->effectIndex));
            }
            this->beamOnLastFrame = this->beamOn;
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
                if (this->noclipTimer == 0) {
                    Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 60.0f, 100.0f, 5);
                } else {
                    this->noclipTimer--;
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
        Collider_SetQuadVertices(&this->maskFrontCollider, &sp9C, &sp90, &sp84, &sp78);

        sp68 = (player->stateFlags3 & PLAYER_STATE3_200) ? 70.0f : 40.0f;
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
        Collider_SetQuadVertices(&this->maskBackCollider, &sp9C, &sp90, &sp84, &sp78);

        if (player->stateFlags3 & PLAYER_STATE3_200) {
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->maskBackCollider.base);
        } else {
            if ((this->actionFunc != Boss07_Mask_Stunned) && (this->actionFunc != Boss07_Mask_Damaged)) {
                CollisionCheck_SetAC(play, &play->colChkCtx, &this->maskFrontCollider.base);
            }
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->maskBackCollider.base);
            if (this->actionFunc == Boss07_Mask_Spin) {
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->maskFrontCollider.base);
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->maskBackCollider.base);
            }
        }
        if (this->timer_18D6 != 0) {
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

void Boss07_Mask_UpdateTentacles(Boss07* this, PlayState* play, Vec3f* base, Vec3f* pos, Vec3f* rot, Vec3f* vel,
                                 Vec3f* arg6, f32 arg7, u8 arg8, f32 arg9) {
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
    Vec3f* sp7C = vel;

    if (this->unk_1874 != 0) {
        for (i = 0; i < MAJORAS_TENT_LENGTH; i++) {
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
    for (i = 0; i < MAJORAS_TENT_LENGTH; i++, vel++) {
        if (i == 0) {
            pos[0] = *base;
        } else {
            Math_ApproachF(&vel->x, 0.0f, 1.0f, 1.0f);
            Math_ApproachF(&vel->y, 0.0f, 1.0f, 1.0f);
            Math_ApproachF(&vel->z, 0.0f, 1.0f, 1.0f);
        }
    }

    pos++;
    rot++;
    vel = sp7C + 1;
    sp98.x = sp98.y = 0.0f;
    sp98.z = arg7 * 23.0f;
    for (i = 1; i < MAJORAS_TENT_LENGTH; i++, vel++, pos++, rot++) {
        if (i < MAJORAS_TENT_LENGTH / 2) {
            sp80.x = arg6->x * (MAJORAS_TENT_LENGTH / 2 - i) * 0.2f;
            sp80.y = arg6->y * (MAJORAS_TENT_LENGTH / 2 - i) * 0.2f;
            sp80.z = arg6->z * (MAJORAS_TENT_LENGTH / 2 - i) * 0.2f;
        } else {
            sp80 = gZeroVec3f;
        }
        temp_f24 = pos->x + vel->x - (pos - 1)->x + sp80.x;
        if (this->unk_1874 != 0) {
            phi_f0 = 0.0f;
        } else if (arg8 && ((this->actor.world.pos.y - 30.0f) < (pos - 1)->y)) {
            phi_f0 = -30.0f;
        } else {
            phi_f0 = -3.0f - ((s32)(i % 8U) * 0.05f);
        }
        phi_f2 = pos->y + vel->y + phi_f0 + sp80.y;
        if (phi_f2 < 2.0f) {
            phi_f2 = 2.0f;
        }

        temp_f22 = phi_f2 - (pos - 1)->y;
        temp_f20 = pos->z + vel->z - (pos - 1)->z + sp80.x;
        temp_f26 = Math_Atan2F_XY(temp_f20, temp_f24);
        temp2 = sqrtf(SQ(temp_f24) + SQ(temp_f20));
        temp1 = -Math_Atan2F_XY(temp2, temp_f22);
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
        vel->x = (pos->x - temp_f24) * 0.85f;
        vel->y = (pos->y - temp_f22) * 0.85f;
        vel->z = (pos->z - temp_f20) * 0.85f;
    }
}

void Boss07_Mask_DrawTentacles(Boss07* this, PlayState* play, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5) {
    s32 i;
    f32 phi_f12;

    OPEN_DISPS(play->state.gfxCtx);
    for (i = 0; i < MAJORAS_TENT_LENGTH - 1; i++, arg2++, arg3++) {
        Matrix_Translate(arg2->x, arg2->y, arg2->z, MTXMODE_NEW);
        Matrix_RotateYF(arg3->y, MTXMODE_APPLY);
        Matrix_RotateXFApply(arg3->x);
        Matrix_RotateZF(arg5, MTXMODE_APPLY);
        if (i <= (MAJORAS_TENT_LENGTH - 1) / 2) {
            phi_f12 = 0.035f;
        } else {
            phi_f12 = 0.035f - (i - (MAJORAS_TENT_LENGTH - 1) / 2) * 60.0f * 0.0001f;
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
        Matrix_Scale(this->beamXYscale * 0.05f, this->beamXYscale * 0.05f, this->eyeBeamsZscale * 0.05f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);
        Matrix_Pop();

        Matrix_Translate(-250.0f, 0.0f, 200.0f, MTXMODE_APPLY);
        Matrix_RotateYS(0xA00, MTXMODE_APPLY);
        Matrix_Scale(this->beamXYscale * 0.05f, this->beamXYscale * 0.05f, this->eyeBeamsZscale * 0.05f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);
        Matrix_Pop();

        Matrix_Translate(0.0f, 0.0f, 1200.0f, MTXMODE_APPLY);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(this->beamFocusOrbScale * 40.0f * this->beamXYscale,
                     this->beamFocusOrbScale * 40.0f * this->beamXYscale, 0.0f, MTXMODE_APPLY);
        Matrix_RotateZS(this->actionTimer * 0x100, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 60, sREG(89) + 80);
        Matrix_Scale(6.0f, 6.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateZS(0x4000, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 60, 200);
        Matrix_Pop();

        Matrix_Translate(0.0f, 0.0f, 1150.0f, MTXMODE_APPLY);
        Matrix_MultZero(&this->unk_189C);
        Matrix_Scale(this->beamXYscale * 0.05f, this->beamXYscale * 0.05f, (this->unk_1894 * 0.01f) - 0.01f,
                     MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);
        Matrix_MultVecZ(20100.0f, &this->unk_18A8);
        if (this->unk_18C0 > 0.0f) {
            Vec3f sp50;

            Matrix_MultVecZ(20000.0f, &sp50);
            Matrix_Translate(this->unk_18A8.x, this->unk_18A8.y, this->unk_18A8.z, MTXMODE_NEW);
            Matrix_RotateYS(this->beamTargetYaw, MTXMODE_APPLY);
            Matrix_RotateXS(this->beamTargetPitch, MTXMODE_APPLY);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Matrix_Scale(this->beamXYscale * 0.05f, this->beamXYscale * 0.05f, this->unk_18C0 * 0.01f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gMajorasMaskBeamDL);

            Matrix_MultVecZ(20100.0f, &this->unk_18B4);
            Matrix_Translate(sp50.x, sp50.y, sp50.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(this->beamXYscale * 5.0f, this->beamXYscale * 5.0f, 0.0f, MTXMODE_APPLY);
            Matrix_RotateZS(this->actionTimer * 0x100, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);
            gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
        }
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Mask_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss07* this = THIS;

    if (limbIndex == MAJORAS_MASK_LIMB_FACE) {
        Matrix_MultVecX(500.0f, &this->tentAttachPos);
    }
}

void Boss07_Mask_Draw(Actor* thisx, PlayState* play2) {
    static void* D_80A082E0[2] = { gMajorasMaskWithNormalEyesTex, gMajorasMaskWithDullEyesTex };
    PlayState* play = play2;
    Boss07* this = THIS;
    f32 temp_f20;
    f32 temp_f22;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    temp_f20 = this->dmgShakeTimer * (M_PI / 4.0f) * 0.06666667f;
    temp_f22 = Math_SinS(this->dmgShakeTimer * 0x3500) * temp_f20 * 0.5f;
    Matrix_RotateYF(Math_SinS(this->dmgShakeTimer * 0x4500) * temp_f20, MTXMODE_APPLY);
    Matrix_RotateXFApply(temp_f22);
    if ((this->dmgFogEffectTimer % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    gSPSegment(POLY_OPA_DISP++, 8, Lib_SegmentedToVirtual(D_80A082E0[this->maskEyeState]));
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, Boss07_Mask_PostLimbDraw,
                      &this->actor);
    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasMaskTentacleMaterialDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 155, 155, 80, 255);

    {
        Vec3f spA8;
        Vec3f sp9C;
        Vec3f sp90;
        f32 phi_f24;
        f32 pad2;
        s32 i;
        s32 phi_s6 = ((this->actionFunc == Boss07_Mask_Idle) &&
                      (ABS_ALT((s16)(this->actor.world.rot.y - this->actor.shape.rot.y)) > 0x4000))
                         ? true
                         : false;

        Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
        Matrix_MultVecZ(-3.0f, &sp90);
        spA8.x = 0.0f;
        spA8.y = 20.0f;
        spA8.z = -2.0f;
        phi_f24 = 0.0f;
        for (i = 0; i < MAJORAS_TENT_COUNT; i++) {
            Matrix_Push();
            Matrix_Push();
            Matrix_RotateZF(phi_f24, MTXMODE_APPLY);
            Matrix_MultVec3f(&spA8, &sp9C);
            this->tentacles[i].base.x = this->tentAttachPos.x + sp9C.x;
            this->tentacles[i].base.y = this->tentAttachPos.y + sp9C.y;
            this->tentacles[i].base.z = this->tentAttachPos.z + sp9C.z;

            pad2 = (1 - (i * 0.008f)) * this->tentLengthScale;
            Matrix_Pop();
            if (this->updateWhips) {
                Boss07_Mask_UpdateTentacles(this, play, &this->tentacles[i].base, this->tentacles[i].pos,
                                            this->tentacles[i].rot, this->tentacles[i].vel, &sp90, pad2, phi_s6,
                                            phi_f24);
            }
            Boss07_Mask_DrawTentacles(this, play, this->tentacles[i].pos, this->tentacles[i].rot, pad2, i * 0.9f);
            phi_f24 += 0.5f;
            spA8.y += 1.0f;

            Matrix_Pop();
        }
    }
    Boss07_Mask_DrawBeam(this, play);
    this->updateWhips = false;
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
    if (this->actor.params == MAJORAS_REMAINS_SHOT) {
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
            if (this->actor.params == MAJORAS_INCARNATION_SHOT) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST2_FIRE_OLD);
            }
        }
        for (i = 0; i < ARRAY_COUNT(this->timers); i++) {
            DECR(this->timers[i]);
        }
        Actor_UpdateVelocityWithoutGravity(&this->actor);
        Actor_UpdatePos(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 31.0f, 100.0f, 7);
        this->actor.shape.rot.z += 0x1200;
        if ((this->actor.bgCheckFlags & 0x19) || (this->spawnCollider.base.atFlags & AT_HIT) ||
            (this->spawnCollider.base.atFlags & AT_HIT) || sKillProjectiles) {
            Actor_Kill(&this->actor);
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, this->shotColorIndex, CLEAR_TAG_SMALL_LIGHT_RAYS);
        }
        Collider_UpdateCylinder(&this->actor, &this->spawnCollider);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->spawnCollider.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->spawnCollider.base);
    }
}

void Boss07_Projectile_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, sShotPrimColors[this->shotColorIndex][0],
                    sShotPrimColors[this->shotColorIndex][1], sShotPrimColors[this->shotColorIndex][2], 255);
    gDPSetEnvColor(POLY_XLU_DISP++, sShotEnvColors[this->shotColorIndex][0], sShotEnvColors[this->shotColorIndex][1],
                   sShotEnvColors[this->shotColorIndex][2], 128);
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, 0.0f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);
    gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Remains_CollisionCheck(Boss07* this, PlayState* play) {
    Vec3f sp2C;
    ColliderInfo* hitbox;

    if ((this->invincibilityTimer == 0) && (this->spawnCollider.base.acFlags & AC_HIT)) {
        this->spawnCollider.base.acFlags &= ~AC_HIT;
        this->invincibilityTimer = 15;
        hitbox = this->spawnCollider.info.acHitInfo;
        if (hitbox->toucher.dmgFlags & DMG_HOOKSHOT) {
            Boss07_Remains_SetupStunned(this, play);
        } else {
            u8 damage = this->actor.colChkInfo.damage;

            this->actor.colChkInfo.health -= damage;
            this->dmgFogEffectTimer = 15;
            this->actionFunc = Boss07_Remains_Fly;
            if ((s8)this->actor.colChkInfo.health <= 0) {
                this->actionState = MAJORAS_REMAINS_DEATH;
                this->readyDeath = true;
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FOLLOWERS_DEAD);
            } else {
                this->actionState = MAJORAS_REMAINS_DAMAGED;
                this->timers[0] = 15;
                Boss07_Remains_DamageSfx(this);
            }
            Matrix_RotateYS(this->actor.yawTowardsPlayer, MTXMODE_NEW);
            Matrix_MultVecZ(-20.0f, &sp2C);
            this->xRecoil = sp2C.x;
            this->zRecoil = sp2C.z;
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
        case MAJORAS_REMAINS_CS_WAIT:
            Actor_SetScale(&this->actor, 0.0f);
            this->actor.world.pos.x = player->actor.world.pos.x;
            this->actor.world.pos.y = player->actor.world.pos.y + 30.0f;
            this->actor.world.pos.z = player->actor.world.pos.z;
            if (player->transformation == PLAYER_FORM_FIERCE_DEITY) {
                this->actor.world.pos.y += 30.0f + KREG(48);
            }
            this->moveTarget.x = sRemainsStart[this->actor.params - MAJORAS_REMAINS].x + player->actor.world.pos.x;
            this->moveTarget.y = sRemainsStart[this->actor.params - MAJORAS_REMAINS].y + player->actor.world.pos.y;
            this->moveTarget.z = sRemainsStart[this->actor.params - MAJORAS_REMAINS].z + player->actor.world.pos.z;
            sp54 = this->moveTarget.x - this->actor.world.pos.x;
            sp50 = this->moveTarget.y - this->actor.world.pos.y;
            sp4C = this->moveTarget.z - this->actor.world.pos.z;
            this->actor.world.rot.y = Math_Atan2S(sp54, sp4C);
            this->actor.world.rot.x = Math_Atan2S(sp50, sqrtf(SQ(sp54) + SQ(sp4C)));
            this->timer_AB40 = Rand_ZeroFloat(100.0f);
            break;
        case MAJORAS_REMAINS_CS_FLY:
            this->timer_ABC8++;
            this->timer_AB40++;
            this->remainsOrbRot += 0x200;
            Math_ApproachF(&this->eyeBeamsZscale, 1.2f, 1.0f, 0.1f);
            Math_ApproachF(&this->actor.scale.x, 0.004f, 0.5f, 0.0002f);
            this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
            if (this->timer_ABC8 > 90) {
                this->moveTarget.x = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].x;
                this->moveTarget.y = 370.0f;
                this->moveTarget.z = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].z;
                sp38 = 20.0f;
                sp34 = 0.5f;
                sp40 = 0x1000;
                sp3C = 0x190;
                phi_f2 = 0.0f;
            } else {
                phi_f2 = Math_SinS(this->timer_AB40 * 0x300) * 20.0f;
                sp38 = 1.0f;
                sp34 = 0.1f;
                sp40 = 0x5DC;
                sp3C = 0x64;
            }
            sp54 = this->moveTarget.x - this->actor.world.pos.x;
            sp50 = this->moveTarget.y - this->actor.world.pos.y + phi_f2;
            sp4C = this->moveTarget.z - this->actor.world.pos.z;
            sp30 = Math_Atan2S(sp54, sp4C);
            sp32 = Math_Atan2S(sp50, sqrtf(SQ(sp54) + SQ(sp4C)));
            Math_ApproachS(&this->actor.world.rot.y, sp30, 5, this->vel_170);
            Math_ApproachS(&this->actor.world.rot.x, sp32, 5, this->vel_170);
            Math_ApproachF(&this->vel_170, sp40, 1.0f, sp3C);
            Math_ApproachF(&this->actor.speedXZ, sp38, 1.0f, sp34);
            Actor_UpdateVelocityWithoutGravity(&this->actor);
            Actor_UpdatePos(&this->actor);
            this->actor.shape.rot = this->actor.world.rot;
            break;
        case MAJORAS_REMAINS_CS_ATTACH_WAIT:
            Actor_SetScale(&this->actor, 0.0f);
            this->eyeBeamsZscale = 0.0f;
            this->actor.speedXZ = 0.0f;
            this->actor.world.pos.x = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].x * 0.6f;
            this->actor.world.pos.y = 370.0f;
            this->actor.world.pos.z = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].z * 0.6f;
            this->actor.shape.rot.y = sRemainsEnd[this->actor.params - MAJORAS_REMAINS].y;
            this->timer_ABCC = 0;
            break;
        case MAJORAS_REMAINS_CS_ATTACH:
            this->timer_ABCC++;
            if (this->timer_ABCC == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_FOLLOWERS_STAY);
            }
            Actor_SetScale(&this->actor, 0.03f);
            Math_ApproachF(&this->actor.world.pos.x, sRemainsEnd[this->actor.params - MAJORAS_REMAINS].x, 0.5f, 40.0f);
            Math_ApproachF(&this->actor.world.pos.z, sRemainsEnd[this->actor.params - MAJORAS_REMAINS].z, 0.5f, 22.0f);
            break;
    }
}

void Boss07_Remains_SetupFly(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Remains_Fly;
    this->actor.gravity = -0.75f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
    Collider_InitAndSetCylinder(play, &this->spawnCollider, &this->actor, &sRemainsCylInit);
    this->actor.colChkInfo.health = 5;
    this->actionState = MAJORAS_REMAINS_WAIT;
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
        case MAJORAS_REMAINS_ACTIVATE:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MUJURA_FOLLOWERS_FLY - SFX_FLAG);
            this->timers[0] = 80;
            this->timers[2] = 100.0f + Rand_ZeroFloat(100.0f);
            this->flySpeedTarget = 5.0f;
            this->actor.speedXZ = 5.0f;
            this->moveTarget = gZeroVec3f;
            this->actor.world.rot.y = Math_Atan2S(-this->actor.world.pos.x, -this->actor.world.pos.z);
            this->actionState = MAJORAS_REMAINS_FLY;
            this->noclipTimer = 100;
            this->spawnCollider.base.colType = COLTYPE_HIT3;
            this->actor.flags |= (ACTOR_FLAG_200 | ACTOR_FLAG_1);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LAST1_DEMO_BREAK);
            break;
        case MAJORAS_REMAINS_FLY:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MUJURA_FOLLOWERS_FLY - SFX_FLAG);
            if (this->timers[2] == 0) {
                this->readyShot = true;
                this->timers[2] = Rand_ZeroFloat(200.0f) + 100.0f;
            }
            if (this->timers[0] == 0) {
                if (Rand_ZeroOne() < 0.35f) {
                    this->flySpeedTarget = 1.0f;
                    this->timers[0] = Rand_ZeroFloat(50.0f) + 30.0f;
                } else {
                    Boss07_RandVec3fXZ(&this->moveTarget, 500.0f);
                    this->moveTarget.y = Rand_ZeroFloat(350.0f) + 100.0f;
                    this->timers[0] = Rand_ZeroFloat(50.0f) + 20.0f;
                    this->vel_170 = 0.0f;
                    this->flySpeedTarget = Rand_ZeroFloat(5.0f) + 5.0f;
                }
            }
            sp78 = this->moveTarget.x - this->actor.world.pos.x;
            sp74 = this->moveTarget.y - this->actor.world.pos.y;
            sp70 = this->moveTarget.z - this->actor.world.pos.z;
            sp7C = Math_Atan2S(sp78, sp70);
            sp7E = Math_Atan2S(sp74, sqrtf(SQ(sp78) + SQ(sp70)));
            sp7E += (s16)(Math_SinS(this->actionTimer * 0x1388) * 0xFA0);
            Math_ApproachS(&this->actor.world.rot.y, sp7C, 0xA, this->vel_170);
            Math_ApproachS(&this->actor.world.rot.x, sp7E, 5, this->vel_170);
            Math_ApproachF(&this->vel_170, 0x7D0, 1.0f, 0x64);
            Math_ApproachF(&this->actor.speedXZ, this->flySpeedTarget, 1.0f, 1.0f);
            if ((this->flySpeedTarget < 8.0f) && !Play_InCsMode(play)) {
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000);
            } else {
                Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 0xA, 0x1000);
            }
            Actor_UpdateVelocityWithoutGravity(&this->actor);
            Actor_UpdatePos(&this->actor);
            if (this->noclipTimer == 0) {
                Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 100.0f, 100, 5);
            } else {
                this->noclipTimer--;
            }
            Boss07_Remains_CollisionCheck(this, play);
            break;
        case MAJORAS_REMAINS_DEATH:
            Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 1, 0x500);
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 50.0f, 100.0f, 100.0f, 5);
            if (this->actor.bgCheckFlags & 1) {
                if (this->readyDeath) {
                    this->timer_18D6 |= 4;
                }
                Math_ApproachF(&this->actor.scale.z, 0.0f, 1.0f, 0.001f);
                if (this->actor.scale.z == 0.0f) {
                    this->actionState = MAJORAS_REMAINS_GONE;
                    this->actor.draw = NULL;
                    this->actor.flags &= ~ACTOR_FLAG_1;
                }
                Boss07_SmoothStop(this, 2.0f);
            } else {
                this->actor.shape.rot.z += 0x200;
            }
            break;
        case MAJORAS_REMAINS_DAMAGED:
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
        case MAJORAS_REMAINS_WAIT:
            break;
    }
    if (this->actionState <= MAJORAS_REMAINS_FLY) {
        Collider_UpdateCylinder(&this->actor, &this->spawnCollider);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->spawnCollider.base);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->spawnCollider.base);
    }
    if (this->readyShot) {
        this->readyShot = false;
        if (Boss07_IsFacingPlayer(this, play) && (sMajorasMask->actionFunc != Boss07_Mask_Beam)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_BOSS_07, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, 0, MAJORAS_REMAINS_SHOT);
        }
    }
    if (this->timer_18D6 != 0) {
        sp60.x = randPlusMinusPoint5Scaled(80.0f) + this->actor.world.pos.x;
        sp60.z = randPlusMinusPoint5Scaled(80.0f) + this->actor.world.pos.z;
        if (this->readyDeath) {
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
    Collider_UpdateCylinder(&this->actor, &this->spawnCollider);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->spawnCollider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->spawnCollider.base);
    if (this->timers[0] == 0) {
        this->actionFunc = Boss07_Remains_Fly;
        this->actionState = MAJORAS_REMAINS_FLY;
    }
}

void Boss07_Remains_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    s32 i;

    this->actionTimer++;
    for (i = 0; i < ARRAY_COUNT(this->timers); i++) {
        DECR(this->timers[i]);
    }
    DECR(this->timer_18D6);
    DECR(this->invincibilityTimer);
    DECR(this->dmgFogEffectTimer);
    this->actionFunc(this, play);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.world.pos.x += this->xRecoil;
    this->actor.world.pos.z += this->zRecoil;
    Math_ApproachZeroF(&this->xRecoil, 1.0f, 1.0f);
    Math_ApproachZeroF(&this->zRecoil, 1.0f, 1.0f);
}

void Boss07_Remains_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;
    f32 sp64;
    f32 sp60;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    if ((this->dmgFogEffectTimer % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
    }
    sp64 = this->invincibilityTimer * (M_PI / 4.0f) * 0.06666667f;
    sp60 = Math_SinS(this->invincibilityTimer * 0x3500) * sp64 * 0.5f;
    Matrix_RotateYF(Math_SinS(this->invincibilityTimer * 0x4500) * sp64, MTXMODE_APPLY);
    Matrix_RotateXFApply(sp60);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    switch (this->actor.params) {
        case MAJORAS_REMAINS + REMAINS_ODOLWA:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskOdolwaDL);
            break;
        case MAJORAS_REMAINS + REMAINS_GYORG:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskGyorgDL);
            break;
        case MAJORAS_REMAINS + REMAINS_GOHT:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskGohtDL);
            break;
        case MAJORAS_REMAINS + REMAINS_TWINMOLD:
            gSPDisplayList(POLY_OPA_DISP++, gBossMaskTwinmoldDL);
            break;
    }
    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
    if (this->actionFunc == Boss07_Remains_Intro) {
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, 200);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 100, 128);

        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(this->eyeBeamsZscale, this->eyeBeamsZscale, 0.0f, MTXMODE_APPLY);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_RotateZS(this->remainsOrbRot, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);
    }
    CLOSE_DISPS(play->state.gfxCtx);
}

void Boss07_Top_SetupThrown(Boss07* this, PlayState* play) {
    this->actionFunc = Boss07_Top_Thrown;
    this->actor.gravity = 0.0f;
    this->topSpinRate = (sREG(42) * 0.01f) + 0.9f;
    this->timers[0] = 200;
}

void Boss07_Top_Thrown(Boss07* this, PlayState* play) {
    if (sMajorasWrath->actionFunc == Boss07_Wrath_SpawnTop) {
        Math_Vec3f_Copy(&this->actor.world.pos, &sMajorasWrath->whipGrabPos);
        this->actor.world.pos.y -= 25.0f + sREG(78);
    }
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 50.0f, 80.0f, 1);
    if ((sMajorasWrath->actionTimer >= (s16)(KREG(50) + 21)) || (sMajorasWrath->invincibilityTimer != 0)) {
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
    if (sMajorasWrath->invincibilityTimer != 0) {
        this->timers[0] = sREG(47) + 80;
        this->timers[1] = sREG(77) + 150;
    } else {
        this->timers[0] = sREG(47) + 300;
        this->timers[1] = sREG(77) + 370;
        this->actor.velocity.y = (sREG(43) * 0.1f) + 15.0f;
        this->actor.speedXZ = (sREG(44) * 0.1f) + -3.0f;
    }
    this->actor.world.rot.y = (sREG(45) * 0x1000) + sMajorasWrath->actor.shape.rot.y;
    this->actor.shape.rot.z = Rand_ZeroFloat((f32)(sREG(29) + 10) * 0x100);
}

void Boss07_Top_Ground(Boss07* this, PlayState* play) {
    f32 sp4C;
    f32 sp48;

    func_8019FAD8(&this->actor.projectedPos, NA_SE_EN_LAST3_KOMA_OLD - SFX_FLAG, this->topSpinRate * 1.1111112f);
    Actor_MoveWithGravity(&this->actor);
    this->actor.world.pos.x += this->xRecoil;
    this->actor.world.pos.z += this->zRecoil;
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 40.0f, 80.0f, 5);
    if ((this->unk_158 == 0) && (this->actor.bgCheckFlags & 8)) {
        this->unk_158 = 10;
        if (this->topSpinRate > 0.01f) {
            if (this->topSpinRate < 0.45f) {
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
                Math_ApproachS(&this->actor.shape.rot.z, (sREG(19) * 0x800) + 0x2000, 1, sREG(18) + 0x1A0);
                Math_ApproachZeroF(&this->topSpinRate, 1.0f, (sREG(16) * 0.0001f) + 0.005f);
                Math_ApproachS(&this->unk_180, (sREG(20) * 0x800) + 0x2000, 1, (sREG(21) * 16) + 0xC0);
            } else if (this->timers[0] == 0) {
                Math_ApproachZeroF(&this->actor.speedXZ, 1.0f, (sREG(26) * 0.01f) + 0.5f);
                Math_ApproachS(&this->actor.shape.rot.z, (sREG(19) * 0x800) + 0x2000, 1, 0x800);
                Math_ApproachZeroF(&this->topSpinRate, 1.0f, (sREG(27) * 0.001f) + 0.024f);
                Math_ApproachS(&this->unk_180, 0, 2, sREG(28) + 106);
            } else {
                Math_ApproachF(&this->actor.speedXZ, sREG(22) + 10.0f, 1.0f, (sREG(23) * 0.01f) + 0.6f);
                Math_ApproachS(&this->actor.shape.rot.z, (sREG(19) * 0x800) + 0x2000, 1, sREG(18) + 0x410);
                Math_ApproachZeroF(&this->topSpinRate, 1.0f, (sREG(16) * 0.0001f) + 0.005f);
                Math_ApproachS(&this->unk_180, (sREG(29) * 0x800) - 0x800, 1, (sREG(30) * 16) + 0x340);
            }
            this->actor.world.rot.y += this->unk_180;
        } else {
            Math_ApproachS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x300);
            Math_ApproachF(&this->actor.speedXZ, (sREG(48) * 0.1f) + 2.0f + 8.0f, 1.0f,
                           (sREG(46) * 0.01f) + 0.100000024f + 0.2f);
        }
        Math_ApproachZeroF(&this->xRecoil, 1.0f, 1.0f);
        Math_ApproachZeroF(&this->zRecoil, 1.0f, 1.0f);
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
        this->actionState = MAJORAS_TOP_ON_GROUND;
    } else if (this->actionState != MAJORAS_TOP_IN_AIR) {
        this->actionState = MAJORAS_TOP_IN_AIR;
        func_800AEF44(Effect_GetByIndex(this->effectIndex));
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->timers[1] == 0) {
        EnBom* bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, this->actor.world.pos.x,
                                          this->actor.world.pos.y + 25.0f, this->actor.world.pos.z, 0, 0, 0, ENBOM_0);

        if (bomb != NULL) {
            bomb->timer = 0;
        }
        Actor_Kill(&this->actor);
    } else if (this->timers[1] == 25) {
        this->dmgFogEffectTimer = 25;
        func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_EXPLOSIVES);
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
            if ((this != top) && (top->actor.params == MAJORAS_TOP) && (top->unk_158 == 0)) {
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
                        this->topSpinRate = (sREG(89) * 0.01f) + 0.2f;
                        this->unk_180 = 0x800;
                    }
                    if (top->timers[0] > 0) {
                        top->actor.speedXZ = -10.0f;
                    } else {
                        top->actor.speedXZ = -5.0f;
                        top->topSpinRate = (sREG(89) * 0.01f) + 0.2f;
                        top->unk_180 = 0x800;
                    }
                    CollisionCheck_SpawnShieldParticles(play, &this->actor.focus.pos);
                    CollisionCheck_SpawnShieldParticles(play, &top->actor.focus.pos);
                    if (this->timers[0] > 80) {
                        this->actor.shape.rot.z = randPlusMinusPoint5Scaled((f32)(sREG(29) + 20) * 0x100);
                        for (i = 0; i < 5; i++) {
                            DECR(this->timers[0]);
                            DECR(this->timers[1]);
                        }
                    }
                    if (top->timers[0] > 80) {
                        top->actor.shape.rot.z = randPlusMinusPoint5Scaled((f32)(sREG(29) + 20) * 0x100);
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
    s32 sp38 = false;
    Player* player = GET_PLAYER(play);
    s32 pad[3];

    if (this->spawnCollider.base.acFlags & AC_HIT) {
        this->spawnCollider.base.acFlags &= ~AC_HIT;
        if (this->invincibilityTimer == 0) {
            this->invincibilityTimer = 5;
            if ((this->actor.colChkInfo.damageEffect == MAJORAS_TOP_DMGEFF_D) ||
                (this->actor.colChkInfo.damageEffect == MAJORAS_TOP_DMGEFF_A)) {
                if (this->actor.colChkInfo.damageEffect == MAJORAS_TOP_DMGEFF_D) {
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
                    } else if (this->actor.colChkInfo.damageEffect == MAJORAS_TOP_DMGEFF_A) {
                        this->actor.speedXZ = -15.0f;
                    } else {
                        this->actor.speedXZ = -7.0f;
                    }
                }
            } else if (this->actor.colChkInfo.damageEffect == MAJORAS_TOP_DMGEFF_C) {
                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                this->actor.speedXZ = 2.0f * -player->actor.speedXZ;
                sp38 = true;
            } else if (this->actor.colChkInfo.damageEffect == MAJORAS_TOP_DMGEFF_B) {
                this->actor.world.rot.y =
                    Math_Atan2S(this->spawnCollider.base.ac->world.pos.x - this->actor.world.pos.x,
                                this->spawnCollider.base.ac->world.pos.z - this->actor.world.pos.z);
                this->actor.speedXZ = -20.0f;
                this->actor.velocity.y = sREG(55) + 15.0f;
                sp38 = true;
            }
        }
    }
    if (this->actor.bgCheckFlags & 1) {
        if ((func_800B64FC(play, 5.0f, &this->actor.world.pos, &sp3C) >= 0.0f) && (sp3C == 0)) {
            this->actor.world.rot.y = this->actor.yawTowardsPlayer;
            this->actor.velocity.y = sREG(55) + 25.0f;
            sp38 = true;
        }
    }
    if (sp38 && (this->timers[0] > 90)) {
        this->actor.shape.rot.z = randPlusMinusPoint5Scaled((f32)(sREG(29) + 30) * 0x100);
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
    DECR(this->dmgFogEffectTimer);
    DECR(this->invincibilityTimer);
    DECR(this->unk_158);
    this->actionFunc(this, play);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
    this->actor.focus.pos.y += 25.0f;
    Boss07_Top_CollisionCheck(this, play);
    Collider_UpdateCylinder(&this->actor, &this->spawnCollider);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->spawnCollider.base);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->spawnCollider.base);
    Boss07_Top_Collide(this, play);
    this->topSpinAngle -= this->topSpinRate;
    if (this->topSpinAngle < -2.0f * M_PI) {
        this->topSpinAngle += 2.0f * M_PI;
    }
    if (sMajorasWrath->actionFunc == Boss07_Wrath_Death) {
        Actor_Kill(&this->actor);
    }
    Math_ApproachF(&this->actor.scale.x, (sREG(77) * 0.001f) + 0.06f, 1.0f, 0.012f);
    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void Boss07_Top_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    Boss07* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    if ((this->dmgFogEffectTimer % 2) != 0) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 780, 1099);
    }
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_RotateYF(this->topSpinAngle, MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gMajorasWrathSpinningTopDL);
    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);
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
    if (this->lensFlareOn) {
        D_801F4E32 = true;
        D_801F4E38 = this->lensFlarePos;
        D_801F4E44 = this->lensFlareScale;
        D_801F4E48 = 10.0f;
        D_801F4E4C = 0;
        this->lensFlareOn = false;
    } else {
        D_801F4E32 = false;
    }
    this->timer_ABC8++;
    switch (this->csState) {
        case MAJORAS_STATIC_CS_STATE_0:
            if ((sMajorasMask != NULL) && sMajorasMask->activateRemains) {
                this->csState = MAJORAS_STATIC_CS_STATE_1;
                this->timer_ABC8 = 0;
            }
            break;
        case MAJORAS_STATIC_CS_STATE_1:
            if (ActorCutscene_GetCurrentIndex() == -1) {
                Cutscene_Start(play, &play->csCtx);
                func_800B7298(play, &this->actor, 7);
                this->subCamIndex = Play_CreateSubCamera(play);
                Play_ChangeCameraStatus(play, CAM_ID_MAIN, CAM_STATUS_WAIT);
                Play_ChangeCameraStatus(play, this->subCamIndex, CAM_STATUS_ACTIVE);
                this->timer_ABC8 = 0;
                this->csState = MAJORAS_STATIC_CS_STATE_2;
                Play_EnableMotionBlur(150);
                this->subCamEye.x = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case MAJORAS_STATIC_CS_STATE_2:
            if (this->timer_ABC8 == 20) {
                sBossRemains[REMAINS_ODOLWA]->actionState = MAJORAS_REMAINS_ACTIVATE;
            }
            this->subCamAt.x = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_ODOLWA]->actor.world.pos.z;
            if (this->timer_ABC8 == 40) {
                this->csState = MAJORAS_STATIC_CS_STATE_3;
                this->timer_ABC8 = 0;
                this->subCamEye.x = sBossRemains[REMAINS_GYORG]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_GYORG]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_GYORG]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case MAJORAS_STATIC_CS_STATE_3:
            if (this->timer_ABC8 == 20) {
                sBossRemains[REMAINS_GYORG]->actionState = MAJORAS_REMAINS_ACTIVATE;
            }
            this->subCamAt.x = sBossRemains[REMAINS_GYORG]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_GYORG]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_GYORG]->actor.world.pos.z;
            if (this->timer_ABC8 == 40) {
                this->csState = MAJORAS_STATIC_CS_STATE_4;
                this->timer_ABC8 = 0;
                this->subCamEye.x = sBossRemains[REMAINS_GOHT]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_GOHT]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_GOHT]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case MAJORAS_STATIC_CS_STATE_4:
            if (this->timer_ABC8 == 20) {
                sBossRemains[REMAINS_GOHT]->actionState = MAJORAS_REMAINS_ACTIVATE;
            }
            this->subCamAt.x = sBossRemains[REMAINS_GOHT]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_GOHT]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_GOHT]->actor.world.pos.z;
            if (this->timer_ABC8 == 40) {
                this->csState = MAJORAS_STATIC_CS_STATE_5;
                this->timer_ABC8 = 0;
                this->subCamEye.x = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.x * 0.7f;
                this->subCamEye.y = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.y * 0.7f;
                this->subCamEye.z = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.z * 0.7f;
            } else {
                break;
            }
        case MAJORAS_STATIC_CS_STATE_5:
            if (this->timer_ABC8 == 20) {
                sBossRemains[REMAINS_TWINMOLD]->actionState = MAJORAS_REMAINS_ACTIVATE;
            }
            this->subCamAt.x = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.x;
            this->subCamAt.y = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.y;
            this->subCamAt.z = sBossRemains[REMAINS_TWINMOLD]->actor.world.pos.z;
            if (this->timer_ABC8 == 40) {
                Camera* mainCam = Play_GetCamera(play, CAM_ID_MAIN);
                s32 i;

                this->csState = MAJORAS_STATIC_CS_STATE_6;
                this->timer_ABC8 = 0;
                mainCam->eye = this->subCamEye;
                mainCam->eyeNext = this->subCamEye;
                mainCam->at = this->subCamAt;
                func_80169AFC(play, this->subCamIndex, 0);
                this->subCamIndex = SUB_CAM_ID_DONE;
                Cutscene_End(play, &play->csCtx);
                func_800B7298(play, &this->actor, 6);
                Play_DisableMotionBlur();
                for (i = 0; i < ARRAY_COUNT(sBossRemains); i++) {
                    func_800BC154(play, &play->actorCtx, &sBossRemains[i]->actor, ACTORCAT_ENEMY);
                }
            }
            break;
        case MAJORAS_STATIC_CS_STATE_6:
            break;
    }
    if (this->subCamIndex != SUB_CAM_ID_DONE) {
        if (this->timer_ABC8 < 20) {
            s32 j;

            for (j = 0; j < ARRAY_COUNT(sBossRemains); j++) {
                if ((this->timer_ABC8 % 2) != 0) {
                    sBossRemains[j]->actor.world.pos.x += 2.0f;
                    sBossRemains[j]->actor.world.pos.z += 2.0f;
                } else {
                    sBossRemains[j]->actor.world.pos.x -= 2.0f;
                    sBossRemains[j]->actor.world.pos.z -= 2.0f;
                }
            }
        }
        ShrinkWindow_Letterbox_SetSizeTarget(27);
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
        if (effect->type != MAJORAS_EFFECT_NONE) {
            effect->scroll++;

            effect->pos.x += effect->vel.x;
            effect->pos.y += effect->vel.y;
            effect->pos.z += effect->vel.z;

            effect->vel.x += effect->accel.x;
            effect->vel.y += effect->accel.y;
            effect->vel.z += effect->accel.z;
            if (effect->type == MAJORAS_EFFECT_FLAME) {
                if (effect->isFading) {
                    effect->alpha -= (i % 8U) + 13;
                    if (effect->alpha <= 0) {
                        effect->alpha = 0;
                        effect->type = MAJORAS_EFFECT_NONE;
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
        if (effect->type > MAJORAS_EFFECT_NONE) {
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
