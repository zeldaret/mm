#ifndef Z_EN_OSK_H
#define Z_EN_OSK_H

#include "global.h"

struct EnOsk;

typedef void (*EnOskActionFunc)(struct EnOsk*, GlobalContext*);

#define ENOSK_GET_F(thisx) ((thisx)->params & 0xF)

#define ENOSK_1 1
#define ENOSK_2 2

typedef struct EnOsk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[17];
    /* 0x01EE */ Vec3s morphTable[17];
    /* 0x0254 */ s16 unk_254;
    /* 0x0256 */ s16 unk_256;
    /* 0x0258 */ u16 unk_258;
    /* 0x025C */ f32 unk_25C;
    /* 0x0260 */ EnOskActionFunc actionFunc;
} EnOsk; // size = 0x264

extern const ActorInit En_Osk_InitVars;

#endif // Z_EN_OSK_H
