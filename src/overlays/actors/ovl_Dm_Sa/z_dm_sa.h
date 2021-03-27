#ifndef Z_DM_SA_H
#define Z_DM_SA_H

#include <global.h>

struct DmSa;

typedef void (*DmSaActionFunc)(struct DmSa*, GlobalContext*);

typedef struct DmSa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ char unk194[0x108];
    /* 0x290 */ DmSaActionFunc actionFunc;
    /* 0x294 */ char unk294[0x20];
    /* 0x2B4 */ s32 unk2B4;
    /* 0x2B8 */ char unk2B8[0x28];
    /* 0x2E0 */ u16 unk2E0;
    /* 0x2E2 */ char unk2E2[0xE];
    /* 0x2F0 */ u32 alpha;
} DmSa; // size = 0x2F4

extern const ActorInit Dm_Sa_InitVars;

#endif // Z_DM_SA_H
