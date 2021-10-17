#ifndef Z_EN_DNO_H
#define Z_EN_DNO_H

#include <global.h>

struct EnDno;

typedef struct EnDno {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x328];
} EnDno; // size = 0x46C

extern const ActorInit En_Dno_InitVars;

#endif // Z_EN_DNO_H
