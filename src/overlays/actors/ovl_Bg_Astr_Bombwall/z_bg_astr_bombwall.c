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

void BgAstrBombwall_InitCollider(ColliderTrisInit* init, Vec3f* pos, Vec3s* rot, ColliderTris* collider) {
    s32 i;
    s32 j;
    Vec3f sp54[3];

    Matrix_RotateYS(rot->y, MTXMODE_NEW);
    Matrix_RotateXS(rot->x, MTXMODE_APPLY);
    Matrix_RotateZS(rot->z, MTXMODE_APPLY);

    for (i = 0; i < init->count; i++) {
        for (j = 0; j < 3; j++) {                                          // https://decomp.me/scratch/JrEnl
            Matrix_MultVec3f(&(init->elements + i)->dim.vtx[j], &sp54[j]); //! FAKE MATCH:
            Math_Vec3f_Sum(&sp54[j], pos, &sp54[j]);
        }
        Collider_SetTrisVertices(collider, i, &sp54[0], &sp54[1], &sp54[2]);
    }
}

void BgAstrBombwall_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgAstrBombwall* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_astr_obj_Colheader_002498);
    Collider_InitTris(globalCtx, &this->collider);
    if (Flags_GetSwitch(globalCtx, BGASTRBOMBWALL_GET_SWITCHFLAG(thisx))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    this->dyna.actor.flags |= ACTOR_FLAG_10000000;
    if (!Collider_SetTris(globalCtx, &this->collider, &this->dyna.actor, &sTrisInit, this->colliderElements)) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    BgAstrBombwall_InitCollider(&sTrisInit, &this->dyna.actor.world.pos, &this->dyna.actor.shape.rot, &this->collider);
    SubS_FillCutscenesList(&this->dyna.actor, this->cutscenes, ARRAY_COUNT(this->cutscenes));
    func_80C0A378(this);
}

void BgAstrBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgAstrBombwall* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80C0A120(BgAstrBombwall* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f vec;
    Vec3f pos;
    s16 var_v0;
    Vec3f velocity;
    f32 rand;

    Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    for (i = 0; i < 30; i++) {
        vec.x = Rand_Centered() * 140.0f;
        vec.y = Rand_ZeroOne() * 200.0f;
        vec.z = 0.0f;
        Matrix_MultVec3f(&vec, &pos);
        Math_Vec3f_Sum(&this->dyna.actor.world.pos, &pos, &pos);
        func_800BBFB0(globalCtx, &pos, 50.0f, 2, Rand_ZeroOne() * 120.0f + 20.0f, Rand_ZeroOne() * 240.0f + 20.0f, 0);
        velocity.x = Rand_ZeroOne() * 2.5f;
        velocity.y = (Rand_ZeroOne() * 2.5f) + 1.0f;
        velocity.z = Rand_ZeroOne() * 2.5f;
        rand = Rand_ZeroOne();

        if (rand < 0.2f) {
            var_v0 = 0x60;
        } else if (rand < 0.6f) {
            var_v0 = 0x40;
        } else {
            var_v0 = 0x20;
        }
        EffectSsKakera_Spawn(globalCtx, &pos, &velocity, &pos, -260, var_v0, 20, 0, 0, 10, 0, 0, 50, -1,
                             OBJECT_ASTR_OBJ, object_astr_obj_DL_002178);
    }
}

void func_80C0A378(BgAstrBombwall* this) {
    this->actionFunc = func_80C0A38C;
}

void func_80C0A38C(BgAstrBombwall* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Flags_SetSwitch(globalCtx, BGASTRBOMBWALL_GET_SWITCHFLAG(&this->dyna.actor));
        func_80C0A400(this, globalCtx);
    } else {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80C0A400(BgAstrBombwall* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80C0A418;
}

void func_80C0A418(BgAstrBombwall* this, GlobalContext* globalCtx) {
    if (SubS_StartActorCutscene(&this->dyna.actor, this->cutscenes[0], -1, SUBS_CUTSCENE_SET_UNK_LINK_FIELDS)) {
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
        gSPSetGeometryMode(&opa[2], G_LIGHTING_POSITIONAL);
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
        gSPSetGeometryMode(&xlu[2], G_LIGHTING_POSITIONAL);
        gSPDisplayList(&xlu[3], object_astr_obj_DL_0022E0);
        POLY_XLU_DISP = &xlu[4];
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
