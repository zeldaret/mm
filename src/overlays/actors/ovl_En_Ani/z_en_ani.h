#ifndef Z_EN_ANI_H
#define Z_EN_ANI_H

#include "global.h"

struct EnAni;

typedef void (*EnAniActionFunc)(struct EnAni*, GlobalContext*);
typedef void (*EnAniOtherFunc)(struct EnAni*);

typedef struct EnAni {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider1;
    /* 0x190 */ ColliderCylinder collider2;
    /* 0x1DC */ SkelAnime skelAnime;
    /* 0x220 */ Vec3s unk220;                       /* inferred */
    /* 0x226 */ char pad226[0x5A];                  /* maybe part of unk220[0x10]? */
    /* 0x280 */ Vec3s unk280;                       /* inferred */
    /* 0x286 */ char pad286[0x5A];                  /* maybe part of unk280[0x10]? */
    /* 0x2E0 */ Vec3s unk2E0;                       /* inferred */
    /* 0x2E6 */ Vec3s unk2E6;                       /* inferred */
    /* 0x2EC */ u16 unk2EC;                         /* inferred */
    /* 0x2EE */ s16 unk2EE;                         /* inferred */
    /* 0x2F0 */ s16 unk2F0;                         /* inferred */
    /* 0x2F2 */ char pad2F2[2];
    /* 0x2F4 */ EnAniOtherFunc otherFunc;
    /* 0x2F8 */ s16 blinkState;
    /* 0x2FA */ s16 unkTimer2FA;
    /* 0x2FC */ EnAniActionFunc actionFunc;
} EnAni; // size = 0x300

#endif // Z_EN_ANI_H
