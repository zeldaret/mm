#ifndef Z_DM_CHAR09_H
#define Z_DM_CHAR09_H

#include "global.h"

typedef struct unkStruct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} unkStruct;

struct DmChar09;

typedef void (*DmChar09ActionFunc)(struct DmChar09*, PlayState*);

typedef struct DmChar09 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s unk188;
    /* 0x18E */ char pad18E[0x36];
    /* 0x1C4 */ Vec3s unk1C4;
    /* 0x1CA */ char pad1CA[0x36];
    /* 0x200 */ DmChar09ActionFunc actionFunc;
    /* 0x204 */ f32 unk204;
    /* 0x208 */ f32 unk208;
    /* 0x20C */ f32 unk20C;
    /* 0x210 */ f32 unk210;
    /* 0x214 */ s32 unk214;
    /* 0x218 */ s32 unk218;
    /* 0x21C */ s32 unk21C;
    /* 0x220 */ s32 unk220;
    /* 0x224 */ unkStruct* unk224;
    /* 0x228 */ s16 unk228;
    /* 0x22A */ s16 unk22A;
    /* 0x22C */ char pad22C[2];
    /* 0x22E */ u8 unk22E;
    /* 0x22F */ u8 unk22F;
} DmChar09; // size = 0x230

extern const ActorInit Dm_Char09_InitVars;

#endif // Z_DM_CHAR09_H
