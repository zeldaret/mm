#ifndef Z_BG_CRACE_MOVEBG_H
#define Z_BG_CRACE_MOVEBG_H

#include "global.h"
#include "assets/objects/object_crace_object/object_crace_object.h"

struct BgCraceMovebg;

typedef void (*BgCraceMovebgActionFunc)(struct BgCraceMovebg*, PlayState*);

#define BGCRACEMOVEBG_GET_F(thisx) (((thisx)->params) & 0xF)
#define BGCRACEMOVEBG_GET_7F0(thisx) (((thisx)->params >> 4) & 0x7F)
#define BGCRACEMOVEBG_GET_3F80(thisx) (((thisx)->params >> 7) & 0x7F)
#define BGCRACEMOVEBG_GET_F800(thisx) (((thisx)->params >> 0xB) & 0x1F)

typedef struct BgCraceMovebg {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgCraceMovebgActionFunc actionFunc;
    /* 0x160 */ f32 unk160;
    /* 0x164 */ f32 unk164;
    /* 0x168 */ UNK_TYPE1 pad168[0x4];
    /* 0x16C */ f32 unk16C;
    /* 0x170 */ s32 unk170;
    /* 0x174 */ s32 unk174;
    /* 0x178 */ Vec3f unk178;
    /* 0x184 */ u8 unk184;
    /* 0x188 */ Vec3f unk188;
} BgCraceMovebg; // size = 0x194

extern const ActorInit Bg_Crace_Movebg_InitVars;

#endif // Z_BG_CRACE_MOVEBG_H
