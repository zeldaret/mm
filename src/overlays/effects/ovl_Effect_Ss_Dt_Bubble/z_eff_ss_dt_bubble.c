/*
 * File: z_eff_ss_dt_bubble.c
 * Overlay: ovl_Effect_Ss_Dt_Bubble
 * Description:
 */

#include "z_eff_ss_dt_bubble.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rPrimColorR regs[0]
#define rPrimColorG regs[1]
#define rPrimColorB regs[2]
#define rPrimColorA regs[3]
#define rEnvColorR regs[4]
#define rEnvColorG regs[5]
#define rEnvColorB regs[6]
#define rEnvColorA regs[7]
#define rRandXZ regs[8]
#define rScale regs[9]
#define rLifespan regs[10]

#define PARAMS ((EffectSsDtBubbleInitParams*)initParamsx)

u32 EffectSsDtBubble_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDtBubble_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDtBubble_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

static Color_RGBA8 sPrimColors[] = {
    { 255, 255, 100, 255 },
    { 150, 255, 255, 255 },
    { 100, 255, 255, 255 },
    { 255, 255, 255, 255 },
};

static Color_RGBA8 sEnvColors[] = {
    { 170, 0, 0, 255 },
    { 0, 100, 0, 255 },
    { 0, 0, 255, 255 },
    { 150, 150, 150, 0 },
};

const EffectSsInit Effect_Ss_Dt_Bubble_InitVars = {
    EFFECT_SS_DT_BUBBLE,
    EffectSsDtBubble_Init,
};

u32 EffectSsDtBubble_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsDtBubbleInitParams* initParams = (EffectSsDtBubbleInitParams*)initParamsx;

    {
        TexturePtr tex = (Rand_ZeroOne() < 0.5f) ? gameplay_keep_Tex_091BE0 : gameplay_keep_Tex_091CE0;

        this->gfx = VIRTUAL_TO_PHYSICAL(SEGMENTED_TO_VIRTUAL(tex));
    }

    Math_Vec3f_Copy(&this->pos, &initParams->pos);
    Math_Vec3f_Copy(&this->velocity, &initParams->velocity);
    Math_Vec3f_Copy(&this->accel, &initParams->accel);
    this->life = initParams->life;

    if (!initParams->customColor) {
        this->rPrimColorR = sPrimColors[initParams->colorProfile].r;
        this->rPrimColorG = sPrimColors[initParams->colorProfile].g;
        this->rPrimColorB = sPrimColors[initParams->colorProfile].b;
        this->rPrimColorA = sPrimColors[initParams->colorProfile].a;
        this->rEnvColorR = sEnvColors[initParams->colorProfile].r;
        this->rEnvColorG = sEnvColors[initParams->colorProfile].g;
        this->rEnvColorB = sEnvColors[initParams->colorProfile].b;
        this->rEnvColorA = sEnvColors[initParams->colorProfile].a;
    } else {
        this->rPrimColorR = initParams->primColor.r;
        this->rPrimColorG = initParams->primColor.g;
        this->rPrimColorB = initParams->primColor.b;
        this->rPrimColorA = initParams->primColor.a;
        this->rEnvColorR = initParams->envColor.r;
        this->rEnvColorG = initParams->envColor.g;
        this->rEnvColorB = initParams->envColor.b;
        this->rEnvColorA = initParams->envColor.a;
    }

    this->rRandXZ = initParams->randXZ;
    this->rScale = initParams->scale;
    this->rLifespan = initParams->life;
    this->draw = EffectSsDtBubble_Draw;
    this->update = EffectSsDtBubble_Update;

    return 1;
}

void EffectSsDtBubble_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    f32 scale;

    OPEN_DISPS(gfxCtx);

    scale = this->rScale * 0.004f;
    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->rPrimColorR, this->rPrimColorG, this->rPrimColorB,
                    (this->rPrimColorA * this->life) / this->rLifespan);
    gDPSetEnvColor(POLY_OPA_DISP++, this->rEnvColorR, this->rEnvColorG, this->rEnvColorB,
                   (this->rEnvColorA * this->life) / this->rLifespan);
    gSPSegment(POLY_OPA_DISP++, 0x08, this->gfx);
    gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_0301B0);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsDtBubble_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    f32 rand;

    if (this->rRandXZ == 1) {
        rand = Rand_ZeroOne();
        this->pos.x += (rand * 2.0f) - 1.0f;

        rand = Rand_ZeroOne();
        this->pos.z += (rand * 2.0f) - 1.0f;
    }
}
