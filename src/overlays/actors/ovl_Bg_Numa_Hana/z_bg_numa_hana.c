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

void BgNumaHana_Init(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Update(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgNumaHana_SetupDoNothing(BgNumaHana* this);
void BgNumaHana_DoNothing(BgNumaHana* this, GlobalContext* globalCtx);
void BgNumaHana_SetupClosedIdle(BgNumaHana* this);
void BgNumaHana_ClosedIdle(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1AAE8(BgNumaHana* this);
void func_80A1AB00(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1ABD8(BgNumaHana* this);
void func_80A1ABF0(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1ACCC(BgNumaHana* this);
void func_80A1ACE0(BgNumaHana* this, GlobalContext* globalCtx);
void BgNumaHana_SetupOpenedIdle(BgNumaHana* this);
void BgNumaHana_OpenedIdle(BgNumaHana* this, GlobalContext* globalCtx);

const ActorInit Bg_Numa_Hana_InitVars = {
    ACTOR_BG_NUMA_HANA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_NUMA_OBJ,
    sizeof(BgNumaHana),
    (ActorFunc)BgNumaHana_Init,
    (ActorFunc)BgNumaHana_Destroy,
    (ActorFunc)BgNumaHana_Update,
    (ActorFunc)BgNumaHana_Draw,
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

static s16 sAnglePerPetal[] = { 0x0000, 0x2AAA, 0x5555, 0x8000, 0xAAAA, 0xD555 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_STOP),
};

s32 BgNumaHana_SpawnOpenFlowerCollisionChild(BgNumaHana* this, GlobalContext* globalCtx) {
    Actor* child;

    child = Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_BG_NUMA_HANA,
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
    angle = this->overallPetalZRot - 0x2000;
    outerPetalPosScale = (Math_CosS(angle) * 77.42784f) + 74.95192f;
    outerPetalYPos = (Math_SinS(this->overallPetalZRot) * 77.42784f) + this->dyna.actor.world.pos.y + -64.74976f;

    for (i = 0; i < ARRAY_COUNT(this->innerPetalPosRot); i++) {
        innerPetalPosRot = &this->innerPetalPosRot[i];
        outerPetalPosRot = &this->outerPetalPosRot[i];
        angle = sAnglePerPetal[i] + this->dyna.actor.shape.rot.y + 0x1555;

        innerPetalPosRot->pos.x = (Math_SinS(angle) * 74.95192f) + this->dyna.actor.world.pos.x;
        innerPetalPosRot->pos.y = innerPetalYPos;
        innerPetalPosRot->pos.z = (Math_CosS(angle) * 74.95192f) + this->dyna.actor.world.pos.z;
        innerPetalPosRot->rot.x = this->dyna.actor.shape.rot.x;
        innerPetalPosRot->rot.y = angle - 0x4000;
        innerPetalPosRot->rot.z = this->dyna.actor.shape.rot.z + this->overallPetalZRot;

        outerPetalPosRot->pos.x = (Math_SinS(angle) * outerPetalPosScale) + this->dyna.actor.world.pos.x;
        outerPetalPosRot->pos.y = outerPetalYPos;
        outerPetalPosRot->pos.z = (Math_CosS(angle) * outerPetalPosScale) + this->dyna.actor.world.pos.z;
        outerPetalPosRot->rot.x = innerPetalPosRot->rot.x;
        outerPetalPosRot->rot.y = innerPetalPosRot->rot.y;
        outerPetalPosRot->rot.z = innerPetalPosRot->rot.z + this->extraOuterPetalZRot;
    }
}

void func_80A1A750(s16* arg0, s16* arg1, f32* arg2, f32 arg3) {
    *arg1 += 0x32C8;
    Math_StepToF(arg2, 0.0f, arg3);
    *arg0 += (s16)(Math_SinS(*arg1) * *arg2);
}

void BgNumaHana_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DynaPolyActor* child;
    s32 type;
    BgNumaHana* this = THIS;

    type = BG_NUMA_HANA_GET_TYPE(&this->dyna.actor);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 3);
    if (type == BG_NUMA_HANA_TYPE_OPEN_FLOWER_COLLISION) {
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gWoodenFlowerOpenFlowerCol);
        BgNumaHana_SetupDoNothing(this);
        this->dyna.actor.draw = NULL;
        return;
    }

    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gWoodenFlowerClosedFlowerCol);
    FireObj_Init(globalCtx, &this->fire, &sFireObjInit, &this->dyna.actor);
    Collider_InitCylinder(globalCtx, &this->torchCollider);
    Collider_SetCylinder(globalCtx, &this->torchCollider, &this->dyna.actor, &sCylinderInit);
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    if (!BgNumaHana_SpawnOpenFlowerCollisionChild(this, globalCtx)) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    if (gSaveContext.weekEventReg[12] & 1) {
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->overallPetalZRot = 0x2000;
        this->unk_32A = 0x2000;
        this->unk_32C = 0;
        this->unk_32E = 0;
        this->unk_330 = 0;
        this->unk_334 = 0.0f;
        this->extraOuterPetalZRot = -0x4000;
        this->unk_33A = 0;
        this->unk_33C = 0x147;
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 210.0f;
        FireObj_SetState2(&this->fire, 0.05f, 2);
        Flags_SetSwitch(globalCtx, BG_NUMA_HANA_SWITCH_FLAG(&this->dyna.actor));
        BgNumaHana_SetupOpenedIdle(this);
    } else {
        child = (DynaPolyActor*)this->dyna.actor.child;
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, child->bgId);
        Flags_UnsetSwitch(globalCtx, BG_NUMA_HANA_SWITCH_FLAG(&this->dyna.actor));
        BgNumaHana_SetupClosedIdle(this);
    }

    BgNumaHana_UpdatePetalPosRots(this);
}

void BgNumaHana_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgNumaHana* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    if (BG_NUMA_HANA_GET_TYPE(&this->dyna.actor) == BG_NUMA_HANA_TYPE_NORMAL) {
        FireObj_Destroy(globalCtx, &this->fire);
        Collider_DestroyCylinder(globalCtx, &this->torchCollider);
    }
}

void BgNumaHana_SetupDoNothing(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_DoNothing;
}

void BgNumaHana_DoNothing(BgNumaHana* this, GlobalContext* globalCtx) {
}

void BgNumaHana_SetupClosedIdle(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_ClosedIdle;
}

void BgNumaHana_ClosedIdle(BgNumaHana* this, GlobalContext* globalCtx) {
    if (this->fire.state != 3) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLAME_IGNITION);
        if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
            gSaveContext.weekEventReg[12] |= 1;
            Flags_SetSwitch(globalCtx, BG_NUMA_HANA_SWITCH_FLAG(&this->dyna.actor));
            func_80A1AAE8(this);
        } else {
            ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        }
    }
}

void func_80A1AAE8(BgNumaHana* this) {
    this->actionFunc = func_80A1AB00;
    this->unk_33E = 0;
}

void func_80A1AB00(BgNumaHana* this, GlobalContext* globalCtx) {
    Math_StepToS(&this->unk_32C, 0xF0, 0xE);
    if (Math_ScaledStepToS(&this->unk_32A, 0x2000, this->unk_32C)) {
        if (this->unk_33E >= 11) {
            func_80A1ABD8(this);
        } else {
            if (this->unk_33E <= 0) {
                this->unk_32E = 0;
                this->unk_330 = 0;
                this->unk_334 = 420.0f;
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_STOP);
            }
            this->unk_33E++;
        }
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_MOVE - SFX_FLAG);
    }

    func_80A1A750(&this->unk_32E, &this->unk_330, &this->unk_334, 20.0f);
    this->overallPetalZRot = this->unk_32A + this->unk_32E;
    BgNumaHana_UpdatePetalPosRots(this);
}

void func_80A1ABD8(BgNumaHana* this) {
    this->actionFunc = func_80A1ABF0;
    this->unk_33E = 0;
}

void func_80A1ABF0(BgNumaHana* this, GlobalContext* globalCtx) {
    Math_StepToS(&this->unk_33A, 0xF0, 0xE);
    if (Math_ScaledStepToS(&this->extraOuterPetalZRot, -0x4000, this->unk_33A)) {
        if (this->unk_33E >= 11) {
            func_80A1ACCC(this);
        } else {
            if (this->unk_33E <= 0) {
                this->unk_32E = 0;
                this->unk_330 = 0x5120;
                this->unk_334 = 130.0f;
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_STOP);
            }
            this->unk_33E++;
        }
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_MOVE - SFX_FLAG);
    }

    func_80A1A750(&this->unk_32E, &this->unk_330, &this->unk_334, 7.0f);
    this->overallPetalZRot = this->unk_32A + this->unk_32E;
    BgNumaHana_UpdatePetalPosRots(this);
}

void func_80A1ACCC(BgNumaHana* this) {
    this->actionFunc = func_80A1ACE0;
}

void func_80A1ACE0(BgNumaHana* this, GlobalContext* globalCtx) {
    s32 pad;
    DynaPolyActor* child;

    func_80A1A750(&this->unk_32E, &this->unk_330, &this->unk_334, 10.0f);
    this->overallPetalZRot = this->unk_32A + this->unk_32E;
    Math_StepToS(&this->unk_33C, 0x111, 0xA);
    this->dyna.actor.shape.rot.y += this->unk_33C;
    Math_StepToF(&this->dyna.actor.velocity.y, 3.0f, 0.3f);
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 210.0f,
                     this->dyna.actor.velocity.y)) {
        child = (DynaPolyActor*)this->dyna.actor.child;
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, child->bgId);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->overallPetalZRot = 0x2000;
        this->unk_32A = 0x2000;
        this->unk_32C = 0;
        this->unk_32E = 0;
        this->unk_330 = 0;
        this->extraOuterPetalZRot = -0x4000;
        this->unk_33A = 0;
        this->unk_33C = 0x147;
        this->unk_334 = 0.0f;
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        BgNumaHana_SetupOpenedIdle(this);
    }

    BgNumaHana_UpdatePetalPosRots(this);
    func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWER_ROLLING - SFX_FLAG);
}

void BgNumaHana_SetupOpenedIdle(BgNumaHana* this) {
    this->actionFunc = BgNumaHana_OpenedIdle;
}

void BgNumaHana_OpenedIdle(BgNumaHana* this, GlobalContext* globalCtx) {
    this->dyna.actor.shape.rot.y += this->unk_33C;
    this->overallPetalZRot = this->unk_32A + this->unk_32E;
    BgNumaHana_UpdatePetalPosRots(this);
    func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWER_ROLLING - SFX_FLAG);
}

void BgNumaHana_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgNumaHana* this = THIS;
    s32 type;
    Vec3f firePos;

    type = BG_NUMA_HANA_GET_TYPE(&this->dyna.actor);
    if (type == BG_NUMA_HANA_TYPE_NORMAL) {
        firePos.x = this->dyna.actor.world.pos.x;
        firePos.y = this->dyna.actor.world.pos.y + 10.5f;
        firePos.z = this->dyna.actor.world.pos.z;
        FireObj_SetPosition(&this->fire, &firePos);
        FireObj_Update(globalCtx, &this->fire, &this->dyna.actor);
    }

    this->actionFunc(this, globalCtx);

    if (type == BG_NUMA_HANA_TYPE_NORMAL) {
        this->dyna.actor.child->shape.rot = this->dyna.actor.shape.rot;
        Collider_UpdateCylinder(&this->dyna.actor, &this->torchCollider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->torchCollider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->torchCollider.base);
    }
}

void BgNumaHana_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    BgNumaHana* this = THIS;
    WoodenFlowerPetalPosRot* innerPetalPosRot;
    WoodenFlowerPetalPosRot* outerPetalPosRot;
    s32 objectIndex;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gWoodenFlowerStalkDL);

    for (i = 0; i < ARRAY_COUNT(this->innerPetalPosRot); i++) {
        innerPetalPosRot = &this->innerPetalPosRot[i];
        outerPetalPosRot = &this->outerPetalPosRot[i];

        Matrix_SetStateRotationAndTranslation(innerPetalPosRot->pos.x, innerPetalPosRot->pos.y, innerPetalPosRot->pos.z,
                                              &innerPetalPosRot->rot);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gWoodenFlowerPetalInnerDL);

        Matrix_SetStateRotationAndTranslation(outerPetalPosRot->pos.x, outerPetalPosRot->pos.y, outerPetalPosRot->pos.z,
                                              &outerPetalPosRot->rot);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gWoodenFlowerPetalOuterDL);
    }

    objectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_SYOKUDAI);
    if ((objectIndex >= 0) && (Object_IsLoaded(&globalCtx->objectCtx, objectIndex))) {
        Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y - 64.5f,
                                              this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
        Matrix_Scale(1.5f, 1.5f, 1.5f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[objectIndex].segment);
        gSPDisplayList(POLY_OPA_DISP++, gObjectSyokudaiTypeNoSwitchDL);
    }

    FireObj_Draw(globalCtx, &this->fire);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
