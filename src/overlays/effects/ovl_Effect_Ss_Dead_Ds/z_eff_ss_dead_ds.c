/*
 * File: z_eff_ss_dead_ds.c
 * Overlay: ovl_Effect_Ss_Dead_Ds
 * Description:
 */

#include "z_eff_ss_dead_ds.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rScale regs[0]
#define rTimer regs[1]
#define rRoll regs[2]
#define rPitch regs[3]
#define rYaw regs[4]
#define rAlpha regs[5]
#define rScaleStep regs[9]
#define rAlphaStep regs[10]
#define rHalfOfLife regs[11]

#define PARAMS ((EffectSsDeadDsInitParams*)initParamsx)

u32 EffectSsDeadDs_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDeadDs_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDeadDs_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Dead_Ds_InitVars = {
    EFFECT_SS_DEAD_DS,
    EffectSsDeadDs_Init,
};

u32 EffectSsDeadDs_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsDeadDsInitParams* initParams = (EffectSsDeadDsInitParams*)initParamsx;

    this->pos = initParams->pos;
    this->velocity = initParams->velocity;
    this->accel = initParams->accel;
    this->life = initParams->life;
    this->rScaleStep = initParams->scaleStep;
    this->rHalfOfLife = initParams->life / 2;
    this->rAlphaStep = initParams->alpha / this->rHalfOfLife;
    this->draw = EffectSsDeadDs_Draw;
    this->update = EffectSsDeadDs_Update;
    this->rScale = initParams->scale;
    this->rAlpha = initParams->alpha;
    this->rTimer = 0;

    return 1;
}

void EffectSsDeadDs_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 pad;
    f32 scale;
    s32 pad2[2];
    MtxF mf;
    f32 yIntersect;
    Vec3f pos;
    CollisionPoly* floorPoly;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    scale = this->rScale * 0.01f;
    func_8012C974(globalCtx->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, this->rAlpha);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 0);
    pos = this->pos;

    if (this->rTimer == 0) {
        Vec3s rpy;
        Vec3f sp44;

        sp44.x = pos.x - this->velocity.x;
        sp44.y = pos.y - this->velocity.y;
        sp44.z = pos.z - this->velocity.z;

        if (BgCheck_EntitySphVsWall1(&globalCtx->colCtx, &this->pos, &pos, &sp44, 1.5f, &floorPoly, 1.0f)) {
            func_800C0094(floorPoly, this->pos.x, this->pos.y, this->pos.z, &mf);
            Matrix_SetCurrentState(&mf);
        } else {
            pos.y++;
            yIntersect = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &floorPoly, &pos);

            if (floorPoly != NULL) {
                func_800C0094(floorPoly, this->pos.x, yIntersect + 1.5f, this->pos.z, &mf);
                Matrix_SetCurrentState(&mf);
            } else {
                Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
                Matrix_CopyCurrentState(&mf);
            }
        }

        func_801822C4(&mf, &rpy, 0);
        this->rRoll = rpy.x;
        this->rPitch = rpy.y;
        this->rYaw = rpy.z;
        this->pos.y = mf.wy;
        this->rTimer++;
    }

    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_InsertRotation(this->rRoll, this->rPitch, this->rYaw, MTXMODE_APPLY);
    Matrix_RotateStateAroundXAxis(1.57f);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetCombineLERP(POLY_XLU_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);
    gSPDisplayList(POLY_XLU_DISP++, gLensFlareCircleDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EffectSsDeadDs_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    if (this->life < this->rHalfOfLife) {

        this->rScale += this->rScaleStep;
        if (this->rScale < 0) {
            this->rScale = 0;
        }

        this->rAlpha -= this->rAlphaStep;
        if (this->rAlpha < 0) {
            this->rAlpha = 0;
        }
    }
}
