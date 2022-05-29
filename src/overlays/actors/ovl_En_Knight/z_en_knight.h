#ifndef Z_EN_KNIGHT_H
#define Z_EN_KNIGHT_H

#include "global.h"

struct EnKnight;

typedef void (*EnKnightActionFunc)(struct EnKnight*, GlobalContext*);

typedef struct EnKnight {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ s16 unk_144;
    /* 0x0146 */ char unk_146[0x2];
    /* 0x0148 */ s8 unk_148;
    /* 0x0149 */ char pad149[8];
    /* 0x0151 */ s8 unk_151;
    /* 0x0152 */ char pad152[1];
    /* 0x0153 */ u8 unk_153;
    /* 0x0154 */ u8 unk_154;
    /* 0x0155 */ char pad155[0x2CB];
    /* 0x0420 */ EnKnightActionFunc actionFunc;
    /* 0x0424 */ char unk_424[0x25C];
    /* 0x0680 */ u8 unk_680;
    /* 0x0681 */ char pad681[9];
    /* 0x068A */ s16 unk_68A;
    /* 0x068C */ char pad68C[0x48];
} EnKnight; // size = 0x6D4

extern const ActorInit En_Knight_InitVars;

#endif // Z_EN_KNIGHT_H
