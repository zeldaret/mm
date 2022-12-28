#include "prevent_bss_reordering.h"
#include "global.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "z64shrink_window.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"

void CutsceneHandler_DoNothing(PlayState* play, CutsceneContext* csCtx);
void CutsceneHandler_StartManual(PlayState* play, CutsceneContext* csCtx);
void CutsceneHandler_StopManual(PlayState* play, CutsceneContext* csCtx);
void CutsceneHandler_StartScript(PlayState* play, CutsceneContext* csCtx);
void CutsceneHandler_RunScript(PlayState* play, CutsceneContext* csCtx);
void CutsceneHandler_StopScript(PlayState* play, CutsceneContext* csCtx);
void Cutscene_SetupScripted(PlayState* play, CutsceneContext* csCtx);

// Unused
UNK_TYPE4 D_801BB120 = 0;
u16 sCurTextId = 0;
u16 sCurOcarinaAction = 0;
u8 D_801BB12C = 0;
u8 sCutsceneStoredPlayerForm = 0;

// bss
#ifndef NON_MATCHING
static u16 sSeqId;
#endif
s16 sCutsceneQuakeIndex;
CutsceneCamera sCutsceneCameraInfo;
u16 sCueTypeList[10];
UNK_TYPE D_801F4DDC;
u8 D_801F4DE0;
s16 gDungeonBossWarpSceneId;

void Cutscene_InitContext(PlayState* play, CutsceneContext* csCtx) {
    s32 i;

    csCtx->state = CS_STATE_IDLE;
    csCtx->curFrame = 0;
    csCtx->timer = 0.0f;
    play->csCtx.scriptListCount = 0;
    play->csCtx.scriptIndex = 0;

    for (i = 0; i < ARRAY_COUNT(sCueTypeList); i++) {
        sCueTypeList[i] = 0;
    }

    D_801F4DE0 = 0;

    Audio_SetCutsceneFlag(false);
}

void Cutscene_StartManual(PlayState* play, CutsceneContext* csCtx) {
    csCtx->state = CS_STATE_START;
    csCtx->playerCue = NULL;
}

void Cutscene_StopManual(PlayState* play, CutsceneContext* csCtx) {
    if (csCtx->state != CS_STATE_RUN_UNSTOPPABLE) {
        csCtx->state = CS_STATE_STOP;
    }
}

typedef void (*CutsceneHandler)(PlayState* play, CutsceneContext* csCtx);

CutsceneHandler sManualCutsceneHandlers[] = {
    CutsceneHandler_DoNothing,   // CS_STATE_IDLE
    CutsceneHandler_StartManual, // CS_STATE_START
    CutsceneHandler_DoNothing,   // CS_STATE_RUN
    CutsceneHandler_StopManual,  // CS_STATE_STOP
    CutsceneHandler_DoNothing,   // CS_STATE_RUN_UNSTOPPABLE
};

void Cutscene_UpdateManual(PlayState* play, CutsceneContext* csCtx) {
    if (gSaveContext.save.cutscene < 0xFFF0) {
        sManualCutsceneHandlers[csCtx->state](play, csCtx);
    }
}

CutsceneHandler sScriptedCutsceneHandlers[] = {
    CutsceneHandler_DoNothing,   // CS_STATE_IDLE
    CutsceneHandler_StartScript, // CS_STATE_START
    CutsceneHandler_RunScript,   // CS_STATE_RUN
    CutsceneHandler_StopScript,  // CS_STATE_STOP
    CutsceneHandler_RunScript,   // CS_STATE_RUN_UNSTOPPABLE
};

void Cutscene_UpdateScripted(PlayState* play, CutsceneContext* csCtx) {
    if ((gSaveContext.cutsceneTrigger != 0) && (play->transitionTrigger == TRANS_TRIGGER_START)) {
        gSaveContext.cutsceneTrigger = 0;
    }

    if ((gSaveContext.cutsceneTrigger != 0) && (csCtx->state == CS_STATE_IDLE)) {
        gSaveContext.save.cutscene = 0xFFFD;
        gSaveContext.cutsceneTrigger = 1;
    }

    if (gSaveContext.save.cutscene >= 0xFFF0) {
        Cutscene_SetupScripted(play, csCtx);
        sScriptedCutsceneHandlers[csCtx->state](play, csCtx);
    }
}

void CutsceneHandler_DoNothing(PlayState* play, CutsceneContext* csCtx) {
}

s32 Cutscene_StepTimer(PlayState* play, CutsceneContext* csCtx, f32 target) {
    return Math_StepToF(&csCtx->timer, target, 0.1f);
}

void CutsceneHandler_StartManual(PlayState* play, CutsceneContext* csCtx) {
    Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
    ShrinkWindow_Letterbox_SetSizeTarget(32);

    if (Cutscene_StepTimer(play, csCtx, 1.0f)) {
        Audio_SetCutsceneFlag(true);
        csCtx->state++; // CS_STATE_RUN
    }
}

void CutsceneHandler_StartScript(PlayState* play, CutsceneContext* csCtx) {
    CutsceneHandler_RunScript(play, csCtx);
    Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
    ShrinkWindow_Letterbox_SetSizeTarget(32);

    if (Cutscene_StepTimer(play, csCtx, 1.0f)) {
        Audio_SetCutsceneFlag(true);
        csCtx->state++; // CS_STATE_RUN
    }
}

/* Start of command handling section */

// Command 0x96: Miscellaneous commands.
void CutsceneCmd_Misc(PlayState* play, CutsceneContext* csCtx, CsCmdMisc* cmd) {
    static u16 D_801BB15C = 0xFFFF;
    Player* player = GET_PLAYER(play);
    f32 lerp;
    u8 isFirstFrame = false;
    SceneTableEntry* loadedScene;

    if (!((csCtx->curFrame >= cmd->startFrame) &&
          ((csCtx->curFrame < cmd->endFrame) || (cmd->endFrame == cmd->startFrame)))) {
        return;
    }

    lerp = Environment_LerpWeight(cmd->endFrame - 1, cmd->startFrame, csCtx->curFrame);

    if (csCtx->curFrame == cmd->startFrame) {
        isFirstFrame = true;
    }

    switch (cmd->type) {
        case CS_MISC_STORM:
            if (isFirstFrame) {
                func_800FD78C(play);
                play->envCtx.unk_F2[0] = 60;
            }
            break;

        case CS_MISC_LIGHTNING:
            if (isFirstFrame) {
                Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_0, 0);
                Environment_AddLightningBolts(play, 3);
                D_801F4E68 = 1;
            }
            break;

        case CS_MISC_LIFT_FOG:
            if (play->envCtx.lightSettings.fogFar < 12800) {
                play->envCtx.lightSettings.fogFar += 35;
            }
            break;

        case CS_MISC_CLOUDY_SKY:
            if (isFirstFrame) {
                play->envCtx.unk_19 = 1;
                play->envCtx.unk_17 = 1;
                play->envCtx.unk_18 = 0;
                play->envCtx.unk_1A = 0x3C;
                play->envCtx.unk_21 = 1;
                play->envCtx.unk_1F = 0;
                play->envCtx.unk_20 = 1;
                play->envCtx.unk_24 = 0x3C;
                play->envCtx.unk_22 = play->envCtx.unk_24;
            }
            break;

        case CS_MISC_STOP_CUTSCENE:
            if (isFirstFrame && (csCtx->state != CS_STATE_RUN_UNSTOPPABLE)) {
                csCtx->state = CS_STATE_STOP;
            }
            break;

        case CS_MISC_SHOW_TITLE_CARD:
            if (isFirstFrame) {
                loadedScene = play->loadedScene;
                if (loadedScene->titleTextId != 0) {
                    func_80151A68(play, loadedScene->titleTextId);
                }
            }
            break;

        case CS_MISC_MEDIUM_QUAKE_START:
            func_8019F128(NA_SE_EV_EARTHQUAKE_LAST - SFX_FLAG);
            if (isFirstFrame) {
                sCutsceneQuakeIndex = Quake_Add(GET_ACTIVE_CAM(play), QUAKE_TYPE_6);
                Quake_SetSpeed(sCutsceneQuakeIndex, 22000);
                Quake_SetQuakeValues(sCutsceneQuakeIndex, 6, 4, 0, 0);
                Quake_SetCountdown(sCutsceneQuakeIndex, 800);
            }
            break;

        case CS_MISC_QUAKE_STOP:
            if (isFirstFrame) {
                Quake_Init();
            }
            break;

        case CS_MISC_VISMONO_BLACK_AND_WHITE:
            gVisMonoColor.r = 255;
            gVisMonoColor.g = 255;
            gVisMonoColor.b = 255;
            gVisMonoColor.a = 255 * lerp;
            break;

        case CS_MISC_VISMONO_SEPIA:
            gVisMonoColor.r = 255;
            gVisMonoColor.g = 180;
            gVisMonoColor.b = 100;
            gVisMonoColor.a = 255 * lerp;
            break;

        case CS_MISC_HIDE_ROOM:
            play->roomCtx.curRoom.segment = NULL;
            break;

        case CS_MISC_RED_PULSATING_LIGHTS:
            if (play->state.frames & 8) {
                if (play->envCtx.lightSettings.ambientColor[0] < 40) {
                    play->envCtx.lightSettings.ambientColor[0] += 2;
                    play->envCtx.lightSettings.diffuseColor1[1] -= 3;
                    play->envCtx.lightSettings.diffuseColor1[2] -= 3;
                }
            } else {
                if (play->envCtx.lightSettings.ambientColor[0] > 2) {
                    play->envCtx.lightSettings.ambientColor[0] -= 2;
                    play->envCtx.lightSettings.diffuseColor1[1] += 3;
                    play->envCtx.lightSettings.diffuseColor1[2] += 3;
                }
            }
            break;

        case CS_MISC_HALT_ALL_ACTORS:
            play->unk_18845 = 1;
            break;

        case CS_MISC_RESUME_ALL_ACTORS:
            play->unk_18845 = 0;
            break;

        case CS_MISC_SANDSTORM_FILL:
            if (isFirstFrame) {
                play->envCtx.sandstormState = 1;
            }
            func_8019F128(NA_SE_EV_SAND_STORM - SFX_FLAG);
            break;

        case CS_MISC_SUNSSONG_START:
            gSaveContext.sunsSongState = SUNSSONG_START;
            break;

        case CS_MISC_FREEZE_TIME:
            if (!gSaveContext.save.isNight) {
                gSaveContext.save.time = ((void)0, gSaveContext.save.time) - (u16)R_TIME_SPEED;
            } else {
                gSaveContext.save.time = ((void)0, gSaveContext.save.time) - (u16)(2 * R_TIME_SPEED);
            }
            break;

        case CS_MISC_LONG_SCARECROW_SONG:
            AudioOcarina_PlayLongScarecrowSong();
            csCtx->curFrame = cmd->startFrame - 1;
            break;

        case CS_MISC_SET_CSFLAG_3:
            CutsceneFlags_Set(play, 3);
            break;

        case CS_MISC_SET_CSFLAG_4:
            CutsceneFlags_Set(play, 4);
            break;

        case CS_MISC_PLAYER_FORM_DEKU:
            gSaveContext.save.playerForm = PLAYER_FORM_DEKU;
            break;

        case CS_MISC_ENABLE_PLAYER_REFLECTION:
            player->stateFlags2 |= PLAYER_STATE2_4000000;
            break;

        case CS_MISC_DISABLE_PLAYER_REFLECTION:
            player->stateFlags2 &= ~PLAYER_STATE2_4000000;
            break;

        case CS_MISC_PLAYER_FORM_HUMAN:
            sCutsceneStoredPlayerForm = gSaveContext.save.playerForm;
            gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
            gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
            break;

        case CS_MISC_STRONG_QUAKE_START:
            func_8019F128(NA_SE_EV_EARTHQUAKE_LAST2 - SFX_FLAG);
            if (isFirstFrame) {
                sCutsceneQuakeIndex = Quake_Add(GET_ACTIVE_CAM(play), QUAKE_TYPE_6);
                Quake_SetSpeed(sCutsceneQuakeIndex, 30000);
                Quake_SetQuakeValues(sCutsceneQuakeIndex, 20, 10, 0, 0);
                Quake_SetCountdown(sCutsceneQuakeIndex, 800);
            }
            break;

        case CS_MISC_1B:
            if (isFirstFrame) {
                play->nextEntrance = ENTRANCE(CUTSCENE, 0);
                gSaveContext.nextCutsceneIndex = 0xFFF8;
                play->transitionTrigger = TRANS_TRIGGER_START;
                play->transitionType = TRANS_TYPE_03;
            }
            break;

        case CS_MISC_1C:
            if (isFirstFrame) {
                // skyboxConfig
                play->envCtx.unk_17 = 0xD;
            }
            break;

        case CS_MISC_PLAYER_FORM_RESTORED:
            gSaveContext.save.playerForm = sCutsceneStoredPlayerForm;
            break;

        case CS_MISC_1E:
            D_801F4DE0 = true;
            break;

        case CS_MISC_1F:
            D_801F4DE0 = false;
            break;

        case CS_MISC_SPECIAL_SAVE:
            if (isFirstFrame) {
                Sram_SaveSpecialEnterClockTown(play);
            }
            break;

        case CS_MISC_SAVE:
            if (isFirstFrame) {
                func_80144A94(&play->sramCtx);
            }
            break;

        case CS_MISC_TIME_ADVANCE:
            if (csCtx->curFrame != D_801BB15C) {
                D_801BB15C = csCtx->curFrame;

                if (R_TIME_SPEED != 0) {
                    gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)R_TIME_SPEED;
                    gSaveContext.save.time =
                        ((void)0, gSaveContext.save.time) + (u16)((void)0, gSaveContext.save.timeSpeedOffset);
                }
            }
            break;

        case CS_MISC_WEAK_QUAKE_START:
            func_8019F128(NA_SE_EV_EARTHQUAKE_LAST - SFX_FLAG);
            if (isFirstFrame) {
                sCutsceneQuakeIndex = Quake_Add(GET_ACTIVE_CAM(play), QUAKE_TYPE_6);
                Quake_SetSpeed(sCutsceneQuakeIndex, 22000);
                Quake_SetQuakeValues(sCutsceneQuakeIndex, 2, 1, 0, 0);
                Quake_SetCountdown(sCutsceneQuakeIndex, 800);
            }
            break;

        case CS_MISC_DAWN_OF_A_NEW_DAY:
            gSaveContext.save.day = 9;

            STOP_GAMESTATE(&play->state);
            SET_NEXT_GAMESTATE(&play->state, DayTelop_Init, sizeof(DayTelopState));

            Sram_SaveSpecialNewDay(play);
            break;

        case CS_MISC_PLAYER_FORM_ZORA:
            gSaveContext.save.playerForm = PLAYER_FORM_ZORA;
            break;

        case CS_MISC_FOREVER:
            csCtx->curFrame = cmd->startFrame - 1; // the cutscene runs forever
            break;

        default:
            break;
    }
}

void CutsceneCmd_SetLightSetting(PlayState* play, CutsceneContext* csCtx, CsCmdLightSetting* cmd) {
    if (csCtx->curFrame == cmd->startFrame) {
        if (cmd->setting != 0x20) {
            play->envCtx.lightSettingOverride = cmd->setting - 1;
            play->envCtx.lightBlend = 1.0f;
        } else {
            play->envCtx.lightSettingOverride = 0xFF;
        }
    }
}

void CutsceneCmd_StartSequence(PlayState* play, CutsceneContext* csCtx, CsCmdStartSeq* cmd) {
    if (csCtx->curFrame == cmd->startFrame) {
        Audio_PlaySequenceInCutscene(cmd->sequence - 1);
    }
}

void CutsceneCmd_StopSequence(PlayState* play, CutsceneContext* csCtx, CsCmdStartSeq* cmd) {
    if ((csCtx->curFrame >= cmd->startFrame) && (cmd->endFrame >= csCtx->curFrame)) {
        Audio_StopSequenceInCutscene(cmd->sequence - 1);
    }
}

// Command 0x9C: Fade a sequence (Background music or Fanfare) over duration
void CutsceneCmd_FadeOutSequence(PlayState* play, CutsceneContext* csCtx, CsCmdSequenceFade* cmd) {
    if ((csCtx->curFrame == cmd->startFrame) && (csCtx->curFrame < cmd->endFrame)) {
        u8 fadeOutDuration = cmd->endFrame - cmd->startFrame;

        if (cmd->type == CS_FADE_OUT_FANFARE) {
            Audio_QueueSeqCmd((fadeOutDuration << 0x10) | 0x110000FF);
        } else { // CS_FADE_OUT_BGM_MAIN
            Audio_QueueSeqCmd((fadeOutDuration << 0x10) | NA_BGM_STOP);
        }
    }
}

// Command 0x12E: Play Ambience sequence
void CutsceneCmd_StartAmbience(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->curFrame == cmd->startFrame) {
        Audio_PlayAmbience(play->sequenceCtx.ambienceId);
    }
}

// Command 0x130:
void Cutscene_SetSfxReverbIndexTo2(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->curFrame == cmd->startFrame) {
        // Audio_SetSfxReverbIndexExceptOcarinaBank
        func_801A4428(2);
    }
}

// Command 0x131:
void Cutscene_SetSfxReverbIndexTo1(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->curFrame == cmd->startFrame) {
        // Audio_SetSfxReverbIndexExceptOcarinaBank
        func_801A4428(1);
    }
}

#ifdef NON_MATCHING
// needs in-function static bss
// audio related
void CutsceneCmd_ModifySequence(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    static u16 sSeqId;
    u8 dayMinusOne;

    if (csCtx->curFrame == cmd->startFrame) {
        dayMinusOne = (gSaveContext.save.day - 1);
        if (dayMinusOne >= 3) {
            dayMinusOne = 0;
        }

        switch (cmd->base) {
            case 1:
                // func_801A246C(SEQ_PLAYER_BGM_MAIN, TYPE_1);
                func_801A246C(SEQ_PLAYER_BGM_MAIN, 1);
                break;

            case 2:
                // func_801A246C(SEQ_PLAYER_BGM_MAIN, TYPE_0);
                func_801A246C(SEQ_PLAYER_BGM_MAIN, 0);
                break;

            case 3:
                // func_801A246C(SEQ_PLAYER_BGM_MAIN, TYPE_2);
                func_801A246C(SEQ_PLAYER_BGM_MAIN, 2);
                break;

            case 4:
                // func_801A246C(SEQ_PLAYER_AMBIENCE, TYPE_1);
                func_801A246C(SEQ_PLAYER_AMBIENCE, 1);
                break;

            case 5:
                // func_801A246C(SEQ_PLAYER_AMBIENCE, TYPE_0);
                func_801A246C(SEQ_PLAYER_AMBIENCE, 0);
                break;

            case 6:
                // func_801A246C(SEQ_PLAYER_AMBIENCE, TYPE_2);
                func_801A246C(SEQ_PLAYER_AMBIENCE, 2);
                break;

            case 7:
                sSeqId = Audio_GetActiveSequence(SEQ_PLAYER_BGM_MAIN);
                break;

            case 8:
                if (sSeqId != NA_BGM_DISABLED) {
                    Audio_PlaySceneSequence(sSeqId, dayMinusOne);
                }
                break;
        }
    }
}
#else
void CutsceneCmd_ModifySequence(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/CutsceneCmd_ModifySequence.s")
#endif

void CutsceneCmd_FadeOutAmbience(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->curFrame == cmd->startFrame) && (csCtx->curFrame < cmd->endFrame)) {
        u8 fadeOutDuration = cmd->endFrame - cmd->startFrame;

        Audio_QueueSeqCmd((fadeOutDuration << 0x10) | 0x140000FF);
    }
}

void CutsceneCmd_RumbleController(PlayState* play, CutsceneContext* csCtx, CsCmdRumble* cmd) {
    switch (cmd->type) {
        case 1:
            if (csCtx->curFrame == cmd->startFrame) {
                Rumble_Request(0.0f, cmd->intensity, cmd->decayTimer, cmd->decayStep);
            }
            break;

        case 2:
            if ((csCtx->curFrame >= cmd->startFrame) && (cmd->endFrame >= csCtx->curFrame)) {
                if ((csCtx->curFrame == cmd->startFrame) || (play->state.frames % 64 == 0)) {
                    Rumble_Request(0.0f, cmd->intensity, cmd->decayTimer, cmd->decayStep);
                }
            }
            break;

        default:
            break;
    }
}

// Command 0x9B:
void CutsceneCmd_FadeColorScreen(PlayState* play, CutsceneContext* csCtx, CsCmdFadeScreen* cmd) {
    if ((csCtx->curFrame >= cmd->startFrame) && (cmd->endFrame >= csCtx->curFrame)) {
        f32 alpha;

        play->envCtx.fillScreen = true;
        alpha = Environment_LerpWeight(cmd->endFrame, cmd->startFrame, csCtx->curFrame);

        if (((cmd->unk0 == 1)) || (cmd->unk0 == 2)) {
            play->envCtx.screenFillColor[0] = cmd->color.r;
            play->envCtx.screenFillColor[1] = cmd->color.g;
            play->envCtx.screenFillColor[2] = cmd->color.b;

            if (cmd->unk0 == 2) {
                play->envCtx.screenFillColor[3] = (1.0f - alpha) * 255.0f;
            } else {
                play->envCtx.screenFillColor[3] = 255.0f * alpha;
            }
        }
    }
}

// Command 0x9D: Set Time of Day & Environment Time
void CutsceneCmd_SetTime(PlayState* play, CutsceneContext* csCtx, CsCmdDayTime* cmd) {
    u16 nextTime;
    u16 hourAsMinutes;
    u16 minutes;

    if (csCtx->curFrame == cmd->startFrame) {
        hourAsMinutes = CLOCK_TIME_ALT_F(cmd->hour, 0);
        minutes = CLOCK_TIME_ALT_F(0, cmd->minute + 1);

        nextTime = hourAsMinutes + minutes;
        gSaveContext.save.time = nextTime;
        gSaveContext.skyboxTime = nextTime;
    }
}

void CutsceneCmd_DestinationImpl(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    csCtx->state = CS_STATE_RUN_UNSTOPPABLE;
    func_80165690();
    Audio_SetCutsceneFlag(false);
    gSaveContext.cutsceneTransitionControl = 1;

    // `hudVisibilityForceButtonAlphasByStatus` has a secondary purpose, which is to signal to the title
    // screen actor that it should display immediately. This occurs when a title screen cutscene that
    // is not the main clock town scene is skipped.
    if ((gSaveContext.gameMode != 0) && (csCtx->curFrame != cmd->startFrame)) {
        gSaveContext.hudVisibilityForceButtonAlphasByStatus = true;
    }

    gSaveContext.save.cutscene = 0;

    if (cmd->base == 1) {
        play->nextEntrance = play->csCtx.scriptList[play->csCtx.scriptIndex].nextEntrance;
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        if (gSaveContext.gameMode != 1) {
            Scene_SetExitFade(play);
        } else {
            D_801BB12C++;
            if (D_801BB12C >= 2) {
                D_801BB12C = 0;
            }
            play->transitionType = TRANS_TYPE_04;
        }

        if ((play->nextEntrance & 0xF) > 0) {
            gSaveContext.nextCutsceneIndex = (play->nextEntrance & 0xF) + 0xFFEF;
        }

        play->nextEntrance &= ~0xF;
    }
}

void CutsceneCmd_Destination(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (cmd->base == 1) {
        if (csCtx->curFrame == cmd->startFrame) {
            CutsceneCmd_DestinationImpl(play, csCtx, cmd);
        }
    } else if (cmd->base == 2) {
        if (csCtx->curFrame == cmd->startFrame) {
            func_80165690();

            switch (gDungeonBossWarpSceneId) {
                case SCENE_MITURIN_BS:
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_20_02)) {
                        play->nextEntrance = ENTRANCE(WOODFALL_TEMPLE, 1);
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_03;
                    } else {
                        play->nextEntrance = ENTRANCE(WOODFALL, 0);
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_03;
                    }
                    break;

                case SCENE_HAKUGIN_BS:
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_33_80)) {
                        play->nextEntrance = ENTRANCE(MOUNTAIN_VILLAGE_SPRING, 7);
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_03;
                    } else {
                        play->nextEntrance = ENTRANCE(MOUNTAIN_VILLAGE_SPRING, 0);
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_03;
                    }
                    break;

                case SCENE_SEA_BS:
                    SET_WEEKEVENTREG(WEEKEVENTREG_55_80);
                    play->nextEntrance = ENTRANCE(ZORA_CAPE, 8);
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                    play->transitionTrigger = TRANS_TRIGGER_START;
                    play->transitionType = TRANS_TYPE_03;
                    break;

                case SCENE_INISIE_BS:
                    SET_WEEKEVENTREG(WEEKEVENTREG_52_20);
                    play->nextEntrance = ENTRANCE(IKANA_CANYON, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                    play->transitionTrigger = TRANS_TRIGGER_START;
                    play->transitionType = TRANS_TYPE_03;
                    break;

                default:
                    break;
            }
        }
    }
}

// Command 0x15F: Chooses between a cutscene or a rotating mask depending on whether the player has the corresponding
// mask
void CutsceneCmd_ChooseCreditsScenes(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->curFrame >= cmd->startFrame) && (func_801A3950(SEQ_PLAYER_BGM_MAIN, true) != 0xFF)) {
        switch (cmd->base) {
            case 1:
                CutsceneCmd_DestinationImpl(play, csCtx, cmd);
                break;

            case 2:
                if (INV_CONTENT(ITEM_MASK_KAMARO) == ITEM_MASK_KAMARO) {
                    play->nextEntrance = ENTRANCE(MILK_BAR, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 3:
                if (INV_CONTENT(ITEM_MASK_GREAT_FAIRY) == ITEM_MASK_GREAT_FAIRY) {
                    play->nextEntrance = ENTRANCE(FAIRY_FOUNTAIN, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 1);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 4:
                if (INV_CONTENT(ITEM_MASK_ROMANI) == ITEM_MASK_ROMANI) {
                    play->nextEntrance = ENTRANCE(ROMANI_RANCH, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 2);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 5:
                if (INV_CONTENT(ITEM_MASK_BLAST) == ITEM_MASK_BLAST) {
                    play->nextEntrance = ENTRANCE(WEST_CLOCK_TOWN, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 3);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 6:
                if (INV_CONTENT(ITEM_MASK_CIRCUS_LEADER) == ITEM_MASK_CIRCUS_LEADER) {
                    play->nextEntrance = ENTRANCE(MILK_BAR, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 5);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 7:
                if (INV_CONTENT(ITEM_MASK_BREMEN) == ITEM_MASK_BREMEN) {
                    play->nextEntrance = ENTRANCE(MILK_BAR, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF3;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 6);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 8:
                play->nextEntrance = ENTRANCE(IKANA_CANYON, 0);
                gSaveContext.nextCutsceneIndex = 0xFFF3;
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 9:
                if (INV_CONTENT(ITEM_MASK_COUPLE) == ITEM_MASK_COUPLE) {
                    play->nextEntrance = ENTRANCE(TERMINA_FIELD, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF8;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 7);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 10:
                if (INV_CONTENT(ITEM_MASK_BUNNY) == ITEM_MASK_BUNNY) {
                    play->nextEntrance = ENTRANCE(CUCCO_SHACK, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 4);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;

            case 11:
                if (INV_CONTENT(ITEM_MASK_POSTMAN) == ITEM_MASK_POSTMAN) {
                    play->nextEntrance = ENTRANCE(TERMINA_FIELD, 1);
                    gSaveContext.nextCutsceneIndex = 0xFFF8;
                } else {
                    play->nextEntrance = ENTRANCE(CUTSCENE, 8);
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                play->transitionTrigger = TRANS_TRIGGER_START;
                break;
        }
    }
}

void CutsceneCmd_MotionBlur(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->curFrame >= cmd->startFrame) && (cmd->endFrame >= csCtx->curFrame)) {
        if ((csCtx->curFrame == cmd->startFrame) && (cmd->base == 1)) {
            func_8016566C(180);
        }

        if (cmd->base == 2) {
            f32 lerp = Environment_LerpWeight(cmd->endFrame, cmd->startFrame, csCtx->curFrame);

            if (lerp >= 0.9f) {
                func_80165690();
            } else {
                func_80165658((1.0f - lerp) * 180.0f);
            }
        }
    }
}

void CutsceneCmd_GiveTatlToPlayer(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    Player* player = GET_PLAYER(play);

    if (csCtx->curFrame == cmd->startFrame) {
        if (cmd->base == 1) {
            gSaveContext.save.hasTatl = true;
            if (player->tatlActor != NULL) {
                return;
            }
            player->tatlActor = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_ELF, player->actor.world.pos.x,
                                            player->actor.world.pos.y, player->actor.world.pos.z, 0, 0, 0, 0);
        }
    }
}

void CutsceneCmd_Transition(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->curFrame >= cmd->startFrame) && (cmd->endFrame >= csCtx->curFrame)) {
        f32 lerp;

        play->envCtx.fillScreen = true;
        lerp = Environment_LerpWeight(cmd->endFrame, cmd->startFrame, csCtx->curFrame);

        switch (cmd->base) {
            case CS_TRANS_GRAY_FILL_IN:
            case CS_TRANS_GRAY_FILL_OUT:
                play->envCtx.screenFillColor[0] = 160;
                play->envCtx.screenFillColor[1] = 160;
                play->envCtx.screenFillColor[2] = 160;

                if (cmd->base == CS_TRANS_GRAY_FILL_IN) {
                    play->envCtx.screenFillColor[3] = 255.0f * lerp;
                    if (lerp == 0.0f) {
                        func_8019F128(NA_SE_EV_S_STONE_FLASH);
                    }
                } else {
                    play->envCtx.screenFillColor[3] = (1.0f - lerp) * 255.0f;
                }
                break;

            case CS_TRANS_BLUE_FILL_IN:
            case CS_TRANS_BLUE_FILL_OUT:
                play->envCtx.screenFillColor[0] = 0;
                play->envCtx.screenFillColor[1] = 0;
                play->envCtx.screenFillColor[2] = 255;
                if (cmd->base == CS_TRANS_BLUE_FILL_IN) {
                    play->envCtx.screenFillColor[3] = 255.0f * lerp;
                } else {
                    play->envCtx.screenFillColor[3] = (1.0f - lerp) * 255.0f;
                }
                break;

            case CS_TRANS_RED_FILL_OUT:
            case CS_TRANS_RED_FILL_IN:
                play->envCtx.screenFillColor[0] = 255;
                play->envCtx.screenFillColor[1] = 0;
                play->envCtx.screenFillColor[2] = 0;
                if (cmd->base == CS_TRANS_RED_FILL_OUT) {
                    play->envCtx.screenFillColor[3] = (1.0f - lerp) * 255.0f;
                } else {
                    play->envCtx.screenFillColor[3] = 255.0f * lerp;
                }
                break;

            case CS_TRANS_GREEN_FILL_OUT:
            case CS_TRANS_GREEN_FILL_IN:
                play->envCtx.screenFillColor[0] = 0;
                play->envCtx.screenFillColor[1] = 255;
                play->envCtx.screenFillColor[2] = 0;
                if (cmd->base == CS_TRANS_GREEN_FILL_OUT) {
                    play->envCtx.screenFillColor[3] = (1.0f - lerp) * 255.0f;
                } else {
                    play->envCtx.screenFillColor[3] = 255.0f * lerp;
                }
                break;

            case CS_TRANS_TRIGGER_INSTANCE:
                gSaveContext.cutsceneTransitionControl = 1;
                break;

            case CS_TRANS_BLACK_FILL_OUT:
            case CS_TRANS_BLACK_FILL_IN:
                play->envCtx.screenFillColor[0] = 0;
                play->envCtx.screenFillColor[1] = 0;
                play->envCtx.screenFillColor[2] = 0;
                if (cmd->base == 10) {
                    play->envCtx.screenFillColor[3] = (1.0f - lerp) * 255.0f;
                } else {
                    play->envCtx.screenFillColor[3] = 255.0f * lerp;
                }
                break;

            case CS_TRANS_BLACK_C:
                play->envCtx.screenFillColor[0] = 160.0f * (1.0f - lerp);
                play->envCtx.screenFillColor[1] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[2] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[3] = 255;
                break;

            case CS_TRANS_BLACK_D:
                play->envCtx.screenFillColor[0] = 160.0f * lerp;
                play->envCtx.screenFillColor[1] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[2] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[3] = 255;
                break;

            default:
                break;
        }
    }
}

s32 CutsceneCmd_UpdateCamSpline(PlayState* play, u8* cmd) {
    s32 sp1C = 0;

    bcopy(cmd, &sp1C, sizeof(s32));
    cmd += sizeof(s32);
    if (!Play_IsDebugCamEnabled()) {
        CutsceneCamera_ProcessCommands(cmd, &sCutsceneCameraInfo);
    }
    return sp1C + sizeof(s32);
}

/**
 * Counts how many masks the player has
 * The count doesn't include transformation masks
 */
s32 Cutscene_CountNormalMasks(void) {
    s32 count = 0;

    if (INV_CONTENT(ITEM_MASK_TRUTH) == ITEM_MASK_TRUTH) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_KAFEIS_MASK) == ITEM_MASK_KAFEIS_MASK) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_ALL_NIGHT) == ITEM_MASK_ALL_NIGHT) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_BUNNY) == ITEM_MASK_BUNNY) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_KEATON) == ITEM_MASK_KEATON) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_GARO) == ITEM_MASK_GARO) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_ROMANI) == ITEM_MASK_ROMANI) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_CIRCUS_LEADER) == ITEM_MASK_CIRCUS_LEADER) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_POSTMAN) == ITEM_MASK_POSTMAN) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_COUPLE) == ITEM_MASK_COUPLE) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_GREAT_FAIRY) == ITEM_MASK_GREAT_FAIRY) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_GIBDO) == ITEM_MASK_GIBDO) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_DON_GERO) == ITEM_MASK_DON_GERO) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_KAMARO) == ITEM_MASK_KAMARO) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_CAPTAIN) == ITEM_MASK_CAPTAIN) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_STONE) == ITEM_MASK_STONE) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_BREMEN) == ITEM_MASK_BREMEN) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_BLAST) == ITEM_MASK_BLAST) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_SCENTS) == ITEM_MASK_SCENTS) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_GIANT) == ITEM_MASK_GIANT) {
        count++;
    }

    return count;
}

void CutsceneCmd_Text(PlayState* play, CutsceneContext* csCtx, CsCmdText* cmd) {
    static s32 D_801BB160 = CS_TEXTBOX_TYPE_DEFAULT;
    u8 talkState;
    s32 pad;
    u16 originalCsFrames;
    s32 pad2;

    if ((cmd->startFrame >= csCtx->curFrame) || ((cmd->endFrame < csCtx->curFrame))) {
        return;
    }

    if (cmd->type != CS_TEXT_OCARINA_ACTION) {
        if (sCurTextId != cmd->base) {
            if (D_801BB160 == CS_TEXTBOX_TYPE_3) {
                csCtx->curFrame--;
            }
            D_801BB160 = CS_TEXTBOX_TYPE_1;
            sCurTextId = cmd->base;
            if (cmd->type == CS_TEXTBOX_TYPE_BOSSES_REMAINS) {
                if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOLWA) && CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT) &&
                    CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG) && CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
                    if (cmd->textId1 != 0xFFFF) {
                        Message_StartTextbox(play, cmd->textId1, NULL);
                    }
                } else {
                    Message_StartTextbox(play, cmd->base, NULL);
                }
            } else if (cmd->type == CS_TEXTBOX_TYPE_ALL_NORMAL_MASKS) {
                if (Cutscene_CountNormalMasks() == 20) {
                    if (cmd->textId1 != 0xFFFF) {
                        Message_StartTextbox(play, cmd->textId1, NULL);
                    }
                } else {
                    Message_StartTextbox(play, cmd->base, NULL);
                }
            } else {
                Message_StartTextbox(play, cmd->base, NULL);
            }
        } else {
            goto else_label;
        }
    } else if (sCurOcarinaAction != cmd->base) {
        D_801BB160 = CS_TEXT_OCARINA_ACTION;
        sCurOcarinaAction = cmd->base;
        func_80152434(play, cmd->base);
    } else {
    else_label:
        if (csCtx->curFrame >= cmd->endFrame) {
            // The Textbox command can change the current cutscene frame, mainly to prevent advancing the cutscene when
            // a textbox that is expected to be closed by the user is still open.

            originalCsFrames = csCtx->curFrame;
            talkState = Message_GetState(&play->msgCtx);
            if ((talkState != TEXT_STATE_CLOSING) && (talkState != TEXT_STATE_NONE) && (talkState != TEXT_STATE_7) &&
                (talkState != TEXT_STATE_8)) {
                csCtx->curFrame--;
                if ((talkState == TEXT_STATE_CHOICE) && Message_ShouldAdvance(play)) {
                    if (play->msgCtx.choiceIndex == 0) {
                        if (cmd->base == 0x33BD) {
                            func_8019F230();
                        }

                        if (cmd->textId1 != 0xFFFF) {
                            func_80151938(play, cmd->textId1);
                            if (cmd->type == CS_TEXTBOX_TYPE_3) {
                                D_801BB160 = CS_TEXTBOX_TYPE_3;
                                if (cmd->textId2 != 0xFFFF) {
                                    csCtx->curFrame++;
                                }
                            }
                        } else {
                            func_801477B4(play);
                            csCtx->curFrame++;
                        }
                    } else {
                        if (cmd->base == 0x33BD) {
                            func_8019F208();
                        }

                        if (cmd->textId2 != 0xFFFF) {
                            func_80151938(play, cmd->textId2);
                            if (cmd->type == CS_TEXTBOX_TYPE_3) {
                                D_801BB160 = CS_TEXTBOX_TYPE_3;
                                if (cmd->textId1 != 0xFFFF) {
                                    csCtx->curFrame++;
                                }
                            }
                        } else {
                            func_801477B4(play);
                            csCtx->curFrame++;
                        }
                    }
                }

                if ((talkState == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
                    func_80152434(play, cmd->base);
                }
            }

            if ((talkState == TEXT_STATE_CLOSING) && (D_801BB160 == CS_TEXTBOX_TYPE_3)) {
                csCtx->curFrame--;
                sCurTextId++;
            }

            if (originalCsFrames == csCtx->curFrame) {
                Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
                sCurTextId = 0;
                sCurOcarinaAction = 0;
                func_80161C0C();
            } else {
                func_80161BE0(1);
            }
        }
    }
}

void Cutscene_SetActorCue(CutsceneContext* csCtx, u8** script, s16 cueChannel) {
    s32 i;
    s32 numCues;

    bcopy(*script, &numCues, sizeof(numCues));
    *script += sizeof(numCues);

    for (i = 0; i < numCues; i++) {
        CsCmdActorCue* cue = *(CsCmdActorCue**)script;

        if ((csCtx->curFrame >= cue->startFrame) && (csCtx->curFrame < cue->endFrame)) {
            csCtx->actorCues[cueChannel] = cue;
        }

        *script += sizeof(CsCmdActorCue);
    }
}

/**
 * Loops over the cutscene data itself (`script`), applying the effects of each command instantaneously (for most
 * commands).
 *
 * The cutscene data is an irregularly-structured array of words, which is made up of
 * - A beginning, which contains the number of command lists of this cutscene and the ending frame (see
 * `CS_BEGIN_CUTSCENE`).
 * - Any number of cutscene command lists (which should be the number specified in the beginning), each one of which
 * contains commands of the corresponding category.
 * - A end marker (see `CS_END`).
 *
 * This function iterates over each command list until either it has processed the number of command lists stated on
 * `CS_BEGIN_CUTSCENE` or until it finds a end marker.
 *
 * A command list starts with a pair of words containing the command category and a count of how many commands this list
 * has (N). This is followed by N commands of the said category. (The exception is Camera, which has the length of the
 * list in bytes instead of the number of commands).
 *
 * For most command lists categories (all but the actorCues and Camera commands):
 * - For each command list found, read the number of commands and loop over them, passing each one to the corresponding
 * function which handles the command, applying its effects and checking the frame range stored in the command.
 *
 * This function is invoked once per frame that a cutscene is active.
 *
 * TODO: consider changing the type of `script` to `uintptr_t` when this function matches.
 */
void Cutscene_ProcessScript(PlayState* play, CutsceneContext* csCtx, u8* script) {
    s32 i;
    s32 j;
    s32 pad;
    s32 totalEntries;
    u32 cmdType;
    s32 cmdEntries;
    s32 pad2;
    s32 csFrameCount;
    CsCmdBase* cmd;

    // Read the command list count and the ending frame for this cutscene
    bcopy(script, &totalEntries, sizeof(s32));
    script += sizeof(totalEntries);

    bcopy(script, &csFrameCount, sizeof(s32));
    script += sizeof(csFrameCount);

    if ((csCtx->curFrame > (u16)csFrameCount) && (play->transitionTrigger != TRANS_TRIGGER_START) &&
        (csCtx->state != CS_STATE_RUN_UNSTOPPABLE)) {
        csCtx->state = CS_STATE_STOP;
        return;
    }

    // Loop over every command list
    for (i = 0; i < totalEntries; i++) {
        // Read the command type of the current command list.
        bcopy(script, &cmdType, sizeof(cmdType));
        script += sizeof(u32);

        // TODO: This should probably be added to the CutsceneCmd enum. Consider doing it when this function matches.
        if (cmdType == 0xFFFFFFFF) {
            break;
        }

        // Check special cases of command types. This are generic ActorCues
        // Ranges: [0x64, 0x96), 0xC9, [0x1C2, 0x258)
        if (((cmdType >= CS_CMD_ACTOR_CUE_100) && (cmdType <= CS_CMD_ACTOR_CUE_149)) ||
            (cmdType == CS_CMD_ACTOR_CUE_201) ||
            ((cmdType >= CS_CMD_ACTOR_CUE_450) && (cmdType <= CS_CMD_ACTOR_CUE_599))) {
            for (j = 0; j < ARRAY_COUNT(sCueTypeList); j = (s16)(j + 1)) {
                if (sCueTypeList[j] == (u16)cmdType) {
                    Cutscene_SetActorCue(csCtx, &script, j);
                    cmdType = -2;
                    break;
                }

                if (sCueTypeList[j] == 0) {
                    sCueTypeList[j] = cmdType;
                    Cutscene_SetActorCue(csCtx, &script, j);
                    cmdType = -2;
                    break;
                }
            }
        }

        switch (cmdType) {
            case CS_CMD_MISC:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_Misc(play, csCtx, (void*)script);
                    script += sizeof(CsCmdMisc);
                }
                break;

            case CS_CMD_LIGHT_SETTING:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_SetLightSetting(play, csCtx, (CsCmdLightSetting*)script);
                    script += sizeof(CsCmdLightSetting);
                }
                break;

            case CS_CMD_START_SEQ:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_StartSequence(play, csCtx, (CsCmdStartSeq*)script);
                    script += sizeof(CsCmdStartSeq);
                }
                break;

            case CS_CMD_STOP_SEQ:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_StopSequence(play, csCtx, (CsCmdStartSeq*)script);
                    script += sizeof(CsCmdStartSeq);
                }
                break;

            case CS_CMD_FADE_OUT_SEQ:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_FadeOutSequence(play, csCtx, (CsCmdSequenceFade*)script);
                    script += sizeof(CsCmdSequenceFade);
                }
                break;

            case CS_CMD_START_AMBIENCE:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_StartAmbience(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_FADE_OUT_AMBIENCE:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_FadeOutAmbience(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_SFX_REVERB_INDEX_2:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_SetSfxReverbIndexTo2(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_SFX_REVERB_INDEX_1:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_SetSfxReverbIndexTo1(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_MODIFY_SEQ:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_ModifySequence(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_RUMBLE:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_RumbleController(play, csCtx, (CsCmdRumble*)script);
                    script += sizeof(CsCmdRumble);
                }
                break;

            case CS_CMD_FADE_SCREEN:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_FadeColorScreen(play, csCtx, (CsCmdFadeScreen*)script);
                    script += sizeof(CsCmdFadeScreen);
                }
                break;

            case CS_CMD_TIME:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_SetTime(play, csCtx, (CsCmdDayTime*)script);
                    script += sizeof(CsCmdDayTime);
                }
                break;

            case CS_CMD_PLAYER_CUE:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    cmd = (CsCmdBase*)script;
                    if ((cmd->startFrame <= csCtx->curFrame) && (csCtx->curFrame < cmd->endFrame)) {
                        csCtx->playerCue = (CsCmdActorCue*)cmd;
                    }
                    script += sizeof(CsCmdActorCue);
                }
                break;

            case CS_CMD_CAMERA_SPLINE:
                script += CutsceneCmd_UpdateCamSpline(play, script);
                break;

            case CS_CMD_DESTINATION:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_Destination(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_CHOOSE_CREDITS_SCENES:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_ChooseCreditsScenes(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_TEXT:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    cmd = (CsCmdBase*)script;
                    if (cmd->base != 0xFFFF) {
                        CutsceneCmd_Text(play, csCtx, (CsCmdText*)cmd);
                    }
                    script += sizeof(CsCmdText);
                }
                break;

            case CS_CMD_TRANSITION:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_Transition(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_MOTION_BLUR:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_MotionBlur(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_GIVE_TATL:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    CutsceneCmd_GiveTatlToPlayer(play, csCtx, (CsCmdBase*)script);
                    script += sizeof(CsCmdBase);
                }
                break;

            case -2:
                break;

            default:
                bcopy(script, &cmdEntries, sizeof(cmdEntries));
                script += sizeof(cmdEntries);

                for (j = 0; j < cmdEntries; j++) {
                    script += sizeof(CsCmdBase);
                }
                break;
        }
    }
}

/* End of command handling section */

void CutsceneHandler_RunScript(PlayState* play, CutsceneContext* csCtx) {
    if (gSaveContext.save.cutscene >= 0xFFF0) {
        csCtx->curFrame++;
        Cutscene_ProcessScript(play, csCtx, (u8*)play->csCtx.script);
    }
}

void CutsceneHandler_StopManual(PlayState* play, CutsceneContext* csCtx) {
    if (Cutscene_StepTimer(play, csCtx, 0.0f)) {
        Audio_SetCutsceneFlag(false);
        csCtx->state = CS_STATE_IDLE;
    }
}

void CutsceneHandler_StopScript(PlayState* play, CutsceneContext* csCtx) {
    if (Cutscene_StepTimer(play, csCtx, 0.0f)) {
        s16 i;

        csCtx->playerCue = NULL;

        for (i = 0; i < ARRAY_COUNT(csCtx->actorCues); i++) {
            csCtx->actorCues[i] = NULL;
        }

        gSaveContext.save.cutscene = 0;
        gSaveContext.gameMode = 0;

        ActorCutscene_Stop(0x7F);
        Audio_SetCutsceneFlag(false);
        csCtx->state = CS_STATE_IDLE;
    }
}

void Cutscene_SetupScripted(PlayState* play, CutsceneContext* csCtx) {
    if ((gSaveContext.cutsceneTrigger != 0) && (csCtx->state == CS_STATE_IDLE) && !Player_InCsMode(play)) {
        gSaveContext.save.cutscene = 0xFFFD;
    }

    if ((gSaveContext.save.cutscene >= 0xFFF0) && (csCtx->state == CS_STATE_IDLE)) {
        s16 i;

        sCurTextId = 0;
        sCurOcarinaAction = 0;
        csCtx->playerCue = NULL;

        for (i = 0; i < ARRAY_COUNT(csCtx->actorCues); i++) {
            csCtx->actorCues[i] = NULL;
        }

        csCtx->state++; // CS_STATE_START

        if (csCtx->state == CS_STATE_START) {
            Audio_SetCutsceneFlag(true);

            csCtx->curFrame = 0xFFFF;

            csCtx->subCamId = ActorCutscene_GetCurrentSubCamId(0x7F);
            CutsceneCamera_Init(Play_GetCamera(play, csCtx->subCamId), &sCutsceneCameraInfo);
            csCtx->unk_18 = 0xFFFF;

            if (gSaveContext.cutsceneTrigger == 0) {
                Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
                ShrinkWindow_Letterbox_SetSizeTarget(32);
                ShrinkWindow_Letterbox_SetSize(32);
                csCtx->state++; // CS_STATE_RUN
            }

            CutsceneHandler_RunScript(play, csCtx);
        }

        gSaveContext.cutsceneTrigger = 0;
    }
}

void Cutscene_HandleEntranceTriggers(PlayState* play) {
    s32 pad;
    s16 actorCsId;
    SceneTableEntry* scene;
    s32 scriptIndex;

    if (((gSaveContext.gameMode == 0) || (gSaveContext.gameMode == 1)) && (gSaveContext.respawnFlag <= 0)) {
        // Try to find an actor cutscene that's triggered by the current spawn
        actorCsId = ActorCutscene_FindEntranceCutscene();
        if (actorCsId != -1) {
            scriptIndex = ActorCutscene_GetCutsceneScriptIndex(actorCsId);
            if (scriptIndex != -1) {
                // A scripted cutscene is triggered by a spawn
                if ((play->csCtx.scriptList[scriptIndex].spawnFlags != CS_SPAWN_FLAG_NONE) &&
                    (gSaveContext.respawnFlag == 0)) {
                    if (play->csCtx.scriptList[scriptIndex].spawnFlags == CS_SPAWN_FLAG_ALWAYS) {
                        // Entrance cutscenes that always run
                        ActorCutscene_Start(actorCsId, NULL);
                        gSaveContext.showTitleCard = false;
                    } else if (!(((void)0, gSaveContext.save
                                               .weekEventReg[(play->csCtx.scriptList[scriptIndex].spawnFlags / 8)]) &
                                 (1 << (play->csCtx.scriptList[scriptIndex].spawnFlags % 8)))) {
                        // Entrance cutscenes that only run once
                        // TODO: macros for this kind of weekEventReg access
                        gSaveContext.save.weekEventReg[(play->csCtx.scriptList[scriptIndex].spawnFlags / 8)] =
                            ((void)0,
                             gSaveContext.save.weekEventReg[(play->csCtx.scriptList[scriptIndex].spawnFlags / 8)]) |
                            (1 << (play->csCtx.scriptList[scriptIndex].spawnFlags % 8));
                        ActorCutscene_Start(actorCsId, NULL);
                        // The title card will be used by the cs misc command if necessary.
                        gSaveContext.showTitleCard = false;
                    }
                }
            } else {
                // A non-scripted cutscene is triggered by a spawn
                ActorCutscene_StartAndSetUnkLinkFields(actorCsId, NULL);
            }
        }
    }

    if ((gSaveContext.respawnFlag == 0) || (gSaveContext.respawnFlag == -2)) {
        scene = play->loadedScene;
        if ((scene->titleTextId != 0) && gSaveContext.showTitleCard) {
            if ((Entrance_GetTransitionFlags(((void)0, gSaveContext.save.entrance) +
                                             ((void)0, gSaveContext.sceneLayer)) &
                 0x4000) != 0) {
                func_80151A68(play, scene->titleTextId);
            }
        }

        gSaveContext.showTitleCard = true;
    }
}

void func_800EDDB0(PlayState* play) {
}

void func_800EDDBC(UNK_TYPE arg0, UNK_TYPE arg1) {
}

void Cutscene_LoadScript(PlayState* play, u8 scriptIndex) {
    if (!dREG(95)) {
        play->csCtx.scriptIndex = scriptIndex;
        play->csCtx.script = Lib_SegmentedToVirtual(play->csCtx.scriptList[scriptIndex].script);
    }

    gSaveContext.cutsceneTrigger = 1;
}

/* Start of actor utilities section */

/**
 * Interpolates the actor's position based on the corresponding actor action's position
 * and the current cutscene frame
 */
void Cutscene_ActorTranslate(Actor* actor, PlayState* play, s32 cueChannel) {
    Vec3f start;
    Vec3f end;
    CsCmdActorCue* entry = play->csCtx.actorCues[cueChannel];
    f32 lerp;

    start.x = entry->startPos.x;
    start.y = entry->startPos.y;
    start.z = entry->startPos.z;
    end.x = entry->endPos.x;
    end.y = entry->endPos.y;
    end.z = entry->endPos.z;

    lerp = Environment_LerpWeight(entry->endFrame, entry->startFrame, play->csCtx.curFrame);

    VEC3F_LERPIMPDST(&actor->world.pos, &start, &end, lerp);
}

/**
 * Interpolates the actor's position based on the corresponding actor action's position
 * and the current cutscene frame, and sets the actor's yaw using the actor action yaw
 */
void Cutscene_ActorTranslateAndYaw(Actor* actor, PlayState* play, s32 cueChannel) {
    Cutscene_ActorTranslate(actor, play, cueChannel);

    actor->world.rot.y = play->csCtx.actorCues[cueChannel]->urot.y;
    actor->shape.rot.y = actor->world.rot.y;
}

/**
 * Interpolates the actor's position and yaw based on the corresponding actor action's
 * position and the current cutscene frame
 */
void Cutscene_ActorTranslateAndYawSmooth(Actor* actor, PlayState* play, s32 cueChannel) {
    Vec3f start;
    Vec3f end;
    CsCmdActorCue* entry;
    f32 lerp;

    start.x = play->csCtx.actorCues[cueChannel]->startPos.x;
    start.y = play->csCtx.actorCues[cueChannel]->startPos.y;
    start.z = play->csCtx.actorCues[cueChannel]->startPos.z;
    end.x = play->csCtx.actorCues[cueChannel]->endPos.x;
    end.y = play->csCtx.actorCues[cueChannel]->endPos.y;
    end.z = play->csCtx.actorCues[cueChannel]->endPos.z;

    entry = play->csCtx.actorCues[cueChannel];
    lerp = Environment_LerpWeight(entry->endFrame, entry->startFrame, play->csCtx.curFrame);

    VEC3F_LERPIMPDST(&actor->world.pos, &start, &end, lerp);

    Math_SmoothStepToS(&actor->world.rot.y, Math_Vec3f_Yaw(&start, &end), 10, 1000, 1);
    actor->shape.rot.y = actor->world.rot.y;
}

/**
 * Interpolates the actor's XZ position and yaw based on the corresponding actor action's
 * position and the current cutscene frame
 */
void Cutscene_ActorTranslateXZAndYawSmooth(Actor* actor, PlayState* play, s32 cueChannel) {
    Vec3f start;
    Vec3f end;
    CsCmdActorCue* entry;
    f32 lerp;

    start.x = play->csCtx.actorCues[cueChannel]->startPos.x;
    start.z = play->csCtx.actorCues[cueChannel]->startPos.z;
    end.x = play->csCtx.actorCues[cueChannel]->endPos.x;
    end.z = play->csCtx.actorCues[cueChannel]->endPos.z;

    entry = play->csCtx.actorCues[cueChannel];
    lerp = Environment_LerpWeight(entry->endFrame, entry->startFrame, play->csCtx.curFrame);

    actor->world.pos.x = start.x + (end.x - start.x) * lerp;
    actor->world.pos.z = start.z + (end.z - start.z) * lerp;

    Math_SmoothStepToS(&actor->world.rot.y, Math_Vec3f_Yaw(&start, &end), 10, 1000, 1);
    actor->shape.rot.y = actor->world.rot.y;
}

s32 Cutscene_GetSceneLayer(PlayState* play) {
    s32 sceneLayer = 0;

    if (gSaveContext.sceneLayer > 0) {
        sceneLayer = gSaveContext.sceneLayer;
    }
    return sceneLayer;
}

/**
 * @param play See `PlayState`
 * @param cueType See `cmdType`
 * @return cue channel
 */
s32 Cutscene_GetCueChannel(PlayState* play, u16 cueType) {
    s32 i;
    s32 cueChannel = -1;

    for (i = 0; i < ARRAY_COUNT(sCueTypeList); i++) {
        if (cueType == sCueTypeList[i]) {
            cueChannel = i;
        }
    }

    return cueChannel;
}

/**
 * @param play See `PlayState`
 * @param cueType See `cmdType`
 * @return is cuetype in a channel
 */
s32 Cutscene_IsCueInChannel(PlayState* play, u16 cueType) {
    if (play->csCtx.state != CS_STATE_IDLE) {
        s32 cueChannel = Cutscene_GetCueChannel(play, cueType);

        if (cueChannel != -1) {
            return play->csCtx.actorCues[cueChannel] != NULL;
        }
    }

    return false;
}

u8 Cutscene_IsPlaying(PlayState* play) {
    return (gSaveContext.cutsceneTrigger != 0) || (play->csCtx.state != CS_STATE_IDLE);
}

/* End of actor utilities section */
