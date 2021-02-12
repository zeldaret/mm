#ifndef Z_EN_RSN_H
#define Z_EN_RSN_H

#include <global.h>

struct EnRsn;

typedef void (*EnRsnActionFunc)(struct BgHakaCurtain*, GlobalContext*);

typedef struct EnRsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk144[0x4C];
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnRsnActionFunc actionFunc;
    /* 0x1D8 */ Vec3s unk1D8;
    /* 0x1DE */ Vec3s unk1DE;
} EnRsn; // size = 0x1E4

extern const ActorInit En_Rsn_InitVars;

#endif // Z_EN_RSN_H
