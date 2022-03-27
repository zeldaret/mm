#include "global.h"

#define ANIM_INTERP 1

s32 LinkAnimation_Loop(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 LinkAnimation_Once(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 SkelAnime_LoopFull(SkelAnime* skelAnime);
s32 SkelAnime_LoopPartial(SkelAnime* skelAnime);
s32 SkelAnime_Once(SkelAnime* skelAnime);
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animation);
void SkelAnime_UpdateTranslation(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
void LinkAnimation_Change(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation, f32 playSpeed,
                          f32 frame, f32 frameCount, u8 animationMode, f32 morphFrames);
void SkelAnime_CopyFrameTable(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);

static AnimationEntryCallback sAnimationLoadDone[] = {
    AnimationContext_LoadFrame, AnimationContext_CopyAll,   AnimationContext_Interp,
    AnimationContext_CopyTrue,  AnimationContext_CopyFalse, AnimationContext_MoveActor,
};

s32 sAnimQueueFlags;
s32 sDisableAnimQueueFlags;

/*
 * Draws the limb at `limbIndex` with a level of detail display lists index by `dListIndex`
 */
void SkelAnime_DrawLimbLod(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor, s32 lod) {
    LodLimb* limb;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();
    limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];

    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    dList = limb->dLists[lod];
    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, actor) == 0)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);

            gSPDisplayList(&polyTemp[1], dList);
            POLY_OPA_DISP = &polyTemp[2];
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawLimbLod(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor, lod);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawLimbLod(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                              lod);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw all limbs of type `LodLimb` in a given skeleton
 * Near or far display list is specified via `lod`
 */
void SkelAnime_DrawLod(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable,
                       OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor, s32 lod) {
    LodLimb* rootLimb;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);
    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];
    dList = rootLimb->dLists[lod];

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);

            gSPDisplayList(&polyTemp[1], dList);

            POLY_OPA_DISP = &polyTemp[2];
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawLimbLod(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                              lod);
    }

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw a limb of type `LodLimb` contained within a flexible skeleton
 * Near or far display list is specified via `lod`
 */
void SkelAnime_DrawFlexLimbLod(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                               OverrideLimbDrawFlex overrideLimbDraw, PostLimbDrawFlex postLimbDraw, Actor* actor,
                               s32 lod, Mtx** mtx) {
    LodLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;

    rot = jointTable[limbIndex];

    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    newDList = limbDList = limb->dLists[lod];

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            Matrix_ToMtx(*mtx);
            gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, newDList);
            (*mtx)++;
        } else if (limbDList != NULL) {
            Matrix_ToMtx(*mtx);
            (*mtx)++;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &newDList, &limbDList, &rot, actor);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbLod(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                                  lod, mtx);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawFlexLimbLod(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                                  lod, mtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draws all limbs of type `LodLimb` in a given flexible skeleton
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 */
void SkelAnime_DrawFlexLod(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                           OverrideLimbDrawFlex overrideLimbDraw, PostLimbDrawFlex postLimbDraw, Actor* actor,
                           s32 lod) {
    LodLimb* rootLimb;
    s32 pad;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    Mtx* mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);
    Matrix_StatePush();

    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);
    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];

    newDList = limbDList = rootLimb->dLists[lod];

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(&polyTemp[1], newDList);
            POLY_OPA_DISP = &polyTemp[2];
            mtx++;
        } else if (limbDList != NULL) {
            Matrix_ToMtx(mtx);
            mtx++;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &newDList, &limbDList, &rot, actor);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbLod(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                  actor, lod, &mtx);
    }

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/*
 * Draws the limb of the Skeleton `skeleton` at `limbIndex`
 */
void SkelAnime_DrawLimbOpa(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor) {
    StandardLimb* limb;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];
    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;
    dList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(&polyTemp[1], dList);
            POLY_OPA_DISP = &polyTemp[2];
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw all limbs of type `StandardLimb` in a given skeleton to the polyOpa buffer
 */
void SkelAnime_DrawOpa(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable,
                       OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();
    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];
    dList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(&polyTemp[1], dList);
            POLY_OPA_DISP = &polyTemp[2];
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor);
    }

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void SkelAnime_DrawFlexLimbOpa(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                               OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor,
                               Mtx** limbMatricies) {
    StandardLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];

    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    newDList = limbDList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            Matrix_ToMtx(*limbMatricies);
            gSPMatrix(POLY_OPA_DISP++, *limbMatricies, G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, newDList);
            (*limbMatricies)++;
        } else if (limbDList != NULL) {
            Matrix_ToMtx(*limbMatricies);
            (*limbMatricies)++;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &limbDList, &rot, actor);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                                  limbMatricies);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                                  limbMatricies);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw all limbs of type `StandardLimb` in a given flexible skeleton to the polyOpa buffer
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 */
void SkelAnime_DrawFlexOpa(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    Mtx* mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);

    Matrix_StatePush();

    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;
    rot = jointTable[1];

    newDList = limbDList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(&polyTemp[1], newDList);
            POLY_OPA_DISP = &polyTemp[2];
            mtx++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(mtx);
                mtx++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &limbDList, &rot, actor);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                  actor, &mtx);
    }

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void SkelAnime_DrawTransformFlexLimbOpa(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                                        OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw,
                                        TransformLimbDrawOpa transformLimbDraw, Actor* actor, Mtx** mtx) {
    StandardLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;

    rot = jointTable[limbIndex];
    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    newDList = limbDList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        Matrix_StatePush();

        transformLimbDraw(globalCtx, limbIndex, actor);

        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_ToMtx(*mtx), G_MTX_LOAD);
            gSPDisplayList(&polyTemp[1], newDList);
            POLY_OPA_DISP = &polyTemp[2];
            (*mtx)++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(*mtx);
                (*mtx)++;
            }
        }
        Matrix_StatePop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &limbDList, &rot, actor);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawTransformFlexLimbOpa(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                           transformLimbDraw, actor, mtx);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawTransformFlexLimbOpa(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw,
                                           postLimbDraw, transformLimbDraw, actor, mtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw all limbs of type `StandardLimb` in a given flexible skeleton to the polyOpa buffer
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 *
 * Also makes use of a `TransformLimbDraw`, which transforms limbs based on world coordinates, as opposed to local limb
 * coordinates.
 * Note that the `TransformLimbDraw` does not have a NULL check, so must be provided even if empty.
 */
void SkelAnime_DrawTransformFlexOpa(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                                    OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw,
                                    TransformLimbDrawOpa transformLimbDraw, Actor* actor) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    Mtx* mtx;

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);

    Matrix_StatePush();

    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;
    rot = jointTable[1];

    newDList = limbDList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, actor)) {
        Matrix_JointPosition(&pos, &rot);
        Matrix_StatePush();

        transformLimbDraw(globalCtx, 1, actor);

        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(&polyTemp[0], Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(&polyTemp[1], newDList);
            POLY_OPA_DISP = &polyTemp[2];
            mtx++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(mtx++);
            }
        }
        Matrix_StatePop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &limbDList, &rot, actor);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawTransformFlexLimbOpa(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                                           postLimbDraw, transformLimbDraw, actor, &mtx);
    }

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Copies frame data from the frame data table, indexed by the joint index table.
 * Indices below staticIndexMax are copied from that entry in the static frame data table.
 * Indices above staticIndexMax are offsets to a frame data array indexed by the frame.
 */
void SkelAnime_GetFrameData(AnimationHeader* animation, s32 frame, s32 limbCount, Vec3s* frameTable) {
    AnimationHeader* animHeader = Lib_SegmentedToVirtual(animation);
    JointIndex* jointIndices = Lib_SegmentedToVirtual(animHeader->jointIndices);
    s16* frameData = Lib_SegmentedToVirtual(animHeader->frameData);
    s16* dynamicData = &frameData[frame];
    s32 i;
    u16 staticIndexMax = animHeader->staticIndexMax;

    for (i = 0; i < limbCount; i++) {
        // Debug prints here, this is needed to prevent loop unrolling
        if (0) {
            if (0) {};
        }
        frameTable->x = jointIndices->x >= staticIndexMax ? dynamicData[jointIndices->x] : frameData[jointIndices->x];
        frameTable->y = jointIndices->y >= staticIndexMax ? dynamicData[jointIndices->y] : frameData[jointIndices->y];
        frameTable->z = jointIndices->z >= staticIndexMax ? dynamicData[jointIndices->z] : frameData[jointIndices->z];
        jointIndices++, frameTable++;
    }
}

s16 Animation_GetLength(void* animation) {
    AnimationHeaderCommon* common = Lib_SegmentedToVirtual(animation);

    return common->frameCount;
}

s16 Animation_GetLastFrame(void* animation) {
    AnimationHeaderCommon* common = Lib_SegmentedToVirtual(animation);

    return (u16)common->frameCount - 1;
}

/*
 * Draws the Skeleton `skeleton`'s limb at index `limbIndex`.  Appends all generated graphics commands to
 * `gfx`.  Returns a pointer to the next gfx to be appended to.
 */
Gfx* SkelAnime_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, Gfx* gfx) {
    StandardLimb* limb;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    Matrix_StatePush();

    limb = Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;

    rot = jointTable[limbIndex];
    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    dList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, actor, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(&gfx[1], dList);
            gfx = &gfx[2];
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor, &gfx);
    }

    if (limb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                                 gfx);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw, actor,
                                 gfx);
    }

    return gfx;
}

/*
 * Draws the Skeleton `skeleton`  Appends all generated graphics to `gfx`, and returns a pointer to the
 * next gfx to be appended to.
 */
Gfx* SkelAnime_Draw(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, OverrideLimbDraw overrideLimbDraw,
                    PostLimbDraw postLimbDraw, Actor* actor, Gfx* gfx) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return NULL;
    }

    Matrix_StatePush();

    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];

    dList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, actor, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            gSPMatrix(&gfx[0], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(&gfx[1], dList);
            gfx = &gfx[2];
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor, &gfx);
    }

    if (rootLimb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                 actor, gfx);
    }

    Matrix_StatePop();

    return gfx;
}

/**
 * Draw a limb of type `StandardLimb` contained within a flexible skeleton to the specified display buffer
 */
Gfx* SkelAnime_DrawFlexLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                            OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, Mtx** mtx,
                            Gfx* gfx) {
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
        if (newDList != NULL) {
            gSPMatrix(&gfx[0], Matrix_ToMtx(*mtx), G_MTX_LOAD);
            gSPDisplayList(&gfx[1], newDList);
            gfx = &gfx[2];
            (*mtx)++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(*mtx);
                (*mtx)++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &limbDList, &rot, actor, &gfx);
    }

    if (limb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                     actor, mtx, gfx);
    }

    Matrix_StatePop();

    if (limb->sibling != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                     actor, mtx, gfx);
    }

    return gfx;
}

/**
 * Draw all limbs of type `StandardLimb` in a given flexible skeleton to the specified display buffer
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 */
Gfx* SkelAnime_DrawFlex(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, Gfx* gfx) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    Mtx* mtx;

    if (skeleton == NULL) {
        return NULL;
    }

    mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    gSPSegment(gfx++, 0x0D, mtx);

    Matrix_StatePush();

    rootLimb = Lib_SegmentedToVirtual(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];

    newDList = limbDList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, actor, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            gSPMatrix(&gfx[0], Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(&gfx[1], newDList);
            gfx = &gfx[2];
            mtx++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(mtx);
                mtx++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &limbDList, &rot, actor, &gfx);
    }

    if (rootLimb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                                     actor, &mtx, gfx);
    }

    Matrix_StatePop();

    return gfx;
}

/**
 * Unpacks frame data for the animation at the given frame into frameTable
 * Used by the legacy animation format
 */
s16 SkelAnime_GetFrameDataLegacy(LegacyAnimationHeader* animation, s32 frame, Vec3s* frameTable) {
    LegacyAnimationHeader* animHeader = Lib_SegmentedToVirtual(animation);
    s16 limbCount = animHeader->limbCount;
    JointKey* key = Lib_SegmentedToVirtual(animHeader->jointKey);
    s16* frameData = Lib_SegmentedToVirtual(animHeader->frameData);
    s16* staticData = &frameData[0];
    s16* dynamicData = &frameData[frame];
    s32 i;

    frameTable->x = frame < key->xMax ? dynamicData[key->x] : staticData[key->x];
    frameTable->y = frame < key->yMax ? dynamicData[key->y] : staticData[key->y];
    frameTable->z = frame < key->zMax ? dynamicData[key->z] : staticData[key->z];

    frameTable++;
    key++;

    for (i = 1; i <= limbCount; i++, key++, frameTable++) {
        frameTable->x = frame < key->xMax ? dynamicData[key->x] : staticData[key->x];
        frameTable->y = frame < key->yMax ? dynamicData[key->y] : staticData[key->y];
        frameTable->z = frame < key->zMax ? dynamicData[key->z] : staticData[key->z];
    }

    return limbCount;
}

/**
 * Used by legacy animation format
 */
s16 Animation_GetLimbCount2(LegacyAnimationHeader* animation) {
    LegacyAnimationHeader* animHeader = Lib_SegmentedToVirtual(animation);

    return animHeader->limbCount;
}

/**
 * Used by legacy animation format
 */
s16 Animation_GetLength2(LegacyAnimationHeader* animation) {
    LegacyAnimationHeader* animHeader = Lib_SegmentedToVirtual(animation);

    return animHeader->frameCount;
}

/**
 * Used by legacy animation format
 */
s16 Animation_GetLastFrame2(LegacyAnimationHeader* animation) {
    AnimationHeaderCommon* animHeader = Lib_SegmentedToVirtual(animation);

    return animHeader->frameCount - 1;
}

/**
 * Linearly interpolates the start and tactoret frame tables with the given weight, putting the result in dst
 */
void SkelAnime_InterpFrameTable(s32 limbCount, Vec3s* dst, Vec3s* start, Vec3s* tactoret, f32 weight) {
    s32 i;
    s16 diff;
    s16 base;

    if (weight < 1.0f) {
        for (i = 0; i < limbCount; i++, dst++, start++, tactoret++) {
            base = start->x;
            diff = tactoret->x - base;
            dst->x = (s16)(diff * weight) + base;
            base = start->y;
            diff = tactoret->y - base;
            dst->y = (s16)(diff * weight) + base;
            base = start->z;
            diff = tactoret->z - base;
            dst->z = (s16)(diff * weight) + base;
        }
    } else {
        for (i = 0; i < limbCount; i++, dst++, tactoret++) {
            dst->x = tactoret->x;
            dst->y = tactoret->y;
            dst->z = tactoret->z;
        }
    }
}

/**
 * Zeroes out the current request count
 */
void AnimationContext_Reset(AnimationContext* animationCtx) {
    animationCtx->animationCount = 0;
}

/**
 * Shifts the queue flag to the next queue
 */
void AnimationContext_SetNextQueue(GlobalContext* globalCtx) {
    sAnimQueueFlags <<= 1;
}

/**
 * Disables the current animation queue. Only load and move actor requests will be processed for that queue.
 */
void AnimationContext_DisableQueue(GlobalContext* globalCtx) {
    sDisableAnimQueueFlags |= sAnimQueueFlags;
}

AnimationEntry* AnimationContext_AddEntry(AnimationContext* animationCtx, AnimationType type) {
    AnimationEntry* entry;
    s16 index = animationCtx->animationCount;

    if (index >= ANIMATION_ENTRY_MAX) {
        return NULL;
    }

    animationCtx->animationCount = index + 1;
    entry = &animationCtx->entries[index];
    entry->type = type;
    return entry;
}

/**
 * Requests loading frame data from the Link animation into frameTable
 */
void AnimationContext_SetLoadFrame(GlobalContext* globalCtx, LinkAnimationHeader* animation, s32 frame, s32 limbCount,
                                   Vec3s* frameTable) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_LINKANIMETION);

    if (entry != NULL) {
        LinkAnimationHeader* linkAnimHeader = Lib_SegmentedToVirtual(animation);
        u32 ram = frameTable;

        osCreateMesgQueue(&entry->data.load.msgQueue, &entry->data.load.msg, 1);
        DmaMgr_SendRequestImpl(&entry->data.load.req, ram,
                               LINK_ANIMETION_OFFSET(linkAnimHeader->segment, (sizeof(Vec3s) * limbCount + 2) * frame),
                               sizeof(Vec3s) * limbCount + 2, 0, &entry->data.load.msgQueue, NULL);
    }
}

/**
 * Requests copying all vectors from src frame table into dst frame table
 */
void AnimationContext_SetCopyAll(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMENTRY_COPYALL);

    if (entry != NULL) {
        entry->data.copy.queueFlag = sAnimQueueFlags;
        entry->data.copy.vecCount = vecCount;
        entry->data.copy.dst = dst;
        entry->data.copy.src = src;
    }
}

/**
 * Requests interpolating between base and mod frame tables with the given weight, placing the result in base
 */
void AnimationContext_SetInterp(GlobalContext* globalCtx, s32 vecCount, Vec3s* base, Vec3s* mod, f32 weight) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMENTRY_INTERP);

    if (entry != NULL) {
        entry->data.interp.queueFlag = sAnimQueueFlags;
        entry->data.interp.vecCount = vecCount;
        entry->data.interp.base = base;
        entry->data.interp.mod = mod;
        entry->data.interp.weight = weight;
    }
}

/**
 * Requests copying vectors from src frame table to dst frame table whose load flag is true
 */
void AnimationContext_SetCopyTrue(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* copyFlag) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMENTRY_COPYTRUE);

    if (entry != NULL) {
        entry->data.copy1.queueFlag = sAnimQueueFlags;
        entry->data.copy1.vecCount = vecCount;
        entry->data.copy1.dst = dst;
        entry->data.copy1.src = src;
        entry->data.copy1.copyFlag = copyFlag;
    }
}

/**
 * Requests copying vectors from src frame table to dst frame table whose load flag is false
 */
void AnimationContext_SetCopyFalse(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* copyFlag) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMENTRY_COPYFALSE);

    if (entry != NULL) {
        entry->data.copy0.queueFlag = sAnimQueueFlags;
        entry->data.copy0.vecCount = vecCount;
        entry->data.copy0.dst = dst;
        entry->data.copy0.src = src;
        entry->data.copy0.copyFlag = copyFlag;
    }
}

/**
 * Requests moving an actor according to the translation of its root limb
 */
void AnimationContext_SetMoveActor(GlobalContext* globalCtx, Actor* actor, SkelAnime* skelAnime, f32 arg3) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMENTRY_MOVEACTOR);

    if (entry != NULL) {
        entry->data.move.actor = actor;
        entry->data.move.skelAnime = skelAnime;
        entry->data.move.unk08 = arg3;
    }
}

/**
 * Receives the request for Link's animation frame data
 */
void AnimationContext_LoadFrame(GlobalContext* globalCtx, AnimationEntryData* data) {
    AnimEntryLoadFrame* entry = &data->load;

    osRecvMesg(&entry->msgQueue, NULL, OS_MESG_BLOCK);
}

/**
 * If the entry's queue is enabled, copies all vectors from src frame table to dst frame table
 */
void AnimationContext_CopyAll(GlobalContext* globalCtx, AnimationEntryData* data) {
    AnimEntryCopyAll* entry = &data->copy;

    if (!(entry->queueFlag & sDisableAnimQueueFlags)) {
        Vec3s* dst = entry->dst;
        Vec3s* src = entry->src;
        s32 i;

        for (i = 0; i < entry->vecCount; i++) {
            *dst++ = *src++;
        }
    }
}

/**
 * If the entry's queue is enabled, interpolates between the base and mod frame tables, placing the result in base
 */
void AnimationContext_Interp(GlobalContext* globalCtx, AnimationEntryData* data) {
    AnimEntryInterp* entry = &data->interp;

    if (!(entry->queueFlag & sDisableAnimQueueFlags)) {
        SkelAnime_InterpFrameTable(entry->vecCount, entry->base, entry->base, entry->mod, entry->weight);
    }
}

/**
 * If the entry's queue is enabled, copies all vectors from src frame table to dst frame table whose copy flag is true
 */
void AnimationContext_CopyTrue(GlobalContext* globalCtx, AnimationEntryData* data) {
    AnimEntryCopyTrue* entry = &data->copy1;

    if (!(entry->queueFlag & sDisableAnimQueueFlags)) {
        Vec3s* dst = entry->dst;
        Vec3s* src = entry->src;
        u8* copyFlag = entry->copyFlag;
        s32 i;

        for (i = 0; i < entry->vecCount; i++, dst++, src++) {
            if (*copyFlag++) {
                *dst = *src;
            }
        }
    }
}

/**
 * If the entry's queue is enabled, copies all vectors from src frame table to dst frame table whose copy flag is false
 */
void AnimationContext_CopyFalse(GlobalContext* globalCtx, AnimationEntryData* data) {
    AnimEntryCopyFalse* entry = &data->copy0;

    if (!(entry->queueFlag & sDisableAnimQueueFlags)) {
        Vec3s* dst = entry->dst;
        Vec3s* src = entry->src;
        u8* copyFlag = entry->copyFlag;
        s32 i;

        for (i = 0; i < entry->vecCount; i++, dst++, src++) {
            if (!(*copyFlag++)) {
                *dst = *src;
            }
        }
    }
}

/**
 * Moves an actor according to the translation of its root limb
 */
void AnimationContext_MoveActor(GlobalContext* globalCtx, AnimationEntryData* data) {
    AnimEntryMoveActor* entry = &data->move;
    Actor* actor = entry->actor;
    Vec3f diff;

    SkelAnime_UpdateTranslation(entry->skelAnime, &diff, actor->shape.rot.y);
    actor->world.pos.x += diff.x * actor->scale.x * entry->unk08;
    actor->world.pos.y += diff.y * actor->scale.y * entry->unk08;
    actor->world.pos.z += diff.z * actor->scale.z * entry->unk08;
}

/**
 * Performs all requests in the animation queue, then resets the queue flags.
 */
void AnimationContext_Update(GlobalContext* globalCtx, AnimationContext* animationCtx) {
    AnimationEntry* entry = animationCtx->entries;

    for (; animationCtx->animationCount != 0; entry++, animationCtx->animationCount--) {
        sAnimationLoadDone[entry->type](globalCtx, &entry->data);
    }

    sAnimQueueFlags = 1;
    sDisableAnimQueueFlags = 0;
}

/**
 * Initializes a skeleton to be used with Link animations to a looping animation, dynamically allocating the frame
 * tables if not given.
 */
void SkelAnime_InitLink(GlobalContext* globalCtx, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                        LinkAnimationHeader* animation, s32 flags, Vec3s* jointTable, Vec3s* morphTable,
                        s32 limbBufCount) {
    FlexSkeletonHeader* skeletonHeader;
    s32 headerJointCount;
    s32 limbCount;
    size_t allocSize;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    headerJointCount = skeletonHeader->sh.limbCount;
    skelAnime->initFlags = flags;
    limbCount = (flags & 2) ? headerJointCount : 1;

    if (flags & 1) {
        limbCount += headerJointCount;
    }

    if (flags & 4) {
        limbCount += headerJointCount;
    }

    skelAnime->limbCount = limbCount;
    skelAnime->dListCount = skeletonHeader->dListCount;
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->sh.segment);
    allocSize = sizeof(Vec3s) * limbCount;

    if (flags & 8) {
        allocSize += 2;
    }

    if (jointTable == NULL) {
        skelAnime->jointTable = ZeldaArena_Malloc(allocSize);
        skelAnime->morphTable = ZeldaArena_Malloc(allocSize);
    } else {
        skelAnime->jointTable = (Vec3s*)ALIGN16((u32)jointTable);
        skelAnime->morphTable = (Vec3s*)ALIGN16((u32)morphTable);
    }

    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f);
}

/**
 * Sets the update function of a SkelAnime that uses Link animations based on its mode
 */
void LinkAnimation_SetUpdateFunction(SkelAnime* skelAnime) {
    if (skelAnime->mode <= ANIMMODE_LOOP_INTERP) {
        skelAnime->update = LinkAnimation_Loop;
    } else {
        skelAnime->update = LinkAnimation_Once;
    }
    skelAnime->morphWeight = 0.0f;
}

/**
 * Advances the current Link animation and updates all frame tables. If the animation plays once, returns true when it
 * finishes.
 */
s32 LinkAnimation_Update(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    return skelAnime->update(globalCtx, skelAnime);
}

/**
 * Requests an interpolation between the pose in jointTable to the one in morphTable, advancing the morph but not the
 * animation frame
 */
s32 LinkAnimation_Morph(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 prevMorphWeight = skelAnime->morphWeight;
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    skelAnime->morphWeight -= skelAnime->morphRate * updateRate;
    if (skelAnime->morphWeight <= 0.0f) {
        LinkAnimation_SetUpdateFunction(skelAnime);
    }

    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->jointTable, skelAnime->morphTable,
                               1.0f - (skelAnime->morphWeight / prevMorphWeight));
    return 0;
}

/**
 * Requests a load of the next frame of a Link animation, advances the morph, and requests an interpolation between
 * jointTable and morphTable
 */
void LinkAnimation_AnimateFrame(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    AnimationContext_SetLoadFrame(globalCtx, skelAnime->animation, skelAnime->curFrame, skelAnime->limbCount,
                                  skelAnime->jointTable);
    if (skelAnime->morphWeight != 0) {
        f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;
        skelAnime->morphWeight -= skelAnime->morphRate * updateRate;
        if (skelAnime->morphWeight <= 0.0f) {
            skelAnime->morphWeight = 0.0f;
        } else {
            AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->jointTable, skelAnime->morphTable,
                                       skelAnime->morphWeight);
        }
    }
}

/**
 * Advances a Link animation that loops over its full length
 */
s32 LinkAnimation_Loop(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    skelAnime->curFrame += skelAnime->playSpeed * updateRate;
    if (skelAnime->curFrame < 0.0f) {
        skelAnime->curFrame += skelAnime->animLength;
    } else if (skelAnime->animLength <= skelAnime->curFrame) {
        skelAnime->curFrame -= skelAnime->animLength;
    }
    LinkAnimation_AnimateFrame(globalCtx, skelAnime);
    return 0;
}

/**
 * Advances a Link animation that stops at endFrame and returns true when it is reached.
 */
s32 LinkAnimation_Once(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    if (skelAnime->curFrame == skelAnime->endFrame) {
        LinkAnimation_AnimateFrame(globalCtx, skelAnime);
        return 1;
    }

    skelAnime->curFrame += skelAnime->playSpeed * updateRate;

    if (((skelAnime->curFrame - skelAnime->endFrame) * skelAnime->playSpeed) > 0.0f) {
        skelAnime->curFrame = skelAnime->endFrame;
    } else {
        if (skelAnime->curFrame < 0.0f) {
            skelAnime->curFrame += skelAnime->animLength;
        } else if (skelAnime->animLength <= skelAnime->curFrame) {
            skelAnime->curFrame -= skelAnime->animLength;
        }
    }
    LinkAnimation_AnimateFrame(globalCtx, skelAnime);
    return 0;
}

/**
 * Sets a new morph and resets the morph weight for the current animation.
 */
void Animation_SetMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 morphFrames) {
    skelAnime->morphWeight = 1.0f;
    skelAnime->morphRate = 1.0f / morphFrames;
}

/**
 * General way to set a new Link animation, allowing choice of playback speed, start frame, end frame, play mode, and
 * number of transition frames. Positive morph frames morph from the current pose to the start pose of the new
 * animation, then start the new animation. Negative morph frames start the new animation immediately, modified by the
 * pose immediately before the animation change.
 */
void LinkAnimation_Change(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation, f32 playSpeed,
                          f32 startFrame, f32 endFrame, u8 mode, f32 morphFrames) {
    skelAnime->mode = mode;
    if ((morphFrames != 0.0f) && ((animation != skelAnime->animation) || (startFrame != skelAnime->curFrame))) {
        if (morphFrames < 0) {
            LinkAnimation_SetUpdateFunction(skelAnime);
            SkelAnime_CopyFrameTable(skelAnime, skelAnime->morphTable, skelAnime->jointTable);
            morphFrames = -morphFrames;
        } else {
            skelAnime->update = LinkAnimation_Morph;
            AnimationContext_SetLoadFrame(globalCtx, animation, (s32)startFrame, skelAnime->limbCount,
                                          skelAnime->morphTable);
        }
        skelAnime->morphWeight = 1.0f;
        skelAnime->morphRate = 1.0f / morphFrames;
    } else {
        LinkAnimation_SetUpdateFunction(skelAnime);
        AnimationContext_SetLoadFrame(globalCtx, animation, (s32)startFrame, skelAnime->limbCount,
                                      skelAnime->jointTable);
        skelAnime->morphWeight = 0.0f;
    }

    skelAnime->animation = animation;
    skelAnime->curFrame = 0.0f;
    skelAnime->startFrame = startFrame;
    skelAnime->curFrame = startFrame;
    skelAnime->endFrame = endFrame;
    skelAnime->animLength = Animation_GetLength(animation);
    skelAnime->playSpeed = playSpeed;
}

/**
 * Immediately changes to a Link animation that plays once at the default speed.
 */
void LinkAnimation_PlayOnce(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f, Animation_GetLastFrame(&animation->common),
                         ANIMMODE_ONCE, 0.0f);
}

/**
 * Immediately changes to a Link animation that plays once at the specified speed.
 */
void LinkAnimation_PlayOnceSetSpeed(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                                    f32 playSpeed) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, playSpeed, 0.0f, Animation_GetLastFrame(&animation->common),
                         ANIMMODE_ONCE, 0.0f);
}

/**
 * Immediately changes to a Link animation that loops at the default speed.
 */
void LinkAnimation_PlayLoop(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f, Animation_GetLastFrame(&animation->common),
                         ANIMMODE_LOOP, 0.0f);
}

/**
 * Immediately changes to a Link animation that loops at the specified speed.
 */
void LinkAnimation_PlayLoopSetSpeed(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                                    f32 playSpeed) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, playSpeed, 0.0f, Animation_GetLastFrame(&animation->common),
                         ANIMMODE_LOOP, 0.0f);
}

/**
 * Requests copying jointTable to morphTable
 */
void LinkAnimation_CopyJointToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    AnimationContext_SetCopyAll(globalCtx, skelAnime->limbCount, skelAnime->morphTable, skelAnime->jointTable);
}

/**
 * Requests copying morphTable to jointTable
 */
void LinkAnimation_CopyMorphToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    AnimationContext_SetCopyAll(globalCtx, skelAnime->limbCount, skelAnime->jointTable, skelAnime->morphTable);
}

/**
 * Requests loading frame data from the Link animation into morphTable
 */
void LinkAnimation_LoadToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                               f32 frame) {
    AnimationContext_SetLoadFrame(globalCtx, animation, (s32)frame, skelAnime->limbCount, skelAnime->morphTable);
}

/**
 * Requests loading frame data from the Link animation into jointTable
 */
void LinkAnimation_LoadToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                               f32 frame) {
    AnimationContext_SetLoadFrame(globalCtx, animation, (s32)frame, skelAnime->limbCount, skelAnime->jointTable);
}

/**
 * Requests interpolating between jointTable and morphTable, placing the result in jointTable
 */
void LinkAnimation_InterpJointMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 weight) {
    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->jointTable, skelAnime->morphTable, weight);
}

/**
 * Requests loading frame data from the Link animations and blending them, placing the result in jointTable
 */
void LinkAnimation_BlendToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation1,
                                f32 frame1, LinkAnimationHeader* animation2, f32 frame2, f32 blendWeight,
                                Vec3s* blendTable) {
    Vec3s* alignedBlendTable;

    AnimationContext_SetLoadFrame(globalCtx, animation1, (s32)frame1, skelAnime->limbCount, skelAnime->jointTable);

    alignedBlendTable = (Vec3s*)ALIGN16((u32)blendTable);

    AnimationContext_SetLoadFrame(globalCtx, animation2, (s32)frame2, skelAnime->limbCount, alignedBlendTable);
    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->jointTable, alignedBlendTable, blendWeight);
}

/**
 * Requests loading frame data from the Link animations and blending them, placing the result in morphTable
 */
void LinkAnimation_BlendToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation1,
                                f32 frame1, LinkAnimationHeader* animation2, f32 frame2, f32 blendWeight,
                                Vec3s* blendTable) {
    Vec3s* alignedBlendTable;

    AnimationContext_SetLoadFrame(globalCtx, animation1, (s32)frame1, skelAnime->limbCount, skelAnime->morphTable);

    alignedBlendTable = (Vec3s*)ALIGN16((u32)blendTable);

    AnimationContext_SetLoadFrame(globalCtx, animation2, (s32)frame2, skelAnime->limbCount, alignedBlendTable);
    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->morphTable, alignedBlendTable, blendWeight);
}

/**
 * Changes a looping animation to one that stops at the end.
 */
void LinkAnimation_EndLoop(SkelAnime* skelAnime) {
    skelAnime->mode = ANIMMODE_ONCE;
    LinkAnimation_SetUpdateFunction(skelAnime);
}

/**
 * Checks if the current frame is after frame and the previous frame was before it.
 */
s32 Animation_OnFrameImpl(SkelAnime* skelAnime, f32 frame, f32 updateRate) {
    f32 updateSpeed;
    f32 curFrameDiff;
    f32 nextFrame;

    updateSpeed = skelAnime->playSpeed * updateRate;
    nextFrame = skelAnime->curFrame - updateSpeed;
    if (nextFrame < 0.0f) {
        nextFrame += skelAnime->animLength;
    } else if (skelAnime->animLength <= nextFrame) {
        nextFrame -= skelAnime->animLength;
    }

    if ((frame == 0.0f) && (updateSpeed > 0.0f)) {
        frame = skelAnime->animLength;
    }

    curFrameDiff = (nextFrame + updateSpeed) - frame;
    if ((0.0f <= (curFrameDiff * updateSpeed)) && (((curFrameDiff - updateSpeed) * updateSpeed) < 0.0f)) {
        return true;
    }
    return false;
}

/**
 * Checks if the current Link animation has reached the specified frame
 */
s32 LinkAnimation_OnFrame(SkelAnime* skelAnime, f32 frame) {
    f32 updateRate = gFramerateDivisorHalf;

    return Animation_OnFrameImpl(skelAnime, frame, updateRate);
}

/**
 * Initializes a normal skeleton to a looping animation, dynamically allocating the frame tables if not provided.
 */
void SkelAnime_Init(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                    AnimationHeader* animation, Vec3s* jointTable, Vec3s* morphTable, s32 limbCount) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->segment);
    if (jointTable == NULL) {
        skelAnime->jointTable = ZeldaArena_Malloc(sizeof(*skelAnime->jointTable) * skelAnime->limbCount);
        skelAnime->morphTable = ZeldaArena_Malloc(sizeof(*skelAnime->morphTable) * skelAnime->limbCount);
    } else {
        skelAnime->jointTable = jointTable;
        skelAnime->morphTable = morphTable;
    }

    if (animation != NULL) {
        Animation_PlayLoop(skelAnime, animation);
    }
}

/**
 * Initializes a flex skeleton to a looping animation, dynamically allocating the frame tables if not given.
 */
void SkelAnime_InitFlex(GlobalContext* globalCtx, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animation, Vec3s* jointTable, Vec3s* morphTable, s32 limbCount) {
    FlexSkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->sh.limbCount + 1;
    skelAnime->dListCount = skeletonHeader->dListCount;
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->sh.segment);

    if (jointTable == NULL) {
        skelAnime->jointTable = ZeldaArena_Malloc(sizeof(*skelAnime->jointTable) * skelAnime->limbCount);

        skelAnime->morphTable = ZeldaArena_Malloc(sizeof(*skelAnime->morphTable) * skelAnime->limbCount);
    } else {
        skelAnime->jointTable = jointTable;
        skelAnime->morphTable = morphTable;
    }

    if (animation != NULL) {
        Animation_PlayLoop(skelAnime, animation);
    }
}

/**
 * Initializes a skeleton with SkinLimbs to a looping animation, dynamically allocating the frame tables.
 */
void SkelAnime_InitSkin(GameState* gameState, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animation) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->segment);
    skelAnime->jointTable = ZeldaArena_Malloc(sizeof(*skelAnime->jointTable) * skelAnime->limbCount);
    skelAnime->morphTable = ZeldaArena_Malloc(sizeof(*skelAnime->morphTable) * skelAnime->limbCount);

    // Debug prints here, required to match.
    if (1) {};

    if (animation != NULL) {
        Animation_PlayLoop(skelAnime, animation);
    }
}

/**
 * Sets the SkelAnime's update function based on its current mode.
 */
void SkelAnime_SetUpdate(SkelAnime* skelAnime) {
    if (skelAnime->mode <= ANIMMODE_LOOP_INTERP) {
        skelAnime->update = SkelAnime_LoopFull;
    } else if (skelAnime->mode <= ANIMMODE_ONCE_INTERP) {
        skelAnime->update = SkelAnime_Once;
    } else {
        skelAnime->update = SkelAnime_LoopPartial;
    }
}

/**
 * Advances the current animation and updates all frame tables. If the animation plays once, returns true when it
 * finishes.
 */
s32 SkelAnime_Update(SkelAnime* skelAnime) {
    return skelAnime->update(skelAnime);
}

/**
 * Morphs from the pose in jointTable to the one in morphTable, advancing the morph but not the animation frame
 */
s32 SkelAnime_Morph(SkelAnime* skelAnime) {
    f32 prevMorphWeight = skelAnime->morphWeight;
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->morphWeight -= skelAnime->morphRate * updateRate;
    if (skelAnime->morphWeight <= 0.0f) {
        SkelAnime_SetUpdate(skelAnime);
        skelAnime->morphWeight = 0.0f;
    }
    SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->jointTable, skelAnime->jointTable,
                               skelAnime->morphTable, 1.0f - (skelAnime->morphWeight / prevMorphWeight));
    return 0;
}

/**
 * Performs a tapered morph from the pose in jointTable to the one in morphTable, advancing the morph but not the
 * animation frame
 */
s32 SkelAnime_MorphTaper(SkelAnime* skelAnime) {
    s16 prevPhase = skelAnime->morphWeight * 0x4000;
    s16 curPhase;
    f32 prevWeight;
    f32 curWeight;
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->morphWeight -= skelAnime->morphRate * updateRate;
    if (skelAnime->morphWeight <= 0.0f) {
        SkelAnime_SetUpdate(skelAnime);
        skelAnime->morphWeight = 0.0f;
    }
    curPhase = skelAnime->morphWeight * 0x4000;
    if (skelAnime->taper < 0) {
        prevWeight = 1.0f - Math_CosS(prevPhase);
        curWeight = 1.0f - Math_CosS(curPhase);
    } else {
        prevWeight = Math_SinS(prevPhase);
        curWeight = Math_SinS(curPhase);
    }
    if (curWeight != 0.0f) {
        curWeight /= prevWeight;
    } else {
        curWeight = 0.0f;
    }
    SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->jointTable, skelAnime->jointTable,
                               skelAnime->morphTable, 1.0f - curWeight);
    return 0;
}

/**
 * Gets frame data for the current frame as modified by morphTable and advances the morph
 */
void SkelAnime_AnimateFrame(SkelAnime* skelAnime) {
    Vec3s nextjointTable[100];

    SkelAnime_GetFrameData(skelAnime->animation, skelAnime->curFrame, skelAnime->limbCount, skelAnime->jointTable);
    if (skelAnime->mode & ANIM_INTERP) {
        s32 frame = skelAnime->curFrame;
        f32 partialFrame = skelAnime->curFrame - frame;

        if (++frame >= (s32)skelAnime->animLength) {
            frame = 0;
        }
        SkelAnime_GetFrameData(skelAnime->animation, frame, skelAnime->limbCount, nextjointTable);
        SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->jointTable, skelAnime->jointTable, nextjointTable,
                                   partialFrame);
    }
    if (skelAnime->morphWeight != 0) {
        f32 updateRate = gFramerateDivisorThird;

        skelAnime->morphWeight -= skelAnime->morphRate * updateRate;
        if (skelAnime->morphWeight <= 0.0f) {
            skelAnime->morphWeight = 0.0f;
        } else {
            SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->jointTable, skelAnime->jointTable,
                                       skelAnime->morphTable, skelAnime->morphWeight);
        }
    }
}
/**
 * Advances an animation that loops over its full length and updates the frame tables
 */
s32 SkelAnime_LoopFull(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->curFrame += skelAnime->playSpeed * updateRate;
    if (skelAnime->curFrame < 0.0f) {
        skelAnime->curFrame += skelAnime->animLength;
    } else if (skelAnime->animLength <= skelAnime->curFrame) {
        skelAnime->curFrame -= skelAnime->animLength;
    }

    SkelAnime_AnimateFrame(skelAnime);
    return 0;
}

/**
 * Advances an animation that loops over part of its length and updates the frame tables
 */
s32 SkelAnime_LoopPartial(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->curFrame += skelAnime->playSpeed * updateRate;
    if (skelAnime->curFrame < skelAnime->startFrame) {
        skelAnime->curFrame = (skelAnime->curFrame - skelAnime->startFrame) + skelAnime->endFrame;
    } else if (skelAnime->endFrame <= skelAnime->curFrame) {
        skelAnime->curFrame = (skelAnime->curFrame - skelAnime->endFrame) + skelAnime->startFrame;
    }

    SkelAnime_AnimateFrame(skelAnime);
    return 0;
}

/**
 * Advances an animation that stops at endFrame and returns true when it is reached.
 */
s32 SkelAnime_Once(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    if (skelAnime->curFrame == skelAnime->endFrame) {
        SkelAnime_GetFrameData(skelAnime->animation, skelAnime->curFrame, skelAnime->limbCount, skelAnime->jointTable);
        SkelAnime_AnimateFrame(skelAnime);
        return 1;
    }

    skelAnime->curFrame += skelAnime->playSpeed * updateRate;
    if (((skelAnime->curFrame - skelAnime->endFrame) * skelAnime->playSpeed) > 0.0f) {
        skelAnime->curFrame = skelAnime->endFrame;
    } else {
        if (skelAnime->curFrame < 0.0f) {
            skelAnime->curFrame += skelAnime->animLength;
        } else {
            if (skelAnime->animLength <= skelAnime->curFrame) {
                skelAnime->curFrame -= skelAnime->animLength;
            }
        }
    }
    SkelAnime_AnimateFrame(skelAnime);
    return 0;
}

/**
 * Fully general way to set a new animation, allowing choice of playback speed, start frame, end frame, play mode,
 * number of transition frames, and tapering of the transition. Positive morph frames morph from the current pose to the
 * start pose of the new animation, then start the new animation. Negative morph frames start the new animation
 * immediately, modified by the pose immediately before the animation change.
 */
void Animation_ChangeImpl(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame, f32 endFrame,
                          u8 mode, f32 morphFrames, s8 taper) {
    skelAnime->mode = mode;
    if ((morphFrames != 0.0f) && ((animation != skelAnime->animation) || (startFrame != skelAnime->curFrame))) {
        if (morphFrames < 0) {
            SkelAnime_SetUpdate(skelAnime);
            SkelAnime_CopyFrameTable(skelAnime, skelAnime->morphTable, skelAnime->jointTable);
            morphFrames = -morphFrames;
        } else {
            if (taper != ANIMTAPER_NONE) {
                skelAnime->update = SkelAnime_MorphTaper;
                skelAnime->taper = taper;
            } else {
                skelAnime->update = SkelAnime_Morph;
            }
            SkelAnime_GetFrameData(animation, startFrame, skelAnime->limbCount, skelAnime->morphTable);
        }
        skelAnime->morphWeight = 1.0f;
        skelAnime->morphRate = 1.0f / morphFrames;
    } else {
        SkelAnime_SetUpdate(skelAnime);
        SkelAnime_GetFrameData(animation, startFrame, skelAnime->limbCount, skelAnime->jointTable);
        skelAnime->morphWeight = 0.0f;
    }

    skelAnime->animation = animation;
    skelAnime->startFrame = startFrame;
    skelAnime->endFrame = endFrame;
    skelAnime->animLength = Animation_GetLength(&animation->common);
    if (skelAnime->mode >= ANIMMODE_LOOP_PARTIAL) {
        skelAnime->curFrame = 0.0f;
    } else {
        skelAnime->curFrame = startFrame;
        if (skelAnime->mode <= ANIMMODE_LOOP_INTERP) {
            skelAnime->endFrame = skelAnime->animLength - 1.0f;
        }
    }
    skelAnime->playSpeed = playSpeed;
}

/**
 * General way to set a new animation, allowing choice of playback speed, start frame, end frame, play mode, and number
 * of transition frames. Positive morph frames morph from the current pose to the start pose of the new animation, then
 * start the new animation. Negative morph frames start the new animation immediately, modified by the pose immediately
 * before the animation change.
 */
void Animation_Change(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame, f32 endFrame,
                      u8 mode, f32 morphFrames) {
    Animation_ChangeImpl(skelAnime, animation, playSpeed, startFrame, endFrame, mode, morphFrames, ANIMTAPER_NONE);
}

/**
 * Immediately changes to an animation that plays once at the default speed.
 */
void Animation_PlayOnce(SkelAnime* skelAnime, AnimationHeader* animation) {
    Animation_Change(skelAnime, animation, 1.0f, 0.0f, Animation_GetLastFrame(&animation->common), ANIMMODE_ONCE, 0.0f);
}

/**
 * Smoothly transitions to an animation that plays once at the default speed.
 * Positive morph frames morph from the current pose to the start pose of the new animation, then start the new
 * animation. Negative morph frames start the new animation immediately, modified by the pose immediately before the
 * animation change.
 */
void Animation_MorphToPlayOnce(SkelAnime* skelAnime, AnimationHeader* animation, f32 morphFrames) {
    Animation_Change(skelAnime, animation, 1.0f, 0, Animation_GetLastFrame(&animation->common), ANIMMODE_ONCE,
                     morphFrames);
}

/**
 * Immediately changes to an animation that plays once at the specified speed.
 */
void Animation_PlayOnceSetSpeed(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed) {
    Animation_Change(skelAnime, animation, playSpeed, 0.0f, Animation_GetLastFrame(&animation->common), ANIMMODE_ONCE,
                     0.0f);
}

/**
 * Immediately changes to an animation that loops at the default.
 */
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animation) {
    Animation_Change(skelAnime, animation, 1.0f, 0.0f, Animation_GetLastFrame(&animation->common), ANIMMODE_LOOP, 0.0f);
}

/**
 * Smoothly transitions to a looping animation, specifying the number of frames for the transition.
 * Positive morph frames morph from the current pose to the start pose of the new animation, then start the new
 * animation. Negative morph frames start the new animation immediately, modified by the pose immediately before the
 * animation change.
 */
void Animation_MorphToLoop(SkelAnime* skelAnime, AnimationHeader* animation, f32 morphFrames) {
    Animation_Change(skelAnime, animation, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, morphFrames);
}

/**
 * Immediately changes to an animation that loops at the specified speed.
 */
void Animation_PlayLoopSetSpeed(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed) {
    Animation_Change(skelAnime, animation, playSpeed, 0.0f, Animation_GetLastFrame(&animation->common), ANIMMODE_LOOP,
                     0.0f);
}

/**
 * Changes a looping animation to one that stops at the end. Unused
 */
void Animation_EndLoop(SkelAnime* skelAnime) {
    skelAnime->mode = ANIMMODE_ONCE;
    skelAnime->endFrame = skelAnime->animLength;
    SkelAnime_SetUpdate(skelAnime);
}

/**
 * Reverses the current animation.
 */
void Animation_Reverse(SkelAnime* skelAnime) {
    f32 startFrame = skelAnime->startFrame;

    skelAnime->startFrame = skelAnime->endFrame;
    skelAnime->playSpeed = -skelAnime->playSpeed;
    skelAnime->endFrame = startFrame;
}

/**
 * Copies the src frame table to the dst frame table if copyFlag for that limb is true.
 */
void SkelAnime_CopyFrameTableTrue(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* copyFlag) {
    s32 i;

    for (i = 0; i < skelAnime->limbCount; i++, dst++, src++) {
        if (*copyFlag++) {
            *dst = *src;
        }
    }
}

/**
 * Copies the src frame table to the dst frame table if copyFlag for that limb is false.
 */
void SkelAnime_CopyFrameTableFalse(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* copyFlag) {
    s32 i;

    for (i = 0; i < skelAnime->limbCount; i++, dst++, src++) {
        if (!*copyFlag++) {
            *dst = *src;
        }
    }
}

/**
 * Updates translation of the root limb and calculates `pos`, the difference between
 * the old and new positions of the root limb as rotated by `angle`. Used to allow
 * animations to change an actor's position.
 */
void SkelAnime_UpdateTranslation(SkelAnime* skelAnime, Vec3f* diff, s16 angle) {
    f32 x;
    f32 z;
    f32 sin;
    f32 cos;

    if (skelAnime->moveFlags & ANIM_FLAG_NOMOVE) {
        diff->z = 0.0f;
        diff->x = 0.0f;
    } else {
        // `angle` rotation around y axis.
        x = skelAnime->jointTable->x - skelAnime->prevTransl.x;
        z = skelAnime->jointTable->z - skelAnime->prevTransl.z;
        sin = Math_SinS(angle);
        cos = Math_CosS(angle);
        diff->x = x * cos + z * sin;
        diff->z = z * cos - x * sin;
    }

    skelAnime->prevTransl.x = skelAnime->jointTable->x;
    skelAnime->jointTable->x = skelAnime->baseTransl.x;
    skelAnime->prevTransl.z = skelAnime->jointTable->z;
    skelAnime->jointTable->z = skelAnime->baseTransl.z;
    if (skelAnime->moveFlags & ANIM_FLAG_UPDATEY) {
        if (skelAnime->moveFlags & ANIM_FLAG_NOMOVE) {
            diff->y = 0.0f;
        } else {
            diff->y = skelAnime->jointTable->y - skelAnime->prevTransl.y;
        }
        skelAnime->prevTransl.y = skelAnime->jointTable->y;
        skelAnime->jointTable->y = skelAnime->baseTransl.y;
    } else {
        diff->y = 0.0f;
        skelAnime->prevTransl.y = skelAnime->jointTable->y;
    }
    skelAnime->moveFlags &= ~ANIM_FLAG_NOMOVE;
}

/**
 * Checks if the current animation is at the specified frame
 */
s32 Animation_OnFrame(SkelAnime* skelAnime, f32 frame) {
    return Animation_OnFrameImpl(skelAnime, frame, 1.0f);
}

/**
 * Frees the frame tables for a skelAnime with dynamically allocated tables.
 */
void SkelAnime_Free(SkelAnime* skelAnime, GlobalContext* globalCtx) {
    if (skelAnime->jointTable != NULL) {
        ZeldaArena_Free(skelAnime->jointTable);
    }

    if (skelAnime->morphTable != NULL) {
        ZeldaArena_Free(skelAnime->morphTable);
    }
}

/**
 * Copies the src frame table to the dst frame table.
 */
void SkelAnime_CopyFrameTable(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src) {
    bcopy(src, dst, sizeof(Vec3s) * skelAnime->limbCount);
}
