#ifndef GRAPH_H
#define GRAPH_H

#include "ultra64.h"

#include "stdint.h"

struct GameState;
struct GfxMasterList;
struct GraphicsContext;
union TwoHeadGfxArena;

void Graph_FaultClient(void);
void Graph_InitTHGA(union TwoHeadGfxArena* arena, Gfx* buffer, s32 size);
void Graph_SetNextGfxPool(struct GraphicsContext* gfxCtx);
struct GameStateOverlay* Graph_GetNextGameState(struct GameState* gameState);
uintptr_t Graph_FaultAddrConv(uintptr_t address, void* param);
void Graph_Init(struct GraphicsContext* gfxCtx);
void Graph_Destroy(struct GraphicsContext* gfxCtx);
void Graph_TaskSet00(struct GraphicsContext* gfxCtx, struct GameState* gameState);
void Graph_UpdateGame(struct GameState* gameState);
void Graph_ExecuteAndDraw(struct GraphicsContext* gfxCtx, struct GameState* gameState);
void Graph_Update(struct GraphicsContext* gfxCtx, struct GameState* gameState);
void Graph_ThreadEntry(void* arg);

extern struct GfxMasterList* gGfxMasterDL;

#endif
