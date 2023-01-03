/*
 * File: z_en_honotrap.c
 * Overlay: ovl_En_Honotrap
 * Description: Eye switch that shoots fire
 */

#include "z_en_honotrap.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnHonotrap*)thisx)

void EnHonotrap_Init(Actor* thisx, PlayState* play);
void EnHonotrap_Destroy(Actor* thisx, PlayState* play);
void EnHonotrap_Update(Actor* thisx, PlayState* play);
void EnHonotrap_Draw(Actor* thisx, PlayState* play);

void func_8092EBDC(EnHonotrap* this, PlayState* play);
void func_8092ECF0(EnHonotrap* this, PlayState* play);
void func_8092EDD8(EnHonotrap* this, PlayState* play);
void func_8092EE1C(EnHonotrap* this, PlayState* play);
void func_8092EE90(EnHonotrap* this, PlayState* play);
void func_8092EF98(EnHonotrap* this, PlayState* play);
void func_8092F074(EnHonotrap* this, PlayState* play);
void func_8092F0B8(EnHonotrap* this, PlayState* play);
void func_8092F10C(EnHonotrap* this, PlayState* play);
void func_8092F208(EnHonotrap* this, PlayState* play);
void func_8092F3D8(EnHonotrap* this, PlayState* play);
void func_8092F5EC(EnHonotrap* this, PlayState* play);
void func_8092F7BC(EnHonotrap* this, PlayState* play);
void func_8092F878(EnHonotrap* this, PlayState* play);

void func_8092E638(EnHonotrap* this, PlayState* play); // d
void func_8092E840(EnHonotrap* this, PlayState* play); // d
void func_8092E988(EnHonotrap* this, PlayState* play); // d
void func_8092FE44(Actor* thisx, PlayState* play);
void func_8092FEFC(Actor* thisx, PlayState* play);
void func_80930030(Actor* thisx, PlayState* play);
void func_80930190(Actor* thisx, PlayState* play);

void func_8092EBC0(EnHonotrap* this);
void func_8092EE68(EnHonotrap* this);
void func_8092F0F8(EnHonotrap* this);
void func_8092F854(EnHonotrap* this);

#if 0
ActorInit En_Honotrap_InitVars = {
    ACTOR_EN_HONOTRAP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(EnHonotrap),
    (ActorFunc)EnHonotrap_Init,
    (ActorFunc)EnHonotrap_Destroy,
    (ActorFunc)EnHonotrap_Update,
    (ActorFunc)EnHonotrap_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80930424[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { -23.0f, 0.0f, 8.5f }, { 0.0f, -23.0f, 8.5f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { 0.0f, -23.0f, 8.5f }, { 23.0f, 0.0f, 8.5f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_8093049C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    ARRAY_COUNT(sTrisElementsInit), D_80930424, // sTrisElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809304AC = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x04 }, { 0x00100000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 10, 25, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_809304D8 = { 0, 9, 23, 1 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809304E0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

#endif
extern Gfx* D_809303F0[4];
extern s32 D_80930400;
extern ColliderTrisElementInit D_80930424[2];
extern ColliderTrisInit D_8093049C;
extern ColliderCylinderInit D_809304AC;
extern CollisionCheckInfoInit D_809304D8;
extern InitChainEntry D_809304E0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092E5A4.s")

// EnHonotrap_InitEye
void func_8092E638(EnHonotrap* this, PlayState* play) {
    s32 i;
    s32 j;
    s32 k;
    f32 sin;
    f32 cos;
    Vec3f sp70[3];
    Vec3f* vtx;

    sin = Math_SinS(this->actor.home.rot.y);
    cos = Math_CosS(this->actor.home.rot.y);
    Actor_SetScale(&this->actor, 0.1f);

    if (D_80930400 != 0) {
        D_80930400 = 0;
        for (k = 0; k < 4; k++) {
            D_809303F0[k] = Lib_SegmentedToVirtual(D_809303F0[k]);
        }
    }

    Collider_InitTris(play, &this->collider.tris);
    Collider_SetTris(play, &this->collider.tris, &this->actor, &D_8093049C, this->collider.elements);

    for (i = 0; i < 2; i++) {
        for (j = 0, vtx = sp70; j < 3; j++, vtx++) {
            Vec3f* test = &D_8093049C.elements[i].dim.vtx[j];

            vtx->x = (test->z * sin) + (test->x * cos);
            vtx->y = test->y;
            vtx->z = (test->z * cos) - (test->x * sin);

            Math_Vec3f_Sum(vtx, &this->actor.world.pos, vtx);
        }
        Collider_SetTrisVertices(&this->collider.tris, i, &sp70[0], &sp70[1], &sp70[2]);
    }
    Actor_SetFocus(&this->actor, 0.0f);
    if (this->actor.params == 0) {
        func_8092EBC0(this);
    } else {
        func_8092EE68(this);
    }
}

// EnHonotrap_InitFlame
void func_8092E840(EnHonotrap* this, PlayState* play) {
    s32 pad[2];
    s32 params;

    params = this->actor.params;
    Actor_SetScale(&this->actor, 0.0001f);
    Collider_InitCylinder(play, &this->collider.cyl);
    Collider_SetCylinder(play, &this->collider.cyl, &this->actor, &D_809304AC);
    Collider_UpdateCylinder(&this->actor, &this->collider.cyl);
    this->actor.terminalVelocity = -1.0f;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_809304D8);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    this->actor.shape.shadowAlpha = 0x80;
    this->unk228 = GET_PLAYER(play)->actor.world.pos;
    this->unk228.y += 10.0f;
    this->unk23A = Rand_ZeroOne() * 511.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FLAME_IGNITION);
    if (params == 2) {
        this->actor.room = -1;
        this->collider.cyl.dim.radius = 12;
        this->collider.cyl.dim.height = 30;
        this->actor.shape.yOffset = -1000.0f;
    }
    func_8092F0F8(this);
}

void func_8092E988(EnHonotrap* this, PlayState* play) {
    EnHonotrap23C* var_s2;
    s32 var_s0;
    s32 i;

    Actor_SetScale(&this->actor, 0.0001f);
    Collider_InitCylinder(play, &this->collider.cyl);
    Collider_SetCylinder(play, &this->collider.cyl, &this->actor, &D_809304AC);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_809304D8);

    var_s0 = Rand_ZeroOne() * 511.0f;
    var_s2 = &this->unk23C;
    for (i = 0; i < 6; i++) {
        var_s2->unkC[i].unk_10 = var_s0;
        var_s0 += (s32)Rand_ZeroFloat(300.0f) + 0x64;
        var_s0 &= 0x1FF;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_FLAME_IGNITION);
    func_8092F854(this);
}

void EnHonotrap_Init(Actor* thisx, PlayState* play) {
    s32 params;
    EnHonotrap* this = (EnHonotrap*)thisx;

    params = this->actor.params;
    Actor_ProcessInitChain(&this->actor, D_809304E0);
    if ((params == 0) || (params == 3)) {
        func_8092E638(this, play);
    } else if (params == 4) {
        func_8092E988(this, play);
        this->actor.update = func_8092FEFC;
        this->actor.draw = func_80930190;
        this->actor.uncullZoneScale = 500.0f;
        this->actor.uncullZoneDownward = 500.0f;
    } else {
        func_8092E840(this, play);
        this->actor.update = func_8092FE44;
        this->actor.draw = func_80930030;
    }
}

void EnHonotrap_Destroy(Actor* thisx, PlayState* play) {
    s16 params;
    EnHonotrap* this = (EnHonotrap*)thisx;

    params = this->actor.params;
    if ((params == 0) || (params == 3)) {
        Collider_DestroyTris(play, &this->collider.tris);
    } else {
        Collider_DestroyCylinder(play, &this->collider.cyl);
    }
}

void func_8092EBC0(EnHonotrap* this) {
    this->actionFunc = func_8092EBDC;
    this->unk222 = 3;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092ECF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EDC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EDD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE1C.s")

void func_8092EE68(EnHonotrap* this) {
    this->unk222 = 3;
    this->unk220 = 0x50;
    this->unk224 = 0;
    this->actionFunc = func_8092EE90;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EE90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092EF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F0F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F10C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F3D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F7A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F7BC.s")

void func_8092F854(EnHonotrap* this) {
    this->actionFunc = func_8092F878;
    this->unk220 = 0x50;
    this->unk23C.unk_08 = 0.0f;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Update.s")

void func_8092FE44(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;

    if (this->unk220 > 0) {
        this->unk220--;
    }
    this->unk2C0 = 0; // + 23C + 0x10 + 0x64 + 0x10 = s8
    this->unk238 += 0x640;
    if (this->actor.params != 4) {
        this->actor.shape.yOffset = Math_SinS(this->unk238) * 1000.0f + 600.0f;
    }
    Actor_SetFocus(&this->actor, 5.0f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
    this->actionFunc(this, play);
    this->unk23A -= 0x14;
    this->unk23A &= 0x1FF;
}

void func_8092FEFC(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;
    Actor* temp_v0;

    temp_v0 = this->actor.parent;
    if ((temp_v0 != NULL) && (temp_v0->update == NULL)) {
        this->actor.parent = NULL;
    }
    if (this->unk220 > 0) {
        this->unk220--;
    }
    this->unk238 += 0x640;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
    this->actionFunc(this, play);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/EnHonotrap_Draw.s")

void func_80930030(Actor* thisx, PlayState* play) {
    s32 pad;
    EnHonotrap* this = (EnHonotrap*)thisx;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0, this->unk23A, 32, 128));
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 200, 0, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
    Matrix_RotateYS(Camera_GetCamDirYaw(play->cameraPtrs[play->activeCamId]) + 0x8000, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gEffFire1DL);
    CLOSE_DISPS(play->state.gfxCtx);
}

#ifdef NON_MATCHING
void func_80930190(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;
    Vec3s spB8;
    EnHonotrapArr* temp_s0;
    EnHonotrap23C* var_s3;
    s32 i; // s4

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 200, 0, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
    func_800DFC90(&spB8, play->cameraPtrs[play->activeCamId]);
    spB8.y += 0x8000;
    var_s3 = &this->unk23C;
    for (i = 0; i < 6; i++) {
        temp_s0 = &var_s3->unkC[i];
        if (temp_s0->unk12 != 0) {
            gSPSegment(
                POLY_XLU_DISP++, 0x08,
                Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, temp_s0->unk_10, 0x20, 0x80));
            Matrix_SetTranslateRotateYXZ(temp_s0->unk0.x, temp_s0->unk0.y - (4000.0f * temp_s0->unkC), temp_s0->unk0.z,
                                         &spB8);
            // temp_fa1 = temp_s0->unkC;
            Matrix_Scale(((fabsf(Math_SinS((s16)(spB8.y - this->actor.shape.rot.y) >> 1)) * 0.2f) + 1.7f) *
                             temp_s0->unkC,
                         temp_s0->unkC, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gEffFire1DL);
        }
    }
    CLOSE_DISPS(play->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_80930190.s")
#endif
