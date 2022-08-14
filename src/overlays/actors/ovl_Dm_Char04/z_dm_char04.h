#ifndef Z_DM_CHAR04_H
#define Z_DM_CHAR04_H

#include "global.h"

struct DmChar04;

typedef void (*DmChar04ActionFunc)(struct DmChar04*, PlayState*);

typedef struct DmChar04 {
    /* 0x0000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[15];
    /* 0x1E2 */ Vec3s morphTable[15];
    /* 0x023C */ DmChar04ActionFunc actionFunc;
    /* 0x240 */ Color_RGBAf primColors;
    /* 0x250 */ Color_RGBAf envColors;
    /* 0x260 */ u8 csAction;
    /* 0x261 */ u8 animationIndex;
    /* 0x262 */ u16 timer;
} DmChar04; // size = 0x264

extern const ActorInit Dm_Char04_InitVars;

#endif // Z_DM_CHAR04_H
