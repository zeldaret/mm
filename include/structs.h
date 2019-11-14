#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <unk.h>
#include <os.h>

enum EffectSSType {
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
};

enum IRQ_MSG_TYPE {
    IRQ_VERTICAL_RETRACE_MSG = 0x1,
    IRQ_PRENMI_2_MSG = 0x3,
    IRQ_PRENMI_1_MSG = 0x4
};

enum IRQ_TYPE {
    IRQ_VERTICAL_RETRACE = 0x29A,
    IRQ_SP = 0x29B,
    IRQ_DP = 0x29C,
    IRQ_PRENMI_1 = 0x29D,
    IRQ_PRENMI_2 = 0x29F,
    IRQ_PRENMI_3 = 0x2A0,
    IRQ_PRENMI_4 = 0x2A1
};

enum THREAD_STACK_STATUS {
    THREAD_STACK_STATUS_GOOD = 0x0,
    THREAD_STACK_STATUS_WARNING = 0x1,
    THREAD_STACK_STATUS_FULL = 0x2
};

typedef struct {
/* 0x0 */ unsigned int inst1;
/* 0x4 */ unsigned int inst2;
/* 0x8 */ unsigned int inst3;
/* 0xC */ unsigned int inst4;
} __osExceptionVector;

typedef void(*func_ptr)(void);

typedef void(*osCreateThread_func)(void*);

typedef struct {
/* 0x000 */ OSThread unk0;
/* 0x1B0 */ UNK_TYPE1 pad1B0[1536];
/* 0x7B0 */ OSMesgQueue unk7B0;
/* 0x7C8 */ UNK_TYPE4 unk7C8;
/* 0x7CC */ u8 unk7CC;
/* 0x7CD */ u8 unk7CD;
/* 0x7CE */ u8 unk7CE;
/* 0x7CF */ u8 unk7CF;
/* 0x7D0 */ UNK_TYPE4 unk7D0;
/* 0x7D4 */ func_ptr unk7D4;
/* 0x7D8 */ UNK_TYPE4 unk7D8;
/* 0x7DC */ UNK_TYPE1 pad7DC[108];
} s80083BC4;

typedef struct {
/* 0x00 */ UNK_TYPE4 unk0;
/* 0x04 */ UNK_TYPE4 unk4;
/* 0x08 */ UNK_TYPE4 unk8;
/* 0x0C */ UNK_TYPE1 padC[92];
/* 0x68 */ f32 unk68;
/* 0x6C */ f32 unk6C;
/* 0x70 */ f32 unk70;
/* 0x74 */ u16 unk74;
/* 0x76 */ u16 unk76;
/* 0x78 */ u16 unk78;
/* 0x7A */ UNK_TYPE1 pad7A[2];
/* 0x7C */ f32 unk7C;
/* 0x80 */ f32 unk80;
/* 0x84 */ f32 unk84;
/* 0x88 */ f32 unk88;
/* 0x8C */ f32 unk8C;
/* 0x90 */ f32 unk90;
/* 0x94 */ u16 unk94;
/* 0x96 */ u16 unk96;
/* 0x98 */ u16 unk98;
/* 0x9A */ UNK_TYPE1 pad9A[2];
/* 0x9C */ f32 unk9C;
/* 0xA0 */ f32 unkA0;
/* 0xA4 */ f32 unkA4;
} s800CAAD0;

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[32];
} s800E03A0;

typedef struct {
/* 0x000 */ OSThread unk0;
/* 0x1B0 */ s8 argCount;
/* 0x1B1 */ s8 unk1B1;
/* 0x1B2 */ UNK_TYPE1 pad1B2[2];
/* 0x1B4 */ UNK_TYPE1 func;
/* 0x1B5 */ UNK_TYPE1 pad1B5[3];
/* 0x1B8 */ s32 arg0;
/* 0x1BC */ s32 arg1;
} s8018571C;

typedef struct {
/* 0x00 */ int unk0;
/* 0x04 */ void* unk4;
/* 0x08 */ int unk8;
/* 0x0C */ int unkC;
/* 0x10 */ int unk10;
/* 0x14 */ OSMesgQueue unk14;
} s80185D40;

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[20];
} s801FE7C0;

typedef struct {
/* 0x00 */ u8 unk0[32];
} z_ActorDamageChart;

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
} z_ActorEnTest20C;

typedef struct {
/* 0x0 */ u32 cont : 1;
/* 0x0 */ u32 type : 4;
/* 0x0 */ u32 offset : 11;
/* 0x2 */ s32 value : 16;
} z_ActorInitVar;

typedef struct {
/* 0x0 */ u32 unk0;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 unk5;
} z_ColBumpInit;

typedef struct {
/* 0x0 */ u8 unk0;
/* 0x1 */ u8 unk1;
/* 0x2 */ u8 unk2;
/* 0x3 */ u8 unk3;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 type;
} z_ColCommonInit;

typedef struct {
/* 0x0 */ u32 collidesWith;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 unk5;
} z_ColTouch;

typedef struct {
/* 0x0 */ u32 unk0;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 unk5;
} z_ColTouchInit;

typedef struct {
/* 0x0 */ u8 red;
/* 0x1 */ u8 green;
/* 0x2 */ u8 blue;
/* 0x3 */ u8 alpha;
} z_Color;

typedef struct {
/* 0x00 */ u8 cutsceneCount;
/* 0x01 */ UNK_TYPE1 pad1[3];
/* 0x04 */ u16* currentCutsceneData;
/* 0x08 */ u8 state;
/* 0x09 */ UNK_TYPE1 pad9[3];
/* 0x0C */ f32 unkC;
/* 0x10 */ u16 currentFrame;
/* 0x12 */ UNK_TYPE1 pad12[22];
/* 0x28 */ UNK_TYPE4 unk28[10];
} z_CutsceneContext;

typedef struct {
/* 0x0 */ u32 data;
/* 0x4 */ UNK_TYPE1 pad4[4];
} z_CutsceneEntry;

typedef struct {
/* 0x0 */ u32 size;
/* 0x4 */ void* unk4;
/* 0x8 */ Gfx* append;
/* 0xC */ void* appendEnd;
} z_DisplayList;

typedef struct {
/* 0x00 */ u32 vromStart;
/* 0x04 */ u32 vramStart;
/* 0x08 */ u32 size;
/* 0x0C */ UNK_TYPE1 padC[8];
/* 0x14 */ UNK_TYPE4 unk14;
/* 0x18 */ OSMesgQueue* callback;
/* 0x1C */ void* callbackMesg;
} z_DmaRequest;

typedef struct {
/* 0x0 */ u32 vromStart;
/* 0x4 */ u32 vromEnd;
/* 0x8 */ u32 romStart;
/* 0xC */ u32 romEnd;
} z_DmadataEntry;

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
} z_F3DVertexColor;

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
} z_F3DVertexNormal;

typedef struct {
/* 0x0 */ UNK_TYPE4 size;
/* 0x4 */ void* heapStart;
/* 0x8 */ void* heapAppendStart;
/* 0xC */ void* heapAppendEnd;
} z_GameStateHeap;

typedef struct {
/* 0x00 */ u32 ramLocation;
/* 0x04 */ u32 vromStart;
/* 0x08 */ u32 vromEnd;
/* 0x0C */ u32 vramStart;
/* 0x10 */ u32 vramEnd;
/* 0x14 */ UNK_TYPE4 unk14;
/* 0x18 */ func_ptr init;
/* 0x1C */ func_ptr fini;
/* 0x20 */ UNK_TYPE4 unk20;
/* 0x24 */ UNK_TYPE4 unk24;
/* 0x28 */ UNK_TYPE4 unk28;
/* 0x2C */ u32 size;
} z_GameStateMetaInfo;

typedef struct {
/* 0x00 */ s32 unk0;
/* 0x04 */ UNK_TYPE1 pad4[64];
} z_GlobalContext17d98;

typedef struct {
/* 0x000 */ UNK_TYPE1 pad0[104];
/* 0x068 */ f32 unk68;
/* 0x06C */ f32 unk6C;
/* 0x070 */ f32 unk70;
/* 0x074 */ UNK_TYPE1 pad74[12];
/* 0x080 */ f32 unk80;
/* 0x084 */ f32 unk84;
/* 0x088 */ f32 unk88;
/* 0x08C */ UNK_TYPE1 pad8C[52];
/* 0x0C0 */ f32 unkC0;
/* 0x0C4 */ f32 unkC4;
/* 0x0C8 */ f32 unkC8;
/* 0x0CC */ f32 unkCC;
/* 0x0D0 */ f32 unkD0;
/* 0x0D4 */ f32 unkD4;
/* 0x0D8 */ UNK_TYPE1 padD8[36];
/* 0x0FC */ f32 unkFC;
/* 0x100 */ f32 unk100;
/* 0x104 */ UNK_TYPE1 pad104[52];
/* 0x138 */ u16 unk138;
/* 0x13A */ UNK_TYPE1 pad13A[4];
/* 0x13E */ u16 unk13E;
/* 0x140 */ s16 unk140;
/* 0x142 */ s16 unk142;
/* 0x144 */ UNK_TYPE1 pad144[4];
/* 0x148 */ s16 unk148;
/* 0x14A */ UNK_TYPE1 pad14A[2];
/* 0x14C */ s16 unk14C;
/* 0x14E */ UNK_TYPE1 pad14E[6];
/* 0x154 */ s16 unk154;
/* 0x156 */ UNK_TYPE1 pad156[16];
/* 0x166 */ s16 unk166;
/* 0x168 */ UNK_TYPE1 pad168[16];
} z_GlobalContext220;

// Font textures are loaded into here
typedef struct {
/* 0x0000 */ u8 unk0[128][120][2];
/* 0x7800 */ u8 unk7800[128][93];
} z_GlobalContext4A70;

typedef struct {
/* 0x000 */ Gfx* polyOpaBuffer;
/* 0x004 */ Gfx* polyXluBuffer;
/* 0x008 */ UNK_TYPE1 pad8[8];
/* 0x010 */ Gfx* overlayBuffer;
/* 0x014 */ UNK_TYPE1 pad14[36];
/* 0x038 */ UNK_TYPE4 unk38[8];
/* 0x058 */ UNK_TYPE1 pad58[4];
/* 0x05C */ OSMesgQueue unk5C;
/* 0x074 */ UNK_TYPE1 pad74[300];
/* 0x1A0 */ Gfx* unk1A0;
/* 0x1A4 */ z_DisplayList unk1A4;
/* 0x1B4 */ Gfx* unk1B4;
/* 0x1B8 */ z_DisplayList unk1B8;
/* 0x1C8 */ UNK_TYPE1 pad1C8[172];
/* 0x274 */ OSViMode* unk274;
/* 0x278 */ UNK_TYPE1 pad278[32];
/* 0x298 */ z_DisplayList overlay;
/* 0x2A8 */ z_DisplayList polyOpa;
/* 0x2B8 */ z_DisplayList polyXlu;
/* 0x2C8 */ s32 displaylistCounter;
/* 0x2CC */ void* framebuffer;
/* 0x2D0 */ UNK_TYPE1 pad2D0[11];
/* 0x2DB */ u8 framebufferCounter;
/* 0x2DC */ UNK_TYPE1 pad2DC[8];
/* 0x2E4 */ f32 unk2E4;
/* 0x2E8 */ f32 unk2E8;
/* 0x2EC */ UNK_TYPE1 pad2EC[4];
} z_GraphicsContext;

typedef struct {
/* 0x0 */ u16 buttons;
/* 0x2 */ s8 xAxis;
/* 0x3 */ s8 yAxis;
/* 0x4 */ s16 unk4;
} z_InputInfo;

typedef struct {
/* 0x00 */ z_InputInfo current;
/* 0x06 */ z_InputInfo last;
/* 0x0C */ z_InputInfo pressEdge;
/* 0x12 */ z_InputInfo releaseEdge;
} z_InputStruct;

typedef struct {
/* 0x0 */ u8 type;
/* 0x2 */ u16 params[6];
} z_LightInfo;

typedef struct {
/* 0x0 */ s8 dirX;
/* 0x1 */ s8 dirY;
/* 0x2 */ s8 dirZ;
/* 0x3 */ u8 red;
/* 0x4 */ u8 green;
/* 0x5 */ u8 blue;
/* 0x6 */ u16 pad[3];
} z_LightInfoDirectionalParams;

typedef struct {
/* 0x0 */ s16 posX;
/* 0x2 */ s16 posY;
/* 0x4 */ s16 posZ;
/* 0x6 */ u8 red;
/* 0x7 */ u8 green;
/* 0x8 */ u8 blue;
/* 0x9 */ u8 unk9; // func_80102880 sets this only for type 2, func_80102A64 draws something if this is set
/* 0xA */ s16 radius;
} z_LightInfoPositionalParams;

typedef struct {
/* 0x00 */ u8 enablePosLights;
/* 0x01 */ u8 numLights;
/* 0x02 */ UNK_TYPE1 pad2[6];
/* 0x08 */ Ambient ambient;
/* 0x10 */ Light lights[7];
} z_LightMapper;

typedef struct {
/* 0x00 */ f32 x[4];
/* 0x10 */ f32 y[4];
/* 0x20 */ f32 z[4];
/* 0x30 */ f32 w[4];
} z_Matrix;

typedef struct {
/* 0x0 */ u32 vromStart;
/* 0x4 */ u32 vromEnd;
} z_ObjectFileTableEntry;

typedef struct {
/* 0x00 */ u32 textSize;
/* 0x04 */ u32 dataSize;
/* 0x08 */ u32 rodataSize;
/* 0x0C */ u32 bssSize;
/* 0x10 */ u32 amountOfRelocations;
} z_OverlayBlockSizes;

typedef struct {
/* 0x0 */ u8 red;
/* 0x1 */ u8 green;
/* 0x2 */ u8 blue;
} z_RGB;

typedef struct {
/* 0x00 */ s16 intPart[16];
/* 0x20 */ u16 fracPart[16];
} z_RSPMatrix;

typedef struct {
/* 0x0 */ u32 vromStart;
/* 0x4 */ u32 vromEnd;
} z_RoomFileLocation;

typedef struct {
/* 0x00 */ u8 zelda[6]; // Will always be "ZELDA3" for a valid save
/* 0x06 */ UNK_TYPE1 pad6[34];
} z_SaveContext_struct1;

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[34];
} z_SaveContext_struct2;

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[136];
} z_SaveContext_struct3;

typedef struct {
/* 0x0 */ UNK_TYPE1 pad0[16];
} z_SceneActorInit;

typedef struct {
/* 0x0 */ u8 command;
/* 0x1 */ u8 unk1;
/* 0x2 */ UNK_TYPE1 pad2[2];
/* 0x4 */ u32 unk4;
} z_SceneHeaderEntry;

typedef struct {
/* 0x00 */ s16 scenes[27];
} z_SceneIdList;

typedef struct {
/* 0x00 */ s16 id; // Negative ids mean that the object is unloaded
/* 0x02 */ UNK_TYPE1 pad2[2];
/* 0x04 */ void* vramAddr;
/* 0x08 */ z_DmaRequest unk8;
/* 0x28 */ OSMesgQueue unk28;
/* 0x40 */ UNK_TYPE1 pad40[4];
} z_SceneObject;

typedef struct {
/* 0x0 */ u32 romStart;
/* 0x4 */ u32 romEnd;
/* 0x8 */ UNK_TYPE1 pad8[3];
/* 0xB */ u8 unkB;
/* 0xC */ UNK_TYPE1 padC[1];
/* 0xD */ u8 unkD;
/* 0xE */ UNK_TYPE1 padE[2];
} z_SceneTableEntry;

typedef struct {
/* 0x0000 */ u8 unk0;
/* 0x0001 */ u8 unk1;
/* 0x0002 */ u8 unk2;
/* 0x0003 */ u8 unk3;
/* 0x0004 */ u32 unk4;
/* 0x0008 */ UNK_TYPE1 pad8[204];
/* 0x00D4 */ u16 unkD4;
/* 0x00D6 */ UNK_TYPE1 padD6[38];
/* 0x00FC */ s16 unkFC;
/* 0x00FE */ UNK_TYPE1 padFE[24];
/* 0x0116 */ s16 unk116;
/* 0x0118 */ UNK_TYPE1 pad118[2398];
/* 0x0A76 */ s16 unkA76;
/* 0x0A78 */ UNK_TYPE1 padA78[2];
/* 0x0A7A */ s16 unkA7A;
/* 0x0A7C */ s16 unkA7C;
/* 0x0A7E */ UNK_TYPE1 padA7E[2902];
} z_StaticContext;

typedef struct {
/* 0x0 */ s8 unk0;
/* 0x1 */ UNK_TYPE1 pad1[1];
/* 0x2 */ s8 unk2;
/* 0x3 */ UNK_TYPE1 pad3[1];
/* 0x4 */ s16 actorIndex; // negative means already loaded?
/* 0x6 */ s16 x;
/* 0x8 */ s16 y;
/* 0xA */ s16 z;
/* 0xC */ s16 yRot;
/* 0xE */ u16 variable;
} z_TransitionActorInit;

typedef struct {
/* 0x0 */ f32 x;
/* 0x4 */ f32 y;
/* 0x8 */ f32 z;
} z_Vector3f;

typedef struct {
/* 0x0 */ s16 x;
/* 0x2 */ s16 y;
/* 0x4 */ s16 z;
} z_Vector3s;

typedef struct {
/* 0x000 */ u32 magic; // always 0x56494557, "VIEW"
/* 0x004 */ z_GraphicsContext* graphics;
/* 0x008 */ UNK_TYPE1 pad8[16];
/* 0x018 */ f32 unk18;
/* 0x01C */ f32 unk1C;
/* 0x020 */ f32 unk20;
/* 0x024 */ f32 unk24;
/* 0x028 */ z_Vector3f unk28;
/* 0x034 */ z_Vector3f unk34;
/* 0x040 */ z_Vector3f unk40;
/* 0x04C */ UNK_TYPE1 pad4C[220];
/* 0x128 */ f32 unk128;
/* 0x12C */ f32 unk12C;
/* 0x130 */ f32 unk130;
/* 0x134 */ f32 unk134;
/* 0x138 */ f32 unk138;
/* 0x13C */ f32 unk13C;
/* 0x140 */ f32 unk140;
/* 0x144 */ f32 unk144;
/* 0x148 */ f32 unk148;
/* 0x14C */ f32 unk14C;
/* 0x150 */ f32 unk150;
/* 0x154 */ f32 unk154;
/* 0x158 */ f32 unk158;
/* 0x15C */ UNK_TYPE1 pad15C[12];
} z_View;

typedef struct {
/* 0x00 */ void* bufferEnd;
/* 0x04 */ u32 romReadHead;
/* 0x08 */ u32 amountLeftToRead;
/* 0x0C */ u32 loadNextChunkBoundary;
/* 0x10 */ u32 destBufferEnd;
} z_Yaz0DecompState;

typedef void(*light_map_directional_func)(z_LightMapper* mapper, void* params, z_Vector3f* pos);

typedef void(*light_map_positional_func)(z_LightMapper* mapper, void* params);

typedef struct {
/* 0x00 */ z_Vector3f unk0;
/* 0x0C */ z_Vector3f unkC;
/* 0x18 */ s16 unk18;
/* 0x1A */ s16 unk1A;
} s80874650;

// Related to collision?
typedef struct {
/* 0x00 */ z_ActorDamageChart* damageChart;
/* 0x04 */ z_Vector3f displacement;
/* 0x10 */ s16 unk10;
/* 0x12 */ s16 unk12;
/* 0x14 */ s16 unk14;
/* 0x16 */ u8 unk16;
/* 0x17 */ u8 unk17;
} z_ActorA0;

typedef struct {
/* 0x00 */ z_Vector3s rotation;
/* 0x08 */ f32 yDisplacement;
/* 0x0C */ func_ptr postDrawFunc; // TODO params (z_Actor*, UNK*, z_GlobalContext*)
/* 0x10 */ f32 unk10;
/* 0x14 */ s8 unk14;
} z_ActorBC;

typedef struct {
/* 0x00 */ u8 unk0;
/* 0x04 */ z_ColTouchInit unk4;
/* 0x0C */ z_ColBumpInit unkC;
/* 0x14 */ u8 unk14;
/* 0x15 */ u8 unk15;
/* 0x16 */ u8 unk16;
} z_ColBodyInfoInit;

typedef struct {
/* 0x0 */ u32 collidesWith;
/* 0x4 */ u8 unk4;
/* 0x5 */ u8 unk5;
/* 0x6 */ z_Vector3s unk6;
} z_ColBump;

typedef struct {
/* 0x0 */ s16 radius;
/* 0x2 */ s16 height;
/* 0x4 */ s16 yOffset;
/* 0x6 */ z_Vector3s loc;
} z_ColCylinderParams;

typedef struct {
/* 0x00 */ z_Vector3f pointA;
/* 0x0C */ z_Vector3f pointB;
/* 0x18 */ z_Vector3f pointC;
/* 0x24 */ z_Vector3f pointD;
/* 0x30 */ z_Vector3s unk30;
/* 0x36 */ z_Vector3s unk36;
/* 0x3C */ f32 unk3C;
} z_ColQuadParams;

typedef struct {
/* 0x0 */ z_Vector3s loc;
/* 0x6 */ s16 radius;
} z_ColSphereCollisionInfo;

typedef struct {
/* 0x00 */ z_Vector3s unk0;
/* 0x06 */ s16 unk6;
/* 0x08 */ z_ColSphereCollisionInfo colInfo;
/* 0x10 */ f32 unk10;
/* 0x14 */ u8 unk14;
/* 0x15 */ UNK_TYPE1 pad15[3];
} z_ColSphereParams;

typedef struct {
/* 0x0 */ u8 unk0;
/* 0x1 */ z_ColSphereCollisionInfo unk1;
/* 0xA */ s16 unkA;
} z_ColSphereParamsInit;

typedef struct {
/* 0x00 */ z_Vector3f pointA;
/* 0x0C */ z_Vector3f pointB;
/* 0x18 */ z_Vector3f pointC;
/* 0x24 */ z_Vector3f unitNormal;
/* 0x30 */ f32 unk30;
} z_ColTriParams;

typedef struct {
/* 0x00 */ z_Vector3f unk0;
/* 0x0C */ z_Vector3f unkC;
/* 0x18 */ z_Vector3f unk18;
} z_ColTriParamsInit;

typedef struct {
/* 0x00 */ z_Vector3f position;
/* 0x0C */ z_Vector3f velocity;
/* 0x18 */ z_Vector3f acceleration;
/* 0x24 */ z_Color color1;
/* 0x28 */ z_Color color2;
/* 0x2C */ s16 scale;
/* 0x2E */ s16 scaleChangePerFrame;
/* 0x30 */ s16 life;
/* 0x32 */ u16 flags; // bit0: ? bit1: ? bit2: randomize colors
/* 0x34 */ u8 type; // type0: start small, get big, fade away type1: start big, fade away
} z_EffectDustInit;

typedef union {
/* 0x0 */ z_F3DVertexColor color;
/* 0x0 */ z_F3DVertexNormal normal;
} z_F3DVertex;

typedef struct {
/* 0x000 */ z_View unk0;
/* 0x168 */ UNK_TYPE1 pad168[194];
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
/* 0x252 */ s16 unk252;
/* 0x254 */ s16 unk254;
/* 0x256 */ UNK_TYPE1 pad256[26];
/* 0x270 */ s16 unk270;
/* 0x272 */ UNK_TYPE1 pad272[214];
} z_GlobalContext169E8;

typedef struct {
/* 0x00000 */ z_View unk0;
/* 0x00168 */ z_GlobalContext4A70 unk168;
/* 0x0A7E8 */ UNK_TYPE1 padA7E8[30960];
} z_GlobalContext4908;

typedef struct {
/* 0x0 */ u8 type;
/* 0x2 */ z_LightInfoDirectionalParams params;
} z_LightInfoDirectional;

typedef struct {
/* 0x0 */ u8 type;
/* 0x2 */ z_LightInfoPositionalParams params;
} z_LightInfoPositional;

typedef struct {
/* 0x00 */ z_Vector3f a;
/* 0x0C */ z_Vector3f b;
} z_LineSegment;

typedef struct {
/* 0x0000 */ UNK_TYPE1 pad0[12];
/* 0x000C */ u16 time;
/* 0x000E */ UNK_TYPE1 padE[22];
/* 0x0024 */ z_SaveContext_struct1 unk24;
/* 0x004C */ z_SaveContext_struct2 unk4C;
/* 0x006E */ UNK_TYPE1 pad6E[2];
/* 0x0070 */ z_SaveContext_struct3 unk70;
/* 0x00F8 */ UNK_TYPE1 padF8[3684];
/* 0x0F5C */ u32 mapsVisited;
/* 0x0F60 */ UNK_TYPE1 padF60[170];
/* 0x100A */ u16 checksum;
} z_SaveContext;

typedef struct {
/* 0x000 */ void* objectVramStart;
/* 0x004 */ void* objectVramEnd;
/* 0x008 */ u8 unk8;
/* 0x009 */ u8 unk9;
/* 0x00A */ u8 unkA;
/* 0x00B */ u8 keepObjectId;
/* 0x00C */ z_SceneObject objects[35];
} z_SceneContext;

typedef struct {
/* 0x00 */ z_ColCommonInit base;
/* 0x08 */ z_ColBodyInfoInit body;
/* 0x20 */ z_ColCylinderParams info;
} z_ColCylinderInit;

typedef struct {
/* 0x00 */ z_ColCommonInit base;
/* 0x08 */ z_ColBodyInfoInit body;
/* 0x20 */ z_ColQuadParams params;
} z_ColQuadInit;

typedef struct {
/* 0x00 */ z_ColBodyInfoInit body;
/* 0x18 */ z_ColSphereParamsInit params;
} z_ColSphereGroupElementInit;

typedef struct {
/* 0x0 */ z_ColCommonInit base;
/* 0x6 */ UNK_TYPE1 pad6[2];
/* 0x8 */ u32 count;
/* 0xC */ z_ColSphereGroupElementInit* init;
} z_ColSphereGroupInit;

typedef struct {
/* 0x00 */ z_ColCommonInit base;
/* 0x08 */ z_ColBodyInfoInit body;
/* 0x20 */ z_ColSphereParamsInit info;
} z_ColSphereInit;

typedef struct {
/* 0x00 */ z_ColBodyInfoInit body;
/* 0x18 */ z_ColTriParamsInit params;
} z_ColTriInit;

typedef struct {
/* 0x00 */ UNK_TYPE1 pad0[4];
/* 0x04 */ f32 unk4;
/* 0x08 */ f32 unk8;
/* 0x0C */ f32 unkC;
/* 0x10 */ UNK_TYPE1 pad10[7];
/* 0x17 */ u8 unk17;
/* 0x18 */ u8 unk18;
/* 0x19 */ UNK_TYPE1 pad19[5];
/* 0x1E */ u8 unk1E;
/* 0x1F */ u8 unk1F;
/* 0x20 */ u8 unk20;
/* 0x21 */ u8 unk21;
/* 0x22 */ u16 unk22;
/* 0x24 */ u16 unk24;
/* 0x26 */ UNK_TYPE1 pad26[2];
/* 0x28 */ z_LightInfoDirectional unk28;
/* 0x36 */ z_LightInfoDirectional unk36;
/* 0x44 */ UNK_TYPE1 pad44[72];
/* 0x8C */ z_Vector3s unk8C;
/* 0x92 */ z_Vector3s unk92;
/* 0x98 */ z_Vector3s unk98;
/* 0x9E */ z_Vector3s unk9E;
/* 0xA4 */ s16 unkA4;
/* 0xA6 */ s16 unkA6;
/* 0xA8 */ UNK_TYPE1 padA8[12];
/* 0xB4 */ f32 unkB4;
/* 0xB8 */ u8 environmentSettingsCount;
/* 0xB9 */ UNK_TYPE1 padB9[3];
/* 0xBC */ void* environmentSettingsList;
/* 0xC0 */ UNK_TYPE1 padC0[1];
/* 0xC1 */ u8 unkC1;
/* 0xC2 */ u8 unkC2;
/* 0xC3 */ UNK_TYPE1 padC3[1];
/* 0xC4 */ z_RGB unkC4;
/* 0xC7 */ s8 unkC7;
/* 0xC8 */ s8 unkC8;
/* 0xC9 */ s8 unkC9;
/* 0xCA */ z_RGB unkCA;
/* 0xCD */ s8 unkCD;
/* 0xCE */ s8 unkCE;
/* 0xCF */ s8 unkCF;
/* 0xD0 */ z_RGB unkD0;
/* 0xD3 */ z_RGB unkD3;
/* 0xD6 */ s16 unkD6;
/* 0xD8 */ s16 unkD8;
/* 0xDA */ UNK_TYPE1 padDA[2];
/* 0xDC */ f32 unkDC;
/* 0xE0 */ u8 unkE0;
/* 0xE1 */ UNK_TYPE1 padE1[17];
} z_KankyoContext;

typedef struct {
/* 0x0 */ z_ColCommonInit base;
/* 0x8 */ u32 count;
/* 0xC */ z_ColTriInit* elemInit;
} z_ColTriGroupInit;

typedef struct z_ActorBgMbarChair z_ActorBgMbarChair;

typedef struct z_ActorEnBji01 z_ActorEnBji01;

typedef struct z_ActorEnTest z_ActorEnTest;

typedef struct z_ActorInitData z_ActorInitData;

typedef struct {
/* 0x00 */ u32 vromStart;
/* 0x04 */ u32 vromEnd;
/* 0x08 */ u32 vramStart;
/* 0x0C */ u32 vramEnd;
/* 0x10 */ u32 ramAddr;
/* 0x14 */ z_ActorInitData* initValues;
/* 0x18 */ s8* name;
/* 0x1C */ s16 flags; // bit 0: don't allocate memory, use actorContext->0x250? bit 1: Always keep loaded?
/* 0x1E */ s8 clients;
/* 0x1F */ UNK_TYPE1 pad1F[1];
} z_ActorOverlayTableEntry;

typedef struct z_ActorPlayer z_ActorPlayer;

typedef struct z_ActorTypeList z_ActorTypeList;

typedef struct z_ActorContext z_ActorContext;

typedef struct z_ColCommon z_ColCommon;

typedef struct {
/* 0x000 */ s16 ATgroupLength;
/* 0x002 */ u16 flags; // bit 0: collision bodies can't be added or removed, only swapped out
/* 0x004 */ z_ColCommon* ATgroup[50];
/* 0x0CC */ s32 ACgroupLength;
/* 0x0D0 */ z_ColCommon* ACgroup[60];
/* 0x1C0 */ s32 OTgroupLength;
/* 0x1C4 */ z_ColCommon* OTgroup[50];
/* 0x28C */ s32 group4Length;
/* 0x290 */ z_ColCommon* group4[3];
} z_CollisionContext;

typedef struct z_ColBodyInfo z_ColBodyInfo;

struct z_ColBodyInfo {
/* 0x00 */ z_ColTouch toucher;
/* 0x08 */ z_ColBump bumper;
/* 0x14 */ u8 unk14;
/* 0x15 */ u8 unk15; // bit 0: can be toucher in AT-AC collision
/* 0x16 */ u8 unk16; // bit 0: can be bumper in AT-AC collision
/* 0x17 */ u8 unk17;
/* 0x18 */ z_ColCommon* unk18;
/* 0x1C */ z_ColCommon* unk1C;
/* 0x20 */ z_ColBodyInfo* unk20;
/* 0x24 */ z_ColBodyInfo* unk24;
};

typedef struct {
/* 0x00 */ z_ColBodyInfo body;
/* 0x28 */ z_ColSphereParams params;
} z_ColSphereGroupElement;

typedef struct {
/* 0x00 */ z_ColBodyInfo body;
/* 0x28 */ z_ColTriParams params;
} z_ColTri;

typedef struct z_ColCylinder z_ColCylinder;

typedef struct z_ColQuad z_ColQuad;

typedef struct z_ColSphere z_ColSphere;

typedef struct z_ColSphereGroup z_ColSphereGroup;

typedef struct z_ColTriGroup z_ColTriGroup;

typedef struct z_ActorEnBom z_ActorEnBom;

typedef struct z_ActorEnFirefly z_ActorEnFirefly;

typedef struct z_ActorObjBell z_ActorObjBell;

typedef struct z_ContextCommon z_ContextCommon;

typedef struct z_OpeningContext z_OpeningContext;

typedef struct z_TitleContext z_TitleContext;

typedef struct z_EffectTableInfo z_EffectTableInfo;

typedef struct z_GameAllocNode z_GameAllocNode;

struct z_GameAllocNode {
/* 0x00 */ z_GameAllocNode* unk0;
/* 0x04 */ z_GameAllocNode* unk4;
/* 0x08 */ u32 size;
/* 0x0C */ UNK_TYPE1 padC[4];
/* 0x10 */ z_GameAllocNode* unk10;
};

struct z_ContextCommon {
/* 0x00 */ z_GraphicsContext* graphicsContext;
/* 0x04 */ func_ptr update;
/* 0x08 */ func_ptr fini;
/* 0x0C */ func_ptr nextGameStateInit;
/* 0x10 */ u32 nextGameStateSize;
/* 0x14 */ z_InputStruct controllers[4];
/* 0x74 */ z_GameStateHeap heap;
/* 0x84 */ z_GameAllocNode gamealloc;
/* 0x98 */ UNK_TYPE1 pad98[3];
/* 0x9B */ u8 shouldContinue; // If 0, switch to next game state
/* 0x9C */ s32 frameCount;
/* 0xA0 */ UNK_TYPE1 padA0[2];
/* 0xA2 */ u8 unkA2; // game speed?
/* 0xA3 */ UNK_TYPE1 padA3[1];
};

struct z_OpeningContext {
/* 0x000 */ z_ContextCommon common;
/* 0x0A4 */ UNK_TYPE1 padA4[4];
/* 0x0A8 */ z_View unkA8;
};

struct z_TitleContext {
/* 0x000 */ z_ContextCommon common;
/* 0x0A4 */ u8* nintendo_logo_data;
/* 0x0A8 */ z_View unkA8;
/* 0x210 */ UNK_TYPE1 pad210[40];
/* 0x238 */ s16 unk238;
/* 0x23A */ s16 logoCoverAlpha;
/* 0x23C */ s16 logoCoverAlphaChangePerFrame;
/* 0x23E */ s16 logoFullVisibilityDuration;
/* 0x240 */ s16 frameCounter;
/* 0x242 */ UNK_TYPE2 frameCounterMod0x80;
/* 0x244 */ u8 switchToNextGameState;
/* 0x245 */ UNK_TYPE1 pad245[3];
};

typedef struct z_GlobalContext z_GlobalContext;

typedef void(*collision_func)(z_GlobalContext*, z_CollisionContext*, z_ColCommon*, z_ColCommon*);

typedef void(*cutscene_update_func)(z_GlobalContext* ctxt, z_CutsceneContext* cCtxt);

typedef void(*global_context_func)(z_GlobalContext*);

typedef void(*scene_header_func)(z_GlobalContext* ctxt, z_SceneHeaderEntry* entry);

typedef struct z_Heap z_Heap;

typedef struct z_HeapNode z_HeapNode;

struct z_Heap {
/* 0x00 */ z_HeapNode* head;
/* 0x04 */ u32 base;
/* 0x08 */ OSMesgQueue lock;
/* 0x20 */ UNK_TYPE1 pad20[1];
/* 0x21 */ u8 initialized;
/* 0x22 */ UNK_TYPE1 pad22[2];
};

struct z_HeapNode {
/* 0x0 */ s16 magic; // Should always be 0x7373
/* 0x2 */ s16 free;
/* 0x4 */ u32 size;
/* 0x8 */ z_HeapNode* next;
/* 0xC */ z_HeapNode* prev;
};

typedef struct z_Irqmgr z_Irqmgr;

typedef struct z_AudioThreadStruct z_AudioThreadStruct;

typedef struct z_Light z_Light;

struct z_Light {
/* 0x0 */ z_LightInfo* info;
/* 0x4 */ z_Light* prev;
/* 0x8 */ z_Light* next;
};

typedef struct {
/* 0x0 */ z_Light* lightsHead;
/* 0x4 */ u8 ambientRed;
/* 0x5 */ u8 ambientGreen;
/* 0x6 */ u8 ambientBlue;
/* 0x7 */ UNK_TYPE1 pad7[3];
/* 0xA */ s16 unkA;
/* 0xC */ s16 unkC;
} z_LightingContext;

typedef struct {
/* 0x000 */ int numOccupied;
/* 0x004 */ int nextFree;
/* 0x008 */ z_Light lights[32];
} z_LightsList;

typedef struct z_LoadedParticleEntry z_LoadedParticleEntry;

typedef void(*effect_func)(z_GlobalContext* ctxt, u32 index, z_LoadedParticleEntry* particle);

typedef void(*effect_init_func)(z_GlobalContext* ctxt, u32 index, z_LoadedParticleEntry* particle, void* init);

struct z_EffectTableInfo {
/* 0x0 */ z_LoadedParticleEntry* data_table; // Name from debug assert
/* 0x4 */ s32 searchIndex;
/* 0x8 */ s32 size;
};

struct z_LoadedParticleEntry {
/* 0x00 */ z_Vector3f position;
/* 0x0C */ z_Vector3f velocity;
/* 0x18 */ z_Vector3f acceleration;
/* 0x24 */ effect_func update;
/* 0x28 */ global_context_func draw;
/* 0x2C */ f32 unk2C;
/* 0x30 */ f32 unk30;
/* 0x34 */ f32 unk34;
/* 0x38 */ u32 displayList;
/* 0x3C */ UNK_TYPE4 unk3C;
/* 0x40 */ s16 regs[13]; // These are particle-specific
/* 0x5A */ u16 flags; // bit 0: set if this entry is not considered free on a priority tie bit 1: ? bit 2: ?
/* 0x5C */ s16 life; // -1 means this entry is free
/* 0x5E */ u8 priority; // Lower number mean higher priority
/* 0x5F */ u8 type;
};

typedef struct {
/* 0x0 */ UNK_TYPE4 unk0;
/* 0x4 */ effect_init_func init;
} z_ParticleOverlayInfo;

typedef struct {
/* 0x00 */ u32 vromStart;
/* 0x04 */ u32 vromEnd;
/* 0x08 */ u32 vramStart;
/* 0x0C */ u32 vramEnd;
/* 0x10 */ u32 loadedRamAddr;
/* 0x14 */ z_ParticleOverlayInfo* overlayInfo;
/* 0x18 */ u32 unk18; // Always 0x01000000?
} z_ParticleOverlayTableEntry;

typedef struct z_OSMesgQueueListNode z_OSMesgQueueListNode;

struct z_Irqmgr {
/* 0x000 */ s16 verticalRetraceMesg;
/* 0x002 */ UNK_TYPE1 pad2[30];
/* 0x020 */ s16 prenmi1Msg;
/* 0x022 */ UNK_TYPE1 pad22[30];
/* 0x040 */ s16 prenmi2Msg;
/* 0x042 */ UNK_TYPE1 pad42[30];
/* 0x060 */ OSMesgQueue irqQueue;
/* 0x078 */ UNK_TYPE4 irqBuffer[8];
/* 0x098 */ OSThread thread;
/* 0x248 */ z_OSMesgQueueListNode* callbacks;
/* 0x24C */ s8 prenmiStage;
/* 0x24D */ UNK_TYPE1 pad24D[3];
/* 0x250 */ OSTime lastPrenmiTime;
/* 0x258 */ OSTimer unk258;
/* 0x278 */ OSTime lastFrameTime;
};

struct z_OSMesgQueueListNode {
/* 0x0 */ z_OSMesgQueueListNode* next;
/* 0x4 */ OSMesgQueue* queue;
};

typedef struct {
/* 0x000 */ u8 controllers; // bit 0 is set if controller 1 is plugged in, etc.
/* 0x001 */ UNK_TYPE1 pad1[19];
/* 0x014 */ OSContStatus statuses[4];
/* 0x024 */ UNK_TYPE4 unk24;
/* 0x028 */ UNK_TYPE4 unk28;
/* 0x02C */ UNK_TYPE4 interrupts[8];
/* 0x04C */ OSMesgQueue siEventCallbackQueue;
/* 0x064 */ OSMesgQueue unk64;
/* 0x07C */ OSMesgQueue irqmgrCallbackQueue;
/* 0x094 */ z_OSMesgQueueListNode irqmgrCallbackQueueNode;
/* 0x09C */ z_Irqmgr* irqmgr;
/* 0x0A0 */ OSThread thread;
/* 0x250 */ UNK_TYPE1 pad250[96];
/* 0x2B0 */ OSContPad controllerState1[4];
/* 0x2C8 */ u8 maxNumControllers;
/* 0x2C9 */ UNK_TYPE1 pad2C9[435];
/* 0x47C */ u8 unk47C;
/* 0x47D */ u8 unk47D;
/* 0x47E */ u8 unk47E;
/* 0x47F */ UNK_TYPE1 pad47F[1];
} z_PadmgrThreadStruct;

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
/* 0x31C */ UNK_TYPE1 pad31C[4];
/* 0x320 */ UNK_TYPE4 unk320;
/* 0x324 */ UNK_TYPE4 unk324;
/* 0x328 */ UNK_TYPE1 pad328[7];
/* 0x32F */ s8 unk32F;
/* 0x330 */ z_OSMesgQueueListNode unk330;
} z_SchedThreadStruct;

struct z_AudioThreadStruct {
/* 0x000 */ z_Irqmgr* irqmgr;
/* 0x004 */ z_SchedThreadStruct* unk4;
/* 0x008 */ UNK_TYPE1 pad8[88];
/* 0x060 */ UNK_TYPE4 unk60;
/* 0x064 */ OSMesgQueue unk64;
/* 0x07C */ UNK_TYPE4 unk7C[30];
/* 0x0F4 */ OSMesgQueue unkF4;
/* 0x10C */ UNK_TYPE4 unk10C;
/* 0x110 */ OSMesgQueue initDoneCallback;
/* 0x128 */ UNK_TYPE4 initDoneCallbackMsgBuffer;
/* 0x12C */ UNK_TYPE1 pad12C[4];
/* 0x130 */ OSThread unk130;
};

typedef struct z_ThreadInfo z_ThreadInfo;

struct z_ThreadInfo {
/* 0x00 */ z_ThreadInfo* next;
/* 0x04 */ z_ThreadInfo* prev;
/* 0x08 */ s32* stackBegin;
/* 0x0C */ s32* stackEnd;
/* 0x10 */ s32 initStackValue;
/* 0x14 */ s32 stackWarningThreshold;
/* 0x18 */ s8* name;
};

typedef struct z_Actor z_Actor;

typedef void(*actor_func)(z_Actor* this, z_GlobalContext* ctxt);

typedef void(*actor_init_var_func)(z_Actor*, z_ActorInitVar*);

struct z_Actor {
/* 0x000 */ s16 id;
/* 0x002 */ UNK_TYPE1 type;
/* 0x003 */ s8 room;
/* 0x004 */ UNK_TYPE4 flags; // bit 22: disable positional lights if bit 28 is not set; bit 28: enable positional lights on actor
/* 0x008 */ z_Vector3f initPos;
/* 0x014 */ z_Vector3s initRot;
/* 0x01A */ UNK_TYPE1 pad1A[2];
/* 0x01C */ s16 variable;
/* 0x01E */ s8 objectIndex;
/* 0x01F */ UNK_TYPE1 pad1F[1];
/* 0x020 */ s16 unk20;
/* 0x022 */ UNK_TYPE1 pad22[2];
/* 0x024 */ z_Vector3f pos;
/* 0x030 */ z_Vector3s speedRot;
/* 0x036 */ UNK_TYPE1 pad36[2];
/* 0x038 */ s8 unk38;
/* 0x039 */ u8 unk39;
/* 0x03A */ UNK_TYPE1 pad3A[2];
/* 0x03C */ z_Vector3f unk3C;
/* 0x048 */ z_Vector3s unk48;
/* 0x04E */ UNK_TYPE1 pad4E[2];
/* 0x050 */ u16 unk50;
/* 0x052 */ UNK_TYPE1 pad52[2];
/* 0x054 */ f32 unk54;
/* 0x058 */ z_Vector3f scale;
/* 0x064 */ z_Vector3f velocity;
/* 0x070 */ f32 speed;
/* 0x074 */ f32 gravity;
/* 0x078 */ f32 minYVelocity;
/* 0x07C */ UNK_TYPE1 pad7C[12];
/* 0x088 */ f32 unk88;
/* 0x08C */ f32 unk8C;
/* 0x090 */ u16 unk90;
/* 0x092 */ s16 unk92;
/* 0x094 */ UNK_TYPE1 pad94[4];
/* 0x098 */ f32 unk98;
/* 0x09C */ f32 unk9C;
/* 0x0A0 */ z_ActorA0 unkA0;
/* 0x0B8 */ UNK_TYPE1 padB8[1];
/* 0x0B9 */ u8 unkB9;
/* 0x0BA */ UNK_TYPE1 padBA[2];
/* 0x0BC */ z_ActorBC unkBC;
/* 0x0D4 */ UNK_TYPE1 padD4[24];
/* 0x0EC */ z_Vector3f unkEC;
/* 0x0F8 */ f32 unkF8;
/* 0x0FC */ f32 unkFC;
/* 0x100 */ f32 unk100;
/* 0x104 */ f32 unk104;
/* 0x108 */ z_Vector3f unk108;
/* 0x114 */ u8 unk114;
/* 0x115 */ UNK_TYPE1 pad115[1];
/* 0x116 */ s16 textId;
/* 0x118 */ UNK_TYPE1 pad118[2];
/* 0x11A */ u16 hitEffectParams; // TODO make into bitfield
/* 0x11C */ u8 hitEffectIntensity;
/* 0x11D */ u8 unk11D;
/* 0x11E */ UNK_TYPE1 pad11E[1];
/* 0x11F */ u8 naviMsgId;
/* 0x120 */ z_Actor* parent;
/* 0x124 */ z_Actor* child;
/* 0x128 */ z_Actor* prev;
/* 0x12C */ z_Actor* next;
/* 0x130 */ actor_func init;
/* 0x134 */ actor_func fini;
/* 0x138 */ actor_func main;
/* 0x13C */ actor_func draw;
/* 0x140 */ z_ActorOverlayTableEntry* tableEntry;
};

typedef struct {
/* 0x000 */ z_Actor base;
/* 0x144 */ UNK_TYPE1 pad144[100];
/* 0x1A8 */ u32 displayListAddr;
/* 0x1AC */ actor_func updateFunc;
} z_ActorBgIknvObj;

struct z_ActorBgMbarChair {
/* 0x000 */ z_Actor base;
/* 0x144 */ UNK_TYPE1 pad144[24];
};

struct z_ActorEnBji01 {
/* 0x000 */ z_Actor base;
/* 0x144 */ UNK_TYPE1 pad144[368];
};

struct z_ActorEnTest {
/* 0x000 */ z_Actor base;
/* 0x144 */ UNK_TYPE1 pad144[16];
/* 0x154 */ f32 unk154;
/* 0x158 */ UNK_TYPE1 pad158[176];
/* 0x208 */ u8 unk208;
/* 0x209 */ UNK_TYPE1 pad209[1];
/* 0x20A */ u8 unk20A;
/* 0x20B */ UNK_TYPE1 pad20B[1];
/* 0x20C */ z_ActorEnTest20C unk20C[20];
};

struct z_ActorInitData {
/* 0x00 */ s16 id;
/* 0x02 */ u8 type;
/* 0x03 */ UNK_TYPE1 pad3[1];
/* 0x04 */ s32 flags;
/* 0x08 */ s16 objectDependency;
/* 0x0A */ UNK_TYPE1 padA[2];
/* 0x0C */ u32 instanceSize;
/* 0x10 */ actor_func init;
/* 0x14 */ actor_func fini;
/* 0x18 */ actor_func main;
/* 0x1C */ actor_func draw;
};

struct z_ActorPlayer {
/* 0x000 */ z_Actor base;
/* 0x144 */ UNK_TYPE1 pad144[3124];
};

struct z_ActorTypeList {
/* 0x0 */ s32 length;
/* 0x4 */ z_Actor* head;
/* 0x8 */ UNK_TYPE1 pad8[4];
};

struct z_ColCommon {
/* 0x00 */ z_Actor* actor;
/* 0x04 */ z_Actor* unk4;
/* 0x08 */ z_Actor* unk8;
/* 0x0C */ z_Actor* unkC;
/* 0x10 */ u8 unk10;
/* 0x11 */ u8 unk11;
/* 0x12 */ u8 unk12;
/* 0x13 */ u8 unk13;
/* 0x14 */ u8 unk14;
/* 0x15 */ u8 type;
/* 0x16 */ UNK_TYPE1 pad16[2];
};

struct z_ColCylinder {
/* 0x00 */ z_ColCommon base;
/* 0x18 */ z_ColBodyInfo body;
/* 0x40 */ z_ColCylinderParams params;
};

struct z_ColQuad {
/* 0x00 */ z_ColCommon base;
/* 0x18 */ z_ColBodyInfo body;
/* 0x40 */ z_ColQuadParams params;
};

struct z_ColSphere {
/* 0x00 */ z_ColCommon base;
/* 0x18 */ z_ColBodyInfo body;
/* 0x40 */ z_ColSphereParams params;
};

struct z_ColSphereGroup {
/* 0x00 */ z_ColCommon base;
/* 0x18 */ u32 count;
/* 0x1C */ z_ColSphereGroupElement* spheres;
};

struct z_ColTriGroup {
/* 0x00 */ z_ColCommon base;
/* 0x18 */ u32 count;
/* 0x1C */ z_ColTri* tris;
};

typedef struct {
/* 0x000 */ z_Actor base;
/* 0x144 */ z_ColQuad unk144;
/* 0x1C4 */ z_ColQuad unk1C4;
/* 0x244 */ z_Vector3f unk244;
/* 0x250 */ f32 unk250;
/* 0x254 */ f32 unk254;
/* 0x258 */ actor_func update;
/* 0x25C */ s16 unk25C;
/* 0x25E */ u16 unk25E;
/* 0x260 */ u8 unk260;
/* 0x261 */ UNK_TYPE1 pad261[3];
} z_ActorArrowFire;

struct z_ActorContext {
/* 0x000 */ UNK_TYPE1 pad0[2];
/* 0x002 */ u8 unk2;
/* 0x003 */ UNK_TYPE1 pad3[1];
/* 0x004 */ s8 unk4;
/* 0x005 */ UNK_TYPE1 pad5[7];
/* 0x00C */ s16 unkC;
/* 0x00E */ u8 totalLoadedActors;
/* 0x00F */ u8 unkF;
/* 0x010 */ z_ActorTypeList actorTypeLists[12];
/* 0x0A0 */ z_Actor* unkA0;
/* 0x0A4 */ UNK_TYPE1 padA4[180];
/* 0x158 */ z_Actor* unk158;
/* 0x15C */ UNK_TYPE1 pad15C[80];
/* 0x1AC */ z_Actor* unk1AC;
/* 0x1B0 */ z_Actor* unk1B0;
/* 0x1B4 */ UNK_TYPE1 pad1B4[24];
/* 0x1CC */ u32 unk1CC;
/* 0x1D0 */ u32 clearedRooms;
/* 0x1D4 */ u32 collectibleFlags[4]; // bitfield of 128 bits
/* 0x1E4 */ UNK_TYPE1 pad1E4[17];
/* 0x1F5 */ u8 unk1F5;
/* 0x1F6 */ UNK_TYPE1 pad1F6[90];
/* 0x250 */ void* unk250; // allocation of 0x20f0 bytes?
/* 0x254 */ UNK_TYPE1 pad254[48];
};

typedef struct {
/* 0x000 */ z_Actor base;
/* 0x144 */ actor_func update;
/* 0x148 */ z_ColCylinder collision;
/* 0x194 */ UNK_TYPE1 pad194[20];
} z_ActorEnAObj;

struct z_ActorEnBom {
/* 0x000 */ z_Actor base;
/* 0x144 */ z_ColCylinder unk144;
/* 0x190 */ z_ColSphereGroup unk190;
/* 0x1B0 */ z_ColSphereGroupElement unk1B0[1];
/* 0x1F0 */ s16 unk1F0;
/* 0x1F2 */ UNK_TYPE1 pad1F2[6];
/* 0x1F8 */ u8 unk1F8;
/* 0x1F9 */ u8 unk1F9;
/* 0x1FA */ UNK_TYPE1 pad1FA[2];
/* 0x1FC */ u8 unk1FC;
/* 0x1FD */ UNK_TYPE1 pad1FD[3];
/* 0x200 */ func_ptr unk200;
};

struct z_ActorEnFirefly {
/* 0x000 */ z_Actor base;
/* 0x144 */ UNK_TYPE1 pad144[28];
/* 0x160 */ f32 unk160;
/* 0x164 */ UNK_TYPE1 pad164[36];
/* 0x188 */ func_ptr updateFunc;
/* 0x18C */ UNK_TYPE1 type;
/* 0x18D */ u8 unk18D;
/* 0x18E */ u8 unk18E;
/* 0x18F */ u8 unk18F;
/* 0x190 */ s16 unk190;
/* 0x192 */ UNK_TYPE1 pad192[338];
/* 0x2E4 */ f32 unk2E4;
/* 0x2E8 */ f32 unk2E8;
/* 0x2EC */ f32 unk2EC;
/* 0x2F0 */ f32 unk2F0;
/* 0x2F4 */ UNK_TYPE1 pad2F4[40];
/* 0x31C */ z_ColSphere collision;
};

typedef struct {
/* 0x000 */ z_Actor base;
/* 0x144 */ actor_func update;
/* 0x148 */ s16 unk148;
/* 0x14A */ UNK_TYPE1 pad14A[2];
/* 0x14C */ s16 unk14C;
/* 0x14E */ s16 unk14E;
/* 0x150 */ s16 unk150;
/* 0x152 */ s16 unk152;
/* 0x154 */ f32 unk154;
/* 0x158 */ z_ColCylinder collision;
/* 0x1A4 */ UNK_TYPE1 pad1A4[4];
} z_ActorEnItem00;

struct z_ActorObjBell {
/* 0x000 */ z_Actor base;
/* 0x144 */ UNK_TYPE1 pad144[24];
/* 0x15C */ z_ColSphere unk15C;
/* 0x1B4 */ z_ColSphere unk1B4;
/* 0x20C */ UNK_TYPE1 pad20C[2];
/* 0x20E */ s16 unk20E;
/* 0x210 */ UNK_TYPE1 pad210[4];
/* 0x214 */ s16 unk214;
/* 0x216 */ UNK_TYPE1 pad216[18];
};

struct z_GlobalContext {
/* 0x00000 */ z_ContextCommon commonVars;
/* 0x000A4 */ s16 currentScene;
/* 0x000A6 */ u8 unkA6;
/* 0x000A7 */ UNK_TYPE1 padA7[9];
/* 0x000B0 */ void* currentSceneVram;
/* 0x000B4 */ UNK_TYPE1 padB4[4];
/* 0x000B8 */ z_View unkB8;
/* 0x00220 */ z_GlobalContext220 unk220[4];
/* 0x00800 */ UNK_TYPE1 pad800[24];
/* 0x00818 */ z_LightingContext lightsContext;
/* 0x00826 */ UNK_TYPE1 pad826[2];
/* 0x00828 */ u32 unk828;
/* 0x0082C */ UNK_TYPE1 pad82C[5236];
/* 0x01CA0 */ z_ActorContext actorContext;
/* 0x01F24 */ z_CutsceneContext cutsceneContext;
/* 0x01F74 */ z_CutsceneEntry* cutsceneList;
/* 0x01F78 */ UNK_TYPE1 pad1F78[10640];
/* 0x04908 */ z_GlobalContext4908 unk4908;
/* 0x169E0 */ UNK_TYPE1 pad169E0[8];
/* 0x169E8 */ z_GlobalContext169E8 unk169E8;
/* 0x16D30 */ UNK_TYPE1 pad16D30[492];
/* 0x16F1C */ u16 unk16F1C;
/* 0x16F1E */ UNK_TYPE1 pad16F1E[226];
/* 0x17000 */ u16 unk17000;
/* 0x17002 */ UNK_TYPE1 pad17002[2];
/* 0x17004 */ z_KankyoContext kankyoContext;
/* 0x170F6 */ UNK_TYPE1 pad170F6[3218];
/* 0x17D88 */ z_SceneContext sceneContext;
/* 0x186E0 */ s8 currentRoom;
/* 0x186E1 */ UNK_TYPE1 pad186E1[5];
/* 0x186E6 */ u8 enablePosLights;
/* 0x186E7 */ UNK_TYPE1 pad186E7[1];
/* 0x186E8 */ u32* meshHeader;
/* 0x186EC */ UNK_TYPE1 pad186EC[116];
/* 0x18760 */ u8 transitionActorCount;
/* 0x18761 */ UNK_TYPE1 pad18761[3];
/* 0x18764 */ z_TransitionActorInit* transitionActorList;
/* 0x18768 */ UNK_TYPE1 pad18768[72];
/* 0x187B0 */ z_Matrix unk187B0;
/* 0x187F0 */ UNK_TYPE1 pad187F0[86];
/* 0x18846 */ u16 sceneNumActorsToLoad;
/* 0x18848 */ u8 numRooms;
/* 0x18849 */ UNK_TYPE1 pad18849[3];
/* 0x1884C */ z_RoomFileLocation* roomAddrs;
/* 0x18850 */ UNK_TYPE1 pad18850[4];
/* 0x18854 */ z_SceneActorInit* sceneActorList;
/* 0x18858 */ UNK_TYPE1 pad18858[4];
/* 0x1885C */ u8* entranceList;
/* 0x18860 */ void* exitList;
/* 0x18864 */ void* pathList;
/* 0x18868 */ UNK_TYPE1 pad18868[4];
/* 0x1886C */ void* textureAnimations;
/* 0x18870 */ UNK_TYPE1 pad18870[4];
/* 0x18874 */ u8 unk18874;
/* 0x18875 */ UNK_TYPE1 pad18875[15];
/* 0x18884 */ z_CollisionContext collisionContext;
/* 0x18B20 */ UNK_TYPE1 pad18B20[820];
/* 0x18E54 */ z_SceneTableEntry* currentSceneTableEntry;
/* 0x18E58 */ UNK_TYPE1 pad18E58[1024];
};


#endif
