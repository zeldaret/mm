#include "global.h"
#include "z64environment.h"
#include "z64save.h"
#include "z64skybox.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Init.s")

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
    } else if (play->envCtx.lightSettingOverride == 0xFF) {
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
        play->envCtx.lightSettingOverride = 0xFF;
        play->envCtx.lightBlend = 1.0f;
    }
}

void func_800F6A04(void) {
    if ((gSaveContext.gameMode != GAMEMODE_NORMAL) && (gSaveContext.gameMode != GAMEMODE_END_CREDITS)) {
        Rumble_StateWipeRequests();
    }
}

void func_800F6A40(PlayState* play) {
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->pauseCtx.debugEditor == DEBUG_EDITOR_NONE) &&
        ((play->skyboxId == SKYBOX_NORMAL_SKY) || (play->skyboxId == SKYBOX_3))) {
        play->skyboxCtx.rot.y -= R_TIME_SPEED * 1.0e-4f;
    }
}

void func_800F6AB8(void) {
    if ((gSaveContext.nextDayTime >= 0xFF00) && (gSaveContext.nextDayTime != 0xFFFF)) {
        gSaveContext.nextDayTime -= 0x10;
        if (gSaveContext.nextDayTime == 0xFF0E) {
            play_sound(0x2813); // TODO document sound name
            gSaveContext.nextDayTime = 0xFFFF;
        } else if (gSaveContext.nextDayTime == 0xFF0D) {
            func_8019F128(0x28AE); // TODO document sound name
            gSaveContext.nextDayTime = 0xFFFF;
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F6CEC.s")

// TODO permuter - regalloc issues
/*
void func_800F6CEC(PlayState* arg0, u8 arg1, EnvLightSettings* arg2, LightSettings* arg3) {
    s32 phi_t1;
    s32 temp_v1_2;
    s32 temp_v1;

    if ((((void)0, gSaveContext.day) >= 2) && (arg1 >= 4) && (arg1 < 8)) {
        temp_v1 = (arg1 % 4);
        temp_v1_2 = (((void)0, gSaveContext.day) * 4) + 4;
        for (phi_t1 = 0; phi_t1 != 3; phi_t1++) {
            arg2->ambientColor[phi_t1] = arg3[temp_v1_2 + temp_v1].ambientColor[phi_t1] -
arg3[temp_v1].ambientColor[phi_t1]; arg2->diffuseColor1[phi_t1] = arg3[temp_v1_2 + temp_v1].diffuseColor1[phi_t1] -
arg3[temp_v1].diffuseColor1[phi_t1]; arg2->diffuseColor2[phi_t1] = arg3[temp_v1_2 + temp_v1].diffuseColor[phi_t1] -
arg3[temp_v1].diffuseColor[phi_t1]; // TODO rename to diffuseColor2 arg2->fogColor[phi_t1] = arg3[temp_v1_2 +
temp_v1].fogColor[phi_t1] - arg3[temp_v1].fogColor[phi_t1];
        }
        arg2->fogNear = arg3[temp_v1_2 + temp_v1].fogNear - arg3[temp_v1].fogNear;
    }

    if ((arg1 >= 4) && (arg1 < 8) && (D_801BDBB0 == 1)) {
        arg2->ambientColor[0] = -50;
        arg2->ambientColor[1] = -100;
        arg2->ambientColor[2] = -100;
        arg2->diffuseColor1[0] = -100;
        arg2->diffuseColor1[1] = -100;
        arg2->diffuseColor1[2] = -100;
        arg2->diffuseColor2[0] = -100;
        arg2->diffuseColor2[1] = -100;
        arg2->diffuseColor2[2] = -100;
        arg2->fogColor[0] = -arg3[arg1].fogColor[0] + 30;
        arg2->fogColor[1] = -arg3[arg1].fogColor[1] + 30;
        arg2->fogColor[2] = -arg3[arg1].fogColor[2] + 45;
    }
}
*/

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F6FF8.s")

void func_800F8554(PlayState* play) {
    f32 temp_f0;
    s16 temp_a0;
    u16 phi_v0;

    if (!play->envCtx.sunMoonDisabled) {
        if (play->envCtx.precipitation[1] != 0) {
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

void func_800F88C4(u16 arg0) {
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_08) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_28_10) &&
        CHECK_WEEKEVENTREG(arg0)) {
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
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_27_40) && ((gSaveContext.save.time - 0x3FFC) >= 0x2580)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_27_40);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_UPPER_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_27_80) && ((gSaveContext.save.time - 0x3FFC) >= 0x2B30)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_27_80);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_NORTH_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_01) && ((gSaveContext.save.time - 0x3FFC) >= 0x30E0)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_28_01);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_UPPER_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_02) && ((gSaveContext.save.time - 0x3FFC) >= 0x3413)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_28_02);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_EAST_LOWER_CLOCKTOWN);
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_04) && ((gSaveContext.save.time - 0x3FFC) >= 0x39C3)) {
        SET_WEEKEVENTREG(WEEKEVENTREG_28_04);
        func_800F88C4(WEEKEVENTREG_DEPOSITED_LETTER_TO_KAFEI_SOUTH_LOWER_CLOCKTOWN);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F8A9C.s")

// TODO permuter - regalloc issues, minor reordering
/*
void func_800F8A9C(s32 arg0) {
    u8 temp_a1;
    u8 v1;
    u16 temp_a2_2;

    temp_a1 = (gSaveContext.eventInf[7] & 0xE0) >> 5;

    if (temp_a1 != (u8)((void)0, gSaveContext.day)) {
        v1 = gSaveContext.eventInf[7] & 0x1F;
        v1 |= ((void)0, gSaveContext.day) << 5;
        gSaveContext.eventInf[7] = v1;

        gSaveContext.weekEventReg[27] |= 0x40;
        gSaveContext.weekEventReg[27] |= 0x80;
        gSaveContext.weekEventReg[28] |= 1;
        gSaveContext.weekEventReg[28] |= 2;
        gSaveContext.weekEventReg[28] |= 4;

        func_800F88C4(0x1B02);
        func_800F88C4(0x1B04);
        func_800F88C4(0x1B08);
        func_800F88C4(0x1B10);
        func_800F88C4(0x1B20);

        gSaveContext.weekEventReg[27] &= (u8)~0x40;
        gSaveContext.weekEventReg[27] &= (u8)~0x80;
        gSaveContext.weekEventReg[28] &= (u8)~1;
        gSaveContext.weekEventReg[28] &= (u8)~2;
        gSaveContext.weekEventReg[28] &= (u8)~4;
    }

    if (((((void)0, gSaveContext.time) - 0x3FFC) < 0x1FFE) || ((((void)0, gSaveContext.time) - 0x3FFC) >= 0x3FFD)) {
        gSaveContext.weekEventReg[90] &= (u8)~8;
    }

    func_800F8970();

    if (((gSaveContext.weekEventReg[75] & 0x10) == 0) && ((gSaveContext.weekEventReg[55] & 2) == 0)) {
        if (((void)0, gSaveContext.day) >= 2) {
            gSaveContext.weekEventReg[55] |= 2;
        } else if ((((void)0, gSaveContext.day) == 1) && ((((void)0, gSaveContext.time) - 0x3FFC) >= 0x6FF9)) {
            gSaveContext.weekEventReg[55] |= 2;
        }
    }

    if ((gSaveContext.weekEventReg[90] & 1) == 0) {
        temp_a2_2 = ((void)0, gSaveContext.time) - D_801F4E78;

        if (((gSaveContext.weekEventReg[89] & 0x40) != 0) && (((((void)0, gSaveContext.time) - 0x3FFC) & 0xFFFF) >=
0xF556)) { gSaveContext.weekEventReg[90] |= 1; } else if (((gSaveContext.weekEventReg[89] & 8) != 0) && (temp_a2_2 >=
0x416)) { gSaveContext.weekEventReg[89] |= 0x40; D_801F4E78 = 0; } else if (((gSaveContext.weekEventReg[85] & 0x80) !=
0) && (temp_a2_2 >= 0x1198)) { gSaveContext.weekEventReg[89] |= 8; D_801F4E78 = gSaveContext.time; } else if
(((gSaveContext.weekEventReg[86] & 1) != 0) && (temp_a2_2 >= 0xC43)) { gSaveContext.weekEventReg[85] |= 0x80;
        }
    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Update.s")

void Environment_UpdateRain(PlayState*);
void func_800F8A9C(PlayState*);
void Environment_UpdateTimeBasedSequence(PlayState*);

void Environment_Update(PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx, PauseContext* pauseCtx,
                        MessageContext* msgCtx, GameOverContext* gameOverCtx, GraphicsContext* gfxCtx) {
    D_801BDBC0 = 0;
    D_801BDBC4 = 0;

    func_800F6A04();

    if (pauseCtx->state == PAUSE_STATE_OFF) {
        func_800F6A40(play);
        Environment_UpdateRain(play);
        Environment_UpdateTimeBasedSequence(play);
        func_800F6AB8();
        Environment_UpdateTime(play, envCtx, pauseCtx, msgCtx, gameOverCtx);
        func_800F8554(play);
        func_800F6FF8(play, envCtx, lightCtx);
        func_800F8A9C(play);
    }
}

extern Gfx* D_0407AB70; // gSunDL

void Environment_DrawSun(PlayState* play) {
    if (!play->envCtx.sunMoonDisabled) {
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
            Matrix_Scale(sSunScale, sSunScale, sSunScale, 1);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_LOAD);
            Gfx_SetupDL54_Opa(play->state.gfxCtx);
            gSPDisplayList(POLY_OPA_DISP++, &D_0407AB70);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void Environment_DrawSunLensFlare(PlayState* play, EnvironmentContext* envCtx, View* view, GraphicsContext* gfxCtx,
                                  Vec3f vec) {
    if ((play->envCtx.precipitation[1] == 0) && !(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER) &&
        (play->skyboxId == SKYBOX_NORMAL_SKY)) {
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
    if (!(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER) && (play->envCtx.precipitation[2] == 0)) {
        if (play->envCtx.precipitation[4] != 0) {
            if (play->envCtx.precipitation[2] == 0) {
                Environment_DrawRainImpl(play, view, gfxCtx);
            }
        } else if (!(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER)) {
            if ((func_800FE4B8(play) != 0) && (play->envCtx.precipitation[2] == 0)) {
                Environment_DrawRainImpl(play, view, gfxCtx);
            }
        }
    }
}

void Environment_ChangeLightSetting(PlayState* play, u8 lightConfig) {
    if (play->envCtx.lightMode == LIGHT_MODE_TIME) {
        if ((lightConfig == 31) || D_801F4F33) {
            if (D_801F4F30 != 0xFF) {
                play->envCtx.changeLightEnabled = true;
                play->envCtx.changeLightNextConfig = D_801F4F30;
                play->envCtx.changeDuration = 20;
                play->envCtx.changeLightTimer = play->envCtx.changeDuration;
                D_801F4F30 = 0xFF;
            }
        } else if (play->envCtx.changeLightNextConfig != lightConfig) {
            D_801F4F30 = play->envCtx.lightConfig;
            play->envCtx.changeLightEnabled = true;
            play->envCtx.changeLightNextConfig = lightConfig;
            play->envCtx.changeDuration = 20;
            play->envCtx.changeLightTimer = play->envCtx.changeDuration;
        }
    } else if ((play->envCtx.lightSetting != lightConfig) && (play->envCtx.lightBlend >= 1.0f) &&
               (play->envCtx.lightSettingOverride == 0xFF)) {
        if (lightConfig > 30) {
            lightConfig = 0;
        }

        play->envCtx.lightBlend = 0.0f;
        play->envCtx.prevLightSetting = play->envCtx.lightSetting;
        play->envCtx.lightSetting = lightConfig;
    }
}

void Environment_DrawSkyboxFilters(PlayState* play) {
    if ((((play->skyboxId != SKYBOX_NONE) && (play->lightCtx.fogNear < 980)) || (play->skyboxId >= SKYBOX_2)) &&
        ((play->skyboxId != SKYBOX_3) || (D_801F4E74 != 0.0f))) {
        f32 alpha;

        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL57_Opa(play->state.gfxCtx);

        alpha = (1000 - play->lightCtx.fogNear) * 0.02f;

        if (play->skyboxId == 2) {
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
    if (play->envCtx.unk_E3 != LIGHTNING_MODE_OFF) {
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

                play->envCtx.lightSettings.ambientColor[0] += 80;
                play->envCtx.lightSettings.ambientColor[1] += 80;
                play->envCtx.lightSettings.ambientColor[2] += 100;

                sLightningFlashAlpha += 100;

                if (sLightningFlashAlpha >= gLightningStrike.flashAlphaTarget) {
                    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_0, 0);
                    gLightningStrike.state++;
                    gLightningStrike.flashAlphaTarget = 0;
                }
                break;

            case LIGHTNING_STRIKE_END:
                if (play->envCtx.lightSettings.ambientColor[0] > 0) {
                    play->envCtx.lightSettings.ambientColor[0] -= 10;
                    play->envCtx.lightSettings.ambientColor[1] -= 10;
                }

                if (play->envCtx.lightSettings.ambientColor[2] > 0) {
                    play->envCtx.lightSettings.ambientColor[2] -= 10;
                }

                sLightningFlashAlpha -= 10;

                if (sLightningFlashAlpha <= gLightningStrike.flashAlphaTarget) {
                    play->envCtx.lightSettings.ambientColor[0] = 0;
                    play->envCtx.lightSettings.ambientColor[1] = 0;
                    play->envCtx.lightSettings.ambientColor[2] = 0;

                    gLightningStrike.state = LIGHTNING_STRIKE_WAIT;

                    if (play->envCtx.unk_E3 == LIGHTNING_MODE_LAST) {
                        play->envCtx.unk_E3 = LIGHTNING_MODE_OFF;
                    }
                }
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

extern Gfx D_0403F230[];
extern void* sLightningTextures[8]; // TODO static

/**
 * Draw any active lightning bolt entries contained in `sLightningBolts`
 */
void Environment_DrawLightning(PlayState* play, s32 unused) {
    // TODO
    // static void* sLightningTextures[] = {
    // gEffLightning1Tex, gEffLightning2Tex, gEffLightning3Tex,
    // gEffLightning4Tex, gEffLightning5Tex, gEffLightning6Tex,
    // gEffLightning7Tex, gEffLightning8Tex, NULL,
    // };
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
            gSPDisplayList(POLY_XLU_DISP++, D_0403F230);
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
                if (play->envCtx.precipitation[1] < 9) {
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

    if ((play->envCtx.timeSeqState != 0xFE) && (((void)0, gSaveContext.save.day) == 3) &&
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

void Kankyo_InitGameOverLights(PlayState* play) {
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
            if (play->envCtx.lightSettings.ambientColor[i] > -255) {
                play->envCtx.lightSettings.ambientColor[i] -= 12;
                play->envCtx.lightSettings.diffuseColor1[i] -= 12;
            }
            play->envCtx.lightSettings.fogColor[i] = -255;
        }

        if (play->envCtx.unk_C4.zFar + play->envCtx.lightSettings.zFar > 900) {
            play->envCtx.lightSettings.zFar -= 100;
        }

        if (play->envCtx.unk_C4.fogNear + play->envCtx.lightSettings.fogNear > 950) {
            play->envCtx.lightSettings.fogNear -= 10;
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
            Math_SmoothStepToS(&play->envCtx.lightSettings.ambientColor[i], 0, 5, 12, 1);
            Math_SmoothStepToS(&play->envCtx.lightSettings.diffuseColor1[i], 0, 5, 12, 1);
            play->envCtx.lightSettings.fogColor[i] = 0;
        }
        play->envCtx.lightSettings.zFar = 0;
        play->envCtx.lightSettings.fogNear = 0;
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
    u8 max = MAX(play->envCtx.precipitation[0], play->envCtx.precipitation[4]);

    if ((play->envCtx.precipitation[1] != max) && ((play->state.frames % 8) == 0)) {
        if (play->envCtx.precipitation[1] < max) {
            play->envCtx.precipitation[1] += 2;
        } else {
            play->envCtx.precipitation[1] -= 2;
        }
    }
}

#define FILL_SCREEN_OPA (1 << 0)
#define FILL_SCREEN_XLU (1 << 1)

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSandstorm.s")

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

    play->envCtx.lightSettings.fogNear = (arg2 - play->envCtx.unk_C4.fogNear) * temp;

    if (arg1 == 0.0f) {
        for (i = 0; i < 3; i++) {
            play->envCtx.lightSettings.fogColor[i] = 0;
        }
    } else {
        temp = arg1 * 5.0f;
        temp = CLAMP_MAX(temp, 1.0f);

        for (i = 0; i < 3; i++) {
            play->envCtx.lightSettings.fogColor[i] = -(f32)play->envCtx.unk_C4.fogColor[i] * temp;
        }
    }

    if (arg4 <= 0.0f) {
        return 1;
    }

    arg1 *= arg4;

    for (i = 0; i < 3; i++) {
        play->envCtx.lightSettings.ambientColor[i] = -(f32)play->envCtx.unk_C4.ambientColor[i] * arg1;
        play->envCtx.lightSettings.diffuseColor1[i] = -(f32)play->envCtx.unk_C4.diffuseColor1[i] * arg1;
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
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.unk_C4.ambientColor, to, lerp,
                         (Vec3s*)&play->envCtx.lightSettings.ambientColor);
}

void Environment_LerpDiffuseColor(PlayState* play, Color_RGB8* to, f32 lerp) {
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.unk_C4.diffuseColor1, to, lerp,
                         (Vec3s*)play->envCtx.lightSettings.diffuseColor1);
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.unk_C4.diffuseColor, to, lerp,
                         (Vec3s*)play->envCtx.lightSettings.diffuseColor2);
}

void Environment_LerpFogColor(PlayState* play, Color_RGB8* to, f32 lerp) {
    Environment_LerpRGB8((Color_RGB8*)play->envCtx.unk_C4.fogColor, to, lerp,
                         (Vec3s*)play->envCtx.lightSettings.fogColor);
}

void Environment_LerpFog(PlayState* play, s16 fogNearTarget, s16 fogFarTarget, f32 lerp) {
    play->envCtx.lightSettings.fogNear = (fogNearTarget - (s16)play->envCtx.unk_C4.fogNear) * lerp;
    play->envCtx.lightSettings.zFar = (fogFarTarget - (s16)play->envCtx.unk_C4.zFar) * lerp;
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
    gWeatherMode = 0;
    gSaveContext.save.cutsceneIndex = 0;
    gSaveContext.respawnFlag = -3;
    play->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_RETURN].entrance;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_FADE_WHITE;
    gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE;
}

void func_800FD980(PlayState* play) {
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

        D_801F4F38 = POLY_OPA_DISP;

        gSPNoOp(POLY_OPA_DISP++);

        CLOSE_DISPS(play->state.gfxCtx);
    } else {
        D_801F4F38 = NULL;
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

void Environment_DrawSkyboxStars(PlayState* play, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSkyboxStars.s")

// This funcion is a wreck
/*
void Environment_DrawSkyboxStars(PlayState* arg0, Gfx** arg1) {
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF4;
    f32 spF0;
    s32 spE4;
    Gfx *spD8;
    Gfx *temp_s5;
    MtxF *temp_s3;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    s32 phi_s2;
    u32 seed;
    s32 phi_v1;
    u32 phi_a3;

    temp_s5 = *arg1;
    spE4 = Environment_IsSceneUpsideDown(arg0);
    Matrix_FromRSPMatrix(arg0->view.viewingPtr, &arg0->billboardMtxF);
    Matrix_FromRSPMatrix(&arg0->view.projection, &arg0->viewProjectionMtxF);
    SkinMatrix_MtxFMtxFMult(&arg0->viewProjectionMtxF, &arg0->billboardMtxF, &arg0->viewProjectionMtxF);

    phi_v1 = 0;

    gDPPipeSync(temp_s5++);

    gDPSetEnvColor(temp_s5++, 255, 255, 255, (u8)(255.0f * D_801F4F28));

    _DW({
        Gfx* _g = temp_s5++;
        _g->words.w0 = 0xFC32BA65;
        _g->words.w1 = 0xFF77FFFF;
    });

    _DW({
        Gfx* _g = temp_s5++;
        _g->words.w0 = 0xEF000CF0;
        _g->words.w1 = 0x50704C;
    });

    seed = (gSaveContext.playerName[7] << 0x1C) ^
           ((gSaveContext.playerName[0] << 0x18) ^
            (gSaveContext.playerName[1] << 0x14) ^
            (gSaveContext.playerName[2] << 0x10) ^
            (gSaveContext.playerName[3] << 0xC) ^
            (gSaveContext.playerName[4] << 8) ^
            (gSaveContext.playerName[5] << 4) ^
             gSaveContext.playerName[6] ^
            (gSaveContext.playerName[7] >> 4));

    for (phi_s2 = 0; phi_s2 < sEnvSkyboxNumStars; phi_s2++) {
        if (phi_s2 < 0x10) {
            spFC = D_801DD880[phi_s2].x + arg0->view.eye.x;
            sp100 = D_801DD880[phi_s2].y + arg0->view.eye.y;
            sp104 = D_801DD880[phi_s2].z + arg0->view.eye.z;
            phi_a3 = 8;
        } else {
            seed = (seed * 0x19660D) + 0x3C6EF35F;
            sRandFloat = (seed >> 9) | 0x3F800000;
            temp_f4 = *((f32*)&sRandFloat) - 1.0f;

            seed = (seed * 0x19660D) + 0x3C6EF35F;
            sRandFloat = (seed >> 9) | 0x3F800000;
            temp_f20 = ((*((f32*)&sRandFloat) - 1.0f) + temp_f4) * 0.5f;

            seed = (seed * 0x19660D) + 0x3C6EF35F;
            sp100 = (arg0->view.eye.y + (temp_f20 * temp_f20 * 16384.0f)) - 1000.0f;
            spFC = Math_SinS(seed) * (D_801DD9FC - temp_f20) * 16384.0f + arg0->view.eye.x;
            sp104 = Math_CosS(seed) * (D_801DD9FC - temp_f20) * 16384.0f + arg0->view.eye.z;

            seed = (seed * 0x19660D) + 0x3C6EF35F;
            sRandFloat = (seed >> 9) | 0x3F800000;
            temp_f2 = *((f32*)&sRandFloat) - 1.0f;

            phi_a3 = (temp_f2 * temp_f2 * 8.0f) + 2.0f;
        }

        if (spE4 != 0) {
            sp100 = -sp100;
        }

        if ((phi_s2 < 0xF) || ((phi_s2 == 0xF) && ((gSaveContext.day % 7) == 0))) {
            _DW({
                Gfx* _g = temp_s5++;
                _g->words.w0 = 0xFA000000;
                _g->words.w1 = D_801DD8E0[phi_s2 & 7];
            });
        } else if (((phi_s2 & 0x3F) == 0) || (phi_s2 == 0x10)) {
            _DW({
                Gfx* _g = temp_s5++;
                _g->words.w0 = 0xFA000000;
                _g->words.w1 = D_801DD900[phi_v1 & 0xF].rgba;
            });
            phi_v1++;
        }

        if (phi_a3 >= 2) {
            temp_f2_2 = arg0->viewProjectionMtxF.mf[3][3] + ((spFC * arg0->viewProjectionMtxF.mf[0][3]) + (sp100 *
arg0->viewProjectionMtxF.mf[1][3]) + (sp104 * arg0->viewProjectionMtxF.mf[2][3])); if (temp_f2_2 >= 1.0f) { temp_f0
= 1.0f / temp_f2_2; temp_s3 = &arg0->viewProjectionMtxF; spF0 = (temp_s3->mf[3][0] + ((spFC * temp_s3->mf[0][0]) +
(sp100 * temp_s3->mf[1][0]) + (sp104 * temp_s3->mf[2][0]))) * temp_f0; spF4 = (temp_s3->mf[3][1] + ((spFC *
temp_s3->mf[0][1]) + (sp100 * temp_s3->mf[1][1]) + (sp104 * temp_s3->mf[2][1]))) * temp_f0;
            }

            if ((temp_f2_2 >= 1.0f) && (spF0 > -1.0f) && (spF0 < 1.0f) && (spF4 > -1.0f) && (spF4 < 1.0f)) {
                spD8 = temp_s5;
                spF0 = (spF0 * 160.0f) + 160.0f;
                spF4 = (spF4 * -120.0f) + 120.0f;
                Environment_DrawSkyboxStar(&spD8, spF0, spF4, phi_a3, 4);
                temp_s5 = spD8;
            }
        }
    }

    gDPPipeSync(temp_s5++);

    *arg1 = temp_s5;
}
*/

void Environment_Draw(PlayState* play) {
    func_800FD980(play);
    Environment_DrawSun(play);
    Environment_UpdateLightningStrike(play);
    Environment_DrawLightning(play, 0);
    Environment_DrawSkyboxFilters(play);
}

void func_800FE3E0(PlayState* play) {
    Gfx* sp2C;
    Gfx* sp28;

    if (D_801F4F38 != NULL) {
        OPEN_DISPS(play->state.gfxCtx);

        sp28 = POLY_OPA_DISP;
        sp2C = Graph_GfxPlusOne(sp28);

        gSPDisplayList(D_801F4F38, sp2C);

        Environment_DrawSkyboxStars(play, &sp2C);

        gSPEndDisplayList(sp2C++);

        Graph_BranchDlist(sp28, sp2C);

        POLY_OPA_DISP = sp2C;
        D_801F4F38 = NULL;

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

u32 func_800FE4B8(PlayState* play) {
    u32 ret = play->envCtx.unk_E2;

    if ((play->sceneId == SCENE_OMOYA) && (play->roomCtx.curRoom.num == 0)) {
        ret = ((gSaveContext.save.day >= 2) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) ? true : false;
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
                ret = false;
            }
            break;
        case SCENE_10YUKIYAMANOMURA2:
            if (gSaveContext.sceneLayer == 1) {
                ret = false;
            }
            break;
    }

    return ret;
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

u8 func_800FE6F8(PlayState* play, s16 arg1, s16 arg2) {
    u16 temp_v0;
    u8 ret = false;

    if (R_TIME_SPEED != 0) {
        temp_v0 = ((void)0, gSaveContext.save.time) +
                  (R_TIME_SPEED + ((void)0, gSaveContext.save.timeSpeedOffset)) * arg1 * 20;
        if (arg2 < temp_v0) {
            ret = true;
        }
    }

    return ret;
}

u8 func_800FE778(void) {
    return sSandstormColorIndex;
}

u8 func_800FE788(void) {
    return sNextSandstormColorIndex;
}

f32 func_800FE798(void) {
    return sSandstormLerpScale;
}

void func_800FE7A8(Color_RGBA8* arg0, Color_RGBA8* arg1) {
    f32 sp24;
    u32 pad;
    u32 index;
    u32 index2;

    sp24 = func_800FE798();
    index = func_800FE778();
    index2 = func_800FE788();
    if (sp24 <= 0.0f) {
        arg1->r = arg0[index].r;
        arg1->g = arg0[index].g;
        arg1->b = arg0[index].b;
        arg1->a = arg0[index].a;
    } else {
        arg1->r = (s32)F32_LERP(arg0[index].r, arg0[index2].r, sp24);
        arg1->g = (s32)F32_LERP(arg0[index].g, arg0[index2].g, sp24);
        arg1->b = (s32)F32_LERP(arg0[index].b, arg0[index2].b, sp24);
        arg1->a = (s32)F32_LERP(arg0[index].a, arg0[index2].a, sp24);
    }
}

u8 func_800FE9B4(PlayState* play) {
    u8 ret;

    ret = false;
    if ((play->envCtx.precipitation[4] == 60) && (play->envCtx.precipitation[2] == 0)) {
        ret = true;
    }

    if ((play->envCtx.precipitation[0] == 60) && !(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER)) {
        if (func_800FE4B8(play) && (play->envCtx.precipitation[2] == 0)) {
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FEAF4.s")

// TODO permuter - regalloc, reordering issues
/*
void func_800FEAF4(EnvironmentContext *envCtx) {
    u8 temp_t8;
    u8 phi_v1;

    phi_v1 = 0;
    if (((void)0, gSaveContext.day) != 0) {
        phi_v1 = ((void)0, gSaveContext.day) - 1;
    }
    temp_t8 = phi_v1 + (D_801F4E31 * 3);
    envCtx->unk_17 = temp_t8;
    envCtx->unk_18 = temp_t8;

    if (D_801F4E31 == 4) {
        temp_t8 = 0xE;
        envCtx->unk_17 = temp_t8;
        envCtx->unk_18 = temp_t8;
    } else if (D_801F4E31 == 5) {
        temp_t8 = 0x10;
        envCtx->unk_17 = temp_t8;
        envCtx->unk_18 = temp_t8;
    } else if (D_801F4E31 == 6) {
        temp_t8 = 0x11;
        envCtx->unk_17 = temp_t8;
        envCtx->unk_18 = temp_t8;
    } else if (D_801F4E31 == 7) {
        temp_t8 = phi_v1 + 0x12;
        envCtx->unk_17 = temp_t8;
        envCtx->unk_18 = temp_t8;
    } else if (D_801F4E31 == 8) {
        temp_t8 = phi_v1 + 0x15;
        envCtx->unk_17 = temp_t8;
        envCtx->unk_18 = temp_t8;
    } else if (D_801F4E31 == 9) {
        temp_t8 = 0x18;
        envCtx->unk_17 = temp_t8;
        envCtx->unk_18 = temp_t8;
    } else if (D_801F4E31 == 0xA) {
        temp_t8 = phi_v1 + 0x19;
        envCtx->unk_17 = temp_t8;
        envCtx->unk_18 = temp_t8;
    }

    if (phi_v1 >= 3) {
        temp_t8 = 0xD;
        envCtx->unk_17 = 0xD;
        envCtx->unk_18 = 0xD;
    }

    if (temp_t8 >= 0x1C) {
        envCtx->unk_17 = 0;
        envCtx->unk_18 = 0;
    }

    switch (((void)0, gSaveContext.day)) {
    default:
    case 0:
    case 1:
        envCtx->unk_1F = 0;
        envCtx->unk_20 = 0;
        break;
    case 2:
        envCtx->unk_1F = 3;
        envCtx->unk_20 = 3;
        break;
    case 3:
        envCtx->unk_1F = 4;
        envCtx->unk_20 = 4;
        break;
    }

    return;
}
*/
