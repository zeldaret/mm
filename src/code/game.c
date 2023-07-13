#include "global.h"
#include "audiomgr.h"
#include "idle.h"
#include "system_malloc.h"
#include "z64debug_text.h"
#include "z64rumble.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

s32 gFramerateDivisor = 1;
f32 gFramerateDivisorF = 1.0f;
f32 gFramerateDivisorHalf = 1.0f / 2.0f;
f32 gFramerateDivisorThird = 1.0f / 3.0f;

void Game_UpdateFramerateVariables(s32 divisor) {
    gFramerateDivisor = divisor;
    gFramerateDivisorF = divisor;
    gFramerateDivisorHalf = divisor / 2.0f;
    gFramerateDivisorThird = divisor / 3.0f;
}

void Game_SetFramerateDivisor(GameState* gameState, s32 divisor) {
    R_UPDATE_RATE = (s16)divisor;
    gameState->framerateDivisor = divisor;
    Game_UpdateFramerateVariables(divisor);
}

void GameState_SetFBFilter(Gfx** gfx, void* zbuffer) {
    Gfx* dlist = *gfx;

    if ((R_FB_FILTER_TYPE > 0) && (R_FB_FILTER_TYPE < 5)) {
        D_801F8010.type = R_FB_FILTER_TYPE;
        D_801F8010.color.r = R_FB_FILTER_PRIM_COLOR(0);
        D_801F8010.color.g = R_FB_FILTER_PRIM_COLOR(1);
        D_801F8010.color.b = R_FB_FILTER_PRIM_COLOR(2);
        D_801F8010.color.a = R_FB_FILTER_A;
        VisCvg_Draw(&D_801F8010, &dlist);
    } else if ((R_FB_FILTER_TYPE == 5) || (R_FB_FILTER_TYPE == 6)) {
        sVisZbuf.useRgba = (R_FB_FILTER_TYPE == 6);
        sVisZbuf.primColor.r = R_FB_FILTER_PRIM_COLOR(0);
        sVisZbuf.primColor.g = R_FB_FILTER_PRIM_COLOR(1);
        sVisZbuf.primColor.b = R_FB_FILTER_PRIM_COLOR(2);
        sVisZbuf.primColor.a = R_FB_FILTER_A;
        sVisZbuf.envColor.r = R_FB_FILTER_ENV_COLOR(0);
        sVisZbuf.envColor.g = R_FB_FILTER_ENV_COLOR(1);
        sVisZbuf.envColor.b = R_FB_FILTER_ENV_COLOR(2);
        sVisZbuf.envColor.a = R_FB_FILTER_A;
        VisZbuf_Draw(&sVisZbuf, &dlist, zbuffer);
    } else if (R_FB_FILTER_TYPE == 7) {
        sMonoColors.unk_00 = 0;
        sMonoColors.primColor.r = R_FB_FILTER_PRIM_COLOR(0);
        sMonoColors.primColor.g = R_FB_FILTER_PRIM_COLOR(1);
        sMonoColors.primColor.b = R_FB_FILTER_PRIM_COLOR(2);
        sMonoColors.primColor.a = R_FB_FILTER_A;
        sMonoColors.envColor.r = R_FB_FILTER_ENV_COLOR(0);
        sMonoColors.envColor.g = R_FB_FILTER_ENV_COLOR(1);
        sMonoColors.envColor.b = R_FB_FILTER_ENV_COLOR(2);
        sMonoColors.envColor.a = R_FB_FILTER_A;
        VisMono_Draw(&sMonoColors, &dlist);
    }

    *gfx = dlist;
}

void Game_Nop80173534(GameState* gameState) {
}

void GameState_Draw(GameState* gameState, GraphicsContext* gfxCtx) {
    Gfx* nextDisplayList;
    Gfx* polyOpa;

    OPEN_DISPS(gfxCtx);

    nextDisplayList = Graph_GfxPlusOne(polyOpa = POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);

    if (R_FB_FILTER_TYPE && R_FB_FILTER_ENV_COLOR(3) == 0) {
        GameState_SetFBFilter(&nextDisplayList, gfxCtx->zbuffer);
    }

    if (R_ENABLE_ARENA_DBG < 0) {
        R_ENABLE_ARENA_DBG = 0;
    }

    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(polyOpa, nextDisplayList);
    POLY_OPA_DISP = nextDisplayList;

    CLOSE_DISPS(gfxCtx);

    Debug_DrawText(gfxCtx);

    if (R_ENABLE_ARENA_DBG != 0) {
        SpeedMeter_DrawTimeEntries(&D_801F7FF0, gfxCtx);
        SpeedMeter_DrawAllocEntries(&D_801F7FF0, gfxCtx, gameState);
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

void func_801736DC(GraphicsContext* gfxCtx) {
    Gfx* nextDisplayList;
    Gfx* polyOpa;

    OPEN_DISPS(gfxCtx);

    nextDisplayList = Graph_GfxPlusOne(polyOpa = gfxCtx->polyOpa.p);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);
    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(polyOpa, nextDisplayList);

    POLY_OPA_DISP = nextDisplayList;

    CLOSE_DISPS(gfxCtx);
}

void Game_UpdateInput(GameState* gameState) {
    PadMgr_GetInput(gameState->input, true);
}

void Game_Update(GameState* gameState) {
    GraphicsContext* gfxCtx = gameState->gfxCtx;

    GameState_SetFrameBuffer(gameState->gfxCtx);

    gameState->main(gameState);

    if (R_PAUSE_BG_PRERENDER_STATE != PAUSE_BG_PRERENDER_PROCESS) {
        GameState_Draw(gameState, gfxCtx);
        func_801736DC(gfxCtx);
    }
}

void Game_IncrementFrameCount(GameState* gameState) {
    Game_Nop80173534(gameState);
    gameState->frames++;
}

void GameState_InitArena(GameState* gameState, size_t size) {
    GameAlloc* alloc = &gameState->alloc;
    void* buf = GameAlloc_Malloc(alloc, size);

    if (buf) {
        THA_Init(&gameState->heap, buf, size);
        return;
    }

    THA_Init(&gameState->heap, NULL, 0);
    __assert("../game.c", 1035);
}

void GameState_Realloc(GameState* gameState, size_t size) {
    GameAlloc* alloc;
    void* gameArena;
    size_t systemMaxFree;
    size_t bytesFree;
    size_t bytesAllocated;
    void* heapStart;

    heapStart = gameState->heap.start;
    alloc = &gameState->alloc;
    THA_Destroy(&gameState->heap);
    GameAlloc_Free(alloc, heapStart);
    SystemArena_GetSizes(&systemMaxFree, &bytesFree, &bytesAllocated);
    size = ((systemMaxFree - (sizeof(ArenaNode))) < size) ? (0) : (size);
    if (size == 0) {
        size = systemMaxFree - (sizeof(ArenaNode));
    }

    if ((gameArena = GameAlloc_Malloc(alloc, size)) != NULL) {
        THA_Init(&gameState->heap, gameArena, size);
    } else {
        THA_Init(&gameState->heap, 0, 0);
        __assert("../game.c", 1074);
    }
}

void GameState_Init(GameState* gameState, GameStateFunc init, GraphicsContext* gfxCtx) {
    gameState->gfxCtx = gfxCtx;
    gameState->frames = 0;
    gameState->main = NULL;
    gameState->destroy = NULL;
    gameState->running = 1;
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
    Game_SetFramerateDivisor(gameState, 3);

    init(gameState);

    VisCvg_Init(&D_801F8010);
    VisZbuf_Init(&sVisZbuf);
    VisMono_Init(&sMonoColors);
    ViMode_Init(&D_801F8048);
    func_801773A0(&D_801F7FF0);
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
    func_801773C4(&D_801F7FF0);
    VisCvg_Destroy(&D_801F8010);
    VisZbuf_Destroy(&sVisZbuf);
    VisMono_Destroy(&sMonoColors);
    ViMode_Destroy(&D_801F8048);
    THA_Destroy(&gameState->heap);
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
    return THA_GetRemaining(&gameState->heap);
}

s32 func_80173B48(GameState* gameState) {
    s32 result = OS_CYCLES_TO_NSEC(gameState->framerateDivisor * sIrqMgrRetraceTime) - OS_CYCLES_TO_NSEC(D_801FBAF0);

    return result;
}
