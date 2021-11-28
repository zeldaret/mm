#ifndef Z_EN_TALK_H
#define Z_EN_TALK_H

#include "global.h"

struct EnTalk;

typedef void (*EnTalkActionFunc)(struct EnTalk*, GlobalContext*);

typedef struct EnTalk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTalkActionFunc actionFunc;
} EnTalk; // size = 0x148

extern const ActorInit En_Talk_InitVars;

#define GET_TEXT_ID(this) ((this->actor.params & 0x3F) + 0x1C00)

#endif // Z_EN_TALK_H
