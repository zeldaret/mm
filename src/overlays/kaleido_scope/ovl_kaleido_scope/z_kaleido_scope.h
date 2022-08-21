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
    /* 0x00 */ PAUSE_STATE_0,
    /* 0x01 */ PAUSE_STATE_1,
    /* 0x02 */ PAUSE_STATE_2,
    /* 0x03 */ PAUSE_STATE_3,
    /* 0x04 */ PAUSE_STATE_4,
    /* 0x05 */ PAUSE_STATE_5,
    /* 0x06 */ PAUSE_STATE_6,
    /* 0x07 */ PAUSE_STATE_7,
    /* 0x0A */ PAUSE_STATE_A = 0xA,
    /* 0x0B */ PAUSE_STATE_B,
    /* 0x0C */ PAUSE_STATE_C,
    /* 0x0D */ PAUSE_STATE_D,
    /* 0x0E */ PAUSE_STATE_E,
    /* 0x0F */ PAUSE_STATE_F,
    /* 0x10 */ PAUSE_STATE_10,
    /* 0x11 */ PAUSE_STATE_11,
    /* 0x12 */ PAUSE_STATE_12,
    /* 0x15 */ PAUSE_STATE_15 = 0x15,
    /* 0x16 */ PAUSE_STATE_16,
    /* 0x17 */ PAUSE_STATE_17,
    /* 0x18 */ PAUSE_STATE_18,
    /* 0x19 */ PAUSE_STATE_19,
    /* 0x1A */ PAUSE_STATE_1A,
    /* 0x1B */ PAUSE_STATE_1B
} PauseState;

typedef enum {
    /* 0 */ PAUSE_EQUIP_C_LEFT,
    /* 1 */ PAUSE_EQUIP_C_DOWN,
    /* 2 */ PAUSE_EQUIP_C_RIGHT
} PauseEquipCButton;

typedef enum {
  /* 0 */ DEBUG_EDITOR_NONE,
  /* 1 */ DEBUG_EDITOR_INVENTORY_INIT,
  /* 2 */ DEBUG_EDITOR_INVENTORY,
  /* 3 */ DEBUG_EDITOR_EVENTS
} DebugEditor;

typedef enum {
    /* 0 */ EQUIP_STATE_MAGIC_ARROW_GROW_ORB,
    /* 1 */ EQUIP_STATE_MAGIC_ARROW_MOVE_TO_BOW_SLOT,
    /* 2 */ EQUIP_STATE_MAGIC_ARROW_HOVER_OVER_BOW_SLOT,
    /* 3 */ EQUIP_STATE_MOVE_TO_C_BTN
} EquipState;

#define SLOT_MASK_FIRST 24

#define PAUSE_PROMPT_YES 0
#define PAUSE_PROMPT_NO 4

// NES
void KaleidoScope_MoveCursorToSpecialPos(PlayState* play, s16 cursorSpecialPos);
void KaleidoScope_DrawQuadTextureRGBA32(GraphicsContext* gfxCtx, void* texture, u16 width, u16 height, u16 point);
void func_80821A04(PlayState* play);

// Map
void func_8081D6DC(PlayState*);
void func_8081E118(PlayState* play);
void KaleidoScope_DrawWorldMap(PlayState* play);
void func_8081FB1C(PlayState* play);

// Collect
void KaleidoScope_DrawQuestStatus(PlayState* play);
void KaleidoScope_UpdateQuestStatus(PlayState* play);

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
