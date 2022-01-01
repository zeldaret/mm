#ifndef Z_EN_NEO_REEBA_H
#define Z_EN_NEO_REEBA_H

#include "global.h"

struct EnNeoReeba;

typedef void (*EnNeoReebaActionFunc)(struct EnNeoReeba*, GlobalContext*);

typedef struct EnNeoReeba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ ColliderCylinder collider;
    /* 0x01d4 */ Vec3s jointTable[18];
    /* 0x0240 */ Vec3s morphTable[18];
    /* 0x02AC */ EnNeoReebaActionFunc actionFunc;
    /* 0x02B0 */ Vec3f unk_2B0;
    /* 0x02BC */ Vec3f unk_2BC;
    /* 0x02C8 */ char unk_2C8[0x30];
    /* 0x02F8 */ f32 unk_2F8;
    /* 0x02FC */ f32 unk_2FC;
    /* 0x0300 */ f32 unk_300;
    /* 0x0304 */ f32 unk_304;
    /* 0x0308 */ s16 unk_308;
    /* 0x030A */ s16 unk_30A;
    /* 0x030C */ s16 unk_30C;
    /* 0x030E */ s16 unk_30E;
    /* 0x0310 */ s8 unk_310;
} EnNeoReeba; // size = 0x314

extern const ActorInit En_Neo_Reeba_InitVars;

#endif // Z_EN_NEO_REEBA_H
