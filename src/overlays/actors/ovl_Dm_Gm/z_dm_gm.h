#ifndef Z_DM_GM_H
#define Z_DM_GM_H

#include "global.h"
#include "objects/object_an1/object_an1.h"

struct DmGm;

typedef void (*DmGmActionFunc)(struct DmGm*, PlayState*);

typedef struct DmGm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ DmGmActionFunc actionFunc;
    /* 0x18C */ Vec3f unk_18C;
    /* 0x18C */ Vec3f unk_194;
    /* 0x1A4 */ Vec3s unk_1A4;
    /* 0x1A4 */ Vec3s unk_1AA;
    /* 0x1B0 */ Vec3s jointTable[OBJECT_AN1_LIMB_MAX];
    /* 0x22E */ Vec3s morphTable[OBJECT_AN1_LIMB_MAX];
    /* 0x2AC */ s8 unk_2AC;
    /* 0x2AD */ s8 unk_2AD;
    /* 0x2AE */ u16 unk_2AE;
    /* 0x2B0 */ u8 cueId;
    /* 0x2B4 */ Actor* unk_2B4;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 unk_2BA;
    /* 0x2BC */ s16 unk_2BC;
    /* 0x2BE */ s16 unk_2BE;
    /* 0x2C0 */ s16 unk_2C0;
    /* 0x2C2 */ s16 unk_2C2;
    /* 0x2C4 */ s16 unk_2C4;
    /* 0x2C8 */ s32 animIndex;
    /* 0x2CC */ s32 prevAnimIndex;
    /* 0x2D0 */ s32 isCutscenePlaying;
    /* 0x2D4 */ s32 didAnimChangeInCs;
} DmGm; // size = 0x2D8

#endif // Z_DM_GM_H
