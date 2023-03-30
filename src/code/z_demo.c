#include "prevent_bss_reordering.h"
#include "global.h"
#include "z64quake.h"
#include "z64rumble.h"
#include "z64shrink_window.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"

void Cutscene_DoNothing(PlayState* play, CutsceneContext* csCtx);
void func_800EA258(PlayState* play, CutsceneContext* csCtx);
void func_800ED9C4(PlayState* play, CutsceneContext* csCtx);
void func_800EA2B8(PlayState* play, CutsceneContext* csCtx);
void func_800ED980(PlayState* play, CutsceneContext* csCtx);
void func_800EDA04(PlayState* play, CutsceneContext* csCtx);
void func_800EDA84(PlayState* play, CutsceneContext* csCtx);

// Unused
UNK_TYPE4 D_801BB120 = 0;
u16 D_801BB124 = 0;
u16 D_801BB128 = 0;
u8 D_801BB12C = 0;
u8 sCutsceneStoredPlayerForm = 0;

// bss
#ifndef NON_MATCHING
static u16 seqId;
#endif
s16 sCutsceneQuakeIndex;
DbCameraUnkStruct sCutsceneCameraInfo;
u16 D_801F4DC8[10];
UNK_TYPE D_801F4DDC;
u8 D_801F4DE0;
s16 D_801F4DE2;

void Cutscene_Init(PlayState* play, CutsceneContext* csCtx) {
    s32 i;

    csCtx->state = CS_STATE_0;
    csCtx->frames = 0;
    csCtx->unk_0C = 0.0f;
    play->csCtx.sceneCsCount = 0;
    play->csCtx.currentCsIndex = 0;

    for (i = 0; i < ARRAY_COUNT(D_801F4DC8); i++) {
        D_801F4DC8[i] = 0;
    }

    D_801F4DE0 = 0;

    Audio_SetCutsceneFlag(false);
}

void Cutscene_Start(PlayState* play, CutsceneContext* csCtx) {
    csCtx->state = CS_STATE_1;
    csCtx->playerAction = NULL;
}

void Cutscene_End(PlayState* play, CutsceneContext* csCtx) {
    if (csCtx->state != CS_STATE_4) {
        csCtx->state = CS_STATE_3;
    }
}

typedef void (*CutsceneStateHandler)(PlayState* play, CutsceneContext* csCtx);

CutsceneStateHandler sCsStateHandlers1[] = {
    Cutscene_DoNothing, // CS_STATE_0
    func_800EA258,      // CS_STATE_1
    Cutscene_DoNothing, // CS_STATE_2
    func_800ED9C4,      // CS_STATE_3
    Cutscene_DoNothing, // CS_STATE_4
};

void Cutscene_Update1(PlayState* play, CutsceneContext* csCtx) {
    if (gSaveContext.save.cutscene < 0xFFF0) {
        sCsStateHandlers1[csCtx->state](play, csCtx);
    }
}

CutsceneStateHandler sCsStateHandlers2[] = {
    Cutscene_DoNothing, // CS_STATE_0
    func_800EA2B8,      // CS_STATE_1
    func_800ED980,      // CS_STATE_2
    func_800EDA04,      // CS_STATE_3
    func_800ED980,      // CS_STATE_4
};

void Cutscene_Update2(PlayState* play, CutsceneContext* csCtx) {
    if ((gSaveContext.cutsceneTrigger != 0) && (play->transitionTrigger == TRANS_TRIGGER_START)) {
        gSaveContext.cutsceneTrigger = 0;
    }

    if ((gSaveContext.cutsceneTrigger != 0) && (csCtx->state == CS_STATE_0)) {
        gSaveContext.save.cutscene = 0xFFFD;
        gSaveContext.cutsceneTrigger = 1;
    }

    if (gSaveContext.save.cutscene >= 0xFFF0) {
        func_800EDA84(play, csCtx);
        sCsStateHandlers2[csCtx->state](play, csCtx);
    }
}

void Cutscene_DoNothing(PlayState* play, CutsceneContext* csCtx) {
}

s32 func_800EA220(PlayState* play, CutsceneContext* csCtx, f32 target) {
    return Math_StepToF(&csCtx->unk_0C, target, 0.1f);
}

void func_800EA258(PlayState* play, CutsceneContext* csCtx) {
    Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
    ShrinkWindow_Letterbox_SetSizeTarget(32);
    if (func_800EA220(play, csCtx, 1.0f)) {
        Audio_SetCutsceneFlag(true);
        csCtx->state++;
    }
}

void func_800EA2B8(PlayState* play, CutsceneContext* csCtx) {
    func_800ED980(play, csCtx);
    Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
    ShrinkWindow_Letterbox_SetSizeTarget(32);
    if (func_800EA220(play, csCtx, 1.0f)) {
        Audio_SetCutsceneFlag(true);
        csCtx->state++;
    }
}

/* Start of command handling section */

// Command 0x96: Miscellaneous commands.
void Cutscene_Command_Misc(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    static u16 D_801BB15C = 0xFFFF;
    Player* player = GET_PLAYER(play);
    f32 progress;
    u8 isStartFrame = false;
    SceneTableEntry* loadedScene;

    if ((csCtx->frames < cmd->startFrame) || ((csCtx->frames >= cmd->endFrame) && (cmd->endFrame != cmd->startFrame))) {
        return;
    }

    progress = Environment_LerpWeight(cmd->endFrame - 1, cmd->startFrame, csCtx->frames);
    if (csCtx->frames == cmd->startFrame) {
        isStartFrame = true;
    }

    // TODO: consider creating an enum for this when we understand what each value does
    switch (cmd->base) {
        case 0x1:
            if (isStartFrame) {
                func_800FD78C(play);
                play->envCtx.unk_F2[0] = 0x3C;
            }
            break;
        case 0x2:
            if (isStartFrame) {
                Audio_SetAmbienceChannelIO(AMBIENCE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_0, 0);
                Environment_AddLightningBolts(play, 3);
                D_801F4E68 = 1;
            }
            break;
        case 0x3:
            if (play->envCtx.lightSettings.zFar < 12800) {
                play->envCtx.lightSettings.zFar += 35;
            }
            break;
        case 0x4:
            if (isStartFrame) {
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
        case 0x5:
            if (isStartFrame && (csCtx->state != CS_STATE_4)) {
                csCtx->state = CS_STATE_3;
            }
            break;
        case 0x7:
            if (isStartFrame) {
                loadedScene = play->loadedScene;
                if (loadedScene->titleTextId != 0) {
                    func_80151A68(play, loadedScene->titleTextId);
                }
            }
            break;
        case 0x8:
            func_8019F128(NA_SE_EV_EARTHQUAKE_LAST - SFX_FLAG);
            if (isStartFrame) {
                sCutsceneQuakeIndex = Quake_Add(GET_ACTIVE_CAM(play), QUAKE_TYPE_6);
                Quake_SetSpeed(sCutsceneQuakeIndex, 22000);
                Quake_SetQuakeValues(sCutsceneQuakeIndex, 6, 4, 0, 0);
                Quake_SetCountdown(sCutsceneQuakeIndex, 800);
            }
            break;
        case 0x9:
            if (isStartFrame) {
                Quake_Init();
            }
            break;
        case 0xA:
            gVisMonoColor.r = 255;
            gVisMonoColor.g = 255;
            gVisMonoColor.b = 255;
            gVisMonoColor.a = 255 * progress;
            break;
        case 0xB:
            gVisMonoColor.r = 255;
            gVisMonoColor.g = 180;
            gVisMonoColor.b = 100;
            gVisMonoColor.a = 255 * progress;
            break;
        case 0xC:
            play->roomCtx.curRoom.segment = NULL;
            break;
        case 0xD:
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
        case 0xE:
            play->haltAllActors = true;
            break;
        case 0xF:
            play->haltAllActors = false;
            break;
        case 0x10:
            if (isStartFrame) {
                play->envCtx.sandstormState = 1;
            }
            func_8019F128(NA_SE_EV_SAND_STORM - SFX_FLAG);
            break;
        case 0x11:
            gSaveContext.sunsSongState = SUNSSONG_START;
            break;
        case 0x12:
            if (!gSaveContext.save.isNight) {
                gSaveContext.save.time = ((void)0, gSaveContext.save.time) - (u16)R_TIME_SPEED;
            } else {
                gSaveContext.save.time = ((void)0, gSaveContext.save.time) - (u16)(2 * R_TIME_SPEED);
            }
            break;
        case 0x13:
            AudioOcarina_PlayLongScarecrowAfterCredits();
            csCtx->frames = cmd->startFrame - 1;
            break;
        case 0x14:
            EnvFlags_Set(play, 3);
            break;
        case 0x15:
            EnvFlags_Set(play, 4);
            break;
        case 0x16:
            gSaveContext.save.playerForm = PLAYER_FORM_DEKU;
            break;
        case 0x17:
            player->stateFlags2 |= PLAYER_STATE2_4000000;
            break;
        case 0x18:
            player->stateFlags2 &= ~PLAYER_STATE2_4000000;
            break;
        case 0x19:
            sCutsceneStoredPlayerForm = gSaveContext.save.playerForm;
            gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
            gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
            break;
        case 0x1A:
            func_8019F128(NA_SE_EV_EARTHQUAKE_LAST2 - SFX_FLAG);
            if (isStartFrame) {
                sCutsceneQuakeIndex = Quake_Add(GET_ACTIVE_CAM(play), QUAKE_TYPE_6);
                Quake_SetSpeed(sCutsceneQuakeIndex, 30000);
                Quake_SetQuakeValues(sCutsceneQuakeIndex, 20, 10, 0, 0);
                Quake_SetCountdown(sCutsceneQuakeIndex, 800);
            }
            break;
        case 0x1B:
            if (isStartFrame) {
                play->nextEntrance = ENTRANCE(CUTSCENE, 0);
                gSaveContext.nextCutsceneIndex = 0xFFF8;
                play->transitionTrigger = TRANS_TRIGGER_START;
                play->transitionType = TRANS_TYPE_FADE_WHITE;
            }
            break;
        case 0x1C:
            if (isStartFrame) {
                play->envCtx.unk_17 = 0xD;
            }
            break;
        case 0x1D:
            gSaveContext.save.playerForm = sCutsceneStoredPlayerForm;
            break;
        case 0x1E:
            D_801F4DE0 = true;
            break;
        case 0x1F:
            D_801F4DE0 = false;
            break;
        case 0x21:
            if (isStartFrame) {
                Sram_SaveSpecialEnterClockTown(play);
            }
            break;
        case 0x22:
            if (isStartFrame) {
                func_80144A94(&play->sramCtx);
            }
            break;
        case 0x23:
            if (csCtx->frames != D_801BB15C) {
                D_801BB15C = csCtx->frames;

                if (R_TIME_SPEED != 0) {
                    gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)R_TIME_SPEED;
                    gSaveContext.save.time =
                        ((void)0, gSaveContext.save.time) + (u16)((void)0, gSaveContext.save.timeSpeedOffset);
                }
            }
            break;
        case 0x24:
            func_8019F128(NA_SE_EV_EARTHQUAKE_LAST - SFX_FLAG);
            if (isStartFrame) {
                sCutsceneQuakeIndex = Quake_Add(GET_ACTIVE_CAM(play), QUAKE_TYPE_6);
                Quake_SetSpeed(sCutsceneQuakeIndex, 22000);
                Quake_SetQuakeValues(sCutsceneQuakeIndex, 2, 1, 0, 0);
                Quake_SetCountdown(sCutsceneQuakeIndex, 800);
            }
            break;

        case 0x26:
            // Seems to be used to trigger "Dawn of A New Day"

            gSaveContext.save.day = 9;

            STOP_GAMESTATE(&play->state);
            SET_NEXT_GAMESTATE(&play->state, DayTelop_Init, sizeof(DayTelopState));

            Sram_SaveSpecialNewDay(play);
            break;

        case 0x27:
            gSaveContext.save.playerForm = PLAYER_FORM_ZORA;
            break;

        case 0x28:
            csCtx->frames = cmd->startFrame - 1;
            break;
    }
}

// Command 0x97: Set Environment Lighting
void Cutscene_Command_SetLighting(PlayState* play, CutsceneContext* csCtx, CsCmdEnvLighting* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        if (cmd->setting != 0x20) {
            play->envCtx.lightSettingOverride = cmd->setting - 1;
            play->envCtx.lightBlend = 1.0f;
        } else {
            play->envCtx.lightSettingOverride = 0xFF;
        }
    }
}

// Command 0x12C: Plays a sequence (Background music or Fanfare)
void Cutscene_Command_PlaySequence(PlayState* play, CutsceneContext* csCtx, CsCmdSequenceChange* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        Audio_PlaySequenceInCutscene(cmd->sequence - 1);
    }
}

// Command 0x12D: Stops a sequence (Background music or Fanfare)
void Cutscene_Command_StopSequence(PlayState* play, CutsceneContext* csCtx, CsCmdSequenceChange* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        Audio_StopSequenceInCutscene(cmd->sequence - 1);
    }
}

// Command 0x9C: Fade a sequence (Background music or Fanfare) over duration
void Cutscene_Command_FadeSequence(PlayState* play, CutsceneContext* csCtx, CsCmdSequenceFade* cmd) {
    if ((csCtx->frames == cmd->startFrame) && (csCtx->frames < cmd->endFrame)) {
        u8 fadeTimer = cmd->endFrame - cmd->startFrame;

        if (cmd->type == 2) {
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, fadeTimer);
        } else {
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM_MAIN, fadeTimer);
        }
    }
}

// Command 0x12E: Play Ambience sequence
void Cutscene_Command_PlayAmbienceSequence(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        Audio_PlayAmbience(play->sequenceCtx.ambienceId);
    }
}

// Command 0x130:
void func_800EAD48(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        // Audio_SetSfxReverbIndexExceptOcarinaBank
        func_801A4428(2);
    }
}

// Command 0x131:
void func_800EAD7C(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        // Audio_SetSfxReverbIndexExceptOcarinaBank
        func_801A4428(1);
    }
}

#ifdef NON_MATCHING
// needs in-function static bss
// audio related
void func_800EADB0(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    static u16 seqId;
    u8 dayMinusOne;

    if (csCtx->frames == cmd->startFrame) {
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
                seqId = AudioSeq_GetActiveSeqId(SEQ_PLAYER_BGM_MAIN);
                break;

            case 8:
                if (seqId != NA_BGM_DISABLED) {
                    Audio_PlaySceneSequence(seqId, dayMinusOne);
                }
                break;
        }
    }
}
#else
void func_800EADB0(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EADB0.s")
#endif

// Command 0x12F: Fade Ambience sequence
void Cutscene_Command_FadeAmbienceSequence(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame && csCtx->frames < cmd->endFrame) {
        u8 fadeTimer = cmd->endFrame - cmd->startFrame;

        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_AMBIENCE, fadeTimer);
    }
}

// Command 0x190: Rumble
void Cutscene_Command_Rumble(PlayState* play, CutsceneContext* csCtx, CsCmdRumble* cmd) {
    switch (cmd->type) {
        case 1:
            if (csCtx->frames == cmd->startFrame) {
                Rumble_Request(0.0f, cmd->intensity, cmd->decayTimer, cmd->decayStep);
            }
            break;

        case 2:
            if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
                if ((csCtx->frames == cmd->startFrame) || (play->state.frames % 64 == 0)) {
                    Rumble_Request(0.0f, cmd->intensity, cmd->decayTimer, cmd->decayStep);
                }
            }
            break;
    }
}

// Command 0x9B:
void Cutscene_Command_FadeColorScreen(PlayState* play, CutsceneContext* csCtx, CsCmdFadeScreen* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        f32 alpha;

        play->envCtx.fillScreen = true;
        alpha = Environment_LerpWeight(cmd->endFrame, cmd->startFrame, csCtx->frames);

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
void Cutscene_Command_SetTime(PlayState* play, CutsceneContext* csCtx, CsCmdDayTime* cmd) {
    u16 nextTime;
    u16 hourAsMinutes;
    u16 minutes;

    if (csCtx->frames == cmd->startFrame) {
        hourAsMinutes = CLOCK_TIME_ALT_F(cmd->hour, 0);
        minutes = CLOCK_TIME_ALT_F(0, cmd->minute + 1);

        nextTime = hourAsMinutes + minutes;
        gSaveContext.save.time = nextTime;
        gSaveContext.skyboxTime = nextTime;
    }
}

void Cutscene_TerminatorImpl(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    csCtx->state = CS_STATE_4;
    Play_DisableMotionBlur();
    Audio_SetCutsceneFlag(false);
    gSaveContext.cutsceneTransitionControl = 1;

    if ((gSaveContext.gameMode != 0) && (csCtx->frames != cmd->startFrame)) {
        gSaveContext.hudVisibilityForceButtonAlphasByStatus = true;
    }

    gSaveContext.save.cutscene = 0;
    if (cmd->base == 1) {
        play->nextEntrance = play->csCtx.sceneCsList[play->csCtx.currentCsIndex].nextEntrance;
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        if (gSaveContext.gameMode != 1) {
            Scene_SetExitFade(play);
        } else {
            D_801BB12C++;
            if (D_801BB12C >= 2) {
                D_801BB12C = 0;
            }
            play->transitionType = TRANS_TYPE_FADE_BLACK_FAST;
        }

        if ((play->nextEntrance & 0xF) > 0) {
            gSaveContext.nextCutsceneIndex = (play->nextEntrance & 0xF) + 0xFFEF;
        }

        play->nextEntrance &= ~0xF;
    }
}

// Command 0x15E
void Cutscene_Command_Terminator(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (cmd->base == 1) {
        if (csCtx->frames == cmd->startFrame) {
            Cutscene_TerminatorImpl(play, csCtx, cmd);
        }
    } else if (cmd->base == 2) {
        if (csCtx->frames == cmd->startFrame) {
            Play_DisableMotionBlur();

            switch (D_801F4DE2) {
                case 0x1F:
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_20_02)) {
                        play->nextEntrance = ENTRANCE(WOODFALL_TEMPLE, 1);
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_FADE_WHITE;
                    } else {
                        play->nextEntrance = ENTRANCE(WOODFALL, 0);
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_FADE_WHITE;
                    }
                    break;

                case 0x44:
                    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_33_80)) {
                        play->nextEntrance = ENTRANCE(MOUNTAIN_VILLAGE_SPRING, 7);
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_FADE_WHITE;
                    } else {
                        play->nextEntrance = ENTRANCE(MOUNTAIN_VILLAGE_SPRING, 0);
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        play->transitionTrigger = TRANS_TRIGGER_START;
                        play->transitionType = TRANS_TYPE_FADE_WHITE;
                    }
                    break;

                case 0x5F:
                    SET_WEEKEVENTREG(WEEKEVENTREG_55_80);
                    play->nextEntrance = ENTRANCE(ZORA_CAPE, 8);
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                    play->transitionTrigger = TRANS_TRIGGER_START;
                    play->transitionType = TRANS_TYPE_FADE_WHITE;
                    break;

                case 0x36:
                    SET_WEEKEVENTREG(WEEKEVENTREG_52_20);
                    play->nextEntrance = ENTRANCE(IKANA_CANYON, 0);
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                    play->transitionTrigger = TRANS_TRIGGER_START;
                    play->transitionType = TRANS_TYPE_FADE_WHITE;
                    break;
            }
        }
    }
}

// Command 0x15F: Chooses between a cutscene or a rotating mask depending on whether the player has the corresponding
// mask
void Cutscene_Command_ChooseCreditsScenes(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (func_801A3950(SEQ_PLAYER_BGM_MAIN, true) != 0xFF)) {
        switch (cmd->base) {
            case 1:
                Cutscene_TerminatorImpl(play, csCtx, cmd);
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

// Command 0x99: Motion blur
void Cutscene_Command_MotionBlur(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        if ((csCtx->frames == cmd->startFrame) && (cmd->base == 1)) {
            Play_EnableMotionBlur(180);
        }

        if (cmd->base == 2) {
            f32 progress = Environment_LerpWeight(cmd->endFrame, cmd->startFrame, csCtx->frames);

            if (progress >= 0.9f) {
                Play_DisableMotionBlur();
            } else {
                Play_SetMotionBlurAlpha((1.0f - progress) * 180.0f);
            }
        }
    }
}

// Command 0x9A: Gives Tatl to the player
void Cutscene_Command_GiveTatlToPlayer(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    Player* player = GET_PLAYER(play);

    if (csCtx->frames == cmd->startFrame) {
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

// Command 0x98
void Cutscene_Command_TransitionFX(PlayState* play, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        f32 temp_f0;

        play->envCtx.fillScreen = true;
        temp_f0 = Environment_LerpWeight(cmd->endFrame, cmd->startFrame, csCtx->frames);

        switch (cmd->base) {
            case 1:
            case 5:
                play->envCtx.screenFillColor[0] = 160;
                play->envCtx.screenFillColor[1] = 160;
                play->envCtx.screenFillColor[2] = 160;
                if (cmd->base == 1) {
                    play->envCtx.screenFillColor[3] = 255.0f * temp_f0;
                    if (temp_f0 == 0.0f) {
                        func_8019F128(NA_SE_EV_S_STONE_FLASH);
                    }
                } else {
                    play->envCtx.screenFillColor[3] = (1.0f - temp_f0) * 255.0f;
                }
                break;

            case 2:
            case 6:
                play->envCtx.screenFillColor[0] = 0;
                play->envCtx.screenFillColor[1] = 0;
                play->envCtx.screenFillColor[2] = 255;
                if (cmd->base == 2) {
                    play->envCtx.screenFillColor[3] = 255.0f * temp_f0;
                } else {
                    play->envCtx.screenFillColor[3] = (1.0f - temp_f0) * 255.0f;
                }
                break;

            case 3:
            case 7:
                play->envCtx.screenFillColor[0] = 255;
                play->envCtx.screenFillColor[1] = 0;
                play->envCtx.screenFillColor[2] = 0;
                if (cmd->base == 3) {
                    play->envCtx.screenFillColor[3] = (1.0f - temp_f0) * 255.0f;
                } else {
                    play->envCtx.screenFillColor[3] = 255.0f * temp_f0;
                }
                break;

            case 4:
            case 8:
                play->envCtx.screenFillColor[0] = 0;
                play->envCtx.screenFillColor[1] = 255;
                play->envCtx.screenFillColor[2] = 0;
                if (cmd->base == 4) {
                    play->envCtx.screenFillColor[3] = (1.0f - temp_f0) * 255.0f;
                } else {
                    play->envCtx.screenFillColor[3] = 255.0f * temp_f0;
                }
                break;

            case 9:
                gSaveContext.cutsceneTransitionControl = 1;
                break;

            case 10:
            case 11:
                play->envCtx.screenFillColor[0] = 0;
                play->envCtx.screenFillColor[1] = 0;
                play->envCtx.screenFillColor[2] = 0;
                if (cmd->base == 10) {
                    play->envCtx.screenFillColor[3] = (1.0f - temp_f0) * 255.0f;
                } else {
                    play->envCtx.screenFillColor[3] = 255.0f * temp_f0;
                }
                break;

            case 12:
                play->envCtx.screenFillColor[0] = (160.0f * (1.0f - temp_f0));
                play->envCtx.screenFillColor[1] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[2] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[3] = 255;
                break;

            case 13:
                play->envCtx.screenFillColor[0] = (160.0f * temp_f0);
                play->envCtx.screenFillColor[1] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[2] = play->envCtx.screenFillColor[0];
                play->envCtx.screenFillColor[3] = 255;
                break;
        }
    }
}

// Command 0x5A: Camera
s32 Cutscene_Command_Camera(PlayState* play, u8* cmd) {
    s32 sp1C = 0;

    bcopy(cmd, &sp1C, sizeof(s32));
    cmd += sizeof(s32);
    if (!Play_IsDebugCamEnabled()) {
        func_80161998(cmd, &sCutsceneCameraInfo);
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

// Command 0xA: Textbox
void Cutscene_Command_Textbox(PlayState* play, CutsceneContext* csCtx, CsCmdTextbox* cmd) {
    static s32 D_801BB160 = CS_TEXTBOX_TYPE_DEFAULT;
    u8 talkState;
    s32 pad;
    u16 originalCsFrames;
    s32 pad2;

    if ((cmd->startFrame >= csCtx->frames) || ((cmd->endFrame < csCtx->frames))) {
        return;
    }

    if (cmd->type != CS_TEXTBOX_TYPE_LEARN_SONG) {
        if (D_801BB124 != cmd->base) {
            if (D_801BB160 == CS_TEXTBOX_TYPE_3) {
                csCtx->frames--;
            }
            D_801BB160 = CS_TEXTBOX_TYPE_1;
            D_801BB124 = cmd->base;
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
    } else if (D_801BB128 != cmd->base) {
        D_801BB160 = CS_TEXTBOX_TYPE_LEARN_SONG;
        D_801BB128 = cmd->base;
        func_80152434(play, cmd->base);
    } else {
    else_label:
        if (csCtx->frames >= cmd->endFrame) {
            // The Textbox command can change the current cutscene frame, mainly to prevent advancing the cutscene when
            // a textbox that is expected to be closed by the user is still open.

            originalCsFrames = csCtx->frames;
            talkState = Message_GetState(&play->msgCtx);
            if ((talkState != TEXT_STATE_CLOSING) && (talkState != TEXT_STATE_NONE) && (talkState != TEXT_STATE_7) &&
                (talkState != TEXT_STATE_8)) {
                csCtx->frames--;
                if ((talkState == TEXT_STATE_CHOICE) && Message_ShouldAdvance(play)) {
                    if (play->msgCtx.choiceIndex == 0) {
                        if (cmd->base == 0x33BD) {
                            func_8019F230();
                        }

                        if (cmd->textId1 != 0xFFFF) {
                            Message_ContinueTextbox(play, cmd->textId1);
                            if (cmd->type == CS_TEXTBOX_TYPE_3) {
                                D_801BB160 = CS_TEXTBOX_TYPE_3;
                                if (cmd->textId2 != 0xFFFF) {
                                    csCtx->frames++;
                                }
                            }
                        } else {
                            Message_CloseTextbox(play);
                            csCtx->frames++;
                        }
                    } else {
                        if (cmd->base == 0x33BD) {
                            func_8019F208();
                        }

                        if (cmd->textId2 != 0xFFFF) {
                            Message_ContinueTextbox(play, cmd->textId2);
                            if (cmd->type == CS_TEXTBOX_TYPE_3) {
                                D_801BB160 = CS_TEXTBOX_TYPE_3;
                                if (cmd->textId1 != 0xFFFF) {
                                    csCtx->frames++;
                                }
                            }
                        } else {
                            Message_CloseTextbox(play);
                            csCtx->frames++;
                        }
                    }
                }

                if ((talkState == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
                    func_80152434(play, cmd->base);
                }
            }

            if ((talkState == TEXT_STATE_CLOSING) && (D_801BB160 == CS_TEXTBOX_TYPE_3)) {
                csCtx->frames--;
                D_801BB124++;
            }

            if (originalCsFrames == csCtx->frames) {
                Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
                D_801BB124 = 0;
                D_801BB128 = 0;
                func_80161C0C();
            } else {
                func_80161BE0(1);
            }
        }
    }
}

// Related to actorActions. Maybe a generic actorAction setter?
void func_800ECD7C(CutsceneContext* csCtx, u8** cutscenePtr, s16 index) {
    s32 i;
    s32 count;

    bcopy(*cutscenePtr, &count, sizeof(s32));
    *cutscenePtr += sizeof(s32);

    for (i = 0; i < count; i++) {
        CsCmdActorAction* actorAction = *(CsCmdActorAction**)cutscenePtr;

        if ((csCtx->frames >= actorAction->startFrame) && (csCtx->frames < actorAction->endFrame)) {
            csCtx->actorActions[index] = actorAction;
        }

        *cutscenePtr += sizeof(CsCmdActorAction);
    }
}

/**
 * Loops over the cutscene data itself (`cutscenePtr`), applying the effects of each command instantaneously (for most
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
 * For most command lists categories (all but the actorActions and Camera commands):
 * - For each command list found, read the number of commands and loop over them, passing each one to the corresponding
 * function which handles the command, applying its effects and checking the frame range stored in the command.
 *
 * This function is invoked once per frame that a cutscene is active.
 *
 * TODO: consider changing the type of `cutscenePtr` to `uintptr_t` when this function matches.
 */
void Cutscene_ProcessCommands(PlayState* play, CutsceneContext* csCtx, u8* cutscenePtr) {
    s32 i;
    s32 j;
    s32 pad;
    s32 totalEntries;
    u32 cmdType;
    s32 cmdEntries;
    s32 pad2;
    s32 cutsceneEndFrame;
    CsCmdBase* cmd;

    // Read the command list count and the ending frame for this cutscene
    bcopy(cutscenePtr, &totalEntries, sizeof(s32));
    cutscenePtr += sizeof(s32);
    bcopy(cutscenePtr, &cutsceneEndFrame, sizeof(s32));
    cutscenePtr += sizeof(s32);

    if (((u16)cutsceneEndFrame < csCtx->frames) && (play->transitionTrigger != TRANS_TRIGGER_START) &&
        (csCtx->state != CS_STATE_4)) {
        csCtx->state = CS_STATE_3;
        return;
    }

    // Loop over every command list
    for (i = 0; i < totalEntries; i++) {
        // Read the command type of the current command list.
        bcopy(cutscenePtr, &cmdType, sizeof(u32));
        cutscenePtr += sizeof(u32);

        // TODO: This should probably be added to the CutsceneCmd enum. Consider doing it when this function matches.
        if (cmdType == 0xFFFFFFFF) {
            break;
        }

        // Check special cases of command types. This are generic ActorActions
        // Ranges: [0x64, 0x96), 0xC9, [0x1C2, 0x258)
        if (((cmdType >= 100) && (cmdType < 150)) || (cmdType == 201) || ((cmdType >= 450) && (cmdType < 600))) {
            for (j = 0; j < ARRAY_COUNT(D_801F4DC8); j = (s16)(j + 1)) {
                if (D_801F4DC8[j] == (u16)cmdType) {
                    func_800ECD7C(csCtx, &cutscenePtr, j);
                    cmdType = -2;
                    break;
                } else if (D_801F4DC8[j] == 0) {
                    D_801F4DC8[j] = cmdType;
                    func_800ECD7C(csCtx, &cutscenePtr, j);
                    cmdType = -2;
                    break;
                }
            }
        }

        switch (cmdType) {
            case CS_CMD_MISC:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_Misc(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_SET_LIGHTING:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_SetLighting(play, csCtx, (CsCmdEnvLighting*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdEnvLighting);
                }
                break;

            case CS_CMD_PLAYSEQ:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_PlaySequence(play, csCtx, (CsCmdSequenceChange*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdSequenceChange);
                }
                break;

            case CS_CMD_STOPSEQ:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_StopSequence(play, csCtx, (CsCmdSequenceChange*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdSequenceChange);
                }
                break;

            case CS_CMD_FADESEQ:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_FadeSequence(play, csCtx, (CsCmdSequenceFade*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdSequenceFade);
                }
                break;

            case CS_CMD_PLAYAMBIENCE:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_PlayAmbienceSequence(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_FADEAMBIENCE:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_FadeAmbienceSequence(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_130:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    func_800EAD48(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_131:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    func_800EAD7C(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_132:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    func_800EADB0(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_RUMBLE:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_Rumble(play, csCtx, (CsCmdRumble*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdRumble);
                }
                break;

            case CS_CMD_FADESCREEN:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_FadeColorScreen(play, csCtx, (CsCmdFadeScreen*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdFadeScreen);
                }
                break;

            case CS_CMD_SETTIME:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_SetTime(play, csCtx, (CsCmdDayTime*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdDayTime);
                }
                break;

            case CS_CMD_SET_PLAYER_ACTION:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    cmd = (CsCmdBase*)cutscenePtr;
                    if ((cmd->startFrame <= csCtx->frames) && (csCtx->frames < cmd->endFrame)) {
                        csCtx->playerAction = (CsCmdActorAction*)cmd;
                    }
                    cutscenePtr += sizeof(CsCmdActorAction);
                }
                break;

            case CS_CMD_CAMERA:
                cutscenePtr += Cutscene_Command_Camera(play, cutscenePtr);
                break;

            case CS_CMD_TERMINATOR:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_Terminator(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_CHOOSE_CREDITS_SCENES:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_ChooseCreditsScenes(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_TEXTBOX:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    cmd = (CsCmdBase*)cutscenePtr;
                    if (cmd->base != 0xFFFF) {
                        Cutscene_Command_Textbox(play, csCtx, (CsCmdTextbox*)cmd);
                    }
                    cutscenePtr += sizeof(CsCmdTextbox);
                }
                break;

            case CS_CMD_SCENE_TRANS_FX:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_TransitionFX(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_MOTIONBLUR:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_MotionBlur(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case CS_CMD_GIVETATL:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    Cutscene_Command_GiveTatlToPlayer(play, csCtx, (CsCmdBase*)cutscenePtr);
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;

            case -2:
                break;

            default:
                bcopy(cutscenePtr, &cmdEntries, sizeof(s32));
                cutscenePtr += sizeof(s32);
                for (j = 0; j < cmdEntries; j++) {
                    cutscenePtr += sizeof(CsCmdBase);
                }
                break;
        }
    }
}

/* End of command handling section */

void func_800ED980(PlayState* play, CutsceneContext* csCtx) {
    if (gSaveContext.save.cutscene >= 0xFFF0) {
        csCtx->frames++;
        Cutscene_ProcessCommands(play, csCtx, (u8*)play->csCtx.csData);
    }
}

void func_800ED9C4(PlayState* play, CutsceneContext* csCtx) {
    if (func_800EA220(play, csCtx, 0.0f)) {
        Audio_SetCutsceneFlag(false);
        csCtx->state = CS_STATE_0;
    }
}

// unused
void func_800EDA04(PlayState* play, CutsceneContext* csCtx) {
    if (func_800EA220(play, csCtx, 0.0f)) {
        s16 i;

        csCtx->playerAction = NULL;

        for (i = 0; i < ARRAY_COUNT(csCtx->actorActions); i++) {
            csCtx->actorActions[i] = NULL;
        }

        gSaveContext.save.cutscene = 0;
        gSaveContext.gameMode = 0;
        ActorCutscene_Stop(0x7F);
        Audio_SetCutsceneFlag(false);
        csCtx->state = CS_STATE_0;
    }
}

void func_800EDA84(PlayState* play, CutsceneContext* csCtx) {
    if ((gSaveContext.cutsceneTrigger != 0) && (csCtx->state == CS_STATE_0) && !Player_InCsMode(play)) {
        gSaveContext.save.cutscene = 0xFFFD;
    }

    if ((gSaveContext.save.cutscene >= 0xFFF0) && (csCtx->state == CS_STATE_0)) {
        s16 i;

        D_801BB124 = 0;
        D_801BB128 = 0;
        csCtx->playerAction = NULL;

        for (i = 0; i < ARRAY_COUNT(csCtx->actorActions); i++) {
            csCtx->actorActions[i] = NULL;
        }

        csCtx->state++;
        if (csCtx->state == CS_STATE_1) {
            Audio_SetCutsceneFlag(true);

            csCtx->frames = 0xFFFF;
            csCtx->subCamId = ActorCutscene_GetCurrentSubCamId(0x7F);
            func_8016119C(Play_GetCamera(play, csCtx->subCamId), &sCutsceneCameraInfo);
            csCtx->unk_18 = 0xFFFF;

            if (gSaveContext.cutsceneTrigger == 0) {
                Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
                ShrinkWindow_Letterbox_SetSizeTarget(32);
                ShrinkWindow_Letterbox_SetSize(32);
                csCtx->state++;
            }

            func_800ED980(play, csCtx);
        }

        gSaveContext.cutsceneTrigger = 0;
    }
}

// HandleFlags?
void func_800EDBE0(PlayState* play) {
    s32 pad;
    s16 sp2A;
    SceneTableEntry* sp24;
    s32 temp_v0_3;

    if (((gSaveContext.gameMode == 0) || (gSaveContext.gameMode == 1)) && (gSaveContext.respawnFlag <= 0)) {
        sp2A = func_800F21CC();
        if (sp2A != -1) {
            temp_v0_3 = func_800F2138(sp2A);
            if (temp_v0_3 != -1) {
                if ((play->csCtx.sceneCsList[temp_v0_3].unk7 != 0xFF) && (gSaveContext.respawnFlag == 0)) {
                    if (play->csCtx.sceneCsList[temp_v0_3].unk7 == 0xFE) {
                        ActorCutscene_Start(sp2A, NULL);
                        gSaveContext.showTitleCard = false;
                    } else if (!(((void)0,
                                  gSaveContext.save.weekEventReg[(play->csCtx.sceneCsList[temp_v0_3].unk7 / 8)]) &
                                 (1 << (play->csCtx.sceneCsList[temp_v0_3].unk7 % 8)))) {
                        // TODO: macros for this kind of weekEventReg access
                        gSaveContext.save.weekEventReg[(play->csCtx.sceneCsList[temp_v0_3].unk7 / 8)] =
                            ((void)0, gSaveContext.save.weekEventReg[(play->csCtx.sceneCsList[temp_v0_3].unk7 / 8)]) |
                            (1 << (play->csCtx.sceneCsList[temp_v0_3].unk7 % 8));
                        ActorCutscene_Start(sp2A, NULL);
                        gSaveContext.showTitleCard = false;
                    }
                }
            } else {
                ActorCutscene_StartAndSetUnkLinkFields(sp2A, NULL);
            }
        }
    }

    if ((gSaveContext.respawnFlag == 0) || (gSaveContext.respawnFlag == -2)) {
        sp24 = play->loadedScene;
        if ((sp24->titleTextId != 0) && gSaveContext.showTitleCard) {
            if ((Entrance_GetTransitionFlags(((void)0, gSaveContext.save.entrance) +
                                             ((void)0, gSaveContext.sceneLayer)) &
                 0x4000) != 0) {
                func_80151A68(play, sp24->titleTextId);
            }
        }

        gSaveContext.showTitleCard = true;
    }
}

void func_800EDDB0(PlayState* play) {
}

void func_800EDDBC(UNK_TYPE arg0, UNK_TYPE arg1) {
}

void Cutscene_LoadCutsceneData(PlayState* play, u8 csIndex) {
    if (dREG(95) == 0) {
        play->csCtx.currentCsIndex = csIndex;
        play->csCtx.csData = Lib_SegmentedToVirtual(play->csCtx.sceneCsList[csIndex].segmentedData);
    }

    gSaveContext.cutsceneTrigger = 1;
}

/* Start of actor utilities section */

/**
 * Interpolates the actor's position based on the corresponding actor action's position
 * and the current cutscene frame
 */
void Cutscene_ActorTranslate(Actor* actor, PlayState* play, s32 actorActionIndex) {
    Vec3f start;
    Vec3f end;
    CsCmdActorAction* entry = play->csCtx.actorActions[actorActionIndex];
    f32 progress;

    start.x = entry->startPos.x;
    start.y = entry->startPos.y;
    start.z = entry->startPos.z;
    end.x = entry->endPos.x;
    end.y = entry->endPos.y;
    end.z = entry->endPos.z;

    progress = Environment_LerpWeight(entry->endFrame, entry->startFrame, play->csCtx.frames);

    VEC3F_LERPIMPDST(&actor->world.pos, &start, &end, progress);
}

/**
 * Interpolates the actor's position based on the corresponding actor action's position
 * and the current cutscene frame, and sets the actor's yaw using the actor action yaw
 */
void Cutscene_ActorTranslateAndYaw(Actor* actor, PlayState* play, s32 actorActionIndex) {
    Cutscene_ActorTranslate(actor, play, actorActionIndex);

    actor->world.rot.y = play->csCtx.actorActions[actorActionIndex]->urot.y;
    actor->shape.rot.y = actor->world.rot.y;
}

/**
 * Interpolates the actor's position and yaw based on the corresponding actor action's
 * position and the current cutscene frame
 */
void Cutscene_ActorTranslateAndYawSmooth(Actor* actor, PlayState* play, s32 actorActionIndex) {
    Vec3f start;
    Vec3f end;
    CsCmdActorAction* entry;
    f32 progress;

    start.x = play->csCtx.actorActions[actorActionIndex]->startPos.x;
    start.y = play->csCtx.actorActions[actorActionIndex]->startPos.y;
    start.z = play->csCtx.actorActions[actorActionIndex]->startPos.z;
    end.x = play->csCtx.actorActions[actorActionIndex]->endPos.x;
    end.y = play->csCtx.actorActions[actorActionIndex]->endPos.y;
    end.z = play->csCtx.actorActions[actorActionIndex]->endPos.z;

    entry = play->csCtx.actorActions[actorActionIndex];
    progress = Environment_LerpWeight(entry->endFrame, entry->startFrame, play->csCtx.frames);

    VEC3F_LERPIMPDST(&actor->world.pos, &start, &end, progress);

    Math_SmoothStepToS(&actor->world.rot.y, Math_Vec3f_Yaw(&start, &end), 10, 1000, 1);
    actor->shape.rot.y = actor->world.rot.y;
}

/**
 * Interpolates the actor's XZ position and yaw based on the corresponding actor action's
 * position and the current cutscene frame
 */
void Cutscene_ActorTranslateXZAndYawSmooth(Actor* actor, PlayState* play, s32 actorActionIndex) {
    Vec3f start;
    Vec3f end;
    CsCmdActorAction* entry;
    f32 progress;

    start.x = play->csCtx.actorActions[actorActionIndex]->startPos.x;
    start.z = play->csCtx.actorActions[actorActionIndex]->startPos.z;
    end.x = play->csCtx.actorActions[actorActionIndex]->endPos.x;
    end.z = play->csCtx.actorActions[actorActionIndex]->endPos.z;

    entry = play->csCtx.actorActions[actorActionIndex];
    progress = Environment_LerpWeight(entry->endFrame, entry->startFrame, play->csCtx.frames);

    actor->world.pos.x = start.x + (end.x - start.x) * progress;
    actor->world.pos.z = start.z + (end.z - start.z) * progress;

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

s32 Cutscene_GetActorActionIndex(PlayState* play, u16 actorActionCmd) {
    s32 i;
    s32 index = -1;

    for (i = 0; i < ARRAY_COUNT(D_801F4DC8); i++) {
        if (actorActionCmd == D_801F4DC8[i]) {
            index = i;
        }
    }

    return index;
}

s32 Cutscene_CheckActorAction(PlayState* play, u16 actorActionCmd) {
    if (play->csCtx.state != CS_STATE_0) {
        s32 index = Cutscene_GetActorActionIndex(play, actorActionCmd);

        if (index != -1) {
            return play->csCtx.actorActions[index] != NULL;
        }
    }

    return false;
}

u8 Cutscene_IsPlaying(PlayState* play) {
    return (gSaveContext.cutsceneTrigger != 0) || (play->csCtx.state != CS_STATE_0);
}

/* End of actor utilities section */
