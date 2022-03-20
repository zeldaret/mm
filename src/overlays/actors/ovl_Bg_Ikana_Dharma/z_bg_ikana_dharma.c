/*
 * File: z_bg_ikana_dharma.c
 * Overlay: ovl_Bg_Ikana_Dharma
 * Description: Stone Tower Temple - Punchable Pillar Segments
 */

#include "z_bg_ikana_dharma.h"
#include "assets/objects/object_ikana_obj/object_ikana_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaDharma*)thisx)

void BgIkanaDharma_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Draw(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_BeginNormalState(BgIkanaDharma* this);
void BgIkanaDharma_UpdateNormalState(BgIkanaDharma* this, GlobalContext* globalCtx);
void BgIkanaDharma_BeginWaitToStartCutscene(BgIkanaDharma* this);
void BgIkanaDharma_WaitToStartCutscene(BgIkanaDharma* this, GlobalContext* globalCtx);
void BgIkanaDharma_BeginCutsceneState(BgIkanaDharma* this);
void BgIkanaDharma_UpdateCutscene(BgIkanaDharma* this, GlobalContext* globalCtx);

const ActorInit Bg_Ikana_Dharma_InitVars = {
    ACTOR_BG_IKANA_DHARMA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaDharma),
    (ActorFunc)BgIkanaDharma_Init,
    (ActorFunc)BgIkanaDharma_Destroy,
    (ActorFunc)BgIkanaDharma_Update,
    (ActorFunc)BgIkanaDharma_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000100, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 98, 10, 25, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 320, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 320, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1100, ICHAIN_STOP),
};

static BgIkanaDharma* sFirstHitBgIkanaDharma;

void BgIkanaDharma_CreateParticles(BgIkanaDharma* this, GlobalContext* globalCtx) {
    u32 pad;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    f32 speed;
    f32 dirX;
    f32 initialY;
    f32 dirZ;
    f32 initialRadius;
    s16 angle;
    s32 i;

    initialRadius = this->dyna.actor.scale.x * 200.0f;
    initialY = this->dyna.actor.scale.y * 50.0f;
    for (i = 0; i != 4; i++) {
        speed = (Rand_ZeroOne() * 5.0f) + 5.0f;
        angle = ((u32)Rand_Next() >> 0x12) + this->dyna.actor.world.rot.y + 0x6000;
        dirX = Math_SinS(angle);
        dirZ = Math_CosS(angle);
        pos.x = (dirX * initialRadius) + this->dyna.actor.world.pos.x;
        pos.y = this->dyna.actor.world.pos.y + initialY;
        pos.z = (dirZ * initialRadius) + this->dyna.actor.world.pos.z;
        velocity.x = speed * dirX;
        velocity.y = Rand_ZeroOne() + 0.5f;
        velocity.z = speed * dirZ;
        accel.x = velocity.x * -0.05f;
        accel.y = -0.15f;
        accel.z = velocity.z * -0.05f;
        EffectSsKiraKira_SpawnSmallYellow(globalCtx, &pos, &velocity, &accel);
    }
}

void BgIkanaDharma_Init(Actor* thisx, GlobalContext* globalCtx) {
    s16 params;
    BgIkanaDharma* this = THIS;
    f32 segmentY;
    GlobalContext* globalCtx2 = globalCtx;
    s32 i;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.scale.x = 0.3f;
    this->dyna.actor.scale.y = 0.1f;
    this->dyna.actor.scale.z = 0.3f;
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_ikana_obj_Colheader_000C50);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx2, &this->collider, &this->dyna.actor, &sCylinderInit);
    i = 0;
    params = this->dyna.actor.params;
    if (((params >> 5) & 1) == 0) {
        segmentY = this->dyna.actor.world.pos.y;
        if (i < (params & 0xF)) {
            do {
                segmentY += 60.0f;
                Actor_SpawnAsChildAndCutscene(&globalCtx2->actorCtx, globalCtx2, ACTOR_BG_IKANA_DHARMA,
                                              this->dyna.actor.world.pos.x, segmentY, this->dyna.actor.world.pos.z,
                                              this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y,
                                              this->dyna.actor.shape.rot.z, BGIKANADHARMA_FLAG_IS_CHILD,
                                              this->dyna.actor.cutscene, this->dyna.actor.unk20, NULL);
                i++;
            } while (i != (params & 0xF));
        }
        this->dyna.actor.bgCheckFlags |= 1;
    }
    BgIkanaDharma_BeginNormalState(this);
}

void BgIkanaDharma_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (sFirstHitBgIkanaDharma == this) {
        sFirstHitBgIkanaDharma = NULL;
    }
}

void BgIkanaDharma_BeginNormalState(BgIkanaDharma* this) {
    this->actionFunc = BgIkanaDharma_UpdateNormalState;
    this->dyna.actor.speedXZ = 0.0f;
}

void BgIkanaDharma_UpdateNormalState(BgIkanaDharma* this, GlobalContext* globalCtx) {
    s32 phi_v0 = (this->collider.base.acFlags & AC_HIT) != 0;
    Actor* temp_a3 = GET_PLAYER(globalCtx);
    BgIkanaDharma* this2 = this;
    s32 temp_v0_3;

    if (phi_v0) {
        this->collider.base.acFlags &= ~AC_HIT;
    }
    if (phi_v0 && sFirstHitBgIkanaDharma == NULL) {
        s32 temp_v0_2;
        sFirstHitBgIkanaDharma = this2;
        Flags_SetSwitch(globalCtx, BGIKANADHARMA_GET_SWITCHFLAG(&this->dyna.actor));
        temp_v0_3 = (s16)(this->dyna.actor.yawTowardsPlayer + 0x8000);
        temp_v0_2 = ((s16)(temp_a3->shape.rot.y - temp_v0_3) >> 1);
        this->dyna.actor.world.rot.y = temp_v0_3 + temp_v0_2 + 0xF000;
        this->dyna.actor.speedXZ = 20.0f;
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_DARUMA_VANISH);
        BgIkanaDharma_BeginWaitToStartCutscene(this);
    } else if ((this->dyna.actor.flags & 0x40) == 0x40 && sFirstHitBgIkanaDharma == NULL &&
               this->dyna.actor.xzDistToPlayer < 420.0f) {
        temp_v0_3 = (s16)(this->dyna.actor.yawTowardsPlayer - temp_a3->shape.rot.y);
        if (temp_v0_3 < 0) {
            temp_v0_3 = -temp_v0_3; // this line is the reason temp_v0_3 isn't s16
        }
        if (temp_v0_3 >= 0x4001) {
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void BgIkanaDharma_BeginWaitToStartCutscene(BgIkanaDharma* this) {
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    this->actionFunc = BgIkanaDharma_WaitToStartCutscene;
}

void BgIkanaDharma_WaitToStartCutscene(BgIkanaDharma* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        BgIkanaDharma_BeginCutsceneState(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void BgIkanaDharma_BeginCutsceneState(BgIkanaDharma* this) {
    this->cutsceneFramesRemaining = 0xA;
    this->actionFunc = BgIkanaDharma_UpdateCutscene;
}

void BgIkanaDharma_UpdateCutscene(BgIkanaDharma* this, GlobalContext* globalCtx) {
    if (this->cutsceneFramesRemaining > 0) {
        this->cutsceneFramesRemaining--;
        if (this->cutsceneFramesRemaining == 0) {
            if (sFirstHitBgIkanaDharma == this) {
                sFirstHitBgIkanaDharma = NULL;
            }
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }
    if (Math_StepToF(&this->dyna.actor.scale.y, 0.0f, 1.0f / 300.0f) != 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        this->dyna.actor.scale.x = this->dyna.actor.scale.y * 3.0f;
        this->dyna.actor.scale.z = this->dyna.actor.scale.y * 3.0f;
        BgIkanaDharma_CreateParticles(this, globalCtx);
    }
}

void BgIkanaDharma_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = THIS;

    this->actionFunc(this, globalCtx);
    if (this->actionFunc == BgIkanaDharma_UpdateNormalState) {
        DynaPolyActor* actorBelow;
        u32 pad, pad2;
        func_800B4AEC(globalCtx, &this->dyna.actor, 30.0f);
        actorBelow = DynaPoly_GetActor(&globalCtx->colCtx, this->dyna.actor.floorBgId);
        if (actorBelow == NULL) {
            Actor_MoveWithGravity(&this->dyna.actor);
            Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4);
            if (this->dyna.actor.bgCheckFlags & 2) {
                s16 quake = Quake_Add(globalCtx->cameraPtrs[globalCtx->activeCamera], 3);
                Quake_SetSpeed(quake, 21536);
                Quake_SetQuakeValues(quake, 4, 0, 0, 0);
                Quake_SetCountdown(quake, 12);
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BLOCK_BOUND);
            }
        } else {
            if (actorBelow->actor.id == ACTOR_BG_IKANA_DHARMA) {
                this->dyna.actor.world.pos.y = actorBelow->actor.world.pos.y + 60.0f;
            } else {
                this->dyna.actor.world.pos.y = this->dyna.actor.floorHeight;
            }
            this->dyna.actor.velocity.y = 0.0f;
        }
    } else {
        f32 phi_f0 = this->dyna.actor.scale.x * 300.0f;
        if (phi_f0 < 2.0f) {
            phi_f0 = 2.0f;
        }
        Actor_MoveWithGravity(&this->dyna.actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 20.0f, phi_f0, 0.0f, 5);
    }
    Actor_SetFocus(&this->dyna.actor, 40.0f);
}

void BgIkanaDharma_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = THIS;
    Gfx_DrawDListOpa(globalCtx, object_ikana_obj_DL_0008C8);
}
