/*
 * File: z_en_insect.c
 * Overlay: ovl_En_Insect
 * Description: Single freestanding bug that doesn't burrow
 */

#include "z_en_insect.h"

#define FLAGS 0x00000000

void EnInsect_Init(Actor* thisx, PlayState* play);
void EnInsect_Destroy(Actor* thisx, PlayState* play2);
void EnInsect_Update(Actor* thisx, PlayState* play);
void EnInsect_Draw(Actor* thisx, PlayState* play);

void EnInsect_SetupSlowDown(EnInsect* this);
void EnInsect_SlowDown(EnInsect* this, PlayState* play);
void EnInsect_SetupCrawl(EnInsect* this);
void EnInsect_Crawl(EnInsect* this, PlayState* play);
void EnInsect_SetupRunFromPlayer(EnInsect* this);
void EnInsect_RunFromPlayer(EnInsect* this, PlayState* play);
void EnInsect_Caught(EnInsect* this, PlayState* play);
void EnInsect_SetupDig(EnInsect* this);
void EnInsect_Dig(EnInsect* this, PlayState* play);
void EnInsect_SetupWalkOnWater(EnInsect* this);
void EnInsect_WalkOnWater(EnInsect* this, PlayState* play);
void EnInsect_SetupDrown(EnInsect* this);
void EnInsect_Drown(EnInsect* this, PlayState* play);

/**
 * The number of bugs caught this frame.
 */
static s16 sCaughtCount = 0;

ActorProfile En_Insect_Profile = {
    /**/ ACTOR_EN_INSECT,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnInsect),
    /**/ EnInsect_Init,
    /**/ EnInsect_Destroy,
    /**/ EnInsect_Update,
    /**/ EnInsect_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEM_MATERIAL_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            ATELEM_NONE | ATELEM_SFX_NORMAL,
            ACELEM_NONE,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COL_MATERIAL_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static u16 sInitInsectFlags[] = { 0, INSECT_FLAG_0 | INSECT_FLAG_IS_SHORT_LIVED };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeDistance, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeScale, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeDownward, 30, ICHAIN_STOP),
};

static Vec3f accel = { 0.0f, 0.0f, 0.0f };

void EnInsect_InitFlags(EnInsect* this) {
    this->insectFlags = sInitInsectFlags[ENINSECT_GET_INIT_FLAGS(&this->actor)];
}

f32 EnInsect_XZDistanceSquared(Vec3f* arg0, Vec3f* arg1) {
    return SQ(arg0->x - arg1->x) + SQ(arg0->z - arg1->z);
}

s32 EnInsect_InBottleRange(EnInsect* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);
    Vec3f pos;

    if (this->actor.xzDistToPlayer < 32.0f) {
        pos.x = player->actor.world.pos.x + (Math_SinS(BINANG_ROT180(this->actor.yawTowardsPlayer)) * 16.0f);
        pos.y = player->actor.world.pos.y;
        pos.z = player->actor.world.pos.z + (Math_CosS(BINANG_ROT180(this->actor.yawTowardsPlayer)) * 16.0f);
        if (EnInsect_XZDistanceSquared(&pos, &this->actor.world.pos) <= SQ(20.0f)) {
            return true;
        }
    }
    return false;
}

void EnInsect_UpdateCrawlSfx(EnInsect* this) {
    if (this->crawlSoundDelay > 0) {
        this->crawlSoundDelay--;
        return;
    }

    Actor_PlaySfx(&this->actor, NA_SE_EN_MUSI_WALK);

    this->crawlSoundDelay = 3.0f / CLAMP_MIN(this->skelAnime.playSpeed, 0.1f);
    if (this->crawlSoundDelay < 2) {
        this->crawlSoundDelay = 2;
    }
}

void EnInsect_Init(Actor* thisx, PlayState* play) {
    EnInsect* this = (EnInsect*)thisx;
    f32 rand;

    this->actor.world.rot.y = Rand_Next() & 0xFFFF;
    this->actor.home.rot.y = this->actor.world.rot.y;
    this->actor.shape.rot.y = this->actor.world.rot.y;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    EnInsect_InitFlags(this);

    SkelAnime_Init(play, &this->skelAnime, &gameplay_keep_Skel_0527A0, &gameplay_keep_Anim_05140C, this->jointTable,
                   this->morphTable, BUG_LIMB_MAX);
    Animation_Change(&this->skelAnime, &gameplay_keep_Anim_05140C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, 0.0f);
    Collider_InitJntSph(play, &this->collider);
    Collider_SetJntSph(play, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);

    {
        ColliderJntSphElement* jntSphElem = &this->collider.elements[0];

        jntSphElem->dim.worldSphere.radius = jntSphElem->dim.modelSphere.radius * jntSphElem->dim.scale;
    }

    this->actor.colChkInfo.mass = 30;

    if (this->insectFlags & INSECT_FLAG_0) {
        this->actor.gravity = -0.2f;
        this->actor.terminalVelocity = -2.0f;
    }

    if (this->insectFlags & INSECT_FLAG_IS_SHORT_LIVED) {
        this->lifeTimer = Rand_S16Offset(200, 40);
        this->actor.flags |= ACTOR_FLAG_UPDATE_CULLING_DISABLED;
    }

    rand = Rand_ZeroOne();
    if (rand < 0.3f) {
        EnInsect_SetupSlowDown(this);
    } else if (rand < 0.4f) {
        EnInsect_SetupCrawl(this);
    } else {
        EnInsect_SetupRunFromPlayer(this);
    }
}

void EnInsect_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInsect* this = (EnInsect*)thisx;

    Collider_DestroyJntSph(play, &this->collider);
}

void EnInsect_SetupSlowDown(EnInsect* this) {
    this->actionTimer = Rand_S16Offset(5, 35);
    this->actionFunc = EnInsect_SlowDown;
    this->insectFlags |= INSECT_FLAG_CRAWLING;
}

void EnInsect_SlowDown(EnInsect* this, PlayState* play) {
    f32 temp_f2;

    Math_SmoothStepToF(&this->actor.speed, 0.0f, 0.1f, 0.5f, 0.0f);

    temp_f2 = (Rand_ZeroOne() * 0.8f) + (this->actor.speed * 1.2f);
    if (temp_f2 < 0.0f) {
        this->skelAnime.playSpeed = 0.0f;
    } else {
        f32 clamped = CLAMP_MAX(temp_f2, 1.9f);

        this->skelAnime.playSpeed = clamped;
    }

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    if (this->actionTimer <= 0) {
        EnInsect_SetupCrawl(this);
    }

    if ((this->insectFlags & INSECT_FLAG_IS_SHORT_LIVED) && (this->lifeTimer <= 0)) {
        EnInsect_SetupDig(this);
    } else if ((this->insectFlags & INSECT_FLAG_0) && (this->actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH)) {
        EnInsect_SetupWalkOnWater(this);
    } else if (this->actor.xzDistToPlayer < 40.0f) {
        EnInsect_SetupRunFromPlayer(this);
    }
}

void EnInsect_SetupCrawl(EnInsect* this) {
    this->actionTimer = Rand_S16Offset(10, 45);
    this->actionFunc = EnInsect_Crawl;
    this->insectFlags |= INSECT_FLAG_CRAWLING;
}

void EnInsect_Crawl(EnInsect* this, PlayState* play) {
    s32 pad;
    f32 temp_f0;
    s16 yaw;

    Math_SmoothStepToF(&this->actor.speed, 1.5f, 0.1f, 0.5f, 0.0f);

    if ((EnInsect_XZDistanceSquared(&this->actor.world.pos, &this->actor.home.pos) > SQ(40.0f)) ||
        (this->actionTimer < 4)) {
        yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos);
        Math_ScaledStepToS(&this->actor.world.rot.y, yaw, 2000);
    } else if ((this->actor.child != NULL) && (&this->actor != this->actor.child)) {
        yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.child->world.pos);
        Math_ScaledStepToS(&this->actor.world.rot.y, yaw, 2000);
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;

    temp_f0 = this->actor.speed * 1.4f;
    this->skelAnime.playSpeed = CLAMP(temp_f0, 0.7f, 1.9f);
    SkelAnime_Update(&this->skelAnime);

    if (this->actionTimer <= 0) {
        EnInsect_SetupSlowDown(this);
    }

    if ((this->insectFlags & INSECT_FLAG_IS_SHORT_LIVED) && (this->lifeTimer <= 0)) {
        EnInsect_SetupDig(this);
    } else if ((this->insectFlags & INSECT_FLAG_0) && (this->actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH)) {
        EnInsect_SetupWalkOnWater(this);
    } else if (this->actor.xzDistToPlayer < 40.0f) {
        EnInsect_SetupRunFromPlayer(this);
    }
}

void EnInsect_SetupRunFromPlayer(EnInsect* this) {
    this->actionTimer = Rand_S16Offset(10, 40);
    this->actionFunc = EnInsect_RunFromPlayer;
    this->insectFlags |= INSECT_FLAG_CRAWLING;
}

void EnInsect_RunFromPlayer(EnInsect* this, PlayState* play) {
    s32 pad;
    f32 speed;
    s16 frames;
    s16 yaw;
    s32 playerIsClose = this->actor.xzDistToPlayer < 40.0f;

    Math_SmoothStepToF(&this->actor.speed, 1.8f, 0.1f, 0.5f, 0.0f);

    if ((EnInsect_XZDistanceSquared(&this->actor.world.pos, &this->actor.home.pos) > SQ(160.0f)) ||
        (this->actionTimer < 4)) {
        Math_ScaledStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &this->actor.home.pos),
                           2000);
    } else if (playerIsClose) {
        frames = play->state.frames;
        yaw = BINANG_ROT180(this->actor.yawTowardsPlayer);
        if ((frames & 0x10) != 0) {
            if ((frames & 0x20) != 0) {
                yaw += 0x2000;
            }
        } else if ((frames & 0x20) != 0) {
            yaw -= 0x2000;
        }

        //! FAKE:
        if (play) {}

        Math_ScaledStepToS(&this->actor.world.rot.y, yaw, 2000);
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;

    speed = this->actor.speed * 1.6f;
    this->skelAnime.playSpeed = CLAMP(speed, 0.8f, 1.9f);
    SkelAnime_Update(&this->skelAnime);

    if ((this->actionTimer <= 0) || !playerIsClose) {
        EnInsect_SetupSlowDown(this);
    } else if ((this->insectFlags & INSECT_FLAG_0) && (this->actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH)) {
        EnInsect_SetupWalkOnWater(this);
    }
}

void EnInsect_SetupCaught(EnInsect* this) {
    this->actionTimer = 200;
    Actor_SetScale(&this->actor, 0.001f);
    this->actor.draw = NULL;
    this->actor.speed = 0.0f;
    this->skelAnime.playSpeed = 0.3f;
    this->actionFunc = EnInsect_Caught;
    this->insectFlags &= ~INSECT_FLAG_CRAWLING;
}

void EnInsect_Caught(EnInsect* this, PlayState* play) {
    if ((this->actionTimer == 20) && !(this->insectFlags & INSECT_FLAG_IS_SHORT_LIVED)) {
        this->actor.draw = EnInsect_Draw;
    } else if (this->actionTimer == 0) {
        if (this->insectFlags & INSECT_FLAG_IS_SHORT_LIVED) {
            Actor_Kill(&this->actor);
            return;
        }

        Actor_SetScale(&this->actor, 0.01f);
        EnInsect_SetupSlowDown(this);
    } else if (this->actionTimer < 20) {
        Actor_SetScale(&this->actor, CLAMP_MAX(this->actor.scale.x + 0.001f, 0.01f));
        SkelAnime_Update(&this->skelAnime);
    }
}

void EnInsect_SetupDig(EnInsect* this) {
    this->actionTimer = 60;
    this->skelAnime.playSpeed = 1.9f;
    Actor_PlaySfx(&this->actor, NA_SE_EN_STALTURA_BOUND);
    Math_Vec3f_Copy(&this->actor.home.pos, &this->actor.world.pos);
    this->actionFunc = EnInsect_Dig;
    this->insectFlags &= ~INSECT_FLAG_CRAWLING;
    this->insectFlags |= INSECT_FLAG_UNCATCHABLE;
}

void EnInsect_Dig(EnInsect* this, PlayState* play) {
    s32 pad[2];
    Vec3f velocity;

    Math_SmoothStepToF(&this->actor.speed, 0.0f, 0.1f, 0.5f, 0.0f);
    Math_StepToS(&this->actor.shape.rot.x, 10922, 352);
    Actor_SetScale(&this->actor, CLAMP_MIN(this->actor.scale.x - 0.0002f, 0.001f));

    this->actor.shape.yOffset -= 0.8f;
    this->actor.world.pos.x = (Rand_ZeroOne() + this->actor.home.pos.x) - 0.5f;
    this->actor.world.pos.z = (Rand_ZeroOne() + this->actor.home.pos.z) - 0.5f;

    SkelAnime_Update(&this->skelAnime);

    if ((this->actionTimer > 20) && (Rand_ZeroOne() < 0.1f)) {
        velocity.x = Math_SinS(this->actor.shape.rot.y) * -0.6f;
        velocity.y = Math_SinS(this->actor.shape.rot.x) * 0.6f;
        velocity.z = Math_CosS(this->actor.shape.rot.y) * -0.6f;
        func_800B1210(play, &this->actor.world.pos, &velocity, &accel, (Rand_ZeroOne() * 5.0f) + 8.0f,
                      (Rand_ZeroOne() * 5.0f) + 8.0f);
    }

    if (this->actionTimer <= 0) {
        Actor_Kill(&this->actor);
    }
}

void EnInsect_SetupWalkOnWater(EnInsect* this) {
    this->actionTimer = Rand_S16Offset(120, 50);
    this->unk_310 = 0;
    this->unk_30E = this->unk_310;
    this->actionFunc = EnInsect_WalkOnWater;
    this->insectFlags &= ~INSECT_FLAG_CRAWLING;
}

void EnInsect_WalkOnWater(EnInsect* this, PlayState* play) {
    s32 pad[2];
    s16 temp;
    Vec3f sp40;

    if (this->actionTimer > 80) {
        Math_StepToF(&this->actor.speed, 0.6f, 0.08f);
    } else {
        Math_StepToF(&this->actor.speed, 0.0f, 0.02f);
    }

    this->actor.velocity.y = 0.0f;
    this->actor.world.pos.y += this->actor.depthInWater;

    this->skelAnime.playSpeed = CLAMP(this->actionTimer * 0.018f, 0.1f, 1.9f);
    SkelAnime_Update(&this->skelAnime);

    if (this->actionTimer > 80) {
        this->unk_30E += Rand_S16Offset(-50, 100);
        this->unk_310 += Rand_S16Offset(-300, 600);
    }

    temp = this->skelAnime.playSpeed * 200.0f;
    this->unk_30E = CLAMP(this->unk_30E, -temp, temp);
    this->actor.world.rot.y += this->unk_30E;

    temp = this->skelAnime.playSpeed * 1000.0f;
    this->unk_310 = CLAMP(this->unk_310, -temp, temp);

    this->actor.shape.rot.y += this->unk_310;
    Math_ScaledStepToS(&this->actor.world.rot.x, 0, 3000);
    this->actor.shape.rot.x = this->actor.world.rot.x;

    if (Rand_ZeroOne() < 0.03f) {
        sp40.x = this->actor.world.pos.x;
        sp40.y = this->actor.world.pos.y + this->actor.depthInWater;
        sp40.z = this->actor.world.pos.z;
        EffectSsGRipple_Spawn(play, &sp40, 40, 200, 4);
    }

    if ((this->actionTimer <= 0) || ((this->insectFlags & INSECT_FLAG_IS_SHORT_LIVED) && (this->lifeTimer <= 0))) {
        EnInsect_SetupDrown(this);
    } else if (!(this->actor.bgCheckFlags & BGCHECKFLAG_WATER_TOUCH)) {
        EnInsect_SetupSlowDown(this);
    }
}

void EnInsect_SetupDrown(EnInsect* this) {
    this->actionTimer = 100;
    this->actor.velocity.y = 0.0f;
    this->actor.speed = 0.0f;
    this->actor.terminalVelocity = -0.8f;
    this->actor.gravity = -0.04f;
    this->insectFlags &= ~INSECT_FLAG_0;
    this->actionFunc = EnInsect_Drown;
    this->insectFlags &= ~INSECT_FLAG_CRAWLING;
    this->insectFlags |= INSECT_FLAG_UNCATCHABLE;
}

void EnInsect_Drown(EnInsect* this, PlayState* play) {
    this->actor.shape.rot.x -= 500;
    this->actor.shape.rot.y += 200;
    Actor_SetScale(&this->actor, CLAMP_MIN(this->actor.scale.x - 0.00005f, 0.001f));

    if ((this->actor.depthInWater > 5.0f) && (this->actor.depthInWater < 30.0f) && (Rand_ZeroOne() < 0.3f)) {
        EffectSsBubble_Spawn(play, &this->actor.world.pos, -5.0f, 5.0f, 5.0f, (Rand_ZeroOne() * 0.04f) + 0.02f);
    }

    if (this->actionTimer <= 0) {
        Actor_Kill(&this->actor);
    }
}

void EnInsect_Update(Actor* thisx, PlayState* play) {
    EnInsect* this = (EnInsect*)thisx;
    s32 updBgCheckInfoFlags;

    if ((this->actor.child != NULL) && (this->actor.child->update == NULL) && (&this->actor != this->actor.child)) {
        this->actor.child = NULL;
    }

    if (this->actionTimer > 0) {
        this->actionTimer--;
    }

    if (this->lifeTimer > 0) {
        this->lifeTimer--;
    }

    this->actionFunc(this, play);

    if (this->actor.update != NULL) {
        Actor_MoveWithGravity(&this->actor);
        if (this->insectFlags & INSECT_FLAG_CRAWLING) {
            if (this->insectFlags & INSECT_FLAG_0) {
                if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
                    EnInsect_UpdateCrawlSfx(this);
                }
            } else {
                EnInsect_UpdateCrawlSfx(this);
            }
        }

        updBgCheckInfoFlags = 0;
        if (this->insectFlags & INSECT_FLAG_0) {
            updBgCheckInfoFlags = UPDBGCHECKINFO_FLAG_4;
        }

        if (updBgCheckInfoFlags != 0) {
            updBgCheckInfoFlags |= UPDBGCHECKINFO_FLAG_40;
            Actor_UpdateBgCheckInfo(play, &this->actor, 8.0f, 5.0f, 0.0f, updBgCheckInfoFlags);
        }

        if (Actor_HasParent(&this->actor, play)) {
            this->actor.parent = NULL;
            EnInsect_SetupCaught(this);
        } else if ((this->actor.xzDistToPlayer < 50.0f) && (this->actionFunc != EnInsect_Caught)) {
            if (!(this->insectFlags & INSECT_FLAG_SOIL_CLOSE) && (this->lifeTimer < 180)) {
                ColliderJntSphElement* jntSphElem = &this->collider.elements[0];

                jntSphElem->dim.worldSphere.center.x = this->actor.world.pos.x;
                jntSphElem->dim.worldSphere.center.y = this->actor.world.pos.y;
                jntSphElem->dim.worldSphere.center.z = this->actor.world.pos.z;
                CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
            }

            if (!(this->insectFlags & INSECT_FLAG_UNCATCHABLE) && (sCaughtCount < 4) &&
                EnInsect_InBottleRange(this, play) && Actor_OfferGetItem(&this->actor, play, GI_MAX, 60.0f, 30.0f)) {
                sCaughtCount++;
            }
        }

        Actor_SetFocus(&this->actor, 0.0f);
    }
}

void EnInsect_Draw(Actor* thisx, PlayState* play) {
    EnInsect* this = (EnInsect*)thisx;

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, NULL);
    sCaughtCount = 0;
}
