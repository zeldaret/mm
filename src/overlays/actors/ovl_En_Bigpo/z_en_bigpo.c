#include "z_en_bigpo.h"

#define FLAGS 0x00001215

#define THIS ((EnBigpo*)thisx)

//void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Init(EnBigpo* this, GlobalContext* globalCtx);
//void EnBigpo_Destroy(EnBigpo* this, GlobalContext* globalCtx);

// update functions
//void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Update(EnBigpo* this, GlobalContext* globalCtx);
void func_80B64190(Actor* thisx, GlobalContext* globalCtx);

// draw funcs
void func_80B64470(Actor* thisx, GlobalContext* globalCtx);
void func_80B6467C(Actor* thisx, GlobalContext* globalCtx);

void func_80B61AC8(EnBigpo* this);
void func_80B61B38(EnBigpo* this);
void func_80B61D74(EnBigpo* this);
void func_80B61E9C(EnBigpo* this);
void func_80B62034(EnBigpo* this);
void func_80B62154(EnBigpo* this);
void func_80B622E4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B624F4(EnBigpo* this);
void func_80B6275C(EnBigpo* this);

void func_80B62814(EnBigpo* this);
void func_80B62900(EnBigpo* this);
void func_80B629E4(EnBigpo* this);
void func_80B62AD4(EnBigpo* this);
void func_80B62E38(EnBigpo* this, GlobalContext* globalCtx);
void func_80B631F8(EnBigpo* this);
void func_80B632BC(EnBigpo* this);
void func_80B633E8(EnBigpo* this);
void func_80B63450(EnBigpo* this);
void func_80B636D0(EnBigpo* this);
void func_80B61B38(EnBigpo* this);
void func_80B6383C(EnBigpo* this);
void func_80B638AC(EnBigpo* this);

void func_80B61AF8(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61B70(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61DA4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B61F04(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62084(EnBigpo* this, GlobalContext* globalCtx);
void func_80B621CC(EnBigpo* this, GlobalContext* globalCtx);
void func_80B623BC(EnBigpo* this, GlobalContext* globalCtx);
void func_80B6259C(EnBigpo* this, GlobalContext* globalCtx);
void func_80B627B4(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62920(EnBigpo* this, GlobalContext* globalCtx);

void func_80B62830(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62920(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62A68(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62B10(EnBigpo* this, GlobalContext* globalCtx);
void func_80B62F10(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63264(EnBigpo* this, GlobalContext* globalCtx);
void func_80B6330C(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63410(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63474(EnBigpo* this, GlobalContext* globalCtx);
void func_80B636E4(EnBigpo* this, GlobalContext* globalCtx);


void func_80B6382C(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63854(EnBigpo* this, GlobalContext* globalCtx);
void func_80B63888(EnBigpo* this, GlobalContext* globalCtx);
void func_80B638D4(EnBigpo* this, GlobalContext* globalCtx);

/*
const ActorInit En_Bigpo_InitVars = {
    ACTOR_EN_BIGPO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIGPO,
    sizeof(EnBigpo),
    (ActorFunc)EnBigpo_Init,
    (ActorFunc)EnBigpo_Destroy,
    (ActorFunc)EnBigpo_Update,;
    (ActorFunc)NULL,
};
*/

extern InitChainEntry D_80B65064;
extern DamageTable D_80B65044; 
extern ColliderCylinderInit D_80B65010;
extern CollisionCheckInfoInit D_80B6503C;

extern u32 D_06001360[];


/*
// bleh these struct memes hurt
void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    s16 temp_a1;
    s32 *g;
    s32 temp_s1;
    LightInfo *phi_s3;
    s32 *phi_s0;
    LightInfo *phi_s2;
    s32 phi_s1;

    Actor_ProcessInitChain((Actor *) this, &D_80B65064);
    //temp_t6 = this->actor.params;
    //this->unk210 = ((s32) temp_t6 >> 8) & 0xFF;
    this->unk210 = (this->actor.params >> 8) & 0xFF;
    this->actor.params &= 0xFF;
    if (this->actor.params == 2) {
        if (Flags_GetSwitch(globalCtx, (s32) this->unk210) == 0) {
            this->actor.update = func_800BDFB0;
            func_80B6383C(this);
            return;
        }
        Actor_MarkForDeath((Actor *) this);
        return;
    }
    SkelAnime_Init(globalCtx, &this->skelAnime, (void *)0x6005C18, (void *)0x6000924, this->limbDrawTbl, this->transitionDrawTbl, 0xA);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, (Actor *) this, &D_80B65010);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80B65044, &D_80B6503C);
    g = &this->fires[0].unk10;
    phi_s3 = this->fires[1].info;
    phi_s0 = g;
    phi_s2 = (LightInfo *) (g + 0x10);
    phi_s1 = 0;
  loop_5:
    phi_s0->unkC = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, phi_s3);
    Lights_PointNoGlowSetInfo(phi_s2, (s16) (s32) this->actor.home.pos.x, (s16) (s32) this->actor.home.pos.y, (s16) (s32) this->actor.home.pos.z, 0xFF, 0xFF, 0xFF, 0);
    temp_s1 = phi_s1 + 0x20;

    //phi_s3 += 0x20;
    //phi_s0 += 0x20;
    //phi_s2 += 0x20;
    //phi_s1 = temp_s1;
    if (temp_s1 != 0x60) {
        goto loop_5;
    }
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 45.0f);
    temp_a1 = this->unk210;
    this->actor.bgCheckFlags |= 0x400;
    this->unk218 = this->actor.home.pos.y + 100.0f;
    this->unk290 = 0xFF; // color?
    this->unk291 = 0xFF;
    this->unk292 = 0xD2;
    this->unk290[3] = 0;
    if ((temp_a1 != 0xFF) && (Flags_GetSwitch(globalCtx, (s32) temp_a1) != 0)) {
        Actor_MarkForDeath((Actor *) this);
    }
    if (this->actor.params == 0) {
        this->unk204 = (u8)1;
        this->actor.flags &= -0x11;
        func_80B61AC8(this);
    } else if (this->actor.params == 1) {
        func_80B63450(this);
    }
} // */
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/EnBigpo_Init.asm")

void EnBigpo_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    GlobalContext *gCtx2;
    s32 fireCount;

    if ((this->actor.params != 2) && (this->actor.params != 3) && (this->actor.params != 4) && (this->actor.params != 5)) {
        if (1) {}
        gCtx2 = globalCtx;
        for(fireCount = 0; fireCount < 3; ++fireCount){
          LightContext_RemoveLight(gCtx2, &gCtx2->lightCtx, this->fires[fireCount].light);
        }
        Collider_DestroyCylinder(gCtx2, &this->collider);
    }
} //#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/EnBigpo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61914.asm")

// takes this only
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B619B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B619FC.asm")

void func_80B61AC8(EnBigpo *this) {
    this->actor.flags &= -2;
    this->actionFunc = func_80B61AF8;
    this->unk214 = 200.0f;
}

void func_80B61AF8(EnBigpo *this, GlobalContext *globalCtx) {
    if (this->actor.xzDistToPlayer < 200.0f) {
        func_80B61B38(this);
    }
}
void func_80B61B38(EnBigpo *this) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actionFunc = func_80B61B70;
}

void func_80B61B70(EnBigpo *this, GlobalContext *globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, (Actor *) this);
        func_800B724C(globalCtx, &this->actor, 7);
        this->unk20E = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        if (this->actor.params == 0) {
            func_80B61C04(this, globalCtx);
        } else {
            func_80B63758(this, globalCtx);
        }
    }else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

// particle
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61CFC.asm")

void func_80B61D74(EnBigpo *this) {
    this->unk20A = 0x1000;
    this->actionFunc = func_80B61DA4;
    this->unk214 = 200.0f;
    this->actor.velocity.y = 0.0f;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61DA4.asm")

// appear 
void func_80B61E9C(EnBigpo *this) {
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, D_06001360);
    this->actor.draw = func_80B64470;
    Actor_SetScale((Actor *) this, 0.014f);
    Audio_PlayActorSound2(this, 0x3873); // NA_SE_EN_STALKIDS_APPEAR
    this->actionFunc = func_80B61F04;
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B61F04.asm")

void func_80B62034(EnBigpo *this) {
    this->unk206 = 0xF;
    if (this->unk204 == 0) {
        func_801A2E54(0x38);
        this->unk204 = 1;
    }
    this->actionFunc = func_80B62084;
}

void func_80B62084(EnBigpo *this, GlobalContext *globalCtx) {
    Actor *dampe;
    Camera *cam;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->unk206 -= 1;
    if (this->unk206 == 0) {
        cam = Play_GetCamera(globalCtx, this->unk20E);
        func_8016970C(globalCtx, 0, &cam->focalPoint, &cam->eye);
        this->unk20E = 0;
        if (this->actor.params == 1) {
            dampe = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_NPC, ACTOR_EN_TK);
            if (dampe != 0) {
                dampe->params = this->actor.cutscene;
            } else {
                ActorCutscene_Stop(this->actor.cutscene);
            }
        } else {
            ActorCutscene_Stop(this->actor.cutscene);
        }
        func_800B724C(globalCtx, &this->actor, 6);
        func_80B624F4(this);
    }
}

void func_80B62154(EnBigpo *this) {
    this->collider.base.acFlags &= -2;
    this->collider.base.ocFlags1 &= -2;
    this->unk20A = 0x2000;
    this->unk206 = 0x20;
    this->actor.flags &= -2;
    this->actor.speedXZ = 0.0f;
    Audio_PlayActorSound2(&this->actor, 0x3874);
    this->actionFunc = func_80B621CC;
}

void func_80B621CC(EnBigpo *this, GlobalContext *globalCtx) {
    DECR(this->unk206);
    this->actor.shape.rot.y += this->unk20A;
    if (this->unk206 < 0x10) {
        Math_ScaledStepToS(&this->unk20A, 0, 0x200);
    }
    this->unk290[3] = (s8) (u32) (this->unk206 * 7.96875f);
    if (this->unk206 == 0) {
        this->unk290[3] = 0;
        func_80B622E4(this, globalCtx);
    }
}

void func_80B622E4(EnBigpo *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;
    f32 distance;
    s16 randomYaw;

    distance = (this->actor.xzDistToPlayer < 200.0f) ? ( 200.0f ) : ( this->actor.xzDistToPlayer );
    randomYaw = (Rand_Next() >> 0x14) + this->actor.yawTowardsPlayer;
    Audio_PlayActorSound2(this, 0x3873);
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001360);
    this->unk20A = 0x2000;
    this->actor.world.pos.x = (Math_SinS(randomYaw) * distance) + player->base.world.pos.x;
    this->actor.world.pos.z = (Math_CosS(randomYaw) * distance) + player->base.world.pos.z;
    this->actionFunc = func_80B623BC;
}

void func_80B623BC(EnBigpo *this, GlobalContext *globalCtx) {
    this->unk206 += 1;
    this->actor.shape.rot.y -= this->unk20A;
    if (this->unk206 >= 0x10) {
        Math_ScaledStepToS(&this->unk20A, 0, 0x200);
    }
    this->unk290[3] = (s8) (u32) (this->unk206 * 7.96875f);
    if (this->unk206 == 0x20) {
        this->unk290[3] = 0xFF;
        if (this->unk204 == 0) {
            func_801A2E54(0x38);
            this->unk204 = 1;
        }
        func_80B624F4(this);
    }
}

extern u32 D_06000924;

// non-matching: regallloc around 
void func_80B624F4(EnBigpo *this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000924, -5.0f);
    this->unk206 = (this->actionFunc == func_80B62920) ? 0x50 : 0;
    this->unk212 = 0x28;
    this->actor.velocity.y = 0.0f;
    this->collider.base.acFlags |= 1;
    this->collider.base.ocFlags1 |= 1;
    this->actor.flags |= 1;
    this->actionFunc = func_80B6259C;
    this->unk218 = this->actor.world.pos.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;
} //#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B624F4.asm")

void func_80B6259C(EnBigpo *this, GlobalContext *globalCtx) {
    ActorPlayer *player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    DECR(this->unk206);
    this->unk212 = (this->unk212 == 0) ? 0x28 : (this->unk212 -1);
    Math_StepToF(&this->unk218, player->base.world.pos.y + 100.0f, 1.5f);
    this->actor.world.pos.y = (sin_rad((f32) this->unk212 * 0.15707964f) * 10.0f) + this->unk218;
    Math_StepToF(&this->actor.speedXZ, 3.0f, 0.2f);
    func_800B9010((Actor *) this, (u16)0x3071);
    if (Actor_XZDistanceToPoint((Actor *) this, &this->actor.home) > 300.0f) {
        this->unk208 = Actor_YawToPoint((Actor *) this, &this->actor.home);
    }
    if ((Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk208, 0x200) != 0) && (Rand_ZeroOne() < 0.075f)) {
        // casts req
        this->unk208 += (s16)((((u32)Rand_Next() >> 0x14) + 0x1000) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1));
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (this->unk206 == 0) {
        func_80B6275C(this);
    }
}

void func_80B6275C(EnBigpo *this) {
    this->collider.base.colType = 9;
    this->collider.base.acFlags |= AC_HARD;
    this->collider.info.bumper.dmgFlags &= ~0x8000;
    this->collider.base.atFlags |= 0x1;
    this->unk20A = 0x800;
    this->actionFunc = func_80B627B4;
    this->actor.speedXZ = 0.0f;
}

void func_80B627B4(EnBigpo *this, GlobalContext *globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->unk20A += 0x200;
    func_80B619B4(this);
    if ((s32) this->unk20A >= 0x3C00) {
        func_80B62814(this);
    }
}

void func_80B62814(EnBigpo *this) {
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = func_80B62830;
}

void func_80B62830(EnBigpo *this, GlobalContext *globalCtx) {
    Actor *player = PLAYER;
    s16 yawDiff;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 10.0f, 1.0f);
    Math_SmoothStepToF(&this->actor.world.pos.y, player->world.pos.y, 0.3f, 7.5f, 1.0f);
    func_80B619B4(this);
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    if (((this->collider.base.atFlags & AT_HIT)) 
      || ( ((yawDiff < 0) ? -yawDiff : yawDiff) >= 0x4001) && (this->actor.xzDistToPlayer > 50.0f)) {
        func_80B62900(this);
    }
}

void func_80B62900(EnBigpo *this) {
    this->collider.base.atFlags &= ~0x1; // todo
    this->actionFunc = func_80B62920;
}

void func_80B62920(EnBigpo *this, GlobalContext *globalCtx) {
    Actor *player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothStepToF(&this->actor.world.pos.y, player->world.pos.y + 100.0f, 0.3f, 5.0f, 1.0f);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
    if (Math_ScaledStepToS(&this->unk20A, 0, 0x200) != 0) {
        this->collider.base.colType = 3;
        this->collider.base.acFlags &= ~AC_HARD;
        this->collider.info.bumper.dmgFlags |= 0x8000;
        func_80B624F4(this);
    }
    func_80B619B4(this);
}

extern u32 D_06000454;

void func_80B629E4(EnBigpo *this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06000454, -6.0f);
    func_800BCB70(&this->actor, 0x4000, 0xFF, 0, 0x10);
    this->collider.base.acFlags &= ~AC_ON;
    func_800BE504(&this->actor, &this->collider);
    this->actionFunc = func_80B62A68;
    this->actor.speedXZ = 5.0f;
}

void func_80B62A68(EnBigpo *this, GlobalContext *globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if (this->actor.colChkInfo.health == 0) { // death?
            func_80B62AD4(this);
        } else { 
            func_80B62154(this);
        }
    }
}

void func_80B62AD4(EnBigpo *this) {
    this->unk206 = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.hintId = 0xFF; // clear?
    this->collider.base.ocFlags1 &= 0xFFFE;
    this->actionFunc = func_80B62B10;
}

extern Vec3f D_80B6506C;

void func_80B62B10(EnBigpo *this, GlobalContext *globalCtx) {
    Vec3f tempVec; 
    f32 unkTemp2; 
    s16 cam; 
    s16 unkTemp; 
    s16 modded206; 

    this->unk206 += 1;
    if ( this->unk206  < 8) {
        cam = func_800DFCDC(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x4800;
        if ((s32) this->unk206 < 5) {
            unkTemp = (this->unk206 << 0xC) - 0x4000;
            tempVec.y = (((Math_SinS(unkTemp) * 23.0f) + 40.0f) * 1.4000001f) + this->actor.world.pos.y;
            unkTemp2 = Math_CosS(unkTemp) * 32.2f;
            tempVec.x = (Math_SinS(cam) * unkTemp2) + this->actor.world.pos.x;
            tempVec.z = (Math_CosS(cam) * unkTemp2) + this->actor.world.pos.z;
        } else {
            tempVec.y = this->actor.world.pos.y + ((40.0f + (15.0f * (f32) (this->unk206 - 5))) * 1.4000001f);
            tempVec.x = (Math_SinS(cam) * 32.2f) + this->actor.world.pos.x;
            tempVec.z = (Math_CosS(cam) * 32.2f) + this->actor.world.pos.z;
        }
        modded206 = (s32) ((f32) ((this->unk206 * 0xA) + 0x50) * 1.4000001f);
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modded206, 0, 2);
        tempVec.x = (2.0f * this->actor.world.pos.x) - tempVec.x;
        tempVec.z = (2.0f * this->actor.world.pos.z) - tempVec.z;
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modded206, 0, 2);
        tempVec.x = this->actor.world.pos.x;
        tempVec.z = this->actor.world.pos.z;
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modded206, 0, 2);
    } else if (this->unk206 >= 0x1C) {
        func_80B62E38(this, globalCtx);
    } else if (this->unk206 >= 0x13) {
        this->actor.scale.x = (( (0x1C - this->unk206)) * 0.014f) * 0.1f;
        this->actor.scale.z = this->actor.scale.y = this->actor.scale.x;
        this->actor.world.pos.y += 5.0f;
    }

    if (this->unk206 < 0x12) {
        func_800B9010((Actor *) this, 0x321F); // sfx
    }
    if (this->unk206 == 0x12) {
        Audio_PlayActorSound2(this, 0x3877);
    }
}

// thinks fires.unk0 is a vec3f
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62E38.asm")

extern Gfx D_060041A0[];

void func_80B62F10(EnBigpo *this, GlobalContext *globalCtx) {
    //s16 temp_a1;

    if (((this->actor.bgCheckFlags & 1)) || (this->actor.floorHeight == -32000.0f)) {
        //temp_a1 = this->switchFlags;
        if (this->switchFlags != 0xFF) {
            Actor_SetSwitchFlag(globalCtx, this->switchFlags);
        }
        EffectSsHahen_SpawnBurst(globalCtx, &this->actor.world, 6.0f, 0, 1, 1, 0xF, 0x1F1, 0xA, &D_060041A0);

        func_80B631F8(this);
    }
}

void func_80B62FCC(EnBigpo *this, s32 arg);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B62FCC.asm")

void func_80B631F8(EnBigpo *this) {
    this->actor.draw = func_80B6467C;
    this->actor.shape.yOffset = 0.0f;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.y = 0;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->unk290[3] = 0;
    this->actor.scale.x = 0.0f;
    this->actor.scale.y = 0.0f;
    this->unk218 = this->actor.world.pos.y;
    Audio_PlayActorSound2(&this->actor, 0x28E0);
    this->actionFunc = func_80B63264;
}

void func_80B63264(EnBigpo *this, GlobalContext *globalCtx) {
    this->unk218 += 2.0f;
    func_80B62FCC(this, 0x14);
    if (this->unk290[3] == 0xFF) {
        func_80B632BC(this);
    }
}

void func_80B632BC(EnBigpo *this) {
    this->unk218 = this->actor.world.pos.y;
    Actor_SetHeight((Actor *) this, -10.0f);
    this->unk206 = 0x190;
    this->actor.flags |= 1;
    this->actionFunc = func_80B6330C;
}

void func_80B6330C(EnBigpo *this, GlobalContext *globalCtx) {
    DECR(this->unk206);
    if (Actor_HasParent((Actor *) this, globalCtx)) {
        Actor_MarkForDeath((Actor *) this);
    } else if (this->unk206 == 0) {
        Audio_PlayActorSound2(this, 0x38EC);
        func_80B633E8(this);
    } else {
        func_800B8A1C((Actor *) this, globalCtx, 0xBA, 35.0f, 60.0f);
        this->actor.world.pos.y = (sin_rad((f32) this->unk206 * 0.15707964f) * 5.0f) + this->unk218;
    }
}

void func_80B633E8(EnBigpo *this) {
    this->actor.flags &= ~0x10001;
    this->actionFunc = func_80B63410;
}

void func_80B63410(EnBigpo *this, GlobalContext *globalCtx) {
    func_80B62FCC(this, -0xD);
    if (this->unk290[3] == 0) {
        Actor_MarkForDeath((Actor *) this);
    }
}

void func_80B63450(EnBigpo *this) {
    this->actor.flags &= -2; // todo
    this->actionFunc = func_80B63474;
}

// think this is the code that searches for fires and handles them at the start
void func_80B63474(EnBigpo *this, GlobalContext *globalCtx) {
    Actor *enemyPtr;
    EnBigpo* randBigpo;
    s32 fireIndex;
    s32 randomIndex;
    s32 fireCount;

    fireCount = 0;
    for (enemyPtr = FIRSTENEMY; enemyPtr != NULL; enemyPtr = enemyPtr->next) {
      if ((enemyPtr->id == 0x208) &&(enemyPtr->params == 2)) {
          fireCount++;
      }
    }

    if (fireCount < 3) { // not enough fire poes
        this->actor.draw = func_80B64470;
        Actor_SetScale((Actor *) this, 0.014f);
        func_80B622E4(this, globalCtx);
        Math_Vec3f_Copy(&this->actor.world, &this->actor.home);
        this->actor.world.pos.y += 100.0f;
        return;
    }

    for (fireIndex = 0; fireIndex < 3 ; ++fireIndex, --fireCount) {
        enemyPtr = FIRSTENEMY;
        randomIndex = ((s32) Rand_ZeroFloat(fireCount)) % fireCount;

        // cannot be for because enemyPtr must be initilized before randomIndex
        while(enemyPtr != NULL) {
            if ((enemyPtr->id == 0x208) && (enemyPtr->params == 2)){
                if (randomIndex == 0) {
                    randBigpo = (EnBigpo*) enemyPtr;
                    randBigpo->actor.params = 3;
                    Math_Vec3f_Copy(&this->fires[fireIndex].unk10, &randBigpo->actor.world.pos);
                    randBigpo->actor.parent = this;
                    randBigpo->actor.update = func_80B64190;
                    func_800BC154(globalCtx, &globalCtx->actorCtx, &randBigpo->actor, ACTORCAT_PROP);
                    randBigpo->unk20C = fireIndex;
                    randBigpo->actor.flags &= -2;
                    Actor_SetScale(&randBigpo->actor, 0);

                    if (this->actor.child == 0) {
                        this->actor.child = &randBigpo->actor;
                    } else {
                        randBigpo->actor.child = this->actor.child;
                        this->actor.child = &randBigpo->actor;
                    }
                    break;
                } else {
                    randomIndex--;

                }
            }
          enemyPtr = enemyPtr->next;
        }
    }
    for (enemyPtr = FIRSTENEMY; enemyPtr != NULL; enemyPtr = enemyPtr->next) {
        if ((enemyPtr->id == 0x208) && (enemyPtr->params == 2)) {
            randBigpo = (EnBigpo* ) enemyPtr;
            randBigpo->actionFunc = func_80B63888;
            randBigpo->actor.update = func_80B64190;
        }
    }
    func_80B636D0(this);
}

void func_80B636D0(EnBigpo *this) {
    this->actionFunc = func_80B636E4;
}

//looping
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B636E4.asm")


#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6382C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6383C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B638AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B638D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63AC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63C28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B63D88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/EnBigpo_Update.asm")

// alternative update func
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B641E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64240.asm")

// draw func
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64470.asm")

// draw func
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B6467C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpo_0x80B615E0/func_80B64DFC.asm")
