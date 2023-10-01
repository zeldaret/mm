#ifndef Z64_VISFBCOPYFX_H
#define Z64_VISFBCOPYFX_H

#include "ultra64.h"
#include "color.h"
#include "PR/gs2dex.h"

typedef enum VisFbCopyBgMode {
    /* 0 */ VIS_FB_COPY_BG_CYC_1CYC, //!< Enable rescaling
    /* 1 */ VIS_FB_COPY_BG_CYC_COPY  //!< Direct copy, no scaling
} VisFbCopyBgMode;

typedef enum VisFbCopyMode {
    /* 0 */ VIS_FB_COPY_MODE_NONE,    //!< Do nothing but waste time loading microcode
    /* 1 */ VIS_FB_COPY_MODE_GENERAL, //!< Interpolation, filling and scaling
    /* 2 */ VIS_FB_COPY_MODE_INTERPOLATE
} VisFbCopyMode;

typedef struct VisFbCopyFx {
    /* 0x00 */ u8 mode;
    /* 0x04 */ f32 scale;
    /* 0x08 */ f32 lodProportion; // expected to be between 0.0f and 1.0f
    /* 0x0C */ Color_RGBA8_u32 primColor;
    /* 0x10 */ Color_RGBA8_u32 envColor;
} VisFbCopyFx; // size = 0x14

void VisFbCopyFx_Init(VisFbCopyFx* this);
void VisFbCopyFx_Destroy(VisFbCopyFx* this);
void VisFbCopyFx_DrawBgToColorImage(Gfx** gfxP, uObjBg* bg, void* img, s32 width, s32 height, VisFbCopyBgMode cycleMode);
void VisFbCopyFx_SetBg(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 x, f32 y, f32 scaleX, f32 scaleY, VisFbCopyBgMode cycleMode);
void VisFbCopyFx_SetBgSimple(Gfx** gfxP, void* source, void* img, s32 width, s32 height, VisFbCopyBgMode cycleMode);
void VisFbCopyFx_SetBgGeneral(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 x, f32 y, f32 scaleX, f32 scaleY, VisFbCopyBgMode cycleMode);
void VisFbCopyFx_ApplyEffects(VisFbCopyFx* this, Gfx** gfxP, void* source, void* img, s32 width, s32 height);
void VisFbCopyFx_DrawGeneral(VisFbCopyFx* this, Gfx** gfxP, void* source, void* img, s32 width, s32 height);
void VisFbCopyFx_DrawInterpolate(VisFbCopyFx* this, Gfx** gfxP, void* img, s32 width, s32 height);
void VisFbCopyFx_Draw(VisFbCopyFx* this, Gfx** gfxP, void* img);

#endif
