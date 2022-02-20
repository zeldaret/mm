#ifndef Z64_BGCHECK_H
#define Z64_BGCHECK_H

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
#define BGCHECK_Y_MAX 32000.0f
#define BGCHECK_Y_MIN -32000.0f
#define BGCHECK_XYZ_ABSMAX 32760.0f
#define BGCHECK_SUBDIV_OVERLAP 50
#define BGCHECK_SUBDIV_MIN 150.0f

#define WATERBOX_ROOM(p) ((((s32)p) >> 13) & 0x3F)

// bccFlags (bgcheck check flags)
#define BGCHECK_CHECK_WALL (1 << 0)
#define BGCHECK_CHECK_FLOOR (1 << 1)
#define BGCHECK_CHECK_CEILING (1 << 2)
#define BGCHECK_CHECK_ONE_FACE (1 << 3)
#define BGCHECK_CHECK_DYNA (1 << 4)
#define BGCHECK_CHECK_ALL \
    (BGCHECK_CHECK_WALL | BGCHECK_CHECK_FLOOR | BGCHECK_CHECK_CEILING | BGCHECK_CHECK_ONE_FACE | BGCHECK_CHECK_DYNA)

// bciFlags (bgcheck ignore flags)
#define BGCHECK_IGNORE_NONE 0
#define BGCHECK_IGNORE_CEILING (1 << 0)
#define BGCHECK_IGNORE_WALL (1 << 1)
#define BGCHECK_IGNORE_FLOOR (1 << 2)

// xpFlags (poly exclusion flags)
#define COLPOLY_IGNORE_NONE 0
#define COLPOLY_IGNORE_CAMERA (1 << 0)
#define COLPOLY_IGNORE_ENTITY (1 << 1)
#define COLPOLY_IGNORE_PROJECTILES (1 << 2)

// Surface Types
#define COLPOLY_SURFACE_GROUND 0
#define COLPOLY_SURFACE_SAND 1
#define COLPOLY_SURFACE_SNOW 14

// CollisionContext flags
#define BGCHECK_FLAG_REVERSE_CONVEYOR_FLOW 1

typedef enum {
    /* 0 */ CONVEYOR_WATER,
    /* 1 */ CONVEYOR_FLOOR
} ConveyorType;

typedef struct {
    /* 0x0 */ Vec3s pos;
} BgVertex; // size = 0x6

typedef struct {
    /* 0x00 */ Vec3f scale;
    /* 0x0C */ Vec3s rot;
    /* 0x14 */ Vec3f pos;
} ScaleRotPos; // size = 0x20

typedef struct CollisionPoly {
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
    /* 0x0 */ u16 setting;
    /* 0x2 */ s16 numData;
    /* 0x4 */ Vec3s* data;
} CamData; // size = 0x8 (BgCamData)

typedef struct {
    /* 0x0 */ Vec3s minPos;
    /* 0x6 */ s16 xLength;
    /* 0x8 */ s16 zLength;
    /* 0xC */ u32 properties;
    // 0x0008_0000 = ?
    // 0x0007_E000 = room index, 0x3F = all rooms
    // 0x0000_1F00 = lighting setting index
    // 0x0000_00FF = CamData index
} WaterBox; // size = 0x10

typedef struct {
    /* 0x0 */ u32 data[2];

    // Word 0
    // 0x8000_0000 = horse blocked
    // 0x4000_0000 = floor surface recessed by 1 unit
    // 0x3C00_0000 = ? (floor property?)
    // 0x03E0_0000 = ? (wall property?)
    // 0x001C_0000 = ?
    // 0x0003_E000 = ?
    // 0x0000_1F00 = scene exit index
    // 0x0000_00FF = CamData index
    // Word 1
    // 0x0800_0000 = wall damage
    // 0x07E0_0000 = conveyor direction
    // 0x001C_0000 = conveyor speed
    // 0x0002_0000 = is hookable surface
    // 0x0001_F800 = echo/reverb
    // 0x0000_07C0 = lighting setting index
    // 0x0000_0030 = surface slope
    // 0x0000_000F = type

} SurfaceType; // size = 0x8

typedef struct {
    /* 0x00 */ Vec3s minBounds; // minimum coordinates of poly bounding box
    /* 0x06 */ Vec3s maxBounds; // maximum coordinates of poly bounding box
    /* 0x0C */ u16 numVertices;
    /* 0x10 */ Vec3s* vtxList;
    /* 0x14 */ u16 numPolygons;
    /* 0x18 */ CollisionPoly* polyList;
    /* 0x1C */ SurfaceType* surfaceTypeList;
    /* 0x20 */ CamData* cameraDataList;
    /* 0x24 */ u16 numWaterBoxes;
    /* 0x28 */ WaterBox* waterBoxes;
} CollisionHeader; // size = 0x2C

typedef struct {
    /* 0x0 */ s16 polyId;
    /* 0x2 */ u16 next; // index of the next SSNode in the list, or SS_NULL if last element 
} SSNode; // size = 0x4

typedef struct {
    u16 head; // index of the first SSNode in the list, or SS_NULL if the list is empty
} SSList; // represents a linked list of type SSNode

typedef struct {
    /* 0x0 */ u16 max;
    /* 0x2 */ u16 count;
    /* 0x4 */ SSNode* tbl;
    /* 0x8 */ u8* polyCheckTbl;
} SSNodeList; // size = 0xC

typedef struct {
    /* 0x0 */ SSNode* tbl;
    /* 0x4 */ u32 count;
    /* 0x8 */ s32 maxNodes;
} DynaSSNodeList; // size = 0xC

typedef struct {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ WaterBox* boxes;
} DynaWaterBoxList; // size = 0x8

typedef struct {
    /* 0x0 */ SSList floor;
    /* 0x2 */ SSList wall;
    /* 0x4 */ SSList ceiling;
} StaticLookup; // size = 0x6

typedef struct {
    /* 0x0 */ s16 polyStartIndex;
    /* 0x2 */ SSList ceiling;
    /* 0x4 */ SSList wall;
    /* 0x6 */ SSList floor;
} DynaLookup; // size = 0x8

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ CollisionHeader* colHeader;
    /* 0x08 */ DynaLookup dynaLookup;
    /* 0x10 */ u16 vtxStartIndex;
    /* 0x12 */ u16 waterboxesStartIndex;
    /* 0x14 */ ScaleRotPos prevTransform;
    /* 0x34 */ ScaleRotPos curTransform;
    /* 0x54 */ Sphere16 boundingSphere;
    /* 0x5C */ f32 minY;
    /* 0x60 */ f32 maxY;
} BgActor; // size = 0x64

typedef struct {
    /* 0x0000 */ u8 bitFlag;
    /* 0x0004 */ BgActor bgActors[BG_ACTOR_MAX];
    /* 0x138C */ u16 bgActorFlags[BG_ACTOR_MAX]; // bit 0 - Is mesh active
    /* 0x13F0 */ CollisionPoly* polyList;
    /* 0x13F4 */ Vec3s* vtxList;
    /* 0x13F8 */ DynaWaterBoxList waterBoxList;
    /* 0x1400 */ DynaSSNodeList polyNodes;
    /* 0x140C */ s32 polyNodesMax;
    /* 0x1410 */ s32 polyListMax;
    /* 0x1414 */ s32 vtxListMax;
} DynaCollisionContext; // size = 0x1418

typedef struct {
    /* 0x00 */ CollisionHeader* colHeader; // scene's static collision
    /* 0x04 */ Vec3f minBounds;            // minimum coordinates of collision bounding box
    /* 0x10 */ Vec3f maxBounds;            // maximum coordinates of collision bounding box
    /* 0x1C */ Vec3i subdivAmount;         // x, y, z subdivisions of the scene's static collision
    /* 0x28 */ Vec3f subdivLength;         // x, y, z subdivision worldspace lengths
    /* 0x34 */ Vec3f subdivLengthInv;      // inverse of subdivision length
    /* 0x40 */ StaticLookup* lookupTbl;    // 3d array of length subdivAmount
    /* 0x44 */ SSNodeList polyNodes;
    /* 0x0050 */ DynaCollisionContext dyna;
    /* 0x1468 */ u32 memSize; // Size of all allocated memory plus CollisionContext
    /* 0x146C */ u32 flags;   // bit 0 reverses conveyor direction (i.e. water flow in Great Bay Temple)
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
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ f32 checkDist;
    /* 0x2C */ DynaCollisionContext* dyna;
    /* 0x30 */ SSList* ssList;
} DynaRaycast; // size = 0x34

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
    /* 0x1C */ CollisionPoly** outPoly;
    /* 0x20 */ f32 outDistSq;
    /* 0x24 */ f32 checkDist;
    /* 0x28 */ s32 bccFlags;
    /* 0x2C */ Actor* actor;
} StaticLineTest; // size = 0x30

typedef struct {
    /* 0x00 */ CollisionContext* colCtx;
    /* 0x04 */ u16 xpFlags;
    /* 0x08 */ DynaCollisionContext* dyna;
    /* 0x0C */ SSList* ssList;
    /* 0x10 */ Vec3f* posA;
    /* 0x14 */ Vec3f* posB;
    /* 0x18 */ Vec3f* posResult;
    /* 0x1C */ CollisionPoly** resultPoly;
    /* 0x20 */ s32 checkOneFace; // bccFlags & 0x8
    /* 0x24 */ f32* distSq;      // distance from posA to poly squared
    /* 0x28 */ f32 checkDist;    // distance from poly
    /* 0x2C */ Actor* actor;
    /* 0x30 */ s32 bgId;
} DynaLineTest; // size = 0x34

typedef struct {
    /* 0x00 */ CollisionPoly* poly;
    /* 0x04 */ Vec3s* vtxList;
    /* 0x08 */ Vec3f* posA;
    /* 0x0C */ Vec3f* posB;
    /* 0x10 */ Vec3f* planeIntersect;
    /* 0x14 */ s32 checkOneFace;
    /* 0x18 */ f32 checkDist;
} BgLineVsPolyTest; // size = 0x1C

typedef struct {
    /* 0x0 */ s16 sceneId;
    /* 0x4 */ u32 memSize;
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
    s16 sceneId;
    Vec3s subdivAmount;
    s32 nodeListMax; // if -1, dynamically compute max nodes
} BgCheckSceneSubdivisionEntry;
#endif
