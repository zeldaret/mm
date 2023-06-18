#ifndef Z64GAME_H
#define Z64GAME_H

#include "ultra64.h"
#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "padutils.h"
#include "tha.h"
#include "padmgr.h"

struct GraphicsContext;
struct GameState;


typedef void (*GameStateFunc)(struct GameState* gameState);

typedef struct {
    /* 0x00 */ void*         loadedRamAddr;
    /* 0x04 */ uintptr_t     vromStart; // if applicable
    /* 0x08 */ uintptr_t     vromEnd;   // if applicable
    /* 0x0C */ void*         vramStart; // if applicable
    /* 0x10 */ void*         vramEnd;   // if applicable
    /* 0x14 */ UNK_PTR       unk_14;
    /* 0x18 */ GameStateFunc init;    // initializes and executes the given context
    /* 0x1C */ GameStateFunc destroy; // deconstructs the context, and sets the next context to load
    /* 0x20 */ UNK_PTR       unk_20;
    /* 0x24 */ UNK_PTR       unk_24;
    /* 0x28 */ UNK_TYPE      unk_28;
    /* 0x2C */ size_t        instanceSize;
} GameStateOverlay; // size = 0x30

typedef struct GameAllocEntry {
    /* 0x0 */ struct GameAllocEntry* next;
    /* 0x4 */ struct GameAllocEntry* prev;
    /* 0x8 */ size_t size;
    /* 0xC */ u32 unk_0C;
} GameAllocEntry; // size = 0x10

typedef struct GameAlloc {
    /* 0x00 */ GameAllocEntry base;
    /* 0x10 */ GameAllocEntry* head;
} GameAlloc; // size = 0x14

typedef struct GameState {
    /* 0x00 */ struct GraphicsContext* gfxCtx;
    /* 0x04 */ GameStateFunc main;
    /* 0x08 */ GameStateFunc destroy;
    /* 0x0C */ GameStateFunc init; // Usually the current game state's init, though after stopping, the graph thread will look here to determine the next game state to load.
    /* 0x10 */ size_t size;
    /* 0x14 */ Input input[MAXCONTROLLERS];
    /* 0x74 */ TwoHeadArena heap;
    /* 0x84 */ GameAlloc alloc;
    /* 0x98 */ UNK_TYPE1 pad98[0x3];
    /* 0x9B */ u8 running; // If 0, switch to next game state
    /* 0x9C */ u32 frames;
    /* 0xA0 */ u8 padA0[0x2];
    /* 0xA2 */ u8 framerateDivisor;
    /* 0xA3 */ u8 unk_A3;
} GameState; // size = 0xA4


void Game_UpdateFramerateVariables(s32 divisor);
void Game_SetFramerateDivisor(GameState* gameState, s32 divisor);
void GameState_SetFBFilter(Gfx** gfx, void* zbuffer);
void Game_Nop80173534(GameState* gameState);
void GameState_Draw(GameState* gameState, struct GraphicsContext* gfxCtx);
void GameState_SetFrameBuffer(struct GraphicsContext* gfxCtx);
void func_801736DC(struct GraphicsContext* gfxCtx);
void Game_UpdateInput(GameState* gameState);
void Game_Update(GameState* gameState);
void Game_IncrementFrameCount(GameState* gameState);
void GameState_InitArena(GameState* gameState, size_t size);
void GameState_Realloc(GameState* gameState, size_t size);
void GameState_Init(GameState* gameState, GameStateFunc init, struct GraphicsContext* gfxCtx);
void GameState_Destroy(GameState* gameState);
GameStateFunc GameState_GetInit(GameState* gameState);
size_t GameState_GetSize(GameState* gameState);
u32 GameState_IsRunning(GameState* gameState);
s32 GameState_GetArenaSize(GameState* gameState);
s32 func_80173B48(GameState* gameState);

extern s32 gFramerateDivisor;
extern f32 gFramerateDivisorF;
extern f32 gFramerateDivisorHalf;
extern f32 gFramerateDivisorThird;


#define STOP_GAMESTATE(curState)     \
    do {                             \
        GameState* state = curState; \
                                     \
        state->running = false;      \
    } while(0)

#define SET_NEXT_GAMESTATE(curState, nextInit, nextSize) \
    do {                                                 \
        GameState* state = curState;                     \
                                                         \
        (state)->init = nextInit;                        \
        (state)->size = nextSize;                        \
    } while (0)


#endif
