#ifndef _Z_EN_FSN_H_
#define _Z_EN_FSN_H_

#include <global.h>

struct EnFsn;

typedef struct EnFsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x30C];
} EnFsn; // size = 0x450

extern const ActorInit En_Fsn_InitVars;

#endif
