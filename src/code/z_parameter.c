#include "global.h"
#include "z64view.h"
#include "interface/parameter_static/parameter_static.h"
#include "interface/do_action_static/do_action_static.h"
#include "misc/story_static/story_static.h"

#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"
#include "overlays/actors/ovl_En_Mm3/z_en_mm3.h"

typedef enum {
    /* 0 */ PICTO_BOX_STATE_OFF,         // Not using the pictograph
    /* 1 */ PICTO_BOX_STATE_LENS,        // Looking through the lens of the pictograph
    /* 2 */ PICTO_BOX_STATE_SETUP_PHOTO, // Looking at the photo currently taken
    /* 3 */ PICTO_BOX_STATE_PHOTO
} PictoBoxState;

typedef struct {
    /* 0x00 */ u8 scene;
    /* 0x01 */ u8 flags1;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
} RestrictionFlags;

Input sPostmanTimerInput[4];

#define RESTRICTIONS_TABLE_END 0xFF

#define RESTRICTIONS_GET_BITS(flags, s) (((flags) & (3 << (s))) >> (s))

// does nothing
#define RESTRICTIONS_GET_HGAUGE(flags) RESTRICTIONS_GET_BITS((flags)->flags1, 6)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_B_BUTTON(flags) RESTRICTIONS_GET_BITS((flags)->flags1, 4)
// does nothing
#define RESTRICTIONS_GET_A_BUTTON(flags) RESTRICTIONS_GET_BITS((flags)->flags1, 2)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_TRADE_ITEMS(flags) RESTRICTIONS_GET_BITS((flags)->flags1, 0)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_SONG_OF_TIME(flags) RESTRICTIONS_GET_BITS((flags)->flags2, 6)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_SONG_OF_DOUBLE_TIME(flags) RESTRICTIONS_GET_BITS((flags)->flags2, 4)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_INV_SONG_OF_TIME(flags) RESTRICTIONS_GET_BITS((flags)->flags2, 2)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_SONG_OF_SOARING(flags) RESTRICTIONS_GET_BITS((flags)->flags2, 0)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_SONG_OF_STORMS(flags) RESTRICTIONS_GET_BITS((flags)->flags3, 6)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_MASKS(flags) RESTRICTIONS_GET_BITS((flags)->flags3, 4)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_PICTO_BOX(flags) RESTRICTIONS_GET_BITS((flags)->flags3, 2)
// 0 = usable, !0 = unusable
#define RESTRICTIONS_GET_ALL(flags) RESTRICTIONS_GET_BITS((flags)->flags3, 0)

#define RESTRICTIONS_SET(hGauge, bButton, aButton, tradeItems, songOfTime, songOfDoubleTime, invSongOfTime, \
                         songOfSoaring, songOfStorms, masks, pictoBox, all)                                 \
    ((((hGauge)&3) << 6) | (((bButton)&3) << 4) | (((aButton)&3) << 2) | (((tradeItems)&3) << 0)),          \
        ((((songOfTime)&3) << 6) | (((songOfDoubleTime)&3) << 4) | (((invSongOfTime)&3) << 2) |             \
         (((songOfSoaring)&3) << 0)),                                                                       \
        ((((songOfStorms)&3) << 6) | (((masks)&3) << 4) | (((pictoBox)&3) << 2) | (((all)&3) << 0))

// Common patterns
#define RESTRICTIONS_NONE RESTRICTIONS_SET(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define RESTRICTIONS_INDOORS RESTRICTIONS_SET(0, 1, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1)
#define RESTRICTIONS_MOON RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0)
#define RESTRICTIONS_NO_DOUBLE_TIME RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0)

RestrictionFlags sRestrictionFlags[] = {
    { SCENE_20SICHITAI2, RESTRICTIONS_NONE },
    { SCENE_UNSET_1, RESTRICTIONS_NONE },
    { SCENE_UNSET_2, RESTRICTIONS_NONE },
    { SCENE_UNSET_3, RESTRICTIONS_NONE },
    { SCENE_UNSET_4, RESTRICTIONS_NONE },
    { SCENE_UNSET_5, RESTRICTIONS_NONE },
    { SCENE_UNSET_6, RESTRICTIONS_NONE },
    { SCENE_KAKUSIANA, RESTRICTIONS_NONE },
    { SCENE_SPOT00, RESTRICTIONS_NONE },
    { SCENE_UNSET_9, RESTRICTIONS_NONE },
    { SCENE_WITCH_SHOP, RESTRICTIONS_INDOORS },
    { SCENE_LAST_BS, RESTRICTIONS_MOON },
    { SCENE_HAKASHITA, RESTRICTIONS_NONE },
    { SCENE_AYASHIISHOP, RESTRICTIONS_INDOORS },
    { SCENE_UNSET_E, RESTRICTIONS_NONE },
    { SCENE_UNSET_F, RESTRICTIONS_NONE },
    { SCENE_OMOYA, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0) },
    { SCENE_BOWLING, RESTRICTIONS_INDOORS },
    { SCENE_SONCHONOIE, RESTRICTIONS_INDOORS },
    { SCENE_IKANA, RESTRICTIONS_NONE },
    { SCENE_KAIZOKU, RESTRICTIONS_NONE },
    { SCENE_MILK_BAR, RESTRICTIONS_INDOORS },
    { SCENE_INISIE_N, RESTRICTIONS_NONE },
    { SCENE_TAKARAYA, RESTRICTIONS_INDOORS },
    { SCENE_INISIE_R, RESTRICTIONS_NONE },
    { SCENE_OKUJOU, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0) },
    { SCENE_OPENINGDAN, RESTRICTIONS_NONE },
    { SCENE_MITURIN, RESTRICTIONS_NONE },
    { SCENE_13HUBUKINOMITI, RESTRICTIONS_NONE },
    { SCENE_CASTLE, RESTRICTIONS_NONE },
    { SCENE_DEKUTES, RESTRICTIONS_SET(0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1) },
    { SCENE_MITURIN_BS, RESTRICTIONS_NONE },
    { SCENE_SYATEKI_MIZU, RESTRICTIONS_INDOORS },
    { SCENE_HAKUGIN, RESTRICTIONS_NONE },
    { SCENE_ROMANYMAE, RESTRICTIONS_NONE },
    { SCENE_PIRATE, RESTRICTIONS_NONE },
    { SCENE_SYATEKI_MORI, RESTRICTIONS_INDOORS },
    { SCENE_SINKAI, RESTRICTIONS_NONE },
    { SCENE_YOUSEI_IZUMI, RESTRICTIONS_NONE },
    { SCENE_KINSTA1, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_KINDAN2, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_TENMON_DAI, RESTRICTIONS_SET(0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0) },
    { SCENE_LAST_DEKU, RESTRICTIONS_MOON },
    { SCENE_22DEKUCITY, RESTRICTIONS_NONE },
    { SCENE_KAJIYA, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0) },
    { SCENE_00KEIKOKU, RESTRICTIONS_NONE },
    { SCENE_POSTHOUSE, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1) },
    { SCENE_LABO, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1) },
    { SCENE_DANPEI2TEST, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_UNSET_31, RESTRICTIONS_NONE },
    { SCENE_16GORON_HOUSE, RESTRICTIONS_NONE },
    { SCENE_33ZORACITY, RESTRICTIONS_SET(0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0) },
    { SCENE_8ITEMSHOP, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1) },
    { SCENE_F01, RESTRICTIONS_NONE },
    { SCENE_INISIE_BS, RESTRICTIONS_NONE },
    { SCENE_30GYOSON, RESTRICTIONS_NONE },
    { SCENE_31MISAKI, RESTRICTIONS_NONE },
    { SCENE_TAKARAKUJI, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1) },
    { SCENE_UNSET_3A, RESTRICTIONS_NONE },
    { SCENE_TORIDE, RESTRICTIONS_NONE },
    { SCENE_FISHERMAN, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1) },
    { SCENE_GORONSHOP, RESTRICTIONS_INDOORS },
    { SCENE_DEKU_KING, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0) },
    { SCENE_LAST_GORON, RESTRICTIONS_MOON },
    { SCENE_24KEMONOMITI, RESTRICTIONS_NONE },
    { SCENE_F01_B, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_F01C, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_BOTI, RESTRICTIONS_NONE },
    { SCENE_HAKUGIN_BS, RESTRICTIONS_NONE },
    { SCENE_20SICHITAI, RESTRICTIONS_NONE },
    { SCENE_21MITURINMAE, RESTRICTIONS_NONE },
    { SCENE_LAST_ZORA, RESTRICTIONS_MOON },
    { SCENE_11GORONNOSATO2, RESTRICTIONS_NONE },
    { SCENE_SEA, RESTRICTIONS_NONE },
    { SCENE_35TAKI, RESTRICTIONS_NONE },
    { SCENE_REDEAD, RESTRICTIONS_NONE },
    { SCENE_BANDROOM, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0) },
    { SCENE_11GORONNOSATO, RESTRICTIONS_NONE },
    { SCENE_GORON_HAKA, RESTRICTIONS_NONE },
    { SCENE_SECOM, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 3, 0, 3, 0, 0, 0) },
    { SCENE_10YUKIYAMANOMURA, RESTRICTIONS_NONE },
    { SCENE_TOUGITES, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0) },
    { SCENE_DANPEI, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_IKANAMAE, RESTRICTIONS_NONE },
    { SCENE_DOUJOU, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 1) },
    { SCENE_MUSICHOUSE, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 0) },
    { SCENE_IKNINSIDE, RESTRICTIONS_SET(0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0) },
    { SCENE_MAP_SHOP, RESTRICTIONS_INDOORS },
    { SCENE_F40, RESTRICTIONS_NONE },
    { SCENE_F41, RESTRICTIONS_NONE },
    { SCENE_10YUKIYAMANOMURA2, RESTRICTIONS_NONE },
    { SCENE_14YUKIDAMANOMITI, RESTRICTIONS_NONE },
    { SCENE_12HAKUGINMAE, RESTRICTIONS_NONE },
    { SCENE_17SETUGEN, RESTRICTIONS_NONE },
    { SCENE_17SETUGEN2, RESTRICTIONS_NONE },
    { SCENE_SEA_BS, RESTRICTIONS_NONE },
    { SCENE_RANDOM, RESTRICTIONS_NONE },
    { SCENE_YADOYA, RESTRICTIONS_INDOORS },
    { SCENE_KONPEKI_ENT, RESTRICTIONS_NONE },
    { SCENE_INSIDETOWER, RESTRICTIONS_SET(0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0) },
    { SCENE_26SARUNOMORI, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_LOST_WOODS, RESTRICTIONS_NONE },
    { SCENE_LAST_LINK, RESTRICTIONS_MOON },
    { SCENE_SOUGEN, RESTRICTIONS_MOON },
    { SCENE_BOMYA, RESTRICTIONS_INDOORS },
    { SCENE_KYOJINNOMA, RESTRICTIONS_NONE },
    { SCENE_KOEPONARACE, RESTRICTIONS_NO_DOUBLE_TIME },
    { SCENE_GORONRACE, RESTRICTIONS_NONE },
    { SCENE_TOWN, RESTRICTIONS_NONE },
    { SCENE_ICHIBA, RESTRICTIONS_NONE },
    { SCENE_BACKTOWN, RESTRICTIONS_NONE },
    { SCENE_CLOCKTOWER, RESTRICTIONS_NONE },
    { SCENE_ALLEY, RESTRICTIONS_NONE },
    // { RESTRICTIONS_TABLE_END, RESTRICTIONS_NONE }, // See note below
};
//! @note: in `Interface_SetSceneRestrictions`, `RESTRICTIONS_TABLE_END` act as a terminating value to
// stop looping through the array. If a scene is missing, then this will cause issues.

s16 sPictoState = PICTO_BOX_STATE_OFF;
s16 sPictoPhotoBeingTaken = false;

s16 sHBAScoreTier = 0; // Remnant of OoT, non-functional

u16 sMinigameScoreDigits[] = { 0, 0, 0, 0 };

u16 sCUpInvisible = 0;
u16 sCUpTimer = 0;

s16 sMagicMeterOutlinePrimRed = 255;
s16 sMagicMeterOutlinePrimGreen = 255;
s16 sMagicMeterOutlinePrimBlue = 255;
s16 sMagicBorderRatio = 2;
s16 sMagicBorderStep = 1;

s16 sExtraItemBases[] = {
    ITEM_STICK,   // ITEM_STICKS_5
    ITEM_STICK,   // ITEM_STICKS_10
    ITEM_NUT,     // ITEM_NUTS_5
    ITEM_NUT,     // ITEM_NUTS_10
    ITEM_BOMB,    // ITEM_BOMBS_5
    ITEM_BOMB,    // ITEM_BOMBS_10
    ITEM_BOMB,    // ITEM_BOMBS_20
    ITEM_BOMB,    // ITEM_BOMBS_30
    ITEM_BOW,     // ITEM_ARROWS_10
    ITEM_BOW,     // ITEM_ARROWS_30
    ITEM_BOW,     // ITEM_ARROWS_40
    ITEM_BOMBCHU, // ITEM_ARROWS_50 !@bug this data is missing an ITEM_BOW, offsetting the rest by 1
    ITEM_BOMBCHU, // ITEM_BOMBCHUS_20
    ITEM_BOMBCHU, // ITEM_BOMBCHUS_10
    ITEM_BOMBCHU, // ITEM_BOMBCHUS_1
    ITEM_STICK,   // ITEM_BOMBCHUS_5
    ITEM_STICK,   // ITEM_STICK_UPGRADE_20
    ITEM_NUT,     // ITEM_STICK_UPGRADE_30
    ITEM_NUT,     // ITEM_NUT_UPGRADE_30
};

s16 sEnvHazard = PLAYER_ENV_HAZARD_NONE;
s16 sEnvTimerActive = false;
s16 sPostmanBunnyHoodState = POSTMAN_MINIGAME_BUNNY_HOOD_OFF;
OSTime sTimerPausedOsTime = 0;
OSTime sBottleTimerPausedOsTime = 0;
OSTime D_801BF8F8[] = {
    0, 0, 0, 0, 0, 0, 0,
};
OSTime D_801BF930[] = {
    0, 0, 0, 0, 0, 0, 0,
};
u8 sIsTimerPaused = false;
u8 sIsBottleTimerPaused = false;
s16 sTimerId = TIMER_ID_NONE;

s16 D_801BF974 = 0;
s16 D_801BF978 = 10;
s16 D_801BF97C = 255;
f32 D_801BF980 = 1.0f;
s32 D_801BF984 = 0;

Gfx sScreenFillSetupDL[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
};

s16 D_801BF9B0 = 0;
f32 D_801BF9B4[] = { 100.0f, 109.0f };
s16 D_801BF9BC[] = { 0x226, 0x2A8, 0x2A8, 0x2A8 };
s16 D_801BF9C4[] = { 0x9E, 0x9B };
s16 D_801BF9C8[] = { 0x17, 0x16 };
f32 D_801BF9CC[] = { -380.0f, -350.0f };
s16 D_801BF9D4[] = { 0xA7, 0xE3 };
s16 D_801BF9D8[] = { 0xF9, 0x10F };
s16 D_801BF9DC[] = { 0x11, 0x12 };
s16 D_801BF9E0[] = { 0x22, 0x12 };
s16 D_801BF9E4[] = { 0x23F, 0x26C };
s16 D_801BF9E8[] = { 0x26C, 0x26C };

s16 sFinalHoursClockDigitsRed = 0;
s16 sFinalHoursClockFrameEnvRed = 0;
s16 sFinalHoursClockFrameEnvGreen = 0;
s16 sFinalHoursClockFrameEnvBlue = 0;
s16 sFinalHoursClockColorTimer = 15;
s16 sFinalHoursClockColorTargetIndex = 0;

/**
 * Draw a RGBA16 texture on a rectangle
 *
 * @param gfx the display list pointer
 * @param texture
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param rectLeft the x-coordinate of upper-left corner of rectangle
 * @param rectTop the y-coordinate of upper-left corner of rectangle
 * @param rectWidth rectangle width in texels
 * @param rectHeight rectangle height in texels
 * @param dsdx the change in s for each change in x (s5.10)
 * @param dtdy the change in t for each change in y (s5.10)
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawTexRectRGBA16(Gfx* gfx, TexturePtr texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                           s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy) {
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_RGBA, G_IM_SIZ_16b, textureWidth, textureHeight, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + rectWidth) << 2, (rectTop + rectHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    return gfx;
}

/**
 * Draw an IA8 texture on a rectangle
 *
 * @param gfx the display list pointer
 * @param texture
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param rectLeft the x-coordinate of upper-left corner of rectangle
 * @param rectTop the y-coordinate of upper-left corner of rectangle
 * @param rectWidth rectangle width in texels
 * @param rectHeight rectangle height in texels
 * @param dsdx the change in s for each change in x (s5.10)
 * @param dtdy the change in t for each change in y (s5.10)
 * @return Gfx*  the display list pointer
 */
Gfx* Gfx_DrawTexRectIA8(Gfx* gfx, TexturePtr texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                        s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy) {
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, textureWidth, textureHeight, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + rectWidth) << 2, (rectTop + rectHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    return gfx;
}

/**
 * Draw an IA8 texture on a rectangle with a shadow slightly offset to the bottom-right
 *
 * @param gfx the display list pointer
 * @param texture
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param rectLeft the x-coordinate of upper-left corner of rectangle
 * @param rectTop the y-coordinate of upper-left corner of rectangle
 * @param rectWidth rectangle width in texels
 * @param rectHeight rectangle height in texels
 * @param dsdx the change in s for each change in x (s5.10)
 * @param dtdy the change in t for each change in y (s5.10)
 * @param r texture red
 * @param g texture green
 * @param b texture blue
 * @param a texture alpha
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawTexRectIA8_DropShadow(Gfx* gfx, TexturePtr texture, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                                   s16 rectTop, s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy, s16 r, s16 g, s16 b,
                                   s16 a) {
    s16 dropShadowAlpha = a;

    if (a > 100) {
        dropShadowAlpha = 100;
    }

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, dropShadowAlpha);

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, textureWidth, textureHeight, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(gfx++, (rectLeft + 2) * 4, (rectTop + 2) * 4, (rectLeft + rectWidth + 2) * 4,
                        (rectTop + rectHeight + 2) * 4, G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);

    gSPTextureRectangle(gfx++, rectLeft * 4, rectTop * 4, (rectLeft + rectWidth) * 4, (rectTop + rectHeight) * 4,
                        G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    return gfx;
}

/**
 * Draw a colored rectangle with a shadow slightly offset to the bottom-right
 *
 * @param gfx the display list pointer
 * @param rectLeft the x-coordinate of upper-left corner of rectangle
 * @param rectTop the y-coordinate of upper-left corner of rectangle
 * @param rectWidth rectangle width in texels
 * @param rectHeight rectangle height in texels
 * @param dsdx the change in s for each change in x (s5.10)
 * @param dtdy the change in t for each change in y (s5.10)
 * @param r // rectangle red
 * @param g // rectangle green
 * @param b // rectangle blue
 * @param a // rectangle alpha
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawRect_DropShadow(Gfx* gfx, s16 rectLeft, s16 rectTop, s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy,
                             s16 r, s16 g, s16 b, s16 a) {
    s16 dropShadowAlpha = a;

    if (a > 100) {
        dropShadowAlpha = 100;
    }

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, dropShadowAlpha);
    gSPTextureRectangle(gfx++, (rectLeft + 2) * 4, (rectTop + 2) * 4, (rectLeft + rectWidth + 2) * 4,
                        (rectTop + rectHeight + 2) * 4, G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);

    gSPTextureRectangle(gfx++, rectLeft * 4, rectTop * 4, (rectLeft + rectWidth) * 4, (rectTop + rectHeight) * 4,
                        G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    return gfx;
}

/**
 * Draw an IA8 texture on a rectangle with a shadow slightly offset to the bottom-right with additional texture offsets
 *
 * @param gfx the display list pointer
 * @param texture
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param rectLeft the x-coordinate of upper-left corner of rectangle
 * @param rectTop the y-coordinate of upper-left corner of rectangle
 * @param rectWidth rectangle width in texels
 * @param rectHeight rectangle height in texels
 * @param dsdx the change in s for each change in x (s5.10)
 * @param dtdy the change in t for each change in y (s5.10)
 * @param r // texture red
 * @param g // texture green
 * @param b // texture blue
 * @param a // texture alpha
 * @param masks specify the mask for the s axis
 * @param rects the texture coordinate s of upper-left corner of rectangle (s10.5)
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawTexRectIA8_DropShadowOffset(Gfx* gfx, TexturePtr texture, s16 textureWidth, s16 textureHeight,
                                         s16 rectLeft, s16 rectTop, s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy,
                                         s16 r, s16 g, s16 b, s16 a, s32 masks, s32 rects) {
    s16 dropShadowAlpha = a;

    if (a > 100) {
        dropShadowAlpha = 100;
    }

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, dropShadowAlpha);

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, textureWidth, textureHeight, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, (rectLeft + 2) * 4, (rectTop + 2) * 4, (rectLeft + rectWidth + 2) * 4,
                        (rectTop + rectHeight + 2) * 4, G_TX_RENDERTILE, rects, 0, dsdx, dtdy);

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, r, g, b, a);

    gSPTextureRectangle(gfx++, rectLeft * 4, rectTop * 4, (rectLeft + rectWidth) * 4, (rectTop + rectHeight) * 4,
                        G_TX_RENDERTILE, rects, 0, dsdx, dtdy);

    return gfx;
}

/**
 * Draw an I8 texture on a rectangle
 *
 * @param gfx the display list pointer
 * @param texture
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param rectLeft the x-coordinate of upper-left corner of rectangle
 * @param rectTop the y-coordinate of upper-left corner of rectangle
 * @param rectWidth rectangle width in texels
 * @param rectHeight rectangle height in texels
 * @param dsdx the change in s for each change in x (s5.10)
 * @param dtdy the change in t for each change in y (s5.10)
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawTexRectI8(Gfx* gfx, TexturePtr texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                       s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy) {
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_I, G_IM_SIZ_8b, textureWidth, textureHeight, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + rectWidth) << 2, (rectTop + rectHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, dsdx, dtdy);

    return gfx;
}

/**
 * Draw a 4b texture on a rectangle
 *
 * @param gfx the display list pointer
 * @param texture
 * @param fmt texture image format
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param rectLeft the x-coordinate of upper-left corner of rectangle
 * @param rectTop the y-coordinate of upper-left corner of rectangle
 * @param rectWidth rectangle width in texels
 * @param rectHeight rectangle height in texels
 * @param cms gives the clamp, wrap, and mirror flag for the s axis
 * @param masks specify the mask for the s axis
 * @param rects the texture coordinate s of upper-left corner of rectangle (s10.5)
 * @param dsdx the change in s for each change in x (s5.10)
 * @param dtdy the change in t for each change in y (s5.10)
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawTexRect4b(Gfx* gfx, TexturePtr texture, s32 fmt, s16 textureWidth, s16 textureHeight, s16 rectLeft,
                       s16 rectTop, s16 rectWidth, s16 rectHeight, s32 cms, s32 masks, s32 rects, u16 dsdx, u16 dtdy) {
    gDPLoadTextureBlock_4b(gfx++, texture, fmt, textureWidth, textureHeight, 0, cms, G_TX_NOMIRROR | G_TX_WRAP, masks,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + rectWidth) << 2, (rectTop + rectHeight) << 2,
                        G_TX_RENDERTILE, rects, 0, dsdx, dtdy);

    return gfx;
}

/**
 * Draw an I8 texture on a Quadrangle
 *
 * @param gfx the display list pointer
 * @param texture
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param point index of the first point to draw the Quadrangle
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawTexQuadIA8(Gfx* gfx, TexturePtr texture, s16 textureWidth, s16 textureHeight, u16 point) {
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, textureWidth, textureHeight, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gSP1Quadrangle(gfx++, point, point + 2, point + 3, point + 1, 0);

    return gfx;
}

/**
 * Draw a 4b texture on a Quadrangle
 *
 * @param gfx the display list pointer
 * @param texture
 * @param fmt texture image format
 * @param textureWidth texture image width in texels
 * @param textureHeight texture image height in texels
 * @param point index of the first point to draw the Quadrangle
 * @return Gfx* the display list pointer
 */
Gfx* Gfx_DrawTexQuad4b(Gfx* gfx, TexturePtr texture, s32 fmt, s16 textureWidth, s16 textureHeight, u16 point) {
    gDPLoadTextureBlock_4b(gfx++, texture, fmt, textureWidth, textureHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSP1Quadrangle(gfx++, point, point + 2, point + 3, point + 1, 0);

    return gfx;
}

// Total number of non-minigame-perfect action quads
#define ACTION_QUAD_BASE_COUNT 11

s16 sActionVtxPosX[ACTION_QUAD_BASE_COUNT] = {
    -14, // A Button
    -14, // A Button Background
    -24, // A Button Do-Action
    -8,  // Three-Day Clock's Star (for the Minute Tracker)
    -12, // Three-Day Clock's Sun (for the Day-Time Hours Tracker)
    -12, // Three-Day Clock's Moon (for the Night-Time Hours Tracker)
    -7,  // Three-Day Clock's Hour Digit Above the Sun
    -8,  // Three-Day Clock's Hour Digit Above the Sun
    -7,  // Three-Day Clock's Hour Digit Above the Moon
    -8,  // Three-Day Clock's Hour Digit Above the Moon
    -12, // Minigame Countdown Textures
};

s16 sActionVtxWidths[ACTION_QUAD_BASE_COUNT] = {
    28, // A Button
    28, // A Button Background
    48, // A Button Do-Action
    16, // Three-Day Clock's Star (for the Minute Tracker)
    24, // Three-Day Clock's Sun (for the Day-Time Hours Tracker)
    24, // Three-Day Clock's Moon (for the Night-Time Hours Tracker)
    16, // Three-Day Clock's Hour Digit Above the Sun
    16, // Three-Day Clock's Hour Digit Above the Sun
    16, // Three-Day Clock's Hour Digit Above the Moon
    16, // Three-Day Clock's Hour Digit Above the Moon
    24, // Minigame Countdown Textures
};

s16 sActionVtxPosY[ACTION_QUAD_BASE_COUNT] = {
    14,  // A Button
    14,  // A Button Background
    8,   // A Button Do-Action
    24,  // Three-Day Clock's Star (for the Minute Tracker)
    -82, // Three-Day Clock's Sun (for the Day-Time Hours Tracker)
    -82, // Three-Day Clock's Moon (for the Night-Time Hours Tracker)
    58,  // Three-Day Clock's Hour Digit Above the Sun
    59,  // Three-Day Clock's Hour Digit Above the Sun
    58,  // Three-Day Clock's Hour Digit Above the Moon
    59,  // Three-Day Clock's Hour Digit Above the Moon
    32,  // Minigame Countdown Textures
};

s16 sActionVtxHeights[ACTION_QUAD_BASE_COUNT] = {
    28, // A Button
    28, // A Button Background
    16, // A Button Do-Action
    16, // Three-Day Clock's Star (for the Minute Tracker)
    24, // Three-Day Clock's Sun (for the Day-Time Hours Tracker)
    24, // Three-Day Clock's Moon (for the Night-Time Hours Tracker)
    11, // Three-Day Clock's Hour Digit Above the Sun
    11, // Three-Day Clock's Hour Digit Above the Sun
    11, // Three-Day Clock's Hour Digit Above the Moon
    11, // Three-Day Clock's Hour Digit Above the Moon
    32, // Minigame Countdown Textures
};

#define PERFECT_LETTERS_VTX_WIDTH 32
#define PERFECT_LETTERS_VTX_HEIGHT 33

// Used for PERFECT_LETTERS_TYPE_1 and only part of PERFECT_LETTERS_TYPE_3
// Both PERFECT_LETTERS_TYPE_2 and PERFECT_LETTERS_TYPE_2 have (0, 0) as the center for all letters
s16 sPerfectLettersCenterX[PERFECT_LETTERS_NUM_LETTERS] = {
    -61,  // P
    -45,  // E
    29,   // R
    104,  // F
    -117, // E
    -42,  // C
    32,   // T
    55,   // !
};

s16 sPerfectLettersCenterY[PERFECT_LETTERS_NUM_LETTERS] = {
    1,   // P
    -70, // E
    -99, // R
    -70, // F
    71,  // E
    101, // C
    72,  // T
    1,   // !
};

/**
 * interfaceCtx->actionVtx[0]   -> A Button
 * interfaceCtx->actionVtx[4]   -> A Button Shadow
 * interfaceCtx->actionVtx[8]   -> A Button Do-Action
 * interfaceCtx->actionVtx[12]  -> Three-Day Clock's Star (for the Minute Tracker)
 * interfaceCtx->actionVtx[16]  -> Three-Day Clock's Sun (for the Day Hours Tracker)
 * interfaceCtx->actionVtx[20]  -> Three-Day Clock's Moon (for the Night Hours Tracker)
 * interfaceCtx->actionVtx[24]  -> Three-Day Clock's Hour Digit Above the Sun (uses 8 vertices)
 * interfaceCtx->actionVtx[32]  -> Three-Day Clock's Hour Digit Above the Moon (uses 8 vertices)
 * interfaceCtx->actionVtx[40]  -> Minigame Countdown Textures
 * interfaceCtx->actionVtx[44]  -> Minigame Perfect Letter P Shadow
 * interfaceCtx->actionVtx[48]  -> Minigame Perfect Letter E Shadow
 * interfaceCtx->actionVtx[52]  -> Minigame Perfect Letter R Shadow
 * interfaceCtx->actionVtx[56]  -> Minigame Perfect Letter F Shadow
 * interfaceCtx->actionVtx[60]  -> Minigame Perfect Letter E Shadow
 * interfaceCtx->actionVtx[64]  -> Minigame Perfect Letter C Shadow
 * interfaceCtx->actionVtx[68]  -> Minigame Perfect Letter T Shadow
 * interfaceCtx->actionVtx[72]  -> Minigame Perfect Letter ! Shadow
 * interfaceCtx->actionVtx[76]  -> Minigame Perfect Letter P Colored
 * interfaceCtx->actionVtx[80]  -> Minigame Perfect Letter E Colored
 * interfaceCtx->actionVtx[84]  -> Minigame Perfect Letter R Colored
 * interfaceCtx->actionVtx[88]  -> Minigame Perfect Letter F Colored
 * interfaceCtx->actionVtx[92]  -> Minigame Perfect Letter E Colored
 * interfaceCtx->actionVtx[96]  -> Minigame Perfect Letter C Colored
 * interfaceCtx->actionVtx[100] -> Minigame Perfect Letter T Colored
 * interfaceCtx->actionVtx[104] -> Minigame Perfect Letter ! Colored
 */

#define BEATING_HEART_VTX_X -8
#define BEATING_HEART_VTX_Y -8
#define BEATING_HEART_VTX_WIDTH 16

void Interface_SetVertices(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 i;
    s16 j;
    s16 k;
    s16 shadowOffset;

    play->interfaceCtx.actionVtx =
        GRAPH_ALLOC(play->state.gfxCtx, (ACTION_QUAD_BASE_COUNT + (2 * PERFECT_LETTERS_NUM_LETTERS)) * 4 * sizeof(Vtx));

    // Loop over all non-minigame perfect vertices
    // where (i) is the actionVtx index, (k) is the iterator
    for (k = 0, i = 0; i < (ACTION_QUAD_BASE_COUNT * 4); i += 4, k++) {
        // Left vertices x Pos
        interfaceCtx->actionVtx[i + 0].v.ob[0] = interfaceCtx->actionVtx[i + 2].v.ob[0] = sActionVtxPosX[k];

        // Right vertices x Pos
        interfaceCtx->actionVtx[i + 1].v.ob[0] = interfaceCtx->actionVtx[i + 3].v.ob[0] =
            interfaceCtx->actionVtx[i + 0].v.ob[0] + sActionVtxWidths[k];

        // Top vertices y Pos
        interfaceCtx->actionVtx[i + 0].v.ob[1] = interfaceCtx->actionVtx[i + 1].v.ob[1] = sActionVtxPosY[k];

        // Bottom vertices y Pos
        interfaceCtx->actionVtx[i + 2].v.ob[1] = interfaceCtx->actionVtx[i + 3].v.ob[1] =
            interfaceCtx->actionVtx[i + 0].v.ob[1] - sActionVtxHeights[k];

        // All vertices z Pos
        interfaceCtx->actionVtx[i + 0].v.ob[2] = interfaceCtx->actionVtx[i + 1].v.ob[2] =
            interfaceCtx->actionVtx[i + 2].v.ob[2] = interfaceCtx->actionVtx[i + 3].v.ob[2] = 0;

        // Unused flag
        interfaceCtx->actionVtx[i + 0].v.flag = interfaceCtx->actionVtx[i + 1].v.flag =
            interfaceCtx->actionVtx[i + 2].v.flag = interfaceCtx->actionVtx[i + 3].v.flag = 0;

        // Left and Top texture coordinates
        interfaceCtx->actionVtx[i + 0].v.tc[0] = interfaceCtx->actionVtx[i + 0].v.tc[1] =
            interfaceCtx->actionVtx[i + 1].v.tc[1] = interfaceCtx->actionVtx[i + 2].v.tc[0] = 0;

        // Right vertices texture coordinates
        interfaceCtx->actionVtx[i + 1].v.tc[0] = interfaceCtx->actionVtx[i + 3].v.tc[0] = sActionVtxWidths[k] << 5;

        // Bottom vertices texture coordinates
        interfaceCtx->actionVtx[i + 2].v.tc[1] = interfaceCtx->actionVtx[i + 3].v.tc[1] = sActionVtxHeights[k] << 5;

        // Set color
        interfaceCtx->actionVtx[i + 0].v.cn[0] = interfaceCtx->actionVtx[i + 1].v.cn[0] =
            interfaceCtx->actionVtx[i + 2].v.cn[0] = interfaceCtx->actionVtx[i + 3].v.cn[0] =
                interfaceCtx->actionVtx[i + 0].v.cn[1] = interfaceCtx->actionVtx[i + 1].v.cn[1] =
                    interfaceCtx->actionVtx[i + 2].v.cn[1] = interfaceCtx->actionVtx[i + 3].v.cn[1] =
                        interfaceCtx->actionVtx[i + 0].v.cn[2] = interfaceCtx->actionVtx[i + 1].v.cn[2] =
                            interfaceCtx->actionVtx[i + 2].v.cn[2] = interfaceCtx->actionVtx[i + 3].v.cn[2] = 255;

        // Set alpha
        interfaceCtx->actionVtx[i + 0].v.cn[3] = interfaceCtx->actionVtx[i + 1].v.cn[3] =
            interfaceCtx->actionVtx[i + 2].v.cn[3] = interfaceCtx->actionVtx[i + 3].v.cn[3] = 255;
    }

    // A button right and top texture coordinates
    interfaceCtx->actionVtx[1].v.tc[0] = interfaceCtx->actionVtx[3].v.tc[0] = interfaceCtx->actionVtx[2].v.tc[1] =
        interfaceCtx->actionVtx[3].v.tc[1] = 32 << 5;

    // A button background right and top texture coordinates
    interfaceCtx->actionVtx[5].v.tc[0] = interfaceCtx->actionVtx[7].v.tc[0] = interfaceCtx->actionVtx[6].v.tc[1] =
        interfaceCtx->actionVtx[7].v.tc[1] = 32 << 5;

    // Loop over vertices for the minigame-perfect letters
    // Outer loop is to loop over 2 sets of letters: shadowed letters (j = 0) and colored letters (j = 1)
    for (j = 0, shadowOffset = 2; j < 2; j++, shadowOffset -= 2) {
        // Inner loop is to loop over letters (k) and actionVtx index (i)
        for (k = 0; k < PERFECT_LETTERS_NUM_LETTERS; k++, i += 4) {
            if ((interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_1) ||
                ((interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_3) &&
                 (interfaceCtx->perfectLettersState[0] == PERFECT_LETTERS_STATE_EXIT))) {
                // Left vertices x Pos
                interfaceCtx->actionVtx[i + 0].v.ob[0] = interfaceCtx->actionVtx[i + 2].v.ob[0] =
                    -((sPerfectLettersCenterX[k] - shadowOffset) + 16);

                // Right vertices x Pos
                interfaceCtx->actionVtx[i + 1].v.ob[0] = interfaceCtx->actionVtx[i + 3].v.ob[0] =
                    interfaceCtx->actionVtx[i + 0].v.ob[0] + PERFECT_LETTERS_VTX_WIDTH;

                // Top vertices y Pos
                interfaceCtx->actionVtx[i + 0].v.ob[1] = interfaceCtx->actionVtx[i + 1].v.ob[1] =
                    (sPerfectLettersCenterY[k] - shadowOffset) + 16;

                // Bottom vertices y Pos
                interfaceCtx->actionVtx[i + 2].v.ob[1] = interfaceCtx->actionVtx[i + 3].v.ob[1] =
                    interfaceCtx->actionVtx[i + 0].v.ob[1] - PERFECT_LETTERS_VTX_HEIGHT;

            } else if ((interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_2) ||
                       (interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_3)) {
                // Left vertices x Pos
                interfaceCtx->actionVtx[i + 0].v.ob[0] = interfaceCtx->actionVtx[i + 2].v.ob[0] =
                    -(interfaceCtx->perfectLettersOffsetX[k] - shadowOffset + 16);

                // Right vertices x Pos
                interfaceCtx->actionVtx[i + 1].v.ob[0] = interfaceCtx->actionVtx[i + 3].v.ob[0] =
                    interfaceCtx->actionVtx[i + 0].v.ob[0] + PERFECT_LETTERS_VTX_WIDTH;

                // Top vertices y Pos
                interfaceCtx->actionVtx[i + 0].v.ob[1] = interfaceCtx->actionVtx[i + 1].v.ob[1] = 16 - shadowOffset;

                // Bottom vertices y Pos
                interfaceCtx->actionVtx[i + 2].v.ob[1] = interfaceCtx->actionVtx[i + 3].v.ob[1] =
                    interfaceCtx->actionVtx[i + 0].v.ob[1] - PERFECT_LETTERS_VTX_HEIGHT;

            } else {
                // Left vertices x Pos
                interfaceCtx->actionVtx[i + 0].v.ob[0] = interfaceCtx->actionVtx[i + 2].v.ob[0] = -(216 - shadowOffset);

                // Right vertices x Pos
                interfaceCtx->actionVtx[i + 1].v.ob[0] = interfaceCtx->actionVtx[i + 3].v.ob[0] =
                    interfaceCtx->actionVtx[i + 0].v.ob[0] + PERFECT_LETTERS_VTX_WIDTH;

                // Top vertices y Pos
                interfaceCtx->actionVtx[i + 0].v.ob[1] = interfaceCtx->actionVtx[i + 1].v.ob[1] = 24 - shadowOffset;

                // Bottom vertices y Pos
                interfaceCtx->actionVtx[i + 2].v.ob[1] = interfaceCtx->actionVtx[i + 3].v.ob[1] =
                    interfaceCtx->actionVtx[i + 0].v.ob[1] - PERFECT_LETTERS_VTX_HEIGHT;
            }

            // All vertices z Pos
            interfaceCtx->actionVtx[i + 0].v.ob[2] = interfaceCtx->actionVtx[i + 1].v.ob[2] =
                interfaceCtx->actionVtx[i + 2].v.ob[2] = interfaceCtx->actionVtx[i + 3].v.ob[2] = 0;

            // Unused flag
            interfaceCtx->actionVtx[i + 0].v.flag = interfaceCtx->actionVtx[i + 1].v.flag =
                interfaceCtx->actionVtx[i + 2].v.flag = interfaceCtx->actionVtx[i + 3].v.flag = 0;

            // Left and Top texture coordinates
            interfaceCtx->actionVtx[i + 0].v.tc[0] = interfaceCtx->actionVtx[i + 0].v.tc[1] =
                interfaceCtx->actionVtx[i + 1].v.tc[1] = interfaceCtx->actionVtx[i + 2].v.tc[0] = 0;

            // Right vertices texture coordinates
            interfaceCtx->actionVtx[i + 1].v.tc[0] = interfaceCtx->actionVtx[i + 3].v.tc[0] = PERFECT_LETTERS_VTX_WIDTH
                                                                                              << 5;

            // Bottom vertices texture coordinates
            interfaceCtx->actionVtx[i + 2].v.tc[1] = interfaceCtx->actionVtx[i + 3].v.tc[1] = PERFECT_LETTERS_VTX_HEIGHT
                                                                                              << 5;

            // Set color
            interfaceCtx->actionVtx[i + 0].v.cn[0] = interfaceCtx->actionVtx[i + 1].v.cn[0] =
                interfaceCtx->actionVtx[i + 2].v.cn[0] = interfaceCtx->actionVtx[i + 3].v.cn[0] =
                    interfaceCtx->actionVtx[i + 0].v.cn[1] = interfaceCtx->actionVtx[i + 1].v.cn[1] =
                        interfaceCtx->actionVtx[i + 2].v.cn[1] = interfaceCtx->actionVtx[i + 3].v.cn[1] =
                            interfaceCtx->actionVtx[i + 0].v.cn[2] = interfaceCtx->actionVtx[i + 1].v.cn[2] =
                                interfaceCtx->actionVtx[i + 2].v.cn[2] = interfaceCtx->actionVtx[i + 3].v.cn[2] = 255;

            // Set alpha
            interfaceCtx->actionVtx[i + 0].v.cn[3] = interfaceCtx->actionVtx[i + 1].v.cn[3] =
                interfaceCtx->actionVtx[i + 2].v.cn[3] = interfaceCtx->actionVtx[i + 3].v.cn[3] = 255;
        }
    }

    // Beating Hearts Vertices
    interfaceCtx->beatingHeartVtx = GRAPH_ALLOC(play->state.gfxCtx, 4 * sizeof(Vtx));

    // Left vertices x Pos
    interfaceCtx->beatingHeartVtx[0].v.ob[0] = interfaceCtx->beatingHeartVtx[2].v.ob[0] = BEATING_HEART_VTX_X;

    // Right vertices x Pos
    interfaceCtx->beatingHeartVtx[1].v.ob[0] = interfaceCtx->beatingHeartVtx[3].v.ob[0] =
        BEATING_HEART_VTX_X + BEATING_HEART_VTX_WIDTH;

    // Top vertices y Pos
    interfaceCtx->beatingHeartVtx[0].v.ob[1] = interfaceCtx->beatingHeartVtx[1].v.ob[1] =
        BEATING_HEART_VTX_Y + BEATING_HEART_VTX_WIDTH;

    // Bottom vertices y Pos
    interfaceCtx->beatingHeartVtx[2].v.ob[1] = interfaceCtx->beatingHeartVtx[3].v.ob[1] = BEATING_HEART_VTX_Y;

    // All vertices z Pos
    interfaceCtx->beatingHeartVtx[0].v.ob[2] = interfaceCtx->beatingHeartVtx[1].v.ob[2] =
        interfaceCtx->beatingHeartVtx[2].v.ob[2] = interfaceCtx->beatingHeartVtx[3].v.ob[2] = 0;

    // unused flag
    interfaceCtx->beatingHeartVtx[0].v.flag = interfaceCtx->beatingHeartVtx[1].v.flag =
        interfaceCtx->beatingHeartVtx[2].v.flag = interfaceCtx->beatingHeartVtx[3].v.flag = 0;

    // Texture Coordinates
    interfaceCtx->beatingHeartVtx[0].v.tc[0] = interfaceCtx->beatingHeartVtx[0].v.tc[1] =
        interfaceCtx->beatingHeartVtx[1].v.tc[1] = interfaceCtx->beatingHeartVtx[2].v.tc[0] = 0;
    interfaceCtx->beatingHeartVtx[1].v.tc[0] = interfaceCtx->beatingHeartVtx[2].v.tc[1] =
        interfaceCtx->beatingHeartVtx[3].v.tc[0] = interfaceCtx->beatingHeartVtx[3].v.tc[1] =
            BEATING_HEART_VTX_WIDTH << 5;

    // Set color
    interfaceCtx->beatingHeartVtx[0].v.cn[0] = interfaceCtx->beatingHeartVtx[1].v.cn[0] =
        interfaceCtx->beatingHeartVtx[2].v.cn[0] = interfaceCtx->beatingHeartVtx[3].v.cn[0] =
            interfaceCtx->beatingHeartVtx[0].v.cn[1] = interfaceCtx->beatingHeartVtx[1].v.cn[1] =
                interfaceCtx->beatingHeartVtx[2].v.cn[1] = interfaceCtx->beatingHeartVtx[3].v.cn[1] =
                    interfaceCtx->beatingHeartVtx[0].v.cn[2] = interfaceCtx->beatingHeartVtx[1].v.cn[2] =
                        interfaceCtx->beatingHeartVtx[2].v.cn[2] = interfaceCtx->beatingHeartVtx[3].v.cn[2] =
                            interfaceCtx->beatingHeartVtx[0].v.cn[3] = interfaceCtx->beatingHeartVtx[1].v.cn[3] =
                                interfaceCtx->beatingHeartVtx[2].v.cn[3] = interfaceCtx->beatingHeartVtx[3].v.cn[3] =
                                    255;
}

s32 sPostmanTimerInputBtnAPressed = false;

void Interface_PostmanTimerCallback(s32 arg0) {
    s32 btnAPressed;

    func_80175E68(&sPostmanTimerInput[0], 0);
    btnAPressed = CHECK_BTN_ALL(sPostmanTimerInput[0].cur.button, BTN_A);
    if ((btnAPressed != sPostmanTimerInputBtnAPressed) && btnAPressed) {
        gSaveContext.postmanTimerStopOsTime = osGetTime();
        gSaveContext.timerStates[TIMER_ID_POSTMAN] = TIMER_STATE_POSTMAN_STOP;
    }

    sPostmanTimerInputBtnAPressed = btnAPressed;
}

void Interface_StartTimer(s16 timerId, s16 seconds) {
    gSaveContext.timerX[timerId] = 115;
    gSaveContext.timerY[timerId] = 80;

    sEnvTimerActive = false;

    gSaveContext.timerCurTimes[timerId] = SECONDS_TO_TIMER(seconds);
    gSaveContext.timerTimeLimits[timerId] = gSaveContext.timerCurTimes[timerId];

    if (gSaveContext.timerCurTimes[timerId] != SECONDS_TO_TIMER(0)) {
        gSaveContext.timerDirections[timerId] = TIMER_COUNT_DOWN;
    } else {
        gSaveContext.timerDirections[timerId] = TIMER_COUNT_UP;
    }

    gSaveContext.timerStates[timerId] = TIMER_STATE_START;
}

void Interface_StartPostmanTimer(s16 seconds, s16 bunnyHoodState) {
    gSaveContext.timerX[TIMER_ID_POSTMAN] = 115;
    gSaveContext.timerY[TIMER_ID_POSTMAN] = 80;

    sPostmanBunnyHoodState = bunnyHoodState;

    gSaveContext.timerCurTimes[TIMER_ID_POSTMAN] = SECONDS_TO_TIMER(seconds);
    gSaveContext.timerTimeLimits[TIMER_ID_POSTMAN] = gSaveContext.timerCurTimes[TIMER_ID_POSTMAN];

    if (gSaveContext.timerCurTimes[TIMER_ID_POSTMAN] != SECONDS_TO_TIMER(0)) {
        gSaveContext.timerDirections[TIMER_ID_POSTMAN] = TIMER_COUNT_DOWN;
    } else {
        gSaveContext.timerDirections[TIMER_ID_POSTMAN] = TIMER_COUNT_UP;
    }

    gSaveContext.timerStates[TIMER_ID_POSTMAN] = TIMER_STATE_POSTMAN_START;
    gSaveContext.timerStopTimes[TIMER_ID_POSTMAN] = SECONDS_TO_TIMER(0);
    gSaveContext.timerPausedOsTimes[TIMER_ID_POSTMAN] = 0;
}

// Unused, goron race actually uses TIMER_ID_MINIGAME_2
void Interface_StartGoronRaceTimer(s32 arg0) {
    if (gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] != TIMER_STATE_OFF) {
        // Goron race started
        if (CHECK_EVENTINF(EVENTINF_10)) {
            gSaveContext.timerCurTimes[TIMER_ID_GORON_RACE_UNUSED] = SECONDS_TO_TIMER_PRECISE(2, 39);
        } else {
            gSaveContext.timerCurTimes[TIMER_ID_GORON_RACE_UNUSED] = SECONDS_TO_TIMER_PRECISE(0, 1);
        }
    }
}

void Interface_StartBottleTimer(s16 seconds, s16 timerId) {
    gSaveContext.bottleTimerStates[timerId] = BOTTLE_TIMER_STATE_COUNTING;
    gSaveContext.bottleTimerCurTimes[timerId] = SECONDS_TO_TIMER(seconds);
    gSaveContext.bottleTimerTimeLimits[timerId] = gSaveContext.bottleTimerCurTimes[timerId];
    gSaveContext.bottleTimerStartOsTimes[timerId] = osGetTime();
    gSaveContext.bottleTimerPausedOsTimes[timerId] = 0;
    sBottleTimerPausedOsTime = 0;
}

u32 Interface_GetCompressedTimerDigits(s16 timerId) {
    u64 time;
    s16 timerArr[6];

    time = gSaveContext.timerCurTimes[timerId];

    // 6 minutes
    timerArr[0] = time / SECONDS_TO_TIMER(360);
    time -= timerArr[0] * SECONDS_TO_TIMER(360);

    // minutes
    timerArr[1] = time / SECONDS_TO_TIMER(60);
    time -= timerArr[1] * SECONDS_TO_TIMER(60);

    // 10 seconds
    timerArr[2] = time / SECONDS_TO_TIMER(10);
    time -= timerArr[2] * SECONDS_TO_TIMER(10);

    // seconds
    timerArr[3] = time / SECONDS_TO_TIMER(1);
    time -= timerArr[3] * SECONDS_TO_TIMER(1);

    // 100 milliseconds
    timerArr[4] = time / SECONDS_TO_TIMER_PRECISE(0, 10);
    time -= timerArr[4] * SECONDS_TO_TIMER_PRECISE(0, 10);

    // 10 milliseconds
    timerArr[5] = time;

    return (timerArr[0] << 0x14) | (timerArr[1] << 0x10) | (timerArr[2] << 0xC) | (timerArr[3] << 8) |
           (timerArr[4] << 4) | timerArr[5];
}

void Interface_NewDay(PlayState* play, s32 day) {
    s32 pad;
    s16 i = day - 1;

    // i is used to store dayMinusOne
    if ((i < 0) || (i >= 3)) {
        i = 0;
    }

    // Loads day number from week_static for the three-day clock
    DmaMgr_SendRequest0((u32)play->interfaceCtx.doActionSegment + 0x780,
                        (u32)SEGMENT_ROM_START(week_static) + i * 0x510, 0x510);

    // i is used to store sceneId
    for (i = 0; i < ARRAY_COUNT(gSaveContext.save.permanentSceneFlags); i++) {
        gSaveContext.save.permanentSceneFlags[i].chest = gSaveContext.cycleSceneFlags[i].chest;
        gSaveContext.save.permanentSceneFlags[i].switch0 = gSaveContext.cycleSceneFlags[i].switch0;
        gSaveContext.save.permanentSceneFlags[i].switch1 = gSaveContext.cycleSceneFlags[i].switch1;
        gSaveContext.save.permanentSceneFlags[i].clearedRoom = gSaveContext.cycleSceneFlags[i].clearedRoom;
        gSaveContext.save.permanentSceneFlags[i].collectible = gSaveContext.cycleSceneFlags[i].collectible;
    }
}

void Interface_SetHudVisibility(u16 hudVisibility) {
    if (gSaveContext.hudVisibility != hudVisibility) {
        gSaveContext.hudVisibility = hudVisibility;
        gSaveContext.nextHudVisibility = hudVisibility;
        gSaveContext.hudVisibilityTimer = 1;
    }
}

/**
 * Sets the button alphas to be dimmed for disabled buttons, or to the requested alpha for non-disabled buttons
 */
void Interface_UpdateButtonAlphasByStatus(PlayState* play, s16 risingAlpha) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    if ((gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) || (gSaveContext.unk_1015 == ITEM_NONE)) {
        if (interfaceCtx->bAlpha != 70) {
            interfaceCtx->bAlpha = 70;
        }
    } else {
        if (interfaceCtx->bAlpha != 255) {
            interfaceCtx->bAlpha = risingAlpha;
        }
    }

    if (gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] == BTN_DISABLED) {
        if (interfaceCtx->cLeftAlpha != 70) {
            interfaceCtx->cLeftAlpha = 70;
        }
    } else {
        if (interfaceCtx->cLeftAlpha != 255) {
            interfaceCtx->cLeftAlpha = risingAlpha;
        }
    }

    if (gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] == BTN_DISABLED) {
        if (interfaceCtx->cDownAlpha != 70) {
            interfaceCtx->cDownAlpha = 70;
        }
    } else {
        if (interfaceCtx->cDownAlpha != 255) {
            interfaceCtx->cDownAlpha = risingAlpha;
        }
    }

    if (gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] == BTN_DISABLED) {
        if (interfaceCtx->cRightAlpha != 70) {
            interfaceCtx->cRightAlpha = 70;
        }
    } else {
        if (interfaceCtx->cRightAlpha != 255) {
            interfaceCtx->cRightAlpha = risingAlpha;
        }
    }

    if (gSaveContext.buttonStatus[EQUIP_SLOT_A] == BTN_DISABLED) {
        if (interfaceCtx->aAlpha != 70) {
            interfaceCtx->aAlpha = 70;
        }
    } else {
        if (interfaceCtx->aAlpha != 255) {
            interfaceCtx->aAlpha = risingAlpha;
        }
    }
}

/**
 * Lower button alphas on the HUD to the requested value
 * If (gSaveContext.hudVisibilityForceButtonAlphasByStatus), then instead update button alphas
 * depending on button status
 */
void Interface_UpdateButtonAlphas(PlayState* play, s16 dimmingAlpha, s16 risingAlpha) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    if (gSaveContext.hudVisibilityForceButtonAlphasByStatus) {
        Interface_UpdateButtonAlphasByStatus(play, risingAlpha);
        return;
    }

    if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
        interfaceCtx->bAlpha = dimmingAlpha;
    }

    if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
        interfaceCtx->aAlpha = dimmingAlpha;
    }

    if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
        interfaceCtx->cLeftAlpha = dimmingAlpha;
    }

    if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
        interfaceCtx->cDownAlpha = dimmingAlpha;
    }

    if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
        interfaceCtx->cRightAlpha = dimmingAlpha;
    }
}

void Interface_UpdateHudAlphas(PlayState* play, s16 dimmingAlpha) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 risingAlpha = 255 - dimmingAlpha;

    switch (gSaveContext.nextHudVisibility) {
        case HUD_VISIBILITY_NONE:
        case HUD_VISIBILITY_NONE_ALT:
        case HUD_VISIBILITY_B:
            if (gSaveContext.nextHudVisibility == HUD_VISIBILITY_B) {
                if (interfaceCtx->bAlpha != 255) {
                    interfaceCtx->bAlpha = risingAlpha;
                }
            } else {
                if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
                    interfaceCtx->bAlpha = dimmingAlpha;
                }
            }

            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            break;

        case HUD_VISIBILITY_HEARTS_WITH_OVERWRITE:
            // aAlpha is immediately overwritten in Interface_UpdateButtonAlphas
            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            Interface_UpdateButtonAlphas(play, dimmingAlpha, risingAlpha + 0);

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_A:
            if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
                interfaceCtx->bAlpha = dimmingAlpha;
            }

            // aAlpha is immediately overwritten below
            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE:
            Interface_UpdateButtonAlphas(play, dimmingAlpha, risingAlpha);

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            // aAlpha overwrites the value set in Interface_UpdateButtonAlphas
            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE:
            Interface_UpdateButtonAlphas(play, dimmingAlpha, risingAlpha);

            // aAlpha overwrites the value set in Interface_UpdateButtonAlphas
            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (play->sceneId == SCENE_SPOT00) {
                if (interfaceCtx->minimapAlpha < 170) {
                    interfaceCtx->minimapAlpha = risingAlpha;
                } else {
                    interfaceCtx->minimapAlpha = 170;
                }
            } else if (interfaceCtx->minimapAlpha != 255) {
                interfaceCtx->minimapAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_ALL_NO_MINIMAP_W_DISABLED:
            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            Interface_UpdateButtonAlphasByStatus(play, risingAlpha);

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_HEARTS_MAGIC:
            if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
                interfaceCtx->bAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_B_ALT:
            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if (interfaceCtx->bAlpha != 255) {
                interfaceCtx->bAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_HEARTS:
            if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
                interfaceCtx->bAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_A_B_MINIMAP:
            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if ((gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) || (gSaveContext.unk_1015 == ITEM_NONE)) {
                if (interfaceCtx->bAlpha != 70) {
                    interfaceCtx->bAlpha = 70;
                }
            } else {
                if (interfaceCtx->bAlpha != 255) {
                    interfaceCtx->bAlpha = risingAlpha;
                }
            }

            if (interfaceCtx->minimapAlpha != 255) {
                interfaceCtx->minimapAlpha = risingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            break;

        case HUD_VISIBILITY_HEARTS_MAGIC_WITH_OVERWRITE:
            Interface_UpdateButtonAlphas(play, dimmingAlpha, risingAlpha);

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            // aAlpha overwrites the value set in Interface_UpdateButtonAlphas
            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_HEARTS_MAGIC_C:
            if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
                interfaceCtx->bAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if (interfaceCtx->cLeftAlpha != 255) {
                interfaceCtx->cLeftAlpha = risingAlpha;
            }

            if (interfaceCtx->cDownAlpha != 255) {
                interfaceCtx->cDownAlpha = risingAlpha;
            }

            if (interfaceCtx->cRightAlpha != 255) {
                interfaceCtx->cRightAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_ALL_NO_MINIMAP:
            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if (interfaceCtx->bAlpha != 255) {
                interfaceCtx->bAlpha = risingAlpha;
            }

            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if (interfaceCtx->cLeftAlpha != 255) {
                interfaceCtx->cLeftAlpha = risingAlpha;
            }

            if (interfaceCtx->cDownAlpha != 255) {
                interfaceCtx->cDownAlpha = risingAlpha;
            }

            if (interfaceCtx->cRightAlpha != 255) {
                interfaceCtx->cRightAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_A_B_C:
            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            if (interfaceCtx->bAlpha != 255) {
                interfaceCtx->bAlpha = risingAlpha;
            }

            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if (interfaceCtx->cLeftAlpha != 255) {
                interfaceCtx->cLeftAlpha = risingAlpha;
            }

            if (interfaceCtx->cDownAlpha != 255) {
                interfaceCtx->cDownAlpha = risingAlpha;
            }

            if (interfaceCtx->cRightAlpha != 255) {
                interfaceCtx->cRightAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_B_MINIMAP:
            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            if (interfaceCtx->bAlpha != 255) {
                interfaceCtx->bAlpha = risingAlpha;
            }

            if (interfaceCtx->minimapAlpha != 255) {
                interfaceCtx->minimapAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_HEARTS_MAGIC_MINIMAP:
            if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
                interfaceCtx->bAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (interfaceCtx->minimapAlpha != 255) {
                interfaceCtx->minimapAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP:
            if ((interfaceCtx->bAlpha != 0) && (interfaceCtx->bAlpha > dimmingAlpha)) {
                interfaceCtx->bAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if (interfaceCtx->minimapAlpha != 255) {
                interfaceCtx->minimapAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_B_MAGIC:
            if ((interfaceCtx->aAlpha != 0) && (interfaceCtx->aAlpha > dimmingAlpha)) {
                interfaceCtx->aAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            if (interfaceCtx->bAlpha != 255) {
                interfaceCtx->bAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            break;

        case HUD_VISIBILITY_A_B:
            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if (interfaceCtx->bAlpha != 255) {
                interfaceCtx->bAlpha = risingAlpha;
            }

            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->minimapAlpha != 0) && (interfaceCtx->minimapAlpha > dimmingAlpha)) {
                interfaceCtx->minimapAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->magicAlpha != 0) && (interfaceCtx->magicAlpha > dimmingAlpha)) {
                interfaceCtx->magicAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->healthAlpha != 0) && (interfaceCtx->healthAlpha > dimmingAlpha)) {
                interfaceCtx->healthAlpha = dimmingAlpha;
            }

            break;

        case HUD_VISIBILITY_A_B_HEARTS_MAGIC_MINIMAP:
            if ((interfaceCtx->cLeftAlpha != 0) && (interfaceCtx->cLeftAlpha > dimmingAlpha)) {
                interfaceCtx->cLeftAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cDownAlpha != 0) && (interfaceCtx->cDownAlpha > dimmingAlpha)) {
                interfaceCtx->cDownAlpha = dimmingAlpha;
            }

            if ((interfaceCtx->cRightAlpha != 0) && (interfaceCtx->cRightAlpha > dimmingAlpha)) {
                interfaceCtx->cRightAlpha = dimmingAlpha;
            }

            if (interfaceCtx->bAlpha != 255) {
                interfaceCtx->bAlpha = risingAlpha;
            }

            if (interfaceCtx->aAlpha != 255) {
                interfaceCtx->aAlpha = risingAlpha;
            }

            if (interfaceCtx->minimapAlpha != 255) {
                interfaceCtx->minimapAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            break;
    }

    if ((play->roomCtx.curRoom.unk3 == 1) && (interfaceCtx->minimapAlpha >= 255)) {
        interfaceCtx->minimapAlpha = 255;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80110038.s")

void func_80111CB4(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80111CB4.s")

void Interface_SetSceneRestrictions(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 i = 0;
    u8 currentScene;

    do {
        currentScene = (u8)play->sceneId;
        if (currentScene == sRestrictionFlags[i].scene) {
            interfaceCtx->restrictions.hGauge = RESTRICTIONS_GET_HGAUGE(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.bButton = RESTRICTIONS_GET_B_BUTTON(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.aButton = RESTRICTIONS_GET_A_BUTTON(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.tradeItems = RESTRICTIONS_GET_TRADE_ITEMS(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.songOfTime = RESTRICTIONS_GET_SONG_OF_TIME(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.songOfDoubleTime = RESTRICTIONS_GET_SONG_OF_DOUBLE_TIME(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.invSongOfTime = RESTRICTIONS_GET_INV_SONG_OF_TIME(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.songOfSoaring = RESTRICTIONS_GET_SONG_OF_SOARING(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.songOfStorms = RESTRICTIONS_GET_SONG_OF_STORMS(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.masks = RESTRICTIONS_GET_MASKS(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.pictoBox = RESTRICTIONS_GET_PICTO_BOX(&sRestrictionFlags[i]);
            interfaceCtx->restrictions.all = RESTRICTIONS_GET_ALL(&sRestrictionFlags[i]);
            break;
        }
        i++;
    } while (sRestrictionFlags[i].scene != RESTRICTIONS_TABLE_END);
}

void Interface_Noop(void) {
}

void Interface_InitMinigame(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    gSaveContext.minigameStatus = MINIGAME_STATUS_ACTIVE;
    gSaveContext.minigameScore = 0;
    gSaveContext.minigameHiddenScore = 0;

    sHBAScoreTier = 0;
    interfaceCtx->minigamePoints = interfaceCtx->minigameHiddenPoints = interfaceCtx->minigameUnusedPoints = 0;

    interfaceCtx->minigameAmmo = 20;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/Interface_LoadItemIconImpl.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/Interface_LoadItemIcon.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80112C0C.s")

s16 sAmmoRefillCounts[] = { 5, 10, 20, 30 }; // Sticks, nuts, bombs
s16 sArrowRefillCounts[] = { 10, 30, 40, 50 };
s16 sBombchuRefillCounts[] = { 20, 10, 1, 5 };
s16 sRupeeRefillCounts[] = { 1, 5, 10, 20, 50, 100, 200 };

u8 Item_Give(PlayState* play, u8 item) {
    Player* player = GET_PLAYER(play);
    u8 i;
    u8 temp;
    u8 slot;

    slot = SLOT(item);
    if (item >= ITEM_STICKS_5) {
        slot = SLOT(sExtraItemBases[item - ITEM_STICKS_5]);
    }

    if (item == ITEM_SKULL_TOKEN) {
        //! @bug: Sets QUEST_QUIVER instead of QUEST_SKULL_TOKEN
        // Setting `QUEST_SKULL_TOKEN` will result in misplaced digits on the pause menu - Quest Status page.
        SET_QUEST_ITEM(item - ITEM_SKULL_TOKEN + QUEST_QUIVER);
        Inventory_IncrementSkullTokenCount(play->sceneId);
        return ITEM_NONE;

    } else if (item == ITEM_TINGLE_MAP) {
        return ITEM_NONE;

    } else if (item == ITEM_BOMBERS_NOTEBOOK) {
        SET_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK);
        return ITEM_NONE;

    } else if ((item == ITEM_HEART_PIECE_2) || (item == ITEM_HEART_PIECE)) {
        INCREMENT_QUEST_HEART_PIECE_COUNT;
        if (EQ_MAX_QUEST_HEART_PIECE_COUNT) {
            RESET_HEART_PIECE_COUNT;
            gSaveContext.save.playerData.healthCapacity += 0x10;
            gSaveContext.save.playerData.health += 0x10;
        }
        return ITEM_NONE;

    } else if (item == ITEM_HEART_CONTAINER) {
        gSaveContext.save.playerData.healthCapacity += 0x10;
        gSaveContext.save.playerData.health += 0x10;
        return ITEM_NONE;

    } else if ((item >= ITEM_SONG_SONATA) && (item <= ITEM_SONG_LULLABY_INTRO)) {
        SET_QUEST_ITEM(item - ITEM_SONG_SONATA + QUEST_SONG_SONATA);
        return ITEM_NONE;

    } else if ((item >= ITEM_SWORD_KOKIRI) && (item <= ITEM_SWORD_GILDED)) {
        SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, item - ITEM_SWORD_KOKIRI + EQUIP_VALUE_SWORD_KOKIRI);
        CUR_FORM_EQUIP(EQUIP_SLOT_B) = item;
        Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
        if (item == ITEM_SWORD_RAZOR) {
            gSaveContext.save.playerData.swordHealth = 100;
        }
        return ITEM_NONE;

    } else if ((item >= ITEM_SHIELD_HERO) && (item <= ITEM_SHIELD_MIRROR)) {
        if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SHIELD) != (u16)(item - ITEM_SHIELD_HERO + EQUIP_VALUE_SHIELD_HERO)) {
            SET_EQUIP_VALUE(EQUIP_TYPE_SHIELD, item - ITEM_SHIELD_HERO + EQUIP_VALUE_SHIELD_HERO);
            Player_SetEquipmentData(play, player);
            return ITEM_NONE;
        }
        return item;

    } else if ((item == ITEM_KEY_BOSS) || (item == ITEM_COMPASS) || (item == ITEM_DUNGEON_MAP)) {
        SET_DUNGEON_ITEM(item - ITEM_KEY_BOSS, gSaveContext.mapIndex);
        return ITEM_NONE;

    } else if (item == ITEM_KEY_SMALL) {
        if (DUNGEON_KEY_COUNT(gSaveContext.mapIndex) < 0) {
            DUNGEON_KEY_COUNT(gSaveContext.mapIndex) = 1;
            return ITEM_NONE;
        } else {
            DUNGEON_KEY_COUNT(gSaveContext.mapIndex)++;
            return ITEM_NONE;
        }

    } else if ((item == ITEM_QUIVER_30) || (item == ITEM_BOW)) {
        if (CUR_UPG_VALUE(UPG_QUIVER) == 0) {
            Inventory_ChangeUpgrade(UPG_QUIVER, 1);
            INV_CONTENT(ITEM_BOW) = ITEM_BOW;
            AMMO(ITEM_BOW) = CAPACITY(UPG_QUIVER, 1);
            return ITEM_NONE;
        } else {
            AMMO(ITEM_BOW)++;
            if (AMMO(ITEM_BOW) > (s8)CUR_CAPACITY(UPG_QUIVER)) {
                AMMO(ITEM_BOW) = CUR_CAPACITY(UPG_QUIVER);
            }
        }

    } else if (item == ITEM_QUIVER_40) {
        Inventory_ChangeUpgrade(UPG_QUIVER, 2);
        INV_CONTENT(ITEM_BOW) = ITEM_BOW;
        AMMO(ITEM_BOW) = CAPACITY(UPG_QUIVER, 2);
        return ITEM_NONE;

    } else if (item == ITEM_QUIVER_50) {
        Inventory_ChangeUpgrade(UPG_QUIVER, 3);
        INV_CONTENT(ITEM_BOW) = ITEM_BOW;
        AMMO(ITEM_BOW) = CAPACITY(UPG_QUIVER, 3);
        return ITEM_NONE;

    } else if (item == ITEM_BOMB_BAG_20) {
        if (CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
            Inventory_ChangeUpgrade(UPG_BOMB_BAG, 1);
            INV_CONTENT(ITEM_BOMB) = ITEM_BOMB;
            AMMO(ITEM_BOMB) = CAPACITY(UPG_BOMB_BAG, 1);
            return ITEM_NONE;

        } else {
            AMMO(ITEM_BOMB)++;
            if (AMMO(ITEM_BOMB) > CUR_CAPACITY(UPG_BOMB_BAG)) {
                AMMO(ITEM_BOMB) = CUR_CAPACITY(UPG_BOMB_BAG);
            }
        }

    } else if (item == ITEM_BOMB_BAG_30) {
        Inventory_ChangeUpgrade(UPG_BOMB_BAG, 2);
        INV_CONTENT(ITEM_BOMB) = ITEM_BOMB;
        AMMO(ITEM_BOMB) = CAPACITY(UPG_BOMB_BAG, 2);
        return ITEM_NONE;

    } else if (item == ITEM_BOMB_BAG_40) {
        Inventory_ChangeUpgrade(UPG_BOMB_BAG, 3);
        INV_CONTENT(ITEM_BOMB) = ITEM_BOMB;
        AMMO(ITEM_BOMB) = CAPACITY(UPG_BOMB_BAG, 3);
        return ITEM_NONE;

    } else if (item == ITEM_WALLET_ADULT) {
        Inventory_ChangeUpgrade(UPG_WALLET, 1);
        return ITEM_NONE;

    } else if (item == ITEM_WALLET_GIANT) {
        Inventory_ChangeUpgrade(UPG_WALLET, 2);
        return ITEM_NONE;

    } else if (item == ITEM_STICK_UPGRADE_20) {
        if (INV_CONTENT(ITEM_STICK) != ITEM_STICK) {
            INV_CONTENT(ITEM_STICK) = ITEM_STICK;
        }
        Inventory_ChangeUpgrade(UPG_STICKS, 2);
        AMMO(ITEM_STICK) = CAPACITY(UPG_STICKS, 2);
        return ITEM_NONE;

    } else if (item == ITEM_STICK_UPGRADE_30) {
        if (INV_CONTENT(ITEM_STICK) != ITEM_STICK) {
            INV_CONTENT(ITEM_STICK) = ITEM_STICK;
        }
        Inventory_ChangeUpgrade(UPG_STICKS, 3);
        AMMO(ITEM_STICK) = CAPACITY(UPG_STICKS, 3);
        return ITEM_NONE;

    } else if (item == ITEM_NUT_UPGRADE_30) {
        if (INV_CONTENT(ITEM_NUT) != ITEM_NUT) {
            INV_CONTENT(ITEM_NUT) = ITEM_NUT;
        }
        Inventory_ChangeUpgrade(UPG_NUTS, 2);
        AMMO(ITEM_NUT) = CAPACITY(UPG_NUTS, 2);
        return ITEM_NONE;

    } else if (item == ITEM_NUT_UPGRADE_40) {
        if (INV_CONTENT(ITEM_NUT) != ITEM_NUT) {
            INV_CONTENT(ITEM_NUT) = ITEM_NUT;
        }
        Inventory_ChangeUpgrade(UPG_NUTS, 3);
        AMMO(ITEM_NUT) = CAPACITY(UPG_NUTS, 3);
        return ITEM_NONE;

    } else if (item == ITEM_STICK) {
        if (INV_CONTENT(ITEM_STICK) != ITEM_STICK) {
            Inventory_ChangeUpgrade(UPG_STICKS, 1);
            AMMO(ITEM_STICK) = 1;
        } else {
            AMMO(ITEM_STICK)++;
            if (AMMO(ITEM_STICK) > CUR_CAPACITY(UPG_STICKS)) {
                AMMO(ITEM_STICK) = CUR_CAPACITY(UPG_STICKS);
            }
        }

    } else if ((item == ITEM_STICKS_5) || (item == ITEM_STICKS_10)) {
        if (INV_CONTENT(ITEM_STICK) != ITEM_STICK) {
            Inventory_ChangeUpgrade(UPG_STICKS, 1);
            AMMO(ITEM_STICK) = sAmmoRefillCounts[item - ITEM_STICKS_5];
        } else {
            AMMO(ITEM_STICK) += sAmmoRefillCounts[item - ITEM_STICKS_5];
            if (AMMO(ITEM_STICK) > CUR_CAPACITY(UPG_STICKS)) {
                AMMO(ITEM_STICK) = CUR_CAPACITY(UPG_STICKS);
            }
        }

        item = ITEM_STICK;

    } else if (item == ITEM_NUT) {
        if (INV_CONTENT(ITEM_NUT) != ITEM_NUT) {
            Inventory_ChangeUpgrade(UPG_NUTS, 1);
            AMMO(ITEM_NUT) = 1;
        } else {
            AMMO(ITEM_NUT)++;
            if (AMMO(ITEM_NUT) > CUR_CAPACITY(UPG_NUTS)) {
                AMMO(ITEM_NUT) = CUR_CAPACITY(UPG_NUTS);
            }
        }

    } else if ((item == ITEM_NUTS_5) || (item == ITEM_NUTS_10)) {
        if (INV_CONTENT(ITEM_NUT) != ITEM_NUT) {
            Inventory_ChangeUpgrade(UPG_NUTS, 1);
            AMMO(ITEM_NUT) += sAmmoRefillCounts[item - ITEM_NUTS_5];
        } else {
            AMMO(ITEM_NUT) += sAmmoRefillCounts[item - ITEM_NUTS_5];
            if (AMMO(ITEM_NUT) > CUR_CAPACITY(UPG_NUTS)) {
                AMMO(ITEM_NUT) = CUR_CAPACITY(UPG_NUTS);
            }
        }
        item = ITEM_NUT;

    } else if (item == ITEM_POWDER_KEG) {
        if (INV_CONTENT(ITEM_POWDER_KEG) != ITEM_POWDER_KEG) {
            INV_CONTENT(ITEM_POWDER_KEG) = ITEM_POWDER_KEG;
        }

        AMMO(ITEM_POWDER_KEG) = 1;
        return ITEM_NONE;

    } else if (item == ITEM_BOMB) {
        if ((AMMO(ITEM_BOMB) += 1) > CUR_CAPACITY(UPG_BOMB_BAG)) {
            AMMO(ITEM_BOMB) = CUR_CAPACITY(UPG_BOMB_BAG);
        }
        return ITEM_NONE;

    } else if ((item >= ITEM_BOMBS_5) && (item <= ITEM_BOMBS_30)) {
        if (gSaveContext.save.inventory.items[SLOT_BOMB] != ITEM_BOMB) {
            INV_CONTENT(ITEM_BOMB) = ITEM_BOMB;
            AMMO(ITEM_BOMB) += sAmmoRefillCounts[item - ITEM_BOMBS_5];
            return ITEM_NONE;
        }

        if ((AMMO(ITEM_BOMB) += sAmmoRefillCounts[item - ITEM_BOMBS_5]) > CUR_CAPACITY(UPG_BOMB_BAG)) {
            AMMO(ITEM_BOMB) = CUR_CAPACITY(UPG_BOMB_BAG);
        }
        return ITEM_NONE;

    } else if (item == ITEM_BOMBCHU) {
        if (INV_CONTENT(ITEM_BOMBCHU) != ITEM_BOMBCHU) {
            INV_CONTENT(ITEM_BOMBCHU) = ITEM_BOMBCHU;
            AMMO(ITEM_BOMBCHU) = 10;
            return ITEM_NONE;
        }
        if ((AMMO(ITEM_BOMBCHU) += 10) > CUR_CAPACITY(UPG_BOMB_BAG)) {
            AMMO(ITEM_BOMBCHU) = CUR_CAPACITY(UPG_BOMB_BAG);
        }
        return ITEM_NONE;

    } else if ((item >= ITEM_BOMBCHUS_20) && (item <= ITEM_BOMBCHUS_5)) {
        if (gSaveContext.save.inventory.items[SLOT_BOMBCHU] != ITEM_BOMBCHU) {
            INV_CONTENT(ITEM_BOMBCHU) = ITEM_BOMBCHU;
            AMMO(ITEM_BOMBCHU) += sBombchuRefillCounts[item - ITEM_BOMBCHUS_20];

            if (AMMO(ITEM_BOMBCHU) > CUR_CAPACITY(UPG_BOMB_BAG)) {
                AMMO(ITEM_BOMBCHU) = CUR_CAPACITY(UPG_BOMB_BAG);
            }
            return ITEM_NONE;
        }

        if ((AMMO(ITEM_BOMBCHU) += sBombchuRefillCounts[item - ITEM_BOMBCHUS_20]) > CUR_CAPACITY(UPG_BOMB_BAG)) {
            AMMO(ITEM_BOMBCHU) = CUR_CAPACITY(UPG_BOMB_BAG);
        }
        return ITEM_NONE;

    } else if ((item >= ITEM_ARROWS_10) && (item <= ITEM_ARROWS_50)) {
        AMMO(ITEM_BOW) += sArrowRefillCounts[item - ITEM_ARROWS_10];

        if ((AMMO(ITEM_BOW) >= CUR_CAPACITY(UPG_QUIVER)) || (AMMO(ITEM_BOW) < 0)) {
            AMMO(ITEM_BOW) = CUR_CAPACITY(UPG_QUIVER);
        }
        return ITEM_BOW;

    } else if (item == ITEM_OCARINA) {
        INV_CONTENT(ITEM_OCARINA) = ITEM_OCARINA;
        return ITEM_NONE;

    } else if (item == ITEM_MAGIC_BEANS) {
        if (INV_CONTENT(ITEM_MAGIC_BEANS) == ITEM_NONE) {
            INV_CONTENT(item) = item;
            AMMO(ITEM_MAGIC_BEANS) = 1;
        } else if (AMMO(ITEM_MAGIC_BEANS) < 20) {
            AMMO(ITEM_MAGIC_BEANS)++;
        } else {
            AMMO(ITEM_MAGIC_BEANS) = 20;
        }
        return ITEM_NONE;

    } else if ((item >= ITEM_REMAINS_ODOLWA) && (item <= ITEM_REMAINS_TWINMOLD)) {
        SET_QUEST_ITEM(item - ITEM_REMAINS_ODOLWA + QUEST_REMAINS_ODOLWA);
        return ITEM_NONE;

    } else if (item == ITEM_RECOVERY_HEART) {
        Health_ChangeBy(play, 0x10);
        return item;

    } else if (item == ITEM_MAGIC_SMALL) {
        Magic_Add(play, MAGIC_NORMAL_METER / 2);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_12_80)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_12_80);
            return ITEM_NONE;
        }
        return item;

    } else if (item == ITEM_MAGIC_LARGE) {
        Magic_Add(play, MAGIC_NORMAL_METER);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_12_80)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_12_80);
            return ITEM_NONE;
        }
        return item;

    } else if ((item >= ITEM_RUPEE_GREEN) && (item <= ITEM_RUPEE_HUGE)) {
        Rupees_ChangeBy(sRupeeRefillCounts[item - ITEM_RUPEE_GREEN]);
        return ITEM_NONE;

    } else if (item == ITEM_LONGSHOT) {
        slot = SLOT(item);

        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.inventory.items[slot + i] = ITEM_POTION_RED;
                return ITEM_NONE;
            }
        }
        return item;

    } else if ((item == ITEM_MILK_BOTTLE) || (item == ITEM_POE) || (item == ITEM_GOLD_DUST) || (item == ITEM_CHATEAU) ||
               (item == ITEM_HYLIAN_LOACH)) {
        slot = SLOT(item);

        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.inventory.items[slot + i] = item;
                return ITEM_NONE;
            }
        }
        return item;

    } else if (item == ITEM_BOTTLE) {
        slot = SLOT(item);

        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.inventory.items[slot + i] = item;
                return ITEM_NONE;
            }
        }
        return item;

    } else if (((item >= ITEM_POTION_RED) && (item <= ITEM_OBABA_DRINK)) || (item == ITEM_CHATEAU_2) ||
               (item == ITEM_MILK) || (item == ITEM_GOLD_DUST_2) || (item == ITEM_HYLIAN_LOACH_2) ||
               (item == ITEM_SEAHORSE_CAUGHT)) {
        slot = SLOT(item);

        if ((item != ITEM_MILK_BOTTLE) && (item != ITEM_MILK_HALF)) {
            if (item == ITEM_CHATEAU_2) {
                item = ITEM_CHATEAU;

            } else if (item == ITEM_MILK) {
                item = ITEM_MILK_BOTTLE;

            } else if (item == ITEM_GOLD_DUST_2) {
                item = ITEM_GOLD_DUST;

            } else if (item == ITEM_HYLIAN_LOACH_2) {
                item = ITEM_HYLIAN_LOACH;

            } else if (item == ITEM_SEAHORSE_CAUGHT) {
                item = ITEM_SEAHORSE;
            }
            slot = SLOT(item);

            for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
                if (gSaveContext.save.inventory.items[slot + i] == ITEM_BOTTLE) {
                    if (item == ITEM_HOT_SPRING_WATER) {
                        Interface_StartBottleTimer(60, i);
                    }

                    if ((slot + i) == C_SLOT_EQUIP(0, EQUIP_SLOT_C_LEFT)) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) = item;
                        Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_LEFT);
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_ENABLED;
                    } else if ((slot + i) == C_SLOT_EQUIP(0, EQUIP_SLOT_C_DOWN)) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) = item;
                        Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_DOWN);
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_ENABLED;
                    } else if ((slot + i) == C_SLOT_EQUIP(0, EQUIP_SLOT_C_RIGHT)) {
                        BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) = item;
                        Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_RIGHT);
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_ENABLED;
                    }

                    gSaveContext.save.inventory.items[slot + i] = item;
                    return ITEM_NONE;
                }
            }
        } else {
            for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
                if (gSaveContext.save.inventory.items[slot + i] == ITEM_NONE) {
                    gSaveContext.save.inventory.items[slot + i] = item;
                    return ITEM_NONE;
                }
            }
        }

    } else if ((item >= ITEM_MOON_TEAR) && (item <= ITEM_MASK_GIANT)) {
        temp = INV_CONTENT(item);
        INV_CONTENT(item) = item;
        if ((item >= ITEM_MOON_TEAR) && (item <= ITEM_PENDANT_OF_MEMORIES) && (temp != ITEM_NONE)) {
            for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
                if (temp == GET_CUR_FORM_BTN_ITEM(i)) {
                    SET_CUR_FORM_BTN_ITEM(i, item);
                    Interface_LoadItemIconImpl(play, i);
                    return ITEM_NONE;
                }
            }
        }
        return ITEM_NONE;
    }

    temp = gSaveContext.save.inventory.items[slot];
    INV_CONTENT(item) = item;
    return temp;
}

u8 Item_CheckObtainabilityImpl(u8 item) {
    s16 i;
    u8 slot;
    u8 bottleSlot;

    slot = SLOT(item);
    if (item >= ITEM_STICKS_5) {
        slot = SLOT(sExtraItemBases[item - ITEM_STICKS_5]);
    }

    if (item == ITEM_SKULL_TOKEN) {
        return ITEM_NONE;

    } else if (item == ITEM_TINGLE_MAP) {
        return ITEM_NONE;

    } else if (item == ITEM_BOMBERS_NOTEBOOK) {
        return ITEM_NONE;

    } else if ((item >= ITEM_SWORD_KOKIRI) && (item <= ITEM_SWORD_GILDED)) {
        return ITEM_NONE;

    } else if ((item >= ITEM_SHIELD_HERO) && (item <= ITEM_SHIELD_MIRROR)) {
        return ITEM_NONE;

    } else if ((item == ITEM_KEY_BOSS) || (item == ITEM_COMPASS) || (item == ITEM_DUNGEON_MAP)) {
        if (!CHECK_DUNGEON_ITEM(item - ITEM_KEY_BOSS, gSaveContext.mapIndex)) {
            return ITEM_NONE;
        }
        return item;

    } else if (item == ITEM_KEY_SMALL) {
        return ITEM_NONE;

    } else if ((item == ITEM_OCARINA) || (item == ITEM_BOMBCHU) || (item == ITEM_HOOKSHOT) || (item == ITEM_LENS) ||
               (item == ITEM_SWORD_GREAT_FAIRY) || (item == ITEM_PICTO_BOX)) {
        if (INV_CONTENT(item) == ITEM_NONE) {
            return ITEM_NONE;
        }
        return INV_CONTENT(item);

    } else if ((item >= ITEM_BOMBS_5) && (item == ITEM_BOMBS_30)) {
        //! @bug: Should be a range check: (item <= ITEM_BOMBS_30)
        if (CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
            return ITEM_NONE;
        }
        return 0;

    } else if ((item >= ITEM_BOMBCHUS_20) && (item <= ITEM_BOMBCHUS_5)) {
        if (CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
            return ITEM_NONE;
        }
        return 0;

    } else if ((item == ITEM_QUIVER_30) || (item == ITEM_BOW)) {
        if (CUR_UPG_VALUE(UPG_QUIVER) == 0) {
            return ITEM_NONE;
        }
        return 0;

    } else if ((item == ITEM_QUIVER_40) || (item == ITEM_QUIVER_50)) {
        return ITEM_NONE;

    } else if ((item == ITEM_BOMB_BAG_20) || (item == ITEM_BOMB)) {
        if (CUR_UPG_VALUE(UPG_BOMB_BAG) == 0) {
            return ITEM_NONE;
        }
        return 0;

    } else if ((item >= ITEM_STICK_UPGRADE_20) && (item <= ITEM_NUT_UPGRADE_40)) {
        return ITEM_NONE;

    } else if ((item >= ITEM_BOMB_BAG_30) && (item <= ITEM_WALLET_GIANT)) {
        return ITEM_NONE;

    } else if (item == ITEM_MAGIC_BEANS) {
        return ITEM_NONE;

    } else if (item == ITEM_POWDER_KEG) {
        return ITEM_NONE;

    } else if ((item == ITEM_HEART_PIECE_2) || (item == ITEM_HEART_PIECE)) {
        return ITEM_NONE;

    } else if (item == ITEM_HEART_CONTAINER) {
        return ITEM_NONE;

    } else if (item == ITEM_RECOVERY_HEART) {
        return ITEM_RECOVERY_HEART;

    } else if ((item == ITEM_MAGIC_SMALL) || (item == ITEM_MAGIC_LARGE)) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_12_80)) {
            return ITEM_NONE;
        }
        return item;

    } else if ((item >= ITEM_RUPEE_GREEN) && (item <= ITEM_RUPEE_HUGE)) {
        return ITEM_NONE;

    } else if ((item >= ITEM_REMAINS_ODOLWA) && (item <= ITEM_REMAINS_TWINMOLD)) {
        return ITEM_NONE;

    } else if (item == ITEM_LONGSHOT) {
        return ITEM_NONE;

    } else if (item == ITEM_BOTTLE) {
        return ITEM_NONE;

    } else if ((item == ITEM_MILK_BOTTLE) || (item == ITEM_POE) || (item == ITEM_GOLD_DUST) || (item == ITEM_CHATEAU) ||
               (item == ITEM_HYLIAN_LOACH)) {
        return ITEM_NONE;

    } else if (((item >= ITEM_POTION_RED) && (item <= ITEM_OBABA_DRINK)) || (item == ITEM_CHATEAU_2) ||
               (item == ITEM_MILK) || (item == ITEM_GOLD_DUST_2) || (item == ITEM_HYLIAN_LOACH_2) ||
               (item == ITEM_SEAHORSE_CAUGHT)) {
        bottleSlot = SLOT(item);

        if ((item != ITEM_MILK_BOTTLE) && (item != ITEM_MILK_HALF)) {
            if (item == ITEM_CHATEAU_2) {
                item = ITEM_CHATEAU;

            } else if (item == ITEM_MILK) {
                item = ITEM_MILK_BOTTLE;

            } else if (item == ITEM_GOLD_DUST_2) {
                item = ITEM_GOLD_DUST;

            } else if (item == ITEM_HYLIAN_LOACH_2) {
                item = ITEM_HYLIAN_LOACH;

            } else if (item == ITEM_SEAHORSE_CAUGHT) {
                item = ITEM_SEAHORSE;
            }
            bottleSlot = SLOT(item);

            for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
                if (gSaveContext.save.inventory.items[bottleSlot + i] == ITEM_BOTTLE) {
                    return ITEM_NONE;
                }
            }
        } else {
            for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
                if (gSaveContext.save.inventory.items[bottleSlot + i] == ITEM_NONE) {
                    return ITEM_NONE;
                }
            }
        }
    } else if ((item >= ITEM_MOON_TEAR) && (item <= ITEM_MASK_GIANT)) {
        return ITEM_NONE;
    }

    return gSaveContext.save.inventory.items[slot];
}

u8 Item_CheckObtainability(u8 item) {
    return Item_CheckObtainabilityImpl(item);
}

void Inventory_DeleteItem(s16 item, s16 slot) {
    s16 btn;

    gSaveContext.save.inventory.items[slot] = ITEM_NONE;

    for (btn = EQUIP_SLOT_C_LEFT; btn <= EQUIP_SLOT_C_RIGHT; btn++) {
        if (GET_CUR_FORM_BTN_ITEM(btn) == item) {
            SET_CUR_FORM_BTN_ITEM(btn, ITEM_NONE);
            SET_CUR_FORM_BTN_SLOT(btn, SLOT_NONE);
        }
    }
}

void Inventory_UnequipItem(s16 item) {
    s16 btn;

    for (btn = EQUIP_SLOT_C_LEFT; btn <= EQUIP_SLOT_C_RIGHT; btn++) {
        if (GET_CUR_FORM_BTN_ITEM(btn) == item) {
            SET_CUR_FORM_BTN_ITEM(btn, ITEM_NONE);
            SET_CUR_FORM_BTN_SLOT(btn, SLOT_NONE);
        }
    }
}

s32 Inventory_ReplaceItem(PlayState* play, u8 oldItem, u8 newItem) {
    u8 i;

    for (i = 0; i < 24; i++) {
        if (gSaveContext.save.inventory.items[i] == oldItem) {
            gSaveContext.save.inventory.items[i] = newItem;

            for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
                if (GET_CUR_FORM_BTN_ITEM(i) == oldItem) {
                    SET_CUR_FORM_BTN_ITEM(i, newItem);
                    Interface_LoadItemIconImpl(play, i);
                    break;
                }
            }
            return true;
        }
    }
    return false;
}

void Inventory_UpdateDeitySwordEquip(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    u8 btn;

    if (CUR_FORM == PLAYER_FORM_FIERCE_DEITY) {
        interfaceCtx->unk_21C = 0;
        interfaceCtx->bButtonDoAction = 0;

        // Is simply checking if (gSaveContext.save.playerForm == PLAYER_FORM_FIERCE_DEITY)
        if ((((gSaveContext.save.playerForm > 0) && (gSaveContext.save.playerForm < 4))
                 ? 1
                 : gSaveContext.save.playerForm >> 1) == 0) {
            CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_DEITY;
        } else if (CUR_FORM_EQUIP(EQUIP_SLOT_B) == ITEM_SWORD_DEITY) {
            if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_NONE) {
                CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_NONE;
            } else {
                CUR_FORM_EQUIP(EQUIP_SLOT_B) =
                    GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) - EQUIP_VALUE_SWORD_KOKIRI + ITEM_SWORD_KOKIRI;
            }
        }
    }

    for (btn = EQUIP_SLOT_B; btn <= EQUIP_SLOT_B; btn++) {
        if ((GET_CUR_FORM_BTN_ITEM(btn) != ITEM_NONE) && (GET_CUR_FORM_BTN_ITEM(btn) != ITEM_FD)) {
            Interface_LoadItemIconImpl(play, btn);
        }
    }
}

s32 Inventory_HasEmptyBottle(void) {
    s32 slot;

    for (slot = SLOT_BOTTLE_1; slot <= SLOT_BOTTLE_6; slot++) {
        if (gSaveContext.save.inventory.items[slot] == ITEM_BOTTLE) {
            return true;
        }
    }
    return false;
}

s32 Inventory_HasItemInBottle(u8 item) {
    s32 slot;

    for (slot = SLOT_BOTTLE_1; slot <= SLOT_BOTTLE_6; slot++) {
        if (gSaveContext.save.inventory.items[slot] == item) {
            return true;
        }
    }
    return false;
}

void Inventory_UpdateBottleItem(PlayState* play, u8 item, u8 btn) {
    gSaveContext.save.inventory.items[GET_CUR_FORM_BTN_SLOT(btn)] = item;
    SET_CUR_FORM_BTN_ITEM(btn, item);

    Interface_LoadItemIconImpl(play, btn);

    play->pauseCtx.cursorItem[PAUSE_ITEM] = item;
    gSaveContext.buttonStatus[btn] = BTN_ENABLED;

    if (item == ITEM_HOT_SPRING_WATER) {
        Interface_StartBottleTimer(60, GET_CUR_FORM_BTN_SLOT(btn) - SLOT_BOTTLE_1);
    }
}

s32 Inventory_ConsumeFairy(PlayState* play) {
    u8 bottleSlot = SLOT(ITEM_FAIRY);
    u8 btn;
    u8 i;

    for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
        if (gSaveContext.save.inventory.items[bottleSlot + i] == ITEM_FAIRY) {
            for (btn = EQUIP_SLOT_C_LEFT; btn <= EQUIP_SLOT_C_RIGHT; btn++) {
                if (GET_CUR_FORM_BTN_ITEM(btn) == ITEM_FAIRY) {
                    SET_CUR_FORM_BTN_ITEM(btn, ITEM_BOTTLE);
                    Interface_LoadItemIconImpl(play, btn);
                    bottleSlot = GET_CUR_FORM_BTN_SLOT(btn);
                    i = 0;
                    break;
                }
            }
            gSaveContext.save.inventory.items[bottleSlot + i] = ITEM_BOTTLE;
            return true;
        }
    }

    return false;
}

/**
 * Only used to equip Spring Water when Hot Spring Water timer runs out.
 */
void Inventory_UpdateItem(PlayState* play, s16 slot, s16 item) {
    s16 btn;

    gSaveContext.save.inventory.items[slot] = item;

    for (btn = EQUIP_SLOT_C_LEFT; btn <= EQUIP_SLOT_C_RIGHT; btn++) {
        if (GET_CUR_FORM_BTN_SLOT(btn) == slot) {
            SET_CUR_FORM_BTN_ITEM(btn, item);
            Interface_LoadItemIconImpl(play, btn);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_801153C8.s")

TexturePtr sDoActionTextures[] = {
    gDoActionAttackENGTex,
    gDoActionCheckENGTex,
};

void func_80115428(InterfaceContext* interfaceCtx, u16 doAction, s16 loadOffset);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80115428.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011552C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_801155B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80115764.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80115844.s")

/**
 * @return false if player is out of health
 */
s32 Health_ChangeBy(PlayState* play, s16 healthChange) {
    if (healthChange > 0) {
        play_sound(NA_SE_SY_HP_RECOVER);
    } else if (gSaveContext.save.playerData.doubleDefense && (healthChange < 0)) {
        healthChange >>= 1;
    }

    gSaveContext.save.playerData.health += healthChange;

    if (((void)0, gSaveContext.save.playerData.health) > ((void)0, gSaveContext.save.playerData.healthCapacity)) {
        gSaveContext.save.playerData.health = gSaveContext.save.playerData.healthCapacity;
    }

    if (gSaveContext.save.playerData.health <= 0) {
        gSaveContext.save.playerData.health = 0;
        return false;
    } else {
        return true;
    }
}

void Health_GiveHearts(s16 hearts) {
    gSaveContext.save.playerData.healthCapacity += hearts * 0x10;
}

void Rupees_ChangeBy(s16 rupeeChange) {
    gSaveContext.rupeeAccumulator += rupeeChange;
}

void Inventory_ChangeAmmo(s16 item, s16 ammoChange) {
    if (item == ITEM_STICK) {
        AMMO(ITEM_STICK) += ammoChange;

        if (AMMO(ITEM_STICK) >= CUR_CAPACITY(UPG_STICKS)) {
            AMMO(ITEM_STICK) = CUR_CAPACITY(UPG_STICKS);
        } else if (AMMO(ITEM_STICK) < 0) {
            AMMO(ITEM_STICK) = 0;
        }

    } else if (item == ITEM_NUT) {
        AMMO(ITEM_NUT) += ammoChange;

        if (AMMO(ITEM_NUT) >= CUR_CAPACITY(UPG_NUTS)) {
            AMMO(ITEM_NUT) = CUR_CAPACITY(UPG_NUTS);
        } else if (AMMO(ITEM_NUT) < 0) {
            AMMO(ITEM_NUT) = 0;
        }

    } else if (item == ITEM_BOMBCHU) {
        AMMO(ITEM_BOMBCHU) += ammoChange;

        if (AMMO(ITEM_BOMBCHU) >= CUR_CAPACITY(UPG_BOMB_BAG)) {
            AMMO(ITEM_BOMBCHU) = CUR_CAPACITY(UPG_BOMB_BAG);
        } else if (AMMO(ITEM_BOMBCHU) < 0) {
            AMMO(ITEM_BOMBCHU) = 0;
        }

    } else if (item == ITEM_BOW) {
        AMMO(ITEM_BOW) += ammoChange;

        if (AMMO(ITEM_BOW) >= CUR_CAPACITY(UPG_QUIVER)) {
            AMMO(ITEM_BOW) = CUR_CAPACITY(UPG_QUIVER);
        } else if (AMMO(ITEM_BOW) < 0) {
            AMMO(ITEM_BOW) = 0;
        }

    } else if (item == ITEM_BOMB) {
        AMMO(ITEM_BOMB) += ammoChange;

        if (AMMO(ITEM_BOMB) >= CUR_CAPACITY(UPG_BOMB_BAG)) {
            AMMO(ITEM_BOMB) = CUR_CAPACITY(UPG_BOMB_BAG);
        } else if (AMMO(ITEM_BOMB) < 0) {
            AMMO(ITEM_BOMB) = 0;
        }

    } else if (item == ITEM_MAGIC_BEANS) {
        AMMO(ITEM_MAGIC_BEANS) += ammoChange;

    } else if (item == ITEM_POWDER_KEG) {
        AMMO(ITEM_POWDER_KEG) += ammoChange;
        if (AMMO(ITEM_POWDER_KEG) >= 1) {
            AMMO(ITEM_POWDER_KEG) = 1;
        } else if (AMMO(ITEM_POWDER_KEG) < 0) {
            AMMO(ITEM_POWDER_KEG) = 0;
        }
    }
}

void Magic_Add(PlayState* play, s16 magicToAdd) {
    if (((void)0, gSaveContext.save.playerData.magic) < ((void)0, gSaveContext.magicCapacity)) {
        gSaveContext.magicToAdd += magicToAdd;
        gSaveContext.isMagicRequested = true;
    }
}

void Magic_Reset(PlayState* play) {
    if ((gSaveContext.magicState != MAGIC_STATE_STEP_CAPACITY) && (gSaveContext.magicState != MAGIC_STATE_FILL)) {
        sMagicMeterOutlinePrimRed = sMagicMeterOutlinePrimGreen = sMagicMeterOutlinePrimBlue = 255;
        gSaveContext.magicState = MAGIC_STATE_IDLE;
    }
}

/**
 * Request to consume magic.
 *
 * @param magicToConsume the positive-valued amount to decrease magic by
 * @param type how the magic is consumed.
 * @return false if the request failed
 */
s32 Magic_Consume(PlayState* play, s16 magicToConsume, s16 type) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    // Magic is not acquired yet
    if (!gSaveContext.save.playerData.isMagicAcquired) {
        return false;
    }

    // Not enough magic available to consume
    if ((gSaveContext.save.playerData.magic - magicToConsume) < 0) {
        if (gSaveContext.magicCapacity != 0) {
            play_sound(NA_SE_SY_ERROR);
        }
        return false;
    }

    switch (type) {
        case MAGIC_CONSUME_NOW:
        case MAGIC_CONSUME_NOW_ALT:
            // Drain magic immediately e.g. Deku Bubble
            if ((gSaveContext.magicState == MAGIC_STATE_IDLE) ||
                (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS)) {
                if (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS) {
                    play->actorCtx.lensActive = false;
                }
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                    magicToConsume = 0;
                }
                gSaveContext.magicToConsume = magicToConsume;
                gSaveContext.magicState = MAGIC_STATE_CONSUME_SETUP;
                return true;
            } else {
                play_sound(NA_SE_SY_ERROR);
                return false;
            }

        case MAGIC_CONSUME_WAIT_NO_PREVIEW:
            // Sets consume target but waits to consume.
            // No yellow magic to preview target consumption.
            if ((gSaveContext.magicState == MAGIC_STATE_IDLE) ||
                (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS)) {
                if (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS) {
                    play->actorCtx.lensActive = false;
                }
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                    magicToConsume = 0;
                }
                gSaveContext.magicToConsume = magicToConsume;
                gSaveContext.magicState = MAGIC_STATE_METER_FLASH_3;
                return true;
            } else {
                play_sound(NA_SE_SY_ERROR);
                return false;
            }

        case MAGIC_CONSUME_LENS:
            if (gSaveContext.magicState == MAGIC_STATE_IDLE) {
                if (gSaveContext.save.playerData.magic != 0) {
                    interfaceCtx->magicConsumptionTimer = 80;
                    gSaveContext.magicState = MAGIC_STATE_CONSUME_LENS;
                    return true;
                } else {
                    return false;
                }
            } else if (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS) {
                return true;
            } else {
                return false;
            }

        case MAGIC_CONSUME_WAIT_PREVIEW:
            // Sets consume target but waits to consume.
            // Preview consumption with a yellow bar. e.g. Spin Attack
            if ((gSaveContext.magicState == MAGIC_STATE_IDLE) ||
                (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS)) {
                if (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS) {
                    play->actorCtx.lensActive = false;
                }
                gSaveContext.magicToConsume = magicToConsume;
                gSaveContext.magicState = MAGIC_STATE_METER_FLASH_2;
                return true;
            } else {
                play_sound(NA_SE_SY_ERROR);
                return false;
            }

        case MAGIC_CONSUME_GORON_ZORA:
            // Goron spiked rolling or Zora electric barrier
            if (gSaveContext.save.playerData.magic != 0) {
                interfaceCtx->magicConsumptionTimer = 10;
                gSaveContext.magicState = MAGIC_STATE_CONSUME_GORON_ZORA_SETUP;
                return true;
            } else {
                return false;
            }

        case MAGIC_CONSUME_GIANTS_MASK:
            // Wearing Giant's Mask
            if (gSaveContext.magicState == MAGIC_STATE_IDLE) {
                if (gSaveContext.save.playerData.magic != 0) {
                    interfaceCtx->magicConsumptionTimer = R_MAGIC_CONSUME_TIMER_GIANTS_MASK;
                    gSaveContext.magicState = MAGIC_STATE_CONSUME_GIANTS_MASK;
                    return true;
                } else {
                    return false;
                }
            }
            if (gSaveContext.magicState == MAGIC_STATE_CONSUME_GIANTS_MASK) {
                return true;
            } else {
                return false;
            }

        case MAGIC_CONSUME_DEITY_BEAM:
            // Consumes magic immediately
            if ((gSaveContext.magicState == MAGIC_STATE_IDLE) ||
                (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS)) {
                if (gSaveContext.magicState == MAGIC_STATE_CONSUME_LENS) {
                    play->actorCtx.lensActive = false;
                }
                if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                    magicToConsume = 0;
                }
                gSaveContext.save.playerData.magic -= magicToConsume;
                return true;
            } else {
                play_sound(NA_SE_SY_ERROR);
                return false;
            }
    }

    return false;
}

void Magic_UpdateAddRequest(void) {
    if (gSaveContext.isMagicRequested) {
        gSaveContext.save.playerData.magic += 4;
        play_sound(NA_SE_SY_GAUGE_UP - SFX_FLAG);

        if (((void)0, gSaveContext.save.playerData.magic) >= ((void)0, gSaveContext.magicCapacity)) {
            gSaveContext.save.playerData.magic = gSaveContext.magicCapacity;
            gSaveContext.magicToAdd = 0;
            gSaveContext.isMagicRequested = false;
        } else {
            gSaveContext.magicToAdd -= 4;
            if (gSaveContext.magicToAdd <= 0) {
                gSaveContext.magicToAdd = 0;
                gSaveContext.isMagicRequested = false;
            }
        }
    }
}

s16 sMagicBorderColors[][3] = {
    { 255, 255, 255 },
    { 150, 150, 150 },
};
s16 sMagicBorderIndices[] = { 0, 1, 1, 0 };
s16 sMagicBorderColorTimerIndex[] = { 2, 1, 2, 1 };

void Magic_FlashMeterBorder(void) {
    s16 borderChangeR;
    s16 borderChangeG;
    s16 borderChangeB;
    s16 index = sMagicBorderIndices[sMagicBorderStep];

    borderChangeR = ABS_ALT(sMagicMeterOutlinePrimRed - sMagicBorderColors[index][0]) / sMagicBorderRatio;
    borderChangeG = ABS_ALT(sMagicMeterOutlinePrimGreen - sMagicBorderColors[index][1]) / sMagicBorderRatio;
    borderChangeB = ABS_ALT(sMagicMeterOutlinePrimBlue - sMagicBorderColors[index][2]) / sMagicBorderRatio;

    if (sMagicMeterOutlinePrimRed >= sMagicBorderColors[index][0]) {
        sMagicMeterOutlinePrimRed -= borderChangeR;
    } else {
        sMagicMeterOutlinePrimRed += borderChangeR;
    }

    if (sMagicMeterOutlinePrimGreen >= sMagicBorderColors[index][1]) {
        sMagicMeterOutlinePrimGreen -= borderChangeG;
    } else {
        sMagicMeterOutlinePrimGreen += borderChangeG;
    }

    if (sMagicMeterOutlinePrimBlue >= sMagicBorderColors[index][2]) {
        sMagicMeterOutlinePrimBlue -= borderChangeB;
    } else {
        sMagicMeterOutlinePrimBlue += borderChangeB;
    }

    sMagicBorderRatio--;
    if (sMagicBorderRatio == 0) {
        sMagicMeterOutlinePrimRed = sMagicBorderColors[index][0];
        sMagicMeterOutlinePrimGreen = sMagicBorderColors[index][1];
        sMagicMeterOutlinePrimBlue = sMagicBorderColors[index][2];

        sMagicBorderRatio = sMagicBorderColorTimerIndex[sMagicBorderStep];

        sMagicBorderStep++;
        if (sMagicBorderStep >= 4) {
            sMagicBorderStep = 0;
        }
    }
}

void Magic_Update(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 magicCapacityTarget;

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
        Magic_FlashMeterBorder();
    }

    switch (gSaveContext.magicState) {
        case MAGIC_STATE_STEP_CAPACITY:
            // Step magicCapacity to the capacity determined by magicLevel
            // This changes the width of the magic meter drawn
            magicCapacityTarget = gSaveContext.save.playerData.magicLevel * MAGIC_NORMAL_METER;
            if (gSaveContext.magicCapacity != magicCapacityTarget) {
                if (gSaveContext.magicCapacity < magicCapacityTarget) {
                    gSaveContext.magicCapacity += 0x10;
                    if (gSaveContext.magicCapacity > magicCapacityTarget) {
                        gSaveContext.magicCapacity = magicCapacityTarget;
                    }
                } else {
                    gSaveContext.magicCapacity -= 0x10;
                    if (gSaveContext.magicCapacity <= magicCapacityTarget) {
                        gSaveContext.magicCapacity = magicCapacityTarget;
                    }
                }
            } else {
                // Once the capacity has reached its target,
                // follow up by filling magic to magicFillTarget
                gSaveContext.magicState = MAGIC_STATE_FILL;
            }
            break;

        case MAGIC_STATE_FILL:
            // Add magic until magicFillTarget is reached
            gSaveContext.save.playerData.magic += 0x10;

            if ((gSaveContext.gameMode == 0) && (gSaveContext.sceneLayer < 4)) {
                play_sound(NA_SE_SY_GAUGE_UP - SFX_FLAG);
            }

            if (((void)0, gSaveContext.save.playerData.magic) >= ((void)0, gSaveContext.magicFillTarget)) {
                gSaveContext.save.playerData.magic = gSaveContext.magicFillTarget;
                gSaveContext.magicState = MAGIC_STATE_IDLE;
            }
            break;

        case MAGIC_STATE_CONSUME_SETUP:
            // Sets the speed at which magic border flashes
            sMagicBorderRatio = 2;
            gSaveContext.magicState = MAGIC_STATE_CONSUME;
            break;

        case MAGIC_STATE_CONSUME:
            // Consume magic until target is reached or no more magic is available
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                gSaveContext.save.playerData.magic =
                    ((void)0, gSaveContext.save.playerData.magic) - ((void)0, gSaveContext.magicToConsume);
                if (gSaveContext.save.playerData.magic <= 0) {
                    gSaveContext.save.playerData.magic = 0;
                }
                gSaveContext.magicState = MAGIC_STATE_METER_FLASH_1;
                sMagicMeterOutlinePrimRed = sMagicMeterOutlinePrimGreen = sMagicMeterOutlinePrimBlue = 255;
            }
            // fallthrough (flash border while magic is being consumed)
        case MAGIC_STATE_METER_FLASH_1:
        case MAGIC_STATE_METER_FLASH_2:
        case MAGIC_STATE_METER_FLASH_3:
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                Magic_FlashMeterBorder();
            }
            break;

        case MAGIC_STATE_RESET:
            sMagicMeterOutlinePrimRed = sMagicMeterOutlinePrimGreen = sMagicMeterOutlinePrimBlue = 255;
            gSaveContext.magicState = MAGIC_STATE_IDLE;
            break;

        case MAGIC_STATE_CONSUME_LENS:
            // Slowly consume magic while Lens of Truth is active
            if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) &&
                (msgCtx->msgMode == 0) && (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
                (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF) &&
                !Play_InCsMode(play)) {

                if ((gSaveContext.save.playerData.magic == 0) ||
                    ((Player_GetEnvironmentalHazard(play) >= PLAYER_ENV_HAZARD_UNDERWATER_FLOOR) &&
                     (Player_GetEnvironmentalHazard(play) <= PLAYER_ENV_HAZARD_UNDERWATER_FREE)) ||
                    ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) != ITEM_LENS) &&
                     (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) != ITEM_LENS) &&
                     (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) != ITEM_LENS)) ||
                    !play->actorCtx.lensActive) {
                    // Deactivate Lens of Truth and set magic state to idle
                    play->actorCtx.lensActive = false;
                    play_sound(NA_SE_SY_GLASSMODE_OFF);
                    gSaveContext.magicState = MAGIC_STATE_IDLE;
                    sMagicMeterOutlinePrimRed = sMagicMeterOutlinePrimGreen = sMagicMeterOutlinePrimBlue = 255;
                    break;
                }

                interfaceCtx->magicConsumptionTimer--;
                if (interfaceCtx->magicConsumptionTimer == 0) {
                    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                        gSaveContext.save.playerData.magic--;
                    }
                    interfaceCtx->magicConsumptionTimer = 80;
                }
            }
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                Magic_FlashMeterBorder();
            }
            break;

        case MAGIC_STATE_CONSUME_GORON_ZORA_SETUP:
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                gSaveContext.save.playerData.magic -= 2;
            }
            if (gSaveContext.save.playerData.magic <= 0) {
                gSaveContext.save.playerData.magic = 0;
            }
            gSaveContext.magicState = MAGIC_STATE_CONSUME_GORON_ZORA;
            // fallthrough
        case MAGIC_STATE_CONSUME_GORON_ZORA:
            if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == 0) &&
                (msgCtx->msgMode == 0) && (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
                (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
                if (!Play_InCsMode(play)) {
                    interfaceCtx->magicConsumptionTimer--;
                    if (interfaceCtx->magicConsumptionTimer == 0) {
                        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                            gSaveContext.save.playerData.magic--;
                        }
                        if (gSaveContext.save.playerData.magic <= 0) {
                            gSaveContext.save.playerData.magic = 0;
                        }
                        interfaceCtx->magicConsumptionTimer = 10;
                    }
                }
            }
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                Magic_FlashMeterBorder();
            }
            break;

        case MAGIC_STATE_CONSUME_GIANTS_MASK:
            if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) &&
                (msgCtx->msgMode == 0) && (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
                (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
                if (!Play_InCsMode(play)) {
                    interfaceCtx->magicConsumptionTimer--;
                    if (interfaceCtx->magicConsumptionTimer == 0) {
                        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                            gSaveContext.save.playerData.magic--;
                        }
                        if (gSaveContext.save.playerData.magic <= 0) {
                            gSaveContext.save.playerData.magic = 0;
                        }
                        interfaceCtx->magicConsumptionTimer = R_MAGIC_CONSUME_TIMER_GIANTS_MASK;
                    }
                }
            }
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                Magic_FlashMeterBorder();
            }
            break;

        default:
            gSaveContext.magicState = MAGIC_STATE_IDLE;
            break;
    }
}

void Magic_DrawMeter(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 magicBarY;

    OPEN_DISPS(play->state.gfxCtx);

    if (gSaveContext.save.playerData.magicLevel != 0) {
        if (gSaveContext.save.playerData.healthCapacity > 0xA0) {
            magicBarY = 42; // two rows of hearts
        } else {
            magicBarY = 34; // one row of hearts
        }

        func_8012C654(play->state.gfxCtx);

        gDPSetEnvColor(OVERLAY_DISP++, 100, 50, 50, 255);

        OVERLAY_DISP = Gfx_DrawTexRectIA8_DropShadow(
            OVERLAY_DISP, gMagicMeterEndTex, 8, 16, 18, magicBarY, 8, 16, 1 << 10, 1 << 10, sMagicMeterOutlinePrimRed,
            sMagicMeterOutlinePrimGreen, sMagicMeterOutlinePrimBlue, interfaceCtx->magicAlpha);
        OVERLAY_DISP = Gfx_DrawTexRectIA8_DropShadow(OVERLAY_DISP, gMagicMeterMidTex, 24, 16, 26, magicBarY,
                                                     ((void)0, gSaveContext.magicCapacity), 16, 1 << 10, 1 << 10,
                                                     sMagicMeterOutlinePrimRed, sMagicMeterOutlinePrimGreen,
                                                     sMagicMeterOutlinePrimBlue, interfaceCtx->magicAlpha);
        OVERLAY_DISP = Gfx_DrawTexRectIA8_DropShadowOffset(
            OVERLAY_DISP, gMagicMeterEndTex, 8, 16, ((void)0, gSaveContext.magicCapacity) + 26, magicBarY, 8, 16,
            1 << 10, 1 << 10, sMagicMeterOutlinePrimRed, sMagicMeterOutlinePrimGreen, sMagicMeterOutlinePrimBlue,
            interfaceCtx->magicAlpha, 3, 0x100);

        gDPPipeSync(OVERLAY_DISP++);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE);
        gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);

        if (gSaveContext.magicState == MAGIC_STATE_METER_FLASH_2) {
            // Yellow part of the meter indicating the amount of magic to be subtracted
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 250, 250, 0, interfaceCtx->magicAlpha);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, gMagicMeterFillTex, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(OVERLAY_DISP++, 104, (magicBarY + 3) << 2,
                                (((void)0, gSaveContext.save.playerData.magic) + 26) << 2, (magicBarY + 10) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

            // Fill the rest of the meter with the normal magic color
            gDPPipeSync(OVERLAY_DISP++);
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                // Blue magic
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 200, interfaceCtx->magicAlpha);
            } else {
                // Green magic (default)
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 200, 0, interfaceCtx->magicAlpha);
            }

            gSPTextureRectangle(
                OVERLAY_DISP++, 104, (magicBarY + 3) << 2,
                ((((void)0, gSaveContext.save.playerData.magic) - ((void)0, gSaveContext.magicToConsume)) + 26) << 2,
                (magicBarY + 10) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        } else {
            // Fill the whole meter with the normal magic color
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                // Blue magic
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 200, interfaceCtx->magicAlpha);
            } else {
                // Green magic (default)
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 200, 0, interfaceCtx->magicAlpha);
            }

            gDPLoadTextureBlock_4b(OVERLAY_DISP++, gMagicMeterFillTex, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(OVERLAY_DISP++, 104, (magicBarY + 3) << 2,
                                (((void)0, gSaveContext.save.playerData.magic) + 26) << 2, (magicBarY + 10) << 2,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80116FD8.s")

void func_801170B8(InterfaceContext* interfaceCtx);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_801170B8.s")

TexturePtr cUpLabelTextures[] = {
    gTatlCUpENGTex, gTatlCUpENGTex, gTatlCUpGERTex, gTatlCUpFRATex, gTatlCUpESPTex,
};
s16 startButtonLeftPos[] = {
    // Remnant of OoT
    130, 136, 136, 136, 136,
};
s16 D_801BFAF4[] = { 0x1D, 0x1B };
s16 D_801BFAF8[] = { 0x1B, 0x1B };

void func_80117100(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80117100.s")

s16 D_801BFAFC[] = { 30, 24, 24, 24 };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80117A20.s")

s16 D_801BFB04[] = { 0xA2, 0xE4, 0xFA, 0x110 };
s16 D_801BFB0C[] = { 0x23, 0x23, 0x33, 0x23 };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80117BD0.s")

void func_80118084(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80118084.s")

void func_80118890(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80118890.s")

void func_80118BA4(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80118BA4.s")

extern TexturePtr D_08095AC0;            // gMagicArrowEquipEffectTex
s16 D_801BFB14[] = { 255, 100, 255, 0 }; // magicArrowEffectsR
s16 D_801BFB1C[] = { 0, 100, 255, 0 };   // magicArrowEffectsG
s16 D_801BFB24[] = { 0, 255, 100, 0 };   // magicArrowEffectsB

void func_80119030(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80119030.s")

/**
 * Draws either the analog three-day clock or the digital final-hours clock
 */
#ifdef NON_MATCHING
void Interface_DrawClock(PlayState* play) {
    static s16 sThreeDayClockAlpha = 255;
    static s16 D_801BFB30 = 0; // sClockAlphaTimer1
    static s16 D_801BFB34 = 0; // sClockAlphaTimer2
    static u16 sThreeDayClockHours[] = {
        CLOCK_TIME(0, 0),  CLOCK_TIME(1, 0),  CLOCK_TIME(2, 0),  CLOCK_TIME(3, 0),  CLOCK_TIME(4, 0),
        CLOCK_TIME(5, 0),  CLOCK_TIME(6, 0),  CLOCK_TIME(7, 0),  CLOCK_TIME(8, 0),  CLOCK_TIME(9, 0),
        CLOCK_TIME(10, 0), CLOCK_TIME(11, 0), CLOCK_TIME(12, 0), CLOCK_TIME(13, 0), CLOCK_TIME(14, 0),
        CLOCK_TIME(15, 0), CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), CLOCK_TIME(19, 0),
        CLOCK_TIME(20, 0), CLOCK_TIME(21, 0), CLOCK_TIME(22, 0), CLOCK_TIME(23, 0), CLOCK_TIME(24, 0) - 1,
    };
    static TexturePtr sThreeDayClockHourTextures[] = {
        gThreeDayClockHour12Tex, gThreeDayClockHour1Tex, gThreeDayClockHour2Tex,  gThreeDayClockHour3Tex,
        gThreeDayClockHour4Tex,  gThreeDayClockHour5Tex, gThreeDayClockHour6Tex,  gThreeDayClockHour7Tex,
        gThreeDayClockHour8Tex,  gThreeDayClockHour9Tex, gThreeDayClockHour10Tex, gThreeDayClockHour11Tex,
        gThreeDayClockHour12Tex, gThreeDayClockHour1Tex, gThreeDayClockHour2Tex,  gThreeDayClockHour3Tex,
        gThreeDayClockHour4Tex,  gThreeDayClockHour5Tex, gThreeDayClockHour6Tex,  gThreeDayClockHour7Tex,
        gThreeDayClockHour8Tex,  gThreeDayClockHour9Tex, gThreeDayClockHour10Tex, gThreeDayClockHour11Tex,
    };
    static s16 D_801BFBCC = 0;              // sClockInvDiamondPrimRed
    static s16 D_801BFBD0 = 0;              // sClockInvDiamondPrimGreen
    static s16 D_801BFBD4 = 255;            // sClockInvDiamondPrimBlue
    static s16 D_801BFBD8 = 0;              // sClockInvDiamondEnvRed
    static s16 D_801BFBDC = 0;              // sClockInvDiamondEnvGreen
    static s16 D_801BFBE0 = 0;              // sClockInvDiamondEnvBlue
    static s16 D_801BFBE4 = 15;             // sClockInvDiamondTimer
    static s16 D_801BFBE8 = 0;              // sClockInvDiamondTargetIndex
    static s16 D_801BFBEC[] = { 100, 0 };   // sClockInvDiamondPrimRedTargets
    static s16 D_801BFBF0[] = { 205, 155 }; // sClockInvDiamondPrimGreenTargets
    static s16 D_801BFBF4[] = { 255, 255 }; // sClockInvDiamondPrimBlueTargets
    static s16 D_801BFBF8[] = { 30, 0 };    // sClockInvDiamondEnvRedTargets
    static s16 D_801BFBFC[] = { 30, 0 };    // sClockInvDiamondEnvGreenTargets
    static s16 D_801BFC00[] = { 100, 0 };   // sClockInvDiamondEnvBlueTargets
    static s16 D_801BFC04[] = { 255, 0 };   // sFinalHoursClockDigitsRed
    static s16 D_801BFC08[] = { 100, 0 };   // sFinalHoursClockFrameEnvRedTargets
    static s16 D_801BFC0C[] = { 30, 0 };    // sFinalHoursClockFrameEnvGreenTargets
    static s16 D_801BFC10[] = { 100, 0 };   // sFinalHoursClockFrameEnvBlueTargets
    static TexturePtr sFinalHoursDigitTextures[] = {
        gFinalHoursClockDigit0Tex, gFinalHoursClockDigit1Tex, gFinalHoursClockDigit2Tex, gFinalHoursClockDigit3Tex,
        gFinalHoursClockDigit4Tex, gFinalHoursClockDigit5Tex, gFinalHoursClockDigit6Tex, gFinalHoursClockDigit7Tex,
        gFinalHoursClockDigit8Tex, gFinalHoursClockDigit9Tex, gFinalHoursClockColonTex,
    };
    // sFinalHoursDigitSlotPosXOffset
    static s16 D_801BFC40[] = {
        127, 136, 144, 151, 160, 168, 175, 184,
    };
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    MessageContext* msgCtx = &play->msgCtx;
    s16 sp1E6;
    f32 temp_f14;
    u32 timeUntilMoonCrash;
    f32 sp1D8;
    f32 timeInMinutes;
    f32 timeInSeconds;
    f32 sp1CC;
    s32 new_var;
    s16 sp1C6;
    s16 currentHour;
    u16 time;
    s16 temp;
    s16 colorStep;
    s16 finalHoursClockSlots[8]; // sp1AC
    s16 index;

    OPEN_DISPS(play->state.gfxCtx);

    if (R_TIME_SPEED != 0) {
        if ((msgCtx->msgMode == 0) || ((play->actorCtx.flags & ACTORCTX_FLAG_1) && !Play_InCsMode(play)) ||
            (msgCtx->msgMode == 0) || ((msgCtx->currentTextId >= 0x100) && (msgCtx->currentTextId <= 0x200)) ||
            (gSaveContext.gameMode == 3)) {
            if (!FrameAdvance_IsEnabled(&play->state) && !Environment_IsTimeStopped() && (gSaveContext.save.day < 4)) {
                /**
                 * Changes Clock's transparancy depending if Player is moving or not and possibly other things
                 */
                if (gSaveContext.hudVisibility == HUD_VISIBILITY_ALL) {
                    if (func_801234D4(play)) {
                        sThreeDayClockAlpha = 80;
                        D_801BFB30 = 5;
                        D_801BFB34 = 20;
                    } else if (D_801BFB34 != 0) {
                        D_801BFB34--;
                    } else if (D_801BFB30 != 0) {
                        colorStep = ABS_ALT(sThreeDayClockAlpha - 255) / D_801BFB30;
                        sThreeDayClockAlpha += colorStep;

                        if (sThreeDayClockAlpha >= 255) {
                            sThreeDayClockAlpha = 255;
                            D_801BFB30 = 0;
                        }
                    } else {
                        if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
                            sThreeDayClockAlpha = 255;
                        } else {
                            sThreeDayClockAlpha = interfaceCtx->bAlpha;
                        }
                        D_801BFB34 = 0;
                        D_801BFB30 = 0;
                    }
                } else {
                    if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
                        sThreeDayClockAlpha = 255;
                    } else {
                        sThreeDayClockAlpha = interfaceCtx->bAlpha;
                    }
                    D_801BFB34 = 0;
                    D_801BFB30 = 0;
                }

                if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {

                    func_8012C654(play->state.gfxCtx);

                    /**
                     * Draw Clock's Hour Lines
                     */
                    gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                    gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 130, 130, 130, sThreeDayClockAlpha);
                    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
                                      TEXEL0, 0, PRIMITIVE, 0);

                    OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gThreeDayClockHourLinesTex, 4, 64, 35, 96, 180, 128,
                                                     35, 1, 6, 0, 1 << 10, 1 << 10);

                    /**
                     * Draw Clock's Border
                     */
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, sThreeDayClockAlpha);
                    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
                                      TEXEL0, 0, PRIMITIVE, 0);

                    //! @bug A texture height of 50 is given below. The texture is only 48 units height
                    //!      resulting in this reading into the next texture. This results in a white
                    //!      dot in the bottom center of the clock. For the three-day clock, this is
                    //!      covered by the diamond. However, it can be seen by the final-hours clock.
                    OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gThreeDayClockBorderTex, 4, 64, 50, 96, 168, 128, 50,
                                                     1, 6, 0, 1 << 10, 1 << 10);

                    if (((CURRENT_DAY >= 4) || ((CURRENT_DAY == 3) && (((void)0, gSaveContext.save.time) >= 5) &&
                                                (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0))))) {
                        func_8012C8D4(play->state.gfxCtx);
                        gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    } else {
                        /**
                         * Draw Three-Day Clock's Diamond
                         */
                        gDPPipeSync(OVERLAY_DISP++);

                        // Time is slowed down to half speed with inverted song of time
                        if (gSaveContext.save.timeSpeedOffset == -2) {
                            // Clock diamond is blue and flashes white
                            colorStep = ABS_ALT(D_801BFBCC - D_801BFBEC[D_801BFBE8]) / D_801BFBE4;
                            if (D_801BFBCC >= D_801BFBEC[D_801BFBE8]) {
                                D_801BFBCC -= colorStep;
                            } else {
                                D_801BFBCC += colorStep;
                            }

                            colorStep = ABS_ALT(D_801BFBD0 - D_801BFBF0[D_801BFBE8]) / D_801BFBE4;
                            if (D_801BFBD0 >= D_801BFBF0[D_801BFBE8]) {
                                D_801BFBD0 -= colorStep;
                            } else {
                                D_801BFBD0 += colorStep;
                            }

                            colorStep = ABS_ALT(D_801BFBD4 - D_801BFBF4[D_801BFBE8]) / D_801BFBE4;
                            if (D_801BFBD4 >= D_801BFBF4[D_801BFBE8]) {
                                D_801BFBD4 -= colorStep;
                            } else {
                                D_801BFBD4 += colorStep;
                            }

                            colorStep = ABS_ALT(D_801BFBD8 - D_801BFBF8[D_801BFBE8]) / D_801BFBE4;
                            if (D_801BFBD8 >= D_801BFBF8[D_801BFBE8]) {
                                D_801BFBD8 -= colorStep;
                            } else {
                                D_801BFBD8 += colorStep;
                            }

                            colorStep = ABS_ALT(D_801BFBDC - D_801BFBFC[D_801BFBE8]) / D_801BFBE4;
                            if (D_801BFBDC >= D_801BFBFC[D_801BFBE8]) {
                                D_801BFBDC -= colorStep;
                            } else {
                                D_801BFBDC += colorStep;
                            }

                            colorStep = ABS_ALT(D_801BFBE0 - D_801BFC00[D_801BFBE8]) / D_801BFBE4;
                            if (D_801BFBE0 >= D_801BFC00[D_801BFBE8]) {
                                D_801BFBE0 -= colorStep;
                            } else {
                                D_801BFBE0 += colorStep;
                            }

                            D_801BFBE4--;

                            if (D_801BFBE4 == 0) {
                                D_801BFBCC = D_801BFBEC[D_801BFBE8];
                                D_801BFBD0 = D_801BFBF0[D_801BFBE8];
                                D_801BFBD4 = D_801BFBF4[D_801BFBE8];
                                D_801BFBD8 = D_801BFBF8[D_801BFBE8];
                                D_801BFBDC = D_801BFBFC[D_801BFBE8];
                                D_801BFBE0 = D_801BFC00[D_801BFBE8];
                                D_801BFBE4 = 15;
                                D_801BFBE8 ^= 1;
                            }

                            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0,
                                              PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0,
                                              PRIMITIVE, 0);
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, D_801BFBCC, D_801BFBD0, 255, sThreeDayClockAlpha);
                            gDPSetEnvColor(OVERLAY_DISP++, D_801BFBD8, D_801BFBDC, D_801BFBE0, 0);
                        } else {
                            // Clock diamond is green for regular timeSpeedOffset
                            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 170, 100, sThreeDayClockAlpha);
                        }

                        OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, gThreeDayClockDiamondTex, 40, 32, 140, 190, 40,
                                                          32, 1 << 10, 1 << 10);

                        /**
                         * Draw Three-Day Clock's Day-Number over Diamond
                         */
                        gDPPipeSync(OVERLAY_DISP++);
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);

                        OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, interfaceCtx->doActionSegment + 0x780, 48, 27,
                                                          137, 192, 48, 27, 1 << 10, 1 << 10);

                        /**
                         * Draw Three-Day Clock's Star (for the Minute Tracker)
                         */
                        gDPPipeSync(OVERLAY_DISP++);

                        if (D_801BF974 != 0) {
                            D_801BF980 += 0.02f;
                            D_801BF97C += 11;
                        } else {
                            D_801BF980 -= 0.02f;
                            D_801BF97C -= 11;
                        }

                        D_801BF978--;
                        if (D_801BF978 == 0) {
                            D_801BF978 = 10;
                            D_801BF974 ^= 1;
                        }

                        timeInSeconds = TIME_TO_SECONDS_F(gSaveContext.save.time);
                        timeInSeconds -= ((s16)(timeInSeconds / 3600.0f)) * 3600.0f;

                        func_8012C8D4(play->state.gfxCtx);

                        gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                        if (sThreeDayClockAlpha != 255) {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 110, sThreeDayClockAlpha);
                        } else {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 110, D_801BF97C);
                        }

                        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                        gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                        gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

                        Matrix_Translate(0.0f, -86.0f, 0.0f, MTXMODE_NEW);
                        Matrix_Scale(1.0f, 1.0f, D_801BF980, MTXMODE_APPLY);
                        Matrix_RotateZF(-(timeInSeconds * 0.0175f) / 10.0f, MTXMODE_APPLY);

                        gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[12], 4, 0);
                        gDPLoadTextureBlock_4b(OVERLAY_DISP++, gThreeDayClockStarMinuteTex, G_IM_FMT_I, 16, 16, 0,
                                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                        gSP1Quadrangle(OVERLAY_DISP++, 0, 2, 3, 1, 0);
                    }

                    /**
                     * Cuts off Three-Day Clock's Sun and Moon when they dip below the clock
                     */
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetScissorFrac(OVERLAY_DISP++, G_SC_NON_INTERLACE, 400, 620, 880,
                                      R_THREE_DAY_CLOCK_SUN_MOON_CUTOFF * 4.0f);

                    // determines the current hour
                    for (sp1C6 = 0; sp1C6 <= 24; sp1C6++) {
                        if (((void)0, gSaveContext.save.time) < sThreeDayClockHours[sp1C6 + 1]) {
                            break;
                        }
                    }

                    /**
                     * Draw Three-Day Clock's Sun (for the Day-Time Hours Tracker)
                     */
                    time = gSaveContext.save.time;
                    sp1D8 = Math_SinS(time) * -40.0f;
                    temp_f14 = Math_CosS(time) * -34.0f;

                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 100, 110, sThreeDayClockAlpha);

                    Matrix_Translate(sp1D8, temp_f14, 0.0f, MTXMODE_NEW);
                    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

                    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[16], 4, 0);

                    OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gThreeDayClockSunHourTex, 24, 24, 0);

                    /**
                     * Draw Three-Day Clock's Moon (for the Night-Time Hours Tracker)
                     */
                    sp1D8 = Math_SinS(time) * 40.0f;
                    temp_f14 = Math_CosS(time) * 34.0f;

                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 55, sThreeDayClockAlpha);

                    Matrix_Translate(sp1D8, temp_f14, 0.0f, MTXMODE_NEW);
                    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[20], 4, 0);

                    OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gThreeDayClockMoonHourTex, 24, 24, 0);

                    /**
                     * Cuts off Three-Day Clock's Hour Digits when they dip below the clock
                     */
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetScissorFrac(OVERLAY_DISP++, G_SC_NON_INTERLACE, 400, 620, 880,
                                      R_THREE_DAY_CLOCK_HOUR_DIGIT_CUTOFF * 4.0f);

                    /**
                     * Draws Three-Day Clock's Hour Digit Above the Sun
                     */
                    sp1CC = gSaveContext.save.time * 0.000096131f;

                    // Rotates Three-Day Clock's Hour Digit To Above the Sun
                    Matrix_Translate(0.0f, R_THREE_DAY_CLOCK_Y_POS / 10.0f, 0.0f, MTXMODE_NEW);
                    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                    Matrix_RotateZF(-(sp1CC - 3.15f), MTXMODE_APPLY);
                    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    // Draws Three-Day Clock's Hour Digit Above the Sun
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
                                      TEXEL0, 0, PRIMITIVE, 0);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, sThreeDayClockAlpha);
                    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[24], 8, 0);

                    OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sThreeDayClockHourTextures[sp1C6], 4, 16, 11, 0);

                    // Colours the Three-Day Clocks's Hour Digit Above the Sun
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);
                    gSP1Quadrangle(OVERLAY_DISP++, 4, 6, 7, 5, 0);

                    /**
                     * Draws Three-Day Clock's Hour Digit Above the Moon
                     */
                    // Rotates Three-Day Clock's Hour Digit To Above the Moon
                    Matrix_Translate(0.0f, R_THREE_DAY_CLOCK_Y_POS / 10.0f, 0.0f, MTXMODE_NEW);
                    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                    Matrix_RotateZF(-sp1CC, MTXMODE_APPLY);
                    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                    // Draws Three-Day Clock's Hour Digit Above the Moon
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
                                      TEXEL0, 0, PRIMITIVE, 0);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, sThreeDayClockAlpha);
                    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[32], 8, 0);

                    OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sThreeDayClockHourTextures[sp1C6], 4, 16, 11, 0);

                    // Colours the Three-Day Clocks's Hour Digit Above the Moon
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);
                    gSP1Quadrangle(OVERLAY_DISP++, 4, 6, 7, 5, 0);

                    gSPDisplayList(OVERLAY_DISP++, D_0E000000.setScissor);

                    // Final Hours
                    if ((CURRENT_DAY >= 4) || ((CURRENT_DAY == 3) && (((void)0, gSaveContext.save.time) >= 5) &&
                                               (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0)))) {
                        if (((void)0, gSaveContext.save.time) >= CLOCK_TIME(5, 0)) {
                            // The Final Hours clock will flash red

                            colorStep =
                                ABS_ALT(sFinalHoursClockDigitsRed - D_801BFC04[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                            if (sFinalHoursClockDigitsRed >= D_801BFC04[sFinalHoursClockColorTargetIndex]) {
                                sFinalHoursClockDigitsRed -= colorStep;
                            } else {
                                sFinalHoursClockDigitsRed += colorStep;
                            }

                            colorStep =
                                ABS_ALT(sFinalHoursClockFrameEnvRed - D_801BFC08[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                            if (sFinalHoursClockFrameEnvRed >= D_801BFC08[sFinalHoursClockColorTargetIndex]) {
                                sFinalHoursClockFrameEnvRed -= colorStep;
                            } else {
                                sFinalHoursClockFrameEnvRed += colorStep;
                            }

                            colorStep =
                                ABS_ALT(sFinalHoursClockFrameEnvGreen - D_801BFC0C[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                            if (sFinalHoursClockFrameEnvGreen >= D_801BFC0C[sFinalHoursClockColorTargetIndex]) {
                                sFinalHoursClockFrameEnvGreen -= colorStep;
                            } else {
                                sFinalHoursClockFrameEnvGreen += colorStep;
                            }

                            colorStep =
                                ABS_ALT(sFinalHoursClockFrameEnvBlue - D_801BFC10[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                            if (sFinalHoursClockFrameEnvBlue >= D_801BFC10[sFinalHoursClockColorTargetIndex]) {
                                sFinalHoursClockFrameEnvBlue -= colorStep;
                            } else {
                                sFinalHoursClockFrameEnvBlue += colorStep;
                            }

                            sFinalHoursClockColorTimer--;

                            if (sFinalHoursClockColorTimer == 0) {
                                sFinalHoursClockDigitsRed = D_801BFC04[sFinalHoursClockColorTargetIndex];
                                sFinalHoursClockFrameEnvRed = D_801BFC08[sFinalHoursClockColorTargetIndex];
                                sFinalHoursClockFrameEnvGreen = D_801BFC0C[sFinalHoursClockColorTargetIndex];
                                sFinalHoursClockFrameEnvBlue = D_801BFC10[sFinalHoursClockColorTargetIndex];
                                sFinalHoursClockColorTimer = 6;
                                sFinalHoursClockColorTargetIndex ^= 1;
                            }
                        }

                        sp1E6 = sThreeDayClockAlpha;
                        if (sp1E6 != 0) {
                            sp1E6 = 255;
                        }

                        func_8012C654(play->state.gfxCtx);

                        /**
                         * Draws Final-Hours Clock's Frame
                         */
                        gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                        gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0,
                                          PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0,
                                          PRIMITIVE, 0);
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 195, sp1E6);
                        gDPSetEnvColor(OVERLAY_DISP++, sFinalHoursClockFrameEnvRed, sFinalHoursClockFrameEnvGreen,
                                       sFinalHoursClockFrameEnvBlue, 0);

                        OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gFinalHoursClockFrameTex, 3, 80, 13, 119, 202,
                                                         80, 13, 0, 0, 0, 1 << 10, 1 << 10);

                        finalHoursClockSlots[0] = 0;

                        timeUntilMoonCrash = TIME_UNTIL_MOON_CRASH;

                        timeInMinutes = TIME_TO_MINUTES_F(timeUntilMoonCrash);

                        // digits for hours
                        finalHoursClockSlots[1] = timeInMinutes / 60.0f;
                        finalHoursClockSlots[2] = timeInMinutes / 60.0f;

                        temp = (s32)timeInMinutes % 60;

                        while (finalHoursClockSlots[1] >= 10) {
                            finalHoursClockSlots[0]++;
                            finalHoursClockSlots[1] -= 10;
                        }

                        // digits for minutes
                        finalHoursClockSlots[3] = 0;
                        finalHoursClockSlots[4] = temp;

                        while (finalHoursClockSlots[4] >= 10) {
                            finalHoursClockSlots[3]++;
                            finalHoursClockSlots[4] -= 10;
                        }

                        // digits for seconds
                        finalHoursClockSlots[6] = 0;
                        finalHoursClockSlots[7] =
                            timeUntilMoonCrash - (u32)((finalHoursClockSlots[2] * ((f32)0x10000 / 24)) +
                                                       (((void)0, temp) * ((f32)0x10000 / (24 * 60))));

                        while (finalHoursClockSlots[7] >= 10) {
                            finalHoursClockSlots[6]++;
                            finalHoursClockSlots[7] -= 10;
                        }

                        // Colon separating hours from minutes and minutes from seconds
                        finalHoursClockSlots[2] = finalHoursClockSlots[5] = 10;

                        /**
                         * Draws Final-Hours Clock's Digits
                         */
                        gDPPipeSync(OVERLAY_DISP++);
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sFinalHoursClockDigitsRed, 0, 0, sp1E6);
                        gDPSetEnvColor(OVERLAY_DISP++, sFinalHoursClockDigitsRed, 0, 0, 0);

                        for (sp1C6 = 0; sp1C6 < 8; sp1C6++) {
                            index = D_801BFC40[sp1C6];

                            OVERLAY_DISP =
                                Gfx_DrawTexRectI8(OVERLAY_DISP, sFinalHoursDigitTextures[finalHoursClockSlots[sp1C6]],
                                                  8, 8, index, 205, 8, 8, 1 << 10, 1 << 10);
                        }
                    }
                }
            }
        }
    }
    CLOSE_DISPS(play->state.gfxCtx);
}
#else
s16 sThreeDayClockAlpha = 255;
s16 D_801BFB30 = 0;
s16 D_801BFB34 = 0;
u16 sThreeDayClockHours[] = {
    CLOCK_TIME(0, 0),  CLOCK_TIME(1, 0),  CLOCK_TIME(2, 0),  CLOCK_TIME(3, 0),  CLOCK_TIME(4, 0),
    CLOCK_TIME(5, 0),  CLOCK_TIME(6, 0),  CLOCK_TIME(7, 0),  CLOCK_TIME(8, 0),  CLOCK_TIME(9, 0),
    CLOCK_TIME(10, 0), CLOCK_TIME(11, 0), CLOCK_TIME(12, 0), CLOCK_TIME(13, 0), CLOCK_TIME(14, 0),
    CLOCK_TIME(15, 0), CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), CLOCK_TIME(19, 0),
    CLOCK_TIME(20, 0), CLOCK_TIME(21, 0), CLOCK_TIME(22, 0), CLOCK_TIME(23, 0), CLOCK_TIME(24, 0) - 1,
};
TexturePtr sThreeDayClockHourTextures[] = {
    gThreeDayClockHour12Tex, gThreeDayClockHour1Tex, gThreeDayClockHour2Tex,  gThreeDayClockHour3Tex,
    gThreeDayClockHour4Tex,  gThreeDayClockHour5Tex, gThreeDayClockHour6Tex,  gThreeDayClockHour7Tex,
    gThreeDayClockHour8Tex,  gThreeDayClockHour9Tex, gThreeDayClockHour10Tex, gThreeDayClockHour11Tex,
    gThreeDayClockHour12Tex, gThreeDayClockHour1Tex, gThreeDayClockHour2Tex,  gThreeDayClockHour3Tex,
    gThreeDayClockHour4Tex,  gThreeDayClockHour5Tex, gThreeDayClockHour6Tex,  gThreeDayClockHour7Tex,
    gThreeDayClockHour8Tex,  gThreeDayClockHour9Tex, gThreeDayClockHour10Tex, gThreeDayClockHour11Tex,
};
s16 D_801BFBCC = 0;   // color R
s16 D_801BFBD0 = 155; // color G
s16 D_801BFBD4 = 255;
s16 D_801BFBD8 = 0;
s16 D_801BFBDC = 0;
s16 D_801BFBE0 = 0;
s16 D_801BFBE4 = 0xF;
u32 D_801BFBE8 = 0;
s16 D_801BFBEC[] = { 100, 0 };
s16 D_801BFBF0[] = { 205, 155 };
s16 D_801BFBF4[] = { 255, 255 };
s16 D_801BFBF8[] = { 30, 0 };
s16 D_801BFBFC[] = { 30, 0 };
s16 D_801BFC00[] = { 100, 0 };
s16 D_801BFC04[] = { 255, 0 };
s16 D_801BFC08[] = { 100, 0 };
s16 D_801BFC0C[] = { 30, 0 };
s16 D_801BFC10[] = { 100, 0 };
TexturePtr sFinalHoursDigitTextures[] = {
    gFinalHoursClockDigit0Tex, gFinalHoursClockDigit1Tex, gFinalHoursClockDigit2Tex, gFinalHoursClockDigit3Tex,
    gFinalHoursClockDigit4Tex, gFinalHoursClockDigit5Tex, gFinalHoursClockDigit6Tex, gFinalHoursClockDigit7Tex,
    gFinalHoursClockDigit8Tex, gFinalHoursClockDigit9Tex, gFinalHoursClockColonTex,
};
s16 D_801BFC40[] = {
    127, 136, 144, 151, 160, 168, 175, 184,
};
void Interface_DrawClock(PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/Interface_DrawClock.s")
#endif

void Interface_SetPerfectLetters(PlayState* play, s16 perfectLettersType) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 i;

    interfaceCtx->perfectLettersOn = true;
    interfaceCtx->perfectLettersType = perfectLettersType;

    interfaceCtx->perfectLettersPrimColor[0] = 255;
    interfaceCtx->perfectLettersPrimColor[1] = 165;
    interfaceCtx->perfectLettersPrimColor[2] = 55;
    interfaceCtx->perfectLettersPrimColor[3] = 255;
    interfaceCtx->perfectLettersColorTimer = 20;

    interfaceCtx->perfectLettersColorIndex = 0;
    interfaceCtx->perfectLettersCount = 1;
    interfaceCtx->perfectLettersTimer = 0;

    for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
        interfaceCtx->perfectLettersAngles[i] = 0;
        interfaceCtx->perfectLettersState[i] = interfaceCtx->perfectLettersOffsetX[i] = 0;
        if (interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_1) {
            interfaceCtx->perfectLettersSemiAxisX[i] = 140.0f;
            interfaceCtx->perfectLettersSemiAxisY[i] = 100.0f;
        } else {
            interfaceCtx->perfectLettersSemiAxisY[i] = 200.0f;
            interfaceCtx->perfectLettersSemiAxisX[i] = 200.0f;
        }
    }
    interfaceCtx->perfectLettersState[0] = PERFECT_LETTERS_STATE_INIT;
}

u16 sPerfectLettersType1OffScreenAngles[PERFECT_LETTERS_NUM_LETTERS] = {
    6 * PERFECT_LETTERS_ANGLE_PER_LETTER, // P
    7 * PERFECT_LETTERS_ANGLE_PER_LETTER, // E
    0 * PERFECT_LETTERS_ANGLE_PER_LETTER, // R
    1 * PERFECT_LETTERS_ANGLE_PER_LETTER, // F
    5 * PERFECT_LETTERS_ANGLE_PER_LETTER, // E
    4 * PERFECT_LETTERS_ANGLE_PER_LETTER, // C
    3 * PERFECT_LETTERS_ANGLE_PER_LETTER, // T
    2 * PERFECT_LETTERS_ANGLE_PER_LETTER, // !
};

s16 sPerfectLettersType1PrimColorTargets[2][3] = {
    { 255, 255, 255 },
    { 255, 165, 55 },
};

void Interface_UpdatePerfectLettersType1(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 i;
    s16 count;
    s16 colorStepR;
    s16 colorStepG;
    s16 colorStepB;

    // Update letter positions
    for (count = 0, i = 0; i < interfaceCtx->perfectLettersCount; i++, count += 4) {
        if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_INIT) {
            // Initialize letter positions along the elliptical spirals
            interfaceCtx->perfectLettersAngles[i] = sPerfectLettersType1OffScreenAngles[i] + 0xA000;
            interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_ENTER;
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_ENTER) {
            // Swirl inwards along elliptical spirals to form the spelt-out word
            interfaceCtx->perfectLettersAngles[i] -= 0x800;
            if (interfaceCtx->perfectLettersAngles[i] == sPerfectLettersType1OffScreenAngles[i]) {
                interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_STATIONARY;
            }
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_SPREAD) {
            // Swirl outwards along elliptical spirals offscreen
            interfaceCtx->perfectLettersAngles[i] -= 0x800;
            if (interfaceCtx->perfectLettersAngles[i] == (u16)(sPerfectLettersType1OffScreenAngles[i] - 0x8000)) {
                interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_OFF;
            }
        }
    }

    // Initialize the next letter in the list
    // if `perfectLettersCount == PERFECT_LETTERS_NUM_LETTERS`,
    // then perfectLettersState[] is accessed
    if ((interfaceCtx->perfectLettersState[interfaceCtx->perfectLettersCount] == PERFECT_LETTERS_STATE_OFF) &&
        (interfaceCtx->perfectLettersCount < PERFECT_LETTERS_NUM_LETTERS)) {
        interfaceCtx->perfectLettersState[interfaceCtx->perfectLettersCount] = PERFECT_LETTERS_STATE_INIT;

        interfaceCtx->perfectLettersSemiAxisX[interfaceCtx->perfectLettersCount] = 140.0f;
        interfaceCtx->perfectLettersSemiAxisY[interfaceCtx->perfectLettersCount] = 100.0f;
        interfaceCtx->perfectLettersAngles[interfaceCtx->perfectLettersCount] =
            sPerfectLettersType1OffScreenAngles[interfaceCtx->perfectLettersCount] + 0xA000;

        interfaceCtx->perfectLettersCount++;
    }

    // Update letter colors
    if ((interfaceCtx->perfectLettersCount == PERFECT_LETTERS_NUM_LETTERS) &&
        (interfaceCtx->perfectLettersState[PERFECT_LETTERS_NUM_LETTERS - 1] == PERFECT_LETTERS_STATE_STATIONARY)) {

        colorStepR = ABS_ALT(interfaceCtx->perfectLettersPrimColor[0] -
                             sPerfectLettersType1PrimColorTargets[interfaceCtx->perfectLettersColorIndex][0]) /
                     interfaceCtx->perfectLettersColorTimer;
        colorStepG = ABS_ALT(interfaceCtx->perfectLettersPrimColor[1] -
                             sPerfectLettersType1PrimColorTargets[interfaceCtx->perfectLettersColorIndex][1]) /
                     interfaceCtx->perfectLettersColorTimer;
        colorStepB = ABS_ALT(interfaceCtx->perfectLettersPrimColor[2] -
                             sPerfectLettersType1PrimColorTargets[interfaceCtx->perfectLettersColorIndex][2]) /
                     interfaceCtx->perfectLettersColorTimer;

        if (interfaceCtx->perfectLettersPrimColor[0] >=
            sPerfectLettersType1PrimColorTargets[interfaceCtx->perfectLettersColorIndex][0]) {
            interfaceCtx->perfectLettersPrimColor[0] -= colorStepR;
        } else {
            interfaceCtx->perfectLettersPrimColor[0] += colorStepR;
        }

        if (interfaceCtx->perfectLettersPrimColor[1] >=
            sPerfectLettersType1PrimColorTargets[interfaceCtx->perfectLettersColorIndex][1]) {
            interfaceCtx->perfectLettersPrimColor[1] -= colorStepG;
        } else {
            interfaceCtx->perfectLettersPrimColor[1] += colorStepG;
        }

        if (interfaceCtx->perfectLettersPrimColor[2] >=
            sPerfectLettersType1PrimColorTargets[interfaceCtx->perfectLettersColorIndex][2]) {
            interfaceCtx->perfectLettersPrimColor[2] -= colorStepB;
        } else {
            interfaceCtx->perfectLettersPrimColor[2] += colorStepB;
        }

        interfaceCtx->perfectLettersColorTimer--;

        if (interfaceCtx->perfectLettersColorTimer == 0) {
            interfaceCtx->perfectLettersColorTimer = 20;
            interfaceCtx->perfectLettersColorIndex ^= 1;
            interfaceCtx->perfectLettersTimer++;

            if (interfaceCtx->perfectLettersTimer == 6) {
                for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
                    interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_SPREAD;
                }
            }
        }
    }

    for (count = 0, i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
        if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_OFF) {
            count++;
        }
    }

    if (count == PERFECT_LETTERS_NUM_LETTERS) {
        interfaceCtx->perfectLettersOn = false;
    }
}

// Targets to offset each letter to properly spell "PERFECT!"
s16 sPerfectLettersType2SpellingOffsetsX[PERFECT_LETTERS_NUM_LETTERS] = {
    78,  // P
    54,  // E
    29,  // R
    5,   // F
    -18, // E
    -42, // C
    -67, // T
    -85, // !
};

// Targets to offset each letter to sweep horizontally offscreen
s16 sPerfectLettersType2OffScreenOffsetsX[PERFECT_LETTERS_NUM_LETTERS] = {
    180,  // P (offscreen left)
    180,  // E (offscreen left)
    180,  // R (offscreen left)
    180,  // F (offscreen left)
    -180, // E (offscreen right)
    -180, // C (offscreen right)
    -180, // T (offscreen right)
    -180, // ! (offscreen right)
};

s16 sPerfectLettersType2PrimColorTargets[2][3] = {
    { 255, 255, 255 },
    { 255, 165, 55 },
};

void Interface_UpdatePerfectLettersType2(PlayState* play) {
    s16 i;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 colorStepR;
    s16 colorStepG;
    s16 colorStepB;
    s16 colorStepA;
    s16 j = 0; // unused incrementer

    // Update letter positions
    for (i = 0; i < interfaceCtx->perfectLettersCount; i++, j += 4) {
        if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_INIT) {
            // Initialize letter positions along the elliptical spirals
            interfaceCtx->perfectLettersAngles[i] = i * (0x10000 / PERFECT_LETTERS_NUM_LETTERS);
            interfaceCtx->perfectLettersSemiAxisX[i] = 200.0f;
            interfaceCtx->perfectLettersSemiAxisY[i] = 200.0f;

            interfaceCtx->perfectLettersOffsetX[i] = 0;
            interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_ENTER;
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_ENTER) {
            // Swirl inwards along elliptical spirals to the center of the screen
            interfaceCtx->perfectLettersAngles[i] -= 0x800;
            interfaceCtx->perfectLettersSemiAxisX[i] -= 8.0f;
            interfaceCtx->perfectLettersSemiAxisY[i] -= 8.0f;

            if (interfaceCtx->perfectLettersSemiAxisX[i] <= 0.0f) {
                // The letter has reached the center of the screen
                interfaceCtx->perfectLettersSemiAxisY[i] = 0.0f;
                interfaceCtx->perfectLettersSemiAxisX[i] = 0.0f;
                interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_STATIONARY;

                if (i == (PERFECT_LETTERS_NUM_LETTERS - 1)) {
                    // The last letter has reached the center of the screen
                    interfaceCtx->perfectLettersColorTimer = 5;
                    interfaceCtx->perfectLettersState[0] = interfaceCtx->perfectLettersState[1] =
                        interfaceCtx->perfectLettersState[2] = interfaceCtx->perfectLettersState[3] =
                            interfaceCtx->perfectLettersState[4] = interfaceCtx->perfectLettersState[5] =
                                interfaceCtx->perfectLettersState[6] = interfaceCtx->perfectLettersState[7] =
                                    PERFECT_LETTERS_STATE_SPREAD;
                }
            }
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_SPREAD) {
            // Spread out the letters horizontally from the center to the spelt-out word
            colorStepR = ABS_ALT(interfaceCtx->perfectLettersOffsetX[i] - sPerfectLettersType2SpellingOffsetsX[i]) /
                         interfaceCtx->perfectLettersColorTimer;
            if (interfaceCtx->perfectLettersOffsetX[i] >= sPerfectLettersType2SpellingOffsetsX[i]) {
                interfaceCtx->perfectLettersOffsetX[i] -= colorStepR;
            } else {
                interfaceCtx->perfectLettersOffsetX[i] += colorStepR;
            }
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_EXIT) {
            // Spread out the letters horizontally from the spelt-out world to offscreen
            colorStepR = ABS_ALT(interfaceCtx->perfectLettersOffsetX[i] - sPerfectLettersType2OffScreenOffsetsX[i]) /
                         interfaceCtx->perfectLettersColorTimer;
            if (interfaceCtx->perfectLettersOffsetX[i] >= sPerfectLettersType2OffScreenOffsetsX[i]) {
                interfaceCtx->perfectLettersOffsetX[i] -= colorStepR;
            } else {
                interfaceCtx->perfectLettersOffsetX[i] += colorStepR;
            }
        }
    }

    if ((interfaceCtx->perfectLettersState[0] == PERFECT_LETTERS_STATE_SPREAD) ||
        (interfaceCtx->perfectLettersState[0] == PERFECT_LETTERS_STATE_EXIT)) {
        if (interfaceCtx->perfectLettersState[0] == PERFECT_LETTERS_STATE_EXIT) {
            colorStepA = interfaceCtx->perfectLettersPrimColor[3] / interfaceCtx->perfectLettersColorTimer;
            interfaceCtx->perfectLettersPrimColor[3] -= colorStepA;
        }
        interfaceCtx->perfectLettersColorTimer--;
        if (interfaceCtx->perfectLettersColorTimer == 0) {

            if (interfaceCtx->perfectLettersState[0] == PERFECT_LETTERS_STATE_SPREAD) {
                for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
                    interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_DISPLAY;
                }
                interfaceCtx->perfectLettersColorTimer = 20;
            } else {
                for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
                    interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_OFF;
                }
                interfaceCtx->perfectLettersOn = false;
            }
        }
    }

    // Initialize the next letter in the list
    if (interfaceCtx->perfectLettersState[interfaceCtx->perfectLettersCount] == PERFECT_LETTERS_STATE_OFF) {
        if (interfaceCtx->perfectLettersCount < PERFECT_LETTERS_NUM_LETTERS) {
            interfaceCtx->perfectLettersState[interfaceCtx->perfectLettersCount] = PERFECT_LETTERS_STATE_INIT;
            interfaceCtx->perfectLettersCount++;
        }
    }

    // Update letter colors
    if (interfaceCtx->perfectLettersCount == PERFECT_LETTERS_NUM_LETTERS) {
        if (interfaceCtx->perfectLettersState[PERFECT_LETTERS_NUM_LETTERS - 1] == PERFECT_LETTERS_STATE_DISPLAY) {

            colorStepR = ABS_ALT(interfaceCtx->perfectLettersPrimColor[0] -
                                 sPerfectLettersType2PrimColorTargets[interfaceCtx->perfectLettersColorIndex][0]) /
                         interfaceCtx->perfectLettersColorTimer;
            colorStepG = ABS_ALT(interfaceCtx->perfectLettersPrimColor[1] -
                                 sPerfectLettersType2PrimColorTargets[interfaceCtx->perfectLettersColorIndex][1]) /
                         interfaceCtx->perfectLettersColorTimer;
            colorStepB = ABS_ALT(interfaceCtx->perfectLettersPrimColor[2] -
                                 sPerfectLettersType2PrimColorTargets[interfaceCtx->perfectLettersColorIndex][2]) /
                         interfaceCtx->perfectLettersColorTimer;

            if (interfaceCtx->perfectLettersPrimColor[0] >=
                sPerfectLettersType2PrimColorTargets[interfaceCtx->perfectLettersColorIndex][0]) {
                interfaceCtx->perfectLettersPrimColor[0] -= colorStepR;
            } else {
                interfaceCtx->perfectLettersPrimColor[0] += colorStepR;
            }

            if (interfaceCtx->perfectLettersPrimColor[1] >=
                sPerfectLettersType2PrimColorTargets[interfaceCtx->perfectLettersColorIndex][1]) {
                interfaceCtx->perfectLettersPrimColor[1] -= colorStepG;
            } else {
                interfaceCtx->perfectLettersPrimColor[1] += colorStepG;
            }

            if (interfaceCtx->perfectLettersPrimColor[2] >=
                sPerfectLettersType2PrimColorTargets[interfaceCtx->perfectLettersColorIndex][2]) {
                interfaceCtx->perfectLettersPrimColor[2] -= colorStepB;
            } else {
                interfaceCtx->perfectLettersPrimColor[2] += colorStepB;
            }

            interfaceCtx->perfectLettersColorTimer--;
            if (interfaceCtx->perfectLettersColorTimer == 0) {
                interfaceCtx->perfectLettersColorTimer = 20;
                interfaceCtx->perfectLettersColorIndex ^= 1;
                interfaceCtx->perfectLettersTimer++;
                if (interfaceCtx->perfectLettersTimer == 6) {
                    for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
                        interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_EXIT;
                    }
                    interfaceCtx->perfectLettersColorTimer = 5;
                }
            }
        }
    }
}

// Targets to offset each letter to properly spell "PERFECT!"
s16 sPerfectLettersType3SpellingOffsetsX[PERFECT_LETTERS_NUM_LETTERS] = {
    78,  // P
    54,  // E
    29,  // R
    5,   // F
    -18, // E
    -42, // C
    -67, // T
    -85, // !
};

// Targets to sweep each letter's angle along an elliptical spiral offscreen
u16 sPerfectLettersType3OffScreenAngles[PERFECT_LETTERS_NUM_LETTERS] = {
    6 * PERFECT_LETTERS_ANGLE_PER_LETTER, // P
    7 * PERFECT_LETTERS_ANGLE_PER_LETTER, // E
    0 * PERFECT_LETTERS_ANGLE_PER_LETTER, // R
    1 * PERFECT_LETTERS_ANGLE_PER_LETTER, // F
    5 * PERFECT_LETTERS_ANGLE_PER_LETTER, // E
    4 * PERFECT_LETTERS_ANGLE_PER_LETTER, // C
    3 * PERFECT_LETTERS_ANGLE_PER_LETTER, // T
    2 * PERFECT_LETTERS_ANGLE_PER_LETTER, // !
};

s16 sPerfectLettersType3PrimColorTargets[2][3] = {
    { 255, 255, 255 },
    { 255, 165, 55 },
};

void Interface_UpdatePerfectLettersType3(PlayState* play) {
    s16 i;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 colorStepR;
    s16 colorStepG;
    s16 colorStepB;
    s16 j = 0;

    // Update letter positions
    for (i = 0; i < interfaceCtx->perfectLettersCount; i++, j += 4) {
        if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_INIT) {
            // Initialize letter positions along the elliptical spirals
            interfaceCtx->perfectLettersAngles[i] = i * (0x10000 / PERFECT_LETTERS_NUM_LETTERS);
            interfaceCtx->perfectLettersSemiAxisX[i] = 200.0f;
            interfaceCtx->perfectLettersSemiAxisY[i] = 200.0f;

            interfaceCtx->perfectLettersOffsetX[i] = 0;
            interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_ENTER;
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_ENTER) {
            // Swirl inwards along elliptical spirals to the center of the screen
            interfaceCtx->perfectLettersAngles[i] -= 0x800;
            interfaceCtx->perfectLettersSemiAxisX[i] -= 8.0f;
            interfaceCtx->perfectLettersSemiAxisY[i] -= 8.0f;

            if (interfaceCtx->perfectLettersSemiAxisX[i] <= 0.0f) {
                // The letter has reached the center of the screen
                interfaceCtx->perfectLettersSemiAxisY[i] = 0.0f;
                interfaceCtx->perfectLettersSemiAxisX[i] = 0.0f;
                interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_STATIONARY;

                if (i == (PERFECT_LETTERS_NUM_LETTERS - 1)) {
                    // The last letter has reached the center of the screen
                    interfaceCtx->perfectLettersColorTimer = 5;
                    interfaceCtx->perfectLettersState[0] = interfaceCtx->perfectLettersState[1] =
                        interfaceCtx->perfectLettersState[2] = interfaceCtx->perfectLettersState[3] =
                            interfaceCtx->perfectLettersState[4] = interfaceCtx->perfectLettersState[5] =
                                interfaceCtx->perfectLettersState[6] = interfaceCtx->perfectLettersState[7] =
                                    PERFECT_LETTERS_STATE_SPREAD;
                }
            }
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_SPREAD) {
            // Spread out the letters horizontally from the center to the spelt-out word
            colorStepR = ABS_ALT(interfaceCtx->perfectLettersOffsetX[i] - sPerfectLettersType3SpellingOffsetsX[i]) /
                         interfaceCtx->perfectLettersColorTimer;
            if (interfaceCtx->perfectLettersOffsetX[i] >= sPerfectLettersType3SpellingOffsetsX[i]) {
                interfaceCtx->perfectLettersOffsetX[i] -= colorStepR;
            } else {
                interfaceCtx->perfectLettersOffsetX[i] += colorStepR;
            }
        } else if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_EXIT) {
            // Swirl outwards along elliptical spirals offscreen
            interfaceCtx->perfectLettersAngles[i] -= 0x800;
            if (interfaceCtx->perfectLettersAngles[i] == (u16)(sPerfectLettersType3OffScreenAngles[i] - 0x8000)) {
                interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_OFF;
            }
        }
    }

    if (interfaceCtx->perfectLettersState[0] == PERFECT_LETTERS_STATE_SPREAD) {
        interfaceCtx->perfectLettersColorTimer--;
        if (interfaceCtx->perfectLettersColorTimer == 0) {
            for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
                interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_DISPLAY;
            }
            interfaceCtx->perfectLettersColorTimer = 20;
        }
    }

    // Initialize the next letter in the list
    if ((interfaceCtx->perfectLettersState[interfaceCtx->perfectLettersCount] == PERFECT_LETTERS_STATE_OFF) &&
        (interfaceCtx->perfectLettersCount < PERFECT_LETTERS_NUM_LETTERS)) {
        interfaceCtx->perfectLettersState[interfaceCtx->perfectLettersCount] = PERFECT_LETTERS_STATE_INIT;
        interfaceCtx->perfectLettersCount++;
    }

    // Update letter colors
    if ((interfaceCtx->perfectLettersCount == PERFECT_LETTERS_NUM_LETTERS) &&
        (interfaceCtx->perfectLettersState[PERFECT_LETTERS_NUM_LETTERS - 1] == PERFECT_LETTERS_STATE_DISPLAY)) {

        colorStepR = ABS_ALT(interfaceCtx->perfectLettersPrimColor[0] -
                             sPerfectLettersType3PrimColorTargets[interfaceCtx->perfectLettersColorIndex][0]) /
                     interfaceCtx->perfectLettersColorTimer;
        colorStepG = ABS_ALT(interfaceCtx->perfectLettersPrimColor[1] -
                             sPerfectLettersType3PrimColorTargets[interfaceCtx->perfectLettersColorIndex][1]) /
                     interfaceCtx->perfectLettersColorTimer;
        colorStepB = ABS_ALT(interfaceCtx->perfectLettersPrimColor[2] -
                             sPerfectLettersType3PrimColorTargets[interfaceCtx->perfectLettersColorIndex][2]) /
                     interfaceCtx->perfectLettersColorTimer;

        if (interfaceCtx->perfectLettersPrimColor[0] >=
            sPerfectLettersType3PrimColorTargets[interfaceCtx->perfectLettersColorIndex][0]) {
            interfaceCtx->perfectLettersPrimColor[0] -= colorStepR;
        } else {
            interfaceCtx->perfectLettersPrimColor[0] += colorStepR;
        }

        if (interfaceCtx->perfectLettersPrimColor[1] >=
            sPerfectLettersType3PrimColorTargets[interfaceCtx->perfectLettersColorIndex][1]) {
            interfaceCtx->perfectLettersPrimColor[1] -= colorStepG;
        } else {
            interfaceCtx->perfectLettersPrimColor[1] += colorStepG;
        }

        if (interfaceCtx->perfectLettersPrimColor[2] >=
            sPerfectLettersType3PrimColorTargets[interfaceCtx->perfectLettersColorIndex][2]) {
            interfaceCtx->perfectLettersPrimColor[2] -= colorStepB;
        } else {
            interfaceCtx->perfectLettersPrimColor[2] += colorStepB;
        }

        interfaceCtx->perfectLettersColorTimer--;
        if (interfaceCtx->perfectLettersColorTimer == 0) {
            interfaceCtx->perfectLettersColorTimer = 20;
            interfaceCtx->perfectLettersColorIndex ^= 1;
            interfaceCtx->perfectLettersTimer++;
            if (interfaceCtx->perfectLettersTimer == 6) {
                for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
                    interfaceCtx->perfectLettersSemiAxisX[i] = 140.0f;
                    interfaceCtx->perfectLettersSemiAxisY[i] = 100.0f;
                    interfaceCtx->perfectLettersAngles[i] = sPerfectLettersType3OffScreenAngles[i];
                    interfaceCtx->perfectLettersState[i] = PERFECT_LETTERS_STATE_EXIT;
                }
                interfaceCtx->perfectLettersColorTimer = 5;
            }
        }
    }

    j = 0;
    for (i = 0; i < PERFECT_LETTERS_NUM_LETTERS; i++) {
        if (interfaceCtx->perfectLettersState[i] == PERFECT_LETTERS_STATE_OFF) {
            j++;
        }
    }

    if (j == PERFECT_LETTERS_NUM_LETTERS) {
        interfaceCtx->perfectLettersOn = false;
    }
}

TexturePtr sPerfectLettersTextures[PERFECT_LETTERS_NUM_LETTERS] = {
    gPerfectLetterPTex, gPerfectLetterETex, gPerfectLetterRTex, gPerfectLetterFTex,
    gPerfectLetterETex, gPerfectLetterCTex, gPerfectLetterTTex, gPerfectLetterExclamationTex,
};

void Interface_DrawPerfectLetters(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    f32 letterX;
    f32 letterY;
    s16 i;
    s16 vtxOffset;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C8D4(play->state.gfxCtx);

    gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);

    for (vtxOffset = 0, i = 0; i < PERFECT_LETTERS_NUM_LETTERS; vtxOffset += 4, i++) {
        if (interfaceCtx->perfectLettersState[i] != PERFECT_LETTERS_STATE_OFF) {

            // The positions follow the path of an elliptical spiral
            letterX = Math_SinS(interfaceCtx->perfectLettersAngles[i]) * interfaceCtx->perfectLettersSemiAxisX[i];
            letterY = Math_CosS(interfaceCtx->perfectLettersAngles[i]) * interfaceCtx->perfectLettersSemiAxisY[i];

            // Draw Minigame Perfect Shadows
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->perfectLettersPrimColor[3]);

            Matrix_Translate(letterX, letterY, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[44 + vtxOffset], 4, 0);

            OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sPerfectLettersTextures[i], 4, 32, 33, 0);

            // Draw Minigame Perfect Colored Letters
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, interfaceCtx->perfectLettersPrimColor[0],
                            interfaceCtx->perfectLettersPrimColor[1], interfaceCtx->perfectLettersPrimColor[2],
                            interfaceCtx->perfectLettersPrimColor[3]);

            Matrix_Translate(letterX, letterY, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[76 + vtxOffset], 4, 0);

            OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sPerfectLettersTextures[i], 4, 32, 33, 0);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Interface_StartMoonCrash(PlayState* play) {
    if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
        Audio_QueueSeqCmd(0xE0000100);
    }

    gSaveContext.save.day = 4;
    gSaveContext.save.daysElapsed = 4;
    gSaveContext.save.time = CLOCK_TIME(6, 0) + 10;
    play->nextEntrance = ENTRANCE(TERMINA_FIELD, 12);
    gSaveContext.nextCutsceneIndex = 0;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_03;
}

void Interface_GetTimerDigits(u64 timer, s16* timerArr) {
    u64 time = timer;

    // 6 minutes
    timerArr[0] = time / SECONDS_TO_TIMER(360);
    time -= timerArr[0] * SECONDS_TO_TIMER(360);

    // minutes
    timerArr[1] = time / SECONDS_TO_TIMER(60);
    time -= timerArr[1] * SECONDS_TO_TIMER(60);

    // 10 seconds
    timerArr[3] = time / SECONDS_TO_TIMER(10);
    time -= timerArr[3] * SECONDS_TO_TIMER(10);

    // seconds
    timerArr[4] = time / SECONDS_TO_TIMER(1);
    time -= timerArr[4] * SECONDS_TO_TIMER(1);

    // 100 milliseconds
    timerArr[6] = time / SECONDS_TO_TIMER_PRECISE(0, 10);
    time -= timerArr[6] * SECONDS_TO_TIMER_PRECISE(0, 10);

    // 10 milliseconds
    timerArr[7] = time;
}

#define IS_POSTMAN_TIMER_DRAWN                                                        \
    (((sTimerId == TIMER_ID_POSTMAN) &&                                               \
      (gSaveContext.timerStates[TIMER_ID_POSTMAN] == TIMER_STATE_POSTMAN_COUNTING) && \
      (sPostmanBunnyHoodState == POSTMAN_MINIGAME_BUNNY_HOOD_OFF) &&                  \
      (gSaveContext.timerCurTimes[TIMER_ID_POSTMAN] < SECONDS_TO_TIMER(3))) ||        \
     (sPostmanBunnyHoodState == POSTMAN_MINIGAME_BUNNY_HOOD_ON))

/**
 * Update and draw the timers
 */
void Interface_DrawTimers(PlayState* play) {
    static s16 sTimerStateTimer = 0;
    static s16 sTimerDigits[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    static s16 sTimerBeepSfxSeconds = 99;
    static s16 sTimerDigitsOffsetX[] = {
        16, 25, 34, 42, 51, 60, 68, 77,
    };
    static s16 sTimerDigitsWidth[] = {
        9, 9, 8, 9, 9, 8, 9, 9,
    };
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);
    OSTime osTime;
    OSTime postmanTimerStopOsTime;
    s16 j;
    s16 i;

    OPEN_DISPS(play->state.gfxCtx);

    // Not satisfying any of these conditions will pause the timer
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) &&
        (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
        ((msgCtx->msgMode == 0) ||
         ((msgCtx->msgMode != 0) && (msgCtx->currentTextId >= 0x1BB2) && (msgCtx->currentTextId <= 0x1BB6))) &&
        !(player->stateFlags1 & PLAYER_STATE1_200) && (play->transitionTrigger == TRANS_TRIGGER_OFF) &&
        (play->transitionMode == TRANS_MODE_OFF) && !Play_InCsMode(play)) {

        // Account for osTime when the timer is paused
        if (sIsTimerPaused) {
            osTime = osGetTime();

            for (j = 0; j < TIMER_ID_MAX; j++) {
                if (gSaveContext.timerStates[j] == TIMER_STATE_COUNTING) {
                    gSaveContext.timerPausedOsTimes[j] =
                        gSaveContext.timerPausedOsTimes[j] + (osTime - sTimerPausedOsTime);
                }
            }
            sIsTimerPaused = false;
        }

        sTimerId = TIMER_ID_NONE;

        // Update all timer states
        for (i = 0; i < TIMER_ID_MAX; i++) {
            if (gSaveContext.timerStates[i] == TIMER_STATE_OFF) {
                continue;
            }

            sTimerId = i;

            // Process the timer for the postman counting minigame
            if (sTimerId == TIMER_ID_POSTMAN) {
                switch (gSaveContext.timerStates[TIMER_ID_POSTMAN]) {
                    case TIMER_STATE_POSTMAN_START:
                        if (gSaveContext.timerDirections[TIMER_ID_POSTMAN] != TIMER_COUNT_DOWN) {
                            gSaveContext.timerStartOsTimes[TIMER_ID_POSTMAN] = osGetTime();
                        }
                        gSaveContext.timerStates[TIMER_ID_POSTMAN] = TIMER_STATE_POSTMAN_COUNTING;
                        sPostmanTimerInputBtnAPressed = true;
                        func_80174F7C(Interface_PostmanTimerCallback, NULL);
                        break;

                    case TIMER_STATE_POSTMAN_STOP:
                        postmanTimerStopOsTime = gSaveContext.postmanTimerStopOsTime;
                        gSaveContext.timerCurTimes[TIMER_ID_POSTMAN] = OSTIME_TO_TIMER(
                            postmanTimerStopOsTime - ((void)0, gSaveContext.timerStartOsTimes[TIMER_ID_POSTMAN]) -
                            ((void)0, gSaveContext.timerPausedOsTimes[TIMER_ID_POSTMAN]));
                        gSaveContext.timerStates[TIMER_ID_POSTMAN] = TIMER_STATE_POSTMAN_END;
                        func_80174F9C(Interface_PostmanTimerCallback, NULL);
                        break;

                    case TIMER_STATE_POSTMAN_COUNTING:
                    case TIMER_STATE_POSTMAN_END:
                        break;
                }
                break;
            }

            // process the remaining timers
            switch (gSaveContext.timerStates[sTimerId]) {
                case TIMER_STATE_START:
                case TIMER_STATE_ALT_START:
                    sTimerStateTimer = 20;
                    if (interfaceCtx->minigameState != MINIGAME_STATE_NONE) {

                        // Set the timer position
                        gSaveContext.timerX[sTimerId] = 26;

                        if (interfaceCtx->magicAlpha != 255) {
                            gSaveContext.timerY[sTimerId] = 22;
                        } else if (gSaveContext.save.playerData.healthCapacity > 0xA0) {
                            gSaveContext.timerY[sTimerId] = 54;
                        } else {
                            gSaveContext.timerY[sTimerId] = 46;
                        }

                        if ((interfaceCtx->minigameState == MINIGAME_STATE_COUNTDOWN_GO) ||
                            (interfaceCtx->minigameState == MINIGAME_STATE_PLAYING)) {
                            if (gSaveContext.timerStates[sTimerId] == TIMER_STATE_START) {
                                gSaveContext.timerStates[sTimerId] = TIMER_STATE_COUNTING;
                            } else {
                                gSaveContext.timerStates[sTimerId] = TIMER_STATE_ALT_COUNTING;
                                D_801BF8F8[sTimerId] = osGetTime();
                                D_801BF930[sTimerId] = 0;
                            }

                            gSaveContext.timerStartOsTimes[sTimerId] = osGetTime();
                            gSaveContext.timerStopTimes[sTimerId] = SECONDS_TO_TIMER(0);
                            gSaveContext.timerPausedOsTimes[sTimerId] = 0;
                        }
                    } else {
                        gSaveContext.timerStates[sTimerId] = TIMER_STATE_HOLD_TIMER;
                    }
                    break;

                case TIMER_STATE_HOLD_TIMER:
                    sTimerStateTimer--;
                    if (sTimerStateTimer == 0) {
                        sTimerStateTimer = 20;
                        gSaveContext.timerStates[sTimerId] = TIMER_STATE_MOVING_TIMER;
                    }
                    break;

                case TIMER_STATE_MOVING_TIMER:
                    // Move the timer from the center of the screen to the timer location where it will count.
                    if (sTimerId == TIMER_ID_MOON_CRASH) {
                        j = ((((void)0, gSaveContext.timerX[sTimerId]) - R_MOON_CRASH_TIMER_X) / sTimerStateTimer);
                        gSaveContext.timerX[sTimerId] = ((void)0, gSaveContext.timerX[sTimerId]) - j;
                        j = ((((void)0, gSaveContext.timerY[sTimerId]) - R_MOON_CRASH_TIMER_Y) / sTimerStateTimer);
                        gSaveContext.timerY[sTimerId] = ((void)0, gSaveContext.timerY[sTimerId]) - j;
                    } else {
                        j = ((((void)0, gSaveContext.timerX[sTimerId]) - 26) / sTimerStateTimer);
                        gSaveContext.timerX[sTimerId] = ((void)0, gSaveContext.timerX[sTimerId]) - j;

                        j = (gSaveContext.save.playerData.healthCapacity > 0xA0)
                                ? ((((void)0, gSaveContext.timerY[sTimerId]) - 54) / sTimerStateTimer)
                                : ((((void)0, gSaveContext.timerY[sTimerId]) - 46) / sTimerStateTimer);
                        gSaveContext.timerY[sTimerId] = ((void)0, gSaveContext.timerY[sTimerId]) - j;
                    }

                    sTimerStateTimer--;
                    if (sTimerStateTimer == 0) {
                        sTimerStateTimer = 20;

                        if (sTimerId == TIMER_ID_MOON_CRASH) {
                            gSaveContext.timerY[sTimerId] = R_MOON_CRASH_TIMER_Y;
                        } else {
                            gSaveContext.timerX[sTimerId] = 26;
                            if (gSaveContext.save.playerData.healthCapacity > 0xA0) {
                                gSaveContext.timerY[sTimerId] = 54;
                            } else {
                                gSaveContext.timerY[sTimerId] = 46;
                            }
                        }

                        gSaveContext.timerStates[sTimerId] = TIMER_STATE_COUNTING;
                        gSaveContext.timerStartOsTimes[sTimerId] = osGetTime();
                        gSaveContext.timerStopTimes[sTimerId] = SECONDS_TO_TIMER(0);
                        gSaveContext.timerPausedOsTimes[sTimerId] = 0;
                    }
                    // fallthrough
                case TIMER_STATE_COUNTING:
                    if ((gSaveContext.timerStates[sTimerId] == TIMER_STATE_COUNTING) &&
                        (sTimerId == TIMER_ID_MOON_CRASH)) {
                        gSaveContext.timerX[TIMER_ID_MOON_CRASH] = R_MOON_CRASH_TIMER_X;
                        gSaveContext.timerY[TIMER_ID_MOON_CRASH] = R_MOON_CRASH_TIMER_Y;
                    }
                    break;

                case TIMER_STATE_10:
                    D_801BF8F8[sTimerId] = osGetTime();
                    D_801BF930[sTimerId] = 0;
                    gSaveContext.timerStates[sTimerId] = TIMER_STATE_ALT_COUNTING;
                    // fallthrough
                case TIMER_STATE_ALT_COUNTING:
                    D_801BF930[sTimerId] = osGetTime() - D_801BF8F8[sTimerId];
                    break;

                case TIMER_STATE_12:
                    osTime = osGetTime();

                    gSaveContext.timerPausedOsTimes[sTimerId] =
                        gSaveContext.timerPausedOsTimes[sTimerId] + osTime - D_801BF8F8[sTimerId];
                    D_801BF930[sTimerId] = 0;
                    gSaveContext.timerStates[sTimerId] = TIMER_STATE_COUNTING;
                    break;

                case TIMER_STATE_ENV_HAZARD_START:
                    gSaveContext.timerCurTimes[sTimerId] = SECONDS_TO_TIMER(gSaveContext.save.playerData.health >> 1);
                    gSaveContext.timerDirections[sTimerId] = TIMER_COUNT_DOWN;
                    gSaveContext.timerTimeLimits[sTimerId] = gSaveContext.timerCurTimes[sTimerId];
                    sTimerStateTimer = 20;
                    gSaveContext.timerStates[sTimerId] = TIMER_STATE_MOVING_TIMER;
                    break;

                case TIMER_STATE_STOP:
                    osTime = osGetTime();

                    gSaveContext.timerStopTimes[sTimerId] =
                        OSTIME_TO_TIMER(osTime - ((void)0, gSaveContext.timerStartOsTimes[sTimerId]) -
                                        ((void)0, gSaveContext.timerPausedOsTimes[sTimerId]));

                    gSaveContext.timerStates[sTimerId] = TIMER_STATE_OFF;

                    if (sTimerId == TIMER_ID_MOON_CRASH) {
                        gSaveContext.save.day = 4;
                        if ((play->sceneId == SCENE_OKUJOU) && (gSaveContext.sceneLayer == 3)) {
                            play->nextEntrance = ENTRANCE(TERMINA_FIELD, 1);
                            gSaveContext.nextCutsceneIndex = 0xFFF0;
                            play->transitionTrigger = TRANS_TRIGGER_START;
                        } else {
                            Interface_StartMoonCrash(play);
                        }
                    } else if (gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] != TIMER_STATE_OFF) {
                        gSaveContext.timerX[TIMER_ID_GORON_RACE_UNUSED] = 115;
                        gSaveContext.timerY[TIMER_ID_GORON_RACE_UNUSED] = 80;
                        if (gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] <= TIMER_STATE_10) {
                            gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] = TIMER_STATE_MOVING_TIMER;
                        }
                    }
                    break;

                case TIMER_STATE_6:
                    osTime = osGetTime();

                    gSaveContext.timerStopTimes[sTimerId] =
                        OSTIME_TO_TIMER(osTime - ((void)0, gSaveContext.timerStartOsTimes[sTimerId]) -
                                        ((void)0, gSaveContext.timerPausedOsTimes[sTimerId]));

                    if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) &&
                        (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                        if (gSaveContext.timerStopTimes[sTimerId] >= SECONDS_TO_TIMER(120)) {
                            gSaveContext.timerStopTimes[sTimerId] = SECONDS_TO_TIMER(120);
                            gSaveContext.timerCurTimes[sTimerId] = SECONDS_TO_TIMER(120);
                        }
                    } else if (CHECK_EVENTINF(EVENTINF_34) && (play->sceneId == SCENE_DEKUTES) &&
                               (gSaveContext.timerStopTimes[sTimerId] >= SECONDS_TO_TIMER(120))) {
                        gSaveContext.timerCurTimes[sTimerId] = SECONDS_TO_TIMER(120);
                    }
                    gSaveContext.timerStates[sTimerId] = TIMER_STATE_7;

                    if (gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] != TIMER_STATE_OFF) {
                        gSaveContext.timerX[TIMER_ID_GORON_RACE_UNUSED] = 115;
                        gSaveContext.timerY[TIMER_ID_GORON_RACE_UNUSED] = 80;
                        if (gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] <= TIMER_STATE_10) {
                            gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] = TIMER_STATE_MOVING_TIMER;
                        }
                        gSaveContext.timerStates[sTimerId] = TIMER_STATE_OFF;
                    }
                    break;
            }
            break;
        }

        // Update timer counting
        if ((sTimerId != TIMER_ID_NONE) && gSaveContext.timerStates[sTimerId]) { // != TIMER_STATE_OFF
            if (gSaveContext.timerDirections[sTimerId] == TIMER_COUNT_DOWN) {
                sTimerDigits[0] = sTimerDigits[1] = sTimerDigits[3] = sTimerDigits[4] = sTimerDigits[6] = 0;

                // Used to index the counter colon
                sTimerDigits[2] = sTimerDigits[5] = 10;

                // Get the total amount of unpaused time since the start of the timer, centiseconds (1/100th sec).
                if ((gSaveContext.timerStates[sTimerId] == TIMER_STATE_COUNTING) ||
                    (gSaveContext.timerStates[sTimerId] == TIMER_STATE_10) ||
                    (gSaveContext.timerStates[sTimerId] == TIMER_STATE_ALT_COUNTING) ||
                    (gSaveContext.timerStates[sTimerId] == TIMER_STATE_POSTMAN_COUNTING)) {
                    osTime = osGetTime();

                    osTime =
                        OSTIME_TO_TIMER(osTime - ((void)0, gSaveContext.timerPausedOsTimes[sTimerId]) -
                                        D_801BF930[sTimerId] - ((void)0, gSaveContext.timerStartOsTimes[sTimerId]));
                } else if (gSaveContext.timerStates[sTimerId] == TIMER_STATE_7) {
                    osTime = gSaveContext.timerStopTimes[sTimerId];
                } else {
                    osTime = 0;
                }

                // Check how much unpaused time has passed
                if (osTime == 0) {
                    // No unpaused time has passed since the start of the timer.
                    gSaveContext.timerCurTimes[sTimerId] = gSaveContext.timerTimeLimits[sTimerId] - osTime;
                } else if (osTime <= gSaveContext.timerTimeLimits[sTimerId]) {
                    // Time has passed, but the time limit has not been exceeded
                    if (osTime >= gSaveContext.timerTimeLimits[sTimerId]) {
                        // The time is exactly at the time limit. No time remaining.
                        gSaveContext.timerCurTimes[sTimerId] = SECONDS_TO_TIMER(0);
                    } else {
                        // Update the time remaining
                        gSaveContext.timerCurTimes[sTimerId] = gSaveContext.timerTimeLimits[sTimerId] - osTime;
                    }
                } else {
                    // Time has passed, and the time limit has been exceeded.
                    gSaveContext.timerCurTimes[sTimerId] = SECONDS_TO_TIMER(0);
                    gSaveContext.timerStates[sTimerId] = TIMER_STATE_STOP;
                    if (sEnvTimerActive) {
                        gSaveContext.save.playerData.health = 0;
                        play->damagePlayer(play, -(((void)0, gSaveContext.save.playerData.health) + 2));
                    }
                    sEnvTimerActive = false;
                }

                Interface_GetTimerDigits(((void)0, gSaveContext.timerCurTimes[sTimerId]), sTimerDigits);

                // Use seconds to determine when to beep
                if (gSaveContext.timerCurTimes[sTimerId] > SECONDS_TO_TIMER(60)) {
                    if ((sTimerBeepSfxSeconds != sTimerDigits[4]) && (sTimerDigits[4] == 1)) {
                        play_sound(NA_SE_SY_MESSAGE_WOMAN);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                } else if (gSaveContext.timerCurTimes[sTimerId] > SECONDS_TO_TIMER(10)) {
                    if ((sTimerBeepSfxSeconds != sTimerDigits[4]) && ((sTimerDigits[4] % 2) != 0)) {
                        play_sound(NA_SE_SY_WARNING_COUNT_N);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                } else if (sTimerBeepSfxSeconds != sTimerDigits[4]) {
                    play_sound(NA_SE_SY_WARNING_COUNT_E);
                    sTimerBeepSfxSeconds = sTimerDigits[4];
                }
            } else { // TIMER_COUNT_UP
                sTimerDigits[0] = sTimerDigits[1] = sTimerDigits[3] = sTimerDigits[4] = sTimerDigits[6] = 0;

                // Used to index the counter colon
                sTimerDigits[2] = sTimerDigits[5] = 10;

                // Get the total amount of unpaused time since the start of the timer, centiseconds (1/100th sec).
                if ((gSaveContext.timerStates[sTimerId] == TIMER_STATE_COUNTING) ||
                    (gSaveContext.timerStates[sTimerId] == TIMER_STATE_POSTMAN_COUNTING)) {
                    osTime = osGetTime();
                    osTime =
                        OSTIME_TO_TIMER(osTime - ((void)0, gSaveContext.timerStartOsTimes[sTimerId]) -
                                        ((void)0, gSaveContext.timerPausedOsTimes[sTimerId]) - D_801BF930[sTimerId]);
                } else if (gSaveContext.timerStates[sTimerId] == TIMER_STATE_7) {
                    osTime = gSaveContext.timerStopTimes[sTimerId];
                } else if (sTimerId == TIMER_ID_POSTMAN) {
                    osTime = gSaveContext.timerCurTimes[sTimerId];
                } else {
                    osTime = SECONDS_TO_TIMER(0);
                }

                if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) &&
                    (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                    if (osTime >= SECONDS_TO_TIMER(120)) {
                        osTime = SECONDS_TO_TIMER(120);
                    }
                } else if (CHECK_EVENTINF(EVENTINF_34) && (play->sceneId == SCENE_DEKUTES) &&
                           (osTime >= SECONDS_TO_TIMER(120))) {
                    osTime = SECONDS_TO_TIMER(120);
                }

                // Update the time remaining with the total amount of time since the start of the timer,
                gSaveContext.timerCurTimes[sTimerId] = osTime;

                Interface_GetTimerDigits(osTime, sTimerDigits);

                // Use seconds to determine when to beep
                if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) &&
                    (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                    if ((gSaveContext.timerCurTimes[sTimerId] > SECONDS_TO_TIMER(110)) &&
                        (sTimerBeepSfxSeconds != sTimerDigits[4])) {
                        play_sound(NA_SE_SY_WARNING_COUNT_E);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                } else if (CHECK_EVENTINF(EVENTINF_34) && (play->sceneId == SCENE_DEKUTES)) {
                    if ((((void)0, gSaveContext.timerCurTimes[sTimerId]) >
                         (gSaveContext.save.dekuPlaygroundHighScores[CURRENT_DAY - 1] - SECONDS_TO_TIMER(9))) &&
                        (sTimerBeepSfxSeconds != sTimerDigits[4])) {
                        play_sound(NA_SE_SY_WARNING_COUNT_E);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                }
            }

            // Draw timer
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 0);
            OVERLAY_DISP = Gfx_DrawTexRectIA8(
                OVERLAY_DISP, gTimerClockIconTex, 0x10, 0x10, ((void)0, gSaveContext.timerX[sTimerId]),
                ((void)0, gSaveContext.timerY[sTimerId]) + 2, 0x10, 0x10, 1 << 10, 1 << 10);
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);

            if (IS_POSTMAN_TIMER_DRAWN || (gSaveContext.timerStates[sTimerId] <= TIMER_STATE_12)) {
                // Set the timer color
                if (gSaveContext.timerStates[sTimerId]) { // != TIMER_STATE_OFF
                    if (sTimerId == TIMER_ID_2) {
                        if ((gSaveContext.timerCurTimes[sTimerId] == SECONDS_TO_TIMER(0)) ||
                            (gSaveContext.timerStates[sTimerId] == TIMER_STATE_COUNTING)) {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 50, 0, 255);
                        } else {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
                        }
                    } else if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) &&
                               (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                        if (gSaveContext.timerCurTimes[sTimerId] >= SECONDS_TO_TIMER(110)) {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 50, 0, 255);
                        } else {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
                        }
                    } else if (CHECK_EVENTINF(EVENTINF_34) && (play->sceneId == SCENE_DEKUTES)) {
                        if (((void)0, gSaveContext.timerCurTimes[sTimerId]) >=
                            gSaveContext.save.dekuPlaygroundHighScores[CURRENT_DAY - 1]) {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 50, 0, 255);
                        } else if (((void)0, gSaveContext.timerCurTimes[sTimerId]) >=
                                   (gSaveContext.save.dekuPlaygroundHighScores[CURRENT_DAY - 1] -
                                    SECONDS_TO_TIMER(9))) {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 0, 255);
                        } else {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
                        }
                    } else if ((gSaveContext.timerCurTimes[sTimerId] < SECONDS_TO_TIMER(10)) &&
                               (gSaveContext.timerDirections[sTimerId] == TIMER_COUNT_DOWN) &&
                               (gSaveContext.timerStates[sTimerId] != TIMER_STATE_ALT_COUNTING)) {
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 50, 0, 255);
                    } else {
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
                    }
                }

                // Draw the timer
                if (sTimerId == TIMER_ID_POSTMAN) {
                    if (sPostmanBunnyHoodState == POSTMAN_MINIGAME_BUNNY_HOOD_ON) {
                        // draw sTimerDigits[3] (10s of seconds) to sTimerDigits[6] (100s of milliseconds)
                        for (j = 0; j < 4; j++) {
                            OVERLAY_DISP = Gfx_DrawTexRectI8(
                                OVERLAY_DISP, ((u8*)gCounterDigit0Tex + (8 * 16 * sTimerDigits[j + 3])), 8, 0x10,
                                ((void)0, gSaveContext.timerX[sTimerId]) + sTimerDigitsOffsetX[j],
                                ((void)0, gSaveContext.timerY[sTimerId]), sTimerDigitsWidth[j], 0xFA, 0x370, 0x370);
                        }
                    } else {
                        // draw sTimerDigits[3] (10s of seconds) to sTimerDigits[7] (10s of milliseconds)
                        for (j = 0; j < 5; j++) {
                            OVERLAY_DISP = Gfx_DrawTexRectI8(
                                OVERLAY_DISP, ((u8*)gCounterDigit0Tex + (8 * 16 * sTimerDigits[j + 3])), 8, 0x10,
                                ((void)0, gSaveContext.timerX[sTimerId]) + sTimerDigitsOffsetX[j],
                                ((void)0, gSaveContext.timerY[sTimerId]), sTimerDigitsWidth[j], 0xFA, 0x370, 0x370);
                        }
                    }
                } else {
                    // draw sTimerDigits[3] (6s of minutes) to sTimerDigits[7] (10s of milliseconds)
                    for (j = 0; j < 8; j++) {
                        OVERLAY_DISP = Gfx_DrawTexRectI8(
                            OVERLAY_DISP, ((u8*)gCounterDigit0Tex + (8 * 16 * sTimerDigits[j])), 8, 0x10,
                            ((void)0, gSaveContext.timerX[sTimerId]) + sTimerDigitsOffsetX[j],
                            ((void)0, gSaveContext.timerY[sTimerId]), sTimerDigitsWidth[j], 0xFA, 0x370, 0x370);
                    }
                }
            }
        }

    } else if (!sIsTimerPaused) {
        sTimerPausedOsTime = osGetTime();
        sIsTimerPaused = true;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Interface_UpdateBottleTimers(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 i;
    s16 j;
    u64 osTime;
    s32 pad[2];

    // Not satisfying any of these conditions will pause the bottle timer
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) &&
        (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
        ((msgCtx->msgMode == 0) || ((msgCtx->currentTextId >= 0x100) && (msgCtx->currentTextId <= 0x200)) ||
         ((msgCtx->currentTextId >= 0x1BB2) && (msgCtx->currentTextId <= 0x1BB6))) &&
        (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF) &&
        !Play_InCsMode(play)) {

        // Account for osTime when the timer is paused
        if (sIsBottleTimerPaused) {
            osTime = osGetTime();

            for (j = BOTTLE_FIRST; j < BOTTLE_MAX; j++) {
                if (gSaveContext.bottleTimerStates[j] == BOTTLE_TIMER_STATE_COUNTING) {
                    gSaveContext.bottleTimerPausedOsTimes[j] += osTime - sBottleTimerPausedOsTime;
                }
            }

            sIsBottleTimerPaused = false;
        }

        sTimerId = TIMER_ID_NONE;

        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.bottleTimerStates[i] == BOTTLE_TIMER_STATE_COUNTING) {
                osTime = osGetTime();

                // Get the total amount of unpaused time since the start of the timer, centiseconds (1/100th sec).
                osTime = OSTIME_TO_TIMER_ALT(osTime - ((void)0, gSaveContext.bottleTimerPausedOsTimes[i]) -
                                             ((void)0, gSaveContext.bottleTimerStartOsTimes[i]));

                if (osTime == 0) {
                    // No unpaused time has passed since the start of the timer.
                    gSaveContext.bottleTimerCurTimes[i] = gSaveContext.bottleTimerTimeLimits[i] - osTime;
                } else if (osTime <= gSaveContext.bottleTimerTimeLimits[i]) {
                    // Time has passed, but the time limit has not been exceeded
                    if (osTime >= gSaveContext.bottleTimerTimeLimits[i]) {
                        // The time is exactly at the time limit. No time remaining.
                        gSaveContext.bottleTimerCurTimes[i] = SECONDS_TO_TIMER(0);
                    } else {
                        // Update the time remaining
                        gSaveContext.bottleTimerCurTimes[i] = gSaveContext.bottleTimerTimeLimits[i] - osTime;
                    }
                } else {
                    // Time has passed, and the time limit has been exceeded.
                    gSaveContext.bottleTimerCurTimes[i] = SECONDS_TO_TIMER(0);

                    if (gSaveContext.save.inventory.items[i + SLOT_BOTTLE_1] == ITEM_HOT_SPRING_WATER) {
                        Inventory_UpdateItem(play, i + SLOT_BOTTLE_1, ITEM_SPRING_WATER);
                        Message_StartTextbox(play, 0xFA, NULL);
                    }
                    gSaveContext.bottleTimerStates[i] = BOTTLE_TIMER_STATE_OFF;
                }
            }
        }
    } else if (!sIsBottleTimerPaused) {
        sBottleTimerPausedOsTime = osGetTime();
        sIsBottleTimerPaused = true;
    }
}

void Interface_DrawMinigameIcons(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 i;
    s16 numDigitsDrawn;
    s16 rectX;
    s16 rectY;
    s16 width;
    s16 height;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C654(play->state.gfxCtx);

    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
        // Carrots rendering if the action corresponds to riding a horse
        if (interfaceCtx->unk_212 == DO_ACTION_FASTER) {
            // Load Carrot Icon
            gDPLoadTextureBlock(OVERLAY_DISP++, gCarrotIconTex, G_IM_FMT_RGBA, G_IM_SIZ_32b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            rectX = 110;
            rectY = (interfaceCtx->minigameState != MINIGAME_STATE_NONE) ? 200 : 56;

            // Draw 6 carrots
            for (i = 1; i < 7; i++, rectX += 16) {
                // Carrot Color (based on availability)
                if ((interfaceCtx->numHorseBoosts == 0) || (interfaceCtx->numHorseBoosts < i)) {
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 150, 255, interfaceCtx->aAlpha);
                } else {
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->aAlpha);
                }

                gSPTextureRectangle(OVERLAY_DISP++, rectX << 2, rectY << 2, (rectX + 16) << 2, (rectY + 16) << 2,
                                    G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            }
        }

        if (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) {
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            width = 24;
            height = 16;
            rectX = 20;
            if (gSaveContext.save.playerData.healthCapacity > 0xA0) {
                rectY = 75; // two rows of hearts
            } else {
                rectY = 67; // one row of hearts
            }

            if (gSaveContext.save.entrance == ENTRANCE(WATERFALL_RAPIDS, 1)) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->bAlpha);
                gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
                gDPLoadTextureBlock(OVERLAY_DISP++, gBeaverRingIconTex, G_IM_FMT_RGBA, G_IM_SIZ_32b, 24, 16, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
            } else if (play->sceneId == SCENE_DOUJOU) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 140, 50, interfaceCtx->bAlpha);
                gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
                gDPLoadTextureBlock(OVERLAY_DISP++, gSwordTrainingLogIconTex, G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
            } else if (play->sceneId == SCENE_30GYOSON) {
                width = 16;
                height = 30;
                rectX = 24;
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 100, 75, interfaceCtx->bAlpha);
                gDPSetEnvColor(OVERLAY_DISP++, 55, 55, 0, 255);
                gDPLoadTextureBlock(OVERLAY_DISP++, gFishermanMinigameTorchIconTex, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 30, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->bAlpha);
                gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
                gDPLoadTextureBlock(OVERLAY_DISP++, gArcheryScoreIconTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 16, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
            }

            gSPTextureRectangle(OVERLAY_DISP++, (rectX << 2), (rectY << 2), ((rectX + width) << 2),
                                ((rectY + height) << 2), G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->bAlpha);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);

            if (play->sceneId == SCENE_30GYOSON) {
                rectX += 20;
                if (gSaveContext.save.playerData.healthCapacity > 0xA0) {
                    rectY = 87; // two rows of hearts
                } else {
                    rectY = 79; // one row of hearts
                }
            } else {
                rectX += 26;
            }

            for (i = 0, numDigitsDrawn = 0; i < 4; i++) {
                if ((sMinigameScoreDigits[i] != 0) || (numDigitsDrawn != 0) || (i >= 3)) {
                    OVERLAY_DISP =
                        Gfx_DrawTexRectI8(OVERLAY_DISP, ((u8*)gCounterDigit0Tex + (8 * 16 * sMinigameScoreDigits[i])),
                                          8, 0x10, rectX, rectY - 2, 9, 0xFA, 0x370, 0x370);
                    rectX += 9;
                    numDigitsDrawn++;
                }
            }

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

s16 sRupeeDigitsFirst[] = { 1, 0, 0, 0 };

s16 sRupeeDigitsCount[] = { 2, 3, 3, 0 };

Color_RGB16 sRupeeCounterIconPrimColors[] = {
    { 200, 255, 100 },
    { 170, 170, 255 },
    { 255, 105, 105 },
};

Color_RGB16 sRupeeCounterIconEnvColors[] = {
    { 0, 80, 0 },
    { 10, 10, 80 },
    { 40, 10, 0 },
};

TexturePtr sMinigameCountdownTextures[] = {
    gMinigameCountdown3Tex,
    gMinigameCountdown2Tex,
    gMinigameCountdown1Tex,
    gMinigameCountdownGoTex,
};

s16 sMinigameCountdownTexWidths[] = { 24, 24, 24, 40 };

Color_RGB16 sMinigameCountdownPrimColors[] = {
    { 100, 255, 100 },
    { 255, 255, 60 },
    { 255, 100, 0 },
    { 120, 170, 255 },
};

TexturePtr sStoryTextures[] = {
    gStoryMaskFestivalTex,
    gStoryGiantsLeavingTex,
};

TexturePtr sStoryTLUTs[] = {
    gStoryMaskFestivalTLUT,
    gStoryGiantsLeavingTLUT,
};

void Interface_Draw(PlayState* play) {
    s32 pad;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    Gfx* gfx;
    s16 sp2CE;
    s16 sp2CC;
    s16 sp2CA;
    s16 sp2C8;
    PauseContext* pauseCtx = &play->pauseCtx;
    f32 minigameCountdownScale;
    s16 counterDigits[4];
    s16 magicAlpha;

    OPEN_DISPS(play->state.gfxCtx);

    gSPSegment(OVERLAY_DISP++, 0x02, interfaceCtx->parameterSegment);
    gSPSegment(OVERLAY_DISP++, 0x09, interfaceCtx->doActionSegment);
    gSPSegment(OVERLAY_DISP++, 0x08, interfaceCtx->iconItemSegment);
    gSPSegment(OVERLAY_DISP++, 0x0B, interfaceCtx->mapSegment);

    if (pauseCtx->debugEditor == DEBUG_EDITOR_NONE) {
        Interface_SetVertices(play);
        func_801170B8(interfaceCtx);

        // Draw Grandma's Story
        if (interfaceCtx->storyDmaStatus == STORY_DMA_DONE) {
            gSPSegment(OVERLAY_DISP++, 0x07, interfaceCtx->storySegment);
            func_8012C628(play->state.gfxCtx);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

            // Load in Grandma's Story
            gSPLoadUcodeL(OVERLAY_DISP++, gspS2DEX2_fifo);
            gfx = OVERLAY_DISP;
            func_80172758(&gfx, sStoryTextures[interfaceCtx->storyType], sStoryTLUTs[interfaceCtx->storyType],
                          SCREEN_WIDTH, SCREEN_HEIGHT, 2, 1, 0x8000, 0x100, 0.0f, 0.0f, 1.0f, 1.0f, 0);
            OVERLAY_DISP = gfx;
            gSPLoadUcode(OVERLAY_DISP++, SysUcode_GetUCode(), SysUcode_GetUCodeData());

            gDPPipeSync(OVERLAY_DISP++);

            // Fill the screen with a black rectangle
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, R_STORY_FILL_SCREEN_ALPHA);
            gDPFillRectangle(OVERLAY_DISP++, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        LifeMeter_Draw(play);

        func_8012C654(play->state.gfxCtx);

        // Draw Rupee Icon
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sRupeeCounterIconPrimColors[CUR_UPG_VALUE(UPG_WALLET)].r,
                        sRupeeCounterIconPrimColors[CUR_UPG_VALUE(UPG_WALLET)].g,
                        sRupeeCounterIconPrimColors[CUR_UPG_VALUE(UPG_WALLET)].b, interfaceCtx->magicAlpha);
        gDPSetEnvColor(OVERLAY_DISP++, sRupeeCounterIconEnvColors[CUR_UPG_VALUE(UPG_WALLET)].r,
                       sRupeeCounterIconEnvColors[CUR_UPG_VALUE(UPG_WALLET)].g,
                       sRupeeCounterIconEnvColors[CUR_UPG_VALUE(UPG_WALLET)].b, 255);
        OVERLAY_DISP =
            Gfx_DrawTexRectIA8(OVERLAY_DISP, gRupeeCounterIconTex, 16, 16, 26, 206, 16, 16, 1 << 10, 1 << 10);

        switch (play->sceneId) {
            case SCENE_INISIE_N:
            case SCENE_INISIE_R:
            case SCENE_MITURIN:
            case SCENE_HAKUGIN:
            case SCENE_SEA:
                if (DUNGEON_KEY_COUNT(gSaveContext.mapIndex) >= 0) {
                    // Small Key Icon
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 230, 255, interfaceCtx->magicAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 20, 255);
                    OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, gSmallKeyCounterIconTex, 16, 16, 26, 190, 16, 16,
                                                      1 << 10, 1 << 10);

                    // Small Key Counter
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
                                      TEXEL0, 0, PRIMITIVE, 0);

                    counterDigits[2] = 0;
                    counterDigits[3] = DUNGEON_KEY_COUNT(gSaveContext.mapIndex);

                    while (counterDigits[3] >= 10) {
                        counterDigits[2]++;
                        counterDigits[3] -= 10;
                    }

                    sp2CA = 42;

                    if (counterDigits[2] != 0) {
                        gDPPipeSync(OVERLAY_DISP++);
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

                        OVERLAY_DISP =
                            Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[2]), 8, 16,
                                              43, 191, 8, 16, 1 << 10, 1 << 10);

                        gDPPipeSync(OVERLAY_DISP++);
                        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
                        gSPTextureRectangle(OVERLAY_DISP++, 168, 760, 200, 824, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                            1 << 10);

                        sp2CA += 8;
                    }

                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

                    OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[3]),
                                                     8, 16, sp2CA + 1, 191, 8, 16, 1 << 10, 1 << 10);

                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
                    gSPTextureRectangle(OVERLAY_DISP++, sp2CA * 4, 760, (sp2CA * 4) + 0x20, 824, G_TX_RENDERTILE, 0, 0,
                                        1 << 10, 1 << 10);
                }
                break;

            case SCENE_KINSTA1:
            case SCENE_KINDAN2:
                // Gold Skulltula Icon
                gDPPipeSync(OVERLAY_DISP++);
                gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
                gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 255);
                gDPLoadTextureBlock(OVERLAY_DISP++, gGoldSkulltulaCounterIconTex, G_IM_FMT_RGBA, G_IM_SIZ_32b, 24, 24,
                                    0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(OVERLAY_DISP++, 80, 748, 176, 820, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

                // Gold Skulluta Counter
                gDPPipeSync(OVERLAY_DISP++);
                gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE,
                                  TEXEL0, 0, PRIMITIVE, 0);

                counterDigits[2] = 0;
                counterDigits[3] = Inventory_GetSkullTokenCount(play->sceneId);

                while (counterDigits[3] >= 10) {
                    counterDigits[2]++;
                    counterDigits[3] -= 10;
                }

                sp2CA = 42;

                if (counterDigits[2] != 0) {
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

                    OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[2]),
                                                     8, 16, 43, 191, 8, 16, 1 << 10, 1 << 10);

                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
                    gSPTextureRectangle(OVERLAY_DISP++, 168, 760, 200, 824, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

                    sp2CA += 8;
                }

                gDPPipeSync(OVERLAY_DISP++);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->magicAlpha);

                OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[3]), 8,
                                                 16, sp2CA + 1, 191, 8, 16, 1 << 10, 1 << 10);

                gDPPipeSync(OVERLAY_DISP++);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
                gSPTextureRectangle(OVERLAY_DISP++, sp2CA * 4, 760, (sp2CA * 4) + 0x20, 824, G_TX_RENDERTILE, 0, 0,
                                    1 << 10, 1 << 10);
                break;

            default:
                break;
        }

        // Rupee Counter
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                          PRIMITIVE, 0);

        counterDigits[0] = counterDigits[1] = 0;
        counterDigits[2] = gSaveContext.save.playerData.rupees;

        if ((counterDigits[2] > 9999) || (counterDigits[2] < 0)) {
            counterDigits[2] &= 0xDDD;
        }

        while (counterDigits[2] >= 100) {
            counterDigits[0]++;
            counterDigits[2] -= 100;
        }

        while (counterDigits[2] >= 10) {
            counterDigits[1]++;
            counterDigits[2] -= 10;
        }

        sp2CC = sRupeeDigitsFirst[CUR_UPG_VALUE(UPG_WALLET)];
        sp2C8 = sRupeeDigitsCount[CUR_UPG_VALUE(UPG_WALLET)];

        magicAlpha = interfaceCtx->magicAlpha;
        if (magicAlpha > 180) {
            magicAlpha = 180;
        }

        for (sp2CE = 0, sp2CA = 42; sp2CE < sp2C8; sp2CE++, sp2CC++, sp2CA += 8) {
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, magicAlpha);

            OVERLAY_DISP = Gfx_DrawTexRectI8(OVERLAY_DISP, (u8*)gCounterDigit0Tex + (8 * 16 * counterDigits[sp2CC]), 8,
                                             16, sp2CA + 1, 207, 8, 16, 1 << 10, 1 << 10);

            gDPPipeSync(OVERLAY_DISP++);

            if (gSaveContext.save.playerData.rupees == CUR_CAPACITY(UPG_WALLET)) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 120, 255, 0, interfaceCtx->magicAlpha);
            } else if (gSaveContext.save.playerData.rupees != 0) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->magicAlpha);
            } else {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 100, 100, 100, interfaceCtx->magicAlpha);
            }

            gSPTextureRectangle(OVERLAY_DISP++, sp2CA * 4, 824, (sp2CA * 4) + 0x20, 888, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                1 << 10);
        }

        Magic_DrawMeter(play);
        Minimap_Draw(play);

        if ((R_PAUSE_BG_PRERENDER_STATE != 2) && (R_PAUSE_BG_PRERENDER_STATE != 3)) {
            Actor_DrawZTarget(&play->actorCtx.targetContext, play);
        }

        func_8012C654(play->state.gfxCtx);

        func_80117100(play);

        if (player->transformation == ((void)0, gSaveContext.save.playerForm)) {
            func_80118084(play);
        }
        func_80118890(play);

        func_80118BA4(play);

        func_80119030(play);

        // Draw either the minigame countdown or the three-day clock
        if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
            if ((interfaceCtx->minigameState != MINIGAME_STATE_NONE) &&
                (interfaceCtx->minigameState < MINIGAME_STATE_NO_COUNTDOWN_SETUP)) {
                // Minigame Countdown
                if (((u32)interfaceCtx->minigameState % 2) == 0) {

                    sp2CE = (interfaceCtx->minigameState >> 1) - 1;
                    minigameCountdownScale = interfaceCtx->minigameCountdownScale / 100.0f;

                    if (sp2CE == 3) {
                        interfaceCtx->actionVtx[40 + 0].v.ob[0] = interfaceCtx->actionVtx[40 + 2].v.ob[0] = -20;
                        interfaceCtx->actionVtx[40 + 1].v.ob[0] = interfaceCtx->actionVtx[40 + 3].v.ob[0] =
                            interfaceCtx->actionVtx[40 + 0].v.ob[0] + 40;
                        interfaceCtx->actionVtx[40 + 1].v.tc[0] = interfaceCtx->actionVtx[40 + 3].v.tc[0] = 40 << 5;
                    }

                    interfaceCtx->actionVtx[40 + 2].v.tc[1] = interfaceCtx->actionVtx[40 + 3].v.tc[1] = 32 << 5;

                    func_8012C8D4(play->state.gfxCtx);

                    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                    gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sMinigameCountdownPrimColors[sp2CE].r,
                                    sMinigameCountdownPrimColors[sp2CE].g, sMinigameCountdownPrimColors[sp2CE].b,
                                    interfaceCtx->minigameCountdownAlpha);

                    Matrix_Translate(0.0f, -40.0f, 0.0f, MTXMODE_NEW);
                    Matrix_Scale(minigameCountdownScale, minigameCountdownScale, 0.0f, MTXMODE_APPLY);

                    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[40], 4, 0);

                    OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, sMinigameCountdownTextures[sp2CE],
                                                      sMinigameCountdownTexWidths[sp2CE], 32, 0);
                }
            } else {
                Interface_DrawClock(play);
            }
        }

        // Draw the letters of minigame perfect
        if (interfaceCtx->perfectLettersOn) {
            Interface_DrawPerfectLetters(play);
        }

        Interface_DrawMinigameIcons(play);
        Interface_DrawTimers(play);
    }

    // Draw pictograph focus icons
    if (sPictoState == PICTO_BOX_STATE_LENS) {

        func_8012C654(play->state.gfxCtx);

        gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
        gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, 255);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, gPictoBoxFocusBorderTex, G_IM_FMT_IA, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                               G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);

        gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_TOPLEFT_X << 2, R_PICTO_FOCUS_BORDER_TOPLEFT_Y << 2,
                            (R_PICTO_FOCUS_BORDER_TOPLEFT_X << 2) + (16 << 2),
                            (R_PICTO_FOCUS_BORDER_TOPLEFT_Y << 2) + (16 << 2), G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_TOPRIGHT_X << 2, R_PICTO_FOCUS_BORDER_TOPRIGHT_Y << 2,
                            (R_PICTO_FOCUS_BORDER_TOPRIGHT_X << 2) + (16 << 2),
                            (R_PICTO_FOCUS_BORDER_TOPRIGHT_Y << 2) + (16 << 2), G_TX_RENDERTILE, 512, 0, 1 << 10,
                            1 << 10);
        gSPTextureRectangle(
            OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_BOTTOMLEFT_X << 2, R_PICTO_FOCUS_BORDER_BOTTOMLEFT_Y << 2,
            (R_PICTO_FOCUS_BORDER_BOTTOMLEFT_X << 2) + (16 << 2), (R_PICTO_FOCUS_BORDER_BOTTOMLEFT_Y << 2) + (16 << 2),
            G_TX_RENDERTILE, 0, 512, 1 << 10, 1 << 10);
        gSPTextureRectangle(
            OVERLAY_DISP++, R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_X << 2, R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_Y << 2,
            (R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_X << 2) + (16 << 2),
            (R_PICTO_FOCUS_BORDER_BOTTOMRIGHT_Y << 2) + (16 << 2), G_TX_RENDERTILE, 512, 512, 1 << 10, 1 << 10);

        gDPLoadTextureBlock_4b(OVERLAY_DISP++, gPictoBoxFocusIconTex, G_IM_FMT_I, 32, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_ICON_X << 2, R_PICTO_FOCUS_ICON_Y << 2,
                            (R_PICTO_FOCUS_ICON_X << 2) + 0x80, (R_PICTO_FOCUS_ICON_Y << 2) + (16 << 2),
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

        gDPLoadTextureBlock_4b(OVERLAY_DISP++, gPictoBoxFocusTextTex, G_IM_FMT_I, 32, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        gSPTextureRectangle(OVERLAY_DISP++, R_PICTO_FOCUS_TEXT_X << 2, R_PICTO_FOCUS_TEXT_Y << 2,
                            (R_PICTO_FOCUS_TEXT_X << 2) + 0x80, (R_PICTO_FOCUS_TEXT_Y << 2) + 0x20, G_TX_RENDERTILE, 0,
                            0, 1 << 10, 1 << 10);
    }

    // Draw pictograph photo
    if (sPictoState >= PICTO_BOX_STATE_SETUP_PHOTO) {
        if (!(play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON)) {
            Play_CompressI8ToI5((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : D_801FBB90,
                                (u8*)gSaveContext.pictoPhotoI5, PICTO_PHOTO_WIDTH * PICTO_PHOTO_HEIGHT);

            interfaceCtx->unk_222 = interfaceCtx->unk_224 = 0;

            sPictoState = PICTO_BOX_STATE_OFF;
            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
        } else {
            s16 pictoRectTop;
            s16 pictoRectLeft;

            if (sPictoState == PICTO_BOX_STATE_SETUP_PHOTO) {
                sPictoState = PICTO_BOX_STATE_PHOTO;
                Message_StartTextbox(play, 0xF8, NULL);
                Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
                player->stateFlags1 |= PLAYER_STATE1_200;
            }

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 200, 200, 200, 250);
            gDPFillRectangle(OVERLAY_DISP++, 70, 22, 251, 151);

            func_8012C654(play->state.gfxCtx);

            gDPSetRenderMode(OVERLAY_DISP++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 250, 160, 160, 255);

            // Picture is offset up by 33 pixels to give room for the message box at the bottom
            pictoRectTop = PICTO_PHOTO_TOPLEFT_Y - 33;
            for (sp2CC = 0; sp2CC < (PICTO_PHOTO_HEIGHT / 8); sp2CC++, pictoRectTop += 8) {
                pictoRectLeft = PICTO_PHOTO_TOPLEFT_X;
                gDPLoadTextureBlock(OVERLAY_DISP++,
                                    (u8*)((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : D_801FBB90) +
                                        (0x500 * sp2CC),
                                    G_IM_FMT_I, G_IM_SIZ_8b, PICTO_PHOTO_WIDTH, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                gSPTextureRectangle(OVERLAY_DISP++, pictoRectLeft << 2, pictoRectTop << 2,
                                    (pictoRectLeft + PICTO_PHOTO_WIDTH) << 2, (pictoRectTop << 2) + (8 << 2),
                                    G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
            }
        }
    }

    // Draw over the entire screen (used in gameover)
    if (interfaceCtx->screenFillAlpha != 0) {
        gDPPipeSync(OVERLAY_DISP++);
        gSPDisplayList(OVERLAY_DISP++, sScreenFillSetupDL);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, interfaceCtx->screenFillAlpha);
        gSPDisplayList(OVERLAY_DISP++, D_0E000000.fillRect);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Interface_LoadStory(PlayState* play, s32 osMesgFlag) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    switch (interfaceCtx->storyDmaStatus) {
        case STORY_DMA_IDLE:
            if (interfaceCtx->storySegment == NULL) {
                break;
            }
            osCreateMesgQueue(&interfaceCtx->storyMsgQueue, &interfaceCtx->storyMsgBuf, 1);
            DmaMgr_SendRequestImpl(&interfaceCtx->dmaRequest, interfaceCtx->storySegment, interfaceCtx->storyAddr,
                                   interfaceCtx->storySize, 0, &interfaceCtx->storyMsgQueue, NULL);
            interfaceCtx->storyDmaStatus = STORY_DMA_LOADING;
            // fallthrough
        case STORY_DMA_LOADING:
            if (osRecvMesg(&interfaceCtx->storyMsgQueue, NULL, osMesgFlag) == 0) {
                interfaceCtx->storyDmaStatus = STORY_DMA_DONE;
            }
            break;

        default: // STORY_DMA_DONE
            break;
    }
}

void Interface_AllocStory(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    interfaceCtx->storyAddr = SEGMENT_ROM_START(story_static);
    interfaceCtx->storySize = SEGMENT_ROM_SIZE(story_static);

    if (interfaceCtx->storySegment == NULL) {
        interfaceCtx->storySegment = ZeldaArena_Malloc(interfaceCtx->storySize);
    }
    Interface_LoadStory(play, OS_MESG_NOBLOCK);
}

void Interface_Update(PlayState* play) {
    static u8 sIsSunsPlayedAtDay = false;
    static s16 sPrevTimeSpeed = 0;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);
    s16 dimmingAlpha;
    s16 risingAlpha;
    u16 aButtonDoAction;

    // Update buttons
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
        if (play->gameOverCtx.state == GAMEOVER_INACTIVE) {
            func_80111CB4(play);
        }
    }

    // Update hud visibility
    switch (gSaveContext.nextHudVisibility) {
        case HUD_VISIBILITY_NONE:
        case HUD_VISIBILITY_NONE_ALT:
        case HUD_VISIBILITY_B:
            dimmingAlpha = 255 - (gSaveContext.hudVisibilityTimer << 5);
            if (dimmingAlpha < 0) {
                dimmingAlpha = 0;
            }

            Interface_UpdateHudAlphas(play, dimmingAlpha);
            gSaveContext.hudVisibilityTimer += 2;
            if (dimmingAlpha == 0) {
                gSaveContext.nextHudVisibility = HUD_VISIBILITY_IDLE;
            }
            break;

        case HUD_VISIBILITY_HEARTS_WITH_OVERWRITE:
        case HUD_VISIBILITY_A:
        case HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE:
        case HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE:
        case HUD_VISIBILITY_ALL_NO_MINIMAP_W_DISABLED:
        case HUD_VISIBILITY_HEARTS_MAGIC:
        case HUD_VISIBILITY_B_ALT:
        case HUD_VISIBILITY_HEARTS:
        case HUD_VISIBILITY_A_B_MINIMAP:
        case HUD_VISIBILITY_HEARTS_MAGIC_WITH_OVERWRITE:
        case HUD_VISIBILITY_HEARTS_MAGIC_C:
        case HUD_VISIBILITY_ALL_NO_MINIMAP:
        case HUD_VISIBILITY_A_B_C:
        case HUD_VISIBILITY_B_MINIMAP:
        case HUD_VISIBILITY_HEARTS_MAGIC_MINIMAP:
        case HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP:
        case HUD_VISIBILITY_B_MAGIC:
        case HUD_VISIBILITY_A_B:
        case HUD_VISIBILITY_A_B_HEARTS_MAGIC_MINIMAP:
            dimmingAlpha = 255 - (gSaveContext.hudVisibilityTimer << 5);
            if (dimmingAlpha < 0) {
                dimmingAlpha = 0;
            }

            Interface_UpdateHudAlphas(play, dimmingAlpha);
            gSaveContext.hudVisibilityTimer++;
            if (dimmingAlpha == 0) {
                gSaveContext.nextHudVisibility = HUD_VISIBILITY_IDLE;
            }
            break;

        case HUD_VISIBILITY_ALL:
            dimmingAlpha = 255 - (gSaveContext.hudVisibilityTimer << 5);
            if (dimmingAlpha < 0) {
                dimmingAlpha = 0;
            }

            risingAlpha = 255 - dimmingAlpha;
            if (risingAlpha >= 255) {
                risingAlpha = 255;
            }

            Interface_UpdateButtonAlphasByStatus(play, risingAlpha);

            if (gSaveContext.buttonStatus[5] == BTN_DISABLED) {
                if (interfaceCtx->startAlpha != 70) {
                    interfaceCtx->startAlpha = 70;
                }
            } else {
                if (interfaceCtx->startAlpha != 255) {
                    interfaceCtx->startAlpha = risingAlpha;
                }
            }

            if (interfaceCtx->healthAlpha != 255) {
                interfaceCtx->healthAlpha = risingAlpha;
            }

            if (interfaceCtx->magicAlpha != 255) {
                interfaceCtx->magicAlpha = risingAlpha;
            }

            if (play->sceneId == SCENE_SPOT00) {
                if (interfaceCtx->minimapAlpha < 170) {
                    interfaceCtx->minimapAlpha = risingAlpha;
                } else {
                    interfaceCtx->minimapAlpha = 170;
                }
            } else if (interfaceCtx->minimapAlpha != 255) {
                interfaceCtx->minimapAlpha = risingAlpha;
            }

            gSaveContext.hudVisibilityTimer++;

            if (risingAlpha == 255) {
                gSaveContext.nextHudVisibility = HUD_VISIBILITY_IDLE;
            }

            break;

        case HUD_VISIBILITY_NONE_INSTANT:
            // Turn off all Hud immediately
            gSaveContext.nextHudVisibility = HUD_VISIBILITY_NONE;
            Interface_UpdateHudAlphas(play, 0);
            gSaveContext.nextHudVisibility = HUD_VISIBILITY_IDLE;
            // fallthrough
        default:
            break;
    }

    Map_Update(play);

    // Update health
    if (gSaveContext.healthAccumulator != 0) {
        gSaveContext.healthAccumulator -= 4;
        gSaveContext.save.playerData.health += 4;

        if ((gSaveContext.save.playerData.health & 0xF) < 4) {
            play_sound(NA_SE_SY_HP_RECOVER);
        }

        if (((void)0, gSaveContext.save.playerData.health) >= ((void)0, gSaveContext.save.playerData.healthCapacity)) {
            gSaveContext.save.playerData.health = gSaveContext.save.playerData.healthCapacity;
            gSaveContext.healthAccumulator = 0;
        }
    }

    LifeMeter_UpdateSizeAndBeep(play);

    // Update environmental hazard (remnant of OoT)
    sEnvHazard = Player_GetEnvironmentalHazard(play);
    if (sEnvHazard == PLAYER_ENV_HAZARD_HOTROOM) {
        if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_TUNIC) == EQUIP_VALUE_TUNIC_GORON) {
            sEnvHazard = PLAYER_ENV_HAZARD_NONE;
        }
    } else if ((Player_GetEnvironmentalHazard(play) >= PLAYER_ENV_HAZARD_UNDERWATER_FLOOR) &&
               (Player_GetEnvironmentalHazard(play) <= PLAYER_ENV_HAZARD_UNDERWATER_FREE)) {
        if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_TUNIC) == EQUIP_VALUE_TUNIC_ZORA) {
            sEnvHazard = PLAYER_ENV_HAZARD_NONE;
        }
    }

    LifeMeter_UpdateColors(play);

    // Update rupees
    if (gSaveContext.rupeeAccumulator != 0) {
        if (gSaveContext.rupeeAccumulator > 0) {
            if (gSaveContext.save.playerData.rupees < CUR_CAPACITY(UPG_WALLET)) {
                gSaveContext.rupeeAccumulator--;
                gSaveContext.save.playerData.rupees++;
                play_sound(NA_SE_SY_RUPY_COUNT);
            } else {
                // Max rupees
                gSaveContext.save.playerData.rupees = CUR_CAPACITY(UPG_WALLET);
                gSaveContext.rupeeAccumulator = 0;
            }
        } else if (gSaveContext.save.playerData.rupees != 0) {
            if (gSaveContext.rupeeAccumulator <= -50) {
                gSaveContext.rupeeAccumulator += 10;
                gSaveContext.save.playerData.rupees -= 10;
                if (gSaveContext.save.playerData.rupees < 0) {
                    gSaveContext.save.playerData.rupees = 0;
                }
                play_sound(NA_SE_SY_RUPY_COUNT);
            } else {
                gSaveContext.rupeeAccumulator++;
                gSaveContext.save.playerData.rupees--;
                play_sound(NA_SE_SY_RUPY_COUNT);
            }
        } else {
            gSaveContext.rupeeAccumulator = 0;
        }
    }

    // Update perfect letters
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
        if (interfaceCtx->perfectLettersOn) {
            if (interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_1) {
                Interface_UpdatePerfectLettersType1(play);
            } else if (interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_2) {
                Interface_UpdatePerfectLettersType2(play);
            } else if (interfaceCtx->perfectLettersType == PERFECT_LETTERS_TYPE_3) {
                Interface_UpdatePerfectLettersType3(play);
            }
        }
    }

    // Update minigame State
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
        if ((u32)interfaceCtx->minigameState != MINIGAME_STATE_NONE) {
            switch (interfaceCtx->minigameState) {
                case MINIGAME_STATE_COUNTDOWN_SETUP_3:
                case MINIGAME_STATE_COUNTDOWN_SETUP_2:
                case MINIGAME_STATE_COUNTDOWN_SETUP_1:
                case MINIGAME_STATE_COUNTDOWN_SETUP_GO:
                    interfaceCtx->minigameCountdownAlpha = 255;
                    interfaceCtx->minigameCountdownScale = 100;
                    interfaceCtx->minigameState++;
                    if (interfaceCtx->minigameState == MINIGAME_STATE_COUNTDOWN_GO) {
                        interfaceCtx->minigameCountdownScale = 160;
                        play_sound(NA_SE_SY_START_SHOT);
                    } else {
                        play_sound(NA_SE_SY_WARNING_COUNT_E);
                    }
                    break;

                case MINIGAME_STATE_COUNTDOWN_3:
                case MINIGAME_STATE_COUNTDOWN_2:
                case MINIGAME_STATE_COUNTDOWN_1:
                    interfaceCtx->minigameCountdownAlpha -= 10;
                    interfaceCtx->minigameCountdownScale += 3;
                    if (interfaceCtx->minigameCountdownAlpha < 22) {
                        interfaceCtx->minigameState++;
                    }
                    break;

                case MINIGAME_STATE_COUNTDOWN_GO:
                    interfaceCtx->minigameCountdownAlpha -= 10;
                    if (interfaceCtx->minigameCountdownAlpha <= 150) {
                        interfaceCtx->minigameState = MINIGAME_STATE_PLAYING;
                    }
                    break;

                case MINIGAME_STATE_NO_COUNTDOWN_SETUP:
                    interfaceCtx->minigameCountdownAlpha = 0;
                    interfaceCtx->minigameState++;
                    break;

                case MINIGAME_STATE_NO_COUNTDOWN:
                    interfaceCtx->minigameCountdownAlpha++;
                    if (interfaceCtx->minigameCountdownAlpha >= 18) {
                        interfaceCtx->minigameState = MINIGAME_STATE_PLAYING;
                    }
                    break;
            }
        }
    }

    // Update A Button
    switch (interfaceCtx->aButtonState) {
        case A_BTN_STATE_1:
            interfaceCtx->aButtonRoll += 10466.667f;
            if (interfaceCtx->aButtonRoll >= 15700.0f) {
                interfaceCtx->aButtonRoll = -15700.0f;
                interfaceCtx->aButtonState = A_BTN_STATE_2;

                if ((msgCtx->msgMode != 0) && (msgCtx->unk12006 == 0x26)) {
                    R_A_BTN_Y_OFFSET = -14;
                } else {
                    R_A_BTN_Y_OFFSET = 0;
                }
            }
            break;

        case A_BTN_STATE_2:
            interfaceCtx->aButtonRoll += 10466.667f;
            if (interfaceCtx->aButtonRoll >= 0.0f) {
                interfaceCtx->aButtonRoll = 0.0f;
                interfaceCtx->aButtonState = A_BTN_STATE_0;
                interfaceCtx->unk_212 = interfaceCtx->aButtonDoAction;
                aButtonDoAction = interfaceCtx->unk_212;
                if ((aButtonDoAction == DO_ACTION_MAX) || (aButtonDoAction == DO_ACTION_MAX + 1)) {
                    aButtonDoAction = DO_ACTION_NONE;
                }
                func_80115428(&play->interfaceCtx, aButtonDoAction, 0);
            }
            break;

        case A_BTN_STATE_3:
            interfaceCtx->aButtonRoll += 10466.667f;
            if (interfaceCtx->aButtonRoll >= 15700.0f) {
                interfaceCtx->aButtonRoll = -15700.0f;
                interfaceCtx->aButtonState = A_BTN_STATE_2;
            }
            break;

        case A_BTN_STATE_4:
            interfaceCtx->aButtonRoll += 10466.667f;
            if (interfaceCtx->aButtonRoll >= 0.0f) {
                interfaceCtx->aButtonRoll = 0.0f;
                interfaceCtx->aButtonState = A_BTN_STATE_0;
                interfaceCtx->unk_212 = interfaceCtx->aButtonDoAction;
                aButtonDoAction = interfaceCtx->unk_212;
                if ((aButtonDoAction == DO_ACTION_MAX) || (aButtonDoAction == DO_ACTION_MAX + 1)) {
                    aButtonDoAction = DO_ACTION_NONE;
                }

                func_80115428(&play->interfaceCtx, aButtonDoAction, 0);
            }
            break;

        default: // A_BTN_STATE_0
            break;
    }

    // Update magic
    if (!(player->stateFlags1 & PLAYER_STATE1_200)) {
        if (R_MAGIC_DBG_SET_UPGRADE == MAGIC_DBG_SET_UPGRADE_DOUBLE_METER) {
            // Upgrade to double magic
            if (!gSaveContext.save.playerData.isMagicAcquired) {
                gSaveContext.save.playerData.isMagicAcquired = true;
            }
            gSaveContext.save.playerData.isDoubleMagicAcquired = true;
            gSaveContext.save.playerData.magic = MAGIC_DOUBLE_METER;
            gSaveContext.save.playerData.magicLevel = 0;
            R_MAGIC_DBG_SET_UPGRADE = MAGIC_DBG_SET_UPGRADE_NO_ACTION;
        } else if (R_MAGIC_DBG_SET_UPGRADE == MAGIC_DBG_SET_UPGRADE_NORMAL_METER) {
            // Upgrade to normal magic
            if (!gSaveContext.save.playerData.isMagicAcquired) {
                gSaveContext.save.playerData.isMagicAcquired = true;
            }
            gSaveContext.save.playerData.isDoubleMagicAcquired = false;
            gSaveContext.save.playerData.magic = MAGIC_NORMAL_METER;
            gSaveContext.save.playerData.magicLevel = 0;
            R_MAGIC_DBG_SET_UPGRADE = MAGIC_DBG_SET_UPGRADE_NO_ACTION;
        }

        if ((gSaveContext.save.playerData.isMagicAcquired) && (gSaveContext.save.playerData.magicLevel == 0)) {
            // Prepare to step `magicCapacity` to full capacity
            gSaveContext.save.playerData.magicLevel = gSaveContext.save.playerData.isDoubleMagicAcquired + 1;
            gSaveContext.magicFillTarget = gSaveContext.save.playerData.magic;
            gSaveContext.save.playerData.magic = 0;
            gSaveContext.magicState = MAGIC_STATE_STEP_CAPACITY;
            BUTTON_ITEM_EQUIP(PLAYER_FORM_DEKU, EQUIP_SLOT_B) = ITEM_NUT;
        }

        Magic_Update(play);
        Magic_UpdateAddRequest();
    }

    // Update environmental hazard timer
    if (gSaveContext.timerStates[TIMER_ID_ENV_HAZARD] == TIMER_STATE_OFF) {
        if ((sEnvHazard == PLAYER_ENV_HAZARD_HOTROOM) || (sEnvHazard == PLAYER_ENV_HAZARD_UNDERWATER_FREE)) {
            if (CUR_FORM != PLAYER_FORM_ZORA) {
                if (play->gameOverCtx.state == GAMEOVER_INACTIVE) {
                    if ((gSaveContext.save.playerData.health >> 1) != 0) {
                        gSaveContext.timerStates[TIMER_ID_ENV_HAZARD] = TIMER_STATE_ENV_HAZARD_START;
                        gSaveContext.timerX[TIMER_ID_ENV_HAZARD] = 115;
                        gSaveContext.timerY[TIMER_ID_ENV_HAZARD] = 80;
                        sEnvTimerActive = true;
                        gSaveContext.timerDirections[TIMER_ID_ENV_HAZARD] = TIMER_COUNT_DOWN;
                    }
                }
            }
        }
    } else if (((sEnvHazard == PLAYER_ENV_HAZARD_NONE) || (sEnvHazard == PLAYER_ENV_HAZARD_SWIMMING)) &&
               (gSaveContext.timerStates[TIMER_ID_ENV_HAZARD] <= TIMER_STATE_COUNTING)) {
        gSaveContext.timerStates[TIMER_ID_ENV_HAZARD] = TIMER_STATE_OFF;
    }

    // Update minigame
    if (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) {
        gSaveContext.minigameScore += interfaceCtx->minigamePoints;
        gSaveContext.minigameHiddenScore += interfaceCtx->minigameHiddenPoints;
        interfaceCtx->minigamePoints = 0;
        interfaceCtx->minigameHiddenPoints = 0;

        // Update horseback archery tier, unused remnant of OoT.
        if (sHBAScoreTier == 0) {
            if (gSaveContext.minigameScore >= 1000) {
                sHBAScoreTier++;
            }
        } else if (sHBAScoreTier == 1) {
            if (gSaveContext.minigameScore >= 1500) {
                sHBAScoreTier++;
            }
        }

        // Get minigame digits
        sMinigameScoreDigits[0] = sMinigameScoreDigits[1] = 0;
        sMinigameScoreDigits[2] = 0;
        sMinigameScoreDigits[3] = gSaveContext.minigameScore;

        while (sMinigameScoreDigits[3] >= 1000) {
            sMinigameScoreDigits[0]++;
            sMinigameScoreDigits[3] -= 1000;
        }

        while (sMinigameScoreDigits[3] >= 100) {
            sMinigameScoreDigits[1]++;
            sMinigameScoreDigits[3] -= 100;
        }

        while (sMinigameScoreDigits[3] >= 10) {
            sMinigameScoreDigits[2]++;
            sMinigameScoreDigits[3] -= 10;
        }
    }

    // Update Sun Song
    if (gSaveContext.sunsSongState != SUNSSONG_INACTIVE) {
        // exit out of ocarina mode after suns song finishes playing
        if ((msgCtx->ocarinaAction != 0x39) && (gSaveContext.sunsSongState == SUNSSONG_START)) {
            play->msgCtx.ocarinaMode = 4;
        }

        // handle suns song in areas where time moves
        if (play->envCtx.sceneTimeSpeed != 0) {
            if (gSaveContext.sunsSongState != SUNSSONG_SPEED_TIME) {
                sIsSunsPlayedAtDay = false;
                if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time <= CLOCK_TIME(18, 0))) {
                    sIsSunsPlayedAtDay = true;
                }

                gSaveContext.sunsSongState = SUNSSONG_SPEED_TIME;
                sPrevTimeSpeed = R_TIME_SPEED;
                R_TIME_SPEED = 400;
            } else if (!sIsSunsPlayedAtDay) {
                // Nighttime
                if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time <= CLOCK_TIME(18, 0))) {
                    // Daytime has been reached. End suns song effect
                    gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
                    R_TIME_SPEED = sPrevTimeSpeed;
                    play->msgCtx.ocarinaMode = 4;
                }
            } else {
                // Daytime
                if (gSaveContext.save.time > CLOCK_TIME(18, 0)) {
                    // Nighttime has been reached. End suns song effect
                    gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
                    R_TIME_SPEED = sPrevTimeSpeed;
                    play->msgCtx.ocarinaMode = 4;
                }
            }
        } else {
            gSaveContext.sunsSongState = SUNSSONG_SPECIAL;
        }
    }

    Interface_UpdateBottleTimers(play);

    // Update Grandma's Story
    if (interfaceCtx->storyState != STORY_STATE_OFF) {
        if (interfaceCtx->storyState == STORY_STATE_INIT) {
            interfaceCtx->storyDmaStatus = STORY_DMA_IDLE;
            interfaceCtx->storyState = STORY_STATE_IDLE;
            R_STORY_FILL_SCREEN_ALPHA = 0;
        }

        Interface_AllocStory(play);

        if (interfaceCtx->storyState == STORY_STATE_DESTROY) {
            interfaceCtx->storyState = STORY_STATE_OFF;
            interfaceCtx->storyDmaStatus = STORY_DMA_IDLE;
            if (interfaceCtx->storySegment != NULL) {
                ZeldaArena_Free(interfaceCtx->storySegment);
                interfaceCtx->storySegment = NULL;
            }
        } else if (interfaceCtx->storyState == STORY_STATE_SETUP_IDLE) {
            interfaceCtx->storyState = STORY_STATE_IDLE;
        } else if (interfaceCtx->storyState == STORY_STATE_FADE_OUT) {
            R_STORY_FILL_SCREEN_ALPHA += 10;
            if (R_STORY_FILL_SCREEN_ALPHA >= 250) {
                R_STORY_FILL_SCREEN_ALPHA = 255;
                interfaceCtx->storyState = STORY_STATE_IDLE;
            }
        } else if (interfaceCtx->storyState == STORY_STATE_FADE_IN) {
            R_STORY_FILL_SCREEN_ALPHA -= 10;
            if (R_STORY_FILL_SCREEN_ALPHA < 0) {
                R_STORY_FILL_SCREEN_ALPHA = 0;
                interfaceCtx->storyState = STORY_STATE_IDLE;
            }
        }
    }
}

void Interface_Destroy(PlayState* play) {
    Map_Destroy(play);
    func_80174F9C(Interface_PostmanTimerCallback, NULL);
}

void Interface_Init(PlayState* play) {
    s32 pad;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    size_t parameterStaticSize;
    s32 i;

    bzero(interfaceCtx, sizeof(InterfaceContext));

    gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
    gSaveContext.nextHudVisibility = HUD_VISIBILITY_IDLE;
    gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;

    View_Init(&interfaceCtx->view, play->state.gfxCtx);

    interfaceCtx->magicConsumptionTimer = 16;
    interfaceCtx->healthTimer = 200;

    parameterStaticSize = SEGMENT_ROM_SIZE(parameter_static);
    interfaceCtx->parameterSegment = THA_AllocEndAlign16(&play->state.heap, parameterStaticSize);
    DmaMgr_SendRequest0(interfaceCtx->parameterSegment, SEGMENT_ROM_START(parameter_static), parameterStaticSize);

    interfaceCtx->doActionSegment = THA_AllocEndAlign16(&play->state.heap, 0xC90);
    DmaMgr_SendRequest0(interfaceCtx->doActionSegment, SEGMENT_ROM_START(do_action_static), 0x300);
    DmaMgr_SendRequest0(interfaceCtx->doActionSegment + 0x300, SEGMENT_ROM_START(do_action_static) + 0x480, 0x180);

    Interface_NewDay(play, CURRENT_DAY);

    interfaceCtx->iconItemSegment = THA_AllocEndAlign16(&play->state.heap, 0x4000);

    if (CUR_FORM_EQUIP(EQUIP_SLOT_B) < ITEM_F0) {
        Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
    } else if ((CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_NONE) && (CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_FD)) {
        Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
    }

    if (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) < ITEM_F0) {
        Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_LEFT);
    }

    if (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) < ITEM_F0) {
        Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_DOWN);
    }

    if (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) < ITEM_F0) {
        Interface_LoadItemIconImpl(play, EQUIP_SLOT_C_RIGHT);
    }

    if (((gSaveContext.timerStates[TIMER_ID_MINIGAME_2] == TIMER_STATE_COUNTING) ||
         (gSaveContext.timerStates[TIMER_ID_GORON_RACE_UNUSED] == TIMER_STATE_COUNTING)) &&
        ((gSaveContext.respawnFlag == -1) || (gSaveContext.respawnFlag == 1)) &&
        (gSaveContext.timerStates[TIMER_ID_MINIGAME_2] == TIMER_STATE_COUNTING)) {
        gSaveContext.timerStates[TIMER_ID_MINIGAME_2] = TIMER_STATE_START;
        gSaveContext.timerX[TIMER_ID_MINIGAME_2] = 115;
        gSaveContext.timerY[TIMER_ID_MINIGAME_2] = 80;
    }

    LifeMeter_Init(play);
    Map_Init(play);

    gSaveContext.minigameStatus = MINIGAME_STATUS_END;
    interfaceCtx->perfectLettersPrimColor[0] = 255;
    interfaceCtx->perfectLettersPrimColor[1] = 165;
    interfaceCtx->perfectLettersPrimColor[2] = 55;

    if (CHECK_EVENTINF(EVENTINF_34)) {
        CLEAR_EVENTINF(EVENTINF_34);
        gSaveContext.timerStates[TIMER_ID_MINIGAME_2] = TIMER_STATE_OFF;
    }

    gSaveContext.timerStates[TIMER_ID_MINIGAME_1] = TIMER_STATE_OFF;
    gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_1] = SECONDS_TO_TIMER(0);
    gSaveContext.timerTimeLimits[TIMER_ID_MINIGAME_1] = SECONDS_TO_TIMER(0);
    gSaveContext.timerStartOsTimes[TIMER_ID_MINIGAME_1] = 0;
    gSaveContext.timerStopTimes[TIMER_ID_MINIGAME_1] = 0;
    gSaveContext.timerPausedOsTimes[TIMER_ID_MINIGAME_1] = 0;

    for (i = 0; i < TIMER_ID_MAX; i++) {
        if (gSaveContext.timerStates[i] == TIMER_STATE_7) {
            gSaveContext.timerStates[i] = TIMER_STATE_OFF;
        }
    }

    sPictoState = PICTO_BOX_STATE_OFF;
    sPictoPhotoBeingTaken = false;

    if ((play->sceneId != SCENE_MITURIN_BS) && (play->sceneId != SCENE_HAKUGIN_BS) && (play->sceneId != SCENE_SEA_BS) &&
        (play->sceneId != SCENE_INISIE_BS) && (play->sceneId != SCENE_LAST_BS) && (play->sceneId != SCENE_MITURIN) &&
        (play->sceneId != SCENE_HAKUGIN) && (play->sceneId != SCENE_SEA) && (play->sceneId != SCENE_INISIE_N) &&
        (play->sceneId != SCENE_INISIE_R) && (play->sceneId != SCENE_LAST_DEKU) &&
        (play->sceneId != SCENE_LAST_GORON) && (play->sceneId != SCENE_LAST_ZORA) &&
        (play->sceneId != SCENE_LAST_LINK)) {

        CLEAR_EVENTINF(EVENTINF_53); // Goht intro cutscene watched
        CLEAR_EVENTINF(EVENTINF_54); // Odolwa intro cutscene watched
        CLEAR_EVENTINF(EVENTINF_55); // Twinmold intro cutscene watched
        CLEAR_EVENTINF(EVENTINF_56); // Gyorg intro cutscene watched
        CLEAR_EVENTINF(EVENTINF_57); // Igos du Ikana intro cutscene watched
        CLEAR_EVENTINF(EVENTINF_60); // Wart intro cutscene watched
        CLEAR_EVENTINF(EVENTINF_61); // Majoras intro cutscene watched
        CLEAR_EVENTINF(EVENTINF_62); //
        CLEAR_EVENTINF(EVENTINF_63); // Gomess intro cutscene watched
    }

    sFinalHoursClockDigitsRed = sFinalHoursClockFrameEnvRed = sFinalHoursClockFrameEnvGreen =
        sFinalHoursClockFrameEnvBlue = 0;
    sFinalHoursClockColorTimer = 15;
    sFinalHoursClockColorTargetIndex = 0;
}
