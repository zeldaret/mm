#ifndef Z64SCENE_H
#define Z64SCENE_H

#include "ultra64.h"
#include "z64dma.h"
#include "z64cutscene.h"
#include "unk.h"

#define SPAWN_ROT_FLAGS(rotation, flags) (((rotation) << 7) | (flags))

typedef struct {
    /* 0x0 */ uintptr_t vromStart;
    /* 0x4 */ uintptr_t vromEnd;
} RomFile; // size = 0x8

#define ROOM_DRAW_OPA (1 << 0)
#define ROOM_DRAW_XLU (1 << 1)

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ u32 data2;
} SCmdBase; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdSpawnList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdActorList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdCsCameraList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdColHeader; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdRoomList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x2 */ UNK_TYPE1 pad2[2];
    /* 0x4 */ s8  west;
    /* 0x5 */ s8  vertical;
    /* 0x6 */ s8  south;
    /* 0x7 */ u8  clothIntensity;
} SCmdWindSettings; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdEntranceList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  naviQuestHintFileId;
    /* 0x4 */ u32 subKeepIndex;
} SCmdSpecialFiles; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  gpFlag1;
    /* 0x4 */ u32 gpFlag2;
} SCmdRoomBehavior; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdMesh; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdObjectList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdLightList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdPathList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdTransiActorList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdLightSettingList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x2 */ UNK_TYPE1 pad2[2];
    /* 0x4 */ u8  hour;
    /* 0x5 */ u8  min;
    /* 0x6 */ u8  timeSpeed;
} SCmdTimeSettings; // size = 0x7

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x2 */ UNK_TYPE1 pad2[2];
    /* 0x4 */ u8  skyboxId;
    /* 0x5 */ u8  unk5;
    /* 0x6 */ u8  unk6;
} SCmdSkyboxSettings; // size = 0x7

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x2 */ UNK_TYPE1 pad2[2];
    /* 0x4 */ u8  unk4;
    /* 0x5 */ u8  unk5;
} SCmdSkyboxDisables; // size = 0x6

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdExitList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ u32 data2;
} SCmdEndMarker; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  specId;
    /* 0x2 */ UNK_TYPE1 unk_02[4];
    /* 0x6 */ u8  ambienceId;
    /* 0x7 */ u8  seqId;
} SCmdSoundSettings; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x2 */ UNK_TYPE1 unk_02[5];
    /* 0x7 */ u8  echo;
} SCmdEchoSettings; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdCutsceneData; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  sceneCsCount;
    /* 0x4 */ void* segment;
} SCmdCutsceneList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdAltHeaders; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ UNK_TYPE1 pad[7];
} SCmdRegionVisited; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdTextureAnimations; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdCutsceneActorList; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  data1;
    /* 0x4 */ void* segment;
} SCmdMinimapSettings; // size = 0x8

typedef struct {
    /* 0x0 */ u8  code;
    /* 0x1 */ u8  num;
    /* 0x4 */ void* segment;
} SCmdMinimapChests; // size = 0x8

typedef enum {
    /* 0 */ ROOM_SHAPE_TYPE_NORMAL,
    /* 1 */ ROOM_SHAPE_TYPE_IMAGE,
    /* 2 */ ROOM_SHAPE_TYPE_CULLABLE,
    /* 3 */ ROOM_SHAPE_TYPE_NONE,
    /* 4 */ ROOM_SHAPE_TYPE_MAX
} RoomShapeType;

typedef struct {
    /* 0x0 */ u8 type;
} RoomShapeBase; // size = 0x1

typedef struct {
    /* 0x0 */ Gfx* opa;
    /* 0x4 */ Gfx* xlu;
} RoomShapeDListsEntry; // size = 0x8

typedef struct {
    /* 0x0 */ RoomShapeBase base;
    /* 0x1 */ u8 numEntries;
    /* 0x4 */ RoomShapeDListsEntry* entries;
    /* 0x8 */ RoomShapeDListsEntry* entriesEnd;
} RoomShapeNormal; // size = 0xC

typedef enum {
    /* 1 */ ROOM_SHAPE_IMAGE_AMOUNT_SINGLE = 1,
    /* 2 */ ROOM_SHAPE_IMAGE_AMOUNT_MULTI
} RoomShapeImageAmountType;

typedef struct {
    /* 0x0 */ RoomShapeBase base;
    /* 0x1 */ u8 amountType; // uses `RoomShapeImageAmountType`
    /* 0x4 */ RoomShapeDListsEntry* entry;
} RoomShapeImageBase; // size = 0x8

typedef struct {
    /* 0x00 */ RoomShapeImageBase base;
    /* 0x08 */ void* source;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ void* tlut;
    /* 0x14 */ u16 width;
    /* 0x16 */ u16 height;
    /* 0x18 */ u8 fmt;
    /* 0x19 */ u8 siz;
    /* 0x1A */ u16 tlutMode;
    /* 0x1C */ u16 tlutCount;
} RoomShapeImageSingle; // size = 0x20

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 bgCamIndex; // the bg cam index this entry is for
    /* 0x04 */ void* source;
    /* 0x08 */ u32 unk_0C;
    /* 0x0C */ void* tlut;
    /* 0x10 */ u16 width;
    /* 0x12 */ u16 height;
    /* 0x14 */ u8 fmt;
    /* 0x15 */ u8 siz;
    /* 0x16 */ u16 tlutMode;
    /* 0x18 */ u16 tlutCount;
} RoomShapeImageMultiBgEntry; // size = 0x1C

typedef struct {
    /* 0x0 */ RoomShapeImageBase base;
    /* 0x8 */ u8 numBackgrounds;
    /* 0xC */ RoomShapeImageMultiBgEntry* backgrounds;
} RoomShapeImageMulti; // size = 0x10

typedef struct {
    /* 0x0 */ Vec3s boundsSphereCenter;
    /* 0x6 */ s16 boundsSphereRadius;
    /* 0x8 */ Gfx* opa;
    /* 0xC */ Gfx* xlu;
} RoomShapeCullableEntry; // size = 0x10

typedef struct {
    /* 0x0 */ RoomShapeBase base;
    /* 0x1 */ u8 numEntries;
    /* 0x4 */ RoomShapeCullableEntry* entries;
    /* 0x8 */ RoomShapeCullableEntry* entriesEnd;
} RoomShapeCullable; // size = 0xC

typedef union {
    RoomShapeBase base;
    RoomShapeNormal normal;
    union {
        RoomShapeImageBase base;
        RoomShapeImageSingle single;
        RoomShapeImageMulti multi;
    } image;
    RoomShapeCullable cullable;
} RoomShape; // "Ground Shape"

// TODO: update ZAPD
#define SCENE_CMD_MESH SCENE_CMD_ROOM_SHAPE

// TODO: Check which ones don't exist
typedef enum {
    /* 0 */ ROOM_BEHAVIOR_TYPE1_0,
    /* 1 */ ROOM_BEHAVIOR_TYPE1_1,
    /* 2 */ ROOM_BEHAVIOR_TYPE1_2,
    /* 3 */ ROOM_BEHAVIOR_TYPE1_3, // unused
    /* 4 */ ROOM_BEHAVIOR_TYPE1_4,
    /* 5 */ ROOM_BEHAVIOR_TYPE1_5
} RoomBehaviorType1;

typedef enum {
    /* 0 */ ROOM_BEHAVIOR_TYPE2_0,
    /* 1 */ ROOM_BEHAVIOR_TYPE2_1,
    /* 2 */ ROOM_BEHAVIOR_TYPE2_2,
    /* 3 */ ROOM_BEHAVIOR_TYPE2_HOT,
    /* 4 */ ROOM_BEHAVIOR_TYPE2_4,
    /* 5 */ ROOM_BEHAVIOR_TYPE2_5,
    /* 6 */ ROOM_BEHAVIOR_TYPE2_6
} RoomBehaviorType2;

typedef struct {
    /* 0x00 */ s8 num;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 behaviorType2;
    /* 0x03 */ u8 behaviorType1;
    /* 0x04 */ s8 echo;
    /* 0x05 */ u8 lensMode;
    /* 0x06 */ u8 enablePosLights;
    /* 0x07 */ UNK_TYPE1 pad7[0x1];
    /* 0x08 */ RoomShape* roomShape;
    /* 0x0C */ void* segment;
    /* 0x10 */ UNK_TYPE1 pad10[0x4];
} Room; // size = 0x14

typedef struct {
    /* 0x00 */ Room curRoom;
    /* 0x14 */ Room prevRoom;
    /* 0x28 */ void* roomMemPages[2]; // In a scene with transitions, roomMemory is split between two pages that toggle each transition. This is one continuous range, as the second page allocates from the end
    /* 0x30 */ u8 activeMemPage; // 0 - First page in memory, 1 - Second page
    /* 0x31 */ s8 status;
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

typedef void(*RoomDrawHandler)(struct PlayState* play, Room* room, u32 flags);

typedef struct TransitionActorEntry {
    struct {
        s8 room;    // Room to switch to
        s8 bgCamIndex; // How the camera reacts during the transition. -2 for spiral staircase. -1 for generic door. 0+ will index scene CamData
    } /* 0x0 */ sides[2]; // 0 = front, 1 = back
    /* 0x4 */ s16 id;
    /* 0x6 */ Vec3s pos;
    /* 0xC */ s16 rotY;
    /* 0xE */ u16 params;
} TransitionActorEntry; // size = 0x10

typedef struct {
    /* 0x0 */ u8 numTransitionActors;
    /* 0x4 */ TransitionActorEntry* transitionActorList;
} DoorContext; // size = 0x8

typedef struct {
    /* 0x0 */ s16 id;
    /* 0x2 */ Vec3s pos;
    /* 0x8 */ Vec3s rot;
    /* 0xE */ s16 params;
} ActorEntry; // size = 0x10

typedef struct {
    /* 0x0 */ u8 spawn;
    /* 0x1 */ u8 room;
} EntranceEntry; // size = 0x2

typedef struct {
    /* 0x0 */ s8 sceneId;
    /* 0x1 */ s8 spawnNum;
    /* 0x2 */ u16 flags;
} EntranceTableEntry; // size = 0x4

typedef struct {
    /* 0x0 */ u32 tableCount : 8; // unused
    /* 0x4 */ EntranceTableEntry** table;
    /* 0x8 */ char* name; // unused
} SceneEntranceTableEntry; // size = 0xC

typedef struct {
    /* 0x00 */ s16 id; // Negative ids mean that the object is unloaded
    /* 0x02 */ UNK_TYPE1 pad2[0x2];
    /* 0x04 */ void* segment;
    /* 0x08 */ DmaRequest dmaReq;
    /* 0x28 */ OSMesgQueue loadQueue;
    /* 0x40 */ OSMesg loadMsg;
} ObjectStatus; // size = 0x44

typedef struct {
    /* 0x0 */ RomFile segment;
    /* 0x8 */ u16 titleTextId;
    /* 0xA */ u8 unk_A;
    /* 0xB */ u8 drawConfig;
    /* 0xC */ u8 unk_C;
    /* 0xD */ u8 unk_D;
} SceneTableEntry; // size = 0x10

typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
    /* 0x4 */ u8 lodFrac;
} F3DPrimColor; // size = 0x5

typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} F3DEnvColor; // size = 0x4

typedef struct {
    /* 0x0 */ u16 keyFrameLength;
    /* 0x2 */ u16 keyFrameCount;
    /* 0x4 */ F3DPrimColor* primColors;
    /* 0x8 */ F3DEnvColor* envColors;
    /* 0xC */ u16* keyFrames;
} AnimatedMatColorParams; // size = 0x10

typedef struct {
    /* 0x0 */ s8 xStep;
    /* 0x1 */ s8 yStep;
    /* 0x2 */ u8 width;
    /* 0x3 */ u8 height;
} AnimatedMatTexScrollParams; // size = 0x4

typedef struct {
    /* 0x0 */ u16 keyFrameLength;
    /* 0x4 */ TexturePtr* textureList;
    /* 0x8 */ u8* textureIndexList;
} AnimatedMatTexCycleParams; // size = 0xC

typedef struct {
    /* 0x000 */ void* spaceStart;
    /* 0x004 */ void* spaceEnd;
    /* 0x008 */ u8 num;
    /* 0x009 */ u8 spawnedObjectCount;
    /* 0x00A */ u8 mainKeepIndex;
    /* 0x00B */ u8 subKeepIndex;
    /* 0x00C */ ObjectStatus status[OBJECT_EXCHANGE_BANK_MAX];
} ObjectContext; // size = 0x958

typedef struct {
    /* 0x0 */ u8 count; // number of points in the path
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ Vec3s* points; // Segment Address to the array of points
} Path; // size = 0x8

typedef struct {
    /* 0x0 */ UNK_TYPE2 unk0;
    /* 0x2 */ UNK_TYPE2 unk2;
    /* 0x4 */ UNK_TYPE2 unk4;
    /* 0x6 */ UNK_TYPE2 unk6;
    /* 0x8 */ UNK_TYPE2 unk8;
} MinimapEntry; // size = 0xA

typedef struct {
    /* 0x0 */ MinimapEntry* entry;
    /* 0x4 */ s16 unk4;
} MinimapList; // size  = 0x8

typedef struct {
    /* 0x0 */ UNK_TYPE2 unk0;
    /* 0x2 */ UNK_TYPE2 unk2;
    /* 0x4 */ UNK_TYPE2 unk4;
    /* 0x6 */ UNK_TYPE2 unk6;
    /* 0x8 */ UNK_TYPE2 unk8;
} MinimapChest; // size = 0xA

// TODO: consider merging with bgCamInfo?
typedef struct {
    /* 0x0 */ s16 setting; // camera setting described by CameraSettingType enum
    /* 0x2 */ s16 count;
    /* 0x4 */ Vec3s* actorCsCamFuncData; // s16 data grouped in threes
} ActorCsCamInfo; // size = 0x8

typedef ActorCsCamInfo CsCameraEntry; // TODO: Remove once ZAPD updates its structs

typedef union {
    /* Command: N/A  */ SCmdBase              base;
    /* Command: 0x00 */ SCmdSpawnList         spawnList;
    /* Command: 0x01 */ SCmdActorList         actorList;
    /* Command: 0x02 */ SCmdCsCameraList      actorCsCamList;
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
    /* Command: 0x17 */ SCmdCutsceneList      cutsceneList;
    /* Command: 0x18 */ SCmdAltHeaders        altHeaders;
    /* Command: 0x19 */ SCmdRegionVisited     regionVisited;
    /* Command: 0x1A */ SCmdTextureAnimations textureAnimations;
    /* Command: 0x1B */ SCmdCutsceneActorList cutsceneActorList;
    /* Command: 0x1C */ SCmdMinimapSettings   minimapSettings;
    /* Command: 0x1D */ // Unused
    /* Command: 0x1E */ SCmdMinimapChests     minimapChests;
} SceneCmd; // size = 0x8

// Sets cursor point options on the world map
typedef enum {
    /* 0x0 */ REGION_GREAT_BAY,
    /* 0x1 */ REGION_ZORA_HALL,
    /* 0x2 */ REGION_ROMANI_RANCH,
    /* 0x3 */ REGION_DEKU_PALACE,
    /* 0x4 */ REGION_WOODFALL,
    /* 0x5 */ REGION_CLOCK_TOWN,
    /* 0x6 */ REGION_SNOWHEAD,
    /* 0x7 */ REGION_IKANA_GRAVEYARD,
    /* 0x8 */ REGION_IKANA_CANYON,
    /* 0x9 */ REGION_GORON_VILLAGE,
    /* 0xA */ REGION_STONE_TOWER,
    /* 0xB */ REGION_MAX
} RegionId;

// Sets warp points for owl statues
typedef enum {
    /* 0x0 */ OWL_WARP_GREAT_BAY_COAST,
    /* 0x1 */ OWL_WARP_ZORA_CAPE,
    /* 0x2 */ OWL_WARP_SNOWHEAD,
    /* 0x3 */ OWL_WARP_MOUNTAIN_VILLAGE,
    /* 0x4 */ OWL_WARP_CLOCK_TOWN,
    /* 0x5 */ OWL_WARP_MILK_ROAD,
    /* 0x6 */ OWL_WARP_WOODFALL,
    /* 0x7 */ OWL_WARP_SOUTHERN_SWAMP,
    /* 0x8 */ OWL_WARP_IKANA_CANYON,
    /* 0x9 */ OWL_WARP_STONE_TOWER,
    /* 0xA */ OWL_WARP_ENTRANCE, // Special index for warping to the entrance of a scene
    /* 0xB */ OWL_WARP_MAX
} OwlWarpId;

// Sets cloud visibility on the world map
typedef enum {
    /* 0 */ TINGLE_MAP_CLOCK_TOWN,
    /* 1 */ TINGLE_MAP_WOODFALL,
    /* 2 */ TINGLE_MAP_SNOWHEAD,
    /* 3 */ TINGLE_MAP_ROMANI_RANCH,
    /* 4 */ TINGLE_MAP_GREAT_BAY,
    /* 5 */ TINGLE_MAP_STONE_TOWER,
    /* 6 */ TINGLE_MAP_MAX
} TingleMapId;

typedef enum {
    /* 0x00 */ SCENE_20SICHITAI2, // Southern Swamp (Clear)
    /* 0x01 */ SCENE_UNSET_1,
    /* 0x02 */ SCENE_UNSET_2,
    /* 0x03 */ SCENE_UNSET_3,
    /* 0x04 */ SCENE_UNSET_4,
    /* 0x05 */ SCENE_UNSET_5,
    /* 0x06 */ SCENE_UNSET_6,
    /* 0x07 */ SCENE_KAKUSIANA, // Lone Peak Shrine & Grottos
    /* 0x08 */ SCENE_SPOT00, // Cutscene Scene
    /* 0x09 */ SCENE_UNSET_9,
    /* 0x0A */ SCENE_WITCH_SHOP, // Magic Hags' Potion Shop
    /* 0x0B */ SCENE_LAST_BS, // Majora's Lair
    /* 0x0C */ SCENE_HAKASHITA, // Beneath the Graveyard
    /* 0x0D */ SCENE_AYASHIISHOP, // Curiosity Shop
    /* 0x0E */ SCENE_UNSET_E,
    /* 0x0F */ SCENE_UNSET_F,
    /* 0x10 */ SCENE_OMOYA, // Mama's House (Ranch House in PAL) & Barn
    /* 0x11 */ SCENE_BOWLING, // Honey & Darling's Shop
    /* 0x12 */ SCENE_SONCHONOIE, // The Mayor's Residence
    /* 0x13 */ SCENE_IKANA, // Ikana Canyon
    /* 0x14 */ SCENE_KAIZOKU, // Pirates' Fortress
    /* 0x15 */ SCENE_MILK_BAR, // Milk Bar
    /* 0x16 */ SCENE_INISIE_N, // Stone Tower Temple
    /* 0x17 */ SCENE_TAKARAYA, // Treasure Chest Shop
    /* 0x18 */ SCENE_INISIE_R, // Inverted Stone Tower Temple
    /* 0x19 */ SCENE_OKUJOU, // Clock Tower Rooftop
    /* 0x1A */ SCENE_OPENINGDAN, // Before Clock Town
    /* 0x1B */ SCENE_MITURIN, // Woodfall Temple
    /* 0x1C */ SCENE_13HUBUKINOMITI, // Path to Mountain Village
    /* 0x1D */ SCENE_CASTLE, // Ancient Castle of Ikana
    /* 0x1E */ SCENE_DEKUTES, // Deku Scrub Playground
    /* 0x1F */ SCENE_MITURIN_BS, // Odolwa's Lair
    /* 0x20 */ SCENE_SYATEKI_MIZU, // Town Shooting Gallery
    /* 0x21 */ SCENE_HAKUGIN, // Snowhead Temple
    /* 0x22 */ SCENE_ROMANYMAE, // Milk Road
    /* 0x23 */ SCENE_PIRATE, // Pirates' Fortress Interior
    /* 0x24 */ SCENE_SYATEKI_MORI, // Swamp Shooting Gallery
    /* 0x25 */ SCENE_SINKAI, // Pinnacle Rock
    /* 0x26 */ SCENE_YOUSEI_IZUMI, // Fairy's Fountain
    /* 0x27 */ SCENE_KINSTA1, // Swamp Spider House
    /* 0x28 */ SCENE_KINDAN2, // Oceanside Spider House
    /* 0x29 */ SCENE_TENMON_DAI, // Astral Observatory
    /* 0x2A */ SCENE_LAST_DEKU, // Moon Deku Trial
    /* 0x2B */ SCENE_22DEKUCITY, // Deku Palace
    /* 0x2C */ SCENE_KAJIYA, // Mountain Smithy
    /* 0x2D */ SCENE_00KEIKOKU, // Termina Field
    /* 0x2E */ SCENE_POSTHOUSE, // Post Office
    /* 0x2F */ SCENE_LABO, // Marine Research Lab
    /* 0x30 */ SCENE_DANPEI2TEST, // Beneath the Graveyard (Day 3) and Dampe's House
    /* 0x31 */ SCENE_UNSET_31,
    /* 0x32 */ SCENE_16GORON_HOUSE, // Goron Shrine
    /* 0x33 */ SCENE_33ZORACITY, // Zora Hall
    /* 0x34 */ SCENE_8ITEMSHOP, // Trading Post
    /* 0x35 */ SCENE_F01, // Romani Ranch
    /* 0x36 */ SCENE_INISIE_BS, // Twinmold's Lair
    /* 0x37 */ SCENE_30GYOSON, // Great Bay Coast
    /* 0x38 */ SCENE_31MISAKI, // Zora Cape
    /* 0x39 */ SCENE_TAKARAKUJI, // Lottery Shop
    /* 0x3A */ SCENE_UNSET_3A,
    /* 0x3B */ SCENE_TORIDE, // Pirates' Fortress Moat
    /* 0x3C */ SCENE_FISHERMAN, // Fisherman's Hut
    /* 0x3D */ SCENE_GORONSHOP, // Goron Shop
    /* 0x3E */ SCENE_DEKU_KING, // Deku King's Chamber
    /* 0x3F */ SCENE_LAST_GORON, // Moon Goron Trial
    /* 0x40 */ SCENE_24KEMONOMITI, // Road to Southern Swamp
    /* 0x41 */ SCENE_F01_B, // Doggy Racetrack
    /* 0x42 */ SCENE_F01C, // Cucco Shack
    /* 0x43 */ SCENE_BOTI, // Ikana Graveyard
    /* 0x44 */ SCENE_HAKUGIN_BS, // Goht's Lair
    /* 0x45 */ SCENE_20SICHITAI, // Southern Swamp (poison)
    /* 0x46 */ SCENE_21MITURINMAE, // Woodfall
    /* 0x47 */ SCENE_LAST_ZORA, // Moon Zora Trial
    /* 0x48 */ SCENE_11GORONNOSATO2, // Goron Village (spring)
    /* 0x49 */ SCENE_SEA, // Great Bay Temple
    /* 0x4A */ SCENE_35TAKI, // Waterfall Rapids
    /* 0x4B */ SCENE_REDEAD, // Beneath the Well
    /* 0x4C */ SCENE_BANDROOM, // Zora Hall Rooms
    /* 0x4D */ SCENE_11GORONNOSATO, // Goron Village (winter)
    /* 0x4E */ SCENE_GORON_HAKA, // Goron Graveyard
    /* 0x4F */ SCENE_SECOM, // Sakon's Hideout
    /* 0x50 */ SCENE_10YUKIYAMANOMURA, // Mountain Village (winter)
    /* 0x51 */ SCENE_TOUGITES, // Ghost Hut
    /* 0x52 */ SCENE_DANPEI, // Deku Shrine
    /* 0x53 */ SCENE_IKANAMAE, // Road to Ikana
    /* 0x54 */ SCENE_DOUJOU, // Swordsman's School
    /* 0x55 */ SCENE_MUSICHOUSE, // Music Box House
    /* 0x56 */ SCENE_IKNINSIDE, // Igos du Ikana's Lair
    /* 0x57 */ SCENE_MAP_SHOP, // Tourist Information
    /* 0x58 */ SCENE_F40, // Stone Tower
    /* 0x59 */ SCENE_F41, // Inverted Stone Tower
    /* 0x5A */ SCENE_10YUKIYAMANOMURA2, // Mountain Village (spring)
    /* 0x5B */ SCENE_14YUKIDAMANOMITI, // Path to Snowhead
    /* 0x5C */ SCENE_12HAKUGINMAE, // Snowhead
    /* 0x5D */ SCENE_17SETUGEN, // Path to Goron Village (winter)
    /* 0x5E */ SCENE_17SETUGEN2, // Path to Goron Village (spring)
    /* 0x5F */ SCENE_SEA_BS, // Gyorg's Lair
    /* 0x60 */ SCENE_RANDOM, // Secret Shrine
    /* 0x61 */ SCENE_YADOYA, // Stock Pot Inn
    /* 0x62 */ SCENE_KONPEKI_ENT, // Great Bay Cutscene
    /* 0x63 */ SCENE_INSIDETOWER, // Clock Tower Interior
    /* 0x64 */ SCENE_26SARUNOMORI, // Woods of Mystery
    /* 0x65 */ SCENE_LOST_WOODS, // Lost Woods (Intro)
    /* 0x66 */ SCENE_LAST_LINK, // Moon Link Trial
    /* 0x67 */ SCENE_SOUGEN, // The Moon
    /* 0x68 */ SCENE_BOMYA, // Bomb Shop
    /* 0x69 */ SCENE_KYOJINNOMA, // Giants' Chamber
    /* 0x6A */ SCENE_KOEPONARACE, // Gorman Track
    /* 0x6B */ SCENE_GORONRACE, // Goron Racetrack
    /* 0x6C */ SCENE_TOWN, // East Clock Town
    /* 0x6D */ SCENE_ICHIBA, // West Clock Town
    /* 0x6E */ SCENE_BACKTOWN, // North Clock Town
    /* 0x6F */ SCENE_CLOCKTOWER, // South Clock Town
    /* 0x70 */ SCENE_ALLEY, // Laundry Pool
    /* 0x71 */ SCENE_MAX
} SceneId;

typedef enum {
    /* 0x00 */ ENTR_SCENE_MAYORS_RESIDENCE,
    /* 0x01 */ ENTR_SCENE_MAJORAS_LAIR,
    /* 0x02 */ ENTR_SCENE_MAGIC_HAGS_POTION_SHOP,
    /* 0x03 */ ENTR_SCENE_RANCH_HOUSE,
    /* 0x04 */ ENTR_SCENE_HONEY_AND_DARLINGS_SHOP,
    /* 0x05 */ ENTR_SCENE_BENEATH_THE_GRAVERYARD,
    /* 0x06 */ ENTR_SCENE_SOUTHERN_SWAMP_CLEARED,
    /* 0x07 */ ENTR_SCENE_CURIOSITY_SHOP,
    /* 0x08 */ ENTR_SCENE_UNSET_08,
    /* 0x09 */ ENTR_SCENE_UNSET_09,
    /* 0x0A */ ENTR_SCENE_GROTTOS,
    /* 0x0B */ ENTR_SCENE_UNSET_0B,
    /* 0x0C */ ENTR_SCENE_UNSET_0C,
    /* 0x0D */ ENTR_SCENE_UNSET_0D,
    /* 0x0E */ ENTR_SCENE_CUTSCENE,
    /* 0x0F */ ENTR_SCENE_UNSET_0F,
    /* 0x10 */ ENTR_SCENE_IKANA_CANYON,
    /* 0x11 */ ENTR_SCENE_PIRATES_FORTRESS,
    /* 0x12 */ ENTR_SCENE_MILK_BAR,
    /* 0x13 */ ENTR_SCENE_STONE_TOWER_TEMPLE,
    /* 0x14 */ ENTR_SCENE_TREASURE_CHEST_SHOP,
    /* 0x15 */ ENTR_SCENE_STONE_TOWER_TEMPLE_INVERTED,
    /* 0x16 */ ENTR_SCENE_CLOCK_TOWER_ROOFTOP,
    /* 0x17 */ ENTR_SCENE_OPENING_DUNGEON,
    /* 0x18 */ ENTR_SCENE_WOODFALL_TEMPLE,
    /* 0x19 */ ENTR_SCENE_PATH_TO_MOUNTAIN_VILLAGE,
    /* 0x1A */ ENTR_SCENE_IKANA_CASTLE,
    /* 0x1B */ ENTR_SCENE_DEKU_SCRUB_PLAYGROUND,
    /* 0x1C */ ENTR_SCENE_ODOLWAS_LAIR,
    /* 0x1D */ ENTR_SCENE_TOWN_SHOOTING_GALLERY,
    /* 0x1E */ ENTR_SCENE_SNOWHEAD_TEMPLE,
    /* 0x1F */ ENTR_SCENE_MILK_ROAD,
    /* 0x20 */ ENTR_SCENE_PIRATES_FORTRESS_INTERIOR,
    /* 0x21 */ ENTR_SCENE_SWAMP_SHOOTING_GALLERY,
    /* 0x22 */ ENTR_SCENE_PINNACLE_ROCK,
    /* 0x23 */ ENTR_SCENE_FAIRY_FOUNTAIN,
    /* 0x24 */ ENTR_SCENE_SWAMP_SPIDER_HOUSE,
    /* 0x25 */ ENTR_SCENE_OCEANSIDE_SPIDER_HOUSE,
    /* 0x26 */ ENTR_SCENE_ASTRAL_OBSERVATORY,
    /* 0x27 */ ENTR_SCENE_MOON_DEKU_TRIAL,
    /* 0x28 */ ENTR_SCENE_DEKU_PALACE,
    /* 0x29 */ ENTR_SCENE_MOUNTAIN_SMITHY,
    /* 0x2A */ ENTR_SCENE_TERMINA_FIELD,
    /* 0x2B */ ENTR_SCENE_POST_OFFICE,
    /* 0x2C */ ENTR_SCENE_MARINE_RESEARCH_LAB,
    /* 0x2D */ ENTR_SCENE_DAMPES_HOUSE,
    /* 0x2E */ ENTR_SCENE_UNSET_2E,
    /* 0x2F */ ENTR_SCENE_GORON_SHRINE,
    /* 0x30 */ ENTR_SCENE_ZORA_HALL,
    /* 0x31 */ ENTR_SCENE_TRADING_POST,
    /* 0x32 */ ENTR_SCENE_ROMANI_RANCH,
    /* 0x33 */ ENTR_SCENE_TWINMOLDS_LAIR,
    /* 0x34 */ ENTR_SCENE_GREAT_BAY_COAST,
    /* 0x35 */ ENTR_SCENE_ZORA_CAPE,
    /* 0x36 */ ENTR_SCENE_LOTTERY_SHOP,
    /* 0x37 */ ENTR_SCENE_UNSET_37,
    /* 0x38 */ ENTR_SCENE_PIRATES_FORTRESS_EXTERIOR,
    /* 0x39 */ ENTR_SCENE_FISHERMANS_HUT,
    /* 0x3A */ ENTR_SCENE_GORON_SHOP,
    /* 0x3B */ ENTR_SCENE_DEKU_KINGS_CHAMBER,
    /* 0x3C */ ENTR_SCENE_MOON_GORON_TRIAL,
    /* 0x3D */ ENTR_SCENE_ROAD_TO_SOUTHERN_SWAMP,
    /* 0x3E */ ENTR_SCENE_DOGGY_RACETRACK,
    /* 0x3F */ ENTR_SCENE_CUCCO_SHACK,
    /* 0x40 */ ENTR_SCENE_IKANA_GRAVEYARD,
    /* 0x41 */ ENTR_SCENE_GOHTS_LAIR,
    /* 0x42 */ ENTR_SCENE_SOUTHERN_SWAMP_POISONED,
    /* 0x43 */ ENTR_SCENE_WOODFALL,
    /* 0x44 */ ENTR_SCENE_MOON_ZORA_TRIAL,
    /* 0x45 */ ENTR_SCENE_GORON_VILLAGE_SPRING,
    /* 0x46 */ ENTR_SCENE_GREAT_BAY_TEMPLE,
    /* 0x47 */ ENTR_SCENE_WATERFALL_RAPIDS,
    /* 0x48 */ ENTR_SCENE_BENEATH_THE_WELL,
    /* 0x49 */ ENTR_SCENE_ZORA_HALL_ROOMS,
    /* 0x4A */ ENTR_SCENE_GORON_VILLAGE_WINTER,
    /* 0x4B */ ENTR_SCENE_GORON_GRAVERYARD,
    /* 0x4C */ ENTR_SCENE_SAKONS_HIDEOUT,
    /* 0x4D */ ENTR_SCENE_MOUNTAIN_VILLAGE_WINTER,
    /* 0x4E */ ENTR_SCENE_GHOST_HUT,
    /* 0x4F */ ENTR_SCENE_DEKU_SHRINE,
    /* 0x50 */ ENTR_SCENE_ROAD_TO_IKANA,
    /* 0x51 */ ENTR_SCENE_SWORDMANS_SCHOOL,
    /* 0x52 */ ENTR_SCENE_MUSIC_BOX_HOUSE,
    /* 0x53 */ ENTR_SCENE_IGOS_DU_IKANAS_LAIR,
    /* 0x54 */ ENTR_SCENE_TOURIST_INFORMATION,
    /* 0x55 */ ENTR_SCENE_STONE_TOWER,
    /* 0x56 */ ENTR_SCENE_STONE_TOWER_INVERTED,
    /* 0x57 */ ENTR_SCENE_MOUNTAIN_VILLAGE_SPRING,
    /* 0x58 */ ENTR_SCENE_PATH_TO_SNOWHEAD,
    /* 0x59 */ ENTR_SCENE_SNOWHEAD,
    /* 0x5A */ ENTR_SCENE_PATH_TO_GORON_VILLAGE_WINTER,
    /* 0x5B */ ENTR_SCENE_PATH_TO_GORON_VILLAGE_SPRING,
    /* 0x5C */ ENTR_SCENE_GYORGS_LAIR,
    /* 0x5D */ ENTR_SCENE_SECRET_SHRINE,
    /* 0x5E */ ENTR_SCENE_STOCK_POT_INN,
    /* 0x5F */ ENTR_SCENE_GREAT_BAY_CUTSCENE,
    /* 0x60 */ ENTR_SCENE_CLOCK_TOWER_INTERIOR,
    /* 0x61 */ ENTR_SCENE_WOODS_OF_MYSTERY,
    /* 0x62 */ ENTR_SCENE_LOST_WOODS,
    /* 0x63 */ ENTR_SCENE_MOON_LINK_TRIAL,
    /* 0x64 */ ENTR_SCENE_THE_MOON,
    /* 0x65 */ ENTR_SCENE_BOMB_SHOP,
    /* 0x66 */ ENTR_SCENE_GIANTS_CHAMBER,
    /* 0x67 */ ENTR_SCENE_GORMAN_TRACK,
    /* 0x68 */ ENTR_SCENE_GORON_RACETRACK,
    /* 0x69 */ ENTR_SCENE_EAST_CLOCK_TOWN,
    /* 0x6A */ ENTR_SCENE_WEST_CLOCK_TOWN,
    /* 0x6B */ ENTR_SCENE_NORTH_CLOCK_TOWN,
    /* 0x6C */ ENTR_SCENE_SOUTH_CLOCK_TOWN,
    /* 0x6D */ ENTR_SCENE_LAUNDRY_POOL,
    /* 0x6E */ ENTR_SCENE_MAX
} EntranceSceneId;

/*
* 0xFE00:  Index into sSceneEntranceTable (Scene)
* 0x01F0:  Index into the scenes specific entrance table (Spawn)
* 0x000F:  Index into the specific entrance table (Layer), stored seperately in sceneLayer
*/
#define ENTRANCE(scene, spawn) ((((ENTR_SCENE_##scene) & 0x7F) << 9) | (((spawn) & 0x1F) << 4))

// SceneTableEntry draw configs
typedef enum {
    /* 0 */ SCENE_DRAW_CFG_DEFAULT,
    /* 1 */ SCENE_DRAW_CFG_MAT_ANIM,
    /* 2 */ SCENE_DRAW_CFG_NOTHING,
    /* 3 */ SCENE_DRAW_CFG_UNUSED_3,
    /* 4 */ SCENE_DRAW_CFG_UNUSED_4,
    /* 5 */ SCENE_DRAW_CFG_UNUSED_5,
    /* 6 */ SCENE_DRAW_CFG_GREAT_BAY_TEMPLE,
    /* 7 */ SCENE_DRAW_CFG_MAT_ANIM_MANUAL_STEP
} SceneDrawConfigIds;

// TODO: make ZAPD use this enum for `SCENE_CMD_SPECIAL_FILES`
// Leftover from OoT
typedef enum {
    /* 0 */ NAVI_QUEST_HINTS_NONE,
    /* 1 */ NAVI_QUEST_HINTS_OVERWORLD,
    /* 2 */ NAVI_QUEST_HINTS_DUNGEON
} NaviQuestHintFileId;

// SceneTableEntry commands
typedef enum {
    /* 0x00 */ SCENE_CMD_ID_SPAWN_LIST,
    /* 0x01 */ SCENE_CMD_ID_ACTOR_LIST,
    /* 0x02 */ SCENE_CMD_ID_ACTOR_CUTSCENE_CAM_LIST,
    /* 0x03 */ SCENE_CMD_ID_COL_HEADER,
    /* 0x04 */ SCENE_CMD_ID_ROOM_LIST,
    /* 0x05 */ SCENE_CMD_ID_WIND_SETTINGS,
    /* 0x06 */ SCENE_CMD_ID_ENTRANCE_LIST,
    /* 0x07 */ SCENE_CMD_ID_SPECIAL_FILES,
    /* 0x08 */ SCENE_CMD_ID_ROOM_BEHAVIOR,
    /* 0x09 */ SCENE_CMD_ID_UNK_09,
    /* 0x0A */ SCENE_CMD_ID_ROOM_SHAPE,
    /* 0x0B */ SCENE_CMD_ID_OBJECT_LIST,
    /* 0x0C */ SCENE_CMD_ID_LIGHT_LIST,
    /* 0x0D */ SCENE_CMD_ID_PATH_LIST,
    /* 0x0E */ SCENE_CMD_ID_TRANSI_ACTOR_LIST,
    /* 0x0F */ SCENE_CMD_ID_ENV_LIGHT_SETTINGS,
    /* 0x10 */ SCENE_CMD_ID_TIME_SETTINGS,
    /* 0x11 */ SCENE_CMD_ID_SKYBOX_SETTINGS,
    /* 0x12 */ SCENE_CMD_ID_SKYBOX_DISABLES,
    /* 0x13 */ SCENE_CMD_ID_EXIT_LIST,
    /* 0x14 */ SCENE_CMD_ID_END,
    /* 0x15 */ SCENE_CMD_ID_SOUND_SETTINGS,
    /* 0x16 */ SCENE_CMD_ID_ECHO_SETTINGS,
    /* 0x17 */ SCENE_CMD_ID_CUTSCENE_LIST,
    /* 0x18 */ SCENE_CMD_ID_ALTERNATE_HEADER_LIST,
    /* 0x19 */ SCENE_CMD_ID_SET_REGION_VISITED,
    /* 0x1A */ SCENE_CMD_ID_ANIMATED_MATERIAL_LIST,
    /* 0x1B */ SCENE_CMD_ID_ACTOR_CUTSCENE_LIST,
    /* 0x1C */ SCENE_CMD_ID_MINIMAP_INFO,
    /* 0x1D */ SCENE_CMD_ID_UNUSED_1D,
    /* 0x1E */ SCENE_CMD_ID_MINIMAP_COMPASS_ICON_INFO,
    /* 0x1F */ SCENE_CMD_MAX
} SceneCommandTypeId;

#define SCENE_CMD_SPAWN_LIST(numSpawns, spawnList) \
    { SCENE_CMD_ID_SPAWN_LIST, numSpawns, CMD_PTR(spawnList) }

#define SCENE_CMD_ACTOR_LIST(numActors, actorList) \
    { SCENE_CMD_ID_ACTOR_LIST, numActors, CMD_PTR(actorList) }

#define SCENE_CMD_ACTOR_CUTSCENE_CAM_LIST(numCams, camList) \
    { SCENE_CMD_ID_ACTOR_CUTSCENE_CAM_LIST, numCams, CMD_PTR(camList) }

#define SCENE_CMD_COL_HEADER(colHeader) \
    { SCENE_CMD_ID_COL_HEADER, 0, CMD_PTR(colHeader) }

#define SCENE_CMD_ROOM_LIST(numRooms, roomList) \
    { SCENE_CMD_ID_ROOM_LIST, numRooms, CMD_PTR(roomList) }

#define SCENE_CMD_WIND_SETTINGS(xDir, yDir, zDir, strength) \
    { SCENE_CMD_ID_WIND_SETTINGS, 0, CMD_BBBB(xDir, yDir, zDir, strength) }

#define SCENE_CMD_ENTRANCE_LIST(entranceList) \
    { SCENE_CMD_ID_ENTRANCE_LIST, 0, CMD_PTR(entranceList) }

#define SCENE_CMD_SPECIAL_FILES(naviQuestHintFileId, keepObjectId) \
    { SCENE_CMD_ID_SPECIAL_FILES, naviQuestHintFileId, CMD_W(keepObjectId) }

#define SCENE_CMD_ROOM_BEHAVIOR(curRoomUnk3, curRoomUnk2, curRoomUnk5, msgCtxunk12044, enablePosLights,  \
                                kankyoContextUnkE2)                                                         \
    {                                                                                                       \
        SCENE_CMD_ID_ROOM_BEHAVIOR, curRoomUnk3,                                                           \
            curRoomUnk2 | _SHIFTL(curRoomUnk5, 8, 1) | _SHIFTL(msgCtxunk12044, 10, 1) | \
                _SHIFTL(enablePosLights, 11, 1) | _SHIFTL(kankyoContextUnkE2, 12, 1)                        \
    }

#define SCENE_CMD_UNK_09() \
    { SCENE_CMD_ID_UNK_09, 0, CMD_W(0) }

#define SCENE_CMD_ROOM_SHAPE(roomShape) \
    { SCENE_CMD_ID_ROOM_SHAPE, 0, CMD_PTR(roomShape) }

#define SCENE_CMD_OBJECT_LIST(numObjects, objectList) \
    { SCENE_CMD_ID_OBJECT_LIST, numObjects, CMD_PTR(objectList) }

#define SCENE_CMD_LIGHT_LIST(numLights, lightList) \
    { SCENE_CMD_ID_LIGHT_LIST, numLights, CMD_PTR(lightList) } 

#define SCENE_CMD_PATH_LIST(pathList) \
    { SCENE_CMD_ID_PATH_LIST, 0, CMD_PTR(pathList) }

#define SCENE_CMD_TRANSITION_ACTOR_LIST(numTransitionActors, actorList) \
    { SCENE_CMD_ID_TRANSI_ACTOR_LIST, numTransitionActors, CMD_PTR(actorList) } 

#define SCENE_CMD_ENV_LIGHT_SETTINGS(numLightSettings, lightSettingsList) \
    { SCENE_CMD_ID_ENV_LIGHT_SETTINGS, numLightSettings, CMD_PTR(lightSettingsList) }

#define SCENE_CMD_TIME_SETTINGS(hour, min, speed) \
    { SCENE_CMD_ID_TIME_SETTINGS, 0, CMD_BBBB(hour, min, speed, 0) }

#define SCENE_CMD_SKYBOX_SETTINGS(externalTextureFileId, skyboxId, weather, lightMode) \
    { SCENE_CMD_ID_SKYBOX_SETTINGS, externalTextureFileId, CMD_BBBB(skyboxId, weather, lightMode, 0) }

#define SCENE_CMD_SKYBOX_DISABLES(disableSky, disableSunMoon) \
    { SCENE_CMD_ID_SKYBOX_DISABLES, 0, CMD_BBBB(disableSky, disableSunMoon, 0, 0) }

#define SCENE_CMD_EXIT_LIST(exitList) \
    { SCENE_CMD_ID_EXIT_LIST, 0, CMD_PTR(exitList) }

#define SCENE_CMD_END() \
    { SCENE_CMD_ID_END, 0, CMD_W(0) }

#define SCENE_CMD_SOUND_SETTINGS(specId, ambienceId, seqId) \
    { SCENE_CMD_ID_SOUND_SETTINGS, specId, CMD_BBBB(0, 0, ambienceId, seqId) }

#define SCENE_CMD_ECHO_SETTINGS(echo) \
    { SCENE_CMD_ID_ECHO_SETTINGS, 0, CMD_BBBB(0, 0, 0, echo) }

#define SCENE_CMD_CUTSCENE_LIST(numCutscene, cutsceneList) \
    { SCENE_CMD_ID_CUTSCENE_LIST, numCutscene, CMD_PTR(cutsceneList) }

#define SCENE_CMD_ALTERNATE_HEADER_LIST(alternateHeaderList) \
    { SCENE_CMD_ID_ALTERNATE_HEADER_LIST, 0, CMD_PTR(alternateHeaderList) }

#define SCENE_CMD_MISC_SETTINGS SCENE_CMD_SET_REGION_VISITED // TODO: ZAPD Capatability
#define SCENE_CMD_SET_REGION_VISITED() \
    { SCENE_CMD_ID_SET_REGION_VISITED, 0, CMD_W(0) }

#define SCENE_CMD_ANIMATED_MATERIAL_LIST(matAnimList) \
    { SCENE_CMD_ID_ANIMATED_MATERIAL_LIST, 0, CMD_PTR(matAnimList) }

#define SCENE_CMD_ACTOR_CUTSCENE_LIST(actorCutsceneCount, actorCutsceneList) \
    { SCENE_CMD_ID_ACTOR_CUTSCENE_LIST, actorCutsceneCount, CMD_PTR(actorCutsceneList) }

#define SCENE_CMD_MINIMAP_INFO(minimapInfo) \
    { SCENE_CMD_ID_MINIMAP_INFO, 0, CMD_PTR(minimapInfo) }

#define SCENE_CMD_MINIMAP_COMPASS_ICON_INFO(compassIconCount, compassIconInfo) \
    { SCENE_CMD_ID_MINIMAP_COMPASS_ICON_INFO, compassIconCount, CMD_PTR(compassIconInfo) }

#endif
