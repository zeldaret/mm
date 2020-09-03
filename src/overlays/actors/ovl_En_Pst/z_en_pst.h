#ifndef _Z_EN_PST_H_
#define _Z_EN_PST_H_

#include <global.h>

struct EnPst;

typedef struct EnPst {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xDC];
} EnPst; // size = 0x220

extern const ActorInit En_Pst_InitVars;

#endif
