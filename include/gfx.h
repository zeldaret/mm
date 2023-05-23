#ifndef GFX_H
#define GFX_H

#include "ultra64.h"
#include "PR/sched.h"
#include "thga.h"
#include "alignment.h"


typedef struct {
    /* 0x000 */ Gfx taskStart[9];
    /* 0x048 */ Gfx clearZBuffer[8];       // original name: clear_zb_dl
    /* 0x088 */ Gfx clearFrameBuffer[5];   // original name: clear_fb_dl
    /* 0x0B0 */ Gfx setupBuffers[6];       // setup framebuffer and zbuffer
    /* 0x0E0 */ Gfx unk_E0[12];            // unused
    /* 0x140 */ Gfx syncSegments[17];
    /* 0x1C8 */ Gfx setScissor[2];
    /* 0x1D8 */ Gfx unk_1D8[25];           // unused
    /* 0x2A0 */ Gfx disps[5];
    /* 0x2C8 */ Gfx clearFillRect[3];      // fillrect for clearing buffers
    /* 0x2E0 */ Gfx fillRect[3];           // fillrect for general purpose
    /* 0x2F8 */ Gfx debugDisp[1];
} GfxMasterList; // size = 0x300

#define GFXPOOL_HEAD_MAGIC 0x1234
#define GFXPOOL_TAIL_MAGIC 0x5678

typedef struct GfxPool {
    /* 0x00000 */ u16 headMagic; // 1234
    /* 0x00008 */ GfxMasterList master;
    /* 0x00308 */ Gfx polyXluBuffer[2048];
    /* 0x04308 */ Gfx overlayBuffer[1024];
    /* 0x06308 */ Gfx workBuffer[64];
    /* 0x06508 */ Gfx debugBuffer[64];
    /* 0x06708 */ Gfx polyOpaBuffer[13184];
    /* 0x20308 */ u16 tailMagic; // 5678
} GfxPool; // size = 0x20310

typedef struct GraphicsContext {
    /* 0x000 */ Gfx*        polyOpaBuffer;  // Pointer to "Zelda 0"
    /* 0x004 */ Gfx*        polyXluBuffer;  // Pointer to "Zelda 1"
    /* 0x008 */ char        unk_8[0x8];     // Unused, could this be pointers to "Zelda 2" / "Zelda 3"
    /* 0x010 */ Gfx*        overlayBuffer;  // Pointer to "Zelda 4"
    /* 0x014 */ u32         unk_14;
    /* 0x018 */ char        unk_18[0x20];
    /* 0x038 */ OSMesg      msgBuff[8];
    /* 0x058 */ OSMesgQueue* schedMsgQ;
    /* 0x05C */ OSMesgQueue queue;
    /* 0x074 */ char        unk_74[0x04];
    /* 0x078 */ OSScTask    task;
    /* 0x0E0 */ char        unk_E0[0xD0];
    /* 0x1B0 */ Gfx*        workBuffer;
    /* 0x1B4 */ TwoHeadGfxArena work;
    /* 0x1C4 */ Gfx*        debugBuffer;
    /* 0x1C8 */ TwoHeadGfxArena debug;
    /* 0x1D8 */ char        unk_1D8[0xAC];
    /* 0x284 */ OSViMode*   viMode;
    /* 0x288 */ void*       zbuffer;
    /* 0x28C */ char        unk_28C[0x1C];
    /* 0x2A8 */ TwoHeadGfxArena overlay;    // "Zelda 4"
    /* 0x2B8 */ TwoHeadGfxArena polyOpa;    // "Zelda 0"
    /* 0x2C8 */ TwoHeadGfxArena polyXlu;    // "Zelda 1"
    /* 0x2D8 */ u32         gfxPoolIdx;
    /* 0x2DC */ u16*        curFrameBuffer;
    /* 0x2E0 */ char        unk_2E0[0x4];
    /* 0x2E4 */ u32         viConfigFeatures;
    /* 0x2E8 */ char        unk_2E8[0x2];
    /* 0x2EA */ u8          updateViMode;
    /* 0x2EB */ u8          framebufferIndex;
    /* 0x2EC */ void        (*callback)(struct GraphicsContext*, u32);
    /* 0x2F0 */ u32         callbackArg;
    /* 0x2F4 */ f32         xScale;
    /* 0x2F8 */ f32         yScale;
    /* 0x2FC */ GfxMasterList* masterList;
} GraphicsContext; // size = 0x300


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



#endif
