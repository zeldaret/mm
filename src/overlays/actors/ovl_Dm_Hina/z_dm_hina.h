#ifndef Z_DM_HINA_H
#define Z_DM_HINA_H

#include "global.h"

struct DmHina;

typedef void (*DmHinaActionFunc)(struct DmHina*, PlayState*);

typedef struct DmHina {
    /* 0x000 */ Actor actor;
    /* 0x144 */ DmHinaActionFunc actionFunc;
    /* 0x148 */ f32 unk_148;
    /* 0x14C */ f32 unk_14C;
    /* 0x150 */ f32 unk_150;
    /* 0x154 */ f32 unk_154;
    /* 0x158 */ f32 unk_158;
    /* 0x15C */ f32 unk_15C;
    /* 0x160 */ Vec3f subCamEye;
    /* 0x16C */ Vec3f subCamAt;
    /* 0x178 */ UNK_TYPE1 pad_160[2];
    /* 0x17A */ s16 subCamId;
    /* 0x17C */ s16 timer;
    /* 0x17E */ u8 unk_17E;
    /* 0x17F */ u8 unk_17F;
    /* 0x180 */ u8 unk_180;
} DmHina; // size = 0x184

extern const ActorInit Dm_Hina_InitVars;

#endif // Z_DM_HINA_H
