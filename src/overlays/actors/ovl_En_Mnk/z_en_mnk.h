#ifndef _Z_EN_MNK_H_
#define _Z_EN_MNK_H_

#include <global.h>

struct EnMnk;

typedef struct EnMnk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2A8];
} EnMnk; // size = 0x3EC

extern const ActorInit En_Mnk_InitVars;

#endif
