/*
 * File: z_eff_ss_sbn.c
 * Overlay: ovl_Effect_Ss_Sbn
 * Description:
 */

#include "z_eff_ss_sbn.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define PARAMS ((EffectSsSbnInitParams*)initParamsx)

u32 EffectSsSbn_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsSbn_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_80AC8ECC(GlobalContext* globalCtx, u32 index, EffectSs* this);
void func_80AC9164(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Sbn_InitVars = {
    EFFECT_SS_SBN,
    EffectSsSbn_Init,
};

TexturePtr D_80AC93B8[] = {
    gameplay_keep_Tex_071300, gameplay_keep_Tex_071700, gameplay_keep_Tex_071B00, gameplay_keep_Tex_071F00,
    gameplay_keep_Tex_072300, gameplay_keep_Tex_072700, gameplay_keep_Tex_072B00, gameplay_keep_Tex_072F00,
    gameplay_keep_Tex_073300, gameplay_keep_Tex_073700, gameplay_keep_Tex_073B00, gameplay_keep_Tex_073F00,
};

TexturePtr D_80AC93E8[] = {
    gameplay_keep_Tex_074400, gameplay_keep_Tex_074800, gameplay_keep_Tex_074C00,
    gameplay_keep_Tex_075000, gameplay_keep_Tex_075400,
};

u32 EffectSsSbn_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsSbnInitParams* initParams = PARAMS;
    CollisionPoly* sp98;
    MtxF sp58;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    f32 sp30;
    f32 phi_f14;

    Math_Vec3f_Copy(&this->pos, &initParams->unk_00);
    Math_Vec3f_Copy(&this->velocity, &gZeroVec3f);
    Math_Vec3f_Copy(&this->accel, &gZeroVec3f);
    this->flags = 0;
    this->gfx = initParams->unk_0C;

    this->regs[1] = 0;
    this->regs[0] = 7;
    this->regs[2] = 0;
    this->regs[3] = 200;
    this->regs[4] = 250;
    this->regs[5] = 30;

    this->regs[7] = randPlusMinusPoint5Scaled(100.0f) + (initParams->unk_10 * 120.0f);
    if (this->regs[7] < 600) {
        this->regs[7] = 600;
    } else if (this->regs[7] > 1500) {
        this->regs[7] = 1500;
    }

    this->regs[8] = 1000;
    this->regs[6] = 0;
    this->life = 93;
    this->draw = func_80AC8ECC;
    this->update = EffectSsSbn_Update;

    if (this->gfx != NULL) {
        sp98 = this->gfx;
        func_800C0094(sp98, this->pos.x, this->pos.y, this->pos.z, &sp58);
        sp4C.x = COLPOLY_GET_NORMAL(sp98->normal.x);
        sp4C.y = COLPOLY_GET_NORMAL(sp98->normal.y);
        sp4C.z = COLPOLY_GET_NORMAL(sp98->normal.z);
        if ((sp4C.y > 0.95f) || (sp4C.y < -0.95f)) {
            this->draw = func_80AC9164;
            return 1;
        }
        if (sp4C.y > 0.05f) {
            sp40.x = sp4C.x * 10.0f;
            sp40.y = (-(SQ(sp4C.x) + SQ(sp4C.z)) * 10.0f) / sp4C.y;
            sp40.z = sp4C.z * 10.0f;
        } else if (sp4C.y < -0.05f) {
            sp40.x = -sp4C.x * 10.0f;
            sp40.y = (-(SQ(sp4C.x) + SQ(sp4C.z)) * 10.0f) / -sp4C.y;
            sp40.z = -sp4C.z * 10.0f;
        } else {
            sp40.x = 0.0f;
            sp40.y = -10.0f;
            sp40.z = 0.0f;
        }
        sp34.x = -sp58.mf[2][0] * 10.0f;
        sp34.y = -sp58.mf[2][1] * 10.0f;
        sp34.z = -sp58.mf[2][2] * 10.0f;
        Math3D_AngleBetweenVectors(&sp40, &sp34, &sp30);

        phi_f14 = (SQ(sp30) >= 1.0f) ? 0.0f : sqrtf(1.0f - SQ(sp30));
        if (((sp58.mf[0][0] * sp40.x) + (sp58.mf[0][1] * sp40.y) + (sp58.mf[0][2] * sp40.z)) < 0.0f) {
            this->regs[6] = Math_FAtan2F(sp30, phi_f14);
        } else {
            this->regs[6] = -Math_FAtan2F(sp30, phi_f14);
        }
    }
    return 1;
}

void func_80AC8ECC(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    MtxF sp74;
    f32 sp70 = this->regs[7] * 0.001f;
    s32 pad;

    func_800C0094(this->gfx, this->pos.x, this->pos.y, this->pos.z, &sp74);
    SkinMatrix_MulYRotation(&sp74, this->regs[6]);
    Matrix_InsertMatrix(&sp74, MTXMODE_NEW);
    Matrix_Scale(sp70, sp70, sp70, MTXMODE_APPLY);
    Matrix_Scale(0.05f, 0.05f, 0.05f, MTXMODE_APPLY);

    OPEN_DISPS(gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(gfxCtx);
    gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_DECAL2);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->regs[3]);

    if (this->regs[2] < 12) {
        {
            TexturePtr tex = D_80AC93B8[this->regs[2]];

            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(tex));
        }
        this->regs[2]++;
        this->regs[1] += this->regs[0];
    } else {
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_073F00));
        if ((this->regs[0] >= 2) && ((globalCtx->state.frames % 2) == 0)) {
            this->regs[0]--;
        }
        this->regs[1] += this->regs[0];
    }
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, this->regs[1], 0x20, 0x20));
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_071230);

    CLOSE_DISPS(gfxCtx);
}

void func_80AC9164(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    MtxF sp54;
    f32 sp50 = this->regs[7] * 0.001f;

    func_800C0094(this->gfx, this->pos.x, this->pos.y, this->pos.z, &sp54);
    SkinMatrix_MulYRotation(&sp54, this->regs[6]);
    Matrix_InsertMatrix(&sp54, MTXMODE_NEW);
    Matrix_Scale(sp50, sp50, sp50, MTXMODE_APPLY);
    Matrix_Scale(0.05f, 0.05f, 0.05f, MTXMODE_APPLY);

    OPEN_DISPS(gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(gfxCtx);
    gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_DECAL2);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->regs[3]);

    if (this->regs[2] < 5) {
        {
            TexturePtr tex = D_80AC93E8[this->regs[2]];

            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(tex));
        }
        this->regs[2]++;
    } else {
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_075400));
    }
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_074330);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsSbn_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    if (this->life < 10) {
        this->regs[3] += -20;
    } else if (this->life >= 45) {
        if (this->life < 85) {
            this->regs[8] += 12;
            this->regs[4] -= this->regs[5];
        } else {
            this->regs[8] = 1000;
        }
    }
}
