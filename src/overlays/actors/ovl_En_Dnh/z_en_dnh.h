#ifndef Z_EN_DNH_H
#define Z_EN_DNH_H

#include "global.h"

struct EnDnh;

typedef void (*EnDnhActionFunc)(struct EnDnh*, PlayState*);

typedef struct EnDnh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnDnhActionFunc actionFunc;
    /* 0x148 */ SkelAnime unk148;
    /* 0x18C */ u16 unk18C;
    /* 0x18E */ char pad18E[2];
    /* 0x190 */ s32 unk190;
    /* 0x194 */ s32 unk194;
    /* 0x198 */ s16 unk198;
    /* 0x19A */ char pad19A[2];
    /* 0x19C */ s16 unk19C; /* inferred */
    /* 0x19E */ s16 unk19E;
    /* 0x1A0 */ s32* unk1A0;
    /* 0x1A4 */ Vec3s unk1A4;
    /* 0x1AA */ char pad1AA[6];
    /* 0x1B0 */ Vec3s unk1B0;
    /* 0x1B6 */ char pad1B6[6];
} EnDnh;
#endif // Z_EN_DNH_H

// EnDnhActionFunc actionFunc