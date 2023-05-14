#include "global.h"

extern CutsceneCamera* sCurCsCamera;

typedef s16 (*CsCamInterpolateCallback)(Vec3f*, f32*, s16*, CsCmdCamPoint*, CsCmdCamMisc*, CutsceneCameraInterp*);

// function declarations
s16 func_80161180(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_8016237C(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_8016253C(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_80162A50(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_801623E4(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_80161C20(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_80161E4C(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_801620CC(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
s16 func_80163334(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp);
f32 func_80163660(Actor* actor);

#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80161180.s")

/**
 * Initializes Cutscene Camera Info
 */
s32 CutsceneCamera_Init(Camera* camera, CutsceneCamera* csCamera) {
    csCamera->camera = camera;

    csCamera->nextSplineTimer = csCamera->updateSplineTimer = 0;
    csCamera->cmdIndex = 0;
    csCamera->splineIndex = 0xFFFF;
    csCamera->splineNeedsInit = true;
    csCamera->state = CS_CAM_STATE_UPDATE_ALL;

    sCurCsCamera = csCamera;

    __osMemset(&csCamera->eyeInterp, 0, sizeof(CutsceneCameraInterp));
    __osMemset(&csCamera->atInterp, 0, sizeof(CutsceneCameraInterp));

    csCamera->eyeInterp.unk_2D = csCamera->atInterp.unk_2D = 7;

    return 1;
}

CsCamInterpolateCallback CutsceneCamera_Interpolate(u8 interpType) {
    switch (interpType) {
        case CS_CAM_INTERP_7:
        default:
            return func_80161180;

        case CS_CAM_INTERP_0:
            return func_8016237C;

        case CS_CAM_INTERP_5:
            return func_8016253C;

        case CS_CAM_INTERP_4:
            return func_80162A50;

        case CS_CAM_INTERP_1:
            return func_801623E4;

        case CS_CAM_INTERP_2:
            return func_80161C20;

        case CS_CAM_INTERP_3:
            return func_80161E4C;

        case CS_CAM_INTERP_6:
            return func_801620CC;
    }
}

u8 CutsceneCamera_ProcessSpline(CutsceneCamera* csCamera) {
    s32 sp5C;
    f32* fov;
    s16* roll;
    CsCamInterpolateCallback interpHandler;
    Player* player;
    Actor* target;
    s16 numPoints;

    sp5C = true;
    if (csCamera->state == CS_CAM_STATE_DONE_SPLINE) {
        return false;
    }

    player = GET_PLAYER(csCamera->camera->play);
    target = csCamera->camera->target;

    if (csCamera->eyeCmd[csCamera->atInterp.curPoint].interpType <
        csCamera->atCmd[csCamera->eyeInterp.curPoint].interpType) {
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

    interpHandler = CutsceneCamera_Interpolate(csCamera->atCmd[csCamera->eyeInterp.curPoint].interpType);

    switch (csCamera->atCmd[csCamera->eyeInterp.curPoint].relativeTo) {
        case CS_CAM_REL_2:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        case CS_CAM_REL_3:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case CS_CAM_REL_1:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case CS_CAM_REL_4:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case CS_CAM_REL_5:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        default: // CS_CAM_REL_0
            break;
    }

    numPoints = interpHandler(&csCamera->camera->at, fov, roll, &csCamera->atCmd[csCamera->eyeInterp.curPoint],
                              &csCamera->miscCmd[csCamera->eyeInterp.curPoint], &csCamera->eyeInterp);

    switch (csCamera->atCmd[csCamera->eyeInterp.curPoint].relativeTo) {
        case CS_CAM_REL_2:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        case CS_CAM_REL_3:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            csCamera->camera->at.y += func_80163660(&player->actor);
            break;

        case CS_CAM_REL_1:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case CS_CAM_REL_4:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->at, &csCamera->camera->at, 1);
            break;

        case CS_CAM_REL_5:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->at, &csCamera->camera->at, 2);
            break;

        default: // CS_CAM_REL_0
            break;
    }

    csCamera->eyeInterp.curPoint += numPoints;

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

    interpHandler = CutsceneCamera_Interpolate(csCamera->eyeCmd[csCamera->atInterp.curPoint].interpType);

    switch (csCamera->eyeCmd[csCamera->atInterp.curPoint].relativeTo) {
        case CS_CAM_REL_2:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        case CS_CAM_REL_3:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case CS_CAM_REL_1:
            OLib_DbCameraVec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case CS_CAM_REL_4:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case CS_CAM_REL_5:
            OLib_DbCameraVec3fDiff(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        default: // CS_CAM_REL_0
            break;
    }

    numPoints = interpHandler(&csCamera->camera->eye, fov, roll, &csCamera->eyeCmd[csCamera->atInterp.curPoint],
                              &csCamera->miscCmd[csCamera->atInterp.curPoint], &csCamera->atInterp);

    switch (csCamera->eyeCmd[csCamera->atInterp.curPoint].relativeTo) {
        case CS_CAM_REL_2:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        case CS_CAM_REL_3:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            csCamera->camera->eye.y += func_80163660(&player->actor);
            break;

        case CS_CAM_REL_1:
            OLib_DbCameraVec3fSum(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case CS_CAM_REL_4:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 1);
            break;

        case CS_CAM_REL_5:
            OLib_DbCameraVec3fSum(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, 2);
            break;

        default: // CS_CAM_REL_0
            break;
    }

    csCamera->atInterp.curPoint += numPoints;

    if ((csCamera->eyeInterp.curPoint >= csCamera->eyeInterp.numEntries) ||
        (csCamera->atInterp.curPoint >= csCamera->atInterp.numEntries)) {
        return false;
    }

    return true;
}

/**
 * Processes camera cutscene commands
 */
s32 CutsceneCamera_UpdateSplines(u8* script, CutsceneCamera* csCamera) {
    CsCmdCamSpline* spline;

    switch (csCamera->state) {
        case CS_CAM_STATE_DONE:
            return 0;

        case CS_CAM_STATE_PAUSE:
            return csCamera->nextSplineTimer;

        case CS_CAM_STATE_UPDATE_SPLINE:
            if (csCamera->updateSplineTimer <= csCamera->duration) {
                csCamera->updateSplineTimer++;
                if (csCamera->updateSplineTimer <= csCamera->duration) {
                    // Process Spline
                    if (!CutsceneCamera_ProcessSpline(csCamera)) {
                        csCamera->state = CS_CAM_STATE_DONE_SPLINE;
                    }
                }
            }
            break;

        case CS_CAM_STATE_DONE_SPLINE:
            break;

        default: // CS_CAM_STATE_UPDATE_ALL
            if (csCamera->splineNeedsInit == true) {
                // Spline Header
                spline = (CsCmdCamSpline*)&script[csCamera->cmdIndex];
                csCamera->atInterp.numEntries = csCamera->eyeInterp.numEntries = spline->numEntries;
                csCamera->duration = spline->duration;
                csCamera->cmdIndex += sizeof(CsCmdCamSpline);

                // At Point
                csCamera->atCmd = (CsCmdCamPoint*)&script[csCamera->cmdIndex];
                csCamera->cmdIndex += (s16)(csCamera->eyeInterp.numEntries * sizeof(CsCmdCamPoint));

                // Misc Point
                csCamera->eyeCmd = (CsCmdCamPoint*)&script[csCamera->cmdIndex];
                csCamera->cmdIndex += (s16)(csCamera->eyeInterp.numEntries * sizeof(CsCmdCamPoint));

                // Misc
                csCamera->miscCmd = (CsCmdCamMisc*)&script[csCamera->cmdIndex];
                csCamera->cmdIndex += (s16)(csCamera->eyeInterp.numEntries * sizeof(CsCmdCamMisc));

                // Other Params
                csCamera->eyeInterp.curPoint = 0;
                csCamera->atInterp.curPoint = 0;

                csCamera->splineNeedsInit = false;
                //! FAKE: csCamera->splineIndex++;
                csCamera->splineIndex = (csCamera->splineIndex & 0xFFFF) + 1;
                csCamera->state = CS_CAM_STATE_UPDATE_ALL;
                csCamera->nextSplineTimer = csCamera->updateSplineTimer = 0;
                csCamera->eyeInterp.unk_2D = csCamera->atInterp.unk_2D = 7;
            }

            csCamera->nextSplineTimer++;

            if (csCamera->updateSplineTimer <= csCamera->duration) {
                csCamera->updateSplineTimer++;
                if (csCamera->updateSplineTimer <= csCamera->duration) {
                    // Process SubCommands
                    if (!CutsceneCamera_ProcessSpline(csCamera)) {
                        csCamera->state = CS_CAM_STATE_DONE_SPLINE;
                    }
                }
            }
            break;
    }

    if (csCamera->nextSplineTimer > csCamera->duration) {
        // Next Spline
        csCamera->splineNeedsInit = true;
        spline = (CsCmdCamSpline*)&script[csCamera->cmdIndex];
        if (spline->numEntries == -1) {
            csCamera->state = CS_CAM_STATE_DONE;
            return 0;
        }
    }

    return csCamera->nextSplineTimer;
}

// Unused
s16 func_80161BAC(void) {
    return (sCurCsCamera->state == CS_CAM_STATE_PAUSE) || (sCurCsCamera->state == CS_CAM_STATE_UPDATE_SPLINE);
}

void CutsceneCamera_SetState(s16 state) {
    if (sCurCsCamera->state == CS_CAM_STATE_UPDATE_ALL) {
        sCurCsCamera->state = state;
    }
}

void CutsceneCamera_Reset(void) {
    sCurCsCamera->state = CS_CAM_STATE_UPDATE_ALL;
}

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
