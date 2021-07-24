#ifndef Z_BG_IKNV_DOUKUTU_H
#define Z_BG_IKNV_DOUKUTU_H

#include "global.h"

struct BgIknvDoukutu;

typedef struct BgIknvDoukutu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} BgIknvDoukutu; // size = 0x168

extern const ActorInit Bg_Iknv_Doukutu_InitVars;

#endif // Z_BG_IKNV_DOUKUTU_H
