#ifndef Z_BG_DBLUE_BALANCE_H
#define Z_BG_DBLUE_BALANCE_H

#include "global.h"

struct BgDblueBalance;

typedef void (*BgDblueBalanceActionFunc)(struct BgDblueBalance*, GlobalContext*);

#define BGDBLUEBALANCE_GET_7F(thisx) ((thisx)->params & 0x7F)
#define BGDBLUEBALANCE_GET_300(thisx) (((thisx)->params >> 8) & 3)

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 unk_0E;
    /* 0x10 */ f32 unk_10;
} BgDblueBalanceStruct; // size = 0x14

typedef struct BgDblueBalance {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ struct BgDblueBalance* unk_15C;
    /* 0x0160 */ struct BgDblueBalance* unk_160;
    /* 0x0164 */ struct BgDblueBalance* unk_164;
    /* 0x0168 */ BgDblueBalanceActionFunc actionFunc;
    /* 0x016C */ s32 unk_16C;
    /* 0x0170 */ s32 unk_170;
    /* 0x0174 */ s16 unk_174;
    /* 0x0176 */ s16 unk_176;
    /* 0x0178 */ s16 unk_178;
    /* 0x017A */ s16 unk_17A;
    /* 0x017C */ s8 unk_17C;
    /* 0x017D */ s8 unk_17D;
    /* 0x017E */ s8 unk_17E;
    /* 0x017F */ s8 unk_17F;
    /* 0x0180 */ s8 unk_180;
    /* 0x0181 */ s8 unk_181;
    /* 0x0182 */ s8 unk_182;
    /* 0x0183 */ u8 unk_183;
    /* 0x0184 */ s16 unk_184;
    /* 0x0186 */ s8 unk_186;
    /* 0x0187 */ s8 unk_187;
    /* 0x0188 */ BgDblueBalanceStruct unk_188[8];
    /* 0x0228 */ f32 unk_228;
} BgDblueBalance; // size = 0x22C

extern const ActorInit Bg_Dblue_Balance_InitVars;

#endif // Z_BG_DBLUE_BALANCE_H
