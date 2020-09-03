#ifndef _Z_EN_ELFGRP_H_
#define _Z_EN_ELFGRP_H_

#include <global.h>

struct EnElfgrp;

typedef struct EnElfgrp {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC];
} EnElfgrp; // size = 0x150

extern const ActorInit En_Elfgrp_InitVars;

#endif
