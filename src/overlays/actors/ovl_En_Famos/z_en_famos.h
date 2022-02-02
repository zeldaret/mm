#ifndef Z_EN_FAMOS_H
#define Z_EN_FAMOS_H

#include "global.h"

struct EnFamos;

typedef void (*EnFamosActionFunc)(struct EnFamos*, GlobalContext*);

typedef struct EnFamosParticle {
    /* 00 */ Vec3f pos;
    /* 0C */ Vec3f velocity;
    /* 18 */ Vec3s rotation;
    /* 20 */ f32   scale;
} EnFamosParticle; // size = 0x24

#define FAMOS_LIMB_COUNT 0x6

typedef struct EnFamos {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[FAMOS_LIMB_COUNT];
    /* 0x1AC */ Vec3s morphTable[FAMOS_LIMB_COUNT];
    /* 0x1D0 */ EnFamosActionFunc actionFunc;
    /* 0x1D4 */ u8 animatedMaterialIndex;
    /* 0x1D5 */ u8 stableRotation; // starts 1, set to zero when flipped, then updated by rotation to 1 if upright or regular, zero is transitioning?
    /* 0x1D6 */ u8 pathNodeCount;
    /* 0x1D7 */ u8 currentPathNode;
    /* 0x1D8 */ u8 unk1D8;
    /* 0x1D9 */ u8 unk1D9;
    /* 0x1DA */ s16 hoverClk; // 30->0, repeat, for height adjustment
    /* 0x1DC */ s16 unk1DC;
    /* 0x1DE */ s16 unk1DE;
    /* 0x1E0 */ s16 flippedTimer;
    /* 0x1E2 */ s16 unk1E2;
    /* 0x1E4 */ s16 unk1E4;
    /* 0x1E6 */ s16 unk1E6;
    /* 0x1E8 */ Vec3s* pathPoints;
    /* 0x1EC */ f32 unk1EC; // height?
    /* 0x1F0 */ f32 unk1F0;
    /* 0x1F4 */ Vec3f targetDest;
    /* 0x200 */ Vec3f unk200; // current pos? why not use actor.pos
    /* 0x20C */ ColliderCylinder collider1;
    /* 0x258 */ ColliderCylinder collider2;
    /* 0x2A4 */ ColliderJntSph   emblemCollider;
    /* 0x2C4 */ ColliderJntSphElement collider3Elements;
    /* 0x340 */ char unk340[0x40];
    /* 0x344 */ EnFamosParticle particles[0x14];
} EnFamos; // size = 0x614

#endif // Z_EN_FAMOS_H
