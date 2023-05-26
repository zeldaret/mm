#ifndef Z_EN_OSK_H
#define Z_EN_OSK_H

#include "global.h"

struct EnOsk;

typedef void (*EnOskActionFunc)(struct EnOsk*, PlayState*);

#define ENOSK_GET_F(thisx) ((thisx)->params & 0xF)

#define ENOSK_1 1
#define ENOSK_2 2

typedef struct EnOsk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[17];
    /* 0x1EE */ Vec3s morphTable[17];
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ s16 cueId;
    /* 0x258 */ u16 cueType;
    /* 0x25C */ f32 unk_25C;
    /* 0x260 */ EnOskActionFunc actionFunc;
} EnOsk; // size = 0x264

#endif // Z_EN_OSK_H
