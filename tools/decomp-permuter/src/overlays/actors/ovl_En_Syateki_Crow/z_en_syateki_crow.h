#ifndef Z_EN_SYATEKI_CROW_H
#define Z_EN_SYATEKI_CROW_H

#include <global.h>

struct EnSyatekiCrow;

typedef struct EnSyatekiCrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x158];
} EnSyatekiCrow; // size = 0x29C

extern const ActorInit En_Syateki_Crow_InitVars;

#endif // Z_EN_SYATEKI_CROW_H
