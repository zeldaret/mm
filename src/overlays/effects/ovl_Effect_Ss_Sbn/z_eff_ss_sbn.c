/*
 * File: z_eff_ss_sbn.c
 * Overlay: ovl_Effect_Ss_Sbn
 * Description: Popped Deku Bubble
 */

#include "z_eff_ss_sbn.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rTwoTexY2Step regs[0]
#define rTwoTexY2 regs[1]
#define rTexIndex regs[2]
#define rAlpha regs[3]
#define rReg4 regs[4]
#define rReg4Step regs[5]
#define rRotAngle regs[6]
#define rScale regs[7]
#define rReg8 regs[8]

#define PARAMS ((EffectSsSbnInitParams*)initParamsx)

u32 EffectSsSbn_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsSbn_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsSbn_DrawSliding(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsSbn_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Sbn_InitVars = {
    EFFECT_SS_SBN,
    EffectSsSbn_Init,
};

TexturePtr sEffectSbnSlidingTextures[] = {
    gEffectSbnSliding1Tex, gEffectSbnSliding2Tex,  gEffectSbnSliding3Tex,  gEffectSbnSliding4Tex,
    gEffectSbnSliding5Tex, gEffectSbnSliding6Tex,  gEffectSbnSliding7Tex,  gEffectSbnSliding8Tex,
    gEffectSbnSliding9Tex, gEffectSbnSliding10Tex, gEffectSbnSliding11Tex, gEffectSbnSliding12Tex,
};

TexturePtr sEffectSbnTextures[] = {
    gEffectSbn1Tex, gEffectSbn2Tex, gEffectSbn3Tex, gEffectSbn4Tex, gEffectSbn5Tex,
};

u32 EffectSsSbn_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsSbnInitParams* initParams = PARAMS;
    CollisionPoly* colPoly;
    MtxF mtx;
    Vec3f normal;
    Vec3f sp40;
    Vec3f sp34;
    f32 angle;
    f32 opposite;

    Math_Vec3f_Copy(&this->pos, &initParams->pos);
    Math_Vec3f_Copy(&this->velocity, &gZeroVec3f);
    Math_Vec3f_Copy(&this->accel, &gZeroVec3f);
    this->flags = 0;
    this->gfx = initParams->colPoly; // Uses the gfx field to store a collisionPoly

    this->rTwoTexY2 = 0;
    this->rTwoTexY2Step = 7;
    this->rTexIndex = 0;
    this->rAlpha = 200;
    this->rReg4 = 250;
    this->rReg4Step = 30;

    this->rScale = randPlusMinusPoint5Scaled(100.0f) + (initParams->scale * 120.0f);
    if (this->rScale < 600) {
        this->rScale = 600;
    } else if (this->rScale > 1500) {
        this->rScale = 1500;
    }

    this->rReg8 = 1000;
    this->rRotAngle = 0;
    this->life = 93;
    this->draw = EffectSsSbn_DrawSliding;
    this->update = EffectSsSbn_Update;

    if (this->gfx != NULL) {
        colPoly = this->gfx;
        func_800C0094(colPoly, this->pos.x, this->pos.y, this->pos.z, &mtx);
        normal.x = COLPOLY_GET_NORMAL(colPoly->normal.x);
        normal.y = COLPOLY_GET_NORMAL(colPoly->normal.y);
        normal.z = COLPOLY_GET_NORMAL(colPoly->normal.z);
        if ((normal.y > 0.95f) || (normal.y < -0.95f)) {
            this->draw = EffectSsSbn_Draw;
            return 1;
        }
        if (normal.y > 0.05f) {
            sp40.x = normal.x * 10.0f;
            sp40.y = (-(SQ(normal.x) + SQ(normal.z)) * 10.0f) / normal.y;
            sp40.z = normal.z * 10.0f;
        } else if (normal.y < -0.05f) {
            sp40.x = -normal.x * 10.0f;
            sp40.y = (-(SQ(normal.x) + SQ(normal.z)) * 10.0f) / -normal.y;
            sp40.z = -normal.z * 10.0f;
        } else {
            sp40.x = 0.0f;
            sp40.y = -10.0f;
            sp40.z = 0.0f;
        }
        sp34.x = -mtx.mf[2][0] * 10.0f;
        sp34.y = -mtx.mf[2][1] * 10.0f;
        sp34.z = -mtx.mf[2][2] * 10.0f;
        Math3D_AngleBetweenVectors(&sp40, &sp34, &angle);

        opposite = (SQ(angle) >= 1.0f) ? 0.0f : sqrtf(1.0f - SQ(angle));
        if (((mtx.mf[0][0] * sp40.x) + (mtx.mf[0][1] * sp40.y) + (mtx.mf[0][2] * sp40.z)) < 0.0f) {
            this->rRotAngle = Math_FAtan2F(angle, opposite);
        } else {
            this->rRotAngle = -Math_FAtan2F(angle, opposite);
        }
    }
    return 1;
}

void EffectSsSbn_DrawSliding(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    MtxF mtx;
    f32 scale = this->rScale * 0.001f;
    s32 pad;

    func_800C0094(this->gfx, this->pos.x, this->pos.y, this->pos.z, &mtx);
    SkinMatrix_MulYRotation(&mtx, this->rRotAngle);
    Matrix_InsertMatrix(&mtx, MTXMODE_NEW);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    Matrix_Scale(0.05f, 0.05f, 0.05f, MTXMODE_APPLY);

    OPEN_DISPS(gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(gfxCtx);
    gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_DECAL2);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->rAlpha);

    if (this->rTexIndex < ARRAY_COUNT(sEffectSbnSlidingTextures)) {
        {
            TexturePtr tex = sEffectSbnSlidingTextures[this->regs[2]];

            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(tex));
        }
        this->rTexIndex++;
        this->rTwoTexY2 += this->rTwoTexY2Step;
    } else {
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gEffectSbnSliding12Tex));
        if ((this->rTwoTexY2Step >= 2) && ((globalCtx->state.frames % 2) == 0)) {
            this->rTwoTexY2Step--;
        }
        this->rTwoTexY2 += this->rTwoTexY2Step;
    }
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, this->rTwoTexY2, 0x20, 0x20));
    gSPDisplayList(POLY_XLU_DISP++, gEffectSbnSlidingDL);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsSbn_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    MtxF mtx;
    f32 scale = this->rScale * 0.001f;

    func_800C0094(this->gfx, this->pos.x, this->pos.y, this->pos.z, &mtx);
    SkinMatrix_MulYRotation(&mtx, this->rRotAngle);
    Matrix_InsertMatrix(&mtx, MTXMODE_NEW);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    Matrix_Scale(0.05f, 0.05f, 0.05f, MTXMODE_APPLY);

    OPEN_DISPS(gfxCtx);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(gfxCtx);
    gDPSetRenderMode(POLY_XLU_DISP++, G_RM_FOG_SHADE_A, G_RM_ZB_XLU_DECAL2);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->rAlpha);

    if (this->rTexIndex < ARRAY_COUNT(sEffectSbnTextures)) {
        {
            TexturePtr tex = sEffectSbnTextures[this->rTexIndex];

            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(tex));
        }
        this->rTexIndex++;
    } else {
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gEffectSbn5Tex));
    }
    gSPDisplayList(POLY_XLU_DISP++, gEffectSbnDL);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsSbn_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    if (this->life < 10) {
        this->rAlpha -= 20;
    } else if (this->life >= 45) {
        if (this->life < 85) {
            this->rReg8 += 12;
            this->rReg4 -= this->rReg4Step;
        } else {
            this->rReg8 = 1000;
        }
    }
}
