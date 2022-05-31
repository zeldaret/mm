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
    /* 0x188 */ char pad188[0xD8]; // unused by DmZl
    /* 0x0260 */ DmZlActionFunc actionFunc;
    /* 0x264 */ char pad264[0x4C]; // unused by DmZl
    /* 0x2B0 */ s16 animationIndex;
    /* 0x2B2 */ u8 unk2B2; // eye tex id
    /* 0x2B3 */ u8 unk2B3; // exe tex id
    /* 0x2B4 */ u8 mouthTextureIndex;
    /* 0x2B5 */ u8 unk2B5; // used to control eye state, but not set by our actor, outside of actor?
    /* 0x2B6 */ u8 unk2B6; // used to control mouth state, but not set by our actor, outside of actor?
    /* 0x2B8 */ s16 timer;
    /* 0x2BA */ s16 unused2BA; // init to 0
    /* 0x2BC */ char pad2BC[0x18]; // unused by DmZl

} DmZl; // size = 0x2D4

extern const ActorInit Dm_Zl_InitVars;

#endif // Z_DM_ZL_H
