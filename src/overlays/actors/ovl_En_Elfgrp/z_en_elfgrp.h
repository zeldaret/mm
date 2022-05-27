#ifndef Z_EN_ELFGRP_H
#define Z_EN_ELFGRP_H

#include "global.h"

struct EnElfgrp;

typedef void (*EnElfgrpActionFunc)(struct EnElfgrp*, GlobalContext*);

#define ENELFGRP_GET(thisx) ((thisx)->params & 0xF)
#define ENELFGRP_GET_FE00(thisx) (((thisx)->params & 0xFE00) >> 9)

enum {
    /* 0 */ ENELFGRP_0,
    /* 2 */ ENELFGRP_1,
    /* 2 */ ENELFGRP_2,
    /* 3 */ ENELFGRP_3,
    /* 4 */ ENELFGRP_4,
};

typedef struct EnElfgrp {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ s16 unk_144;
    /* 0x0146 */ u8 unk_146;
    /* 0x0147 */ u8 unk_147;
    /* 0x0148 */ s8 unk_148;
    /* 0x014A */ u16 unk_14A;
    /* 0x014C */ EnElfgrpActionFunc actionFunc;
} EnElfgrp; // size = 0x150

extern const ActorInit En_Elfgrp_InitVars;

#endif // Z_EN_ELFGRP_H
