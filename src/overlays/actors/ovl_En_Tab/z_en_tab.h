#ifndef Z_EN_TAB_H
#define Z_EN_TAB_H

#include "global.h"
#include "overlays/actors/ovl_En_Gm/z_en_gm.h"

struct EnTab;

typedef void (*EnTabActionFunc)(struct EnTab*, GlobalContext*);
typedef s32 (*EnTabUnkFunc)(struct EnTab*, GlobalContext*);

typedef struct EnTab {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnTabActionFunc actionFunc;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ u8 unk_1D8;
    /* 0x01DC */ s32 unk_1DC;
    /* 0x01E0 */ Actor* unk_1E0;
    /* 0x01E4 */ EnGm* unk_1E4;
    /* 0x01E8 */ Vec3f unk_1E8[2];
    /* 0x0200 */ Vec3s unk_200[2];
    /* 0x020C */ Vec3s jointTable[20];
    /* 0x0284 */ Vec3s morphTable[20];
    /* 0x02FC */ u16 unk_2FC;
    /* 0x0300 */ f32 unk_300;
    /* 0x0304 */ f32 unk_304;
    /* 0x0308 */ f32 unk_308;
    /* 0x030C */ s16 unk_30C;
    /* 0x030E */ UNK_TYPE1 unk30E[4];
    /* 0x0312 */ s16 unk_312;
    /* 0x0314 */ s16 unk_314;
    /* 0x0316 */ s16 unk_316;
    /* 0x0318 */ s16 unk_318;
    /* 0x031A */ s16 unk_31A;
    /* 0x031C */ s16 unk_31C;
    /* 0x031E */ s16 unk_31E;
    /* 0x0320 */ s16 unk_320;
    /* 0x0322 */ s16 unk_322;
    /* 0x0324 */ s16 unk_324;
    /* 0x0328 */ EnTabUnkFunc unk_328;
    /* 0x032C */ s32 unk_32C;
    /* 0x0330 */ UNK_TYPE1 unk330[4];
    /* 0x0334 */ s32 unk_334;
    /* 0x0338 */ s32 unk_338;
} EnTab; // size = 0x33C

extern const ActorInit En_Tab_InitVars;

#endif // Z_EN_TAB_H
