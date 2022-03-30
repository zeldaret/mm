#ifndef Z_EN_FU_MATO_H
#define Z_EN_FU_MATO_H

#include "global.h"

struct EnFuMato;

typedef void (*EnFuMatoActionFunc)(struct EnFuMato*, GlobalContext*);

#define ENFUMATO_GET(thisx) ((thisx)->params)

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3s unk_24;
    /* 0x2A */ Vec3s unk_2A;
    /* 0x30 */ s16 unk_30;
} EnFuMatoStruct; // size = 0x34

typedef struct EnFuMato {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ EnFuMatoActionFunc actionFunc;
    /* 0x0160 */ ColliderSphere collider;
    /* 0x01B8 */ EnFuMatoStruct unk_1B8[6];
    /* 0x02F0 */ s32 unk_2F0;
    /* 0x02F4 */ s32 unk_2F4;
    /* 0x02F8 */ Vec3s* unk_2F8;
    /* 0x02FC */ Vec3s unk_2FC;
    /* 0x0302 */ s16 unk_302;
    /* 0x0304 */ s16 unk_304;
    /* 0x0306 */ UNK_TYPE1 unk306[2];
    /* 0x0308 */ s16 unk_308;
    /* 0x030A */ s16 unk_30A;
} EnFuMato; // size = 0x30C

extern const ActorInit En_Fu_Mato_InitVars;

#endif // Z_EN_FU_MATO_H
