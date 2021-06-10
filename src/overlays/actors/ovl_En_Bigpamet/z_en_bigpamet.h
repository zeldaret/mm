#ifndef Z_EN_BIGPAMET_H
#define Z_EN_BIGPAMET_H

#include <global.h>

struct EnBigpamet;

typedef struct EnBigpamet {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x168];
    /* 0x2AC */ f32 unk_2AC;
    /* 0x2B0 */ char unk_2B0[0x31C];
} EnBigpamet; // size = 0x5CC

extern const ActorInit En_Bigpamet_InitVars;

#endif // Z_EN_BIGPAMET_H
