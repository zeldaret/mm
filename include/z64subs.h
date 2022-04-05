#ifndef Z64SUBS_H
#define Z64SUBS_H

#include "z64actor.h"
#include "z64scene.h"

typedef enum {
    /* 0 */ SUBS_CUTSCENE_SET_UNK_LINK_FIELDS,
    /* 1 */ SUBS_CUTSCENE_NORMAL,
    /* 2 */ SUBS_CUTSCENE_SET_FLAG
} SubSCutsceneType;

typedef s32 (*func_8013E748_arg6)(struct GlobalContext*, Actor*, void*);

typedef s32 (*VerifyActor)(struct GlobalContext*, Actor*, Actor*, void*);

#define ACTOR_PATHING_RETURN_TO_START (1 << 0)
#define ACTOR_PATHING_SWITCH_DIRECTION (1 << 1)
#define ACTOR_PATHING_MOVE_BACKWARDS (1 << 3)
#define ACTOR_PATHING_REACHED_POINT_PERMANENT (1 << 4)
#define ACTOR_PATHING_REACHED_END_PERMANENT (1 << 5)
#define ACTOR_PATHING_REACHED_POINT_TEMPORARY (1 << 6)
#define ACTOR_PATHING_REACHED_END_TEMPORARY (1 << 7)

#define ACTOR_PATHING_REACHED_TEMPORARY \
    (ACTOR_PATHING_REACHED_POINT_TEMPORARY | ACTOR_PATHING_REACHED_END_TEMPORARY)
#define ACTOR_PATHING_REACHED_POINT \
    (ACTOR_PATHING_REACHED_POINT_PERMANENT | ACTOR_PATHING_REACHED_POINT_TEMPORARY)
#define ACTOR_PATHING_REACHED_END \
    (ACTOR_PATHING_REACHED_END_PERMANENT | ACTOR_PATHING_REACHED_END_TEMPORARY)

struct ActorPathing;
typedef void (*ActorPathingComputeFunc)(struct GlobalContext*, struct ActorPathing*);
typedef s32 (*ActorPathingUpdateFunc)(struct GlobalContext*, struct ActorPathing*);

typedef struct ActorPathing {
    /* 0x00 */ Path* setupPathList;
    /* 0x04 */ s32 pathIndex;
    /* 0x08 */ Vec3s* points;
    /* 0x0C */ s32 count;
    /* 0x10 */ s32 curPointIndex;
    /* 0x14 */ s32 begPointIndex;
    /* 0x18 */ s32 endPointIndex;
    /* 0x1C */ u8 flags;
    /* 0x1D */ u8 prevFlags;
    /* 0x20 */ Vec3f curPoint;
    /* 0x2C */ Vec3f pointOffset;
    /* 0x38 */ Vec3f prevPoint;
    /* 0x44 */ Vec3f* worldPos;
    /* 0x48 */ Actor* actor;
    /* 0x4C */ f32 distSqToCurPointXZ;
    /* 0x50 */ f32 distSqToCurPoint;
    /* 0x54 */ Vec3s rotToCurPoint;
    /* 0x5C */ ActorPathingComputeFunc computePointInfoFunc;
    /* 0x60 */ ActorPathingUpdateFunc updateActorInfoFunc; // Return true if should setNextPoint, false if the actor should move forward
    /* 0x64 */ ActorPathingUpdateFunc moveFunc; // Return true if should compute and update again
    /* 0x68 */ ActorPathingUpdateFunc setNextPointFunc; // Return true if should compute and update again
} ActorPathing; // size = 0x6C

#endif
