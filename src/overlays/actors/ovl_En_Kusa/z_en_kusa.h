#ifndef Z_EN_KUSA_H
#define Z_EN_KUSA_H

#include <global.h>

struct EnKusa;

typedef struct EnKusa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144;
    /* 0x148 */ ColliderCylinder collider; // size = 0x4C
    /* 0x194 */ char pad[0x08];
} EnKusa; // size = 0x19C

extern const ActorInit En_Kusa_InitVars;

#endif // Z_EN_KUSA_H
