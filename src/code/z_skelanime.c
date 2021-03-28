#include <ultra64.h>
#include <global.h>

s32 LinkAnimation_Loop(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 LinkAnimation_Once(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 SkelAnime_LoopFull(SkelAnime* skelAnime);
s32 SkelAnime_LoopPartial(SkelAnime* skelAnime);
s32 SkelAnime_Once(SkelAnime* skelAnime);
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_UpdateTranslation(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
void LinkAnimation_Change(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimetionEntrySeg,
                              f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationMode, f32 transitionRate);
void SkelAnime_CopyFrameTable(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);

static AnimationEntryCallback sAnimationLoadDone[] = {
    AnimationContext_LoadFrame,  AnimationContext_CopyAll, AnimationContext_Interp,
    AnimationContext_CopyTrue, AnimationContext_CopyFalse, AnimationContext_MoveActor,
};

s32 sAnimQueueFlags;
s32 sDisableAnimQueueFlags;

/*
 * Draws the limb at `limbIndex` with a level of detail display lists index by `dListIndex`
 */
void SkelAnime_DrawLimbLod(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg, s32 lod) {
    LodLimb* limb;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    
    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Push();
    limb = (LodLimb *)Lib_PtrSegToVirt(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];

    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    dList = limb->dLists[lod];
    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, arg) == 0)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);

            gSPDisplayList(polyTemp + 1, dList);
            POLY_OPA_DISP = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, arg);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawLimbLod(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw,
                              postLimbDraw, arg, lod);
    }

    Matrix_Pop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawLimbLod(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw,
                              postLimbDraw, arg, lod);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw all limbs of type `LodLimb` in a given skeleton
 * Near or far display list is specified via `lod`
 */
void SkelAnime_DrawLod(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable,
                       OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg, s32 lod) {
    LodLimb* rootLimb;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Push();

    rootLimb = (LodLimb *)Lib_PtrSegToVirt(skeleton[0]);
    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];
    dList = rootLimb->dLists[lod];

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, arg)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);

            gSPDisplayList(polyTemp + 1, dList);

            POLY_OPA_DISP = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, arg);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawLimbLod(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                              postLimbDraw, arg, lod);
    }

    Matrix_Pop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw a limb of type `LodLimb` contained within a flexible skeleton
 * Near or far display list is specified via `lod`
 */
void SkelAnime_DrawFlexLimbLod(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                             OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, void* arg,
                             s32 lod, Mtx** mtx) {
    LodLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Push();

    limb = (LodLimb *)Lib_PtrSegToVirt(skeleton[limbIndex]);
    limbIndex++;

    rot = jointTable[limbIndex];

    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;
    
    newDList = limbDList = limb->dLists[lod];

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, arg)) {
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
        postLimbDraw(globalCtx, limbIndex, &newDList, &limbDList, &rot, arg);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbLod(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw,
                                postLimbDraw, arg, lod, mtx);
    }

    Matrix_Pop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawFlexLimbLod(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw,
                                postLimbDraw, arg, lod, mtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draws all limbs of type `LodLimb` in a given flexible skeleton
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 */
void SkelAnime_DrawFlexLod(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                         OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, void* arg,
                         s32 lod) {
    LodLimb* rootLimb;
    s32 pad;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    Mtx* mtx = (Mtx *)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0xD, mtx);
    Matrix_Push();

    rootLimb = (LodLimb *)Lib_PtrSegToVirt(skeleton[0]);
    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];

    newDList = limbDList = rootLimb->dLists[lod];

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, arg)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, newDList);
            POLY_OPA_DISP = polyTemp + 2;
            mtx++;
        } else if (limbDList != NULL) {
            Matrix_ToMtx(mtx);
            mtx++;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &newDList, &limbDList, &rot, arg);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbLod(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                                postLimbDraw, arg, lod, &mtx);
    }

    Matrix_Pop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/*
 * Draws the limb of the Skeleton `skeleton` at `limbIndex`
 */
void SkelAnime_DrawLimbOpa(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                        OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg) {
    StandardLimb* limb;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    
    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Push();

    limb = (StandardLimb *)Lib_PtrSegToVirt(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];
    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;
    dList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, arg)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList);
            POLY_OPA_DISP = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, arg);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw,
                           postLimbDraw, arg);
    }

    Matrix_Pop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                           arg);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw all limbs of type `StandardLimb` in a given skeleton to the polyOpa buffer
 */
void SkelAnime_DrawOpa(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable,
                    OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Push();
    rootLimb = Lib_PtrSegToVirt(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];
    dList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, arg)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList);
            POLY_OPA_DISP = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, arg);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                           postLimbDraw, arg);
    }

    Matrix_Pop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void SkelAnime_DrawFlexLimbOpa(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                          OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg,
                          Mtx** limbMatricies) {
    StandardLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    
    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Push();

    limb = Lib_PtrSegToVirt(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];

    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    newDList = limbDList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, arg)) {
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
        postLimbDraw(globalCtx, limbIndex, &limbDList, &rot, arg);
    }

    if (limb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw,
                             postLimbDraw, arg, limbMatricies);
    }

    Matrix_Pop();

    if (limb->sibling != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw,
                             postLimbDraw, arg, limbMatricies);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Draw all limbs of type `StandardLimb` in a given flexible skeleton to the polyOpa buffer
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 */
void SkelAnime_DrawFlexOpa(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                      OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, void* arg) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    Mtx* mtx = (Mtx *)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    if (skeleton == NULL) {
        return;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0xD, mtx);

    Matrix_Push();

    rootLimb = Lib_PtrSegToVirt(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;
    rot = jointTable[1];

    newDList = limbDList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, arg)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, newDList);
            POLY_OPA_DISP = polyTemp + 2;
            mtx++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(mtx);
                mtx++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &limbDList, &rot, arg);
    }

    if (rootLimb->child != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                             postLimbDraw, arg, &mtx);
    }

    Matrix_Pop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80134148(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                   OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, UnkActorDraw unkDraw, void* arg,
                   Mtx** mtx) {
    StandardLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;
    
    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_Push();

    limb = (StandardLimb *)Lib_PtrSegToVirt(skeleton[limbIndex]);
    limbIndex++;

    rot = jointTable[limbIndex];
    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    newDList = limbDList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, arg)) {
        Matrix_JointPosition(&pos, &rot);
        Matrix_Push();
        unkDraw(globalCtx, limbIndex, arg);
        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_ToMtx(*mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, newDList);
            POLY_OPA_DISP = polyTemp + 2;
            (*mtx)++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(*mtx);
                (*mtx)++;
            }
        }
        Matrix_Pop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &limbDList, &rot, arg);
    }

    if (limb->child != LIMB_DONE) {
        func_80134148(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, arg, mtx);
    }

    Matrix_Pop();

    if (limb->sibling != LIMB_DONE) {
        func_80134148(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, arg, mtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_801343C0(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                   OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, UnkActorDraw unkDraw, void* arg) {
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

    mtx = (Mtx*)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    gSPSegment(POLY_OPA_DISP++, 0xD, mtx);

    Matrix_Push();

    rootLimb = (StandardLimb *)Lib_PtrSegToVirt(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;
    rot = jointTable[1];

    newDList = limbDList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, arg)) {
        Matrix_JointPosition(&pos, &rot);
        Matrix_Push();
        unkDraw(globalCtx, 1, arg);
        if (newDList != NULL) {
            Gfx* polyTemp = POLY_OPA_DISP;

            gSPMatrix(polyTemp, Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, newDList);
            POLY_OPA_DISP = polyTemp + 2;
            mtx++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(mtx++);
            }
        }
        Matrix_Pop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &limbDList, &rot, arg);
    }

    if (rootLimb->child != LIMB_DONE) {
        func_80134148(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, arg, &mtx);
    }

    Matrix_Pop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Copies frame data from the frame data table, indexed by the joint index table.
 * Indices below staticIndexMax are copied from that entry in the static frame data table.
 * Indices above staticIndexMax are offsets to a frame data array indexed by the frame.
 */
void SkelAnime_GetFrameData(AnimationHeader* animation, s32 frame, s32 limbCount, Vec3s* frameTable) {
    AnimationHeader* animHeader = Lib_PtrSegToVirt(animation);
    JointIndex* jointIndices = Lib_PtrSegToVirt(animHeader->jointIndices);
    s16* frameData = Lib_PtrSegToVirt(animHeader->frameData);
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
    AnimationHeaderCommon* common = Lib_PtrSegToVirt(animation);

    return common->frameCount;
}

s16 Animation_GetLastFrame(void* animation) {
    AnimationHeaderCommon* common = Lib_PtrSegToVirt(animation);

    return (u16)common->frameCount - 1;
}

/*
 * Draws the Skeleton `skeleton`'s limb at index `limbIndex`.  Appends all generated graphics commands to
 * `gfx`.  Returns a pointer to the next gfx to be appended to.
 */
Gfx* SkelAnime_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                         OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, void* arg, Gfx* gfx) {
    StandardLimb* limb;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    Matrix_Push();

    limb = (StandardLimb *)Lib_PtrSegToVirt(skeleton[limbIndex]);
    limbIndex++;

    rot = jointTable[limbIndex];
    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    dList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, arg, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            gSPMatrix(gfx, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList);
            gfx = gfx + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, arg, &gfx);
    }

    if (limb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw,
                                  postLimbDraw, arg, gfx);
    }

    Matrix_Pop();

    if (limb->sibling != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw,
                                  postLimbDraw, arg, gfx);
    }

    return gfx;
}

/*
 * Draws the Skeleton `skeleton`  Appends all generated graphics to `gfx`, and returns a pointer to the
 * next gfx to be appended to.
 */
Gfx* SkelAnime_Draw(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable,
                     OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, void* arg, Gfx* gfx) {
    StandardLimb* rootLimb;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return NULL;
    }

    Matrix_Push();

    rootLimb = (StandardLimb *)Lib_PtrSegToVirt(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];

    dList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, arg, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        if (dList != NULL) {
            gSPMatrix(gfx, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList);
            gfx = gfx + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, arg, &gfx);
    }

    if (rootLimb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                                  postLimbDraw, arg, gfx);
    }

    Matrix_Pop();

    return gfx;
}

/**
 * Draw a limb of type `StandardLimb` contained within a flexible skeleton to the specified display buffer
 */
Gfx* SkelAnime_DrawFlexLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                           OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, void* arg,
                           Mtx** mtx, Gfx* gfx) {
    StandardLimb* limb;
    Gfx* newDList;
    Gfx* limbDList;
    Vec3f pos;
    Vec3s rot;

    Matrix_Push();

    limb = (StandardLimb *)Lib_PtrSegToVirt(skeleton[limbIndex]);
    limbIndex++;
    rot = jointTable[limbIndex];

    pos.x = limb->jointPos.x;
    pos.y = limb->jointPos.y;
    pos.z = limb->jointPos.z;

    newDList = limbDList = limb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, limbIndex, &newDList, &pos, &rot, arg, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            gSPMatrix(gfx, Matrix_ToMtx(*mtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, newDList);
            gfx = gfx + 2;
            (*mtx)++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(*mtx);
                (*mtx)++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &limbDList, &rot, arg, &gfx);
    }

    if (limb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, limb->child, skeleton, jointTable, overrideLimbDraw,
                                    postLimbDraw, arg, mtx, gfx);
    }

    Matrix_Pop();

    if (limb->sibling != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, limb->sibling, skeleton, jointTable, overrideLimbDraw,
                                    postLimbDraw, arg, mtx, gfx);
    }

    return gfx;
}

/**
 * Draw all limbs of type `StandardLimb` in a given flexible skeleton to the specified display buffer
 * Limbs in a flexible skeleton have meshes that can stretch to line up with other limbs.
 * An array of matrices is dynamically allocated so each limb can access any transform to ensure its meshes line up.
 */
Gfx* SkelAnime_DrawFlex(GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount,
                       OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, void* arg, Gfx* gfx) {
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

    mtx = (Mtx*)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(Mtx) * dListCount));

    gSPSegment(gfx++, 0xD, mtx);

    Matrix_Push();

    rootLimb = Lib_PtrSegToVirt(skeleton[0]);

    pos.x = jointTable[0].x;
    pos.y = jointTable[0].y;
    pos.z = jointTable[0].z;

    rot = jointTable[1];

    newDList = limbDList = rootLimb->dList;

    if ((overrideLimbDraw == NULL) || !overrideLimbDraw(globalCtx, 1, &newDList, &pos, &rot, arg, &gfx)) {
        Matrix_JointPosition(&pos, &rot);
        if (newDList != NULL) {
            gSPMatrix(gfx, Matrix_ToMtx(mtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, newDList);
            gfx = gfx + 2;
            mtx++;
        } else {
            if (limbDList != NULL) {
                Matrix_ToMtx(mtx);
                mtx++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &limbDList, &rot, arg, &gfx);
    }

    if (rootLimb->child != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, rootLimb->child, skeleton, jointTable, overrideLimbDraw,
                                    postLimbDraw, arg, &mtx, gfx);
    }

    Matrix_Pop();

    return gfx;
}

/**
 * Unpacks frame data for the animation at the given frame into frameTable
 * Used by the legacy animation format
 */
#ifdef NON_MATCHING
// equivalent, minor reordering
s16 SkelAnime_GetFrameData2(LegacyAnimationHeader* animation, s32 frame, Vec3s* frameTable) {
    LegacyAnimationHeader* animHeader = Lib_PtrSegToVirt(animation);
    s16 limbCount = animHeader->limbCount;
    JointKey* key = Lib_PtrSegToVirt(animHeader->jointKey);
    s16* frameData = Lib_PtrSegToVirt(animHeader->frameData);
    s16* staticData = &frameData[0];
    s16* dynamicData = &frameData[frame];
    s32 i;

    /**
     *Equivalent to the following, but the compiler optimizes the loop in a way I can't replicate
     */
/*
     for(i = 0, frameTable++, key++; i < limbCount + 1; i++, key++, frameTable++) {
         frameTable->x = frame < key->xMax ? dynamicData[key->x] : staticData[key->x];
         frameTable->y = frame < key->yMax ? dynamicData[key->y] : staticData[key->y];
         frameTable->z = frame < key->zMax ? dynamicData[key->z] : staticData[key->z];
     }
*/
    frameTable->x = frame < key->xMax ? dynamicData[key->x] : staticData[key->x];
    frameTable->y = frame < key->yMax ? dynamicData[key->y] : staticData[key->y];
    frameTable->z = frame < key->zMax ? dynamicData[key->z] : staticData[key->z];

    i = 1;
    frameTable++;
    key++;

    if (limbCount & 1) {}

    if (limbCount > 0) {
        if (limbCount & 1) {
            i++;
            frameTable->x = frame < key->xMax ? dynamicData[key->x] : staticData[key->x];
            frameTable->y = frame < key->yMax ? dynamicData[key->y] : staticData[key->y];
            frameTable->z = frame < key->zMax ? dynamicData[key->z] : staticData[key->z];
            key++;
            frameTable++;
            if (limbCount + 1 == i) {
                goto ret;
            }
        }
        do {
            i += 2;
            frameTable->x = frame < key->xMax ? dynamicData[key->x] : staticData[key->x];
            frameTable->y = frame < key->yMax ? dynamicData[key->y] : staticData[key->y];
            frameTable->z = frame < key->zMax ? dynamicData[key->z] : staticData[key->z];
            key++;
            frameTable++;
            frameTable->x = frame < key->xMax ? dynamicData[key->x] : staticData[key->x];
            frameTable->y = frame < key->yMax ? dynamicData[key->y] : staticData[key->y];
            frameTable->z = frame < key->zMax ? dynamicData[key->z] : staticData[key->z];
            key++;
            frameTable++;
        } while (i != limbCount + 1);
    }
    
ret:
    return limbCount;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_skelanime/SkelAnime_GetFrameData2.asm")
#endif

/**
 * Used by legacy animation format
 */
s16 Animation_GetLimbCount2(LegacyAnimationHeader* animation) {
    LegacyAnimationHeader* animHeader = Lib_PtrSegToVirt(animation);

    return animHeader->limbCount;
}

/**
 * Used by legacy animation format
 */
s16 Animation_GetLength2(LegacyAnimationHeader* animation) {
    LegacyAnimationHeader* animHeader = Lib_PtrSegToVirt(animation);

    return animHeader->frameCount;
}

/**
 * Used by legacy animation format
 */
s16 Animation_GetLastFrame2(LegacyAnimationHeader* animation) {
    AnimationHeaderCommon* animHeader = Lib_PtrSegToVirt(animation);

    return animHeader->frameCount - 1;
}

/**
 * Linearly interpolates the start and target frame tables with the given weight, putting the result in dst
 */
void SkelAnime_InterpFrameTable(s32 limbCount, Vec3s* dst, Vec3s* start, Vec3s* target, f32 weight) {
    s32 i;
    s16 diff;
    s16 base;

    if (weight < 1.0f) {
        for (i = 0; i < limbCount; i++, dst++, start++, target++) {
            base = start->x;
            diff = target->x - base;
            dst->x = (s16)(diff * weight) + base;
            base = start->y;
            diff = target->y - base;
            dst->y = (s16)(diff * weight) + base;
            base = start->z;
            diff = target->z - base;
            dst->z = (s16)(diff * weight) + base;
        }
    } else {
        for (i = 0; i < limbCount; i++, dst++, target++) {
            dst->x = target->x;
            dst->y = target->y;
            dst->z = target->z;
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
void AnimationContext_SetLoadFrame(GlobalContext* globalCtx, LinkAnimationHeader* animation, s32 frame,
                                 s32 limbCount, Vec3s* frameTable) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_LINKANIMETION);

    if (entry != NULL) {
        LinkAnimationHeader* linkAnimHeader = (LinkAnimationHeader *)Lib_PtrSegToVirt(animation);
        u32 ram = frameTable;

        osCreateMesgQueue(&entry->data.load.msgQueue, &entry->data.load.msg, 1);
        DmaMgr_SendRequestImpl(
            &entry->data.load.req, ram,
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
void SkelAnime_InitLink(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                                 LinkAnimationHeader* animation, s32 flags, Vec3s* jointTable,
                                 Vec3s* morphTable, s32 limbBufCount) {
    SkeletonHeader* skeletonHeader;
    s32 headerCount;
    s32 limbCount;
    size_t allocSize;

    skeletonHeader = Lib_PtrSegToVirt(skeletonHeaderSeg);
    headerCount = skeletonHeader->limbCount;
    skelAnime->initFlags = flags;
    limbCount = (flags & 2) ? headerCount : 1;

    if (flags & 1) {
        limbCount += headerCount;
    }

    if (flags & 4) {
        limbCount += headerCount;
    }

    skelAnime->limbCount = limbCount;
    skelAnime->dListCount = skeletonHeader->dListCount;
    skelAnime->skeleton = Lib_PtrSegToVirt(skeletonHeader->skeletonSeg);
    allocSize = sizeof(Vec3s) * limbCount;

    if (flags & 8) {
        allocSize += 2;
    }

    if (jointTable == NULL) {
        skelAnime->limbDrawTbl = ZeldaArena_Malloc(allocSize);
        skelAnime->transitionDrawTbl = ZeldaArena_Malloc(allocSize);
    } else {
        skelAnime->limbDrawTbl = (Vec3s*)ALIGN16((u32)jointTable);
        skelAnime->transitionDrawTbl = (Vec3s*)ALIGN16((u32)morphTable);
    }

    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f, 0.0f, 0, 0.0f);
}

void LinkAnimation_SetUpdateFunction(SkelAnime* skelAnime) {
    if (skelAnime->mode < 2) {
        skelAnime->animUpdate = LinkAnimation_Loop;
    } else {
        skelAnime->animUpdate = LinkAnimation_Once;
    }
    skelAnime->transCurrentFrame = 0.0f;
}

/**
 * Advances the current Link animation and updates all frame tables. If the animation plays once, returns true when it
 * finishes.
 */
s32 LinkAnimation_Update(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    return skelAnime->animUpdate(globalCtx, skelAnime);
}

/**
 * Requests an interpolation between the pose in jointTable to the one in morphTable, advancing the morph but not the
 * animation frame
 */
s32 LinkAnimation_Morph(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 prevMorphWeight = skelAnime->transCurrentFrame;
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
    if (skelAnime->transCurrentFrame <= 0.0f) {
        LinkAnimation_SetUpdateFunction(skelAnime);
    }

    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl,
                                 1.0f - (skelAnime->transCurrentFrame / prevMorphWeight));
    return 0;
}

/**
 * Requests a load of the next frame of a Link animation, advances the morph, and requests an interpolation between
 * jointTable and morphTable
 */
void LinkAnimation_AnimateFrame(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    AnimationContext_SetLoadFrame(globalCtx, skelAnime->linkAnimetionSeg, skelAnime->animCurrentFrame,
                                skelAnime->limbCount, skelAnime->limbDrawTbl);
    if (skelAnime->transCurrentFrame != 0) {
        f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;
        skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
        if (skelAnime->transCurrentFrame <= 0.0f) {
            skelAnime->transCurrentFrame = 0.0f;
        } else {
            AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl,
                                         skelAnime->transitionDrawTbl, skelAnime->transCurrentFrame);
        }
    }
}

/**
 * Advances a Link animation that loops over its full length
 */
s32 LinkAnimation_Loop(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;
    if (skelAnime->animCurrentFrame < 0.0f) {
        skelAnime->animCurrentFrame += skelAnime->totalFrames;
    } else if (skelAnime->totalFrames <= skelAnime->animCurrentFrame) {
        skelAnime->animCurrentFrame -= skelAnime->totalFrames;
    }
    LinkAnimation_AnimateFrame(globalCtx, skelAnime);
    return 0;
}

/**
 * Advances a Link animation that stops at endFrame and returns true when it is reached.
 */
s32 LinkAnimation_Once(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    if (skelAnime->animCurrentFrame == skelAnime->animFrameCount) {
        LinkAnimation_AnimateFrame(globalCtx, skelAnime);
        return 1;
    }

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;

    if (((skelAnime->animCurrentFrame - skelAnime->animFrameCount) * skelAnime->animPlaybackSpeed) > 0.0f) {
        skelAnime->animCurrentFrame = skelAnime->animFrameCount;
    } else {
        if (skelAnime->animCurrentFrame < 0.0f) {
            skelAnime->animCurrentFrame += skelAnime->totalFrames;
        } else if (skelAnime->totalFrames <= skelAnime->animCurrentFrame) {
            skelAnime->animCurrentFrame -= skelAnime->totalFrames;
        }
    }
    LinkAnimation_AnimateFrame(globalCtx, skelAnime);
    return 0;
}

/**
 * Sets a new morph and resets the morph weight for the current animation.
 */
void Animation_SetMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 morphFrames) {
    skelAnime->transCurrentFrame = 1.0f;
    skelAnime->transitionStep = 1.0f / morphFrames;
}

/**
 * General way to set a new Link animation, allowing choice of playback speed, start frame, end frame, play mode, and
 * number of transition frames. Positive morph frames morph from the current pose to the start pose of the new
 * animation, then start the new animation. Negative morph frames start the new animation immediately, modified by the
 * pose immediately before the animation change.
 */
void LinkAnimation_Change(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                              f32 playSpeed, f32 startFrame, f32 endFrame, u8 mode, f32 morphFrames) {
    skelAnime->mode = mode;
    if ((morphFrames != 0.0f) &&
        ((animation != skelAnime->linkAnimetionSeg) || (startFrame != skelAnime->animCurrentFrame))) {
        if (morphFrames < 0) {
            LinkAnimation_SetUpdateFunction(skelAnime);
            SkelAnime_CopyFrameTable(skelAnime, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
            morphFrames = -morphFrames;
        } else {
            skelAnime->animUpdate = LinkAnimation_Morph;
            AnimationContext_SetLoadFrame(globalCtx, animation, (s32)startFrame, skelAnime->limbCount,
                                        skelAnime->transitionDrawTbl);
        }
        skelAnime->transCurrentFrame = 1.0f;
        skelAnime->transitionStep = 1.0f / morphFrames;
    } else {
        LinkAnimation_SetUpdateFunction(skelAnime);
        AnimationContext_SetLoadFrame(globalCtx, animation, (s32)startFrame, skelAnime->limbCount,
                                    skelAnime->limbDrawTbl);
        skelAnime->transCurrentFrame = 0.0f;
    }

    skelAnime->linkAnimetionSeg = animation;
    skelAnime->animCurrentFrame = 0.0f;
    skelAnime->initialFrame = startFrame;
    skelAnime->animCurrentFrame = startFrame;
    skelAnime->animFrameCount = endFrame;
    skelAnime->totalFrames = Animation_GetLength(animation);
    skelAnime->animPlaybackSpeed = playSpeed;
}

/**
 * Immediately changes to a Link animation that plays once at the default speed.
 */
void LinkAnimation_PlayOnce(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                         LinkAnimationHeader* animation) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f,
                             Animation_GetLastFrame(&animation->common), 2, 0.0f);
}

/**
 * Immediately changes to a Link animation that plays once at the specified speed.
 */
void LinkAnimation_PlayOnceSetSpeed(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                          LinkAnimationHeader* animation, f32 playSpeed) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, playSpeed, 0.0f,
                             Animation_GetLastFrame(&animation->common), 2, 0.0f);
}

/**
 * Immediately changes to a Link animation that loops at the default speed.
 */
void LinkAnimation_PlayLoop(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                           LinkAnimationHeader* animation) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f,
                             Animation_GetLastFrame(&animation->common), 0, 0.0f);
}

/**
 * Immediately changes to a Link animation that loops at the specified speed.
 */
void LinkAnimation_PlayLoopSetSpeed(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                            LinkAnimationHeader* animation, f32 playSpeed) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, playSpeed, 0.0f,
                             Animation_GetLastFrame(&animation->common), 0, 0.0f);
}

/**
 * Requests copying jointTable to morphTable
 */
void LinkAnimation_CopyJointToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    AnimationContext_SetCopyAll(globalCtx, skelAnime->limbCount, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
}

/**
 * Requests copying morphTable to jointTable
 */
void LinkAnimation_CopyMorphToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    AnimationContext_SetCopyAll(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl);
}

/**
 * Requests loading frame data from the Link animation into morphTable
 */
void LinkAnimation_LoadToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                   f32 frame) {
    AnimationContext_SetLoadFrame(globalCtx, animation, (s32)frame, skelAnime->limbCount,
                                skelAnime->transitionDrawTbl);
}

/**
 * Requests loading frame data from the Link animation into jointTable
 */
void LinkAnimation_LoadToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                   f32 frame) {
    AnimationContext_SetLoadFrame(globalCtx, animation, (s32)frame, skelAnime->limbCount,
                                skelAnime->limbDrawTbl);
}

/**
 * Requests interpolating between jointTable and morphTable, placing the result in jointTable
 */
void LinkAnimation_InterpJointMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 weight) {
    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl,
                                 weight);
}

/**
 * Requests loading frame data from the Link animations and blending them, placing the result in jointTable
 */
void LinkAnimation_BlendToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation1,
                   f32 frame1, LinkAnimationHeader* animation2, f32 frame2, f32 blendWeight,
                   Vec3s* blendTable) {
    Vec3s* alignedBlendTable;
    AnimationContext_SetLoadFrame(globalCtx, animation1, (s32)frame1, skelAnime->limbCount,
                                skelAnime->limbDrawTbl);

    alignedBlendTable = (Vec3s*)ALIGN16((u32)blendTable);

    AnimationContext_SetLoadFrame(globalCtx, animation2, (s32)frame2, skelAnime->limbCount,
                                alignedBlendTable);
    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, alignedBlendTable,
                                 blendWeight);
}

/**
 * Requests loading frame data from the Link animations and blending them, placing the result in morphTable
 */
void LinkAnimation_BlendToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* animation1,
                   f32 frame1, LinkAnimationHeader* animation2, f32 frame2, f32 blendWeight,
                   Vec3s* blendTable) {
    Vec3s* alignedBlendTable;

    AnimationContext_SetLoadFrame(globalCtx, animation1, (s32)frame1, skelAnime->limbCount,
                                skelAnime->transitionDrawTbl);

    alignedBlendTable = (Vec3s*)ALIGN16((u32)blendTable);

    AnimationContext_SetLoadFrame(globalCtx, animation2, (s32)frame2, skelAnime->limbCount,
                                alignedBlendTable);
    AnimationContext_SetInterp(globalCtx, skelAnime->limbCount, skelAnime->transitionDrawTbl, alignedBlendTable,
                                 blendWeight);
}

void LinkAnimation_EndLoop(SkelAnime* skelAnime) {
    skelAnime->mode = 2;
    LinkAnimation_SetUpdateFunction(skelAnime);
}

/**
 * Checks if the current frame is after frame and the previous frame was before it.
 */
s32 Animation_OnFrameImpl(SkelAnime* skelAnime, f32 frame, f32 updateRate) {
    f32 updateSpeed;
    f32 curFrameDiff;
    f32 nextFrame;

    updateSpeed = skelAnime->animPlaybackSpeed * updateRate;
    nextFrame = skelAnime->animCurrentFrame - updateSpeed;
    if (nextFrame < 0.0f) {
        nextFrame += skelAnime->totalFrames;
    } else if (skelAnime->totalFrames <= nextFrame) {
        nextFrame -= skelAnime->totalFrames;
    }

    if ((frame == 0.0f) && (updateSpeed > 0.0f)) {
        frame = skelAnime->totalFrames;
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
                    AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_PtrSegToVirt(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_PtrSegToVirt(skeletonHeader->skeletonSeg);
    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl = ZeldaArena_Malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);
        skelAnime->transitionDrawTbl = ZeldaArena_Malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);
    } else {
        skelAnime->limbDrawTbl = limbDrawTbl;
        skelAnime->transitionDrawTbl = transitionDrawTable;
    }

    if (animationSeg != NULL) {
        Animation_PlayLoop(skelAnime, animationSeg);
    }
}

/**
 * Initializes a flex skeleton to a looping animation, dynamically allocating the frame tables if not given.
 */
void SkelAnime_InitFlex(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                      AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_PtrSegToVirt(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->dListCount = skeletonHeader->dListCount;
    skelAnime->skeleton = Lib_PtrSegToVirt(skeletonHeader->skeletonSeg);

    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl = ZeldaArena_Malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);

        skelAnime->transitionDrawTbl = ZeldaArena_Malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);
    } else {
        skelAnime->limbDrawTbl = limbDrawTbl;
        skelAnime->transitionDrawTbl = transitionDrawTable;
    }

    if (animationSeg != NULL) {
        Animation_PlayLoop(skelAnime, animationSeg);
    }
}

/**
 * Initializes a skeleton with SkinLimbs to a looping animation, dynamically allocating the frame tables.
 */
void SkelAnime_InitSkin(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animationSeg) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_PtrSegToVirt(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_PtrSegToVirt(skeletonHeader->skeletonSeg);
    skelAnime->limbDrawTbl = ZeldaArena_Malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);
    skelAnime->transitionDrawTbl = ZeldaArena_Malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);

    // Debug prints here, required to match.
    if (1) {};

    if (animationSeg != NULL) {
        Animation_PlayLoop(skelAnime, animationSeg);
    }
}

/**
 * Sets the SkelAnime's update function based on its current mode.
 */
void SkelAnime_SetUpdate(SkelAnime* skelAnime) {
    if (skelAnime->mode < 2) {
        skelAnime->animUpdate = SkelAnime_LoopFull;
    } else if (skelAnime->mode < 4) {
        skelAnime->animUpdate = SkelAnime_Once;
    } else {
        skelAnime->animUpdate = SkelAnime_LoopPartial;
    }
}

/**
 * Advances the current animation and updates all frame tables. If the animation plays once, returns true when it
 * finishes.
 */
s32 SkelAnime_Update(SkelAnime* skelAnime) {
    return skelAnime->animUpdate(skelAnime);
}

/**
 * Morphs from the pose in jointTable to the one in morphTable, advancing the morph but not the animation frame
 */
s32 SkelAnime_Morph(SkelAnime* skelAnime) {
    f32 prevMorphWeight = skelAnime->transCurrentFrame;
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
    if (skelAnime->transCurrentFrame <= 0.0f) {
        SkelAnime_SetUpdate(skelAnime);
        skelAnime->transCurrentFrame = 0.0f;
    }
    SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
                               skelAnime->transitionDrawTbl, 1.0f - (skelAnime->transCurrentFrame / prevMorphWeight));
    return 0;
}

/**
 * Performs a tapered morph from the pose in jointTable to the one in morphTable, advancing the morph but not the
 * animation frame
 */
s32 SkelAnime_MorphTaper(SkelAnime* skelAnime) {
    s16 prevPhase = (s16)(skelAnime->transCurrentFrame * 16384.0f);
    s16 curPhase;
    f32 prevWeight;
    f32 curWeight;
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
    if (skelAnime->transCurrentFrame <= 0.0f) {
        SkelAnime_SetUpdate(skelAnime);
        skelAnime->transCurrentFrame = 0.0f;
    }
    curPhase = (s16)(skelAnime->transCurrentFrame * 16384.0f);
    if (skelAnime->unk03 < 0) {
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
    SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
                               skelAnime->transitionDrawTbl, 1.0f - curWeight);
    return 0;
}

/**
 * Gets frame data for the current frame as modified by morphTable and advances the morph
 */
void SkelAnime_AnimateFrame(SkelAnime* skelAnime) {
    s32 t;
    s32 pad[2];
    Vec3s sp38[98];
    f32 temp_f10;
    f32 temp_f2;

    SkelAnime_GetFrameData(skelAnime->animCurrentSeg, skelAnime->animCurrentFrame, skelAnime->limbCount,
                           skelAnime->limbDrawTbl);
    if (skelAnime->mode & 0x1) {
        t = (s32)skelAnime->animCurrentFrame;
        temp_f10 = t;
        temp_f2 = skelAnime->animCurrentFrame - temp_f10;
        t++;
        if (t >= (s32)skelAnime->totalFrames) {
            t = 0;
        }
        SkelAnime_GetFrameData(skelAnime->animCurrentSeg, t, skelAnime->limbCount, sp38);
        SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl, sp38, temp_f2);
    }
    if (skelAnime->transCurrentFrame != 0) {
        f32 updateRate = gFramerateDivisorThird;

        skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
        if (skelAnime->transCurrentFrame <= 0.0f) {
            skelAnime->transCurrentFrame = 0.0f;
            return;
        }
        SkelAnime_InterpFrameTable(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
                                   skelAnime->transitionDrawTbl, skelAnime->transCurrentFrame);
    }
}

/**
 * Advances an animation that loops over its full length and updates the frame tables
 */
s32 SkelAnime_LoopFull(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;
    if (skelAnime->animCurrentFrame < 0.0f) {
        skelAnime->animCurrentFrame += skelAnime->totalFrames;
    } else if (skelAnime->totalFrames <= skelAnime->animCurrentFrame) {
        skelAnime->animCurrentFrame -= skelAnime->totalFrames;
    }

    SkelAnime_AnimateFrame(skelAnime);
    return 0;
}

/**
 * Advances an animation that loops over part of its length and updates the frame tables
 */
s32 SkelAnime_LoopPartial(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;
    if (skelAnime->animCurrentFrame < skelAnime->initialFrame) {
        skelAnime->animCurrentFrame =
            (skelAnime->animCurrentFrame - skelAnime->initialFrame) + skelAnime->animFrameCount;
    } else if (skelAnime->animFrameCount <= skelAnime->animCurrentFrame) {
        skelAnime->animCurrentFrame =
            (skelAnime->animCurrentFrame - skelAnime->animFrameCount) + skelAnime->initialFrame;
    }

    SkelAnime_AnimateFrame(skelAnime);
    return 0;
}

/**
 * Advances an animation that stops at endFrame and returns true when it is reached.
 */
s32 SkelAnime_Once(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    if (skelAnime->animCurrentFrame == skelAnime->animFrameCount) {
        SkelAnime_GetFrameData(skelAnime->animCurrentSeg, (s32)skelAnime->animCurrentFrame, skelAnime->limbCount,
                               skelAnime->limbDrawTbl);
        SkelAnime_AnimateFrame(skelAnime);
        return 1;
    }

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;
    if (((skelAnime->animCurrentFrame - skelAnime->animFrameCount) * skelAnime->animPlaybackSpeed) > 0.0f) {
        skelAnime->animCurrentFrame = skelAnime->animFrameCount;
    } else {
        if (skelAnime->animCurrentFrame < 0.0f) {
            skelAnime->animCurrentFrame += skelAnime->totalFrames;
        } else {
            if (skelAnime->totalFrames <= skelAnime->animCurrentFrame) {
                skelAnime->animCurrentFrame -= skelAnime->totalFrames;
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
void Animation_ChangeImpl(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame,
                              f32 endFrame, u8 mode, f32 morphFrames, s8 taper) {
    skelAnime->mode = mode;
    if ((morphFrames != 0.0f) &&
        ((animation != skelAnime->animCurrentSeg) || (startFrame != skelAnime->animCurrentFrame))) {
        if (morphFrames < 0) {
            SkelAnime_SetUpdate(skelAnime);
            SkelAnime_CopyFrameTable(skelAnime, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
            morphFrames = -morphFrames;
        } else {
            if (taper != 0) {
                skelAnime->animUpdate = SkelAnime_MorphTaper;
                skelAnime->unk03 = taper;
            } else {
                skelAnime->animUpdate = SkelAnime_Morph;
            }
            SkelAnime_GetFrameData(animation, startFrame, skelAnime->limbCount, skelAnime->transitionDrawTbl);
        }
        skelAnime->transCurrentFrame = 1.0f;
        skelAnime->transitionStep = 1.0f / morphFrames;
    } else {
        SkelAnime_SetUpdate(skelAnime);
        SkelAnime_GetFrameData(animation, startFrame, skelAnime->limbCount, skelAnime->limbDrawTbl);
        skelAnime->transCurrentFrame = 0.0f;
    }

    skelAnime->animCurrentSeg = animation;
    skelAnime->initialFrame = startFrame;
    skelAnime->animFrameCount = endFrame;
    skelAnime->totalFrames = Animation_GetLength(&animation->common);
    if (skelAnime->mode >= 4) {
        skelAnime->animCurrentFrame = 0.0f;
    } else {
        skelAnime->animCurrentFrame = startFrame;
        if (skelAnime->mode < 2) {
            skelAnime->animFrameCount = skelAnime->totalFrames - 1.0f;
        }
    }
    skelAnime->animPlaybackSpeed = playSpeed;
}

/**
 * General way to set a new animation, allowing choice of playback speed, start frame, end frame, play mode, and number
 * of transition frames. Positive morph frames morph from the current pose to the start pose of the new animation, then
 * start the new animation. Negative morph frames start the new animation immediately, modified by the pose immediately
 * before the animation change.
 */
void Animation_Change(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame,
                          f32 endFrame, u8 mode, f32 morphFrames) {
    Animation_ChangeImpl(skelAnime, animation, playSpeed, startFrame, endFrame, mode, morphFrames, 0);
}

void Animation_PlayOnce(SkelAnime* skelAnime, AnimationHeader* animationSeg) {
    Animation_Change(skelAnime, animationSeg, 1.0f, 0.0f, Animation_GetLastFrame(&animationSeg->common), 2,
                         0.0f);
}

/**
 * Smoothly transitions to an animation that plays once at the default speed.
 * Positive morph frames morph from the current pose to the start pose of the new animation, then start the new
 * animation. Negative morph frames start the new animation immediately, modified by the pose immediately before the
 * animation change.
 */
void Animation_MorphToPlayOnce(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 morphFrames) {
    Animation_Change(skelAnime, animationSeg, 1.0f, 0, Animation_GetLastFrame(&animationSeg->common), 2,
                         morphFrames);
}

/**
 * Immediately changes to an animation that plays once at the specified speed.
 */
void Animation_PlayOnceSetSpeed(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playSpeed) {
    Animation_Change(skelAnime, animationSeg, playSpeed, 0.0f,
                         Animation_GetLastFrame(&animationSeg->common), 2, 0.0f);
}

/**
 * Immediately changes to an animation that loops at the default.
 */
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animationSeg) {
    Animation_Change(skelAnime, animationSeg, 1.0f, 0.0f, Animation_GetLastFrame(&animationSeg->common), 0,
                         0.0f);
}

/**
 * Smoothly transitions to a looping animation, specifying the number of frames for the transition.
 * Positive morph frames morph from the current pose to the start pose of the new animation, then start the new
 * animation. Negative morph frames start the new animation immediately, modified by the pose immediately before the
 * animation change.
 */
void Animation_MorphToLoop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 morphFrames) {
    Animation_Change(skelAnime, animationSeg, 1.0f, 0.0f, 0.0f, 0, morphFrames);
}

void Animation_PlayLoopSetSpeed(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed) {
    Animation_Change(skelAnime, animationSeg, playbackSpeed, 0.0f,
                         Animation_GetLastFrame(&animationSeg->common), 0, 0.0f);
}

void Animation_EndLoop(SkelAnime* skelAnime) {
    skelAnime->mode = 2;
    skelAnime->animFrameCount = skelAnime->totalFrames;
    SkelAnime_SetUpdate(skelAnime);
}

void Animation_Reverse(SkelAnime* skelAnime) {
    f32 initialFrame = skelAnime->initialFrame;

    skelAnime->initialFrame = skelAnime->animFrameCount;
    skelAnime->animPlaybackSpeed = -skelAnime->animPlaybackSpeed;
    skelAnime->animFrameCount = initialFrame;
}

void SkelAnime_CopyFrameTableTrue(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* index) {
    s32 i;

    for (i = 0; i < skelAnime->limbCount; i++, dst++, src++) {
        if (*index++) {
            *dst = *src;
        }
    }
}

void SkelAnime_CopyFrameTableFalse(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* arg3) {
    s32 i;

    for (i = 0; i < skelAnime->limbCount; i++, dst++, src++) {
        if (*arg3++ < 1U) {
            *dst = *src;
        }
    }
}

/*
 * Moves `pos` backwards on the xz plane from `angle`
 */
void SkelAnime_UpdateTranslation(SkelAnime* skelAnime, Vec3f* pos, s16 angle) {
    f32 x;
    f32 z;
    f32 sin;
    f32 cos;

    if (skelAnime->flags & 0x10) {
        pos->z = 0.0f;
        pos->x = 0.0f;
    } else {
        // `angle` rotation around y axis.
        x = skelAnime->limbDrawTbl->x - skelAnime->prevFramePos.x;
        z = skelAnime->limbDrawTbl->z - skelAnime->prevFramePos.z;
        sin = Math_SinS(angle);
        cos = Math_CosS(angle);
        pos->x = x * cos + z * sin;
        pos->z = z * cos - x * sin;
    }

    skelAnime->prevFramePos.x = skelAnime->limbDrawTbl->x;
    skelAnime->limbDrawTbl->x = skelAnime->unk3E.x;
    skelAnime->prevFramePos.z = skelAnime->limbDrawTbl->z;
    skelAnime->limbDrawTbl->z = skelAnime->unk3E.z;
    if (skelAnime->flags & ANIM_FLAG_UPDATEXZ) {
        if (skelAnime->flags & ANIM_FLAG_UPDATEY) {
            pos->y = 0.0f;
        } else {
            pos->y = skelAnime->limbDrawTbl->y - skelAnime->prevFramePos.y;
        }
        skelAnime->prevFramePos.y = skelAnime->limbDrawTbl->y;
        skelAnime->limbDrawTbl->y = skelAnime->unk3E.y;
    } else {
        pos->y = 0.0f;
        skelAnime->prevFramePos.y = skelAnime->limbDrawTbl->y;
    }
    skelAnime->flags &= ~ANIM_FLAG_UPDATEY;
}

s32 Animation_OnFrame(SkelAnime* skelAnime, f32 frame) {
    return Animation_OnFrameImpl(skelAnime, frame, 1.0f);
}

void SkelAnime_Free(SkelAnime* skelAnime, GlobalContext* globalCtx) {
    if (skelAnime->limbDrawTbl != NULL) {
        ZeldaArena_Free(skelAnime->limbDrawTbl);
    }

    if (skelAnime->transitionDrawTbl != NULL) {
        ZeldaArena_Free(skelAnime->transitionDrawTbl);
    }
}

void SkelAnime_CopyFrameTable(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src) {
    bcopy(src, dst, sizeof(Vec3s) * skelAnime->limbCount);
}
