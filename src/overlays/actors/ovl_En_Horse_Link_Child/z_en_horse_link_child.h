#ifndef Z_EN_HORSE_LINK_CHILD_H
#define Z_EN_HORSE_LINK_CHILD_H

#include "global.h"
#include "z64skin.h"

struct EnHorseLinkChild;

typedef void (*EnHorseLinkChildUnkFunc)(struct EnHorseLinkChild*, PlayState*);

typedef struct EnHorseLinkChild {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 action; // index to action func list
    /* 0x148 */ s32 animIndex;
    /* 0x14C */ Skin skin;
    /* 0x1DC */ s32 unk_1DC;
    /* 0x1DC */ s32 unk_1E0; // true false
    /* 0x1E4 */ u8 eyeTexIndex;
    /* 0x1E8 */ s32 gallopTimer;
    /* 0x1EC */ ColliderCylinder colldierCylinder;
    /* 0x238 */ ColliderJntSph colliderJntSph;
    /* 0x258 */ ColliderJntSphElement colliderJntSphElements[1];
    /* 0x298 */ UNK_TYPE1 unk298[4];
} EnHorseLinkChild; // size = 0x29C

#endif // Z_EN_HORSE_LINK_CHILD_H
