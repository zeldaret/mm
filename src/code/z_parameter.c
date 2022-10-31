#include "global.h"
#include "z64view.h"
#include "interface/parameter_static/parameter_static.h"
#include "interface/do_action_static/do_action_static.h"
#include "misc/story_static/story_static.h"

#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"
#include "overlays/actors/ovl_En_Mm3/z_en_mm3.h"

typedef struct {
    /* 0x00 */ u8 scene;
    /* 0x01 */ u8 flags1;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
} RestrictionFlags;

Input sPostmanTimerInput[4];

RestrictionFlags sRestrictionFlags[] = {
    { SCENE_20SICHITAI2, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_1, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_2, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_3, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_4, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_5, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_6, 0x00, 0x00, 0x00 },
    { SCENE_KAKUSIANA, 0x00, 0x00, 0x00 },
    { SCENE_SPOT00, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_9, 0x00, 0x00, 0x00 },
    { SCENE_WITCH_SHOP, 0x10, 0x30, 0xC1 },
    { SCENE_LAST_BS, 0x00, 0x3F, 0x00 },
    { SCENE_HAKASHITA, 0x00, 0x00, 0x00 },
    { SCENE_AYASHIISHOP, 0x10, 0x30, 0xC1 },
    { SCENE_UNSET_E, 0x00, 0x00, 0x00 },
    { SCENE_UNSET_F, 0x00, 0x00, 0x00 },
    { SCENE_OMOYA, 0x00, 0x33, 0x00 },
    { SCENE_BOWLING, 0x10, 0x30, 0xC1 },
    { SCENE_SONCHONOIE, 0x10, 0x30, 0xC1 },
    { SCENE_IKANA, 0x00, 0x00, 0x00 },
    { SCENE_KAIZOKU, 0x00, 0x00, 0x00 },
    { SCENE_MILK_BAR, 0x10, 0x30, 0xC1 },
    { SCENE_INISIE_N, 0x00, 0x00, 0x00 },
    { SCENE_TAKARAYA, 0x10, 0x30, 0xC1 },
    { SCENE_INISIE_R, 0x00, 0x00, 0x00 },
    { SCENE_OKUJOU, 0x00, 0x3F, 0xF0 },
    { SCENE_OPENINGDAN, 0x00, 0x00, 0x00 },
    { SCENE_MITURIN, 0x00, 0x00, 0x00 },
    { SCENE_13HUBUKINOMITI, 0x00, 0x00, 0x00 },
    { SCENE_CASTLE, 0x00, 0x00, 0x00 },
    { SCENE_DEKUTES, 0x10, 0x30, 0x01 },
    { SCENE_MITURIN_BS, 0x00, 0x00, 0x00 },
    { SCENE_SYATEKI_MIZU, 0x10, 0x30, 0xC1 },
    { SCENE_HAKUGIN, 0x00, 0x00, 0x00 },
    { SCENE_ROMANYMAE, 0x00, 0x00, 0x00 },
    { SCENE_PIRATE, 0x00, 0x00, 0x00 },
    { SCENE_SYATEKI_MORI, 0x10, 0x30, 0xC1 },
    { SCENE_SINKAI, 0x00, 0x00, 0x00 },
    { SCENE_YOUSEI_IZUMI, 0x00, 0x00, 0x00 },
    { SCENE_KINSTA1, 0x00, 0x30, 0x00 },
    { SCENE_KINDAN2, 0x00, 0x30, 0x00 },
    { SCENE_TENMON_DAI, 0x00, 0x03, 0xC0 },
    { SCENE_LAST_DEKU, 0x00, 0x3F, 0x00 },
    { SCENE_22DEKUCITY, 0x00, 0x00, 0x00 },
    { SCENE_KAJIYA, 0x00, 0x30, 0xC0 },
    { SCENE_00KEIKOKU, 0x00, 0x00, 0x00 },
    { SCENE_POSTHOUSE, 0x00, 0x30, 0xC1 },
    { SCENE_LABO, 0x00, 0x30, 0xC1 },
    { SCENE_DANPEI2TEST, 0x00, 0x30, 0x00 },
    { SCENE_UNSET_31, 0x00, 0x00, 0x00 },
    { SCENE_16GORON_HOUSE, 0x00, 0x00, 0x00 },
    { SCENE_33ZORACITY, 0x00, 0x00, 0xC0 },
    { SCENE_8ITEMSHOP, 0x00, 0x30, 0xC1 },
    { SCENE_F01, 0x00, 0x00, 0x00 },
    { SCENE_INISIE_BS, 0x00, 0x00, 0x00 },
    { SCENE_30GYOSON, 0x00, 0x00, 0x00 },
    { SCENE_31MISAKI, 0x00, 0x00, 0x00 },
    { SCENE_TAKARAKUJI, 0x00, 0x30, 0xC1 },
    { SCENE_UNSET_3A, 0x00, 0x00, 0x00 },
    { SCENE_TORIDE, 0x00, 0x00, 0x00 },
    { SCENE_FISHERMAN, 0x00, 0x30, 0xC1 },
    { SCENE_GORONSHOP, 0x10, 0x30, 0xC1 },
    { SCENE_DEKU_KING, 0x00, 0x30, 0xC0 },
    { SCENE_LAST_GORON, 0x00, 0x3F, 0x00 },
    { SCENE_24KEMONOMITI, 0x00, 0x00, 0x00 },
    { SCENE_F01_B, 0x00, 0x30, 0x00 },
    { SCENE_F01C, 0x00, 0x30, 0x00 },
    { SCENE_BOTI, 0x00, 0x00, 0x00 },
    { SCENE_HAKUGIN_BS, 0x00, 0x00, 0x00 },
    { SCENE_20SICHITAI, 0x00, 0x00, 0x00 },
    { SCENE_21MITURINMAE, 0x00, 0x00, 0x00 },
    { SCENE_LAST_ZORA, 0x00, 0x3F, 0x00 },
    { SCENE_11GORONNOSATO2, 0x00, 0x00, 0x00 },
    { SCENE_SEA, 0x00, 0x00, 0x00 },
    { SCENE_35TAKI, 0x00, 0x00, 0x00 },
    { SCENE_REDEAD, 0x00, 0x00, 0x00 },
    { SCENE_BANDROOM, 0x00, 0x30, 0xC0 },
    { SCENE_11GORONNOSATO, 0x00, 0x00, 0x00 },
    { SCENE_GORON_HAKA, 0x00, 0x00, 0x00 },
    { SCENE_SECOM, 0x00, 0x3C, 0xC0 },
    { SCENE_10YUKIYAMANOMURA, 0x00, 0x00, 0x00 },
    { SCENE_TOUGITES, 0x00, 0x3F, 0xF0 },
    { SCENE_DANPEI, 0x00, 0x30, 0x00 },
    { SCENE_IKANAMAE, 0x00, 0x00, 0x00 },
    { SCENE_DOUJOU, 0x00, 0x30, 0xC1 },
    { SCENE_MUSICHOUSE, 0x00, 0x30, 0xC0 },
    { SCENE_IKNINSIDE, 0x00, 0x3F, 0xC0 },
    { SCENE_MAP_SHOP, 0x10, 0x30, 0xC1 },
    { SCENE_F40, 0x00, 0x00, 0x00 },
    { SCENE_F41, 0x00, 0x00, 0x00 },
    { SCENE_10YUKIYAMANOMURA2, 0x00, 0x00, 0x00 },
    { SCENE_14YUKIDAMANOMITI, 0x00, 0x00, 0x00 },
    { SCENE_12HAKUGINMAE, 0x00, 0x00, 0x00 },
    { SCENE_17SETUGEN, 0x00, 0x00, 0x00 },
    { SCENE_17SETUGEN2, 0x00, 0x00, 0x00 },
    { SCENE_SEA_BS, 0x00, 0x00, 0x00 },
    { SCENE_RANDOM, 0x00, 0x00, 0x00 },
    { SCENE_YADOYA, 0x10, 0x30, 0xC1 },
    { SCENE_KONPEKI_ENT, 0x00, 0x00, 0x00 },
    { SCENE_INSIDETOWER, 0x00, 0xFF, 0xC0 },
    { SCENE_26SARUNOMORI, 0x00, 0x30, 0x00 },
    { SCENE_LOST_WOODS, 0x00, 0x00, 0x00 },
    { SCENE_LAST_LINK, 0x00, 0x3F, 0x00 },
    { SCENE_SOUGEN, 0x00, 0x3F, 0x00 },
    { SCENE_BOMYA, 0x10, 0x30, 0xC1 },
    { SCENE_KYOJINNOMA, 0x00, 0x00, 0x00 },
    { SCENE_KOEPONARACE, 0x00, 0x30, 0x00 },
    { SCENE_GORONRACE, 0x00, 0x00, 0x00 },
    { SCENE_TOWN, 0x00, 0x00, 0x00 },
    { SCENE_ICHIBA, 0x00, 0x00, 0x00 },
    { SCENE_BACKTOWN, 0x00, 0x00, 0x00 },
    { SCENE_CLOCKTOWER, 0x00, 0x00, 0x00 },
    { SCENE_ALLEY, 0x00, 0x00, 0x00 },
};

s16 D_801BF884 = 0;     // pictoBox related
s16 D_801BF888 = false; // pictoBox related

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

s16 sEnvTimerType = PLAYER_ENV_TIMER_NONE;
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

Gfx D_801BF988[] = {
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010CB80.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010CD98.s")

Gfx* func_8010CFBC(Gfx* displayListHead, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                   s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy, s16 r, s16 g, s16 b, s16 a);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010CFBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010D2D4.s")

Gfx* func_8010D480(Gfx* displayListHead, void* texture, s16 textureWidth, s16 textureHeight, s16 rectLeft, s16 rectTop,
                   s16 rectWidth, s16 rectHeight, u16 dsdx, u16 dtdy, s16 r, s16 g, s16 b, s16 a, s32 argE, s32 argF);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010D480.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010D7D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010D9F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010DC58.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010DE38.s")

s16 D_801BFA04[] = {
    -14, -14, -24, -8, -12, -12, -7, -8, -7, -8, -12, 0,
};
s16 D_801BFA1C[] = {
    0x1C, 0x1C, 0x30, 0x10, 0x18, 0x18, 0x10, 0x10, 0x10, 0x10, 0x18, 0,
};
s16 D_801BFA34[] = {
    14, 14, 8, 24, -82, -82, 58, 59, 58, 59, 32, 0,
};
s16 D_801BFA4C[] = {
    0x1C, 0x1C, 0x10, 0x10, 0x18, 0x18, 0xB, 0xB, 0xB, 0xB, 0x20, 0,
};
s16 D_801BFA64[] = {
    -61, -45, 29, 104, -117, -42, 32, 55,
};
s16 D_801BFA74[] = {
    1, -70, -99, -70, 71, 101, 72, 1,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010E028.s")

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
        if (gSaveContext.eventInf[1] & 1) {
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8010EE74.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80111CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_801129E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80112AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80112AFC.s")

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
        BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = item;
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
        if (!(gSaveContext.save.weekEventReg[12] & 0x80)) {
            gSaveContext.save.weekEventReg[12] |= 0x80;
            return ITEM_NONE;
        }
        return item;

    } else if (item == ITEM_MAGIC_LARGE) {
        Magic_Add(play, MAGIC_NORMAL_METER);
        if (!(gSaveContext.save.weekEventReg[12] & 0x80)) {
            gSaveContext.save.weekEventReg[12] |= 0x80;
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
        if (!(gSaveContext.save.weekEventReg[12] & 0x80)) {
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
            BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_SWORD_DEITY;
        } else if (BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) == ITEM_SWORD_DEITY) {
            if (GET_CUR_EQUIP_VALUE(EQUIP_TYPE_SWORD) == EQUIP_VALUE_SWORD_NONE) {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) = ITEM_NONE;
            } else {
                BUTTON_ITEM_EQUIP(CUR_FORM, EQUIP_SLOT_B) =
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
                if (gSaveContext.save.weekEventReg[14] & 8) {
                    // Drank Chateau Romani
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
                if (gSaveContext.save.weekEventReg[14] & 8) {
                    // Drank Chateau Romani
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
                if (gSaveContext.save.weekEventReg[14] & 8) {
                    // Drank Chateau Romani
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

    if (gSaveContext.save.weekEventReg[14] & 8) {
        // Drank Chateau Romani
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
            if (!(gSaveContext.save.weekEventReg[14] & 8)) {
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
            if (!(gSaveContext.save.weekEventReg[14] & 8)) {
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
                    ((Player_GetEnvTimerType(play) >= PLAYER_ENV_TIMER_UNDERWATER_FLOOR) &&
                     (Player_GetEnvTimerType(play) <= PLAYER_ENV_TIMER_UNDERWATER_FREE)) ||
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
                    if (!(gSaveContext.save.weekEventReg[14] & 8)) {
                        gSaveContext.save.playerData.magic--;
                    }
                    interfaceCtx->magicConsumptionTimer = 80;
                }
            }
            if (!(gSaveContext.save.weekEventReg[14] & 8)) {
                Magic_FlashMeterBorder();
            }
            break;

        case MAGIC_STATE_CONSUME_GORON_ZORA_SETUP:
            if (!(gSaveContext.save.weekEventReg[14] & 8)) {
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
                        if (!(gSaveContext.save.weekEventReg[14] & 8)) {
                            gSaveContext.save.playerData.magic--;
                        }
                        if (gSaveContext.save.playerData.magic <= 0) {
                            gSaveContext.save.playerData.magic = 0;
                        }
                        interfaceCtx->magicConsumptionTimer = 10;
                    }
                }
            }
            if (!(gSaveContext.save.weekEventReg[14] & 8)) {
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
                        if (!(gSaveContext.save.weekEventReg[14] & 8)) {
                            gSaveContext.save.playerData.magic--;
                        }
                        if (gSaveContext.save.playerData.magic <= 0) {
                            gSaveContext.save.playerData.magic = 0;
                        }
                        interfaceCtx->magicConsumptionTimer = R_MAGIC_CONSUME_TIMER_GIANTS_MASK;
                    }
                }
            }
            if (!(gSaveContext.save.weekEventReg[14] & 8)) {
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

        OVERLAY_DISP = func_8010CFBC(OVERLAY_DISP, gMagicMeterEndTex, 8, 16, 18, magicBarY, 8, 16, 1 << 10, 1 << 10,
                                     sMagicMeterOutlinePrimRed, sMagicMeterOutlinePrimGreen, sMagicMeterOutlinePrimBlue,
                                     interfaceCtx->magicAlpha);
        OVERLAY_DISP =
            func_8010CFBC(OVERLAY_DISP, gMagicMeterMidTex, 24, 16, 26, magicBarY, ((void)0, gSaveContext.magicCapacity),
                          16, 1 << 10, 1 << 10, sMagicMeterOutlinePrimRed, sMagicMeterOutlinePrimGreen,
                          sMagicMeterOutlinePrimBlue, interfaceCtx->magicAlpha);
        OVERLAY_DISP =
            func_8010D480(OVERLAY_DISP, gMagicMeterEndTex, 8, 16, ((void)0, gSaveContext.magicCapacity) + 26, magicBarY,
                          8, 16, 1 << 10, 1 << 10, sMagicMeterOutlinePrimRed, sMagicMeterOutlinePrimGreen,
                          sMagicMeterOutlinePrimBlue, interfaceCtx->magicAlpha, 3, 0x100);

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
            if (gSaveContext.save.weekEventReg[14] & 8) {
                // Blue magic (drank Chateau Romani)
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
            if (gSaveContext.save.weekEventReg[14] & 8) {
                // Blue magic (drank Chateau Romani)
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80117100.s")

s16 D_801BFAFC[] = { 30, 24, 24, 24 };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80117A20.s")

s16 D_801BFB04[] = { 0xA2, 0xE4, 0xFA, 0x110 };
s16 D_801BFB0C[] = { 0x23, 0x23, 0x33, 0x23 };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80117BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80118084.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80118890.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80118BA4.s")

extern TexturePtr D_08095AC0;            // gMagicArrowEquipEffectTex
s16 D_801BFB14[] = { 255, 100, 255, 0 }; // magicArrowEffectsR
s16 D_801BFB1C[] = { 0, 100, 255, 0 };   // magicArrowEffectsG
s16 D_801BFB24[] = { 0, 255, 100, 0 };   // magicArrowEffectsB

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80119030.s")

s16 D_801BFB2C = 255;
s16 D_801BFB30 = 0;
s16 D_801BFB34 = 0;
u16 D_801BFB38[] = {
    CLOCK_TIME(0, 0),  CLOCK_TIME(1, 0),  CLOCK_TIME(2, 0),  CLOCK_TIME(3, 0),  CLOCK_TIME(4, 0),
    CLOCK_TIME(5, 0),  CLOCK_TIME(6, 0),  CLOCK_TIME(7, 0),  CLOCK_TIME(8, 0),  CLOCK_TIME(9, 0),
    CLOCK_TIME(10, 0), CLOCK_TIME(11, 0), CLOCK_TIME(12, 0), CLOCK_TIME(13, 0), CLOCK_TIME(14, 0),
    CLOCK_TIME(15, 0), CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), CLOCK_TIME(19, 0),
    CLOCK_TIME(20, 0), CLOCK_TIME(21, 0), CLOCK_TIME(22, 0), CLOCK_TIME(23, 0), CLOCK_TIME(24, 0) - 1,
};
TexturePtr D_801BFB6C[] = {
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
TexturePtr D_801BFC14[] = {
    gFinalHoursClockDigit0Tex, gFinalHoursClockDigit1Tex, gFinalHoursClockDigit2Tex, gFinalHoursClockDigit3Tex,
    gFinalHoursClockDigit4Tex, gFinalHoursClockDigit5Tex, gFinalHoursClockDigit6Tex, gFinalHoursClockDigit7Tex,
    gFinalHoursClockDigit8Tex, gFinalHoursClockDigit9Tex, gFinalHoursClockColonTex,
};
s16 D_801BFC40[] = {
    127, 136, 144, 151, 160, 168, 175, 184,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80119610.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011B4E0.s")

u16 D_801BFC50[] = {
    0xC000, 0xE000, 0x0000, 0x2000, 0xA000, 0x8000, 0x6000, 0x4000,
};
s16 D_801BFC60[][3] = {
    255, 255, 255, 255, 165, 55,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011B5C0.s")

s16 D_801BFC6C[] = {
    78, 54, 29, 5, -18, -42, -67, -85,
};
s16 D_801BFC7C[] = {
    180, 180, 180, 180, -180, -180, -180, -180,
};
s16 D_801BFC8C[2][3] = {
    { 255, 255, 255 },
    { 255, 165, 55 },
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011B9E0.s")

s16 D_801BFC98[] = {
    78, 54, 29, 5, -18, -42, -67, -85,
};
u16 D_801BFCA8[] = {
    0xC000, 0xE000, 0x0000, 0x2000, 0xA000, 0x8000, 0x6000, 0x4000,
};
s16 D_801BFCB8[2][3] = {
    { 255, 255, 255 },
    { 255, 165, 55 },
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011BF70.s")

TexturePtr D_801BFCC4[] = {
    gMinigameLetterPTex, gMinigameLetterETex, gMinigameLetterRTex, gMinigameLetterFTex,
    gMinigameLetterETex, gMinigameLetterCTex, gMinigameLetterTTex, gMinigameExclamationTex,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011C4C4.s")

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
    OSTime timerOsTime;
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
                        timerOsTime = gSaveContext.postmanTimerStopOsTime;
                        gSaveContext.timerCurTimes[TIMER_ID_POSTMAN] =
                            OSTIME_TO_TIMER(timerOsTime - ((void)0, gSaveContext.timerStartOsTimes[TIMER_ID_POSTMAN]) -
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
                    if (interfaceCtx->unk_280 != 0) {

                        // Set the timer position
                        gSaveContext.timerX[sTimerId] = 26;

                        if (interfaceCtx->magicAlpha != 255) {
                            gSaveContext.timerY[sTimerId] = 22;
                        } else if (gSaveContext.save.playerData.healthCapacity > 0xA0) {
                            gSaveContext.timerY[sTimerId] = 54;
                        } else {
                            gSaveContext.timerY[sTimerId] = 46;
                        }

                        if ((interfaceCtx->unk_280 == 8) || (interfaceCtx->unk_280 == 30)) {
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

                case TIMER_STATE_ENV_START:
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

                    if ((gSaveContext.minigameState == 1) &&
                        (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                        if (gSaveContext.timerStopTimes[sTimerId] >= SECONDS_TO_TIMER(120)) {
                            gSaveContext.timerStopTimes[sTimerId] = SECONDS_TO_TIMER(120);
                            gSaveContext.timerCurTimes[sTimerId] = SECONDS_TO_TIMER(120);
                        }
                    } else if ((gSaveContext.eventInf[3] & 0x10) && (play->sceneId == SCENE_DEKUTES) &&
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

                if ((gSaveContext.minigameState == 1) && (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                    if (osTime >= SECONDS_TO_TIMER(120)) {
                        osTime = SECONDS_TO_TIMER(120);
                    }
                } else if ((gSaveContext.eventInf[3] & 0x10) && (play->sceneId == SCENE_DEKUTES) &&
                           (osTime >= SECONDS_TO_TIMER(120))) {
                    osTime = SECONDS_TO_TIMER(120);
                }

                // Update the time remaining with the total amount of time since the start of the timer,
                gSaveContext.timerCurTimes[sTimerId] = osTime;

                Interface_GetTimerDigits(osTime, sTimerDigits);

                // Use seconds to determine when to beep
                if ((gSaveContext.minigameState == 1) && (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                    if ((gSaveContext.timerCurTimes[sTimerId] > SECONDS_TO_TIMER(110)) &&
                        (sTimerBeepSfxSeconds != sTimerDigits[4])) {
                        play_sound(NA_SE_SY_WARNING_COUNT_E);
                        sTimerBeepSfxSeconds = sTimerDigits[4];
                    }
                } else if ((gSaveContext.eventInf[3] & 0x10) && (play->sceneId == SCENE_DEKUTES)) {
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
            OVERLAY_DISP =
                func_8010CD98(OVERLAY_DISP, gTimerClockIconTex, 0x10, 0x10, ((void)0, gSaveContext.timerX[sTimerId]),
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
                    } else if ((gSaveContext.minigameState == 1) &&
                               (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 0))) {
                        if (gSaveContext.timerCurTimes[sTimerId] >= SECONDS_TO_TIMER(110)) {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 50, 0, 255);
                        } else {
                            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 255, 255, 255, 255);
                        }
                    } else if ((gSaveContext.eventInf[3] & 0x10) && (play->sceneId == SCENE_DEKUTES)) {
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
                            OVERLAY_DISP = func_8010D7D0(
                                OVERLAY_DISP, ((u8*)gCounterDigit0Tex + (8 * 16 * sTimerDigits[j + 3])), 8, 0x10,
                                ((void)0, gSaveContext.timerX[sTimerId]) + sTimerDigitsOffsetX[j],
                                ((void)0, gSaveContext.timerY[sTimerId]), sTimerDigitsWidth[j], 0xFA, 0x370, 0x370);
                        }
                    } else {
                        // draw sTimerDigits[3] (10s of seconds) to sTimerDigits[7] (10s of milliseconds)
                        for (j = 0; j < 5; j++) {
                            OVERLAY_DISP = func_8010D7D0(
                                OVERLAY_DISP, ((u8*)gCounterDigit0Tex + (8 * 16 * sTimerDigits[j + 3])), 8, 0x10,
                                ((void)0, gSaveContext.timerX[sTimerId]) + sTimerDigitsOffsetX[j],
                                ((void)0, gSaveContext.timerY[sTimerId]), sTimerDigitsWidth[j], 0xFA, 0x370, 0x370);
                        }
                    }
                } else {
                    // draw sTimerDigits[3] (6s of minutes) to sTimerDigits[7] (10s of milliseconds)
                    for (j = 0; j < 8; j++) {
                        OVERLAY_DISP = func_8010D7D0(
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011E730.s")

// rupeeDigitsFirst
s16 D_801BFD1C[] = { 1, 0, 0, 0 };
// rupeeDigitsCount
s16 D_801BFD24[] = { 2, 3, 3, 0 };
// rupeeIconPrimColor
Color_RGB16 D_801BFD2C[] = {
    { 200, 255, 100 },
    { 170, 170, 255 },
    { 255, 105, 105 },
};
// rupeeIconEnvColor
Color_RGB16 D_801BFD40[] = {
    { 0, 80, 0 },
    { 10, 10, 80 },
    { 40, 10, 0 },
};
// minigameCountdownTexs
TexturePtr D_801BFD54[] = {
    gMinigameCountdown3Tex,
    gMinigameCountdown2Tex,
    gMinigameCountdown1Tex,
    gMinigameCountdownGoTex,
};
// minigameCountdownTexHeights
s16 D_801BFD64[] = { 24, 24, 24, 40 };
// minigameCountdownPrimColor
Color_RGB16 D_801BFD6C[] = {
    { 100, 255, 100 },
    { 255, 255, 60 },
    { 255, 100, 0 },
    { 120, 170, 255 },
};
// grandma's story pictures
TexturePtr D_801BFD84[] = {
    gStoryMaskFestivalTex,
    gStoryGiantsLeavingTex,
};
// grandma's story TLUT
TexturePtr D_801BFD8C[] = {
    gStoryMaskFestivalTLUT,
    gStoryGiantsLeavingTLUT,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_8011F0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80120F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80121064.s")

u8 D_801BFD94 = 0;
s16 D_801BFD98 = 0;
s16 D_801BFD9C = 0;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_801210E0.s")

void Interface_Destroy(PlayState* play) {
    Map_Destroy(play);
    func_80174F9C(Interface_PostmanTimerCallback, NULL);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_parameter/func_80121FC4.s")
