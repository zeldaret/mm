#include "global.h"
#include "PR/gs2dex.h"
#include "sys_cfb.h"
#include "z64snap.h"
#include "z64view.h"
#include "archives/icon_item_static/icon_item_static_yar.h"
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

// TODO extract this information from the texture definitions themselves
#define DO_ACTION_TEX_WIDTH 48
#define DO_ACTION_TEX_HEIGHT 16
#define DO_ACTION_TEX_SIZE ((DO_ACTION_TEX_WIDTH * DO_ACTION_TEX_HEIGHT) / 2) // (sizeof(gCheckDoActionENGTex))

typedef struct {
    /* 0x0 */ u8 scene;
    /* 0x1 */ u8 flags1;
    /* 0x2 */ u8 flags2;
    /* 0x3 */ u8 flags3;
} RestrictionFlags; // size = 0x4

Input sPostmanTimerInput[MAXCONTROLLERS];

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

#define DEFINE_SCENE(_name, enumValue, _textId, _drawConfig, restrictionFlags, _persistentCycleFlags) \
    { enumValue, restrictionFlags },

#define DEFINE_SCENE_UNSET(enumValue) { enumValue, RESTRICTIONS_NONE },

RestrictionFlags sRestrictionFlags[] = {
#include "tables/scene_table.h"
    // { RESTRICTIONS_TABLE_END, RESTRICTIONS_NONE }, // See note below
};
//! @note: in `Interface_SetSceneRestrictions`, `RESTRICTIONS_TABLE_END` act as a terminating value to
// stop looping through the array. If a scene is missing, then this will cause issues.

#undef DEFINE_SCENE
#undef DEFINE_SCENE_UNSET

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
    ITEM_DEKU_STICK, // ITEM_DEKU_STICKS_5
    ITEM_DEKU_STICK, // ITEM_DEKU_STICKS_10
    ITEM_DEKU_NUT,   // ITEM_DEKU_NUTS_5
    ITEM_DEKU_NUT,   // ITEM_DEKU_NUTS_10
    ITEM_BOMB,       // ITEM_BOMBS_5
    ITEM_BOMB,       // ITEM_BOMBS_10
    ITEM_BOMB,       // ITEM_BOMBS_20
    ITEM_BOMB,       // ITEM_BOMBS_30
    ITEM_BOW,        // ITEM_ARROWS_10
    ITEM_BOW,        // ITEM_ARROWS_30
    ITEM_BOW,        // ITEM_ARROWS_40
    ITEM_BOMBCHU,    // ITEM_ARROWS_50 !@bug this data is missing an ITEM_BOW, offsetting the rest by 1
    ITEM_BOMBCHU,    // ITEM_BOMBCHUS_20
    ITEM_BOMBCHU,    // ITEM_BOMBCHUS_10
    ITEM_BOMBCHU,    // ITEM_BOMBCHUS_1
    ITEM_DEKU_STICK, // ITEM_BOMBCHUS_5
    ITEM_DEKU_STICK, // ITEM_DEKU_STICK_UPGRADE_20
    ITEM_DEKU_NUT,   // ITEM_DEKU_STICK_UPGRADE_30
    ITEM_DEKU_NUT,   // ITEM_DEKU_NUT_UPGRADE_30
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

static Gfx sScreenFillSetupDL[] = {
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
s16 D_801BF9BC[] = {
    0x226, // EQUIP_SLOT_B
    0x2A8, // EQUIP_SLOT_C_LEFT
    0x2A8, // EQUIP_SLOT_C_DOWN
    0x2A8, // EQUIP_SLOT_C_RIGHT
};
s16 D_801BF9C4[] = { 0x9E, 0x9B };
s16 D_801BF9C8[] = { 0x17, 0x16 };
f32 D_801BF9CC[] = { -380.0f, -350.0f };
s16 D_801BF9D4[] = {
    0xA7,  // EQUIP_SLOT_B
    0xE3,  // EQUIP_SLOT_C_LEFT
    0xF9,  // EQUIP_SLOT_C_DOWN
    0x10F, // EQUIP_SLOT_C_RIGHT
};
s16 D_801BF9DC[] = {
    0x11, // EQUIP_SLOT_B
    0x12, // EQUIP_SLOT_C_LEFT
    0x22, // EQUIP_SLOT_C_DOWN
    0x12, // EQUIP_SLOT_C_RIGHT
};
s16 D_801BF9E4[] = {
    0x23F, // EQUIP_SLOT_B
    0x26C, // EQUIP_SLOT_C_LEFT
    0x26C, // EQUIP_SLOT_C_DOWN
    0x26C, // EQUIP_SLOT_C_RIGHT
};

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

void Interface_PostmanTimerCallback(void* arg) {
    s32 btnAPressed;

    PadMgr_GetInputNoLock(sPostmanTimerInput, false);
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
    for (i = 0; i < ARRAY_COUNT(gSaveContext.save.saveInfo.permanentSceneFlags); i++) {
        gSaveContext.save.saveInfo.permanentSceneFlags[i].chest = gSaveContext.cycleSceneFlags[i].chest;
        gSaveContext.save.saveInfo.permanentSceneFlags[i].switch0 = gSaveContext.cycleSceneFlags[i].switch0;
        gSaveContext.save.saveInfo.permanentSceneFlags[i].switch1 = gSaveContext.cycleSceneFlags[i].switch1;
        gSaveContext.save.saveInfo.permanentSceneFlags[i].clearedRoom = gSaveContext.cycleSceneFlags[i].clearedRoom;
        gSaveContext.save.saveInfo.permanentSceneFlags[i].collectible = gSaveContext.cycleSceneFlags[i].collectible;
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

    if ((gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) || (gSaveContext.bButtonStatus == BTN_DISABLED)) {
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

            if ((gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) ||
                (gSaveContext.bButtonStatus == ITEM_NONE)) {
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

    if ((play->roomCtx.curRoom.behaviorType1 == ROOM_BEHAVIOR_TYPE1_1) && (interfaceCtx->minimapAlpha >= 255)) {
        interfaceCtx->minimapAlpha = 255;
    }
}

/**
 * A continuation of the if-else chain from Interface_UpdateButtonsPart1
 * Also used directly when opening the pause menu i.e. skips part 1
 */
void Interface_UpdateButtonsPart2(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    s16 i;
    s16 restoreHudVisibility = false;

    if (CHECK_EVENTINF(EVENTINF_41)) {
        // Related to swamp boat (non-minigame)?
        for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
            if ((GET_CUR_FORM_BTN_ITEM(i) != ITEM_PICTOGRAPH_BOX) || (msgCtx->msgMode != MSGMODE_NONE)) {
                if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                    restoreHudVisibility = true;
                }
                gSaveContext.buttonStatus[i] = BTN_DISABLED;
            } else {
                if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                    restoreHudVisibility = true;
                }
                gSaveContext.buttonStatus[i] = BTN_ENABLED;
            }
        }

        if (sPictoState == PICTO_BOX_STATE_OFF) {
            if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
                restoreHudVisibility = true;
            }
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
        } else {
            if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                restoreHudVisibility = true;
            }
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
        }
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_90_20)) {
        // Fishermans's jumping minigame
        for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
            if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                gSaveContext.buttonStatus[i] = BTN_DISABLED;
            }
        }

        Interface_SetHudVisibility(HUD_VISIBILITY_B);
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_82_08)) {
        // Swordsman's log minigame
        for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
            if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                gSaveContext.buttonStatus[i] = BTN_DISABLED;
            }
        }

        Interface_SetHudVisibility(HUD_VISIBILITY_A_B_HEARTS_MAGIC_MINIMAP);
    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_84_20)) {
        // Related to moon child
        if (player->currentMask == PLAYER_MASK_FIERCE_DEITY) {
            for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
                if ((GET_CUR_FORM_BTN_ITEM(i) == ITEM_MASK_FIERCE_DEITY) ||
                    ((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_BOTTLE) && (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_OBABA_DRINK))) {
                    if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                        restoreHudVisibility = true;
                        gSaveContext.buttonStatus[i] = BTN_ENABLED;
                    }
                } else {
                    if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                        gSaveContext.buttonStatus[i] = BTN_DISABLED;
                        restoreHudVisibility = true;
                    }
                }
            }
        } else {
            for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
                if ((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MASK_DEKU) && (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_MASK_ZORA)) {
                    if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                        restoreHudVisibility = true;
                    }
                    gSaveContext.buttonStatus[i] = BTN_DISABLED;
                } else {
                    if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                        restoreHudVisibility = true;
                    }
                    gSaveContext.buttonStatus[i] = BTN_ENABLED;
                }
            }
        }
    } else if ((play->sceneId == SCENE_SPOT00) && (gSaveContext.sceneLayer == 6)) {
        // Unknown cutscene
        for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
            if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                restoreHudVisibility = true;
            }
            gSaveContext.buttonStatus[i] = BTN_DISABLED;
        }
    } else if (CHECK_EVENTINF(EVENTINF_34)) {
        // Deku playground minigame
        if (player->stateFlags3 & PLAYER_STATE3_1000000) {
            if (gSaveContext.save.saveInfo.inventory.items[SLOT_DEKU_NUT] == ITEM_DEKU_NUT) {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_DEKU_NUT;
                Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
            } else {
                gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
                restoreHudVisibility = true;
            }
        } else {
            if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
                restoreHudVisibility = true;
            }

            for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
                if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                    restoreHudVisibility = true;
                }
                gSaveContext.buttonStatus[i] = BTN_DISABLED;
            }
        }

        if (restoreHudVisibility || (gSaveContext.hudVisibility != HUD_VISIBILITY_A_B_MINIMAP)) {
            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
            Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
            restoreHudVisibility = false;
        }
    } else if (player->stateFlags3 & PLAYER_STATE3_1000000) {
        // Nuts on B (from flying as Deku Link)
        if (gSaveContext.save.saveInfo.inventory.items[SLOT_DEKU_NUT] == ITEM_DEKU_NUT) {
            if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_DEKU_NUT) {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_DEKU_NUT;
                Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
                restoreHudVisibility = true;
            }
        } else if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_ENABLED) {
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
            restoreHudVisibility = true;
        }

        if (restoreHudVisibility) {
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
        }
    } else if (!gSaveContext.save.saveInfo.playerData.isMagicAcquired && (CUR_FORM == PLAYER_FORM_DEKU) &&
               (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_DEKU_NUT)) {
        // Nuts on B (as Deku Link)
        BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_FD;
        gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
    } else if ((Player_GetEnvironmentalHazard(play) >= PLAYER_ENV_HAZARD_UNDERWATER_FLOOR) &&
               (Player_GetEnvironmentalHazard(play) <= PLAYER_ENV_HAZARD_UNDERWATER_FREE)) {
        // Swimming underwater
        if (CUR_FORM != PLAYER_FORM_ZORA) {
            if ((player->currentMask == PLAYER_MASK_BLAST) && (player->blastMaskTimer == 0)) {
                if (gSaveContext.bButtonStatus == BTN_DISABLED) {
                    restoreHudVisibility = true;
                }
                gSaveContext.bButtonStatus = BTN_ENABLED;
            } else if ((interfaceCtx->bButtonDoAction == DO_ACTION_EXPLODE) &&
                       (player->currentMask == PLAYER_MASK_BLAST)) {
                if (gSaveContext.bButtonStatus != BTN_DISABLED) {
                    gSaveContext.bButtonStatus = BTN_DISABLED;
                    restoreHudVisibility = true;
                }
            } else {
                if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
                    restoreHudVisibility = true;
                }
                gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
            }
        } else {
            if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                restoreHudVisibility = true;
            }
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
        }

        for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
            if (GET_CUR_FORM_BTN_ITEM(i) != ITEM_MASK_ZORA) {
                if (Player_GetEnvironmentalHazard(play) == PLAYER_ENV_HAZARD_UNDERWATER_FLOOR) {
                    if (!((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_BOTTLE) &&
                          (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_OBABA_DRINK))) {
                        if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                            restoreHudVisibility = true;
                        }
                        gSaveContext.buttonStatus[i] = BTN_DISABLED;
                    } else {
                        if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                            restoreHudVisibility = true;
                        }
                        gSaveContext.buttonStatus[i] = BTN_ENABLED;
                    }
                } else {
                    if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                        restoreHudVisibility = true;
                    }
                    gSaveContext.buttonStatus[i] = BTN_DISABLED;
                }
            } else if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                gSaveContext.buttonStatus[i] = BTN_ENABLED;
                restoreHudVisibility = true;
            }
        }

        if (restoreHudVisibility) {
            gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
        }

        if ((play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
            if (CutsceneManager_GetCurrentCsId() == CS_ID_NONE) {
                Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
            }
        }
    } else if (player->stateFlags1 & PLAYER_STATE1_200000) {
        // First person view
        for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
            if (GET_CUR_FORM_BTN_ITEM(i) != ITEM_LENS_OF_TRUTH) {
                if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                    restoreHudVisibility = true;
                }
                gSaveContext.buttonStatus[i] = BTN_DISABLED;
            } else {
                if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                    restoreHudVisibility = true;
                }
                gSaveContext.buttonStatus[i] = BTN_ENABLED;
            }
        }

        if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
            restoreHudVisibility = true;
        }
    } else if (player->stateFlags1 & PLAYER_STATE1_2000) {
        // Hanging from a ledge
        if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
            restoreHudVisibility = true;
            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
        }
    } else {
        // End of special event cases

        // B button
        if ((interfaceCtx->bButtonDoAction == DO_ACTION_EXPLODE) && (player->currentMask == PLAYER_MASK_BLAST) &&
            (player->blastMaskTimer != 0)) {
            // Cooldown period for blast mask
            if (gSaveContext.bButtonStatus != BTN_DISABLED) {
                gSaveContext.bButtonStatus = BTN_DISABLED;
                restoreHudVisibility = true;
            }
        } else {
            // default to enabled
            if (gSaveContext.bButtonStatus == BTN_DISABLED) {
                gSaveContext.bButtonStatus = BTN_ENABLED;
                restoreHudVisibility = true;
            }

            // Apply B button restriction
            if (interfaceCtx->restrictions.bButton == 0) {
                if ((BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOW) ||
                    (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMB) ||
                    (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMBCHU)) {
                    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_NONE) {
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
                    }

                    if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_ENABLED) {
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] =
                            ITEM_SWORD_KOKIRI + GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) - EQUIP_VALUE_SWORD_KOKIRI;
                    }

                    BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = gSaveContext.buttonStatus[EQUIP_SLOT_B];

                    if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_NONE) {
                        Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                    }
                    restoreHudVisibility = true;
                } else if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_NONE) {
                    if (interfaceCtx->bButtonDoAction != 0) {
                        if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                            restoreHudVisibility = true;
                            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
                        }
                    } else {
                        if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
                            restoreHudVisibility = true;
                            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
                        }
                    }
                } else if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_NONE) {
                    if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
                        restoreHudVisibility = true;
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
                    }
                } else {
                    if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                        restoreHudVisibility = true;
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
                    }
                }
            } else if (interfaceCtx->restrictions.bButton != 0) {
                if ((BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOW) ||
                    (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMB) ||
                    (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMBCHU)) {
                    if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_NONE) {
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
                    }

                    BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = gSaveContext.buttonStatus[EQUIP_SLOT_B];

                    if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_NONE) {
                        Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                    }
                    restoreHudVisibility = true;
                }
                if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
                    gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_DISABLED;
                    restoreHudVisibility = true;
                }
            }
        }

        // C buttons
        if (GET_PLAYER_FORM == player->transformation) {
            for (i = EQUIP_SLOT_C_LEFT; i <= EQUIP_SLOT_C_RIGHT; i++) {
                // Individual C button
                if (!gPlayerFormItemRestrictions[GET_PLAYER_FORM][GET_CUR_FORM_BTN_ITEM(i)]) {
                    // Item not usable in current playerForm
                    if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                        gSaveContext.buttonStatus[i] = BTN_DISABLED;
                        restoreHudVisibility = true;
                    }
                } else if (player->actor.id != ACTOR_PLAYER) {
                    // Currently not playing as the main player
                    if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                        gSaveContext.buttonStatus[i] = BTN_DISABLED;
                        restoreHudVisibility = true;
                    }
                } else if (player->currentMask == PLAYER_MASK_GIANT) {
                    // Currently wearing Giant's Mask
                    if (GET_CUR_FORM_BTN_ITEM(i) != ITEM_MASK_GIANT) {
                        if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                            gSaveContext.buttonStatus[i] = BTN_DISABLED;
                            restoreHudVisibility = true;
                        }
                    } else if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                        restoreHudVisibility = true;
                        gSaveContext.buttonStatus[i] = BTN_ENABLED;
                    }
                } else if (GET_CUR_FORM_BTN_ITEM(i) == ITEM_MASK_GIANT) {
                    // Giant's Mask is equipped
                    if (play->sceneId != SCENE_INISIE_BS) {
                        if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                            gSaveContext.buttonStatus[i] = BTN_DISABLED;
                            restoreHudVisibility = true;
                        }
                    } else if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                        restoreHudVisibility = true;
                        gSaveContext.buttonStatus[i] = BTN_ENABLED;
                    }
                } else if (GET_CUR_FORM_BTN_ITEM(i) == ITEM_MASK_FIERCE_DEITY) {
                    // Fierce Deity's Mask is equipped
                    if ((play->sceneId != SCENE_MITURIN_BS) && (play->sceneId != SCENE_HAKUGIN_BS) &&
                        (play->sceneId != SCENE_SEA_BS) && (play->sceneId != SCENE_INISIE_BS) &&
                        (play->sceneId != SCENE_LAST_BS)) {
                        if (gSaveContext.buttonStatus[i] != BTN_DISABLED) {
                            gSaveContext.buttonStatus[i] = BTN_DISABLED;
                            restoreHudVisibility = true;
                        }
                    } else if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                        restoreHudVisibility = true;
                        gSaveContext.buttonStatus[i] = BTN_ENABLED;
                    }
                } else {
                    // End of special item cases. Apply restrictions to buttons
                    if (interfaceCtx->restrictions.tradeItems != 0) {
                        if (((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MOONS_TEAR) &&
                             (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_PENDANT_OF_MEMORIES)) ||
                            ((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_BOTTLE) &&
                             (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_OBABA_DRINK)) ||
                            (GET_CUR_FORM_BTN_ITEM(i) == ITEM_OCARINA_OF_TIME)) {
                            if (gSaveContext.buttonStatus[i] == BTN_ENABLED) {
                                restoreHudVisibility = true;
                            }
                            gSaveContext.buttonStatus[i] = BTN_DISABLED;
                        }
                    } else if (interfaceCtx->restrictions.tradeItems == 0) {
                        if (((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MOONS_TEAR) &&
                             (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_PENDANT_OF_MEMORIES)) ||
                            ((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_BOTTLE) &&
                             (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_OBABA_DRINK)) ||
                            (GET_CUR_FORM_BTN_ITEM(i) == ITEM_OCARINA_OF_TIME)) {
                            if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                                restoreHudVisibility = true;
                            }
                            gSaveContext.buttonStatus[i] = BTN_ENABLED;
                        }
                    }

                    if (interfaceCtx->restrictions.masks != 0) {
                        if ((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MASK_DEKU) &&
                            (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_MASK_GIANT)) {
                            if (!gSaveContext.buttonStatus[i]) { // == BTN_ENABLED
                                restoreHudVisibility = true;
                            }
                            gSaveContext.buttonStatus[i] = BTN_DISABLED;
                        }
                    } else if (interfaceCtx->restrictions.masks == 0) {
                        if ((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MASK_DEKU) &&
                            (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_MASK_GIANT)) {
                            if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                                restoreHudVisibility = true;
                            }
                            gSaveContext.buttonStatus[i] = BTN_ENABLED;
                        }
                    }

                    if (interfaceCtx->restrictions.pictoBox != 0) {
                        if (GET_CUR_FORM_BTN_ITEM(i) == ITEM_PICTOGRAPH_BOX) {
                            if (!gSaveContext.buttonStatus[i]) { // == BTN_ENABLED
                                restoreHudVisibility = true;
                            }
                            gSaveContext.buttonStatus[i] = BTN_DISABLED;
                        }
                    } else if (interfaceCtx->restrictions.pictoBox == 0) {
                        if (GET_CUR_FORM_BTN_ITEM(i) == ITEM_PICTOGRAPH_BOX) {
                            if (gSaveContext.buttonStatus[i] == BTN_DISABLED) {
                                restoreHudVisibility = true;
                            }
                            gSaveContext.buttonStatus[i] = BTN_ENABLED;
                        }
                    }

                    if (interfaceCtx->restrictions.all != 0) {
                        if (!((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MOONS_TEAR) &&
                              (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_PENDANT_OF_MEMORIES)) &&
                            !((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_BOTTLE) &&
                              (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_OBABA_DRINK)) &&
                            (GET_CUR_FORM_BTN_ITEM(i) != ITEM_OCARINA_OF_TIME) &&
                            !((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MASK_DEKU) &&
                              (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_MASK_GIANT)) &&
                            (GET_CUR_FORM_BTN_ITEM(i) != ITEM_PICTOGRAPH_BOX)) {

                            if ((gSaveContext.buttonStatus[i] == BTN_ENABLED)) {
                                restoreHudVisibility = true;
                                gSaveContext.buttonStatus[i] = BTN_DISABLED;
                            }
                        }
                    } else if (interfaceCtx->restrictions.all == 0) {
                        if (!((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MOONS_TEAR) &&
                              (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_PENDANT_OF_MEMORIES)) &&
                            !((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_BOTTLE) &&
                              (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_OBABA_DRINK)) &&
                            (GET_CUR_FORM_BTN_ITEM(i) != ITEM_OCARINA_OF_TIME) &&
                            !((GET_CUR_FORM_BTN_ITEM(i) >= ITEM_MASK_DEKU) &&
                              (GET_CUR_FORM_BTN_ITEM(i) <= ITEM_MASK_GIANT)) &&
                            (GET_CUR_FORM_BTN_ITEM(i) != ITEM_PICTOGRAPH_BOX)) {

                            if ((gSaveContext.buttonStatus[i] == BTN_DISABLED)) {
                                restoreHudVisibility = true;
                                gSaveContext.buttonStatus[i] = BTN_ENABLED;
                            }
                        }
                    }
                }
            }
        }
    }

    if (restoreHudVisibility && (play->activeCamId == CAM_ID_MAIN) && (play->transitionTrigger == TRANS_TRIGGER_OFF) &&
        (play->transitionMode == TRANS_MODE_OFF)) {
        gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
        Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
    }
}

void Interface_UpdateButtonsPart1(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    s32 pad;
    s32 restoreHudVisibility = false;

    if (gSaveContext.save.cutsceneIndex < 0xFFF0) {
        gSaveContext.hudVisibilityForceButtonAlphasByStatus = false;
        if ((player->stateFlags1 & PLAYER_STATE1_800000) || CHECK_WEEKEVENTREG(WEEKEVENTREG_08_01) ||
            (!CHECK_EVENTINF(EVENTINF_41) && (play->unk_1887C >= 2))) {
            // Riding Epona OR Honey & Darling minigame OR Horseback balloon minigame OR related to swamp boat
            // (non-minigame?)
            if ((player->stateFlags1 & PLAYER_STATE1_800000) && (player->currentMask == PLAYER_MASK_BLAST) &&
                (gSaveContext.bButtonStatus == BTN_DISABLED)) {
                // Riding Epona with blast mask?
                restoreHudVisibility = true;
                gSaveContext.bButtonStatus = BTN_ENABLED;
            }

            if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_NONE) {
                if ((player->transformation == PLAYER_FORM_DEKU) && CHECK_WEEKEVENTREG(WEEKEVENTREG_08_01)) {
                    gSaveContext.hudVisibilityForceButtonAlphasByStatus = true;
                    if (play->sceneId == SCENE_BOWLING) {
                        if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
                        }
                    } else if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_ENABLED;
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_ENABLED;
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_ENABLED;
                    }

                    Interface_SetHudVisibility(HUD_VISIBILITY_B_MAGIC);
                } else {
                    if ((BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_BOW) &&
                        (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_BOMB) &&
                        (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_BOMBCHU)) {
                        gSaveContext.hudVisibilityForceButtonAlphasByStatus = true;
                        gSaveContext.buttonStatus[EQUIP_SLOT_B] = BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B);
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_ENABLED;
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_ENABLED;
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_ENABLED;
                        if (play->sceneId == SCENE_BOWLING) {
                            if (CURRENT_DAY == 1) {
                                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOMBCHU;
                            } else if (CURRENT_DAY == 2) {
                                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOMB;
                            } else {
                                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOW;
                            }
                            Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
                        } else {
                            BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOW;

                            if (play->unk_1887C >= 2) {
                                Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                            } else if (gSaveContext.save.saveInfo.inventory.items[SLOT_BOW] == ITEM_NONE) {
                                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_NONE;
                            } else {
                                Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                            }

                            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
                            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
                            Interface_SetHudVisibility(HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE);
                        }
                    }

                    if (play->transitionMode != TRANS_MODE_OFF) {
                        Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
                    } else if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) &&
                               (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0)) &&
                               (Cutscene_GetSceneLayer(play) != 0) && (play->transitionTrigger == TRANS_TRIGGER_OFF)) {
                        Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
                    } else if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) && CHECK_EVENTINF(EVENTINF_35)) {
                        Interface_SetHudVisibility(HUD_VISIBILITY_B_MINIMAP);
                    } else if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_82_08) &&
                               (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE)) {
                        Interface_SetHudVisibility(HUD_VISIBILITY_B);
                    } else if (play->unk_1887C >= 2) {
                        Interface_SetHudVisibility(HUD_VISIBILITY_B);
                    } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_08_01)) {
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
                        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
                        Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
                    } else if (player->stateFlags1 & PLAYER_STATE1_800000) {
                        Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
                    }
                }
            } else {
                if (player->stateFlags1 & PLAYER_STATE1_800000) {
                    Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
                }

                if (play->sceneId == SCENE_BOWLING) {
                    if (CURRENT_DAY == 1) {
                        BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOMBCHU;
                    } else if (CURRENT_DAY == 2) {
                        BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOMB;
                    } else {
                        BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOW;
                    }
                    gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
                    gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
                    gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
                } else {
                    BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_BOW;
                }

                if (play->unk_1887C >= 2) {
                    Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                } else if (gSaveContext.save.saveInfo.inventory.items[SLOT_BOW] == ITEM_NONE) {
                    BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_NONE;
                } else {
                    Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
                }

                if (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED) {
                    gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
                    restoreHudVisibility = true;
                }

                gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
                gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
                gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
                Interface_SetHudVisibility(HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_WITH_OVERWRITE);

                if (play->transitionMode != TRANS_MODE_OFF) {
                    Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
                } else if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) &&
                           (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0)) &&
                           (Cutscene_GetSceneLayer(play) != 0) && (play->transitionTrigger == TRANS_TRIGGER_OFF)) {
                    Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
                } else if (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) {
                    Interface_SetHudVisibility(HUD_VISIBILITY_B);
                } else if (play->unk_1887C >= 2) {
                    Interface_SetHudVisibility(HUD_VISIBILITY_B);
                } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_08_01)) {
                    gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
                    gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
                    gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
                    Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
                } else if (player->stateFlags1 & PLAYER_STATE1_800000) {
                    Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
                }
            }
        } else if (sPictoState != PICTO_BOX_STATE_OFF) {
            // Related to pictograph
            if (sPictoState == PICTO_BOX_STATE_LENS) {
                if (!(play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON)) {
                    Play_CompressI8ToI5((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : gWorkBuffer,
                                        (u8*)((void)0, gSaveContext.pictoPhotoI5),
                                        PICTO_PHOTO_WIDTH * PICTO_PHOTO_HEIGHT);
                    interfaceCtx->unk_222 = interfaceCtx->unk_224 = 0;
                    restoreHudVisibility = true;
                    sPictoState = PICTO_BOX_STATE_OFF;
                } else if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_B)) {
                    play->actorCtx.flags &= ~ACTORCTX_FLAG_PICTO_BOX_ON;
                    interfaceCtx->unk_222 = interfaceCtx->unk_224 = 0;
                    restoreHudVisibility = true;
                    sPictoState = PICTO_BOX_STATE_OFF;
                } else if (CHECK_BTN_ALL(CONTROLLER1(&play->state)->press.button, BTN_A) || (func_801A5100() == 1)) {
                    if (!CHECK_EVENTINF(EVENTINF_41) ||
                        (CHECK_EVENTINF(EVENTINF_41) && (CutsceneManager_GetCurrentCsId() == CS_ID_NONE))) {
                        Audio_PlaySfx(NA_SE_SY_CAMERA_SHUTTER);
                        SREG(89) = 1;
                        play->haltAllActors = true;
                        sPictoState = PICTO_BOX_STATE_SETUP_PHOTO;
                        sPictoPhotoBeingTaken = true;
                    }
                }
            } else if ((sPictoState >= PICTO_BOX_STATE_SETUP_PHOTO) && (Message_GetState(&play->msgCtx) == 4) &&
                       Message_ShouldAdvance(play)) {
                play->haltAllActors = false;
                player->stateFlags1 &= ~PLAYER_STATE1_200;
                Message_CloseTextbox(play);
                if (play->msgCtx.choiceIndex != 0) {
                    Audio_PlaySfx_MessageCancel();
                    func_80115844(play, DO_ACTION_STOP);
                    Interface_SetHudVisibility(HUD_VISIBILITY_A_B);
                    sPictoState = PICTO_BOX_STATE_LENS;
                    REMOVE_QUEST_ITEM(QUEST_PICTOGRAPH);
                } else {
                    Audio_PlaySfx_MessageDecide();
                    interfaceCtx->unk_222 = interfaceCtx->unk_224 = 0;
                    restoreHudVisibility = true;
                    Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
                    sPictoState = PICTO_BOX_STATE_OFF;
                    if (sPictoPhotoBeingTaken) {
                        Play_CompressI8ToI5((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : gWorkBuffer,
                                            (u8*)((void)0, gSaveContext.pictoPhotoI5),
                                            PICTO_PHOTO_WIDTH * PICTO_PHOTO_HEIGHT);
                        Snap_RecordPictographedActors(play);
                    }
                    play->actorCtx.flags &= ~ACTORCTX_FLAG_PICTO_BOX_ON;
                    SET_QUEST_ITEM(QUEST_PICTOGRAPH);
                    sPictoPhotoBeingTaken = false;
                }
            }
        } else if ((gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE) &&
                   (gSaveContext.save.entrance == ENTRANCE(WATERFALL_RAPIDS, 1)) &&
                   (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
            // Beaver race minigame
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
            Interface_SetHudVisibility(HUD_VISIBILITY_A_B_MINIMAP);
        } else if ((gSaveContext.save.entrance == ENTRANCE(GORON_RACETRACK, 1)) &&
                   (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
            // Goron race minigame
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_DISABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_DISABLED;
            Interface_SetHudVisibility(HUD_VISIBILITY_A_B_HEARTS_MAGIC_MINIMAP);
        } else if (play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON) {
            // Related to pictograph
            if (!CHECK_QUEST_ITEM(QUEST_PICTOGRAPH)) {
                func_80115844(play, DO_ACTION_STOP);
                Interface_SetHudVisibility(HUD_VISIBILITY_A_B);
                sPictoState = PICTO_BOX_STATE_LENS;
            } else {
                Play_DecompressI5ToI8((u8*)((void)0, gSaveContext.pictoPhotoI5),
                                      (play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : gWorkBuffer,
                                      PICTO_PHOTO_WIDTH * PICTO_PHOTO_HEIGHT);
                play->haltAllActors = true;
                sPictoState = PICTO_BOX_STATE_SETUP_PHOTO;
            }
        } else {
            // Continue processing the remaining cases
            Interface_UpdateButtonsPart2(play);
        }
    }

    if (restoreHudVisibility) {
        gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
        if ((play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
            Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
        }
    }
}

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

/**
 * @param play PlayState
 * @param flag 0 for default update, 1 for simplified update
 */
void Interface_UpdateButtonsAlt(PlayState* play, u16 flag) {
    if (flag) {
        if ((BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOW) ||
            (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMB) ||
            (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMBCHU) ||
            (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_FISHING_ROD) ||
            (gSaveContext.buttonStatus[EQUIP_SLOT_B] == BTN_DISABLED)) {
            if ((BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOW) ||
                (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMB) ||
                (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_BOMBCHU) ||
                (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_FISHING_ROD)) {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = gSaveContext.buttonStatus[EQUIP_SLOT_B];
                Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
            }
        } else if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_NONE) {
            if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_NONE) {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = gSaveContext.buttonStatus[EQUIP_SLOT_B];
                Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
            }
        }

        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] =
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
        Interface_SetHudVisibility(HUD_VISIBILITY_ALL_NO_MINIMAP_W_DISABLED);
    } else {
        gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] =
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
        Interface_UpdateButtonsPart1(play);
    }
}

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
    if (item >= ITEM_DEKU_STICKS_5) {
        slot = SLOT(sExtraItemBases[item - ITEM_DEKU_STICKS_5]);
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
            gSaveContext.save.saveInfo.playerData.healthCapacity += 0x10;
            gSaveContext.save.saveInfo.playerData.health += 0x10;
        }
        return ITEM_NONE;

    } else if (item == ITEM_HEART_CONTAINER) {
        gSaveContext.save.saveInfo.playerData.healthCapacity += 0x10;
        gSaveContext.save.saveInfo.playerData.health += 0x10;
        return ITEM_NONE;

    } else if ((item >= ITEM_SONG_SONATA) && (item <= ITEM_SONG_LULLABY_INTRO)) {
        SET_QUEST_ITEM(item - ITEM_SONG_SONATA + QUEST_SONG_SONATA);
        return ITEM_NONE;

    } else if ((item >= ITEM_SWORD_KOKIRI) && (item <= ITEM_SWORD_GILDED)) {
        SET_EQUIP_VALUE(EQUIP_TYPE_SWORD, item - ITEM_SWORD_KOKIRI + EQUIP_VALUE_SWORD_KOKIRI);
        CUR_FORM_EQUIP(EQUIP_SLOT_B) = item;
        Interface_LoadItemIconImpl(play, EQUIP_SLOT_B);
        if (item == ITEM_SWORD_RAZOR) {
            gSaveContext.save.saveInfo.playerData.swordHealth = 100;
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

    } else if (item == ITEM_DEKU_STICK_UPGRADE_20) {
        if (INV_CONTENT(ITEM_DEKU_STICK) != ITEM_DEKU_STICK) {
            INV_CONTENT(ITEM_DEKU_STICK) = ITEM_DEKU_STICK;
        }
        Inventory_ChangeUpgrade(UPG_DEKU_STICKS, 2);
        AMMO(ITEM_DEKU_STICK) = CAPACITY(UPG_DEKU_STICKS, 2);
        return ITEM_NONE;

    } else if (item == ITEM_DEKU_STICK_UPGRADE_30) {
        if (INV_CONTENT(ITEM_DEKU_STICK) != ITEM_DEKU_STICK) {
            INV_CONTENT(ITEM_DEKU_STICK) = ITEM_DEKU_STICK;
        }
        Inventory_ChangeUpgrade(UPG_DEKU_STICKS, 3);
        AMMO(ITEM_DEKU_STICK) = CAPACITY(UPG_DEKU_STICKS, 3);
        return ITEM_NONE;

    } else if (item == ITEM_DEKU_NUT_UPGRADE_30) {
        if (INV_CONTENT(ITEM_DEKU_NUT) != ITEM_DEKU_NUT) {
            INV_CONTENT(ITEM_DEKU_NUT) = ITEM_DEKU_NUT;
        }
        Inventory_ChangeUpgrade(UPG_DEKU_NUTS, 2);
        AMMO(ITEM_DEKU_NUT) = CAPACITY(UPG_DEKU_NUTS, 2);
        return ITEM_NONE;

    } else if (item == ITEM_DEKU_NUT_UPGRADE_40) {
        if (INV_CONTENT(ITEM_DEKU_NUT) != ITEM_DEKU_NUT) {
            INV_CONTENT(ITEM_DEKU_NUT) = ITEM_DEKU_NUT;
        }
        Inventory_ChangeUpgrade(UPG_DEKU_NUTS, 3);
        AMMO(ITEM_DEKU_NUT) = CAPACITY(UPG_DEKU_NUTS, 3);
        return ITEM_NONE;

    } else if (item == ITEM_DEKU_STICK) {
        if (INV_CONTENT(ITEM_DEKU_STICK) != ITEM_DEKU_STICK) {
            Inventory_ChangeUpgrade(UPG_DEKU_STICKS, 1);
            AMMO(ITEM_DEKU_STICK) = 1;
        } else {
            AMMO(ITEM_DEKU_STICK)++;
            if (AMMO(ITEM_DEKU_STICK) > CUR_CAPACITY(UPG_DEKU_STICKS)) {
                AMMO(ITEM_DEKU_STICK) = CUR_CAPACITY(UPG_DEKU_STICKS);
            }
        }

    } else if ((item == ITEM_DEKU_STICKS_5) || (item == ITEM_DEKU_STICKS_10)) {
        if (INV_CONTENT(ITEM_DEKU_STICK) != ITEM_DEKU_STICK) {
            Inventory_ChangeUpgrade(UPG_DEKU_STICKS, 1);
            AMMO(ITEM_DEKU_STICK) = sAmmoRefillCounts[item - ITEM_DEKU_STICKS_5];
        } else {
            AMMO(ITEM_DEKU_STICK) += sAmmoRefillCounts[item - ITEM_DEKU_STICKS_5];
            if (AMMO(ITEM_DEKU_STICK) > CUR_CAPACITY(UPG_DEKU_STICKS)) {
                AMMO(ITEM_DEKU_STICK) = CUR_CAPACITY(UPG_DEKU_STICKS);
            }
        }

        item = ITEM_DEKU_STICK;

    } else if (item == ITEM_DEKU_NUT) {
        if (INV_CONTENT(ITEM_DEKU_NUT) != ITEM_DEKU_NUT) {
            Inventory_ChangeUpgrade(UPG_DEKU_NUTS, 1);
            AMMO(ITEM_DEKU_NUT) = 1;
        } else {
            AMMO(ITEM_DEKU_NUT)++;
            if (AMMO(ITEM_DEKU_NUT) > CUR_CAPACITY(UPG_DEKU_NUTS)) {
                AMMO(ITEM_DEKU_NUT) = CUR_CAPACITY(UPG_DEKU_NUTS);
            }
        }

    } else if ((item == ITEM_DEKU_NUTS_5) || (item == ITEM_DEKU_NUTS_10)) {
        if (INV_CONTENT(ITEM_DEKU_NUT) != ITEM_DEKU_NUT) {
            Inventory_ChangeUpgrade(UPG_DEKU_NUTS, 1);
            AMMO(ITEM_DEKU_NUT) += sAmmoRefillCounts[item - ITEM_DEKU_NUTS_5];
        } else {
            AMMO(ITEM_DEKU_NUT) += sAmmoRefillCounts[item - ITEM_DEKU_NUTS_5];
            if (AMMO(ITEM_DEKU_NUT) > CUR_CAPACITY(UPG_DEKU_NUTS)) {
                AMMO(ITEM_DEKU_NUT) = CUR_CAPACITY(UPG_DEKU_NUTS);
            }
        }
        item = ITEM_DEKU_NUT;

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
        if (gSaveContext.save.saveInfo.inventory.items[SLOT_BOMB] != ITEM_BOMB) {
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
        if (gSaveContext.save.saveInfo.inventory.items[SLOT_BOMBCHU] != ITEM_BOMBCHU) {
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

    } else if (item == ITEM_OCARINA_OF_TIME) {
        INV_CONTENT(ITEM_OCARINA_OF_TIME) = ITEM_OCARINA_OF_TIME;
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

    } else if (item == ITEM_MAGIC_JAR_SMALL) {
        Magic_Add(play, MAGIC_NORMAL_METER / 2);
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_12_80)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_12_80);
            return ITEM_NONE;
        }
        return item;

    } else if (item == ITEM_MAGIC_JAR_BIG) {
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
            if (gSaveContext.save.saveInfo.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.saveInfo.inventory.items[slot + i] = ITEM_POTION_RED;
                return ITEM_NONE;
            }
        }
        return item;

    } else if ((item == ITEM_MILK_BOTTLE) || (item == ITEM_POE) || (item == ITEM_GOLD_DUST) || (item == ITEM_CHATEAU) ||
               (item == ITEM_HYLIAN_LOACH)) {
        slot = SLOT(item);

        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.saveInfo.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.saveInfo.inventory.items[slot + i] = item;
                return ITEM_NONE;
            }
        }
        return item;

    } else if (item == ITEM_BOTTLE) {
        slot = SLOT(item);

        for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
            if (gSaveContext.save.saveInfo.inventory.items[slot + i] == ITEM_NONE) {
                gSaveContext.save.saveInfo.inventory.items[slot + i] = item;
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
                if (gSaveContext.save.saveInfo.inventory.items[slot + i] == ITEM_BOTTLE) {
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

                    gSaveContext.save.saveInfo.inventory.items[slot + i] = item;
                    return ITEM_NONE;
                }
            }
        } else {
            for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
                if (gSaveContext.save.saveInfo.inventory.items[slot + i] == ITEM_NONE) {
                    gSaveContext.save.saveInfo.inventory.items[slot + i] = item;
                    return ITEM_NONE;
                }
            }
        }

    } else if ((item >= ITEM_MOONS_TEAR) && (item <= ITEM_MASK_GIANT)) {
        temp = INV_CONTENT(item);
        INV_CONTENT(item) = item;
        if ((item >= ITEM_MOONS_TEAR) && (item <= ITEM_PENDANT_OF_MEMORIES) && (temp != ITEM_NONE)) {
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

    temp = gSaveContext.save.saveInfo.inventory.items[slot];
    INV_CONTENT(item) = item;
    return temp;
}

u8 Item_CheckObtainabilityImpl(u8 item) {
    s16 i;
    u8 slot;
    u8 bottleSlot;

    slot = SLOT(item);
    if (item >= ITEM_DEKU_STICKS_5) {
        slot = SLOT(sExtraItemBases[item - ITEM_DEKU_STICKS_5]);
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

    } else if ((item == ITEM_OCARINA_OF_TIME) || (item == ITEM_BOMBCHU) || (item == ITEM_HOOKSHOT) ||
               (item == ITEM_LENS_OF_TRUTH) || (item == ITEM_SWORD_GREAT_FAIRY) || (item == ITEM_PICTOGRAPH_BOX)) {
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

    } else if ((item >= ITEM_DEKU_STICK_UPGRADE_20) && (item <= ITEM_DEKU_NUT_UPGRADE_40)) {
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

    } else if ((item == ITEM_MAGIC_JAR_SMALL) || (item == ITEM_MAGIC_JAR_BIG)) {
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
                if (gSaveContext.save.saveInfo.inventory.items[bottleSlot + i] == ITEM_BOTTLE) {
                    return ITEM_NONE;
                }
            }
        } else {
            for (i = BOTTLE_FIRST; i < BOTTLE_MAX; i++) {
                if (gSaveContext.save.saveInfo.inventory.items[bottleSlot + i] == ITEM_NONE) {
                    return ITEM_NONE;
                }
            }
        }
    } else if ((item >= ITEM_MOONS_TEAR) && (item <= ITEM_MASK_GIANT)) {
        return ITEM_NONE;
    }

    return gSaveContext.save.saveInfo.inventory.items[slot];
}

u8 Item_CheckObtainability(u8 item) {
    return Item_CheckObtainabilityImpl(item);
}

void Inventory_DeleteItem(s16 item, s16 slot) {
    s16 btn;

    gSaveContext.save.saveInfo.inventory.items[slot] = ITEM_NONE;

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
        if (gSaveContext.save.saveInfo.inventory.items[i] == oldItem) {
            gSaveContext.save.saveInfo.inventory.items[i] = newItem;

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

        // Is simply checking if (GET_PLAYER_FORM == PLAYER_FORM_FIERCE_DEITY)
        if ((((GET_PLAYER_FORM > 0) && (GET_PLAYER_FORM < 4)) ? 1 : GET_PLAYER_FORM >> 1) == 0) {
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
        if (gSaveContext.save.saveInfo.inventory.items[slot] == ITEM_BOTTLE) {
            return true;
        }
    }
    return false;
}

s32 Inventory_HasItemInBottle(u8 item) {
    s32 slot;

    for (slot = SLOT_BOTTLE_1; slot <= SLOT_BOTTLE_6; slot++) {
        if (gSaveContext.save.saveInfo.inventory.items[slot] == item) {
            return true;
        }
    }
    return false;
}

void Inventory_UpdateBottleItem(PlayState* play, u8 item, u8 btn) {
    gSaveContext.save.saveInfo.inventory.items[GET_CUR_FORM_BTN_SLOT(btn)] = item;
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
        if (gSaveContext.save.saveInfo.inventory.items[bottleSlot + i] == ITEM_FAIRY) {
            for (btn = EQUIP_SLOT_C_LEFT; btn <= EQUIP_SLOT_C_RIGHT; btn++) {
                if (GET_CUR_FORM_BTN_ITEM(btn) == ITEM_FAIRY) {
                    SET_CUR_FORM_BTN_ITEM(btn, ITEM_BOTTLE);
                    Interface_LoadItemIconImpl(play, btn);
                    bottleSlot = GET_CUR_FORM_BTN_SLOT(btn);
                    i = 0;
                    break;
                }
            }
            gSaveContext.save.saveInfo.inventory.items[bottleSlot + i] = ITEM_BOTTLE;
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

    gSaveContext.save.saveInfo.inventory.items[slot] = item;

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
        Audio_PlaySfx(NA_SE_SY_HP_RECOVER);
    } else if (gSaveContext.save.saveInfo.playerData.doubleDefense && (healthChange < 0)) {
        healthChange >>= 1;
    }

    gSaveContext.save.saveInfo.playerData.health += healthChange;

    if (((void)0, gSaveContext.save.saveInfo.playerData.health) >
        ((void)0, gSaveContext.save.saveInfo.playerData.healthCapacity)) {
        gSaveContext.save.saveInfo.playerData.health = gSaveContext.save.saveInfo.playerData.healthCapacity;
    }

    if (gSaveContext.save.saveInfo.playerData.health <= 0) {
        gSaveContext.save.saveInfo.playerData.health = 0;
        return false;
    } else {
        return true;
    }
}

void Health_GiveHearts(s16 hearts) {
    gSaveContext.save.saveInfo.playerData.healthCapacity += hearts * 0x10;
}

void Rupees_ChangeBy(s16 rupeeChange) {
    gSaveContext.rupeeAccumulator += rupeeChange;
}

void Inventory_ChangeAmmo(s16 item, s16 ammoChange) {
    if (item == ITEM_DEKU_STICK) {
        AMMO(ITEM_DEKU_STICK) += ammoChange;

        if (AMMO(ITEM_DEKU_STICK) >= CUR_CAPACITY(UPG_DEKU_STICKS)) {
            AMMO(ITEM_DEKU_STICK) = CUR_CAPACITY(UPG_DEKU_STICKS);
        } else if (AMMO(ITEM_DEKU_STICK) < 0) {
            AMMO(ITEM_DEKU_STICK) = 0;
        }

    } else if (item == ITEM_DEKU_NUT) {
        AMMO(ITEM_DEKU_NUT) += ammoChange;

        if (AMMO(ITEM_DEKU_NUT) >= CUR_CAPACITY(UPG_DEKU_NUTS)) {
            AMMO(ITEM_DEKU_NUT) = CUR_CAPACITY(UPG_DEKU_NUTS);
        } else if (AMMO(ITEM_DEKU_NUT) < 0) {
            AMMO(ITEM_DEKU_NUT) = 0;
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
    if (((void)0, gSaveContext.save.saveInfo.playerData.magic) < ((void)0, gSaveContext.magicCapacity)) {
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
    if (!gSaveContext.save.saveInfo.playerData.isMagicAcquired) {
        return false;
    }

    // Not enough magic available to consume
    if ((gSaveContext.save.saveInfo.playerData.magic - magicToConsume) < 0) {
        if (gSaveContext.magicCapacity != 0) {
            Audio_PlaySfx(NA_SE_SY_ERROR);
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
                Audio_PlaySfx(NA_SE_SY_ERROR);
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
                Audio_PlaySfx(NA_SE_SY_ERROR);
                return false;
            }

        case MAGIC_CONSUME_LENS:
            if (gSaveContext.magicState == MAGIC_STATE_IDLE) {
                if (gSaveContext.save.saveInfo.playerData.magic != 0) {
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
                Audio_PlaySfx(NA_SE_SY_ERROR);
                return false;
            }

        case MAGIC_CONSUME_GORON_ZORA:
            // Goron spiked rolling or Zora electric barrier
            if (gSaveContext.save.saveInfo.playerData.magic != 0) {
                interfaceCtx->magicConsumptionTimer = 10;
                gSaveContext.magicState = MAGIC_STATE_CONSUME_GORON_ZORA_SETUP;
                return true;
            } else {
                return false;
            }

        case MAGIC_CONSUME_GIANTS_MASK:
            // Wearing Giant's Mask
            if (gSaveContext.magicState == MAGIC_STATE_IDLE) {
                if (gSaveContext.save.saveInfo.playerData.magic != 0) {
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
                gSaveContext.save.saveInfo.playerData.magic -= magicToConsume;
                return true;
            } else {
                Audio_PlaySfx(NA_SE_SY_ERROR);
                return false;
            }
    }

    return false;
}

void Magic_UpdateAddRequest(void) {
    if (gSaveContext.isMagicRequested) {
        gSaveContext.save.saveInfo.playerData.magic += 4;
        Audio_PlaySfx(NA_SE_SY_GAUGE_UP - SFX_FLAG);

        if (((void)0, gSaveContext.save.saveInfo.playerData.magic) >= ((void)0, gSaveContext.magicCapacity)) {
            gSaveContext.save.saveInfo.playerData.magic = gSaveContext.magicCapacity;
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
            magicCapacityTarget = gSaveContext.save.saveInfo.playerData.magicLevel * MAGIC_NORMAL_METER;
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
            gSaveContext.save.saveInfo.playerData.magic += 0x10;

            if ((gSaveContext.gameMode == GAMEMODE_NORMAL) && (gSaveContext.sceneLayer < 4)) {
                Audio_PlaySfx(NA_SE_SY_GAUGE_UP - SFX_FLAG);
            }

            if (((void)0, gSaveContext.save.saveInfo.playerData.magic) >= ((void)0, gSaveContext.magicFillTarget)) {
                gSaveContext.save.saveInfo.playerData.magic = gSaveContext.magicFillTarget;
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
                gSaveContext.save.saveInfo.playerData.magic =
                    ((void)0, gSaveContext.save.saveInfo.playerData.magic) - ((void)0, gSaveContext.magicToConsume);
                if (gSaveContext.save.saveInfo.playerData.magic <= 0) {
                    gSaveContext.save.saveInfo.playerData.magic = 0;
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
                (msgCtx->msgMode == MSGMODE_NONE) && (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
                (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF) &&
                !Play_InCsMode(play)) {

                if ((gSaveContext.save.saveInfo.playerData.magic == 0) ||
                    ((Player_GetEnvironmentalHazard(play) >= PLAYER_ENV_HAZARD_UNDERWATER_FLOOR) &&
                     (Player_GetEnvironmentalHazard(play) <= PLAYER_ENV_HAZARD_UNDERWATER_FREE)) ||
                    ((BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) != ITEM_LENS_OF_TRUTH) &&
                     (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) != ITEM_LENS_OF_TRUTH) &&
                     (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) != ITEM_LENS_OF_TRUTH)) ||
                    !play->actorCtx.lensActive) {
                    // Deactivate Lens of Truth and set magic state to idle
                    play->actorCtx.lensActive = false;
                    Audio_PlaySfx(NA_SE_SY_GLASSMODE_OFF);
                    gSaveContext.magicState = MAGIC_STATE_IDLE;
                    sMagicMeterOutlinePrimRed = sMagicMeterOutlinePrimGreen = sMagicMeterOutlinePrimBlue = 255;
                    break;
                }

                interfaceCtx->magicConsumptionTimer--;
                if (interfaceCtx->magicConsumptionTimer == 0) {
                    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                        gSaveContext.save.saveInfo.playerData.magic--;
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
                gSaveContext.save.saveInfo.playerData.magic -= 2;
            }
            if (gSaveContext.save.saveInfo.playerData.magic <= 0) {
                gSaveContext.save.saveInfo.playerData.magic = 0;
            }
            gSaveContext.magicState = MAGIC_STATE_CONSUME_GORON_ZORA;
            // fallthrough
        case MAGIC_STATE_CONSUME_GORON_ZORA:
            if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == 0) &&
                (msgCtx->msgMode == MSGMODE_NONE) && (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
                (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
                if (!Play_InCsMode(play)) {
                    interfaceCtx->magicConsumptionTimer--;
                    if (interfaceCtx->magicConsumptionTimer == 0) {
                        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                            gSaveContext.save.saveInfo.playerData.magic--;
                        }
                        if (gSaveContext.save.saveInfo.playerData.magic <= 0) {
                            gSaveContext.save.saveInfo.playerData.magic = 0;
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
                (msgCtx->msgMode == MSGMODE_NONE) && (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
                (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF)) {
                if (!Play_InCsMode(play)) {
                    interfaceCtx->magicConsumptionTimer--;
                    if (interfaceCtx->magicConsumptionTimer == 0) {
                        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_DRANK_CHATEAU_ROMANI)) {
                            gSaveContext.save.saveInfo.playerData.magic--;
                        }
                        if (gSaveContext.save.saveInfo.playerData.magic <= 0) {
                            gSaveContext.save.saveInfo.playerData.magic = 0;
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

    if (gSaveContext.save.saveInfo.playerData.magicLevel != 0) {
        if (gSaveContext.save.saveInfo.playerData.healthCapacity > 0xA0) {
            magicBarY = 42; // two rows of hearts
        } else {
            magicBarY = 34; // one row of hearts
        }

        Gfx_SetupDL39_Overlay(play->state.gfxCtx);

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
                                (((void)0, gSaveContext.save.saveInfo.playerData.magic) + 26) << 2,
                                (magicBarY + 10) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

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
                ((((void)0, gSaveContext.save.saveInfo.playerData.magic) - ((void)0, gSaveContext.magicToConsume)) + 26)
                    << 2,
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
                                (((void)0, gSaveContext.save.saveInfo.playerData.magic) + 26) << 2,
                                (magicBarY + 10) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Interface_SetPerspectiveView(PlayState* play, s32 topY, s32 bottomY, s32 leftX, s32 rightX) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Vec3f eye;
    Vec3f at;
    Vec3f up;

    eye.x = eye.y = eye.z = 0.0f;
    at.x = at.y = 0.0f;
    at.z = -1.0f;
    up.x = up.z = 0.0f;
    up.y = 1.0f;

    View_LookAt(&interfaceCtx->view, &eye, &at, &up);

    interfaceCtx->viewport.topY = topY;
    interfaceCtx->viewport.bottomY = bottomY;
    interfaceCtx->viewport.leftX = leftX;
    interfaceCtx->viewport.rightX = rightX;
    View_SetViewport(&interfaceCtx->view, &interfaceCtx->viewport);

    View_SetPerspective(&interfaceCtx->view, 60.0f, 10.0f, 60.0f);
    View_ApplyPerspectiveToOverlay(&interfaceCtx->view);
}

void Interface_SetOrthoView(InterfaceContext* interfaceCtx) {
    SET_FULLSCREEN_VIEWPORT(&interfaceCtx->view);
    View_ApplyOrthoToOverlay(&interfaceCtx->view);
}

void Interface_DrawItemButtons(PlayState* play) {
    static TexturePtr cUpLabelTextures[] = {
        gTatlCUpENGTex, gTatlCUpENGTex, gTatlCUpGERTex, gTatlCUpFRATex, gTatlCUpESPTex,
    };
    static s16 startButtonLeftPos[] = {
        // Remnant of OoT
        130, 136, 136, 136, 136,
    };
    static s16 D_801BFAF4[] = {
        0x1D, // EQUIP_SLOT_B
        0x1B, // EQUIP_SLOT_C_LEFT
        0x1B, // EQUIP_SLOT_C_DOWN
        0x1B, // EQUIP_SLOT_C_RIGHT
    };
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);
    PauseContext* pauseCtx = &play->pauseCtx;
    MessageContext* msgCtx = &play->msgCtx;
    s16 temp; // Used as both an alpha value and a button index
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(OVERLAY_DISP++);
    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    // B Button Color & Texture
    OVERLAY_DISP = Gfx_DrawTexRectIA8_DropShadow(
        OVERLAY_DISP, gButtonBackgroundTex, 0x20, 0x20, D_801BF9D4[EQUIP_SLOT_B], D_801BF9DC[EQUIP_SLOT_B],
        D_801BFAF4[EQUIP_SLOT_B], D_801BFAF4[EQUIP_SLOT_B], D_801BF9E4[EQUIP_SLOT_B] * 2, D_801BF9E4[EQUIP_SLOT_B] * 2,
        100, 255, 120, interfaceCtx->bAlpha);
    gDPPipeSync(OVERLAY_DISP++);

    // C-Left Button Color & Texture
    OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, D_801BF9D4[EQUIP_SLOT_C_LEFT], D_801BF9DC[EQUIP_SLOT_C_LEFT],
                                           D_801BFAF4[EQUIP_SLOT_C_LEFT], D_801BFAF4[EQUIP_SLOT_C_LEFT],
                                           D_801BF9E4[EQUIP_SLOT_C_LEFT] * 2, D_801BF9E4[EQUIP_SLOT_C_LEFT] * 2, 255,
                                           240, 0, interfaceCtx->cLeftAlpha);
    // C-Down Button Color & Texture
    OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, D_801BF9D4[EQUIP_SLOT_C_DOWN], D_801BF9DC[EQUIP_SLOT_C_DOWN],
                                           D_801BFAF4[EQUIP_SLOT_C_DOWN], D_801BFAF4[EQUIP_SLOT_C_DOWN],
                                           D_801BF9E4[EQUIP_SLOT_C_DOWN] * 2, D_801BF9E4[EQUIP_SLOT_C_DOWN] * 2, 255,
                                           240, 0, interfaceCtx->cDownAlpha);
    // C-Right Button Color & Texture
    OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, D_801BF9D4[EQUIP_SLOT_C_RIGHT], D_801BF9DC[EQUIP_SLOT_C_RIGHT],
                                           D_801BFAF4[EQUIP_SLOT_C_RIGHT], D_801BFAF4[EQUIP_SLOT_C_RIGHT],
                                           D_801BF9E4[EQUIP_SLOT_C_RIGHT] * 2, D_801BF9E4[EQUIP_SLOT_C_RIGHT] * 2, 255,
                                           240, 0, interfaceCtx->cRightAlpha);

    if (!IS_PAUSE_STATE_GAMEOVER) {
        if ((play->pauseCtx.state != PAUSE_STATE_OFF) || (play->pauseCtx.debugEditor != DEBUG_EDITOR_NONE)) {
            OVERLAY_DISP = Gfx_DrawRect_DropShadow(OVERLAY_DISP, 0x88, 0x11, 0x16, 0x16, 0x5B6, 0x5B6, 0xFF, 0x82, 0x3C,
                                                   interfaceCtx->startAlpha);
            // Start Button Texture, Color & Label
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->startAlpha);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 0);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, interfaceCtx->doActionSegment + DO_ACTION_TEX_SIZE * 2, G_IM_FMT_IA,
                                   DO_ACTION_TEX_WIDTH, DO_ACTION_TEX_HEIGHT, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(OVERLAY_DISP++, 0x01F8, 0x0054, 0x02D4, 0x009C, G_TX_RENDERTILE, 0, 0, 0x04A6, 0x04A6);
        }
    }

    if (interfaceCtx->tatlCalling && (play->pauseCtx.state == PAUSE_STATE_OFF) &&
        (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) && (play->csCtx.state == CS_STATE_IDLE) &&
        (sPictoState == PICTO_BOX_STATE_OFF)) {
        if (sCUpInvisible == 0) {
            // C-Up Button Texture, Color & Label (Tatl Text)
            gDPPipeSync(OVERLAY_DISP++);

            if ((gSaveContext.hudVisibility == HUD_VISIBILITY_NONE) ||
                (gSaveContext.hudVisibility == HUD_VISIBILITY_NONE_ALT) ||
                (gSaveContext.hudVisibility == HUD_VISIBILITY_A_HEARTS_MAGIC_WITH_OVERWRITE) ||
                (msgCtx->msgMode != MSGMODE_NONE)) {
                temp = 0;
            } else if (player->stateFlags1 & PLAYER_STATE1_200000) {
                temp = 70;
            } else {
                temp = interfaceCtx->aAlpha;
            }

            OVERLAY_DISP =
                Gfx_DrawRect_DropShadow(OVERLAY_DISP, 0xFE, 0x10, 0x10, 0x10, 0x800, 0x800, 0xFF, 0xF0, 0, temp);

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, temp);
            gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 0);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPLoadTextureBlock_4b(OVERLAY_DISP++, cUpLabelTextures[gSaveContext.options.language], G_IM_FMT_IA, 32, 12,
                                   0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(OVERLAY_DISP++, 0x03DC, 0x0048, 0x045C, 0x0078, G_TX_RENDERTILE, 0, 0, 1 << 10,
                                1 << 10);
        }

        sCUpTimer--;
        if (sCUpTimer == 0) {
            sCUpInvisible ^= 1;
            sCUpTimer = 10;
        }
    }

    gDPPipeSync(OVERLAY_DISP++);

    // Empty C Button Arrows
    for (temp = EQUIP_SLOT_C_LEFT; temp <= EQUIP_SLOT_C_RIGHT; temp++) {
        if (GET_CUR_FORM_BTN_ITEM(temp) > 0xF0) {
            if (temp == EQUIP_SLOT_C_LEFT) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 240, 0, interfaceCtx->cLeftAlpha);
            } else if (temp == EQUIP_SLOT_C_DOWN) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 240, 0, interfaceCtx->cDownAlpha);
            } else { // EQUIP_SLOT_C_RIGHT
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 240, 0, interfaceCtx->cRightAlpha);
            }
            OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, ((u8*)gButtonBackgroundTex + ((32 * 32) * (temp + 1))),
                                              0x20, 0x20, D_801BF9D4[temp], D_801BF9DC[temp], D_801BFAF4[temp],
                                              D_801BFAF4[temp], D_801BF9E4[temp] * 2, D_801BF9E4[temp] * 2);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Interface_DrawItemIconTexture(PlayState* play, TexturePtr texture, s16 button) {
    static s16 D_801BFAFC[] = { 30, 24, 24, 24 };

    OPEN_DISPS(play->state.gfxCtx);

    gDPLoadTextureBlock(OVERLAY_DISP++, texture, G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(OVERLAY_DISP++, D_801BF9D4[button] << 2, D_801BF9DC[button] << 2,
                        (D_801BF9D4[button] + D_801BFAFC[button]) << 2, (D_801BF9DC[button] + D_801BFAFC[button]) << 2,
                        G_TX_RENDERTILE, 0, 0, D_801BF9BC[button] << 1, D_801BF9BC[button] << 1);

    CLOSE_DISPS(play->state.gfxCtx);
}

s16 D_801BFB04[] = { 0xA2, 0xE4, 0xFA, 0x110 };
s16 D_801BFB0C[] = { 0x23, 0x23, 0x33, 0x23 };

void Interface_DrawAmmoCount(PlayState* play, s16 button, s16 alpha) {
    u8 i;
    u16 ammo;

    OPEN_DISPS(play->state.gfxCtx);

    i = ((void)0, GET_CUR_FORM_BTN_ITEM(button));

    if ((i == ITEM_DEKU_STICK) || (i == ITEM_DEKU_NUT) || (i == ITEM_BOMB) || (i == ITEM_BOW) ||
        ((i >= ITEM_BOW_FIRE) && (i <= ITEM_BOW_LIGHT)) || (i == ITEM_BOMBCHU) || (i == ITEM_POWDER_KEG) ||
        (i == ITEM_MAGIC_BEANS) || (i == ITEM_PICTOGRAPH_BOX)) {

        if ((i >= ITEM_BOW_FIRE) && (i <= ITEM_BOW_LIGHT)) {
            i = ITEM_BOW;
        }

        ammo = AMMO(i);

        if (i == ITEM_PICTOGRAPH_BOX) {
            if (!CHECK_QUEST_ITEM(QUEST_PICTOGRAPH)) {
                ammo = 0;
            } else {
                ammo = 1;
            }
        }

        gDPPipeSync(OVERLAY_DISP++);

        if ((button == EQUIP_SLOT_B) && (gSaveContext.minigameStatus == MINIGAME_STATUS_ACTIVE)) {
            ammo = play->interfaceCtx.minigameAmmo;
        } else if ((button == EQUIP_SLOT_B) && (play->unk_1887C > 1)) {
            ammo = play->unk_1887C - 1;
        } else if (((i == ITEM_BOW) && (AMMO(i) == CUR_CAPACITY(UPG_QUIVER))) ||
                   ((i == ITEM_BOMB) && (AMMO(i) == CUR_CAPACITY(UPG_BOMB_BAG))) ||
                   ((i == ITEM_DEKU_STICK) && (AMMO(i) == CUR_CAPACITY(UPG_DEKU_STICKS))) ||
                   ((i == ITEM_DEKU_NUT) && (AMMO(i) == CUR_CAPACITY(UPG_DEKU_NUTS))) ||
                   ((i == ITEM_BOMBCHU) && (AMMO(i) == CUR_CAPACITY(UPG_BOMB_BAG))) ||
                   ((i == ITEM_POWDER_KEG) && (ammo == 1)) || ((i == ITEM_PICTOGRAPH_BOX) && (ammo == 1)) ||
                   ((i == ITEM_MAGIC_BEANS) && (ammo == 20))) {
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 120, 255, 0, alpha);
        }

        if ((u32)ammo == 0) {
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 100, 100, 100, alpha);
        }

        for (i = 0; ammo >= 10; i++) {
            ammo -= 10;
        }

        // Draw upper digit (tens)
        if ((u32)i != 0) {
            OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, ((u8*)gAmmoDigit0Tex + ((8 * 8) * i)), 8, 8,
                                              D_801BFB04[button], D_801BFB0C[button], 8, 8, 1 << 10, 1 << 10);
        }

        // Draw lower digit (ones)
        OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, ((u8*)gAmmoDigit0Tex + ((8 * 8) * ammo)), 8, 8,
                                          D_801BFB04[button] + 6, D_801BFB0C[button], 8, 8, 1 << 10, 1 << 10);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Interface_DrawBButtonIcons(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    Player* player = GET_PLAYER(play);

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(OVERLAY_DISP++);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->bAlpha);
    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if ((interfaceCtx->unk_222 == 0) && (player->stateFlags3 & PLAYER_STATE3_1000000)) {
        if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_DISABLED) {
            Interface_DrawItemIconTexture(play, interfaceCtx->iconItemSegment, EQUIP_SLOT_B);
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

            Interface_DrawAmmoCount(play, EQUIP_SLOT_B, interfaceCtx->bAlpha);
        }
    } else if ((!interfaceCtx->unk_21C && (interfaceCtx->unk_222 == 0)) ||
               ((interfaceCtx->unk_21C &&
                 ((BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) < ITEM_SWORD_KOKIRI) ||
                  (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) > ITEM_SWORD_GILDED)) &&
                 BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_NONE) &&
                (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_DEKU_NUT))) {
        if ((player->transformation == PLAYER_FORM_FIERCE_DEITY) || (player->transformation == PLAYER_FORM_HUMAN)) {
            if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) != ITEM_NONE) {
                Interface_DrawItemIconTexture(play, interfaceCtx->iconItemSegment, EQUIP_SLOT_B);
                if ((player->stateFlags1 & PLAYER_STATE1_800000) || CHECK_WEEKEVENTREG(WEEKEVENTREG_08_01) ||
                    (play->unk_1887C >= 2)) {
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE,
                                      0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

                    if ((play->sceneId != SCENE_SYATEKI_MIZU) && (play->sceneId != SCENE_SYATEKI_MORI) &&
                        (play->sceneId != SCENE_BOWLING) &&
                        ((gSaveContext.minigameStatus != MINIGAME_STATUS_ACTIVE) ||
                         (gSaveContext.save.entrance != ENTRANCE(ROMANI_RANCH, 0))) &&
                        ((gSaveContext.minigameStatus != MINIGAME_STATUS_ACTIVE) || !CHECK_EVENTINF(EVENTINF_35)) &&
                        (!CHECK_WEEKEVENTREG(WEEKEVENTREG_31_80) || (play->unk_1887C != 100))) {
                        Interface_DrawAmmoCount(play, EQUIP_SLOT_B, interfaceCtx->bAlpha);
                    }
                }
            }
        }
    } else if (interfaceCtx->unk_222 != 0) {
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->bAlpha);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, interfaceCtx->doActionSegment + 0x480, G_IM_FMT_IA, 48, 16, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);

        D_801BF9B0 = 1024.0f / (D_801BF9B4[gSaveContext.options.language] / 100.0f);

        gSPTextureRectangle(
            OVERLAY_DISP++, (D_801BF9C4[gSaveContext.options.language] * 4),
            (D_801BF9C8[gSaveContext.options.language] * 4), ((D_801BF9C4[gSaveContext.options.language] + 0x30) << 2),
            ((D_801BF9C8[gSaveContext.options.language] + 0x10) << 2), G_TX_RENDERTILE, 0, 0, D_801BF9B0, D_801BF9B0);
    } else if (interfaceCtx->bButtonDoAction != DO_ACTION_NONE) {
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->bAlpha);
        gDPLoadTextureBlock_4b(OVERLAY_DISP++, interfaceCtx->doActionSegment + 0x600, G_IM_FMT_IA, 48, 16, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);

        D_801BF9B0 = 1024.0f / (D_801BF9B4[gSaveContext.options.language] / 100.0f);

        gSPTextureRectangle(
            OVERLAY_DISP++, (D_801BF9C4[gSaveContext.options.language] * 4),
            (D_801BF9C8[gSaveContext.options.language] * 4), ((D_801BF9C4[gSaveContext.options.language] + 0x30) << 2),
            ((D_801BF9C8[gSaveContext.options.language] + 0x10) << 2), G_TX_RENDERTILE, 0, 0, D_801BF9B0, D_801BF9B0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * Draws the icons and ammo for each of the C buttons
 */
void Interface_DrawCButtonIcons(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(OVERLAY_DISP++);

    // C-Left Button Icon & Ammo Count
    if (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_LEFT) < ITEM_F0) {
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->cLeftAlpha);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        Interface_DrawItemIconTexture(play, interfaceCtx->iconItemSegment + 0x1000, EQUIP_SLOT_C_LEFT);
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        Interface_DrawAmmoCount(play, EQUIP_SLOT_C_LEFT, interfaceCtx->cLeftAlpha);
    }

    gDPPipeSync(OVERLAY_DISP++);

    // C-Down Button Icon & Ammo Count
    if (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_DOWN) < ITEM_F0) {
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->cDownAlpha);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        Interface_DrawItemIconTexture(play, interfaceCtx->iconItemSegment + 0x2000, EQUIP_SLOT_C_DOWN);
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        Interface_DrawAmmoCount(play, EQUIP_SLOT_C_DOWN, interfaceCtx->cDownAlpha);
    }

    gDPPipeSync(OVERLAY_DISP++);

    // C-Right Button Icon & Ammo Count
    if (BUTTON_ITEM_EQUIP(0, EQUIP_SLOT_C_RIGHT) < ITEM_F0) {
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->cRightAlpha);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        Interface_DrawItemIconTexture(play, interfaceCtx->iconItemSegment + 0x3000, EQUIP_SLOT_C_RIGHT);
        gDPPipeSync(OVERLAY_DISP++);
        gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        Interface_DrawAmmoCount(play, EQUIP_SLOT_C_RIGHT, interfaceCtx->cRightAlpha);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Interface_DrawAButton(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    s16 aAlpha;

    OPEN_DISPS(play->state.gfxCtx);

    aAlpha = interfaceCtx->aAlpha;

    if (aAlpha > 100) {
        aAlpha = 100;
    }

    Gfx_SetupDL42_Overlay(play->state.gfxCtx);

    Interface_SetPerspectiveView(play, 25 + R_A_BTN_Y_OFFSET, 70 + R_A_BTN_Y_OFFSET, 192, 237);

    gSPClearGeometryMode(OVERLAY_DISP++, G_CULL_BOTH);
    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);

    Matrix_Translate(0.0f, 0.0f, -38.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_RotateXFApply(interfaceCtx->aButtonRoll / 10000.0f);

    // Draw A button Shadow
    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(OVERLAY_DISP++);
    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[4], 4, 0);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, aAlpha);

    OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gButtonBackgroundTex, 32, 32, 0);

    // Draw A Button Colored
    gDPPipeSync(OVERLAY_DISP++);
    Interface_SetPerspectiveView(play, 23 + R_A_BTN_Y_OFFSET, 68 + R_A_BTN_Y_OFFSET, 190, 235);
    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[0], 4, 0);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 100, 200, 255, interfaceCtx->aAlpha);
    gSP1Quadrangle(OVERLAY_DISP++, 0, 2, 3, 1, 0);

    // Draw A Button Do-Action
    gDPPipeSync(OVERLAY_DISP++);
    Interface_SetPerspectiveView(play, 23 + R_A_BTN_Y_OFFSET, 68 + R_A_BTN_Y_OFFSET, 190, 235);
    gSPSetGeometryMode(OVERLAY_DISP++, G_CULL_BACK);
    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, interfaceCtx->aAlpha);
    gDPSetEnvColor(OVERLAY_DISP++, 0, 0, 0, 0);

    Matrix_Translate(0.0f, 0.0f, D_801BF9CC[gSaveContext.options.language] / 10.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_RotateXFApply(interfaceCtx->aButtonRoll / 10000.0f);
    gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[8], 4, 0);

    // Draw Action Label
    if (((interfaceCtx->aButtonState <= A_BTN_STATE_1) || (interfaceCtx->aButtonState == A_BTN_STATE_3))) {
        OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, interfaceCtx->doActionSegment, 3, DO_ACTION_TEX_WIDTH,
                                         DO_ACTION_TEX_HEIGHT, 0);
    } else {
        OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, interfaceCtx->doActionSegment + DO_ACTION_TEX_SIZE, 3,
                                         DO_ACTION_TEX_WIDTH, DO_ACTION_TEX_HEIGHT, 0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

static s16 sMagicArrowEffectsR[] = { 255, 100, 255 };
static s16 sMagicArrowEffectsG[] = { 0, 100, 255 };
static s16 sMagicArrowEffectsB[] = { 0, 255, 100 };

void Interface_DrawPauseMenuEquippingIcons(PlayState* play) {
    InterfaceContext* interfaceCtx = &play->interfaceCtx;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 temp;

    OPEN_DISPS(play->state.gfxCtx);

    gDPPipeSync(OVERLAY_DISP++);

    // This is needed as `Interface_DrawPauseMenuEquippingIcons` is call immediately
    // after `Interface_DrawAButton`, which sets the view to perspective mode
    Interface_SetOrthoView(interfaceCtx);

    if ((pauseCtx->state == PAUSE_STATE_MAIN) && ((pauseCtx->mainState == PAUSE_MAIN_STATE_EQUIP_ITEM) ||
                                                  (pauseCtx->mainState == PAUSE_MAIN_STATE_EQUIP_MASK))) {
        // Inventory Equip Effects
        gSPSegment(OVERLAY_DISP++, 0x08, pauseCtx->iconItemSegment);
        Gfx_SetupDL42_Overlay(play->state.gfxCtx);
        gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
        gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        pauseCtx->cursorVtx[16].v.ob[0] = pauseCtx->cursorVtx[18].v.ob[0] = pauseCtx->equipAnimX / 10;
        pauseCtx->cursorVtx[17].v.ob[0] = pauseCtx->cursorVtx[19].v.ob[0] =
            pauseCtx->cursorVtx[16].v.ob[0] + (pauseCtx->equipAnimScale / 10);
        pauseCtx->cursorVtx[16].v.ob[1] = pauseCtx->cursorVtx[17].v.ob[1] = pauseCtx->equipAnimY / 10;
        pauseCtx->cursorVtx[18].v.ob[1] = pauseCtx->cursorVtx[19].v.ob[1] =
            pauseCtx->cursorVtx[16].v.ob[1] - (pauseCtx->equipAnimScale / 10);

        if (pauseCtx->equipTargetItem < 0xB5) {
            // Normal Equip (icon goes from the inventory slot to the C button when equipping it)
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, pauseCtx->equipAnimAlpha);
            gSPVertex(OVERLAY_DISP++, &pauseCtx->cursorVtx[16], 4, 0);
            gDPLoadTextureBlock(OVERLAY_DISP++, gItemIcons[pauseCtx->equipTargetItem], G_IM_FMT_RGBA, G_IM_SIZ_32b, 32,
                                32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
        } else {
            // Magic Arrow Equip Effect
            temp = pauseCtx->equipTargetItem - 0xB5;
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sMagicArrowEffectsR[temp], sMagicArrowEffectsG[temp],
                            sMagicArrowEffectsB[temp], pauseCtx->equipAnimAlpha);

            if ((pauseCtx->equipAnimAlpha > 0) && (pauseCtx->equipAnimAlpha < 255)) {
                temp = (pauseCtx->equipAnimAlpha / 8) / 2;
                pauseCtx->cursorVtx[16].v.ob[0] = pauseCtx->cursorVtx[18].v.ob[0] =
                    pauseCtx->cursorVtx[16].v.ob[0] - temp;
                pauseCtx->cursorVtx[17].v.ob[0] = pauseCtx->cursorVtx[19].v.ob[0] =
                    pauseCtx->cursorVtx[16].v.ob[0] + temp * 2 + 32;
                pauseCtx->cursorVtx[16].v.ob[1] = pauseCtx->cursorVtx[17].v.ob[1] =
                    pauseCtx->cursorVtx[16].v.ob[1] + temp;
                pauseCtx->cursorVtx[18].v.ob[1] = pauseCtx->cursorVtx[19].v.ob[1] =
                    pauseCtx->cursorVtx[16].v.ob[1] - temp * 2 - 32;
            }

            gSPVertex(OVERLAY_DISP++, &pauseCtx->cursorVtx[16], 4, 0);
            gDPLoadTextureBlock(OVERLAY_DISP++, gMagicArrowEquipEffectTex, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
        }

        gSP1Quadrangle(OVERLAY_DISP++, 0, 2, 3, 1, 0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * Draws either the analog three-day clock or the digital final-hours clock
 */
void Interface_DrawClock(PlayState* play) {
    static s16 sThreeDayClockAlpha = 255;
    static s16 sClockAlphaTimer1 = 0;
    static s16 sClockAlphaTimer2 = 0;
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
    static s16 sClockInvDiamondPrimRed = 0;
    static s16 sClockInvDiamondPrimGreen = 155;
    static s16 sClockInvDiamondPrimBlue = 255;
    static s16 sClockInvDiamondEnvRed = 0;
    static s16 sClockInvDiamondEnvGreen = 0;
    static s16 sClockInvDiamondEnvBlue = 0;
    static s16 sClockInvDiamondTimer = 15;
    static s16 sClockInvDiamondTargetIndex = 0;
    static s16 sClockInvDiamondPrimRedTargets[] = { 100, 0 };
    static s16 sClockInvDiamondPrimGreenTargets[] = { 205, 155 };
    static s16 sClockInvDiamondPrimBlueTargets[] = { 255, 255 };
    static s16 sClockInvDiamondEnvRedTargets[] = { 30, 0 };
    static s16 sClockInvDiamondEnvGreenTargets[] = { 30, 0 };
    static s16 sClockInvDiamondEnvBlueTargets[] = { 100, 0 };
    static s16 sFinalHoursClockDigitsRedTargets[] = { 255, 0 };
    static s16 sFinalHoursClockFrameEnvRedTargets[] = { 100, 0 };
    static s16 sFinalHoursClockFrameEnvGreenTargets[] = { 30, 0 };
    static s16 sFinalHoursClockFrameEnvBlueTargets[] = { 100, 0 };
    static TexturePtr sFinalHoursDigitTextures[] = {
        gFinalHoursClockDigit0Tex, gFinalHoursClockDigit1Tex, gFinalHoursClockDigit2Tex, gFinalHoursClockDigit3Tex,
        gFinalHoursClockDigit4Tex, gFinalHoursClockDigit5Tex, gFinalHoursClockDigit6Tex, gFinalHoursClockDigit7Tex,
        gFinalHoursClockDigit8Tex, gFinalHoursClockDigit9Tex, gFinalHoursClockColonTex,
    };
    static s16 sFinalHoursDigitSlotPosXOffset[] = {
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
    s32 pad1;
    s16 sp1C6;
    s16 currentHour;
    u16 time;
    s16 pad2;
    s16 colorStep;
    s16 finalHoursClockSlots[8];
    s16 index;

    OPEN_DISPS(play->state.gfxCtx);

    if ((R_TIME_SPEED != 0) &&
        ((msgCtx->msgMode == MSGMODE_NONE) || ((play->actorCtx.flags & ACTORCTX_FLAG_1) && !Play_InCsMode(play)) ||
         (msgCtx->msgMode == MSGMODE_NONE) || ((msgCtx->currentTextId >= 0x100) && (msgCtx->currentTextId <= 0x200)) ||
         (gSaveContext.gameMode == GAMEMODE_END_CREDITS)) &&
        !FrameAdvance_IsEnabled(&play->state) && !Environment_IsTimeStopped() && (gSaveContext.save.day <= 3)) {
        /**
         * Section: Changes Clock's transparancy depending if Player is moving or not and possibly other things
         */
        if (gSaveContext.hudVisibility == HUD_VISIBILITY_ALL) {
            if (func_801234D4(play)) {
                sThreeDayClockAlpha = 80;
                sClockAlphaTimer1 = 5;
                sClockAlphaTimer2 = 20;
            } else if (sClockAlphaTimer2 != 0) {
                sClockAlphaTimer2--;
            } else if (sClockAlphaTimer1 != 0) {
                colorStep = ABS_ALT(sThreeDayClockAlpha - 255) / sClockAlphaTimer1;
                sThreeDayClockAlpha += colorStep;

                if (sThreeDayClockAlpha >= 255) {
                    sThreeDayClockAlpha = 255;
                    sClockAlphaTimer1 = 0;
                }
            } else {
                if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
                    sThreeDayClockAlpha = 255;
                } else {
                    sThreeDayClockAlpha = interfaceCtx->bAlpha;
                }
                sClockAlphaTimer2 = 0;
                sClockAlphaTimer1 = 0;
            }
        } else {
            if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
                sThreeDayClockAlpha = 255;
            } else {
                sThreeDayClockAlpha = interfaceCtx->bAlpha;
            }
            sClockAlphaTimer2 = 0;
            sClockAlphaTimer1 = 0;
        }

        if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE)) {
            Gfx_SetupDL39_Overlay(play->state.gfxCtx);

            /**
             * Section: Draw Clock's Hour Lines
             */
            gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
            gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 130, 130, 130, sThreeDayClockAlpha);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);

            OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gThreeDayClockHourLinesTex, 4, 64, 35, 96, 180, 128, 35, 1,
                                             6, 0, 1 << 10, 1 << 10);

            /**
             * Section: Draw Clock's Border
             */
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, sThreeDayClockAlpha);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);

            //! @bug A texture height of 50 is given below. The texture is only 48 units height
            //!      resulting in this reading into the next texture. This results in a white
            //!      dot in the bottom center of the clock. For the three-day clock, this is
            //!      covered by the diamond. However, it can be seen by the final-hours clock.
            OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gThreeDayClockBorderTex, 4, 64, 50, 96, 168, 128, 50, 1, 6,
                                             0, 1 << 10, 1 << 10);

            if (((CURRENT_DAY >= 4) ||
                 ((CURRENT_DAY == 3) && (((void)0, gSaveContext.save.time) >= (CLOCK_TIME(0, 0) + 5)) &&
                  (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0))))) {
                Gfx_SetupDL42_Overlay(play->state.gfxCtx);
                gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            } else {
                /**
                 * Section: Draw Three-Day Clock's Diamond
                 */
                gDPPipeSync(OVERLAY_DISP++);

                // Time is slowed down to half speed with inverted song of time
                if (gSaveContext.save.timeSpeedOffset == -2) {
                    // Clock diamond is blue and flashes white
                    colorStep =
                        ABS_ALT(sClockInvDiamondPrimRed - sClockInvDiamondPrimRedTargets[sClockInvDiamondTargetIndex]) /
                        sClockInvDiamondTimer;
                    if (sClockInvDiamondPrimRed >= sClockInvDiamondPrimRedTargets[sClockInvDiamondTargetIndex]) {
                        sClockInvDiamondPrimRed -= colorStep;
                    } else {
                        sClockInvDiamondPrimRed += colorStep;
                    }

                    colorStep = ABS_ALT(sClockInvDiamondPrimGreen -
                                        sClockInvDiamondPrimGreenTargets[sClockInvDiamondTargetIndex]) /
                                sClockInvDiamondTimer;
                    if (sClockInvDiamondPrimGreen >= sClockInvDiamondPrimGreenTargets[sClockInvDiamondTargetIndex]) {
                        sClockInvDiamondPrimGreen -= colorStep;
                    } else {
                        sClockInvDiamondPrimGreen += colorStep;
                    }

                    colorStep = ABS_ALT(sClockInvDiamondPrimBlue -
                                        sClockInvDiamondPrimBlueTargets[sClockInvDiamondTargetIndex]) /
                                sClockInvDiamondTimer;
                    if (sClockInvDiamondPrimBlue >= sClockInvDiamondPrimBlueTargets[sClockInvDiamondTargetIndex]) {
                        sClockInvDiamondPrimBlue -= colorStep;
                    } else {
                        sClockInvDiamondPrimBlue += colorStep;
                    }

                    colorStep =
                        ABS_ALT(sClockInvDiamondEnvRed - sClockInvDiamondEnvRedTargets[sClockInvDiamondTargetIndex]) /
                        sClockInvDiamondTimer;
                    if (sClockInvDiamondEnvRed >= sClockInvDiamondEnvRedTargets[sClockInvDiamondTargetIndex]) {
                        sClockInvDiamondEnvRed -= colorStep;
                    } else {
                        sClockInvDiamondEnvRed += colorStep;
                    }

                    colorStep = ABS_ALT(sClockInvDiamondEnvGreen -
                                        sClockInvDiamondEnvGreenTargets[sClockInvDiamondTargetIndex]) /
                                sClockInvDiamondTimer;
                    if (sClockInvDiamondEnvGreen >= sClockInvDiamondEnvGreenTargets[sClockInvDiamondTargetIndex]) {
                        sClockInvDiamondEnvGreen -= colorStep;
                    } else {
                        sClockInvDiamondEnvGreen += colorStep;
                    }

                    colorStep =
                        ABS_ALT(sClockInvDiamondEnvBlue - sClockInvDiamondEnvBlueTargets[sClockInvDiamondTargetIndex]) /
                        sClockInvDiamondTimer;
                    if (sClockInvDiamondEnvBlue >= sClockInvDiamondEnvBlueTargets[sClockInvDiamondTargetIndex]) {
                        sClockInvDiamondEnvBlue -= colorStep;
                    } else {
                        sClockInvDiamondEnvBlue += colorStep;
                    }

                    sClockInvDiamondTimer--;

                    if (sClockInvDiamondTimer == 0) {
                        sClockInvDiamondPrimRed = sClockInvDiamondPrimRedTargets[sClockInvDiamondTargetIndex];
                        sClockInvDiamondPrimGreen = sClockInvDiamondPrimGreenTargets[sClockInvDiamondTargetIndex];
                        sClockInvDiamondPrimBlue = sClockInvDiamondPrimBlueTargets[sClockInvDiamondTargetIndex];
                        sClockInvDiamondEnvRed = sClockInvDiamondEnvRedTargets[sClockInvDiamondTargetIndex];
                        sClockInvDiamondEnvGreen = sClockInvDiamondEnvGreenTargets[sClockInvDiamondTargetIndex];
                        sClockInvDiamondEnvBlue = sClockInvDiamondEnvBlueTargets[sClockInvDiamondTargetIndex];
                        sClockInvDiamondTimer = 15;
                        sClockInvDiamondTargetIndex ^= 1;
                    }

                    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE,
                                      0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sClockInvDiamondPrimRed, sClockInvDiamondPrimGreen, 255,
                                    sThreeDayClockAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, sClockInvDiamondEnvRed, sClockInvDiamondEnvGreen,
                                   sClockInvDiamondEnvBlue, 0);
                } else {
                    // Clock diamond is green for regular timeSpeedOffset
                    gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 170, 100, sThreeDayClockAlpha);
                }

                OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, gThreeDayClockDiamondTex, 40, 32, 140, 190, 40, 32,
                                                  1 << 10, 1 << 10);

                /**
                 * Section: Draw Three-Day Clock's Day-Number over Diamond
                 */
                gDPPipeSync(OVERLAY_DISP++);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);

                OVERLAY_DISP = Gfx_DrawTexRectIA8(OVERLAY_DISP, interfaceCtx->doActionSegment + 0x780, 48, 27, 137, 192,
                                                  48, 27, 1 << 10, 1 << 10);

                /**
                 * Section: Draw Three-Day Clock's Star (for the Minute Tracker)
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

                Gfx_SetupDL42_Overlay(play->state.gfxCtx);

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
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSP1Quadrangle(OVERLAY_DISP++, 0, 2, 3, 1, 0);
            }

            /**
             * Section: Cuts off Three-Day Clock's Sun and Moon when they dip below the clock
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
             * Section: Draw Three-Day Clock's Sun (for the Day-Time Hours Tracker)
             */
            time = gSaveContext.save.time;
            sp1D8 = Math_SinS(time) * -40.0f;
            temp_f14 = Math_CosS(time) * -34.0f;

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 100, 110, sThreeDayClockAlpha);

            Matrix_Translate(sp1D8, temp_f14, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);

            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[16], 4, 0);

            OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gThreeDayClockSunHourTex, 24, 24, 0);

            /**
             * Section: Draw Three-Day Clock's Moon (for the Night-Time Hours Tracker)
             */
            sp1D8 = Math_SinS(time) * 40.0f;
            temp_f14 = Math_CosS(time) * 34.0f;

            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 55, sThreeDayClockAlpha);

            Matrix_Translate(sp1D8, temp_f14, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[20], 4, 0);

            OVERLAY_DISP = Gfx_DrawTexQuadIA8(OVERLAY_DISP, gThreeDayClockMoonHourTex, 24, 24, 0);

            /**
             * Section: Cuts off Three-Day Clock's Hour Digits when they dip below the clock
             */
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetScissorFrac(OVERLAY_DISP++, G_SC_NON_INTERLACE, 400, 620, 880,
                              R_THREE_DAY_CLOCK_HOUR_DIGIT_CUTOFF * 4.0f);

            /**
             * Section: Draws Three-Day Clock's Hour Digit Above the Sun
             */
            sp1CC = gSaveContext.save.time * 0.000096131f; // (2.0f * 3.15f / 0x10000)

            // Rotates Three-Day Clock's Hour Digit To Above the Sun
            Matrix_Translate(0.0f, R_THREE_DAY_CLOCK_Y_POS / 10.0f, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
            Matrix_RotateZF(-(sp1CC - 3.15f), MTXMODE_APPLY);
            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            // Draws Three-Day Clock's Hour Digit Above the Sun
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, sThreeDayClockAlpha);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[24], 8, 0);

            OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sThreeDayClockHourTextures[sp1C6], 4, 16, 11, 0);

            // Colours the Three-Day Clocks's Hour Digit Above the Sun
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);
            gSP1Quadrangle(OVERLAY_DISP++, 4, 6, 7, 5, 0);

            /**
             * Section: Draws Three-Day Clock's Hour Digit Above the Moon
             */

            // Rotates Three-Day Clock's Hour Digit To Above the Moon
            Matrix_Translate(0.0f, R_THREE_DAY_CLOCK_Y_POS / 10.0f, 0.0f, MTXMODE_NEW);
            Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
            Matrix_RotateZF(-sp1CC, MTXMODE_APPLY);
            gSPMatrix(OVERLAY_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            // Draws Three-Day Clock's Hour Digit Above the Moon
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetCombineLERP(OVERLAY_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0,
                              0, PRIMITIVE, 0);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 0, 0, 0, sThreeDayClockAlpha);
            gSPVertex(OVERLAY_DISP++, &interfaceCtx->actionVtx[32], 8, 0);

            OVERLAY_DISP = Gfx_DrawTexQuad4b(OVERLAY_DISP, sThreeDayClockHourTextures[sp1C6], 4, 16, 11, 0);

            // Colours the Three-Day Clocks's Hour Digit Above the Moon
            gDPPipeSync(OVERLAY_DISP++);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 155, sThreeDayClockAlpha);
            gSP1Quadrangle(OVERLAY_DISP++, 4, 6, 7, 5, 0);

            gSPDisplayList(OVERLAY_DISP++, D_0E000000.setScissor);

            // Final Hours
            if ((CURRENT_DAY >= 4) ||
                ((CURRENT_DAY == 3) && (((void)0, gSaveContext.save.time) >= (CLOCK_TIME(0, 0) + 5)) &&
                 (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0)))) {
                if (((void)0, gSaveContext.save.time) >= CLOCK_TIME(5, 0)) {
                    // The Final Hours clock will flash red

                    colorStep = ABS_ALT(sFinalHoursClockDigitsRed -
                                        sFinalHoursClockDigitsRedTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockDigitsRed >=
                        sFinalHoursClockDigitsRedTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockDigitsRed -= colorStep;
                    } else {
                        sFinalHoursClockDigitsRed += colorStep;
                    }

                    colorStep = ABS_ALT(sFinalHoursClockFrameEnvRed -
                                        sFinalHoursClockFrameEnvRedTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockFrameEnvRed >=
                        sFinalHoursClockFrameEnvRedTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockFrameEnvRed -= colorStep;
                    } else {
                        sFinalHoursClockFrameEnvRed += colorStep;
                    }

                    colorStep = ABS_ALT(sFinalHoursClockFrameEnvGreen -
                                        sFinalHoursClockFrameEnvGreenTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockFrameEnvGreen >=
                        sFinalHoursClockFrameEnvGreenTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockFrameEnvGreen -= colorStep;
                    } else {
                        sFinalHoursClockFrameEnvGreen += colorStep;
                    }

                    colorStep = ABS_ALT(sFinalHoursClockFrameEnvBlue -
                                        sFinalHoursClockFrameEnvBlueTargets[sFinalHoursClockColorTargetIndex]) /
                                sFinalHoursClockColorTimer;
                    if (sFinalHoursClockFrameEnvBlue >=
                        sFinalHoursClockFrameEnvBlueTargets[sFinalHoursClockColorTargetIndex]) {
                        sFinalHoursClockFrameEnvBlue -= colorStep;
                    } else {
                        sFinalHoursClockFrameEnvBlue += colorStep;
                    }

                    sFinalHoursClockColorTimer--;

                    if (sFinalHoursClockColorTimer == 0) {
                        sFinalHoursClockDigitsRed = sFinalHoursClockDigitsRedTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockFrameEnvRed =
                            sFinalHoursClockFrameEnvRedTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockFrameEnvGreen =
                            sFinalHoursClockFrameEnvGreenTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockFrameEnvBlue =
                            sFinalHoursClockFrameEnvBlueTargets[sFinalHoursClockColorTargetIndex];
                        sFinalHoursClockColorTimer = 6;
                        sFinalHoursClockColorTargetIndex ^= 1;
                    }
                }

                sp1E6 = sThreeDayClockAlpha;
                if (sp1E6 != 0) {
                    sp1E6 = 255;
                }

                Gfx_SetupDL39_Overlay(play->state.gfxCtx);

                /**
                 * Section: Draws Final-Hours Clock's Frame
                 */
                gSPMatrix(OVERLAY_DISP++, &gIdentityMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                gDPSetRenderMode(OVERLAY_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                                  PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 195, sp1E6);
                gDPSetEnvColor(OVERLAY_DISP++, sFinalHoursClockFrameEnvRed, sFinalHoursClockFrameEnvGreen,
                               sFinalHoursClockFrameEnvBlue, 0);

                OVERLAY_DISP = Gfx_DrawTexRect4b(OVERLAY_DISP, gFinalHoursClockFrameTex, 3, 80, 13, 119, 202, 80, 13, 0,
                                                 0, 0, 1 << 10, 1 << 10);

                timeUntilMoonCrash = TIME_UNTIL_MOON_CRASH;
                timeInMinutes = TIME_TO_MINUTES_F(timeUntilMoonCrash);

                // digits for hours
                finalHoursClockSlots[0] = 0;
                finalHoursClockSlots[1] = timeInMinutes / 60.0f;
                finalHoursClockSlots[2] = timeInMinutes / 60.0f;

                while (finalHoursClockSlots[1] >= 10) {
                    finalHoursClockSlots[0]++;
                    finalHoursClockSlots[1] -= 10;
                }

                // digits for minutes
                finalHoursClockSlots[3] = 0;
                finalHoursClockSlots[4] = (s32)timeInMinutes % 60;
                finalHoursClockSlots[5] = (s32)timeInMinutes % 60;

                while (finalHoursClockSlots[4] >= 10) {
                    finalHoursClockSlots[3]++;
                    finalHoursClockSlots[4] -= 10;
                }

                // digits for seconds
                finalHoursClockSlots[6] = 0;
                finalHoursClockSlots[7] =
                    timeUntilMoonCrash - (u32)((finalHoursClockSlots[2] * ((f32)0x10000 / 24)) +
                                               (finalHoursClockSlots[5] * ((f32)0x10000 / (24 * 60))));

                while (finalHoursClockSlots[7] >= 10) {
                    finalHoursClockSlots[6]++;
                    finalHoursClockSlots[7] -= 10;
                }

                // Colon separating hours from minutes and minutes from seconds
                finalHoursClockSlots[2] = finalHoursClockSlots[5] = 10;

                /**
                 * Section: Draws Final-Hours Clock's Digits
                 */
                gDPPipeSync(OVERLAY_DISP++);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sFinalHoursClockDigitsRed, 0, 0, sp1E6);
                gDPSetEnvColor(OVERLAY_DISP++, sFinalHoursClockDigitsRed, 0, 0, 0);

                for (sp1C6 = 0; sp1C6 < 8; sp1C6++) {
                    index = sFinalHoursDigitSlotPosXOffset[sp1C6];

                    OVERLAY_DISP =
                        Gfx_DrawTexRectI8(OVERLAY_DISP, sFinalHoursDigitTextures[finalHoursClockSlots[sp1C6]], 8, 8,
                                          index, 205, 8, 8, 1 << 10, 1 << 10);
                }
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

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

    Gfx_SetupDL42_Overlay(play->state.gfxCtx);

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
        SEQCMD_DISABLE_PLAY_SEQUENCES(false);
    }

    gSaveContext.save.day = 4;
    gSaveContext.save.eventDayCount = 4;
    gSaveContext.save.time = CLOCK_TIME(6, 0) + 10;
    play->nextEntrance = ENTRANCE(TERMINA_FIELD, 12);
    gSaveContext.nextCutsceneIndex = 0;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_FADE_WHITE;
}

void Interface_GetTimerDigits(OSTime time, s16* timerArr) {
    OSTime t = time;

    // 6 minutes
    timerArr[0] = t / SECONDS_TO_TIMER(360);
    t -= timerArr[0] * SECONDS_TO_TIMER(360);

    // minutes
    timerArr[1] = t / SECONDS_TO_TIMER(60);
    t -= timerArr[1] * SECONDS_TO_TIMER(60);

    // 10 seconds
    timerArr[3] = t / SECONDS_TO_TIMER(10);
    t -= timerArr[3] * SECONDS_TO_TIMER(10);

    // seconds
    timerArr[4] = t / SECONDS_TO_TIMER(1);
    t -= timerArr[4] * SECONDS_TO_TIMER(1);

    // 100 milliseconds
    timerArr[6] = t / SECONDS_TO_TIMER_PRECISE(0, 10);
    t -= timerArr[6] * SECONDS_TO_TIMER_PRECISE(0, 10);

    // 10 milliseconds
    timerArr[7] = t;
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
        ((msgCtx->msgMode == MSGMODE_NONE) || ((msgCtx->msgMode != MSGMODE_NONE) && (msgCtx->currentTextId >= 0x1BB2) &&
                                               (msgCtx->currentTextId <= 0x1BB6))) &&
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
                        PadMgr_SetInputRetraceCallback(Interface_PostmanTimerCallback, NULL);
                        break;

                    case TIMER_STATE_POSTMAN_STOP:
                        postmanTimerStopOsTime = gSaveContext.postmanTimerStopOsTime;
                        gSaveContext.timerCurTimes[TIMER_ID_POSTMAN] = OSTIME_TO_TIMER(
                            postmanTimerStopOsTime - ((void)0, gSaveContext.timerStartOsTimes[TIMER_ID_POSTMAN]) -
                            ((void)0, gSaveContext.timerPausedOsTimes[TIMER_ID_POSTMAN]));
                        gSaveContext.timerStates[TIMER_ID_POSTMAN] = TIMER_STATE_POSTMAN_END;
                        PadMgr_UnsetInputRetraceCallback(Interface_PostmanTimerCallback, NULL);
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
                        } else if (gSaveContext.save.saveInfo.playerData.healthCapacity > 0xA0) {
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

                        j = (gSaveContext.save.saveInfo.playerData.healthCapacity > 0xA0)
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
                            if (gSaveContext.save.saveInfo.playerData.healthCapacity > 0xA0) {
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
                    gSaveContext.timerCurTimes[sTimerId] =
                        SECONDS_TO_TIMER(gSaveContext.save.saveInfo.playerData.health >> 1);
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
                        gSaveContext.save.saveInfo.playerData.health = 0;
                        play->damagePlayer(play, -(((void)0, gSaveContext.save.saveInfo.playerData.health) + 2));
                    }
                    sEnvTimerActive = false;
                }

                Interface_GetTimerDigits(((void)0, gSaveContext.timerCurTimes[sTimerId]), sTimerDigits);

                // Use seconds to determine when to beep
                if (gSaveContext.timerCurTimes[sTimerId] > SECONDS_TO_TIMER(60)) {
                    if ((sTimerBeepSfxSeconds != sTimerDigits[4]) && (sTimerDigits[4] == 1)) {
                        Audio_PlaySfx(NA_SE_SY_MESSAGE_WOMAN);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                } else if (gSaveContext.timerCurTimes[sTimerId] > SECONDS_TO_TIMER(10)) {
                    if ((sTimerBeepSfxSeconds != sTimerDigits[4]) && ((sTimerDigits[4] % 2) != 0)) {
                        Audio_PlaySfx(NA_SE_SY_WARNING_COUNT_N);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                } else if (sTimerBeepSfxSeconds != sTimerDigits[4]) {
                    Audio_PlaySfx(NA_SE_SY_WARNING_COUNT_E);
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
                        Audio_PlaySfx(NA_SE_SY_WARNING_COUNT_E);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                } else if (CHECK_EVENTINF(EVENTINF_34) && (play->sceneId == SCENE_DEKUTES)) {
                    if ((((void)0, gSaveContext.timerCurTimes[sTimerId]) >
                         (gSaveContext.save.saveInfo.dekuPlaygroundHighScores[CURRENT_DAY - 1] -
                          SECONDS_TO_TIMER(9))) &&
                        (sTimerBeepSfxSeconds != sTimerDigits[4])) {
                        Audio_PlaySfx(NA_SE_SY_WARNING_COUNT_E);
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
                            gSaveContext.save.saveInfo.dekuPlaygroundHighScores[CURRENT_DAY - 1]) {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 50, 0, 255);
                        } else if (((void)0, gSaveContext.timerCurTimes[sTimerId]) >=
                                   (gSaveContext.save.saveInfo.dekuPlaygroundHighScores[CURRENT_DAY - 1] -
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
        ((msgCtx->msgMode == MSGMODE_NONE) || ((msgCtx->currentTextId >= 0x100) && (msgCtx->currentTextId <= 0x200)) ||
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

                    if (gSaveContext.save.saveInfo.inventory.items[i + SLOT_BOTTLE_1] == ITEM_HOT_SPRING_WATER) {
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

    Gfx_SetupDL39_Overlay(play->state.gfxCtx);

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
            if (gSaveContext.save.saveInfo.playerData.healthCapacity > 0xA0) {
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
                if (gSaveContext.save.saveInfo.playerData.healthCapacity > 0xA0) {
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
        Interface_SetOrthoView(interfaceCtx);

        // Draw Grandma's Story
        if (interfaceCtx->storyDmaStatus == STORY_DMA_DONE) {
            gSPSegment(OVERLAY_DISP++, 0x07, interfaceCtx->storySegment);
            Gfx_SetupDL39_Opa(play->state.gfxCtx);

            gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, pauseCtx->alpha);

            // Load in Grandma's Story
            gSPLoadUcodeL(OVERLAY_DISP++, gspS2DEX2_fifo);
            gfx = OVERLAY_DISP;
            Prerender_DrawBackground2D(&gfx, sStoryTextures[interfaceCtx->storyType],
                                       sStoryTLUTs[interfaceCtx->storyType], SCREEN_WIDTH, SCREEN_HEIGHT, 2, 1, 0x8000,
                                       0x100, 0.0f, 0.0f, 1.0f, 1.0f, 0);
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

        Gfx_SetupDL39_Overlay(play->state.gfxCtx);

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
        counterDigits[2] = gSaveContext.save.saveInfo.playerData.rupees;

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

            if (gSaveContext.save.saveInfo.playerData.rupees == CUR_CAPACITY(UPG_WALLET)) {
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 120, 255, 0, interfaceCtx->magicAlpha);
            } else if (gSaveContext.save.saveInfo.playerData.rupees != 0) {
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
            Target_Draw(&play->actorCtx.targetCtx, play);
        }

        Gfx_SetupDL39_Overlay(play->state.gfxCtx);

        Interface_DrawItemButtons(play);

        if (player->transformation == GET_PLAYER_FORM) {
            Interface_DrawBButtonIcons(play);
        }
        Interface_DrawCButtonIcons(play);

        Interface_DrawAButton(play);

        Interface_DrawPauseMenuEquippingIcons(play);

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

                    Gfx_SetupDL42_Overlay(play->state.gfxCtx);

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

        Gfx_SetupDL39_Overlay(play->state.gfxCtx);

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
            Play_CompressI8ToI5((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : gWorkBuffer,
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

            Gfx_SetupDL39_Overlay(play->state.gfxCtx);

            gDPSetRenderMode(OVERLAY_DISP++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            gDPSetCombineMode(OVERLAY_DISP++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 250, 160, 160, 255);

            // Picture is offset up by 33 pixels to give room for the message box at the bottom
            pictoRectTop = PICTO_PHOTO_TOPLEFT_Y - 33;
            for (sp2CC = 0; sp2CC < (PICTO_PHOTO_HEIGHT / 8); sp2CC++, pictoRectTop += 8) {
                pictoRectLeft = PICTO_PHOTO_TOPLEFT_X;
                gDPLoadTextureBlock(OVERLAY_DISP++,
                                    (u8*)((play->pictoPhotoI8 != NULL) ? play->pictoPhotoI8 : gWorkBuffer) +
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
            Interface_UpdateButtonsPart1(play);
        }
    }

    // Update hud visibility
    switch (gSaveContext.nextHudVisibility) {
        case HUD_VISIBILITY_NONE:
        case HUD_VISIBILITY_NONE_ALT:
        case HUD_VISIBILITY_B:
            dimmingAlpha = 255 - (gSaveContext.hudVisibilityTimer * 32);
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
            dimmingAlpha = 255 - (gSaveContext.hudVisibilityTimer * 32);
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
            dimmingAlpha = 255 - (gSaveContext.hudVisibilityTimer * 32);
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
        gSaveContext.save.saveInfo.playerData.health += 4;

        if ((gSaveContext.save.saveInfo.playerData.health & 0xF) < 4) {
            Audio_PlaySfx(NA_SE_SY_HP_RECOVER);
        }

        if (((void)0, gSaveContext.save.saveInfo.playerData.health) >=
            ((void)0, gSaveContext.save.saveInfo.playerData.healthCapacity)) {
            gSaveContext.save.saveInfo.playerData.health = gSaveContext.save.saveInfo.playerData.healthCapacity;
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
            if (gSaveContext.save.saveInfo.playerData.rupees < CUR_CAPACITY(UPG_WALLET)) {
                gSaveContext.rupeeAccumulator--;
                gSaveContext.save.saveInfo.playerData.rupees++;
                Audio_PlaySfx(NA_SE_SY_RUPY_COUNT);
            } else {
                // Max rupees
                gSaveContext.save.saveInfo.playerData.rupees = CUR_CAPACITY(UPG_WALLET);
                gSaveContext.rupeeAccumulator = 0;
            }
        } else if (gSaveContext.save.saveInfo.playerData.rupees != 0) {
            if (gSaveContext.rupeeAccumulator <= -50) {
                gSaveContext.rupeeAccumulator += 10;
                gSaveContext.save.saveInfo.playerData.rupees -= 10;
                if (gSaveContext.save.saveInfo.playerData.rupees < 0) {
                    gSaveContext.save.saveInfo.playerData.rupees = 0;
                }
                Audio_PlaySfx(NA_SE_SY_RUPY_COUNT);
            } else {
                gSaveContext.rupeeAccumulator++;
                gSaveContext.save.saveInfo.playerData.rupees--;
                Audio_PlaySfx(NA_SE_SY_RUPY_COUNT);
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
                        Audio_PlaySfx(NA_SE_SY_START_SHOT);
                    } else {
                        Audio_PlaySfx(NA_SE_SY_WARNING_COUNT_E);
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

                if ((msgCtx->msgMode != MSGMODE_NONE) && (msgCtx->textboxYTarget == 38)) {
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
            if (!gSaveContext.save.saveInfo.playerData.isMagicAcquired) {
                gSaveContext.save.saveInfo.playerData.isMagicAcquired = true;
            }
            gSaveContext.save.saveInfo.playerData.isDoubleMagicAcquired = true;
            gSaveContext.save.saveInfo.playerData.magic = MAGIC_DOUBLE_METER;
            gSaveContext.save.saveInfo.playerData.magicLevel = 0;
            R_MAGIC_DBG_SET_UPGRADE = MAGIC_DBG_SET_UPGRADE_NO_ACTION;
        } else if (R_MAGIC_DBG_SET_UPGRADE == MAGIC_DBG_SET_UPGRADE_NORMAL_METER) {
            // Upgrade to normal magic
            if (!gSaveContext.save.saveInfo.playerData.isMagicAcquired) {
                gSaveContext.save.saveInfo.playerData.isMagicAcquired = true;
            }
            gSaveContext.save.saveInfo.playerData.isDoubleMagicAcquired = false;
            gSaveContext.save.saveInfo.playerData.magic = MAGIC_NORMAL_METER;
            gSaveContext.save.saveInfo.playerData.magicLevel = 0;
            R_MAGIC_DBG_SET_UPGRADE = MAGIC_DBG_SET_UPGRADE_NO_ACTION;
        }

        if ((gSaveContext.save.saveInfo.playerData.isMagicAcquired) &&
            (gSaveContext.save.saveInfo.playerData.magicLevel == 0)) {
            // Prepare to step `magicCapacity` to full capacity
            gSaveContext.save.saveInfo.playerData.magicLevel =
                gSaveContext.save.saveInfo.playerData.isDoubleMagicAcquired + 1;
            gSaveContext.magicFillTarget = gSaveContext.save.saveInfo.playerData.magic;
            gSaveContext.save.saveInfo.playerData.magic = 0;
            gSaveContext.magicState = MAGIC_STATE_STEP_CAPACITY;
            BUTTON_ITEM_EQUIP(PLAYER_FORM_DEKU, EQUIP_SLOT_B) = ITEM_DEKU_NUT;
        }

        Magic_Update(play);
        Magic_UpdateAddRequest();
    }

    // Update environmental hazard timer
    if (gSaveContext.timerStates[TIMER_ID_ENV_HAZARD] == TIMER_STATE_OFF) {
        if ((sEnvHazard == PLAYER_ENV_HAZARD_HOTROOM) || (sEnvHazard == PLAYER_ENV_HAZARD_UNDERWATER_FREE)) {
            if (CUR_FORM != PLAYER_FORM_ZORA) {
                if (play->gameOverCtx.state == GAMEOVER_INACTIVE) {
                    if ((gSaveContext.save.saveInfo.playerData.health >> 1) != 0) {
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
        if ((msgCtx->ocarinaAction != OCARINA_ACTION_CHECK_NOTIME_DONE) &&
            (gSaveContext.sunsSongState == SUNSSONG_START)) {
            play->msgCtx.ocarinaMode = OCARINA_MODE_END;
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
                    play->msgCtx.ocarinaMode = OCARINA_MODE_END;
                }
            } else {
                // Daytime
                if (gSaveContext.save.time > CLOCK_TIME(18, 0)) {
                    // Nighttime has been reached. End suns song effect
                    gSaveContext.sunsSongState = SUNSSONG_INACTIVE;
                    R_TIME_SPEED = sPrevTimeSpeed;
                    play->msgCtx.ocarinaMode = OCARINA_MODE_END;
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
    PadMgr_UnsetInputRetraceCallback(Interface_PostmanTimerCallback, NULL);
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
    interfaceCtx->parameterSegment = THA_AllocTailAlign16(&play->state.tha, parameterStaticSize);
    DmaMgr_SendRequest0(interfaceCtx->parameterSegment, SEGMENT_ROM_START(parameter_static), parameterStaticSize);

    interfaceCtx->doActionSegment = THA_AllocTailAlign16(&play->state.tha, 0xC90);
    DmaMgr_SendRequest0(interfaceCtx->doActionSegment, SEGMENT_ROM_START(do_action_static), 0x300);
    DmaMgr_SendRequest0(interfaceCtx->doActionSegment + 0x300, SEGMENT_ROM_START(do_action_static) + 0x480, 0x180);

    Interface_NewDay(play, CURRENT_DAY);

    interfaceCtx->iconItemSegment = THA_AllocTailAlign16(&play->state.tha, 0x4000);

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
