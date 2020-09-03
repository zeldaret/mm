#ifndef _Z_DM_CHAR01_H_
#define _Z_DM_CHAR01_H_

#include <global.h>

struct DmChar01;

typedef struct DmChar01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20C];
} DmChar01; // size = 0x350

extern const ActorInit Dm_Char01_InitVars;

#endif
