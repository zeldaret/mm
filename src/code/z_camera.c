#include "global.h"

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_fabsf.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_LengthVec3f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB270.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Lerpf.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Lerps.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB42C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_LerpVec3f.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB544.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB584.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB60C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB674.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB6C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB700.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB780.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB7CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB7F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB828.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB854.s")

s32 Camera_IsSwimming(Camera* camera) {
    Actor* focalActor = camera->focalActor;

    if (focalActor == &GET_PLAYER(camera->play)->actor) {
        if (((Player*)focalActor)->stateFlags3 & PLAYER_STATE3_8000) {
            // Swimming as Zora
            return 999;
        } else {
            // Swimming as Human or Fierce Deity
            return ((Player*)focalActor)->stateFlags1 & PLAYER_STATE1_8000000;
        }
    } else {
        // Camera not focused on player
        return 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB8C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB924.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CB950.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBA08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBA34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBA7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBAD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBB88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CBFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC000.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC128.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC1C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC260.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC488.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC56C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC5C8.s")

#define CAM_DATA_IS_BG (1 << 12) // if not set, then cam data is for actor cutscenes

/**
 * Returns the CameraSettingType of the camera from either the bgCam or the actorCsCam at index `camDataId`
 */
s16 Camera_GetBgCamOrActorCsCamSetting(Camera* camera, u32 camDataId) {
    if (camDataId & CAM_DATA_IS_BG) {
        return BgCheck_GetBgCamSettingImpl(&camera->play->colCtx, camDataId & ~CAM_DATA_IS_BG, BGCHECK_SCENE);
    } else {
        return Play_GetActorCsCamSetting(camera->play, camDataId);
    }
}

/**
 * Returns either the bgCam data or the actorCsCam data at index `camDataId`
 */
Vec3s* Camera_GetBgCamOrActorCsCamFuncData(Camera* camera, u32 camDataId) {
    if (camDataId & CAM_DATA_IS_BG) {
        return BgCheck_GetBgCamFuncDataImpl(&camera->play->colCtx, camDataId & ~CAM_DATA_IS_BG, BGCHECK_SCENE);
    } else {
        return Play_GetActorCsCamFuncData(camera->play, camDataId);
    }
}

/**
 * Gets the bgCam index for the poly `poly`, returns -1 if
 * there is no camera data for that poly.
 */
s32 Camera_GetBgCamIndex(Camera* camera, s32* bgId, CollisionPoly* poly) {
    s32 bgCamIndex = SurfaceType_GetBgCamIndex(&camera->play->colCtx, poly, *bgId);
    s32 ret;

    if (BgCheck_GetBgCamSettingImpl(&camera->play->colCtx, bgCamIndex, *bgId) == CAM_SET_NONE) {
        ret = -1;
    } else {
        ret = bgCamIndex;
    }

    return ret;
}

/**
 * Gets the Camera setting for the water box the player is in.
 * Returns -1 if the player is not in a water box, or does not have a swimming state.
 * Returns -2 if there is no bgCam index for the water box.
 * Returns the camera setting otherwise.
 */
s32 Camera_GetWaterBoxBgCamSetting(Camera* camera, f32* waterY) {
    PosRot playerPosShape;
    WaterBox* waterBox;
    s32 camSetting;
    s32 bgId;

    Actor_GetWorldPosShapeRot(&playerPosShape, camera->focalActor);
    *waterY = playerPosShape.pos.y;

    if (!WaterBox_GetSurfaceImpl(camera->play, &camera->play->colCtx, playerPosShape.pos.x, playerPosShape.pos.z,
                                 waterY, &waterBox, &bgId)) {
        // player's position is not in a waterbox
        *waterY = playerPosShape.pos.y;
        return -1;
    }

    if (!Camera_IsSwimming(camera)) {
        return -1;
    }

    camSetting = WaterBox_GetBgCamSetting(&camera->play->colCtx, waterBox, bgId);

    // -2: no bgCam index
    return (camSetting == CAM_SET_NONE) ? -2 : camSetting;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC938.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC958.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CC9C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CCCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD04C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD288.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD2F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD3E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD44C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD634.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CD834.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CDA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CDB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CDE6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE79C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CE930.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CEAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CEC38.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800CED90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeNop.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeNORM1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeNORM2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeNORM3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeNORM4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeNORM0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModePARA1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModePARA2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModePARA3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModePARA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModePARA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeJUMP1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeJUMP2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeJUMP3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeJUMP4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeJUMP0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeBATT1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeBATT2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeBATT3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeBATT4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeBATT0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeKEEP1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeKEEP2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeKEEP3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeKEEP4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeKEEP0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeFIXD1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeFIXD2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeFIXD3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeFIXD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeFIXD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSUBJ1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSUBJ2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSUBJ3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSUBJ4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSUBJ0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDATA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDATA1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDATA2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDATA3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDATA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ5.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ6.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ7.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeUNIQ9.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO5.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO6.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO7.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO9.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeDEMO0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC1.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC3.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC5.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC6.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC7.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ModeSPEC9.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Alloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Free.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DDFE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE0EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE308.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE324.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE840.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE890.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DE954.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DF498.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeMode.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DF86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DF8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeSetting.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeDataIdx.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFC1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetInputDirYaw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetCamDir.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetCamDirPitch.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetCamDirYaw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_AddQuake.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFD78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800DFF44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetFlags.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ClearFlags.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_ChangeDoorCam.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E007C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E01AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetQuakeOffset.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E01DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E0228.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E0238.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetToTrackActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_SetTargetActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/Camera_GetWaterYPos.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_camera/func_800E0348.s")
