/*
 * File: z_en_rd.c
 * Overlay: ovl_En_Rd
 * Description: Dancing Redead/Gibdo
 */

#include "z_en_rd.h"

#define FLAGS 0x00000415

#define THIS ((EnRd*)thisx)

void EnRd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_808D41FC(GlobalContext* globalCtx);
void func_808D4308(EnRd* this);
void func_808D43AC(EnRd* this, GlobalContext* globalCtx);
void func_808D45D4(EnRd* this);
void func_808D4660(EnRd* this, GlobalContext* globalCtx);
void func_808D47DC(EnRd* this);
void func_808D4868(EnRd* this, GlobalContext* globalCtx);
void func_808D49E4(EnRd* this, GlobalContext* globalCtx);
void func_808D4A90(EnRd* this);
void func_808D4B20(EnRd* this, GlobalContext* globalCtx);
void func_808D4CA8(EnRd* this, GlobalContext* globalCtx);
void func_808D4DC4(EnRd* this);
void func_808D4E60(EnRd* this, GlobalContext* globalCtx);
void func_808D506C(EnRd* this, GlobalContext* globalCtx);
void func_808D53C0(EnRd* this, GlobalContext* globalCtx);
void func_808D5440(EnRd* this, GlobalContext* globalCtx);
void func_808D5660(EnRd* this);
void func_808D56E4(EnRd* this, GlobalContext* globalCtx);
void func_808D586C(EnRd* this);
void func_808D58CC(EnRd* this, GlobalContext* globalCtx);
void func_808D5C54(EnRd* this);
void func_808D5CCC(EnRd* this, GlobalContext* globalCtx);
void func_808D5D88(EnRd* this);
void func_808D5DF4(EnRd* this, GlobalContext* globalCtx);
void func_808D5E98(EnRd* this);
void func_808D5F18(EnRd* this, GlobalContext* globalCtx);
void func_808D6008(EnRd* this);
void func_808D6054(EnRd* this, GlobalContext* globalCtx);
void func_808D60B0(EnRd* this);
void func_808D6130(EnRd* this, GlobalContext* globalCtx);
void func_808D6200(EnRd* this, GlobalContext* globalCtx);
void func_808D6388(EnRd* this, GlobalContext* globalCtx);
void func_808D65BC(EnRd* this, GlobalContext* globalCtx);

extern FlexSkeletonHeader D_060053E8;
extern AnimationHeader D_06006678;
extern AnimationHeader D_06006B08;
extern AnimationHeader D_06006EEC;
extern AnimationHeader D_060073A4;
extern AnimationHeader D_06007BBC;
extern AnimationHeader D_060081A8;
extern AnimationHeader D_06009298;
extern AnimationHeader D_06009900;
extern AnimationHeader D_0600A450;
extern AnimationHeader D_0600ABE0;
extern FlexSkeletonHeader D_06010B88;
extern AnimationHeader D_060113EC;
extern AnimationHeader D_060118D8;
extern AnimationHeader D_06011DB8;
extern AnimationHeader D_0601216C;

const ActorInit En_Rd_InitVars = {
    ACTOR_EN_RD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRd),
    (ActorFunc)EnRd_Init,
    (ActorFunc)EnRd_Destroy,
    (ActorFunc)EnRd_Update,
    (ActorFunc)EnRd_Draw,
};

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
        { 0xF7EFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 70, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xD),
    /* Normal arrow   */ DMG_ENTRY(0, 0xD),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0xD),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xC),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};

void EnRd_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRd* this = THIS;
    s32 pad;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.targetMode = 0;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->unk_3DA = this->unk_3D8 = 0;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;
    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.colChkInfo.health = 8;
    this->unk_3DE = 255;
    this->unk_3F1 = -1;
    this->unk_3DC = ENRD_GET_FF00(thisx);

    if (ENRD_GET_80(&this->actor)) {
        this->actor.params |= 0xFF00;
    } else {
        this->actor.params &= 0xFF;
    }

    if (this->actor.params >= ENRD_GET_MINUS_1) {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06010B88, &D_0600ABE0, this->jointTable, this->morphTable,
                           26);
    } else {
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_060053E8, &D_0600ABE0, this->jointTable, this->morphTable,
                           26);
    }

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    if (this->actor.params >= ENRD_GET_MINUS_2) {
        switch (this->actor.params) {
            case 5:
                if (!func_808D41FC(globalCtx)) {
                    func_808D45D4(this);
                } else {
                    this->actor.hintId = 0x2A;
                    func_808D4308(this);
                }
                this->unkFunc = func_808D45D4;
                break;

            case 6:
                if (!func_808D41FC(globalCtx)) {
                    func_808D47DC(this);
                } else {
                    this->actor.hintId = 0x2A;
                    func_808D4308(this);
                }
                this->unkFunc = func_808D47DC;
                break;

            case 7:
                if (!func_808D41FC(globalCtx)) {
                    func_808D4A90(this);
                } else {
                    this->actor.hintId = 0x2A;
                    func_808D4308(this);
                }
                this->unkFunc = func_808D4A90;
                break;

            default:
                if (this->actor.params == ENRD_GET_MINUS_2) {
                    this->actor.hintId = 0x2D;
                } else {
                    this->actor.hintId = 0x2A;
                }
                func_808D4308(this);
                this->unkFunc = func_808D4308;
                break;
        }
    } else {
        func_808D4DC4(this);
    }

    SkelAnime_Update(&this->skelAnime);

    if (this->actor.params == ENRD_GET_3) {
        this->actor.flags |= 0x80;
    }

    if (this->actor.params == ENRD_GET_4) {
        s32 pad2;

        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_OBJ_ICE_POLY, this->actor.world.pos.x,
                           this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x,
                           this->actor.world.rot.y, this->actor.world.rot.z, 0xFF4B);
    }
}

void EnRd_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRd* this = THIS;

    if (gSaveContext.unk_3F58 != 0) {
        gSaveContext.unk_3F58 = 0;
    }
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_808D4190(GlobalContext* globalCtx, EnRd* this, s32 arg2) {
    Actor* actor = globalCtx->actorCtx.actorList[ACTORCAT_ENEMY].first;

    while (actor != NULL) {
        if ((actor->id != ACTOR_EN_RD) || (this == (EnRd*)actor) || (actor->params < ENRD_GET_0)) {
            actor = actor->next;
            continue;
        } else if (arg2 != 0) {
            actor->parent = &this->actor;
        } else if (this == (EnRd*)actor->parent) {
            actor->parent = NULL;
        }
        actor = actor->next;
    }
}

s32 func_808D41FC(GlobalContext* globalCtx) {
    if ((Player_GetMask(globalCtx) == PLAYER_MASK_GIBDO_MASK) ||
        (Player_GetMask(globalCtx) == PLAYER_MASK_CAPTAINS_HAT) ||
        (Player_GetMask(globalCtx) == PLAYER_MASK_GAROS_MASK)) {
        return false;
    }
    return true;
}

void func_808D4260(EnRd* this, GlobalContext* globalCtx) {
    if ((this->actor.params >= ENRD_GET_5) && (this->actionFunc != func_808D4660) &&
        (this->actionFunc != func_808D4868) && (this->actionFunc != func_808D4B20) &&
        (this->actionFunc != func_808D65BC) && (this->actionFunc != func_808D58CC) &&
        (this->actionFunc != func_808D6200) && (this->actionFunc != func_808D6388)) {
        if (!func_808D41FC(globalCtx)) {
            this->unkFunc(this);
        }
    }
}

void func_808D4308(EnRd* this) {
    if (this->actor.params != ENRD_GET_2) {
        Animation_MorphToLoop(&this->skelAnime, &D_0600ABE0, -6.0f);
    } else {
        Animation_PlayLoop(&this->skelAnime, &D_060081A8);
    }

    this->unk_3EF = 0;
    this->unk_3D6 = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808D43AC;
}

void func_808D43AC(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 100, 0);
    if ((this->actor.params == ENRD_GET_2) && Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (Rand_ZeroOne() >= 0.5f) {
            Animation_PlayLoop(&this->skelAnime, &D_060081A8);
        } else {
            Animation_PlayLoop(&this->skelAnime, &D_06007BBC);
        }
    } else {
        this->unk_3D6--;
        if (this->unk_3D6 == 0) {
            this->unk_3D6 = (Rand_ZeroOne() * 10.0f) + 10.0f;
            this->skelAnime.curFrame = 0.0f;
        }
    }

    if (this->actor.parent != NULL) {
        if (this->unk_3EC == 0) {
            if (this->actor.params != ENRD_GET_2) {
                func_808D5660(this);
            } else {
                func_808D6008(this);
            }
        }
    } else {
        if (this->unk_3EC != 0) {
            if (this->actor.params != ENRD_GET_2) {
                func_808D5C54(this);
            } else {
                func_808D6008(this);
            }
        }

        this->unk_3EC = 0;
        if ((this->actor.xzDistToPlayer <= 150.0f) && func_800B715C(globalCtx)) {
            if ((this->actor.params != ENRD_GET_2) && (this->unk_3EC == 0)) {
                func_808D5C54(this);
            } else {
                func_808D6008(this);
            }
        }
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_808D45D4(EnRd* this) {
    Animation_MorphToLoop(&this->skelAnime, &D_0601216C, -6.0f);
    this->unk_3EF = 14;
    this->unk_3D6 = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->unk_3E4 = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808D4660;
}

void func_808D4660(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 100, 0);
    if (this->unk_3EC != 0) {
        func_808D5C54(this);
    }

    this->unk_3EC = 0;
    if ((this->actor.xzDistToPlayer <= 150.0f) && func_808D41FC(globalCtx) && func_800B715C(globalCtx)) {
        if (this->actor.params == ENRD_GET_MINUS_2) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        Animation_Change(&this->skelAnime, &D_060073A4, 0.0f, 0.0f, 19.0f, 2, -10.0f);
        this->actionFunc = func_808D49E4;
    }

    if (func_808D41FC(globalCtx)) {
        if (this->actor.params == ENRD_GET_MINUS_2) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        func_808D4308(this);
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_808D47DC(EnRd* this) {
    Animation_MorphToLoop(&this->skelAnime, &D_06011DB8, -6.0f);
    this->unk_3EF = 15;
    this->unk_3D6 = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->unk_3E4 = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808D4868;
}

void func_808D4868(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 100, 0);
    if (this->unk_3EC != 0) {
        func_808D5C54(this);
    }

    this->unk_3EC = 0;
    if ((this->actor.xzDistToPlayer <= 150.0f) && func_808D41FC(globalCtx) && func_800B715C(globalCtx)) {
        if (this->actor.params == ENRD_GET_MINUS_2) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        Animation_Change(&this->skelAnime, &D_060073A4, 0.0f, 0.0f, 19.0f, 2, -10.0f);
        this->actionFunc = func_808D49E4;
    }

    if (func_808D41FC(globalCtx)) {
        if (this->actor.params == ENRD_GET_MINUS_2) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        func_808D4308(this);
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_808D49E4(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }

    this->unk_3E4++;
    if (this->unk_3E4 > 10) {
        if ((this->actor.params != ENRD_GET_2) && (this->unk_3EC == 0)) {
            func_808D5C54(this);
        } else {
            func_808D6008(this);
        }
        this->unk_3E4 = 0;
    }
}

void func_808D4A90(EnRd* this) {
    Animation_MorphToLoop(&this->skelAnime, &D_060118D8, -6.0f);
    this->unk_3EF = 16;
    this->unk_3D6 = (Rand_ZeroOne() * 10.0f) + 5.0f;
    this->unk_3E4 = 4370;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_808D4B20;
}

void func_808D4B20(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 100, 0);
    if (this->unk_3EC != 0) {
        func_808D5C54(this);
    }

    this->unk_3EC = 0;
    if ((this->actor.xzDistToPlayer <= 150.0f) && func_808D41FC(globalCtx) && func_800B715C(globalCtx)) {
        if (this->actor.params == ENRD_GET_MINUS_2) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        this->actionFunc = func_808D4CA8;
    }

    if (func_808D41FC(globalCtx)) {
        if (this->actor.params == ENRD_GET_MINUS_2) {
            this->actor.hintId = 0x2D;
        } else {
            this->actor.hintId = 0x2A;
        }
        func_808D4308(this);
    }

    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->unk_3E4 = 4370;
    } else if (Animation_OnFrame(&this->skelAnime, 15.0f)) {
        this->unk_3E4 = 6554;
    }

    this->actor.world.rot.y -= this->unk_3E4;
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_808D4CA8(EnRd* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }

    this->actor.world.rot.y -= this->unk_3E4;
    this->actor.shape.rot.y = this->actor.world.rot.y;

    this->unk_3E4 -= 100;
    if ((this->unk_3E4 < 2100) && (this->unk_3E4 >= 2000)) {
        Animation_Change(&this->skelAnime, &D_060073A4, 0.0f, 0.0f, 19.0f, 2, -10.0f);
    } else if (this->unk_3E4 < 1000) {
        if ((this->actor.params != ENRD_GET_2) && (this->unk_3EC == 0)) {
            func_808D5C54(this);
        } else {
            func_808D6008(this);
        }
    }
}

void func_808D4DC4(EnRd* this) {
    Animation_Change(&this->skelAnime, &D_0600ABE0, 0.0f, 0.0f, Animation_GetLastFrame(&D_0600ABE0), 0, -6.0f);
    this->unk_3EF = 13;
    this->unk_3D6 = 6;
    this->actor.shape.rot.x = -0x4000;
    this->actor.gravity = 0.0f;
    this->actor.shape.yOffset = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_808D4E60;
}

void func_808D4E60(EnRd* this, GlobalContext* globalCtx) {
    if (this->actor.shape.rot.x != -0x4000) {
        Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 1, 0x7D0, 0);
        if (Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 0.3f, 2.0f, 0.3f) == 0.0f) {
            this->actor.gravity = -3.5f;
            func_808D4308(this);
        }
    } else {
        if (this->actor.world.pos.y == this->actor.home.pos.y) {
            Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
        }

        if (Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 50.0f, 0.3f, 2.0f, 0.3f) == 0.0f) {
            if (this->unk_3D6 != 0) {
                this->unk_3D6--;
                Math_SmoothStepToF(&this->actor.speedXZ, 6.0f, 0.3f, 1.0f, 0.3f);
            } else if (Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 0.3f, 1.0f, 0.3f) == 0.0f) {
                Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 1, 0x7D0, 0);
            }
        }
    }
}

void func_808D4FE0(EnRd* this, GlobalContext* globalCtx) {
    f32 frameCount = Animation_GetLastFrame(&D_060113EC);

    Animation_Change(&this->skelAnime, &D_060113EC, 1.0f, 4.0f, frameCount, 1, -4.0f);
    this->actor.speedXZ = 0.4f;
    this->unk_3EF = 4;
    this->actionFunc = func_808D506C;
}

void func_808D506C(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s16 sp36 = ((this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->unk_3D8) - this->unk_3DA;

    this->skelAnime.playSpeed = this->actor.speedXZ;
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 250, 0);
    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 100, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);

    if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 150.0f) {
        func_808D53C0(this, globalCtx);
    }

    if ((ABS_ALT(sp36) < 0x1554) && (Actor_DistanceBetweenActors(&this->actor, &player->actor) <= 150.0f)) {
        if (!(player->stateFlags1 & (0x200000 | 0x80000 | 0x40000 | 0x4000 | 0x2000 | 0x80)) &&
            !(player->stateFlags2 & 0x4080)) {
            if (this->unk_3ED == 0) {
                if (!(this->unk_3DC & 0x80)) {
                    player->actor.freezeTimer = 40;
                    func_80123E90(globalCtx, &this->actor);
                    GET_PLAYER(globalCtx)->unk_A78 = &this->actor;
                    func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
                }
                this->unk_3ED = 60;
                Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_AIM);
            }
        } else {
            func_808D53C0(this, globalCtx);
        }
    }

    if (this->unk_3EE != 0) {
        this->unk_3EE--;
    }

    if (!this->unk_3EE && (Actor_DistanceBetweenActors(&this->actor, &player->actor) <= 45.0f) &&
        Actor_IsFacingPlayer(&this->actor, 0x38E3)) {
        player->actor.freezeTimer = 0;
        if ((player->transformation == PLAYER_FORM_GORON) || (player->transformation == PLAYER_FORM_DEKU)) {
            if (Actor_DistanceToPoint(&this->actor, &this->actor.home.pos) < 150.0f) {
                func_808D5D88(this);
            } else {
                func_808D53C0(this, globalCtx);
            }
        } else if (globalCtx->grabPlayer(globalCtx, player)) {
            this->actor.flags &= ~1;
            func_808D586C(this);
        }
    } else if (this->actor.params > ENRD_GET_0) {
        if (this->actor.parent != NULL) {
            func_808D5660(this);
        } else {
            this->unk_3EC = 0;
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_808D53C0(EnRd* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &D_060113EC, 0.5f, 0.0f, Animation_GetLastFrame(&D_060113EC), 1, -4.0f);
    this->unk_3EF = 2;
    this->actionFunc = func_808D5440;
}

void func_808D5440(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    s16 sp36 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);

    if (Actor_DistanceToPoint(&this->actor, &this->actor.home.pos) >= 5.0f) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp36, 1, 450, 0);
    } else {
        this->actor.speedXZ = 0.0f;
        if (!Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 1, 450, 0)) {
            if (this->actor.params != ENRD_GET_2) {
                func_808D4308(this);
            } else {
                func_808D60B0(this);
            }
        }
    }

    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 100, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 100, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);

    if (!(player->stateFlags1 & (0x200000 | 0x80000 | 0x40000 | 0x4000 | 0x2000 | 0x80)) &&
        !(player->stateFlags2 & 0x4080) && (player->transformation != PLAYER_FORM_GORON) &&
        (player->transformation != PLAYER_FORM_DEKU) &&
        (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) < 150.0f)) {
        this->actor.targetMode = 0;
        func_808D4FE0(this, globalCtx);
    } else if (this->actor.params > ENRD_GET_0) {
        if (this->actor.parent != NULL) {
            func_808D5660(this);
        } else {
            this->unk_3EC = 0;
        }
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_808D5660(EnRd* this) {
    f32 frameCount = Animation_GetLastFrame(&D_060113EC);

    Animation_Change(&this->skelAnime, &D_060113EC, 0.5f, 0.0f, frameCount, 1, -4.0f);
    this->unk_3EF = 3;
    this->unk_3EC = 1;
    this->actionFunc = func_808D56E4;
}

void func_808D56E4(EnRd* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 yaw;
    Vec3f sp2C;

    if (this->actor.parent != NULL) {
        sp2C = this->actor.parent->world.pos;
        yaw = Actor_YawToPoint(&this->actor, &sp2C);

        Math_SmoothStepToS(&this->actor.shape.rot.y, yaw, 1, 250, 0);
        if (Actor_DistanceToPoint(&this->actor, &sp2C) >= 45.0f) {
            this->actor.speedXZ = 0.4f;
        } else {
            this->actor.speedXZ = 0.0f;
            if (this->actor.params != ENRD_GET_2) {
                func_808D4308(this);
            } else {
                func_808D60B0(this);
            }
        }
        Math_SmoothStepToS(&this->unk_3D8, 0, 1, 100, 0);
        Math_SmoothStepToS(&this->unk_3DA, 0, 1, 100, 0);
    } else {
        func_808D4FE0(this, globalCtx);
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 10.0f) || Animation_OnFrame(&this->skelAnime, 22.0f)) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_RIZA_WALK);
    } else if ((globalCtx->gameplayFrames & 0x5F) == 0) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_CRY);
    }
}

void func_808D586C(EnRd* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06006EEC);
    this->unk_3D6 = 0;
    this->unk_3EB = 0;
    this->unk_3EA = 200;
    this->unk_3EF = 10;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_808D58CC;
}

void func_808D58CC(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->unk_3EB++;
    }

    switch (this->unk_3EB) {
        case 1:
            Animation_PlayLoop(&this->skelAnime, &D_06006678);
            this->unk_3EB++;
            globalCtx->damagePlayer(globalCtx, -8);
            func_8013ECE0(this->actor.xzDistToPlayer, 255, 1, 12);
            this->unk_3EA = 20;

        case 0:
            Math_SmoothStepToS(&this->unk_3D8, 0, 1, 1500, 0);
            Math_SmoothStepToS(&this->unk_3DA, 0, 1, 1500, 0);

        case 2:
            if (!(player->stateFlags2 & 0x80) || (player->unk_B62 != 0)) {
                if ((player->unk_B62 != 0) && (player->stateFlags2 & 0x80)) {
                    player->stateFlags2 &= ~0x80;
                    player->unk_AE8 = 100;
                }
                Animation_Change(&this->skelAnime, &D_06006B08, 0.5f, 0.0f, Animation_GetLastFrame(&D_06006B08), 3,
                                 0.0f);
                this->unk_3EB++;
                this->unk_3EF = 4;
                break;
            }

            switch (player->transformation) {
                case 0:
                case 1:
                case 2:
                case 3:
                    break;

                case 4:
                    Math_SmoothStepToF(&this->actor.shape.yOffset, -1500.0f, 1.0f, 150.0f, 0.0f);
                    break;
            }

            Math_SmoothStepToF(&this->actor.world.pos.x,
                               (Math_SinS(player->actor.shape.rot.y) * -25.0f) + player->actor.world.pos.x, 1.0f, 10.0f,
                               0.0f);
            Math_SmoothStepToF(&this->actor.world.pos.y, player->actor.world.pos.y, 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->actor.world.pos.z,
                               (Math_CosS(player->actor.shape.rot.y) * -25.0f) + player->actor.world.pos.z, 1.0f, 10.0f,
                               0.0f);
            Math_SmoothStepToS(&this->actor.shape.rot.y, player->actor.shape.rot.y, 1, 6000, 0);

            if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
                Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_ATTACK);
            }

            this->unk_3EA--;
            if (this->unk_3EA == 0) {
                globalCtx->damagePlayer(globalCtx, -8);
                func_8013ECE0(this->actor.xzDistToPlayer, 240, 1, 12);
                this->unk_3EA = 20;
                func_800B8E58(player, player->ageProperties->unk_92 + 0x6805);
            }
            break;

        case 3:
            if (player->transformation != PLAYER_FORM_FIERCE_DEITY) {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            break;

        case 4:
            if (player->transformation != PLAYER_FORM_FIERCE_DEITY) {
                Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 1.0f, 400.0f, 0.0f);
            }
            this->actor.targetMode = 0;
            this->actor.flags |= 1;
            this->unk_3ED = 10;
            this->unk_3EE = 15;
            func_808D4FE0(this, globalCtx);
            break;
    }
}

void func_808D5C54(EnRd* this) {
    Animation_Change(&this->skelAnime, &D_060073A4, 0.0f, 0.0f, Animation_GetLastFrame(&D_060073A4), 2, 0.0f);
    this->unk_3EF = 7;
    this->actionFunc = func_808D5CCC;
}

void func_808D5CCC(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 temp_v0 = ((this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->unk_3D8) - this->unk_3DA;

    if (ABS_ALT(temp_v0) < 0x2008) {
        if (!(this->unk_3DC & 0x80)) {
            player->actor.freezeTimer = 60;
            func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
            func_80123E90(globalCtx, &this->actor);
        }
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_AIM);
        func_808D4FE0(this, globalCtx);
    }
}

void func_808D5D88(EnRd* this) {
    this->unk_3EF = 8;
    Animation_MorphToPlayOnce(&this->skelAnime, &D_06009900, -6.0f);
    this->actor.speedXZ = -2.0f;
    Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->unk_3EF = 8;
    this->actionFunc = func_808D5DF4;
}

void func_808D5DF4(EnRd* this, GlobalContext* globalCtx) {
    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 300, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 300, 0);
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_808D5E98(this);
    }
}

void func_808D5E98(EnRd* this) {
    f32 frameCount = Animation_GetLastFrame(&D_060113EC);

    Animation_Change(&this->skelAnime, &D_060113EC, 0.5f, 0.0f, frameCount, 1, -4.0f);
    this->unk_3EF = 9;
    this->unk_3D4 = 0;
    this->actionFunc = func_808D5F18;
}

void func_808D5F18(EnRd* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, BINANG_ROT180(this->actor.yawTowardsPlayer), 5, 3500, 200);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (this->unk_3D4 > 60) {
        func_808D53C0(this, globalCtx);
        this->unk_3D4 = 0;
    } else {
        this->unk_3D8 = Math_SinS(this->unk_3D4 * 4000) * (9583.0f * ((60 - this->unk_3D4) / 60.0f));
        SkelAnime_Update(&this->skelAnime);
        this->unk_3D4++;
    }
}

void func_808D6008(EnRd* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &D_0600A450, -4.0f);
    this->unk_3EF = 5;
    this->actionFunc = func_808D6054;
}

void func_808D6054(EnRd* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.parent != NULL) {
            func_808D5660(this);
        } else {
            func_808D5C54(this);
        }
    }
}

void func_808D60B0(EnRd* this) {
    Animation_Change(&this->skelAnime, &D_0600A450, -1.0f, Animation_GetLastFrame(&D_0600A450), 0.0f, 2, -4.0f);
    this->unk_3EF = 6;
    this->actionFunc = func_808D6130;
}

void func_808D6130(EnRd* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_808D4308(this);
    }
}

void func_808D616C(EnRd* this) {
    this->actor.shape.yOffset = 0.0f;
    Animation_MorphToPlayOnce(&this->skelAnime, &D_06009900, -6.0f);
    if (this->actor.bgCheckFlags & 1) {
        this->actor.speedXZ = -2.0f;
    }

    this->actor.flags |= 1;
    Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_DAMAGE);
    this->unk_3EF = 11;
    this->actionFunc = func_808D6200;
}

void func_808D6200(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actor.speedXZ < 0.0f) {
        this->actor.speedXZ += 0.15f;
    }

    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 300, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 300, 0);

    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.parent != NULL) {
            func_808D5660(this);
        } else if (Actor_DistanceToPoint(&player->actor, &this->actor.home.pos) >= 150.0f) {
            func_808D53C0(this, globalCtx);
        } else {
            func_808D4FE0(this, globalCtx);
        }
        this->unk_3F1 = -1;
    }
}

void func_808D6310(EnRd* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &D_06009298, -1.0f);
    this->unk_3EF = 12;
    this->unk_3D6 = 300;
    this->actor.flags &= ~1;
    this->actor.speedXZ = 0.0f;
    Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_REDEAD_DEAD);
    this->actionFunc = func_808D6388;
}

void func_808D6388(EnRd* this, GlobalContext* globalCtx) {
    if (this->actor.category != 6) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, 6);
    }

    Math_SmoothStepToS(&this->unk_3D8, 0, 1, 2000, 0);
    Math_SmoothStepToS(&this->unk_3DA, 0, 1, 2000, 0);

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_3D6 == 0) {
            if (!Flags_GetSwitch(globalCtx, this->unk_3DC & 0x7F)) {
                Flags_SetSwitch(globalCtx, this->unk_3DC & 0x7F);
            }

            if (this->unk_3DE != 0) {
                if (this->unk_3DE == 180) {
                    func_808D4190(globalCtx, this, 0);
                }
                this->actor.scale.y -= (75.0f / 1000000.0f);
                this->unk_3DE -= 5;
            } else {
                Actor_MarkForDeath(&this->actor);
            }
        } else {
            this->unk_3D6--;
        }
    } else if (Animation_OnFrame(&this->skelAnime, 33.0f) || Animation_OnFrame(&this->skelAnime, 40.0f)) {
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_GERUDOFT_DOWN);
    }
}

void func_808D64D0(EnRd* this) {
    this->unk_3EF = 1;
    this->unk_3D6 = 0xA;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (gSaveContext.unk_3F58 != 0) {
        this->unk_3E9 = 1;
        this->unk_3E0 = 600;
        Actor_PlaySfxByPos2(&this->actor, NA_SE_EN_LIGHT_ARROW_HIT);
        Actor_SetColorFilter(&this->actor, 0x8000, 0x80C8, 0, 255);
    } else if (this->unk_3F0 == 1) {
        Actor_SetColorFilter(&this->actor, 0, 0xC8, 0, 40);
    } else if (this->unk_3F0 == 12) {
        Actor_SetColorFilter(&this->actor, 0, 0xC8, 0, 40);
    }
    this->actionFunc = func_808D65BC;
}

void func_808D65BC(EnRd* this, GlobalContext* globalCtx) {
    if (this->unk_3D6 > 0) {
        this->unk_3D6--;
    }

    if (this->unk_3E9 != 0) {
        if (this->unk_3E0 != 0) {
            this->unk_3E0--;
            if (this->unk_3E0 >= 255) {
                Actor_SetColorFilter(&this->actor, 0x8000, 0x80C8, 0, 255);
            }

            if (this->unk_3E0 == 0) {
                this->unk_3E9 = 0;
                gSaveContext.unk_3F58 = 0;
            }
        }
    }

    if (this->actor.colorFilterTimer == 0) {
        if (this->actor.colChkInfo.health == 0) {
            func_808D4190(globalCtx, this, 1);
            func_808D6310(this);
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x90);
        } else {
            func_808D616C(this);
        }
    }
}

void func_808D66A0(EnRd* this, GlobalContext* globalCtx) {
    s16 phi_v0 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y) - this->unk_3DA;
    s16 temp_v0 = CLAMP(phi_v0, -0x1F4, 0x1F4);

    phi_v0 -= this->unk_3D8;
    phi_v0 = CLAMP(phi_v0, -0x1F4, 0x1F4);

    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) >= 0) {
        this->unk_3DA += ABS_ALT(temp_v0);
        this->unk_3D8 += ABS_ALT(phi_v0);
    } else {
        this->unk_3DA -= ABS_ALT(temp_v0);
        this->unk_3D8 -= ABS_ALT(phi_v0);
    }

    this->unk_3DA = CLAMP(this->unk_3DA, -0x495F, 0x495F);
    this->unk_3D8 = CLAMP(this->unk_3D8, -0x256F, 0x256F);
}

void func_808D6814(EnRd* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if ((gSaveContext.unk_3F58 != 0) && (this->actor.shape.rot.x == 0) && (this->unk_3E9 == 0) &&
        (this->unk_3EF != 11) && (this->unk_3EF != 12) && (this->unk_3EF != 1)) {
        func_808D64D0(this);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        this->unk_3F0 = this->actor.colChkInfo.damageEffect;

        if (this->unk_3EF == 13) {
            return;
        }

        Actor_SetDropFlag(&this->actor, &this->collider.info);

        if (player->unk_ADC != 0) {
            this->unk_3F1 = player->unk_ADD;
        }

        switch (this->unk_3F0) {
            case 12:
                if ((this->actionFunc != func_808D58CC) &&
                    ((this->actionFunc != func_808D65BC) || (this->unk_3D6 == 0))) {
                    this->unk_3E6 = 40;
                    this->unk_3E8 = 30;
                    this->unk_294 = 1.0f;
                    func_808D64D0(this);
                }
                return;

            case 1:
                func_808D64D0(this);
                return;

            case 2:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
                this->unk_3E6 = 180;
                this->unk_3E8 = 0;
                this->unk_3E9 = 0;
                this->unk_3E0 = 0;
                this->unk_294 = 1.0f;
                break;

            case 4:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
                this->unk_3E6 = 60;
                this->unk_3E8 = 20;
                this->unk_3E9 = 0;
                this->unk_3E0 = 0;
                this->unk_294 = 1.0f;
                break;

            case 15:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                this->unk_3E9 = 0;
                this->unk_3E0 = 0;
                break;

            case 14:
                Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
                this->unk_3E9 = 0;
                this->unk_3E0 = 0;
                this->actor.colChkInfo.health = 0;
                break;

            default:
                return;
        }

        Actor_ApplyDamage(&this->actor);
        if (this->actor.colChkInfo.health == 0) {
            func_808D4190(globalCtx, this, 1);
            func_808D6310(this);
            Item_DropCollectibleRandom(globalCtx, NULL, &this->actor.world.pos, 0x90);
        } else {
            func_808D616C(this);
        }
    }
}

void func_808D6A94(EnRd* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((this->actor.colChkInfo.health > 0) && (this->unk_3EF != 10)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (((this->unk_3EF != 11) || ((player->unk_ADC != 0) && (player->unk_ADD != this->unk_3F1))) &&
            ((this->actionFunc != func_808D65BC) || (this->unk_3D6 == 0))) {
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_808D6B64(EnRd* this, GlobalContext* globalCtx) {
    if (this->unk_3E6 > 0) {
        this->unk_3E6--;
    }

    if (this->unk_3E6 < 20) {
        Math_SmoothStepToF(&this->unk_298, 0.0f, 0.5f, 0.03f, 0.0f);
        this->unk_294 = this->unk_3E6 * 0.05f;
    } else {
        Math_SmoothStepToF(&this->unk_298, 0.5f, 0.1f, 0.02f, 0.0f);
    }
}

void EnRd_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRd* this = THIS;

    func_808D6814(this, globalCtx);
    if ((gSaveContext.unk_3F58 != 0) && (this->unk_3E9 == 0)) {
        gSaveContext.unk_3F58 = 0;
    }

    if ((this->unk_3F0 != 6) && ((this->unk_3EF != 13) || (this->unk_3F0 != 2))) {
        if (this->unk_3ED != 0) {
            this->unk_3ED--;
        }

        this->actionFunc(this, globalCtx);

        if ((this->unk_3EF != 10) && (this->actor.speedXZ != 0.0f)) {
            Actor_MoveWithGravity(&this->actor);
        }

        if ((this->actor.shape.rot.x == 0) && (this->unk_3EF != 10) && (this->actor.speedXZ != 0.0f)) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 20.0f, 35.0f, 0x1D);
        }

        if (this->unk_3EF == 7) {
            func_808D66A0(this, globalCtx);
        }
    }

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 50.0f;
    func_808D6A94(this, globalCtx);
    func_808D4260(this, globalCtx);
    func_808D6B64(this, globalCtx);
}

s32 EnRd_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                          Gfx** gfx) {
    EnRd* this = THIS;

    if (limbIndex == 23) {
        rot->y += this->unk_3D8;
    } else if (limbIndex == 12) {
        rot->y += this->unk_3DA;
    }
    return false;
}

void EnRd_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnRd* this = THIS;

    if ((this->unk_3E6 != 0) &&
        ((limbIndex == 3) || (limbIndex == 4) || (limbIndex == 6) || (limbIndex == 8) || (limbIndex == 9) ||
         (limbIndex == 11) || (limbIndex == 14) || (limbIndex == 16) || (limbIndex == 17) || (limbIndex == 18) ||
         (limbIndex == 20) || (limbIndex == 21) || (limbIndex == 22) || (limbIndex == 24) || (limbIndex == 25))) {
        Matrix_GetStateTranslation(&this->unk_1DC[this->unk_290]);
        this->unk_290++;
    }
}

void EnRd_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f D_808D7138 = { 0.25f, 0.25f, 0.25f };
    s32 pad;
    EnRd* this = THIS;
    Vec3f sp54 = this->actor.world.pos;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    this->unk_290 = 0;

    if (this->unk_3DE == 255) {
        func_8012C28C(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->unk_3DE);
        gSPSegment(POLY_OPA_DISP++, 0x08, D_801AEFA0);

        POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnRd_OverrideLimbDraw, EnRd_PostLimbDraw,
                                           &this->actor, POLY_OPA_DISP);

        func_800BC620(&sp54, &D_808D7138, 255, globalCtx);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);

        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_3DE);
        gSPSegment(POLY_XLU_DISP++, 0x08, D_801AEF88);

        POLY_XLU_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, EnRd_OverrideLimbDraw, NULL, &this->actor, POLY_XLU_DISP);
        func_800BC620(&sp54, &D_808D7138, this->unk_3DE, globalCtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_3E6 > 0) {
        func_800BE680(globalCtx, &this->actor, this->unk_1DC, ARRAY_COUNT(this->unk_1DC), this->unk_298, 0.5f,
                      this->unk_294, this->unk_3E8);
    }
}
