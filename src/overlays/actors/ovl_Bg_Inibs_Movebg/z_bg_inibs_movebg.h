#ifndef Z_BG_INIBS_MOVEBG_H
#define Z_BG_INIBS_MOVEBG_H

#include "global.h"

struct BgInibsMovebg;

#define BGINIBSMOVEBG_GET_F(thisx) (u16)(thisx.actor.params) & 0xF

typedef struct BgInibsMovebg {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s32 unk_15C;
    /* 0x160 */ s32 unk_160;
    /* 0x164 */ s32 unk_164;
} BgInibsMovebg; // size = 0x168

extern const ActorInit Bg_Inibs_Movebg_InitVars;

#endif // Z_BG_INIBS_MOVEBG_H
