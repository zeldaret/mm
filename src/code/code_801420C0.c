#include "global.h"

void func_801420C0(struct_801F8020* this) {
    this->useRgba = false;
    this->setScissor = 0;
    this->primColor.r = 255;
    this->primColor.g = 255;
    this->primColor.b = 255;
    this->primColor.a = 255;
    this->envColor.r = 0;
    this->envColor.g = 0;
    this->envColor.b = 0;
    this->envColor.a = 255;
}

void func_801420F4(struct_801F8020* this) {

}

#ifdef NON_EQUIVALENT
void func_80142100(struct_801F8020* this, Gfx** gfxP, s32 arg2) {
    Gfx* gfx = *gfxP;
    s32 temp_a0;
    s32 temp_a1;
    s32 height = 0x1000 / (D_801FBBCC * 2); // temp_lo;
    s32 temp_t1;
    s32 y; // a3;
    s32 var_v0 = !this->useRgba ? G_IM_FMT_IA : G_IM_FMT_RGBA;
    u32 temp_a0_2;

    if (arg2 == 0) {
        return;
    }

    gDPPipeSync(gfx++);
    if (this->setScissor == 1) {
        gSPDisplayList(gfx++, &D_0E000000.setScissor[0]);
    }

    gDPSetOtherMode(gfx++, G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT);
    gDPSetPrimColor(gfx++, 0, 0, this->primColor.r, this->primColor.g, this->primColor.b, this->primColor.a);
    gDPSetEnvColor(gfx++, this->envColor.r, this->envColor.g, this->envColor.b, this->envColor.a);

    temp_a0 = (var_v0 & 7) << 0x15;
    y = 0;

    for (y = 0; y <= D_801FBBCE - height; y += height) {
        gDPLoadTextureBlock(gfx++, arg2, var_v0, G_IM_SIZ_16b, SCREEN_WIDTH, height, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        gSPTextureRectangle(gfx++, 0, y << 2, D_801FBBCC << 2, (y + height) << 2, G_TX_RENDERTILE, 0, y << 5, 1 << 10, 1 << 10);
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/code_801420C0/func_80142100.s")
#endif
