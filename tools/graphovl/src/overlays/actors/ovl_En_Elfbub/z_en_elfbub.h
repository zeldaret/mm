#ifndef Z_EN_ELFBUB_H
#define Z_EN_ELFBUB_H

#include "global.h"

#define ENELFBUB_GET_SWITCHFLAG(thisx) ((((thisx)->params) & 0xFE00) >> 9)

struct EnElfbub;

typedef void (*EnElfbubActionFunc)(struct EnElfbub*, GlobalContext*);

typedef struct EnElfbub {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ s16 zRot;
    /* 0x0192 */ s16 zRotDelta;
    /* 0x0194 */ s16 oscillationAngle;
    /* 0x0196 */ s16 popTimer;
    /* 0x0198 */ f32 xScale;
    /* 0x019C */ f32 xyScale;
    /* 0x01A0 */ EnElfbubActionFunc actionFunc;
} EnElfbub; // size = 0x1A4

extern const ActorInit En_Elfbub_InitVars;

#endif // Z_EN_ELFBUB_H
