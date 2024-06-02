#ifndef GAMEALLOC_H
#define GAMEALLOC_H

#include "ultra64.h"

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

void GameAlloc_Log(GameAlloc* this);
void* GameAlloc_Malloc(GameAlloc* this, size_t size);
void GameAlloc_Free(GameAlloc* this, void* data);
void GameAlloc_Cleanup(GameAlloc* this);
void GameAlloc_Init(GameAlloc* this);

#endif
