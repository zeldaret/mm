#ifndef Z64SCENE_H
#define Z64SCENE_H

#include "ultra64.h"
#include "z64dma.h"
#include "z64cutscene.h"
#include "unk.h"

#define SPAWN_ROT_FLAGS(rotation, flags) (((rotation) << 7) | (flags))

typedef struct {
    /* 0x00 */ uintptr_t vromStart;
    /* 0x04 */ uintptr_t vromEnd;
} RomFile; // size = 0x8

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
    /* 0x04 */ u32 subKeepIndex;
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
    /* 0x01 */ u8  cameraMovement;
    /* 0x04 */ u32 area;
} SCmdMiscSettings;

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

typedef struct {
    /* 0x0 */ Gfx* opaqueDl;
    /* 0x4 */ Gfx* translucentDl;
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

typedef union {
    RoomMeshType0 type0;
    RoomMeshType1 type1;
    RoomMeshType2 type2;
} RoomMesh; // size = 0xC

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

typedef struct {
    struct {
        s8 room;    // Room to switch to
        s8 bgCamDataId; // How the camera reacts during the transition. -2 for spiral staircase. -1 for generic door. 0+ will index scene CamData
    } /* 0x00 */ sides[2]; // 0 = front, 1 = back
    /* 0x04 */ s16   id;
    /* 0x06 */ Vec3s pos;
    /* 0x0C */ s16   rotY;
    /* 0x0E */ u16   params;
} TransitionActorEntry; // size = 0x10

typedef struct {
    /* 0x00 */ u8 numTransitionActors;
    /* 0x04 */ TransitionActorEntry* transitionActorList;
} DoorContext;

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
    /* 0x0 */ s8 sceneNum;
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
} SceneTableEntry; // size = 0x10;

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
    /* 0x4 */ void* textureList;
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
    u8 headerType;
} MeshHeaderBase;

typedef struct {
    MeshHeaderBase base;

    u8 numEntries;
    u32 dListStart;
    u32 dListEnd;
} MeshHeader0;

typedef struct {
    u32 opaqueDList;
    u32 translucentDList;
} MeshEntry0;

typedef struct {
    MeshHeaderBase base;
    u8 format;
    u32 entryRecord;
} MeshHeader1Base;

typedef struct {
    MeshHeader1Base base;
    u32 imagePtr; // 0x08
    u32 unknown; // 0x0C
    u32 unknown2; // 0x10
    u16 bgWidth; // 0x14
    u16 bgHeight; // 0x16
    u8 imageFormat; // 0x18
    u8 imageSize; // 0x19
    u16 imagePal; // 0x1A
    u16 imageFlip; // 0x1C
} MeshHeader1Single;

typedef struct {
    MeshHeader1Base base;
    u8 bgCnt;
    u32 bgRecordPtr;
} MeshHeader1Multi;

typedef struct {
    u16 unknown; // 0x00
    s8 bgID; // 0x02
    u32 imagePtr; // 0x04
    u32 unknown2; // 0x08
    u32 unknown3; // 0x0C
    u16 bgWidth; // 0x10
    u16 bgHeight; // 0x12
    u8 imageFmt; // 0x14
    u8 imageSize; // 0x15
    u16 imagePal; // 0x16
    u16 imageFlip; // 0x18
} BackgroundRecord;

typedef struct {
    s16 playerXMax, playerZMax;
    s16 playerXMin, playerZMin;
    u32 opaqueDList;
    u32 translucentDList;
} MeshEntry2;

typedef struct {
    MeshHeaderBase base;
    u8 numEntries;
    u32 dListStart;
    u32 dListEnd;
} MeshHeader2;

typedef struct {
    /* 0x00 */ u8 count; // number of points in the path
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ Vec3s* points; // Segment Address to the array of points
} Path; // size = 0x8

typedef struct {
    /* 0x00 */ UNK_TYPE2 unk0;
    /* 0x02 */ UNK_TYPE2 unk2;
    /* 0x04 */ UNK_TYPE2 unk4;
    /* 0x06 */ UNK_TYPE2 unk6;
    /* 0x08 */ UNK_TYPE2 unk8;
} MinimapEntry; // size = 0xA

typedef struct {
    /* 0x00 */ MinimapEntry* entry;
    /* 0x04 */ UNK_TYPE unk4;
} MinimapList; // size  = 0x8

typedef struct {
    /* 0x00 */ UNK_TYPE2 unk0;
    /* 0x02 */ UNK_TYPE2 unk2;
    /* 0x04 */ UNK_TYPE2 unk4;
    /* 0x06 */ UNK_TYPE2 unk6;
    /* 0x08 */ UNK_TYPE2 unk8;
} MinimapChest; // size = 0xA

typedef struct {
    /* 0x0 */ s16 setting;
    /* 0x2 */ s16 numData;
    /* 0x4 */ Vec3s* data;
} CsCamData; // size = 0x8

typedef CsCamData CsCameraEntry; // TODO: Remove once ZAPD updates its structs

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
    /* Command: 0x17 */ SCmdMiscSettings      miscSettings;
    /* Command: 0x18 */ SCmdAltHeaders        altHeaders;
    /* Command: 0x19 */ SCmdWorldMapVisited   worldMapVisited;
    /* Command: 0x1A */ SCmdTextureAnimations textureAnimations;
    /* Command: 0x1B */ SCmdCutsceneActorList cutsceneActorList;
    /* Command: 0x1C */ SCmdMinimapSettings   minimapSettings;
    /* Command: 0x1D */ // Unused
    /* Command: 0x1E */ SCmdMinimapChests     minimapChests;
} SceneCmd; // size = 0x8

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
    /* 0x70 */ SCENE_ALLEY,
    /* 0x71 */ SCENE_MAX
} SceneID;

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
    /* 0x0A */ SCENE_CMD_ID_MESH,
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
    /* 0x19 */ SCENE_CMD_ID_MISC_SETTINGS,
    /* 0x1A */ SCENE_CMD_ID_ANIMATED_MATERIAL_LIST,
    /* 0x1B */ SCENE_CMD_ID_ACTOR_CUTSCENE_LIST,
    /* 0x1C */ SCENE_CMD_ID_MINIMAP_INFO,
    /* 0x1D */ SCENE_CMD_ID_UNUSED_1D,
    /* 0x1E */ SCENE_CMD_ID_MINIMAP_COMPASS_ICON_INFO,
    /* 0x1F */ SCENE_CMD_MAX
} SceneCommandTypeID;

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

#define SCENE_CMD_SPECIAL_FILES(elfMessageFile, keepObjectId) \
    { SCENE_CMD_ID_SPECIAL_FILES, elfMessageFile, CMD_W(keepObjectId) }

#define SCENE_CMD_ROOM_BEHAVIOR(currRoomUnk3, currRoomUnk2, currRoomUnk5, msgCtxunk12044, enablePosLights,  \
                                kankyoContextUnkE2)                                                         \
    {                                                                                                       \
        SCENE_CMD_ID_ROOM_BEHAVIOR, currRoomUnk3,                                                           \
            currRoomUnk2 | _SHIFTL(currRoomUnk5, 8, 1) | _SHIFTL(msgCtxunk12044, 10, 1) | \
                _SHIFTL(enablePosLights, 11, 1) | _SHIFTL(kankyoContextUnkE2, 12, 1)                        \
    }

#define SCENE_CMD_UNK_09() \
    { SCENE_CMD_ID_UNK_09, 0, CMD_W(0) }

#define SCENE_CMD_MESH(meshHeader) \
    { SCENE_CMD_ID_MESH, 0, CMD_PTR(meshHeader) }

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

#define SCENE_CMD_SOUND_SETTINGS(audioSessionId, nighttimeSfx, bgmId) \
    { SCENE_CMD_ID_SOUND_SETTINGS, audioSessionId, CMD_BBBB(0, 0, nighttimeSfx, bgmId) }

#define SCENE_CMD_ECHO_SETTINGS(echo) \
    { SCENE_CMD_ID_ECHO_SETTINGS, 0, CMD_BBBB(0, 0, 0, echo) }

#define SCENE_CMD_CUTSCENE_LIST(numCutscene, cutsceneList) \
    { SCENE_CMD_ID_CUTSCENE_LIST, numCutscene, CMD_PTR(cutsceneList) }

#define SCENE_CMD_ALTERNATE_HEADER_LIST(alternateHeaderList) \
    { SCENE_CMD_ID_ALTERNATE_HEADER_LIST, 0, CMD_PTR(alternateHeaderList) }

#define SCENE_CMD_MISC_SETTINGS() \
    { SCENE_CMD_ID_MISC_SETTINGS, 0, CMD_W(0) }

#define SCENE_CMD_ANIMATED_MATERIAL_LIST(matAnimList) \
    { SCENE_CMD_ID_ANIMATED_MATERIAL_LIST, 0, CMD_PTR(matAnimList) }

#define SCENE_CMD_ACTOR_CUTSCENE_LIST(actorCutsceneCount, actorCutsceneList) \
    { SCENE_CMD_ID_ACTOR_CUTSCENE_LIST, actorCutsceneCount, CMD_PTR(actorCutsceneList) }

#define SCENE_CMD_MINIMAP_INFO(minimapInfo) \
    { SCENE_CMD_ID_MINIMAP_INFO, 0, CMD_PTR(minimapInfo) }

#define SCENE_CMD_MINIMAP_COMPASS_ICON_INFO(compassIconCount, compassIconInfo) \
    { SCENE_CMD_ID_MINIMAP_COMPASS_ICON_INFO, compassIconCount, CMD_PTR(compassIconInfo) }

#endif
