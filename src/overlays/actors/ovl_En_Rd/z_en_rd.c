/*
 * File: z_en_rd.c
 * Overlay: ovl_En_Rd
 * Description: Redead/Gibdo that cannot talk to the player.
 *
 * A variety of different Redeads/Gibdos are represented by this actor;
 * one of the few things they all have in common is that none of them
 * can talk with the player, which separates them from Talk_Gibud and
 * Railgibud. Some of the different kinds of Redeads/Gibdos that this
 * actor controls are:
 * - Three different types of dancing Redeads. These are the only
 *   Redead/Gidbo variations that are actually used in the final game.
 * - A Redead frozen in a block of ice.
 * - An invisible Redead.
 * - A crying Redead.
 * - A Gidbo that rises out of a "coffin"; this is leftover from OoT.
 *
 * Another thing that separates this actor from Talk_Gibud and Railgibud
 * is that most Redead variations will "mourn" other fallen Redeads in
 * the same area by walking over to their corpse. Note that some Redeads,
 * depending on their params, will refuse to mourn under certain
 * circumstances, and all Gibdo variations will refuse to mourn as well.
 */

#include "z_en_rd.h"
#include "objects/object_rd/object_rd.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_400)

#define THIS ((EnRd*)thisx)

void EnRd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 EnRd_ShouldNotDance(GlobalContext* globalCtx);
void EnRd_SetupIdle(EnRd* this);
void EnRd_Idle(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupSquattingDance(EnRd* this);
void EnRd_SquattingDance(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupClappingDance(EnRd* this);
void EnRd_ClappingDance(EnRd* this, GlobalContext* globalCtx);
void EnRd_EndClappingOrSquattingDanceWhenPlayerIsClose(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupPirouette(EnRd* this);
void EnRd_Pirouette(EnRd* this, GlobalContext* globalCtx);
void EnRd_EndPirouetteWhenPlayerIsClose(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupRiseFromCoffin(EnRd* this);
void EnRd_RiseFromCoffin(EnRd* this, GlobalContext* globalCtx);
void EnRd_WalkToPlayer(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupWalkToHome(EnRd* this, GlobalContext* globalCtx);
void EnRd_WalkToHome(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupWalkToParent(EnRd* this);
void EnRd_WalkToParent(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupGrab(EnRd* this);
void EnRd_Grab(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupAttemptPlayerFreeze(EnRd* this);
void EnRd_AttemptPlayerFreeze(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupGrabFail(EnRd* this);
void EnRd_GrabFail(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupTurnAwayAndShakeHead(EnRd* this);
void EnRd_TurnAwayAndShakeHead(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupStandUp(EnRd* this);
void EnRd_StandUp(EnRd* this, GlobalContext* globalCtx);
void EnRd_SetupCrouch(EnRd* this);
void EnRd_Crouch(EnRd* this, GlobalContext* globalCtx);
void EnRd_Damage(EnRd* this, GlobalContext* globalCtx);
void EnRd_Dead(EnRd* this, GlobalContext* globalCtx);
void EnRd_Stunned(EnRd* this, GlobalContext* globalCtx);

typedef enum {
    /*  0 */ EN_RD_ACTION_IDLE,
    /*  1 */ EN_RD_ACTION_STUNNED,
    /*  2 */ EN_RD_ACTION_WALKING_TO_HOME,
    /*  3 */ EN_RD_ACTION_WALKING_TO_PARENT,
    /*  4 */ EN_RD_ACTION_WALKING_TO_PLAYER_OR_RELEASING_GRAB,
    /*  5 */ EN_RD_ACTION_STANDING_UP,
    /*  6 */ EN_RD_ACTION_CROUCHING,
    /*  7 */ EN_RD_ACTION_ATTEMPTING_PLAYER_STUN,
    /*  8 */ EN_RD_ACTION_FAILING_GRAB,
    /*  9 */ EN_RD_ACTION_TURNING_AWAY_AND_SHAKING_HEAD,
    /* 10 */ EN_RD_ACTION_GRABBING,
    /* 11 */ EN_RD_ACTION_DAMAGE,
    /* 12 */ EN_RD_ACTION_DEAD,
    /* 13 */ EN_RD_ACTION_RISING_FROM_COFFIN,
    /* 14 */ EN_RD_ACTION_SQUATTING_DANCE,
    /* 15 */ EN_RD_ACTION_CLAPPING_DANCE,
    /* 16 */ EN_RD_ACTION_PIROUETTE
} EnRdAction;

typedef enum {
    /* 0 */ EN_RD_GRAB_START,
    /* 1 */ EN_RD_GRAB_INITIAL_DAMAGE,
    /* 2 */ EN_RD_GRAB_ATTACK,
    /* 3 */ EN_RD_GRAB_RELEASE,
    /* 4 */ EN_RD_GRAB_END,
} EnRdGrabState;

const ActorInit En_Rd_InitVars = {
    ACTOR_EN_RD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRd),
    (ActorFunc)EnRd_Init,
    (ActorFunc)EnRd_Destroy,
    (ActorFunc)EnRd_Update,
    (ActorFunc)EnRd_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7EFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

typedef enum {
    /* 0x0 */ EN_RD_DMGEFF_NONE,              // Does not interact with the Gibdo/Redead at all
    /* 0x1 */ EN_RD_DMGEFF_STUN,              // Stuns without applying any effect
    /* 0x2 */ EN_RD_DMGEFF_FIRE_ARROW,        // Damages and applies a fire effect
    /* 0x4 */ EN_RD_DMGEFF_LIGHT_ARROW = 0x4, // Damages and applies a light effect
    /* 0x6 */ EN_RD_DMGEFF_UNUSED_6 = 0x6,    // Referenced in EnRd_Update, but no attack uses this damage effect.
                                              // Likely to have originally been used for Ice Arrows like OoT.
    /* 0xC */ EN_RD_DMGEFF_ZORA_MAGIC = 0xC,  // Stuns and applies an electric effect
    /* 0xD */ EN_RD_DMGEFF_RECOIL,            // Deals no damage, but displays hit mark and recoil animation
    /* 0xE */ EN_RD_DMGEFF_LIGHT_RAY,         // Instantly kills on contact
    /* 0xF */ EN_RD_DMGEFF_DAMAGE,            // Deals damage and plays the damage animation
} EnRdDamageEffect;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* Deku Stick     */ DMG_ENTRY(2, EN_RD_DMGEFF_DAMAGE),
    /* Horse trample  */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* Explosives     */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Zora boomerang */ DMG_ENTRY(0, EN_RD_DMGEFF_RECOIL),
    /* Normal arrow   */ DMG_ENTRY(0, EN_RD_DMGEFF_RECOIL),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, EN_RD_DMGEFF_DAMAGE),
    /* Hookshot       */ DMG_ENTRY(0, EN_RD_DMGEFF_RECOIL),
    /* Goron punch    */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Sword          */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Goron pound    */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Fire arrow     */ DMG_ENTRY(1, EN_RD_DMGEFF_FIRE_ARROW),
    /* Ice arrow      */ DMG_ENTRY(0, EN_RD_DMGEFF_RECOIL),
    /* Light arrow    */ DMG_ENTRY(2, EN_RD_DMGEFF_LIGHT_ARROW),
    /* Goron spikes   */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Deku spin      */ DMG_ENTRY(0, EN_RD_DMGEFF_STUN),
    /* Deku bubble    */ DMG_ENTRY(0, EN_RD_DMGEFF_RECOIL),
    /* Deku launch    */ DMG_ENTRY(2, EN_RD_DMGEFF_DAMAGE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* Zora barrier   */ DMG_ENTRY(0, EN_RD_DMGEFF_ZORA_MAGIC),
    /* Normal shield  */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, EN_RD_DMGEFF_LIGHT_RAY),
    /* Thrown object  */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Zora punch     */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Spin attack    */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
    /* Sword beam     */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, EN_RD_DMGEFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(1, EN_RD_DMGEFF_DAMAGE),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

void EnRd_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRd* this = THIS;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.targetMode = 0;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->upperBodyYRotation = this->headYRotation = 0;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;
    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.colChkInfo.health = 8;
    this->alpha = 255;
    this->unk_3F1 = -1;
    this->flags = EN_RD_GET_FLAGS(thisx);

    if (EN_RD_GET_80(&this->actor)) {
        this->actor.params |= 0xFF00;
    } else {
        this->actor.params &= 0xFF;
    }

    if (EN_RD_GET_TYPE(&this->actor) > EN_RD_TYPE_GIBDO) {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gRedeadSkel, &gGibdoRedeadIdleAnim, this->jointTable,
                           this->morphTable, REDEAD_LIMB_MAX);
    } else {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGibdoSkel, &gGibdoRedeadIdleAnim, this->jointTable,
                           this->morphTable, REDEAD_LIMB_MAX);
    }

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    if (EN_RD_GET_TYPE(&this->actor) >= EN_RD_TYPE_GIBDO) {
        switch (EN_RD_GET_TYPE(&this->actor)) {
            case EN_RD_TYPE_SQUATTING_DANCE:
                if (!EnRd_ShouldNotDance(globalCtx)) {
                    EnRd_SetupSquattingDance(this);
                } else {
                    this->actor.hintId = 0x2A;
                    EnRd_SetupIdle(this);
                }
                this->setupDanceFunc = EnRd_SetupSquattingDance;
                break;

            case EN_RD_TYPE_CLAPPING_DANCE:
                if (!EnRd_ShouldNotDance(globalCtx)) {
                    EnRd_SetupClappingDance(this);
                } else {
                    this->actor.hintId = 0x2A;
                    EnRd_SetupIdle(this);
                }
                this->setupDanceFunc = EnRd_SetupClappingDance;
                break;

            case EN_RD_TYPE_PIROUETTE:
                if (!EnRd_ShouldNotDance(globalCtx)) {
                    EnRd_SetupPirouette(this);
                } else {
                    this->actor.hintId = 0x2A;
                    EnRd_SetupIdle(this);
                }
                this->setupDanceFunc = EnRd_SetupPirouette;
                break;

            default:
                if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_GIBDO) {
                    this->actor.hintId = 0x2D;
                } else {
                    this->actor.hintId = 0x2A;
                }
                EnRd_SetupIdle(this);
                this->setupDanceFunc = EnRd_SetupIdle;
                break;
        }
    } else {
        EnRd_SetupRiseFromCoffin(this);
    }

    SkelAnime_Update(&this->skelAnime);

    if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_INVISIBLE) {
        this->actor.flags |= ACTOR_FLAG_80;
    }

    if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_FROZEN) {
        s32 requiredScopeTemp;

        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                           this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                           this->actor.world.rot.y, this->actor.world.rot.z, 0xFF4B);
    }
}

void EnRd_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRd* this = THIS;

    if (gSaveContext.sunsSongState != SUNSSONG_INACTIVE) {
        gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
    }
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

/**
 * This function does two things depending on whether setParent is true or false.
 * - If setParent is true, this function sets thisx to be the parent for all Redeads
 *   in the area that are capable of mourning. This is used right when thisx first
 *   dies to make the other Redeads mourn it.
 * - If setParent is false, this function nulls out the parent for all Redeads in the
 *   are whose parents is thisx. This is used when thisx is fading away to make the
 *   other Redeads stop mourning over it.
 */
void EnRd_UpdateParentForOtherRedeads(GlobalContext* globalCtx, Actor* thisx, s32 setParent) {
    Actor* enemyIterator = globalCtx->actorCtx.actorLists[ACTORCAT_ENEMY].first;

    while (enemyIterator != NULL) {
        if ((enemyIterator->id != ACTOR_EN_RD) || (enemyIterator == thisx) ||
            (EN_RD_GET_TYPE(enemyIterator) < EN_RD_TYPE_DOES_NOT_MOURN_IF_WALKING)) {
            enemyIterator = enemyIterator->next;
            continue;
        }

        if (setParent) {
            enemyIterator->parent = thisx;
        } else if (thisx == enemyIterator->parent) {
            enemyIterator->parent = NULL;
        }

        enemyIterator = enemyIterator->next;
    }
}

/**
 * Returns true if the various dancing Redead types *should not* be dancing
 * and returns false if they *should* be dancing. The non-dancing Redeads
 * do not call this function in the final game and thus don't care about
 * what mask the player has equipped.
 */
s32 EnRd_ShouldNotDance(GlobalContext* globalCtx) {
    if ((Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO) || (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAIN) ||
        (Player_GetMask(globalCtx) == PLAYER_MASK_GARO)) {
        return false;
    }

    return true;
}

/**
 * If the Redead/Gibdo is a dancing Redead; if it isn't already dancing; if it isn't stunned,
 * taking damage, dead, or currently grabbing the player; and if the player is wearing the
 * appropriate mask, this function will make the Redead start dancing.
 */
void EnRd_SetupDanceIfConditionsMet(EnRd* this, GlobalContext* globalCtx) {
    if ((EN_RD_GET_TYPE(&this->actor) >= EN_RD_TYPE_SQUATTING_DANCE) && (this->actionFunc != EnRd_SquattingDance) &&
        (this->actionFunc != EnRd_ClappingDance) && (this->actionFunc != EnRd_Pirouette) &&
        (this->actionFunc != EnRd_Stunned) && (this->actionFunc != EnRd_Grab) && (this->actionFunc != EnRd_Damage) &&
        (this->actionFunc != EnRd_Dead)) {
        if (!EnRd_ShouldNotDance(globalCtx)) {
            this->setupDanceFunc(this);
        }
    }
}

void EnRd_SetupIdle(EnRd* this) {
    if (EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) {
        Animation_MorphToLoop(&this->skelAnime, &gGibdoRedeadIdleAnim, -6.0f);
    } else {
        Animation_PlayLoop(&this->skelAnime, &gGibdoRedeadSobbingAnim);
    }

    this->action = EN_RD_ACTION_IDLE;
    this->animationJudderTimer = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnRd_Idle;
}

void EnRd_Idle(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->headYRotation, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 100, 0);

    if ((EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_CRYING) && Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (Rand_ZeroOne() >= 0.5f) {
            Animation_PlayLoop(&this->skelAnime, &gGibdoRedeadSobbingAnim);
        } else {
            Animation_PlayLoop(&this->skelAnime, &gGibdoRedeadWipingTearsAnim);
        }
    } else {
        this->animationJudderTimer--;
        if (this->animationJudderTimer == 0) {
            // This resets the idle animation back to its first frame, making the
            // Redead/Gibdo appear to "judder" in place.
            this->animationJudderTimer = (Rand_ZeroOne() * 10.0f) + 10.0f;
            this->skelAnime.curFrame = 0.0f;
        }
    }

    if (this->actor.parent != NULL) {
        if (!this->isMourning) {
            if (EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) {
                EnRd_SetupWalkToParent(this);
            } else {
                EnRd_SetupStandUp(this);
            }
        }
    } else {
        if (this->isMourning) {
            if (EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) {
                EnRd_SetupAttemptPlayerFreeze(this);
            } else {
                EnRd_SetupStandUp(this);
            }
        }

        this->isMourning = false;
        if ((this->actor.xzDistToPlayer <= 150.0f) && func_800B715C(globalCtx)) {
            if ((EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) && (!this->isMourning)) {
                EnRd_SetupAttemptPlayerFreeze(this);
            } else {
                EnRd_SetupStandUp(this);
            }
        }
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnRd_SetupSquattingDance(EnRd* this) {
    Animation_MorphToLoop(&this->skelAnime, &gGibdoRedeadSquattingDanceAnim, -6.0f);
    this->action = EN_RD_ACTION_SQUATTING_DANCE;
    this->animationJudderTimer = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->danceEndTimer = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnRd_SquattingDance;
}

void EnRd_SquattingDance(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->headYRotation, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 100, 0);

    if (this->isMourning) {
        EnRd_SetupAttemptPlayerFreeze(this);
    }

    this->isMourning = false;
    if ((this->actor.xzDistToPlayer <= 150.0f) && EnRd_ShouldNotDance(globalCtx) && func_800B715C(globalCtx)) {
        if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_GIBDO) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        Animation_Change(&this->skelAnime, &gGibdoRedeadLookBackAnim, 0.0f, 0.0f, 19.0f, 2, -10.0f);
        this->actionFunc = EnRd_EndClappingOrSquattingDanceWhenPlayerIsClose;
    }

    if (EnRd_ShouldNotDance(globalCtx)) {
        if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_GIBDO) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        EnRd_SetupIdle(this);
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnRd_SetupClappingDance(EnRd* this) {
    Animation_MorphToLoop(&this->skelAnime, &gGibdoRedeadClappingDanceAnim, -6.0f);
    this->action = EN_RD_ACTION_CLAPPING_DANCE;
    this->animationJudderTimer = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->danceEndTimer = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnRd_ClappingDance;
}

void EnRd_ClappingDance(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->headYRotation, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 100, 0);

    if (this->isMourning) {
        EnRd_SetupAttemptPlayerFreeze(this);
    }

    this->isMourning = false;
    if ((this->actor.xzDistToPlayer <= 150.0f) && EnRd_ShouldNotDance(globalCtx) && func_800B715C(globalCtx)) {
        if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_GIBDO) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        Animation_Change(&this->skelAnime, &gGibdoRedeadLookBackAnim, 0.0f, 0.0f, 19.0f, 2, -10.0f);
        this->actionFunc = EnRd_EndClappingOrSquattingDanceWhenPlayerIsClose;
    }

    if (EnRd_ShouldNotDance(globalCtx)) {
        if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_GIBDO) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        EnRd_SetupIdle(this);
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnRd_EndClappingOrSquattingDanceWhenPlayerIsClose(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }

    this->danceEndTimer++;
    if (this->danceEndTimer > 10) {
        if ((EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) && (!this->isMourning)) {
            EnRd_SetupAttemptPlayerFreeze(this);
        } else {
            EnRd_SetupStandUp(this);
        }
        this->danceEndTimer = 0;
    }
}

void EnRd_SetupPirouette(EnRd* this) {
    Animation_MorphToLoop(&this->skelAnime, &gGibdoRedeadPirouetteAnim, -6.0f);
    this->action = EN_RD_ACTION_PIROUETTE;
    this->animationJudderTimer = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->pirouetteRotationalVelocity = 0x1112;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = EnRd_Pirouette;
}

void EnRd_Pirouette(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->headYRotation, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 100, 0);

    if (this->isMourning) {
        EnRd_SetupAttemptPlayerFreeze(this);
    }

    this->isMourning = false;
    if ((this->actor.xzDistToPlayer <= 150.0f) && EnRd_ShouldNotDance(globalCtx) && func_800B715C(globalCtx)) {
        if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_GIBDO) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        this->actionFunc = EnRd_EndPirouetteWhenPlayerIsClose;
    }

    if (EnRd_ShouldNotDance(globalCtx)) {
        if (EN_RD_GET_TYPE(&this->actor) == EN_RD_TYPE_GIBDO) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        EnRd_SetupIdle(this);
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->pirouetteRotationalVelocity = 0x1112;
    } else if (Animation_OnFrame(&this->skelAnime, 15.0f)) {
        this->pirouetteRotationalVelocity = 0x199A;
    }

    this->actor.world.rot.y -= this->pirouetteRotationalVelocity;
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void EnRd_EndPirouetteWhenPlayerIsClose(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }

    this->actor.world.rot.y -= this->pirouetteRotationalVelocity;
    this->actor.shape.rot.y = this->actor.world.rot.y;

    this->pirouetteRotationalVelocity -= 0x64;
    if ((this->pirouetteRotationalVelocity < 0x834) && (this->pirouetteRotationalVelocity >= 0x7D0)) {
        Animation_Change(&this->skelAnime, &gGibdoRedeadLookBackAnim, 0.0f, 0.0f, 19.0f, 2, -10.0f);
    } else if (this->pirouetteRotationalVelocity < 0x3E8) {
        if ((EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) && (!this->isMourning)) {
            EnRd_SetupAttemptPlayerFreeze(this);
        } else {
            EnRd_SetupStandUp(this);
        }
    }
}

void EnRd_SetupRiseFromCoffin(EnRd* this) {
    Animation_Change(&this->skelAnime, &gGibdoRedeadIdleAnim, 0.0f, 0.0f, Animation_GetLastFrame(&gGibdoRedeadIdleAnim),
                     0, -6.0f);
    this->action = EN_RD_ACTION_RISING_FROM_COFFIN;
    this->coffinRiseForwardAccelTimer = 6;
    this->actor.shape.rot.x = -0x4000;
    this->actor.gravity = 0.0f;
    this->actor.shape.yOffset = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = EnRd_RiseFromCoffin;
}

void EnRd_RiseFromCoffin(EnRd* this, GlobalContext* globalCtx) {
    if (this->actor.shape.rot.x != -0x4000) {
        Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 1, 0x7D0, 0);
        if (Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.3f, 2.0f, 0.3f) == 0.0f) {
            this->actor.gravity = -3.5f;
            EnRd_SetupIdle(this);
        }
    } else {
        if (this->actor.world.pos.y == this->actor.home.pos.y) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
        }

        if (Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 50.0f, 0.3f, 2.0f, 0.3f) == 0.0f) {
            if (this->coffinRiseForwardAccelTimer != 0) {
                this->coffinRiseForwardAccelTimer--;
                Math_SmoothStepToF(&this->actor.speedXZ, 6.0f, 0.3f, 1.0f, 0.3f);
            } else if (Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 0.3f, 1.0f, 0.3f) == 0.0f) {
                Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 1, 0x7D0, 0);
            }
        }
    }
}

void EnRd_SetupWalkToPlayer(EnRd* this, GlobalContext* globalCtx) {
    f32 frameCount = Animation_GetLastFrame(&gGibdoRedeadWalkAnim);

    Animation_Change(&this->skelAnime, &gGibdoRedeadWalkAnim, 1.0f, 4.0f, frameCount, 1, -4.0f);
    this->actor.speedXZ = 0.4f;
    this->action = EN_RD_ACTION_WALKING_TO_PLAYER_OR_RELEASING_GRAB;
    this->actionFunc = EnRd_WalkToPlayer;
}

void EnRd_WalkToPlayer(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s16 yaw =
        ((this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->headYRotation) - this->upperBodyYRotation;

    this->skelAnime.playSpeed = this->actor.speedXZ;
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 250, 0);
    Math_SmoothStepToS(&this->headYRotation, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 100, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);

    if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 150.0f) {
        EnRd_SetupWalkToHome(this, globalCtx);
    }

    if ((ABS_ALT(yaw) < 0x1554) && (Actor_DistanceBetweenActors(&this->actor, &player->actor) <= 150.0f)) {
        if (!(player->stateFlags1 & (0x200000 | 0x80000 | 0x40000 | 0x4000 | 0x2000 | 0x80)) &&
            !(player->stateFlags2 & (0x4000 | 0x80))) {
            if (this->playerStunWaitTimer == 0) {
                if (!(this->flags & EN_RD_FLAG_CANNOT_FREEZE_PLAYER)) {
                    player->actor.freezeTimer = 40;
                    func_80123E90(globalCtx, &this->actor);
                    GET_PLAYER(globalCtx)->unk_A78 = &this->actor;
                    func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
                }
                this->playerStunWaitTimer = 60;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_AIM);
            }
        } else {
            EnRd_SetupWalkToHome(this, globalCtx);
        }
    }

    if (this->grabWaitTimer != 0) {
        this->grabWaitTimer--;
    }

    if (!this->grabWaitTimer && (Actor_DistanceBetweenActors(&this->actor, &player->actor) <= 45.0f) &&
        Actor_IsFacingPlayer(&this->actor, 0x38E3)) {
        player->actor.freezeTimer = 0;
        if ((player->transformation == PLAYER_FORM_GORON) || (player->transformation == PLAYER_FORM_DEKU)) {
            if (Actor_DistanceToPoint(&this->actor, &this->actor.home.pos) < 150.0f) {
                // If the Gibdo/Redead tries to grab Goron or Deku Link, it will fail to
                // do so. It will appear to take damage and shake its head side-to-side.
                EnRd_SetupGrabFail(this);
            } else {
                EnRd_SetupWalkToHome(this, globalCtx);
            }
        } else if (globalCtx->grabPlayer(globalCtx, player)) {
            this->actor.flags &= ~ACTOR_FLAG_1;
            EnRd_SetupGrab(this);
        }
    } else if (EN_RD_GET_TYPE(&this->actor) > EN_RD_TYPE_DOES_NOT_MOURN_IF_WALKING) {
        if (this->actor.parent != NULL) {
            EnRd_SetupWalkToParent(this);
        } else {
            this->isMourning = false;
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnRd_SetupWalkToHome(EnRd* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &gGibdoRedeadWalkAnim, 0.5f, 0.0f, Animation_GetLastFrame(&gGibdoRedeadWalkAnim),
                     1, -4.0f);
    this->action = EN_RD_ACTION_WALKING_TO_HOME;
    this->actionFunc = EnRd_WalkToHome;
}

void EnRd_WalkToHome(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s16 sp36 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);

    if (Actor_DistanceToPoint(&this->actor, &this->actor.home.pos) >= 5.0f) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp36, 1, 450, 0);
    } else {
        this->actor.speedXZ = 0.0f;
        if (!Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 450, 0)) {
            if (EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) {
                EnRd_SetupIdle(this);
            } else {
                EnRd_SetupCrouch(this);
            }
        }
    }

    Math_SmoothStepToS(&this->headYRotation, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 100, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);

    if (!(player->stateFlags1 & (0x200000 | 0x80000 | 0x40000 | 0x4000 | 0x2000 | 0x80)) &&
        !(player->stateFlags2 & (0x4000 | 0x80)) && (player->transformation != PLAYER_FORM_GORON) &&
        (player->transformation != PLAYER_FORM_DEKU) &&
        (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) < 150.0f)) {
        this->actor.targetMode = 0;
        EnRd_SetupWalkToPlayer(this, globalCtx);
    } else if (EN_RD_GET_TYPE(&this->actor) > EN_RD_TYPE_DOES_NOT_MOURN_IF_WALKING) {
        if (this->actor.parent != NULL) {
            EnRd_SetupWalkToParent(this);
        } else {
            this->isMourning = false;
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnRd_SetupWalkToParent(EnRd* this) {
    f32 frameCount = Animation_GetLastFrame(&gGibdoRedeadWalkAnim);

    Animation_Change(&this->skelAnime, &gGibdoRedeadWalkAnim, 0.5f, 0.0f, frameCount, 1, -4.0f);
    this->action = EN_RD_ACTION_WALKING_TO_PARENT;
    this->isMourning = true;
    this->actionFunc = EnRd_WalkToParent;
}

/**
 * When a Redead or Gibdo dies, it sets itself to be the parent for all other
 * Redeads in the area that are capable of mourning. This function will make
 * these Redeads walk over to the corpse and stand near until it begins to
 * fade away.
 */
void EnRd_WalkToParent(EnRd* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 yaw;
    Vec3f parentPos;

    if (this->actor.parent != NULL) {
        parentPos = this->actor.parent->world.pos;
        yaw = Actor_YawToPoint(&this->actor, &parentPos);

        Math_SmoothStepToS(&this->actor.shape.rot.y, yaw, 1, 250, 0);
        if (Actor_DistanceToPoint(&this->actor, &parentPos) >= 45.0f) {
            this->actor.speedXZ = 0.4f;
        } else {
            this->actor.speedXZ = 0.0f;
            if (EN_RD_GET_TYPE(&this->actor) != EN_RD_TYPE_CRYING) {
                EnRd_SetupIdle(this);
            } else {
                EnRd_SetupCrouch(this);
            }
        }
        Math_SmoothStepToS(&this->headYRotation, 0, 1, 100, 0);
        Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 100, 0);
    } else {
        EnRd_SetupWalkToPlayer(this, globalCtx);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void EnRd_SetupGrab(EnRd* this) {
    Animation_PlayOnce(&this->skelAnime, &gGibdoRedeadGrabStartAnim);
    this->animationJudderTimer = 0;
    this->grabState = 0;
    this->grabDamageTimer = 200;
    this->action = EN_RD_ACTION_GRABBING;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = EnRd_Grab;
}

void EnRd_Grab(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->grabState++;
    }

    switch (this->grabState) {
        case EN_RD_GRAB_INITIAL_DAMAGE:
            Animation_PlayLoop(&this->skelAnime, &gGibdoRedeadGrabAttackAnim);
            this->grabState++;
            globalCtx->damagePlayer(globalCtx, -8);
            func_8013ECE0(this->actor.xzDistToPlayer, 255, 1, 12);
            this->grabDamageTimer = 20;

        case EN_RD_GRAB_START:
            Math_SmoothStepToS(&this->headYRotation, 0, 1, 1500, 0);
            Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 1500, 0);

        case EN_RD_GRAB_ATTACK:
            if (!(player->stateFlags2 & 0x80) || (player->unk_B62 != 0)) {
                if ((player->unk_B62 != 0) && (player->stateFlags2 & 0x80)) {
                    player->stateFlags2 &= ~0x80;
                    player->unk_AE8 = 100;
                }
                Animation_Change(&this->skelAnime, &gGibdoRedeadGrabEndAnim, 0.5f, 0.0f,
                                 Animation_GetLastFrame(&gGibdoRedeadGrabEndAnim), 3, 0.0f);
                this->grabState++;
                this->action = EN_RD_ACTION_WALKING_TO_PLAYER_OR_RELEASING_GRAB;
                break;
            }

            switch (player->transformation) {
                case PLAYER_FORM_FIERCE_DEITY:
                case PLAYER_FORM_GORON:
                case PLAYER_FORM_ZORA:
                case PLAYER_FORM_DEKU:
                    break;

                case PLAYER_FORM_HUMAN:
                    Math_SmoothStepToF(&this->actor.shape.yOffset, -1500.0f, 1.0f, 150.0f, 0.0f);
                    break;
            }

            Math_SmoothStepToF(&this->actor.world.pos.x,
                               (Math_SinS(player->actor.shape.rot.y) * -25.0f) + player->actor.world.pos.x, 1.0f, 10.0f,
                               0.0f);
            Math_SmoothStepToF(&this->actor.world.pos.y, player->actor.world.pos.y, 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->actor.world.pos.z,
                               (Math_CosS(player->actor.shape.rot.y) * -25.0f) + player->actor.world.pos.z, 1.0f, 10.0f,
                               0.0f);
            Math_SmoothStepToS(&this->actor.shape.rot.y, player->actor.shape.rot.y, 1, 6000, 0);

            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_ATTACK);
            }

            this->grabDamageTimer--;
            if (this->grabDamageTimer == 0) {
                globalCtx->damagePlayer(globalCtx, -8);
                func_8013ECE0(this->actor.xzDistToPlayer, 240, 1, 12);
                this->grabDamageTimer = 20;
                func_800B8E58(player, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
            }
            break;

        case EN_RD_GRAB_RELEASE:
            if (player->transformation != PLAYER_FORM_FIERCE_DEITY) {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            break;

        case EN_RD_GRAB_END:
            if (player->transformation != PLAYER_FORM_FIERCE_DEITY) {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            this->actor.targetMode = 0;
            this->actor.flags |= ACTOR_FLAG_1;
            this->playerStunWaitTimer = 10;
            this->grabWaitTimer = 15;
            EnRd_SetupWalkToPlayer(this, globalCtx);
            break;
    }
}

void EnRd_SetupAttemptPlayerFreeze(EnRd* this) {
    Animation_Change(&this->skelAnime, &gGibdoRedeadLookBackAnim, 0.0f, 0.0f,
                     Animation_GetLastFrame(&gGibdoRedeadLookBackAnim), 2, 0.0f);
    this->action = EN_RD_ACTION_ATTEMPTING_PLAYER_STUN;
    this->actionFunc = EnRd_AttemptPlayerFreeze;
}

void EnRd_AttemptPlayerFreeze(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 yaw =
        ((this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->headYRotation) - this->upperBodyYRotation;

    if (ABS_ALT(yaw) < 0x2008) {
        if (!(this->flags & EN_RD_FLAG_CANNOT_FREEZE_PLAYER)) {
            player->actor.freezeTimer = 60;
            func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
            func_80123E90(globalCtx, &this->actor);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_AIM);
        EnRd_SetupWalkToPlayer(this, globalCtx);
    }
}

void EnRd_SetupGrabFail(EnRd* this) {
    this->action = EN_RD_ACTION_FAILING_GRAB;
    Animation_MorphToPlayOnce(&this->skelAnime, &gGibdoRedeadDamageAnim, -6.0f);
    this->actor.speedXZ = -2.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->action = EN_RD_ACTION_FAILING_GRAB;
    this->actionFunc = EnRd_GrabFail;
}

void EnRd_GrabFail(EnRd* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->headYRotation, 0, 1, 300, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 300, 0);
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        EnRd_SetupTurnAwayAndShakeHead(this);
    }
}

void EnRd_SetupTurnAwayAndShakeHead(EnRd* this) {
    f32 frameCount = Animation_GetLastFrame(&gGibdoRedeadWalkAnim);

    Animation_Change(&this->skelAnime, &gGibdoRedeadWalkAnim, 0.5f, 0.0f, frameCount, 1, -4.0f);
    this->action = EN_RD_ACTION_TURNING_AWAY_AND_SHAKING_HEAD;
    this->headShakeTimer = 0;
    this->actionFunc = EnRd_TurnAwayAndShakeHead;
}

void EnRd_TurnAwayAndShakeHead(EnRd* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 5, 3500, 200);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->headShakeTimer > 60) {
        EnRd_SetupWalkToHome(this, globalCtx);
        this->headShakeTimer = 0;
    } else {
        this->headYRotation = Math_SinS(this->headShakeTimer * 4000) * (0x256F * ((60 - this->headShakeTimer) / 60.0f));
        SkelAnime_Update(&this->skelAnime);
        this->headShakeTimer++;
    }
}

void EnRd_SetupStandUp(EnRd* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gGibdoRedeadStandUpAnim, -4.0f);
    this->action = EN_RD_ACTION_STANDING_UP;
    this->actionFunc = EnRd_StandUp;
}

void EnRd_StandUp(EnRd* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.parent != NULL) {
            EnRd_SetupWalkToParent(this);
        } else {
            EnRd_SetupAttemptPlayerFreeze(this);
        }
    }
}

void EnRd_SetupCrouch(EnRd* this) {
    Animation_Change(&this->skelAnime, &gGibdoRedeadStandUpAnim, -1.0f,
                     Animation_GetLastFrame(&gGibdoRedeadStandUpAnim), 0.0f, 2, -4.0f);
    this->action = EN_RD_ACTION_CROUCHING;
    this->actionFunc = EnRd_Crouch;
}

void EnRd_Crouch(EnRd* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        EnRd_SetupIdle(this);
    }
}

void EnRd_SetupDamage(EnRd* this) {
    this->actor.shape.yOffset = 0.0f;
    Animation_MorphToPlayOnce(&this->skelAnime, &gGibdoRedeadDamageAnim, -6.0f);
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = -2.0f;
    }

    this->actor.flags |= ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->action = EN_RD_ACTION_DAMAGE;
    this->actionFunc = EnRd_Damage;
}

void EnRd_Damage(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->headYRotation, 0, 1, 300, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 300, 0);

    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.parent != NULL) {
            EnRd_SetupWalkToParent(this);
        } else if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 150.0f) {
            EnRd_SetupWalkToHome(this, globalCtx);
        } else {
            EnRd_SetupWalkToPlayer(this, globalCtx);
        }
        this->unk_3F1 = -1;
    }
}

void EnRd_SetupDead(EnRd* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gGibdoRedeadDeathAnim, -1.0f);
    this->action = EN_RD_ACTION_DEAD;
    this->deathTimer = 300;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_REDEAD_DEAD);
    this->actionFunc = EnRd_Dead;
}

void EnRd_Dead(EnRd* this, GlobalContext* globalCtx) {
    if (this->actor.category != ACTORCAT_PROP) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_PROP);
    }

    Math_SmoothStepToS(&this->headYRotation, 0, 1, 2000, 0);
    Math_SmoothStepToS(&this->upperBodyYRotation, 0, 1, 2000, 0);

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->deathTimer == 0) {
            if (!Flags_GetSwitch(globalCtx, EN_RD_GET_SWITCH_FLAG(this))) {
                Flags_SetSwitch(globalCtx, EN_RD_GET_SWITCH_FLAG(this));
            }

            if (this->alpha != 0) {
                if (this->alpha == 180) {
                    EnRd_UpdateParentForOtherRedeads(globalCtx, &this->actor, false);
                }
                this->actor.scale.y -= (75.0f / 1000000.0f);
                this->alpha -= 5;
            } else {
                Actor_MarkForDeath(&this->actor);
            }
        } else {
            this->deathTimer--;
        }
    } else if (Animation_OnFrame(&this->skelAnime, 33.0f) || Animation_OnFrame(&this->skelAnime, 40.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GERUDOFT_DOWN);
    }
}

void EnRd_SetupStunned(EnRd* this) {
    this->action = EN_RD_ACTION_STUNNED;
    this->stunTimer = 10;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (gSaveContext.sunsSongState != SUNSSONG_INACTIVE) {
        this->stunnedBySunsSong = true;
        this->sunsSongStunTimer = 600;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_LIGHT_ARROW_HIT);
        Actor_SetColorFilter(&this->actor, 0x8000, 0x80C8, 0, 255);
    } else if (this->damageEffect == EN_RD_DMGEFF_STUN) {
        Actor_SetColorFilter(&this->actor, 0, 0xC8, 0, 40);
    } else if (this->damageEffect == EN_RD_DMGEFF_ZORA_MAGIC) {
        Actor_SetColorFilter(&this->actor, 0, 0xC8, 0, 40);
    }
    this->actionFunc = EnRd_Stunned;
}

void EnRd_Stunned(EnRd* this, GlobalContext* globalCtx) {
    if (this->stunTimer > 0) {
        this->stunTimer--;
    }

    if (this->stunnedBySunsSong) {
        if (this->sunsSongStunTimer != 0) {
            this->sunsSongStunTimer--;
            if (this->sunsSongStunTimer >= 255) {
                Actor_SetColorFilter(&this->actor, 0x8000, 0x80C8, 0, 255);
            }

            if (this->sunsSongStunTimer == 0) {
                this->stunnedBySunsSong = false;
                gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
            }
        }
    }

    if (this->actor.colorFilterTimer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            EnRd_UpdateParentForOtherRedeads(globalCtx, &this->actor, true);
            EnRd_SetupDead(this);
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x90);
        } else {
            EnRd_SetupDamage(this);
        }
    }
}

void EnRd_TurnTowardsPlayer(EnRd* this, GlobalContext* globalCtx) {
    s16 headAngle = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->upperBodyYRotation;
    s16 upperBodyAngle = CLAMP(headAngle, -500, 500);

    headAngle -= this->headYRotation;
    headAngle = CLAMP(headAngle, -500, 500);

    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) >= 0) {
        this->upperBodyYRotation += ABS_ALT(upperBodyAngle);
        this->headYRotation += ABS_ALT(headAngle);
    } else {
        this->upperBodyYRotation -= ABS_ALT(upperBodyAngle);
        this->headYRotation -= ABS_ALT(headAngle);
    }

    this->upperBodyYRotation = CLAMP(this->upperBodyYRotation, -0x495F, 0x495F);
    this->headYRotation = CLAMP(this->headYRotation, -0x256F, 0x256F);
}

void EnRd_UpdateDamage(EnRd* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if ((gSaveContext.sunsSongState != SUNSSONG_INACTIVE) && (this->actor.shape.rot.x == 0) &&
        (!this->stunnedBySunsSong) && (this->action != EN_RD_ACTION_DAMAGE) && (this->action != EN_RD_ACTION_DEAD) &&
        (this->action != EN_RD_ACTION_STUNNED)) {
        EnRd_SetupStunned(this);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        this->damageEffect = this->actor.colChkInfo.damageEffect;

        if (this->action == EN_RD_ACTION_RISING_FROM_COFFIN) {
            return;
        }

        Actor_SetDropFlag(&this->actor, &this->collider.info);

        if (player->unk_ADC != 0) {
            this->unk_3F1 = player->unk_ADD;
        }

        switch (this->damageEffect) {
            case EN_RD_DMGEFF_ZORA_MAGIC:
                if ((this->actionFunc != EnRd_Grab) && ((this->actionFunc != EnRd_Stunned) || (this->stunTimer == 0))) {
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_SMALL;
                    this->drawDmgEffAlpha = 1.0f;
                    EnRd_SetupStunned(this);
                }
                return;

            case EN_RD_DMGEFF_STUN:
                EnRd_SetupStunned(this);
                return;

            case EN_RD_DMGEFF_FIRE_ARROW:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
                this->drawDmgEffTimer = 180;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                this->stunnedBySunsSong = false;
                this->sunsSongStunTimer = 0;
                this->drawDmgEffAlpha = 1.0f;
                break;

            case EN_RD_DMGEFF_LIGHT_ARROW:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
                this->drawDmgEffTimer = 60;
                this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                this->stunnedBySunsSong = false;
                this->sunsSongStunTimer = 0;
                this->drawDmgEffAlpha = 1.0f;
                break;

            case EN_RD_DMGEFF_DAMAGE:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                this->stunnedBySunsSong = false;
                this->sunsSongStunTimer = 0;
                break;

            case EN_RD_DMGEFF_LIGHT_RAY:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                this->stunnedBySunsSong = false;
                this->sunsSongStunTimer = 0;
                this->actor.colChkInfo.health = 0;
                break;

            default:
                return;
        }

        Actor_ApplyDamage(&this->actor);
        if (this->actor.colChkInfo.health == 0) {
            EnRd_UpdateParentForOtherRedeads(globalCtx, &this->actor, true);
            EnRd_SetupDead(this);
            Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, 0x90);
        } else {
            EnRd_SetupDamage(this);
        }
    }
}

void EnRd_UpdateCollision(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((this->actor.colChkInfo.health > 0) && (this->action != EN_RD_ACTION_GRABBING)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (((this->action != EN_RD_ACTION_DAMAGE) || ((player->unk_ADC != 0) && (player->unk_ADD != this->unk_3F1))) &&
            ((this->actionFunc != EnRd_Stunned) || (this->stunTimer == 0))) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void EnRd_UpdateEffect(EnRd* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffTimer > 0) {
        this->drawDmgEffTimer--;
    }

    if (this->drawDmgEffTimer < 20) {
        Math_SmoothStepToF(&this->drawDmgEffScale, 0.0f, 0.5f, 0.03f, 0.0f);
        this->drawDmgEffAlpha = this->drawDmgEffTimer * 0.05f;
    } else {
        Math_SmoothStepToF(&this->drawDmgEffScale, 0.5f, 0.1f, 0.02f, 0.0f);
    }
}

void EnRd_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRd* this = THIS;

    EnRd_UpdateDamage(this, globalCtx);
    if ((gSaveContext.sunsSongState != SUNSSONG_INACTIVE) && (!this->stunnedBySunsSong)) {
        gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
    }

    if ((this->damageEffect != EN_RD_DMGEFF_UNUSED_6) &&
        ((this->action != EN_RD_ACTION_RISING_FROM_COFFIN) || (this->damageEffect != EN_RD_DMGEFF_FIRE_ARROW))) {
        if (this->playerStunWaitTimer != 0) {
            this->playerStunWaitTimer--;
        }

        this->actionFunc(this, globalCtx);

        if ((this->action != EN_RD_ACTION_GRABBING) && (this->actor.speedXZ != 0.0f)) {
            Actor_MoveWithGravity(&this->actor);
        }

        if ((this->actor.shape.rot.x == 0) && (this->action != EN_RD_ACTION_GRABBING) &&
            (this->actor.speedXZ != 0.0f)) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 20.0f, 35.0f, 0x1D);
        }

        if (this->action == EN_RD_ACTION_ATTEMPTING_PLAYER_STUN) {
            EnRd_TurnTowardsPlayer(this, globalCtx);
        }
    }

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;

    EnRd_UpdateCollision(this, globalCtx);
    EnRd_SetupDanceIfConditionsMet(this, globalCtx);
    EnRd_UpdateEffect(this, globalCtx);
}

s32 EnRd_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                          Gfx** gfx) {
    EnRd* this = THIS;

    if (limbIndex == REDEAD_LIMB_HEAD_ROOT) {
        rot->y += this->headYRotation;
    } else if (limbIndex == REDEAD_LIMB_UPPER_BODY_ROOT) {
        rot->y += this->upperBodyYRotation;
    }
    return false;
}

void EnRd_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnRd* this = THIS;

    if ((this->drawDmgEffTimer != 0) &&
        ((limbIndex == REDEAD_LIMB_LEFT_THIGH) || (limbIndex == REDEAD_LIMB_LEFT_SHIN) ||
         (limbIndex == REDEAD_LIMB_LEFT_FOOT) || (limbIndex == REDEAD_LIMB_RIGHT_THIGH) ||
         (limbIndex == REDEAD_LIMB_RIGHT_SHIN) || (limbIndex == REDEAD_LIMB_RIGHT_FOOT) ||
         (limbIndex == REDEAD_LIMB_TORSO) || (limbIndex == REDEAD_LIMB_LEFT_SHOULDER_AND_UPPER_ARM) ||
         (limbIndex == REDEAD_LIMB_LEFT_FOREARM) || (limbIndex == REDEAD_LIMB_LEFT_HAND) ||
         (limbIndex == REDEAD_LIMB_RIGHT_SHOULDER_AND_UPPER_ARM) || (limbIndex == REDEAD_LIMB_RIGHT_FOREARM) ||
         (limbIndex == REDEAD_LIMB_RIGHT_HAND) || (limbIndex == REDEAD_LIMB_HEAD) ||
         (limbIndex == REDEAD_LIMB_PELVIS))) {
        Matrix_GetStateTranslation(&this->limbPos[this->limbIndex]);
        this->limbIndex++;
    }
}

void EnRd_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_808D7138 = { 0.25f, 0.25f, 0.25f };
    s32 pad;
    EnRd* this = THIS;
    Vec3f sp54 = this->actor.world.pos;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    this->limbIndex = 0;

    if (this->alpha == 255) {
        func_8012C28C(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->alpha);
        gSPSegment(POLY_OPA_DISP++, 0x08, D_801AEFA0);

        POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnRd_OverrideLimbDraw, EnRd_PostLimbDraw,
                                           &this->actor, POLY_OPA_DISP);

        func_800BC620(&sp54, &D_808D7138, 255, globalCtx);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);
        gSPSegment(POLY_XLU_DISP++, 0x08, D_801AEF88);

        POLY_XLU_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, EnRd_OverrideLimbDraw, NULL, &this->actor, POLY_XLU_DISP);
        func_800BC620(&sp54, &D_808D7138, this->alpha, globalCtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (this->drawDmgEffTimer > 0) {
        Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos),
                                this->drawDmgEffScale, 0.5f, this->drawDmgEffAlpha, this->drawDmgEffType);
    }
}
