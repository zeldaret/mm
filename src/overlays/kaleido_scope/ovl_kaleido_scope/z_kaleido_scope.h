#ifndef Z_KALEIDO_SCOPE_H
#define Z_KALEIDO_SCOPE_H

#include "global.h"

#define PAUSE_ITEM_NONE 999

#define PAUSE_CURSOR_PAGE_LEFT 10
#define PAUSE_CURSOR_PAGE_RIGHT 11

typedef enum {
    /* 0 */ PAUSE_ITEM,
    /* 1 */ PAUSE_MAP,
    /* 2 */ PAUSE_QUEST,
    /* 3 */ PAUSE_MASK,
    /* 4 */ PAUSE_WORLD_MAP
} PauseMenuPage;

typedef enum {
  /* 0 */ DEBUG_EDITOR_NONE,
  /* 1 */ DEBUG_EDITOR_INVENTORY_INIT,
  /* 2 */ DEBUG_EDITOR_INVENTORY,
  /* 3 */ DEBUG_EDITOR_EVENTS
} DebugEditor;

// NES
void func_80821984(PlayState* play, s16 cursorSpecialPos);
void KaleidoScope_DrawQuadTextureRGBA32(GraphicsContext* gfxCtx, void* texture, u16 width, u16 height, u16 point);

// Map
void func_8081FB1C(PlayState* play);

// Item
void KaleidoScope_DrawItemSelect(PlayState* play);
void KaleidoScope_UpdateItemEquip(PlayState* play);

// Debug
void KaleidoScope_DrawInventoryEditor(PlayState* play);
void KaleidoScope_UpdateInventoryEditor(PlayState* play);

#endif
