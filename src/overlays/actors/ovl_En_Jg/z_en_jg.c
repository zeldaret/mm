/*
 * File: z_en_jg.c
 * Overlay: ovl_En_Jg
 * Description: Goron Elder
 */

#include "z_en_jg.h"
#include "objects/object_jg/object_jg.h"
#include "overlays/actors/ovl_En_S_Goro/z_en_s_goro.h"

#define FLAGS 0x00000019

#define THIS ((EnJg*)thisx)

#define FLAG_SHRINE_GORON_ARMS_RAISED (1 << 0)
#define FLAG_LOOKING_AT_PLAYER (1 << 2)
#define FLAG_DRUM_SPAWNED (1 << 3)

#define TEXT_TATL_OLD_GORON_FROZEN_SOLID 0x236
#define TEXT_EN_JG_WHAT_WAS_I_DOING 0xDAC
#define TEXT_EN_JG_I_MUST_HURRY 0xDAD
#define TEXT_EN_JG_HAVE_YOU_SOME_BUSINESS_WITH_ELDER 0xDAE
#define TEXT_EN_JG_WHAT_HAS_ME_SO_RUSHED 0xDAF
#define TEXT_EN_JG_ITS_THIS_COLD_SNAP 0xDB0
#define TEXT_EN_JG_ITS_THE_LACK_OF_GOODS 0xDB1
#define TEXT_EN_JG_ITS_MY_SON_CRYING_CONTINUOUSLY 0xDB2
#define TEXT_EN_JG_AS_THE_ELDER_I_MUST_DO_SOMETHING 0xDB3
#define TEXT_EN_JG_THIS_IS_OUR_PROBLEM_FIRST 0xDB4
#define TEXT_EN_JG_THIS_IS_OUR_PROBLEM_REPEAT 0xDB5
#define TEXT_EN_JG_HUNH 0xDB6
#define TEXT_EN_JG_OH_YOURE_DARMANI 0xDB7
#define TEXT_EN_JG_AM_I_HALLUCINATING 0xDB8
#define TEXT_EN_JG_MAYBE_THIS_IS_THE_DOING_OF_SNOWHEAD 0xDB9
#define TEXT_EN_JG_IVE_BEEN_MADE_A_FOOL_OF 0xDBA
#define TEXT_EN_JG_IF_I_CAN_SEE_PAST_THE_ILLUSION 0xDBB
#define TEXT_EN_JG_FOLLOWING_ME_WONT_DO_ANY_GOOD 0xDBC
#define TEXT_EN_JG_WHAT 0xDBD
#define TEXT_EN_JG_MY_SON_MISSES_ME 0xDBE
#define TEXT_EN_JG_WHY_DO_YOU_KNOW_THAT 0xDBF
#define TEXT_EN_JG_FORGIVE_ME_MY_CHILD 0xDC0
#define TEXT_EN_JG_I_NO_LONGER_CARE_IF_YOURE_A_GHOST 0xDC1
#define TEXT_EN_JG_PLEASE_QUIETLY_SING_MY_SON_TO_SLEEP 0xDC2
#define TEXT_EN_JG_THE_SAME_MELODY_I_PLAYED_FOR_YOU 0xDC3
#define TEXT_EN_JG_SO_COLD_I_CANT_PLAY 0xDC4
#define TEXT_EN_JG_LET_ME_PLAY_ONCE_MORE 0xDC5
#define TEXT_EN_JG_I_AM_COUNTING_ON_YOU 0xDC6
#define TEXT_EN_JG_HOW_DOES_SONG_GO 0xDC7
#define TEXT_EN_JG_UMM 0xDC8
#define TEXT_EN_JG_LIKE_THIS 0xDC9
#define TEXT_EN_JG_CAN_ONLY_REMEMBER_THE_BEGINNING 0xDCA
#define TEXT_EN_JG_WELCOME_TO_SPRING 0xDCB
#define TEXT_EN_JG_WERE_HOLDING_THE_GORON_RACES 0xDCC
#define TEXT_EN_JG_IVE_BEEN_WAITING_IMPATIENTLY 0xDCD
#define TEXT_EN_JG_I_HEARD_YOU_SEALED_THE_BLIZZARD 0xDCE
#define TEXT_EN_JG_SPRING_HAS_COME_THANKS_TO_YOU 0xDCF
#define TEXT_EN_JG_CHEER_GREATEST_GORON_HERO 0xDD0
#define TEXT_EN_JG_CHEER_DARMANI 0xDD1
#define TEXT_EN_JG_CHEER_THE_IMMORTAL_GORON 0xDD2
#define TEXT_EN_JG_CHEER_THE_STAR_WE_WISH_UPON 0xDD3
#define TEXT_EN_JG_CHEER_DARMANI_GREATEST_OF_GORONS 0xDD4
#define TEXT_EN_JG_CHEER_GREATEST_OF_GORONS 0xDD5
#define TEXT_EN_JG_CHEER_DARMANI_GREATEST_IN_THE_WORLD 0xDD6
#define TEXT_EN_JG_CHEER_GREATEST_IN_THE_WORLD 0xDD7
#define TEXT_EN_JG_SON_WENT_TO_SEE_RACES 0xDD8
#define TEXT_EN_JG_YIELD_PATRIARCH_TO_YOUNGER_ONE 0xDD9
#define TEXT_EN_JG_GORON_WHO_TAKES_CARE_OF_ALL 0xDDA
#define TEXT_EN_JG_THE_CHOSEN_ONE_DARMANI 0xDDB
#define TEXT_EN_JG_EVERYONE_WOULD_ACCEPT_YOU 0xDDC
#define TEXT_EN_JG_THINK_IT_OVER_SLOWLY 0xDDD
#define TEXT_EN_JG_COME_BACK_AFTER_ENTERING_RACE 0xDDE
#define TEXT_EN_JG_MY_SON_IS_AWAITING_YOU 0xDDF
#define TEXT_EN_JG_GO_BEYOND_TWIN_ISLANDS_CAVE 0xDE0

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnJg_GoronShrineTalk(EnJg* this, GlobalContext* globalCtx);
void EnJg_GoronShrineCheer(EnJg* this, GlobalContext* globalCtx);
void EnJg_AlternateTalkOrWalkInPlace(EnJg* this, GlobalContext* globalCtx);
void EnJg_Walk(EnJg* this, GlobalContext* globalCtx);
void EnJg_Talk(EnJg* this, GlobalContext* globalCtx);
void EnJg_SetupWalk(EnJg* this, GlobalContext* globalCtx);
void EnJg_FrozenIdle(EnJg* this, GlobalContext* globalCtx);
void EnJg_EndFrozenInteraction(EnJg* this, GlobalContext* globalCtx);
void EnJg_TeachLullabyIntro(EnJg* this, GlobalContext* globalCtx);
void EnJg_LullabyIntroCutsceneAction(EnJg* this, GlobalContext* globalCtx);
s32 EnJg_GetNextTextId(EnJg* this);
s32 EnJg_GetStartingConversationTextId(EnJg* this, GlobalContext* globalCtx);
void EnJg_CheckIfTalkingToPlayerAndHandleFreezeTimer(EnJg* this, GlobalContext* globalCtx);

typedef enum {
    /*  0 */ EN_JG_ANIMATION_IDLE,
    /*  1 */ EN_JG_ANIMATION_WALK,
    /*  2 */ EN_JG_ANIMATION_WAVING,
    /*  3 */ EN_JG_ANIMATION_SHAKING_HEAD,
    /*  4 */ EN_JG_ANIMATION_SURPRISE_START,
    /*  5 */ EN_JG_ANIMATION_SURPRISE_LOOP,
    /*  6 */ EN_JG_ANIMATION_ANGRY,
    /*  7 */ EN_JG_ANIMATION_FROZEN_START,
    /*  8 */ EN_JG_ANIMATION_FROZEN_LOOP,
    /*  9 */ EN_JG_ANIMATION_WALK_2,
    /* 10 */ EN_JG_ANIMATION_TAKING_OUT_DRUM,
    /* 11 */ EN_JG_ANIMATION_DRUM_IDLE,
    /* 12 */ EN_JG_ANIMATION_PLAYING_DRUM,
    /* 13 */ EN_JG_ANIMATION_THINKING,
    /* 14 */ EN_JG_ANIMATION_REMEMBERING,
    /* 15 */ EN_JG_ANIMATION_STRONG_REMEMBERING,
    /* 16 */ EN_JG_ANIMATION_DEPRESSED,
    /* 17 */ EN_JG_ANIMATION_CUTSCENE_IDLE,
    /* 18 */ EN_JG_ANIMATION_CRADLE,
    /* 19 */ EN_JG_ANIMATION_MAX,
} EnJgAnimationIndex;

typedef enum {
    /* 0x0 */ EN_JG_ACTION_FIRST_THAW,
    /* 0x1 */ EN_JG_ACTION_SPAWNING,
    /* 0x2 */ EN_JG_ACTION_FROZEN_OR_NON_FIRST_THAW,
    /* 0x3 */ EN_JG_ACTION_LULLABY_INTRO_CS,
} EnJgAction;

const ActorInit En_Jg_InitVars = {
    ACTOR_EN_JG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_JG,
    sizeof(EnJg),
    (ActorFunc)EnJg_Init,
    (ActorFunc)EnJg_Destroy,
    (ActorFunc)EnJg_Update,
    (ActorFunc)EnJg_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 60, 80, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 50, 80, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static ActorAnimationEntryS sAnimations[] = {
    { &gGoronElderIdleAnim, 1.0f, 0, -1, 0, -10 },          { &gGoronElderWalkAnim, 1.0f, 0, -1, 0, -10 },
    { &gGoronElderWavingAnim, 1.0f, 0, -1, 0, -10 },        { &gGoronElderHeadShakeAnim, 1.0f, 0, -1, 0, -10 },
    { &gGoronElderSurpriseStartAnim, 1.0f, 0, -1, 2, -10 }, { &gGoronElderSurpriseLoopAnim, 1.0f, 0, -1, 0, -10 },
    { &gGoronElderAngryAnim, 1.0f, 0, -1, 0, -10 },         { &gGoronElderSurpriseStartAnim, 2.0f, 0, -1, 2, 0 },
    { &gGoronElderSurpriseStartAnim, -2.0f, 0, -1, 2, 0 },  { &gGoronElderWalkAnim, -1.0f, 0, -1, 0, -10 },
    { &gGoronElderTakeOutDrumAnim, 1.0f, 0, -1, 2, 0 },     { &gGoronElderDrumIdleAnim, 1.0f, 0, -1, 0, 0 },
    { &gGoronElderPlayingDrumAnim, 1.0f, 1, 44, 2, 0 },     { &gGoronElderThinkingAnim, 1.0f, 0, -1, 0, 0 },
    { &gGoronElderRememberingAnim, 1.0f, 0, -1, 2, 0 },     { &gGoronElderStrongRememberingAnim, 1.0f, 0, -1, 2, 0 },
    { &gGoronElderDepressedAnim, 1.0f, 0, -1, 0, 0 },       { &gGoronElderIdleAnim, 1.0f, 0, -1, 0, 0 },
    { &gGoronElderCradleAnim, 1.0f, 0, -1, 0, 0 },
};

static Vec3f sSfxPos = { 0.0f, 0.0f, 0.0f };

static Vec3f sFocusOffset = { 0.0f, 0.0f, 0.0f };

static Vec3f sBreathPosOffset = { 1000.0f, -500.0f, 0.0f };

static Vec3f sBreathVelOffset = { 0.0f, 0.0f, 0.75f };

static Vec3f sBreathAccelOffset = { 0.0f, 0.0f, -0.070000000298f };

/**
 * When the elder and the Gorons in the shrine are doing a cheer
 * for Darmani, the camera will focus on specific Gorons for
 * certain parts of the cheer. This function is responsible for
 * returning a pointer to the specified Goron so the camera
 * can focus on them.
 */
Actor* EnJg_GetShrineGoronToFocusOn(GlobalContext* globalCtx, u8 focusedShrineGoronParam) {
    Actor* actorIterator = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actorIterator != NULL) {
        if ((actorIterator->id == ACTOR_EN_S_GORO) &&
            (EN_S_GORO_GET_PARAM_F(actorIterator) == focusedShrineGoronParam)) {
            return actorIterator;
        }

        actorIterator = actorIterator->next;
    }

    return NULL;
}

void EnJg_UpdateCollision(EnJg* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 30.0f, 30.0f, 7);
}

s16 EnJg_GetWalkingYRotation(Path* path, s32 pointIndex, Vec3f* pos, f32* distSQ) {
    Vec3s* points;
    f32 diffX;
    f32 diffZ;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[pointIndex];
        diffX = points[0].x - pos->x;
        diffZ = points[0].z - pos->z;
    } else {
        diffX = 0.0f;
        diffZ = 0.0f;
    }

    *distSQ = SQ(diffX) + SQ(diffZ);

    return RADF_TO_BINANG(Math_Acot2F(diffZ, diffX));
}

s32 EnJg_ReachedPoint(EnJg* this, Path* path, s32 pointIndex) {
    Vec3s* points = Lib_SegmentedToVirtual(path->points);
    s32 pathCount = path->count;
    s32 currentPoint = pointIndex;
    s32 reached = false;
    f32 diffX;
    f32 diffZ;
    f32 px;
    f32 pz;
    f32 d;
    Vec3f point;

    Math_Vec3s_ToVec3f(&point, &points[pointIndex]);
    if (currentPoint == 0) {
        diffX = points[1].x - points[0].x;
        diffZ = points[1].z - points[0].z;
    } else {
        if (currentPoint == (pathCount - 1)) {
            diffX = points[pathCount - 1].x - points[pathCount - 2].x;
            diffZ = points[pathCount - 1].z - points[pathCount - 2].z;
        } else {
            diffX = points[currentPoint + 1].x - points[currentPoint - 1].x;
            diffZ = points[currentPoint + 1].z - points[currentPoint - 1].z;
        }
    }

    func_8017B7F8(&point, RADF_TO_BINANG(func_80086B30(diffX, diffZ)), &px, &pz, &d);

    if (((this->actor.world.pos.x * px) + (pz * this->actor.world.pos.z) + d) > 0.0f) {
        reached = true;
    }

    return reached;
}

s16 EnJg_GetCutsceneForTeachingLullabyIntro(EnJg* this) {
    s16 temp = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (temp > 0) {
        return this->actor.cutscene;
    }

    return ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
}

void EnJg_SetupGoronShrineCheer(EnJg* this) {
    ActorCutscene_Stop(this->cutscene);
    if (this->focusedShrineGoronParam == 10) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            this->actionFunc = EnJg_GoronShrineTalk;
        } else {
            this->cutscene = 0x7C;
        }
    } else {
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
    }

    ActorCutscene_SetIntentToPlay(this->cutscene);
    this->actionFunc = EnJg_GoronShrineCheer;

    switch (this->textId) {
        case TEXT_EN_JG_CHEER_GREATEST_GORON_HERO:
        case TEXT_EN_JG_CHEER_THE_IMMORTAL_GORON:
        case TEXT_EN_JG_CHEER_THE_STAR_WE_WISH_UPON:
        case TEXT_EN_JG_CHEER_DARMANI_GREATEST_OF_GORONS:
        case TEXT_EN_JG_CHEER_DARMANI_GREATEST_IN_THE_WORLD:
            this->flags |= FLAG_SHRINE_GORON_ARMS_RAISED;
            break;

        default:
            this->flags &= ~FLAG_SHRINE_GORON_ARMS_RAISED;
            break;
    }
}

void EnJg_SetupTalk(EnJg* this, GlobalContext* globalCtx) {
    switch (this->textId) {
        case TEXT_EN_JG_WHAT_WAS_I_DOING:
            this->animationIndex = EN_JG_ANIMATION_SHAKING_HEAD;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Talk;
            break;

        case TEXT_EN_JG_I_MUST_HURRY:
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_START;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_AlternateTalkOrWalkInPlace;
            break;

        case TEXT_EN_JG_OH_YOURE_DARMANI:
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_START;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Talk;
            break;

        case TEXT_EN_JG_HAVE_YOU_SOME_BUSINESS_WITH_ELDER:
        case TEXT_EN_JG_AS_THE_ELDER_I_MUST_DO_SOMETHING:
        case TEXT_EN_JG_HUNH:
        case TEXT_EN_JG_IVE_BEEN_MADE_A_FOOL_OF:
        case TEXT_EN_JG_WHAT:
        case TEXT_EN_JG_SO_COLD_I_CANT_PLAY:
            this->animationIndex = EN_JG_ANIMATION_IDLE;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Talk;
            break;

        case TEXT_EN_JG_ITS_THIS_COLD_SNAP:
        case TEXT_EN_JG_IF_I_CAN_SEE_PAST_THE_ILLUSION:
        case TEXT_EN_JG_FOLLOWING_ME_WONT_DO_ANY_GOOD:
        case TEXT_EN_JG_I_AM_COUNTING_ON_YOU:
            this->animationIndex = EN_JG_ANIMATION_ANGRY;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Talk;
            break;

        case TEXT_EN_JG_THIS_IS_OUR_PROBLEM_FIRST:
        case TEXT_EN_JG_THIS_IS_OUR_PROBLEM_REPEAT:
            this->animationIndex = EN_JG_ANIMATION_WAVING;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Talk;
            break;
    }
}

void EnJg_Idle(EnJg* this, GlobalContext* globalCtx) {
    EnJg_CheckIfTalkingToPlayerAndHandleFreezeTimer(this, globalCtx);
}

void EnJg_GoronShrineIdle(EnJg* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->flags |= FLAG_LOOKING_AT_PLAYER;
        func_801518B0(globalCtx, this->textId, &this->actor);
        this->actionFunc = EnJg_GoronShrineTalk;
    } else if ((this->actor.xzDistToPlayer < 100.0f) || (this->actor.isTargeted)) {
        func_800B863C(&this->actor, globalCtx);
        this->textId = EnJg_GetStartingConversationTextId(this, globalCtx);
    }
}

void EnJg_GoronShrineTalk(EnJg* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx))) {
        if ((this->textId == TEXT_EN_JG_WERE_HOLDING_THE_GORON_RACES) ||
            (this->textId == TEXT_EN_JG_THINK_IT_OVER_SLOWLY) ||
            (this->textId == TEXT_EN_JG_GO_BEYOND_TWIN_ISLANDS_CAVE)) {
            // There is nothing more to say after these lines, so end the current conversation.
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->flags &= ~FLAG_LOOKING_AT_PLAYER;
            this->actionFunc = EnJg_GoronShrineIdle;
        } else {
            this->textId = EnJg_GetNextTextId(this);
            func_801518B0(globalCtx, this->textId, &this->actor);
        }
    }
}

void EnJg_GoronShrineCheer(EnJg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        switch (this->textId) {
            case TEXT_EN_JG_CHEER_GREATEST_GORON_HERO:
            case TEXT_EN_JG_CHEER_THE_IMMORTAL_GORON:
            case TEXT_EN_JG_CHEER_THE_STAR_WE_WISH_UPON:
            case TEXT_EN_JG_CHEER_DARMANI_GREATEST_OF_GORONS:
            case TEXT_EN_JG_CHEER_DARMANI_GREATEST_IN_THE_WORLD:
                // Focus on a specifc Goron for these lines
                this->shrineGoron = EnJg_GetShrineGoronToFocusOn(globalCtx, this->focusedShrineGoronParam);
                ActorCutscene_Start(this->cutscene, this->shrineGoron);
                func_800E0308(globalCtx->cameraPtrs[0], this->shrineGoron);
                break;

            default:
                // Focus on the whole group for these lines
                ActorCutscene_Start(this->cutscene, &this->actor);
                func_800E0308(globalCtx->cameraPtrs[0], this->shrineGoron);
                break;
        }
        this->actionFunc = EnJg_GoronShrineTalk;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            if (this->focusedShrineGoronParam == 10) {
                this->actionFunc = EnJg_GoronShrineTalk;
            } else {
                ActorCutscene_Stop(0x7C);
            }
        }
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

/**
 * You need to reach a certain point in the conversation when talking with the elder before
 * he starts walking for the first time. This function specifically handles this scenario; the
 * reason they used this instead of EnJg_Talk is seemingly to bypass EnJg_SetupWalk resetting
 * the freeze timer.
 *
 * Additionally, when the elder has reached the end of his specified path, this function will
 * set his speed to 0, causing him to walk in place.
 */
void EnJg_AlternateTalkOrWalkInPlace(EnJg* this, GlobalContext* globalCtx) {
    u8 messageState = Message_GetState(&globalCtx->msgCtx);
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);

    if (this->animationIndex == EN_JG_ANIMATION_SURPRISE_START) {
        if (currentFrame == lastFrame) {
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_LOOP;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        }
    } else if (this->animationIndex == EN_JG_ANIMATION_SURPRISE_LOOP) {
        if ((messageState == 5) && (func_80147624(globalCtx))) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->flags &= ~FLAG_LOOKING_AT_PLAYER;
            this->animationIndex = EN_JG_ANIMATION_WALK;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Walk;
        }
    } else if (this->animationIndex == EN_JG_ANIMATION_WALK) {
        Math_ApproachF(&this->actor.speedXZ, 0.0f, 0.2f, 1.0f);
        EnJg_CheckIfTalkingToPlayerAndHandleFreezeTimer(this, globalCtx);
    }
}

void EnJg_Walk(EnJg* this, GlobalContext* globalCtx) {
    s16 yRotation;
    f32 distSQ;

    if (this->path != NULL) {
        yRotation = EnJg_GetWalkingYRotation(this->path, this->currentPoint, &this->actor.world.pos, &distSQ);
        if (this->actor.bgCheckFlags & 8) {
            yRotation = this->actor.wallYaw;
        }

        Math_SmoothStepToS(&this->actor.world.rot.y, yRotation, 4, 0x3E8, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;

        if (EnJg_ReachedPoint(this, this->path, this->currentPoint)) {
            if (this->currentPoint >= (this->path->count - 1)) {
                // Force the elder to walk in place
                this->animationIndex = EN_JG_ANIMATION_WALK;
                this->actionFunc = EnJg_AlternateTalkOrWalkInPlace;
            } else {
                this->currentPoint++;
                Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
            }
        } else {
            Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
        }
    }

    EnJg_CheckIfTalkingToPlayerAndHandleFreezeTimer(this, globalCtx);
}

void EnJg_Talk(EnJg* this, GlobalContext* globalCtx) {
    u8 messageState = Message_GetState(&globalCtx->msgCtx);
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);
    u16 temp;

    if ((this->animationIndex == EN_JG_ANIMATION_SURPRISE_START) && (currentFrame == lastFrame)) {
        this->animationIndex = EN_JG_ANIMATION_SURPRISE_LOOP;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
    }

    if ((messageState == 5) && (func_80147624(globalCtx))) {
        temp = this->textId;
        if ((temp == TEXT_EN_JG_THIS_IS_OUR_PROBLEM_FIRST) || (temp == TEXT_EN_JG_THIS_IS_OUR_PROBLEM_REPEAT) ||
            (temp == TEXT_EN_JG_SO_COLD_I_CANT_PLAY) || (temp == TEXT_EN_JG_I_AM_COUNTING_ON_YOU)) {
            // There is nothing more to say after these lines, so end the current conversation.
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->flags &= ~FLAG_LOOKING_AT_PLAYER;
            this->actionFunc = EnJg_SetupWalk;
            return;
        }

        temp = this->textId;
        if ((temp == TEXT_EN_JG_IF_I_CAN_SEE_PAST_THE_ILLUSION) || (temp == TEXT_EN_JG_FOLLOWING_ME_WONT_DO_ANY_GOOD)) {
            if (!(gSaveContext.weekEventReg[0x18] & 0x80)) {
                // The player hasn't talked to the Goron Child at least once, so they can't learn
                // the Lullaby Intro. End the current conversation with the player.
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->flags &= ~FLAG_LOOKING_AT_PLAYER;
                this->actionFunc = EnJg_SetupWalk;
            } else if (((gSaveContext.weekEventReg[0x18] & 0x40)) ||
                       (CHECK_QUEST_ITEM(QUEST_SONG_LULLABY) || CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO))) {
                // The player already has the Lullaby or Lullaby Intro, so say "I'm counting on you"
                this->textId = EnJg_GetNextTextId(this);
                func_801518B0(globalCtx, this->textId, &this->actor);
                this->actionFunc = EnJg_SetupTalk;
            } else {
                // To get to this point, the player *has* talked to the Goron Child, but doesn't
                // already have the Lullaby or Lullaby Intro. End the current conversation and
                // start the cutscene that teaches the Lullaby Intro.
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->flags &= ~FLAG_LOOKING_AT_PLAYER;
                this->cutscene = EnJg_GetCutsceneForTeachingLullabyIntro(this);
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                }
                ActorCutscene_SetIntentToPlay(this->cutscene);
                this->actionFunc = EnJg_TeachLullabyIntro;
            }
        } else {
            this->textId = EnJg_GetNextTextId(this);
            func_801518B0(globalCtx, this->textId, &this->actor);
            this->actionFunc = EnJg_SetupTalk;
        }
    }
}

void EnJg_SetupWalk(EnJg* this, GlobalContext* globalCtx) {
    if (this->animationIndex != EN_JG_ANIMATION_WALK) {
        this->animationIndex = EN_JG_ANIMATION_WALK;
        this->freezeTimer = 1000;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = EnJg_Walk;
    } else {
        this->freezeTimer = 1000;
        this->actionFunc = EnJg_Walk;
    }
}

void EnJg_Freeze(EnJg* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);

    if (this->action == EN_JG_ACTION_SPAWNING) {
        this->action = EN_JG_ACTION_FROZEN_OR_NON_FIRST_THAW;
        this->freezeTimer = 1000;
        this->skelAnime.curFrame = lastFrame;
        this->icePoly = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                    this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                    this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
        this->animationIndex = EN_JG_ANIMATION_FROZEN_LOOP;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = EnJg_FrozenIdle;
    } else if (this->animationIndex == EN_JG_ANIMATION_FROZEN_START) {
        this->action = EN_JG_ACTION_FROZEN_OR_NON_FIRST_THAW;
        if (currentFrame == lastFrame) {
            this->freezeTimer = 1000;
            this->icePoly = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                                        this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                                        this->actor.world.rot.y, this->actor.world.rot.z, 0xFF50);
            this->animationIndex = EN_JG_ANIMATION_FROZEN_LOOP;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_FrozenIdle;
        }
    }
}

void EnJg_FrozenIdle(EnJg* this, GlobalContext* globalCtx) {
    if (this->icePoly->update == NULL) {
        this->icePoly = NULL;
        if (this->animationIndex == EN_JG_ANIMATION_FROZEN_LOOP) {
            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                this->animationIndex = EN_JG_ANIMATION_IDLE;

                // If you've never talked to the elder before, he stands
                // around idle until you've talked to him at least once.
                // Otherwise, he immediately begins walking after being
                // thawed out.
                if (this->textId == TEXT_EN_JG_WHAT_WAS_I_DOING) {
                    func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
                    this->actionFunc = EnJg_Idle;
                } else {
                    this->freezeTimer = 1000;
                    func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
                    this->actionFunc = EnJg_Walk;
                }
            }
        }
    } else {
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            func_801518B0(globalCtx, TEXT_TATL_OLD_GORON_FROZEN_SOLID, &this->actor);
            this->actionFunc = EnJg_EndFrozenInteraction;
        } else if (this->actor.isTargeted) {
            func_800B863C(&this->actor, globalCtx);
        }
    }
}

void EnJg_EndFrozenInteraction(EnJg* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx) != 0) {
        globalCtx->msgCtx.unk11F22 = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->actionFunc = EnJg_FrozenIdle;
    }
}

void EnJg_TeachLullabyIntro(EnJg* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        this->actionFunc = EnJg_LullabyIntroCutsceneAction;
    } else {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void EnJg_LullabyIntroCutsceneAction(EnJg* this, GlobalContext* globalCtx) {
    s32 pad;

    if (func_800EE29C(globalCtx, 0x1D6)) {
        u32 actionIndex = func_800EE200(globalCtx, 0x1D6);

        if (this->csAction != globalCtx->csCtx.npcActions[actionIndex]->unk0) {
            this->csAction = globalCtx->csCtx.npcActions[actionIndex]->unk0;

            switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
                case 1:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_CUTSCENE_IDLE;
                    if (this->drum != NULL) {
                        Actor_MarkForDeath(this->drum);
                        this->drum = NULL;
                    }
                    break;

                case 2:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_TAKING_OUT_DRUM;
                    break;

                case 3:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_DRUM_IDLE;
                    break;

                case 4:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_PLAYING_DRUM;
                    break;

                case 5:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_THINKING;
                    break;

                case 6:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_REMEMBERING;
                    break;

                case 7:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_STRONG_REMEMBERING;
                    break;

                case 8:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_DEPRESSED;
                    break;

                case 9:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_CRADLE;
                    break;

                default:
                    this->cutsceneAnimationIndex = EN_JG_ANIMATION_IDLE;
                    break;
            }

            func_8013BC6C(&this->skelAnime, sAnimations, this->cutsceneAnimationIndex);
        }

        if ((!(this->flags & FLAG_DRUM_SPAWNED)) &&
            (((this->cutsceneAnimationIndex == EN_JG_ANIMATION_TAKING_OUT_DRUM) &&
              (Animation_OnFrame(&this->skelAnime, 14.0f)) && (this->action != EN_JG_ACTION_LULLABY_INTRO_CS)) ||
             (((this->cutsceneAnimationIndex == EN_JG_ANIMATION_DRUM_IDLE) ||
               (this->cutsceneAnimationIndex == EN_JG_ANIMATION_PLAYING_DRUM)) &&
              (this->action == EN_JG_ACTION_LULLABY_INTRO_CS)))) {
            this->flags |= FLAG_DRUM_SPAWNED;
            this->drum = Actor_SpawnAsChildAndCutscene(
                &globalCtx->actorCtx, globalCtx, ACTOR_OBJ_JG_GAKKI, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, this->actor.shape.rot.x, this->actor.shape.rot.y, this->actor.shape.rot.z,
                this->actor.params, this->actor.cutscene, this->actor.unk20, NULL);
        }

        if (this->cutsceneAnimationIndex == EN_JG_ANIMATION_TAKING_OUT_DRUM) {
            if (Animation_OnFrame(&this->skelAnime, 23.0f)) {
                func_8019F1C0(&sSfxPos, NA_SE_EV_WOOD_BOUND_S);
            } else if (Animation_OnFrame(&this->skelAnime, 38.0f)) {
                func_8019F1C0(&sSfxPos, NA_SE_EV_OBJECT_SLIDE);
            }
        }
    } else {
        this->csAction = 99;
        this->freezeTimer = 1000;
        gSaveContext.weekEventReg[0x18] |= 0x40;
        this->actionFunc = EnJg_Idle;
    }
}

/**
 * Returns the "next" text ID that the elder should use based on his current text ID.
 * Note that the results here can be counterintuitive, because his current text ID can
 * cause multiple text boxes to display in sequence; this function will return the text
 * ID that starts the *next* sequence.
 *
 * As an example, TEXT_EN_JG_OH_YOURE_DARMANI displays that TEXT_EN_JG_OH_YOURE_DARMANI,
 * TEXT_EN_JG_AM_I_HALLUCINATING, and TEXT_EN_JG_MAYBE_THIS_IS_THE_DOING_OF_SNOWHEAD
 * in sequence, so the start of the next sequence is TEXT_EN_JG_IVE_BEEN_MADE_A_FOOL_OF.
 * Sequences generally seem to be tied to text IDs that should all share the same animation.
 */
s32 EnJg_GetNextTextId(EnJg* this) {
    switch (this->textId) {
        case TEXT_EN_JG_WHAT_WAS_I_DOING:
            return TEXT_EN_JG_I_MUST_HURRY;

        case TEXT_EN_JG_HAVE_YOU_SOME_BUSINESS_WITH_ELDER:
            return TEXT_EN_JG_ITS_THIS_COLD_SNAP;

        case TEXT_EN_JG_ITS_THIS_COLD_SNAP:
            return TEXT_EN_JG_AS_THE_ELDER_I_MUST_DO_SOMETHING;

        case TEXT_EN_JG_AS_THE_ELDER_I_MUST_DO_SOMETHING:
            return TEXT_EN_JG_THIS_IS_OUR_PROBLEM_FIRST;

        case TEXT_EN_JG_HUNH:
            return TEXT_EN_JG_OH_YOURE_DARMANI;

        case TEXT_EN_JG_OH_YOURE_DARMANI:
            return TEXT_EN_JG_IVE_BEEN_MADE_A_FOOL_OF;

        case TEXT_EN_JG_IVE_BEEN_MADE_A_FOOL_OF:
            return TEXT_EN_JG_IF_I_CAN_SEE_PAST_THE_ILLUSION;

        case TEXT_EN_JG_IF_I_CAN_SEE_PAST_THE_ILLUSION:
        case TEXT_EN_JG_FOLLOWING_ME_WONT_DO_ANY_GOOD:
            return TEXT_EN_JG_I_AM_COUNTING_ON_YOU;

        case TEXT_EN_JG_WELCOME_TO_SPRING:
            return TEXT_EN_JG_WERE_HOLDING_THE_GORON_RACES;

        case TEXT_EN_JG_COME_BACK_AFTER_ENTERING_RACE:
            return TEXT_EN_JG_MY_SON_IS_AWAITING_YOU;

        case TEXT_EN_JG_MY_SON_IS_AWAITING_YOU:
            return TEXT_EN_JG_GO_BEYOND_TWIN_ISLANDS_CAVE;

        case TEXT_EN_JG_IVE_BEEN_WAITING_IMPATIENTLY:
            return TEXT_EN_JG_I_HEARD_YOU_SEALED_THE_BLIZZARD;

        case TEXT_EN_JG_I_HEARD_YOU_SEALED_THE_BLIZZARD:
            return TEXT_EN_JG_SPRING_HAS_COME_THANKS_TO_YOU;

        case TEXT_EN_JG_SPRING_HAS_COME_THANKS_TO_YOU:
            this->focusedShrineGoronParam = 3;
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->actionFunc = EnJg_GoronShrineCheer;
            return TEXT_EN_JG_CHEER_GREATEST_GORON_HERO;

        case TEXT_EN_JG_CHEER_GREATEST_GORON_HERO:
            EnJg_SetupGoronShrineCheer(this);
            return TEXT_EN_JG_CHEER_DARMANI;

        case TEXT_EN_JG_CHEER_DARMANI:
            switch (this->focusedShrineGoronParam) {
                case 3:
                    this->focusedShrineGoronParam = 4;
                    EnJg_SetupGoronShrineCheer(this);
                    return TEXT_EN_JG_CHEER_THE_IMMORTAL_GORON;

                case 4:
                    this->focusedShrineGoronParam = 5;
                    EnJg_SetupGoronShrineCheer(this);
                    return TEXT_EN_JG_CHEER_THE_STAR_WE_WISH_UPON;

                case 5:
                    this->focusedShrineGoronParam = 6;
                    EnJg_SetupGoronShrineCheer(this);
                    return TEXT_EN_JG_CHEER_DARMANI_GREATEST_OF_GORONS;

                default:
                    return TEXT_EN_JG_CHEER_DARMANI_GREATEST_OF_GORONS;
            }
            break;

        case TEXT_EN_JG_CHEER_THE_IMMORTAL_GORON:
            EnJg_SetupGoronShrineCheer(this);
            return TEXT_EN_JG_CHEER_DARMANI;

        case TEXT_EN_JG_CHEER_THE_STAR_WE_WISH_UPON:
            EnJg_SetupGoronShrineCheer(this);
            return TEXT_EN_JG_CHEER_DARMANI;

        case TEXT_EN_JG_CHEER_DARMANI_GREATEST_OF_GORONS:
            EnJg_SetupGoronShrineCheer(this);
            return TEXT_EN_JG_CHEER_GREATEST_OF_GORONS;

        case TEXT_EN_JG_CHEER_GREATEST_OF_GORONS:
            this->focusedShrineGoronParam = 7;
            EnJg_SetupGoronShrineCheer(this);
            return TEXT_EN_JG_CHEER_DARMANI_GREATEST_IN_THE_WORLD;

        case TEXT_EN_JG_CHEER_DARMANI_GREATEST_IN_THE_WORLD:
            EnJg_SetupGoronShrineCheer(this);
            return TEXT_EN_JG_CHEER_GREATEST_IN_THE_WORLD;

        case TEXT_EN_JG_CHEER_GREATEST_IN_THE_WORLD:
            this->focusedShrineGoronParam = 10;
            EnJg_SetupGoronShrineCheer(this);
            this->flags &= ~FLAG_SHRINE_GORON_ARMS_RAISED;
            return TEXT_EN_JG_SON_WENT_TO_SEE_RACES;

        case TEXT_EN_JG_SON_WENT_TO_SEE_RACES:
            return TEXT_EN_JG_YIELD_PATRIARCH_TO_YOUNGER_ONE;

        case TEXT_EN_JG_YIELD_PATRIARCH_TO_YOUNGER_ONE:
            return TEXT_EN_JG_GORON_WHO_TAKES_CARE_OF_ALL;

        case TEXT_EN_JG_GORON_WHO_TAKES_CARE_OF_ALL:
            return TEXT_EN_JG_THE_CHOSEN_ONE_DARMANI;

        case TEXT_EN_JG_THE_CHOSEN_ONE_DARMANI:
            return TEXT_EN_JG_EVERYONE_WOULD_ACCEPT_YOU;

        case TEXT_EN_JG_EVERYONE_WOULD_ACCEPT_YOU:
            gSaveContext.weekEventReg[0x4D] |= 0x80;
            return TEXT_EN_JG_THINK_IT_OVER_SLOWLY;

        default:
            return 0;
    }
}

/**
 * Returns the text ID of the first thing the elder should say when you talk to him
 * under most circumstances. Some circumstances (like the very first time the player
 * talks to him after he thaws) bypass this function.
 */
s32 EnJg_GetStartingConversationTextId(EnJg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!EN_JG_IS_IN_GORON_SHRINE(&this->actor)) {
        if (player->transformation == PLAYER_FORM_GORON) {
            if ((gSaveContext.weekEventReg[0x18] & 0x10) || CHECK_QUEST_ITEM(QUEST_SONG_LULLABY) ||
                CHECK_QUEST_ITEM(QUEST_SONG_LULLABY_INTRO)) {
                // The player has already talked as a Goron at least once.
                return TEXT_EN_JG_FOLLOWING_ME_WONT_DO_ANY_GOOD;
            }

            // The player has never talked as a Goron.
            return TEXT_EN_JG_HUNH;
        }

        if (gSaveContext.weekEventReg[0x18] & 0x20) {
            // The player has already talked as a non-Goron at least once.
            return TEXT_EN_JG_THIS_IS_OUR_PROBLEM_REPEAT;
        }

        // The player has never talked as a non-Goron.
        return TEXT_EN_JG_HAVE_YOU_SOME_BUSINESS_WITH_ELDER;
    }

    if (player->transformation == PLAYER_FORM_GORON) {
        if (gSaveContext.weekEventReg[0x4D] & 0x80) {
            // The player has heard the Goron Shrine cheer as a Goron at least once.
            return TEXT_EN_JG_COME_BACK_AFTER_ENTERING_RACE;
        }

        // The player has never heard the Goron Shrine cheer as a Goron.
        return TEXT_EN_JG_IVE_BEEN_WAITING_IMPATIENTLY;
    }

    // The player is talking to the elder in Goron Shrine as a non-Goron.
    return TEXT_EN_JG_WELCOME_TO_SPRING;
}

void EnJg_SpawnBreath(EnJg* this, GlobalContext* globalCtx) {
    s16 scale = (Rand_ZeroOne() * 20.0f) + 30.0f;

    if (globalCtx->state.frames % 8 == 0) {
        EffectSsIceSmoke_Spawn(globalCtx, &this->breathPos, &this->breathVelocity, &this->breathAccel, scale);
    }
}

/**
 * This function has two purposes:
 * - If the player starts talking to the elder, this stops him from moving, makes him face
 *   towards the player, updates certain weekEventRegs, and calls EnJg_SetupTalk.
 * - If the player is *not* talking to the elder, this decrements his freeze timer. If his
 *   freeze timer is 0 or negative, this function starts the process of freezing him before
 *   handing it off to EnJg_Freeze.
 */
void EnJg_CheckIfTalkingToPlayerAndHandleFreezeTimer(EnJg* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(sAnimations[this->animationIndex].animationSeg);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->flags |= FLAG_LOOKING_AT_PLAYER;
        this->actor.speedXZ = 0.0f;

        if (this->textId == TEXT_EN_JG_WHAT_WAS_I_DOING) {
            this->action = EN_JG_ACTION_FIRST_THAW;
        } else if (this->textId == TEXT_EN_JG_HAVE_YOU_SOME_BUSINESS_WITH_ELDER) {
            gSaveContext.weekEventReg[0x18] |= 0x20;
        } else if (this->textId == TEXT_EN_JG_HUNH) {
            gSaveContext.weekEventReg[0x18] |= 0x10;
        }

        func_801518B0(globalCtx, this->textId, &this->actor);
        this->actionFunc = EnJg_SetupTalk;
    } else {
        if ((this->actor.xzDistToPlayer < 100.0f) || (this->actor.isTargeted)) {
            func_800B863C(&this->actor, globalCtx);
            if (this->action == EN_JG_ACTION_FIRST_THAW) {
                this->textId = EnJg_GetStartingConversationTextId(this, globalCtx);
            }
        }

        this->freezeTimer--;
        if ((this->freezeTimer <= 0) && (currentFrame == lastFrame)) {
            this->animationIndex = EN_JG_ANIMATION_FROZEN_START;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            func_8019F1C0(&sSfxPos, NA_SE_EV_FREEZE_S);
            this->actionFunc = EnJg_Freeze;
        }
    }
}

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnJg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGoronElderSkel, &gGoronElderIdleAnim, this->jointTable,
                       this->morphTable, EN_JG_LIMB_MAX);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    Actor_SetScale(&this->actor, 0.01f);

    if (!EN_JG_IS_IN_GORON_SHRINE(thisx)) {
        if ((globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 7) &&
            (globalCtx->csCtx.unk_12 == 0)) {
            // This is the elder that appears in the cutscene for learning the full Goron Lullaby.
            this->animationIndex = EN_JG_ANIMATION_IDLE;
            this->action = EN_JG_ACTION_LULLABY_INTRO_CS;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_LullabyIntroCutsceneAction;
        } else {
            // This is the elder that appears in Mountain Village or the Path to Goron Village in winter.
            this->path = func_8013D648(globalCtx, EN_JG_GET_PATH(thisx), 0x3F);
            this->animationIndex = EN_JG_ANIMATION_SURPRISE_START;
            this->action = EN_JG_ACTION_SPAWNING;
            this->freezeTimer = 1000;
            this->textId = TEXT_EN_JG_WHAT_WAS_I_DOING;
            func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
            this->actionFunc = EnJg_Freeze;
        }
    } else {
        // This is the elder that appears in Goron Shrine in spring.
        this->animationIndex = EN_JG_ANIMATION_IDLE;
        this->cutscene = this->actor.cutscene;
        func_8013BC6C(&this->skelAnime, sAnimations, this->animationIndex);
        this->actionFunc = EnJg_GoronShrineIdle;
    }
}

void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnJg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    if ((this->actionFunc != EnJg_FrozenIdle) && (this->actionFunc != EnJg_EndFrozenInteraction)) {
        EnJg_UpdateCollision(this, globalCtx);
        Actor_MoveWithGravity(&this->actor);
        SkelAnime_Update(&this->skelAnime);

        if ((this->action != EN_JG_ACTION_LULLABY_INTRO_CS) && (!EN_JG_IS_IN_GORON_SHRINE(&this->actor))) {
            EnJg_SpawnBreath(this, globalCtx);
        }

        func_800E9250(globalCtx, &this->actor, &this->unusedRotation1, &this->unusedRotation2, this->actor.focus.pos);
    }
    this->actionFunc(this, globalCtx);
}

s32 EnJg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnJg* this = THIS;

    if (limbIndex == EN_JG_LIMB_ROOT) {
        if (this->flags & FLAG_LOOKING_AT_PLAYER) {
            Math_SmoothStepToS(&this->rootRotationWhenTalking, this->actor.yawTowardsPlayer - this->actor.shape.rot.y,
                               5, 0x1000, 0x100);
            Matrix_RotateY(this->rootRotationWhenTalking, MTXMODE_APPLY);
        } else {
            Math_SmoothStepToS(&this->rootRotationWhenTalking, 0, 5, 0x1000, 0x100);
            Matrix_RotateY(this->rootRotationWhenTalking, MTXMODE_APPLY);
        }
    }

    return false;
}

void EnJg_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnJg* this = THIS;

    if (limbIndex == EN_JG_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&sFocusOffset, &this->actor.focus.pos);
    }

    if (limbIndex == EN_JG_LIMB_LOWER_LIP) {
        Matrix_MultiplyVector3fByState(&sBreathPosOffset, &this->breathPos);
        Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
        Matrix_MultiplyVector3fByState(&sBreathVelOffset, &this->breathVelocity);
        Matrix_MultiplyVector3fByState(&sBreathAccelOffset, &this->breathAccel);
    }
}

void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnJg* this = THIS;

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnJg_OverrideLimbDraw, EnJg_PostLimbDraw, &this->actor);
}
