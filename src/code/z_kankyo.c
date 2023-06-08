#include "global.h"

void func_800F5090(s32 arg0, PlayState* play) {
    D_801BDB94 = SysCfb_GetZBufferPixel(D_801F4F20, D_801F4F24);
    Lights_GlowCheck(play);
}

s32 Environment_ZBufValToFixedPoint(s32 zBufferVal) {
    s32 ret = ((zBufferVal >> 4 & 0x7FF) << D_801BE4F4[zBufferVal >> 15 & 7].unk_0) + D_801BE4F4[zBufferVal >> 15 & 7].unk_4;

    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Init.s")

u8 func_800F5954(u8* pvalue, u8 target, u8 scale, u8 step, u8 minStep) {
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

f32 func_800F5B10(u16 endFrame, u16 startFrame, u16 curFrame, u16 accelDuration, u16 decelDuration) {
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
        //osSyncPrintf(VT_COL(RED, WHITE) "\nend_frameとstart_frameのフレーム関係がおかしい!!!" VT_RST);
        //osSyncPrintf(VT_COL(RED, WHITE) "\nby get_parcent_forAccelBrake!!!!!!!!!" VT_RST);

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

void func_800F6834(PlayState* play, s32 waterLightsIndex) {
    if (waterLightsIndex == 0x1F) {
        waterLightsIndex = 0;
    }

    if (!play->envCtx.lightMode) {
        if (D_801F4F31 == 0) {
            D_801F4F31 = 1;
            D_801BDBB4 = play->envCtx.changeLightNextConfig;
            if (waterLightsIndex != play->envCtx.lightConfig) {
                play->envCtx.lightConfig = waterLightsIndex;
                play->envCtx.changeLightNextConfig = waterLightsIndex;
            }
        } else if ((play->envCtx.lightConfig != waterLightsIndex) && (play->envCtx.changeLightTimer == 0)) {
            play->envCtx.changeLightEnabled = 1;
            play->envCtx.changeLightNextConfig = waterLightsIndex;
            play->envCtx.changeDuration = 0x14;
            play->envCtx.changeLightTimer = play->envCtx.changeDuration;
        }
    } else if (play->envCtx.lightSettingOverride == 0xFF) {
        if (D_801F4F31 == 0) {
            D_801F4F31 = 1;
            D_801BDBB4 = play->envCtx.lightSetting;
        }
        play->envCtx.lightBlendEnabled = false; // instantly switch to water lights
        play->envCtx.lightSettingOverride = waterLightsIndex;
    }
}

void func_800F694C(PlayState* play) {
    if (!play->envCtx.lightMode) {
        if (D_801F4F31 != 0) {
            D_801F4F31 = 0;
            play->envCtx.lightConfig = D_801BDBB4;
            play->envCtx.changeLightNextConfig = D_801BDBB4;
        }
    } else if (D_801F4F31 != 0) {
        D_801F4F31 = 0;
        play->envCtx.lightSetting = D_801BDBB4;
        play->envCtx.lightBlendEnabled = false; // instantly switch to previous lights
        play->envCtx.lightSettingOverride = 0xFF;
        play->envCtx.lightBlend = 1.0f;
    }
}

void func_800F6A04(void) {
    if ((gSaveContext.gameMode != 0) && (gSaveContext.gameMode != 3)) {
        Rumble_StateWipeRequests();
    }
}

void func_800F6A40(PlayState* play) {
    if ((play->pauseCtx.state == 0) && (play->pauseCtx.debugEditor == 0) && ((play->skyboxId == 1) || (play->skyboxId == 3))) {
        play->skyboxCtx.rot.y -= gRegEditor->data[0xF] * 1.0e-4f;
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

void func_800F6B44(PlayState* play, EnvironmentContext* envCtx, PauseContext* pauseCtx, MessageContext* msgCtx, GameOverContext* gameOverCtx) {
    u16 time;

    if ((D_801F4F32 == 0) && (pauseCtx->state == 0) && (gameOverCtx->state == GAMEOVER_INACTIVE)) {
        if ((msgCtx->msgMode == 0) || (msgCtx->currentTextId == 0xF7) || (msgCtx->currentTextId == 0x20D2) || (msgCtx->currentTextId == 0x140C) || ((msgCtx->currentTextId >= 0x100) && (msgCtx->currentTextId < 0x201)) || (((void)0, gSaveContext.gameMode) == 3)) {
            if (!FrameAdvance_IsEnabled(&play->state) && ((play->transitionMode == 0) || (((void)0, gSaveContext.gameMode) != 0))) {
                if (play->transitionTrigger == 0) {
                    if (CutsceneManager_GetCurrentCsId() == -1) {
                        if (Play_InCsMode(play) == 0) {
                            gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)gRegEditor->data[0xF];
                            if (gRegEditor->data[0xF] != 0) {
                                // TODO figure out gSaveContext.unk_16
                                gSaveContext.save.time = ((void)0, gSaveContext.save.time) + ((void)0, *(u16*)((u8*)&gSaveContext + 0x16));
                            }
                        }
                    }
                }
            }
        }
    }
    if ((((void)0, gSaveContext.skyboxTime) >= 0x4000) ||
        (((void)0, gSaveContext.save.time) < 0x4000) ||
        (((void)0, gSaveContext.save.time) >= 0x4010)) {
        gSaveContext.skyboxTime = gSaveContext.save.time;
    }

    time = ((void)0, gSaveContext.save.time);

    if ((time >= 0xC000) || (time < 0x4000)) {
        gSaveContext.save.isNight = 1;
    } else {
        gSaveContext.save.isNight = 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F6CEC.s")

// TODO permuter - regalloc issues
/*
void func_800F6CEC(PlayState* arg0, u8 arg1, s800F6CEC* arg2, LightSettings* arg3) {
    s32 phi_t1;
    s32 temp_v1_2;
    s32 temp_v1;

    if ((((void)0, gSaveContext.day) >= 2) && (arg1 >= 4) && (arg1 < 8)) {
        temp_v1 = (arg1 % 4);
        temp_v1_2 = (((void)0, gSaveContext.day) * 4) + 4;
        for (phi_t1 = 0; phi_t1 != 3; phi_t1++) {
            arg2->ambientColor[phi_t1] = arg3[temp_v1_2 + temp_v1].ambientColor[phi_t1] - arg3[temp_v1].ambientColor[phi_t1];
            arg2->diffuseColor1[phi_t1] = arg3[temp_v1_2 + temp_v1].diffuseColor1[phi_t1] - arg3[temp_v1].diffuseColor1[phi_t1];
            arg2->diffuseColor2[phi_t1] = arg3[temp_v1_2 + temp_v1].diffuseColor[phi_t1] - arg3[temp_v1].diffuseColor[phi_t1]; // TODO rename to diffuseColor2
            arg2->fogColor[phi_t1] = arg3[temp_v1_2 + temp_v1].fogColor[phi_t1] - arg3[temp_v1].fogColor[phi_t1];
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

    if (play->envCtx.sunMoonDisabled == 0) {
        if (play->envCtx.unk_F2[1] != 0) {
            Math_SmoothStepToF(&D_801F4F1C, 0.0f, 0.5f, 4.0f, D_801DD944);
        } else {
            Math_SmoothStepToF(&D_801F4F1C, 255.0f, 0.5f, 4.0f, D_801DD948);
        }

        if (Environment_IsSceneUpsideDown(play)) {
            phi_v0 = ((void)0, gSaveContext.save.time) + 0x8000;
        } else {
            phi_v0 = ((void)0, gSaveContext.save.time);
        }

        temp_a0 = phi_v0 - 0x8000;

        if (play->csCtx.state != 0) {
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

        D_801F4F10 = temp_f0 / 80.0f * 255.0f;
        if (D_801F4F10 < 0.0f) {
            D_801F4F10 = 0.0f;
        }
        if (D_801F4F10 > 255.0f) {
            D_801F4F10 = 255.0f;
        }
        D_801F4F10 = 255.0f - D_801F4F10;

        D_801F4F14 = temp_f0 / 80.0f;
        if (D_801F4F14 < 0.0f) {
            D_801F4F14 = 0.0f;
        }
        if (D_801F4F14 > 1.0f) {
            D_801F4F14 = 1.0f;
        }

        D_801F4F18 = (2.0f * D_801F4F14) + 12.0f;
    }
}

void func_800F88C4(u16 arg0) {
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_28_08) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_28_10) && CHECK_WEEKEVENTREG(arg0)) {
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

        if (((gSaveContext.weekEventReg[89] & 0x40) != 0) && (((((void)0, gSaveContext.time) - 0x3FFC) & 0xFFFF) >= 0xF556)) {
            gSaveContext.weekEventReg[90] |= 1;
        } else if (((gSaveContext.weekEventReg[89] & 8) != 0) && (temp_a2_2 >= 0x416)) {
            gSaveContext.weekEventReg[89] |= 0x40;
            D_801F4E78 = 0;
        } else if (((gSaveContext.weekEventReg[85] & 0x80) != 0) && (temp_a2_2 >= 0x1198)) {
            gSaveContext.weekEventReg[89] |= 8;
            D_801F4E78 = gSaveContext.time;
        } else if (((gSaveContext.weekEventReg[86] & 1) != 0) && (temp_a2_2 >= 0xC43)) {
            gSaveContext.weekEventReg[85] |= 0x80;
        }
    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Update.s")

void func_800FC3DC(PlayState*);
void func_800F8A9C(PlayState*);
void func_800FB9B4(PlayState*);

void Environment_Update(PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx, PauseContext* pauseCtx, MessageContext* msgCtx, GameOverContext* gameOverCtx, GraphicsContext* gfxCtx) {
    D_801BDBC0 = 0;
    D_801BDBC4 = 0;

    func_800F6A04();

    if (pauseCtx->state == 0) {
        func_800F6A40(play);
        func_800FC3DC(play);
        func_800FB9B4(play);
        func_800F6AB8();
        func_800F6B44(play, envCtx, pauseCtx, msgCtx, gameOverCtx);
        func_800F8554(play);
        func_800F6FF8(play, envCtx, lightCtx);
        func_800F8A9C(play);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F8D84.s")

extern Gfx D_0407AB70[];

// TODO permuter - regalloc issues, minor reordering
/*
void func_800F8D84(PlayState *play) {
    if (play->envCtx.unk_16 == 0) {
        OPEN_DISPS(play->state.gfxCtx);

        if ((play->envCtx.unk_8 > -800.0f) || Kankyo_IsSceneUpsideDown(play)) {
            Matrix_InsertTranslation(play->view.eye.x + play->envCtx.unk_4,
                                     play->view.eye.y + play->envCtx.unk_8,
                                     play->view.eye.z + play->envCtx.unk_C, MTXMODE_NEW);

            if (((void)0, gSaveContext.time) < 0x8000) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0,
                                255,
                                (u8)(D_801F4F14 * 52.0f) + 203,
                                (u8)(D_801F4F14 * 19.0f) + 181,
                                D_801F4F1C);
                gDPSetEnvColor(POLY_OPA_DISP++,
                               -(u8)(D_801F4F14 * 5.0f) + 175,
                               (u8)(D_801F4F14 * 135.0f) + 120,
                               (u8)(D_801F4F14 * 100.0f) + 100,
                               D_801F4F10);
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0,
                                255,
                                (u8)(D_801F4F14 * 75.0f) + 180,
                                (u8)(D_801F4F14 * 100.0f) + 100,
                                D_801F4F1C);
                gDPSetEnvColor(POLY_OPA_DISP++,
                               180,
                               (u8)(D_801F4F14 * 255.0f),
                               (u8)(D_801F4F14 * 200.0f),
                               D_801F4F10);
            }

            Matrix_Scale(D_801F4F18, D_801F4F18, D_801F4F18, 1);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_LOAD);

            func_8012C148(play->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, D_0407AB70);

        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
*/

void Environment_DrawSunLensFlare(PlayState* play, EnvironmentContext* envCtx, View* view, GraphicsContext* gfxCtx, Vec3f vec) {
    if ((play->envCtx.unk_F2[1] == 0) && !(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER) && (play->skyboxId == 1)) {
        f32 v0 = Math_CosS(((void)0, gSaveContext.save.time) - 0x8000);
        func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, vec, 370.0f, v0 * 120.0f, 0x190, 1);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F9824.s")

f32 func_800FA39C(void) {
    return Rand_ZeroOne() - 0.5f;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FA3C4.s")

void Environment_DrawRain(PlayState* play, View* view, GraphicsContext* gfxCtx) {
    if (!(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER) && (play->envCtx.unk_F2[2] == 0)) {
        if (play->envCtx.unk_F2[4] != 0) {
            if (play->envCtx.unk_F2[2] == 0) {
                func_800FA3C4(play, view, gfxCtx);
            }
        } else if (!(GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER)) {
            if ((func_800FE4B8(play) != 0) && (play->envCtx.unk_F2[2] == 0)) {
                func_800FA3C4(play, view, gfxCtx);
            }
        }
    }
}

void func_800FAAB4(PlayState* play, u8 arg1) {
    if (!play->envCtx.lightMode) {
        if ((arg1 == 31) || (D_801F4F33 != 0)) {
            if (D_801F4F30 != 0xFF) {
                play->envCtx.changeLightEnabled = 1;
                play->envCtx.changeLightNextConfig = D_801F4F30;
                play->envCtx.changeDuration = 20;
                play->envCtx.changeLightTimer = play->envCtx.changeDuration;
                D_801F4F30 = 0xFF;
            }
        } else if (play->envCtx.changeLightNextConfig != arg1) {
            D_801F4F30 = play->envCtx.lightConfig;
            play->envCtx.changeLightEnabled = 1;
            play->envCtx.changeLightNextConfig = arg1;
            play->envCtx.changeDuration = 20;
            play->envCtx.changeLightTimer = play->envCtx.changeDuration;
        }
    } else if ((play->envCtx.lightSetting != arg1) && (play->envCtx.lightBlend >= 1.0f) && (play->envCtx.lightSettingOverride == 0xFF)) {
        if (arg1 > 30) {
            arg1 = 0;
        }

        play->envCtx.lightBlend = 0.0f;
        play->envCtx.prevLightSetting = play->envCtx.lightSetting;
        play->envCtx.lightSetting = arg1;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FAC20.s")

extern Gfx D_0E0002C8[];

void func_800FAF74(PlayState* play, u8 red, u8 green, u8 blue, u8 alpha) {
    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL57_Opa(play->state.gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, red, green, blue, alpha);
    gSPDisplayList(POLY_OPA_DISP++, D_0E0002C8);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_800FB010(PlayState* play) {
    if (play->envCtx.unk_E3 != LIGHTNING_MODE_OFF) {
        switch (D_801F4E68.state) {
            case LIGHTNING_STRIKE_WAIT:
                // every frame theres a 10% chance of the timer advancing 10 units
                if (Rand_ZeroOne() < 0.1f) {
                    D_801F4E68.delayTimer += 10.0f;
                }

                D_801F4E68.delayTimer += Rand_ZeroOne();

                if (D_801F4E68.delayTimer > 500.0f) {
                    D_801F4E68.flashRed = 200;
                    D_801F4E68.flashGreen = 200;
                    D_801F4E68.flashBlue = 255;
                    D_801F4E68.flashAlphaTarget = 200;

                    D_801F4E68.delayTimer = 0.0f;
                    Environment_AddLightningBolts(play, (u8)((Rand_ZeroOne() * (ARRAY_COUNT(D_801F4E80) - 0.1f)) + 1.0f));
                    D_801F4F2C = 0;
                    D_801F4E68.state++;
                }
                break;
            case LIGHTNING_STRIKE_START:
                D_801F4E68.flashRed = 200;
                D_801F4E68.flashGreen = 200;
                D_801F4E68.flashBlue = 255;

                play->envCtx.lightSettings.ambientColor[0] += 80;
                play->envCtx.lightSettings.ambientColor[1] += 80;
                play->envCtx.lightSettings.ambientColor[2] += 100;

                D_801F4F2C += 100;

                if (D_801F4F2C >= D_801F4E68.flashAlphaTarget) {
                    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_0, 0);
                    D_801F4E68.state++;
                    D_801F4E68.flashAlphaTarget = 0;
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

                D_801F4F2C -= 10;

                if (D_801F4F2C <= D_801F4E68.flashAlphaTarget) {
                    play->envCtx.lightSettings.ambientColor[0] = 0;
                    play->envCtx.lightSettings.ambientColor[1] = 0;
                    play->envCtx.lightSettings.ambientColor[2] = 0;

                    D_801F4E68.state = LIGHTNING_STRIKE_WAIT;

                    if (play->envCtx.unk_E3 == LIGHTNING_MODE_LAST) {
                        play->envCtx.unk_E3 = LIGHTNING_MODE_OFF;
                    }
                }
                break;
        }
    }

    if (D_801F4E68.state != LIGHTNING_STRIKE_WAIT) {
        func_800FAF74(play, D_801F4E68.flashRed, D_801F4E68.flashGreen,
                                       D_801F4E68.flashBlue, D_801F4F2C);
    }
}

void Environment_AddLightningBolts(PlayState* play, u8 num) {
    s16 boltsAdded = 0;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(D_801F4E80); i++) {
        if (D_801F4E80[i].state == LIGHTNING_BOLT_INACTIVE) {
            D_801F4E80[i].state = LIGHTNING_BOLT_START;
            boltsAdded++;

            if (boltsAdded >= num) {
                break;
            }
        }
    }
}


extern Gfx D_0403F230[];

void func_800FB388(PlayState* play, s32 unused) {
    // TODO
    // static void* D_801BE90C[] = {
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

    for (i = 0; i < ARRAY_COUNT(D_801F4E80); i++) {
        switch (D_801F4E80[i].state) {
            case LIGHTNING_BOLT_START:
                dx = play->view.at.x - play->view.eye.x;
                dz = play->view.at.z - play->view.eye.z;

                x = dx / sqrtf(SQ(dx) + SQ(dz));
                z = dz / sqrtf(SQ(dx) + SQ(dz));

                D_801F4E80[i].pos.x = play->view.eye.x + x * 9500.0f;
                D_801F4E80[i].pos.y = Rand_ZeroOne() * 1000.0f + 4000.0f;
                D_801F4E80[i].pos.z = play->view.eye.z + z * 9500.0f;

                D_801F4E80[i].offset.x = (Rand_ZeroOne() - 0.5f) * 5000.0f;
                D_801F4E80[i].offset.y = 0.0f;
                D_801F4E80[i].offset.z = (Rand_ZeroOne() - 0.5f) * 5000.0f;

                D_801F4E80[i].textureIndex = 0;
                D_801F4E80[i].pitch = (Rand_ZeroOne() - 0.5f) * 40.0f;
                D_801F4E80[i].roll = (Rand_ZeroOne() - 0.5f) * 40.0f;
                D_801F4E80[i].delayTimer = 3 * (i + 1);
                D_801F4E80[i].state++;
                break;
            case LIGHTNING_BOLT_WAIT:
                D_801F4E80[i].delayTimer--;

                if (D_801F4E80[i].delayTimer <= 0) {
                    D_801F4E80[i].state++;
                }
                break;
            case LIGHTNING_BOLT_DRAW:
                if (D_801F4E80[i].textureIndex < 7) {
                    D_801F4E80[i].textureIndex++;
                } else {
                    D_801F4E80[i].state = LIGHTNING_BOLT_INACTIVE;
                }
                break;
        }

        if (D_801F4E80[i].state == LIGHTNING_BOLT_DRAW) {
            Matrix_Translate(D_801F4E80[i].pos.x + D_801F4E80[i].offset.x,
                             D_801F4E80[i].pos.y + D_801F4E80[i].offset.y,
                             D_801F4E80[i].pos.z + D_801F4E80[i].offset.z, MTXMODE_NEW);
            Matrix_RotateXFApply(D_801F4E80[i].pitch * (M_PI / 180.0f));
            Matrix_RotateZF(D_801F4E80[i].roll * (M_PI / 180.0f), MTXMODE_APPLY);
            Matrix_Scale(22.0f, 100.0f, 22.0f, MTXMODE_APPLY);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 128);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 255, 255, 128);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_801BE90C[D_801F4E80[i].textureIndex]));
            Gfx_SetupDL61_Xlu(play->state.gfxCtx);
            gSPMatrix(POLY_XLU_DISP++, &D_01000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, D_0403F230);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FB758.s")

// needs a lot of work
/*
void func_800FB758(PlayState *play) {
    u8 phi_v0;

    phi_v0 = ((void)0, gSaveContext.day) - 1;
    if (phi_v0 >= 3) {
        phi_v0 = 0;
    }
    if (play->envCtx.unk_E4 != 0xFE) {
        play->envCtx.unk_E4 = 0xFF;
        if (((void)0, gSaveContext.unk_3F46) != 0) {
            play->envCtx.unk_E4 = 0xFE;
            Audio_QueueSeqCmd(((void)0, gSaveContext.unk_3F46) + 0x8000);
            gSaveContext.unk_3F46 = 0;
        } else if ((func_800FE590(play) == 0) || (func_800FE5D0(play) != 0) || (func_801A8A50(0) != 0x57)) {
            if (play->soundCtx.seqIndex == 0x7F) {
                if (play->soundCtx.nightSeqIndex != 0x13) {
                    if (play->soundCtx.nightSeqIndex != ((void)0, gSaveContext.nightSeqIndex)) {
                        func_801A4A28(play->soundCtx.nightSeqIndex);
                    }
                }
            } else {
                if (play->soundCtx.nightSeqIndex == 0x13) {
                    if (play->soundCtx.seqIndex != ((void)0, gSaveContext.seqIndex)) {
                        func_801A25E4(play->soundCtx.seqIndex, phi_v0);
                    }
                } else {
                    if ((((void)0, gSaveContext.time) >= 0x4000) && (((void)0, gSaveContext.time) < 0xB71D)) {
                        if (D_801BDBC8 != 0) {
                            func_801A2544(play->soundCtx.seqIndex, phi_v0);
                        } else if ((((void)0, gSaveContext.time) >= 0x402D) && (play->soundCtx.seqIndex != ((void)0, gSaveContext.seqIndex))) {
                            func_801A25E4(play->soundCtx.seqIndex, phi_v0);
                        }
                        play->envCtx.unk_E4 = 1;
                    } else {
                        if (play->soundCtx.nightSeqIndex != gSaveContext.nightSeqIndex) {
                            func_801A4A28(play->soundCtx.nightSeqIndex);
                        }
                        if ((((void)0, gSaveContext.time) >= 0xB71D) && (((void)0, gSaveContext.time) < 0xCAAA)) {
                            play->envCtx.unk_E4 = 3;
                        } else if ((((void)0, gSaveContext.time) >= 0xCAAB) || (((void)0, gSaveContext.time) < 0x3555)) {
                            play->envCtx.unk_E4 = 5;
                        } else {
                            play->envCtx.unk_E4 = 7;
                        }
                    }
                }
            }
        }

        func_801A3CD8(play->roomCtx.currRoom.echo);
        D_801BDBC8 = 0;
    }
}
*/

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FB9B4.s")

void Environment_DrawCustomLensFlare(PlayState* play) {
    Vec3f pos;

    if (D_801F4E32 != 0) {
        pos.x = D_801F4E38.x;
        pos.y = D_801F4E38.y;
        pos.z = D_801F4E38.z;
        func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, pos, D_801F4E44, D_801F4E48, D_801F4E4C, 0);
    }

    if (D_801F4E4E != 0) {
        pos.x = D_801F4E50.x;
        pos.y = D_801F4E50.y;
        pos.z = D_801F4E50.z;
        func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, pos, D_801F4E5C, D_801F4E60, D_801F4E64, 0);
    }
}

void Kankyo_InitGameOverLights(PlayState *play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    D_801F4F34 = 0;

    Lights_PointNoGlowSetInfo(&D_801F4EE8, player->actor.world.pos.x - 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z - 10.0f, 0, 0, 0,
                              255);
    D_801F4EE0 = LightContext_InsertLight(play, &play->lightCtx, &D_801F4EE8);

    Lights_PointNoGlowSetInfo(&D_801F4F00, player->actor.world.pos.x + 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z + 10.0f, 0, 0, 0,
                              255);

    D_801F4EF8 = LightContext_InsertLight(play, &play->lightCtx, &D_801F4F00);
}

void Kankyo_FadeInGameOverLights(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 i;

    Lights_PointNoGlowSetInfo(&D_801F4EE8, player->actor.world.pos.x - 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z - 10.0f,
                              D_801F4F34, D_801F4F34, D_801F4F34, 255);
    Lights_PointNoGlowSetInfo(&D_801F4F00, player->actor.world.pos.x + 10.0f,
                              player->actor.world.pos.y + 10.0f, player->actor.world.pos.z + 10.0f,
                              D_801F4F34, D_801F4F34, D_801F4F34, 255);

    if (D_801F4F34 < 254) {
        D_801F4F34 += 2;
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
        play->envCtx.screenFillColor[3] = D_801F4F34;
    }
}

void Kankyo_FadeOutGameOverLights(PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 i;

    if (D_801F4F34 >= 3) {
        D_801F4F34 -= 3;
    } else {
        D_801F4F34 = 0;
    }

    if (D_801F4F34 == 1) {
        LightContext_RemoveLight(play, &play->lightCtx, D_801F4EE0);
        LightContext_RemoveLight(play, &play->lightCtx, D_801F4EF8);
    } else if (D_801F4F34 >= 2) {
        Lights_PointNoGlowSetInfo(&D_801F4EE8, player->actor.world.pos.x - 10.0f,
                                  player->actor.world.pos.y + 10.0f, player->actor.world.pos.z - 10.0f,
                                  D_801F4F34, D_801F4F34, D_801F4F34, 255);
        Lights_PointNoGlowSetInfo(&D_801F4F00, player->actor.world.pos.x + 10.0f,
                                  player->actor.world.pos.y + 10.0f, player->actor.world.pos.z + 10.0f,
                                  D_801F4F34, D_801F4F34, D_801F4F34, 255);
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
        play->envCtx.screenFillColor[3] = D_801F4F34;
        if (D_801F4F34 == 0) {
            play->envCtx.fillScreen = false;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FC3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_FillScreen.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSandstorm.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FD2B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FD538.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FD59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FD5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FD654.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FD698.s")

u32 get_days_elapsed(void) {
    return gSaveContext.save.daysElapsed;
}

void reset_days_elapsed(void) {
    gSaveContext.save.daysElapsed = 0;
}

u32 get_current_day(void) {
    return gSaveContext.save.day;
}

void func_800FD750(u16 seqId) {
    gSaveContext.forcedSeqId = seqId;
}

s32 func_800FD768(void) {
    s32 isDisabled = false;
    if (gSaveContext.forcedSeqId != 0) {
        isDisabled = true;
    }

    return isDisabled;
}

void func_800FD78C(PlayState* play) {
    if (((play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) && (play->sequenceCtx.ambienceId == AMBIENCE_ID_13)) || (play = play, (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) == NA_BGM_FINAL_HOURS))) {
        Audio_PlayAmbience(AMBIENCE_ID_07);
    } else if (play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) {
        if (play->sequenceCtx.ambienceId != AMBIENCE_ID_13) {
            if ((((void)0, gSaveContext.save.time) >= 0x4000) && (((void)0, gSaveContext.save.time) < 0xC000)) {
                Audio_PlayAmbience(play->sequenceCtx.ambienceId);
            }
        }
    }

    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_RAIN, CHANNEL_IO_PORT_1, 1);
    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_1, 1);
}

void func_800FD858(PlayState* play) {
    if (((play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) && (play->sequenceCtx.ambienceId == AMBIENCE_ID_13)) || (play = play, (AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN) == NA_BGM_FINAL_HOURS))) {
		SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_AMBIENCE, 20);
    } else if (play->sequenceCtx.seqId != NA_BGM_NO_MUSIC) {
        if (play->sequenceCtx.ambienceId != AMBIENCE_ID_13) {
            if ((((void)0, gSaveContext.save.time) >= 0x4000) && (((void)0, gSaveContext.save.time) < 0xC000)) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_AMBIENCE, 20);
            }
        }
    }

    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_RAIN, CHANNEL_IO_PORT_1, 0);
    Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_1, 0);
}


void func_800FD928(PlayState* play) {
    gWeatherMode = 0;
    gSaveContext.save.cutsceneIndex = 0;
    gSaveContext.respawnFlag = -3;
    play->nextEntrance = gSaveContext.respawn[RESPAWN_MODE_RETURN].entrance;
    play->transitionTrigger = 0x14;
    play->transitionType = TRANS_TYPE_FADE_WHITE;
    gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE;
}

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FD980.s")

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FDAF8.s")

void func_800FD980(PlayState* play) {
    f32 phi_f0;

    if ((play->envCtx.skybox1Index == 0) && (play->skyboxId == 1)) {
        if ((((void)0, gSaveContext.save.time) >= 0xE000) || (((void)0, gSaveContext.save.time) < 0x1555)) {
            phi_f0 = 1.0f;
        } else if (((void)0, gSaveContext.save.time) >= 0xCAAB) {
            phi_f0 = 1.0f - ((0xE000 - ((void)0, gSaveContext.save.time)) * 1.8308312e-4f); // TODO find thing
        } else if (((void)0, gSaveContext.save.time) < 0x2000) {
            phi_f0 = (0x2000 - ((void)0, gSaveContext.save.time)) * 3.6616623e-4f; // TODO find thing
        } else {
            phi_f0 = 0.0f;
        }

        phi_f0 = (play->envCtx.skyboxConfig == 0x18) ? 1.0f : phi_f0;

        D_801F4F28 = phi_f0;
        D_801BDB98 = D_801F4E7A;
    } else {
        D_801F4F28 = 0.0f;
        D_801BDB98 = 0;
    }

    if ((D_801BDB98 != 0) && (D_801F4F28 != 0.0f)) {
        OPEN_DISPS(play->state.gfxCtx);

        D_801F4F38 = POLY_OPA_DISP;

        gSPNoOp(POLY_OPA_DISP++);

        CLOSE_DISPS(play->state.gfxCtx);
    } else {
        D_801F4F38 = NULL;
    }
}

void func_800FDAF8(Gfx** arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4) {
    Gfx* g = *arg0;
    u32 xl = arg1 * 4.0f;
    u32 yl = arg2 * 4.0f;
    u32 xd = arg3;
    u32 yd = arg4;

    gSPTextureRectangle(g++, xl, yl, xl + xd, yl + yd, 0, 0, 0, 0, 0);
    *arg0 = g;
}

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FDC94.s")

void func_800FDC94(PlayState*, Gfx **);

// This funcion is a wreck
/*
void func_800FDC94(PlayState* arg0, Gfx** arg1) {
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
    spE4 = Kankyo_IsSceneUpsideDown(arg0);
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

    for (phi_s2 = 0; phi_s2 < D_801BDB98; phi_s2++) {
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
            temp_f2_2 = arg0->viewProjectionMtxF.mf[3][3] + ((spFC * arg0->viewProjectionMtxF.mf[0][3]) + (sp100 * arg0->viewProjectionMtxF.mf[1][3]) + (sp104 * arg0->viewProjectionMtxF.mf[2][3]));
            if (temp_f2_2 >= 1.0f) {
                temp_f0 = 1.0f / temp_f2_2;
                temp_s3 = &arg0->viewProjectionMtxF;
                spF0 = (temp_s3->mf[3][0] + ((spFC * temp_s3->mf[0][0]) + (sp100 * temp_s3->mf[1][0]) + (sp104 * temp_s3->mf[2][0]))) * temp_f0;
                spF4 = (temp_s3->mf[3][1] + ((spFC * temp_s3->mf[0][1]) + (sp100 * temp_s3->mf[1][1]) + (sp104 * temp_s3->mf[2][1]))) * temp_f0;
            }

            if ((temp_f2_2 >= 1.0f) && (spF0 > -1.0f) && (spF0 < 1.0f) && (spF4 > -1.0f) && (spF4 < 1.0f)) {
                spD8 = temp_s5;
                spF0 = (spF0 * 160.0f) + 160.0f;
                spF4 = (spF4 * -120.0f) + 120.0f;
                func_800FDAF8(&spD8, spF0, spF4, phi_a3, 4);
                temp_s5 = spD8;
            }
        }
    }

    gDPPipeSync(temp_s5++);

    *arg1 = temp_s5;
}
*/

void func_800FE390(PlayState* play) {
    func_800FD980(play);
    func_800F8D84(play);
    func_800FB010(play);
    func_800FB388(play, 0);
    func_800FAC20(play);
}

void func_800FE3E0(PlayState* play) {
    Gfx* sp2C;
    Gfx* sp28;

    if (D_801F4F38 != NULL) {
        OPEN_DISPS(play->state.gfxCtx);

        sp28 = POLY_OPA_DISP;
        sp2C = Graph_GfxPlusOne(sp28);

        gSPDisplayList(D_801F4F38, sp2C);

        func_800FDC94(play, &sp2C);

        gSPEndDisplayList(sp2C++);

        Graph_BranchDlist(sp28, sp2C);

        POLY_OPA_DISP = sp2C;
        D_801F4F38 = NULL;

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void Environment_StopTime(void) {
    D_801F4F32 = 1;
}

void Environment_StartTime(void) {
    D_801F4F32 = 0;
}

u8 Environment_IsTimeStopped(void) {
    return D_801F4F32;
}

u32 func_800FE4B8(PlayState* play) {
    u32 ret;

    ret = play->envCtx.unk_E2;
    if ((play->sceneId == SCENE_OMOYA) && (play->roomCtx.curRoom.num == 0)) {
        ret = ((gSaveContext.save.day >= 2) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_DEFENDED_AGAINST_THEM)) ? 1 : 0;
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
            ret = 0;
        }
        break;
    case SCENE_10YUKIYAMANOMURA2:
        if (gSaveContext.sceneLayer == 1) {
            ret = 0;
        }
        break;
    }

    return ret;
}

u8 func_800FE590(PlayState* play) {
    u8 phi_v1 = 0;

    if ((gSaveContext.save.day == 3) && (gSaveContext.save.time < 0x4000)) {
        phi_v1 = 1;
    }

    return phi_v1;
}

u8 func_800FE5D0(PlayState* play) {
    u8 phi_v1 = 0;

    if (Entrance_GetSceneId(((void)0, gSaveContext.save.entrance)) < 0) {
        phi_v1 = 1;
    }

    return phi_v1;
}

u32 func_800FE610(PlayState* play) {
    return 0;
}

u16 func_800FE620(PlayState *play) {
    u16 phi_v1 = 0;

    if (gRegEditor->data[0xF] != 0) {
		// TODO figure out gSaveContext.unk_16
        phi_v1 =  gRegEditor->data[0xF] + ((void)0, *(u16*)((u8*)&gSaveContext + 0x16));
    }

    return phi_v1;
}

void func_800FE658(f32 arg0) {
    D_801BDB9C = arg0 * D_801DDA7C;
}

u8 func_800FE6F8(PlayState* play, s16 arg1, s16 arg2) {
    u16 temp_v0;
    u8 phi_v1 = 0;

    if (gRegEditor->data[0xF] != 0) {
        temp_v0 = ((void)0, gSaveContext.save.time) + (gRegEditor->data[0xF] + ((void)0, gSaveContext.save.timeSpeedOffset)) * arg1 * 20;
        if (arg2 < temp_v0) {
            phi_v1 = 1;
        }
    }

    return phi_v1;
}

u8 func_800FE778() {
    return D_801BDBA0;
}

u8 func_800FE788() {
    return D_801BDBA4;
}

f32 func_800FE798() {
    return D_801BDB90;
}

void func_800FE7A8(Color_RGBA8 *arg0, Color_RGBA8 *arg1) {
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
    u8 phi_a1;

    phi_a1 = 0;
    if ((play->envCtx.unk_F2[4] == 0x3C) && (play->envCtx.unk_F2[2] == 0)) {
        phi_a1 = 1;
    }

    if ((play->envCtx.unk_F2[0] == 0x3C) && ((GET_ACTIVE_CAM(play)->stateFlags & CAM_STATE_UNDERWATER) == 0)) {
        if ((func_800FE4B8(play) != 0) && (play->envCtx.unk_F2[2] == 0)) {
            phi_a1 = 1;
        }
    }

    return phi_a1;
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
    D_801F4F33 = 1;
}

void func_800FEAB0() {
    D_801F4F33 = 0;
}

void func_800FEAC0(void) {
    if (D_801BDB9C != 0) {
        gSaveContext.save.time = ((void)0, gSaveContext.save.time) + D_801BDB9C;
        D_801BDB9C = 0;
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
