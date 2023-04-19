#ifndef Z64_H
#define Z64_H

#include "libc/math.h"
#include "libc/stdarg.h"
#include "libc/stdbool.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "libc/stdlib.h"

#include "ultra64.h"
#include "ultra64/gs2dex.h"
#include "io/controller.h"
#include "osint.h"
#include "os.h"
#include "irqmgr.h"
#include "scheduler.h"
#include "xstdio.h"

#include "color.h"
#include "ichain.h"
#include "sequence.h"
#include "seqcmd.h"
#include "sfx.h"
#include "message_data_static.h"

#include "gfxprint.h"
#include "sys_matrix.h"
#include "tha.h"
#include "thga.h"
#include "z64actor.h"
#include "z64animation.h"
#include "z64animation_legacy.h"
#include "z64audio.h"
#include "z64bgcheck.h"
#include "z64camera.h"
#include "z64collision_check.h"
#include "z64curve.h"
#include "z64cutscene.h"
#include "z64dma.h"
#include "z64eff_footmark.h"
#include "z64effect.h"
#include "z64frameadvance.h"
#include "z64game_over.h"
#include "z64interface.h"
#include "z64item.h"
#include "z64light.h"
#include "z64map.h"
#include "z64math.h"
#include "z64message.h"
#include "z64object.h"
#include "z64ocarina.h"
#include "z64player.h"
#include "z64save.h"
#include "z64scene.h"
#include "z64schedule.h"
#include "z64skin.h"
#include "z64skybox.h"
#include "z64subs.h"
#include "z64transition.h"
#include "z64view.h"
#include "regs.h"

#define Z_THREAD_ID_IDLE     1
#define Z_THREAD_ID_SLOWLY   2
#define Z_THREAD_ID_FAULT    2
#define Z_THREAD_ID_MAIN     3
#define Z_THREAD_ID_GRAPH    4
#define Z_THREAD_ID_SCHED    5
#define Z_THREAD_ID_DMAMGR  18
#define Z_THREAD_ID_IRQMGR  19

#define Z_PRIORITY_SLOWLY          5
#define Z_PRIORITY_GRAPH           9
#define Z_PRIORITY_AUDIOMGR       11
#define Z_PRIORITY_IDLE           12
#define Z_PRIORITY_MAIN           12
#define Z_PRIORITY_PADMGR         15
#define Z_PRIORITY_SCHED          16
#define Z_PRIORITY_DMAMGR         17
#define Z_PRIORITY_IRQMGR         18
#define Z_THREAD_PRI_FAULT_CLIENT (OS_PRIORITY_APPMAX - 1)
#define Z_THREAD_PRI_FAULT        OS_PRIORITY_APPMAX

typedef enum {
    /* 0 */ EQUIP_SLOT_B,
    /* 1 */ EQUIP_SLOT_C_LEFT,
    /* 2 */ EQUIP_SLOT_C_DOWN,
    /* 3 */ EQUIP_SLOT_C_RIGHT,
    /* 4 */ EQUIP_SLOT_A
} EquipSlot;

typedef struct {
    /* 0x0 */ s16 priority; // Lower means higher priority. -1 means it ignores priority
    /* 0x2 */ s16 length;
    /* 0x4 */ s16 csCamSceneDataId; // Index of CsCameraEntry to use. Negative indices use sGlobalCamDataSettings. Indices 0 and above use CsCameraEntry from scene
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 additionalCutscene;
    /* 0xA */ u8 sound;
    /* 0xB */ u8 unkB;
    /* 0xC */ s16 unkC;
    /* 0xE */ u8 unkE;
    /* 0xF */ u8 letterboxSize;
} ActorCutscene; // size = 0x10

typedef struct {
    /* 0x0 */ s8 segment;
    /* 0x2 */ s16 type;
    /* 0x4 */ void* params;
} AnimatedMaterial; // size = 0x8

typedef struct {
    /* 0x0 */ Vec3s pos;
    /* 0x6 */ s16   unk_06;
    /* 0x8 */ Gfx*  opa;
    /* 0xC */ Gfx*  xlu;
} PolygonDlist2; // size = 0x10

typedef struct {
    /* 0x0 */ u8    type;
    /* 0x1 */ u8    num; // number of dlist entries
    /* 0x4 */ void* start;
    /* 0x8 */ void* end;
} PolygonType2; // size = 0xC

typedef struct {
    /* 0x000 */ Gfx taskStart[9];
    /* 0x048 */ Gfx clearZBuffer[8];       // original name: clear_zb_dl
    /* 0x088 */ Gfx clearFrameBuffer[5];   // original name: clear_fb_dl
    /* 0x0B0 */ Gfx setupBuffers[6];       // setup framebuffer and zbuffer
    /* 0x0E0 */ Gfx unk_E0[12];            // unused
    /* 0x140 */ Gfx syncSegments[17];
    /* 0x1C8 */ Gfx setScissor[2];
    /* 0x1D8 */ Gfx unk_1D8[25];           // unused
    /* 0x2A0 */ Gfx disps[5];
    /* 0x2C8 */ Gfx clearFillRect[3];      // fillrect for clearing buffers
    /* 0x2E0 */ Gfx fillRect[3];           // fillrect for general purpose
    /* 0x2F8 */ Gfx debugDisp[1];
} GfxMasterList; // size = 0x300

#define GFXPOOL_HEAD_MAGIC 0x1234
#define GFXPOOL_TAIL_MAGIC 0x5678

typedef struct {
    /* 0x00000 */ u16 headMagic; // 1234
    /* 0x00008 */ GfxMasterList master;
    /* 0x00308 */ Gfx polyXluBuffer[2048];
    /* 0x04308 */ Gfx overlayBuffer[1024];
    /* 0x06308 */ Gfx workBuffer[64];
    /* 0x06508 */ Gfx debugBuffer[64];
    /* 0x06708 */ Gfx polyOpaBuffer[13184];
    /* 0x20308 */ u16 tailMagic; // 5678
} GfxPool; // size = 0x20310

typedef struct GraphicsContext {
    /* 0x000 */ Gfx*        polyOpaBuffer;  // Pointer to "Zelda 0"
    /* 0x004 */ Gfx*        polyXluBuffer;  // Pointer to "Zelda 1"
    /* 0x008 */ char        unk_8[0x8];     // Unused, could this be pointers to "Zelda 2" / "Zelda 3"
    /* 0x010 */ Gfx*        overlayBuffer;  // Pointer to "Zelda 4"
    /* 0x014 */ u32         unk_14;
    /* 0x018 */ char        unk_18[0x20];
    /* 0x038 */ OSMesg      msgBuff[8];
    /* 0x058 */ OSMesgQueue* schedMsgQ;
    /* 0x05C */ OSMesgQueue queue;
    /* 0x074 */ char        unk_74[0x04];
    /* 0x078 */ OSScTask    task;
    /* 0x0E0 */ char        unk_E0[0xD0];
    /* 0x1B0 */ Gfx*        workBuffer;
    /* 0x1B4 */ TwoHeadGfxArena work;
    /* 0x1C4 */ Gfx*        debugBuffer;
    /* 0x1C8 */ TwoHeadGfxArena debug;
    /* 0x1D8 */ char        unk_1D8[0xAC];
    /* 0x284 */ OSViMode*   viMode;
    /* 0x288 */ void*       zbuffer;
    /* 0x28C */ char        unk_28C[0x1C];
    /* 0x2A8 */ TwoHeadGfxArena overlay;    // "Zelda 4"
    /* 0x2B8 */ TwoHeadGfxArena polyOpa;    // "Zelda 0"
    /* 0x2C8 */ TwoHeadGfxArena polyXlu;    // "Zelda 1"
    /* 0x2D8 */ u32         gfxPoolIdx;
    /* 0x2DC */ u16*        curFrameBuffer;
    /* 0x2E0 */ char        unk_2E0[0x4];
    /* 0x2E4 */ u32         viConfigFeatures;
    /* 0x2E8 */ char        unk_2E8[0x2];
    /* 0x2EA */ u8          updateViMode;
    /* 0x2EB */ u8          framebufferIndex;
    /* 0x2EC */ void        (*callback)(struct GraphicsContext*, u32);
    /* 0x2F0 */ u32         callbackArg;
    /* 0x2F4 */ f32         xScale;
    /* 0x2F8 */ f32         yScale;
    /* 0x2FC */ GfxMasterList* masterList;
} GraphicsContext; // size = 0x300

typedef enum IRQ_MSG_TYPE {
    IRQ_VERTICAL_RETRACE_MSG = 0x1,
    IRQ_PRENMI_2_MSG = 0x3,
    IRQ_PRENMI_1_MSG = 0x4
} IRQ_MSG_TYPE;

typedef enum IRQ_TYPE {
    IRQ_VERTICAL_RETRACE = 0x29A,
    IRQ_SP = 0x29B,
    IRQ_DP = 0x29C,
    IRQ_PRENMI_1 = 0x29D,
    IRQ_PRENMI_2 = 0x29F,
    IRQ_PRENMI_3 = 0x2A0,
    IRQ_PRENMI_4 = 0x2A1
} IRQ_TYPE;

typedef struct {
    /* 0x00 */ u32 resetting;
    /* 0x04 */ u32 resetCount;
    /* 0x08 */ OSTime duration;
    /* 0x10 */ OSTime resetTime;
} NmiBuff; // size >= 0x18

typedef struct {
    /* 0x00 */ int unk0;
    /* 0x04 */ void* unk4;
    /* 0x08 */ int unk8;
    /* 0x0C */ int unkC;
    /* 0x10 */ int unk10;
    /* 0x14 */ OSMesgQueue unk14;
} s80185D40; // size = 0x2C

typedef struct {
    /* 0x00 */ u8 countdown;
    /* 0x01 */ u8 playSfxEachFrame;
    /* 0x02 */ u16 sfxId;
    /* 0x04 */ Vec3f worldPos;
    /* 0x10 */ Vec3f projectedPos;
} SoundSource; // size = 0x1C

typedef struct {
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
    /* 0x194 */ Vtx* mapVtx;
    /* 0x198 */ Vtx* questVtx;
    /* 0x19C */ Vtx* maskVtx;
    /* 0x1A0 */ Vtx* unk_1A0;
    /* 0x1A4 */ Vtx* unk_1A4;
    /* 0x1A8 */ Vtx* cursorVtx;
    /* 0x1AC */ OcarinaStaff* ocarinaStaff;
    /* 0x1B0 */ UNK_TYPE1 unk_1B0[0x20];
    /* 0x1D0 */ OSMesgQueue loadQueue;
    /* 0x1E8 */ OSMesg loadMsg;
    /* 0x1EC */ u16 state;
    /* 0x1EE */ u16 debugEditor;
    /* 0x1F0 */ u8 bombersNotebookOpen;
    /* 0x1F4 */ Vec3f eye;
    /* 0x200 */ u16 mainState;
    /* 0x202 */ u16 nextPageMode; // (2 * prev pageIndex) + (scroll left ? 1 : 0)
    /* 0x204 */ u16 pageIndex;
    /* 0x206 */ u16 switchPageTimer;
    /* 0x208 */ u16 savePromptState;
    /* 0x20C */ f32 unk_20C;
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
    /* 0x238 */ s16 cursorPoint[5];
    /* 0x242 */ s16 cursorXIndex[5];
    /* 0x24C */ s16 cursorYIndex[5];
    /* 0x256 */ s16 unk_256; // Uses DungeonItem enum
    /* 0x258 */ s16 cursorSpecialPos;
    /* 0x25A */ s16 pageSwitchTimer;
    /* 0x25C */ u16 namedItem;
    /* 0x25E */ u16 cursorItem[5];
    /* 0x268 */ u16 cursorSlot[5];
    /* 0x272 */ u16 equipTargetItem;
    /* 0x274 */ u16 equipTargetSlot;
    /* 0x276 */ u16 equipTargetCBtn;
    /* 0x278 */ s16 equipAnimX;
    /* 0x27A */ s16 equipAnimY;
    /* 0x27C */ s16 equipAnimAlpha;
    /* 0x27E */ s16 infoPanelOffsetY;
    /* 0x280 */ u16 unk_280;
    /* 0x282 */ u16 nameColorSet;
    /* 0x284 */ s16 cursorColorSet;
    /* 0x286 */ s16 unk_286;
    /* 0x288 */ f32 unk_288;
    /* 0x28C */ f32 unk_28C;
    /* 0x290 */ f32 unk_290;
    /* 0x294 */ f32 unk_294;
    /* 0x298 */ f32 unk_298;
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

typedef struct {
    /* 0x00 */ void* loadedRamAddr;
    /* 0x04 */ uintptr_t vromStart;
    /* 0x08 */ uintptr_t vromEnd;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ uintptr_t offset; // loadedRamAddr - vramStart
    /* 0x18 */ const char* name;
} KaleidoMgrOverlay; // size = 0x1C

typedef enum {
    /* 0x00 */ KALEIDO_OVL_KALEIDO_SCOPE,
    /* 0x01 */ KALEIDO_OVL_PLAYER_ACTOR,
    /* 0x02 */ KALEID_OVL_MAX
} KaleidoMgrOverlayType;

typedef struct {
    /* 0x00 */ u16 unk_0;
    /* 0x02 */ u16 sceneTimeSpeed;
    /* 0x04 */ Vec3f sunPos;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 skyboxDisabled;
    /* 0x16 */ u8 sunMoonDisabled;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 unk_1E;
    /* 0x1F */ u8 unk_1F;
    /* 0x20 */ u8 unk_20;
    /* 0x21 */ u8 unk_21;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26;
    /* 0x28 */ LightInfo dirLight1; // sun 1
    /* 0x36 */ LightInfo unk_36; // sun 2
    /* 0x44 */ s8 unk_44;
    /* 0x48 */ DmaRequest unk_48;
    /* 0x68 */ OSMesgQueue unk_68;
    /* 0x80 */ OSMesg unk_80;
    /* 0x84 */ f32 unk_84;
    /* 0x88 */ f32 unk_88;
    /* 0x8C */ EnvLightSettings lightSettings;
    /* 0xA8 */ f32 unk_A8;
    /* 0xAC */ Vec3s windDir;
    /* 0xB4 */ f32 windSpeed;
    /* 0xB8 */ u8 numLightSettings;
    /* 0xBC */ LightSettings* lightSettingsList;
    /* 0xC0 */ u8 unk_C0;
    /* 0xC1 */ u8 unk_C1;
    /* 0xC2 */ u8 unk_C2;
    /* 0xC3 */ u8 lightSettingOverride;
    /* 0xC4 */ LightSettings unk_C4;
    /* 0xDA */ u16 unk_DA;
    /* 0xDC */ f32 lightBlend;
    /* 0xE0 */ u8 unk_E0;
    /* 0xE1 */ u8 unk_E1;
    /* 0xE2 */ s8 unk_E2;
    /* 0xE3 */ u8 unk_E3; // modified by unused func in EnWeatherTag
    /* 0xE4 */ u8 unk_E4;
    /* 0xE5 */ u8 fillScreen;
    /* 0xE6 */ u8 screenFillColor[4];
    /* 0xEA */ u8 sandstormState;
    /* 0xEB */ u8 sandstormPrimA;
    /* 0xEC */ u8 sandstormEnvA;
    /* 0xED */ u8 unk_ED;
    /* 0xEE */ u8 unk_EE[4];
    /* 0xF2 */ u8 unk_F2[8]; // [3] is used by both DemoKankyo and ObjectKankyo effect count
    /* 0xFA */ u8 unk_FA[4];
} EnvironmentContext; // size = 0x100

typedef struct ListAlloc {
    /* 0x0 */ struct ListAlloc* prev;
    /* 0x4 */ struct ListAlloc* next;
} ListAlloc; // size = 0x8

typedef struct {
    /* 0x00 */ u16 width;
    /* 0x02 */ u16 height;
    /* 0x04 */ u16 widthSave;
    /* 0x06 */ u16 heightSave;
    /* 0x08 */ char unk_8[8];
    /* 0x10 */ u16* fbuf;
    /* 0x14 */ u16* fbufSave;
    /* 0x18 */ u8* cvgSave;
    /* 0x1C */ u16* zbuf;
    /* 0x20 */ u16* zbufSave;
    /* 0x24 */ u16 ulxSave;
    /* 0x26 */ u16 ulySave;
    /* 0x28 */ u16 lrxSave;
    /* 0x2A */ u16 lrySave;
    /* 0x2C */ u16 ulx;
    /* 0x2E */ u16 uly;
    /* 0x30 */ u16 lrx;
    /* 0x32 */ u16 lry;
    /* 0x34 */ char unk_34[16];
    /* 0x44 */ ListAlloc alloc;
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 unk_4D;
    /* 0x4E */ char unk_4E[2];
} PreRender; // size = 0x50

typedef struct {
    /* 0x00 */ void* timg;
    /* 0x04 */ void* tlut;
    /* 0x08 */ u16 width;
    /* 0x0A */ u16 height;
    /* 0x0C */ u8 fmt;
    /* 0x0D */ u8 siz;
    /* 0x0E */ u16 tt;
    /* 0x10 */ u16 unk_10;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 xScale;
    /* 0x20 */ f32 yScale;
    /* 0x24 */ u32 flags;
} PreRenderParams; // size = 0x28

struct GameState;

typedef void (*GameStateFunc)(struct GameState* gameState);

typedef struct {
    /* 0x00 */ void*         loadedRamAddr;
    /* 0x04 */ uintptr_t     vromStart; // if applicable
    /* 0x08 */ uintptr_t     vromEnd;   // if applicable
    /* 0x0C */ void*         vramStart; // if applicable
    /* 0x10 */ void*         vramEnd;   // if applicable
    /* 0x14 */ UNK_PTR       unk_14;
    /* 0x18 */ GameStateFunc init;    // initializes and executes the given context
    /* 0x1C */ GameStateFunc destroy; // deconstructs the context, and sets the next context to load
    /* 0x20 */ UNK_PTR       unk_20;
    /* 0x24 */ UNK_PTR       unk_24;
    /* 0x28 */ UNK_TYPE      unk_28;
    /* 0x2C */ size_t        instanceSize;
} GameStateOverlay; // size = 0x30

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

typedef struct GameState {
    /* 0x00 */ GraphicsContext* gfxCtx;
    /* 0x04 */ GameStateFunc main;
    /* 0x08 */ GameStateFunc destroy;
    /* 0x0C */ GameStateFunc init; // Usually the current game state's init, though after stopping, the graph thread will look here to determine the next game state to load.
    /* 0x10 */ size_t size;
    /* 0x14 */ Input input[4];
    /* 0x74 */ TwoHeadArena heap;
    /* 0x84 */ GameAlloc alloc;
    /* 0x98 */ UNK_TYPE1 pad98[0x3];
    /* 0x9B */ u8 running; // If 0, switch to next game state
    /* 0x9C */ u32 frames;
    /* 0xA0 */ u8 padA0[0x2];
    /* 0xA2 */ u8 framerateDivisor; // game speed?
    /* 0xA3 */ u8 unk_A3;
} GameState; // size = 0xA4

struct PlayState;

typedef s32 (*ColChkResetFunc)(struct PlayState*, Collider*);
typedef void (*ColChkBloodFunc)(struct PlayState*, Collider*, Vec3f*);
typedef void (*ColChkApplyFunc)(struct PlayState*, CollisionCheckContext*, Collider*);
typedef void (*ColChkVsFunc)(struct PlayState*, CollisionCheckContext*, Collider*, Collider*);
typedef s32 (*ColChkLineFunc)(struct PlayState*, CollisionCheckContext*, Collider*, Vec3f*, Vec3f*);

typedef struct {
    /* 0x000 */ u8 controllers; // bit 0 is set if controller 1 is plugged in, etc.
    /* 0x001 */ UNK_TYPE1 pad1[0x13];
    /* 0x014 */ OSContStatus statuses[4];
    /* 0x024 */ UNK_TYPE4 unk24;
    /* 0x028 */ OSMesg lockMesg[1];
    /* 0x02C */ OSMesg interrupts[8];
    /* 0x04C */ OSMesgQueue sSiIntMsgQ;
    /* 0x064 */ OSMesgQueue lock;
    /* 0x07C */ OSMesgQueue irqmgrCallbackQueue;
    /* 0x094 */ IrqMgrClient irqmgrCallbackQueueNode;
    /* 0x09C */ IrqMgr* irqmgr;
    /* 0x0A0 */ OSThread thread;
    /* 0x250 */ Input input[4];
    /* 0x2B0 */ OSContPad controllerState1[4];
    /* 0x2C8 */ u8 maxNumControllers;
    /* 0x2C9 */ UNK_TYPE1 pad2C9[0x1B3];
    /* 0x47C */ u8 unk47C;
    /* 0x47D */ u8 unk47D;
    /* 0x47E */ u8 hasStopped;
    /* 0x47F */ UNK_TYPE1 pad47F[0x1];
} PadMgr; // size = 0x480

#define OS_SC_RETRACE_MSG       1
#define OS_SC_DONE_MSG          2
#define OS_SC_NMI_MSG           3 // name is made up, 3 is OS_SC_RDP_DONE_MSG in the original sched.c
#define OS_SC_PRE_NMI_MSG       4

typedef struct {
    /* 0x000 */ IrqMgr* irqMgr;
    /* 0x004 */ SchedContext* sched;
    /* 0x008 */ OSScTask audioTask;
    /* 0x060 */ AudioTask* rspTask;
    /* 0x064 */ OSMesgQueue interruptMsgQ;
    /* 0x07C */ OSMesg interruptMsgBuf[30];
    /* 0x0F4 */ OSMesgQueue cmdQ;
    /* 0x10C */ OSMesg cmdMsgBuf[1];
    /* 0x110 */ OSMesgQueue lockMsgQ;
    /* 0x128 */ OSMesg lockMsgBuf[1];
    /* 0x12C */ UNK_TYPE1 pad_12C[0x4];
    /* 0x130 */ OSThread thread;
} AudioMgr; // size = 0x2E0

typedef struct {
    /* 0x0 */ u8   seqId;
    /* 0x1 */ u8   ambienceId;
} SequenceContext; // size = 0x2

typedef struct PlayState {
    /* 0x00000 */ GameState state;
    /* 0x000A4 */ s16 sceneId;
    /* 0x000A6 */ u8 sceneConfig;
    /* 0x000A7 */ char unk_A7[0x9];
    /* 0x000B0 */ void* sceneSegment;
    /* 0x000B4 */ char unk_B4[0x4];
    /* 0x000B8 */ View view;
    /* 0x00220 */ Camera mainCamera;
    /* 0x00398 */ Camera subCameras[NUM_CAMS - CAM_ID_SUB_FIRST];
    /* 0x00800 */ Camera* cameraPtrs[NUM_CAMS];
    /* 0x00810 */ s16 activeCamId;
    /* 0x00812 */ s16 nextCamera;
    /* 0x00814 */ SequenceContext sequenceCtx;
    /* 0x00818 */ LightContext lightCtx;
    /* 0x00828 */ FrameAdvanceContext frameAdvCtx;
    /* 0x00830 */ CollisionContext colCtx;
    /* 0x01CA0 */ ActorContext actorCtx;
    /* 0x01F24 */ CutsceneContext csCtx;
    /* 0x01F78 */ SoundSource soundSources[16];
    /* 0x02138 */ EffFootmark footprintInfo[100];
    /* 0x046B8 */ SramContext sramCtx;
    /* 0x046E0 */ SkyboxContext skyboxCtx;
    /* 0x04908 */ MessageContext msgCtx;
    /* 0x169E8 */ InterfaceContext interfaceCtx;
    /* 0x16D30 */ PauseContext pauseCtx;
    /* 0x17000 */ GameOverContext gameOverCtx;
    /* 0x17004 */ EnvironmentContext envCtx;
    /* 0x17104 */ AnimationContext animationCtx;
    /* 0x17D88 */ ObjectContext objectCtx;
    /* 0x186E0 */ RoomContext roomCtx;
    /* 0x18760 */ DoorContext doorCtx;
    /* 0x18768 */ void (*playerInit)(Player* player, struct PlayState* play, FlexSkeletonHeader* skelHeader);
    /* 0x1876C */ void (*playerUpdate)(Player* player, struct PlayState* play, Input* input);
    /* 0x18770 */ void (*unk_18770)(struct PlayState* play, Player* player);
    /* 0x18774 */ s32 (*startPlayerFishing)(struct PlayState* play);
    /* 0x18778 */ s32 (*grabPlayer)(struct PlayState* play, Player* player);
    /* 0x1877C */ s32 (*startPlayerCutscene)(struct PlayState* play, Player* player, s32 mode);
    /* 0x18780 */ void (*func_18780)(Player* player, struct PlayState* play);
    /* 0x18784 */ s32 (*damagePlayer)(struct PlayState* play, s32 damage);
    /* 0x18788 */ void (*talkWithPlayer)(struct PlayState* play, Actor* actor);
    /* 0x1878C */ void (*unk_1878C)(struct PlayState* play);
    /* 0x18790 */ void (*unk_18790)(struct PlayState* play, s16 arg1);
    /* 0x18794 */ PlayerItemAction (*unk_18794)(struct PlayState* play, Player* player, ItemId itemId);
    /* 0x18798 */ s32 (*setPlayerTalkAnim)(struct PlayState* play, PlayerAnimationHeader* talkAnim, AnimationMode animMode);
    /* 0x1879C */ s16 playerActorCsIds[10];
    /* 0x187B0 */ MtxF viewProjectionMtxF;
    /* 0x187F0 */ Vec3f projectionMtxFDiagonal;
    /* 0x187FC */ MtxF billboardMtxF;
    /* 0x1883C */ Mtx* billboardMtx;
    /* 0x18840 */ u32 gameplayFrames;
    /* 0x18844 */ u8 unk_18844; // bool
    /* 0x18845 */ u8 haltAllActors;
    /* 0x18846 */ s16 numSetupActors;
    /* 0x18848 */ u8 numRooms;
    /* 0x1884C */ RomFile* roomList;
    /* 0x18850 */ ActorEntry* linkActorEntry;
    /* 0x18854 */ ActorEntry* setupActorList;
    /* 0x18858 */ ActorCsCamInfo* actorCsCamList;
    /* 0x1885C */ EntranceEntry* setupEntranceList;
    /* 0x18860 */ u16* setupExitList;
    /* 0x18864 */ Path* setupPathList;
    /* 0x18868 */ void* naviQuestHints; // leftover from OoT, system which processes this is removed
    /* 0x1886C */ AnimatedMaterial* sceneMaterialAnims;
    /* 0x18870 */ void* specialEffects;
    /* 0x18874 */ u8 skyboxId; // @see SkyboxId enum
    /* 0x18875 */ s8 transitionTrigger; // "fade_direction"
    /* 0x18876 */ s16 worldCoverAlpha;
    /* 0x18878 */ s16 bgCoverAlpha;
    /* 0x1887A */ u16 nextEntrance;
    /* 0x1887C */ s8 unk_1887C; // shootingGalleryStatus?
    /* 0x1887D */ s8 unk_1887D;
    /* 0x1887E */ s8 unk_1887E;
    /* 0x1887F */ u8 transitionType; // fadeTransition
    /* 0x18880 */ u8 unk_18880;
    /* 0x18884 */ CollisionCheckContext colChkCtx;
    /* 0x18B20 */ u16 envFlags[20];
    /* 0x18B48 */ u8 curSpawn;
    /* 0x18B49 */ u8 unk_18B49;
    /* 0x18B4A */ u8 transitionMode;
    /* 0x18B4C */ PreRender pauseBgPreRender;
    /* 0x18B9C */ char unk_18B9C[0x54];
    /* 0x18BF0 */ TransitionContext transitionCtx;
    /* 0x18E48 */ TransitionFade unk_18E48;
    /* 0x18E54 */ SceneTableEntry* loadedScene;
    /* 0x18E58 */ void* unk_18E58;
    /* 0x18E5C */ TexturePtr pictoPhotoI8;
    /* 0x18E60 */ void* unk_18E60;
    /* 0x18E64 */ void* unk_18E64;
    /* 0x18E68 */ void* unk_18E68; // framebuffer related to Lens of Truth
    /* 0x18E6C */ char unk_18E6C[0x3EC];
} PlayState; // size = 0x19258

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char unk_01[0x3F];
    /* 0x40 */ void* unk_40;
    /* 0x44 */ u32 unk_44;
    /* 0x48 */ u32 unk_48;
    /* 0x4C */ DmaRequest unk_4C;
    /* 0x6C */ OSMesgQueue unk_6C;
    /* 0x84 */ OSMesg unk_84[1];
    /* 0x88 */ void* unk_88;
    /* 0x8C */ uintptr_t unk_8C;
    /* 0x90 */ size_t unk_90;
    /* 0x94 */ s32 unk_94;
    /* 0x98 */ s32 unk_98;
    /* 0x9C */ s32 unk_9C;
    /* 0xA0 */ char unk_A0[0x4];
    /* 0xA4 */ s32 unk_A4;
    /* 0xA8 */ s32 unk_A8;
} BombersNotebook; // size = 0xAC

typedef enum {
    /* 0 */ PICTO_PHOTO_STATE_OFF,
    /* 1 */ PICTO_PHOTO_STATE_SETUP,
    /* 2 */ PICTO_PHOTO_STATE_PROCESS,
    /* 3 */ PICTO_PHOTO_STATE_READY
} PictoPhotoState;

typedef struct {
    /* 0x00 */ u8 mode;
    /* 0x04 */ f32 scale;
    /* 0x08 */ f32 lodProportion; // expected to be between 0.0f and 1.0f
    /* 0x0C */ Color_RGBA8_u32 primColor;
    /* 0x10 */ Color_RGBA8_u32 envColor;
} Struct_80140E80; // size = 0x14

typedef struct {
    /* 0x0 */ u32 type;
    /* 0x4 */ u32 setScissor;
    /* 0x8 */ Color_RGBA8 color;
    /* 0xC */ Color_RGBA8 envColor;
} struct_801F8010; // size = 0x10

typedef struct {
    /* 0x0 */ u32 useRgba;
    /* 0x4 */ u32 setScissor;
    /* 0x8 */ Color_RGBA8_u32 primColor;
    /* 0xC */ Color_RGBA8_u32 envColor;
} VisZbuf; // size = 0x10

typedef struct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ Color_RGBA8_u32 primColor;
    /* 0x0C */ Color_RGBA8_u32 envColor;
    /* 0x10 */ u16* tlut;
    /* 0x14 */ Gfx* dList;
} VisMono; // size = 0x18

typedef struct {
    /* 0x0 */ u8* value;
    /* 0x4 */ const char* name;
} FlagSetEntry; // size = 0x8

// TODO: Dedicated Header?
#define FRAM_BASE_ADDRESS 0x08000000           // FRAM Base Address in Cart Memory
#define FRAM_STATUS_REGISTER FRAM_BASE_ADDRESS // FRAM Base Address in Cart Memory
#define FRAM_COMMAND_REGISTER 0x10000          // Located at 0x08010000 on the Cart

enum fram_command {
    /* Does nothing for FRAM_COMMAND_SET_MODE_READ_AND_STATUS, FRAM_MODE_NOP, FRAM_COMMAND_SET_MODE_STATUS_AND_STATUS
       Initializes fram to 0xFF in FRAM_MODE_ERASE
       Writes Contents in FLASHRAM_MODE_WRITE
       After execution, sets FRAM_MODE to FRAM_MODE_NOP */
    FRAM_COMMAND_EXECUTE = 0xD2000000,
    /* flashram->erase_offset = (command & 0xFFFF) * 128; */
    FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET = 0x4B000000,
    /* flashram->mode = FLASHRAM_MODE_ERASE;
       flashram->status = 0x1111800800C20000LL; */
    FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS = 0x78000000,
    /* flashram->erase_offset = (command & 0xFFFF) * 128;
       flashram->status = 0x1111800400C20000LL; */
    FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET_AND_STATUS = 0xA5000000,
    /* flashram->mode = FLASHRAM_MODE_WRITE; */
    FRAM_COMMAND_SET_MODE_WRITE = 0xB4000000,
    /* flashram->mode = FLASHRAM_MODE_STATUS;
       flashram->status = 0x1111800100C20000LL; */
    FRAM_COMMAND_SET_MODE_STATUS_AND_STATUS = 0xE1000000,
    /* flashram->mode = FLASHRAM_MODE_READ;
       flashram->status = 0x11118004F0000000LL; */
    FRAM_COMMAND_SET_MODE_READ_AND_STATUS = 0xF0000000,
    /* unk */
    FRAM_COMMAND_UNK_ERASE_OPERATION = 0x3C000000
};

enum fram_mode {
    FRAM_MODE_NOP = 0,
    FRAM_MODE_ERASE,
    FRAM_MODE_WRITE,
    FRAM_MODE_READ,
    FRAM_MODE_STATUS
};

typedef struct {
    /* 0x00 */ UNK_TYPE1 unk_00[0x14];
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ UNK_TYPE1 unk_1A[0x3];
    /* 0x0C */ u8 unk_1D;
    /* 0x1E */ UNK_TYPE1 unk_1E[0xC];
    /* 0x2A */ s16 unk_2A;
    /* 0x1E */ UNK_TYPE1 unk_2C[0x1];
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ UNK_TYPE1 unk_2E[2];
} DbCameraUnkSubStruct; // size = 0x30

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ UNK_TYPE1 unk_0E[0x02];
    /* 0x10 */ DbCameraUnkSubStruct unk_10;
    /* 0x40 */ DbCameraUnkSubStruct unk_40;
    /* 0x70 */ UNK_PTR unk_70;
    /* 0x74 */ UNK_PTR unk_74;
    /* 0x78 */ UNK_PTR unk_78;
    /* 0x7C */ Camera* camera;
} DbCameraUnkStruct; // size = 0x80

#endif
