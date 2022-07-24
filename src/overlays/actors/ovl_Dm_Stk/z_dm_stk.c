/*
 * File: z_dm_stk.c
 * Overlay: ovl_Dm_Stk
 * Description: Skull Kid. Also manages Majora's Mask in the cutscene where its backstory is explained.
 *
 * This actor is responsible for some somewhat unintuitive things. For example, during certain cutscenes,
 * it is responsible for handling the player's sound effects as well. As another example, this actor makes
 * time pass when the player looks through the Astral Observatory telescope.
 */

#include "z_dm_stk.h"
#include "objects/object_stk2/object_stk2.h"
#include "objects/object_stk3/object_stk3.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((DmStk*)thisx)

void DmStk_Init(Actor* thisx, PlayState* play);
void DmStk_Destroy(Actor* thisx, PlayState* play);
void DmStk_Update(Actor* thisx, PlayState* play);
void DmStk_Draw(Actor* thisx, PlayState* play);

void DmStk_ClockTower_DoNothing(DmStk* this, PlayState* play);
void DmStk_DoNothing(DmStk* this, PlayState* play);
void DmStk_WaitForTelescope(DmStk* this, PlayState* play);
void DmStk_StartTelescopeCutscene(DmStk* this, PlayState* play);
void DmStk_ClockTower_StartIntroCutsceneVersion1(DmStk* this, PlayState* play);
void DmStk_ClockTower_WaitForIntroCutsceneVersion1ToEnd(DmStk* this, PlayState* play);
void DmStk_ClockTower_StartIntroCutsceneVersion2(DmStk* this, PlayState* play);
void DmStk_ClockTower_WaitForIntroCutsceneVersion2ToEnd(DmStk* this, PlayState* play);
void DmStk_ClockTower_StartDropOcarinaCutscene(DmStk* this, PlayState* play);
void DmStk_ClockTower_WaitForDropOcarinaCutsceneToEnd(DmStk* this, PlayState* play);
void DmStk_ClockTower_DeflectHit(DmStk* this, PlayState* play);
void DmStk_ClockTower_WaitForDeflectionToEnd(DmStk* this, PlayState* play);
void DmStk_ClockTower_IdleWithOcarina(DmStk* this, PlayState* play);
void DmStk_ClockTower_Idle(DmStk* this, PlayState* play);

typedef enum {
    /*  0 */ SK_ANIMATION_SHAKE_HEAD,
    /*  1 */ SK_ANIMATION_WALK,
    /*  2 */ SK_ANIMATION_LOOK_AROUND, // Not used in the final game
    /*  3 */ SK_ANIMATION_IDLE,
    /*  4 */ SK_ANIMATION_UNUSED_IDLE, // Unused duplicate of SK_ANIMATION_IDLE
    /*  5 */ SK_ANIMATION_BENT_OVER_HEAD_TWITCH,
    /*  6 */ SK_ANIMATION_GLITCHY_HORSE_RIDE_START, // Not used in the final game
    /*  7 */ SK_ANIMATION_RECLINING_FLOAT,
    /*  8 */ SK_ANIMATION_CURSE_START,
    /*  9 */ SK_ANIMATION_CURSE_LOOP,
    /* 10 */ SK_ANIMATION_LAUGH_START,
    /* 11 */ SK_ANIMATION_LAUGH_LOOP,
    /* 12 */ SK_ANIMATION_HIDE_OCARINA_START,
    /* 13 */ SK_ANIMATION_HIDE_OCARINA_LOOP,
    /* 14 */ SK_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING,
    /* 15 */ SK_ANIMATION_PLAY_OCARINA_AND_LAUGH,
    /* 16 */ SK_ANIMATION_PICK_UP_OCARINA, // Not used in the final game
    /* 17 */ SK_ANIMATION_LOOK_AT_OCARINA, // Not used in the final game
    /* 18 */ SK_ANIMATION_KICK_OVER_LINK,
    /* 19 */ SK_ANIMATION_SEARCH_LINK,
    /* 20 */ SK_ANIMATION_UNUSED_KICK_OVER_LINK, // Unused duplicate of SK_ANIMATION_KICK_OVER_LINK
    /* 21 */ SK_ANIMATION_UNUSED_SEARCH_LINK,    // Unused duplicate of SK_ANIMATION_SEARCH_LINK
    /* 22 */ SK_ANIMATION_HORSE_RIDE_START,
    /* 23 */ SK_ANIMATION_HORSE_RIDE_LOOP,
    /* 24 */ SK_ANIMATION_RAISE_MASK_START,
    /* 25 */ SK_ANIMATION_RAISE_MASK_LOOP,
    /* 26 */ SK_ANIMATION_LOWER_MASK,
    /* 27 */ SK_ANIMATION_JUMP_WHILE_HIDING_OCARINA,
    /* 28 */ SK_ANIMATION_HORSE_RIDE_AND_ROTATE, // Used when Link gets thrown off his horse
    /* 29 */ SK_ANIMATION_PLAY_OCARINA_WHILE_FLOATING,
    /* 30 */ SK_ANIMATION_FLOATING_TURN_AROUND,
    /* 31 */ SK_ANIMATION_OCARINA_JUGGLE,
    /* 32 */ SK_ANIMATION_CALL_DOWN_MOON_START,
    /* 33 */ SK_ANIMATION_CALL_DOWN_MOON_LOOP,
    /* 34 */ SK_ANIMATION_SMACK_FAIRY_START,
    /* 35 */ SK_ANIMATION_SMACK_FAIRY_LOOP,
    /* 36 */ SK_ANIMATION_HIT_BY_BUBBLE,
    /* 37 */ SK_ANIMATION_DROP_OCARINA,
    /* 38 */ SK_ANIMATION_FLOATING_ARMS_CROSSED,
    /* 39 */ SK_ANIMATION_DEFLECT_ATTACK,
    /* 40 */ SK_ANIMATION_TELESCOPE_LOOK_UP_START,
    /* 41 */ SK_ANIMATION_TELESCOPE_LOOK_UP_LOOP,
    /* 42 */ SK_ANIMATION_SURPRISE_START,
    /* 43 */ SK_ANIMATION_SURPRISE_LOOP,
    /* 44 */ SK_ANIMATION_LOOK_AROUND_FOR_GIANTS_START,
    /* 45 */ SK_ANIMATION_LOOK_AROUND_FOR_GIANTS_LOOP,
    /* 46 */ SK_ANIMATION_HOLD_HEAD_AND_SHAKE_START,
    /* 47 */ SK_ANIMATION_HOLD_HEAD_AND_SHAKE_LOOP,
    /* 48 */ SK_ANIMATION_HOLD_HEAD_AND_SCREAM_START,
    /* 49 */ SK_ANIMATION_HOLD_HEAD_AND_SCREAM_LOOP,
    /* 50 */ SK_ANIMATION_HUDDLE_WITH_FAIRIES,
    /* 51 */ SK_ANIMATION_SEARCH_MASK_SALESMAN,
    /* 52 */ SK_ANIMATION_HOLD_UP_MASK_START,
    /* 53 */ SK_ANIMATION_HOLD_UP_MASK_LOOP,
    /* 54 */ SK_ANIMATION_SHIVER,
    /* 55 */ SK_ANIMATION_DRAW,
    /* 56 */ SK_ANIMATION_BENT_OVER_LOOK_UP,
    /* 57 */ SK_ANIMATION_SPANK,
    /* 58 */ SK_ANIMATION_HIP_SHAKE_AND_JUMP,
    /* 59 */ SK_ANIMATION_PLAY_FLUTE,
    /* 60 */ SK_ANIMATION_CARTWHEEL,
    /* 61 */ SK_ANIMATION_LIE_FLAT,
    /* 62 */ SK_ANIMATION_DANGLE_FROM_MASK_START,
    /* 63 */ SK_ANIMATION_DANGLE_FROM_MASK_LOOP,
    /* 64 */ SK_ANIMATION_DROPPED_FROM_MASK,
    /* 65 */ SK_ANIMATION_LOOK_UP_AT_GIANTS,
    /* 66 */ SK_ANIMATION_ASHAMED_START,
    /* 67 */ SK_ANIMATION_ASHAMED_LOOP,
    /* 68 */ SK_ANIMATION_LOOK_LEFT_START,
    /* 69 */ SK_ANIMATION_LOOK_LEFT_LOOP,
    /* 70 */ SK_ANIMATION_SNIFF,
    /* 71 */ SK_ANIMATION_LAUGH_AFTER_SNIFF,
} SkullKidAnimationIndex;

typedef enum {
    /* 0 */ SK_MASK_TYPE_NO_MASK,
    /* 1 */ SK_MASK_TYPE_NORMAL,
    /* 2 */ SK_MASK_TYPE_GLOWING_EYES,
    /* 3 */ SK_MASK_TYPE_FADING_OUT,
    /* 9 */ SK_MASK_TYPE_RAISED = 9,
} SkullKidMaskType;

typedef enum {
    /* 0 */ SK_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE,
    /* 1 */ SK_HAND_TYPE_HOLDING_LINK_MASK,
    /* 2 */ SK_HAND_TYPE_HOLDING_MAJORAS_MASK,
    /* 3 */ SK_HAND_TYPE_HOLDING_OCARINA,
    /* 4 */ SK_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA,
    /* 5 */ SK_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE,
    /* 6 */ SK_HAND_TYPE_HOLDING_FLUTE,
    /* 9 */ SK_HAND_TYPE_DEFAULT = 9,
} SkullKidHandType;

typedef enum {
    /* 0 */ SK_FADE_IN_STATE_NONE,
    /* 1 */ SK_FADE_IN_STATE_START,
    /* 2 */ SK_FADE_IN_STATE_INCREASE_FOG,
    /* 3 */ SK_FADE_IN_STATE_INCREASE_ALPHA,
} SkullKidFadeInState;

typedef enum {
    /* 0 */ SK_FADE_OUT_STATE_NONE,
    /* 1 */ SK_FADE_OUT_STATE_FADING_OUT,
} SkullKidFadeOutState;

typedef enum {
    /* 0 */ SK_DEKU_PIPES_CS_STATE_NOT_READY,
    /* 1 */ SK_DEKU_PIPES_CS_STATE_READY,
    /* 2 */ SK_DEKU_PIPES_CS_STATE_PLAYER_USED_OCARINA,
    /* 3 */ SK_DEKU_PIPES_CS_STATE_START,
    /* 4 */ SK_DEKU_PIPES_CS_STATE_END
} SkullKidDekuPipesCutsceneState;

const ActorInit Dm_Stk_InitVars = {
    ACTOR_DM_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmStk),
    (ActorFunc)DmStk_Init,
    (ActorFunc)DmStk_Destroy,
    (ActorFunc)DmStk_Update,
    (ActorFunc)DmStk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 14, 38, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(1, 0xF),
    /* Light ray      */ DMG_ENTRY(1, 0xF),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0xF),
    /* Unblockable    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static AnimationInfo sAnimations[] = {
    { &gSkullKidShakeHeadAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidWalkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLookAroundAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidIdleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidIdleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidBentOverHeadTwitchAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidGlitchyHorseRideStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidRecliningFloatAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidCurseStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidCurseLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLaughStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLaughLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHideOcarinaStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHideOcarinaLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidPickUpOcarinaAndStartPlayingAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidPlayOcarinaAndLaughAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidPickUpOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookAtOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidKickOverLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSearchLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidKickOverLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSearchLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHorseRideStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHorseRideLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidRaiseMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidRaiseMaskLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLowerMaskAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidJumpWhileHidingOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHorseRideAndRotateAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidPlayOcarinaWhileFloatingAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidFloatingTurnAroundAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidOcarinaJuggleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidCallDownMoonStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidCallDownMoonLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSmackFairyStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSmackFairyLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHitByBubbleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDropOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidFloatingArmsCrossedAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidDeflectAttackAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidTelescopeLookUpStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidTelescopeLookUpLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSurpriseStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSurpriseLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLookAroundForGiantsStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookAroundForGiantsLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHoldHeadAndShakeStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHoldHeadAndShakeLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHoldHeadAndScreamStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHoldHeadAndScreamLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHuddleWithFairiesAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSearchMaskSalesmanAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHoldUpMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHoldUpMaskLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidShiverAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidDrawAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidBentOverLookUpAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSpankAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHipShakeAndJumpAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidPlayFluteAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidCartwheelAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDangleFromMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDangleFromMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDangleFromMaskLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidDroppedFromMaskAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookUpAtGiantsAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidAshamedStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidAshamedLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLookLeftStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookLeftLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSniffAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLaughAfterSniffAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
};

/**
 * Ensures the correct object for the current animation is in segment 6.
 */
void DmStk_LoadObjectForAnimation(DmStk* this, PlayState* play) {
    s32 objectIndex;

    if (((this->animIndex >= SK_ANIMATION_SHAKE_HEAD) && (this->animIndex <= SK_ANIMATION_BENT_OVER_HEAD_TWITCH)) ||
        (this->animIndex == SK_ANIMATION_CALL_DOWN_MOON_START) ||
        (this->animIndex == SK_ANIMATION_CALL_DOWN_MOON_LOOP) ||
        (this->animIndex == SK_ANIMATION_TELESCOPE_LOOK_UP_START) ||
        (this->animIndex == SK_ANIMATION_TELESCOPE_LOOK_UP_LOOP)) {
        objectIndex = this->objectStkObjectIndex;
    } else if (this->animIndex >= SK_ANIMATION_LOOK_UP_AT_GIANTS) {
        objectIndex = this->objectStk3ObjectIndex;
    } else {
        objectIndex = this->objectStk2ObjectIndex;
    }

    if (objectIndex >= 0) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(play->objectCtx.status[objectIndex].segment);
    }
}

/**
 * This function is always called with unusedExtraOffset = 0.
 */
void DmStk_ChangeAnimation(DmStk* this, PlayState* play, SkelAnime* skelAnime, AnimationInfo* animation,
                           u16 unusedExtraOffset) {
    DmStk_LoadObjectForAnimation(this, play);

    animation += unusedExtraOffset;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame,
                     (animation->frameCount < 0.0f) ? Animation_GetLastFrame(&animation->animation->common)
                                                    : animation->frameCount,
                     animation->mode, animation->morphFrames);
}

/**
 * Handles sound effects for the first part of the intro cutscene, i.e., the cutscene
 * that starts when the player start a new game and ends when the screen fades to white
 * after Skull Kid steals Epona.
 */
void DmStk_PlaySfxForIntroCutsceneFirstPart(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames + 20) {
        case 1195:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
            break;

        case 1232:
        case 1241:
        case 1252:
        case 1255:
        case 1257:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;

        case 1285:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;

        case 1343:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 1410:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            break;

        case 1603:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_WALK);
            break;

        case 1610:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_REVERSE);
            break;

        case 2095:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SURPRISED);
            break;

        case 2190:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_JUMP);
            break;

        case 2212:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;

        case 2214:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL02_LAUGH_SHORT);
            break;

        case 2250:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL06_SURPRISED);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
            break;

        case 2255:
        case 2266:
        case 2277:
        case 2288:
        case 2299:
        case 2310:
        case 2321:
        case 2332:
        case 2343:
        case 2354:
        case 2365:
        case 2376:
        case 2387:
        case 2398:
        case 2409:
        case 2420:
        case 2431:
        case 2442:
        case 2453:
        case 2464:
        case 2475:
        case 2486:
        case 2497:
        case 2508:
        case 2519:
        case 2530:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;
    }
}

/**
 * This is supposed to play a bell sound in the title cutscene where the Skull Kid is
 * looking at the moon on top of the Clock Tower. However, it doesn't actually play
 * any sound in-game, since all sound effects are muted when it plays.
 */
void DmStk_PlaySfxForTitleCutscene(DmStk* this, PlayState* play) {
    if (play->csCtx.frames == 535) {
        func_8019F128(NA_SE_EV_CLOCK_TOWER_BELL);
    }
}

/**
 * Handles sound effects for the second part of the intro cutscene, i.e., the cutscene
 * that starts after the fade-to-white and ends when the player gains control.
 */
void DmStk_PlaySfxForIntroCutsceneSecondPart(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 78:
        case 89:
        case 100:
        case 111:
        case 122:
        case 133:
        case 144:
        case 155:
        case 166:
        case 177:
        case 188:
        case 199:
        case 210:
        case 221:
        case 232:
        case 243:
        case 254:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 173:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;
    }
}

/**
 * Handles sound effects for the cutscene where Skull Kid steals Majora's Mask from
 * the Happy Mask Salesman.
 */
void DmStk_PlaySfxForObtainingMajorasMaskCutscene(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 18:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_GASAGOSO);
            break;

        case 90:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            break;

        case 142:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EVIL_POWER);
            break;
    }
}

/**
 * Handles sound effects for the first part of the curse cutscene, i.e., the cutscene
 * that starts when Link falls down the large hole and ends with a fade-to-black to
 * the hallucinatory Deku Scrubs scene.
 */
void DmStk_PlaySfxForCurseCutsceneFirstPart(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 415:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 100);
            break;

        case 785:
            func_8019F128(NA_SE_SY_STALKIDS_PSYCHO);
            func_8019FE74(&gSfxVolume, 0.0f, 150);
            break;

        case 560:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL02_LAUGH_SHORT);
            break;

        case 890:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL21_PSYCHO_VOICE);
            break;
    }
}

/**
 * Handles sound effects for the second part of the curse cutscene, i.e., the cutscene
 * that starts once the hallucinatory Deku Scrubs scene is over and ends when the player
 * gains control.
 */
void DmStk_PlaySfxForCurseCutsceneSecondPart(DmStk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (play->csCtx.frames) {
        case 10:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 50);
            break;

        case 71:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_BODY);
            break;

        case 365:
            func_801A0654(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 0);
            break;

        case 650:
            func_8019FE74(&gSfxVolume, 0.0f, 80);
            break;

        case 265:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;

        case 126:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_150);
            break;

        case 197:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_134);
            break;

        case 207:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_135);
            break;

        case 217:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_136);
            break;
    }

    if (player) {}

    if ((play->csCtx.frames >= 263) && (play->csCtx.frames < 698)) {
        Actor_PlaySfxAtPos(&player->actor, NA_SE_EN_STALKIDS_BODY_LEV - SFX_FLAG);
    }
}

/**
 * Handles sound effects for the intro cutscene at the top of the Clock Tower. Specifically,
 * it handles the variation of the cutscene that plays the first time the player reaches the
 * top of the Clock Tower, which is slightly longer.
 */
void DmStk_PlaySfxForClockTowerIntroCutsceneVersion1(DmStk* this, PlayState* play) {
    static s32 sMoonCallTimer = 0;

    switch (play->csCtx.frames) {
        case 140:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 80);
            break;

        case 258:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_TURN);
            break;

        case 524:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_TURN);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL04_ANGER);
            break;

        case 534:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_ROLL);
            break;

        case 678:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_STRETCH);
            break;
    }

    if ((this->animIndex == SK_ANIMATION_OCARINA_JUGGLE) && (play->csCtx.frames < 700)) {
        if (Animation_OnFrame(&this->skelAnime, 5.0f) || Animation_OnFrame(&this->skelAnime, 25.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_OTEDAMA1);
        } else if (Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 40.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_OTEDAMA2);
        }
    }

    if (play->csCtx.frames >= 700) {
        if (sMoonCallTimer < 128) {
            if ((sMoonCallTimer & 0x1F) == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON);
            } else if ((sMoonCallTimer & 0x1F) == 16) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON2);
            }

            sMoonCallTimer++;
        }
    } else {
        sMoonCallTimer = 0;
    }
}

/**
 * Handles sound effects for the cutscene where Skull Kid drops the Ocarina of Time.
 */
void DmStk_PlaySfxForDroppingOcarinaCutscene(DmStk* this, PlayState* play) {
    if (play->csCtx.frames == 3) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL06_SURPRISED);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
    }
}

/**
 * Handles sound effects for the cutscene where Skull Kid is shivering in the rain.
 */
void DmStk_PlaySfxForShiveringInRainCutscene(DmStk* this, PlayState* play) {
    if ((play->csCtx.frames >= 642) && (play->csCtx.frames < 845)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_NE_STAL23_COLD - SFX_FLAG);
    }
}

/**
 * Handles sound effects for the cutscene where Skull Kid is playing with Tatl and Tael
 * in Termina Field.
 */
void DmStk_PlaySfxForPlayingWithFairiesCutscene(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 58:
        case 61:
        case 68:
        case 72:
        case 77:
        case 79:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_WALK_WATER2);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_WALK);
            break;

        case 186:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
            break;

        case 230:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL22_LAUGH_KID_L);
            break;
    }
}

/**
 * Handles sound effects for the first part of the ending cutscene, i.e., the cutscene
 * that starts after the Dawn of the New Day screen and ends with a fade to black as
 * the Giants are walking away.
 */
void DmStk_PlaySfxForEndingCutsceneFirstPart(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 5:
            func_801A4A28(12);
            break;

        case 660:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;
    }
}

/**
 * Handles sound effects for the second part of the ending cutscene, i.e., the cutscene
 * that starts after a fade-to-black and ends after the credits start.
 */
void DmStk_PlaySfxForEndingCutsceneSecondPart(DmStk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (play->csCtx.frames) {
        case 5:
            func_801A4A28(12);
            break;

        case 45:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 93:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 245:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 269:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL11_LAUGH_SHY2);
            break;

        case 327:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;

        case 455:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 1730:
            Audio_QueueSeqCmd(0x141400FF);
            break;

        case 1395:
            func_800B8E58(player, NA_SE_VO_DUMMY_34);
            break;

        case 1850:
            Audio_QueueSeqCmd(0x42320000);
            break;

        case 2000:
            func_801A5BD0(0x7F);
            break;
    }

    if (this->animIndex == SK_ANIMATION_SHAKE_HEAD) {
        if (Animation_OnFrame(&this->skelAnime, 8.0f) || Animation_OnFrame(&this->skelAnime, 17.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
        }

        if (Animation_OnFrame(&this->skelAnime, 28.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
        }
    } else if (this->animIndex == SK_ANIMATION_LAUGH_AFTER_SNIFF) {
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f) ||
            Animation_OnFrame(&this->skelAnime, 12.0f) || Animation_OnFrame(&this->skelAnime, 18.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
        }
    } else if ((this->animIndex == SK_ANIMATION_SNIFF) &&
               (Animation_OnFrame(&this->skelAnime, 16.0f) || Animation_OnFrame(&this->skelAnime, 23.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_NOSE);
    }
}

/**
 * Handles sound effects for the intro cutscene at the top of the Clock Tower. Specifically,
 * it handles the variation of the cutscene that plays the second or later time the player
 * reaches the top of the Clock Tower, which is slightly shorter.
 */
void DmStk_PlaySfxForClockTowerIntroCutsceneVersion2(DmStk* this, PlayState* play) {
    static s32 sMoonCallTimer = 0;

    switch (play->csCtx.frames) {
        case 40:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 80);
            break;

        case 234:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_TURN);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL04_ANGER);
            break;

        case 244:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_ROLL);
            break;

        case 388:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_STRETCH);
            break;
    }

    if (play->csCtx.frames >= 408) {
        if (sMoonCallTimer < 128) {
            if ((sMoonCallTimer & 0x1F) == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON);
            } else if ((sMoonCallTimer & 0x1F) == 16) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON2);
            }

            sMoonCallTimer++;
        }
    } else {
        sMoonCallTimer = 0;
    }
}

/**
 * Handles sound effects for the cutscene that plays after the player plays the
 * Oath to Order at the top of the Clock Tower.
 */
void DmStk_PlaySfxForCutsceneAfterPlayingOathToOrder(DmStk* this, PlayState* play) {
    this->oathToOrderCutsceneVoicePos.x = this->actor.projectedPos.x;
    this->oathToOrderCutsceneVoicePos.y = this->actor.projectedPos.y;
    this->oathToOrderCutsceneVoicePos.z = this->actor.projectedPos.z;

    switch (play->csCtx.frames) {
        case 64:
            Audio_PlaySfxAtPos(&this->oathToOrderCutsceneVoicePos, NA_SE_EN_STAL06_SURPRISED);
            break;

        case 327:
        case 332:
        case 335:
        case 344:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 367:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_BODY_LEV);
            break;

        case 470:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_HEADACHE);
            break;

        case 486:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            Audio_PlaySfxAtPos(&this->oathToOrderCutsceneVoicePos, NA_SE_EN_STAL08_CRY_BIG);
            break;

        case 496:
            Audio_PlaySfxAtPos(&this->oathToOrderCutsceneVoicePos, NA_SE_EN_STAL09_SCREAM);
            break;

        case 590:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 592:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 594:
            Audio_PlaySfxAtPos(&this->oathToOrderCutsceneVoicePos, NA_SE_EN_STAL24_SCREAM2);
            break;
    }

    if (1) {}

    if ((play->csCtx.frames >= 62) && (play->csCtx.frames < 273)) {
        if ((Rand_ZeroOne() < 0.75f) && ((play->state.frames % 2) != 0)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_EARTHQUAKE);
        }
    }

    if ((play->csCtx.frames >= 498) && (play->csCtx.frames < 577)) {
        if ((play->state.frames % 4) == 0) {
            if ((play->state.frames & 4) != 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_BODY_LEV);
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            }
        }
    }

    if (play->csCtx.frames >= 290) {
        func_8019F128(NA_SE_EV_KYOJIN_VOICE_SUCCESS - SFX_FLAG);
    }
}

/**
 * Handles sound effects for the cutscene before the player warps to the moon. Specifically,
 * it handles the variation of the cutscene that plays the first time the player warps to the
 * moon, which is slightly longer.
 */
void DmStk_PlaySfxForMoonWarpCutsceneVersion1(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 551:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_PULLED);
            break;

        case 711:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 716:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;
    }
}

/**
 * Handles sound effects for the cutscene before the player warps to the moon. Specifically,
 * it handles the variation of the cutscene that plays the second or later time the player
 * warps to the moon, which is slightly shorter.
 */
void DmStk_PlaySfxForMoonWarpCutsceneVersion2(DmStk* this, PlayState* play) {
    switch (play->csCtx.frames) {
        case 311:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_PULLED);
            break;

        case 365:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 372:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;
    }
}

/**
 * Handles sound effects for all cutscenes.
 */
void DmStk_PlaySfxForCutscenes(DmStk* this, PlayState* play) {
    if (play->csCtx.state != 0) {
        switch (play->sceneNum) {
            case SCENE_LOST_WOODS:
                if (gSaveContext.sceneSetupIndex == 1) {
                    DmStk_PlaySfxForIntroCutsceneFirstPart(this, play);
                } else if (gSaveContext.sceneSetupIndex == 0) {
                    DmStk_PlaySfxForIntroCutsceneSecondPart(this, play);
                } else if ((gSaveContext.sceneSetupIndex == 2) && (play->csCtx.currentCsIndex == 0)) {
                    DmStk_PlaySfxForObtainingMajorasMaskCutscene(this, play);
                }
                break;

            case SCENE_CLOCKTOWER:
                if (gSaveContext.sceneSetupIndex == 1) {
                    DmStk_PlaySfxForTitleCutscene(this, play);
                }
                break;

            case SCENE_OPENINGDAN:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (play->csCtx.currentCsIndex == 0) {
                        DmStk_PlaySfxForCurseCutsceneFirstPart(this, play);
                    } else if (play->csCtx.currentCsIndex == 1) {
                        DmStk_PlaySfxForCurseCutsceneSecondPart(this, play);
                    }
                }
                break;

            case SCENE_OKUJOU:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (play->csCtx.currentCsIndex == 0) {
                        DmStk_PlaySfxForClockTowerIntroCutsceneVersion1(this, play);
                    } else if (play->csCtx.currentCsIndex == 1) {
                        DmStk_PlaySfxForDroppingOcarinaCutscene(this, play);
                    } else if (play->csCtx.currentCsIndex == 2) {
                        DmStk_PlaySfxForClockTowerIntroCutsceneVersion2(this, play);
                    } else if (play->csCtx.currentCsIndex == 3) {
                        DmStk_PlaySfxForCutsceneAfterPlayingOathToOrder(this, play);
                    }
                } else if (gSaveContext.sceneSetupIndex == 2) {
                    if (play->csCtx.currentCsIndex == 0) {
                        DmStk_PlaySfxForMoonWarpCutsceneVersion1(this, play);
                    } else if (play->csCtx.currentCsIndex == 1) {
                        DmStk_PlaySfxForMoonWarpCutsceneVersion2(this, play);
                    }
                }
                break;

            case SCENE_00KEIKOKU:
                if (gSaveContext.sceneSetupIndex == 3) {
                    if (play->csCtx.currentCsIndex == 0) {
                        DmStk_PlaySfxForShiveringInRainCutscene(this, play);
                    } else if (play->csCtx.currentCsIndex == 2) {
                        DmStk_PlaySfxForPlayingWithFairiesCutscene(this, play);
                    }
                } else if (gSaveContext.sceneSetupIndex == 7) {
                    if (play->csCtx.currentCsIndex == 0) {
                        DmStk_PlaySfxForEndingCutsceneFirstPart(this, play);
                    } else if (play->csCtx.currentCsIndex == 1) {
                        DmStk_PlaySfxForEndingCutsceneSecondPart(this, play);
                    }
                }
                break;
        }
    }

    if (this->animIndex == SK_ANIMATION_WALK) {
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_WALK);
        }
    } else if (this->animIndex == SK_ANIMATION_SEARCH_LINK) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 13.0f) ||
            Animation_OnFrame(&this->skelAnime, 20.0f) || Animation_OnFrame(&this->skelAnime, 27.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_CALM_HIT);
        }
    } else if (this->animIndex == SK_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING) {
        if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_PUT_OUT_ITEM);
        }
    } else if (this->animIndex == SK_ANIMATION_PLAY_OCARINA_AND_LAUGH) {
        if (Animation_OnFrame(&this->skelAnime, 14.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_UNSKILLFUL_OCARINA);
        }

        if (Animation_OnFrame(&this->skelAnime, 45.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL01_LAUGH);
        }
    }
}

void DmStk_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    DmStk* this = THIS;

    this->shouldDraw = true;
    if (DM_STK_GET_TYPE(&this->actor) != DM_STK_TYPE_MAJORAS_MASK) {
        this->dekuPipesCutsceneState = SK_DEKU_PIPES_CS_STATE_NOT_READY;
        this->objectStkObjectIndex = Object_GetIndex(&play->objectCtx, OBJECT_STK);
        this->objectStk2ObjectIndex = Object_GetIndex(&play->objectCtx, OBJECT_STK2);
        this->objectStk3ObjectIndex = Object_GetIndex(&play->objectCtx, OBJECT_STK3);
        if (this->objectStkObjectIndex < 0) {
            Actor_MarkForDeath(&this->actor);
        }

        this->tatlMessageTimer = 0;
        this->deflectCount = 0;
        this->maskType = SK_MASK_TYPE_NORMAL;
        this->animIndex = SK_ANIMATION_IDLE;
        this->fogR = play->lightCtx.unk7;
        this->fogG = play->lightCtx.unk8;
        this->fogB = play->lightCtx.unk9;

        if ((play->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1)) {
            this->alpha = 0;
            this->fogN = 0;
            this->fogF = 1000;
            this->fogScale = 1.0f;
            this->actionFunc = DmStk_DoNothing;
        } else if (play->sceneNum == SCENE_OKUJOU) {
            this->alpha = 255;
            this->fogN = 996;
            this->fogF = 1000;
            this->fogScale = 0.7f;
            this->hasBeenHit = false;

            Collider_InitCylinder(play, &this->collider);

            if (gSaveContext.save.entranceIndex == 0x2C00) {
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (gSaveContext.unk_3DD0[3] == 0) {
                        // Starts a 5 minute (300 second) timer until the moon falls.
                        func_8010E9F0(3, 300);
                        XREG(80) = 200;
                        XREG(81) = 115;
                    }

                    if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                        sCylinderInit.base.colType = COLTYPE_WOOD;
                        this->actionFunc = DmStk_ClockTower_StartIntroCutsceneVersion1;
                    } else {
                        sCylinderInit.base.colType = COLTYPE_WOOD;
                        this->actionFunc = DmStk_ClockTower_StartIntroCutsceneVersion2;
                    }

                } else if (gSaveContext.sceneSetupIndex == 3) {
                    this->animIndex = SK_ANIMATION_FLOATING_ARMS_CROSSED;
                    if (gSaveContext.unk_3DD0[3] == 0) {
                        // This code is called when the Giants fail to stop the moon.
                        // Starts a 1 minute (60 second) timer until the moon falls.
                        func_8010E9F0(3, 60);
                        XREG(80) = 200;
                        XREG(81) = 115;
                    }

                    this->actor.world.pos.y = 120.0f;
                    sCylinderInit.base.colType = COLTYPE_WOOD;
                    this->actionFunc = DmStk_ClockTower_Idle;
                } else {
                    this->animIndex = SK_ANIMATION_FLOATING_ARMS_CROSSED;
                    this->actionFunc = DmStk_ClockTower_DoNothing;
                }
            } else {
                this->dekuPipesCutsceneState = SK_DEKU_PIPES_CS_STATE_READY;
                this->animIndex = SK_ANIMATION_FLOATING_ARMS_CROSSED;
                this->actor.world.pos.y = 120.0f;
                sCylinderInit.base.colType = COLTYPE_WOOD;
                this->actionFunc = DmStk_ClockTower_Idle;
            }

            Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
            CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

        } else if ((play->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 0)) {
            if (!(play->actorCtx.unk5 & 2)) {
                Actor_MarkForDeath(&this->actor);
            }

            this->maskType = SK_MASK_TYPE_GLOWING_EYES;
            this->alpha = 255;
            this->fogN = 996;
            this->fogF = 1000;
            this->fogScale = 0.7f;
            this->animIndex = SK_ANIMATION_BENT_OVER_HEAD_TWITCH;
            this->actionFunc = DmStk_WaitForTelescope;
        } else {
            if ((play->sceneNum == SCENE_LOST_WOODS) && !Cutscene_IsPlaying(play)) {
                Actor_MarkForDeath(&this->actor);
            }

            this->maskType = SK_MASK_TYPE_GLOWING_EYES;
            this->alpha = 255;
            this->fogN = 996;
            this->fogF = 1000;
            this->fogScale = 0.7f;
            this->actionFunc = DmStk_DoNothing;
        }

        this->handType = SK_HAND_TYPE_DEFAULT;
        this->fadeInState = SK_FADE_IN_STATE_NONE;
        this->fadeOutState = SK_FADE_OUT_STATE_NONE;
        this->fadeOutTimer = 0;
        this->alpha = this->alpha;
        this->actor.targetArrowOffset = 1100.0f;
        this->csAction = 99;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gSkullKidSkel, NULL, NULL, NULL, 0);
        DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
    }

    Actor_SetScale(&this->actor, 0.01f);

    if ((play->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 3) &&
        (play->csCtx.currentCsIndex > 0)) {
        play->envCtx.unk_17 = 15;
        play->envCtx.unk_18 = 15;
    }
}

void DmStk_Destroy(Actor* thisx, PlayState* play) {
}

void DmStk_ClockTower_DoNothing(DmStk* this, PlayState* play) {
}

void DmStk_DoNothing(DmStk* this, PlayState* play) {
}

/**
 * Waits around until the player zooms the telescope in on Skull Kid,
 * then starts the telescope cutscene.
 */
void DmStk_WaitForTelescope(DmStk* this, PlayState* play) {
    Vec3f screenPos;

    if (!(gSaveContext.save.weekEventReg[74] & 0x20)) {
        func_80169474(play, &this->actor.world.pos, &screenPos);
        if (play->view.fovy < 25.0f) {
            if ((screenPos.x >= 70.0f) && (screenPos.x < 250.0f) && (screenPos.y >= 30.0f) && (screenPos.y < 210.0f)) {
                func_800FE484();
                this->actionFunc = DmStk_StartTelescopeCutscene;
            }
        }
    }
}

/**
 * Plays the cutscene in the telescope where the Moon's Tear falls.
 */
void DmStk_StartTelescopeCutscene(DmStk* this, PlayState* play) {
    s16 dayOneAndTwoCutscene = this->actor.cutscene;
    s16 dayThreeCutscene = ActorCutscene_GetAdditionalCutscene(dayOneAndTwoCutscene);
    s16 finalHoursCutscene = ActorCutscene_GetAdditionalCutscene(dayThreeCutscene);
    s16 cutscene;

    if (gSaveContext.save.day < 3) {
        cutscene = dayOneAndTwoCutscene;
    } else if ((gSaveContext.save.weekEventReg[8] & 0x40) ||
               ((CURRENT_DAY == 3) && (gSaveContext.save.time < CLOCK_TIME(6, 0)))) {
        cutscene = finalHoursCutscene;
    } else {
        cutscene = dayThreeCutscene;
    }

    if (ActorCutscene_GetCanPlayNext(cutscene)) {
        ActorCutscene_Start(cutscene, &this->actor);
        func_800FE498();
        this->actionFunc = DmStk_DoNothing;
    } else {
        ActorCutscene_SetIntentToPlay(cutscene);
    }
}

void DmStk_ClockTower_StartIntroCutsceneVersion1(DmStk* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(9)) {
        ActorCutscene_Start(9, &this->actor);
        this->actionFunc = DmStk_ClockTower_WaitForIntroCutsceneVersion1ToEnd;
    } else {
        ActorCutscene_SetIntentToPlay(9);
    }
}

void DmStk_ClockTower_WaitForIntroCutsceneVersion1ToEnd(DmStk* this, PlayState* play) {
    if (play->csCtx.state == 0) {
        this->animIndex = SK_ANIMATION_CALL_DOWN_MOON_LOOP;
        this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
        DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
        this->actionFunc = DmStk_ClockTower_IdleWithOcarina;
    }
}

void DmStk_ClockTower_StartIntroCutsceneVersion2(DmStk* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(11)) {
        ActorCutscene_Start(11, &this->actor);
        this->actionFunc = DmStk_ClockTower_WaitForIntroCutsceneVersion2ToEnd;
    } else {
        ActorCutscene_SetIntentToPlay(11);
    }
}

void DmStk_ClockTower_WaitForIntroCutsceneVersion2ToEnd(DmStk* this, PlayState* play) {
    if (play->csCtx.state == 0) {
        this->animIndex = SK_ANIMATION_FLOATING_ARMS_CROSSED;
        DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
        this->actionFunc = DmStk_ClockTower_Idle;
    }
}

void DmStk_ClockTower_StartDropOcarinaCutscene(DmStk* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(10)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DAMAGE);
        ActorCutscene_Start(10, &this->actor);
        this->actor.shape.rot.x = 0;
        this->actor.world.rot.x = this->actor.shape.rot.x;
        this->actor.shape.rot.y = this->actor.shape.rot.x;
        this->actor.world.rot.y = this->actor.shape.rot.x;
        this->actionFunc = DmStk_ClockTower_WaitForDropOcarinaCutsceneToEnd;
    } else {
        ActorCutscene_SetIntentToPlay(10);
    }
}

void DmStk_ClockTower_WaitForDropOcarinaCutsceneToEnd(DmStk* this, PlayState* play) {
    if ((play->csCtx.state != 0) && (play->csCtx.frames > 20)) {
        this->actionFunc = DmStk_ClockTower_Idle;
    }
}

/**
 * Makes Skull Kid bob up and down and face the player.
 */
void DmStk_ClockTower_AdjustHeightAndRotation(DmStk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 sin;

    this->bobPhase += 0x4B0;
    sin = Math_SinS(this->bobPhase) * 10.0f;
    Math_SmoothStepToF(&this->actor.world.pos.y, 160.0f + sin, 0.2f, 1.0f, 0.0001f);

    this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, &player->actor);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    this->actor.world.rot.x = 0x1B58;
    this->actor.shape.rot.x = this->actor.world.rot.x;
}

/**
 * Starts the deflection animation and, depending on how many times Skull Kid has been hit,
 * prints a message taunting the player.
 */
void DmStk_ClockTower_DeflectHit(DmStk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    DmStk_ClockTower_AdjustHeightAndRotation(this, play);
    this->deflectCount++;
    if (this->deflectCount >= 3) {
        this->deflectCount = 0;
        if (!(player->stateFlags2 & 0x8000000)) {
            // That won't do you any good
            Message_StartTextbox(play, 0x2013, &this->actor);
        }
    }

    this->animIndex = SK_ANIMATION_DEFLECT_ATTACK;
    DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
    this->actionFunc = DmStk_ClockTower_WaitForDeflectionToEnd;
}

/**
 * Resets Skull Kid back to his idle state once the deflection animation ends.
 * If he is hit again before the animation ends, this function will make his deflection restart.
 */
void DmStk_ClockTower_WaitForDeflectionToEnd(DmStk* this, PlayState* play) {
    DmStk_ClockTower_AdjustHeightAndRotation(this, play);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->animIndex = SK_ANIMATION_FLOATING_ARMS_CROSSED;
        DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
        this->actionFunc = DmStk_ClockTower_Idle;
    }

    if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
        this->actionFunc = DmStk_ClockTower_DeflectHit;
    }
}

/**
 * Updates a variety of states based on Skull Kid's current cutscene, including his current
 * animation, his hand/mask type, his fade in/fade out state, and his current cutscene action.
 */
void DmStk_UpdateCutscenes(DmStk* this, PlayState* play) {
    s32 pad;
    s32 actorActionIndex;

    if (Cutscene_CheckActorAction(play, 107)) {
        actorActionIndex = Cutscene_GetActorActionIndex(play, 107);

        if (play->csCtx.frames == play->csCtx.actorActions[actorActionIndex]->startFrame) {
            if (this->csAction != play->csCtx.actorActions[actorActionIndex]->action) {
                this->csAction = play->csCtx.actorActions[actorActionIndex]->action;
                if (play->sceneNum == SCENE_CLOCKTOWER) {
                    this->handType = SK_HAND_TYPE_HOLDING_FLUTE;
                } else {
                    this->handType = SK_HAND_TYPE_DEFAULT;
                }

                switch (play->csCtx.actorActions[actorActionIndex]->action) {
                    case 0:
                    case 1:
                        this->animIndex = SK_ANIMATION_IDLE;
                        break;

                    case 2:
                        this->animIndex = SK_ANIMATION_WALK;
                        break;

                    case 3:
                        this->animIndex = SK_ANIMATION_UNUSED_KICK_OVER_LINK;
                        break;

                    case 4:
                        this->animIndex = SK_ANIMATION_KICK_OVER_LINK;
                        break;

                    case 6:
                        this->animIndex = SK_ANIMATION_PICK_UP_OCARINA;
                        this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 7:
                        this->animIndex = SK_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING;
                        this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 8:
                        this->animIndex = SK_ANIMATION_SHAKE_HEAD;
                        break;

                    case 9:
                        this->animIndex = SK_ANIMATION_IDLE;
                        this->fadeInState = SK_FADE_IN_STATE_START;
                        break;

                    case 12:
                        this->animIndex = SK_ANIMATION_HIDE_OCARINA_START;
                        this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 13:
                        this->animIndex = SK_ANIMATION_JUMP_WHILE_HIDING_OCARINA;
                        this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 14:
                        this->animIndex = SK_ANIMATION_HORSE_RIDE_START;
                        break;

                    case 15:
                        this->animIndex = SK_ANIMATION_HORSE_RIDE_LOOP;
                        break;

                    case 16:
                        this->animIndex = SK_ANIMATION_HORSE_RIDE_AND_ROTATE;
                        break;

                    case 17:
                        this->animIndex = SK_ANIMATION_RECLINING_FLOAT;
                        break;

                    case 18:
                        this->animIndex = SK_ANIMATION_CURSE_START;
                        break;

                    case 19:
                        this->animIndex = SK_ANIMATION_LAUGH_START;
                        break;

                    case 20:
                        this->animIndex = SK_ANIMATION_RAISE_MASK_START;
                        break;

                    case 21:
                        this->animIndex = SK_ANIMATION_LOWER_MASK;
                        break;

                    case 22:
                        this->animIndex = SK_ANIMATION_PLAY_OCARINA_WHILE_FLOATING;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 23:
                        this->animIndex = SK_ANIMATION_FLOATING_TURN_AROUND;
                        this->handType = SK_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA;
                        break;

                    case 24:
                        this->animIndex = SK_ANIMATION_CALL_DOWN_MOON_START;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 25:
                        Actor_MarkForDeath(&this->actor);
                        break;

                    case 26:
                        this->animIndex = SK_ANIMATION_SMACK_FAIRY_START;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 27:
                        this->animIndex = SK_ANIMATION_HIT_BY_BUBBLE;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SK_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 28:
                        this->animIndex = SK_ANIMATION_DROP_OCARINA;
                        this->handType = SK_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA;
                        break;

                    case 30:
                        this->animIndex = SK_ANIMATION_FLOATING_ARMS_CROSSED;
                        break;

                    case 31:
                        this->animIndex = SK_ANIMATION_DEFLECT_ATTACK;
                        break;

                    case 32:
                        this->animIndex = SK_ANIMATION_SURPRISE_START;
                        break;

                    case 33:
                        this->animIndex = SK_ANIMATION_LOOK_AROUND_FOR_GIANTS_START;
                        break;

                    case 34:
                        this->animIndex = SK_ANIMATION_HOLD_HEAD_AND_SHAKE_START;
                        break;

                    case 35:
                        this->animIndex = SK_ANIMATION_HOLD_HEAD_AND_SCREAM_START;
                        break;

                    case 36:
                        this->animIndex = SK_ANIMATION_HUDDLE_WITH_FAIRIES;
                        break;

                    case 37:
                        this->animIndex = SK_ANIMATION_SEARCH_MASK_SALESMAN;
                        break;

                    case 38:
                        this->animIndex = SK_ANIMATION_HOLD_UP_MASK_START;
                        break;

                    case 39:
                        this->animIndex = SK_ANIMATION_SHIVER;
                        break;

                    case 40:
                        this->animIndex = SK_ANIMATION_DRAW;
                        break;

                    case 41:
                        this->animIndex = SK_ANIMATION_TELESCOPE_LOOK_UP_START;
                        break;

                    case 42:
                        this->animIndex = SK_ANIMATION_BENT_OVER_HEAD_TWITCH;
                        break;

                    case 43:
                        this->animIndex = SK_ANIMATION_BENT_OVER_LOOK_UP;
                        break;

                    case 44:
                        this->animIndex = SK_ANIMATION_SPANK;
                        break;

                    case 45:
                        this->animIndex = SK_ANIMATION_HIP_SHAKE_AND_JUMP;
                        this->fadeOutState = SK_FADE_OUT_STATE_FADING_OUT;
                        break;

                    case 46:
                        this->handType = SK_HAND_TYPE_HOLDING_FLUTE;
                        this->animIndex = SK_ANIMATION_PLAY_FLUTE;
                        break;

                    case 47:
                        this->animIndex = SK_ANIMATION_CARTWHEEL;
                        break;

                    case 48:
                        this->animIndex = SK_ANIMATION_CARTWHEEL;
                        break;

                    case 49:
                        this->animIndex = SK_ANIMATION_LOOK_UP_AT_GIANTS;
                        break;

                    case 50:
                        this->animIndex = SK_ANIMATION_ASHAMED_START;
                        break;

                    case 51:
                        this->animIndex = SK_ANIMATION_LOOK_LEFT_START;
                        break;

                    case 52:
                        this->animIndex = SK_ANIMATION_SNIFF;
                        break;

                    case 53:
                        this->animIndex = SK_ANIMATION_CARTWHEEL;
                        break;

                    case 54:
                        this->animIndex = SK_ANIMATION_LIE_FLAT;
                        break;

                    case 55:
                        this->animIndex = SK_ANIMATION_DANGLE_FROM_MASK_START;
                        break;

                    case 56:
                        this->animIndex = SK_ANIMATION_DROPPED_FROM_MASK;
                        break;

                    case 57:
                        this->animIndex = SK_ANIMATION_LOOK_UP_AT_GIANTS;
                        break;

                    case 58:
                        this->animIndex = SK_ANIMATION_ASHAMED_START;
                        break;

                    case 59:
                        this->animIndex = SK_ANIMATION_LOOK_LEFT_START;
                        break;

                    case 60:
                        this->animIndex = SK_ANIMATION_SNIFF;
                        break;

                    case 5:
                    case 10:
                        break;

                    default:
                        this->animIndex = SK_ANIMATION_SHAKE_HEAD;
                        break;
                }

                DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, actorActionIndex);
    } else {
        this->csAction = 99;
    }

    if (this->fadeInState == SK_FADE_IN_STATE_START) {
        Math_SmoothStepToF(&this->fogScale, 0.7f, 0.1f, 0.007f, 0.005f);
        if (this->fogScale < 0.71f) {
            this->fogScale = 0.7f;
            this->fogN = 800;
            this->fadeInState++;
        }

        this->fogR = play->lightCtx.unk7 * this->fogScale;
        this->fogG = play->lightCtx.unk8 * this->fogScale;
        this->fogB = play->lightCtx.unk9 * this->fogScale;
    } else if (this->fadeInState == SK_FADE_IN_STATE_INCREASE_FOG) {
        if (this->fogN < 996) {
            this->fogN += 10;
        }

        if (this->fogN > 996) {
            this->fadeInState++;
            this->fogN = 996;
        }
    } else if (this->fadeInState == SK_FADE_IN_STATE_INCREASE_ALPHA) {
        if (this->alpha < 128) {
            this->alpha += 3;
        }

        if (this->alpha < 255) {
            this->alpha += 20;
        } else {
            this->alpha = 255;
            this->fadeInState = SK_FADE_IN_STATE_NONE;
        }
    }

    if (this->fadeOutState == SK_FADE_OUT_STATE_FADING_OUT) {
        if (this->fadeOutTimer > 40) {
            this->maskType = SK_MASK_TYPE_FADING_OUT;
        }

        this->fadeOutTimer++;
        if (this->fadeOutTimer >= 44) {
            this->alpha -= 35;
            if (this->alpha < 0) {
                this->alpha = 0;
                this->fadeOutState = SK_FADE_OUT_STATE_NONE;
                gSaveContext.save.weekEventReg[12] |= 4;
                if (!(play->actorCtx.unk5 & 2)) {
                    Actor_MarkForDeath(&this->actor);
                } else {
                    this->shouldDraw = false;
                }
            }
        }
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->animIndex) {
            case SK_ANIMATION_LOOK_AROUND:
            case SK_ANIMATION_CURSE_START:
            case SK_ANIMATION_LAUGH_START:
            case SK_ANIMATION_HIDE_OCARINA_START:
            case SK_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING:
            case SK_ANIMATION_PICK_UP_OCARINA:
            case SK_ANIMATION_KICK_OVER_LINK:
            case SK_ANIMATION_UNUSED_KICK_OVER_LINK:
            case SK_ANIMATION_HORSE_RIDE_START:
            case SK_ANIMATION_RAISE_MASK_START:
            case SK_ANIMATION_FLOATING_TURN_AROUND:
            case SK_ANIMATION_CALL_DOWN_MOON_START:
            case SK_ANIMATION_SMACK_FAIRY_START:
            case SK_ANIMATION_TELESCOPE_LOOK_UP_START:
            case SK_ANIMATION_SURPRISE_START:
            case SK_ANIMATION_LOOK_AROUND_FOR_GIANTS_START:
            case SK_ANIMATION_HOLD_HEAD_AND_SHAKE_START:
            case SK_ANIMATION_HOLD_HEAD_AND_SCREAM_START:
            case SK_ANIMATION_HOLD_UP_MASK_START:
            case SK_ANIMATION_DANGLE_FROM_MASK_START:
            case SK_ANIMATION_ASHAMED_START:
            case SK_ANIMATION_LOOK_LEFT_START:
            case SK_ANIMATION_SNIFF:
                this->animIndex++;
                DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
                break;

            case SK_ANIMATION_LOWER_MASK:
                this->animIndex = SK_ANIMATION_IDLE;
                this->maskType = SK_MASK_TYPE_NORMAL;
                this->handType = SK_HAND_TYPE_DEFAULT;
                DmStk_ChangeAnimation(this, play, &this->skelAnime, &sAnimations[this->animIndex], 0);
                break;
        }
    }

    if (((this->animIndex == SK_ANIMATION_RAISE_MASK_START) && (this->skelAnime.curFrame >= 16.0f)) ||
        (this->animIndex == SK_ANIMATION_RAISE_MASK_LOOP) || (this->animIndex == SK_ANIMATION_LOWER_MASK)) {
        this->maskType = SK_MASK_TYPE_RAISED;
        this->handType = SK_HAND_TYPE_HOLDING_MAJORAS_MASK;
    } else if (((this->animIndex >= SK_ANIMATION_HUDDLE_WITH_FAIRIES) && (this->animIndex <= SK_ANIMATION_DRAW)) ||
               ((this->animIndex >= SK_ANIMATION_PLAY_FLUTE) && (this->animIndex <= SK_ANIMATION_CARTWHEEL)) ||
               ((play->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 7))) {
        this->maskType = SK_MASK_TYPE_NO_MASK;
        if ((this->animIndex == SK_ANIMATION_HOLD_UP_MASK_START) ||
            (this->animIndex == SK_ANIMATION_HOLD_UP_MASK_LOOP)) {
            this->handType = SK_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE;
        }
    }

    if (this->animIndex == SK_ANIMATION_DROPPED_FROM_MASK) {
        this->maskType = SK_MASK_TYPE_NO_MASK;
    }
}

void DmStk_UpdateCollision(DmStk* this, PlayState* play) {
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

/**
 * Handles Skull Kid when he is at the top of the Clock Tower with the Ocarina of Time.
 * If he is hit in this state, he will drop the Ocarina.
 *
 * If the player waits a while while Skull Kid is in this state, they will see a message
 * from Tatl telling them to hurry up and do something.
 */
void DmStk_ClockTower_IdleWithOcarina(DmStk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (play->csCtx.state == 0) {
        DmStk_ClockTower_AdjustHeightAndRotation(this, play);
        this->actor.flags |= ACTOR_FLAG_1;
        this->tatlMessageTimer++;
        if (this->tatlMessageTimer > 800) {
            this->tatlMessageTimer = 0;
            if (!(player->stateFlags2 & 0x8000000)) {
                // Why are you just standing around?
                Message_StartTextbox(play, 0x2014, &this->actor);
            }
        }

        if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
            this->hasBeenHit = true;
            this->actionFunc = DmStk_ClockTower_StartDropOcarinaCutscene;
        }
    }
}

/**
 * Handles Skull Kid when he is at the top of the Clock Tower after the Ocarina of Time
 * has been returned to the player.
 * If he is hit in this state, he will just deflect the attack.
 */
void DmStk_ClockTower_Idle(DmStk* this, PlayState* play) {
    if (play->csCtx.state == 0) {
        DmStk_ClockTower_AdjustHeightAndRotation(this, play);
        this->actor.flags |= ACTOR_FLAG_1;

        if (this->animIndex == SK_ANIMATION_CALL_DOWN_MOON_LOOP) {
            this->actor.targetArrowOffset = 3100.0f;
        } else {
            this->actor.targetArrowOffset = 200.0f;
        }

        if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
            this->hasBeenHit = true;
            this->actionFunc = DmStk_ClockTower_DeflectHit;
        }
    }
}

void DmStk_Update(Actor* thisx, PlayState* play) {
    DmStk* this = THIS;

    if (DM_STK_GET_TYPE(&this->actor) != DM_STK_TYPE_MAJORAS_MASK) {
        if (this->animIndex == SK_ANIMATION_CALL_DOWN_MOON_LOOP) {
            Actor_SetFocus(&this->actor, 40.0f);
        } else {
            Actor_SetFocus(&this->actor, 6.0f);
        }

        DmStk_LoadObjectForAnimation(this, play);

        if (this->animIndex != SK_ANIMATION_LIE_FLAT) {
            SkelAnime_Update(&this->skelAnime);
        }

        this->alpha = this->alpha;

        this->actionFunc(this, play);

        if (play->sceneNum == SCENE_OKUJOU) {
            DmStk_UpdateCollision(this, play);
        }

        DmStk_UpdateCutscenes(this, play);
        DmStk_PlaySfxForCutscenes(this, play);

        // This handles the cutscene where the player takes out the Deku Pipes for the first time.
        switch (this->dekuPipesCutsceneState) {
            case SK_DEKU_PIPES_CS_STATE_READY:
                if (func_800B8718(&this->actor, &play->state)) {
                    this->dekuPipesCutsceneState = SK_DEKU_PIPES_CS_STATE_PLAYER_USED_OCARINA;
                } else {
                    func_800B874C(&this->actor, play, this->actor.xzDistToPlayer, fabsf(this->actor.playerHeightRel));
                }
                break;

            case SK_DEKU_PIPES_CS_STATE_PLAYER_USED_OCARINA:
                if (ActorCutscene_GetCanPlayNext(16)) {
                    this->dekuPipesCutsceneState = SK_DEKU_PIPES_CS_STATE_START;
                    ActorCutscene_Start(16, &this->actor);
                    this->actionFunc = DmStk_ClockTower_Idle;
                } else {
                    ActorCutscene_SetIntentToPlay(16);
                }
                break;

            case SK_DEKU_PIPES_CS_STATE_START:
                if (play->csCtx.state == 0) {
                    this->dekuPipesCutsceneState = SK_DEKU_PIPES_CS_STATE_END;
                }
                break;
        }

        // This code is responsible for making in-game time pass while using the telescope in the Astral Observatory.
        // Skull Kid is always loaded in the scene, even if he isn't visible, hence why time always passes.
        if ((play->actorCtx.unk5 & 2) && (play->msgCtx.msgMode != 0) && (play->msgCtx.currentTextId == 0x5E6) &&
            !FrameAdvance_IsEnabled(&play->state) && (play->transitionTrigger == TRANS_TRIGGER_OFF) &&
            (ActorCutscene_GetCurrentIndex() == -1) && (play->csCtx.state == 0)) {
            gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)REG(15);
            if (REG(15) != 0) {
                gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)((void)0, gSaveContext.save.daySpeed);
            }
        }
    }

    if ((play->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 3) &&
        (play->csCtx.currentCsIndex > 0)) {
        play->envCtx.unk_17 = 15;
        play->envCtx.unk_18 = 15;
    }
}

s32 DmStk_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    DmStk* this = THIS;

    if (limbIndex == SKULL_KID_LIMB_RIGHT_HAND) {
        if ((this->handType == SK_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE) ||
            (this->handType == SK_HAND_TYPE_HOLDING_LINK_MASK) || (this->handType == SK_HAND_TYPE_HOLDING_OCARINA)) {
            *dList = NULL;
        }
    } else if (limbIndex == SKULL_KID_LIMB_LEFT_HAND) {
        switch (this->handType) {
            case SK_HAND_TYPE_HOLDING_LINK_MASK:
            case SK_HAND_TYPE_HOLDING_MAJORAS_MASK:
            case SK_HAND_TYPE_HOLDING_OCARINA:
            case SK_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA:
            case SK_HAND_TYPE_HOLDING_FLUTE:
                *dList = NULL;
                break;

            case SK_HAND_TYPE_DEFAULT:
                if (this->alpha == 255) {
                    *dList = NULL;
                }
                break;
        }
    } else if (limbIndex == SKULL_KID_LIMB_HEAD) {
        *dList = NULL;
    }

    return false;
}

void DmStk_PostLimbDraw2(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    s32 pad;
    s32 pad2;
    DmStk* this = THIS;

    if (limbIndex == SKULL_KID_LIMB_HEAD) {
        Matrix_MultZero(&this->headPos);

        OPEN_DISPS(play->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((this->animIndex == SK_ANIMATION_LOOK_LEFT_LOOP) || (this->animIndex == SK_ANIMATION_LAUGH_LOOP) ||
            (this->animIndex == SK_ANIMATION_LAUGH_AFTER_SNIFF)) {
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidLaughingHeadDL);
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidLaughingEyesDL);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidNormalHeadDL);
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidNormalEyesDL);
        }

        switch (this->maskType) {
            case SK_MASK_TYPE_NO_MASK:
                break;

            case SK_MASK_TYPE_NORMAL:
                if ((play->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1) &&
                    (play->csCtx.frames < 1400)) {
                    if (this->fogN == this->fogF) {
                        this->fogF = this->fogN;
                    }
                    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, this->fogR, this->fogG, this->fogB, this->fogA,
                                               this->fogN, this->fogF);
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
                } else {
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                }
                break;

            case SK_MASK_TYPE_GLOWING_EYES:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMaskEyesDL);

                if (Cutscene_CheckActorAction(play, 513) &&
                    (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 513)]->action == 2) &&
                    (this->objectStk2ObjectIndex >= 0)) {
                    Matrix_Push();
                    Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);
                    gSegments[6] = PHYSICAL_TO_VIRTUAL(play->objectCtx.status[this->objectStk2ObjectIndex].segment);

                    gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[this->objectStk2ObjectIndex].segment);

                    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(gSkullKidMajorasMaskCurseOverlayTexAnim));
                    Gfx_DrawDListOpa(play, gSkullKidMajorasMaskCurseOverlayDL);
                    gSegments[6] = PHYSICAL_TO_VIRTUAL(play->objectCtx.status[this->objectStkObjectIndex].segment);

                    gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[this->objectStkObjectIndex].segment);

                    Matrix_Pop();
                }
                break;
        }

        CLOSE_DISPS(play->state.gfxCtx);

    } else if (limbIndex == SKULL_KID_LIMB_RIGHT_HAND) {

        OPEN_DISPS(play->state.gfxCtx);

        if (this->handType != SK_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE) {
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }

        switch (this->handType) {
            case SK_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidUntexturedRightHand);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidLinkMask2DL);
                break;

            case SK_HAND_TYPE_HOLDING_LINK_MASK:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMaskHoldingRightHand);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidLinkMask3DL);
                break;

            case SK_HAND_TYPE_HOLDING_OCARINA:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidOcarinaHoldingRightHand);

                if ((play->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1)) {
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidOcarinaOfTimeDL);
                }
                break;

            case SK_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE:
                Matrix_Translate(-20.0f, -660.0f, 860.0f, MTXMODE_APPLY);
                Matrix_RotateYS(0x6142, MTXMODE_APPLY);
                Matrix_RotateXS(-0x1988, MTXMODE_APPLY);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                break;
        }

        CLOSE_DISPS(play->state.gfxCtx);

    } else if (limbIndex == SKULL_KID_LIMB_LEFT_HAND) {

        OPEN_DISPS(play->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        switch (this->handType) {
            case SK_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE:
                break;

            case SK_HAND_TYPE_HOLDING_LINK_MASK:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidUntexturedLeftHand);
                break;

            case SK_HAND_TYPE_HOLDING_MAJORAS_MASK:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidTwoFingersExtendedLeftHand);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask2DL);
                break;

            case SK_HAND_TYPE_HOLDING_OCARINA:
                if ((play->sceneNum != SCENE_LOST_WOODS) || (gSaveContext.sceneSetupIndex != 1)) {
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidOcarinaOfTimeDL);
                }
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidTwoFingersExtendedLeftHand);
                break;

            case SK_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidTwoFingersExtendedLeftHand);
                break;

            case SK_HAND_TYPE_HOLDING_FLUTE:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidFluteHoldingLeftHand);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidFluteDL);
                break;

            case SK_HAND_TYPE_DEFAULT:
                if (this->alpha == 255) {
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidOpenLeftHand);
                }
                break;
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void DmStk_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmStk* this = THIS;

    DmStk_PostLimbDraw2(play, limbIndex, dList, rot, &this->actor, NULL);
}

void DmStk_Draw(Actor* thisx, PlayState* play) {
    DmStk* this = THIS;

    if (this->shouldDraw) {
        if (DM_STK_GET_TYPE(&this->actor) == DM_STK_TYPE_MAJORAS_MASK) {
            Gfx_DrawDListOpa(play, gSkullKidMajorasMask1DL);
            return;
        }

        gSegments[6] = PHYSICAL_TO_VIRTUAL(play->objectCtx.status[this->objectStkObjectIndex].segment);

        OPEN_DISPS(play->state.gfxCtx);

        this->alpha = this->alpha;
        func_8012C28C(play->state.gfxCtx);

        if (this->alpha < 255) {
            func_8012C2DC(play->state.gfxCtx);
            Scene_SetRenderModeXlu(play, 1, 2);

            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);

            POLY_XLU_DISP =
                SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, DmStk_PostLimbDraw2, &this->actor, POLY_XLU_DISP);
        } else {
            Scene_SetRenderModeXlu(play, 0, 1);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);

            SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                  this->skelAnime.dListCount, DmStk_OverrideLimbDraw, DmStk_PostLimbDraw, &this->actor);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
