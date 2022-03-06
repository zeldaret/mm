/*
 * File: z_en_tubo_trap.c
 * Overlay: ovl_En_Tubo_Trap
 * Description: Flying Pot Trap Enemy
 */

#include "z_en_tubo_trap.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"

#define FLAGS 0x00000000

#define THIS ((EnTuboTrap*)thisx)

void EnTuboTrap_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Idle(EnTuboTrap* this, GlobalContext* globalCtx);
void EnTuboTrap_Levitate(EnTuboTrap* this, GlobalContext* globalCtx);
void EnTuboTrap_FlyAtPlayer(EnTuboTrap* this, GlobalContext* globalCtx);

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 11, 28, 0, { 0, 0, 0 } },
};

const ActorInit En_Tubo_Trap_InitVars = {
    ACTOR_EN_TUBO_TRAP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(EnTuboTrap),
    (ActorFunc)EnTuboTrap_Init,
    (ActorFunc)EnTuboTrap_Destroy,
    (ActorFunc)EnTuboTrap_Update,
    (ActorFunc)EnTuboTrap_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 197, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

void EnTuboTrap_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTuboTrap* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 1.8f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actionFunc = EnTuboTrap_Idle;
}

void EnTuboTrap_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTuboTrap* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTuboTrap_DropCollectible(EnTuboTrap* this, GlobalContext* globalCtx) {
    s32 itemParam = ((this->actor.params >> 8) & 0x3F);
    s32 dropItem00Id = func_800A8150(itemParam);

    if (dropItem00Id > ITEM00_NO_DROP) {
        Item_DropCollectible(globalCtx, &this->actor.world.pos, ((this->actor.params & 0x7F) << 8) | dropItem00Id);
    }
}

void EnTuboTrap_SpawnEffectsOnLand(EnTuboTrap* this, GlobalContext* globalCtx) {
    f32 rand;
    f32 sin;
    f32 cos;
    Vec3f pos;
    Vec3f vel;
    s32 arg5;
    s16 var;
    s32 i;
    Vec3f* actorPos = &this->actor.world.pos;

    for (i = 0, var = 0; i < 15; i++, var += 20000) {
        sin = Math_SinS(var);
        cos = Math_CosS(var);
        pos.x = sin * 8.0f;
        pos.y = (Rand_ZeroOne() * 5.0f) + 2.0f;
        pos.z = cos * 8.0f;

        vel.x = pos.x * 0.23f;
        vel.y = (Rand_ZeroOne() * 5.0f) + 2.0f;
        vel.z = pos.z * 0.23f;

        pos.x += actorPos->x;
        pos.y += actorPos->y;
        pos.z += actorPos->z;

        rand = Rand_ZeroOne();
        if (rand < 0.2f) {
            arg5 = 0x60;
        } else if (rand < 0.6f) {
            arg5 = 0x40;
        } else {
            arg5 = 0x20;
        }
        EffectSsKakera_Spawn(globalCtx, &pos, &vel, actorPos, -0xF0, arg5, 0x14, 0, 0,
                             ((Rand_ZeroOne() * 85.0f) + 15.0f), 0, 0, 0x3C, -1, GAMEPLAY_DANGEON_KEEP,
                             gameplay_dangeon_keep_DL_018090);
    }

    func_800BBFB0(globalCtx, actorPos, 30.0f, 4, 0x14, 0x32, 0);
}

void EnTuboTrap_SpawnEffectsInWater(EnTuboTrap* this, GlobalContext* globalCtx) {
    f32 rand;
    f32 sin;
    f32 cos;
    Vec3f pos;
    Vec3f vel;
    s16 var;
    s32 arg5;
    s32 i;
    Vec3f* actorPos = &this->actor.world.pos;

    pos = *actorPos;
    pos.y += this->actor.depthInWater;

    EffectSsGSplash_Spawn(globalCtx, &pos, NULL, NULL, 0, 0x190);

    for (i = 0, var = 0; i < 15; i++, var += 20000) {
        sin = Math_SinS(var);
        cos = Math_CosS(var);
        pos.x = sin * 8.0f;
        pos.y = (Rand_ZeroOne() * 5.0f) + 2.0f;
        pos.z = cos * 8.0f;

        vel.x = pos.x * 0.20f;
        vel.y = (Rand_ZeroOne() * 4.0f) + 2.0f;
        vel.z = pos.z * 0.20f;

        pos.x += actorPos->x;
        pos.y += actorPos->y;
        pos.z += actorPos->z;

        rand = Rand_ZeroOne();
        if (rand < 0.2f) {
            arg5 = 64;
        } else {
            arg5 = 32;
        }

        EffectSsKakera_Spawn(globalCtx, &pos, &vel, actorPos, -0xAA, arg5, 0x32, 5, 0,
                             ((Rand_ZeroOne() * 85.0f) + 15.0f), 0, 0, 0x46, -1, GAMEPLAY_DANGEON_KEEP,
                             gameplay_dangeon_keep_DL_018090);
    }
}

void EnTuboTrap_HandleImpact(EnTuboTrap* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Player* player2 = GET_PLAYER(globalCtx);

    if ((this->actor.bgCheckFlags & 0x20) && (this->actor.depthInWater > 15.0f)) {
        EnTuboTrap_SpawnEffectsInWater(this, globalCtx);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EV_BOMB_DROP_WATER);
        EnTuboTrap_DropCollectible(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->collider.base.atFlags & AT_BOUNCED) {
        this->collider.base.atFlags &= ~AT_BOUNCED;
        EnTuboTrap_SpawnEffectsOnLand(this, globalCtx);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_IT_SHIELD_REFLECT_SW);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EV_POT_BROKEN);
        EnTuboTrap_DropCollectible(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        EnTuboTrap_SpawnEffectsOnLand(this, globalCtx);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EV_EXPLOSION);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EV_POT_BROKEN);
        EnTuboTrap_DropCollectible(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;

        if (&player->actor == this->collider.base.at) {
            EnTuboTrap_SpawnEffectsOnLand(this, globalCtx);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EV_POT_BROKEN);
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &player2->actor.world.pos, 40, NA_SE_PL_BODY_HIT);
            EnTuboTrap_DropCollectible(this, globalCtx);
            Actor_MarkForDeath(&this->actor);
            return;
        }
    }

    if ((this->actor.bgCheckFlags & 8) || (this->actor.bgCheckFlags & 1)) {
        EnTuboTrap_SpawnEffectsOnLand(this, globalCtx);
        SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EV_POT_BROKEN);
        EnTuboTrap_DropCollectible(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnTuboTrap_Idle(EnTuboTrap* this, GlobalContext* globalCtx) {
    static s8 sTransformationHeight[] = {
        40, 40, 40, 25, 28,
    };
    Player* player = GET_PLAYER(globalCtx);
    f32 currentHeight;
    f32 transformationHeight;
    s16 startingRotation;

    if ((this->actor.xzDistToPlayer < 200.0f) && (this->actor.world.pos.y <= player->actor.world.pos.y)) {
        startingRotation = this->actor.home.rot.z;
        if ((startingRotation == 0) || (this->actor.playerHeightRel <= (startingRotation * 10.0f))) {
            func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_ENEMY);
            currentHeight = this->actor.world.pos.y;
            this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_10); // always update and can target

            transformationHeight = sTransformationHeight[player->transformation];

            this->targetHeight = player->actor.world.pos.y + transformationHeight;
            if (this->targetHeight < currentHeight) {
                this->targetHeight = currentHeight;
                this->targetHeight += transformationHeight;
            }
            this->originPos = this->actor.world.pos;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_POT_MOVE_START);
            this->actionFunc = EnTuboTrap_Levitate;
        }
    }
}

void EnTuboTrap_Levitate(EnTuboTrap* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.y += 5000;
    Math_ApproachF(&this->actor.world.pos.y, this->targetHeight, 0.8f, 3.0f);

    if (fabsf(this->actor.world.pos.y - this->targetHeight) < 10.0f) {
        this->actor.speedXZ = 10.0f;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        this->actionFunc = EnTuboTrap_FlyAtPlayer;
    }
}

void EnTuboTrap_FlyAtPlayer(EnTuboTrap* this, GlobalContext* globalCtx) {
    f32 dX = this->originPos.x - this->actor.world.pos.x;
    f32 dY = this->originPos.y - this->actor.world.pos.y;
    f32 dZ = this->originPos.z - this->actor.world.pos.z;

    //! @bug should be NA_SE_EN_TUBOOCK_FLY - SFX_FLAG
    // In OoT, NA_SE_EN_TUBOOCK_FLY is the value 0x3837
    // But in MM, certain sfxIds got reordered and devs forgot to update:
    // In MM, NA_SE_EN_MIZUBABA2_ATTACK is the old value 0x3837
    // In MM, NA_SE_EN_TUBOOCK_FLY is the new value 0x3AE0
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_MIZUBABA2_ATTACK - SFX_FLAG);

    if ((SQ(dX) + SQ(dY) + SQ(dZ) > SQ(240.0f))) {
        Math_ApproachF(&this->actor.gravity, -3.0f, 0.2f, 0.5f);
    }

    this->actor.shape.rot.y += 5000;
    EnTuboTrap_HandleImpact(this, globalCtx);
}

void EnTuboTrap_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTuboTrap* this = THIS;
    s32 padding;

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 12.0f, 10.0f, 20.0f, 0x1F);
    Actor_SetFocus(&this->actor, 0.0f);

    if (this->actor.projectedPos.z < 811.0f) {
        if (this->actor.projectedPos.z > 300.0f) {
            this->actor.shape.shadowAlpha = (u8)((811 - (s32)this->actor.projectedPos.z) >> 1);
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        } else if (this->actor.projectedPos.z > -10.0f) {
            this->actor.shape.shadowAlpha = 255;
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        } else {
            this->actor.shape.shadowDraw = NULL;
        }
    } else {
        this->actor.shape.shadowDraw = NULL;
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnTuboTrap_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, gameplay_dangeon_keep_DL_017EA0);
}
