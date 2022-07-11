/*
 * File: z_kaleido_debug.c
 * Overlay: ovl_kaleido_scope
 * Description:
 */

#include "z_kaleido_scope.h"
#include "interface/parameter_static/parameter_static.h"

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

s32 D_8082B0F0 = 0;

s32 D_8082B0F4 = 0;

s16 D_8082B0F8[] = {
    0x0041, 0x000E, 0x0029, 0x0091, 0x000E, 0x0015, 0x00C1, 0x000E, 0x0023, 0x002A, 0x0025, 0x0016, 0x0041, 0x0025,
    0x0016, 0x0058, 0x0025, 0x0016, 0x006F, 0x0025, 0x0016, 0x0086, 0x0025, 0x0016, 0x009D, 0x0025, 0x0016, 0x002A,
    0x0033, 0x0016, 0x0041, 0x0033, 0x0016, 0x0058, 0x0033, 0x0016, 0x006F, 0x0033, 0x0016, 0x0086, 0x0033, 0x0016,
    0x009D, 0x0033, 0x0016, 0x002A, 0x0041, 0x0016, 0x0041, 0x0041, 0x0016, 0x0058, 0x0041, 0x0016, 0x006F, 0x0041,
    0x0016, 0x0086, 0x0041, 0x0016, 0x009D, 0x0041, 0x0016, 0x002A, 0x0050, 0x0016, 0x0041, 0x0050, 0x0016, 0x0058,
    0x0050, 0x0016, 0x006F, 0x0050, 0x0016, 0x0086, 0x0050, 0x0016, 0x009D, 0x0050, 0x0016, 0x00CA, 0x0025, 0x000E,
    0x00D7, 0x0025, 0x000E, 0x00E5, 0x0025, 0x000E, 0x00F3, 0x0025, 0x000E, 0x0101, 0x0025, 0x000E, 0x010F, 0x0025,
    0x000E, 0x00CA, 0x0033, 0x000E, 0x00D7, 0x0033, 0x000E, 0x00E5, 0x0033, 0x000E, 0x00F3, 0x0033, 0x000E, 0x0101,
    0x0033, 0x000E, 0x010F, 0x0033, 0x000E, 0x00CA, 0x0041, 0x000E, 0x00D7, 0x0041, 0x000E, 0x00E5, 0x0041, 0x000E,
    0x00F3, 0x0041, 0x000E, 0x0101, 0x0041, 0x000E, 0x010F, 0x0041, 0x000E, 0x00CA, 0x0050, 0x000E, 0x00D7, 0x0050,
    0x000E, 0x00E5, 0x0050, 0x000E, 0x00F3, 0x0050, 0x000E, 0x0101, 0x0050, 0x000E, 0x010F, 0x0050, 0x000E, 0x002A,
    0x006F, 0x000E, 0x0036, 0x006F, 0x000E, 0x0042, 0x006F, 0x000E, 0x004E, 0x006F, 0x000E, 0x0072, 0x0063, 0x000E,
    0x008E, 0x0063, 0x000E, 0x00BC, 0x0063, 0x000E, 0x00CA, 0x0063, 0x000E, 0x00D8, 0x0063, 0x000E, 0x00E6, 0x0063,
    0x000E, 0x00F4, 0x0063, 0x000E, 0x0102, 0x0063, 0x000E, 0x00BC, 0x0071, 0x000E, 0x00CA, 0x0071, 0x000E, 0x00D8,
    0x0071, 0x000E, 0x00E6, 0x0071, 0x000E, 0x00F4, 0x0071, 0x000E, 0x0102, 0x0071, 0x000E, 0x0110, 0x0071, 0x000E,
    0x0036, 0x008D, 0x000E, 0x0070, 0x0086, 0x000E, 0x009B, 0x0086, 0x000E, 0x00C2, 0x0082, 0x0020, 0x00C2, 0x0090,
    0x0020, 0x0106, 0x0086, 0x000E, 0x002B, 0x00A8, 0x000E, 0x0037, 0x00A8, 0x000E, 0x0043, 0x00A8, 0x000E, 0x004F,
    0x00A8, 0x000E, 0x007F, 0x00A8, 0x000E, 0x008B, 0x00A8, 0x000E, 0x0097, 0x00A8, 0x000E, 0x00A3, 0x00A8, 0x000E,
    0x00CA, 0x00A8, 0x0016, 0x00DF, 0x00A8, 0x0016, 0x00F4, 0x00A8, 0x0016, 0x0109, 0x00A8, 0x0016, 0x002A, 0x00CA,
    0x000E, 0x0049, 0x00CA, 0x000E, 0x0088, 0x00CA, 0x0026, 0x00D6, 0x00CA, 0x004A, 0x00D6, 0x00CA, 0x004A, 0x0000,
};

s16 D_8082B328[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A, 0x000B,
    0x000C, 0x000D, 0x000E, 0x000F, 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0023,
    0x003E, 0x0038, 0x0047, 0x0045, 0x0040, 0x0032, 0x003A, 0x0046, 0x0039, 0x0042, 0x0048, 0x0033,
    0x003C, 0x003D, 0x0037, 0x003F, 0x0036, 0x0034, 0x0043, 0x0041, 0x003B, 0x0044, 0x0049, 0x0035,
};

s16 D_8082B388[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x001B, 0x0033, 0x0037, 0x0038, 0x0039,
    0x0046, 0x0047, 0x0048, 0x0049, 0x004B, 0x004C, 0x0050, 0x0054, 0x0058,
};

s32 D_8082B3AC = 0;

s32 D_8082B3B0[] = { 0, 0, 0, 0 };

void KaleidoScope_DrawDebugEditorText(Gfx** gfxp) {
    GfxPrint printer;
    s32 pad[2];

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, *gfxp);

    GfxPrint_SetPos(&printer, 4, 2);
    GfxPrint_SetColor(&printer, 255, 60, 0, 255);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾙﾋﾟｰ"); // "Rupee"
    GfxPrint_SetPos(&printer, 15, 2);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾊｰﾄ"); // "Heart"
    GfxPrint_SetPos(&printer, 15, 3);
    GfxPrint_Printf(&printer, "%s", "MAX");
    GfxPrint_SetPos(&printer, 21, 3);
    GfxPrint_Printf(&printer, "%s", "NOW");
    GfxPrint_SetPos(&printer, 28, 3);
    GfxPrint_Printf(&printer, "%s", "/4");
    GfxPrint_SetPos(&printer, 4, 5);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｱ");
    GfxPrint_SetPos(&printer, 4, 6);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｲ");
    GfxPrint_SetPos(&printer, 4, 7);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾃ");
    GfxPrint_SetPos(&printer, 4, 8);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾑ");
    GfxPrint_SetPos(&printer, 24, 5);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾏ");
    GfxPrint_SetPos(&printer, 24, 6);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｽ");
    GfxPrint_SetPos(&printer, 24, 7);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｸ");
    GfxPrint_SetPos(&printer, 4, 13);
    GfxPrint_Printf(&printer, "%s", "BOSS");
    GfxPrint_SetPos(&printer, 13, 13);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｹ");
    GfxPrint_SetPos(&printer, 13, 14);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾝ");
    GfxPrint_SetPos(&printer, 17, 13);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾀ");
    GfxPrint_SetPos(&printer, 17, 14);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾃ");
    GfxPrint_SetPos(&printer, 21, 13);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｵｶ");
    GfxPrint_SetPos(&printer, 21, 14);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾘﾅ");
    GfxPrint_SetPos(&printer, 4, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｽｹｼﾞｭｰﾙ");
    GfxPrint_SetPos(&printer, 12, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾔ");
    GfxPrint_SetPos(&printer, 12, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾀﾃ");
    GfxPrint_SetPos(&printer, 16, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾎﾞﾑ");
    GfxPrint_SetPos(&printer, 16, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾌｸﾛ");
    GfxPrint_SetPos(&printer, 22, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｷﾝ");
    GfxPrint_SetPos(&printer, 22, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｽﾀ");
    GfxPrint_SetPos(&printer, 29, 17);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ﾊｰﾄ");
    GfxPrint_SetPos(&printer, 29, 18);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｶｹﾗ");
    GfxPrint_SetPos(&printer, 34, 18);
    GfxPrint_Printf(&printer, "%s", "/4");
    GfxPrint_SetPos(&printer, 4, 21);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｶ");
    GfxPrint_SetPos(&printer, 4, 22);
    GfxPrint_Printf(&printer, "%s", GFXP_KATAKANA "ｷﾞ");
    GfxPrint_SetPos(&printer, 12, 21);
    GfxPrint_Printf(&printer, "%s", "MAP");
    GfxPrint_SetPos(&printer, 12, 22);
    GfxPrint_Printf(&printer, "%s", "ｺﾝﾊﾟ");
    GfxPrint_SetPos(&printer, 23, 21);
    GfxPrint_Printf(&printer, "%s", "ﾖｳ");
    GfxPrint_SetPos(&printer, 23, 22);
    GfxPrint_Printf(&printer, "%s", "ｾｲ");
    GfxPrint_SetPos(&printer, 4, 25);
    GfxPrint_Printf(&printer, "%s", "ｲ");
    GfxPrint_SetPos(&printer, 4, 26);
    GfxPrint_Printf(&printer, "%s", "ﾉ");
    GfxPrint_SetPos(&printer, 4, 27);
    GfxPrint_Printf(&printer, "%s", "ﾁ");
    GfxPrint_SetPos(&printer, 8, 25);
    GfxPrint_Printf(&printer, "%s", "ﾏ");
    GfxPrint_SetPos(&printer, 8, 26);
    GfxPrint_Printf(&printer, "%s", "ﾎ");
    GfxPrint_SetPos(&printer, 8, 27);
    GfxPrint_Printf(&printer, "%s", "ｳ");
    GfxPrint_SetPos(&printer, 13, 25);
    GfxPrint_Printf(&printer, "%s", "ﾀｶﾗ");
    GfxPrint_SetPos(&printer, 13, 26);
    GfxPrint_Printf(&printer, "%s", "ｸｼﾞ");
    GfxPrint_SetPos(&printer, 23, 24);
    GfxPrint_Printf(&printer, "%s", "ｷﾝｲﾛ");
    GfxPrint_SetPos(&printer, 23, 26);
    GfxPrint_Printf(&printer, "%s", "ﾎﾞﾝ");
    GfxPrint_SetPos(&printer, 23, 27);
    GfxPrint_Printf(&printer, "%s", "ﾊﾞｰｽﾞ");

    *gfxp = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);
}

void KaleidoScope_DrawDigit(PlayState* play, s32 digit, s32 rectLeft, s32 rectTop) {
    OPEN_DISPS(play->state.gfxCtx);

    gDPLoadTextureBlock(POLY_OPA_DISP++, ((u8*)gCounterDigit0Tex + (8 * 16 * digit)), G_IM_FMT_I, G_IM_SIZ_8b, 8, 16, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(POLY_OPA_DISP++, rectLeft << 2, rectTop << 2, (rectLeft + 8) << 2, (rectTop + 16) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    CLOSE_DISPS(play->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80819238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80819F04.s")
