#ifndef _Z_EN_BIGPAMET_H_
#define _Z_EN_BIGPAMET_H_

#include <global.h>

struct EnBigpamet;

typedef struct EnBigpamet {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x488];
} EnBigpamet; // size = 0x5CC

extern const ActorInit En_Bigpamet_InitVars;

#endif
