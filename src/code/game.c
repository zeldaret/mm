#include "z64game.h"

#include "global.h"
#include "audiomgr.h"
#include "libu64/debug.h"
#include "gfx.h"
#include "gfxalloc.h"
#include "idle.h"
#include "regs.h"
#include "sys_cfb.h"
#include "libc64/malloc.h"

#include "z64debug_text.h"
#include "z64rumble.h"
#include "z64speed_meter.h"
#include "z64vimode.h"
#include "z64vis.h"

s32 gFramerateDivisor = 1;
f32 gFramerateDivisorF = 1.0f;
f32 gFramerateDivisorHalf = 1.0f / 2.0f;
f32 gFramerateDivisorThird = 1.0f / 3.0f;

SpeedMeter sGameSpeedMeter;
VisCvg sGameVisCvg;
VisZBuf sGameVisZBuf;
VisMono sGameVisMono;
ViMode sGameViMode;

void GameState_UpdateFramerateDivisors(s32 divisor) {
    gFramerateDivisor = divisor;
    gFramerateDivisorF = divisor;
    gFramerateDivisorHalf = divisor / 2.0f;
    gFramerateDivisorThird = divisor / 3.0f;
}

void GameState_SetFramerateDivisor(GameState* gameState, s32 divisor) {
    R_UPDATE_RATE = divisor;
    gameState->framerateDivisor = divisor;
    GameState_UpdateFramerateDivisors(divisor);
}

void GameState_SetFBFilter(Gfx** gfxP, void* zbuffer) {
    Gfx* gfx = *gfxP;

    if ((R_FB_FILTER_TYPE >= FB_FILTER_CVG_RGB) && (R_FB_FILTER_TYPE <= FB_FILTER_CVG_RGB_FOG)) {
        // Visualize coverage
        sGameVisCvg.vis.type = FB_FILTER_TO_CVG_TYPE(R_FB_FILTER_TYPE);
        sGameVisCvg.vis.primColor.r = R_FB_FILTER_PRIM_COLOR(0);
        sGameVisCvg.vis.primColor.g = R_FB_FILTER_PRIM_COLOR(1);
        sGameVisCvg.vis.primColor.b = R_FB_FILTER_PRIM_COLOR(2);
        sGameVisCvg.vis.primColor.a = R_FB_FILTER_A;
        VisCvg_Draw(&sGameVisCvg, &gfx);
    } else if ((R_FB_FILTER_TYPE == FB_FILTER_ZBUF_IA) || (R_FB_FILTER_TYPE == FB_FILTER_ZBUF_RGBA)) {
        // Visualize z-buffer
        sGameVisZBuf.vis.type = (R_FB_FILTER_TYPE == FB_FILTER_ZBUF_RGBA);
        sGameVisZBuf.vis.primColor.r = R_FB_FILTER_PRIM_COLOR(0);
        sGameVisZBuf.vis.primColor.g = R_FB_FILTER_PRIM_COLOR(1);
        sGameVisZBuf.vis.primColor.b = R_FB_FILTER_PRIM_COLOR(2);
        sGameVisZBuf.vis.primColor.a = R_FB_FILTER_A;
        sGameVisZBuf.vis.envColor.r = R_FB_FILTER_ENV_COLOR(0);
        sGameVisZBuf.vis.envColor.g = R_FB_FILTER_ENV_COLOR(1);
        sGameVisZBuf.vis.envColor.b = R_FB_FILTER_ENV_COLOR(2);
        sGameVisZBuf.vis.envColor.a = R_FB_FILTER_A;
        VisZBuf_Draw(&sGameVisZBuf, &gfx, zbuffer);
    } else if (R_FB_FILTER_TYPE == FB_FILTER_MONO) {
        // Monochrome filter
        sGameVisMono.vis.type = 0;
        sGameVisMono.vis.primColor.r = R_FB_FILTER_PRIM_COLOR(0);
        sGameVisMono.vis.primColor.g = R_FB_FILTER_PRIM_COLOR(1);
        sGameVisMono.vis.primColor.b = R_FB_FILTER_PRIM_COLOR(2);
        sGameVisMono.vis.primColor.a = R_FB_FILTER_A;
        sGameVisMono.vis.envColor.r = R_FB_FILTER_ENV_COLOR(0);
        sGameVisMono.vis.envColor.g = R_FB_FILTER_ENV_COLOR(1);
        sGameVisMono.vis.envColor.b = R_FB_FILTER_ENV_COLOR(2);
        sGameVisMono.vis.envColor.a = R_FB_FILTER_A;
        VisMono_Draw(&sGameVisMono, &gfx);
    }

    *gfxP = gfx;
}

void GameState_Noop(GameState* gameState) {
}

void GameState_Draw(GameState* gameState, GraphicsContext* gfxCtx) {
    Gfx* gfx;
    Gfx* gfxHead;

    OPEN_DISPS(gfxCtx);

    gfx = Gfx_Open(gfxHead = POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    if ((R_FB_FILTER_TYPE != 0) && (R_FB_FILTER_ENV_COLOR(3) == 0)) {
        GameState_SetFBFilter(&gfx, gfxCtx->zbuffer);
    }

    if (R_ENABLE_ARENA_DBG < 0) {
        R_ENABLE_ARENA_DBG = 0;
    }

    gSPEndDisplayList(gfx++);
    Gfx_Close(gfxHead, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);

    Debug_DrawText(gfxCtx);

    if (R_ENABLE_ARENA_DBG != 0) {
        SpeedMeter_DrawTimeEntries(&sGameSpeedMeter, gfxCtx);
        SpeedMeter_DrawAllocEntries(&sGameSpeedMeter, gfxCtx, gameState);
    }
}

void GameState_SetFrameBuffer(GraphicsContext* gfxCtx) {
    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);
    gSPSegment(POLY_OPA_DISP++, 0x0F, gfxCtx->curFrameBuffer);
    gSPSegment(POLY_XLU_DISP++, 0x00, NULL);
    gSPSegment(POLY_XLU_DISP++, 0x0F, gfxCtx->curFrameBuffer);
    gSPSegment(OVERLAY_DISP++, 0x00, NULL);
    gSPSegment(OVERLAY_DISP++, 0x0F, gfxCtx->curFrameBuffer);

    CLOSE_DISPS(gfxCtx);
}

void GameState_DrawEnd(GraphicsContext* gfxCtx) {
    Gfx* gfx;
    Gfx* gfxHead;

    OPEN_DISPS(gfxCtx);

    gfx = Gfx_Open(gfxHead = POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, gfx);
    gSPEndDisplayList(gfx++);
    Gfx_Close(gfxHead, gfx);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

void GameState_GetInput(GameState* gameState) {
    PadMgr_GetInput(gameState->input, true);
}

void GameState_Update(GameState* gameState) {
    GraphicsContext* gfxCtx = gameState->gfxCtx;

    GameState_SetFrameBuffer(gameState->gfxCtx);

    gameState->main(gameState);

    if (R_PAUSE_BG_PRERENDER_STATE != PAUSE_BG_PRERENDER_PROCESS) {
        GameState_Draw(gameState, gfxCtx);
        GameState_DrawEnd(gfxCtx);
    }
}

void GameState_IncrementFrameCount(GameState* gameState) {
    GameState_Noop(gameState);
    gameState->frames++;
}

void GameState_InitArena(GameState* gameState, size_t size) {
    GameAlloc* alloc = &gameState->alloc;
    void* buf = GameAlloc_Malloc(alloc, size);

    if (buf) {
        THA_Init(&gameState->tha, buf, size);
        return;
    }

    THA_Init(&gameState->tha, NULL, 0);
    _dbg_hungup("../game.c", 1035);
}

void GameState_Realloc(GameState* gameState, size_t size) {
    GameAlloc* alloc = &gameState->alloc;
    void* gameArena;
    size_t systemMaxFree;
    size_t bytesFree;
    size_t bytesAllocated;
    void* heapStart = gameState->tha.start;

    THA_Destroy(&gameState->tha);
    GameAlloc_Free(alloc, heapStart);
    GetFreeArena(&systemMaxFree, &bytesFree, &bytesAllocated);
    size = ((systemMaxFree - sizeof(ArenaNode)) < size) ? 0 : size;
    if (size == 0) {
        size = systemMaxFree - sizeof(ArenaNode);
    }

    gameArena = GameAlloc_Malloc(alloc, size);
    if (gameArena != NULL) {
        THA_Init(&gameState->tha, gameArena, size);
    } else {
        THA_Init(&gameState->tha, NULL, 0);
        _dbg_hungup("../game.c", 1074);
    }
}

void GameState_Init(GameState* gameState, GameStateFunc init, GraphicsContext* gfxCtx) {
    gameState->gfxCtx = gfxCtx;
    gameState->frames = 0;
    gameState->main = NULL;
    gameState->destroy = NULL;
    gameState->running = true;
    gfxCtx->viMode = gActiveViMode;
    gfxCtx->viConfigFeatures = gViConfigFeatures;
    gfxCtx->xScale = gViConfigXScale;
    gfxCtx->yScale = gViConfigYScale;
    gameState->init = NULL;
    gameState->size = 0;

    {
        s32 requiredScopeTemp;

        GameAlloc_Init(&gameState->alloc);
    }

    GameState_InitArena(gameState, 0x100000);
    GameState_SetFramerateDivisor(gameState, 3);

    init(gameState);

    VisCvg_Init(&sGameVisCvg);
    VisZBuf_Init(&sGameVisZBuf);
    VisMono_Init(&sGameVisMono);
    ViMode_Init(&sGameViMode);
    SpeedMeter_Init(&sGameSpeedMeter);
    Rumble_Init();

    osSendMesg(&gameState->gfxCtx->queue, NULL, OS_MESG_BLOCK);
}

void GameState_Destroy(GameState* gameState) {
    AudioMgr_StopAllSfxExceptSystem();
    Audio_Update();
    osRecvMesg(&gameState->gfxCtx->queue, NULL, OS_MESG_BLOCK);

    if (gameState->destroy != NULL) {
        gameState->destroy(gameState);
    }

    Rumble_Destroy();
    SpeedMeter_Destroy(&sGameSpeedMeter);
    VisCvg_Destroy(&sGameVisCvg);
    VisZBuf_Destroy(&sGameVisZBuf);
    VisMono_Destroy(&sGameVisMono);
    ViMode_Destroy(&sGameViMode);
    THA_Destroy(&gameState->tha);
    GameAlloc_Cleanup(&gameState->alloc);
}

GameStateFunc GameState_GetInit(GameState* gameState) {
    return gameState->init;
}

size_t GameState_GetSize(GameState* gameState) {
    return gameState->size;
}

u32 GameState_IsRunning(GameState* gameState) {
    return gameState->running;
}

s32 GameState_GetArenaSize(GameState* gameState) {
    return THA_GetRemaining(&gameState->tha);
}

s32 func_80173B48(GameState* gameState) {
    s32 result = OS_CYCLES_TO_NSEC(gameState->framerateDivisor * gIrqMgrRetraceTime) - OS_CYCLES_TO_NSEC(gRDPTimeTotal);

    return result;
}
