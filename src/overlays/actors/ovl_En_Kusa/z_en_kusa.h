#ifndef Z_EN_KUSA_H
#define Z_EN_KUSA_H

#include "global.h"

struct EnKusa;

typedef void (*EnKusaActionFunc)(struct EnKusa*, GlobalContext*);

typedef enum {
    /* 0 */ ENKUSA_TYPE_BUSH,
    /* 1 */ ENKUSA_TYPE_REGROWING_GRASS,
    /* 2 */ ENKUSA_TYPE_GRASS,
    /* 3 */ ENKUSA_TYPE_GRASS_2
} EnKusaType;

typedef struct EnKusa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnKusaActionFunc actionFunc;
    /* 0x148 */ ColliderCylinder collider;
    /* 0x194 */ u8 timer;
    /* 0x195 */ s8 objIndex;
    /* 0x196 */ s8 kusaMtxIdx;
    /* 0x197 */ u8 isCut;
    /* 0x198 */ u8 isInWater;
} EnKusa; // size = 0x19C

extern const ActorInit En_Kusa_InitVars;

#define KUSA_GET_COLLECTIBLE_ID(thisx) ((((thisx)->params >> 8) & 0x7F))
#define KUSA_GET_RAND_COLLECTIBLE_ID(thisx) (((thisx)->params >> 8) & 0xF)
#define KUSA_SHOULD_SPAWN_BUGS(thisx) (((thisx)->params >> 0x4) & 1)
#define KUSA_GET_PARAMS_0C(thisx) (((thisx)->params >> 0xC) & 0x1)
#define KUSA_GET_PARAMS_3F(thisx) (((thisx)->params >> 0x2) & 0x3F)


#define GET_KUSA_TYPE(thisx)((thisx)->params & 0x3)

#endif // Z_EN_KUSA_H
