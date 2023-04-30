#ifndef Z64BOMBERS_NOTEBOOK_H
#define Z64BOMBERS_NOTEBOOK_H

#include "ultra64.h"
#include "io/controller.h"
#include "z64dma.h"

typedef enum BombersNotebookLoadState {
    /* 0 */ BOMBERSNOTEBOOK_LOAD_STATE_NONE,
    /* 1 */ BOMBERSNOTEBOOK_LOAD_STATE_STARTED,
    /* 2 */ BOMBERSNOTEBOOK_LOAD_STATE_DONE
} BombersNotebookLoadState;

typedef struct {
    /* 0x00 */ u8 loadState;
    /* 0x01 */ UNK_TYPE1 pad01[0x3F];
    /* 0x40 */ void* scheduleDmaSegment;
    /* 0x44 */ u32 scheduleDmaSegmentStart;
    /* 0x48 */ u32 scheduleDmaSegmentSize;
    /* 0x4C */ DmaRequest dmaRequest;
    /* 0x6C */ OSMesgQueue loadQueue;
    /* 0x84 */ OSMesg loadMsg[1];
    /* 0x88 */ void* scheduleSegment;
    /* 0x8C */ uintptr_t scheduleSegmentStart;
    /* 0x90 */ size_t scheduleSegmentSize;
    /* 0x94 */ s32 cursorPageRow;
    /* 0x98 */ s32 cursorEntry; // Entries are 3 apart
    /* 0x9C */ s32 cursorPage;
    /* 0xA0 */ UNK_TYPE1 padA0[0x4];
    /* 0xA4 */ s32 scrollAmount;
    /* 0xA8 */ s32 scrollOffset;
} BombersNotebook; // size = 0xAC

void BombersNotebook_Draw(BombersNotebook* this, struct GraphicsContext* gfxCtx);
void BombersNotebook_Update(struct PlayState* play, BombersNotebook* this, Input* input);
void BombersNotebook_Init(BombersNotebook* this);
void BombersNotebook_Destroy(BombersNotebook* this);

#endif
