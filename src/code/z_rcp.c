#include <ultra64.h>
#include <global.h>

Gfx sSetupDL[438] = {
    /* 0x00 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetOtherMode(G_AD_NOISE | G_CD_NOISE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_ZB_CLD_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x01 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x02 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x03 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x04 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x05 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x06 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_TEX_EDGE2),
    gsSPLoadGeometryMode(G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x07 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x08 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x09 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x0A */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x0B */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x0C */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x0D */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x0E */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x0F */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x10 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x11 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_TEX_EDGE | G_RM_AA_ZB_TEX_EDGE2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x12 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x13 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | AA_EN | Z_CMP | IM_RD | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA |
                         FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA) |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x14 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x15 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x16 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x17 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x18 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x19 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x1A */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x1B */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x1C */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_AA_TEX_EDGE | G_RM_AA_TEX_EDGE2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x1D */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0, NOISE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x1E */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_LINE | G_RM_AA_ZB_XLU_LINE2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x1F */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_HILITERGBA, G_CC_HILITERGBA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x20 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_HILITERGBA, G_CC_HILITERGBA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x21 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, SHADE, 1, 0, TEXEL0, SHADE, ENVIRONMENT, COMBINED, TEXEL0, COMBINED,
                       ENVIRONMENT, COMBINED, TEXEL0, COMBINED),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                         G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x22 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x23 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_DECAL | G_RM_AA_ZB_XLU_DECAL2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x24 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x25 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x26 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x27 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x28 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, TEXEL1, TEXEL0, PRIMITIVE, TEXEL0, 0, 0, 0, COMBINED, 0,
                       0, 0, COMBINED),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_FRONT | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x29 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x2A */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x2B */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x2C */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_PASS2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_ZB_OVL_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x2D */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x2E */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x2F */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x30 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x31 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_XLU_SURF | G_RM_AA_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x32 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),

    /* 0x33 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),

    /* 0x34 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),

    /* 0x35 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, PRIMITIVE, ENVIRONMENT,
                       COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),

    /* 0x36 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, PRIMITIVE, ENVIRONMENT,
                       COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_PASS | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),

    /* 0x37 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, PRIMITIVE, ENVIRONMENT,
                       COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_PASS | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),

    /* 0x38 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_XLU_SURF | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x39 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPLoadGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x3A */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, SHADE, 0),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x3B */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, SHADE, 1, 0, TEXEL0, SHADE, ENVIRONMENT, COMBINED, TEXEL0, COMBINED,
                       ENVIRONMENT, COMBINED, TEXEL0, COMBINED),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_AA_OPA_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x3C */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT,
                       TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x3D */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT,
                       TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetOtherMode(G_AD_NOISE | G_CD_NOISE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x3E */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x3F */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | Z_UPD | IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
                         GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA) |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x40 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_PASS | G_RM_XLU_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x41 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x42 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | Z_CMP | Z_UPD | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA |
                         ALPHA_CVG_SEL | G_RM_PASS | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x43 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | Z_CMP | Z_UPD | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA |
                         ALPHA_CVG_SEL | G_RM_PASS | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x44 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA |
                         ALPHA_CVG_SEL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM) |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x45 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA |
                         ALPHA_CVG_SEL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM) |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x46 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_THRESHOLD | G_ZS_PIXEL | Z_CMP | Z_UPD | CVG_DST_FULL | ZMODE_OPA | CVG_X_ALPHA |
                         ALPHA_CVG_SEL | G_RM_PASS | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x47 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_BAYER | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),

    /* 0x48 */
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_BAYER | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_ZB_CLD_SURF2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx sFillSetupDL[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPDisplayList(&D_0E0001C8),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x08),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPEndDisplayList(),
};

Gfx gEmptyDL[] = {
    gsSPEndDisplayList(),
};

Gfx* Gfx_SetFog(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f) {
    gDPSetFogColor(gfx, r, g, b, a);

    if (n >= 997) {
        if (n >= 1000) {
            gSPFogFactor(gfx + 1, 0, 0); // gSPFogPosition(gfx++, ?, ?)
        } else {
            gSPFogFactor(gfx + 1, 0x7FFF, 0x8100); // gSPFogPosition(gfx++, ?, ?)
        }
    } else {
        if (n < 0) {
            gSPFogFactor(gfx + 1, 0, 255); // gSPFogPosition(gfx++, ?, ?)
        } else {
            gSPFogPosition(gfx + 1, n, f);
        }
    }

    return gfx + 2;
}

Gfx* Gfx_SetFogWithSync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f) {
    gDPPipeSync(gfx++);
    gDPSetFogColor(gfx++, r, g, b, a);

    if (n >= 1000) {
        gSPFogFactor(gfx++, 0, 0); // gSPFogPosition(gfx++, ?, ?)
    } else if (n >= 997) {
        gSPFogFactor(gfx++, 0x7FFF, 0x8100); // gSPFogPosition(gfx++, ?, ?)
    } else if (n < 0) {
        gSPFogFactor(gfx++, 0, 255); // gSPFogPosition(gfx++, ?, ?)
    } else {
        gSPFogPosition(gfx++, n, f);
    }

    return gfx;
}

Gfx* Gfx_SetFog2(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f) {
    return Gfx_SetFog(gfx, r, g, b, a, n, f);
}

Gfx* Gfx_CallSetupDLImpl(Gfx* gfx, u32 i) {
    gSPDisplayList(gfx++, &sSetupDL[6 * i]);
    return gfx;
}

Gfx* Gfx_CallSetupDL(Gfx* gfx, u32 i) {
    return Gfx_CallSetupDLImpl(gfx, i);
}

void Gfx_CallSetupDLAtPtr(Gfx** gfxp, u32 i) {
    *gfxp = Gfx_CallSetupDL(*gfxp, i);
}

Gfx* func_8012BFC4(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x39]);
    return gfx;
}

Gfx* func_8012BFEC(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x39]);
    return gfx;
}

Gfx* func_8012C014(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x34]);
    gDPSetColorDither(gfx++, G_CD_DISABLE);
    return gfx;
}

void func_8012C058(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x3A]);
}

void func_8012C080(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x39]);
}

void func_8012C0A8(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x32]);
}

void func_8012C0D0(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x33]);
}

void func_8012C0F8(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x34]);
}

void func_8012C120(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x35]);
}

void func_8012C148(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x36]);
}

void func_8012C170(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x37]);
}

Gfx* func_8012C198(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x1A]);
    return gfx;
}

void func_8012C1C0(GraphicsContext* gfxCtx) {
    gfxCtx->polyOpa.p = func_8012C198(gfxCtx->polyOpa.p);
}

Gfx* func_8012C1EC(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x17]);
    return gfx;
}

void func_8012C214(GraphicsContext* gfxCtx) {
    gfxCtx->polyOpa.p = func_8012C1EC(gfxCtx->polyOpa.p);
}

void func_8012C240(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x19]);
}

void func_8012C268(GlobalContext* globalCtx) {
    func_8012C28C(globalCtx->state.gfxCtx);
}

void func_8012C28C(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x19]);
}

Gfx* func_8012C2B4(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x47]);
    return gfx;
}

void func_8012C2DC(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x19]);
}

Gfx* func_8012C304(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x48]);
    return gfx;
}

void func_8012C32C(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x1F]);
}

void func_8012C354(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x20]);
}

void func_8012C37C(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x21]);
}

Gfx* func_8012C3A4(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x40]);
    return gfx;
}

Gfx* func_8012C3CC(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x22]);
    return gfx;
}

void func_8012C3F4(GraphicsContext* gfxCtx) {
    gfxCtx->polyOpa.p = func_8012C3CC(gfxCtx->polyOpa.p);
}

void func_8012C420(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x23]);
}

void func_8012C448(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x2C]);
}

void func_8012C470(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x24]);
}

Gfx* func_8012C498(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x1C]);
    return gfx;
}

void func_8012C4C0(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x1C]);
}

void func_8012C4E8(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x2B]);
}

void func_8012C510(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x2D]);
}

void func_8012C538(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->overlay.p++, &sSetupDL[6 * 0x2E]);
}

void func_8012C560(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x26]);
}

void func_8012C588(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x4]);
}

void func_8012C5B0(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x25]);
}

void func_8012C5D8(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x2]);
}

Gfx* func_8012C600(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x27]);
    return gfx;
}

void func_8012C628(GraphicsContext* gfxCtx) {
    gfxCtx->polyOpa.p = func_8012C600(gfxCtx->polyOpa.p);
}

void func_8012C654(GraphicsContext* gfxCtx) {
    gfxCtx->overlay.p = func_8012C600(gfxCtx->overlay.p);
}

void func_8012C680(Gfx** gfxp) {
    Gfx* gfx = *gfxp;
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x27]);
    *gfxp = gfx;
}

void func_8012C6AC(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x28]);
}

void func_8012C6D4(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x29]);
}

void func_8012C6FC(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x2F]);
}

Gfx* func_8012C724(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x42]);
    return gfx;
}

Gfx* func_8012C74C(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x43]);
    return gfx;
}

Gfx* func_8012C774(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x44]);
    gDPSetColorDither(gfx++, G_CD_DISABLE);
    return gfx;
}

Gfx* func_8012C7B8(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x45]);
    gDPSetColorDither(gfx++, G_CD_DISABLE);
    return gfx;
}

Gfx* func_8012C7FC(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x41]);
    gDPSetColorDither(gfx++, G_CD_DISABLE);
    return gfx;
}

Gfx* func_8012C840(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x46]);
    return gfx;
}

Gfx* func_8012C868(Gfx* gfx) {
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x14]);
    gDPSetColorDither(gfx++, G_CD_DISABLE);
    return gfx;
}

void func_8012C8AC(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x2A]);
}

void func_8012C8D4(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->overlay.p++, &sSetupDL[6 * 0x2A]);
}

void func_8012C8FC(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x30]);
}

void func_8012C924(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x31]);
}

void func_8012C94C(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x1B]);
}

void func_8012C974(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x3C]);
    gDPSetColorDither(gfxCtx->polyXlu.p++, G_CD_DISABLE);
}

void func_8012C9BC(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyXlu.p++, &sSetupDL[6 * 0x3D]);
}

void func_8012C9E4(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x38]);
}

void func_8012CA0C(Gfx** gfxp) {
    Gfx* gfx = *gfxp;
    gSPDisplayList(gfx++, &sSetupDL[6 * 0x38]);
    *gfxp = gfx;
}

void func_8012CA38(GraphicsContext* gfxCtx) {
    gSPDisplayList(gfxCtx->polyOpa.p++, &sSetupDL[6 * 0x3B]);
}

Gfx* Gfx_BranchTexScroll(Gfx** gfxp, u32 x, u32 y, s32 width, s32 height) {
    Gfx* displayList = Graph_DlistAlloc(gfxp, 3 * sizeof(Gfx));

    gDPTileSync(displayList);
    gDPSetTileSize(displayList + 1, 0, x, y, (x + ((width - 1) << 2)), (y + ((height - 1) << 2)));
    gSPEndDisplayList(displayList + 2);

    return displayList;
}

void func_8012CB04(Gfx** gfxp, u32 x, u32 y) {
    Gfx_BranchTexScroll(gfxp, x, y, 0, 0);
}

Gfx* func_8012CB28(GraphicsContext* gfxCtx, u32 x, u32 y) {
    return Gfx_TexScroll(gfxCtx, x, y, 0, 0);
}

Gfx* Gfx_TexScroll(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height) {
    Gfx* displayList;

    {
        Gfx* _g = (Gfx*)gfxCtx->polyOpa.d - 4;
        displayList = _g;
        gfxCtx->polyOpa.d = _g;
    }

    x %= 2048;
    y %= 2048;

    gDPTileSync(displayList);
    gDPSetTileSize(displayList + 1, 0, x, y, (x + ((width - 1) << 2)), (y + ((height - 1) << 2)));
    gSPEndDisplayList(displayList + 2);

    return displayList;
}

Gfx* Gfx_TwoTexScroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2,
                      u32 y2, s32 width2, s32 height2) {
    Gfx* displayList;

    {
        Gfx* _g = (Gfx*)gfxCtx->polyOpa.d - 6;
        displayList = _g;
        gfxCtx->polyOpa.d = _g;
    }

    x1 %= 2048;
    y1 %= 2048;
    x2 %= 2048;
    y2 %= 2048;

    gDPTileSync(displayList);
    gDPSetTileSize(displayList + 1, tile1, x1, y1, (x1 + ((width1 - 1) << 2)), (y1 + ((height1 - 1) << 2)));
    gDPTileSync(displayList + 2);
    gDPSetTileSize(displayList + 3, tile2, x2, y2, (x2 + ((width2 - 1) << 2)), (y2 + ((height2 - 1) << 2)));
    gSPEndDisplayList(displayList + 4);

    return displayList;
}

Gfx* Gfx_TwoTexScrollEnvColor(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2,
                              u32 x2, u32 y2, s32 width2, s32 height2, s32 r, s32 g, s32 b, s32 a) {
    Gfx* displayList;

    {
        Gfx* _g = (Gfx*)gfxCtx->polyOpa.d - 6;
        displayList = _g;
        gfxCtx->polyOpa.d = _g;
    }

    x1 %= 2048;
    y1 %= 2048;
    x2 %= 2048;
    y2 %= 2048;

    gDPTileSync(displayList);
    gDPSetTileSize(displayList + 1, tile1, x1, y1, (x1 + ((width1 - 1) << 2)), (y1 + ((height1 - 1) << 2)));
    gDPTileSync(displayList + 2);
    gDPSetTileSize(displayList + 3, tile2, x2, y2, (x2 + ((width2 - 1) << 2)), (y2 + ((height2 - 1) << 2)));
    gDPSetEnvColor(displayList + 4, r, g, b, a);
    gSPEndDisplayList(displayList + 5);

    return displayList;
}

Gfx* Gfx_EnvColor(GraphicsContext* gfxCtx, s32 r, s32 g, s32 b, s32 a) {
    Gfx* displayList;

    {
        Gfx* _g = (Gfx*)gfxCtx->polyOpa.d - 2;
        displayList = _g;
        gfxCtx->polyOpa.d = _g;
    }

    gDPSetEnvColor(displayList, r, g, b, a);
    gSPEndDisplayList(displayList + 1);

    return displayList;
}

Gfx* Gfx_PrimColor(GraphicsContext* gfxCtx, s32 lodfrac, s32 r, s32 g, s32 b, s32 a) {
    Gfx* displayList;

    {
        Gfx* _g = (Gfx*)gfxCtx->polyOpa.d - 2;
        displayList = _g;
        gfxCtx->polyOpa.d = _g;
    }

    gDPSetPrimColor(displayList, 0, lodfrac, r, g, b, a);
    gSPEndDisplayList(displayList + 1);

    return displayList;
}

#ifdef NON_MATCHING
// regalloc, some reorderings
void func_8012CF0C(GraphicsContext* gfxCtx, s32 iParm2, s32 iParm3, u8 r, u8 g, u8 b) {
    s32 i;
    Gfx* gfx;

    gSegments[0] = 0;
    gSegments[14] = (u32)graphDlEntry;
    gSegments[15] = (u32)gfxCtx->framebuffer;

    gfx = graphDlEntry + 0x16;
    gSPDisplayList(gfx + 0, &D_0E000140);
    gSPDisplayList(gfx + 1, D_801C1CA0);
    gDPSetColorImage(gfx + 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_801FBBCC, 0x0F000000);
    if (gfxCtx->zbuffer != NULL) {
        gDPSetDepthImage(gfx + 3, gfxCtx->zbuffer);
    } else {
        gDPSetDepthImage(gfx + 3, 0x0F000000);
    }
    gSPEndDisplayList(gfx + 4);

    gfx = graphDlEntry + 0x39;
    gDPSetScissor(gfx + 0, G_SC_NON_INTERLACE, 0, 0, D_801FBBCC, D_801FBBCE);
    gSPEndDisplayList(gfx + 1);

    gfx = graphDlEntry + 0x9;
    if (gfxCtx->zbuffer == NULL) {
        gSPEndDisplayList(gfx + 0);
    } else {
        gDPSetColorImage(gfx + 0, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_801FBBCC, gfxCtx->zbuffer);
        gDPPipeSync(gfx + 1);
        gDPSetCycleType(gfx + 2, G_CYC_FILL);
        gDPSetRenderMode(gfx + 3, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(gfx + 4, (GPACK_RGBA5551(0xFF, 0xFF, 0xF0, 0) << 16) | GPACK_RGBA5551(0xFF, 0xFF, 0xF0, 0));
        gSPDisplayList(gfx + 5, &D_0E0002C8);
        gDPSetColorImage(gfx + 6, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_801FBBCC, gfxCtx->zbuffer);
        gSPEndDisplayList(gfx + 7);
    }

    gfx = graphDlEntry + 0x11;
    gDPSetColorImage(gfx + 0, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_801FBBCC, 0x0F000000);
    gDPSetCycleType(gfx + 1, G_CYC_FILL);
    gDPSetRenderMode(gfx + 2, G_RM_NOOP, G_RM_NOOP2);
    gDPSetFillColor(gfx + 3, GPACK_RGBA5551(r, g, b, 0));
    gSPBranchList(gfx + 4, &D_0E0002C8);

    gfx = graphDlEntry + 0x59;
    gDPFillRectangle(gfx + 0, 0, 0, D_801FBBCC - 1, D_801FBBCE - 1);
    gDPPipeSync(gfx + 1);
    gSPEndDisplayList(gfx + 2);

    gfx = graphDlEntry + 0x5C;
    gDPFillRectangle(gfx + 0, 0, 0, D_801FBBCC, D_801FBBCE);
    gDPPipeSync(gfx + 1);
    gSPEndDisplayList(gfx + 2);

    gfx = graphDlEntry + 0x28;
    for (i = 0; i < 0x10; i++) {
        if (i == 0xE) {
            gSPNoOp(gfx + i);
        } else {
            gSPSegment(gfx + i, i, gSegments[i]);
        }
    }
    gSPEndDisplayList(gfx + i);

    gSPDisplayList(gfxCtx->polyOpa.p++, graphDlEntry + 0x16);
    gSPDisplayList(gfxCtx->polyXlu.p++, graphDlEntry + 0x16);
    gSPDisplayList(gfxCtx->overlay.p++, graphDlEntry + 0x16);
    gSPDisplayList(gfxCtx->unk1B8.p++, graphDlEntry + 0x16);

    if (iParm3) {
        gSPDisplayList(gfxCtx->polyOpa.p++, &D_0E000048);
    }
    if (iParm2) {
        gSPDisplayList(gfxCtx->polyOpa.p++, &D_0E000088);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_rcp/func_8012CF0C.asm")
#endif

void func_8012D374(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b) {
    if ((R_PAUSE_MENU_MODE < 2) && (D_801F6D10 < 2)) {
        func_8012CF0C(gfxCtx, 1, 1, r, g, b);
    } else {
        func_8012CF0C(gfxCtx, 0, 0, r, g, b);
    }
}

void func_8012D40C(f32* param_1, f32* param_2, s16* param_3) {
    param_1[0] = param_3[0] * 0.25f;
    param_1[1] = param_3[1] * 0.25f;
    param_1[2] = param_3[4] * 0.25f;
    param_1[3] = param_3[5] * 0.25f;

    param_2[0] = param_1[0] / (gScreenWidth / 2);
    param_2[2] = param_1[2] - param_1[0];
    param_2[1] = param_1[1] / (gScreenHeight / 2);
    param_2[3] = param_1[3] - param_1[1];
}
