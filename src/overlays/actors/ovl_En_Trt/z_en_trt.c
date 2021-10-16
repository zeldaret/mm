/*
 * File: z_en_trt.c
 * Overlay: ovl_En_Trt
 * Description: Kotake
 */

#include "z_en_trt.h"

#define FLAGS 0x00000009

#define THIS ((EnTrt*)thisx)

#define ENTRT_FULLY_AWAKE (1 << 0)
#define ENTRT_GIVEN_MUSHROOM (1 << 1)
#define ENTRT_MET (1 << 2)

void EnTrt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTrt_GetCutscenes(EnTrt* this, GlobalContext* globalCtx);
s32 EnTrt_ReturnItemToShelf(EnTrt* this);
void EnTrt_ResetItemPosition(EnTrt* this);
s32 EnTrt_FacingShopkeeperDialogResult(EnTrt* this, GlobalContext* globalCtx);
s32 EnTrt_TakeItemOffShelf(EnTrt* this);
void EnTrt_UpdateHeadYawAndPitch(EnTrt* this, GlobalContext* globalCtx);

void EnTrt_BeginInteraction(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_IdleSleeping(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_IdleAwake(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_Hello(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_FaceShopkeeper(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_SetupEndInteraction(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_StartShopping(GlobalContext* globalCtx, EnTrt* this);
void EnTrt_GiveRedPotionForKoume(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_EndConversation(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_TryToGiveRedPotion(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_Surprised(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_LookToShelf(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_GivenRedPotionForKoume(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_TryToGiveRedPotionAfterSurprised(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_BrowseShelf(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_SetupTalkToShopkeeper(GlobalContext* globalCtx, EnTrt* this);
void EnTrt_ContinueShopping(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_ItemGiven(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_SelectItem(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_SetupLookToShopkeeperFromShelf(GlobalContext* globalCtx, EnTrt* this);
void EnTrt_LookToShopkeeperFromShelf(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_PayForMushroom(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_CanBuy(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_CannotBuy(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_BuyItemWithFanfare(EnTrt* this, GlobalContext* globalCtx);
void EnTrt_SetupItemGiven(EnTrt* this, GlobalContext* globalCtx);

void EnTrt_EyesClosed(EnTrt* this);
void EnTrt_OpenThenCloseEyes(EnTrt* this);
void EnTrt_OpenEyesThenSetToBlink(EnTrt* this);
void EnTrt_CloseEyes(EnTrt* this);
void EnTrt_OpenEyes(EnTrt* this);
void EnTrt_Blink(EnTrt* this);
void EnTrt_OpenEyes2(EnTrt* this);
void EnTrt_NodOff(EnTrt* this);

extern UNK_TYPE D_0401F740;
extern UNK_TYPE D_0401F8C0;
extern UNK_TYPE D_0401F7C0;
extern FlexSkeletonHeader D_0600FEF0;
extern AnimationHeader D_0600FD34;
extern AnimationHeader D_0600DE68;
extern AnimationHeader D_06002224;
extern AnimationHeader D_06001EF4;
extern AnimationHeader D_060030EC;
extern AnimationHeader D_0600D52C;
extern AnimationHeader D_06002CB0;
extern AnimationHeader D_0600EE98;
extern AnimationHeader D_06003D78;
extern AnimationHeader D_06000A44;
extern TexturePtr D_0600B0B8;
extern TexturePtr D_0600B8B8;
extern TexturePtr D_0600C0B8;

static ActorAnimationEntryS sAnimations[] = {
    { &D_0600DE68, 1.0f, 0, -1, 2, 0 }, { &D_0600EE98, 1.0f, 0, -1, 2, 0 }, { &D_0600FD34, 1.0f, 0, -1, 0, 0 },
    { &D_060030EC, 1.0f, 0, -1, 2, 0 }, { &D_06003D78, 1.0f, 0, -1, 2, 0 }, { &D_0600D52C, 1.0f, 0, -1, 0, 0 },
    { &D_06000A44, 1.0f, 0, -1, 0, 0 }, { &D_06001EF4, 1.0f, 0, -1, 0, 0 }, { &D_06002224, 1.0f, 0, -1, 0, 0 },
    { &D_06002CB0, 1.0f, 0, -1, 0, 0 },
};

const ActorInit En_Trt_InitVars = {
    ACTOR_EN_TRT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRT,
    sizeof(EnTrt),
    (ActorFunc)EnTrt_Init,
    (ActorFunc)EnTrt_Destroy,
    (ActorFunc)EnTrt_Update,
    (ActorFunc)EnTrt_Draw,
};

static f32 sActorScale = 0.008f;

static ShopItem sShop[] = {
    { SI_POTION_RED_1, { 24, 32, -36 } },
    { SI_POTION_GREEN_1, { 6, 32, -36 } },
    { SI_POTION_BLUE, { -12, 32, -36 } },
};

void EnTrt_ChangeAnim(SkelAnime* skelAnime, ActorAnimationEntryS* animations, s32 idx) {
    f32 frameCount;

    animations += idx;
    if (animations->frameCount < 0) {
        frameCount = Animation_GetLastFrame(&animations->animationSeg->common);
    } else {
        frameCount = animations->frameCount;
    }
    Animation_Change(skelAnime, animations->animationSeg, animations->playbackSpeed, animations->frame, frameCount,
                     animations->mode, animations->transitionRate);
}

s32 EnTrt_TestItemSelected(GlobalContext* globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A);
    }
    return CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
           CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B) ||
           CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_CUP);
}

void EnTrt_SpawnShopItems(EnTrt* this, GlobalContext* globalCtx, ShopItem* shopItem) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->items); i++, shopItem++) {
        if (shopItem->shopItemId < 0) {
            this->items[i] = NULL;
        } else if (shopItem->shopItemId < 0) {
            this->items[i] = NULL;
        } else {
            this->items[i] =
                (EnGirlA*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA, shopItem->spawnPos.x,
                                      shopItem->spawnPos.y, shopItem->spawnPos.z, 0, 0, 0, shopItem->shopItemId);
        }
    }
}

void EnTrt_UpdateCollider(EnTrt* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnTrt_UpdateCursorPos(GlobalContext* globalCtx, EnTrt* this) {
    s16 x;
    s16 y;
    f32 xOffset = 0.0f;
    f32 yOffset = 17.0f;

    func_800B8898(globalCtx, &this->items[this->cursorIdx]->actor, &x, &y);
    this->cursorPos.x = x + xOffset;
    this->cursorPos.y = y + yOffset;
    this->cursorPos.z = 1.2f;
}

void EnTrt_SetupGetMushroomCutscene(EnTrt* this) {
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
        if (this->cutscene != this->tmpGetMushroomCutscene) {
            ActorCutscene_Stop(this->cutscene);
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->tmpGetMushroomCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = ENTRT_CUTSCENESTATE_WAITING;
        }
    }
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING_SPECIAL;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

u16 EnTrt_GetItemTextId(EnTrt* this) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (item->actor.params == SI_POTION_BLUE && !(this->flags & ENTRT_GIVEN_MUSHROOM)) {
        return 0x880;
    }
    return item->actor.textId;
}

u16 EnTrt_GetItemChoiceTextId(EnTrt* this) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (item->actor.params == SI_POTION_BLUE && !(gSaveContext.weekEventReg[0x35] & 0x10)) {
        this->textId = 0x881;
        return 0x881;
    }
    return item->choiceTextId;
}

void EnTrt_EndInteraction(GlobalContext* globalCtx, EnTrt* this) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
    }
    func_800B84D0(&this->actor, globalCtx);
    globalCtx->msgCtx.unk11F22 = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = false;
    player->stateFlags2 &= ~0x20000000;
    globalCtx->interfaceCtx.unk_222 = 0;
    globalCtx->interfaceCtx.unk_224 = 0;
    this->textId = 0x834;
    this->timer = 80;
    this->flags |= ENTRT_FULLY_AWAKE;
    this->sleepSoundTimer = 10;
    this->actor.textId = 0;
    this->actionFunc = EnTrt_IdleSleeping;
    this->blinkFunc = EnTrt_NodOff;
}

s32 EnTrt_TestEndInteraction(EnTrt* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        EnTrt_EndInteraction(globalCtx, this);
        return true;
    }
    return false;
}

s32 EnTrt_TestCancelOption(EnTrt* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, EnTrt_GetItemTextId(this));
        return true;
    }
    return false;
}

void EnTrt_SetupStartShopping(GlobalContext* globalCtx, EnTrt* this, u8 skipHello) {
    func_8011552C(globalCtx, 0x10);
    if (!skipHello) {
        this->actionFunc = EnTrt_Hello;
    } else {
        EnTrt_StartShopping(globalCtx, this);
    }
}

void EnTrt_StartShopping(GlobalContext* globalCtx, EnTrt* this) {
    func_80151938(globalCtx, 0x83E);
    func_8011552C(globalCtx, 6);
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = true;
    this->actionFunc = EnTrt_FaceShopkeeper;
}

void EnTrt_UpdateJoystickInputState(GlobalContext* globalCtx, EnTrt* this) {
    s8 stickX = CONTROLLER1(globalCtx)->rel.stick_x;
    s8 stickY = CONTROLLER1(globalCtx)->rel.stick_y;

    if (this->stickAccumX == 0) {
        if (stickX > 30 || stickX < -30) {
            this->stickAccumX = stickX;
        }
    } else if (stickX <= 30 && stickX >= -30) {
        this->stickAccumX = 0;
    } else if ((this->stickAccumX * stickX) < 0) { // Stick has swapped directions
        this->stickAccumX = stickX;
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
        }
    } else if (stickY <= 30 && stickY >= -30) {
        this->stickAccumY = 0;
    } else if ((this->stickAccumY * stickY) < 0) { // Stick has swapped directions
        this->stickAccumY = stickY;
    } else {
        this->stickAccumY += stickY;
        if (this->stickAccumY > 2000) {
            this->stickAccumY = 2000;
        } else if (this->stickAccumY < -2000) {
            this->stickAccumY = -2000;
        }
    }
}

u8 EnTrt_SetCursorIndexFromNeutral(EnTrt* this, u8 shelfOffset) {
    if (this->items[shelfOffset] != NULL) {
        return shelfOffset;
    }
    return CURSOR_INVALID;
}

void EnTrt_Hello(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (this->cutsceneState == ENTRT_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (talkState == 5 && func_80147624(globalCtx)) {
        play_sound(NA_SE_SY_MESSAGE_PASS);
        if (!EnTrt_TestEndInteraction(this, globalCtx, CONTROLLER1(globalCtx))) {
            EnTrt_StartShopping(globalCtx, this);
        }
    }
}

void EnTrt_GetMushroom(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = GET_PLAYER(globalCtx);

    this->tmpGetMushroomCutscene = this->getMushroomCutscene;
    if (this->cutsceneState != ENTRT_CUTSCENESTATE_PLAYING_SPECIAL) {
        EnTrt_SetupGetMushroomCutscene(this);
        if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING_SPECIAL) {
            player->stateFlags2 &= ~0x20000000;
        }
    } else if (talkState == 5 && func_80147624(globalCtx)) {
        switch (this->textId) {
            case 0x883:
                this->textId = 0x884;
                func_801518B0(globalCtx, this->textId, &this->actor);
                gSaveContext.weekEventReg[0x35] |= 8;
                func_80123D50(globalCtx, GET_PLAYER(globalCtx), 18, 21);
                break;
            case 0x888:
                this->textId = 0x889;
                func_801518B0(globalCtx, this->textId, &this->actor);
                break;
            case 0x889:
                if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING_SPECIAL) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
                }
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = EnTrt_PayForMushroom;
                break;
            default:
                this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
                EnTrt_EndInteraction(globalCtx, this);
                break;
        }
    }
}

void EnTrt_PayForMushroom(EnTrt* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80123D50(globalCtx, GET_PLAYER(globalCtx), 18, 21);
        this->actionFunc = EnTrt_SetupItemGiven;
    } else {
        func_800B8A1C(&this->actor, globalCtx, GI_RUPEE_RED, 300.0f, 300.0f);
    }
}

void EnTrt_Goodbye(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        switch (this->textId) {
            case 0x886:
                this->textId = 0x887;
                func_80151938(globalCtx, this->textId);
                break;
            case 0x887:
            case 0x88B:
                EnTrt_EndInteraction(globalCtx, this);
                break;
        }
    }
}

void EnTrt_SetupTryToGiveRedPotion(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        if (this->textId == 0x88F) {
            if (func_80114E90() || !(gSaveContext.weekEventReg[0xC] & 0x10)) {
                if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
                }
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = EnTrt_GiveRedPotionForKoume;
            } else {
                this->tmpTextId = this->textId;
                this->textId = 0x88E;
                gSaveContext.weekEventReg[0x55] |= 8;
                func_801518B0(globalCtx, this->textId, &this->actor);
                this->actionFunc = EnTrt_EndConversation;
            }
        } else {
            if (gSaveContext.weekEventReg[0xC] & 8) {
                this->textId = 0x83D;
                EnTrt_SetupStartShopping(globalCtx, this, 0);
            } else if (gSaveContext.weekEventReg[0x54] & 0x40) {
                this->textId = 0x83B;
                if (func_80114F2C(ITEM_POTION_RED)) {
                    EnTrt_SetupStartShopping(globalCtx, this, false);
                } else {
                    this->actionFunc = EnTrt_TryToGiveRedPotion;
                }
            } else if (gSaveContext.weekEventReg[0x10] & 0x10) {
                this->timer = 30;
                this->textId = 0x838;
                this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING_SPECIAL;
                this->actionFunc = EnTrt_Surprised;
                return;
            } else if (gSaveContext.weekEventReg[0x11] & 1) {
                this->textId = 0x835;
                EnTrt_SetupStartShopping(globalCtx, this, false);
            }
            func_801518B0(globalCtx, this->textId, &this->actor);
        }
    }
}

void EnTrt_GiveRedPotionForKoume(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        if (!(gSaveContext.weekEventReg[0xC] & 0x10)) {
            gSaveContext.weekEventReg[0xC] |= 0x10;
        }
        gSaveContext.weekEventReg[0x54] |= 0x40;
        player->stateFlags2 &= ~0x20000000;
        this->actionFunc = EnTrt_GivenRedPotionForKoume;
    } else if (gSaveContext.weekEventReg[0xC] & 0x10) {
        func_800B8A1C(&this->actor, globalCtx, GI_POTION_RED, 300.0f, 300.0f);
    } else {
        func_800B8A1C(&this->actor, globalCtx, GI_BOTTLE_POTION_RED, 300.0f, 300.0f);
    }
}

void EnTrt_GivenRedPotionForKoume(EnTrt* this, GlobalContext* globalCtx) {
    //! @bug: player is set to NULL not PLAYER
    Player* player = NULL;

    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
            if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
                ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
                player->stateFlags2 |= 0x20000000;
                //! @bug: EnTrt_ContinueShopping gets overwritten by EnTrt_ItemGiven
                this->actionFunc = EnTrt_ContinueShopping;
                this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
            } else {
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                }
                this->cutscene = this->lookToShopkeeperCutscene;
                ActorCutscene_SetIntentToPlay(this->cutscene);
            }
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
        this->actionFunc = EnTrt_ItemGiven;
    }
}

void EnTrt_EndConversation(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (talkState == 5) {
        if (func_80147624(globalCtx)) {
            EnTrt_EndInteraction(globalCtx, this);
        }
    } else if (talkState == 6) {
        if (func_80147624(globalCtx)) {
            EnTrt_EndInteraction(globalCtx, this);
        }
    }
}

s32 EnTrt_FacingShopkeeperDialogResult(EnTrt* this, GlobalContext* globalCtx) {
    switch (globalCtx->msgCtx.choiceIndex) {
        case 0:
            func_8019F208();
            EnTrt_SetupTalkToShopkeeper(globalCtx, this);
            return true;
        case 1:
            func_8019F230();
            EnTrt_EndInteraction(globalCtx, this);
            return true;
    }
    return false;
}

void EnTrt_FaceShopkeeper(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    u8 cursorIdx;

    if (this->cutsceneState == ENTRT_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookForwardCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = ENTRT_CUTSCENESTATE_WAITING;
    } else if (talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (!EnTrt_TestEndInteraction(this, globalCtx, CONTROLLER1(globalCtx))) {
            if ((!func_80147624(globalCtx) || !EnTrt_FacingShopkeeperDialogResult(this, globalCtx)) &&
                (this->stickAccumX > 0)) {
                cursorIdx = EnTrt_SetCursorIndexFromNeutral(this, 2);
                if (cursorIdx != CURSOR_INVALID) {
                    this->cursorIdx = cursorIdx;
                    this->actionFunc = EnTrt_LookToShelf;
                    func_8011552C(globalCtx, 6);
                    this->stickRightPrompt.isEnabled = false;
                    play_sound(NA_SE_SY_CURSOR);
                }
            }
        }
    }
}

void EnTrt_LookToShelf(EnTrt* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
    }
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToShelfCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = ENTRT_CUTSCENESTATE_WAITING;
    } else if (this->cutsceneState == ENTRT_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
            EnTrt_UpdateCursorPos(globalCtx, this);
            this->actionFunc = EnTrt_BrowseShelf;
            func_80151938(globalCtx, EnTrt_GetItemTextId(this));
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void EnTrt_CursorLeftRight(GlobalContext* globalCtx, EnTrt* this) {
    u8 curTemp = this->cursorIdx;

    if (this->stickAccumX < 0) {
        if (curTemp != 2) {
            curTemp++;
        } else {
            EnTrt_SetupLookToShopkeeperFromShelf(globalCtx, this);
        }
        if (this->items[curTemp] != NULL) {
            this->cursorIdx = curTemp;
        }
    } else if (this->stickAccumX > 0) {
        if (curTemp != 0) {
            curTemp--;
        }
        if (this->items[curTemp] != NULL) {
            this->cursorIdx = curTemp;
        }
    }
}

s32 EnTrt_HasPlayerSelectedItem(GlobalContext* globalCtx, EnTrt* this, Input* input) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (EnTrt_TestEndInteraction(this, globalCtx, input)) {
        return true;
    }
    if (EnTrt_TestItemSelected(globalCtx)) {
        if (item->actor.params != SI_POTION_BLUE || (this->flags & ENTRT_GIVEN_MUSHROOM)) {
            this->tmpActionFunc = this->actionFunc;
            func_80151938(globalCtx, EnTrt_GetItemChoiceTextId(this));
            play_sound(NA_SE_SY_DECIDE);
            this->stickLeftPrompt.isEnabled = false;
            this->stickRightPrompt.isEnabled = false;
            this->drawCursor = 0;
            this->actionFunc = EnTrt_SelectItem;
        } else {
            play_sound(NA_SE_SY_ERROR);
        }
        return true;
    }
    return false;
}

void EnTrt_BrowseShelf(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    u8 prevCursorIdx = this->cursorIdx;
    u8 cursorIdx;

    if (!EnTrt_ReturnItemToShelf(this)) {
        this->delayTimer = 3;
    } else if (this->delayTimer != 0) {
        this->delayTimer--;
    } else {
        this->drawCursor = 0xFF;
        this->stickLeftPrompt.isEnabled = true;
        EnTrt_UpdateCursorPos(globalCtx, this);
        if (talkState == 5) {
            func_8011552C(globalCtx, 6);
            if (!EnTrt_HasPlayerSelectedItem(globalCtx, this, CONTROLLER1(globalCtx))) {
                EnTrt_CursorLeftRight(globalCtx, this);
                if (this->cursorIdx != prevCursorIdx) {
                    func_80151938(globalCtx, EnTrt_GetItemTextId(this));
                    play_sound(NA_SE_SY_CURSOR);
                }
            }
        }
    }
}

void EnTrt_SetupBuyItemWithFanfare(GlobalContext* globalCtx, EnTrt* this) {
    Player* player = GET_PLAYER(globalCtx);

    func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    globalCtx->msgCtx.unk11F22 = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    player->stateFlags2 &= ~0x20000000;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    this->actionFunc = EnTrt_BuyItemWithFanfare;
}

void EnTrt_SetupCannotBuy(GlobalContext* globalCtx, EnTrt* this, u16 textId) {
    func_80151938(globalCtx, textId);
    this->actionFunc = EnTrt_CannotBuy;
}

void EnTrt_SetupCanBuy(GlobalContext* globalCtx, EnTrt* this, u16 textId) {
    func_80151938(globalCtx, textId);
    this->actionFunc = EnTrt_CanBuy;
}

void EnTrt_HandleCanBuyItem(GlobalContext* globalCtx, EnTrt* this) {
    EnGirlA* item = this->items[this->cursorIdx];
    EnGirlA* item2;

    switch (item->canBuyFunc(globalCtx, item)) {
        case CANBUY_RESULT_SUCCESS_1:
            if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
                ActorCutscene_Stop(this->cutscene);
                this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
            }
            func_8019F208();
            item2 = this->items[this->cursorIdx];
            item2->buyFanfareFunc(globalCtx, item2);
            EnTrt_SetupBuyItemWithFanfare(globalCtx, this);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_SUCCESS_2:
            func_8019F208();
            item->buyFunc(globalCtx, item);
            EnTrt_SetupCanBuy(globalCtx, this, 0x848);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_NO_ROOM:
            play_sound(NA_SE_SY_ERROR);
            EnTrt_SetupCannotBuy(globalCtx, this, 0x641);
            break;
        case CANBUY_RESULT_NEED_EMPTY_BOTTLE:
            play_sound(NA_SE_SY_ERROR);
            EnTrt_SetupCannotBuy(globalCtx, this, 0x846);
            break;
        case CANBUY_RESULT_NEED_RUPEES:
            play_sound(NA_SE_SY_ERROR);
            EnTrt_SetupCannotBuy(globalCtx, this, 0x847);
            break;
        case CANBUY_RESULT_CANNOT_GET_NOW:
            play_sound(NA_SE_SY_ERROR);
            EnTrt_SetupCannotBuy(globalCtx, this, 0x643);
            break;
    }
}

void EnTrt_SelectItem(EnTrt* this, GlobalContext* globalCtx) {
    EnGirlA* item = this->items[this->cursorIdx];
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (EnTrt_TakeItemOffShelf(this)) {
        if (talkState == 4) {
            func_8011552C(globalCtx, 6);
            if (!EnTrt_TestCancelOption(this, globalCtx, CONTROLLER1(globalCtx)) && func_80147624(globalCtx)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        EnTrt_HandleCanBuyItem(globalCtx, this);
                        break;
                    case 1:
                        func_8019F230();
                        this->actionFunc = this->tmpActionFunc;
                        func_80151938(globalCtx, EnTrt_GetItemTextId(this));
                        break;
                }
            }
        } else if (talkState == 5 && func_80147624(globalCtx)) {
            if (!func_80114E90()) {
                play_sound(NA_SE_SY_ERROR);
                EnTrt_SetupCannotBuy(globalCtx, this, 0x846);
            } else {
                if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
                }
                EnTrt_SetupBuyItemWithFanfare(globalCtx, this);
                this->drawCursor = 0;
                this->shopItemSelectedTween = 0.0f;
                item->boughtFunc(globalCtx, item);
                gSaveContext.weekEventReg[0x35] |= 0x10;
            }
        }
    }
}

void EnTrt_IdleSleeping(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((gSaveContext.weekEventReg[0x55] & 8) && !(gSaveContext.weekEventReg[0x54] & 0x40)) {
        this->textId = 0x88F;
    } else if (!(this->flags & ENTRT_MET)) {
        this->textId = 0x834;
    } else {
        this->textId = 0x83E;
    }
    if (!(gSaveContext.weekEventReg[0x35] & 8)) {
        this->talkOptionTextId = 0x845;
    } else if (this->flags & ENTRT_GIVEN_MUSHROOM) {
        this->talkOptionTextId = 0x882;
    } else {
        this->talkOptionTextId = 0x885;
    }
    this->tmpTextId = this->textId;

    if (player->transformation == PLAYER_FORM_GORON || player->transformation == PLAYER_FORM_ZORA ||
        player->transformation == PLAYER_FORM_DEKU) {
        this->textId = 0x850;
    }
    if (Player_GetMask(globalCtx) == PLAYER_MASK_MASK_OF_SCENTS) {
        this->textId = 0x890;
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (player->transformation == PLAYER_FORM_HUMAN) {
            this->flags |= ENTRT_MET;
        }
        if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookForwardCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = ENTRT_CUTSCENESTATE_WAITING;
        }
        player->stateFlags2 |= 0x20000000;
        this->timer = 45;
        this->actionFunc = EnTrt_BeginInteraction;
    } else if ((player->actor.world.pos.x >= -50.0f && player->actor.world.pos.x <= -25.0f) &&
               (player->actor.world.pos.z >= -19.0f && player->actor.world.pos.z <= 30.0f)) {
        func_800B8614(&this->actor, globalCtx, 200.0f);
    }
    if (DECR(this->timer) == 0) {
        this->timer = 40;
        EnTrt_ChangeAnim(&this->skelAnime, sAnimations, 1);
        this->animationIdx = 1;
        this->actionFunc = EnTrt_IdleAwake;
        this->blinkFunc = EnTrt_OpenThenCloseEyes;
    }
    if (DECR(this->sleepSoundTimer) == 0) {
        func_800B9010(&this->actor, NA_SE_EN_KOTAKE_SLEEP - SFX_FLAG);
    }
}

void EnTrt_IdleAwake(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->flags &= ~ENTRT_FULLY_AWAKE;
    if (player->transformation == PLAYER_FORM_HUMAN || player->transformation == PLAYER_FORM_FIERCE_DEITY) {
        if (Player_GetMask(globalCtx) == PLAYER_MASK_MASK_OF_SCENTS) {
            this->textId = 0x890;
        } else {
            this->textId = this->tmpTextId;
        }
    } else {
        this->textId = 0x850;
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookForwardCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = ENTRT_CUTSCENESTATE_WAITING;
        }
        player->stateFlags2 |= 0x20000000;
        if (player->transformation == PLAYER_FORM_HUMAN) {
            this->flags |= ENTRT_MET;
        }
        EnTrt_ChangeAnim(&this->skelAnime, sAnimations, 2);
        this->blinkFunc = EnTrt_EyesClosed;
        this->timer = 45;
        this->actionFunc = EnTrt_BeginInteraction;
    } else if ((player->actor.world.pos.x >= -50.0f && player->actor.world.pos.x <= -25.0f) &&
               (player->actor.world.pos.z >= -19.0f && player->actor.world.pos.z <= 30.0f)) {
        func_800B8614(&this->actor, globalCtx, 200.0f);
    }
    if (DECR(this->timer) == 0) {
        this->timer = Rand_S16Offset(150, 100);
        EnTrt_ChangeAnim(&this->skelAnime, sAnimations, 2);
        this->animationIdx = 2;
        this->sleepSoundTimer = 10;
        this->actor.textId = 0;
        this->actionFunc = EnTrt_IdleSleeping;
        this->blinkFunc = EnTrt_EyesClosed;
    }
}

void EnTrt_BeginInteraction(EnTrt* this, GlobalContext* globalCtx) {
    s16 curFrame = this->skelAnime.curFrame / this->skelAnime.playSpeed;
    s16 animLastFrame = Animation_GetLastFrame(&D_060030EC.common) / (s16)this->skelAnime.playSpeed;

    if (this->cutsceneState == ENTRT_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING_SPECIAL;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    } else if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING_SPECIAL) {
        if (this->animationIdx != 5) {
            if (curFrame == animLastFrame) {
                EnTrt_ChangeAnim(&this->skelAnime, sAnimations, 3);
                this->animationIdx = 3;
                this->blinkFunc = EnTrt_OpenEyesThenSetToBlink;
                this->timer = 10;
                this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_KOTAKE_SURPRISED2);
            }
        } else {
            this->blinkFunc = EnTrt_OpenEyesThenSetToBlink;
            this->timer = 10;
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
        }
    } else if (DECR(this->timer) == 0) {
        this->timer = Rand_S16Offset(40, 20);
        EnTrt_ChangeAnim(&this->skelAnime, sAnimations, 5);
        func_801518B0(globalCtx, this->textId, &this->actor);
        this->animationIdx = 5;
        switch (this->textId) {
            case 0x834:
                if (!(gSaveContext.weekEventReg[0xC] & 8) && !(gSaveContext.weekEventReg[0x54] & 0x40) &&
                    !(gSaveContext.weekEventReg[0x10] & 0x10) && !(gSaveContext.weekEventReg[0x11] & 1)) {
                    func_8011552C(globalCtx, 6);
                    this->stickLeftPrompt.isEnabled = false;
                    this->stickRightPrompt.isEnabled = true;
                    this->actionFunc = EnTrt_Hello;
                } else {
                    this->actionFunc = EnTrt_SetupTryToGiveRedPotion;
                }
                break;
            case 0x83E:
                func_8011552C(globalCtx, 6);
                this->stickLeftPrompt.isEnabled = false;
                this->stickRightPrompt.isEnabled = true;
                this->actionFunc = EnTrt_FaceShopkeeper;
                break;
            case 0x850:
            case 0x890:
                this->actionFunc = EnTrt_SetupEndInteraction;
                break;
            case 0x88F:
                this->actionFunc = EnTrt_SetupTryToGiveRedPotion;
                break;
        }
    }
}

void EnTrt_Surprised(EnTrt* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING_SPECIAL;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    } else if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING_SPECIAL) {
        if (DECR(this->timer) == 0) {
            EnTrt_ChangeAnim(&this->skelAnime, sAnimations, 4);
            this->animationIdx = 4;
            this->blinkFunc = EnTrt_OpenEyes2;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_KOTAKE_SURPRISED);
            this->timer = 30;
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
        }
    } else if (DECR(this->timer) == 0) {
        this->timer = Rand_S16Offset(40, 20);
        EnTrt_ChangeAnim(&this->skelAnime, sAnimations, 5);
        func_801518B0(globalCtx, this->textId, &this->actor);
        this->animationIdx = 5;
        this->actionFunc = EnTrt_TryToGiveRedPotionAfterSurprised;
    }
}

void EnTrt_TryToGiveRedPotionAfterSurprised(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    this->blinkFunc = EnTrt_Blink;
    if (talkState == 6 && func_80147624(globalCtx)) {
        if (func_80114E90() || !(gSaveContext.weekEventReg[0xC] & 0x10)) {
            if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
                ActorCutscene_Stop(this->cutscene);
                this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
            }
            this->actionFunc = EnTrt_GiveRedPotionForKoume;
        } else {
            this->tmpTextId = this->textId;
            this->textId = 0x88E;
            gSaveContext.weekEventReg[0x55] |= 8;
            func_801518B0(globalCtx, this->textId, &this->actor);
            this->actionFunc = EnTrt_EndConversation;
        }
    }
}

void EnTrt_TryToGiveRedPotion(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        if (this->textId == 0x83C) {
            if (func_80114E90()) {
                if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
                }
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = EnTrt_GiveRedPotionForKoume;
            } else {
                this->tmpTextId = this->textId;
                this->textId = 0x88E;
                gSaveContext.weekEventReg[0x55] |= 8;
                func_801518B0(globalCtx, this->textId, &this->actor);
                this->actionFunc = EnTrt_EndConversation;
            }
        } else {
            this->textId = 0x83C;
            func_801518B0(globalCtx, this->textId, &this->actor);
        }
    }
}

void EnTrt_ItemGiven(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            player->stateFlags2 |= 0x20000000;
            this->actionFunc = EnTrt_ContinueShopping;
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookToShopkeeperCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        switch (this->textId) {
            case 0x889:
                this->textId = 0x88A;
                break;
            case 0x881:
                this->textId = 0x88C;
                break;
            case 0x838:
            case 0x83C:
            case 0x88E:
            case 0x88F:
                this->textId = 0x83A;
                break;
            default:
                if (1) {}
                this->textId = 0x849;
                break;
        }
        func_80151938(globalCtx, this->textId);
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void EnTrt_SetupEndInteraction(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        EnTrt_EndInteraction(globalCtx, this);
    }
}

void EnTrt_ShopkeeperGone(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = GET_PLAYER(globalCtx);

    if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, this->textId, &this->actor);
    } else {
        if ((player->actor.world.pos.x >= -50.0f && player->actor.world.pos.x <= 50.0f) &&
            (player->actor.world.pos.z >= -19.0f && player->actor.world.pos.z <= 30.0f)) {
            func_800B8614(&this->actor, globalCtx, 200.0f);
        }
    }
    if (talkState == 6 && func_80147624(globalCtx)) {
        if (gSaveContext.weekEventReg[0x14] & 2) {
            globalCtx->nextEntranceIndex = 0xC50;
        } else {
            globalCtx->nextEntranceIndex = 0x8450;
        }
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 0x40;
        globalCtx->sceneLoadFlag = 0x14;
    }
}

void EnTrt_CannotBuy(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, EnTrt_GetItemTextId(this));
    }
}

void EnTrt_CanBuy(EnTrt* this, GlobalContext* globalCtx) {
    EnGirlA* item;

    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->shopItemSelectedTween = 0.0f;
        EnTrt_ResetItemPosition(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, EnTrt_GetItemTextId(this));
    }
}

void EnTrt_BuyItemWithFanfare(EnTrt* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = EnTrt_SetupItemGiven;
    } else {
        func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    }
}

void EnTrt_SetupItemGiven(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        this->actionFunc = EnTrt_ItemGiven;
        if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookToShopkeeperCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void EnTrt_ContinueShopping(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = GET_PLAYER(globalCtx);
    EnGirlA* item;

    if (talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (func_80147624(globalCtx)) {
            EnTrt_ResetItemPosition(this);
            item = this->items[this->cursorIdx];
            item->restockFunc(globalCtx, item);
            if (!EnTrt_TestEndInteraction(this, globalCtx, CONTROLLER1(globalCtx))) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        player->actor.shape.rot.y = BINANG_ROT180(player->actor.shape.rot.y);
                        player->stateFlags2 |= 0x20000000;
                        func_801518B0(globalCtx, this->textId, &this->actor);
                        EnTrt_SetupStartShopping(globalCtx, this, true);
                        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
                        break;
                    case 1:
                    default:
                        func_8019F230();
                        EnTrt_EndInteraction(globalCtx, this);
                        break;
                }
            }
        }
    } else if (talkState == 5) {
        if (func_80147624(globalCtx)) {
            EnTrt_ResetItemPosition(this);
            item = this->items[this->cursorIdx];
            item->restockFunc(globalCtx, item);
            EnTrt_EndInteraction(globalCtx, this);
        }
    }
}

void EnTrt_PositionSelectedItem(EnTrt* this) {
    static Vec3f sSelectedItemPosition = { 6.0f, 35.0f, -12.0f };
    u8 i = this->cursorIdx;
    EnGirlA* item;
    ShopItem* shopItem = &sShop[i];
    Vec3f worldPos;

    item = this->items[i];

    VEC3F_LERPIMPDST(&worldPos, &shopItem->spawnPos, &sSelectedItemPosition, this->shopItemSelectedTween);

    item->actor.world.pos.x = worldPos.x;
    item->actor.world.pos.y = worldPos.y;
    item->actor.world.pos.z = worldPos.z;
}

void EnTrt_ResetItemPosition(EnTrt* this) {
    this->shopItemSelectedTween = 0.0f;
    EnTrt_PositionSelectedItem(this);
}

/*
 * Returns true when animation has completed
 */
s32 EnTrt_TakeItemOffShelf(EnTrt* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 1.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween >= 0.85f) {
        this->shopItemSelectedTween = 1.0f;
    }
    EnTrt_PositionSelectedItem(this);
    if (this->shopItemSelectedTween == 1.0f) {
        return true;
    }
    return false;
}

/*
 * Returns true when animation has completed
 */
s32 EnTrt_ReturnItemToShelf(EnTrt* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 0.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween <= 0.15f) {
        this->shopItemSelectedTween = 0.0f;
    }
    EnTrt_PositionSelectedItem(this);
    if (this->shopItemSelectedTween == 0.0f) {
        return true;
    }
    return false;
}

void EnTrt_UpdateItemSelectedProperty(EnTrt* this) {
    EnGirlA** items = this->items;
    EnGirlA* item;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->items); i++, items++) {
        item = *items;
        if (item != NULL) {
            if ((this->actionFunc != EnTrt_SelectItem) && (this->actionFunc != EnTrt_CannotBuy) &&
                (this->drawCursor == 0)) {
                item->isSelected = false;
            } else {
                item->isSelected = this->cursorIdx == i ? true : false;
            }
        }
    }
}

void EnTrt_UpdateCursorAnim(EnTrt* this) {
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

void EnTrt_UpdateStickDirectionPromptAnim(EnTrt* this) {
    f32 arrowAnimTween = this->arrowAnimTween;
    f32 stickAnimTween = this->stickAnimTween;

    // Possbily fake temps
    s32 maxColor = 255;
    f32 tmp;

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

    tmp = 155.0f * arrowAnimTween;

    this->stickAnimTween = stickAnimTween;

    this->stickLeftPrompt.arrowColor.r = COL_CHAN_MIX(255, 155.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColor.g = COL_CHAN_MIX(maxColor, 155.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColor.b = COL_CHAN_MIX(0, -100, arrowAnimTween);
    this->stickLeftPrompt.arrowColor.a = COL_CHAN_MIX(200, 50.0f, arrowAnimTween);

    this->stickRightPrompt.arrowColor.r = (maxColor - ((s32)tmp)) & 0xFF;
    this->stickRightPrompt.arrowColor.g = (255 - ((s32)tmp)) & 0xFF;
    this->stickRightPrompt.arrowColor.b = COL_CHAN_MIX(0, -100.0f, arrowAnimTween);
    this->stickRightPrompt.arrowColor.a = COL_CHAN_MIX(200, 50.0f, arrowAnimTween);

    this->stickRightPrompt.arrowTexX = 290.0f;
    this->stickLeftPrompt.arrowTexX = 33.0f;

    this->stickRightPrompt.stickTexX = 274.0f;
    this->stickRightPrompt.stickTexX += 8.0f * stickAnimTween;
    this->stickLeftPrompt.stickTexX = 49.0f;
    this->stickLeftPrompt.stickTexX -= 8.0f * stickAnimTween;

    this->stickLeftPrompt.arrowTexY = this->stickRightPrompt.arrowTexY = 91.0f;
    this->stickLeftPrompt.stickTexY = this->stickRightPrompt.stickTexY = 95.0f;
}

void EnTrt_OpenEyes(EnTrt* this) {
    if (this->eyeTextureIdx <= 0) {
        this->eyeTextureIdx = 0;
    } else {
        this->eyeTextureIdx--;
    }
}

void EnTrt_CloseEyes(EnTrt* this) {
    if (this->eyeTextureIdx >= 2) {
        this->eyeTextureIdx = 2;
    } else {
        this->eyeTextureIdx++;
    }
}

void EnTrt_Blink(EnTrt* this) {
    s16 decr = this->blinkTimer - 1;
    s16 eyeTextureIdxTemp;

    if (decr != 0) {
        this->blinkTimer = decr;
        return;
    }
    eyeTextureIdxTemp = this->eyeTextureIdx + 1;
    if (eyeTextureIdxTemp > 2) {
        this->eyeTextureIdx = 0;
        this->blinkTimer = (s32)(Rand_ZeroOne() * 60.0f) + 20;
    } else {
        this->eyeTextureIdx = eyeTextureIdxTemp;
        this->blinkTimer = 1;
    }
}

void EnTrt_NodOff(EnTrt* this) {
    s16 decr = this->blinkTimer - 1;
    s16 eyeTextureIdxTemp;

    if (decr != 0) {
        this->blinkTimer = decr;
        return;
    }
    eyeTextureIdxTemp = this->eyeTextureIdx + 1;
    if (eyeTextureIdxTemp > 2) {
        this->eyeTextureIdx = 1;
        this->blinkTimer = 20;
    } else {
        this->eyeTextureIdx = eyeTextureIdxTemp;
        this->blinkTimer = 3;
    }
}

void EnTrt_OpenThenCloseEyes(EnTrt* this) {
    if (this->skelAnime.curFrame >= 40.0f) {
        EnTrt_CloseEyes(this);
    } else if (this->skelAnime.curFrame >= 35.0f) {
        this->eyeTextureIdx = 1;
    } else if (this->skelAnime.curFrame >= 10.0f) {
        EnTrt_OpenEyes(this);
    }
}

void EnTrt_EyesClosed(EnTrt* this) {
    this->eyeTextureIdx = 2;
}

void EnTrt_OpenEyes2(EnTrt* this) {
    EnTrt_OpenEyes(this);
}

void EnTrt_OpenEyesThenSetToBlink(EnTrt* this) {
    if (this->skelAnime.curFrame >= 7.0f) {
        EnTrt_OpenEyes(this);
        if (this->eyeTextureIdx == 0) {
            this->blinkFunc = EnTrt_Blink;
        }
    }
}

void EnTrt_TalkToShopkeeper(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = GET_PLAYER(globalCtx);
    s32 itemGiven;

    if (talkState == 5) {
        if (func_80147624(globalCtx)) {
            if (this->talkOptionTextId == 0x845 || this->talkOptionTextId == 0x882) {
                func_80151938(globalCtx, 0xFF);
            } else {
                EnTrt_StartShopping(globalCtx, this);
            }
        }
    } else if (talkState == 16) {
        itemGiven = func_80123810(globalCtx);
        if (itemGiven > 0) {
            if (itemGiven == ITEM_MUSHROOM) {
                if (gSaveContext.weekEventReg[0x35] & 8) {
                    player->actor.textId = 0x888;
                } else {
                    player->actor.textId = 0x883;
                }
                this->textId = player->actor.textId;
                player->unk_A87 = itemGiven;
                this->actionFunc = EnTrt_GetMushroom;
            } else {
                if (this->flags & ENTRT_GIVEN_MUSHROOM) {
                    player->actor.textId = 0x88B;
                } else {
                    player->actor.textId = 0x886;
                }
                this->textId = player->actor.textId;
                this->actionFunc = EnTrt_Goodbye;
            }
            func_801477B4(globalCtx);
        } else if (itemGiven < 0) {
            if (this->flags & ENTRT_GIVEN_MUSHROOM) {
                this->textId = 0x88B;
            } else {
                this->textId = 0x886;
            }
            func_801518B0(globalCtx, this->textId, &this->actor);
            this->actionFunc = EnTrt_Goodbye;
        }
    }
}

void EnTrt_SetupTalkToShopkeeper(GlobalContext* globalCtx, EnTrt* this) {
    this->actionFunc = EnTrt_TalkToShopkeeper;
    func_80151938(globalCtx, this->talkOptionTextId);
    func_8011552C(globalCtx, 6);
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = false;
}

void EnTrt_SetupLookToShopkeeperFromShelf(GlobalContext* globalCtx, EnTrt* this) {
    play_sound(NA_SE_SY_CURSOR);
    this->drawCursor = 0;
    this->actionFunc = EnTrt_LookToShopkeeperFromShelf;
}

void EnTrt_LookToShopkeeperFromShelf(EnTrt* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_PLAYING) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = ENTRT_CUTSCENESTATE_STOPPED;
    }
    if (this->cutsceneState == ENTRT_CUTSCENESTATE_STOPPED) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToShopkeeperCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = ENTRT_CUTSCENESTATE_WAITING;
    } else if (this->cutsceneState == ENTRT_CUTSCENESTATE_WAITING) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = ENTRT_CUTSCENESTATE_PLAYING;
            EnTrt_StartShopping(globalCtx, this);
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void EnTrt_InitShopkeeper(EnTrt* this, GlobalContext* globalCtx) {
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0600FEF0, &D_0600FD34, NULL, NULL, 0);
    if (!(gSaveContext.weekEventReg[0xC] & 8) && !(gSaveContext.weekEventReg[0x54] & 0x40) && gSaveContext.day >= 2) {
        this->actor.draw = NULL;
    } else {
        this->actor.draw = EnTrt_Draw;
    }
}

void EnTrt_InitShop(EnTrt* this, GlobalContext* globalCtx) {
    u32 maxcolor = 255;
    EnTrt* this2;

    EnTrt_GetCutscenes(this, globalCtx);
    this->cutscene = this->lookForwardCutscene;
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    EnTrt_InitShopkeeper(this, globalCtx);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.colChkInfo.cylRadius = 50;
    this->timer = Rand_S16Offset(40, 20);
    if (!(gSaveContext.weekEventReg[0xC] & 8) && !(gSaveContext.weekEventReg[0x54] & 0x40) && gSaveContext.day >= 2) {
        this->textId = 0x84A;
        this->actionFunc = EnTrt_ShopkeeperGone;
    } else {
        this->sleepSoundTimer = 10;
        this->actor.textId = 0;
        this->actionFunc = EnTrt_IdleSleeping;
    }

    this->stickAccumY = 0;
    this->stickAccumX = 0;
    this->cursorIdx = 0;
    this->cursorPos.y = this->cursorPos.x = 100.0f;
    this->cursorPos.z = 1.2f;
    this->cursorColor.r = 0;
    this->cursorColor.g = 80;
    this->cursorColor.b = maxcolor;
    this->cursorColor.a = maxcolor;
    this->cursorAnimTween = 0.0f;
    this->cursorAnimState = 0;
    this->drawCursor = 0;

    this2 = this;

    this->stickLeftPrompt.stickColor.r = 200;
    this2->stickLeftPrompt.stickColor.g = 200;
    this2->stickLeftPrompt.stickColor.b = 200;
    this2->stickLeftPrompt.stickColor.a = 180;
    this2->stickLeftPrompt.stickTexX = 49.0f;
    this2->stickLeftPrompt.stickTexY = 95.0f;
    this2->stickLeftPrompt.arrowColor.r = maxcolor;
    this2->stickLeftPrompt.arrowColor.g = maxcolor;
    this2->stickLeftPrompt.arrowColor.b = 0;
    this2->stickLeftPrompt.arrowColor.a = 200;
    this2->stickLeftPrompt.arrowTexX = 33.0f;
    this2->stickLeftPrompt.arrowTexY = 91.0f;
    this2->stickLeftPrompt.texZ = 1.0f;
    this2->stickLeftPrompt.isEnabled = false;

    if (1) {}

    this2->stickRightPrompt.stickColor.r = 200;
    this2->stickRightPrompt.stickColor.g = 200;
    this2->stickRightPrompt.stickColor.b = 200;
    this2->stickRightPrompt.stickColor.a = 180;
    this2->stickRightPrompt.stickTexX = 274.0f;
    this2->stickRightPrompt.stickTexY = 95.0f;
    this2->stickRightPrompt.arrowColor.r = maxcolor;
    this2->stickRightPrompt.arrowColor.g = 0;
    this2->stickRightPrompt.arrowColor.b = 0;
    this2->stickRightPrompt.arrowColor.a = 200;
    this2->stickRightPrompt.arrowTexX = 290.0f;
    this2->stickRightPrompt.arrowTexY = 91.0f;
    this2->stickRightPrompt.texZ = 1.0f;
    this2->stickRightPrompt.isEnabled = false;

    this2->arrowAnimTween = 0.0f;
    this2->stickAnimTween = 0.0f;
    this2->arrowAnimState = 0;
    this2->stickAnimState = 0;
    this2->shopItemSelectedTween = 0.0f;

    this->actor.gravity = 0.0f;
    Actor_SetScale(&this->actor, sActorScale);
    EnTrt_SpawnShopItems(this, globalCtx, sShop);
    this->blinkTimer = 20;
    this->eyeTextureIdx = 0;
    this->blinkFunc = EnTrt_EyesClosed;
    if (gSaveContext.weekEventReg[0x35] & 8) {
        this->flags |= ENTRT_GIVEN_MUSHROOM;
    }

    this->actor.flags &= ~1;
}

void EnTrt_GetCutscenes(EnTrt* this, GlobalContext* globalCtx) {
    this->lookForwardCutscene = this->actor.cutscene;
    this->lookToShelfCutscene = ActorCutscene_GetAdditionalCutscene(this->lookForwardCutscene);
    this->lookToShopkeeperCutscene = ActorCutscene_GetAdditionalCutscene(this->lookToShelfCutscene);
    this->getMushroomCutscene = ActorCutscene_GetAdditionalCutscene(this->lookToShopkeeperCutscene);
}

void EnTrt_DrawCursor(GlobalContext* globalCtx, EnTrt* this, f32 x, f32 y, f32 z, u8 drawCursor) {
    s32 ulx, uly, lrx, lry;
    f32 w;
    s32 dsdx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (drawCursor != 0) {
        func_8012C654(globalCtx->state.gfxCtx);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, this->cursorColor.r, this->cursorColor.g, this->cursorColor.b,
                        this->cursorColor.a);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, &D_0401F740, G_IM_FMT_IA, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
        w = 16.0f * z;
        ulx = (x - w) * 4.0f;
        uly = (y - w + -12.0f) * 4.0f;
        lrx = (x + w) * 4.0f;
        lry = (y + w + -12.0f) * 4.0f;
        dsdx = (1.0f / z) * 1024.0f;
        gSPTextureRectangle(OVERLAY_DISP++, ulx, uly, lrx, lry, G_TX_RENDERTILE, 0, 0, dsdx, dsdx);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnTrt_DrawTextRec(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t, f32 dx,
                       f32 dy) {
    f32 unk;
    s32 ulx, uly, lrx, lry;
    f32 w, h;
    s32 dsdx, dtdy;

    ((void)"../z_en_trt.c"); // Unreferenced

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

void EnTrt_DrawStickDirectionPrompt(GlobalContext* globalCtx, EnTrt* this) {
    s32 drawStickRightPrompt = this->stickLeftPrompt.isEnabled;
    s32 drawStickLeftPrompt = this->stickRightPrompt.isEnabled;

    ((void)"../z_en_trt.c"); // Unreferenced

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (drawStickRightPrompt || drawStickLeftPrompt) {
        func_8012C654(globalCtx->state.gfxCtx);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetTextureImage(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, &D_0401F8C0);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPLoadSync(OVERLAY_DISP++);
        gDPLoadBlock(OVERLAY_DISP++, G_TX_LOADTILE, 0, 0, 191, 1024);
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPSetTileSize(OVERLAY_DISP++, G_TX_RENDERTILE, 0, 0, 15 * 4, 23 * 4);
        if (drawStickRightPrompt) {
            EnTrt_DrawTextRec(globalCtx, this->stickLeftPrompt.arrowColor.r, this->stickLeftPrompt.arrowColor.g,
                              this->stickLeftPrompt.arrowColor.b, this->stickLeftPrompt.arrowColor.a,
                              this->stickLeftPrompt.arrowTexX, this->stickLeftPrompt.arrowTexY,
                              this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            EnTrt_DrawTextRec(globalCtx, this->stickRightPrompt.arrowColor.r, this->stickRightPrompt.arrowColor.g,
                              this->stickRightPrompt.arrowColor.b, this->stickRightPrompt.arrowColor.a,
                              this->stickRightPrompt.arrowTexX, this->stickRightPrompt.arrowTexY,
                              this->stickRightPrompt.texZ, 0, 0, 1.0f, 1.0f);
        }
        gDPSetTextureImage(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, &D_0401F7C0);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPLoadSync(OVERLAY_DISP++);
        gDPLoadBlock(OVERLAY_DISP++, G_TX_LOADTILE, 0, 0, 127, 1024);
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetTile(OVERLAY_DISP++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
                   G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
        gDPSetTileSize(OVERLAY_DISP++, G_TX_RENDERTILE, 0, 0, 15 * 4, 15 * 4);
        if (drawStickRightPrompt) {
            EnTrt_DrawTextRec(globalCtx, this->stickLeftPrompt.stickColor.r, this->stickLeftPrompt.stickColor.g,
                              this->stickLeftPrompt.stickColor.b, this->stickLeftPrompt.stickColor.a,
                              this->stickLeftPrompt.stickTexX, this->stickLeftPrompt.stickTexY,
                              this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            EnTrt_DrawTextRec(globalCtx, this->stickRightPrompt.stickColor.r, this->stickRightPrompt.stickColor.g,
                              this->stickRightPrompt.stickColor.b, this->stickRightPrompt.stickColor.a,
                              this->stickRightPrompt.stickTexX, this->stickRightPrompt.stickTexY,
                              this->stickRightPrompt.texZ, 0, 0, 1.0f, 1.0f);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

void EnTrt_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    EnTrt_InitShop(this, globalCtx);
}

void EnTrt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTrt_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt* this = THIS;

    this->blinkFunc(this);
    EnTrt_UpdateJoystickInputState(globalCtx, this);
    EnTrt_UpdateItemSelectedProperty(this);
    EnTrt_UpdateStickDirectionPromptAnim(this);
    EnTrt_UpdateCursorAnim(this);
    EnTrt_UpdateHeadYawAndPitch(this, globalCtx);
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, 90.0f);
    SkelAnime_Update(&this->skelAnime);
    EnTrt_UpdateCollider(this, globalCtx);
}

void EnTrt_UpdateHeadYawAndPitch(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f playerPos;
    Vec3f pos;

    Math_SmoothStepToS(&this->headYaw, this->actor.yawTowardsPlayer - this->actor.shape.rot.y, 4, 0x38E0, 1);
    this->headYaw = CLAMP(this->headYaw, -0x38E0, 0x38E0);

    playerPos = player->actor.world.pos;
    playerPos.y = player->bodyPartsPos[7].y + 3.0f;
    pos = this->actor.world.pos;
    Math_SmoothStepToS(&this->headPitch, Math_Vec3f_Pitch(&pos, &playerPos), 4, 0x1C70, 1);
    this->headPitch = CLAMP(this->headPitch, -0x1C70, 0x1C70);
}

void EnTrt_UpdateHeadPosAndRot(s16 pitch, s16 yaw, Vec3f* pos, Vec3s* rot, s32 isFullyAwake) {
    Vec3f newPos;
    Vec3f D_801D15B0tmp = D_801D15B0;
    Vec3s newRot;
    MtxF currentState;

    Matrix_MultiplyVector3fByState(&D_801D15B0tmp, &newPos);
    Matrix_CopyCurrentState(&currentState);
    func_8018219C(&currentState, &newRot, MTXMODE_NEW);
    *pos = newPos;
    if (isFullyAwake) {
        newRot.x += pitch;
        newRot.y += yaw;
        Math_SmoothStepToS(&rot->x, newRot.x, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&rot->y, newRot.y, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&rot->z, newRot.z, 4, 0x1FFE, 1);
    } else {
        rot->x = newRot.x;
        rot->y = newRot.y;
        rot->z = newRot.z;
    }
}

s32 EnTrt_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTrt* this = THIS;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->items); i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }

    if (limbIndex == 14) {
        *dList = NULL;
    }
    return 0;
}

void EnTrt_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTrt* this = THIS;
    s32 isFullyAwake;

    isFullyAwake = false;
    if (this->flags & ENTRT_FULLY_AWAKE) {
        isFullyAwake = true;
    }
    if (limbIndex == 21) {
        EnTrt_UpdateHeadPosAndRot(this->headPitch, this->headYaw, &this->headPos, &this->headRot, isFullyAwake);
        Matrix_InsertTranslation(this->headPos.x, this->headPos.y, this->headPos.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->headRot.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->headRot.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->headRot.z, MTXMODE_APPLY);
    }
}

void EnTrt_UnkActorDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnTrt* this = THIS;

    if (limbIndex == 21) {
        Matrix_InsertTranslation(this->headPos.x, this->headPos.y, this->headPos.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->headRot.y, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->headRot.x, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->headRot.z, MTXMODE_APPLY);
    }
}

void EnTrt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr sEyeTextures[] = { &D_0600B0B8, &D_0600B8B8, &D_0600C0B8 };
    EnTrt* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIdx]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIdx]));
    func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                  EnTrt_OverrideLimbDraw, EnTrt_PostLimbDraw, EnTrt_UnkActorDraw, &this->actor);
    EnTrt_DrawCursor(globalCtx, this, this->cursorPos.x, this->cursorPos.y, this->cursorPos.z, this->drawCursor);
    EnTrt_DrawStickDirectionPrompt(globalCtx, this);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
