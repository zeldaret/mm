/*
 * File: z_en_sob1.c
 * Overlay: ovl_En_Sob1
 * Description: Shops (Zora, Goron, and Bomb)
 */

#include "z_en_sob1.h"

#define FLAGS 0x00000019

#define THIS ((EnSob1*)thisx)

#define CURSOR_INVALID 0xFF
#define ColChanMix(c1, c2, m) (c1 - (s32)(c2 * m)) & 0xFF

void EnSob1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Update(Actor* thisx, GlobalContext* globalCtx);

void EnSob1_DrawZoraShopkeeper(Actor* thisx, GlobalContext* globalCtx);  // Draw
void EnSob1_DrawGoronShopkeeper(Actor* thisx, GlobalContext* globalCtx); // Draw
void EnSob1_DrawBombShopkeeper(Actor* thisx, GlobalContext* globalCtx);  // Draw

void EnSob1_Idle(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_Blink(EnSob1* this);
void EnSob1_Walk(EnSob1* this, GlobalContext* globalCtx);
s16 EnSob1_GetAngleAndDistanceSquaredToPoint(Path* path, s32 pointIdx, Vec3f* pos, f32* dist);
void EnSob1_Walking(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_Hello(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_StartShopping(GlobalContext* globalCtx, EnSob1* this);
void EnSob1_SetupIdle(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_FaceShopKeeper(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_LookToShelf(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_EndingInteraction(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_BrowseShelf(EnSob1* this, GlobalContext* globalCtx);
s32 EnSob1_ReturnItemToShelf(EnSob1* this);
void EnSob1_TalkingToShopkeeper(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_SelectItem(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_LookToShopkeeperFromShelf(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_BuyItemWithFanfare(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_CanBuy(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_CannotBuy(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_SetupItemPurchased(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_ResetItemPosition(EnSob1* this);
void EnSob1_ContinueShopping(EnSob1* this, GlobalContext* globalCtx);
s32 EnSob1_TestCancelOption(EnSob1* this, GlobalContext* globalCtx, Input* input);
s32 EnSob1_TakeItemOffShelf(EnSob1* this);
void EnSob1_InitZoraShopkeeper(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_InitGoronShopkeeper(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_InitBombShopkeeper(EnSob1* this, GlobalContext* globalCtx);
void EnSob1_InitialUpdate(EnSob1* this, GlobalContext* globalCtx);

extern UNK_TYPE D_0401F740;
extern UNK_TYPE D_0401F8C0;
extern UNK_TYPE D_0401F7C0;
extern AnimationHeader D_06009120;
extern AnimationHeader D_06008268;
extern FlexSkeletonHeader D_0600D208;
extern AnimationHeader D_0600078C;
extern AnimationHeader D_060087BC;
extern FlexSkeletonHeader D_06011AC8;
extern AnimationHeader D_060000FC;
extern FlexSkeletonHeader D_06009220;
extern Gfx D_06000970[];
extern UNK_TYPE D_06005458;
extern UNK_TYPE D_060050A0;
extern UNK_TYPE D_060058A0;
extern UNK_TYPE D_060060A0;
extern UNK_TYPE D_06010438;
extern UNK_TYPE D_06010C38;
extern UNK_TYPE D_06011038;

static ActorAnimationEntryS sAnimationsBombShopkeeper[] = {
    { &D_06009120, 2.0f, 0, -1, 0, 20 },
    { &D_06008268, 1.0f, 0, -1, 2, 0 },
    { &D_060087BC, 1.0f, 0, -1, 0, 0 },
};

const ActorInit En_Sob1_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSob1),
    (ActorFunc)EnSob1_Init,
    (ActorFunc)EnSob1_Destroy,
    (ActorFunc)EnSob1_Update,
    (ActorFunc)NULL,
};

static s16 sObjectIds[][3] = {
    { 0x00D0, 0x0283, 0x00D6 },
    { 0x00A1, 0x0283, 0x00D5 },
    { 0x012C, 0x0283, 0x0283 },
    { 0x00A1, 0x0283, 0x00D5 },
};

static u16 sFacingShopkeeperTextIds[] = { 0x12D6, 0x0BC0, 0x0640, 0x0BC0 };

static u16 sNoRoomTextIds[] = { 0x12E3, 0x0BD3, 0x0641, 0x0BD3 };

static u16 sBuySuccessTextIds[] = { 0x12E6, 0x0BD6, 0x0647, 0x0BD6 };

static u16 sCannotGetNowTextIds[] = { 0x12E1, 0x0BD2, 0x0645, 0x0BD2 };

static u16 sNeedRupeesTextIds[] = { 0x12E5, 0x0BD5, 0x0646, 0x0BD5 };

static u16 sNeedEmptyBottleTextIds[] = { 0x12E4, 0x0BD4, 0x0645, 0x0BD4 };

static u16 sCannotGetNow2TextIds[] = { 0x12E1, 0x0BD1, 0x0641, 0x0BD1 };

static u16 sNoRoom2TextIds[] = { 0x12E3, 0x0BD3, 0x0641, 0x0BD3 };

static f32 sActorScales[] = { 0.01f, 0.01f, 0.01f, 0.01f };

static ShopItem sShops[][3] = {
    {
        { SI_POTION_RED_4, 1258, 42, 325 },
        { SI_ARROWS_SMALL_1, 1240, 42, 325 },
        { SI_SHIELD_HERO_3, 1222, 42, 325 },
    },
    {
        { SI_POTION_RED_5, -57, 42, -62 },
        { SI_ARROWS_SMALL_2, -75, 42, -62 },
        { SI_BOMB_2, -93, 42, -62 },
    },
    {
        { SI_BOMB_BAG_20_2, 221, -7, 73 },
        { SI_BOMBCHU, 203, -7, 69 },
        { SI_BOMB_1, 185, -7, 65 },
    },
    {
        { SI_POTION_RED_6, -57, 42, -62 },
        { SI_ARROWS_SMALL_3, -75, 42, -62 },
        { SI_BOMB_3, -93, 42, -62 },
    },
};

static EnSob1XZRange sPosXZRanges[] = {
    { 1170.0f, 1230.0f, 360.0f, 380.0f },
    { -142.0f, -72.0f, -20.0f, 0.0f },
    { 138.0f, 200.0f, 72.0f, 160.0f },
    { -142.0f, -72.0f, -20.0f, 0.0f },
};

static Vec3f sSelectedItemPositions[] = {
    { 1240.0f, 45.0f, 349.0f },
    { -75.0f, 45.0f, -38.0f },
    { 197.0f, -4.0f, 93.0f },
    { -75.0f, 45.0f, -38.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

static EnSob1ActionFunc sInitFuncs[] = {
    EnSob1_InitZoraShopkeeper,
    EnSob1_InitGoronShopkeeper,
    EnSob1_InitBombShopkeeper,
    EnSob1_InitGoronShopkeeper,
};

extern Vec3f sPosOffset[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, -4.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, -4.0f, 0.0f },
};

static UNK_PTR sZoraShopkeeperEyeTextures[] = { &D_060050A0, &D_060058A0, &D_060060A0 };

static UNK_PTR sGoronShopkeeperEyeTextures[] = { &D_06010438, &D_06010C38, &D_06011038 };

void EnSob1_ChangeAnim(SkelAnime* skelAnime, ActorAnimationEntryS* animations, s32 idx) {
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

void EnSob1_SetupAction(EnSob1* this, EnSob1ActionFunc action) {
    this->actionFunc = action;
}

s32 EnSob1_TestItemSelected(GlobalContext* globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A);
    }
    return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CUP);
}

u16 EnSob1_GetTalkOption(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->shopType == BOMB_SHOP) {
        if (gSaveContext.day == 1 && gSaveContext.time >= 0x4000) {
            return 0x648;
        } else if (gSaveContext.weekEventReg[33] & 8) {
            return 0x649;
        } else {
            return 0x64A;
        }
    } else if (this->shopType == ZORA_SHOP) {
        switch (player->transformation) {
            case PLAYER_FORM_DEKU:
                return 0x12D8;
            case PLAYER_FORM_GORON:
                return 0x12D9;
            case PLAYER_FORM_ZORA:
                return 0x12DA;
            default:
                return 0x12D7;
        }
    } else if (this->shopType == GORON_SHOP) {
        if (player->transformation != PLAYER_FORM_GORON) {
            return 0xBC1;
        }
        return 0xBC2;
    } else if (this->shopType == GORON_SHOP_SPRING) {
        if (player->transformation != PLAYER_FORM_GORON) {
            return 0xBC3;
        }
        return 0xBC4;
    }
    return 0;
}

#ifdef NON_MATCHING
// Matches but jmptable is in late rodata
u16 EnSob1_GetWelcome(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->shopType == BOMB_SHOP) {
        switch (Player_GetMask(globalCtx)) {
            case PLAYER_MASK_NONE:
            case PLAYER_MASK_BUNNY_HOOD:
            case PLAYER_MASK_POSTMANS_HAT:
                return 0x644;
            case PLAYER_MASK_GORON_MASK:
            case PLAYER_MASK_ZORA_MASK:
            case PLAYER_MASK_DEKU_MASK:
                return 0x64B;
            case PLAYER_MASK_MASK_OF_TRUTH:
            case PLAYER_MASK_ALL_NIGHT_MASK:
            case PLAYER_MASK_KEATON_MASK:
            case PLAYER_MASK_ROMANIS_MASK:
            case PLAYER_MASK_GREAT_FAIRYS_MASK:
            case PLAYER_MASK_DON_GEROS_MASK:
            case PLAYER_MASK_KAMAROS_MASK:
            case PLAYER_MASK_BREMEN_MASK:
            case PLAYER_MASK_MASK_OF_SCENTS:
                return 0x685;
            case PLAYER_MASK_GAROS_MASK:
            case PLAYER_MASK_CIRCUS_LEADERS_MASK:
            case PLAYER_MASK_GIBDO_MASK:
            case PLAYER_MASK_CAPTAINS_HAT:
                return 0x686;
            case PLAYER_MASK_COUPLES_MASK:
                return 0x687;
            case PLAYER_MASK_STONE_MASK:
                return 0x688;
            case PLAYER_MASK_BLAST_MASK:
                return 0x689;
            case PLAYER_MASK_KAFEIS_MASK:
                return 0x68A;
        }
    } else if (this->shopType == ZORA_SHOP) {
        switch (player->transformation) {
            case PLAYER_FORM_HUMAN:
                if (gSaveContext.weekEventReg[57] & 0x10) {
                    return 0x12CF;
                }
                gSaveContext.weekEventReg[57] |= 0x10;
                return 0x12CE;
            case PLAYER_FORM_DEKU:
                if (gSaveContext.weekEventReg[57] & 0x20) {
                    return 0x12D1;
                }
                gSaveContext.weekEventReg[57] |= 0x20;
                return 0x12D0;
            case PLAYER_FORM_GORON:
                if (gSaveContext.weekEventReg[57] & 0x40) {
                    return 0x12D3;
                }
                gSaveContext.weekEventReg[57] |= 0x40;
                return 0x12D2;
            case PLAYER_FORM_ZORA:
                if (gSaveContext.weekEventReg[57] & 0x80) {
                    return 0x12D5;
                }
                gSaveContext.weekEventReg[57] |= 0x80;
                return 0x12D4;
            default:
                return 0x12CE;
        }
    } else if (this->shopType == GORON_SHOP) {
        if (player->transformation != PLAYER_FORM_GORON) {
            if (gSaveContext.weekEventReg[58] & 4) {
                return 0xBB9;
            }
            gSaveContext.weekEventReg[58] |= 4;
            return 0xBB8;
        } else {
            if (gSaveContext.weekEventReg[58] & 8) {
                return 0xBBB;
            }
            gSaveContext.weekEventReg[58] |= 8;
            return 0xBBA;
        }
    } else if (this->shopType == GORON_SHOP_SPRING) {
        if (player->transformation != PLAYER_FORM_GORON) {
            if (gSaveContext.weekEventReg[58] & 0x10) {
                return 0xBBD;
            }
            gSaveContext.weekEventReg[58] |= 0x10;
            return 0xBBC;
        } else {
            if (gSaveContext.weekEventReg[58] & 0x20) {
                return 0xBBF;
            }
            gSaveContext.weekEventReg[58] |= 0x20;
            return 0xBBE;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_GetWelcome.asm")
#endif

u16 EnSob1_GetGoodbyeBombShop(EnSob1* this) {
    if (this->shopType == BOMB_SHOP) {
        if (gSaveContext.day == 1) {
            return 0x64C;
        } else if (gSaveContext.day == 2) {
            return 0x64D;
        } else if (!gSaveContext.isNight) {
            return 0x64E;
        } else {
            return 0x64F;
        }
    }
    return 0x64C;
}

void EnSob1_EndInteractionBombShop(EnSob1* this, GlobalContext* globalCtx) {
    this->drawCursor = 0;
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = false;
    this->goodbyeTextId = EnSob1_GetGoodbyeBombShop(this);
    func_801518B0(globalCtx, this->goodbyeTextId, &this->actor);
    EnSob1_SetupAction(this, EnSob1_EndingInteraction);
}

void EnSob1_SpawnShopItems(EnSob1* this, GlobalContext* globalCtx, ShopItem* shopItem) {
    s32 i;

    for (i = 0; i < 3; i++, shopItem++) {
        if (shopItem->shopItemId < 0) {
            this->items[i] = NULL;
        } else {
            this->items[i] = (EnGirlA*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA, shopItem->x,
                                                   shopItem->y, shopItem->z, 0, 0, 0, shopItem->shopItemId);
        }
    }
}

s32 EnSob1_GetObjIndicies(EnSob1* this, GlobalContext* globalCtx, s16* objIds) {
    if (objIds[1] != 0x283) {
        this->objIndicies[1] = Object_GetIndex(&globalCtx->objectCtx, objIds[1]);
        if (this->objIndicies[1] < 0) {
            return false;
        }
    } else {
        this->objIndicies[1] = -1;
    }
    if (objIds[2] != 0x283) {
        this->objIndicies[2] = Object_GetIndex(&globalCtx->objectCtx, objIds[2]);
        if (this->objIndicies[2] < 0) {
            return false;
        }
    } else {
        this->objIndicies[2] = -1;
    }
    return true;
}

void EnSob1_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    s16* objIds;

    switch (ENSOB1_GET_SHOPTYPE(thisx)) {
        case ZORA_SHOP:
            this->shopType = ZORA_SHOP;
            break;
        case GORON_SHOP:
            if (gSaveContext.weekEventReg[33] & 0x80) {
                this->shopType = GORON_SHOP_SPRING;
            } else {
                this->shopType = GORON_SHOP;
            }
            break;
        case BOMB_SHOP:
            this->shopType = BOMB_SHOP;
            break;
        default:
            Actor_MarkForDeath(&this->actor);
            return;
    }

    objIds = sObjectIds[this->shopType];
    this->objIndicies[0] = Object_GetIndex(&globalCtx->objectCtx, objIds[0]);
    if (this->objIndicies[0] < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (!EnSob1_GetObjIndicies(this, globalCtx, objIds)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    Actor_ProcessInitChain(&this->actor, sInitChain);
    EnSob1_SetupAction(this, EnSob1_InitialUpdate);
}

void EnSob1_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void EnSob1_UpdateCursorPos(GlobalContext* globalCtx, EnSob1* this) {
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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_UpdateCursorPos.asm")
#endif

void EnSob1_EndInteraction(GlobalContext* globalCtx, EnSob1* this) {
    Player* player = PLAYER;

    if (this->cutsceneState == 2) {
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
    globalCtx->interfaceCtx.unk_222 = 0;
    globalCtx->interfaceCtx.unk_224 = 0;
    EnSob1_SetupAction(this, EnSob1_Idle);
}

s32 EnSob1_TestEndInteraction(EnSob1* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        if (this->shopType == BOMB_SHOP) {
            EnSob1_EndInteractionBombShop(this, globalCtx);
        } else {
            EnSob1_EndInteraction(globalCtx, this);
        }
        return true;
    }
    return false;
}

s32 EnSob1_TestCancelOption(EnSob1* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        return true;
    }
    return false;
}

void EnSob1_SetupStartShopping(GlobalContext* globalCtx, EnSob1* this, u8 skipHello) {
    func_8011552C(globalCtx, 16);
    if (!skipHello) {
        EnSob1_SetupAction(this, EnSob1_Hello);
    } else {
        EnSob1_StartShopping(globalCtx, this);
    }
}

void EnSob1_StartShopping(GlobalContext* globalCtx, EnSob1* this) {
    EnSob1_SetupAction(this, EnSob1_FaceShopKeeper);
    func_80151938(globalCtx, sFacingShopkeeperTextIds[this->shopType]);
    func_8011552C(globalCtx, 6);
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = true;
}

void EnSob1_TalkToShopkeeper(GlobalContext* globalCtx, EnSob1* this) {
    EnSob1_SetupAction(this, EnSob1_TalkingToShopkeeper);
    this->talkOptionTextId = EnSob1_GetTalkOption(this, globalCtx);
    func_80151938(globalCtx, this->talkOptionTextId);
    func_8011552C(globalCtx, 6);
    this->stickLeftPrompt.isEnabled = false;
    this->stickRightPrompt.isEnabled = false;
}

void EnSob1_SetupLookToShopkeeperFromShelf(GlobalContext* globalCtx, EnSob1* this) {
    play_sound(NA_SE_SY_CURSOR);
    this->drawCursor = 0;
    EnSob1_SetupAction(this, EnSob1_LookToShopkeeperFromShelf);
}

void EnSob1_EndingInteraction(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        EnSob1_EndInteraction(globalCtx, this);
    }
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void EnSob1_SetupWalk(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((player->actor.world.pos.x >= 0.0f && player->actor.world.pos.x <= 390.0f) &&
        (player->actor.world.pos.z >= 72.0f && player->actor.world.pos.z <= 365.0f)) {
        EnSob1_SetupAction(this, EnSob1_Walk);
    }
}
#else
void EnSob1_SetupWalk(EnSob1* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_SetupWalk.asm")
#endif

void EnSob1_Idle(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->headRotTarget = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookFowardCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = 1;
        }
        player->stateFlags2 |= 0x20000000;
        this->welcomeTextId = EnSob1_GetWelcome(this, globalCtx);
        func_801518B0(globalCtx, this->welcomeTextId, &this->actor);
        if (ENSOB1_GET_SHOPTYPE(&this->actor) == BOMB_SHOP) {
            this->headRotTarget = -0x2000;
        }
        EnSob1_SetupStartShopping(globalCtx, this, false);
    } else {
        if ((player->actor.world.pos.x >= this->posXZRange.xMin &&
             player->actor.world.pos.x <= this->posXZRange.xMax) &&
            (player->actor.world.pos.z >= this->posXZRange.zMin &&
             player->actor.world.pos.z <= this->posXZRange.zMax)) {
            func_800B8614(&this->actor, globalCtx, 400.0f);
        }
        if (this->wasTalkedToWhileWalking == 1) {
            this->wasTalkedToWhileWalking = false;
            EnSob1_SetupStartShopping(globalCtx, this, false);
        }
    }
}

void EnSob1_UpdateJoystickInputState(GlobalContext* globalCtx, EnSob1* this) {
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

u8 EnSob1_SetCursorIndexFromNeutral(EnSob1* this, u8 shelfOffset) {
    if (this->items[shelfOffset] != NULL) {
        return shelfOffset;
    }
    return CURSOR_INVALID;
}

void EnSob1_Hello(EnSob1* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if ((talkState == 5) && (func_80147624(globalCtx)) &&
        (!EnSob1_TestEndInteraction(this, globalCtx, globalCtx->state.input))) {
        if (this->welcomeTextId == 0x68A) { // Welcome text when wearing Kafei's mask
            EnSob1_EndInteraction(globalCtx, this);
        } else {
            EnSob1_StartShopping(globalCtx, this);
        }
    }
}

s32 EnSob1_FacingShopkeeperDialogResult(EnSob1* this, GlobalContext* globalCtx) {
    switch (globalCtx->msgCtx.choiceIndex) {
        case 0:
            func_8019F208();
            EnSob1_TalkToShopkeeper(globalCtx, this);
            return true;
        case 1:
            func_8019F230();
            if (this->shopType == BOMB_SHOP) {
                EnSob1_EndInteractionBombShop(this, globalCtx);
            } else {
                EnSob1_EndInteraction(globalCtx, this);
            }
            return true;
    }
    return false;
}

void EnSob1_FaceShopKeeper(EnSob1* this, GlobalContext* globalCtx) {
    s32 pad[2];
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    u8 cursorIdx;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookFowardCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else {
        if (talkState == 4) {
            func_8011552C(globalCtx, 6);
            if (!EnSob1_TestEndInteraction(this, globalCtx, globalCtx->state.input)) {
                if (!func_80147624(globalCtx) || !EnSob1_FacingShopkeeperDialogResult(this, globalCtx)) {
                    if (this->stickAccumX > 0) {
                        cursorIdx = EnSob1_SetCursorIndexFromNeutral(this, 2);
                        if (cursorIdx != CURSOR_INVALID) {
                            this->cursorIdx = cursorIdx;
                            EnSob1_SetupAction(this, EnSob1_LookToShelf);
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

void EnSob1_TalkingToShopkeeper(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        EnSob1_StartShopping(globalCtx, this);
    }
}

void EnSob1_LookToShopkeeperFromShelf(EnSob1* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 2) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = 0;
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToShopkeeperCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
            EnSob1_StartShopping(globalCtx, this);
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void EnSob1_EndWalk(EnSob1* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 dist;
    s16 sp2E;
    s16 sp2C;

    sp2E = this->skelAnime.animCurrentFrame / this->skelAnime.animPlaybackSpeed;
    sp2C = SkelAnime_GetFrameCount(&D_06009120.common) / (s16)this->skelAnime.animPlaybackSpeed;
    Math_SmoothStepToS(
        &this->actor.world.rot.y,
        EnSob1_GetAngleAndDistanceSquaredToPoint(this->path, this->pathPointsIdx - 1, &this->actor.world.pos, &dist), 4,
        1000, 1);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
    if (dist < 12.0f) {
        this->actor.speedXZ = 0.0f;
        if (sp2C == sp2E) {
            EnSob1_ChangeAnim(&this->skelAnime, sAnimationsBombShopkeeper, 1);
            EnSob1_SetupAction(this, EnSob1_SetupIdle);
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void EnSob1_SetupIdle(EnSob1* this, GlobalContext* globalCtx) {
    s16 animCurrentFrame = this->skelAnime.animCurrentFrame;

    if (SkelAnime_GetFrameCount(&D_06008268.common) == animCurrentFrame) {
        EnSob1_ChangeAnim(&this->skelAnime, sAnimationsBombShopkeeper, 2);
        EnSob1_SetupAction(this, EnSob1_Idle);
    }
    EnSob1_Walking(this, globalCtx);
}

void EnSob1_Walk(EnSob1* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 dist;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (this->path != NULL) {
        Math_SmoothStepToS(
            &this->actor.world.rot.y,
            EnSob1_GetAngleAndDistanceSquaredToPoint(this->path, this->pathPointsIdx, &this->actor.world.pos, &dist), 4,
            1000, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->actor.speedXZ = 2.0f;
        if (dist < 25.0f) {
            this->pathPointsIdx++;
            if ((this->path->count - 1) < this->pathPointsIdx) {
                this->actor.speedXZ = 0.0f;
                EnSob1_SetupAction(this, EnSob1_EndWalk);
            }
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    EnSob1_Walking(this, globalCtx);
}

void EnSob1_Walking(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookFowardCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->cutsceneState = 1;
        }
        player->stateFlags2 |= 0x20000000;
        this->welcomeTextId = EnSob1_GetWelcome(this, globalCtx);
        func_801518B0(globalCtx, this->welcomeTextId, &this->actor);
        this->wasTalkedToWhileWalking = true;
    } else {
        if ((player->actor.world.pos.x >= this->posXZRange.xMin &&
             player->actor.world.pos.x <= this->posXZRange.xMax) &&
            (player->actor.world.pos.z >= this->posXZRange.zMin &&
             player->actor.world.pos.z <= this->posXZRange.zMax)) {
            func_800B8614(&this->actor, globalCtx, 400.0f);
        }
    }
}

void EnSob1_ItemPurchased(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            player->stateFlags2 |= 0x20000000;
            EnSob1_SetupAction(this, EnSob1_ContinueShopping);
            this->cutsceneState = 2;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookToShopkeeperCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80151938(globalCtx, 0x647);
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void EnSob1_LookToShelf(EnSob1* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 2) {
        ActorCutscene_Stop(this->cutscene);
        this->cutsceneState = 0;
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->lookToShelfCutscene;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene) != 0) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
            EnSob1_UpdateCursorPos(globalCtx, this);
            EnSob1_SetupAction(this, EnSob1_BrowseShelf);
            func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void EnSob1_CursorLeftRight(GlobalContext* globalCtx, EnSob1* this) {
    u8 curTemp = this->cursorIdx;

    if (this->stickAccumX < 0) {
        if (curTemp != 2) {
            curTemp++;
        } else {
            EnSob1_SetupLookToShopkeeperFromShelf(globalCtx, this);
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

s32 EnSob1_HasPlayerSelectedItem(GlobalContext* globalCtx, EnSob1* this, Input* input) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (EnSob1_TestEndInteraction(this, globalCtx, input)) {
        return true;
    }
    if (EnSob1_TestItemSelected(globalCtx)) {
        if (!item->isOutOfStock) {
            this->tmpActionFunc = this->actionFunc;
            func_80151938(globalCtx, this->items[this->cursorIdx]->choiceTextId);
            play_sound(NA_SE_SY_DECIDE);
            this->stickLeftPrompt.isEnabled = false;
            this->stickRightPrompt.isEnabled = false;
            this->drawCursor = 0;
            EnSob1_SetupAction(this, EnSob1_SelectItem);
        } else {
            play_sound(NA_SE_SY_ERROR);
        }
        return true;
    }
    return false;
}

void EnSob1_BrowseShelf(EnSob1* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    u8 prevCursorIdx = this->cursorIdx;
    u8 cursorIdx;

    if (!EnSob1_ReturnItemToShelf(this)) {
        this->delayTimer = 3;
    } else if (this->delayTimer != 0) {
        this->delayTimer--;
    } else {
        this->drawCursor = 0xFF;
        this->stickLeftPrompt.isEnabled = true;
        EnSob1_UpdateCursorPos(globalCtx, this);
        if (talkState == 5) {
            func_8011552C(globalCtx, 6);
            if (!EnSob1_HasPlayerSelectedItem(globalCtx, this, globalCtx->state.input)) {
                EnSob1_CursorLeftRight(globalCtx, this);
                cursorIdx = this->cursorIdx;
                if (cursorIdx != prevCursorIdx) {
                    func_80151938(globalCtx, this->items[cursorIdx]->actor.textId);
                    play_sound(NA_SE_SY_CURSOR);
                }
            }
        }
    }
}

void EnSob1_SetupBuyItemWithFanfare(GlobalContext* globalCtx, EnSob1* this) {
    Player* player = PLAYER;

    func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    globalCtx->msgCtx.unk11F22 = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    player->stateFlags2 &= ~0x20000000;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    EnSob1_SetupAction(this, EnSob1_BuyItemWithFanfare);
}

void EnSob1_SetupCannotBuy(GlobalContext* globalCtx, EnSob1* this, u16 textId) {
    func_80151938(globalCtx, textId);
    EnSob1_SetupAction(this, EnSob1_CannotBuy);
}

void EnSob1_SetupCanBuy(GlobalContext* globalCtx, EnSob1* this, u16 textId) {
    func_80151938(globalCtx, textId);
    EnSob1_SetupAction(this, EnSob1_CanBuy);
}

#ifdef NON_MATCHING
// Matches but jmptable is in late rodata
void EnSob1_HandleCanBuyItem(GlobalContext* globalCtx, EnSob1* this) {
    EnGirlA* item = this->items[this->cursorIdx];
    EnGirlA* item2;

    switch (item->canBuyFunc(globalCtx, item)) {
        case CANBUY_RESULT_SUCCESS_FANFARE:
            if (this->cutsceneState == 2) {
                ActorCutscene_Stop(this->cutscene);
                this->cutsceneState = 0;
            }
            func_8019F208();
            item2 = this->items[this->cursorIdx];
            item2->buyFanfareFunc(globalCtx, item2);
            EnSob1_SetupBuyItemWithFanfare(globalCtx, this);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_SUCCESS:
            func_8019F208();
            item->buyFunc(globalCtx, item);
            if ((this->shopType == GORON_SHOP) && (item->actor.params == SI_POTION_RED_5)) {
                EnSob1_SetupCanBuy(globalCtx, this, 0xBD7);
            } else if ((this->shopType == ZORA_SHOP) && (item->actor.params == SI_POTION_RED_4)) {
                EnSob1_SetupCanBuy(globalCtx, this, 0x12E7);
            } else if ((this->shopType == GORON_SHOP_SPRING) && (item->actor.params == SI_POTION_RED_6)) {
                EnSob1_SetupCanBuy(globalCtx, this, 0xBD7);
            } else {
                EnSob1_SetupCanBuy(globalCtx, this, sBuySuccessTextIds[this->shopType]);
            }
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case CANBUY_RESULT_NO_ROOM:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, sNoRoomTextIds[this->shopType]);
            break;
        case CANBUY_RESULT_NEED_EMPTY_BOTTLE:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, sNeedEmptyBottleTextIds[this->shopType]);
            break;
        case CANBUY_RESULT_NEED_RUPEES:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, sNeedRupeesTextIds[this->shopType]);
            break;
        case CANBUY_RESULT_CANNOT_GET_NOW:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, sCannotGetNowTextIds[this->shopType]);
            break;
        case CANBUY_RESULT_CANNOT_GET_NOW_2:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, sCannotGetNow2TextIds[this->shopType]);
            break;
        case CANBUY_RESULT_NO_ROOM_2:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, sNoRoom2TextIds[this->shopType]);
            break;
        case CANBUY_RESULT_ALREADY_HAVE:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, 0x658);
            break;
        case CANBUY_RESULT_HAVE_BETTER:
            play_sound(NA_SE_SY_ERROR);
            EnSob1_SetupCannotBuy(globalCtx, this, 0x659);
            break;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_HandleCanBuyItem.asm")
#endif

void EnSob1_SelectItem(EnSob1* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (EnSob1_TakeItemOffShelf(this) && talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (!EnSob1_TestCancelOption(this, globalCtx, globalCtx->state.input) && func_80147624(globalCtx)) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    EnSob1_HandleCanBuyItem(globalCtx, this);
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

void EnSob1_CannotBuy(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5) {
        if (func_80147624(globalCtx)) {
            this->actionFunc = this->tmpActionFunc;
            func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        }
    }
}

void EnSob1_CanBuy(EnSob1* this, GlobalContext* globalCtx) {
    EnGirlA* item;

    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->shopItemSelectedTween = 0.0f;
        EnSob1_ResetItemPosition(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
    }
}

void EnSob1_BuyItemWithFanfare(EnSob1* this, GlobalContext* globalCtx) {
    // The player sets itself as the parent actor to signal that it has obtained the give item request
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        EnSob1_SetupAction(this, EnSob1_SetupItemPurchased);
    } else {
        func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    }
}

void EnSob1_SetupItemPurchased(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        globalCtx->msgCtx.unk11F22 = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        EnSob1_SetupAction(this, EnSob1_ItemPurchased);
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->lookToShopkeeperCutscene;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void EnSob1_ContinueShopping(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    EnGirlA* item;

    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx))) {
        EnSob1_ResetItemPosition(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        player->actor.shape.rot.y += 0x8000;
        player->stateFlags2 |= 0x20000000;
        func_801518B0(globalCtx, this->welcomeTextId, &this->actor);
        EnSob1_SetupStartShopping(globalCtx, this, true);
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void EnSob1_PositionSelectedItem(EnSob1* this) {
    Vec3f selectedItemPosition = sSelectedItemPositions[this->shopType];
    u8 i = this->cursorIdx;
    EnGirlA* item;
    ShopItem* shopItem;
    Vec3f worldPos;

    shopItem = &sShops[this->shopType][i];
    item = this->items[i];

    worldPos.x = shopItem->x + (selectedItemPosition.x - shopItem->x) * this->shopItemSelectedTween;
    worldPos.y = shopItem->y + (selectedItemPosition.y - shopItem->y) * this->shopItemSelectedTween;
    worldPos.z = shopItem->z + (selectedItemPosition.z - shopItem->z) * this->shopItemSelectedTween;

    item->actor.world.pos.x = worldPos.x;
    item->actor.world.pos.y = worldPos.y;
    item->actor.world.pos.z = worldPos.z;
}

void EnSob1_ResetItemPosition(EnSob1* this) {
    this->shopItemSelectedTween = 0.0f;
    EnSob1_PositionSelectedItem(this);
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
// Returns true when animation has completed
s32 EnSob1_TakeItemOffShelf(EnSob1* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 1.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween >= 0.85f) {
        this->shopItemSelectedTween = 1.0f;
    }
    EnSob1_PositionSelectedItem(this);
    if (this->shopItemSelectedTween == 1.0f) {
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_TakeItemOffShelf.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
// Returns true when animation has completed
s32 EnSob1_ReturnItemToShelf(EnSob1* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 0.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween <= 0.15f) {
        this->shopItemSelectedTween = 0.0f;
    }
    EnSob1_PositionSelectedItem(this);
    if (this->shopItemSelectedTween == 0.0f) {
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_ReturnItemToShelf.asm")
#endif

void EnSob1_UpdateItemSelectedProperty(EnSob1* this) {
    EnGirlA** items = this->items;
    EnGirlA* item;
    s32 i;

    for (i = 0; i < 3; i++, items++) {
        item = *items;
        if (item != NULL) {
            if (this->actionFunc != EnSob1_SelectItem && this->actionFunc != EnSob1_CannotBuy &&
                this->drawCursor == 0) {
                item->isSelected = false;
            } else {
                item->isSelected = this->cursorIdx == i ? true : false;
            }
        }
    }
}

#ifdef NON_MATCHING
// Matches but floats are in laterodata
void EnSob1_UpdateCursorAnim(EnSob1* this) {
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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_UpdateCursorAnim.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void EnSob1_UpdateStickDirectionPromptAnim(EnSob1* this) {
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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_UpdateStickDirectionPromptAnim.asm")
#endif

#ifdef NON_MATCHING
// Matches but float is in late rodata
s16 EnSob1_GetAngleAndDistanceSquaredToPoint(Path* path, s32 pointIdx, Vec3f* pos, f32* dist) {
    Vec3s* points;
    f32 diffX;
    f32 diffZ;

    if (path != NULL) {
        points = (Vec3s*)Lib_SegmentedToVirtual(path->points);
        points = &points[pointIdx];
        diffX = points->x - pos->x;
        diffZ = points->z - pos->z;
    } else {
        diffX = 0.0f;
        diffZ = 0.0f;
    }
    *dist = SQ(diffX) + SQ(diffZ);
    return Math_Acot2F(diffZ, diffX) * (0x8000 / M_PI);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_GetAngleAndDistanceSquaredToPoint.asm")
#endif

void EnSob1_GetCutscenes(EnSob1* this) {
    this->lookFowardCutscene = this->actor.cutscene;
    this->lookToShelfCutscene = ActorCutscene_GetAdditionalCutscene(this->lookFowardCutscene);
    this->lookToShopkeeperCutscene = ActorCutscene_GetAdditionalCutscene(this->lookToShelfCutscene);
}

void EnSob1_WaitForBlink(EnSob1* this) {
    s16 decr;

    decr = this->blinkTimer - 1;
    if (decr != 0) {
        this->blinkTimer = decr;
    } else {
        this->blinkFunc = EnSob1_Blink;
    }
}

void EnSob1_Blink(EnSob1* this) {
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
        this->blinkFunc = EnSob1_WaitForBlink;
    } else {
        this->eyeTextureIdx = eyeTextureIdxTemp;
        this->blinkTimer = 1;
    }
}

void EnSob1_Obj3ToSeg6(EnSob1* this, GlobalContext* globalCtx) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->objIndicies[2]].segment);
}

s32 EnSob1_AreObjectsLoaded(EnSob1* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndicies[0])) {
        if (this->objIndicies[1] >= 0 && !Object_IsLoaded(&globalCtx->objectCtx, this->objIndicies[1])) {
            return false;
        }
        if (this->objIndicies[2] >= 0 && !Object_IsLoaded(&globalCtx->objectCtx, this->objIndicies[2])) {
            return false;
        }
        return true;
    }
    return false;
}

void EnSob1_InitZoraShopkeeper(EnSob1* this, GlobalContext* globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600D208, NULL, this->limbDrawTable, this->transitionDrawTable,
                     20);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->objIndicies[2]].segment);
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600078C, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0600078C.common), 0,
                         0.0f);
    this->actor.draw = EnSob1_DrawZoraShopkeeper;
    this->actionFunc2 = EnSob1_Obj3ToSeg6;
}

void EnSob1_InitGoronShopkeeper(EnSob1* this, GlobalContext* globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06011AC8, NULL, this->limbDrawTable, this->transitionDrawTable,
                     18);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->objIndicies[2]].segment);
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060000FC, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060000FC.common), 0,
                         0.0f);
    this->actor.draw = EnSob1_DrawGoronShopkeeper;
    this->actionFunc2 = EnSob1_Obj3ToSeg6;
}

void EnSob1_InitBombShopkeeper(EnSob1* this, GlobalContext* globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06009220, &D_06009120, this->limbDrawTable,
                     this->transitionDrawTable, 16);
    this->actor.draw = EnSob1_DrawBombShopkeeper;
    this->actionFunc2 = NULL;
    this->skelAnime.animPlaybackSpeed = 2.0f;
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void EnSob1_InitialUpdate(EnSob1* this, GlobalContext* globalCtx) {
    ShopItem* shopItems;
    EnSob1XZRange* unkStruct;
    Vec3f* posOffset;

    // Possibly fake temps
    EnSob1* this2;
    u32 maxColor = 255;

    if (EnSob1_AreObjectsLoaded(this, globalCtx)) {
        this->actor.flags &= ~0x10;
        this->actor.objBankIndex = this->objIndicies[0];
        Actor_SetObjectSegment(globalCtx, &this->actor);
        posOffset = &sPosOffset[this->shopType];
        this->actor.world.pos.x += posOffset->x;
        this->actor.world.pos.y += posOffset->y;
        this->actor.world.pos.z += posOffset->z;
        shopItems = sShops[this->shopType];
        if ((this->shopType == BOMB_SHOP) && (gSaveContext.weekEventReg[33] & 8)) {
            sShops[this->shopType][0].shopItemId = SI_BOMB_BAG_30_2;
        }

        this->cutsceneState = 0;
        EnSob1_GetCutscenes(this);
        this->cutscene = this->lookFowardCutscene;
        ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
        sInitFuncs[this->shopType](this, globalCtx);
        this->actor.colChkInfo.mass = 0xFF;
        this->actor.colChkInfo.cylRadius = 50;
        this->wasTalkedToWhileWalking = false;
        this->pathPointsIdx = 0;

        if (this->shopType == BOMB_SHOP) {
            this->path = func_8013D648(globalCtx, ENSOB1_GET_PATH(&this->actor), 0x1F);
        }
        if (this->shopType == BOMB_SHOP) {
            EnSob1_SetupAction(this, EnSob1_SetupWalk);
        } else {
            EnSob1_SetupAction(this, EnSob1_Idle);
        }

        this->cursorY = (this->cursorX = 100.0f);
        this->stickAccumX = (this->stickAccumY = 0);
        this->cursorIdx = 0;
        this->cursorZ = 1.2f;
        this->cursorColorR = 0;
        this->cursorColorG = 80;
        this->cursorColorB = maxColor;
        this->cursorColorA = maxColor;
        this->cursorAnimTween = 0.0f;
        this->cursorAnimState = 0;
        this->drawCursor = 0;

        this2 = this;

        this2->stickLeftPrompt.stickColorR = 200;
        this2->stickLeftPrompt.stickColorG = 200;
        this2->stickLeftPrompt.stickColorB = 200;
        this2->stickLeftPrompt.stickColorA = 180;
        this2->stickLeftPrompt.stickTexX = 49.0f;
        this2->stickLeftPrompt.stickTexY = 95.0f;
        this2->stickLeftPrompt.arrowColorR = maxColor;
        this2->stickLeftPrompt.arrowColorG = maxColor;
        this2->stickLeftPrompt.arrowColorB = 0;
        this2->stickLeftPrompt.arrowColorA = 200;
        this2->stickLeftPrompt.arrowTexX = 33.0f;
        this2->stickLeftPrompt.arrowTexY = 91.0f;
        this2->stickLeftPrompt.texZ = 1.0f;
        this2->stickLeftPrompt.isEnabled = 0;

        if (1) {}

        this2->stickRightPrompt.stickColorR = 200;
        this2->stickRightPrompt.stickColorG = 200;
        this2->stickRightPrompt.stickColorB = 200;
        this2->stickRightPrompt.stickColorA = 180;
        this2->stickRightPrompt.stickTexX = 274.0f;
        this2->stickRightPrompt.stickTexY = 95.0f;
        this2->stickRightPrompt.arrowColorR = maxColor;
        this2->stickRightPrompt.arrowColorG = 0;
        this2->stickRightPrompt.arrowColorB = 0;
        this2->stickRightPrompt.arrowColorA = 200;
        this2->stickRightPrompt.arrowTexX = 290.0f;
        this2->stickRightPrompt.arrowTexY = 91.0f;
        this2->stickRightPrompt.texZ = 1.0f;
        this2->stickRightPrompt.isEnabled = 0;

        this2->arrowAnimState = 0;
        this2->stickAnimState = 0;
        this2->arrowAnimTween = 0.0f;
        this2->stickAnimTween = 0.0f;
        this2->shopItemSelectedTween = 0.0f;

        this2->actor.gravity = 0.0f;
        this2->posXZRange = sPosXZRanges[this2->shopType];
        Actor_SetScale(&this2->actor, sActorScales[this2->shopType]);
        EnSob1_SpawnShopItems(this2, globalCtx, shopItems);
        this->headRot = this->headRotTarget = 0;
        this2->blinkTimer = 20;
        this2->eyeTextureIdx = 0;
        this->blinkFunc = EnSob1_WaitForBlink;
        this->actor.flags &= ~1;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_InitialUpdate.asm")
#endif

void EnSob1_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1ActionFunc actionFunc2;
    EnSob1* this = THIS;

    if (this->actionFunc != EnSob1_InitialUpdate) {
        this->blinkFunc(this);
        EnSob1_UpdateJoystickInputState(globalCtx, this);
        EnSob1_UpdateItemSelectedProperty(this);
        EnSob1_UpdateStickDirectionPromptAnim(this);
        EnSob1_UpdateCursorAnim(this);
        Math_StepToS(&this->headRot, this->headRotTarget, 0x190);
        this->actionFunc(this, globalCtx);
        Actor_SetHeight(&this->actor, 90.0f);
        actionFunc2 = this->actionFunc2;
        if (actionFunc2 != NULL) {
            actionFunc2(this, globalCtx);
        }
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    } else {
        this->actionFunc(this, globalCtx);
    }
}

void EnSob1_DrawCursor(GlobalContext* globalCtx, EnSob1* this, f32 x, f32 y, f32 z, u8 drawCursor) {
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

void EnSob1_DrawTextRec(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t, f32 dx,
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

void EnSob1_DrawStickDirectionPrompt(GlobalContext* globalCtx, EnSob1* this) {
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
            EnSob1_DrawTextRec(globalCtx, this->stickLeftPrompt.arrowColorR, this->stickLeftPrompt.arrowColorG,
                               this->stickLeftPrompt.arrowColorB, this->stickLeftPrompt.arrowColorA,
                               this->stickLeftPrompt.arrowTexX, this->stickLeftPrompt.arrowTexY,
                               this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            EnSob1_DrawTextRec(globalCtx, this->stickRightPrompt.arrowColorR, this->stickRightPrompt.arrowColorG,
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
            EnSob1_DrawTextRec(globalCtx, this->stickLeftPrompt.stickColorR, this->stickLeftPrompt.stickColorG,
                               this->stickLeftPrompt.stickColorB, this->stickLeftPrompt.stickColorA,
                               this->stickLeftPrompt.stickTexX, this->stickLeftPrompt.stickTexY,
                               this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            EnSob1_DrawTextRec(globalCtx, this->stickRightPrompt.stickColorR, this->stickRightPrompt.stickColorG,
                               this->stickRightPrompt.stickColorB, this->stickRightPrompt.stickColorA,
                               this->stickRightPrompt.stickTexX, this->stickRightPrompt.stickTexY,
                               this->stickRightPrompt.texZ, 0, 0, 1.0f, 1.0f);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 EnSob1_OverrideLimbDrawZoraShopkeeper(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                          Actor* thisx) {
    EnSob1* this = THIS;

    if (limbIndex == 15) {
        rot->x += this->headRot;
    }
    return 0;
}

s32 EnSob1_OverrideLimbDrawBombShopkeeper(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                          Actor* thisx) {
    EnSob1* this = THIS;

    if (limbIndex == 15) {
        SysMatrix_InsertXRotation_s(this->headRot, MTXMODE_APPLY);
    }
    return 0;
}

void EnSob1_PostLimbDrawBombShopkeeper(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (limbIndex == 11) {
        gSPDisplayList(POLY_OPA_DISP++, D_06000970);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

Gfx* EnSob1_EndDList(GraphicsContext* gfxCtx) {
    Gfx* dList;
    Gfx* dListHead;

    dList = dListHead = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);
    gSPEndDisplayList(dListHead++);

    return dList;
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void EnSob1_DrawZoraShopkeeper(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 0x00, 0x00, 0x00, 0xFF);
    gSPSegment(POLY_OPA_DISP++, 0x0C, EnSob1_EndDList(globalCtx->state.gfxCtx));
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sZoraShopkeeperEyeTextures[this->eyeTextureIdx]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnSob1_OverrideLimbDrawZoraShopkeeper, NULL, &this->actor);
    for (i = 0; i < 3; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }
    EnSob1_DrawCursor(globalCtx, this, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    EnSob1_DrawStickDirectionPrompt(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_DrawZoraShopkeeper.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void EnSob1_DrawGoronShopkeeper(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sGoronShopkeeperEyeTextures[this->eyeTextureIdx]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, &this->actor);
    for (i = 0; i < 3; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }
    EnSob1_DrawCursor(globalCtx, this, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    EnSob1_DrawStickDirectionPrompt(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_DrawGoronShopkeeper.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void EnSob1_DrawBombShopkeeper(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    u32 frames;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(&D_06005458));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnSob1_OverrideLimbDrawBombShopkeeper, EnSob1_PostLimbDrawBombShopkeeper, &this->actor);
    for (i = 0; i < 3; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }
    EnSob1_DrawCursor(globalCtx, this, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    EnSob1_DrawStickDirectionPrompt(globalCtx, this);
    frames = globalCtx->gameplayFrames;
    func_8012C2DC(globalCtx->state.gfxCtx);
    SysMatrix_NormalizeXYZ(&globalCtx->unk187FC);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0, -frames * 20, 32, 128));
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xFF, 0xFF, 0x00, 0xFF);
    gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0x00, 0x00, 0x00);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_DrawBombShopkeeper.asm")
#endif
