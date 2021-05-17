#ifndef Z_EN_MA_YTO_H
#define Z_EN_MA_YTO_H

#include <global.h>

struct EnMaYto;

typedef void (*EnMaYtoActionFunc)(struct EnMaYto*, GlobalContext*);

typedef struct EnMaYto {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ EnMaYtoActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ char unk_1D8[0x14C];
} EnMaYto; // size = 0x324

extern const ActorInit En_Ma_Yto_InitVars;

#endif // Z_EN_MA_YTO_H
