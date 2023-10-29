/*
 * File: z_en_ma_yts.c
 * Overlay: ovl_En_Ma_Yts
 * Description: Romani. As opposed as EnMa4, this actor is used in conjunction with another actor, like EnMaYto.
 */

#include "z_en_ma_yts.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, PlayState* play);
void EnMaYts_Destroy(Actor* thisx, PlayState* play);
void EnMaYts_Update(Actor* thisx, PlayState* play);
void EnMaYts_Draw(Actor* thisx, PlayState* play);

void EnMaYts_SetupDoNothing(EnMaYts* this);
void EnMaYts_DoNothing(EnMaYts* this, PlayState* play);
void EnMaYts_SetupStartDialogue(EnMaYts* this);
void EnMaYts_StartDialogue(EnMaYts* this, PlayState* play);
void EnMaYts_SetupDialogueHandler(EnMaYts* this);
void EnMaYts_DialogueHandler(EnMaYts* this, PlayState* play);
void EnMaYts_SetupEndCreditsHandler(EnMaYts* this);
void EnMaYts_EndCreditsHandler(EnMaYts* this, PlayState* play);
void EnMaYts_ChooseNextDialogue(EnMaYts* this, PlayState* play);

void EnMaYts_SetFaceExpression(EnMaYts* this, s16 overrideEyeTexIndex, s16 mouthTexIndex);

void EnMaYts_DrawSleeping(Actor* thisx, PlayState* play);

ActorInit En_Ma_Yts_InitVars = {
    /**/ ACTOR_EN_MA_YTS,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_MA1,
    /**/ sizeof(EnMaYts),
    /**/ EnMaYts_Init,
    /**/ EnMaYts_Destroy,
    /**/ EnMaYts_Update,
    /**/ EnMaYts_Draw,
};

void EnMaYts_UpdateEyes(EnMaYts* this) {
    if (this->overrideEyeTexIndex != 0) {
        this->eyeTexIndex = this->overrideEyeTexIndex;
    } else if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= 3) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}

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
    { &gRomaniIdleAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniIdleAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSingStartAnim, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &gRomaniSingStartAnim, 1.0f, ANIMMODE_ONCE, -6.0f },
    { &gRomaniSingLoopAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSingLoopAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniRunAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniRunAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniWalkAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniWalkAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniLookAroundAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniLookAroundAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniShootBowAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniShootBowAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSittingAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSittingAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSittingHeadShakeAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSittingHeadShakeAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniSittingLookDownAnim, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &gRomaniSittingLookDownAnim, 1.0f, ANIMMODE_LOOP, -6.0f },
    { &gRomaniTurnAroundAndFlickHairAnim, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &gRomaniTurnAroundAndFlickHairAnim, 1.0f, ANIMMODE_ONCE, -6.0f },
};

static TexturePtr sMouthTextures[] = {
    gRomaniMouthHappyTex,
    gRomaniMouthFrownTex,
    gRomaniMouthHangingOpenTex,
    gRomaniMouthSmileTex,
};

static TexturePtr sEyeTextures[] = {
    gRomaniEyeOpenTex, gRomaniEyeHalfTex, gRomaniEyeClosedTex, gRomaniEyeHappyTex, gRomaniEyeSadTex,
};

void EnMaYts_ChangeAnim(EnMaYts* this, s32 animIndex) {
    Animation_Change(&this->skelAnime, sAnimationInfo[animIndex].animation, 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationInfo[animIndex].animation), sAnimationInfo[animIndex].mode,
                     sAnimationInfo[animIndex].morphFrames);
}

void func_80B8D12C(EnMaYts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 trackingMode = (this->unk_32C == 2) ? NPC_TRACKING_NONE : NPC_TRACKING_PLAYER_AUTO_TURN;

    if ((this->unk_32C == 0) || (this->actor.parent == NULL)) {
        this->interactInfo.trackPos = player->actor.world.pos;
        this->interactInfo.trackPos.y -= -10.0f;
    } else {
        Math_Vec3f_StepTo(&this->interactInfo.trackPos, &this->actor.parent->world.pos, 8.0f);
        this->interactInfo.trackPos.y -= -10.0f;
    }

    Npc_TrackPoint(&this->actor, &this->interactInfo, 0, trackingMode);
}

void EnMaYts_InitAnimation(EnMaYts* this, PlayState* play) {
    switch (this->type) {
        case MA_YTS_TYPE_BARN:
            this->actor.targetMode = TARGET_MODE_0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case MA_YTS_TYPE_SITTING:
            this->actor.targetMode = TARGET_MODE_6;
            // Day 1 or "Winning" the alien invasion
            if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                EnMaYts_ChangeAnim(this, 14);
            } else {
                EnMaYts_ChangeAnim(this, 18);
            }
            break;

        case MA_YTS_TYPE_SLEEPING:
            this->actor.targetMode = TARGET_MODE_0;
            this->actor.draw = EnMaYts_DrawSleeping;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case MA_YTS_TYPE_ENDCREDITS:
            this->actor.targetMode = TARGET_MODE_0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        default:
            EnMaYts_ChangeAnim(this, 0);
            break;
    }
}

s32 EnMaYts_CheckValidSpawn(EnMaYts* this, PlayState* play) {
    switch (this->type) {
        case MA_YTS_TYPE_SITTING:
            switch (CURRENT_DAY) {
                case 1:
                    break;

                case 2:
                    // Failing the alien invasion
                    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                        return false;
                    }
                    break;

                case 3:
                    // "Winning" the alien invasion
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                        return false;
                    }
                    break;

                default:
                    break;
            }
            break;

        case MA_YTS_TYPE_BARN:
            // Failing the alien invasion
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                return false;
            } else if ((gSaveContext.save.time >= CLOCK_TIME(20, 0)) && (CURRENT_DAY == 3)) {
                return false;
            }
            break;

        case MA_YTS_TYPE_SLEEPING:
            // "Winning" the alien invasion
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
                return false;
            }
            break;

        case MA_YTS_TYPE_ENDCREDITS:
            break;

        default:
            break;
    }

    return true;
}

void EnMaYts_Init(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;
    s32 pad;

    this->type = EN_MA_YTS_GET_TYPE(thisx);
    if (!EnMaYts_CheckValidSpawn(this, play)) {
        Actor_Kill(&this->actor);
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, NULL, this->jointTable, this->morphTable, ROMANI_LIMB_MAX);
    EnMaYts_InitAnimation(this, play);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit2);

    if (this->type == MA_YTS_TYPE_SLEEPING) {
        this->collider.dim.radius = 40;
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
    Actor_SetScale(&this->actor, 0.01f);

    this->interactInfo.talkState = NPC_TALK_STATE_IDLE;
    this->unk_200 = 0;
    this->blinkTimer = 0;

    if (this->type == MA_YTS_TYPE_ENDCREDITS) {
        this->hasBow = true;
    } else {
        this->hasBow = false;
    }

    if ((CURRENT_DAY == 1) || CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        this->overrideEyeTexIndex = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 0;
    } else {
        this->overrideEyeTexIndex = 1;
        this->eyeTexIndex = 1;
        this->mouthTexIndex = 2;
        this->unk_32C = 2;
    }

    if (this->type == MA_YTS_TYPE_ENDCREDITS) {
        this->overrideEyeTexIndex = 0;
        this->eyeTexIndex = 0;
        this->mouthTexIndex = 0;
        this->unk_32C = 2;
        EnMaYts_SetupEndCreditsHandler(this);
    } else if ((CURRENT_DAY == 2) && (gSaveContext.save.isNight == 1) &&
               CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) {
        EnMaYts_SetupStartDialogue(this);
    } else {
        EnMaYts_SetupDoNothing(this);
    }
}

void EnMaYts_Destroy(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnMaYts_SetupDoNothing(EnMaYts* this) {
    this->actionFunc = EnMaYts_DoNothing;
}

void EnMaYts_DoNothing(EnMaYts* this, PlayState* play) {
}

void EnMaYts_SetupStartDialogue(EnMaYts* this) {
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_StartDialogue;
}

void EnMaYts_StartDialogue(EnMaYts* this, PlayState* play) {
    s16 sp26 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (GET_PLAYER_FORM != PLAYER_FORM_HUMAN) {
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_65_80)) {
                // Saying to non-human Link: "Cremia went to town."
                SET_WEEKEVENTREG(WEEKEVENTREG_65_80);
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x335F, &this->actor);
                this->textId = 0x335F;
            } else {
                // Saying to non-human Link: "Pretend you did not hear that."
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x3362, &this->actor);
                this->textId = 0x3362;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
            }
        } else if (Player_GetMask(play) != PLAYER_MASK_NONE) {
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_65_40)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_65_40);
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x3363, &this->actor);
                this->textId = 0x3363;
            } else {
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3366, &this->actor);
                this->textId = 0x3366;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
            }
        } else if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_PROMISED_TO_HELP_WITH_THEM)) {
            EnMaYts_SetFaceExpression(this, 0, 0);
            Message_StartTextbox(play, 0x3367, &this->actor);
            this->textId = 0x3367;
        } else {
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_65_20)) {
                // Saying to Grasshopper: "Cremia went to town."
                SET_WEEKEVENTREG(WEEKEVENTREG_65_20);
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3369, &this->actor);
                this->textId = 0x3369;
            } else {
                // Saying to Grasshopper: "You're our bodyguard."
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x336C, &this->actor);
                this->textId = 0x336C;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
            }
        }
        EnMaYts_SetupDialogueHandler(this);
    } else if (ABS_ALT(sp26) < 0x4000) {
        Actor_OfferTalk(&this->actor, play, 120.0f);
    }
}

void EnMaYts_SetupDialogueHandler(EnMaYts* this) {
    this->actionFunc = EnMaYts_DialogueHandler;
}

void EnMaYts_DialogueHandler(EnMaYts* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_5: // End message block
            EnMaYts_ChooseNextDialogue(this, play);
            break;

        case TEXT_STATE_DONE: // End conversation
            if (Message_ShouldAdvance(play)) {
                EnMaYts_SetupStartDialogue(this);
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

void EnMaYts_SetupEndCreditsHandler(EnMaYts* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_EndCreditsHandler;
}

static u16 sCueId = 99;
void EnMaYts_EndCreditsHandler(EnMaYts* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_120)) {
        s32 cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_120);

        if (play->csCtx.curFrame == play->csCtx.actorCues[cueChannel]->startFrame) {
            if (sCueId != play->csCtx.actorCues[cueChannel]->id) {
                sCueId = play->csCtx.actorCues[cueChannel]->id;
                this->endCreditsFlag = 0;
                switch (play->csCtx.actorCues[cueChannel]->id) {
                    case 1:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 0);
                        break;

                    case 2:
                        this->hasBow = false;
                        EnMaYts_ChangeAnim(this, 2);
                        break;

                    case 3:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 12);
                        break;

                    case 4:
                        this->hasBow = true;
                        EnMaYts_ChangeAnim(this, 20);
                        break;

                    default:
                        break;
                }
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
        if ((sCueId == 2) && (this->endCreditsFlag == 0) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->endCreditsFlag++;
            EnMaYts_ChangeAnim(this, 5);
        }
    } else {
        sCueId = 99;
        this->hasBow = true;
    }
}

// Select the following dialogue based on the current one, and an appropiate face expression
void EnMaYts_ChooseNextDialogue(EnMaYts* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x335F:
                EnMaYts_SetFaceExpression(this, 0, 2);
                Message_StartTextbox(play, 0x3360, &this->actor);
                this->textId = 0x3360;
                break;

            case 0x3360:
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x3361, &this->actor);
                this->textId = 0x3361;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            case 0x3363:
                EnMaYts_SetFaceExpression(this, 1, 1);
                Message_StartTextbox(play, 0x3364, &this->actor);
                this->textId = 0x3364;
                break;

            case 0x3364:
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(play, 0x3365, &this->actor);
                this->textId = 0x3365;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            case 0x3367:
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(play, 0x3368, &this->actor);
                this->textId = 0x3368;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            case 0x3369:
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(play, 0x336A, &this->actor);
                this->textId = 0x336A;
                break;

            case 0x336A:
                EnMaYts_SetFaceExpression(this, 3, 3);
                Message_StartTextbox(play, 0x336B, &this->actor);
                this->textId = 0x336B;
                Message_BombersNotebookQueueEvent(play, BOMBERS_NOTEBOOK_EVENT_MET_ROMANI);
                break;

            default:
                break;
        }
    }
}

void EnMaYts_SetFaceExpression(EnMaYts* this, s16 overrideEyeTexIndex, s16 mouthTexIndex) {
    this->overrideEyeTexIndex = overrideEyeTexIndex;
    this->mouthTexIndex = mouthTexIndex;
    if (this->overrideEyeTexIndex == 0) {
        this->eyeTexIndex = 0;
    }
}

void EnMaYts_Update(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;
    ColliderCylinder* collider;

    this->actionFunc(this, play);
    collider = &this->collider;
    Collider_UpdateCylinder(&this->actor, collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &collider->base);
    SkelAnime_Update(&this->skelAnime);
    EnMaYts_UpdateEyes(this);
    func_80B8D12C(this, play);
}

s32 EnMaYts_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMaYts* this = THIS;
    Vec3s limbRot;

    if (limbIndex == ROMANI_LIMB_HEAD) {
        limbRot = this->interactInfo.headRot;
        rot->x += limbRot.y;
        if ((this->skelAnime.animation == &gRomaniIdleAnim) || (this->skelAnime.animation == &gRomaniSittingAnim)) {
            rot->z += limbRot.x;
        }
    } else if (limbIndex == ROMANI_LIMB_TORSO) {
        limbRot = this->interactInfo.torsoRot;
        rot->x += limbRot.y;
        rot->z += limbRot.x;
    }

    return false;
}

void EnMaYts_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMaYts* this = THIS;

    if (limbIndex == ROMANI_LIMB_HEAD) {
        Matrix_MultZero(&this->actor.focus.pos);
    } else if (limbIndex == ROMANI_LIMB_LEFT_HAND) {
        if (this->hasBow == true) {
            OPEN_DISPS(play->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, gRomaniBowDL);

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}

void EnMaYts_Draw(Actor* thisx, PlayState* play) {
    EnMaYts* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_K0(sMouthTextures[this->mouthTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_K0(sEyeTextures[this->eyeTexIndex]));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMaYts_OverrideLimbDraw, EnMaYts_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

// Alternative draw function
void EnMaYts_DrawSleeping(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gRomaniSleepingDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
