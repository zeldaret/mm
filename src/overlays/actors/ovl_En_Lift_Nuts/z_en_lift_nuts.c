/*
 * File: z_en_lift_nuts.c
 * Overlay: ovl_En_Lift_Nuts
 * Description: Deku Scrub Playground - Employee
 */

#include "z_en_lift_nuts.h"
#include "objects/object_dnt/object_dnt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnLiftNuts*)thisx)

void EnLiftNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AEA910(EnLiftNuts* this, GlobalContext* globalCtx);

s32 func_80AE9B8C(void);
void func_80AE9F70(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEA044(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEA0B4(EnLiftNuts* this);
void func_80AEA128(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEA1A0(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEABF0(EnLiftNuts* this);
void func_80AEAC64(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEACF8(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEAEAC(EnLiftNuts* this);
void func_80AEAF14(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEAF8C(EnLiftNuts* this);
void func_80AEAFA0(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB114(EnLiftNuts* this);
void func_80AEB148(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB1C8(EnLiftNuts* this);
void func_80AEB230(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB280(EnLiftNuts* this);
void func_80AEB294(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB428(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB584(EnLiftNuts* this);
void func_80AEB598(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB684(EnLiftNuts* this);
void func_80AEB698(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB828(EnLiftNuts* this);
void func_80AEB8A4(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB934(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB974(EnLiftNuts* this);
void func_80AEB9E0(EnLiftNuts* this, GlobalContext* globalCtx);

const ActorInit En_Lift_Nuts_InitVars = {
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

AnimationInfo D_80AEBD50[] = {
    { &object_dnt_Anim_005488, 1.0f, 0.0f, 0.0f, 0, -4.0f }, { &object_dnt_Anim_00B0B4, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_004AA0, 1.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_0029E8, 1.0f, 0.0f, 0.0f, 2, -4.0f },
    { &object_dnt_Anim_005CA8, 1.0f, 0.0f, 0.0f, 2, -1.0f }, { &object_dnt_Anim_0038CC, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_003CC0, 1.0f, 0.0f, 0.0f, 2, -1.0f }, { &object_dnt_Anim_0012F4, 1.0f, 0.0f, 0.0f, 2, -4.0f },
    { &object_dnt_Anim_004700, 0.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_001BC8, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_003438, 1.0f, 0.0f, 0.0f, 2, -2.0f }, { &object_dnt_Anim_001E2C, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_000994, 1.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_002268, 1.0f, 0.0f, 0.0f, 2, -1.0f },
    { &object_dnt_Anim_002F08, 1.0f, 0.0f, 0.0f, 0, -4.0f }, { &object_dnt_Anim_00577C, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_004E38, 1.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_0029E8, 1.0f, 4.0f, 0.0f, 2, -4.0f },
    { &object_dnt_Anim_0029E8, 1.0f, 8.0f, 0.0f, 2, 0.0f },
};

Gfx* D_80AEBF18[] = {
    object_dnt_DL_008290,
    object_dnt_DL_001350,
    object_dnt_DL_001420,
    NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AEBF28 = {
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

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AEBF54 = { 0, 0, 0, 0, MASS_IMMOVABLE };

UNK_PTR D_80AEBF60 = NULL;
UNK_TYPE D_80AEBF64 = 0x00000000;
UNK_TYPE2 D_80AEBF68 = 0x0000;

void func_80AE9A20(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (D_80AEBF64 == 0) {
        func_800B6584(globalCtx, ACTOR_EN_GAMELUPY, &D_80AEBF60, 2);
        D_80AEBF64 = 1;
    }
    this->ptr_1EC = (s16*)&D_80AEBF60;
}

void func_80AE9A80(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (D_80AEBF68 == 0) {
        func_800B6608(globalCtx, ACTOR_EN_GAMELUPY);
        D_80AEBF68 = 1;
    }
}

s32 D_80AEBF6C = 0;

// Most likely a fake match
s32 func_80AE9AC4(EnLiftNuts* this, s32 arg1) {
    s32* temp = &D_80AEBF6C;
    s32 temp2;

    switch (arg1) {
        case 0:
            if (*temp == 0) {
                return 1;
            }
            break;
        case 1:
            if (*temp == 0) {
                this->unk_34E = 1;
                D_80AEBF6C = 1;
                return 1;
            }
            break;
        case 2:
            if (*temp == (temp2 = 1)) {
                this->unk_34E = 0;
                D_80AEBF6C = 0;
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}

UNK_TYPE D_80AEBF70 = 0x00000000;

Color_RGBA8 D_80AEBF74 = { 170, 130, 90, 255 };
Color_RGBA8 D_80AEBF78 = { 100, 60, 20, 255 };

Vec3f D_80AEBF7C = { 0.0f, 0.0f, 0.0f };

UNK_TYPE func_80AE9B4C(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        if (D_80AEBF70 == (arg1 ^ 0)) {
            return 1;
        }
    } else if (arg0 == 1) {
        D_80AEBF70 = arg1;
        return 1;
    }
    return 0;
}

s32 func_80AE9B8C() {
    s32 ret = 0;

    if (gSaveContext.save.weekEventReg[14] & 0x10) {
        ret = 1;
    }

    if (gSaveContext.save.weekEventReg[14] & 0x20) {
        ret++;
    }

    if (gSaveContext.save.weekEventReg[14] & 0x40) {
        ret++;
    }

    return ret;
}

void func_80AE9BCC(EnLiftNuts* this, GlobalContext* globalCtx) {

    if ((this->actionFunc != func_80AEB934) && (this->actionFunc != func_80AEB8A4) &&
        (this->actionFunc != func_80AEACF8) && (this->actionFunc != func_80AEAC64) &&
        (this->actionFunc != func_80AEA044) && (this->actionFunc != func_80AEB598) &&
        (this->actionFunc != func_80AEB698) && (func_80AE9B4C(0, 3) == 0) && (func_80AE9B8C() == 3) &&
        (gSaveContext.save.playerForm == 3) && (this->actor.xzDistToPlayer < 150.0f)) {
        func_80AEB828(this);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/EnLiftNuts_Init.s")

void EnLiftNuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnLiftNuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    func_80AE9A80(this, globalCtx);
}

void func_80AE9F28(EnLiftNuts* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 18);
    this->actionFunc = func_80AE9F70;
    this->unk_354 = 0;
}

void func_80AE9F70(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (this->unk_354 < 40) {
        this->unk_354++;
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_80AEA0B4(this);
    }
}

void func_80AE9FC8(EnLiftNuts* this) {
    if (this->actionFunc == func_80AEA1A0) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 17);
    } else {
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 3);
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
    this->actionFunc = func_80AEA044;
}

void func_80AEA044(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        func_80AE9F28(this);
    } else if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        func_80AEB9E0(this, globalCtx);
    }
}

void func_80AEA0B4(EnLiftNuts* this) {
    if (func_80AE9B4C(0, 1)) {
        this->actionFunc = func_80AEA1A0;
    } else {
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 2);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actionFunc = func_80AEA128;
    }
}

void func_80AEA128(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 15);
        this->actionFunc = func_80AEA1A0;
    } else if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
        func_80AEB9E0(this, globalCtx);
    }
}

void func_80AEA1A0(EnLiftNuts* this, GlobalContext* globalCtx) {
    s32 pad;
    OSTime time;

    if (((func_80AE9B4C(0, 3) != 0) || (func_80AE9B4C(0, 1) != 0)) && (this->unk_34E == 1)) {
        this->actor.flags |= 0x10000;
    } else if (this->actor.xzDistToPlayer > 120.0f) {
        func_80AE9FC8(this);
    }
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_DEKU) {
            if (func_80AE9B4C(0, 0)) {
                switch (CURRENT_DAY) {
                    case 1:
                        if ((gSaveContext.save.time >= 0xFAAB) || (gSaveContext.save.time < 0x4001)) {
                            Message_StartTextbox(globalCtx, 0x27F7, &this->actor);
                            this->textId = 0x27F7;
                        } else if ((gSaveContext.save.weekEventReg[0xE] & 0x10) != 0) {
                            Message_StartTextbox(globalCtx, 0x27D9, &this->actor);
                            this->textId = 0x27D9;
                        } else {
                            Message_StartTextbox(globalCtx, 0x27DA, &this->actor);
                            this->textId = 0x27DA;
                        }
                        break;
                    case 2:
                        if ((gSaveContext.save.time >= 0xFAAB) || (gSaveContext.save.time < 0x4001)) {
                            Message_StartTextbox(globalCtx, 0x27F7U, &this->actor);
                            this->textId = 0x27F7;
                        } else {
                            if ((gSaveContext.save.weekEventReg[0xE] & 0x20) != 0) {
                                Message_StartTextbox(globalCtx, 0x27DB, &this->actor);
                                this->textId = 0x27DB;
                                break;
                            }

                            if ((gSaveContext.save.weekEventReg[0xE] & 0x10) != 0) {
                                Message_StartTextbox(globalCtx, 0x27DC, &this->actor);
                                this->textId = 0x27DC;
                            } else {
                                Message_StartTextbox(globalCtx, 0x27DD, &this->actor);
                                this->textId = 0x27DD;
                            }
                        }
                        break;
                    case 3:
                        if ((gSaveContext.save.time >= 0xFAAB) || (gSaveContext.save.time < 0x4001)) {
                            Message_StartTextbox(globalCtx, 0x27F7, &this->actor);
                            this->textId = 0x27F7;
                        } else if ((gSaveContext.save.weekEventReg[0xE] & 0x40) != 0) {
                            Message_StartTextbox(globalCtx, 0x27DE, &this->actor);
                            this->textId = 0x27DE;
                        } else if (func_80AE9B8C() == 2) {
                            Message_StartTextbox(globalCtx, 0x27DF, &this->actor);
                            this->textId = 0x27DF;
                        } else if (func_80AE9B8C() == 1) {
                            Message_StartTextbox(globalCtx, 0x27E0, &this->actor);
                            this->textId = 0x27E0;
                        } else {
                            Message_StartTextbox(globalCtx, 0x27E1, &this->actor);
                            this->textId = 0x27E1;
                            break;
                        }
                        break;
                }
            } else if (func_80AE9B4C(0, 3)) {
                if (Flags_GetSwitch(globalCtx, 0x40)) {
                    Flags_UnsetSwitch(globalCtx, 0x40);
                    Inventory_SaveDekuPlaygroundHighScore(4);
                    if (((gSaveContext.save.weekEventReg[0xE] & 0x10)) &&
                        ((gSaveContext.save.weekEventReg[0xE] & 0x20)) && ((CURRENT_DAY) == 3)) {
                        this->unk_354 = 0;
                        Message_StartTextbox(globalCtx, 0x27F4, &this->actor);
                        this->textId = 0x27F4;
                    } else {
                        Message_StartTextbox(globalCtx, 0x27EE, &this->actor);
                        this->textId = 0x27EE;
                    }
                } else {
                    time = gSaveContext.unk_3DE0[4];
                    if (((time >= (gSaveContext.save.dekuPlaygroundHighScores[CURRENT_DAY - 1])))) {
                        if (gSaveContext.unk_3DE0[4] < 0x2EE0) {
                            Message_StartTextbox(globalCtx, 0x27F9, &this->actor);
                            this->textId = 0x27F9;
                        } else {
                            Message_StartTextbox(globalCtx, 0x27EB, &this->actor);
                            this->textId = 0x27EB;
                        }
                    } else {
                        Message_StartTextbox(globalCtx, 0x27ED, &this->actor);
                        this->textId = 0x27ED;
                    }
                }
                Flags_UnsetSwitch(globalCtx, 0x41);
                this->actor.flags &= 0xFFFEFFFF;
            } else if (Flags_GetSwitch(globalCtx, 0x42) == 0) {
                Flags_SetSwitch(globalCtx, 0x42);
                Message_StartTextbox(globalCtx, 0x27E6, &this->actor);
                this->textId = 0x27E6;
            } else {
                switch (CURRENT_DAY) {
                    case 1:
                        Message_StartTextbox(globalCtx, 0x27E7, &this->actor);
                        this->textId = 0x27E7;
                        break;
                    case 2:
                        Message_StartTextbox(globalCtx, 0x27E8, &this->actor);
                        this->textId = 0x27E8;
                        break;
                    case 3:
                        Message_StartTextbox(globalCtx, 0x27E9, &this->actor);
                        this->textId = 0x27E9;
                        break;
                }
            }
        } else {
            Message_StartTextbox(globalCtx, 0x27D8, &this->actor);
            this->textId = 0x27D8;
        }
        func_80AEABF0(this);
    } else if ((func_80AE9AC4(this, 0)) || (this->unk_34E == 1)) {
        if (this->unk_34E == 1) {
            func_800B8614(&this->actor, globalCtx, 200.0f);
        } else if (this->actor.playerHeightRel >= -13.0f) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x1000, 0x500);
}

void func_80AEA7A4(EnLiftNuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    if (Message_ShouldAdvance(globalCtx)) {
        switch (this->textId) {
            case 0x27E2:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    if (gSaveContext.save.playerData.rupees >= 10) {
                        func_8019F208();
                        Message_StartTextbox(globalCtx, 0x27E5, &this->actor);
                        this->textId = 0x27E5;
                        func_801159EC(-10);
                    } else {
                        play_sound(0x4806);
                        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
                        Message_StartTextbox(globalCtx, 0x27E4, &this->actor);
                        this->textId = 0x27E4;
                    }
                } else {
                    func_8019F230();
                    Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
                    Message_StartTextbox(globalCtx, 0x27E3, &this->actor);
                    this->textId = 0x27E3;
                }
                break;
            case 0x238D:
                if (globalCtx->msgCtx.choiceIndex == 0) {
                    player->stateFlags1 |= 0x20;
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

void func_80AEA910(EnLiftNuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Message_ShouldAdvance(globalCtx)) {
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
                Message_StartTextbox(globalCtx, 0x27E2, &this->actor);
                this->textId = 0x27E2;
                break;
            case 0x27E3:
            case 0x27E4:
                func_80AE9FC8(this);
                break;
            case 0x27E5:
                func_801477B4(globalCtx);
                player->stateFlags1 |= 0x20;
                func_80AEAEAC(this);
                break;
            case 0x27E6:
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
                switch (CURRENT_DAY) {
                    case 1:
                        Message_StartTextbox(globalCtx, 0x27E7, &this->actor);
                        this->textId = 0x27E7;
                        break;
                    case 2:
                        Message_StartTextbox(globalCtx, 0x27E8, &this->actor);
                        this->textId = 0x27E8;
                        break;
                    case 3:
                        Message_StartTextbox(globalCtx, 0x27E9, &this->actor);
                        this->textId = 0x27E9;
                        break;
                }
                break;
            case 0x27E7:
            case 0x27E8:
            case 0x27E9:
                Message_StartTextbox(globalCtx, 0x27FA, &this->actor);
                this->textId = 0x27FA;
                break;
            case 0x27FA:
                func_801477B4(globalCtx);
                player->stateFlags1 &= ~0x20;
                func_80AEB114(this);
                break;
            case 0x27EE:
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 0x10);
                Message_StartTextbox(globalCtx, 0x27EF, &this->actor);
                this->textId = 0x27EF;
                break;
            case 0x27EF:
                func_801477B4(globalCtx);
                func_80AEB584(this);
                func_80AEB598(this, globalCtx);
                break;
            case 0x27F1:
                Message_StartTextbox(globalCtx, 0x27F2, &this->actor);
                this->textId = 0x27F2;
                break;
            case 0x27F2:
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
                Message_StartTextbox(globalCtx, 0x27F3, &this->actor);
                this->textId = 0x27F3;
                break;
            case 0x27F4:
                func_801477B4(globalCtx);
                func_80AEB584(this);
                func_80AEB598(this, globalCtx);
                break;
            case 0x27F5:
                func_801477B4(globalCtx);
                func_80AE9B4C(1, 0);
                player->stateFlags1 &= ~0x20;
                func_80AE9FC8(this);
                break;
            case 0x27F9:
                Message_StartTextbox(globalCtx, 0x27ED, &this->actor);
                this->textId = 0x27ED;
                break;
        }
    }
}

void func_80AEABF0(EnLiftNuts* this) {
    this->unk_354 = 0;

    if (this->actionFunc != func_80AEB698) {
        if (func_80AE9B4C(0, 0)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        }
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 16);
    }
    this->actionFunc = func_80AEAC64;
}

void func_80AEAC64(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if ((this->textId == 0x27EE) || (this->textId == 0x27F4) || (this->textId == 0x27F5)) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 10);
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 0);
        }
        this->actionFunc = func_80AEACF8;
    }
}

void func_80AEACF8(EnLiftNuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            func_80AEA7A4(this, globalCtx);
            break;
        case 5:
            func_80AEA910(this, globalCtx);
            break;
        case 6:
            if (Message_ShouldAdvance(globalCtx)) {
                player->stateFlags1 &= ~0x20;
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
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 11);
                break;
            case 0x27EF:
                Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
                break;
            case 0x27F4:
                if (this->unk_354 == 0) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 11);
                    this->unk_354++;
                } else if (this->unk_354 == 4) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 12);
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
    this->actor.speedXZ = 2.0f;
    Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
    func_80AE9AC4(this, 1);
    func_80AE9B4C(1, 1);
    this->actionFunc = func_80AEAF14;
}

void func_80AEAF14(EnLiftNuts* this, GlobalContext* globalCtx) {
    f32 dist;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 10, 0x1000, 0x500);
    dist = Math_Vec3f_StepTo(&this->actor.world.pos, &this->vec_1D8, this->actor.speedXZ);
    this->actor.world.pos.y += this->actor.gravity;

    if (dist == 0.0f) {
        func_80AEAF8C(this);
    }
}

void func_80AEAF8C(EnLiftNuts* this) {
    this->actionFunc = func_80AEAFA0;
}

#if 0
void func_80AEAFA0(EnLiftNuts *this, GlobalContext *globalCtx) {
    f32 sp30;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    PosRot *sp1C;
    PosRot *sp18;
    PosRot *temp_a0;
    PosRot *temp_a1;
    f32 temp_fv0;
    f32 var_fv0;
    s16 temp_v0;
    s16 temp_v1;
    s16 var_a3;
    s16 var_v0;
    s32 var_a3_2;

    Player* player = GET_PLAYER(globalCtx);
    
    temp_a1 = &this->actor.home;
    temp_a0 = &globalCtx->actorCtx.actorLists[2].first->world;
    sp28 = this->actor.yawTowardsPlayer - 0x8000;
    sp1C = temp_a0;
    sp18 = temp_a1;
    temp_v0 = Math_Vec3f_Yaw(&temp_a0->pos, &temp_a1->pos);
    temp_v1 = temp_v0 - sp28;
    sp26 = temp_v1;
    sp2A = temp_v0;
    temp_fv0 = Math_Vec3f_DistXZ(&temp_a0->pos, &temp_a1->pos);
    var_a3 = sp2A;
    if (this->actor.xzDistToPlayer < temp_fv0) {
        var_v0 = temp_v1;
        if (temp_v1 < 0) {
            var_v0 = -temp_v1;
        }
        if (var_v0 < 0x2000) {
            if (temp_v1 > 0) {
                var_a3_2 = (var_a3 + 0x2000) << 0x10;
            } else {
                var_a3_2 = (var_a3 - 0x2000) << 0x10;
            }
            var_a3 = (s16) (var_a3_2 >> 0x10);
        }
    }
    if (temp_fv0 < 5.0f) {
        var_fv0 = 10.0f;
    } else if (temp_fv0 < 30.0f) {
        var_fv0 = 40.0f;
    } else {
        var_fv0 = 80.0f;
    }
    globalCtx->actorCtx.unk268 = 1;
    sp30 = temp_fv0;
    func_800B6F20(globalCtx, &globalCtx->actorCtx.unk_26C, var_fv0, var_a3);
    if (temp_fv0 < 5.0f) {
        func_80AEA0B4(this);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAFA0.s")
#endif

void func_80AEB114(EnLiftNuts* this) {
    func_801A2BB8(NA_BGM_MINI_GAME_2);
    this->actionFunc = func_80AEB148;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB148.s")

void func_80AEB1C8(EnLiftNuts* this) {
    this->actor.speedXZ = 2.0f;
    gSaveContext.eventInf[3] |= 0x10;
    func_8010E9F0(4, 0);
    func_80AE9B4C(1, 2);
    this->actionFunc = func_80AEB230;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB230.s")

void func_80AEB280(EnLiftNuts* this) {
    this->actionFunc = func_80AEB294;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB3E0.s")

#if 0
void func_80AEB428(EnLiftNuts *this, GlobalContext *globalCtx) {
    if (this->unk_354 == 10) {
        if (gSaveContext.unk_3DE0[4] >= 0 || ((gSaveContext.unk_E18[gSaveContext.day % 5]) < this->unk_354)) {
            Message_StartTextbox(globalCtx, 0x27EA, &this->actor);
            this->textId = 0x27EA;
        } else if (*this->ptr_1EC == 300) {
            Message_StartTextbox(globalCtx, 0x27F8, &this->actor);
            this->textId = 0x27F8;
        } else {
            Message_StartTextbox(globalCtx, 0x27EC, &this->actor);
            this->textId = 0x27EC;
        }
    } else if (this->unk_354 == 30) {
        gSaveContext.respawn[0].entranceIndex = 0x3610;
        gSaveContext.eventInf[3] &= 0xEF;
        gSaveContext.nextCutsceneIndex = 0;
        func_80169EFC(&globalCtx->state);
        gSaveContext.respawnFlag = -2;
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 2;
    }
    this->unk_354 += 1;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB428.s")
#endif

void func_80AEB584(EnLiftNuts* this) {
    this->actionFunc = func_80AEB598;
}

void func_80AEB598(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        if ((gSaveContext.save.weekEventReg[14] & 0x10) && (gSaveContext.save.weekEventReg[14] & 0x20) &&
            ((gSaveContext.save.day % 5) == 3) && !(gSaveContext.save.weekEventReg[14] & 0x80)) {
            gSaveContext.save.weekEventReg[14] |= 0x80;
        }
        func_80AEB684(this);
        return;
    }
    if (this->textId == 0x27F4 && !(gSaveContext.save.weekEventReg[0xE] & 0x80)) {
        Actor_PickUp(&this->actor, globalCtx, 0xC, 500.0f, 100.0f);
    } else {
        Actor_PickUp(&this->actor, globalCtx, 5, 500.0f, 100.0f);
    }
}

void func_80AEB684(EnLiftNuts* this) {
    this->actionFunc = func_80AEB698;
}

void func_80AEB698(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if ((gSaveContext.save.weekEventReg[0xE] & 0x10) && (gSaveContext.save.weekEventReg[0xE] & 0x20) &&
            ((gSaveContext.save.day % 5) == 3)) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 0xD);
            Message_StartTextbox(globalCtx, 0x27F5, &this->actor);
            this->textId = 0x27F5;
        } else if (func_80AE9B8C() > 0) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
            Message_StartTextbox(globalCtx, 0x27F0, &this->actor);
            this->textId = 0x27F0;
        } else {
            Message_StartTextbox(globalCtx, 0x27F1, &this->actor);
            this->textId = 0x27F1;
        }
        this->actor.flags &= 0xFFFEFFFF;
        func_80AEABF0(this);
        switch (gSaveContext.save.day % 5) {
            case 1:
                gSaveContext.save.weekEventReg[0xE] |= 0x10;
                break;
            case 2:
                gSaveContext.save.weekEventReg[0xE] |= 0x20;
                break;
            case 3:
                gSaveContext.save.weekEventReg[0xE] |= 0x40;
                break;
            default:
                break;
        }
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void func_80AEB828(EnLiftNuts* this) {
    if (!func_80AE9B4C(0, 4)) {
        func_80AE9B4C(1, 4);
        this->unk_356 = 1;
    }
    if (this->actionFunc == func_80AE9F70) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 0xF);
    }
    this->unk_354 = 0;
    this->actionFunc = func_80AEB8A4;
}

void func_80AEB8A4(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (this->unk_354 == 22) {
        if (this->unk_356 == 1) {
            Message_StartTextbox(globalCtx, 0x27F6, &this->actor);
            this->textId = 0x27F6;
        }
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 17);
        this->actionFunc = func_80AEB934;
    }
    this->unk_354++;
}

void func_80AEB934(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        func_80AEB9E0(this, globalCtx);
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

void func_80AEB9E0(EnLiftNuts* this, GlobalContext* globalCtx) {
    Vec3f worldPos;
    Vec3f velocity;
    Vec3f accel;
    Color_RGBA8 sp68;
    Color_RGBA8 sp64;
    s32 i;

    worldPos = this->actor.world.pos;

    sp68 = D_80AEBF74;
    sp64 = D_80AEBF78;

    accel.y = 0.0f;

    for (i = 0; i < 30; i++) {
        velocity.x = Rand_Centered() * 15.0f;
        velocity.y = Rand_ZeroOne() * 2.0f;
        velocity.z = Rand_Centered() * 15.0f;

        accel.x = -0.2f * velocity.x;
        accel.z = -0.2f * velocity.z;

        func_800B0EB0(globalCtx, &worldPos, &velocity, &accel, &sp68, &sp64, 80, 25, 10);
    }
}

void func_80AEBB30(EnLiftNuts* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnLiftNuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnLiftNuts* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, globalCtx);
    func_80AEBB30(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, thisx, 0.0f, 0.0f, 0.0f, 4);
    func_80AE9BCC(this, globalCtx);

    if (func_80AE9B4C(0, 2)) {
        thisx->flags &= -2;
    }
}

s32 func_80AEBC18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnLiftNuts* this = THIS;

    if (limbIndex == 15 || limbIndex == 16 || limbIndex == 21 || limbIndex == 23 || limbIndex == 24 ||
        limbIndex == 21 || limbIndex == 27) {
        *dList = NULL;
    }

    if (limbIndex == 26) {
        *dList = D_80AEBF18[this->unk_1E4];
    }
    return 0;
}

void func_80AEBC90(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 25) {
        Matrix_MultVec3f(&D_80AEBF7C, &thisx->focus.pos);
    }
}

void EnLiftNuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnLiftNuts* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80AEBC18, func_80AEBC90, thisx);
}
