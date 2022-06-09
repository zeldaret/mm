#ifndef Z_DM_BAL_H
#define Z_DM_BAL_H

#include "global.h"

struct DmBal;

typedef void (*DmBalActionFunc)(struct DmBal*, GlobalContext*);

typedef struct DmBal {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;                
    /* 0x188 */ DmBalActionFunc actionFunc;
    /* 0x18C */ f32 unk18C;                         
    /* 0x190 */ f32 unk190;                        
    /* 0x194 */ f32 unk194;                         
    /* 0x198 */ s32 unk198;
    /* 0x19C */ Vec3s morphTable;
    /* 0x1A2 */ char pad1A2[0xC0];                  
    /* 0x262 */ Vec3s joinTable;
    /* 0x268 */ char pad268[0xCC];                  
    /* 0x334 */ s16 unk334;
    /* 0x336 */ s16 unk336;
    /* 0x338 */ s16 unk338;                         
    /* 0x33A */ s16 unk33A;                        
} DmBal;    /* size = 0x33C */                                           

extern const ActorInit Dm_Bal_InitVars;

#endif // Z_DM_BAL_H
