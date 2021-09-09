#ifndef _Z64_BGCHECK_H_
#define _Z64_BGCHECK_H_

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
#define DYNA_WATERBOX_MAX 30
#define BGCHECK_SCENE BG_ACTOR_MAX
#define BGCHECK_Y_MIN -32000.0f
#define BGCHECK_XYZ_ABSMAX 32760.0f
#define BGCHECK_SUBDIV_OVERLAP 50
#define BGCHECK_SUBDIV_MIN 150.0f

#define FUNC_80041EA4_RESPAWN 5
#define FUNC_80041EA4_MOUNT_WALL 6
#define FUNC_80041EA4_STOP 8
#define FUNC_80041EA4_VOID_OUT 12

#define WATERBOX_ROOM(p) ((((s32)p) >> 13) & 0x3F)

// bccFlags
#define BGCHECK_CHECK_WALL (1 << 0)
#define BGCHECK_CHECK_FLOOR (1 << 1)
#define BGCHECK_CHECK_CEILING (1 << 2)
#define BGCHECK_CHECK_ONE_FACE (1 << 3)
#define BGCHECK_CHECK_DYNA (1 << 4)
#define BGCHECK_CHECK_ALL \
    (BGCHECK_CHECK_WALL | BGCHECK_CHECK_FLOOR | BGCHECK_CHECK_CEILING | BGCHECK_CHECK_ONE_FACE | BGCHECK_CHECK_DYNA)

// bciFlags
#define BGCHECK_IGNORE_NONE 0
#define BGCHECK_IGNORE_CEILING (1 << 0)
#define BGCHECK_IGNORE_WALL (1 << 1)
#define BGCHECK_IGNORE_FLOOR (1 << 2)

// poly exclusion flags (xpFlags)
#define COLPOLY_IGNORE_NONE 0
#define COLPOLY_IGNORE_CAMERA (1 << 0)
#define COLPOLY_IGNORE_ENTITY (1 << 1)
#define COLPOLY_IGNORE_PROJECTILES (1 << 2)

typedef struct {
    /* 0x00 */ u16 cameraSType;
    /* 0x02 */ s16 numCameras;
    /* 0x04 */ Vec3s* camPosData;
} CamData;

typedef struct {
    u16 head;
} SSList;

typedef struct {
    /* 0x0 */ s16 polyStartIndex;
    /* 0x2 */ SSList ceiling;
    /* 0x4 */ SSList wall;
    /* 0x6 */ SSList floor;
} DynaLookup; // size = 0x8
//#define ActorMeshPolyLists DynaLookup

typedef struct {
    /* 0x0 */ SSList floor;
    /* 0x2 */ SSList wall;
    /* 0x4 */ SSList ceiling;
} StaticLookup; // size = 0x6
//#define BgMeshSubdivision StaticLookup

typedef struct {
    /* 0x0 */ u32 data[2]; //attributes[2];
} SurfaceType; // size = 0x8
//#define BgPolygonAttributes SurfaceType

typedef struct {
    /* 0x0 */ s16 polyId; //polyIndex;
    /* 0x2 */ u16 next;
} SSNode; // size = 0x4
//#define BgPolygonLinkedListNode SSNode

typedef struct {
    /* 0x0 */ u16 max; //maxNodes;
    /* 0x2 */ u16 count; //reservedNodes
    /* 0x4 */ SSNode* tbl;//nodes;
    /* 0x8 */ u8* polyCheckTbl;
} SSNodeList; // size = 0xC
//#define BgScenePolygonLists SSNodeList

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
} BgSpecialSceneMeshSubdivision; // size = 0xC //BgCheckSceneSubdivisionEntry

typedef struct {
    s16 sceneId;
    Vec3s subdivAmount;
    s32 nodeListMax; // if -1, dynamically compute max nodes
} BgCheckSceneSubdivisionEntry;

typedef struct {
    /* 0x00 */ Vec3f scale;
    /* 0x0C */ Vec3s rot;
    /* 0x14 */ Vec3f pos;
} ScaleRotPos; // size = 0x20
//#define ActorMeshParams ScaleRotPos

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
    /* 0x0 */ SSNode* tbl; //nodes
    /* 0x4 */ u32 count;
    /* 0x8 */ s32 maxNodes;
} DynaSSNodeList; // size = 0xC
//#define BgPolygonLinkedList DynaSSNodeList

typedef struct {
    /* 0x0 */ Vec3s pos;
} BgVertex; // size = 0x6

typedef struct {
    /* 0x0 */ Vec3s minPos;
    /* 0x6 */ s16 xLength;
    /* 0x8 */ s16 zLength;
    /* 0xC */ u32 properties;
} WaterBox; // size = 0x10
//#define BgWaterBox WaterBox

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ WaterBox* boxes;
} DynaSSWaterboxList; // size = 0x8
//#define DynaSSWaterboxList BgWaterboxList

typedef struct {
    /* 0x00 */ Vec3s minBounds; //min
    /* 0x06 */ Vec3s maxBounds; //max
    /* 0x0C */ u16 numVertices; //numVertices;
    /* 0x10 */ Vec3s* vtxList; //BgVertex* vertices;
    /* 0x14 */ u16 numPolygons; //numPolygons;
    /* 0x18 */ CollisionPoly* polyList; //polygons;
    /* 0x1C */ SurfaceType* surfaceTypeList; //attributes;
    /* 0x20 */ CamData* cameraDataList; //cameraData;
    /* 0x24 */ u16 numWaterBoxes; //nbWaterBoxes MM
    /* 0x28 */ WaterBox* waterBoxes;
} CollisionHeader; // size = 0x2C
//#define BgMeshHeader CollisionHeader

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ CollisionHeader* colHeader; //header;
    /* 0x08 */ DynaLookup dynaLookup; //polyLists;
    /* 0x10 */ u16 vtxStartIndex; //s16 verticesStartIndex;
    /* 0x12 */ u16 waterboxesStartIndex;
    /* 0x14 */ ScaleRotPos prevTransform; //prevParams;
    /* 0x34 */ ScaleRotPos curTransform; //currParams;
    /* 0x54 */ Sphere16 boundingSphere; //Vec3s averagePos;
    /* 0x5A */ //s16 radiusFromAveragePos;
    /* 0x5C */ f32 minY;
    /* 0x60 */ f32 maxY;
} BgActor; // size = 0x64
//#define ActorMesh BgActor

typedef struct {
    /* 0x0000 */ u8 bitFlag;
    /* 0x0004 */ BgActor bgActors[BG_ACTOR_MAX]; //actorMeshArr[50];
    /* 0x138C */ u16 bgActorFlags[BG_ACTOR_MAX]; //flags[50]; // bit 0 - Is mesh active
    /* 0x13F0 */ CollisionPoly* polyList; //polygons;
    /* 0x13F4 */ Vec3s* vtxList; //BgVertex* vertices;
    /* 0x13F8 */ DynaSSWaterboxList waterboxes; //-> waterBoxList
    /* 0x1400 */ DynaSSNodeList polyNodes; //polygonList;
    /* 0x140C */ s32 polyNodesMax; //u32 maxNodes;
    /* 0x1410 */ s32 polyListMax; //u32 maxPolygons;
    /* 0x1414 */ s32 vtxListMax; //u32 maxVertices;
} DynaCollisionContext; // size = 0x1418

typedef struct {
    /* 0x00 */ CollisionHeader* colHeader;//sceneMesh;
    /* 0x04 */ Vec3f minBounds; //sceneMin;
    /* 0x10 */ Vec3f maxBounds; //sceneMax;
    /* 0x1C */ Vec3i subdivAmount; //s32 xSubdivisions;
    /* 0x20 */ //s32 ySubdivisions;
    /* 0x24 */ //s32 zSubdivisions;
    /* 0x28 */ Vec3f subdivLength; //subdivisionSize;
    /* 0x34 */ Vec3f subdivLengthInv; //inverseSubdivisionSize;
    /* 0x40 */ StaticLookup* lookupTbl; //subdivisions;
    /* 0x44 */ SSNodeList polyNodes; //scenePolyLists;
    /* 0x0050 */ DynaCollisionContext dyna;
    /* 0x1468 */ u32 memSize; //maxMemory
    /* 0x146C */ u32 unk146C;
} CollisionContext; // size = 0x1470

typedef struct {
    /* 0x00 */ struct GlobalContext* globalCtx;
    /* 0x04 */ CollisionContext* colCtx;
    /* 0x08 */ u16 xpFlags;
    /* 0x0C */ CollisionPoly** resultPoly;
    /* 0x10 */ f32 yIntersect;
    /* 0x14 */ Vec3f* pos;
    /* 0x18 */ s32* bgId;
    /* 0x1C */ s32 unk1C; 
    /* 0x20 */ struct Actor* actor;
    /* 0x24 */ u32 unk_24; //oot unk20
    /* 0x28 */ f32 chkDist;
    /* 0x2C */ DynaCollisionContext* dyna;
    /* 0x30 */ SSList* ssList;
} DynaRaycast;

typedef struct {
    /* 0x00 */ struct CollisionContext* colCtx;
    /* 0x04 */ u16 xpFlags;
    /* 0x08 */ DynaCollisionContext* dyna;
    /* 0x0C */ SSList* ssList;
    /* 0x10 */ Vec3f* posA;
    /* 0x14 */ Vec3f* posB;
    /* 0x18 */ Vec3f* posResult;
    /* 0x1C */ CollisionPoly** resultPoly;
    /* 0x20 */ s32 chkOneFace; // bccFlags & 0x8
    /* 0x24 */ f32* distSq;    // distance from posA to poly squared
    /* 0x28 */ f32 chkDist;    // distance from poly
    /* 0x2C */ Actor* actor;
    /* 0x30 */ s32 bgId;
} DynaLineTest;

#endif

typedef struct {
    /* 0x00 */ CollisionPoly* poly;
    /* 0x04 */ Vec3s* vtxList;
    /* 0x08 */ Vec3f* posA;
    /* 0x0C */ Vec3f* posB;
    /* 0x10 */ Vec3f* planeIntersect;
    /* 0x14 */ s32 chkOneFace;
    /* 0x18 */ f32 chkDist;
} func_800C07F0_args;

typedef struct
{
    /* 0x00 */ StaticLookup* lookup;
    /* 0x04 */ SSList* ssList; 
    /* 0x08 */ CollisionContext* colCtx;
    /* 0x0C */ u16 xpFlags1;
    /* 0x0E */ u16 xpFlags2;
    /* 0x10 */ Vec3f* posA;
    /* 0x14 */ Vec3f* posB;
    /* 0x18 */ Vec3f* outPos;
    /* 0x1C */ CollisionPoly* outPoly;
    /* 0x20 */ f32 outDistSq;
    /* 0x24 */ f32 chkDist;
    /* 0x28 */ s32 bccFlags;
    /* 0x2C */ Actor* actor;
} struct_func_800C1D7C;
