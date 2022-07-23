#ifndef Z_DM_AL_H
#define Z_DM_AL_H

#include "global.h"
#include "objects/object_al/object_al.h"

struct DmAl;

typedef void (*DmAlActionFunc)(struct DmAl*, PlayState*);

typedef struct DmAl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ DmAlActionFunc actionFunc;
    /* 0x18C */ MtxF shawlMatrices[6];
    /* 0x30C */ Vec3s jointTable[MADAME_AROMA_LIMB_MAX];
    /* 0x3AE */ Vec3s morphTable[MADAME_AROMA_LIMB_MAX];
    /* 0x450 */ u8 action;
    /* 0x454 */ s32 animationIndex;
    /* 0x458 */ s32 animationIndex2;
    /* 0x45C */ s32 unk_45C;
} DmAl; // size = 0x460

typedef enum {
    /* 0x0 */ MADAME_AROMA_ANIMATION_0,
    /* 0x1 */ MADAME_AROMA_ANIMATION_1
} DmAlAnimations;

extern const ActorInit Dm_Al_InitVars;

#endif // Z_DM_AL_H
