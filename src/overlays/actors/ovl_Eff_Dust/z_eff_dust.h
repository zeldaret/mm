#ifndef Z_EFF_DUST_H
#define Z_EFF_DUST_H

#include <global.h>

struct EffDust;

typedef void (*EffDustActionFunc)(struct EffDust*, GlobalContext*);
typedef void (*EffDustDrawFunc)(Actor*, GlobalContext*);

typedef struct EffDust {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x414];
    /* 0x558 */ EffDustActionFunc actionFunc;
    /* 0x55C */ EffDustDrawFunc drawFunc;
} EffDust; // size = 0x560

extern const ActorInit Eff_Dust_InitVars;

#endif // Z_EFF_DUST_H
