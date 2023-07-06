#ifndef Z_EN_GAMELUPY_H
#define Z_EN_GAMELUPY_H

#include "global.h"

struct EnGamelupy;

#define ENGAMELUPY_COLLECTED 50

typedef void (*EnGamelupyActionFunc)(struct EnGamelupy*, PlayState*);

typedef enum {
    /* 0 */ ENGAMELUPY_TYPE_GREEN,
    /* 1 */ ENGAMELUPY_TYPE_BLUE,
    /* 2 */ ENGAMELUPY_TYPE_MAX
} EnGamelupyType;

typedef struct EnGamelupy {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ EnGamelupyActionFunc actionFunc;
    /* 0x194 */ s32 type;
    /* 0x198 */ s16* sharedMem; // Shared memory location with ACTOR_EN_LIFT_NUTS
    /* 0x19C */ s16 collectedFrames;
    /* 0x19E */ s16 sparklesAngle;
    /* 0x1A0 */ s16 sparklesAngleStep;
} EnGamelupy; // size = 0x1A4

#endif // Z_EN_GAMELUPY_H
