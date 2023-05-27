#ifndef GFX_H
#define GFX_H

#include "ultra64.h"
#include "PR/sched.h"
#include "thga.h"
#include "alignment.h"

struct GameState;

typedef enum SetupDL {
    /* 0x00 */ SETUPDL_0,
    /* 0x01 */ SETUPDL_1,
    /* 0x02 */ SETUPDL_2,
    /* 0x03 */ SETUPDL_3,
    /* 0x04 */ SETUPDL_4,
    /* 0x05 */ SETUPDL_5,
    /* 0x06 */ SETUPDL_6,
    /* 0x07 */ SETUPDL_7,
    /* 0x08 */ SETUPDL_8,
    /* 0x09 */ SETUPDL_9,
    /* 0x0A */ SETUPDL_10,
    /* 0x0B */ SETUPDL_11,
    /* 0x0C */ SETUPDL_12,
    /* 0x0D */ SETUPDL_13,
    /* 0x0E */ SETUPDL_14,
    /* 0x0F */ SETUPDL_15,
    /* 0x10 */ SETUPDL_16,
    /* 0x11 */ SETUPDL_17,
    /* 0x12 */ SETUPDL_18,
    /* 0x13 */ SETUPDL_19,
    /* 0x14 */ SETUPDL_20,
    /* 0x15 */ SETUPDL_21,
    /* 0x16 */ SETUPDL_22,
    /* 0x17 */ SETUPDL_23,
    /* 0x18 */ SETUPDL_24,
    /* 0x19 */ SETUPDL_25,
    /* 0x1A */ SETUPDL_26,
    /* 0x1B */ SETUPDL_27,
    /* 0x1C */ SETUPDL_28,
    /* 0x1D */ SETUPDL_29,
    /* 0x1E */ SETUPDL_30,
    /* 0x1F */ SETUPDL_31,
    /* 0x20 */ SETUPDL_32,
    /* 0x21 */ SETUPDL_33,
    /* 0x22 */ SETUPDL_34,
    /* 0x23 */ SETUPDL_35,
    /* 0x24 */ SETUPDL_36,
    /* 0x25 */ SETUPDL_37,
    /* 0x26 */ SETUPDL_38,
    /* 0x27 */ SETUPDL_39,
    /* 0x28 */ SETUPDL_40,
    /* 0x29 */ SETUPDL_41,
    /* 0x2A */ SETUPDL_42,
    /* 0x2B */ SETUPDL_43,
    /* 0x2C */ SETUPDL_44,
    /* 0x2D */ SETUPDL_45,
    /* 0x2E */ SETUPDL_46,
    /* 0x2F */ SETUPDL_47,
    /* 0x30 */ SETUPDL_48,
    /* 0x31 */ SETUPDL_49,
    /* 0x32 */ SETUPDL_50,
    /* 0x33 */ SETUPDL_51,
    /* 0x34 */ SETUPDL_52,
    /* 0x35 */ SETUPDL_53,
    /* 0x36 */ SETUPDL_54,
    /* 0x37 */ SETUPDL_55,
    /* 0x38 */ SETUPDL_56,
    /* 0x39 */ SETUPDL_57,
    /* 0x3A */ SETUPDL_58,
    /* 0x3B */ SETUPDL_59,
    /* 0x3C */ SETUPDL_60,
    /* 0x3D */ SETUPDL_61,
    /* 0x3E */ SETUPDL_62,
    /* 0x3F */ SETUPDL_63,
    /* 0x40 */ SETUPDL_64,
    /* 0x41 */ SETUPDL_65,
    /* 0x42 */ SETUPDL_66,
    /* 0x43 */ SETUPDL_67,
    /* 0x44 */ SETUPDL_68,
    /* 0x45 */ SETUPDL_69,
    /* 0x46 */ SETUPDL_70,
    /* 0x47 */ SETUPDL_71,
    /* 0x48 */ SETUPDL_72,
    /* 0x49 */ SETUPDL_MAX
} SetupDL;

typedef struct {
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
    /* 0x0E0 */ char unk_E0[0xD0];
    /* 0x1B0 */ Gfx* workBuffer;
    /* 0x1B4 */ TwoHeadGfxArena work;
    /* 0x1C4 */ Gfx* debugBuffer;
    /* 0x1C8 */ TwoHeadGfxArena debug;
    /* 0x1D8 */ UNK_TYPE1 unk_1D8[0xAC];
    /* 0x284 */ OSViMode* viMode;
    /* 0x288 */ void* zbuffer;
    /* 0x28C */ char unk_28C[0x1C];
    /* 0x2A8 */ TwoHeadGfxArena overlay; // "Zelda 4"
    /* 0x2B8 */ TwoHeadGfxArena polyOpa; // "Zelda 0"
    /* 0x2C8 */ TwoHeadGfxArena polyXlu; // "Zelda 1"
    /* 0x2D8 */ u32 gfxPoolIdx;
    /* 0x2DC */ u16* curFrameBuffer;
    /* 0x2E0 */ char unk_2E0[0x4];
    /* 0x2E4 */ u32 viConfigFeatures;
    /* 0x2E8 */ char unk_2E8[0x2];
    /* 0x2EA */ u8 updateViMode;
    /* 0x2EB */ u8 framebufferIndex;
    /* 0x2EC */ void (*callback)(struct GraphicsContext*, u32);
    /* 0x2F0 */ u32 callbackArg;
    /* 0x2F4 */ f32 xScale;
    /* 0x2F8 */ f32 yScale;
    /* 0x2FC */ GfxMasterList* masterList;
} GraphicsContext; // size = 0x300

Gfx* Gfx_SetFog(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFogWithSync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFog2(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_CallSetupDLImpl(Gfx* gfx, u32 i);
Gfx* Gfx_CallSetupDL(Gfx* gfx, u32 i);
void Gfx_CallSetupDLAtPtr(Gfx** gfxp, u32 i);
Gfx* func_8012BFC4(Gfx* gfx);
Gfx* func_8012BFEC(Gfx* gfx);
Gfx* func_8012C014(Gfx* gfx);
void func_8012C058(GraphicsContext* gfxCtx);
void func_8012C080(GraphicsContext* gfxCtx);
void func_8012C0A8(GraphicsContext* gfxCtx);
void func_8012C0D0(GraphicsContext* gfxCtx);
void func_8012C0F8(GraphicsContext* gfxCtx);
void func_8012C120(GraphicsContext* gfxCtx);
void func_8012C148(GraphicsContext* gfxCtx);
void func_8012C170(GraphicsContext* gfxCtx);
Gfx* func_8012C198(Gfx* gfx);
void func_8012C1C0(GraphicsContext* gfxCtx);
Gfx* func_8012C1EC(Gfx* gfx);
void func_8012C214(GraphicsContext* gfxCtx);
void func_8012C240(GraphicsContext* gfxCtx);
void func_8012C268(struct GameState* gameState);
void func_8012C28C(GraphicsContext* gfxCtx);
Gfx* func_8012C2B4(Gfx* gfx);
void func_8012C2DC(GraphicsContext* gfxCtx);
Gfx* func_8012C304(Gfx* gfx);
void func_8012C32C(GraphicsContext* gfxCtx);
void func_8012C354(GraphicsContext* gfxCtx);
void func_8012C37C(GraphicsContext* gfxCtx);
Gfx* func_8012C3A4(Gfx* gfx);
Gfx* func_8012C3CC(Gfx* gfx);
void func_8012C3F4(GraphicsContext* gfxCtx);
void func_8012C420(GraphicsContext* gfxCtx);
void func_8012C448(GraphicsContext* gfxCtx);
void func_8012C470(GraphicsContext* gfxCtx);
Gfx* func_8012C498(Gfx* gfx);
void func_8012C4C0(GraphicsContext* gfxCtx);
void func_8012C4E8(GraphicsContext* gfxCtx);
void func_8012C510(GraphicsContext* gfxCtx);
void func_8012C538(GraphicsContext* gfxCtx);
void func_8012C560(GraphicsContext* gfxCtx);
void func_8012C588(GraphicsContext* gfxCtx);
void func_8012C5B0(GraphicsContext* gfxCtx);
void func_8012C5D8(GraphicsContext* gfxCtx);
Gfx* func_8012C600(Gfx* gfx);
void func_8012C628(GraphicsContext* gfxCtx);
void func_8012C654(GraphicsContext* gfxCtx);
void func_8012C680(Gfx** gfxp);
void func_8012C6AC(GraphicsContext* gfxCtx);
void func_8012C6D4(GraphicsContext* gfxCtx);
void func_8012C6FC(GraphicsContext* gfxCtx);
Gfx* func_8012C724(Gfx* gfx);
Gfx* func_8012C74C(Gfx* gfx);
Gfx* func_8012C774(Gfx* gfx);
Gfx* func_8012C7B8(Gfx* gfx);
Gfx* func_8012C7FC(Gfx* gfx);
Gfx* func_8012C840(Gfx* gfx);
Gfx* func_8012C868(Gfx* gfx);
void func_8012C8AC(GraphicsContext* gfxCtx);
void func_8012C8D4(GraphicsContext* gfxCtx);
void func_8012C8FC(GraphicsContext* gfxCtx);
void func_8012C924(GraphicsContext* gfxCtx);
void func_8012C94C(GraphicsContext* gfxCtx);
void func_8012C974(GraphicsContext* gfxCtx);
void func_8012C9BC(GraphicsContext* gfxCtx);
void func_8012C9E4(GraphicsContext* gfxCtx);
void func_8012CA0C(Gfx** gfxp);
void func_8012CA38(GraphicsContext* gfxCtx);
Gfx* Gfx_BranchTexScroll(Gfx** gfxp, u32 x, u32 y, s32 width, s32 height);
void func_8012CB04(Gfx** gfxp, u32 x, u32 y);
Gfx* func_8012CB28(GraphicsContext* gfxCtx, u32 x, u32 y);
Gfx* Gfx_TexScroll(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height);
Gfx* Gfx_TwoTexScroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2);
Gfx* Gfx_TwoTexScrollEnvColor(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2, u32 y2, s32 width2, s32 height2, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_EnvColor(GraphicsContext* gfxCtx, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_PrimColor(GraphicsContext* gfxCtx, s32 lodfrac, s32 r, s32 g, s32 b, s32 a);
void func_8012CF0C(GraphicsContext* gfxCtx, s32 clearFb, s32 clearZb, u8 r, u8 g, u8 b);
void func_8012D374(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b);
void func_8012D40C(f32* param_1, f32* param_2, s16* param_3);

extern Gfx gSetupDL[SETUPDL_MAX * 6];
extern Gfx gEmptyDL[];

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
