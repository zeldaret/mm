/*
 * File: z_en_dragon.c
 * Overlay: ovl_En_Dragon
 * Description: Deep Python
 */

#include "z_en_dragon.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnDragon*)thisx)

void EnDragon_Init(Actor* thisx, PlayState* play);
void EnDragon_Destroy(Actor* thisx, PlayState* play);
void EnDragon_Update(Actor* thisx, PlayState* play);
void EnDragon_Draw(Actor* thisx, PlayState* play);

void EnDragon_SetupRetreatOrIdle(EnDragon* this);
void EnDragon_RetreatOrIdle(EnDragon* this, PlayState* play);
void EnDragon_SetupExtend(EnDragon* this);
void EnDragon_Extend(EnDragon* this, PlayState* play);
void EnDragon_Grab(EnDragon* this, PlayState* play);
void EnDragon_SetupAttack(EnDragon* this);
void EnDragon_Attack(EnDragon* this, PlayState* play);
void EnDragon_Dead(EnDragon* this, PlayState* play);

typedef enum {
    /* 0 */ DEEP_PYTHON_ANIMATION_SMALL_SIDE_SWAY,
    /* 1 */ DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY,
    /* 2 */ DEEP_PYTHON_ANIMATION_VERTICAL_SWAY,
    /* 3 */ DEEP_PYTHON_ANIMATION_IDLE
} DeepPythonAnimationIndex;

typedef enum {
    /* 0 */ DEEP_PYTHON_EXTEND_STATE_NOT_FULLY_EXTENDED,
    /* 1 */ DEEP_PYTHON_EXTEND_STATE_FULLY_EXTENDED,
    /* 2 */ DEEP_PYTHON_EXTEND_STATE_REPEAT_LARGE_SWAY,
    /* 3 */ DEEP_PYTHON_EXTEND_STATE_REPEAT_SMALL_SWAY,
} DeepPythonExtendState;

typedef enum {
    /* 0 */ DEEP_PYTHON_GRAB_STATE_START,
    /* 1 */ DEEP_PYTHON_GRAB_STATE_GRABBED,
} DeepPythonGrabState;

typedef enum {
    /* 0 */ DEEP_PYTHON_ATTACK_STATE_START,
    /* 1 */ DEEP_PYTHON_ATTACK_STATE_RELEASED,
} DeepPythonAttackState;

static s32 sNumPythonsDead = 0;

const ActorInit En_Dragon_InitVars = {
    ACTOR_EN_DRAGON,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_UTUBO,
    sizeof(EnDragon),
    (ActorFunc)EnDragon_Init,
    (ActorFunc)EnDragon_Destroy,
    (ActorFunc)EnDragon_Update,
    (ActorFunc)EnDragon_Draw,
};

typedef enum {
    /* 0x0 */ DEEP_PYTHON_DMGEFF_NONE,
    /* 0xF */ DEEP_PYTHON_DMGEFF_DAMAGE = 0xF
} DeepPythonDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Deku Stick     */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, DEEP_PYTHON_DMGEFF_DAMAGE),
    /* Zora boomerang */ DMG_ENTRY(1, DEEP_PYTHON_DMGEFF_DAMAGE),
    /* Normal arrow   */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Hookshot       */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Goron punch    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Ice arrow      */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Light arrow    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Goron spikes   */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Zora barrier   */ DMG_ENTRY(1, DEEP_PYTHON_DMGEFF_DAMAGE),
    /* Normal shield  */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Thrown object  */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, DEEP_PYTHON_DMGEFF_DAMAGE),
    /* Spin attack    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, DEEP_PYTHON_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, DEEP_PYTHON_DMGEFF_DAMAGE),
};

static ColliderJntSphElementInit sJntSphElementsInit[8] = {
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_HEAD, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_COLLAR, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_COLLAR, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_BODY_SEGMENT_1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_BODY_SEGMENT_1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_BODY_SEGMENT_2, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_BODY_SEGMENT_2, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { DEEP_PYTHON_LIMB_BODY_SEGMENT_2, { { 0, 0, 0 }, 0 }, 1 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

void EnDragon_Init(Actor* thisx, PlayState* play) {
    EnDragon* this = THIS;

    SkelAnime_InitFlex(play, &this->skelAnime, &gDeepPythonSkel, &gDeepPythonSmallSideSwayAnim, this->jointTable,
                       this->morphTable, DEEP_PYTHON_LIMB_MAX);

    this->actor.colChkInfo.health = 4;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.targetMode = 0xA;
    Collider_InitAndSetJntSph(play, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);

    this->collider.elements[0].dim.scale = this->collider.elements[1].dim.scale = this->collider.elements[2].dim.scale =
        this->collider.elements[3].dim.scale = this->collider.elements[4].dim.scale =
            this->collider.elements[5].dim.scale = this->collider.elements[6].dim.scale =
                this->collider.elements[7].dim.scale = 1.0f;

    this->collider.elements[0].dim.modelSphere.radius = 150;
    this->collider.elements[0].dim.modelSphere.center.x = 420;
    this->collider.elements[1].dim.modelSphere.radius = 160;
    this->collider.elements[1].dim.modelSphere.center.x = 630;
    this->collider.elements[2].dim.modelSphere.radius = 130;
    this->collider.elements[2].dim.modelSphere.center.x = 630;
    this->collider.elements[3].dim.modelSphere.radius = 170;
    this->collider.elements[3].dim.modelSphere.center.x = 920;
    this->collider.elements[4].dim.modelSphere.radius = 150;
    this->collider.elements[4].dim.modelSphere.center.x = 530;
    this->collider.elements[5].dim.modelSphere.radius = 140;
    this->collider.elements[5].dim.modelSphere.center.x = 730;
    this->collider.elements[6].dim.modelSphere.radius = 120;
    this->collider.elements[6].dim.modelSphere.center.x = 430;
    this->collider.elements[7].dim.modelSphere.radius = 110;
    this->collider.elements[7].dim.modelSphere.center.x = 160;

    this->pythonIndex = EN_DRAGON_GET_PYTHON_INDEX(&this->actor);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->action = DEEP_PYTHON_ACTION_IDLE;
    this->actor.hintId = 0xE;
    this->scale = 0.5f;
    this->actor.flags &= ~ACTOR_FLAG_8000000;

    EnDragon_SetupRetreatOrIdle(this);
}

void EnDragon_Destroy(Actor* thisx, PlayState* play) {
    EnDragon* this = THIS;

    Collider_DestroyJntSph(play, &this->collider);
}

static AnimationHeader* sAnimations[] = {
    &gDeepPythonSmallSideSwayAnim,
    &gDeepPythonLargeSideSwayAnim,
    &gDeepPythonVerticalSwayAnim,
    &gDeepPythonSmallSideSwayAnim,
};

static u8 sAnimationModes[] = { ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE };

void EnDragon_ChangeAnimation(EnDragon* this, s32 animationIndex) {
    f32 startFrame;

    this->animationIndex = animationIndex;
    this->endFrame = Animation_GetLastFrame(sAnimations[animationIndex]);
    startFrame = 0.0f;
    if (this->animationIndex == DEEP_PYTHON_ANIMATION_IDLE) {
        startFrame = this->endFrame;
    }

    Animation_Change(&this->skelAnime, sAnimations[animationIndex], 1.0f, startFrame, this->endFrame,
                     sAnimationModes[this->animationIndex], -4.0f);
}

static Color_RGBA8 sBubblePrimColors[] = {
    { 255, 255, 255, 255 },
    { 150, 255, 255, 255 },
    { 100, 255, 255, 255 },
};

static Color_RGBA8 sBubbleEnvColors[] = {
    { 150, 150, 150, 0 },
    { 0, 100, 0, 255 },
    { 0, 0, 255, 255 },
};

void EnDragon_SpawnBubbles(EnDragon* this, PlayState* play, Vec3f basePos) {
    static Vec3f sBubbleVelocity = { 0.0f, 0.0f, 0.0f };
    static Vec3f sBubbleAccel = { 0.0f, 0.1f, 0.0f };
    s32 bubbleCount;
    s16 colorIndex;
    s16 scale;
    Vec3f bubblePos;
    s32 i;

    bubbleCount = (s32)randPlusMinusPoint5Scaled(5.0f) + 10;
    colorIndex = 0;
    if (this->action == DEEP_PYTHON_ACTION_DEAD) {
        colorIndex = 1;
        bubbleCount = (s32)randPlusMinusPoint5Scaled(5.0f) + 10;
    }

    for (i = 0; i < bubbleCount; i++) {
        Math_Vec3f_Copy(&bubblePos, &basePos);
        sBubbleVelocity.x = Rand_ZeroFloat(1.0f) * 23.0f;
        sBubbleVelocity.y = Rand_ZeroFloat(1.0f) * 10.0f;
        sBubbleVelocity.z = Rand_ZeroFloat(1.0f) * 23.0f;
        bubblePos.x += randPlusMinusPoint5Scaled(i * 30.0f);
        bubblePos.y += randPlusMinusPoint5Scaled(5.0f);
        bubblePos.z += randPlusMinusPoint5Scaled(i * 30.0f);
        sBubbleAccel.y = Rand_ZeroFloat(1.0f) * 20.0f * 3.0f;
        scale = Rand_S16Offset(380, 240);
        EffectSsDtBubble_SpawnCustomColor(play, &bubblePos, &sBubbleVelocity, &sBubbleAccel,
                                          &sBubblePrimColors[colorIndex], &sBubbleEnvColors[colorIndex], scale, 30, 0);
    }
}

void EnDragon_RetreatOnceTimerEnds(EnDragon* this, PlayState* play) {
    if (this->timer == 0) {
        func_800B8D50(play, &this->actor, 10.0f, this->actor.world.rot.y, 10.0f, 8);
        EnDragon_SetupRetreatOrIdle(this);
    }
}

void EnDragon_SetupRetreatOrIdle(EnDragon* this) {
    EnDragon_ChangeAnimation(this, DEEP_PYTHON_ANIMATION_IDLE);
    this->state = 0;
    this->unk_2CC = 0;
    this->hasGrabbedPlayer = false;
    this->grabTimer = 0;
    this->timer = 30;
    this->actionFunc = EnDragon_RetreatOrIdle;
}

void EnDragon_RetreatOrIdle(EnDragon* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (this->action == DEEP_PYTHON_ACTION_EXTEND) {
        EnDragon_SetupExtend(this);
    } else if ((this->timer != 0) && (fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 101.0f) &&
               (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 101.0f)) {
        this->actor.speedXZ = -100.0f;
    } else {
        this->actor.speedXZ = 0.0f;

        if ((fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 4.0f) &&
            (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 4.0f)) {
            Math_ApproachF(&this->actor.world.pos.x, this->actor.home.pos.x, 0.3f, 200.0f);
            Math_ApproachF(&this->actor.world.pos.z, this->actor.home.pos.z, 0.3f, 200.0f);
        } else if (this->action != DEEP_PYTHON_ACTION_IDLE) {
            this->action = DEEP_PYTHON_ACTION_IDLE;
        }
    }
}

void EnDragon_SetupExtend(EnDragon* this) {
    this->state = 0;
    this->behindJawRetreatTimer = this->state;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_APPEAR_TRG);
    this->retreatTimer = 250;
    this->actionFunc = EnDragon_Extend;
}

void EnDragon_Extend(EnDragon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 currentFrame = this->skelAnime.curFrame;
    s16 yaw;

    EnDragon_SpawnBubbles(this, play, this->jawPos);

    if (this->action >= DEEP_PYTHON_ACTION_DAMAGE) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BACK);
        EnDragon_SetupRetreatOrIdle(this);
    } else if (this->retreatTimer == 0) {
        this->action = DEEP_PYTHON_ACTION_RETREAT;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BACK);
        EnDragon_SetupRetreatOrIdle(this);
    } else if (this->state == DEEP_PYTHON_EXTEND_STATE_NOT_FULLY_EXTENDED) {
        Vec3f extendedPos;

        Math_Vec3f_Copy(&extendedPos, &this->burrowEntrancePos);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_APPEAR - SFX_FLAG);
        extendedPos.x += Math_SinS(this->actor.world.rot.y) * -530.0f;
        extendedPos.z += Math_CosS(this->actor.world.rot.y) * -530.0f;
        this->actor.speedXZ = 40.0f;
        Math_SmoothStepToS(&this->jawZRotation, 0xFA0, 5, 0xBB8, 0x14);

        if ((fabsf(this->actor.world.pos.x - extendedPos.x) < 51.0f) &&
            (fabsf(this->actor.world.pos.z - extendedPos.z) < 51.0f)) {
            this->actor.speedXZ = 0.0f;
            Math_ApproachF(&this->actor.world.pos.x, extendedPos.x, 0.3f, 50.0f);
            Math_ApproachF(&this->actor.world.pos.z, extendedPos.z, 0.3f, 50.0f);
            if ((fabsf(this->actor.world.pos.x - extendedPos.x) < 4.0f) &&
                (fabsf(this->actor.world.pos.z - extendedPos.z) < 4.0f)) {
                if (this->animationIndex != DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY) {
                    EnDragon_ChangeAnimation(this, DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY);
                }

                this->state = DEEP_PYTHON_EXTEND_STATE_FULLY_EXTENDED;
            }
        }
    } else {
        Math_SmoothStepToS(&this->jawZRotation, 0, 5, 0xBB8, 0x14);
        SkelAnime_Update(&this->skelAnime);
        if (this->state == DEEP_PYTHON_EXTEND_STATE_FULLY_EXTENDED) {
            if (currentFrame < this->endFrame) {
                return;
            }

            this->state = DEEP_PYTHON_EXTEND_STATE_REPEAT_LARGE_SWAY;
        }

        yaw = ABS_ALT(BINANG_SUB(Math_Vec3f_Yaw(&this->jawPos, &player->actor.world.pos), this->actor.shape.rot.y));
        if (yaw < 0x5000) {
            // Player is in front of the jaw
            if ((this->endFrame <= currentFrame) && (this->largeSwayWaitTimer == 0)) {
                if (this->animationIndex != DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY) {
                    EnDragon_ChangeAnimation(this, DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY);
                }

                this->state = DEEP_PYTHON_EXTEND_STATE_REPEAT_LARGE_SWAY;
            }

            this->behindJawRetreatTimer = 0;
        } else {
            // Player is in behind the jaw
            if (this->state == DEEP_PYTHON_EXTEND_STATE_REPEAT_LARGE_SWAY) {
                EnDragon_ChangeAnimation(this, DEEP_PYTHON_ANIMATION_SMALL_SIDE_SWAY);
                this->largeSwayWaitTimer = Rand_ZeroFloat(20.0f) + this->endFrame;
                this->state = DEEP_PYTHON_EXTEND_STATE_REPEAT_SMALL_SWAY;
            }

            this->behindJawRetreatTimer++;
            if (this->behindJawRetreatTimer > 60) {
                this->action = DEEP_PYTHON_ACTION_RETREAT;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BACK);
                EnDragon_SetupRetreatOrIdle(this);
            }
        }
    }
}

void EnDragon_SetSubCamEyeAt(EnDragon* this, PlayState* play, Vec3f subCamEye, Vec3f subCamAt) {
    this->subCamId = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
    Math_Vec3f_Copy(&this->subCamEye, &subCamEye);
    Math_Vec3f_Copy(&this->subCamAt, &subCamAt);
    Play_CameraSetAtEye(play, this->subCamId, &this->subCamAt, &this->subCamEye);
}

void EnDragon_SetupGrab(EnDragon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f extendedPos;
    s16 yaw;

    if (!ActorCutscene_GetCanPlayNext(this->grabCutsceneIndex)) {
        ActorCutscene_SetIntentToPlay(this->grabCutsceneIndex);
    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->grabCutsceneIndex, &this->actor);
        Math_Vec3f_Copy(&extendedPos, &this->burrowEntrancePos);
        extendedPos.x += Math_SinS(this->actor.world.rot.y) * -530.0f;
        extendedPos.z += Math_CosS(this->actor.world.rot.y) * -530.0f;
        Math_Vec3f_Copy(&this->actor.world.pos, &extendedPos);
        yaw = Math_Vec3f_Yaw(&player->actor.world.pos, &this->jawPos);
        player->actor.shape.rot.y = yaw;
        player->actor.world.rot.y = yaw;
        this->state = DEEP_PYTHON_GRAB_STATE_START;
        this->grabTimer = 0;
        this->hasGrabbedPlayer = false;
        EnDragon_ChangeAnimation(this, DEEP_PYTHON_ANIMATION_IDLE);
        this->actionFunc = EnDragon_Grab;
    }
}

static Vec3f sSubCamEyePerPython[] = {
    { 1600.0f, 0.0f, 1400.0f }, { 1400.0f, 0.0f, 400.0f },  { 1800.0f, 0.0f, 1400.f },  { 1100.0f, -200.0f, 1500.0f },
    { 2000.0f, 0.0f, 1500.0f }, { 1900.0f, 0.0f, 1800.0f }, { 1700.0f, 0.0f, 1100.0f }, { 1700.0f, 0.0f, 1100.0f },
};

static Vec3f sSubCamAtPerPython[] = {
    { 300.0f, -100.0f, 1300.0f }, { 1500.0f, 0.0f, 2400.0f }, { 300.0f, -100.0f, 1300.0f }, { 1900.0f, 500.0f, 600.0f },
    { -1000.0f, 0.0f, 1000.0f },  { 1200.0f, 0.0f, 1500.0f }, { 1100.0f, 0.0f, 2000.0f },   { 1100.0f, 0.0f, 2000.0f },
};

static s16 sZRotPerPython[] = { 0x07D0, 0x07D0, 0x07D0, 0x07D0, 0x07D0, 0x0BB8, 0x0000, 0x0000 };

static s32 sMaxGrabTimerPerPython[] = { 5, 5, 5, 4, 5, 8, 5, 5 };

void EnDragon_Grab(EnDragon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f pos; // used as both the extended position and the camera eye
    Vec3f subCamAt;

    this->subCamId = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
    SkelAnime_Update(&this->skelAnime);

    if (this->grabTimer == 0) {
        if (!this->hasGrabbedPlayer) {
            Math_Vec3f_Copy(&player->actor.world.pos, &this->playerGrabPosition);
            Math_Vec3f_Copy(&this->playerGrabPositionTemp, &this->playerGrabPosition);
            this->hasGrabbedPlayer = true;
        } else {
            Math_Vec3f_Copy(&player->actor.world.pos, &this->playerGrabPositionTemp);
        }

        Math_Vec3f_Copy(&pos, &this->burrowEntrancePos);
        pos.x += Math_SinS(this->actor.world.rot.y) * -930.0f;
        pos.z += Math_CosS(this->actor.world.rot.y) * -930.0f;
        Math_Vec3f_Copy(&this->actor.world.pos, &pos);
        this->jawZRotation = 0x1450;
        this->actor.speedXZ = 60.0f;
    }

    this->grabTimer++;
    Math_SmoothStepToS(&this->actor.shape.rot.z, sZRotPerPython[this->pythonIndex], 0xA, 0x1F4, 0x14);
    EnDragon_SpawnBubbles(this, play, this->jawPos);

    Math_Vec3f_Copy(&pos, &this->burrowEntrancePos);

    pos.x += Math_SinS(this->actor.world.rot.y) * sSubCamEyePerPython[this->pythonIndex].x;
    pos.y += sSubCamEyePerPython[this->pythonIndex].y;
    pos.z += Math_CosS(this->actor.world.rot.y) * sSubCamEyePerPython[this->pythonIndex].z;

    Math_Vec3f_Copy(&subCamAt, &this->actor.world.pos);
    subCamAt.x += Math_SinS(this->actor.world.rot.y) * sSubCamAtPerPython[this->pythonIndex].x;
    subCamAt.y += sSubCamAtPerPython[this->pythonIndex].y;
    subCamAt.z += Math_CosS(this->actor.world.rot.y) * sSubCamAtPerPython[this->pythonIndex].z;

    EnDragon_SetSubCamEyeAt(this, play, pos, subCamAt);

    if (this->grabTimer > sMaxGrabTimerPerPython[this->pythonIndex]) {
        if (this->state == DEEP_PYTHON_GRAB_STATE_START) {
            func_800B7298(play, &this->actor, 6);
            this->state = DEEP_PYTHON_GRAB_STATE_GRABBED;
        }

        play->unk_18770(play, player);
        player->actor.parent = &this->actor;
        player->unk_AE8 = 50;
        this->action = DEEP_PYTHON_ACTION_GRAB;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_EAT);
        EnDragon_SetupAttack(this);
    }
}

void EnDragon_SetupAttack(EnDragon* this) {
    if (this->animationIndex != DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY) {
        EnDragon_ChangeAnimation(this, DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY);
    }

    this->behindJawRetreatTimer = 0;
    this->grabTimer = 0;
    this->state = DEEP_PYTHON_ATTACK_STATE_START;
    this->actionFunc = EnDragon_Attack;
}

void EnDragon_Attack(EnDragon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 currentFrame = this->skelAnime.curFrame;
    Vec3f pos; // used as both the extended position and the camera eye
    Vec3f subCamAt;

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.shape.rot.z, 0, 0xA, 0x1388, 0);
    if ((play->gameplayFrames % 16) == 0) {
        play->damagePlayer(play, -2);

        //! @bug: This function should only pass Player*: it uses *(this + 0x153), which is meant to be
        //! player->currentMask, but in this case is garbage in the skelAnime
        func_800B8E58((Player*)this, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BITE);
        CollisionCheck_GreenBlood(play, NULL, &player->actor.world.pos);
    }

    Math_Vec3f_Copy(&pos, &this->actor.world.pos);
    pos.x += Math_SinS(this->actor.world.rot.y) * 3000.0f;
    pos.y += 600.0f;
    pos.z += Math_CosS(this->actor.world.rot.y) * 3000.0f;

    Math_Vec3f_Copy(&subCamAt, &this->actor.world.pos);
    subCamAt.x += Math_SinS(this->actor.world.rot.y) * 1200.0f;
    subCamAt.y += -100.0f;
    subCamAt.z += Math_CosS(this->actor.world.rot.y) * 1200.0f;

    EnDragon_SetSubCamEyeAt(this, play, pos, subCamAt);

    player->actor.world.rot.y = player->actor.shape.rot.y = this->actor.world.rot.y;
    player->actor.world.rot.x = player->actor.shape.rot.x = this->actor.world.rot.x;
    player->actor.world.rot.z = player->actor.shape.rot.z = this->actor.world.rot.z - 0x36B0;
    Math_Vec3f_Copy(&player->actor.world.pos, &this->playerGrabPosition);
    this->jawZRotation = 0xC8;

    Math_Vec3f_Copy(&pos, &this->burrowEntrancePos);
    pos.x += Math_SinS(this->actor.world.rot.y) * -530.0f;
    pos.z += Math_CosS(this->actor.world.rot.y) * -530.0f;
    Math_ApproachF(&this->actor.world.pos.x, pos.x, 0.3f, 200.0f);
    Math_ApproachF(&this->actor.world.pos.y, pos.y, 0.3f, 200.0f);
    Math_ApproachF(&this->actor.world.pos.z, pos.z, 0.3f, 200.0f);

    if ((this->state <= DEEP_PYTHON_ATTACK_STATE_START) && (this->endFrame <= currentFrame)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BITE);
        if (this->animationIndex != DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY) {
            EnDragon_ChangeAnimation(this, DEEP_PYTHON_ANIMATION_LARGE_SIDE_SWAY);
        }

        this->state++;
    }

    if (((this->state != DEEP_PYTHON_ATTACK_STATE_START) && (this->endFrame <= currentFrame)) ||
        (!(player->stateFlags2 & 0x80)) || ((this->collider.elements[0].info.bumperFlags & BUMP_HIT)) ||
        (this->collider.elements[1].info.bumperFlags & BUMP_HIT) ||
        (this->collider.elements[2].info.bumperFlags & BUMP_HIT)) {
        player->actor.parent = NULL;
        this->grabWaitTimer = 30;
        ActorCutscene_Stop(this->grabCutsceneIndex);
        if (player->stateFlags2 & 0x80) {
            player->unk_AE8 = 100;
        }

        this->actor.flags &= ~ACTOR_FLAG_100000;

        if ((this->state != DEEP_PYTHON_ATTACK_STATE_START) && (this->endFrame <= currentFrame)) {
            this->timer = 3;
            this->actionFunc = EnDragon_RetreatOnceTimerEnds;
        } else {
            EnDragon_SetupRetreatOrIdle(this);
        }
    }
}

void EnDragon_SetupDead(EnDragon* this, PlayState* play) {
    if (!ActorCutscene_GetCanPlayNext(this->deathCutsceneIndex)) {
        ActorCutscene_SetIntentToPlay(this->deathCutsceneIndex);
    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->deathCutsceneIndex, &this->actor);
        this->endFrame = Animation_GetLastFrame(&gDeepPythonSmallSideSwayAnim);
        Animation_Change(&this->skelAnime, &gDeepPythonSmallSideSwayAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
        this->timer = 20;
        this->actionFunc = EnDragon_Dead;
    }
}

void EnDragon_Dead(EnDragon* this, PlayState* play) {
    Vec3f seahorsePos;

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.z += 0x1000;
    this->jawZRotation = 0xFA0;
    EnDragon_SpawnBubbles(this, play, this->jawPos);

    if ((this->timer != 0) && (fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 121.0f) &&
        (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 121.0f)) {
        this->actor.speedXZ = -120.0f;
        if (((this->pythonIndex & 1) == 0) && (Rand_ZeroOne() < 0.5f)) {
            //! @bug: !play->gameplayFrames is 0 essentially all the time, so this code never runs.
            if (((!play->gameplayFrames) & 0x1F)) {
                Item_DropCollectibleRandom(play, NULL, &this->jawPos, 0x90);
            }
        }

        this->action = DEEP_PYTHON_ACTION_DEAD;
        return;
    }

    this->actor.speedXZ = 0.0f;
    if ((fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 20.0f) &&
        (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 20.0f)) {
        Math_ApproachF(&this->actor.world.pos.x, this->actor.home.pos.x, 0.3f, 300.0f);
        Math_ApproachF(&this->actor.world.pos.z, this->actor.home.pos.z, 0.3f, 300.0f);
        return;
    }

    sNumPythonsDead++;
    if (sNumPythonsDead >= (BREG(39) + 8)) {
        Math_Vec3f_Copy(&seahorsePos, &this->actor.parent->world.pos);
        seahorsePos.x += (Math_SinS((this->actor.parent->world.rot.y + 0x8000)) * (500.0f + BREG(38)));
        seahorsePos.y += -100.0f + BREG(33);
        seahorsePos.z += (Math_CosS((this->actor.parent->world.rot.y + 0x8000)) * (500.0f + BREG(38)));
        if (Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, ACTOR_EN_OT, seahorsePos.x, seahorsePos.y,
                                          seahorsePos.z, 0, this->actor.shape.rot.y, 0, 0x4000, this->actor.cutscene,
                                          this->actor.unk20, NULL)) {
            gSaveContext.save.weekEventReg[13] |= 1;
            switch (this->pythonIndex) {
                case 0:
                    gSaveContext.save.weekEventReg[83] |= 0x10;
                    break;

                case 1:
                    gSaveContext.save.weekEventReg[83] |= 0x20;
                    break;

                case 2:
                    gSaveContext.save.weekEventReg[83] |= 0x40;
                    break;

                case 3:
                    gSaveContext.save.weekEventReg[83] |= 0x80;
                    break;
                case 4:
                    gSaveContext.save.weekEventReg[84] |= 1;
                    break;

                case 5:
                    gSaveContext.save.weekEventReg[84] |= 2;
                    break;

                case 6:
                    gSaveContext.save.weekEventReg[84] |= 4;
                    break;

                case 7:
                    gSaveContext.save.weekEventReg[84] |= 8;
                    break;
            }
        }
    }

    Actor_MarkForDeath(&this->actor);
}

void EnDragon_UpdateDamage(EnDragon* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u32 sp30;

    if (this->action == DEEP_PYTHON_ACTION_EXTEND) {
        if ((this->collider.elements[2].info.bumperFlags & BUMP_HIT) ||
            (this->collider.elements[3].info.bumperFlags & BUMP_HIT) ||
            (this->collider.elements[4].info.bumperFlags & BUMP_HIT) ||
            (this->collider.elements[5].info.bumperFlags & BUMP_HIT) ||
            (this->collider.elements[6].info.bumperFlags & BUMP_HIT) ||
            (this->collider.elements[7].info.bumperFlags & BUMP_HIT)) {
            Actor_ApplyDamage(&this->actor);
            Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 25);
            if (this->actor.colChkInfo.health > 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_DAMAGE);
                this->action = DEEP_PYTHON_ACTION_DAMAGE;
            } else {
                Enemy_StartFinishingBlow(play, &this->actor);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_DEAD);
                this->actor.flags |= ACTOR_FLAG_8000000;
                this->actor.flags &= ~ACTOR_FLAG_1;
                this->actor.flags |= ACTOR_FLAG_100000;
                this->action = DEEP_PYTHON_ACTION_SETUP_DEAD;
                this->actionFunc = EnDragon_SetupDead;
            }
        }
    }

    if ((this->action == DEEP_PYTHON_ACTION_EXTEND) && (this->grabWaitTimer == 0) &&
        (player->invincibilityTimer == 0) && (this->collider.elements[0].info.ocElemFlags & OCELEM_HIT) &&
        (!(func_800B64FC(play, 1000.0f, &this->actor.world.pos, &sp30) >= 0.0f) || (sp30 != 1))) {
        this->actor.speedXZ = 0.0f;
        this->action = DEEP_PYTHON_ACTION_GRAB;
        this->actor.flags |= ACTOR_FLAG_100000;
        this->actionFunc = EnDragon_SetupGrab;
    }
}

void EnDragon_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnDragon* this = THIS;

    if (this->retreatTimer != 0) {
        this->retreatTimer--;
    }

    if (this->timer != 0) {
        this->timer--;
    }

    if (this->largeSwayWaitTimer != 0) {
        this->largeSwayWaitTimer--;
    }

    if (this->grabWaitTimer != 0) {
        this->grabWaitTimer--;
    }

    EnDragon_UpdateDamage(this, play);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->focusPos);
    Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    Actor_SetScale(&this->actor, this->scale);

    this->actionFunc(this, play);
    Actor_MoveWithGravity(&this->actor);

    if (this->action != DEEP_PYTHON_ACTION_GRAB) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->action < DEEP_PYTHON_ACTION_DAMAGE) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }
}

s32 EnDragon_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDragon* this = THIS;

    if (limbIndex == DEEP_PYTHON_LIMB_JAW) {
        rot->x += this->jawXRotation;
        rot->y += this->jawYRotation;
        rot->z += this->jawZRotation;
    }

    return false;
}

void EnDragon_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDragon* this = THIS;
    Vec3f playerGrabOffsetFromJawPos = { 350.0f, -120.0f, -60.0f };

    if (limbIndex == DEEP_PYTHON_LIMB_JAW) {
        Matrix_MultVec3f(&gZeroVec3f, &this->jawPos);
        playerGrabOffsetFromJawPos.x = 350.0f;
        playerGrabOffsetFromJawPos.y = -120.0f;
        playerGrabOffsetFromJawPos.z = -60.0f;
        Matrix_MultVec3f(&playerGrabOffsetFromJawPos, &this->playerGrabPosition);
    }

    if (limbIndex == DEEP_PYTHON_LIMB_HEAD_AND_COLLAR_ROOT) {
        Matrix_MultVec3f(&gZeroVec3f, &this->focusPos);
    }

    Collider_UpdateSpheres(limbIndex, &this->collider);
}

void EnDragon_Draw(Actor* thisx, PlayState* play) {
    EnDragon* this = THIS;

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnDragon_OverrideLimbDraw, EnDragon_PostLimbDraw, &this->actor);
}
