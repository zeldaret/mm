#ifndef Z64PATH_H
#define Z64PATH_H

#include "PR/ultratypes.h"
#include "z64math.h"

struct PlayState;
struct Actor;

#define PATH_INDEX_NONE -1
#define ADDITIONAL_PATH_INDEX_NONE (u8)-1

typedef struct Path {
    /* 0x0 */ u8 count; // Number of points in the path
    /* 0x1 */ u8 additionalPathIndex;
    /* 0x2 */ s16 customValue; // Path specific to help distinguish different paths
    /* 0x4 */ Vec3s* points; // Segment Address to the array of points
} Path; // size = 0x8

Path* Path_GetByIndex(struct PlayState* play, s16 index, s16 indexNone);
f32 Path_OrientAndGetDistSq(struct Actor* actor, Path* path, s16 waypoint, s16* yaw);
void Path_CopyLastPoint(Path* path, Vec3f* dest);

#endif
