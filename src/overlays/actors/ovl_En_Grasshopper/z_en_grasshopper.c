/*
 * File: z_en_grasshopper.c
 * Overlay: ovl_En_Grasshopper
 * Description: Dragonfly
 */

#include "z_en_grasshopper.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10)

#define THIS ((EnGrasshopper*)thisx)

void EnGrasshopper_Init(Actor* thisx, PlayState* play);
void EnGrasshopper_Destroy(Actor* thisx, PlayState* play);
void EnGrasshopper_Update(Actor* thisx, PlayState* play);
void EnGrasshopper_Draw(Actor* thisx, PlayState* play);

void EnGrasshopper_ChangeAnim(EnGrasshopper* this, s32 animIndex);
void EnGrasshopper_RaiseTail(EnGrasshopper* this);
void EnGrasshopper_LowerTail(EnGrasshopper* this);
void EnGrasshopper_DecideAction(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_SetupFly(EnGrasshopper* this);
void EnGrasshopper_Fly(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_RoamInCircles(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_SetupBank(EnGrasshopper* this);
void EnGrasshopper_Bank(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_SetupBounced(EnGrasshopper* this);
void EnGrasshopper_Bounced(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_SetupApproachPlayer(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_ApproachPlayer(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_SetupAttack(EnGrasshopper* this);
void EnGrasshopper_Attack(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_SetupWaitAfterAttack(EnGrasshopper* this);
void EnGrasshopper_WaitAfterAttack(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_Damaged(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_Dead(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_SetupFall(EnGrasshopper* this);
void EnGrasshopper_Fall(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_InitializeEffect(EnGrasshopper* this, Vec3f* pos);
void EnGrasshopper_UpdateEffects(EnGrasshopper* this, PlayState* play);
void EnGrasshopper_DrawEffects(EnGrasshopper* this, PlayState* play);

typedef enum {
    /*  0 */ EN_GRASSHOPPER_ACTION_FLY,
    /*  1 */ EN_GRASSHOPPER_ACTION_ROAM_IN_CIRCLES,
    /*  2 */ EN_GRASSHOPPER_ACTION_BANK,
    /*  3 */ EN_GRASSHOPPER_ACTION_BOUNCED,
    /*  4 */ EN_GRASSHOPPER_ACTION_DECIDE_ACTION,
    /*  5 */ EN_GRASSHOPPER_ACTION_APPROACH_PLAYER,
    /*  6 */ EN_GRASSHOPPER_ACTION_ATTACK,
    /*  7 */ EN_GRASSHOPPER_ACTION_WAIT_AFTER_ATTACK,
    /*  8 */ EN_GRASSHOPPER_ACTION_DAMAGED,
    /*  9 */ EN_GRASSHOPPER_ACTION_DEAD,
    /* 10 */ EN_GRASSHOPPER_ACTION_FALL,
} EnGrasshopperAction;

typedef enum {
    /* 0 */ EN_GRASSHOPPER_DECISION_ATTACK,
    /* 1 */ EN_GRASSHOPPER_DECISION_FLY,
    /* 2 */ EN_GRASSHOPPER_DECISION_ROAM_IN_CIRCLES, // Never used in the final game
} EnGrasshopperNextAction;

typedef enum {
    /* 0 */ EN_GRASSHOPPER_BANK_STATE_BANKING,
    /* 1 */ EN_GRASSHOPPER_BANK_STATE_DONE,
} EnGrasshopperBankState;

typedef enum {
    /* 0 */ EN_GRASSHOPPER_ANIM_RAISE_TAIL,
    /* 1 */ EN_GRASSHOPPER_ANIM_LOWER_TAIL,
    /* 2 */ EN_GRASSHOPPER_ANIM_FLY,
    /* 3 */ EN_GRASSHOPPER_ANIM_ATTACK,
    /* 4 */ EN_GRASSHOPPER_ANIM_HOVER,
    /* 5 */ EN_GRASSHOPPER_ANIM_DAMAGE,
    /* 6 */ EN_GRASSHOPPER_ANIM_DEAD,
    /* 7 */ EN_GRASSHOPPER_ANIM_FALL,
} EnGrasshopperAnim;

static s32 sOccupiedIndices[] = {
    false, false, false, false, false,
};

static s8 sLimbIndexToShadowBodyPartsIndex[DRAGONFLY_LIMB_MAX] = {
    -1, -1, 0, 1, 2, 3, 4, 5, -1, -1, 6, 7, -1, 8, 9, -1, 10, 11, -1, 12, 13, -1, -1, -1,
};

static s8 sParentBodyParts[DRAGONFLY_LIMB_MAX] = {
    -1, -1, -1, 0, 1, 2, 3, -1, -1, -1, -1, 6, -1, -1, 8, -1, -1, 10, -1, -1, 12, -1, -1, -1,
};

static u8 sShadowSizes[DRAGONFLY_LIMB_MAX] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

typedef enum {
    /* 0x0 */ EN_GRASSHOPPER_DMGEFF_IMMUNE,     // Deals no damage
    /* 0x2 */ EN_GRASSHOPPER_DMGEFF_FIRE = 0x2, // Damages and sets the Dragonfly on fire
    /* 0x3 */ EN_GRASSHOPPER_DMGEFF_FREEZE,     // Damages and freezes the Dragonfly in ice
    /* 0x4 */ EN_GRASSHOPPER_DMGEFF_LIGHT_ORB,  // Damages and surrounds the Dragonfly with light orbs
    /* 0xE */ EN_GRASSHOPPER_DMGEFF_HOOK = 0xE, // If hit by the Hookshot, it pulls the Dragonfly towards the player
    /* 0xF */ EN_GRASSHOPPER_DMGEFF_NONE,       // Deals regular damage with no extra effect
} EnDragonflyDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Deku Stick     */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Horse trample  */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* Explosives     */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* Hookshot       */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_HOOK),
    /* Goron punch    */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Sword          */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Goron pound    */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(2, EN_GRASSHOPPER_DMGEFF_FIRE),
    /* Ice arrow      */ DMG_ENTRY(2, EN_GRASSHOPPER_DMGEFF_FREEZE),
    /* Light arrow    */ DMG_ENTRY(2, EN_GRASSHOPPER_DMGEFF_LIGHT_ORB),
    /* Goron spikes   */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Deku spin      */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Deku launch    */ DMG_ENTRY(2, EN_GRASSHOPPER_DMGEFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Zora barrier   */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Normal shield  */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* Light ray      */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* Thrown object  */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Zora punch     */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Spin attack    */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* Normal Roll    */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* Unblockable    */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, EN_GRASSHOPPER_DMGEFF_IMMUNE),
    /* Powder Keg     */ DMG_ENTRY(1, EN_GRASSHOPPER_DMGEFF_HOOK),
};

ActorInit En_Grasshopper_InitVars = {
    ACTOR_EN_GRASSHOPPER,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_GRASSHOPPER,
    sizeof(EnGrasshopper),
    (ActorFunc)EnGrasshopper_Init,
    (ActorFunc)EnGrasshopper_Destroy,
    (ActorFunc)EnGrasshopper_Update,
    (ActorFunc)EnGrasshopper_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { DRAGONFLY_LIMB_THORAX, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xF7CFFFFF, 0x07, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { DRAGONFLY_LIMB_TAIL_TIP, { { 0, 0, 0 }, 0 }, 0 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT2,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_1,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

void EnGrasshopper_Init(Actor* thisx, PlayState* play) {
    EnGrasshopper* this = THIS;
    s32 i;

    this->actor.hintId = TATL_HINT_ID_DRAGONFLY;
    this->actor.targetMode = 4;
    this->actor.colChkInfo.mass = 60;
    this->actor.colChkInfo.health = 2;

    Collider_InitAndSetJntSph(play, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
    this->collider.elements[0].dim.modelSphere.radius = 1;
    this->collider.elements[0].dim.scale = 22.0f;
    this->collider.elements[1].dim.modelSphere.radius = 1;
    this->collider.elements[1].dim.scale = 16.0f;
    this->collider.elements[1].dim.modelSphere.center.x = 1000;
    this->collider.elements[0].dim.modelSphere.center.x = this->collider.elements[0].dim.modelSphere.center.y =
        this->collider.elements[0].dim.modelSphere.center.z = this->collider.elements[1].dim.modelSphere.center.y =
            this->collider.elements[1].dim.modelSphere.center.z = 0;

    this->actor.flags |= ACTOR_FLAG_200;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 1.0f);
    this->actor.colChkInfo.damageTable = &sDamageTable;
    Math_Vec3f_Copy(&this->flyingHomePos, &this->actor.home.pos);
    this->action = EN_GRASSHOPPER_ACTION_FLY;
    this->index = -1;

    for (i = 0; i < ARRAY_COUNT(sOccupiedIndices); i++) {
        if (!sOccupiedIndices[i]) {
            this->index = i;
            sOccupiedIndices[i] = true;
            break;
        }
    }

    // Deciding a random index like this if all indices are occupied causes a bug in EnGrasshopper_Destroy.
    if (this->index < 0) {
        this->index = Rand_ZeroFloat(4.99f);
    }

    SkelAnime_Init(play, &this->skelAnime, &gDragonflySkel, &gDragonflyFlyAnim, this->jointTable, this->morphTable,
                   DRAGONFLY_LIMB_MAX);
    this->type = EN_GRASSHOPPER_GET_TYPE(&this->actor);
    if (this->type < EN_GRASSHOPPER_TYPE_UNUSED_NORMAL) {
        this->type = EN_GRASSHOPPER_TYPE_NORMAL;
    }

    if (this->type != EN_GRASSHOPPER_TYPE_GROWS_WHEN_SPAWNED) {
        this->dragonflyScale = 0.01f;
    } else {
        this->dragonflyScale = 0.0f;
        Actor_SetScale(&this->actor, 0.0f);
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
        Math_Vec3f_Copy(&this->flyingHomePos, &this->actor.world.pos);
        this->flyingHomePos.y += 90.0f;
        this->collider.elements[0].dim.modelSphere.radius = this->collider.elements[1].dim.modelSphere.radius =
            this->type;
    }

    this->baseFlyHeight = randPlusMinusPoint5Scaled(50.0f) + this->flyingHomePos.y;
    EnGrasshopper_SetupFly(this);
}

void EnGrasshopper_Destroy(Actor* thisx, PlayState* play) {
    EnGrasshopper* this = THIS;

    Collider_DestroyJntSph(play, &this->collider);

    //! @bug If the dragonfly selected a random index in EnGrasshopper_Init (because all indices were occupied),
    //! then two dragonflies will have the same index. When one of those dragonflies sharing an index is destroyed,
    //! it will mark the index as unoccupied, when it still occupied by at least one dragonfly.
    sOccupiedIndices[this->index] = false;
}

static AnimationHeader* sAnimations[] = {
    &gDragonflyRaiseTailAnim, // EN_GRASSHOPPER_ANIM_RAISE_TAIL
    &gDragonflyLowerTailAnim, // EN_GRASSHOPPER_ANIM_LOWER_TAIL
    &gDragonflyFlyAnim,       // EN_GRASSHOPPER_ANIM_FLY
    &gDragonflyAttackAnim,    // EN_GRASSHOPPER_ANIM_ATTACK
    &gDragonflyHoverAnim,     // EN_GRASSHOPPER_ANIM_HOVER
    &gDragonflyDamageAnim,    // EN_GRASSHOPPER_ANIM_DAMAGE
    &gDragonflyDeadAnim,      // EN_GRASSHOPPER_ANIM_DEAD
    &gDragonflyFallAnim,      // EN_GRASSHOPPER_ANIM_FALL
};

static u8 sAnimationModes[] = {
    ANIMMODE_ONCE, // EN_GRASSHOPPER_ANIM_RAISE_TAIL
    ANIMMODE_ONCE, // EN_GRASSHOPPER_ANIM_LOWER_TAIL
    ANIMMODE_LOOP, // EN_GRASSHOPPER_ANIM_FLY
    ANIMMODE_ONCE, // EN_GRASSHOPPER_ANIM_ATTACK
    ANIMMODE_LOOP, // EN_GRASSHOPPER_ANIM_HOVER
    ANIMMODE_ONCE, // EN_GRASSHOPPER_ANIM_DAMAGE
    ANIMMODE_ONCE, // EN_GRASSHOPPER_ANIM_DEAD
    ANIMMODE_ONCE, // EN_GRASSHOPPER_ANIM_FALL
};

void EnGrasshopper_ChangeAnim(EnGrasshopper* this, s32 animIndex) {
    f32 morphFrames;

    this->endFrame = Animation_GetLastFrame(sAnimations[animIndex]);
    morphFrames = 0.0f;
    if ((animIndex == EN_GRASSHOPPER_ANIM_ATTACK) || (animIndex == EN_GRASSHOPPER_ANIM_HOVER) ||
        (animIndex == EN_GRASSHOPPER_ANIM_DAMAGE)) {
        morphFrames = -3.0f;
    }

    Animation_Change(&this->skelAnime, sAnimations[animIndex], 1.0f, 0.0f, this->endFrame, sAnimationModes[animIndex],
                     morphFrames);
}

void EnGrasshopper_RaiseTail(EnGrasshopper* this) {
    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_RAISE_TAIL);
    if (this->decision != EN_GRASSHOPPER_DECISION_ROAM_IN_CIRCLES) {
        this->decision = EN_GRASSHOPPER_DECISION_FLY;
    }

    this->action = EN_GRASSHOPPER_ACTION_DECIDE_ACTION;
    this->actionFunc = EnGrasshopper_DecideAction;
}

void EnGrasshopper_LowerTail(EnGrasshopper* this) {
    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_LOWER_TAIL);
    this->action = EN_GRASSHOPPER_ACTION_DECIDE_ACTION;
    this->decision = EN_GRASSHOPPER_DECISION_ATTACK;
    this->actionFunc = EnGrasshopper_DecideAction;
}

void EnGrasshopper_DecideAction(EnGrasshopper* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    if (curFrame >= this->endFrame) {
        if (this->decision == EN_GRASSHOPPER_DECISION_ATTACK) {
            EnGrasshopper_SetupAttack(this);
        } else {
            Math_Vec3f_Copy(&this->flyingHomePos, &this->actor.world.pos);
            this->flyingHomePos.y = this->actor.floorHeight + 90.0f;
            EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_FLY);
            if (this->decision != EN_GRASSHOPPER_DECISION_ROAM_IN_CIRCLES) {
                if (Player_GetMask(play) == PLAYER_MASK_STONE) {
                    EnGrasshopper_SetupFly(this);
                } else {
                    EnGrasshopper_SetupApproachPlayer(this, play);
                }
            } else {
                this->timer = 0;
                this->action = EN_GRASSHOPPER_ACTION_ROAM_IN_CIRCLES;
                this->decision = EN_GRASSHOPPER_DECISION_ATTACK;
                this->waitTimer = this->timer;
                this->actionFunc = EnGrasshopper_RoamInCircles;
            }
        }
    }
}

void EnGrasshopper_SetupFly(EnGrasshopper* this) {
    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_FLY);
    this->baseFlyHeight = randPlusMinusPoint5Scaled(50.0f) + this->flyingHomePos.y;
    this->action = EN_GRASSHOPPER_ACTION_FLY;
    this->actionFunc = EnGrasshopper_Fly;
}

void EnGrasshopper_Fly(EnGrasshopper* this, PlayState* play) {
    f32 diffX;
    f32 diffZ;
    f32 targetSpeed;
    Vec3f collisionCheckPos;

    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_FLY - SFX_FLAG);
    diffX = this->flyingHomePos.x - this->actor.world.pos.x;
    diffZ = this->flyingHomePos.z - this->actor.world.pos.z;
    if ((this->type != EN_GRASSHOPPER_TYPE_WOODFALL_TEMPLE_FINAL_ROOM) &&
        (this->type != EN_GRASSHOPPER_TYPE_WOODFALL)) {
        this->bobPhase += 0xAF0;
        this->targetPosY = (Math_SinS(this->bobPhase) * 10.0f) + this->baseFlyHeight;
        Math_ApproachF(&this->actor.world.pos.y, this->targetPosY, 0.1f, 10.0f);
        collisionCheckPos.x = (Math_SinS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.x;
        collisionCheckPos.y = this->actor.world.pos.y;
        collisionCheckPos.z = (Math_CosS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.z;

        if (this->collider.elements[0].info.ocElemFlags & OCELEM_HIT) {
            this->shouldTurn = true;
        }

        if (BgCheck_SphVsFirstPoly(&play->colCtx, &collisionCheckPos, 10.0f)) {
            this->shouldTurn = true;
        } else {
            this->shouldTurn = false;
        }

        //! @bug Unreachable code. To get here, the type must NOT be EN_GRASSHOPPER_TYPE_WOODFALL
        if (this->type == EN_GRASSHOPPER_TYPE_WOODFALL) {
            if (sqrtf(SQ(this->actor.world.pos.x) + SQ(this->actor.world.pos.z)) < 600.0f) {
                this->shouldTurn = true;
            }
        }

        if (this->shouldTurn) {
            this->baseFlyHeight = randPlusMinusPoint5Scaled(50.0f) + this->flyingHomePos.y;
            this->targetRot.y = Math_Atan2S(diffX, diffZ);
            this->timer = Rand_S16Offset(30, 30);
        }
    }

    if ((Player_GetMask(play) != PLAYER_MASK_STONE) && !CHECK_EVENTINF(EVENTINF_41) && !this->shouldTurn &&
        (this->actor.xzDistToPlayer < 200.0f)) {
        EnGrasshopper_SetupApproachPlayer(this, play);
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.z, this->targetRot.z, 5, 0x3E8, 5);
        this->targetRot.z *= 0.8f;
        if (this->waitTimer != 0) {
            Math_ApproachZeroF(&this->actor.speed, 0.2f, 0.5f);
        } else {
            this->targetRot.z = (this->actor.world.rot.y - this->targetRot.y) * 0.2f;
            targetSpeed = (this->index * 0.1f) + 4.0f;
            Math_ApproachF(&this->actor.speed, targetSpeed, 0.4f, 0.7f);
            Math_ApproachF(&this->rotationalVelocity, 2000.0f, 1.0f, 50.0f);
            Math_SmoothStepToS(&this->actor.world.rot.y, this->targetRot.y, 5, this->rotationalVelocity, 5);
            if (this->timer == 0) {
                if (Rand_ZeroFloat(1.0f) < 0.3f) {
                    this->waitTimer = Rand_S16Offset(10, 10);
                    this->rotationalVelocity = 0.0f;
                }

                this->targetRot.y = Math_Atan2S(diffX, diffZ);
                this->timer = Rand_S16Offset(30, 70);
                this->baseFlyHeight = randPlusMinusPoint5Scaled(50.0f) + this->flyingHomePos.y;
            }
        }
    }
}

/**
 * Unused in the final game. Makes the dragonfly roam the area in a very wide circular arc.
 */
void EnGrasshopper_RoamInCircles(EnGrasshopper* this, PlayState* play) {
    f32 diffX;
    f32 diffZ;
    f32 targetSpeed;
    s16 rotationSpeed;
    s32 pad;
    Vec3f collisionCheckPos;
    Player* player = GET_PLAYER(play);

    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_FLY - SFX_FLAG);
    if (Player_GetMask(play) == PLAYER_MASK_STONE) {
        EnGrasshopper_SetupFly(this);
    } else {
        diffX = player->actor.world.pos.x - this->actor.world.pos.x;
        diffZ = player->actor.world.pos.z - this->actor.world.pos.z;
        this->bobPhase += 0xAF0;
        this->targetPosY = player->actor.world.pos.y + 60.0f;
        this->baseFlyHeight = Math_SinS(this->bobPhase) * 10.0f;

        if (this->timer == 0) {
            this->baseFlyHeight = randPlusMinusPoint5Scaled(10.0f);
            this->timer = Rand_S16Offset(30, 30);
        }

        Math_ApproachF(&this->actor.world.pos.y, this->targetPosY, 0.1f, 10.0f);
        collisionCheckPos.x = (Math_SinS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.x;
        collisionCheckPos.y = this->actor.world.pos.y;
        collisionCheckPos.z = (Math_CosS(this->actor.shape.rot.y) * 100.0f) + this->actor.world.pos.z;

        if ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) ||
            BgCheck_SphVsFirstPoly(&play->colCtx, &collisionCheckPos, 10.0f)) {
            EnGrasshopper_SetupBank(this);
        } else if (player->stateFlags1 & PLAYER_STATE1_8000000) {
            this->collider.elements[0].info.toucherFlags |= (TOUCH_ON | TOUCH_SFX_WOOD);
            EnGrasshopper_RaiseTail(this);
        } else if (this->collider.base.atFlags & AT_BOUNCED) {
            this->collider.elements[0].info.toucherFlags &= ~(TOUCH_ON | TOUCH_SFX_WOOD);
            EnGrasshopper_SetupBounced(this);
        } else {
            this->targetRot.z = (this->actor.world.rot.y - this->targetRot.y) * 0.2f;
            Math_SmoothStepToS(&this->actor.world.rot.z, this->targetRot.z, 5, 0x3E8, 5);
            rotationSpeed = this->index + 70;
            targetSpeed = (this->index * 0.05f) + 4.0f;
            this->targetRot.y = Math_Atan2S(diffX, diffZ);
            Math_ApproachF(&this->actor.speed, targetSpeed, 0.4f, 0.8f);
            Math_SmoothStepToS(&this->actor.world.rot.y, this->targetRot.y, rotationSpeed, 0xFA0, 0xA);
        }
    }
}

/**
 * Unused in the final game.
 */
void EnGrasshopper_SetupBank(EnGrasshopper* this) {
    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_FLY - SFX_FLAG);
    this->targetBankRot.y = this->actor.world.rot.y + 0x8000;
    this->action = EN_GRASSHOPPER_ACTION_BANK;
    this->bankState = EN_GRASSHOPPER_BANK_STATE_BANKING;
    this->actor.speed = 2.0f;
    this->actionFunc = EnGrasshopper_Bank;
}

/**
 * Unused in the final game. Makes the dragonfly perform a wide banking turn on its side, then
 * it flies forward for 100 frames.
 */
void EnGrasshopper_Bank(EnGrasshopper* this, PlayState* play) {
    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_FLY - SFX_FLAG);
    switch (this->bankState) {
        case EN_GRASSHOPPER_BANK_STATE_BANKING:
            Math_SmoothStepToS(&this->actor.world.rot.y, this->targetBankRot.y, 0x64, 0x3E8, 0x3E8);
            Math_SmoothStepToS(&this->actor.world.rot.z, 0x4000, 0x64, 0x1F40, 0xBB8);
            if (fabsf(this->actor.world.rot.y - (f32)this->targetBankRot.y) < 10.0f) {
                this->postBankTimer = 100;
                this->bankState = EN_GRASSHOPPER_BANK_STATE_DONE;
            }
            break;

        case EN_GRASSHOPPER_BANK_STATE_DONE:
            Math_SmoothStepToS(&this->actor.world.rot.z, 0, 0x64, 0x1F40, 0xBB8);
            if (this->postBankTimer == 0) {
                this->timer = 0;
                this->action = EN_GRASSHOPPER_ACTION_ROAM_IN_CIRCLES;
                this->decision = EN_GRASSHOPPER_DECISION_ATTACK;
                this->waitTimer = this->timer;
                this->actionFunc = EnGrasshopper_RoamInCircles;
            }
            break;
    }
}

/**
 * Unused in the final game.
 */
void EnGrasshopper_SetupBounced(EnGrasshopper* this) {
    this->targetRot.y = -this->actor.yawTowardsPlayer;
    this->timer = Rand_S16Offset(30, 30);
    this->targetRot.z = (this->actor.world.rot.y - this->targetRot.y) * 0.2f;
    this->action = EN_GRASSHOPPER_ACTION_BOUNCED;
    this->actionFunc = EnGrasshopper_Bounced;
}

/**
 * Unused in the final game. Makes the dragonfly rotate away from the player, then go
 * back to roaming in circles.
 */
void EnGrasshopper_Bounced(EnGrasshopper* this, PlayState* play) {
    f32 targetSpeed;

    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_FLY - SFX_FLAG);
    targetSpeed = (this->index * 0.05f) + 7.0f;
    Math_ApproachF(&this->actor.speed, targetSpeed, 0.4f, 0.8f);
    Math_SmoothStepToS(&this->actor.world.rot.z, this->targetRot.z, 5, 0x3E8, 5);
    this->targetRot.z *= 0.8f;
    Math_SmoothStepToS(&this->actor.world.rot.y, this->targetRot.y, 5, this->rotationalVelocity, 5);
    if (this->timer == 0) {
        this->collider.elements[0].info.toucherFlags |= (TOUCH_ON | TOUCH_SFX_WOOD);
        this->timer = 0;
        this->action = EN_GRASSHOPPER_ACTION_ROAM_IN_CIRCLES;
        this->waitTimer = this->timer;
        this->actionFunc = EnGrasshopper_RoamInCircles;
    }
}

void EnGrasshopper_SetupApproachPlayer(EnGrasshopper* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    this->timer = 50;
    this->action = EN_GRASSHOPPER_ACTION_APPROACH_PLAYER;
    this->approachSpeed = 0.0f;
    this->targetApproachPos.x = (Math_SinS(player->actor.shape.rot.y) * 130.0f) + player->actor.world.pos.x;
    this->targetApproachPos.z = (Math_CosS(player->actor.shape.rot.y) * 130.0f) + player->actor.world.pos.z;
    this->actionFunc = EnGrasshopper_ApproachPlayer;
}

/**
 * Approaches the player in preparation for an attack. It will also attack if the timer reaches 0.
 */
void EnGrasshopper_ApproachPlayer(EnGrasshopper* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    WaterBox* waterBox;
    Vec3f splashPos;

    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_FLY - SFX_FLAG);
    this->bobPhase += 0xAF0;
    this->targetApproachPos.y = (Math_SinS(this->bobPhase) * 10.0f) + (player->actor.world.pos.y + 120.0f);

    Math_SmoothStepToS(&this->actor.world.rot.z, 0, 5, 0x3E8, 5);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.shape.rot.y, 0xA, 0xFA0, 0xA);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0xFA0, 0xA);
    Math_ApproachF(&this->actor.world.pos.x, this->targetApproachPos.x, 0.3f, this->approachSpeed);
    Math_ApproachF(&this->actor.world.pos.y, this->targetApproachPos.y, 0.1f, this->approachSpeed);
    Math_ApproachF(&this->actor.world.pos.z, this->targetApproachPos.z, 0.3f, this->approachSpeed);
    Math_ApproachF(&this->approachSpeed, 7.0f, 0.3f, 1.0f);

    if (WaterBox_GetSurface1(play, &play->colCtx, this->tailTipPos.x, this->tailTipPos.z, &this->waterSurface,
                             &waterBox)) {
        if (this->tailTipPos.y < this->waterSurface) {
            if ((this->splashCount < 3) || !(play->gameplayFrames % 8)) {
                this->splashCount++;
                Math_Vec3f_Copy(&splashPos, &this->tailTipPos);
                splashPos.x += randPlusMinusPoint5Scaled(20.0f);
                splashPos.z += randPlusMinusPoint5Scaled(20.0f);
                EffectSsGSplash_Spawn(play, &splashPos, NULL, NULL, 0, (((s32)Rand_ZeroOne() * 100) + 400));
                SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EV_BOMB_DROP_WATER);
            }
        } else {
            this->splashCount = 0;
        }
    }

    if ((this->timer == 0) || ((fabsf(this->targetApproachPos.x - this->actor.world.pos.x) <= 10.0f) &&
                               (fabsf(this->targetApproachPos.y - this->actor.world.pos.y) <= 20.0f) &&
                               (fabsf(this->targetApproachPos.z - this->actor.world.pos.z) <= 10.0f))) {
        EnGrasshopper_LowerTail(this);
    }
}

void EnGrasshopper_SetupAttack(EnGrasshopper* this) {
    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_ATTACK);
    this->approachSpeed = 0.0f;
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0xFA0, 0xA);
    this->actor.speed = 3.0f;
    this->baseFlyHeight = this->actor.world.pos.y;
    this->collider.elements[0].info.toucherFlags &= ~(TOUCH_ON | TOUCH_SFX_WOOD);
    this->collider.elements[1].info.toucherFlags |= (TOUCH_ON | TOUCH_SFX_WOOD);
    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_ATTACK);
    this->action = EN_GRASSHOPPER_ACTION_ATTACK;
    this->actionFunc = EnGrasshopper_Attack;
}

void EnGrasshopper_Attack(EnGrasshopper* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 curFrame = this->skelAnime.curFrame;
    Vec3f hitPos;
    Vec3f diff;
    f32 playerToHitPosDist;
    s32 i;
    WaterBox* waterBox;
    Vec3f splashPos;

    for (i = 0; i < 6; i++) {
        EnGrasshopper_InitializeEffect(this, &this->tailTipPos);
    }

    if (WaterBox_GetSurface1(play, &play->colCtx, this->tailTipPos.x, this->tailTipPos.z, &this->waterSurface,
                             &waterBox)) {
        if (this->tailTipPos.y < this->waterSurface) {
            if ((this->splashCount < 3) || !(play->gameplayFrames % 8)) {
                this->splashCount++;
                Math_Vec3f_Copy(&splashPos, &this->tailTipPos);
                splashPos.x += randPlusMinusPoint5Scaled(20.0f);
                splashPos.z += randPlusMinusPoint5Scaled(20.0f);
                EffectSsGSplash_Spawn(play, &splashPos, NULL, NULL, 0, ((s32)Rand_ZeroOne() * 100) + 400);
                SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EV_BOMB_DROP_WATER);
            }
        } else {
            this->splashCount = 0;
        }
    }

    this->bobPhase += 0xAF0;
    this->targetApproachPos.y = (Math_SinS(this->bobPhase) * 10.0f) + (player->actor.world.pos.y + 60.0f);

    hitPos.x = this->collider.elements[1].info.bumper.hitPos.x;
    hitPos.y = this->collider.elements[1].info.bumper.hitPos.y;
    hitPos.z = this->collider.elements[1].info.bumper.hitPos.z;
    diff.x = hitPos.x - player->actor.world.pos.x;
    diff.y = hitPos.y - player->actor.world.pos.y;
    diff.z = hitPos.z - player->actor.world.pos.z;
    playerToHitPosDist = sqrtf(SQXYZ(diff));

    if ((this->collider.base.atFlags & AT_BOUNCED) ||
        ((player->stateFlags1 & PLAYER_STATE1_400000) && (playerToHitPosDist <= 60.0f) &&
         ((s16)((player->actor.shape.rot.y - this->actor.shape.rot.y) + 0x8000) < 0x2000) &&
         ((s16)((player->actor.shape.rot.y - this->actor.shape.rot.y) + 0x8000) > -0x2000))) {
        this->collider.elements[1].info.toucherFlags &= ~(TOUCH_ON | TOUCH_SFX_WOOD);
    }

    Math_ApproachF(&this->actor.world.pos.y, this->targetApproachPos.y, 0.1f, this->approachSpeed);
    Math_ApproachF(&this->approachSpeed, 10.0f, 0.1f, 1.0f);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0xFA0, 0xA);
    if (curFrame >= this->endFrame) {
        EnGrasshopper_SetupWaitAfterAttack(this);
    }
}

void EnGrasshopper_SetupWaitAfterAttack(EnGrasshopper* this) {
    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_HOVER);
    this->bobPhase += 0xAF0;
    this->targetPosY = (Math_SinS(this->bobPhase) * 10.0f) + this->baseFlyHeight;
    Math_ApproachF(&this->actor.world.pos.y, this->targetPosY, 0.1f, 10.0f);
    this->action = EN_GRASSHOPPER_ACTION_WAIT_AFTER_ATTACK;
    this->waitTimer = 20;
    this->actor.speed = 0.0f;
    this->collider.elements[1].info.toucherFlags &= ~(TOUCH_ON | TOUCH_SFX_WOOD);
    this->actionFunc = EnGrasshopper_WaitAfterAttack;
}

/**
 * Hover in place for a bit after an attack before raising the tail back up.
 */
void EnGrasshopper_WaitAfterAttack(EnGrasshopper* this, PlayState* play) {
    this->bobPhase += 0xAF0;
    this->targetPosY = (Math_SinS(this->bobPhase) * 10.0f) + this->baseFlyHeight;
    Math_ApproachF(&this->actor.world.pos.y, this->targetPosY, 0.1f, 10.0f);
    if (this->waitTimer == 0) {
        this->collider.elements[0].info.toucherFlags |= (TOUCH_ON | TOUCH_SFX_WOOD);
        EnGrasshopper_RaiseTail(this);
    }
}

void EnGrasshopper_SetupDamaged(EnGrasshopper* this, PlayState* play) {
    Vec3f damagedVelocity;

    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_DAMAGE);
    this->actor.speed = 0.0f;
    this->actor.flags |= ACTOR_FLAG_1;
    this->approachSpeed = 0.0f;
    this->collider.elements[1].info.toucherFlags &= ~(TOUCH_ON | TOUCH_SFX_WOOD);
    Matrix_RotateYS(this->actor.yawTowardsPlayer, MTXMODE_NEW);
    Matrix_MultVecZ(-20.0f, &damagedVelocity);
    Math_Vec3f_Copy(&this->damagedVelocity, &damagedVelocity);
    if (((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
         (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) &&
        (this->drawDmgEffTimer != 0)) {
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), 2, 0.3f, 0.2f);
        this->drawDmgEffTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    }

    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
    this->action = EN_GRASSHOPPER_ACTION_DAMAGED;
    this->actionFunc = EnGrasshopper_Damaged;
}

void EnGrasshopper_Damaged(EnGrasshopper* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.world.rot.z, 0, 5, 0x3E8, 5);
    if (this->actor.colorFilterTimer == 0) {
        EnGrasshopper_RaiseTail(this);
    }
}

void EnGrasshopper_SetupDead(EnGrasshopper* this, PlayState* play) {
    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_DEAD);
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->actor.speed = 0.0f;
    this->approachSpeed = 0.0f;
    this->actor.velocity.y = 5.0f;
    this->actor.gravity = -0.5f;
    if (((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
         (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) &&
        (this->drawDmgEffTimer == 0)) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    }

    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 25);
    Enemy_StartFinishingBlow(play, &this->actor);
    Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_DEAD);
    this->action = EN_GRASSHOPPER_ACTION_DEAD;
    this->actionFunc = EnGrasshopper_Dead;
}

/**
 * Plays the death animation before transitioning to falling from the sky.
 */
void EnGrasshopper_Dead(EnGrasshopper* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    Math_SmoothStepToS(&this->actor.world.rot.z, 0, 5, 0x3E8, 5);
    if (((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
         (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) &&
        (this->drawDmgEffTimer < 2)) {
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), 2, 0.3f, 0.2f);
        this->drawDmgEffTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    }

    if (curFrame >= this->endFrame) {
        this->actor.flags &= ~ACTOR_FLAG_10;
        EnGrasshopper_SetupFall(this);
    }
}

void EnGrasshopper_SetupFall(EnGrasshopper* this) {
    EnGrasshopper_ChangeAnim(this, EN_GRASSHOPPER_ANIM_FALL);
    this->action = EN_GRASSHOPPER_ACTION_FALL;
    this->actor.speed = 0.0f;
    this->approachSpeed = 0.0f;
    this->actionFunc = EnGrasshopper_Fall;
}

/**
 * Falls from the sky and bursts into flames once it touches land or water.
 */
void EnGrasshopper_Fall(EnGrasshopper* this, PlayState* play) {
    WaterBox* waterBox;
    f32 waterSurface;
    s32 isUnderWater = false;

    this->actor.shape.rot.y += 0x1388;
    if ((this->actor.floorHeight <= BGCHECK_Y_MIN) || (this->actor.floorHeight >= BGCHECK_Y_MAX)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &waterSurface,
                             &waterBox)) {
        if (this->actor.world.pos.y < waterSurface) {
            Vec3f splashPos;
            s32 i;

            for (i = 0; i < 3; i++) {
                Math_Vec3f_Copy(&splashPos, &this->actor.world.pos);
                splashPos.x += randPlusMinusPoint5Scaled((i * 5.0f) + 20.0f);
                splashPos.z += randPlusMinusPoint5Scaled((i * 5.0f) + 20.0f);
                EffectSsGSplash_Spawn(play, &splashPos, NULL, NULL, 0, (((s32)Rand_ZeroOne() * 100) + 400));
            }

            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EV_BOMB_DROP_WATER);
            isUnderWater = true;
        }
    }

    if ((BgCheck_SphVsFirstPoly(&play->colCtx, &this->tailTipPos, 40.0f)) &&
        (((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX)) ||
         (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) &&
        (this->drawDmgEffTimer != 0)) {
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), 2, 0.3f, 0.2f);
        this->drawDmgEffTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    }

    if (isUnderWater || (BgCheck_SphVsFirstPoly(&play->colCtx, &this->tailTipPos, 10.0f))) {
        Vec3f firePos;
        Vec3f sFireVelocityAndAccel[] = {
            { 1.0f, 0.0f, 0.5f },   { 1.0f, 0.0f, -0.5f },  { -1.0f, 0.0f, 0.5f },
            { -1.0f, 0.0f, -0.5f }, { 0.5f, 0.0f, 1.0f },   { -0.5f, 0.0f, 1.0f },
            { 0.5f, 0.0f, -1.0f },  { -0.5f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f },
        };
        s32 i;

        for (i = 0; i < ARRAY_COUNT(sFireVelocityAndAccel); i++) {
            Math_Vec3f_Copy(&firePos, &this->actor.world.pos);
            firePos.x += randPlusMinusPoint5Scaled(30.0f);
            if (!isUnderWater) {
                firePos.y = this->actor.floorHeight;
            } else if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                            &waterSurface, &waterBox)) {
                firePos.y = waterSurface;
            }

            firePos.z += randPlusMinusPoint5Scaled(30.0f);
            func_800B3030(play, &firePos, &sFireVelocityAndAccel[i], &sFireVelocityAndAccel[i], 100, 0, 2);
        }

        SoundSource_PlaySfxEachFrameAtFixedWorldPos(play, &this->actor.world.pos, 10,
                                                    NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG);
        Item_DropCollectibleRandom(play, NULL, &this->actor.world.pos, 0x60);
        Actor_Kill(&this->actor);
    }
}

void EnGrasshopper_UpdateDamage(EnGrasshopper* this, PlayState* play) {
    s32 pad;
    s16 attackDealsDamage = false;

    if ((this->collider.elements[0].info.bumperFlags & BUMP_HIT) ||
        (this->collider.elements[1].info.bumperFlags & BUMP_HIT)) {
        this->collider.base.acFlags &= ~AC_HIT;
        if ((this->action != EN_GRASSHOPPER_ACTION_DAMAGED) && (this->action != EN_GRASSHOPPER_ACTION_DEAD) &&
            (this->action != EN_GRASSHOPPER_ACTION_FALL)) {
            if (this->actor.colChkInfo.damageEffect == EN_GRASSHOPPER_DMGEFF_NONE) {
                attackDealsDamage = true;
            } else if (this->actor.colChkInfo.damageEffect == EN_GRASSHOPPER_DMGEFF_FIRE) {
                this->drawDmgEffTimer = 40;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                attackDealsDamage = true;
            } else if (this->actor.colChkInfo.damageEffect == EN_GRASSHOPPER_DMGEFF_FREEZE) {
                if ((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_BLUE_FIRE) || (this->drawDmgEffTimer == 0)) {
                    Actor_ApplyDamage(&this->actor);
                    attackDealsDamage = false;
                    this->drawDmgEffTimer = 80;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
                    this->drawDmgEffScale = 0.0f;
                    this->drawDmgEffFrozenSteamScale = 1.5f;
                }

                if (this->actor.colChkInfo.health <= 0) {
                    EnGrasshopper_SetupDead(this, play);
                    return;
                }
            } else if (this->actor.colChkInfo.damageEffect == EN_GRASSHOPPER_DMGEFF_LIGHT_ORB) {
                Actor_SetColorFilter(&this->actor, 0x8000, 255, 0, 25);
                this->drawDmgEffTimer = 20;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x, this->actor.focus.pos.y,
                            this->actor.focus.pos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                attackDealsDamage = true;
            }
        }
    }

    if (attackDealsDamage) {
        Actor_ApplyDamage(&this->actor);
        if (this->actor.colChkInfo.health > 0) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_BATTA_DAMAGE);
            EnGrasshopper_SetupDamaged(this, play);
        } else {
            EnGrasshopper_SetupDead(this, play);
        }
    }
}

void EnGrasshopper_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnGrasshopper* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    EnGrasshopper_UpdateDamage(this, play);
    this->actionFunc(this, play);

    Actor_SetFocus(&this->actor, 0.0f);
    Actor_SetScale(&this->actor, this->dragonflyScale);

    DECR(this->timer);
    DECR(this->waitTimer);
    DECR(this->postBankTimer);
    DECR(this->drawDmgEffTimer);

    Actor_MoveWithGravity(&this->actor);
    this->actor.world.pos.x += this->damagedVelocity.x;
    this->actor.world.pos.y += this->damagedVelocity.y;
    this->actor.world.pos.z += this->damagedVelocity.z;
    Math_ApproachZeroF(&this->damagedVelocity.x, 1.0f, 2.0f);
    Math_ApproachZeroF(&this->damagedVelocity.y, 1.0f, 2.0f);
    Math_ApproachZeroF(&this->damagedVelocity.z, 1.0f, 2.0f);
    if ((this->action != EN_GRASSHOPPER_ACTION_FALL) && (this->type != EN_GRASSHOPPER_TYPE_WOODFALL)) {
        Actor_UpdateBgCheckInfo(play, &this->actor, 35.0f, 60.0f, 60.0f, 0x1D);
    }

    this->actor.shape.rot.z = this->actor.world.rot.z;
    if (this->type == EN_GRASSHOPPER_TYPE_GROWS_WHEN_SPAWNED) {
        f32 targetScale = this->type * 0.01f;

        if (targetScale >= 0.018f) {
            targetScale = 0.018f;
        }

        Math_ApproachF(&this->dragonflyScale, targetScale, 0.1f, 0.01f);
    }

    if ((this->action != EN_GRASSHOPPER_ACTION_FALL) && (this->action != EN_GRASSHOPPER_ACTION_APPROACH_PLAYER)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 5, 0x3E8, 5);
    }

    EnGrasshopper_UpdateEffects(this, play);
    if ((this->action != EN_GRASSHOPPER_ACTION_DEAD) && (this->action != EN_GRASSHOPPER_ACTION_FALL)) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        if ((this->action == EN_GRASSHOPPER_ACTION_APPROACH_PLAYER) || (this->action == EN_GRASSHOPPER_ACTION_ATTACK)) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        }
    }
}

void EnGrasshopper_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnGrasshopper* this = THIS;
    Vec3f sEffectOffsetFromTailTop = { 500.0f, 0.0f, 0.0f };
    Vec3f sZeroVec3f = { 0.0f, 0.0f, 0.0f };

    Matrix_Push();

    if ((this->type != EN_GRASSHOPPER_TYPE_WOODFALL_TEMPLE_FINAL_ROOM) &&
        (this->type != EN_GRASSHOPPER_TYPE_WOODFALL)) {
        if ((s8)(sLimbIndexToShadowBodyPartsIndex[limbIndex] >= 0)) {
            Matrix_MultVec3f(&sZeroVec3f, &this->shadowBodyPartsPos[sLimbIndexToShadowBodyPartsIndex[limbIndex]]);
        }
    }

    if (limbIndex == DRAGONFLY_LIMB_TAIL_TIP) {
        Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_MultVec3f(&gZeroVec3f, &this->tailTipPos);
        Matrix_MultVec3f(&sEffectOffsetFromTailTop, &this->effectBasePos);
    }

    Collider_UpdateSpheres(limbIndex, &this->collider);
    if ((limbIndex == DRAGONFLY_LIMB_ROOT) || (limbIndex == DRAGONFLY_LIMB_TAIL_SEGMENT_2) ||
        (limbIndex == DRAGONFLY_LIMB_TAIL_TIP) || (limbIndex == DRAGONFLY_LIMB_BACK_LEFT_UPPER_LEG) ||
        (limbIndex == DRAGONFLY_LIMB_BACK_RIGHT_UPPER_LEG) || (limbIndex == DRAGONFLY_LIMB_FRONT_LEFT_UPPER_LEG) ||
        (limbIndex == DRAGONFLY_LIMB_FRONT_LEFT_FOOT) || (limbIndex == DRAGONFLY_LIMB_FRONT_RIGHT_UPPER_LEG) ||
        (limbIndex == DRAGONFLY_LIMB_HEAD) ||
        //! @bug: These do not check for valid limbs. Limb index 24 is DRAGONFLY_LIMB_MAX, so it (and any index
        //! larger than it) is not tied to an actual limb.
        (limbIndex == 24) || (limbIndex == 25) ||
        // While checking for DRAGONFLY_LIMB_ROOT twice is not a bug by itself, it causes another bug below.
        (limbIndex == DRAGONFLY_LIMB_ROOT)) {
        //! @bug: This code only works properly if all 12 elements of bodyPartsPos are updated every frame, since
        //! otherwise bodyPartsPosIndex will be non-zero at the end of a frame. Despite the fact that there are 12
        //! checks in the above if-statement, only 9 of them are valid and non-duplicate, so only 9 elements of
        //! bodyPartsPos are updated on each frame. As a result, three elements in bodyPartsPos will either be (0, 0, 0)
        //! or be a value carried over from the previous frame.
        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartsPosIndex]);
        this->bodyPartsPosIndex++;
        if (this->bodyPartsPosIndex >= ARRAY_COUNT(this->bodyPartsPos)) {
            this->bodyPartsPosIndex = 0;
        }
    }

    Matrix_Pop();
}

// We need to pass in 14 into SubS_GenShadowTex for the bodyPartsNum, NOT the actual size of the
// parent body parts array. This is both necessary to match and to prevent extra dots from being
// drawn with the shadow.
#define SHADOW_BODY_PARTS_NUM 14

void EnGrasshopper_Draw(Actor* thisx, PlayState* play) {
    EnGrasshopper* this = THIS;
    s32 i;
    u8* shadowTex = GRAPH_ALLOC(play->state.gfxCtx, SUBS_SHADOW_TEX_SIZE);
    u8* shadowTexIter;

    func_8012C2DC(play->state.gfxCtx);
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, EnGrasshopper_PostLimbDraw,
                      &this->actor);
    if ((this->type != EN_GRASSHOPPER_TYPE_WOODFALL_TEMPLE_FINAL_ROOM) &&
        (this->type != EN_GRASSHOPPER_TYPE_WOODFALL)) {
        Matrix_RotateXS(0, MTXMODE_NEW);

        for (i = 0, shadowTexIter = shadowTex; i < SUBS_SHADOW_TEX_SIZE; i++) {
            *shadowTexIter++ = 0;
        }

        for (i = 0; i < 5; i++) {
            SubS_GenShadowTex(this->shadowBodyPartsPos, &this->actor.world.pos, shadowTex, i / 5.0f,
                              SHADOW_BODY_PARTS_NUM, sShadowSizes, sParentBodyParts);
            //! FAKE: Needed to fix some regs and stack
            //! https://decomp.me/scratch/4wJBW
            if ((shadowTex && shadowTex) && shadowTex) {}
        }

        SubS_DrawShadowTex(&this->actor, &play->state, shadowTex);
    }

    if (this->drawDmgEffTimer != 0) {
        f32 drawDmgEffAlpha = this->drawDmgEffTimer * 0.05f;

        if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX) ||
            (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) {
            this->drawDmgEffScale += 0.3f;
            if (this->drawDmgEffScale > 0.5f) {
                this->drawDmgEffScale = 0.5f;
            }

            Math_ApproachF(&this->drawDmgEffFrozenSteamScale, this->drawDmgEffScale, 0.1f, 0.04f);
        } else {
            this->drawDmgEffScale = 0.8f;
            this->drawDmgEffFrozenSteamScale = 0.8f;
        }

        Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                                this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, drawDmgEffAlpha,
                                this->drawDmgEffType);
    }

    EnGrasshopper_DrawEffects(this, play);
}

void EnGrasshopper_InitializeEffect(EnGrasshopper* this, Vec3f* pos) {
    EnGrasshopperEffect* effect = this->effects;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (!effect->isEnabled) {
            effect->isEnabled = true;
            effect->pos = *pos;
            effect->timer = 10;
            effect->velocity.x = randPlusMinusPoint5Scaled(20.0f);
            effect->velocity.y = randPlusMinusPoint5Scaled(20.0f);
            effect->velocity.z = randPlusMinusPoint5Scaled(20.0f);
            effect->yaw = randPlusMinusPoint5Scaled(30000.0f);
            return;
        }
    }
}

void EnGrasshopper_UpdateEffects(EnGrasshopper* this, PlayState* play) {
    EnGrasshopperEffect* effect = this->effects;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->isEnabled) {
            effect->pos.x = this->effectBasePos.x + effect->velocity.x;
            effect->pos.y = this->effectBasePos.y + effect->velocity.y;
            effect->pos.z = this->effectBasePos.z + effect->velocity.z;
            if (effect->timer != 0) {
                effect->timer--;
                effect->lightningIndex++;
                Math_ApproachF(&effect->scale.x, 0.1f, 0.1f, 0.05f);
                if (effect->lightningIndex >= 8) {
                    effect->lightningIndex = 0;
                }
            } else {
                Math_ApproachZeroF(&effect->scale.x, 0.1f, 0.1f);
                if (effect->scale.x < 0.2f) {
                    effect->isEnabled = 0;
                }
            }

            effect->scale.y = effect->scale.z = effect->scale.x;
        }
    }
}

static TexturePtr sLightningTextures[] = {
    gEffLightning1Tex, gEffLightning2Tex, gEffLightning3Tex, gEffLightning4Tex,
    gEffLightning5Tex, gEffLightning6Tex, gEffLightning7Tex, gEffLightning8Tex,
};

void EnGrasshopper_DrawEffects(EnGrasshopper* this, PlayState* play) {
    s32 pad[2];
    EnGrasshopperEffect* effect;
    s16 i;
    MtxF mfResult;
    MtxF mfTrans;
    MtxF mfScale;
    MtxF mfRot;
    MtxF mfTransBillboard;
    MtxF mfTransBillboardRot;
    Mtx* mtx;

    OPEN_DISPS(play->state.gfxCtx);

    effect = this->effects;
    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->isEnabled) {
            SkinMatrix_SetTranslate(&mfTrans, effect->pos.x, effect->pos.y, effect->pos.z);
            SkinMatrix_SetScale(&mfScale, effect->scale.x, effect->scale.y, effect->scale.z);
            SkinMatrix_SetRotateRPY(&mfRot, 0, 0, effect->yaw);
            SkinMatrix_MtxFMtxFMult(&mfTrans, &play->billboardMtxF, &mfTransBillboard);
            SkinMatrix_MtxFMtxFMult(&mfTransBillboard, &mfRot, &mfTransBillboardRot);
            SkinMatrix_MtxFMtxFMult(&mfTransBillboardRot, &mfScale, &mfResult);

            gSPMatrix(POLY_XLU_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            mtx = SkinMatrix_MtxFToNewMtx(play->state.gfxCtx, &mfResult);

            if (mtx != NULL) {
                gSPMatrix(POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                func_8012C9BC(play->state.gfxCtx);
                gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sLightningTextures[effect->lightningIndex]));
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
                gDPSetEnvColor(POLY_XLU_DISP++, 200, 255, 255, 255);
                gSPDisplayList(POLY_XLU_DISP++, Lib_SegmentedToVirtual(gEffLightningDL));
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
