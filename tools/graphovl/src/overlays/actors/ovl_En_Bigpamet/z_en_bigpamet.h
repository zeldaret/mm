#ifndef Z_EN_BIGPAMET_H
#define Z_EN_BIGPAMET_H

#include "global.h"

struct EnBigpamet;

typedef void (*EnBigpametActionFunc)(struct EnBigpamet*, GlobalContext*);

typedef struct EnBigpamet {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x154];
    /* 0x0298 */ EnBigpametActionFunc actionFunc;
    /* 0x029C */ char unk_29C[0x10];
    /* 0x02AC */ f32 unk_2AC;
    /* 0x02B0 */ char unk_2B0[0x31C];
} EnBigpamet; // size = 0x5CC

extern const ActorInit En_Bigpamet_InitVars;

#endif // Z_EN_BIGPAMET_H
