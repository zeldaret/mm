#ifndef Z_BG_IKNV_DOUKUTU_H
#define Z_BG_IKNV_DOUKUTU_H

#include "global.h"

struct BgIknvDoukutu;

typedef void (*BgIknvDoukutuActionFunc)(struct BgIknvDoukutu*, GlobalContext*);

typedef struct BgIknvDoukutu {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x20];
    /* 0x0164 */ BgIknvDoukutuActionFunc actionFunc;
} BgIknvDoukutu; // size = 0x168

extern const ActorInit Bg_Iknv_Doukutu_InitVars;

#endif // Z_BG_IKNV_DOUKUTU_H
