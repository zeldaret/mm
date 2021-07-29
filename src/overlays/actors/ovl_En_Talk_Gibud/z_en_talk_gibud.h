#ifndef Z_EN_TALK_GIBUD_H
#define Z_EN_TALK_GIBUD_H

#include "global.h"

struct EnTalkGibud;

typedef void (*EnTalkGibudActionFunc)(struct EnTalkGibud* this, GlobalContext* globalCtx);

typedef struct EnTalkGibud {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnTalkGibudActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x220];
} EnTalkGibud; // size = 0x3F8

extern const ActorInit En_Talk_Gibud_InitVars;

#endif // Z_EN_TALK_GIBUD_H
