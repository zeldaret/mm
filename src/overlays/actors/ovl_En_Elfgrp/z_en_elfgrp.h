#ifndef Z_EN_ELFGRP_H
#define Z_EN_ELFGRP_H

#include "global.h"

struct EnElfgrp;

typedef void (*EnElfgrpActionFunc)(struct EnElfgrp*, GlobalContext*);

typedef struct EnElfgrp {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x8];
    /* 0x014C */ EnElfgrpActionFunc actionFunc;
} EnElfgrp; // size = 0x150

extern const ActorInit En_Elfgrp_InitVars;

#endif // Z_EN_ELFGRP_H
