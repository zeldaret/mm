/*
 * File: z_bg_numa_hana.c
 * Overlay: ovl_Bg_Numa_Hana
 * Description: Big wooden flower in Woodfall Temple
 */

#include "z_bg_numa_hana.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_syokudai/object_syokudai.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_400)

#define THIS ((BgNumaHana*)thisx)

void BgNumaHana_Init(Actor* thisx, PlayState* play);
void BgNumaHana_Destroy(Actor* thisx, PlayState* play);
void BgNumaHana_Update(Actor* thisx, PlayState* play);
void BgNumaHana_Draw(Actor* thisx, PlayState* play2);

void BgNumaHana_SetupDoNothing(BgNumaHana* this);
void BgNumaHana_DoNothing(BgNumaHana* this, PlayState* play);
void BgNumaHana_SetupClosedIdle(BgNumaHana* this);
void BgNumaHana_ClosedIdle(BgNumaHana* this, PlayState* play);
void BgNumaHana_SetupUnfoldInnerPetals(BgNumaHana* this);
void BgNumaHana_UnfoldInnerPetals(BgNumaHana* this, PlayState* play);
void BgNumaHana_SetupUnfoldOuterPetals(BgNumaHana* this);
void BgNumaHana_UnfoldOuterPetals(BgNumaHana* this, PlayState* play);
void BgNumaHana_SetupRaiseFlower(BgNumaHana* this);
void BgNumaHana_RaiseFlower(BgNumaHana* this, PlayState* play);
void BgNumaHana_SetupOpenedIdle(BgNumaHana* this);
void BgNumaHana_OpenedIdle(BgNumaHana* this, PlayState* play);

ActorInit Bg_Numa_Hana_InitVars = {
    /**/ ACTOR_BG_NUMA_HANA,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_NUMA_OBJ,
    /**/ sizeof(BgNumaHana),
    /**/ BgNumaHana_Init,
    /**/ BgNumaHana_Destroy,
    /**/ BgNumaHana_Update,
    /**/ BgNumaHana_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0x01CBFBB6, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 18, 16, 0, { 0, 0, 0 } },
};

static FireObjInitParams sFireObjInit = {
    0.00405000010505f, 0.0500000007451f, 3, 1, 0, 0, 0,
};

static s16 sInitialAnglePerPetal[] = { 0x0000, 0x2AAA, 0x5555, 0x8000, 0xAAAA, 0xD555 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_STOP),
};

/**
 * Spawns another wooden flower instance that handles the opened flower's collision.
 * Returns true if this wooden flower instance was succesfully spawned.
 */
s32 BgNumaHana_SpawnOpenFlowerCollisionChild(BgNumaHana* this, PlayState* play) {
    Actor* child;

    child = Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_BG_NUMA_HANA,
                               this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                               this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z,
                               BG_NUMA_HANA_TYPE_OPEN_FLOWER_COLLISION);

    return child != NULL;
}

void BgNumaHana_UpdatePetalPosRots(BgNumaHana* this) {
    f32 outerPetalPosScale;
    f32 innerPetalYPos;
    f32 outerPetalYPos;
    s16 angle;
    WoodenFlowerPetalPosRot* innerPetalPosRot;
    WoodenFlowerPetalPosRot* outerPetalPosRot;
    s32 i;

    innerPetalYPos = this->dyna.actor.world.pos.y + -10.0f;
    angle = this->petalZRotation - 0x2000;
    outerPetalPosScale = (Math_CosS(angle) * 77.42784f) + 74.95192f;
    outerPetalYPos = (Math_SinS(this->petalZRotation) * 77.42784f) + this->dyna.actor.world.pos.y + -64.74976f;

    for (i = 0; i < ARRAY_COUNT(this->innerPetalPosRot); i++) {
        innerPetalPosRot = &this->innerPetalPosRot[i];
        outerPetalPosRot = &this->outerPetalPosRot[i];
        angle = sInitialAnglePerPetal[i] + this->dyna.actor.shape.rot.y + 0x1555;

        innerPetalPosRot->pos.x = (Math_SinS(angle) * 74.95192f) + this->dyna.actor.world.pos.x;
        innerPetalPosRot->pos.y = innerPetalYPos;
        innerPetalPosRot->pos.z = (Math_CosS(angle) * 74.95192f) + this->dyna.actor.world.pos.z;
        innerPetalPosRot->rot.x = this->dyna.actor.shape.rot.x;
        innerPetalPosRot->rot.y = angle - 0x4000;
        innerPetalPosRot->rot.z = this->dyna.actor.shape.rot.z + this->petalZRotation;

        outerPetalPosRot->pos.x = (Math_SinS(angle) * outerPetalPosScale) + this->dyna.actor.world.pos.x;
        outerPetalPosRot->pos.y = outerPetalYPos;
        outerPetalPosRot->pos.z = (Math_CosS(angle) * outerPetalPosScale) + this->dyna.actor.world.pos.z;
        outerPetalPosRot->rot.x = innerPetalPosRot->rot.x;
        outerPetalPosRot->rot.y = innerPetalPosRot->rot.y;
        outerPetalPosRot->rot.z = innerPetalPosRot->rot.z + this->outerPetalZRotation;
    }
}

/**
 * As the pieces of the petals finish unfolding, they shake to appear
 * as if they are "settling" into place. This function is responsible
 * for computing the extra rotation for this "settling".
 */
void BgNumaHana_UpdateSettleRotation(s16* settleZRotation, s16* settleAngle, f32* settleScale, f32 scaleStep) {
    *settleAngle += 0x32C8;
    Math_StepToF(settleScale, 0.0f, scaleStep);
    *settleZRotation += (s16)(Math_SinS(*settleAngle) * *settleScale);
}

void BgNumaHana_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    DynaPolyActor* child;
    s32 type;
    BgNumaHana* this = THIS;

    type = BG_NUMA_HANA_GET_TYPE(&this->dyna.actor);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 3);

    if (type == BG_NUMA_HANA_TYPE_OPEN_FLOWER_COLLISION) {
        DynaPolyActor_LoadMesh(play, &this->dyna, &gWoodenFlowerOpenedFlowerCol);
        BgNumaHana_SetupDoNothing(this);
        this->dyna.actor.draw = NULL;
    } else {
        DynaPolyActor_LoadMesh(play, &this->dyna, &gWoodenFlowerClosedFlowerCol);
        FireObj_Init(play, &this->fire, &sFireObjInit, &this->dyna.actor);
        Collider_InitCylinder(play, &this->torchCollider);
        Collider_SetCylinder(play, &this->torchCollider, &this->dyna.actor, &sCylinderInit);
        this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
        if (!BgNumaHana_SpawnOpenFlowerCollisionChild(this, play)) {
            Actor_Kill(&this->dyna.actor);
            return;
        }

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_12_01)) {
            func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);

            this->petalZRotation = 0x2000;
            this->innerPetalZRotation = 0x2000;
            this->innerPetalZRotationalVelocity = 0;
            this->settleZRotation = 0;
            this->settleAngle = 0;
            this->settleScale = 0.0f;
            this->outerPetalZRotation = -0x4000;
            this->outerPetalZRotationalVelocity = 0;
            this->flowerRotationalVelocity = 0x147;

            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 210.0f;
            FireObj_SetState2(&this->fire, 0.05f, 2);
            Flags_SetSwitch(play, BG_NUMA_HANA_SWITCH_FLAG(&this->dyna.actor));
            BgNumaHana_SetupOpenedIdle(this);
        } else {
            child = (DynaPolyActor*)this->dyna.actor.child;
            func_800C62BC(play, &play->colCtx.dyna, child->bgId);
            Flags_UnsetSwitch(play, BG_NUMA_HANA_SWITCH_FLAG(&this->dyna.actor));
            BgNumaHana_SetupClosedIdle(this);
        }

        BgNumaHana_UpdatePetalPosRots(this);
    }
}

void BgNumaHana_Destroy(Actor* thisx, PlayState* play) {
    BgNumaHana* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    if (BG_NUMA_HANA_GET_TYPE(&this->dyna.actor) == BG_NUMA_HANA_TYPE_NORMAL) {
        FireObj_Destroy(play, &this->fire);
        Collider_DestroyCylinder(play, &this->torchCollider);
    }
}

void BgNumaHana_SetupDoNothing(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_DoNothing;
}

void BgNumaHana_DoNothing(BgNumaHana* this, PlayState* play) {
}

void BgNumaHana_SetupClosedIdle(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_ClosedIdle;
}

/**
 * This function waits for the torch to be lit. Once it is, it starts
 * the cutscene where the petals unfold.
 */
void BgNumaHana_ClosedIdle(BgNumaHana* this, PlayState* play) {
    if (this->fire.state != 3) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLAME_IGNITION);
        if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
            SET_WEEKEVENTREG(WEEKEVENTREG_12_01);
            Flags_SetSwitch(play, BG_NUMA_HANA_SWITCH_FLAG(&this->dyna.actor));
            BgNumaHana_SetupUnfoldInnerPetals(this);
        } else {
            ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        }
    }
}

void BgNumaHana_SetupUnfoldInnerPetals(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_UnfoldInnerPetals;
    this->transitionTimer = 0;
}

/**
 * Partially moves the flower to the "open" position by raising the "inner"
 * parts of the petals that are closest to the stalk.
 */
void BgNumaHana_UnfoldInnerPetals(BgNumaHana* this, PlayState* play) {
    Math_StepToS(&this->innerPetalZRotationalVelocity, 240, 14);
    if (Math_ScaledStepToS(&this->innerPetalZRotation, 0x2000, this->innerPetalZRotationalVelocity)) {
        if (this->transitionTimer >= 11) {
            BgNumaHana_SetupUnfoldOuterPetals(this);
        } else {
            if (this->transitionTimer <= 0) {
                this->settleZRotation = 0;
                this->settleAngle = 0;
                this->settleScale = 420.0f;
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_STOP);
            }
            this->transitionTimer++;
        }
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_MOVE - SFX_FLAG);
    }

    BgNumaHana_UpdateSettleRotation(&this->settleZRotation, &this->settleAngle, &this->settleScale, 20.0f);
    this->petalZRotation = this->innerPetalZRotation + this->settleZRotation;
    BgNumaHana_UpdatePetalPosRots(this);
}

void BgNumaHana_SetupUnfoldOuterPetals(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_UnfoldOuterPetals;
    this->transitionTimer = 0;
}

/**
 * Partially moves the flower to the "open" position by lowering the "outer"
 * parts of the petals that are furthest to the stalk.
 */
void BgNumaHana_UnfoldOuterPetals(BgNumaHana* this, PlayState* play) {
    Math_StepToS(&this->outerPetalZRotationalVelocity, 240, 14);
    if (Math_ScaledStepToS(&this->outerPetalZRotation, -0x4000, this->outerPetalZRotationalVelocity)) {
        if (this->transitionTimer >= 11) {
            BgNumaHana_SetupRaiseFlower(this);
        } else {
            if (this->transitionTimer <= 0) {
                this->settleZRotation = 0;
                this->settleAngle = 0x5120;
                this->settleScale = 130.0f;
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_STOP);
            }
            this->transitionTimer++;
        }
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_MOVE - SFX_FLAG);
    }

    BgNumaHana_UpdateSettleRotation(&this->settleZRotation, &this->settleAngle, &this->settleScale, 7.0f);
    this->petalZRotation = this->innerPetalZRotation + this->settleZRotation;
    BgNumaHana_UpdatePetalPosRots(this);
}

void BgNumaHana_SetupRaiseFlower(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_RaiseFlower;
}

/**
 * This function slowly raises the flower to its final height and makes it start spinning.
 */
void BgNumaHana_RaiseFlower(BgNumaHana* this, PlayState* play) {
    s32 pad;
    DynaPolyActor* child;

    BgNumaHana_UpdateSettleRotation(&this->settleZRotation, &this->settleAngle, &this->settleScale, 10.0f);
    this->petalZRotation = this->innerPetalZRotation + this->settleZRotation;
    Math_StepToS(&this->flowerRotationalVelocity, 0x111, 0xA);
    this->dyna.actor.shape.rot.y += this->flowerRotationalVelocity;
    Math_StepToF(&this->dyna.actor.velocity.y, 3.0f, 0.3f);

    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 210.0f,
                     this->dyna.actor.velocity.y)) {
        child = (DynaPolyActor*)this->dyna.actor.child;

        // Swaps out the "closed" flower collision for the "opened" collision.
        func_800C6314(play, &play->colCtx.dyna, child->bgId);
        func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);

        this->petalZRotation = 0x2000;
        this->innerPetalZRotation = 0x2000;
        this->innerPetalZRotationalVelocity = 0;
        this->settleZRotation = 0;
        this->settleAngle = 0;
        this->outerPetalZRotation = -0x4000;
        this->outerPetalZRotationalVelocity = 0;
        this->flowerRotationalVelocity = 0x147;
        this->settleScale = 0.0f;

        ActorCutscene_Stop(this->dyna.actor.cutscene);
        BgNumaHana_SetupOpenedIdle(this);
    }

    BgNumaHana_UpdatePetalPosRots(this);
    func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWER_ROLLING - SFX_FLAG);
}

void BgNumaHana_SetupOpenedIdle(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_OpenedIdle;
}

/**
 * Spins the "opened" flower around the y-axis.
 */
void BgNumaHana_OpenedIdle(BgNumaHana* this, PlayState* play) {
    this->dyna.actor.shape.rot.y += this->flowerRotationalVelocity;
    this->petalZRotation = this->innerPetalZRotation + this->settleZRotation;
    BgNumaHana_UpdatePetalPosRots(this);
    func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWER_ROLLING - SFX_FLAG);
}

void BgNumaHana_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    BgNumaHana* this = THIS;
    s32 type = BG_NUMA_HANA_GET_TYPE(&this->dyna.actor);
    Vec3f firePos;

    if (type == BG_NUMA_HANA_TYPE_NORMAL) {
        firePos.x = this->dyna.actor.world.pos.x;
        firePos.y = this->dyna.actor.world.pos.y + 10.5f;
        firePos.z = this->dyna.actor.world.pos.z;
        FireObj_SetPosition(&this->fire, &firePos);
        FireObj_Update(play, &this->fire, &this->dyna.actor);
    }

    this->actionFunc(this, play);

    if (type == BG_NUMA_HANA_TYPE_NORMAL) {
        this->dyna.actor.child->shape.rot = this->dyna.actor.shape.rot;
        Collider_UpdateCylinder(&this->dyna.actor, &this->torchCollider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->torchCollider.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->torchCollider.base);
    }
}

void BgNumaHana_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    BgNumaHana* this = THIS;
    WoodenFlowerPetalPosRot* innerPetalPosRot;
    WoodenFlowerPetalPosRot* outerPetalPosRot;
    s32 objectIndex;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gWoodenFlowerStalkDL);

    for (i = 0; i < ARRAY_COUNT(this->innerPetalPosRot); i++) {
        innerPetalPosRot = &this->innerPetalPosRot[i];
        outerPetalPosRot = &this->outerPetalPosRot[i];

        Matrix_SetTranslateRotateYXZ(innerPetalPosRot->pos.x, innerPetalPosRot->pos.y, innerPetalPosRot->pos.z,
                                     &innerPetalPosRot->rot);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gWoodenFlowerInnerPetalDL);

        Matrix_SetTranslateRotateYXZ(outerPetalPosRot->pos.x, outerPetalPosRot->pos.y, outerPetalPosRot->pos.z,
                                     &outerPetalPosRot->rot);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gWoodenFlowerOuterPetalDL);
    }

    objectIndex = Object_GetIndex(&play->objectCtx, OBJECT_SYOKUDAI);
    if ((objectIndex >= 0) && (Object_IsLoaded(&play->objectCtx, objectIndex))) {
        Matrix_SetTranslateRotateYXZ(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y - 64.5f,
                                     this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
        Matrix_Scale(1.5f, 1.5f, 1.5f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[objectIndex].segment);
        gSPDisplayList(POLY_OPA_DISP++, gObjectSyokudaiTypeNoSwitchDL);
    }

    FireObj_Draw(play, &this->fire);

    CLOSE_DISPS(play->state.gfxCtx);
}
