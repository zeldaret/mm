#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <all_types.h>

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
/* 0x00 */ u8 attack[32];
} ActorDamageChart; // size = 0x20

typedef struct {
/* 0x00 */ s32 unk0;
/* 0x04 */ s32 unk4;
/* 0x08 */ f32 unk8;
/* 0x0C */ f32 unkC;
/* 0x10 */ f32 unk10;
/* 0x14 */ f32 unk14;
/* 0x18 */ f32 unk18;
/* 0x1C */ f32 unk1C;
/* 0x20 */ f32 unk20;
/* 0x24 */ f32 unk24;
/* 0x28 */ f32 unk28;
/* 0x2C */ f32 unk2C;
/* 0x30 */ s16 unk30;
/* 0x32 */ s16 unk32;
/* 0x34 */ s16 unk34;
/* 0x36 */ s16 unk36;
/* 0x38 */ s16 unk38;
/* 0x3A */ s16 unk3A;
} ActorEnTest20C; // size = 0x3C

typedef struct {
/* 0x0 */ u32 cont : 1;
/* 0x0 */ u32 type : 4;
/* 0x0 */ u32 offset : 11;
/* 0x2 */ s32 value : 16;
} ActorInitVar; // size = 0x4

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
/* 0x0 */ u32 unk0;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 unk5;
} ColBumpInit; // size = 0x8

typedef struct {
/* 0x0 */ u8 unk0;
/* 0x1 */ u8 unk1;
/* 0x2 */ u8 unk2;
/* 0x3 */ u8 unk3;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 type;
} ColCommonInit; // size = 0x6

typedef struct {
/* 0x0 */ u32 collidesWith;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 damage;
} ColTouch; // size = 0x8

typedef struct {
/* 0x0 */ u32 unk0;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 unk5;
} ColTouchInit; // size = 0x8

typedef struct {
/* 0x0 */ u8 red;
/* 0x1 */ u8 green;
/* 0x2 */ u8 blue;
/* 0x3 */ u8 alpha;
} ColorRGBA8; // size = 0x4

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[0x2];
/* 0x02 */ u16 startFrame;
/* 0x04 */ u16 endFrame;
/* 0x06 */ UNK_TYPE1 pad6[0x2A];
} CsCmdActorAction; // size = 0x30

typedef struct {
/* 0x0 */ u16 base;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
} CsCmdBase; // size = 0x6

typedef struct {
/* 0x0 */ u16 unk0;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
/* 0x6 */ u8 hour;
/* 0x7 */ u8 minute;
} CsCmdDayTime; // size = 0x8

typedef struct {
/* 0x0 */ u16 setting;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
} CsCmdEnvLighting; // size = 0x6

typedef struct {
/* 0x0 */ u16 sequence;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
} CsCmdMusicChange; // size = 0x6

typedef struct {
/* 0x0 */ u16 type;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
} CsCmdMusicFade; // size = 0x6

typedef struct {
/* 0x0 */ u16 base;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
/* 0x6 */ u16 type;
/* 0x8 */ u16 textId1;
/* 0xA */ u16 textId2;
} CsCmdTextbox; // size = 0xC

typedef struct {
/* 0x0 */ u16 unk0;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
/* 0x6 */ u8 unk6;
/* 0x7 */ u8 unk7;
/* 0x8 */ u8 unk8;
/* 0x9 */ UNK_TYPE1 pad9[0x3];
} CsCmdUnk190; // size = 0xC

typedef struct {
/* 0x0 */ UNK_TYPE4 unk0;
/* 0x4 */ UNK_TYPE4 unk4;
} CsCmdUnk5A; // size = 0x8

typedef struct {
/* 0x0 */ u16 unk0;
/* 0x2 */ u16 startFrame;
/* 0x4 */ u16 endFrame;
/* 0x6 */ u8 unk6;
/* 0x7 */ u8 unk7;
/* 0x8 */ u8 unk8;
/* 0x9 */ UNK_TYPE1 pad9[0x3];
} CsCmdUnk9B; // size = 0xC

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
/* 0x0 */ u32 data;
/* 0x4 */ s16 unk4;
/* 0x6 */ u8 unk6;
/* 0x7 */ u8 unk7;
} CutsceneEntry; // size = 0x8

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
/* 0x0 */ u32 size;
/* 0x4 */ Gfx* buf;
/* 0x8 */ Gfx* p;
/* 0xC */ Gfx* d;
} DispBuf; // size = 0x10

typedef struct {
/* 0x0 */ u32 vromStart;
/* 0x4 */ u32 vromEnd;
/* 0x8 */ u32 romStart;
/* 0xC */ u32 romEnd;
} DmaEntry; // size = 0x10

typedef struct {
/* 0x00 */ u32 vromStart; // VROM address (source)
/* 0x04 */ void* dramAddr; // DRAM address (destination)
/* 0x08 */ u32 size; // File Transfer size
/* 0x0C */ char* filename; // Filename for debugging
/* 0x10 */ s32 line; // Line for debugging
/* 0x14 */ s32 unk14;
/* 0x18 */ OSMesgQueue* notifyQueue; // Message queue for the notification message
/* 0x1C */ OSMesg notifyMsg; // Completion notification message
} DmaRequest; // size = 0x20

typedef struct {
/* 0x000 */ UNK_TYPE1 pad0[0x184];
/* 0x184 */ ColorRGBA8 unk184;
/* 0x188 */ ColorRGBA8 unk188;
/* 0x18C */ ColorRGBA8 unk18C;
/* 0x190 */ ColorRGBA8 unk190;
/* 0x194 */ UNK_TYPE1 pad194[0xC];
} EffBlureInit1; // size = 0x1A0

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[0x8];
/* 0x08 */ ColorRGBA8 unk8;
/* 0x0C */ ColorRGBA8 unkC;
/* 0x10 */ ColorRGBA8 unk10;
/* 0x14 */ ColorRGBA8 unk14;
/* 0x18 */ UNK_TYPE1 pad18[0xC];
} EffBlureInit2; // size = 0x24

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[0x18];
} EffBlureParticle; // size = 0x18

typedef struct {
/* 0x0 */ u8 active;
/* 0x1 */ u8 unk1;
/* 0x2 */ u8 unk2;
/* 0x3 */ UNK_TYPE1 pad3[0x1];
} EffCommon; // size = 0x4

typedef struct {
/* 0x00 */ f32 startSpeed;
/* 0x04 */ f32 endXChange;
/* 0x08 */ f32 endX;
/* 0x0C */ f32 startXChange;
/* 0x10 */ f32 startX;
/* 0x14 */ s16 rotationY;
/* 0x16 */ s16 rotationZ;
} EffShieldParticleParticle; // size = 0x18

typedef struct {
/* 0x0 */ s16 unk0;
/* 0x2 */ s16 maxLife;
/* 0x4 */ ColorRGBA8 color;
} EffTireMarkInit; // size = 0x8

typedef enum EffectSSType {
    EFFECT_SS2_TYPE_DUST = 0x0,
    EFFECT_SS2_TYPE_SPARKLE = 0x1,
    EFFECT_SS2_TYPE_DELETED_2 = 0x2,
    EFFECT_SS2_TYPE_BOMB2 = 0x3,
    EFFECT_SS2_TYPE_BLAST = 0x4,
    EFFECT_SS2_TYPE_G_SPARK = 0x5,
    EFFECT_SS2_TYPE_DODONGO_FIRE = 0x6,
    EFFECT_SS2_TYPE_BUBBLE = 0x7,
    EFFECT_SS2_TYPE_DELETED_8 = 0x8,
    EFFECT_SS2_TYPE_G_RIPPLE = 0x9,
    EFFECT_SS2_TYPE_G_SPLASH = 0xA,
    EFFECT_SS2_TYPE_DELETED_B = 0xB,
    EFFECT_SS2_TYPE_G_FIRE = 0xC,
    EFFECT_SS2_TYPE_LIGHTNING = 0xD,
    EFFECT_SS2_TYPE_BIG_OCTO_BUBBLE = 0xE,
    EFFECT_SS2_TYPE_FRAGMENT = 0xF,
    EFFECT_SS2_TYPE_STICK = 0x10,
    EFFECT_SS2_TYPE_SPLASH = 0x11,
    EFFECT_SS2_TYPE_DELETED_12 = 0x12,
    EFFECT_SS2_TYPE_DELETED_13 = 0x13,
    EFFECT_SS2_TYPE_STONE1 = 0x14,
    EFFECT_SS2_TYPE_HIT_MARK = 0x15,
    EFFECT_SS2_TYPE_PHANTOM_GANON_FLASH = 0x16,
    EFFECT_SS2_TYPE_KAKARIKO_FIRE = 0x17,
    EFFECT_SS2_TYPE_SOLDIER_SEARCH_BALL = 0x18,
    EFFECT_SS2_TYPE_SHARD = 0x19,
    EFFECT_SS2_TYPE_ICE_PIECE = 0x1A,
    EFFECT_SS2_TYPE_ENEMY_ICE = 0x1B,
    EFFECT_SS2_TYPE_FIRE_TAIL = 0x1C,
    EFFECT_SS2_TYPE_ENEMY_FIRE = 0x1D,
    EFFECT_SS2_TYPE_EXTRA = 0x1E,
    EFFECT_SS2_TYPE_DELETED_1F = 0x1F,
    EFFECT_SS2_TYPE_DEAD_DEKU_BABA = 0x20,
    EFFECT_SS2_TYPE_DEAD_DODONGO = 0x21,
    EFFECT_SS2_TYPE_DEAD_DEKU_SCRUB = 0x22,
    EFFECT_SS2_TYPE_DELETED_23 = 0x23,
    EFFECT_SS2_TYPE_ICE_SMOKE = 0x24,
    EFFECT_SS2_TYPE_ICE_BLOCK = 0x25,
    EFFECT_SS2_TYPE_SBN = 0x26,
    EFFECT_SS2_TYPE_LAST_LABEL = 0x27
} EffectSSType;

typedef struct {
/* 0x0 */ u8 spawn;
/* 0x1 */ u8 room;
} EntranceEntry; // size = 0x2

typedef struct {
/* 0x0 */ s8 scene; // TODO what does it means for this to be neagtive?
/* 0x1 */ s8 unk1;
/* 0x2 */ u16 unk2;
} EntranceRecord; // size = 0x4

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
/* 0x0 */ UNK_TYPE4 size;
/* 0x4 */ void* heapStart;
/* 0x8 */ void* heapAppendStart;
/* 0xC */ void* heapAppendEnd;
} GameStateHeap; // size = 0x10

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
/* 0x1A4 */ DispBuf unk1A4;
/* 0x1B4 */ Gfx* unk1B4;
/* 0x1B8 */ DispBuf unk1B8;
/* 0x1C8 */ UNK_TYPE1 pad1C8[0xAC];
/* 0x274 */ OSViMode* unk274;
/* 0x278 */ void* zbuffer;
/* 0x27C */ UNK_TYPE1 pad27C[0x1C];
/* 0x298 */ DispBuf overlay;
/* 0x2A8 */ DispBuf polyOpa;
/* 0x2B8 */ DispBuf polyXlu;
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
/* 0x0 */ u16 buttons;
/* 0x2 */ s8 xAxis;
/* 0x3 */ s8 yAxis;
/* 0x4 */ s8 status;
/* 0x5 */ UNK_TYPE1 pad5[0x1];
} InputInfo; // size = 0x6

typedef struct {
/* 0x0 */ u8 type;
/* 0x2 */ u16 params[6];
} LightInfo; // size = 0xE

typedef struct {
/* 0x0 */ s8 dirX;
/* 0x1 */ s8 dirY;
/* 0x2 */ s8 dirZ;
/* 0x3 */ u8 red;
/* 0x4 */ u8 green;
/* 0x5 */ u8 blue;
/* 0x6 */ u16 pad[3];
} LightInfoDirectionalParams; // size = 0xC

typedef struct {
/* 0x0 */ s16 posX;
/* 0x2 */ s16 posY;
/* 0x4 */ s16 posZ;
/* 0x6 */ u8 red;
/* 0x7 */ u8 green;
/* 0x8 */ u8 blue;
/* 0x9 */ u8 unk9; // func_80102880 sets this only for type 2, func_80102A64 draws something if this is set
/* 0xA */ s16 radius;
} LightInfoPositionalParams; // size = 0xC

typedef struct {
/* 0x00 */ u8 enablePosLights;
/* 0x01 */ u8 numLights;
/* 0x02 */ UNK_TYPE1 pad2[0x6];
/* 0x08 */ Lights7 lights;
} LightMapper; // size = 0x80

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
/* 0x0 */ u8 red;
/* 0x1 */ u8 green;
/* 0x2 */ u8 blue;
} RGB; // size = 0x3

typedef struct {
/* 0x0 */ u8 red;
/* 0x1 */ u8 green;
/* 0x2 */ u8 blue;
/* 0x3 */ u8 alpha;
} RGBA8; // size = 0x4

typedef struct {
/* 0x00 */ s16 intPart[16];
/* 0x20 */ u16 fracPart[16];
} RSPMatrix; // size = 0x40

typedef struct {
/* 0x0 */ u32 vromStart;
/* 0x4 */ u32 vromEnd;
} RoomFileLocation; // size = 0x8

typedef struct {
/* 0x0 */ u32 opaqueDl;
/* 0x4 */ u32 translucentDl;
} RoomMeshType0Params; // size = 0x8

// Fields TODO
typedef struct {
/* 0x0 */ u8 type;
/* 0x1 */ u8 format; // 1 = single, 2 = multi
} RoomMeshType1; // size = 0x2

// Size TODO
typedef struct {
/* 0x0 */ UNK_TYPE1 pad0[0x10];
} RoomMeshType1Params; // size = 0x10

typedef struct {
/* 0x0 */ UNK_TYPE1 pad0[0x10];
} RoomMeshType2Params; // size = 0x10

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ u32 data2;
} SCmdBase;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdSpawnList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdActorList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdCsCameraList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdColHeader;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdRoomList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x02 */ UNK_TYPE1 pad2[2];
/* 0x04 */ s8  west;
/* 0x05 */ s8  vertical;
/* 0x06 */ s8  south;
/* 0x07 */ u8  clothIntensity;
} SCmdWindSettings;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdEntranceList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  cUpElfMsgNum;
/* 0x04 */ u32 keepObjectId;
} SCmdSpecialFiles;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  gpFlag1;
/* 0x04 */ u32 gpFlag2;
} SCmdRoomBehavior;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdMesh;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdObjectList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdLightList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdPathList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdTransiActorList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdLightSettingList;
// Cloudmodding has this as Environment Settings

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x02 */ UNK_TYPE1 pad2[2];
/* 0x04 */ u8  hour;
/* 0x05 */ u8  min;
/* 0x06 */ u8  unk6;
} SCmdTimeSettings;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x02 */ UNK_TYPE1 pad2[2];
/* 0x04 */ u8  skyboxId;
/* 0x05 */ u8  unk5;
/* 0x06 */ u8  unk6;
} SCmdSkyboxSettings;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x02 */ UNK_TYPE1 pad2[2];
/* 0x04 */ u8  unk4;
/* 0x05 */ u8  unk5;
} SCmdSkyboxDisables;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdExitList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ u32 data2;
} SCmdEndMarker;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  bgmId;
/* 0x02 */ UNK_TYPE1 pad2[4];
/* 0x06 */ u8  nighttimeSFX;
/* 0x07 */ u8  musicSeq;
} SCmdSoundSettings;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x02 */ UNK_TYPE1 pad2[5];
/* 0x07 */ u8  echo;
} SCmdEchoSettings;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdCutsceneData;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdAltHeaders;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ u32 data2;
} SCmdWorldMapVisited;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdTextureAnimations;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdCutsceneActorList;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  data1;
/* 0x04 */ void* segment;
} SCmdMinimapSettings;

typedef struct {
/* 0x00 */ u8  code;
/* 0x01 */ u8  num;
/* 0x04 */ void* segment;
} SCmdMinimapChests;

// Extra information in the save context that is not saved
typedef struct {
/* 0x000 */ UNK_TYPE1 pad0[0xC];
/* 0x00C */ s32 sceneSetupIndex;
/* 0x010 */ s32 unk10;
/* 0x014 */ UNK_TYPE1 pad14[0x2E];
/* 0x042 */ s16 unk42;
/* 0x044 */ UNK_TYPE1 pad44[0x232];
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
/* 0x14 */ UNK_TYPE1 pad14[0x1];
/* 0x15 */ s8 currentMagic;
/* 0x16 */ UNK_TYPE1 pad16[0x12];
} SaveContext_struct1; // size = 0x28

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[0x22];
} SaveContext_struct2; // size = 0x22

typedef union {
/* Command: N/A  */ SCmdBase              base;
/* Command: 0x00 */ SCmdSpawnList         spawnList;
/* Command: 0x01 */ SCmdActorList         actorList;
/* Command: 0x02 */ SCmdCsCameraList      csCameraList;
/* Command: 0x03 */ SCmdColHeader         colHeader;
/* Command: 0x04 */ SCmdRoomList          roomList;
/* Command: 0x05 */ SCmdWindSettings      windSettings;
/* Command: 0x06 */ SCmdEntranceList      entranceList;
/* Command: 0x07 */ SCmdSpecialFiles      specialFiles;
/* Command: 0x08 */ SCmdRoomBehavior      roomBehavior;
/* Command: 0x09 */ // Unused
/* Command: 0x0A */ SCmdMesh              mesh;
/* Command: 0x0B */ SCmdObjectList        objectList;
/* Command: 0x0C */ SCmdLightList         lightList;
/* Command: 0x0D */ SCmdPathList          pathList;
/* Command: 0x0E */ SCmdTransiActorList   transiActorList;
/* Command: 0x0F */ SCmdLightSettingList  lightSettingList;
/* Command: 0x10 */ SCmdTimeSettings      timeSettings;
/* Command: 0x11 */ SCmdSkyboxSettings    skyboxSettings;
/* Command: 0x12 */ SCmdSkyboxDisables    skyboxDisables;
/* Command: 0x13 */ SCmdExitList          exitList;
/* Command: 0x14 */ SCmdEndMarker         endMarker;
/* Command: 0x15 */ SCmdSoundSettings     soundSettings;
/* Command: 0x16 */ SCmdEchoSettings      echoSettings;
/* Command: 0x17 */ SCmdCutsceneData      cutsceneData;
/* Command: 0x18 */ SCmdAltHeaders        altHeaders;
/* Command: 0x19 */ SCmdWorldMapVisited   worldMapVisited;
/* Command: 0x1A */ SCmdTextureAnimations textureAnimations;
/* Command: 0x1B */ SCmdCutsceneActorList cutsceneActorList;
/* Command: 0x1C */ SCmdMinimapSettings   minimapSettings;
/* Command: 0x1D */ // Unused
/* Command: 0x1E */ SCmdMinimapChests     minimapChests;
} SceneCmd; // size = 0x8

typedef struct {
/* 0x0 */ u32 entranceCount;
/* 0x4 */ EntranceRecord** entrances;
/* 0x8 */ char* name;
} SceneEntranceTableEnty; // size = 0xC

typedef struct {
/* 0x00 */ u16 scenes[27];
} SceneIdList; // size = 0x36

typedef struct {
/* 0x00 */ s16 id; // Negative ids mean that the object is unloaded
/* 0x02 */ UNK_TYPE1 pad2[0x2];
/* 0x04 */ void* vramAddr;
/* 0x08 */ DmaRequest dmaReq;
/* 0x28 */ OSMesgQueue loadQueue;
/* 0x40 */ OSMesg loadMsg;
} SceneObject; // size = 0x44

typedef struct {
/* 0x0 */ u32 romStart;
/* 0x4 */ u32 romEnd;
/* 0x8 */ u16 unk8;
/* 0xA */ UNK_TYPE1 padA[0x1];
/* 0xB */ u8 sceneConfig; // TODO: This at least controls the behavior of animated textures. Does it do more?
/* 0xC */ UNK_TYPE1 padC[0x1];
/* 0xD */ u8 unkD;
/* 0xE */ UNK_TYPE1 padE[0x2];
} SceneTableEntry; // size = 0x10

typedef struct {
/* 0x0 */ s8 xStep;
/* 0x1 */ s8 yStep;
/* 0x2 */ u8 width;
/* 0x3 */ u8 height;
} ScrollingTextureParams; // size = 0x4

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
/* 0x10 */ ColorRGBA8 unk10;
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
/* 0x0 */ s8 unk0;
/* 0x1 */ UNK_TYPE1 pad1[0x1];
/* 0x2 */ s8 unk2;
/* 0x3 */ UNK_TYPE1 pad3[0x1];
/* 0x4 */ s16 actorIndex; // negative means already loaded?
/* 0x6 */ s16 x;
/* 0x8 */ s16 y;
/* 0xA */ s16 z;
/* 0xC */ s16 yRot; // lower 7 bits contain cutscene number
/* 0xE */ u16 variable;
} TransitionActorInit; // size = 0x10

typedef struct {
/* 0x0 */ f32 x;
/* 0x4 */ f32 y;
/* 0x8 */ f32 z;
} Vec3f; // size = 0xC

typedef struct {
/* 0x0 */ s16 x;
/* 0x2 */ s16 y;
/* 0x4 */ s16 z;
} Vec3s; // size = 0x6

typedef struct {
/* 0x0 */ s32 topY;
/* 0x4 */ s32 bottomY;
/* 0x8 */ s32 leftX;
/* 0xC */ s32 rightX;
} Viewport; // size = 0x10

typedef struct {
/* 0x00 */ void* bufferEnd;
/* 0x04 */ u32 romReadHead;
/* 0x08 */ u32 amountLeftToRead;
/* 0x0C */ u32 loadNextChunkBoundary;
/* 0x10 */ u32 destBufferEnd;
} Yaz0DecompState; // size = 0x14

typedef struct {
/* 0x0 */ unsigned int inst1;
/* 0x4 */ unsigned int inst2;
/* 0x8 */ unsigned int inst3;
/* 0xC */ unsigned int inst4;
} __osExceptionVector; // size = 0x10

typedef void(*actor_init_var_func)(u8*, ActorInitVar*);

typedef void(*eff_destroy_func)(void* params);

typedef void(*eff_draw_func)(void* params, GraphicsContext* gCtxt);

typedef void(*eff_init_func)(void* params, void* init);

typedef s32(*eff_update_func)(void* params);

typedef void*(*fault_address_converter_func)(void* addr, void* arg);

typedef void(*fault_client_func)(void* arg1, void* arg2);

typedef unsigned long(*func)(void);

typedef void(*func_ptr)(void);

typedef void(*light_map_directional_func)(LightMapper* mapper, void* params, Vec3f* pos);

typedef void(*osCreateThread_func)(void*);

typedef void*(*printf_func)(void*, char*, size_t);

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[0x20];
} s800E03A0; // size = 0x20

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

// Related to collision?
typedef struct {
/* 0x00 */ ActorDamageChart* damageChart;
/* 0x04 */ Vec3f displacement;
/* 0x10 */ s16 unk10;
/* 0x12 */ s16 unk12;
/* 0x14 */ s16 unk14;
/* 0x16 */ u8 mass;
/* 0x17 */ u8 health;
/* 0x18 */ u8 damage;
/* 0x19 */ u8 damageEffect;
/* 0x1A */ u8 impactEffect;
/* 0x1B */ UNK_TYPE1 pad1B[0x1];
} ActorA0; // size = 0x1C

typedef struct {
/* 0x0 */ s16 id;
/* 0x2 */ Vec3s pos;
/* 0x8 */ Vec3s rot;
/* 0xE */ s16 params;
} ActorEntry; // size = 0x10

typedef struct {
/* 0x00 */ Vec3f scale;
/* 0x0C */ Vec3s rotation;
/* 0x14 */ Vec3f pos;
} ActorMeshParams; // size = 0x20

typedef struct {
/* 0x0 */ u16 attributeIndex;
/* 0x2 */ u16 vertA; // upper 3 bits contain flags
/* 0x4 */ u16 vertB; // upper 3 bits contain flags
/* 0x6 */ u16 vertC;
/* 0x8 */ Vec3s normal;
/* 0xE */ s16 unkE;
} BgPolygon; // size = 0x10

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

typedef struct {
/* 0x00 */ u8 unk0;
/* 0x04 */ ColTouchInit unk4;
/* 0x0C */ ColBumpInit unkC;
/* 0x14 */ u8 unk14;
/* 0x15 */ u8 unk15;
/* 0x16 */ u8 unk16;
} ColBodyInfoInit; // size = 0x18

typedef struct {
/* 0x0 */ u32 collidesWith;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 unk5;
/* 0x6 */ Vec3s unk6;
} ColBump; // size = 0xC

typedef struct {
/* 0x0 */ s16 radius;
/* 0x2 */ s16 height;
/* 0x4 */ s16 yOffset;
/* 0x6 */ Vec3s loc;
} ColCylinderParams; // size = 0xC

typedef struct {
/* 0x00 */ Vec3f pointA;
/* 0x0C */ Vec3f pointB;
/* 0x18 */ Vec3f pointC;
/* 0x24 */ Vec3f pointD;
/* 0x30 */ Vec3s unk30;
/* 0x36 */ Vec3s unk36;
/* 0x3C */ f32 unk3C;
} ColQuadParams; // size = 0x40

typedef struct {
/* 0x0 */ Vec3s loc;
/* 0x6 */ s16 radius;
} ColSphereCollisionInfo; // size = 0x8

typedef struct {
/* 0x00 */ Vec3s unk0;
/* 0x06 */ s16 unk6;
/* 0x08 */ ColSphereCollisionInfo colInfo;
/* 0x10 */ f32 unk10;
/* 0x14 */ u8 unk14;
/* 0x15 */ UNK_TYPE1 pad15[0x3];
} ColSphereParams; // size = 0x18

typedef struct {
/* 0x0 */ u8 unk0;
/* 0x1 */ ColSphereCollisionInfo unk1;
/* 0xA */ s16 unkA;
} ColSphereParamsInit; // size = 0xC

typedef struct {
/* 0x00 */ Vec3f pointA;
/* 0x0C */ Vec3f pointB;
/* 0x18 */ Vec3f pointC;
/* 0x24 */ Vec3f unitNormal;
/* 0x30 */ f32 unk30;
} ColTriParams; // size = 0x34

typedef struct {
/* 0x00 */ Vec3f unk0;
/* 0x0C */ Vec3f unkC;
/* 0x18 */ Vec3f unk18;
} ColTriParamsInit; // size = 0x24

typedef struct {
/* 0x000 */ EffBlureParticle particles[16];
/* 0x180 */ UNK_TYPE1 pad180[0x4];
/* 0x184 */ f32 unk184;
/* 0x188 */ u16 unk188;
/* 0x18A */ UNK_TYPE1 pad18A[0x4];
/* 0x18E */ ColorRGBA8 unk18E;
/* 0x192 */ ColorRGBA8 unk192;
/* 0x196 */ ColorRGBA8 unk196;
/* 0x19A */ ColorRGBA8 unk19A;
/* 0x19E */ u8 unk19E;
/* 0x19F */ u8 unk19F;
/* 0x1A0 */ u8 unk1A0;
/* 0x1A1 */ u8 unk1A1;
/* 0x1A2 */ UNK_TYPE1 pad1A2[0xA];
} EffBlureParams; // size = 0x1AC

typedef struct {
/* 0x00 */ u32 paramsSize;
/* 0x04 */ eff_init_func init;
/* 0x08 */ eff_destroy_func destroy;
/* 0x0C */ eff_update_func update;
/* 0x10 */ eff_draw_func draw;
} EffInfo; // size = 0x14

typedef struct {
/* 0x00 */ u8 numParticles;
/* 0x02 */ Vec3s position;
/* 0x08 */ ColorRGBA8 primColorStart;
/* 0x0C */ ColorRGBA8 envColorStart;
/* 0x10 */ ColorRGBA8 primColorMid;
/* 0x14 */ ColorRGBA8 envColorMid;
/* 0x18 */ ColorRGBA8 primColorEnd;
/* 0x1C */ ColorRGBA8 envColorEnd;
/* 0x20 */ f32 acceleration;
/* 0x24 */ f32 maxInitialSpeed;
/* 0x28 */ f32 lengthCutoff;
/* 0x2C */ u8 duration;
/* 0x2E */ LightInfoPositionalParams lightParams;
/* 0x3C */ s32 hasLight;
} EffShieldParticleInit; // size = 0x40

typedef struct {
/* 0x00 */ Vec3f velocity;
/* 0x0C */ Vec3f position;
/* 0x18 */ Vec3s unk18;
/* 0x1E */ Vec3s unk1E;
} EffSparkParticle; // size = 0x24

typedef struct {
/* 0x00 */ UNK_TYPE2 active;
/* 0x02 */ Vec3s position1;
/* 0x08 */ Vec3s position2;
/* 0x0E */ s16 life;
/* 0x10 */ UNK_TYPE1 pad10[0x4];
/* 0x14 */ UNK_TYPE4 unk14;
} EffTireMarkParticle; // size = 0x18

typedef struct {
/* 0x00 */ Vec3f position;
/* 0x0C */ Vec3f velocity;
/* 0x18 */ Vec3f acceleration;
/* 0x24 */ ColorRGBA8 color1;
/* 0x28 */ ColorRGBA8 color2;
/* 0x2C */ s16 scale;
/* 0x2E */ s16 scaleChangePerFrame;
/* 0x30 */ s16 life;
/* 0x32 */ u16 flags; // bit0: ? bit1: ? bit2: randomize colors
/* 0x34 */ u8 type; // type0: start small, get big, fade away type1: start big, fade away
} EffectDustInit; // size = 0x35

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

typedef struct {
/* 0x0 */ u16 cycleLength;
/* 0x2 */ u16 numKeyFrames;
/* 0x4 */ FlashingTexturePrimColor* primColors;
/* 0x8 */ RGBA8* envColors;
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
/* 0x00 */ InputInfo current;
/* 0x06 */ InputInfo last;
/* 0x0C */ InputInfo pressEdge;
/* 0x12 */ InputInfo releaseEdge;
} Input; // size = 0x18

typedef struct {
/* 0x0 */ u8 type;
/* 0x2 */ LightInfoDirectionalParams params;
} LightInfoDirectional; // size = 0xE

typedef struct {
/* 0x0 */ u8 type;
/* 0x2 */ LightInfoPositionalParams params;
} LightInfoPositional; // size = 0xE

typedef struct {
/* 0x00 */ Vec3f a;
/* 0x0C */ Vec3f b;
} LineSegment; // size = 0x18

typedef struct {
/* 0x00 */ Vec3f pos;
/* 0x0C */ Vec3s rot;
} PosRot; // size = 0x14

typedef struct {
/* 0x0 */ u8 type;
/* 0x1 */ u8 count;
/* 0x2 */ UNK_TYPE1 pad2[0x2];
/* 0x4 */ RoomMeshType0Params* paramsStart;
/* 0x8 */ RoomMeshType0Params* paramsEnd;
} RoomMeshType0; // size = 0xC

typedef struct {
/* 0x0 */ u8 type;
/* 0x1 */ u8 count;
/* 0x2 */ UNK_TYPE1 pad2[0x2];
/* 0x4 */ RoomMeshType2Params* paramsStart;
/* 0x8 */ RoomMeshType2Params* paramsEnd;
} RoomMeshType2; // size = 0xC

// Permanent save context, kept in regular save files
typedef struct {
/* 0x0000 */ u32 entranceIndex; // bits 0-3 : offset; 4-8: spawn index; 9-15: scene index
/* 0x0004 */ UNK_TYPE1 pad4[0x4];
/* 0x0008 */ s32 cutscene;
/* 0x000C */ u16 time;
/* 0x000E */ UNK_TYPE1 padE[0xA];
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
/* 0x000 */ void* objectVramStart;
/* 0x004 */ void* objectVramEnd;
/* 0x008 */ u8 objectCount;
/* 0x009 */ u8 spawnedObjectCount;
/* 0x00A */ u8 mainKeepIndex;
/* 0x00B */ u8 keepObjectId;
/* 0x00C */ SceneObject objects[35]; // TODO: OBJECT_EXCHANGE_BANK_MAX array size
} SceneContext; // size = 0x958

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
/* 0x18 */ BgPolygon* polygons;
/* 0x1C */ BgPolygonAttributes* attributes;
/* 0x20 */ UNK_PTR cameraData;
/* 0x24 */ u16 numWaterBoxes;
/* 0x28 */ BgWaterBox* waterboxes;
} BgMeshHeader; // size = 0x2C

typedef struct {
/* 0x00 */ ColCommonInit base;
/* 0x08 */ ColBodyInfoInit body;
/* 0x20 */ ColCylinderParams info;
} ColCylinderInit; // size = 0x2C

typedef struct {
/* 0x00 */ ColCommonInit base;
/* 0x08 */ ColBodyInfoInit body;
/* 0x20 */ ColQuadParams params;
} ColQuadInit; // size = 0x60

typedef struct {
/* 0x00 */ ColBodyInfoInit body;
/* 0x18 */ ColSphereParamsInit params;
} ColSphereGroupElementInit; // size = 0x24

typedef struct {
/* 0x0 */ ColCommonInit base;
/* 0x6 */ UNK_TYPE1 pad6[0x2];
/* 0x8 */ u32 count;
/* 0xC */ ColSphereGroupElementInit* init;
} ColSphereGroupInit; // size = 0x10

typedef struct {
/* 0x00 */ ColCommonInit base;
/* 0x08 */ ColBodyInfoInit body;
/* 0x20 */ ColSphereParamsInit info;
} ColSphereInit; // size = 0x2C

typedef struct {
/* 0x00 */ ColBodyInfoInit body;
/* 0x18 */ ColTriParamsInit params;
} ColTriInit; // size = 0x3C

typedef struct {
/* 0x000 */ EffCommon base;
/* 0x004 */ EffBlureParams params;
} EffBlure; // size = 0x1B0

typedef struct {
/* 0x000 */ Vec3s position;
/* 0x008 */ s32 numParticles; // Will be calculated as particleFactor1 * particleFactor2 + 2
/* 0x00C */ EffSparkParticle particles[32];
/* 0x48C */ f32 velocity;
/* 0x490 */ f32 gravity;
/* 0x494 */ u32 particleFactor1;
/* 0x498 */ u32 particleFactor2;
/* 0x49C */ ColorRGBA8 colorStart[4];
/* 0x4AC */ ColorRGBA8 colorEnd[4];
/* 0x4BC */ s32 age;
/* 0x4C0 */ s32 duration;
} EffSparkParams; // size = 0x4C4

typedef struct {
/* 0x000 */ EffTireMarkParticle particles[64];
/* 0x600 */ s16 unk600;
/* 0x602 */ s16 numParticles;
/* 0x604 */ s16 maxLife;
/* 0x606 */ ColorRGBA8 color;
/* 0x60A */ UNK_TYPE1 pad60A[0x2];
} EffTireMarkParams; // size = 0x60C

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
/* 0x10 */ UNK_TYPE1 unk10;
/* 0x11 */ UNK_TYPE1 unk11;
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
/* 0x28 */ LightInfoDirectional unk28;
/* 0x36 */ LightInfoDirectional unk36;
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
/* 0xC4 */ RGB unkC4;
/* 0xC7 */ s8 unkC7;
/* 0xC8 */ s8 unkC8;
/* 0xC9 */ s8 unkC9;
/* 0xCA */ RGB unkCA;
/* 0xCD */ s8 unkCD;
/* 0xCE */ s8 unkCE;
/* 0xCF */ s8 unkCF;
/* 0xD0 */ RGB unkD0;
/* 0xD3 */ RGB unkD3;
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
} KankyoContext; // size = 0xF4

typedef struct {
/* 0x00000 */ View view;
/* 0x00168 */ Font font;
/* 0x0A7E8 */ UNK_TYPE1 padA7E8[0x7708];
/* 0x11EF0 */ u8 unk11EF0;
/* 0x11EF1 */ UNK_TYPE1 pad11EF1[0x13];
/* 0x11F04 */ u16 unk11F04;
/* 0x11F06 */ UNK_TYPE1 pad11F06[0x4];
/* 0x11F0A */ u8 unk11F0A;
/* 0x11F0B */ UNK_TYPE1 pad11F0B[0x17];
/* 0x11F22 */ u8 unk11F22;
/* 0x11F23 */ UNK_TYPE1 pad11F23[0xFD];
/* 0x12020 */ u8 unk12020;
/* 0x12021 */ UNK_TYPE1 pad12021[0x23];
/* 0x12044 */ s16 unk12044;
/* 0x12046 */ UNK_TYPE1 pad12046[0x24];
/* 0x1206A */ s16 unk1206A;
/* 0x1206C */ UNK_TYPE1 pad1206C[0x6C];
} MessageContext; // size = 0x120D8

typedef union {
    RoomMeshType0 type0;
    RoomMeshType1 type1;
    RoomMeshType2 type2;
} RoomMesh; // size = 0xC

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

typedef struct {
/* 0x0 */ ColCommonInit base;
/* 0x8 */ u32 count;
/* 0xC */ ColTriInit* elemInit;
} ColTriGroupInit; // size = 0x10

typedef struct {
/* 0x000 */ EffCommon base;
/* 0x004 */ EffSparkParams params;
} EffSpark; // size = 0x4C8

typedef struct {
/* 0x000 */ EffCommon base;
/* 0x004 */ EffTireMarkParams params;
} EffTireMark; // size = 0x610

typedef struct {
/* 0x00 */ s8 num;
/* 0x01 */ u8 unk1;
/* 0x02 */ u8 unk2;
/* 0x03 */ u8 unk3;
/* 0x04 */ s8 echo;
/* 0x05 */ u8 unk5;
/* 0x06 */ u8 enablePosLights;
/* 0x07 */ UNK_TYPE1 pad7[0x1];
/* 0x08 */ RoomMesh* mesh;
/* 0x0C */ void* segment;
/* 0x10 */ UNK_TYPE1 pad10[0x4];
} Room; // size = 0x14

typedef struct {
/* 0x00 */ Room currRoom;
/* 0x14 */ Room prevRoom;
/* 0x28 */ void* roomMemPages[2]; // In a scene with transitions, roomMemory is split between two pages that toggle each transition. This is one continuous range, as the second page allocates from the end
/* 0x30 */ u8 activeMemPage; // 0 - First page in memory, 1 - Second page
/* 0x31 */ s8 unk31;
/* 0x32 */ UNK_TYPE1 pad32[0x2];
/* 0x34 */ void* activeRoomVram;
/* 0x38 */ DmaRequest dmaRequest;
/* 0x58 */ OSMesgQueue loadQueue;
/* 0x70 */ OSMesg loadMsg[1];
/* 0x74 */ void* unk74;
/* 0x78 */ s8 unk78;
/* 0x79 */ s8 unk79;
/* 0x7A */ UNK_TYPE2 unk7A[3];
} RoomContext; // size = 0x80

typedef struct ActorBgFuKaiten ActorBgFuKaiten;

typedef struct ActorBgMbarChair ActorBgMbarChair;

typedef struct ActorEnBji01 ActorEnBji01;

typedef struct ActorEnTest ActorEnTest;

typedef struct ActorInit ActorInit;

typedef struct {
/* 0x00 */ u32 vromStart;
/* 0x04 */ u32 vromEnd;
/* 0x08 */ void* vramStart;
/* 0x0C */ void* vramEnd;
/* 0x10 */ void* loadedRamAddr; // original name: "allocp"
/* 0x14 */ ActorInit* initInfo;
/* 0x18 */ char* name;
/* 0x1C */ u16 allocType; // bit 0: don't allocate memory, use actorContext->0x250? bit 1: Always keep loaded?
/* 0x1E */ s8 nbLoaded; // original name: "clients"
/* 0x1F */ UNK_TYPE1 pad1F[0x1];
} ActorOverlay; // size = 0x20

typedef struct ActorListEntry ActorListEntry;

typedef struct ActorMesh ActorMesh;

typedef struct DynaCollisionContext DynaCollisionContext;

typedef struct CollisionContext CollisionContext;

typedef struct ActorPlayer ActorPlayer;

typedef struct ActorShape ActorShape;

typedef struct Arena Arena;

typedef struct ArenaNode ArenaNode;

struct Arena {
/* 0x00 */ ArenaNode* head;
/* 0x04 */ void* start;
/* 0x08 */ OSMesgQueue lock;
/* 0x20 */ u8 unk20;
/* 0x21 */ u8 isInit;
/* 0x22 */ u8 flag;
}; // size = 0x24

struct ArenaNode {
/* 0x0 */ s16 magic; // Should always be 0x7373
/* 0x2 */ s16 isFree;
/* 0x4 */ u32 size;
/* 0x8 */ ArenaNode* next;
/* 0xC */ ArenaNode* prev;
}; // size = 0x10

typedef struct CameraContext CameraContext;

typedef struct ColCommon ColCommon;

typedef struct {
/* 0x000 */ s16 ATgroupLength;
/* 0x002 */ u16 flags; // bit 0: collision bodies can't be added or removed, only swapped out
/* 0x004 */ ColCommon* ATgroup[50];
/* 0x0CC */ s32 ACgroupLength;
/* 0x0D0 */ ColCommon* ACgroup[60];
/* 0x1C0 */ s32 OTgroupLength;
/* 0x1C4 */ ColCommon* OTgroup[50];
/* 0x28C */ s32 group4Length;
/* 0x290 */ ColCommon* group4[3];
} CollisionCheckContext; // size = 0x29C

typedef struct ColBodyInfo ColBodyInfo;

struct ColBodyInfo {
/* 0x00 */ ColTouch toucher;
/* 0x08 */ ColBump bumper;
/* 0x14 */ u8 unk14;
/* 0x15 */ u8 unk15; // bit 0: can be toucher in AT-AC collision
/* 0x16 */ u8 unk16; // bit 0: can be bumper in AT-AC collision
/* 0x17 */ u8 unk17;
/* 0x18 */ ColCommon* unk18;
/* 0x1C */ ColCommon* unk1C;
/* 0x20 */ ColBodyInfo* unk20;
/* 0x24 */ ColBodyInfo* unk24;
}; // size = 0x28

typedef struct {
/* 0x00 */ ColBodyInfo body;
/* 0x28 */ ColSphereParams params;
} ColSphereGroupElement; // size = 0x40

typedef struct {
/* 0x00 */ ColBodyInfo body;
/* 0x28 */ ColTriParams params;
} ColTri; // size = 0x5C

typedef struct ColCylinder ColCylinder;

typedef struct ColQuad ColQuad;

typedef struct ColSphere ColSphere;

typedef struct ColSphereGroup ColSphereGroup;

typedef struct ColTriGroup ColTriGroup;

typedef struct ActorEnBom ActorEnBom;

typedef struct ActorEnFirefly ActorEnFirefly;

typedef struct ActorObjBell ActorObjBell;

typedef struct DaytelopContext DaytelopContext;

typedef struct DynaPolyActor DynaPolyActor;

struct ActorMesh {
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
}; // size = 0x64

struct DynaCollisionContext {
/* 0x0000 */ u8 unk0;
/* 0x0001 */ UNK_TYPE1 pad1[0x3];
/* 0x0004 */ ActorMesh actorMeshArr[50];
/* 0x138C */ u16 flags[50]; // bit 0 - Is mesh active
/* 0x13F0 */ BgPolygon* polygons;
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

typedef struct EffFootmark EffFootmark;

typedef struct EffShieldParticle EffShieldParticle;

typedef struct EffShieldParticleParams EffShieldParticleParams;

typedef struct EffTables EffTables;

typedef struct EffectTableInfo EffectTableInfo;

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
/* 0x74 */ GameStateHeap heap;
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

typedef struct IrqMgr IrqMgr;

typedef struct AudioThreadStruct AudioThreadStruct;

typedef struct LightingContext LightingContext;

typedef struct GlobalContext GlobalContext;

typedef struct {
/* 0x0 */ GlobalContext* ctxt;
/* 0x4 */ s32 type; // bitfield, highest set bit determines type
/* 0x8 */ s16 countdown;
/* 0xA */ s16 state; // 0 - stopped, 1 - active, 2 - setup
} Quake2Context; // size = 0xC

typedef s32(*collision_add_func)(GlobalContext*, ColCommon*);

typedef void(*collision_func)(GlobalContext*, CollisionCheckContext*, ColCommon*, ColCommon*);

typedef void(*cutscene_update_func)(GlobalContext* ctxt, CutsceneContext* cCtxt);

typedef void(*draw_func)(GlobalContext* ctxt, s16 index);

typedef void(*global_context_func)(GlobalContext*);

typedef void(*light_map_positional_func)(LightMapper* mapper, void* params, GlobalContext* ctxt);

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

typedef struct LightsList LightsList;

typedef struct LoadedParticleEntry LoadedParticleEntry;

struct EffectTableInfo {
/* 0x0 */ LoadedParticleEntry* data_table; // Name from debug assert
/* 0x4 */ s32 searchIndex;
/* 0x8 */ s32 size;
}; // size = 0xC

typedef void(*effect_func)(GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle);

typedef void(*effect_init_func)(GlobalContext* ctxt, u32 index, LoadedParticleEntry* particle, void* init);

struct LoadedParticleEntry {
/* 0x00 */ Vec3f position;
/* 0x0C */ Vec3f velocity;
/* 0x18 */ Vec3f acceleration;
/* 0x24 */ effect_func update;
/* 0x28 */ effect_func draw;
/* 0x2C */ Vec3f unk2C;
/* 0x38 */ u32 displayList;
/* 0x3C */ UNK_TYPE4 unk3C;
/* 0x40 */ s16 regs[13]; // These are particle-specific
/* 0x5A */ u16 flags; // bit 0: set if this entry is not considered free on a priority tie bit 1: ? bit 2: ?
/* 0x5C */ s16 life; // -1 means this entry is free
/* 0x5E */ u8 priority; // Lower number mean higher priority
/* 0x5F */ u8 type;
}; // size = 0x60

typedef struct {
/* 0x0 */ UNK_TYPE4 unk0;
/* 0x4 */ effect_init_func init;
} ParticleOverlayInfo; // size = 0x8

typedef struct {
/* 0x00 */ u32 vromStart;
/* 0x04 */ u32 vromEnd;
/* 0x08 */ void* vramStart;
/* 0x0C */ void* vramEnd;
/* 0x10 */ void* loadedRamAddr;
/* 0x14 */ ParticleOverlayInfo* overlayInfo;
/* 0x18 */ u32 unk18; // Always 0x01000000?
} ParticleOverlay; // size = 0x1C

typedef struct OSMesgQueueListNode OSMesgQueueListNode;

struct IrqMgr {
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
}; // size = 0x280

struct OSMesgQueueListNode {
/* 0x0 */ OSMesgQueueListNode* next;
/* 0x4 */ OSMesgQueue* queue;
}; // size = 0x8

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

typedef struct StackEntry StackEntry;

struct StackEntry {
/* 0x00 */ StackEntry* next;
/* 0x04 */ StackEntry* prev;
/* 0x08 */ u32 head;
/* 0x0C */ u32 tail;
/* 0x10 */ u32 initValue;
/* 0x14 */ s32 minSpace;
/* 0x18 */ const char* name;
}; // size = 0x1C

typedef struct TargetContext TargetContext;

typedef struct ActorContext ActorContext;

typedef struct s800B948C s800B948C;

typedef struct z_Light z_Light;

struct EffShieldParticleParams {
/* 0x000 */ EffShieldParticleParticle particles[16];
/* 0x180 */ u8 numParticles;
/* 0x181 */ UNK_TYPE1 pad181[0x1];
/* 0x182 */ Vec3s position;
/* 0x188 */ ColorRGBA8 primColorStart;
/* 0x18C */ ColorRGBA8 envColorStart;
/* 0x190 */ ColorRGBA8 primColorMid;
/* 0x194 */ ColorRGBA8 envColorMid;
/* 0x198 */ ColorRGBA8 primColorEnd;
/* 0x19C */ ColorRGBA8 envColorEnd;
/* 0x1A0 */ f32 acceleration;
/* 0x1A4 */ UNK_TYPE1 pad1A4[0x4];
/* 0x1A8 */ f32 maxInitialSpeed;
/* 0x1AC */ f32 lengthCutoff;
/* 0x1B0 */ u8 duration;
/* 0x1B1 */ u8 age;
/* 0x1B2 */ LightInfo lightInfo;
/* 0x1C0 */ z_Light* light;
/* 0x1C4 */ s32 hasLight;
}; // size = 0x1C8

struct FireObjLight {
/* 0x00 */ z_Light* light;
/* 0x04 */ LightInfoPositional lightInfo;
/* 0x12 */ u8 unk12;
}; // size = 0x13

struct LightingContext {
/* 0x0 */ z_Light* lightsHead;
/* 0x4 */ u8 ambientRed;
/* 0x5 */ u8 ambientGreen;
/* 0x6 */ u8 ambientBlue;
/* 0x7 */ u8 unk7;
/* 0x8 */ u8 unk8;
/* 0x9 */ u8 unk9;
/* 0xA */ s16 unkA;
/* 0xC */ s16 unkC;
}; // size = 0x10

struct z_Light {
/* 0x0 */ LightInfo* info;
/* 0x4 */ z_Light* prev;
/* 0x8 */ z_Light* next;
}; // size = 0xC

struct EffShieldParticle {
/* 0x000 */ EffCommon base;
/* 0x004 */ EffShieldParticleParams params;
}; // size = 0x1CC

struct EffTables {
/* 0x0000 */ GlobalContext* ctxt;
/* 0x0004 */ EffSpark sparks[3];
/* 0x0E5C */ EffBlure blures[25];
/* 0x388C */ EffShieldParticle shieldParticles[3];
/* 0x3DF0 */ EffTireMark tireMarks[15];
}; // size = 0x98E0

struct LightsList {
/* 0x000 */ int numOccupied;
/* 0x004 */ int nextFree;
/* 0x008 */ z_Light lights[32];
}; // size = 0x188

typedef struct Actor Actor;

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

struct CameraContext {
/* 0x000 */ Camera activeCameras[4];
/* 0x5E0 */ Camera* activeCameraPtrs[4];
/* 0x5F0 */ s16 activeCamera;
/* 0x5F2 */ s16 unk5F2;
}; // size = 0x5F4

struct ColCommon {
/* 0x00 */ Actor* actor;
/* 0x04 */ Actor* collisionAT;
/* 0x08 */ Actor* collisionAC;
/* 0x0C */ Actor* collisionOT;
/* 0x10 */ u8 flagsAT;
/* 0x11 */ u8 flagsAC; // bit 1 - collision occured?
/* 0x12 */ u8 unk12;
/* 0x13 */ u8 unk13;
/* 0x14 */ u8 unk14;
/* 0x15 */ u8 type;
/* 0x16 */ UNK_TYPE1 pad16[0x2];
}; // size = 0x18

struct ColCylinder {
/* 0x00 */ ColCommon base;
/* 0x18 */ ColBodyInfo body;
/* 0x40 */ ColCylinderParams params;
}; // size = 0x4C

struct ColQuad {
/* 0x00 */ ColCommon base;
/* 0x18 */ ColBodyInfo body;
/* 0x40 */ ColQuadParams params;
}; // size = 0x80

struct ColSphere {
/* 0x00 */ ColCommon base;
/* 0x18 */ ColBodyInfo body;
/* 0x40 */ ColSphereParams params;
}; // size = 0x58

struct ColSphereGroup {
/* 0x00 */ ColCommon base;
/* 0x18 */ u32 count;
/* 0x1C */ ColSphereGroupElement* spheres;
}; // size = 0x20

struct ColTriGroup {
/* 0x00 */ ColCommon base;
/* 0x18 */ u32 count;
/* 0x1C */ ColTri* tris;
}; // size = 0x20

struct EffFootmark {
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
}; // size = 0x60

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
/* 0x2C */ ColCylinder collision;
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

typedef void(*actor_func)(Actor* this, GlobalContext* ctxt);

typedef void(*actor_shadow_draw_func)(Actor* actor, LightMapper* mapper, GlobalContext* ctxt);

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

struct ActorInit {
/* 0x00 */ s16 id;
/* 0x02 */ u8 type;
/* 0x03 */ u8 room;
/* 0x04 */ u32 flags;
/* 0x08 */ s16 objectId;
/* 0x0C */ u32 instanceSize;
/* 0x10 */ actor_func init;
/* 0x14 */ actor_func destroy;
/* 0x18 */ actor_func update;
/* 0x1C */ actor_func draw;
}; // size = 0x20

struct ActorShape {
/* 0x00 */ Vec3s rot;
/* 0x08 */ f32 yDisplacement;
/* 0x0C */ actor_shadow_draw_func shadowDrawFunc;
/* 0x10 */ f32 scale;
/* 0x14 */ u8 alphaScale; // 255 means always draw full opacity if visible
}; // size = 0x18

struct GlobalContext {
/* 0x00000 */ GameState state;
/* 0x000A4 */ s16 sceneNum;
/* 0x000A6 */ u8 sceneConfig; // TODO: This at least controls the behavior of animated textures. Does it do more?
/* 0x000A7 */ UNK_TYPE1 padA7[0x9];
/* 0x000B0 */ SceneCmd* currentSceneVram;
/* 0x000B4 */ UNK_TYPE1 padB4[0x4];
/* 0x000B8 */ View view;
/* 0x00220 */ CameraContext cameraCtx;
/* 0x00814 */ u8 unk814;
/* 0x00815 */ u8 unk815;
/* 0x00816 */ UNK_TYPE1 pad816[0x2];
/* 0x00818 */ LightingContext lightCtx;
/* 0x00828 */ u32 unk828;
/* 0x0082C */ UNK_TYPE1 pad82C[0x4];
/* 0x00830 */ CollisionContext colCtx;
/* 0x01CA0 */ ActorContext actorCtx;
/* 0x01F24 */ CutsceneContext csCtx;
/* 0x01F74 */ CutsceneEntry* cutsceneList;
/* 0x01F78 */ GlobalContext1F78 unk1F78[16];
/* 0x02138 */ EffFootmark footmarks[100];
/* 0x046B8 */ SramContext sram;
/* 0x046D8 */ UNK_TYPE1 pad46D8[0x230];
/* 0x04908 */ MessageContext msgCtx;
/* 0x169E0 */ UNK_TYPE1 pad169E0[0x8];
/* 0x169E8 */ InterfaceContext interfaceCtx;
/* 0x16D30 */ GlobalContext16D30 unk16D30;
/* 0x17000 */ u16 unk17000;
/* 0x17002 */ UNK_TYPE1 pad17002[0x2];
/* 0x17004 */ KankyoContext kankyoContext;
/* 0x170F8 */ UNK_TYPE1 pad170F8[0xC90];
/* 0x17D88 */ SceneContext sceneContext;
/* 0x186E0 */ RoomContext roomContext;
/* 0x18760 */ u8 transitionActorCount;
/* 0x18761 */ UNK_TYPE1 pad18761[0x3];
/* 0x18764 */ TransitionActorInit* transitionActorList;
/* 0x18768 */ UNK_TYPE1 pad18768[0x48];
/* 0x187B0 */ z_Matrix unk187B0;
/* 0x187F0 */ UNK_TYPE1 pad187F0[0xC];
/* 0x187FC */ z_Matrix unk187FC;
/* 0x1883C */ UNK_TYPE1 pad1883C[0x4];
/* 0x18840 */ u32 unk18840;
/* 0x18844 */ u8 unk18844;
/* 0x18845 */ u8 unk18845;
/* 0x18846 */ u16 sceneNumActorsToLoad;
/* 0x18848 */ u8 numRooms;
/* 0x18849 */ UNK_TYPE1 pad18849[0x3];
/* 0x1884C */ RoomFileLocation* roomList;
/* 0x18850 */ ActorEntry* linkActorEntry;
/* 0x18854 */ ActorEntry* setupActorList;
/* 0x18858 */ UNK_PTR unk18858;
/* 0x1885C */ EntranceEntry* setupEntranceList;
/* 0x18860 */ void* setupExitList;
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

struct Actor {
/* 0x000 */ s16 id;
/* 0x002 */ u8 type;
/* 0x003 */ s8 room;
/* 0x004 */ u32 flags; // bit 20: is playing cutscene; bit 22: disable positional lights if bit 28 is not set; bit 28: enable positional lights on actor
/* 0x008 */ PosRot initPosRot;
/* 0x01C */ s16 params;
/* 0x01E */ s8 objBankIndex;
/* 0x01F */ UNK_TYPE1 unk1F;
/* 0x020 */ u16 unk20;
/* 0x022 */ u16 unk22;
/* 0x024 */ PosRot currPosRot;
/* 0x038 */ s8 cutscene;
/* 0x039 */ u8 unk39;
/* 0x03A */ UNK_TYPE1 pad3A[0x2];
/* 0x03C */ PosRot topPosRot;
/* 0x050 */ u16 unk50;
/* 0x052 */ UNK_TYPE1 pad52[0x2];
/* 0x054 */ f32 unk54;
/* 0x058 */ Vec3f scale;
/* 0x064 */ Vec3f velocity;
/* 0x070 */ f32 speedXZ;
/* 0x074 */ f32 gravity;
/* 0x078 */ f32 minVelocityY;
/* 0x07C */ BgPolygon* wallPoly;
/* 0x080 */ BgPolygon* floorPoly;
/* 0x084 */ u8 wallPolySource;
/* 0x085 */ u8 floorPolySource;
/* 0x086 */ UNK_TYPE1 pad86[0x2];
/* 0x088 */ f32 unk88;
/* 0x08C */ f32 unk8C;
/* 0x090 */ u16 unk90;
/* 0x092 */ s16 rotTowardsLinkY;
/* 0x094 */ f32 sqrdDistanceFromLink;
/* 0x098 */ f32 xzDistanceFromLink;
/* 0x09C */ f32 yDistanceFromLink;
/* 0x0A0 */ ActorA0 unkA0;
/* 0x0BC */ ActorShape shape;
/* 0x0D4 */ UNK_TYPE1 padD4[0x18];
/* 0x0EC */ Vec3f unkEC;
/* 0x0F8 */ f32 unkF8;
/* 0x0FC */ f32 unkFC;
/* 0x100 */ f32 unk100;
/* 0x104 */ f32 unk104;
/* 0x108 */ Vec3f lastPos;
/* 0x114 */ u8 unk114;
/* 0x115 */ u8 unk115;
/* 0x116 */ u16 textId;
/* 0x118 */ u16 freeze;
/* 0x11A */ u16 hitEffectParams; // TODO make into bitfield
/* 0x11C */ u8 hitEffectIntensity;
/* 0x11D */ u8 hasBeenDrawn;
/* 0x11E */ UNK_TYPE1 pad11E[0x1];
/* 0x11F */ u8 naviEnemyId;
/* 0x120 */ Actor* parent;
/* 0x124 */ Actor* child;
/* 0x128 */ Actor* prev;
/* 0x12C */ Actor* next;
/* 0x130 */ actor_func init;
/* 0x134 */ actor_func destroy;
/* 0x138 */ actor_func update;
/* 0x13C */ actor_func draw;
/* 0x140 */ ActorOverlay* overlayEntry;
}; // size = 0x144

typedef struct {
/* 0x000 */ Actor base;
/* 0x144 */ ColQuad unk144;
/* 0x1C4 */ ColQuad unk1C4;
/* 0x244 */ Vec3f unk244;
/* 0x250 */ f32 unk250;
/* 0x254 */ f32 unk254;
/* 0x258 */ actor_func update;
/* 0x25C */ s16 unk25C;
/* 0x25E */ u16 unk25E;
/* 0x260 */ u8 unk260;
/* 0x261 */ UNK_TYPE1 pad261[0x3];
} ActorArrowFire; // size = 0x264

typedef struct {
/* 0x000 */ Actor base;
/* 0x144 */ ColCylinder collision;
/* 0x190 */ AnimatedTexture* animatedTextures;
/* 0x194 */ actor_func update;
} ActorBgIkanaRay; // size = 0x198

struct ActorBgMbarChair {
/* 0x000 */ Actor base;
/* 0x144 */ UNK_TYPE1 pad144[0x18];
}; // size = 0x15C

typedef struct {
/* 0x000 */ Actor base;
/* 0x144 */ actor_func update;
/* 0x148 */ ColCylinder collision;
/* 0x194 */ UNK_TYPE1 pad194[0x14];
} ActorEnAObj; // size = 0x1A8

struct ActorEnBji01 {
/* 0x000 */ Actor base;
/* 0x144 */ UNK_TYPE1 pad144[0x170];
}; // size = 0x2B4

struct ActorEnBom {
/* 0x000 */ Actor base;
/* 0x144 */ ColCylinder unk144;
/* 0x190 */ ColSphereGroup unk190;
/* 0x1B0 */ ColSphereGroupElement unk1B0[1];
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
/* 0x31C */ ColSphere collision;
}; // size = 0x374

typedef struct {
/* 0x000 */ Actor base;
/* 0x144 */ actor_func update;
/* 0x148 */ s16 collectibleFlagId;
/* 0x14A */ s16 unk14A;
/* 0x14C */ s16 unk14C;
/* 0x14E */ s16 unk14E;
/* 0x150 */ s16 unk150;
/* 0x152 */ s16 unk152;
/* 0x154 */ f32 unk154;
/* 0x158 */ ColCylinder collision;
/* 0x1A4 */ UNK_TYPE1 pad1A4[0x4];
} ActorEnItem00; // size = 0x1A8

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
/* 0x150 */ actor_func unk150;
} ActorEnTest4; // size = 0x154

struct ActorObjBell {
/* 0x000 */ Actor base;
/* 0x144 */ UNK_TYPE1 pad144[0x18];
/* 0x15C */ ColSphere unk15C;
/* 0x1B4 */ ColSphere unk1B4;
/* 0x20C */ UNK_TYPE1 pad20C[0x2];
/* 0x20E */ s16 unk20E;
/* 0x210 */ UNK_TYPE1 pad210[0x4];
/* 0x214 */ s16 unk214;
/* 0x216 */ UNK_TYPE1 pad216[0x12];
}; // size = 0x228

struct ActorPlayer {
/* 0x000 */ Actor base;
/* 0x144 */ UNK_TYPE1 pad144[0x3];
/* 0x147 */ s8 unk147;
/* 0x148 */ UNK_TYPE1 pad148[0x3];
/* 0x14B */ u8 unk14B;
/* 0x14C */ UNK_TYPE1 pad14C[0x7];
/* 0x153 */ u8 unk153;
/* 0x154 */ UNK_TYPE1 pad154[0x1F8];
/* 0x34C */ Actor* unk34C;
/* 0x350 */ UNK_TYPE1 pad350[0x44];
/* 0x394 */ u8 unk394;
/* 0x395 */ UNK_TYPE1 pad395[0x37];
/* 0x3CC */ s16 unk3CC;
/* 0x3CE */ s8 unk3CE;
/* 0x3CF */ UNK_TYPE1 pad3CF[0x361];
/* 0x730 */ Actor* unk730;
/* 0x734 */ UNK_TYPE1 pad734[0x338];
/* 0xA6C */ u32 unkA6C;
/* 0xA70 */ u32 unkA70;
/* 0xA74 */ u32 unkA74;
/* 0xA78 */ UNK_TYPE1 padA78[0x8];
/* 0xA80 */ Actor* unkA80;
/* 0xA84 */ UNK_TYPE1 padA84[0x4];
/* 0xA88 */ Actor* unkA88;
/* 0xA8C */ f32 unkA8C;
/* 0xA90 */ UNK_TYPE1 padA90[0x44];
/* 0xAD4 */ s16 unkAD4;
/* 0xAD6 */ UNK_TYPE1 padAD6[0x8];
/* 0xADE */ u8 unkADE;
/* 0xADF */ UNK_TYPE1 padADF[0x4];
/* 0xAE3 */ s8 unkAE3;
/* 0xAE4 */ UNK_TYPE1 padAE4[0x44];
/* 0xB28 */ s16 unkB28;
/* 0xB2A */ UNK_TYPE1 padB2A[0x72];
/* 0xB9C */ Vec3f unkB9C;
/* 0xBA8 */ UNK_TYPE1 padBA8[0x1D0];
}; // size = 0xD78

struct DynaPolyActor {
/* 0x000 */ Actor actor;
/* 0x144 */ s32 dynaPolyId;
/* 0x148 */ f32 unk148;
/* 0x14C */ f32 unk14C;
/* 0x150 */ s16 unk150;
/* 0x152 */ s16 unk152;
/* 0x154 */ u32 unk154;
/* 0x158 */ u8 dynaFlags;
/* 0x159 */ UNK_TYPE1 pad159[0x3];
}; // size = 0x15C

struct ActorBgFuKaiten {
/* 0x000 */ DynaPolyActor bg;
/* 0x15C */ UNK_TYPE1 pad15C[0x4];
/* 0x160 */ f32 elevation;
/* 0x164 */ f32 bouceHeight;
/* 0x168 */ s16 rotationSpeed;
/* 0x16A */ s16 bounceSpeed;
/* 0x16C */ s16 bounce;
/* 0x16E */ UNK_TYPE1 pad16E[0x2];
}; // size = 0x170

struct ActorBgIknvObj {
/* 0x000 */ DynaPolyActor bg;
/* 0x15C */ ColCylinder collision;
/* 0x1A8 */ u32 displayListAddr;
/* 0x1AC */ actor_func updateFunc;
}; // size = 0x1B0

typedef struct {
    /* 0x00 */ u32 type;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ ColorRGBA8 color;
    /* 0x0C */ ColorRGBA8 envColor;
} struct_801F8010; // size = 0x10

typedef struct {
    /* 0x00 */ u32 useRgba;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ ColorRGBA8 primColor;
    /* 0x08 */ ColorRGBA8 envColor;
} struct_801F8020; // size = 0x10

typedef struct {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 setScissor;
    /* 0x08 */ ColorRGBA8 primColor;
    /* 0x0C */ ColorRGBA8 envColor;
    /* 0x10 */ u16* tlut;
    /* 0x14 */ Gfx* monoDl;
} VisMono; // size = 0x18

typedef enum {
    /* 0x000 */ ACTOR_PLAYER,
    /* 0x001 */ ACTOR_EN_TEST,
    /* 0x002 */ ACTOR_EN_GIRLA,
    /* 0x003 */ ACTOR_EN_PART,
    /* 0x004 */ ACTOR_EN_LIGHT,
    /* 0x005 */ ACTOR_EN_DOOR,
    /* 0x006 */ ACTOR_EN_BOX,
    /* 0x007 */ ACTOR_EN_PAMETFROG,
    /* 0x008 */ ACTOR_EN_OKUTA,
    /* 0x009 */ ACTOR_EN_BOM,
    /* 0x00A */ ACTOR_EN_WALLMAS,
    /* 0x00B */ ACTOR_EN_DODONGO,
    /* 0x00C */ ACTOR_EN_FIREFLY,
    /* 0x00D */ ACTOR_EN_HORSE,
    /* 0x00E */ ACTOR_EN_ITEM00,
    /* 0x00F */ ACTOR_EN_ARROW,
    /* 0x010 */ ACTOR_EN_ELF,
    /* 0x011 */ ACTOR_EN_NIW,
    /* 0x012 */ ACTOR_EN_TITE,
    /* 0x013 */ ACTOR_UNSET_13,
    /* 0x014 */ ACTOR_EN_PEEHAT,
    /* 0x015 */ ACTOR_EN_BUTTE,
    /* 0x016 */ ACTOR_EN_INSECT,
    /* 0x017 */ ACTOR_EN_FISH,
    /* 0x018 */ ACTOR_EN_HOLL,
    /* 0x019 */ ACTOR_EN_DINOFOS,
    /* 0x01A */ ACTOR_EN_HATA,
    /* 0x01B */ ACTOR_EN_ZL1,
    /* 0x01C */ ACTOR_EN_VIEWER,
    /* 0x01D */ ACTOR_EN_BUBBLE,
    /* 0x01E */ ACTOR_DOOR_SHUTTER,
    /* 0x01F */ ACTOR_UNSET_1F,
    /* 0x020 */ ACTOR_EN_BOOM,
    /* 0x021 */ ACTOR_EN_TORCH2,
    /* 0x022 */ ACTOR_EN_MINIFROG,
    /* 0x023 */ ACTOR_UNSET_23,
    /* 0x024 */ ACTOR_EN_ST,
    /* 0x025 */ ACTOR_UNSET_25,
    /* 0x026 */ ACTOR_EN_A_OBJ,
    /* 0x027 */ ACTOR_OBJ_WTURN,
    /* 0x028 */ ACTOR_EN_RIVER_SOUND,
    /* 0x029 */ ACTOR_UNSET_29,
    /* 0x02A */ ACTOR_EN_OSSAN,
    /* 0x02B */ ACTOR_UNSET_2B,
    /* 0x02C */ ACTOR_UNSET_2C,
    /* 0x02D */ ACTOR_EN_FAMOS,
    /* 0x02E */ ACTOR_UNSET_2E,
    /* 0x02F */ ACTOR_EN_BOMBF,
    /* 0x030 */ ACTOR_UNSET_30,
    /* 0x031 */ ACTOR_UNSET_31,
    /* 0x032 */ ACTOR_EN_AM,
    /* 0x033 */ ACTOR_EN_DEKUBABA,
    /* 0x034 */ ACTOR_EN_M_FIRE1,
    /* 0x035 */ ACTOR_EN_M_THUNDER,
    /* 0x036 */ ACTOR_BG_BREAKWALL,
    /* 0x037 */ ACTOR_UNSET_37,
    /* 0x038 */ ACTOR_DOOR_WARP1,
    /* 0x039 */ ACTOR_OBJ_SYOKUDAI,
    /* 0x03A */ ACTOR_ITEM_B_HEART,
    /* 0x03B */ ACTOR_EN_DEKUNUTS,
    /* 0x03C */ ACTOR_EN_BBFALL,
    /* 0x03D */ ACTOR_ARMS_HOOK,
    /* 0x03E */ ACTOR_EN_BB,
    /* 0x03F */ ACTOR_BG_KEIKOKU_SPR,
    /* 0x040 */ ACTOR_UNSET_40,
    /* 0x041 */ ACTOR_EN_WOOD02,
    /* 0x042 */ ACTOR_UNSET_42,
    /* 0x043 */ ACTOR_EN_DEATH,
    /* 0x044 */ ACTOR_EN_MINIDEATH,
    /* 0x045 */ ACTOR_UNSET_45,
    /* 0x046 */ ACTOR_UNSET_46,
    /* 0x047 */ ACTOR_EN_VM,
    /* 0x048 */ ACTOR_DEMO_EFFECT,
    /* 0x049 */ ACTOR_DEMO_KANKYO,
    /* 0x04A */ ACTOR_EN_FLOORMAS,
    /* 0x04B */ ACTOR_UNSET_4B,
    /* 0x04C */ ACTOR_EN_RD,
    /* 0x04D */ ACTOR_BG_F40_FLIFT,
    /* 0x04E */ ACTOR_UNSET_4E,
    /* 0x04F */ ACTOR_OBJ_MURE,
    /* 0x050 */ ACTOR_EN_SW,
    /* 0x051 */ ACTOR_OBJECT_KANKYO,
    /* 0x052 */ ACTOR_UNSET_52,
    /* 0x053 */ ACTOR_UNSET_53,
    /* 0x054 */ ACTOR_EN_HORSE_LINK_CHILD,
    /* 0x055 */ ACTOR_DOOR_ANA,
    /* 0x056 */ ACTOR_UNSET_56,
    /* 0x057 */ ACTOR_UNSET_57,
    /* 0x058 */ ACTOR_UNSET_58,
    /* 0x059 */ ACTOR_UNSET_59,
    /* 0x05A */ ACTOR_UNSET_5A,
    /* 0x05B */ ACTOR_EN_ENCOUNT1,
    /* 0x05C */ ACTOR_DEMO_TRE_LGT,
    /* 0x05D */ ACTOR_UNSET_5D,
    /* 0x05E */ ACTOR_UNSET_5E,
    /* 0x05F */ ACTOR_EN_ENCOUNT2,
    /* 0x060 */ ACTOR_EN_FIRE_ROCK,
    /* 0x061 */ ACTOR_BG_CTOWER_ROT,
    /* 0x062 */ ACTOR_MIR_RAY,
    /* 0x063 */ ACTOR_UNSET_63,
    /* 0x064 */ ACTOR_EN_SB,
    /* 0x065 */ ACTOR_EN_BIGSLIME,
    /* 0x066 */ ACTOR_EN_KAREBABA,
    /* 0x067 */ ACTOR_EN_IN,
    /* 0x068 */ ACTOR_UNSET_68,
    /* 0x069 */ ACTOR_EN_RU,
    /* 0x06A */ ACTOR_EN_BOM_CHU,
    /* 0x06B */ ACTOR_EN_HORSE_GAME_CHECK,
    /* 0x06C */ ACTOR_EN_RR,
    /* 0x06D */ ACTOR_UNSET_6D,
    /* 0x06E */ ACTOR_UNSET_6E,
    /* 0x06F */ ACTOR_UNSET_6F,
    /* 0x070 */ ACTOR_UNSET_70,
    /* 0x071 */ ACTOR_UNSET_71,
    /* 0x072 */ ACTOR_UNSET_72,
    /* 0x073 */ ACTOR_EN_FR,
    /* 0x074 */ ACTOR_UNSET_74,
    /* 0x075 */ ACTOR_UNSET_75,
    /* 0x076 */ ACTOR_UNSET_76,
    /* 0x077 */ ACTOR_UNSET_77,
    /* 0x078 */ ACTOR_UNSET_78,
    /* 0x079 */ ACTOR_UNSET_79,
    /* 0x07A */ ACTOR_OBJ_OSHIHIKI,
    /* 0x07B */ ACTOR_EFF_DUST,
    /* 0x07C */ ACTOR_BG_UMAJUMP,
    /* 0x07D */ ACTOR_ARROW_FIRE,
    /* 0x07E */ ACTOR_ARROW_ICE,
    /* 0x07F */ ACTOR_ARROW_LIGHT,
    /* 0x080 */ ACTOR_ITEM_ETCETERA,
    /* 0x081 */ ACTOR_OBJ_KIBAKO,
    /* 0x082 */ ACTOR_OBJ_TSUBO,
    /* 0x083 */ ACTOR_UNSET_83,
    /* 0x084 */ ACTOR_EN_IK,
    /* 0x085 */ ACTOR_UNSET_85,
    /* 0x086 */ ACTOR_UNSET_86,
    /* 0x087 */ ACTOR_UNSET_87,
    /* 0x088 */ ACTOR_UNSET_88,
    /* 0x089 */ ACTOR_DEMO_SHD,
    /* 0x08A */ ACTOR_EN_DNS,
    /* 0x08B */ ACTOR_ELF_MSG,
    /* 0x08C */ ACTOR_EN_HONOTRAP,
    /* 0x08D */ ACTOR_EN_TUBO_TRAP,
    /* 0x08E */ ACTOR_OBJ_ICE_POLY,
    /* 0x08F */ ACTOR_EN_FZ,
    /* 0x090 */ ACTOR_EN_KUSA,
    /* 0x091 */ ACTOR_OBJ_BEAN,
    /* 0x092 */ ACTOR_OBJ_BOMBIWA,
    /* 0x093 */ ACTOR_OBJ_SWITCH,
    /* 0x094 */ ACTOR_UNSET_94,
    /* 0x095 */ ACTOR_OBJ_LIFT,
    /* 0x096 */ ACTOR_OBJ_HSBLOCK,
    /* 0x097 */ ACTOR_EN_OKARINA_TAG,
    /* 0x098 */ ACTOR_UNSET_98,
    /* 0x099 */ ACTOR_EN_GOROIWA,
    /* 0x09A */ ACTOR_UNSET_9A,
    /* 0x09B */ ACTOR_UNSET_9B,
    /* 0x09C */ ACTOR_EN_DAIKU,
    /* 0x09D */ ACTOR_EN_NWC,
    /* 0x09E */ ACTOR_ITEM_INBOX,
    /* 0x09F */ ACTOR_EN_GE1,
    /* 0x0A0 */ ACTOR_OBJ_BLOCKSTOP,
    /* 0x0A1 */ ACTOR_EN_SDA,
    /* 0x0A2 */ ACTOR_EN_CLEAR_TAG,
    /* 0x0A3 */ ACTOR_UNSET_A3,
    /* 0x0A4 */ ACTOR_EN_GM,
    /* 0x0A5 */ ACTOR_EN_MS,
    /* 0x0A6 */ ACTOR_EN_HS,
    /* 0x0A7 */ ACTOR_BG_INGATE,
    /* 0x0A8 */ ACTOR_EN_KANBAN,
    /* 0x0A9 */ ACTOR_UNSET_A9,
    /* 0x0AA */ ACTOR_EN_ATTACK_NIW,
    /* 0x0AB */ ACTOR_UNSET_AB,
    /* 0x0AC */ ACTOR_UNSET_AC,
    /* 0x0AD */ ACTOR_UNSET_AD,
    /* 0x0AE */ ACTOR_EN_MK,
    /* 0x0AF */ ACTOR_EN_OWL,
    /* 0x0B0 */ ACTOR_EN_ISHI,
    /* 0x0B1 */ ACTOR_OBJ_HANA,
    /* 0x0B2 */ ACTOR_OBJ_LIGHTSWITCH,
    /* 0x0B3 */ ACTOR_OBJ_MURE2,
    /* 0x0B4 */ ACTOR_UNSET_B4,
    /* 0x0B5 */ ACTOR_EN_FU,
    /* 0x0B6 */ ACTOR_UNSET_B6,
    /* 0x0B7 */ ACTOR_UNSET_B7,
    /* 0x0B8 */ ACTOR_EN_STREAM,
    /* 0x0B9 */ ACTOR_EN_MM,
    /* 0x0BA */ ACTOR_UNSET_BA,
    /* 0x0BB */ ACTOR_UNSET_BB,
    /* 0x0BC */ ACTOR_EN_WEATHER_TAG,
    /* 0x0BD */ ACTOR_EN_ANI,
    /* 0x0BE */ ACTOR_UNSET_BE,
    /* 0x0BF */ ACTOR_EN_JS,
    /* 0x0C0 */ ACTOR_UNSET_C0,
    /* 0x0C1 */ ACTOR_UNSET_C1,
    /* 0x0C2 */ ACTOR_UNSET_C2,
    /* 0x0C3 */ ACTOR_UNSET_C3,
    /* 0x0C4 */ ACTOR_EN_OKARINA_EFFECT,
    /* 0x0C5 */ ACTOR_EN_MAG,
    /* 0x0C6 */ ACTOR_ELF_MSG2,
    /* 0x0C7 */ ACTOR_BG_F40_SWLIFT,
    /* 0x0C8 */ ACTOR_UNSET_C8,
    /* 0x0C9 */ ACTOR_UNSET_C9,
    /* 0x0CA */ ACTOR_EN_KAKASI,
    /* 0x0CB */ ACTOR_OBJ_MAKEOSHIHIKI,
    /* 0x0CC */ ACTOR_OCEFF_SPOT,
    /* 0x0CD */ ACTOR_UNSET_CD,
    /* 0x0CE */ ACTOR_EN_TORCH,
    /* 0x0CF */ ACTOR_UNSET_CF,
    /* 0x0D0 */ ACTOR_SHOT_SUN,
    /* 0x0D1 */ ACTOR_UNSET_D1,
    /* 0x0D2 */ ACTOR_UNSET_D2,
    /* 0x0D3 */ ACTOR_OBJ_ROOMTIMER,
    /* 0x0D4 */ ACTOR_EN_SSH,
    /* 0x0D5 */ ACTOR_UNSET_D5,
    /* 0x0D6 */ ACTOR_OCEFF_WIPE,
    /* 0x0D7 */ ACTOR_OCEFF_STORM,
    /* 0x0D8 */ ACTOR_OBJ_DEMO,
    /* 0x0D9 */ ACTOR_EN_MINISLIME,
    /* 0x0DA */ ACTOR_EN_NUTSBALL,
    /* 0x0DB */ ACTOR_UNSET_DB,
    /* 0x0DC */ ACTOR_UNSET_DC,
    /* 0x0DD */ ACTOR_UNSET_DD,
    /* 0x0DE */ ACTOR_UNSET_DE,
    /* 0x0DF */ ACTOR_OCEFF_WIPE2,
    /* 0x0E0 */ ACTOR_OCEFF_WIPE3,
    /* 0x0E1 */ ACTOR_UNSET_E1,
    /* 0x0E2 */ ACTOR_EN_DG,
    /* 0x0E3 */ ACTOR_EN_SI,
    /* 0x0E4 */ ACTOR_OBJ_COMB,
    /* 0x0E5 */ ACTOR_OBJ_KIBAKO2,
    /* 0x0E6 */ ACTOR_UNSET_E6,
    /* 0x0E7 */ ACTOR_EN_HS2,
    /* 0x0E8 */ ACTOR_OBJ_MURE3,
    /* 0x0E9 */ ACTOR_EN_TG,
    /* 0x0EA */ ACTOR_UNSET_EA,
    /* 0x0EB */ ACTOR_UNSET_EB,
    /* 0x0EC */ ACTOR_EN_WF,
    /* 0x0ED */ ACTOR_EN_SKB,
    /* 0x0EE */ ACTOR_UNSET_EE,
    /* 0x0EF */ ACTOR_EN_GS,
    /* 0x0F0 */ ACTOR_OBJ_SOUND,
    /* 0x0F1 */ ACTOR_EN_CROW,
    /* 0x0F2 */ ACTOR_UNSET_F2,
    /* 0x0F3 */ ACTOR_EN_COW,
    /* 0x0F4 */ ACTOR_UNSET_F4,
    /* 0x0F5 */ ACTOR_UNSET_F5,
    /* 0x0F6 */ ACTOR_OCEFF_WIPE4,
    /* 0x0F7 */ ACTOR_UNSET_F7,
    /* 0x0F8 */ ACTOR_EN_ZO,
    /* 0x0F9 */ ACTOR_OBJ_MAKEKINSUTA,
    /* 0x0FA */ ACTOR_EN_GE3,
    /* 0x0FB */ ACTOR_UNSET_FB,
    /* 0x0FC */ ACTOR_OBJ_HAMISHI,
    /* 0x0FD */ ACTOR_EN_ZL4,
    /* 0x0FE */ ACTOR_EN_MM2,
    /* 0x0FF */ ACTOR_UNSET_FF,
    /* 0x100 */ ACTOR_DOOR_SPIRAL,
    /* 0x101 */ ACTOR_UNSET_101,
    /* 0x102 */ ACTOR_OBJ_PZLBLOCK,
    /* 0x103 */ ACTOR_OBJ_TOGE,
    /* 0x104 */ ACTOR_UNSET_104,
    /* 0x105 */ ACTOR_OBJ_ARMOS,
    /* 0x106 */ ACTOR_OBJ_BOYO,
    /* 0x107 */ ACTOR_UNSET_107,
    /* 0x108 */ ACTOR_UNSET_108,
    /* 0x109 */ ACTOR_EN_GRASSHOPPER,
    /* 0x10A */ ACTOR_UNSET_10A,
    /* 0x10B */ ACTOR_OBJ_GRASS,
    /* 0x10C */ ACTOR_OBJ_GRASS_CARRY,
    /* 0x10D */ ACTOR_OBJ_GRASS_UNIT,
    /* 0x10E */ ACTOR_UNSET_10E,
    /* 0x10F */ ACTOR_UNSET_10F,
    /* 0x110 */ ACTOR_BG_FIRE_WALL,
    /* 0x111 */ ACTOR_EN_BU,
    /* 0x112 */ ACTOR_EN_ENCOUNT3,
    /* 0x113 */ ACTOR_EN_JSO,
    /* 0x114 */ ACTOR_OBJ_CHIKUWA,
    /* 0x115 */ ACTOR_EN_KNIGHT,
    /* 0x116 */ ACTOR_EN_WARP_TAG,
    /* 0x117 */ ACTOR_EN_AOB_01,
    /* 0x118 */ ACTOR_EN_BOJ_01,
    /* 0x119 */ ACTOR_EN_BOJ_02,
    /* 0x11A */ ACTOR_EN_BOJ_03,
    /* 0x11B */ ACTOR_EN_ENCOUNT4,
    /* 0x11C */ ACTOR_EN_BOM_BOWL_MAN,
    /* 0x11D */ ACTOR_EN_SYATEKI_MAN,
    /* 0x11E */ ACTOR_UNSET_11E,
    /* 0x11F */ ACTOR_BG_ICICLE,
    /* 0x120 */ ACTOR_EN_SYATEKI_CROW,
    /* 0x121 */ ACTOR_EN_BOJ_04,
    /* 0x122 */ ACTOR_EN_CNE_01,
    /* 0x123 */ ACTOR_EN_BBA_01,
    /* 0x124 */ ACTOR_EN_BJI_01,
    /* 0x125 */ ACTOR_BG_SPDWEB,
    /* 0x126 */ ACTOR_UNSET_126,
    /* 0x127 */ ACTOR_UNSET_127,
    /* 0x128 */ ACTOR_EN_MT_TAG,
    /* 0x129 */ ACTOR_BOSS_01,
    /* 0x12A */ ACTOR_BOSS_02,
    /* 0x12B */ ACTOR_BOSS_03,
    /* 0x12C */ ACTOR_BOSS_04,
    /* 0x12D */ ACTOR_BOSS_05,
    /* 0x12E */ ACTOR_BOSS_06,
    /* 0x12F */ ACTOR_BOSS_07,
    /* 0x130 */ ACTOR_BG_DY_YOSEIZO,
    /* 0x131 */ ACTOR_UNSET_131,
    /* 0x132 */ ACTOR_EN_BOJ_05,
    /* 0x133 */ ACTOR_UNSET_133,
    /* 0x134 */ ACTOR_UNSET_134,
    /* 0x135 */ ACTOR_EN_SOB1,
    /* 0x136 */ ACTOR_UNSET_136,
    /* 0x137 */ ACTOR_UNSET_137,
    /* 0x138 */ ACTOR_EN_GO,
    /* 0x139 */ ACTOR_UNSET_139,
    /* 0x13A */ ACTOR_EN_RAF,
    /* 0x13B */ ACTOR_OBJ_FUNEN,
    /* 0x13C */ ACTOR_OBJ_RAILLIFT,
    /* 0x13D */ ACTOR_BG_NUMA_HANA,
    /* 0x13E */ ACTOR_OBJ_FLOWERPOT,
    /* 0x13F */ ACTOR_OBJ_SPINYROLL,
    /* 0x140 */ ACTOR_DM_HINA,
    /* 0x141 */ ACTOR_EN_SYATEKI_WF,
    /* 0x142 */ ACTOR_OBJ_SKATEBLOCK,
    /* 0x143 */ ACTOR_OBJ_ICEBLOCK,
    /* 0x144 */ ACTOR_EN_BIGPAMET,
    /* 0x145 */ ACTOR_EN_SYATEKI_DEKUNUTS,
    /* 0x146 */ ACTOR_ELF_MSG3,
    /* 0x147 */ ACTOR_EN_FG,
    /* 0x148 */ ACTOR_DM_RAVINE,
    /* 0x149 */ ACTOR_DM_SA,
    /* 0x14A */ ACTOR_EN_SLIME,
    /* 0x14B */ ACTOR_EN_PR,
    /* 0x14C */ ACTOR_OBJ_TOUDAI,
    /* 0x14D */ ACTOR_OBJ_ENTOTU,
    /* 0x14E */ ACTOR_OBJ_BELL,
    /* 0x14F */ ACTOR_EN_SYATEKI_OKUTA,
    /* 0x150 */ ACTOR_UNSET_150,
    /* 0x151 */ ACTOR_OBJ_SHUTTER,
    /* 0x152 */ ACTOR_DM_ZL,
    /* 0x153 */ ACTOR_EN_ELFGRP,
    /* 0x154 */ ACTOR_DM_TSG,
    /* 0x155 */ ACTOR_EN_BAGUO,
    /* 0x156 */ ACTOR_OBJ_VSPINYROLL,
    /* 0x157 */ ACTOR_OBJ_SMORK,
    /* 0x158 */ ACTOR_EN_TEST2,
    /* 0x159 */ ACTOR_EN_TEST3,
    /* 0x15A */ ACTOR_EN_TEST4,
    /* 0x15B */ ACTOR_EN_BAT,
    /* 0x15C */ ACTOR_EN_SEKIHI,
    /* 0x15D */ ACTOR_EN_WIZ,
    /* 0x15E */ ACTOR_EN_WIZ_BROCK,
    /* 0x15F */ ACTOR_EN_WIZ_FIRE,
    /* 0x160 */ ACTOR_EFF_CHANGE,
    /* 0x161 */ ACTOR_DM_STATUE,
    /* 0x162 */ ACTOR_OBJ_FIRESHIELD,
    /* 0x163 */ ACTOR_BG_LADDER,
    /* 0x164 */ ACTOR_EN_MKK,
    /* 0x165 */ ACTOR_DEMO_GETITEM,
    /* 0x166 */ ACTOR_UNSET_166,
    /* 0x167 */ ACTOR_EN_DNB,
    /* 0x168 */ ACTOR_EN_DNH,
    /* 0x169 */ ACTOR_EN_DNK,
    /* 0x16A */ ACTOR_EN_DNQ,
    /* 0x16B */ ACTOR_UNSET_16B,
    /* 0x16C */ ACTOR_BG_KEIKOKU_SAKU,
    /* 0x16D */ ACTOR_OBJ_HUGEBOMBIWA,
    /* 0x16E */ ACTOR_EN_FIREFLY2,
    /* 0x16F */ ACTOR_EN_RAT,
    /* 0x170 */ ACTOR_EN_WATER_EFFECT,
    /* 0x171 */ ACTOR_EN_KUSA2,
    /* 0x172 */ ACTOR_BG_SPOUT_FIRE,
    /* 0x173 */ ACTOR_UNSET_173,
    /* 0x174 */ ACTOR_BG_DBLUE_MOVEBG,
    /* 0x175 */ ACTOR_EN_DY_EXTRA,
    /* 0x176 */ ACTOR_EN_BAL,
    /* 0x177 */ ACTOR_EN_GINKO_MAN,
    /* 0x178 */ ACTOR_EN_WARP_UZU,
    /* 0x179 */ ACTOR_OBJ_DRIFTICE,
    /* 0x17A */ ACTOR_EN_LOOK_NUTS,
    /* 0x17B */ ACTOR_EN_MUSHI2,
    /* 0x17C */ ACTOR_EN_FALL,
    /* 0x17D */ ACTOR_EN_MM3,
    /* 0x17E */ ACTOR_BG_CRACE_MOVEBG,
    /* 0x17F */ ACTOR_EN_DNO,
    /* 0x180 */ ACTOR_EN_PR2,
    /* 0x181 */ ACTOR_EN_PRZ,
    /* 0x182 */ ACTOR_EN_JSO2,
    /* 0x183 */ ACTOR_OBJ_ETCETERA,
    /* 0x184 */ ACTOR_EN_EGOL,
    /* 0x185 */ ACTOR_OBJ_MINE,
    /* 0x186 */ ACTOR_OBJ_PURIFY,
    /* 0x187 */ ACTOR_EN_TRU,
    /* 0x188 */ ACTOR_EN_TRT,
    /* 0x189 */ ACTOR_UNSET_189,
    /* 0x18A */ ACTOR_UNSET_18A,
    /* 0x18B */ ACTOR_EN_TEST5,
    /* 0x18C */ ACTOR_EN_TEST6,
    /* 0x18D */ ACTOR_EN_AZ,
    /* 0x18E */ ACTOR_EN_ESTONE,
    /* 0x18F */ ACTOR_BG_HAKUGIN_POST,
    /* 0x190 */ ACTOR_DM_OPSTAGE,
    /* 0x191 */ ACTOR_DM_STK,
    /* 0x192 */ ACTOR_DM_CHAR00,
    /* 0x193 */ ACTOR_DM_CHAR01,
    /* 0x194 */ ACTOR_DM_CHAR02,
    /* 0x195 */ ACTOR_DM_CHAR03,
    /* 0x196 */ ACTOR_DM_CHAR04,
    /* 0x197 */ ACTOR_DM_CHAR05,
    /* 0x198 */ ACTOR_DM_CHAR06,
    /* 0x199 */ ACTOR_DM_CHAR07,
    /* 0x19A */ ACTOR_DM_CHAR08,
    /* 0x19B */ ACTOR_DM_CHAR09,
    /* 0x19C */ ACTOR_OBJ_TOKEIDAI,
    /* 0x19D */ ACTOR_UNSET_19D,
    /* 0x19E */ ACTOR_EN_MNK,
    /* 0x19F */ ACTOR_EN_EGBLOCK,
    /* 0x1A0 */ ACTOR_EN_GUARD_NUTS,
    /* 0x1A1 */ ACTOR_BG_HAKUGIN_BOMBWALL,
    /* 0x1A2 */ ACTOR_OBJ_TOKEI_TOBIRA,
    /* 0x1A3 */ ACTOR_BG_HAKUGIN_ELVPOLE,
    /* 0x1A4 */ ACTOR_EN_MA4,
    /* 0x1A5 */ ACTOR_EN_TWIG,
    /* 0x1A6 */ ACTOR_EN_PO_FUSEN,
    /* 0x1A7 */ ACTOR_EN_DOOR_ETC,
    /* 0x1A8 */ ACTOR_EN_BIGOKUTA,
    /* 0x1A9 */ ACTOR_BG_ICEFLOE,
    /* 0x1AA */ ACTOR_OBJ_OCARINALIFT,
    /* 0x1AB */ ACTOR_EN_TIME_TAG,
    /* 0x1AC */ ACTOR_BG_OPEN_SHUTTER,
    /* 0x1AD */ ACTOR_BG_OPEN_SPOT,
    /* 0x1AE */ ACTOR_BG_FU_KAITEN,
    /* 0x1AF */ ACTOR_OBJ_AQUA,
    /* 0x1B0 */ ACTOR_EN_ELFORG,
    /* 0x1B1 */ ACTOR_EN_ELFBUB,
    /* 0x1B2 */ ACTOR_UNSET_1B2,
    /* 0x1B3 */ ACTOR_EN_FU_MATO,
    /* 0x1B4 */ ACTOR_EN_FU_KAGO,
    /* 0x1B5 */ ACTOR_EN_OSN,
    /* 0x1B6 */ ACTOR_BG_CTOWER_GEAR,
    /* 0x1B7 */ ACTOR_EN_TRT2,
    /* 0x1B8 */ ACTOR_OBJ_TOKEI_STEP,
    /* 0x1B9 */ ACTOR_BG_LOTUS,
    /* 0x1BA */ ACTOR_EN_KAME,
    /* 0x1BB */ ACTOR_OBJ_TAKARAYA_WALL,
    /* 0x1BC */ ACTOR_BG_FU_MIZU,
    /* 0x1BD */ ACTOR_EN_SELLNUTS,
    /* 0x1BE */ ACTOR_BG_DKJAIL_IVY,
    /* 0x1BF */ ACTOR_UNSET_1BF,
    /* 0x1C0 */ ACTOR_OBJ_VISIBLOCK,
    /* 0x1C1 */ ACTOR_EN_TAKARAYA,
    /* 0x1C2 */ ACTOR_EN_TSN,
    /* 0x1C3 */ ACTOR_EN_DS2N,
    /* 0x1C4 */ ACTOR_EN_FSN,
    /* 0x1C5 */ ACTOR_EN_SHN,
    /* 0x1C6 */ ACTOR_UNSET_1C6,
    /* 0x1C7 */ ACTOR_EN_STOP_HEISHI,
    /* 0x1C8 */ ACTOR_OBJ_BIGICICLE,
    /* 0x1C9 */ ACTOR_EN_LIFT_NUTS,
    /* 0x1CA */ ACTOR_EN_TK,
    /* 0x1CB */ ACTOR_UNSET_1CB,
    /* 0x1CC */ ACTOR_BG_MARKET_STEP,
    /* 0x1CD */ ACTOR_OBJ_LUPYGAMELIFT,
    /* 0x1CE */ ACTOR_EN_TEST7,
    /* 0x1CF */ ACTOR_OBJ_LIGHTBLOCK,
    /* 0x1D0 */ ACTOR_MIR_RAY2,
    /* 0x1D1 */ ACTOR_EN_WDHAND,
    /* 0x1D2 */ ACTOR_EN_GAMELUPY,
    /* 0x1D3 */ ACTOR_BG_DANPEI_MOVEBG,
    /* 0x1D4 */ ACTOR_EN_SNOWWD,
    /* 0x1D5 */ ACTOR_EN_PM,
    /* 0x1D6 */ ACTOR_EN_GAKUFU,
    /* 0x1D7 */ ACTOR_ELF_MSG4,
    /* 0x1D8 */ ACTOR_ELF_MSG5,
    /* 0x1D9 */ ACTOR_EN_COL_MAN,
    /* 0x1DA */ ACTOR_EN_TALK_GIBUD,
    /* 0x1DB */ ACTOR_EN_GIANT,
    /* 0x1DC */ ACTOR_OBJ_SNOWBALL,
    /* 0x1DD */ ACTOR_BOSS_HAKUGIN,
    /* 0x1DE */ ACTOR_EN_GB2,
    /* 0x1DF */ ACTOR_EN_ONPUMAN,
    /* 0x1E0 */ ACTOR_BG_TOBIRA01,
    /* 0x1E1 */ ACTOR_EN_TAG_OBJ,
    /* 0x1E2 */ ACTOR_OBJ_DHOUSE,
    /* 0x1E3 */ ACTOR_OBJ_HAKAISI,
    /* 0x1E4 */ ACTOR_BG_HAKUGIN_SWITCH,
    /* 0x1E5 */ ACTOR_UNSET_1E5,
    /* 0x1E6 */ ACTOR_EN_SNOWMAN,
    /* 0x1E7 */ ACTOR_TG_SW,
    /* 0x1E8 */ ACTOR_EN_PO_SISTERS,
    /* 0x1E9 */ ACTOR_EN_PP,
    /* 0x1EA */ ACTOR_EN_HAKUROCK,
    /* 0x1EB */ ACTOR_EN_HANABI,
    /* 0x1EC */ ACTOR_OBJ_DOWSING,
    /* 0x1ED */ ACTOR_OBJ_WIND,
    /* 0x1EE */ ACTOR_EN_RACEDOG,
    /* 0x1EF */ ACTOR_EN_KENDO_JS,
    /* 0x1F0 */ ACTOR_BG_BOTIHASIRA,
    /* 0x1F1 */ ACTOR_EN_FISH2,
    /* 0x1F2 */ ACTOR_EN_PST,
    /* 0x1F3 */ ACTOR_EN_POH,
    /* 0x1F4 */ ACTOR_OBJ_SPIDERTENT,
    /* 0x1F5 */ ACTOR_EN_ZORAEGG,
    /* 0x1F6 */ ACTOR_EN_KBT,
    /* 0x1F7 */ ACTOR_EN_GG,
    /* 0x1F8 */ ACTOR_EN_MARUTA,
    /* 0x1F9 */ ACTOR_OBJ_SNOWBALL2,
    /* 0x1FA */ ACTOR_EN_GG2,
    /* 0x1FB */ ACTOR_OBJ_GHAKA,
    /* 0x1FC */ ACTOR_EN_DNP,
    /* 0x1FD */ ACTOR_EN_DAI,
    /* 0x1FE */ ACTOR_BG_GORON_OYU,
    /* 0x1FF */ ACTOR_EN_KGY,
    /* 0x200 */ ACTOR_EN_INVADEPOH,
    /* 0x201 */ ACTOR_EN_GK,
    /* 0x202 */ ACTOR_EN_AN,
    /* 0x203 */ ACTOR_UNSET_203,
    /* 0x204 */ ACTOR_EN_BEE,
    /* 0x205 */ ACTOR_EN_OT,
    /* 0x206 */ ACTOR_EN_DRAGON,
    /* 0x207 */ ACTOR_OBJ_DORA,
    /* 0x208 */ ACTOR_EN_BIGPO,
    /* 0x209 */ ACTOR_OBJ_KENDO_KANBAN,
    /* 0x20A */ ACTOR_OBJ_HARIKO,
    /* 0x20B */ ACTOR_EN_STH,
    /* 0x20C */ ACTOR_BG_SINKAI_KABE,
    /* 0x20D */ ACTOR_BG_HAKA_CURTAIN,
    /* 0x20E */ ACTOR_BG_KIN2_BOMBWALL,
    /* 0x20F */ ACTOR_BG_KIN2_FENCE,
    /* 0x210 */ ACTOR_BG_KIN2_PICTURE,
    /* 0x211 */ ACTOR_BG_KIN2_SHELF,
    /* 0x212 */ ACTOR_EN_RAIL_SKB,
    /* 0x213 */ ACTOR_EN_JG,
    /* 0x214 */ ACTOR_EN_TRU_MT,
    /* 0x215 */ ACTOR_OBJ_UM,
    /* 0x216 */ ACTOR_EN_NEO_REEBA,
    /* 0x217 */ ACTOR_BG_MBAR_CHAIR,
    /* 0x218 */ ACTOR_BG_IKANA_BLOCK,
    /* 0x219 */ ACTOR_BG_IKANA_MIRROR,
    /* 0x21A */ ACTOR_BG_IKANA_ROTARYROOM,
    /* 0x21B */ ACTOR_BG_DBLUE_BALANCE,
    /* 0x21C */ ACTOR_BG_DBLUE_WATERFALL,
    /* 0x21D */ ACTOR_EN_KAIZOKU,
    /* 0x21E */ ACTOR_EN_GE2,
    /* 0x21F */ ACTOR_EN_MA_YTS,
    /* 0x220 */ ACTOR_EN_MA_YTO,
    /* 0x221 */ ACTOR_OBJ_TOKEI_TURRET,
    /* 0x222 */ ACTOR_BG_DBLUE_ELEVATOR,
    /* 0x223 */ ACTOR_OBJ_WARPSTONE,
    /* 0x224 */ ACTOR_EN_ZOG,
    /* 0x225 */ ACTOR_OBJ_ROTLIFT,
    /* 0x226 */ ACTOR_OBJ_JG_GAKKI,
    /* 0x227 */ ACTOR_BG_INIBS_MOVEBG,
    /* 0x228 */ ACTOR_EN_ZOT,
    /* 0x229 */ ACTOR_OBJ_TREE,
    /* 0x22A */ ACTOR_OBJ_Y2LIFT,
    /* 0x22B */ ACTOR_OBJ_Y2SHUTTER,
    /* 0x22C */ ACTOR_OBJ_BOAT,
    /* 0x22D */ ACTOR_OBJ_TARU,
    /* 0x22E */ ACTOR_OBJ_HUNSUI,
    /* 0x22F */ ACTOR_EN_JC_MATO,
    /* 0x230 */ ACTOR_MIR_RAY3,
    /* 0x231 */ ACTOR_EN_ZOB,
    /* 0x232 */ ACTOR_ELF_MSG6,
    /* 0x233 */ ACTOR_OBJ_NOZOKI,
    /* 0x234 */ ACTOR_EN_TOTO,
    /* 0x235 */ ACTOR_EN_RAILGIBUD,
    /* 0x236 */ ACTOR_EN_BABA,
    /* 0x237 */ ACTOR_EN_SUTTARI,
    /* 0x238 */ ACTOR_EN_ZOD,
    /* 0x239 */ ACTOR_EN_KUJIYA,
    /* 0x23A */ ACTOR_EN_GEG,
    /* 0x23B */ ACTOR_OBJ_KINOKO,
    /* 0x23C */ ACTOR_OBJ_YASI,
    /* 0x23D */ ACTOR_EN_TANRON1,
    /* 0x23E */ ACTOR_EN_TANRON2,
    /* 0x23F */ ACTOR_EN_TANRON3,
    /* 0x240 */ ACTOR_OBJ_CHAN,
    /* 0x241 */ ACTOR_EN_ZOS,
    /* 0x242 */ ACTOR_EN_S_GORO,
    /* 0x243 */ ACTOR_EN_NB,
    /* 0x244 */ ACTOR_EN_JA,
    /* 0x245 */ ACTOR_BG_F40_BLOCK,
    /* 0x246 */ ACTOR_BG_F40_SWITCH,
    /* 0x247 */ ACTOR_EN_PO_COMPOSER,
    /* 0x248 */ ACTOR_EN_GURUGURU,
    /* 0x249 */ ACTOR_OCEFF_WIPE5,
    /* 0x24A */ ACTOR_EN_STONE_HEISHI,
    /* 0x24B */ ACTOR_OCEFF_WIPE6,
    /* 0x24C */ ACTOR_EN_SCOPENUTS,
    /* 0x24D */ ACTOR_EN_SCOPECROW,
    /* 0x24E */ ACTOR_OCEFF_WIPE7,
    /* 0x24F */ ACTOR_EFF_KAMEJIMA_WAVE,
    /* 0x250 */ ACTOR_EN_HG,
    /* 0x251 */ ACTOR_EN_HGO,
    /* 0x252 */ ACTOR_EN_ZOV,
    /* 0x253 */ ACTOR_EN_AH,
    /* 0x254 */ ACTOR_OBJ_HGDOOR,
    /* 0x255 */ ACTOR_BG_IKANA_BOMBWALL,
    /* 0x256 */ ACTOR_BG_IKANA_RAY,
    /* 0x257 */ ACTOR_BG_IKANA_SHUTTER,
    /* 0x258 */ ACTOR_BG_HAKA_BOMBWALL,
    /* 0x259 */ ACTOR_BG_HAKA_TOMB,
    /* 0x25A */ ACTOR_EN_SC_RUPPE,
    /* 0x25B */ ACTOR_BG_IKNV_DOUKUTU,
    /* 0x25C */ ACTOR_BG_IKNV_OBJ,
    /* 0x25D */ ACTOR_EN_PAMERA,
    /* 0x25E */ ACTOR_OBJ_HSSTUMP,
    /* 0x25F */ ACTOR_EN_HIDDEN_NUTS,
    /* 0x260 */ ACTOR_EN_ZOW,
    /* 0x261 */ ACTOR_EN_TALK,
    /* 0x262 */ ACTOR_EN_AL,
    /* 0x263 */ ACTOR_EN_TAB,
    /* 0x264 */ ACTOR_EN_NIMOTSU,
    /* 0x265 */ ACTOR_EN_HIT_TAG,
    /* 0x266 */ ACTOR_EN_RUPPECROW,
    /* 0x267 */ ACTOR_EN_TANRON4,
    /* 0x268 */ ACTOR_EN_TANRON5,
    /* 0x269 */ ACTOR_EN_TANRON6,
    /* 0x26A */ ACTOR_EN_DAIKU2,
    /* 0x26B */ ACTOR_EN_MUTO,
    /* 0x26C */ ACTOR_EN_BAISEN,
    /* 0x26D */ ACTOR_EN_HEISHI,
    /* 0x26E */ ACTOR_EN_DEMO_HEISHI,
    /* 0x26F */ ACTOR_EN_DT,
    /* 0x270 */ ACTOR_EN_CHA,
    /* 0x271 */ ACTOR_OBJ_DINNER,
    /* 0x272 */ ACTOR_EFF_LASTDAY,
    /* 0x273 */ ACTOR_BG_IKANA_DHARMA,
    /* 0x274 */ ACTOR_EN_AKINDONUTS,
    /* 0x275 */ ACTOR_EFF_STK,
    /* 0x276 */ ACTOR_EN_IG,
    /* 0x277 */ ACTOR_EN_RG,
    /* 0x278 */ ACTOR_EN_OSK,
    /* 0x279 */ ACTOR_EN_STH2,
    /* 0x27A */ ACTOR_EN_YB,
    /* 0x27B */ ACTOR_EN_RZ,
    /* 0x27C */ ACTOR_EN_SCOPECOIN,
    /* 0x27D */ ACTOR_EN_BJT,
    /* 0x27E */ ACTOR_EN_BOMJIMA,
    /* 0x27F */ ACTOR_EN_BOMJIMB,
    /* 0x280 */ ACTOR_EN_BOMBERS,
    /* 0x281 */ ACTOR_EN_BOMBERS2,
    /* 0x282 */ ACTOR_EN_BOMBAL,
    /* 0x283 */ ACTOR_OBJ_MOON_STONE,
    /* 0x284 */ ACTOR_OBJ_MU_PICT,
    /* 0x285 */ ACTOR_BG_IKNINSIDE,
    /* 0x286 */ ACTOR_EFF_ZORABAND,
    /* 0x287 */ ACTOR_OBJ_KEPN_KOYA,
    /* 0x288 */ ACTOR_OBJ_USIYANE,
    /* 0x289 */ ACTOR_EN_NNH,
    /* 0x28A */ ACTOR_OBJ_KZSAKU,
    /* 0x28B */ ACTOR_OBJ_MILK_BIN,
    /* 0x28C */ ACTOR_EN_KITAN,
    /* 0x28D */ ACTOR_BG_ASTR_BOMBWALL,
    /* 0x28E */ ACTOR_BG_IKNIN_SUSCEIL,
    /* 0x28F */ ACTOR_EN_BSB,
    /* 0x290 */ ACTOR_EN_RECEPGIRL,
    /* 0x291 */ ACTOR_EN_THIEFBIRD,
    /* 0x292 */ ACTOR_EN_JGAME_TSN,
    /* 0x293 */ ACTOR_OBJ_JGAME_LIGHT,
    /* 0x294 */ ACTOR_OBJ_YADO,
    /* 0x295 */ ACTOR_DEMO_SYOTEN,
    /* 0x296 */ ACTOR_DEMO_MOONEND,
    /* 0x297 */ ACTOR_BG_LBFSHOT,
    /* 0x298 */ ACTOR_BG_LAST_BWALL,
    /* 0x299 */ ACTOR_EN_AND,
    /* 0x29A */ ACTOR_EN_INVADEPOH_DEMO,
    /* 0x29B */ ACTOR_OBJ_DANPEILIFT,
    /* 0x29C */ ACTOR_EN_FALL2,
    /* 0x29D */ ACTOR_DM_AL,
    /* 0x29E */ ACTOR_DM_AN,
    /* 0x29F */ ACTOR_DM_AH,
    /* 0x2A0 */ ACTOR_DM_NB,
    /* 0x2A1 */ ACTOR_EN_DRS,
    /* 0x2A2 */ ACTOR_EN_ENDING_HERO,
    /* 0x2A3 */ ACTOR_DM_BAL,
    /* 0x2A4 */ ACTOR_EN_PAPER,
    /* 0x2A5 */ ACTOR_EN_HINT_SKB,
    /* 0x2A6 */ ACTOR_DM_TAG,
    /* 0x2A7 */ ACTOR_EN_BH,
    /* 0x2A8 */ ACTOR_EN_ENDING_HERO2,
    /* 0x2A9 */ ACTOR_EN_ENDING_HERO3,
    /* 0x2AA */ ACTOR_EN_ENDING_HERO4,
    /* 0x2AB */ ACTOR_EN_ENDING_HERO5,
    /* 0x2AC */ ACTOR_EN_ENDING_HERO6,
    /* 0x2AD */ ACTOR_DM_GM,
    /* 0x2AE */ ACTOR_OBJ_SWPRIZE,
    /* 0x2AF */ ACTOR_EN_INVISIBLE_RUPPE,
    /* 0x2B0 */ ACTOR_OBJ_ENDING,
    /* 0x2B1 */ ACTOR_EN_RSN,
    /* 0x2B2 */ ACTOR_ID_MAX // originally "ACTOR_DLF_MAX"
} ActorID;

typedef enum {
    /* 0x00 */ SCENE_20SICHITAI2,
    /* 0x01 */ SCENE_UNSET_1,
    /* 0x02 */ SCENE_UNSET_2,
    /* 0x03 */ SCENE_UNSET_3,
    /* 0x04 */ SCENE_UNSET_4,
    /* 0x05 */ SCENE_UNSET_5,
    /* 0x06 */ SCENE_UNSET_6,
    /* 0x07 */ SCENE_KAKUSIANA,
    /* 0x08 */ SCENE_SPOT00,
    /* 0x09 */ SCENE_UNSET_9,
    /* 0x0A */ SCENE_WITCH_SHOP,
    /* 0x0B */ SCENE_LAST_BS,
    /* 0x0C */ SCENE_HAKASHITA,
    /* 0x0D */ SCENE_AYASHIISHOP,
    /* 0x0E */ SCENE_UNSET_E,
    /* 0x0F */ SCENE_UNSET_F,
    /* 0x10 */ SCENE_OMOYA,
    /* 0x11 */ SCENE_BOWLING,
    /* 0x12 */ SCENE_SONCHONOIE,
    /* 0x13 */ SCENE_IKANA,
    /* 0x14 */ SCENE_KAIZOKU,
    /* 0x15 */ SCENE_MILK_BAR,
    /* 0x16 */ SCENE_INISIE_N,
    /* 0x17 */ SCENE_TAKARAYA,
    /* 0x18 */ SCENE_INISIE_R,
    /* 0x19 */ SCENE_OKUJOU,
    /* 0x1A */ SCENE_OPENINGDAN,
    /* 0x1B */ SCENE_MITURIN,
    /* 0x1C */ SCENE_13HUBUKINOMITI,
    /* 0x1D */ SCENE_CASTLE,
    /* 0x1E */ SCENE_DEKUTES,
    /* 0x1F */ SCENE_MITURIN_BS,
    /* 0x20 */ SCENE_SYATEKI_MIZU,
    /* 0x21 */ SCENE_HAKUGIN,
    /* 0x22 */ SCENE_ROMANYMAE,
    /* 0x23 */ SCENE_PIRATE,
    /* 0x24 */ SCENE_SYATEKI_MORI,
    /* 0x25 */ SCENE_SINKAI,
    /* 0x26 */ SCENE_YOUSEI_IZUMI,
    /* 0x27 */ SCENE_KINSTA1,
    /* 0x28 */ SCENE_KINDAN2,
    /* 0x29 */ SCENE_TENMON_DAI,
    /* 0x2A */ SCENE_LAST_DEKU,
    /* 0x2B */ SCENE_22DEKUCITY,
    /* 0x2C */ SCENE_KAJIYA,
    /* 0x2D */ SCENE_00KEIKOKU,
    /* 0x2E */ SCENE_POSTHOUSE,
    /* 0x2F */ SCENE_LABO,
    /* 0x30 */ SCENE_DANPEI2TEST,
    /* 0x31 */ SCENE_UNSET_31,
    /* 0x32 */ SCENE_16GORON_HOUSE,
    /* 0x33 */ SCENE_33ZORACITY,
    /* 0x34 */ SCENE_8ITEMSHOP,
    /* 0x35 */ SCENE_F01,
    /* 0x36 */ SCENE_INISIE_BS,
    /* 0x37 */ SCENE_30GYOSON,
    /* 0x38 */ SCENE_31MISAKI,
    /* 0x39 */ SCENE_TAKARAKUJI,
    /* 0x3A */ SCENE_UNSET_3A,
    /* 0x3B */ SCENE_TORIDE,
    /* 0x3C */ SCENE_FISHERMAN,
    /* 0x3D */ SCENE_GORONSHOP,
    /* 0x3E */ SCENE_DEKU_KING,
    /* 0x3F */ SCENE_LAST_GORON,
    /* 0x40 */ SCENE_24KEMONOMITI,
    /* 0x41 */ SCENE_F01_B,
    /* 0x42 */ SCENE_F01C,
    /* 0x43 */ SCENE_BOTI,
    /* 0x44 */ SCENE_HAKUGIN_BS,
    /* 0x45 */ SCENE_20SICHITAI,
    /* 0x46 */ SCENE_21MITURINMAE,
    /* 0x47 */ SCENE_LAST_ZORA,
    /* 0x48 */ SCENE_11GORONNOSATO2,
    /* 0x49 */ SCENE_SEA,
    /* 0x4A */ SCENE_35TAKI,
    /* 0x4B */ SCENE_REDEAD,
    /* 0x4C */ SCENE_BANDROOM,
    /* 0x4D */ SCENE_11GORONNOSATO,
    /* 0x4E */ SCENE_GORON_HAKA,
    /* 0x4F */ SCENE_SECOM,
    /* 0x50 */ SCENE_10YUKIYAMANOMURA,
    /* 0x51 */ SCENE_TOUGITES,
    /* 0x52 */ SCENE_DANPEI,
    /* 0x53 */ SCENE_IKANAMAE,
    /* 0x54 */ SCENE_DOUJOU,
    /* 0x55 */ SCENE_MUSICHOUSE,
    /* 0x56 */ SCENE_IKNINSIDE,
    /* 0x57 */ SCENE_MAP_SHOP,
    /* 0x58 */ SCENE_F40,
    /* 0x59 */ SCENE_F41,
    /* 0x5A */ SCENE_10YUKIYAMANOMURA2,
    /* 0x5B */ SCENE_14YUKIDAMANOMITI,
    /* 0x5C */ SCENE_12HAKUGINMAE,
    /* 0x5D */ SCENE_17SETUGEN,
    /* 0x5E */ SCENE_17SETUGEN2,
    /* 0x5F */ SCENE_SEA_BS,
    /* 0x60 */ SCENE_RANDOM,
    /* 0x61 */ SCENE_YADOYA,
    /* 0x62 */ SCENE_KONPEKI_ENT,
    /* 0x63 */ SCENE_INSIDETOWER,
    /* 0x64 */ SCENE_26SARUNOMORI,
    /* 0x65 */ SCENE_LOST_WOODS,
    /* 0x66 */ SCENE_LAST_LINK,
    /* 0x67 */ SCENE_SOUGEN,
    /* 0x68 */ SCENE_BOMYA,
    /* 0x69 */ SCENE_KYOJINNOMA,
    /* 0x6A */ SCENE_KOEPONARACE,
    /* 0x6B */ SCENE_GORONRACE,
    /* 0x6C */ SCENE_TOWN,
    /* 0x6D */ SCENE_ICHIBA,
    /* 0x6E */ SCENE_BACKTOWN,
    /* 0x6F */ SCENE_CLOCKTOWER,
    /* 0x70 */ SCENE_ALLEY
} SceneID;

typedef enum {
    /* 0x000 */ OBJECT_UNSET_0,
    /* 0x001 */ GAMEPLAY_KEEP,
    /* 0x002 */ GAMEPLAY_FIELD_KEEP,
    /* 0x003 */ GAMEPLAY_DANGEON_KEEP,
    /* 0x004 */ OBJECT_NB,
    /* 0x005 */ OBJECT_OKUTA,
    /* 0x006 */ OBJECT_CROW,
    /* 0x007 */ OBJECT_AH,
    /* 0x008 */ OBJECT_DY_OBJ,
    /* 0x009 */ OBJECT_WALLMASTER,
    /* 0x00A */ OBJECT_DODONGO,
    /* 0x00B */ OBJECT_FIREFLY,
    /* 0x00C */ OBJECT_BOX,
    /* 0x00D */ OBJECT_AL,
    /* 0x00E */ OBJECT_BUBBLE,
    /* 0x00F */ OBJECT_NIW,
    /* 0x010 */ OBJECT_LINK_BOY,
    /* 0x011 */ OBJECT_LINK_CHILD,
    /* 0x012 */ OBJECT_TITE,
    /* 0x013 */ OBJECT_TAB,
    /* 0x014 */ OBJECT_PH,
    /* 0x015 */ OBJECT_AND,
    /* 0x016 */ OBJECT_MSMO,
    /* 0x017 */ OBJECT_DINOFOS,
    /* 0x018 */ OBJECT_DRS,
    /* 0x019 */ OBJECT_ZL1,
    /* 0x01A */ OBJECT_AN4,
    /* 0x01B */ OBJECT_UNSET_1B,
    /* 0x01C */ OBJECT_TEST3,
    /* 0x01D */ OBJECT_FAMOS,
    /* 0x01E */ OBJECT_UNSET_1E,
    /* 0x01F */ OBJECT_UNSET_1F,
    /* 0x020 */ OBJECT_ST,
    /* 0x021 */ OBJECT_UNSET_21,
    /* 0x022 */ OBJECT_THIEFBIRD,
    /* 0x023 */ OBJECT_UNSET_23,
    /* 0x024 */ OBJECT_UNSET_24,
    /* 0x025 */ OBJECT_UNSET_25,
    /* 0x026 */ OBJECT_UNSET_26,
    /* 0x027 */ OBJECT_UNSET_27,
    /* 0x028 */ OBJECT_UNSET_28,
    /* 0x029 */ OBJECT_UNSET_29,
    /* 0x02A */ OBJECT_BOMBF,
    /* 0x02B */ OBJECT_UNSET_2B,
    /* 0x02C */ OBJECT_UNSET_2C,
    /* 0x02D */ OBJECT_UNSET_2D,
    /* 0x02E */ OBJECT_UNSET_2E,
    /* 0x02F */ OBJECT_UNSET_2F,
    /* 0x030 */ OBJECT_AM,
    /* 0x031 */ OBJECT_DEKUBABA,
    /* 0x032 */ OBJECT_UNSET_32,
    /* 0x033 */ OBJECT_UNSET_33,
    /* 0x034 */ OBJECT_UNSET_34,
    /* 0x035 */ OBJECT_UNSET_35,
    /* 0x036 */ OBJECT_UNSET_36,
    /* 0x037 */ OBJECT_UNSET_37,
    /* 0x038 */ OBJECT_UNSET_38,
    /* 0x039 */ OBJECT_UNSET_39,
    /* 0x03A */ OBJECT_UNSET_3A,
    /* 0x03B */ OBJECT_UNSET_3B,
    /* 0x03C */ OBJECT_UNSET_3C,
    /* 0x03D */ OBJECT_UNSET_3D,
    /* 0x03E */ OBJECT_WARP1,
    /* 0x03F */ OBJECT_B_HEART,
    /* 0x040 */ OBJECT_DEKUNUTS,
    /* 0x041 */ OBJECT_UNSET_41,
    /* 0x042 */ OBJECT_UNSET_42,
    /* 0x043 */ OBJECT_UNSET_43,
    /* 0x044 */ OBJECT_UNSET_44,
    /* 0x045 */ OBJECT_UNSET_45,
    /* 0x046 */ OBJECT_UNSET_46,
    /* 0x047 */ OBJECT_UNSET_47,
    /* 0x048 */ OBJECT_UNSET_48,
    /* 0x049 */ OBJECT_UNSET_49,
    /* 0x04A */ OBJECT_UNSET_4A,
    /* 0x04B */ OBJECT_UNSET_4B,
    /* 0x04C */ OBJECT_UNSET_4C,
    /* 0x04D */ OBJECT_UNSET_4D,
    /* 0x04E */ OBJECT_UNSET_4E,
    /* 0x04F */ OBJECT_UNSET_4F,
    /* 0x050 */ OBJECT_UNSET_50,
    /* 0x051 */ OBJECT_BB,
    /* 0x052 */ OBJECT_DEATH,
    /* 0x053 */ OBJECT_UNSET_53,
    /* 0x054 */ OBJECT_UNSET_54,
    /* 0x055 */ OBJECT_UNSET_55,
    /* 0x056 */ OBJECT_UNSET_56,
    /* 0x057 */ OBJECT_UNSET_57,
    /* 0x058 */ OBJECT_UNSET_58,
    /* 0x059 */ OBJECT_UNSET_59,
    /* 0x05A */ OBJECT_UNSET_5A,
    /* 0x05B */ OBJECT_UNSET_5B,
    /* 0x05C */ OBJECT_F40_OBJ,
    /* 0x05D */ OBJECT_PO_COMPOSER,
    /* 0x05E */ OBJECT_UNSET_5E,
    /* 0x05F */ OBJECT_HATA,
    /* 0x060 */ OBJECT_UNSET_60,
    /* 0x061 */ OBJECT_WOOD02,
    /* 0x062 */ OBJECT_UNSET_62,
    /* 0x063 */ OBJECT_UNSET_63,
    /* 0x064 */ OBJECT_TRAP,
    /* 0x065 */ OBJECT_UNSET_65,
    /* 0x066 */ OBJECT_UNSET_66,
    /* 0x067 */ OBJECT_UNSET_67,
    /* 0x068 */ OBJECT_UNSET_68,
    /* 0x069 */ OBJECT_UNSET_69,
    /* 0x06A */ OBJECT_VM,
    /* 0x06B */ OBJECT_UNSET_6B,
    /* 0x06C */ OBJECT_UNSET_6C,
    /* 0x06D */ OBJECT_UNSET_6D,
    /* 0x06E */ OBJECT_UNSET_6E,
    /* 0x06F */ OBJECT_UNSET_6F,
    /* 0x070 */ OBJECT_EFC_STAR_FIELD,
    /* 0x071 */ OBJECT_UNSET_71,
    /* 0x072 */ OBJECT_UNSET_72,
    /* 0x073 */ OBJECT_UNSET_73,
    /* 0x074 */ OBJECT_UNSET_74,
    /* 0x075 */ OBJECT_RD,
    /* 0x076 */ OBJECT_YUKIMURA_OBJ,
    /* 0x077 */ OBJECT_HEAVY_OBJECT,
    /* 0x078 */ OBJECT_UNSET_78,
    /* 0x079 */ OBJECT_UNSET_79,
    /* 0x07A */ OBJECT_UNSET_7A,
    /* 0x07B */ OBJECT_UNSET_7B,
    /* 0x07C */ OBJECT_UNSET_7C,
    /* 0x07D */ OBJECT_HORSE_LINK_CHILD,
    /* 0x07E */ OBJECT_UNSET_7E,
    /* 0x07F */ OBJECT_UNSET_7F,
    /* 0x080 */ OBJECT_SYOKUDAI,
    /* 0x081 */ OBJECT_UNSET_81,
    /* 0x082 */ OBJECT_UNSET_82,
    /* 0x083 */ OBJECT_UNSET_83,
    /* 0x084 */ OBJECT_EFC_TW,
    /* 0x085 */ OBJECT_UNSET_85,
    /* 0x086 */ OBJECT_GI_KEY,
    /* 0x087 */ OBJECT_MIR_RAY,
    /* 0x088 */ OBJECT_CTOWER_ROT,
    /* 0x089 */ OBJECT_UNSET_89,
    /* 0x08A */ OBJECT_BDOOR,
    /* 0x08B */ OBJECT_UNSET_8B,
    /* 0x08C */ OBJECT_UNSET_8C,
    /* 0x08D */ OBJECT_UNSET_8D,
    /* 0x08E */ OBJECT_SB,
    /* 0x08F */ OBJECT_GI_MELODY,
    /* 0x090 */ OBJECT_GI_HEART,
    /* 0x091 */ OBJECT_GI_COMPASS,
    /* 0x092 */ OBJECT_GI_BOSSKEY,
    /* 0x093 */ OBJECT_UNSET_93,
    /* 0x094 */ OBJECT_GI_NUTS,
    /* 0x095 */ OBJECT_UNSET_95,
    /* 0x096 */ OBJECT_GI_HEARTS,
    /* 0x097 */ OBJECT_GI_ARROWCASE,
    /* 0x098 */ OBJECT_GI_BOMBPOUCH,
    /* 0x099 */ OBJECT_IN,
    /* 0x09A */ OBJECT_UNSET_9A,
    /* 0x09B */ OBJECT_UNSET_9B,
    /* 0x09C */ OBJECT_UNSET_9C,
    /* 0x09D */ OBJECT_OS_ANIME,
    /* 0x09E */ OBJECT_GI_BOTTLE,
    /* 0x09F */ OBJECT_GI_STICK,
    /* 0x0A0 */ OBJECT_GI_MAP,
    /* 0x0A1 */ OBJECT_OF1D_MAP,
    /* 0x0A2 */ OBJECT_RU2,
    /* 0x0A3 */ OBJECT_UNSET_A3,
    /* 0x0A4 */ OBJECT_GI_MAGICPOT,
    /* 0x0A5 */ OBJECT_GI_BOMB_1,
    /* 0x0A6 */ OBJECT_UNSET_A6,
    /* 0x0A7 */ OBJECT_MA2,
    /* 0x0A8 */ OBJECT_GI_PURSE,
    /* 0x0A9 */ OBJECT_UNSET_A9,
    /* 0x0AA */ OBJECT_UNSET_AA,
    /* 0x0AB */ OBJECT_RR,
    /* 0x0AC */ OBJECT_UNSET_AC,
    /* 0x0AD */ OBJECT_UNSET_AD,
    /* 0x0AE */ OBJECT_UNSET_AE,
    /* 0x0AF */ OBJECT_GI_ARROW,
    /* 0x0B0 */ OBJECT_GI_BOMB_2,
    /* 0x0B1 */ OBJECT_UNSET_B1,
    /* 0x0B2 */ OBJECT_UNSET_B2,
    /* 0x0B3 */ OBJECT_GI_SHIELD_2,
    /* 0x0B4 */ OBJECT_GI_HOOKSHOT,
    /* 0x0B5 */ OBJECT_GI_OCARINA,
    /* 0x0B6 */ OBJECT_GI_MILK,
    /* 0x0B7 */ OBJECT_MA1,
    /* 0x0B8 */ OBJECT_UNSET_B8,
    /* 0x0B9 */ OBJECT_UNSET_B9,
    /* 0x0BA */ OBJECT_UNSET_BA,
    /* 0x0BB */ OBJECT_NY,
    /* 0x0BC */ OBJECT_FR,
    /* 0x0BD */ OBJECT_UNSET_BD,
    /* 0x0BE */ OBJECT_UNSET_BE,
    /* 0x0BF */ OBJECT_GI_BOW,
    /* 0x0C0 */ OBJECT_GI_GLASSES,
    /* 0x0C1 */ OBJECT_GI_LIQUID,
    /* 0x0C2 */ OBJECT_ANI,
    /* 0x0C3 */ OBJECT_GI_SHIELD_3,
    /* 0x0C4 */ OBJECT_UNSET_C4,
    /* 0x0C5 */ OBJECT_UNSET_C5,
    /* 0x0C6 */ OBJECT_GI_BEAN,
    /* 0x0C7 */ OBJECT_GI_FISH,
    /* 0x0C8 */ OBJECT_UNSET_C8,
    /* 0x0C9 */ OBJECT_UNSET_C9,
    /* 0x0CA */ OBJECT_UNSET_CA,
    /* 0x0CB */ OBJECT_GI_LONGSWORD,
    /* 0x0CC */ OBJECT_UNSET_CC,
    /* 0x0CD */ OBJECT_UNSET_CD,
    /* 0x0CE */ OBJECT_UNSET_CE,
    /* 0x0CF */ OBJECT_UNSET_CF,
    /* 0x0D0 */ OBJECT_ZO,
    /* 0x0D1 */ OBJECT_UNSET_D1,
    /* 0x0D2 */ OBJECT_UMAJUMP,
    /* 0x0D3 */ OBJECT_UNSET_D3,
    /* 0x0D4 */ OBJECT_UNSET_D4,
    /* 0x0D5 */ OBJECT_MASTERGOLON,
    /* 0x0D6 */ OBJECT_MASTERZOORA,
    /* 0x0D7 */ OBJECT_AOB,
    /* 0x0D8 */ OBJECT_IK,
    /* 0x0D9 */ OBJECT_AHG,
    /* 0x0DA */ OBJECT_CNE,
    /* 0x0DB */ OBJECT_UNSET_DB,
    /* 0x0DC */ OBJECT_UNSET_DC,
    /* 0x0DD */ OBJECT_AN3,
    /* 0x0DE */ OBJECT_BJI,
    /* 0x0DF */ OBJECT_BBA,
    /* 0x0E0 */ OBJECT_AN2,
    /* 0x0E1 */ OBJECT_UNSET_E1,
    /* 0x0E2 */ OBJECT_AN1,
    /* 0x0E3 */ OBJECT_BOJ,
    /* 0x0E4 */ OBJECT_FZ,
    /* 0x0E5 */ OBJECT_BOB,
    /* 0x0E6 */ OBJECT_GE1,
    /* 0x0E7 */ OBJECT_YABUSAME_POINT,
    /* 0x0E8 */ OBJECT_UNSET_E8,
    /* 0x0E9 */ OBJECT_UNSET_E9,
    /* 0x0EA */ OBJECT_UNSET_EA,
    /* 0x0EB */ OBJECT_UNSET_EB,
    /* 0x0EC */ OBJECT_D_HSBLOCK,
    /* 0x0ED */ OBJECT_D_LIFT,
    /* 0x0EE */ OBJECT_MAMENOKI,
    /* 0x0EF */ OBJECT_GOROIWA,
    /* 0x0F0 */ OBJECT_TORYO,
    /* 0x0F1 */ OBJECT_DAIKU,
    /* 0x0F2 */ OBJECT_NWC,
    /* 0x0F3 */ OBJECT_GM,
    /* 0x0F4 */ OBJECT_MS,
    /* 0x0F5 */ OBJECT_HS,
    /* 0x0F6 */ OBJECT_UNSET_F6,
    /* 0x0F7 */ OBJECT_LIGHTSWITCH,
    /* 0x0F8 */ OBJECT_KUSA,
    /* 0x0F9 */ OBJECT_TSUBO,
    /* 0x0FA */ OBJECT_UNSET_FA,
    /* 0x0FB */ OBJECT_UNSET_FB,
    /* 0x0FC */ OBJECT_KANBAN,
    /* 0x0FD */ OBJECT_OWL,
    /* 0x0FE */ OBJECT_MK,
    /* 0x0FF */ OBJECT_FU,
    /* 0x100 */ OBJECT_GI_KI_TAN_MASK,
    /* 0x101 */ OBJECT_UNSET_101,
    /* 0x102 */ OBJECT_GI_MASK18,
    /* 0x103 */ OBJECT_GI_RABIT_MASK,
    /* 0x104 */ OBJECT_GI_TRUTH_MASK,
    /* 0x105 */ OBJECT_UNSET_105,
    /* 0x106 */ OBJECT_STREAM,
    /* 0x107 */ OBJECT_MM,
    /* 0x108 */ OBJECT_UNSET_108,
    /* 0x109 */ OBJECT_UNSET_109,
    /* 0x10A */ OBJECT_UNSET_10A,
    /* 0x10B */ OBJECT_UNSET_10B,
    /* 0x10C */ OBJECT_UNSET_10C,
    /* 0x10D */ OBJECT_UNSET_10D,
    /* 0x10E */ OBJECT_UNSET_10E,
    /* 0x10F */ OBJECT_JS,
    /* 0x110 */ OBJECT_CS,
    /* 0x111 */ OBJECT_UNSET_111,
    /* 0x112 */ OBJECT_UNSET_112,
    /* 0x113 */ OBJECT_GI_SOLDOUT,
    /* 0x114 */ OBJECT_UNSET_114,
    /* 0x115 */ OBJECT_MAG,
    /* 0x116 */ OBJECT_UNSET_116,
    /* 0x117 */ OBJECT_UNSET_117,
    /* 0x118 */ OBJECT_UNSET_118,
    /* 0x119 */ OBJECT_GI_GOLONMASK,
    /* 0x11A */ OBJECT_GI_ZORAMASK,
    /* 0x11B */ OBJECT_UNSET_11B,
    /* 0x11C */ OBJECT_UNSET_11C,
    /* 0x11D */ OBJECT_KA,
    /* 0x11E */ OBJECT_UNSET_11E,
    /* 0x11F */ OBJECT_ZG,
    /* 0x120 */ OBJECT_UNSET_120,
    /* 0x121 */ OBJECT_GI_M_ARROW,
    /* 0x122 */ OBJECT_DS2,
    /* 0x123 */ OBJECT_UNSET_123,
    /* 0x124 */ OBJECT_FISH,
    /* 0x125 */ OBJECT_GI_SUTARU,
    /* 0x126 */ OBJECT_UNSET_126,
    /* 0x127 */ OBJECT_SSH,
    /* 0x128 */ OBJECT_BIGSLIME,
    /* 0x129 */ OBJECT_BG,
    /* 0x12A */ OBJECT_BOMBIWA,
    /* 0x12B */ OBJECT_HINTNUTS,
    /* 0x12C */ OBJECT_RS,
    /* 0x12D */ OBJECT_UNSET_12D,
    /* 0x12E */ OBJECT_GLA,
    /* 0x12F */ OBJECT_UNSET_12F,
    /* 0x130 */ OBJECT_GELDB,
    /* 0x131 */ OBJECT_UNSET_131,
    /* 0x132 */ OBJECT_DOG,
    /* 0x133 */ OBJECT_KIBAKO2,
    /* 0x134 */ OBJECT_DNS,
    /* 0x135 */ OBJECT_DNK,
    /* 0x136 */ OBJECT_UNSET_136,
    /* 0x137 */ OBJECT_GI_INSECT,
    /* 0x138 */ OBJECT_UNSET_138,
    /* 0x139 */ OBJECT_GI_GHOST,
    /* 0x13A */ OBJECT_GI_SOUL,
    /* 0x13B */ OBJECT_UNSET_13B,
    /* 0x13C */ OBJECT_UNSET_13C,
    /* 0x13D */ OBJECT_UNSET_13D,
    /* 0x13E */ OBJECT_UNSET_13E,
    /* 0x13F */ OBJECT_GI_RUPY,
    /* 0x140 */ OBJECT_MU,
    /* 0x141 */ OBJECT_WF,
    /* 0x142 */ OBJECT_SKB,
    /* 0x143 */ OBJECT_GS,
    /* 0x144 */ OBJECT_PS,
    /* 0x145 */ OBJECT_OMOYA_OBJ,
    /* 0x146 */ OBJECT_COW,
    /* 0x147 */ OBJECT_UNSET_147,
    /* 0x148 */ OBJECT_GI_SWORD_1,
    /* 0x149 */ OBJECT_UNSET_149,
    /* 0x14A */ OBJECT_UNSET_14A,
    /* 0x14B */ OBJECT_ZL4,
    /* 0x14C */ OBJECT_LINK_GORON,
    /* 0x14D */ OBJECT_LINK_ZORA,
    /* 0x14E */ OBJECT_GRASSHOPPER,
    /* 0x14F */ OBJECT_BOYO,
    /* 0x150 */ OBJECT_UNSET_150,
    /* 0x151 */ OBJECT_UNSET_151,
    /* 0x152 */ OBJECT_UNSET_152,
    /* 0x153 */ OBJECT_FWALL,
    /* 0x154 */ OBJECT_LINK_NUTS,
    /* 0x155 */ OBJECT_JSO,
    /* 0x156 */ OBJECT_KNIGHT,
    /* 0x157 */ OBJECT_ICICLE,
    /* 0x158 */ OBJECT_SPDWEB,
    /* 0x159 */ OBJECT_UNSET_159,
    /* 0x15A */ OBJECT_BOSS01,
    /* 0x15B */ OBJECT_BOSS02,
    /* 0x15C */ OBJECT_BOSS03,
    /* 0x15D */ OBJECT_BOSS04,
    /* 0x15E */ OBJECT_BOSS05,
    /* 0x15F */ OBJECT_BOSS06,
    /* 0x160 */ OBJECT_BOSS07,
    /* 0x161 */ OBJECT_RAF,
    /* 0x162 */ OBJECT_FUNEN,
    /* 0x163 */ OBJECT_RAILLIFT,
    /* 0x164 */ OBJECT_NUMA_OBJ,
    /* 0x165 */ OBJECT_FLOWERPOT,
    /* 0x166 */ OBJECT_SPINYROLL,
    /* 0x167 */ OBJECT_ICE_BLOCK,
    /* 0x168 */ OBJECT_UNSET_168,
    /* 0x169 */ OBJECT_KEIKOKU_DEMO,
    /* 0x16A */ OBJECT_SLIME,
    /* 0x16B */ OBJECT_PR,
    /* 0x16C */ OBJECT_F52_OBJ,
    /* 0x16D */ OBJECT_F53_OBJ,
    /* 0x16E */ OBJECT_UNSET_16E,
    /* 0x16F */ OBJECT_KIBAKO,
    /* 0x170 */ OBJECT_SEK,
    /* 0x171 */ OBJECT_GMO,
    /* 0x172 */ OBJECT_BAT,
    /* 0x173 */ OBJECT_SEKIHIL,
    /* 0x174 */ OBJECT_SEKIHIG,
    /* 0x175 */ OBJECT_SEKIHIN,
    /* 0x176 */ OBJECT_SEKIHIZ,
    /* 0x177 */ OBJECT_UNSET_177,
    /* 0x178 */ OBJECT_WIZ,
    /* 0x179 */ OBJECT_LADDER,
    /* 0x17A */ OBJECT_MKK,
    /* 0x17B */ OBJECT_UNSET_17B,
    /* 0x17C */ OBJECT_UNSET_17C,
    /* 0x17D */ OBJECT_UNSET_17D,
    /* 0x17E */ OBJECT_KEIKOKU_OBJ,
    /* 0x17F */ OBJECT_SICHITAI_OBJ,
    /* 0x180 */ OBJECT_DEKUCITY_ANA_OBJ,
    /* 0x181 */ OBJECT_RAT,
    /* 0x182 */ OBJECT_WATER_EFFECT,
    /* 0x183 */ OBJECT_UNSET_183,
    /* 0x184 */ OBJECT_DBLUE_OBJECT,
    /* 0x185 */ OBJECT_BAL,
    /* 0x186 */ OBJECT_WARP_UZU,
    /* 0x187 */ OBJECT_DRIFTICE,
    /* 0x188 */ OBJECT_FALL,
    /* 0x189 */ OBJECT_HANAREYAMA_OBJ,
    /* 0x18A */ OBJECT_CRACE_OBJECT,
    /* 0x18B */ OBJECT_DNQ,
    /* 0x18C */ OBJECT_OBJECT_UNSET_TOKEIDAI,
    /* 0x18D */ OBJECT_EG,
    /* 0x18E */ OBJECT_TRU,
    /* 0x18F */ OBJECT_TRT,
    /* 0x190 */ OBJECT_HAKUGIN_OBJ,
    /* 0x191 */ OBJECT_HORSE_GAME_CHECK,
    /* 0x192 */ OBJECT_STK,
    /* 0x193 */ OBJECT_UNSET_193,
    /* 0x194 */ OBJECT_UNSET_194,
    /* 0x195 */ OBJECT_MNK,
    /* 0x196 */ OBJECT_GI_BOTTLE_RED,
    /* 0x197 */ OBJECT_TOKEI_TOBIRA,
    /* 0x198 */ OBJECT_AZ,
    /* 0x199 */ OBJECT_TWIG,
    /* 0x19A */ OBJECT_DEKUCITY_OBJ,
    /* 0x19B */ OBJECT_PO_FUSEN,
    /* 0x19C */ OBJECT_RACETSUBO,
    /* 0x19D */ OBJECT_HA,
    /* 0x19E */ OBJECT_BIGOKUTA,
    /* 0x19F */ OBJECT_OPEN_OBJ,
    /* 0x1A0 */ OBJECT_FU_KAITEN,
    /* 0x1A1 */ OBJECT_FU_MATO,
    /* 0x1A2 */ OBJECT_MTORIDE,
    /* 0x1A3 */ OBJECT_OSN,
    /* 0x1A4 */ OBJECT_TOKEI_STEP,
    /* 0x1A5 */ OBJECT_LOTUS,
    /* 0x1A6 */ OBJECT_TL,
    /* 0x1A7 */ OBJECT_DKJAIL_OBJ,
    /* 0x1A8 */ OBJECT_VISIBLOCK,
    /* 0x1A9 */ OBJECT_TSN,
    /* 0x1AA */ OBJECT_DS2N,
    /* 0x1AB */ OBJECT_FSN,
    /* 0x1AC */ OBJECT_SHN,
    /* 0x1AD */ OBJECT_BIGICICLE,
    /* 0x1AE */ OBJECT_GI_BOTTLE_15,
    /* 0x1AF */ OBJECT_TK,
    /* 0x1B0 */ OBJECT_MARKET_OBJ,
    /* 0x1B1 */ OBJECT_GI_RESERVE00,
    /* 0x1B2 */ OBJECT_GI_RESERVE01,
    /* 0x1B3 */ OBJECT_LIGHTBLOCK,
    /* 0x1B4 */ OBJECT_TAKARAYA_OBJECTS,
    /* 0x1B5 */ OBJECT_WDHAND,
    /* 0x1B6 */ OBJECT_SDN,
    /* 0x1B7 */ OBJECT_SNOWWD,
    /* 0x1B8 */ OBJECT_GIANT,
    /* 0x1B9 */ OBJECT_COMB,
    /* 0x1BA */ OBJECT_HANA,
    /* 0x1BB */ OBJECT_BOSS_HAKUGIN,
    /* 0x1BC */ OBJECT_MEGANEANA_OBJ,
    /* 0x1BD */ OBJECT_GI_NUTSMASK,
    /* 0x1BE */ OBJECT_STK2,
    /* 0x1BF */ OBJECT_SPOT11_OBJ,
    /* 0x1C0 */ OBJECT_DANPEI_OBJECT,
    /* 0x1C1 */ OBJECT_DHOUSE,
    /* 0x1C2 */ OBJECT_HAKAISI,
    /* 0x1C3 */ OBJECT_PO,
    /* 0x1C4 */ OBJECT_SNOWMAN,
    /* 0x1C5 */ OBJECT_PO_SISTERS,
    /* 0x1C6 */ OBJECT_PP,
    /* 0x1C7 */ OBJECT_GORONSWITCH,
    /* 0x1C8 */ OBJECT_DELF,
    /* 0x1C9 */ OBJECT_BOTIHASIRA,
    /* 0x1CA */ OBJECT_GI_BIGBOMB,
    /* 0x1CB */ OBJECT_PST,
    /* 0x1CC */ OBJECT_BSMASK,
    /* 0x1CD */ OBJECT_SPIDERTENT,
    /* 0x1CE */ OBJECT_ZORAEGG,
    /* 0x1CF */ OBJECT_KBT,
    /* 0x1D0 */ OBJECT_GG,
    /* 0x1D1 */ OBJECT_MARUTA,
    /* 0x1D2 */ OBJECT_GHAKA,
    /* 0x1D3 */ OBJECT_OYU,
    /* 0x1D4 */ OBJECT_DNP,
    /* 0x1D5 */ OBJECT_DAI,
    /* 0x1D6 */ OBJECT_KGY,
    /* 0x1D7 */ OBJECT_FB,
    /* 0x1D8 */ OBJECT_TAISOU,
    /* 0x1D9 */ OBJECT_MASK_BU_SAN,
    /* 0x1DA */ OBJECT_MASK_KI_TAN,
    /* 0x1DB */ OBJECT_MASK_RABIT,
    /* 0x1DC */ OBJECT_MASK_SKJ,
    /* 0x1DD */ OBJECT_MASK_BAKURETU,
    /* 0x1DE */ OBJECT_MASK_TRUTH,
    /* 0x1DF */ OBJECT_GK,
    /* 0x1E0 */ OBJECT_HAKA_OBJ,
    /* 0x1E1 */ OBJECT_MASK_GORON,
    /* 0x1E2 */ OBJECT_MASK_ZORA,
    /* 0x1E3 */ OBJECT_MASK_NUTS,
    /* 0x1E4 */ OBJECT_MASK_BOY,
    /* 0x1E5 */ OBJECT_DNT,
    /* 0x1E6 */ OBJECT_YUKIYAMA,
    /* 0x1E7 */ OBJECT_ICEFLOE,
    /* 0x1E8 */ OBJECT_GI_GOLD_DUST,
    /* 0x1E9 */ OBJECT_GI_BOTTLE_16,
    /* 0x1EA */ OBJECT_GI_BOTTLE_22,
    /* 0x1EB */ OBJECT_BEE,
    /* 0x1EC */ OBJECT_OT,
    /* 0x1ED */ OBJECT_UTUBO,
    /* 0x1EE */ OBJECT_DORA,
    /* 0x1EF */ OBJECT_GI_LOACH,
    /* 0x1F0 */ OBJECT_GI_SEAHORSE,
    /* 0x1F1 */ OBJECT_BIGPO,
    /* 0x1F2 */ OBJECT_HARIKO,
    /* 0x1F3 */ OBJECT_DNO,
    /* 0x1F4 */ OBJECT_SINKAI_KABE,
    /* 0x1F5 */ OBJECT_KIN2_OBJ,
    /* 0x1F6 */ OBJECT_ISHI,
    /* 0x1F7 */ OBJECT_HAKUGIN_DEMO,
    /* 0x1F8 */ OBJECT_JG,
    /* 0x1F9 */ OBJECT_GI_SWORD_2,
    /* 0x1FA */ OBJECT_GI_SWORD_3,
    /* 0x1FB */ OBJECT_GI_SWORD_4,
    /* 0x1FC */ OBJECT_UM,
    /* 0x1FD */ OBJECT_MASK_GIBUDO,
    /* 0x1FE */ OBJECT_MASK_JSON,
    /* 0x1FF */ OBJECT_MASK_KERFAY,
    /* 0x200 */ OBJECT_MASK_BIGELF,
    /* 0x201 */ OBJECT_RB,
    /* 0x202 */ OBJECT_MBAR_OBJ,
    /* 0x203 */ OBJECT_IKANA_OBJ,
    /* 0x204 */ OBJECT_KZ,
    /* 0x205 */ OBJECT_TOKEI_TURRET,
    /* 0x206 */ OBJECT_ZOG,
    /* 0x207 */ OBJECT_ROTLIFT,
    /* 0x208 */ OBJECT_POSTHOUSE_OBJ,
    /* 0x209 */ OBJECT_GI_MASK09,
    /* 0x20A */ OBJECT_GI_MASK14,
    /* 0x20B */ OBJECT_GI_MASK15,
    /* 0x20C */ OBJECT_INIBS_OBJECT,
    /* 0x20D */ OBJECT_TREE,
    /* 0x20E */ OBJECT_KAIZOKU_OBJ,
    /* 0x20F */ OBJECT_GI_RESERVE_B_00,
    /* 0x210 */ OBJECT_GI_RESERVE_C_00,
    /* 0x211 */ OBJECT_ZOB,
    /* 0x212 */ OBJECT_MILKBAR,
    /* 0x213 */ OBJECT_DMASK,
    /* 0x214 */ OBJECT_MASK_KYOJIN,
    /* 0x215 */ OBJECT_GI_RESERVE_C_01,
    /* 0x216 */ OBJECT_ZOD,
    /* 0x217 */ OBJECT_KUMO30,
    /* 0x218 */ OBJECT_OBJECT_UNSET_YASI,
    /* 0x219 */ OBJECT_MASK_ROMERNY,
    /* 0x21A */ OBJECT_TANRON1,
    /* 0x21B */ OBJECT_TANRON2,
    /* 0x21C */ OBJECT_TANRON3,
    /* 0x21D */ OBJECT_GI_MAGICMUSHROOM,
    /* 0x21E */ OBJECT_OBJECT_UNSET_CHAN,
    /* 0x21F */ OBJECT_GI_MASK10,
    /* 0x220 */ OBJECT_ZOS,
    /* 0x221 */ OBJECT_MASK_POSTHAT,
    /* 0x222 */ OBJECT_F40_SWITCH,
    /* 0x223 */ OBJECT_LODMOON,
    /* 0x224 */ OBJECT_TRO,
    /* 0x225 */ OBJECT_GI_MASK12,
    /* 0x226 */ OBJECT_GI_MASK23,
    /* 0x227 */ OBJECT_GI_BOTTLE_21,
    /* 0x228 */ OBJECT_GI_CAMERA,
    /* 0x229 */ OBJECT_KAMEJIMA,
    /* 0x22A */ OBJECT_HARFGIBUD,
    /* 0x22B */ OBJECT_ZOV,
    /* 0x22C */ OBJECT_HGDOOR,
    /* 0x22D */ OBJECT_UNSET_22D,
    /* 0x22E */ OBJECT_UNSET_22E,
    /* 0x22F */ OBJECT_UNSET_22F,
    /* 0x230 */ OBJECT_DOR01,
    /* 0x231 */ OBJECT_DOR02,
    /* 0x232 */ OBJECT_DOR03,
    /* 0x233 */ OBJECT_DOR04,
    /* 0x234 */ OBJECT_LAST_OBJ,
    /* 0x235 */ OBJECT_REDEAD_OBJ,
    /* 0x236 */ OBJECT_IKNINSIDE_OBJ,
    /* 0x237 */ OBJECT_IKNV_OBJ,
    /* 0x238 */ OBJECT_PAMERA,
    /* 0x239 */ OBJECT_HSSTUMP,
    /* 0x23A */ OBJECT_ZM,
    /* 0x23B */ OBJECT_BIG_FWALL,
    /* 0x23C */ OBJECT_SECOM_OBJ,
    /* 0x23D */ OBJECT_HUNSUI,
    /* 0x23E */ OBJECT_UCH,
    /* 0x23F */ OBJECT_TANRON4,
    /* 0x240 */ OBJECT_TANRON5,
    /* 0x241 */ OBJECT_DT,
    /* 0x242 */ OBJECT_GI_MASK03,
    /* 0x243 */ OBJECT_CHA,
    /* 0x244 */ OBJECT_OBJECT_UNSET_DINNER,
    /* 0x245 */ OBJECT_GI_RESERVE_B_01,
    /* 0x246 */ OBJECT_LASTDAY,
    /* 0x247 */ OBJECT_BAI,
    /* 0x248 */ OBJECT_IN2,
    /* 0x249 */ OBJECT_IKN_DEMO,
    /* 0x24A */ OBJECT_YB,
    /* 0x24B */ OBJECT_RZ,
    /* 0x24C */ OBJECT_MASK_ZACHO,
    /* 0x24D */ OBJECT_GI_FIELDMAP,
    /* 0x24E */ OBJECT_MASK_STONE,
    /* 0x24F */ OBJECT_BJT,
    /* 0x250 */ OBJECT_TARU,
    /* 0x251 */ OBJECT_MOONSTON,
    /* 0x252 */ OBJECT_MASK_BREE,
    /* 0x253 */ OBJECT_GI_SCHEDULE,
    /* 0x254 */ OBJECT_GI_STONEMASK,
    /* 0x255 */ OBJECT_ZORABAND,
    /* 0x256 */ OBJECT_KEPN_KOYA,
    /* 0x257 */ OBJECT_OBJECT_UNSET_USIYANE,
    /* 0x258 */ OBJECT_GI_MASK05,
    /* 0x259 */ OBJECT_GI_MASK11,
    /* 0x25A */ OBJECT_GI_MASK20,
    /* 0x25B */ OBJECT_NNH,
    /* 0x25C */ OBJECT_MASK_GERO,
    /* 0x25D */ OBJECT_MASK_YOFUKASI,
    /* 0x25E */ OBJECT_MASK_MEOTO,
    /* 0x25F */ OBJECT_MASK_DANCER,
    /* 0x260 */ OBJECT_KZSAKU,
    /* 0x261 */ OBJECT_OBJECT_UNSET_MILK_BIN,
    /* 0x262 */ OBJECT_RANDOM_OBJ,
    /* 0x263 */ OBJECT_KUJIYA,
    /* 0x264 */ OBJECT_KITAN,
    /* 0x265 */ OBJECT_GI_MASK06,
    /* 0x266 */ OBJECT_GI_MASK16,
    /* 0x267 */ OBJECT_ASTR_OBJ,
    /* 0x268 */ OBJECT_BSB,
    /* 0x269 */ OBJECT_FALL2,
    /* 0x26A */ OBJECT_STH,
    /* 0x26B */ OBJECT_GI_MSSA,
    /* 0x26C */ OBJECT_SMTOWER,
    /* 0x26D */ OBJECT_GI_MASK21,
    /* 0x26E */ OBJECT_YADO_OBJ,
    /* 0x26F */ OBJECT_SYOTEN,
    /* 0x270 */ OBJECT_MOONEND,
    /* 0x271 */ OBJECT_OB,
    /* 0x272 */ OBJECT_GI_BOTTLE_04,
    /* 0x273 */ OBJECT_OBJECT_UNSET_DANPEILIFT,
    /* 0x274 */ OBJECT_WDOR01,
    /* 0x275 */ OBJECT_WDOR02,
    /* 0x276 */ OBJECT_WDOR03,
    /* 0x277 */ OBJECT_STK3,
    /* 0x278 */ OBJECT_KINSTA1_OBJ,
    /* 0x279 */ OBJECT_KINSTA2_OBJ,
    /* 0x27A */ OBJECT_BH,
    /* 0x27B */ OBJECT_WDOR04,
    /* 0x27C */ OBJECT_WDOR05,
    /* 0x27D */ OBJECT_GI_MASK17,
    /* 0x27E */ OBJECT_GI_MASK22,
    /* 0x27F */ OBJECT_LBFSHOT,
    /* 0x280 */ OBJECT_FUSEN,
    /* 0x281 */ OBJECT_ENDING_OBJ,
    /* 0x282 */ OBJECT_GI_MASK13
} ObjectID;

#endif
