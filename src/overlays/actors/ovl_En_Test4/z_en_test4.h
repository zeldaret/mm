#ifndef Z_EN_TEST4_H
#define Z_EN_TEST4_H

#include "global.h"

struct EnTest4;

typedef void (*EnTest4ActionFunc)(struct EnTest4*, GlobalContext*);

typedef struct EnTest4 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ s8 csIdx;
    /* 0x0145 */ u8 unk_145; // timer?
    /* 0x0146 */ u16 unk_146; // currentTime?
    /* 0x0148 */ u16 unk_148; // something time related
    /* 0x014A */ u16 unk_14A; // another time
    /* 0x014C */ u8 unk_14C; // state?
    /* 0x0150 */ EnTest4ActionFunc actionFunc;
} EnTest4; // size = 0x154

extern const ActorInit En_Test4_InitVars;

#endif // Z_EN_TEST4_H
