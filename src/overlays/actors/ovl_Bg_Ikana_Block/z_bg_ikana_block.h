#ifndef Z_BG_IKANA_BLOCK_H
#define Z_BG_IKANA_BLOCK_H

#include "global.h"

struct BgIkanaBlock;

typedef void (*BgIkanaBlockActionFunc)(struct BgIkanaBlock*, GlobalContext*);

typedef struct BgIkanaBlock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ BgIkanaBlockActionFunc actionFunc;
    /* 0x0164 */ char unk_164[0xC];
    /* 0x0170 */ f32 unk_170;
    /* 0x0174 */ char unk_174[0x8];
    /* 0x017C */ u8 unk_17C;
    /* 0x017D */ char unk_17D[0x1];
    /* 0x017E */ u8 unk_17E;
} BgIkanaBlock; // size = 0x180

extern const ActorInit Bg_Ikana_Block_InitVars;

#endif // Z_BG_IKANA_BLOCK_H
