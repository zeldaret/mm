#include "prevent_bss_reordering.h"
#include "global.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "overlays/gamestates/ovl_select/z_select.h"
#include "overlays/gamestates/ovl_title/z_title.h"

extern u64* D_801FBB94; // gGfxSPTaskOutputBufferPtr
extern u32 D_801FBB98; // gGfxSPTaskOutputBufferSize

FaultAddrConvClient graphFaultAddrConvClient;
FaultClient graphFaultClient;
GfxMasterList* gGfxMasterDL;
CfbInfo D_801F80F8[3];
OSTime lastRenderFrameTimestamp;

// TODO rename get_framebuffer -> SysCfb_GetFbPtr
// TODO rename get_zbuffer -> SysCfb_GetZBuffer
// TODO rename schedContext -> gSchedContext
// TODO rename func_80182C90 -> SysUcode_GetUCodeBoot
// TODO rename func_80182CA0 -> SysUcode_GetUCodeBootSize
// TODO rename func_80182CBC -> SysUcode_GetUCode
// TODO rename func_80182CCC -> SysUcode_GetUCodeData

void* Graph_FaultClient(void) {
    FaultDrawer_DrawText(30, 100, "ShowFrameBuffer PAGE 0/1");
    osViSwapBuffer(get_framebuffer(0));
    osViSetMode(D_801FBB88);
    osViSetSpecialFeatures(0x42); // gamma_disable | dither_fliter_enable_aa_mode3_disable
    Fault_WaitForInput();
    osViSwapBuffer(get_framebuffer(1));
    osViSetMode(D_801FBB88);
    osViSetSpecialFeatures(0x42); // gamma_disable | dither_fliter_enable_aa_mode3_disable
}

// Graph_InitTHGA
void Graph_DlAlloc(TwoHeadGfxArena* arena, Gfx* buffer, s32 size) {
    THGA_Ct(arena, buffer, size);
}

// TODO rename
void Graph_InitTHGA(GraphicsContext* gfxCtx) {
    GfxPool* pool = &gGfxPools[gfxCtx->gfxPoolIdx & 1];

    gGfxMasterDL = &pool->master;
    gSegments[0x0E] = gGfxMasterDL;

    pool->headMagic = GFXPOOL_HEAD_MAGIC;
    pool->tailMagic = GFXPOOL_TAIL_MAGIC;

    Graph_DlAlloc(&gfxCtx->polyOpa, pool->polyOpaBuffer, sizeof(pool->polyOpaBuffer));
    Graph_DlAlloc(&gfxCtx->polyXlu, pool->polyXluBuffer, sizeof(pool->polyXluBuffer));
    Graph_DlAlloc(&gfxCtx->overlay, pool->overlayBuffer, sizeof(pool->overlayBuffer));
    Graph_DlAlloc(&gfxCtx->work, pool->workBuffer, sizeof(pool->workBuffer));
    Graph_DlAlloc(&gfxCtx->debug, pool->debugBuffer, sizeof(pool->debugBuffer));

    gfxCtx->polyOpaBuffer = pool->polyOpaBuffer;
    gfxCtx->polyXluBuffer = pool->polyXluBuffer;
    gfxCtx->overlayBuffer = pool->overlayBuffer;
    gfxCtx->workBuffer = pool->workBuffer;
    gfxCtx->debugBuffer = pool->debugBuffer;

    gfxCtx->curFrameBuffer = get_framebuffer(gfxCtx->framebufferIdx % 2);
    gSegments[0x0F] = gfxCtx->curFrameBuffer;

    gfxCtx->zbuffer = get_zbuffer();

    gSPBranchList(&gGfxMasterDL->unk_2A0[0], pool->polyOpaBuffer);
    gSPBranchList(&gGfxMasterDL->unk_2A0[1], pool->polyXluBuffer);
    gSPBranchList(&gGfxMasterDL->unk_2A0[2], pool->overlayBuffer);
    gSPBranchList(&gGfxMasterDL->unk_2A0[3], pool->workBuffer);
    gSPEndDisplayList(&gGfxMasterDL->unk_2A0[4]);
    gSPBranchList(&gGfxMasterDL->unk_2F8[0], pool->debugBuffer);
}

GameStateOverlay* Graph_GetNextGameState(GameState* gameState) {
    GameStateFunc gameStateInit = Game_GetNextStateInit(gameState);

    if (gameStateInit == (GameStateFunc)TitleSetup_Init) {
        return &gGameStateOverlayTable[0];
    }
    if (gameStateInit == (GameStateFunc)Select_Init) {
        return &gGameStateOverlayTable[1];
    }
    if (gameStateInit == (GameStateFunc)Title_Init) {
        return &gGameStateOverlayTable[2];
    }
    if (gameStateInit == (GameStateFunc)Play_Init) {
        return &gGameStateOverlayTable[3];
    }
    if (gameStateInit == (GameStateFunc)Opening_Init) {
        return &gGameStateOverlayTable[4];
    }
    if (gameStateInit == (GameStateFunc)FileChoose_Init) {
        return &gGameStateOverlayTable[5];
    }
    if (gameStateInit == (GameStateFunc)Daytelop_Init) {
        return &gGameStateOverlayTable[6];
    }
    return NULL;
}

#ifdef NON_MATCHING
// Regalloc differences
void* Graph_FaultAddrConvFunc(void* address, void* param) {
    u32 addr = address;
    GameStateOverlay *gamestateOvl;
    u32 ramConv;
    u32 ramStart;
    u32 diff;
    s32 i;

    for (i = 0; i < graphNumGameStates; i++) {
        gamestateOvl = &gGameStateOverlayTable[i];
        ramStart = gamestateOvl->loadedRamAddr;
        diff = (u32)gamestateOvl->vramEnd - (u32)gamestateOvl->vramStart;
        ramConv = (u32)gamestateOvl->vramStart - ramStart;

        if (gamestateOvl->loadedRamAddr != NULL) {
            if (addr >= ramStart && addr < ramStart + diff) {
                return addr + ramConv;
            }
        }
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/graph/Graph_FaultAddrConvFunc.s")
#endif

void Graph_Init(GraphicsContext* gfxCtx) {
    bzero(gfxCtx, sizeof(GraphicsContext));
    gfxCtx->gfxPoolIdx = 0;
    gfxCtx->framebufferIdx = 0;
    gfxCtx->viMode = NULL;
    gfxCtx->viConfigFeatures = gViConfigFeatures;
    gfxCtx->xScale = gViConfigXScale;
    gfxCtx->yScale = gViConfigYScale;
    osCreateMesgQueue(&gfxCtx->queue, gfxCtx->msgBuff, ARRAY_COUNT(gfxCtx->msgBuff));
    Fault_AddClient(&graphFaultClient, (fault_client_func)Graph_FaultClient, NULL, NULL);
    Fault_AddAddrConvClient(&graphFaultAddrConvClient, (fault_address_converter_func )Graph_FaultAddrConvFunc, NULL);
}

void Graph_Destroy(GraphicsContext* gfxCtx) {
    Fault_RemoveClient(&graphFaultClient);
    Fault_RemoveAddrConvClient(&graphFaultAddrConvClient);
}

// Graph_TaskSet00
void Graph_Render(GraphicsContext* gfxCtx, GameState* gameState) {
    static s32 D_801D1510 = 10; // retry count?
    static s32 D_801D1514 = 0;

    OSTask_t* task = &gfxCtx->task.list.t;
    OSScTask* scTask = &gfxCtx->task;
    OSTimer timer;
    OSMesg msg;
    CfbInfo* cfb;

retry:
    osSetTimer(&timer, 140625000, 0, &gfxCtx->queue, (OSMesg)666);
    osRecvMesg(&gfxCtx->queue, &msg, OS_MESG_BLOCK);
    osStopTimer(&timer);

    if (msg == (OSMesg)666) {
        osSyncPrintf("GRAPH SP TIMEOUT\n");
        if (D_801D1510 >= 0) {
            D_801D1510--;
            Sched_SendGfxCancelMsg(&schedContext);
            goto retry;
        } else {
            // graph.c: No more! die!
            osSyncPrintf("graph.c:もうダメ！死ぬ！\n");
            Fault_AddHungupAndCrashImpl("RCP is HUNG UP!!", "Oh! MY GOD!!");
        }
    }
    gfxCtx->unk_2FC = gGfxMasterDL;
    if (gfxCtx->callback != NULL) {
        gfxCtx->callback(gfxCtx, gfxCtx->callbackParam);
    }

    task->type = 1;
    task->flags = 4;
    task->ucode_boot = func_80182C90();
    task->ucode_boot_size = func_80182CA0();
    task->ucode = func_80182CBC();
    task->ucode_data = func_80182CCC();
    task->ucode_size = 0x1000;
    task->ucode_data_size = 0x800;
    task->dram_stack = (u64*)gGfxSPTaskStack;
    task->dram_stack_size = sizeof(gGfxSPTaskStack);
    task->output_buff = D_801FBB94; // gGfxSPTaskOutputBufferPtr;
    task->output_buff_size = D_801FBB98; // gGfxSPTaskOutputBufferSize;
    task->data_ptr = (u64*)gGfxMasterDL;
    task->data_size = 0;
    task->yield_data_ptr = (u64*)gGfxSPTaskYieldBuffer;
    task->yield_data_size = 0xC00;

    scTask->next = NULL;
    scTask->flags = OS_SC_RCP_MASK | OS_SC_SWAPBUFFER | OS_SC_LAST_TASK;

    if (SREG(33) & 1) {
        SREG(33) &= ~1;
        scTask->flags &= ~OS_SC_SWAPBUFFER;
        gfxCtx->framebufferIdx--;
    }

    scTask->msgQ = &gfxCtx->queue;
    scTask->msg = NULL;

    { s32 pad; }

    cfb = &D_801F80F8[D_801D1514];
    D_801D1514 = (D_801D1514 + 1) % 3;

    cfb->fb1 = gfxCtx->curFrameBuffer;
    cfb->swapBuffer = gfxCtx->curFrameBuffer;

    if (gfxCtx->unk_2EA != 0) {
        gfxCtx->unk_2EA = 0;
        cfb->viMode = gfxCtx->viMode;
        cfb->features = gfxCtx->viConfigFeatures;
        cfb->xScale = gfxCtx->xScale;
        cfb->yScale = gfxCtx->yScale;
    } else {
        cfb->viMode = NULL;
    }
    cfb->unk_10 = 0;
    cfb->updateRate = gameState->framerateDivisor;

    scTask->framebuffer = cfb;

    while (gfxCtx->queue.validCount != 0) {
        osRecvMesg(&gfxCtx->queue, NULL, OS_MESG_NOBLOCK);
    }

    gfxCtx->schedMsgQ = &schedContext.cmdQ;
    osSendMesg(&schedContext.cmdQ, scTask, OS_MESG_BLOCK);
    Sched_SendEntryMsg(&schedContext);
}

void Graph_FrameSetup(GameState* state) {
    Game_UpdateInput(state);
    Game_IncrementFrameCount(state);
    if (SREG(20) < 3) {
        func_8019E014();
    }
}

// Graph_Update
void Graph_RenderFrame(GraphicsContext* gfxCtx, GameState* gameState) {
    u32 problem;

    gameState->unk_A3 = 0;
    Graph_InitTHGA(gfxCtx);

    Game_Update(gameState);

    OPEN_DISPS(gfxCtx);

    gSPEndDisplayList(WORK_DISP++);
    gSPEndDisplayList(POLY_OPA_DISP++);
    gSPEndDisplayList(POLY_XLU_DISP++);
    gSPEndDisplayList(OVERLAY_DISP++);
    gSPEndDisplayList(DEBUG_DISP++);

    CLOSE_DISPS(gfxCtx);

    {
        Gfx* gfx = &gGfxMasterDL->unk_0[0];

        gSPSegment(gfx++, 0x0E, gGfxMasterDL);
        gSPDisplayList(gfx++, &D_0E000000.unk_2A0[3]);
        gSPDisplayList(gfx++, &D_0E000000.unk_2A0[0]);
        gSPDisplayList(gfx++, &D_0E000000.unk_2A0[1]);
        gSPDisplayList(gfx++, &D_0E000000.unk_2A0[2]);
        gSPDisplayList(gfx++, &D_0E000000.unk_2F8[0]);

        gDPPipeSync(gfx++);
        gDPFullSync(gfx++);
        gSPEndDisplayList(gfx++);
    }

    problem = false;

    {
        GfxPool* pool = &gGfxPools[gfxCtx->gfxPoolIdx & 1];

        if (pool->headMagic != GFXPOOL_HEAD_MAGIC) {
            Fault_AddHungupAndCrash("../graph.c", 1054);
        }
        if (pool->tailMagic != GFXPOOL_TAIL_MAGIC) {
            Fault_AddHungupAndCrash("../graph.c", 1066);
        }
    }

    if (THGA_IsCrash(&gfxCtx->polyOpa)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->polyXlu)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->overlay)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->work)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->debug)) {
        problem = true;
    }

    if (!problem) {
        Graph_Render(gfxCtx, gameState);
        gfxCtx->gfxPoolIdx++;
        gfxCtx->framebufferIdx++;
    }

    {
        OSTime time = osGetTime();

        D_801FBAE8 = sRSPGFXTotalTime;
        D_801FBAE0 = gRSPAudioTotalTime;
        D_801FBAF0 = gRDPTotalTime;
        sRSPGFXTotalTime = 0;
        gRSPAudioTotalTime = 0;
        gRDPTotalTime = 0;

        if (lastRenderFrameTimestamp != 0) {
            lastRenderFrameDuration = time - lastRenderFrameTimestamp;
        }
        lastRenderFrameTimestamp = time;
    }
}

void Graph_DoFrame(GraphicsContext* gfxCtx, GameState* gameState) {
    gameState->unk_A3 = 0;

    Graph_FrameSetup(gameState);
    Graph_RenderFrame(gfxCtx, gameState);
}

void Graph_ThreadEntry(void* arg) {
    GraphicsContext gfxCtx;
    GameStateOverlay* nextOvl = &gGameStateOverlayTable[0];
    GameStateOverlay* ovl;
    GameState* gameState;
    u32 size;
    s32 pad[2];

    sys_cfb_zbufl = StartHeap_Alloc(sizeof(*sys_cfb_zbufl) + sizeof(*sys_cfb_wbufl) + 64 - 1);
    sys_cfb_zbufl = (void*)ALIGN64((u32)sys_cfb_zbufl);

    sys_cfb_wbufl = (void*)((u8*)sys_cfb_zbufl + sizeof(*sys_cfb_zbufl));

    sys_cfb_fifol = StartHeap_Alloc(sizeof(*sys_cfb_fifol));
    D_801FBBC4 = sys_cfb_fifol;

    D_801FBBB0 = (u8*)sys_cfb_fifol + sizeof(*sys_cfb_fifol);
    D_801FBBC8 = (u8*)D_801FBBC4 + sizeof(*sys_cfb_fifol);

    func_80178978();
    Fault_SetFB(D_801FBB90, SCREEN_WIDTH, SCREEN_HEIGHT);
    Graph_Init(&gfxCtx);

    while (nextOvl) {
        ovl = nextOvl;

        DLF_LoadGameState(ovl);

        size = ovl->instanceSize;

        func_800809F4(ovl->vromStart);

        gameState = StartHeap_Alloc(size);

        bzero(gameState, size);
        Game_StateInit(gameState, ovl->init, &gfxCtx);

        while (Game_GetShouldContinue(gameState)) {
            Graph_DoFrame(&gfxCtx, gameState);
        }

        nextOvl = Graph_GetNextGameState(gameState);

        if (size) {}

        Game_StateFini(gameState);
        StartHeap_Free(gameState);

        DLF_FreeGameState(ovl);
    }
    Graph_Destroy(&gfxCtx);
}
