#ifndef Z_EN_GAMELUPY_H
#define Z_EN_GAMELUPY_H

#include "global.h"

struct EnGamelupy;

typedef void (*EnGamelupyActionFunc)(struct EnGamelupy*, PlayState*);

typedef struct EnGamelupy {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ EnGamelupyActionFunc actionFunc;
    /* 0x194 */ s32 rupeeIndex;
    /* 0x198 */ s16* unk_198;
    /* 0x19C */ s16 unk_19C;
    /* 0x19E */ s16 unk_19E;
    /* 0x1A0 */ s16 unk_1A0;
} EnGamelupy; // size = 0x1A4

extern const ActorInit En_Gamelupy_InitVars;

#endif // Z_EN_GAMELUPY_H
