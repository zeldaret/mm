#ifndef Z_DM_CHAR04_H
#define Z_DM_CHAR04_H

#include "global.h"

struct DmChar04;

typedef void (*DmChar04ActionFunc)(struct DmChar04*, PlayState*);

typedef struct unkStruct {
    f32 unk_240;
    f32 unk_244;
    f32 unk_248;
    f32 unk_24C;
} unkStruct;

typedef struct DmChar04 {
    /* 0x0000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable;
    /* 0x18E */ char pad18E[0x54];
    /* 0x1E2 */ Vec3s morphTable;
    /* 0x1E8 */ char pad1E8[0x54];
    /* 0x023C */ DmChar04ActionFunc actionFunc;
    /* 0x240 */ unkStruct str; // 240, 244, 248, 24C
    /* 0x250 */ unkStruct str2; // 250, 254, 258, 25C
    /* 0x260 */ u8 unk260;
    /* 0x261 */ u8 unk261;
    /* 0x262 */ u16 unk262;
} DmChar04; // size = 0x264

extern const ActorInit Dm_Char04_InitVars;

#endif // Z_DM_CHAR04_H
