#ifndef Z_EN_TAKARAYA_H
#define Z_EN_TAKARAYA_H

#include "global.h"

struct EnTakaraya;

typedef void (*EnTakarayaActionFunc)(struct EnTakaraya*, PlayState*);

typedef struct EnTakaraya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;
    /* 0x188 */ Vec3s unk188;
    /* 0x18E */ char pad18E[0x8A];
    /* 0x218 */ Vec3s unk218;
    /* 0x21E */ char pad21E[0x8A];
    /* 0x2A8 */ EnTakarayaActionFunc actionFunc;
    /* 0x2AC */ s8 unk2AC;
    /* 0x2AD */ u8 unk2AD;
    /* 0x2AE */ s16 unk2AE;
    /* 0x2B0 */ s16 unk2B0;
    /* 0x2B2 */ s16 unk2B2;
    /* 0x2B4 */ char pad2B4[8];
} EnTakaraya; /* size = 0x2BC */

#endif // Z_EN_TAKARAYA_H
