/*
 * File: z_eff_ss_hitmark.c
 * Overlay: ovl_Effect_Ss_Hitmark
 * Description:
 */

#include "z_eff_ss_hitmark.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rTexIndex regs[0]
#define rType regs[1]
#define rPrimColorR regs[2]
#define rPrimColorG regs[3]
#define rPrimColorB regs[4]
#define rEnvColorR regs[5]
#define rEnvColorG regs[6]
#define rEnvColorB regs[7]
#define rScale regs[8]

#define PARAMS ((EffectSsHitmarkInitParams*)initParamsx)

u32 EffectSsHitmark_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsHitmark_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsHitmark_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

static Color_RGB8 sColors[] = {
    { 255, 255, 255 }, { 255, 255, 0 }, { 255, 255, 255 }, { 255, 0, 0 },   { 255, 200, 100 }, { 200, 150, 0 },
    { 150, 100, 0 },   { 100, 50, 0 },  { 255, 255, 255 }, { 255, 0, 0 },   { 255, 255, 0 },   { 255, 0, 0 },
    { 255, 255, 255 }, { 0, 255, 200 }, { 255, 255, 255 }, { 150, 0, 255 },
};

static TexturePtr sTextures[] = {
    gameplay_keep_Tex_033310, gameplay_keep_Tex_033490, gameplay_keep_Tex_033610, gameplay_keep_Tex_033790,
    gameplay_keep_Tex_033910, gameplay_keep_Tex_033A90, gameplay_keep_Tex_033C10, gameplay_keep_Tex_033D90,
    gameplay_keep_Tex_033F10, gameplay_keep_Tex_034090, gameplay_keep_Tex_034210, gameplay_keep_Tex_034390,
    gameplay_keep_Tex_034510, gameplay_keep_Tex_034690, gameplay_keep_Tex_034810, gameplay_keep_Tex_034990,
    gameplay_keep_Tex_034B10, gameplay_keep_Tex_034C90, gameplay_keep_Tex_034E10, gameplay_keep_Tex_034F90,
    gameplay_keep_Tex_035110, gameplay_keep_Tex_035290, gameplay_keep_Tex_035410, gameplay_keep_Tex_035590,
    gameplay_keep_Tex_033310, gameplay_keep_Tex_033490, gameplay_keep_Tex_033610, gameplay_keep_Tex_033790,
    gameplay_keep_Tex_033910, gameplay_keep_Tex_033A90, gameplay_keep_Tex_033C10, gameplay_keep_Tex_033D90,
};

const EffectSsInit Effect_Ss_Hitmark_InitVars = {
    EFFECT_SS_HITMARK,
    EffectSsHitmark_Init,
};

u32 EffectSsHitmark_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsHitmarkInitParams* initParams = PARAMS;
    s32 colorIndex;

    this->pos = initParams->pos;
    this->gfx = gameplay_keep_DL_035710;

    if (initParams->type == EFFECT_HITMARK_DUST) {
        this->life = 16;
    } else {
        this->life = 8;
    }

    this->draw = EffectSsHitmark_Draw;
    this->update = EffectSsHitmark_Update;

    colorIndex = initParams->type * 4;
    this->rTexIndex = 0;
    this->rType = initParams->type;
    this->rPrimColorR = sColors[colorIndex].r;
    this->rPrimColorG = sColors[colorIndex].g;
    this->rPrimColorB = sColors[colorIndex].b;
    this->rEnvColorR = sColors[colorIndex + 1].r;
    this->rEnvColorG = sColors[colorIndex + 1].g;
    this->rEnvColorB = sColors[colorIndex + 1].b;
    this->rScale = initParams->scale;

    return 1;
}

void EffectSsHitmark_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    MtxF mfTrans;
    MtxF mfScale;
    MtxF mfResult;
    MtxF mfTrans11DA0;
    Mtx* mtx;
    f32 scale;
    TexturePtr tex;
    s32 pad;

    OPEN_DISPS(gfxCtx);

    SkinMatrix_SetTranslate(&mfTrans, this->pos.x, this->pos.y, this->pos.z);
    scale = this->rScale / 100.0f;
    SkinMatrix_SetScale(&mfScale, scale, scale, 1.0f);
    SkinMatrix_MtxFMtxFMult(&mfTrans, &globalCtx->billboardMtxF, &mfTrans11DA0);
    SkinMatrix_MtxFMtxFMult(&mfTrans11DA0, &mfScale, &mfResult);
    gSPMatrix(POLY_XLU_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    mtx = SkinMatrix_MtxFToNewMtx(gfxCtx, &mfResult);

    if (mtx != NULL) {
        gSPMatrix(POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        tex = sTextures[(this->rType * 8) + (this->rTexIndex)];
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(tex));
        func_8012C9BC(gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, this->rPrimColorR, this->rPrimColorG, this->rPrimColorB, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, this->rEnvColorR, this->rEnvColorG, this->rEnvColorB, 0);
        gSPDisplayList(POLY_XLU_DISP++, this->gfx);
    }
    CLOSE_DISPS(gfxCtx);
}

void EffectSsHitmark_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 colorIndex;

    if (this->rType == EFFECT_HITMARK_DUST) {
        this->rTexIndex = (15 - this->life) / 2;
    } else {
        this->rTexIndex = 7 - this->life;
    }

    if (this->rTexIndex != 0) {
        colorIndex = this->rType * 4 + 2;
        this->rPrimColorR = func_800B096C(this->rPrimColorR, sColors[colorIndex].r, this->life + 1);
        this->rPrimColorG = func_800B096C(this->rPrimColorG, sColors[colorIndex].g, this->life + 1);
        this->rPrimColorB = func_800B096C(this->rPrimColorB, sColors[colorIndex].b, this->life + 1);
        this->rEnvColorR = func_800B096C(this->rEnvColorR, sColors[colorIndex + 1].r, this->life + 1);
        this->rEnvColorG = func_800B096C(this->rEnvColorG, sColors[colorIndex + 1].g, this->life + 1);
        this->rEnvColorB = func_800B096C(this->rEnvColorB, sColors[colorIndex + 1].b, this->life + 1);
    }
}
