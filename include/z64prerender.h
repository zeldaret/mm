#ifndef Z64_PRERENDER_H
#define Z64_PRERENDER_H

#include "ultra64.h"
#include "listalloc.h"
#include "unk.h"

#define BG2D_FLAGS_1 (1 << 0)
#define BG2D_FLAGS_2 (1 << 1)
#define BG2D_FLAGS_AC_THRESHOLD (1 << 2)
#define BG2D_FLAGS_LOAD_S2DEX2 (1 << 3)
#define BG2D_FLAGS_COPY (1 << 4)

typedef enum PrerenderFilterState {
    /* 0 */ PRERENDER_FILTER_STATE_NONE,
    /* 1 */ PRERENDER_FILTER_STATE_PROCESS,
    /* 2 */ PRERENDER_FILTER_STATE_DONE
} PrerenderFilterState;

typedef struct PreRender {
    /* 0x00 */ u16 width;
    /* 0x02 */ u16 height;
    /* 0x04 */ u16 widthSave;
    /* 0x06 */ u16 heightSave;
    /* 0x08 */ UNK_TYPE1 unk_08[0x8];
    /* 0x10 */ u16* fbuf;
    /* 0x14 */ u16* fbufSave;
    /* 0x18 */ u8* cvgSave;
    /* 0x1C */ u16* zbuf;
    /* 0x20 */ u16* zbufSave;
    /* 0x24 */ u16 ulxSave;
    /* 0x26 */ u16 ulySave;
    /* 0x28 */ u16 lrxSave;
    /* 0x2A */ u16 lrySave;
    /* 0x2C */ u16 ulx;
    /* 0x2E */ u16 uly;
    /* 0x30 */ u16 lrx;
    /* 0x32 */ u16 lry;
    /* 0x34 */ UNK_TYPE1 unk_34[0x10];
    /* 0x44 */ ListAlloc alloc;
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 filterState; // See `PrerenderFilterState`
} PreRender; // size = 0x50


void PreRender_SetValuesSave(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg);
void PreRender_Init(PreRender* this);
void PreRender_SetValues(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf);
void PreRender_Destroy(PreRender* this);
void PreRender_CopyImage(PreRender* this, Gfx** gfxp, void* img, void* imgDst, u32 useThresholdAlphaCompare);
void PreRender_RestoreBuffer(PreRender* this, Gfx** gfxp, void* buf, void* bufSave);
void func_8016FF90(PreRender* this, Gfx** gfxp, void* buf, void* bufSave, s32 envR, s32 envG, s32 envB, s32 envA);
void func_80170200(PreRender* this, Gfx** gfxp, void* buf, void* bufSave);
void PreRender_CoverageRgba16ToI8(PreRender* this, Gfx** gfxp, void* img, void* cvgDst);
void PreRender_SaveZBuffer(PreRender* this, Gfx** gfxp);
void PreRender_SaveFramebuffer(PreRender* this, Gfx** gfxp);
void PreRender_FetchFbufCoverage(PreRender* this, Gfx** gfxp);
void PreRender_DrawCoverage(PreRender* this, Gfx** gfxp);
void PreRender_RestoreZBuffer(PreRender* this, Gfx** gfxp);
void func_80170798(PreRender* this, Gfx** gfxp);
void func_80170AE0(PreRender* this, Gfx** gfxp, s32 alpha);
void PreRender_RestoreFramebuffer(PreRender* this, Gfx** gfxp);
void PreRender_AntiAliasFilterPixel(PreRender* this, s32 x, s32 y);
void PreRender_AntiAliasFilter(PreRender* this);
u32 PreRender_Get5bMedian9(u8* px1, u8* px2, u8* px3);
void PreRender_DivotFilter(PreRender* this);
void PreRender_ApplyFilters(PreRender* this);
void PreRender_ApplyFiltersSlowlyInit(PreRender* this);
void PreRender_ApplyFiltersSlowlyDestroy(PreRender* this);
void func_801720C4(PreRender* this);
void Prerender_DrawBackground2D(Gfx** gfxp, void* timg, void* tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 tt, u16 tlutCount, f32 x, f32 y, f32 xScale, f32 yScale, u32 flags);

#endif
