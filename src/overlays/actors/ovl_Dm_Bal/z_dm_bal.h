#ifndef Z_DM_BAL_H
#define Z_DM_BAL_H

#include "global.h"
#include "objects/object_bal/object_bal.h"

struct DmBal;

typedef void (*DmBalActionFunc)(struct DmBal*, GlobalContext*);

typedef struct DmBal {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ DmBalActionFunc actionFunc;
    /* 0x18C */ f32 unk_18C;
    /* 0x190 */ f32 unk_190; 
    /* 0x194 */ f32 unk_194;
    /* 0x198 */ s32 unk_198;
    /* 0x262 */ Vec3s jointTable[OBJECT_BAL_LIMB_MAX];
    /* 0x19C */ Vec3s morphTable[OBJECT_BAL_LIMB_MAX];
    /* 0x328 */ UNK_TYPE1 pad_328[12];
    /* 0x334 */ s16 unk_334;
    /* 0x336 */ s16 unk_336; 
    /* 0x338 */ s16 unk_338;
    /* 0x33A */ s16 unk_33A;
} DmBal; /* size = 0x33C */

extern const ActorInit Dm_Bal_InitVars;

#endif // Z_DM_BAL_H
