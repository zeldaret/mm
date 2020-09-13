#ifndef Z_EN_TALK_H
#define Z_EN_TALK_H

#include <global.h>

struct EnTalk;

typedef struct EnTalk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} EnTalk; // size = 0x148

extern const ActorInit En_Talk_InitVars;

#endif // Z_EN_TALK_H
