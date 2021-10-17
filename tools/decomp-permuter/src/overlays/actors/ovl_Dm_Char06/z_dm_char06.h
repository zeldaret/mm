#ifndef Z_DM_CHAR06_H
#define Z_DM_CHAR06_H

#include <global.h>

struct DmChar06;

typedef struct DmChar06 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x160];
} DmChar06; // size = 0x2A4

extern const ActorInit Dm_Char06_InitVars;

#endif // Z_DM_CHAR06_H
