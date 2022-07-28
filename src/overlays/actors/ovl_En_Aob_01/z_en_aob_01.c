/*
 * File: z_en_aob_01.c
 * Overlay: ovl_En_Aob_01
 * Description: Mamamu Yan
 */

#include "z_en_aob_01.h"
#include "overlays/actors/ovl_En_Racedog/z_en_racedog.h"
#include "overlays/actors/ovl_En_Dg/z_en_dg.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnAob01*)thisx)

void EnAob01_Init(Actor* thisx, PlayState* play);
void EnAob01_Destroy(Actor* thisx, PlayState* play);
void EnAob01_Update(Actor* thisx, PlayState* play);
void EnAob01_Draw(Actor* thisx, PlayState* play);

void func_809C1C9C(EnAob01* this, PlayState* play);
void func_809C1D64(EnAob01* this, PlayState* play);
void func_809C2060(EnAob01* this, PlayState* play);
void func_809C21E0(EnAob01* this, PlayState* play);
void func_809C26E4(EnAob01* this, PlayState* play);
void func_809C2730(EnAob01* this, PlayState* play);
void func_809C2788(EnAob01* this, PlayState* play);
void func_809C2824(EnAob01* this, PlayState* play);
void func_809C28B8(EnAob01* this, PlayState* play);
void func_809C2A64(EnAob01* this, PlayState* play);
void func_809C2BE4(EnAob01* this, PlayState* play);
void func_809C2C9C(EnAob01* this, PlayState* play);
void func_809C2D0C(EnAob01* this, PlayState* play);
s32 func_809C2EC4(EnAob01* this, PlayState* play);

const ActorInit En_Aob_01_InitVars = {
    ACTOR_EN_AOB_01,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AOB,
    sizeof(EnAob01),
    (ActorFunc)EnAob01_Init,
    (ActorFunc)EnAob01_Destroy,
    (ActorFunc)EnAob01_Update,
    (ActorFunc)EnAob01_Draw,
};

static AnimationInfo D_809C3790[6] = {
    { &gMamamuYanIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gMamamuYanLaughStartAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &gMamamuYanLaughLoopAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gMamamuYanSurpriseStartAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    { &gMamamuYanSurpriseLoopAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
    { &gMamamuYanIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -6.0f },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
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
    { 18, 64, 0, { 0, 0, 0 } },
};

typedef struct {
    Vec3f unk_00;
    s16 unk_04;
    s16 unk_06;
} EnAobStruct;

static EnAobStruct D_809C384C[] = {
    { { -4130.0f, 150.0f, 1367.0f }, 84, 0 },  { { -4861.0f, 172.0f, 1606.0f }, 94, 4 },
    { { -4139.0f, 155.0f, 2133.0f }, 73, 6 },  { { -4406.0f, 144.0f, 1416.0f }, 88, 2 },
    { { -4156.0f, 155.0f, 1731.0f }, 42, 0 },  { { -4033.0f, 157.0f, 1994.0f }, -65, 1 },
    { { -4582.0f, 158.0f, 1206.0f }, 144, 2 }, { { -4595.0f, 156.0f, 1493.0f }, 61, 3 },
    { { -4526.0f, 146.0f, 1702.0f }, 61, 4 },  { { -3820.0f, 162.0f, 1965.0f }, 109, 5 },
    { { -4395.0f, 147.0f, 1569.0f }, -24, 0 }, { { -4315.0f, 150.0f, 2048.0f }, 61, 6 },
    { { -4827.0f, 168.0f, 1328.0f }, 115, 4 }, { { -4130.0f, 150.0f, 1367.0f }, 112, 0 },
};

void func_809C10B0(EnAob01* this, s32 arg1) {
    if (DECR(this->blinkTimer) == 0) {
        this->eyeIndex++;
        if (this->eyeIndex >= arg1) {
            this->eyeIndex = 0;
            this->blinkTimer = Rand_S16Offset(30, 30);
        }
    }
}

void func_809C1124(void) {
    gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)REG(15);
    gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)((void)0, gSaveContext.save.daySpeed);
}

void func_809C1158(EnAob01* this, PlayState* play) {
    s32 temp_s0 = ENAOB01_GET_7E00_2(&this->actor);
    s16 i = 0;

    if (temp_s0 != 0x3F) {
        do {
            this->unk_1D8[i] = SubS_GetPathByIndex(play, temp_s0, 0x3F);
            temp_s0 = this->unk_1D8[i]->unk1;
            i++;
        } while (temp_s0 != 0xFF);
    }
}

void func_809C11EC(EnAob01* this, PlayState* play) {
    s32 enDgParams;
    s16 i;

    func_809C1158(this, play);

    for (i = 0; i < ARRAY_COUNT(D_809C384C); i++) {
        enDgParams = ENDG_PARAMS(this->unk_1D8[D_809C384C[i].unk_06]->unk1, i);

        this->unk_3F8[i] = Actor_SpawnAsChildAndCutscene(
            &play->actorCtx, play, ACTOR_EN_DG, D_809C384C[i].unk_00.x, D_809C384C[i].unk_00.y, D_809C384C[i].unk_00.z,
            0, D_809C384C[i].unk_04 * 182.04445f, 0, enDgParams, 0xFFFF, this->actor.unk20, NULL);
    }
}

void func_809C1304(EnAob01* this, PlayState* play) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_3F8); i++) {
        this->unk_3F8[i] = Actor_SpawnAsChildAndCutscene(
            &play->actorCtx, play, ACTOR_EN_RACEDOG, (i * 15.0f) + -3897.0f, 130.0f, 1290.0f - (i * 10.0f), 0, 0x1555,
            0, (i << 5) | ENAOB01_GET_7E00_1(&this->actor), 0xFFFF, this->actor.unk20, NULL);
    }
}

s32 func_809C1424(EnAob01* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(D_809C3790[this->unk_43C].animation);

    if (this->unk_43C == 1) {
        if (curFrame == lastFrame) {
            this->unk_43C = 2;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 2);
            return true;
        }
    } else if (this->unk_43C == 2) {
        return true;
    }
    return false;
}

s32 func_809C14D0(EnAob01* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(D_809C3790[this->unk_43C].animation);

    if ((this->unk_43C == 0) || (this->unk_43C == 5)) {
        if (curFrame == lastFrame) {
            this->unk_43C = 3;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 3);
            return true;
        }
    } else if (this->unk_43C == 3) {
        if (curFrame == lastFrame) {
            this->unk_43C = 4;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 4);
            return true;
        }
    } else if (this->unk_43C == 4) {
        return true;
    }
    return false;
}

s32 func_809C15BC(EnAob01* this) {
    s16 curFrame = this->skelAnime.curFrame;
    s16 lastFrame = Animation_GetLastFrame(D_809C3790[this->unk_43C].animation);

    if ((this->unk_43C != 0) && (this->unk_43C != 5)) {
        if (curFrame == lastFrame) {
            this->unk_43C = 5;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 5);
            return true;
        }
    } else {
        return true;
    }

    return false;
}

void func_809C165C(EnAob01* this, PlayState* play) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void func_809C16DC(EnAob01* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (this->unk_210) {
        case 0:
        case 0x3524:
        case 0x3535:
        case 0x3548:
        case 0x3549:
        case 0x354A:
            switch (gSaveContext.save.day) {
                case 1:
                    if (!gSaveContext.save.isNight) {
                        if (!(gSaveContext.save.weekEventReg[64] & 0x80)) {
                            gSaveContext.save.weekEventReg[64] |= 0x80;
                            this->unk_210 = 0x3520;
                        } else {
                            this->unk_210 = 0x352F;
                        }
                    } else {
                        if (!(gSaveContext.save.weekEventReg[65] & 1)) {
                            gSaveContext.save.weekEventReg[65] |= 1;
                            this->unk_210 = 0x3530;
                        } else {
                            this->unk_210 = 0x352F;
                        }
                    }
                    break;

                case 2:
                    if (!gSaveContext.save.isNight) {
                        if (!(gSaveContext.save.weekEventReg[65] & 2)) {
                            gSaveContext.save.weekEventReg[65] |= 2;
                            this->unk_210 = 0x3531;
                        } else {
                            this->unk_210 = 0x352F;
                        }
                    } else {
                        if (!(gSaveContext.save.weekEventReg[65] & 4)) {
                            gSaveContext.save.weekEventReg[65] |= 4;
                            this->unk_210 = 0x3532;
                        } else {
                            this->unk_210 = 0x352F;
                        }
                    }
                    break;

                case 3:
                    if (!gSaveContext.save.isNight) {
                        if (!(gSaveContext.save.weekEventReg[65] & 8)) {
                            gSaveContext.save.weekEventReg[65] |= 8;
                            this->unk_210 = 0x3533;
                        } else {
                            this->unk_210 = 0x352F;
                        }
                    } else {
                        if (!(gSaveContext.save.weekEventReg[65] & 0x10)) {
                            gSaveContext.save.weekEventReg[65] |= 0x10;
                            this->unk_210 = 0x3534;
                        } else {
                            this->unk_210 = 0x352F;
                        }
                    }
                    break;
            }
            break;

        case 0x3520:
        case 0x352F:
        case 0x3530:
        case 0x3531:
        case 0x3532:
        case 0x3533:
        case 0x3534:
            this->unk_210 = 0x3521;
            break;

        case 0x3521:
            if (this->unk_2D2 & 2) {
                this->unk_2D2 &= ~2;

                switch (player->transformation) {
                    case PLAYER_FORM_GORON:
                        this->unk_210 = 0x3548;
                        this->unk_2D2 |= 0x10;
                        break;

                    case PLAYER_FORM_ZORA:
                        this->unk_210 = 0x3549;
                        this->unk_2D2 |= 0x10;
                        break;

                    case PLAYER_FORM_DEKU:
                        this->unk_210 = 0x354A;
                        this->unk_2D2 |= 0x10;
                        break;

                    case PLAYER_FORM_HUMAN:
                        if (gSaveContext.save.playerData.rupees < 10) {
                            this->unk_210 = 0x3524;
                            this->unk_2D2 |= 0x10;
                        } else {
                            this->unk_210 = 0x3522;
                            this->unk_2D2 |= 4;
                            this->unk_2D2 |= 0x10;
                        }
                }
            } else {
                this->unk_2D2 |= 0x10;
                this->unk_210 = 0x3535;
            }
            break;

        case 0x3522:
        case 0x3523:
            if (this->unk_2D2 & 8) {
                this->unk_210 = 0x3525;
                break;
            }

            this->unk_210 = 0x3523;
            this->unk_2D2 |= 0x40;
            this->unk_2D2 |= 0x10;
            this->unk_43C = 1;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
            break;

        case 0x3525:
        case 0x3526:
            if (this->unk_2D2 & 4) {
                if (this->unk_2D2 & 8) {
                    this->unk_210 = 0x3525;
                    break;
                }

                this->unk_210 = 0x3523;
                this->unk_2D2 |= 0x40;
                this->unk_2D2 |= 0x10;
                this->unk_43C = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
                break;
            }

            if (this->unk_2D2 & 2) {
                this->unk_2D2 &= ~2;
                this->unk_210 = 0x3527;
                break;
            }

            this->unk_210 = 0x3526;
            this->unk_2D2 |= 0x40;
            this->unk_2D2 |= 4;
            this->unk_2D2 |= 0x10;
            this->unk_43C = 1;
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
            break;

        case 0x3527:
            this->unk_210 = 0x3528;
            break;

        case 0x3528:
            if (gSaveContext.save.playerData.rupees < this->unk_434) {
                this->unk_210 = 0x3536;
                this->unk_2D2 |= 0x40;
                this->unk_43C = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
                break;
            }

            if (this->unk_434 == 0) {
                this->unk_210 = 0x3537;
                this->unk_2D2 |= 0x40;
                this->unk_43C = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
                break;
            }

            gSaveContext.unk_3F5C = this->unk_434;
            play->msgCtx.bankRupees = this->unk_434;
            this->unk_210 = 0x3529;
            break;

        case 0x3529:
            if (this->unk_2D2 & 2) {
                this->unk_2D2 &= ~2;
                Rupees_ChangeBy(-this->unk_434);
                func_800B7298(play, NULL, 7);
                play->msgCtx.msgMode = 0x43;
                play->msgCtx.stateTimer = 4;
                this->actionFunc = func_809C1C9C;
                return;
            }
            this->unk_210 = 0x3528;
            break;

        case 0x3536:
        case 0x3537:
            this->unk_210 = 0x3528;
            break;
    }

    Message_StartTextbox(play, this->unk_210, &this->actor);
}

void func_809C1C9C(EnAob01* this, PlayState* play) {
    if (gSaveContext.rupeeAccumulator == 0) {
        gSaveContext.save.weekEventReg[63] |= 1;
        gSaveContext.save.weekEventReg[63] &= (u8)~2;
        this->unk_2D2 |= 0x20;
        func_800FD750(0x40);
        play->nextEntranceIndex = 0x7C10;
        play->transitionType = TRANS_TYPE_64;
        gSaveContext.nextTransitionType = TRANS_TYPE_64;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & (u8)~7) | 2;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & 7) | (this->unk_432 * 8);
        play->transitionTrigger = TRANS_TRIGGER_START;
    }
}

void func_809C1D64(EnAob01* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    if (talkState == TEXT_STATE_CHOICE) {
        if (Message_ShouldAdvance(play)) {
            switch (play->msgCtx.choiceIndex) {
                case 0:
                    if (gSaveContext.save.playerData.rupees < 10) {
                        play_sound(NA_SE_SY_ERROR);
                        this->unk_210 = 0x3524;
                        Message_StartTextbox(play, this->unk_210, &this->actor);
                    } else {
                        func_8019F208();
                        this->unk_2D2 |= 4;
                        this->unk_2D2 |= 0x10;
                        this->unk_210 = 0x3522;
                        Message_StartTextbox(play, this->unk_210, &this->actor);
                        this->actionFunc = func_809C21E0;
                    }
                    break;

                case 1:
                    func_8019F230();
                    this->unk_210 = 0x3535;
                    Message_StartTextbox(play, this->unk_210, &this->actor);
                    break;
            }
        }
    } else if ((talkState == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        play->msgCtx.msgMode = 0x43;
        play->msgCtx.stateTimer = 4;
        this->unk_210 = 0;
        this->actionFunc = func_809C2060;
    }
}

void func_809C1EC8(EnAob01* this, PlayState* play) {
    static TrackOptionsSet sTrackOptions = {
        { 0xFA0, 4, 1, 3 },
        { 0x1770, 4, 1, 6 },
        { 0xFA0, 4, 1, 3 },
        { 0x1770, 4, 1, 6 },
    };
    Player* player = GET_PLAYER(play);
    Vec3f point;

    SkelAnime_Update(&this->skelAnime);
    if (SubS_AngleDiffLessEqual(this->actor.shape.rot.y, 0x36B0, this->actor.yawTowardsPlayer)) {
        point.x = player->actor.world.pos.x;
        point.y = player->bodyPartsPos[7].y + 3.0f;
        point.z = player->actor.world.pos.z;
        SubS_TrackPoint(&point, &this->actor.focus.pos, &this->actor.shape.rot, &this->trackTarget, &this->headRot,
                        &this->torsoRot, &sTrackOptions);
    } else {
        Math_SmoothStepToS(&this->trackTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->trackTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->torsoRot.y, 0, 4, 0x3E8, 1);
    }
    func_809C10B0(this, 3);
    SubS_FillLimbRotTables(play, this->unk_2F8, this->unk_318, ARRAY_COUNT(this->unk_2F8));
    func_809C165C(this, play);
    if (player->stateFlags1 & 0x20) {
        func_809C1124();
    }
}

void func_809C2060(EnAob01* this, PlayState* play) {
    if (func_809C15BC(this)) {
        if (func_809C2EC4(this, play) && !(this->unk_2D2 & 0x100)) {
            if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
                this->actor.flags |= ACTOR_FLAG_10000;
                func_800B8614(&this->actor, play, 100.0f);
                this->unk_2D2 |= 8;
                this->actionFunc = func_809C21E0;
            }
        } else if (Actor_ProcessTalkRequest(&this->actor, &play->state) && (this->unk_2D2 & 0x100)) {
            this->unk_2D2 &= ~0x100;
            this->unk_2E6 = this->trackTarget;
            this->unk_2EC = this->headRot;
            this->unk_2F2 = this->torsoRot;
            func_809C16DC(this, play);
            this->actionFunc = func_809C21E0;
        } else {
            this->unk_2D2 &= ~0x100;
            if ((this->actor.xzDistToPlayer < 100.0f) && !(this->collider.base.ocFlags2 & OC2_HIT_PLAYER)) {
                this->unk_2D2 |= 0x100;
                func_800B8614(&this->actor, play, 100.0f);
            }
        }
    }
}

void func_809C21E0(EnAob01* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 4000, 1);

    if ((this->unk_2D2 & 8) && !func_809C2EC4(this, play)) {
        if ((this->unk_210 != 0) && (this->unk_210 != 0x3535) && (this->unk_210 != 0x3524) &&
            (this->unk_210 != 0x3548) && (this->unk_210 != 0x3549) && (this->unk_210 != 0x354A)) {
            this->unk_210 = 0x3523;
        }
        this->actor.textId = 0;
        this->unk_2D2 &= ~8;
        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->actionFunc = func_809C2060;
        return;
    }

    if (this->unk_2D2 & 0x40) {
        if (!func_809C1424(this)) {
            return;
        }
    } else if (!func_809C15BC(this)) {
        return;
    }

    if (this->unk_2D2 & 8) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            func_80123E90(play, &this->actor);
            if (this->unk_2D2 & 4) {
                func_809C16DC(this, play);
                this->unk_2D2 &= ~4;
            } else {
                this->unk_2D2 |= 0x10;
                this->unk_2D2 |= 0x40;
                this->unk_43C = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
                Message_StartTextbox(play, 0x354B, &this->actor);
            }
            this->unk_2D2 &= ~8;
        }
    } else if (talkState == TEXT_STATE_CHOICE) {
        if (Message_ShouldAdvance(play)) {
            this->unk_2D2 &= ~0x40;
            switch (play->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    this->unk_2D2 |= 2;
                    func_809C16DC(this, play);
                    break;

                case 1:
                    func_8019F230();
                    func_809C16DC(this, play);
                    break;
            }
        }
    } else if (talkState == TEXT_STATE_5) {
        if (Message_ShouldAdvance(play)) {
            this->unk_2D2 &= ~0x40;
            if (this->unk_2D2 & 0x10) {
                this->unk_2D2 &= ~0x10;
                play->msgCtx.msgMode = 0x43;
                play->msgCtx.stateTimer = 4;
                this->actionFunc = func_809C2060;
            } else {
                func_809C16DC(this, play);
            }
        }
    } else if ((talkState == TEXT_STATE_14) && Message_ShouldAdvance(play)) {
        this->unk_2D2 &= ~0x40;
        this->unk_434 = play->msgCtx.bankRupeesSelected;
        func_809C16DC(this, play);
    }
}

s32 func_809C2504(EnAob01* this, PlayState* play) {
    Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RACEDOG) && (func_800F2178(this->unk_430) == ((EnRacedog*)npc)->currentPoint)) {
            ActorCutscene_Stop(this->unk_430);
            this->unk_3F4 = npc;
            this->unk_430 = ActorCutscene_GetAdditionalCutscene(this->unk_430);
            return true;
        }
        npc = npc->next;
    }

    return false;
}

s32 func_809C2594(EnAob01* this, PlayState* play) {
    Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RACEDOG) && (((EnRacedog*)npc)->index == ((EnRacedog*)npc)->selectedDogIndex)) {
            this->unk_3F4 = npc;
            return true;
        }
        npc = npc->next;
    }

    return false;
}

s32 func_809C25E4(EnAob01* this, PlayState* play) {
    Actor* npc = play->actorCtx.actorLists[ACTORCAT_NPC].first;
    s16 count = 0;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RACEDOG) && (((EnRacedog*)npc)->raceStatus == RACEDOG_RACE_STATUS_FINISHED)) {
            count++;
        }
        npc = npc->next;
    }

    if (count >= 14) {
        return true;
    }

    if ((count >= 10) && (DECR(this->unk_440) == 0)) {
        return true;
    }
    return false;
}

s32 func_809C2680(EnAob01* this) {
    if ((ActorCutscene_GetLength(this->unk_430) > 0) && (ActorCutscene_GetCurrentIndex() != this->unk_430)) {
        this->unk_430 = ActorCutscene_GetAdditionalCutscene(this->unk_430);
        return true;
    }
    return false;
}

void func_809C26E4(EnAob01* this, PlayState* play) {
    ActorCutscene_Stop(this->unk_430);
    this->unk_430 = ActorCutscene_GetAdditionalCutscene(this->unk_430);
    this->actionFunc = func_809C2824;
}

void func_809C2730(EnAob01* this, PlayState* play) {
    if (func_809C2504(this, play) || func_809C2680(this)) {
        ActorCutscene_SetIntentToPlay(this->unk_430);
        this->actionFunc = func_809C2824;
    }
}

void func_809C2788(EnAob01* this, PlayState* play) {
    this->unk_2D2 |= 0x20;
    if (func_809C25E4(this, play)) {
        if (func_801A8A50(0) != 0x41) {
            play->nextEntranceIndex = 0x7C10;
            gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & (u8)~7) | 3;
            play->transitionType = TRANS_TYPE_64;
            gSaveContext.nextTransitionType = TRANS_TYPE_03;
            play->transitionTrigger = TRANS_TRIGGER_START;
        }
    }
}

void func_809C2824(EnAob01* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->unk_430)) {
        ActorCutscene_Start(this->unk_430, this->unk_3F4);
        switch (func_800F2178(this->unk_430)) {
            case 255:
                this->actionFunc = func_809C26E4;
                break;

            case 99:
                this->actionFunc = func_809C2788;
                break;

            default:
                this->actionFunc = func_809C2730;
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->unk_430);
    }
}

void func_809C28B8(EnAob01* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_80123E90(play, &this->actor);
        this->unk_434 = gSaveContext.unk_3F5C;
        switch ((gSaveContext.eventInf[0] & 0xF8) >> 3) {
            case 1:
                this->unk_210 = 0x352A;
                this->unk_2D2 |= 0x80;
                this->unk_434 *= 3;
                Rupees_ChangeBy(this->unk_434);
                play->msgCtx.bankRupees = this->unk_434;
                break;

            case 2:
                this->unk_210 = 0x352B;
                this->unk_2D2 |= 0x80;
                this->unk_434 *= 2;
                Rupees_ChangeBy(this->unk_434);
                play->msgCtx.bankRupees = this->unk_434;
                break;

            case 3:
            case 4:
            case 5:
                this->unk_210 = 0x352C;
                Rupees_ChangeBy(this->unk_434);
                break;

            default:
                this->unk_210 = 0x352D;
                this->unk_2D2 |= 0x40;
                this->unk_43C = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
                break;
        }

        Message_StartTextbox(play, this->unk_210, &this->actor);
        this->actionFunc = func_809C2D0C;
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_800B8614(&this->actor, play, 100.0f);
    }
}

void func_809C2A64(EnAob01* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    if (func_809C15BC(this)) {
        if ((talkState == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
            this->unk_434 = 0;
            play->msgCtx.msgMode = 0x43;
            play->msgCtx.stateTimer = 4;
        }

        if (Actor_HasParent(&this->actor, play)) {
            this->trackTarget = this->unk_2E6;
            this->headRot = this->unk_2EC;
            this->torsoRot = this->unk_2F2;
            this->actor.parent = NULL;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            if (gSaveContext.save.weekEventReg[8] & 0x20) {
                this->actionFunc = func_809C2BE4;
            } else {
                gSaveContext.save.weekEventReg[8] |= 0x20;
                this->actionFunc = func_809C2BE4;
            }
        } else if (gSaveContext.save.weekEventReg[8] & 0x20) {
            Actor_PickUp(&this->actor, play, GI_RUPEE_RED, 300.0f, 300.0f);
        } else {
            Actor_PickUp(&this->actor, play, GI_HEART_PIECE, 300.0f, 300.0f);
        }
    }
}

void func_809C2BE4(EnAob01* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    if (((talkState == TEXT_STATE_5) || (talkState == TEXT_STATE_DONE)) && Message_ShouldAdvance(play)) {
        if (gSaveContext.save.weekEventReg[63] & 2) {
            gSaveContext.save.weekEventReg[63] &= (u8)~2;
        }

        if (gSaveContext.save.weekEventReg[63] & 1) {
            gSaveContext.save.weekEventReg[63] &= (u8)~1;
        }

        this->unk_210 = 0;
        func_800B85E0(&this->actor, play, 400.0f, -1);
        gSaveContext.eventInf[0] &= (u8)~7;
        this->actionFunc = func_809C2C9C;
    }
}

void func_809C2C9C(EnAob01* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->unk_210 = 0x354C;
        func_80151938(play, this->unk_210);
        this->actionFunc = func_809C1D64;
    } else {
        func_800B85E0(&this->actor, play, 400.0f, -1);
    }
}

void func_809C2D0C(EnAob01* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 4000, 1);

    if (this->unk_2D2 & 0x40) {
        if (!func_809C1424(this)) {
            return;
        }
    } else if (this->unk_2D2 & 0x80) {
        if (!func_809C14D0(this)) {
            return;
        }
    }

    if ((talkState == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        this->unk_2D2 &= ~0x40;
        this->unk_2D2 &= ~0x80;
        if (this->unk_434 >= 150) {
            this->unk_210 = 0x352E;
            Message_StartTextbox(play, this->unk_210, &this->actor);
            this->actionFunc = func_809C2A64;
        } else {
            this->trackTarget = this->unk_2E6;
            this->headRot = this->unk_2EC;
            this->torsoRot = this->unk_2F2;

            this->unk_434 = 0;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            if (gSaveContext.save.weekEventReg[63] & 2) {
                gSaveContext.save.weekEventReg[63] &= (u8)~2;
            }

            if (gSaveContext.save.weekEventReg[63] & 1) {
                gSaveContext.save.weekEventReg[63] &= (u8)~1;
            }

            this->unk_210 = 0x354C;
            Message_StartTextbox(play, this->unk_210, &this->actor);
            this->actionFunc = func_809C1D64;
            gSaveContext.eventInf[0] &= (u8)~7;
        }
    }
}

s32 func_809C2EC4(EnAob01* this, PlayState* play) {
    Actor* dog = play->actorCtx.actorLists[ACTORCAT_ENEMY].first;

    while (dog != NULL) {
        if (dog->id == ACTOR_EN_DG) {
            this->unk_432 = ((EnDg*)dog)->selectedDogIndex;
            if (this->unk_432 == -1) {
                return false;
            }

            if (this->unk_432 == ENDG_GET_INDEX(dog)) {
                return true;
            }
        }
        dog = dog->next;
    }

    return false;
}

void func_809C2F34(EnAob01* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->actor.world.pos.x = -4134.0f;
    player->actor.world.pos.z = 1464.0f;
    player->actor.shape.rot.y = player->actor.world.rot.y;
    player->actor.draw = NULL;
    player->stateFlags1 |= 0x20;
    this->actor.world.pos.x = -4308.0f;
    this->actor.world.pos.z = 1620.0f;
    this->actor.prevPos = this->actor.world.pos;
}

void func_809C2FA0(void) {
    u8 i;
    u8 rand;
    u8 index;
    u8 orig;
    u8 orig2;
    u8 sp44[7];
    u8 sp34[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    };

    for (i = 0; i < ARRAY_COUNT(sp34); i++) {
        rand = Rand_ZeroFloat(14.0f);
        orig = sp34[i];

        sp34[i] = sp34[rand];
        sp34[rand] = orig;
    }

    for (i = 0; i < ARRAY_COUNT(sp44); i++) {
        gSaveContext.save.weekEventReg[42 + i] = 0;
        sp44[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(sp34); i++) {
        orig2 = sp34[i];
        index = i / 2;

        if (i % 2) {
            sp44[index] |= orig2 << 0x4;
            gSaveContext.save.weekEventReg[42 + index] =
                ((void)0, gSaveContext.save.weekEventReg[42 + index]) | sp44[index];
        } else {
            sp44[index] |= orig2;
        }
    }
}

void EnAob01_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnAob01* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gMamamuYanSkel, NULL, this->jointTable, this->morphTable,
                       MAMAMU_YAN_LIMB_MAX);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->unk_43C = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 0);
    Actor_SetScale(&this->actor, 0.01f);

    switch (gSaveContext.eventInf[0] & 7) {
        case 0:
            func_809C2FA0();
            func_809C11EC(this, play);
            this->actor.flags |= ACTOR_FLAG_1;
            this->actionFunc = func_809C2060;
            break;

        case 2:
            this->unk_440 = 500;
            func_809C1304(this, play);
            this->actor.draw = NULL;
            this->unk_430 = this->actor.cutscene;
            func_809C2594(this, play);
            ActorCutscene_SetIntentToPlay(this->unk_430);
            this->actor.flags &= ~ACTOR_FLAG_1;
            func_809C2F34(this, play);
            this->actionFunc = func_809C2824;
            break;

        case 3:
            func_809C2FA0();
            func_809C11EC(this, play);
            this->actor.flags |= ACTOR_FLAG_1;
            this->actor.flags |= ACTOR_FLAG_10000;
            this->actionFunc = func_809C28B8;
            break;
    }
}

void EnAob01_Destroy(Actor* thisx, PlayState* play) {
    EnAob01* this = THIS;

    if (!(this->unk_2D2 & 0x20)) {
        gSaveContext.save.weekEventReg[63] &= (u8)~1;
    }
    Collider_DestroyCylinder(play, &this->collider);
}

void EnAob01_Update(Actor* thisx, PlayState* play) {
    EnAob01* this = THIS;

    this->actionFunc(this, play);
    func_809C1EC8(this, play);
}

s32 EnAob01_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnAob01* this = THIS;
    TexturePtr eyeTextures[] = {
        gMamamuYanEyeOpenTex,
        gMamamuYanEyeHalfTex,
        gMamamuYanEyeClosedTex,
    };

    if (limbIndex == MAMAMU_YAN_LIMB_HEAD) {
        OPEN_DISPS(play->state.gfxCtx);

        *dList = gMamamuYanHeadDL;

        gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(eyeTextures[this->eyeIndex]));

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (limbIndex == MAMAMU_YAN_LIMB_HEAD) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->headRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(this->headRot.x * -1, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == MAMAMU_YAN_LIMB_TORSO) {
        Matrix_RotateXS(this->torsoRot.y * -1, MTXMODE_APPLY);
        Matrix_RotateZS(this->torsoRot.x * -1, MTXMODE_APPLY);
    }

    if ((limbIndex == MAMAMU_YAN_LIMB_TORSO) || (limbIndex == MAMAMU_YAN_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == MAMAMU_YAN_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += (s16)Math_SinS(this->unk_2F8[limbIndex]) * 200;
        rot->z += (s16)Math_CosS(this->unk_318[limbIndex]) * 200;
    }
    return false;
}

void EnAob01_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_809C3968 = { 0.0f, 0.0f, 0.0f };
    EnAob01* this = THIS;

    if (limbIndex == MAMAMU_YAN_LIMB_HEAD) {
        Matrix_MultVec3f(&D_809C3968, &this->actor.focus.pos);
    }
}

void EnAob01_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

void EnAob01_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnAob01* this = THIS;
    Vec3f sp5C;
    Vec3f sp50;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 50, 80, 0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 50, 80, 0, 0));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnAob01_OverrideLimbDraw, EnAob01_PostLimbDraw,
                                   EnAob01_TransformLimbDraw, &this->actor);

    if (this->actor.draw != NULL) {
        func_8012C2DC(play->state.gfxCtx);
        sp5C = this->actor.world.pos;
        sp50.x = 0.5f;
        sp50.y = 0.5f;
        sp50.z = 0.5f;
        func_800BC620(&sp5C, &sp50, 0xFF, play);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
