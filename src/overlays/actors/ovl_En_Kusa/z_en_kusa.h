#ifndef Z_EN_KUSA_H
#define Z_EN_KUSA_H

#include <global.h>

struct EnKusa;

typedef void (*EnKusaActionFunc)(struct EnKusa*, GlobalContext*);

typedef struct EnKusa {
    /* 0x000 */ Actor actor;
    // /* 0x144 */ char unk_144[0x58];
    /* 0x144 */ EnKusaActionFunc actionFunc;
    /* 0x148 */ ColliderCylinder collider; // size = 0x4C
    /* 0x194 */ u8 timer;
    /* 0x197 */ u8 unk_197;
} EnKusa; // size = 0x19C

extern const ActorInit En_Kusa_InitVars;

#endif // Z_EN_KUSA_H
