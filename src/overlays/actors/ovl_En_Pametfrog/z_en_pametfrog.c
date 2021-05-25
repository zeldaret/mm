#include "z_en_pametfrog.h"

#define FLAGS 0x00000035

#define THIS ((EnPametfrog*)thisx)

void EnPametfrog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPametfrog_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8086A0F4(EnPametfrog* this, GlobalContext* globalCtx);

void func_8086AB68(EnPametfrog* this, GlobalContext* globalCtx);
void func_8086BA6C(EnPametfrog* this, GlobalContext* globalCtx);
void func_8086BDA8(EnPametfrog* this, GlobalContext* globalCtx);
void func_8086C618(EnPametfrog* this, GlobalContext* globalCtx);
void func_8086C6D0(EnPametfrog* this);
void func_8086C72C(EnPametfrog* this, GlobalContext* globalCtx);
void func_8086C7C8(EnPametfrog* this);
void func_8086C81C(EnPametfrog* this, GlobalContext* globalCtx);
void func_8086C94C(EnPametfrog* this);
void func_8086C99C(EnPametfrog* this, GlobalContext* globalCtx);

void func_8086C5A8(EnPametfrog* this);

extern AnimationHeader D_0600347C;
extern AnimationHeader D_060039C4;
extern AnimationHeader D_06003F28;
extern AnimationHeader D_060066B4;
extern AnimationHeader D_060070C4;
extern FlexSkeletonHeader D_0600DF98;
extern AnimationHeader D_0600F990;
extern AnimationHeader D_0600F048;
extern f32 D_8086DA98;

const ActorInit En_Pametfrog_InitVars = {
    ACTOR_EN_PAMETFROG,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnPametfrog),
    (ActorFunc)EnPametfrog_Init,
    (ActorFunc)EnPametfrog_Destroy,
    (ActorFunc)EnPametfrog_Update,
    (ActorFunc)EnPametfrog_Draw,
};

// static DamageTable sDamageTable;
DamageTable D_8086D960 = {
    0x10, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x10, 0x01, 0x01, 0x01, 0x22, 0x32, 0x42, 0x01, 0x10,
    0x01, 0x02, 0x10, 0x50, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2]
ColliderJntSphElementInit D_8086D980[2] = {
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 32 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_WOOD,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 25 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit
ColliderJntSphInit D_8086D9C8 = {
    {
        COLTYPE_HIT6,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    2,
    D_8086D980,
};

// static CollisionCheckInfoInit sColChkInit
CollisionCheckInfoInit D_8086D9D8 = { 3, 30, 60, 50 };

// static InitChainEntry sInitChain[]
InitChainEntry D_8086D9E0[] = {
    ICHAIN_S8(hintId, 69, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(targetArrowOffset, -13221, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 10, ICHAIN_STOP),
};

s32 D_8086D9F4[] = {
    (0x20 << 8) | 0x40,
    (0x20 << 8) | 0x80,
    (0x21 << 8) | 0x01,
    (0x21 << 8) | 0x02,
};

s32 D_8086DA04[] = {
    0x00000000,
    0xBF000000,
    0x00000000,
};

s32 D_8086DA10[] = {
    0xFAFAFAFF,

};
s32 D_8086DA14[] = {
    0xB4B4B4FF,
};

// static ActorAnimationEntry animations[]
AnimationHeader* D_8086DA18[] = {
    &D_0600347C,
    &D_060070C4,
    &D_06003F28,
    &D_0600F048,
};

s32 D_8086DA28[] = {
    0xFFFF00FF, 0x01FF02FF, 0x03FF04FF, 0x0506FF07, 0x0809FF0A, 0xFF0BFFFF,
};

void EnPametfrog_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPametfrog* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_8086D9E0);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 55.0f);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_8086D960, &D_8086D9D8);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0600DF98, &D_0600F990, this->limbDrawTable,
                     this->transitionDrawTable, 24);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &D_8086D9C8, this->colElement);
    this->params = CLAMP(this->actor.params, 1, 4);

    if (Actor_GetRoomCleared(globalCtx, globalCtx->roomContext.currRoom.num)) {
        Actor_MarkForDeath(&this->actor);
        if ((gSaveContext.perm.weekEventReg[D_8086D9F4[this->actor.params - 1] >> 8] &
             (u8)D_8086D9F4[this->actor.params - 1]) == 0) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_MINIFROG, this->actor.world.pos.x,
                        this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0, this->params);
            return;
        }
    } else {
        for (i = 0; i < 2; i++) {
            this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius;
        }

        if (Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_BIGPAMET,
                                  this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0,
                                  0) == 0) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

        this->actor.params = 0;
        func_8086C6D0(this);
    }
}

void EnPametfrog_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPametfrog* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_80869FBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A068.asm")

void func_8086A0F4(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f pos;

    if (this->actor.yDistToWater > 0.0f) {
        pos.x = this->actor.world.pos.x;
        pos.z = this->actor.world.pos.z;
        pos.y = this->actor.world.pos.y + this->actor.yDistToWater;
        EffectSsGRipple_Spawn(globalCtx, &pos, 150, 550, 0);
        pos.y += 8.0f;
        EffectSsGSplash_Spawn(globalCtx, &pos, NULL, NULL, 0, 550);
    }
}

void func_8086A1A0(EnPametfrog* this, GlobalContext* globalCtx) {
    Vec3f pos;

    if ((this->actor.yDistToWater > 0.0f) && ((globalCtx->gameplayFrames % 14) == 0)) {
        pos.x = this->actor.world.pos.x;
        pos.z = this->actor.world.pos.z;
        pos.y = this->actor.world.pos.y + this->actor.yDistToWater;
        EffectSsGRipple_Spawn(globalCtx, &pos, 150, 550, 0);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A2CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A4E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A554.asm")

void func_8086A6B0(EnPametfrog* this, GlobalContext* globalCtx) {
    if (func_801378B8(&this->skelAnime, 1.0f)) {
        Audio_PlayActorSound2(this, 0x395B);
    } else if (func_801378B8(&this->skelAnime, 11.0f)) {
        func_8086A0F4(this, globalCtx);
        Audio_PlayActorSound2(this, 0x2902);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A80C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A8C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086A964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AA60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AAA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AB04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AB68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AEC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086AFC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B66C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B8CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086B9D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BA6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BB9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BBE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BEEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086BF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086C4B8.asm")

void func_8086C5A8(EnPametfrog* this) {
    if (this->actor.colChkInfo.health == 0) {
        this->cutscene = this->actor.cutscene;
    } else {
        this->cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
    }
    ActorCutscene_SetIntentToPlay(this->cutscene);
    this->actionFunc = func_8086C618;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
}

void func_8086C618(EnPametfrog* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        this->camera = ActorCutscene_GetCurrentCamera(this->cutscene);
        func_800B724C(globalCtx, this, 7);
        if (this->actor.colChkInfo.health == 0) {
            if (this->actor.params == 0) {
                func_8086CD6C(this, globalCtx);
            } else {
                func_8086BBE0(this, globalCtx);
            }
        } else {
            func_8086AC0C(this, globalCtx);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void func_8086C6D0(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060066B4);
    this->collider.base.atFlags &= ~1;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8086C72C;
}

void func_8086C72C(EnPametfrog* this, GlobalContext* globalCtx) {
    func_8086A1A0(this, globalCtx);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 5, 0x400, 0x80);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) && (func_801690CC(globalCtx) == 0)) {
        if (this->unk_2AE == 0) {
            func_801A2E54(0x38);
            this->unk_2AE = 1;
        }
        func_8086C7C8(this);
    }
}

void func_8086C7C8(EnPametfrog* this) {
    SkelAnime* temp_a0;

    temp_a0 = &this->skelAnime;
    this = this;
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_060039C4);
    this->collider.base.acFlags |= 1;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8086C81C;
}

void func_8086C81C(EnPametfrog* this, GlobalContext* globalCtx) {
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000, 0x80);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_8086A6B0(this, globalCtx);
    if ((this->actor.bgCheckFlags & 1) == 0 ||
        (this->skelAnime.animCurrentFrame > 1.0f && this->skelAnime.animCurrentFrame < 12.0f)) {
        this->actor.speedXZ = 8.0f;
    } else {
        this->actor.speedXZ = 0.0f;
    }

    if ((this->collider.base.ocFlags1 & 2) && (this->collider.base.ocFlags2 & 1) &&
        Actor_IsActorFacingLink(&this->actor, 0x3000) &&
        (this->skelAnime.animCurrentFrame <= 2.0f || this->skelAnime.animCurrentFrame >= 11.0f)) {
        func_8086C94C(this);
    }
}

void func_8086C94C(EnPametfrog* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600F990);
    this->unk_2B6 = 7;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_8086C99C;
}

void func_8086C99C(EnPametfrog* this, GlobalContext* globalCtx) {
    func_8086A1A0(this, globalCtx);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        this->unk_2B6--;
        if (this->unk_2B6 == 0) {
            func_8086C6D0(this);
        } else if (this->unk_2B6 == 6) {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600F990);
        } else {
            SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, D_8086DA18[(s32)Rand_ZeroFloat(4.0f) % 4]);
        }
    }

    if ((this->skelAnime.animCurrentSeg == &D_0600347C && func_801378B8(&this->skelAnime, 2.0f)) ||
        (this->skelAnime.animCurrentSeg == &D_060070C4 && func_801378B8(&this->skelAnime, 9.0f)) ||
        (this->skelAnime.animCurrentSeg == &D_06003F28 && func_801378B8(&this->skelAnime, 2.0f)) ||
        ((this->skelAnime.animCurrentSeg == &D_0600F048) && func_801378B8(&this->skelAnime, 27.0f))) {

        this->collider.base.atFlags |= 1;
        if (this->skelAnime.animCurrentSeg == &D_06003F28) {
            Audio_PlayActorSound2(this, 0x3966);
        } else {
            Audio_PlayActorSound2(this, 0x3961);
        }
    } else {
        this->collider.base.atFlags &= ~1;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CC04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CD04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CD6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CEB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086CEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D1E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D230.asm")

// D_8086DA98 = -0.1;
void EnPametfrog_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnPametfrog* this = THIS;
    f32 temp_f0;
    f32 phi_f0;

    if (this->actor.params == 5) {
        func_8086C5A8(this);
    } else if (this->actionFunc != func_8086C618) {
        func_8086D230(this, globalCtx);
    } else {
        this->collider.base.acFlags &= ~2;
    }
    this->actionFunc(this, globalCtx);
    if ((this->actionFunc != func_8086BA6C) && (this->actionFunc != func_8086AB68)) {
        if (this->actor.gravity < D_8086DA98) {
            Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
            phi_f0 = this->actionFunc == func_8086BDA8 ? 3.0f : 15.0f;
            func_800B78B8(globalCtx, &this->actor, 25.0f, phi_f0, 3.0f, 0x1F);
        } else if (this->unk_2BC == 0) {
            Actor_SetVelocityAndMoveXYRotation(&this->actor);
            this->actor.floorHeight = this->actor.world.pos.y;
        }
    }
    if (this->collider.base.atFlags & 1) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }
    if (this->collider.base.acFlags & 1) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }
    if (this->collider.base.ocFlags1 & 1) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    }
    if (this->unk_2C4 > 0.0f) {
        if ((this->unk_2AC != 0xA) && (this->actionFunc != func_8086C618)) {
            Math_StepToF(&this->unk_2C4, 0.0f, 0.05f);
            temp_f0 = ((this->unk_2C4 + 1.0f) * 0.375f);
            this->unk_2C8 = temp_f0;
            this->unk_2C8 = (temp_f0 > 0.75f) ? 0.75f : this->unk_2C8;

        } else if (Math_StepToF(&this->unk_2CC, 0.75f, 0.01875f) == 0) {
            func_800B9010(&this->actor, 0x20B2);
        }
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/func_8086D730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pametfrog_0x80869D90/EnPametfrog_Draw.asm")
