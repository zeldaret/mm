#include <ultra64.h>
#include <global.h>

s32 gFramerateDivisor = 1;
f32 gFramerateDivisorF = 1.0f;
f32 gFramerateDivisorHalf = 1.0f / 2.0f;
f32 gFramerateDivisorThird = 1.0f / 3.0f;

u32 D_801D1510 = 0x0000000A;
u32 D_801D1514[3] = { 0 };

void Game_UpdateFramerateVariables(s32 divisor) {
    gFramerateDivisor = divisor;
    gFramerateDivisorF = (f32) divisor;
    gFramerateDivisorHalf = (f32) (divisor * 0.5f);
    gFramerateDivisorThird = (f32) (divisor / 3.0f);
}

void Game_SetFramerateDivisor(GameState *gameState, s32 divisor) {
    R_UPDATE_RATE = (s16) divisor;
    gameState->framerateDivisor = divisor;
    Game_UpdateFramerateVariables(divisor);
}

void GameState_SetFBFilter(Gfx** gfx, u32 arg1) {
    Gfx* _gfx = *gfx;

    if ((R_FB_FILTER_TYPE > 0) && (R_FB_FILTER_TYPE < 5)) {
        D_801F8010.type = R_FB_FILTER_TYPE;
        D_801F8010.color.red = R_FB_FILTER_PRIM_COLOR(0);
        D_801F8010.color.green = R_FB_FILTER_PRIM_COLOR(1);
        D_801F8010.color.blue = R_FB_FILTER_PRIM_COLOR(2);
        D_801F8010.color.alpha = R_FB_FILTER_A;
        func_80140D10(&D_801F8010, &_gfx, arg1);
    } else {
        if ((R_FB_FILTER_TYPE == 5) || (R_FB_FILTER_TYPE == 6)) {
            D_801F8020.useRgba = (R_FB_FILTER_TYPE == 6);
            D_801F8020.primColor.red = R_FB_FILTER_PRIM_COLOR(0);
            D_801F8020.primColor.green = R_FB_FILTER_PRIM_COLOR(1);
            D_801F8020.primColor.blue = R_FB_FILTER_PRIM_COLOR(2);
            D_801F8020.primColor.alpha = R_FB_FILTER_A;
            D_801F8020.envColor.red = R_FB_FILTER_ENV_COLOR(0);
            D_801F8020.envColor.green = R_FB_FILTER_ENV_COLOR(1);
            D_801F8020.envColor.blue = R_FB_FILTER_ENV_COLOR(2);
            D_801F8020.envColor.alpha = R_FB_FILTER_A;
            func_80142100(&D_801F8020, &_gfx, arg1);
        } else {
            if (R_FB_FILTER_TYPE == 7) {
                sMonoColors.unk_00 = 0;
                sMonoColors.primColor.red = R_FB_FILTER_PRIM_COLOR(0);
                sMonoColors.primColor.green = R_FB_FILTER_PRIM_COLOR(1);
                sMonoColors.primColor.blue = R_FB_FILTER_PRIM_COLOR(2);
                sMonoColors.primColor.alpha = R_FB_FILTER_A;
                sMonoColors.envColor.red = R_FB_FILTER_ENV_COLOR(0);
                sMonoColors.envColor.green = R_FB_FILTER_ENV_COLOR(1);
                sMonoColors.envColor.blue = R_FB_FILTER_ENV_COLOR(2);
                sMonoColors.envColor.alpha = R_FB_FILTER_A;
                VisMono_Draw(&sMonoColors, &_gfx, arg1);
            }
        }
    }

    *gfx = _gfx;
}

void Game_Nop80173534(GameState *ctxt) {
    ;
}

void GameState_Draw(GameState *ctxt, GraphicsContext *gCtxt) {
    Gfx* nextDisplayList;
    Gfx* _polyOpa;
    // Unused vars impact regalloc
    Gfx* temp_t2;
    u32 temp_v1;

    _polyOpa = gCtxt->polyOpa.p;
    nextDisplayList = Graph_GfxPlusOne(gCtxt->polyOpa.p);
    gSPDisplayList(gCtxt->overlay.p++, nextDisplayList);

    if (R_FB_FILTER_TYPE && R_FB_FILTER_ENV_COLOR(3) == 0) {
        GameState_SetFBFilter(&nextDisplayList, (u32) gCtxt->zbuffer);
    }
    
    if (R_ENABLE_ARENA_DBG < 0) {
        R_ENABLE_ARENA_DBG = 0;
    }
    
    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(_polyOpa, nextDisplayList);
    gCtxt->polyOpa.p = nextDisplayList;

lblUnk:; // Label prevents reordering, if(1) around the above block don't seem to help unlike in OoT
    func_800E9F78(gCtxt);

    if (R_ENABLE_ARENA_DBG != 0) {
        SpeedMeter_DrawTimeEntries(&D_801F7FF0, gCtxt);
        SpeedMeter_DrawAllocEntries(&D_801F7FF0, gCtxt, ctxt);
    }
}

void Game_ResetSegments(GraphicsContext *gCtxt) {
    gSPSegment(gCtxt->polyOpa.p++, 0, 0);
    gSPSegment(gCtxt->polyOpa.p++, 0xF, gCtxt->framebuffer);
    gSPSegment(gCtxt->polyXlu.p++, 0, 0);
    gSPSegment(gCtxt->polyXlu.p++, 0xF, gCtxt->framebuffer);
    gSPSegment(gCtxt->overlay.p++, 0, 0);
    gSPSegment(gCtxt->overlay.p++, 0xF, gCtxt->framebuffer);
}

void func_801736DC(GraphicsContext *gCtxt) {
    Gfx* nextDisplayList;
    Gfx* _polyOpa;
    
    nextDisplayList = Graph_GfxPlusOne(_polyOpa = gCtxt->polyOpa.p);
    gSPDisplayList(gCtxt->overlay.p++, nextDisplayList);
    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(_polyOpa, nextDisplayList);
    
    gCtxt->polyOpa.p = nextDisplayList;
}

void Game_UpdateInput(GameState *ctxt) {
    Padmgr_GetInput(ctxt->input, 1);
}

void Game_Update(GameState *ctxt) {
    GraphicsContext* _gCtx;
    _gCtx = ctxt->gfxCtx;

    Game_ResetSegments(ctxt->gfxCtx);

    ctxt->main(ctxt);

    if (R_PAUSE_MENU_MODE != 2) {
        GameState_Draw(ctxt, _gCtx);
        func_801736DC(_gCtx);
    }
}

void Game_IncrementFrameCount(GameState *ctxt) {
    Game_Nop80173534(ctxt);
    ctxt->frames++;
}

void Game_InitHeap(GameState *ctxt, u32 size) {
    GameState *_ctx;
    void *buf;

    _ctx = ctxt;
    buf = GameAlloc_Malloc(&_ctx->alloc, size);

    if (buf) {
        GameStateHeap_Init(&ctxt->heap, buf, size);
        return;
    }

    GameStateHeap_Init(&ctxt->heap, NULL, 0);
    assert_fail("../game.c", 0x40B);
}

void Game_ResizeHeap(GameState *ctxt, u32 size)
{
    GameAlloc *alloc;
    void *buf;
    u32 systemMaxFree;
    u32 bytesFree;
    u32 bytesAllocated;
    void *heapStart;

    heapStart = ctxt->heap.heapStart;
    alloc = &ctxt->alloc;
    GameStateHeap_Clear(&ctxt->heap);
    GameAlloc_Free(alloc, heapStart);
    StartHeap_AnalyzeArena(&systemMaxFree, &bytesFree, &bytesAllocated);
    size = ((systemMaxFree - (sizeof(ArenaNode))) < size) ? (0) : (size);
    if (!size)
    {
        size = systemMaxFree - (sizeof(ArenaNode));
    }

    if (buf = GameAlloc_Malloc(alloc, size))
    {
        GameStateHeap_Init(&ctxt->heap, buf, size);
    }
    else
    {
        GameStateHeap_Init(&ctxt->heap, 0, 0);
        assert_fail("../game.c", 0x432);
    }
}

void Game_StateInit(GameState *ctxt, GameStateFunc gameStateInit, GraphicsContext *gCtxt) {
    ctxt->gfxCtx = gCtxt;
    ctxt->frames = 0U;
    ctxt->main = NULL;
    ctxt->destroy = NULL;
    ctxt->running = 1;
    gCtxt->unk274 = D_801FBB88;
    gCtxt->viConfigFeatures = gViConfigFeatures;
    gCtxt->viConfigXScale = gViConfigXScale;
    gCtxt->viConfigYScale = gViConfigYScale;
    ctxt->nextGameStateInit = NULL;
    ctxt->nextGameStateSize = 0U;

lblUnk:;
    GameAlloc_Init(&ctxt->alloc);
    Game_InitHeap(ctxt, 0x100000);
    Game_SetFramerateDivisor(ctxt, 3);
    
    gameStateInit(ctxt);

    func_80140CE0(&D_801F8010);
    func_801420C0(&D_801F8020);
    func_801418B0(&sMonoColors);
    func_80140898(&D_801F8048);
    func_801773A0(&D_801F7FF0);
    func_8013ED9C();
    
    osSendMesg(&ctxt->gfxCtx->unk5C, NULL, 1);
}

void Game_StateFini(GameState *ctxt) {
    func_80172BC0();
    func_8019E014();
    osRecvMesg(&ctxt->gfxCtx->unk5C, 0, 1);

    if (ctxt->destroy != 0) {
        ctxt->destroy(ctxt);
    }

    func_8013EDD0();
    func_801773C4(&D_801F7FF0);
    func_80140D04(&D_801F8010);
    func_801420F4(&D_801F8020);
    func_80141900(&sMonoColors);
    func_80140900(&D_801F8048);
    GameStateHeap_Clear(&ctxt->heap);
    GameAlloc_Cleanup(&ctxt->alloc);
}

GameStateFunc Game_GetNextStateInit(GameState *ctxt) {
    return ctxt->nextGameStateInit;
}

u32 Game_GetNextStateSize(GameState *ctxt) {
    return ctxt->nextGameStateSize;
}

u32 Game_GetShouldContinue(GameState *ctxt) {
    return ctxt->running;
}

s32 Game_GetHeapFreeSize(GameState *ctxt) {
    return GameStateHeap_GetFreeSize(&ctxt->heap);
}

s32 func_80173B48(GameState *ctxt) {
    s32 result;
    result = OS_CYCLES_TO_NSEC(ctxt->framerateDivisor * sIrqMgrRetraceTime) - OS_CYCLES_TO_NSEC(D_801FBAF0);
    return result;
}
