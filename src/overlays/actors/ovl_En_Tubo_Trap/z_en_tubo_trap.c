#include "z_en_tubo_trap.h"

#define FLAGS 0x00000000

#define THIS ((EnTuboTrap*)thisx)

void EnTuboTrap_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80931004(EnTuboTrap *this, GlobalContext *globalCtx);
void func_80931138(EnTuboTrap* this, GlobalContext* globalCtx);
void func_809311C4(EnTuboTrap* this, GlobalContext* globalCtx);

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
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

//used in WaitForProximity
s8 D_8093146C[] = {
    0x28, 0x28, 0x28, 0x19, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

void EnTuboTrap_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnTuboTrap* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 1.8f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actionFunc = func_80931004; // idle
}

void EnTuboTrap_Destroy(Actor* thisx, GlobalContext *globalCtx) {
    EnTuboTrap* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// drop collectable
void func_8093089C(EnTuboTrap *this, GlobalContext *globalCtx) {
    s32 itemParam = ((this->actor.params >> 8) & 0x3F);
    s32 dropCount = func_800A8150(itemParam);

    if (dropCount >= 0) {
        Item_DropCollectible(globalCtx,
                             &this->actor.world,
                             ((this->actor.params & 0x7F) << 8) | dropCount);
    }
}

// EnTuboTrap_SpawnEffectsOnLand
void func_809308F4(EnTuboTrap *this, GlobalContext *globalCtx) {
    f32 rand;
    f32 sin;
    f32 cos;

    Vec3f pos;
    Vec3f vel;
    s32 arg5;

    s16 var;
    s32 i;

    Vec3f *actorPos = &this->actor.world.pos;

    for (i = 0, var = 0; i < 15; i++, var += 20000){
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
        }else if (rand < 0.6f){
            arg5 = 0x40;
        }else {
            arg5 = 0x20;
        }
        EffectSsKakera_Spawn(globalCtx,
                            &pos,
                            &vel,
                            actorPos,
                            -0xF0,
                            arg5,
                            0x14,
                            0,
                            0,
                            ((Rand_ZeroOne() * 85.0f) + 15.0f),
                            0,
                            0,
                            0x3C,
                            -1,
                            GAMEPLAY_DANGEON_KEEP,
                            &D_05018090);
    }

    func_800BBFB0(globalCtx, actorPos, 30.0f, 4, 0x14, 0x32, 0);
}

// EnTuboTrap_SpawnEffectsInWater
void func_80930B60(EnTuboTrap *this, GlobalContext *globalCtx) {
    f32 rand;
    f32 sin;
    f32 cos;

    Vec3f pos;
    Vec3f vel;

    s16 var;
    s32 arg5;
    s32 i;
    Vec3f *actorPos = &this->actor.world.pos;


    pos = *actorPos;
    pos.y += this->actor.yDistToWater;

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

       EffectSsKakera_Spawn(globalCtx,
                          &pos,
                          &vel,
                          actorPos,
                          -0xAA,
                          arg5,
                          0x32, 5, 0,
                          ((Rand_ZeroOne() * 85.0f) + 15.0f),
                          0, 0, 0x46,
                          -1,
                          GAMEPLAY_DANGEON_KEEP,
                          &D_05018090);

  }
}

// EnTuboTrap_HandleImpact
void func_80930DDC(EnTuboTrap *this, GlobalContext *globalCtx) {
    Actor *player = PLAYER;
    Actor *player2 = PLAYER;

    // in oot func_800F0568 is Audio_PlaySoundAtPosition

    if (((this->actor.bgCheckFlags & 0x20) != 0) && (this->actor.yDistToWater > 15.0f)) {
        func_80930B60(this, globalCtx);
        func_800F0568(globalCtx,  &this->actor.world, 0x28, 0x2817);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if ((this->collider.base.atFlags & AT_BOUNCED) != 0) {
        this->collider.base.atFlags &= ~AT_BOUNCED;
        func_809308F4(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world, 0x28, 0x1808);
        func_800F0568(globalCtx, &this->actor.world, 0x28, 0x2887);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if ((this->collider.base.acFlags & AC_HIT) != 0) {
        this->collider.base.acFlags &= ~AC_HIT;
        func_809308F4(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.world, 0x28, 0x2802);
        func_800F0568(globalCtx, &this->actor.world, 0x28, 0x2887);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if ((this->collider.base.atFlags & AT_HIT) != 0) {
        this->collider.base.atFlags &= ~AT_HIT;
        if (player == this->collider.base.at) {
            func_809308F4(this, globalCtx);
            func_800F0568(globalCtx,  &this->actor.world, 0x28, 0x2887);
            func_800F0568(globalCtx,  &player2->world, 0x28, 0x83E);
            func_8093089C(this, globalCtx);
            Actor_MarkForDeath(&this->actor);
            return;
        }
    }
    if (((this->actor.bgCheckFlags & 8) != 0) || ((this->actor.bgCheckFlags & 1) != 0)) {
        func_809308F4(this, globalCtx);
        func_800F0568(globalCtx,  &this->actor.world, 0x28, 0x2887);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath(&this->actor);
    }
}

#if NON-MATCHING
// Wait For Proximity (idle)
  // NON-MATCHING: wrong register used, v instead of t for the weirdValues[] pointer
void func_80931004(EnTuboTrap *this, GlobalContext *globalCtx) {
    Actor *player = PLAYER;
    f32 currentHeight;
    s8 weirdvalue;
    s16 startingRotation;
    static s8 D_8093146C[] = {
        0x28, 0x28, 0x28, 0x19, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };

    if ((this->actor.xzDistToPlayer < 200.0f) && (this->actor.world.pos.y <= player->world.pos.y)) {
        startingRotation = this->actor.home.rot.z;
        if ((startingRotation == 0) || (this->actor.yDistToPlayer <= ((f32) startingRotation * 10.0f))) {
            func_800BC154(globalCtx, &globalCtx->actorCtx, this, ACTORCAT_ENEMY);
            currentHeight = this->actor.world.pos.y;
            this->actor.flags |= 0x11; // always update and can target

            // hard to know what this value is even used for without knowing what ActorPlayer::unk14B is
            // wild guess: this is player animation state, height is modified to always point at center of link model
            weirdvalue = D_8093146C[ ((ActorPlayer*) player)->unk14B & 0xFF];

            this->targetHeight = player->world.pos.y + (f32) weirdvalue;
            if (this->targetHeight < currentHeight) {
                this->targetHeight = currentHeight;
                this->targetHeight += weirdvalue;
            }
            this->originPos = this->actor.world.pos;
            Audio_PlayActorSound2(&this->actor, 0x28C4);
            this->actionFunc = func_80931138;
        }
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_80931004.asm")
#endif

// levitate
void func_80931138(EnTuboTrap *this, GlobalContext *globalCtx) {
    this->actor.shape.rot.y += 5000;
    Math_ApproachF(&this->actor.world.pos.y, this->targetHeight, 0.8f, 3.0f);

    if (fabsf(this->actor.world.pos.y - this->targetHeight) < 10.0f) {
        this->actor.speedXZ = 10.0f;
        this->actor.world.rot.y = this->actor.yawTowardsPlayer;
        this->actionFunc = func_809311C4; // flying at link
    }
}

// flying at link
void func_809311C4(EnTuboTrap *this, GlobalContext *globalCtx) {
    f32 dX = this->originPos.x - this->actor.world.pos.x;
    f32 dY = this->originPos.y - this->actor.world.pos.y;
    f32 dZ = this->originPos.z - this->actor.world.pos.z;

    Audio_PlayActorSound2(&this->actor, 0x3037);

    if ((SQ(dX) + SQ(dY) + SQ(dZ) > 57600.0f)) { //240.0f ^ 2
        Math_ApproachF(&this->actor.gravity, -3.0f, 0.2f, 0.5f);
    }

    this->actor.shape.rot.y += 5000;
    func_80930DDC(this, globalCtx); // "handle impact"
}

void EnTuboTrap_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnTuboTrap* this = THIS;
    s32 padding;

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_800B78B8(globalCtx, &this->actor, 12.0f, 10.0f, 20.0f, 0x1F);
    Actor_SetHeight(&this->actor, 0.0f);

    if (this->actor.projectedPos.z < 811.0f) {
        if (this->actor.projectedPos.z > 300.0f) {
            this->actor.shape.shadowAlpha = (u8) ( (0x32B - (s32) this->actor.projectedPos.z) >> 1);
            this->actor.shape.shadowDraw = func_800B3FC0;
        } else if (this->actor.projectedPos.z > -10.0f) {
            this->actor.shape.shadowAlpha = 0xFF;
            this->actor.shape.shadowDraw = func_800B3FC0;
        } else{
            this->actor.shape.shadowDraw = NULL;
        }
    } else {
        this->actor.shape.shadowDraw = NULL;
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
}

void EnTuboTrap_Draw(Actor *thisx, GlobalContext *globalCtx) {
    //  Gfx_DrawDListOpa with a display list
    func_800BDFC0(globalCtx, &D_05017EA0);
}
