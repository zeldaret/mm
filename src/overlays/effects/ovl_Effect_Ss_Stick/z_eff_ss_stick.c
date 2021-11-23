/*
 * File: z_eff_ss_stick.c
 * Overlay: ovl_Effect_Ss_Stick
 * Description: Deku Stick
 */

#include "z_eff_ss_stick.h"

#define PARAMS ((EffectSsStickInitParams*)initParamsx)

u32 EffectSsStick_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsStick_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsStick_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Stick_InitVars = {
    EFFECT_SS_STICK,
    EffectSsStick_Init,
};

u32 EffectSsStick_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsStickInitParams* params = PARAMS;
    Vec3f pos;

    this->regs[0] = Object_GetIndex(&globalCtx->objectCtx, GAMEPLAY_KEEP);
    pos = params->pos;
    this->pos = pos;
    this->vec = pos;
    this->regs[1] = params->yaw;
    this->velocity.x = Math_SinS(params->yaw) * 6.0f;
    this->velocity.z = Math_CosS(params->yaw) * 6.0f;
    this->life = 20;
    this->draw = EffectSsStick_Draw;
    this->update = EffectSsStick_Update;
    this->velocity.y = 26.0f;
    this->accel.y = -4.0f;
    return 1;
}

void EffectSsStick_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_Scale(0.01f, 0.0025f, 0.01f, MTXMODE_APPLY);
    Matrix_InsertRotation(0, this->regs[1], 0, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->regs[0]].segment);
    gSPSegment(POLY_OPA_DISP++, 0x0C, D_801C0850);
    gSPDisplayList(POLY_OPA_DISP++, D_040032B0);
    CLOSE_DISPS(gfxCtx);
}

void EffectSsStick_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
}
