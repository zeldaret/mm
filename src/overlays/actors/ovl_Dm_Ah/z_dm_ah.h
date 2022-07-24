#ifndef Z_DM_AH_H
#define Z_DM_AH_H

#include "global.h"

struct DmAh;

typedef void (*DmAhActionFunc)(struct DmAh*, PlayState*);

typedef struct DmAh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;
    /* 0x188 */ DmAhActionFunc actionFunc;
    /* 0x18C */ char pad18C[0x24];
    /* 0x1B0 */ Vec3s unk1B0;
    /* 0x1B6 */ char pad1B6[0x60];
    /* 0x216 */ Vec3s unk216;
    /* 0x21C */ char pad21C[0x60];
    /* 0x27C */ u16 unk27C;
    /* 0x27E */ u8 unk27E;
    /* 0x27F */ char pad27F[1];
    /* 0x280 */ Player* unk280;
    /* 0x284 */ s16 unk284;
    /* 0x286 */ s16 unk286;
    /* 0x288 */ s16 unk288;
    /* 0x28A */ s16 unk28A;
    /* 0x28C */ s16 unk28C;
    /* 0x28E */ s16 unk28E;
    /* 0x290 */ s16 unk290;
    /* 0x292 */ char pad292[2];
    /* 0x294 */ s32 unk294;
    /* 0x298 */ s32 unk298;
    /* 0x29C */ s32 unk29C;
} DmAh; // size = 0x2A0

extern const ActorInit Dm_Ah_InitVars;

#endif // Z_DM_AH_H
