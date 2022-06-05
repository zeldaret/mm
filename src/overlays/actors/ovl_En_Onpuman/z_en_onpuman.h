#ifndef Z_EN_ONPUMAN_H
#define Z_EN_ONPUMAN_H

#include "global.h"

struct EnOnpuman;

typedef void (*EnOnpumanActionFunc)(struct EnOnpuman*, GlobalContext*);

typedef struct EnOnpuman {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char pad144[0x110];
    /* 0x254 */ ColliderCylinder unk254;            /* inferred */
    /* 0x2A0 */ s32 unk2A0;                         /* inferred */
    /* 0x2A4 */ s16 unk2A4;                         /* inferred */
    /* 0x2A6 */ char pad2A6[2];
    /* 0x2A8 */ EnOnpumanActionFunc actionFunc;
} EnOnpuman;  /* size = 0x2AC */

extern const ActorInit En_Onpuman_InitVars;

#endif // Z_EN_ONPUMAN_H
