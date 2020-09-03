#ifndef _Z_BG_KEIKOKU_SPR_H_
#define _Z_BG_KEIKOKU_SPR_H_

#include <global.h>

struct BgKeikokuSpr;

typedef struct BgKeikokuSpr {
    /* 0x000 */ Actor actor;
} BgKeikokuSpr; // size = 0x144

extern const ActorInit Bg_Keikoku_Spr_InitVars;

#endif
