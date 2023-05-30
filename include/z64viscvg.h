#ifndef Z64_VISCVG_H
#define Z64_VISCVG_H

#include "ultra64.h"
#include "color.h"

typedef struct struct_801F8010 {
    /* 0x0 */ u32 type;
    /* 0x4 */ u32 setScissor;
    /* 0x8 */ Color_RGBA8_u32 color;
    /* 0xC */ Color_RGBA8 envColor;
} struct_801F8010; // size = 0x10

void VisCvg_Init(struct_801F8010* this);
void VisCvg_Destroy(struct_801F8010* this);
void VisCvg_Draw(struct_801F8010* this, Gfx** gfxp);

#endif
