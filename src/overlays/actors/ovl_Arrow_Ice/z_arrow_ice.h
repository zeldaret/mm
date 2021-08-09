#ifndef Z_ARROW_ICE_H
#define Z_ARROW_ICE_H

#include "global.h"

struct ArrowIce;

typedef void (*ArrowIceActionFunc)(struct ArrowIce*, GlobalContext*);

typedef struct ArrowIce {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ s16 unk_144; // radius
    /* 0x0146 */ u16 unk_146; // timer
    /* 0x0148 */ u8 unk_148;  // alpha
    /* 0x014C */ Vec3f unk_14C; // unkPos
    /* 0x0158 */ f32 unk_158;
    /* 0x015C */ f32 unk_15C;
    /* 0x0160 */ ArrowIceActionFunc actionFunc;
} ArrowIce; // size = 0x164

extern const ActorInit Arrow_Ice_InitVars;

#endif // Z_ARROW_ICE_H
