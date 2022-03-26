#ifndef Z_BG_SPDWEB_H
#define Z_BG_SPDWEB_H

#include "global.h"

struct BgSpdweb;

typedef void (*BgSpdwebActionFunc)(struct BgSpdweb*, GlobalContext*);

#define BGSPDWEB_GET_SWITCHFLAG(thisx) (((thisx)->params >> 8) & 0x7F)

#define BGSPDWEB_FF_0 0
#define BGSPDWEB_FF_1 1

typedef struct BgSpdweb {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ BgSpdwebActionFunc actionFunc;
    /* 0x0160 */ u8 switchFlag;
    /* 0x0161 */ u8 unk_161;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ f32 unk_164;
    /* 0x0168 */ ColliderTris collider;
    /* 0x0188 */ ColliderTrisElement colliderElements[4];
    /* 0x02F8 */ Vec3s* unk_2F8;
} BgSpdweb; // size = 0x2FC

extern const ActorInit Bg_Spdweb_InitVars;

#endif // Z_BG_SPDWEB_H
