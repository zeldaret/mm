#include <ultra64.h>
#include <global.h>

s32 func_80136288(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_8013631C(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_8013702C(SkelAnime* skelAnime);
s32 func_801370B0(SkelAnime* skelAnime);
s32 func_8013713C(SkelAnime* skelAnime);
void SkelAnime_ChangeAnimDefaultRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void func_80137748(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
void SkelAnime_ChangeLinkAnim(GlobalContext* globalCtx, SkelAnime* skelAnime,
                              LinkAnimationHeader* linkAnimationHeaderSeg, f32 playbackSpeed, f32 frame, f32 frameCount,
                              u8 animationMode, f32 transitionRate);
void SkelAnime_CopyVec3s(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);
void SkelAnime_LinkAnimetionLoaded(GlobalContext* globalCtx, AnimationEntryType0* entry);
void SkelAnime_AnimationType1Loaded(GlobalContext* globalCtx, AnimationEntryType1* entry);
void SkelAnime_AnimationType2Loaded(GlobalContext* globalCtx, AnimationEntryType2* entry);
void SkelAnime_AnimationType3Loaded(GlobalContext* globalCtx, AnimationEntryType3* entry);
void SkelAnime_AnimationType4Loaded(GlobalContext* globalCtx, AnimationEntryType4* entry);
void SkelAnime_AnimationType5Loaded(GlobalContext* globalCtx, AnimationEntryType5* entry);

static AnimationEntryCallback sAnimationLoadDone[] = {
    (AnimationEntryCallback)SkelAnime_LinkAnimetionLoaded,  (AnimationEntryCallback)SkelAnime_AnimationType1Loaded,
    (AnimationEntryCallback)SkelAnime_AnimationType2Loaded, (AnimationEntryCallback)SkelAnime_AnimationType3Loaded,
    (AnimationEntryCallback)SkelAnime_AnimationType4Loaded, (AnimationEntryCallback)SkelAnime_AnimationType5Loaded,
};

s32 D_801F5AB0;
s32 D_801F5AB4;

/*
 * Draws the limb at `limbIndex` with a level of detail display lists index by `dListIndex`
 */
void SkelAnime_LodDrawLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex) {
    StandardLimb* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    SysMatrix_StatePush();
    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;
    rot = limbDrawTable[limbIndex];

    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;

    dList = limbEntry->displayLists[dListIndex];
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
        SkelAnime_LodDrawLimb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                              postLimbDraw, actor, dListIndex);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        SkelAnime_LodDrawLimb(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                              postLimbDraw, actor, dListIndex);
    }
}

/*
 * Draws the Skeleton described by `skeleton` with a level of detail display list indexed by `dListIndex`
 */
void SkelAnime_LodDraw(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable,
                       OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex) {
    StandardLimb* limbEntry;
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

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[0]);
    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;

    rot = limbDrawTable[1];
    dList = limbEntry->displayLists[dListIndex];

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

    if (limbEntry->firstChildIndex != 0xFF) {
        SkelAnime_LodDrawLimb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                              postLimbDraw, actor, dListIndex);
    }

    SysMatrix_StatePop();
}

/*
 * Draws the limb at `limbIndex` with a level of detail display lists index by `dListIndex`, Limb matrices come
 * from a dynamic allocation from the graph arena.
 */
void SkelAnime_LodDrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                             OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor,
                             s32 dListIndex, RSPMatrix** mtx) {
    StandardLimb* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;

    rot = limbDrawTable[limbIndex];

    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;
    // Double assignment here would not work.
    dList[0] = limbEntry->displayLists[dListIndex];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList[1] != NULL) {
            SysMatrix_GetStateAsRSPMatrix(*mtx);
            gSPMatrix(gfxCtx->polyOpa.p++, *mtx, G_MTX_LOAD);
            gSPDisplayList(gfxCtx->polyOpa.p++, dList[1]);
            (*mtx)++;
        } else if (dList[0] != NULL) {
            SysMatrix_GetStateAsRSPMatrix(*mtx);
            (*mtx)++;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList[1], &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        SkelAnime_LodDrawLimbSV(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                postLimbDraw, actor, dListIndex, mtx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        SkelAnime_LodDrawLimbSV(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                postLimbDraw, actor, dListIndex, mtx);
    }
}

/*
 * Draws the Skeleton described by `skeleton` with a level of detail display list indexed by `dListIndex`
 * Matricies for the limbs are dynamically allocted from the graph arena.  The dynamic allocation occurs
 * because the Skeleton is too large to be supported by the normal matrix stack.
 */
void SkelAnime_LodDrawSV(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                         OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor,
                         s32 dListIndex) {
    StandardLimb* limbEntry;
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
    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[0]);
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
        SkelAnime_LodDrawLimbSV(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                postLimbDraw, actor, dListIndex, &mtx);
    }

    SysMatrix_StatePop();
}

/*
 * Draws the limb of the Skeleton `skeleton` at `limbIndex`
 */
void SkelAnime_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor) {
    StandardLimb* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]);
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
        SkelAnime_DrawLimb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                           postLimbDraw, actor);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        SkelAnime_DrawLimb(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                           actor);
    }
}

void SkelAnime_Draw(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw,
                    PostLimbDraw postLimbDraw, Actor* actor) {
    StandardLimb* rootLimb;
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

    SysMatrix_StatePush();
    rootLimb = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[0]);

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
        SkelAnime_DrawLimb(globalCtx, rootLimb->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                           postLimbDraw, actor);
    }

    SysMatrix_StatePop();
}

void SkelAnime_DrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                          OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor,
                          RSPMatrix** limbMatricies) {
    StandardLimb* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]);
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
        SkelAnime_DrawLimbSV(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, limbMatricies);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        SkelAnime_DrawLimbSV(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, limbMatricies);
    }
}

void SkelAnime_DrawSV(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor) {
    StandardLimb* limbEntry;
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

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[0]);

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
        SkelAnime_DrawLimbSV(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, &mtx);
    }

    SysMatrix_StatePop();
}

void func_80134148(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                   OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor,
                   RSPMatrix** mtx) {
    StandardLimb* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad2;

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]);
    limbIndex++;

    rot = limbDrawTable[limbIndex];
    pos.x = limbEntry->translation.x;
    pos.y = limbEntry->translation.y;
    pos.z = limbEntry->translation.z;

    dList[0] = limbEntry->displayLists[0];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, limbIndex, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        SysMatrix_StatePush();
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
        SysMatrix_StatePop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        func_80134148(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, actor, mtx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        func_80134148(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, actor, mtx);
    }
}

void func_801343C0(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                   OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor) {
    StandardLimb* limbEntry;
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

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[0]);

    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;
    rot = limbDrawTable[1];

    dList[0] = limbEntry->displayLists[0];
    dList[1] = dList[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList[1], &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        SysMatrix_StatePush();
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
        SysMatrix_StatePop();
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList[0], &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        func_80134148(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                      unkDraw, actor, &mtx);
    }

    SysMatrix_StatePop();
}

/*
 * Copies the rotation values from the rotation value table, indexed by the rotation index table
 * When a rotation index is >= the animation limit, the output rotation value is copied from the frame's
 * rotation value list, otherwise it is copied from the initial rotation value list
 */
void SkelAnime_AnimateFrame(AnimationHeader* animationSeg, s32 currentFrame, s32 limbCount, Vec3s* dst) {
    AnimationHeader* animationHeader = Lib_SegmentedToVirtual(animationSeg);
    JointIndex* index = Lib_SegmentedToVirtual(animationHeader->jointIndices);
    AnimationRotationValue* rotationValueTable = Lib_SegmentedToVirtual(animationHeader->frameData);
    AnimationRotationValue* frameRotationValueTable = &rotationValueTable[currentFrame];
    s32 i;
    u16 limit = animationHeader->staticIndexMax;

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

s16 SkelAnime_GetTotalFrames(AnimationHeaderCommon* animationSeg) {
    AnimationHeaderCommon* animation = Lib_SegmentedToVirtual(animationSeg);
    return animation->frameCount;
}

s16 SkelAnime_GetFrameCount(AnimationHeaderCommon* animationSeg) {
    AnimationHeaderCommon* animation = Lib_SegmentedToVirtual(animationSeg);

    return (u16)animation->frameCount - 1;
}

/*
 * Draws the Skeleton `skeleton`'s limb at index `limbIndex`.  Appends all generated graphics commands to
 * `gfx`.  Returns a pointer to the next gfx to be appended to.
 */
Gfx* SkelAnime_Draw2Limb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                         OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    StandardLimb* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]);
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
        gfx = SkelAnime_Draw2Limb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        gfx = SkelAnime_Draw2Limb(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    return gfx;
}

/*
 * Draws the Skeleton `skeleton`  Appends all generated graphics to `gfx`, and returns a pointer to the
 * next gfx to be appended to.
 */
Gfx* SkelAnime_Draw2(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable,
                     OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    StandardLimb* limbEntry;
    s32 pad;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return NULL;
    }

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[0]);

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
        gfx = SkelAnime_Draw2Limb(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    SysMatrix_StatePop();

    return gfx;
}

/*
 * Draws the Skeleton `skeleton`  Appends all generated graphics to `gfx`, and returns a pointer to the
 * next gfx to be appended to.  Allocates matricies for display lists on the graph heap.
 */
Gfx* SkelAnime_DrawLimbSV2(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor,
                           RSPMatrix** mtx, Gfx* gfx) {
    StandardLimb* limbEntry;
    Gfx* dList1;
    Gfx* dList2;
    Vec3f pos;
    Vec3s rot;

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]);
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
        gfx = SkelAnime_DrawLimbSV2(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, mtx, gfx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        gfx = SkelAnime_DrawLimbSV2(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, mtx, gfx);
    }

    return gfx;
}

Gfx* SkelAnime_DrawSV2(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                       OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    StandardLimb* limbEntry;
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

    SysMatrix_StatePush();

    limbEntry = (StandardLimb*)Lib_SegmentedToVirtual(skeleton[0]);

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
        gfx = SkelAnime_DrawLimbSV2(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, &mtx, gfx);
    }

    SysMatrix_StatePop();

    return gfx;
}

// Function is unused.
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_skelanime/func_80134FFC.asm")

s16 func_801353D4(AnimationHeaderCommon* animationSeg) {
    AnimationHeaderCommon* animation = Lib_SegmentedToVirtual(animationSeg);

    return animation->unk02;
}

/*
 * Appears to be unused anywhere in the game.  Appears to be a clone of
 * SkelAnime_GetTotalFrames
 */
s16 SkelAnime_GetTotalFrames2(AnimationHeaderCommon* animationSeg) {
    AnimationHeaderCommon* animation = Lib_SegmentedToVirtual(animationSeg);

    return animation->frameCount;
}

/*
 * Appears to be unused anywhere in the game.  Appears to be a clone of
 * SkelAnime_GetFrameCount
 */
s16 SkelAnime_GetFrameCount2(AnimationHeaderCommon* animationSeg) {
    AnimationHeaderCommon* animation = Lib_SegmentedToVirtual(animationSeg);

    return animation->frameCount - 1;
}

void SkelAnime_InterpolateVec3s(s32 limbCount, Vec3s* dst, Vec3s* vec2, Vec3s* vec3, f32 unkf) {
    s32 i;
    s16 dist;
    s16 temp2;

    if (unkf < 1.0f) {
        for (i = 0; i < limbCount; i++, dst++, vec2++, vec3++) {
            temp2 = vec2->x;
            dist = vec3->x - temp2;
            dst->x = (s16)(dist * unkf) + temp2;
            temp2 = vec2->y;
            dist = vec3->y - temp2;
            dst->y = (s16)(dist * unkf) + temp2;
            temp2 = vec2->z;
            dist = vec3->z - temp2;
            dst->z = (s16)(dist * unkf) + temp2;
        }
    } else {
        for (i = 0; i < limbCount; i++, dst++, vec3++) {
            dst->x = vec3->x;
            dst->y = vec3->y;
            dst->z = vec3->z;
        }
    }
}

void SkelAnime_AnimationCtxReset(AnimationContext* animationCtx) {
    animationCtx->animationCount = 0;
}

void func_801358D4(GlobalContext* globalCtx) {
    D_801F5AB0 *= 2;
}

void func_801358F4(GlobalContext* globalCtx) {
    D_801F5AB4 |= D_801F5AB0;
}

AnimationEntry* SkelAnime_NextEntry(AnimationContext* animationCtx, AnimationType type) {
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

/*
 * The next 6 functions are coordinate with the AnimationType enum
 */

void SkelAnime_LoadLinkAnimetion(GlobalContext* globalCtx, LinkAnimationHeader* linkAnimetionSeg, s32 frame,
                                 s32 limbCount, void* ram) {
    AnimationEntry* entry;
    LinkAnimationHeader* LinkAnimationHeader;
    s32 pad;

    entry = SkelAnime_NextEntry(&globalCtx->animationCtx, ANIMATION_LINKANIMETION);

    if (entry != NULL) {
        LinkAnimationHeader = Lib_SegmentedToVirtual(linkAnimetionSeg);
        osCreateMesgQueue(&entry->types.type0.msgQueue, &entry->types.type0.msg, 1);
        DmaMgr_SendRequestImpl(
            &entry->types.type0.req, ram,
            LINK_ANIMETION_OFFSET(LinkAnimationHeader->segment, (sizeof(Vec3s) * limbCount + 2) * frame),
            sizeof(Vec3s) * limbCount + 2, 0, &entry->types.type0.msgQueue, NULL);
    }
}

void SkelAnime_LoadAnimationType1(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src) {
    AnimationEntry* entry = SkelAnime_NextEntry(&globalCtx->animationCtx, ANIMATION_TYPE1);

    if (entry != NULL) {
        entry->types.type1.unk00 = D_801F5AB0;
        entry->types.type1.vecCount = vecCount;
        entry->types.type1.dst = dst;
        entry->types.type1.src = src;
    }
}

void SkelAnime_LoadAnimationType2(GlobalContext* globalCtx, s32 limbCount, Vec3s* arg2, Vec3s* arg3, f32 arg4) {
    AnimationEntry* entry = SkelAnime_NextEntry(&globalCtx->animationCtx, ANIMATION_TYPE2);

    if (entry != NULL) {
        entry->types.type2.unk00 = D_801F5AB0;
        entry->types.type2.limbCount = limbCount;
        entry->types.type2.unk04 = arg2;
        entry->types.type2.unk08 = arg3;
        entry->types.type2.unk0C = arg4;
    }
}

void SkelAnime_LoadAnimationType3(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index) {
    AnimationEntry* entry = SkelAnime_NextEntry(&globalCtx->animationCtx, ANIMATION_TYPE3);

    if (entry != NULL) {
        entry->types.type3.unk00 = D_801F5AB0;
        entry->types.type3.vecCount = vecCount;
        entry->types.type3.dst = dst;
        entry->types.type3.src = src;
        entry->types.type3.index = index;
    }
}

void SkelAnime_LoadAnimationType4(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index) {
    AnimationEntry* entry = SkelAnime_NextEntry(&globalCtx->animationCtx, ANIMATION_TYPE4);

    if (entry != NULL) {
        entry->types.type4.unk00 = D_801F5AB0;
        entry->types.type4.vecCount = vecCount;
        entry->types.type4.dst = dst;
        entry->types.type4.src = src;
        entry->types.type4.index = index;
    }
}

void SkelAnime_LoadAnimationType5(GlobalContext* globalCtx, Actor* actor, SkelAnime* skelAnime, f32 arg3) {
    AnimationEntry* entry = SkelAnime_NextEntry(&globalCtx->animationCtx, ANIMATION_TYPE5);

    if (entry != NULL) {
        entry->types.type5.actor = actor;
        entry->types.type5.skelAnime = skelAnime;
        entry->types.type5.unk08 = arg3;
    }
}

/* The next functions are callbacks to loading animations */

void SkelAnime_LinkAnimetionLoaded(GlobalContext* globalCtx, AnimationEntryType0* entry) {
    osRecvMesg(&entry->msgQueue, NULL, OS_MESG_BLOCK);
}

void SkelAnime_AnimationType1Loaded(GlobalContext* globalCtx, AnimationEntryType1* entry) {
    s32 i;
    Vec3s* dst;
    Vec3s* src;
    AnimationEntryRaw* genericEntry = (AnimationEntryRaw*)entry;

    if ((genericEntry->raw[0] & D_801F5AB4) != 0) {
        return;
    }

    for (dst = entry->dst, src = entry->src, i = 0; i < genericEntry->raw[1]; i++) {
        *dst++ = *src++;
    }
}

void SkelAnime_AnimationType2Loaded(GlobalContext* globalCtx, AnimationEntryType2* entry) {
    if ((entry->unk00 & D_801F5AB4) == 0) {
        SkelAnime_InterpolateVec3s(entry->limbCount, entry->unk04, entry->unk04, entry->unk08, entry->unk0C);
    }
}

void SkelAnime_AnimationType3Loaded(GlobalContext* globalCtx, AnimationEntryType3* entry) {
    s32 i;
    Vec3s* dst;
    Vec3s* src;
    u8* index;
    AnimationEntryRaw* rawEntry = (AnimationEntryRaw*)entry;

    if ((rawEntry->raw[0] & D_801F5AB4) == 0) {
        for (dst = entry->dst, src = entry->src, index = entry->index, i = 0; i < rawEntry->raw[1]; i++, dst++, src++) {
            if (*index++) {
                *dst = *src;
            }
        }
    }
}

void SkelAnime_AnimationType4Loaded(GlobalContext* globalCtx, AnimationEntryType4* entry) {
    s32 i;
    Vec3s* dst;
    Vec3s* src;
    u8* index;
    AnimationEntryRaw* rawEntry = (AnimationEntryRaw*)entry;

    if ((rawEntry->raw[0] & D_801F5AB4) == 0) {
        for (dst = entry->dst, src = entry->src, index = entry->index, i = 0; i < rawEntry->raw[1]; i++, dst++, src++) {
            if (*index++ < 1U) {
                *dst = *src;
            }
        }
    }
}

void SkelAnime_AnimationType5Loaded(GlobalContext* globalCtx, AnimationEntryType5* entry) {
    s32 pad;
    Actor* actor = entry->actor;
    Vec3f pos;

    func_80137748(entry->skelAnime, &pos, actor->shape.rot.y);
    actor->world.pos.x += (pos.x * actor->scale.x) * entry->unk08;
    actor->world.pos.y += (pos.y * actor->scale.y) * entry->unk08;
    actor->world.pos.z += (pos.z * actor->scale.z) * entry->unk08;
}

void func_80135EE8(GlobalContext* globalCtx, AnimationContext* animationCtx) {
    AnimationEntry* entry = animationCtx->entries;

    for (; animationCtx->animationCount != 0; entry++, animationCtx->animationCount--) {
        sAnimationLoadDone[entry->type](globalCtx, &entry->types);
    }

    D_801F5AB0 = 1;
    D_801F5AB4 = 0;
}

void SkelAnime_InitLinkAnimetion(GlobalContext* globalCtx, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                                 LinkAnimationHeader* linkAnimationHeaderSeg, s32 flags, Vec3s* limbDrawTbl,
                                 Vec3s* transitionDrawTbl, s32 limbBufCount) {
    FlexSkeletonHeader* skeletonHeader;
    s32 headerCount;
    s32 limbCount;
    u32 allocSize;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    headerCount = skeletonHeader->sh.limbCount;
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
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->sh.skeletonSeg);
    allocSize = sizeof(Vec3s) * limbCount;

    if (flags & 8) {
        allocSize += 2;
    }

    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl = zelda_malloc(allocSize);
        skelAnime->transitionDrawTbl = zelda_malloc(allocSize);
    } else {
        skelAnime->limbDrawTbl = (Vec3s*)ALIGN16((u32)limbDrawTbl);
        skelAnime->transitionDrawTbl = (Vec3s*)ALIGN16((u32)transitionDrawTbl);
    }

    SkelAnime_ChangeLinkAnim(globalCtx, skelAnime, linkAnimationHeaderSeg, 1.0f, 0.0f, 0.0f, 0, 0.0f);
}

void func_801360A8(SkelAnime* skelAnime) {
    if (skelAnime->mode < 2) {
        skelAnime->animUpdate = func_80136288;
    } else {
        skelAnime->animUpdate = func_8013631C;
    }
    skelAnime->transCurrentFrame = 0.0f;
}

s32 func_801360E0(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    return skelAnime->animUpdate(globalCtx, skelAnime);
}

s32 func_80136104(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 prevUnk28 = skelAnime->transCurrentFrame;
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
    if (skelAnime->transCurrentFrame <= 0.0f) {
        func_801360A8(skelAnime);
    }

    SkelAnime_LoadAnimationType2(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl,
                                 1.0f - (skelAnime->transCurrentFrame / prevUnk28));
    return 0;
}

void func_801361BC(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    SkelAnime_LoadLinkAnimetion(globalCtx, skelAnime->linkAnimetionSeg, skelAnime->animCurrentFrame,
                                skelAnime->limbCount, skelAnime->limbDrawTbl);
    if (skelAnime->transCurrentFrame != 0) {
        f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;
        skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
        if (skelAnime->transCurrentFrame <= 0.0f) {
            skelAnime->transCurrentFrame = 0.0f;
        } else {
            SkelAnime_LoadAnimationType2(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl,
                                         skelAnime->transitionDrawTbl, skelAnime->transCurrentFrame);
        }
    }
}

s32 func_80136288(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;
    if (skelAnime->animCurrentFrame < 0.0f) {
        skelAnime->animCurrentFrame += skelAnime->totalFrames;
    } else if (skelAnime->totalFrames <= skelAnime->animCurrentFrame) {
        skelAnime->animCurrentFrame -= skelAnime->totalFrames;
    }
    func_801361BC(globalCtx, skelAnime);
    return 0;
}

s32 func_8013631C(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;

    if (skelAnime->animCurrentFrame == skelAnime->animFrameCount) {
        func_801361BC(globalCtx, skelAnime);
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
    func_801361BC(globalCtx, skelAnime);
    return 0;
}

void SkelAnime_SetTransition(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 transitionRate) {
    skelAnime->transCurrentFrame = 1.0f;
    skelAnime->transitionStep = 1.0f / transitionRate;
}

void SkelAnime_ChangeLinkAnim(GlobalContext* globalCtx, SkelAnime* skelAnime,
                              LinkAnimationHeader* linkAnimationHeaderSeg, f32 playbackSpeed, f32 frame, f32 frameCount,
                              u8 animationMode, f32 transitionRate) {
    skelAnime->mode = animationMode;
    if ((transitionRate != 0.0f) &&
        ((linkAnimationHeaderSeg != skelAnime->linkAnimetionSeg) || (frame != skelAnime->animCurrentFrame))) {
        if (transitionRate < 0) {
            func_801360A8(skelAnime);
            SkelAnime_CopyVec3s(skelAnime, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
            transitionRate = -transitionRate;
        } else {
            skelAnime->animUpdate = func_80136104;
            SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimationHeaderSeg, (s32)frame, skelAnime->limbCount,
                                        skelAnime->transitionDrawTbl);
        }
        skelAnime->transCurrentFrame = 1.0f;
        skelAnime->transitionStep = 1.0f / transitionRate;
    } else {
        func_801360A8(skelAnime);
        SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimationHeaderSeg, (s32)frame, skelAnime->limbCount,
                                    skelAnime->limbDrawTbl);
        skelAnime->transCurrentFrame = 0.0f;
    }

    skelAnime->linkAnimetionSeg = linkAnimationHeaderSeg;
    skelAnime->animCurrentFrame = 0.0f;
    skelAnime->initialFrame = frame;
    skelAnime->animCurrentFrame = frame;
    skelAnime->animFrameCount = frameCount;
    skelAnime->totalFrames = SkelAnime_GetTotalFrames(&linkAnimationHeaderSeg->common);
    skelAnime->animPlaybackSpeed = playbackSpeed;
}

void SkelAnime_ChangeLinkAnimDefaultStop(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                         LinkAnimationHeader* linkAnimationHeaderSeg) {
    SkelAnime_ChangeLinkAnim(globalCtx, skelAnime, linkAnimationHeaderSeg, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&linkAnimationHeaderSeg->common), 2, 0.0f);
}

void SkelAnime_ChangeLinkAnimPlaybackStop(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                          LinkAnimationHeader* linkAnimationHeaderSeg, f32 playbackSpeed) {
    SkelAnime_ChangeLinkAnim(globalCtx, skelAnime, linkAnimationHeaderSeg, playbackSpeed, 0.0f,
                             SkelAnime_GetFrameCount(&linkAnimationHeaderSeg->common), 2, 0.0f);
}

void SkelAnime_ChangeLinkAnimDefaultRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                           LinkAnimationHeader* linkAnimationHeaderSeg) {
    SkelAnime_ChangeLinkAnim(globalCtx, skelAnime, linkAnimationHeaderSeg, 1.0f, 0.0f,
                             SkelAnime_GetFrameCount(&linkAnimationHeaderSeg->common), 0, 0.0f);
}

void SkelAnime_ChangeLinkAnimPlaybackRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                            LinkAnimationHeader* linkAnimationHeaderSeg, f32 playbackSpeed) {
    SkelAnime_ChangeLinkAnim(globalCtx, skelAnime, linkAnimationHeaderSeg, playbackSpeed, 0.0f,
                             SkelAnime_GetFrameCount(&linkAnimationHeaderSeg->common), 0, 0.0f);
}

void func_8013670C(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    SkelAnime_LoadAnimationType1(globalCtx, skelAnime->limbCount, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
}

void func_8013673C(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    SkelAnime_LoadAnimationType1(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl);
}

void func_8013676C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 frame) {
    SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimationHeaderSeg, (s32)frame, skelAnime->limbCount,
                                skelAnime->transitionDrawTbl);
}

void func_801367B0(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 frame) {
    SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimationHeaderSeg, (s32)frame, skelAnime->limbCount,
                                skelAnime->limbDrawTbl);
}

void func_801367F4(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 frame) {
    SkelAnime_LoadAnimationType2(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl,
                                 frame);
}

void func_8013682C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 transitionFrame, LinkAnimationHeader* LinkAnimationHeaderSeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl) {
    Vec3s* alignedLimbDrawTbl;
    SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimationHeaderSeg, (s32)transitionFrame, skelAnime->limbCount,
                                skelAnime->limbDrawTbl);

    alignedLimbDrawTbl = (Vec3s*)ALIGN16((u32)limbDrawTbl);

    SkelAnime_LoadLinkAnimetion(globalCtx, LinkAnimationHeaderSeg2, (s32)frame, skelAnime->limbCount,
                                alignedLimbDrawTbl);
    SkelAnime_LoadAnimationType2(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, alignedLimbDrawTbl,
                                 transitionRate);
}

void func_801368CC(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 transitionFrame, LinkAnimationHeader* LinkAnimationHeaderSeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl) {
    Vec3s* alignedLimbDrawTbl;

    SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimationHeaderSeg, (s32)transitionFrame, skelAnime->limbCount,
                                skelAnime->transitionDrawTbl);

    alignedLimbDrawTbl = (Vec3s*)ALIGN16((u32)limbDrawTbl);

    SkelAnime_LoadLinkAnimetion(globalCtx, LinkAnimationHeaderSeg2, (s32)frame, skelAnime->limbCount,
                                alignedLimbDrawTbl);
    SkelAnime_LoadAnimationType2(globalCtx, skelAnime->limbCount, skelAnime->transitionDrawTbl, alignedLimbDrawTbl,
                                 transitionRate);
}

void SkelAnime_SetModeStop(SkelAnime* skelAnime) {
    skelAnime->mode = 2;
    func_801360A8(skelAnime);
}

s32 func_80136990(SkelAnime* skelAnime, f32 arg1, f32 updateRate) {
    f32 updateSpeed;
    f32 temp_f12;
    f32 nextFrame;

    updateSpeed = skelAnime->animPlaybackSpeed * updateRate;
    nextFrame = skelAnime->animCurrentFrame - updateSpeed;
    if (nextFrame < 0.0f) {
        nextFrame += skelAnime->totalFrames;
    } else if (skelAnime->totalFrames <= nextFrame) {
        nextFrame -= skelAnime->totalFrames;
    }

    if ((arg1 == 0.0f) && (updateSpeed > 0.0f)) {
        arg1 = skelAnime->totalFrames;
    }

    temp_f12 = (nextFrame + updateSpeed) - arg1;
    if ((0.0f <= (temp_f12 * updateSpeed)) && (((temp_f12 - updateSpeed) * updateSpeed) < 0.0f)) {
        return 1;
    }
    return 0;
}

s32 func_80136A48(SkelAnime* skelAnime, f32 arg1) {
    f32 updateRate = gFramerateDivisorHalf;

    return func_80136990(skelAnime, arg1, updateRate);
}

void SkelAnime_Init(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                    AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->skeletonSeg);
    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl = zelda_malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);
        skelAnime->transitionDrawTbl = zelda_malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);
    } else {
        skelAnime->limbDrawTbl = limbDrawTbl;
        skelAnime->transitionDrawTbl = transitionDrawTable;
    }

    if (animationSeg != NULL) {
        SkelAnime_ChangeAnimDefaultRepeat(skelAnime, animationSeg);
    }
}

void SkelAnime_InitSV(GlobalContext* globalCtx, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                      AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount) {
    FlexSkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->sh.limbCount + 1;
    skelAnime->dListCount = skeletonHeader->dListCount;
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->sh.skeletonSeg);

    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl = zelda_malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);

        skelAnime->transitionDrawTbl = zelda_malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);
    } else {
        skelAnime->limbDrawTbl = limbDrawTbl;
        skelAnime->transitionDrawTbl = transitionDrawTable;
    }

    if (animationSeg != NULL) {
        SkelAnime_ChangeAnimDefaultRepeat(skelAnime, animationSeg);
    }
}

void SkelAnime_InitSkin(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animationSeg) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_SegmentedToVirtual(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_SegmentedToVirtual(skeletonHeader->skeletonSeg);
    skelAnime->limbDrawTbl = zelda_malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);
    skelAnime->transitionDrawTbl = zelda_malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);

    // Debug prints here, required to match.
    if (1) {};

    if (animationSeg != NULL) {
        SkelAnime_ChangeAnimDefaultRepeat(skelAnime, animationSeg);
    }
}

void func_80136C84(SkelAnime* skelAnime) {
    if (skelAnime->mode < 2) {
        skelAnime->animUpdate = func_8013702C;
    } else if (skelAnime->mode < 4) {
        skelAnime->animUpdate = func_8013713C;
    } else {
        skelAnime->animUpdate = func_801370B0;
    }
}

s32 SkelAnime_FrameUpdateMatrix(SkelAnime* skelAnime) {
    return skelAnime->animUpdate(skelAnime);
}

s32 func_80136CF4(SkelAnime* skelAnime) {
    f32 prevUnk28 = skelAnime->transCurrentFrame;
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
    if (skelAnime->transCurrentFrame <= 0.0f) {
        func_80136C84(skelAnime);
        skelAnime->transCurrentFrame = 0.0f;
    }
    SkelAnime_InterpolateVec3s(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
                               skelAnime->transitionDrawTbl, 1.0f - (skelAnime->transCurrentFrame / prevUnk28));
    return 0;
}

s32 func_80136D98(SkelAnime* skelAnime) {
    s16 temp_a2 = (s16)(skelAnime->transCurrentFrame * 16384.0f);
    s16 temp_a1;
    f32 sp28;
    f32 phi_f2;
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
    if (skelAnime->transCurrentFrame <= 0.0f) {
        func_80136C84(skelAnime);
        skelAnime->transCurrentFrame = 0.0f;
    }
    temp_a1 = (s16)(skelAnime->transCurrentFrame * 16384.0f);
    if (skelAnime->unk03 < 0) {
        sp28 = 1.0f - Math_CosS(temp_a2);
        phi_f2 = 1.0f - Math_CosS(temp_a1);
    } else {
        sp28 = Math_SinS(temp_a2);
        phi_f2 = Math_SinS(temp_a1);
    }
    if (phi_f2 != 0.0f) {
        phi_f2 /= sp28;
    } else {
        phi_f2 = 0.0f;
    }
    SkelAnime_InterpolateVec3s(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
                               skelAnime->transitionDrawTbl, 1.0f - phi_f2);
    return 0;
}

void func_80136F04(SkelAnime* skelAnime) {
    s32 t;
    s32 pad[2];
    Vec3s sp38[98];
    f32 temp_f10;
    f32 temp_f2;

    SkelAnime_AnimateFrame(skelAnime->animCurrentSeg, skelAnime->animCurrentFrame, skelAnime->limbCount,
                           skelAnime->limbDrawTbl);
    if (skelAnime->mode & 0x1) {
        t = (s32)skelAnime->animCurrentFrame;
        temp_f10 = t;
        temp_f2 = skelAnime->animCurrentFrame - temp_f10;
        t++;
        if (t >= (s32)skelAnime->totalFrames) {
            t = 0;
        }
        SkelAnime_AnimateFrame(skelAnime->animCurrentSeg, t, skelAnime->limbCount, sp38);
        SkelAnime_InterpolateVec3s(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl, sp38, temp_f2);
    }
    if (skelAnime->transCurrentFrame != 0) {
        f32 updateRate = gFramerateDivisorThird;
        skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
        if (skelAnime->transCurrentFrame <= 0.0f) {
            skelAnime->transCurrentFrame = 0.0f;
            return;
        }
        SkelAnime_InterpolateVec3s(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
                                   skelAnime->transitionDrawTbl, skelAnime->transCurrentFrame);
    }
}

s32 func_8013702C(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;
    if (skelAnime->animCurrentFrame < 0.0f) {
        skelAnime->animCurrentFrame += skelAnime->totalFrames;
    } else if (skelAnime->totalFrames <= skelAnime->animCurrentFrame) {
        skelAnime->animCurrentFrame -= skelAnime->totalFrames;
    }

    func_80136F04(skelAnime);
    return 0;
}

s32 func_801370B0(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    skelAnime->animCurrentFrame += skelAnime->animPlaybackSpeed * updateRate;
    if (skelAnime->animCurrentFrame < skelAnime->initialFrame) {
        skelAnime->animCurrentFrame =
            (skelAnime->animCurrentFrame - skelAnime->initialFrame) + skelAnime->animFrameCount;
    } else if (skelAnime->animFrameCount <= skelAnime->animCurrentFrame) {
        skelAnime->animCurrentFrame =
            (skelAnime->animCurrentFrame - skelAnime->animFrameCount) + skelAnime->initialFrame;
    }

    func_80136F04(skelAnime);
    return 0;
}

s32 func_8013713C(SkelAnime* skelAnime) {
    f32 updateRate = gFramerateDivisorThird;

    if (skelAnime->animCurrentFrame == skelAnime->animFrameCount) {
        SkelAnime_AnimateFrame(skelAnime->animCurrentSeg, (s32)skelAnime->animCurrentFrame, skelAnime->limbCount,
                               skelAnime->limbDrawTbl);
        func_80136F04(skelAnime);
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
    func_80136F04(skelAnime);
    return 0;
}

void SkelAnime_ChangeAnimImpl(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                              f32 frameCount, u8 animationType, f32 transitionRate, s8 unk2) {
    skelAnime->mode = animationType;
    if ((transitionRate != 0.0f) &&
        ((animationSeg != skelAnime->animCurrentSeg) || (frame != skelAnime->animCurrentFrame))) {
        if (transitionRate < 0) {
            func_80136C84(skelAnime);
            SkelAnime_CopyVec3s(skelAnime, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
            transitionRate = -transitionRate;
        } else {
            if (unk2 != 0) {
                skelAnime->animUpdate = func_80136D98;
                skelAnime->unk03 = unk2;
            } else {
                skelAnime->animUpdate = func_80136CF4;
            }
            SkelAnime_AnimateFrame(animationSeg, frame, skelAnime->limbCount, skelAnime->transitionDrawTbl);
        }
        skelAnime->transCurrentFrame = 1.0f;
        skelAnime->transitionStep = 1.0f / transitionRate;
    } else {
        func_80136C84(skelAnime);
        SkelAnime_AnimateFrame(animationSeg, frame, skelAnime->limbCount, skelAnime->limbDrawTbl);
        skelAnime->transCurrentFrame = 0.0f;
    }

    skelAnime->animCurrentSeg = animationSeg;
    skelAnime->initialFrame = frame;
    skelAnime->animFrameCount = frameCount;
    skelAnime->totalFrames = SkelAnime_GetTotalFrames(&animationSeg->common);
    if (skelAnime->mode >= 4) {
        skelAnime->animCurrentFrame = 0.0f;
    } else {
        skelAnime->animCurrentFrame = frame;
        if (skelAnime->mode < 2) {
            skelAnime->animFrameCount = skelAnime->totalFrames - 1.0f;
        }
    }
    skelAnime->animPlaybackSpeed = playbackSpeed;
}

void SkelAnime_ChangeAnim(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                          f32 frameCount, u8 mode, f32 transitionRate) {
    SkelAnime_ChangeAnimImpl(skelAnime, animationSeg, playbackSpeed, frame, frameCount, mode, transitionRate, 0);
}

void SkelAnime_ChangeAnimDefaultStop(SkelAnime* skelAnime, AnimationHeader* animationSeg) {
    SkelAnime_ChangeAnim(skelAnime, animationSeg, 1.0f, 0.0f, SkelAnime_GetFrameCount(&animationSeg->common), 2, 0.0f);
}

void SkelAnime_ChangeAnimTransitionStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate) {
    SkelAnime_ChangeAnim(skelAnime, animationSeg, 1.0f, 0, SkelAnime_GetFrameCount(&animationSeg->common), 2,
                         transitionRate);
}

void SkelAnime_ChangeAnimPlaybackStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed) {
    SkelAnime_ChangeAnim(skelAnime, animationSeg, playbackSpeed, 0.0f, SkelAnime_GetFrameCount(&animationSeg->common),
                         2, 0.0f);
}

void SkelAnime_ChangeAnimDefaultRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg) {
    SkelAnime_ChangeAnim(skelAnime, animationSeg, 1.0f, 0.0f, SkelAnime_GetFrameCount(&animationSeg->common), 0, 0.0f);
}

void SkelAnime_ChangeAnimTransitionRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate) {
    SkelAnime_ChangeAnim(skelAnime, animationSeg, 1.0f, 0.0f, 0.0f, 0, transitionRate);
}

void SkelAnime_ChangeAnimPlaybackRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed) {
    SkelAnime_ChangeAnim(skelAnime, animationSeg, playbackSpeed, 0.0f, SkelAnime_GetFrameCount(&animationSeg->common),
                         0, 0.0f);
}

void SkelAnime_AnimSetStop(SkelAnime* skelAnime) {
    skelAnime->mode = 2;
    skelAnime->animFrameCount = skelAnime->totalFrames;
    func_80136C84(skelAnime);
}

void SkelAnime_AnimReverse(SkelAnime* skelAnime) {
    f32 initialFrame = skelAnime->initialFrame;

    skelAnime->initialFrame = skelAnime->animFrameCount;
    skelAnime->animPlaybackSpeed = -skelAnime->animPlaybackSpeed;
    skelAnime->animFrameCount = initialFrame;
}

void func_80137674(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* index) {
    s32 i;

    for (i = 0; i < skelAnime->limbCount; i++, dst++, src++) {
        if (*index++) {
            *dst = *src;
        }
    }
}

void func_801376DC(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* arg3) {
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
void func_80137748(SkelAnime* skelAnime, Vec3f* pos, s16 angle) {
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

s32 func_801378B8(SkelAnime* skelAnime, f32 arg1) {
    return func_80136990(skelAnime, arg1, 1.0f);
}

void SkelAnime_Free(SkelAnime* skelAnime, GlobalContext* globalCtx) {
    if (skelAnime->limbDrawTbl != NULL) {
        zelda_free(skelAnime->limbDrawTbl);
    }

    if (skelAnime->transitionDrawTbl != NULL) {
        zelda_free(skelAnime->transitionDrawTbl);
    }
}

void SkelAnime_CopyVec3s(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src) {
    bcopy(src, dst, sizeof(Vec3s) * skelAnime->limbCount);
}
