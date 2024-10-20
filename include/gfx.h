#ifndef GFX_H
#define GFX_H

#include "ultra64.h"
#include "PR/sched.h"
#include "thga.h"
#include "alignment.h"
#include "unk.h"

struct GameState;
struct PlayState;

#define TMEM_SIZE 0x1000

typedef struct GfxMasterList {
    /* 0x000 */ Gfx taskStart[9];
    /* 0x048 */ Gfx clearZBuffer[8];     // original name: clear_zb_dl
    /* 0x088 */ Gfx clearFrameBuffer[5]; // original name: clear_fb_dl
    /* 0x0B0 */ Gfx setupBuffers[6];     // setup framebuffer and zbuffer
    /* 0x0E0 */ Gfx unk_E0[12];          // unused
    /* 0x140 */ Gfx syncSegments[17];
    /* 0x1C8 */ Gfx setScissor[2];
    /* 0x1D8 */ Gfx unk_1D8[25]; // unused
    /* 0x2A0 */ Gfx disps[5];
    /* 0x2C8 */ Gfx clearFillRect[3]; // fillrect for clearing buffers
    /* 0x2E0 */ Gfx fillRect[3];      // fillrect for general purpose
    /* 0x2F8 */ Gfx debugDisp[1];
} GfxMasterList; // size = 0x300

#define GFXPOOL_HEAD_MAGIC 0x1234
#define GFXPOOL_TAIL_MAGIC 0x5678

typedef struct GfxPool {
    /* 0x00000 */ u16 headMagic; // GFXPOOL_HEAD_MAGIC
    /* 0x00008 */ GfxMasterList master;
    /* 0x00308 */ Gfx polyXluBuffer[0x800];
    /* 0x04308 */ Gfx overlayBuffer[0x400];
    /* 0x06308 */ Gfx workBuffer[0x40];
    /* 0x06508 */ Gfx debugBuffer[0x40];
    /* 0x06708 */ Gfx polyOpaBuffer[0x3380];
    /* 0x20308 */ u16 tailMagic; // GFXPOOL_TAIL_MAGIC
} GfxPool; // size = 0x20310

typedef struct GraphicsContext {
    /* 0x000 */ Gfx* polyOpaBuffer; // Pointer to "Zelda 0"
    /* 0x004 */ Gfx* polyXluBuffer; // Pointer to "Zelda 1"
    /* 0x008 */ char unk_8[0x8];    // Unused, could this be pointers to "Zelda 2" / "Zelda 3"
    /* 0x010 */ Gfx* overlayBuffer; // Pointer to "Zelda 4"
    /* 0x014 */ u32 unk_14;
    /* 0x018 */ char unk_18[0x20];
    /* 0x038 */ OSMesg msgBuff[8];
    /* 0x058 */ OSMesgQueue* schedMsgQ;
    /* 0x05C */ OSMesgQueue queue;
    /* 0x074 */ char unk_74[0x04];
    /* 0x078 */ OSScTask task;
    /* 0x0D0 */ char unk_D0[0xD0];
    /* 0x1A0 */ Gfx* workBuffer;
    /* 0x1A4 */ TwoHeadGfxArena work;
    /* 0x1B4 */ Gfx* debugBuffer;
    /* 0x1B8 */ TwoHeadGfxArena debug;
    /* 0x1C8 */ UNK_TYPE1 unk_1C8[0xAC];
    /* 0x274 */ OSViMode* viMode;
    /* 0x278 */ void* zbuffer;
    /* 0x27C */ char unk_27C[0x1C];
    /* 0x298 */ TwoHeadGfxArena overlay; // "Zelda 4"
    /* 0x2A8 */ TwoHeadGfxArena polyOpa; // "Zelda 0"
    /* 0x2B8 */ TwoHeadGfxArena polyXlu; // "Zelda 1"
    /* 0x2C8 */ u32 gfxPoolIdx;
    /* 0x2CC */ u16* curFrameBuffer;
    /* 0x2D0 */ char unk_2D0[0x4];
    /* 0x2D4 */ u32 viConfigFeatures;
    /* 0x2D8 */ char unk_2D8[0x2];
    /* 0x2DA */ u8 updateViMode;
    /* 0x2DB */ u8 framebufferIndex;
    /* 0x2DC */ void (*callback)(struct GraphicsContext*, void*);
    /* 0x2E0 */ void* callbackArg;
    /* 0x2E4 */ f32 xScale;
    /* 0x2E8 */ f32 yScale;
    /* 0x2EC */ GfxMasterList* masterList;
} GraphicsContext; // size = 0x2F0

// graph.c
void Graph_ThreadEntry(void* arg);

Gfx* Gfx_SetFog(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFogWithSync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFog2(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);

Gfx* Gfx_BranchTexScroll(Gfx** gfxP, u32 x, u32 y, s32 width, s32 height);
void func_8012CB04(Gfx** gfxP, u32 x, u32 y);
Gfx* func_8012CB28(GraphicsContext* gfxCtx, u32 x, u32 y);
Gfx* Gfx_TexScroll(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height);
Gfx* Gfx_TwoTexScroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2);
Gfx* Gfx_TwoTexScrollEnvColor(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_EnvColor(GraphicsContext* gfxCtx, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_PrimColor(GraphicsContext* gfxCtx, s32 lodfrac, s32 r, s32 g, s32 b, s32 a);
void func_8012CF0C(GraphicsContext* gfxCtx, s32 clearFb, s32 clearZb, u8 r, u8 g, u8 b);
void func_8012D374(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b);
void func_8012D40C(f32* param_1, f32* param_2, s16* param_3);

void Gfx_DrawDListOpa(struct PlayState* play, Gfx* dList);
void Gfx_DrawDListXlu(struct PlayState* play, Gfx* dList);

// graph.c
extern struct GfxMasterList* gGfxMasterDL;

extern Gfx gEmptyDL[];


extern GfxMasterList D_0E000000;


#define WORK_DISP __gfxCtx->work.p
#define POLY_OPA_DISP __gfxCtx->polyOpa.p
#define POLY_XLU_DISP __gfxCtx->polyXlu.p
#define OVERLAY_DISP __gfxCtx->overlay.p
#define DEBUG_DISP __gfxCtx->debug.p

// __gfxCtx shouldn't be used directly.
// Use the DISP macros defined above when writing to display buffers.
#define OPEN_DISPS(gfxCtx)                  \
    {                                       \
        GraphicsContext* __gfxCtx = gfxCtx; \
        s32 __dispPad

#define CLOSE_DISPS(gfxCtx) \
    (void)0;                \
    }                       \
    (void)0

#define GRAPH_ALLOC(gfxCtx, size) ((void*)((gfxCtx)->polyOpa.d = (Gfx*)((u8*)(gfxCtx)->polyOpa.d - ALIGN16(size))))

// Custom gbi macro
#define gDPSetTileCustom(pkt, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)                    \
    {                                                                                                                  \
        gDPPipeSync(pkt);                                                                                              \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, \
                   masks, shifts);                                                                                     \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,  \
                   cms, masks, shifts);                                                                                \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                          \
    }                                                                                                                  \
    (void)0

// used only by code_80140E80
#define gDPSetLODColor(pkt, c, m, l, d)                                           \
    _DW({                                                                         \
        Gfx* _g = (Gfx*)(pkt);                                                    \
                                                                                  \
        _g->words.w0 = (_SHIFTL(c, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)); \
        _g->words.w1 = (unsigned int)(d);                                         \
    })

/**
 * `x` vertex x
 * `y` vertex y
 * `z` vertex z
 * `s` texture s coordinate
 * `t` texture t coordinate
 * `crnx` red component of color vertex, or x component of normal vertex
 * `cgny` green component of color vertex, or y component of normal vertex
 * `cbnz` blue component of color vertex, or z component of normal vertex
 * `a` alpha
 */
#define VTX(x, y, z, s, t, crnx, cgny, cbnz, a) \
    { { { x, y, z }, 0, { s, t }, { crnx, cgny, cbnz, a } }, }

#define VTX_T(x, y, z, s, t, cr, cg, cb, a) \
    { { x, y, z }, 0, { s, t }, { cr, cg, cb, a }, }

#endif
