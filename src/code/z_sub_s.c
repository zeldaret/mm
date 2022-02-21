/*
 * File: z_sub_s.c
 * Description: Various miscellaneous helpers
 */

#include "global.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

/**
 * Finds the first EnDoor instance with unk_1A4 == 5 and the specified unk_1A5.
 */
EnDoor* SubS_FindDoor(GlobalContext* globalCtx, s32 unk_1A5) {
    Actor* actor = NULL;
    EnDoor* door;

    while (true) {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_DOOR, ACTOR_EN_DOOR);
        door = (EnDoor*)actor;

        if (actor == NULL) {
            break;
        }

        if ((door->unk_1A4 == 5) && (door->unk_1A5 == (u8)unk_1A5)) {
            break;
        }

        if (actor->next == NULL) {
            door = NULL;
            break;
        }

        actor = actor->next;
    }

    return door;
}

Gfx* SubS_DrawTransformFlexLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                                OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw,
                                TransformLimbDraw transformLimbDraw, Actor* actor, Mtx** mtx, Gfx* gfx) {
    StandardLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;

    Matrix_StatePush();
    limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];
    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;
    newDList = limbDList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, actor, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        Matrix_StatePush();

        transformLimbDraw(globalCtx, limbIndex, actor, &gfx);

        if (newDList != NULL) {
            Matrix_ToMtx(*mtx);
            gSPMatrix(gfx++, *mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, newDList);
            (*mtx)++;
        } else if (limbDList != NULL) {
            Matrix_ToMtx(*mtx);
            (*mtx)++;
        }
        Matrix_StatePop();
    }
    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &limbDList, &rot, actor, &gfx);
    }
    if (limb->child != LIMB_DONE) {
        gfx = SubS_DrawTransformFlexLimb(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                         transformLimbDraw, actor, mtx, gfx);
    }
    Matrix_StatePop();
    if (limb->sibling != LIMB_DONE) {
        gfx = SubS_DrawTransformFlexLimb(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                         transformLimbDraw, actor, mtx, gfx);
    }
    return gfx;
}

/**
 * Draw all limbs of type `StandardLimb` in a given flexible skeleton
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 *
 * Also makes use of a `TransformLimbDraw`, which transforms limbs based on world coordinates, as opposed to local limb
 * coordinates.
 * Note that the `TransformLimbDraw` does not have a NULL check, so must be provided even if empty.
 */
Gfx* SubS_DrawTransformFlex(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                            OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw,
                            TransformLimbDraw transformLimbDraw, Actor* actor, Gfx* gfx) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* newDlist;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    Mtx* mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(dListCount * sizeof(Mtx)));

    if (skeleton == NULL) {
        return NULL;
    }

    gSPSegment(gfx++, 0x0D, mtx);
    Matrix_StatePush();
    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);
    pos.x = jointTable->x;
    pos.y = jointTable->y;
    pos.z = jointTable->z;
    rot = jointTable[1];
    newDlist = rootLimb->dList;
    limbDList = rootLimb->dList;

    if (overrideLimbDraw == NULL || !overrideLimbDraw(globalCtx, 1, &newDlist, &pos, &rot, actor, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        Matrix_StatePush();

        transformLimbDraw(globalCtx, 1, actor, &gfx);

        if (newDlist != NULL) {
            Matrix_ToMtx(mtx);
            gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, newDlist);
            mtx++;
        } else if (limbDList != NULL) {
            Matrix_ToMtx(mtx);
            mtx++;
        }
        Matrix_StatePop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &limbDList, &rot, actor, &gfx);
    }

    if (rootLimb->child != LIMB_DONE) {
        gfx = SubS_DrawTransformFlexLimb(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                                         postLimbDraw, transformLimbDraw, actor, &mtx, gfx);
    }
    Matrix_StatePop();
    return gfx;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AD6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AD9C.s")

void SubS_UpdateFlags(u16* flags, u16 setBits, u16 unsetBits) {
    *flags = (*flags & ~unsetBits) | setBits;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AF00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B010.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B350.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B878.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013BB34.s")

/**
 * Finds the nearest actor instance of a specified Id and category to an actor.
 */
Actor* SubS_FindNearestActor(Actor* actor, GlobalContext* globalCtx, u8 actorCategory, s16 actorId) {
    Actor* actorIter = NULL;
    Actor* actorTmp;
    f32 dist;
    Actor* closestActor = NULL;
    f32 minDist = 99999.0f;
    s32 isSetup = false;

    do {
        actorIter = SubS_FindActor(globalCtx, actorIter, actorCategory, actorId);

        actorTmp = actorIter;
        if (actorTmp == NULL) {
            break;
        }
        actorIter = actorTmp;

        if (actorIter != actor) {
            dist = Actor_DistanceBetweenActors(actor, actorIter);
            if (!isSetup || dist < minDist) {
                closestActor = actorIter;
                minDist = dist;
                isSetup = true;
            }
        }

        actorIter = actorIter->next;
    } while (actorIter != NULL);

    return closestActor;
}

s32 SubS_ChangeAnimationByInfoS(SkelAnime* skelAnime, AnimationInfoS* animations, s32 index) {
    s32 endFrame;
    s32 startFrame;

    animations += index;
    endFrame = animations->frameCount;
    if (animations->frameCount < 0) {
        endFrame = Animation_GetLastFrame(&animations->animation->common);
    }
    startFrame = animations->startFrame;
    if (startFrame >= endFrame || startFrame < 0) {
        return false;
    }
    if (animations->playSpeed < 0.0f) {
        SWAP(s32, endFrame, startFrame);
    }
    Animation_Change(skelAnime, animations->animation, animations->playSpeed, startFrame, endFrame, animations->mode,
                     animations->morphFrames);
    return true;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013BD40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013BEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C068.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C624.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C964.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013CC2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013CD64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013CF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D2E0.s")

s32 SubS_AngleDiffLessEqual(s16 angleA, s16 threshold, s16 angleB) {
    return (ABS_ALT(BINANG_SUB(angleB, angleA)) <= threshold) ? true : false;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D648.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D68C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D720.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D768.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D83C.s")

s8 SubS_IsObjectLoaded(s8 index, GlobalContext* globalCtx) {
    return !Object_IsLoaded(&globalCtx->objectCtx, index) ? false : true;
}

s8 SubS_GetObjectIndex(s16 id, GlobalContext* globalCtx) {
    return Object_GetIndex(&globalCtx->objectCtx, id);
}

/**
 * Finds the first actor instance of a specified Id and category.
 */
Actor* SubS_FindActor(GlobalContext* globalCtx, Actor* actorListStart, u8 actorCategory, s16 actorId) {
    Actor* actor = actorListStart;

    if (actor == NULL) {
        actor = globalCtx->actorCtx.actorLists[actorCategory].first;
    }

    while (actor != NULL && actorId != actor->id) {
        actor = actor->next;
    }

    return actor;
}

s32 SubS_FillLimbRotTables(GlobalContext* globalCtx, s16* limbRotTableY, s16* limbRotTableZ, s32 numLimbs) {
    s32 i;
    u32 frames = globalCtx->gameplayFrames;

    for (i = 0; i < numLimbs; i++) {
        limbRotTableY[i] = (i * 50 + 0x814) * frames;
        limbRotTableZ[i] = (i * 50 + 0x940) * frames;
    }

    return true;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DCCC.s")

void func_8013DCE0(GlobalContext* globalCtx, Vec3f* worldPos, Actor* actor, struct_8013DF3C_arg1* arg3, Path* paths,
                   s32 pathIndex, s32 begPointIndex, s32 endPointIndex, s32 curPointIndex, u8 flags) {
    Path* path;

    arg3->setupPathList = globalCtx->setupPathList;
    arg3->pathIndex = pathIndex;
    path = &paths[pathIndex];
    arg3->points = Lib_SegmentedToVirtual(path->points);
    arg3->count = path->count;
    arg3->begPointIndex = begPointIndex;
    if (endPointIndex == 0) {
        arg3->endPointIndex = arg3->count - 1;
    } else if (endPointIndex > 0) {
        arg3->endPointIndex = endPointIndex;
    } else {
        //! @bug: endPointIndex is negative, subtraction causes result to be past the end
        arg3->endPointIndex = (arg3->count - endPointIndex) - 1;
    }
    arg3->curPointIndex = curPointIndex;
    arg3->curPoint.x = arg3->points[0].x;
    arg3->curPoint.y = arg3->points[0].y;
    arg3->curPoint.z = arg3->points[0].z;
    Math_Vec3f_Copy(&arg3->prevPoint, &arg3->curPoint);
    arg3->worldPos = worldPos;
    arg3->actor = actor;
    arg3->flags = flags;
    arg3->prevFlags = flags;
}

s32 func_8013DE04(GlobalContext* globalCtx, struct_8013DF3C_arg1* arg1,
                  struct_8013DF3C_arg1_ComputeFunc computePointInfoFunc,
                  struct_8013DF3C_arg1_UpdateFunc updateActorInfoFunc, struct_8013DF3C_arg1_UpdateFunc moveFunc,
                  struct_8013DF3C_arg1_UpdateFunc setNextPointFunc) {
    s32 shouldSetNextPoint;
    s32 reupdate;

    arg1->computePointInfoFunc = computePointInfoFunc;
    arg1->updateActorInfoFunc = updateActorInfoFunc;
    arg1->moveFunc = moveFunc;
    arg1->setNextPointFunc = setNextPointFunc;
    arg1->flags &= ~struct_8013DF3C_arg1_REACHED_TEMPORARY;
    reupdate = false;
    if (arg1->flags & struct_8013DF3C_arg1_MOVE_BACKWARDS) {
        if (!(arg1->prevFlags & struct_8013DF3C_arg1_MOVE_BACKWARDS)) {
            arg1->curPointIndex--;
        }
    } else if (arg1->prevFlags & struct_8013DF3C_arg1_MOVE_BACKWARDS) {
        arg1->curPointIndex++;
    }
    do {
        shouldSetNextPoint = false;
        if (arg1->computePointInfoFunc != NULL) {
            arg1->computePointInfoFunc(globalCtx, arg1);
        }
        if (arg1->updateActorInfoFunc != NULL) {
            shouldSetNextPoint = arg1->updateActorInfoFunc(globalCtx, arg1);
        }
        if (shouldSetNextPoint) {
            if (arg1->setNextPointFunc != NULL) {
                reupdate = arg1->setNextPointFunc(globalCtx, arg1);
            }
        } else if (arg1->moveFunc != NULL) {
            reupdate = arg1->moveFunc(globalCtx, arg1);
        }
    } while (reupdate);
    arg1->prevFlags = arg1->flags;
    return false;
}

void func_8013DF3C(GlobalContext* globalCtx, struct_8013DF3C_arg1* arg1) {
    Vec3f diff;

    arg1->curPoint.x = arg1->points[arg1->curPointIndex].x + arg1->pointOffset.x;
    arg1->curPoint.y = arg1->points[arg1->curPointIndex].y + arg1->pointOffset.y;
    arg1->curPoint.z = arg1->points[arg1->curPointIndex].z + arg1->pointOffset.z;
    diff.x = arg1->curPoint.x - arg1->worldPos->x;
    diff.y = arg1->curPoint.y - arg1->worldPos->y;
    diff.z = arg1->curPoint.z - arg1->worldPos->z;
    arg1->distSqToCurPointXZ = Math3D_XZLengthSquared(diff.x, diff.z);
    arg1->distSqToCurPoint = Math3D_LengthSquared(&diff);
    arg1->rotToCurPoint.y = Math_FAtan2F(diff.z, diff.x);
    arg1->rotToCurPoint.x = Math_FAtan2F(sqrtf(arg1->distSqToCurPointXZ), -diff.y);
    arg1->rotToCurPoint.z = 0;
}

s32 func_8013E054(GlobalContext* globalCtx, struct_8013DF3C_arg1* arg1) {
    Actor_MoveWithGravity(arg1->actor);
    return false;
}

s32 func_8013E07C(GlobalContext* globalCtx, struct_8013DF3C_arg1* arg1) {
    Actor_MoveWithoutGravityReverse(arg1->actor);
    return false;
}

s32 func_8013E0A4(GlobalContext* globalCtx, struct_8013DF3C_arg1* arg1) {
    s32 reupdate = true;

    Math_Vec3f_Copy(&arg1->prevPoint, &arg1->curPoint);
    if (!(arg1->flags & struct_8013DF3C_arg1_MOVE_BACKWARDS)) {
        if (arg1->curPointIndex >= arg1->endPointIndex) {
            if (arg1->flags & struct_8013DF3C_arg1_RETURN_TO_START) {
                arg1->curPointIndex = arg1->begPointIndex;
            } else if (arg1->flags & struct_8013DF3C_arg1_SWITCH_DIRECTION) {
                arg1->flags |= struct_8013DF3C_arg1_MOVE_BACKWARDS;
            } else {
                reupdate = false;
            }
            arg1->flags |= struct_8013DF3C_arg1_REACHED_END;
        } else {
            arg1->curPointIndex++;
        }
        arg1->flags |= struct_8013DF3C_arg1_REACHED_POINT;
    } else {
        if (arg1->begPointIndex >= arg1->curPointIndex) {
            if (arg1->flags & struct_8013DF3C_arg1_RETURN_TO_START) {
                arg1->curPointIndex = arg1->endPointIndex;
            } else if (arg1->flags & struct_8013DF3C_arg1_SWITCH_DIRECTION) {
                arg1->flags &= ~struct_8013DF3C_arg1_MOVE_BACKWARDS;
            } else {
                reupdate = false;
            }
            arg1->flags |= struct_8013DF3C_arg1_REACHED_END;
        } else {
            arg1->curPointIndex--;
        }
    }
    arg1->flags |= struct_8013DF3C_arg1_REACHED_POINT;
    return reupdate;
}

void SubS_ChangeAnimationBySpeedInfo(SkelAnime* skelAnime, AnimationSpeedInfo* animations, s32 nextIndex,
                                     s32* curIndex) {
    AnimationSpeedInfo* animation = &animations[nextIndex];
    f32 startFrame = skelAnime->curFrame;
    f32 endFrame;
    f32 morphFrames;

    if ((*curIndex < 0) || (nextIndex == *curIndex)) {
        morphFrames = 0.0f;
        if (*curIndex < 0) {
            startFrame = 0.0f;
        }
    } else {
        morphFrames = animation->morphFrames;
        if (nextIndex != *curIndex) {
            startFrame = 0.0f;
        }
    }
    if (animation->playSpeed >= 0.0f) {
        endFrame = Animation_GetLastFrame(&animation->animation->common);
    } else {
        startFrame = Animation_GetLastFrame(&animation->animation->common);
        endFrame = 0.0f;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, startFrame, endFrame, animation->mode,
                     morphFrames);
    *curIndex = nextIndex;
}

s32 SubS_StartActorCutscene(Actor* actor, s16 nextCutscene, s16 curCutscene, s32 type) {
    s32 isStarted = false;

    if ((curCutscene != -1) && (ActorCutscene_GetCurrentIndex() == curCutscene)) {
        ActorCutscene_Stop(curCutscene);
        ActorCutscene_SetIntentToPlay(nextCutscene);
    } else if (ActorCutscene_GetCanPlayNext(nextCutscene)) {
        switch (type) {
            case SUBS_CUTSCENE_SET_UNK_LINK_FIELDS:
                ActorCutscene_StartAndSetUnkLinkFields(nextCutscene, actor);
                break;
            case SUBS_CUTSCENE_NORMAL:
                ActorCutscene_Start(nextCutscene, actor);
                break;
            case SUBS_CUTSCENE_SET_FLAG:
                ActorCutscene_StartAndSetFlag(nextCutscene, actor);
                break;
        }
        isStarted = true;
    } else {
        ActorCutscene_SetIntentToPlay(nextCutscene);
    }

    return isStarted;
}

s32 SubS_FillCutscenesList(Actor* actor, s16 cutscenes[], s16 numCutscenes) {
    s16 cs;
    s32 i;

    for (i = 0; i < numCutscenes; i++) {
        cutscenes[i] = -1;
    }

    cs = actor->cutscene;
    i = 0;

    while (cs != -1) {
        // Note: Infinite loop if numCutscenes is less than possible additional cutscenes
        if (i < numCutscenes) {
            cutscenes[i] = cs;
            cs = ActorCutscene_GetAdditionalCutscene(cs);
            i++;
        }
    }

    return i;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E5CC.s")

/**
 * Finds the first actor instance of a specified Id and category verified with a custom callback.
 * The callback should return `true` when the actor is succesfully verified.
 */
Actor* SubS_FindActorCustom(GlobalContext* globalCtx, Actor* actor, Actor* actorListStart, u8 actorCategory,
                            s16 actorId, void* verifyData, VerifyActor verifyActor) {
    Actor* actorIter = actorListStart;

    if (actorListStart == NULL) {
        actorIter = globalCtx->actorCtx.actorLists[actorCategory].first;
    }

    while (actorIter != NULL && (actorId != actorIter->id ||
                                 (actorId == actorIter->id &&
                                  (verifyActor == NULL ||
                                   (verifyActor != NULL && !verifyActor(globalCtx, actor, actorIter, verifyData)))))) {
        actorIter = actorIter->next;
    }

    return actorIter;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E748.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E950.s")
