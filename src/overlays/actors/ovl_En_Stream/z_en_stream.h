#ifndef Z_EN_STREAM_H
#define Z_EN_STREAM_H

#include "global.h"

struct EnStream;

typedef struct EnStream {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC];
} EnStream; // size = 0x150

extern const ActorInit En_Stream_InitVars;

#endif // Z_EN_STREAM_H
