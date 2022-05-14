#ifndef Z_BG_IKANA_BLOCK_H
#define Z_BG_IKANA_BLOCK_H

#include "global.h"

struct BgIkanaBlock;

typedef void (*BgIkanaBlockActionFunc)(struct BgIkanaBlock*, GlobalContext*);

typedef struct BgIkanaBlock {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ AnimatedMaterial* unk_15C;
    /* 0x0160 */ BgIkanaBlockActionFunc actionFunc;
    /* 0x0164 */ f32* unk_164;
    /* 0x0168 */ f32 unk_168;
    /* 0x016C */ f32 unk_16C;
    /* 0x0170 */ f32 unk_170;
    /* 0x0174 */ Vec3s unk_174;
    /* 0x017A */ u8 unk_17A;
    /* 0x017B */ s8 unk_17B;
    /* 0x017C */ u8 unk_17C;
    /* 0x017D */ s8 unk_17D;
    /* 0x017E */ s8 unk_17E;
    /* 0x017F */ s8 unk_17F;
} BgIkanaBlock; // size = 0x180

extern const ActorInit Bg_Ikana_Block_InitVars;

#endif // Z_BG_IKANA_BLOCK_H
