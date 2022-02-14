/*
 * File: z_bg_numa_hana.c
 * Overlay: ovl_Bg_Numa_Hana
 * Description: Big wooden flower in Woodfall Temple
 */

#include "z_bg_numa_hana.h"

#define FLAGS 0x00000410

#define THIS ((BgNumaHana*)thisx)

void BgNumaHana_Init(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Update(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A1AA28(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1AA4C(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1AB00(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1ABF0(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1ACE0(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1AE1C(BgNumaHana* this, GlobalContext* globalCtx);
void func_80A1AA14(BgNumaHana* this);
void func_80A1AE08(BgNumaHana* this);
void func_80A1AA38(BgNumaHana* this);
void func_80A1AAE8(BgNumaHana* this);
void func_80A1ABD8(BgNumaHana* this);
void func_80A1ACCC(BgNumaHana* this);

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

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A1B260 = {
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

static FireObjInitParams D_80A1B28C = {
    0.00405000010505f, 0.0500000007451f, 3, 1, 0, 0, 0,
};

static s16 D_80A1B29C[] = { 0x0000, 0x2AAA, 0x5555, 0x8000, 0xAAAA, 0xD555 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A1B2A8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_STOP),
};

extern CollisionHeader D_06009FE0;
extern CollisionHeader D_0600A740;
extern UNK_TYPE D_0600B928;

s32 func_80A1A500(BgNumaHana* this, GlobalContext* globalCtx) {
    Actor* child;

    child =
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, ACTOR_BG_NUMA_HANA,
                           this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                           this->dyna.actor.shape.rot.x, this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 1);

    return child != NULL;
}

void func_80A1A56C(BgNumaHana* this) {
    f32 temp_f20;
    f32 temp_f24;
    f32 temp_f26;
    s16 temp_s1;
    UnkBgNumaHanaStruct* phi_s2;
    UnkBgNumaHanaStruct* phi_s5;
    s32 i;

    temp_f24 = this->dyna.actor.world.pos.y + -10.0f;
    temp_s1 = this->unk_328 - 0x2000;
    temp_f20 = (Math_CosS(temp_s1) * 77.42784f) + 74.95192f;
    temp_f26 = (Math_SinS(this->unk_328) * 77.42784f) + this->dyna.actor.world.pos.y + -64.74976f;
    for (i = 0; i < 6; i++) {
        phi_s2 = &this->unk_238[i];
        phi_s5 = &this->unk_2B0[i];
        temp_s1 = D_80A1B29C[i] + this->dyna.actor.shape.rot.y + 0x1555;

        phi_s2->unk_00.x = (Math_SinS(temp_s1) * 74.95192f) + this->dyna.actor.world.pos.x;
        phi_s2->unk_00.y = temp_f24;
        phi_s2->unk_00.z = (Math_CosS(temp_s1) * 74.95192f) + this->dyna.actor.world.pos.z;
        phi_s2->unk_0C.x = this->dyna.actor.shape.rot.x;
        phi_s2->unk_0C.y = temp_s1 - 0x4000;
        phi_s2->unk_0C.z = this->dyna.actor.shape.rot.z + this->unk_328;

        phi_s5->unk_00.x = (Math_SinS(temp_s1) * temp_f20) + this->dyna.actor.world.pos.x;
        phi_s5->unk_00.y = temp_f26;
        phi_s5->unk_00.z = (Math_CosS(temp_s1) * temp_f20) + this->dyna.actor.world.pos.z;
        phi_s5->unk_0C.x = phi_s2->unk_0C.x;
        phi_s5->unk_0C.y = phi_s2->unk_0C.y;
        phi_s5->unk_0C.z = phi_s2->unk_0C.z + this->unk_338;
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
    s32 temp;
    BgNumaHana* this = THIS;

    temp = this->dyna.actor.params & 1;
    Actor_ProcessInitChain(&this->dyna.actor, D_80A1B2A8);
    DynaPolyActor_Init(&this->dyna, 3);
    if (temp == 1) {
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_06009FE0);
        func_80A1AA14(this);
        this->dyna.actor.draw = NULL;
        return;
    }

    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_0600A740);
    FireObj_Init(globalCtx, &this->unk_15C, &D_80A1B28C, &this->dyna.actor);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &D_80A1B260);
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    if (!func_80A1A500(this, globalCtx)) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    if (gSaveContext.weekEventReg[12] & 1) {
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->unk_328 = 0x2000;
        this->unk_32A = 0x2000;
        this->unk_32C = 0;
        this->unk_32E = 0;
        this->unk_330 = 0;
        this->unk_334 = 0.0f;
        this->unk_338 = -0x4000;
        this->unk_33A = 0;
        this->unk_33C = 0x147;
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 210.0f;
        FireObj_SetState2(&this->unk_15C, 0.05f, 2);
        Flags_SetSwitch(globalCtx, BG_NUMA_HAMA_SWITCH_FLAG(&this->dyna.actor));
        func_80A1AE08(this);
    } else {
        child = (DynaPolyActor*)this->dyna.actor.child;
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, child->bgId);
        Flags_UnsetSwitch(globalCtx, BG_NUMA_HAMA_SWITCH_FLAG(&this->dyna.actor));
        func_80A1AA38(this);
    }

    func_80A1A56C(this);
}

void BgNumaHana_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgNumaHana* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    if (!(this->dyna.actor.params & 1)) {
        FireObj_Destroy(globalCtx, &this->unk_15C);
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

void func_80A1AA14(BgNumaHana* this) {
    this->actionFunc = func_80A1AA28;
}

void func_80A1AA28(BgNumaHana* this, GlobalContext* globalCtx) {
}

void func_80A1AA38(BgNumaHana* this) {
    this->actionFunc = func_80A1AA4C;
}

void func_80A1AA4C(BgNumaHana* this, GlobalContext* globalCtx) {
    if (this->unk_15C.state != 3) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLAME_IGNITION);
        if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
            gSaveContext.weekEventReg[12] |= 1;
            Flags_SetSwitch(globalCtx, BG_NUMA_HAMA_SWITCH_FLAG(&this->dyna.actor));
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
        if (this->unk_33E >= 0xB) {
            func_80A1ABD8(this);
        } else {
            if (this->unk_33E <= 0) {
                this->unk_32E = 0;
                this->unk_330 = 0;
                this->unk_334 = 420.0f;
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_STOP);
            }
            this->unk_33E += 1;
        }
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_MOVE - SFX_FLAG);
    }

    func_80A1A750(&this->unk_32E, &this->unk_330, &this->unk_334, 20.0f);
    this->unk_328 = this->unk_32A + this->unk_32E;
    func_80A1A56C(this);
}

void func_80A1ABD8(BgNumaHana* this) {
    this->actionFunc = func_80A1ABF0;
    this->unk_33E = 0;
}

void func_80A1ABF0(BgNumaHana* this, GlobalContext* globalCtx) {

    Math_StepToS(&this->unk_33A, 0xF0, 0xE);
    if (Math_ScaledStepToS(&this->unk_338, -0x4000, this->unk_33A)) {
        if (this->unk_33E >= 0xB) {
            func_80A1ACCC(this);
        } else {
            if (this->unk_33E <= 0) {
                this->unk_32E = 0;
                this->unk_330 = 0x5120;
                this->unk_334 = 130.0f;
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_STOP);
            }
            this->unk_33E += 1;
        }
    } else {
        func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWERPETAL_MOVE - SFX_FLAG);
    }

    func_80A1A750(&this->unk_32E, &this->unk_330, &this->unk_334, 7.0f);
    this->unk_328 = this->unk_32A + this->unk_32E;
    func_80A1A56C(this);
}

void func_80A1ACCC(BgNumaHana* this) {
    this->actionFunc = func_80A1ACE0;
}

void func_80A1ACE0(BgNumaHana* this, GlobalContext* globalCtx) {
    s32 pad;
    DynaPolyActor* child;

    func_80A1A750(&this->unk_32E, &this->unk_330, &this->unk_334, 10.0f);
    this->unk_328 = this->unk_32A + this->unk_32E;
    Math_StepToS(&this->unk_33C, 0x111, 0xA);
    this->dyna.actor.shape.rot.y += this->unk_33C;
    Math_StepToF(&this->dyna.actor.velocity.y, 3.0f, 0.3f);
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 210.0f,
                     this->dyna.actor.velocity.y)) {
        child = (DynaPolyActor*)this->dyna.actor.child;
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, child->bgId);
        func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->unk_328 = 0x2000;
        this->unk_32A = 0x2000;
        this->unk_32C = 0;
        this->unk_32E = 0;
        this->unk_330 = 0;
        this->unk_338 = -0x4000;
        this->unk_33A = 0;
        this->unk_33C = 0x147;
        this->unk_334 = 0.0f;
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        func_80A1AE08(this);
    }

    func_80A1A56C(this);
    func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWER_ROLLING - SFX_FLAG);
}

void func_80A1AE08(BgNumaHana* this) {
    this->actionFunc = func_80A1AE1C;
}

void func_80A1AE1C(BgNumaHana* this, GlobalContext* globalCtx) {
    this->dyna.actor.shape.rot.y += this->unk_33C;
    this->unk_328 = this->unk_32A + this->unk_32E;
    func_80A1A56C(this);
    func_800B9010(&this->dyna.actor, NA_SE_EV_FLOWER_ROLLING - SFX_FLAG);
}

void BgNumaHana_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgNumaHana* this = THIS;
    s32 temp;
    Vec3f sp28;

    temp = this->dyna.actor.params & 1;
    if (temp == 0) {
        sp28.x = this->dyna.actor.world.pos.x;
        sp28.y = this->dyna.actor.world.pos.y + 10.5f;
        sp28.z = this->dyna.actor.world.pos.z;
        FireObj_SetPosition(&this->unk_15C, &sp28);
        FireObj_Update(globalCtx, &this->unk_15C, &this->dyna.actor);
    }

    this->actionFunc(this, globalCtx);

    if (temp == 0) {
        this->dyna.actor.child->shape.rot = this->dyna.actor.shape.rot;
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Draw.s")
