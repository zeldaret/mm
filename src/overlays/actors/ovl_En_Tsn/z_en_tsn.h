#ifndef Z_EN_TSN_H
#define Z_EN_TSN_H

#include "global.h"

struct EnTsn;

typedef void (*EnTsnActionFunc)(struct EnTsn*, PlayState*);

#define ENTSN_GET_OBJECT_TYPE(thisx) ((thisx)->params & 0xF)
#define ENTSN_IS_OBJECT(thisx) ((thisx)->params & 0x100)
#define ENTSN_GET_Z(thisx) ((thisx)->home.rot.z)
#define ENTSN_SET_Z(thisx, state) ((thisx)->home.rot.z = (state))

typedef struct EnTsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnTsnActionFunc actionFunc;
    /* 0x1D8 */ struct EnTsn* fisherman;
    /* 0x1DC */ UNK_TYPE1 pad_1DC[0x44];
    /* 0x220 */ u16 flags;
    /* 0x222 */ Vec3s headRot;
    /* 0x228 */ Vec3s torsoRot;
    /* 0x22E */ s16 eyeIndex;
    /* 0x230 */ s16 blinkTimer;
} EnTsn; // size = 0x234

#endif // Z_EN_TSN_H
