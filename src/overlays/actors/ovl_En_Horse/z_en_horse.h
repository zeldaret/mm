#ifndef Z_EN_HORSE_H
#define Z_EN_HORSE_H

#include "global.h"
#include "z64skin.h"

struct EnHorse;

typedef struct EnHorse {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC];
    /* 0x150 */ s32 unk_150;
    /* 0x154 */ char unk_154[0x98];
    /* 0x1EC */ UNK_TYPE4 unk_1EC;
    /* 0x1F0 */ char unk_1F0[0x5C];
    /* 0x24C */ u32 unk_24C;
    /* 0x250 */ char unk_250[0x138];
    /* 0x388 */ s32 inRace;
    /* 0x38C */ char unk_38C[0x208];
} EnHorse; // size = 0x594

extern const ActorInit En_Horse_InitVars;

#endif // Z_EN_HORSE_H
