#ifndef Z_EN_ZORAEGG_H
#define Z_EN_ZORAEGG_H

#include "global.h"

struct EnZoraegg;

typedef void (*EnZoraeggActionFunc)(struct EnZoraegg*, GlobalContext*);

#define ENZORAEGG_GET_1F(thisx) ((thisx)->params & 0x1F)
#define ENZORAEGG_GET_FE00(thisx) (((thisx)->params & 0xFE00) >> 9)

enum {
    /* 0 */ ENZORAEGG_1F_0,
    /* 1 */ ENZORAEGG_1F_1,
    /* 2 */ ENZORAEGG_1F_2,
    /* 3 */ ENZORAEGG_1F_3,
    /* 4 */ ENZORAEGG_1F_4,
    /* 5 */ ENZORAEGG_1F_5,
    /* 6 */ ENZORAEGG_1F_6,
    /* 7 */ ENZORAEGG_1F_7,
    /* 8 */ ENZORAEGG_1F_8,
    /* 9 */ ENZORAEGG_1F_9,
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
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[7];
    /* 0x01B2 */ Vec3s morphTable[7];
    /* 0x01DC */ Actor* unk_1DC;
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E4 */ f32 unk_1E4;
    /* 0x01E8 */ s16 unk_1E8;
    /* 0x01EA */ u16 unk_1EA;
    /* 0x01EC */ u8 unk_1EC;
    /* 0x01ED */ u8 unk_1ED;
    /* 0x01EE */ u8 unk_1EE;
    /* 0x01EF */ u8 unk_1EF;
    /* 0x01F0 */ u16 actorActionCmd;
    /* 0x01F2 */ s16 unk_1F2;
    /* 0x01F4 */ s16 unk_1F4;
    /* 0x01F8 */ EnZoraeggActionFunc actionFunc;
} EnZoraegg; // size = 0x1FC

extern const ActorInit En_Zoraegg_InitVars;

#endif // Z_EN_ZORAEGG_H
