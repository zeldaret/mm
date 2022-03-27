/*
 * File: z_en_ma_yts.c
 * Overlay: ovl_En_Ma_Yts
 * Description: Romani. As opposed as EnMa4, this actor is used in conjunction with another actor, like EnMaYto.
 */

#include "z_en_ma_yts.h"
#include "objects/object_ma1/object_ma1.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnMaYts*)thisx)

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnMaYts_SetupDoNothing(EnMaYts* this);
void EnMaYts_DoNothing(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_SetupStartDialogue(EnMaYts* this);
void EnMaYts_StartDialogue(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_SetupDialogueHandler(EnMaYts* this);
void EnMaYts_DialogueHandler(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_SetupEndCreditsHandler(EnMaYts* this);
void EnMaYts_EndCreditsHandler(EnMaYts* this, GlobalContext* globalCtx);
void EnMaYts_ChooseNextDialogue(EnMaYts* this, GlobalContext* globalCtx);

void EnMaYts_SetFaceExpression(EnMaYts* this, s16 overrideEyeTexIndex, s16 mouthTexIndex);

void EnMaYts_DrawSleeping(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Ma_Yts_InitVars = {
    ACTOR_EN_MA_YTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMaYts),
    (ActorFunc)EnMaYts_Init,
    (ActorFunc)EnMaYts_Destroy,
    (ActorFunc)EnMaYts_Update,
    (ActorFunc)EnMaYts_Draw,
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
    { &object_ma1_Anim_009E58, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_009E58, 1.0f, ANIMMODE_LOOP, -6.0f }, // Idle anim
    { &object_ma1_Anim_018948, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_ma1_Anim_018948, 1.0f, ANIMMODE_ONCE, -6.0f }, // Starts holding hands anim
    { &object_ma1_Anim_01B76C, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_01B76C, 1.0f, ANIMMODE_LOOP, -6.0f }, // Holnding hands anim
    { &object_ma1_Anim_007328, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_007328, 1.0f, ANIMMODE_LOOP, -6.0f }, // Walking anim
    { &object_ma1_Anim_014088, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_014088, 1.0f, ANIMMODE_LOOP, -6.0f }, //
    { &object_ma1_Anim_002A8C, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_002A8C, 1.0f, ANIMMODE_LOOP, -6.0f }, // Looking around anim
    { &object_ma1_Anim_015B7C, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_015B7C, 1.0f, ANIMMODE_LOOP, -6.0f }, // Shoot arrow anim
    { &object_ma1_Anim_007D98, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_007D98, 1.0f, ANIMMODE_LOOP, -6.0f }, // Sitting anim
    { &object_ma1_Anim_00852C, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_00852C, 1.0f, ANIMMODE_LOOP, -6.0f }, // Sitting traumatized anim
    { &object_ma1_Anim_008F6C, 1.0f, ANIMMODE_LOOP, 0.0f },
    { &object_ma1_Anim_008F6C, 1.0f, ANIMMODE_LOOP, -6.0f }, // Sitting sad anim
    { &object_ma1_Anim_0180DC, 1.0f, ANIMMODE_ONCE, 0.0f },
    { &object_ma1_Anim_0180DC, 1.0f, ANIMMODE_ONCE, -6.0f }, // Turns around anim
};

static TexturePtr sMouthTextures[] = {
    object_ma1_Tex_0127C8,
    object_ma1_Tex_012BC8,
    object_ma1_Tex_012FC8,
    object_ma1_Tex_0133C8,
};

static TexturePtr sEyeTextures[] = {
    object_ma1_Tex_00FFC8, object_ma1_Tex_0107C8, object_ma1_Tex_010FC8, object_ma1_Tex_0117C8, object_ma1_Tex_011FC8,
};

void EnMaYts_ChangeAnim(EnMaYts* this, s32 index) {
    Animation_Change(&this->skelAnime, sAnimationInfo[index].animation, 1.0f, 0.0f,
                     Animation_GetLastFrame(sAnimationInfo[index].animation), sAnimationInfo[index].mode,
                     sAnimationInfo[index].morphFrames);
}

void func_80B8D12C(EnMaYts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 flag = this->unk_32C == 2 ? true : false;

    if (this->unk_32C == 0 || this->actor.parent == NULL) {
        this->unk_1D8.unk_18 = player->actor.world.pos;
        this->unk_1D8.unk_18.y -= -10.0f;
    } else {
        Math_Vec3f_StepTo(&this->unk_1D8.unk_18, &this->actor.parent->world.pos, 8.0f);
        this->unk_1D8.unk_18.y -= -10.0f;
    }

    func_800BD888(&this->actor, &this->unk_1D8, 0, flag);
}

void EnMaYts_InitAnimation(EnMaYts* this, GlobalContext* globalCtx) {
    switch (this->type) {
        case MA_YTS_TYPE_BARN:
            this->actor.targetMode = 0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case MA_YTS_TYPE_SITTING:
            this->actor.targetMode = 6;
            // Day 1 or "Winning" the alien invasion
            if (CURRENT_DAY == 1 || (gSaveContext.save.weekEventReg[22] & 1)) {
                EnMaYts_ChangeAnim(this, 14);
            } else {
                EnMaYts_ChangeAnim(this, 18);
            }
            break;

        case MA_YTS_TYPE_SLEEPING:
            this->actor.targetMode = 0;
            this->actor.draw = EnMaYts_DrawSleeping;
            EnMaYts_ChangeAnim(this, 0);
            break;

        case MA_YTS_TYPE_ENDCREDITS:
            this->actor.targetMode = 0;
            EnMaYts_ChangeAnim(this, 0);
            break;

        default:
            EnMaYts_ChangeAnim(this, 0);
            break;
    }
}

s32 EnMaYts_CheckValidSpawn(EnMaYts* this, GlobalContext* globalCtx) {
    switch (this->type) {
        case MA_YTS_TYPE_SITTING:
            switch (CURRENT_DAY) {
                case 1:
                    break;

                case 2:
                    // Failing the alien invasion
                    if (!(gSaveContext.save.weekEventReg[22] & 1)) {
                        return false;
                    }
                    break;

                case 3:
                    // "Winning" the alien invasion
                    if (gSaveContext.save.weekEventReg[22] & 1) {
                        return false;
                    }
                    break;
            }
            break;

        case MA_YTS_TYPE_BARN:
            // Failing the alien invasion
            if (!(gSaveContext.save.weekEventReg[22] & 1)) {
                return false;
            } else if (gSaveContext.save.time >= CLOCK_TIME(20, 0) && CURRENT_DAY == 3) {
                return false;
            }
            break;

        case MA_YTS_TYPE_SLEEPING:
            // "Winning" the alien invasion
            if (gSaveContext.save.weekEventReg[22] & 1) {
                return false;
            }
            break;

        case MA_YTS_TYPE_ENDCREDITS:
            break;
    }

    return true;
}

void EnMaYts_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;
    s32 pad;

    this->type = EN_MA_YTS_PARSE_TYPE(thisx);
    if (!EnMaYts_CheckValidSpawn(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
    }

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_ma1_Skel_013928, NULL, this->jointTable, this->morphTable,
                       MA1_LIMB_MAX);
    EnMaYts_InitAnimation(this, globalCtx);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit2);

    if (this->type == MA_YTS_TYPE_SLEEPING) {
        this->collider.dim.radius = 40;
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 0x4);
    Actor_SetScale(&this->actor, 0.01f);

    this->unk_1D8.unk_00 = 0;
    this->unk_200 = 0;
    this->blinkTimer = 0;

    if (this->type == MA_YTS_TYPE_ENDCREDITS) {
        this->hasBow = true;
    } else {
        this->hasBow = false;
    }

    if (CURRENT_DAY == 1 || (gSaveContext.save.weekEventReg[22] & 1)) {
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
    } else if (CURRENT_DAY == 2 && gSaveContext.save.isNight == 1 && (gSaveContext.save.weekEventReg[22] & 1)) {
        EnMaYts_SetupStartDialogue(this);
    } else {
        EnMaYts_SetupDoNothing(this);
    }
}

void EnMaYts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnMaYts_SetupDoNothing(EnMaYts* this) {
    this->actionFunc = EnMaYts_DoNothing;
}

void EnMaYts_DoNothing(EnMaYts* this, GlobalContext* globalCtx) {
}

void EnMaYts_SetupStartDialogue(EnMaYts* this) {
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_StartDialogue;
}

void EnMaYts_StartDialogue(EnMaYts* this, GlobalContext* globalCtx) {
    s16 sp26 = this->actor.shape.rot.y - this->actor.yawTowardsPlayer;

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if (!(gSaveContext.save.playerForm == PLAYER_FORM_HUMAN)) {
            if (!(gSaveContext.save.weekEventReg[65] & 0x80)) {
                // Saying to non-human Link: "Cremia went to town."
                gSaveContext.save.weekEventReg[65] |= 0x80;
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(globalCtx, 0x335F, &this->actor);
                this->textId = 0x335F;
            } else {
                // Saying to non-human Link: "Pretend you did not hear that."
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(globalCtx, 0x3362, &this->actor);
                this->textId = 0x3362;
                func_80151BB4(globalCtx, 5);
            }
        } else if (Player_GetMask(globalCtx) != PLAYER_MASK_NONE) {
            if (!(gSaveContext.save.weekEventReg[65] & 0x40)) {
                gSaveContext.save.weekEventReg[65] |= 0x40;
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(globalCtx, 0x3363, &this->actor);
                this->textId = 0x3363;
            } else {
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(globalCtx, 0x3366, &this->actor);
                this->textId = 0x3366;
                func_80151BB4(globalCtx, 5);
            }
        } else if (!(gSaveContext.save.weekEventReg[21] & 0x20)) {
            EnMaYts_SetFaceExpression(this, 0, 0);
            Message_StartTextbox(globalCtx, 0x3367, &this->actor);
            this->textId = 0x3367;
        } else {
            if (!(gSaveContext.save.weekEventReg[65] & 0x20)) {
                // Saying to Grasshopper: "Cremia went to town."
                gSaveContext.save.weekEventReg[65] |= 0x20;
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(globalCtx, 0x3369, &this->actor);
                this->textId = 0x3369;
            } else {
                // Saying to Grasshopper: "You're our bodyguard."
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(globalCtx, 0x336C, &this->actor);
                this->textId = 0x336C;
                func_80151BB4(globalCtx, 5);
            }
        }
        EnMaYts_SetupDialogueHandler(this);
    } else if (ABS_ALT(sp26) < 0x4000) {
        func_800B8614(&this->actor, globalCtx, 120.0f);
    }
}

void EnMaYts_SetupDialogueHandler(EnMaYts* this) {
    this->actionFunc = EnMaYts_DialogueHandler;
}

void EnMaYts_DialogueHandler(EnMaYts* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 5: // End message block
            EnMaYts_ChooseNextDialogue(this, globalCtx);
            break;

        case 6: // End conversation
            if (Message_ShouldAdvance(globalCtx) != 0) {
                EnMaYts_SetupStartDialogue(this);
            }
            break;

        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;
    }
}

void EnMaYts_SetupEndCreditsHandler(EnMaYts* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    EnMaYts_SetFaceExpression(this, 0, 0);
    this->actionFunc = EnMaYts_EndCreditsHandler;
}

static u16 D_80B8E32C = 99;
void EnMaYts_EndCreditsHandler(EnMaYts* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 120)) {
        s32 actionIndex = Cutscene_GetActorActionIndex(globalCtx, 120);

        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
            if (globalCtx->csCtx.actorActions[actionIndex]->action != D_80B8E32C) {
                D_80B8E32C = globalCtx->csCtx.actorActions[actionIndex]->action;
                this->endCreditsFlag = 0;
                switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
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
                }
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
        if ((D_80B8E32C == 2) && (this->endCreditsFlag == 0) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->endCreditsFlag++;
            EnMaYts_ChangeAnim(this, 5);
        }
    } else {
        D_80B8E32C = 99;
        this->hasBow = true;
    }
}

// Select the following dialogue based on the current one, and an appropiate face expression
void EnMaYts_ChooseNextDialogue(EnMaYts* this, GlobalContext* globalCtx) {
    if (Message_ShouldAdvance(globalCtx) != 0) {
        switch (this->textId) {
            case 0x335F:
                EnMaYts_SetFaceExpression(this, 0, 2);
                Message_StartTextbox(globalCtx, 0x3360, &this->actor);
                this->textId = 0x3360;
                break;

            case 0x3360:
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(globalCtx, 0x3361, &this->actor);
                this->textId = 0x3361;
                func_80151BB4(globalCtx, 5);
                break;

            case 0x3363:
                EnMaYts_SetFaceExpression(this, 1, 1);
                Message_StartTextbox(globalCtx, 0x3364, &this->actor);
                this->textId = 0x3364;
                break;

            case 0x3364:
                EnMaYts_SetFaceExpression(this, 4, 2);
                Message_StartTextbox(globalCtx, 0x3365, &this->actor);
                this->textId = 0x3365;
                func_80151BB4(globalCtx, 5);
                break;

            case 0x3367:
                EnMaYts_SetFaceExpression(this, 4, 3);
                Message_StartTextbox(globalCtx, 0x3368, &this->actor);
                this->textId = 0x3368;
                func_80151BB4(globalCtx, 5);
                break;

            case 0x3369:
                EnMaYts_SetFaceExpression(this, 0, 0);
                Message_StartTextbox(globalCtx, 0x336A, &this->actor);
                this->textId = 0x336A;
                break;

            case 0x336A:
                EnMaYts_SetFaceExpression(this, 3, 3);
                Message_StartTextbox(globalCtx, 0x336B, &this->actor);
                this->textId = 0x336B;
                func_80151BB4(globalCtx, 5);
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

void EnMaYts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;
    ColliderCylinder* collider;

    this->actionFunc(this, globalCtx);
    collider = &this->collider;
    Collider_UpdateCylinder(&this->actor, collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &collider->base);
    SkelAnime_Update(&this->skelAnime);
    EnMaYts_UpdateEyes(this);
    func_80B8D12C(this, globalCtx);
}

s32 EnMaYts_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnMaYts* this = THIS;
    Vec3s sp4;

    if (limbIndex == MA1_LIMB_HEAD) {
        sp4 = this->unk_1D8.unk_08;
        rot->x += sp4.y;
        if ((this->skelAnime.animation == &object_ma1_Anim_009E58) ||
            (this->skelAnime.animation == &object_ma1_Anim_007D98)) {
            rot->z += sp4.x;
        }
    } else if (limbIndex == MA1_LIMB_TORSO) {
        sp4 = this->unk_1D8.unk_0E;
        rot->x += sp4.y;
        rot->z += sp4.x;
    }

    return false;
}

void EnMaYts_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMaYts* this = THIS;

    if (limbIndex == MA1_LIMB_HEAD) {
        Matrix_GetStateTranslation(&this->actor.focus.pos);
    } else if (limbIndex == MA1_LIMB_HAND_LEFT) {
        if (this->hasBow == true) {
            OPEN_DISPS(globalCtx->state.gfxCtx);
            gSPDisplayList(POLY_OPA_DISP++, object_ma1_DL_0003B0);
            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void EnMaYts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMaYts* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(sMouthTextures[this->mouthTexIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sEyeTextures[this->eyeTexIndex]));

    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMaYts_OverrideLimbDraw, EnMaYts_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// Alternative draw function
void EnMaYts_DrawSleeping(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_ma1_DL_0043A0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
