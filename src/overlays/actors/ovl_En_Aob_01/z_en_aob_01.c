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

void EnAob01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809C1C9C(EnAob01* this, GlobalContext* globalCtx);
void func_809C1D64(EnAob01* this, GlobalContext* globalCtx);
void func_809C2060(EnAob01* this, GlobalContext* globalCtx);
void func_809C21E0(EnAob01* this, GlobalContext* globalCtx);
void func_809C26E4(EnAob01* this, GlobalContext* globalCtx);
void func_809C2730(EnAob01* this, GlobalContext* globalCtx);
void func_809C2788(EnAob01* this, GlobalContext* globalCtx);
void func_809C2824(EnAob01* this, GlobalContext* globalCtx);
void func_809C28B8(EnAob01* this, GlobalContext* globalCtx);
void func_809C2A64(EnAob01* this, GlobalContext* globalCtx);
void func_809C2BE4(EnAob01* this, GlobalContext* globalCtx);
void func_809C2C9C(EnAob01* this, GlobalContext* globalCtx);
void func_809C2D0C(EnAob01* this, GlobalContext* globalCtx);
s32 func_809C2EC4(EnAob01* this, GlobalContext* globalCtx);

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
    u16 time = gSaveContext.save.time;

    gSaveContext.save.time = (u16)REG(15) + time;
    time = gSaveContext.save.time;
    gSaveContext.save.time = (u16)gSaveContext.save.daySpeed + time;
}

void func_809C1158(EnAob01* this, GlobalContext* globalCtx) {
    s32 temp_s0 = ENAOB01_GET_7E00_2(&this->actor);
    s16 i = 0;

    if (temp_s0 != 0x3F) {
        do {
            this->unk_1D8[i] = SubS_GetPathByIndex(globalCtx, temp_s0, 0x3F);
            temp_s0 = this->unk_1D8[i]->unk1;
            i++;
        } while (temp_s0 != 0xFF);
    }
}

void func_809C11EC(EnAob01* this, GlobalContext* globalCtx) {
    s32 unk;
    s16 i;

    func_809C1158(this, globalCtx);

    for (i = 0; i < ARRAY_COUNT(D_809C384C); i++) {
        unk = (this->unk_1D8[D_809C384C[i].unk_06]->unk1 << 0xA) | (i << 5);

        this->unk_3F8[i] = Actor_SpawnAsChildAndCutscene(
            &globalCtx->actorCtx, globalCtx, ACTOR_EN_DG, D_809C384C[i].unk_00.x, D_809C384C[i].unk_00.y,
            D_809C384C[i].unk_00.z, 0, D_809C384C[i].unk_04 * 182.04445f, 0, unk, 0xFFFF, this->actor.unk20, NULL);
    }
}

void func_809C1304(EnAob01* this, GlobalContext* globalCtx) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_3F8); i++) {
        this->unk_3F8[i] = Actor_SpawnAsChildAndCutscene(
            &globalCtx->actorCtx, globalCtx, ACTOR_EN_RACEDOG, (i * 15.0f) + -3897.0f, 130.0f, 1290.0f - (i * 10.0f), 0,
            0x1555, 0, (i << 5) | ENAOB01_GET_7E00_1(&this->actor), 0xFFFF, this->actor.unk20, NULL);
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

void func_809C165C(EnAob01* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_809C16DC(EnAob01* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

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
            globalCtx->msgCtx.bankRupees = this->unk_434;
            this->unk_210 = 0x3529;
            break;

        case 0x3529:
            if (this->unk_2D2 & 2) {
                this->unk_2D2 &= ~2;
                func_801159EC(-this->unk_434);
                func_800B7298(globalCtx, NULL, 7);
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
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

    Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
}

void func_809C1C9C(EnAob01* this, GlobalContext* globalCtx) {
    if (gSaveContext.rupeeAccumulator == 0) {
        gSaveContext.save.weekEventReg[63] |= 1;
        gSaveContext.save.weekEventReg[63] &= (u8)~2;
        this->unk_2D2 |= 0x20;
        func_800FD750(0x40);
        globalCtx->nextEntranceIndex = 0x7C10;
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 0x40;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & (u8)~7) | 2;
        gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & 7) | (this->unk_432 * 8);
        globalCtx->sceneLoadFlag = 0x14;
    }
}

void func_809C1D64(EnAob01* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (temp_v0 == 4) {
        if (Message_ShouldAdvance(globalCtx)) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    if (gSaveContext.save.playerData.rupees < 10) {
                        play_sound(NA_SE_SY_ERROR);
                        this->unk_210 = 0x3524;
                        Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
                    } else {
                        func_8019F208();
                        this->unk_2D2 |= 4;
                        this->unk_2D2 |= 0x10;
                        this->unk_210 = 0x3522;
                        Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
                        this->actionFunc = func_809C21E0;
                    }
                    break;

                case 1:
                    func_8019F230();
                    this->unk_210 = 0x3535;
                    Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
                    break;
            }
        }
    } else if ((temp_v0 == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->unk_210 = 0;
        this->actionFunc = func_809C2060;
    }
}

void func_809C1EC8(EnAob01* this, GlobalContext* globalCtx) {
    static u16 D_809C392C[] = { 4000, 4, 1, 3, 6000, 4, 1, 6, 4000, 4, 1, 3, 6000, 4, 1, 6 };
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp30;

    SkelAnime_Update(&this->skelAnime);
    if (SubS_AngleDiffLessEqual(this->actor.shape.rot.y, 0x36B0, this->actor.yawTowardsPlayer)) {
        sp30.x = player->actor.world.pos.x;
        sp30.y = player->bodyPartsPos[7].y + 3.0f;
        sp30.z = player->actor.world.pos.z;
        func_8013D2E0(&sp30, &this->actor.focus.pos, &this->actor.shape.rot, &this->unk_2D4, &this->unk_2DA,
                      &this->unk_2E0, D_809C392C);
    } else {
        Math_SmoothStepToS(&this->unk_2D4.x, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk_2D4.y, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk_2DA.x, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk_2DA.y, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk_2E0.x, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk_2E0.y, 0, 4, 1000, 1);
    }
    func_809C10B0(this, 3);
    SubS_FillLimbRotTables(globalCtx, this->unk_2F8, this->unk_318, ARRAY_COUNT(this->unk_2F8));
    func_809C165C(this, globalCtx);
    if (player->stateFlags1 & 0x20) {
        func_809C1124();
    }
}

void func_809C2060(EnAob01* this, GlobalContext* globalCtx) {
    if (func_809C15BC(this)) {
        if (func_809C2EC4(this, globalCtx) && !(this->unk_2D2 & 0x100)) {
            if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
                this->actor.flags |= ACTOR_FLAG_10000;
                func_800B8614(&this->actor, globalCtx, 100.0f);
                this->unk_2D2 |= 8;
                this->actionFunc = func_809C21E0;
            }
        } else if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state) && (this->unk_2D2 & 0x100)) {
            this->unk_2D2 &= ~0x100;
            this->unk_2E6 = this->unk_2D4;
            this->unk_2EC = this->unk_2DA;
            this->unk_2F2 = this->unk_2E0;
            func_809C16DC(this, globalCtx);
            this->actionFunc = func_809C21E0;
        } else {
            this->unk_2D2 &= ~0x100;
            if ((this->actor.xzDistToPlayer < 100.0f) && !(this->collider.base.ocFlags2 & OC2_HIT_PLAYER)) {
                this->unk_2D2 |= 0x100;
                func_800B8614(&this->actor, globalCtx, 100.0f);
            }
        }
    }
}

void func_809C21E0(EnAob01* this, GlobalContext* globalCtx) {
    u8 sp2F = Message_GetState(&globalCtx->msgCtx);

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 4000, 1);

    if ((this->unk_2D2 & 8) && !func_809C2EC4(this, globalCtx)) {
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
        if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->actor.flags &= ~ACTOR_FLAG_10000;
            func_80123E90(globalCtx, &this->actor);
            if (this->unk_2D2 & 4) {
                func_809C16DC(this, globalCtx);
                this->unk_2D2 &= ~4;
            } else {
                this->unk_2D2 |= 0x10;
                this->unk_2D2 |= 0x40;
                this->unk_43C = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
                Message_StartTextbox(globalCtx, 0x354B, &this->actor);
            }
            this->unk_2D2 &= ~8;
        }
    } else if (sp2F == 4) {
        if (Message_ShouldAdvance(globalCtx)) {
            this->unk_2D2 &= ~0x40;
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    this->unk_2D2 |= 2;
                    func_809C16DC(this, globalCtx);
                    break;

                case 1:
                    func_8019F230();
                    func_809C16DC(this, globalCtx);
                    break;
            }
        }
    } else if (sp2F == 5) {
        if (Message_ShouldAdvance(globalCtx)) {
            this->unk_2D2 &= ~0x40;
            if (this->unk_2D2 & 0x10) {
                this->unk_2D2 &= ~0x10;
                globalCtx->msgCtx.msgMode = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_809C2060;
            } else {
                func_809C16DC(this, globalCtx);
            }
        }
    } else if ((sp2F == 14) && Message_ShouldAdvance(globalCtx)) {
        this->unk_2D2 &= ~0x40;
        this->unk_434 = globalCtx->msgCtx.bankRupeesSelected;
        func_809C16DC(this, globalCtx);
    }
}

s32 func_809C2504(EnAob01* this, GlobalContext* globalCtx) {
    Actor* npc = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RACEDOG) && (func_800F2178(this->unk_430) == ((EnRacedog*)npc)->unk_1E8)) {
            ActorCutscene_Stop(this->unk_430);
            this->unk_3F4 = npc;
            this->unk_430 = ActorCutscene_GetAdditionalCutscene(this->unk_430);
            return true;
        }
        npc = npc->next;
    }

    return false;
}

s32 func_809C2594(EnAob01* this, GlobalContext* globalCtx) {
    Actor* npc = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RACEDOG) && (((EnRacedog*)npc)->unk_290 == ((EnRacedog*)npc)->unk_292)) {
            this->unk_3F4 = npc;
            return true;
        }
        npc = npc->next;
    }

    return false;
}

s32 func_809C25E4(EnAob01* this, GlobalContext* globalCtx) {
    Actor* npc = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;
    s16 count = 0;

    while (npc != NULL) {
        if ((npc->id == ACTOR_EN_RACEDOG) && (((EnRacedog*)npc)->unk_29C == 3)) {
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

void func_809C26E4(EnAob01* this, GlobalContext* globalCtx) {
    ActorCutscene_Stop(this->unk_430);
    this->unk_430 = ActorCutscene_GetAdditionalCutscene(this->unk_430);
    this->actionFunc = func_809C2824;
}

void func_809C2730(EnAob01* this, GlobalContext* globalCtx) {
    if (func_809C2504(this, globalCtx) || func_809C2680(this)) {
        ActorCutscene_SetIntentToPlay(this->unk_430);
        this->actionFunc = func_809C2824;
    }
}

void func_809C2788(EnAob01* this, GlobalContext* globalCtx) {
    this->unk_2D2 |= 0x20;
    if (func_809C25E4(this, globalCtx)) {
        globalCtx = globalCtx;
        if (func_801A8A50(0) != 0x41) {
            globalCtx->nextEntranceIndex = 0x7C10;
            gSaveContext.eventInf[0] = (gSaveContext.eventInf[0] & (u8)~7) | 3;
            globalCtx->unk_1887F = 0x40;
            gSaveContext.nextTransition = 3;
            globalCtx->sceneLoadFlag = 0x14;
        }
    }
}

void func_809C2824(EnAob01* this, GlobalContext* globalCtx) {
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

void func_809C28B8(EnAob01* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_80123E90(globalCtx, &this->actor);
        this->unk_434 = gSaveContext.unk_3F5C;
        switch ((gSaveContext.eventInf[0] & 0xF8) >> 3) {
            case 1:
                this->unk_210 = 0x352A;
                this->unk_2D2 |= 0x80;
                this->unk_434 *= 3;
                func_801159EC(this->unk_434);
                globalCtx->msgCtx.bankRupees = this->unk_434;
                break;

            case 2:
                this->unk_210 = 0x352B;
                this->unk_2D2 |= 0x80;
                this->unk_434 *= 2;
                func_801159EC(this->unk_434);
                globalCtx->msgCtx.bankRupees = this->unk_434;
                break;

            case 3:
            case 4:
            case 5:
                this->unk_210 = 0x352C;
                func_801159EC(this->unk_434);
                break;

            default:
                this->unk_210 = 0x352D;
                this->unk_2D2 |= 0x40;
                this->unk_43C = 1;
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 1);
                break;
        }

        Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
        this->actionFunc = func_809C2D0C;
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_809C2A64(EnAob01* this, GlobalContext* globalCtx) {
    u8 sp2F = Message_GetState(&globalCtx->msgCtx);

    if (func_809C15BC(this)) {
        if ((sp2F == 5) && Message_ShouldAdvance(globalCtx)) {
            this->unk_434 = 0;
            globalCtx->msgCtx.msgMode = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
        }

        if (Actor_HasParent(&this->actor, globalCtx)) {
            this->unk_2D4 = this->unk_2E6;
            this->unk_2DA = this->unk_2EC;
            this->unk_2E0 = this->unk_2F2;
            this->actor.parent = NULL;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            if (gSaveContext.save.weekEventReg[8] & 0x20) {
                this->actionFunc = func_809C2BE4;
            } else {
                gSaveContext.save.weekEventReg[8] |= 0x20;
                this->actionFunc = func_809C2BE4;
            }
        } else if (gSaveContext.save.weekEventReg[8] & 0x20) {
            Actor_PickUp(&this->actor, globalCtx, GI_RUPEE_RED, 300.0f, 300.0f);
        } else {
            Actor_PickUp(&this->actor, globalCtx, GI_HEART_PIECE, 300.0f, 300.0f);
        }
    }
}

void func_809C2BE4(EnAob01* this, GlobalContext* globalCtx) {
    u8 temp_v0 = Message_GetState(&globalCtx->msgCtx);

    if (((temp_v0 == 5) || (temp_v0 == 6)) && Message_ShouldAdvance(globalCtx)) {
        if (gSaveContext.save.weekEventReg[63] & 2) {
            gSaveContext.save.weekEventReg[63] &= (u8)~2;
        }

        if (gSaveContext.save.weekEventReg[63] & 1) {
            gSaveContext.save.weekEventReg[63] &= (u8)~1;
        }

        this->unk_210 = 0;
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
        gSaveContext.eventInf[0] &= (u8)~7;
        this->actionFunc = func_809C2C9C;
    }
}

void func_809C2C9C(EnAob01* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk_210 = 0x354C;
        func_80151938(globalCtx, this->unk_210);
        this->actionFunc = func_809C1D64;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_809C2D0C(EnAob01* this, GlobalContext* globalCtx) {
    u8 sp2F = Message_GetState(&globalCtx->msgCtx);

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

    if ((sp2F == 5) && Message_ShouldAdvance(globalCtx)) {
        this->unk_2D2 &= ~0x40;
        this->unk_2D2 &= ~0x80;
        if (this->unk_434 >= 150) {
            this->unk_210 = 0x352E;
            Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
            this->actionFunc = func_809C2A64;
        } else {
            this->unk_2D4 = this->unk_2E6;
            this->unk_2DA = this->unk_2EC;
            this->unk_2E0 = this->unk_2F2;

            this->unk_434 = 0;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            if (gSaveContext.save.weekEventReg[63] & 2) {
                gSaveContext.save.weekEventReg[63] &= (u8)~2;
            }

            if (gSaveContext.save.weekEventReg[63] & 1) {
                gSaveContext.save.weekEventReg[63] &= (u8)~1;
            }

            this->unk_210 = 0x354C;
            Message_StartTextbox(globalCtx, this->unk_210, &this->actor);
            this->actionFunc = func_809C1D64;
            gSaveContext.eventInf[0] &= (u8)~7;
        }
    }
}

s32 func_809C2EC4(EnAob01* this, GlobalContext* globalCtx) {
    Actor* dog = globalCtx->actorCtx.actorLists[ACTORCAT_ENEMY].first;

    while (dog != NULL) {
        if (dog->id == ACTOR_EN_DG) {
            this->unk_432 = ((EnDg*)dog)->unk_288;
            if (this->unk_432 == -1) {
                return false;
            }

            if (this->unk_432 == ENDG_GET_3E0(dog)) {
                return true;
            }
        }
        dog = dog->next;
    }

    return false;
}

void func_809C2F34(EnAob01* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

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
    u8 idx;
    u8 idx2;
    u8 orig;
    u8 orig2;
    u8 sp44[7];
    u8 sp34[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    };

    for (i = 0; i < ARRAY_COUNT(sp34); i++) {
        idx = Rand_ZeroFloat(14.0f);
        orig = sp34[i];

        sp34[i] = sp34[idx];
        sp34[idx] = orig;
    }

    for (i = 0; i < ARRAY_COUNT(sp44); i++) {
        gSaveContext.save.weekEventReg[42 + i] = 0;
        sp44[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(sp34); i++) {
        orig2 = sp34[i];
        idx2 = i / 2;

        if (i % 2) {
            sp44[idx2] |= orig2 << 0x4;
            idx = gSaveContext.save.weekEventReg[42 + idx2];
            gSaveContext.save.weekEventReg[42 + idx2] = idx | sp44[idx2];
        } else {
            sp44[idx2] |= orig2;
        }
    }
}

void EnAob01_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnAob01* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gMamamuYanSkel, NULL, this->jointTable, this->morphTable,
                       MAMAMU_YAN_LIMB_MAX);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->unk_43C = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, D_809C3790, 0);
    Actor_SetScale(&this->actor, 0.01f);

    switch (gSaveContext.eventInf[0] & 7) {
        case 0:
            func_809C2FA0();
            func_809C11EC(this, globalCtx);
            this->actor.flags |= ACTOR_FLAG_1;
            this->actionFunc = func_809C2060;
            break;

        case 2:
            this->unk_440 = 500;
            func_809C1304(this, globalCtx);
            this->actor.draw = NULL;
            this->unk_430 = this->actor.cutscene;
            func_809C2594(this, globalCtx);
            ActorCutscene_SetIntentToPlay(this->unk_430);
            this->actor.flags &= ~ACTOR_FLAG_1;
            func_809C2F34(this, globalCtx);
            this->actionFunc = func_809C2824;
            break;

        case 3:
            func_809C2FA0();
            func_809C11EC(this, globalCtx);
            this->actor.flags |= ACTOR_FLAG_1;
            this->actor.flags |= ACTOR_FLAG_10000;
            this->actionFunc = func_809C28B8;
            break;
    }
}

void EnAob01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAob01* this = THIS;

    if (!(this->unk_2D2 & 0x20)) {
        gSaveContext.save.weekEventReg[63] &= (u8)~1;
    }
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnAob01_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAob01* this = THIS;

    this->actionFunc(this, globalCtx);
    func_809C1EC8(this, globalCtx);
}

s32 EnAob01_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnAob01* this = THIS;
    TexturePtr eyeTextures[] = {
        gMamamuYanEyeOpenTex,
        gMamamuYanEyeHalfTex,
        gMamamuYanEyeClosedTex,
    };

    if (limbIndex == MAMAMU_YAN_LIMB_HEAD) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        *dList = gMamamuYanHeadDL;

        gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(eyeTextures[this->eyeIndex]));

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == MAMAMU_YAN_LIMB_HEAD) {
        Matrix_InsertTranslation(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->unk_2DA.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_2DA.x * -1, MTXMODE_APPLY);
        Matrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == MAMAMU_YAN_LIMB_TORSO) {
        Matrix_InsertXRotation_s(this->unk_2E0.y * -1, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->unk_2E0.x * -1, MTXMODE_APPLY);
    }

    if ((limbIndex == MAMAMU_YAN_LIMB_TORSO) || (limbIndex == MAMAMU_YAN_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == MAMAMU_YAN_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += (s16)Math_SinS(this->unk_2F8[limbIndex]) * 200;
        rot->z += (s16)Math_CosS(this->unk_318[limbIndex]) * 200;
    }
    return false;
}

void EnAob01_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f D_809C3968 = { 0.0f, 0.0f, 0.0f };
    EnAob01* this = THIS;

    if (limbIndex == MAMAMU_YAN_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&D_809C3968, &this->actor.focus.pos);
    }
}

void EnAob01_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
}

void EnAob01_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnAob01* this = THIS;
    Vec3f sp5C;
    Vec3f sp50;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(globalCtx->state.gfxCtx, 50, 80, 0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 50, 80, 0, 0));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnAob01_OverrideLimbDraw, EnAob01_PostLimbDraw,
                                   EnAob01_TransformLimbDraw, &this->actor);

    if (this->actor.draw != NULL) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        sp5C = this->actor.world.pos;
        sp50.x = 0.5f;
        sp50.y = 0.5f;
        sp50.z = 0.5f;
        func_800BC620(&sp5C, &sp50, 0xFF, globalCtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
