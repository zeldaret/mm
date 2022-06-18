#ifndef Z_DM_OPSTAGE_H
#define Z_DM_OPSTAGE_H

#include "global.h"

#define DMOPSTAGE_GET_TYPE(thisx) (((thisx)->params & 0xFF))
#define DMOPSTAGE_GET_08(thisx) (((thisx)->params >> 8) & 0xFF)

struct DmOpstage;

typedef void (*DmOpstageActionFunc)(struct DmOpstage*, GlobalContext*);
typedef struct DmOpstage {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ UNK_TYPE1 pad_15C[0x44];
    /* 0x1A0 */ DmOpstageActionFunc actionFunc;
    /* 0x1A4 */ Vec3f pos;
} DmOpstage; // size = 0x1B0

typedef enum {
    /* 0 */ DM_OPSTAGE_TYPE_FLOOR,
    /* 1 */ DM_OPSTAGE_TYPE_TREE1,
    /* 2 */ DM_OPSTAGE_TYPE_TREE2,
    /* 3 */ DM_OPSTAGE_TYPE_TREE3,
} DmOpStageTypes;

extern const ActorInit Dm_Opstage_InitVars;

#endif // Z_DM_OPSTAGE_H
