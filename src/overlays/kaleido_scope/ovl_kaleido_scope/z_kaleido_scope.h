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
    /* 0x00 */ PAUSE_SAVEPROMPT_STATE_APPEARING,
    /* 0x01 */ PAUSE_SAVEPROMPT_STATE_1,
    /* 0x02 */ PAUSE_SAVEPROMPT_STATE_RETURN_TO_MENU,
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

// === PROMPT === //

/**
 * promptPageVtx (unused in MM, inferred from OoT)
 * 
 * // PAGE_BG_QUADS
 * promptPageVtx[0] prompt page background texture:  row 0, column 0
 * promptPageVtx[4] prompt page background texture:  row 1, column 0
 * promptPageVtx[8] prompt page background texture:  row 2, column 0
 * promptPageVtx[12] prompt page background texture: row 3, column 0
 * promptPageVtx[16] prompt page background texture: row 4, column 0
 * promptPageVtx[20] prompt page background texture: row 0, column 1
 * promptPageVtx[24] prompt page background texture: row 1, column 1
 * promptPageVtx[28] prompt page background texture: row 2, column 1
 * promptPageVtx[32] prompt page background texture: row 3, column 1
 * promptPageVtx[36] prompt page background texture: row 4, column 1
 * promptPageVtx[40] prompt page background texture: row 0, column 2
 * promptPageVtx[44] prompt page background texture: row 1, column 2
 * promptPageVtx[48] prompt page background texture: row 2, column 2
 * promptPageVtx[52] prompt page background texture: row 3, column 2
 * promptPageVtx[56] prompt page background texture: row 4, column 2
 * 
 * // QUAD_PROMPT_MAX
 * promptPageVtx[60] message
 * promptPageVtx[64] cursor left
 * promptPageVtx[68] cursor right
 * promptPageVtx[72] choice (yes)
 * promptPageVtx[76] choice (no)
 */

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


// === ITEM === //

/**
 * itemPageVtx
 * 
 * // PAGE_BG_QUADS
 * itemPageVtx[0] item page background texture:  row 0, column 0
 * itemPageVtx[4] item page background texture:  row 1, column 0
 * itemPageVtx[8] item page background texture:  row 2, column 0
 * itemPageVtx[12] item page background texture: row 3, column 0
 * itemPageVtx[16] item page background texture: row 4, column 0
 * itemPageVtx[20] item page background texture: row 0, column 1
 * itemPageVtx[24] item page background texture: row 1, column 1
 * itemPageVtx[28] item page background texture: row 2, column 1
 * itemPageVtx[32] item page background texture: row 3, column 1
 * itemPageVtx[36] item page background texture: row 4, column 1
 * itemPageVtx[40] item page background texture: row 0, column 2
 * itemPageVtx[44] item page background texture: row 1, column 2
 * itemPageVtx[48] item page background texture: row 2, column 2
 * itemPageVtx[52] item page background texture: row 3, column 2
 * itemPageVtx[56] item page background texture: row 4, column 2
 * 
 * // VTX_PAGE_ITEM_QUADS
 * None
 */

/**
 * itemVtx
 * 
 * // ITEM_NUM_SLOTS
 * itemVtx[0] item icon: SLOT_OCARINA
 * itemVtx[4] item icon: SLOT_BOW
 * itemVtx[8] item icon: SLOT_ARROW_FIRE
 * itemVtx[12] item icon: SLOT_ARROW_ICE
 * itemVtx[16] item icon: SLOT_ARROW_LIGHT
 * itemVtx[20] item icon: SLOT_TRADE_DEED
 * itemVtx[24] item icon: SLOT_BOMB
 * itemVtx[28] item icon: SLOT_BOMBCHU
 * itemVtx[32] item icon: SLOT_STICK
 * itemVtx[36] item icon: SLOT_NUT
 * itemVtx[40] item icon: SLOT_MAGIC_BEANS
 * itemVtx[44] item icon: SLOT_TRADE_KEY_MAMA
 * itemVtx[48] item icon: SLOT_POWDER_KEG
 * itemVtx[52] item icon: SLOT_PICTO_BOX
 * itemVtx[56] item icon: SLOT_LENS
 * itemVtx[60] item icon: SLOT_HOOKSHOT
 * itemVtx[64] item icon: SLOT_SWORD_GREAT_FAIRY
 * itemVtx[68] item icon: SLOT_TRADE_COUPLE
 * itemVtx[72] item icon: SLOT_BOTTLE_1
 * itemVtx[76] item icon: SLOT_BOTTLE_2
 * itemVtx[80] item icon: SLOT_BOTTLE_3
 * itemVtx[84] item icon: SLOT_BOTTLE_4
 * itemVtx[88] item icon: SLOT_BOTTLE_5
 * itemVtx[92] item icon: SLOT_BOTTLE_6
 * 
 * // C Buttons
 * itemVtx[96] equipped item white-box outline: EQUIP_SLOT_C_LEFT
 * itemVtx[100] equipped item white-box outline: EQUIP_SLOT_C_DOWN
 * itemVtx[104] equipped item white-box outline: EQUIP_SLOT_C_RIGHT
 */

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

/**
 * maskPageVtx
 * 
 * // PAGE_BG_QUADS
 * maskPageVtx[0] mask page background texture:  row 0, column 0
 * maskPageVtx[4] mask page background texture:  row 1, column 0
 * maskPageVtx[8] mask page background texture:  row 2, column 0
 * maskPageVtx[12] mask page background texture: row 3, column 0
 * maskPageVtx[16] mask page background texture: row 4, column 0
 * maskPageVtx[20] mask page background texture: row 0, column 1
 * maskPageVtx[24] mask page background texture: row 1, column 1
 * maskPageVtx[28] mask page background texture: row 2, column 1
 * maskPageVtx[32] mask page background texture: row 3, column 1
 * maskPageVtx[36] mask page background texture: row 4, column 1
 * maskPageVtx[40] mask page background texture: row 0, column 2
 * maskPageVtx[44] mask page background texture: row 1, column 2
 * maskPageVtx[48] mask page background texture: row 2, column 2
 * maskPageVtx[52] mask page background texture: row 3, column 2
 * maskPageVtx[56] mask page background texture: row 4, column 2
 * 
 * // VTX_PAGE_MASK_QUADS
 * None
 */

/**
 * maskVtx
 * 
 * maskVtx[0] mask icon: SLOT_MASK_POSTMAN
 * maskVtx[4] mask icon: SLOT_MASK_ALL_NIGHT
 * maskVtx[8] mask icon: SLOT_MASK_BLAST
 * maskVtx[12] mask icon: SLOT_MASK_STONE
 * maskVtx[16] mask icon: SLOT_MASK_GREAT_FAIRY
 * maskVtx[20] mask icon: SLOT_MASK_DEKU
 * maskVtx[24] mask icon: SLOT_MASK_KEATON
 * maskVtx[28] mask icon: SLOT_MASK_BREMEN
 * maskVtx[32] mask icon: SLOT_MASK_BUNNY
 * maskVtx[36] mask icon: SLOT_MASK_DON_GERO
 * maskVtx[40] mask icon: SLOT_MASK_SCENTS
 * maskVtx[44] mask icon: SLOT_MASK_GORON
 * maskVtx[48] mask icon: SLOT_MASK_ROMANI
 * maskVtx[52] mask icon: SLOT_MASK_CIRCUS_LEADER
 * maskVtx[56] mask icon: SLOT_MASK_KAFEIS_MASK
 * maskVtx[60] mask icon: SLOT_MASK_COUPLE
 * maskVtx[64] mask icon: SLOT_MASK_TRUTH
 * maskVtx[68] mask icon: SLOT_MASK_ZORA
 * maskVtx[72] mask icon: SLOT_MASK_KAMARO
 * maskVtx[76] mask icon: SLOT_MASK_GIBDO
 * maskVtx[80] mask icon: SLOT_MASK_GARO
 * maskVtx[84] mask icon: SLOT_MASK_CAPTAIN
 * maskVtx[88] mask icon: SLOT_MASK_GIANT
 * maskVtx[92] mask icon: SLOT_MASK_FIERCE_DEITY
 * maskVtx[96] equipped mask white-box outline: EQUIP_SLOT_C_LEFT
 * maskVtx[100] equipped mask white-box outline: EQUIP_SLOT_C_DOWN
 * maskVtx[104] equipped mask white-box outline: EQUIP_SLOT_C_RIGHT
 */

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

#define MASK_NUM_SLOTS (MASK_GRID_ROWS * MASK_GRID_COLS)

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

/**
 * questPageVtx
 * 
 * // PAGE_BG_QUADS
 * questPageVtx[0] quest page background texture:  row 0, column 0
 * questPageVtx[4] quest page background texture:  row 1, column 0
 * questPageVtx[8] quest page background texture:  row 2, column 0
 * questPageVtx[12] quest page background texture: row 3, column 0
 * questPageVtx[16] quest page background texture: row 4, column 0
 * questPageVtx[20] quest page background texture: row 0, column 1
 * questPageVtx[24] quest page background texture: row 1, column 1
 * questPageVtx[28] quest page background texture: row 2, column 1
 * questPageVtx[32] quest page background texture: row 3, column 1
 * questPageVtx[36] quest page background texture: row 4, column 1
 * questPageVtx[40] quest page background texture: row 0, column 2
 * questPageVtx[44] quest page background texture: row 1, column 2
 * questPageVtx[48] quest page background texture: row 2, column 2
 * questPageVtx[52] quest page background texture: row 3, column 2
 * questPageVtx[56] quest page background texture: row 4, column 2
 * 
 * // VTX_PAGE_QUEST_QUADS
 * None
 */

/**
 * questVtx
 * 
 * questVtx[0] quest icon: QUEST_REMAINS_ODOLWA
 * questVtx[4] quest icon: QUEST_REMAINS_GOHT
 * questVtx[8] quest icon: QUEST_REMAINS_GYORG
 * questVtx[12] quest icon: QUEST_REMAINS_TWINMOLD
 * questVtx[16] quest icon: QUEST_SHIELD
 * questVtx[20] quest icon: QUEST_SWORD
 * questVtx[24] quest icon: QUEST_SONG_SONATA
 * questVtx[28] quest icon: QUEST_SONG_LULLABY
 * questVtx[32] quest icon: QUEST_SONG_BOSSA_NOVA
 * questVtx[36] quest icon: QUEST_SONG_ELEGY
 * questVtx[40] quest icon: QUEST_SONG_OATH
 * questVtx[44] quest icon: QUEST_SONG_SARIA
 * questVtx[48] quest icon: QUEST_SONG_TIME
 * questVtx[52] quest icon: QUEST_SONG_HEALING
 * questVtx[56] quest icon: QUEST_SONG_EPONA
 * questVtx[60] quest icon: QUEST_SONG_SOARING
 * questVtx[64] quest icon: QUEST_SONG_STORMS
 * questVtx[68] quest icon: QUEST_SONG_SUN
 * questVtx[72] quest icon: QUEST_BOMBERS_NOTEBOOK
 * questVtx[76] quest icon: QUEST_QUIVER
 * questVtx[80] quest icon: QUEST_BOMB_BAG
 * questVtx[84] quest icon: QUEST_SKULL_TOKEN
 * questVtx[88] quest icon: QUEST_HEART_PIECE
 * questVtx[92] ocarina song button index 0
 * questVtx[96] ocarina song button index 1
 * questVtx[100] ocarina song button index 2
 * questVtx[104] ocarina song button index 3
 * questVtx[108] ocarina song button index 4
 * questVtx[112] ocarina song button index 5
 * questVtx[116] ocarina song button index 6
 * questVtx[120] ocarina song button index 7
 * questVtx[124] ocarina input button index 0
 * questVtx[128] ocarina input button index 1
 * questVtx[132] ocarina input button index 2
 * questVtx[140] ocarina input button index 3
 * questVtx[144] ocarina input button index 4
 * questVtx[148] ocarina input button index 5
 * questVtx[152] ocarina input button index 6
 * questVtx[156] ocarina input button index 7
 */

// QuestQuad;

// === DUNGEON MAP === //

/**
 * mapPageVtx (Dungeon)
 * 
 * // PAGE_BG_QUADS
 * mapPageVtx[0] map page background texture:  row 0, column 0
 * mapPageVtx[4] map page background texture:  row 1, column 0
 * mapPageVtx[8] map page background texture:  row 2, column 0
 * mapPageVtx[12] map page background texture: row 3, column 0
 * mapPageVtx[16] map page background texture: row 4, column 0
 * mapPageVtx[20] map page background texture: row 0, column 1
 * mapPageVtx[24] map page background texture: row 1, column 1
 * mapPageVtx[28] map page background texture: row 2, column 1
 * mapPageVtx[32] map page background texture: row 3, column 1
 * mapPageVtx[36] map page background texture: row 4, column 1
 * mapPageVtx[40] map page background texture: row 0, column 2
 * mapPageVtx[44] map page background texture: row 1, column 2
 * mapPageVtx[48] map page background texture: row 2, column 2
 * mapPageVtx[52] map page background texture: row 3, column 2
 * mapPageVtx[56] map page background texture: row 4, column 2
 * 
 * // VTX_PAGE_MAP_DUNGEON
 * mapPageVtx[60] dungeon title
 * mapPageVtx[64] dungeon boss key
 * mapPageVtx[68] dungeon compass
 * mapPageVtx[72] dungeon map
 * mapPageVtx[76] dungeon stray fairy glowing circle
 * mapPageVtx[80] dungeon unused
 */

// === WORLD MAP === //

/**
 * mapPageVtx (World)
 * 
 * // PAGE_BG_QUADS
 * mapPageVtx[0] map page background texture:  row 0, column 0
 * mapPageVtx[4] map page background texture:  row 1, column 0
 * mapPageVtx[8] map page background texture:  row 2, column 0
 * mapPageVtx[12] map page background texture: row 3, column 0
 * mapPageVtx[16] map page background texture: row 4, column 0
 * mapPageVtx[20] map page background texture: row 0, column 1
 * mapPageVtx[24] map page background texture: row 1, column 1
 * mapPageVtx[28] map page background texture: row 2, column 1
 * mapPageVtx[32] map page background texture: row 3, column 1
 * mapPageVtx[36] map page background texture: row 4, column 1
 * mapPageVtx[40] map page background texture: row 0, column 2
 * mapPageVtx[44] map page background texture: row 1, column 2
 * mapPageVtx[48] map page background texture: row 2, column 2
 * mapPageVtx[52] map page background texture: row 3, column 2
 * mapPageVtx[56] map page background texture: row 4, column 2
 * 
 * // VTX_PAGE_MAP_WORLD
 * mapPageVtx[60] world map clouds Clock Town 1
 * mapPageVtx[64] world map clouds Clock Town 2
 * mapPageVtx[68] world map clouds Woodfall 1
 * mapPageVtx[72] world map clouds Woodfall 2
 * mapPageVtx[76] world map clouds Woodfall 3
 * mapPageVtx[80] world map clouds Snowhead 1
 * mapPageVtx[84] world map clouds Snowhead 2
 * mapPageVtx[88] world map clouds Snowhead 3
 * mapPageVtx[92] world map clouds Romani Rance
 * mapPageVtx[96] world map clouds Great Bay 1
 * mapPageVtx[100] world map clouds Great Bay 2
 * mapPageVtx[104] world map clouds Great Bay 3
 * mapPageVtx[108] world map clouds Great Bay 4
 * mapPageVtx[112] world map clouds Stone Tower 1
 * mapPageVtx[116] world map clouds Stone Tower 2
 * mapPageVtx[120] world map region Great Bay
 * mapPageVtx[124] world map region Zora Hall
 * mapPageVtx[128] world map region Romani Ranch
 * mapPageVtx[132] world map region Deku Palace
 * mapPageVtx[136] world map region Woodfall
 * mapPageVtx[140] world map region Clock Town
 * mapPageVtx[144] world map region Snowhead
 * mapPageVtx[148] world map region Ikana Graveyard
 * mapPageVtx[152] world map region Ikana Canyon
 * mapPageVtx[156] world map region Goron Village
 * mapPageVtx[160] world map region Stone Tower
 * mapPageVtx[164] world map owl warp Great Bay Coast
 * mapPageVtx[168] world map owl warp Zora Cape
 * mapPageVtx[172] world map owl warp snowhead
 * mapPageVtx[176] world map owl warp Mountain Village
 * mapPageVtx[180] world map owl warp Clock Town
 * mapPageVtx[184] world map owl warp Milk Road
 * mapPageVtx[188] world map owl warp Woodfall
 * mapPageVtx[192] world map owl warp Southern Swamp
 * mapPageVtx[196] world map owl warp Ikana Canyon
 * mapPageVtx[200] world map owl warp Stone Tower
 * 
 * WORLD_MAP_IMAGE_FRAG_NUM
 * mapPageVtx[204] World Map fragment row 1
 * mapPageVtx[208] World Map fragment row 2
 * mapPageVtx[212] World Map fragment row 3
 * mapPageVtx[216] World Map fragment row 4
 * mapPageVtx[220] World Map fragment row 5
 * mapPageVtx[224] World Map fragment row 6
 * mapPageVtx[228] World Map fragment row 7
 * mapPageVtx[232] World Map fragment row 8
 * mapPageVtx[236] World Map fragment row 9
 * mapPageVtx[240] World Map fragment row 10
 * mapPageVtx[244] World Map fragment row 11
 * mapPageVtx[248] World Map fragment row 12
 * mapPageVtx[252] World Map fragment row 13
 * mapPageVtx[256] World Map fragment row 14
 * mapPageVtx[260] World Map fragment row 15
 */

// MapQuad

#define WORLD_MAP_IMAGE_WIDTH 216
#define WORLD_MAP_IMAGE_HEIGHT 128
#define WORLD_MAP_IMAGE_FRAG_HEIGHT ((TMEM_SIZE / 2) / (WORLD_MAP_IMAGE_WIDTH * G_IM_SIZ_8b_BYTES))
#define WORLD_MAP_IMAGE_FRAG_NUM (((WORLD_MAP_IMAGE_HEIGHT - 1) / WORLD_MAP_IMAGE_FRAG_HEIGHT) + 1)

// === INFO PANEL === //

/**
 * infoPanelVtx
 * 
 * infoPanelVtx[0] name panel left texture
 * infoPanelVtx[4] name panel right texture
 * infoPanelVtx[8] L Button icon
 * infoPanelVtx[12] R Button icon
 * infoPanelVtx[16] A button icon (or name segment)
 * infoPanelVtx[20] pause-to-decide texture
 * infoPanelVtx[24] (unused) oot remnant of Gold Skulltula Icon Texture
 */

#define PAUSE_NAME_COLOR_SET_WHITE 0
#define PAUSE_NAME_COLOR_SET_GREY 1

// === CURSOR === //

/**
 * cursorVtx
 * 
 * cursorVtx[0] cursor circle
 * cursorVtx[4] (unused) oot remnant of top-right corner of cursor
 * cursorVtx[8] (unused) oot remnant of bottom-left corner of cursor
 * cursorVtx[12] (unused) oot remnant of bottom-right corner of cursor
 * cursorVtx[16] equipping item icon (while moving)
 */

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
