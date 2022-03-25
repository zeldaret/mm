#ifndef Z_EN_FAMOS_H
#define Z_EN_FAMOS_H

#include "global.h"
#include "objects/object_famos/object_famos.h"

struct EnFamos;

typedef void (*EnFamosActionFunc)(struct EnFamos*, GlobalContext*);

typedef struct EnFamosRock {
    /* 00 */ Vec3f pos;
    /* 0C */ Vec3f velocity;
    /* 18 */ Vec3s rotation;
    /* 20 */ f32   scale;
} EnFamosRock; // size = 0x24

#define GET_FAMOS_PATH(thisx) (thisx->params)

// delayTimer gets reused:
//   after spotting player, counts frames until first attack (8)
//   after lost agro, measures frames looking around before returning to home (60)
//   before smash attack, counts frames before disabling emblem colider (4)
//   after smash attack collision, counts frames before rising (3)
//   after smash attack finish, counts frames rising above ground before next attempt (20)

typedef struct EnFamos {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[FAMOS_LIMB_MAX];
    /* 0x1AC */ Vec3s morphTable[FAMOS_LIMB_MAX];
    /* 0x1D0 */ EnFamosActionFunc actionFunc;
    /* 0x1D4 */ u8 animatedMaterialIndex;
    /* 0x1D5 */ u8 stableRotation;
    /* 0x1D6 */ u8 pathNodeCount;
    /* 0x1D7 */ u8 currentPathNode;
    /* 0x1D8 */ u8 unk1D8;
    /* 0x1D9 */ u8 unk1D9;
    /* 0x1DA */ s16 hoverClk; // 30->0, repeat, for height adjustment
    /* 0x1DC */ s16 delayTimer; // reused for different functions
    /* 0x1DE */ s16 unkTimer1DE;
    /* 0x1E0 */ s16 flippedTimer; // frames until it flips right side up
    /* 0x1E2 */ s16 unkTimer1E2;
    /* 0x1E4 */ s16 unk1E4;
    /* 0x1E6 */ s16 unk1E6;
    /* 0x1E8 */ Vec3s* pathPoints;
    /* 0x1EC */ f32 unk1EC; // height?
    /* 0x1F0 */ f32 unk1F0;
    /* 0x1F4 */ Vec3f targetDest;
    /* 0x200 */ Vec3f unk200; // current pos? why not use actor.pos
    // havent figured out what the difference between the colliders are, only one cylinder is visible in KZ
    /* 0x20C */ ColliderCylinder collider1;
    /* 0x258 */ ColliderCylinder collider2;
    /* 0x2A4 */ ColliderJntSph   emblemCollider;
    /* 0x2C4 */ ColliderJntSphElement emblemColliderElements;
    /* 0x340 */ u8 unk340[0x40];
    /* 0x344 */ EnFamosRock rocks[20];
} EnFamos; // size = 0x614

#endif // Z_EN_FAMOS_H
