#ifndef _Z_BGCHECK_
#define _Z_BGCHECK_

struct GlobalContext;
struct Actor;
struct DynaPolyActor;

#define SS_NULL 0xFFFF

#define COLPOLY_NORMAL_FRAC (1.0f / SHT_MAX)
#define COLPOLY_SNORMAL(x) ((s16)((x) * SHT_MAX))
#define COLPOLY_GET_NORMAL(n) ((n)*COLPOLY_NORMAL_FRAC)
#define COLPOLY_VIA_FLAG_TEST(vIA, flags) ((vIA) & (((flags)&7) << 13))
#define COLPOLY_VTX_INDEX(vI) ((vI)&0x1FFF)

#define DYNAPOLY_INVALIDATE_LOOKUP (1 << 0)

#define BGACTOR_NEG_ONE -1
#define BG_ACTOR_MAX 50
#define BGCHECK_SCENE BG_ACTOR_MAX
#define BGCHECK_Y_MIN -32000.0f
#define BGCHECK_XYZ_ABSMAX 32760.0f
#define BGCHECK_SUBDIV_OVERLAP 50
#define BGCHECK_SUBDIV_MIN 150.0f

#define FUNC_80041EA4_RESPAWN 5
#define FUNC_80041EA4_MOUNT_WALL 6
#define FUNC_80041EA4_STOP 8
#define FUNC_80041EA4_VOID_OUT 12

#define WATERBOX_ROOM(p) ((p >> 13) & 0x3F)

typedef struct {
    u16 head;
} SSList;

typedef struct {
    /* 0x0 */ s16 polyStartIndex;
    /* 0x2 */ SSList ceiling;
    /* 0x4 */ SSList wall;
    /* 0x6 */ SSList floor;
} DynaLookup; // size = 0x8
#define ActorMeshPolyLists DynaLookup

typedef struct {
    /* 0x0 */ SSList floor;
    /* 0x2 */ SSList wall;
    /* 0x4 */ SSList ceiling;
} StaticLookup; // size = 0x6
#define BgMeshSubdivision StaticLookup

typedef struct {
    /* 0x0 */ u32 data[2]; //attributes[2];
} SurfaceType; // size = 0x8
#define BgPolygonAttributes SurfaceType

typedef struct {
    /* 0x0 */ s16 polyId; //polyIndex;
    /* 0x2 */ u16 next;
} SSNode; // size = 0x4
#define BgPolygonLinkedListNode SSNode

typedef struct {
    /* 0x0 */ u16 maxNodes;
    /* 0x2 */ u16 reservedNodes;
    /* 0x4 */ BgPolygonLinkedListNode* nodes;
    /* 0x8 */ u8* polyCheckTbl;
} SSNodeList; // size = 0xC
#define BgScenePolygonLists SSNodeList

typedef struct {
    /* 0x0 */ s16 sceneId;
    ///* 0x2 */ UNK_TYPE1 pad2[0x2];
    /* 0x4 */ u32 memSize;
    // BgCheckSceneMemEntry
} BgSpecialSceneMaxMemory; // size = 0x8

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x2 */ s16 maxNodes;
    /* 0x4 */ s16 maxPolygons;
    /* 0x6 */ s16 maxVertices;
} BgSpecialSceneMaxObjects; // size = 0x8

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x2 */ s16 xSubdivisions;
    /* 0x4 */ s16 ySubdivisions;
    /* 0x6 */ s16 zSubdivisions;
    /* 0x8 */ s32 unk8;
} BgSpecialSceneMeshSubdivision; // size = 0xC

typedef struct {
    /* 0x00 */ Vec3f scale;
    /* 0x0C */ Vec3s rotation;
    /* 0x14 */ Vec3f pos;
} ScaleRotPos; // size = 0x20
#define ActorMeshParams ScaleRotPos

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
    /* 0x4 */ u32 count;
    /* 0x8 */ s32 maxNodes;
} DynaSSNodeList; // size = 0xC
#define BgPolygonLinkedList DynaSSNodeList

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
} WaterBox; // size = 0x10
#define BgWaterBox WaterBox

typedef struct {
    /* 0x0 */ UNK_TYPE1 pad0[0x4];
    /* 0x4 */ BgWaterBox* boxes;
} BgWaterboxList; // size = 0x8

typedef struct {
    SSNode* tbl;
    s32 count;
    s32 max;
} DynaSSNodeList;

typedef struct {
    /* 0x00 */ Vec3s min;
    /* 0x06 */ Vec3s max;
    /* 0x0C */ u16 nbVertices; //numVertices;
    /* 0x10 */ Vec3s* vtxList; //BgVertex* vertices;
    /* 0x14 */ u16 nbPolygons; //numPolygons;
    /* 0x18 */ CollisionPoly* polyList; //polygons;
    /* 0x1C */ BgPolygonAttributes* surfaceTypeList; //attributes;
    /* 0x20 */ UNK_PTR cameraDataList; //cameraData;
    /* 0x24 */ u16 nbWaterBoxes; //numWaterBoxes;
    /* 0x28 */ BgWaterBox* waterboxes;
} CollisionHeader; // size = 0x2C
#define BgMeshHeader CollisionHeader

typedef struct {
    u16 polyStartIndex;
    SSList ceiling;
    SSList wall;
    SSList floor;
} DynaLookup;

typedef struct {
    /* 0x00 */ DynaPolyActor* actor;
    /* 0x04 */ BgMeshHeader* colHeader; //header;
    /* 0x08 */ ActorMeshPolyLists dynaLookup; //polyLists;
    /* 0x10 */ u16 vtxStartIndex; //s16 verticesStartIndex;
    /* 0x12 */ s16 waterboxesStartIndex;
    /* 0x14 */ ActorMeshParams prevTransform; //prevParams;
    /* 0x34 */ ActorMeshParams curTransform; //currParams;
    /* 0x54 */ Sphere16 boundingSphere; //Vec3s averagePos;
    /* 0x5A */ //s16 radiusFromAveragePos;
    /* 0x5C */ f32 minY;
    /* 0x60 */ f32 maxY;
} BgActor; // size = 0x64
#define ActorMesh BgActor

typedef struct {
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ //UNK_TYPE1 pad1[0x3];
    /* 0x0004 */ ActorMesh bgActors[BG_ACTOR_MAX]; //actorMeshArr[50];
    /* 0x138C */ u16 bgActorFlags[BG_ACTOR_MAX]; //flags[50]; // bit 0 - Is mesh active
    /* 0x13F0 */ CollisionPoly* polyList; //polygons;
    /* 0x13F4 */ Vec3s* vtxList; //BgVertex* vertices;
    /* 0x13F8 */ BgWaterboxList waterboxes;
    /* 0x1400 */ BgPolygonLinkedList polyNodes; //polygonList;
    /* 0x140C */ s32 polyNodesMax; //u32 maxNodes;
    /* 0x1410 */ s32 polyListMax; //u32 maxPolygons;
    /* 0x1414 */ s32 vtxListMax; //u32 maxVertices;
    /* 0x1418 */ u32 maxMemory;
    /* 0x141C */ u32 unk141C;
} DynaCollisionContext; // size = 0x1420

struct CollisionContext {
    /* 0x00 */ BgMeshHeader* colHeader;//sceneMesh;
    /* 0x04 */ Vec3f minBounds; //sceneMin;
    /* 0x10 */ Vec3f maxBounds; //sceneMax;
    /* 0x1C */ Vec3i subdivAmount; //s32 xSubdivisions;
    /* 0x20 */ //s32 ySubdivisions;
    /* 0x24 */ //s32 zSubdivisions;
    /* 0x28 */ Vec3f subdivLength; //subdivisionSize;
    /* 0x34 */ Vec3f subdivLengthInv; //inverseSubdivisionSize;
    /* 0x40 */ BgMeshSubdivision* lookupTbl; //subdivisions;
    /* 0x44 */ BgScenePolygonLists polyNodes; //scenePolyLists;
    /* 0x0050 */ DynaCollisionContext dyna;
}; // size = 0x1470
#endif
