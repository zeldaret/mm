#ifndef Z_DM_TSG_H
#define Z_DM_TSG_H

#include "global.h"

struct DmTsg;

typedef void (*DmTsgActionFunc)(struct DmTsg*, PlayState*);

typedef struct DmTsg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ UNK_TYPE4 unk_144;
    /* 0x148 */ Vec3f unk_148[100];
    /* 0x5F8 */ f32 unk_5F8[100];
    /* 0x788 */ f32 unk_788;
    /* 0x78C */ s16 unk_78C[100];
    /* 0x854 */ s16 unk_854;
    /* 0x856 */ s16 unk_856[100];
    /* 0x91E */ u8 unk_91E;
} DmTsg; // size = 0x920

#endif // Z_DM_TSG_H
