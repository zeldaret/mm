#ifndef Z_EN_TEST4_H
#define Z_EN_TEST4_H

#include "global.h"

struct EnTest4;

#define TEST4_GET_SKYBOX_NUM_STARS(thisx) (((thisx)->params >> 10) * 100)
#define TEST4_GET_BIG_BELLS_SFX_VOLUME_INDEX(thisx) (((thisx)->params >> 5) & 0xF)

typedef void (*EnTest4ActionFunc)(struct EnTest4*, PlayState*);

typedef struct EnTest4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s8 csIdIndex; // 0 on night, 1 on day
    /* 0x145 */ u8 transitionCsTimer;
    /* 0x146 */ u16 unk_146;
    /* 0x148 */ u16 nextBellTime; // Next time the bell will sound
    /* 0x14A */ u16 lastBellTime; // Last time the bell sounded
    /* 0x14C */ u8 state;
    /* 0x150 */ EnTest4ActionFunc actionFunc;
} EnTest4; // size = 0x154

typedef enum {
    /* 0 */ TEST4_STATE_0,
    /* 1 */ TEST4_STATE_1
} EnTest4State;

#endif // Z_EN_TEST4_H
