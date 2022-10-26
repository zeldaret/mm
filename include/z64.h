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
#include "sfx.h"
#include "message_data_static.h"

#include "gfxprint.h"
#include "sys_matrix.h"
#include "z64actor.h"
#include "z64animation.h"
#include "z64audio.h"
#include "z64bgcheck.h"
#include "z64camera.h"
#include "z64collision_check.h"
#include "z64curve.h"
#include "z64cutscene.h"
#include "z64dma.h"
#include "z64effect.h"
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
#include "z64subs.h"
#include "z64transition.h"
#include "z64view.h"
#include "regs.h"

#define Z_THREAD_ID_IDLE     1
#define Z_THREAD_ID_SLOWLY   2
#define Z_THREAD_ID_MAIN     3
#define Z_THREAD_ID_GRAPH    4
#define Z_THREAD_ID_SCHED    5
#define Z_THREAD_ID_DMAMGR  18
#define Z_THREAD_ID_IRQMGR  19

#define Z_PRIORITY_SLOWLY    5
#define Z_PRIORITY_GRAPH     9
#define Z_PRIORITY_AUDIOMGR 11
#define Z_PRIORITY_IDLE     12
#define Z_PRIORITY_MAIN     12
#define Z_PRIORITY_PADMGR   15
#define Z_PRIORITY_SCHED    16
#define Z_PRIORITY_DMAMGR   17
#define Z_PRIORITY_IRQMGR   18

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
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 reserved;
    /* 0x8 */ s16 s;
    /* 0xA */ s16 t;
    /* 0xC */ s8 r;
    /* 0xD */ s8 g;
    /* 0xE */ s8 b;
    /* 0xF */ s8 a;
} F3DVertexColor; // size = 0x10

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 reserved;
    /* 0x8 */ s16 s;
    /* 0xA */ s16 t;
    /* 0xC */ s8 normalX;
    /* 0xD */ s8 normalY;
    /* 0xE */ s8 normalZ;
    /* 0xF */ s8 a;
} F3DVertexNormal; // size = 0x10

typedef struct {
    /* 0x0 */ f32 size;
    /* 0x4 */ f32 dynamicSizeStep;
    /* 0x8 */ u8 state;
    /* 0x9 */ u8 sizeGrowsCos2;
    /* 0xA */ u8 colorsIndex;
    /* 0xB */ u8 flags;
    /* 0xC */ u8 lightParamsIndex;
} FireObjInitParams; // size = 0x10

typedef struct FireObjColors {
    /* 0x0 */ Color_RGBA8 primColor;
    /* 0x4 */ u8 lod;
    /* 0x5 */ Color_RGB8 envColor;
} FireObjColors; // size = 0x8

typedef struct FireObjLightParams {
    /* 0x0 */ s16 radius;
    /* 0x2 */ Color_RGB8 color;
    /* 0x5 */ Color_RGB8 maxColorAdj;
} FireObjLightParams; // size = 0x8

// Game Info aka. Static Context
// Data normally accessed through REG macros (see regs.h)
typedef struct {
    /* 0x00 */ u8  unk_00; // regPage;?   // 1 is first page
    /* 0x01 */ u8  unk_01; // regGroup;?  // "register" group (R, RS, RO, RP etc.)
    /* 0x02 */ u8  unk_02; // regCur;?    // selected register within page
    /* 0x03 */ u8  unk_03; // dpadLast;?
    /* 0x04 */ u32 unk_04; // repeat;?
    /* 0x08 */ UNK_TYPE1 pad_08[0xC];
    /* 0x14 */ s16 data[REG_GROUPS * REG_PER_GROUP]; // 0xAE0 entries
} GameInfo; // size = 0x15D4

typedef struct {
    /* 0x0 */ u32    size;
    /* 0x4 */ void*  bufp;
    /* 0x8 */ void*  head;
    /* 0xC */ void*  tail;
} TwoHeadArena; // size = 0x10

typedef struct {
    /* 0x0 */ u32    size;
    /* 0x4 */ Gfx*   bufp;
    /* 0x8 */ Gfx*   p;
    /* 0xC */ Gfx*   d;
} TwoHeadGfxArena; // size = 0x10

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
    /* 0x2EB */ u8          framebufferIdx;
    /* 0x2EC */ void        (*callback)(struct GraphicsContext*, u32);
    /* 0x2F0 */ u32         callbackParam;
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

typedef void(*osCreateThread_func)(void*);

typedef enum {
    SLOWLY_CALLBACK_NO_ARGS,
    SLOWLY_CALLBACK_ONE_ARG,
    SLOWLY_CALLBACK_TWO_ARGS
} SlowlyCallbackArgCount;

typedef struct {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ u8 callbackArgCount;
    /* 0x1B1 */ u8 status;
    /* 0x1B4 */ union {
        void (*callback0)(void);
        void (*callback1)(void*);
        void (*callback2)(void*, void*);
    };
    /* 0x1B8 */ void* callbackArg0;
    /* 0x1BC */ void* callbackArg1;
} SlowlyTask; // size = 0x1C0

typedef struct {
    /* 0x00 */ int unk0;
    /* 0x04 */ void* unk4;
    /* 0x08 */ int unk8;
    /* 0x0C */ int unkC;
    /* 0x10 */ int unk10;
    /* 0x14 */ OSMesgQueue unk14;
} s80185D40; // size = 0x2C

typedef struct {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ UNK_TYPE1 pad7[0x2];
    /* 0x09 */ u8 unk9;
    /* 0x0A */ UNK_TYPE1 padA[0x2];
    /* 0x0C */ u32 unkC;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ UNK_TYPE1 pad16[0x2];
    /* 0x18 */ u32 unk18;
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ u32 unk20;
    /* 0x24 */ u32 unk24;
    /* 0x28 */ u32 unk28;
    /* 0x2C */ u32 unk2C;
    /* 0x30 */ u32 unk30;
    /* 0x34 */ u32 unk34;
} s8018CFAC; // size = 0x38

typedef struct {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f unkC;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
} s80874650; // size = 0x1C

typedef union {
    F3DVertexColor color;
    F3DVertexNormal normal;
} F3DVertex; // size = 0x10

// End of RDRAM without the Expansion Pak installed
#define NORMAL_RDRAM_END 0x80400000
// End of RDRAM with the Expansion Pak installed
#define EXPANDED_RDRAM_END 0x80800000
// Address at the end of normal RDRAM after which is room for a screen buffer
#define FAULT_FB_ADDRESS (NORMAL_RDRAM_END - sizeof(u16[SCREEN_HEIGHT][SCREEN_WIDTH]))

typedef void (*FaultDrawerCallback)(void);

typedef struct {
    /* 0x00 */ u16* fb;
    /* 0x04 */ u16 w;
    /* 0x06 */ u16 h;
    /* 0x08 */ u16 yStart;
    /* 0x0A */ u16 yEnd;
    /* 0x0C */ u16 xStart;
    /* 0x0E */ u16 xEnd;
    /* 0x10 */ u16 foreColor;
    /* 0x12 */ u16 backColor;
    /* 0x14 */ u16 cursorX;
    /* 0x16 */ u16 cursorY;
    /* 0x18 */ const u32* font;
    /* 0x1C */ u8 charW;
    /* 0x1D */ u8 charH;
    /* 0x1E */ s8 charWPad;
    /* 0x1F */ s8 charHPad;
    /* 0x20 */ u16 printColors[10];
    /* 0x34 */ u8 escCode;
    /* 0x35 */ u8 osSyncPrintfEnabled;
    /* 0x38 */ FaultDrawerCallback inputCallback;
} FaultDrawer; // size = 0x3C

typedef struct {
    /* 0x00 */ u8 countdown;
    /* 0x01 */ u8 playSfxEachFrame;
    /* 0x02 */ u16 sfxId;
    /* 0x04 */ Vec3f worldPos;
    /* 0x10 */ Vec3f projectedPos;
} SoundSource; // size = 0x1C

typedef void(*fault_update_input_func)(Input* input);

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
    /* 0x000 */ View view;
    /* 0x168 */ Vtx* actionVtx;
    /* 0x16C */ Vtx* beatingHeartVtx;
    /* 0x170 */ u8* parameterSegment;
    /* 0x174 */ u8* doActionSegment;
    /* 0x178 */ u8* iconItemSegment;
    /* 0x17C */ u8* mapSegment;
    /* 0x180 */ u8* unk_180;
    /* 0x184 */ DmaRequest dmaRequest_184;
    /* 0x1A4 */ DmaRequest dmaRequest_1A4;
    /* 0x1C4 */ DmaRequest dmaRequest_1C4;
    /* 0x1E4 */ OSMesgQueue loadQueue;
    /* 0x1FC */ OSMesg loadMsg;
    /* 0x200 */ Viewport viewport;
    /* 0x210 */ s16 unk_210;
    /* 0x212 */ u16 unk_212;
    /* 0x214 */ u16 unk_214;
    /* 0x218 */ f32 unk_218;
    /* 0x21C */ s16 unk_21C;
    /* 0x21E */ s16 bButtonDoAction;
    /* 0x220 */ s16 unk_220;
    /* 0x222 */ s16 unk_222;
    /* 0x224 */ s16 unk_224;
    /* 0x226 */ s16 lifeColorChange;
    /* 0x228 */ s16 lifeColorChangeDirection;
    /* 0x22A */ s16 beatingHeartPrim[3];
    /* 0x230 */ s16 beatingHeartEnv[3];
    /* 0x236 */ s16 heartsPrimR[2];
    /* 0x23A */ s16 heartsPrimG[2];
    /* 0x23E */ s16 heartsPrimB[2];
    /* 0x242 */ s16 heartsEnvR[2];
    /* 0x246 */ s16 heartsEnvG[2];
    /* 0x24A */ s16 heartsEnvB[2];
    /* 0x24E */ s16 health;
    /* 0x250 */ s16 unkTimer;
    /* 0x252 */ s16 lifeSizeChange;
    /* 0x254 */ s16 lifeSizeChangeDirection; // 1 means shrinking, 0 growing
    /* 0x256 */ s16 unk_256;
    /* 0x258 */ s16 magicConsumptionTimer; // For certain magic states, 1 unit of magic is consumed every time the timer reaches 0
    /* 0x25A */ u8 numHorseBoosts;
    /* 0x25C */ u16 unk_25C;
    /* 0x25E */ u16 unk_25E;
    /* 0x260 */ u16 hbaAmmo;
    /* 0x262 */ u16 unk_262;
    /* 0x264 */ s16 unk_264;
    /* 0x266 */ s16 aAlpha;
    /* 0x268 */ s16 bAlpha;
    /* 0x26A */ s16 cLeftAlpha;
    /* 0x26C */ s16 cDownAlpha;
    /* 0x26E */ s16 cRightAlpha;
    /* 0x270 */ s16 healthAlpha;
    /* 0x272 */ s16 magicAlpha;
    /* 0x274 */ s16 minimapAlpha;
    /* 0x276 */ s16 startAlpha;
    /* 0x278 */ s16 unk_278;
    /* 0x27A */ s16 dungeonOrBossAreaMapIndex;
    /* 0x27C */ s16 mapRoomNum;
    /* 0x27E */ u8 unk_27E;
    /* 0x27F */ u8 unk_27F;
    /* 0x280 */ u8 unk_280;
    /* 0x282 */ s16 unk_282;
    /* 0x284 */ s16 unk_284;
    /* 0x286 */ s16 unk_286;
    /* 0x288 */ s16 unk_288;
    /* 0x28A */ s16 unk_28A[8];
    /* 0x29A */ u16 unk_29A[8];
    /* 0x2AA */ s16 unk_2AA[8];
    /* 0x2BC */ f32 unk_2BC[8];
    /* 0x2DC */ f32 unk_2DC[8];
    /* 0x2FC */ s16 unk_2FC[4];
    /* 0x304 */ s16 unk_304;
    /* 0x306 */ s16 unk_306;
    /* 0x308 */ s16 unk_308;
    /* 0x30A */ s16 unk_30A;
    /* 0x30C */ s16 unk_30C;
    struct {
        /* 0x30E */ u8 unk_30E; // "h_gauge"
        /* 0x30F */ u8 bButton;
        /* 0x310 */ u8 aButton;
        /* 0x311 */ u8 tradeItems;
        /* 0x312 */ u8 unk_312;
        /* 0x313 */ u8 unk_313;
        /* 0x314 */ u8 unk_314;
        /* 0x315 */ u8 songOfSoaring;
        /* 0x316 */ u8 songOfStorms;
        /* 0x317 */ u8 unk_317;
        /* 0x318 */ u8 pictographBox;
        /* 0x319 */ u8 all;     // "another"; enables all item restrictions
    } restrictions; // size = 0xC
    /* 0x31A */ u8 storyState;
    /* 0x31B */ u8 storyType;
    /* 0x31C */ u8 unk_31C;
    /* 0x320 */ OSMesgQueue unk_320;
    /* 0x338 */ OSMesg unk_338;
    /* 0x33C */ void* unk_33C;
    /* 0x340 */ u32 unk_340;
    /* 0x344 */ u32 unk_344;
} InterfaceContext; // size = 0x348

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
    /* 0x02 */ u16 timeIncrement;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ f32 unk_C;
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
    /* 0xEB */ u8 unk_EB;
    /* 0xEC */ u8 unk_EC;
    /* 0xED */ u8 unk_ED;
    /* 0xEE */ u8 unk_EE[4];
    /* 0xF2 */ u8 unk_F2[8]; // [3] is used by both DemoKankyo and ObjectKankyo effect count
    /* 0xFA */ u8 unk_FA[4];
} EnvironmentContext; // size = 0x100

typedef struct {
    /* 0x000 */ View view;
    /* 0x168 */ void* skyboxStaticSegment[4];
    /* 0x178 */ void* skyboxPaletteStaticSegment;
    /* 0x17C */ Gfx* dListBuf;
    /* 0x180 */ Gfx* roomDL;
    /* 0x184 */ Vtx* roomVtx;
    /* 0x188 */ DmaRequest unk188;
    /* 0x1A8 */ DmaRequest unk1A8;
    /* 0x1C8 */ DmaRequest unk1C8;
    /* 0x1E8 */ OSMesgQueue loadQueue;
    /* 0x200 */ OSMesg loadMsg;
    /* 0x204 */ s16 skyboxShouldDraw;
    /* 0x208 */ f32 rotX;
    /* 0x20C */ f32 rotY;
    /* 0x210 */ f32 rotZ;
    /* 0x214 */ Vec3f eye;
    /* 0x220 */ s16 angle;
    /* 0x222 */ u8 primR;
    /* 0x223 */ u8 primG;
    /* 0x224 */ u8 primB;
    /* 0x225 */ u8 envR;
    /* 0x226 */ u8 envG;
    /* 0x227 */ u8 envB;
} SkyboxContext; // size = 0x228

typedef enum {
    /* 0x05 */ SKYBOX_CUTSCENE_MAP = 5
} SkyboxId;

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

#define TRANS_TRIGGER_OFF 0 // transition is not active
#define TRANS_TRIGGER_START 20 // start transition (exiting an area)
#define TRANS_TRIGGER_END -20 // transition is ending (arriving in a new area)

typedef enum TransitionMode {
    /*  0 */ TRANS_MODE_OFF,
    /*  1 */ TRANS_MODE_01,
    /*  2 */ TRANS_MODE_02,
    /*  3 */ TRANS_MODE_03,
    /*  4 */ TRANS_MODE_04,
    /*  5 */ TRANS_MODE_05,
    /*  6 */ TRANS_MODE_06,
    /*  7 */ TRANS_MODE_07,
    /*  8 */ TRANS_MODE_08,
    /*  9 */ TRANS_MODE_09,
    /* 10 */ TRANS_MODE_10,
    /* 11 */ TRANS_MODE_11,
    /* 12 */ TRANS_MODE_12,
    /* 13 */ TRANS_MODE_13,
    /* 14 */ TRANS_MODE_14,
    /* 15 */ TRANS_MODE_15,
    /* 16 */ TRANS_MODE_16,
    /* 17 */ TRANS_MODE_17
} TransitionMode;

typedef enum TransitionType {
    /*  0 */ TRANS_TYPE_00,
    /*  1 */ TRANS_TYPE_01,
    /*  2 */ TRANS_TYPE_02,
    /*  3 */ TRANS_TYPE_03,
    /*  4 */ TRANS_TYPE_04,
    /*  5 */ TRANS_TYPE_05,
    /*  6 */ TRANS_TYPE_06,
    /*  7 */ TRANS_TYPE_07,
    /*  8 */ TRANS_TYPE_08,
    /*  9 */ TRANS_TYPE_09, 
    /* 10 */ TRANS_TYPE_10,
    /* 11 */ TRANS_TYPE_11,
    /* 12 */ TRANS_TYPE_12,
    /* 13 */ TRANS_TYPE_13,
    /* 14 */ TRANS_TYPE_14,
    /* 15 */ TRANS_TYPE_15,
    /* 16 */ TRANS_TYPE_16,
    /* 17 */ TRANS_TYPE_17,
    /* 18 */ TRANS_TYPE_18,
    /* 19 */ TRANS_TYPE_19,
    /* 20 */ TRANS_TYPE_20,
    /* 21 */ TRANS_TYPE_21,
    /* 64 */ TRANS_TYPE_64 = 64,
    /* 70 */ TRANS_TYPE_70 = 70,
    /* 72 */ TRANS_TYPE_72 = 72,
    /* 73 */ TRANS_TYPE_73,
    /* 80 */ TRANS_TYPE_80 = 80,
    /* 86 */ TRANS_TYPE_86 = 86
} TransitionType;

#define TRANS_NEXT_TYPE_DEFAULT 0xFF

typedef struct FaultAddrConvClient {
    /* 0x0 */ struct FaultAddrConvClient* next;
    /* 0x4 */ void* (*callback)(void*, void*);
    /* 0x8 */ void* param;
} FaultAddrConvClient; // size = 0xC

typedef struct FaultClient {
    /* 0x0 */ struct FaultClient* next;
    /* 0x4 */ void (*callback)(void*, void*);
    /* 0x8 */ void* param0;
    /* 0xC */ void* param1;
} FaultClient; // size = 0x10

typedef struct {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ u8 stack[1536]; // Seems leftover from an earlier version. The thread actually uses a stack of this size at 0x8009BE60
    /* 0x7B0 */ OSMesgQueue queue;
    /* 0x7C8 */ OSMesg msg[1];
    /* 0x7CC */ u8 exitDebugger;
    /* 0x7CD */ u8 msgId; // 1 - CPU Break; 2 - Fault; 3 - Unknown
    /* 0x7CE */ u8 faultHandlerEnabled;
    /* 0x7CF */ u8 faultActive;
    /* 0x7D0 */ OSThread* faultedThread;
    /* 0x7D4 */ fault_update_input_func padCallback;
    /* 0x7D8 */ FaultClient* clients;
    /* 0x7DC */ FaultAddrConvClient* addrConvClients;
    /* 0x7E0 */ UNK_TYPE1 pad7E0[0x4];
    /* 0x7E4 */ Input padInput[4];
    /* 0x844 */ void* fb;
} FaultThreadStruct; // size = 0x848

typedef struct FireObj FireObj;

typedef struct FireObjLight FireObjLight;

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

typedef struct {
    /* 0x00 */ u32 resetting;
    /* 0x04 */ u32 resetCount;
    /* 0x08 */ OSTime duration;
    /* 0x10 */ OSTime resetTime;
} PreNmiBuff; // size = 0x18 (actually osAppNmiBuffer is 0x40 bytes large but the rest is unused)

typedef struct PlayState PlayState;

typedef s32 (*ColChkResetFunc)(PlayState*, Collider*);
typedef void (*ColChkBloodFunc)(PlayState*, Collider*, Vec3f*);
typedef void (*ColChkApplyFunc)(PlayState*, CollisionCheckContext*, Collider*);
typedef void (*ColChkVsFunc)(PlayState*, CollisionCheckContext*, Collider*, Collider*);
typedef s32 (*ColChkLineFunc)(PlayState*, CollisionCheckContext*, Collider*, Vec3f*, Vec3f*);

typedef void(*room_draw_func)(PlayState* play, Room* room, u32 flags);

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

typedef struct StackEntry {
    /* 0x00 */ struct StackEntry* next;
    /* 0x04 */ struct StackEntry* prev;
    /* 0x08 */ u32 head;
    /* 0x0C */ u32 tail;
    /* 0x10 */ u32 initValue;
    /* 0x14 */ s32 minSpace;
    /* 0x18 */ const char* name;
} StackEntry; // size = 0x1C

typedef enum {
    STACK_STATUS_OK = 0,
    STACK_STATUS_WARNING = 1,
    STACK_STATUS_OVERFLOW = 2
} StackStatus;

struct FireObjLight {
    /* 0x00 */ LightNode* light;
    /* 0x04 */ LightInfo lightInfo;
    /* 0x12 */ u8 lightParamsIndex;
}; // size = 0x14

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
    /* 0x00 */ MtxF displayMatrix;
    /* 0x40 */ Actor* actor;
    /* 0x44 */ Vec3f location;
    /* 0x50 */ u8 flags; // bit 0 - footmark fades out
    /* 0x51 */ u8 id;
    /* 0x52 */ u8 red;
    /* 0x53 */ u8 blue;
    /* 0x54 */ u8 green;
    /* 0x55 */ UNK_TYPE1 pad55[0x1];
    /* 0x56 */ u16 alpha;
    /* 0x58 */ u16 alphaChange;
    /* 0x5A */ u16 size;
    /* 0x5C */ u16 fadeoutDelay;
    /* 0x5E */ u16 age;
} EffFootmark; // size = 0x60

struct FireObj {
    /* 0x00 */ Vec3f position;
    /* 0x0C */ f32 size;
    /* 0x10 */ f32 sizeInv;
    /* 0x14 */ f32 xScale;
    /* 0x18 */ f32 yScale;
    /* 0x1C */ f32 dynamicSize;
    /* 0x20 */ f32 dynamicSizeStep;
    /* 0x24 */ u8 state; // 0 - growing, 1 - shrinking, 2 - fully lit, 3 - not lit
    /* 0x25 */ u8 sizeGrowsCos2;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 colorsIndex;
    /* 0x28 */ u8 flags; // bit 0 - ?, bit 1 - ?
    /* 0x29 */ UNK_TYPE1 pad29[0x1];
    /* 0x2A */ s16 ignitionDelay;
    /* 0x2C */ ColliderCylinder collision;
    /* 0x78 */ FireObjLight light;
}; // size = 0x8B

typedef struct {
    /* 0x0 */ u8   seqId;
    /* 0x1 */ u8   ambienceId;
} SequenceContext; // size = 0x2

typedef struct {
    /* 0x0 */ s32 enabled;
    /* 0x4 */ s32 timer;
} FrameAdvanceContext; // size = 0x8

typedef enum {
    /*  0 */ GAMEOVER_INACTIVE,
    /*  1 */ GAMEOVER_DEATH_START,
    /*  2 */ GAMEOVER_DEATH_WAIT_GROUND,    // wait for player to fall and hit the ground
    /*  3 */ GAMEOVER_DEATH_FADE_OUT,       // wait before fading out
    /* 20 */ GAMEOVER_REVIVE_START = 20,
    /* 21 */ GAMEOVER_REVIVE_RUMBLE,
    /* 22 */ GAMEOVER_REVIVE_WAIT_GROUND,   // wait for player to fall and hit the ground
    /* 23 */ GAMEOVER_REVIVE_WAIT_FAIRY,    // wait for the fairy to rise all the way up out of player's body
    /* 24 */ GAMEOVER_REVIVE_FADE_OUT       // fade out the game over lights as player is revived and gets back up
} GameOverState;

typedef struct {
    /* 0x0 */ u16 state;
} GameOverContext; // size = 0x2

struct PlayState {
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
    /* 0x18790 */ void (*unk_18790)(struct PlayState* play, s16 arg1, Actor* actor);
    /* 0x18794 */ s32 (*unk_18794)(struct PlayState* play, Player* player, s32 itemId, s32 arg3);
    /* 0x18798 */ s32 (*setPlayerTalkAnim)(struct PlayState* play, void* talkAnim, s32 arg2);
    /* 0x1879C */ s16 playerActorCsIds[10];
    /* 0x187B0 */ MtxF viewProjectionMtxF;
    /* 0x187F0 */ Vec3f unk_187F0;
    /* 0x187FC */ MtxF billboardMtxF;
    /* 0x1883C */ Mtx* billboardMtx;
    /* 0x18840 */ u32 gameplayFrames;
    /* 0x18844 */ u8 unk_18844;
    /* 0x18845 */ u8 unk_18845;
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
    /* 0x18874 */ u8 skyboxId;
    /* 0x18875 */ s8 transitionTrigger; // "fade_direction"
    /* 0x18876 */ s16 unk_18876;
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
    /* 0x18B9C */ char unk_18B9C[0x2B8];
    /* 0x18E54 */ SceneTableEntry* loadedScene;
    /* 0x18E58 */ char unk_18E58[0x10];
    /* 0x18E68 */ void* unk_18E68;
    /* 0x18E6C */ char unk_18E6C[0x3EC];
}; // size = 0x19258

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} struct_801C5F44; // size = 0x14

// From OoT's struct_80034A14_arg1
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ Vec3s unk_08;
    /* 0x0E */ Vec3s unk_0E;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ Vec3f unk_18; // Usually setted to Player's position or Player's focus
    /* 0x24 */ s16 unk_24;
} struct_800BD888_arg1; // size = 0x28

typedef struct {
    /* 0x0 */ u32 type;
    /* 0x4 */ u32 setScissor;
    /* 0x8 */ Color_RGBA8 color;
    /* 0xC */ Color_RGBA8 envColor;
} struct_801F8010; // size = 0x10

typedef struct {
    /* 0x0 */ u32 useRgba;
    /* 0x4 */ u32 setScissor;
    /* 0x8 */ Color_RGBA8 primColor;
    /* 0xC */ Color_RGBA8 envColor;
} struct_801F8020; // size = 0x10

typedef struct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ Color_RGBA8_u32 primColor;
    /* 0x0C */ Color_RGBA8_u32 envColor;
    /* 0x10 */ u16* tlut;
    /* 0x14 */ Gfx* dList;
} VisMono; // size = 0x18

typedef struct DebugDispObject {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3s rot;
    /* 0x14 */ Vec3f scale;
    /* 0x20 */ Color_RGBA8 color;
    /* 0x24 */ s16   type;
    /* 0x28 */ struct DebugDispObject* next;
    /* 0x2C */ s32 pad; //Padding not in the OOT version
} DebugDispObject; // size = 0x30

typedef struct {
    /* 0x0 */ f32 rangeSq;
    /* 0x4 */ f32 leashScale;
} TargetRangeParams; // size = 0x8

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
