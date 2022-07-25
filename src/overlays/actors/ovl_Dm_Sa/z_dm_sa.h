#ifndef Z_DM_SA_H
#define Z_DM_SA_H

#include "global.h"

struct DmSa;

typedef void (*DmSaActionFunc)(struct DmSa*, PlayState*);

typedef struct DmSa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ UNK_TYPE1 unk194[0x108];
    /* 0x290 */ DmSaActionFunc actionFunc;
    /* 0x294 */ UNK_TYPE1 unk294[0x20];
    /* 0x2B4 */ s32 unk2B4;
    /* 0x2B8 */ UNK_TYPE1 unk2B8[0x28];
    /* 0x2E0 */ u16 unk2E0;
    /* 0x2E2 */ UNK_TYPE1 unk2E2[0xE];
    /* 0x2F0 */ u32 alpha;
} DmSa; // size = 0x2F4

#endif // Z_DM_SA_H
