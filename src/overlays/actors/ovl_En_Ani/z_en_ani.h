#ifndef Z_EN_ANI_H
#define Z_EN_ANI_H

#include "global.h"

struct EnAni;

typedef void (*EnAniActionFunc)(struct EnAni*, GlobalContext*);
typedef void (*EnAniBlinkFunc)(struct EnAni*);

#define ANI_LIMB_COUNT 16

typedef struct EnAni {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider1;
    /* 0x190 */ ColliderCylinder collider2;
    /* 0x1DC */ SkelAnime skelAnime;
    /* 0x220 */ Vec3s jointTable[ANI_LIMB_COUNT];
    /* 0x280 */ Vec3s morphTable[ANI_LIMB_COUNT];
    /* 0x2E0 */ Vec3s headRot;
    /* 0x2E6 */ Vec3s unk2E6;
    /* 0x2EC */ u16 stateFlags;
    /* 0x2EE */ s16 unusedShort;
    /* 0x2F0 */ s16 treeReachTimer;
    /* 0x2F4 */ EnAniBlinkFunc blinkFunc;
    /* 0x2F8 */ s16 blinkState;
    /* 0x2FA */ s16 blinkTimer;
    /* 0x2FC */ EnAniActionFunc actionFunc;
} EnAni; // size = 0x300

enum EnAniType {
  /* 0 */ ANI_TYPE_UNUSED_STANDING, // other, not really zero
  /* 1 */ ANI_TYPE_TREE_HANGING,
};

enum EnAniStateFlags {
  /* 0 */ ANI_STATE_STANDING  = 0,
  /* 1 */ ANI_STATE_UNUSED    = 1, // checked for but never set
  /* 2 */ ANI_STATE_SUFFERING = 2,
  /* 4 */ ANI_STATE_CLIMBING  = 4,
  /* 8 */ ANI_STATE_FALLING   = 8,
};

#define GET_ANI_TYPE(thisx) (thisx->params & 0xFF) 

#endif // Z_EN_ANI_H
