#ifndef Z_DM_NB_H
#define Z_DM_NB_H

#include <global.h>

struct DmNb;

typedef void (*DmNbActionFunc)(struct DmNb*, GlobalContext*);

typedef struct DmNb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ DmNbActionFunc actionFunc;
    /* 0x18C */ Vec3s limbDrawTable[8];
    /* 0x1BC */ Vec3s transitionDrawTable[8];
    /* 0x1EC */ u8 unk1EC;
    /* 0x1F0 */ s32 unk1F0;
    /* 0x1F4 */ s32 unk1F4;
    /* 0x1F8 */ s32 unk1F8;
} DmNb; // size = 0x1FC

extern const ActorInit Dm_Nb_InitVars;

#endif // Z_DM_NB_H
