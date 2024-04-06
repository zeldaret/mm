#include "z64eff_ss_dead.h"
#include "global.h"

void func_800AE2A0(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3) {
    f32 cos;
    Gfx* gfx;
    f32 absCos;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_OPA_DISP;
    cos = Math_CosS((0x8000 / arg3) * arg2);
    absCos = fabsf(cos);

    gDPPipeSync(gfx++);

    if (color == NULL) {
        gDPSetFogColor(gfx++, 255, 0, 0, 0);
    } else {
        gDPSetFogColor(gfx++, color->r, color->g, color->b, color->a);
    }

    gSPFogPosition(gfx++, 0, TRUNCF_BINANG(absCos * 3000.0f) + 1500);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800AE434(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3) {
    Gfx* gfx;
    f32 cos;

    OPEN_DISPS(play->state.gfxCtx);

    cos = Math_CosS((0x4000 / arg3) * arg2);
    gfx = POLY_OPA_DISP;

    gDPPipeSync(gfx++);
    gDPSetFogColor(gfx++, color->r, color->g, color->b, color->a);
    gSPFogPosition(gfx++, 0, TRUNCF_BINANG(2800.0f * fabsf(cos)) + 1700);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800AE5A0(PlayState* play) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    POLY_OPA_DISP = Play_SetFog(play, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800AE5E4(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3) {
    f32 cos;
    Gfx* gfx;
    f32 absCos;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_XLU_DISP;
    cos = Math_CosS((0x8000 / arg3) * arg2);
    absCos = fabsf(cos);

    gDPPipeSync(gfx++);

    if (color == NULL) {
        gDPSetFogColor(gfx++, 255, 0, 0, 0);
    } else {
        gDPSetFogColor(gfx++, color->r, color->g, color->b, color->a);
    }

    gSPFogPosition(gfx++, 0, TRUNCF_BINANG(absCos * 3000.0f) + 1500);

    POLY_XLU_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800AE778(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3) {
    f32 cos;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    gfx = POLY_XLU_DISP;
    cos = Math_CosS((0x4000 / arg3) * arg2);

    gDPPipeSync(gfx++);
    gDPSetFogColor(gfx++, color->r, color->g, color->b, color->a);
    gSPFogPosition(gfx++, 0, TRUNCF_BINANG(2800.0f * fabsf(cos)) + 1700);

    POLY_XLU_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800AE8EC(PlayState* play) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(POLY_XLU_DISP++);
    POLY_XLU_DISP = Play_SetFog(play, POLY_XLU_DISP);

    CLOSE_DISPS(play->state.gfxCtx);
}
