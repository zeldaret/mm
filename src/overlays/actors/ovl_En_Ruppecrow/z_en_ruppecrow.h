#ifndef Z_EN_RUPPECROW_H
#define Z_EN_RUPPECROW_H

#include "global.h"

struct EnRuppecrow;

typedef void (*EnRuppecrowActionFunc)(struct EnRuppecrow*, GlobalContext*);

typedef struct EnRuppecrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE unk_144[20];
    /* 0x0194 */ SkelAnime skelAnime;
    /* 0x01D8 */ EnRuppecrowActionFunc actionFunc;
    /* 0x01DC */ UNK_TYPE unk_1DC;
    /* 0x01E0 */ Vec3s joinTable[9];
    /* 0x0216 */ Vec3s morphTable[9];
    /* 0x024C */ Path* path;
    /* 0x0250 */ UNK_TYPE unk_250;
    /* 0x0254 */ ColliderJntSph collider;
    /* 0x0274 */ ColliderJntSphElement colliderElement;
    /* 0x02B4 */ UNK_TYPE unk_2B4[80];
} EnRuppecrow; // size = 0x304

extern const ActorInit En_Ruppecrow_InitVars;

#endif // Z_EN_RUPPECROW_H
