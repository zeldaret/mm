/*
 * File z_en_in.c
 * Overlay: ovl_en_in
 * Description: Gorman Bros
 */

#include "z_en_in.h"

#define FLAGS 0x00000019

#define THIS ((EnIn*)thisx)

#define SET_FLAGS_FINISH_RACE                                                                   \
    {                                                                                           \
        gSaveContext.weekEventReg[92] &= (u8) ~(1 | 2 | 4);                                     \
        gSaveContext.weekEventReg[92] =                                                         \
            gSaveContext.weekEventReg[92] | (u8)(gSaveContext.weekEventReg[92] & ~(1 | 2 | 4)); \
    }

#define SET_FLAGS_START_RACE                                                                          \
    {                                                                                                 \
        gSaveContext.weekEventReg[92] &= (u8) ~(1 | 2 | 4);                                           \
        gSaveContext.weekEventReg[92] =                                                               \
            gSaveContext.weekEventReg[92] | (u8)((gSaveContext.weekEventReg[92] & ~(1 | 2 | 4)) | 1); \
    }

void EnIn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808F5A94(EnIn* this, GlobalContext* globalCtx);
void func_808F3690(EnIn* this, GlobalContext* globalCtx);
void func_808F5A34(EnIn* this, GlobalContext* globalCtx);
s32 func_808F5994(EnIn* this, GlobalContext* globalCtx, Vec3f* arg2, s16 arg3);

const ActorInit En_In_InitVars = {
    ACTOR_EN_IN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_IN,
    sizeof(EnIn),
    (ActorFunc)EnIn_Init,
    (ActorFunc)EnIn_Destroy,
    (ActorFunc)EnIn_Update,
    (ActorFunc)EnIn_Draw,
};

extern FlexSkeletonHeader D_06014EA8;
extern AnimationHeader D_06015E38;
extern AnimationHeader D_06016484;
extern AnimationHeader D_06016A60;
extern AnimationHeader D_060170DC;
extern AnimationHeader D_060177AC;
extern AnimationHeader D_06018240;
extern AnimationHeader D_060187C8;
extern AnimationHeader D_060198A8;
extern Gfx D_06007A70[];
extern Gfx D_06007C48[];
extern Gfx D_0601C528[];
extern AnimatedMaterial D_06001C30;
extern UNK_TYPE D_06003520;
extern UNK_TYPE D_060035E0;
extern UNK_TYPE D_06004820;
extern UNK_TYPE D_06004C20;
extern UNK_TYPE D_060043E0;
extern AnimationHeader D_06001D10;
extern AnimationHeader D_06014F8C;
extern AnimationHeader D_06000CB0;
extern AnimationHeader D_060003B4;
extern AnimationHeader D_06001BE0;
extern AnimationHeader D_06015918;
extern AnimationHeader D_0601C0B0;
extern AnimationHeader D_0601A140;
extern AnimationHeader D_0601B904;
extern AnimationHeader D_0601B3C4;
extern AnimationHeader D_06019EB4;
extern Gfx D_060137A0[];
extern Gfx D_06014420[];
extern Gfx D_06014040[];
extern Gfx D_06013670[];
extern Gfx D_06014AE0[];
extern Gfx D_06012A78[];
extern Gfx D_06013DE0[];
extern Gfx D_060138D0[];
extern Gfx D_06013540[];
extern Gfx D_06012DF8[];
extern Gfx D_060145D8[];
extern Gfx D_06014860[];
extern Gfx D_06014710[];
extern Gfx D_06013A00[];
extern Gfx D_06013F10[];
extern Gfx D_06014C30[];
extern Gfx D_060149A8[];
extern Gfx D_06013440[];

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
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

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 12, { { 1600, 0, 0 }, 5 }, 200 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

CollisionCheckInfoInit2 sColChkInfoInit2 = {
    0, 0, 0, 0, MASS_HEAVY,
};

static DamageTable sDamageTable = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static ActorAnimationEntryS sAnimations[] = {
    { &D_06001D10, 1.0f, 0, -1, 0, 0 },  { &D_06001D10, 1.0f, 0, -1, 0, -4 }, { &D_06014F8C, 1.0f, 0, -1, 0, 0 },
    { &D_06014F8C, 1.0f, 0, -1, 0, -4 }, { &D_06000CB0, 1.0f, 0, -1, 0, -4 }, { &D_060003B4, 1.0f, 0, -1, 0, -4 },
    { &D_06001BE0, 1.0f, 0, -1, 0, -4 }, { &D_06015918, 1.0f, 0, -1, 0, -4 }, { &D_0601C0B0, 1.0f, 0, -1, 0, 0 },
    { &D_0601C0B0, 1.0f, 0, -1, 0, -4 }, { &D_0601A140, 1.0f, 0, -1, 0, 0 },  { &D_0601A140, 1.0f, 0, -1, 0, -4 },
    { &D_0601B904, 1.0f, 0, -1, 0, 0 },  { &D_0601B904, 1.0f, 0, -1, 0, -4 }, { &D_0601B3C4, 1.0f, 0, -1, 0, 0 },
    { &D_0601B3C4, 0.0f, 0, -1, 2, 0 },  { &D_0601B3C4, 1.0f, 0, -1, 0, -4 }, { &D_06019EB4, 1.0f, 0, -1, 2, -4 },
};

static s16 D_808F6C0C[] = {
    4000, 4, 1, 3, 6000, 4, 1, 6, 4000, 4, 1, 3, 6000, 4, 1, 6,
};

s32 func_808F30B0(SkelAnime* skelAnime, s16 animIndex) {
    s16 frameCount;
    s32 ret = false;

    if (animIndex >= 0 && animIndex < 18) {
        ret = true;
        frameCount = sAnimations[animIndex].frameCount;
        if (frameCount < 0) {
            frameCount = SkelAnime_GetFrameCount(&sAnimations[animIndex].animationSeg->common);
        }
        SkelAnime_ChangeAnim(skelAnime, sAnimations[animIndex].animationSeg, sAnimations[animIndex].playbackSpeed,
                             sAnimations[animIndex].frame, frameCount, sAnimations[animIndex].mode,
                             sAnimations[animIndex].transitionRate);
    }
    return ret;
}

s32 func_808F3178(EnIn* this, GlobalContext* globalCtx) {
    u8 prevUnk260 = this->unk260;
    u8 prevUnk261 = this->unk261;
    u8 tmp;

    this->unk260 = tmp = func_8013DB90(globalCtx, &this->unk248, -6.0f);
    if (this->unk260 != 0 && prevUnk260 == 0 && tmp & 0xFF) {
        Audio_PlayActorSound2(&this->actor, 0x802);
    }
    this->unk261 = tmp = func_8013DB90(globalCtx, &this->unk254, -6.0f);
    if (this->unk261 != 0 && prevUnk261 == 0 && tmp & 0xFF) {
        Audio_PlayActorSound2(&this->actor, 0x802);
    }
    return 0;
}

void func_808F322C(EnIn* this, s32 arg1) {
    if (DECR(this->unk484) == 0) {
        this->unk482++;
        if (this->unk482 >= arg1) {
            this->unk482 = 0;
            this->unk484 = Rand_S16Offset(30, 30);
        }
    }
}

void func_808F32A0(EnIn* this, GlobalContext* globalCtx) {
    this->colliderCylinder.dim.pos.x = this->actor.world.pos.x;
    this->colliderCylinder.dim.pos.y = this->actor.world.pos.y;
    this->colliderCylinder.dim.pos.z = this->actor.world.pos.z;
    if (this->unk23D == 0) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }
}

s32 func_808F3310(EnIn* this, GlobalContext* globalCtx) {
    if (this->colliderCylinder.base.acFlags & AC_HIT) {
        this->colliderCylinder.base.acFlags &= ~AC_HIT;
    }
    return 0;
}

s32 func_808F3334(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (this->colliderJntSph.base.atFlags & AT_HIT) {
        this->colliderJntSph.base.atFlags &= ~AT_HIT;
        if (this->colliderJntSph.base.atFlags & AT_BOUNCED) {
            return 0;
        }
        Audio_PlayActorSound2(&player->actor, 0x83E);
        func_800B8D98(globalCtx, &this->actor, 3.0f, this->actor.yawTowardsPlayer, 6.0f);
    }
    return 1;
}

s32 func_808F33B8(void) {
    s32 ret;

    if (((ret = gSaveContext.day == 1) && (ret = gSaveContext.time >= 0x3AAA) && (ret = gSaveContext.time <= 0x4000)) ||
        (ret = gSaveContext.day >= 2)) {
        ret = (gSaveContext.weekEventReg[22] & 1) == 0;
    }
    return ret;
}

void func_808F3414(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f sp30;

    if (this->unk23D == 0) {
        this->unk494 = SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }
    if (func_8013D5E8(this->actor.shape.rot.y, 0x2710, this->actor.yawTowardsPlayer)) {
        sp30.x = player->actor.world.pos.x;
        sp30.y = player->bodyPartsPos[7].y + 3.0f;
        sp30.z = player->actor.world.pos.z;
        func_8013D2E0(&sp30, &this->actor.focus, &this->actor.shape, &this->unk352, &this->unk358, &this->unk35E,
                      D_808F6C0C);
    } else {
        Math_SmoothStepToS(&this->unk352, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk354, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk358, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk35A, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk35E, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->unk360, 0, 4, 1000, 1);
    }
    func_808F322C(this, 3);
    func_808F3178(this, globalCtx);
    func_8013D9C8(globalCtx, this->unk376, this->unk39E, 20);
}

void func_808F35AC(EnIn* this, GlobalContext* globalCtx) {
    this->unk4AC |= 0x10;
    if (this->unk4A4 != NULL) {
        this->unk4A4->unk4AC |= 0x10;
    }
}

void func_808F35D8(EnIn* this, GlobalContext* globalCtx) {
    this->unk4AC &= ~0x10;
    if (this->unk4A4 != NULL) {
        this->unk4A4->unk4AC &= ~0x10;
    }
}

void EnIn_DoNothing(EnIn* this, GlobalContext* globalCtx) {
}

void func_808F3618(EnIn* this, GlobalContext* globalCtx) {
    if (ENIN_GET_WALKING_FLAG(&this->actor) != 0x3F) {
        func_808F30B0(&this->skelAnime, 9);
    }
    if (ENIN_GET_WALKING_FLAG(&this->actor) != 0x3F) {
        this->actionFunc = func_808F3690;
    } else {
        this->actionFunc = EnIn_DoNothing;
    }
}

void func_808F3690(EnIn* this, GlobalContext* globalCtx) {
    s16 sp36;
    Vec3f sp28; // unsure if Vec3f, but it is probably size 0xC

    Math_SmoothStepToF(&this->actor.speedXZ, 1.0f, 0.4f, 1000.0f, 0.0f);
    sp36 = this->actor.speedXZ * 400.0f;
    if (func_8013D68C(this->unk240, this->unk244, &sp28) && func_8013D768(&this->actor, &sp28, sp36)) {
        this->unk244++;
        if (this->unk244 >= *this->unk240) {
            this->unk244 = 0;
        }
    }
}

void func_808F374C(EnIn* this, GlobalContext* globalCtx) {
    AnimationHeader* animations[] = { &D_06015E38, &D_06016A60, &D_060177AC, &D_06016484,
                                      &D_060170DC, &D_06018240, &D_060187C8, &D_060198A8 };

    if (this->skelAnime.animCurrentSeg == &D_06016484 || this->skelAnime.animCurrentSeg == &D_060170DC) {
        if (func_801378B8(&this->skelAnime, 8.0f)) {
            func_8019F88C(&this->actor.projectedPos, NA_SE_VO_IN_LASH_0, 2);
            if (Rand_ZeroOne() < 0.3f) {
                func_8019F1C0(&this->actor.projectedPos, NA_SE_IT_INGO_HORSE_NEIGH);
            }
            func_8019F1C0(&this->actor.projectedPos, NA_SE_IT_LASH);
        }
    }
    if (this->skelAnime.animCurrentSeg == &D_060198A8 && func_801378B8(&this->skelAnime, 20.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_CRY_0);
    }
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        this->unk486 = this->unk488 %= 8;
        SkelAnime_ChangeAnim(&this->skelAnime, animations[this->unk488], 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&animations[this->unk488]->common), 2, -10.0f);
    }
}

void func_808F38F8(EnIn* this, GlobalContext* globalCtx) {
    this->unk4A4 = NULL;
    while (true) {
        //! @bug: Infinite loop if there is only one ACTOR_EN_IN
        this->unk4A4 = (EnIn*)func_ActorCategoryIterateById(globalCtx, &this->unk4A4->actor, ACTORCAT_NPC, ACTOR_EN_IN);
        if (this->unk4A4 != NULL && this->unk4A4 != this) {
            break;
        }
        this->unk4A4 = (EnIn*)this->unk4A4->actor.next;
    }
}

void func_808F395C(EnIn* this, GlobalContext* globalCtx) {
    if (this->unk4B0 == 0) {
        this->actionFunc = func_808F5A94;
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.flags &= ~0x10000;
        this->actionFunc = func_808F5A34;
        this->unk48C = 1;
    } else {
        func_800B8614(&this->actor, globalCtx, 200.0f);
    }
}

void func_808F39DC(EnIn* this, GlobalContext* globalCtx) {
    u16 textId = 0;

    if (gSaveContext.day != 3) {
        switch (gSaveContext.weekEventReg[92] & (1 | 2 | 4)) {
            case 2:
                textId = 0x347A;
                break;
            case 3:
                textId = 0x3476;
                break;
        }
        SET_FLAGS_FINISH_RACE;
    } else {
        switch (gSaveContext.weekEventReg[92] & (1 | 2 | 4)) {
            case 2:
                textId = 0x349D;
                break;
            case 3:
                textId = 0x3499;
                break;
        }
        SET_FLAGS_FINISH_RACE;
    }
    this->actor.flags |= 0x10000;
    this->actor.textId = textId;
    this->actionFunc = func_808F395C;
    if (this->unk4B0 == 2) {
        Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LOST);
    } else {
        Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_JOY0);
    }
}

void func_808F3AD4(EnIn* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.flags &= ~0x10000;
        this->unk48C = 1;
        this->actionFunc = func_808F5A94;
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void func_808F3B40(EnIn* this, GlobalContext* globalCtx) {
    u16 textId;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actor.flags |= 0x10000;
        this->actionFunc = func_808F3AD4;
        textId = gSaveContext.day != 3 ? 0x3481 : 0x34A4;
        this->actor.textId = textId;
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x92, 500.0f, 100.0f);
    }
}

void func_808F3BD4(EnIn* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.flags &= ~0x10000;
        this->unk48C = 1;
        this->actionFunc = func_808F5A94;
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void func_808F3C40(EnIn* this, GlobalContext* globalCtx) {
    u16 textId;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actor.flags |= 0x10000;
        this->actionFunc = func_808F3BD4;
        textId = gSaveContext.day != 3 ? 0x346A : 0x3492;
        this->actor.textId = textId;
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x92, 500.0f, 100.0f);
    }
}

void func_808F3CD4(EnIn* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.flags &= ~0x10000;
        this->unk48C = 1;
        this->actionFunc = func_808F5A94;
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void func_808F3D40(EnIn* this, GlobalContext* globalCtx) {
    u16 textId;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        this->actionFunc = func_808F3CD4;
        textId = gSaveContext.day != 3 ? 0x347D : 0x34A0;
        this->actor.textId = textId;
        this->actor.flags |= 0x10000;
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x81, 500.0f, 100.0f);
    }
}

u16 func_808F3DD4(GlobalContext* globalCtx, EnIn* this, u32 arg2) {
    u16 textId = 0;

    if (Player_GetMask(globalCtx) == PLAYER_MASK_CIRCUS_LEADERS_MASK) {
        if (!(gSaveContext.weekEventReg[63] & 0x40)) {
            return 0x34A9;
        } else if (this->unk4AC & 8) {
            return 0x34B1;
        } else {
            textId = 0x34AF;
        }
    dummy_label_895710:; // POSSIBLE FAKE MATCH
    } else {
        switch (arg2) {
            case 0:
                if ((gSaveContext.playerForm == 2) || (gSaveContext.playerForm == 1)) {
                    textId = 0x345C;
                } else if (gSaveContext.playerForm == 3) {
                    textId = 0x3460;
                } else if (!(gSaveContext.weekEventReg[15] & 8)) {
                    textId = 0x3458;
                } else {
                    textId = 0x345B;
                }
                break;
            case 1:
                if (!(gSaveContext.weekEventReg[15] & 0x10)) {
                    textId = 0x3463;
                } else {
                    textId = 0x346B;
                }
                break;
            case 3:
                if (gSaveContext.playerForm == 3) {
                    textId = 0x3485;
                } else if (gSaveContext.playerForm == 2 || gSaveContext.playerForm == 1) {
                    textId = 0x3484;
                } else if (!(gSaveContext.weekEventReg[56] & 4)) {
                    textId = 0x346D;
                } else {
                    textId = 0x3482;
                }
                break;
            case 4:
                if (gSaveContext.playerForm == 2 || gSaveContext.playerForm == 1) {
                    textId = 0x348A;
                } else if (gSaveContext.playerForm == 3) {
                    textId = 0x348B;
                } else if (!(gSaveContext.weekEventReg[16] & 1)) {
                    textId = 0x3486;
                } else {
                    textId = 0x3489;
                }
                break;
            case 5:
                if (func_808F33B8()) {
                    textId = 0x34B3;
                } else if (!(gSaveContext.weekEventReg[16] & 2)) {
                    textId = 0x348E;
                } else {
                    textId = 0x3493;
                }
                break;
            case 7:
                if (gSaveContext.playerForm == 3) {
                    textId = 0x34A8;
                } else if (gSaveContext.playerForm == 2 || gSaveContext.playerForm == 1) {
                    textId = 0x34A7;
                } else if (!(gSaveContext.weekEventReg[16] & 4)) {
                    textId = 0x3495;
                } else {
                    textId = 0x34A5;
                }
        }
        if (textId == 0) {
            textId = 1;
        }
    }
    return textId;
}

void func_808F4054(GlobalContext* globalCtx, EnIn* this, s32 arg2, u16 textId) {
    s32 unused;

    if (textId == 0x34AE || textId == 0x34B0 || textId == 0x34B2) {
        unused = textId;
        func_80151BB4(globalCtx, 0x11);
    }
    switch (arg2) {
        case 1:
        case 5:
        case 7:
            if (textId == 0x3473) {
                func_808F35D8(this, globalCtx);
            }
            break;
        case 2:
            if (textId == 0x3473) {
                func_808F35D8(this, globalCtx);
            }
            break;
        case 0:
            break;
    }
}

void func_808F4108(EnIn* this, GlobalContext* globalCtx, u16 textId) {
    func_800B86C8(&this->actor, globalCtx, &this->unk4A4->actor);
    this->actor.textId = 0;
    this->unk4A4->actor.textId = textId;
    this->unk4A4->unk48C = 2;
    this->unk48C = 0;
}

s32 func_808F4150(GlobalContext* globalCtx, EnIn* this, s32 arg2, MessageContext* msgCtx) {
    EnIn* this2 = this;

    if (msgCtx->choiceIndex == 0) {
        func_8019F208();
        if (gSaveContext.rupees >= globalCtx->msgCtx.unk1206C) {
            func_801159EC(-globalCtx->msgCtx.unk1206C);
            if (!(gSaveContext.weekEventReg[57] & 1)) {
                func_808F4108(this, globalCtx, 0x3474);
            } else if (this->unk4AC & 8) {
                func_808F4108(this, globalCtx, 0x3475);
            } else {
                func_800E8EA0(globalCtx, &this->actor, 0x3475);
            }
        } else {
            play_sound(NA_SE_SY_ERROR);
            func_800E8EA0(globalCtx, &this->actor, 0x3473);
        }
    } else {
        func_8019F230();
        func_800E8EA0(globalCtx, &this->actor, 0x3472);
    }
    return 0;
}

s32 func_808F4270(GlobalContext* globalCtx, EnIn* this, s32 arg2, MessageContext* msgCtx, s32 arg4) {
    s32 pad;
    s32 fee = globalCtx->msgCtx.unk1206C != 0xFFFF ? globalCtx->msgCtx.unk1206C : 10;

    if (msgCtx->choiceIndex == 0) {
        func_8019F208();
        if (gSaveContext.rupees >= fee) {
            func_801159EC(-fee);
            if (!(gSaveContext.weekEventReg[57] & 1)) {
                if (arg4 != 0) {
                    func_800E8EA0(globalCtx, &this->actor, 0x3474);
                } else {
                    func_808F4108(this, globalCtx, 0x3474);
                }
            } else {
                if (arg4 != 0) {
                    func_800E8EA0(globalCtx, &this->actor, 0x3475);
                } else {
                    func_808F4108(this, globalCtx, 0x3475);
                }
            }
        } else {
            play_sound(NA_SE_SY_ERROR);
            if (arg4 != 0) {
                func_800E8EA0(globalCtx, &this->actor, 0x3473);
            } else {
                func_808F4108(this, globalCtx, 0x3473);
            }
        }
    } else {
        func_8019F230();
        func_800E8EA0(globalCtx, &this->actor, 0x3472);
    }
    return 0;
}

s32 func_808F43E0(EnIn* this) {
    this->unk48C = 0;
    this->actor.textId = 0;
    SET_FLAGS_FINISH_RACE;
    return 0;
}

s32 func_808F4414(GlobalContext* globalCtx, EnIn* this, s32 arg2) {
    u16 textId = this->actor.textId;
    s32 ret = true;
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s32 pad[2];

    switch (textId) {
        case 0x34AF:
            func_800E8EA0(globalCtx, &this->actor, 0x34B0);
            ret = false;
            break;
        case 0x34A9:
            func_808F4108(this, globalCtx, 0x34AA);
            gSaveContext.weekEventReg[63] |= 0x40;
            ret = false;
            break;
        case 0x34AA:
            func_808F4108(this, globalCtx, 0x34AB);
            ret = false;
            break;
        case 0x34AB:
            func_808F4108(this, globalCtx, 0x34AC);
            ret = false;
            break;
        case 0x34AC:
            func_808F4108(this, globalCtx, 0x34AD);
            ret = false;
            break;
        case 0x34AD:
            func_800E8EA0(globalCtx, &this->actor, 0x34AE);
            ret = false;
            break;
        case 0x34B1:
            func_800E8EA0(globalCtx, &this->actor, 0x34B2);
            ret = false;
            break;
        default:
            break;
    }

    switch (arg2) {
        case 0:
            switch (textId) {
                case 0x3458:
                    gSaveContext.weekEventReg[15] |= 8;
                    func_800E8EA0(globalCtx, &this->actor, 0x3459);
                    ret = false;
                    break;
                case 0x3459:
                    func_800E8EA0(globalCtx, &this->actor, 0x345A);
                    ret = false;
                    break;
                case 0x345A:
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x345B:
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x345C:
                    func_800E8EA0(globalCtx, &this->actor, 0x345D);
                    ret = false;
                    break;
                case 0x345D:
                    func_800E8EA0(globalCtx, &this->actor, 0x345E);
                    ret = false;
                    break;
                case 0x345E:
                    func_800E8EA0(globalCtx, &this->actor, 0x345F);
                    ret = false;
                    break;
                case 0x345F:
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x3460:
                    func_800E8EA0(globalCtx, &this->actor, 0x3461);
                    ret = false;
                    break;
                case 0x3461:
                    func_800E8EA0(globalCtx, &this->actor, 0x3462);
                    ret = false;
                    break;
                case 0x3462:
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
            }
            break;
        case 1:
            switch (textId) {
                case 0x3463:
                    gSaveContext.weekEventReg[15] |= 16;
                    func_800E8EA0(globalCtx, &this->actor, 0x3464);
                    ret = false;
                    break;
                case 0x3464:
                    func_800E8EA0(globalCtx, &this->actor, 0x3465);
                    ret = false;
                    break;
                case 0x3465:
                    func_800E8EA0(globalCtx, &this->actor, 0x3466);
                    ret = false;
                    break;
                case 0x3466:
                    if (msgCtx->choiceIndex == 0) {
                        func_8019F208();
                        if (gSaveContext.rupees >= globalCtx->msgCtx.unk1206C) {
                            if (func_80114E90()) {
                                this->actionFunc = func_808F3C40;
                                func_800B8A1C(&this->actor, globalCtx, 0x92, 500.0f, 100.0f);
                                func_801159EC(-globalCtx->msgCtx.unk1206C);
                                ret = true;
                            } else {
                                func_800E8EA0(globalCtx, &this->actor, 0x3469);
                                ret = false;
                            }
                        } else {
                            play_sound(NA_SE_SY_ERROR);
                            func_800E8EA0(globalCtx, &this->actor, 0x3468);
                            ret = false;
                        }
                    } else {
                        func_8019F230();
                        func_800E8EA0(globalCtx, &this->actor, 0x3467);
                        ret = false;
                    }
                    break;
                case 0x3467:
                case 0x3468:
                case 0x3469:
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x346B:
                    func_800E8EA0(globalCtx, &this->actor, 0x346C);
                    ret = false;
                    break;
                case 0x346C:
                    func_800E8EA0(globalCtx, &this->actor, 0x3466);
                    ret = false;
                    break;
                case 0x346A:
                    this->actionFunc = func_808F5A94;
                    func_80151BB4(globalCtx, 0x11);
                    break;
            }
            break;
        case 2:
            switch (textId) {
                case 0x346E:
                    func_808F4108(this, globalCtx, 0x346F);
                    ret = false;
                    break;
                case 0x3470:
                    func_800E8EA0(globalCtx, &this->actor, 0x3471);
                    ret = false;
                    break;
                case 0x3483:
                    func_800E8EA0(globalCtx, &this->actor, 0x3471);
                    ret = false;
                    break;
                case 0x3471:
                    func_808F4150(globalCtx, this, arg2, msgCtx);
                    ret = false;
                    break;
                case 0x3472:
                    func_808F43E0(this);
                    gSaveContext.weekEventReg[56] &= (u8)~8;
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x3473:
                    gSaveContext.weekEventReg[56] &= (u8)~8;
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x3475:
                    SET_FLAGS_START_RACE;
                    func_800FD750(0x40);
                    globalCtx->nextEntranceIndex = 0xCE50;
                    globalCtx->unk_1887F = 5;
                    globalCtx->sceneLoadFlag = 0x14;
                    gSaveContext.weekEventReg[57] |= 1;
                    break;
                case 0x3478:
                    if (msgCtx->choiceIndex == 0) {
                        func_808F4150(globalCtx, this, arg2, msgCtx);
                        ret = false;
                    } else {
                        func_8019F230();
                        gSaveContext.weekEventReg[56] &= (u8)~8;
                        func_808F4108(this, globalCtx, 0x3479);
                        ret = false;
                    }
                    break;
                case 0x347B:
                    func_808F4108(this, globalCtx, 0x347C);
                    gSaveContext.weekEventReg[56] &= (u8)~8;
                    ret = false;
                    break;
            }
            break;
        case 3:
            switch (textId) {
                case 0x346D:
                    func_808F4108(this, globalCtx, 0x346E);
                    gSaveContext.weekEventReg[56] |= 4;
                    gSaveContext.weekEventReg[56] |= 8;
                    ret = false;
                    break;
                case 0x346F:
                    func_808F4108(this, globalCtx, 0x3470);
                    ret = false;
                    break;
                case 0x3482:
                    func_808F4108(this, globalCtx, 0x3483);
                    gSaveContext.weekEventReg[56] |= 8;
                    ret = false;
                    break;
                case 0x3484:
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x3485:
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x3474:
                    func_808F4108(this, globalCtx, 0x3475);
                    ret = false;
                    break;
                case 0x3476:
                    func_800E8EA0(globalCtx, &this->actor, 0x3477);
                    func_808F30B0(&this->skelAnime, 1);
                    func_808F30B0(&this->unk4A4->skelAnime, 7);
                    ret = false;
                    break;
                case 0x3477:
                    gSaveContext.weekEventReg[56] |= 8;
                    func_808F4108(this, globalCtx, 0x3478);
                    ret = false;
                    break;
                case 0x347A:
                    func_808F30B0(&this->skelAnime, 1);
                    func_808F30B0(&this->unk4A4->skelAnime, 7);
                    if (INV_CONTENT(ITEM_MASK_GARO) == ITEM_MASK_GARO) {
                        func_800E8EA0(globalCtx, &this->actor, 0x347E);
                        ret = false;
                    } else {
                        gSaveContext.weekEventReg[56] |= 8;
                        func_808F4108(this, globalCtx, 0x347B);
                        ret = false;
                    }
                    break;
                case 0x347E:
                    func_808F35D8(this, globalCtx);
                    if (func_80114E90()) {
                        this->actionFunc = func_808F3B40;
                        func_800B8A1C(&this->actor, globalCtx, 0x92, 500.0f, 100.0f);
                        ret = true;
                    } else {
                        func_800E8EA0(globalCtx, &this->actor, 0x347F);
                        ret = false;
                    }
                    break;
                case 0x347F:
                    func_800E8EA0(globalCtx, &this->actor, 0x3480);
                    ret = false;
                    break;
                case 0x3480:
                    func_808F43E0(this);
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x3479:
                    func_808F43E0(this);
                    func_808F35D8(this, globalCtx);
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x347C:
                    this->actionFunc = func_808F3D40;
                    func_800B8A1C(&this->actor, globalCtx, 0x81, 500.0f, 100.0f);
                    func_808F35D8(this, globalCtx);
                    ret = true;
                    break;
                case 0x3481:
                    this->actionFunc = func_808F5A34;
                    func_808F43E0(this);
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x347D:
                    this->actionFunc = func_808F5A34;
                    func_808F43E0(this);
                    func_80151BB4(globalCtx, 0x11);
                    func_80151BB4(globalCtx, 0x2F);
                    ret = true;
                    break;
            }
            break;
        case 4:
            switch (textId) {
                case 0x3486:
                    func_800E8EA0(globalCtx, &this->actor, 0x3487);
                    gSaveContext.weekEventReg[16] |= 1;
                    ret = false;
                    break;
                case 0x3487:
                    func_800E8EA0(globalCtx, &this->actor, 0x3488);
                    ret = false;
                    break;
                case 0x3488:
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x3489:
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x348A:
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x348B:
                    func_800E8EA0(globalCtx, &this->actor, 0x348C);
                    ret = false;
                    break;
                case 0x348C:
                    func_800E8EA0(globalCtx, &this->actor, 0x348D);
                    ret = false;
                    break;
                case 0x348D:
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
            }
            break;
        case 5:
            switch (textId) {
                case 0x3468:
                case 0x3469:
                case 0x3491:
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x348E:
                case 0x34B3:
                    func_800E8EA0(globalCtx, &this->actor, 0x348F);
                    gSaveContext.weekEventReg[16] |= 2;
                    ret = false;
                    break;
                case 0x3493:
                    func_800E8EA0(globalCtx, &this->actor, 0x3494);
                    ret = false;
                    break;
                case 0x348F:
                case 0x3494:
                    func_800E8EA0(globalCtx, &this->actor, 0x3490);
                    ret = false;
                    break;
                case 0x3490:
                    if (msgCtx->choiceIndex == 0) {
                        func_8019F208();
                        if (gSaveContext.rupees >= globalCtx->msgCtx.unk1206C) {
                            if (func_80114E90()) {
                                this->actionFunc = func_808F3C40;
                                func_800B8A1C(&this->actor, globalCtx, 0x92, 500.0f, 100.0f);
                                func_801159EC(-globalCtx->msgCtx.unk1206C);
                                ret = true;
                            } else {
                                func_800E8EA0(globalCtx, &this->actor, 0x3469);
                                ret = false;
                            }
                        } else {
                            play_sound(NA_SE_SY_ERROR);
                            func_800E8EA0(globalCtx, &this->actor, 0x3468);
                            ret = false;
                        }
                    } else {
                        func_8019F230();
                        func_800E8EA0(globalCtx, &this->actor, 0x3491);
                        ret = false;
                    }
                    break;
                case 0x3492:
                    this->actionFunc = func_808F5A94;
                    func_80151BB4(globalCtx, 0x11);
                    break;
            }
            break;
        case 7:
            switch (textId) {
                case 0x34A8:
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x34A7:
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x3495:
                    func_808F4108(this, globalCtx, 0x3496);
                    gSaveContext.weekEventReg[16] |= 4;
                    gSaveContext.weekEventReg[56] |= 8;
                    ret = false;
                    break;
                case 0x3497:
                    func_808F4108(this, globalCtx, 0x3498);
                    ret = false;
                    break;
                case 0x34A4:
                    this->actionFunc = func_808F5A34;
                    func_808F43E0(this);
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x34A5:
                    func_808F4108(this, globalCtx, 0x34A6);
                    gSaveContext.weekEventReg[56] |= 8;
                    ret = false;
                    break;
                case 0x3473:
                    gSaveContext.weekEventReg[56] &= (u8)~8;
                    func_80151BB4(globalCtx, 0x11);
                    break;
                case 0x3474:
                    func_800E8EA0(globalCtx, &this->actor, 0x3475);
                    ret = false;
                    break;
                case 0x3475:
                    SET_FLAGS_START_RACE;
                    func_800FD750(0x40);
                    globalCtx->nextEntranceIndex = 0xCE50;
                    globalCtx->unk_1887F = 5;
                    globalCtx->sceneLoadFlag = 0x14;
                    gSaveContext.weekEventReg[57] |= 1;
                    break;
                case 0x349D:
                    func_808F30B0(&this->skelAnime, 1);
                    func_808F30B0(&this->unk4A4->skelAnime, 7);
                    if (INV_CONTENT(ITEM_MASK_GARO) == ITEM_MASK_GARO) {
                        func_800E8EA0(globalCtx, &this->actor, 0x34A1);
                        ret = false;
                    } else {
                        gSaveContext.weekEventReg[56] |= 8;
                        func_808F4108(this, globalCtx, 0x349E);
                        ret = false;
                    }
                    break;
                case 0x349F:
                    this->actionFunc = func_808F3D40;
                    func_800B8A1C(&this->actor, globalCtx, 0x81, 500.0f, 100.0f);
                    func_808F35D8(this, globalCtx);
                    ret = true;
                    break;
                case 0x34A0:
                    this->actionFunc = func_808F5A34;
                    func_80151BB4(globalCtx, 0x11);
                    func_80151BB4(globalCtx, 0x2F);
                    func_808F43E0(this);
                    ret = true;
                    break;
                case 0x34A1:
                    func_808F35D8(this, globalCtx);
                    if (func_80114E90()) {
                        this->actionFunc = func_808F3B40;
                        func_800B8A1C(&this->actor, globalCtx, 0x92, 500.0f, 100.0f);
                        ret = true;
                    } else {
                        func_800E8EA0(globalCtx, &this->actor, 0x34A2);
                        ret = false;
                    }
                    break;
                case 0x34A2:
                    func_800E8EA0(globalCtx, &this->actor, 0x34A3);
                    ret = false;
                    break;
                case 0x34A3:
                    func_808F43E0(this);
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x3499:
                    func_800E8EA0(globalCtx, &this->actor, 0x349A);
                    func_808F30B0(&this->skelAnime, 1);
                    func_808F30B0(&this->unk4A4->skelAnime, 7);
                    ret = false;
                    break;
                case 0x349A:
                    func_800E8EA0(globalCtx, &this->actor, 0x349B);
                    ret = false;
                    break;
                case 0x349B:
                    if (msgCtx->choiceIndex == 0) {
                        func_808F4270(globalCtx, this, arg2, msgCtx, 1);
                        ret = false;
                    } else {
                        func_8019F230();
                        func_800E8EA0(globalCtx, &this->actor, 0x349C);
                        ret = false;
                    }
                    break;
                case 0x349C:
                    func_808F43E0(this);
                    func_808F35D8(this, globalCtx);
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
            }
            break;
        case 6:
            switch (textId) {
                case 0x3496:
                    func_808F4108(this, globalCtx, 0x3497);
                    ret = false;
                    break;
                case 0x3498:
                case 0x34A6:
                    func_800E8EA0(globalCtx, &this->actor, 0x3471);
                    ret = false;
                    break;
                case 0x3471:
                    func_808F4270(globalCtx, this, arg2, msgCtx, 0);
                    ret = false;
                    break;
                case 0x3472:
                    func_808F43E0(this);
                    gSaveContext.weekEventReg[56] &= (u8)~8;
                    func_80151BB4(globalCtx, 0x11);
                    ret = true;
                    break;
                case 0x349E:
                    func_808F4108(this, globalCtx, 0x349F);
                    gSaveContext.weekEventReg[56] &= (u8)~8;
                    ret = false;
                    break;
            }
            break;
    }
    return ret;
}

s32 func_808F5674(GlobalContext* globalCtx, EnIn* this, s32 arg2) {
    s32 pad;
    s32 ret = false;

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 2:
            func_808F4054(globalCtx, this, arg2, this->actor.textId);
            ret = true;
            break;
        case 4:
        case 5:
            if (func_80147624(globalCtx) && func_808F4414(globalCtx, this, arg2)) {
                func_801477B4(globalCtx);
                ret = true;
            }
            break;
    }
    return ret;
}

s32 func_808F5728(GlobalContext* globalCtx, EnIn* this, s32 arg2, s32* arg3) {
    s16 rotDiff;
    s16 yawDiff;
    s16 yawDiffA;
    Player* player;

    if (*arg3 == 4) {
        return 0;
    }
    if (*arg3 == 2) {
        func_801518B0(globalCtx, this->actor.textId, &this->actor);
        *arg3 = 1;
        return 0;
    }
    if (*arg3 == 3) {
        func_80151938(globalCtx, this->actor.textId);
        *arg3 = 1;
        return 0;
    }
    if (func_800B84D0(&this->actor, globalCtx)) {
        *arg3 = 1;
        return 1;
    }
    if (*arg3 == 1) {
        player = PLAYER;
        func_808F5994(this, globalCtx, &player->actor.world.pos, 0xC80);
    dummy_label_895711:; // POSSIBLE FAKE MATCH
    } else {
        rotDiff = this->actor.home.rot.y - this->actor.world.rot.y;
        if (rotDiff > 0x320) {
            this->actor.world.rot.y += 0x320;
        } else if (rotDiff < -0x320) {
            this->actor.world.rot.y -= 0x320;
        } else {
            this->actor.world.rot.y += rotDiff;
        }
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
    if (*arg3 == 1) {
        if (func_808F5674(globalCtx, this, arg2)) {
            *arg3 = 0;
        }
        return 0;
    }
    if (!func_800B8934(globalCtx, &this->actor)) {
        return 0;
    }
    yawDiff = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    yawDiffA = ABS_ALT(yawDiff);
    if (yawDiffA >= 0x4300) {
        return 0;
    }
    if (this->actor.xyzDistToPlayerSq > SQ(160.0f) && !this->actor.isTargeted) {
        return 0;
    }
    if (this->actor.xyzDistToPlayerSq <= SQ(80.0f)) {
        if (func_800B8614(&this->actor, globalCtx, 80.0f)) {
            this->actor.textId = func_808F3DD4(globalCtx, this, arg2);
        }
    } else if (func_800B863C(&this->actor, globalCtx)) {
        this->actor.textId = func_808F3DD4(globalCtx, this, arg2);
    }
    return 0;
}

s32 func_808F5994(EnIn* this, GlobalContext* globalCtx, Vec3f* arg2, s16 arg3) {
    s32 ret = 0;
    s16 yaw = Math_Vec3f_Yaw(&this->actor.world.pos, arg2) - this->actor.world.rot.y;

    if (yaw > arg3) {
        this->actor.world.rot.y += arg3;
    } else if (yaw < -arg3) {
        this->actor.world.rot.y -= arg3;
    } else {
        this->actor.world.rot.y += yaw;
        ret = 1;
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;

    return ret;
}

void func_808F5A34(EnIn* this, GlobalContext* globalCtx) {
    if (gSaveContext.day != 3) {
        func_808F5728(globalCtx, this, 3, &this->unk48C);
    } else {
        func_808F5728(globalCtx, this, 7, &this->unk48C);
    }
}

void func_808F5A94(EnIn* this, GlobalContext* globalCtx) {
    if (func_800F41E4(globalCtx, &globalCtx->actorCtx)) {
        if (gSaveContext.day == 3) {
            func_808F5728(globalCtx, this, 7, &this->unk48C);
        } else {
            func_808F5728(globalCtx, this, 3, &this->unk48C);
        }
    } else {
        if (gSaveContext.day == 3) {
            func_808F5728(globalCtx, this, 5, &this->unk48C);
        } else {
            func_808F5728(globalCtx, this, 1, &this->unk48C);
        }
    }
}

void func_808F5B58(EnIn* this, GlobalContext* globalCtx) {
    if (func_800F41E4(globalCtx, &globalCtx->actorCtx)) {
        if ((Player_GetMask(globalCtx) == PLAYER_MASK_CIRCUS_LEADERS_MASK && gSaveContext.weekEventReg[63] & 0x40) ||
            gSaveContext.weekEventReg[56] & 8) {
            if (gSaveContext.day == 3) {
                func_808F5728(globalCtx, this, 6, &this->unk48C);
            } else {
                func_808F5728(globalCtx, this, 2, &this->unk48C);
            }
        }
    } else if (Player_GetMask(globalCtx) != PLAYER_MASK_CIRCUS_LEADERS_MASK ||
               (Player_GetMask(globalCtx) == PLAYER_MASK_CIRCUS_LEADERS_MASK && gSaveContext.weekEventReg[63] & 0x40)) {
        if (gSaveContext.day == 3) {
            func_808F5728(globalCtx, this, 4, &this->unk48C);
        } else {
            func_808F5728(globalCtx, this, 0, &this->unk48C);
        }
    }
}

void func_808F5C98(EnIn* this, GlobalContext* globalCtx) {
    if (this->unk4B0 == 0) {
        this->actionFunc = func_808F5B58;
    }
    if ((Player_GetMask(globalCtx) == PLAYER_MASK_CIRCUS_LEADERS_MASK && gSaveContext.weekEventReg[63] & 0x40) ||
        gSaveContext.weekEventReg[56] & 8) {
        if (gSaveContext.day != 3) {
            func_808F5728(globalCtx, this, 2, &this->unk48C);
        } else {
            func_808F5728(globalCtx, this, 6, &this->unk48C);
        }
    }
    if (this->unk4A8 == 2) {
        if (this->unk4B0 == 2) {
            Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LOST);
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_JOY0);
        }
        this->unk4A8 = 3;
    } else if (this->unk4A8 < 3) {
        this->unk4A8++;
    }
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

void EnIn_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnIn* this = THIS;
    s32 pad[2];
    s16 type;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 30.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06014EA8, NULL, this->limbDrawTbl, this->transitionDrawTbl, 20);
    func_808F30B0(&this->skelAnime, 0);
    Collider_InitCylinder(globalCtx, &this->colliderCylinder);
    Collider_SetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit2);
    this->unk48A = 0;
    this->unk48C = 0;
    this->unk4AC = 0;
    type = ENIN_GET_TYPE(thisx);
    this->unk4B0 = gSaveContext.weekEventReg[92] & (1 | 2 | 4);
    if (type == ENIN_HORSE_RIDER_BLUE_SHIRT || type == 4) {
        this->unk4AC |= 8;
    }
    if (type == ENIN_HORSE_RIDER_YELLOW_SHIRT || type == ENIN_HORSE_RIDER_BLUE_SHIRT) {
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
        this->unk488 = 1;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_06016A60, 1.0f, 0.0f, SkelAnime_GetFrameCount(&D_06016A60.common), 2,
                             0.0f);
        Actor_SetScale(&this->actor, 0.01f);
        this->unk23C = 0;
        this->unk23D = 1;
        this->actionFunc = func_808F374C;
    } else {
        Collider_InitJntSph(globalCtx, &this->colliderJntSph);
        Collider_SetJntSph(globalCtx, &this->colliderJntSph, &this->actor, &sJntSphInit, &this->colliderJntSphElement);
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.gravity = -4.0f;
        this->unk240 = func_8013D648(globalCtx, ENIN_GET_WALKING_FLAG(&this->actor), 0x3F);
        this->unk23D = 0;
        if (type == ENIN_YELLOW_SHIRT || type == ENIN_BLUE_SHIRT) {
            if ((gSaveContext.weekEventReg[92] & (1 | 2 | 4)) == 2 ||
                (gSaveContext.weekEventReg[92] & (1 | 2 | 4)) == 3) {
                gSaveContext.weekEventReg[56] &= (u8)~8;
                this->unk4A8 = 0;
                this->unk4AC |= 2;
                func_808F35AC(this, globalCtx);
                this->unk23C = 0;
                D_801BDAA0 = 0;
                if ((gSaveContext.weekEventReg[92] & (1 | 2 | 4)) == 2) {
                    func_808F30B0(&this->skelAnime, 6);
                } else {
                    func_808F30B0(&this->skelAnime, 4);
                }
                if ((gSaveContext.weekEventReg[92] & (1 | 2 | 4)) == 2) {
                    this->skelAnime.animCurrentFrame =
                        ((Rand_ZeroOne() * 0.6f) + 0.2f) * this->skelAnime.animFrameCount;
                }
                if (this->unk4AC & 8) {
                    this->actionFunc = func_808F39DC;
                } else {
                    this->actionFunc = func_808F5C98;
                }
            } else {
                if ((gSaveContext.weekEventReg[92] & (1 | 2 | 4)) != 1) {
                    gSaveContext.weekEventReg[56] &= (u8)~8;
                    this->unk23C = 0;
                    this->unk4AC |= 2;
                    if (type == ENIN_BLUE_SHIRT) {
                        if (func_808F33B8()) {
                            func_808F30B0(&this->skelAnime, 0);
                            this->actionFunc = func_808F5A94;
                        } else {
                            if (gSaveContext.weekEventReg[52] & 1) {
                                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_KANBAN, this->actor.world.pos.x,
                                            this->actor.world.pos.y, this->actor.world.pos.z, this->actor.shape.rot.x,
                                            this->actor.shape.rot.y, this->actor.shape.rot.z, 0xF);
                                Actor_MarkForDeath(&this->actor);
                            } else {
                                func_808F30B0(&this->skelAnime, 0);
                                this->actionFunc = func_808F5A94;
                            }
                        }
                    } else {
                        if (gSaveContext.weekEventReg[52] & 1) {
                            Actor_MarkForDeath(&this->actor);
                        } else {
                            func_808F30B0(&this->skelAnime, 7);
                            this->actionFunc = func_808F5B58;
                        }
                    }
                } else {
                    Actor_MarkForDeath(&this->actor);
                }
            }
        } else {
            this->actionFunc = func_808F3618;
        }
    }
}

void EnIn_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnIn* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
}

void EnIn_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnIn* this = THIS;

    func_808F3310(this, globalCtx);
    func_808F3334(this, globalCtx);
    if (this->unk4AC & 2) {
        this->unk4AC &= ~2;
        func_808F38F8(this, globalCtx);
    }
    if (Player_GetMask(globalCtx) == PLAYER_MASK_CIRCUS_LEADERS_MASK) {
        this->unk4AC |= 0x40;
    } else {
        this->unk4AC &= ~0x40;
    }
    this->actionFunc(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 0x4);
    func_808F3414(this, globalCtx);
    func_808F32A0(this, globalCtx);
}

void func_808F6334(EnIn* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s32 newUnk4C8;

    newUnk4C8 = func_80152498(&globalCtx->msgCtx);
    this->unk4C4 += this->unk4C0 != 0.0f ? 40.0f : -40.0f;
    this->unk4C4 = CLAMP(this->unk4C4, 0.0f, 80.0f);

    SysMatrix_InsertTranslation(this->unk4C4, 0.0f, 0.0f, MTXMODE_APPLY);
    if (this == (EnIn*)player->targetActor &&
        !(globalCtx->msgCtx.unk11F04 >= 0xFF && globalCtx->msgCtx.unk11F04 <= 0x200) && newUnk4C8 == 3 &&
        this->unk4C8 == 3) {
        if (!(globalCtx->state.frames & 1)) {
            this->unk4C0 = this->unk4C0 != 0.0f ? 0.0f : 1.0f;
        }
    } else {
        this->unk4C0 = 0.0f;
    }
    this->unk4C8 = newUnk4C8;
}

s32 EnIn_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnIn* this = THIS;
    s32 pad;
    Gfx* sp50[] = {
        NULL,       NULL,       D_060149A8, D_06014AE0, D_06014C30, D_060145D8, D_06014710,
        D_06014860, D_06014420, D_06012A78, D_06013DE0, D_06013F10, D_06014040, D_060137A0,
        D_060138D0, D_06013A00, D_06012DF8, D_06013670, D_06013540, D_06013440,
    };

    if (this->unk23C != 0 && limbIndex != 16) {
        if (sp50[limbIndex] != NULL) {
            *dList = sp50[limbIndex];
        }
    }
    if (this->unk4AC & 4 && limbIndex == 16) {
        *dList = D_0601C528;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if (limbIndex == 16) {
        void* sp38[] = { &D_060035E0, &D_06004820, &D_06004C20, &D_060043E0 };
        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sp38[this->unk482]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(&D_06003520));
    } else {
        AnimatedMat_DrawStep(globalCtx, Lib_SegmentedToVirtual(&D_06001C30), this->unk4AC & 8 ? 1 : 0);
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (limbIndex == 16) {
        SysMatrix_InsertTranslation(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->unk35A, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(-this->unk358, MTXMODE_APPLY);
        SysMatrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        func_808F6334(this, globalCtx);
    }
    if (limbIndex == 9) {
        Matrix_RotateY(this->unk360, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->unk35E, MTXMODE_APPLY);
    }
    if (limbIndex == 9 || limbIndex == 10 || limbIndex == 13) {
        rot->y += (s16)(Math_SinS(this->unk376[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->unk39E[limbIndex]) * 200.0f);
    }
    if (this->unk4AC & 0x40) {
        if (limbIndex == 18) {
            rot->x = 0x1F40;
            rot->y = -0x3E8;
            rot->z = 0x1D4C;
        } else if (limbIndex == 17) {
            rot->x = -0x1F40;
            rot->y = 0x3E8;
            rot->z = 0x1D4C;
        } else if (limbIndex == 19) {
            rot->x = 0;
            rot->y = 0x7FFF;
            rot->z = -0x2328;
        }
    }
    return 0;
}

void EnIn_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnIn* this = THIS;
    Vec3f sp50 = { 1600.0f, 0.0f, 0.0f };
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 16) {
        SysMatrix_MultiplyVector3fByState(&sp50, &this->unk4B4);
        Math_Vec3f_Copy(&this->actor.focus.pos, &this->unk4B4);
    }
    if (this->unk23D == 0) {
        Collider_UpdateSpheres(limbIndex, &this->colliderJntSph);
        if (limbIndex == 4) {
            SysMatrix_MultiplyVector3fByState(&sp44, &this->unk248);
        }
        if (limbIndex == 7) {
            SysMatrix_MultiplyVector3fByState(&sp44, &this->unk254);
        }
        if (this->unk23C == 0) {
            if (!(this->unk4AC & 8)) {
                OPEN_DISPS(globalCtx->state.gfxCtx);
                if (limbIndex == 12) {
                    gSPDisplayList(POLY_OPA_DISP++, D_06007A70);
                }
                if (limbIndex == 15) {
                    gSPDisplayList(POLY_OPA_DISP++, D_06007C48);
                }
                CLOSE_DISPS(globalCtx->state.gfxCtx);
            }
        }
    }
    if (this->unk4AC & 0x20) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        if (limbIndex == 12) {
            gSPDisplayList(POLY_OPA_DISP++, D_06007C48);
        }
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnIn_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnIn* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gDPPipeSync(POLY_OPA_DISP++);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     EnIn_OverrideLimbDraw, EnIn_PostLimbDraw, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
