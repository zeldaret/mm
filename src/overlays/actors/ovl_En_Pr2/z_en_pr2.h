#ifndef Z_EN_PR2_H
#define Z_EN_PR2_H

#include "global.h"
#include "assets/objects/object_pr/object_pr.h"

struct EnPr2;

typedef void (*EnPr2ActionFunc)(struct EnPr2*, PlayState*);

// I wonder if they planned more for this actor, because there 
// is room enough in params without using rotation of the parent

#define ENPR2_GET_TYPE(thisx) ((thisx)->params & 0xF)
// only used for type PR2_TYPE_RESIDENT (agro distance is 1/20th of final units) 
#define ENPR2_GET_AGRO_DISTANCE(thisx) (((thisx)->params >> 4) & 0xFF)

// only if we are NOT spawned by a parent actor
#define ENPR2_GETZ_DROPID(thisx) ((thisx)->world.rot.z)
// only if we are spawned by En_Encount1
#define ENPR2_GETY_PARENT_DROPID(parent) ((parent)->world.rot.y)
// agro distance is 1/20th of final distance
#define ENPR2_GETZ_PARENT_AGRO_DISTANCE(parent) ((parent)->world.rot.z)

#define ENPR2_PATH_INDEX_NONE 0x3F
#define ENPR2_PARAMS(paramF, paramFF0) (((paramF) & 0xF) | (((paramFF0) << 4) & 0xFF0))

typedef enum EnPr2Type {
    /* 00 */ PR2_TYPE_PASSIVE,   // does not attack, used as a hazard around the cape heartpiece likelike
    /* 01 */ PR2_TYPE_SPAWNED,   // called from Encount1 as part of endless spawn
    /* 02 */ PR2_TYPE_RESIDENT,  // regular spawn and remain in the world
    /* 03 */ PR2_TYPE_PATHING,   // spawned by Encount1 in GBT so they swim out of a waterway
    // all types above 10 are limb based, for drawing the dead fish parts after being broken
    /* 10 */ PR2_TYPE_BROKEN = 10
} EnPr2Type;

typedef enum EnPr2State {
    /* 00 */ PR2_STATE_PATHING,
    /* 01 */ PR2_STATE_IDLE,
    /* 02 */ PR2_STATE_ATTACKING,
    /* 03 */ PR2_STATE_DEAD,
} EnPr2State;

typedef struct EnPr2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_PR_2_LIMB_MAX];
    /* 0x1A6 */ Vec3s morphTable[OBJECT_PR_2_LIMB_MAX];
    /* 0x1C4 */ EnPr2ActionFunc actionFunc;
    /* 0x1C8 */ s16 pathIndex;
    /* 0x1CC */ Path* path;
    /* 0x1D0 */ s32 waypoint;
    /* 0x1D4 */ s16 state;
    /* 0x1D6 */ s16 bubbleToggle;
    /* 0x1D8 */ s16 mainTimer;
    /* 0x1DA */ s16 waypointTimer; // path related, maybe rename
    /* 0x1DC */ s16 targetingTimer; // on zero, attack attempt on player
    /* 0x1DE */ s16 returnHomeTimer; // frames until attacking player acceptable again
    /* 0x1E0 */ s16 type;
    /* 0x1E2 */ UNK_TYPE1 unk1E2[2];
    /* 0x1E4 */ s16 targetZRot;
    /* 0x1E6 */ s16 targetYRot;
    /* 0x1E8 */ UNK_TYPE1 unk1E8[4];
    /* 0x1EC */ s16 primColor; // r and g and b, all same var, think this is to force the actor black
    /* 0x1EE */ s16 yawTowardsWaypoint;
    /* 0x1F0 */ s16 wallCollisionAngleAdjustment;
    /* 0x1F2 */ s16 wallCollisionCounter;
    /* 0x1F4 */ s16 alpha;
    /* 0x1F8 */ f32 animEndFrame;
    /* 0x1FC */ f32 slowLimbYaw; // think this is related to swimming animation, for head turning
    /* 0x200 */ f32 waterSurfaceHeight;
    /* 0x204 */ f32 scale;
    /* 0x208 */ f32 agroDistance; // might be incorrect
    /* 0x20C */ f32 randomTargetHeightOffset; // recheck name, might not be target
    /* 0x210 */ s32 animIndex;
    /* 0x214 */ UNK_TYPE1 unk214[4];
    /* 0x218 */ s32 dropID;
    /* 0x21C */ Vec3f waypointPos;
    /* 0x228 */ Vec3f newHome;
    /* 0x234 */ Vec3f limbPos[5];
    /* 0x270 */ Vec3f limbJawPos;
    /* 0x27C */ ColliderCylinder collider;
} EnPr2; // size = 0x2C8

#endif // Z_EN_PR2_H
