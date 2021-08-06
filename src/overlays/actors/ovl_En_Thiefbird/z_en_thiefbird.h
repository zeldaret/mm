#ifndef Z_EN_THIEFBIRD_H
#define Z_EN_THIEFBIRD_H

#include "global.h"

struct EnThiefbird;

typedef void (*EnThiefbirdActionFunc)(struct EnThiefbird*, GlobalContext*);

typedef struct EnThiefbird {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnThiefbirdActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x804];
} EnThiefbird; // size = 0x990

extern const ActorInit En_Thiefbird_InitVars;

#endif // Z_EN_THIEFBIRD_H
