#ifndef Z_EN_SB_H
#define Z_EN_SB_H

#include <global.h>

struct EnSb;

typedef void (*EnSbActionFunc)(struct EnSb*, GlobalContext*);

typedef enum {
    /* 0x00 */ SHELLBLADE_OPEN,
    /* 0x01 */ SHELLBLADE_WAIT_CLOSED,
    /* 0x02 */ SHELLBLADE_WAIT_OPEN,
    /* 0x03 */ SHELLBLADE_LUNGE,
    /* 0x04 */ SHELLBLADE_BOUNCE
} ShellbladeState;

typedef struct EnSb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s limbDrawTable[9];
    /* 0x1BE */ Vec3s transitionDrawTable[9];
    /* 0x1F4 */ EnSbActionFunc actionFunc;
    /* 0x1F8 */ ColliderCylinder collider;
    /* 0x244 */ s16 fireCount;
    /* 0x246 */ s16 state;
    /* 0x248 */ s16 isDead;
    /* 0x24A */ s16 attackTimer;
    /* 0x24C */ s16 vulnerableTimer;
    /* 0x24E */ s16 yawAngle;
    /* 0x250 */ s16 bounceCounter;
    /* 0x252 */ u8 unk_252;
    /* 0x253 */ u8 isDrawn;
} EnSb; // size = 0x254

extern const ActorInit En_Sb_InitVars;

#endif // Z_EN_SB_H
