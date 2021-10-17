#ifndef Z_EN_TITE_H
#define Z_EN_TITE_H

#include <global.h>

struct EnTite;

typedef struct EnTite {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C0];
} EnTite; // size = 0x404

extern const ActorInit En_Tite_InitVars;

#endif // Z_EN_TITE_H
