/*
 * File: z_en_bjt.c
 * Overlay: ovl_En_Bjt
 * Description: ??? (Hand in toilet)
 */

#include "z_en_bjt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnBjt*)thisx)

void EnBjt_Init(Actor* thisx, PlayState* play);
void EnBjt_Destroy(Actor* thisx, PlayState* play);
void EnBjt_Update(Actor* thisx, PlayState* play);
void EnBjt_Draw(Actor* thisx, PlayState* play);

void func_80BFDA48(EnBjt* this, PlayState* play);
void func_80BFDAE8(EnBjt* this, PlayState* play);

#define TOILET_HAND_STATE_8 8       // (1 << 3)
#define TOILET_HAND_STATE_10 0x10   // (1 << 4) // Talking
#define TOILET_HAND_STATE_80 0x80   // (1 << 7) // Appearing
#define TOILET_HAND_STATE_100 0x100 // (1 << 8) // Vanishing
#define TOILET_HAND_STATE_200 0x200 // (1 << 9) // Out

static u8 sScheduleScript[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x11 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 6, 0, 0x0B - 0x0A),
    /* 0x0A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0B */ SCHEDULE_CMD_RET_TIME(0, 0, 6, 0, 1),
    /* 0x11 */ SCHEDULE_CMD_RET_NONE(),
};

static s32 sMsgEventScript[] = {
    0x0E29480C, 0x0E00FF2B, 0x52,       0x5F2C29,   0x4A0C2F00, 0xC1509,    0xE29,      0x4B0C1509,
    0xE29,      0x4C0C1200, 0x4908001D, 0x09000006, 0xC0000,    0x13000C2F, 0x2E2D,     0x282D00,
    0x0D0C1149, 0x08115A80, 0x10090000, 0x06000200, 0x130002,   0x2F00002E, 0x2D000D0C, 0x115A8010,
    0x2C29490C, 0x2F00000C, 0x2D000D12, 0x102D000D, 0x12100000,
};

const ActorInit En_Bjt_InitVars = {
    ACTOR_EN_BJT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJT,
    sizeof(EnBjt),
    (ActorFunc)EnBjt_Init,
    (ActorFunc)EnBjt_Destroy,
    (ActorFunc)EnBjt_Update,
    (ActorFunc)EnBjt_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 68, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

// extern u8 D_80BFDEA0[];
// extern s32 D_80BFDEB4[];
// extern ColliderCylinderInit D_80BFDF48;
// extern CollisionCheckInfoInit2 D_80BFDF74;
// extern AnimationInfoS D_80BFDF80[];
// extern Vec3f D_80BFDFE0;

// extern FlexSkeletonHeader D_06002390;

typedef enum {
    /* -1 */ TOILET_HAND_ANIM_NONE = -1,
    /*  0 */ TOILET_HAND_ANIM_0,
    /*  1 */ TOILET_HAND_ANIM_1,
    /*  2 */ TOILET_HAND_ANIM_2,
    /*  3 */ TOILET_HAND_ANIM_THUMBS_UP,
    /*  4 */ TOILET_HAND_ANIM_4,
    /*  5 */ TOILET_HAND_ANIM_5,
} ToiletHandAnimations;

static AnimationInfoS sAnimationInfo[] = {
    { 0x060007B8, 1.0f, 0, -1, 0, 0 },  { 0x060007B8, 1.0f, 0, -1, 0, -4 }, { 0x060000FC, 1.0f, 0, -1, 0, -4 },
    { 0x060003A8, 1.0f, 0, -1, 0, -4 }, { 0x06000564, 1.0f, 0, -1, 0, -4 }, { 0x06000218, 1.0f, 0, -1, 0, -4 },
};

void EnBjt_UpdateAnimation(EnBjt* this) {
    this->skelAnime.playSpeed = this->animPlaySpead;
    SkelAnime_Update(&this->skelAnime);
}

s32 EnBjt_ChangeAnimation(EnBjt* this, s32 animIndex) {
    s32 changeAnim = false;
    s32 changed = false;

    if ((animIndex == TOILET_HAND_ANIM_0) || (animIndex == TOILET_HAND_ANIM_1)) {
        if (!((this->curAnimIndex == TOILET_HAND_ANIM_0) || (this->curAnimIndex == TOILET_HAND_ANIM_1))) {
            changeAnim = true;
        }
    } else if (this->curAnimIndex != animIndex) {
        changeAnim = true;
    }

    if (changeAnim) {
        this->curAnimIndex = animIndex;
        changed = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        this->animPlaySpead = this->skelAnime.playSpeed;
    }

    return changed;
}

void EnBjt_UpdateCollision(EnBjt* this, GlobalContext* globalCtx) {
    static Vec3f sColliderBasePos = { 0.0f, 8.0f, 10.0f };
    s32 pad;
    Vec3f pos;
    f32 height;

    if (this->stateFlags & (TOILET_HAND_STATE_80 | TOILET_HAND_STATE_200)) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &sColliderBasePos, &pos);
        Math_Vec3f_ToVec3s(&this->collider.dim.pos, &pos);
        height = this->actor.focus.pos.y - this->actor.world.pos.y;
        this->collider.dim.height = height;
        this->collider.dim.radius = 0x20;
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

s32 EnBjt_TakeItem(s32 exchangeItem) {
    switch (exchangeItem) {
        case EXCH_ITEM_LETTER_TO_KAFEI:
            func_801149A0(ITEM_LETTER_TO_KAFEI, SLOT(ITEM_LETTER_TO_KAFEI));
            break;
        case EXCH_ITEM_DEED_SWAMP:
            func_801149A0(ITEM_DEED_SWAMP, SLOT(ITEM_DEED_SWAMP));
            break;
        case EXCH_ITEM_DEED_MOUNTAIN:
            func_801149A0(ITEM_DEED_MOUNTAIN, SLOT(ITEM_DEED_MOUNTAIN));
            break;
        case EXCH_ITEM_DEED_OCEAN:
            func_801149A0(ITEM_DEED_OCEAN, SLOT(ITEM_DEED_OCEAN));
            break;
        case EXCH_ITEM_DEED_LAND:
            func_801149A0(ITEM_DEED_LAND, SLOT(ITEM_DEED_LAND));
            break;
        case EXCH_ITEM_LETTER_MAMA:
            func_801149A0(ITEM_LETTER_MAMA, SLOT(ITEM_LETTER_MAMA));
            break;
    }
    return 0;
}

#define FULLY_GROWN_SCALE 0.017f

/**
 * @return boolean true if scale is set to final value
 */
s32 EnBjt_Appear(EnBjt* this) {
    s32 finished = false;

    if (!this->playedSfx) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_TOILET_HAND_APPEAR);
        this->playedSfx = true;
    }

    Math_ApproachF(&this->actor.scale.x, FULLY_GROWN_SCALE, 0.21f, 0.3f);
    if ((FULLY_GROWN_SCALE - this->actor.scale.x) < FULLY_GROWN_SCALE / 100.0f) {
        this->actor.scale.x = FULLY_GROWN_SCALE;
        this->stateFlags |= TOILET_HAND_STATE_200;
        this->stateFlags &= ~TOILET_HAND_STATE_80;
        finished = true;
    }
    this->heightOffset = (this->actor.scale.x / FULLY_GROWN_SCALE) * 4.0f;
    this->actor.world.pos.y = this->actor.home.pos.y + this->heightOffset;
    Actor_SetScale(&this->actor, this->actor.scale.x);

    return finished;
}

/**
 * @return boolean true if scale is set to final value
 */
s32 EnBjt_Vanish(EnBjt* this) {
    s32 finished = false;

    if (!this->playedSfx) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_TOILET_HAND_VANISH);
        this->playedSfx = true;
    }

    Math_ApproachF(&this->actor.scale.x, 0.0f, 0.21f, 0.3f);
    if (this->actor.scale.x < FULLY_GROWN_SCALE / 100.0f) {
        this->actor.scale.x = 0.0f;
        this->stateFlags &= ~TOILET_HAND_STATE_100;
        finished = true;
    }
    this->heightOffset = (this->actor.scale.x / FULLY_GROWN_SCALE) * 4.0f;
    this->actor.world.pos.y = this->actor.home.pos.y + this->heightOffset;
    Actor_SetScale(&this->actor, this->actor.scale.x);

    return finished;
}

typedef enum {
    /* 0 */ TOILET_HAND_STATE_0,
    /* 0 */ TOILET_HAND_STATE_1,
    /* 0 */ TOILET_HAND_STATE_2,
    /* 0 */ TOILET_HAND_STATE_3,
    /* 0 */ TOILET_HAND_STATE_4,
} ToiletHandState;

// msgevent callback/communication
s32 func_80BFD6BC(Actor* thisx, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnBjt* this = THIS;
    s32 itemAP;
    s32 scriptBranch = 0;

    switch (this->unk240) {
        case 0:
            switch (Message_GetState(&globalCtx->msgCtx)) {
                case 4:
                case 5:
                    if (!Message_ShouldAdvance(globalCtx)) {
                        break;
                    }
                case 16:
                    itemAP = func_80123810(globalCtx);
                    if ((itemAP == EXCH_ITEM_DEED_LAND) || (itemAP == EXCH_ITEM_LETTER_TO_KAFEI) ||
                        (itemAP == EXCH_ITEM_DEED_SWAMP) || (itemAP == EXCH_ITEM_DEED_MOUNTAIN) ||
                        (itemAP == EXCH_ITEM_DEED_OCEAN) || (itemAP == EXCH_ITEM_LETTER_MAMA)) {
                        EnBjt_ChangeAnimation(this, TOILET_HAND_ANIM_1);
                        this->playedSfx = false;
                        this->unk240++;
                        scriptBranch = 1; // Right item
                    } else if (itemAP < 0) {
                        this->playedSfx = false;
                        this->unk240++;
                        scriptBranch = 3; // Wrong item
                    } else if (itemAP != 0) {
                        this->playedSfx = false;
                        this->unk240++;
                        scriptBranch = 2;
                    }
                    break;
                default:
                    break;
            }
            break;

        case 1:
            if (player->exchangeItemId != EXCH_ITEM_NONE) {
                EnBjt_TakeItem(player->exchangeItemId);
                player->exchangeItemId = EXCH_ITEM_NONE;
            }
            if (EnBjt_Vanish(this)) {
                this->timer = 60;
                this->unk240++;
                scriptBranch = 1;
            }
            break;

        case 2:
            if (DECR(this->timer) == 0) {
                EnBjt_ChangeAnimation(this, TOILET_HAND_ANIM_5);
                this->playedSfx = false;
                this->unk240++;
            } else if (this->timer == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_TOILET_WATER);
            }
            break;

        case 3:
            if (EnBjt_Appear(this)) {
                this->unk240++;
                scriptBranch = 1;
            }
            break;

        case 4:
            EnBjt_ChangeAnimation(this, TOILET_HAND_ANIM_4);
            this->unk240++;
            scriptBranch = 1;
            break;
        default:
            break;
    }
    return scriptBranch;
}

// Used in Update
s32 func_80BFD8F0(EnBjt* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->stateFlags & 7) && Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->stateFlags |= TOILET_HAND_STATE_8;
        SubS_UpdateFlags(&this->stateFlags, 0, 7);
        this->msgEventCallback = func_80BFD6BC;
        this->unk240 = 0;
        this->actionFunc = func_80BFDA48;
        ret = true;
    }
    return ret;
}

// Used in Update
s32 func_80BFD984(EnBjt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 curTextId = globalCtx->msgCtx.currentTextId;

    if (player->stateFlags1 & 0x440) {
        this->stateFlags |= TOILET_HAND_STATE_10;
        if (this->textId != curTextId) {
            switch (curTextId) {
                case 0x2949:
                    EnBjt_ChangeAnimation(this, TOILET_HAND_ANIM_2);
                    break;

                case 0x294A:
                    EnBjt_ChangeAnimation(this, TOILET_HAND_ANIM_THUMBS_UP);
                    break;
            }
        }
        this->textId = curTextId;
    } else if (this->stateFlags & TOILET_HAND_STATE_10) {
        this->stateFlags &= ~TOILET_HAND_STATE_10;
        EnBjt_ChangeAnimation(this, TOILET_HAND_ANIM_0);
    }
    return 0;
}

// Action function
void func_80BFDA48(EnBjt* this, GlobalContext* globalCtx) {
    s16 yaw = this->actor.yawTowardsPlayer;

    if (func_8010BF58(&this->actor, globalCtx, sMsgEventScript, this->msgEventCallback, &this->msgEventArg4)) {
        this->actor.flags &= ~ACTOR_FLAG_100;
        SubS_UpdateFlags(&this->stateFlags, 3, 7);
        this->stateFlags &= ~TOILET_HAND_STATE_8;
        this->msgEventArg4 = 0;
        this->actionFunc = func_80BFDAE8;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, yaw, 4, 0x2AA8);
    }
}

// Action function
void func_80BFDAE8(EnBjt* this, GlobalContext* globalCtx) {
    ScheduleResult scheduleOutput;

    if (!Schedule_RunScript(globalCtx, sScheduleScript, &scheduleOutput)) {
        scheduleOutput.result = 0;
    }
    if (scheduleOutput.result == 1) { // available
        if (this->stateFlags & TOILET_HAND_STATE_80) {
            if (EnBjt_Appear(this)) {
                SubS_UpdateFlags(&this->stateFlags, 3, 7);
            }
        } else if (this->stateFlags & TOILET_HAND_STATE_100) {
            EnBjt_Vanish(this);
        } else if (this->stateFlags & TOILET_HAND_STATE_200) {
            // Vanish if player goes too far away or heart piece given
            if ((fabsf(this->actor.playerHeightRel) > 70.0f) || (this->actor.xzDistToPlayer > 140.0f) ||
                (gSaveContext.save.weekEventReg[90] & 0x80)) {
                SubS_UpdateFlags(&this->stateFlags, 0, 7);
                this->playedSfx = false;
                this->stateFlags &= ~TOILET_HAND_STATE_200;
                this->stateFlags |= TOILET_HAND_STATE_100;
            }
        } else if ((fabsf(this->actor.playerHeightRel) < 20.0f) && (this->actor.xzDistToPlayer < 70.0f) &&
                   !(gSaveContext.save.weekEventReg[90] & 0x80)) {
            this->stateFlags |= TOILET_HAND_STATE_80;
            this->playedSfx = false;
        }
        this->scheduleResult = scheduleOutput.result;
    } else {
        this->actor.flags |= ACTOR_FLAG_8000000;
        Actor_SetScale(&this->actor, 0.0f);
        this->stateFlags = 0;
        this->msgEventCallback = NULL;
        this->scheduleResult = 0;
    }
}

void EnBjt_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBjt* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gToiletHandSkel, NULL, this->jointTable, this->morphTable,
                       TOILET_HAND_LIMB_MAX);

    this->curAnimIndex = TOILET_HAND_ANIM_NONE;
    EnBjt_ChangeAnimation(this, TOILET_HAND_ANIM_0);

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    this->actor.flags |= ACTOR_FLAG_8000000;
    Actor_SetScale(&this->actor, 0.0f);

    this->scheduleResult = 0;
    this->stateFlags = 0;
    this->actionFunc = func_80BFDAE8;
}

void EnBjt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnBjt_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBjt* this = THIS;

    func_80BFD8F0(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80BFD984(this, globalCtx);

    if (this->scheduleResult != 0) {
        EnBjt_UpdateAnimation(this);
        func_8013C964(&this->actor, globalCtx, 60.0f, 10.0f, 0, this->stateFlags & 7);
        Actor_SetFocus(&this->actor, 26.0f);
        EnBjt_UpdateCollision(this, globalCtx);
    }
}

void EnBjt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBjt* this = THIS;

    if (this->scheduleResult != 0) {
        func_8012C28C(globalCtx->state.gfxCtx);
        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              this->skelAnime.dListCount, NULL, NULL, &this->actor);
    }
}
