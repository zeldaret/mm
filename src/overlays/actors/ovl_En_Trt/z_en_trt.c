#include "z_en_trt.h"

#define FLAGS 0x00000009

#define THIS ((EnTrt*)thisx)

#define ColChanMix(c1, c2, m) (c1 - (s32)(c2 * m)) & 0xFF

void EnTrt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTrt_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A8ED3C(EnTrt* this, GlobalContext* globalCtx);
void func_80A8EFA4(EnTrt* this, GlobalContext* globalCtx);
void func_80A8ECA4(EnTrt* this, GlobalContext* globalCtx);
void func_80A8DD60(EnTrt* this, GlobalContext* globalCtx);
void func_80A8D094(EnTrt* this, GlobalContext* globalCtx);
void func_80A8E91C(EnTrt* this);
void func_80A8B88C(EnTrt* this, GlobalContext* globalCtx, ShopItem* shopItems);
void func_80A8D5C8(EnTrt* this, GlobalContext* globalCtx);
void func_80A8B770(SkelAnime* skelAnime, ActorAnimationEntryS* animations, s32 idx);
void func_80A8D380(EnTrt* this, GlobalContext* globalCtx);
void func_80A8E890(EnTrt* this);
void func_80A8E94C(EnTrt* this);
void func_80A8BF24(EnTrt* this, GlobalContext* globalCtx);
void func_80A8C288(EnTrt* this, GlobalContext* globalCtx);
void func_80A8C74C(EnTrt* this, GlobalContext* globalCtx);
void func_80A8DD10(EnTrt* this, GlobalContext* globalCtx);
void func_80A8E774(EnTrt* this);
void func_80A8E754(EnTrt* this);
void func_80A8E79C(EnTrt* this);
s32 func_80A8BC8C(EnTrt* this, GlobalContext* globalCtx, Input* input);
void func_80A8BD7C(GlobalContext* globalCtx, EnTrt* this);
void func_80A8C488(EnTrt* this, GlobalContext* globalCtx);
void func_80A8C64C(EnTrt* this, GlobalContext* globalCtx);
void func_80A8BD28(GlobalContext* globalCtx, EnTrt* this, u8 skipHello);
void func_80A8DAAC(EnTrt* this, GlobalContext* globalCtx);
void func_80A8D880(EnTrt* this, GlobalContext* globalCtx);
void func_80A8C8A0(EnTrt* this, GlobalContext* globalCtx);
s32 func_80A8C6CC(EnTrt* this, GlobalContext* globalCtx);
u8 func_80A8BEF4(EnTrt* this, u8 shelfOffset);
void func_80A8BB8C(GlobalContext* globalCtx, EnTrt* this);
void func_80A8C564(EnTrt* this, GlobalContext* globalCtx);
void func_80A8E92C(EnTrt* this);
void func_80A8D9CC(EnTrt* this, GlobalContext* globalCtx);
void func_80A8B9B8(GlobalContext* globalCtx, EnTrt* this);
void func_80A8CB0C(EnTrt* this, GlobalContext* globalCtx);
u16 func_80A8BAF8(EnTrt* this);
void func_80A8EB4C(GlobalContext* globalCtx, EnTrt* this);
void func_80A8E830(EnTrt* this);
void func_80A8E0D0(EnTrt* this, GlobalContext* globalCtx);
void func_80A8DBBC(EnTrt* this, GlobalContext* globalCtx);
s32 func_80A8E3CC(EnTrt* this);
s32 func_80A8CA2C(GlobalContext* globalCtx, EnTrt* this, Input* input);
void func_80A8C98C(GlobalContext* globalCtx, EnTrt* this);
void func_80A8E9A4(EnTrt* this, GlobalContext* globalCtx);
void func_80A8E30C(EnTrt* this);
s32 func_80A8B80C(GlobalContext* globalCtx);
u16 func_80A8BB3C(EnTrt* this);
void func_80A8CEE8(EnTrt* this, GlobalContext* globalCtx);
void func_80A8EB9C(GlobalContext* globalCtx, EnTrt* this);
void func_80A8BFE0(EnTrt* this, GlobalContext* globalCtx);
void func_80A8C1E8(EnTrt* this, GlobalContext* globalCtx);
s32 func_80A8E330(EnTrt* this);
s32 func_80A8BCD4(EnTrt* this, GlobalContext* globalCtx, Input* input);
void func_80A8CD2C(GlobalContext* globalCtx, EnTrt* this);
void func_80A8CCB4(GlobalContext* globalCtx, EnTrt* this, u16 textId);
void func_80A8CBFC(GlobalContext* globalCtx, EnTrt* this);
void func_80A8EBD8(EnTrt* this, GlobalContext* globalCtx);
void func_80A8BA3C(EnTrt* this);
void func_80A8C168(EnTrt* this, GlobalContext* globalCtx);
void func_80A8CCF0(GlobalContext* globalCtx, EnTrt* this, u16 textId);
void func_80A8DEBC(EnTrt* this, GlobalContext* globalCtx);
void func_80A8DFBC(EnTrt* this, GlobalContext* globalCtx);
void func_80A8E02C(EnTrt* this, GlobalContext* globalCtx);
void func_80A8DF20(EnTrt* this, GlobalContext* globalCtx);
void func_80A8BDD0(GlobalContext* globalCtx, EnTrt* this);
void func_80A8E458(EnTrt* this);
void func_80A8E5A4(EnTrt* this);
void func_80A8E4D8(EnTrt* this);
void func_80A8F8C4(EnTrt* this, GlobalContext* globalCtx);
void func_80A8B964(EnTrt* this, GlobalContext* globalCtx);
s32 func_80A8FB34(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80A8FBB4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_80A8FA00(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4);
void func_80A8FC64(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx);
void func_80A8EFF8(GlobalContext* globalCtx, EnTrt* this, f32 x, f32 y, f32 z, u8 drawCursor);
void func_80A8F404(GlobalContext* globalCtx, EnTrt* this);
void func_80A8F268(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t, f32 dx,
                   f32 dy);

void func_80A8E26C(EnTrt* this);

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
extern UNK_TYPE D_0600B0B8;
extern UNK_TYPE D_0600B8B8;
extern UNK_TYPE D_0600C0B8;

static ActorAnimationEntryS D_80A8FE10[] = {
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

static f32 D_80A8FED0 = 0.008f;

static ShopItem D_80A8FED4[3] = {
    { SI_POTION_RED_1, 24, 32, -36 },
    { SI_POTION_GREEN_1, 6, 32, -36 },
    { SI_POTION_BLUE, -12, 32, -36 },
};

static f32 D_80A8FEEC = 6.0f;
static f32 D_80A8FEF0 = 35.0f;
static f32 D_80A8FEF4 = -12.0f;

static InitChainEntry D_80A8FEF8[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

void func_80A8B770(SkelAnime* skelAnime, ActorAnimationEntryS* animations, s32 idx) {
    f32 frameCount;

    animations += idx;
    if (animations->frameCount < 0) {
        frameCount = SkelAnime_GetFrameCount(&animations->animationSeg->common);
    } else {
        frameCount = animations->frameCount;
    }
    SkelAnime_ChangeAnim(skelAnime, animations->animationSeg, animations->playbackSpeed, animations->frame, frameCount,
                         animations->mode, animations->transitionRate);
}

s32 func_80A8B80C(GlobalContext* globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A);
    }
    return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CUP);
}

void func_80A8B88C(EnTrt* this, GlobalContext* globalCtx, ShopItem* shopItem) {
    s32 i;

    for (i = 0; i < 3; i++, shopItem++) {
        if (shopItem->shopItemId < 0) {
            this->items[i] = NULL;
        } else if (shopItem->shopItemId < 0) {
            this->items[i] = NULL;
        } else {
            this->items[i] = (EnGirlA*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA, shopItem->x,
                                                   shopItem->y, shopItem->z, 0, 0, 0, shopItem->shopItemId);
        }
    }
}

void func_80A8B964(EnTrt* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A8B9B8(GlobalContext* globalCtx, EnTrt* this) {
    s16 x;
    s16 y;
    f32 xOffset = 0.0f;
    f32 yOffset = 17.0f;

    func_800B8898(globalCtx, &this->items[this->cursorIdx]->actor, &x, &y);
    this->cursorX = x + xOffset;
    this->cursorY = y + yOffset;
    this->cursorZ = 1.2f;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8B9B8.asm")
#endif

void func_80A8BA3C(EnTrt* this) {
    if (this->cutsceneState == 3) {
        if (this->cutscene != this->unk3E2) {
            ActorCutscene_Stop(this->cutscene);
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk3E2;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = 1;
        }
    }
    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

u16 func_80A8BAF8(EnTrt* this) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (item->actor.params == SI_POTION_BLUE && !(this->unk42C & 2)) {
        return 0x880;
    }
    return item->actor.textId;
}

u16 func_80A8BB3C(EnTrt* this) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (item->actor.params == SI_POTION_BLUE && !(gSaveContext.weekEventReg[53] & 0x10)) {
        this->unk406 = 0x881;
        return 0x881;
    }
    return item->choiceTextId;
}

void func_80A8BB8C(GlobalContext* globalCtx, EnTrt* this) {
    Player* player = PLAYER;

    if (this->cutsceneState == 3) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = 0;
    }
    func_800B84D0(&this->actor, globalCtx);
    globalCtx->msgCtx.unk11F22 = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = false;
    player->stateFlags2 &= ~0x20000000;
    globalCtx->interfaceCtx.unk222 = 0;
    globalCtx->interfaceCtx.unk224 = 0;
    this->unk406 = 0x834;
    this->unk402 = 0x50;
    this->unk42C |= 1;
    this->unk332 = 0xA;
    this->actor.textId = 0;
    this->actionFunc = func_80A8D094;
    this->blinkFunc = func_80A8E830;
}

s32 func_80A8BC8C(EnTrt* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        func_80A8BB8C(globalCtx, this);
        return true;
    }
    return false;
}

s32 func_80A8BCD4(EnTrt* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, func_80A8BAF8(this));
        return true;
    }
    return false;
}

void func_80A8BD28(GlobalContext* globalCtx, EnTrt* this, u8 skipHello) {
    func_8011552C(globalCtx, 0x10);
    if (!skipHello) {
        this->actionFunc = func_80A8BF24;
    } else {
        func_80A8BD7C(globalCtx, this);
    }
}

void func_80A8BD7C(GlobalContext* globalCtx, EnTrt* this) {
    func_80151938(globalCtx, 0x83E);
    func_8011552C(globalCtx, 6);
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = true;
    this->actionFunc = func_80A8C74C;
}

void func_80A8BDD0(GlobalContext* globalCtx, EnTrt* this) {
    Input* controller1 = &globalCtx->state.input[0];
    s8 stickX = controller1->rel.stick_x;
    s8 stickY = controller1->rel.stick_y;

    if (this->stickAccumX == 0) {
        if (stickX > 30 || stickX < -30) {
            this->stickAccumX = stickX;
        }
    } else if (stickX <= 30 && stickX >= -30) {
        this->stickAccumX = 0;
    } else {
        if ((this->stickAccumX * stickX) < 0) { // Stick has swapped directions
            this->stickAccumX = stickX;
        } else {
            this->stickAccumX += stickX;
            if (this->stickAccumX > 2000) {
                this->stickAccumX = 2000;
            } else if (this->stickAccumX < -2000) {
                this->stickAccumX = -2000;
            }
        }
    }
    if (this->stickAccumY == 0) {
        if (stickY > 30 || stickY < -30) {
            this->stickAccumY = stickY;
        }
    } else {
        if (stickY <= 30 && stickY >= -30) {
            this->stickAccumY = 0;
        } else {
            if ((this->stickAccumY * stickY) < 0) { // Stick has swapped directions
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
    }
}

u8 func_80A8BEF4(EnTrt* this, u8 shelfOffset) {
    if (this->items[shelfOffset] != NULL) {
        return shelfOffset;
    }
    return 0xFF;
}

void func_80A8BF24(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 3;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (talkState == 5 && func_80147624(globalCtx)) {
        play_sound(NA_SE_SY_MESSAGE_PASS);
        if (!func_80A8BC8C(this, globalCtx, globalCtx->state.input)) {
            func_80A8BD7C(globalCtx, this);
        }
    }
}

void func_80A8BFE0(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = PLAYER;

    this->unk3E2 = this->unk412;
    if (this->cutsceneState != 2) {
        func_80A8BA3C(this);
        if (this->cutsceneState == 2) {
            player->stateFlags2 &= ~0x20000000;
        }
    } else if (talkState == 5 && func_80147624(globalCtx)) {
        switch (this->unk406) {
            case 0x883:
                this->unk406 = 0x884;
                func_801518B0(globalCtx, this->unk406, &this->actor);
                gSaveContext.weekEventReg[53] |= 8;
                func_80123D50(globalCtx, PLAYER, 18, 21);
                break;
            case 0x888:
                this->unk406 = 0x889;
                func_801518B0(globalCtx, this->unk406, &this->actor);
                break;
            case 0x889:
                if (this->cutsceneState == 2) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = 0;
                }
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_80A8C168;
                break;
            default:
                this->cutsceneState = 3;
                func_80A8BB8C(globalCtx, this);
                break;
        }
    }
}

void func_80A8C168(EnTrt* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80123D50(globalCtx, PLAYER, 18, 21);
        this->actionFunc = func_80A8E02C;
    } else {
        func_800B8A1C(&this->actor, globalCtx, 4, 300.0f, 300.0f);
    }
}

void func_80A8C1E8(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        switch (this->unk406) {
            case 0x886:
                this->unk406 = 0x887;
                func_80151938(globalCtx, this->unk406);
                break;
            case 0x887:
            case 0x88B:
                func_80A8BB8C(globalCtx, this);
                break;
        }
    }
}

void func_80A8C288(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        if (this->unk406 == 0x88F) {
            if (func_80114E90() || !(gSaveContext.weekEventReg[12] & 0x10)) {
                if (this->cutsceneState == 3) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = 0;
                }
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_80A8C488;
            } else {
                this->unk408 = this->unk406;
                this->unk406 = 0x88E;
                gSaveContext.weekEventReg[85] |= 8;
                func_801518B0(globalCtx, this->unk406, &this->actor);
                this->actionFunc = func_80A8C64C;
            }
        } else {
            if (gSaveContext.weekEventReg[12] & 8) {
                this->unk406 = 0x83D;
                func_80A8BD28(globalCtx, this, 0);
            } else if (gSaveContext.weekEventReg[84] & 0x40) {
                this->unk406 = 0x83B;
                if (func_80114F2C(0x13)) {
                    func_80A8BD28(globalCtx, this, 0);
                } else {
                    this->actionFunc = func_80A8DAAC;
                }
            } else if (gSaveContext.weekEventReg[16] & 0x10) {
                this->unk402 = 0x1E;
                this->unk406 = 0x838;
                this->cutsceneState = 2;
                this->actionFunc = func_80A8D880;
                return;
            } else if (gSaveContext.weekEventReg[17] & 1) {
                this->unk406 = 0x835;
                func_80A8BD28(globalCtx, this, 0);
            }
            func_801518B0(globalCtx, this->unk406, &this->actor);
        }
    }
}

void func_80A8C488(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        if (!(gSaveContext.weekEventReg[12] & 0x10)) {
            gSaveContext.weekEventReg[12] |= 0x10;
        }
        gSaveContext.weekEventReg[84] |= 0x40;
        player->stateFlags2 &= ~0x20000000;
        this->actionFunc = func_80A8C564;
    } else if (gSaveContext.weekEventReg[12] & 0x10) {
        func_800B8A1C(&this->actor, globalCtx, 0x5B, 300.0f, 300.0f);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x59, 300.0f, 300.0f);
    }
}

// Unused?
void func_80A8C564(EnTrt* this, GlobalContext* globalCtx) {
    //! @bug: player is set to NULL not PLAYER
    Player* player = NULL;

    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
                ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
                player->stateFlags2 |= 0x20000000;
                //! @bug: func_80A8E0D0 will get overwritten by func_80A8DBBC
                this->actionFunc = func_80A8E0D0;
                this->cutsceneState = 3;
            } else {
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                }
                this->cutscene = this->unk410;
                ActorCutscene_SetIntentToPlay(this->cutscene);
            }
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
        this->actionFunc = func_80A8DBBC;
    }
}

void func_80A8C64C(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (talkState == 5) {
        if (func_80147624(globalCtx)) {
            func_80A8BB8C(globalCtx, this);
        }
    } else if (talkState == 6) {
        if (func_80147624(globalCtx)) {
            func_80A8BB8C(globalCtx, this);
        }
    }
}

s32 func_80A8C6CC(EnTrt* this, GlobalContext* globalCtx) {
    switch (globalCtx->msgCtx.choiceIndex) {
        case 0:
            func_8019F208();
            func_80A8EB4C(globalCtx, this);
            return true;
        case 1:
            func_8019F230();
            func_80A8BB8C(globalCtx, this);
            return true;
    }
    return false;
}

void func_80A8C74C(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    u8 cursorIdx;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 3;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->unk40C;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else {
        if (talkState == 4) {
            func_8011552C(globalCtx, 6);
            if (!func_80A8BC8C(this, globalCtx, globalCtx->state.input)) {
                if (!func_80147624(globalCtx) || !func_80A8C6CC(this, globalCtx)) {
                    if (this->stickAccumX > 0) {
                        cursorIdx = func_80A8BEF4(this, 2);
                        if (cursorIdx != 0xFF) {
                            this->cursorIdx = cursorIdx;
                            this->actionFunc = func_80A8C8A0;
                            func_8011552C(globalCtx, 6);
                            this->stickRightPrompt.isEnabled = false;
                            play_sound(NA_SE_SY_CURSOR);
                        }
                    }
                }
            }
        }
    }
}

void func_80A8C8A0(EnTrt* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 3) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = 0;
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->unk40E;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 3;
            func_80A8B9B8(globalCtx, this);
            this->actionFunc = func_80A8CB0C;
            func_80151938(globalCtx, func_80A8BAF8(this));
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void func_80A8C98C(GlobalContext* globalCtx, EnTrt* this) {
    u8 curTemp = this->cursorIdx;

    if (this->stickAccumX < 0) {
        if (curTemp != 2) {
            curTemp++;
        } else {
            func_80A8EB9C(globalCtx, this);
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

s32 func_80A8CA2C(GlobalContext* globalCtx, EnTrt* this, Input* input) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (func_80A8BC8C(this, globalCtx, input)) {
        return true;
    }
    if (func_80A8B80C(globalCtx)) {
        if (item->actor.params != SI_POTION_BLUE || (this->unk42C & 2)) {
            this->tmpActionFunc = this->actionFunc;
            func_80151938(globalCtx, func_80A8BB3C(this));
            play_sound(NA_SE_SY_DECIDE);
            this->stickLeftPrompt.isEnabled = false;
            this->stickRightPrompt.isEnabled = false;
            this->drawCursor = 0;
            this->actionFunc = func_80A8CEE8;
        } else {
            play_sound(NA_SE_SY_ERROR);
        }
        return true;
    }
    return false;
}

void func_80A8CB0C(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    u8 prevCursorIdx = this->cursorIdx;
    u8 cursorIdx;

    if (!func_80A8E3CC(this)) {
        this->delayTimer = 3;
    } else if (this->delayTimer != 0) {
        this->delayTimer--;
    } else {
        this->drawCursor = 0xFF;
        this->stickLeftPrompt.isEnabled = true;
        func_80A8B9B8(globalCtx, this);
        if (talkState == 5) {
            func_8011552C(globalCtx, 6);
            if (!func_80A8CA2C(globalCtx, this, globalCtx->state.input)) {
                func_80A8C98C(globalCtx, this);
                if (this->cursorIdx != prevCursorIdx) {
                    func_80151938(globalCtx, func_80A8BAF8(this));
                    play_sound(NA_SE_SY_CURSOR);
                }
            }
        }
    }
}

void func_80A8CBFC(GlobalContext* globalCtx, EnTrt* this) {
    Player* player = PLAYER;

    func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    globalCtx->msgCtx.unk11F22 = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    player->stateFlags2 &= ~0x20000000;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    this->actionFunc = func_80A8DFBC;
}

void func_80A8CCB4(GlobalContext* globalCtx, EnTrt* this, u16 textId) {
    func_80151938(globalCtx, textId);
    this->actionFunc = func_80A8DEBC;
}

void func_80A8CCF0(GlobalContext* globalCtx, EnTrt* this, u16 textId) {
    func_80151938(globalCtx, textId);
    this->actionFunc = func_80A8DF20;
}

#ifdef NON_MATCHING
// Matches but jmptable is in late rodata
void func_80A8CD2C(GlobalContext* globalCtx, EnTrt* this) {
    EnGirlA* item = this->items[this->cursorIdx];
    EnGirlA* item2;

    switch (item->canBuyFunc(globalCtx, item)) {
        case CANBUY_RESULT_SUCCESS_FANFARE:
            if (this->cutsceneState == 3) {
                ActorCutscene_Stop(this->cutscene);
                this->cutsceneState = 0;
            }
            func_8019F208();
            item2 = this->items[this->cursorIdx];
            item2->buyFanfareFunc(globalCtx, item2);
            func_80A8CBFC(globalCtx, this);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_SUCCESS:
            func_8019F208();
            item->buyFunc(globalCtx, item);
            func_80A8CCF0(globalCtx, this, 0x848);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_NO_ROOM:
            play_sound(NA_SE_SY_ERROR);
            func_80A8CCB4(globalCtx, this, 0x641);
            break;
        case CANBUY_RESULT_NEED_EMPTY_BOTTLE:
            play_sound(NA_SE_SY_ERROR);
            func_80A8CCB4(globalCtx, this, 0x846);
            break;
        case CANBUY_RESULT_NEED_RUPEES:
            play_sound(NA_SE_SY_ERROR);
            func_80A8CCB4(globalCtx, this, 0x847);
            break;
        case CANBUY_RESULT_CANNOT_GET_NOW:
            play_sound(NA_SE_SY_ERROR);
            func_80A8CCB4(globalCtx, this, 0x643);
            break;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8CD2C.asm")
#endif

void func_80A8CEE8(EnTrt* this, GlobalContext* globalCtx) {
    EnGirlA* item = this->items[this->cursorIdx];
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (func_80A8E330(this)) {
        if (talkState == 4) {
            func_8011552C(globalCtx, 6);
            if (!func_80A8BCD4(this, globalCtx, globalCtx->state.input) && func_80147624(globalCtx)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_80A8CD2C(globalCtx, this);
                        break;
                    case 1:
                        func_8019F230();
                        this->actionFunc = this->tmpActionFunc;
                        func_80151938(globalCtx, func_80A8BAF8(this));
                        break;
                }
            }
        } else if (talkState == 5 && func_80147624(globalCtx)) {
            if (!func_80114E90()) {
                play_sound(NA_SE_SY_ERROR);
                func_80A8CCB4(globalCtx, this, 0x846);
            } else {
                if (this->cutsceneState == 3) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = 0;
                }
                func_80A8CBFC(globalCtx, this);
                this->drawCursor = 0;
                this->shopItemSelectedTween = 0.0f;
                item->boughtFunc(globalCtx, item);
                gSaveContext.weekEventReg[53] |= 0x10;
            }
        }
    }
}

void func_80A8D094(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((gSaveContext.weekEventReg[85] & 8) && !(gSaveContext.weekEventReg[84] & 0x40)) {
        this->unk406 = 0x88F;
    } else if (!(this->unk42C & 4)) {
        this->unk406 = 0x834;
    } else {
        this->unk406 = 0x83E;
    }
    if (!(gSaveContext.weekEventReg[53] & 8)) {
        this->unk40A = 0x845;
    } else if (this->unk42C & 2) {
        this->unk40A = 0x882;
    } else {
        this->unk40A = 0x885;
    }
    this->unk408 = this->unk406;

    if (player->transformation == PLAYER_FORM_GORON || player->transformation == PLAYER_FORM_ZORA ||
        player->transformation == PLAYER_FORM_DEKU) {
        this->unk406 = 0x850;
    }
    if (Player_GetMask(globalCtx) == PLAYER_MASK_MASK_OF_SCENTS) {
        this->unk406 = 0x890;
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (player->transformation == PLAYER_FORM_HUMAN) {
            this->unk42C |= 4;
        }
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk40C;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = 1;
        }
        player->stateFlags2 |= 0x20000000;
        this->unk402 = 0x2D;
        this->actionFunc = func_80A8D5C8;
    } else {
        if ((player->actor.world.pos.x >= -50.0f && player->actor.world.pos.x <= -25.0f) &&
            (player->actor.world.pos.z >= -19.0f && player->actor.world.pos.z <= 30.0f)) {
            func_800B8614(&this->actor, globalCtx, 200.0f);
        }
    }
    if (DECR(this->unk402) == 0) {
        this->unk402 = 40;
        func_80A8B770(&this->skelAnime, D_80A8FE10, 1);
        this->unk404 = 1;
        this->actionFunc = func_80A8D380;
        this->blinkFunc = func_80A8E890;
    }
    if (DECR(this->unk332) == 0) {
        func_800B9010(&this->actor, NA_SE_EN_KOTAKE_SLEEP - SFX_FLAG);
    }
}

void func_80A8D380(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->unk42C &= ~1;
    if (player->transformation == PLAYER_FORM_HUMAN || player->transformation == PLAYER_FORM_FIERCE_DEITY) {
        if (Player_GetMask(globalCtx) == PLAYER_MASK_MASK_OF_SCENTS) {
            this->unk406 = 0x890;
        } else {
            this->unk406 = this->unk408;
        }
    } else {
        this->unk406 = 0x850;
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk40C;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = 1;
        }
        player->stateFlags2 |= 0x20000000;
        if (player->transformation == PLAYER_FORM_HUMAN) {
            this->unk42C |= 4;
        }
        func_80A8B770(&this->skelAnime, D_80A8FE10, 2);
        this->blinkFunc = func_80A8E91C;
        this->unk402 = 45;
        this->actionFunc = func_80A8D5C8;
    } else {
        if ((player->actor.world.pos.x >= -50.0f && player->actor.world.pos.x <= -25.0f) &&
            (player->actor.world.pos.z >= -19.0f && player->actor.world.pos.z <= 30.0f)) {
            func_800B8614(&this->actor, globalCtx, 200.0f);
        }
    }
    if (DECR(this->unk402) == 0) {
        this->unk402 = Rand_S16Offset(150, 100);
        func_80A8B770(&this->skelAnime, D_80A8FE10, 2);
        this->unk404 = 2;
        this->unk332 = 0xA;
        this->actor.textId = 0;
        this->actionFunc = func_80A8D094;
        this->blinkFunc = func_80A8E91C;
    }
}

void func_80A8D5C8(EnTrt* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.animCurrentFrame / this->skelAnime.animPlaybackSpeed;
    s16 sp28 = SkelAnime_GetFrameCount(&D_060030EC.common) / (s16)this->skelAnime.animPlaybackSpeed;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    } else if (this->cutsceneState == 2) {
        if (this->unk404 != 5) {
            if (sp26 == sp28) {
                func_80A8B770(&this->skelAnime, D_80A8FE10, 3);
                this->unk404 = 3;
                this->blinkFunc = func_80A8E94C;
                this->unk402 = 0xA;
                this->cutsceneState = 3;
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_KOTAKE_SURPRISED2);
            }
        } else {
            this->blinkFunc = func_80A8E94C;
            this->unk402 = 0xA;
            this->cutsceneState = 3;
        }
    } else {
        if (DECR(this->unk402) == 0) {
            this->unk402 = Rand_S16Offset(40, 20);
            func_80A8B770(&this->skelAnime, D_80A8FE10, 5);
            func_801518B0(globalCtx, this->unk406, &this->actor);
            this->unk404 = 5;
            switch (this->unk406) {
                case 0x834:
                    if (!(gSaveContext.weekEventReg[12] & 8) && !(gSaveContext.weekEventReg[84] & 0x40) &&
                        !(gSaveContext.weekEventReg[16] & 0x10) && !(gSaveContext.weekEventReg[17] & 1)) {
                        func_8011552C(globalCtx, 6);
                        this->stickLeftPrompt.isEnabled = false;
                        this->stickRightPrompt.isEnabled = true;
                        this->actionFunc = func_80A8BF24;
                    } else {
                        this->actionFunc = func_80A8C288;
                    }
                    break;
                case 0x83E:
                    func_8011552C(globalCtx, 6);
                    this->stickLeftPrompt.isEnabled = false;
                    this->stickRightPrompt.isEnabled = true;
                    this->actionFunc = func_80A8C74C;
                    break;
                case 0x850:
                case 0x890:
                    this->actionFunc = func_80A8DD10;
                    break;
                case 0x88F:
                    this->actionFunc = func_80A8C288;
                    break;
            }
        }
    }
}

void func_80A8D880(EnTrt* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    } else if (this->cutsceneState == 2) {
        if (DECR(this->unk402) == 0) {
            func_80A8B770(&this->skelAnime, D_80A8FE10, 4);
            this->unk404 = 4;
            this->blinkFunc = func_80A8E92C;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_KOTAKE_SURPRISED);
            this->unk402 = 30;
            this->cutsceneState = 3;
        }
    } else {
        if (DECR(this->unk402) == 0) {
            this->unk402 = Rand_S16Offset(40, 20);
            func_80A8B770(&this->skelAnime, D_80A8FE10, 5);
            func_801518B0(globalCtx, this->unk406, &this->actor);
            this->unk404 = 5;
            this->actionFunc = func_80A8D9CC;
        }
    }
}

void func_80A8D9CC(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    this->blinkFunc = func_80A8E79C;
    if (talkState == 6 && func_80147624(globalCtx)) {
        if (func_80114E90() || !(gSaveContext.weekEventReg[12] & 0x10)) {
            if (this->cutsceneState == 3) {
                ActorCutscene_Stop(this->cutscene);
                this->cutsceneState = 0;
            }
            this->actionFunc = func_80A8C488;
        } else {
            this->unk408 = this->unk406;
            this->unk406 = 0x88E;
            gSaveContext.weekEventReg[85] |= 8;
            func_801518B0(globalCtx, this->unk406, &this->actor);
            this->actionFunc = func_80A8C64C;
        }
    }
}

void func_80A8DAAC(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        if (this->unk406 == 0x83C) {
            if (func_80114E90()) {
                if (this->cutsceneState == 3) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = 0;
                }
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                this->actionFunc = func_80A8C488;
            } else {
                this->unk408 = this->unk406;
                this->unk406 = 0x88E;
                gSaveContext.weekEventReg[85] |= 8;
                func_801518B0(globalCtx, this->unk406, &this->actor);
                this->actionFunc = func_80A8C64C;
            }
        } else {
            this->unk406 = 0x83C;
            func_801518B0(globalCtx, this->unk406, &this->actor);
        }
    }
}

void func_80A8DBBC(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, (Actor*)this);
            player->stateFlags2 |= 0x20000000;
            this->actionFunc = func_80A8E0D0;
            this->cutsceneState = 3;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk410;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        switch (this->unk406) {
            case 0x889:
                this->unk406 = 0x88A;
                break;
            case 0x881:
                this->unk406 = 0x88C;
                break;
            case 0x838:
            case 0x83C:
            case 0x88E:
            case 0x88F:
                this->unk406 = 0x83A;
                break;
            default:
                if (1) {}
                this->unk406 = 0x849;
                break;
        }
        func_80151938(globalCtx, this->unk406);
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80A8DD10(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        func_80A8BB8C(globalCtx, this);
    }
}

void func_80A8DD60(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = PLAYER;

    if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, this->unk406, &this->actor);
    } else {
        if ((player->actor.world.pos.x >= -50.0f && player->actor.world.pos.x <= 50.0f) &&
            (player->actor.world.pos.z >= -19.0f && player->actor.world.pos.z <= 30.0f)) {
            func_800B8614(&this->actor, globalCtx, 200.0f);
        }
    }
    if (talkState == 6 && func_80147624(globalCtx)) {
        if (gSaveContext.weekEventReg[20] & 2) {
            globalCtx->nextEntranceIndex = 0xC50;
        } else {
            globalCtx->nextEntranceIndex = 0x8450;
        }
        globalCtx->unk1887F = 0x40;
        gSaveContext.nextTransition = 0x40;
        globalCtx->unk18875 = 0x14;
    }
}

void func_80A8DEBC(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, func_80A8BAF8(this));
    }
}

void func_80A8DF20(EnTrt* this, GlobalContext* globalCtx) {
    EnGirlA* item;

    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->shopItemSelectedTween = 0.0f;
        func_80A8E30C(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, func_80A8BAF8(this));
    }
}

void func_80A8DFBC(EnTrt* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80A8E02C;
    } else {
        func_800B8A1C((Actor*)this, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    }
}

void func_80A8E02C(EnTrt* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        this->actionFunc = func_80A8DBBC;
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk410;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80A8E0D0(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = PLAYER;
    EnGirlA* item;

    if (talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (func_80147624(globalCtx)) {
            func_80A8E30C(this);
            item = this->items[this->cursorIdx];
            item->restockFunc(globalCtx, item);
            if (!func_80A8BC8C(this, globalCtx, globalCtx->state.input)) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_8019F208();
                        player->actor.shape.rot.y += 0x8000;
                        player->stateFlags2 |= 0x20000000;
                        func_801518B0(globalCtx, this->unk406, &this->actor);
                        func_80A8BD28(globalCtx, this, true);
                        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
                        break;
                    case 1:
                    default:
                        func_8019F230();
                        func_80A8BB8C(globalCtx, this);
                        break;
                }
            }
        }
    } else if (talkState == 5) {
        if (func_80147624(globalCtx)) {
            func_80A8E30C(this);
            item = this->items[this->cursorIdx];
            item->restockFunc(globalCtx, item);
            func_80A8BB8C(globalCtx, this);
        }
    }
}

#ifdef NON_MATCHING
// Extra lui
void func_80A8E26C(EnTrt* this) {
    u8 i = this->cursorIdx;
    EnGirlA* item;
    ShopItem* shopItem;
    Vec3f worldPos;

    shopItem = &D_80A8FED4[i];
    item = this->items[i];

    worldPos.x = shopItem->x + (D_80A8FEEC - shopItem->x) * this->shopItemSelectedTween;
    worldPos.y = shopItem->y + (D_80A8FEF0 - shopItem->y) * this->shopItemSelectedTween;
    worldPos.z = shopItem->z + (D_80A8FEF4 - shopItem->z) * this->shopItemSelectedTween;

    item->actor.world.pos.x = worldPos.x;
    item->actor.world.pos.y = worldPos.y;
    item->actor.world.pos.z = worldPos.z;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E26C.asm")
#endif

void func_80A8E30C(EnTrt* this) {
    this->shopItemSelectedTween = 0.0f;
    func_80A8E26C(this);
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
// Returns true when animation has completed
s32 func_80A8E330(EnTrt* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 1.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween >= 0.85f) {
        this->shopItemSelectedTween = 1.0f;
    }
    func_80A8E26C(this);
    if (this->shopItemSelectedTween == 1.0f) {
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E330.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in laterodata
// returns true if animation has completed
s32 func_80A8E3CC(EnTrt* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 0.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween <= 0.15f) {
        this->shopItemSelectedTween = 0.0f;
    }
    func_80A8E26C(this);
    if (this->shopItemSelectedTween == 0.0f) {
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E3CC.asm")
#endif

void func_80A8E458(EnTrt* this) {
    EnGirlA** items = this->items;
    EnGirlA* item;
    s32 i;

    for (i = 0; i < 3; i++, items++) {
        item = *items;
        if (item != NULL) {
            if (this->actionFunc != func_80A8CEE8 && this->actionFunc != func_80A8DEBC && this->drawCursor == 0) {
                item->isSelected = false;
            } else {
                item->isSelected = this->cursorIdx == i ? true : false;
            }
        }
    }
}

#ifdef NON_MATCHING
// Matches but floats are in laterodata
void func_80A8E4D8(EnTrt* this) {
    f32 t;

    t = this->cursorAnimTween;
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
    this->cursorColorR = ColChanMix(0, 0.0f, t);
    this->cursorColorG = ColChanMix(80, 80.0f, t);
    this->cursorColorB = ColChanMix(255, 0.0f, t);
    this->cursorColorA = ColChanMix(255, 0.0f, t);
    this->cursorAnimTween = t;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E4D8.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A8E5A4(EnTrt* this) {
    f32 arrowAnimTween = this->arrowAnimTween;
    f32 stickAnimTween = this->stickAnimTween;

    // Possbily fake temps
    s32 new_var2 = 255;
    f32 new_var3;

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

    new_var3 = 155.0f * arrowAnimTween;

    this->stickAnimTween = stickAnimTween;

    this->stickLeftPrompt.arrowColorR = ColChanMix(255, 155.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColorG = ColChanMix(new_var2, 155.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColorB = ColChanMix(0, -100, arrowAnimTween);
    this->stickLeftPrompt.arrowColorA = ColChanMix(200, 50.0f, arrowAnimTween);

    this->stickRightPrompt.arrowColorR = (new_var2 - ((s32)new_var3)) & 0xFF;
    this->stickRightPrompt.arrowColorG = (255 - ((s32)new_var3)) & 0xFF;
    this->stickRightPrompt.arrowColorB = ColChanMix(0, -100.0f, arrowAnimTween);
    this->stickRightPrompt.arrowColorA = ColChanMix(200, 50.0f, arrowAnimTween);

    this->stickRightPrompt.arrowTexX = 290.0f;
    this->stickLeftPrompt.arrowTexX = 33.0f;

    this->stickRightPrompt.stickTexX = 274.0f;
    this->stickRightPrompt.stickTexX += 8.0f * stickAnimTween;
    this->stickLeftPrompt.stickTexX = 49.0f;
    this->stickLeftPrompt.stickTexX -= 8.0f * stickAnimTween;

    this->stickLeftPrompt.arrowTexY = this->stickRightPrompt.arrowTexY = 91.0f;
    this->stickLeftPrompt.stickTexY = this->stickRightPrompt.stickTexY = 95.0f;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8E5A4.asm")
#endif

void func_80A8E754(EnTrt* this) {
    if (this->eyeTextureIdx <= 0) {
        this->eyeTextureIdx = 0;
    } else {
        this->eyeTextureIdx--;
    }
}

void func_80A8E774(EnTrt* this) {
    if (this->eyeTextureIdx >= 2) {
        this->eyeTextureIdx = 2;
    } else {
        this->eyeTextureIdx++;
    }
}

void func_80A8E79C(EnTrt* this) {
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

void func_80A8E830(EnTrt* this) {
    s16 decr;
    s16 eyeTextureIdxTemp;

    decr = this->blinkTimer - 1;
    if (decr != 0) {
        this->blinkTimer = decr;
        return;
    }
    eyeTextureIdxTemp = this->eyeTextureIdx + 1;
    if (eyeTextureIdxTemp >= 3) {
        this->eyeTextureIdx = 1;
        this->blinkTimer = 20;
    } else {
        this->eyeTextureIdx = eyeTextureIdxTemp;
        this->blinkTimer = 3;
    }
}

void func_80A8E890(EnTrt* this) {
    if (this->skelAnime.animCurrentFrame >= 40.0f) {
        func_80A8E774(this);
    } else if (this->skelAnime.animCurrentFrame >= 35.0f) {
        this->eyeTextureIdx = 1;
    } else if (this->skelAnime.animCurrentFrame >= 10.0f) {
        func_80A8E754(this);
    }
}

void func_80A8E91C(EnTrt* this) {
    this->eyeTextureIdx = 2;
}

void func_80A8E92C(EnTrt* this) {
    func_80A8E754(this);
}

void func_80A8E94C(EnTrt* this) {
    if (this->skelAnime.animCurrentFrame >= 7.0f) {
        func_80A8E754(this);
        if (this->eyeTextureIdx == 0) {
            this->blinkFunc = func_80A8E79C;
        }
    }
}

void func_80A8E9A4(EnTrt* this, GlobalContext* globalCtx) {
    u8 talkState = talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = PLAYER;
    s32 func80123810ret;

    if (talkState == 5) {
        if (func_80147624(globalCtx)) {
            if (this->unk40A == 0x845 || this->unk40A == 0x882) {
                func_80151938(globalCtx, 0xFF);
            } else {
                func_80A8BD7C(globalCtx, this);
            }
        }
    } else if (talkState == 16) {
        func80123810ret = func_80123810(globalCtx);
        if (func80123810ret > 0) {
            if (func80123810ret == 0x1E) {
                if (gSaveContext.weekEventReg[53] & 8) {
                    player->actor.textId = 0x888;
                } else {
                    player->actor.textId = 0x883;
                }
                this->unk406 = player->actor.textId;
                player->unk_A87 = func80123810ret;
                this->actionFunc = func_80A8BFE0;
            } else {
                if (this->unk42C & 2) {
                    player->actor.textId = 0x88B;
                } else {
                    player->actor.textId = 0x886;
                }
                this->unk406 = player->actor.textId;
                this->actionFunc = func_80A8C1E8;
            }
            func_801477B4(globalCtx);
        } else if (func80123810ret < 0) {
            if (this->unk42C & 2) {
                this->unk406 = 0x88B;
            } else {
                this->unk406 = 0x886;
            }
            func_801518B0(globalCtx, this->unk406, &this->actor);
            this->actionFunc = func_80A8C1E8;
        }
    }
}

void func_80A8EB4C(GlobalContext* globalCtx, EnTrt* this) {
    this->actionFunc = func_80A8E9A4;
    func_80151938(globalCtx, this->unk40A);
    func_8011552C(globalCtx, 6);
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = false;
}

void func_80A8EB9C(GlobalContext* globalCtx, EnTrt* this) {
    play_sound(NA_SE_SY_CURSOR);
    this->drawCursor = 0;
    this->actionFunc = func_80A8EBD8;
}

void func_80A8EBD8(EnTrt* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 3) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = 0;
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->unk410;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 3;
            func_80A8BD7C(globalCtx, this);
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void func_80A8ECA4(EnTrt* this, GlobalContext* globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600FEF0, &D_0600FD34, NULL, NULL, 0);
    if (!(gSaveContext.weekEventReg[12] & 8) && !(gSaveContext.weekEventReg[84] & 0x40) && gSaveContext.day >= 2) {
        this->actor.draw = NULL;
    } else {
        this->actor.draw = EnTrt_Draw;
    }
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A8ED3C(EnTrt* this, GlobalContext* globalCtx) {
    u32 maxcolor = 0xFF;
    EnTrt* this2;

    func_80A8EFA4(this, globalCtx);
    this->cutscene = this->unk40C;
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    func_80A8ECA4(this, globalCtx);
    this->actor.colChkInfo.mass = 0xFF;
    this->actor.colChkInfo.cylRadius = 50;
    this->unk402 = Rand_S16Offset(40, 20);
    if (!(gSaveContext.weekEventReg[12] & 8) && !(gSaveContext.weekEventReg[84] & 0x40) && gSaveContext.day >= 2) {
        this->unk406 = 0x84A;
        this->actionFunc = func_80A8DD60;
    } else {
        this->unk332 = 0xA;
        this->actor.textId = 0;
        this->actionFunc = func_80A8D094;
    }

    this->stickAccumY = 0;
    this->stickAccumX = 0;
    this->cursorIdx = 0;
    this->cursorY = this->cursorX = 100.0f;
    this->cursorZ = 1.2f;
    this->cursorColorR = 0;
    this->cursorColorG = 80;
    this->cursorColorB = maxcolor;
    this->cursorColorA = maxcolor;
    this->cursorAnimTween = 0.0f;
    this->cursorAnimState = 0;
    this->drawCursor = 0;

    this2 = this;

    this->stickLeftPrompt.stickColorR = 200;
    this2->stickLeftPrompt.stickColorG = 200;
    this2->stickLeftPrompt.stickColorB = 200;
    this2->stickLeftPrompt.stickColorA = 180;
    this2->stickLeftPrompt.stickTexX = 49.0f;
    this2->stickLeftPrompt.stickTexY = 95.0f;
    this2->stickLeftPrompt.arrowColorR = maxcolor;
    this2->stickLeftPrompt.arrowColorG = maxcolor;
    this2->stickLeftPrompt.arrowColorB = 0;
    this2->stickLeftPrompt.arrowColorA = 200;
    this2->stickLeftPrompt.arrowTexX = 33.0f;
    this2->stickLeftPrompt.arrowTexY = 91.0f;
    this2->stickLeftPrompt.texZ = 1.0f;
    this2->stickLeftPrompt.isEnabled = false;

    if (1) {}

    this2->stickRightPrompt.stickColorR = 200;
    this2->stickRightPrompt.stickColorG = 200;
    this2->stickRightPrompt.stickColorB = 200;
    this2->stickRightPrompt.stickColorA = 180;
    this2->stickRightPrompt.stickTexX = 274.0f;
    this2->stickRightPrompt.stickTexY = 95.0f;
    this2->stickRightPrompt.arrowColorR = maxcolor;
    this2->stickRightPrompt.arrowColorG = 0;
    this2->stickRightPrompt.arrowColorB = 0;
    this2->stickRightPrompt.arrowColorA = 200;
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
    Actor_SetScale(&this->actor, D_80A8FED0);
    func_80A8B88C(this, globalCtx, D_80A8FED4);
    this->blinkTimer = 20;
    this->eyeTextureIdx = 0;
    this->blinkFunc = func_80A8E91C;
    if (gSaveContext.weekEventReg[53] & 8) {
        this->unk42C |= 2;
    }

    this->actor.flags &= ~1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8ED3C.asm")
#endif

void func_80A8EFA4(EnTrt* this, GlobalContext* globalCtx) {
    this->unk40C = this->actor.cutscene;
    this->unk40E = ActorCutscene_GetAdditionalCutscene(this->unk40C);
    this->unk410 = ActorCutscene_GetAdditionalCutscene(this->unk40E);
    this->unk412 = ActorCutscene_GetAdditionalCutscene(this->unk410);
}

void func_80A8EFF8(GlobalContext* globalCtx, EnTrt* this, f32 x, f32 y, f32 z, u8 drawCursor) {
    s32 ulx, uly, lrx, lry;
    f32 w;
    s32 dsdx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (drawCursor != 0) {
        func_8012C654(globalCtx->state.gfxCtx);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, this->cursorColorR, this->cursorColorG, this->cursorColorB,
                        this->cursorColorA);
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

void func_80A8F268(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t, f32 dx,
                   f32 dy) {
    f32 unk;
    s32 ulx, uly, lrx, lry;
    f32 w, h;
    s32 dsdx, dtdy;

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

void func_80A8F404(GlobalContext* globalCtx, EnTrt* this) {
    s32 drawStickRightPrompt = this->stickLeftPrompt.isEnabled;
    s32 drawStickLeftPrompt = this->stickRightPrompt.isEnabled;

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
            func_80A8F268(globalCtx, this->stickLeftPrompt.arrowColorR, this->stickLeftPrompt.arrowColorG,
                          this->stickLeftPrompt.arrowColorB, this->stickLeftPrompt.arrowColorA,
                          this->stickLeftPrompt.arrowTexX, this->stickLeftPrompt.arrowTexY, this->stickLeftPrompt.texZ,
                          0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_80A8F268(globalCtx, this->stickRightPrompt.arrowColorR, this->stickRightPrompt.arrowColorG,
                          this->stickRightPrompt.arrowColorB, this->stickRightPrompt.arrowColorA,
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
            func_80A8F268(globalCtx, this->stickLeftPrompt.stickColorR, this->stickLeftPrompt.stickColorG,
                          this->stickLeftPrompt.stickColorB, this->stickLeftPrompt.stickColorA,
                          this->stickLeftPrompt.stickTexX, this->stickLeftPrompt.stickTexY, this->stickLeftPrompt.texZ,
                          0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_80A8F268(globalCtx, this->stickRightPrompt.stickColorR, this->stickRightPrompt.stickColorG,
                          this->stickRightPrompt.stickColorB, this->stickRightPrompt.stickColorA,
                          this->stickRightPrompt.stickTexX, this->stickRightPrompt.stickTexY,
                          this->stickRightPrompt.texZ, 0, 0, 1.0f, 1.0f);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnTrt_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80A8FEF8);
    func_80A8ED3C(this, globalCtx);
}

void EnTrt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt* this = THIS;

    SkelAnime_Free(&this->skelAnime, globalCtx);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTrt_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTrt* this = THIS;

    this->blinkFunc(this);
    func_80A8BDD0(globalCtx, this);
    func_80A8E458(this);
    func_80A8E5A4(this);
    func_80A8E4D8(this);
    func_80A8F8C4(this, globalCtx);
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, 90.0f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80A8B964(this, globalCtx);
}

void func_80A8F8C4(EnTrt* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f playerPos;
    Vec3f pos;

    Math_SmoothStepToS(&this->unk42A, this->actor.yawTowardsPlayer - this->actor.shape.rot.y, 4, 0x38E0, 1);
    this->unk42A = CLAMP(this->unk42A, -0x38E0, 0x38E0);

    playerPos = player->actor.world.pos;
    playerPos.y = player->bodyPartsPos[7].y + 3.0f;
    pos = this->actor.world.pos;
    Math_SmoothStepToS(&this->unk428, Math_Vec3f_Pitch(&pos, &playerPos), 4, 0x1C70, 1);
    this->unk428 = CLAMP(this->unk428, -0x1C70, 0x1C70);
}

void func_80A8FA00(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4) {
    Vec3f sp7C;
    Vec3f sp70 = D_801D15B0;
    Vec3s sp68;
    MtxF sp28;

    SysMatrix_MultiplyVector3fByState(&sp70, &sp7C);
    SysMatrix_CopyCurrentState(&sp28);
    func_8018219C(&sp28, &sp68, MTXMODE_NEW);
    *arg2 = sp7C;
    if (arg4 != 0) {
        sp68.x += arg0;
        sp68.y += arg1;
        Math_SmoothStepToS(&arg3->x, sp68.x, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&arg3->y, sp68.y, 4, 0x1FFE, 1);
        Math_SmoothStepToS(&arg3->z, sp68.z, 4, 0x1FFE, 1);
    } else {
        arg3->x = sp68.x;
        arg3->y = sp68.y;
        arg3->z = sp68.z;
    }
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8FA00.asm")

#ifdef NON_MATCHING
// Matched but floats are in late rodata
s32 func_80A8FB34(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTrt* this = THIS;
    s32 i;

    for (i = 0; i < 3; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }

    if (limbIndex == 14) {
        *dList = NULL;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8FB34.asm")
#endif

void func_80A8FBB4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTrt* this = THIS;
    s32 phi_v0;

    phi_v0 = 0;
    if (this->unk42C & 1) {
        phi_v0 = 1;
    }
    if (limbIndex == 21) {
        func_80A8FA00(this->unk428, this->unk42A, &this->unk41C, &this->unk416, phi_v0);
        SysMatrix_InsertTranslation(this->unk41C.x, this->unk41C.y, this->unk41C.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk416.y, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->unk416.x, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(this->unk416.z, MTXMODE_APPLY);
    }
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/func_80A8FBB4.asm")

void func_80A8FC64(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
    EnTrt* this = THIS;

    if (limbIndex == 21) {
        SysMatrix_InsertTranslation(this->unk41C.x, this->unk41C.y, this->unk41C.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateY(this->unk416.y, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->unk416.x, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(this->unk416.z, MTXMODE_APPLY);
    }
}

void EnTrt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static UNK_PTR D_80A8FEFC[] = { &D_0600B0B8, &D_0600B8B8, &D_0600C0B8 };
    EnTrt* this = THIS;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A8FEFC[this->eyeTextureIdx]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80A8FEFC[this->eyeTextureIdx]));
    func_801343C0(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                  func_80A8FB34, func_80A8FBB4, func_80A8FC64, &this->actor);
    func_80A8EFF8(globalCtx, this, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    func_80A8F404(globalCtx, this);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Trt_0x80A8B770/EnTrt_Draw.asm")
