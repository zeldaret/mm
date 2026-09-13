/*
 * File: z_en_jgame_tsn.c
 * Overlay: ovl_En_Jgame_Tsn
 * Description: Fisherman's Jumping Game - Fisherman
 */

#include "z_en_jgame_tsn.h"
#include "overlays/actors/ovl_Obj_Jgame_Light/z_obj_jgame_light.h"

#define FLAGS                                                                                  \
    (ACTOR_FLAG_ATTENTION_ENABLED | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_UPDATE_CULLING_DISABLED | \
     ACTOR_FLAG_UPDATE_DURING_OCARINA)

void EnJgameTsn_Init(Actor* thisx, PlayState* play);
void EnJgameTsn_Destroy(Actor* thisx, PlayState* play);
void EnJgameTsn_Update(Actor* thisx, PlayState* play);
void EnJgameTsn_Draw(Actor* thisx, PlayState* play);

void EnJgameTsn_SetupIslandBounds(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_SetupIdle(EnJgameTsn* this);
void EnJgameTsn_Idle(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_SetupPlayerInMiddle(EnJgameTsn* this);
void EnJgameTsn_PlayerInMiddle(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_ExplainRules(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_SetupTalk(EnJgameTsn* this);
void EnJgameTsn_Talk(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_Countdown(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_SetupMinigame(EnJgameTsn* this);
void EnJgameTsn_RunMinigame(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_EndMinigame(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_GiveReward(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_SetupAfterReward(EnJgameTsn* this);
void EnJgameTsn_AfterReward(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_HandleMessageChoice(EnJgameTsn* this, PlayState* play);
void EnJgameTsn_HandleMessageEvent(EnJgameTsn* this, PlayState* play);
s32 EnJgameTsn_PlayerOnIsland(PlayState* play, EnJgameTsnIslandBounds* island);
s32 EnJgameTsn_PlayerOnCorrectIsland(EnJgameTsn* this, PlayState* play);

ActorProfile En_Jgame_Tsn_Profile = {
    /**/ ACTOR_EN_JGAME_TSN,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_TSN,
    /**/ sizeof(EnJgameTsn),
    /**/ EnJgameTsn_Init,
    /**/ EnJgameTsn_Destroy,
    /**/ EnJgameTsn_Update,
    /**/ EnJgameTsn_Draw,
};

typedef enum EnJgameTsnAnimation {
    /* -1 */ ENJGAMETSN_ANIM_NONE = -1,
    /*  0 */ ENJGAMETSN_ANIM_IDLE,
    /*  1 */ ENJGAMETSN_ANIM_TALK_ONE_HAND,
    /*  2 */ ENJGAMETSN_ANIM_TALK_BOTH_HANDS,
    /*  3 */ ENJGAMETSN_ANIM_MAX
} EnJgameTsnAnimation;

typedef enum {
    /* 0 */ FISHERMAN_EYE_OPEN,
    /* 1 */ FISHERMAN_EYE_CLOSED
} EnJgameTsnEyes;

static AnimationInfo sAnimationInfo[ENJGAMETSN_ANIM_MAX] = {
    { &gFishermanIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f },        // ENJGAMETSN_ANIM_IDLE
    { &gFishermanOneHandTalkAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f }, // ENJGAMETSN_ANIM_TALK_ONE_HAND
    { &gFishermanTwoHandTalkAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f }, // ENJGAMETSN_ANIM_TALK_BOTH_HANDS
};

static ColliderCylinderInit sCylinderInit = {
    {
        COL_MATERIAL_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        ATELEM_NONE | ATELEM_SFX_NORMAL,
        ACELEM_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

static TexturePtr sFishermanEyeTextures[] = { gFishermanEyeOpenTex, gFishermanEyeClosedTex };

void EnJgameTsn_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnJgameTsn* this = (EnJgameTsn*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gFishermanSkel, &gFishermanIdleAnim, this->jointTable, this->morphTable,
                       OBJECT_TSN_LIMB_MAX);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    this->actor.attentionRangeType = ATTENTION_RANGE_6;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.velocity.y = 0.0f;

    if (gSaveContext.save.entrance == ENTRANCE(GREAT_BAY_COAST, 13)) {
        this->actor.flags |= ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
    }

    this->hasSpoken = false;
    this->blinkTimer = 0;
    this->eyeIndex = FISHERMAN_EYE_OPEN;
    this->playerStoodInMiddle = false;

    EnJgameTsn_SetupIslandBounds(this, play);
    EnJgameTsn_SetupIdle(this);
}

void EnJgameTsn_SetupIslandBounds(EnJgameTsn* this, PlayState* play) {
    Path* path = &play->setupPathList[ENJGAMETSN_GET_PATH_INDEX(&this->actor)];
    s32 i;

    if (path == NULL) {
        Actor_Kill(&this->actor);
    }

    for (i = 0; i < ARRAY_COUNT(this->torchIslands); i++) {
        this->torchIslands[i].points = Lib_SegmentedToVirtual(path->points);
        this->torchIslands[i].count = path->count;

        path = &play->setupPathList[path->additionalPathIndex];
        if (path == NULL) {
            Actor_Kill(&this->actor);
        }
    }

    this->middleIsland.points = Lib_SegmentedToVirtual(path->points);
    this->middleIsland.count = path->count;

    path = &play->setupPathList[path->additionalPathIndex];
    if (path == NULL) {
        Actor_Kill(&this->actor);
    }

    this->treeIsland.points = Lib_SegmentedToVirtual(path->points);
    this->treeIsland.count = path->count;
}

void EnJgameTsn_Destroy(Actor* thisx, PlayState* play) {
    EnJgameTsn* this = (EnJgameTsn*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_PLAYING_FISHERMAN_JUMPING_GAME);
}

void EnJgameTsn_SetupIdle(EnJgameTsn* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_IDLE);
    this->actionFunc = EnJgameTsn_Idle;
}

void EnJgameTsn_Idle(EnJgameTsn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        if (this->actor.flags & ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED) {
            this->actor.flags &= ~ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
            if (gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2] > SECONDS_TO_TIMER(0)) {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_ONE_HAND);
                Message_StartTextbox(play, 0x10A2, &this->actor);
                this->textId = 0x10A2;
            } else if (gSaveContext.minigameScore < 20) {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_ONE_HAND);
                Message_StartTextbox(play, 0x10A2, &this->actor);
                this->textId = 0x10A2;
            } else {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_BOTH_HANDS);
                Message_StartTextbox(play, 0x10A3, &this->actor);
                this->textId = 0x10A3;
            }
        } else if (((CURRENT_TIME > CLOCK_TIME(4, 0)) && (CURRENT_TIME < CLOCK_TIME(7, 0))) ||
                   ((CURRENT_TIME > CLOCK_TIME(16, 0)) && (CURRENT_TIME < CLOCK_TIME(19, 0)))) {
            Message_StartTextbox(play, 0x1094, &this->actor);
            this->textId = 0x1094;
        } else if (!this->hasSpoken) {
            this->hasSpoken = true;
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_ONE_HAND);
            Message_StartTextbox(play, 0x1095, &this->actor);
            this->textId = 0x1095;
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_ONE_HAND);
            Message_StartTextbox(play, 0x1096, &this->actor);
            this->textId = 0x1096;
        }
        EnJgameTsn_SetupTalk(this);
    } else if (this->actor.flags & ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED) {
        Actor_OfferTalk(&this->actor, play, 200.0f);
    } else {
        Actor_OfferTalk(&this->actor, play, 80.0f);
    }

    if ((player->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && !(player->stateFlags1 & PLAYER_STATE1_2000) &&
        (!this->playerStoodInMiddle) && (GET_PLAYER_FORM == PLAYER_FORM_HUMAN) &&
        EnJgameTsn_PlayerOnIsland(play, &this->middleIsland)) {
        this->playerStoodInMiddle = true;
        EnJgameTsn_SetupPlayerInMiddle(this);
    } else if (!(player->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        this->playerStoodInMiddle = false;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x71C, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnJgameTsn_SetupPlayerInMiddle(EnJgameTsn* this) {
    this->actor.flags |= ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
    this->actionFunc = EnJgameTsn_PlayerInMiddle;
}

void EnJgameTsn_PlayerInMiddle(EnJgameTsn* this, PlayState* play) {
    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        this->actor.flags &= ~ACTOR_FLAG_TALK_OFFER_AUTO_ACCEPTED;
        if (((CURRENT_TIME > CLOCK_TIME(4, 0)) && (CURRENT_TIME < CLOCK_TIME(7, 0))) ||
            ((CURRENT_TIME > CLOCK_TIME(16, 0)) && (CURRENT_TIME < CLOCK_TIME(19, 0)))) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_BOTH_HANDS);
            Message_StartTextbox(play, 0x1094, &this->actor);
            this->textId = 0x1094;
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_ONE_HAND);
            Message_StartTextbox(play, 0x1098, &this->actor);
            this->textId = 0x1098;
        }
        EnJgameTsn_SetupTalk(this);
    } else {
        Actor_OfferTalk(&this->actor, play, 1000.0f);
    }
}

void EnJgameTsn_SetupExplainRules(EnJgameTsn* this) {
    this->actionFunc = EnJgameTsn_ExplainRules;
}

void EnJgameTsn_ExplainRules(EnJgameTsn* this, PlayState* play) {
    if (this->actor.csId != CS_ID_NONE) {
        if (CutsceneManager_IsNext(this->actor.csId)) {
            CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
            EnJgameTsn_SetupTalk(this);
        } else {
            if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
                CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
            }
            CutsceneManager_Queue(this->actor.csId);
        }
    } else {
        EnJgameTsn_SetupTalk(this);
    }
}

void EnJgameTsn_SetupTalk(EnJgameTsn* this) {
    this->actionFunc = EnJgameTsn_Talk;
}

void EnJgameTsn_Talk(EnJgameTsn* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
        case TEXT_STATE_NEXT:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_FADING:
            break;

        case TEXT_STATE_CHOICE:
            EnJgameTsn_HandleMessageChoice(this, play);
            break;

        case TEXT_STATE_EVENT:
            EnJgameTsn_HandleMessageEvent(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                if (CutsceneManager_GetCurrentCsId() == this->actor.csId) {
                    CutsceneManager_Stop(this->actor.csId);
                }
                EnJgameTsn_SetupIdle(this);
            }
            break;

        default:
            break;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x71C, 0xB6);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnJgameTsn_SetupCountdown(EnJgameTsn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->stateFlags1 |= PLAYER_STATE1_20;
    Audio_PlaySubBgm(NA_BGM_TIMED_MINI_GAME);
    play->interfaceCtx.minigameState = MINIGAME_STATE_COUNTDOWN_SETUP_3;
    Interface_InitMinigame(play);
    SET_WEEKEVENTREG(WEEKEVENTREG_PLAYING_FISHERMAN_JUMPING_GAME);
    Interface_StartTimer(TIMER_ID_MINIGAME_2, 120);
    this->actionFunc = EnJgameTsn_Countdown;
}

void EnJgameTsn_Countdown(EnJgameTsn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (play->interfaceCtx.minigameState == MINIGAME_STATE_COUNTDOWN_GO) {
        EnJgameTsn_SetupMinigame(this);
        player->stateFlags1 &= ~PLAYER_STATE1_20;
    }
}

void EnJgameTsn_SetupMinigame(EnJgameTsn* this) {
    this->torchIndex = Rand_Next() & 3;
    this->torchTimer = 0;
    *this->torchFlags[this->torchIndex] |= OBJJGAMELIGHT_IGNITE_FIRE;
    this->actionFunc = EnJgameTsn_RunMinigame;
}

void EnJgameTsn_RunMinigame(EnJgameTsn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 i;
    s32 nextTorchIndex;

    if ((this->torchTimer > 100) || EnJgameTsn_PlayerOnCorrectIsland(this, play)) {
        nextTorchIndex = Rand_Next() % 3;

        this->torchTimer = 0;
        if (nextTorchIndex < this->torchIndex) {
            this->torchIndex = nextTorchIndex;
        } else {
            this->torchIndex = nextTorchIndex + 1;
        }

        for (i = 0; i < ARRAY_COUNT(this->torchFlags); i++) {
            if (i == this->torchIndex) {
                *this->torchFlags[i] |= OBJJGAMELIGHT_IGNITE_FIRE;
                *this->torchFlags[i] &= ~OBJJGAMELIGHT_SNUFF_FIRE;
            } else {
                *this->torchFlags[i] |= OBJJGAMELIGHT_SNUFF_FIRE;
            }
        }
    }

    this->torchTimer++;

    if ((player->actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) && EnJgameTsn_PlayerOnIsland(play, &this->treeIsland)) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_BOTH_HANDS);
        Message_StartTextbox(play, 0x109F, &this->actor);
        this->textId = 0x109F;
        player->stateFlags1 |= PLAYER_STATE1_20;
        *this->torchFlags[this->torchIndex] &= ~OBJJGAMELIGHT_IGNITE_FIRE;
        Audio_StopSubBgm();
        EnJgameTsn_SetupTalk(this);
    } else if ((player->actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH) ||
               (player->actor.bgCheckFlags & BGCHECKFLAG_WATER)) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_BOTH_HANDS);
        Message_StartTextbox(play, 0x10A0, &this->actor);
        this->textId = 0x10A0;
        player->stateFlags1 |= PLAYER_STATE1_20;
        *this->torchFlags[this->torchIndex] &= ~OBJJGAMELIGHT_IGNITE_FIRE;
        Audio_StopSubBgm();
        EnJgameTsn_SetupTalk(this);
    }

    if (gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2] == SECONDS_TO_TIMER(0)) {
        Message_StartTextbox(play, 0x10A1, &this->actor);
        this->textId = 0x10A1;
        player->stateFlags1 |= PLAYER_STATE1_20;
        *this->torchFlags[this->torchIndex] &= ~OBJJGAMELIGHT_IGNITE_FIRE;
        Audio_StopSubBgm();
        EnJgameTsn_SetupTalk(this);
    }
}

void EnJgameTsn_SetupEndMinigame(EnJgameTsn* this) {
    this->actionFunc = EnJgameTsn_EndMinigame;
}

void EnJgameTsn_EndMinigame(EnJgameTsn* this, PlayState* play) {
    play->nextEntrance = ENTRANCE(GREAT_BAY_COAST, 13);
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_80;
    gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE;
}

void EnJgameTsn_SetupGiveReward(EnJgameTsn* this) {
    this->actionFunc = EnJgameTsn_GiveReward;
}

void EnJgameTsn_GiveReward(EnJgameTsn* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_FISHERMANS_JUMPING_GAME_HEART_PIECE)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_FISHERMANS_JUMPING_GAME_HEART_PIECE);
        }
        EnJgameTsn_SetupAfterReward(this);
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_FISHERMANS_JUMPING_GAME_HEART_PIECE)) {
        Actor_OfferGetItem(&this->actor, play, GI_RUPEE_PURPLE, 500.0f, 100.0f);
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 500.0f, 100.0f);
    }
}

void EnJgameTsn_SetupAfterReward(EnJgameTsn* this) {
    this->actionFunc = EnJgameTsn_AfterReward;
}

void EnJgameTsn_AfterReward(EnJgameTsn* this, PlayState* play) {
    if (Actor_TalkOfferAccepted(&this->actor, &play->state)) {
        Message_StartTextbox(play, 0x10A4, &this->actor);
        this->textId = 0x10A4;
        EnJgameTsn_SetupTalk(this);
    } else {
        Actor_OfferTalkExchangeEquiCylinder(&this->actor, play, 200.0f, PLAYER_IA_MINUS1);
    }
}

void EnJgameTsn_HandleMessageChoice(EnJgameTsn* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        if (play->msgCtx.choiceIndex == 0) {
            if (gSaveContext.save.saveInfo.playerData.rupees >= 20) {
                Message_StartTextbox(play, 0x109E, &this->actor);
                this->textId = 0x109E;
                Rupees_ChangeBy(-20);
            } else {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_BOTH_HANDS);
                Message_StartTextbox(play, 0x109D, &this->actor);
                this->textId = 0x109D;
            }
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_TALK_BOTH_HANDS);
            Message_StartTextbox(play, 0x109C, &this->actor);
            this->textId = 0x109C;
        }
    }
}

void EnJgameTsn_GetTorchFlags(EnJgameTsn* this, PlayState* play) {
    Actor* prop = play->actorCtx.actorLists[ACTORCAT_PROP].first;

    while (prop != NULL) {
        if (prop->id == ACTOR_OBJ_JGAME_LIGHT) {
            this->torchFlags[OBJJGAMELIGHT_GET_FLAGS(prop)] = &prop->colChkInfo.health;
        }
        prop = prop->next;
    }
}

void EnJgameTsn_HandleMessageEvent(EnJgameTsn* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x1095:
                Message_StartTextbox(play, 0x1096, &this->actor);
                this->textId = 0x1096;
                break;

            case 0x1096:
                Message_StartTextbox(play, 0x1097, &this->actor);
                this->textId = 0x1097;
                break;

            case 0x1098:
                Message_StartTextbox(play, 0x1099, &this->actor);
                this->textId = 0x1099;
                EnJgameTsn_SetupExplainRules(this);
                break;

            case 0x1099:
                Message_StartTextbox(play, 0x109A, &this->actor);
                this->textId = 0x109A;
                break;

            case 0x109A:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, ENJGAMETSN_ANIM_IDLE);
                Message_StartTextbox(play, 0x109B, &this->actor);
                this->textId = 0x109B;
                break;

            case 0x109E:
                if (CutsceneManager_GetCurrentCsId() == this->actor.csId) {
                    CutsceneManager_Stop(this->actor.csId);
                }
                Message_CloseTextbox(play);
                EnJgameTsn_GetTorchFlags(this, play);
                EnJgameTsn_SetupCountdown(this, play);
                break;

            case 0x109F:
            case 0x10A0:
            case 0x10A1:
                Message_CloseTextbox(play);
                gSaveContext.minigameStatus = MINIGAME_STATUS_END;
                gSaveContext.timerStates[TIMER_ID_MINIGAME_2] = TIMER_STATE_STOP;
                CLEAR_WEEKEVENTREG(WEEKEVENTREG_PLAYING_FISHERMAN_JUMPING_GAME);
                EnJgameTsn_SetupEndMinigame(this);
                break;

            case 0x10A3:
                Message_CloseTextbox(play);
                EnJgameTsn_SetupGiveReward(this);
                EnJgameTsn_GiveReward(this, play);
                break;

            default:
                break;
        }
    }
}

s32 EnJgameTsn_PlayerSideOfLine(Vec2f currentPointDiff, Vec2f nextPointDiff) {
    s32 side;

    if ((nextPointDiff.x * currentPointDiff.z) < (currentPointDiff.x * nextPointDiff.z)) {
        side = 1;
    } else {
        side = -1;
    }
    return side;
}

s32 EnJgameTsn_PlayerOnIsland(PlayState* play, EnJgameTsnIslandBounds* island) {
    s32 nextPointIndex = 1;
    s32 side;
    Player* player = GET_PLAYER(play);
    Vec2f currentPointDiff;
    Vec2f nextPointDiff;
    s32 playerIsHere = true;
    s32 pad;
    s32 currentPointIndex = 0;
    f32 playerZ = player->actor.world.pos.z;
    f32 playerX = player->actor.world.pos.x;

    currentPointDiff.x = island->points[0].z - playerZ;
    currentPointDiff.z = island->points[0].x - playerX;
    nextPointDiff.x = island->points[1].z - playerZ;
    nextPointDiff.z = island->points[1].x - playerX;
    side = EnJgameTsn_PlayerSideOfLine(currentPointDiff, nextPointDiff);

    while (nextPointIndex != 0) {
        currentPointIndex++;
        if (nextPointIndex < (island->count - 1)) {
            nextPointIndex++;
        } else {
            nextPointIndex = 0;
        }

        currentPointDiff.x = island->points[currentPointIndex].z - playerZ;
        currentPointDiff.z = island->points[currentPointIndex].x - playerX;
        nextPointDiff.x = island->points[nextPointIndex].z - playerZ;
        nextPointDiff.z = island->points[nextPointIndex].x - playerX;

        if (EnJgameTsn_PlayerSideOfLine(currentPointDiff, nextPointDiff) != side) {
            playerIsHere = false;
            break;
        }
    }

    return playerIsHere;
}

s32 EnJgameTsn_PlayerOnCorrectIsland(EnJgameTsn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 i;
    s32 torchIndex = -1;

    if (player->actor.bgCheckFlags & BGCHECKFLAG_GROUND_TOUCH) {
        for (i = 0; i < ARRAY_COUNT(this->torchIslands); i++) {
            if (EnJgameTsn_PlayerOnIsland(play, &this->torchIslands[i])) {
                torchIndex = i;
            }
        }

        if (torchIndex == -1) {
            return false;
        }

        if (torchIndex == this->torchIndex) {
            Actor_PlaySfx(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
            *this->torchFlags[torchIndex] |= OBJJGAMELIGHT_DISPLAY_CORRECT;
            play->interfaceCtx.minigamePoints = 1;
            return true;
        }

        if (*this->torchFlags[torchIndex] & OBJJGAMELIGHT_IGNITE_FIRE) {
            Actor_PlaySfx(&this->actor, NA_SE_SY_TRE_BOX_APPEAR);
            *this->torchFlags[torchIndex] |= OBJJGAMELIGHT_DISPLAY_CORRECT;
            play->interfaceCtx.minigamePoints = 1;
        } else {
            *this->torchFlags[torchIndex] |= OBJJGAMELIGHT_DISPLAY_INCORRECT;
            Actor_PlaySfx(&this->actor, NA_SE_SY_ERROR);
        }
    }

    return false;
}

void EnJgameTsn_UpdateCollider(EnJgameTsn* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnJgameTsn_Blink(EnJgameTsn* this, PlayState* play) {
    Actor_TrackPlayer(play, &this->actor, &this->headRot, &this->torsoRot, this->actor.focus.pos);

    if (DECR(this->blinkTimer) == 0) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }

    if ((this->blinkTimer == 1) || (this->blinkTimer == 3)) {
        this->eyeIndex = FISHERMAN_EYE_CLOSED;
    } else {
        this->eyeIndex = FISHERMAN_EYE_OPEN;
    }
}

void EnJgameTsn_Update(Actor* thisx, PlayState* play) {
    EnJgameTsn* this = (EnJgameTsn*)thisx;

    this->actionFunc(this, play);

    SkelAnime_Update(&this->skelAnime);
    EnJgameTsn_UpdateCollider(this, play);
    EnJgameTsn_Blink(this, play);
}

s32 EnJgameTsn_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnJgameTsn* this = (EnJgameTsn*)thisx;
    s16 halfRotX = this->headRot.x >> 1;

    if (limbIndex == OBJECT_TSN_LIMB_0F) {
        rot->x += this->headRot.y;
        rot->z += halfRotX;
    } else if (limbIndex == OBJECT_TSN_LIMB_08) {
        rot->x += this->torsoRot.y;
        rot->z += halfRotX;
    }
    return false;
}

void EnJgameTsn_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == OBJECT_TSN_LIMB_0F) {
        Matrix_MultZero(&thisx->focus.pos);
    }
}

void EnJgameTsn_Draw(Actor* thisx, PlayState* play) {
    EnJgameTsn* this = (EnJgameTsn*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL37_Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sFishermanEyeTextures[this->eyeIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sFishermanEyeTextures[this->eyeIndex]));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnJgameTsn_OverrideLimbDraw, EnJgameTsn_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
