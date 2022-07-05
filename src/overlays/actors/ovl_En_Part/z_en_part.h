#ifndef Z_EN_PART_H
#define Z_EN_PART_H

#include "global.h"

struct EnPart;

typedef void (*EnPartActionFunc)(struct EnPart*, PlayState*);

typedef enum {
    PARAMS_0 = 0,
    PARAMS_1 = 1,
    PARAMS_4 = 4,
    PARAMS_15 = 15
} ActorParams;

typedef struct EnPart {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 unk144;
    /* 0x146 */ s16 unk146;
    /* 0x148 */ f32 zRot;
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ Gfx* displayList;
} EnPart; // size = 0x154

extern const ActorInit En_Part_InitVars;

#endif // Z_EN_PART_H
