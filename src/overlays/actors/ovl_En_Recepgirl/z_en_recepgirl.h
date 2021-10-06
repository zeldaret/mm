#ifndef Z_EN_RECEPGIRL_H
#define Z_EN_RECEPGIRL_H

#include "global.h"

struct EnRecepgirl;

typedef void (*EnRecepgirlActionFunc)(struct EnRecepgirl*, GlobalContext*);

typedef struct EnRecepgirl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[24];
    /* 0x0218 */ Vec3s morphTable[24];
    /* 0x02A8 */ EnRecepgirlActionFunc actionFunc;
    /* 0x02AC */ u8 unk_2AC;
    /* 0x02AE */ Vec3s unk_2AE;
} EnRecepgirl; // size = 0x2B4

extern const ActorInit En_Recepgirl_InitVars;

#endif // Z_EN_RECEPGIRL_H
