#ifndef Z_EN_TUBO_TRAP_H
#define Z_EN_TUBO_TRAP_H

#include <global.h>

struct EnTuboTrap;

typedef void (*EnTuboTrapActionFunc)(struct EnTuboTrap*, GlobalContext*);

typedef struct EnTuboTrap {
    /* 0x000 */ Actor actor;
    // actor is smaller by 4 I think
    /* 0x014X */ EnTuboTrapActionFunc actionFunc;
    /* 0x015X */ f32 targetY;
    /* 0x015X */ Vec3f originPos;
    /* 0x0158 */ ColCylinder collider;

    /* 0x144 */ //char unk_144[0x60];
} EnTuboTrap; // size = 0x1A4

extern const ActorInit En_Tubo_Trap_InitVars;

extern s32 D_05018090; // pot break shard displaylist?

extern s32 D_05017EA0; // the pot displaylist?

extern f32 D_80931494; // distance to player

#endif // Z_EN_TUBO_TRAP_H
