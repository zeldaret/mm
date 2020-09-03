#ifndef _Z_DM_NB_H_
#define _Z_DM_NB_H_

#include <global.h>

struct DmNb;

typedef struct DmNb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xB8];
} DmNb; // size = 0x1FC

extern const ActorInit Dm_Nb_InitVars;

#endif
