/*
 * File: z_en_mk.c
 * Overlay: ovl_En_Mk
 * Description: Marine Researcher
 */

#include "z_en_mk.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnMk*)thisx)

void EnMk_Init(Actor* thisx, PlayState* play);
void EnMk_Destroy(Actor* thisx, PlayState* play);
void EnMk_Update(Actor* thisx, PlayState* play);
void EnMk_Draw(Actor* thisx, PlayState* play);

s32 func_80959524(PlayState* play);
void func_809596A0(EnMk* this, PlayState* play);
void func_80959774(EnMk* this, PlayState* play);
void func_80959A24(EnMk* this, PlayState* play);
void func_80959C94(EnMk* this, PlayState* play);
void func_80959D28(EnMk* this, PlayState* play);
void func_80959E18(EnMk* this, PlayState* play);

ActorInit En_Mk_InitVars = {
    /**/ ACTOR_EN_MK,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_MK,
    /**/ sizeof(EnMk),
    /**/ EnMk_Init,
    /**/ EnMk_Destroy,
    /**/ EnMk_Update,
    /**/ EnMk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
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
    { 30, 40, 0, { 0, 0, 0 } },
};

s32 func_809592E0(EnMk* this, s16 index) {
    AnimationHeader* sAnimations[] = {
        &gMarineResearcherIdleAnim,        &gMarineResearcherHeadWaggleAnim, &gMarineResearcherYellAnim,
        &gMarineResearcherShakeInFearAnim, &gMarineResearcherStrokeChinAnim,
    };

    if (index == this->unk_27C) {
        return false;
    }

    if ((index < 0) || (index >= 5)) {
        return false;
    }

    Animation_PlayLoop(&this->skelAnime, sAnimations[index]);
    this->unk_27C = index;
    return true;
}

void EnMk_Init(Actor* thisx, PlayState* play) {
    EnMk* this = THIS;
    s16 csId;
    s32 i;

    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -1.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gMarineResearcherSkel, &gMarineResearcherIdleAnim, this->jointTable,
                       this->morphTable, MARINE_RESEARCHER_LIMB_MAX);

    this->unk_27C = -1;
    func_809592E0(this, 0);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    Actor_SetScale(&this->actor, 0.01f);

    this->actionFunc = func_80959E18;
    this->unk_27A = 0;
    this->actor.targetMode = TARGET_MODE_6;

    if (func_80959524(play) < 7) {
        this->unk_27A |= 2;
    }

    csId = this->actor.csId;
    for (i = 0; i < ARRAY_COUNT(this->csIdList); i++) {
        this->csIdList[i] = csId;
        if (csId != CS_ID_NONE) {
            this->actor.csId = csId;
            csId = CutsceneManager_GetAdditionalCsId(this->actor.csId);
        }
    }

    this->actor.csId = this->csIdList[0];
}

void EnMk_Destroy(Actor* thisx, PlayState* play) {
    EnMk* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

s32 func_80959524(PlayState* play) {
    return gSaveContext.save.saveInfo.permanentSceneFlags[play->sceneId].unk_14 & 7;
}

void func_8095954C(EnMk* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_127)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_127));

        switch (play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_127)]->id) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                func_809592E0(this, play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_127)]->id - 1);
                break;

            default:
                break;
        }
    } else {
        func_809592E0(this, 0);
    }
}

void func_80959624(EnMk* this, PlayState* play) {
    u16 textId;

    if (GET_PLAYER_FORM == PLAYER_FORM_ZORA) {
        if (this->unk_27A & 4) {
            textId = 0xFB9;
        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) {
            textId = 0xFBC;
        } else {
            textId = 0xFBB;
        }
    } else {
        textId = 0xFBA;
    }
    Message_StartTextbox(play, textId, &this->actor);
}

void func_809596A0(EnMk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if ((play->msgCtx.currentTextId == 0xFB9) || (play->msgCtx.currentTextId == 0xFBB) ||
        (play->msgCtx.currentTextId == 0xFBC)) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x400, 0x80);
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_5:
            if (Message_ShouldAdvance(play)) {
                Message_CloseTextbox(play);
                this->actionFunc = func_80959774;
            }
            break;

        case TEXT_STATE_CLOSING:
            this->actionFunc = func_80959774;
            break;
    }
}

void func_80959774(EnMk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 3, 0x400, 0x80);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80959624(this, play);
        this->actionFunc = func_809596A0;
    } else if ((this->actor.xzDistToPlayer < 120.0f) && Player_IsFacingActor(&this->actor, 0x3000, play)) {
        Actor_OfferTalk(&this->actor, play, 130.0f);
    }

    func_8095954C(this, play);
}

void func_80959844(EnMk* this, PlayState* play) {
    u16 textId;

    if ((this->unk_27A & 2) && (func_80959524(play) >= 7)) {
        textId = 0xFB3;
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_20_40)) {
        textId = 0xFB9;
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_19_40)) {
        textId = 0xFB5;
    } else if (func_80959524(play) >= 7) {
        textId = 0xFB3;
    } else {
        switch (GET_PLAYER_FORM) {
            case PLAYER_FORM_DEKU:
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_19_10)) {
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) {
                        textId = 0xFAF;
                    } else {
                        textId = 0xFAE;
                    }
                } else {
                    textId = 0xFAC;
                }
                break;

            case PLAYER_FORM_GORON:
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_19_08)) {
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) {
                        textId = 0xFAB;
                    } else {
                        textId = 0xFAA;
                    }
                } else {
                    textId = 0xFA8;
                }
                break;

            case PLAYER_FORM_FIERCE_DEITY:
            case PLAYER_FORM_HUMAN:
                if (func_80959524(play) > 0) {
                    textId = 0xFA7;
                } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_19_04)) {
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) {
                        textId = 0xFBF;
                    } else {
                        textId = 0xFA6;
                    }
                } else {
                    textId = 0xFA0;
                }
                break;

            default:
                if (func_80959524(play) > 0) {
                    textId = 0xFB0;
                } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_19_20)) {
                    textId = 0xFB2;
                } else {
                    textId = 0xFB1;
                }
                break;
        }
    }
    Message_StartTextbox(play, textId, &this->actor);
}

void func_80959A24(EnMk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    this->unk_27A |= 1;

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CLOSING:
            break;

        case TEXT_STATE_5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0xFA1:
                    case 0xFA3:
                    case 0xFA4:
                    case 0xFAA:
                    case 0xFAE:
                        Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0xFA2:
                        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) {
                            Message_CloseTextbox(play);
                            this->actionFunc = func_80959E18;
                        } else {
                            Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        }
                        break;

                    case 0xFA5:
                    case 0xFA6:
                    case 0xFA7:
                    case 0xFA9:
                    case 0xFAB:
                    case 0xFAD:
                    case 0xFAF:
                    case 0xFB0:
                    case 0xFB2:
                    case 0xFBD:
                    case 0xFBE:
                    case 0xFBF:
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80959E18;
                        break;

                    case 0xFA0:
                        SET_WEEKEVENTREG(WEEKEVENTREG_19_04);
                        Message_ContinueTextbox(play, 0xFA1);
                        break;

                    case 0xFA8:
                        SET_WEEKEVENTREG(WEEKEVENTREG_19_08);
                        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) {
                            Message_ContinueTextbox(play, 0xFBD);
                        } else {
                            Message_ContinueTextbox(play, 0xFA9);
                        }
                        break;

                    case 0xFAC:
                        SET_WEEKEVENTREG(WEEKEVENTREG_19_10);
                        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_GREAT_BAY_TEMPLE)) {
                            Message_ContinueTextbox(play, 0xFBE);
                        } else {
                            Message_ContinueTextbox(play, 0xFAD);
                        }
                        break;

                    case 0xFB1:
                        SET_WEEKEVENTREG(WEEKEVENTREG_19_20);
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80959E18;
                        break;

                    case 0xFB3:
                    case 0xFB4:
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80959E18;
                        this->actor.flags &= ~ACTOR_FLAG_10000;
                        break;

                    case 0xFB5:
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80959E18;
                        break;

                    default:
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80959E18;
                        break;
                }
            }
            break;
    }
}

void func_80959C94(EnMk* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80959A24;
        this->unk_27A &= ~2;
        Message_StartTextbox(play, 0xFB3, &this->actor);
    } else {
        this->actor.flags |= ACTOR_FLAG_10000;
        Actor_OfferTalkExchange(&this->actor, play, 350.0f, 1000.0f, PLAYER_IA_MINUS1);
    }
}

void func_80959D28(EnMk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if ((play->csCtx.state == CS_STATE_IDLE) && (this->actor.csId == CS_ID_NONE)) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_20_40)) {
            this->unk_27A &= ~1;
            this->actionFunc = func_80959774;
            this->actor.home.rot.y += 0x4E20;
            this->unk_27A |= 4;
        } else {
            this->actionFunc = func_80959E18;
        }
        this->actor.csId = this->csIdList[0];
    } else {
        if (this->actor.csId != CS_ID_NONE) {
            if (CutsceneManager_IsNext(this->actor.csId)) {
                CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
                this->actor.csId = CS_ID_NONE;
            } else {
                CutsceneManager_Queue(this->actor.csId);
            }
        }
        func_8095954C(this, play);
    }
}

void func_80959E18(EnMk* this, PlayState* play) {
    s32 pad;
    s16 sp22 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    SkelAnime_Update(&this->skelAnime);

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_20_40)) {
        this->unk_27A &= ~1;
        this->actionFunc = func_80959774;
        this->actor.home.rot.y += 0x4E20;
        return;
    }

    if (func_800B8718(&this->actor, &play->state)) {
        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
        this->actionFunc = func_80959D28;
        if (GET_PLAYER_FORM == PLAYER_FORM_ZORA) {
            this->actor.csId = this->csIdList[0];
            SET_WEEKEVENTREG(WEEKEVENTREG_20_40);
            Item_Give(play, ITEM_SONG_NOVA);
        } else {
            this->actor.csId = this->csIdList[1];
        }
        CutsceneManager_Queue(this->actor.csId);
    } else if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80959844(this, play);
        this->actionFunc = func_80959A24;
        this->unk_27A |= 1;
    } else if ((this->unk_27A & 2) && (func_80959524(play) >= 7)) {
        this->actionFunc = func_80959C94;
    } else if ((this->actor.xzDistToPlayer < 120.0f) && (ABS_ALT(sp22) <= 0x4300)) {
        this->unk_27A |= 1;
        Actor_OfferTalk(&this->actor, play, 200.0f);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_20_40) && CHECK_WEEKEVENTREG(WEEKEVENTREG_19_40)) {
            func_800B874C(&this->actor, play, 200.0f, 100.0f);
        }
    } else {
        this->unk_27A &= ~1;
    }
    func_8095954C(this, play);
}

void EnMk_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnMk* this = THIS;
    Vec3s sp38;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);

    this->actionFunc(this, play);

    if ((this->unk_27A & 1) && !Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_127)) {
        Actor_TrackPlayer(play, &this->actor, &this->unk_270, &sp38, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_270.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_270.y, 0, 6, 0x1838, 0x64);
    }
}

s32 EnMk_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMk* this = THIS;

    if (limbIndex == MARINE_RESEARCHER_LIMB_HEAD) {
        rot->y -= this->unk_270.y;
        rot->z += this->unk_270.x;
    }
    return false;
}

Vec3f D_8095A2A0 = { 1000.0f, -100.0f, 0.0f };

void EnMk_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMk* this = THIS;

    if (limbIndex == MARINE_RESEARCHER_LIMB_HEAD) {
        Matrix_MultVec3f(&D_8095A2A0, &this->actor.focus.pos);
    }
}

void EnMk_Draw(Actor* thisx, PlayState* play) {
    EnMk* this = THIS;

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMk_OverrideLimbDraw, EnMk_PostLimbDraw, &this->actor);
}
