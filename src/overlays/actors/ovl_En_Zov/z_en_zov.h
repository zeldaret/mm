#ifndef Z_EN_ZOV_H
#define Z_EN_ZOV_H

#include "global.h"

struct EnZov;

typedef void (*EnZovActionFunc)(struct EnZov*, GlobalContext*);
typedef s32 (*EnZovUnkFunc)(GlobalContext*, struct EnZov*);

#define ENZOV_GET_F(thisx) ((thisx)->params & 0xF)
#define ENZOV_GET_FE00(thisx) (((thisx)->params & 0xFE00) >> 9)

#define ENZOV_F_1 1
#define ENZOV_F_2 2

typedef struct EnZov {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnZovUnkFunc unk_144;
    /* 0x0148 */ Vec3s jontTable[23];
    /* 0x01D2 */ Vec3s morphTable[23];
    /* 0x025C */ SkelAnime skelAnime;
    /* 0x02A0 */ ColliderCylinder collider;
    /* 0x02EC */ s16 unk_2EC;
    /* 0x02EE */ s16 unk_2EE;
    /* 0x02F0 */ Vec3s unk_2F0;
    /* 0x02F6 */ Vec3s unk_2F6;
    /* 0x02FC */ Vec3f unk_2FC;
    /* 0x0308 */ Vec3f unk_308;
    /* 0x0314 */ Vec3f unk_314;
    /* 0x0320 */ u16 unk_320;
    /* 0x0322 */ s16 unk_322;
    /* 0x0324 */ s16 unk_324;
    /* 0x0326 */ s16 unk_326;
    /* 0x0328 */ s16 unk_328[2];
    /* 0x032C */ s16 unk_32C;
    /* 0x0330 */ EnZovActionFunc actionFunc;
} EnZov; // size = 0x334

extern const ActorInit En_Zov_InitVars;

#endif // Z_EN_ZOV_H
