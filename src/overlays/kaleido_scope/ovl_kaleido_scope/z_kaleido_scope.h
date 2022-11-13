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

// Direction of pause pages
#define PAUSE_ITEM_X (0)
#define PAUSE_ITEM_Z (-1)
#define PAUSE_MAP_X (1)
#define PAUSE_MAP_Z (0)
#define PAUSE_QUEST_X (0)
#define PAUSE_QUEST_Z (1)
#define PAUSE_MASK_X (-1)
#define PAUSE_MASK_Z (0)

#define PAUSE_EYE_DIST (64.0f)

typedef enum {
    /* 0x00 */ PAUSE_STATE_OFF,
    /* 0x01 */ PAUSE_STATE_OPENING_0,
    /* 0x02 */ PAUSE_STATE_OPENING_1,
    /* 0x03 */ PAUSE_STATE_OPENING_2,
    /* 0x04 */ PAUSE_STATE_OPENING_3,
    /* 0x05 */ PAUSE_STATE_OPENING_4,
    /* 0x06 */ PAUSE_STATE_MAIN, // Pause menu ready for player inputs.
    /* 0x07 */ PAUSE_STATE_SAVEPROMPT,
    /* 0x08 */ PAUSE_STATE_GAMEOVER_0,
    /* 0x09 */ PAUSE_STATE_GAMEOVER_1,
    /* 0x0A */ PAUSE_STATE_GAMEOVER_2,
    /* 0x0B */ PAUSE_STATE_GAMEOVER_3,
    /* 0x0C */ PAUSE_STATE_GAMEOVER_4,
    /* 0x0D */ PAUSE_STATE_GAMEOVER_5,
    /* 0x0E */ PAUSE_STATE_GAMEOVER_SAVE_PROMPT,
    /* 0x0F */ PAUSE_STATE_GAMEOVER_7,
    /* 0x10 */ PAUSE_STATE_GAMEOVER_8,
    /* 0x11 */ PAUSE_STATE_GAMEOVER_CONTINUE_PROMPT,
    /* 0x12 */ PAUSE_STATE_GAMEOVER_10,
    /* 0x13 */ PAUSE_STATE_OWLWARP_0,
    /* 0x14 */ PAUSE_STATE_OWLWARP_1,
    /* 0x15 */ PAUSE_STATE_OWLWARP_2,
    /* 0x16 */ PAUSE_STATE_OWLWARP_3,
    /* 0x17 */ PAUSE_STATE_OWLWARP_SELECT, // Selecting the destination
    /* 0x18 */ PAUSE_STATE_OWLWARP_CONFIRM, // Confirming the choice given
    /* 0x19 */ PAUSE_STATE_OWLWARP_6,
    /* 0x1A */ PAUSE_STATE_UNPAUSE_SETUP, // Unpause
    /* 0x1B */ PAUSE_STATE_UNPAUSE_CLOSE
} PauseState;

typedef enum {
    /* 0x00 */ PAUSE_MAIN_STATE_IDLE, // Await input for the next action
    /* 0x01 */ PAUSE_MAIN_STATE_SWITCHING_PAGE,
    /* 0x02 */ PAUSE_MAIN_STATE_SONG_PLAYBACK,
    /* 0x03 */ PAUSE_MAIN_STATE_EQUIP_ITEM,
    /* 0x04 */ PAUSE_MAIN_STATE_SONG_PROMPT_INIT,
    /* 0x05 */ PAUSE_MAIN_STATE_SONG_PROMPT,
    /* 0x06 */ PAUSE_MAIN_STATE_SONG_PROMPT_DONE,
    /* 0x07 */ PAUSE_MAIN_STATE_SONG_PROMPT_UNUSED,
    /* 0x08 */ PAUSE_MAIN_STATE_IDLE_CURSOR_ON_SONG, // Await input but the cursor is on a song
    /* 0x09 */ PAUSE_MAIN_STATE_SONG_PLAYBACK_INIT,
    /* 0x0F */ PAUSE_MAIN_STATE_EQUIP_MASK = 0xF,
    /* 0x10 */ PAUSE_MAIN_STATE_BOMBERS_NOTEBOOK_OPEN,
    /* 0x11 */ PAUSE_MAIN_STATE_UNK
} PauseMainState;

typedef enum {
    /* 0x00 */ PAUSE_SAVEPROMPT_STATE_0,
    /* 0x01 */ PAUSE_SAVEPROMPT_STATE_1,
    /* 0x02 */ PAUSE_SAVEPROMPT_STATE_2,
    /* 0x03 */ PAUSE_SAVEPROMPT_STATE_3,
    /* 0x04 */ PAUSE_SAVEPROMPT_STATE_4,
    /* 0x05 */ PAUSE_SAVEPROMPT_STATE_5,
    /* 0x06 */ PAUSE_SAVEPROMPT_STATE_6,
    /* 0x07 */ PAUSE_SAVEPROMPT_STATE_7
} PauseSavePromptState;

#define IS_PAUSE_STATE_GAMEOVER \
    ((pauseCtx->state >= PAUSE_STATE_GAMEOVER_0) && (pauseCtx->state <= PAUSE_STATE_GAMEOVER_10))

#define IS_PAUSE_STATE_OWLWARP \
    ((pauseCtx->state >= PAUSE_STATE_OWLWARP_2) && (pauseCtx->state <= PAUSE_STATE_OWLWARP_6))

#define IS_PAUSE_MAIN_STATE_SONG_PROMPT                            \
    ((pauseCtx->mainState >= PAUSE_MAIN_STATE_SONG_PROMPT_INIT) && \
     (pauseCtx->mainState <= PAUSE_MAIN_STATE_SONG_PROMPT_DONE))

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

// TODO: Taken from OoT. Verify in MM
typedef enum {
    /* 0 */ PAUSE_BG_PRERENDER_OFF,
    /* 1 */ PAUSE_BG_PRERENDER_SETUP, // The current frame is only drawn for the purpose of serving as the pause background.
    /* 2 */ PAUSE_BG_PRERENDER_PROCESS, // The previous frame was PAUSE_BG_PRERENDER_SETUP, now apply prerender filters.
    /* 3 */ PAUSE_BG_PRERENDER_DONE, // The pause background is ready to be used.
    /* 4 */ PAUSE_BG_PRERENDER_UNK4,
    /* 5 */ PAUSE_BG_PRERENDER_MAX
} PauseBgPreRenderState;

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

typedef enum {
    /* 0 */ PAUSE_QUAD_CURSOR_0,
    /* 1 */ PAUSE_QUAD_CURSOR_1,
    /* 2 */ PAUSE_QUAD_CURSOR_2,
    /* 3 */ PAUSE_QUAD_CURSOR_3,
    /* 4 */ PAUSE_QUAD_CURSOR_4,
    /* 5 */ PAUSE_QUAD_CURSOR_MAX
} PauseCursorQuad;

typedef enum {
    /* 0 */ VTX_PAGE_MASK,
    /* 1 */ VTX_PAGE_ITEM,
    /* 2 */ VTX_PAGE_MAP_DUNGEON,
    /* 3 */ VTX_PAGE_QUEST,
    /* 4 */ VTX_PAGE_MAP_WORLD,
    /* 5 */ VTX_PAGE_PROMPT,
    /* 6 */ VTX_PAGE_MAX
} VtxPage;

#define VTX_PAGE_MASK_QUADS 0        // VTX_PAGE_MASK
#define VTX_PAGE_ITEM_QUADS 0        // VTX_PAGE_ITEM
#define VTX_PAGE_MAP_DUNGEON_QUADS 6 // VTX_PAGE_MAP_DUNGEON
#define VTX_PAGE_QUEST_QUADS 0       // VTX_PAGE_QUEST
#define VTX_PAGE_MAP_WORLD_QUADS 36  // VTX_PAGE_MAP_WORLD
#define VTX_PAGE_SAVE_QUADS 5        // VTX_PAGE_PROMPT

#define PAGE_BG_COLS 3
#define PAGE_BG_ROWS 5
#define PAGE_BG_QUADS (PAGE_BG_COLS * PAGE_BG_ROWS)
#define PAGE_BG_QUAD_WIDTH 80
#define PAGE_BG_QUAD_HEIGHT 32
#define PAGE_BG_QUAD_TEX_WIDTH 80
#define PAGE_BG_QUAD_TEX_HEIGHT 32

#define PAUSE_PROMPT_YES 0
#define PAUSE_PROMPT_NO 4

typedef enum {
    /* 0 */ QUAD_PROMPT_MESSAGE,
    /* 1 */ QUAD_PROMPT_CURSOR_LEFT,
    /* 2 */ QUAD_PROMPT_CURSOR_RIGHT,
    /* 3 */ QUAD_PROMPT_CHOICE_YES,
    /* 4 */ QUAD_PROMPT_CHOICE_NO,
    /* 5 */ QUAD_PROMPT_MAX
} PromptQuad;


// === ITEM/MASK === //

#define ITEM_GRID_ROWS 4
#define ITEM_GRID_COLS 6
#define ITEM_GRID_CELL_WIDTH 32
#define ITEM_GRID_CELL_HEIGHT 32
#define ITEM_GRID_QUAD_MARGIN 2
#define ITEM_GRID_QUAD_WIDTH (ITEM_GRID_CELL_WIDTH - (2 * ITEM_GRID_QUAD_MARGIN))
#define ITEM_GRID_QUAD_HEIGHT (ITEM_GRID_CELL_HEIGHT - (2 * ITEM_GRID_QUAD_MARGIN))
#define ITEM_GRID_QUAD_TEX_SIZE 32 // both width and height
#define ITEM_GRID_QUAD_ENLARGE_OFFSET 2

#define ITEM_GRID_SELECTED_QUAD_MARGIN (-2)
#define ITEM_GRID_SELECTED_QUAD_WIDTH (ITEM_GRID_QUAD_WIDTH - (2 * ITEM_GRID_SELECTED_QUAD_MARGIN))
#define ITEM_GRID_SELECTED_QUAD_HEIGHT (ITEM_GRID_QUAD_HEIGHT - (2 * ITEM_GRID_SELECTED_QUAD_MARGIN))
#define ITEM_GRID_SELECTED_QUAD_TEX_SIZE 32 // both width and height

#define ITEM_NUM_SLOTS (ITEM_GRID_ROWS * ITEM_GRID_COLS)

#define ITEM_AMMO_DIGIT_QUAD_WIDTH 8
#define ITEM_AMMO_DIGIT_QUAD_HEIGHT 8
#define ITEM_AMMO_DIGIT_QUAD_TEX_SIZE 8

// Relative to the corresponding QUAD_ITEM_GRID_ quad
#define ITEM_AMMO_TENS_QUAD_OFFSET_X 0
#define ITEM_AMMO_TENS_QUAD_OFFSET_Y 22

// Relative to the ammo tens digit
#define ITEM_AMMO_UNITS_QUAD_OFFSET_X 6
#define ITEM_AMMO_UNITS_QUAD_OFFSET_Y 0

typedef enum {
    // 0..23 are the ITEM_GRID_ROWS*ITEM_GRID_COLS item grid
    // The values follow the `InventorySlot` enum
    /*  0 */ QUAD_ITEM_GRID_FIRST,
    /* 23 */ QUAD_ITEM_GRID_LAST = ITEM_GRID_ROWS * ITEM_GRID_COLS - 1,
    // Markers indicating the currently equipped items
    /* 24 */ QUAD_ITEM_GRID_SELECTED_C_LEFT,
    /* 25 */ QUAD_ITEM_GRID_SELECTED_C_DOWN,
    /* 26 */ QUAD_ITEM_GRID_SELECTED_C_RIGHT,
    /* 27 */ QUAD_ITEM_MAX
} ItemQuad;

// === MASK === //
#define MASK_NUM_SLOTS 24

#define MASK_GRID_ROWS 4
#define MASK_GRID_COLS 6
#define MASK_GRID_CELL_WIDTH 32
#define MASK_GRID_CELL_HEIGHT 32
#define MASK_GRID_QUAD_MARGIN 2
#define MASK_GRID_QUAD_WIDTH (MASK_GRID_CELL_WIDTH - (2 * MASK_GRID_QUAD_MARGIN))
#define MASK_GRID_QUAD_HEIGHT (MASK_GRID_CELL_HEIGHT - (2 * MASK_GRID_QUAD_MARGIN))
#define MASK_GRID_QUAD_TEX_SIZE 32 // both width and height
#define MASK_GRID_QUAD_ENLARGE_OFFSET 2

#define MASK_GRID_SELECTED_QUAD_MARGIN (-2)
#define MASK_GRID_SELECTED_QUAD_WIDTH (MASK_GRID_QUAD_WIDTH - (2 * MASK_GRID_SELECTED_QUAD_MARGIN))
#define MASK_GRID_SELECTED_QUAD_HEIGHT (MASK_GRID_QUAD_HEIGHT - (2 * MASK_GRID_SELECTED_QUAD_MARGIN))
#define MASK_GRID_SELECTED_QUAD_TEX_SIZE 32 // both width and height

typedef enum {
    // 0..23 are the MASK_GRID_ROWS*MASK_GRID_COLS item grid
    // The values follow the `InventorySlot` enum offset by ITEM_NUM_SLOTS
    /*  0 */ QUAD_MASK_GRID_FIRST,
    /* 23 */ QUAD_MASK_GRID_LAST = MASK_GRID_ROWS * MASK_GRID_COLS - 1,
    // Markers indicating the currently equipped items
    /* 24 */ QUAD_MASK_GRID_SELECTED_C_LEFT,
    /* 25 */ QUAD_MASK_GRID_SELECTED_C_DOWN,
    /* 26 */ QUAD_MASK_GRID_SELECTED_C_RIGHT,
    /* 27 */ QUAD_MASK_MAX
} MaskQuad;

// === QUEST === //

// QuestQuad;

// === WORLD MAP === //

// MapQuad

#define WORLD_MAP_IMAGE_WIDTH 216
#define WORLD_MAP_IMAGE_HEIGHT 128
#define WORLD_MAP_IMAGE_FRAG_HEIGHT ((TMEM_SIZE / 2) / (WORLD_MAP_IMAGE_WIDTH * G_IM_SIZ_8b_BYTES))
#define WORLD_MAP_IMAGE_FRAG_NUM (((WORLD_MAP_IMAGE_HEIGHT - 1) / WORLD_MAP_IMAGE_FRAG_HEIGHT) + 1)

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
