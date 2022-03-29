#ifndef Z_EN_HS_H
#define Z_EN_HS_H

#include "global.h"
#include "objects/object_hs/object_hs.h"

struct EnHs;

typedef void (*EnHsActionFunc)(struct EnHs*, GlobalContext*);

#define ENHS_GET_F(thisx) ((thisx)->params & 0xF)

#define ENHS_1 1

typedef struct EnHs {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ Vec3s jointTable[OBJECT_HS_LIMB_MAX];
    /* 0x0234 */ Vec3s morphTable[OBJECT_HS_LIMB_MAX];
    /* 0x0294 */ Vec3s unk_294;
    /* 0x029A */ Vec3s unk_29A;
    /* 0x02A0 */ u16 unk_2A0;
    /* 0x02A2 */ s16 unk_2A2;
    /* 0x02A4 */ Vec3f unk_2A4[20];
    /* 0x0394 */ EnHsActionFunc actionFunc;
} EnHs; // size = 0x398

extern const ActorInit En_Hs_InitVars;

#endif // Z_EN_HS_H
