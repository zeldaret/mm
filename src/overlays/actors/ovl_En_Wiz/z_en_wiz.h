#ifndef Z_EN_WIZ_H
#define Z_EN_WIZ_H

#include "global.h"

struct EnWiz;

typedef void (*EnWizActionFunc)(struct EnWiz*, GlobalContext*);

typedef struct EnWiz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x268];
    /* 0x03AC */ EnWizActionFunc actionFunc;
    /* 0x03B0 */ char unk_3B0[0xA];
    /* 0x03BA */ s16 unk_3BA;
    /* 0x03BC */ char unk_3BC[0x8C];
    /* 0x0448 */ s32 unk_448;
    /* 0x044C */ char unk_44C[0x2FE];
    /* 0x074A */ s16 unk_74A;
    /* 0x074C */ char unk_74C[0x634];
} EnWiz; // size = 0xD80

extern const ActorInit En_Wiz_InitVars;

#endif // Z_EN_WIZ_H
