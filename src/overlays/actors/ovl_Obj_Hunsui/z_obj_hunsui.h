#ifndef Z_OBJ_HUNSUI_H
#define Z_OBJ_HUNSUI_H

#include "global.h"
#include "overlays/actors/ovl_Bg_Dblue_Movebg/z_bg_dblue_movebg.h"

struct ObjHunsui;

typedef void (*ObjHunsuiActionFunc)(struct ObjHunsui*, GlobalContext*);

#define OBJHUNSUI_GET_7F(thisx) ((thisx)->params & 0x7F)
#define OBJHUNSUI_GET_F80(thisx) (((thisx)->params >> 7) & 0x1F)
#define OBJHUNSUI_GET_F000(thisx) (((thisx)->params >> 0xC) & 0xF)

enum {
    /* 0 */ OBJHUNSUI_F000_0,
    /* 1 */ OBJHUNSUI_F000_1,
    /* 2 */ OBJHUNSUI_F000_2,
    /* 3 */ OBJHUNSUI_F000_3,
    /* 4 */ OBJHUNSUI_F000_4,
    /* 5 */ OBJHUNSUI_F000_5,
    /* 6 */ OBJHUNSUI_F000_6,
};

typedef struct ObjHunsui {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ObjHunsuiActionFunc actionFunc;
    /* 0x0160 */ s16 unk_160;
    /* 0x0164 */ s32 unk_164;
    /* 0x0168 */ s32 unk_168;
    /* 0x016C */ s8 unk_16C;
    /* 0x016D */ s8 unk_16D;
    /* 0x016E */ s8 unk_16E;
    /* 0x0170 */ s16 unk_170;
    /* 0x0172 */ u16 unk_172;
    /* 0x0174 */ f32 unk_174;
    /* 0x0178 */ f32 unk_178;
    /* 0x017C */ s16 unk_17C;
    /* 0x0180 */ s32 unk_180;
    /* 0x0184 */ s16 unk_184;
    /* 0x0186 */ s16 unk_186;
    /* 0x0188 */ s16 unk_188;
    /* 0x018A */ s16 unk_18A;
    /* 0x018C */ s16 unk_18C;
    /* 0x0190 */ f32 unk_190;
    /* 0x0194 */ f32 unk_194;
    /* 0x0198 */ f32 unk_198;
    /* 0x019C */ f32 unk_19C;
    /* 0x01A0 */ f32 unk_1A0;
    /* 0x01A4 */ s16 unk_1A4;
    /* 0x0196 */ UNK_TYPE1 unk1A6[0x6];
    /* 0x01AC */ f32 unk_1AC;
    /* 0x01B0 */ f32 unk_1B0;
    /* 0x01B4 */ BgDblueMovebg* unk_1B4;
} ObjHunsui; // size = 0x1B8

extern const ActorInit Obj_Hunsui_InitVars;

#endif // Z_OBJ_HUNSUI_H
