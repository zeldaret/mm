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

static u8 sScheduleScript[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x11 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(0, 0, 6, 0, 0x0B - 0x0A),
    /* 0x0A */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0B */ SCHEDULE_CMD_RET_TIME(0, 0, 6, 0, 1),
    /* 0x11 */ SCHEDULE_CMD_RET_NONE(),
};

static s32 D_80BFDEB4[0x1D] = {
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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BFDF48 = {
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

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BFDF74 = { 0, 0, 0, 0, MASS_IMMOVABLE };

static AnimationInfoS D_80BFDF80[] = {
    { (AnimationHeader*)0x060007B8, 1.0f, 0, -1, 0, 0 },  { (AnimationHeader*)0x060007B8, 1.0f, 0, -1, 0, -4 },
    { (AnimationHeader*)0x060000FC, 1.0f, 0, -1, 0, -4 }, { (AnimationHeader*)0x060003A8, 1.0f, 0, -1, 0, -4 },
    { (AnimationHeader*)0x06000564, 1.0f, 0, -1, 0, -4 }, { (AnimationHeader*)0x06000218, 1.0f, 0, -1, 0, -4 },
};
static Vec3f D_80BFDFE0 = { 0.0f, 8.0f, 10.0f };
// extern u8 D_80BFDEA0[];
// extern s32 D_80BFDEB4[];
// extern ColliderCylinderInit D_80BFDF48;
// extern CollisionCheckInfoInit2 D_80BFDF74;
// extern AnimationInfoS D_80BFDF80[];
// extern Vec3f D_80BFDFE0;

extern FlexSkeletonHeader D_06002390;

void func_80BFD2E0(EnBjt* this) {
    this->skelAnime.playSpeed = this->unk238;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80BFD30C(EnBjt* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 ret = false;

    if ((arg1 == 0) || (arg1 == 1)) {
        if (!((this->unk250 == 0) || (this->unk250 == 1))) {
            phi_v1 = true;
        }
    } else if (arg1 != this->unk250) {
        phi_v1 = true;
    }
    if (phi_v1) {
        this->unk250 = arg1;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80BFDF80, arg1);
        this->unk238 = this->skelAnime.playSpeed;
    }

    return ret;
}

void func_80BFD3A4(EnBjt* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp28;
    f32 height;

    if (this->unk234 & 0x280) {
        Lib_Vec3f_TranslateAndRotateY(&this->actor.world.pos, this->actor.shape.rot.y, &D_80BFDFE0, &sp28);
        Math_Vec3f_ToVec3s(&this->collider.dim.pos, &sp28);
        height = this->actor.focus.pos.y - this->actor.world.pos.y;
        this->collider.dim.height = height;
        this->collider.dim.radius = 0x20;
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

s32 func_80BFD434(s32 exchangeItem) {
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

// EnBjt_AppearAnim
s32 func_80BFD4FC(EnBjt* this) {
    s32 ret = false;
    f32 temp_f0;

    if (this->unk248 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_TOILET_HAND_APPEAR);
        this->unk248 = 1;
    }
    Math_ApproachF(&this->actor.scale.x, 0.017f, 0.21f, 0.3f);
    if ((0.017f - this->actor.scale.x) < 0.017f / 100.0f) {
        this->actor.scale.x = 0.017f;
        this->unk234 |= 0x200;
        this->unk234 &= ~0x80;
        ret = true;
    }
    temp_f0 = (this->actor.scale.x / 0.017f) * 4.0f;
    this->unk23C = temp_f0;
    this->actor.world.pos.y = this->actor.home.pos.y + temp_f0;
    Actor_SetScale(&this->actor, this->actor.scale.x);

    return ret;
}

// EnBjt_VanishAnim
s32 func_80BFD5E4(EnBjt* this) {
    s32 ret = false;
    f32 temp_f0;

    if (this->unk248 == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_TOILET_HAND_VANISH);
        this->unk248 = 1;
    }
    Math_ApproachF(&this->actor.scale.x, 0.0f, 0.21f, 0.3f);
    if (this->actor.scale.x < 0.017f / 100.0f) {
        this->unk234 &= ~0x100;
        this->actor.scale.x = 0.0f;
        ret = true;
    }
    temp_f0 = (this->actor.scale.x / 0.017f) * 4.0f;
    this->unk23C = temp_f0;
    this->actor.world.pos.y = this->actor.home.pos.y + temp_f0;
    Actor_SetScale(&this->actor, this->actor.scale.x);
    return ret;
}

s32 func_80BFD6BC(EnBjt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 var_v1;
    s32 itemAP;
    s32 ret = 0;

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
                    if ((itemAP == 0x2B) || (itemAP == 0x2D) || (itemAP == 0x2F) || (itemAP == 0x30) ||
                        (itemAP == 0x31) || (itemAP == 0x33)) {
                        func_80BFD30C(this, 1);
                        this->unk248 = 0;
                        this->unk240++;
                        ret = 1;
                    } else if (itemAP < 0) {
                        this->unk248 = 0;
                        this->unk240++;
                        ret = 3;
                    } else if (itemAP != 0) {
                        this->unk248 = 0;
                        this->unk240++;
                        ret = 2;
                    }
                    break;
            }
            break;
        case 1:
            if (player->exchangeItemId != EXCH_ITEM_NONE) {
                func_80BFD434(player->exchangeItemId);
                player->exchangeItemId = 0;
            }
            if (func_80BFD5E4(this)) {
                this->unk242 = 60;
                this->unk240++;
                ret = 1;
            }
            break;
        case 2:
            if (DECR(this->unk242) == 0) {
                func_80BFD30C(this, 5);
                this->unk248 = 0;
                this->unk240++;
            } else if (this->unk242 == 10) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_TOILET_WATER);
            }
            break;
        case 3:
            if (func_80BFD4FC(this)) {
                this->unk240++;
                ret = 1;
            }
            break;
        case 4:
            func_80BFD30C(this, 4);
            this->unk240++;
            ret = 1;
            break;
    }
    return ret;
}

s32 func_80BFD8F0(EnBjt* this, GlobalContext* globalCtx) {
    s32 ret = false;

    if ((this->unk234 & 7) && Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->unk234 |= 8;
        SubS_UpdateFlags(&this->unk234, 0, 7);
        this->unk24C = func_80BFD6BC;
        this->unk240 = 0;
        this->actionFunc = func_80BFDA48;
        ret = true;
    }
    return ret;
}

s32 func_80BFD984(EnBjt* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u16 phi_v1 = globalCtx->msgCtx.currentTextId;

    if (player->stateFlags1 & 0x440) {
        this->unk234 |= 0x10;
        if (this->unk236 != phi_v1) {
            switch (phi_v1) {
                case 0x2949:
                    func_80BFD30C(this, 2);
                    break;

                case 0x294A:
                    func_80BFD30C(this, 3);
                    break;
            }
        }
        this->unk236 = phi_v1;
    } else {
        if (this->unk234 & 0x10) {
            this->unk234 &= ~0x10;
            func_80BFD30C(this, 0);
        }
    }
    return 0;
}

void func_80BFDA48(EnBjt* this, GlobalContext* globalCtx) {
    s16 yaw = this->actor.yawTowardsPlayer;

    if (func_8010BF58(&this->actor, globalCtx, D_80BFDEB4, this->unk24C, &this->unk1DC)) {
        this->actor.flags &= ~ACTOR_FLAG_100;
        SubS_UpdateFlags(&this->unk234, 3, 7);
        this->unk234 &= ~8;
        this->unk1DC = 0;
        this->actionFunc = func_80BFDAE8;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, yaw, 4, 0x2AA8);
    }
}

void func_80BFDAE8(EnBjt* this, GlobalContext* globalCtx) {
    ScheduleResult schResult;

    if (!Schedule_RunScript(globalCtx, sScheduleScript, &schResult)) {
        schResult.result = 0;
    }
    if (schResult.result == 1) {
        if (this->unk234 & 0x80) {
            if (func_80BFD4FC(this)) {
                SubS_UpdateFlags(&this->unk234, 3, 7);
            }
        } else if (this->unk234 & 0x100) {
            func_80BFD5E4(this);
        } else if (this->unk234 & 0x200) {
            if ((fabsf(this->actor.playerHeightRel) > 70.0f) || (this->actor.xzDistToPlayer > 140.0f) ||
                (gSaveContext.save.weekEventReg[90] & 0x80)) {
                SubS_UpdateFlags(&this->unk234, 0, 7);
                this->unk248 = 0;
                this->unk234 &= ~0x200;
                this->unk234 |= 0x100;
            }
        } else if ((fabsf(this->actor.playerHeightRel) < 20.0f) && (this->actor.xzDistToPlayer < 70.0f) &&
                   !(gSaveContext.save.weekEventReg[90] & 0x80)) {
            this->unk234 |= 0x80;
            this->unk248 = 0;
        }
        this->unk1D8 = schResult.result;
    } else {
        this->actor.flags |= ACTOR_FLAG_8000000;
        Actor_SetScale(&this->actor, 0.0f);
        this->unk234 = 0;
        this->unk24C = NULL;
        this->unk1D8 = 0;
    }
}

void EnBjt_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBjt* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06002390, NULL, this->unk1E0, this->unk20A, 7);
    this->unk250 = -1;
    func_80BFD30C(this, 0);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80BFDF48);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80BFDF74);
    this->actor.flags |= ACTOR_FLAG_8000000;
    Actor_SetScale(&this->actor, 0.0f);
    this->unk1D8 = 0;
    this->unk234 = 0;
    this->actionFunc = func_80BFDAE8;
}

void EnBjt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnBjt_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBjt* this = THIS;

    func_80BFD8F0(this, globalCtx);
    this->actionFunc(this, globalCtx);
    func_80BFD984(this, globalCtx);

    if (this->unk1D8 != 0) {
        func_80BFD2E0(this);
        func_8013C964(&this->actor, globalCtx, 60.0f, 10.0f, 0, this->unk234 & 7);
        Actor_SetFocus(&this->actor, 26.0f);
        func_80BFD3A4(this, globalCtx);
    }
}

void EnBjt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBjt* this = THIS;

    if (this->unk1D8 != 0) {
        func_8012C28C(globalCtx->state.gfxCtx);
        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              this->skelAnime.dListCount, NULL, NULL, &this->actor);
    }
}
