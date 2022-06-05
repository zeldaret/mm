#ifndef Z_EN_VM_H
#define Z_EN_VM_H

#include "global.h"

struct EnVm;

typedef void (*EnVmActionFunc)(struct EnVm*, GlobalContext*);

#define ENVM_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)

#define ENVM_FF00_0 0
#define ENVM_FF00_5 5
#define ENVM_FF00_FF 0xFF

typedef struct EnVm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[11];
    /* 0x01CA */ Vec3s morphTable[11];
    /* 0x020C */ EnVmActionFunc actionFunc;
    /* 0x0210 */ u8 unk_210;
    /* 0x0212 */ s16 unk_212;
    /* 0x0214 */ s16 unk_214;
    /* 0x0216 */ s16 unk_216;
    /* 0x0218 */ s16 unk_218;
    /* 0x021C */ f32 unk_21C;
    /* 0x0220 */ f32 unk_220;
    /* 0x0224 */ f32 unk_224;
    /* 0x0228 */ Vec3f unk_228;
    /* 0x0234 */ Vec3f unk_234;
    /* 0x0240 */ ColliderJntSph colliderJntSph;
    /* 0x0260 */ ColliderJntSphElement colliderJntSphElements[2];
    /* 0x02E0 */ ColliderTris colliderTris;
    /* 0x0300 */ ColliderTrisElement colliderTrisElements[1];
} EnVm; // size = 0x35C

extern const ActorInit En_Vm_InitVars;

#endif // Z_EN_VM_H
