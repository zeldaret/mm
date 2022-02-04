#ifndef Z_EN_KUSA_H
#define Z_EN_KUSA_H

#include "global.h"

struct EnKusa;

typedef void (*EnKusaActionFunc)(struct EnKusa*, GlobalContext*);

typedef enum {
    /* 0 */ ENKUSA_TYPE_BUSH,
    /* 1 */ ENKUSA_TYPE_REGROW_GRASS,
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
    /* 0x198 */ u8 unk198;
} EnKusa; // size = 0x19C

extern const ActorInit En_Kusa_InitVars;

#define GET_KUSA_COLLECTIBLE_ID(x) (((x->actor.params >> 8) & 0x7F))
#define GET_KUSA_RAND_COLLECTIBLE_ID(x) ((x->actor.params >> 8) & 0xF)

#define GET_KUSA_TYPE(this)(this->actor.params & 0x3)

#endif // Z_EN_KUSA_H
