#include "global.h"

extern CutsceneCamera* sCurCsCamera;

typedef s16 (*CsCamInterpolateCallback)(Vec3f*, f32*, s16*, CsCmdCamPoint*, CsCmdCamMisc*, CutsceneCameraInterp*);

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

s16 func_80161180(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    return 0;
}

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
            OLib_Vec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, OLIB_DIFF);
            break;

        case CS_CAM_REL_3:
            OLib_Vec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, OLIB_DIFF_OFFSET);
            break;

        case CS_CAM_REL_1:
            OLib_Vec3fDiff(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, OLIB_DIFF_OFFSET);
            break;

        case CS_CAM_REL_4:
            OLib_Vec3fDiff(&target->world, &csCamera->camera->at, &csCamera->camera->at, OLIB_DIFF_OFFSET);
            break;

        case CS_CAM_REL_5:
            OLib_Vec3fDiff(&target->world, &csCamera->camera->at, &csCamera->camera->at, OLIB_DIFF);
            break;

        default: // CS_CAM_REL_0
            break;
    }

    numPoints = interpHandler(&csCamera->camera->at, fov, roll, &csCamera->atCmd[csCamera->eyeInterp.curPoint],
                              &csCamera->miscCmd[csCamera->eyeInterp.curPoint], &csCamera->eyeInterp);

    switch (csCamera->atCmd[csCamera->eyeInterp.curPoint].relativeTo) {
        case CS_CAM_REL_2:
            OLib_Vec3fAdd(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, OLIB_ADD);
            break;

        case CS_CAM_REL_3:
            OLib_Vec3fAdd(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, OLIB_ADD_OFFSET);
            csCamera->camera->at.y += func_80163660(&player->actor);
            break;

        case CS_CAM_REL_1:
            OLib_Vec3fAdd(&player->actor.world, &csCamera->camera->at, &csCamera->camera->at, OLIB_ADD_OFFSET);
            break;

        case CS_CAM_REL_4:
            OLib_Vec3fAdd(&target->world, &csCamera->camera->at, &csCamera->camera->at, OLIB_ADD_OFFSET);
            break;

        case CS_CAM_REL_5:
            OLib_Vec3fAdd(&target->world, &csCamera->camera->at, &csCamera->camera->at, OLIB_ADD);
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
            OLib_Vec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_DIFF);
            break;

        case CS_CAM_REL_3:
            OLib_Vec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_DIFF_OFFSET);
            break;

        case CS_CAM_REL_1:
            OLib_Vec3fDiff(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_DIFF_OFFSET);
            break;

        case CS_CAM_REL_4:
            OLib_Vec3fDiff(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_DIFF_OFFSET);
            break;

        case CS_CAM_REL_5:
            OLib_Vec3fDiff(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_DIFF);
            break;

        default: // CS_CAM_REL_0
            break;
    }

    numPoints = interpHandler(&csCamera->camera->eye, fov, roll, &csCamera->eyeCmd[csCamera->atInterp.curPoint],
                              &csCamera->miscCmd[csCamera->atInterp.curPoint], &csCamera->atInterp);

    switch (csCamera->eyeCmd[csCamera->atInterp.curPoint].relativeTo) {
        case CS_CAM_REL_2:
            OLib_Vec3fAdd(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_ADD);
            break;

        case CS_CAM_REL_3:
            OLib_Vec3fAdd(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_ADD_OFFSET);
            csCamera->camera->eye.y += func_80163660(&player->actor);
            break;

        case CS_CAM_REL_1:
            OLib_Vec3fAdd(&player->actor.world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_ADD_OFFSET);
            break;

        case CS_CAM_REL_4:
            OLib_Vec3fAdd(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_ADD_OFFSET);
            break;

        case CS_CAM_REL_5:
            OLib_Vec3fAdd(&target->world, &csCamera->camera->eye, &csCamera->camera->eye, OLIB_ADD);
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

s16 func_80161C20(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    f32 temp_f0;

    if (interp->unk_2D != 2) {
        interp->unk_2D = 2;
        interp->unk_26 = 0;
        interp->curFrame = 0;
        interp->duration = 1;
        if (pos != NULL) {
            interp->unk_0C.x = pos->x;
            interp->unk_0C.y = pos->y;
            interp->unk_0C.z = pos->z;
        }

        if (fov != NULL) {
            interp->unk_18 = *fov;
        }

        if (roll != NULL) {
            interp->unk_1C = *roll;
        }
    }

    interp->curFrame++;

    temp_f0 = ((f32)interp->curFrame / point->duration) * (point->weight / 100.0f);

    if (pos != NULL) {
        pos->x = interp->unk_0C.x + ((point->pos.x - interp->unk_0C.x) * temp_f0);
        pos->y = interp->unk_0C.y + ((point->pos.y - interp->unk_0C.y) * temp_f0);
        pos->z = interp->unk_0C.z + ((point->pos.z - interp->unk_0C.z) * temp_f0);
    }

    if (fov != NULL) {
        *fov = interp->unk_18 + ((misc->fov - interp->unk_18) * temp_f0);
    }

    if (roll != NULL) {
        s16 new_var;
        s16 temp;

        new_var = CAM_DEG_TO_BINANG(misc->roll);

        temp = (s16)(new_var - (s16)interp->unk_1C);

        *roll = (s16)interp->unk_1C + (s16)(temp * temp_f0);
    }

    if (interp->curFrame >= point->duration) {
        interp->unk_2D = 7;
        return 1;
    }

    return 0;
}

s16 func_80161E4C(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    f32 phi_f2;
    f32 tmp1;
    f32 tmp2;

    if (interp->unk_2D != 3) {
        interp->unk_2D = 3;
        interp->unk_26 = 0;
        interp->curFrame = 0;
        interp->duration = 1;
        if (pos != NULL) {
            interp->unk_0C.x = pos->x;
            interp->unk_0C.y = pos->y;
            interp->unk_0C.z = pos->z;
        }
        if (fov != NULL) {
            interp->unk_18 = *fov;
        }
        if (roll != NULL) {
            interp->unk_1C = *roll;
        }
    }

    tmp2 = (((point->weight + 100) * (point->duration / 2)) + (((point->weight + 100) / 2) * (point->duration & 1)));
    if (point->duration < 2) {
        phi_f2 = 1.0f;
    } else {
        tmp1 = (f32)(point->weight - 100) / (point->duration - 1);
        phi_f2 = ((interp->curFrame * tmp1) + 100.0f) / tmp2;
    }

    interp->curFrame++;

    if (pos != NULL) {
        pos->x += (point->pos.x - interp->unk_0C.x) * phi_f2;
        pos->y += (point->pos.y - interp->unk_0C.y) * phi_f2;
        pos->z += (point->pos.z - interp->unk_0C.z) * phi_f2;
    }

    if (fov != NULL) {
        *fov += (misc->fov - interp->unk_18) * phi_f2;
    }

    if (roll != NULL) {
        s16 new_var;
        s16 temp;

        new_var = CAM_DEG_TO_BINANG(misc->roll);

        temp = (s16)(new_var - (s16)interp->unk_1C);

        *roll += (s16)(temp * phi_f2);
    }

    if (interp->curFrame >= point->duration) {
        interp->unk_2D = 7;
        return 1;
    }
    return 0;
}

s16 func_801620CC(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    VecGeo sp40;
    f32 sp3C;
    f32 tmp1;
    f32 tmp2;

    if (interp->unk_2D != 6) {
        interp->unk_2D = 6;
        interp->unk_26 = 0;
        interp->curFrame = 0;
        interp->duration = 1;
        if (pos != NULL) {
            interp->unk_20 = OLib_Vec3fDist(&interp->unk_00, pos) * Math_FTanF(DEG_TO_RAD(*fov));
        }
        if (fov != NULL) {
            interp->unk_18 = *fov;
        }
        if (roll != NULL) {
            interp->unk_1C = *roll;
        }
    }

    tmp2 = (((point->weight + 100) * (point->duration / 2)) + (((point->weight + 100) / 2) * (point->duration & 1)));
    if (point->duration < 2) {
        sp3C = 1.0f;
    } else {
        tmp1 = (f32)(point->weight - 100) / (point->duration - 1);
        sp3C = ((interp->curFrame * tmp1) + 100.0f) / tmp2;
    }

    interp->curFrame++;

    if (pos != NULL) {
        OLib_Vec3fDiffToVecGeo(&sp40, &interp->unk_00, pos);
        sp40.r = interp->unk_20 / Math_FTanF(DEG_TO_RAD(*fov));
        OLib_AddVecGeoToVec3f(pos, &interp->unk_00, &sp40);
    }

    if (fov != NULL) {
        *fov += (misc->fov - interp->unk_18) * sp3C;
    }

    if (roll != NULL) {
        s16 new_var;
        s16 temp;

        new_var = CAM_DEG_TO_BINANG(misc->roll);

        temp = (s16)(new_var - (s16)interp->unk_1C);

        *roll += (s16)(temp * sp3C);
    }

    if (interp->curFrame >= point->duration) {
        interp->unk_2D = 7;
        return 1;
    }

    return 0;
}

s16 func_8016237C(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    if (interp->unk_2D != 0) {
        interp->unk_2D = 0;
        interp->unk_26 = 0;
        interp->curFrame = 0;
        interp->duration = 1;
    }

    interp->curFrame++;
    if (interp->curFrame >= point->duration) {
        interp->unk_2D = 7;
        return true;
    }
    return false;
}

s16 func_801623E4(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    s16 pad;

    if (interp->unk_2D != 1) {
        interp->unk_2D = 1;
        interp->unk_26 = 0;
        interp->curFrame = 0;
        interp->duration = 1;
        if (fov != NULL) {
            *fov = misc->fov;
        }
        if (roll != NULL) {
            *roll = CAM_DEG_TO_BINANG(misc->roll);
        }
    }

    if (pos != NULL) {
        pos->x = point->pos.x;
        pos->y = point->pos.y;
        pos->z = point->pos.z;
    }

    interp->curFrame++;

    if (interp->curFrame >= point->duration) {
        interp->unk_2D = 7;
        return true;
    }

    return false;
}

void func_801624EC(f32 u, f32* coeff) {
    f32 u1 = 1.0f - u;

    coeff[0] = u1 * u1 * 0.5f;
    coeff[1] = u * u1 + 0.5f;
    coeff[2] = u * u * 0.5f;
}

s16 func_8016253C(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    f32 new_var;
    f32 coeff[3];
    s32 sp3C[3];

    if (interp->unk_2D != 5) {
        interp->unk_2D = 5;
        interp->unk_26 = 0;
        interp->duration = point->duration;
        interp->curFrame = 0;
    }

    new_var = (f32)interp->curFrame / point[interp->unk_26 + 1].duration;

    if (interp->unk_26 < (interp->duration - 1)) {
        sp3C[0] = interp->unk_26;
    } else {
        sp3C[0] = interp->duration - 1;
    }

    if ((interp->unk_26 + 1) < (interp->duration - 1)) {
        sp3C[1] = interp->unk_26 + 1;
    } else {
        sp3C[1] = interp->duration - 1;
    }

    if ((interp->unk_26 + 2) < (interp->duration - 1)) {
        sp3C[2] = interp->unk_26 + 2;
    } else {
        sp3C[2] = interp->duration - 1;
    }

    func_801624EC(new_var, coeff);

    if (pos != NULL) {
        pos->x =
            (coeff[0] * point[sp3C[0]].pos.x) + (coeff[1] * point[sp3C[1]].pos.x) + (coeff[2] * point[sp3C[2]].pos.x);
        pos->y =
            (coeff[0] * point[sp3C[0]].pos.y) + (coeff[1] * point[sp3C[1]].pos.y) + (coeff[2] * point[sp3C[2]].pos.y);
        pos->z =
            (coeff[0] * point[sp3C[0]].pos.z) + (coeff[1] * point[sp3C[1]].pos.z) + (coeff[2] * point[sp3C[2]].pos.z);
    }

    if (fov != NULL) {
        *fov = (coeff[0] * misc[sp3C[0]].fov) + (coeff[1] * misc[sp3C[1]].fov) + (coeff[2] * misc[sp3C[2]].fov);
    }

    if (roll != NULL) {
        s16 sp34[3];
        s32 sp28[2];
        s32 temp;

        sp34[0] = CAM_DEG_TO_BINANG(misc[sp3C[0]].roll);
        sp34[1] = CAM_DEG_TO_BINANG(misc[sp3C[1]].roll);
        sp34[2] = CAM_DEG_TO_BINANG(misc[sp3C[2]].roll);

        sp28[0] = (s16)(sp34[1] - sp34[0]);
        sp28[1] = sp28[0] + (s16)(sp34[2] - sp34[1]);

        temp = ((coeff[1] * sp28[0]) + (coeff[2] * sp28[1]));
        *roll = sp34[0] + temp;
    }

    interp->curFrame++;

    if (interp->curFrame == point[interp->unk_26 + 1].duration) {
        interp->unk_26++;
        interp->curFrame = 0;
        if (interp->unk_26 >= (interp->duration - 2)) {
            interp->unk_2D = 7;
            return interp->duration;
        }
    }
    return 0;
}

/**
 * This code is very similar to the unused spline system in OoT's func_800BB0A0
 * in which that is based on the Super Mario 64 cutscene camera movement
 */
void func_801629BC(f32 u, f32* coeff) {
    coeff[0] = (1.0f - u) * (1.0f - u) * (1.0f - u) * (1.0f / 6.0f);
    coeff[1] = ((u * u * u * 0.5f) - u * u) + (2.0f / 3.0f);
    coeff[2] = (u * u * u * -0.5f) + (u * u * 0.5f) + (u * 0.5f) + (1.0f / 6.0f);
    coeff[3] = u * u * u * (1.0f / 6.0f);
}

s16 func_80162A50(Vec3f* pos, f32* fov, s16* roll, CsCmdCamPoint* point, CsCmdCamMisc* misc,
                  CutsceneCameraInterp* interp) {
    f32 new_var;
    f32 coeff[4];
    s32 sp44[4];

    if (interp->unk_2D != 4) {
        interp->unk_2D = 4;
        interp->unk_26 = 0;
        interp->duration = point->duration;
        interp->curFrame = 0;
    }

    new_var = (f32)interp->curFrame / point[interp->unk_26 + 1].duration;

    if (interp->unk_26 < (interp->duration - 1)) {
        sp44[0] = interp->unk_26;
    } else {
        sp44[0] = interp->duration - 1;
    }

    if ((interp->unk_26 + 1) < (interp->duration - 1)) {
        sp44[1] = interp->unk_26 + 1;
    } else {
        sp44[1] = interp->duration - 1;
    }

    if ((interp->unk_26 + 2) < (interp->duration - 1)) {
        sp44[2] = interp->unk_26 + 2;
    } else {
        sp44[2] = interp->duration - 1;
    }

    if ((interp->unk_26 + 3) < (interp->duration - 1)) {
        sp44[3] = interp->unk_26 + 3;
    } else {
        sp44[3] = interp->duration - 1;
    }

    func_801629BC(new_var, coeff);

    if (pos != NULL) {
        pos->x = (coeff[0] * point[sp44[0]].pos.x) + (coeff[1] * point[sp44[1]].pos.x) +
                 (coeff[2] * point[sp44[2]].pos.x) + (coeff[3] * point[sp44[3]].pos.x);
        pos->y = (coeff[0] * point[sp44[0]].pos.y) + (coeff[1] * point[sp44[1]].pos.y) +
                 (coeff[2] * point[sp44[2]].pos.y) + (coeff[3] * point[sp44[3]].pos.y);
        pos->z = (coeff[0] * point[sp44[0]].pos.z) + (coeff[1] * point[sp44[1]].pos.z) +
                 (coeff[2] * point[sp44[2]].pos.z) + (coeff[3] * point[sp44[3]].pos.z);
    }

    if (fov != NULL) {
        *fov = (coeff[0] * misc[sp44[0]].fov) + (coeff[1] * misc[sp44[1]].fov) + (coeff[2] * misc[sp44[2]].fov) +
               (coeff[3] * misc[sp44[3]].fov);
    }

    if (roll != NULL) {
        s16 sp3C[4];
        s32 sp2C[3];
        s32 temp;

        sp3C[0] = CAM_DEG_TO_BINANG(misc[sp44[0]].roll);
        sp3C[1] = CAM_DEG_TO_BINANG(misc[sp44[1]].roll);
        sp3C[2] = CAM_DEG_TO_BINANG(misc[sp44[2]].roll);
        sp3C[3] = CAM_DEG_TO_BINANG(misc[sp44[3]].roll);

        sp2C[0] = (s16)(sp3C[1] - sp3C[0]);
        sp2C[1] = sp2C[0] + (s16)(sp3C[2] - sp3C[1]);
        sp2C[2] = sp2C[1] + (s16)(sp3C[3] - sp3C[2]);

        temp = ((coeff[1] * sp2C[0]) + (coeff[2] * sp2C[1]) + (coeff[3] * sp2C[2]));
        *roll = sp3C[0] + temp;
    }

    interp->curFrame++;

    if (interp->curFrame == point[interp->unk_26 + 1].duration) {
        interp->curFrame = 0;
        interp->unk_26++;
        if (interp->unk_26 >= (interp->duration - 3)) {
            interp->unk_2D = 7;
            return interp->duration;
        }
    }
    return 0;
}

extern f32 sKnots[];

// Only used by unused func_80163334
void func_80162FF8(s16 arg0) {
    f32 var_fv0 = 0.0f;
    s32 i;

    sKnots[0] = 0.0f;
    sKnots[1] = 0.0f;
    sKnots[2] = 0.0f;

    for (i = 3; i < arg0; i++) {
        if (i == 3) {
            var_fv0 += 0.9f;
        } else if ((i == 4) || (i == (arg0 - 1))) {
            var_fv0 += 0.6f;
        } else {
            var_fv0 += 0.3f;
        }

        sKnots[i] = var_fv0;
    }

    var_fv0 += 0.9f;
    sKnots[i++] = var_fv0;
    sKnots[i++] = var_fv0;
    sKnots[i++] = var_fv0;
}

// Only used by unused func_80163334
void func_801631DC(f32 progress, s32 arg2, f32* coeff) {
    f32 coeffTemp[4][4];
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 3 + 1; i++) {
        for (j = 0; j < 3 + 1; j++) {
            coeffTemp[i][j] = 0.0f;
        }
    }

    coeffTemp[0][3 - 1] = 1.0f;

    for (i = 1; i < 3; i++) {
        for (j = arg2 - i, k = (3 - 1) - i; j <= arg2; j++, k++) {
            if (sKnots[j + i] != sKnots[j]) {
                coeffTemp[i][k] = ((progress - sKnots[j]) / (sKnots[j + i] - sKnots[j])) * coeffTemp[i - 1][k];
            } else {
                coeffTemp[i][k] = 0.0f;
            }

            if (sKnots[j + i + 1] != sKnots[j + 1]) {
                coeffTemp[i][k] +=
                    ((sKnots[j + i + 1] - progress) / (sKnots[j + i + 1] - sKnots[j + 1])) * coeffTemp[i - 1][k + 1];
            }
        }
    }
    for (j = 0; j < 3; j++) {
        coeff[j] = coeffTemp[3 - 1][j];
    }
}

// Unused
#pragma GLOBAL_ASM("asm/non_matchings/code/cutscene_camera/func_80163334.s")

f32 func_80163660(Actor* actor) {
    if (actor->category != ACTORCAT_PLAYER) {
        return 38.0f - (actor->focus.pos.y - actor->world.pos.y);
    }

    switch (((Player*)actor)->transformation) {
        case PLAYER_FORM_DEKU:
            return -8.0f;

        case PLAYER_FORM_GORON:
            return 23.0f;

        case PLAYER_FORM_ZORA:
            return 27.0f;

        case PLAYER_FORM_FIERCE_DEITY:
            return 17.0f;

        default:
            return 0.0f;
    }
}
