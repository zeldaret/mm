#ifndef _Z_BG_KEIKOKU_SAKU_H_
#define _Z_BG_KEIKOKU_SAKU_H_

#include <global.h>

struct BgKeikokuSaku;

typedef struct BgKeikokuSaku {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} BgKeikokuSaku; // size = 0x164

extern const ActorInit Bg_Keikoku_Saku_InitVars;

#endif
