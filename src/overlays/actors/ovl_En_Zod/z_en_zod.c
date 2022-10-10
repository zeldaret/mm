/*
 * File: z_en_zod.c
 * Overlay: ovl_En_Zod
 * Description: Zora Drummer Tijo
 */

#include "z_en_zod.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnZod*)thisx)

void EnZod_Init(Actor* thisx, PlayState* play);
void EnZod_Destroy(Actor* thisx, PlayState* play);
void EnZod_Update(Actor* thisx, PlayState* play);
void EnZod_Draw(Actor* thisx, PlayState* play);

void EnZod_ChangeAnimation(EnZod* this, s16 nextAnimIndex, u8 mode);
void func_80BAF99C(EnZod* this, PlayState* play);
void func_80BAFB84(EnZod* this, PlayState* play);
void func_80BAFDB4(EnZod* this, PlayState* play);
void func_80BAFF14(EnZod* this, PlayState* play);

const ActorInit En_Zod_InitVars = {
    ACTOR_EN_ZOD,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOD,
    sizeof(EnZod),
    (ActorFunc)EnZod_Init,
    (ActorFunc)EnZod_Destroy,
    (ActorFunc)EnZod_Update,
    (ActorFunc)EnZod_Draw,
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
    { 60, 40, 0, { 0, 0, 0 } },
};

static AnimationHeader* D_80BB056C[] = {
    &object_zod_Anim_0002E8, &object_zod_Anim_000894, &object_zod_Anim_000A9C,
    &object_zod_Anim_000D94, &object_zod_Anim_00D9B0,
};

static Vec3f D_80BB0580 = { 1300.0f, 1100.0f, 0.0f };

typedef enum {
    ENZOD_ANIM_0,
    ENZOD_ANIM_1,
    ENZOD_ANIM_2,
    ENZOD_ANIM_3,
    ENZOD_ANIM_4,
    ENZOD_ANIM_MAX,
} EnZodAnimations;

void EnZod_Init(Actor* thisx, PlayState* play) {
    s32 i;
    EnZod* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 60.0f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_zod_Skel_00D658, &object_zod_Anim_000D94, this->morphTable,
                       this->JointTable, OBJECT_ZOD_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &object_zod_Anim_000D94);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    this->unk25C[0] = this->unk25C[1] = this->unk25C[2] = 0;
    this->actor.gravity = this->actor.terminalVelocity = -4.0f;
    this->unk262[0] = this->unk262[1] = this->unk262[2] = 0x12C;
    this->unk256 = 0;
    this->nextAnimIndex = -1;
    this->curAnimIndex = -1;
    this->actor.textId = 0;
    this->unused = 0;

    for (i = 0; i < 6; i++) {
        this->unk268[i] = 0.0f;
        this->unk280[i] = 0.01;
    }

    EnZod_ChangeAnimation(this, ENZOD_ANIM_3, ANIMMODE_ONCE);
    this->actionFunc = func_80BAF99C;

    switch (ENZOD_GET_F(thisx)) {
        case 1:
            if (gSaveContext.save.weekEventReg[0x4E] & 1) {
                this->actionFunc = func_80BAFDB4;
                EnZod_ChangeAnimation(this, ENZOD_ANIM_0, ANIMMODE_ONCE);
                this->actor.flags |= 0x10;
                ActorCutscene_SetIntentToPlay((s16)this->actor.cutscene);
                break;
            }

            this->actionFunc = func_80BAFB84;
            if (!(gSaveContext.save.weekEventReg[0x37] & 0x80)) {
                Actor_MarkForDeath(&this->actor);
                break;
            }
            break;

        case 2:
            this->actionFunc = func_80BAFF14;
            this->fogNear = -1;
            this->unk256 |= 2;
            break;

        default:
            if (gSaveContext.save.weekEventReg[0x37] & 0x80) {
                Actor_MarkForDeath(&this->actor);
            }
            this->actor.flags |= ACTOR_FLAG_10;
            break;
    }
}

void EnZod_Destroy(Actor* thisx, PlayState* play) {
    EnZod* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80BAF1EC(EnZod* this, PlayState* play) {
    u16 textId;

    if (gSaveContext.save.playerForm != PLAYER_FORM_ZORA) {
        textId = 0x1227; // Huh? Who are you? You can't just come walkin' in here.
        if (gSaveContext.save.weekEventReg[0x20] & 8) {
            textId = 0x1229; // This is a problem. You just can't come in and hang out in our room!
        } else {
            gSaveContext.save.weekEventReg[0x20] |= 8;
        }
    } else if (this->unk256 & 1) {
        textId = 0x1225; // Don't get mad, but i want you to hear this...
    } else {
        textId = 0x1219; // Mikau? Where've you been? I was worried.
        if (gSaveContext.save.weekEventReg[0x20] & 0x10) {
            textId = 0x1226; // Ooh! Ooh! How's Lulu? Is she talking to you?
        } else {
            gSaveContext.save.weekEventReg[0x20] |= 0x10;
        }
        this->unk256 |= 1;
    }

    EnZod_ChangeAnimation(this, ENZOD_ANIM_0, ANIMMODE_ONCE);
    Message_StartTextbox(play, textId, &this->actor);
}

s32 func_80BAF2B4(EnZod* this, PlayState* play) {
    if ((this->actor.playerHeightRel < 30.0f) && (this->actor.xzDistToPlayer < 200.0f) &&
        Player_IsFacingActor(&this->actor, 0x3000, play) && Actor_IsFacingPlayer(&this->actor, 0x3000)) {
        return true;
    }
    return false;
}

void EnZod_ChangeAnimation(EnZod* this, s16 nextAnimIndex, u8 mode) {
    if ((nextAnimIndex < ENZOD_ANIM_0) || (nextAnimIndex >= ENZOD_ANIM_MAX)) {
        nextAnimIndex = ENZOD_ANIM_3;
    }
    Animation_Change(&this->skelAnime, D_80BB056C[nextAnimIndex], 1.0f, 0.0f,
                     Animation_GetLastFrame(D_80BB056C[nextAnimIndex]), mode, -5.0f);
    this->curAnimIndex = nextAnimIndex;
    this->nextAnimIndex = nextAnimIndex;
}

void func_80BAF3E0(EnZod* this) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->nextAnimIndex == this->curAnimIndex) {
            EnZod_ChangeAnimation(this, this->curAnimIndex, ANIMMODE_ONCE);
            switch (this->curAnimIndex) {
                case 3:
                    if (Rand_ZeroFloat(1.0f) < 0.2f) {
                        this->nextAnimIndex = ENZOD_ANIM_4;
                    }
                    break;

                case 4:
                    if (Rand_ZeroFloat(1.0f) < 0.8f) {
                        this->nextAnimIndex = ENZOD_ANIM_3;
                    }
                    break;
            }

        } else {
            EnZod_ChangeAnimation(this, this->nextAnimIndex, ANIMMODE_ONCE);
        }
        SkelAnime_Update(&this->skelAnime);
    }
}

void func_80BAF4D8(EnZod* this) {
    s32 i;

    for (i = 0; i < 3; i++) {
        this->unk25C[i] += this->unk262[i];
        this->unk262[i] -= (s16)(this->unk25C[i] * 0.1f);

        if (ABS_ALT(this->unk262[i]) >= 0x65) {
            this->unk262[i] *= 0.9f;
        }

        switch (i) {
            case 0:
                if ((this->curAnimIndex == ENZOD_ANIM_4) && ((s32)this->skelAnime.curFrame == 7)) {
                    this->unk262[i] = -0x3E8;
                }
                break;

            case 1:
                if ((this->curAnimIndex == ENZOD_ANIM_4) && ((s32)this->skelAnime.curFrame == 19)) {
                    this->unk262[i] = -0x3E8;
                }
                break;
        }
    }

    for (i = 0; i < 6; i++) {
        this->unk268[i] += this->unk280[i];
        this->unk280[i] -= (this->unk268[i] * 0.8f);

        if (fabsf(this->unk280[i]) > 0.01f) {
            this->unk280[i] *= 0.5f;
        }

        switch (i) {
            case 0:
                if (((this->curAnimIndex == ENZOD_ANIM_3) || (this->curAnimIndex == ENZOD_ANIM_4)) &&
                    ((s32)this->skelAnime.curFrame == 1)) {
                    this->unk280[i] = 0.1f;
                }
                break;

            case 2:
                if (((this->curAnimIndex == ENZOD_ANIM_3) && ((s32)this->skelAnime.curFrame == 19)) ||
                    ((this->curAnimIndex == ENZOD_ANIM_4) && ((s32)this->skelAnime.curFrame == 8))) {
                    this->unk280[i] = 0.1f;
                }
                break;

            case 3:
                switch (this->curAnimIndex) {
                    case 3:
                        switch ((s32)this->skelAnime.curFrame) {
                            case 1:
                            case 7:
                            case 12:
                            case 19:
                                this->unk280[i] = 0.03f;
                                break;
                        }
                        break;

                    case 4:
                        if ((s32)this->skelAnime.curFrame == 1) {
                            this->unk280[i] = 0.1f;
                        }
                        break;
                }
                break;

            case 4:
                if ((this->curAnimIndex == ENZOD_ANIM_4) && ((s32)this->skelAnime.curFrame == 19)) {
                    this->unk280[i] = 0.15f;
                }

                break;
        }
    }
}

void func_80BAF7CC(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(play) && (play->msgCtx.currentTextId == 0x121F)) {
                switch (play->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        func_80151938(play, 0x1220); // There's a rumor that the ocean is getting weird...
                        break;

                    case 1:
                        func_8019F230();
                        func_80151938(play, 0x1223); // Oh, yeah, that's right. There aren't any secrets...
                        break;
                }
            }
            break;

        case 5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x121A:
                    case 0x121B:
                    case 0x121C:
                    case 0x1220:
                    case 0x1221:
                    case 0x1227:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        break;

                    case 0x1219:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        this->nextAnimIndex = ENZOD_ANIM_2;
                        break;

                    case 0x121D:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        this->nextAnimIndex = ENZOD_ANIM_1;
                        break;

                    case 0x1223:
                        func_80151938(play, (play->msgCtx.currentTextId + 1) & 0xFFFF);
                        this->nextAnimIndex = ENZOD_ANIM_0;
                        break;

                    case 0x121E:
                    case 0x1226:
                        func_80151938(play, 0x121F);
                        this->nextAnimIndex = ENZOD_ANIM_1;
                        break;

                    default:
                        func_801477B4(play);
                        this->actionFunc = func_80BAF99C;
                        EnZod_ChangeAnimation(this, ENZOD_ANIM_3, ANIMMODE_ONCE);
                        break;
                }
            }
    }
}

void func_80BAF99C(EnZod* this, PlayState* play) {
    s32 pad;
    Vec3f sp20;

    func_80BAF3E0(this);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80BAF1EC(this, play);
        this->actionFunc = func_80BAF7CC;
    } else if (func_80BAF2B4(this, play)) {
        func_800B8614(&this->actor, play, 210.0f);
    }

    sp20.x = this->actor.projectedPos.x;
    sp20.y = this->actor.projectedPos.y;
    sp20.z = this->actor.projectedPos.z;

    func_801A1FB4(3, &sp20, 0x6D, 700.0f);
}

void func_80BAFA44(EnZod* this, PlayState* play) {
    u16 textId;

    if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
        if (gSaveContext.save.weekEventReg[0x4F] & 1) {
            textId = 0x1253;
        } else {
            textId = 0x1251;
            if (gSaveContext.save.weekEventReg[0x4E] & 0x20) {
                textId = 0x1252;
            } else {
                gSaveContext.save.weekEventReg[0x4E] |= 0x20;
            }
        }
    } else {
        textId = 0x1250;
    }

    EnZod_ChangeAnimation(this, ENZOD_ANIM_0, ANIMMODE_ONCE);
    Message_StartTextbox(play, textId, &this->actor);
}

void func_80BAFADC(EnZod* this, PlayState* play) {
    u8 msgState;

    func_80BAF3E0(this);
    msgState = Message_GetState(&play->msgCtx);
    if (msgState != 2) {
        if ((msgState == 5) && Message_ShouldAdvance(play)) {
            func_801477B4(play);
            this->actionFunc = func_80BAFB84;
            EnZod_ChangeAnimation(this, ENZOD_ANIM_3, ANIMMODE_ONCE);
        }
    } else {
        this->actionFunc = func_80BAFB84;
        EnZod_ChangeAnimation(this, ENZOD_ANIM_3, ANIMMODE_ONCE);
    }
}

void func_80BAFB84(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        func_80BAFA44(this, play);
        this->actionFunc = func_80BAFADC;
    } else if (func_80BAF2B4(this, play)) {
        func_800B8614(&this->actor, play, 210.0f);
    }
}

void func_80BAFC00(EnZod* this, PlayState* play) {
}

void func_80BAFC10(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        if (this->actor.cutscene == -1) {
            this->actionFunc = func_80BAFC00;
            play->nextEntrance = play->setupExitList[ENZOD_GET_ENTRANCE_INDEX(&this->actor)];
            play->transitionType = TRANS_TYPE_05;
            play->transitionTrigger = TRANS_TRIGGER_START;
            gSaveContext.save.weekEventReg[0x4E] &= 0xFE;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80BAFD00(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        EnZod_ChangeAnimation(this, ENZOD_ANIM_3, ANIMMODE_ONCE);
        this->actionFunc = func_80BAFC10;
        ActorCutscene_Stop(this->actor.cutscene);
        this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        gSaveContext.save.weekEventReg[0x4F] |= 1;
        Audio_QueueSeqCmd(NA_BGM_INDIGO_GO_SESSION | 0x8000);
    }
}

void func_80BAFDB4(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        func_800B7298(play, NULL, 0x44);
        Message_StartTextbox(play, 0x103A, &this->actor);
        this->actionFunc = func_80BAFD00;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80BAFE34(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (this->fogNear < 799) {
        this->fogNear += 200;
    } else {
        this->fogNear += 30;
    }

    if (this->fogNear >= 1000) {
        this->fogNear = 999;
    }

    if (Cutscene_CheckActorAction(play, 0x203U) != 0) {
        if (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x203)]->action == 1) {
            this->actionFunc = func_80BAFF14;
            this->fogNear = -1;
        }
    } else {
        this->actionFunc = func_80BAFF14;
        this->fogNear = -1;
    }
}

void func_80BAFF14(EnZod* this, PlayState* play) {
    func_80BAF3E0(this);
    if (Cutscene_CheckActorAction(play, 0x203) &&
        (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x203)]->action == 4)) {
        this->actionFunc = func_80BAFE34;
    }
}

void EnZod_Update(Actor* thisx, PlayState* play) {
    EnZod* this = THIS;
    s32 pad;
    Vec3s torsoRot;

    Actor_MoveWithGravity(&this->actor);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 10.0f, 4);
    this->actionFunc(this, play);
    func_80BAF4D8(this);

    if (DECR(this->blinkTimer) == 0) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }

    this->eyeIndex = this->blinkTimer;

    if (this->eyeIndex >= 3) {
        this->eyeIndex = 0;
    }

    torsoRot.z = 0;
    torsoRot.y = 0;
    torsoRot.x = 0;

    if (func_80BAF2B4(this, play)) {
        Actor_TrackPlayer(play, &this->actor, &this->headRot, &torsoRot, this->actor.focus.pos);
        if (this->headRot.x > 0xBB8) {
            this->headRot.x = 0xBB8;
        } else if (this->headRot.x < -0xBB8) {
            this->headRot.x = -0xBB8;
        }
    } else {
        Math_SmoothStepToS(&this->headRot.x, 0, 6, 0x1838, 0x64);
        Math_SmoothStepToS(&this->headRot.y, 0, 6, 0x1838, 0x64);
    }
}

s32 func_80BB0128(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnZod* this = THIS;

    if (limbIndex == OBJECT_ZOD_LIMB_03) {
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;
    }

    return false;
}

void func_80BB0170(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 3) {
        Matrix_MultVec3f(&D_80BB0580, &thisx->focus.pos);
    }
}

void func_80BB01B0(EnZod* this, PlayState* play) {
    s32 i;
    static Gfx* D_80BB0604[] = { object_zod_DL_00A460, object_zod_DL_00A550, object_zod_DL_00A5E0, object_zod_DL_00A670,
                                 object_zod_DL_00A700, object_zod_DL_00A8F8, object_zod_DL_00AAF0, object_zod_DL_00ACE8,
                                 object_zod_DL_00AEE0, object_zod_DL_00B0D8 };
    f32 D_80BB058C[] = { 0.0f, -2690.0f, 2310.0f, 3888.0f, -4160.0f, -2200.0f, -463.0f, 1397.0f, 3413.0f, 389.0f };
    f32 D_80BB05B4[] = { 0.0f, 6335.0f, 6703.0f, 5735.0f, 3098.0f, 3349.0f, 3748.0f, 3718.0f, 2980.0f, 1530.0f };
    f32 D_80BB05DC[] = { 0.0f, 4350.0f, 3200.0f, 1555.0f, 2874.0f, 3901.0f, 4722.0f, 4344.0f, 3200.0f, 3373.0f };
    f32 temp_fa0;

    OPEN_DISPS(play->state.gfxCtx);

    for (i = 0; i < 10; i++) {
        Matrix_Push();
        Matrix_Translate(D_80BB058C[i], D_80BB05B4[i], D_80BB05DC[i], MTXMODE_APPLY);

        switch (i) {
            case 1:
            case 2:
            case 3:
                Matrix_RotateXS(this->unk25C[i - 1], MTXMODE_APPLY);
                break;

            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                temp_fa0 = this->unk268[9 - i] + 1.0f;
                Matrix_Scale(temp_fa0, temp_fa0, temp_fa0, MTXMODE_APPLY);
                break;
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_80BB0604[i]);
        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnZod_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr D_80BB062C[5] = { &object_zod_Tex_005E50, &object_zod_Tex_006650, &object_zod_Tex_006E50, NULL,
                                        NULL };
    EnZod* this = THIS;
    Gfx* gfxP;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (this->unk256 & 2) {
        POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 0, 0, 0, 0, this->fogNear, 1000);
    }

    gfxP = POLY_OPA_DISP;

    gSPSegment(gfxP, 0x08, Lib_SegmentedToVirtual(D_80BB062C[this->eyeIndex]));
    gSPSegment(gfxP + 1, 0x09, Lib_SegmentedToVirtual(&object_zod_Tex_007650));

    POLY_OPA_DISP = gfxP + 2;

    func_80BB01B0(this, play);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80BB0128, func_80BB0170, &this->actor);
    if (this->unk256 & 2) {
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}