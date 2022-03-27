#ifndef Z_EN_KBT_H
#define Z_EN_KBT_H

#include "global.h"
#include "objects/object_kbt/object_kbt.h"

struct EnKbt;

typedef void (*EnKbtActionFunc)(struct EnKbt*, GlobalContext*);

typedef struct EnKbt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[OBJECT_KBT_LIMB_MAX];
    /* 0x0200 */ Vec3s morphTable[OBJECT_KBT_LIMB_MAX];
    /* 0x0278 */ Actor* unk_278;
    /* 0x027C */ u16 unk_27C;
    /* 0x027E */ u8 unk_27E;
    /* 0x027F */ u8 unk_27F;
    /* 0x0280 */ s16 unk_280;
    /* 0x0282 */ s16 unk_282;
    /* 0x0284 */ s16 unk_284;
    /* 0x0288 */ EnKbtActionFunc actionFunc;
} EnKbt; // size = 0x28C

extern const ActorInit En_Kbt_InitVars;

#endif // Z_EN_KBT_H
