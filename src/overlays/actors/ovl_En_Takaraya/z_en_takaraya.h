#ifndef Z_EN_TAKARAYA_H
#define Z_EN_TAKARAYA_H

#include "global.h"

struct EnTakaraya;

typedef void (*EnTakarayaActionFunc)(struct EnTakaraya*, PlayState*);

typedef struct EnTakaraya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;                   /* inferred */
    /* 0x188 */ Vec3s unk188;                       /* inferred */
    /* 0x18E */ char pad18E[0x8A];                  /* maybe part of unk188[0x18]? */
    /* 0x218 */ Vec3s unk218;                       /* inferred */
    /* 0x21E */ char pad21E[0x8A];                  /* maybe part of unk218[0x18]? */
    /* 0x2A8 */ EnTakarayaActionFunc actionFunc;
    /* 0x2AC */ s8 unk2AC;
    /* 0x2AD */ u8 unk2AD;                          /* inferred */
    /* 0x2AE */ char pad2AE[4];                     /* maybe part of unk2AD[5]? */
    /* 0x2B2 */ s16 unk2B2;
    /* 0x2B4 */ char pad2B4[8];                     /* maybe part of unk2B2[5]? */
} EnTakaraya;                                       /* size = 0x2BC */

#endif // Z_EN_TAKARAYA_H
