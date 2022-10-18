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
    /* 0 */ PAUSE_EQUIP_C_LEFT,
    /* 1 */ PAUSE_EQUIP_C_DOWN,
    /* 2 */ PAUSE_EQUIP_C_RIGHT
} PauseEquipCButton;

typedef enum {
    /* 0 */ EQUIP_STATE_MAGIC_ARROW_GROW_ORB,
    /* 1 */ EQUIP_STATE_MAGIC_ARROW_MOVE_TO_BOW_SLOT,
    /* 2 */ EQUIP_STATE_MAGIC_ARROW_HOVER_OVER_BOW_SLOT,
    /* 3 */ EQUIP_STATE_MOVE_TO_C_BTN
} EquipState;

typedef enum {
    /* 0 */ DEBUG_EDITOR_NONE,
    /* 1 */ DEBUG_EDITOR_INVENTORY_INIT,
    /* 2 */ DEBUG_EDITOR_INVENTORY,
    /* 3 */ DEBUG_EDITOR_EVENTS
} DebugEditor;

#define PAUSE_NAME_COLOR_SET_WHITE 0
#define PAUSE_NAME_COLOR_SET_GREY 1

#define PAUSE_CURSOR_COLOR_SET_WHITE 0
#define PAUSE_CURSOR_COLOR_SET_YELLOW 2
#define PAUSE_CURSOR_COLOR_SET_BLUE 4

// To be used for Item-Page cursor and Mask-Page cursor
typedef enum {
    /* 0 */ PAUSE_CURSOR_RESULT_NONE,
    /* 1 */ PAUSE_CURSOR_RESULT_SLOT,
    /* 2 */ PAUSE_CURSOR_RESULT_SPECIAL_POS
} PauseMoveCursorResult;

#define NUM_ITEM_SLOTS 24
#define NUM_MASK_SLOTS 24

#define PAUSE_PROMPT_YES 0
#define PAUSE_PROMPT_NO 4

// NES
void KaleidoScope_MoveCursorToSpecialPos(PlayState* play, s16 cursorSpecialPos);
void KaleidoScope_DrawTexQuadRGBA32(GraphicsContext* gfxCtx, TexturePtr texture, u16 width, u16 height, u16 point);
void KaleidoScope_SetView(PauseContext* pauseCtx, f32 eyeX, f32 eyeY, f32 eyeZ);
void func_80821A04(PlayState* play);

// Map
void KaleidoScope_DrawDungeonMap(PlayState* play);
void KaleidoScope_UpdateDungeonCursor(PlayState* play);
void KaleidoScope_DrawWorldMap(PlayState* play);
void KaleidoScope_UpdateWorldMapCursor(PlayState* play);

// Collect
void KaleidoScope_DrawQuestStatus(PlayState* play);
void KaleidoScope_UpdateQuestCursor(PlayState* play);   

// Item
void KaleidoScope_SetCursorVtx(PauseContext* pauseCtx, u16 index, Vtx* vtx);
void KaleidoScope_DrawItemSelect(PlayState* play);
void KaleidoScope_UpdateItemCursor(PlayState* play);
void KaleidoScope_UpdateItemEquip(PlayState* play);

// Mask
void KaleidoScope_DrawMaskSelect(PlayState* play);
void KaleidoScope_UpdateMaskCursor(PlayState* play);
void KaleidoScope_UpdateMaskEquip(PlayState* play);

// Prompt
void KaleidoScope_UpdatePrompt(PlayState* play);

// Debug
void KaleidoScope_DrawInventoryEditor(PlayState* play);
void KaleidoScope_UpdateInventoryEditor(PlayState* play);

#endif
