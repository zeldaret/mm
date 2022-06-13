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

void BgIkanaDharma_SetupWaitForHit(BgIkanaDharma* this);
void BgIkanaDharma_WaitForHit(BgIkanaDharma* this, GlobalContext* globalCtx);
void BgIkanaDharma_SetupStartCutscene(BgIkanaDharma* this);
void BgIkanaDharma_StartCutscene(BgIkanaDharma* this, GlobalContext* globalCtx);
void BgIkanaDharma_SetupWaitForCutsceneToEnd(BgIkanaDharma* this);
void BgIkanaDharma_WaitForCutsceneToEnd(BgIkanaDharma* this, GlobalContext* globalCtx);

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

void BgIkanaDharma_SpawnEffects(BgIkanaDharma* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    s32 i;
    f32 initialRadius = this->dyna.actor.scale.x * 200.0f;
    f32 initialY = this->dyna.actor.scale.y * 50.0f;

    for (i = 0; i < 4; i++) {
        f32 speed = (Rand_ZeroOne() * 5.0f) + 5.0f;
        s16 angle = ((u32)Rand_Next() >> 0x12) + this->dyna.actor.world.rot.y + 0x6000;
        f32 dirX = Math_SinS(angle);
        f32 dirZ = Math_CosS(angle);

        pos.x = (dirX * initialRadius) + this->dyna.actor.world.pos.x;
        pos.y = this->dyna.actor.world.pos.y + initialY;
        pos.z = (dirZ * initialRadius) + this->dyna.actor.world.pos.z;
        velocity.x = speed * dirX;
        velocity.y = Rand_ZeroOne() + 0.5f;
        velocity.z = speed * dirZ;
        accel.x = velocity.x * -0.05f;
        accel.y = -0.15f;
        accel.z = velocity.z * -0.05f;
        EffectSsKirakira_SpawnSmallYellow(globalCtx, &pos, &velocity, &accel);
    }
}

void BgIkanaDharma_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgIkanaDharma* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.scale.x = 0.3f;
    this->dyna.actor.scale.y = 0.1f;
    this->dyna.actor.scale.z = 0.3f;
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gStoneTowerTemplePunchablePillarCol);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
    if (!BGIKANADHARMA_IS_CHILD(&this->dyna.actor)) {
        f32 segmentY = this->dyna.actor.world.pos.y;
        s32 numSegments = BGIKANADHARMA_NUM_SEGMENTS(&this->dyna.actor);
        s32 i;

        for (i = 0; i < numSegments; i++) {
            segmentY += 60.0f;
            Actor_SpawnAsChildAndCutscene(&globalCtx->actorCtx, globalCtx, ACTOR_BG_IKANA_DHARMA,
                                          this->dyna.actor.world.pos.x, segmentY, this->dyna.actor.world.pos.z,
                                          this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y,
                                          this->dyna.actor.shape.rot.z, BGIKANADHARMA_PARAMS(0, true, 0),
                                          this->dyna.actor.cutscene, this->dyna.actor.unk20, NULL);
        }

        this->dyna.actor.bgCheckFlags |= 1;
    }

    BgIkanaDharma_SetupWaitForHit(this);
}

void BgIkanaDharma_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (sFirstHitBgIkanaDharma == this) {
        sFirstHitBgIkanaDharma = NULL;
    }
}

void BgIkanaDharma_SetupWaitForHit(BgIkanaDharma* this) {
    this->actionFunc = BgIkanaDharma_WaitForHit;
    this->dyna.actor.speedXZ = 0.0f;
}

void BgIkanaDharma_WaitForHit(BgIkanaDharma* this, GlobalContext* globalCtx) {
    s32 wasHit = (this->collider.base.acFlags & AC_HIT) != 0;
    Player* player = GET_PLAYER(globalCtx);
    BgIkanaDharma* this2 = this;
    s32 tempAngle1;
    s32 tempAngle2;

    if (wasHit) {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    if (wasHit && sFirstHitBgIkanaDharma == NULL) {
        sFirstHitBgIkanaDharma = this2;
        Flags_SetSwitch(globalCtx, BGIKANADHARMA_GET_SWITCHFLAG(&this->dyna.actor));
        tempAngle1 = BINANG_ADD(this->dyna.actor.yawTowardsPlayer, 0x8000);
        tempAngle2 = (BINANG_SUB(player->actor.shape.rot.y, tempAngle1) >> 1);
        this->dyna.actor.world.rot.y = tempAngle1 + tempAngle2 + 0xF000;
        this->dyna.actor.speedXZ = 20.0f;
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_DARUMA_VANISH);
        BgIkanaDharma_SetupStartCutscene(this);
    } else if ((this->dyna.actor.flags & ACTOR_FLAG_40) == ACTOR_FLAG_40 && sFirstHitBgIkanaDharma == NULL &&
               this->dyna.actor.xzDistToPlayer < 420.0f) {
        tempAngle1 = BINANG_SUB(this->dyna.actor.yawTowardsPlayer, player->actor.shape.rot.y);
        tempAngle1 = ABS_ALT(tempAngle1);

        if (tempAngle1 > 0x4000) {
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void BgIkanaDharma_SetupStartCutscene(BgIkanaDharma* this) {
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    this->actionFunc = BgIkanaDharma_StartCutscene;
}

void BgIkanaDharma_StartCutscene(BgIkanaDharma* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        BgIkanaDharma_SetupWaitForCutsceneToEnd(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void BgIkanaDharma_SetupWaitForCutsceneToEnd(BgIkanaDharma* this) {
    this->cutsceneFramesRemaining = 10;
    this->actionFunc = BgIkanaDharma_WaitForCutsceneToEnd;
}

void BgIkanaDharma_WaitForCutsceneToEnd(BgIkanaDharma* this, GlobalContext* globalCtx) {
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
        BgIkanaDharma_SpawnEffects(this, globalCtx);
    }
}

void BgIkanaDharma_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = THIS;

    this->actionFunc(this, globalCtx);
    if (this->actionFunc == BgIkanaDharma_WaitForHit) {
        DynaPolyActor* actorBelow;
        s32 pad[2];

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
        f32 wallCheckRadius = this->dyna.actor.scale.x * 300.0f;
        wallCheckRadius = CLAMP_MIN(wallCheckRadius, 2.0f);

        Actor_MoveWithGravity(&this->dyna.actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 20.0f, wallCheckRadius, 0.0f, 5);
    }

    Actor_SetFocus(&this->dyna.actor, 40.0f);
}

void BgIkanaDharma_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaDharma* this = THIS;

    Gfx_DrawDListOpa(globalCtx, gStoneTowerTemplePunchablePillarDL);
}
