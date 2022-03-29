/*
 * File: z_en_sellnuts.c
 * Overlay: ovl_En_Sellnuts
 * Description: Business Scrub Carrying Bags
 */

#include "z_en_sellnuts.h"
#include "objects/object_dnt/object_dnt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnSellnuts*)thisx)

void EnSellnuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ADB4F4(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADB544(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADB924(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADBAB8(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADBBEC(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADBCE4(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADBD64(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADBE80(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADBFA0(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADC2CC(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADC37C(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADC580(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADC6D0(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADC7B4(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADC8C4(EnSellnuts* this, GlobalContext* globalCtx);
void func_80ADCA64(EnSellnuts* this, GlobalContext* globalCtx);
s32 func_80ADCE4C(EnSellnuts* this, Path* path, s32 arg2);
f32 func_80ADCFE8(Path* path, s32 arg1, Vec3f* pos, Vec3s* arg3);

static u16 D_80ADD910[] = { 0x0614, 0x060E, 0x0628 };

static u16 D_80ADD918[] = { 0x0616, 0x0610, 0x0629 };

static u16 D_80ADD920[] = { 0x0618, 0x0611, 0x062A };

static u16 D_80ADD928[] = { 0x0617, 0x0612, 0x0612 };

static u16 D_80ADD930[] = { 0x0619, 0x0613, 0x0613 };

static u16 D_80ADD938[] = { 0x0615, 0x060F, 0x060F };

static u8 D_80ADD940 = 0;

const ActorInit En_Sellnuts_InitVars = {
    ACTOR_EN_SELLNUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnSellnuts),
    (ActorFunc)EnSellnuts_Init,
    (ActorFunc)EnSellnuts_Destroy,
    (ActorFunc)EnSellnuts_Update,
    (ActorFunc)EnSellnuts_Draw,
};

static ColliderCylinderInitType1 sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
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
    { 27, 32, 0, { 0, 0, 0 } },
};

static AnimationInfoS D_80ADD990[] = {
    { &object_dnt_Anim_005488, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_00B0B4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_004AA0, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_004E38, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_0029E8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_005CA8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_0038CC, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_003CC0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_0012F4, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_004700, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_001BC8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_003438, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_001E2C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_000994, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_002268, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_002F08, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_00577C, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &object_dnt_Anim_0029E8, 1.0f, 8, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_0029E8, 1.0f, 4, -1, ANIMMODE_ONCE, -4 },
    { &object_dnt_Anim_0029E8, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_001BC8, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_dnt_Anim_0012F4, -1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_dnt_Anim_002670, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

void func_80ADADD0(EnSellnuts* this, GlobalContext* globalCtx) {
    if (this->unk_338 & 2) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    if (this->unk_338 & 1) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 5);
    }
}

void func_80ADAE64(EnSellnuts* this) {
    s16 currentFrame = this->skelAnime.curFrame;

    switch (currentFrame) {
        case 10:
            this->unk_350 = 1;
            this->unk_354 = 0.1f;
            this->unk_358 = 0.1f;
            this->unk_35C = 0.1f;
            break;

        case 11:
        case 12:
            this->unk_354 += 0.15f;
            this->unk_358 += 0.32f;
            this->unk_35C += 0.15f;
            break;

        case 13:
            this->unk_354 = 0.55f;
            this->unk_358 = 1.05f;
            this->unk_35C = 0.55f;
            break;

        case 14:
            this->unk_354 = 1.0f;
            this->unk_358 = 2.0f;
            this->unk_35C = 1.0f;
            break;

        case 15:
        case 16:
            this->unk_358 -= 0.33f;
            break;

        case 17:
            this->unk_358 = 1.0f;
            break;

        case 18:
        case 19:
            this->unk_358 += 0.27f;
            break;

        case 20:
            this->unk_350 = 3;
            this->unk_358 = 1.8f;
            break;

        case 21:
        case 22:
        case 23:
            this->unk_358 -= 0.2f;
            break;

        case 24:
            this->unk_358 = 1.0f;
            break;
    }
}

void func_80ADAFC0(EnSellnuts* this) {
    s16 currentFrame = this->skelAnime.curFrame;

    switch (currentFrame) {
        case 10:
            this->unk_350 = 0;
            break;

        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            this->unk_350 = 1;
            this->unk_354 -= 0.1f;
            this->unk_358 -= 0.1f;
            this->unk_35C -= 0.1f;
            break;
    }
}

Actor* func_80ADB040(GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actor != NULL) {
        if ((actor->id == ACTOR_EN_SELLNUTS) && !ENSELLNUTS_GET_1(actor)) {
            return actor;
        }
        actor = actor->next;
    }

    return NULL;
}

f32 func_80ADB08C(GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    Actor* sp18 = func_80ADB040(globalCtx);

    if (sp18 != NULL) {
        return Math_Vec3f_DistXZ(&player->actor.world.pos, &sp18->home.pos);
    }

    return 80.0f;
}

void func_80ADB0D8(EnSellnuts* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    if (currentFrame == frameCount) {
        switch (this->unk_340) {
            case 0x611:
            case 0x62A:
                this->unk_34C = 0;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 0);
                this->actionFunc = func_80ADBFA0;
                break;

            case 0x618:
                if (this->unk_34C == 1) {
                    this->unk_34C = 0;
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 0);
                    this->actionFunc = func_80ADB544;
                } else {
                    this->unk_34C = 1;
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 1);
                    this->actionFunc = func_80ADBFA0;
                }
                break;

            case 0xFF:
            case 0x60E:
            case 0x60F:
            case 0x614:
            case 0x628:
                this->unk_34C = 0;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 0);
                this->actionFunc = func_80ADB924;
                break;

            case 0x610:
            case 0x615:
            case 0x616:
            case 0x629:
                this->unk_34C = 1;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 1);
                this->actionFunc = func_80ADB924;
                break;

            case 0x613:
            case 0x619:
                this->unk_34C = 7;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 7);
                this->actionFunc = func_80ADBD64;
                break;
        }
    }
}

void func_80ADB254(EnSellnuts* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xE38);
    if (((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f) ? true : false) &&
        ((this->actor.xzDistToPlayer < 200.0f) ? true : false)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actionFunc = func_80ADB4F4;
        this->unk_34C = 3;
        this->collider.dim.height = 64;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 3);
    } else if (currentFrame == frameCount) {
        if ((this->unk_34C == 4) || (this->unk_34C == 18)) {
            this->unk_34C = 17;
            this->collider.dim.height = 0;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
            SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 17);
        } else if (this->unk_34C == 2) {
            this->unk_34C = 16;
            this->collider.dim.height = 32;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
            SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 16);
        } else if (this->unk_34C == 17) {
            if (DECR(this->unk_34E) == 0) {
                this->unk_34E = Rand_ZeroOne() * 10.0f;
                this->unk_34C = 2;
                this->collider.dim.height = 32;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 2);
            }
        } else if (this->unk_34C == 16) {
            if (DECR(this->unk_34E) == 0) {
                this->unk_34E = Rand_S16Offset(40, 40);
                this->unk_34C = 18;
                this->collider.dim.height = 32;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 18);
            }
        }
    }
}

void func_80ADB4F4(EnSellnuts* this, GlobalContext* globalCtx) {
    if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
        this->actionFunc = func_80ADB544;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 0);
    }
}

void func_80ADB544(EnSellnuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 0x7D0, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if (Player_GetExchangeItemId(globalCtx) == EXCH_ITEM_2A) {
            player->actor.textId = D_80ADD928[this->unk_33A];
            this->unk_340 = player->actor.textId;
            this->actionFunc = func_80ADBAB8;
        } else {
            switch (this->unk_340) {
                case 0x60E:
                    gSaveContext.save.weekEventReg[17] |= 0x20;
                    gSaveContext.save.weekEventReg[86] |= 4;
                    Message_StartTextbox(globalCtx, this->unk_340, &this->actor);
                    this->actionFunc = func_80ADB0D8;
                    break;

                case 0x628:
                    gSaveContext.save.weekEventReg[77] |= 0x40;
                    gSaveContext.save.weekEventReg[86] |= 4;
                    Message_StartTextbox(globalCtx, this->unk_340, &this->actor);
                    this->actionFunc = func_80ADB0D8;
                    break;

                case 0x614:
                    gSaveContext.save.weekEventReg[17] |= 0x40;
                    Message_StartTextbox(globalCtx, this->unk_340, &this->actor);
                    this->actionFunc = func_80ADB0D8;
                    break;

                case 0x610:
                case 0x616:
                case 0x629:
                    Message_StartTextbox(globalCtx, this->unk_340, &this->actor);
                    this->actionFunc = func_80ADB0D8;
                    break;

                default:
                    this->actionFunc = func_80ADBAB8;
                    break;
            }
        }
    } else if (((this->actor.xzDistToPlayer < 80.0f) &&
                (((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false)) ||
               this->actor.isTargeted) {
        func_800B85E0(&this->actor, globalCtx, 80.0f, EXCH_ITEM_2A);
        if (player->transformation == PLAYER_FORM_DEKU) {
            if (gSaveContext.save.day == 3) {
                this->unk_33A = 2;
                if (gSaveContext.save.weekEventReg[77] & 0x40) {
                    this->unk_340 = D_80ADD918[this->unk_33A];
                } else {
                    this->unk_340 = D_80ADD910[this->unk_33A];
                }
            } else {
                this->unk_33A = 1;
                if (gSaveContext.save.weekEventReg[17] & 0x20) {
                    this->unk_340 = D_80ADD918[this->unk_33A];
                } else {
                    this->unk_340 = D_80ADD910[this->unk_33A];
                }
            }
        } else if (gSaveContext.save.weekEventReg[17] & 0x40) {
            this->unk_340 = D_80ADD918[this->unk_33A];
        } else {
            this->unk_340 = D_80ADD910[this->unk_33A];
        }
    }

    if (!(((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false) ||
        !((this->actor.xzDistToPlayer < 200.0f) ? true : false)) {
        this->unk_34C = 4;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 4);
        this->actionFunc = func_80ADB254;
    }
}

void func_80ADB924(EnSellnuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u8 msgState = Message_GetState(&globalCtx->msgCtx);
    s32 item;

    if (msgState == 0x10) {
        item = func_80123810(globalCtx);
        if (item > EXCH_ITEM_NONE) {
            if (item == EXCH_ITEM_2A) {
                player->actor.textId = D_80ADD928[this->unk_33A];
                this->unk_340 = player->actor.textId;
                player->exchangeItemId = item;
                this->actionFunc = func_80ADBAB8;
            } else {
                player->actor.textId = D_80ADD920[this->unk_33A];
                this->unk_340 = player->actor.textId;
                this->actionFunc = func_80ADB0D8;
            }
            func_801477B4(globalCtx);
        } else if (item < EXCH_ITEM_NONE) {
            this->unk_340 = D_80ADD920[this->unk_33A];
            func_80151938(globalCtx, this->unk_340);
            this->actionFunc = func_80ADB0D8;
        }
    } else if ((msgState == 5) && Message_ShouldAdvance(globalCtx)) {
        if (this->unk_340 == D_80ADD910[this->unk_33A]) {
            this->unk_340 = D_80ADD938[this->unk_33A];
            func_80151938(globalCtx, this->unk_340);
            this->actionFunc = func_80ADB0D8;
        } else {
            this->unk_340 = 0xFF;
            func_80151938(globalCtx, this->unk_340);
            this->actionFunc = func_80ADB0D8;
        }
    }
}

void func_80ADBAB8(EnSellnuts* this, GlobalContext* globalCtx) {
    u8 sp27 = Message_GetState(&globalCtx->msgCtx);
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    if (this->unk_368 == 0x28) {
        this->unk_34C = 5;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 5);
    }

    this->unk_368++;

    if ((currentFrame == frameCount) && (this->unk_34C == 5)) {
        this->unk_34C = 6;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 6);
    }

    if ((sp27 == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->actionFunc = func_80ADBBEC;
        func_800B7298(globalCtx, NULL, 0x13);
    }
}

void func_80ADBBEC(EnSellnuts* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        gSaveContext.save.weekEventReg[17] |= 0x80;
        this->actionFunc = func_80ADBCE4;
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_DEED_LAND, 300.0f, 300.0f);
    }
}

void func_80ADBC60(EnSellnuts* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, this->unk_340, &this->actor);
        this->actionFunc = func_80ADB0D8;
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, EXCH_ITEM_MINUS1);
        this->unk_340 = D_80ADD930[this->unk_33A];
    }
}

void func_80ADBCE4(EnSellnuts* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 6) && Message_ShouldAdvance(globalCtx)) {
        func_800B85E0(&this->actor, globalCtx, 400.0f, EXCH_ITEM_MINUS1);
        this->unk_340 = D_80ADD930[this->unk_33A];
        this->actionFunc = func_80ADBC60;
    }
}

void func_80ADBD64(EnSellnuts* this, GlobalContext* globalCtx) {
    u8 sp27 = Message_GetState(&globalCtx->msgCtx);
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    if ((currentFrame == frameCount) && (this->unk_34C == 7)) {
        this->unk_34C = 0;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 0);
    }

    if ((sp27 == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->unk_338 &= ~2;
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->unk_34C = 8;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 8);
        this->actionFunc = func_80ADBE80;
    }
}

void func_80ADBE80(EnSellnuts* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    func_80ADAE64(this);
    if (this->unk_366 == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->cutscene, &this->actor);
            this->unk_366 = 1;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->cutscene);
            return;
        }
    }

    if (currentFrame == frameCount) {
        this->unk_350 = 4;
        this->unk_34C = 19;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 19);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
        this->unk_338 &= ~1;
        this->unk_338 |= 8;
        this->unk_32C = this->actor.world.pos.y;
        this->actionFunc = func_80ADC2CC;
    }
}

void func_80ADBFA0(EnSellnuts* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        if (this->unk_34C == 0) {
            this->actionFunc = func_80ADB544;
        } else {
            this->actionFunc = func_80ADB0D8;
        }
    }
}

void func_80ADC034(EnSellnuts* this, GlobalContext* globalCtx) {
    this->unk_344 += this->unk_364;
    if (this->unk_360 >= 1.0f) {
        this->unk_360 = 1.0f;
        this->actor.velocity.y = 5.0f;
    } else {
        this->actor.velocity.y = 5.0f;
        this->unk_360 += 0.1f;
    }

    if ((this->actor.home.pos.y + 200.0f) < this->actor.world.pos.y) {
        Math_ApproachF(&this->actor.velocity.y, 0.0f, 0.2f, 1.0f);
        this->unk_34C = 10;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 10);
        this->unk_368 = 0;
        this->actionFunc = func_80ADC37C;
    }
}

void func_80ADC118(EnSellnuts* this, GlobalContext* globalCtx) {
    Vec3f sp34;
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    if (currentFrame == frameCount) {
        Math_SmoothStepToS(&this->unk_364, 0x1C71, 3, 0x100, 0);
        this->unk_344 += this->unk_364;
        this->actor.shape.yOffset = 1500.0f;
        Math_SmoothStepToS(&this->actor.shape.rot.y, 0x4000, 3, 0x7D0, 0);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (DECR(this->unk_34A) == 0) {
        if (!(this->unk_328 & 3)) {
            sp34 = this->actor.world.pos;
            func_800B14D4(globalCtx, 20.0f, &sp34);
        }
        this->actor.velocity.y = 5.0f;
    } else if (!(this->unk_328 & 3)) {
        sp34.x = this->actor.world.pos.x;
        sp34.y = this->unk_32C;
        sp34.z = this->actor.world.pos.z;
        func_800B14D4(globalCtx, 20.0f, &sp34);
    }

    if ((this->actor.home.pos.y + 22.5f) < this->actor.world.pos.y) {
        this->unk_34C = 9;
        this->unk_360 = 0.3f;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 9);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actionFunc = func_80ADC034;
    }
}

void func_80ADC2CC(EnSellnuts* this, GlobalContext* globalCtx) {
    f32 sp24 = this->unk_32C - this->actor.world.pos.y;
    Vec3f sp18;

    this->unk_344 += this->unk_364;
    if (!(this->unk_328 & 3)) {
        sp18.x = this->actor.world.pos.x;
        sp18.y = this->unk_32C;
        sp18.z = this->actor.world.pos.z;
        func_800B14D4(globalCtx, 20.0f, &sp18);
    }

    if (sp24 > 5.0f) {
        this->actionFunc = func_80ADC118;
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
    }
}

void func_80ADC37C(EnSellnuts* this, GlobalContext* globalCtx) {
    Vec3s sp30;
    f32 sp2C;

    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;
    if (this->path != NULL) {
        sp2C = func_80ADCFE8(this->path, this->unk_334, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            sp30.y = this->actor.wallYaw;
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 0xA, 0x12C, 0);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->unk_342 = 0x1000;
        this->unk_344 += this->unk_364;
        this->actor.world.rot.x = -sp30.x;
        if (func_80ADCE4C(this, this->path, this->unk_334) && (sp2C < 500.0f)) {
            if (this->unk_334 >= (this->path->count - 1)) {
                ActorCutscene_Stop(this->cutscene);
                this->actionFunc = func_80ADC580;
            } else {
                this->unk_334++;
            }
        }
    } else if (this->actor.playerHeightRel > 500.0f) {
        ActorCutscene_Stop(this->cutscene);
        this->actionFunc = func_80ADC580;
    }

    Math_ApproachF(&this->actor.speedXZ, 2.0f, 0.2f, 1.0f);
    Actor_MoveWithoutGravity(&this->actor);
    if (this->unk_366 == 2) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->cutscene, &this->actor);
            this->unk_366 = 3;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
            return;
        }
    } else if ((this->unk_366 == 1) && (this->unk_368 == 20)) {
        ActorCutscene_Stop(this->cutscene);
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->unk_366 = 2;
    }

    this->unk_368++;
}

void func_80ADC580(EnSellnuts* this, GlobalContext* globalCtx) {
    Actor_MarkForDeath(&this->actor);
}

void func_80ADC5A4(EnSellnuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        player->linearVelocity = 0.0f;
        this->actor.flags &= ~ACTOR_FLAG_10000;
        Message_StartTextbox(globalCtx, this->unk_340, &this->actor);
        if (this->unk_340 == 0x625) {
            this->unk_338 |= 1;
            this->actor.draw = EnSellnuts_Draw;
            D_80ADD940 = 0;
            player->stateFlags1 |= 0x20;
            this->actionFunc = func_80ADC7B4;
        } else {
            player->stateFlags1 &= ~0x20;
            this->actionFunc = func_80ADC6D0;
        }
    } else if (func_80ADB08C(globalCtx) < 80.0f) {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, globalCtx, this->actor.xzDistToPlayer);
    }
}

void func_80ADC6D0(EnSellnuts* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        if (player->transformation == PLAYER_FORM_DEKU) {
            if (gSaveContext.save.day == 3) {
                this->unk_33A = 2;
            } else {
                this->unk_33A = 1;
            }
        } else {
            this->unk_33A = 0;
        }
        this->unk_340 = D_80ADD910[this->unk_33A];
        this->actionFunc = func_80ADB544;
    }
}

void func_80ADC7B4(EnSellnuts* this, GlobalContext* globalCtx) {
    s32 temp = Message_GetState(&globalCtx->msgCtx);

    if (this->unk_366 == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->cutscene, &this->actor);
            this->unk_366 = 1;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    } else if ((this->unk_366 == 1) && (temp == 5) && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        this->unk_366 = 0;
        ActorCutscene_Stop(this->cutscene);
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->cutscene);
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->unk_338 |= 8;
        this->actionFunc = func_80ADC8C4;
    }
}

void func_80ADC8C4(EnSellnuts* this, GlobalContext* globalCtx) {
    Vec3s sp30;

    if (this->unk_366 == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->cutscene, &this->actor);
            this->unk_366 = 1;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->cutscene);
            return;
        }
    }

    if (this->path != NULL) {
        func_80ADCFE8(this->path, this->unk_334, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & 8) {
            sp30.y = this->actor.wallYaw;
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 0xA, 0x12C, 0);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->unk_342 = 0x1000;
        this->unk_344 += 0x1C71;
        this->actor.world.rot.x = -sp30.x;
        if (func_80ADCE4C(this, this->path, this->unk_334)) {
            if (this->unk_334 >= (this->path->count - 1)) {
                this->unk_34C = 22;
                this->actor.gravity = -1.0f;
                this->actor.velocity.y = -1.0f;
                this->actor.speedXZ = 0.0f;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
                this->unk_338 &= ~1;
                this->unk_338 &= ~2;
                this->actionFunc = func_80ADCA64;
                return;
            }
            this->unk_334++;
        }
        Math_ApproachF(&this->actor.speedXZ, 2.0f, 0.2f, 1.0f);
        Actor_MoveWithoutGravity(&this->actor);
    }
}

void func_80ADCA64(EnSellnuts* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    if (this->unk_34C == 22) {
        Math_SmoothStepToS(&this->unk_364, 0, 3, 0x100, 0);
        this->actor.shape.rot.y += 0x4000;
        this->unk_360 *= 0.93f;
        if (this->actor.world.pos.y < -50.0f) {
            ActorCutscene_Stop(this->cutscene);
            this->unk_338 &= ~8;
            this->unk_34E = 20;
            this->unk_350 = 4;
            this->unk_34C = 19;
            this->actor.velocity.y = 0.0f;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DOWN);
        }
        return;
    }

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xE38);
    if (currentFrame == frameCount) {
        if (this->unk_34C == 19) {
            this->unk_34C = 17;
            this->collider.dim.height = 0;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, 17);
        } else if (this->unk_34C == 17) {
            ActorCutscene_Stop(this->cutscene);
            gSaveContext.save.weekEventReg[73] |= 4;
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80ADCC04(EnSellnuts* this, GlobalContext* globalCtx) {
    s16 currentFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(D_80ADD990[this->unk_34C].animation);

    if (this->unk_34C == 3) {
        if (currentFrame == frameCount) {
            this->unk_350 = 4;
            this->unk_34C = 21;
            this->unk_354 = 1.0f;
            this->unk_358 = 1.0f;
            this->unk_35C = 1.0f;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
        }
    } else if (this->unk_34C == 21) {
        func_80ADAFC0(this);
        if (currentFrame == 0) {
            if (func_80ADB08C(globalCtx) < 9999.0f) {
                this->actor.flags |= ACTOR_FLAG_10000;
                func_800B8614(&this->actor, globalCtx, 9999.0f);
            }
            this->unk_340 = 0x626;
            this->unk_34C = 0;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
            this->actionFunc = func_80ADC5A4;
        }
    }
}

void func_80ADCD3C(EnSellnuts* this, GlobalContext* globalCtx) {
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xE38);
    if (gSaveContext.save.weekEventReg[73] & 4) {
        this->unk_338 |= 2;
        this->unk_338 |= 1;
        this->unk_340 = 0x626;
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.gravity = -1.0f;
        this->actor.draw = EnSellnuts_Draw;
        this->unk_34A = 50;
        this->unk_34E = Rand_ZeroOne() * 10.0f;
        this->collider.dim.height = 64;
        this->unk_34C = 3;
        this->unk_350 = 4;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
        this->actionFunc = func_80ADCC04;
    } else if (D_80ADD940 != 0) {
        this->collider.dim.height = 64;
    }
}

s32 func_80ADCE4C(EnSellnuts* this, Path* path, s32 arg2) {
    Vec3s* points = Lib_SegmentedToVirtual(path->points);
    s32 count = path->count;
    s32 var = arg2;
    s32 ret = false;
    f32 pointX;
    f32 pointY;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &points[var]);
    if (var == 0) {
        pointX = points[1].x - points[0].x;
        pointY = points[1].z - points[0].z;
    } else if ((u32)count == (u32)(var + 1)) {
        pointX = points[count - 1].x - points[count - 2].x;
        pointY = points[count - 1].z - points[count - 2].z;
    } else {
        pointX = points[var + 1].x - points[var - 1].x;
        pointY = points[var + 1].z - points[var - 1].z;
    }

    func_8017B7F8(&sp30, RADF_TO_BINANG(func_80086B30(pointX, pointY)), &sp44, &sp40, &sp3C);
    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        ret = true;
    }

    return ret;
}

f32 func_80ADCFE8(Path* path, s32 arg1, Vec3f* pos, Vec3s* arg3) {
    s32 pad;
    Vec3f sp20;
    Vec3s* points;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        sp20.x = points->x;
        sp20.y = points->y;
        sp20.z = points->z;
    }

    arg3->y = Math_Vec3f_Yaw(pos, &sp20);
    arg3->x = Math_Vec3f_Pitch(pos, &sp20);
    return sp20.y - pos->y;
}

void EnSellnuts_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSellnuts* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad2;

    if ((gSaveContext.save.weekEventReg[17] & 0x80) || (gSaveContext.save.weekEventReg[61] & 0x10)) {
        Actor_MarkForDeath(&this->actor);
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dnt_Skel_00AC70, &object_dnt_Anim_005488, this->jointTable,
                       this->morphTable, 28);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinderType1(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    this->path = SubS_GetPathByIndex(globalCtx, ENSELLNUTS_GET_FC00(&this->actor), 0x3F);
    this->cutscene = this->actor.cutscene;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.cylRadius = 0;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_350 = 0;
    this->unk_366 = 0;
    this->unk_374 = 0.01f;
    this->unk_370 = 0.01f;
    this->unk_36C = 0.01f;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    if (gSaveContext.save.weekEventReg[73] & 4) {
        if (ENSELLNUTS_GET_1(&this->actor)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        this->unk_338 |= 2;
        this->unk_338 |= 1;
        if (player->transformation == PLAYER_FORM_DEKU) {
            if (gSaveContext.save.day == 3) {
                this->unk_33A = 2;
            } else {
                this->unk_33A = 1;
            }
        } else {
            this->unk_33A = 0;
        }
        this->unk_340 = D_80ADD910[this->unk_33A];
        this->actor.gravity = -1.0f;
        this->unk_34A = 50;
        this->unk_34C = 4;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
        this->actionFunc = func_80ADB254;
        return;
    }

    D_80ADD940 = 1;
    if (ENSELLNUTS_GET_1(&this->actor)) {
        this->unk_338 |= 2;
        this->unk_338 &= ~1;
        this->unk_340 = 0x625;
        this->actor.gravity = 0.0f;
        this->actor.draw = NULL;
        this->unk_34C = 20;
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->unk_35C = 1.0f;
        this->unk_358 = 1.0f;
        this->unk_354 = 1.0f;
        this->unk_360 = 1.0f;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
        this->actionFunc = func_80ADC5A4;
    } else {
        this->unk_338 |= 2;
        this->unk_338 &= ~1;
        this->actor.flags &= ~ACTOR_FLAG_1;
        this->actor.gravity = 0.0f;
        this->actor.draw = NULL;
        this->unk_34C = 4;
        this->unk_34E = 20;
        this->collider.dim.height = 64;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80ADD990, this->unk_34C);
        this->actionFunc = func_80ADCD3C;
    }
}

void EnSellnuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSellnuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnSellnuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSellnuts* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    this->unk_328++;
    if (player->transformation == PLAYER_FORM_DEKU) {
        if (gSaveContext.save.day == 3) {
            this->unk_33A = 2;
        } else {
            this->unk_33A = 1;
        }
    } else {
        this->unk_33A = 0;
    }

    Actor_SetFocus(&this->actor, 60.0f);
    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_Update(&this->skelAnime);
    Actor_MoveWithGravity(&this->actor);
    this->actionFunc(this, globalCtx);
    if (this->unk_338 & 8) {
        func_800B9010(&this->actor, NA_SE_EN_AKINDO_FLY - SFX_FLAG);
    }
    func_80ADADD0(this, globalCtx);
}

s32 EnSellnuts_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                Actor* thisx) {
    EnSellnuts* this = THIS;

    if (((this->unk_34C == 4) && (this->unk_350 == 0)) || ((this->unk_34C == 8) && (this->unk_350 == 0)) ||
        ((this->unk_34C == 21) && (this->unk_350 == 0)) || (this->unk_34C == 18) || (this->unk_34C == 2) ||
        ((this->unk_34C == 3) && (this->unk_350 == 0)) || ((this->unk_34C == 17) && (this->unk_350 == 0)) ||
        (this->unk_34C == 5) || (this->unk_34C == 6) || (this->unk_34C == 7) || (this->unk_34C == 1) ||
        (this->unk_34C == 0) || (this->unk_34C == 16)) {
        if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 23) || (limbIndex == 24) ||
            (limbIndex == 15)) {
            *dList = NULL;
        }
    } else if ((this->unk_34C == 8) || (this->unk_34C == 21) || (this->unk_34C == 19) ||
               ((this->unk_34C == 3) && (this->unk_350 == 4)) || ((this->unk_34C == 17) && (this->unk_350 == 4))) {
        switch (this->unk_350) {
            case 1:
                if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 25)) {
                    *dList = NULL;
                }
                break;

            case 3:
            case 4:
                if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 15) ||
                    (limbIndex == 25)) {
                    *dList = NULL;
                }
                break;

            case 5:
                if ((limbIndex == 15) || (limbIndex == 25)) {
                    *dList = NULL;
                }
                break;
        }
    } else if ((this->unk_34C == 9) || (this->unk_34C == 10)) {
        if ((limbIndex == 15) || (limbIndex == 25)) {
            *dList = NULL;
        }
    } else if (((this->unk_34C == 22) || (this->unk_34C == 20)) &&
               ((limbIndex == 15) || (limbIndex == 25) || (limbIndex == 27))) {
        *dList = NULL;
    }

    if (limbIndex == 24) {
        Matrix_InsertXRotation_s(this->unk_342, MTXMODE_APPLY);
    }

    if (limbIndex == 26) {
        if ((this->unk_34C == 6) || (this->unk_34C == 5) || (this->unk_34C == 7)) {
            *dList = object_dnt_DL_001350;
        } else {
            *dList = object_dnt_DL_008290;
        }
    }

    return false;
}

void EnSellnuts_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnSellnuts_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnSellnuts* this = THIS;

    if (((this->unk_350 == 1) || (this->unk_350 == 3)) && ((limbIndex == 23) || (limbIndex == 24))) {
        Matrix_Scale(this->unk_354, this->unk_358, this->unk_35C, MTXMODE_APPLY);
    }

    if (((this->unk_34C == 9) || (this->unk_34C == 20) || (this->unk_34C == 22)) &&
        ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27))) {
        Matrix_Scale(this->unk_360, this->unk_360, this->unk_360, MTXMODE_APPLY);
    }

    if (limbIndex == 24) {
        Matrix_RotateY(this->unk_344, MTXMODE_APPLY);
    }
}

void EnSellnuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnSellnuts* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnSellnuts_OverrideLimbDraw, EnSellnuts_PostLimbDraw,
                                   EnSellnuts_TransformLimbDraw, &this->actor);
}
