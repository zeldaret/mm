#ifndef Z_EN_MINIFROG_H
#define Z_EN_MINIFROG_H

#include <global.h>

struct EnMinifrog;

typedef void (*EnMinifrogActionFunc)(struct EnMinifrog*, GlobalContext*);

#define EN_MINIFROG_IS_RETURNED(this) ((((this)->actor.params)&0xF0) >> 4)

typedef enum {
    /* 0x00 */ MINIFROG_YELLOW,         // Mountain Village
    /* 0x01 */ MINIFROG_CYAN,           // Woodfall Temple
    /* 0x02 */ MINIFROG_PINK,           // Great Bay Temple
    /* 0x03 */ MINIFROG_BLUE,           // Southern Swamp
    /* 0x04 */ MINIFROG_WHITE,          // Laundry Pool
    /* 0xFF */ MINIFROG_INVALID = 0xFF // -1
} MinifrogType;

typedef enum {
    /* 0x00 */ MINIFROG_STATE_JUMP,
    /* 0x01 */ MINIFROG_STATE_AIR,
    /* 0x02 */ MINIFROG_STATE_GROUND
} MinifrogJumpState;

typedef struct EnMinifrog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTable[24];
    /* 0x218 */ Vec3s transitionDrawTable[24];
    /* 0x2A8 */ EnMinifrogActionFunc actionFunc;
    /* 0x2AC */ struct EnMinifrog* frog;
    /* 0x2B0 */ s16 frogIndex;
    /* 0x2B2 */ s16 jumpState;
    /* 0x2B4 */ s16 timer;
    /* 0x2B6 */ u16 flags;
    /* 0x2B8 */ ColliderCylinder collider;
} EnMinifrog; // size = 0x304

extern const ActorInit En_Minifrog_InitVars;

#endif // Z_EN_MINIFROG_H
