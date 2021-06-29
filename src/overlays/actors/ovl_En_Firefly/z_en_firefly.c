/*
 * File: z_en_firefly.c
 * Overlay: ovl_En_Firefly
 * Description: Keese (Normal, Fire, Ice)
 */

#include "z_en_firefly.h"
#include "overlays/actors/ovl_Obj_Syokudai/z_obj_syokudai.h"

#define FLAGS 0x00005005

#define THIS ((EnFirefly*)thisx)

void EnFirefly_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80879CC0(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A110(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A1C8(EnFirefly* this);
void func_8087A1EC(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A268(EnFirefly* this);
void func_8087A2D8(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A548(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A5DC(EnFirefly* this);
void func_8087A60C(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A818(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A8FC(EnFirefly* this);
void func_8087A920(EnFirefly* this, GlobalContext* globalCtx);
void func_8087A9E0(EnFirefly* this);
void func_8087AA1C(EnFirefly* this, GlobalContext* globalCtx);

const ActorInit En_Firefly_InitVars = {
    ACTOR_EN_FIREFLY,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FIREFLY,
    sizeof(EnFirefly),
    (ActorFunc)EnFirefly_Init,
    (ActorFunc)EnFirefly_Destroy,
    (ActorFunc)EnFirefly_Update,
    (ActorFunc)EnFirefly_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x01, 0x08 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_HARD,
        BUMP_ON,
        OCELEM_ON,
    },
    { 1, { { 0, 1000, 0 }, 15 }, 100 },
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 10, 10, 10 };

static DamageTable sDamageTable = {
    0x10, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x22, 0x32, 0x42, 0x01, 0x01,
    0x01, 0x02, 0x10, 0x50, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 5, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 4000, ICHAIN_STOP),
};

extern AnimationHeader D_0600017C;
extern SkeletonHeader D_060018B8;
extern Gfx D_06001678[];

void EnFirefly_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_060018B8, &D_0600017C, this->jointTable, this->morphTable, 28);
    Collider_InitAndSetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    if (this->actor.params & 0x8000) {
        this->actor.flags |= 0x80;
        if (1) {}
        this->actor.params &= 0x7FFF;
        this->unk_18E = 1;
    }

    if (this->actor.params == 0) {
        this->unk_18C = 1;
        this->unk_190 = Rand_S16Offset(20, 60);
        this->actor.shape.rot.x = 0x1554;
        this->actor.hintId = 0x11;
        this->unk_2E4 = this->actor.home.pos.y;
        this->actionFunc = func_80879CC0;
    } else if (this->actor.params == 4) {
        this->unk_18C = 2;
        this->collider.info.toucher.effect = 2;
        this->actor.hintId = 0x56;
        this->unk_2E4 = this->actor.home.pos.y + 100.0f;
        this->actionFunc = func_80879CC0;
    } else {
        this->unk_18C = 0;
        this->collider.info.toucher.effect = 0;
        this->actor.hintId = 0x12;
        this->unk_2E4 = this->actor.home.pos.y + 100.0f;
        this->actionFunc = func_8087A920;
    }
    this->unk_18D = this->actor.params;
    this->collider.dim.worldSphere.radius = sSphereInit.dim.modelSphere.radius;
}

void EnFirefly_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFirefly* this = THIS;

    Collider_DestroySphere(globalCtx, &this->collider);
}

void func_808798C4(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->unk_18F == 0xA) {
        this->unk_18F = 0;
        this->unk_2E8.x = 0.0f;
        func_800BF7CC(globalCtx, &this->actor, &this->unk_2F8, 3, 2, 0.2f, 0.2f);
    }
}

void func_80879930(EnFirefly* this) {
    this->unk_18D = 3;
    this->collider.info.toucher.effect = 0;
    this->unk_18C = 0;
    this->actor.hintId = 0x12;
}

void func_80879950(EnFirefly* this) {
    if (this->actor.params == 0) {
        this->unk_18D = 0;
        this->collider.info.toucher.effect = 1;
        this->unk_18C = 1;
        this->actor.hintId = 0x11;
    }
}

s32 func_8087997C(EnFirefly* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    f32 distFromHome;

    if (this->actor.params != 3) {
        return false;
    }

    if (Actor_XZDistanceToPoint(&player->base, &this->actor.home.pos) > 300.0f) {
        distFromHome = Actor_DistanceToPoint(&this->actor, &this->actor.home.pos);

        if (distFromHome < 5.0f) {
            func_8087A8FC(this);
            return true;
        }

        if (distFromHome * 0.05f < 1.0f) {
            this->actor.speedXZ *= distFromHome * 0.05f;
        }

        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x300);
        Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &this->actor.home.pos) + 0x1554,
                           0x100);

        return true;
    }

    return false;
}

s32 func_80879A98(EnFirefly* this, GlobalContext* globalCtx) {
    ObjSyokudai* findTorch;
    ObjSyokudai* closestTorch;
    f32 currentDist;
    f32 currentMinDist;
    Vec3f flamePos;

    findTorch = (ObjSyokudai*)globalCtx->actorCtx.actorList[ACTORCAT_PROP].first;
    closestTorch = NULL;
    currentMinDist = 35000.0f;

    if ((this->actor.params != 0) || (this->unk_18D != 3)) {
        return false;
    }

    while (findTorch != NULL) {
        if ((findTorch->actor.id == ACTOR_OBJ_SYOKUDAI) && (findTorch->unk_1DC != 0)) {
            currentDist = Actor_DistanceBetweenActors(&this->actor, &findTorch->actor);
            if (currentDist < currentMinDist) {
                currentMinDist = currentDist;
                closestTorch = findTorch;
            }
        }
        findTorch = (ObjSyokudai*)findTorch->actor.next;
    }

    if (closestTorch != NULL) {
        flamePos.x = closestTorch->actor.world.pos.x;
        flamePos.y = closestTorch->actor.world.pos.y + 52.0f + 30.0f;
        flamePos.z = closestTorch->actor.world.pos.z;

        if (Actor_DistanceToPoint(&this->actor, &flamePos) < 15.0f) {
            func_80879950(this);
        } else {
            Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawBetweenActors(&this->actor, &closestTorch->actor),
                               0x300);
            Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &flamePos) + 0x1554, 0x100);
        }

        return true;
    }

    return false;
}

void func_80879C14(EnFirefly* this) {
    this->unk_190 = Rand_S16Offset(70, 100);
    this->actor.speedXZ = (Rand_ZeroOne() * 1.5f) + 1.5f;
    Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x300);
    this->unk_192 = ((this->unk_2E4 < this->actor.world.pos.y) ? 0xC00 : -0xC00) + 0x1554;
    this->skelAnime.animPlaybackSpeed = 1.0f;
    this->actionFunc = func_80879CC0;
}

void func_80879CC0(EnFirefly* this, GlobalContext* globalCtx) {
    s32 skelAnimeUpdated;
    f32 rand;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_190 != 0) {
        this->unk_190--;
    }

    skelAnimeUpdated = func_801378B8(&this->skelAnime, 0.0f);
    this->actor.speedXZ = (Rand_ZeroOne() * 1.5f) + 1.5f;

    if (!func_8087997C(this, globalCtx) && !func_80879A98(this, globalCtx)) {
        if (skelAnimeUpdated) {
            rand = Rand_ZeroOne();

            if (rand < 0.5f) {
                Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos),
                                   0x300);
            } else if (rand < 0.8f) {
                this->actor.shape.rot.y += (s16)randPlusMinusPoint5Scaled(1536.0f);
            }

            // Climb if too close to ground
            if (this->actor.world.pos.y < this->actor.floorHeight + 20.0f) {
                this->unk_192 = 0x954;
                // Descend if above maxAltitude
            } else if (this->unk_2E4 < this->actor.world.pos.y) {
                this->unk_192 = 0x2154;
                // Otherwise ascend or descend at random, biased towards ascending
            } else if (Rand_ZeroOne() > 0.35f) {
                this->unk_192 = 0x954;
            } else {
                this->unk_192 = 0x2154;
            }
        } else {
            if (this->actor.bgCheckFlags & 1) {
                this->unk_192 = 0x954;
            } else if ((this->actor.bgCheckFlags & 0x10) || (this->unk_2E4 < this->actor.world.pos.y)) {
                this->unk_192 = 0x2154;
            }
        }

        Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk_192, 0x100);
    }

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.wallYaw, 2, 0xC00, 0x300);
    }

    if ((this->unk_190 == 0) && (this->actor.xzDistToPlayer < 200.0f) && (func_8012403C(globalCtx) != 0x10)) {
        func_8087A268(this);
    }
}

void func_80879F28(EnFirefly* this, GlobalContext* globalCtx) {
    this->unk_190 = 40;
    this->actor.velocity.y = 0.0f;
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600017C, 0.0f, 6.0f, 6.0f, 2, 0.0f);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_FFLY_DEAD);
    this->actor.flags |= 0x10;

    if (this->unk_18E != 0) {
        func_800BCB70(&this->actor, 0x4000, 255, 0x2000, 40);
    } else {
        func_800BCB70(&this->actor, 0x4000, 255, 0, 40);
    }

    if (this->actor.colChkInfo.damageEffect == 3) {
        this->unk_18F = 0xA;
        this->unk_2E8.x = 1.0f;
        this->unk_2E8.y = 0.55f;
        this->unk_2E8.z = 0.82500005f;
    } else if (this->actor.colChkInfo.damageEffect == 4) {
        this->unk_18F = 0x14;
        this->unk_2E8.x = 4.0f;
        this->unk_2E8.y = 0.55f;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                    this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0, 3);
    } else if (this->actor.colChkInfo.damageEffect == 2) {
        this->unk_18F = 0;
        this->unk_2E8.x = 4.0f;
        this->unk_2E8.y = 0.55f;
    }

    if (this->unk_2E8.x > 0.0f) {
        this->unk_18C = 0;
    }

    if ((this->actor.flags & 0x8000) != 0) {
        this->actor.speedXZ = 0.0f;
    }

    this->actionFunc = func_8087A110;
}

void func_8087A110(EnFirefly* this, GlobalContext* globalCtx) {
    this->actor.colorFilterTimer = 40;
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);

    if (!(this->actor.flags & 0x8000)) {
        if (this->unk_18F != 0xA) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x6800, 0x200);
            this->actor.shape.rot.y += -0x300;
        }
        if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == BGCHECK_Y_MIN)) {
            func_808798C4(this, globalCtx);
            func_8087A1C8(this);
        }
    }
}

void func_8087A1C8(EnFirefly* this) {
    this->unk_190 = 15;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_8087A1EC;
}

void func_8087A1EC(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->unk_190 != 0) {
        this->unk_190--;
    }

    Math_StepToF(&this->actor.scale.x, 0.0f, 0.00034f);
    this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;

    if (this->unk_190 == 0) {
        Item_DropCollectibleRandom(globalCtx, &this->actor, &this->actor.world.pos, 0xA0);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_8087A268(EnFirefly* this) {
    this->unk_190 = Rand_S16Offset(70, 100);
    this->skelAnime.animPlaybackSpeed = 1.0f;
    this->unk_192 = ((this->actor.yDistToPlayer > 0.0f) ? -0xC00 : 0xC00) + 0x1554;
    this->actionFunc = func_8087A2D8;
}

void func_8087A2D8(EnFirefly* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    Vec3f preyPos;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    if (this->unk_190 != 0) {
        this->unk_190--;
    }

    Math_StepToF(&this->actor.speedXZ, 4.0f, 0.5f);

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.wallYaw, 2, 0xC00, 0x300);
        Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk_192, 0x100);
    } else if (Actor_IsActorFacingLink(&this->actor, 0x2800)) {
        if (func_801378B8(&this->skelAnime, 4.0f)) {
            this->skelAnime.animPlaybackSpeed = 0.0f;
            this->skelAnime.animCurrentFrame = 4.0f;
        }

        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xC00, 0x300);
        preyPos.x = player->base.world.pos.x;
        preyPos.y = player->base.world.pos.y + 20.0f;
        preyPos.z = player->base.world.pos.z;
        Math_SmoothStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &preyPos) + 0x1554, 2, 0x400,
                           0x100);
    } else {
        this->skelAnime.animPlaybackSpeed = 1.5f;
        if (this->actor.xzDistToPlayer > 80.0f) {
            Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xC00, 0x300);
        }

        if (this->actor.bgCheckFlags & 1) {
            this->unk_192 = 0x954;
        }

        if ((this->actor.bgCheckFlags & 0x10) || (this->unk_2E4 < this->actor.world.pos.y)) {
            this->unk_192 = 0x2154;
        } else {
            this->unk_192 = 0x954;
        }

        Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk_192, 0x100);
    }

    if ((this->unk_190 == 0) || (func_8012403C(globalCtx) == 0x10) || (player->unkA70 & 0x80) ||
        (player->base.freezeTimer > 0)) {
        func_8087A5DC(this);
    }
}

void func_8087A50C(EnFirefly* this) {
    this->actor.world.rot.x = 0x7000;
    this->unk_190 = 18;
    this->skelAnime.animPlaybackSpeed = 1.0f;
    this->actor.speedXZ = 2.5f;
    this->actionFunc = func_8087A548;
}

void func_8087A548(EnFirefly* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x100);
    Math_StepToF(&this->actor.velocity.y, 0.0f, 0.4f);
    if (Math_StepToF(&this->actor.speedXZ, 0.0f, 0.15f) != 0) {
        if (this->unk_190 != 0) {
            this->unk_190--;
        }

        if (this->unk_190 == 0) {
            func_8087A5DC(this);
        }
    }
}

void func_8087A5DC(EnFirefly* this) {
    this->unk_190 = 150;
    this->unk_192 = 0x954;
    this->actionFunc = func_8087A60C;
    this->skelAnime.animPlaybackSpeed = 1.0f;
}

void func_8087A60C(EnFirefly* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    if (this->unk_190 != 0) {
        this->unk_190--;
    }

    if ((fabsf(this->actor.world.pos.y - this->unk_2E4) < 10.0f) &&
            (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) < 20.0f) ||
        (this->unk_190 == 0)) {
        func_80879C14(this);
        return;
    }

    Math_StepToF(&this->actor.speedXZ, 3.0f, 0.3f);

    if (this->actor.bgCheckFlags & 1) {
        this->unk_192 = 0x954;
    } else if ((this->actor.bgCheckFlags & 0x10) || (this->unk_2E4 < this->actor.world.pos.y)) {
        this->unk_192 = 0x2154;
    } else {
        this->unk_192 = 0x954;
    }

    if (this->actor.bgCheckFlags & 8) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.wallYaw, 2, 0xC00, 0x300);
    } else {
        Math_ScaledStepToS(&this->actor.shape.rot.y, Actor_YawToPoint(&this->actor, &this->actor.home.pos), 0x300);
    }

    Math_ScaledStepToS(&this->actor.shape.rot.x, this->unk_192, 0x100);
}

void func_8087A774(EnFirefly* this) {
    if (this->unk_18E != 0) {
        func_800BCB70(&this->actor, 0, 255, 0x2000, this->unk_190);
    } else {
        func_800BCB70(&this->actor, 0, 255, 0, this->unk_190);
    }

    if (this->actionFunc != func_8087A818) {
        this->actor.velocity.y = 0.0f;
        this->actor.speedXZ = 0.0f;
    }

    this->unk_18C = 0;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_COMMON_FREEZE);
    this->actionFunc = func_8087A818;
}

void func_8087A818(EnFirefly* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0x1554, 0x100);
    if ((this->actor.bgCheckFlags & 1) || (this->actor.floorHeight == BGCHECK_Y_MIN)) {
        if (this->unk_190 != 0) {
            this->unk_190--;
        }

        if (this->unk_190 == 0) {
            if (this->unk_18D == 0) {
                this->unk_18C = 1;
            } else if (this->unk_18D == 4) {
                this->unk_18C = 2;
            }

            func_80879C14(this);
        }
    } else {
        this->actor.colorFilterTimer = 40;

        if (this->unk_2E8.x > 0.0f) {
            this->unk_2E8.x = 2.0f;
        }
    }
}

void func_8087A8FC(EnFirefly* this) {
    this->unk_190 = 1;
    this->actionFunc = func_8087A920;
    this->actor.speedXZ = 0.0f;
}

void func_8087A920(EnFirefly* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x100);
    if (this->unk_190 != 0) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        if (func_801378B8(&this->skelAnime, 6.0f)) {
            this->unk_190--;
        }
    } else if (Rand_ZeroOne() < 0.02f) {
        this->unk_190 = 1;
    }

    if (this->actor.xzDistToPlayer < 120.0f) {
        func_8087A9E0(this);
    }
}

void func_8087A9E0(EnFirefly* this) {
    this->skelAnime.animPlaybackSpeed = 3.0f;
    this->actor.shape.rot.x = 0x1554;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->unk_190 = 50;
    this->actor.speedXZ = 3.0f;
    this->actionFunc = func_8087AA1C;
}

void func_8087AA1C(EnFirefly* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    Vec3f preyPos;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);

    if (this->unk_190 != 0) {
        this->unk_190--;
    }
    if (this->unk_190 < 40) {
        Math_ScaledStepToS(&this->actor.shape.rot.x, -0xAAC, 0x100);
    } else {
        preyPos.x = player->base.world.pos.x;
        preyPos.y = player->base.world.pos.y + 20.0f;
        preyPos.z = player->base.world.pos.z;
        Math_ScaledStepToS(&this->actor.shape.rot.x, Actor_PitchToPoint(&this->actor, &preyPos) + 0x1554, 0x100);
        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x300);
    }

    if (this->unk_190 == 0) {
        func_80879C14(this);
    }
}

void func_8087AAF4(EnFirefly* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & 2) {
        this->collider.base.acFlags &= ~2;
        func_800BE258(&this->actor, &this->collider.info);

        if (this->actor.colChkInfo.damageEffect == 1) {
            this->unk_190 = 40;
            func_8087A774(this);
        } else if (this->actor.colChkInfo.damageEffect == 5) {
            this->unk_190 = 40;
            this->unk_18F = 0x1F;
            this->unk_2E8.x = 2.0f;
            this->unk_2E8.y = 0.55f;
            func_8087A774(this);
        } else {
            func_800BBA88(globalCtx, &this->actor);
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= ~1;

            if (((this->unk_18D == 0) && (this->actor.colChkInfo.damageEffect == 2)) ||
                ((this->unk_18D == 4) && (this->actor.colChkInfo.damageEffect == 3))) {
                this->actor.colChkInfo.damageEffect = 0;
            }
            func_80879F28(this, globalCtx);
        }
    }
}

void EnFirefly_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnFirefly* this = THIS;

    if (this->collider.base.atFlags & 2) {
        this->collider.base.atFlags &= ~2;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_FFLY_ATTACK);

        if (this->unk_18D != 3) {
            func_80879930(this);
        }

        if (this->actionFunc != func_8087AA1C) {
            func_8087A50C(this);
        }
    }

    func_8087AAF4(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if (!(this->actor.flags & 0x8000)) {
        if ((this->actor.colChkInfo.health == 0) || (this->actionFunc == func_8087A818)) {
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        } else {
            if (this->actionFunc != func_8087A548) {
                this->actor.world.rot.x = 0x1554 - this->actor.shape.rot.x;
            }

            Actor_SetVelocityAndMoveXYRotation(&this->actor);
        }
    }

    func_800B78B8(globalCtx, &this->actor, 10.0f, 10.0f, 15.0f, 7);
    this->collider.dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.dim.worldSphere.center.y = (s32)this->actor.world.pos.y + 10;
    this->collider.dim.worldSphere.center.z = this->actor.world.pos.z;

    if ((this->actionFunc == func_8087A2D8) || (this->actionFunc == func_8087AA1C)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }

    if (this->actor.colChkInfo.health != 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
        this->actor.world.rot.y = this->actor.shape.rot.y;

        if (func_801378B8(&this->skelAnime, 5.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_FFLY_FLY);
        }
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);

    if (this->unk_2E8.x > 0.0f) {
        if (this->unk_18F != 0xA) {
            Math_StepToF(&this->unk_2E8.x, 0.0f, 0.05f);
            this->unk_2E8.y = (this->unk_2E8.x + 1.0f) * 0.275f;
            this->unk_2E8.y = CLAMP_MAX(this->unk_2E8.y, 0.55f);
        } else if (!Math_StepToF(&this->unk_2E8.z, 0.55f, 0.01375f)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }

    this->actor.focus.pos.x =
        10.0f * Math_SinS(this->actor.shape.rot.x) * Math_SinS(this->actor.shape.rot.y) + this->actor.world.pos.x;
    this->actor.focus.pos.y = 10.0f * Math_CosS(this->actor.shape.rot.x) + this->actor.world.pos.y;
    this->actor.focus.pos.z =
        10.0f * Math_SinS(this->actor.shape.rot.x) * Math_CosS(this->actor.shape.rot.y) + this->actor.world.pos.z;
}

s32 func_8087AF48(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnFirefly* this = THIS;

    if ((this->unk_18E != 0) && (globalCtx->actorCtx.unk4 != 0x64)) {
        *dList = NULL;
    } else if (limbIndex == 1) {
        pos->y += 2300.0f;
    }
    return false;
}

void func_8087AF98(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Color_RGBA8 D_8087B4D4 = { 255, 255, 100, 255 };
    static Color_RGBA8 D_8087B4D8 = { 255, 50, 0, 0 };
    static Color_RGBA8 D_8087B4DC = { 100, 200, 255, 255 };
    static Color_RGBA8 D_8087B4E0 = { 0, 0, 255, 0 };
    static Vec3f D_8087B4E4 = { 0.0f, 0.5f, 0.0f };
    static Vec3f D_8087B4F0 = { 0.0f, 0.5f, 0.0f };
    Vec3f auraPos;
    Color_RGBA8* auraPrimColor;
    Color_RGBA8* auraEnvColor;
    s16 auraScaleStep;
    s16 auraLife;
    s32 pad;
    EnFirefly* this = THIS;

    if ((this->unk_18D != 0) && (limbIndex == 27)) {
        gSPDisplayList((*gfx)++, D_06001678);
    } else if ((this->unk_2F4 != globalCtx->gameplayFrames) && ((this->unk_18C == 1) || (this->unk_18C == 2)) &&
               ((limbIndex == 15) || (limbIndex == 21))) {
        if (this->actionFunc != func_8087A1EC) {
            SysMatrix_GetStateTranslation(&auraPos);
            auraPos.x += Rand_ZeroFloat(5.0f);
            auraPos.y += Rand_ZeroFloat(5.0f);
            auraPos.z += Rand_ZeroFloat(5.0f);
            auraScaleStep = -40;
            auraLife = 3;
        } else {
            if (limbIndex == 15) {
                auraPos.x = Math_SinS(9100 * this->unk_190) * this->unk_190 + this->actor.world.pos.x;
                auraPos.z = Math_CosS(9100 * this->unk_190) * this->unk_190 + this->actor.world.pos.z;
            } else {
                auraPos.x = this->actor.world.pos.x - Math_SinS(9100 * this->unk_190) * this->unk_190;
                auraPos.z = this->actor.world.pos.z - Math_CosS(9100 * this->unk_190) * this->unk_190;
            }

            auraPos.y = this->actor.world.pos.y + (15 - this->unk_190) * 1.5f;
            auraScaleStep = -5;
            auraLife = 10;
        }

        if (this->unk_18C == 1) {
            auraPrimColor = &D_8087B4D4;
            auraEnvColor = &D_8087B4D8;
        } else {
            auraPrimColor = &D_8087B4DC;
            auraEnvColor = &D_8087B4E0;
        }

        func_800B0F80(globalCtx, &auraPos, &D_8087B4E4, &D_8087B4F0, auraPrimColor, auraEnvColor, 250, auraScaleStep,
                      auraLife);
    }

    if (limbIndex == 15) {
        SysMatrix_GetStateTranslation(&this->unk_2F8);
    } else if (limbIndex == 21) {
        SysMatrix_GetStateTranslation(&this->unk_304);
    } else if (limbIndex == 10) {
        SysMatrix_GetStateTranslation(&this->unk_310);
    }
}

void EnFirefly_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFirefly* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_18E != 0) {
        gfx = POLY_XLU_DISP;
    } else {
        gfx = POLY_OPA_DISP;
    }

    gSPDisplayList(gfx, &sSetupDL[150]);

    if (this->unk_18D == 0) {
        gDPSetEnvColor(gfx + 1, 0, 0, 0, 0);
    } else {
        gDPSetEnvColor(gfx + 1, 0, 0, 0, 255);
    }

    gfx = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, func_8087AF48,
                          func_8087AF98, &this->actor, gfx + 2);
    if (this->unk_18E != 0) {
        POLY_XLU_DISP = gfx;
    } else {
        POLY_OPA_DISP = gfx;
    }

    func_800BE680(globalCtx, NULL, &this->unk_2F8, 3, this->unk_2E8.y * this->actor.scale.y * 200.0f, this->unk_2E8.z,
                  this->unk_2E8.x, this->unk_18F);
    this->unk_2F4 = globalCtx->gameplayFrames;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
