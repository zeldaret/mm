#ifndef Z_EN_PO_FUSEN_H
#define Z_EN_PO_FUSEN_H

#include <global.h>

struct EnPoFusen;

typedef void (*EnPoFusenActionFunc)(struct EnPoFusen*, GlobalContext*);

typedef struct EnPoFusen {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime anime;
    /* 0x188 */ EnPoFusenActionFunc actionFunc;
    /* 0x18C */ ColliderSphere collider;
    /* 0x1E4 */ Vec3s limbDrawTbl[0xA];
    /* 0x220 */ Vec3s transitionDrawTbl[0xA];
    /* 0x25C */ s16 randScaleChange;
    /* 0x25E */ s16 randXZRotChange;
    /* 0x260 */ s16 randYRotChange;
    /* 0x262 */ s16 avgBaseRotation;
    /* 0x264 */ s16 limb3Rot;
    /* 0x266 */ s16 limb46Rot;
    /* 0x268 */ s16 limb57Rot;
    /* 0x26A */ s16 limb8Rot;
    /* 0x26C */ s16 limb9Rot;
    /* 0x26E */ s16 randBaseRotChange;
    /* 0x270 */ s16 fuse;
} EnPoFusen; // size = 0x274

extern const ActorInit En_Po_Fusen_InitVars;

#endif // Z_EN_PO_FUSEN_H
