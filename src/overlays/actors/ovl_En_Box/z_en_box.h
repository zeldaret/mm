#ifndef Z_EN_BOX_H
#define Z_EN_BOX_H

#include "global.h"

struct EnBox;

typedef void (*EnBoxActionFunc)(struct EnBox*, GlobalContext*);

typedef struct EnBox {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xAC];
    /* 0x01F0 */ char unk_1F0[0x01];
    /* 0x01F1 */ u8 unk_1F1;
    /* 0x01F2 */ char unk_1F2[0x02];
    /* 0x01F4 */ char unk_1F4[0x0C];
    /* 0x0200 */ EnBoxActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0x20];
} EnBox; // size = 0x224

extern const ActorInit En_Box_InitVars;

#endif // Z_EN_BOX_H
