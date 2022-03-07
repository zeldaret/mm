#ifndef Z_ARROW_LIGHT_H
#define Z_ARROW_LIGHT_H

#include "global.h"

struct ArrowLight;

typedef void (*ArrowLightActionFunc)(struct ArrowLight*, GlobalContext*);

typedef struct ArrowLight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s16 radius;       /* inferred */
    /* 0x146 */ u16 timer;       /* inferred */
    /* 0x148 */ u8 alpha;        /* inferred */
    /* 0x14C */ Vec3f unk_14C;    /* maybe part of unk148[0x10]? */
    /* 0x158 */ f32 height;       /* inferred */
    /* 0x15C */ f32 unk15C;       /* inferred */
    /* 0x160 */ ArrowLightActionFunc actionFunc;
} ArrowLight; /* size = 0x164 */


extern const ActorInit Arrow_Light_InitVars;

#endif // Z_ARROW_LIGHT_H
