#ifndef Z_EN_TANRON5_H
#define Z_EN_TANRON5_H

#include "global.h"

struct EnTanron5;

#define EN_TANRON5_GET_TYPE(thisx) ((thisx)->params)

typedef enum {
    /*   0 */ EN_TANRON5_TYPE_STATIC,
    /*   1 */ EN_TANRON5_TYPE_MAJORA_PILLAR_1,
    /*   2 */ EN_TANRON5_TYPE_MAJORA_PILLAR_2,
    /*   3 */ EN_TANRON5_TYPE_MAJORA_PILLAR_3,
    /*   4 */ EN_TANRON5_TYPE_MAJORA_PILLAR_4,
    /*   5 */ EN_TANRON5_TYPE_MAJORA_PILLAR_5,
    /*   6 */ EN_TANRON5_TYPE_MAJORA_PILLAR_6,
    /*   7 */ EN_TANRON5_TYPE_MAJORA_PILLAR_7,
    /*   8 */ EN_TANRON5_TYPE_MAJORA_PILLAR_8,
    /*   9 */ EN_TANRON5_TYPE_MAJORA_PILLAR_9,
    /*  10 */ EN_TANRON5_TYPE_MAJORA_PILLAR_10,
    /*  11 */ EN_TANRON5_TYPE_MAJORA_PILLAR_11,
    /*  12 */ EN_TANRON5_TYPE_MAJORA_PILLAR_12,
    /*  13 */ EN_TANRON5_TYPE_PYRAMID_RUIN_1,
    /*  14 */ EN_TANRON5_TYPE_PYRAMID_RUIN_2,
    /*  15 */ EN_TANRON5_TYPE_PYRAMID_RUIN_3,
    /*  16 */ EN_TANRON5_TYPE_PYRAMID_RUIN_4,
    /*  17 */ EN_TANRON5_TYPE_PYRAMID_RUIN_5,
    /*  18 */ EN_TANRON5_TYPE_PYRAMID_RUIN_6,
    /*  19 */ EN_TANRON5_TYPE_PYRAMID_RUIN_7,
    /*  20 */ EN_TANRON5_TYPE_PYRAMID_RUIN_8,
    /* 100 */ EN_TANRON5_TYPE_LARGE_RUIN_FRAGMENT_1 = 100,
    /* 101 */ EN_TANRON5_TYPE_LARGE_RUIN_FRAGMENT_2,
    /* 102 */ EN_TANRON5_TYPE_LARGE_RUIN_FRAGMENT_3,
    /* 103 */ EN_TANRON5_TYPE_LARGE_RUIN_FRAGMENT_4,
    /* 104 */ EN_TANRON5_TYPE_LARGE_RUIN_FRAGMENT_5,
    /* 105 */ EN_TANRON5_TYPE_LARGE_RUIN_FRAGMENT_6,
    /* 106 */ EN_TANRON5_TYPE_LARGE_RUIN_FRAGMENT_7,
    /* 107 */ EN_TANRON5_TYPE_SMALL_RUIN_FRAGMENT_1,
    /* 108 */ EN_TANRON5_TYPE_SMALL_RUIN_FRAGMENT_2,
    /* 109 */ EN_TANRON5_TYPE_SMALL_RUIN_FRAGMENT_3,
    /* 110 */ EN_TANRON5_TYPE_ITEM_DROP_1,
    /* 111 */ EN_TANRON5_TYPE_ITEM_DROP_2
} EnTanron5Type;

typedef struct EnTanron5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s16 timer;
    /* 0x148 */ Gfx* dList;
    /* 0x14C */ ColliderCylinder collider;
    /* 0x198 */ union {
                    s16 ruinFragmentRotationalVelocityX;
                    s16 itemDropRotZ;
                };
    /* 0x19A */ s16 ruinFragmentRotationalVelocityY;
    /* 0x19C */ f32 baseScale;
    /* 0x1A0 */ union {
                    u8 hitCount;     // used by destructible props
                    u8 sinkTimer;    // used by ruin fragments
                    u8 itemDropType; // used by item drops
                };
    /* 0x1A1 */ u8 hitTimer;
} EnTanron5; // size = 0x1A4

#endif // Z_EN_TANRON5_H
