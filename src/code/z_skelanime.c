#include <ultra64.h>
#include <global.h>

s32 LinkAnimation_Loop(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 LinkAnimation_Once(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 SkelAnime_LoopFull(SkelAnime* skelAnime);
s32 SkelAnime_LoopPartial(SkelAnime* skelAnime);
s32 SkelAnime_Once(SkelAnime* skelAnime);
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_UpdateTranslation(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
void LinkAnimation_Change(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                              f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationMode, f32 transitionRate);
void SkelAnime_CopyFrameTable(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);
void AnimationContext_LoadFrame(GlobalContext* globalCtx, AnimationEntryType0* entry);
void AnimationContext_CopyAll(GlobalContext* globalCtx, AnimationEntryType1* entry);
void AnimationContext_Interp(GlobalContext* globalCtx, AnimationEntryType2* entry);
void AnimationContext_CopyTrue(GlobalContext* globalCtx, AnimationEntryType3* entry);
void AnimationContext_CopyFalse(GlobalContext* globalCtx, AnimationEntryType4* entry);
void AnimationContext_MoveActor(GlobalContext* globalCtx, AnimationEntryType5* entry);

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
        SysMatrix_RotateAndTranslateState(&pos, &rot);
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
        SysMatrix_RotateAndTranslateState(&pos, &rot);
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

/*
 * Draws the limb at `limbIndex` with a level of detail display lists index by `dListIndex`, Limb matrices come
 * from a dynamic allocation from the graph arena.
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
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (newDList != NULL) {
            SysMatrix_GetStateAsRSPMatrix(*mtx);
            gSPMatrix(POLY_OPA_DISP++, *mtx, G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, newDList);
            (*mtx)++;
        } else if (limbDList != NULL) {
            SysMatrix_GetStateAsRSPMatrix(*mtx);
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

/*
 * Draws the Skeleton described by `skeleton` with a level of detail display list indexed by `dListIndex`
 * Matricies for the limbs are dynamically allocted from the graph arena.  The dynamic allocation occurs
 * because the Skeleton is too large to be supported by the normal matrix stack.
 */
void SkelAnime_DrawFlexLod(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                         OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor,
                         s32 dListIndex) {
    SkelLimbEntry* limbEntry;
    s32 pad;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    RSPMatrix* mtx;
    GraphicsContext* gfxCtx;
    s32 pad2;

    mtx = (RSPMatrix*)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(RSPMatrix) * dListCount));

    if (skeleton == NULL) {
        return;
    }

    gfxCtx = globalCtx->state.gfxCtx;

    gSPSegment(gfxCtx->polyOpa.p++, 0xD, mtx);
    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);
    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;

    rot = limbDrawTable[1];

    dList[0] = limbEntry->displayLists[dListIndex];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList[1] != NULL) {
            Gfx* polyTemp = gfxCtx->polyOpa.p;

            gSPMatrix(polyTemp, SysMatrix_GetStateAsRSPMatrix(mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList[1]);
            gfxCtx->polyOpa.p = polyTemp + 2;
            mtx++;
        } else if (dList[0] != NULL) {
            SysMatrix_GetStateAsRSPMatrix(mtx);
            mtx++;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList[1], &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        SkelAnime_DrawFlexLimbLod(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                postLimbDraw, actor, dListIndex, &mtx);
    }

    Matrix_Pop();
}

/*
 * Draws the limb of the Skeleton `skeleton` at `limbIndex`
 */
void SkelAnime_DrawLimbOpa(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                        OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor) {
    SkelLimbEntry* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[limbIndex]);
    limbIndex++;
    rot = limbDrawTable[limbIndex];
    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;
    dList = limbEntry->displayLists[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = gfxCtx->polyOpa.p;

            gSPMatrix(polyTemp, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList);
            gfxCtx->polyOpa.p = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                           postLimbDraw, actor);
    }

    Matrix_Pop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                           actor);
    }
}

void SkelAnime_DrawOpa(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                    OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor) {
    SkelLimbEntry* rootLimb;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx;
    s32 pad2;

    if (skeleton == NULL) {
        return;
    }

    gfxCtx = globalCtx->state.gfxCtx;

    Matrix_Push();
    rootLimb = Lib_PtrSegToVirt(skeleton->limbs[0]);

    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;

    rot = limbDrawTable[1];
    dList = rootLimb->displayLists[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = gfxCtx->polyOpa.p;

            gSPMatrix(polyTemp, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList);
            gfxCtx->polyOpa.p = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor);
    }

    if (rootLimb->firstChildIndex != LIMB_DONE) {
        SkelAnime_DrawLimbOpa(globalCtx, rootLimb->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                           postLimbDraw, actor);
    }

    Matrix_Pop();
}

void SkelAnime_DrawFlexLimbOpa(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                          OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor,
                          RSPMatrix** limbMatricies) {
    SkelLimbEntry* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[limbIndex]);
    limbIndex++;
    rot = limbDrawTable[limbIndex];

    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;

    dList[0] = limbEntry->displayLists[0];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList[1] != NULL) {
            SysMatrix_GetStateAsRSPMatrix(*limbMatricies);
            gSPMatrix(gfxCtx->polyOpa.p++, *limbMatricies, G_MTX_LOAD);
            gSPDisplayList(gfxCtx->polyOpa.p++, dList[1]);
            (*limbMatricies)++;
        } else if (dList[0] != NULL) {
            SysMatrix_GetStateAsRSPMatrix(*limbMatricies);
            (*limbMatricies)++;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, limbMatricies);
    }

    Matrix_Pop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, limbMatricies);
    }
}

void SkelAnime_DrawFlexOpa(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                      OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor) {
    SkelLimbEntry* limbEntry;
    s32 pad;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    RSPMatrix* mtx;
    GraphicsContext* gfxCtx;
    s32 pad2;

    mtx = (RSPMatrix*)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(RSPMatrix) * dListCount));

    if (skeleton == NULL) {
        return;
    }

    gfxCtx = globalCtx->state.gfxCtx;

    gSPSegment(gfxCtx->polyOpa.p++, 0xD, mtx);

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);

    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;
    rot = limbDrawTable[1];

    dList[0] = limbEntry->displayLists[0];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList[1] != NULL) {
            Gfx* polyTemp = gfxCtx->polyOpa.p;

            gSPMatrix(polyTemp, SysMatrix_GetStateAsRSPMatrix(mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList[1]);
            gfxCtx->polyOpa.p = polyTemp + 2;
            mtx++;
        } else {
            if (dList[0] != NULL) {
                SysMatrix_GetStateAsRSPMatrix(mtx);
                mtx++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        SkelAnime_DrawFlexLimbOpa(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, &mtx);
    }

    Matrix_Pop();
}

void func_80134148(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                   OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, UnkActorDraw unkDraw, Actor* actor,
                   RSPMatrix** mtx) {
    SkelLimbEntry* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad2;

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[limbIndex]);
    limbIndex++;

    rot = limbDrawTable[limbIndex];
    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;

    dList[0] = limbEntry->displayLists[0];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        Matrix_Push();
        unkDraw(globalCtx, limbIndex, actor);
        if (dList[1] != NULL) {
            Gfx* polyTemp = gfxCtx->polyOpa.p;

            gSPMatrix(polyTemp, SysMatrix_GetStateAsRSPMatrix(*mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList[1]);
            gfxCtx->polyOpa.p = polyTemp + 2;
            (*mtx)++;
        } else {
            if (dList[0] != NULL) {
                SysMatrix_GetStateAsRSPMatrix(*mtx);
                (*mtx)++;
            }
        }
        Matrix_Pop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        func_80134148(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, actor, mtx);
    }

    Matrix_Pop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        func_80134148(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, actor, mtx);
    }
}

void func_801343C0(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                   OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, UnkActorDraw unkDraw, Actor* actor) {
    SkelLimbEntry* limbEntry;
    s32 pad;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    RSPMatrix* mtx;
    GraphicsContext* gfxCtx;
    s32 pad2;

    if (skeleton == NULL) {
        return;
    }

    gfxCtx = globalCtx->state.gfxCtx;

    mtx = (RSPMatrix*)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(RSPMatrix) * dListCount));

    gSPSegment(gfxCtx->polyOpa.p++, 0xD, mtx);

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);

    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;
    rot = limbDrawTable[1];

    dList[0] = limbEntry->displayLists[0];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        Matrix_Push();
        unkDraw(globalCtx, 1, actor);
        if (dList[1] != NULL) {
            Gfx* polyTemp = gfxCtx->polyOpa.p;

            gSPMatrix(polyTemp, SysMatrix_GetStateAsRSPMatrix(mtx), G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList[1]);
            gfxCtx->polyOpa.p = polyTemp + 2;
            mtx++;
        } else {
            if (dList[0] != NULL) {
                SysMatrix_GetStateAsRSPMatrix(mtx++);
            }
        }
        Matrix_Pop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        func_80134148(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, actor, &mtx);
    }

    Matrix_Pop();
}

/*
 * Copies the rotation values from the rotation value table, indexed by the rotation index table
 * When a rotation index is >= the animation limit, the output rotation value is copied from the frame's
 * rotation value list, otherwise it is copied from the initial rotation value list
 */
void SkelAnime_GetFrameData(AnimationHeader* animationSeg, s32 currentFrame, s32 limbCount, Vec3s* dst) {
    AnimationHeader* animationHeader = Lib_PtrSegToVirt(animationSeg);
    AnimationRotationIndex* index = Lib_PtrSegToVirt(animationHeader->rotationIndexSeg);
    AnimationRotationValue* rotationValueTable = Lib_PtrSegToVirt(animationHeader->rotationValueSeg);
    AnimationRotationValue* frameRotationValueTable = &rotationValueTable[currentFrame];
    s32 i;
    u16 limit = animationHeader->limit;

    for (i = 0; i < limbCount; i++) {
        // Debug prints here, this is needed to prevent loop unrolling
        if (0) {
            if (0) {};
        }
        dst->x = index->x >= limit ? frameRotationValueTable[index->x] : rotationValueTable[index->x];
        dst->y = index->y >= limit ? frameRotationValueTable[index->y] : rotationValueTable[index->y];
        dst->z = index->z >= limit ? frameRotationValueTable[index->z] : rotationValueTable[index->z];
        index++, dst++;
    }
}

s16 Animation_GetLength(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);
    return animation->frameCount;
}

s16 Animation_GetLastFrame(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);

    return (u16)animation->frameCount - 1;
}

/*
 * Draws the Skeleton `skeleton`'s limb at index `limbIndex`.  Appends all generated graphics commands to
 * `gfx`.  Returns a pointer to the next gfx to be appended to.
 */
Gfx* SkelAnime_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                         OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    SkelLimbEntry* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[limbIndex]);
    limbIndex++;

    rot = limbDrawTable[limbIndex];
    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;

    dList = limbEntry->displayLists[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList, &pos, &rot, actor, &gfx) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList != NULL) {
            gSPMatrix(gfx, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList);
            gfx = gfx + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor, &gfx);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    Matrix_Pop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    return gfx;
}

/*
 * Draws the Skeleton `skeleton`  Appends all generated graphics to `gfx`, and returns a pointer to the
 * next gfx to be appended to.
 */
Gfx* SkelAnime_Draw(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                     OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    SkelLimbEntry* limbEntry;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return NULL;
    }

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);

    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;
    rot = limbDrawTable[1];

    dList = limbEntry->displayLists[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, actor, &gfx) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList != NULL) {
            gSPMatrix(gfx, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList);
            gfx = gfx + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor, &gfx);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        gfx = SkelAnime_DrawLimb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    Matrix_Pop();

    return gfx;
}

/*
 * Draws the Skeleton `skeleton`  Appends all generated graphics to `gfx`, and returns a pointer to the
 * next gfx to be appended to.  Allocates matricies for display lists on the graph heap.
 */
Gfx* SkelAnime_DrawFlexLimb(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor,
                           RSPMatrix** mtx, Gfx* gfx) {
    SkelLimbEntry* limbEntry;
    Gfx* dList1;
    Gfx* dList2;
    Vec3f pos;
    Vec3s rot;

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[limbIndex]);
    limbIndex++;
    rot = limbDrawTable[limbIndex];

    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;

    dList1 = dList2 = limbEntry->displayLists[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList1, &pos, &rot, actor, &gfx) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList1 != NULL) {
            gSPMatrix(gfx, SysMatrix_GetStateAsRSPMatrix(*mtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList1);
            gfx = gfx + 2;
            (*mtx)++;
        } else {
            if (dList2 != NULL) {
                SysMatrix_GetStateAsRSPMatrix(*mtx);
                (*mtx)++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList2, &rot, actor, &gfx);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, mtx, gfx);
    }

    Matrix_Pop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, mtx, gfx);
    }

    return gfx;
}

Gfx* SkelAnime_DrawFlex(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                       OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    SkelLimbEntry* limbEntry;
    s32 pad;
    Gfx* dList1;
    Gfx* dList2;
    Vec3f pos;
    Vec3s rot;
    RSPMatrix* mtx;

    if (skeleton == NULL) {
        return NULL;
    }

    mtx = (RSPMatrix*)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(RSPMatrix) * dListCount));

    gSPSegment(gfx++, 0xD, mtx);

    Matrix_Push();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);

    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;

    rot = limbDrawTable[1];

    dList1 = dList2 = limbEntry->displayLists[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList1, &pos, &rot, actor, &gfx) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList1 != NULL) {
            gSPMatrix(gfx, SysMatrix_GetStateAsRSPMatrix(mtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList1);
            gfx = gfx + 2;
            mtx++;
        } else {
            if (dList2 != NULL) {
                SysMatrix_GetStateAsRSPMatrix(mtx);
                mtx++;
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList2, &rot, actor, &gfx);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        gfx = SkelAnime_DrawFlexLimb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, &mtx, gfx);
    }

    Matrix_Pop();

    return gfx;
}

//Function is unused.
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_skelanime/SkelAnime_GetFrameData2.asm")

/**
 * Used by legacy animation format
 */
s16 Animation_GetLimbCount2(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);

    return animation->unk02;
}

/**
 * Used by legacy animation format
 */
s16 Animation_GetLength2(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);

    return animation->frameCount;
}

/**
 * Used by legacy animation format
 */
s16 Animation_GetLastFrame2(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);

    return animation->frameCount - 1;
}

/**
 * Linearly interpolates the start and target frame tables with the given weight, putting the result in dst
 */
void SkelAnime_InterpFrameTable(s32 limbCount, Vec3s* dst, Vec3s* start, Vec3s* target, f32 weight) {
    s32 i;
    s16 dist;
    s16 base;

    if (weight < 1.0f) {
        for (i = 0; i < limbCount; i++, dst++, start++, target++) {
            base = start->x;
            dist = target->x - base;
            dst->x = (s16)(dist * weight) + base;
            base = start->y;
            dist = target->y - base;
            dst->y = (s16)(dist * weight) + base;
            base = start->z;
            dist = target->z - base;
            dst->z = (s16)(dist * weight) + base;
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
void AnimationContext_SetLoadFrame(GlobalContext* globalCtx, LinkAnimetionEntry* animation, s32 frame,
                                 s32 limbCount, void* ram) {
    AnimationEntry* entry;
    LinkAnimetionEntry* linkAnimetionEntry;
    s32 pad;

    entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_LINKANIMETION);

    if (entry != NULL) {
        linkAnimetionEntry = Lib_PtrSegToVirt(animation);
        osCreateMesgQueue(&entry->types.type0.msgQueue, &entry->types.type0.msg, 1);
        DmaMgr_SendRequestImpl(
            &entry->types.type0.req, ram,
            LINK_ANIMETION_OFFSET(linkAnimetionEntry->animationSegAddress, (sizeof(Vec3s) * limbCount + 2) * frame),
            sizeof(Vec3s) * limbCount + 2, 0, &entry->types.type0.msgQueue, NULL);
    }
}

/**
 * Requests copying all vectors from src frame table into dst frame table
 */
void AnimationContext_SetCopyAll(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_TYPE1);

    if (entry != NULL) {
        entry->types.type1.unk00 = sAnimQueueFlags;
        entry->types.type1.vecCount = vecCount;
        entry->types.type1.dst = dst;
        entry->types.type1.src = src;
    }
}

/**
 * Requests interpolating between base and mod frame tables with the given weight, placing the result in base
 */
void AnimationContext_SetInterp(GlobalContext* globalCtx, s32 vecCount, Vec3s* base, Vec3s* mod, f32 weight) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_TYPE2);

    if (entry != NULL) {
        entry->types.type2.unk00 = sAnimQueueFlags;
        entry->types.type2.limbCount = vecCount;
        entry->types.type2.unk04 = base;
        entry->types.type2.unk08 = mod;
        entry->types.type2.unk0C = weight;
    }
}

/**
 * Requests copying vectors from src frame table to dst frame table whose copy flag is true
 */
void AnimationContext_SetCopyTrue(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* copyFlag) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_TYPE3);

    if (entry != NULL) {
        entry->types.type3.unk00 = sAnimQueueFlags;
        entry->types.type3.vecCount = vecCount;
        entry->types.type3.dst = dst;
        entry->types.type3.src = src;
        entry->types.type3.index = copyFlag;
    }
}

/**
 * Requests copying vectors from src frame table to dst frame table whose copy flag is false
 */
void AnimationContext_SetCopyFalse(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* copyFlag) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_TYPE4);

    if (entry != NULL) {
        entry->types.type4.unk00 = sAnimQueueFlags;
        entry->types.type4.vecCount = vecCount;
        entry->types.type4.dst = dst;
        entry->types.type4.src = src;
        entry->types.type4.index = copyFlag;
    }
}


/**
 * Requests moving an actor according to the translation of its root limb
 */
void AnimationContext_SetMoveActor(GlobalContext* globalCtx, Actor* actor, SkelAnime* skelAnime, f32 arg3) {
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, ANIMATION_TYPE5);

    if (entry != NULL) {
        entry->types.type5.actor = actor;
        entry->types.type5.skelAnime = skelAnime;
        entry->types.type5.unk08 = arg3;
    }
}

/**
 * Receives the request for Link's animation frame data
 */
void AnimationContext_LoadFrame(GlobalContext* globalCtx, AnimationEntryType0* entry) {
    osRecvMesg(&entry->msgQueue, NULL, OS_MESG_BLOCK);
}

/**
 * If the entry's queue is enabled, copies all vectors from src frame table to dst frame table
 */
void AnimationContext_CopyAll(GlobalContext* globalCtx, AnimationEntryType1* entry) {
    s32 i;
    Vec3s* dst;
    Vec3s* src;
    AnimationEntryRaw* genericEntry = (AnimationEntryRaw*)entry;

    if ((genericEntry->raw[0] & sDisableAnimQueueFlags) != 0) {
        return;
    }

    for (dst = entry->dst, src = entry->src, i = 0; i < genericEntry->raw[1]; i++) {
        *dst++ = *src++;
    }
}

/**
 * If the entry's queue is enabled, interpolates between the base and mod frame tables, placing the result in base
 */
void AnimationContext_Interp(GlobalContext* globalCtx, AnimationEntryType2* entry) {
    if ((entry->unk00 & sDisableAnimQueueFlags) == 0) {
        SkelAnime_InterpFrameTable(entry->limbCount, entry->unk04, entry->unk04, entry->unk08, entry->unk0C);
    }
}

/**
 * If the entry's queue is enabled, copies all vectors from src frame table to dst frame table whose copy flag is true
 */
void AnimationContext_CopyTrue(GlobalContext* globalCtx, AnimationEntryType3* entry) {
    s32 i;
    Vec3s* dst;
    Vec3s* src;
    u8* index;
    AnimationEntryRaw* rawEntry = (AnimationEntryRaw*)entry;

    if ((rawEntry->raw[0] & sDisableAnimQueueFlags) == 0) {
        for (dst = entry->dst, src = entry->src, index = entry->index, i = 0; i < rawEntry->raw[1]; i++, dst++, src++) {
            if (*index++) {
                *dst = *src;
            }
        }
    }
}

/**
 * If the entry's queue is enabled, copies all vectors from src frame table to dst frame table whose copy flag is false
 */
void AnimationContext_CopyFalse(GlobalContext* globalCtx, AnimationEntryType4* entry) {
    s32 i;
    Vec3s* dst;
    Vec3s* src;
    u8* index;
    AnimationEntryRaw* rawEntry = (AnimationEntryRaw*)entry;

    if ((rawEntry->raw[0] & sDisableAnimQueueFlags) == 0) {
        for (dst = entry->dst, src = entry->src, index = entry->index, i = 0; i < rawEntry->raw[1]; i++, dst++, src++) {
            if (*index++ < 1U) {
                *dst = *src;
            }
        }
    }
}

/**
 * Moves an actor according to the translation of its root limb
 */
void AnimationContext_MoveActor(GlobalContext* globalCtx, AnimationEntryType5* entry) {
    s32 pad;
    Actor* actor = entry->actor;
    Vec3f pos;

    SkelAnime_UpdateTranslation(entry->skelAnime, &pos, actor->shape.rot.y);
    actor->world.pos.x += (pos.x * actor->scale.x) * entry->unk08;
    actor->world.pos.y += (pos.y * actor->scale.y) * entry->unk08;
    actor->world.pos.z += (pos.z * actor->scale.z) * entry->unk08;
}

/**
 * Performs all requests in the animation queue, then resets the queue flags.
 */
void AnimationContext_Update(GlobalContext* globalCtx, AnimationContext* animationCtx) {
    AnimationEntry* entry = animationCtx->entries;

    for (; animationCtx->animationCount != 0; entry++, animationCtx->animationCount--) {
        sAnimationLoadDone[entry->type](globalCtx, &entry->types);
    }

    sAnimQueueFlags = 1;
    sDisableAnimQueueFlags = 0;
}

/**
 * Initializes a skeleton to be used with Link animations to a looping animation, dynamically allocating the frame
 * tables if not given.
 */
void SkelAnime_InitLink(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                                 LinkAnimetionEntry* animation, s32 flags, Vec3s* jointTable,
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
void LinkAnimation_Change(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* animation,
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
                                         LinkAnimetionEntry* animation) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f,
                             Animation_GetLastFrame(&animation->genericHeader), 2, 0.0f);
}

/**
 * Immediately changes to a Link animation that plays once at the specified speed.
 */
void LinkAnimation_PlayOnceSetSpeed(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                          LinkAnimetionEntry* animation, f32 playSpeed) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, playSpeed, 0.0f,
                             Animation_GetLastFrame(&animation->genericHeader), 2, 0.0f);
}

/**
 * Immediately changes to a Link animation that loops at the default speed.
 */
void LinkAnimation_PlayLoop(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                           LinkAnimetionEntry* animation) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, 1.0f, 0.0f,
                             Animation_GetLastFrame(&animation->genericHeader), 0, 0.0f);
}

/**
 * Immediately changes to a Link animation that loops at the specified speed.
 */
void LinkAnimation_PlayLoopSetSpeed(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                            LinkAnimetionEntry* animation, f32 playSpeed) {
    LinkAnimation_Change(globalCtx, skelAnime, animation, playSpeed, 0.0f,
                             Animation_GetLastFrame(&animation->genericHeader), 0, 0.0f);
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
void LinkAnimation_LoadToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* animation,
                   f32 frame) {
    AnimationContext_SetLoadFrame(globalCtx, animation, (s32)frame, skelAnime->limbCount,
                                skelAnime->transitionDrawTbl);
}

/**
 * Requests loading frame data from the Link animation into jointTable
 */
void LinkAnimation_LoadToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* animation,
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
void LinkAnimation_BlendToJoint(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* animation1,
                   f32 frame1, LinkAnimetionEntry* animation2, f32 frame2, f32 blendWeight,
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
void LinkAnimation_BlendToMorph(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* animation1,
                   f32 frame1, LinkAnimetionEntry* animation2, f32 frame2, f32 blendWeight,
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
    skelAnime->totalFrames = Animation_GetLength(&animation->genericHeader);
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
    Animation_Change(skelAnime, animationSeg, 1.0f, 0.0f, Animation_GetLastFrame(&animationSeg->genericHeader), 2,
                         0.0f);
}

/**
 * Smoothly transitions to an animation that plays once at the default speed.
 * Positive morph frames morph from the current pose to the start pose of the new animation, then start the new
 * animation. Negative morph frames start the new animation immediately, modified by the pose immediately before the
 * animation change.
 */
void Animation_MorphToPlayOnce(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 morphFrames) {
    Animation_Change(skelAnime, animationSeg, 1.0f, 0, Animation_GetLastFrame(&animationSeg->genericHeader), 2,
                         morphFrames);
}

/**
 * Immediately changes to an animation that plays once at the specified speed.
 */
void Animation_PlayOnceSetSpeed(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playSpeed) {
    Animation_Change(skelAnime, animationSeg, playSpeed, 0.0f,
                         Animation_GetLastFrame(&animationSeg->genericHeader), 2, 0.0f);
}

/**
 * Immediately changes to an animation that loops at the default.
 */
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animationSeg) {
    Animation_Change(skelAnime, animationSeg, 1.0f, 0.0f, Animation_GetLastFrame(&animationSeg->genericHeader), 0,
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
                         Animation_GetLastFrame(&animationSeg->genericHeader), 0, 0.0f);
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
