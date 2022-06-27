#ifndef Z_EN_ZORAEGG_H
#define Z_EN_ZORAEGG_H

#include "global.h"

struct EnZoraegg;

typedef void (*EnZoraeggActionFunc)(struct EnZoraegg*, PlayState*);

#define ENZORAEGG_GET_1F(thisx) ((thisx)->params & 0x1F)
#define ENZORAEGG_GET_FE00(thisx) (((thisx)->params & 0xFE00) >> 9)

enum {
    /* 00 */ ENZORAEGG_1F_0,
    /* 01 */ ENZORAEGG_1F_1,
    /* 02 */ ENZORAEGG_1F_2,
    /* 03 */ ENZORAEGG_1F_3,
    /* 04 */ ENZORAEGG_1F_4,
    /* 05 */ ENZORAEGG_1F_5,
    /* 06 */ ENZORAEGG_1F_6,
    /* 07 */ ENZORAEGG_1F_7,
    /* 08 */ ENZORAEGG_1F_8,
    /* 09 */ ENZORAEGG_1F_9,
    /* 10 */ ENZORAEGG_1F_10,
    /* 11 */ ENZORAEGG_1F_11,
    /* 12 */ ENZORAEGG_1F_12,
    /* 13 */ ENZORAEGG_1F_13,
    /* 14 */ ENZORAEGG_1F_14,
    /* 15 */ ENZORAEGG_1F_15,
    /* 16 */ ENZORAEGG_1F_16,
    /* 17 */ ENZORAEGG_1F_17,
    /* 18 */ ENZORAEGG_1F_18,
    /* 19 */ ENZORAEGG_1F_19,
    /* 20 */ ENZORAEGG_1F_20,
    /* 21 */ ENZORAEGG_1F_21,
    /* 22 */ ENZORAEGG_1F_22,
    /* 23 */ ENZORAEGG_1F_23,
    /* 24 */ ENZORAEGG_1F_24,
    /* 25 */ ENZORAEGG_1F_25,
};

typedef struct EnZoraegg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[7];
    /* 0x1B2 */ Vec3s morphTable[7];
    /* 0x1DC */ Actor* unk_1DC;
    /* 0x1E0 */ f32 unk_1E0;
    /* 0x1E4 */ f32 unk_1E4;
    /* 0x1E8 */ s16 unk_1E8;
    /* 0x1EA */ u16 unk_1EA;
    /* 0x1EC */ u8 unk_1EC;
    /* 0x1ED */ u8 unk_1ED;
    /* 0x1EE */ u8 unk_1EE;
    /* 0x1EF */ u8 unk_1EF;
    /* 0x1F0 */ u16 actorActionCmd;
    /* 0x1F2 */ s16 unk_1F2;
    /* 0x1F4 */ s16 unk_1F4;
    /* 0x1F8 */ EnZoraeggActionFunc actionFunc;
} EnZoraegg; // size = 0x1FC

extern const ActorInit En_Zoraegg_InitVars;

#endif // Z_EN_ZORAEGG_H
