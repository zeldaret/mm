#ifndef Z_EN_ENCOUNT1_H
#define Z_EN_ENCOUNT1_H

#include "global.h"

#define ENENCOUNT1_GET_TYPE(thisx) (((thisx)->params >> 11) & 0x1F)
#define ENENCOUNT1_GET_7C0(thisx) (((thisx)->params >> 6) & 0x1F)
#define ENENCOUNT1_GET_PATH_INDEX(thisx) ((thisx)->params & 0x3F)

#define ENENCOUNT1_PATH_INDEX_NONE (PATH_INDEX_NONE & 0x3F)

typedef enum EnEncount1Enemy {
    /* 0x0 */ EN_ENCOUNT1_GRASSHOPPER,
    /* 0x1 */ EN_ENCOUNT1_WALLMASTER,
    /* 0x2 */ EN_ENCOUNT1_SKULLFISH,
    /* 0x3 */ EN_ENCOUNT1_SKULLFISH_2,
} EnEncount1Enemy;

struct EnEncount1;

typedef void (*EnEncount1ActionFunc)(struct EnEncount1*, PlayState*);

typedef struct EnEncount1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnEncount1ActionFunc actionFunc;
    /* 0x148 */ Path* path;
    /* 0x14C */ s16 unk_14C;
    /* 0x14E */ s16 unk_14E;
    /* 0x150 */ s16 actorType;
    /* 0x152 */ s16 unk_152;
    /* 0x154 */ s16 unk_154;
    /* 0x156 */ s16 unk_156;
    /* 0x158 */ s16 unk_158;
    /* 0x15A */ s16 unk_15A;
    /* 0x15C */ s32 unk_15C;
    /* 0x160 */ f32 unk_160;
} EnEncount1; // size = 0x164

#endif // Z_EN_ENCOUNT1_H
