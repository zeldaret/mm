#ifndef Z_EN_BH_H
#define Z_EN_BH_H

#include "global.h"

struct EnBh;

typedef void (*EnBhActionFunc)(struct EnBh*, PlayState*);

typedef struct EnBh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelanime;
    /* 0x188 */ Vec3s unk188;
    /* 0x18E */ UNK_TYPE1 pad18E[0x1E];
    /* 0x1AC */ Vec3s unk1AC;
    /* 0x1B2 */ UNK_TYPE1 pad1B2[0x1E];
    /* 0x1D0 */ Vec3f pos;
    /* 0x1DC */ s16 timer;
    /* 0x1DE */ s16 timer2;
    /* 0x1E0 */ s16 step;
    /* 0x1E2 */ s16 unk1E2;
    /* 0x1E4 */ s16 unk1E4;
    /* 0x1E6 */ UNK_TYPE1 pad1E6[2];
    /* 0x01E8 */ EnBhActionFunc actionFunc;
} EnBh; // size = 0x1EC

extern const ActorInit En_Bh_InitVars;

#endif // Z_EN_BH_H
