#ifndef Z_EN_BOOM_H
#define Z_EN_BOOM_H

#include "global.h"

struct EnBoom;

typedef void (*EnBoomActionFunc)(struct EnBoom*, GlobalContext*);

typedef struct EnBoom {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderQuad collider;
    /* 0x01C4 */ Actor* player;
    /* 0x01C8 */ Actor* unk_1C8;
    /* 0x01CC */ u8 unk_1CC;
    /* 0x01CD */ u8 unk_1CD;
    /* 0x01CE */ u8 unk_1CE;
    /* 0x01CF */ s8 unk_1CF;
    /* 0x01D0 */ s32 effectIndex;
    /* 0x01D4 */ WeaponInfo weaponInfo;
    /* 0x01F0 */ EnBoomActionFunc actionFunc;
} EnBoom; // size = 0x1F4

extern const ActorInit En_Boom_InitVars;

#endif // Z_EN_BOOM_H
