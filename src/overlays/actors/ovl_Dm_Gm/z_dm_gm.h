#ifndef Z_DM_GM_H
#define Z_DM_GM_H

#include "global.h"
#include "objects/object_an1/object_an1.h"

struct DmGm;

typedef void (*DmGmActionFunc)(struct DmGm*, GlobalContext*);

typedef struct DmGm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ DmGmActionFunc actionFunc;
    /* 0x018C */ Vec3f unk_18C;
    /* 0x018C */ Vec3f unk_194;
    /* 0x01A4 */ Vec3s unk_1A4;
    /* 0x01A4 */ Vec3s unk_1AA;
    /* 0x01B0 */ Vec3s jointTable[OBJECT_AN1_LIMB_MAX];
    /* 0x022E */ Vec3s morphTable[OBJECT_AN1_LIMB_MAX];
    /* 0x02AC */ s8 unk_2AC;
    /* 0x02AD */ s8 unk_2AD;
    /* 0x02AE */ u16 unk_2AE;
    /* 0x02B0 */ u8 unk_2B0;
    /* 0x02B4 */ Actor* unk_2B4;
    /* 0x02B8 */ s16 unk_2B8;
    /* 0x02BA */ s16 unk_2BA;
    /* 0x02BC */ s16 unk_2BC;
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ s16 unk_2C0;
    /* 0x02C2 */ s16 unk_2C2;
    /* 0x02C4 */ s16 unk_2C4;
    /* 0x02C8 */ s32 unk_2C8;
    /* 0x02CC */ s32 unk_2CC;
    /* 0x02D0 */ s32 unk_2D0;
    /* 0x02D4 */ s32 unk_2D4;
} DmGm; // size = 0x2D8

extern const ActorInit Dm_Gm_InitVars;

#endif // Z_DM_GM_H
