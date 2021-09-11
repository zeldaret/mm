#ifndef Z64_H
#define Z64_H

#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"

#include "PR/ultratypes.h"
#include "PR/gbi.h"
#include "io/controller.h"
#include "osint.h"
#include "viint.h"
#include "math.h"
#include "os.h"
#include "stdlib.h"
#include "xstdio.h"
#include "unk.h"

#include "sfx.h"
#include "color.h"
#include "ichain.h"

#include "z64actor.h"
#include "z64animation.h"
#include "z64bgcheck.h"
#include "z64collision_check.h"
#include "z64cutscene.h"
#include "z64dma.h"
#include "z64effect.h"
#include "z64item.h"
#include "z64light.h"
#include "z64math.h"
#include "z64object.h"
#include "z64player.h"
#include "z64scene.h"
#include "z64save.h"
#include "z64transition.h"

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define SCREEN_WIDTH_HIGH_RES  576
#define SCREEN_HEIGHT_HIGH_RES 454

#define Z_THREAD_ID_IDLE     1
#define Z_THREAD_ID_SLOWLY   2
#define Z_THREAD_ID_MAIN     3
#define Z_THREAD_ID_SCHED    5
#define Z_THREAD_ID_DMAMGR  18
#define Z_THREAD_ID_IRQMGR  19

#define Z_PRIORITY_SLOWLY  5
#define Z_PRIORITY_GRAPH   9
#define Z_PRIORITY_IDLE   12
#define Z_PRIORITY_MAIN   12
#define Z_PRIORITY_DMAMGR 17
#define Z_PRIORITY_IRQMGR 18

#define EQUIP_SLOT_B 0
#define EQUIP_SLOT_C_LEFT 1
#define EQUIP_SLOT_C_DOWN 2
#define EQUIP_SLOT_C_RIGHT 3

typedef struct {
    /* 0x0 */ s16 priority; // Lower means higher priority. -1 means it ignores priority
    /* 0x2 */ s16 length;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 additionalCutscene;
    /* 0xA */ u8 sound;
    /* 0xB */ u8 unkB;
    /* 0xC */ s16 unkC;
    /* 0xE */ u8 unkE;
    /* 0xF */ u8 letterboxSize;
} ActorCutscene; // size = 0x10

typedef struct {
    /* 0x0 */ s16 polyStartIndex;
    /* 0x2 */ s16 ceilingNodeHead;
    /* 0x4 */ s16 wallNodeHead;
    /* 0x6 */ s16 floorNodeHead;
} ActorMeshPolyLists; // size = 0x8

typedef struct {
    /* 0x0 */ s8 segment;
    /* 0x2 */ s16 type;
    /* 0x4 */ void* params;
} AnimatedMaterial; // size = 0x8

typedef struct {
    /* 0x00 */ Vec3s pos;
    /* 0x06 */ s16   unk_06;
    /* 0x08 */ Gfx*  opa;
    /* 0x0C */ Gfx*  xlu;
} PolygonDlist2; // size = 0x8

typedef struct {
    /* 0x00 */ u8    type;
    /* 0x01 */ u8    num; // number of dlist entries
    /* 0x04 */ void* start;
    /* 0x08 */ void* end;
} PolygonType2; // size = 0xC

typedef struct {
    /* 0x0 */ u16 floorHead;
    /* 0x2 */ u16 wallHead;
    /* 0x4 */ u16 ceilingHead;
} BgMeshSubdivision; // size = 0x6

typedef struct {
    /* 0x0 */ u32 attributes[2];
} BgPolygonAttributes; // size = 0x8

typedef struct {
    /* 0x0 */ s16 polyIndex;
    /* 0x2 */ u16 next;
} BgPolygonLinkedListNode; // size = 0x4

typedef struct {
    /* 0x0 */ u16 maxNodes;
    /* 0x2 */ u16 reservedNodes;
    /* 0x4 */ BgPolygonLinkedListNode* nodes;
    /* 0x8 */ u8* unk8;
} BgScenePolygonLists; // size = 0xC

typedef struct {
    /* 0x0 */ s16 sceneNumber;
    /* 0x2 */ UNK_TYPE1 pad2[0x2];
    /* 0x4 */ u32 maxMemory;
} BgSpecialSceneMaxMemory; // size = 0x8

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x2 */ s16 maxNodes;
    /* 0x4 */ s16 maxPolygons;
    /* 0x6 */ s16 maxVertices;
} BgSpecialSceneMaxObjects; // size = 0x8

typedef struct {
    /* 0x0 */ s16 sceneNumber;
    /* 0x2 */ s16 xSubdivisions;
    /* 0x4 */ s16 ySubdivisions;
    /* 0x6 */ s16 zSubdivisions;
    /* 0x8 */ s32 unk8;
} BgSpecialSceneMeshSubdivision; // size = 0xC

typedef struct {
    /* 0x0 */ s16 func;
    /* 0x2 */ UNK_TYPE1 pad2[0x6];
} CameraModeParams; // size = 0x8

typedef struct {
    /* 0x0 */ u32 validModes;
    /* 0x4 */ UNK_TYPE1 pad4[0x4];
    /* 0x8 */ CameraModeParams* modes;
} CameraStateParams; // size = 0xC

typedef struct {
    /* 0x00 */ u8    sceneCsCount;
    /* 0x04 */ void* segment;
    /* 0x08 */ u8    state;
    /* 0x0C */ f32   unk_0C;
    /* 0x10 */ u16   frames;
    /* 0x12 */ u16   unk_12;
    /* 0x14 */ s32   unk_14;
    /* 0x18 */ u16   unk_18;
    /* 0x1A */ u8    unk_1A;
    /* 0x1B */ u8    unk_1B;
    /* 0x1C */ CutsceneCameraPoint* cameraFocus;
    /* 0x20 */ CutsceneCameraPoint* cameraPosition;
    /* 0x24 */ CsCmdActorAction* linkAction;
    /* 0x28 */ CsCmdActorAction* npcActions[10]; // "npcdemopnt"
    /* 0x50 */ CutsceneEntry* sceneCsList;
} CutsceneContext; // size = 0x54

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
    /* 0xA */ u8 unkA;
    /* 0xB */ u8 flags;
    /* 0xC */ u8 unkC;
} FireObjInitParams; // size = 0xD

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} FireObjLightParams; // size = 0x8

//! TODO: Make this use `sizeof(AnyFontTextureSymbol)`
#define FONT_CHAR_TEX_SIZE ((16 * 16) / 2)

// Font textures are loaded into here
typedef struct {
    /* 0x00000 */ u8 charBuf[2][FONT_CHAR_TEX_SIZE * 120];
    /* 0x07800 */ u8 iconBuf[FONT_CHAR_TEX_SIZE];
    /* 0x07880 */ u8 fontBuf[FONT_CHAR_TEX_SIZE * 320];
    /* 0x11880 */ union {
        u8 schar[640];
        u16 wchar[640];
    } msgBuf;
    /* 0x11D80 */ u8* messageStart;
    /* 0x11D84 */ u8* messageEnd;
    /* 0x11D88 */ u8 unk_11D88;
} Font; // size = 0x11D8C

typedef struct {
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ UNK_TYPE1 pad8[0xC];
    /* 0x0014 */ s16 data[2784]; // Accessed through REG macros
} GameInfo; // size = 0x15D4

typedef struct {
    /* 0x0000 */ u32    size;
    /* 0x0004 */ void*  bufp;
    /* 0x0008 */ void*  head;
    /* 0x000C */ void*  tail;
} TwoHeadArena; // size = 0x10

typedef struct {
    /* 0x0000 */ u32    size;
    /* 0x0004 */ Gfx*   bufp;
    /* 0x0008 */ Gfx*   p;
    /* 0x000C */ Gfx*   d;
} TwoHeadGfxArena; // size = 0x10

typedef struct {
    /* 0x00000 */ u16 headMagic; // 1234
    /* 0x00008 */ Gfx unk8[96];
    /* 0x00308 */ Gfx polyXluBuffer[2048];
    /* 0x04308 */ Gfx overlayBuffer[1024];
    /* 0x06308 */ Gfx unk6308[64];
    /* 0x06508 */ Gfx unk6508[64];
    /* 0x06708 */ Gfx polyOpaBuffer[13184];
    /* 0x20308 */ u16 tailMagic; // 5678
} GfxPool; // size = 0x20310

typedef struct {
    /* 0x00 */ u16*     fb1;
    /* 0x04 */ u16*     swapBuffer;
    /* 0x08 */ OSViMode* viMode;
    /* 0x0C */ u32      features;
    /* 0x10 */ u8       unk_10;
    /* 0x11 */ s8       updateRate;
    /* 0x12 */ s8       updateRate2;
    /* 0x13 */ u8       unk_13;
    /* 0x14 */ f32      xScale;
    /* 0x18 */ f32      yScale;
} CfbInfo; // size = 0x1C

typedef struct GraphicsContext {
    /* 0x000 */ Gfx* polyOpaBuffer;
    /* 0x004 */ Gfx* polyXluBuffer;
    /* 0x008 */ UNK_TYPE1 pad8[0x8];
    /* 0x010 */ Gfx* overlayBuffer;
    /* 0x014 */ UNK_TYPE1 pad14[0x24];
    /* 0x038 */ UNK_TYPE4 unk38[8];
    /* 0x058 */ OSMesgQueue* unk58;
    /* 0x05C */ OSMesgQueue unk5C;
    /* 0x074 */ UNK_TYPE1 pad74[0x12C];
    /* 0x1A0 */ Gfx* unk1A0;
    /* 0x1A4 */ TwoHeadGfxArena unk1A4;
    /* 0x1B4 */ Gfx* unk1B4;
    /* 0x1B8 */ TwoHeadGfxArena unk1B8;
    /* 0x1C8 */ UNK_TYPE1 pad1C8[0xAC];
    /* 0x274 */ OSViMode* unk274;
    /* 0x278 */ void* zbuffer;
    /* 0x27C */ UNK_TYPE1 pad27C[0x1C];
    /* 0x298 */ TwoHeadGfxArena overlay;
    /* 0x2A8 */ TwoHeadGfxArena polyOpa;
    /* 0x2B8 */ TwoHeadGfxArena polyXlu;
    /* 0x2C8 */ s32 displaylistCounter;
    /* 0x2CC */ void* framebuffer;
    /* 0x2D0 */ int pad2D0;
    /* 0x2D4 */ u32 viConfigFeatures;
    /* 0x2D8 */ UNK_TYPE1 gap2D8[0x3];
    /* 0x2DB */ u8 framebufferCounter;
    /* 0x2DC */ UNK_TYPE1 pad2DC[0x8];
    /* 0x2E4 */ f32 viConfigXScale;
    /* 0x2E8 */ f32 viConfigYScale;
    /* 0x2EC */ UNK_TYPE1 pad2EC[0x4];
} GraphicsContext; // size = 0x2F0

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
    /* 0x00 */ u32 textSize;
    /* 0x04 */ u32 dataSize;
    /* 0x08 */ u32 rodataSize;
    /* 0x0C */ u32 bssSize;
    /* 0x10 */ u32 nRelocations;
    /* 0x14 */ u32 relocations[1];
} OverlayRelocationSection; // size >= 0x18

typedef struct {
    /* 0x00 */ s16 intPart[16];
    /* 0x20 */ u16 fracPart[16];
} RSPMatrix; // size = 0x40

typedef struct {
    /* 0x0 */ s8 letterboxTarget;
    /* 0x1 */ s8 letterboxMagnitude;
    /* 0x2 */ s8 pillarboxTarget;
    /* 0x3 */ s8 pillarboxMagnitude;
} ShrinkWindowContext; // size = 0x4

typedef struct {
    /* 0x00 */ u8* readBuff;
    /* 0x04 */ u32* flashReadBuff;
    /* 0x08 */ char unk_08[4];
    /* 0x0C */ s16 status;
    /* 0x10 */ u32 curPage;
    /* 0x14 */ u32 numPages;
    /* 0x18 */ OSTime unk_18;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s16 unk_24;
} SramContext; // size = 0x28

typedef struct {
    /* 0x00 */ UNK_TYPE4 unk0;
    /* 0x04 */ UNK_TYPE4 unk4;
    /* 0x08 */ UNK_TYPE4 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ Color_RGBA8 unk10;
} TargetContextEntry; // size = 0x14

typedef struct {
    /* 0x0 */ u32 texture;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ u8 fadeOutDelay;
    /* 0xB */ u8 fadeInDelay;
    /* 0xC */ s16 alpha;
    /* 0xE */ s16 color;
} TitleCardContext; // size = 0x10

typedef struct {
    /* 0x0 */ s32 topY;
    /* 0x4 */ s32 bottomY;
    /* 0x8 */ s32 leftX;
    /* 0xC */ s32 rightX;
} Viewport; // size = 0x10

typedef void*(*fault_address_converter_func)(void* addr, void* arg);

typedef void(*fault_client_func)(void* arg1, void* arg2);

typedef unsigned long(*func)(void);

typedef void(*func_ptr)(void);

typedef void(*osCreateThread_func)(void*);

typedef void* (*PrintCallback)(void*, const char*, u32);

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
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
} s801AEC84; // size = 0x8

typedef struct {
    /* 0x00 */ UNK_TYPE1 pad0[0x14];
} s801FE7C0; // size = 0x14

typedef struct {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f unkC;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
} s80874650; // size = 0x1C

typedef struct {
    /* 0x00 */ Vec3f scale;
    /* 0x0C */ Vec3s rotation;
    /* 0x14 */ Vec3f pos;
} ActorMeshParams; // size = 0x20

typedef struct {
    /* 0x0 */ BgPolygonLinkedListNode* nodes;
    /* 0x4 */ u32 nextFreeNode;
    /* 0x8 */ s32 maxNodes;
} BgPolygonLinkedList; // size = 0xC

typedef struct {
    /* 0x00 */ f32 x[4];
    /* 0x10 */ f32 y[4];
    /* 0x20 */ f32 z[4];
    /* 0x30 */ f32 w[4];
} z_Matrix; // size = 0x40

typedef struct {
    /* 0x0 */ Vec3s pos;
} BgVertex; // size = 0x6

typedef union {
    F3DVertexColor color;
    F3DVertexNormal normal;
} F3DVertex; // size = 0x10

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
    /* 0x18 */ u32* font;
    /* 0x1C */ u8 charW;
    /* 0x1D */ u8 charH;
    /* 0x1E */ s8 charWPad;
    /* 0x1F */ s8 charHPad;
    /* 0x20 */ u16 printColors[10];
    /* 0x34 */ u8 escCode;
    /* 0x35 */ u8 osSyncPrintfEnabled;
    /* 0x38 */ func_ptr inputCallback;
} FaultDrawer; // size = 0x3C

typedef struct GfxPrint {
    /* 0x00 */ struct GfxPrint *(*callback)(struct GfxPrint*, const char*, size_t);
    /* 0x04 */ Gfx* dlist;
    /* 0x08 */ u16 posX;
    /* 0x0A */ u16 posY;
    /* 0x0C */ u16 baseX;
    /* 0x0E */ u8 baseY;
    /* 0x0F */ u8 flag;
    /* 0x10 */ Color_RGBA8_u32 color;
    /* 0x14 */ char unk_14[0x1C]; // unused
} GfxPrint; // size = 0x30

typedef enum {
    GFXPRINT_FLAG1 = 1,
    GFXPRINT_USE_RGBA16 = 2,
    GFXPRINT_FLAG4 = 4,
    GFXPRINT_UPDATE_MODE = 8,
    GFXPRINT_FLAG64 = 0x40,
    GFXPRINT_OPEN = 0x80
} GfxPrintFlag;

typedef struct {
    /* 0x00 */ void* loadedRamAddr;
    /* 0x04 */ u32 vromStart;
    /* 0x08 */ u32 vromEnd;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ UNK_TYPE4 unk14;
    /* 0x18 */ func_ptr init;
    /* 0x1C */ func_ptr destroy;
    /* 0x20 */ UNK_TYPE4 unk20;
    /* 0x24 */ UNK_TYPE4 unk24;
    /* 0x28 */ UNK_TYPE4 unk28;
    /* 0x2C */ u32 instanceSize;
} GameStateOverlay; // size = 0x30

typedef struct {
    /* 0x00 */ u16 countdown;
    /* 0x04 */ Vec3f originPos;
    /* 0x10 */ Vec3f relativePos;
} SoundSource; // size = 0x1C

typedef struct {
    /* 0x00 */ OSContPad cur;
    /* 0x06 */ OSContPad prev;
    /* 0x0C */ OSContPad press; // X/Y store delta from last frame
    /* 0x12 */ OSContPad rel; // X/Y store adjusted
} Input; // size = 0x18

typedef struct {
    /* 0x000 */ u32 magic;
    /* 0x004 */ GraphicsContext* gfxCtx;
    /* 0x008 */ Viewport viewport;
    /* 0x018 */ f32 fovy;
    /* 0x01C */ f32 zNear;
    /* 0x020 */ f32 zFar;
    /* 0x024 */ f32 scale;
    /* 0x028 */ Vec3f eye;
    /* 0x034 */ Vec3f at;
    /* 0x040 */ Vec3f up;
    /* 0x04C */ UNK_TYPE1 pad4C[0x4];
    /* 0x050 */ Vp vp;
    /* 0x060 */ Mtx projection;
    /* 0x0A0 */ Mtx viewing;
    /* 0x0E0 */ Mtx unkE0;
    /* 0x120 */ Mtx* projectionPtr;
    /* 0x124 */ Mtx* viewingPtr;
    /* 0x128 */ Vec3f quakeRot;
    /* 0x134 */ Vec3f quakeScale;
    /* 0x140 */ f32 quakeSpeed;
    /* 0x144 */ Vec3f currQuakeRot;
    /* 0x150 */ Vec3f currQuakeScale;
    /* 0x15C */ u16 normal;
    /* 0x15E */ UNK_TYPE1 pad15E[0x2];
    /* 0x160 */ u32 flags; // bit 3: Render to an orthographic perspective
    /* 0x164 */ UNK_TYPE4 unk164;
} View; // size = 0x168

typedef void(*fault_update_input_func)(Input* input);

typedef struct {
    /* 0x00 */ u8 noteIdx;
    /* 0x01 */ u8 state;
    /* 0x02 */ u8 pos;
} OcarinaStaff; // size = 0x3;

typedef struct {
    /* 0x000 */ View view;
    /* 0x168 */ u8* iconItemSegment;
    /* 0x16C */ u8* iconItem24Segment;
    /* 0x170 */ u8* unk_170;
    /* 0x174 */ u8* unk_174;
    /* 0x178 */ u8* unk_178;
    /* 0x17C */ u8* unk_17C;
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
    /* 0x1B0 */ DmaRequest unk_1B0;
    /* 0x1D0 */ OSMesgQueue loadQueue;
    /* 0x1E8 */ OSMesg loadMsg;
    /* 0x1EC */ u16 state;
    /* 0x1EE */ u16 debugState;
    /* 0x1F0 */ u8 unk_1F0;
    /* 0x1F4 */ Vec3f eye;
    /* 0x200 */ u16 unk_200;
    /* 0x202 */ u16 mode;
    /* 0x204 */ u16 pageIndex;
    /* 0x206 */ u16 unk_206;
    /* 0x208 */ u16 unk_208;
    /* 0x20C */ f32 unk_20C;
    /* 0x210 */ f32 unk_210;
    /* 0x214 */ f32 unk_214;
    /* 0x218 */ f32 unk_218;
    /* 0x21C */ f32 unk_21C;
    /* 0x220 */ f32 unk_220;
    /* 0x224 */ u16 alpha;
    /* 0x226 */ s16 offsetY;
    /* 0x228 */ s32 unk_228;
    /* 0x22C */ s32 unk_22C;
    /* 0x230 */ s32 unk_230;
    /* 0x234 */ s32 unk_234;
    /* 0x238 */ s16 unk_238[5];
    /* 0x242 */ s16 unk_242[5];
    /* 0x24C */ s16 unk_24C[5];
    /* 0x256 */ s16 unk_256;
    /* 0x258 */ s16 unk_258;
    /* 0x25A */ s16 unk_25A;
    /* 0x25C */ u16 unk_25C;
    /* 0x25E */ u16 unk_25E[5];
    /* 0x268 */ u16 unk_268[5];
    /* 0x272 */ u16 equipTargetItem;
    /* 0x274 */ u16 equipTargetSlot;
    /* 0x276 */ u16 equipTargetCBtn;
    /* 0x278 */ s16 equipAnimX;
    /* 0x27A */ s16 equipAnimY;
    /* 0x27C */ s16 equipAnimAlpha;
    /* 0x27E */ s16 unk_27E;
    /* 0x280 */ u16 unk_280;
    /* 0x282 */ u16 unk_282;
    /* 0x284 */ s16 unk_284;
    /* 0x286 */ s16 unk_286;
    /* 0x288 */ f32 unk_288;
    /* 0x28C */ f32 unk_28C;
    /* 0x290 */ f32 unk_290;
    /* 0x294 */ f32 unk_294;
    /* 0x298 */ f32 unk_298;
    /* 0x29C */ s16 unk_29C;
    /* 0x29E */ s16 unk_29E;
    /* 0x2A0 */ s16 unk_2A0;
    /* 0x2A2 */ u8 worldMapPoints[20];
    /* 0x2B6 */ u8 unk_2B6;
    /* 0x2B7 */ u8 unk_2B7;
    /* 0x2B8 */ u8 unk_2B8;
    /* 0x2B9 */ u8 unk_2B9;
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2BE */ s16 unk_2BE[5];
    /* 0x2C8 */ u16 unk_2C8;
    /* 0x2CA */ s16 unk_2CA;
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
    /* 0x21E */ s16 unk_21E;
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
    /* 0x258 */ s16 unk_258;
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
    /* 0x27A */ s16 unk_27A;
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
    /* 0x31A */ u8 unk_31A;
    /* 0x31B */ u8 unk_31B;
    /* 0x31C */ u8 unk_31C;
    /* 0x320 */ OSMesgQueue unk_320;
    /* 0x338 */ OSMesg unk_338;
    /* 0x33C */ void* unk_33C;
    /* 0x340 */ u32 unk_340;
    /* 0x344 */ u32 unk_344;
} InterfaceContext; // size = 0x348

typedef struct {
    /* 0x00 */ u16 unk_0;
    /* 0x02 */ u16 unk_2;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ f32 unk_C;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16;
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
    /* 0x28 */ LightInfo unk_28; // sun 1
    /* 0x36 */ LightInfo unk_36; // sun 2
    /* 0x44 */ s8 unk_44;
    /* 0x48 */ DmaRequest unk_48;
    /* 0x68 */ OSMesgQueue unk_68;
    /* 0x80 */ OSMesg unk_80;
    /* 0x84 */ f32 unk_84;
    /* 0x88 */ f32 unk_88;
    /* 0x8C */ LightSettings2 unk_8C;
    /* 0xA8 */ f32 unk_A8;
    /* 0xAC */ Vec3s windDir;
    /* 0xB4 */ f32 windSpeed;
    /* 0xB8 */ u8 numLightSettings;
    /* 0xBC */ LightSettings* lightSettingsList;
    /* 0xC0 */ u8 unk_C0;
    /* 0xC1 */ u8 unk_C1;
    /* 0xC2 */ u8 unk_C2;
    /* 0xC3 */ u8 unk_C3;
    /* 0xC4 */ LightSettings unk_C4;
    /* 0xDA */ u16 unk_DA;
    /* 0xDC */ f32 unk_DC;
    /* 0xE0 */ u8 unk_E0;
    /* 0xE1 */ u8 unk_E1;
    /* 0xE2 */ s8 unk_E2;
    /* 0xE3 */ u8 unk_E3; // modified by unused func in EnWeatherTag
    /* 0xE4 */ u8 unk_E4;
    /* 0xE5 */ u8 unk_E5;
    /* 0xE6 */ u8 unk_E6[4];
    /* 0xEA */ u8 unk_EA;
    /* 0xEB */ u8 unk_EB;
    /* 0xEC */ u8 unk_EC;
    /* 0xED */ u8 unk_ED;
    /* 0xEE */ u8 unk_EE[4];
    /* 0xF2 */ u8 unk_F2[8];
    /* 0xFA */ u8 unk_FA[4];
} EnvironmentContext; // size = 0x100

typedef struct {
    /* 0x00000 */ View view;
    /* 0x00168 */ void* skyboxStaticSegment[2];
    /* 0x00170 */ char unk170[8]; // more static segments?
    /* 0x00178 */ void* skyboxPaletteStaticSegment;
    /* 0x0017C */ Gfx* unk17C;
    /* 0x00180 */ Gfx* unk180;
    /* 0x00184 */ Vtx* roomVtx;
    /* 0x00188 */ DmaRequest unk188;
    /* 0x001A8 */ DmaRequest unk1A8;
    /* 0x001C8 */ DmaRequest unk1C8;
    /* 0x001E8 */ OSMesgQueue loadQueue;
    /* 0x00200 */ OSMesg loadMsg;
    /* 0x00204 */ s16 skyboxShouldDraw;
    /* 0x00208 */ f32 rotX;
    /* 0x0020C */ f32 rotY;
    /* 0x00210 */ f32 rotZ;
    /* 0x00214 */ Vec3f eye;
    /* 0x00220 */ s16 angle;
    /* 0x00222 */ u8 primR;
    /* 0x00223 */ u8 primG;
    /* 0x00224 */ u8 primB;
    /* 0x00225 */ u8 envR;
    /* 0x00226 */ u8 envG;
    /* 0x00227 */ u8 envB;
} SkyboxContext; // size = 0x228

typedef struct ListAlloc {
    /* 0x00 */ struct ListAlloc* prev;
    /* 0x04 */ struct ListAlloc* next;
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

typedef struct {
    /* 0x00000 */ View view;
    /* 0x00168 */ Font font;
    /* 0x11EF4 */ char unk_11EF4[0x10];
    /* 0x11F04 */ u16 unk11F04;
    /* 0x11F06 */ UNK_TYPE1 pad11F06[0x4];
    /* 0x11F0A */ u8 unk11F0A;
    /* 0x11F0B */ UNK_TYPE1 pad11F0B[0x5];
    /* 0x11F10 */ s32 unk11F10;
    /* 0x11F14 */ UNK_TYPE1 pad11F14[0xE];
    /* 0x11F22 */ u8 unk11F22;
    /* 0x11F23 */ UNK_TYPE1 pad11F23[0xFD];
    /* 0x12020 */ u8 unk12020;
    /* 0x12021 */ u8 choiceIndex;
    /* 0x12022 */ UNK_TYPE1 unk12022;
    /* 0x12023 */ s8 unk12023;
    /* 0x12024 */ UNK_TYPE1 unk12024[0x6];
    /* 0x1202A */ u16 unk1202A;
    /* 0x1202C */ UNK_TYPE1 pad1202C[0x2];
    /* 0x1202E */ u16 unk1202E;
    /* 0x12030 */ UNK_TYPE1 pad12030[0x14];
    /* 0x12044 */ s16 unk12044;
    /* 0x12046 */ UNK_TYPE1 pad12046[0x24];
    /* 0x1206A */ s16 unk1206A;
    /* 0x1206C */ s32 unk1206C;
    /* 0x12070 */ UNK_TYPE1 pad12070[0x8];
    /* 0x12078 */ s32 bankRupeesSelected;
    /* 0x1207C */ s32 bankRupees; 
    /* 0x12080 */ UNK_TYPE1 pad12080[0x31];
    /* 0x120B1 */ u8 unk120B1;
    /* 0x120B2 */ UNK_TYPE1 pad120B2[0x22];
    /* 0x120D4 */ UNK_TYPE2 unk120D4;
    /* 0x120D6 */ UNK_TYPE2 unk120D6;
    /* 0x120D8 */ UNK_TYPE1 pad120D8[0x8];
} MessageContext; // size = 0x120E0

typedef struct ActorBgMbarChair ActorBgMbarChair;

typedef struct ActorEnBji01 ActorEnBji01;

typedef struct ActorEnTest ActorEnTest;

typedef struct ActorListEntry ActorListEntry;

typedef struct ArenaNode_t {
    /* 0x0 */ s16 magic; // Should always be 0x7373
    /* 0x2 */ s16 isFree;
    /* 0x4 */ u32 size;
    /* 0x8 */ struct ArenaNode_t* next;
    /* 0xC */ struct ArenaNode_t* prev;
} ArenaNode; // size = 0x10

typedef struct {
    /* 0x00 */ ArenaNode* head;
    /* 0x04 */ void* start;
    /* 0x08 */ OSMesgQueue lock;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 isInit;
    /* 0x22 */ u8 flag;
} Arena; // size = 0x24

typedef struct ActorEnBom ActorEnBom;

typedef struct ActorEnFirefly ActorEnFirefly;

typedef struct ActorObjBell ActorObjBell;

typedef struct ActorBgIknvObj ActorBgIknvObj;

typedef struct FaultAddrConvClient FaultAddrConvClient;

struct FaultAddrConvClient {
    /* 0x0 */ FaultAddrConvClient* next;
    /* 0x4 */ fault_address_converter_func callback;
    /* 0x8 */ void* param;
}; // size = 0xC

typedef struct FaultClient FaultClient;

struct FaultClient {
    /* 0x0 */ FaultClient* next;
    /* 0x4 */ fault_client_func callback;
    /* 0x8 */ void* param0;
    /* 0xC */ void* param1;
}; // size = 0x10

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

typedef struct GameAlloc GameAlloc;

typedef struct GameState GameState;

typedef struct PreNMIContext PreNMIContext;

typedef struct GameAllocNode GameAllocNode;

struct GameAllocNode {
    /* 0x0 */ GameAllocNode* next;
    /* 0x4 */ GameAllocNode* prev;
    /* 0x8 */ u32 size;
    /* 0xC */ UNK_TYPE1 padC[0x4];
}; // size = 0x10

struct GameAlloc {
    /* 0x00 */ GameAllocNode base;
    /* 0x10 */ GameAllocNode* head;
}; // size = 0x14

typedef void (*GameStateFunc)(struct GameState* gameState);

struct GameState {
    /* 0x00 */ GraphicsContext* gfxCtx;
    /* 0x04 */ GameStateFunc main;
    /* 0x08 */ GameStateFunc destroy;
    /* 0x0C */ GameStateFunc nextGameStateInit;
    /* 0x10 */ u32 nextGameStateSize;
    /* 0x14 */ Input input[4];
    /* 0x74 */ TwoHeadArena heap;
    /* 0x84 */ GameAlloc alloc;
    /* 0x98 */ UNK_TYPE1 pad98[0x3];
    /* 0x9B */ u8 running; // If 0, switch to next game state
    /* 0x9C */ u32 frames;
    /* 0xA0 */ UNK_TYPE1 padA0[0x2];
    /* 0xA2 */ u8 framerateDivisor; // game speed?
    /* 0xA3 */ UNK_TYPE1 unkA3;
}; // size = 0xA4

struct PreNMIContext {
    /* 0x00 */ GameState state;
    /* 0xA4 */ u32 timer;
    /* 0xA8 */ UNK_TYPE4 unkA8;
}; // size = 0xAC

typedef struct GlobalContext GlobalContext;

typedef s32 (*ColChkResetFunc)(GlobalContext*, Collider*);
typedef void (*ColChkBloodFunc)(GlobalContext*, Collider*, Vec3f*);
typedef void (*ColChkApplyFunc)(GlobalContext*, CollisionCheckContext*, Collider*);
typedef void (*ColChkVsFunc)(GlobalContext*, CollisionCheckContext*, Collider*, Collider*);
typedef s32 (*ColChkLineFunc)(GlobalContext*, CollisionCheckContext*, Collider*, Vec3f*, Vec3f*);

typedef void(*cutscene_update_func)(GlobalContext* globalCtx, CutsceneContext* cCtxt);

typedef void(*draw_func)(GlobalContext* globalCtx, s16 index);

typedef void(*room_draw_func)(GlobalContext* globalCtx, Room* room, u32 flags);

typedef struct {
    /* 0x00 */ draw_func unk0;
    /* 0x04 */ u32 unk4;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ u32 unk18;
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ u32 unk20;
} s801BB170; // size = 0x24

typedef struct Camera {
    /* 0x000 */ char paramData[0x50];
    /* 0x050 */ Vec3f at;
    /* 0x05C */ Vec3f eye;
    /* 0x068 */ Vec3f up;
    /* 0x074 */ Vec3f eyeNext;
    /* 0x080 */ Vec3f skyboxOffset;
    /* 0x08C */ struct GlobalContext* globalCtx;
    /* 0x090 */ struct Player* player;
    /* 0x094 */ PosRot playerPosRot;
    /* 0x0A8 */ struct Actor* target;
    /* 0x0AC */ PosRot targetPosRot;
    /* 0x0C0 */ f32 rUpdateRateInv;
    /* 0x0C4 */ f32 pitchUpdateRateInv;
    /* 0x0C8 */ f32 yawUpdateRateInv;
    /* 0x0CC */ f32 yOffsetUpdateRate;
    /* 0x0D0 */ f32 xzOffsetUpdateRate;
    /* 0x0D4 */ f32 fovUpdateRate;
    /* 0x0D8 */ f32 xzSpeed;
    /* 0x0DC */ f32 dist;
    /* 0x0E0 */ f32 speedRatio;
    /* 0x0E4 */ Vec3f posOffset;
    /* 0x0F0 */ Vec3f playerPosDelta;
    /* 0x0FC */ f32 fov;
    /* 0x100 */ f32 atLERPStepScale;
    /* 0x104 */ f32 playerGroundY;
    /* 0x108 */ Vec3f floorNorm;
    /* 0x114 */ f32 waterYPos;
    /* 0x118 */ s32 waterPrevCamIdx;
    /* 0x11C */ s32 waterPrevCamSetting;
    /* 0x120 */ s16 waterQuakeId;
    /* 0x122 */ s16 unk122;
    /* 0x124 */ void* data0;
    /* 0x128 */ void* data1;
    /* 0x12C */ s16 data2;
    /* 0x12E */ s16 data3;
    /* 0x130 */ s16 uid;
    /* 0x132 */ UNK_TYPE1 pad132[2];
    /* 0x134 */ Vec3s inputDir;
    /* 0x13A */ Vec3s camDir;
    /* 0x140 */ s16 status;
    /* 0x142 */ s16 setting;
    /* 0x144 */ s16 mode;
    /* 0x146 */ s16 bgCheckId;
    /* 0x148 */ s16 camDataIdx;
    /* 0x14A */ s16 flags1;
    /* 0x14C */ s16 flags2;
    /* 0x14E */ s16 childCamIdx;
    /* 0x150 */ s16 unk150;
    /* 0x152 */ s16 unk152;
    /* 0x154 */ s16 prevSetting;
    /* 0x156 */ s16 nextCamDataIdx;
    /* 0x158 */ s16 nextBGCheckId;
    /* 0x15A */ s16 roll;
    /* 0x15C */ s16 paramFlags;
    /* 0x15E */ s16 animState;
    /* 0x160 */ s16 unk160;
    /* 0x162 */ s16 timer;
    /* 0x164 */ s16 thisIdx;
    /* 0x166 */ s16 prevCamDataIdx;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ s16 unk16A;
    /* 0x16C */ Vec3f meshActorPos;
} Camera; // size = 0x178

typedef s32(*camera_update_func)(Camera* camera);

typedef struct {
    /* 0x00 */ Vec3f atOffset;
    /* 0x0C */ Vec3f eyeOffset;
    /* 0x18 */ s16 rollOffset;
    /* 0x1A */ s16 zoom;
} ShakeInfo; // size = 0x1C

typedef struct {
    /* 0x00 */ s16 randIdx;
    /* 0x02 */ s16 countdownMax;
    /* 0x04 */ Camera* camera;
    /* 0x08 */ u32 callbackIdx;
    /* 0x0C */ s16 verticalMag;
    /* 0x0E */ s16 horizontalMag;
    /* 0x10 */ s16 zoom;
    /* 0x12 */ s16 rollOffset;
    /* 0x14 */ Vec3s shakePlaneOffset; // angle deviations from shaking in the perpendicular plane
    /* 0x1A */ s16 speed;
    /* 0x1C */ s16 isShakePerpendicular;
    /* 0x1E */ s16 countdown;
    /* 0x20 */ s16 cameraPtrsIdx;
} QuakeRequest; // size = 0x24

typedef struct {
    /* 0x00 */ Vec3f atOffset;
    /* 0x0C */ Vec3f eyeOffset;
    /* 0x18 */ s16 rollOffset;
    /* 0x1A */ s16 zoom;
    /* 0x1C */ f32 max; // Set to scaled max data of struct (mag for Vec3f), never used
} QuakeCamCalc; // size = 0x20

typedef s16 (*QuakeCallbackFunc)(QuakeRequest*, ShakeInfo*);

#define QUAKE_SPEED (1 << 0)
#define QUAKE_VERTICAL_MAG (1 << 1)
#define QUAKE_HORIZONTAL_MAG (1 << 2)
#define QUAKE_ZOOM (1 << 3)
#define QUAKE_ROLL_OFFSET (1 << 4)
#define QUAKE_SHAKE_PLANE_OFFSET_X (1 << 5)
#define QUAKE_SHAKE_PLANE_OFFSET_Y (1 << 6)
#define QUAKE_SHAKE_PLANE_OFFSET_Z (1 << 7)
#define QUAKE_COUNTDOWN (1 << 8)
#define QUAKE_IS_SHAKE_PERPENDICULAR (1 << 9)

typedef struct {
    /* 0x0 */ GlobalContext* globalCtx;
    /* 0x4 */ s32 type; // bitfield, highest set bit determines type
    /* 0x8 */ s16 countdown;
    /* 0xA */ s16 state;
} Quake2Context; // size = 0xC

typedef enum {
    QUAKE2_INACTIVE,
    QUAKE2_ACTIVE,
    QUAKE2_SETUP,
} Quake2State;

typedef struct IrqMgrClient_t {
    /* 0x0 */ struct IrqMgrClient_t* next;
    /* 0x4 */ OSMesgQueue* queue;
} IrqMgrClient; // size = 0x8

typedef struct {
    /* 0x0 */ s16 type;
    /* 0x2 */ u8 misc[30];
} OSScMsg;

typedef struct {
    /* 0x000 */ OSScMsg verticalRetraceMesg;
    /* 0x020 */ OSScMsg prenmiMsg;
    /* 0x040 */ OSScMsg nmiMsg;
    /* 0x060 */ OSMesgQueue irqQueue;
    /* 0x078 */ OSMesg irqBuffer[8];
    /* 0x098 */ OSThread thread;
    /* 0x248 */ IrqMgrClient* callbacks;
    /* 0x24C */ u8 prenmiStage;
    /* 0x250 */ OSTime lastPrenmiTime;
    /* 0x258 */ OSTimer prenmiTimer;
    /* 0x278 */ OSTime lastFrameTime;
} IrqMgr; // size = 0x280

typedef struct {
    /* 0x000 */ u8 controllers; // bit 0 is set if controller 1 is plugged in, etc.
    /* 0x001 */ UNK_TYPE1 pad1[0x13];
    /* 0x014 */ OSContStatus statuses[4];
    /* 0x024 */ UNK_TYPE4 unk24;
    /* 0x028 */ OSMesg lockMesg[1];
    /* 0x02C */ OSMesg interrupts[8];
    /* 0x04C */ OSMesgQueue siEventCallbackQueue;
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

#define OS_SC_NEEDS_RDP         0x0001
#define OS_SC_NEEDS_RSP         0x0002
#define OS_SC_DRAM_DLIST        0x0004
#define OS_SC_PARALLEL_TASK     0x0010
#define OS_SC_LAST_TASK         0x0020
#define OS_SC_SWAPBUFFER        0x0040

#define OS_SC_RCP_MASK          0x0003
#define OS_SC_TYPE_MASK         0x0007

#define OS_SC_DP                0x0001
#define OS_SC_SP                0x0002
#define OS_SC_YIELD             0x0010
#define OS_SC_YIELDED           0x0020

typedef struct OSScTask {
    /* 0x00 */ struct OSScTask* next;
    /* 0x04 */ u32      state;
    /* 0x08 */ u32      flags;
    /* 0x0C */ CfbInfo* framebuffer;
    /* 0x10 */ OSTask   list;
    /* 0x50 */ OSMesgQueue* msgQ;
    /* 0x54 */ OSMesg   msg;
} OSScTask; // size = 0x58

typedef struct {
    /* 0x0000 */ OSMesgQueue interruptQ;
    /* 0x0018 */ OSMesg      intBuf[64];
    /* 0x0118 */ OSMesgQueue cmdQ;
    /* 0x0130 */ OSMesg      cmdMsgBuf[8];
    /* 0x0150 */ OSThread    thread;
    /* 0x0300 */ OSScTask*   audioListHead;
    /* 0x0304 */ OSScTask*   gfxListHead;
    /* 0x0308 */ OSScTask*   audioListTail;
    /* 0x030C */ OSScTask*   gfxListTail;
    /* 0x0310 */ OSScTask*   curRSPTask;
    /* 0x0314 */ OSScTask*   curRDPTask;
    /* 0x0318 */ s32         retraceCount;
    /* 0x0318 */ s32         doAudio;
    /* 0x0320 */ CfbInfo*    curBuf;
    /* 0x0324 */ CfbInfo*    pendingSwapBuf1;
    /* 0x0328 */ CfbInfo*    pendingSwapBuf2;
    /* 0x032C */ char unk_32C[0x3];
    /* 0x032F */ u8 shouldUpdateVi;
    /* 0x0330 */ IrqMgrClient irqClient;
} SchedContext; // size = 0x338

typedef struct StackEntry_t {
    /* 0x00 */ struct StackEntry_t* next;
    /* 0x04 */ struct StackEntry_t* prev;
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

typedef struct TargetContext TargetContext;

typedef struct ActorContext ActorContext;

typedef struct s800B948C s800B948C;

struct FireObjLight {
    /* 0x00 */ LightNode* light;
    /* 0x04 */ LightInfoPositional lightInfo;
    /* 0x12 */ u8 unk12;
}; // size = 0x13

struct ActorListEntry {
    /* 0x0 */ s32 length; // number of actors loaded of this type
    /* 0x4 */ Actor* first; // pointer to first actor of this type
    /* 0x8 */ UNK_TYPE1 pad8[0x4];
}; // size = 0xC

#define OS_SC_RETRACE_MSG       1
#define OS_SC_DONE_MSG          2
#define OS_SC_NMI_MSG           3 // name is made up, 3 is OS_SC_RDP_DONE_MSG in the original sched.c
#define OS_SC_PRE_NMI_MSG       4

typedef struct {
    /* 0x0000 */ OSTask task;
    /* 0x0040 */ OSMesgQueue* taskQueue;
    /* 0x0044 */ char unk_44[0xC];
} AudioTask; // size = 0x50

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
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 flags; // bit 0 - ?, bit 1 - ?
    /* 0x29 */ UNK_TYPE1 pad29[0x1];
    /* 0x2A */ s16 ignitionDelay;
    /* 0x2C */ ColliderCylinder collision;
    /* 0x78 */ FireObjLight light;
}; // size = 0x8B

struct TargetContext {
    /* 0x00 */ Vec3f unk0;
    /* 0x0C */ Vec3f unkC;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ Actor* unk38;
    /* 0x3C */ Actor* unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ s8 unk4C;
    /* 0x4D */ UNK_TYPE1 pad4D[0x3];
    /* 0x50 */ TargetContextEntry unk50[3];
    /* 0x8C */ Actor* unk8C;
    /* 0x90 */ Actor* unk90;
    /* 0x94 */ UNK_TYPE1 pad94[0x4];
}; // size = 0x98

struct s800B948C {
    /* 0x00 */ GlobalContext* globalCtx;
    /* 0x04 */ Actor* actor;
    /* 0x08 */ u32 updateActorIfSet;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ Actor* unk10;
    /* 0x14 */ Player* player;
    /* 0x18 */ u32 runMainIfSet; // Bitmask of actor flags. The actor will only have main called if it has at least 1 flag set that matches this bitmask
}; // size = 0x1C

struct ActorContext {
    /* 0x000 */ UNK_TYPE1 pad0[0x2];
    /* 0x002 */ u8 unk2;
    /* 0x003 */ u8 unk3;
    /* 0x004 */ s8 unk4;
    /* 0x005 */ u8 unk5;
    /* 0x006 */ UNK_TYPE1 pad6[0x5];
    /* 0x00B */ s8 unkB;
    /* 0x00C */ s16 unkC;
    /* 0x00E */ u8 totalLoadedActors;
    /* 0x00F */ u8 undrawnActorCount;
    /* 0x010 */ ActorListEntry actorList[12];
    /* 0x0A0 */ Actor* undrawnActors[32]; // Records the first 32 actors drawn each frame
    /* 0x120 */ TargetContext targetContext;
    /* 0x1B8 */ u32 switchFlags[4]; // First 0x40 are permanent, second 0x40 are temporary
    /* 0x1C8 */ u32 chestFlags;
    /* 0x1CC */ u32 clearedRooms;
    /* 0x1D0 */ u32 clearedRoomsTemp;
    /* 0x1D4 */ u32 collectibleFlags[4]; // bitfield of 128 bits
    /* 0x1E4 */ TitleCardContext titleCtxt;
    /* 0x1F4 */ u8 unk1F4;
    /* 0x1F5 */ u8 unk1F5;
    /* 0x1F6 */ UNK_TYPE1 pad1F6[0x2];
    /* 0x1F8 */ f32 unk1F8;
    /* 0x1FC */ Vec3f unk1FC;
    /* 0x208 */ UNK_TYPE1 pad208[0x48];
    /* 0x250 */ void* unk250; // allocation of 0x20f0 bytes?
    /* 0x254 */ u32 unk254[5];
    /* 0x268 */ u8 unk268;
    /* 0x269 */ UNK_TYPE1 pad269[0x3];
    /* 0x26C */ UNK_TYPE1 pad26C[0xC];
    /* 0x278 */ u16 unk278;
    /* 0x27A */ UNK_TYPE1 pad27A[0x2];
    /* 0x27C */ UNK_TYPE1 pad27C[0x8];
}; // size = 0x284

typedef struct {
    /* 0x00 */ u8   seqIndex;
    /* 0x01 */ u8   nightSeqIndex;
    /* 0x02 */ u8   unk_02;
} SoundContext; // size = 0x3

typedef struct {
    /* 0x00 */ s32 enabled;
    /* 0x04 */ s32 timer;
} FrameAdvanceContext; // size = 0x8

typedef struct {
    /* 0x00 */ u16 state;
} GameOverContext; // size = 0x02

struct GlobalContext {
    /* 0x00000 */ GameState state;
    /* 0x000A4 */ s16 sceneNum;
    /* 0x000A6 */ u8 sceneConfig;
    /* 0x000A7 */ char unk_A7[0x9];
    /* 0x000B0 */ void* sceneSegment;
    /* 0x000B4 */ char unk_B4[0x4];
    /* 0x000B8 */ View view;
    /* 0x00220 */ Camera mainCamera;
    /* 0x00398 */ Camera subCameras[3];
    /* 0x00800 */ Camera* cameraPtrs[4];
    /* 0x00810 */ s16 activeCamera;
    /* 0x00812 */ s16 nextCamera;
    /* 0x00814 */ SoundContext soundCtx;
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
    /* 0x18768 */ void (*playerInit)(Player* player, struct GlobalContext* globalCtx, FlexSkeletonHeader* skelHeader);
    /* 0x1876C */ void (*playerUpdate)(Player* player, struct GlobalContext* globalCtx, Input* input);
    /* 0x18770 */ void* unk_18770; //! TODO: Determine function prototype
    /* 0x18774 */ s32 (*startPlayerFishing)(struct GlobalContext* globalCtx);
    /* 0x18778 */ s32 (*grabPlayer)(struct GlobalContext* globalCtx, Player* player);
    /* 0x1877C */ s32 (*startPlayerCutscene)(struct GlobalContext* globalCtx, Player* player, s32 mode);
    /* 0x18780 */ void (*func_18780)(Player* player, struct GlobalContext* globalCtx);
    /* 0x18784 */ s32 (*damagePlayer)(struct GlobalContext* globalCtx, s32 damage);
    /* 0x18788 */ void (*talkWithPlayer)(struct GlobalContext* globalCtx, Actor* actor);
    /* 0x1878C */ void (*unk_1878C)(struct GlobalContext* globalCtx);
    /* 0x18790 */ void* unk_18790; //! TODO: Determine function prototype
    /* 0x18794 */ void* unk_18794; //! TODO: Determine function prototype
    /* 0x18798 */ s32 (*setPlayerTalkAnim)(struct GlobalContext* globalCtx, void* talkAnim, s32 arg2);
    /* 0x1879C */ s16 unk_1879C[10];
    /* 0x187B0 */ MtxF projectionMatrix;
    /* 0x187F0 */ Vec3f unk_187F0;
    /* 0x187FC */ MtxF mf_187FC;
    /* 0x1883C */ Mtx* unk_1883C;
    /* 0x18840 */ u32 gameplayFrames;
    /* 0x18844 */ u8 unk_18844;
    /* 0x18845 */ u8 unk_18845;
    /* 0x18846 */ s16 numSetupActors;
    /* 0x18848 */ u8 numRooms;
    /* 0x1884C */ RomFile* roomList;
    /* 0x18850 */ ActorEntry* linkActorEntry;
    /* 0x18854 */ ActorEntry* setupActorList;
    /* 0x18858 */ void* unk_18858;
    /* 0x1885C */ EntranceEntry* setupEntranceList;
    /* 0x18860 */ u16* setupExitList;
    /* 0x18864 */ Path* setupPathList;
    /* 0x18868 */ void* unk_18868;
    /* 0x1886C */ AnimatedMaterial* sceneMaterialAnims;
    /* 0x18870 */ void* specialEffects;
    /* 0x18874 */ u8 skyboxId;
    /* 0x18875 */ s8 sceneLoadFlag; // "fade_direction"
    /* 0x18876 */ s16 unk_18876;
    /* 0x18878 */ s16 bgCoverAlpha;
    /* 0x1887A */ u16 nextEntranceIndex;
    /* 0x1887C */ s8 unk_1887C;
    /* 0x1887D */ s8 unk_1887D;
    /* 0x1887E */ s8 unk_1887E;
    /* 0x1887F */ u8 unk_1887F;
    /* 0x18880 */ u8 unk_18880;
    /* 0x18884 */ CollisionCheckContext colChkCtx;
    /* 0x18B20 */ u16 envFlags[20];
    /* 0x18B48 */ u8 curSpawn;
    /* 0x18B49 */ u8 unk_18B49;
    /* 0x18B4A */ u8 unk_18B4A;
    /* 0x18B4C */ PreRender pauseBgPreRender;
    /* 0x18B9C */ char unk_18B9C[0x2B8];
    /* 0x18E54 */ SceneTableEntry* loadedScene;
    /* 0x18E58 */ char unk_18E58[0x400];
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
    /* 0x0 */ u8 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} struct_80133038_arg2; // size = 0xC

typedef struct {
    /* 0x000 */ Actor base;
    /* 0x144 */ ColliderQuad unk144;
    /* 0x1C4 */ ColliderQuad unk1C4;
    /* 0x244 */ Vec3f unk244;
    /* 0x250 */ f32 unk250;
    /* 0x254 */ f32 unk254;
    /* 0x258 */ ActorFunc update;
    /* 0x25C */ s16 unk25C;
    /* 0x25E */ u16 unk25E;
    /* 0x260 */ u8 unk260;
    /* 0x261 */ UNK_TYPE1 pad261[0x3];
} ActorArrowFire; // size = 0x264

struct ActorBgMbarChair {
    /* 0x000 */ Actor base;
    /* 0x144 */ UNK_TYPE1 pad144[0x18];
}; // size = 0x15C

struct ActorEnBji01 {
    /* 0x000 */ Actor base;
    /* 0x144 */ UNK_TYPE1 pad144[0x170];
}; // size = 0x2B4

struct ActorEnBom {
    /* 0x000 */ Actor base;
    /* 0x144 */ ColliderCylinder unk144;
    /* 0x190 */ ColliderJntSph unk190;
    /* 0x1B0 */ ColliderJntSphElement unk1B0[1];
    /* 0x1F0 */ s16 unk1F0;
    /* 0x1F2 */ UNK_TYPE1 pad1F2[0x6];
    /* 0x1F8 */ u8 unk1F8;
    /* 0x1F9 */ u8 unk1F9;
    /* 0x1FA */ UNK_TYPE1 pad1FA[0x2];
    /* 0x1FC */ u8 unk1FC;
    /* 0x1FD */ UNK_TYPE1 pad1FD[0x3];
    /* 0x200 */ func_ptr unk200;
}; // size = 0x204

struct ActorEnFirefly {
    /* 0x000 */ Actor base;
    /* 0x144 */ UNK_TYPE1 pad144[0x1C];
    /* 0x160 */ f32 unk160;
    /* 0x164 */ UNK_TYPE1 pad164[0x24];
    /* 0x188 */ func_ptr updateFunc;
    /* 0x18C */ UNK_TYPE1 type;
    /* 0x18D */ u8 unk18D;
    /* 0x18E */ u8 unk18E;
    /* 0x18F */ u8 unk18F;
    /* 0x190 */ s16 unk190;
    /* 0x192 */ UNK_TYPE1 pad192[0x152];
    /* 0x2E4 */ f32 unk2E4;
    /* 0x2E8 */ f32 unk2E8;
    /* 0x2EC */ f32 unk2EC;
    /* 0x2F0 */ f32 unk2F0;
    /* 0x2F4 */ UNK_TYPE1 pad2F4[0x28];
    /* 0x31C */ ColliderSphere collision;
}; // size = 0x374

struct ActorEnTest {
    /* 0x000 */ Actor base;
    /* 0x144 */ UNK_TYPE1 pad144[0x10];
    /* 0x154 */ f32 unk154;
    /* 0x158 */ UNK_TYPE1 pad158[0xB0];
    /* 0x208 */ u8 unk208;
    /* 0x209 */ UNK_TYPE1 pad209[0x1];
    /* 0x20A */ u8 unk20A;
    /* 0x20B */ UNK_TYPE1 pad20B[0x1];
    /* 0x20C */ ActorEnTest20C unk20C[20];
}; // size = 0x6BC

typedef struct {
    /* 0x000 */ Actor base;
    /* 0x144 */ s8 unk144;
    /* 0x145 */ u8 unk145;
    /* 0x146 */ u16 unk146;
    /* 0x148 */ u16 unk148;
    /* 0x14A */ u16 unk14A;
    /* 0x14C */ u8 unk14C;
    /* 0x14D */ UNK_TYPE1 pad14D[0x3];
    /* 0x150 */ ActorFunc unk150;
} ActorEnTest4; // size = 0x154

struct ActorObjBell {
    /* 0x000 */ Actor base;
    /* 0x144 */ UNK_TYPE1 pad144[0x18];
    /* 0x15C */ ColliderSphere unk15C;
    /* 0x1B4 */ ColliderSphere unk1B4;
    /* 0x20C */ UNK_TYPE1 pad20C[0x2];
    /* 0x20E */ s16 unk20E;
    /* 0x210 */ UNK_TYPE1 pad210[0x4];
    /* 0x214 */ s16 unk214;
    /* 0x216 */ UNK_TYPE1 pad216[0x12];
}; // size = 0x228

struct ActorBgIknvObj {
    /* 0x000 */ DynaPolyActor bg;
    /* 0x15C */ ColliderCylinder collision;
    /* 0x1A8 */ u32 displayListAddr;
    /* 0x1AC */ ActorFunc updateFunc;
}; // size = 0x1B0

typedef struct {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ Color_RGBA8 color;
    /* 0x0C */ Color_RGBA8 envColor;
} struct_801F8010; // size = 0x10

typedef struct {
    /* 0x00 */ u32 useRgba;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ Color_RGBA8 primColor;
    /* 0x08 */ Color_RGBA8 envColor;
} struct_801F8020; // size = 0x10

typedef struct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ Color_RGBA8 primColor;
    /* 0x0C */ Color_RGBA8 envColor;
    /* 0x10 */ u16* tlut;
    /* 0x14 */ Gfx* monoDl;
} VisMono; // size = 0x18

typedef enum {
    MTXMODE_NEW,  // generates a new matrix
    MTXMODE_APPLY // applies transformation to the current matrix
} MatrixMode;

typedef struct {
    /* 0x00 */ u16 intPart[4][4];
    /* 0x20 */ u16 fracPart[4][4];
} MatrixInternal; // size = 0x40

#endif
