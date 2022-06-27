#ifndef Z_BG_IKNV_DOUKUTU_H
#define Z_BG_IKNV_DOUKUTU_H

#include "global.h"

struct BgIknvDoukutu;

typedef void (*BgIknvDoukutuActionFunc)(struct BgIknvDoukutu*, PlayState*);

typedef struct BgIknvDoukutu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
    /* 0x164 */ BgIknvDoukutuActionFunc actionFunc;
} BgIknvDoukutu; // size = 0x168

extern const ActorInit Bg_Iknv_Doukutu_InitVars;

#endif // Z_BG_IKNV_DOUKUTU_H
