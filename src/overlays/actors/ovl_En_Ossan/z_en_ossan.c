/*
 * File: z_en_ossan.c
 * Overlay: ovl_En_Ossan
 * Description: Trading Post Shop
 */

#include "z_en_ossan.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnOssan*)thisx)

#define LOOKED_AT_PLAYER (1 << 0)
#define END_INTERACTION (1 << 1)

void EnOssan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_Update(Actor* thisx, GlobalContext* globalCtx);

void EnOssan_CuriosityShopMan_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnOssan_PartTimeWorker_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnOssan_CuriosityShopMan_Init(EnOssan* this, GlobalContext* globalCtx);
u16 EnOssan_CuriosityShopMan_GetWelcome(EnOssan* this, GlobalContext* globalCtx);

void EnOssan_PartTimeWorker_Init(EnOssan* this, GlobalContext* globalCtx);
u16 EnOssan_PartTimerWorker_GetWelcome(EnOssan* this, GlobalContext* globalCtx);

void EnOssan_InitShop(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_Idle(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_BeginInteraction(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_Hello(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_SetHaveMet(EnOssan* this);
void EnOssan_StartShopping(GlobalContext* globalCtx, EnOssan* this);
void EnOssan_FaceShopkeeper(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_LookToShopkeeperFromShelf(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_TalkToShopkeeper(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_LookToLeftShelf(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_LookToRightShelf(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_BrowseLeftShelf(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_BrowseRightShelf(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_SelectItem(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_BuyItemWithFanfare(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_CannotBuy(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_CanBuy(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_SetupItemPurchased(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_ItemPurchased(EnOssan* this, GlobalContext* globalCtx);
void EnOssan_ResetItemPosition(EnOssan* this);
void EnOssan_Blink(EnOssan* this);
void EnOssan_GetCutscenes(EnOssan* this, GlobalContext* globalCtx);

s32 EnOssan_ReturnItemToShelf(EnOssan* this);
s32 EnOssan_TakeItemOffShelf(EnOssan* this);

typedef enum {
    /* 0 */ ENOSSAN_CUTSCENESTATE_STOPPED,
    /* 1 */ ENOSSAN_CUTSCENESTATE_WAITING,
    /* 2 */ ENOSSAN_CUTSCENESTATE_PLAYING
} EnOssanCutsceneState;

typedef enum {
    /* 00 */ FSN_ANIMATION_IDLE,
    /* 01 */ FSN_ANIMATION_SCRATCH_BACK,
    /* 02 */ FSN_ANIMATION_TURN_AROUND_FORWARD,
    /* 03 */ FSN_ANIMATION_TURN_AROUND_REVERSE,
    /* 04 */ FSN_ANIMATION_HANDS_ON_COUNTER_START,
    /* 05 */ FSN_ANIMATION_HANDS_ON_COUNTER_LOOP,
    /* 06 */ FSN_ANIMATION_HAND_ON_FACE_START,
    /* 07 */ FSN_ANIMATION_HAND_ON_FACE_LOOP,
    /* 08 */ FSN_ANIMATION_LEAN_FORWARD_START,
    /* 09 */ FSN_ANIMATION_LEAN_FORWARD_LOOP,
    /* 10 */ FSN_ANIMATION_SLAM_COUNTER_START,
    /* 11 */ FSN_ANIMATION_SLAM_COUNTER_LOOP,
    /* 12 */ FSN_ANIMATION_MAKE_OFFER,
    /* 13 */ FSN_ANIMATION_MAX
} FsnAnimation;

typedef enum {
    /* 00 */ ANI_ANIMATION_STANDING_NORMAL_LOOP_1,
    /* 01 */ ANI_ANIMATION_STANDING_NORMAL_LOOP_2,
    /* 02 */ ANI_ANIMATION_STANDING_NORMAL_ONCE_FORWARD_1,
    /* 03 */ ANI_ANIMATION_STANDING_NORMAL_ONCE_REVERSE,
    /* 04 */ ANI_ANIMATION_STANDING_NORMAL_ONCE_FORWARD_2,
    /* 05 */ ANI_ANIMATION_STANDING_NORMAL_LOOP_3,
    /* 06 */ ANI_ANIMATION_STANDING_NORMAL_ONCE_FORWARD_3,
    /* 07 */ ANI_ANIMATION_STANDING_NORMAL_LOOP_4,
    /* 08 */ ANI_ANIMATION_APOLOGY_START,
    /* 09 */ ANI_ANIMATION_APOLOGY_LOOP,
    /* 10 */ ANI_ANIMATION_STANDING_NORMAL_ONCE_FORWARD_4,
    /* 11 */ ANI_ANIMATION_STANDING_NORMAL_LOOP_5,
    /* 12 */ ANI_ANIMATION_MAX
} AniAnimation;

const ActorInit En_Ossan_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOssan),
    (ActorFunc)EnOssan_Init,
    (ActorFunc)EnOssan_Destroy,
    (ActorFunc)EnOssan_Update,
    (ActorFunc)NULL,
};

static AnimationInfoS sAnimationsCuriosityShopMan[] = {
    { &gFsnIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gFsnScratchBackAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gFsnTurnAroundAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gFsnTurnAroundAnim, -1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gFsnHandsOnCounterStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gFsnHandsOnCounterLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gFsnHandOnFaceStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gFsnHandOnFaceLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gFsnLeanForwardStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gFsnLeanForwardLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gFsnSlamCounterStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gFsnSlamCounterLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gFsnMakeOfferAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
};

static AnimationInfoS sAnimationsPartTimeWorker[] = {
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -10 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -10 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gAniStandingNormalAnim, -1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gAniHandBehindHeadApologyAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -5 },
    { &gAniHandBehindHeadApologyAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -5 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gAniStandingNormalAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
};

static s16 sObjectIds[] = { OBJECT_FSN, OBJECT_ANI };

static AnimationInfoS* sAnimations[] = { sAnimationsCuriosityShopMan, sAnimationsPartTimeWorker };

static f32 sActorScales[] = { 0.01f, 0.01f };

static ShopItem sShops[][8] = {
    { { SI_NUTS_1, { 50, 68, -195 } },
      { SI_STICK_1, { 50, 92, -195 } },
      { SI_ARROWS_LARGE_1, { 80, 68, -195 } },
      { SI_ARROWS_MEDIUM_1, { 80, 92, -195 } },
      { SI_FAIRY_1, { -50, 68, -195 } },
      { SI_POTION_GREEN_2, { -50, 92, -195 } },
      { SI_SHIELD_HERO_1, { -80, 68, -195 } },
      { SI_POTION_RED_2, { -80, 92, -195 } } },

    { { SI_NUTS_2, { 50, 68, -195 } },
      { SI_STICK_2, { 50, 92, -195 } },
      { SI_ARROWS_LARGE_2, { 80, 68, -195 } },
      { SI_ARROWS_MEDIUM_2, { 80, 92, -195 } },
      { SI_FAIRY_2, { -50, 68, -195 } },
      { SI_POTION_GREEN_3, { -50, 92, -195 } },
      { SI_SHIELD_HERO_2, { -80, 68, -195 } },
      { SI_POTION_RED_3, { -80, 92, -195 } } },
};

static u16 sWelcomeHumanTextIds[] = { 0X06A4, 0X06C1 };

static u16 sTalkOptionTextIds[] = { 0X06AB, 0X06C8 };

static u16 sWelcomeGoronFirstTimeTextIds[] = { 0X06A5, 0X06C2 };

static u16 sWelcomeZoraFirstTimeTextIds[] = { 0X06A7, 0X06C4 };

static u16 sWelcomeDekuFirstTimeTextIds[] = { 0X06A9, 0X06C6 };

static u16 sWelcomeGoronTextIds[] = { 0X06A6, 0X06C3 };

static u16 sWelcomeZoraTextIds[] = { 0X06A8, 0X06C5 };

static u16 sWelcomeDekuTextIds[] = { 0X06AA, 0X06C7 };

static u16 sNeedEmptyBottleTextIds[] = { 0X06BC, 0X06D9 };

static u16 sNeedRupeesTextIds[] = { 0X06BD, 0X06DA };

static u16 sNoRoomTextIds[] = { 0X06BE, 0X06DB };

static u16 sBuySuccessTextIds[] = { 0X06BF, 0X06DC };

static u16 sCannotGetNowTextIds[] = { 0X06C0, 0X06DD };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

void EnOssan_SetupAction(EnOssan* this, EnOssanActionFunc action) {
    this->actionFunc = action;
}

s32 EnOssan_TestItemSelected(GlobalContext* globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A);
    }
    return CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
           CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B) ||
           CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_CUP);
}

void EnOssan_CheckValidSpawn(EnOssan* this) {
    switch (gSaveContext.save.day) {
        case 1:
        case 2:
            if (gSaveContext.save.time <= CLOCK_TIME(21, 30) && gSaveContext.save.time > CLOCK_TIME(6, 00)) {
                if (this->actor.params != ENOSSAN_CURIOSITY_SHOP_MAN) {
                    Actor_MarkForDeath(&this->actor);
                }
            } else if (this->actor.params == ENOSSAN_CURIOSITY_SHOP_MAN) {
                Actor_MarkForDeath(&this->actor);
            }
            break;
        case 3:
            if (this->actor.params == ENOSSAN_CURIOSITY_SHOP_MAN) {
                Actor_MarkForDeath(&this->actor);
            }
            if (!(gSaveContext.save.time <= CLOCK_TIME(22, 00) && gSaveContext.save.time >= CLOCK_TIME(6, 00))) {
                if (this->actor.params != ENOSSAN_CURIOSITY_SHOP_MAN) {
                    Actor_MarkForDeath(&this->actor);
                }
            }
            break;
    }
}

void EnOssan_RotateHead(EnOssan* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.params == ENOSSAN_PART_TIME_WORKER) {
        if (player->transformation == PLAYER_FORM_ZORA) {
            Math_SmoothStepToS(&this->headRotPartTimeWorker.y, this->headRot.y, 3, 2000, 0);
        } else if (this->flags & LOOKED_AT_PLAYER) {
            Math_SmoothStepToS(&this->headRotPartTimeWorker.y, 8000, 3, 2000, 0);
        } else {
            Math_SmoothStepToS(&this->headRotPartTimeWorker.y, this->headRot.y, 3, 2000, 0);
            if (ABS_ALT(this->headRotPartTimeWorker.y - this->headRot.y) < 16) {
                this->flags |= LOOKED_AT_PLAYER;
            }
        }
    }
}

void EnOssan_SpawnShopItems(EnOssan* this, GlobalContext* globalCtx, ShopItem* shop) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->items); i++, shop++) {
        if (shop->shopItemId < 0) {
            this->items[i] = NULL;
        } else {
            this->items[i] = (EnGirlA*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA, shop->spawnPos.x,
                                                   shop->spawnPos.y, shop->spawnPos.z, 0, 0, 0, shop->shopItemId);
        }
    }
}

void EnOssan_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnOssan* this = THIS;
    s16 id;

    //! @bug Condition is impossible, params cannot be both greater then 1 AND less then 0.
    if (this->actor.params > ENOSSAN_PART_TIME_WORKER && this->actor.params < ENOSSAN_CURIOSITY_SHOP_MAN) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    id = sObjectIds[this->actor.params];
    this->objIndex = Object_GetIndex(&globalCtx->objectCtx, id);
    if (this->objIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    EnOssan_CheckValidSpawn(this);
    Actor_ProcessInitChain(&this->actor, sInitChain);
    EnOssan_SetupAction(this, EnOssan_InitShop);
}

void EnOssan_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnOssan* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnOssan_UpdateCursorPos(GlobalContext* globalCtx, EnOssan* this) {
    s16 x;
    s16 y;

    Actor_GetScreenPos(globalCtx, &this->items[this->cursorIdx]->actor, &x, &y);
    this->cursorPos.x = x;
    this->cursorPos.y = y;
}

void EnOssan_EndInteraction(GlobalContext* globalCtx, EnOssan* this) {
    Player* player = GET_PLAYER(globalCtx);

    Actor_ProcessTalkRequest(&this->actor, &globalCtx->state);
    globalCtx->msgCtx.msgMode = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = false;
    player->stateFlags2 &= ~0x20000000;
    globalCtx->interfaceCtx.unk_222 = 0;
    globalCtx->interfaceCtx.unk_224 = 0;
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_PLAYING) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_STOPPED;
    }
    if (this->actor.params == ENOSSAN_CURIOSITY_SHOP_MAN) {
        // EnOssan_BeginInteraction includes the animation of him turning around, before being set to idle
        EnOssan_SetupAction(this, EnOssan_BeginInteraction);
    } else {
        EnOssan_SetupAction(this, EnOssan_Idle);
    }
}

s32 EnOssan_TestEndInteraction(EnOssan* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        EnOssan_EndInteraction(globalCtx, this);
        return true;
    }
    return false;
}

s32 EnOssan_TestCancelOption(EnOssan* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        return true;
    }
    return false;
}

void EnOssan_SetupStartShopping(GlobalContext* globalCtx, EnOssan* this, u8 skipHello) {
    func_8011552C(globalCtx, 0x10);
    if (!skipHello) {
        EnOssan_SetupAction(this, EnOssan_Hello);
    } else {
        EnOssan_StartShopping(globalCtx, this);
    }
}

void EnOssan_StartShopping(GlobalContext* globalCtx, EnOssan* this) {
    EnOssan_SetupAction(this, EnOssan_FaceShopkeeper);
    func_80151938(globalCtx, 0x640);
    func_8011552C(globalCtx, 6);
    this->stickRightPrompt.isEnabled = true;
    this->stickLeftPrompt.isEnabled = true;
}

void EnOssan_SetupLookToShopkeeperFromShelf(GlobalContext* globalCtx, EnOssan* this) {
    play_sound(NA_SE_SY_CURSOR);
    this->drawCursor = 0;
    EnOssan_SetupAction(this, EnOssan_LookToShopkeeperFromShelf);
}

void EnOssan_Idle(EnOssan* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SubS_FillLimbRotTables(globalCtx, this->limbRotTableY, this->limbRotTableZ, ARRAY_COUNT(this->limbRotTableY));
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        player->stateFlags2 |= 0x20000000;
        EnOssan_SetupAction(this, EnOssan_BeginInteraction);
        if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_STOPPED) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookToShopkeeperCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = ENOSSAN_CUTSCENESTATE_WAITING;
        }
    } else {
        if (this->actor.xzDistToPlayer < 100.0f &&
            (player->actor.world.pos.x >= -40.0f && player->actor.world.pos.x <= 40.0f) &&
            (player->actor.world.pos.z >= -91.0f && player->actor.world.pos.z <= -60.0f)) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
        if (this->actor.params == ENOSSAN_PART_TIME_WORKER) {
            Math_SmoothStepToS(&this->headRotPartTimeWorker.y, 8000, 3, 2000, 0);
        }
    }
}

void EnOssan_BeginInteraction(EnOssan* this, GlobalContext* globalCtx) {
    AnimationInfoS* animations = sAnimations[this->actor.params];
    s16 curFrame = this->skelAnime.curFrame;
    s16 frameCount = Animation_GetLastFrame(animations[this->animationIndex].animation);

    if (this->animationIndex == FSN_ANIMATION_TURN_AROUND_REVERSE) {
        frameCount = 0;
    }
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENOSSAN_CUTSCENESTATE_PLAYING;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (this->actor.params == ENOSSAN_CURIOSITY_SHOP_MAN) {
        if (curFrame == frameCount) {
            switch (this->animationIndex) {
                case FSN_ANIMATION_SCRATCH_BACK:
                    this->animationIndex = FSN_ANIMATION_TURN_AROUND_FORWARD;
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, FSN_ANIMATION_TURN_AROUND_FORWARD);
                    break;
                case FSN_ANIMATION_TURN_AROUND_FORWARD:
                    EnOssan_SetHaveMet(this);
                    this->textId = EnOssan_CuriosityShopMan_GetWelcome(this, globalCtx);
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, this->animationIndex);
                    break;
                case FSN_ANIMATION_HANDS_ON_COUNTER_START:
                case FSN_ANIMATION_HAND_ON_FACE_START:
                case FSN_ANIMATION_LEAN_FORWARD_START:
                case FSN_ANIMATION_SLAM_COUNTER_START:
                    this->animationIndex++;
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, this->animationIndex);
                    Message_StartTextbox(globalCtx, this->textId, &this->actor);
                    EnOssan_SetupStartShopping(globalCtx, this, false);
                    break;
                case FSN_ANIMATION_HANDS_ON_COUNTER_LOOP:
                case FSN_ANIMATION_HAND_ON_FACE_LOOP:
                case FSN_ANIMATION_LEAN_FORWARD_LOOP:
                case FSN_ANIMATION_SLAM_COUNTER_LOOP:
                    this->animationIndex = FSN_ANIMATION_TURN_AROUND_REVERSE;
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, FSN_ANIMATION_TURN_AROUND_REVERSE);
                    break;
                case FSN_ANIMATION_TURN_AROUND_REVERSE:
                    this->animationIndex = FSN_ANIMATION_SCRATCH_BACK;
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, FSN_ANIMATION_SCRATCH_BACK);
                    EnOssan_SetupAction(this, EnOssan_Idle);
                    break;
                default:
                    this->animationIndex = FSN_ANIMATION_SCRATCH_BACK;
                    SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, FSN_ANIMATION_SCRATCH_BACK);
                    EnOssan_SetupAction(this, EnOssan_Idle);
                    break;
            }
        }
    } else {
        EnOssan_SetHaveMet(this);
        this->textId = EnOssan_PartTimerWorker_GetWelcome(this, globalCtx);
        Message_StartTextbox(globalCtx, this->textId, &this->actor);
        EnOssan_SetupStartShopping(globalCtx, this, false);
    }
}

void EnOssan_UpdateJoystickInputState(GlobalContext* globalCtx, EnOssan* this) {
    s8 stickX = CONTROLLER1(globalCtx)->rel.stick_x;
    s8 stickY = CONTROLLER1(globalCtx)->rel.stick_y;

    this->moveHorizontal = this->moveVertical = false;

    if (this->stickAccumX == 0) {
        if (stickX > 30 || stickX < -30) {
            this->stickAccumX = stickX;
            this->moveHorizontal = true;
        }
    } else if (stickX <= 30 && stickX >= -30) {
        this->stickAccumX = 0;
    } else if ((this->stickAccumX * stickX) < 0) { // Stick has swapped directions
        this->stickAccumX = stickX;
        this->moveHorizontal = true;
    } else {
        this->stickAccumX += stickX;
        if (this->stickAccumX > 2000) {
            this->stickAccumX = 2000;
        } else if (this->stickAccumX < -2000) {
            this->stickAccumX = -2000;
        }
    }
    if (this->stickAccumY == 0) {
        if (stickY > 30 || stickY < -30) {
            this->stickAccumY = stickY;
            this->moveVertical = true;
        }
    } else if (stickY <= 30 && stickY >= -30) {
        this->stickAccumY = 0;
    } else if ((this->stickAccumY * stickY) < 0) { // Stick has swapped directions
        this->stickAccumY = stickY;
        this->moveVertical = true;
    } else {
        this->stickAccumY += stickY;
        if (this->stickAccumY > 2000) {
            this->stickAccumY = 2000;
        } else if (this->stickAccumY < -2000) {
            this->stickAccumY = -2000;
        }
    }
}

u8 EnOssan_SetCursorIndexFromNeutral(EnOssan* this, u8 shelfOffset) {
    u8 i;

    // if cursor is on the top shelf
    if (this->cursorIdx & 1) {
        // scan top shelf
        for (i = shelfOffset + 1; i < shelfOffset + 4; i += 2) {
            if (this->items[i] != NULL) {
                return i;
            }
        }
        // scan bottom shelf
        for (i = shelfOffset; i < shelfOffset + 4; i += 2) {
            if (this->items[i] != NULL) {
                return i;
            }
        }
    } else {
        // scan bottom shelf
        for (i = shelfOffset; i < shelfOffset + 4; i += 2) {
            if (this->items[i] != NULL) {
                return i;
            }
        }
        // scan top shelf
        for (i = shelfOffset + 1; i < shelfOffset + 4; i += 2) {
            if (this->items[i] != NULL) {
                return i;
            }
        }
    }
    return CURSOR_INVALID;
}

u8 EnOssan_CursorRight(EnOssan* this, u8 cursorIdx, u8 shelfSlotMin) {
    u8 end = shelfSlotMin + 4;

    while (cursorIdx >= shelfSlotMin && cursorIdx < end) {
        cursorIdx -= 2;
        if (cursorIdx >= shelfSlotMin && cursorIdx < end) {
            if (this->items[cursorIdx] != NULL) {
                return cursorIdx;
            }
        }
    }
    return CURSOR_INVALID;
}

u8 EnOssan_CursorLeft(EnOssan* this, u8 cursorIdx, u8 shelfSlotMax) {
    while (cursorIdx < shelfSlotMax) {
        cursorIdx += 2;
        if (cursorIdx < shelfSlotMax) {
            if (this->items[cursorIdx] != NULL) {
                return cursorIdx;
            }
        }
    }
    return CURSOR_INVALID;
}

void EnOssan_Hello(EnOssan* this, GlobalContext* globalCtx) {
    AnimationInfoS* animations = sAnimations[this->actor.params];
    u8 talkState = Message_GetState(&globalCtx->msgCtx);
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    EnOssan_RotateHead(this, globalCtx);
    if (talkState == 5 && Message_ShouldAdvance(globalCtx)) {
        if ((this->animationIndex == ANI_ANIMATION_APOLOGY_LOOP) && (this->actor.params == ENOSSAN_PART_TIME_WORKER)) {
            this->animationIndex = ANI_ANIMATION_STANDING_NORMAL_LOOP_2;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, 1);
        }
        this->flags &= ~LOOKED_AT_PLAYER;
        if (player->transformation == PLAYER_FORM_DEKU) {
            EnOssan_EndInteraction(globalCtx, this);
        } else if (this->flags & END_INTERACTION) {
            this->flags &= ~END_INTERACTION;
            EnOssan_EndInteraction(globalCtx, this);
        } else if (!EnOssan_TestEndInteraction(this, globalCtx, CONTROLLER1(globalCtx))) {
            EnOssan_StartShopping(globalCtx, this);
        } else {
            return;
        }
    }
    if ((talkState == 10) && (this->actor.params == ENOSSAN_PART_TIME_WORKER) &&
        (player->transformation == PLAYER_FORM_ZORA) && Message_ShouldAdvance(globalCtx)) {
        this->animationIndex = ANI_ANIMATION_APOLOGY_LOOP;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, ANI_ANIMATION_APOLOGY_LOOP);
    }
    if ((this->animationIndex == FSN_ANIMATION_SLAM_COUNTER_LOOP) && Animation_OnFrame(&this->skelAnime, 18.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_HANKO);
    }
}

s32 EnOssan_FacingShopkeeperDialogResult(EnOssan* this, GlobalContext* globalCtx) {
    AnimationInfoS* animations = sAnimations[this->actor.params];
    Player* player = GET_PLAYER(globalCtx);

    switch (globalCtx->msgCtx.choiceIndex) {
        case 0:
            func_8019F208();
            if ((this->actor.params == ENOSSAN_PART_TIME_WORKER) && (player->transformation == PLAYER_FORM_ZORA)) {
                this->animationIndex = ANI_ANIMATION_APOLOGY_LOOP;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, 9);
            }
            EnOssan_SetupAction(this, EnOssan_TalkToShopkeeper);
            func_80151938(globalCtx, sTalkOptionTextIds[this->actor.params]);
            func_8011552C(globalCtx, 6);
            this->stickLeftPrompt.isEnabled = false;
            this->stickRightPrompt.isEnabled = false;
            return true;
        case 1:
            func_8019F230();
            EnOssan_EndInteraction(globalCtx, this);
            return true;
    }
    return false;
}

void EnOssan_FaceShopkeeper(EnOssan* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);
    u8 cursorIdx;

    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToShopkeeperCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_WAITING;
    } else {
        if (talkState == 4) {
            func_8011552C(globalCtx, 6);
            if (!EnOssan_TestEndInteraction(this, globalCtx, CONTROLLER1(globalCtx)) &&
                (!Message_ShouldAdvance(globalCtx) || !EnOssan_FacingShopkeeperDialogResult(this, globalCtx))) {
                if (this->stickAccumX < 0) {
                    cursorIdx = EnOssan_SetCursorIndexFromNeutral(this, 4);
                    if (cursorIdx != CURSOR_INVALID) {
                        this->cursorIdx = cursorIdx;
                        EnOssan_SetupAction(this, EnOssan_LookToLeftShelf);
                        func_8011552C(globalCtx, 6);
                        this->stickLeftPrompt.isEnabled = false;
                        play_sound(NA_SE_SY_CURSOR);
                    }
                } else if (this->stickAccumX > 0) {
                    cursorIdx = EnOssan_SetCursorIndexFromNeutral(this, 0);
                    if (cursorIdx != CURSOR_INVALID) {
                        this->cursorIdx = cursorIdx;
                        EnOssan_SetupAction(this, EnOssan_LookToRightShelf);
                        func_8011552C(globalCtx, 6);
                        this->stickRightPrompt.isEnabled = false;
                        play_sound(NA_SE_SY_CURSOR);
                    }
                }
            } else {
                return;
            }
        }
        if (this->actor.params == ENOSSAN_PART_TIME_WORKER && player->transformation != PLAYER_FORM_ZORA) {
            Math_SmoothStepToS(&this->headRotPartTimeWorker.y, 8000, 3, 2000, 0);
        }
    }
}

void EnOssan_TalkToShopkeeper(EnOssan* this, GlobalContext* globalCtx) {
    AnimationInfoS* animations = sAnimations[this->actor.params];

    if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx)) {
        if ((this->animationIndex == ANI_ANIMATION_APOLOGY_LOOP) && (this->actor.params == ENOSSAN_PART_TIME_WORKER)) {
            this->animationIndex = ANI_ANIMATION_STANDING_NORMAL_LOOP_2;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, animations, 1);
        }
        EnOssan_StartShopping(globalCtx, this);
    }
}

void EnOssan_LookToLeftShelf(EnOssan* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_PLAYING) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_STOPPED;
    }
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToLeftShelfCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_WAITING;
    } else {
        if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_WAITING) {
            if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
                ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
                this->cutsceneState = ENOSSAN_CUTSCENESTATE_PLAYING;
                EnOssan_UpdateCursorPos(globalCtx, this);
                EnOssan_SetupAction(this, EnOssan_BrowseLeftShelf);
                func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
            } else {
                ActorCutscene_SetIntentToPlay(this->cutscene);
            }
        }
        this->stickAccumX = 0;
    }
}

void EnOssan_LookToRightShelf(EnOssan* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_PLAYING) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_STOPPED;
    }
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToRightShelfCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_WAITING;
    } else {
        if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_WAITING) {
            if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
                ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
                this->cutsceneState = ENOSSAN_CUTSCENESTATE_PLAYING;
                EnOssan_UpdateCursorPos(globalCtx, this);
                EnOssan_SetupAction(this, EnOssan_BrowseRightShelf);
                func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
            } else {
                ActorCutscene_SetIntentToPlay(this->cutscene);
            }
        }
        this->stickAccumX = 0;
    }
}

void EnOssan_CursorUpDown(EnOssan* this) {
    u8 curTemp = this->cursorIdx;
    u8 curScanTemp;

    if (this->stickAccumY < 0) {
        curTemp &= (u8)~1;
        if (this->items[curTemp] != NULL) {
            this->cursorIdx = curTemp;
            return;
        }
        // cursorIdx on right shelf
        if (curTemp < 4) {
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 4) {
                curScanTemp = 0;
            }
            while (curScanTemp != curTemp) {
                if (this->items[curScanTemp] != NULL) {
                    this->cursorIdx = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 4) {
                    curScanTemp = 0;
                }
            }
        } else {
            // cursorIdx on left shelf
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 8) {
                curScanTemp = 4;
            }
            while (curScanTemp != curTemp) {
                if (this->items[curScanTemp] != NULL) {
                    this->cursorIdx = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 8) {
                    curScanTemp = 4;
                }
            }
        }
    } else if (this->stickAccumY > 0) {
        curTemp |= 1;
        if (this->items[curTemp] != NULL) {
            this->cursorIdx = curTemp;
            return;
        }
        // cursorIdx on right shelf
        if (curTemp < 4) {
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 4) {
                curScanTemp = 1;
            }
            while (curScanTemp != curTemp) {
                if (this->items[curScanTemp] != NULL) {
                    this->cursorIdx = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 4) {
                    curScanTemp = 1;
                }
            }
        } else {
            // cursorIdx on left shelf
            curScanTemp = curTemp + 2;
            if (curScanTemp >= 8) {
                curScanTemp = 5;
            }
            while (curScanTemp != curTemp) {
                if (this->items[curScanTemp] != NULL) {
                    this->cursorIdx = curScanTemp;
                    return;
                }
                curScanTemp += 2;
                if (curScanTemp >= 8) {
                    curScanTemp = 5;
                }
            }
        }
    }
}

s32 EnOssan_HasPlayerSelectedItem(GlobalContext* globalCtx, EnOssan* this, Input* input) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (EnOssan_TestEndInteraction(this, globalCtx, input)) {
        return true;
    }
    if (EnOssan_TestItemSelected(globalCtx)) {
        if (!item->isOutOfStock) {
            this->tmpActionFunc = this->actionFunc;
            func_80151938(globalCtx, this->items[this->cursorIdx]->choiceTextId);
            this->stickLeftPrompt.isEnabled = false;
            this->stickRightPrompt.isEnabled = false;
            play_sound(NA_SE_SY_DECIDE);
            this->drawCursor = 0;
            EnOssan_SetupAction(this, EnOssan_SelectItem);
        } else {
            play_sound(NA_SE_SY_ERROR);
        }
        return true;
    }
    return false;
}

void EnOssan_BrowseLeftShelf(EnOssan* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);
    s32 pad;
    u8 prevCursorIndex = this->cursorIdx;
    u8 cursorIdx;

    if (!EnOssan_ReturnItemToShelf(this)) {
        this->delayTimer = 3;
    } else if (this->delayTimer != 0) {
        this->delayTimer--;
    } else {
        this->drawCursor = 0xFF;
        this->stickRightPrompt.isEnabled = true;
        EnOssan_UpdateCursorPos(globalCtx, this);
        if (talkState == 5) {
            func_8011552C(globalCtx, 6);
            if (!EnOssan_HasPlayerSelectedItem(globalCtx, this, CONTROLLER1(globalCtx))) {
                if (this->moveHorizontal) {
                    if (this->stickAccumX > 0) {
                        cursorIdx = EnOssan_CursorRight(this, this->cursorIdx, 4);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        } else {
                            EnOssan_SetupLookToShopkeeperFromShelf(globalCtx, this);
                            return;
                        }
                    } else if (this->stickAccumX < 0) {
                        cursorIdx = EnOssan_CursorLeft(this, this->cursorIdx, 8);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        }
                    }
                } else {
                    if (this->stickAccumX > 0 && this->stickAccumX > 500) {
                        cursorIdx = EnOssan_CursorRight(this, this->cursorIdx, 4);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        } else {
                            EnOssan_SetupLookToShopkeeperFromShelf(globalCtx, this);
                            return;
                        }
                    } else if (this->stickAccumX < 0 && this->stickAccumX < -500) {
                        cursorIdx = EnOssan_CursorLeft(this, this->cursorIdx, 8);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        }
                    }
                }
                EnOssan_CursorUpDown(this);
                if (this->cursorIdx != prevCursorIndex) {
                    func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
                    play_sound(NA_SE_SY_CURSOR);
                }
            }
        }
    }
}

void EnOssan_BrowseRightShelf(EnOssan* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);
    s32 pad;
    u8 prevCursorIndex = this->cursorIdx;
    u8 cursorIdx;

    if (!EnOssan_ReturnItemToShelf(this)) {
        this->delayTimer = 3;
    } else if (this->delayTimer != 0) {
        this->delayTimer--;
    } else {
        this->drawCursor = 0xFF;
        this->stickLeftPrompt.isEnabled = true;
        EnOssan_UpdateCursorPos(globalCtx, this);
        if (talkState == 5) {
            func_8011552C(globalCtx, 6);
            if (!EnOssan_HasPlayerSelectedItem(globalCtx, this, CONTROLLER1(globalCtx))) {
                if (this->moveHorizontal != 0) {
                    if (this->stickAccumX < 0) {
                        cursorIdx = EnOssan_CursorRight(this, this->cursorIdx, 0);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        } else {
                            EnOssan_SetupLookToShopkeeperFromShelf(globalCtx, this);
                            return;
                        }
                    } else if (this->stickAccumX > 0) {
                        cursorIdx = EnOssan_CursorLeft(this, this->cursorIdx, 4);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        }
                    }
                } else {
                    if (this->stickAccumX < 0 && this->stickAccumX < -500) {
                        cursorIdx = EnOssan_CursorRight(this, this->cursorIdx, 0);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        } else {
                            EnOssan_SetupLookToShopkeeperFromShelf(globalCtx, this);
                            return;
                        }
                    } else if (this->stickAccumX > 0 && this->stickAccumX > 500) {
                        cursorIdx = EnOssan_CursorLeft(this, this->cursorIdx, 4);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                        }
                    }
                }
                EnOssan_CursorUpDown(this);
                if (this->cursorIdx != prevCursorIndex) {
                    func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
                    play_sound(NA_SE_SY_CURSOR);
                }
            }
        }
    }
}

void EnOssan_LookToShopkeeperFromShelf(EnOssan* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_PLAYING) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_STOPPED;
    }
    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToShopKeeperFromShelfCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_WAITING;
    } else if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENOSSAN_CUTSCENESTATE_PLAYING;
            EnOssan_UpdateCursorPos(globalCtx, this);
            EnOssan_StartShopping(globalCtx, this);
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void EnOssan_SetupBuyItemWithFanfare(GlobalContext* globalCtx, EnOssan* this) {
    Player* player = GET_PLAYER(globalCtx);

    Actor_PickUp(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    globalCtx->msgCtx.msgMode = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    player->stateFlags2 &= ~0x20000000;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    EnOssan_SetupAction(this, EnOssan_BuyItemWithFanfare);
}

void EnOssan_SetupCannotBuy(GlobalContext* globalCtx, EnOssan* this, u16 textId) {
    func_80151938(globalCtx, textId);
    EnOssan_SetupAction(this, EnOssan_CannotBuy);
}

void EnOssan_SetupBuy(GlobalContext* globalCtx, EnOssan* this, u16 textId) {
    func_80151938(globalCtx, textId);
    EnOssan_SetupAction(this, EnOssan_CanBuy);
}

void EnOssan_HandleCanBuyItem(GlobalContext* globalCtx, EnOssan* this) {
    EnGirlA* item = this->items[this->cursorIdx];

    switch (item->canBuyFunc(globalCtx, item)) {
        case CANBUY_RESULT_SUCCESS_1:
            if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_PLAYING) {
                ActorCutscene_Stop(this->cutscene);
                this->cutsceneState = ENOSSAN_CUTSCENESTATE_STOPPED;
            }
            func_8019F208();
            item->buyFanfareFunc(globalCtx, item);
            EnOssan_SetupBuyItemWithFanfare(globalCtx, this);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_SUCCESS_2:
            func_8019F208();
            item->buyFunc(globalCtx, item);
            EnOssan_SetupBuy(globalCtx, this, sBuySuccessTextIds[this->actor.params]);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_NO_ROOM:
        case CANBUY_RESULT_NO_ROOM_2:
            play_sound(NA_SE_SY_ERROR);
            EnOssan_SetupCannotBuy(globalCtx, this, sNoRoomTextIds[this->actor.params]);
            break;
        case CANBUY_RESULT_NEED_EMPTY_BOTTLE:
            play_sound(NA_SE_SY_ERROR);
            EnOssan_SetupCannotBuy(globalCtx, this, sNeedEmptyBottleTextIds[this->actor.params]);
            break;
        case CANBUY_RESULT_NEED_RUPEES:
            play_sound(NA_SE_SY_ERROR);
            EnOssan_SetupCannotBuy(globalCtx, this, sNeedRupeesTextIds[this->actor.params]);
            break;
        case CANBUY_RESULT_CANNOT_GET_NOW_2:
            play_sound(NA_SE_SY_ERROR);
            EnOssan_SetupCannotBuy(globalCtx, this, sCannotGetNowTextIds[this->actor.params]);
            break;
        case CANBUY_RESULT_CANNOT_GET_NOW:
            play_sound(NA_SE_SY_ERROR);
            EnOssan_SetupCannotBuy(globalCtx, this, sNoRoomTextIds[this->actor.params]);
            break;
    }
}

void EnOssan_SelectItem(EnOssan* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);

    if (EnOssan_TakeItemOffShelf(this) && talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (!EnOssan_TestCancelOption(this, globalCtx, CONTROLLER1(globalCtx)) && Message_ShouldAdvance(globalCtx)) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    EnOssan_HandleCanBuyItem(globalCtx, this);
                    break;
                case 1:
                    func_8019F230();
                    this->actionFunc = this->tmpActionFunc;
                    func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
                    break;
            }
        }
    }
}

void EnOssan_CannotBuy(EnOssan* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
    }
}

void EnOssan_CanBuy(EnOssan* this, GlobalContext* globalCtx) {
    EnGirlA* item;

    if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx)) {
        this->shopItemSelectedTween = 0.0f;
        EnOssan_ResetItemPosition(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
    }
}

void EnOssan_BuyItemWithFanfare(EnOssan* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        EnOssan_SetupAction(this, EnOssan_SetupItemPurchased);
    } else {
        Actor_PickUp(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    }
}

void EnOssan_SetupItemPurchased(EnOssan* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 6 && Message_ShouldAdvance(globalCtx)) {
        globalCtx->msgCtx.msgMode = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        EnOssan_SetupAction(this, EnOssan_ItemPurchased);
        if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_STOPPED) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookToShopkeeperCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, EXCH_ITEM_MINUS1);
    }
}

void EnOssan_ContinueShopping(EnOssan* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);
    Player* player = GET_PLAYER(globalCtx);
    EnGirlA* item;

    if (talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (Message_ShouldAdvance(globalCtx)) {
            EnOssan_ResetItemPosition(this);
            item = this->items[this->cursorIdx];
            item->restockFunc(globalCtx, item);
            if (!EnOssan_TestEndInteraction(this, globalCtx, CONTROLLER1(globalCtx))) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        player->actor.shape.rot.y = BINANG_ROT180(player->actor.shape.rot.y);
                        player->stateFlags2 |= 0x20000000;
                        Message_StartTextbox(globalCtx, this->textId, &this->actor);
                        EnOssan_SetupStartShopping(globalCtx, this, true);
                        func_800B85E0(&this->actor, globalCtx, 100.0f, EXCH_ITEM_MINUS1);
                        break;
                    case 1:
                    default:
                        func_8019F230();
                        EnOssan_EndInteraction(globalCtx, this);
                        break;
                }
            }
        }
    } else if (talkState == 5 && Message_ShouldAdvance(globalCtx)) {
        EnOssan_ResetItemPosition(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        player->actor.shape.rot.y = BINANG_ROT180(player->actor.shape.rot.y);
        player->stateFlags2 |= 0x20000000;
        Message_StartTextbox(globalCtx, this->textId, &this->actor);
        EnOssan_SetupStartShopping(globalCtx, this, true);
        func_800B85E0(&this->actor, globalCtx, 100.0f, EXCH_ITEM_MINUS1);
    }
}

void EnOssan_ItemPurchased(EnOssan* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->cutsceneState == ENOSSAN_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            player->stateFlags2 |= 0x20000000;
            EnOssan_SetupAction(this, EnOssan_ContinueShopping);
            this->cutsceneState = ENOSSAN_CUTSCENESTATE_PLAYING;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookToShopkeeperCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80151938(globalCtx, 0x642);
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, EXCH_ITEM_MINUS1);
    }
}

void EnOssan_PositionSelectedItem(EnOssan* this) {
    static Vec3f sSelectedItemPosition[] = {
        { 35.0f, 68.0f, -130.0f },
        { -35.0f, 68.0f, -130.0f },
    };
    EnGirlA* item;
    u8 i = this->cursorIdx;
    u8 i2;
    ShopItem* shopItem = &sShops[this->actor.params][i];
    Vec3f worldPos;

    item = this->items[i];
    i2 = i >> 2;
    VEC3F_LERPIMPDST(&worldPos, &shopItem->spawnPos, &sSelectedItemPosition[i2], this->shopItemSelectedTween);

    item->actor.world.pos.x = worldPos.x;
    item->actor.world.pos.y = worldPos.y;
    item->actor.world.pos.z = worldPos.z;
}

void EnOssan_ResetItemPosition(EnOssan* this) {
    this->shopItemSelectedTween = 0.0f;
    EnOssan_PositionSelectedItem(this);
}

/*
 * Returns true if animation has completed
 */
s32 EnOssan_TakeItemOffShelf(EnOssan* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 1.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween >= 0.85f) {
        this->shopItemSelectedTween = 1.0f;
    }
    EnOssan_PositionSelectedItem(this);
    if (this->shopItemSelectedTween == 1.0f) {
        return true;
    }
    return false;
}

/*
 * Returns true if animation has completed
 */
s32 EnOssan_ReturnItemToShelf(EnOssan* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 0.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween <= 0.15f) {
        this->shopItemSelectedTween = 0.0f;
    }
    EnOssan_PositionSelectedItem(this);
    if (this->shopItemSelectedTween == 0.0f) {
        return true;
    }
    return false;
}

void EnOssan_UpdateItemSelectedProperty(EnOssan* this) {
    EnGirlA** items = this->items;
    EnGirlA* item;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->items); i++, items++) {
        item = *items;
        if (item != NULL) {
            if (this->actionFunc != EnOssan_SelectItem && this->actionFunc != EnOssan_CannotBuy &&
                this->drawCursor == 0) {
                item->isSelected = false;
            } else {
                item->isSelected = this->cursorIdx == i ? true : false;
            }
        }
    }
}

void EnOssan_UpdateCursorAnim(EnOssan* this) {
    f32 t = this->cursorAnimTween;

    if (this->cursorAnimState == 0) {
        t += 0.05f;
        if (t >= 1.0f) {
            t = 1.0f;
            this->cursorAnimState = 1;
        }
    } else {
        t -= 0.05f;
        if (t <= 0.0f) {
            t = 0.0f;
            this->cursorAnimState = 0;
        }
    }
    this->cursorColor.r = COL_CHAN_MIX(0, 0.0f, t);
    this->cursorColor.g = COL_CHAN_MIX(80, 80.0f, t);
    this->cursorColor.b = COL_CHAN_MIX(255, 0.0f, t);
    this->cursorColor.a = COL_CHAN_MIX(255, 0.0f, t);
    this->cursorAnimTween = t;
}

void EnOssan_UpdateStickDirectionPromptAnim(EnOssan* this) {
    f32 arrowAnimTween = this->arrowAnimTween;
    f32 stickAnimTween = this->stickAnimTween;
    s32 maxColor = 255; // POSSIBLY FAKE

    if (this->arrowAnimState == 0) {
        arrowAnimTween += 0.05f;
        if (arrowAnimTween > 1.0f) {
            arrowAnimTween = 1.0f;
            this->arrowAnimState = 1;
        }
    } else {
        arrowAnimTween -= 0.05f;
        if (arrowAnimTween < 0.0f) {
            arrowAnimTween = 0.0f;
            this->arrowAnimState = 0;
        }
    }
    this->arrowAnimTween = arrowAnimTween;

    if (this->stickAnimState == 0) {
        stickAnimTween += 0.1f;
        if (stickAnimTween > 1.0f) {
            stickAnimTween = 1.0f;
            this->stickAnimState = 1;
        }
    } else {
        stickAnimTween = 0.0f;
        this->stickAnimState = 0;
    }
    this->stickAnimTween = stickAnimTween;

    this->stickLeftPrompt.arrowColor.r = COL_CHAN_MIX(255, 155.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColor.g = COL_CHAN_MIX(maxColor, 155.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColor.b = COL_CHAN_MIX(0, -100.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColor.a = COL_CHAN_MIX(200, 50.0f, arrowAnimTween);

    this->stickRightPrompt.arrowTexX = 290.0f;

    this->stickRightPrompt.arrowColor.r = COL_CHAN_MIX(maxColor, 155.0f, arrowAnimTween);
    this->stickRightPrompt.arrowColor.g = COL_CHAN_MIX(255, 155.0f, arrowAnimTween);
    this->stickRightPrompt.arrowColor.b = COL_CHAN_MIX(0, -100.0f, arrowAnimTween);
    this->stickRightPrompt.arrowColor.a = COL_CHAN_MIX(200, 50.0f, arrowAnimTween);

    this->stickLeftPrompt.arrowTexX = 33.0f;

    this->stickRightPrompt.stickTexX = 274.0f;
    this->stickRightPrompt.stickTexX += 8.0f * stickAnimTween;

    this->stickLeftPrompt.stickTexX = 49.0f;
    this->stickLeftPrompt.stickTexX -= 8.0f * stickAnimTween;

    this->stickRightPrompt.arrowTexY = 91.0f;
    this->stickLeftPrompt.arrowTexY = 91.0f;

    this->stickRightPrompt.stickTexY = 95.0f;
    this->stickLeftPrompt.stickTexY = 95.0f;
}

void EnOssan_WaitForBlink(EnOssan* this) {
    s16 decr = this->blinkTimer - 1;

    if (decr != 0) {
        this->blinkTimer = decr;
    } else {
        this->blinkFunc = EnOssan_Blink;
    }
}

void EnOssan_Blink(EnOssan* this) {
    s16 decr = this->blinkTimer - 1;
    s16 eyeTexIndexTemp;

    if (decr != 0) {
        this->blinkTimer = decr;
        return;
    }
    eyeTexIndexTemp = this->eyeTexIndex + 1;
    if (eyeTexIndexTemp > 2) {
        this->eyeTexIndex = 0;
        this->blinkTimer = (s32)(Rand_ZeroOne() * 60.0f) + 20;
        this->blinkFunc = EnOssan_WaitForBlink;
    } else {
        this->eyeTexIndex = eyeTexIndexTemp;
        this->blinkTimer = 1;
    }
}

void EnOssan_CuriosityShopMan_Init(EnOssan* this, GlobalContext* globalCtx) {
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gFsnSkel, &gFsnIdleAnim, this->jointTable, this->morphTable,
                       ENOSSAN_LIMB_MAX);
    this->actor.draw = EnOssan_CuriosityShopMan_Draw;
}

void EnOssan_PartTimeWorker_Init(EnOssan* this, GlobalContext* globalCtx) {
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gAniSkeleton, &gAniStandingNormalAnim, this->jointTable,
                       this->morphTable, 16);
    this->actor.draw = EnOssan_PartTimeWorker_Draw;
}

u16 EnOssan_CuriosityShopMan_GetWelcome(EnOssan* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 textId = Text_GetFaceReaction(globalCtx, 0x2F);

    if (textId != 0) {
        this->animationIndex = FSN_ANIMATION_HANDS_ON_COUNTER_START;
        this->flags |= END_INTERACTION;
        return textId;
    }
    switch (player->transformation) {
        case PLAYER_FORM_DEKU:
            this->animationIndex = FSN_ANIMATION_SLAM_COUNTER_START;
            if (gSaveContext.save.weekEventReg[18] & 0x10) {
                return sWelcomeDekuTextIds[ENOSSAN_CURIOSITY_SHOP_MAN];
            }
            return sWelcomeDekuFirstTimeTextIds[ENOSSAN_CURIOSITY_SHOP_MAN];
        case PLAYER_FORM_ZORA:
            this->animationIndex = FSN_ANIMATION_LEAN_FORWARD_START;
            if (gSaveContext.save.weekEventReg[18] & 8) {
                return sWelcomeZoraTextIds[ENOSSAN_CURIOSITY_SHOP_MAN];
            }
            return sWelcomeZoraFirstTimeTextIds[ENOSSAN_CURIOSITY_SHOP_MAN];
        case PLAYER_FORM_GORON:
            this->animationIndex = FSN_ANIMATION_HAND_ON_FACE_START;
            if (gSaveContext.save.weekEventReg[18] & 4) {
                return sWelcomeGoronTextIds[ENOSSAN_CURIOSITY_SHOP_MAN];
            }
            return sWelcomeGoronFirstTimeTextIds[ENOSSAN_CURIOSITY_SHOP_MAN];
    }
    this->animationIndex = FSN_ANIMATION_HANDS_ON_COUNTER_START;
    return sWelcomeHumanTextIds[ENOSSAN_CURIOSITY_SHOP_MAN];
}

u16 EnOssan_PartTimerWorker_GetWelcome(EnOssan* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 textId = Text_GetFaceReaction(globalCtx, 0x36);

    if (textId != 0) {
        this->flags |= END_INTERACTION;
        return textId;
    }
    switch (player->transformation) {
        case PLAYER_FORM_DEKU:
            if (gSaveContext.save.weekEventReg[55] & 0x10) {
                return sWelcomeDekuTextIds[ENOSSAN_PART_TIME_WORKER];
            }
            return sWelcomeDekuFirstTimeTextIds[ENOSSAN_PART_TIME_WORKER];
        case PLAYER_FORM_ZORA:
            if (gSaveContext.save.weekEventReg[55] & 8) {
                return sWelcomeZoraTextIds[ENOSSAN_PART_TIME_WORKER];
            }
            return sWelcomeZoraFirstTimeTextIds[ENOSSAN_PART_TIME_WORKER];
        case PLAYER_FORM_GORON:
            if (gSaveContext.save.weekEventReg[55] & 4) {
                return sWelcomeGoronTextIds[ENOSSAN_PART_TIME_WORKER];
            }
            return sWelcomeGoronFirstTimeTextIds[ENOSSAN_PART_TIME_WORKER];
    }
    return sWelcomeHumanTextIds[ENOSSAN_PART_TIME_WORKER];
}

void EnOssan_SetHaveMet(EnOssan* this) {
    switch (this->textId) {
        case 0x06A9:
            gSaveContext.save.weekEventReg[18] |= 0x10;
            break;
        case 0x06C6:
            gSaveContext.save.weekEventReg[55] |= 0x10;
            break;
        case 0x06A7:
            gSaveContext.save.weekEventReg[18] |= 8;
            break;
        case 0x06C4:
            gSaveContext.save.weekEventReg[55] |= 8;
            break;
        case 0x06A5:
            gSaveContext.save.weekEventReg[18] |= 4;
            break;
        case 0x06C2:
            gSaveContext.save.weekEventReg[55] |= 4;
            break;
    }
}

void EnOssan_InitShop(EnOssan* this, GlobalContext* globalCtx) {
    static EnOssanActionFunc sInitFuncs[] = { EnOssan_CuriosityShopMan_Init, EnOssan_PartTimeWorker_Init };
    ShopItem* shopItems;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex)) {
        this->actor.flags &= ~ACTOR_FLAG_10;
        this->actor.objBankIndex = this->objIndex;
        Actor_SetObjectDependency(globalCtx, &this->actor);
        shopItems = sShops[this->actor.params];
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
        sInitFuncs[this->actor.params](this, globalCtx);
        this->textId = sWelcomeHumanTextIds[this->actor.params];
        EnOssan_GetCutscenes(this, globalCtx);

        this->cursorPos.y = this->cursorPos.x = 100.0f;
        this->cutsceneState = ENOSSAN_CUTSCENESTATE_STOPPED;
        this->cutscene = this->lookToShopkeeperCutscene;
        this->actor.colChkInfo.mass = MASS_IMMOVABLE;
        this->actor.colChkInfo.cylRadius = 50;
        this->stickAccumX = this->stickAccumY = 0;

        this->cursorIdx = 0;
        this->cursorPos.z = 1.5f;
        this->cursorColor.r = 0;
        this->cursorColor.g = 80;
        this->cursorColor.b = 255;
        this->cursorColor.a = 255;
        this->cursorAnimTween = 0.0f;
        this->cursorAnimState = 0;
        this->drawCursor = 0;

        this->stickLeftPrompt.stickColor.r = 200;
        this->stickLeftPrompt.stickColor.g = 200;
        this->stickLeftPrompt.stickColor.b = 200;
        this->stickLeftPrompt.stickColor.a = 180;
        this->stickLeftPrompt.stickTexX = 49.0f;
        this->stickLeftPrompt.stickTexY = 95.0f;
        this->stickLeftPrompt.arrowColor.r = 255;
        this->stickLeftPrompt.arrowColor.g = 255;
        this->stickLeftPrompt.arrowColor.b = 0;
        this->stickLeftPrompt.arrowColor.a = 200;
        this->stickLeftPrompt.arrowTexX = 33.0f;
        this->stickLeftPrompt.arrowTexY = 91.0f;
        this->stickLeftPrompt.texZ = 1.0f;
        this->stickLeftPrompt.isEnabled = false;

        this->stickRightPrompt.stickColor.r = 200;
        this->stickRightPrompt.stickColor.g = 200;
        this->stickRightPrompt.stickColor.b = 200;
        this->stickRightPrompt.stickColor.a = 180;
        this->stickRightPrompt.stickTexX = 274.0f;
        this->stickRightPrompt.stickTexY = 95.0f;
        this->stickRightPrompt.arrowColor.r = 255;
        this->stickRightPrompt.arrowColor.g = 255;
        this->stickRightPrompt.arrowColor.b = 0;
        this->stickRightPrompt.arrowColor.a = 200;
        this->stickRightPrompt.arrowTexX = 290.0f;
        this->stickRightPrompt.arrowTexY = 91.0f;
        this->stickRightPrompt.texZ = 1.0f;
        this->stickRightPrompt.isEnabled = false;

        this->arrowAnimState = 0;
        this->stickAnimState = 0;
        this->arrowAnimTween = 0.0f;
        this->stickAnimTween = 0.0f;
        this->shopItemSelectedTween = 0.0f;

        Actor_SetScale(&this->actor, sActorScales[this->actor.params]);
        this->animationIndex = 1; // FSN_ANIMATION_SCRATCH_BACK and ANI_ANIMATION_STANDING_NORMAL_LOOP_2
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimations[this->actor.params], 1);
        EnOssan_SpawnShopItems(this, globalCtx, shopItems);
        this->blinkTimer = 20;
        this->eyeTexIndex = 0;
        this->blinkFunc = EnOssan_WaitForBlink;
        this->actor.flags &= ~ACTOR_FLAG_1;
        EnOssan_SetupAction(this, EnOssan_Idle);
    }
}

void EnOssan_GetCutscenes(EnOssan* this, GlobalContext* globalCtx) {
    this->lookToShopkeeperCutscene = this->actor.cutscene;
    this->lookToLeftShelfCutscene = ActorCutscene_GetAdditionalCutscene(this->lookToShopkeeperCutscene);
    this->lookToRightShelfCutscene = ActorCutscene_GetAdditionalCutscene(this->lookToLeftShelfCutscene);
    this->lookToShopKeeperFromShelfCutscene = ActorCutscene_GetAdditionalCutscene(this->lookToRightShelfCutscene);
}

void EnOssan_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnOssan* this = THIS;

    if (this->actionFunc != EnOssan_InitShop) {
        this->blinkFunc(this);
        EnOssan_UpdateJoystickInputState(globalCtx, this);
        EnOssan_UpdateItemSelectedProperty(this);
        EnOssan_UpdateStickDirectionPromptAnim(this);
        EnOssan_UpdateCursorAnim(this);
        func_800E9250(globalCtx, &this->actor, &this->headRot, &this->unk2CC, this->actor.focus.pos);
        this->actionFunc(this, globalCtx);
        Actor_SetFocus(&this->actor, 90.0f);
        SkelAnime_Update(&this->skelAnime);
    } else {
        this->actionFunc(this, globalCtx);
    }
}

void EnOssan_DrawCursor(GlobalContext* globalCtx, EnOssan* this, f32 x, f32 y, f32 z, u8 drawCursor) {
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;
    f32 w;
    s32 dsdx;

    (void)"../z_en_oB1.c";

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (drawCursor != 0) {
        func_8012C654(globalCtx->state.gfxCtx);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, this->cursorColor.r, this->cursorColor.g, this->cursorColor.b,
                        this->cursorColor.a);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, gSelectionCursorTex, G_IM_FMT_IA, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
        w = 16.0f * z;
        ulx = (x - w) * 4.0f;
        uly = (y - w) * 4.0f;
        lrx = (x + w) * 4.0f;
        lry = (y + w) * 4.0f;
        dsdx = (1.0f / z) * 1024.0f;
        gSPTextureRectangle(OVERLAY_DISP++, ulx, uly, lrx, lry, G_TX_RENDERTILE, 0, 0, dsdx, dsdx);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnOssan_DrawTextRec(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t,
                         f32 dx, f32 dy) {
    f32 unk;
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;
    f32 w;
    f32 h;
    s32 dsdx;
    s32 dtdy;

    (void)"../z_en_oB1.c";

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gDPPipeSync(OVERLAY_DISP++);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, r, g, b, a);

    w = 8.0f * z;
    ulx = (x - w) * 4.0f;
    lrx = (x + w) * 4.0f;

    h = 12.0f * z;
    uly = (y - h) * 4.0f;
    lry = (y + h) * 4.0f;

    unk = 1024 * (1.0f / z);
    dsdx = unk * dx;
    dtdy = dy * unk;

    gSPTextureRectangle(OVERLAY_DISP++, ulx, uly, lrx, lry, G_TX_RENDERTILE, s, t, dsdx, dtdy);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnOssan_DrawStickDirectionPrompts(GlobalContext* globalCtx, EnOssan* this) {
    s32 drawStickRightPrompt = this->stickLeftPrompt.isEnabled;
    s32 drawStickLeftPrompt = this->stickRightPrompt.isEnabled;

    (void)"../z_en_oB1.c";

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (drawStickRightPrompt || drawStickLeftPrompt) {
        func_8012C654(globalCtx->state.gfxCtx);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPLoadTextureBlock(OVERLAY_DISP++, gArrowCursorTex, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 24, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        if (drawStickRightPrompt) {
            EnOssan_DrawTextRec(globalCtx, this->stickLeftPrompt.arrowColor.r, this->stickLeftPrompt.arrowColor.g,
                                this->stickLeftPrompt.arrowColor.b, this->stickLeftPrompt.arrowColor.a,
                                this->stickLeftPrompt.arrowTexX, this->stickLeftPrompt.arrowTexY,
                                this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            EnOssan_DrawTextRec(globalCtx, this->stickRightPrompt.arrowColor.r, this->stickRightPrompt.arrowColor.g,
                                this->stickRightPrompt.arrowColor.b, this->stickRightPrompt.arrowColor.a,
                                this->stickRightPrompt.arrowTexX, this->stickRightPrompt.arrowTexY,
                                this->stickRightPrompt.texZ, 0, 0, 1.0f, 1.0f);
        }
        gDPLoadTextureBlock(OVERLAY_DISP++, gControlStickTex, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        if (drawStickRightPrompt) {
            EnOssan_DrawTextRec(globalCtx, this->stickLeftPrompt.stickColor.r, this->stickLeftPrompt.stickColor.g,
                                this->stickLeftPrompt.stickColor.b, this->stickLeftPrompt.stickColor.a,
                                this->stickLeftPrompt.stickTexX, this->stickLeftPrompt.stickTexY,
                                this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            EnOssan_DrawTextRec(globalCtx, this->stickRightPrompt.stickColor.r, this->stickRightPrompt.stickColor.g,
                                this->stickRightPrompt.stickColor.b, this->stickRightPrompt.stickColor.a,
                                this->stickRightPrompt.stickTexX, this->stickRightPrompt.stickTexY,
                                this->stickRightPrompt.texZ, 0, 0, 1.0f, 1.0f);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 EnOssan_CuriosityShopMan_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos,
                                              Vec3s* rot, Actor* thisx) {
    EnOssan* this = THIS;

    if (limbIndex == FSN_LIMB_HEAD) {
        Matrix_InsertXRotation_s(this->headRot.y, MTXMODE_APPLY);
    }
    return false;
}

s32 EnOssan_PartTimeWorker_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos,
                                            Vec3s* rot, Actor* thisx) {
    EnOssan* this = THIS;

    if (limbIndex == ANI_LIMB_HEAD) {
        Matrix_InsertXRotation_s(this->headRotPartTimeWorker.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->headRotPartTimeWorker.x, MTXMODE_APPLY);
    }
    return false;
}

void EnOssan_CuriosityShopMan_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot,
                                           Actor* thisx) {
    EnOssan* this = THIS;

    if (limbIndex == FSN_LIMB_PELVIS || limbIndex == FSN_LIMB_LEFT_UPPER_ARM || limbIndex == FSN_LIMB_RIGHT_UPPER_ARM) {
        rot->y += (s16)Math_SinS(this->limbRotTableY[limbIndex]) * 200;
        rot->z += (s16)Math_CosS(this->limbRotTableZ[limbIndex]) * 200;
    }
}

void EnOssan_PartTimeWorker_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot,
                                         Actor* thisx) {
    static Vec3f sPartTimeWorkerFocusOffset = { 800.0f, 500.0f, 0.0f };
    EnOssan* this = THIS;

    if (limbIndex == ANI_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&sPartTimeWorkerFocusOffset, &this->actor.focus.pos);
    }
}

void EnOssan_CuriosityShopMan_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr sEyeTextures[] = { gFsnEyeOpenTex, gFsnEyeHalfTex, gFsnEyeClosedTex };
    s32 pad;
    EnOssan* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnOssan_CuriosityShopMan_OverrideLimbDraw, EnOssan_CuriosityShopMan_PostLimbDraw,
                          &this->actor);
    EnOssan_DrawCursor(globalCtx, this, this->cursorPos.x, this->cursorPos.y, this->cursorPos.z, this->drawCursor);
    EnOssan_DrawStickDirectionPrompts(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnOssan_PartTimeWorker_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr sEyeTextures[] = { gAniOpenEyeTex, gAniClosingEyeTex, gAniClosedEyeTex };
    s32 pad;
    EnOssan* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnOssan_PartTimeWorker_OverrideLimbDraw, EnOssan_PartTimeWorker_PostLimbDraw, &this->actor);
    EnOssan_DrawCursor(globalCtx, this, this->cursorPos.x, this->cursorPos.y, this->cursorPos.z, this->drawCursor);
    EnOssan_DrawStickDirectionPrompts(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
