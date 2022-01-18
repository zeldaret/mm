#ifndef Z_BG_DBLUE_MOVEBG_H
#define Z_BG_DBLUE_MOVEBG_H

#include "global.h"

struct BgDblueMovebg;

typedef void (*BgDblueMovebgActionFunc)(struct BgDblueMovebg*, GlobalContext*);

#define BGDBLUEMOVEBG_GET_F(thisx) ((thisx)->params & 0xF)
#define BGDBLUEMOVEBG_GET_FF0(thisx) (((thisx)->params >> 4) & 0xFF)
#define BGDBLUEMOVEBG_GET_F000(thisx) (((thisx)->params >> 0xC) & 0xF)

#define BGDBLUEMOVEBG_F_8 8

typedef struct BgDblueMovebg {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ BgDblueMovebgActionFunc actionFunc;
    /* 0x0160 */ s32 unk_160;
    /* 0x0164 */ Gfx* unk_164;
    /* 0x0168 */ Gfx* unk_168;
    /* 0x016C */ TexturePtr unk_16C;
    /* 0x0170 */ s8 unk_170;
    /* 0x0171 */ s8 unk_171;
    /* 0x0172 */ u16 unk_172;
    /* 0x0174 */ u16 unk_174;
    /* 0x0178 */ s32 unk_178;
    /* 0x017C */ UNK_TYPE1 unk17C[2];
    /* 0x017E */ s16 unk_17E;
    /* 0x0180 */ s16 unk_180;
    /* 0x0184 */ f32 unk_184;
    /* 0x0188 */ s16 unk_188;
    /* 0x018A */ s16 unk_18A;
    /* 0x018C */ s16 unk_18C;
    /* 0x018E */ s16 unk_18E;
    /* 0x0190 */ Vec3f unk_190;
    /* 0x019C */ Vec3f unk_19C;
    /* 0x01A8 */ Vec3f unk_1A8;
    /* 0x01B4 */ UNK_TYPE1 unk1B4[2];
    /* 0x01B6 */ s16 unk_1B6[2];
    /* 0x01BC */ s32 unk_1BC;
    /* 0x01C0 */ s32 unk_1C0;
    /* 0x01C4 */ s32 unk_1C4;
    /* 0x01C8 */ s32 unk_1C8;
    /* 0x01CC */ s16 unk_1CC;
    /* 0x01CE */ s16 unk_1CE;
    /* 0x01D0 */ s16 unk_1D0;
    /* 0x01D2 */ s16 unk_1D2;
    /* 0x01D4 */ f32 unk_1D4;
    /* 0x01D8 */ s16 unk_1D8[2][8];
    /* 0x01F8 */ f32 unk_1F8[2][8];
    /* 0x0238 */ Vec3f unk_238[2][8];
    /* 0x02F8 */ Actor* unk_2F8[2];
    /* 0x0300 */ u8 unk_300[2][8];
    /* 0x0310 */ UNK_TYPE1 unk310[0x60];
} BgDblueMovebg; // size = 0x370

extern const ActorInit Bg_Dblue_Movebg_InitVars;

#endif // Z_BG_DBLUE_MOVEBG_H
