#include "global.h"

extern CutsceneCamera* sCurCsCamera;

// function declarations
s16 func_80161180(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_8016237C(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_8016253C(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_80162A50(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_801623E4(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_80161C20(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_80161E4C(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_801620CC(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
s16 func_80163334(Vec3f* pos, f32* fov, s16* roll, CutsceneCameraCmd1Cmd2* arg3, CutsceneCameraCmd3* arg4,
                  SubCutsceneCamera* arg5);
f32 func_80163660(Actor* actor);

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80161180.s")

/**
 * Initializes Cutscene Camera Info
 */
s32 CutsceneCamera_Init(Camera* camera, CutsceneCamera* csCamera) {
    csCamera->camera = camera;

    csCamera->unk_08 = csCamera->unk_0A = 0;
    csCamera->cmdIndex = 0;
    csCamera->unk_00 = -1;
    csCamera->unk_04 = 1;
    csCamera->unk_06 = 0;

    sCurCsCamera = csCamera;

    __osMemset(&csCamera->eyeInterp, 0, sizeof(SubCutsceneCamera));
    __osMemset(&csCamera->atInterp, 0, sizeof(SubCutsceneCamera));

    csCamera->eyeInterp.unk_2D = csCamera->atInterp.unk_2D = 7;

    return 1;
}

s16 (*CutsceneCamera_Interpolate(u8 interpType))(Vec3f*, f32*, s16*, CutsceneCameraCmd1Cmd2*, CutsceneCameraCmd3*,
                                                 SubCutsceneCamera*) {
    switch (interpType) {
        case 7:
        default:
            return func_80161180;

        case 0:
            return func_8016237C;

        case 5:
            return func_8016253C;

        case 4:
            return func_80162A50;

        case 1:
            return func_801623E4;

        case 2:
            return func_80161C20;

        case 3:
            return func_80161E4C;

        case 6:
            return func_801620CC;
    }
}

u8 CutsceneCamera_ProcessSubCommands(CutsceneCamera* csCamera) {
    s32 sp5C;
    f32* fov;
    s16* roll;
    s16 (*interpHandler)(Vec3f*, f32*, s16*, CutsceneCameraCmd1Cmd2*, CutsceneCameraCmd3*, SubCutsceneCamera*);
    Player* player;
    Actor* target;
    s16 sp46;

    sp5C = true;
    if (csCamera->unk_06 == 3) {
        return false;
    }

    player = GET_PLAYER(csCamera->camera->play);
    target = csCamera->camera->target;

    if (csCamera->eyeCmd[csCamera->atInterp.unk_2C].subCmd1Cmd2[0].interpType <
        csCamera->atCmd[csCamera->eyeInterp.unk_2C].subCmd1Cmd2[0].interpType) {
        sp5C = false;
    }

    csCamera->eyeInterp.unk_00 = csCamera->camera->eye;
    csCamera->atInterp.unk_00 = csCamera->camera->at;

    if (sp5C) {
        fov = NULL;
    } else {
        fov = &csCamera->camera->fov;
    }

    if (sp5C) {
        roll = NULL;
    } else {
        roll = &csCamera->camera->roll;
    }

    interpHandler = CutsceneCamera_Interpolate(csCamera->atCmd[csCamera->eyeInterp.unk_2C].subCmd1Cmd2[0].interpType);

    switch (csCamera->atCmd[csCamera->eyeInterp.unk_2C].subCmd1Cmd2[0].unk_0A) {
        case 2:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        case 3:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case 1:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case 4:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case 5:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        default:
            break;
    }

    sp46 = interpHandler(&csCamera->camera->at, fov, roll, &csCamera->atCmd[csCamera->eyeInterp.unk_2C],
                         &csCamera->cmd3[csCamera->eyeInterp.unk_2C], &csCamera->eyeInterp);

    switch (csCamera->atCmd[csCamera->eyeInterp.unk_2C].subCmd1Cmd2[0].unk_0A) {
        case 2:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        case 3:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            csCamera->camera->at.y += func_80163660(&player->actor);
            break;

        case 1:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case 4:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case 5:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        default:
            break;
    }

    csCamera->eyeInterp.unk_2C += sp46;

    if (sp5C) {
        fov = &csCamera->camera->fov;
    } else {
        fov = NULL;
    }

    if (sp5C) {
        roll = &csCamera->camera->roll;
    } else {
        roll = NULL;
    }

    interpHandler = CutsceneCamera_Interpolate(csCamera->eyeCmd[csCamera->atInterp.unk_2C].subCmd1Cmd2[0].interpType);

    switch (csCamera->eyeCmd[csCamera->atInterp.unk_2C].subCmd1Cmd2[0].unk_0A) {
        case 2:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        case 3:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case 1:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case 4:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case 5:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        default:
            break;
    }

    sp46 = interpHandler(&csCamera->camera->eye, fov, roll, &csCamera->eyeCmd[csCamera->atInterp.unk_2C],
                         &csCamera->cmd3[csCamera->atInterp.unk_2C], &csCamera->atInterp);

    switch (csCamera->eyeCmd[csCamera->atInterp.unk_2C].subCmd1Cmd2[0].unk_0A) {
        case 2:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        case 3:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            csCamera->camera->eye.y += func_80163660(&player->actor);
            break;

        case 1:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case 4:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case 5:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        default:
            break;
    }

    csCamera->atInterp.unk_2C += sp46;

    if ((csCamera->eyeInterp.unk_2C >= csCamera->eyeInterp.numEntries) ||
        (csCamera->atInterp.unk_2C >= csCamera->atInterp.numEntries)) {
        return false;
    }

    return true;
}

/**
 * Processes camera cutscene commands
 */
s32 CutsceneCamera_ProcessCommands(u8* cmd, CutsceneCamera* csCamera) {
    CutsceneCameraCmdHeader* cmdHeader;

    switch (csCamera->unk_06) {
        case 999:
            return 0;

        case 2:
            return csCamera->unk_08;

        case 1:
            if (csCamera->unk_0C >= csCamera->unk_0A) {
                csCamera->unk_0A++;
                if (csCamera->unk_0C >= csCamera->unk_0A) {
                    // Process SubCommands
                    if (!CutsceneCamera_ProcessSubCommands(csCamera)) {
                        csCamera->unk_06 = 3;
                    }
                }
            }
            break;

        case 3:
            break;

        default:
            if (csCamera->unk_04 == 1) {
                // Header
                cmdHeader = (CutsceneCameraCmdHeader*)&cmd[csCamera->cmdIndex];
                csCamera->atInterp.numEntries = csCamera->eyeInterp.numEntries = cmdHeader->numEntries;
                csCamera->unk_0C = cmdHeader->unk_06;
                csCamera->cmdIndex += sizeof(CutsceneCameraCmdHeader);

                // First Command (at)
                csCamera->atCmd = (CutsceneCameraCmd1Cmd2*)&cmd[csCamera->cmdIndex];
                csCamera->cmdIndex += (s16)(csCamera->eyeInterp.numEntries * sizeof(CutsceneCameraCmd1Cmd2));

                // Second Command (eye)
                csCamera->eyeCmd = (CutsceneCameraCmd1Cmd2*)&cmd[csCamera->cmdIndex];
                csCamera->cmdIndex += (s16)(csCamera->eyeInterp.numEntries * sizeof(CutsceneCameraCmd1Cmd2));

                // Third Command
                csCamera->cmd3 = (CutsceneCameraCmd3*)&cmd[csCamera->cmdIndex];
                csCamera->cmdIndex += (s16)(csCamera->eyeInterp.numEntries * sizeof(CutsceneCameraSubCmd3));

                // Other Params
                csCamera->eyeInterp.unk_2C = 0;
                csCamera->atInterp.unk_2C = 0;

                csCamera->unk_04 = 0;
                csCamera->unk_00 = (csCamera->unk_00 & 0xFFFF) + 1;
                csCamera->unk_06 = 0;
                csCamera->unk_08 = csCamera->unk_0A = 0;
                csCamera->eyeInterp.unk_2D = csCamera->atInterp.unk_2D = 7;
            }

            csCamera->unk_08++;

            if (csCamera->unk_0C >= csCamera->unk_0A) {
                csCamera->unk_0A++;
                if (csCamera->unk_0C >= csCamera->unk_0A) {
                    // Process SubCommands
                    if (!CutsceneCamera_ProcessSubCommands(csCamera)) {
                        csCamera->unk_06 = 3;
                    }
                }
            }
            break;
    }

    if (csCamera->unk_0C < csCamera->unk_08) {
        csCamera->unk_04 = 1;
        cmdHeader = (CutsceneCameraCmdHeader*)&cmd[csCamera->cmdIndex];
        if (cmdHeader->numEntries == -1) {
            csCamera->unk_06 = 999;
            return 0;
        }
    }

    return csCamera->unk_08;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80161BAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80161BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80161C0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80161C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80161E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_801620CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_8016237C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_801623E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_801624EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_8016253C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_801629BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80162A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80162FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_801631DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80163334.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80163660.s")
