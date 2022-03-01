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
    /* 0x01D8 */ char unkA[0x18];
    /* 0x01F0 */ Vec3s jointTable[21];
    /* 0x026E */ Vec3s morphTable[21];
    /* 0x02EC */ 
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
