#include <ultra64.h>
#include <global.h>

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_GetDamageAndEffectOnBumper.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E04BC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_GetToucherDamage.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitCommonDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniCommon.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0594.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E05D4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitCommonWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetCommonForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetCommonForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetCommonForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTouchDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniTouch.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTouchWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_nop800E0720.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitBumpDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniBump.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitBumpWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitBodyDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniBody.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitBodyWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetBodyForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetBodyForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetBodyForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereParamsDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniSphereParams.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereParamsWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereGroupElemDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniSphereGroupElem.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereGroupElemWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereGroupElemForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereGroupElemForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereGroupElemForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereGroupDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0B78.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniSphereGroup.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0CA8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0D84.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereGroupWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereGroup.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereGroupForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereGroupForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereGroupForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitCylinderParamsDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniCylinderParams.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitCylinderParamsWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitCylinderDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniCylinder.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E123C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E12A4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitCylinderWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitCylinder.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetCylinderForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetCylinderForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ReseCylinderForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriParamsDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniTriParams.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriParamsWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniTri.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetTriForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetTriForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E16AC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriGroupDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E16FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniTriGroup.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E1858.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriGroupWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriGroup.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetTriGroupForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetTriGroupForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetTriGroupForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitQuadParamsDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniQuadParams.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetQuadParamsForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_QuadCalcMidpoints.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitQuadParamsWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitQuadDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniQuad.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E1EB8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitQuadWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitQuad.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetQuadForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetQuadForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetQuadForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E20A4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereDefault.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_FiniSphere.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphereWithData.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitSphere.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereForAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereForAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ResetSphereForOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2368.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E23B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E23C4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2408.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2434.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_Fini.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_Reset.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_EnableEditMode.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_EnableAppendMode.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_AddAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_AddIndexAT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_AddAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/collision_AddIndexAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_AddOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_AddIndexOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_AddGroup4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CantBeToucherAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CantBeBumperAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_ToucherIsExcluded.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2C08.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2C1C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2D88.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2EF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2F30.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2F54.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2F78.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E30C8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E3168.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E3304.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_HandleCollisionATWithAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriCalcAvgPoint.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/collision_quad_cal_avg_point.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithSphereGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithCylinderAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithTriGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithQuadAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithSphereAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithSphereGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithCylinderAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithTriGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithQuadAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithSphereAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriGroupWithSphereGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriGroupWithCylinderAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriGroupWithTriGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriGroupWithQuad.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriGroupWithSphereAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_QuadWithSphereGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_QuadWithCylinderAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_QuadWithTriGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_QuadWithQuadAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_QuadWithSphereAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithSphereGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithCylinderAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithTriGroupAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithQuadAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithSphereAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E60C0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E61A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6238.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6320.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E63B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6450.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CollideWithAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_DoATWithAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6724.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_HandleCollisionOTWithOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithSphereGroupOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithCylinderOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithSphereOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithSphereGroupOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithCylinderOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithSphereOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithSphereGroupOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithCylinderOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithSphereOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7264.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7288.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_DoOTWithOT.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7494.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E74DC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7508.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7530.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E755C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7590.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E75C8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E77EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7894.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E78B4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7948.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7968.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7988.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7A48.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7B54.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7BCC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7C64.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7DA8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7DCC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderMoveToActor.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderSetLoc.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_QuadSetCoords.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriGroupSetCoordsAtIndex.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_InitTriParamsAtIndex.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7FDC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8160.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E823C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8318.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8478.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E85D4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8668.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8690.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E86C0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E86E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8784.asm")
