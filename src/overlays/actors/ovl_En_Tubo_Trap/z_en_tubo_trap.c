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

s32 D_80931410[] = { // Colliderinit
    0x0A110900,
    0x20010000,
    0x00000000,
    0xF7CFFFFF,
    0x00040000,
    0xF7CFFFFF,
    0x00000000,
    0x01010000,
    0x000B001C,
    0x00000000,
    0x00000000,
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
    (ActorFunc)EnTuboTrap_Draw
};

s32 D_8093145C[] = { // actorprocessinitchain
    0xC85800C5,
    0xB0FC0FA0,
    0xB1000064,
    0x31040064,
};

// used in WaitForProximity
s8 D_8093146C[] = {
    0x28, 0x28, 0x28, 0x19,
    0x1C, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

void EnTuboTrap_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnTuboTrap* this = THIS;

    Actor_ProcessInitChain(thisx, &D_8093145C);
    thisx->shape.rot.z = 0;
    thisx->currPosRot.rot.z = 0;
    Actor_SetDrawParams(&thisx->shape,
          0.0f,
          (void (*)(struct Actor *actor,
                    struct LightMapper *mapper,
                    struct GlobalContext *ctxt)) func_800B3FC0,
          1.8f);
    Collision_InitCylinderDefault(globalCtx, &this->collider);
    Collision_InitCylinderWithData(globalCtx, &this->collider, thisx, &D_80931410);
    this->actionFunc = func_80931004;
}

void EnTuboTrap_Destroy(Actor* thisx, GlobalContext *globalCtx) {
    EnTuboTrap* this = THIS;

    Collision_FiniCylinder(globalCtx, &this->collider);
}

// drop collectable
void func_8093089C(EnTuboTrap *thisx, GlobalContext *globalCtx) {
    s32 itemParam = ((thisx->actor.params >> 8) & 0x3F);
    s32 dropCount = func_800A8150(itemParam);

    if (dropCount >= 0) {
        func_800A7730(globalCtx, 
                      &thisx->actor.currPosRot, 
                      ((thisx->actor.params & 0x7F) << 8) | dropCount);
    }
}

// EnTuboTrap_SpawnEffectsOnLand
//void func_809308F4(EnTuboTrap *this, GlobalContext *globalCtx);
//GLOBAL_ASM("asm/non_matchings/ovl_En_Tubo_Trap_0x809307E0/func_809308F4.asm")
// should be match, but full compile says it doesn't, might need all of them to match first
void func_809308F4(EnTuboTrap *this, GlobalContext *globalCtx) {
    f32 rand;
    f32 sin;
    f32 cos;

    Vec3f pos;
    Vec3f vel;
    s32 arg5;

    s16 var;
    s32 i;

    Vec3f *actorPos = &this->actor.currPosRot.pos;

    for (i = 0, var = 0; i < 15; i++, var += 20000){
        sin = Math_Sins(var);
        cos = Math_Coss(var);
        pos.x = sin * 8.0f;
        pos.y = (randZeroOne() * 5.0f) + 2.0f;
        pos.z = cos * 8.0f;

        vel.x = pos.x * 0.23f;
        vel.y = (randZeroOne() * 5.0f) + 2.0f;
        vel.z = pos.z * 0.23f;

        pos.x += actorPos->x;
        pos.y += actorPos->y;
        pos.z += actorPos->z;

        rand = randZeroOne();
        if (rand < 0.2f) {
            arg5 = 0x60;
        }else if (rand < 0.6f){
            arg5 = 0x40;
        }else {
            arg5 = 0x20;
        }
        EffectSS_SpawnShard(globalCtx,
                            &pos,
                            &vel,
                            actorPos,
                            -0xF0,
                            arg5,
                            0x14,
                            0,
                            0, 
                            ((randZeroOne() * 85.0f) + 15.0f), 
                            0,
                            0, 
                            0x3C,
                            -1,
                            3, // dangeon_keep is that really what it is?
                            &D_05018090);
    }

    func_800BBFB0(globalCtx, actorPos, 30.0f, 4, 0x14, 0x32, 0);
}


//GLOBAL_ASM("asm/non_matchings/ovl_En_Tubo_Trap_0x809307E0/func_80930B60.asm")
// this is the water version of the function above
void func_80930B60(EnTuboTrap *this, GlobalContext *globalCtx) {
    f32 rand;
    f32 sin;
    f32 cos;

    Vec3f pos;
    Vec3f vel;

    s16 var;
    s32 arg5;
    s32 i;
    Vec3f *actorPos = &this->actor.currPosRot.pos;


    pos = *actorPos;
    pos.y += this->actor.unk8C; // distance to water?
    
    EffectSS_SpawnGSplash(globalCtx, &pos, NULL, NULL, 0, 0x190);

    for (i = 0, var = 0; i < 15; i++, var += 20000) {
        sin = Math_Sins(var);
        cos = Math_Coss(var);

        pos.x = sin * 8.0f;
        pos.y = (randZeroOne() * 5.0f) + 2.0f;
        pos.z = cos * 8.0f;

        vel.x = pos.x * 0.20f;
        vel.y = (randZeroOne() * 4.0f) + 2.0f;
        vel.z = pos.z * 0.20f;

        pos.x += actorPos->x;
        pos.y += actorPos->y;
        pos.z += actorPos->z;

        rand = randZeroOne();
        if (rand < 0.2f) {
            arg5 = 64;
        } else {
            arg5 = 32;
        }

       EffectSS_SpawnShard(globalCtx,
                          &pos, 
                          &vel, 
                          actorPos,
                          -0xAA, 
                          arg5,
                          0x32, 5, 0, 
                          ((randZeroOne() * 85.0f) + 15.0f),
                          0, 0, 0x46, 
                          -1, 3,
                          &D_05018090);

  }
}

// "handle impact"
void func_80930DDC(EnTuboTrap *this, GlobalContext *globalCtx) {
    Actor *player = globalCtx->actorCtx.actorList[2].first;
    Actor *player2 = globalCtx->actorCtx.actorList[2].first;
    // double player, the same as OOT
    
    // unk90 is bgCheckFlags, unk8c is yDistanceToWater
    if (((this->actor.unk90 & 0x20) != 0) && (this->actor.unk8C > 15.0f)) {
        func_80930B60(this, globalCtx);
        func_800F0568(globalCtx,  &this->actor.currPosRot, 0x28, (u16)0x2817);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath((Actor *) this);
        return;
    }
    // 4 = !AT_BOUNCED
    if ((this->collider.base.flagsAT & 4) != 0) {
        this->collider.base.flagsAT = this->collider.base.flagsAT & 0xFFFB;
        func_809308F4(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.currPosRot, 0x28, (u16)0x1808);
        func_800F0568(globalCtx, &this->actor.currPosRot, 0x28, (u16)0x2887);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath((Actor *) this);
        return;
    }
    // AC_HIT
    if ((this->collider.base.flagsAC & 2) != 0) {
        this->collider.base.flagsAC = this->collider.base.flagsAC & 0xFFFD;
        func_809308F4(this, globalCtx);
        func_800F0568(globalCtx, &this->actor.currPosRot , 0x28, (u16)0x2802);
        func_800F0568(globalCtx, &this->actor.currPosRot , 0x28, (u16)0x2887);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath((Actor *) this);
        return;
    }
    // AT_HIT
    if ((this->collider.base.flagsAT & 2) != 0) {
        this->collider.base.flagsAT = this->collider.base.flagsAT & 0xFFFD;
        if (player == this->collider.base.collisionAT) {
            func_809308F4(this, globalCtx);
            func_800F0568(globalCtx,  &this->actor.currPosRot, 0x28, (u16)0x2887);
            func_800F0568(globalCtx,  &player2->currPosRot, 0x28, (u16)0x83E);
            func_8093089C(this, globalCtx);
            Actor_MarkForDeath((Actor *) this);
            return;
        }
    }
    // unk90 is bgcheckflags
    if (((this->actor.unk90 & 8) != 0) || ((this->actor.unk90 & 1) != 0)) {
        func_809308F4(this, globalCtx);
        func_800F0568(globalCtx,  &this->actor.currPosRot, 0x28, (u16)0x2887);
        func_8093089C(this, globalCtx);
        Actor_MarkForDeath((Actor *) this);
    }
} 


#if NON-MATCHING
// wait for proximity
  // NON-MATCHING: wrong register used, v instead of t for the weirdValues[] pointer
void func_80931004(EnTuboTrap *this, GlobalContext *globalCtx) {
    Actor *player = globalCtx->actorCtx.actorList[2].first;
    f32 currentHeight;
    s8 weirdvalue;
    s16 startingRotation;
    //static s8* weirdValues = &D_8093146C;
    s8* weirdValues;// = &D_8093146C;

    if ((this->actor.xzDistanceFromLink < 200.0f) && 
        (this->actor.currPosRot.pos.y <= player->currPosRot.pos.y)) {
        startingRotation = this->actor.initPosRot.rot.z;
        if ((startingRotation == 0) || (this->actor.yDistanceFromLink <= ((f32) startingRotation * 10.0f))) {
            // actor change category
            func_800BC154(globalCtx, &globalCtx->actorCtx, this, 5);
            currentHeight = this->actor.currPosRot.pos.y;
            this->actor.flags = this->actor.flags | 0x11;

            // temp_f2 = (f32) *(&D_8093146C + temp_v1->unk14B);
            weirdValues = &D_8093146C;
            weirdvalue = weirdValues[ ((ActorPlayer*) player)->unk14B & 0xFF];

            //weirdvalue = D_8093146C[ ((ActorPlayer*) player)->unk14B & 0xFF];

            this->targetY = player->currPosRot.pos.y + (f32) weirdvalue;
            if (this->targetY < currentHeight) {
                this->targetY = currentHeight;
                this->targetY += weirdvalue;
            }
            this->originPos = this->actor.currPosRot.pos;
            func_800B8EC8(&this->actor, 0x28C4U);
            this->actionFunc = func_80931138;
        }
    }
} // */
#else
  GLOBAL_ASM("asm/non_matchings/ovl_En_Tubo_Trap_0x809307E0/func_80931004.asm")
#endif

// levitate
void func_80931138(EnTuboTrap *this, GlobalContext *globalCtx) {
    this->actor.shape.rot.y += 0x1388;
    Math_SmoothScaleMaxF(&this->actor.currPosRot.pos.y, this->targetY, 0.8f, 3.0f);

    // once height is reached, switch to flying at link
    if (fabsf(this->actor.currPosRot.pos.y - this->targetY) < 10.0f) {
        this->actor.speedXZ = 10.0f;
        this->actor.currPosRot.rot.y = this->actor.rotTowardsLinkY;
        this->actionFunc = &func_809311C4;
    }
}

// flying at link
void func_809311C4(EnTuboTrap *this, GlobalContext *globalCtx) {
    f32 dX = this->originPos.x - this->actor.currPosRot.pos.x;
    f32 dY = this->originPos.y - this->actor.currPosRot.pos.y;
    f32 dZ = this->originPos.z - this->actor.currPosRot.pos.z;

    func_800B8EC8((Actor *) this, 0x3037U); // play flying sfx
    
    if (((dX * dX) + (dY * dY) + (dZ * dZ)) > 57600.0f) {
        Math_SmoothScaleMaxF(&this->actor.gravity, -3.0f, 0.2f, 0.5f);
    }

    this->actor.shape.rot.y += 0x1388;
    func_80930DDC(this, globalCtx); // "handle impact"
}

void EnTuboTrap_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnTuboTrap* this = THIS;
    s32 padding;
    //static f32 D_80931494 = 0x444AC000; // rodata

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(thisx);
    func_800B78B8(globalCtx, thisx, 12.0f, 10.0f, 20.0f, 0x1F);
    Actor_SetHeight(thisx, 0.0f);
    if (thisx->projectedPos.z < 811.0f) {
        if (thisx->projectedPos.z > 300.0f) {
            // evil floating point bit level hacking
            thisx->shape.alphaScale = (u8) ( (0x32B - (s32) thisx->projectedPos.z) >> 1);
            thisx->shape.shadowDrawFunc = func_800B3FC0;
        } else if (thisx->projectedPos.z > -10.0f) {
            thisx->shape.alphaScale = 0xFF;
            thisx->shape.shadowDrawFunc = func_800B3FC0;
        } else{
            thisx->shape.shadowDrawFunc = NULL;
        }
    } else {
        thisx->shape.shadowDrawFunc = NULL;
    }

    Collision_CylinderMoveToActor(thisx, &this->collider);
    Collision_AddAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    Collision_AddAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
}

void EnTuboTrap_Draw(Actor *thisx, GlobalContext *globalCtx) {
    //  Gfx_DrawDListOpa with a display list
    func_800BDFC0(globalCtx, &D_05017EA0);
}

/* // rodata
s32 enTuboTrapOverlayInfo[] = {
  0x00000C30,
  0x00000070,
  0x00000020,
  0x00000000,
  0x00000027,
};

s32 enTuboTrapOverlayRelocations[] = {
  0x45000014,
  0x46000018,
  0x45000058,
  0x46000060,
  0x45000070,
  0x46000074,
  0x4500015C,
  0x46000160,
  0x45000238,
}; */
