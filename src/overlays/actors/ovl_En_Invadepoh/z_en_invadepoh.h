#ifndef Z_EN_INVADEPOH_H
#define Z_EN_INVADEPOH_H

#include <global.h>

struct EnInvadepoh;

typedef void (*EnInvadepohActionFunc)(struct EnInvadepoh* this, PlayState* play);
typedef void (*EnInvadepohInitFunc)(struct EnInvadepoh* this, PlayState* play);
typedef void (*EnInvadepohDestFunc)(struct EnInvadepoh* this, PlayState* play);

typedef struct EnInvadepoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x15C];
    /* 0x2A0 */ ColliderCylinder unk_2A0;
    /* 0x2EC */ EnInvadepohActionFunc unk_2EC;
    /* 0x2F0 */ char unk_2F0[0xD0];
} EnInvadepoh; // size = 0x3C0

extern const ActorInit En_Invadepoh_InitVars;

#endif // Z_EN_INVADEPOH_H
