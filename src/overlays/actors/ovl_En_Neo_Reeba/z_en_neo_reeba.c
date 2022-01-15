/*
 * File: z_en_neo_reeba.c
 * Overlay: ovl_En_Neo_Reeba
 * Description: (New) Leevers
 */

#include "z_en_neo_reeba.h"

#define FLAGS 0x00000205

#define THIS ((EnNeoReeba*)thisx)

void EnNeoReeba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B7CA34(EnNeoReeba* this);
void func_80B7CA70(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7CB88(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7CCE0(EnNeoReeba* this);
void func_80B7CD28(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7CE34(EnNeoReeba* this);
void func_80B7CE94(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7CFA0(EnNeoReeba* this);
void func_80B7CFFC(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7D130(EnNeoReeba* this);
void func_80B7D150(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7D2E4(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7D398(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7D47C(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7D4FC(EnNeoReeba* this);
void func_80B7D5A4(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7D6D0(EnNeoReeba* this);
void func_80B7D788(EnNeoReeba* this, GlobalContext* globalCtx);
void func_80B7E0BC(EnNeoReeba* this, GlobalContext* globalCtx);

const ActorInit En_Neo_Reeba_InitVars = {
    ACTOR_EN_NEO_REEBA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RB,
    sizeof(EnNeoReeba),
    (ActorFunc)EnNeoReeba_Init,
    (ActorFunc)EnNeoReeba_Destroy,
    (ActorFunc)EnNeoReeba_Update,
    (ActorFunc)EnNeoReeba_Draw,
};
// static DamageTable sDamageTable = {
static DamageTable D_80B7E500 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xE),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xC),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xD),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
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
// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B7E520 = {
    {
        COLTYPE_HIT5,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x08, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 18, 30, 0, { 0, 0, 0 } },
};

extern AnimationHeader D_060001E4;
extern SkeletonHeader D_06001EE8;

void EnNeoReeba_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNeoReeba* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 0.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06001EE8, &D_060001E4, this->jointTable, this->morphTable, 18);
    if (!(this->actor.params & 0x8000)) {
        Actor_SetScale(&this->actor, 0.04f);
        this->actor.colChkInfo.mass = 0x5A;
        this->actor.colChkInfo.health = 1;
    } else {
        Actor_SetScale(&this->actor, 0.05f);
        this->actor.colChkInfo.mass = 0xB4;
        this->actor.colChkInfo.health = 3;
    }

    this->actor.colChkInfo.damageTable = &D_80B7E500;
    this->actor.targetMode = 2;
    this->actor.hintId = 0x47;
    this->actor.gravity = -0.5f;

    this->unk_2B0 = gZeroVec3f;
    this->unk_2BC = gZeroVec3f;

    this->unk_308 = 0;
    this->unk_30C = 0;
    this->unk_30E = 0;
    this->unk_30A = 0;
    this->unk_2F8 = 0.0f;
    this->unk_2FC = 0.0f;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B7E520);

    func_80B7CA34(this);
}

void EnNeoReeba_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNeoReeba* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B7CA34(EnNeoReeba* this) {
    this->actor.flags &= -2;
    this->actor.draw = NULL;
    this->unk_30A = 0xA;
    this->actionFunc = func_80B7CA70;
    this->actor.shape.yOffset = -2000.0f;
}

void func_80B7CA70(EnNeoReeba* this, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if ((Actor_XZDistanceToPoint(&player->actor, &this->actor.home.pos) < 200.0f) &&
        (Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && (fabsf(this->actor.playerHeightRel) < 100.0f)) {
        func_80B7CE34(this);
    }

    if (this->unk_30A == 0) {
        this->actor.world.pos = this->actor.home.pos;
        this->unk_30A = -1;
    } else {
        this->unk_30A--;
    }
}

void func_80B7CB3C(EnNeoReeba* this) {
    this->actor.shape.yOffset = 0.0f;

    if (this->actionFunc == func_80B7CFFC) {
        this->unk_30A = 0x14;
    } else {
        this->unk_30A = 0xA;
    }

    this->actionFunc = func_80B7CB88;
    this->skelAnime.playSpeed = 1.0f;
}

void func_80B7CB88(EnNeoReeba* this, GlobalContext* globalCtx) {
    Player* player;
    f32 temp_f0;
    f32 temp_f2;

    player = GET_PLAYER(globalCtx);
    temp_f0 = Actor_XZDistanceToPoint(&player->actor, &this->actor.home.pos);
    if ((temp_f0 > 200.0f) || (fabsf(this->actor.playerHeightRel) > 100.0f)) {
        func_80B7CCE0(this);
    } else {
        if (this->unk_30A == 0) {
            if ((temp_f0 < 140.0f) && (fabsf(this->actor.playerHeightRel) < 100.0f)) {
                this->unk_2B0 = player->actor.world.pos;
                this->unk_2B0.x += 10.0f * player->actor.speedXZ * Math_SinS(player->actor.world.rot.y);
                this->unk_2B0.z += 10.0f * player->actor.speedXZ * Math_CosS(player->actor.world.rot.y);
                func_80B7CFA0(this);
            } else {
                func_80B7D130(this);
            }
        }
    }
    if (this->unk_30A != 0) {
        this->unk_30A--;
    }
}

void func_80B7CCE0(EnNeoReeba* this) {
    this->unk_2F8 = 0.0f;
    this->skelAnime.playSpeed = 2.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
    this->actionFunc = func_80B7CD28;
}

void func_80B7CD28(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (Math_SmoothStepToF(&this->actor.shape.yOffset, -2000.0f, 0.5f, this->unk_2F8, 10.0f) == 0.0f) {
        func_80B7CA34(this);
    } else if ((globalCtx->gameplayFrames % 4) == 0) {
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1,
                                 8.0f, 500, 10, 1);
    }

    if (this->unk_2F8 < 300.0f) {
        this->unk_2F8 += 20.0f;
    }

    Math_ApproachF(&this->actor.shape.shadowScale, 0.0f, 1.0f, 1.0f);
}

void func_80B7CE34(EnNeoReeba* this) {
    this->actor.draw = EnNeoReeba_Draw;
    this->unk_2F8 = 300.0f;
    this->skelAnime.playSpeed = 2.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKID_APPEAR);
    this->actor.flags |= 1;
    this->actionFunc = func_80B7CE94;
}

void func_80B7CE94(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (Math_SmoothStepToF(&this->actor.shape.yOffset, 0.0f, 0.5f, this->unk_2F8, 10.0f) == 0.0f) {
        func_80B7CB3C(this);
    } else if ((globalCtx->gameplayFrames & 3) == 0) {
        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1,
                                 8.0f, 500, 10, 1);
    }

    if (this->unk_2F8 > 20.0f) {
        this->unk_2F8 = this->unk_2F8 - 10.0f;
    }

    Math_ApproachF(&this->actor.shape.shadowScale, 12.0f, 1.0f, 1.0f);
}

void func_80B7CFA0(EnNeoReeba* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIVA_MOVE);
    this->unk_30C = 0xA;
    this->unk_30A = 0x3C;
    this->actionFunc = func_80B7CFFC;
    this->skelAnime.playSpeed = 2.0f;
    this->actor.speedXZ = 14.0f;
}

void func_80B7CFFC(EnNeoReeba* this, GlobalContext* globalCtx) {
    f32 sp3C = Math_Vec3f_StepToXZ(&this->actor.world.pos, &this->unk_2B0, this->actor.speedXZ);

    Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1, 4.0f,
                             (s16)0xFA, (s16)0xA, (u8)1);

    if (sp3C < 2.0f) {
        func_80B7CB3C(this);
    } else if (sp3C < 40.0f && this->actor.speedXZ > 3.0f) {
        this->actor.speedXZ -= 2.0f;
    }

    if (this->unk_30C == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIVA_MOVE);
        this->unk_30C = 0xA;
    } else {
        this->unk_30C--;
    }

    if (this->unk_30A == 0) {
        func_80B7CB3C(this);
    } else {
        this->unk_30A--;
    }
}

void func_80B7D130(EnNeoReeba* this) {
    this->actionFunc = func_80B7D150;
    this->actor.speedXZ = 6.0f;
}

void func_80B7D150(EnNeoReeba* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 pad;
    f32 temp_f0 = Math_Vec3f_StepToXZ(&this->actor.world.pos, &this->actor.home.pos, this->actor.speedXZ);

    if (temp_f0 < 2.0f) {
        func_80B7CB3C(this);
    } else if (temp_f0 < 40.0f && this->actor.speedXZ > 3.0f) {
        this->actor.speedXZ -= 1.0f;
    }

    if ((Actor_XZDistanceToPoint(&player->actor, &this->actor.home.pos) > 200.0f) ||
        (fabsf(this->actor.playerHeightRel) > 100.0f)) {
        func_80B7CCE0(this);
    }
}

void func_80B7D254(EnNeoReeba* this) {
    this->unk_30A = 0x3C;
    this->unk_2B0 = this->actor.world.pos;
    this->unk_2B0.x -= 20.0f * Math_SinS(this->actor.yawTowardsPlayer);
    this->unk_2B0.z -= 20.0f * Math_CosS(this->actor.yawTowardsPlayer);
    this->actionFunc = func_80B7D2E4;
}

void func_80B7D2E4(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (Math_Vec3f_StepToXZ(&this->actor.world.pos, &this->unk_2B0, this->actor.speedXZ) < 2.0f) {
        func_80B7CB3C(this);
    }

    if (this->unk_30A == 0) {
        func_80B7CB3C(this);
    } else {
        this->unk_30A--;
    }
}

void func_80B7D360(EnNeoReeba* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80B7D398;
}

void func_80B7D398(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (this->unk_30E > 0) {
        this->unk_30E--;
    } else {
        this->unk_300 = 0.0f;
        this->unk_304 = 0.0f;
    }

    if (this->actor.colorFilterTimer == 0) {
        this->unk_30E = 0;
        func_80B7CB3C(this);
    }
}

void func_80B7D3EC(EnNeoReeba* this) {
    this->unk_310 = 0xB;
    this->unk_304 = 0.5f;
    this->unk_300 = 1.0f;
    if (this->actor.params & 0x8000) {
        this->unk_304 *= 1.5f;
    }

    if (this->actor.colChkInfo.health != 0) {
        this->unk_30E = 0x50;
    } else {
        this->unk_30E = 0xC;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_80B7D47C;
}

void func_80B7D47C(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (this->unk_30E == 0) {
        this->unk_30E = 0;
        this->unk_304 = 0.0f;
        this->unk_300 = 0.0f;

        if (this->actor.colChkInfo.health != 0) {
            func_80B7D4FC(this);
        } else {
            func_80B7D6D0(this);
        }

    } else if (this->unk_30E == 1) {
        this->unk_30E--;
        func_80B7E0BC(this, globalCtx);
    } else {
        this->unk_30E--;
    }
}

void func_80B7D4FC(EnNeoReeba* this) {
    this->unk_30A = 0xA;
    this->skelAnime.playSpeed = 1.0f;
    this->unk_2BC.x = Math_SinS(this->actor.yawTowardsPlayer) * -12.0f;
    this->unk_2BC.z = Math_CosS(this->actor.yawTowardsPlayer) * -12.0f;
    this->unk_2FC = 4551.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 25);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIVA_DAMAGE);
    this->actionFunc = func_80B7D5A4;
}

f32 D_80B7E54C[] = { 0.04, 0.04, 0.039, 0.042, 0.045, 0.043, 0.04, 0.035, 0.03, 0.033, 0.04 };
f32 D_80B7E578[] = { 0.04f, 0.04f, 0.041f, 0.038f, 0.035f, 0.037f, 0.04f, 0.045f, 0.05f, 0.047f, 0.04f };

void func_80B7D5A4(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (this->unk_30A == 0) {
        this->unk_2FC = 0.0f;
        func_80B7CB3C(this);
    } else {
        this->unk_308 += -0x1F40;
        Math_SmoothStepToF(&this->unk_2FC, 0.0f, 0.5f, 182.0f, 18.0f);
        this->actor.scale.x = this->actor.scale.z = D_80B7E54C[this->unk_30A];
        this->actor.scale.y = D_80B7E578[this->unk_30A];

        if (this->actor.params & 0x8000) {
            this->actor.scale.x *= 1.5f;
            this->actor.scale.y *= 1.5f;
            this->actor.scale.z *= 1.5f;
        }

        Actor_SpawnFloorDustRing(globalCtx, &this->actor, &this->actor.world.pos, this->actor.shape.shadowScale, 1,
                                 4.0f, 250, 10, 1);
        this->unk_30A += -1;
    }
}

void func_80B7D6D0(EnNeoReeba* this) {
    this->unk_30A = 0xA;
    this->unk_2BC.x = Math_SinS(this->actor.yawTowardsPlayer) * -12.0f;
    this->unk_2BC.z = Math_CosS(this->actor.yawTowardsPlayer) * -12.0f;
    this->unk_2FC = 3640.0f;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 25);
    this->actor.flags |= 0x08000000;
    this->actor.flags &= ~1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIVA_DEAD);
    this->actionFunc = func_80B7D788;
}

Vec3f D_80B7E5A4 = {0.0f, 0.0f, 0.0f};
Vec3f D_80B7E5B0 = {0.0f, 4.0f, 0.0f};

void func_80B7D788(EnNeoReeba* this, GlobalContext* globalCtx) {
    if (this->unk_30A == 0) {
        Math_ApproachZeroF(&this->actor.scale.x, 0.1f, 0.01f);
        Math_ApproachZeroF(&this->actor.scale.y, 0.1f, 0.01f);
        Math_ApproachZeroF(&this->actor.scale.z, 0.1f, 0.01f);
        Math_ApproachZeroF(&this->unk_300, 0.1f, 0.1f);
        Math_ApproachZeroF(&this->unk_304, 0.1f, 0.1f);

        if (this->actor.scale.x < 0.01f) {
            func_800B3030(globalCtx, &this->actor.world.pos, &D_80B7E5B0, &D_80B7E5A4, 0x78, 0, 0);
            Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0x60);
            Actor_MarkForDeath(&this->actor);
        }
    } else {

        if (this->unk_30A < 0xB) {
            this->unk_308 -= 0x1388;
            this->actor.scale.x = this->actor.scale.z = D_80B7E54C[this->unk_30A];
            this->actor.scale.y = D_80B7E578[this->unk_30A];

            if (this->actor.params & 0x8000) {
                this->actor.scale.x *= 1.5f;
                this->actor.scale.y *= 1.5f;
                this->actor.scale.z *= 1.5f;
            }
        }
        if (this->unk_310 == 0) {
            f32 target = 1.2f;

            if (this->actor.params & 0x8000) {
                target *= 1.5f;
            }

            Math_SmoothStepToF(&this->unk_304, target, 0.5f, 0.3f, 0.0f);
        } else {
            f32 target = 1.6f;

            if (this->actor.params & 0x8000) {
                target *= 1.5f;
            }

            Math_SmoothStepToF(&this->unk_304, target, 0.5f, 0.3f, 0.0f);
        }
        this->unk_30A--;
    }
}

void func_80B7D9B8(EnNeoReeba* this, GlobalContext* globalCtx) {
    Actor_SetFocus(&this->actor, 20.0f);
    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;

        if (this->actionFunc == func_80B7D47C) {
            switch (this->actor.colChkInfo.damageEffect) {
                case 1:
                case 3:
                case 4:
                case 13:
                case 14:
                    return;
                default:
                    if (this->unk_30E >= 2) {
                        func_80B7E0BC(this, globalCtx);
                    }
                    this->unk_30E = 0;
            }
        }

        Actor_ApplyDamage(&this->actor);

        switch (this->actor.colChkInfo.damageEffect) {
            case 3:
                func_80B7D3EC(this);
                break;
            case 2:
            case 4:
                if (this->actor.colChkInfo.damageEffect == 2) {
                    this->unk_310 = 0;
                    this->unk_30E = 0x50;
                } else {
                    this->unk_310 = 0x14;
                    this->unk_30E = 0x28;
                }
                this->unk_300 = 1.0f;
                this->unk_304 = 0.0f;
                /* fallthrough */
            case 14:
            case 15:
                if ((this->actor.colChkInfo.damageEffect == 0xF) || (this->actor.colChkInfo.damageEffect == 0xE)) {
                    this->unk_30E = 0;
                }
                if (this->actor.colChkInfo.health > 0) {
                    func_80B7D4FC(this);
                } else {
                    Enemy_StartFinishingBlow(globalCtx, &this->actor);
                    func_80B7D6D0(this);
                }
                break;

            case 13:
                this->unk_310 = 0x1E;
                this->unk_30E = 0x28;
                this->unk_300 = 1.0f;
                this->unk_304 = 2.0f;
                Actor_SetColorFilter(&this->actor, 0, 0x78, 0, 0x28);
                func_80B7D360(this);
                break;

            case 1:
                Actor_SetColorFilter(&this->actor, 0, 0x78, 0, 0x28);
                func_80B7D360(this);
                break;
        }
    } else {
        if (((this->collider.base.ocFlags2 & 1) || (this->collider.base.atFlags & 4)) &&
            (this->actionFunc == func_80B7CFFC)) {
            func_80B7D254(this);
        }
    }
    if ((this->actionFunc != func_80B7CA70) && (this->actionFunc != func_80B7CD28) &&
        (this->actionFunc != func_80B7CE94) && (this->actionFunc != func_80B7D5A4) &&
        (this->actionFunc != func_80B7D788)) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

        if (this->actionFunc != func_80B7D398) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80B7DC80(EnNeoReeba* this, GlobalContext* globalCtx) {
    if ((this->actionFunc != func_80B7CA70) && (this->actionFunc != func_80B7CD28) &&
        (this->actionFunc != func_80B7CE94)) {
        this->actor.velocity.y += this->actor.gravity;

        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.x += this->actor.colChkInfo.displacement.x;
        this->actor.world.pos.z += this->actor.colChkInfo.displacement.z;

        this->actor.world.pos.x += this->unk_2BC.x;
        this->actor.world.pos.z += this->unk_2BC.z;

        Math_ApproachZeroF(&this->unk_2BC.x, 1.0f, 2.0f);
        Math_ApproachZeroF(&this->unk_2BC.z, 1.0f, 2.0f);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 40.0f, 40.0f, 5);
    }
}

void func_80B7DD7C(EnNeoReeba* this, GlobalContext* globalCtx) {
    s32 i;
    f32 phi_f20 = 10.0f;
    f32 phi_f2 = 20.0f;
    f32 phi_f12 = 0.8f;

    if (this->actor.params & 0x8000) {
        phi_f20 *= 1.5f;
        phi_f2 *= 1.5f;
        phi_f12 *= 1.5f;
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_2C8) - 1; i++) {
        this->unk_2C8[i] = this->actor.world.pos;

        this->unk_2C8[i].x += phi_f20 * Math_SinS(BINANG_ADD(this->actor.shape.rot.y, i * 0x5555));
        this->unk_2C8[i].z += phi_f20 * Math_CosS(BINANG_ADD(this->actor.shape.rot.y, i * 0x5555));
        this->unk_2C8[i].y += 5.0f;
    }

    this->unk_2C8[ARRAY_COUNT(this->unk_2C8) - 1] = this->actor.world.pos;
    this->unk_2C8[ARRAY_COUNT(this->unk_2C8) - 1].y += phi_f2;

    this->unk_304 = phi_f12;
    func_800BE680(globalCtx, &this->actor, this->unk_2C8, ARRAY_COUNT(this->unk_2C8), phi_f12, 0.5f, this->unk_300,
                  this->unk_310);
}

void func_80B7DF34(EnNeoReeba* this, GlobalContext* globalCtx) {
    s32 i;
    f32 phi_f20 = 15.0f;

    if (this->actor.params & 0x8000) {
        phi_f20 *= 1.5f;
    }

    if ((this->unk_310 == 0) || (this->unk_310 == 0x14) || (this->unk_310 == 0x1E)) {
        for (i = 0; i < ARRAY_COUNT(this->unk_2C8) - 1; i++) {
            this->unk_2C8[i] = this->actor.world.pos;
            this->unk_2C8[i].x += phi_f20 * Math_SinS(BINANG_ADD(this->actor.shape.rot.y, i * 0x5555));
            this->unk_2C8[i].z += phi_f20 * Math_CosS(BINANG_ADD(this->actor.shape.rot.y, i * 0x5555));
            this->unk_2C8[i].y += -20.0f;
        }

        this->unk_2C8[ARRAY_COUNT(this->unk_2C8) - 1] = this->actor.world.pos;
        func_800BE680(globalCtx, NULL, this->unk_2C8, 4, this->unk_304, 0.5f, this->unk_300, this->unk_310);
    }
}

Color_RGBA8 D_80B7E5BC = {170, 255, 255, 255};
Color_RGBA8 D_80B7E5C0 = {200, 200, 255, 255};
Vec3f D_80B7E5C4 = {0.0f, -1.0f, 0.0f};

void func_80B7E0BC(EnNeoReeba* this, GlobalContext* globalCtx) {
    Vec3f spA4;
    f32 temp_f22;
    f32 temp_f24;
    s32 i;
    s16 temp_v0;
    s32 j;

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_EV_ICE_BROKEN);

    for (i = 0; i < ARRAY_COUNT(this->unk_2C8); i++) {
        temp_v0 = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_2C8[i]);
        temp_f22 = Math_SinS(temp_v0) * 3.0f;
        temp_f24 = Math_CosS(temp_v0) * 3.0f;

        for (j = 0; j < 4; j++) {
            spA4.x = (Rand_Centered() * 3.0f) + temp_f22;
            spA4.z = (Rand_Centered() * 3.0f) + temp_f24;
            spA4.y = (Rand_ZeroOne() * 6.0f) + 4.0f;
            EffectSsEnIce_Spawn(globalCtx, &this->unk_2C8[i], 0.7f, &spA4, &D_80B7E5C4, &D_80B7E5BC, &D_80B7E5C0, 30);
        }
    }
}

void func_80B7E260(EnNeoReeba* this, GlobalContext* globalCtx) {
    if ((this->actionFunc == func_80B7CB88) || (this->actionFunc == func_80B7CFFC) ||
        (this->actionFunc == func_80B7D150)) {
        if (Player_GetMask(globalCtx) == PLAYER_MASK_STONE) {
            func_80B7CCE0(this);
        }
    }
}

void EnNeoReeba_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNeoReeba* this = THIS;

    if (this->actor.params & 0x8000) {
        this->collider.dim.radius = 27;
        this->collider.dim.height = 45;
    }

    this->actionFunc(this, globalCtx);

    if ((this->actionFunc != func_80B7CA70) && (this->actionFunc != func_80B7D398) &&
        (this->actionFunc != func_80B7D47C)) {
        SkelAnime_Update(&this->skelAnime);
    }

    func_80B7D9B8(this, globalCtx);
    func_80B7DC80(this, globalCtx);
    func_80B7E260(this, globalCtx);
}

s32 func_80B7E378(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnNeoReeba* this = THIS;

    if ((limbIndex == 3) && (this->unk_2FC != 0.0f)) {
        rot->y += (s16)(this->unk_2FC * Math_SinS(this->unk_308));
        rot->z += (s16)(this->unk_2FC * Math_CosS(this->unk_308));
    }

    return false;
}

void EnNeoReeba_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnNeoReeba* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    OPEN_DISPS(globalCtx->state.gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0x01, 255, 255, 255, 255);
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80B7E378, NULL,
                      &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_30E > 0) {
        if (this->unk_310 == 0xB) {
            func_80B7DD7C(this, globalCtx);
        } else {
            func_80B7DF34(this, globalCtx);
        }
    }
}
