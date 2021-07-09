#ifndef Z_EN_KUSA_H
#define Z_EN_KUSA_H

#include <global.h>

#define GET_KUSA_COLLECTIBLE_ID(x) (((x->actor.params >> 8) & 0x7F) << 8)
#define GET_KUSA__RAND_COLLECTIBLE_ID(x) ((x->actor.params >> 8) & 0xF)

struct EnKusa;

typedef void (*EnKusaActionFunc)(struct EnKusa*, GlobalContext*);

typedef struct EnKusa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnKusaActionFunc actionFunc;
    /* 0x148 */ ColliderCylinder collider; // size = 0x4C
    /* 0x194 */ u8 timer;
    /* 0x195 */ s8 objIndex;
    /* 0x196 */ s8 unk_196;
    /* 0x197 */ u8 unk_197;
    /* 0x198 */ u8 unk198;
} EnKusa; // size = 0x19C

extern const ActorInit En_Kusa_InitVars;

#endif // Z_EN_KUSA_H
