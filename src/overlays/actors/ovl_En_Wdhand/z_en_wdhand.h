#ifndef Z_EN_WDHAND_H
#define Z_EN_WDHAND_H

#include "global.h"

struct EnWdhand;

typedef void (*EnWdhandActionFunc)(struct EnWdhand*, PlayState*);

typedef struct EnWdhand {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;
    /* 0x188 */ Vec3s unk188[8];
    /* 0x1B8 */ Vec3s unk1B8[8];
    /* 0x1E8 */ EnWdhandActionFunc actionFunc;
    /* 0x1EC */ Vec3s unk1EC[5];
    /* 0x20C */ f32 unk20C;
    /* 0x20C */ f32 unk210[3];
    /* 0x21C */ MtxF unk21C;
    /* 0x25C */ Vec3f unk25C[2];
    /* 0x274 */ ColliderJntSph unk274;
    /* 0x294 */ ColliderJntSphElement unk294[7];
} EnWdhand; // size = 0x454

#endif // Z_EN_WDHAND_H
