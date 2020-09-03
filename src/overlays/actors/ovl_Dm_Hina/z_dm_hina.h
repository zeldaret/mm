#ifndef _Z_DM_HINA_H_
#define _Z_DM_HINA_H_

#include <global.h>

struct DmHina;

typedef struct DmHina {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x40];
} DmHina; // size = 0x184

extern const ActorInit Dm_Hina_InitVars;

#endif
