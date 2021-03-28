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

void Game_SetFramerateDivisor(GameState* this, s32 divisor) {
    R_UPDATE_RATE = (s16) divisor;
    this->framerateDivisor = divisor;
    Game_UpdateFramerateVariables(divisor);
}

void GameState_SetFBFilter(Gfx** gfx, u32 arg1) {
    Gfx* gfxP = *gfx;

    if ((R_FB_FILTER_TYPE > 0) && (R_FB_FILTER_TYPE < 5)) {
        D_801F8010.type = R_FB_FILTER_TYPE;
        D_801F8010.color.r = R_FB_FILTER_PRIM_COLOR(0);
        D_801F8010.color.g = R_FB_FILTER_PRIM_COLOR(1);
        D_801F8010.color.b = R_FB_FILTER_PRIM_COLOR(2);
        D_801F8010.color.a = R_FB_FILTER_A;
        func_80140D10(&D_801F8010, &gfxP, arg1);
    } else {
        if ((R_FB_FILTER_TYPE == 5) || (R_FB_FILTER_TYPE == 6)) {
            D_801F8020.useRgba = (R_FB_FILTER_TYPE == 6);
            D_801F8020.primColor.r = R_FB_FILTER_PRIM_COLOR(0);
            D_801F8020.primColor.g = R_FB_FILTER_PRIM_COLOR(1);
            D_801F8020.primColor.b = R_FB_FILTER_PRIM_COLOR(2);
            D_801F8020.primColor.a = R_FB_FILTER_A;
            D_801F8020.envColor.r = R_FB_FILTER_ENV_COLOR(0);
            D_801F8020.envColor.g = R_FB_FILTER_ENV_COLOR(1);
            D_801F8020.envColor.b = R_FB_FILTER_ENV_COLOR(2);
            D_801F8020.envColor.a = R_FB_FILTER_A;
            func_80142100(&D_801F8020, &gfxP, arg1);
        } else {
            if (R_FB_FILTER_TYPE == 7) {
                sMonoColors.unk_00 = 0;
                sMonoColors.primColor.r = R_FB_FILTER_PRIM_COLOR(0);
                sMonoColors.primColor.g = R_FB_FILTER_PRIM_COLOR(1);
                sMonoColors.primColor.b = R_FB_FILTER_PRIM_COLOR(2);
                sMonoColors.primColor.a = R_FB_FILTER_A;
                sMonoColors.envColor.r = R_FB_FILTER_ENV_COLOR(0);
                sMonoColors.envColor.g = R_FB_FILTER_ENV_COLOR(1);
                sMonoColors.envColor.b = R_FB_FILTER_ENV_COLOR(2);
                sMonoColors.envColor.a = R_FB_FILTER_A;
                VisMono_Draw(&sMonoColors, &gfxP, arg1);
            }
        }
    }

    *gfx = gfxP;
}

void Game_Nop80173534(GameState* this) {
    ;
}

void GameState_Draw(GameState* this, GraphicsContext *gfxCtx) {
    Gfx* nextDisplayList;
    Gfx* polyOpa;
    
    OPEN_DISPS(gfxCtx);

    nextDisplayList = Graph_GfxPlusOne(polyOpa = POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);

    if (R_FB_FILTER_TYPE && R_FB_FILTER_ENV_COLOR(3) == 0) {
        GameState_SetFBFilter(&nextDisplayList, (u32) gfxCtx->zbuffer);
    }

    if (R_ENABLE_ARENA_DBG < 0) {
        R_ENABLE_ARENA_DBG = 0;
    }

    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(polyOpa, nextDisplayList);
    POLY_OPA_DISP = nextDisplayList;

label:
    func_800E9F78(gfxCtx);

    if (R_ENABLE_ARENA_DBG != 0) {
        SpeedMeter_DrawTimeEntries(&D_801F7FF0, gfxCtx);
        SpeedMeter_DrawAllocEntries(&D_801F7FF0, gfxCtx, this);
    }

    CLOSE_DISPS(gfxCtx);
}

void GameState_SetFrameBuffer(GraphicsContext *gfxCtx) {

    OPEN_DISPS(gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0, NULL);
    gSPSegment(POLY_OPA_DISP++, 0xF, gfxCtx->framebuffer);
    gSPSegment(POLY_XLU_DISP++, 0, NULL);
    gSPSegment(POLY_XLU_DISP++, 0xF, gfxCtx->framebuffer);
    gSPSegment(OVERLAY_DISP++, 0, NULL);
    gSPSegment(OVERLAY_DISP++, 0xF, gfxCtx->framebuffer);

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

void Game_UpdateInput(GameState* this) {
    Padmgr_GetInput(this->input, 1);
}

void Game_Update(GameState* this) {
    GraphicsContext* gfxCtx = this->gfxCtx;

    GameState_SetFrameBuffer(this->gfxCtx);

    this->main(this);

    if (R_PAUSE_MENU_MODE != 2) {
        GameState_Draw(this, gfxCtx);
        func_801736DC(gfxCtx);
    }
}

void Game_IncrementFrameCount(GameState* this) {
    Game_Nop80173534(this);
    this->frames++;
}

void GameState_InitArena(GameState* this, size_t size) {
    GameAlloc* alloc;
    void* arena;

    alloc = &this->alloc;

    arena = GameAlloc_Malloc(alloc, size);

    if (arena != NULL) {
        THA_Ct(&this->heap, arena, size);
        return;
    }

    THA_Ct(&this->heap, NULL, 0);
    assert_fail("../game.c", 1035);
}

void GameState_Realloc(GameState* this, size_t size) {
    GameAlloc* alloc;
    void* gameArena;
    size_t systemMaxFree;
    size_t bytesFree;
    size_t bytesAllocated;
    void* heapStart;

    heapStart = this->heap.bufp;
    alloc = &this->alloc;
    THA_Dt(&this->heap);
    GameAlloc_Free(alloc, heapStart);
    StartHeap_AnalyzeArena(&systemMaxFree, &bytesFree, &bytesAllocated);
    size = ((systemMaxFree - (sizeof(ArenaNode))) < size) ? (0) : (size);
    if (size == 0) {
        size = systemMaxFree - (sizeof(ArenaNode));
    }

    if (gameArena = GameAlloc_Malloc(alloc, size), gameArena != NULL) {
        THA_Ct(&this->heap, gameArena, size);
    } else {
        THA_Ct(&this->heap, NULL, 0);
        assert_fail("../game.c", 1074);
    }
}

void GameState_Init(GameState* this, GameStateFunc init, GraphicsContext* gfxCtx) {
    this->gfxCtx = gfxCtx;
    this->frames = 0U;
    this->main = NULL;
    this->destroy = NULL;
    this->running = 1;
    gfxCtx->viMode = D_801FBB88;
    gfxCtx->viConfigFeatures = gViConfigFeatures;
    gfxCtx->viConfigXScale = gViConfigXScale;
    gfxCtx->viConfigYScale = gViConfigYScale;
    this->init = NULL;
    this->size = 0U;

lblUnk:;
    GameAlloc_Init(&this->alloc);
    GameState_InitArena(this, 0x100000);
    Game_SetFramerateDivisor(this, 3);

    init(this);

    func_80140CE0(&D_801F8010);
    func_801420C0(&D_801F8020);
    func_801418B0(&sMonoColors);
    func_80140898(&D_801F8048);
    func_801773A0(&D_801F7FF0);
    func_8013ED9C();

    osSendMesg(&this->gfxCtx->unk5C, NULL, OS_MESG_BLOCK);
}

void GameState_Destroy(GameState* this) {
    func_80172BC0();
    func_8019E014();
    osRecvMesg(&this->gfxCtx->unk5C, NULL, OS_MESG_BLOCK);

    if (this->destroy != NULL) {
        this->destroy(this);
    }

    func_8013EDD0();
    func_801773C4(&D_801F7FF0);
    func_80140D04(&D_801F8010);
    func_801420F4(&D_801F8020);
    func_80141900(&sMonoColors);
    func_80140900(&D_801F8048);
    THA_Dt(&this->heap);
    GameAlloc_Cleanup(&this->alloc);
}

GameStateFunc GameState_GetInit(GameState* this) {
    return this->init;
}

size_t Game_GetNextStateSize(GameState* this) {
    return this->size;
}

u32 GameState_IsRunning(GameState* this) {
    return this->running;
}

s32 GameState_GetArenaSize(GameState* this) {
    return THA_GetSize(&this->heap);
}

s32 func_80173B48(GameState* this) {
    s32 result = OS_CYCLES_TO_NSEC(this->framerateDivisor * sIrqMgrRetraceTime) - OS_CYCLES_TO_NSEC(D_801FBAF0);
    
    return result;
}
