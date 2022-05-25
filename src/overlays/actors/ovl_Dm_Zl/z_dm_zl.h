#ifndef Z_DM_ZL_H
#define Z_DM_ZL_H

#include "global.h"

struct DmZl;

typedef void (*DmZlActionFunc)(struct DmZl*, GlobalContext*);

typedef struct {
    /* 0 */ u8 pad[0x18];
} DmZl_UnkStruct; // size = 0x18


typedef struct DmZl {
    /* 0x0000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ char pad188[0xD8];                  /* maybe part of unk144[4]? */
    /* 0x0260 */ DmZlActionFunc actionFunc;
    /* 0x264 */ char pad264[0x4C];                  /* maybe part of actionFunc[0x14]? */
    /* 0x2B0 */ s16 unk2B0;                         /* inferred */
    /* 0x2B2 */ u8 unk2B2;                          /* inferred */
    /* 0x2B3 */ u8 unk2B3;                          /* inferred */
    /* 0x2B4 */ u8 unk2B4;                          /* inferred */
    /* 0x2B5 */ u8 unk2B5;                          /* inferred */
    /* 0x2B6 */ u8 unk2B6;                          /* inferred */
    /* 0x2B7 */ char pad2B7[1];
    /* 0x2B8 */ s16 unk2B8;                         /* inferred */
    /* 0x2BA */ s16 unk2BA;                         /* inferred */
    /* 0x2BC */ char pad2BC[0x18];                  /* maybe part of unk2BA[0xD]? */

} DmZl; // size = 0x2D4

extern const ActorInit Dm_Zl_InitVars;

#endif // Z_DM_ZL_H
