#include "global.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"

#if 0

glabel D_801F4D40
/* 010DA0 801F4D40 */ .space 0x2

glabel D_801F4D42
/* 010DA2 801F4D42 */ .space 0x6

glabel D_801F4D48
/* 010DA8 801F4D48 */ .space 0x80

glabel D_801F4DC8
/* 010E28 801F4DC8 */ .space 0x14

glabel D_801F4DDC
/* 010E3C 801F4DDC */ .space 0x4

glabel D_801F4DE0
/* 010E40 801F4DE0 */ .space 0x2

glabel D_801F4DE2
/* 010E42 801F4DE2 */ .space 0xE
#endif

extern u16 D_801F4DC8[10];
extern s8 D_801F4DE0;

#if NON_MATCHING
void Cutscene_Init(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    s32 i;

    csCtx->state = 0;
    csCtx->frames = 0;
    csCtx->unk_0C = 0.0f;
    globalCtx->csCtx.sceneCsCount = 0;
    globalCtx->csCtx.unk_12 = 0;

    for (i = 0; i < ARRAY_COUNT(D_801F4DC8); i++) {
        D_801F4DC8[i] = 0;
    }

    D_801F4DE0 = 0;

    func_801A3F54(0);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_Init.s")
#endif

void func_800EA0D4(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    csCtx->state = 1;
    csCtx->linkAction = NULL;
}

void func_800EA0EC(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (csCtx->state != 4) {
        csCtx->state = 3;
    }
}

void Cutscene_StepCutscene1(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (gSaveContext.cutscene < 0xFFF0) {
        sCsStateHandlers1[csCtx->state](globalCtx, csCtx);
    }
}

void Cutscene_StepCutscene2(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if ((gSaveContext.cutsceneTrigger != 0) && (globalCtx->sceneLoadFlag == 0x14)) {
        gSaveContext.cutsceneTrigger = 0;
    }

    if ((gSaveContext.cutsceneTrigger != 0) && (csCtx->state == 0)) {
        gSaveContext.cutscene = 0xFFFD;
        gSaveContext.cutsceneTrigger = 1;
    }

    if (gSaveContext.cutscene >= 0xFFF0) {
        func_800EDA84(globalCtx, csCtx);
        sCsStateHandlers2[csCtx->state](globalCtx, csCtx);
    }
}

void Cutscene_Nop800EA210(GlobalContext* globalCtx, CutsceneContext* csCtx) {

}

s32 func_800EA220(GlobalContext* globalCtx, CutsceneContext* csCtx, f32 target) {
    return Math_StepToF(&csCtx->unk_0C, target, 0.1f);
}

void func_800EA258(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    Interface_ChangeAlpha(1);
    ShrinkWindow_SetLetterboxTarget(0x20);
    if (func_800EA220(globalCtx, csCtx, 1.0f)) {
        func_801A3F54(1);
        csCtx->state += 1;
    }
}

void func_800EA2B8(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    func_800ED980(globalCtx, csCtx);
    Interface_ChangeAlpha(1);
    ShrinkWindow_SetLetterboxTarget(0x20);
    if (func_800EA220(globalCtx, csCtx, 1.0f)) {
        func_801A3F54(1);
        csCtx->state += 1;
    }
}

extern u8 D_801BB130;
extern u16 D_801BB15C;
extern s8 D_801F4E68;
extern s16 D_801F4D42;

#ifdef NON_EQUIVALENT
// Command X: Misc. Actions
void func_800EA324(GlobalContext* globalCtx2, CutsceneContext* csCtx, CsCmdBase* cmd) {
    GlobalContext* globalCtx = globalCtx2;
    Player* player = GET_PLAYER(globalCtx);
    u8 sp3F = false;
    f32 temp_f0;
    u16 temp_t5;

    if ((csCtx->frames < cmd->startFrame) || (csCtx->frames >= cmd->endFrame && cmd->startFrame != cmd->endFrame)) {
        return;
    }

    temp_f0 = func_800F5A8C(cmd->endFrame - 1, cmd->startFrame, csCtx->frames);
    if (csCtx->frames == cmd->startFrame) {
        sp3F = true;
    }

    switch (cmd->base) {
    case 0x1:
        if (sp3F) {
            func_800FD78C(globalCtx);
            globalCtx->envCtx.unk_F2[0] = 0x3C;
        }
        break;
    case 0x2:
        if (sp3F) {
            func_801A47DC(0xF, 0, 0);
            func_800FB320(globalCtx, 3);
            D_801F4E68 = 1;
        }
        break;
    case 0x3:
        if (globalCtx->envCtx.unk_8C.fogFar < 12800) {
            globalCtx->envCtx.unk_8C.fogFar += 35;
        }
        break;
    case 0x4:
        if (sp3F) {
            globalCtx->envCtx.unk_19 = 1;
            globalCtx->envCtx.unk_17 = 1;
            globalCtx->envCtx.unk_18 = 0;
            globalCtx->envCtx.unk_1A = 0x3C;
            globalCtx->envCtx.unk_21 = 1;
            globalCtx->envCtx.unk_1F = 0;
            globalCtx->envCtx.unk_20 = 1;
            globalCtx->envCtx.unk_24 = 0x3C;
            globalCtx->envCtx.unk_22 = globalCtx->envCtx.unk_24;
        }
        break;
    case 0x5:
        if (sp3F && (csCtx->state != 4)) {
            csCtx->state = 3;
        }
        break;
    case 0x7:
        if (sp3F) {
            if (globalCtx->loadedScene->titleTextId != 0) {
                func_80151A68(globalCtx, globalCtx->loadedScene->titleTextId);
            }
        }
        break;
    case 0x8:
        func_8019F128(0x2150);
        if (sp3F) {
            D_801F4D42 = Quake_Add(GET_ACTIVE_CAM(globalCtx), 6);
            Quake_SetSpeed(D_801F4D42, 0x55F0);
            Quake_SetQuakeValues(D_801F4D42, 6, 4, 0, 0);
            Quake_SetCountdown(D_801F4D42, 800);
        }
        break;
    case 0x9:
        if (sp3F) {
            Quake_Init();
        }
        break;
    case 0xA:
        D_801F6D30.r = 0xFF;
        D_801F6D30.g = 0xFF;
        D_801F6D30.b = 0xFF;
        D_801F6D30.a = 0xFF * temp_f0;
        break;
    case 0xB:
        D_801F6D30.r = 0xFF;
        D_801F6D30.g = 0xB4;
        D_801F6D30.b = 0x64;
        D_801F6D30.a = 0xFF * temp_f0;
        break;
    case 0xC:
        globalCtx->roomCtx.currRoom.segment = NULL;
        break;
    case 0xD:
        if (globalCtx->state.frames & 8) {
            if (globalCtx->envCtx.unk_8C.ambientColor[0] < 0x28) {
                globalCtx->envCtx.unk_8C.ambientColor[0] += 2;
                globalCtx->envCtx.unk_8C.diffuseColor1[1] -= 3;
                globalCtx->envCtx.unk_8C.diffuseColor1[2] -= 3;
            }
        } else {
            if (globalCtx->envCtx.unk_8C.ambientColor[0] >= 3) {
                globalCtx->envCtx.unk_8C.ambientColor[0] -= 2;
                globalCtx->envCtx.unk_8C.diffuseColor1[1] += 3;
                globalCtx->envCtx.unk_8C.diffuseColor1[2] += 3;
            }
        }
        break;
    case 0xE:
        globalCtx->unk_18845 = 1;
        break;
    case 0xF:
        globalCtx->unk_18845 = 0;
        break;
    case 0x10:
        if (sp3F) {
            globalCtx->envCtx.unk_EA = 1;
        }
        func_8019F128(0x20C0);
        break;
    case 0x11:
        gSaveContext.unk_3F58 = 1;
        break;
    case 0x12:
        if (gSaveContext.isNight == 0) {
            gSaveContext.time -= (u16) gGameInfo->data[0xF];
        } else {
            gSaveContext.time -= 2 * gGameInfo->data[0xF];
        }
        break;
    case 0x13:
        func_8019D758(csCtx, csCtx->frames, cmd, globalCtx);
        csCtx->frames = cmd->startFrame - 1;
        break;
    case 0x14:
        EnvFlags_Set(globalCtx, 3);
        break;
    case 0x15:
        EnvFlags_Set(globalCtx, 4);
        break;
    case 0x16:
        gSaveContext.playerForm = PLAYER_FORM_DEKU;
        break;
    case 0x17:
        player->stateFlags2 |= 0x4000000;
        break;
    case 0x18:
        player->stateFlags2 &= ~0x4000000;
        break;
    case 0x19:
        D_801BB130 = gSaveContext.playerForm;
        gSaveContext.playerForm = 4;
        gSaveContext.equippedMask = 0;
        break;
    case 0x1A:
        func_8019F128(0x2159U);
        if (sp3F) {
            D_801F4D42 = Quake_Add(GET_ACTIVE_CAM(globalCtx), 6);
            Quake_SetSpeed(D_801F4D42, 30000);
            Quake_SetQuakeValues(D_801F4D42, 20, 10, 0, (s16) 0);
            Quake_SetCountdown(D_801F4D42, 800);
        }
        break;
    case 0x1B:
        if (sp3F) {
            globalCtx->nextEntranceIndex = 0x1C00;
            gSaveContext.nextCutsceneIndex = 0xFFF8;
            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->unk_1887F = 3;
        }
        break;
    case 0x1C:
        if (sp3F) {
            globalCtx->envCtx.unk_17 = 0xD;
        }
        break;
    case 0x1D:
        gSaveContext.playerForm = D_801BB130;
        break;
    case 0x1E:
        D_801F4DE0 = 1;
        break;
    case 0x1F:
        D_801F4DE0 = 0;
        break;
    case 0x21:
        if (sp3F) {
            func_80146EE8(globalCtx, csCtx->frames, cmd);
        }
        break;
    case 0x22:
        if (sp3F) {
            func_80144A94(&globalCtx->sramCtx, csCtx->frames, cmd);
        }
        break;
    case 0x23:
        if (D_801BB15C != csCtx->frames) {
            D_801BB15C = csCtx->frames;
            if (gGameInfo->data[0xF] != 0) {
                temp_t5 = gGameInfo->data[0xF] + gSaveContext.time;
                gSaveContext.time += temp_t5;
                gSaveContext.time = (u16)gSaveContext.unk_14 + temp_t5;
            }
        }
        break;
    case 0x24:
        func_8019F128(0x2150);
        if (sp3F) {
            D_801F4D42 = Quake_Add(GET_ACTIVE_CAM(globalCtx), 6);
            Quake_SetSpeed(D_801F4D42, 22000);
            Quake_SetQuakeValues(D_801F4D42, 2, 1, 0, 0);
            Quake_SetCountdown(D_801F4D42, 800);
        }
        break;
    case 0x26:
        gSaveContext.day = 9;

        {
            GameState* gameState = &globalCtx->state;
            gameState->running = false;
        }
        SET_NEXT_GAMESTATE(&globalCtx->state, Daytelop_Init, DaytelopContext);

        func_80146F5C(globalCtx, csCtx->frames, cmd);

    case 0x27:
        gSaveContext.playerForm = PLAYER_FORM_ZORA;
        break;

    case 0x28:
        csCtx->frames = cmd->startFrame - 1;
        break;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EA324.s")
#endif

void func_800EABAC(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdEnvLighting* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        if (cmd->setting != 0x20) {
            globalCtx->envCtx.unk_C3 = cmd->setting - 1;
            globalCtx->envCtx.unk_DC = 1.0f;
            return;
        } else {
            globalCtx->envCtx.unk_C3 = 0xFF;
        }
    }
}

void func_800EAC08(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicChange* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A2C88(cmd->sequence - 1);
    }
}

void func_800EAC44(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicChange* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        func_801A2D54(cmd->sequence - 1);
    }
}

void func_800EAC94(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicFade* cmd) {
    if ((csCtx->frames == cmd->startFrame) && (csCtx->frames < cmd->endFrame)) {
        u8 frameCount = (cmd->endFrame - cmd->startFrame);

        if (cmd->type == 2) {
            Audio_QueueSeqCmd((frameCount << 0x10) | 0x110000FF);
        } else {
            Audio_QueueSeqCmd((frameCount << 0x10) | NA_BGM_STOP);
        }
    }
}

void func_800EAD14(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A4A28(globalCtx->soundCtx.nightSeqIndex);
    }
}

void func_800EAD48(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A4428(2);
    }
}

void func_800EAD7C(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A4428(1);
    }
}

extern u16 D_801F4D40;

#ifdef NON_MATCHING
void func_800EADB0(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    s32 temp_a1;
    u16 temp_a0;
    s32 phi_a1;

    if (csCtx->frames == cmd->startFrame) {
        phi_a1 = (gSaveContext.day - 1) & 0xFF;
        if (phi_a1 >= 3) {
            phi_a1 = 0;
        }

        switch (cmd->base) {
        case 0x1:
            func_801A246C(0, 1);
            break;
        case 0x2:
            func_801A246C(0, 0);
            break;
        case 0x3:
            func_801A246C(0, 2);
            break;
        case 0x4:
            func_801A246C(4, 1);
            break;
        case 0x5:
            func_801A246C(4, 0);
            break;
        case 0x6:
            func_801A246C(4, 2);
            break;
        case 0x7:
            D_801F4D40 = func_801A8A50(0);
            break;
        case 0x8:
            temp_a0 = D_801F4D40;
            if (D_801F4D40 != 0xFFFF) {
                D_801F4D40 = temp_a0;
                func_801A25E4(temp_a0, phi_a1);
            }
            break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EADB0.s")
#endif

void func_800EAECC(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame && csCtx->frames < cmd->endFrame) {
        u8 frameCount = cmd->endFrame - cmd->startFrame;

        Audio_QueueSeqCmd((frameCount << 0x10) | 0x140000FF);
    }
}

void func_800EAF20(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdUnk190* cmd) {
    switch (cmd->unk0) {
        case 1:
            if (csCtx->frames == cmd->startFrame) {
                func_8013ECE0(0.0f, cmd->unk6, cmd->unk7, cmd->unk8);
            }
            break;

        case 2:
            if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames) && ((csCtx->frames == cmd->startFrame) || !(globalCtx->state.frames & 0x3F))) {
                func_8013ECE0(0.0f, cmd->unk6, cmd->unk7, cmd->unk8);
            }
            break;
    }
}

void func_800EAFE0(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdUnk9B* cmd) {
    f32 temp_f0;
    u16 temp_a0;
    u16 temp_a1;

    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        globalCtx->envCtx.unk_E5 = 1;
        temp_a1 = cmd->startFrame;
        temp_a0 = cmd->endFrame;
        temp_f0 = func_800F5A8C(temp_a0, temp_a1, csCtx->frames);

        if (((cmd->unk0 == 1)) || (cmd->unk0 == 2)) {
            globalCtx->envCtx.unk_E6[0] = cmd->unk6;
            globalCtx->envCtx.unk_E6[1] = cmd->unk7;
            globalCtx->envCtx.unk_E6[2] = cmd->unk8;

            if (cmd->unk0 == 2) {
                globalCtx->envCtx.unk_E6[3] = (u8) (u32) ((1.0f - temp_f0) * 255.0f);
            } else {
                globalCtx->envCtx.unk_E6[3] = (u8) (u32) (255.0f * temp_f0);
            }
        }
    }
}

void func_800EB1DC(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdDayTime* cmd) {
    u16 nextTime;
    u16 hourAsMinutes;
    u16 minutes;

    if (csCtx->frames == cmd->startFrame) {
        hourAsMinutes = (cmd->hour * 60.0f) / (60.0f * 24 / 0x10000);
        minutes = ((cmd->minute + 1) / (60.0f * 24 / 0x10000));

        nextTime = hourAsMinutes + minutes;
        gSaveContext.time = nextTime;
        gSaveContext.environmentTime = nextTime;
    }
}

#ifdef NON_MATCHING
// regalloc
void func_800EB364(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    s32 temp_a0;

    csCtx->state = 4;
    func_80165690();
    func_801A3F54(0);
    gSaveContext.unk_3F48 = 1;

    if ((gSaveContext.gameMode != 0) && (csCtx->frames != cmd->startFrame)) {
        gSaveContext.unk_3F1E = 1;
    }

    gSaveContext.cutscene = 0;
    if (cmd->base == 1) {
        globalCtx->nextEntranceIndex = (u16) globalCtx->csCtx.sceneCsList[globalCtx->csCtx.unk_12].unk4;
        gSaveContext.nextCutsceneIndex = 0;
        globalCtx->sceneLoadFlag = 0x14;
        if (gSaveContext.gameMode != 1) {
            Scene_SetExitFade(globalCtx);
        } else {
            D_801BB12C++;
            if (D_801BB12C >= 2) {
                D_801BB12C = 0;
            }
            globalCtx->unk_1887F = 4;
        }

        temp_a0 = globalCtx->nextEntranceIndex & 0xF;
        if (temp_a0 > 0) {
            gSaveContext.nextCutsceneIndex = temp_a0 + 0xFFEF;
        }

        globalCtx->nextEntranceIndex &= 0xFFF0;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB364.s")
#endif

extern s16 D_801F4DE2;

void func_800EB4B4(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (cmd->base == 1) {
        if (csCtx->frames == cmd->startFrame) {
            func_800EB364(globalCtx, csCtx, cmd);
        }
    } else if (cmd->base == 2) {
        if (csCtx->frames == cmd->startFrame) {
            func_80165690();

            switch (D_801F4DE2) {
                case 0x1F:
                    if (gSaveContext.weekEventReg[0x14] & 2)  {
                        globalCtx->nextEntranceIndex = 0x3010;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                    } else {
                        globalCtx->nextEntranceIndex = 0x8600;
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                    }
                    break;

                case 0x44:
                    if (gSaveContext.weekEventReg[0x21] & 0x80) {
                        globalCtx->nextEntranceIndex = 0xAE70;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                    } else {
                        globalCtx->nextEntranceIndex = 0xAE00;
                        gSaveContext.nextCutsceneIndex = 0xFFF0;
                        globalCtx->sceneLoadFlag = 0x14;
                        globalCtx->unk_1887F = 3;
                    }
                    break;

                case 0x5F:
                    gSaveContext.weekEventReg[0x37] |= 0x80;
                    globalCtx->nextEntranceIndex = 0x6A80;
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 3;
                    break;

                case 0x36:
                    gSaveContext.weekEventReg[0x34] |= 0x20;
                    globalCtx->nextEntranceIndex = 0x2000;
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 3;
                    break;
            }
        }
    }
}

void func_800EB6F8(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (func_801A3950(0, 1) != 0xFF)) {
        switch (cmd->base) {
            case 0x1:
                func_800EB364(globalCtx, csCtx, cmd);
                break;

            case 0x2:
                if (INV_CONTENT(ITEM_MASK_KAMARO) == ITEM_MASK_KAMARO) {
                    globalCtx->nextEntranceIndex = 0x2400;
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C00;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0x3:
                if (INV_CONTENT(ITEM_MASK_GREAT_FAIRY) == ITEM_MASK_GREAT_FAIRY) {
                    globalCtx->nextEntranceIndex = 0x4600;
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C10;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0x4:
                if (INV_CONTENT(ITEM_MASK_ROMANI) == ITEM_MASK_ROMANI) {
                    globalCtx->nextEntranceIndex = 0x6400;
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C20;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0x5:
                if (INV_CONTENT(ITEM_MASK_BLAST) == ITEM_MASK_BLAST) {
                    globalCtx->nextEntranceIndex = 0xD400;
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C30;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0x6:
                if (INV_CONTENT(ITEM_MASK_CIRCUS_LEADER) == ITEM_MASK_CIRCUS_LEADER) {
                    globalCtx->nextEntranceIndex = 0x2400;
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C50;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0x7:
                if (INV_CONTENT(ITEM_MASK_BREMEN) == ITEM_MASK_BREMEN) {
                    globalCtx->nextEntranceIndex = 0x2400;
                    gSaveContext.nextCutsceneIndex = 0xFFF3;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C60;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0x8:
                globalCtx->nextEntranceIndex = 0x2000;
                gSaveContext.nextCutsceneIndex = 0xFFF3;
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0x9:
                if (INV_CONTENT(ITEM_MASK_COUPLE) == ITEM_MASK_COUPLE) {
                    globalCtx->nextEntranceIndex = 0x5400;
                    gSaveContext.nextCutsceneIndex = 0xFFF8;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C70;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0xA:
                if (INV_CONTENT(ITEM_MASK_BUNNY) == ITEM_MASK_BUNNY) {
                    globalCtx->nextEntranceIndex = 0x7E00;
                    gSaveContext.nextCutsceneIndex = 0xFFF0;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C40;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;

            case 0xB:
                if (INV_CONTENT(ITEM_MASK_POSTMAN) == ITEM_MASK_POSTMAN) {
                    globalCtx->nextEntranceIndex = 0x5410;
                    gSaveContext.nextCutsceneIndex = 0xFFF8;
                } else {
                    globalCtx->nextEntranceIndex = 0x1C80;
                    gSaveContext.nextCutsceneIndex = 0xFFF9;
                }
                globalCtx->sceneLoadFlag = 0x14;
                break;
        }
    }
}

void func_800EBB68(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        if ((csCtx->frames == cmd->startFrame) && (cmd->base == 1)) {
            func_8016566C(0xB4);
        }

        if (cmd->base == 2) {
            f32  temp_f0 = func_800F5A8C(cmd->endFrame, cmd->startFrame, csCtx->frames);

            if (temp_f0 >= 0.9f) {
                func_80165690();
            } else {
                func_80165658((1.0f - temp_f0) * 180.0f);
            }
        }
    }
}

void func_800EBCD0(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    Player* player = GET_PLAYER(globalCtx);

    if ((csCtx->frames == cmd->startFrame) && (cmd->base == 1)) {
        gSaveContext.hasTatl = true;
        if (player->tatlActor != NULL) {
            return;
        }
        player->tatlActor = Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ELF, player->actor.world.pos.x, player->actor.world.pos.y, player->actor.world.pos.z, 0, 0, 0, 0);
    }
}

#ifdef NON_MATCHING
// regalloc
void func_800EBD60(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        f32 temp_f0;

        globalCtx->envCtx.unk_E5 = 1;
        temp_f0 = func_800F5A8C(cmd->endFrame, cmd->startFrame, csCtx->frames);

        switch (cmd->base) {
            case 0x1:
            case 0x5:
                globalCtx->envCtx.unk_E6[0] = 0xA0;
                globalCtx->envCtx.unk_E6[1] = 0xA0;
                globalCtx->envCtx.unk_E6[2] = 0xA0;
                if (cmd->base == 1) {
                    globalCtx->envCtx.unk_E6[3] = 255.0f * temp_f0;
                    if (temp_f0 == 0.0f) {
                        func_8019F128(0x2846);
                    }
                } else {
                    globalCtx->envCtx.unk_E6[3] = (1.0f - temp_f0) * 255.0f;
                }
                break;

            case 0x2:
            case 0x6:
                globalCtx->envCtx.unk_E6[0] = 0;
                globalCtx->envCtx.unk_E6[1] = 0;
                globalCtx->envCtx.unk_E6[2] = 0xFF;
                if (cmd->base == 2) {
                    globalCtx->envCtx.unk_E6[3] = 255.0f * temp_f0;
                } else {
                    globalCtx->envCtx.unk_E6[3] = (1.0f - temp_f0) * 255.0f;
                }
                break;

            case 0x3:
            case 0x7:
                globalCtx->envCtx.unk_E6[0] = 0xFF;
                globalCtx->envCtx.unk_E6[1] = 0;
                globalCtx->envCtx.unk_E6[2] = 0;
                if (cmd->base == 3) {
                    globalCtx->envCtx.unk_E6[3] = (1.0f - temp_f0) * 255.0f;
                } else {
                    globalCtx->envCtx.unk_E6[3] = 255.0f * temp_f0;
                }
                break;

            case 0x4:
            case 0x8:
                globalCtx->envCtx.unk_E6[0] = 0;
                globalCtx->envCtx.unk_E6[1] = 0xFF;
                globalCtx->envCtx.unk_E6[2] = 0;
                if (cmd->base == 4) {
                    globalCtx->envCtx.unk_E6[3] = (1.0f - temp_f0) * 255.0f;
                } else {
                    globalCtx->envCtx.unk_E6[3] = 255.0f * temp_f0;
                }
                break;

            case 0x9:
                gSaveContext.unk_3F48 = 1;
                break;

            case 0xA:
            case 0xB:
                globalCtx->envCtx.unk_E6[0] = 0;
                globalCtx->envCtx.unk_E6[1] = 0;
                globalCtx->envCtx.unk_E6[2] = 0;
                if (cmd->base == 0xA) {
                    globalCtx->envCtx.unk_E6[3] = (1.0f - temp_f0) * 255.0f;
                } else {
                    globalCtx->envCtx.unk_E6[3] = 255.0f * temp_f0;
                }
                break;

            case 0xC:
                globalCtx->envCtx.unk_E6[0] = (1.0f - temp_f0) * 160.0f;
                globalCtx->envCtx.unk_E6[1] = (1.0f - temp_f0) * 160.0f;
                globalCtx->envCtx.unk_E6[2] = (1.0f - temp_f0) * 160.0f;
                globalCtx->envCtx.unk_E6[3] = 0xFF;
                break;

            case 0xD:
                globalCtx->envCtx.unk_E6[0] = (160.0f * temp_f0);
                globalCtx->envCtx.unk_E6[1] = (160.0f * temp_f0);
                globalCtx->envCtx.unk_E6[2] = (160.0f * temp_f0);
                globalCtx->envCtx.unk_E6[3] = 0xFF;
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EBD60.s")
#endif

extern UNK_TYPE D_801F4D48;

// ??
s32 func_800EC678(GlobalContext* globalCtx, CsCmdUnk5A* cmd) {
    s32 sp1C = 0;

    bcopy(cmd, &sp1C, 4);
    cmd = (CsCmdUnk5A* ) &cmd->unk4;
    if (func_8016A168() == 0) {
        func_80161998(cmd, &D_801F4D48);
    }
    return sp1C + 4;
}

/**
 * Counts how many masks the player has
 * The count doesn't include transformation masks
 */
s32 func_800EC6D4(void) {
    s32 count = 0;

    if (INV_CONTENT(ITEM_MASK_TRUTH) == ITEM_MASK_TRUTH) {
        count++;
    }
    if (INV_CONTENT(ITEM_MASK_KAFEI) == ITEM_MASK_KAFEI) {
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

extern UNK_TYPE D_801BB160;
extern u16 D_801BB124;
extern u16 D_801BB128;

#ifdef NON_EQUIVALENT
void func_800EC924(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdTextbox* cmd) {
    u8 sp27;
    u16 sp1E;
    u16 temp_v0_2;

    if ((cmd->startFrame >= csCtx->frames) || ((cmd->endFrame < csCtx->frames))) {
        return;
    }

    if (cmd->type != 2) {
        if (cmd->base != D_801BB124) {
            if (D_801BB160 == 3) {
                csCtx->frames = csCtx->frames - 1;
            }
            D_801BB160 = 1;
            D_801BB124 = cmd->base;
            if (cmd->type == 4) {
                if (CHECK_QUEST_ITEM(0) && CHECK_QUEST_ITEM(1) && CHECK_QUEST_ITEM(2) && CHECK_QUEST_ITEM(3)) {
                    if (cmd->textId1 != 0xFFFF) {
                        func_801518B0(globalCtx, cmd->textId1, NULL);
                    }
                } else {
                    func_801518B0(globalCtx, cmd->base, NULL);
                }
            } else if (cmd->type == 5) {
                cmd = cmd;
                if (func_800EC6D4() == 0x14) {
                    if (cmd->textId1 != 0xFFFF) {
                        func_801518B0(globalCtx, cmd->textId1, NULL);
                    }
                } else {
                    func_801518B0(globalCtx, cmd->base, NULL);
                }
            } else {
                func_801518B0(globalCtx, cmd->base, NULL);
            }
        } else {
            goto block_22;
        }
    } else {
        temp_v0_2 = cmd->base;
        if (temp_v0_2 != D_801BB128) {
            D_801BB160 = 2;
            D_801BB128 = temp_v0_2;
            func_80152434(globalCtx, cmd->base);
            return;
        }
block_22:
        if (csCtx->frames >= cmd->endFrame) {
            sp1E = csCtx->frames;
            sp27 = func_80152498(&globalCtx->msgCtx);
            if (sp27 != 2) {
                if ((sp27 != 0) && (sp27 != 7) && (sp27 != 8)) {
                    csCtx->frames += -1;
                    if (sp27 == 4) {
                        cmd = cmd;
                        if (func_80147624(globalCtx) != 0) {
                            if (globalCtx->msgCtx.choiceIndex == 0) {
                                if (cmd->base == 0x33BD) {
                                    cmd = cmd;
                                    func_8019F230();
                                }

                                if (cmd->textId1 != 0xFFFF) {
                                    cmd = cmd;
                                    func_80151938(globalCtx, cmd->textId1);
                                    if (cmd->type == 3) {
                                        D_801BB160 = 3;
                                        if (cmd->textId2 != 0xFFFF) {
                                            csCtx->frames += 1;
                                        }
                                    }
                                } else {
                                    cmd = cmd;
                                    func_801477B4(globalCtx);
                                    csCtx->frames += 1;
                                }
                            } else {
                                if (cmd->base == 0x33BD) {
                                    cmd = cmd;
                                    func_8019F208();
                                }

                                if (cmd->textId2 != 0xFFFF) {
                                    cmd = cmd;
                                    func_80151938(globalCtx, cmd->textId2);
                                    if (cmd->type == 3) {
                                        D_801BB160 = 3;
                                        if (cmd->textId1 != 0xFFFF) {
                                            csCtx->frames += 1;
                                        }
                                    }
                                } else {
                                    cmd = cmd;
                                    func_801477B4(globalCtx);
                                    csCtx->frames += 1;
                                }
                            }
                        }
                    }

                    if (sp27 == 5) {
                        if (func_80147624(globalCtx) != 0) {
                            func_80152434(globalCtx, cmd->base);
                        }
                    }
                }
            }
            if ((sp27 == 2) && (D_801BB160 == 3)) {
                csCtx->frames += -1;
                D_801BB124 = D_801BB124 + 1;
            }
            if (csCtx->frames == sp1E) {
                Interface_ChangeAlpha(1U);
                D_801BB124 = 0;
                D_801BB128 = 0;
                func_80161C0C();
                return;
            }
            func_80161BE0(1);
        }
    }
    
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EC924.s")
#endif

void func_800ECD7C(CutsceneContext* csCtx, u8** cutscenePtr, s16 index) {
    s32 i;
    s32 sp30;

    bcopy(*cutscenePtr, &sp30, sizeof(s32));
    *cutscenePtr += 4;

    for (i = 0; i < sp30; i++) {
        CsCmdActorAction* temp_v0 = *(CsCmdActorAction**)cutscenePtr;

        if ((csCtx->frames >= temp_v0->startFrame) && (csCtx->frames < temp_v0->endFrame)) {
            csCtx->npcActions[index] = temp_v0;
        }

        *cutscenePtr += 0x30;
    }
}

#ifdef NON_EQUIVALENT
// I haven't checked equivalence tho
void Cutscene_ProcessCommands(GlobalContext* globalCtx, CutsceneContext* csCtx, u8* cutscenePtr) {
    s32 i;
    s32 totalEntries;
    u32 sp5C;
    s32 sp58;
    s32 sp50;
    u16 temp_v0;
    u16* temp_v1;
    s16 phi_s0;
    s32 phi_s0_12;
    s32 phi_s0_23;
    s32 j;

    bcopy(cutscenePtr, &totalEntries, 4U);
    cutscenePtr = cutscenePtr + 4;
    bcopy(cutscenePtr, &sp50, 4U);
    cutscenePtr += 4;
    if (((s16) sp50 < csCtx->frames) && (globalCtx->sceneLoadFlag != 0x14) && (csCtx->state != 4)) {
        csCtx->state = 3;
        return;
    }

    for (i = 0; i < totalEntries; i++) {
        bcopy(cutscenePtr, &sp5C, 4U);
        cutscenePtr = cutscenePtr + 4;
        if (sp5C == -1) {
            break;
        }
        if (((sp5C >= 0x64U) && (sp5C < 0x96U)) || (sp5C == 0xC9) || ((sp5C >= 0x1C2U) && (sp5C < 0x258U))) {
            phi_s0 = 0;
loop_13:

            temp_v1 = &D_801F4DC8[phi_s0];
            temp_v0 = *temp_v1;
            if ((sp5C & 0xFFFF) == temp_v0) {
                func_800ECD7C(csCtx, &cutscenePtr, phi_s0);
                sp5C = -2U;
            } else if (temp_v0 == 0) {
                *temp_v1 = (u16) sp5C;
                func_800ECD7C(csCtx, &cutscenePtr, phi_s0);
                sp5C = -2U;
            } else {
                phi_s0 = phi_s0 + 1;
                if (phi_s0 < 0xA) {
                    goto loop_13;
                }
            }
        }
        if (sp5C >= 0x133U) {
            switch (sp5C) {                   /* switch 3; irregular */
            default:                            /* switch 3 */
                if (sp5C != -2) {
                    goto block_120;
                }
                break;
            case 0x190:                         /* switch 3 */
                bcopy(cutscenePtr, &sp58, 4U);
                cutscenePtr = cutscenePtr + 4;
                for (j = 0; j < sp58; j++) {
                    func_800EAF20(globalCtx, csCtx, (CsCmdUnk190* ) cutscenePtr);
                    cutscenePtr = cutscenePtr + 0xC;
                }
                break;
            case 0x15E:                         /* switch 3 */
                bcopy(cutscenePtr, &sp58, 4U);
                cutscenePtr = cutscenePtr + 4;
                for (j = 0; j < sp58; j++) {
                    func_800EB4B4(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                    cutscenePtr = cutscenePtr + 8;
                }
                break;
            case 0x15F:                         /* switch 3 */
                bcopy(cutscenePtr, &sp58, 4U);
                cutscenePtr = cutscenePtr + 4;
                for (j = 0; j < sp58; j++) {
                    func_800EB6F8(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                    cutscenePtr = cutscenePtr + 8;
                }
                break;
            }
        } else if (sp5C >= 0x9EU) {
            if (sp5C >= 0xC9U) {
                switch (sp5C) {               /* switch 1 */
                case 0x12C:                     /* switch 1 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EAC08(globalCtx, csCtx, (CsCmdMusicChange* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x12D:                     /* switch 1 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EAC44(globalCtx, csCtx, (CsCmdMusicChange* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x12E:                     /* switch 1 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                            func_800EAD14(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                            cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x12F:                     /* switch 1 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EAECC(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x130:                     /* switch 1 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EAD48(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x131:                     /* switch 1 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EAD7C(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x132:                     /* switch 1 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EADB0(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                }
            } else {
                if (sp5C != 0xC8) {
                    goto block_120;
                }
                bcopy(cutscenePtr, &sp58, 4U);
                cutscenePtr = cutscenePtr + 4;
                if (sp58 > 0) {
                    phi_s0_12 = 0;
                    if (sp58 & 3 != 0) {
                        while ((sp58 & 3) != phi_s0_12) {
                            if (((s32) csCtx->frames >= ((CsCmdBase*)cutscenePtr)->startFrame) && ((s32) csCtx->frames < ((CsCmdBase*)cutscenePtr)->endFrame)) {
                                csCtx->linkAction = (CsCmdActorAction* ) cutscenePtr;
                            }
                            phi_s0_12 = phi_s0_12 + 1;
                            cutscenePtr = cutscenePtr + 0x30;
                        }
                        if (phi_s0_12 != sp58) {
                            goto block_83;
                        }
                    } else {
block_83:
                        do {
                            if ((csCtx->frames >= ((CsCmdBase*)cutscenePtr)->startFrame) && (csCtx->frames < ((CsCmdBase*)cutscenePtr)->endFrame)) {
                                csCtx->linkAction = (CsCmdActorAction* ) cutscenePtr;
                            }
                            cutscenePtr = cutscenePtr + 0x30;
                            if ((csCtx->frames >= ((CsCmdBase*)cutscenePtr)->startFrame) && (csCtx->frames < ((CsCmdBase*)cutscenePtr)->endFrame)) {
                                csCtx->linkAction = (CsCmdActorAction* ) cutscenePtr;
                            }
                            cutscenePtr = cutscenePtr + 0x30;
                            if ((csCtx->frames >= ((CsCmdBase*)cutscenePtr)->startFrame) && (csCtx->frames < ((CsCmdBase*)cutscenePtr)->endFrame)) {
                                csCtx->linkAction = (CsCmdActorAction* ) cutscenePtr;
                            }
                            cutscenePtr = cutscenePtr + 0x30;
                            if ((csCtx->frames >= ((CsCmdBase*)cutscenePtr)->startFrame) && (csCtx->frames < ((CsCmdBase*)cutscenePtr)->endFrame)) {
                                csCtx->linkAction = (CsCmdActorAction* ) cutscenePtr;
                            }
                            phi_s0_12 = phi_s0_12 + 4;
                            cutscenePtr = cutscenePtr + 0x30;
                        } while (phi_s0_12 != sp58);
                    }
                }
            }
        } else {
            if (sp5C >= 0x5B) {
                switch (sp5C) {               /* switch 2 */
                case 0x96:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EA324(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr += 8;
                    }
                    break;
                case 0x97:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EABAC(globalCtx, csCtx, (CsCmdEnvLighting* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x9C:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EAC94(globalCtx, csCtx, (CsCmdMusicFade* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 0xC;
                    }
                    break;
                case 0x9B:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EAFE0(globalCtx, csCtx, (CsCmdUnk9B* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 0xC;
                    }
                    break;
                case 0x9D:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EB1DC(globalCtx, csCtx, (CsCmdDayTime* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 0xC;
                    }
                    break;
                case 0x98:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EBD60(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x99:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EBB68(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                case 0x9A:                      /* switch 2 */
                    bcopy(cutscenePtr, &sp58, 4U);
                    cutscenePtr = cutscenePtr + 4;
                    for (j = 0; j < sp58; j++) {
                        func_800EBCD0(globalCtx, csCtx, (CsCmdBase* ) cutscenePtr);
                        cutscenePtr = cutscenePtr + 8;
                    }
                    break;
                }
            } else if (sp5C == 0xA) {
                bcopy(cutscenePtr, &sp58, 4U);
                cutscenePtr = cutscenePtr + 4;
                for (j = 0; j < sp58; j++) {
                    if (((CsCmdTextbox*)cutscenePtr)->base != 0xFFFF) {
                        func_800EC924(globalCtx, csCtx, (CsCmdTextbox* ) cutscenePtr);
                    }
                    cutscenePtr = cutscenePtr + 0xC;
                }

            } else if (sp5C == 0x5A) {
                cutscenePtr = &cutscenePtr[func_800EC678(globalCtx, (CsCmdUnk5A* ) cutscenePtr)];
            } else {
            //default:                        /* switch 2 */
            //default:                        /* switch 1 */
block_120:
                bcopy(cutscenePtr, &sp58, 4U);
                cutscenePtr = cutscenePtr + 4;
                if (sp58 > 0) {
                    phi_s0_23 = 0 + 4;
                    if (sp58 & 3) {
                        do {
                            phi_s0_23 = phi_s0_23 + 1;
                            cutscenePtr = cutscenePtr + 8;
                        } while (phi_s0_23 != sp58);
                        phi_s0_23 = phi_s0_23 + 4;
                        if (phi_s0_23 != sp58) {
                            goto loop_124;
                        }
                    } else {
                        do {
loop_124:
                            cutscenePtr = cutscenePtr + 0x20;
                        } while (phi_s0_23 != sp58);
                    }
                }
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_ProcessCommands.s")
#endif

void func_800ED980(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (gSaveContext.cutscene >= 0xFFF0) {
        csCtx->frames += 1;
        Cutscene_ProcessCommands(globalCtx, csCtx, globalCtx->csCtx.segment);
    }
}

void func_800ED9C4(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (func_800EA220(globalCtx, csCtx, 0.0f)) {
        func_801A3F54(0);
        csCtx->state = 0;
    }
}

void func_800EDA04(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (func_800EA220(globalCtx, csCtx, 0.0f)) {
        s16 i;

        csCtx->linkAction = NULL;

        for (i = 0; i < ARRAY_COUNT(csCtx->npcActions); i++) {
            csCtx->npcActions[i] = NULL;
        }

        gSaveContext.cutscene = 0;
        gSaveContext.gameMode = 0;
        ActorCutscene_Stop(0x7F);
        func_801A3F54(0);
        csCtx->state = 0;
    }
}

void func_800EDA84(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if ((gSaveContext.cutsceneTrigger != 0) && (csCtx->state == 0) && (func_801233E4(globalCtx) == 0)) {
        gSaveContext.cutscene = 0xFFFD;
    }

    if (gSaveContext.cutscene >= 0xFFF0) {
        if (csCtx->state == 0) {
            s16 i;

            D_801BB124 = 0;
            D_801BB128 = 0;
            csCtx->linkAction = NULL;

            for (i = 0; i < ARRAY_COUNT(csCtx->npcActions); i++) {
                csCtx->npcActions[i] = NULL;
            }

            csCtx->state++;
            if (csCtx->state == 1) {
                func_801A3F54(1);

                csCtx->frames = 0xFFFF;
                csCtx->unk_14 = ActorCutscene_GetCurrentCamera(0x7F);
                func_8016119C(Play_GetCamera(globalCtx, csCtx->unk_14), &D_801F4D48);
                csCtx->unk_18 = 0xFFFF;

                if (gSaveContext.cutsceneTrigger == 0) {
                    Interface_ChangeAlpha(1);
                    ShrinkWindow_SetLetterboxTarget(0x20);
                    ShrinkWindow_SetLetterboxMagnitude(0x20);
                    csCtx->state += 1;
                }

                func_800ED980(globalCtx, csCtx);
            }

            gSaveContext.cutsceneTrigger = 0;
        }
    }
}

#ifdef NON_MATCHING
void func_800EDBE0(GlobalContext* globalCtx) {
    CutsceneEntry* temp_a3;
    s16 sp2A;
    SceneTableEntry* sp24;
    s32 temp_v0_3;

    if (((gSaveContext.gameMode == 0) || (gSaveContext.gameMode == 1)) && (gSaveContext.respawnFlag <= 0)) {
        sp2A = func_800F21CC();
        if (sp2A != -1) {
            temp_v0_3 = func_800F2138(sp2A);
            if (temp_v0_3 != -1) {
                temp_a3 = ((void)0, globalCtx->csCtx.sceneCsList);
                if ((temp_a3[temp_v0_3].unk7 != 0xFF) && (gSaveContext.respawnFlag == 0)) {
                    if (temp_a3[temp_v0_3].unk7 == 0xFE)
                    {
                        ActorCutscene_Start(sp2A, NULL);
                        gSaveContext.showTitleCard = 0;
                    }
                    else
                    if (!((1 << (temp_a3[temp_v0_3].unk7 % 8)) & gSaveContext.weekEventReg[temp_a3[temp_v0_3].unk7 / 8]))
                    {
                        gSaveContext.weekEventReg[(temp_a3[temp_v0_3].unk7 / 8)] |= 1 << (temp_a3[temp_v0_3].unk7 % 8);
                        ActorCutscene_Start(sp2A, NULL);
                        gSaveContext.showTitleCard = 0;
                    }
                }
            } else {
                ActorCutscene_StartAndSetUnkLinkFields(sp2A, NULL);
            }
        }
    }

    if ((gSaveContext.respawnFlag == 0) || (gSaveContext.respawnFlag == -2)) {
        sp24 = globalCtx->loadedScene;
        if ((sp24->titleTextId != 0) && (gSaveContext.showTitleCard != 0)) {
            if ((Entrance_GetTransitionFlags(gSaveContext.sceneSetupIndex + gSaveContext.entranceIndex) & 0x4000) != 0) {
                func_80151A68(globalCtx, sp24->titleTextId);
            }
        }
        gSaveContext.showTitleCard = 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDBE0.s")
#endif

void nop_800EDDB0(GlobalContext* globalCtx) {

}

void func_800EDDBC(UNK_TYPE arg0, UNK_TYPE arg1) {

}

void func_800EDDCC(GlobalContext* globalCtx, u8 arg1) {
    if (gGameInfo->data[0xA1F] == 0) {
        globalCtx->csCtx.unk_12 = arg1;
        globalCtx->csCtx.segment = Lib_SegmentedToVirtual(globalCtx->csCtx.sceneCsList[arg1].data);
    }

    gSaveContext.cutsceneTrigger = 1;
}

void func_800EDE34(Actor* actor, GlobalContext* globalCtx, s32 index) {
    Vec3f sp24;
    Vec3f sp18;
    CsCmdActorAction* entry = globalCtx->csCtx.npcActions[index];
    f32 temp_f0;

    sp24.x = entry->startPos.x;
    sp24.y = entry->startPos.y;
    sp24.z = entry->startPos.z;
    sp18.x = entry->endPos.x;
    sp18.y = entry->endPos.y;
    sp18.z = entry->endPos.z;

    temp_f0 = func_800F5A8C(entry->endFrame, entry->startFrame, globalCtx->csCtx.frames);
    actor->world.pos.x = ((sp18.x - sp24.x) * temp_f0) + sp24.x;
    actor->world.pos.y = ((sp18.y - sp24.y) * temp_f0) + sp24.y;
    actor->world.pos.z = ((sp18.z - sp24.z) * temp_f0) + sp24.z;
}

void func_800EDF24(Actor* actor, GlobalContext* globalCtx, u32 arg2) {
    func_800EDE34(actor, globalCtx, arg2);
    actor->world.rot.y = (u16)globalCtx->csCtx.npcActions[arg2]->urot.y;
    actor->shape.rot.y = actor->world.rot.y;
}

void func_800EDF78(Actor* actor, GlobalContext* globalCtx, s32 iParm3) {
    Vec3f sp44;
    Vec3f sp38;
    CsCmdActorAction* entry;
    f32 temp_f0;

    sp44.x = (f32) globalCtx->csCtx.npcActions[iParm3]->startPos.x;
    sp44.y = (f32) globalCtx->csCtx.npcActions[iParm3]->startPos.y;
    sp44.z = (f32) globalCtx->csCtx.npcActions[iParm3]->startPos.z;
    sp38.x = (f32) globalCtx->csCtx.npcActions[iParm3]->endPos.x;
    sp38.y = (f32) globalCtx->csCtx.npcActions[iParm3]->endPos.y;
    sp38.z = (f32) globalCtx->csCtx.npcActions[iParm3]->endPos.z;

    entry = globalCtx->csCtx.npcActions[iParm3];
    temp_f0 = func_800F5A8C(entry->endFrame, entry->startFrame, globalCtx->csCtx.frames);

    actor->world.pos.x = ((sp38.x - sp44.x) * temp_f0) + sp44.x;
    actor->world.pos.y = ((sp38.y - sp44.y) * temp_f0) + sp44.y;
    actor->world.pos.z = ((sp38.z - sp44.z) * temp_f0) + sp44.z;

    Math_SmoothStepToS(&actor->world.rot.y, Math_Vec3f_Yaw(&sp44, &sp38), 10, 1000, 1);
    actor->shape.rot.y = actor->world.rot.y;
}

void func_800EE0CC(Actor* actor, GlobalContext* globalCtx, s32 arg2) {
    Vec3f sp44;
    Vec3f sp38;
    CsCmdActorAction* entry;
    f32 temp_f0;

    sp44.x = globalCtx->csCtx.npcActions[arg2]->startPos.x;
    sp44.z = globalCtx->csCtx.npcActions[arg2]->startPos.z;
    sp38.x = globalCtx->csCtx.npcActions[arg2]->endPos.x;
    sp38.z = globalCtx->csCtx.npcActions[arg2]->endPos.z;

    entry = globalCtx->csCtx.npcActions[arg2];
    temp_f0 = func_800F5A8C(entry->endFrame, entry->startFrame, globalCtx->csCtx.frames);

    actor->world.pos.x = ((sp38.x - sp44.x) * temp_f0) + sp44.x;
    actor->world.pos.z = ((sp38.z - sp44.z) * temp_f0) + sp44.z;

    Math_SmoothStepToS(&actor->world.rot.y, Math_Vec3f_Yaw(&sp44, &sp38), 10, 1000, 1);
    actor->shape.rot.y = actor->world.rot.y;
}

s32 func_800EE1D8(GlobalContext* globalCtx) {
    s32 phi_v1 = 0;

    if (gSaveContext.sceneSetupIndex > 0) {
        phi_v1 = gSaveContext.sceneSetupIndex;
    }
    return phi_v1;
}

s32 func_800EE200(GlobalContext* globalCtx, u16 arg1) {
    s32 i;
    s32 phi_v1 = -1;

    for (i = 0; i < ARRAY_COUNT(D_801F4DC8); i++) {
        if (arg1 == D_801F4DC8[i]) {
            phi_v1 = i;
        }
    }

    return phi_v1;
}

s32 func_800EE29C(GlobalContext* globalCtx, u16 arg1) {

    if (globalCtx->csCtx.state != 0) {
        s32 index = func_800EE200(globalCtx, arg1);

        if (index != -1) {
            return globalCtx->csCtx.npcActions[index] != 0;
        }
    }

    return 0;
}

u8 func_800EE2F4(GlobalContext* globalCtx) {
    return gSaveContext.cutsceneTrigger != 0 || globalCtx->csCtx.state != 0;
}
