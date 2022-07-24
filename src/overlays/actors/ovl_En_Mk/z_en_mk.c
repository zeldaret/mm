/*
 * File: z_en_mk.c
 * Overlay: ovl_En_Mk
 * Description: Marine Researcher
 */

#include "z_en_mk.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

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

const ActorInit En_Mk_InitVars = {
    ACTOR_EN_MK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MK,
    sizeof(EnMk),
    (ActorFunc)EnMk_Init,
    (ActorFunc)EnMk_Destroy,
    (ActorFunc)EnMk_Update,
    (ActorFunc)EnMk_Draw,
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
        &object_mk_Anim_001C38, &object_mk_Anim_000438, &object_mk_Anim_0007D8,
        &object_mk_Anim_0010F4, &object_mk_Anim_001964,
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
    s16 cs;
    s32 i;

    this->actor.terminalVelocity = -4.0f;
    this->actor.gravity = -1.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 36.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_mk_Skel_006CA0, &object_mk_Anim_001C38, this->jointTable,
                       this->morphTable, OBJECT_MK_LIMB_MAX);

    this->unk_27C = -1;
    func_809592E0(this, 0);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    Actor_SetScale(&this->actor, 0.01f);

    this->actionFunc = func_80959E18;
    this->unk_27A = 0;
    this->actor.targetMode = 6;

    if (func_80959524(play) < 7) {
        this->unk_27A |= 2;
    }

    cs = this->actor.cutscene;
    for (i = 0; i < ARRAY_COUNT(this->unk_276); i++) {
        this->unk_276[i] = cs;
        if (cs != -1) {
            this->actor.cutscene = cs;
            cs = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        }
    }

    this->actor.cutscene = this->unk_276[0];
}

void EnMk_Destroy(Actor* thisx, PlayState* play) {
    EnMk* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

s32 func_80959524(PlayState* play) {
    return gSaveContext.save.permanentSceneFlags[play->sceneNum].unk_14 & 7;
}

void func_8095954C(EnMk* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x7F)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, 0x7F));

        switch (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x7F)]->action) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                func_809592E0(this, play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x7F)]->action - 1);
                break;
        }
    } else {
        func_809592E0(this, 0);
    }
}

void func_80959624(EnMk* this, PlayState* play) {
    u16 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (this->unk_27A & 4) {
            textId = 0xFB9;
        } else if (gSaveContext.save.weekEventReg[55] & 0x80) {
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
                func_801477B4(play);
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
        func_800B8614(&this->actor, play, 130.0f);
    }

    func_8095954C(this, play);
}

void func_80959844(EnMk* this, PlayState* play) {
    u16 textId;

    if ((this->unk_27A & 2) && (func_80959524(play) >= 7)) {
        textId = 0xFB3;
    } else if (gSaveContext.save.weekEventReg[20] & 0x40) {
        textId = 0xFB9;
    } else if (gSaveContext.save.weekEventReg[19] & 0x40) {
        textId = 0xFB5;
    } else if (func_80959524(play) >= 7) {
        textId = 0xFB3;
    } else {
        switch (gSaveContext.save.playerForm) {
            case PLAYER_FORM_DEKU:
                if (gSaveContext.save.weekEventReg[19] & 0x10) {
                    if (gSaveContext.save.weekEventReg[55] & 0x80) {
                        textId = 0xFAF;
                    } else {
                        textId = 0xFAE;
                    }
                } else {
                    textId = 0xFAC;
                }
                break;

            case PLAYER_FORM_GORON:
                if (gSaveContext.save.weekEventReg[19] & 8) {
                    if (gSaveContext.save.weekEventReg[55] & 0x80) {
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
                } else if (gSaveContext.save.weekEventReg[19] & 4) {
                    if (gSaveContext.save.weekEventReg[55] & 0x80) {
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
                } else if (gSaveContext.save.weekEventReg[19] & 0x20) {
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
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0xFA2:
                        if (gSaveContext.save.weekEventReg[55] & 0x80) {
                            func_801477B4(play);
                            this->actionFunc = func_80959E18;
                            break;
                        }
                        func_80151938(play, play->msgCtx.currentTextId + 1);
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
                        func_801477B4(play);
                        this->actionFunc = func_80959E18;
                        break;

                    case 0xFA0:
                        gSaveContext.save.weekEventReg[19] |= 4;
                        func_80151938(play, 0xFA1);
                        break;

                    case 0xFA8:
                        gSaveContext.save.weekEventReg[19] |= 8;
                        if (gSaveContext.save.weekEventReg[55] & 0x80) {
                            func_80151938(play, 0xFBD);
                            break;
                        }
                        func_80151938(play, 0xFA9);
                        break;

                    case 0xFAC:
                        gSaveContext.save.weekEventReg[19] |= 0x10;
                        if (gSaveContext.save.weekEventReg[55] & 0x80) {
                            func_80151938(play, 0xFBE);
                            break;
                        }
                        func_80151938(play, 0xFAD);
                        break;

                    case 0xFB1:
                        gSaveContext.save.weekEventReg[19] |= 0x20;
                        func_801477B4(play);
                        this->actionFunc = func_80959E18;
                        break;

                    case 0xFB3:
                    case 0xFB4:
                        func_801477B4(play);
                        this->actionFunc = func_80959E18;
                        this->actor.flags &= ~ACTOR_FLAG_10000;
                        break;

                    case 0xFB5:
                        func_801477B4(play);
                        this->actionFunc = func_80959E18;
                        break;

                    default:
                        func_801477B4(play);
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
        func_800B8500(&this->actor, play, 350.0f, 1000.0f, -1);
    }
}

void func_80959D28(EnMk* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if ((play->csCtx.state == 0) && (this->actor.cutscene == -1)) {
        if (gSaveContext.save.weekEventReg[20] & 0x40) {
            this->unk_27A &= ~1;
            this->actionFunc = func_80959774;
            this->actor.home.rot.y += 0x4E20;
            this->unk_27A |= 4;
        } else {
            this->actionFunc = func_80959E18;
        }
        this->actor.cutscene = this->unk_276[0];
    } else {
        if (this->actor.cutscene != -1) {
            if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
                ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
                this->actor.cutscene = -1;
            } else {
                ActorCutscene_SetIntentToPlay(this->actor.cutscene);
            }
        }
        func_8095954C(this, play);
    }
}

void func_80959E18(EnMk* this, PlayState* play) {
    s32 pad;
    s16 sp22 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    SkelAnime_Update(&this->skelAnime);

    if (gSaveContext.save.weekEventReg[20] & 0x40) {
        this->unk_27A &= ~1;
        this->actionFunc = func_80959774;
        this->actor.home.rot.y += 0x4E20;
        return;
    }

    if (func_800B8718(&this->actor, &play->state)) {
        play->msgCtx.ocarinaMode = 4;
        this->actionFunc = func_80959D28;
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            this->actor.cutscene = this->unk_276[0];
            gSaveContext.save.weekEventReg[20] |= 0x40;
            Item_Give(play, ITEM_SONG_NOVA);
        } else {
            this->actor.cutscene = this->unk_276[1];
        }
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    } else if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80959844(this, play);
        this->actionFunc = func_80959A24;
        this->unk_27A |= 1;
    } else if ((this->unk_27A & 2) && (func_80959524(play) >= 7)) {
        this->actionFunc = func_80959C94;
    } else if ((this->actor.xzDistToPlayer < 120.0f) && (ABS_ALT(sp22) <= 0x4300)) {
        this->unk_27A |= 1;
        func_800B8614(&this->actor, play, 200.0f);
        if (!(gSaveContext.save.weekEventReg[20] & 0x40) && (gSaveContext.save.weekEventReg[19] & 0x40)) {
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
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    this->actionFunc(this, play);

    if ((this->unk_27A & 1) && !Cutscene_CheckActorAction(play, 0x7F)) {
        Actor_TrackPlayer(play, &this->actor, &this->unk_270, &sp38, this->actor.focus.pos);
    } else {
        Math_SmoothStepToS(&this->unk_270.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->unk_270.y, 0, 6, 0x1838, 0x64);
    }
}

s32 EnMk_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnMk* this = THIS;

    if (limbIndex == OBJECT_MK_LIMB_0B) {
        rot->y -= this->unk_270.y;
        rot->z += this->unk_270.x;
    }
    return false;
}

Vec3f D_8095A2A0 = { 1000.0f, -100.0f, 0.0f };

void EnMk_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnMk* this = THIS;

    if (limbIndex == OBJECT_MK_LIMB_0B) {
        Matrix_MultVec3f(&D_8095A2A0, &this->actor.focus.pos);
    }
}

void EnMk_Draw(Actor* thisx, PlayState* play) {
    EnMk* this = THIS;

    func_8012C28C(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMk_OverrideLimbDraw, EnMk_PostLimbDraw, &this->actor);
}
