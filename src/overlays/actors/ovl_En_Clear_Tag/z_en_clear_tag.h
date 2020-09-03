#ifndef _Z_EN_CLEAR_TAG_H_
#define _Z_EN_CLEAR_TAG_H_

#include <global.h>

struct EnClearTag;

typedef struct EnClearTag {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x2D40];
} EnClearTag; // size = 0x2E84

extern const ActorInit En_Clear_Tag_InitVars;

#endif
