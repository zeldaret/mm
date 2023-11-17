#ifndef Z64PAUSE_MENU_H
#define Z64PAUSE_MENU_H

#include "ultra64.h"
#include "z64math.h"
#include "z64view.h"
#include "unk.h"

struct OcarinaStaff;
struct PlayState;

typedef enum PauseMenuPage {
    /* 0 */ PAUSE_ITEM,
    /* 1 */ PAUSE_MAP,
    /* 2 */ PAUSE_QUEST,
    /* 3 */ PAUSE_MASK,
    /* 4 */ PAUSE_WORLD_MAP,
    /* 5 */ PAUSE_PAGE_MAX
} PauseMenuPage;

typedef struct PauseContext {
    /* 0x000 */ View view;
    /* 0x168 */ u8* iconItemSegment;
    /* 0x16C */ u8* iconItem24Segment;
    /* 0x170 */ u8* iconItemAltSegment;
    /* 0x174 */ u8* iconItemLangSegment;
    /* 0x178 */ u8* nameSegment;
    /* 0x17C */ u8* iconItemVtxSegment;
    /* 0x180 */ Vtx* itemPageVtx;
    /* 0x184 */ Vtx* mapPageVtx;
    /* 0x188 */ Vtx* questPageVtx;
    /* 0x18C */ Vtx* maskPageVtx;
    /* 0x190 */ Vtx* itemVtx;
    /* 0x194 */ Vtx* mapVtx; // inferred
    /* 0x198 */ Vtx* questVtx;
    /* 0x19C */ Vtx* maskVtx;
    /* 0x1A0 */ Vtx* promptPageVtx;
    /* 0x1A4 */ Vtx* infoPanelVtx;
    /* 0x1A8 */ Vtx* cursorVtx;
    /* 0x1AC */ struct OcarinaStaff* ocarinaStaff;
    /* 0x1B0 */ UNK_TYPE1 unk_1B0[0x20];
    /* 0x1D0 */ OSMesgQueue loadQueue;
    /* 0x1E8 */ OSMesg loadMsg;
    /* 0x1EC */ u16 state; // PauseState enum
    /* 0x1EE */ u16 debugEditor; // DebugEditor enum
    /* 0x1F0 */ u8 bombersNotebookOpen;
    /* 0x1F4 */ Vec3f eye;
    /* 0x200 */ u16 mainState; // PauseMainState enum
    /* 0x202 */ u16 nextPageMode; // (2 * prev pageIndex) + (scroll left ? 1 : 0)
    /* 0x204 */ u16 pageIndex; // PauseMenuPage enum
    /* 0x206 */ u16 switchPageTimer;
    /* 0x208 */ u16 savePromptState; // PauseSavePromptState enum
    /* 0x20C */ f32 unk_20C; // set to 936.0f, unused remnant from OoT
    /* 0x210 */ f32 itemPageRoll; // rotation (-z) of the item page into the screen
    /* 0x214 */ f32 mapPageRoll; // rotation (+x) of the map page into the screen
    /* 0x218 */ f32 questPageRoll; // rotation (+z) of the quest page into the screen
    /* 0x21C */ f32 maskPageRoll; // rotation (-z) of the mask page into the screen
    /* 0x220 */ f32 roll;
    /* 0x224 */ u16 alpha;
    /* 0x226 */ s16 offsetY;
    /* 0x228 */ UNK_TYPE1 unk_228[0x8];
    /* 0x230 */ s32 stickAdjX;
    /* 0x234 */ s32 stickAdjY;
    /* 0x238 */ s16 cursorPoint[PAUSE_PAGE_MAX]; // indexed by PauseMenuPage enum
    /* 0x242 */ s16 cursorXIndex[PAUSE_PAGE_MAX]; // indexed by PauseMenuPage enum
    /* 0x24C */ s16 cursorYIndex[PAUSE_PAGE_MAX]; // indexed by PauseMenuPage enum
    /* 0x256 */ s16 unk_256; // Uses DungeonItem enum
    /* 0x258 */ s16 cursorSpecialPos;
    /* 0x25A */ s16 pageSwitchInputTimer; // Used to introduce a delay before switching page when arriving on the "scroll left/right" positions while holding stick left/right.
    /* 0x25C */ u16 namedItem;
    /* 0x25E */ u16 cursorItem[PAUSE_PAGE_MAX]; // indexed by PauseMenuPage enum
    /* 0x268 */ u16 cursorSlot[PAUSE_PAGE_MAX]; // indexed by PauseMenuPage enum
    /* 0x272 */ u16 equipTargetItem;
    /* 0x274 */ u16 equipTargetSlot;
    /* 0x276 */ u16 equipTargetCBtn; // PauseEquipCButton enum
    /* 0x278 */ s16 equipAnimX;
    /* 0x27A */ s16 equipAnimY;
    /* 0x27C */ s16 equipAnimAlpha;
    /* 0x27E */ s16 infoPanelOffsetY;
    /* 0x280 */ u16 nameDisplayTimer;
    /* 0x282 */ u16 nameColorSet;
    /* 0x284 */ s16 cursorColorSet;
    /* 0x286 */ s16 cursorSpinPhase;
    /* 0x288 */ f32 cursorX;
    /* 0x28C */ f32 cursorY;
    /* 0x290 */ f32 cursorWidth;
    /* 0x294 */ f32 cursorHeight;
    /* 0x298 */ f32 cursorShrinkRate;
    /* 0x29C */ s16 promptChoice; // save/continue choice: 0 = yes; 4 = no
    /* 0x29E */ s16 promptAlpha;
    /* 0x2A0 */ s16 ocarinaSongIndex;
    /* 0x2A2 */ u8 worldMapPoints[20];
    /* 0x2B6 */ u8 unk_2B6; // unused red?
    /* 0x2B7 */ u8 unk_2B7; // unused green?
    /* 0x2B8 */ u8 unk_2B8; // unused blue?
    /* 0x2B9 */ u8 itemDescriptionOn; // helpful description of item given through a message box
    /* 0x2BA */ s16 equipAnimScale; // scale of item icon while moving being equipped to c-button
    /* 0x2BC */ s16 equipAnimShrinkRate; // rate the scale is shrinking for the item icon while moving being equipped to c-button
    /* 0x2BE */ s16 ocarinaButtonsY[5];
    /* 0x2C8 */ u16 unk_2C8; // Uses PauseMenuPage enum for Owl Warp. Never set.
    /* 0x2CA */ s16 unk_2CA; // Uses OwlWarpId enum for Owl Warp. Never set.
} PauseContext; // size = 0x2D0

typedef enum KaleidoMgrOverlayType {
    /* 0 */ KALEIDO_OVL_KALEIDO_SCOPE,
    /* 1 */ KALEIDO_OVL_PLAYER_ACTOR,
    /* 2 */ KALEID_OVL_MAX
} KaleidoMgrOverlayType;

typedef struct KaleidoMgrOverlay {
    /* 0x00 */ void* loadedRamAddr;
    /* 0x04 */ uintptr_t vromStart;
    /* 0x08 */ uintptr_t vromEnd;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ uintptr_t offset; // loadedRamAddr - vramStart
    /* 0x18 */ const char* name;
} KaleidoMgrOverlay; // size = 0x1C


// z_kaleido_setup.c

void func_800F4A10(struct PlayState* play);
void KaleidoSetup_Update(struct PlayState* play);
void KaleidoSetup_Init(struct PlayState* play);
void KaleidoSetup_Destroy(struct PlayState* play);


// z_kaleido_manager.c

void KaleidoManager_LoadOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_ClearOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_Init(struct PlayState* play);
void KaleidoManager_Destroy(void);
void* KaleidoManager_GetRamAddr(void* vram);

extern KaleidoMgrOverlay gKaleidoMgrOverlayTable[KALEID_OVL_MAX];
extern KaleidoMgrOverlay* gKaleidoMgrCurOvl;


// z_kaleido_scope_call.c

void KaleidoScopeCall_LoadPlayer(void);
void KaleidoScopeCall_Init(struct PlayState* play);
void KaleidoScopeCall_Destroy(struct PlayState* play);
void KaleidoScopeCall_Update(struct PlayState* play);
void KaleidoScopeCall_Draw(struct PlayState* play);

#endif
