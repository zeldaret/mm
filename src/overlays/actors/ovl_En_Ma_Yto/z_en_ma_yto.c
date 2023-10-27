/*
 * File: z_en_ma_yto.c
 * Overlay: ovl_En_Ma_Yto
 * Description: Cremia
 */

#include "z_en_ma_yto.h"
#include "overlays/actors/ovl_En_Ma_Yts/z_en_ma_yts.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnMaYto*)thisx)

void EnMaYto_Init(Actor* thisx, PlayState* play);
void EnMaYto_Destroy(Actor* thisx, PlayState* play);
void EnMaYto_Update(Actor* thisx, PlayState* play);
void EnMaYto_Draw(Actor* thisx, PlayState* play);

s32 EnMaYto_CheckValidSpawn(EnMaYto* this, PlayState* play);
void EnMaYto_InitAnimation(EnMaYto* this, PlayState* play);
void EnMaYto_ChooseAction(EnMaYto* this, PlayState* play);
s32 EnMaYto_TryFindRomani(EnMaYto* this, PlayState* play);
void EnMaYto_SetupKeepLookingForRomani(EnMaYto* this);
void EnMaYto_KeepLookingForRomani(EnMaYto* this, PlayState* play);
void EnMaYto_SetupDefaultWait(EnMaYto* this);
void EnMaYto_DefaultWait(EnMaYto* this, PlayState* play);
void EnMaYto_SetupDefaultDialogueHandler(EnMaYto* this);
void EnMaYto_DefaultDialogueHandler(EnMaYto* this, PlayState* play);
void EnMaYto_DefaultHandlePlayerChoice(EnMaYto* this, PlayState* play);
void EnMaYto_DefaultChooseNextDialogue(EnMaYto* this, PlayState* play);
void EnMaYto_SetupDinnerWait(EnMaYto* this);
void EnMaYto_DinnerWait(EnMaYto* this, PlayState* play);
void EnMaYto_SetupDinnerDialogueHandler(EnMaYto* this);
void EnMaYto_DinnerDialogueHandler(EnMaYto* this, PlayState* play);
void EnMaYto_DinnerHandlePlayerChoice(EnMaYto* this, PlayState* play);
void EnMaYto_DinnerChooseNextDialogue(EnMaYto* this, PlayState* play);
void EnMaYto_SetupBarnWait(EnMaYto* this);
void EnMaYto_BarnWait(EnMaYto* this, PlayState* play);
void EnMaYto_SetupBarnDialogueHandler(EnMaYto* this);
void EnMaYto_BarnDialogueHandler(EnMaYto* this, PlayState* play);
void EnMaYto_BarnChooseNextDialogue(EnMaYto* this, PlayState* play);
void EnMaYto_SetupAfterMilkRunInit(EnMaYto* this);
void EnMaYto_AfterMilkRunInit(EnMaYto* this, PlayState* play);
void EnMaYto_SetupAfterMilkRunDialogueHandler(EnMaYto* this);
void EnMaYto_AfterMilkRunDialogueHandler(EnMaYto* this, PlayState* play);
void EnMaYto_AfterMilkRunChooseNextDialogue(EnMaYto* this, PlayState* play);
void EnMaYto_SetupPostMilkRunGiveReward(EnMaYto* this);
void EnMaYto_PostMilkRunGiveReward(EnMaYto* this, PlayState* play);
void EnMaYto_SetupPostMilkRunExplainReward(EnMaYto* this);
void EnMaYto_PostMilkRunExplainReward(EnMaYto* this, PlayState* play);
void EnMaYto_SetupBeginWarmFuzzyFeelingCs(EnMaYto* this);
void EnMaYto_BeginWarmFuzzyFeelingCs(EnMaYto* this, PlayState* play);
void EnMaYto_SetupWarmFuzzyFeelingCs(EnMaYto* this);
void EnMaYto_WarmFuzzyFeelingCs(EnMaYto* this, PlayState* play);
void EnMaYto_SetupPostMilkRunWaitDialogueEnd(EnMaYto* this);
void EnMaYto_PostMilkRunWaitDialogueEnd(EnMaYto* this, PlayState* play);
void EnMaYto_SetupPostMilkRunEnd(EnMaYto* this);
void EnMaYto_PostMilkRunEnd(EnMaYto* this, PlayState* play);
void EnMaYto_DefaultStartDialogue(EnMaYto* this, PlayState* play);
void EnMaYto_DinnerStartDialogue(EnMaYto* this, PlayState* play);
void EnMaYto_BarnStartDialogue(EnMaYto* this, PlayState* play);
void EnMaYto_ChangeAnim(EnMaYto* this, s32 animIndex);
void EnMaYto_UpdateEyes(EnMaYto* this);
void func_80B90E50(EnMaYto* this, s16);
void EnMaYto_SetRomaniFaceExpression(EnMaYto* this, s16 overrideEyeTexIndex, s16 mouthTexIndex);
void EnMaYto_SetFaceExpression(EnMaYto* this, s16 overrideEyeTexIndex, s16 mouthIndex);
void EnMaYto_InitFaceExpression(EnMaYto* this);
s32 EnMaYto_HasSpokenToPlayerToday(void);
s32 EnMaYto_HasSpokenToPlayer(void);
void EnMaYto_SetTalkedFlag(void);

ActorInit En_Ma_Yto_InitVars = {
    /**/ ACTOR_EN_MA_YTO,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_MA2,
    /**/ sizeof(EnMaYto),
    /**/ EnMaYto_Init,
    /**/ EnMaYto_Destroy,
    /**/ EnMaYto_Update,
    /**/ EnMaYto_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit2 = {
    0, 0, 0, 0, MASS_IMMOVABLE,
};

static AnimationSpeedInfo sAnimationInfo[] = {
    { &gCremiaIdleAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaIdleAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gCremiaSpreadArmsStartAnim, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &gCremiaSpreadArmsStartAnim, 1.0f, ANIMMODE_ONCE, -6.0f },
    { &gCremiaSpreadArmsLoopAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaSpreadArmsLoopAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gCremiaWalkAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaWalkAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
    { &gCremiaThinkAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaThinkAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
    { &gCremiaPetCowAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaPetCowAnim, 1.0f, ANIMMODE_LOOP, -10.0f },
    { &gCremiaSittingPetCowAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaSittingPetCowAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
    { &gCremiaSittingAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaSittingAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
    { &gCremiaSittingLookDownAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaSittingLookDownAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
    { &gCremiaHugStartAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaHugStartAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
    { &gCremiaHugLoopAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaHugLoopAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
    { &gCremiaClapAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gCremiaClapAnim, 1.0f, ANIMMODE_LOOP, -8.0f },
};

static TexturePtr sMouthTextures[] = {
    gCremiaMouthNormalTex,
    gCremiaMouthSlightSmileTex,
    gCremiaMouthFrownTex,
    gCremiaMouthHangingOpenTex,
};

static TexturePtr sEyesTextures[] = {
    gCremiaEyeOpenTex, gCremiaEyeHalfTex, gCremiaEyeClosedTex, gCremiaEyeHappyTex, gCremiaEyeAngryTex, gCremiaEyeSadTex,
};

void EnMaYto_Init(Actor* thisx, PlayState* play) {
    EnMaYto* this = THIS;
    s32 pad;

    this->actor.targetMode = TARGET_MODE_0;
    this->unk200 = 0;
    this->unk310 = 0;
    this->unk320 = 0;
    this->eyeTexIndex = 0;

    if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        EnMaYto_SetFaceExpression(this, 0, 1);
    } else {
        EnMaYto_SetFaceExpression(this, 5, 2);
    }

    this->unk31E = 0;
    this->blinkTimer = 100;
    this->type = EN_MA_YTO_GET_TYPE(&this->actor);
    if (!EnMaYto_CheckValidSpawn(this, play)) {
        Actor_Kill(&this->actor);
        return;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gCremiaSkel, NULL, this->jointTable, this->morphTable, CREMIA_LIMB_MAX);
    EnMaYto_InitAnimation(this, play);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit2);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);

    if (EnMaYto_TryFindRomani(this, play) == 1) {
        EnMaYto_SetupKeepLookingForRomani(this);
    } else {
        EnMaYto_ChooseAction(this, play);
    }
}

s32 EnMaYto_CheckValidSpawn(EnMaYto* this, PlayState* play) {
    switch (this->type) {
        case MA_YTO_TYPE_DEFAULT:
            if ((CURRENT_DAY == 3) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                return false;
            }
            break;

        case MA_YTO_TYPE_DINNER:
            if ((CURRENT_DAY != 1) && CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                return false;
            }
            break;

        case MA_YTO_TYPE_BARN:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                if (((this->actor.params & 0x0F00) >> 8) != 0) {
                    return false;
                }
            } else if (((this->actor.params & 0x0F00) >> 8) == 0) {
                return false;
            }
            if ((gSaveContext.save.time >= CLOCK_TIME(20, 0)) && (CURRENT_DAY == 3)) {
                return false;
            }
            break;

        case MA_YTO_TYPE_AFTERMILKRUN:
            if ((!CHECK_WEEKEVENTREG(WEEKEVENTREG_ESCORTED_CREMIA) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_52_02)) ||
                CHECK_WEEKEVENTREG(WEEKEVENTREG_14_01)) {
                return false;
            }
            break;

        case MA_YTO_TYPE_4:
        default:
            break;
    }

    return true;
}

void EnMaYto_InitAnimation(EnMaYto* this, PlayState* play) {
    switch (this->type) {
        case MA_YTO_TYPE_DEFAULT:
            EnMaYto_ChangeAnim(this, 10);
            break;

        case MA_YTO_TYPE_DINNER:
            if (CURRENT_DAY == 1) {
                EnMaYto_ChangeAnim(this, 14);
            } else {
                EnMaYto_ChangeAnim(this, 16);
            }
            break;

        case MA_YTO_TYPE_BARN:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                EnMaYto_ChangeAnim(this, 12);
            } else {
                EnMaYto_ChangeAnim(this, 8);
            }
            break;

        case MA_YTO_TYPE_AFTERMILKRUN:
            EnMaYto_ChangeAnim(this, 0);
            break;

        case MA_YTO_TYPE_4:
            EnMaYto_ChangeAnim(this, 0);
            break;

        default:
            EnMaYto_ChangeAnim(this, 0);
            break;
    }
}

void EnMaYto_ChooseAction(EnMaYto* this, PlayState* play) {
    switch (this->type) {
        case MA_YTO_TYPE_DEFAULT:
            EnMaYto_SetupDefaultWait(this);
            break;

        case MA_YTO_TYPE_DINNER:
            this->actor.targetMode = TARGET_MODE_6;
            EnMaYto_SetupDinnerWait(this);
            break;

        case MA_YTO_TYPE_BARN:
            EnMaYto_SetupBarnWait(this);
            break;

        case MA_YTO_TYPE_AFTERMILKRUN:
            this->unk310 = 0;
            if ((INV_CONTENT(ITEM_MASK_ROMANI) == ITEM_MASK_ROMANI) &&
                CHECK_WEEKEVENTREG(WEEKEVENTREG_ESCORTED_CREMIA) && (Rand_Next() & 0x80)) {
                EnMaYto_SetupBeginWarmFuzzyFeelingCs(this);
            } else {
                EnMaYto_SetupAfterMilkRunInit(this);
            }
            break;

        case MA_YTO_TYPE_4:
            this->actor.flags |= ACTOR_FLAG_10;
            EnMaYto_SetupWarmFuzzyFeelingCs(this);
            break;

        default:
            EnMaYto_SetupDefaultWait(this);
            break;
    }
}

s32 EnMaYto_SearchRomani(EnMaYto* this, PlayState* play) {
    Actor* npcActor = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npcActor != NULL) {
        if (npcActor->id == ACTOR_EN_MA_YTS) {
            EnMaYts* romani = (EnMaYts*)npcActor;
            s16 romaniType = EN_MA_YTS_GET_TYPE(&romani->actor);

            if (((this->type == MA_YTO_TYPE_DINNER) && (romaniType == MA_YTS_TYPE_SITTING)) ||
                ((this->type == MA_YTO_TYPE_BARN) && (romaniType == MA_YTS_TYPE_BARN))) {
                this->actor.child = &romani->actor;
                romani->actor.parent = &this->actor;
                return true;
            } else {
                npcActor = npcActor->next;
                continue;
            }
        }
        npcActor = npcActor->next;
    }

    return false;
}

/**
 * Returns:
 * - 2: Romani was found.
 * - 1: Romani was not found.
 * - 0: There's no need to find Romani.
 */
s32 EnMaYto_TryFindRomani(EnMaYto* this, PlayState* play) {
    switch (this->type) {
        case MA_YTO_TYPE_DEFAULT:
            return 0;

        case MA_YTO_TYPE_DINNER:
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM) && (CURRENT_DAY == 2)) {
                return 0;
            }
            if (EnMaYto_SearchRomani(this, play)) {
                return 2;
            }
            return 1;

        case MA_YTO_TYPE_BARN:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                if (EnMaYto_SearchRomani(this, play)) {
                    return 2;
                }
                return 1;
            }
            return 0;

        case MA_YTO_TYPE_AFTERMILKRUN:
            return 0;

        case MA_YTO_TYPE_4:
            return 0;
    }

    return 0;
}

void EnMaYto_Destroy(Actor* thisx, PlayState* play) {
    EnMaYto* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnMaYto_SetupKeepLookingForRomani(EnMaYto* this) {
    this->actionFunc = EnMaYto_KeepLookingForRomani;
}

void EnMaYto_KeepLookingForRomani(EnMaYto* this, PlayState* play) {
    if (EnMaYto_TryFindRomani(this, play) == 2) {
        EnMaYto_ChooseAction(this, play);
    }
}

void EnMaYto_SetupDefaultWait(EnMaYto* this) {
    if (this->actor.shape.rot.y == this->actor.home.rot.y) {
        this->animIndex = 11;
        EnMaYto_ChangeAnim(this, 11);
    } else {
        this->animIndex = 1;
        EnMaYto_ChangeAnim(this, 1);
    }

    EnMaYto_InitFaceExpression(this);
    this->unk31E = 2;
    this->actionFunc = EnMaYto_DefaultWait;
}

void EnMaYto_DefaultWait(EnMaYto* this, PlayState* play) {
    s16 rotY = this->actor.home.rot.y - 0x8000;
    s16 direction;

    direction = rotY - this->actor.yawTowardsPlayer;
    if (!Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 5, 0x3000, 0x100) &&
        (this->animIndex == 1)) {
        this->animIndex = 11;
        EnMaYto_ChangeAnim(this, 11);
    }

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnMaYto_DefaultStartDialogue(this, play);
        EnMaYto_SetupDefaultDialogueHandler(this);
    } else if (ABS_ALT(direction) < 0x1555) {
        Actor_OfferTalk(&this->actor, play, 100.0f);
    }
}

void EnMaYto_SetupDefaultDialogueHandler(EnMaYto* this) {
    EnMaYto_ChangeAnim(this, 1);
    this->unk31E = 2;
    this->actionFunc = EnMaYto_DefaultDialogueHandler;
}

void EnMaYto_DefaultDialogueHandler(EnMaYto* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            EnMaYto_DefaultHandlePlayerChoice(this, play);
            break;

        case TEXT_STATE_5:
            EnMaYto_DefaultChooseNextDialogue(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                this->unk31E = 0;
                EnMaYto_SetupDefaultWait(this);
            }
            break;

        case TEXT_STATE_NONE:
        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
            break;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3000, 0x100);
    if ((this->textId == 0x3395) && (this->skelAnime.animation == &gCremiaSpreadArmsStartAnim) &&
        Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnMaYto_ChangeAnim(this, 4);
    }
}

void EnMaYto_DefaultHandlePlayerChoice(EnMaYto* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        if (play->msgCtx.choiceIndex == 0) { // Yes
            Audio_PlaySfx_MessageDecide();
            EnMaYto_SetFaceExpression(this, 0, 3);
            // "Milk Road is fixed!"
            Message_StartTextbox(play, 0x3392, &this->actor);
            this->textId = 0x3392;
        } else { // No
            Audio_PlaySfx_MessageCancel();
            // "Don't lie!"
            Message_StartTextbox(play, 0x3391, &this->actor);
            this->textId = 0x3391;
        }
    }
}

void EnMaYto_DefaultChooseNextDialogue(EnMaYto* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x3391:
                EnMaYto_SetFaceExpression(this, 0, 3);
                Message_StartTextbox(play, 0x3392, &this->actor);
                this->textId = 0x3392;
                break;

            case 0x3392:
                EnMaYto_SetFaceExpression(this, 3, 1);
                Message_StartTextbox(play, 0x3393, &this->actor);
                this->textId = 0x3393;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                break;

            case 0x3394:
                EnMaYto_ChangeAnim(this, 2);
                Message_StartTextbox(play, 0x3395, &this->actor);
                this->textId = 0x3395;
                break;

            case 0x3395:
                EnMaYto_ChangeAnim(this, 1);
                Message_StartTextbox(play, 0x3396, &this->actor);
                this->textId = 0x3396;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                break;

            default:
                break;
        }
    }
}

void EnMaYto_SetupDinnerWait(EnMaYto* this) {
    if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        func_80B90E50(this, 0);
        this->unk31E = 0;
    } else {
        func_80B90E50(this, 2);
        this->unk31E = 2;
    }

    EnMaYto_InitFaceExpression(this);
    this->actionFunc = EnMaYto_DinnerWait;
}

void EnMaYto_DinnerWait(EnMaYto* this, PlayState* play) {
    s16 direction = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnMaYto_DinnerStartDialogue(this, play);
        EnMaYto_SetupDinnerDialogueHandler(this);
    } else {
        Actor* child = this->actor.child;

        if ((child != NULL) && Actor_ProcessTalkRequest(child, &play->state)) {
            Actor_ChangeFocus(&this->actor, play, &this->actor);
            EnMaYto_DinnerStartDialogue(this, play);
            EnMaYto_SetupDinnerDialogueHandler(this);
        } else if (ABS_ALT(direction) < 0x4000) {
            Actor_OfferTalk(&this->actor, play, 120.0f);

            child = this->actor.child;
            if ((child != NULL) && (CURRENT_DAY != 2)) {
                s16 childDirection = child->shape.rot.y - child->yawTowardsPlayer;

                if (ABS_ALT(childDirection) < 0x4000) {
                    Actor_OfferTalk(child, play, 120.0f);
                }
            }
        }
    }
}

void EnMaYto_SetupDinnerDialogueHandler(EnMaYto* this) {
    if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        func_80B90E50(this, 1);
    } else {
        func_80B90E50(this, 2);
    }

    this->unk31E = 0;
    this->actionFunc = EnMaYto_DinnerDialogueHandler;
}

void EnMaYto_DinnerDialogueHandler(EnMaYto* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
            EnMaYto_DinnerHandlePlayerChoice(this, play);
            break;

        case TEXT_STATE_5:
            EnMaYto_DinnerChooseNextDialogue(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                EnMaYto_SetupDinnerWait(this);
            }
            break;

        case TEXT_STATE_NONE:
        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
            break;
    }
}

void EnMaYto_DinnerHandlePlayerChoice(EnMaYto* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        if (play->msgCtx.choiceIndex == 0) { // Yes
            Audio_PlaySfx_MessageDecide();
            EnMaYto_SetFaceExpression(this, 0, 3);
            // "Milk Road is fixed!"
            Message_StartTextbox(play, 0x3399, &this->actor);
            this->textId = 0x3399;
        } else { // No
            Audio_PlaySfx_MessageCancel();
            // "Don't lie!"
            Message_StartTextbox(play, 0x3398, &this->actor);
            this->textId = 0x3398;
        }
    }
}

void EnMaYto_DinnerChooseNextDialogue(EnMaYto* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x3398:
                EnMaYto_SetFaceExpression(this, 0, 3);
                Message_StartTextbox(play, 0x3399, &this->actor);
                this->textId = 0x3399;
                break;

            case 0x3399:
                EnMaYto_SetFaceExpression(this, 3, 1);
                Message_StartTextbox(play, 0x339A, &this->actor);
                this->textId = 0x339A;
                break;

            case 0x339A:
                this->unk31E = 1;
                EnMaYto_SetFaceExpression(this, 0, 1);
                Message_StartTextbox(play, 0x339B, &this->actor);
                this->textId = 0x339B;
                break;

            case 0x339B:
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                func_80B90E50(this, 0);
                EnMaYto_SetRomaniFaceExpression(this, 3, 3);
                Message_StartTextbox(play, 0x339C, &this->actor);
                this->textId = 0x339C;
                break;

            case 0x339C:
                this->unk31E = 1;
                Actor_ChangeFocus(&this->actor, play, &this->actor);
                EnMaYto_SetFaceExpression(this, 0, 2);
                Message_StartTextbox(play, 0x339D, &this->actor);
                this->textId = 0x339D;
                break;

            case 0x339D:
                func_80B90E50(this, 1);
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                EnMaYto_SetRomaniFaceExpression(this, 0, 1);
                Message_StartTextbox(play, 0x339E, &this->actor);
                this->textId = 0x339E;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            case 0x339F:
                this->unk31E = 0;
                Message_StartTextbox(play, 0x33A0, &this->actor);
                this->textId = 0x33A0;
                break;

            case 0x33A0:
                Message_StartTextbox(play, 0x33A1, &this->actor);
                this->textId = 0x33A1;
                break;

            case 0x33A1:
                func_80B90E50(this, 1);
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                EnMaYto_SetRomaniFaceExpression(this, 0, 2);
                Message_StartTextbox(play, 0x33A2, &this->actor);
                this->textId = 0x33A2;
                break;

            case 0x33A2:
                this->unk31E = 1;
                Actor_ChangeFocus(&this->actor, play, &this->actor);
                EnMaYto_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x33A3, &this->actor);
                this->textId = 0x33A3;
                break;

            case 0x33A3:
                this->unk31E = 0;
                EnMaYto_SetFaceExpression(this, 3, 3);
                Message_StartTextbox(play, 0x33A4, &this->actor);
                this->textId = 0x33A4;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            case 0x33A5:
                Message_StartTextbox(play, 0x33A6, &this->actor);
                this->textId = 0x33A6;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                break;

            case 0x33A7:
                Message_StartTextbox(play, 0x33A8, &this->actor);
                this->textId = 0x33A8;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                break;

            default:
                break;
        }
    }
}

void EnMaYto_SetupBarnWait(EnMaYto* this) {
    if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        EnMaYto_ChangeAnim(this, 13);
        func_80B90E50(this, 0);
        this->unk31E = 0;
    } else {
        this->unk320 = 0;
        EnMaYto_ChangeAnim(this, 9);
        func_80B90E50(this, 2);
        this->unk31E = 2;
    }
    EnMaYto_InitFaceExpression(this);
    this->actionFunc = EnMaYto_BarnWait;
}

void EnMaYto_BarnWait(EnMaYto* this, PlayState* play) {
    s16 direction = this->actor.shape.rot.y + 0x471C;

    direction -= this->actor.yawTowardsPlayer;
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnMaYto_BarnStartDialogue(this, play);
        EnMaYto_SetupBarnDialogueHandler(this);
    } else {
        Actor* child = this->actor.child;

        if ((child != NULL) && Actor_ProcessTalkRequest(child, &play->state)) {
            Actor_ChangeFocus(&this->actor, play, &this->actor);
            EnMaYto_BarnStartDialogue(this, play);
            EnMaYto_SetupBarnDialogueHandler(this);
        } else if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM) || (ABS_ALT(direction) < 0x2000)) {
            Actor_OfferTalk(&this->actor, play, 100.0f);

            child = this->actor.child;
            if (child != NULL) {
                Actor_OfferTalk(child, play, 100.0f);
            }
        }
    }
}

void EnMaYto_SetupBarnDialogueHandler(EnMaYto* this) {
    if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        func_80B90E50(this, 1);
    } else {
        func_80B90E50(this, 2);
    }

    this->actionFunc = EnMaYto_BarnDialogueHandler;
}

void EnMaYto_BarnDialogueHandler(EnMaYto* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_5:
            EnMaYto_BarnChooseNextDialogue(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                this->unk31E = 0;
                EnMaYto_SetupBarnWait(this);
            }
            break;

        case TEXT_STATE_NONE:
        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
        case TEXT_STATE_CHOICE:
            break;
    }
}

void EnMaYto_BarnChooseNextDialogue(EnMaYto* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x33A9:
                func_80B90E50(this, 0);
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                EnMaYto_SetRomaniFaceExpression(this, 0, 3);
                Message_StartTextbox(play, 0x33AA, &this->actor);
                this->textId = 0x33AA;
                break;

            case 0x33AA:
                Actor_ChangeFocus(&this->actor, play, &this->actor);
                this->unk31E = 1;
                Message_StartTextbox(play, 0x33AB, &this->actor);
                this->textId = 0x33AB;
                break;

            case 0x33AB:
                func_80B90E50(this, 1);
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                EnMaYto_SetRomaniFaceExpression(this, 0, 1);
                Message_StartTextbox(play, 0x33AC, &this->actor);
                this->textId = 0x33AC;
                break;

            case 0x33AC:
                this->unk31E = 0;
                Actor_ChangeFocus(&this->actor, play, &this->actor);
                Message_StartTextbox(play, 0x33AD, &this->actor);
                this->textId = 0x33AD;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            case 0x33AE:
                func_80B90E50(this, 1);
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                EnMaYto_SetRomaniFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x33AF, &this->actor);
                this->textId = 0x33AF;
                break;

            case 0x33AF:
                this->unk31E = 1;
                Actor_ChangeFocus(&this->actor, play, &this->actor);
                EnMaYto_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x33B0, &this->actor);
                this->textId = 0x33B0;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            case 0x33B1:
                this->unk31E = 2;
                EnMaYto_SetFaceExpression(this, 5, 3);
                // "I should had believed what Romani said"
                Message_StartTextbox(play, 0x33B2, &this->actor);
                this->textId = 0x33B2;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                break;

            case 0x33C6:
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                this->unk31E = 0;
                EnMaYto_SetFaceExpression(this, 0, 1);
                Message_StartTextbox(play, 0x33C7, &this->actor);
                this->textId = 0x33C7;
                break;

            case 0x33C7:
                Actor_ChangeFocus(&this->actor, play, &this->actor);
                this->unk31E = 1;
                EnMaYto_SetFaceExpression(this, 0, 1);
                Message_StartTextbox(play, 0x33C8, &this->actor);
                this->textId = 0x33C8;
                break;

            case 0x33C8:
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                func_80B90E50(this, 1);
                EnMaYto_SetRomaniFaceExpression(this, 0, 2);
                Message_StartTextbox(play, 0x33C9, &this->actor);
                this->textId = 0x33C9;
                break;

            case 0x33C9:
                Actor_ChangeFocus(&this->actor, play, &this->actor);
                this->unk31E = 1;
                EnMaYto_SetFaceExpression(this, 3, 1);
                Message_StartTextbox(play, 0x33CA, &this->actor);
                this->textId = 0x33CA;
                break;

            case 0x33CA:
                this->unk31E = 1;
                Message_StartTextbox(play, 0x33CB, &this->actor);
                this->textId = 0x33CB;
                break;

            case 0x33CB:
                Actor_ChangeFocus(&this->actor, play, this->actor.child);
                func_80B90E50(this, 1);
                EnMaYto_SetRomaniFaceExpression(this, 3, 3);
                Message_StartTextbox(play, 0x33CC, &this->actor);
                this->textId = 0x33CC;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            default:
                break;
        }
    }
}

void EnMaYto_SetupAfterMilkRunInit(EnMaYto* this) {
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_ESCORTED_CREMIA)) {
        EnMaYto_SetFaceExpression(this, 3, 1);
    } else {
        Audio_PlayFanfare(NA_BGM_FAILURE_1);
        EnMaYto_SetFaceExpression(this, 5, 2);
    }
    this->actionFunc = EnMaYto_AfterMilkRunInit;
}

void EnMaYto_AfterMilkRunInit(EnMaYto* this, PlayState* play) {
    this->actor.flags |= ACTOR_FLAG_10000;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_ESCORTED_CREMIA)) {
            Message_StartTextbox(play, 0x33C1, &this->actor);
            this->textId = 0x33C1;
        } else {
            // Failed milk minigame
            EnMaYto_SetFaceExpression(this, 5, 2);
            Message_StartTextbox(play, 0x33C0, &this->actor);
            this->textId = 0x33C0;
            SET_WEEKEVENTREG(WEEKEVENTREG_14_01);
            this->unk310 = 4;
            EnMaYto_SetupPostMilkRunWaitDialogueEnd(this);
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
            return;
        }

        EnMaYto_SetupAfterMilkRunDialogueHandler(this);
    } else {
        Actor_OfferTalk(&this->actor, play, 200.0f);
    }
}

void EnMaYto_SetupAfterMilkRunDialogueHandler(EnMaYto* this) {
    this->actionFunc = EnMaYto_AfterMilkRunDialogueHandler;
}

void EnMaYto_AfterMilkRunDialogueHandler(EnMaYto* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
        case TEXT_STATE_CHOICE:
        case TEXT_STATE_DONE:
            break;

        case TEXT_STATE_5:
            EnMaYto_AfterMilkRunChooseNextDialogue(this, play);
            break;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x71C, 0xB6);
}

void EnMaYto_AfterMilkRunChooseNextDialogue(EnMaYto* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x33C1:
                EnMaYto_SetFaceExpression(this, 3, 1);
                // "Thank you. You were cool back there."
                Message_StartTextbox(play, 0x33C2, &this->actor);
                this->textId = 0x33C2;
                break;

            case 0x33C2:
                Message_CloseTextbox(play);
                EnMaYto_SetupPostMilkRunGiveReward(this);
                EnMaYto_PostMilkRunGiveReward(this, play);
                break;

            default:
                break;
        }
    }
}

void EnMaYto_SetupPostMilkRunGiveReward(EnMaYto* this) {
    this->actionFunc = EnMaYto_PostMilkRunGiveReward;
}

void EnMaYto_PostMilkRunGiveReward(EnMaYto* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        EnMaYto_SetupPostMilkRunExplainReward(this);
    } else if (INV_CONTENT(ITEM_MASK_ROMANI) == ITEM_MASK_ROMANI) {
        Actor_OfferGetItem(&this->actor, play, GI_RUPEE_HUGE, 500.0f, 100.0f);
        this->unk310 = 2;
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_MASK_ROMANI, 500.0f, 100.0f);
        this->unk310 = 1;
    }
}

void EnMaYto_SetupPostMilkRunExplainReward(EnMaYto* this) {
    this->actionFunc = EnMaYto_PostMilkRunExplainReward;
}

void EnMaYto_PostMilkRunExplainReward(EnMaYto* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (this->unk310 == 1) {
            // Romani's mask explanation
            EnMaYto_SetFaceExpression(this, 0, 1);
            Message_StartTextbox(play, 0x33C3, &this->actor);
            this->textId = 0x33C3;
            SET_WEEKEVENTREG(WEEKEVENTREG_14_01);
            this->unk310 = 3;
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_RECEIVED_ROMANIS_MASK);
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_ESCORTED_CREMIA);
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
            EnMaYto_SetupPostMilkRunWaitDialogueEnd(this);
        } else {
            // You already have the mask
            EnMaYto_SetFaceExpression(this, 0, 1);
            Message_StartTextbox(play, 0x33D0, &this->actor);
            this->textId = 0x33D0;
            SET_WEEKEVENTREG(WEEKEVENTREG_14_01);
            this->unk310 = 3;
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
            EnMaYto_SetupPostMilkRunWaitDialogueEnd(this);
        }
    } else {
        Actor_OfferTalkExchangeEquiCylinder(&this->actor, play, 200.0f, PLAYER_IA_MINUS1);
    }
}

void EnMaYto_SetupBeginWarmFuzzyFeelingCs(EnMaYto* this) {
    this->actionFunc = EnMaYto_BeginWarmFuzzyFeelingCs;
}

void EnMaYto_BeginWarmFuzzyFeelingCs(EnMaYto* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->actor.csId)) {
        CutsceneManager_Start(this->actor.csId, &this->actor);
        EnMaYto_SetupWarmFuzzyFeelingCs(this);
    } else {
        if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
            CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        }
        CutsceneManager_Queue(this->actor.csId);
    }
}

void EnMaYto_SetupWarmFuzzyFeelingCs(EnMaYto* this) {
    EnMaYto_SetFaceExpression(this, 0, 1);
    this->actionFunc = EnMaYto_WarmFuzzyFeelingCs;
}

static u16 sCueId = 99;

void EnMaYto_WarmFuzzyFeelingCs(EnMaYto* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_556)) {
        s32 cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_556);

        if (play->csCtx.curFrame == play->csCtx.actorCues[cueChannel]->startFrame) {
            u16 cueId = play->csCtx.actorCues[cueChannel]->id;

            if (1) {}

            if (cueId != sCueId) {
                sCueId = cueId;
                switch (cueId) {
                    case 1:
                        EnMaYto_ChangeAnim(this, 0);
                        break;

                    case 2:
                        SET_WEEKEVENTREG(WEEKEVENTREG_14_01);
                        EnMaYto_ChangeAnim(this, 18);
                        break;

                    case 3:
                        EnMaYto_ChangeAnim(this, 22);
                        break;

                    default:
                        break;
                }
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
        if ((sCueId == 2) && (this->skelAnime.animation == &gCremiaHugStartAnim) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            EnMaYto_ChangeAnim(this, 20);
        }
    } else {
        sCueId = 99;
    }
}

void EnMaYto_SetupPostMilkRunWaitDialogueEnd(EnMaYto* this) {
    this->actionFunc = EnMaYto_PostMilkRunWaitDialogueEnd;
}

void EnMaYto_PostMilkRunWaitDialogueEnd(EnMaYto* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_DONE) || (Message_GetState(&play->msgCtx) == TEXT_STATE_5)) {
        if (Message_ShouldAdvance(play) && (Message_GetState(&play->msgCtx) == TEXT_STATE_5)) {
            func_800B7298(play, &this->actor, PLAYER_CSACTION_WAIT);
            Message_CloseTextbox(play);
        }
    }

    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) && (play->msgCtx.bombersNotebookEventQueueCount == 0)) {
        EnMaYto_SetupPostMilkRunEnd(this);
    }
}

void EnMaYto_SetupPostMilkRunEnd(EnMaYto* this) {
    this->actionFunc = EnMaYto_PostMilkRunEnd;
}

void EnMaYto_PostMilkRunEnd(EnMaYto* this, PlayState* play) {
    if (this->unk310 == 3) {
        play->nextEntrance = ENTRANCE(TERMINA_FIELD, 13);
    } else {
        play->nextEntrance = ENTRANCE(ROMANI_RANCH, 8);
    }
    gSaveContext.nextCutsceneIndex = 0;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_80;
    gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE;
}

void EnMaYto_DefaultStartDialogue(EnMaYto* this, PlayState* play) {
    if (CURRENT_DAY == 1) {
        if ((Player_GetMask(play) != PLAYER_MASK_NONE) && (GET_PLAYER_FORM == PLAYER_FORM_HUMAN)) {
            switch (Player_GetMask(play)) {
                case PLAYER_MASK_ROMANI:
                    Message_StartTextbox(play, 0x235D, &this->actor);
                    this->textId = 0x235D;
                    break;

                case PLAYER_MASK_CIRCUS_LEADER:
                    EnMaYto_SetFaceExpression(this, 1, 3);
                    Message_StartTextbox(play, 0x235E, &this->actor);
                    this->textId = 0x235E;
                    break;

                case PLAYER_MASK_KAFEIS_MASK:
                    EnMaYto_SetFaceExpression(this, 1, 2);
                    Message_StartTextbox(play, 0x235F, &this->actor);
                    this->textId = 0x235F;
                    break;

                case PLAYER_MASK_COUPLE:
                    Message_StartTextbox(play, 0x2360, &this->actor);
                    this->textId = 0x2360;
                    break;

                default:
                    Message_StartTextbox(play, 0x2361, &this->actor);
                    this->textId = 0x2361;
                    break;
            }
        } else {
            if (EnMaYto_HasSpokenToPlayer()) {
                Message_StartTextbox(play, 0x3394, &this->actor);
                this->textId = 0x3394;
            } else {
                EnMaYto_SetTalkedFlag();
                // Asks the player if he came from town.
                Message_StartTextbox(play, 0x3390, &this->actor);
                this->textId = 0x3390;
            }
        }
    } else if (CURRENT_DAY == 3) {
        if (EnMaYto_HasSpokenToPlayerToday()) {
            EnMaYto_SetFaceExpression(this, 0, 3);
            Message_StartTextbox(play, 0x33C5, &this->actor);
            this->textId = 0x33C5;
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
        } else {
            EnMaYto_SetTalkedFlag();
            EnMaYto_SetFaceExpression(this, 0, 3);
            Message_StartTextbox(play, 0x33C4, &this->actor);
            this->textId = 0x33C4;
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
        }
    }
}

void EnMaYto_DinnerStartDialogue(EnMaYto* this, PlayState* play) {
    switch (CURRENT_DAY) {
        case 1:
            if ((Player_GetMask(play) != PLAYER_MASK_NONE) && (GET_PLAYER_FORM == PLAYER_FORM_HUMAN)) {
                switch (Player_GetMask(play)) {
                    case PLAYER_MASK_ROMANI:
                        Message_StartTextbox(play, 0x235D, &this->actor);
                        this->textId = 0x235D;
                        break;

                    case PLAYER_MASK_CIRCUS_LEADER:
                        Message_StartTextbox(play, 0x235E, &this->actor);
                        this->textId = 0x235E;
                        break;

                    case PLAYER_MASK_KAFEIS_MASK:
                        Message_StartTextbox(play, 0x235F, &this->actor);
                        this->textId = 0x235F;
                        break;

                    case PLAYER_MASK_COUPLE:
                        Message_StartTextbox(play, 0x2360, &this->actor);
                        this->textId = 0x2360;
                        break;

                    default:
                        Message_StartTextbox(play, 0x2361, &this->actor);
                        this->textId = 0x2361;
                        break;
                }
            } else {
                if (EnMaYto_HasSpokenToPlayer()) {
                    Message_StartTextbox(play, 0x339F, &this->actor);
                    this->textId = 0x339F;
                } else {
                    EnMaYto_SetTalkedFlag();
                    Message_StartTextbox(play, 0x3397, &this->actor);
                    this->textId = 0x3397;
                }
            }
            break;

        case 2:
            if (EnMaYto_HasSpokenToPlayer()) {
                Message_StartTextbox(play, 0x33A6, &this->actor);
                this->textId = 0x33A6;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
            } else {
                EnMaYto_SetTalkedFlag();
                Message_StartTextbox(play, 0x33A5, &this->actor);
                this->textId = 0x33A5;
            }
            break;

        case 3:
            if (EnMaYto_HasSpokenToPlayer()) {
                Message_StartTextbox(play, 0x33A8, &this->actor);
                this->textId = 0x33A8;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
            } else {
                EnMaYto_SetTalkedFlag();
                Message_StartTextbox(play, 0x33A7, &this->actor);
                this->textId = 0x33A7;
            }
            break;

        default:
            break;
    }
}

void EnMaYto_BarnStartDialogue(EnMaYto* this, PlayState* play) {
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        if (CURRENT_DAY == 2) {
            if (this->unk310 == 1) {
                Message_StartTextbox(play, 0x33AE, &this->actor);
                this->textId = 0x33AE;
            } else {
                this->unk310 = 1;
                EnMaYto_SetTalkedFlag();
                Message_StartTextbox(play, 0x33A9, &this->actor);
                this->textId = 0x33A9;
            }
        } else if (CURRENT_DAY == 3) {
            if (this->unk310 == 1) {
                Message_StartTextbox(play, 0x33CB, &this->actor);
                this->textId = 0x33CB;
            } else {
                this->unk310 = 1;
                EnMaYto_SetTalkedFlag();
                EnMaYto_SetFaceExpression(this, 0, 1);
                Message_StartTextbox(play, 0x33C6, &this->actor);
                this->textId = 0x33C6;
            }
        }
    } else {
        if (EnMaYto_HasSpokenToPlayer()) {
            this->unk31E = 2;
            EnMaYto_SetFaceExpression(this, 5, 3);
            Message_StartTextbox(play, 0x33B3, &this->actor);
            this->textId = 0x33B3;
            Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_CREMIA);
        } else {
            EnMaYto_SetTalkedFlag();
            EnMaYto_SetFaceExpression(this, 5, 3);
            Message_StartTextbox(play, 0x33B1, &this->actor);
            this->textId = 0x33B1;
        }
    }
}

void EnMaYto_ChangeAnim(EnMaYto* this, s32 animIndex) {
    Animation_Change(&this->skelAnime, sAnimationInfo[animIndex].animation, 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationInfo[animIndex].animation), sAnimationInfo[animIndex].mode,
                     sAnimationInfo[animIndex].morphFrames);
}

void func_80B90C78(EnMaYto* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 trackingMode;

    SkelAnime_Update(&this->skelAnime);
    trackingMode = (this->unk31E == 2) ? NPC_TRACKING_NONE : NPC_TRACKING_PLAYER_AUTO_TURN;

    if (this->unk31E == 0) {
        this->interactInfo.trackPos = player->actor.world.pos;
        this->interactInfo.yOffset = 0.0f;
    } else if (this->unk31E == 1) {
        Math_Vec3f_StepTo(&this->interactInfo.trackPos, &this->actor.child->world.pos, 8.0f);
        this->interactInfo.yOffset = 0.0f;
    }

    if (this->unk320 == 0) {
        if (this->actionFunc == EnMaYto_WarmFuzzyFeelingCs) {
            this->interactInfo.headRot.y = 0;
            this->interactInfo.headRot.x = 0;
        } else {
            Npc_TrackPoint(&this->actor, &this->interactInfo, 13, trackingMode);
        }
    } else {
        Math_SmoothStepToS(&this->interactInfo.headRot.y, 0, 3, 0x71C, 0xB6);
        Math_SmoothStepToS(&this->interactInfo.headRot.x, 0x18E3, 5, 0x71C, 0xB6);
    }

    EnMaYto_UpdateEyes(this);
}

void EnMaYto_UpdateCollision(EnMaYto* this, PlayState* play) {
    if (this->actionFunc != EnMaYto_WarmFuzzyFeelingCs) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void EnMaYto_UpdateEyes(EnMaYto* this) {
    if (this->overrideEyeTexIndex != 0) {
        this->eyeTexIndex = this->overrideEyeTexIndex;
    } else if (this->blinkTimer == 100) {
        if (this->eyeTexIndex == 0) {
            this->blinkTimer = 0;
        } else {
            this->eyeTexIndex--;
        }
    } else {
        this->blinkTimer++;
        if (this->blinkTimer == 100) {
            this->eyeTexIndex = 2;
        }
    }
}

// EnMaYto_SetRomani... something
void func_80B90E50(EnMaYto* this, s16 arg1) {
    EnMaYts* romani = (EnMaYts*)this->actor.child;

    if ((romani != NULL) && (romani->actor.id == ACTOR_EN_MA_YTS)) {
        romani->unk_32C = arg1;
    }
}

void EnMaYto_SetRomaniFaceExpression(EnMaYto* this, s16 overrideEyeTexIndex, s16 mouthTexIndex) {
    EnMaYts* romani = (EnMaYts*)this->actor.child;

    if ((romani != NULL) && (romani->actor.id == ACTOR_EN_MA_YTS)) {
        romani->overrideEyeTexIndex = overrideEyeTexIndex;
        romani->mouthTexIndex = mouthTexIndex;
    }
}

void EnMaYto_SetFaceExpression(EnMaYto* this, s16 overrideEyeTexIndex, s16 mouthIndex) {
    this->overrideEyeTexIndex = overrideEyeTexIndex;
    this->mouthTexIndex = mouthIndex;
}

void EnMaYto_InitFaceExpression(EnMaYto* this) {
    if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        EnMaYto_SetFaceExpression(this, 0, 1);
        EnMaYto_SetRomaniFaceExpression(this, 0, 0);
    } else {
        EnMaYto_SetFaceExpression(this, 5, 2);
        EnMaYto_SetRomaniFaceExpression(this, 1, 2);
    }
}

s32 EnMaYto_HasSpokenToPlayerToday(void) {
    switch (CURRENT_DAY) {
        case 1:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_04)) {
                return true;
            }
            break;

        case 2:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_08)) {
                return true;
            }
            break;

        case 3:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_10)) {
                return true;
            }
            break;

        default:
            break;
    }
    return false;
}

s32 EnMaYto_HasSpokenToPlayer(void) {
    switch (CURRENT_DAY) {
        case 3:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_10)) {
                return true;
            }
            // fallthrough
        case 2:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_08)) {
                return true;
            }
            // fallthrough
        case 1:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_13_04)) {
                return true;
            }
            break;

        default:
            break;
    }
    return false;
}

void EnMaYto_SetTalkedFlag(void) {
    switch (CURRENT_DAY) {
        case 1:
            SET_WEEKEVENTREG(WEEKEVENTREG_13_04);
            break;

        case 2:
            SET_WEEKEVENTREG(WEEKEVENTREG_13_08);
            break;

        case 3:
            SET_WEEKEVENTREG(WEEKEVENTREG_13_10);
            break;

        default:
            break;
    }
}

void EnMaYto_Update(Actor* thisx, PlayState* play) {
    EnMaYto* this = THIS;

    this->actionFunc(this, play);
    EnMaYto_UpdateCollision(this, play);
    func_80B90C78(this, play);
}

s32 EnMaYto_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMaYto* this = THIS;
    Vec3s limbRot;

    if (limbIndex == CREMIA_LIMB_HEAD) {
        limbRot = this->interactInfo.headRot;

        rot->x += limbRot.y;
        rot->z += limbRot.x;
    } else if (limbIndex == CREMIA_LIMB_TORSO) {
        if ((this->skelAnime.animation != &gCremiaSittingPetCowAnim) &&
            (this->skelAnime.animation != &gCremiaSittingLookDownAnim)) {
            limbRot = this->interactInfo.torsoRot;

            rot->x += limbRot.y;
            if ((this->skelAnime.animation == &gCremiaIdleAnim) || (this->skelAnime.animation == &gCremiaSittingAnim) ||
                (this->skelAnime.animation == &gCremiaSittingLookDownAnim)) {
                rot->z += limbRot.x;
            }
        }
    }
    return false;
}

void EnMaYto_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMaYto* this = THIS;

    if (limbIndex == CREMIA_LIMB_HEAD) {
        Matrix_MultZero(&this->actor.focus.pos);
    }
}

void EnMaYto_Draw(Actor* thisx, PlayState* play) {
    EnMaYto* this = THIS;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    if ((this->type == MA_YTO_TYPE_BARN) && CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gCremiaWoodenBoxDL);
    }
    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyesTextures[this->eyeTexIndex]));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMaYto_OverrideLimbDraw, EnMaYto_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
