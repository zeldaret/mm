#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"

struct EnTg;

typedef void (*EnTgActionFunc)(struct EnTg*, GlobalContext*);

typedef struct EnTg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTgActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ char unk1D8[0x18]; // 24 bytes
    /* 0x01F0 */ Vec3s jointTable[21];
    /* 0x026E */ Vec3s morphTable[21];
    /* 0x02EC */ int unk2EC;
    /* 0x02F0 */ UNK_TYPE1 unk2F0[0xC];
    /* 0x02FC */ UNK_TYPE1 unk2FC[0x24C];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
