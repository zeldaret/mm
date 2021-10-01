#ifndef Z_EN_GIANT_H
#define Z_EN_GIANT_H

#include "global.h"

#define GIANT_TYPE(thisx) ((thisx)->params & 0xF)

typedef enum {
    /*  0 */ GIANT_TYPE_MOUNTAIN_1,
    /*  1 */ GIANT_TYPE_CANYON_1,
    /*  2 */ GIANT_TYPE_SWAMP_1,
    /*  3 */ GIANT_TYPE_OCEAN_1,
    /*  4 */ GIANT_TYPE_MOUNTAIN_2,
    /*  5 */ GIANT_TYPE_CANYON_2,
    /*  6 */ GIANT_TYPE_SWAMP_2,
    /*  7 */ GIANT_TYPE_OCEAN_2,
    /*  8 */ GIANT_TYPE_MOUNTAIN_3,
    /*  9 */ GIANT_TYPE_CANYON_3,
    /* 10 */ GIANT_TYPE_SWAMP_3,
    /* 11 */ GIANT_TYPE_OCEAN_3,
    /* 12 */ GIANT_TYPE_MOUNTAIN_4,
    /* 13 */ GIANT_TYPE_CANYON_4,
    /* 14 */ GIANT_TYPE_SWAMP_4,
    /* 15 */ GIANT_TYPE_OCEAN_4,
    /* 16 */ GIANT_TYPE_MAX
} EnGiantType;

struct EnGiant;

typedef void (*EnGiantActionFunc)(struct EnGiant*, GlobalContext*);

typedef struct EnGiant {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ u16 unk_24C;
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ u16 unk_250;
    /* 0x252 */ char unk_252[0x42];
    /* 0x294 */ s16 unk_294;
    /* 0x296 */ s16 unk_296;
    /* 0x298 */ EnGiantActionFunc actionFunc;
} EnGiant; // size = 0x29C

extern const ActorInit En_Giant_InitVars;

#endif // Z_EN_GIANT_H
