#ifndef Z_EN_STREAM_H
#define Z_EN_STREAM_H

#include "global.h"

struct EnStream;

typedef void (*EnStreamActionFunc)(struct EnStream*, GlobalContext*);

typedef struct EnStream {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnStreamActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x8];
} EnStream; // size = 0x150

extern const ActorInit En_Stream_InitVars;

#endif // Z_EN_STREAM_H
