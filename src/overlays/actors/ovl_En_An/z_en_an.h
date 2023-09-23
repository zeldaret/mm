#ifndef Z_EN_AN_H
#define Z_EN_AN_H

#include "global.h"

struct EnAn;

typedef void (*EnAnActionFunc)(struct EnAn*, PlayState*);

#define ENAN_GET_8000(thisx) (((thisx)->params & 0x8000) >> 0xF)

typedef struct EnAn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ UNK_TYPE1 unk_144[0x44];
    /* 0x188 */ EnAnActionFunc actionFunc;
    /* 0x18C */ UNK_TYPE1 unk_18C[0x4];
    /* 0x190 */ ColliderCylinder unk_190;
    /* 0x1DC */ UNK_TYPE1 pad_1DC[0x214-0x1DC];
    /* 0x214 */ s8 unk_214;
    /* 0x215 */ UNK_TYPE1 unk_215[0x3];
    /* 0x218 */ UNK_TYPE1 unk_218[0x3B8-0x218];
    /* 0x3B8 */ s32 unk_3B8;
    /* 0x3BC */ UNK_TYPE1 unk_3BC[0x3C8-0x3BC];
} EnAn; // size = 0x3C8

#endif // Z_EN_AN_H
