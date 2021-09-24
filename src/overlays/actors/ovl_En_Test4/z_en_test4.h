#ifndef Z_EN_TEST4_H
#define Z_EN_TEST4_H

#include "global.h"

struct EnTest4;

typedef void (*EnTest4ActionFunc)(struct EnTest4*, GlobalContext*);

typedef struct EnTest4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ s8 unk_144; // 0 on night, 1 on day
    /* 0x0145 */ u8 transitionCsTimer;
    /* 0x0146 */ u16 unk_146;
    /* 0x0148 */ u16 nextBellTime; // Next time the bell will sound
    /* 0x014A */ u16 lastBellTime; // Last time the bell sounded
    /* 0x014C */ u8 state;
    /* 0x0150 */ EnTest4ActionFunc actionFunc;
} EnTest4; // size = 0x154

typedef enum {
    /* 0 */ TEST4_STATE_0,
    /* 1 */ TEST4_STATE_1
} EnTest4State;

extern const ActorInit En_Test4_InitVars;

#endif // Z_EN_TEST4_H
