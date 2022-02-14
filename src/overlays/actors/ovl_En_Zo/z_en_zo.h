#ifndef Z_EN_ZO_H
#define Z_EN_ZO_H

#include "global.h"

struct EnZo;

typedef void (*EnZoActionFunc)(struct EnZo*, GlobalContext*);

#define ENZO_GET_PATH(thisx) (((thisx)->params & 0x7E00) >> 9)
#define ENZO_NO_PATH 0x3F

typedef struct EnZo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnZoActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x0194 */ ColliderCylinder collider;
    /* 0x01D8 */ UNK_TYPE1 unk_1D8[0x4];
    /* 0x01DC */ Path* path;
    /* 0x01E0 */ s16 waypoint;
    /* 0x01E4 */ Vec3f leftFootPos;
    /* 0x01F0 */ Vec3f rightFootPos;
    /* 0x01FC */ u8 isLeftFootGrounded;
    /* 0x01FD */ u8 isRightFootGrounded;
    /* 0x01FE */ Vec3s jointTable[20];
    /* 0x0276 */ Vec3s morphTable[20];
    /* 0x02EE */ Vec3s headRotTarget;
    /* 0x02F4 */ Vec3s headRot;
    /* 0x02FA */ Vec3s upperBodyRot;
    /* 0x0300 */ UNK_TYPE1 unk_300[0x12];
    /* 0x0312 */ s16 limbRotY[20];
    /* 0x033A */ s16 limbRotZ[20];
    /* 0x0364 */ Vec3f unk_364[15];
    /* 0x041A */ UNK_TYPE1 unk_41A[0x6];
    /* 0x041E */ s16 eyeIndex;
    /* 0x0420 */ s16 blinkTimer;
} EnZo; // size = 0x424

#endif // Z_EN_ZO_H
