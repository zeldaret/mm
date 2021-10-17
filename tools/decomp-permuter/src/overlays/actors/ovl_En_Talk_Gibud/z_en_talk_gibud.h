#ifndef Z_EN_TALK_GIBUD_H
#define Z_EN_TALK_GIBUD_H

#include <global.h>

struct EnTalkGibud;

typedef struct EnTalkGibud {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2B4];
} EnTalkGibud; // size = 0x3F8

extern const ActorInit En_Talk_Gibud_InitVars;

#endif // Z_EN_TALK_GIBUD_H
