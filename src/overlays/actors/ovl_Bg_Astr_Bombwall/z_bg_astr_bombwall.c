/*
 * File: z_bg_astr_bombwall.c
 * Overlay: ovl_Bg_Astr_Bombwall
 * Description: Astral Observatory - Bombable Wall
 */

#include "z_bg_astr_bombwall.h"

#define FLAGS 0x00000000

#define THIS ((BgAstrBombwall*)thisx)

void BgAstrBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C0A378(BgAstrBombwall* thisx);
void func_80C0A38C(BgAstrBombwall* thisx, GlobalContext* globalCtx);
void func_80C0A400(BgAstrBombwall* thisx, GlobalContext* globalCtx);
void func_80C0A418(BgAstrBombwall* thisx, GlobalContext* globalCtx);
void func_80C0A458(BgAstrBombwall* thisx, GlobalContext* globalCtx);
void func_80C0A120(BgAstrBombwall* thisx, GlobalContext* globalCtx);
void func_80C0A4BC(BgAstrBombwall* thisx, GlobalContext* globalCtx);
void func_80C09ED0(ColliderTrisInit* arg0, Vec3f* arg1, Vec3s* arg2, ColliderTris* arg3);

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

extern Gfx D_06002178;
extern CollisionHeader D_06002498;
extern Gfx D_06002380[];
extern Gfx D_060022E0[];

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
    ColliderTris* temp_a1;
    BgAstrBombwall* this = THIS;
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init((DynaPolyActor*)&this->dyna.actor, 1);
    DynaPolyActor_LoadMesh(globalCtx, (DynaPolyActor*)&this->dyna.actor, &D_06002498);
    temp_a1 = &this->unk160;
    Collider_InitTris(globalCtx, temp_a1);
    if (Flags_GetSwitch(globalCtx, this->dyna.actor.params & 0x7F) != 0) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    this->dyna.actor.flags |= 0x10000000;
    if (Collider_SetTris(globalCtx, temp_a1, &this->dyna.actor, &sTrisInit, &this->unk180) == 0) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    func_80C09ED0(&sTrisInit, &this->dyna.actor.world.pos, &this->dyna.actor.shape.rot, temp_a1);
    SubS_FillCutscenesList(&this->dyna.actor, &this->unk238, 1);
    func_80C0A378(this);
}

void BgAstrBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgAstrBombwall* this = THIS;
    
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80C0A120(BgAstrBombwall* thisx, GlobalContext* globalCtx) {
    s32 var_s1;
    Vec3f spC8;
    Vec3f spBC;
    s16 var_v0;
    Vec3f spAC;
    f32 temp_fv0;
    
    Matrix_RotateYS(thisx->dyna.actor.shape.rot.y, MTXMODE_NEW);
    for (var_s1 = 0; var_s1 < 0x1E; var_s1++) {
        spC8.x = Rand_Centered() * 140.0f;
        spC8.y = Rand_ZeroOne() * 200.0f;
        spC8.z = 0.0f;
        Matrix_MultVec3f(&spC8, &spBC);
        Math_Vec3f_Sum(&thisx->dyna.actor.world.pos, &spBC, &spBC);
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
                             &D_06002178);
    }
}

void func_80C0A378(BgAstrBombwall* thisx) {
    thisx->actionFunc = func_80C0A38C;
}

void func_80C0A38C(BgAstrBombwall* thisx, GlobalContext* globalCtx) {
    u8 temp_v0;

    temp_v0 = thisx->unk160.base.acFlags;
    if ((temp_v0 & 2) != 0) {
        thisx->unk160.base.acFlags = temp_v0 & 0xFFFD;
        Flags_SetSwitch(globalCtx, thisx->dyna.actor.params & 0x7F);
        func_80C0A400(thisx, globalCtx);
        return;
    }
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &thisx->unk160.base);
}

void func_80C0A400(BgAstrBombwall* thisx, GlobalContext* globalCtx) {
    thisx->actionFunc = func_80C0A418;
}

void func_80C0A418(BgAstrBombwall* thisx, GlobalContext* globalCtx) {
    if (SubS_StartActorCutscene(&thisx->dyna.actor, thisx->unk238, -1, 0) != 0) {
        func_80C0A458(thisx, globalCtx);
    }
}

void func_80C0A458(BgAstrBombwall* thisx, GlobalContext* globalCtx) {
    func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, thisx->dyna.bgId);
    thisx->dyna.actor.draw = NULL;
    func_80C0A120(thisx, globalCtx);
    Actor_PlaySfxAtPos(&thisx->dyna.actor, NA_SE_EV_WALL_BROKEN);
    thisx->actionFunc = func_80C0A4BC;
}

void func_80C0A4BC(BgAstrBombwall* thisx, GlobalContext* globalCtx) {
}

void BgAstrBombwall_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgAstrBombwall* this = THIS;
    
    this->actionFunc(this, globalCtx);
}

void BgAstrBombwall_Draw(Actor* thisx, GlobalContext* globalCtx) {
    {
        Gfx* opa;
        OPEN_DISPS(globalCtx->state.gfxCtx);
        opa = POLY_OPA_DISP;
        gSPDisplayList(&opa[0], &sSetupDL[25 * 6]);
        gSPMatrix(&opa[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSetGeometryMode(&opa[2], 0x400000);
        gSPDisplayList(&opa[3], D_06002380);
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
        gSPDisplayList(&xlu[3], D_060022E0);
        POLY_XLU_DISP = &xlu[4];
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
