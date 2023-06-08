#include "prevent_bss_reordering.h"
#include "global.h"
#include "z64environment.h"
#include "z64rumble.h"
#include "z64save.h"
#include "z64skybox.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

void Environment_UpdateSaveFlags(PlayState* play);
void Environment_UpdateRain(PlayState* play);
void Environment_UpdateTimeBasedSequence(PlayState* play);
u8 func_800FE5D0(struct PlayState* play);
void Environment_JumpForwardInTime(void);

typedef enum {
    /* 0x00 */ LIGHTNING_BOLT_START,
    /* 0x01 */ LIGHTNING_BOLT_WAIT,
    /* 0x02 */ LIGHTNING_BOLT_DRAW,
    /* 0xFF */ LIGHTNING_BOLT_INACTIVE = 0xFF
} LightningBoltState;

// Bss to import
u8 D_801F4E30;
u8 D_801F4E31;
u8 gCustomLensFlare1On;
Vec3f gCustomLensFlare1Pos;
f32 D_801F4E44;
f32 D_801F4E48;
s16 D_801F4E4C;
u8 gCustomLensFlare2On;
Vec3f gCustomLensFlare2Pos;
f32 D_801F4E5C;
f32 D_801F4E60;
s16 D_801F4E64;
LightningStrike gLightningStrike;
f32 D_801F4E74;
u16 D_801F4E78;
u16 gSkyboxNumStars;
LightningBolt sLightningBolts[3];
LightNode* sNGameOverLightNode;
LightInfo sNGameOverLightInfo;
LightNode* sSGameOverLightNode;
LightInfo sSGameOverLightInfo;
f32 sSunEnvAlpha;
f32 sSunColor;
f32 sSunScale;
f32 sSunPrimAlpha;
s32 sSunDepthTestX;
s32 sSunDepthTestY;
f32 D_801F4F28;
s16 sLightningFlashAlpha;
u16 sSandstormScroll;
u8 D_801F4F30;
u8 D_801F4F31;
u8 sEnvIsTimeStopped;
u8 D_801F4F33;
u8 sGameOverLightsIntensity;
Gfx* sSkyboxStarsDList;

void Environment_GraphCallback(GraphicsContext* gfxCtx, PlayState* play) {
    sSunScreenDepth = SysCfb_GetZBufferPixel(sSunDepthTestX, sSunDepthTestY);
    Lights_GlowCheck(play);
}

typedef struct {
    /* 0x0 */ s32 mantissa;
    /* 0x4 */ s32 exponent;
} ZBufValConversionEntry; // size = 0x8

extern ZBufValConversionEntry sZBufValConversionTable[8];

#define ZBUFVAL_EXPONENT(v) (((v) >> 15) & 7)
#define ZBUFVAL_MANTISSA(v) (((v) >> 4) & 0x7FF)

/**
 * Convert an 18-bits Z buffer value to a fixed point 15.3 value
 *
 * zBufferVal is 18 bits:
 *   3: Exponent of z value
 *  11: Mantissa of z value
 *   4: dz value (unused)
 */
s32 Environment_ZBufValToFixedPoint(s32 zBufferVal) {
    // base[exp] + mantissa << shift[exp]
    s32 ret = (ZBUFVAL_MANTISSA(zBufferVal) << sZBufValConversionTable[ZBUFVAL_EXPONENT(zBufferVal)].mantissa) +
              sZBufValConversionTable[ZBUFVAL_EXPONENT(zBufferVal)].exponent;

    return ret;
}

extern u8 gSkyboxIsChanging;
extern u8 D_801BDBA8;

#ifdef NON_EQUIVALENT
void Environment_Init(PlayState* play2, EnvironmentContext* envCtx, s32 arg2) {
    PlayState* play = play2;
    f32 temp_ft4;
    u8 var_a0;
    u8 temp_t6;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_t9;
    u8 var_v0;
    s16 i;

    CREG(1) = 0;

    gSaveContext.sunsSongState = SUNSSONG_INACTIVE;

    gSaveContext.skyboxTime = ((void)0, gSaveContext.save.time);

    Environment_JumpForwardInTime();

    if ((((void)0, gSaveContext.save.time) >= CLOCK_TIME(18, 0)) ||
        (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0))) {
        gSaveContext.save.isNight = 1;
    } else {
        gSaveContext.save.isNight = 0;
    }

    play->state.gfxCtx->callback = Environment_GraphCallback;
    play->state.gfxCtx->callbackArg = play;

    Lights_DirectionalSetInfo(&envCtx->dirLight1, 80, 80, 80, 80, 80, 80);
    LightContext_InsertLight(play, &play->lightCtx, &envCtx->dirLight1);

    Lights_DirectionalSetInfo(&envCtx->dirLight2, 80, 80, 80, 80, 80, 80);
    LightContext_InsertLight(play, &play->lightCtx, &envCtx->dirLight2);

    envCtx->changeSkyboxState = CHANGE_SKYBOX_INACTIVE;
    envCtx->changeSkyboxTimer = 0;
    envCtx->changeLightEnabled = false;
    envCtx->changeLightTimer = 0;
    envCtx->skyboxDmaState = 0;
    envCtx->skybox1Index = 99;
    envCtx->skybox2Index = 99;

    envCtx->glareAlpha = 0.0f;
    envCtx->lensFlareAlphaScale = 0.0f;

    if ((play->sceneId == SCENE_00KEIKOKU) && (gSaveContext.sceneLayer == 8)) {
        gSaveContext.save.day = 1;
    }

    switch (gSaveContext.save.day) {
        default:
        case 0:
        case 1:
            envCtx->lightConfig = 0;
            envCtx->changeLightNextConfig = 0;
            break;

        case 2:
            envCtx->lightConfig = 3;
            envCtx->changeLightNextConfig = 3;
            break;

        case 3:
            envCtx->lightConfig = 4;
            envCtx->changeLightNextConfig = 4;
            break;
    }

    envCtx->lightSetting = 0;
    envCtx->prevLightSetting = 0;
    envCtx->lightBlendOverride = LIGHT_BLEND_OVERRIDE_NONE;
    envCtx->stormRequest = STORM_REQUEST_NONE;
    envCtx->stormState = STORM_STATE_OFF;
    envCtx->lightningState = LIGHTNING_OFF;
    envCtx->timeSeqState = TIMESEQ_DAY_BGM;
    envCtx->fillScreen = 0;
    envCtx->screenFillColor[0] = 0;
    envCtx->screenFillColor[1] = 0;
    envCtx->screenFillColor[2] = 0;
    envCtx->screenFillColor[3] = 0;
    envCtx->customSkyboxFilter = false;
    envCtx->skyboxFilterColor[0] = 0;
    envCtx->skyboxFilterColor[1] = 0;
    envCtx->skyboxFilterColor[2] = 0;
    envCtx->skyboxFilterColor[3] = 0;
    envCtx->sandstormState = SANDSTORM_OFF;
    envCtx->sandstormPrimA = 0;
    envCtx->sandstormEnvA = 0;
    envCtx->lightBlend = 1.0f;

    gLightningStrike.state = LIGHTNING_STRIKE_WAIT;
    gLightningStrike.flashRed = 0;
    gLightningStrike.flashGreen = 0;
    gLightningStrike.flashBlue = 0;

    sLightningFlashAlpha = 0;

    D_801F4F30 = 0xFF;
    D_801F4F31 = 0;
    D_801F4E30 = 0;
    D_801F4F33 = 0;

    gSaveContext.cutsceneTransitionControl = 0;

    envCtx->adjLightSettings.ambientColor[0] = 0;
    envCtx->adjLightSettings.ambientColor[1] = 0;
    envCtx->adjLightSettings.ambientColor[2] = 0;
    envCtx->adjLightSettings.diffuseColor1[0] = 0;
    envCtx->adjLightSettings.diffuseColor1[1] = 0;
    envCtx->adjLightSettings.diffuseColor1[2] = 0;
    envCtx->adjLightSettings.diffuseColor2[0] = 0;
    envCtx->adjLightSettings.diffuseColor2[1] = 0;
    envCtx->adjLightSettings.diffuseColor2[2] = 0;
    envCtx->adjLightSettings.fogColor[0] = 0;
    envCtx->adjLightSettings.fogColor[1] = 0;
    envCtx->adjLightSettings.fogColor[2] = 0;
    envCtx->adjLightSettings.fogNear = 0;
    envCtx->adjLightSettings.zFar = 0;

    envCtx->sunPos.x = -(Math_SinS(((void)0, gSaveContext.save.time) - CLOCK_TIME(12, 0)) * 120.0f) * 25.0f;
    envCtx->sunPos.y = (Math_CosS(((void)0, gSaveContext.save.time) - CLOCK_TIME(12, 0)) * 120.0f) * 25.0f;
    envCtx->sunPos.z = (Math_CosS(((void)0, gSaveContext.save.time) - CLOCK_TIME(12, 0)) * 20.0f) * 25.0f;

    envCtx->windDirection.x = 80;
    envCtx->windDirection.y = 80;
    envCtx->windDirection.z = 80;
    envCtx->windSpeed = 20.0f;

    envCtx->lightBlendEnabled = false;
    envCtx->lightSettingOverride = LIGHT_SETTING_OVERRIDE_NONE;
    envCtx->lightBlendRateOverride = LIGHT_BLENDRATE_OVERRIDE_NONE;

    envCtx->sceneTimeSpeed = 0;
    R_TIME_SPEED = R_TIME_SPEED = 0;
    R_ENV_DISABLE_DBG = false;

    CREG(64) = 0;

    play->envCtx.precipitation[PRECIP_RAIN_MAX] = 0;
    play->envCtx.precipitation[PRECIP_SNOW_CUR] = 0;
    play->envCtx.precipitation[PRECIP_SNOW_MAX] = 0;
    play->envCtx.precipitation[PRECIP_SOS_MAX] = 0;

    D_801F4E31 = envCtx->skyboxConfig;

    var_a0 = 0;
    if (((void)0, gSaveContext.save.day) != 0) {
        var_a0 = (((void)0, gSaveContext.save.day) - 1);
    }

    temp_t8 = var_a0 + (D_801F4E31 * 3);
    var_v0 = temp_t8 & 0xFF;

    envCtx->skyboxConfig = temp_t8;
    envCtx->changeSkyboxNextConfig = var_v0;

    // TODO: Solve `func_800FEAF4` first for the pattern here
    if (D_801F4E31 == 4) {
        var_v0 = 0xE & 0xFF;
        envCtx->skyboxConfig = 0xE;
        envCtx->changeSkyboxNextConfig = var_v0;
    } else if (D_801F4E31 == 5) {
        var_v0 = 0x10U & 0xFF;
        envCtx->skyboxConfig = 0x10;
        envCtx->changeSkyboxNextConfig = var_v0;
    } else if (D_801F4E31 == 6) {
        var_v0 = 0x11U & 0xFF;
        envCtx->skyboxConfig = 0x11;
        envCtx->changeSkyboxNextConfig = var_v0;
    } else if (D_801F4E31 == 7) {
        temp_t6 = var_a0 + 0x12;
        var_v0 = temp_t6 & 0xFF;
        envCtx->skyboxConfig = temp_t6;
        envCtx->changeSkyboxNextConfig = var_v0;
    } else if (D_801F4E31 == 8) {
        temp_t7 = var_a0 + 0x15;
        var_v0 = temp_t7 & 0xFF;
        envCtx->skyboxConfig = var_a0 + 0x15;
        envCtx->changeSkyboxNextConfig = var_v0;
    } else if (D_801F4E31 == 9) {
        var_v0 = 0x18U & 0xFF;
        envCtx->skyboxConfig = 0x18;
        envCtx->changeSkyboxNextConfig = var_v0;
    } else if (D_801F4E31 == 0xA) {
        temp_t9 = var_a0 + 0x19;
        var_v0 = temp_t9 & 0xFF;
        envCtx->skyboxConfig = temp_t9;
        envCtx->changeSkyboxNextConfig = var_v0;
    }

    if (var_a0 >= 3) {
        envCtx->skyboxConfig = 0xD;
        envCtx->changeSkyboxNextConfig = 0xD;
    }

    if (envCtx->changeSkyboxNextConfig >= 0x1C) {
        envCtx->skyboxConfig = 0;
        envCtx->changeSkyboxNextConfig = 0;
    }

    D_801F4E74 = 0.0f;

    if ((play->sceneId == SCENE_IKANA) &&
        ((((void)0, gSaveContext.sceneLayer) == 0) || (((void)0, gSaveContext.sceneLayer) == 1)) &&
        !CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE)) {
        play->skyboxId = SKYBOX_3;
        envCtx->lightConfig = 5;
        envCtx->changeLightNextConfig = 5;
        D_801F4E74 = 1.0f;
    }

    if (gSaveContext.retainWeatherMode || (gSaveContext.respawnFlag != 0)) {
        if (gWeatherMode == WEATHER_MODE_2) {
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE)) {
                play->skyboxId = SKYBOX_3;
                envCtx->lightConfig = 5;
                envCtx->changeLightNextConfig = 5;
                D_801F4E74 = 1.0f;
            } else {
                gWeatherMode = WEATHER_MODE_CLEAR;
            }
        }

        play->envCtx.precipitation[PRECIP_SNOW_CUR] = 0;
        play->envCtx.precipitation[PRECIP_SNOW_MAX] = 0;

        if (gWeatherMode == WEATHER_MODE_1) {
            if ((CURRENT_DAY == 2) && (((void)0, gSaveContext.save.time) >= CLOCK_TIME(7, 0)) &&
                (((void)0, gSaveContext.save.time) < CLOCK_TIME(17, 30))) {
                if (Environment_GetStormState(play) != STORM_STATE_OFF) {
                    play->envCtx.precipitation[PRECIP_RAIN_MAX] = 60;
                }
                play->envCtx.precipitation[PRECIP_RAIN_CUR] = 60;
            } else {
                gWeatherMode = WEATHER_MODE_CLEAR;
                Environment_StopStormNatureAmbience(play);
            }
        } else if (gWeatherMode == WEATHER_MODE_SNOW) {
            play->envCtx.precipitation[PRECIP_SNOW_CUR] = 128;
            play->envCtx.precipitation[PRECIP_SNOW_MAX] = 128;
            Environment_StopStormNatureAmbience(play);
        } else {
            Environment_StopStormNatureAmbience(play);
        }
    } else {
        gWeatherMode = WEATHER_MODE_CLEAR;
        Environment_StopStormNatureAmbience(play);
    }

    gInterruptSongOfStorms = false;
    gLightConfigAfterUnderwater = 0;
    gSkyboxIsChanging = false;
    gSaveContext.retainWeatherMode = false;

    R_ENV_LIGHT1_DIR(0) = 80;
    R_ENV_LIGHT1_DIR(1) = 80;
    R_ENV_LIGHT1_DIR(2) = 80;

    R_ENV_LIGHT2_DIR(0) = -80;
    R_ENV_LIGHT2_DIR(1) = -80;
    R_ENV_LIGHT2_DIR(2) = -80;

    cREG(9) = 10;
    cREG(10) = 0;
    cREG(11) = 0;
    cREG(12) = 0;
    cREG(13) = 0;
    cREG(14) = 0;
    D_801F4DDC = 1; // should be u8, breaks bss

    for (i = 0; i < ARRAY_COUNT(sLightningBolts); i++) {
        sLightningBolts[i].state = LIGHTNING_BOLT_INACTIVE;
    }

    play->roomCtx.unk7A[0] = 0;
    play->roomCtx.unk7A[1] = 0;

    for (i = 0; i < ARRAY_COUNT(play->csCtx.actorCues); i++) {
        play->csCtx.actorCues[i] = NULL;
    }

    gCustomLensFlare1On = false;
    gCustomLensFlare2On = false;
    Rumble_StateReset();

    sEnvSkyboxNumStars = 0;
    gSkyboxNumStars = 0;
    D_801BDBA8 = 0;
    sEnvIsTimeStopped = 0;
    sSunPrimAlpha = 255.0f;

    Environment_UpdateSaveFlags(play);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Init.s")
#endif

u8 Environment_SmoothStepToU8(u8* pvalue, u8 target, u8 scale, u8 step, u8 minStep) {
    s16 stepSize = 0;
    s16 diff = target - *pvalue;

    if (target != *pvalue) {
        stepSize = diff / scale;
        if ((stepSize >= (s16)minStep) || ((s16)-minStep >= stepSize)) {
            if ((s16)step < stepSize) {
                stepSize = step;
            }
            if ((s16)-step > stepSize) {
                stepSize = -step;
            }
            *pvalue += (u8)stepSize;
        } else {
            if (stepSize < (s16)minStep) {
                stepSize = minStep;
                *pvalue += (u8)stepSize;
                if (target < *pvalue) {
                    *pvalue = target;
                }
            }
            if ((s16)-minStep < stepSize) {
                stepSize = -minStep;
                *pvalue += (u8)stepSize;
                if (*pvalue < target) {
                    *pvalue = target;
                }
            }
        }
    }
    return diff;
}

f32 Environment_LerpWeight(u16 max, u16 min, u16 val) {
    f32 diff = max - min;

    if (diff != 0.0f) {
        f32 ret = 1.0f - (max - val) / diff;

        if (!(ret >= 1.0f)) {
            return ret;
        }
    }

    return 1.0f;
}

f32 Environment_LerpWeightAccelDecel(u16 endFrame, u16 startFrame, u16 curFrame, u16 accelDuration, u16 decelDuration) {
    f32 endFrameF;
    f32 startFrameF;
    f32 curFrameF;
    f32 accelDurationF;
    f32 decelDurationF;
    f32 totalFrames;
    f32 temp;
    f32 framesElapsed;
    f32 ret;

    if (curFrame <= startFrame) {
        return 0.0f;
    }

    if (curFrame >= endFrame) {
        return 1.0f;
    }

    endFrameF = (s32)endFrame;
    startFrameF = (s32)startFrame;
    curFrameF = (s32)curFrame;
    totalFrames = endFrameF - startFrameF;
    framesElapsed = curFrameF - startFrameF;
    accelDurationF = (s32)accelDuration;
    decelDurationF = (s32)decelDuration;

    if ((startFrameF >= endFrameF) || (accelDurationF + decelDurationF > totalFrames)) {
        // "The frame relation between end_frame and start_frame is wrong!!!"
        // osSyncPrintf(VT_COL(RED, WHITE) "\nend_frameとstart_frameのフレーム関係がおかしい!!!" VT_RST);
        // osSyncPrintf(VT_COL(RED, WHITE) "\nby get_parcent_forAccelBrake!!!!!!!!!" VT_RST);

        return 0.0f;
    }

    temp = 1.0f / ((totalFrames * 2.0f) - accelDurationF - decelDurationF);

    if (accelDurationF != 0.0f) {
        if (framesElapsed <= accelDurationF) {
            return temp * framesElapsed * framesElapsed / accelDurationF;
        }
        ret = temp * accelDurationF;
    } else {
        ret = 0.0f;
    }

    if (framesElapsed <= totalFrames - decelDurationF) {
        ret += 2.0f * temp * (framesElapsed - accelDurationF);
        return ret;
    }

    ret += 2.0f * temp * (totalFrames - accelDurationF - decelDurationF);

    if (decelDurationF != 0.0f) {
        ret += temp * decelDurationF;
        if (framesElapsed < totalFrames) {
            ret -= temp * (totalFrames - framesElapsed) * (totalFrames - framesElapsed) / decelDurationF;
        }
    }

    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateSkybox.s")

void Environment_EnableUnderwaterLights(PlayState* play, s32 waterLightsIndex) {
    if (waterLightsIndex == 0x1F) {
        waterLightsIndex = 0;
    }

    if (play->envCtx.lightMode == LIGHT_MODE_TIME) {
        if (!D_801F4F31) {
            D_801F4F31 = true;
            gLightConfigAfterUnderwater = play->envCtx.changeLightNextConfig;
            if (play->envCtx.lightConfig != waterLightsIndex) {
                play->envCtx.lightConfig = waterLightsIndex;
                play->envCtx.changeLightNextConfig = waterLightsIndex;
            }
        } else if ((play->envCtx.lightConfig != waterLightsIndex) && (play->envCtx.changeLightTimer == 0)) {
            play->envCtx.changeLightEnabled = true;
            play->envCtx.changeLightNextConfig = waterLightsIndex;
            play->envCtx.changeDuration = 20;
            play->envCtx.changeLightTimer = play->envCtx.changeDuration;
        }
    } else if (play->envCtx.lightSettingOverride == LIGHT_SETTING_OVERRIDE_NONE) {
        if (!D_801F4F31) {
            D_801F4F31 = true;
            gLightConfigAfterUnderwater = play->envCtx.lightSetting;
        }
        play->envCtx.lightBlendEnabled = false; // instantly switch to water lights
        play->envCtx.lightSettingOverride = waterLightsIndex;
    }
}

void Environment_DisableUnderwaterLights(PlayState* play) {
    if (play->envCtx.lightMode == LIGHT_MODE_TIME) {
        if (D_801F4F31) {
            D_801F4F31 = false;
            play->envCtx.lightConfig = gLightConfigAfterUnderwater;
            play->envCtx.changeLightNextConfig = gLightConfigAfterUnderwater;
        }
    } else if (D_801F4F31) {
        D_801F4F31 = false;
        play->envCtx.lightSetting = gLightConfigAfterUnderwater;
        play->envCtx.lightBlendEnabled = false; // instantly switch to previous lights
        play->envCtx.lightSettingOverride = LIGHT_SETTING_OVERRIDE_NONE;
        play->envCtx.lightBlend = 1.0f;
    }
}

void func_800F6A04(void) {
    if ((gSaveContext.gameMode != GAMEMODE_NORMAL) && (gSaveContext.gameMode != GAMEMODE_END_CREDITS)) {
        Rumble_StateWipeRequests();
    }
}

void Environment_UpdateSkyboxRotY(PlayState* play) {
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) &&
        ((play->skyboxId == SKYBOX_NORMAL_SKY) || (play->skyboxId == SKYBOX_3))) {
        play->skyboxCtx.rot.y -= R_TIME_SPEED * 1.0e-4f;
    }
}

void Environment_UpdateNextDayTime(void) {
    if ((gSaveContext.nextDayTime >= 0xFF00) && (gSaveContext.nextDayTime != NEXT_TIME_NONE)) {
        gSaveContext.nextDayTime -= 0x10;

        // nextDayTime is used as both a time of day value and a timer to delay sfx when changing days.
        // When Sun's Song is played, nextDayTime is set to 0x8001 or 0 for day and night respectively.
        // These values will actually get used as a time of day value.
        // After this, nextDayTime is assigned magic values of 0xFFFE or 0xFFFD for day and night respectively.
        // From here, 0x10 is decremented from nextDayTime until it reaches either 0xFF0E or 0xFF0D, effectively
        // delaying the chicken crow or dog howl sfx by 15 frames when loading the new area.

        if (gSaveContext.nextDayTime == (NEXT_TIME_DAY_SET - (15 * 0x10))) {
            play_sound(NA_SE_EV_CHICKEN_CRY_M);
            gSaveContext.nextDayTime = NEXT_TIME_NONE;
        } else if (gSaveContext.nextDayTime == (NEXT_TIME_NIGHT_SET - (15 * 0x10))) {
            func_8019F128(NA_SE_EV_DOG_CRY_EVENING);
            gSaveContext.nextDayTime = NEXT_TIME_NONE;
        }
    }
}

void Environment_UpdateTime(PlayState* play, EnvironmentContext* envCtx, PauseContext* pauseCtx, MessageContext* msgCtx,
                            GameOverContext* gameOverCtx) {
    u16 time;

    if ((sEnvIsTimeStopped == 0) && (pauseCtx->state == PAUSE_STATE_OFF) && (gameOverCtx->state == GAMEOVER_INACTIVE)) {
        if ((msgCtx->msgMode == 0) || (msgCtx->currentTextId == 0xF7) || (msgCtx->currentTextId == 0x20D2) ||
            (msgCtx->currentTextId == 0x140C) ||
            ((msgCtx->currentTextId >= 0x100) && (msgCtx->currentTextId <= 0x200)) ||
            (((void)0, gSaveContext.gameMode) == GAMEMODE_END_CREDITS)) {
            if (!FrameAdvance_IsEnabled(&play->state) &&
                ((play->transitionMode == TRANS_MODE_OFF) || (((void)0, gSaveContext.gameMode) != GAMEMODE_NORMAL))) {
                if (play->transitionTrigger == TRANS_TRIGGER_OFF) {
                    if (CutsceneManager_GetCurrentCsId() == CS_ID_NONE) {
                        if (!Play_InCsMode(play)) {
                            gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)R_TIME_SPEED;
                            if (R_TIME_SPEED != 0) {
                                gSaveContext.save.time = ((void)0, gSaveContext.save.time) +
                                                         (u16)((void)0, gSaveContext.save.timeSpeedOffset);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((((void)0, gSaveContext.skyboxTime) >= CLOCK_TIME(6, 0)) ||
        (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0)) ||
        (((void)0, gSaveContext.save.time) >= (CLOCK_TIME(6, 0) + 0x10))) {
        gSaveContext.skyboxTime = gSaveContext.save.time;
    }

    time = ((void)0, gSaveContext.save.time);

    if ((time >= CLOCK_TIME(18, 0)) || (time < CLOCK_TIME(6, 0))) {
        gSaveContext.save.isNight = 1;
    } else {
        gSaveContext.save.isNight = 0;
    }
}

void func_800F6CEC(PlayState* play, u8 arg1, AdjLightSettings* adjLightSettings,
                   CurrentEnvLightSettings* lightSettings) {
    s32 phi_t1;
    s32 temp_v1_2;
    s32 temp_v1 = (arg1 % 4);

    if ((((void)0, gSaveContext.save.day) >= 2) && (arg1 >= 4) && (arg1 < 8)) {
        temp_v1_2 = (((void)0, gSaveContext.save.day) * 4) + 4;
        for (phi_t1 = 0; phi_t1 != 3; phi_t1++) {
            adjLightSettings->ambientColor[phi_t1] =
                lightSettings[temp_v1_2 + temp_v1].ambientColor[phi_t1] - lightSettings[temp_v1].ambientColor[phi_t1];
            adjLightSettings->diffuseColor1[phi_t1] =
                lightSettings[temp_v1_2 + temp_v1].diffuseColor1[phi_t1] - lightSettings[temp_v1].diffuseColor1[phi_t1];
            adjLightSettings->diffuseColor2[phi_t1] =
                lightSettings[temp_v1_2 + temp_v1].diffuseColor[phi_t1] -
                lightSettings[temp_v1].diffuseColor[phi_t1]; // TODO rename to diffuseColor2
            adjLightSettings->fogColor[phi_t1] =
                lightSettings[temp_v1_2 + temp_v1].fogColor[phi_t1] - lightSettings[temp_v1].fogColor[phi_t1];
        }
        adjLightSettings->fogNear = lightSettings[temp_v1_2 + temp_v1].fogNear - lightSettings[temp_v1].fogNear;
    }

    if ((arg1 >= 4) && (arg1 < 8) && (gWeatherMode == WEATHER_MODE_1)) {
        adjLightSettings->ambientColor[0] = -50;
        adjLightSettings->ambientColor[1] = -100;
        adjLightSettings->ambientColor[2] = -100;
        adjLightSettings->diffuseColor1[0] = -100;
        adjLightSettings->diffuseColor1[1] = -100;
        adjLightSettings->diffuseColor1[2] = -100;
        adjLightSettings->diffuseColor2[0] = -100;
        adjLightSettings->diffuseColor2[1] = -100;
        adjLightSettings->diffuseColor2[2] = -100;

        temp_v1 = arg1;
        adjLightSettings->fogColor[0] = -lightSettings[temp_v1].fogColor[0] + 30;
        adjLightSettings->fogColor[1] = -lightSettings[temp_v1].fogColor[1] + 30;
        adjLightSettings->fogColor[2] = -lightSettings[temp_v1].fogColor[2] + 45;
    }
}

u8 func_800F6EA4(f32 arg0, f32 arg1, f32 arg2) {
    arg0 = CLAMP(arg0, 0.0f, 255.0f);
    arg1 = CLAMP(arg1, 0.0f, 255.0f);

    return (((arg0 - arg1) * arg2) + arg1);
}

s32 Environment_IsSceneUpsideDown(PlayState* play) {
    s32 ret = false;

    if ((play->sceneId == SCENE_F41) || (play->sceneId == SCENE_INISIE_R)) {
        ret = true;
    }
    return ret;
}

void Environment_UpdateLights(PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateLights.s")

void Environment_UpdateSun(PlayState* play) {
    f32 temp_f0;
    s16 temp_a0;
    u16 phi_v0;

    if (!play->envCtx.sunDisabled) {
        if (play->envCtx.precipitation[PRECIP_RAIN_CUR] != 0) {
            Math_SmoothStepToF(&sSunPrimAlpha, 0.0f, 0.5f, 4.0f, 0.01f);
        } else {
            Math_SmoothStepToF(&sSunPrimAlpha, 255.0f, 0.5f, 4.0f, 0.01f);
        }

        if (Environment_IsSceneUpsideDown(play)) {
            phi_v0 = ((void)0, gSaveContext.save.time) + 0x8000;
        } else {
            phi_v0 = ((void)0, gSaveContext.save.time);
        }

        temp_a0 = phi_v0 - 0x8000;

        if (play->csCtx.state != CS_STATE_IDLE) {
            // TODO bug?
            Math_SmoothStepToF(&play->envCtx.sunPos.x, -(Math_SinS(temp_a0) * 120.0f) * 25.0f, 1.0f, 0.8f, 0.8f);
            Math_SmoothStepToF(&play->envCtx.sunPos.y, Math_CosS(temp_a0) * 120.0f * 25.0f, 1.0f, 0.8f, 0.8f);
            Math_SmoothStepToF(&play->envCtx.sunPos.y, Math_CosS(temp_a0) * 20.0f * 25.0f, 1.0f, 0.8f, 0.8f);
        } else {
            play->envCtx.sunPos.x = -(Math_SinS(temp_a0) * 120.0f) * 25.0f;
            play->envCtx.sunPos.y = Math_CosS(temp_a0) * 120.0f * 25.0f;
            play->envCtx.sunPos.z = Math_CosS(temp_a0) * 20.0f * 25.0f;
        }

        temp_f0 = play->envCtx.sunPos.y / 25.0f;
        if (Environment_IsSceneUpsideDown(play)) {
            temp_f0 = -temp_f0;
        }

        sSunEnvAlpha = temp_f0 / 80.0f * 255.0f;
        if (sSunEnvAlpha < 0.0f) {
            sSunEnvAlpha = 0.0f;
        }
        if (sSunEnvAlpha > 255.0f) {
            sSunEnvAlpha = 255.0f;
        }
        sSunEnvAlpha = 255.0f - sSunEnvAlpha;

        sSunColor = temp_f0 / 80.0f;
        if (sSunColor < 0.0f) {
            sSunColor = 0.0f;
        }
        if (sSunColor > 1.0f) {
            sSunColor = 1.0f;
        }

        sSunScale = (2.0f * sSunColor) + 12.0f;
    }
}

void func_800F88C4(u16 weekEventFlag) {
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_08) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_28_10) &&
        CHECK_WEEKEVENTREG(weekEventFlag)) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_91_04)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_28_08);
            SET_WEEKEVENTREG(WEEKEVENTREG_90_08);
            SET_WEEKEVENTREG(WEEKEVENTREG_51_02);
        }

        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_91_08)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_28_10);
            SET_WEEKEVENTREG(WEEKEVENTREG_90_08);
            SET_WEEKEVENTREG(WEEKEVENTREG_51_02);
        }
    }
}

void func_800F8970(void) {
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_27_40) && (SCHEDULE_TIME_NOW_ALT >= 0x2580)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_27_40);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_UPPER_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_27_80) && (SCHEDULE_TIME_NOW_ALT >= 0x2B30)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_27_80);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_NORTH_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_01) && (SCHEDULE_TIME_NOW_ALT >= 0x30E0)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_28_01);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_UPPER_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_02) && (SCHEDULE_TIME_NOW_ALT >= 0x3413)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_28_02);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_LOWER_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_04) && (SCHEDULE_TIME_NOW_ALT >= 0x39C3)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_28_04);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_LOWER_CLOCKTOWN);
    }
}

#ifdef NON_MATCHING
void Environment_UpdateSaveFlags(PlayState* play) {
    u8 v1;
    u16 temp_a2_2;

    if ((u8)((void)0, ((gSaveContext.eventInf[7] & 0xE0) >> 5)) != (u8)((void)0, gSaveContext.save.day)) {
        v1 = ((void)0, (gSaveContext.eventInf[7] & (u8)~0xE0)) | (((void)0, gSaveContext.save.day) << 5);
        gSaveContext.eventInf[7] = v1;
        SET_WEEKEVENTREG(WEEKEVENTREG_27_40);
        SET_WEEKEVENTREG(WEEKEVENTREG_27_80);
        SET_WEEKEVENTREG(WEEKEVENTREG_28_01);
        SET_WEEKEVENTREG(WEEKEVENTREG_28_02);
        SET_WEEKEVENTREG(WEEKEVENTREG_28_04);

        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_UPPER_CLOCKTOWN);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_NORTH_CLOCKTOWN);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_UPPER_CLOCKTOWN);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_LOWER_CLOCKTOWN);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_LOWER_CLOCKTOWN);

        CLEAR_WEEKEVENTREG(WEEKEVENTREG_27_40);
        CLEAR_WEEKEVENTREG(WEEKEVENTREG_27_80);
        CLEAR_WEEKEVENTREG(WEEKEVENTREG_28_01);
        CLEAR_WEEKEVENTREG(WEEKEVENTREG_28_02);
        CLEAR_WEEKEVENTREG(WEEKEVENTREG_28_04);
    }

    if ((SCHEDULE_TIME_NOW_ALT < 0x1FFE) || (SCHEDULE_TIME_NOW_ALT >= 0x3FFD)) {
        CLEAR_WEEKEVENTREG(WEEKEVENTREG_90_08);
    }

    func_800F8970();

    if (((CHECK_WEEKEVENTREG(WEEKEVENTREG_RECEIVED_ROOM_KEY)) == 0) &&
        ((CHECK_WEEKEVENTREG(WEEKEVENTREG_55_02)) == 0)) {
        if (((void)0, gSaveContext.save.day) >= 2) {
            SET_WEEKEVENTREG(WEEKEVENTREG_55_02);
        } else if ((((void)0, gSaveContext.save.day) == 1) && (SCHEDULE_TIME_NOW_ALT >= 0x6FF9)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_55_02);
        }
    }

    if ((CHECK_WEEKEVENTREG(WEEKEVENTREG_90_01)) == 0) {
        temp_a2_2 = ((void)0, gSaveContext.save.time) - D_801F4E78;
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_89_40) && ((SCHEDULE_TIME_NOW_ALT & 0xFFFF) >= 0xF556)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_90_01);
        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_89_08) && (temp_a2_2 >= 0x416)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_89_40);
            D_801F4E78 = 0;
        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_85_80) && (temp_a2_2 >= 0x1198)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_89_08);
            D_801F4E78 = gSaveContext.save.time;
        } else if (CHECK_WEEKEVENTREG(WEEKEVENTREG_86_01) && (temp_a2_2 >= 0xC43)) {
            SET_WEEKEVENTREG(WEEKEVENTREG_85_80);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateSaveFlags.s")
#endif

void Environment_Update(PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx, PauseContext* pauseCtx,
                        MessageContext* msgCtx, GameOverContext* gameOverCtx, GraphicsContext* gfxCtx) {
    D_801BDBC0 = 0;
    D_801BDBC4 = 0;

    func_800F6A04();

    if (pauseCtx->state == PAUSE_STATE_OFF) {
        Environment_UpdateSkyboxRotY(play);
        Environment_UpdateRain(play);
        Environment_UpdateTimeBasedSequence(play);
        Environment_UpdateNextDayTime();
        Environment_UpdateTime(play, envCtx, pauseCtx, msgCtx, gameOverCtx);
        Environment_UpdateSun(play);
        Environment_UpdateLights(play, envCtx, lightCtx);
        Environment_UpdateSaveFlags(play);
    }
}

void Environment_DrawSun(PlayState* play) {
    if (!play->envCtx.sunDisabled) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((play->envCtx.sunPos.y > -800.0f) || Environment_IsSceneUpsideDown(play)) {
            Matrix_Translate(play->view.eye.x + play->envCtx.sunPos.x, play->view.eye.y + play->envCtx.sunPos.y,
                             play->view.eye.z + play->envCtx.sunPos.z, MTXMODE_NEW);
            if (((void)0, gSaveContext.save.time) < 0x8000) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, (u8)((u8)(sSunColor * 52.0f) + 203),
                                (u8)((u8)(sSunColor * 19.0f) + 181), (u8)sSunPrimAlpha);
                gDPSetEnvColor(POLY_OPA_DISP++, (u8)(-(u8)(sSunColor * 5.0f) + 175),
                               (u8)((u8)(sSunColor * 135.0f) + 120), (u8)((u8)(sSunColor * 100.0f) + 100),
                               sSunEnvAlpha);
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, (u8)((u8)(sSunColor * 75.0f) + 180),
                                (u8)((u8)(sSunColor * 100.0f) + 100), (u8)sSunPrimAlpha);
                gDPSetEnvColor(POLY_OPA_DISP++, 180, (u8)(sSunColor * 255.0f), (u8)(sSunColor * 200.0f), sSunEnvAlpha);
            }
            Matrix_Scale(sSunScale, sSunScale, sSunScale, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_LOAD);
            Gfx_SetupDL54_Opa(play->state.gfxCtx);
            gSPDisplayList(POLY_OPA_DISP++, gSunDL);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void Environment_DrawSunLensFlare(PlayState* play, EnvironmentContext* envCtx, View* view, GraphicsContext* gfxCtx,
                                  Vec3f vec) {
    if ((play->envCtx.precipitation[PRECIP_RAIN_CUR] == 0) &&
        !(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER) && (play->skyboxId == SKYBOX_NORMAL_SKY)) {
        f32 v0 = Math_CosS(((void)0, gSaveContext.save.time) - 0x8000);

        Environment_DrawLensFlare(play, &play->envCtx, &play->view, play->state.gfxCtx, vec, 370.0f, v0 * 120.0f, 0x190,
                                  true);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawLensFlare.s")

f32 Environment_RandCentered(void) {
    return Rand_ZeroOne() - 0.5f;
}

void Environment_DrawRainImpl(PlayState* play, View* view, GraphicsContext* gfxCtx);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawRainImpl.s")

void Environment_DrawRain(PlayState* play, View* view, GraphicsContext* gfxCtx) {
    if (!(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER) &&
        (play->envCtx.precipitation[PRECIP_SNOW_CUR] == 0)) {
        if (play->envCtx.precipitation[PRECIP_SOS_MAX] != 0) {
            if (play->envCtx.precipitation[PRECIP_SNOW_CUR] == 0) {
                Environment_DrawRainImpl(play, view, gfxCtx);
            }
        } else if (!(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER)) {
            if ((Environment_GetStormState(play) != STORM_STATE_OFF) &&
                (play->envCtx.precipitation[PRECIP_SNOW_CUR] == 0)) {
                Environment_DrawRainImpl(play, view, gfxCtx);
            }
        }
    }
}

void Environment_ChangeLightSetting(PlayState* play, u8 lightSetting) {
    if (play->envCtx.lightMode == LIGHT_MODE_TIME) {
        if ((lightSetting == LIGHT_SETTING_MAX) || D_801F4F33) {
            if (D_801F4F30 != 0xFF) {
                play->envCtx.changeLightEnabled = true;
                play->envCtx.changeLightNextConfig = D_801F4F30;
                play->envCtx.changeDuration = 20;
                play->envCtx.changeLightTimer = play->envCtx.changeDuration;
                D_801F4F30 = 0xFF;
            }
        } else if (play->envCtx.changeLightNextConfig != lightSetting) {
            D_801F4F30 = play->envCtx.lightConfig;
            play->envCtx.changeLightEnabled = true;
            play->envCtx.changeLightNextConfig = lightSetting;
            play->envCtx.changeDuration = 20;
            play->envCtx.changeLightTimer = play->envCtx.changeDuration;
        }
    } else if ((play->envCtx.lightSetting != lightSetting) && (play->envCtx.lightBlend >= 1.0f) &&
               (play->envCtx.lightSettingOverride == LIGHT_SETTING_OVERRIDE_NONE)) {
        if (lightSetting >= LIGHT_SETTING_MAX) {
            lightSetting = 0;
        }

        play->envCtx.lightBlend = 0.0f;
        play->envCtx.prevLightSetting = play->envCtx.lightSetting;
        play->envCtx.lightSetting = lightSetting;
    }
}

void Environment_DrawSkyboxFilters(PlayState* play) {
    if ((((play->skyboxId != SKYBOX_NONE) && (play->lightCtx.fogNear < 980)) || (play->skyboxId >= SKYBOX_2)) &&
        ((play->skyboxId != SKYBOX_3) || (D_801F4E74 != 0.0f))) {
        f32 alpha;

        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL57_Opa(play->state.gfxCtx);

        alpha = (1000 - play->lightCtx.fogNear) * 0.02f;

        if (play->skyboxId == SKYBOX_2) {
            alpha = 1.0f;
        }

        if (alpha > 1.0f) {
            alpha = 1.0f;
        }

        if (play->skyboxId != SKYBOX_3) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, play->lightCtx.fogColor[0], play->lightCtx.fogColor[1],
                            play->lightCtx.fogColor[2], 255.0f * alpha);
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, play->lightCtx.fogColor[0] + 16, play->lightCtx.fogColor[1] + 16,
                            play->lightCtx.fogColor[2] + 16, 255.0f * D_801F4E74);
        }
        gSPDisplayList(POLY_OPA_DISP++, D_0E000000.clearFillRect);

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (play->envCtx.customSkyboxFilter) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL57_Opa(play->state.gfxCtx);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, play->envCtx.skyboxFilterColor[0], play->envCtx.skyboxFilterColor[1],
                        play->envCtx.skyboxFilterColor[2], play->envCtx.skyboxFilterColor[3]);
        gSPDisplayList(POLY_OPA_DISP++, D_0E000000.clearFillRect);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void Environment_DrawLightningFlash(PlayState* play, u8 red, u8 green, u8 blue, u8 alpha) {
    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL57_Opa(play->state.gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, red, green, blue, alpha);
    gSPDisplayList(POLY_OPA_DISP++, D_0E000000.clearFillRect);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Environment_UpdateLightningStrike(PlayState* play) {
    if (play->envCtx.lightningState != LIGHTNING_OFF) {
        switch (gLightningStrike.state) {
            case LIGHTNING_STRIKE_WAIT:
                // every frame theres a 10% chance of the timer advancing 10 units
                if (Rand_ZeroOne() < 0.1f) {
                    gLightningStrike.delayTimer += 10.0f;
                }

                gLightningStrike.delayTimer += Rand_ZeroOne();

                if (gLightningStrike.delayTimer > 500.0f) {
                    gLightningStrike.flashRed = 200;
                    gLightningStrike.flashGreen = 200;
                    gLightningStrike.flashBlue = 255;
                    gLightningStrike.flashAlphaTarget = 200;

                    gLightningStrike.delayTimer = 0.0f;
                    Environment_AddLightningBolts(
                        play, (u8)((Rand_ZeroOne() * (ARRAY_COUNT(sLightningBolts) - 0.1f)) + 1.0f));
                    sLightningFlashAlpha = 0;
                    gLightningStrike.state++;
                }
                break;

            case LIGHTNING_STRIKE_START:
                gLightningStrike.flashRed = 200;
                gLightningStrike.flashGreen = 200;
                gLightningStrike.flashBlue = 255;

                play->envCtx.adjLightSettings.ambientColor[0] += 80;
                play->envCtx.adjLightSettings.ambientColor[1] += 80;
                play->envCtx.adjLightSettings.ambientColor[2] += 100;

                sLightningFlashAlpha += 100;

                if (sLightningFlashAlpha >= gLightningStrike.flashAlphaTarget) {
                    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_0, 0);
                    gLightningStrike.state++;
                    gLightningStrike.flashAlphaTarget = 0;
                }
                break;

            case LIGHTNING_STRIKE_END:
                if (play->envCtx.adjLightSettings.ambientColor[0] > 0) {
                    play->envCtx.adjLightSettings.ambientColor[0] -= 10;
                    play->envCtx.adjLightSettings.ambientColor[1] -= 10;
                }

                if (play->envCtx.adjLightSettings.ambientColor[2] > 0) {
                    play->envCtx.adjLightSettings.ambientColor[2] -= 10;
                }

                sLightningFlashAlpha -= 10;

                if (sLightningFlashAlpha <= gLightningStrike.flashAlphaTarget) {
                    play->envCtx.adjLightSettings.ambientColor[0] = 0;
                    play->envCtx.adjLightSettings.ambientColor[1] = 0;
                    play->envCtx.adjLightSettings.ambientColor[2] = 0;

                    gLightningStrike.state = LIGHTNING_STRIKE_WAIT;

                    if (play->envCtx.lightningState == LIGHTNING_LAST) {
                        play->envCtx.lightningState = LIGHTNING_OFF;
                    }
                }
                break;

            default:
                break;
        }
    }

    if (gLightningStrike.state != LIGHTNING_STRIKE_WAIT) {
        Environment_DrawLightningFlash(play, gLightningStrike.flashRed, gLightningStrike.flashGreen,
                                       gLightningStrike.flashBlue, sLightningFlashAlpha);
    }
}

void Environment_AddLightningBolts(PlayState* play, u8 num) {
    s16 boltsAdded = 0;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(sLightningBolts); i++) {
        if (sLightningBolts[i].state == LIGHTNING_BOLT_INACTIVE) {
            sLightningBolts[i].state = LIGHTNING_BOLT_START;
            boltsAdded++;

            if (boltsAdded >= num) {
                break;
            }
        }
    }
}

extern void* sLightningTextures[8]; // TODO static
// static void* sLightningTextures[] = {
// gEffLightning1Tex, gEffLightning2Tex, gEffLightning3Tex,
// gEffLightning4Tex, gEffLightning5Tex, gEffLightning6Tex,
// gEffLightning7Tex, gEffLightning8Tex, NULL,
// };

/**
 * Draw any active lightning bolt entries contained in `sLightningBolts`
 */
void Environment_DrawLightning(PlayState* play, s32 unused) {
    s16 i;
    f32 dx;
    f32 dz;
    f32 x;
    f32 z;
    s32 pad[2];

    OPEN_DISPS(play->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(sLightningBolts); i++) {
        switch (sLightningBolts[i].state) {
            case LIGHTNING_BOLT_START:
                dx = play->view.at.x - play->view.eye.x;
                dz = play->view.at.z - play->view.eye.z;

                x = dx / sqrtf(SQ(dx) + SQ(dz));
                z = dz / sqrtf(SQ(dx) + SQ(dz));

                sLightningBolts[i].pos.x = play->view.eye.x + x * 9500.0f;
                sLightningBolts[i].pos.y = Rand_ZeroOne() * 1000.0f + 4000.0f;
                sLightningBolts[i].pos.z = play->view.eye.z + z * 9500.0f;

                sLightningBolts[i].offset.x = (Rand_ZeroOne() - 0.5f) * 5000.0f;
                sLightningBolts[i].offset.y = 0.0f;
                sLightningBolts[i].offset.z = (Rand_ZeroOne() - 0.5f) * 5000.0f;

                sLightningBolts[i].textureIndex = 0;
                sLightningBolts[i].pitch = (Rand_ZeroOne() - 0.5f) * 40.0f;
                sLightningBolts[i].roll = (Rand_ZeroOne() - 0.5f) * 40.0f;
                sLightningBolts[i].delayTimer = 3 * (i + 1);
                sLightningBolts[i].state++;
                break;

            case LIGHTNING_BOLT_WAIT:
                sLightningBolts[i].delayTimer--;

                if (sLightningBolts[i].delayTimer <= 0) {
                    sLightningBolts[i].state++;
                }
                break;

            case LIGHTNING_BOLT_DRAW:
                if (sLightningBolts[i].textureIndex < 7) {
                    sLightningBolts[i].textureIndex++;
                } else {
                    sLightningBolts[i].state = LIGHTNING_BOLT_INACTIVE;
                }
                break;

            default:
                break;
        }

        if (sLightningBolts[i].state == LIGHTNING_BOLT_DRAW) {
            Matrix_Translate(sLightningBolts[i].pos.x + sLightningBolts[i].offset.x,
                             sLightningBolts[i].pos.y + sLightningBolts[i].offset.y,
                             sLightningBolts[i].pos.z + sLightningBolts[i].offset.z, MTXMODE_NEW);
            Matrix_RotateXFApply(DEG_TO_RAD(sLightningBolts[i].pitch));
            Matrix_RotateZF(DEG_TO_RAD(sLightningBolts[i].roll), MTXMODE_APPLY);
            Matrix_Scale(22.0f, 100.0f, 22.0f, MTXMODE_APPLY);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 128);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 255, 255, 128);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Lib_SegmentedToVirtual(sLightningTextures[sLightningBolts[i].textureIndex]));
            Gfx_SetupDL61_Xlu(play->state.gfxCtx);
            gSPMatrix(POLY_XLU_DISP++, &D_01000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gEffLightningDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void Environment_PlaySceneSequence(PlayState* play) {
    u8 dayMinusOne = ((void)0, gSaveContext.save.day) - 1;

    if (dayMinusOne >= 3) {
        dayMinusOne = 0;
    }

    if (play->envCtx.timeSeqState != TIMESEQ_REQUEST) {
        play->envCtx.timeSeqState = TIMESEQ_DISABLED;
        if (((void)0, gSaveContext.forcedSeqId) != NA_BGM_GENERAL_SFX) {
            play->envCtx.timeSeqState = TIMESEQ_REQUEST;
            SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0, ((void)0, gSaveContext.forcedSeqId) + SEQ_FLAG_ASYNC);
            gSaveContext.forcedSeqId = NA_BGM_GENERAL_SFX;
        } else if (!Environment_IsFinalHours(play) || func_800FE5D0(play) ||
                   (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) != NA_BGM_FINAL_HOURS)) {
            if (play->sequenceCtx.seqId == NA_BGM_NO_MUSIC) {
                if (play->sequenceCtx.ambienceId == AMBIENCE_ID_13) {
                    return;
                }
                if (play->sequenceCtx.ambienceId != ((void)0, gSaveContext.ambienceId)) {
                    Audio_PlayAmbience(play->sequenceCtx.ambienceId);
                }
            } else if (play->sequenceCtx.ambienceId == AMBIENCE_ID_13) {
                if (play->sequenceCtx.seqId != ((void)0, gSaveContext.seqId)) {
                    Audio_PlaySceneSequence(play->sequenceCtx.seqId, dayMinusOne);
                }
            } else if ((((void)0, gSaveContext.save.time) >= CLOCK_TIME(6, 0)) &&
                       (((void)0, gSaveContext.save.time) <= CLOCK_TIME(17, 10))) {
                if (sSceneSeqState != SCENESEQ_DEFAULT) {
                    Audio_PlayMorningSceneSequence(play->sequenceCtx.seqId, dayMinusOne);
                } else if ((((void)0, gSaveContext.save.time) >= CLOCK_TIME(6, 1)) &&
                           (play->sequenceCtx.seqId != ((void)0, gSaveContext.seqId))) {
                    Audio_PlaySceneSequence(play->sequenceCtx.seqId, dayMinusOne);
                }
                play->envCtx.timeSeqState = TIMESEQ_FADE_DAY_BGM;
            } else {
                if (play->sequenceCtx.ambienceId != ((void)0, gSaveContext.ambienceId)) {
                    Audio_PlayAmbience(play->sequenceCtx.ambienceId);
                }
                if ((((void)0, gSaveContext.save.time) > CLOCK_TIME(17, 10)) &&
                    (((void)0, gSaveContext.save.time) < CLOCK_TIME(19, 0))) {
                    play->envCtx.timeSeqState = TIMESEQ_EARLY_NIGHT_CRITTERS;
                } else if ((((void)0, gSaveContext.save.time) > CLOCK_TIME(19, 0)) ||
                           (((void)0, gSaveContext.save.time) < CLOCK_TIME(5, 0))) {
                    play->envCtx.timeSeqState = TIMESEQ_NIGHT_CRITTERS;
                } else {
                    play->envCtx.timeSeqState = TIMESEQ_MORNING_CRITTERS;
                }
            }
        }
        func_801A3CD8(play->roomCtx.curRoom.echo);
        sSceneSeqState = SCENESEQ_DEFAULT;
    }
}

void Environment_UpdateTimeBasedSequence(PlayState* play) {
    s32 pad;

    //! FAKE:
    if (&gSaveContext.save) {}

    if ((play->csCtx.state == 0) && !(play->actorCtx.flags & ACTORCTX_FLAG_1)) {
        switch (play->envCtx.timeSeqState) {
            case TIMESEQ_DAY_BGM:
                break;

            case TIMESEQ_FADE_DAY_BGM:
                if (((void)0, gSaveContext.save.time) > CLOCK_TIME(17, 10)) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 240);
                    play->envCtx.timeSeqState++;
                }
                break;

            case TIMESEQ_NIGHT_BEGIN_SFX:
                if (((void)0, gSaveContext.save.time) >= CLOCK_TIME(18, 0)) {
                    play->envCtx.timeSeqState++;
                }
                break;

            case TIMESEQ_EARLY_NIGHT_CRITTERS:
                if (play->envCtx.precipitation[PRECIP_RAIN_CUR] < 9) {
                    Audio_PlayAmbience(play->sequenceCtx.ambienceId);
                    Audio_SetAmbienceChannelIO(1, 1, 1);
                }
                play->envCtx.timeSeqState++;
                break;

            case TIMESEQ_NIGHT_DELAY:
                if (((void)0, gSaveContext.save.time) >= CLOCK_TIME(19, 0)) {
                    play->envCtx.timeSeqState++;
                }
                break;

            case TIMESEQ_NIGHT_CRITTERS:
                Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_CRITTER_0, 1, 0);
                Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_CRITTER_1 << 4 | AMBIENCE_CHANNEL_CRITTER_3, 1, 1);
                play->envCtx.timeSeqState++;
                break;

            case TIMESEQ_DAY_BEGIN_SFX:
                if ((((void)0, gSaveContext.save.time) < CLOCK_TIME(19, 0)) &&
                    (((void)0, gSaveContext.save.time) >= CLOCK_TIME(5, 0))) {
                    play->envCtx.timeSeqState++;
                }
                break;

            case TIMESEQ_MORNING_CRITTERS:
                Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_CRITTER_1 << 4 | AMBIENCE_CHANNEL_CRITTER_3, 1, 0);
                Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_CRITTER_4 << 4 | AMBIENCE_CHANNEL_CRITTER_5, 1, 1);
                play->envCtx.timeSeqState++;
                break;

            case TIMESEQ_DAY_DELAY:
                break;

            default:
                break;
        }
    }

    if ((play->envCtx.timeSeqState != TIMESEQ_REQUEST) && (((void)0, gSaveContext.save.day) == 3) &&
        (((void)0, gSaveContext.save.time) < CLOCK_TIME(6, 0)) && !func_800FE5D0(play) &&
        (play->transitionTrigger == TRANS_TRIGGER_OFF) && (play->transitionMode == TRANS_MODE_OFF) &&
        (play->csCtx.state == 0) && ((play->sceneId != SCENE_00KEIKOKU) || (((void)0, gSaveContext.sceneLayer) != 1)) &&
        (CutsceneManager_GetCurrentCsId() == CS_ID_NONE) &&
        (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) != NA_BGM_FINAL_HOURS) &&
        (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) != NA_BGM_SONG_OF_SOARING)) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_AMBIENCE, 0);
        Audio_PlaySceneSequence(NA_BGM_FINAL_HOURS, 3 - 1);
    }
}

void Environment_DrawCustomLensFlare(PlayState* play) {
    Vec3f pos;

    if (gCustomLensFlare1On) {
        pos.x = gCustomLensFlare1Pos.x;
        pos.y = gCustomLensFlare1Pos.y;
        pos.z = gCustomLensFlare1Pos.z;
        Environment_DrawLensFlare(play, &play->envCtx, &play->view, play->state.gfxCtx, pos, D_801F4E44, D_801F4E48,
                                  D_801F4E4C, 0);
    }

    if (gCustomLensFlare2On) {
        pos.x = gCustomLensFlare2Pos.x;
        pos.y = gCustomLensFlare2Pos.y;
        pos.z = gCustomLensFlare2Pos.z;
        Environment_DrawLensFlare(play, &play->envCtx, &play->view, play->state.gfxCtx, pos, D_801F4E5C, D_801F4E60,
                                  D_801F4E64, 0);
    }
}

void Environment_InitGameOverLights(PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    sGameOverLightsIntensity = 0;

    Lights_PointNoGlowSetInfo(&sNGameOverLightInfo, player->actor.world.pos.x - 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z - 10.0f, 0, 0, 0, 255);
    sNGameOverLightNode = LightContext_InsertLight(play, &play->lightCtx, &sNGameOverLightInfo);

    Lights_PointNoGlowSetInfo(&sSGameOverLightInfo, player->actor.world.pos.x + 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z + 10.0f, 0, 0, 0, 255);

    sSGameOverLightNode = LightContext_InsertLight(play, &play->lightCtx, &sSGameOverLightInfo);
}

void Environment_FadeInGameOverLights(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 i;

    Lights_PointNoGlowSetInfo(&sNGameOverLightInfo, player->actor.world.pos.x - 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z - 10.0f,
                              sGameOverLightsIntensity, sGameOverLightsIntensity, sGameOverLightsIntensity, 255);
    Lights_PointNoGlowSetInfo(&sSGameOverLightInfo, player->actor.world.pos.x + 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z + 10.0f,
                              sGameOverLightsIntensity, sGameOverLightsIntensity, sGameOverLightsIntensity, 255);

    if (sGameOverLightsIntensity < 254) {
        sGameOverLightsIntensity += 2;
    }

    if (Play_CamIsNotFixed(&play->state)) {
        for (i = 0; i < 3; i++) {
            if (play->envCtx.adjLightSettings.ambientColor[i] > -255) {
                play->envCtx.adjLightSettings.ambientColor[i] -= 12;
                play->envCtx.adjLightSettings.diffuseColor1[i] -= 12;
            }
            play->envCtx.adjLightSettings.fogColor[i] = -255;
        }

        if (play->envCtx.lightSettings.zFar + play->envCtx.adjLightSettings.zFar > 900) {
            play->envCtx.adjLightSettings.zFar -= 100;
        }

        if (play->envCtx.lightSettings.fogNear + play->envCtx.adjLightSettings.fogNear > 950) {
            play->envCtx.adjLightSettings.fogNear -= 10;
        }
    } else {
        play->envCtx.fillScreen = true;
        play->envCtx.screenFillColor[0] = 0;
        play->envCtx.screenFillColor[1] = 0;
        play->envCtx.screenFillColor[2] = 0;
        play->envCtx.screenFillColor[3] = sGameOverLightsIntensity;
    }
}

void Environment_FadeOutGameOverLights(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 i;

    if (sGameOverLightsIntensity >= 3) {
        sGameOverLightsIntensity -= 3;
    } else {
        sGameOverLightsIntensity = 0;
    }

    if (sGameOverLightsIntensity == 1) {
        LightContext_RemoveLight(play, &play->lightCtx, sNGameOverLightNode);
        LightContext_RemoveLight(play, &play->lightCtx, sSGameOverLightNode);
    } else if (sGameOverLightsIntensity >= 2) {
        Lights_PointNoGlowSetInfo(&sNGameOverLightInfo, player->actor.world.pos.x - 10.0f,
                                  player->actor.world.pos.y + 10.0f, player->actor.world.pos.z - 10.0f,
                                  sGameOverLightsIntensity, sGameOverLightsIntensity, sGameOverLightsIntensity, 255);
        Lights_PointNoGlowSetInfo(&sSGameOverLightInfo, player->actor.world.pos.x + 10.0f,
                                  player->actor.world.pos.y + 10.0f, player->actor.world.pos.z + 10.0f,
                                  sGameOverLightsIntensity, sGameOverLightsIntensity, sGameOverLightsIntensity, 255);
    }

    if (Play_CamIsNotFixed(&play->state)) {
        for (i = 0; i < 3; i++) {
            Math_SmoothStepToS(&play->envCtx.adjLightSettings.ambientColor[i], 0, 5, 12, 1);
            Math_SmoothStepToS(&play->envCtx.adjLightSettings.diffuseColor1[i], 0, 5, 12, 1);
            play->envCtx.adjLightSettings.fogColor[i] = 0;
        }
        play->envCtx.adjLightSettings.zFar = 0;
        play->envCtx.adjLightSettings.fogNear = 0;
    } else {
        play->envCtx.fillScreen = true;
        play->envCtx.screenFillColor[0] = 0;
        play->envCtx.screenFillColor[1] = 0;
        play->envCtx.screenFillColor[2] = 0;
        play->envCtx.screenFillColor[3] = sGameOverLightsIntensity;
        if (sGameOverLightsIntensity == 0) {
            play->envCtx.fillScreen = false;
        }
    }
}

void Environment_UpdateRain(PlayState* play) {
    u8 max = MAX(play->envCtx.precipitation[PRECIP_RAIN_MAX], play->envCtx.precipitation[PRECIP_SOS_MAX]);

    if ((play->envCtx.precipitation[PRECIP_RAIN_CUR] != max) && ((play->state.frames % 8) == 0)) {
        if (play->envCtx.precipitation[PRECIP_RAIN_CUR] < max) {
            play->envCtx.precipitation[PRECIP_RAIN_CUR] += 2;
        } else {
            play->envCtx.precipitation[PRECIP_RAIN_CUR] -= 2;
        }
    }
}

void Environment_FillScreen(GraphicsContext* gfxCtx, u8 red, u8 green, u8 blue, u8 alpha, u8 drawFlags) {
    if (alpha != 0) {
        OPEN_DISPS(gfxCtx);

        if (drawFlags & FILL_SCREEN_OPA) {
            POLY_OPA_DISP = Gfx_SetupDL57(POLY_OPA_DISP);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, red, green, blue, alpha);
            gDPSetAlphaDither(POLY_OPA_DISP++, G_AD_DISABLE);
            gDPSetColorDither(POLY_OPA_DISP++, G_CD_DISABLE);
            gSPDisplayList(POLY_OPA_DISP++, D_0E000000.clearFillRect);
        }

        if (drawFlags & FILL_SCREEN_XLU) {
            POLY_XLU_DISP = Gfx_SetupDL57(POLY_XLU_DISP);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, red, green, blue, alpha);

            if ((u32)alpha == 255) {
                gDPSetRenderMode(POLY_XLU_DISP++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            }

            gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_DISABLE);
            gDPSetColorDither(POLY_XLU_DISP++, G_CD_DISABLE);
            gSPDisplayList(POLY_XLU_DISP++, D_0E000000.clearFillRect);
        }

        CLOSE_DISPS(gfxCtx);
    }
}

extern Color_RGB8 sSandstormPrimColors[8];
extern Color_RGB8 sSandstormEnvColors[8];

// Color_RGB8 sSandstormPrimColors[] = {
//     { 255, 255, 255},
//     { 255, 255, 255},
//     { 255, 255, 255},
//     { 255, 255, 255},
//     { 210, 156, 85},
//     { 255, 200, 100},
//     { 225, 160, 50},
//     { 105, 90, 40},
// };

// Color_RGB8 sSandstormEnvColors[] = {
// { 100, 100, 100 },
// { 100, 100, 100 },
// { 100, 100, 100 },
// { 100, 100, 100 },
// { 155, 106, 35 },
// { 200, 150, 50 },
// { 170, 110, 0 },
// { 50, 40, 0 },
// };

#ifdef NON_EQUIVALENT
void Environment_DrawSandstorm(PlayState* play, u8 sandstormState) {
    s32 primA1;
    s32 envA1;
    s32 primA = play->envCtx.sandstormPrimA;
    s32 envA = play->envCtx.sandstormEnvA;
    Color_RGBA8 primColor;
    Color_RGBA8 envColor;
    s32 index;
    f32 sp98;
    u16 sp96;
    u16 sp94;
    u16 sp92;

    switch (sandstormState) {
        case SANDSTORM_ACTIVE:
            envA1 = 128; // TODO: Bottom?
            primA1 = play->state.frames % 128;
            if (primA1 > 128) {
                primA1 = 255 - primA1;
            }
            primA1 += 73;
            break;

        case SANDSTORM_FILL:
            primA1 = 255;
            envA1 = (play->envCtx.sandstormPrimA >= 255) ? 255 : 128;
            break;

        case SANDSTORM_UNFILL:
        case SANDSTORM_5:
            envA1 = 128;
            if (play->envCtx.sandstormEnvA > 128) {
                primA1 = 255;
            } else {
                primA1 = play->state.frames % 128;
                if (primA1 > 64) {
                    primA1 = 128 - primA1;
                }
                primA1 += 73;
            }
            if ((primA1 >= primA) && (primA1 != 255)) {
                play->envCtx.sandstormState++;
            }
            break;

        case SANDSTORM_DISSIPATE:
            envA1 = 0;
            primA1 = (play->envCtx.sandstormEnvA > 128) ? 255 : play->envCtx.sandstormEnvA >> 1;

            if (primA == 0) {
                play->envCtx.sandstormState = SANDSTORM_OFF;
            }
            break;

        case SANDSTORM_6:
        case SANDSTORM_8:
            envA1 = 1;
            primA1 = D_801F4E30;
            if (sandstormState == SANDSTORM_8) {
                envA1 = 0xA;
            }
            break;

        case SANDSTORM_7:
        case SANDSTORM_9:
            envA1 = 1;
            if (play->envCtx.sandstormPrimA == 0) {
                play->envCtx.sandstormState = SANDSTORM_OFF;
            }
            if (sandstormState == SANDSTORM_9) {
                envA1 = 0xA;
            }
            break;

        case SANDSTORM_A:
            envA1 = 0xFF;
            primA1 = D_801F4E30;
            if (play->envCtx.sandstormPrimA == 0) {
                play->envCtx.sandstormState = SANDSTORM_OFF;
            }
            break;

        case SANDSTORM_B:
            envA1 = 0x80;
            primA1 = play->state.frames & 0x7F;
            if (primA1 >= 0x41) {
                primA1 = 0x80 - primA1;
            }
            primA1 = primA1 + 0x49;
            break;

        case SANDSTORM_C:
            if (play->envCtx.sandstormPrimA == 0) {
                play->envCtx.sandstormState = SANDSTORM_OFF;
            }
            break;

        case SANDSTORM_D:
            envA1 = 0xA;
            primA1 = D_801F4E30;
            break;
    }

    if (ABS_ALT(primA - primA1) < 9) {
        primA = primA1;
    } else if (primA1 < primA) {
        primA = primA - 9;
    } else {
        primA = primA + 9;
    }

    if (ABS_ALT(envA - envA1) < 9) {
        envA = envA1;
    } else if (envA1 < envA) {
        envA = envA - 9;
    } else {
        envA = envA + 9;
    }

    play->envCtx.sandstormPrimA = primA;
    play->envCtx.sandstormEnvA = envA;

    sp98 = (512.0f - (primA + envA)) * (3.0f / 128.0f);

    if (sp98 > 6.0f) {
        sp98 = 6.0f;
    }

    if (play->envCtx.sandstormPrimA != 0) {
        index = 0;
        if (sandstormState >= SANDSTORM_B) {
            index = 0xC;
        }

        if ((play->envCtx.lightMode != LIGHT_MODE_TIME) ||
            (play->envCtx.lightSettingOverride != LIGHT_SETTING_OVERRIDE_NONE)) {
            primColor.r = sSandstormPrimColors[1 + index].r;
            primColor.g = sSandstormPrimColors[1 + index].g;
            primColor.b = sSandstormPrimColors[1 + index].b;
            envColor.r = sSandstormEnvColors[1 + index].r;
            envColor.g = sSandstormEnvColors[1 + index].g;
            envColor.b = sSandstormEnvColors[1 + index].b;
        } else if (sandstormLerpScale == sNextSandstormColorIndex) {
            primColor.r = sSandstormPrimColors[sandstormLerpScale + index].r;
            primColor.g = sSandstormPrimColors[sandstormLerpScale + index].g;
            primColor.b = sSandstormPrimColors[sandstormLerpScale + index].b;
            envColor.r = sSandstormEnvColors[sandstormLerpScale + index].r;
            envColor.g = sSandstormEnvColors[sandstormLerpScale + index].g;
            envColor.b = sSandstormEnvColors[sandstormLerpScale + index].b;
        } else {
            primColor.r = (s32)F32_LERP(sSandstormPrimColors[sandstormLerpScale + index].r,
                                        sSandstormPrimColors[sNextSandstormColorIndex + index].r, sSandstormLerpScale);
            primColor.g = (s32)F32_LERP(sSandstormPrimColors[sandstormLerpScale + index].g,
                                        sSandstormPrimColors[sNextSandstormColorIndex + index].g, sSandstormLerpScale);
            primColor.b = (s32)F32_LERP(sSandstormPrimColors[sandstormLerpScale + index].b,
                                        sSandstormPrimColors[sNextSandstormColorIndex + index].b, sSandstormLerpScale);
            envColor.r = (s32)F32_LERP(sSandstormEnvColors[sandstormLerpScale + index].r,
                                       sSandstormEnvColors[sNextSandstormColorIndex + index].r, sSandstormLerpScale);
            envColor.g = (s32)F32_LERP(sSandstormEnvColors[sandstormLerpScale + index].g,
                                       sSandstormEnvColors[sNextSandstormColorIndex + index].g, sSandstormLerpScale);
            envColor.b = (s32)F32_LERP(sSandstormEnvColors[sandstormLerpScale + index].b,
                                       sSandstormEnvColors[sNextSandstormColorIndex + index].b, sSandstormLerpScale);
        }

        envColor.r = ((envColor.r * sp98) + ((6.0f - sp98) * primColor.r)) * (1.0f / 6.0f);
        envColor.g = ((envColor.g * sp98) + ((6.0f - sp98) * primColor.g)) * (1.0f / 6.0f);
        envColor.b = ((envColor.b * sp98) + ((6.0f - sp98) * primColor.b)) * (1.0f / 6.0f);

        sp96 = (u32)(sSandstormScroll * (11.0f / 6.0f));
        sp94 = (u32)(sSandstormScroll * (9.0f / 6.0f));
        sp92 = (u32)(sSandstormScroll * (6.0f / 6.0f));

        OPEN_DISPS(play->state.gfxCtx);

        POLY_XLU_DISP = func_8012C3A4(POLY_XLU_DISP);

        gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);
        gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, primColor.r, primColor.g, primColor.b, play->envCtx.sandstormPrimA);
        gDPSetEnvColor(POLY_XLU_DISP++, envColor.r, envColor.g, envColor.b, play->envCtx.sandstormEnvA);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, (u32)sp96 % 4096, 0, 512, 32, 1,
                                    (u32)sp94 % 4096, 4095 - ((u32)sp92 % 4096), 256, 64));
        gDPSetTextureLUT(POLY_XLU_DISP++, G_TT_NONE);
        gSPDisplayList(POLY_XLU_DISP++, gFieldSandstormDL);

        CLOSE_DISPS(play->state.gfxCtx);
    }

    sSandstormScroll += (s32)sp98;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSandstorm.s")
#endif

s32 Environment_AdjustLights(PlayState* play, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 temp;
    s32 i;
    Player* player = GET_PLAYER(play);

    if (play->roomCtx.curRoom.behaviorType1 == ROOM_BEHAVIOR_TYPE1_5) {
        return 0;
    }

    if (!Play_CamIsNotFixed(&play->state)) {
        return 0;
    }
    if (play->unk_18880 != 0) {
        return 0;
    }
    if ((player != NULL) && (player->stateFlags1 & PLAYER_STATE1_2)) {
        return 0;
    }

    arg1 = CLAMP_MIN(arg1, 0.0f);
    arg1 = CLAMP_MAX(arg1, 1.0f);

    temp = arg1 - arg3;

    if (arg1 < arg3) {
        temp = 0.0f;
    }

    play->envCtx.adjLightSettings.fogNear = (arg2 - play->envCtx.lightSettings.fogNear) * temp;

    if (arg1 == 0.0f) {
        for (i = 0; i < 3; i++) {
            play->envCtx.adjLightSettings.fogColor[i] = 0;
        }
    } else {
        temp = arg1 * 5.0f;
        temp = CLAMP_MAX(temp, 1.0f);

        for (i = 0; i < 3; i++) {
            play->envCtx.adjLightSettings.fogColor[i] = -(f32)play->envCtx.lightSettings.fogColor[i] * temp;
        }
    }

    if (arg4 <= 0.0f) {
        return 1;
    }

    arg1 *= arg4;

    for (i = 0; i < 3; i++) {
        play->envCtx.adjLightSettings.ambientColor[i] = -(f32)play->envCtx.lightSettings.ambientColor[i] * arg1;
        play->envCtx.adjLightSettings.diffuseColor1[i] = -(f32)play->envCtx.lightSettings.diffuseColor1[i] * arg1;
    }

    return 1;
}

// Get ((to - from) * lerp)
void Environment_LerpRGB8(Color_RGB8* from, Color_RGB8* to, f32 lerp, Vec3s* dst) {
    Color_RGB8 result;

    Color_RGB8_Lerp(from, to, lerp, &result);

    dst->x = result.r - from->r;
    dst->y = result.g - from->g;
    dst->z = result.b - from->b;
}

void Environment_LerpAmbientColor(PlayState* play, Color_RGB8* to, f32 lerp) {
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.lightSettings.ambientColor, to, lerp,
                         (Vec3s*)&play->envCtx.adjLightSettings.ambientColor);
}

void Environment_LerpDiffuseColor(PlayState* play, Color_RGB8* to, f32 lerp) {
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.lightSettings.diffuseColor1, to, lerp,
                         (Vec3s*)play->envCtx.adjLightSettings.diffuseColor1);
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.lightSettings.diffuseColor, to, lerp,
                         (Vec3s*)play->envCtx.adjLightSettings.diffuseColor2);
}

void Environment_LerpFogColor(PlayState* play, Color_RGB8* to, f32 lerp) {
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.lightSettings.fogColor, to, lerp,
                         (Vec3s*)play->envCtx.adjLightSettings.fogColor);
}

void Environment_LerpFog(PlayState* play, s16 fogNearTarget, s16 fogFarTarget, f32 lerp) {
    play->envCtx.adjLightSettings.fogNear = (fogNearTarget - (s16)play->envCtx.lightSettings.fogNear) * lerp;
    play->envCtx.adjLightSettings.zFar = (fogFarTarget - (s16)play->envCtx.lightSettings.zFar) * lerp;
}

// Repurposed from OoT to be more general
u32 Environment_GetBgsDayCount(void) {
    return gSaveContext.save.daysElapsed;
}

// Repurposed from OoT to be more general
void Environment_ClearBgsDayCount(void) {
    gSaveContext.save.daysElapsed = 0;
}

// Repurposed from OoT to be more general
u32 Environment_GetTotalDays(void) {
    return gSaveContext.save.day;
}

void Environment_ForcePlaySequence(u16 seqId) {
    gSaveContext.forcedSeqId = seqId;
}

s32 Environment_IsForcedSequenceDisabled(void) {
    s32 isDisabled = false;

    if (gSaveContext.forcedSeqId != NA_BGM_GENERAL_SFX) {
        isDisabled = true;
    }

    return isDisabled;
}

void Environment_PlayStormNatureAmbience(PlayState* play) {
    if (((play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) && (play->sequenceCtx.ambienceId == AMBIENCE_ID_13)) ||
        (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) == NA_BGM_FINAL_HOURS)) {
        Audio_PlayAmbience(AMBIENCE_ID_07);
    } else if ((play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) && (play->sequenceCtx.ambienceId != AMBIENCE_ID_13)) {
        if ((((void)0, gSaveContext.save.time) >= CLOCK_TIME(6, 0)) &&
            (((void)0, gSaveContext.save.time) < CLOCK_TIME(18, 0))) {
            Audio_PlayAmbience(play->sequenceCtx.ambienceId);
        }
    }

    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_RAIN, CHANNEL_IO_PORT_1, 1);
    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_1, 1);
}

void Environment_StopStormNatureAmbience(PlayState* play) {
    if (((play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) && (play->sequenceCtx.ambienceId == AMBIENCE_ID_13)) ||
        (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) == NA_BGM_FINAL_HOURS)) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_AMBIENCE, 20);
    } else if ((play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) && (play->sequenceCtx.ambienceId != AMBIENCE_ID_13)) {
        if ((((void)0, gSaveContext.save.time) >= CLOCK_TIME(6, 0)) &&
            (((void)0, gSaveContext.save.time) < CLOCK_TIME(18, 0))) {
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_AMBIENCE, 20);
        }
    }

    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_RAIN, CHANNEL_IO_PORT_1, 0);
    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_1, 0);
}

void Environment_WarpSongLeave(PlayState* play) {
    gWeatherMode = WEATHER_MODE_CLEAR;
    gSaveContext.save.cutsceneIndex = 0;
    gSaveContext.respawnFlag = -3;
    play->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_RETURN].entrance;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_FADE_WHITE;
    gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE;
}

void Environment_SetupSkyboxStars(PlayState* play) {
    f32 phi_f0;

    if ((play->envCtx.skybox1Index == 0) && (play->skyboxId == SKYBOX_NORMAL_SKY)) {
        if ((((void)0, gSaveContext.save.time) >= CLOCK_TIME(21, 0)) ||
            (((void)0, gSaveContext.save.time) < CLOCK_TIME(2, 0))) {
            phi_f0 = 1.0f;
        } else if (((void)0, gSaveContext.save.time) > CLOCK_TIME(19, 0)) {
            phi_f0 = 1.0f - ((CLOCK_TIME(21, 0) - ((void)0, gSaveContext.save.time)) * (1.0f / (CLOCK_TIME(2, 0) + 1)));
        } else if (((void)0, gSaveContext.save.time) < CLOCK_TIME(3, 0)) {
            phi_f0 = (CLOCK_TIME(3, 0) - ((void)0, gSaveContext.save.time)) * (1.0f / (CLOCK_TIME(1, 0) + 1));
        } else {
            phi_f0 = 0.0f;
        }

        phi_f0 = (play->envCtx.skyboxConfig == 0x18) ? 1.0f : phi_f0;

        D_801F4F28 = phi_f0;
        sEnvSkyboxNumStars = gSkyboxNumStars;
    } else {
        D_801F4F28 = 0.0f;
        sEnvSkyboxNumStars = 0;
    }

    if ((sEnvSkyboxNumStars != 0) && (D_801F4F28 != 0.0f)) {
        OPEN_DISPS(play->state.gfxCtx);

        sSkyboxStarsDList = POLY_OPA_DISP;

        gSPNoOp(POLY_OPA_DISP++);

        CLOSE_DISPS(play->state.gfxCtx);
    } else {
        sSkyboxStarsDList = NULL;
    }
}

void Environment_DrawSkyboxStar(Gfx** gfxp, f32 x, f32 y, s32 width, s32 height) {
    Gfx* gfx = *gfxp;
    u32 xl = x * 4.0f;
    u32 yl = y * 4.0f;
    u32 xd = width;
    u32 yd = height;

    gSPTextureRectangle(gfx++, xl, yl, xl + xd, yl + yd, 0, 0, 0, 0, 0);

    *gfxp = gfx;
}

extern Vec3s D_801DD880[16];
extern u32 D_801DD8E0[8];
extern u32 D_801DD900[16];

// Vec3s D_801DD880[] = {
//     { 0x0384, 0x2328, 0xD508 }, { 0x09C4, 0x2328, 0xDA1C }, { 0x0E74, 0x22D8, 0xDA1C }, { 0x1450, 0x2468, 0xD8F0 },
//     { 0x1C84, 0x28A0, 0xCBA8 }, { 0x1F40, 0x2134, 0xD8F0 }, { 0x1F40, 0x28A0, 0xDAE4 }, { 0xE4A8, 0x4A38, 0x4A38 },
//     { 0xD058, 0x4C2C, 0x3A98 }, { 0xD8F0, 0x36B0, 0x47E0 }, { 0xD954, 0x3264, 0x3E1C }, { 0xD8F0, 0x3070, 0x37DC },
//     { 0xD8F0, 0x1F40, 0x5208 }, { 0xD760, 0x1838, 0x27D8 }, { 0x0000, 0x4E20, 0x4A38 }, { 0x076C, 0x2328, 0xDCD8 },
// };
// u32 D_801DD8E0[] = {
//     0x41A4FFFF, 0x83A4E6FF, 0x62CDFFFF, 0x5252FFFF, 0x7BA4A4FF, 0x62CDFFFF, 0x62A4E6FF, 0xFF5A00FF,
// };
// u32 D_801DD900[] = {
//     0x405070FF, 0x606080FF, 0x807090FF, 0xA080A0FF, 0xC090A8FF, 0xE0A0B0FF, 0xE0A0B0FF, 0x686888FF,
//     0x887898FF, 0xA888A8FF, 0xC898B8FF, 0xE8A8B8FF, 0xE0B0B8FF, 0xF0C0C0FF, 0xE8B8C0FF, 0xF8C8C0FF,
// };

#ifdef NON_EQUIVALENT
void Environment_DrawSkyboxStarsImpl(PlayState* play, Gfx** gfxP) {
    Vec3f pos;
    f32 imgY;
    f32 imgX;
    s32 negateY;
    Gfx* gfx;
    Gfx* gfxTemp;
    MtxF* viewProjectionMtxF;
    f32 invScale;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    f32 scale;
    f32 temp_f4;
    s32 i;
    u32 randInt;
    s32 phi_v1; // spE8
    u32 imgWidth;
    f32* imgXPtr;
    f32* imgYPtr;
    s32 pad[4];

    gfx = *gfxP;
    viewProjectionMtxF = &play->viewProjectionMtxF;

    //! FAKE:
    if (1) {}
    if (1) {}

    negateY = Environment_IsSceneUpsideDown(play);

    Matrix_MtxToMtxF(play->view.viewingPtr, &play->billboardMtxF);
    Matrix_MtxToMtxF(&play->view.projection, viewProjectionMtxF);
    SkinMatrix_MtxFMtxFMult(viewProjectionMtxF, &play->billboardMtxF, viewProjectionMtxF);

    phi_v1 = 0;

    gDPPipeSync(gfx++);
    gDPSetEnvColor(gfx++, 255, 255, 255, 255 * D_801F4F28);
    gDPSetCombineLERP(gfx++, PRIMITIVE, 0, ENVIRONMENT, 0, PRIMITIVE, 0, ENVIRONMENT, 0, PRIMITIVE, 0, ENVIRONMENT, 0,
                      PRIMITIVE, 0, ENVIRONMENT, 0);
    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_AA_XLU_LINE | G_RM_AA_XLU_LINE2);

    randInt = ((gSaveContext.save.saveInfo.playerData.playerName[7]) << 0x1C);
    randInt ^= ((gSaveContext.save.saveInfo.playerData.playerName[0]) << 0x18);
    randInt ^= ((gSaveContext.save.saveInfo.playerData.playerName[1]) << 0x14);
    randInt ^= ((gSaveContext.save.saveInfo.playerData.playerName[2]) << 0x10);
    randInt ^= (0, (gSaveContext.save.saveInfo.playerData.playerName[3]) << 0xC); //! FAKE:
    randInt ^= ((gSaveContext.save.saveInfo.playerData.playerName[4]) << 8);
    randInt ^= ((gSaveContext.save.saveInfo.playerData.playerName[5]) << 4);
    randInt ^= ((gSaveContext.save.saveInfo.playerData.playerName[6]) << 0);
    randInt ^= ((gSaveContext.save.saveInfo.playerData.playerName[7]) >> 4);

    // randInt = ((gSaveContext.save.saveInfo.playerData.playerName[7]) << 0x1C) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[0]) << 0x18) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[1]) << 0x14) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[2]) << 0x10) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[3]) << 0xC) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[4]) << 8) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[5]) << 4) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[6]) << 0) ^
    //           ((gSaveContext.save.saveInfo.playerData.playerName[7]) >> 4);

    //! FAKE:
    if (&gSaveContext && &gSaveContext && &gSaveContext) {}

    for (i = 0; i < sEnvSkyboxNumStars; i++) {
        if (i < 16) {
            pos.x = play->view.eye.x + D_801DD880[i].x;
            pos.y = play->view.eye.y + D_801DD880[i].y;
            pos.z = play->view.eye.z + D_801DD880[i].z;
            imgWidth = 8;
        } else {
            // temp_f4 = Rand_ZeroOne_Variable(&randInt);
            randInt = (randInt * 1664525) + 1013904223;
            sRandFloat = (randInt >> 9) | 0x3F800000;
            temp_f4 = *((f32*)&sRandFloat) - 1; //! FAKE:

            // temp_f20 = Rand_ZeroOne_Variable(&randInt);
            randInt = (randInt * 1664525) + 1013904223;
            sRandFloat = (randInt >> 9) | 0x3F800000;
            temp_f20 = *((f32*)&sRandFloat) - 1.0f;

            // average
            temp_f20 = (temp_f20 + temp_f4) * 0.5f;

            // randInt = Rand_Next_Variable(&randInt);
            randInt = (randInt * 1664525) + 1013904223;

            // Set random position
            pos.y = play->view.eye.y + (SQ(temp_f20) * SQ(128.0f)) - 1000.0f;
            pos.x = play->view.eye.x + (Math_SinS(randInt) * (1.2f - temp_f20) * SQ(128.0f));
            pos.z = play->view.eye.z + (Math_CosS(randInt) * (1.2f - temp_f20) * SQ(128.0f));

            // temp_f2 = Rand_ZeroOne_Variable(&randInt);
            randInt = (randInt * 1664525) + 1013904223;
            sRandFloat = ((randInt >> 9) | 0x3F800000);
            temp_f2 = *((f32*)&sRandFloat) - 1.0f;

            // Set random width
            imgWidth = (u32)((SQ(temp_f2) * 8.0f) + 2.0f);
        }

        if (negateY) {
            pos.y = -pos.y;
        }

        if ((i < 15) || ((i == 15) && ((((void)0, gSaveContext.save.day) % 7) == 0))) {
            gDPSetColor(gfx++, G_SETPRIMCOLOR, D_801DD8E0[i & 7]);
        } else if (((i & 0x3F) == 0) || (i == 16)) {
            gDPSetColor(gfx++, G_SETPRIMCOLOR, D_801DD900[phi_v1 & 0xF]);
            phi_v1++;
        }

        //! FAKE:
        if ((&pos && &pos && &pos) != 0) {}
        imgXPtr = &imgX;
        imgYPtr = &imgY;

        if (imgWidth >= 2) {
            // w component
            scale = pos.x * play->viewProjectionMtxF.mf[0][3] + pos.y * play->viewProjectionMtxF.mf[1][3] +
                    pos.z * play->viewProjectionMtxF.mf[2][3] + play->viewProjectionMtxF.mf[3][3];
            if (scale >= 1.0f) {
                invScale = 1.0f / scale;
                // x component
                imgX = (pos.x * viewProjectionMtxF->mf[0][0] + pos.y * viewProjectionMtxF->mf[1][0] +
                        pos.z * viewProjectionMtxF->mf[2][0] + viewProjectionMtxF->mf[3][0]) *
                       invScale;
                // y component
                imgY = (((pos.x * viewProjectionMtxF->mf[0][1]) + (pos.y * viewProjectionMtxF->mf[1][1]) +
                         (pos.z * viewProjectionMtxF->mf[2][1])) +
                        viewProjectionMtxF->mf[3][1]) *
                       invScale;
            }

            if ((scale >= 1.0f) && (imgX > -1.0f) && (imgX < 1.0f) && (imgY > -1.0f) && (imgY < 1.0f)) {
                imgX = (imgX * (SCREEN_WIDTH / 2)) + (SCREEN_WIDTH / 2);
                imgY = (imgY * -(SCREEN_HEIGHT / 2)) + (SCREEN_HEIGHT / 2);

                gfxTemp = gfx;
                Environment_DrawSkyboxStar(&gfxTemp, imgX, imgY, imgWidth, 4);
                gfx = gfxTemp;
            }
        }
    }

    gDPPipeSync(gfx++);
    *gfxP = gfx;
}
#else
void Environment_DrawSkyboxStarsImpl(PlayState* play, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSkyboxStarsImpl.s")
#endif

void Environment_Draw(PlayState* play) {
    Environment_SetupSkyboxStars(play);
    Environment_DrawSun(play);
    Environment_UpdateLightningStrike(play);
    Environment_DrawLightning(play, 0);
    Environment_DrawSkyboxFilters(play);
}

void Environment_DrawSkyboxStars(PlayState* play) {
    Gfx* nextOpa;
    Gfx* opa;

    if (sSkyboxStarsDList != NULL) {
        OPEN_DISPS(play->state.gfxCtx);

        opa = POLY_OPA_DISP;
        nextOpa = Graph_GfxPlusOne(opa);

        gSPDisplayList(sSkyboxStarsDList, nextOpa);

        Environment_DrawSkyboxStarsImpl(play, &nextOpa);

        gSPEndDisplayList(nextOpa++);

        Graph_BranchDlist(opa, nextOpa);

        POLY_OPA_DISP = nextOpa;
        sSkyboxStarsDList = NULL;

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void Environment_StopTime(void) {
    sEnvIsTimeStopped = true;
}

void Environment_StartTime(void) {
    sEnvIsTimeStopped = false;
}

u8 Environment_IsTimeStopped(void) {
    return sEnvIsTimeStopped;
}

u32 Environment_GetStormState(PlayState* play) {
    u32 stormState = play->envCtx.stormState;

    if ((play->sceneId == SCENE_OMOYA) && (play->roomCtx.curRoom.num == 0)) {
        stormState = ((gSaveContext.save.day >= 2) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM))
                         ? STORM_STATE_ON
                         : STORM_STATE_OFF;
    }

    switch (play->sceneId) {
        case SCENE_13HUBUKINOMITI:
        case SCENE_11GORONNOSATO:
        case SCENE_10YUKIYAMANOMURA:
        case SCENE_14YUKIDAMANOMITI:
        case SCENE_12HAKUGINMAE:
        case SCENE_17SETUGEN:
        case SCENE_GORONRACE:
            if (gSaveContext.sceneLayer == 0) {
                stormState = STORM_STATE_OFF;
            }
            break;

        case SCENE_10YUKIYAMANOMURA2:
            if (gSaveContext.sceneLayer == 1) {
                stormState = STORM_STATE_OFF;
            }
            break;

        default:
            break;
    }

    return stormState;
}

u8 Environment_IsFinalHours(PlayState* play) {
    u8 ret = false;

    if ((gSaveContext.save.day == 3) && (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
        ret = true;
    }

    return ret;
}

u8 func_800FE5D0(PlayState* play) {
    u8 ret = false;

    if (Entrance_GetSceneId(((void)0, gSaveContext.save.entrance)) < 0) {
        ret = true;
    }

    return ret;
}

u32 func_800FE610(PlayState* play) {
    return 0;
}

u16 Environment_GetTimeSpeed(PlayState* play) {
    u16 timeSpeed = 0;

    if (R_TIME_SPEED != 0) {
        timeSpeed = R_TIME_SPEED + (u16)((void)0, gSaveContext.save.timeSpeedOffset);
    }

    return timeSpeed;
}

void Environment_SetTimeJump(f32 minutes) {
    sTimeJump = CLOCK_TIME_F(0, minutes);
}

u8 func_800FE6F8(PlayState* play, s16 timeAdvanceScaling, s16 nextTimeLimit) {
    u16 nextTime;
    u8 ret = false;

    if (R_TIME_SPEED != 0) {
        nextTime = ((void)0, gSaveContext.save.time) +
                   (R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset)) * timeAdvanceScaling * 20;
        if (nextTime > nextTimeLimit) {
            ret = true;
        }
    }

    return ret;
}

u8 Environment_GetSandstormColorIndex(void) {
    return sSandstormColorIndex;
}

u8 Environment_GetNextSandstormColorIndex(void) {
    return sNextSandstormColorIndex;
}

f32 Environment_GetSandstormLerpScale(void) {
    return sSandstormLerpScale;
}

void Environment_LerpSandstormColors(Color_RGBA8* colorSrc, Color_RGBA8* colorDst) {
    f32 sandstormLerpScale = Environment_GetSandstormLerpScale();
    s32 pad;
    u32 sandstormColorIndex = Environment_GetSandstormColorIndex();
    u32 nextSandstormColorIndex = Environment_GetNextSandstormColorIndex();

    if (sandstormLerpScale <= 0.0f) {
        colorDst->r = colorSrc[sandstormColorIndex].r;
        colorDst->g = colorSrc[sandstormColorIndex].g;
        colorDst->b = colorSrc[sandstormColorIndex].b;
        colorDst->a = colorSrc[sandstormColorIndex].a;
    } else {
        colorDst->r =
            (s32)F32_LERP(colorSrc[sandstormColorIndex].r, colorSrc[nextSandstormColorIndex].r, sandstormLerpScale);
        colorDst->g =
            (s32)F32_LERP(colorSrc[sandstormColorIndex].g, colorSrc[nextSandstormColorIndex].g, sandstormLerpScale);
        colorDst->b =
            (s32)F32_LERP(colorSrc[sandstormColorIndex].b, colorSrc[nextSandstormColorIndex].b, sandstormLerpScale);
        colorDst->a =
            (s32)F32_LERP(colorSrc[sandstormColorIndex].a, colorSrc[nextSandstormColorIndex].a, sandstormLerpScale);
    }
}

u8 func_800FE9B4(PlayState* play) {
    u8 ret;

    ret = false;
    if ((play->envCtx.precipitation[PRECIP_SOS_MAX] == 60) && (play->envCtx.precipitation[PRECIP_SNOW_CUR] == 0)) {
        ret = true;
    }

    if ((play->envCtx.precipitation[PRECIP_RAIN_MAX] == 60) &&
        !(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER)) {
        if ((Environment_GetStormState(play) != STORM_STATE_OFF) &&
            (play->envCtx.precipitation[PRECIP_SNOW_CUR] == 0)) {
            ret = true;
        }
    }

    return ret;
}

void func_800FEA50(PlayState* play) {
    s8 phi_v0;

    switch (gSaveContext.save.day) {
        default:
        case 0:
        case 1:
            phi_v0 = 0;
            break;

        case 2:
            phi_v0 = 3;
            break;

        case 3:
            phi_v0 = 4;
            break;
    }

    D_801F4F30 = phi_v0;
    D_801F4F33 = true;
}

void func_800FEAB0() {
    D_801F4F33 = false;
}

void Environment_JumpForwardInTime(void) {
    if (sTimeJump != 0) {
        gSaveContext.save.time = ((void)0, gSaveContext.save.time) + sTimeJump;
        sTimeJump = 0;
    }
}

void func_800FEAF4(EnvironmentContext *envCtx) {
    u8 phi_v1;

    phi_v1 = 0;
    if (((void)0, gSaveContext.save.day) != 0) {
        phi_v1 = ((void)0, gSaveContext.save.day) - 1;
    }
     envCtx->skyboxConfig = phi_v1 + (D_801F4E31 * 3);
     envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;

    if (D_801F4E31 == 4) {
        envCtx->skyboxConfig = 0xE;
        envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;
    } else if (D_801F4E31 == 5) {
        envCtx->skyboxConfig = 0x10;
        envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;
    } else if (D_801F4E31 == 6) {
        envCtx->skyboxConfig = 0x11;
        envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;
    } else if (D_801F4E31 == 7) {
        envCtx->skyboxConfig = phi_v1 + 0x12;
        envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;
    } else if (D_801F4E31 == 8) {
        envCtx->skyboxConfig = phi_v1 + 0x15;
        envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;
    } else if (D_801F4E31 == 9) {
        envCtx->skyboxConfig = 0x18;
        envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;
    } else if (D_801F4E31 == 0xA) {
        envCtx->skyboxConfig = phi_v1 + 0x19;
        envCtx->changeSkyboxNextConfig = envCtx->skyboxConfig;
    }

    if (phi_v1 >= 3) {
        envCtx->skyboxConfig = 0xD;
        envCtx->changeSkyboxNextConfig = 0xD;
    }

    if (envCtx->skyboxConfig >= 0x1C) {
        envCtx->skyboxConfig = 0;
        envCtx->changeSkyboxNextConfig = 0;
    }

    switch (((void)0, gSaveContext.save.day)) {
        default:
        case 0:
        case 1:
            envCtx->lightConfig = 0;
            envCtx->changeLightNextConfig = 0;
            break;

        case 2:
            envCtx->lightConfig = 3;
            envCtx->changeLightNextConfig = 3;
            break;

        case 3:
            envCtx->lightConfig = 4;
            envCtx->changeLightNextConfig = 4;
            break;
    }

    return;
}