#!/usr/bin/env python3

import os
import argparse

# all occurrences of keys will be replaced by associated value
simpleReplace = {
    # "Math_Rand_":"Rand_",
    # "ACTORTYPE":"ACTORCAT",
    # "DistToLink":"DistToPlayer",
    # "HitItem":"HitInfo",
}

# all occurrences of keys will be replaced by associated value,
# if the occurence is the whole word
# for example, if there is a space before and an open parenthesis after,
# like for a function call: ` func_8002E4B4(`
# 
# Custom behaviour can be enabled by using a tuple as the value (see 
# explanation in replace_single below)
wordReplace = {
    # Functions
    "Actor_GetSwitchFlag": "Flags_GetSwitch",
    "atan_flip": "Math_Acot2F",
    "atans": "Math_Atan2S",

    # "SysMatrix_StateAlloc":                         "Matrix_StateAlloc",
    # "SysMatrix_StatePush":                          "Matrix_StatePush",
    # "SysMatrix_StatePop":                           "Matrix_StatePop",
    # "SysMatrix_GetCurrentState":                    "Matrix_GetCurrentState",
    # "SysMatrix_CopyCurrentState":                   "Matrix_CopyCurrentState",
    # "SysMatrix_SetCurrentState":                    "Matrix_SetCurrentState",
    # "SysMatrix_InsertTranslation":                  "Matrix_InsertTranslation",
    # "SysMatrix_InsertMatrix":                       "Matrix_InsertMatrix",
    # "SysMatrix_Scale":                              "Matrix_Scale",
    # "SysMatrix_InsertXRotation_s":                  "Matrix_InsertXRotation_s",
    # "SysMatrix_InsertXRotation_f":                  "Matrix_InsertXRotation_f",
    # "SysMatrix_RotateStateAroundXAxis":             "Matrix_RotateStateAroundXAxis",
    # "SysMatrix_SetStateXRotation":                  "Matrix_SetStateXRotation",
    # "SysMatrix_RotateY":                            "Matrix_RotateY",
    # "SysMatrix_InsertYRotation_f":                  "Matrix_InsertYRotation_f",
    # "SysMatrix_InsertZRotation_s":                  "Matrix_InsertZRotation_s",
    # "SysMatrix_InsertZRotation_f":                  "Matrix_InsertZRotation_f",
    # "SysMatrix_InsertRotation":                     "Matrix_InsertRotation",
    # "SysMatrix_JointPosition":                      "Matrix_JointPosition",
    # "SysMatrix_SetStateRotationAndTranslation":     "Matrix_SetStateRotationAndTranslation",
    # "SysMatrix_ToRSPMatrix":                        "Matrix_ToRSPMatrix",
    # "SysMatrix_ToMtx":                              "Matrix_ToMtx",
    # "SysMatrix_NewMtx":                             "Matrix_NewMtx",
    # "SysMatrix_AppendToPolyOpaDisp":                "Matrix_AppendToPolyOpaDisp",
    # "SysMatrix_MultiplyVector3fByState":            "Matrix_MultiplyVector3fByState",
    # "SysMatrix_GetStateTranslation":                "Matrix_GetStateTranslation",
    # "SysMatrix_GetStateTranslationAndScaledX":      "Matrix_GetStateTranslationAndScaledX",
    # "SysMatrix_GetStateTranslationAndScaledY":      "Matrix_GetStateTranslationAndScaledY",
    # "SysMatrix_GetStateTranslationAndScaledZ":      "Matrix_GetStateTranslationAndScaledZ",
    # "SysMatrix_MultiplyVector3fXZByCurrentState":   "Matrix_MultiplyVector3fXZByCurrentState",
    # "SysMatrix_MtxFCopy":                           "Matrix_MtxFCopy",
    # "SysMatrix_FromRSPMatrix":                      "Matrix_FromRSPMatrix",
    # "SysMatrix_MultiplyVector3fByMatrix":           "Matrix_MultiplyVector3fByMatrix",
    # "SysMatrix_TransposeXYZ":                       "Matrix_TransposeXYZ",
    # "SysMatrix_NormalizeXYZ":                       "Matrix_NormalizeXYZ",
    # "SysMatrix_InsertRotationAroundUnitVector_f":   "Matrix_InsertRotationAroundUnitVector_f",
    # "SysMatrix_InsertRotationAroundUnitVector_s":   "Matrix_InsertRotationAroundUnitVector_s",
    # "SysMatrix_GetStateAsRSPMatrix":                "Matrix_GetStateAsRSPMatrix",

    "Matrix_StateAlloc":                       "Matrix_Init",
    "Matrix_StatePush":                        "Matrix_Push",
    "Matrix_StatePop":                         "Matrix_Pop",
    "Matrix_CopyCurrentState":                 "Matrix_Get",
    "Matrix_SetCurrentState":                  "Matrix_Put",
    "Matrix_GetCurrentState":                  "Matrix_GetCurrent",
    "Matrix_InsertMatrix":                     "Matrix_Mult",
    "Matrix_InsertTranslation":                "Matrix_Translate",
    "Matrix_InsertXRotation_s":                "Matrix_RotateXS",
    "Matrix_InsertXRotation_f":                "Matrix_RotateXF",
    "Matrix_RotateStateAroundXAxis":           "Matrix_RotateXFApply",
    "Matrix_SetStateXRotation":                "Matrix_RotateXFNew",
    # "Matrix_RotateY":                          "Matrix_RotateYS",
    "Matrix_InsertYRotation_f":                "Matrix_RotateYF",
    "Matrix_InsertZRotation_s":                "Matrix_RotateZS",
    "Matrix_InsertZRotation_f":                "Matrix_RotateZF",
    "Matrix_InsertRotation":                   "Matrix_RotateZYX",
    "Matrix_JointPosition":                    "Matrix_TranslateRotateZYX",
    "Matrix_SetStateRotationAndTranslation":   "Matrix_SetTranslateRotateYXZ",
    "Matrix_ToRSPMatrix":                      "Matrix_MtxFToMtx",
    "Matrix_MultiplyVector3fByState":          "Matrix_MultVec3f",
    "Matrix_GetStateTranslation":              "Matrix_MultZero",
    "Matrix_GetStateTranslationAndScaledX":    "Matrix_MultVecX",
    "Matrix_GetStateTranslationAndScaledY":    "Matrix_MultVecY",
    "Matrix_GetStateTranslationAndScaledZ":    "Matrix_MultVecZ",
    "Matrix_MultiplyVector3fXZByCurrentState": "Matrix_MultVec3fXZ",
    "Matrix_FromRSPMatrix":                    "Matrix_MtxToMtxF",
    "Matrix_TransposeXYZ":                     "Matrix_Transpose",
    "Matrix_NormalizeXYZ":                     "Matrix_ReplaceRotation",
    "func_8018219C":                           "Matrix_MtxFToYXZRot",
    "func_801822C4":                           "Matrix_MtxFToZYXRot",
    "Matrix_InsertRotationAroundUnitVector_f": "Matrix_RotateAxisF",
    "Matrix_InsertRotationAroundUnitVector_s": "Matrix_RotateAxisS",

    "func_800B78B8": "Actor_UpdateBgCheckInfo",
    "func_8012403C": "Player_GetMask",
    "func_8012404c": "Player_RemoveMask",
    "func_80123AA4": "Player_SetModels",
    "func_80123BD4": "Player_SetModelGroup",
    "func_80123F48": "Player_IsBurningStickInRange",
    "func_8012405C": "Player_HasMirrorShieldEquipped",
    "func_80124088": "Player_IsHoldingMirrorShield",
    "func_8012697C": "Player_DrawGetItem",
    "Actor_SpawnWithParentAndCutscene": "Actor_SpawnAsChildAndCutscene",
    "Actor_SpawnWithParent": "Actor_SpawnAsChild",
    "Actor_IsLinkFacingActor": "Player_IsFacingActor",
    "Actor_IsActorFacingLink": "Actor_IsFacingPlayer",
    "Actor_IsActorFacingLinkAndWithinRange": "Actor_IsFacingAndNearPlayer",
    "Actor_IsActorFacingActorAndWithinRange": "Actor_ActorAIsFacingAndNearActorB",
    "Actor_IsActorFacingActor": "Actor_ActorAIsFacingActorB",
    "Actor_IsActorFacedByActor": "Actor_ActorBIsFacingActorA",
    "func_800B84D0": "Actor_ProcessTalkRequest",
    "func_8017D668": "Math3D_PointDistToLine2D",
    "func_800BDFC0": "Gfx_DrawDListOpa",
    "func_800BE03C": "Gfx_DrawDListXlu",
    "func_800B6FC8": "Player_GetHeight",
    "Actor_InitCurrPosition": "Actor_SetWorldToHome",
    "Actor_SetHeight": "Actor_SetFocus",
    "Actor_SetRotationFromDrawRotation": "Actor_SetWorldRotToShape",
    "Actor_InitDrawRotation": "Actor_SetShapeRotToWorld",
    "Actor_CalcOffsetOrientedToDrawRotation": "Actor_OffsetOfPointInActorCoords",
    "Actor_ApplyMovement": "Actor_UpdatePos",
    "Actor_SetVelocityYRotationAndGravity": "Actor_UpdateVelocityWithGravity",
    "Actor_SetVelocityAndMoveYRotationAndGravity": "Actor_MoveWithGravity",
    "Actor_SetVelocityXYRotation": "Actor_UpdateVelocityWithoutGravity",
    "Actor_SetVelocityAndMoveXYRotation": "Actor_MoveWithoutGravity",
    "Actor_SetVelocityXYRotationReverse": "Actor_UpdateVelocityWithoutGravityReverse",
    "Actor_SetVelocityAndMoveXYRotationReverse": "Actor_MoveWithoutGravityReverse",
    "func_800B6C04": "Actor_SetSpeeds",
    "func_800B81E0": "Actor_GetFocus",
    "func_800B8214": "Actor_GetWorld",
    "func_800B8248": "Actor_GetWorldPosShapeRot",
    "func_800BE22C": "Actor_ApplyDamage",
    "Audio_PlaySoundAtPosition": "SoundSource_PlaySfxAtFixedWorldPos",
    "func_800F0590": "SoundSource_PlaySfxEachFrameAtFixedWorldPos",
    "func_8016970C": "Play_CameraSetAtEye",
    "func_800BBA88": "Enemy_StartFinishingBlow",
    "ShrinkWindow_Step": "ShrinkWindow_Update",
    "ShrinkWindow_Fini": "ShrinkWindow_Destroy",
    "func_801A89A8": "Audio_QueueSeqCmd",
    "func_8019F1C0": "Audio_PlaySfxAtPos",
    "func_801A72CC": "Audio_StopSfxByPos",
    "SkelAnime_LodDrawLimb": "SkelAnime_DrawLimbLod",
    "SkelAnime_LodDraw": "SkelAnime_DrawLod",
    "SkelAnime_LodDrawLimbSV": "SkelAnime_DrawFlexLimbLod",
    "SkelAnime_LodDrawSV": "SkelAnime_DrawFlexLod",
    # "SkelAnime_DrawLimb": "SkelAnime_DrawLimbOpa", # A different function is called this now
    # "SkelAnime_Draw": "SkelAnime_DrawOpa", # A different function is called this now
    "SkelAnime_DrawLimbSV": "SkelAnime_DrawFlexLimbOpa",
    "SkelAnime_DrawSV": "SkelAnime_DrawFlexOpa",
    # "SkelAnime_AnimateFrame": "SkelAnime_GetFrameData", # A different function is called this now
    "SkelAnime_GetTotalFrames": "Animation_GetLength",
    "SkelAnime_GetFrameCount": "Animation_GetLastFrame",
    "SkelAnime_Draw2Limb": "SkelAnime_DrawLimb",
    "SkelAnime_Draw2": "SkelAnime_Draw",
    "SkelAnime_DrawLimbSV2": "SkelAnime_DrawFlexLimb",
    "SkelAnime_DrawSV2": "SkelAnime_DrawFlex",
    "func_80134FFC": "SkelAnime_GetFrameData2",
    "func_801353D4": "Animation_GetLimbCount2",
    "SkelAnime_GetTotalFrames2": "Animation_GetLength2",
    "SkelAnime_GetFrameCount2": "Animation_GetLastFrame2",
    "SkelAnime_InterpolateVec3s": "SkelAnime_InterpFrameTable",
    "SkelAnime_AnimationCtxReset": "AnimationContext_Reset",
    "func_801358D4": "AnimationContext_SetNextQueue",
    "func_801358F4": "AnimationContext_DisableQueue",
    "SkelAnime_NextEntry": "AnimationContext_AddEntry",
    "SkelAnime_LoadLinkAnimetion": "AnimationContext_SetLoadFrame",
    "SkelAnime_LoadAnimationType1": "AnimationContext_SetCopyAll",
    "SkelAnime_LoadAnimationType2": "AnimationContext_SetInterp",
    "SkelAnime_LoadAnimationType3": "AnimationContext_SetCopyTrue",
    "SkelAnime_LoadAnimationType4": "AnimationContext_SetCopyFalse",
    "SkelAnime_LoadAnimationType5": "AnimationContext_SetMoveActor",
    "SkelAnime_LinkAnimetionLoaded": "AnimationContext_LoadFrame",
    "SkelAnime_AnimationType1Loaded": "AnimationContext_CopyAll",
    "SkelAnime_AnimationType2Loaded": "AnimationContext_CopyInterp",
    "SkelAnime_AnimationType3Loaded": "AnimationContext_CopyTrue",
    "SkelAnime_AnimationType4Loaded": "AnimationContext_CopyFalse",
    "SkelAnime_AnimationType5Loaded": "AnimationContext_MoveActor",
    "func_80135EE8": "AnimationContext_Update",
    "SkelAnime_InitLinkAnimetion": "SkelAnime_InitLink",
    "func_801360A8": "LinkAnimation_SetUpdateFunction",
    "func_801360E0": "LinkAnimation_Update",
    "func_80136104": "LinkAnimation_Morph",
    "func_801361BC": "LinkAnimation_AnimateFrame",
    "func_80136288": "LinkAnimation_Loop",
    "func_8013631C": "LinkAnimation_Once",
    "SkelAnime_SetTransition": "Animation_SetMorph",
    "SkelAnime_ChangeLinkAnim": "LinkAnimation_Change",
    "SkelAnime_ChangeLinkAnimDefaultStop": "LinkAnimation_PlayOnce",
    "SkelAnime_ChangeLinkAnimPlaybackStop": "LinkAnimation_PlayOnceSetSpeed",
    "SkelAnime_ChangeLinkAnimDefaultRepeat": "LinkAnimation_PlayLoop",
    "SkelAnime_ChangeLinkAnimPlaybackRepeat": "LinkAnimation_PlayLoopSetSpeed",
    "func_8013670C": "LinkAnimation_CopyJointToMorph",
    "func_8013673C": "LinkAnimation_CopyMorphToJoint",
    "func_8013676C": "LinkAnimation_LoadToMorph",
    "func_801367B0": "LinkAnimation_LoadToJoint",
    "func_801367F4": "LinkAnimation_InterpJointMorph",
    "func_8013682C": "LinkAnimation_BlendToJoint",
    "func_801368CC": "LinkAnimation_BlendToMorph",
    "SkelAnime_SetModeStop": "LinkAnimation_EndLoop",
    "func_80136990": "Animation_OnFrameImpl",
    "func_80136A48": "LinkAnimation_OnFrame",
    "SkelAnime_InitSV": "SkelAnime_InitFlex",
    "func_80136C84": "SkelAnime_SetUpdate",
    "SkelAnime_FrameUpdateMatrix": "SkelAnime_Update",
    "func_80136CF4": "SkelAnime_Morph",
    "func_80136D98": "SkelAnime_MorphTaper",
    "func_80136F04": "SkelAnime_AnimateFrame",
    "func_8013702C": "SkelAnime_LoopFull",
    "func_801370B0": "SkelAnime_LoopPartial",
    "func_8013713C": "SkelAnime_Once",
    "SkelAnime_ChangeAnimImpl": "Animation_ChangeImpl",
    "SkelAnime_ChangeAnim": "Animation_Change",
    "SkelAnime_ChangeAnimDefaultStop": "Animation_PlayOnce",
    "SkelAnime_ChangeAnimTransitionStop": "Animation_MorphToPlayOnce",
    "SkelAnime_ChangeAnimPlaybackStop": "Animation_PlayOnceSetSpeed",
    "SkelAnime_ChangeAnimDefaultRepeat": "Animation_PlayLoop",
    "SkelAnime_ChangeAnimTransitionRepeat": "Animation_MorphToLoop",
    "SkelAnime_ChangeAnimPlaybackRepeat": "Animation_PlayLoopSetSpeed",
    "SkelAnime_AnimSetStop": "Animation_EndLoop",
    "SkelAnime_AnimReverse": "Animation_Reverse",
    "func_80137674": "SkelAnime_CopyFrameTableTrue",
    "func_801376DC": "SkelAnime_CopyFrameTableFalse",
    "func_80137748": "SkelAnime_UpdateTranslation",
    "func_801378B8": "Animation_OnFrame",
    "SkelAnime_CopyVec3s": "SkelAnime_CopyFrameTable",
    "Actor_SetObjectSegment": "Actor_SetObjectDependency",
    "func_800B3FC0": "ActorShadow_DrawCircle",
    "func_800B4024": "ActorShadow_DrawSquare",
    "func_800B4088": "ActorShadow_DrawWhiteCircle",
    "func_800B40B8": "ActorShadow_DrawHorse",
    "func_800B40E0": "ActorShadow_DrawFoot",
    "func_800B42F8": "ActorShadow_DrawFeet",
    "func_800B4A98": "Actor_SetFeetPos",
    "Actor_SetSwitchFlag": "Flags_SetSwitch",
    "Actor_UnsetSwitchFlag": "Flags_UnsetSwitch",
    "Actor_GetChestFlag": "Flags_GetTreasure",
    "Actor_SetChestFlag": "Flags_SetTreasure",
    "Actor_SetAllChestFlag": "Flags_SetAllTreasure",
    "Actor_GetAllChestFlag": "Flags_GetAllTreasure",
    "Actor_GetRoomCleared": "Flags_GetClear",
    "Actor_SetRoomCleared": "Flags_SetClear",
    "Actor_UnsetRoomCleared": "Flags_UnsetClear",
    "Actor_GetRoomClearedTemp": "Flags_GetClearTemp",
    "Actor_SetRoomClearedTemp": "Flags_SetClearTemp",
    "Actor_UnsetRoomClearedTemp": "Flags_UnsetTempClear",
    "Actor_GetCollectibleFlag": "Flags_GetCollectible",
    "Actor_SetCollectibleFlag": "Flags_SetCollectible",
    "func_800B8A1C": "Actor_PickUp",
    "func_800B8B84": "Actor_PickUpNearby",
    "func_800B8BB0": "Actor_LiftActor",
    "func_800B8BD0": "Actor_PickUpFar",
    "func_801A5CFC": "Audio_PlaySfxGeneral",
    "func_800BBDAC": "Actor_SpawnFloorDustRing",
    "func_800B8708": "Player_GetExchangeItemId",
    "func_801233E4": "Player_InCsMode",
    "func_800BC4EC": "Actor_TestFloorInDirection",
    "func_800BC5B8": "Actor_IsTargeted",
    "func_800BC5EC": "Actor_OtherIsTargeted",
    "func_800BCB70": "Actor_SetColorFilter",
    "func_800BE0B8": "Actor_FindNearby",
    "func_800BE258": "Actor_SetDropFlag",
    "func_800BE2B8": "Actor_SetDropFlagJntSph",
    "Actor_TitleCardCreate": "TitleCard_InitBossName",
    "func_800B867C": "Actor_TextboxIsClosing",
    "func_800BDC5C": "Actor_ChangeAnimationByInfo",
    "Actor_ChangeAnimation": "Actor_ChangeAnimationByInfo",
    "func_80152498": "Message_GetState",
    "func_800B8898": "Actor_GetScreenPos",
    "Audio_PlayActorSound2": "Actor_PlaySfxAtPos",
    "func_800BF7CC": "Actor_SpawnIceEffects",
    "Actor_IsFacingPlayerAndWithinRange": "Actor_IsFacingAndNearPlayer",
    "func_800BC8B8": "Actor_DrawDoorLock",
    "func_800B86C8": "Actor_ChangeFocus",
    "zelda_malloc": "ZeldaArena_Malloc",
    "zelda_mallocR": "ZeldaArena_MallocR",
    "zelda_realloc": "ZeldaArena_Realloc",
    "zelda_free": "ZeldaArena_Free",
    "zelda_calloc": "ZeldaArena_Calloc",
    "MainHeap_AnalyzeArena": "ZeldaArena_GetSizes",
    "MainHeap_Check": "ZeldaArena_Check",
    "MainHeap_Init": "ZeldaArena_Init",
    "MainHeap_Cleanup": "ZeldaArena_Cleanup",
    "MainHeap_IsInitialized": "ZeldaArena_IsInitialized",
    "func_80138300": "Skin_GetLimbPos",
    "func_8013835C": "Skin_GetVertexPos",
    "BgCheck_RelocateMeshHeader": "CollisionHeader_GetVirtual",
    "BgCheck_AddActorMesh": "DynaPoly_SetBgActor",
    "BgCheck_RemoveActorMesh": "DynaPoly_DeleteBgActor",
    "BgCheck_PolygonLinkedListNodeInit": "SSNode_SetValue",
    "BgCheck_PolygonLinkedListResetHead": "SSList_SetNull",
    "BgCheck_ScenePolygonListsNodeInsert": "SSNodeList_SetSSListHead",
    "BgCheck_PolygonLinkedListNodeInsert": "DynaSSNodeList_SetSSListHead",
    "BgCheck_PolygonLinkedListInit": "DynaSSNodeList_Init",
    "BgCheck_PolygonLinkedListAlloc": "DynaSSNodeList_Alloc",
    "BgCheck_PolygonLinkedListReset": "DynaSSNodeList_ResetCount",
    "BgCheck_AllocPolygonLinkedListNode": "DynaSSNodeList_GetNextNodeIdx",
    "BgCheck_CreateVec3fFromVertex": "BgCheck_Vec3sToVec3f",
    "BgCheck_CreateVertexFromVec3f": "BgCheck_Vec3fToVec3s",
    "BgCheck_PolygonGetMinY": "CollisionPoly_GetMinY",
    "BgCheck_PolygonGetNormal": "CollisionPoly_GetNormalF",
    "BcCheck3_BgActorInit": "DynaPolyActor_Init",
    "BgCheck3_LoadMesh": "DynaPolyActor_LoadMesh",
    "func_800C01B8": "CollisionPoly_GetPointDistanceFromPlane",
    "BgCheck_CreateTriNormFromPolygon": "CollisionPoly_GetVertices",
    "func_800C02C0": "CollisionPoly_GetVerticesByBgId",
    "BgCheck_PolygonCollidesWithSphere": "CollisionPoly_SphVsPoly",
    "BgCheck_ScenePolygonListsInsertSorted": "StaticLookup_AddPolyToSSList",
    "BgCheck_ScenePolygonListsInsert": "StaticLookup_AddPoly",
    "BgCheck_GetPolyMinSubdivisions": "BgCheck_GetSubdivisionMinBounds",
    "BgCheck_GetPolyMaxSubdivisions": "BgCheck_GetSubdivisionMaxBounds",
    "BgCheck_GetPolyMinMaxSubdivisions": "BgCheck_GetPolySubdivisionBounds",
    "func_800C2BE0": "BgCheck_PolyIntersectsSubdivision",
    "BgCheck_SplitScenePolygonsIntoSubdivisions": "BgCheck_InitStaticLookup",
    "BgCheck_GetIsDefaultSpecialScene": "BgCheck_IsSmallMemScene",
    "BgCheck_GetSpecialSceneMaxMemory": "BgCheck_TryGetCustomMemsize",
    "BgCheck_CalcSubdivisionSize": "BgCheck_SetSubdivisionDimension",
    "BgCheck_Init": "BgCheck_Allocate",
    "func_800C3C00": "BgCheck_SetContextFlags",
    "func_800C3C14": "BgCheck_UnsetContextFlags",
    "BgCheck_GetActorMeshHeader": "BgCheck_GetCollisionHeader",
    "func_800C3D50": "BgCheck_RaycastFloorImpl",
    "func_800C3F40": "BgCheck_CameraRaycastFloor1",
    "func_800C3FA0": "BgCheck_EntityRaycastFloor1",
    "func_800C4000": "BgCheck_EntityRaycastFloor2",
    "func_800C4058": "BgCheck_EntityRaycastFloor2_1",
    "func_800C40B4": "BgCheck_EntityRaycastFloor3",
    "func_800C411C": "BgCheck_EntityRaycastFloor5",
    "func_800C4188": "BgCheck_EntityRaycastFloor5_2",
    "func_800C41E4": "BgCheck_EntityRaycastFloor5_3",
    "func_800C4240": "BgCheck_EntityRaycastFloor6",
    "func_800C42A8": "BgCheck_EntityRaycastFloor7",
    "func_800C4314": "BgCheck_AnyRaycastFloor1",
    "func_800C43CC": "BgCheck_AnyRaycastFloor2",
    "func_800C4488": "BgCheck_CameraRaycastFloor2",
    "func_800C44F0": "BgCheck_EntityRaycastFloor8",
    "func_800C455C": "BgCheck_EntityRaycastFloor9",
    "func_800C45C4": "BgCheck_CheckWallImpl",
    "func_800C4C74": "BgCheck_EntitySphVsWall1",
    "func_800C4CD8": "BgCheck_EntitySphVsWall2",
    "func_800C4D3C": "BgCheck_EntitySphVsWall3",
    "func_800C4DA4": "BgCheck_EntitySphVsWall4",
    "func_800C4E10": "BgCheck_CheckCeilingImpl",
    "func_800C4F38": "BgCheck_AnyCheckCeiling",
    "func_800C4F84": "BgCheck_EntityCheckCeiling",
    "func_800C54AC": "BgCheck_CameraLineTest1",
    "func_800C5538": "BgCheck_CameraLineTest2",
    "func_800C55C4": "BgCheck_EntityLineTest1",
    "func_800C5650": "BgCheck_EntityLineTest2",
    "func_800C56E0": "BgCheck_EntityLineTest3",
    "func_800C576C": "BgCheck_ProjectileLineTest",
    "func_800C57F8": "BgCheck_AnyLineTest1",
    "func_800C583C": "BgCheck_AnyLineTest2",
    "func_800C58C8": "BgCheck_AnyLineTest3",
    "func_800C5954": "BgCheck_SphVsFirstPolyImpl",
    "func_800C5A20": "BgCheck_SphVsFirstPoly",
    "func_800C5A64": "BgCheck_SphVsFirstWall",
    "BgCheck_ScenePolygonListsInit": "SSNodeList_Init",
    "BgCheck_ScenePolygonListsAlloc": "SSNodeList_Alloc",
    "func_800C5B80": "SSNodeList_GetNextNode",
    "BgCheck_ScenePolygonListsReserveNode": "SSNodeList_GetNextNodeIdx",
    "BgCheck_ActorMeshParamsInit": "ScaleRotPos_Init",
    "BgCheck_SetActorMeshParams": "ScaleRotPos_SetValue",
    "BgCheck_ActorMeshPolyListsHeadsInit": "DynaLookup_ResetLists",
    "BgCheck_ActorMeshPolyListsInit": "DynaLookup_Reset",
    "BgCheck_ActorMeshVerticesIndexInit": "DynaLookup_ResetVtxStartIndex",
    "BgCheck_ActorMeshWaterboxesIndexInit": "DynaLookup_ResetWaterBoxStartIndex",
    "BgCheck_ActorMeshInit": "BgActor_Init",
    "BgCheck_ActorMeshInitFromActor": "BgActor_SetActor",
    "BgCheck_HasActorMeshChanged": "BgActor_IsTransformUnchanged",
    "BgCheck_PolygonsInit": "DynaPoly_NullPolyList",
    "BgCheck_PolygonsAlloc": "DynaPoly_AllocPolyList",
    "BgCheck_VerticesInit": "DynaPoly_NullVtxList",
    "BgCheck_VerticesListAlloc": "DynaPoly_AllocVtxList",
    "BgCheck_WaterboxListInit": "DynaPoly_InitWaterBoxList",
    "BgCheck_WaterboxListAlloc": "DynaPoly_AllocWaterBoxList",
    "BgCheck_ActorMeshUpdateParams": "DynaPoly_SetBgActorPrevTransform",
    "BgCheck_IsActorMeshIndexValid": "DynaPoly_IsBgIdBgActor",
    "BgCheck_DynaInit": "DynaPoly_Init",
    "BgCheck_DynaAlloc": "DynaPoly_Alloc",
    "BgCheck_AddActorMesh": "DynaPoly_SetBgActor",
    "BgCheck_GetActorOfMesh": "DynaPoly_GetActor",
    "BgCheck_RemoveActorMesh": "DynaPoly_DeleteBgActor",
    "BgCheck_AddActorMeshToLists": "DynaPoly_ExpandSRT",
    "BgCheck_Update": "DynaPoly_Setup",
    "BgCheck_UpdateAllActorMeshes": "DynaPoly_UpdateBgActorTransforms",
    "BgCheck_RelocateMeshHeaderPointers": "CollisionHeader_SegmentedToVirtual",
    "BgCheck_RelocateMeshHeader": "CollisionHeader_GetVirtual",
    "BgCheck_RelocateAllMeshHeaders": "BgCheck_InitCollisionHeaders",
    "BgCheck_GetPolygonAttributes": "SurfaceType_GetData",
    "func_800C9704": "SurfaceType_GetCamDataIndex",
    "func_800C9924": "SurfaceType_GetCamPosData",
    "func_800C99AC": "SurfaceType_GetSceneExitIndex",
    "func_800C9B90": "SurfaceType_IsHorseBlocked",
    "func_800C9BDC": "SurfaceType_GetSfx",
    "func_800C9C74": "SurfaceType_GetSlope",
    "func_800C9C9C": "SurfaceType_GetLightSettingIndex",
    "func_800C9CC4": "SurfaceType_GetEcho",
    "func_800C9CEC": "SurfaceType_IsHookshotSurface",
    "func_800C9D14": "SurfaceType_IsIgnoredByEntities",
    "func_800C9D50": "SurfaceType_IsIgnoredByProjectiles",
    "func_800C9D8C": "SurfaceType_GetConveyorType",
    "func_800C9E18": "SurfaceType_GetConveyorSpeed",
    "func_800C9E40": "SurfaceType_GetConveyorDirection",
    "func_800C9E88": "SurfaceType_IsWallDamage",
    "func_800C9EBC": "WaterBox_GetSurfaceImpl",
    "func_800CA1AC": "WaterBox_GetSurface1",
    "func_800CA1E8": "WaterBox_GetSurface1_2",
    "func_800CA22C": "WaterBox_GetSurface2",
    "func_800CA6D8": "WaterBox_GetLightSettingIndex",
    "func_80179678": "Math3D_PlaneVsLineSegClosestPoint",
    "Math3D_DistanceSquared": "Math3D_Vec3fDistSq",
    "Math3D_NormalVector": "Math3D_SurfaceNorm",
    "func_8017A954": "Math3D_PointRelativeToCubeFaces",
    "func_8017AA0C": "Math3D_PointRelativeToCubeEdges",
    "func_8017ABBC": "Math3D_PointRelativeToCubeVertices",
    "func_8017AD38": "Math3D_LineVsCube",
    "Math3D_NormalizedDistanceFromPlane": "Math3D_UDistPlaneToPos",
    "Math3D_NormalizedSignedDistanceFromPlane": "Math3D_DistPlaneToPos",
    "func_8017BAD0": "Math3D_TriChkPointParaYDist",
    "func_8017BE30": "Math3D_TriChkPointParaYIntersectDist",
    "func_8017BEE0": "Math3D_TriChkPointParaYIntersectInsideTri",
    "func_8017C008": "Math3D_TriChkLineSegParaYIntersect",
    "func_8017C494": "Math3D_TriChkPointParaYIntersectInsideTri2",
    "func_8017C540": "Math3D_TriChkPointParaXDist",
    "func_8017C850": "Math3D_TriChkPointParaXIntersect",
    "func_8017C980": "Math3D_TriChkLineSegParaXIntersect",
    "func_8017CB7C": "Math3D_TriChkLineSegParaZDist",
    "func_8017CEF0": "Math3D_TriChkPointParaZIntersect",
    "func_8017D020": "Math3D_TriChkLineSegParaZIntersect",
    "Math3D_ColSphereLineSeg": "Math3D_LineVsSph",
    "Math3D_ColSphereSphere": "Math3D_SphVsSph",
    "func_8017F9C0": "Math3D_XZInSphere",
    "func_8017FA34": "Math3D_XYInSphere",
    "func_8017FAA8": "Math3D_YZInSphere",
    "func_800DFB14": "Camera_ChangeDataIdx",
    "func_800DFC68": "Camera_GetInputDirYaw",
    "func_800DFCB4": "Camera_GetCamDirPitch",
    "func_800DFCDC": "Camera_GetCamDirYaw",
    "func_800E0308": "Camera_SetTargetActor",
    "func_800E031C": "Camera_GetWaterYPos",
    "func_800E02AC": "Camera_SetToTrackActor",
    "func_800DFAC8": "Camera_ChangeSetting",
    "func_800DFC90": "Camera_GetCamDir",
    "func_800DFD04": "Camera_AddQuake",
    "func_800DFFAC": "Camera_ChangeDoorCam",
    "func_801694DC": "Play_CreateSubCamera",
    "Play_GetActiveCameraIndex": "Play_GetActiveCamId",
    "func_80169590": "Play_CameraChangeStatus",
    "func_80169600": "Play_ClearCamera",
    "func_80169668": "Play_ClearAllSubCameras",
    "func_8016981C": "Play_CameraSetAtEyeUp",
    "func_80169940": "Play_CameraSetFov",
    "func_80169988": "Play_CameraSetRoll",
    "func_801699D4": "Play_CopyCamera",
    "func_80169AC0": "Play_CameraChangeSetting",
    "func_80169BC4": "Play_CameraGetUID",
    "func_80169C64": "Play_GetCsCamDataSetting",
    "func_80169C84": "Play_GetCsCamDataVec3s",
    "convert_scene_number_among_shared_scenes": "Play_GetOriginalSceneNumber",
    "func_80169D40": "Play_SaveCycleSceneFlags",
    "func_80169DCC": "Play_SetRespawnData",
    "func_80169E6C": "Play_SetupRespawnPoint",
    "func_8016A0AC": "Play_IsUnderwater",
    "func_801690CC": "Play_InCsMode",
    "func_80112B40": "Interface_LoadItemIconImpl",
    "func_80112BE4": "Interface_LoadItemIcon",
    "func_80114978": "Item_CheckObtainability",
    "func_801149A0": "Inventory_DeleteItem",
    "func_80114A9C": "Inventory_UnequipItem",
    "func_80114B84": "Inventory_ReplaceItem",
    "func_80114CA0": "Inventory_UpdateDeitySwordEquip",
    "Interface_HasEmptyBottle": "Inventory_HasEmptyBottle",
    "Interface_HasItemInBottle": "Inventory_HasItemInBottle",
    "func_80114FD0": "Inventory_UpdateBottleItem",
    "func_80115130": "Inventory_ConsumeFairy",
    "func_801152B8": "Inventory_UpdateItem",
    "func_80115908": "Health_ChangeBy",
    "func_801159c0": "Health_GiveHearts",
    "func_801159EC": "Rupees_ChangeBy",
    "func_80115A14": "Inventory_ChangeAmmo",
    "func_8013EC44": "Rumble_Override",
    "func_8013ECE0": "Rumble_Request",
    "func_8017D2FC": "Math3D_LineSegVsPlane",
    "func_800A81F0": "EffectBlure_AddVertex",
    "func_800A8514": "EffectBlure_AddSpace",
    "Effect_GetParams": "Effect_GetByIndex",
    "func_800F5A8C": "Environment_LerpWeight",
    "func_801A3F54": "Audio_SetCutsceneFlag",
    "func_800EA0D4": "Cutscene_Start",
    "func_800EA0EC": "Cutscene_End",
    "func_800EDE34": "Cutscene_ActorTranslate",
    "func_800EDF24": "Cutscene_ActorTranslateAndYaw",
    "func_800EDF78": "Cutscene_ActorTranslateAndYawSmooth",
    "func_800EE0CC": "Cutscene_ActorTranslateXZAndYawSmooth",
    "func_800EE1D8": "Cutscene_GetSceneSetupIndex",
    "func_800EE200": "Cutscene_GetActorActionIndex",
    "func_800EE29C": "Cutscene_CheckActorAction",
    "func_800EE2F4": "Cutscene_IsPlaying",
    "func_801343C0": "SkelAnime_DrawTransformFlexOpa",
    "func_80134148": "SkelAnime_DrawTransformFlexLimbOpa",
    "func_80114E90": "Inventory_HasEmptyBottle",
    "func_80114F2C": "Inventory_HasItemInBottle",
    "func_80123C90": "Player_SetEquipmentData",
    "Quake2_ClearType": "Distortion_ClearType",
    "Quake2_SetType": "Distortion_SetType",
    "Quake2_SetCountdown": "Distortion_SetCountdown",
    "func_800BE680": "Actor_DrawDamageEffects",
    "func_8012F22C": "Inventory_GetSkullTokenCount",

    "func_8013AB00": "SubS_DrawTransformFlex",
    "func_8013A860": "SubS_DrawTransformFlexLimb",
    "func_8013BC6C": "SubS_ChangeAnimationByInfoS",
    "func_8013E1C8": "SubS_ChangeAnimationBySpeedInfo",
    "func_8013D9C8": "SubS_FillLimbRotTables",
    "func_8013A7C0": "SubS_FindDoor",
    "func_8013E640": "SubS_FindActorCustom",
    "func_ActorCategoryIterateById": "SubS_FindActor",
    "func_8013BB7C": "SubS_FindNearestActor",
    "func_8013E2D4": "SubS_StartActorCutscene",
    "func_8013E3B8": "SubS_FillCutscenesList",
    "func_8013AED4": "SubS_UpdateFlags",
    "func_8013D8DC": "SubS_IsObjectLoaded",
    "func_8013D924": "SubS_GetObjectIndex",
    "func_8013D5E8": "SubS_AngleDiffLessEqual",
    "func_8013DCE0": "SubS_ActorPathing_Init",
    "func_8013DE04": "SubS_ActorPathing_Update",
    "func_8013DF3C": "SubS_ActorPathing_ComputePointInfo",
    "func_8013E054": "SubS_ActorPathing_MoveWithGravity",
    "func_8013E07C": "SubS_ActorPathing_MoveWithoutGravityReverse",
    "func_8013E0A4": "SubS_ActorPathing_SetNextPoint",
    "func_8013BB34": "SubS_GetAdditionalPath",
    "func_8013BD40": "SubS_HasReachedPoint",
    "func_8013BEDC": "SubS_GetDayDependentPath",
    "func_8013C8B8": "SubS_CopyPointFromPathCheckBounds",
    "func_8013D648": "SubS_GetPathByIndex",
    "func_8013D68C": "SubS_CopyPointFromPath",
    "func_8013D720": "SubS_GetDistSqAndOrientPoints",
    "func_8013D768": "SubS_MoveActorToPoint",
    "func_8013D83C": "SubS_GetDistSqAndOrientPath",
    "func_8013DB90": "SubS_IsFloorAbove",
    "func_8013DC40": "SubS_CopyPointFromPathList",
    "func_8013DCCC": "SubS_GetPathCount",
    "func_8013AD9C": "SubS_UpdateLimb",
    "func_8013D2E0": "SubS_TurnToPoint",

    "func_80147624": "Message_ShouldAdvance",
    "func_80147734": "Message_ShouldAdvanceSilent",
    "func_80149EBC": "Message_FindMessage",
    "func_8014CC14": "Message_LoadChar",
    "func_801518B0": "Message_StartTextbox",
    "func_801588D0": "Message_FindMessageNES",
    "func_80158988": "Message_LoadCharNES",
    "func_80158A24": "Message_LoadPluralRupeesNES",
    "func_80158C04": "Message_LoadLocalizedRupeesNES",
    "func_80158D98": "Message_LoadRupeesNES",
    "func_80158FB0": "Message_LoadTimeNES",
    "func_8015926C": "Message_LoadAreaTextNES",
    "func_8015E750": "Message_FindCreditsMessage",
    "func_80133038": "Schedule_RunScript",

    "EffectSsKiraKira_SpawnSmallYellow": "EffectSsKirakira_SpawnSmallYellow",
    "EffectSsKiraKira_SpawnSmall": "EffectSsKirakira_SpawnSmall",
    "EffectSsKiraKira_SpawnDispersed": "EffectSsKirakira_SpawnDispersed",
    "EffectSsKiraKira_SpawnFocused": "EffectSsKirakira_SpawnFocused",
    "Effect_GetGlobalCtx": "Effect_GetPlayState",
    "EffectSsHitMark_Spawn": "EffectSsHitmark_Spawn",
    "EffectSsHitMark_SpawnFixedScale": "EffectSsHitmark_SpawnFixedScale",
    "EffectSsHitMark_SpawnCustomScale": "EffectSsHitmark_SpawnCustomScale",

    "func_800E8F08": "Actor_TrackNone",
    "func_800E8FA4": "Actor_TrackPoint",
    "func_800E9250": "Actor_TrackPlayer",
    "func_800E8EA0": "Actor_ContinueText",

    "func_8010A000": "Map_GetDungeonOrBossAreaIndex",
    "func_8010A074": "Map_IsInDungeonOrBossArea",
    "func_8010A0F0": "Map_GetDungeonAreaIndex",
    "func_8010A164": "Map_IsInDungeonArea",
    "func_8010A194": "Map_GetBossAreaIndex",
    "func_8010A208": "Map_IsInBossArea",
    "func_8010A2DC": "Minimap_SavePlayerRoomInitInfo",
    "func_8010A33C": "Map_InitRoomData",
    "func_8010A410": "Map_Destroy",
    "func_8010A430": "Map_Init",
    "func_8010A54C": "Minimap_Draw",
    "func_8010A580": "Map_Update",

    "ActorCutscene_GetCurrentCamera": "ActorCutscene_GetCurrentSubCamId",

    # Structs
    "ActorAnimationEntry": "AnimationInfo",
    "ActorAnimationEntryS": "AnimationInfoS",
    "struct_80B8E1A8": "AnimationSpeedInfo",
    "GlobalContext": "PlayState",
    "globalCtx": "play",
    "globalCtx2": "play2",
    "ScheduleResult": "ScheduleOutput",

    # Struct members
    "skelAnime.unk03": "skelAnime.taper",
    "skelAnime.animCurrentSeg": "skelAnime.animation",
    "skelAnime.initialFrame": "skelAnime.startFrame",
    "skelAnime.animFrameCount": "skelAnime.endFrame",
    "skelAnime.totalFrames": "skelAnime.animLength",
    "skelAnime.animCurrentFrame": "skelAnime.curFrame",
    "skelAnime.animPlaybackSpeed": "skelAnime.playSpeed",
    "skelAnime.limbDrawTbl": "skelAnime.jointTable",
    "skelAnime.transitionDrawTbl": "skelAnime.morphTable",
    "skelAnime.transCurrentFrame": "skelAnime.morphWeight",
    "skelAnime.transitionStep": "skelAnime.morphRate",
    "skelAnime.animUpdate": "skelAnime.update",
    "skelAnime.flags": "skelAnime.moveFlags",
    "skelAnime.prevFrameRot": "skelAnime.prevRot",
    "skelAnime.prevFramePos": "skelAnime.prevTransl",
    "skelAnime.unk3E": "skelAnime.baseTransl",
    "actor.minVelocityY": "actor.terminalVelocity",
    "actor.yDistToWater": "actor.depthInWater",
    "actor.yDistToPlayer": "actor.playerHeightRel",

    "gSaveContext.weekEventReg": "gSaveContext.save.weekEventReg",
    "gSaveContext.playerForm": "gSaveContext.save.playerForm",
    "gSaveContext.day": "gSaveContext.save.day",
    "gSaveContext.isNight": "gSaveContext.save.isNight",
    "gSaveContext.naviTimer": "gSaveContext.save.playerData.tatlTimer",
    "gSaveContext.tatlTimer": "gSaveContext.save.playerData.tatlTimer",
    "gSaveContext.rupees": "gSaveContext.save.playerData.rupees",
    "gSaveContext.magicAcquired": "gSaveContext.save.playerData.magicAcquired",
    "gSaveContext.doubleMagic": "gSaveContext.save.playerData.doubleMagic",
    "gSaveContext.doubleDefense": "gSaveContext.save.playerData.doubleDefense",
    "gSaveContext.playerName": "gSaveContext.save.playerData.playerName",
    "gSaveContext.inventory": "gSaveContext.save.inventory",
    "gSaveContext.equippedMask": "gSaveContext.save.equippedMask",
    "gSaveContext.entranceIndex": "gSaveContext.save.entranceIndex",
    "gSaveContext.time": "gSaveContext.save.time",
    "gSaveContext.unk_14": "gSaveContext.save.daySpeed",
    "gSaveContext.unk_FE6": "gSaveContext.save.bombersCaughtNum",
    "gSaveContext.unk_FE7": "gSaveContext.save.bombersCaughtOrder",
    "gSaveContext.linkAge": "gSaveContext.save.linkAge",
    "gSaveContext.dekuPlaygroundHighScores": "gSaveContext.save.dekuPlaygroundHighScores",
    "gSaveContext.lotteryCodeGuess": "gSaveContext.save.lotteryCodeGuess",
    "gSaveContext.permanentSceneFlags": "gSaveContext.save.permanentSceneFlags",
    "gSaveContext.bomberCode": "gSaveContext.save.bomberCode",
    "gSaveContext.skullTokenCount": "gSaveContext.save.skullTokenCount",
    "gSaveContext.cutscene": "gSaveContext.save.cutscene",
    "gSaveContext.health": "gSaveContext.save.playerData.health",
    "gSaveContext.equips": "gSaveContext.save.equips",
    "gSaveContext.unk_1016": "gSaveContext.jinxTimer",
    "gSaveContext.unk_3F58": "gSaveContext.sunsSongState",
    "gSaveContext.unk_48C8": "gSaveContext.dungeonIndex",

    "player->unk_A87": "player->exchangeItemId",
    "player->leftHandActor": "player->heldActor",
    "player->unk_384": "player->getItemId",
    "player->unk_386": "player->getItemDirection",
    "player->unk_388": "player->interactRangeActor",
    "player->unk_38C": "player->mountSide",
    "player->unk_394": "player->csMode",
    "player->swordQuads": "player->meleeWeaponQuads",
    "player->blureEffectIndex": "player->meleeWeaponEffectIndex",
    "player->swordAnimation": "player->meleeWeaponAnimation",
    "player->swordState": "player->meleeWeaponState",
    "player->swordInfo": "player->meleeWeaponInfo",
    "csCtx.npcActions": "csCtx.actorActions",
    "csCtx->npcActions": "csCtx->actorActions",
    "csCtx.unk_12": "csCtx.currentCsIndex",
    "globalCtx->mf_187FC": "play->billboardMtxF",
    "globalCtx->projectionMatrix": "play->viewProjectionMtxF",
    "globalCtx->actorCtx.actorList[": "play->actorCtx.actorLists[",
    "globalCtx->envCtx.unk_8C": "play->envCtx.lightSettings",
    "globalCtx->envCtx.unk_E5": "play->envCtx.fillScreen",
    "globalCtx->envCtx.unk_E6": "play->envCtx.screenFillColor",
    "globalCtx->envCtx.unk_C3": "play->envCtx.lightSettingOverride",
    "globalCtx->envCtx.unk_DC": "play->envCtx.lightBlend",
    "globalCtx->interfaceCtx.unk_21E": "play->interfaceCtx.bButtonDoAction",

    "play->msgCtx.unk11F04": "play->msgCtx.currentTextId",
    "play->msgCtx.unk11F10": "play->msgCtx.msgLength",
    "play->msgCtx.unk11F22": "play->msgCtx.msgMode",
    "play->msgCtx.unk12023": "play->msgCtx.stateTimer",
    "play->msgCtx.unk1202A": "play->msgCtx.ocarinaMode",
    "play->msgCtx.unk1202C": "play->msgCtx.ocarinaAction",

    "play->sceneLoadFlag": "play->transitionTrigger",
    "play->unk_18B4A": "play->transitionMode",
    "play->unk_1887F": "play->transitionType",
    "gSaveContext.nextTransition": "gSaveContext.nextTransitionType",
    "gSaveContext.unk_3F48": "gSaveContext.cutsceneTransitionControl",
    "gSaveContext.fadeDuration": "gSaveContext.transFadeDuration",
    "gSaveContext.fadeSpeed": "gSaveContext.transWipeSpeed",

    "D_801D15B0" : "gZeroVec3f",
    "D_801D15BC" : "gZeroVec3s",
    "D_801D1DE0" : "gIdentityMtx",
    "D_801D1E20" : "gIdentityMtxF",
    "D_04020658" : "gameplay_keep_Anim_020658",
    "D_04022B28" : "gDoorSkel",
    "D_04023100" : "gDoorCol",

    # Macros
    "CUR_EQUIP_VALUE_VOID": "GET_CUR_EQUIP_VALUE",
    "CUR_UPG_VALUE_VOID": "GET_CUR_UPG_VALUE",
    "ICHAIN_F32_DIV1000(minVelocityY,": "ICHAIN_F32_DIV1000(terminalVelocity,",
    "ICHAIN_F32(minVelocityY,": "ICHAIN_F32(terminalVelocity,",

    # Example of custom behaviour:
    # "PLAYER": ("GET_PLAYER(play)", {"ignore": (-1, '"PLAYER"')}), # ignore "PLAYER" in sSoundBankNames
}

# [a-zA-Z0-9_]
def is_word_char(c):
    return (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z') or (c >= '0' and c <= '9') or c == '_'

def replace_single(file):
    with open(file, 'r', encoding = 'utf-8') as infile:
        srcdata = infile.read()

    changesCount = 0

    for old, new in simpleReplace.items():
        # replace `old` with `new`
        if old in srcdata:
            changesCount += 1
            print(old, "->", new)
            srcdata = srcdata.replace(old, new)

    for old, new in wordReplace.items():
        # `new` can be a tuple where the first element is what to replace `old` with,
        # and the second element is a dict containing "custom behavior" properties.
        if isinstance(new, tuple):
            custom_behavior = True
            new, custom_behavior_data = new
            # The "ignore" data is a tuple where the first element is an offset relative to
            # where `old` was found, and the string from that index must differ from the
            # tuple's second element for the replacement to be done.
            custom_behavior_ignore_data = custom_behavior_data.get("ignore")
            custom_behavior_ignore = custom_behavior_ignore_data is not None
            if custom_behavior_ignore:
                custom_behavior_ignore_offset, custom_behavior_ignore_match = custom_behavior_ignore_data
        else:
            custom_behavior = False
        # replace `old` with `new` if the occurence of `old` is the whole word
        oldStartIdx = srcdata.find(old)
        if oldStartIdx >= 0:
            old_start_as_word = is_word_char(old[0])
            old_end_as_word = is_word_char(old[-1])
            replaceCount = 0
            while oldStartIdx >= 0:
                replace = True
                if old_start_as_word:
                    if oldStartIdx == 0:
                        pass
                    elif is_word_char(srcdata[oldStartIdx-1]):
                        replace = False
                if old_end_as_word:
                    oldEndIdx = oldStartIdx + len(old)
                    if oldEndIdx >= len(srcdata):
                        pass
                    elif is_word_char(srcdata[oldEndIdx]):
                        replace = False
                if replace and custom_behavior and custom_behavior_ignore:
                    if srcdata[oldStartIdx + custom_behavior_ignore_offset:].startswith(custom_behavior_ignore_match):
                        replace = False
                if replace:
                    srcdata = srcdata[:oldStartIdx] + new + srcdata[oldEndIdx:]
                    replaceCount += 1
                oldStartIdx = srcdata.find(old, oldStartIdx + len(new))
            if replaceCount > 0:
                changesCount += 1
                print(old, "->", new)

    if changesCount > 0:
        print('Changed', changesCount, 'entry' if changesCount == 1 else 'entries', 'in', file)
        with open(file, 'w', encoding = 'utf-8', newline = '\n') as outfile:
            outfile.write(srcdata)

def replace_all(repo):
    for subdir, dirs, files in os.walk(os.path.join(repo,'src')):
        for filename in files:
            if filename.endswith('.c') or filename.endswith('.h'):
                file = os.path.join(subdir,filename)
                replace_single(file)

    for subdir, dirs, files in os.walk(os.path.join(repo,'asm')):
        for filename in files:
            if filename.endswith('.s'):
                file = os.path.join(subdir,filename)
                replace_single(file)

    for subdir, dirs, files in os.walk(os.path.join(repo,'data')):
        for filename in files:
            if filename.endswith('.s'):
                file = os.path.join(subdir,filename)
                replace_single(file)

    for subdir, dirs, files in os.walk(os.path.join(repo,'docs')):
        for filename in files:
            if filename.endswith('.md'):
                file = os.path.join(subdir,filename)
                replace_single(file)


def dictSanityCheck():
    keys = wordReplace.keys()
    values = wordReplace.values()
    for k in keys:
        if k in values:
            print(f"Key '{k}' found in values")
            print(f"This would produce unintended renames")
            print(f"Fix this by removing said key from the dictionary")
            exit(-1)

    keys = simpleReplace.keys()
    values = {*wordReplace.values(), *simpleReplace.values()}
    for k in keys:
        for value in values:
            if k in value:
                print(f"Key '{k}' found in values")
                print(f"This would produce unintended renames")
                print(f"Fix this by removing said key from the dictionary")
                exit(-1)

def main():
    parser = argparse.ArgumentParser(description='Apply function renames to a file')
    parser.add_argument('file', help="source file to be processed. use . to process the whole repo")
    args = parser.parse_args()

    dictSanityCheck()

    if args.file == '.':
        replace_all(os.curdir)
    else:
        replace_single(args.file)

if __name__ == "__main__":
    main()
