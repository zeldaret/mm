#include <ultra64.h>
#include <global.h>

extern u16 sGfxPrintFontTLUT[64];
extern u16 sGfxPrintUnkTLUT[16];
extern u8 sGfxPrintUnkData[8];
extern u8 sGfxPrintFontData[2048];

#define gDPSetPrimColorMod(pkt, m, l, rgba)                                                    \
    {                                                                                          \
        Gfx* _g = (Gfx*)(pkt);                                                                 \
                                                                                               \
        _g->words.w0 = (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)); \
        _g->words.w1 = (rgba);                                                                 \
    }

/* GfxPrint_InitDlist */
void func_80085570(GfxPrint* this) {
    s32 width = 16;
    s32 height = 256;
    s32 i;

    gDPPipeSync(this->dlist++);
    gDPSetOtherMode(this->dlist++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_IA16 | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gDPSetCombineMode(this->dlist++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPLoadTextureBlock_4b(this->dlist++, sGfxPrintFontData, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadTLUT(this->dlist++, 64, 256, sGfxPrintFontTLUT);

    for (i = 1; i < 4; i++) {
        gDPSetTile(this->dlist++, G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, i * 2, i, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                   G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
        gDPSetTileSize(this->dlist++, i * 2, 0, 0, 60, 1020);
    }

    gDPSetPrimColorMod(this->dlist++, 0, 0, this->color.rgba);

    gDPLoadMultiTile_4b(this->dlist++, sGfxPrintUnkData, 0, 1, G_IM_FMT_CI, 2, 8, 0, 0, 1, 7, 4,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 1, 3, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadTLUT(this->dlist++, 16, 320, sGfxPrintUnkTLUT);

    for (i = 1; i < 4; i++) {
        gDPSetTile(this->dlist++, G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, i * 2 + 1, 4, G_TX_NOMIRROR | G_TX_WRAP, 3,
                   G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 1, G_TX_NOLOD);
        gDPSetTileSize(this->dlist++, i * 2 + 1, 0, 0, 4, 28);
    }
}

/* GfxPrint_SetColor */
void func_800859BC(GfxPrint* this, u32 r, u32 g, u32 b, u32 a) {
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;
    gDPPipeSync(this->dlist++);
    gDPSetPrimColorMod(this->dlist++, 0, 0, this->color.rgba);
}

/* GfxPrint_SetPosPx */
void func_80085A08(GfxPrint* this, s32 x, s32 y) {
    this->posX = this->baseX + (x << 2);
    this->posY = this->baseY + (y << 2);
}

/* GfxPrint_SetPos */
void func_80085A2C(GfxPrint* this, s32 x, s32 y) {
    func_80085A08(this, x << 3, y << 3);
}

/* GfxPrint_SetBasePosPx */
void func_80085A54(GfxPrint* this, s32 x, s32 y) {
    this->baseX = x << 2;
    this->baseY = y << 2;
}

/* GfxPrint_PrintCharImpl */
#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_80085A68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_80085D74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_80085F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_80085F8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_80085FE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_80086010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_80086064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_8008606C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_800860A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_800860B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/boot/gfxprint/func_800860D8.asm")
