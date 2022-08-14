#ifndef Z_KALEIDO_SCOPE_H
#define Z_KALEIDO_SCOPE_H

#include "global.h"

typedef enum {
    /* 0x00 */ PAUSE_ITEM,
    /* 0x01 */ PAUSE_MAP,
    /* 0x02 */ PAUSE_QUEST,
    /* 0x03 */ PAUSE_MASK,
    /* 0x04 */ PAUSE_WORLD_MAP
} PauseMenuPage;

typedef enum {
  /* 0 */ DEBUG_EDITOR_NONE,
  /* 1 */ DEBUG_EDITOR_INVENTORY_INIT,
  /* 2 */ DEBUG_EDITOR_INVENTORY,
  /* 3 */ DEBUG_EDITOR_EVENTS
} DebugEditor;

// Debug
void KaleidoScope_DrawInventoryEditor(PlayState* play);
void KaleidoScope_UpdateInventoryEditor(PlayState* play);

#endif
