#ifndef Z_EN_JC_MATO_H
#define Z_EN_JC_MATO_H

#include <global.h>

struct EnJcMato;

typedef void (*EnJcMatoActionFunc)(struct EnJcMato*, GlobalContext*);

typedef struct EnJcMato {
    /* 0x000 */ Actor actor;
    // /* 0x144 */ char unk_144[0x6C];
    /* 0x144 */ EnJcMatoActionFunc actionFunc;
    /* 0x148 */ ColliderSphere collider; // size: 0x58
    /* 0x1A0 */ s16 unk1A0;
    /* 0x1A2 */ s16 unk1A2;
    /* 0x1A4 */ Vec3f unk1A4; // TargetPos Vector?
} EnJcMato; // size = 0x1B0

extern const ActorInit En_Jc_Mato_InitVars;

#endif // Z_EN_JC_MATO_H
