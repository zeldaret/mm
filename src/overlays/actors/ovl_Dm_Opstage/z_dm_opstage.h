#ifndef Z_DM_OPSTAGE_H
#define Z_DM_OPSTAGE_H

#include "global.h"

struct DmOpstage;

typedef void (*DmOpstageActionFunc)(struct DmOpstage*, GlobalContext*);

typedef struct DmOpstage {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ char pad15C[0x48];
    /* 0x1A4 */ f32 unk1A4;                         /* inferred */
    /* 0x1A8 */ f32 unk1A8;                         /* inferred */
    /* 0x1AC */ f32 unk1AC;                         /* inferred */
    /* 0x1B0 */ char pad1B0[8];                     /* maybe part of unk1AC[3]? */
    /* 0x1B8 */ DmOpstageActionFunc actionFunc;

} DmOpstage;                                        /* size = 0x1C8 */ 

extern const ActorInit Dm_Opstage_InitVars;

#endif // Z_DM_OPSTAGE_H
