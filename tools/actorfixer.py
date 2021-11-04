#!/usr/bin/env python3

import argparse, os

# There are a few commented out entries that would produce unexpected renames.
# They are left as a comment so people can just grab them.

# "old": "new"
animdict = {
    "Actor_GetSwitchFlag": "Flags_GetSwitch",
    "atan_flip": "Math_Acot2F",
    "atans": "Math_Atan2S",
    "SysMatrix_StateAlloc": "Matrix_StateAlloc",
    "SysMatrix_StatePush": "Matrix_StatePush",
    "SysMatrix_CopyCurrentState": "Matrix_CopyCurrentState",
    "SysMatrix_SetCurrentState": "Matrix_SetCurrentState",
    "SysMatrix_InsertTranslation": "Matrix_InsertTranslation",
    "SysMatrix_InsertMatrix": "Matrix_InsertMatrix",
    "SysMatrix_Scale": "Matrix_Scale",
    "SysMatrix_InsertXRotation_s": "Matrix_InsertXRotation_s",
    "SysMatrix_InsertXRotation_f": "Matrix_InsertXRotation_f",
    "SysMatrix_RotateStateAroundXAxis": "Matrix_RotateStateAroundXAxis",
    "SysMatrix_SetStateXRotation": "Matrix_SetStateXRotation",
    "SysMatrix_RotateY": "Matrix_RotateY",
    "SysMatrix_InsertYRotation_f": "Matrix_InsertYRotation_f",
    "SysMatrix_InsertZRotation_s": "Matrix_InsertZRotation_s",
    "SysMatrix_InsertZRotation_f": "Matrix_InsertZRotation_f",
    "SysMatrix_InsertRotation": "Matrix_InsertRotation",
    "SysMatrix_JointPosition": "Matrix_JointPosition",
    "SysMatrix_SetStateRotationAndTranslation": "Matrix_SetStateRotationAndTranslation",
    "SysMatrix_ToRSPMatrix": "Matrix_ToRSPMatrix",
    "SysMatrix_ToMtx": "Matrix_ToMtx",
    "SysMatrix_NewMtx": "Matrix_NewMtx",
    "SysMatrix_AppendToPolyOpaDisp": "Matrix_AppendToPolyOpaDisp",
    "SysMatrix_MultiplyVector3fByState": "Matrix_MultiplyVector3fByState",
    "SysMatrix_GetStateTranslation": "Matrix_GetStateTranslation",
    "SysMatrix_GetStateTranslationAndScaledX": "Matrix_GetStateTranslationAndScaledX",
    "SysMatrix_GetStateTranslationAndScaledY": "Matrix_GetStateTranslationAndScaledY",
    "SysMatrix_GetStateTranslationAndScaledZ": "Matrix_GetStateTranslationAndScaledZ",
    "SysMatrix_MultiplyVector3fXZByCurrentState": "Matrix_MultiplyVector3fXZByCurrentState",
    "SysMatrix_MtxFCopy": "Matrix_MtxFCopy",
    "SysMatrix_FromRSPMatrix": "Matrix_FromRSPMatrix",
    "SysMatrix_MultiplyVector3fByMatrix": "Matrix_MultiplyVector3fByMatrix",
    "SysMatrix_TransposeXYZ": "Matrix_TransposeXYZ",
    "SysMatrix_NormalizeXYZ": "Matrix_NormalizeXYZ",
    "SysMatrix_InsertRotationAroundUnitVector_f": "Matrix_InsertRotationAroundUnitVector_f",
    "SysMatrix_InsertRotationAroundUnitVector_s": "Matrix_InsertRotationAroundUnitVector_s",
    "func_800B78B8": "Actor_UpdateBgCheckInfo",
    "func_8012403C": "Player_GetMask",
    "func_8012404c": "Player_RemoveMask",
    "Actor_SpawnWithParentAndCutscene": "Actor_SpawnAsChildAndCutscene",
    "Actor_SpawnWithParent": "Actor_SpawnAsChild",
    "Actor_IsLinkFacingActor": "Player_IsFacingActor",
    "Actor_IsActorFacingLink": "Actor_IsFacingPlayer",
    "Actor_IsActorFacingLinkAndWithinRange": "Actor_IsFacingAndNearPlayer",
    "Actor_IsActorFacingActorAndWithinRange": "Actor_ActorAIsFacingAndNearActorB",
    "Actor_IsActorFacingActor": "Actor_ActorAIsFacingActorB",
    "Actor_IsActorFacedByActor": "Actor_ActorBIsFacingActorA",
    "func_800B84D0": "Actor_RequestTalk",
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
    "func_800F0568": "Audio_PlaySoundAtPosition",
    "func_8016970C": "Play_CameraSetAtEye",
    "func_800BBA88": "Enemy_StartFinishingBlow",
    "ShrinkWindow_Step": "ShrinkWindow_Update",
    "ShrinkWindow_Fini": "ShrinkWindow_Destroy",
    "func_801A89A8": "Audio_QueueSeqCmd",
    "SkelAnime_LodDrawLimb(": "SkelAnime_DrawLimbLod(",
    "SkelAnime_LodDraw(": "SkelAnime_DrawLod(",
    "SkelAnime_LodDrawLimbSV(": "SkelAnime_DrawFlexLimbLod(",
    "SkelAnime_LodDrawSV(": "SkelAnime_DrawFlexLod(",
    #"SkelAnime_DrawLimb(": "SkelAnime_DrawLimbOpa(",
    #"SkelAnime_Draw(": "SkelAnime_DrawOpa(",
    "SkelAnime_DrawLimbSV(": "SkelAnime_DrawFlexLimbOpa(",
    "SkelAnime_DrawSV(": "SkelAnime_DrawFlexOpa(",
    #"SkelAnime_AnimateFrame(": "SkelAnime_GetFrameData(",
    "SkelAnime_GetTotalFrames(": "Animation_GetLength(",
    "SkelAnime_GetFrameCount(": "Animation_GetLastFrame(",
    "SkelAnime_Draw2Limb(": "SkelAnime_DrawLimb(",
    "SkelAnime_Draw2(": "SkelAnime_Draw(",
    "SkelAnime_DrawLimbSV2(": "SkelAnime_DrawFlexLimb(",
    "SkelAnime_DrawSV2(": "SkelAnime_DrawFlex(",
    "func_80134FFC": "SkelAnime_GetFrameData2",
    "func_801353D4": "Animation_GetLimbCount2",
    "SkelAnime_GetTotalFrames2(": "Animation_GetLength2(",
    "SkelAnime_GetFrameCount2(": "Animation_GetLastFrame2(",
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
    "SkelAnime_InitLinkAnimetion(": "SkelAnime_InitLink(",
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
    "SkelAnime_ChangeAnim(": "Animation_Change(",
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
    "SysMatrix_StatePop": "Matrix_StatePop",
    "SysMatrix_GetCurrentState": "Matrix_GetCurrentState",
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
    "Actor_GetRoomCleared(": "Flags_GetClear(",
    "Actor_SetRoomCleared(": "Flags_SetClear(",
    "Actor_UnsetRoomCleared(": "Flags_UnsetClear(",
    "Actor_GetRoomClearedTemp(": "Flags_GetTempClear(",
    "Actor_SetRoomClearedTemp(": "Flags_SetTempClear(",
    "Actor_UnsetRoomClearedTemp(": "Flags_UnsetTempClear(",
    "Actor_GetCollectibleFlag": "Flags_GetCollectible",
    "Actor_SetCollectibleFlag": "Flags_SetCollectible",
    "func_800B8A1C": "Actor_PickUp",
    "func_800B8B84": "Actor_PickUpNearby",
    "func_800B8BB0": "Actor_LiftActor",
    "func_800B8BD0": "Actor_PickUpFar",
    "func_801A5CFC": "Audio_PlaySoundGeneral",
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
    "zelda_malloc(": "ZeldaArena_Malloc(",
    "zelda_mallocR(": "ZeldaArena_MallocR(",
    "zelda_realloc": "ZeldaArena_Realloc",
    "zelda_free": "ZeldaArena_Free",
    "zelda_calloc": "ZeldaArena_Calloc",
    "MainHeap_AnalyzeArena": "ZeldaArena_GetSizes",
    "MainHeap_Check": "ZeldaArena_Check",
    "MainHeap_Init": "ZeldaArena_Init",
    "MainHeap_Cleanup": "ZeldaArena_Cleanup",
    "MainHeap_IsInitialized": "ZeldaArena_IsInitialized",

    # structs members
    "skelanime.unk03": "skelanime.taper",
    "skelanime.animCurrentSeg": "skelanime.animation",
    "skelanime.initialFrame": "skelanime.startFrame",
    "skelanime.animFrameCount": "skelanime.endFrame",
    "skelanime.totalFrames": "skelanime.animLength",
    "skelanime.animCurrentFrame": "skelanime.curFrame",
    "skelanime.animPlaybackSpeed": "skelanime.playSpeed",
    "skelanime.limbDrawTbl": "skelanime.jointTable",
    "skelanime.transitionDrawTbl": "skelanime.morphTable",
    "skelanime.transCurrentFrame": "skelanime.morphWeight",
    "skelanime.transitionStep": "skelanime.morphRate",
    "skelanime.animUpdate": "skelanime.update",
    "skelanime.flags": "skelanime.moveFlags",
    "skelanime.prevFrameRot": "skelanime.prevRot",
    "skelanime.prevFramePos": "skelanime.prevTransl",
    "skelanime.unk3E": "skelanime.baseTransl",
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
    "actor.yDistToWater" : "actor.depthInWater",
    "actor.yDistToPlayer" : "actor.playerHeightRel",
}

def replace_anim(file):
    with open(file, 'r', encoding='utf-8') as infile:
        srcdata = infile.read()

    funcs = list(animdict.keys())
    fixes = 0
    for func in funcs:
        newfunc = animdict.get(func)
        if(newfunc is None):
            print("How did this happen?")
            return -1
        if(func in srcdata):
            fixes += 1
            print(func)
            srcdata = srcdata.replace(func, newfunc)

    if(fixes > 0):
        print('Changed', fixes,'entr' + ('y' if fixes == 1 else 'ies') + ' in',file)
        with open(file, 'w', encoding = 'utf-8', newline = '\n') as outfile:
            outfile.write(srcdata)
    return 1

def replace_anim_all(repo):
    for subdir, dirs, files in os.walk(repo + os.sep + 'src'):
        for filename in files:
            if(filename.endswith('.c')):
                file = subdir + os.sep + filename
                replace_anim(file)
    for subdir, dirs, files in os.walk(repo + os.sep + 'asm'):
        for filename in files:
            if(filename.endswith('.s')):
                file = subdir + os.sep + filename
                replace_anim(file)
    for subdir, dirs, files in os.walk(repo + os.sep + 'tools' + os.sep + 'sizes'):
        for filename in files:
            if(filename.endswith('.csv')):
                file = subdir + os.sep + filename
                replace_anim(file)
    return 1

def dictSanityCheck():
    keys = animdict.keys()
    values = animdict.values()
    for k in keys:
        if k in values:
            print(f"Key '{k}' found in values")
            print(f"This would produce unintended renames")
            print(f"Fix this by removing said key from the dictionary")
            exit(-1)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Update to the new animation names')
    parser.add_argument('file', help="source file to be processed. use . to process the whole repo", default = None)

    args = parser.parse_args()

    dictSanityCheck()

    if(args.file == '.'):
        replace_anim_all(os.curdir)
    else:
        replace_anim(args.file)
