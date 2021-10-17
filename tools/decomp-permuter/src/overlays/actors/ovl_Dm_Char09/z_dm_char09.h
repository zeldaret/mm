#ifndef Z_DM_CHAR09_H
#define Z_DM_CHAR09_H

#include <global.h>

struct DmChar09;

typedef struct DmChar09 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xEC];
} DmChar09; // size = 0x230

extern const ActorInit Dm_Char09_InitVars;

#endif // Z_DM_CHAR09_H
