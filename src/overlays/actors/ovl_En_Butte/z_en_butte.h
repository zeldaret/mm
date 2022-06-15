#ifndef Z_EN_BUTTE_H
#define Z_EN_BUTTE_H

#include "global.h"

struct EnButte;

typedef void (*EnButteActionFunc)(struct EnButte*, GlobalContext*);

#define ENBUTTE_GET(thisx) ((thisx)->params)
#define ENBUTTE_GET_1(thisx) ((thisx)->params & 1)

#define ENBUTTE_MINUS1 -1
#define ENBUTTE_0 0
#define ENBUTTE_1 1

typedef struct EnButte {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colldierElements[1];
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x01E8 */ Vec3s jointTable[8];
    /* 0x0218 */ Vec3s morphTable[8];
    /* 0x0248 */ EnButteActionFunc actionFunc;
    /* 0x024C */ s16 unk_24C;
    /* 0x024E */ u8 unk_24E;
    /* 0x024F */ u8 unk_24F;
    /* 0x0250 */ u8 unk_250;
    /* 0x0252 */ s16 unk_252;
    /* 0x0254 */ s16 unk_254;
    /* 0x0256 */ s16 unk_256;
    /* 0x0258 */ s16 unk_258;
    /* 0x025C */ f32 unk_25C;
} EnButte; // size = 0x260

extern const ActorInit En_Butte_InitVars;

#endif // Z_EN_BUTTE_H
