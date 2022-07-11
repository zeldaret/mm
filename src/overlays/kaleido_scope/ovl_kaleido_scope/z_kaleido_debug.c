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
