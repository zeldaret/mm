#ifndef Z_EN_NB_H
#define Z_EN_NB_H

#include "global.h"

struct EnNb;

typedef void (*EnNbActionFunc)(struct EnNb*, GlobalContext*);
typedef s32 (*EnNbActionFunc2)(struct EnNb*, GlobalContext*);

typedef struct EnNb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnNbActionFunc actionFunc;
    /* 0x18C */ EnNbActionFunc unk_18C;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ u8 unk_1DC;
    /* 0x1DD */ char unk_1DD[0x3];
    /* 0x1E0 */ void* unk_1E0;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ Actor* unk_1E8;
    /* 0x1EC */ char unk_1EC[0x16];
    /* 0x202 */ Vec3s jointTable[8];
    /* 0x232 */ Vec3s morphTable[8];
    /* 0x262 */ u16 unk_262;
    /* 0x264 */ char unk_264[0x28];
    /* 0x28C */ EnNbActionFunc2 unk_28C;
    /* 0x290 */ s32 unk_290;
    /* 0x294 */ char unk_294[0x8];
} EnNb; // size = 0x29C

extern const ActorInit En_Nb_InitVars;

#endif // Z_EN_NB_H
