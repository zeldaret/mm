#ifndef Z_BG_IKNV_DOUKUTU_H
#define Z_BG_IKNV_DOUKUTU_H

#include "global.h"

struct BgIknvDoukutu;

typedef void (*BgIknvDoukutuActionFunc)(struct BgIknvDoukutu*, PlayState*);

#define BGIKNVDOUKUTU_GET_F(thisx) ((thisx)->params & 0xF)

typedef struct BgIknvDoukutu {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s16 unk_15C;
    /* 0x15E */ u16 unk_15E;
    /* 0x160 */ f32 unk_160;
    /* 0x164 */ BgIknvDoukutuActionFunc actionFunc;
} BgIknvDoukutu;// size = 0x168

extern const ActorInit Bg_Iknv_Doukutu_InitVars;

#endif // Z_BG_IKNV_DOUKUTU_H
