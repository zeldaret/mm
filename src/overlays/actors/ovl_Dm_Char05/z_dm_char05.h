#ifndef Z_DM_CHAR05_H
#define Z_DM_CHAR05_H

#include "global.h"

struct DmChar05;

typedef void (*DmChar05ActionFunc)(struct DmChar05*, GlobalContext*);

typedef struct DmChar05 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ DmChar05ActionFunc actionFunc;
    /* 0x018C */ s16 unk_18C;
    /* 0x018E */ u8 unk_18E;
    /* 0x018F */ u8 unk_18F;
    /* 0x0190 */ Vec3f unk_190;
    /* 0x019C */ u32 unk_19C;
    /* 0x01A0 */ u32 unk_1A0;
    /* 0x01A4 */ u32 unk_1A4;
    /* 0x01A8 */ s32 unk_1A8;
    /* 0x01AC */ s32 unk_1AC;
    /* 0x01B0 */ s32 unk_1B0;
    /* 0x01B4 */ u8 unk_1B4;
} DmChar05; // size = 0x1B8

extern const ActorInit Dm_Char05_InitVars;

#endif // Z_DM_CHAR05_H
