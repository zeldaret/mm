#include "z_en_sob1.h"

#define FLAGS 0x00000019

#define THIS ((EnSob1*)thisx)

#define ColChanMix(c1, c2, m) (c1 - (s32)(c2 * m)) & 0xFF

void EnSob1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A10368(Actor* thisx, GlobalContext* globalCtx); // Draw
void func_80A104E4(Actor* thisx, GlobalContext* globalCtx); // Draw
void func_80A10608(Actor* thisx, GlobalContext* globalCtx); // Draw

void func_80A0C8AC(EnSob1* this, EnSob1ActionFunc action);
s32 func_80A0CE10(EnSob1* this, GlobalContext* globalCtx, Vec3s* arg2);
void func_80A0F284(EnSob1* this);
void func_80A0D414(EnSob1* this, GlobalContext* globalCtx);
void func_80A0D4A0(EnSob1* this, GlobalContext* globalCtx);
void func_80A0F2C8(EnSob1* this);
void func_80A0F2FC(EnSob1* this);
void func_80A0CD48(EnSob1* this, GlobalContext* globalCtx, ShopItem* shopItems);
s32 func_80A0F3D4(EnSob1* this, GlobalContext* globalCtx);
void func_80A0DD40(EnSob1* this, GlobalContext* globalCtx);
void func_80A0D258(GlobalContext* globalCtx, EnSob1* this, u8 arg2);
void func_80A0DB78(EnSob1* this, GlobalContext* globalCtx);
s16 func_80A0F1C4(Path* path, s32 arg1, Vec3f* arg2, f32* arg3);
void func_80A0DE64(EnSob1* this, GlobalContext* globalCtx);
void func_80A0D77C(EnSob1* this, GlobalContext* globalCtx);
void func_80A0D2B8(GlobalContext* globalCtx, EnSob1* this);
void func_80A0DCC4(EnSob1* this, GlobalContext* globalCtx);
u16 func_80A0CA38(EnSob1* this, GlobalContext* globalCtx);
s32 func_80A0D188(EnSob1* this, GlobalContext* globalCtx, Input* input);
void func_80A0D0B8(GlobalContext* globalCtx, EnSob1* this);
void func_80A0D904(EnSob1* this, GlobalContext* globalCtx);
void func_80A0C810(SkelAnime* skelAnime, ActorAnimationEntryS* animations, s32 idx);
void func_80A0CCEC(EnSob1* this, GlobalContext* globalCtx);
void func_80A0E0C0(EnSob1* this, GlobalContext* globalCtx);
s32 func_80A0D850(EnSob1* this, GlobalContext* globalCtx);
u8 func_80A0D74C(EnSob1* this, u8 arg1);
u16 func_80A0CC88(EnSob1* this);
void func_80A0D3C4(EnSob1* this, GlobalContext* globalCtx);
void func_80A0D034(GlobalContext* globalCtx, EnSob1* this);
void func_80A0E330(EnSob1* this, GlobalContext* globalCtx);
void func_80A0D320(GlobalContext* globalCtx, EnSob1* this);
s32 func_80A0EE3C(EnSob1* this);
s32 func_80A0E258(GlobalContext* globalCtx, EnSob1* this, Input* input);
void func_80A0E1B8(GlobalContext* globalCtx, EnSob1* this);
void func_80A0DA5C(EnSob1* this, GlobalContext* globalCtx);
s32 func_80A0C8B8(GlobalContext* globalCtx);
void func_80A0E884(EnSob1* this, GlobalContext* globalCtx);
void func_80A0D388(GlobalContext* globalCtx, EnSob1* this);
void func_80A0E554(GlobalContext* globalCtx, EnSob1* this);
void func_80A0DAAC(EnSob1* this, GlobalContext* globalCtx);
void func_80A0E420(GlobalContext* globalCtx, EnSob1* this);
void func_80A0E518(GlobalContext* globalCtx, EnSob1* this, u16 textId);
void func_80A0E4DC(GlobalContext* globalCtx, EnSob1* this, u16 textId);
void func_80A0EA84(EnSob1* this, GlobalContext* globalCtx);
void func_80A0E9E0(EnSob1* this, GlobalContext* globalCtx);
void func_80A0E96C(EnSob1* this, GlobalContext* globalCtx);
void func_80A0EAF8(EnSob1* this, GlobalContext* globalCtx);
void func_80A0ED7C(EnSob1* this);
void func_80A0DFD0(EnSob1* this, GlobalContext* globalCtx);
void func_80A0EBC0(EnSob1* this, GlobalContext* globalCtx);
s32 func_80A0D1F4(EnSob1* this, GlobalContext* globalCtx, Input* input);
s32 func_80A0EDA0(EnSob1* this);
void func_80A0D628(GlobalContext* globalCtx, EnSob1* this);
void func_80A0EEC8(EnSob1* this);
void func_80A0F014(EnSob1* this);
void func_80A0EF48(EnSob1* this);
u16 func_80A0C938(EnSob1* this, GlobalContext* globalCtx);
void func_80A0F470(EnSob1* this, GlobalContext* globalCtx);
void func_80A0F554(EnSob1* this, GlobalContext* globalCtx);
void func_80A0F638(EnSob1* this, GlobalContext* globalCtx);
void func_80A0F39C(EnSob1* this, GlobalContext* globalCtx);
Gfx* func_80A10344(GraphicsContext* gfxCtx);
void func_80A0FADC(GlobalContext* globalCtx, EnSob1* this, f32 x, f32 y, f32 z, u8 drawCursor);
void func_80A0FD4C(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t, f32 dx,
                   f32 dy);
void func_80A0FEE8(GlobalContext* globalCtx, EnSob1* this);

s32 func_80A10290(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
s32 func_80A102C8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80A10308(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);

void func_80A0F6B0(EnSob1* this, GlobalContext* globalCtx);
void func_80A0EC98(EnSob1* this);

/*
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
*/

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

extern ActorAnimationEntryS D_80A10860[];
/*
static ActorAnimationEntryS D_80A10860[] = {
    {&D_06009120, 2.0f, 0, -1, 0, 20},
    {&D_06008268, 1.0f, 0, -1, 2, 0},
    {&D_060087BC, 1.0f, 0, -1, 0, 0},
};
*/

extern Vec3s D_80A108B0[];
/*
static Vec3s D_80A108B0[] = {
    {0x00D0, 0x0283, 0x00D6},
    {0x00A1, 0x0283, 0x00D5},
    {0x012C, 0x0283, 0x0283},
    {0x00A1, 0x0283, 0x00D5},
};
*/

extern u16 D_80A108C8[];
//static u16 D_80A108C8[] = {0x12D6, 0x0BC0, 0x0640, 0x0BC0};

extern u16 D_80A108D0[];
//static u16 D_80A108D0[] = {0x12E3, 0x0BD3, 0x0641, 0x0BD3};

extern u16 D_80A108D8[];
//static u16 D_80A108D8[] = {0x12E6, 0x0BD6, 0x0647, 0x0BD6};

extern u16 D_80A108E0[];
//static u16 D_80A108E0[] = {0x12E1, 0x0BD2, 0x0645, 0x0BD2};

extern u16 D_80A108E8[];
//static u16 D_80A108E8[] = {0x12E5, 0x0BD5, 0x0646, 0x0BD5};

extern u16 D_80A108F0[];
//static u16 D_80A108F0[] = {0x12E4, 0x0BD4, 0x0645 0x0BD4};

extern u16 D_80A108F8[];
//static u16 D_80A108F8[] = {0x12E1, 0x0BD1, 0x0641, 0x0BD1};

extern u16 D_80A10900[];
//static u16 D_80A10900[] = {0x12E3, 0x0BD3, 0x0641, 0x0BD3};

extern f32 D_80A10908[];
//static f32 D_80A10908[] = {0.01f, 0.01f, 0.01f, 0.01f};

extern ShopItem D_80A10918[][3];
/*
static ShopItem D_80A10918[][3] = {
    {
        {SI_POTION_RED_4, 1258, 42, 325},
        {SI_ARROWS_SMALL_1, 1240, 42, 325},
        {SI_SHIELD_HERO_3, 1222, 42, 325},
    },
    {
        {SI_POTION_RED_5, -57, 42, -62},
        {SI_ARROWS_SMALL_2, -75, 42, -62},
        {SI_BOMB_2, -93, 42, -62},
    },
    {
        {SI_BOMB_BAG_20_2, 221, -7, 73},
        {SI_BOMBCHU, 203, -7, 69},
        {SI_BOMB_1, 185, -7, 65},
    },
    {
        {SI_POTION_RED_6, -57, 42, -62},
        {SI_ARROWS_SMALL_3, -75, 42, -62},
        {SI_BOMB_3, -93, 42, -62},
    },
};
*/

extern EnSob1UnkStruct D_80A10978[];
/*
static EnSob1UnkStruct D_80A10978[] = {
    {1170.0f, 1230.0f, 360.0f, 380.0f},
    {-142.0f, -72.0f, -20.0f, 0.0f},
    {138.0f, 200.0f, 72.0f, 16.0f},
    {-142.0f, -72.0f, -20.0f, 0.0f},
}
*/

extern Vec3f D_80A109B8[];
/*
static Vec3f D_80A109B8[] = {
    {1240.0f, 45.0f, 349.0f},
    {-75.0f, 45.0f, -38.0f},
    {197.0f, -4.0f, 93.0f},
    {-75.0f, 45.0f, -38.0f},
}
*/

extern InitChainEntry D_80A109E8[];
/*
static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};
*/

extern EnSob1ActionFunc D_80A109EC[];
/*
static EnSob1ActionFunc D_80A109EC[] = {
    func_80A0F470, func_80A0F554, func_80A0F638, func_80A0F554,
};
*/

extern Vec3f D_80A109FC[];
/*
extern Vec3f D_80A109FC[] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, -4.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, -4.0f, 0.0f},
};
*/

extern UNK_PTR D_80A10A2C[];
//static UNK_PTR D_80A10A2C[] = { &D_060050A0, &D_060058A0, &D_060060A0 };

extern UNK_PTR D_80A10A38[];
//static UNK_PTR D_80A10A38[] = { &D_06010438, &D_06010C38, &D_06011038 };

void func_80A0C810(SkelAnime* skelAnime, ActorAnimationEntryS* animations, s32 idx) {
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

void func_80A0C8AC(EnSob1* this, EnSob1ActionFunc action) {
    this->actionFunc = action;
}

s32 func_80A0C8B8(GlobalContext* globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A);
    }
    return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CUP);
}

u16 func_80A0C938(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->unk3CC == 2) {
        if (gSaveContext.day == 1 && gSaveContext.time >= 0x4000) {
            return 0x648;
        } else if (gSaveContext.weekEventReg[33] & 8) {
            return 0x649;
        } else {
            return 0x64A;
        }
    } else if (this->unk3CC == 0) {
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
    } else if (this->unk3CC == 1) {
        if (player->transformation != PLAYER_FORM_GORON) {
            return 0xBC1;
        }
        return 0xBC2;
    } else if (this->unk3CC == 3) {
        if (player->transformation != PLAYER_FORM_GORON) {
            return 0xBC3;
        }
        return 0xBC4;
    }
    return 0;
}

#ifdef NON_MATCHING
// Matches but jmptable is in late rodata
u16 func_80A0CA38(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->unk3CC == 2) {
        switch (func_8012403C(globalCtx)) {
            case 0:
            case 4:
            case 9:
                return 0x644;
            case 22:
            case 23:
            case 24:
                return 0x64B;
            case 1:
            case 3:
            case 5:
            case 7:
            case 11:
            case 13:
            case 14:
            case 17:
            case 19:
                return 0x685;
            case 6:
            case 8:
            case 12:
            case 15:
                return 0x686;
            case 10:
                return 0x687;
            case 16:
                return 0x688;
            case 18:
                return 0x689;
            case 2:
                return 0x68A;
        }
    } else if (this->unk3CC == 0) {
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
    } else if (this->unk3CC == 1) {
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
    } else if (this->unk3CC == 3) {
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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0CA38.asm")
#endif

u16 func_80A0CC88(EnSob1* this) {
    if (this->unk3CC == 2) {
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

void func_80A0CCEC(EnSob1* this, GlobalContext* globalCtx) {
    this->drawCursor = 0;
    this->stickRightPrompt.isEnabled = false;
    this->stickLeftPrompt.isEnabled = false;
    this->unk3B8 = func_80A0CC88(this);
    func_801518B0(globalCtx, this->unk3B8, &this->actor);
    func_80A0C8AC(this, func_80A0D3C4);
}

void func_80A0CD48(EnSob1* this, GlobalContext* globalCtx, ShopItem* shopItem) {
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

s32 func_80A0CE10(EnSob1* this, GlobalContext* globalCtx, Vec3s* arg2) {
    if (arg2->y != 0x283) {
        this->unk1EB = Object_GetIndex(&globalCtx->objectCtx, arg2->y);
        if (this->unk1EB < 0) {
            return false;
        }
    } else {
        this->unk1EB = -1;
    }
    if (arg2->z != 0x283) {
        this->unk1EC = Object_GetIndex(&globalCtx->objectCtx, arg2->z);
        if (this->unk1EC < 0) {
            return false;
        }
    } else {
        this->unk1EC = -1;
    }
    return true;
}

void EnSob1_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    Vec3s* sp24;

    switch (this->actor.params & 0x1F) {
        case 0:
            this->unk3CC = 0;
            break;
        case 1:
            if (gSaveContext.weekEventReg[33] & 0x80) {
                this->unk3CC = 3;
            } else {
                this->unk3CC = 1;
            }
            break;
        case 2:
            this->unk3CC = 2;
            break;
        default:
            Actor_MarkForDeath(&this->actor);
            return;
    }

    sp24 = &D_80A108B0[this->unk3CC];
    this->objIndex = Object_GetIndex(&globalCtx->objectCtx, sp24->x);
    if (this->objIndex < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (!func_80A0CE10(this, globalCtx, sp24)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    Actor_ProcessInitChain(&this->actor, D_80A109E8);
    func_80A0C8AC(this, func_80A0F6B0);
}

void EnSob1_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A0D034(GlobalContext* globalCtx, EnSob1* this) {
    s16 sp2E;
    s16 sp2C;
    f32 zero = 0.0f;
    s32 pad;

    func_800B8898(globalCtx, &this->items[this->cursorIdx]->actor, &sp2E, &sp2C);
    this->cursorX = sp2E + zero;
    this->cursorY = sp2C + 17.0f;
    this->cursorZ = 1.2f;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D034.asm")
#endif

void func_80A0D0B8(GlobalContext* globalCtx, EnSob1* this) {
    Player* player = PLAYER;

    if (this->cutsceneState == 2) {
        ActorCutscene_Stop(this->unk3A0);
        this->cutsceneState = 0;
    }
    func_800B84D0(&this->actor, globalCtx);
    globalCtx->msgCtx.unk11F22 = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    this->stickRightPrompt.isEnabled = false;
    this->stickLeftPrompt.isEnabled = false;
    player->stateFlags2 &= ~0x20000000;
    globalCtx->interfaceCtx.unk222 = 0;
    globalCtx->interfaceCtx.unk224 = 0;
    func_80A0C8AC(this, func_80A0D4A0);
}

s32 func_80A0D188(EnSob1* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        if (this->unk3CC == 2) {
            func_80A0CCEC(this, globalCtx);
        } else {
            func_80A0D0B8(globalCtx, this);
        }
        return true;
    }
    return false;
}

s32 func_80A0D1F4(EnSob1* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        this->actionFunc = this->prevActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        return true;
    }
    return false;
}

void func_80A0D258(GlobalContext* globalCtx, EnSob1* this, u8 arg2) {
    func_8011552C(globalCtx, 16);
    if (arg2 == 0) {
        func_80A0C8AC(this, func_80A0D77C);
    } else {
        func_80A0D2B8(globalCtx, this);
    }
}

void func_80A0D2B8(GlobalContext* globalCtx, EnSob1* this) {
    func_80A0C8AC(this, func_80A0D904);
    func_80151938(globalCtx, D_80A108C8[this->unk3CC]);
    func_8011552C(globalCtx, 6);
    this->stickRightPrompt.isEnabled = false;
    this->stickLeftPrompt.isEnabled = true;
}

void func_80A0D320(GlobalContext* globalCtx, EnSob1* this) {
    func_80A0C8AC(this, func_80A0DA5C);
    this->unk3B6 = func_80A0C938(this, globalCtx);
    func_80151938(globalCtx, this->unk3B6);
    func_8011552C(globalCtx, 6);
    this->stickRightPrompt.isEnabled = false;
    this->stickLeftPrompt.isEnabled = false;
}

void func_80A0D388(GlobalContext* globalCtx, EnSob1* this) {
    play_sound(NA_SE_SY_CURSOR);
    this->drawCursor = 0;
    func_80A0C8AC(this, func_80A0DAAC);
}

void func_80A0D3C4(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        func_80A0D0B8(globalCtx, this);
    }
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A0D414(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((player->actor.world.pos.x >= 0.0f && player->actor.world.pos.x <= 390.0f) &&
        (player->actor.world.pos.z >= 72.0f && player->actor.world.pos.z <= 365.0f)) {
        func_80A0C8AC(this, func_80A0DD40);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D414.asm")
#endif

void func_80A0D4A0(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    this->unk1F0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->unk3A0 = this->unk3A2;
            ActorCutscene_SetIntentToPlay(this->unk3A0);
            this->cutsceneState = 1;
        }
        player->stateFlags2 |= 0x20000000;
        this->unk3B4 = func_80A0CA38(this, globalCtx);
        func_801518B0(globalCtx, this->unk3B4, &this->actor);
        if ((this->actor.params & 0x1F) == 2) {
            this->unk1F0 = -0x2000;
        }
        func_80A0D258(globalCtx, this, 0);
    } else {
        if ((player->actor.world.pos.x >= this->unk3BC.unk0 && player->actor.world.pos.x <= this->unk3BC.unk4) &&
            (player->actor.world.pos.z >= this->unk3BC.unk8 && player->actor.world.pos.z <= this->unk3BC.unkC)) {
            func_800B8614(&this->actor, globalCtx, 400.0f);
        }
        if (this->unk3BA == 1) {
            this->unk3BA = 0;
            func_80A0D258(globalCtx, this, 0);
        }
    }
}

void func_80A0D628(GlobalContext* globalCtx, EnSob1* this) {
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

u8 func_80A0D74C(EnSob1* this, u8 arg1) {
    if (this->items[arg1] != NULL) {
        return arg1;
    }
    return 0xFF;
}

void func_80A0D77C(EnSob1* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk3A0)) {
            ActorCutscene_StartAndSetFlag(this->unk3A0, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
    }
    if ((talkState == 5) && (func_80147624(globalCtx)) && (!func_80A0D188(this, globalCtx, globalCtx->state.input))) {
        if (this->unk3B4 == 0x68A) {
            func_80A0D0B8(globalCtx, this);
        } else {
            func_80A0D2B8(globalCtx, this);
        }
    }
}

s32 func_80A0D850(EnSob1* this, GlobalContext* globalCtx) {
    switch (globalCtx->msgCtx.choiceIndex) {
        case 0:
            func_8019F208();
            func_80A0D320(globalCtx, this);
            return true;
        case 1:
            func_8019F230();
            if (this->unk3CC == 2) {
                func_80A0CCEC(this, globalCtx);
            } else {
                func_80A0D0B8(globalCtx, this);
            }
            return true;
    }
    return false;
}

void func_80A0D904(EnSob1* this, GlobalContext* globalCtx) {
    s32 pad[2];
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    u8 cursorIdx;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk3A0)) {
            ActorCutscene_StartAndSetFlag(this->unk3A0, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk3A0 = this->unk3A2;
        ActorCutscene_SetIntentToPlay(this->unk3A0);
        this->cutsceneState = 1;
    } else {
        if (talkState == 4) {
            func_8011552C(globalCtx, 6);
            if (!func_80A0D188(this, globalCtx, globalCtx->state.input)) {
                if (!func_80147624(globalCtx) || !func_80A0D850(this, globalCtx)) {
                    if (this->stickAccumX > 0) {
                        cursorIdx = func_80A0D74C(this, 2);
                        if (cursorIdx != 0xFF) {
                            this->cursorIdx = cursorIdx;
                            func_80A0C8AC(this, func_80A0E0C0);
                            func_8011552C(globalCtx, 6);
                            this->stickLeftPrompt.isEnabled = false;
                            play_sound(NA_SE_SY_CURSOR);
                        }
                    }
                }
            }
        }
    }
}

void func_80A0DA5C(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        func_80A0D2B8(globalCtx, this);
    }
}

void func_80A0DAAC(EnSob1* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 2) {
        ActorCutscene_Stop(this->unk3A0);
        this->cutsceneState = 0;
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk3A0 = this->unk3A6;
        ActorCutscene_SetIntentToPlay(this->unk3A0);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk3A0)) {
            ActorCutscene_StartAndSetFlag(this->unk3A0, &this->actor);
            this->cutsceneState = 2;
            func_80A0D2B8(globalCtx, this);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
    }
}

void func_80A0DB78(EnSob1* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    sp2E = this->skelAnime.animCurrentFrame / this->skelAnime.animPlaybackSpeed;
    sp2C = SkelAnime_GetFrameCount(&D_06009120.common) / (s16)this->skelAnime.animPlaybackSpeed;
    Math_SmoothStepToS(&this->actor.world.rot.y,
                       func_80A0F1C4(this->path, this->unk1E4 - 1, &this->actor.world.pos, &sp30), 4, 1000, 1);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_ApproachF(&this->actor.speedXZ, 0.5f, 0.2f, 1.0f);
    if (sp30 < 12.0f) {
        this->actor.speedXZ = 0.0f;
        if (sp2C == sp2E) {
            func_80A0C810(&this->skelAnime, D_80A10860, 1);
            func_80A0C8AC(this, func_80A0DCC4);
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80A0DCC4(EnSob1* this, GlobalContext* globalCtx) {
    s16 animCurrentFrame = this->skelAnime.animCurrentFrame;

    if (SkelAnime_GetFrameCount(&D_06008268.common) == animCurrentFrame) {
        func_80A0C810(&this->skelAnime, D_80A10860, 2);
        func_80A0C8AC(this, func_80A0D4A0);
    }
    func_80A0DE64(this, globalCtx);
}

void func_80A0DD40(EnSob1* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 sp30;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk3A0)) {
            ActorCutscene_StartAndSetFlag(this->unk3A0, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
    }
    if (this->path != NULL) {
        Math_SmoothStepToS(&this->actor.world.rot.y,
                           func_80A0F1C4(this->path, this->unk1E4, &this->actor.world.pos, &sp30), 4, 1000, 1);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->actor.speedXZ = 2.0f;
        if (sp30 < 25.0f) {
            this->unk1E4++;
            if ((this->path->count - 1) < this->unk1E4) {
                this->actor.speedXZ = 0.0f;
                func_80A0C8AC(this, func_80A0DB78);
            }
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_80A0DE64(this, globalCtx);
}

void func_80A0DE64(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk3A0)) {
            ActorCutscene_StartAndSetFlag(this->unk3A0, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->unk3A0 = this->unk3A2;
            ActorCutscene_SetIntentToPlay(this->unk3A0);
            this->cutsceneState = 1;
        }
        player->stateFlags2 |= 0x20000000;
        this->unk3B4 = func_80A0CA38(this, globalCtx);
        func_801518B0(globalCtx, this->unk3B4, &this->actor);
        this->unk3BA = 1;
    } else {
        if ((player->actor.world.pos.x >= this->unk3BC.unk0 && player->actor.world.pos.x <= this->unk3BC.unk4) &&
            (player->actor.world.pos.z >= this->unk3BC.unk8 && player->actor.world.pos.z <= this->unk3BC.unkC)) {
            func_800B8614(&this->actor, globalCtx, 400.0f);
        }
    }
}

void func_80A0DFD0(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCanPlayNext(this->unk3A0)) {
            ActorCutscene_StartAndSetFlag(this->unk3A0, &this->actor);
            player->stateFlags2 |= 0x20000000;
            func_80A0C8AC(this, func_80A0EBC0);
            this->cutsceneState = 2;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->unk3A0 = this->unk3A6;
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80151938(globalCtx, 0x647);
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80A0E0C0(EnSob1* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 2) {
        ActorCutscene_Stop(this->unk3A0);
        this->cutsceneState = 0;
    }
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->unk3A0 = this->unk3A4;
        ActorCutscene_SetIntentToPlay(this->unk3A0);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->unk3A0) != 0) {
            ActorCutscene_StartAndSetFlag(this->unk3A0, &this->actor);
            this->cutsceneState = 2;
            func_80A0D034(globalCtx, this);
            func_80A0C8AC(this, func_80A0E330);
            func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        } else {
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
    }
}

void func_80A0E1B8(GlobalContext* globalCtx, EnSob1* this) {
    u8 curTemp = this->cursorIdx;

    if (this->stickAccumX < 0) {
        if (curTemp != 2) {
            curTemp++;
        } else {
            func_80A0D388(globalCtx, this);
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

s32 func_80A0E258(GlobalContext* globalCtx, EnSob1* this, Input* input) {
    EnGirlA* item = this->items[this->cursorIdx];

    if (func_80A0D188(this, globalCtx, input)) {
        return 1;
    }
    if (func_80A0C8B8(globalCtx)) {
        if (!item->isOutOfStock) {
            this->prevActionFunc = this->actionFunc;
            func_80151938(globalCtx, this->items[this->cursorIdx]->choiceTextId);
            play_sound(NA_SE_SY_DECIDE);
            this->stickRightPrompt.isEnabled = false;
            this->stickLeftPrompt.isEnabled = false;
            this->drawCursor = 0;
            func_80A0C8AC(this, func_80A0E884);
        } else {
            play_sound(NA_SE_SY_ERROR);
        }
        return 1;
    }
    return 0;
}

void func_80A0E330(EnSob1* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    u8 prevCursorIdx = this->cursorIdx;
    u8 cursorIdx;

    if (!func_80A0EE3C(this)) {
        this->unk1E8 = 3;
    } else if (this->unk1E8 != 0) {
        this->unk1E8--;
    } else {
        this->drawCursor = 0xFF;
        this->stickRightPrompt.isEnabled = true;
        func_80A0D034(globalCtx, this);
        if (talkState == 5) {
            func_8011552C(globalCtx, 6);
            if (!func_80A0E258(globalCtx, this, globalCtx->state.input)) {
                func_80A0E1B8(globalCtx, this);
                cursorIdx = this->cursorIdx;
                if (cursorIdx != prevCursorIdx) {
                    func_80151938(globalCtx, this->items[cursorIdx]->actor.textId);
                    play_sound(NA_SE_SY_CURSOR);
                }
            }
        }
    }
}

void func_80A0E420(GlobalContext* globalCtx, EnSob1* this) {
    Player* player = PLAYER;

    func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    globalCtx->msgCtx.unk11F22 = 0x43;
    globalCtx->msgCtx.unk12023 = 4;
    player->stateFlags2 &= ~0x20000000;
    Interface_ChangeAlpha(50);
    this->drawCursor = 0;
    func_80A0C8AC(this, func_80A0EA84);
}

void func_80A0E4DC(GlobalContext* globalCtx, EnSob1* this, u16 textId) {
    func_80151938(globalCtx, textId);
    func_80A0C8AC(this, func_80A0E96C);
}

void func_80A0E518(GlobalContext* globalCtx, EnSob1* this, u16 textId) {
    func_80151938(globalCtx, textId);
    func_80A0C8AC(this, func_80A0E9E0);
}

#ifdef NON_MATCHING
// Matches but jmptable is in late rodata
void func_80A0E554(GlobalContext* globalCtx, EnSob1* this) {
    EnGirlA* item = this->items[this->cursorIdx];
    EnGirlA* item2;

    switch (item->canBuyFunc(globalCtx, item)) {
        case 0:
            if (this->cutsceneState == 2) {
                ActorCutscene_Stop(this->unk3A0);
                this->cutsceneState = 0;
            }
            func_8019F208();
            item2 = this->items[this->cursorIdx];
            item2->buyFanfareFunc(globalCtx, item2);
            func_80A0E420(globalCtx, this);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case 1:
            func_8019F208();
            item->buyFunc(globalCtx, item);
            if ((this->unk3CC == 1) && (item->actor.params == 0x20)) {
                func_80A0E518(globalCtx, this, 0xBD7);
            } else if ((this->unk3CC == 0) && (item->actor.params == 0x1D)) {
                func_80A0E518(globalCtx, this, 0x12E7);
            } else if ((this->unk3CC == 3) && (item->actor.params == 0x23)) {
                func_80A0E518(globalCtx, this, 0xBD7);
            } else {
                func_80A0E518(globalCtx, this, D_80A108D8[this->unk3CC]);
            }
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item->boughtFunc(globalCtx, item);
            break;
        case 2:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, D_80A108D0[this->unk3CC]);
            break;
        case 3:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, D_80A108F0[this->unk3CC]);
            break;
        case 4:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, D_80A108E8[this->unk3CC]);
            break;
        case 5:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, D_80A108E0[this->unk3CC]);
            break;
        case 6:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, D_80A108F8[this->unk3CC]);
            break;
        case 7:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, D_80A10900[this->unk3CC]);
            break;
        case 8:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, 0x658);
            break;
        case 9:
            play_sound(NA_SE_SY_ERROR);
            func_80A0E4DC(globalCtx, this, 0x659);
            break;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E554.asm")
#endif

void func_80A0E884(EnSob1* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (func_80A0EDA0(this) && talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (!func_80A0D1F4(this, globalCtx, globalCtx->state.input) && func_80147624(globalCtx)) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_80A0E554(globalCtx, this);
                    break;
                case 1:
                    func_8019F230();
                    this->actionFunc = this->prevActionFunc;
                    func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
                    break;
            }
        }
    }
}

void func_80A0E96C(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5) {
        if (func_80147624(globalCtx)) {
            this->actionFunc = this->prevActionFunc;
            func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        }
    }
}

void func_80A0E9E0(EnSob1* this, GlobalContext* globalCtx) {
    EnGirlA* item;

    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->shopItemSelectedTween = 0.0f;
        func_80A0ED7C(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        this->actionFunc = this->prevActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
    }
}

void func_80A0EA84(EnSob1* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        func_80A0C8AC(this, func_80A0EAF8);
    } else {
        func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    }
}

void func_80A0EAF8(EnSob1* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        globalCtx->msgCtx.unk11F22 = 0x43;
        globalCtx->msgCtx.unk12023 = 4;
        func_80A0C8AC(this, func_80A0DFD0);
        if (this->cutsceneState == 0) {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->unk3A0 = this->unk3A6;
            ActorCutscene_SetIntentToPlay(this->unk3A0);
        }
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80A0EBC0(EnSob1* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    EnGirlA* item;

    if ((func_80152498(&globalCtx->msgCtx) == 5) && (func_80147624(globalCtx))) {
        func_80A0ED7C(this);
        item = this->items[this->cursorIdx];
        item->restockFunc(globalCtx, item);
        player->actor.shape.rot.y += 0x8000;
        player->stateFlags2 |= 0x20000000;
        func_801518B0(globalCtx, this->unk3B4, &this->actor);
        func_80A0D258(globalCtx, this, 1);
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void func_80A0EC98(EnSob1* this) {
    Vec3f selectedItemPosition = D_80A109B8[this->unk3CC];
    u8 i = this->cursorIdx;
    EnGirlA* item;
    ShopItem* shopItem;
    Vec3f worldPos;

    shopItem = &D_80A10918[this->unk3CC][i];
    item = this->items[i];

    worldPos.x = shopItem->x + (selectedItemPosition.x - shopItem->x) * this->shopItemSelectedTween;
    worldPos.y = shopItem->y + (selectedItemPosition.y - shopItem->y) * this->shopItemSelectedTween;
    worldPos.z = shopItem->z + (selectedItemPosition.z - shopItem->z) * this->shopItemSelectedTween;

    item->actor.world.pos.x = worldPos.x;
    item->actor.world.pos.y = worldPos.y;
    item->actor.world.pos.z = worldPos.z;
}

void func_80A0ED7C(EnSob1* this) {
    this->shopItemSelectedTween = 0.0f;
    func_80A0EC98(this);
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
s32 func_80A0EDA0(EnSob1* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 1.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween >= 0.85f) {
        this->shopItemSelectedTween = 1.0f;
    }
    func_80A0EC98(this);
    if (this->shopItemSelectedTween == 1.0f) {
        return true;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EDA0.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
s32 func_80A0EE3C(EnSob1* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 0.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween <= 0.15f) {
        this->shopItemSelectedTween = 0.0f;
    }
    func_80A0EC98(this);
    if (this->shopItemSelectedTween == 0.0f) {
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EE3C.asm")
#endif

void func_80A0EEC8(EnSob1* this) {
    EnGirlA** items = this->items;
    EnGirlA* item;
    s32 i;

    for (i = 0; i < 3; i++, items++) {
        item = *items;
        if (item != NULL) {
            if (this->actionFunc != func_80A0E884 && this->actionFunc != func_80A0E96C && this->drawCursor == 0) {
                item->isSelected = false;
            } else {
                item->isSelected = this->cursorIdx == i ? true : false;
            }
        }
    }
}

#ifdef NON_MATCHING
// Matches but floats are in laterodata
void func_80A0EF48(EnSob1* this) {
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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EF48.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A0F014(EnSob1* this) {
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

    this->stickRightPrompt.arrowColorR = ColChanMix(255, 155.0f, arrowAnimTween);
    this->stickRightPrompt.arrowColorG = ColChanMix(new_var2, 155.0f, arrowAnimTween);
    this->stickRightPrompt.arrowColorB = ColChanMix(0, -100, arrowAnimTween);
    this->stickRightPrompt.arrowColorA = ColChanMix(200, 50.0f, arrowAnimTween);

    this->stickLeftPrompt.arrowColorR = (new_var2 - ((s32)new_var3)) & 0xFF;
    this->stickLeftPrompt.arrowColorG = (255 - ((s32)new_var3)) & 0xFF;
    this->stickLeftPrompt.arrowColorB = ColChanMix(0, -100.0f, arrowAnimTween);
    this->stickLeftPrompt.arrowColorA = ColChanMix(200, 50.0f, arrowAnimTween);

    this->stickLeftPrompt.arrowTexX = 290.0f;
    this->stickRightPrompt.arrowTexX = 33.0f;

    this->stickLeftPrompt.stickTexX = 274.0f;
    this->stickLeftPrompt.stickTexX += 8.0f * stickAnimTween;
    this->stickRightPrompt.stickTexX = 49.0f;
    this->stickRightPrompt.stickTexX -= 8.0f * stickAnimTween;

    this->stickRightPrompt.arrowTexY = this->stickLeftPrompt.arrowTexY = 91.0f;
    this->stickRightPrompt.stickTexY = this->stickLeftPrompt.stickTexY = 95.0f;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F014.asm")
#endif

#ifdef NON_MATCHING
// Matches but float is in late rodata
s16 func_80A0F1C4(Path* path, s32 arg1, Vec3f* arg2, f32* arg3) {
    Vec3s* points;
    f32 x;
    f32 z;

    if (path != NULL) {
        points = (Vec3s*)Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        x = points->x - arg2->x;
        z = points->z - arg2->z;
    } else {
        x = 0.0f;
        z = 0.0f;
    }
    *arg3 = SQ(x) + SQ(z);
    return Math_Acot2F(z, x) * (0x8000 / M_PI);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F1C4.asm")
#endif

void func_80A0F284(EnSob1* this) {
    this->unk3A2 = this->actor.cutscene;
    this->unk3A4 = ActorCutscene_GetAdditionalCutscene(this->unk3A2);
    this->unk3A6 = ActorCutscene_GetAdditionalCutscene(this->unk3A4);
}

void func_80A0F2C8(EnSob1* this) {
    s16 decr;

    decr = this->blinkTimer - 1;
    if (decr != 0) {
        this->blinkTimer = decr;
    } else {
        this->blinkFunc = func_80A0F2FC;
    }
}

void func_80A0F2FC(EnSob1* this) {
    s16 decr = this->blinkTimer - 1;
    s16 eyeTextureIdxTemp;

    if (decr != 0) {
        this->blinkTimer = decr;
    } else {
        eyeTextureIdxTemp = this->eyeTextureIdx + 1;
        if (eyeTextureIdxTemp > 2) {
            this->eyeTextureIdx = 0;
            this->blinkTimer = (s32)(Rand_ZeroOne() * 60.0f) + 20;
            this->blinkFunc = func_80A0F2C8;
        } else {
            this->eyeTextureIdx = eyeTextureIdxTemp;
            this->blinkTimer = 1;
        }
    }
}

void func_80A0F39C(EnSob1* this, GlobalContext* globalCtx) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk1EC].segment);
}

s32 func_80A0F3D4(EnSob1* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->objIndex)) {
        if (this->unk1EB >= 0 && !Object_IsLoaded(&globalCtx->objectCtx, this->unk1EB)) {
            return 0;
        }
        if (this->unk1EC >= 0 && !Object_IsLoaded(&globalCtx->objectCtx, this->unk1EC)) {
            return 0;
        }
        return 1;
    }
    return 0;
}

void func_80A0F470(EnSob1* this, GlobalContext* globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600D208, NULL, this->limbDrawTable, this->transitionDrawTable,
                     20);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk1EC].segment);
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600078C, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_0600078C.common), 0,
                         0.0f);
    this->actor.draw = func_80A10368;
    this->actionFunc2 = func_80A0F39C;
}

void func_80A0F554(EnSob1* this, GlobalContext* globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06011AC8, NULL, this->limbDrawTable, this->transitionDrawTable,
                     18);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->unk1EC].segment);
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060000FC, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_060000FC.common), 0,
                         0.0f);
    this->actor.draw = func_80A104E4;
    this->actionFunc2 = func_80A0F39C;
}

void func_80A0F638(EnSob1* this, GlobalContext* globalCtx) {
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06009220, &D_06009120, this->limbDrawTable,
                     this->transitionDrawTable, 16);
    this->actor.draw = func_80A10608;
    this->actionFunc2 = NULL;
    this->skelAnime.animPlaybackSpeed = 2.0f;
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A0F6B0(EnSob1* this, GlobalContext* globalCtx) {
    ShopItem* shopItems;
    EnSob1UnkStruct* unkStruct;
    Vec3f* worldPos;

    // Possibly fake temps
    EnSob1* this2;
    u32 maxColor = 255;

    if (func_80A0F3D4(this, globalCtx)) {
        this->actor.flags &= ~0x10;
        this->actor.objBankIndex = this->objIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        worldPos = &D_80A109FC[this->unk3CC];
        this->actor.world.pos.x += worldPos->x;
        this->actor.world.pos.y += worldPos->y;
        this->actor.world.pos.z += worldPos->z;
        shopItems = D_80A10918[this->unk3CC];
        if ((this->unk3CC == 2) && (gSaveContext.weekEventReg[33] & 8)) {
            D_80A10918[this->unk3CC][0].shopItemId = SI_BOMB_BAG_30_2;
        }

        this->cutsceneState = 0;
        func_80A0F284(this);
        this->unk3A0 = this->unk3A2;
        ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
        D_80A109EC[this->unk3CC](this, globalCtx);
        this->actor.colChkInfo.mass = 0xFF;
        this->actor.colChkInfo.cylRadius = 50;
        this->unk3BA = 0;
        this->unk1E4 = 0;

        if (this->unk3CC == 2) {
            this->path = func_8013D648(globalCtx, (this->actor.params & 0x3E0) >> 5, 0x1F);
        }
        if (this->unk3CC == 2) {
            func_80A0C8AC(this, func_80A0D414);
        } else {
            func_80A0C8AC(this, func_80A0D4A0);
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

        this2->stickRightPrompt.stickColorR = 200;
        this2->stickRightPrompt.stickColorG = 200;
        this2->stickRightPrompt.stickColorB = 200;
        this2->stickRightPrompt.stickColorA = 180;
        this2->stickRightPrompt.stickTexX = 49.0f;
        this2->stickRightPrompt.stickTexY = 95.0f;
        this2->stickRightPrompt.arrowColorR = maxColor;
        this2->stickRightPrompt.arrowColorG = maxColor;
        this2->stickRightPrompt.arrowColorB = 0;
        this2->stickRightPrompt.arrowColorA = 200;
        this2->stickRightPrompt.arrowTexX = 33.0f;
        this2->stickRightPrompt.arrowTexY = 91.0f;
        this2->stickRightPrompt.texZ = 1.0f;
        this2->stickRightPrompt.isEnabled = 0;

        if (1) {}

        this2->stickLeftPrompt.stickColorR = 200;
        this2->stickLeftPrompt.stickColorG = 200;
        this2->stickLeftPrompt.stickColorB = 200;
        this2->stickLeftPrompt.stickColorA = 180;
        this2->stickLeftPrompt.stickTexX = 274.0f;
        this2->stickLeftPrompt.stickTexY = 95.0f;
        this2->stickLeftPrompt.arrowColorR = maxColor;
        this2->stickLeftPrompt.arrowColorG = 0;
        this2->stickLeftPrompt.arrowColorB = 0;
        this2->stickLeftPrompt.arrowColorA = 200;
        this2->stickLeftPrompt.arrowTexX = 290.0f;
        this2->stickLeftPrompt.arrowTexY = 91.0f;
        this2->stickLeftPrompt.texZ = 1.0f;
        this2->stickLeftPrompt.isEnabled = 0;

        this2->arrowAnimState = 0;
        this2->stickAnimState = 0;
        this2->arrowAnimTween = 0.0f;
        this2->stickAnimTween = 0.0f;
        this2->shopItemSelectedTween = 0.0f;

        this2->actor.gravity = 0.0f;
        this2->unk3BC = D_80A10978[this2->unk3CC];
        Actor_SetScale(&this2->actor, D_80A10908[this2->unk3CC]);
        func_80A0CD48(this2, globalCtx, shopItems);
        this->unk1EE = this->unk1F0 = 0;
        this2->blinkTimer = 20;
        this2->eyeTextureIdx = 0;
        this->blinkFunc = func_80A0F2C8;
        this->actor.flags &= ~1;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F6B0.asm")
#endif

void EnSob1_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1ActionFunc actionFunc2;
    EnSob1* this = THIS;

    if (this->actionFunc != func_80A0F6B0) {
        this->blinkFunc(this);
        func_80A0D628(globalCtx, this);
        func_80A0EEC8(this);
        func_80A0F014(this);
        func_80A0EF48(this);
        Math_StepToS(&this->unk1EE, this->unk1F0, 0x190);
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

void func_80A0FADC(GlobalContext* globalCtx, EnSob1* this, f32 x, f32 y, f32 z, u8 drawCursor) {
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

void func_80A0FD4C(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t, f32 dx,
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

void func_80A0FEE8(GlobalContext* globalCtx, EnSob1* this) {
    s32 drawStickRightPrompt = this->stickRightPrompt.isEnabled;
    s32 drawStickLeftPrompt = this->stickLeftPrompt.isEnabled;

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
            func_80A0FD4C(globalCtx, this->stickRightPrompt.arrowColorR, this->stickRightPrompt.arrowColorG,
                          this->stickRightPrompt.arrowColorB, this->stickRightPrompt.arrowColorA,
                          this->stickRightPrompt.arrowTexX, this->stickRightPrompt.arrowTexY,
                          this->stickRightPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_80A0FD4C(globalCtx, this->stickLeftPrompt.arrowColorR, this->stickLeftPrompt.arrowColorG,
                          this->stickLeftPrompt.arrowColorB, this->stickLeftPrompt.arrowColorA,
                          this->stickLeftPrompt.arrowTexX, this->stickLeftPrompt.arrowTexY, this->stickLeftPrompt.texZ,
                          0, 0, 1.0f, 1.0f);
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
            func_80A0FD4C(globalCtx, this->stickRightPrompt.stickColorR, this->stickRightPrompt.stickColorG,
                          this->stickRightPrompt.stickColorB, this->stickRightPrompt.stickColorA,
                          this->stickRightPrompt.stickTexX, this->stickRightPrompt.stickTexY,
                          this->stickRightPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_80A0FD4C(globalCtx, this->stickLeftPrompt.stickColorR, this->stickLeftPrompt.stickColorG,
                          this->stickLeftPrompt.stickColorB, this->stickLeftPrompt.stickColorA,
                          this->stickLeftPrompt.stickTexX, this->stickLeftPrompt.stickTexY, this->stickLeftPrompt.texZ,
                          0, 0, 1.0f, 1.0f);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80A10290(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnSob1* this = THIS;

    if (limbIndex == 15) {
        rot->x += this->unk1EE;
    }
    return 0;
}

s32 func_80A102C8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnSob1* this = THIS;

    if (limbIndex == 15) {
        SysMatrix_InsertXRotation_s(this->unk1EE, MTXMODE_APPLY);
    }
    return 0;
}

void func_80A10308(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (limbIndex == 11) {
        gSPDisplayList(POLY_OPA_DISP++, D_06000970);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

Gfx* func_80A10344(GraphicsContext* gfxCtx) {
    Gfx* dList;
    Gfx* dListHead;

    dList = dListHead = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 2);
    gSPEndDisplayList(dListHead++);

    return dList;
}

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A10368(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 0x00, 0x00, 0x00, 0xFF);
    gSPSegment(POLY_OPA_DISP++, 0x0C, func_80A10344(globalCtx->state.gfxCtx));
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A10A2C[this->eyeTextureIdx]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80A10290, NULL, &this->actor);
    for (i = 0; i < 3; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }
    func_80A0FADC(globalCtx, this, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    func_80A0FEE8(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A10368.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A104E4(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A10A38[this->eyeTextureIdx]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, &this->actor);
    for (i = 0; i < 3; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }
    func_80A0FADC(globalCtx, this, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    func_80A0FEE8(globalCtx, this);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A104E4.asm")
#endif

#ifdef NON_MATCHING
// Matches but floats are in late rodata
void func_80A10608(Actor* thisx, GlobalContext* globalCtx) {
    EnSob1* this = THIS;
    s32 pad;
    u32 frames;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(&D_06005458));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80A102C8, func_80A10308, &this->actor);
    for (i = 0; i < 3; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }
    func_80A0FADC(globalCtx, this, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    func_80A0FEE8(globalCtx, this);
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
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A10608.asm")
#endif
