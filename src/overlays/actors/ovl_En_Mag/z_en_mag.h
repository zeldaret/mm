#ifndef _Z_EN_MAG_H_
#define _Z_EN_MAG_H_

#include <global.h>

struct EnMag;

typedef struct EnMag {
    /* 0x00000 */ Actor actor;
    /* 0x00144 */ char unk_00144[0x11E34];
} EnMag; // size = 0x11F78

extern const ActorInit En_Mag_InitVars;

#endif
