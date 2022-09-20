#ifndef Z_EN_ZOD_H
#define Z_EN_ZOD_H

#include "global.h"

struct EnZod;

typedef void (*EnZodActionFunc)(struct EnZod*, PlayState*);

typedef struct EnZod {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Vec3s morphTable;          /* inferred */
    /* 0x14A */ char pad14A[0x36];         /* maybe part of unk144[0xA]? */
    /* 0x180 */ Vec3s JointTable;          /* inferred */
    /* 0x186 */ char pad186[0x36];         /* maybe part of unk180[0xA]? */
    /* 0x1BC */ SkelAnime skelAnime;       /* inferred */
    /* 0x200 */ ColliderCylinder collider; /* inferred */
    /* 0x24C */ char pad24C[0xA];
    /* 0x256 */ u16 unk256;
    /* 0x258 */ s16 unk258;
    /* 0x25A */ s16 unk25A;
    /* 0x25C */ s16 unk25C;
    /* 0x25E */ s16 unk25E;
    /* 0x260 */ s16 unk260;
    /* 0x262 */ s16 unk262;
    /* 0x264 */ s16 unk264;
    /* 0x266 */ s16 unk266;
    /* 0x268 */ f32 unk268;
    /* 0x26C */ f32 unk26C;
    /* 0x270 */ f32 unk270;
    /* 0x274 */ f32 unk274;
    /* 0x278 */ char pad278[0x2];
    /* 0x280 */ f32 unk280;
    /* 0x284 */ f32 unk284;
    /* 0x288 */ f32 unk288;
    /* 0x28C */ f32 unk28C;
    char pad[0x2];

    /* 0x298 */ s16 unk298;
    /* 0x29A */ s16 unk29A; /* inferred */
    /* 0x29C */ EnZodActionFunc actionFunc;
} EnZod; // size = 0x2A0

extern const ActorInit En_Zod_InitVars;

#endif // Z_EN_ZOD_H
