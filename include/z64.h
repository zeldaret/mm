#ifndef _Z64_H_
#define _Z64_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <PR/sched.h>
#include <io/controller.h>
#include <osint.h>
#include <viint.h>
#include <math.h>
#include <os.h>
#include <stdlib.h>
#include <xstdio.h>
#include <unk.h>

#include <color.h>
#include <ichain.h>

#include <z64actor.h>
#include <z64animation.h>
#include <z64collision_check.h>
#include <z64cutscene.h>
#include <z64dma.h>
#include <z64effect.h>
#include <z64item.h>
#include <z64light.h>
#include <z64math.h>
#include <z64object.h>
#include <z64scene.h>

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define SCREEN_WIDTH_HIGH_RES  576
#define SCREEN_HEIGHT_HIGH_RES 454

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
} AnimatedTexture; // size = 0x8

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
    /* 0x00 */ u8 cutsceneCount;
    /* 0x01 */ UNK_TYPE1 pad1[0x3];
    /* 0x04 */ u8* segment;
    /* 0x08 */ u8 state;
    /* 0x09 */ UNK_TYPE1 pad9[0x3];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u16 frames;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ UNK_TYPE1 pad14[0x14];
    /* 0x28 */ CsCmdActorAction* actorActions[10];
} CutsceneContext; // size = 0x50

typedef struct {
    /* 0x00 */ u32 chestFlags;
    /* 0x04 */ u32 switchFlags[2];
    /* 0x0C */ u32 clearedRooms;
    /* 0x10 */ u32 collectibleFlags;
} CycleSceneFlags; // size = 0x14

typedef struct {
    /* 0x0 */ u16 cycleLength;
    /* 0x4 */ Gfx** textureDls;
    /* 0x8 */ u8* textureDlOffsets;
} CyclingTextureParams; // size = 0xC

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

typedef struct {
    /* 0x0 */ u8 red;
    /* 0x1 */ u8 green;
    /* 0x2 */ u8 blue;
    /* 0x3 */ u8 alpha;
    /* 0x4 */ u8 lodFrac;
} FlashingTexturePrimColor; // size = 0x5

// Font textures are loaded into here
typedef struct {
    /* 0x0000 */ u8 unk0[2][120][128];
    /* 0x7800 */ u8 unk7800[93][128];
} Font; // size = 0xA680

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
    /* 0x00 */ s32 unk0;
    /* 0x04 */ UNK_TYPE1 pad4[0x40];
} GlobalContext17D98; // size = 0x44

typedef struct {
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
    /* 0x0 */ u32 vromStart;
    /* 0x4 */ u32 vromEnd;
} ObjectFileTableEntry; // size = 0x8

typedef struct {
    /* 0x00 */ u32 textSize;
    /* 0x04 */ u32 dataSize;
    /* 0x08 */ u32 rodataSize;
    /* 0x0C */ u32 bssSize;
    /* 0x10 */ u32 nRelocations;
} OverlayRelocationSection; // size = 0x14

typedef struct {
    /* 0x00 */ UNK_TYPE1 pad0[0x1C];
} PermanentSceneFlags; // size = 0x1C

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
} QuakeRequest14; // size = 0x6

typedef struct {
    /* 0x00 */ s16 intPart[16];
    /* 0x20 */ u16 fracPart[16];
} RSPMatrix; // size = 0x40

// Extra information in the save context that is not saved
typedef struct {
    /* 0x000 */ UNK_TYPE1 pad0[0xC];
    /* 0x00C */ s32 sceneSetupIndex;
    /* 0x010 */ s32 unk10;
    /* 0x014 */ UNK_TYPE1 pad14[0x2E];
    /* 0x042 */ s16 unk42;
    /* 0x044 */ UNK_TYPE1 pad44[0x34];
    /* 0x078 */ f32 previousPlayerHeight; //OvlDoorAna
    /* 0x07C */ UNK_TYPE1 pad7C[0x4];
    /* 0x080 */ s16 previousPlayerYRot; //OvlDoorAna
    /* 0x082 */ UNK_TYPE1 pad82[0x5];
    /* 0x087 */ s8 unk87;
    /* 0x088 */ UNK_TYPE1 pad88[0x1EE];
    /* 0x276 */ u8 unk276;
    /* 0x277 */ UNK_TYPE1 pad277[0x9];
    /* 0x280 */ u16 unk280;
    /* 0x282 */ u16 unk282;
    /* 0x284 */ UNK_TYPE1 pad284[0x28];
    /* 0x2AC */ u8 cutsceneTrigger;
    /* 0x2AD */ UNK_TYPE1 pad2AD[0x5];
    /* 0x2B2 */ u16 environmentTime;
    /* 0x2B4 */ UNK_TYPE1 pad2B4[0x4];
    /* 0x2B8 */ s16 unk2b8;
    /* 0x2BA */ UNK_TYPE1 pad2BA[0xA];
    /* 0x2C4 */ f32 unk2C4;
    /* 0x2C8 */ CycleSceneFlags cycleSceneFlags[120];
} SaveContextExtra; // size = 0xC28

typedef struct {
    /* 0x00 */ u8 items[24];
    /* 0x18 */ u8 masks[24];
    /* 0x30 */ u8 quantities[24];
    /* 0x48 */ UNK_TYPE1 pad48[0x40];
} SaveContextInventory; // size = 0x88

// Save Context that is only stored in an owl save
typedef struct {
    /* 0x0000 */ UNK_TYPE1 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ UNK_TYPE1 pad3[0x2];
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ UNK_TYPE1 pad6[0x2C8E];
} SaveContextOwl; // size = 0x2C94

typedef struct {
    /* 0x00 */ u8 zelda[6]; // Will always be "ZELDA3" for a valid save
    /* 0x06 */ UNK_TYPE1 pad6[0xA];
    /* 0x10 */ s16 maxLife;
    /* 0x12 */ s16 currentLife;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ s8 currentMagic;
    /* 0x16 */ s16 unk16;
    /* 0x16 */ UNK_TYPE1 pad17[0x10];
} SaveContext_struct1; // size = 0x28

typedef struct {
    /* 0x00 */ UNK_TYPE1 pad0[0x22];
} SaveContext_struct2; // size = 0x22

typedef struct {
    /* 0x0 */ s8 letterboxTarget;
    /* 0x1 */ s8 letterboxMagnitude;
    /* 0x2 */ s8 pillarboxTarget;
    /* 0x3 */ s8 pillarboxMagnitude;
} ShrinkWindowContext; // size = 0x4

typedef struct {
    /* 0x00 */ UNK_TYPE1 pad0[0x4];
    /* 0x04 */ void* savefile;
    /* 0x08 */ UNK_TYPE1 pad8[0x4];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ UNK_TYPE1 padE[0xA];
    /* 0x18 */ OSTime unk18;
} SramContext; // size = 0x20

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
    struct {
        s8 room;    // Room to switch to
        s8 effects; // How the camera reacts during the transition
    } /* 0x00 */ sides[2]; // 0 = front, 1 = back
    /* 0x04 */ s16   id;
    /* 0x06 */ Vec3s pos;
    /* 0x0C */ s16   rotY;
    /* 0x0E */ s16   params;
} TransitionActorEntry; // size = 0x10

typedef struct {
    /* 0x0 */ s32 topY;
    /* 0x4 */ s32 bottomY;
    /* 0x8 */ s32 leftX;
    /* 0xC */ s32 rightX;
} Viewport; // size = 0x10

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector; // size = 0x10

typedef void*(*fault_address_converter_func)(void* addr, void* arg);

typedef void(*fault_client_func)(void* arg1, void* arg2);

typedef unsigned long(*func)(void);

typedef void(*func_ptr)(void);

typedef void(*osCreateThread_func)(void*);

typedef void*(*printf_func)(void*, char*, size_t);

typedef struct {
    /* 0x000 */ OSThread unk0;
    /* 0x1B0 */ s8 argCount;
    /* 0x1B1 */ s8 unk1B1;
    /* 0x1B2 */ UNK_TYPE1 pad1B2[0x2];
    /* 0x1B4 */ UNK_TYPE1 func;
    /* 0x1B5 */ UNK_TYPE1 pad1B5[0x3];
    /* 0x1B8 */ s32 arg0;
    /* 0x1BC */ s32 arg1;
} s8018571C; // size = 0x1C0

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
    /* 0x00 */ f32 x[4];
    /* 0x10 */ f32 y[4];
    /* 0x20 */ f32 z[4];
    /* 0x30 */ f32 w[4];
} z_Matrix; // size = 0x40

typedef struct {
    /* 0x00 */ Vec3f scale;
    /* 0x0C */ Vec3s rotation;
    /* 0x14 */ Vec3f pos;
} ActorMeshParams; // size = 0x20

typedef struct {
    /* 0x00 */ u16 type;
    union {
        u16 vtxData[3];
        struct {
            /* 0x02 */ u16 flags_vIA; // 0xE000 is poly exclusion flags (xpFlags), 0x1FFF is vtxId
            /* 0x04 */ u16 flags_vIB; // 0xE000 is flags, 0x1FFF is vtxId
                                      // 0x2000 = poly IsConveyor surface
            /* 0x06 */ u16 vIC;
        };
    };
    /* 0x08 */ Vec3s normal; // Unit normal vector
                             // Value ranges from -0x7FFF to 0x7FFF, representing -1.0 to 1.0; 0x8000 is invalid

    /* 0x0E */ s16 dist; // Plane distance from origin along the normal
} CollisionPoly; // size = 0x10

typedef struct {
    /* 0x0 */ BgPolygonLinkedListNode* nodes;
    /* 0x4 */ u32 nextFreeNode;
    /* 0x8 */ s32 maxNodes;
} BgPolygonLinkedList; // size = 0xC

typedef struct {
    /* 0x0 */ Vec3s pos;
} BgVertex; // size = 0x6

typedef struct {
    /* 0x0 */ Vec3s minPos;
    /* 0x6 */ UNK_TYPE1 xLength; // Created by retype action
    /* 0x7 */ UNK_TYPE1 pad7[0x1];
    /* 0x8 */ UNK_TYPE1 zLength; // Created by retype action
    /* 0x9 */ UNK_TYPE1 pad9[0x3];
    /* 0xC */ u32 properties;
} BgWaterBox; // size = 0x10

typedef struct {
    /* 0x0 */ UNK_TYPE1 pad0[0x4];
    /* 0x4 */ BgWaterBox* boxes;
} BgWaterboxList; // size = 0x8

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
    /* 0x0 */ u16 cycleLength;
    /* 0x2 */ u16 numKeyFrames;
    /* 0x4 */ FlashingTexturePrimColor* primColors;
    /* 0x8 */ Color_RGBA8* envColors;
    /* 0xC */ u16* keyFrames;
} FlashingTextureParams; // size = 0x10

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
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ Vec3f unk4;
    /* 0x10 */ Vec3f unk10;
} GlobalContext1F78; // size = 0x1C

typedef struct {
    /* 0x00 */ OSContPad cur;
    /* 0x06 */ OSContPad prev;
    /* 0x0C */ OSContPad press; // X/Y store delta from last frame
    /* 0x12 */ OSContPad rel; // X/Y store adjusted
} Input; // size = 0x18

// Permanent save context, kept in regular save files
typedef struct {
    /* 0x0000 */ u32 entranceIndex; // bits 0-3 : offset; 4-8: spawn index; 9-15: scene index
    /* 0x0004 */ UNK_TYPE1 pad4[0x3];
    /* 0x0007 */ u8 linkAge;
    /* 0x0008 */ s32 cutscene;
    /* 0x000C */ u16 time;
    /* 0x000E */ UNK_TYPE1 padE[0x2];
    /* 0x0010 */ u32 isNight;
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u32 day;
    /* 0x001C */ u32 daysElapsed;
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ UNK_TYPE1 pad21[0x2];
    /* 0x0023 */ u8 owlSave;
    /* 0x0024 */ SaveContext_struct1 unk24;
    /* 0x004C */ SaveContext_struct2 unk4C;
    /* 0x006E */ UNK_TYPE1 pad6E[0x2];
    /* 0x0070 */ SaveContextInventory inv;
    /* 0x00F8 */ PermanentSceneFlags sceneFlags[120];
    /* 0x0E18 */ UNK_TYPE1 padE18[0x60];
    /* 0x0E78 */ u32 pictoFlags0;
    /* 0x0E7C */ u32 pictoFlags1;
    /* 0x0E80 */ UNK_TYPE1 padE80[0x78];
    /* 0x0EF8 */ u8 weekEventReg[100];
    /* 0x0F5C */ u32 mapsVisited;
    /* 0x0F60 */ UNK_TYPE1 padF60[0x8C];
    /* 0x0FEC */ u8 lotteryCodes[9];
    /* 0x0FF5 */ u8 spiderHouseMaskOrder[6];
    /* 0x0FFB */ u8 bomberCode[5];
    /* 0x1000 */ UNK_TYPE1 pad1000[0xA];
    /* 0x100A */ u16 checksum;
} SaveContextPerm; // size = 0x100C

typedef struct {
    /* 0x00 */ Vec3f focalPointChange;
    /* 0x0C */ Vec3f eyeChange;
    /* 0x18 */ s16 rotZ;
    /* 0x1A */ s16 zoom;
    /* 0x1C */ UNK_TYPE1 pad1C[0x2];
} ShakeInfo; // size = 0x1E

typedef struct {
    /* 0x00 */ Vec3f focalPointChange;
    /* 0x0C */ Vec3f eyeChange;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} UnkQuakeCalcStruct; // size = 0x24

typedef struct {
    /* 0x000 */ u32 magic;
    /* 0x004 */ GraphicsContext* gfxCtx;
    /* 0x008 */ Viewport viewport;
    /* 0x018 */ f32 fovy;
    /* 0x01C */ f32 zNear;
    /* 0x020 */ f32 zFar;
    /* 0x024 */ f32 scale;
    /* 0x028 */ Vec3f eye;
    /* 0x034 */ Vec3f focalPoint;
    /* 0x040 */ Vec3f upDir;
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
    /* 0x00 */ Vec3s min;
    /* 0x06 */ Vec3s max;
    /* 0x0C */ u16 numVertices;
    /* 0x10 */ BgVertex* vertices;
    /* 0x14 */ u16 numPolygons;
    /* 0x18 */ CollisionPoly* polygons;
    /* 0x1C */ BgPolygonAttributes* attributes;
    /* 0x20 */ UNK_PTR cameraData;
    /* 0x24 */ u16 numWaterBoxes;
    /* 0x28 */ BgWaterBox* waterboxes;
} BgMeshHeader; // size = 0x2C

typedef struct {
    /* 0x000 */ View view;
    /* 0x168 */ UNK_TYPE1 pad168[0x84];
    /* 0x1EC */ u16 unk1EC;
    /* 0x1EE */ u16 unk1EE;
    /* 0x1F0 */ u8 unk1F0;
    /* 0x1F1 */ UNK_TYPE1 pad1F1[0x3];
    /* 0x1F4 */ f32 unk1F4;
    /* 0x1F8 */ UNK_TYPE1 pad1F8[0xC];
    /* 0x204 */ u16 unk204;
    /* 0x206 */ UNK_TYPE1 pad206[0x6];
    /* 0x20C */ f32 unk20C;
    /* 0x210 */ f32 unk210;
    /* 0x214 */ f32 unk214;
    /* 0x218 */ f32 unk218;
    /* 0x21C */ f32 unk21C;
    /* 0x220 */ f32 unk220;
    /* 0x224 */ UNK_TYPE1 pad224[0xAC];
} GlobalContext16D30; // size = 0x2D0

typedef struct {
    /* 0x000 */ View view;
    /* 0x168 */ UNK_TYPE1 pad168[0xBE];
    /* 0x226 */ s16 lifeColorChange;
    /* 0x228 */ s16 lifeColorChangeDirection;
    /* 0x22A */ s16 unk22A;
    /* 0x22C */ s16 unk22C;
    /* 0x22E */ s16 unk22E;
    /* 0x230 */ s16 unk230;
    /* 0x232 */ s16 unk232;
    /* 0x234 */ s16 unk234;
    /* 0x236 */ s16 unk236;
    /* 0x238 */ s16 unk238;
    /* 0x23A */ s16 unk23A;
    /* 0x23C */ s16 unk23C;
    /* 0x23E */ s16 unk23E;
    /* 0x240 */ s16 unk240;
    /* 0x242 */ s16 unk242;
    /* 0x244 */ s16 unk244;
    /* 0x246 */ s16 unk246;
    /* 0x248 */ s16 unk248;
    /* 0x24A */ s16 unk24A;
    /* 0x24C */ s16 unk24C;
    /* 0x24E */ s16 unk24E;
    /* 0x250 */ s16 unk250;
    /* 0x252 */ s16 lifeSizeChange;
    /* 0x254 */ s16 lifeSizeChangeDirection; // 1 means shrinking, 0 growing
    /* 0x256 */ UNK_TYPE1 pad256[0x1A];
    /* 0x270 */ s16 lifeAlpha;
    /* 0x272 */ UNK_TYPE1 pad272[0xD6];
} InterfaceContext; // size = 0x348

typedef struct {
    /* 0x00 */ UNK_TYPE1 unk0;
    /* 0x01 */ UNK_TYPE1 unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ UNK_TYPE1 unk12;
    /* 0x13 */ UNK_TYPE1 unk13;
    /* 0x14 */ UNK_TYPE1 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ UNK_TYPE1 unk19;
    /* 0x1A */ UNK_TYPE1 unk1A;
    /* 0x1B */ UNK_TYPE1 unk1B;
    /* 0x1C */ UNK_TYPE1 unk1C;
    /* 0x1D */ UNK_TYPE1 unk1D;
    /* 0x1E */ u8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u16 unk22;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ UNK_TYPE1 unk26;
    /* 0x27 */ UNK_TYPE1 unk27;
    /* 0x28 */ LightInfo unk28;
    /* 0x36 */ LightInfo unk36;
    /* 0x44 */ UNK_TYPE1 unk44;
    /* 0x45 */ UNK_TYPE1 unk45;
    /* 0x46 */ UNK_TYPE1 unk46;
    /* 0x47 */ UNK_TYPE1 unk47;
    /* 0x48 */ UNK_TYPE1 unk48;
    /* 0x49 */ UNK_TYPE1 unk49;
    /* 0x4A */ UNK_TYPE1 unk4A;
    /* 0x4B */ UNK_TYPE1 unk4B;
    /* 0x4C */ UNK_TYPE1 unk4C;
    /* 0x4D */ UNK_TYPE1 unk4D;
    /* 0x4E */ UNK_TYPE1 unk4E;
    /* 0x4F */ UNK_TYPE1 unk4F;
    /* 0x50 */ UNK_TYPE1 unk50;
    /* 0x51 */ UNK_TYPE1 unk51;
    /* 0x52 */ UNK_TYPE1 unk52;
    /* 0x53 */ UNK_TYPE1 unk53;
    /* 0x54 */ UNK_TYPE1 unk54;
    /* 0x55 */ UNK_TYPE1 unk55;
    /* 0x56 */ UNK_TYPE1 unk56;
    /* 0x57 */ UNK_TYPE1 unk57;
    /* 0x58 */ UNK_TYPE1 unk58;
    /* 0x59 */ UNK_TYPE1 unk59;
    /* 0x5A */ UNK_TYPE1 unk5A;
    /* 0x5B */ UNK_TYPE1 unk5B;
    /* 0x5C */ UNK_TYPE1 unk5C;
    /* 0x5D */ UNK_TYPE1 unk5D;
    /* 0x5E */ UNK_TYPE1 unk5E;
    /* 0x5F */ UNK_TYPE1 unk5F;
    /* 0x60 */ UNK_TYPE1 unk60;
    /* 0x61 */ UNK_TYPE1 unk61;
    /* 0x62 */ UNK_TYPE1 unk62;
    /* 0x63 */ UNK_TYPE1 unk63;
    /* 0x64 */ UNK_TYPE1 unk64;
    /* 0x65 */ UNK_TYPE1 unk65;
    /* 0x66 */ UNK_TYPE1 unk66;
    /* 0x67 */ UNK_TYPE1 unk67;
    /* 0x68 */ UNK_TYPE1 unk68;
    /* 0x69 */ UNK_TYPE1 unk69;
    /* 0x6A */ UNK_TYPE1 unk6A;
    /* 0x6B */ UNK_TYPE1 unk6B;
    /* 0x6C */ UNK_TYPE1 unk6C;
    /* 0x6D */ UNK_TYPE1 unk6D;
    /* 0x6E */ UNK_TYPE1 unk6E;
    /* 0x6F */ UNK_TYPE1 unk6F;
    /* 0x70 */ UNK_TYPE1 unk70;
    /* 0x71 */ UNK_TYPE1 unk71;
    /* 0x72 */ UNK_TYPE1 unk72;
    /* 0x73 */ UNK_TYPE1 unk73;
    /* 0x74 */ UNK_TYPE1 unk74;
    /* 0x75 */ UNK_TYPE1 unk75;
    /* 0x76 */ UNK_TYPE1 unk76;
    /* 0x77 */ UNK_TYPE1 unk77;
    /* 0x78 */ UNK_TYPE1 unk78;
    /* 0x79 */ UNK_TYPE1 unk79;
    /* 0x7A */ UNK_TYPE1 unk7A;
    /* 0x7B */ UNK_TYPE1 unk7B;
    /* 0x7C */ UNK_TYPE1 unk7C;
    /* 0x7D */ UNK_TYPE1 unk7D;
    /* 0x7E */ UNK_TYPE1 unk7E;
    /* 0x7F */ UNK_TYPE1 unk7F;
    /* 0x80 */ UNK_TYPE1 unk80;
    /* 0x81 */ UNK_TYPE1 unk81;
    /* 0x82 */ UNK_TYPE1 unk82;
    /* 0x83 */ UNK_TYPE1 unk83;
    /* 0x84 */ UNK_TYPE1 unk84;
    /* 0x85 */ UNK_TYPE1 unk85;
    /* 0x86 */ UNK_TYPE1 unk86;
    /* 0x87 */ UNK_TYPE1 unk87;
    /* 0x88 */ UNK_TYPE1 unk88;
    /* 0x89 */ UNK_TYPE1 unk89;
    /* 0x8A */ UNK_TYPE1 unk8A;
    /* 0x8B */ UNK_TYPE1 unk8B;
    /* 0x8C */ Vec3s unk8C;
    /* 0x92 */ Vec3s unk92;
    /* 0x98 */ Vec3s unk98;
    /* 0x9E */ Vec3s unk9E;
    /* 0xA4 */ s16 unkA4;
    /* 0xA6 */ s16 unkA6;
    /* 0xA8 */ UNK_TYPE1 unkA8;
    /* 0xA9 */ UNK_TYPE1 unkA9;
    /* 0xAA */ UNK_TYPE1 unkAA;
    /* 0xAB */ UNK_TYPE1 unkAB;
    /* 0xAC */ s16 windWest;
    /* 0xAE */ s16 windVertical;
    /* 0xB0 */ s16 windSouth;
    /* 0xB2 */ UNK_TYPE1 unkB2;
    /* 0xB3 */ UNK_TYPE1 unkB3;
    /* 0xB4 */ f32 windClothIntensity;
    /* 0xB8 */ u8 environmentSettingsCount;
    /* 0xB9 */ UNK_TYPE1 unkB9;
    /* 0xBA */ UNK_TYPE1 unkBA;
    /* 0xBB */ UNK_TYPE1 unkBB;
    /* 0xBC */ void* environmentSettingsList;
    /* 0xC0 */ UNK_TYPE1 unkC0;
    /* 0xC1 */ u8 unkC1;
    /* 0xC2 */ u8 unkC2;
    /* 0xC3 */ u8 unkC3;
    /* 0xC4 */ Color_RGB8 unkC4;
    /* 0xC7 */ s8 unkC7;
    /* 0xC8 */ s8 unkC8;
    /* 0xC9 */ s8 unkC9;
    /* 0xCA */ Color_RGB8 unkCA;
    /* 0xCD */ s8 unkCD;
    /* 0xCE */ s8 unkCE;
    /* 0xCF */ s8 unkCF;
    /* 0xD0 */ Color_RGB8 unkD0;
    /* 0xD3 */ Color_RGB8 unkD3;
    /* 0xD6 */ s16 unkD6;
    /* 0xD8 */ s16 unkD8;
    /* 0xDA */ UNK_TYPE1 unkDA;
    /* 0xDB */ UNK_TYPE1 unkDB;
    /* 0xDC */ f32 unkDC;
    /* 0xE0 */ u8 unkE0;
    /* 0xE1 */ UNK_TYPE1 unkE1;
    /* 0xE2 */ s8 unkE2;
    /* 0xE3 */ UNK_TYPE1 unkE3;
    /* 0xE4 */ UNK_TYPE1 unkE4;
    /* 0xE5 */ UNK_TYPE1 unkE5;
    /* 0xE6 */ UNK_TYPE1 unkE6;
    /* 0xE7 */ UNK_TYPE1 unkE7;
    /* 0xE8 */ UNK_TYPE1 unkE8;
    /* 0xE9 */ UNK_TYPE1 unkE9;
    /* 0xEA */ UNK_TYPE1 unkEA;
    /* 0xEB */ UNK_TYPE1 unkEB;
    /* 0xEC */ UNK_TYPE1 unkEC;
    /* 0xED */ UNK_TYPE1 unkED;
    /* 0xEE */ UNK_TYPE1 unkEE;
    /* 0xEF */ UNK_TYPE1 unkEF;
    /* 0xF0 */ UNK_TYPE1 unkF0;
    /* 0xF1 */ UNK_TYPE1 unkF1;
    /* 0xF2 */ u8 unkF2[0xC];
} KankyoContext; // size = 0xFE

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


typedef struct {
    /* 0x00000 */ View view;
    /* 0x00168 */ Font font;
    /* 0x0A7E8 */ UNK_TYPE1 padA7E8[0x7708];
    /* 0x11EF0 */ u8 unk11EF0;
    /* 0x11EF1 */ UNK_TYPE1 pad11EF1[0x13];
    /* 0x11F04 */ u16 unk11F04;
    /* 0x11F06 */ UNK_TYPE1 pad11F06[0x4];
    /* 0x11F0A */ u8 unk11F0A;
    /* 0x11F0B */ UNK_TYPE1 pad11F0B[0x5];
    /* 0x11F10 */ s32 unk11F10;
    /* 0x11F11 */ UNK_TYPE1 pad11F11[0xD];
    /* 0x11F22 */ u8 unk11F22;
    /* 0x11F23 */ UNK_TYPE1 pad11F23[0xFD];
    /* 0x12020 */ u8 unk12020;
    /* 0x12021 */ UNK_TYPE1 pad12021[0x23];
    /* 0x12044 */ s16 unk12044;
    /* 0x12046 */ UNK_TYPE1 pad12046[0x24];
    /* 0x1206A */ s16 unk1206A;
    /* 0x1206C */ UNK_TYPE1 pad1206C[0x6C];
} MessageContext; // size = 0x120D8

// Full save context
typedef struct {
    /* 0x0000 */ SaveContextPerm perm;
    /* 0x100C */ SaveContextOwl owl;
    /* 0x3CA0 */ SaveContextExtra extra;
} SaveContext; // size = 0x48C8

typedef struct {
    /* 0x00 */ BgMeshHeader* sceneMesh;
    /* 0x04 */ Vec3f sceneMin;
    /* 0x10 */ Vec3f sceneMax;
    /* 0x1C */ s32 xSubdivisions;
    /* 0x20 */ s32 ySubdivisions;
    /* 0x24 */ s32 zSubdivisions;
    /* 0x28 */ Vec3f subdivisionSize;
    /* 0x34 */ Vec3f inverseSubdivisionSize;
    /* 0x40 */ BgMeshSubdivision* subdivisions;
    /* 0x44 */ BgScenePolygonLists scenePolyLists;
} StaticCollisionContext; // size = 0x50

typedef struct ActorBgMbarChair ActorBgMbarChair;

typedef struct ActorEnBji01 ActorEnBji01;

typedef struct ActorEnTest ActorEnTest;

typedef struct ActorListEntry ActorListEntry;

typedef struct DynaCollisionContext DynaCollisionContext;

typedef struct CollisionContext CollisionContext;

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

typedef struct DaytelopContext DaytelopContext;

typedef struct {
    /* 0x00 */ DynaPolyActor* actor;
    /* 0x04 */ BgMeshHeader* header;
    /* 0x08 */ ActorMeshPolyLists polyLists;
    /* 0x10 */ s16 verticesStartIndex;
    /* 0x12 */ s16 waterboxesStartIndex;
    /* 0x14 */ ActorMeshParams prevParams;
    /* 0x34 */ ActorMeshParams currParams;
    /* 0x54 */ Vec3s averagePos;
    /* 0x5A */ s16 radiusFromAveragePos;
    /* 0x5C */ f32 minY;
    /* 0x60 */ f32 maxY;
} ActorMesh; // size = 0x64

struct DynaCollisionContext {
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ UNK_TYPE1 pad1[0x3];
    /* 0x0004 */ ActorMesh actorMeshArr[50];
    /* 0x138C */ u16 flags[50]; // bit 0 - Is mesh active
    /* 0x13F0 */ CollisionPoly* polygons;
    /* 0x13F4 */ BgVertex* vertices;
    /* 0x13F8 */ BgWaterboxList waterboxes;
    /* 0x1400 */ BgPolygonLinkedList polygonList;
    /* 0x140C */ u32 maxNodes;
    /* 0x1410 */ u32 maxPolygons;
    /* 0x1414 */ u32 maxVertices;
    /* 0x1418 */ u32 maxMemory;
    /* 0x141C */ u32 unk141C;
}; // size = 0x1420

struct CollisionContext {
    /* 0x0000 */ StaticCollisionContext stat;
    /* 0x0050 */ DynaCollisionContext dyna;
}; // size = 0x1470

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

typedef struct FileChooseContext FileChooseContext;

typedef void(*filechoose_update_func)(FileChooseContext* ctxt);

typedef struct FireObj FireObj;

typedef struct FireObjLight FireObjLight;

typedef struct GameAlloc GameAlloc;

typedef struct GameState GameState;

typedef struct OpeningContext OpeningContext;

typedef struct PreNMIContext PreNMIContext;

typedef struct TitleContext TitleContext;

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

struct OpeningContext {
    /* 0x000 */ GameState common;
    /* 0x0A4 */ UNK_TYPE1 padA4[0x4];
    /* 0x0A8 */ View view;
}; // size = 0x210

struct PreNMIContext {
    /* 0x00 */ GameState state;
    /* 0xA4 */ u32 timer;
    /* 0xA8 */ UNK_TYPE4 unkA8;
}; // size = 0xAC

struct TitleContext {
    /* 0x000 */ GameState state;
    /* 0x0A4 */ u8* nintendo_logo_data;
    /* 0x0A8 */ View view;
    /* 0x210 */ SramContext sram;
    /* 0x230 */ UNK_TYPE1 pad230[0x8];
    /* 0x238 */ s16 unk238;
    /* 0x23A */ s16 logoCoverAlpha;
    /* 0x23C */ s16 logoCoverAlphaChangePerFrame;
    /* 0x23E */ s16 logoFullVisibilityDuration;
    /* 0x240 */ s16 frameCounter;
    /* 0x242 */ UNK_TYPE2 frameCounterMod0x80;
    /* 0x244 */ u8 switchToNextGameState;
    /* 0x245 */ UNK_TYPE1 pad245[0x3];
}; // size = 0x248

struct DaytelopContext {
    /* 0x000 */ GameState common;
    /* 0x0A4 */ UNK_TYPE1 padA4[0xC];
    /* 0x0B0 */ View view;
    /* 0x218 */ UNK_TYPE1 pad218[0x28];
    /* 0x240 */ s16 transitionCountdown;
    /* 0x242 */ s16 unk242;
    /* 0x244 */ s16 unk244;
    /* 0x246 */ UNK_TYPE1 pad246[0x2];
}; // size = 0x248

struct FileChooseContext {
    /* 0x00000 */ GameState common;
    /* 0x000A4 */ UNK_TYPE1 padA4[0x14];
    /* 0x000B8 */ View view;
    /* 0x00220 */ SramContext sram;
    /* 0x00240 */ UNK_TYPE1 pad240[0x12310];
    /* 0x12550 */ Font unk12550;
    /* 0x1CBD0 */ UNK_TYPE1 pad1CBD0[0x78B0];
    /* 0x24480 */ s16 unk24480;
    /* 0x24482 */ UNK_TYPE1 pad24482[0x2];
    /* 0x24484 */ s16 unk24484;
    /* 0x24486 */ s16 unk24486;
    /* 0x24488 */ UNK_TYPE1 pad24488[0x4];
    /* 0x2448C */ s16 unk2448C;
    /* 0x2448E */ UNK_TYPE1 pad2448E[0x1A];
    /* 0x244A8 */ s16 unk244A8;
    /* 0x244AA */ UNK_TYPE1 pad244AA[0x2];
    /* 0x244AC */ s16 unk244AC;
    /* 0x244AE */ s16 unk244AE;
    /* 0x244B0 */ s16 unk244B0;
    /* 0x244B2 */ s16 unk244B2;
    /* 0x244B4 */ s16 unk244B4;
    /* 0x244B6 */ s16 unk244B6;
    /* 0x244B8 */ s16 unk244B8;
    /* 0x244BA */ s16 unk244BA;
    /* 0x244BC */ UNK_TYPE1 pad244BC[0x18];
    /* 0x244D4 */ s16 unk244D4;
    /* 0x244D6 */ UNK_TYPE1 pad244D6[0x4];
    /* 0x244DA */ s16 unk244DA;
    /* 0x244DC */ UNK_TYPE1 pad244DC[0xA];
    /* 0x244E6 */ s16 unk244E6;
    /* 0x244E8 */ UNK_TYPE1 pad244E8[0x8];
    /* 0x244F0 */ s16 unk244F0;
    /* 0x244F2 */ s16 unk244F2;
    /* 0x244F4 */ UNK_TYPE1 pad244F4[0x6];
    /* 0x244FA */ s16 inputXChangeCooldown;
    /* 0x244FC */ s16 inputYChangeCooldown;
    /* 0x244FE */ s16 inputXDir;
    /* 0x24500 */ s16 inputYDir;
    /* 0x24502 */ s16 inputX;
    /* 0x24504 */ s16 inputY;
    /* 0x24506 */ UNK_TYPE1 pad24506[0x2];
    /* 0x24508 */ s16 unk24508;
    /* 0x2450A */ s16 unk2450A;
    /* 0x2450C */ UNK_TYPE1 pad2450C[0x1C];
    /* 0x24528 */ s16 unk24528;
    /* 0x2452A */ UNK_TYPE1 pad2452A[0x2E];
}; // size = 0x24558

typedef struct AudioThreadStruct AudioThreadStruct;

typedef struct GlobalContext GlobalContext;

typedef s32 (*ColChkResetFunc)(GlobalContext*, Collider*);
typedef void (*ColChkBloodFunc)(GlobalContext*, Collider*, Vec3f*);
typedef void (*ColChkApplyFunc)(GlobalContext*, CollisionCheckContext*, Collider*);
typedef void (*ColChkVsFunc)(GlobalContext*, CollisionCheckContext*, Collider*, Collider*);
typedef s32 (*ColChkLineFunc)(GlobalContext*, CollisionCheckContext*, Collider*, Vec3f*, Vec3f*);

typedef struct {
    /* 0x0 */ GlobalContext* ctxt;
    /* 0x4 */ s32 type; // bitfield, highest set bit determines type
    /* 0x8 */ s16 countdown;
    /* 0xA */ s16 state; // 0 - stopped, 1 - active, 2 - setup
} Quake2Context; // size = 0xC

typedef void(*cutscene_update_func)(GlobalContext* ctxt, CutsceneContext* cCtxt);

typedef void(*draw_func)(GlobalContext* ctxt, s16 index);

typedef void(*global_context_func)(GlobalContext*);

typedef void(*room_draw_func)(GlobalContext* ctxt, Room* room, u32 flags);

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

typedef void(*scene_header_func)(GlobalContext* ctxt, SceneCmd* entry);

typedef void(*scene_proc_draw_func)(GlobalContext* ctxt, u32 segment, void* params);

typedef struct Camera Camera;

typedef struct {
    /* 0x00 */ s16 randIdx;
    /* 0x02 */ s16 countdownMax;
    /* 0x04 */ Camera* cam;
    /* 0x08 */ u32 callbackIdx;
    /* 0x0C */ s16 y;
    /* 0x0E */ s16 x;
    /* 0x10 */ s16 zoom;
    /* 0x12 */ s16 rotZ;
    /* 0x14 */ QuakeRequest14 unk14;
    /* 0x1A */ s16 speed;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 countdown;
    /* 0x20 */ s16 camPtrIdx;
    /* 0x22 */ UNK_TYPE1 pad22[0x2];
} QuakeRequest; // size = 0x24

typedef s32(*camera_update_func)(Camera* camera);

typedef s16(*quake_callback_func)(QuakeRequest* req, ShakeInfo* shake);

typedef struct OSMesgQueueListNode_t {
    /* 0x0 */ struct OSMesgQueueListNode_t* next;
    /* 0x4 */ OSMesgQueue* queue;
} OSMesgQueueListNode; // size = 0x8

typedef struct {
    /* 0x000 */ OSScMsg verticalRetraceMesg;
    /* 0x020 */ OSScMsg prenmiMsg;
    /* 0x040 */ OSScMsg nmiMsg;
    /* 0x060 */ OSMesgQueue irqQueue;
    /* 0x078 */ OSMesg irqBuffer[8];
    /* 0x098 */ OSThread thread;
    /* 0x248 */ OSMesgQueueListNode* callbacks;
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
    /* 0x094 */ OSMesgQueueListNode irqmgrCallbackQueueNode;
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
} PadmgrThreadStruct; // size = 0x480

typedef struct {
    /* 0x000 */ OSMesgQueue unk0;
    /* 0x018 */ UNK_TYPE4 unk18[64];
    /* 0x118 */ OSMesgQueue unk118;
    /* 0x130 */ UNK_TYPE4 unk130[8];
    /* 0x150 */ OSThread thread;
    /* 0x300 */ UNK_TYPE4 unk300;
    /* 0x304 */ UNK_TYPE4 unk304;
    /* 0x308 */ UNK_TYPE4 unk308;
    /* 0x30C */ UNK_TYPE4 unk30C;
    /* 0x310 */ UNK_TYPE4 unk310;
    /* 0x314 */ UNK_TYPE4 unk314;
    /* 0x318 */ s32 unk318;
    /* 0x31C */ UNK_TYPE1 pad31C[0x4];
    /* 0x320 */ UNK_TYPE4 unk320;
    /* 0x324 */ UNK_TYPE4 unk324;
    /* 0x328 */ UNK_TYPE1 pad328[0x7];
    /* 0x32F */ s8 unk32F;
    /* 0x330 */ OSMesgQueueListNode unk330;
} SchedThreadStruct; // size = 0x338

struct AudioThreadStruct {
    /* 0x000 */ IrqMgr* irqmgr;
    /* 0x004 */ SchedThreadStruct* sched;
    /* 0x008 */ UNK_TYPE1 pad8[0x58];
    /* 0x060 */ UNK_TYPE4 unk60;
    /* 0x064 */ OSMesgQueue irqQueue;
    /* 0x07C */ OSMesg irqBuffer[30];
    /* 0x0F4 */ OSMesgQueue unkF4;
    /* 0x10C */ UNK_TYPE4 unk10C;
    /* 0x110 */ OSMesgQueue initDoneCallback;
    /* 0x128 */ OSMesg initDoneCallbackMsgBuffer[1];
    /* 0x12C */ UNK_TYPE1 pad12C[0x4];
    /* 0x130 */ OSThread thread;
}; // size = 0x2E0

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

struct Camera {
    /* 0x000 */ UNK_TYPE1 pad0[0x4];
    /* 0x004 */ Vec3f unk4;
    /* 0x010 */ UNK_TYPE1 pad10[0x8];
    /* 0x018 */ f32 unk18;
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ s16 unk1E;
    /* 0x020 */ Vec3f unk20;
    /* 0x02C */ UNK_TYPE1 pad2C[0x2];
    /* 0x02E */ s16 unk2E;
    /* 0x030 */ UNK_TYPE1 pad30[0x10];
    /* 0x040 */ s16 unk40;
    /* 0x042 */ s16 unk42;
    /* 0x044 */ UNK_TYPE1 pad44[0x8];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ UNK_TYPE1 pad4E[0x2];
    /* 0x050 */ Vec3f focalPoint;
    /* 0x05C */ Vec3f eye;
    /* 0x068 */ Vec3f upDir;
    /* 0x074 */ Vec3f unk74;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ f32 unk88;
    /* 0x08C */ GlobalContext* ctxt;
    /* 0x090 */ ActorPlayer* player;
    /* 0x094 */ PosRot unk94;
    /* 0x0A8 */ Actor* unkA8;
    /* 0x0AC */ Vec3f unkAC;
    /* 0x0B8 */ UNK_TYPE1 padB8[0x8];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ f32 unkCC;
    /* 0x0D0 */ f32 unkD0;
    /* 0x0D4 */ f32 unkD4;
    /* 0x0D8 */ UNK_TYPE1 padD8[0x4];
    /* 0x0DC */ f32 unkDC;
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ UNK_TYPE1 padE4[0x18];
    /* 0x0FC */ f32 fov;
    /* 0x100 */ f32 unk100;
    /* 0x104 */ UNK_TYPE1 pad104[0x30];
    /* 0x134 */ Vec3s unk134;
    /* 0x13A */ UNK_TYPE1 pad13A[0x4];
    /* 0x13E */ u16 unk13E;
    /* 0x140 */ s16 unk140;
    /* 0x142 */ s16 state;
    /* 0x144 */ s16 mode;
    /* 0x146 */ UNK_TYPE1 pad146[0x2];
    /* 0x148 */ s16 unk148;
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ UNK_TYPE1 pad14E[0x6];
    /* 0x154 */ s16 unk154;
    /* 0x156 */ UNK_TYPE1 pad156[0x4];
    /* 0x15A */ s16 unk15A;
    /* 0x15C */ s16 unk15C;
    /* 0x15E */ s16 unk15E;
    /* 0x160 */ UNK_TYPE1 pad160[0x4];
    /* 0x164 */ s16 unk164;
    /* 0x166 */ s16 unk166;
    /* 0x168 */ UNK_TYPE1 pad168[0x10];
}; // size = 0x178

typedef struct {
    /* 0x00 */ z_Matrix displayMatrix;
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
    /* 0x00 */ GlobalContext* ctxt;
    /* 0x04 */ Actor* actor;
    /* 0x08 */ u32 updateActorIfSet;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ Actor* unk10;
    /* 0x14 */ ActorPlayer* player;
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
    /* 0x254 */ UNK_TYPE1 pad254[0x14];
    /* 0x268 */ u8 unk268;
    /* 0x269 */ UNK_TYPE1 pad269[0x1B];
}; // size = 0x284

struct GlobalContext {
    /* 0x00000 */ GameState state;
    /* 0x000A4 */ s16 sceneNum;
    /* 0x000A6 */ u8 sceneConfig; // TODO: This at least controls the behavior of animated textures. Does it do more?
    /* 0x000A7 */ UNK_TYPE1 padA7[0x9];
    /* 0x000B0 */ SceneCmd* currentSceneVram;
    /* 0x000B4 */ UNK_TYPE1 padB4[0x4];
    /* 0x000B8 */ View view;
    /* 0x00220 */ Camera activeCameras[4];
    /* 0x00800 */ Camera* cameraPtrs[4];
    /* 0x00810 */ s16 activeCamera;
    /* 0x00812 */ s16 unk812;
    /* 0x00814 */ u8 unk814;
    /* 0x00815 */ u8 unk815;
    /* 0x00816 */ UNK_TYPE1 pad816[0x2];
    /* 0x00818 */ LightContext lightCtx;
    /* 0x00828 */ u32 unk828;
    /* 0x0082C */ UNK_TYPE1 pad82C[0x4];
    /* 0x00830 */ CollisionContext colCtx;
    /* 0x01CA0 */ ActorContext actorCtx;
    /* 0x01F24 */ CutsceneContext csCtx;
    /* 0x01F74 */ CutsceneEntry* cutsceneList;
    /* 0x01F78 */ GlobalContext1F78 unk1F78[16];
    /* 0x02138 */ EffFootmark footmarks[100];
    /* 0x046B8 */ SramContext sram;
    /* 0x046D8 */ UNK_TYPE1 pad46D8[0x8];
    /* 0x046E0 */ SkyboxContext skyboxCtx;
    /* 0x04908 */ MessageContext msgCtx;
    /* 0x169E0 */ UNK_TYPE1 pad169E0[0x8];
    /* 0x169E8 */ InterfaceContext interfaceCtx;
    /* 0x16D30 */ GlobalContext16D30 unk16D30;
    /* 0x17000 */ u16 unk17000;
    /* 0x17002 */ UNK_TYPE1 pad17002[0x2];
    /* 0x17004 */ KankyoContext kankyoContext;
    /* 0x17104 */ AnimationContext animationCtx;
    /* 0x17D88 */ SceneContext sceneContext;
    /* 0x186E0 */ RoomContext roomContext;
    /* 0x18760 */ u8 transitionActorCount;
    /* 0x18761 */ UNK_TYPE1 pad18761[0x3];
    /* 0x18764 */ TransitionActorEntry* transitionActorList;
    /* 0x18768 */ UNK_TYPE1 pad18768[0x48];
    /* 0x187B0 */ z_Matrix unk187B0;
    /* 0x187F0 */ UNK_TYPE1 pad187F0[0xC];
    /* 0x187FC */ MtxF mf_187FC;
    /* 0x1883C */ UNK_TYPE1 pad1883C[0x4];
    /* 0x18840 */ u32 unk18840;
    /* 0x18844 */ u8 unk18844;
    /* 0x18845 */ u8 unk18845;
    /* 0x18846 */ u16 sceneNumActorsToLoad;
    /* 0x18848 */ u8 numRooms;
    /* 0x18849 */ UNK_TYPE1 pad18849;
    /* 0x1884A */ s16 unk1884A;
    /* 0x1884C */ RoomFileLocation* roomList;
    /* 0x18850 */ ActorEntry* linkActorEntry;
    /* 0x18854 */ ActorEntry* setupActorList;
    /* 0x18858 */ UNK_PTR unk18858;
    /* 0x1885C */ EntranceEntry* setupEntranceList;
    /* 0x18860 */ u16* setupExitList;
    /* 0x18864 */ void* setupPathList;
    /* 0x18868 */ UNK_PTR unk18868;
    /* 0x1886C */ AnimatedTexture* sceneTextureAnimations;
    /* 0x18870 */ UNK_TYPE1 pad18870[0x4];
    /* 0x18874 */ u8 unk18874;
    /* 0x18875 */ s8 unk18875;
    /* 0x18876 */ UNK_TYPE1 pad18876[0x4];
    /* 0x1887A */ u16 unk1887A;
    /* 0x1887C */ s8 unk1887C;
    /* 0x1887D */ UNK_TYPE1 pad1887D[0x2];
    /* 0x1887F */ u8 unk1887F;
    /* 0x18880 */ UNK_TYPE1 pad18880[0x4];
    /* 0x18884 */ CollisionCheckContext colCheckCtx;
    /* 0x18B20 */ UNK_TYPE1 pad18B20[0x28];
    /* 0x18B48 */ u8 curSpawn;
    /* 0x18B49 */ UNK_TYPE1 pad18B49[0x1];
    /* 0x18B4A */ u8 unk18B4A;
    /* 0x18B4B */ UNK_TYPE1 pad18B4B[0x309];
    /* 0x18E54 */ SceneTableEntry* currentSceneTableEntry;
    /* 0x18E58 */ UNK_TYPE1 pad18E58[0x400];
}; // size = 0x19258

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} struct_801C5F44; // size = 0x14

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
