#ifndef Z_EN_STOP_HEISHI_H
#define Z_EN_STOP_HEISHI_H

#include <global.h>

struct EnStopheishi;

typedef struct EnStopheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1A4];
} EnStopheishi; // size = 0x2E8

extern const ActorInit En_Stop_heishi_InitVars;

#endif // Z_EN_STOP_HEISHI_H
