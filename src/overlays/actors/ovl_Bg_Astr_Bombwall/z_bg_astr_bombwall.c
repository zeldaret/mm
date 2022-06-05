/*
 * File: z_bg_astr_bombwall.c
 * Overlay: ovl_Bg_Astr_Bombwall
 * Description: Astral Observatory - Bombable Wall
 */

#include "z_bg_astr_bombwall.h"
#include "objects/object_astr_obj/object_astr_obj.h"

#define FLAGS 0x00000000

#define THIS ((BgAstrBombwall*)thisx)

void BgAstrBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C09ED0(ColliderTrisInit* arg0, Vec3f* arg1, Vec3s* arg2, ColliderTris* arg3);
void func_80C0A120(BgAstrBombwall* this, GlobalContext* globalCtx);
void func_80C0A378(BgAstrBombwall* this);
void func_80C0A38C(BgAstrBombwall* this, GlobalContext* globalCtx);
void func_80C0A400(BgAstrBombwall* this, GlobalContext* globalCtx);
void func_80C0A418(BgAstrBombwall* this, GlobalContext* globalCtx);
void func_80C0A458(BgAstrBombwall* this, GlobalContext* globalCtx);
void func_80C0A4BC(BgAstrBombwall* this, GlobalContext* globalCtx);

const ActorInit Bg_Astr_Bombwall_InitVars = {
    ACTOR_BG_ASTR_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ASTR_OBJ,
    sizeof(BgAstrBombwall),
    (ActorFunc)BgAstrBombwall_Init,
    (ActorFunc)BgAstrBombwall_Destroy,
    (ActorFunc)BgAstrBombwall_Update,
    (ActorFunc)BgAstrBombwall_Draw,
};

static ColliderTrisElementInit sTrisElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000008, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -70.0f, 0.0f, 3.0f }, { 70.0f, 0.0f, 3.0f }, { -70.0f, 200.0f, 3.0f } } },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000008, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 70.0f, 0.0f, 3.0f }, { 70.0f, 200.0f, 3.0f }, { -70.0f, 200.0f, 3.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    2,
    sTrisElementsInit,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

void func_80C09ED0(ColliderTrisInit* arg0, Vec3f* arg1, Vec3s* arg2, ColliderTris* arg3) {
    s32 i;
    s32 j;
    Vec3f sp54[3];

    Matrix_RotateYS(arg2->y, MTXMODE_NEW);
    Matrix_RotateXS(arg2->x, MTXMODE_APPLY);
    Matrix_RotateZS(arg2->z, MTXMODE_APPLY);

    for (i = 0; i < arg0->count; i++) {
        for (j = 0; j < 3; j++) {                                          // https://decomp.me/scratch/JrEnl
            Matrix_MultVec3f(&(arg0->elements + i)->dim.vtx[j], &sp54[j]); //! FAKE MATCH:
            Math_Vec3f_Sum(&sp54[j], arg1, &sp54[j]);
        }
        Collider_SetTrisVertices(arg3, i, &sp54[0], &sp54[1], &sp54[2]);
    }
}

void BgAstrBombwall_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgAstrBombwall* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_astr_obj_Colheader_002498);
    Collider_InitTris(globalCtx, &this->collider);
    if (Flags_GetSwitch(globalCtx, OBJBgAstrBombwall_GET_SWITCHFLAG(this))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    this->dyna.actor.flags |= 0x10000000;
    if (Collider_SetTris(globalCtx, &this->collider, &this->dyna.actor, &sTrisInit, this->colliderElements) == 0) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    func_80C09ED0(&sTrisInit, &this->dyna.actor.world.pos, &this->dyna.actor.shape.rot, &this->collider);
    SubS_FillCutscenesList(&this->dyna.actor, this->unk238, ARRAY_COUNT(this->unk238));
    func_80C0A378(this); 
}

void BgAstrBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgAstrBombwall* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80C0A120(BgAstrBombwall* this, GlobalContext* globalCtx) {
    s32 var_s1;
    Vec3f spC8;
    Vec3f spBC;
    s16 var_v0;
    Vec3f spAC;
    f32 temp_fv0;

    Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    for (var_s1 = 0; var_s1 < 0x1E; var_s1++) {
        spC8.x = Rand_Centered() * 140.0f;
        spC8.y = Rand_ZeroOne() * 200.0f;
        spC8.z = 0.0f;
        Matrix_MultVec3f(&spC8, &spBC);
        Math_Vec3f_Sum(&this->dyna.actor.world.pos, &spBC, &spBC);
        func_800BBFB0(globalCtx, &spBC, 50.0f, 2, Rand_ZeroOne() * 120.0f + 20.0f, Rand_ZeroOne() * 240.0f + 20.0f, 0);
        spAC.x = Rand_ZeroOne() * 2.5f;
        spAC.y = (Rand_ZeroOne() * 2.5f) + 1.0f;
        spAC.z = Rand_ZeroOne() * 2.5f;
        temp_fv0 = Rand_ZeroOne();

        if (temp_fv0 < 0.2f) {
            var_v0 = 0x60;
        } else if (temp_fv0 < 0.6f) {
            var_v0 = 0x40;
        } else {
            var_v0 = 0x20;
        }
        EffectSsKakera_Spawn(globalCtx, &spBC, &spAC, &spBC, -0x104, var_v0, 0x14, 0, 0, 0xA, 0, 0, 0x32, -1, 0x267,
                             object_astr_obj_DL_002178);
    }
}

void func_80C0A378(BgAstrBombwall* this) {
    this->actionFunc = func_80C0A38C;
}

void func_80C0A38C(BgAstrBombwall* this, GlobalContext* globalCtx) {
    if ((this->collider.base.acFlags & AC_HIT)) {
        this->collider.base.acFlags &= ~AC_HIT;
        Flags_SetSwitch(globalCtx, OBJBgAstrBombwall_GET_SWITCHFLAG(this));
        func_80C0A400(this, globalCtx);
        return;
    }
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80C0A400(BgAstrBombwall* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80C0A418;
}

void func_80C0A418(BgAstrBombwall* this, GlobalContext* globalCtx) {
    if (SubS_StartActorCutscene(&this->dyna.actor, this->unk238[0], -1, SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
        func_80C0A458(this, globalCtx);
    }
}

void func_80C0A458(BgAstrBombwall* this, GlobalContext* globalCtx) {
    func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    this->dyna.actor.draw = NULL;
    func_80C0A120(this, globalCtx);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WALL_BROKEN);
    this->actionFunc = func_80C0A4BC;
}

void func_80C0A4BC(BgAstrBombwall* this, GlobalContext* globalCtx) {
}

void BgAstrBombwall_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgAstrBombwall* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgAstrBombwall_Draw(Actor* thixs, GlobalContext* globalCtx) {
    {
        Gfx* opa;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        opa = POLY_OPA_DISP;
        gSPDisplayList(&opa[0], &sSetupDL[25 * 6]);
        gSPMatrix(&opa[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSetGeometryMode(&opa[2], 0x400000);
        gSPDisplayList(&opa[3], object_astr_obj_DL_002380);
        POLY_OPA_DISP = &opa[4];
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    {
        Gfx* xlu;

        OPEN_DISPS(globalCtx->state.gfxCtx);
        xlu = POLY_XLU_DISP;
        gSPDisplayList(&xlu[0], &sSetupDL[25 * 6]);
        gSPMatrix(&xlu[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSetGeometryMode(&xlu[2], 0x400000);
        gSPDisplayList(&xlu[3], object_astr_obj_DL_0022E0);
        POLY_XLU_DISP = &xlu[4];
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
