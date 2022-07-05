#ifndef Z_EN_PART_H
#define Z_EN_PART_H

#include "global.h"

struct EnPart;

typedef struct EnPart {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 unk144;
    /* 0x145 */ s8 unk145;
    /* 0x146 */ s16 unk146;
    /* 0x148 */ f32 unk148;
    /* 0x14C */ f32 unk14C;
    /* 0x150 */ Gfx* unk_150;
} EnPart; // size = 0x154

extern const ActorInit En_Part_InitVars;

#endif // Z_EN_PART_H
