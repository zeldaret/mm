#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"

struct EnTg;

typedef void (*EnTgActionFunc)(struct EnTg*, GlobalContext*);

typedef struct EnTgIdk {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ char unk2[0x2];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ char unk8[0xC];
    /* 0x14 */ Vec3f unk14;
    /* 0x20 */ char unk20[0x10];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s16 unk38;
} EnTgIdk; // size = 0x48

typedef struct EnTg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTgActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ char unk1D8[0x18]; // 24 bytes
    /* 0x01F0 */ Vec3s jointTable[21];
    /* 0x026E */ Vec3s morphTable[21];
    /* 0x02EC */ s16 unk2EC;
    /* 0x02F0 */ EnTgIdk unk2F0;
    /* 0x0338 */char unk338[0x258];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
