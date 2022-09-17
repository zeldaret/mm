#ifndef Z_EN_DEKUBABA_H
#define Z_EN_DEKUBABA_H

#include "global.h"

struct EnDekubaba;

typedef void (*EnDekubabaActionFunc)(struct EnDekubaba*, PlayState*);

typedef struct EnDekubaba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnDekubabaActionFunc actionFunc;
    /* 0x18C */ u8 drawDmgEffType;
    /* 0x18E */ s16 timer;
    /* 0x190 */ s16 targetSwayAngle;
    /* 0x192 */ s16 stemSectionAngle[3];
    /* 0x198 */ Vec3s jointTable[8];
    /* 0x1C8 */ Vec3s morphTable[8];
    /* 0x1F8 */ f32 size;
    /* 0x1FC */ f32 drawDmgEffAlpha;
    /* 0x200 */ f32 drawDmgEffScale;
    /* 0x204 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x208 */ Vec3f bodyPartsPos[4];
    /* 0x238 */ CollisionPoly* boundFloor;
    /* 0x23C */ ColliderJntSph collider;
    /* 0x25C */ ColliderJntSphElement colliderElements[7];
} EnDekubaba; // size = 0x41C

extern const ActorInit En_Dekubaba_InitVars;

#endif // Z_EN_DEKUBABA_H
