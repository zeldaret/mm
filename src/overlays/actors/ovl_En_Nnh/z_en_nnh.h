#ifndef Z_EN_NNH_H
#define Z_EN_NNH_H

#include <global.h>

struct EnNnh;

typedef void (*EnNnhActionFunc)(struct EnNnh*, GlobalContext*);

typedef struct EnNnh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColCylinder collider;
    /* 0x190 */ EnNnhActionFunc actionFunc;
} EnNnh; // size = 0x194

extern const ActorInit En_Nnh_InitVars;

#endif // Z_EN_NNH_H
