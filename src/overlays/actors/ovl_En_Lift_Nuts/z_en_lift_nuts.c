/*
 * File: z_en_lift_nuts.c
 * Overlay: ovl_En_Lift_Nuts
 * Description: Deku Scrub Playground - Employee
 */

#include "z_en_lift_nuts.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnLiftNuts*)thisx)

void EnLiftNuts_Init(Actor* thisx, PlayState* play);
void EnLiftNuts_Destroy(Actor* thisx, PlayState* play);
void EnLiftNuts_Update(Actor* thisx, PlayState* play);
void EnLiftNuts_Draw(Actor* thisx, PlayState* play);

void func_80AEA910(EnLiftNuts* this, PlayState* play);

s32 func_80AE9B8C(void);
void func_80AE9F28(EnLiftNuts* this);
void func_80AE9F70(EnLiftNuts* this, PlayState* play);
void func_80AEA044(EnLiftNuts* this, PlayState* play);
void func_80AEA0B4(EnLiftNuts* this);
void func_80AEA128(EnLiftNuts* this, PlayState* play);
void func_80AEA1A0(EnLiftNuts* this, PlayState* play);
void func_80AEABF0(EnLiftNuts* this);
void func_80AEAC64(EnLiftNuts* this, PlayState* play);
void func_80AEACF8(EnLiftNuts* this, PlayState* play);
void func_80AEAEAC(EnLiftNuts* this);
void func_80AEAF14(EnLiftNuts* this, PlayState* play);
void func_80AEAF8C(EnLiftNuts* this);
void func_80AEAFA0(EnLiftNuts* this, PlayState* play);
void func_80AEB114(EnLiftNuts* this);
void func_80AEB148(EnLiftNuts* this, PlayState* play);
void func_80AEB1C8(EnLiftNuts* this);
void func_80AEB230(EnLiftNuts* this, PlayState* play);
void func_80AEB280(EnLiftNuts* this);
void func_80AEB294(EnLiftNuts* this, PlayState* play);
void func_80AEB3E0(EnLiftNuts* this, PlayState* play);
void func_80AEB428(EnLiftNuts* this, PlayState* play);
void func_80AEB584(EnLiftNuts* this);
void func_80AEB598(EnLiftNuts* this, PlayState* play);
void func_80AEB684(EnLiftNuts* this);
void func_80AEB698(EnLiftNuts* this, PlayState* play);
void func_80AEB828(EnLiftNuts* this);
void func_80AEB8A4(EnLiftNuts* this, PlayState* play);
void func_80AEB934(EnLiftNuts* this, PlayState* play);
void func_80AEB974(EnLiftNuts* this);
void func_80AEB9E0(EnLiftNuts* this, PlayState* play);

ActorInit En_Lift_Nuts_InitVars = {
    ACTOR_EN_LIFT_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnLiftNuts),
    (ActorFunc)EnLiftNuts_Init,
    (ActorFunc)EnLiftNuts_Destroy,
    (ActorFunc)EnLiftNuts_Update,
    (ActorFunc)EnLiftNuts_Draw,
};

static AnimationInfo sAnimations[] = {
    { &object_dnt_Anim_005488, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_dnt_Anim_00B0B4, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_dnt_Anim_004AA0, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_dnt_Anim_0029E8, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_dnt_Anim_005CA8, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dnt_Anim_0038CC, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_dnt_Anim_003CC0, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dnt_Anim_0012F4, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_dnt_Anim_004700, 0.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_dnt_Anim_001BC8, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_dnt_Anim_003438, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -2.0f },
    { &object_dnt_Anim_001E2C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_dnt_Anim_000994, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_dnt_Anim_002268, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dnt_Anim_002F08, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_dnt_Anim_00577C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_dnt_Anim_004E38, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_dnt_Anim_0029E8, 1.0f, 4.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_dnt_Anim_0029E8, 1.0f, 8.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
};

Gfx* D_80AEBF18[] = {
    object_dnt_DL_008290,
    object_dnt_DL_001350,
    object_dnt_DL_001420,
    NULL,
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
    { 25, 75, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

void func_80AE9A20(EnLiftNuts* this, PlayState* play) {
    static s16 D_80AEBF60 = 0;
    static s32 D_80AEBF64 = false;

    if (!D_80AEBF64) {
        func_800B6584(play, ACTOR_EN_GAMELUPY, &D_80AEBF60, sizeof(s16));
        D_80AEBF64 = true;
    }
    this->ptr_1EC = &D_80AEBF60;
}

void func_80AE9A80(EnLiftNuts* this, PlayState* play) {
    static s16 D_80AEBF68 = false;

    if (!D_80AEBF68) {
        func_800B6608(play, ACTOR_EN_GAMELUPY);
        D_80AEBF68 = true;
    }
}

s32 func_80AE9AC4(EnLiftNuts* this, s32 arg1) {
    static s32 D_80AEBF6C = 0;

    switch (arg1) {
        case 0:
            if (D_80AEBF6C == 0) {
                return true;
            }
            break;

        case 1:
            if (D_80AEBF6C == 0) {
                this->unk_34E = 1;
                D_80AEBF6C = 1;
                return true;
            }
            break;

        case 2:
            if (D_80AEBF6C == 1) {
                this->unk_34E = 0;
                D_80AEBF6C = 0;
                return true;
            }
            break;

        default:
            break;
    }
    return false;
}

s32 func_80AE9B4C(s32 arg0, s32 arg1) {
    static s32 D_80AEBF70 = 0;

    if (arg0 == 0) {
        if (D_80AEBF70 == arg1) {
            return true;
        }
    } else if (arg0 == 1) {
        D_80AEBF70 = arg1;
        return true;
    }
    return false;
}

s32 func_80AE9B8C() {
    s32 ret = 0;

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_10)) {
        ret = 1;
    }

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_20)) {
        ret++;
    }

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_40)) {
        ret++;
    }

    return ret;
}

void func_80AE9BCC(EnLiftNuts* this, PlayState* play) {
    if ((this->actionFunc != func_80AEB934) && (this->actionFunc != func_80AEB8A4) &&
        (this->actionFunc != func_80AEACF8) && (this->actionFunc != func_80AEAC64) &&
        (this->actionFunc != func_80AEA044) && (this->actionFunc != func_80AEB598) &&
        (this->actionFunc != func_80AEB698) && !func_80AE9B4C(0, 3) && (func_80AE9B8C() == 3) &&
        (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) && (this->actor.xzDistToPlayer < 150.0f)) {
        func_80AEB828(this);
    }
}

void EnLiftNuts_Init(Actor* thisx, PlayState* play) {
    EnLiftNuts* this = THIS;
    Path* path;
    Vec3s* pathPos;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_dnt_Skel_00AC70, &object_dnt_Anim_0029E8, this->jointTable,
                       this->morphTable, OBJECT_DNT_LIMB_MAX);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    if (this->actor.floorBgId != BGCHECK_SCENE) {
        DynaPolyActor* bgActor = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);

        if (bgActor != NULL) {
            this->actor.world.pos = bgActor->actor.world.pos;
            this->actor.home.pos = bgActor->actor.world.pos;
        }
    }
    this->actor.targetMode = 0;
    this->unk_354 = 0;
    this->unk_34E = 0;
    this->unk_356 = 0;
    this->unk_1E4 = 0;
    this->unk_1E8 = 0;
    this->actor.gravity = -2.0f;

    path = &play->setupPathList[ENLIFTNUTS_GET_FF00(&this->actor)];
    pathPos = Lib_SegmentedToVirtual(path->points);
    this->vec_1D8.x = pathPos->x;
    this->vec_1D8.y = pathPos->y;
    this->vec_1D8.z = pathPos->z;
    func_80AE9A20(this, play);
    if (!Flags_GetSwitch(play, 0x41)) {
        func_80AE9B4C(1, 0);
        func_80AE9F28(this);
    } else if (func_80AE9AC4(this, 0)) {
        Player* player = GET_PLAYER(play);

        player->stateFlags1 |= PLAYER_STATE1_20;
        func_80AE9AC4(this, 1);
        func_80AE9B4C(1, 3);
        func_80AEA0B4(this);
    } else {
        func_80AE9F28(this);
    }
}

void EnLiftNuts_Destroy(Actor* thisx, PlayState* play) {
    EnLiftNuts* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
    func_80AE9A80(this, play);
}

void func_80AE9F28(EnLiftNuts* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 18);
    this->actionFunc = func_80AE9F70;
    this->unk_354 = 0;
}

void func_80AE9F70(EnLiftNuts* this, PlayState* play) {
    if (this->unk_354 < 40) {
        this->unk_354++;
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_80AEA0B4(this);
    }
}

void func_80AE9FC8(EnLiftNuts* this) {
    if (this->actionFunc == func_80AEA1A0) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 17);
    } else {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 3);
    }

    Actor_PlaySfx(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
    this->actionFunc = func_80AEA044;
}

void func_80AEA044(EnLiftNuts* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80AE9F28(this);
    } else if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        func_80AEB9E0(this, play);
    }
}

void func_80AEA0B4(EnLiftNuts* this) {
    if (func_80AE9B4C(0, 1)) {
        this->actionFunc = func_80AEA1A0;
    } else {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 2);
        Actor_PlaySfx(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actionFunc = func_80AEA128;
    }
}

void func_80AEA128(EnLiftNuts* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 15);
        this->actionFunc = func_80AEA1A0;
    } else if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
        func_80AEB9E0(this, play);
    }
}

void func_80AEA1A0(EnLiftNuts* this, PlayState* play) {
    if ((func_80AE9B4C(0, 3) || func_80AE9B4C(0, 1)) && this->unk_34E == 1) {
        this->actor.flags |= ACTOR_FLAG_10000;
    } else if (this->actor.xzDistToPlayer > 120.0f) {
        func_80AE9FC8(this);
    }
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
            if (func_80AE9B4C(0, 0)) {
                switch (CURRENT_DAY) {
                    case 1:
                        if (gSaveContext.save.time > CLOCK_TIME(23, 30) || gSaveContext.save.time <= CLOCK_TIME(6, 0)) {
                            Message_StartTextbox(play, 0x27F7, &this->actor);
                            this->textId = 0x27F7;
                        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_10)) {
                            Message_StartTextbox(play, 0x27D9, &this->actor);
                            this->textId = 0x27D9;
                        } else {
                            Message_StartTextbox(play, 0x27DA, &this->actor);
                            this->textId = 0x27DA;
                        }
                        break;

                    case 2:
                        if (gSaveContext.save.time > CLOCK_TIME(23, 30) || gSaveContext.save.time <= CLOCK_TIME(6, 0)) {
                            Message_StartTextbox(play, 0x27F7, &this->actor);
                            this->textId = 0x27F7;
                        } else {
                            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_20)) {
                                Message_StartTextbox(play, 0x27DB, &this->actor);
                                this->textId = 0x27DB;
                                break;
                            }

                            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_10)) {
                                Message_StartTextbox(play, 0x27DC, &this->actor);
                                this->textId = 0x27DC;
                            } else {
                                Message_StartTextbox(play, 0x27DD, &this->actor);
                                this->textId = 0x27DD;
                            }
                        }
                        break;

                    case 3:
                        if (gSaveContext.save.time > CLOCK_TIME(23, 30) || gSaveContext.save.time <= CLOCK_TIME(6, 0)) {
                            Message_StartTextbox(play, 0x27F7, &this->actor);
                            this->textId = 0x27F7;
                        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_40)) {
                            Message_StartTextbox(play, 0x27DE, &this->actor);
                            this->textId = 0x27DE;
                        } else if (func_80AE9B8C() == 2) {
                            Message_StartTextbox(play, 0x27DF, &this->actor);
                            this->textId = 0x27DF;
                        } else if (func_80AE9B8C() == 1) {
                            Message_StartTextbox(play, 0x27E0, &this->actor);
                            this->textId = 0x27E0;
                        } else {
                            Message_StartTextbox(play, 0x27E1, &this->actor);
                            this->textId = 0x27E1;
                        }
                        break;
                }
            } else if (func_80AE9B4C(0, 3)) {
                if (Flags_GetSwitch(play, 0x40)) {
                    Flags_UnsetSwitch(play, 0x40);
                    Inventory_SaveDekuPlaygroundHighScore(4);
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_10) && CHECK_WEEKEVENTREG(WEEKEVENTREG_14_20) &&
                        CURRENT_DAY == 3) {
                        this->unk_354 = 0;
                        Message_StartTextbox(play, 0x27F4, &this->actor);
                        this->textId = 0x27F4;
                    } else {
                        Message_StartTextbox(play, 0x27EE, &this->actor);
                        this->textId = 0x27EE;
                    }
                } else {
                    if (((void)0, gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2]) >=
                        gSaveContext.save.dekuPlaygroundHighScores[CURRENT_DAY - 1]) {
                        if (gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2] < 0x2EE0) {
                            Message_StartTextbox(play, 0x27F9, &this->actor);
                            this->textId = 0x27F9;
                        } else {
                            Message_StartTextbox(play, 0x27EB, &this->actor);
                            this->textId = 0x27EB;
                        }
                    } else {
                        Message_StartTextbox(play, 0x27ED, &this->actor);
                        this->textId = 0x27ED;
                    }
                }
                Flags_UnsetSwitch(play, 0x41);
                this->actor.flags &= ~ACTOR_FLAG_10000;
            } else if (!Flags_GetSwitch(play, 0x42)) {
                Flags_SetSwitch(play, 0x42);
                Message_StartTextbox(play, 0x27E6, &this->actor);
                this->textId = 0x27E6;
            } else {
                switch (CURRENT_DAY) {
                    case 1:
                        Message_StartTextbox(play, 0x27E7, &this->actor);
                        this->textId = 0x27E7;
                        break;

                    case 2:
                        Message_StartTextbox(play, 0x27E8, &this->actor);
                        this->textId = 0x27E8;
                        break;

                    case 3:
                        Message_StartTextbox(play, 0x27E9, &this->actor);
                        this->textId = 0x27E9;
                        break;
                }
            }
        } else {
            Message_StartTextbox(play, 0x27D8, &this->actor);
            this->textId = 0x27D8;
        }
        func_80AEABF0(this);
    } else if (func_80AE9AC4(this, 0) || this->unk_34E == 1) {
        if (this->unk_34E == 1) {
            func_800B8614(&this->actor, play, 200.0f);
        } else if (this->actor.playerHeightRel >= -13.0f) {
            func_800B8614(&this->actor, play, 100.0f);
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000, 0x500);
}

void func_80AEA7A4(EnLiftNuts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x27E2:
                if (play->msgCtx.choiceIndex == 0) { // Yes
                    if (gSaveContext.save.playerData.rupees >= 10) {
                        func_8019F208();
                        Message_StartTextbox(play, 0x27E5, &this->actor);
                        this->textId = 0x27E5;
                        Rupees_ChangeBy(-10);
                    } else {
                        play_sound(NA_SE_SY_ERROR);
                        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                        Message_StartTextbox(play, 0x27E4, &this->actor);
                        this->textId = 0x27E4;
                    }
                } else {
                    func_8019F230();
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                    Message_StartTextbox(play, 0x27E3, &this->actor);
                    this->textId = 0x27E3;
                }
                break;

            case 0x238D:
                if (play->msgCtx.choiceIndex == 0) { // Yes
                    player->stateFlags1 |= PLAYER_STATE1_20;
                    func_80AEB1C8(this);
                } else {
                    func_80AE9FC8(this);
                }
                break;

            default:
                func_80AE9FC8(this);
                break;
        }
    }
}

void func_80AEA910(EnLiftNuts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x27D9:
            case 0x27DA:
            case 0x27DB:
            case 0x27DC:
            case 0x27DD:
            case 0x27DE:
            case 0x27DF:
            case 0x27E0:
            case 0x27E1:
                Message_StartTextbox(play, 0x27E2, &this->actor);
                this->textId = 0x27E2;
                break;

            case 0x27E3:
            case 0x27E4:
                func_80AE9FC8(this);
                break;

            case 0x27E5:
                func_801477B4(play);
                player->stateFlags1 |= PLAYER_STATE1_20;
                func_80AEAEAC(this);
                break;

            case 0x27E6:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                switch (CURRENT_DAY) {
                    case 1:
                        Message_StartTextbox(play, 0x27E7, &this->actor);
                        this->textId = 0x27E7;
                        break;

                    case 2:
                        Message_StartTextbox(play, 0x27E8, &this->actor);
                        this->textId = 0x27E8;
                        break;

                    case 3:
                        Message_StartTextbox(play, 0x27E9, &this->actor);
                        this->textId = 0x27E9;
                        break;
                }
                break;

            case 0x27E7:
            case 0x27E8:
            case 0x27E9:
                Message_StartTextbox(play, 0x27FA, &this->actor);
                this->textId = 0x27FA;
                break;

            case 0x27FA:
                func_801477B4(play);
                player->stateFlags1 &= ~PLAYER_STATE1_20;
                func_80AEB114(this);
                break;

            case 0x27EE:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0x10);
                Message_StartTextbox(play, 0x27EF, &this->actor);
                this->textId = 0x27EF;
                break;

            case 0x27EF:
                func_801477B4(play);
                func_80AEB584(this);
                func_80AEB598(this, play);
                break;

            case 0x27F1:
                Message_StartTextbox(play, 0x27F2, &this->actor);
                this->textId = 0x27F2;
                break;

            case 0x27F2:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                Message_StartTextbox(play, 0x27F3, &this->actor);
                this->textId = 0x27F3;
                break;

            case 0x27F4:
                func_801477B4(play);
                func_80AEB584(this);
                func_80AEB598(this, play);
                break;

            case 0x27F5:
                func_801477B4(play);
                func_80AE9B4C(1, 0);
                player->stateFlags1 &= ~PLAYER_STATE1_20;
                func_80AE9FC8(this);
                break;

            case 0x27F9:
                Message_StartTextbox(play, 0x27ED, &this->actor);
                this->textId = 0x27ED;
                break;
        }
    }
}

void func_80AEABF0(EnLiftNuts* this) {
    this->unk_354 = 0;

    if (this->actionFunc != func_80AEB698) {
        if (func_80AE9B4C(0, 0)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        }
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 16);
    }
    this->actionFunc = func_80AEAC64;
}

void func_80AEAC64(EnLiftNuts* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if ((this->textId == 0x27EE) || (this->textId == 0x27F4) || (this->textId == 0x27F5)) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 10);
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 0);
        }
        this->actionFunc = func_80AEACF8;
    }
}

void func_80AEACF8(EnLiftNuts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    switch (Message_GetState(&play->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;

        case 4:
            func_80AEA7A4(this, play);
            break;

        case 5:
            func_80AEA910(this, play);
            break;

        case 6:
            if (Message_ShouldAdvance(play)) {
                player->stateFlags1 &= ~PLAYER_STATE1_20;
                func_80AE9FC8(this);
                func_80AE9AC4(this, 2);
                if (func_80AE9B4C(0, 3)) {
                    func_80AE9B4C(1, 0);
                }
            }
            break;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x2000, 0x500);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->textId) {
            case 0x27EE:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 11);
                break;

            case 0x27EF:
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
                break;

            case 0x27F4:
                if (this->unk_354 == 0) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 11);
                    this->unk_354++;
                } else if (this->unk_354 == 4) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 12);
                    this->unk_354 = 0;
                } else {
                    this->unk_354++;
                }
                break;
        }
    }
    func_80AEB974(this);
}

void func_80AEAEAC(EnLiftNuts* this) {
    this->actor.speed = 2.0f;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
    func_80AE9AC4(this, 1);
    func_80AE9B4C(1, 1);
    this->actionFunc = func_80AEAF14;
}

void func_80AEAF14(EnLiftNuts* this, PlayState* play) {
    f32 dist;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 10, 0x1000, 0x500);
    dist = Math_Vec3f_StepTo(&this->actor.world.pos, &this->vec_1D8, this->actor.speed);
    this->actor.world.pos.y += this->actor.gravity;

    if (dist == 0.0f) {
        func_80AEAF8C(this);
    }
}

void func_80AEAF8C(EnLiftNuts* this) {
    this->actionFunc = func_80AEAFA0;
}

void func_80AEAFA0(EnLiftNuts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 dist;
    f32 temp_fv0;
    s16 yaw;
    s16 sp28;
    s16 yawDiff;

    sp28 = this->actor.yawTowardsPlayer - 0x8000;
    yaw = Math_Vec3f_Yaw(&player->actor.world.pos, &this->actor.home.pos);
    yawDiff = yaw - sp28;
    dist = Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos);

    if (this->actor.xzDistToPlayer < dist) {
        if (ABS_ALT(yawDiff) < 0x2000) {
            yaw = (yawDiff > 0) ? (yaw + 0x2000) : (yaw - 0x2000);
        }
    }
    if (dist < 5.0f) {
        temp_fv0 = 10.0f;
    } else if (dist < 30.0f) {
        temp_fv0 = 40.0f;
    } else {
        temp_fv0 = 80.0f;
    }

    play->actorCtx.unk268 = 1;
    func_800B6F20(play, &play->actorCtx.unk_26C, temp_fv0, yaw);
    if (dist < 5.0f) {
        func_80AEA0B4(this);
    }
}

void func_80AEB114(EnLiftNuts* this) {
    func_801A2BB8(NA_BGM_TIMED_MINI_GAME);
    this->actionFunc = func_80AEB148;
}

void func_80AEB148(EnLiftNuts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (player->stateFlags3 & PLAYER_STATE3_200) {
        this->actor.speed = 2.0f;
        SET_EVENTINF(EVENTINF_34);
        Interface_StartTimer(4, 0);
        func_80AE9B4C(1, 2);
        Actor_PlaySfx(&this->actor, NA_SE_SY_FOUND);
        func_80AEB280(this);
    }
}

void func_80AEB1C8(EnLiftNuts* this) {
    this->actor.speed = 2.0f;
    SET_EVENTINF(EVENTINF_34);
    Interface_StartTimer(4, 0);
    func_80AE9B4C(1, 2);
    this->actionFunc = func_80AEB230;
}

void func_80AEB230(EnLiftNuts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2] > 0) {
        player->stateFlags1 &= ~PLAYER_STATE1_20;
        func_80AEB280(this);
    }
}

void func_80AEB280(EnLiftNuts* this) {
    this->actionFunc = func_80AEB294;
}

void func_80AEB294(EnLiftNuts* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (((player->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (player->actor.floorBgId == BG_ACTOR_MAX) &&
         player->actor.world.pos.y < 20.0f) ||
        gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2] >= 0x2EE0) {
        player->stateFlags1 |= PLAYER_STATE1_20;
        Flags_SetSwitch(play, 0x41);
        func_80AEB3E0(this, play);
    }

    if (*this->ptr_1EC == 300) {
        player->stateFlags1 |= PLAYER_STATE1_20;

        if (((void)0, gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2]) <
            gSaveContext.save.dekuPlaygroundHighScores[CURRENT_DAY - 1]) {
            Flags_SetSwitch(play, 0x40);
        }
        Flags_SetSwitch(play, 0x41);
        func_80AEB3E0(this, play);
    }
}

void func_80AEB3E0(EnLiftNuts* this, PlayState* play) {
    play_sound(NA_SE_SY_FOUND);
    this->unk_354 = 0;
    gSaveContext.timerStates[TIMER_ID_MINIGAME_2] = TIMER_STATE_6;
    this->actionFunc = func_80AEB428;
}

void func_80AEB428(EnLiftNuts* this, PlayState* play) {
    s32 pad;

    if (this->unk_354 == 10) {
        if (((void)0, gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2]) >
            gSaveContext.save.dekuPlaygroundHighScores[CURRENT_DAY - 1]) {
            Message_StartTextbox(play, 0x27EA, &this->actor);
            this->textId = 0x27EA;
        } else if (*this->ptr_1EC == 300) {
            Message_StartTextbox(play, 0x27F8, &this->actor);
            this->textId = 0x27F8;
        } else {
            Message_StartTextbox(play, 0x27EC, &this->actor);
            this->textId = 0x27EC;
        }
    } else if (this->unk_354 == 30) {
        CLEAR_EVENTINF(EVENTINF_34);
        gSaveContext.respawn[RESPAWN_MODE_DOWN].entrance = ENTRANCE(DEKU_SCRUB_PLAYGROUND, 1);
        gSaveContext.nextCutsceneIndex = 0;
        func_80169EFC(&play->state);
        gSaveContext.respawnFlag = -2;
        play->transitionType = TRANS_TYPE_64;
        gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK;
    }
    this->unk_354++;
}

void func_80AEB584(EnLiftNuts* this) {
    this->actionFunc = func_80AEB598;
}

void func_80AEB598(EnLiftNuts* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_10) && CHECK_WEEKEVENTREG(WEEKEVENTREG_14_20) && (CURRENT_DAY == 3) &&
            !CHECK_WEEKEVENTREG(WEEKEVENTREG_14_80)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_14_80);
        }
        func_80AEB684(this);
    } else if ((this->textId == 0x27F4) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_14_80)) {
        Actor_PickUp(&this->actor, play, GI_HEART_PIECE, 500.0f, 100.0f);
    } else {
        Actor_PickUp(&this->actor, play, GI_RUPEE_PURPLE, 500.0f, 100.0f);
    }
}

void func_80AEB684(EnLiftNuts* this) {
    this->actionFunc = func_80AEB698;
}

void func_80AEB698(EnLiftNuts* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_14_10) && CHECK_WEEKEVENTREG(WEEKEVENTREG_14_20) && (CURRENT_DAY == 3)) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 13);
            Message_StartTextbox(play, 0x27F5, &this->actor);
            this->textId = 0x27F5;
        } else if (func_80AE9B8C() > 0) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 1);
            Message_StartTextbox(play, 0x27F0, &this->actor);
            this->textId = 0x27F0;
        } else {
            Message_StartTextbox(play, 0x27F1, &this->actor);
            this->textId = 0x27F1;
        }
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_80AEABF0(this);
        switch (CURRENT_DAY) {
            case 1:
                SET_WEEKEVENTREG(WEEKEVENTREG_14_10);
                break;

            case 2:
                SET_WEEKEVENTREG(WEEKEVENTREG_14_20);
                break;

            case 3:
                SET_WEEKEVENTREG(WEEKEVENTREG_14_40);
                break;

            default:
                break;
        }
    } else {
        func_800B85E0(&this->actor, play, 200.0f, -1);
    }
}

void func_80AEB828(EnLiftNuts* this) {
    if (!func_80AE9B4C(0, 4)) {
        func_80AE9B4C(1, 4);
        this->unk_356 = 1;
    }
    if (this->actionFunc == func_80AE9F70) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 15);
    }
    this->unk_354 = 0;
    this->actionFunc = func_80AEB8A4;
}

void func_80AEB8A4(EnLiftNuts* this, PlayState* play) {
    if (this->unk_354 == 22) {
        if (this->unk_356 == 1) {
            Message_StartTextbox(play, 0x27F6, &this->actor);
            this->textId = 0x27F6;
        }
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimations, 17);
        this->actionFunc = func_80AEB934;
    }
    this->unk_354++;
}

void func_80AEB934(EnLiftNuts* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        func_80AEB9E0(this, play);
    }
}

void func_80AEB974(EnLiftNuts* this) {
    s16 textId = this->textId;

    switch (textId) {
        default:
            this->unk_1E4 = 0;
            break;

        case 0x27EE:
        case 0x27EF:
            this->unk_1E4 = 1;
            break;

        case 0x27F5:
            this->unk_1E4 = 2;
            break;

        case 0x27F4:
            if (this->unk_354 == 0) {
                this->unk_1E4 = 2;
                break;
            }
            this->unk_1E4 = 1;
    }
}

void func_80AEB9E0(EnLiftNuts* this, PlayState* play) {
    Vec3f worldPos = this->actor.world.pos;
    Vec3f velocity;
    Vec3f accel;
    Color_RGBA8 primColor = { 170, 130, 90, 255 };
    Color_RGBA8 envColor = { 100, 60, 20, 255 };
    s32 i;

    accel.y = 0.0f;

    for (i = 0; i < 30; i++) {
        velocity.x = Rand_Centered() * 15.0f;
        velocity.y = Rand_ZeroOne() * 2.0f;
        velocity.z = Rand_Centered() * 15.0f;

        accel.x = -0.2f * velocity.x;
        accel.z = -0.2f * velocity.z;

        func_800B0EB0(play, &worldPos, &velocity, &accel, &primColor, &envColor, 80, 25, 10);
    }
}

void func_80AEBB30(EnLiftNuts* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnLiftNuts_Update(Actor* thisx, PlayState* play) {
    EnLiftNuts* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    func_80AEBB30(this, play);
    Actor_UpdateBgCheckInfo(play, thisx, 0.0f, 0.0f, 0.0f, 4);
    func_80AE9BCC(this, play);

    if (func_80AE9B4C(0, 2)) {
        thisx->flags &= ~ACTOR_FLAG_1;
    }
}

s32 EnLiftNuts_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnLiftNuts* this = THIS;

    if (limbIndex == OBJECT_DNT_LIMB_0F || limbIndex == OBJECT_DNT_LIMB_10 || limbIndex == OBJECT_DNT_LIMB_15 ||
        limbIndex == OBJECT_DNT_LIMB_17 || limbIndex == OBJECT_DNT_LIMB_18 || limbIndex == OBJECT_DNT_LIMB_15 ||
        limbIndex == OBJECT_DNT_LIMB_1B) {
        *dList = NULL;
    }

    if (limbIndex == OBJECT_DNT_LIMB_1A) {
        *dList = D_80AEBF18[this->unk_1E4];
    }
    return false;
}

void EnLiftNuts_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f sFocusOffset = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == OBJECT_DNT_LIMB_19) {
        Matrix_MultVec3f(&sFocusOffset, &thisx->focus.pos);
    }
}

void EnLiftNuts_Draw(Actor* thisx, PlayState* play) {
    EnLiftNuts* this = THIS;

    func_8012C28C(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnLiftNuts_OverrideLimbDraw, EnLiftNuts_PostLimbDraw, thisx);
}
