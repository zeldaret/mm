#include "z_en_fsn.h"

#define FLAGS 0x00000019

#define THIS ((EnFsn*)thisx)

#define ColChanMix(c1, c2, m) (c1 - (s32)(c2 * m)) & 0xFF

void EnFsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFsn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE4CD8(EnFsn* this);
void func_80AE2F78(EnFsn* this, GlobalContext* globalCtx);
void func_80AE4B70(EnFsn* this, GlobalContext* globalCtx);
s32 func_80AE2298(void);
void func_80AE2438(EnFsn* this, GlobalContext* globalCtx);
void func_80AE30F8(EnFsn* this, GlobalContext* globalCtx);
void func_80AE1C54(EnFsn* this, GlobalContext* globalCtx);
void func_80AE4BF4(EnFsn* this, GlobalContext* globalCtx);
void func_80AE2340(EnFsn* this);
void func_80AE32D4(EnFsn* this, GlobalContext* globalCtx);
u16 func_80AE1BF0(GlobalContext* globalCtx);
void func_80AE3474(EnFsn* this, GlobalContext* globalCtx);
void func_80AE3BC4(EnFsn* this, GlobalContext* globalCtx);
s16 func_80AE21C8(void);
s16 func_80AE2234(u32 arg0);
void func_80AE3644(EnFsn* this, GlobalContext* globalCtx);
void func_80AE352C(EnFsn* this, GlobalContext* globalCtx);
void func_80AE4B20(EnFsn* this, GlobalContext* globalCtx);
void func_80AE3CF0(EnFsn* this, GlobalContext* globalCtx);
s32 func_80AE25D4(EnFsn* this, GlobalContext* globalCtx, Input* input);
void func_80AE4A1C(EnFsn* this, GlobalContext* globalCtx);
void func_80AE1F5C(EnFsn* this);
void func_80AE38E0(EnFsn* this, GlobalContext* globalCtx);
void func_80AE3880(EnFsn* this, GlobalContext* globalCtx);
void func_80AE2524(EnFsn* this, GlobalContext* globalCtx);
void func_80AE1E58(EnFsn* this, GlobalContext* globalCtx);
void func_80AE4424(EnFsn* this, GlobalContext* globalCtx);
s32 func_80AE2760(EnFsn* this, GlobalContext* globalCtx);
u8 func_80AE2028(EnFsn* this);
void func_80AE3F40(EnFsn* this, GlobalContext* globalCtx);
void func_80AE3A68(EnFsn* this, GlobalContext* globalCtx);
void func_80AE3D50(EnFsn* this, GlobalContext* globalCtx);
void func_80AE26D4(EnFsn* this, GlobalContext* globalCtx);
void func_80AE4028(EnFsn* this, GlobalContext* globalCtx);
void func_80AE3E4C(EnFsn* this, GlobalContext* globalCtx);
s32 func_80AE2BE0(EnFsn* this);
s32 func_80AE28B0(EnFsn* this, GlobalContext* globalCtx, Input* input);
void func_80AE2074(EnFsn* this);
void func_80AE4638(EnFsn* this, GlobalContext* globalCtx);
void func_80AE4828(EnFsn* this, GlobalContext* globalCtx);
void func_80AE2A98(EnFsn* this);
s32 func_80AE1B70(GlobalContext* globalCtx);
void func_80AE44DC(EnFsn* this, GlobalContext* globalCtx);
void func_80AE4120(EnFsn* this, GlobalContext* globalCtx);
s32 func_80AE2B44(EnFsn* this);
s32 func_80AE2670(EnFsn* this, GlobalContext* globalCtx, Input* input);
void func_80AE41FC(EnFsn* this, GlobalContext* globalCtx);
void func_80AE45C4(EnFsn* this, GlobalContext* globalCtx);
void func_80AE1EF4(EnFsn* this, GlobalContext* globalCtx);
void func_80AE2974(EnFsn* this, GlobalContext* globalCtx);
void func_80AE2C6C(EnFsn* this);
void func_80AE2CFC(EnFsn* this);
void func_80AE2DC8(EnFsn* this);
void func_80AE4D28(EnFsn* this);
s32 func_80AE57E8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80AE5910(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
void func_80AE502C(EnFsn* this, GlobalContext* globalCtx, f32 x, f32 y, f32 z, u8 drawCursor);
void func_80AE5440(EnFsn* this, GlobalContext* globalCtx);
void func_80AE52A4(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t, f32 dx,
                   f32 dy);

extern UNK_TYPE D_0401F740;
extern UNK_TYPE D_0401F8C0;
extern UNK_TYPE D_0401F7C0;
extern AnimationHeader D_06012C34;
extern AnimationHeader D_060131FC;
extern AnimationHeader D_0600C58C;
extern AnimationHeader D_0600E3EC;
extern AnimationHeader D_0600F00C;
extern AnimationHeader D_0600CB3C;
extern AnimationHeader D_0600D354;
extern AnimationHeader D_060138B0;
extern AnimationHeader D_0601430C;
extern AnimationHeader D_0600B9D8;
extern AnimationHeader D_0600C26C;
extern AnimationHeader D_0600DE34;
extern FlexSkeletonHeader D_06013320;
extern UNK_TYPE D_06005BC0;
extern UNK_TYPE D_06006D40;
extern UNK_TYPE D_06007140;
extern Gfx D_0600F180[];
extern Gfx D_0600F218[];


const ActorInit En_Fsn_InitVars = {
    ACTOR_EN_FSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FSN,
    sizeof(EnFsn),
    (ActorFunc)EnFsn_Init,
    (ActorFunc)EnFsn_Destroy,
    (ActorFunc)EnFsn_Update,
    (ActorFunc)EnFsn_Draw,
};

ActorAnimationEntryS D_80AE5B20[] = {
    { &D_06012C34, 1.0f, 0, -1, 0, 0 },  { &D_060131FC, 1.0f, 0, -1, 0, 0 }, { &D_0600C58C, 1.0f, 0, -1, 2, 0 },
    { &D_0600C58C, -1.0f, 0, -1, 2, 0 }, { &D_0600E3EC, 1.0f, 0, -1, 2, 0 }, { &D_0600F00C, 1.0f, 0, -1, 0, 0 },
    { &D_0600CB3C, 1.0f, 0, -1, 2, 0 },  { &D_0600D354, 1.0f, 0, -1, 0, 0 }, { &D_060138B0, 1.0f, 0, -1, 2, 0 },
    { &D_0601430C, 1.0f, 0, -1, 0, 0 },  { &D_0600B9D8, 1.0f, 0, -1, 2, 0 }, { &D_0600C26C, 1.0f, 0, -1, 0, 0 },
    { &D_0600DE34, 1.0f, 0, -1, 2, 0 },
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

static Vec3f D_80AE5C1C[3] = {
    { -5.0f, 35.0f, -95.0f },
    { 13.0f, 35.0f, -95.0f },
    { 31.0f, 35.0f, -95.0f },
};

s32 func_80AE1B70(GlobalContext* globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A);
    }
    return CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B) ||
           CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CUP);
}

u16 func_80AE1BF0(GlobalContext* globalCtx) {

    switch (Player_GetMask(globalCtx)) {
        case PLAYER_MASK_NONE:
            return 0x29CC;
        case PLAYER_MASK_DEKU_MASK:
            return 0x29FC;
        case PLAYER_MASK_GORON_MASK:
        case PLAYER_MASK_ZORA_MASK:
            return 0x29FD;
        case PLAYER_MASK_KAFEIS_MASK:
            return 0x2364;
        default:
            return 0x29FE;
    }
}

void func_80AE1C54(EnFsn* this, GlobalContext* globalCtx) {
    switch (this->unk376) {
        case 0:
            if (!(gSaveContext.weekEventReg[0x50] & 0x10)) {
                this->unk376 = 0x29E0;
                break;
            } else {
                this->unk376 = 0x29E4;
                this->unk44E |= 1;
                break;
            }
        case 0x29E0:
            if (INV_CONTENT(ITEM_MASK_KEATON) == ITEM_MASK_KEATON) {
                this->unk44E |= 2;
                this->unk44E |= 8;
                this->unk37C = 0xA1;
                gSaveContext.weekEventReg[0x50] |= 0x10;
                this->unk376 = 0x29F1;
                break;
            } else {
                this->unk376 = 0x29E1;
                break;
            }
        case 0x29E1:
            this->unk376 = 0x29E2;
            break;
        case 0x29E2:
            this->unk44E |= 2;
            this->unk44E |= 4;
            this->unk37C = 0x80;
            this->unk376 = 0x29E3;
            break;
        case 0x29E3:
            this->unk44E |= 2;
            this->unk44E |= 8;
            this->unk37C = 0xA1;
            gSaveContext.weekEventReg[0x50] |= 0x10;
            this->unk376 = 0x29F1;
            break;
        case 0x29F1:
            this->unk376 = 0x29E4;
            this->unk44E |= 1;
            break;
    }
    func_801518B0(globalCtx, this->unk376, &this->actor);
    if (this->unk44E & 1) {
        if (this->unk44E & 8) {
            this->unk44E &= ~8;
            func_80151BB4(globalCtx, 34);
        }
        if (this->unk44E & 4) {
            this->unk44E &= ~4;
            func_80151BB4(globalCtx, 33);
        }
        func_80151BB4(globalCtx, 3);
    }
}

void func_80AE1E58(EnFsn* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx) && this->cutsceneState == 0) {
        func_800B84D0(&this->actor, globalCtx);
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
        if (!(this->actor.params & 1)) {
            this->actor.textId = 0;
        }
        this->actionFunc = func_80AE3D50;
    }
}

void func_80AE1EF4(EnFsn* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80AE1F5C(EnFsn* this) {
    if (this->cutsceneState == 2 && this->unk372 != this->cutscene && this->actor.textId == 0x29CE) {
        ActorCutscene_Stop(this->cutscene);
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->unk372;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_Start(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

u8 func_80AE2028(EnFsn* this) {
    if (this->unk384[0] != -1) {
        return 0;
    }
    if (this->unk384[1] != -1) {
        return 1;
    }
    if (this->unk384[2] != -1) {
        return 2;
    }
    return 0xFF;
}

void func_80AE2074(EnFsn* this) {
    u8 cursorScan = this->cursorIdx;

    if (this->stickAccumX > 0) {
        if (cursorScan != this->unk38A - 1) {
            while (cursorScan != this->unk38A - 1) {
                cursorScan++;
                if (this->unk384[cursorScan] != -1) {
                    this->cursorIdx = cursorScan;
                    break;
                }
            }
        } else {
            if (this->unk384[cursorScan] != -1) {
                this->cursorIdx = cursorScan;
            }
        }
    } else if (this->stickAccumX < 0) {
        if (cursorScan != 0) {
            while (cursorScan != 0) {
                cursorScan--;
                if (this->unk384[cursorScan] != -1) {
                    this->cursorIdx = cursorScan;
                    break;
                } else if (cursorScan == 0) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->drawCursor = 0;
                    this->actionFunc = func_80AE4120;
                    break;
                }
            }
        } else {
            play_sound(NA_SE_SY_CURSOR);
            this->drawCursor = 0;
            this->actionFunc = func_80AE4120;
            if (this->unk384[cursorScan] != -1) {
                this->cursorIdx = cursorScan;
            }
        }
    }
}

s16 func_80AE21C8(void) {
    if (!(gSaveContext.weekEventReg[0x21] & 4) && CURRENT_DAY == 3) {
        if (!(gSaveContext.weekEventReg[0x21] & 8) && !(gSaveContext.weekEventReg[0x4F] & 0x40)) {
            return SI_BOMB_BAG_30_1;
        }
        return SI_MASK_ALL_NIGHT;
    }
    return 0;
}

s16 func_80AE2234(u32 arg0) {
    switch (arg0) {
        case 0x12:
            return SI_BOTTLE;
        case 0x10:
            return SI_SWORD_GREAT_FAIRY;
        case 0x4D:
            return SI_SWORD_KOKIRI;
        case 0x4E:
            return SI_SWORD_RAZOR;
        case 0x4F:
            return SI_SWORD_GILDED;
    }
    return 0;
}

s32 func_80AE2298(void) {
    if (CURRENT_DAY != 3) {
        if (((gSaveContext.roomInf[126][5] & 0xFF000000) >> 0x18) ||
            ((gSaveContext.roomInf[126][5] & 0xFF0000) >> 0x10)) {
            return 1;
        }
        return 0;
    } else {
        if (((gSaveContext.roomInf[126][5] & 0xFF000000) >> 0x18) ||
            ((gSaveContext.roomInf[126][5] & 0xFF0000) >> 0x10) || !(gSaveContext.weekEventReg[0x21] & 4)) {
            return 1;
        }
        return 0;
    }
}

void func_80AE2340(EnFsn* this) {
    u32 sp1C = (gSaveContext.roomInf[126][5] & 0xFF000000) >> 0x18;
    u32 sp18 = (gSaveContext.roomInf[126][5] & 0xFF0000) >> 0x10;
    s16 itemId;

    this->unk380 = this->unk382 = 0;
    this->unk384[0] = this->unk384[1] = this->unk384[2] = 0;

    itemId = func_80AE21C8();
    this->unk384[this->unk38A] = itemId;
    if (itemId != 0) {
        this->unk38A += 1;
    }
    itemId = func_80AE2234(sp1C);
    this->unk384[this->unk38A] = itemId;
    if (itemId != 0) {
        this->unk380 = this->unk38A;
        this->unk38A += 1;
    }
    itemId = func_80AE2234(sp18);
    this->unk384[this->unk38A] = itemId;
    if (itemId != 0) {
        this->unk382 = this->unk38A;
        this->unk38A += 1;
    }
    this->unk38C = this->unk38A;
}

void func_80AE2438(EnFsn* this, GlobalContext* globalCtx) {
    s32 i;

    func_80AE2340(this);
    for (i = 0; i < this->unk38A; i++) {
        if (this->unk384[i] < 0) {
            this->items[i] = NULL;
        } else {
            this->items[i] = (EnGirlA*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA, D_80AE5C1C[i].x,
                                                   D_80AE5C1C[i].y, D_80AE5C1C[i].z, 0, 0, 0, this->unk384[i]);
        }
    }
}

void func_80AE2524(EnFsn* this, GlobalContext* globalCtx) {
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
    globalCtx->interfaceCtx.unk_222 = 0;
    globalCtx->interfaceCtx.unk_224 = 0;
    this->actor.textId = 0;
    this->actionFunc = func_80AE30F8;
}

s32 func_80AE25D4(EnFsn* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        if (CURRENT_DAY == 3) {
            this->actor.textId = 0x29DF;
        } else {
            this->actor.textId = 0x29D1;
        }
        func_801518B0(globalCtx, this->actor.textId, &this->actor);
        func_80151BB4(globalCtx, 3);
        this->actionFunc = func_80AE4424;
        return 1;
    }
    return 0;
}

s32 func_80AE2670(EnFsn* this, GlobalContext* globalCtx, Input* input) {
    if (CHECK_BTN_ALL(input[0].press.button, BTN_B)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        return 1;
    }
    return 0;
}

void func_80AE26D4(EnFsn* this, GlobalContext* globalCtx) {
    s16 sp2E;
    s16 sp2C;
    f32 xOffset = 0.0f;
    f32 yOffset = 17.0f;

    func_800B8898(globalCtx, &this->items[this->cursorIdx]->actor, &sp2E, &sp2C);
    this->cursorX = sp2E + xOffset;
    this->cursorY = sp2C + yOffset;
    this->cursorZ = 1.2f;
}

s32 func_80AE2760(EnFsn* this, GlobalContext* globalCtx) {
    switch (globalCtx->msgCtx.choiceIndex) {
        case 0:
            func_8019F208();
            if (CURRENT_DAY != 3) {
                this->actor.textId = 0x29FB;
            } else {
                if (gSaveContext.weekEventReg[0x21] & 4) {
                    this->actor.textId = 0x29FF;
                } else if (!(gSaveContext.weekEventReg[0x21] & 8) && !(gSaveContext.weekEventReg[0x4F] & 0x40)) {
                    this->actor.textId = 0x29D7;
                } else {
                    this->actor.textId = 0x29D8;
                }
            }
            func_801518B0(globalCtx, this->actor.textId, &this->actor);
            return 1;
        case 1:
            func_8019F230();
            if (CURRENT_DAY == 3) {
                this->actor.textId = 0x29DF;
            } else {
                this->actor.textId = 0x29D1;
            }
            func_801518B0(globalCtx, this->actor.textId, &this->actor);
            func_80151BB4(globalCtx, 3);
            this->actionFunc = func_80AE4424;
            return 1;
    }
    return 0;
}

s32 func_80AE28B0(EnFsn* this, GlobalContext* globalCtx, Input* input) {
    if (func_80AE25D4(this, globalCtx, input)) {
        return 1;
    }
    if (func_80AE1B70(globalCtx)) {
        if (!this->items[this->cursorIdx]->isOutOfStock) {
            this->tmpActionFunc = this->actionFunc;
            func_80151938(globalCtx, this->items[this->cursorIdx]->choiceTextId);
            play_sound(NA_SE_SY_DECIDE);
            this->stickLeftPrompt.isEnabled = false;
            this->stickRightPrompt.isEnabled = false;
            this->drawCursor = 0;
            this->actionFunc = func_80AE44DC;
        } else {
            play_sound(NA_SE_SY_ERROR);
        }
        return 1;
    }
    return 0;
}

void func_80AE2974(EnFsn* this, GlobalContext* globalCtx) {
    s8 stickX = globalCtx->state.input[0].rel.stick_x;
    s8 stickY = globalCtx->state.input[0].rel.stick_y;

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

void func_80AE2A98(EnFsn* this) {
    Vec3f D_80AE5C40 = { 13.0f, 38.0f, -71.0f };
    u8 i = this->cursorIdx;
    EnGirlA* item = this->items[i];
    Vec3f worldPos;

    worldPos.x = D_80AE5C1C[i].x + (D_80AE5C40.x - D_80AE5C1C[i].x) * this->shopItemSelectedTween;
    worldPos.y = D_80AE5C1C[i].y + (D_80AE5C40.y - D_80AE5C1C[i].y) * this->shopItemSelectedTween;
    worldPos.z = D_80AE5C1C[i].z + (D_80AE5C40.z - D_80AE5C1C[i].z) * this->shopItemSelectedTween;

    item->actor.world.pos.x = worldPos.x;
    item->actor.world.pos.y = worldPos.y;
    item->actor.world.pos.z = worldPos.z;
}

s32 func_80AE2B44(EnFsn* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 1.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween >= 0.85f) {
        this->shopItemSelectedTween = 1.0f;
    }
    func_80AE2A98(this);
    if (this->shopItemSelectedTween == 1.0f) {
        return 1;
    }
    return 0;
}

s32 func_80AE2BE0(EnFsn* this) {
    Math_ApproachF(&this->shopItemSelectedTween, 0.0f, 1.0f, 0.15f);
    if (this->shopItemSelectedTween <= 0.15f) {
        this->shopItemSelectedTween = 0.0f;
    }
    func_80AE2A98(this);
    if (this->shopItemSelectedTween == 0.0f) {
        return 1;
    }
    return 0;
}

void func_80AE2C6C(EnFsn* this) {
    EnGirlA** items;
    s32 i;

    for (items = this->items, i = 0; i < this->unk38A; items++, i++) {
        if (this->actionFunc != func_80AE44DC && this->actionFunc != func_80AE45C4 && this->drawCursor == 0) {
            (*items)->isSelected = 0;
        } else {
            (*items)->isSelected = i == this->cursorIdx ? 1 : 0;
        }
    }
}

void func_80AE2CFC(EnFsn* this) {
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

void func_80AE2DC8(EnFsn* this) {
    f32 arrowAnimTween = this->arrowAnimTween;
    f32 stickAnimTween = this->stickAnimTween;
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

void func_80AE2F78(EnFsn* this, GlobalContext* globalCtx) {
    EnFsn* this2;
    s32 maxColor = 255;

    if (func_80AE2298() != 0) {
        func_80AE2438(this, globalCtx);

        this2 = this;
        this2->cursorX = 100.0f;
        this2->cursorY = 100.0f;
        this2->stickAccumY = 0;
        this2->stickAccumX = 0;
        
        this->cursorZ = 1.2f;
        this->cursorColorR = 0;
        this->cursorColorG = 80;
        this->cursorColorB = maxColor;
        this->cursorColorA = maxColor;
        this->cursorAnimState = 0;
        this->drawCursor = 0;
        this->cursorAnimTween = 0.0f;

        this->stickLeftPrompt.stickColorR = 200;
        this->stickLeftPrompt.stickColorG = 200;
        this->stickLeftPrompt.stickColorB = 200;
        this->stickLeftPrompt.stickColorA = 180;
        this->stickLeftPrompt.stickTexX = 49.0f;
        this->stickLeftPrompt.stickTexY = 95.0f;
        this->stickLeftPrompt.arrowColorR = maxColor;
        this->stickLeftPrompt.arrowColorG = maxColor;
        this->stickLeftPrompt.arrowColorB = 0;
        this->stickLeftPrompt.arrowColorA = 200;
        this->stickLeftPrompt.arrowTexX = 33.0f;
        this->stickLeftPrompt.arrowTexY = 91.0f;
        this->stickLeftPrompt.texZ = 1.0f;
        this->stickLeftPrompt.isEnabled = 0;

        this->stickRightPrompt.stickColorR = 200;
        this->stickRightPrompt.stickColorG = 200;
        this->stickRightPrompt.stickColorB = 200;
        this->stickRightPrompt.stickColorA = 180;
        this->stickRightPrompt.stickTexX = 274.0f;
        this->stickRightPrompt.stickTexY = 95.0f;
        this->stickRightPrompt.arrowColorR = maxColor;
        this->stickRightPrompt.arrowColorG = 0;
        this->stickRightPrompt.arrowColorB = 0;
        this->stickRightPrompt.arrowColorA = 200;
        this->stickRightPrompt.arrowTexX = 290.0f;
        this->stickRightPrompt.arrowTexY = 91.0f;
        this->stickRightPrompt.texZ = 1.0f;
        this->stickRightPrompt.isEnabled = 0;

        this->arrowAnimState = 0;
        this->stickAnimState = 0;
        this->stickAnimTween = this->arrowAnimTween = 0.0f;
    }
    this->blinkTimer = 20;
    this->unk44C = 4;
    this->eyeTextureIdx = 0;
    func_8013BC6C(&this->skelAnime, D_80AE5B20, this->unk44C);
    this->actionFunc = func_80AE30F8;
}

void func_80AE30F8(EnFsn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->unk44C == 4) {
        s16 sp22 = this->skelAnime.animCurrentFrame;
        s16 sp24 = SkelAnime_GetFrameCount(&D_80AE5B20[this->unk44C].animationSeg->common);
        if (sp22 == sp24) {
            this->unk44C = 5;
            func_8013BC6C(&this->skelAnime, D_80AE5B20, this->unk44C);
        }
    } else if (this->unk44E & 0x80) {
    dummy:;
        this->actionFunc = func_80AE32D4;
    } else {
    dummy2:;
        if (func_800B84D0(&this->actor, globalCtx)) {
            if (this->cutsceneState == 0) {
                if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                    ActorCutscene_Stop(0x7C);
                }
                this->cutscene = this->unk36C;
                ActorCutscene_SetIntentToPlay(this->cutscene);
                this->cutsceneState = 1;
            }
            this->actor.textId = func_80AE1BF0(globalCtx);
            func_801518B0(globalCtx, this->actor.textId, &this->actor);
            player->actor.world.pos.x = 1.0f;
            player->actor.world.pos.z = -34.0f;
            this->actionFunc = func_80AE3474;
        } else {
            if (((player->actor.world.pos.x >= -50.0f) && (player->actor.world.pos.x <= 15.0f)) &&
                (player->actor.world.pos.y > 0.0f) &&
                ((player->actor.world.pos.z >= -35.0f) && (player->actor.world.pos.z <= -20.0f))) {
                func_800B8614(&this->actor, globalCtx, 400.0f);
            }
        }
    }
}

void func_80AE32D4(EnFsn* this, GlobalContext* globalCtx) {
    s16 sp26 = this->skelAnime.animCurrentFrame;
    s16 sp24 = SkelAnime_GetFrameCount(&D_80AE5B20[this->unk44C].animationSeg->common);

    if (this->unk44E & 0x100) {
        this->unk44E &= ~0x100;
        this->unk44C = 11;
        func_8013BC6C(&this->skelAnime, D_80AE5B20, this->unk44C);
    } else {
        if (this->unk44C == 11 && func_801378B8(&this->skelAnime, 18.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_HANKO);
        }
        if (this->unk44E & 0x200) {
            this->unk44E &= ~0x200;
            this->unk44C = 5;
            func_8013BC6C(&this->skelAnime, D_80AE5B20, this->unk44C);
        } else if (this->unk44E & 0x40) {
            this->unk44E &= ~0x40;
            this->unk44C = 12;
            func_8013BC6C(&this->skelAnime, D_80AE5B20, this->unk44C);
        } else {
            if (this->unk44C == 12) {
                if (sp26 == sp24) {
                    this->unk44C = 5;
                    func_8013BC6C(&this->skelAnime, D_80AE5B20, this->unk44C);
                } else {
                    if (func_801378B8(&this->skelAnime, 28.0f)) {
                        Audio_PlayActorSound2(&this->actor, NA_SE_EV_HANKO);
                    }
                    return;
                }
            }
            if (!(this->unk44E & 0x80)) {
                this->actionFunc = func_80AE30F8;
            }
        }
    }
}

void func_80AE3474(EnFsn* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
            if (Player_GetMask(globalCtx) == PLAYER_MASK_NONE) {
                func_8011552C(globalCtx, 0x10);
                if (func_80AE2298()) {
                    this->actionFunc = func_80AE3644;
                } else {
                    this->unk378 = 0;
                    this->actionFunc = func_80AE352C;
                }
            } else {
                this->actionFunc = func_80AE4B20;
            }
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void func_80AE352C(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = PLAYER;

    func_80AE1F5C(this);
    if (talkState == 5 && func_80147624(globalCtx)) {
        switch (this->actor.textId) {
            case 0x29CC:
                this->actor.textId = 0x29CD;
                func_801518B0(globalCtx, this->actor.textId, &this->actor);
                break;
            case 0x29CD:
                this->actor.textId = 0x29CE;
                func_80AE1F5C(this);
                func_801518B0(globalCtx, this->actor.textId, &this->actor);
                break;
            case 0x29CE:
                this->actor.textId = 0xFF;
                func_801518B0(globalCtx, this->actor.textId, &this->actor);
                this->actionFunc = func_80AE38E0;
                break;
            case 0x29CF:
                player->unk_A87 = 0;
                this->actionFunc = func_80AE3880;
                break;
        }
    }
}

void func_80AE3644(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (talkState == 5) {
        if (func_80147624(globalCtx)) {
            switch (this->actor.textId) {
                case 0x29CC:
                    if (CURRENT_DAY != 3) {
                        this->actor.textId = 0x29FA;
                    } else {
                        this->actor.textId = 0x29D2;
                    }
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    break;
                case 0x29D2:
                    if (gSaveContext.weekEventReg[0x21] & 4) {
                        this->actor.textId = 0x2A01;
                    } else if (!(gSaveContext.weekEventReg[0x21] & 8) && !(gSaveContext.weekEventReg[0x4F] & 0x40)) {
                        this->actor.textId = 0x29D3;
                    } else {
                        this->actor.textId = 0x29D4;
                    }
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    break;
                case 0x29D3:
                case 0x29D4:
                case 0x29FA:
                case 0x2A01:
                    this->actor.textId = 0x29D5;
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    break;
            }
        }
    } else if (talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (!func_80AE25D4(this, globalCtx, globalCtx->state.input) && func_80147624(globalCtx)) {
            u32 trueTmp = true;
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    this->unk378 = trueTmp;
                    this->stickLeftPrompt.isEnabled = false;
                    this->stickRightPrompt.isEnabled = trueTmp;
                    this->actor.textId = 0x29D6;
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    this->actionFunc = func_80AE4A1C;
                    break;
                case 1:
                    func_8019F208();
                    this->unk378 = 0;
                    this->actor.textId = 0x29CE;
                    func_80AE1F5C(this);
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    this->actionFunc = func_80AE352C;
                    break;
            }
        }
    }
}

void func_80AE3880(EnFsn* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.textId = 0xFF;
        func_801518B0(globalCtx, this->actor.textId, &this->actor);
        this->actionFunc = func_80AE38E0;
    }
}

void func_80AE38E0(EnFsn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 temp_v0;
    u8 phi_v0;

    if (func_80152498(&globalCtx->msgCtx) == 16) {
        temp_v0 = func_80123810(globalCtx);
        if (temp_v0 > 0) {
            if (player->heldItemButton == 0) {
                phi_v0 = gSaveContext.equips
                             .buttonItems[gSaveContext.playerForm == PLAYER_FORM_HUMAN ? 0 : gSaveContext.playerForm]
                                         [player->heldItemButton];
            } else {
                phi_v0 = gSaveContext.equips.buttonItems[0][player->heldItemButton];
            }
            this->unk374 = phi_v0 < 40 ? gItemPrices[phi_v0] : 0;
            if (this->unk374 > 0) {
                player->actor.textId = 0x29EF;
                player->unk_A87 = phi_v0;
                this->actionFunc = func_80AE3A68;
            } else {
                player->actor.textId = 0x29CF;
                this->actionFunc = func_80AE352C;
            }
            this->actor.textId = player->actor.textId;
            func_801477B4(globalCtx);
        } else if (temp_v0 < 0) {
            if (CURRENT_DAY == 3) {
                this->actor.textId = 0x29DF;
            } else {
                this->actor.textId = 0x29D1;
            }
            func_801518B0(globalCtx, this->actor.textId, &this->actor);
            func_80151BB4(globalCtx, 3);
            this->actionFunc = func_80AE4424;
        }
    }
}

void func_80AE3A68(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    Player* player = PLAYER;

    if (talkState == 4 && func_80147624(globalCtx)) {
        switch (globalCtx->msgCtx.choiceIndex) {
            case 0:
                func_8019F208();
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
                if (this->cutsceneState == 2) {
                    ActorCutscene_Stop(this->cutscene);
                    this->cutsceneState = 0;
                }
                switch (this->unk374) {
                    case 5:
                        this->unk37C = 2;
                        break;
                    case 10:
                        this->unk37C = 3;
                        break;
                    case 20:
                        this->unk37C = 4;
                        break;
                    case 50:
                        this->unk37C = 5;
                        break;
                    case 200:
                        this->unk37C = 7;
                        break;
                }
                this->actionFunc = func_80AE3BC4;
                break;
            case 1:
                func_8019F230();
                player->unk_A87 = 0;
                this->actionFunc = func_80AE3880;
                break;
        }
    }
}

void func_80AE3BC4(EnFsn* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        if (this->unk378 == 1 && (this->items[this->cursorIdx]->getItemId == 0x7E)) {
            func_80151BB4(globalCtx, 45);
            func_80151BB4(globalCtx, 3);
        }
        this->actor.parent = NULL;
        if (!(this->actor.params & 1) && this->unk378 == 0) {
            func_80123D50(globalCtx, PLAYER, 18, 21);
        }
        this->actionFunc = func_80AE3CF0;
    } else if (this->unk378 == 1) {
        func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
    } else {
        func_800B8A1C(&this->actor, globalCtx, this->unk37C, 300.0f, 300.0f);
    }
}

void func_80AE3CF0(EnFsn* this, GlobalContext* globalCtx) {
    if (((void)0, gSaveContext.inventory.questItems) & gBitFlags[18]) {
        if (globalCtx->msgCtx.unk120B1 == 0) {
            func_80AE1E58(this, globalCtx);
        }
    } else {
        func_80AE1E58(this, globalCtx);
    }
}

void func_80AE3D50(EnFsn* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        if (!(this->actor.params & 1)) {
            if (this->unk378 == 0) {
                this->cutscene = this->unk372;
                this->actor.textId = 0x29D0;
            } else {
                this->cutscene = this->unk36C;
                this->actor.textId = this->unk38C <= 0 ? 0x29DE : 0x29D6;
            }
            func_801518B0(globalCtx, this->actor.textId, &this->actor);
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->cutscene);
            this->actionFunc = func_80AE3E4C;
        } else {
            func_80AE1C54(this, globalCtx);
            this->actionFunc = func_80AE4BF4;
        }
    } else {
        func_800B85E0(&this->actor, globalCtx, 400.0f, -1);
    }
}

void func_80AE3E4C(EnFsn* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
            if (this->unk378 == 0) {
                this->actionFunc = func_80AE4638;
            } else if (this->actor.textId != 0x29D6) {
                this->actionFunc = func_80AE4828;
            } else {
                func_8011552C(globalCtx, 6);
                this->stickLeftPrompt.isEnabled = false;
                this->stickRightPrompt.isEnabled = true;
                this->actionFunc = func_80AE4A1C;
            }
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk378 == 0 ? this->unk372 : this->unk36C;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void func_80AE3F40(EnFsn* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 2) {
        ActorCutscene_Stop(this->cutscene);
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->unk36E;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene) != 0) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
            func_80AE26D4(this, globalCtx);
            this->actionFunc = func_80AE4028;
            func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void func_80AE4028(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkstate = func_80152498(&globalCtx->msgCtx);
    s32 pad;
    u8 cursorIdx = this->cursorIdx;

    if (!func_80AE2BE0(this)) {
        this->delayTimer = 3;
    } else if (this->delayTimer != 0) {
        this->delayTimer--;
    } else {
        this->drawCursor = 0xFF;
        this->stickLeftPrompt.isEnabled = true;
        func_80AE26D4(this, globalCtx);
        if (talkstate == 5) {
            func_8011552C(globalCtx, 6);
            if (!func_80AE28B0(this, globalCtx, globalCtx->state.input)) {
                func_80AE2074(this);
                if (this->cursorIdx != cursorIdx) {
                    play_sound(NA_SE_SY_CURSOR);
                    func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
                }
            }
        }
    }
}

void func_80AE4120(EnFsn* this, GlobalContext* globalCtx) {
    if (this->cutsceneState == 2) {
        ActorCutscene_Stop(this->cutscene);
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        }
        this->cutscene = this->unk370;
        ActorCutscene_SetIntentToPlay(this->cutscene);
        this->cutsceneState = 1;
    } else if (this->cutsceneState == 1) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
            this->stickLeftPrompt.isEnabled = false;
            this->stickRightPrompt.isEnabled = true;
            this->actor.textId = 0x29D6;
            func_80151938(globalCtx, this->actor.textId);
            this->actionFunc = func_80AE4A1C;
        } else {
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
}

void func_80AE41FC(EnFsn* this, GlobalContext* globalCtx) {
    EnGirlA* item;
    EnGirlA* item2;
    EnGirlA* item3;

    item = this->items[this->cursorIdx];
    switch (item->canBuyFunc(globalCtx, item)) {
        case CANBUY_RESULT_SUCCESS: // Still results in fanfare, used by All Nights mask to set weekEvent flag
            func_8019F208();
            gSaveContext.weekEventReg[0x21] |= 4;
        case CANBUY_RESULT_SUCCESS_FANFARE:
            if (this->cutsceneState == 2) {
                ActorCutscene_Stop(this->cutscene);
                this->cutsceneState = 0;
            }
            func_8019F208();
            item2 = this->items[this->cursorIdx];
            item2->buyFanfareFunc(globalCtx, item2);
            func_800B8A1C(&this->actor, globalCtx, this->items[this->cursorIdx]->getItemId, 300.0f, 300.0f);
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            Interface_ChangeAlpha(50);
            this->drawCursor = 0;
            this->shopItemSelectedTween = 0.0f;
            item3 = this->items[this->cursorIdx];
            item3->boughtFunc(globalCtx, item3);
            if (this->unk380 == this->cursorIdx) {
                gSaveContext.roomInf[126][5] &= ~0xFF000000;
            } else if (this->unk382 == this->cursorIdx) {
                gSaveContext.roomInf[126][5] &= ~0xFF0000;
            }
            this->unk38C += -1;
            this->unk384[this->cursorIdx] = -1;
            this->actionFunc = func_80AE3BC4;
            break;
        case CANBUY_RESULT_NEED_RUPEES:
            play_sound(NA_SE_SY_ERROR);
            func_80151938(globalCtx, 0x29F0);
            this->actionFunc = func_80AE45C4;
            break;
        case CANBUY_RESULT_CANNOT_GET_NOW:
            play_sound(NA_SE_SY_ERROR);
            func_80151938(globalCtx, 0x29DD);
            this->actionFunc = func_80AE45C4;
            break;
    }
}

void func_80AE4424(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if ((talkState == 5 || talkState == 6) && func_80147624(globalCtx)) {
        if (((void)0, gSaveContext.inventory.questItems) & gBitFlags[18]) {
            if (globalCtx->msgCtx.unk120B1 == 0) {
                func_80AE2524(this, globalCtx);
            } else {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
            }

        } else {
            func_80AE2524(this, globalCtx);
        }
    }
}

void func_80AE44DC(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (func_80AE2B44(this) && talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (!func_80AE2670(this, globalCtx, globalCtx->state.input) && func_80147624(globalCtx)) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_80AE41FC(this, globalCtx);
                    break;
                case 1:
                    func_8019F230();
                    this->actionFunc = this->tmpActionFunc;
                    func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
            }
        }
    }
}

void func_80AE45C4(EnFsn* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        this->actionFunc = this->tmpActionFunc;
        func_80151938(globalCtx, this->items[this->cursorIdx]->actor.textId);
    }
}

void func_80AE4638(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk36C;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (talkState == 4) {
        if (func_80147624(globalCtx) != 0) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    this->actor.textId = 0xFF;
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    this->actionFunc = func_80AE38E0;
                    break;
                case 1:
                    func_8019F230();
                    this->actor.textId = CURRENT_DAY == 3 ? 0x29DF : 0x29D1;
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    func_80151BB4(globalCtx, 3);
                    break;
            }
        }
    } else if ((talkState == 5 || talkState == 6) && func_80147624(globalCtx)) {
        if (((void)0, gSaveContext.inventory.questItems) & gBitFlags[18]) {
            if (globalCtx->msgCtx.unk120B1 == 0) {
                func_80AE2524(this, globalCtx);
            } else {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
            }
        } else {
            func_80AE2524(this, globalCtx);
        }
    }
}

void func_80AE4828(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (this->cutsceneState == 0) {
        if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
            ActorCutscene_StartAndSetFlag(this->cutscene, &this->actor);
            this->cutsceneState = 2;
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            this->cutscene = this->unk36C;
            ActorCutscene_SetIntentToPlay(this->cutscene);
        }
    }
    if (talkState == 4) {
        if (func_80147624(globalCtx) != 0) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    this->unk378 = 0;
                    this->actor.textId = 0x29CE;
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    this->actionFunc = func_80AE352C;
                    break;
                case 1:
                    func_8019F230();
                    this->actor.textId = CURRENT_DAY == 3 ? 0x29DF : 0x29D1;
                    func_801518B0(globalCtx, this->actor.textId, &this->actor);
                    func_80151BB4(globalCtx, 3);
                    break;
            }
        }
    } else if ((talkState == 5 || talkState == 6) && func_80147624(globalCtx)) {
        if (((void)0, gSaveContext.inventory.questItems) & gBitFlags[18]) {
            if (globalCtx->msgCtx.unk120B1 == 0) {
                func_80AE2524(this, globalCtx);
            } else {
                globalCtx->msgCtx.unk11F22 = 0x43;
                globalCtx->msgCtx.unk12023 = 4;
            }
        } else {
            func_80AE2524(this, globalCtx);
        }
    }
}

void func_80AE4A1C(EnFsn* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);
    u8 cursorIdx;

    if (talkState == 4) {
        func_8011552C(globalCtx, 6);
        if (!func_80AE25D4(this, globalCtx, globalCtx->state.input) &&
            (!func_80147624(globalCtx) || !func_80AE2760(this, globalCtx)) && this->stickAccumX > 0) {
            cursorIdx = func_80AE2028(this);
            if (cursorIdx != 0xFF) {
                this->cursorIdx = cursorIdx;
                this->actionFunc = func_80AE3F40;
                func_8011552C(globalCtx, 6);
                this->stickRightPrompt.isEnabled = false;
                play_sound(NA_SE_SY_CURSOR);
            }
        }
    } else if (talkState == 5 && func_80147624(globalCtx)) {
        this->actor.textId = 0x29D6;
        func_801518B0(globalCtx, this->actor.textId, &this->actor);
        if (globalCtx) {}
    }
}

void func_80AE4B20(EnFsn* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        func_80AE2524(this, globalCtx);
    }
}

void func_80AE4B70(EnFsn* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->unk376 = 0;
        func_80AE1C54(this, globalCtx);
        this->actionFunc = func_80AE4BF4;
        return;
    } else {
        if ((this->actor.xzDistToPlayer < 100.0f) || this->actor.isTargeted) {
            func_800B8614(&this->actor, globalCtx, 100.0f);
        }
    }
}

void func_80AE4BF4(EnFsn* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 5 && func_80147624(globalCtx)) {
        if (this->unk44E & 1) {
            this->unk44E = this->unk44E & ~1;
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->actionFunc = func_80AE4B70;
        } else if (this->unk44E & 2) {
            this->unk44E = this->unk44E & ~2;
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            this->actionFunc = func_80AE3BC4;
        } else {
            func_80AE1C54(this, globalCtx);
        }
    }
}

void func_80AE4CD8(EnFsn* this) {
    this->unk36C = this->actor.cutscene;
    this->unk36E = ActorCutscene_GetAdditionalCutscene(this->unk36C);
    this->unk370 = ActorCutscene_GetAdditionalCutscene(this->unk36E);
    this->unk372 = ActorCutscene_GetAdditionalCutscene(this->unk370);
}

void func_80AE4D28(EnFsn* this) {
    s16 decr;

    decr = this->blinkTimer - 1;
    if (decr >= 3) {
        this->eyeTextureIdx = 0;
        this->blinkTimer = decr;
    } else if (decr == 0) {
        this->eyeTextureIdx = 2;
        this->blinkTimer = (s32)(Rand_ZeroOne() * 60.0f) + 20;
    } else {
        this->eyeTextureIdx = 1;
        this->blinkTimer = decr;
    }
}

void EnFsn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFsn* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 20.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013320, &D_06012C34, this->limbDrawTable,
                     this->transitionDrawTable, 19);
    if (!(this->actor.params & 1)) {
        this->actor.shape.rot.y += 0x8000;
        this->actor.flags &= ~1;
        func_80AE4CD8(this);
        func_80AE2F78(this, globalCtx);
    } else {
        if ((gSaveContext.weekEventReg[0x21] & 8) || (gSaveContext.weekEventReg[0x4F] & 0x40)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
        Collider_InitCylinder(globalCtx, &this->collider);
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        this->blinkTimer = 20;
        this->eyeTextureIdx = 0;
        this->actor.flags |= 1;
        this->actor.targetMode = 0;
        this->unk44C = 0;
        func_8013BC6C(&this->skelAnime, D_80AE5B20, this->unk44C);
        this->actionFunc = func_80AE4B70;
    }
}

void EnFsn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFsn* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnFsn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFsn* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_800E9250(globalCtx, &this->actor, &this->unk274, &this->unk27A, this->actor.focus.pos);
    func_8013D9C8(globalCtx, this->unk228, this->unk24E, 19);
    func_80AE4D28(this);
    if (!(this->actor.params & 1) && func_80AE2298()) {
        func_80AE2974(this, globalCtx);
        func_80AE2C6C(this);
        func_80AE2DC8(this);
        func_80AE2CFC(this);
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->actor.params & 1) {
        func_80AE1EF4(this, globalCtx);
    }
}

void func_80AE502C(EnFsn* this, GlobalContext* globalCtx, f32 x, f32 y, f32 z, u8 drawCursor) {
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

void func_80AE52A4(GlobalContext* globalCtx, s32 r, s32 g, s32 b, s32 a, f32 x, f32 y, f32 z, s32 s, s32 t,
                         f32 dx, f32 dy) {
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

void func_80AE5440(EnFsn* this, GlobalContext* globalCtx) {
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
            func_80AE52A4(globalCtx, this->stickLeftPrompt.arrowColorR, this->stickLeftPrompt.arrowColorG,
                                this->stickLeftPrompt.arrowColorB, this->stickLeftPrompt.arrowColorA,
                                this->stickLeftPrompt.arrowTexX, this->stickLeftPrompt.arrowTexY,
                                this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_80AE52A4(globalCtx, this->stickRightPrompt.arrowColorR, this->stickRightPrompt.arrowColorG,
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
            func_80AE52A4(globalCtx, this->stickLeftPrompt.stickColorR, this->stickLeftPrompt.stickColorG,
                                this->stickLeftPrompt.stickColorB, this->stickLeftPrompt.stickColorA,
                                this->stickLeftPrompt.stickTexX, this->stickLeftPrompt.stickTexY,
                                this->stickLeftPrompt.texZ, 0, 0, -1.0f, 1.0f);
        }
        if (drawStickLeftPrompt) {
            func_80AE52A4(globalCtx, this->stickRightPrompt.stickColorR, this->stickRightPrompt.stickColorG,
                                this->stickRightPrompt.stickColorB, this->stickRightPrompt.stickColorA,
                                this->stickRightPrompt.stickTexX, this->stickRightPrompt.stickTexY,
                                this->stickRightPrompt.texZ, 0, 0, 1.0f, 1.0f);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80AE57E8(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnFsn *this = THIS;
    s16 tmp;
    s32 phi_v0;

    if (limbIndex == 16) {
        SysMatrix_InsertXRotation_s(this->unk274.y, 1);
    }
    if (this->actor.params & 1) {
        switch(limbIndex) {
            case 8:
                phi_v0 = 0;
                break;
            case 11:
                phi_v0 = 1;
                break;
            case 16:
                phi_v0 = 2;
                break;
            default:
                phi_v0 = 9;
                break;
        }
        if (phi_v0 < 9) {
            tmp = (s32) (Math_SinS(this->unk228[phi_v0]) * 200.0f);
            rot->y += tmp;
            tmp = (s32) (Math_CosS(this->unk24E[phi_v0]) * 200.0f);
            rot->z += tmp;
        }
    }
    if (limbIndex == 17) {
        *dList = NULL;
    }
    return 0;
}

void func_80AE5910(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnFsn *this = THIS;

    if (limbIndex == 16) {
        this->actor.focus.pos.x = this->actor.world.pos.x;
        this->actor.focus.pos.y = this->actor.world.pos.y + 60.0f;
        this->actor.focus.pos.z = this->actor.world.pos.z;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, D_0600F180);
        gSPDisplayList(POLY_OPA_DISP++, D_0600F218);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnFsn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static void* D_80AE5C4C[] = { &D_06005BC0, &D_06006D40, &D_06007140 };
    EnFsn* this = THIS;
    s32 pad;
    s16 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C5B0(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80AE5C4C[this->eyeTextureIdx]));
    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80AE5C4C[this->eyeTextureIdx]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80AE57E8, func_80AE5910, &this->actor);

    for (i = 0; i < this->unk38A; i++) {
        this->items[i]->actor.scale.x = 0.2f;
        this->items[i]->actor.scale.y = 0.2f;
        this->items[i]->actor.scale.z = 0.2f;
    }
    func_80AE502C(this, globalCtx, this->cursorX, this->cursorY, this->cursorZ, this->drawCursor);
    func_80AE5440(this, globalCtx);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}