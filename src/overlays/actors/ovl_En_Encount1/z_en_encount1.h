#ifndef Z_EN_ENCOUNT1_H
#define Z_EN_ENCOUNT1_H

#include "global.h"

#define ENENCOUNT1_MAX_SPAWNS_TOTAL_INFINITE 63 // aka 0x3F, All bits set

#define ENENCOUNT1_GET_TYPE(thisx) (((thisx)->params >> 11) & 0x1F)
#define ENENCOUNT1_GET_MAX_SPAWNS_CUR(thisx) (((thisx)->params >> 6) & 0x1F)
#define ENENCOUNT1_GET_MAX_SPAWNS_TOTAL(thisx) ((thisx)->params & 0x3F)
#define ENENCOUNT1_GET_PATH_INDEX(thisx) ((thisx)->params & 0x3F) // Used only by EN_ENCOUNT1_SKULLFISH_2 which doesn't use MaxSpawnsTotal

#define ENENCOUNT1_GET_MIN_SPAWN_TIME(thisx) ((thisx)->world.rot.x) // Time to wait between spawning
#define ENENCOUNT1_GET_SPAWN_UNK(thisx) ((thisx)->world.rot.y) // Unused
#define ENENCOUNT1_GET_MAX_SPAWN_DISTANCE(thisx) ((thisx)->world.rot.z) // Negative means infinite distance

typedef enum EnEncount1Enemy {
    /* 0 */ EN_ENCOUNT1_GRASSHOPPER,
    /* 1 */ EN_ENCOUNT1_WALLMASTER,
    /* 2 */ EN_ENCOUNT1_SKULLFISH,
    /* 3 */ EN_ENCOUNT1_SKULLFISH_2,
} EnEncount1Enemy;

struct EnEncount1;

typedef void (*EnEncount1ActionFunc)(struct EnEncount1*, PlayState*);

typedef struct EnEncount1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnEncount1ActionFunc actionFunc;
    /* 0x148 */ Path* path;
    /* 0x14C */ s16 maxSpawnsCur;
    /* 0x14E */ s16 curSpawnNum;
    /* 0x150 */ s16 type;
    /* 0x152 */ s16 totalSpawnNum;
    /* 0x154 */ s16 maxSpawnsTotal;
    /* 0x156 */ s16 timer;
    /* 0x158 */ s16 minSpawnTime;
    /* 0x15A */ s16 pathIndex;
    /* 0x15C */ s32 spawnUnk;
    /* 0x160 */ f32 maxSpawnDistance;
} EnEncount1; // size = 0x164

#endif // Z_EN_ENCOUNT1_H
