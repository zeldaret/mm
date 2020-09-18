#include <ultra64.h>
#include <global.h>

s32 func_80136288(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_8013631C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_8013792C(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);
void func_80137540(SkelAnime* skelAnime, AnimationHeader* animationSeg);
s32 func_8013702C(SkelAnime* skelAnime);
s32 func_801370B0(SkelAnime* skelAnime);
s32 func_8013713C(SkelAnime* skelAnime);
void func_80137748(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
void func_80136414(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                              f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationMode, f32 transitionRate);

// .data
u32 D_801F5AB4 = 0;
static AnimationEntryCallback sAnimationLoadDone[] = {
    func_80135C3C, func_80135C6C, func_80135CDC,
    func_80135D38, func_80135DB8, func_80135E3C,
};

// .bss
u32 D_801F5AB0;

// SkelAnime_LodDrawLimb
void func_801330E0(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex) {
    SkelLimbEntry* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    SysMatrix_StatePush();
    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[limbIndex]);
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

            gSPMatrix(polyTemp, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
                      G_MTX_LOAD);

            gSPDisplayList(polyTemp + 1, dList);
            gfxCtx->polyOpa.p = polyTemp + 2;
        }
    }


    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        func_801330E0(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                              postLimbDraw, actor, dListIndex);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        func_801330E0(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                              postLimbDraw, actor, dListIndex);
    }
}

// SkelAnime_LodDraw
void func_801332F0(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                       OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex) {
    SkelLimbEntry* limbEntry;
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

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);
    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;

    rot = limbDrawTable[1];
    dList = limbEntry->displayLists[dListIndex];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, actor) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList != NULL) {
            Gfx* polyTemp = gfxCtx->polyOpa.p;

            gSPMatrix(polyTemp, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
                      G_MTX_LOAD);

            gSPDisplayList(polyTemp + 1, dList);

            gfxCtx->polyOpa.p = polyTemp + 2;
        }
    }
    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor);
    }

    if (limbEntry->firstChildIndex != 0xFF) {
        func_801330E0(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                              postLimbDraw, actor, dListIndex);
    }

    SysMatrix_StatePop();

}

// SkelAnime_LodDrawLimbSV
void func_801334A0(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                             OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor, s32 dListIndex,
                             RSPMatrix** mtx) {
    SkelLimbEntry* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    SysMatrix_StatePush();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[limbIndex]);
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
        func_801334A0(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                postLimbDraw, actor, dListIndex, mtx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        func_801334A0(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                postLimbDraw, actor, dListIndex, mtx);
    }
}

// SkelAnime_LodDrawSV
void func_80133710(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                         OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor, s32 dListIndex) {
    SkelLimbEntry* limbEntry;
    s32 pad;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    RSPMatrix* mtx;
    GraphicsContext* gfxCtx;

    mtx = (RSPMatrix*)GRAPH_ALLOC(globalCtx->state.gfxCtx, ALIGN16(sizeof(RSPMatrix) * dListCount));

    if (skeleton == NULL) {
        return;
    }

    gfxCtx = globalCtx->state.gfxCtx;

    gSPSegment(gfxCtx->polyOpa.p++, 0xD, mtx);
    SysMatrix_StatePush();

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
        func_801334A0(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                postLimbDraw, actor, dListIndex, &mtx);
    }

    SysMatrix_StatePop();
}

// SkelAnime_DrawLimb
void func_80133948(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor) {
    SkelLimbEntry* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;
    
    SysMatrix_StatePush();

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

            gSPMatrix(polyTemp, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
                      G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList);
            gfxCtx->polyOpa.p = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        func_80133948(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                           postLimbDraw, actor);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        func_80133948(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw, postLimbDraw,
                           actor);
    }

}

// SkelAnime_Draw
void func_80133B3C(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                    OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor) {
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

    SysMatrix_StatePush();
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

            gSPMatrix(polyTemp, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
                      G_MTX_LOAD);
            gSPDisplayList(polyTemp + 1, dList);
            gfxCtx->polyOpa.p = polyTemp + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor);
    }

    if (rootLimb->firstChildIndex != LIMB_DONE) {
        func_80133948(globalCtx, rootLimb->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                           postLimbDraw, actor);
    }

    SysMatrix_StatePop();
}

// SkelAnime_DrawLimbSV
void func_80133CDC(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                          OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor,
                          RSPMatrix** limbMatricies) {
    SkelLimbEntry* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    SysMatrix_StatePush();

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
        func_80133CDC(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, limbMatricies);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        func_80133CDC(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, limbMatricies);
    }
}

// SkelAnime_DrawSV
void func_80133F28(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor) {
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

    SysMatrix_StatePush();

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
        func_80133CDC(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, actor, &mtx);
    }

    SysMatrix_StatePop();
}

void func_80134148(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable, 
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor,
                      RSPMatrix** mtx) { 
    SkelLimbEntry* limbEntry;
    Gfx* dList[2];
    Vec3f pos;
    Vec3s rot;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad2;

    SysMatrix_StatePush();

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
        func_80134148(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, unkDraw, actor, mtx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        func_80134148(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, unkDraw, actor, mtx);
    }
}

void func_801343C0(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor) {
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

    SysMatrix_StatePush();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);

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
        func_80134148(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                             postLimbDraw, unkDraw, actor, &mtx);
    }

    SysMatrix_StatePop();
}

// SkelAnime_AnimateFrame
void func_80134600(AnimationHeader* animationSeg, s32 currentFrame, s32 limbCount, Vec3s* dst) {
    AnimationHeader* animationHeader = Lib_PtrSegToVirt(animationSeg);
    AnimationRotationIndex* index = Lib_PtrSegToVirt(animationHeader->rotationIndexSeg);
    AnimationRotationValue* rotationValueTable = Lib_PtrSegToVirt(animationHeader->rotationValueSeg);
    AnimationRotationValue* frameRotationValueTable = &rotationValueTable[currentFrame];
    s32 i;
    u16 limit = animationHeader->limit;

    for (i = 0; i < limbCount; i++) {
        // Debug prints here, this needed to prevent loop unrolling
        if (0) {
            if (0){};
        }
        dst->x = index->x >= limit ? frameRotationValueTable[index->x] : rotationValueTable[index->x];
        dst->y = index->y >= limit ? frameRotationValueTable[index->y] : rotationValueTable[index->y];
        dst->z = index->z >= limit ? frameRotationValueTable[index->z] : rotationValueTable[index->z];
        index++, dst++;
    }
}

// SkelAnime_GetTotalFrames
s16 func_80134724(GenericAnimationHeader *animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);
    return animation->frameCount;
}

// SkelAnime_GetFrameCount
s16 func_80134748(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);
    // Loads an unsigned half for some reason.
    return (u16)animation->frameCount - 1;
}

// SkelAnime_Draw2Limb
Gfx* func_80134774(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                         OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    SkelLimbEntry* limbEntry;
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    SysMatrix_StatePush();

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
            gSPMatrix(gfx, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList);
            gfx = gfx + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, limbIndex, &dList, &rot, actor, &gfx);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        gfx = func_80134774(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        gfx = func_80134774(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    return gfx;
}

// SkelAnime_Draw2
Gfx* func_80134990(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable,
                     OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx) {
    SkelLimbEntry* limbEntry;
    char pad[4];
    Gfx* dList;
    Vec3f pos;
    Vec3s rot;

    if (skeleton == NULL) {
        return NULL;
    }

    SysMatrix_StatePush();

    limbEntry = Lib_PtrSegToVirt(skeleton->limbs[0]);

    pos.x = limbDrawTable[0].x;
    pos.y = limbDrawTable[0].y;
    pos.z = limbDrawTable[0].z;

    rot = limbDrawTable[1];

    dList = limbEntry->displayLists[0];

    if ((overrideLimbDraw == NULL) || (overrideLimbDraw(globalCtx, 1, &dList, &pos, &rot, actor, &gfx) == 0)) {
        SysMatrix_RotateAndTranslateState(&pos, &rot);
        if (dList != NULL) {
            gSPMatrix(gfx, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx), G_MTX_LOAD);
            gSPDisplayList(gfx + 1, dList);
            gfx = gfx + 2;
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, 1, &dList, &rot, actor, &gfx);
    }

    if (limbEntry->firstChildIndex != LIMB_DONE) {
        gfx = func_80134774(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                  postLimbDraw, actor, gfx);
    }

    SysMatrix_StatePop();

    return gfx;
}

// SkelAnime_DrawLimbSV2
Gfx* func_80134B54(GlobalContext* globalCtx, s32 limbIndex, Skeleton* skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, RSPMatrix** mtx,
                           Gfx* gfx) {
    SkelLimbEntry* limbEntry;
    Gfx* dList1;
    Gfx* dList2;
    Vec3f pos;
    Vec3s rot;

    SysMatrix_StatePush();

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
        gfx = func_80134B54(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, mtx, gfx);
    }

    SysMatrix_StatePop();

    if (limbEntry->nextLimbIndex != LIMB_DONE) {
        gfx = func_80134B54(globalCtx, limbEntry->nextLimbIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, mtx, gfx);
    }

    return gfx;
}

// SkelAnime_DrawSV2
Gfx* func_80134DBC(GlobalContext* globalCtx, Skeleton* skeleton, Vec3s* limbDrawTable, s32 dListCount,
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
    SysMatrix_StatePush();
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
        gfx = func_80134B54(globalCtx, limbEntry->firstChildIndex, skeleton, limbDrawTable, overrideLimbDraw,
                                    postLimbDraw, actor, &mtx, gfx);
    }

    SysMatrix_StatePop();

    return gfx;
}

// Unused
GLOBAL_ASM("asm/non_matchings/z_skelanime/func_80134FFC.asm")

s16 func_801353D4(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);

    return animation->unk_02;
}

// SkelAnime_GetTotalFrames2
s16 func_801353F8(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);

    return animation->frameCount;
}

// SkelAnime_GetFrameCount2
s16 func_8013541C(GenericAnimationHeader* animationSeg) {
    GenericAnimationHeader* animation = Lib_PtrSegToVirt(animationSeg);

    return animation->frameCount - 1;
}

// SkelAnime_InterpolateVec3s
void func_80135448(s32 limbCount, Vec3s* dst, Vec3s* vec2, Vec3s* vec3, f32 unkf) {
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

// SkelAnime_AnimationCtxReset
void func_801358C8(AnimationContext* animationCtx) {
    animationCtx->animationCount = 0;
}

void func_801358D4(GlobalContext *globalCtx) {
    D_801F5AB0 *= 2;
}

void func_801358F4(GlobalContext *globalCtx) {
    D_801F5AB4 |= D_801F5AB0;
}

// SkelAnime_NextEntry
AnimationEntry* func_8013591C(AnimationContext* animationCtx, AnimationType type) {
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

// SkelAnime_LoadLinkAnimetion
void func_80135954(GlobalContext* globalCtx, LinkAnimetionEntry* linkAnimetionSeg, s32 frame,
                                 s32 limbCount, void* ram) {
    AnimationEntry* entry;
    LinkAnimetionEntry* linkAnimetionEntry;
    s32 pad;

    entry = func_8013591C(&globalCtx->animationCtx, ANIMATION_LINKANIMETION);

    if (entry != NULL) {
        linkAnimetionEntry = Lib_PtrSegToVirt(linkAnimetionSeg);
        osCreateMesgQueue(&entry->types.type0.msgQueue, &entry->types.type0.msg, 1);
        DmaMgr_SendRequestImpl(
            &entry->types.type0.req, ram,
            LINK_ANIMETION_OFFSET(linkAnimetionEntry->animationSegAddress, (sizeof(Vec3s) * limbCount + 2) * frame),
            sizeof(Vec3s) * limbCount + 2, 0, 
            &entry->types.type0.msgQueue, NULL);
    }
}

// SkelAnime_LoadAnimationType1
void func_80135A28(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src) {
    AnimationEntry* entry = func_8013591C(&globalCtx->animationCtx, ANIMATION_TYPE1);
    if (entry != NULL) {
        entry->types.type1.unk_00 = D_801F5AB0;
        entry->types.type1.vecCount = vecCount;
        entry->types.type1.dst = dst;
        entry->types.type1.src = src;
    }
}

// SkelAnime_LoadAnimationType2
void func_80135A90(GlobalContext* globalCtx, s32 limbCount, Vec3s* arg2, Vec3s* arg3, f32 arg4) {
    AnimationEntry* entry = func_8013591C(&globalCtx->animationCtx, ANIMATION_TYPE2);
    if (entry != NULL) {
        entry->types.type2.unk_00 = D_801F5AB0;
        entry->types.type2.limbCount = limbCount;
        entry->types.type2.unk_04 = arg2;
        entry->types.type2.unk_08 = arg3;
        entry->types.type2.unk_0C = arg4;
    }
}

// SkelAnime_LoadAnimationType3
void func_80135B00(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index) {
    AnimationEntry* entry = func_8013591C(&globalCtx->animationCtx, ANIMATION_TYPE3);
    if (entry != NULL) {
        entry->types.type3.unk_00 = D_801F5AB0;
        entry->types.type3.vecCount = vecCount;
        entry->types.type3.dst = dst;
        entry->types.type3.src = src;
        entry->types.type3.index = index;
    }
}

// SkelAnime_LoadAnimationType4 
void func_80135B70(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index) {
    AnimationEntry* entry = func_8013591C(&globalCtx->animationCtx, ANIMATION_TYPE4);
    if (entry != NULL) {
        entry->types.type4.unk_00 = D_801F5AB0;
        entry->types.type4.vecCount = vecCount;
        entry->types.type4.dst = dst;
        entry->types.type4.src = src;
        entry->types.type4.index = index;
    }
}

// SkelAnime_LoadAnimationType5
void func_80135BE0(GlobalContext* globalCtx, Actor* actor, SkelAnime* skelAnime, f32 arg3) {
    AnimationEntry* entry = func_8013591C(&globalCtx->animationCtx, ANIMATION_TYPE5);
    if (entry != NULL) {
        entry->types.type5.actor = actor;
        entry->types.type5.skelAnime = skelAnime;
        entry->types.type5.unk_08 = arg3;
    }
}

// SkelAnime_LinkAnimetionLoaded
void func_80135C3C(GlobalContext* globalCtx, AnimationEntryType0* entry) {
    osRecvMesg(&entry->msgQueue, NULL, OS_MESG_BLOCK);
}

// SkelAnime_AnimationType1Loaded
void func_80135C6C(GlobalContext* globalCtx, AnimationEntryType1* entry) {
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

// SkelAnime_AnimationType2Loaded
void func_80135CDC(GlobalContext* globalCtx, AnimationEntryType2* entry) {
    if ((entry->unk_00 & D_801F5AB4) == 0) {
        func_80135448(entry->limbCount, entry->unk_04, entry->unk_04, entry->unk_08, entry->unk_0C);
    }
}

// SkelAnime_AnimationType3Loaded
void func_80135D38(GlobalContext* globalCtx, AnimationEntryType3* entry) {
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

// SkelAnime_AnimationType4Loaded
void func_80135DB8(GlobalContext* globalCtx, AnimationEntryType4* entry) {
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

// SkelAnime_AnimationType5Loaded
void func_80135E3C(GlobalContext* globalCtx, AnimationEntryType5* entry) {
    s32 pad;
    Actor* actor = entry->actor;
    Vec3f pos;

    func_80137748(entry->skelAnime, &pos, actor->shape.rot.y);
    actor->currPosRot.pos.x += (pos.x * actor->scale.x) * entry->unk_08;
    actor->currPosRot.pos.y += (pos.y * actor->scale.y) * entry->unk_08;
    actor->currPosRot.pos.z += (pos.z * actor->scale.z) * entry->unk_08;
}

void func_80135EE8(GlobalContext* globalCtx, AnimationContext* animationCtx) {
    AnimationEntry* entry = animationCtx->entries;

    for (; animationCtx->animationCount != 0; entry++, animationCtx->animationCount--) {
        sAnimationLoadDone[entry->type](globalCtx, &entry->types);
    }

    D_801F5AB0 = 1;
    D_801F5AB4 = 0;
}

// SkelAnime_InitLinkAnimetion
void func_80135F88(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                                 LinkAnimetionEntry* linkAnimetionEntrySeg, s32 flags, Vec3s* limbDrawTbl,
                                 Vec3s* transitionDrawTbl, s32 limbBufCount) {
    SkeletonHeader* skeletonHeader;
    s32 headerCount;
    s32 limbCount;
    u32 allocSize;

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

    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl = zelda_malloc(allocSize);
        skelAnime->transitionDrawTbl = zelda_malloc(allocSize);
    } else {
        skelAnime->limbDrawTbl = (Vec3s*)ALIGN16((u32)limbDrawTbl);
        skelAnime->transitionDrawTbl = (Vec3s*)ALIGN16((u32)transitionDrawTbl);
    }

    func_80136414(globalCtx, skelAnime, linkAnimetionEntrySeg, 1.0f, 0.0f, 0.0f, 0, 0.0f);
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

    func_80135A90(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl,
                                 1.0f - (skelAnime->transCurrentFrame / prevUnk28));
    return 0;
}

void func_801361BC(GlobalContext* globalCtx, SkelAnime* skelAnime) {

    func_80135954(globalCtx, skelAnime->linkAnimetionSeg, skelAnime->animCurrentFrame,
                                skelAnime->limbCount, skelAnime->limbDrawTbl);
    if (skelAnime->transCurrentFrame != 0) {
        f32 updateRate = (s32)globalCtx->state.framerateDivisor * 0.5f;
        skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
        if (skelAnime->transCurrentFrame <= 0.0f) {
            skelAnime->transCurrentFrame = 0.0f;
        } else {
            func_80135A90(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl,
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

// SkelAnime_SetTransition
void func_801363F0(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 transitionRate) {
    skelAnime->transCurrentFrame = 1.0f;
    skelAnime->transitionStep = 1.0f / transitionRate;
}

// SkelAnime_ChangeLinkAnim
void func_80136414(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                              f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationMode, f32 transitionRate) {
    skelAnime->mode = animationMode;
    if ((transitionRate != 0.0f) &&
        ((linkAnimetionEntrySeg != skelAnime->linkAnimetionSeg) || (frame != skelAnime->animCurrentFrame))) {
        if (transitionRate < 0) {
            func_801360A8(skelAnime);
            func_8013792C(skelAnime, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
            transitionRate = -transitionRate;
        } else {
            skelAnime->animUpdate = func_80136104;
            func_80135954(globalCtx, linkAnimetionEntrySeg, (s32)frame, skelAnime->limbCount,
                                        skelAnime->transitionDrawTbl);
        }
        skelAnime->transCurrentFrame = 1.0f;
        skelAnime->transitionStep = 1.0f / transitionRate;
    } else {
        func_801360A8(skelAnime);
        func_80135954(globalCtx, linkAnimetionEntrySeg, (s32)frame, skelAnime->limbCount,
                                    skelAnime->limbDrawTbl);
        skelAnime->transCurrentFrame = 0.0f;
    }

    skelAnime->linkAnimetionSeg = linkAnimetionEntrySeg;
    skelAnime->animCurrentFrame = 0.0f;
    skelAnime->initialFrame = frame;
    skelAnime->animCurrentFrame = frame;
    skelAnime->animFrameCount = frameCount;
    skelAnime->totalFrames = func_80134724(linkAnimetionEntrySeg);
    skelAnime->animPlaybackSpeed = playbackSpeed;
}

// SkelAnime_ChangeLinkAnimDefaultStop
void func_8013658C(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                         LinkAnimetionEntry* linkAnimetionEntrySeg) {
    func_80136414(globalCtx, skelAnime, linkAnimetionEntrySeg, 1.0f, 0.0f,
                             func_80134748(&linkAnimetionEntrySeg->genericHeader), 2, 0.0f);
}

// SkelAnime_ChangeLinkAnimPlaybackStop
void func_801365EC(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                          LinkAnimetionEntry* linkAnimetionEntrySeg, f32 playbackSpeed) {
    func_80136414(globalCtx, skelAnime, linkAnimetionEntrySeg, playbackSpeed, 0.0f,
                             func_80134748(&linkAnimetionEntrySeg->genericHeader), 2, 0.0f);
}

// SkelAnime_ChangeLinkAnimDefaultRepeat
void func_80136650(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                           LinkAnimetionEntry* linkAnimetionEntrySeg) {
    func_80136414(globalCtx, skelAnime, linkAnimetionEntrySeg, 1.0f, 0.0f,
                             func_80134748(&linkAnimetionEntrySeg->genericHeader), 0, 0.0f);
}

// SkelAnime_ChangeLinkAnimPlaybackRepeat
void func_801366AC(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                            LinkAnimetionEntry* linkAnimetionEntrySeg, f32 playbackSpeed) {
    func_80136414(globalCtx, skelAnime, linkAnimetionEntrySeg, playbackSpeed, 0.0f,
                             func_80134748(&linkAnimetionEntrySeg->genericHeader), 0, 0.0f);
}

void func_8013670C(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    func_80135A28(globalCtx, skelAnime->limbCount, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
}

void func_8013673C(GlobalContext* globalCtx, SkelAnime* skelAnime) {
    func_80135A28(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl);
}

void func_8013676C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                   f32 frame) {
    func_80135954(globalCtx, linkAnimetionEntrySeg, (s32)frame, skelAnime->limbCount,
                                skelAnime->transitionDrawTbl);
}

void func_801367B0(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                   f32 frame) {
    func_80135954(globalCtx, linkAnimetionEntrySeg, (s32)frame, skelAnime->limbCount,
                                skelAnime->limbDrawTbl);
}

void func_801367F4(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 frame) {
    func_80135A90(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->transitionDrawTbl,
                                 frame);
}

void func_8013682C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                   f32 transitionFrame, LinkAnimetionEntry* linkAnimetionEntrySeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl) {
    Vec3s* alignedLimbDrawTbl;
    func_80135954(globalCtx, linkAnimetionEntrySeg, (s32)transitionFrame, skelAnime->limbCount,
                                skelAnime->limbDrawTbl);

    alignedLimbDrawTbl = (Vec3s*)ALIGN16((u32)limbDrawTbl);

    func_80135954(globalCtx, linkAnimetionEntrySeg2, (s32)frame, skelAnime->limbCount,
                                alignedLimbDrawTbl);
    func_80135A90(globalCtx, skelAnime->limbCount, skelAnime->limbDrawTbl, alignedLimbDrawTbl,
                                 transitionRate);
}

void func_801368CC(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimetionEntry* linkAnimetionEntrySeg,
                   f32 transitionFrame, LinkAnimetionEntry* linkAnimetionEntrySeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl) {
    Vec3s* alignedLimbDrawTbl;

    func_80135954(globalCtx, linkAnimetionEntrySeg, (s32)transitionFrame, skelAnime->limbCount,
                                skelAnime->transitionDrawTbl);

    alignedLimbDrawTbl = (Vec3s*)ALIGN16((u32)limbDrawTbl);

    func_80135954(globalCtx, linkAnimetionEntrySeg2, (s32)frame, skelAnime->limbCount,
                                alignedLimbDrawTbl);
    func_80135A90(globalCtx, skelAnime->limbCount, skelAnime->transitionDrawTbl, alignedLimbDrawTbl,
                                 transitionRate);
}

// SkelAnime_SetModeStop
void func_8013696C(SkelAnime* skelAnime) {
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

// SkelAnime_Init
void func_80136A7C(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                    AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_PtrSegToVirt(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_PtrSegToVirt(skeletonHeader->skeletonSeg);
    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl =
            zelda_malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);
        skelAnime->transitionDrawTbl = 
            zelda_malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);
    } else {
        skelAnime->limbDrawTbl = limbDrawTbl;
        skelAnime->transitionDrawTbl = transitionDrawTable;
    }

    if (animationSeg != NULL) {
        func_80137540(skelAnime, animationSeg);
    }
}

// SkelAnime_InitSV
void func_80136B30(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                      AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_PtrSegToVirt(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->dListCount = skeletonHeader->dListCount;
    skelAnime->skeleton = Lib_PtrSegToVirt(skeletonHeader->skeletonSeg);

    if (limbDrawTbl == NULL) {
        skelAnime->limbDrawTbl =
            zelda_malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);

        skelAnime->transitionDrawTbl = 
            zelda_malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);
    } else {
        skelAnime->limbDrawTbl = limbDrawTbl;
        skelAnime->transitionDrawTbl = transitionDrawTable;
    }

    if (animationSeg != NULL) {
        func_80137540(skelAnime, animationSeg);
    }
}

// SkelAnime_InitSkin
void func_80136BEC(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animationSeg) {
    SkeletonHeader* skeletonHeader;

    skeletonHeader = Lib_PtrSegToVirt(skeletonHeaderSeg);
    skelAnime->limbCount = skeletonHeader->limbCount + 1;
    skelAnime->skeleton = Lib_PtrSegToVirt(skeletonHeader->skeletonSeg);
    skelAnime->limbDrawTbl =
        zelda_malloc(sizeof(*skelAnime->limbDrawTbl) * skelAnime->limbCount);
    skelAnime->transitionDrawTbl =
        zelda_malloc(sizeof(*skelAnime->transitionDrawTbl) * skelAnime->limbCount);
    
    // Debug prints here, required to match.
    if (1){};

    if (animationSeg != NULL) {
        func_80137540(skelAnime, animationSeg);
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

// SkelAnime_FrameUpdateMatrix
s32 func_80136CD0(SkelAnime* skelAnime) {
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
    func_80135448(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
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
    if (skelAnime->unk_03 < 0) {
        sp28 = 1.0f - Math_Coss(temp_a2);
        phi_f2 = 1.0f - Math_Coss(temp_a1);
    } else {
        sp28 = Math_Sins(temp_a2);
        phi_f2 = Math_Sins(temp_a1);
    }
    if (phi_f2 != 0.0f) {
        phi_f2 /= sp28;
    } else {
        phi_f2 = 0.0f;
    }
    func_80135448(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
                               skelAnime->transitionDrawTbl, 1.0f - phi_f2);
    return 0;
}

void func_80136F04(SkelAnime* skelAnime) {
    s32 t;
    s32 pad[2];
    Vec3s sp38[98];
    f32 temp_f10;
    f32 temp_f2;

    func_80134600(skelAnime->animCurrentSeg, skelAnime->animCurrentFrame, skelAnime->limbCount,
                           skelAnime->limbDrawTbl);
    if (skelAnime->mode & 0x1) {
        t = (s32)skelAnime->animCurrentFrame;
        temp_f10 = t;
        temp_f2 = skelAnime->animCurrentFrame - temp_f10;
        t++;
        if (t >= (s32)skelAnime->totalFrames) {
            t = 0;
        }
        func_80134600(skelAnime->animCurrentSeg, t, skelAnime->limbCount, sp38);
        func_80135448(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl, sp38, temp_f2);
    }
    if (skelAnime->transCurrentFrame != 0) {
        f32 updateRate = gFramerateDivisorThird;
        skelAnime->transCurrentFrame -= skelAnime->transitionStep * updateRate;
        if (skelAnime->transCurrentFrame <= 0.0f) {
            skelAnime->transCurrentFrame = 0.0f;
            return;
        }
        func_80135448(skelAnime->limbCount, skelAnime->limbDrawTbl, skelAnime->limbDrawTbl,
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

        func_80134600(skelAnime->animCurrentSeg, (s32)skelAnime->animCurrentFrame, skelAnime->limbCount,
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

// SkelAnime_ChangeAnimImpl
void func_8013722C(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                              f32 frameCount, u8 animationType, f32 transitionRate, s8 unk2) {
    skelAnime->mode = animationType;
    if ((transitionRate != 0.0f) &&
        ((animationSeg != skelAnime->animCurrentSeg) || (frame != skelAnime->animCurrentFrame))) {
        if (transitionRate < 0) {
            func_80136C84(skelAnime);
            func_8013792C(skelAnime, skelAnime->transitionDrawTbl, skelAnime->limbDrawTbl);
            transitionRate = -transitionRate;
        } else {
            if (unk2 != 0) {
                skelAnime->animUpdate = func_80136D98;
                skelAnime->unk_03 = unk2;
            } else {
                skelAnime->animUpdate = func_80136CF4;
            }
            func_80134600(animationSeg, frame, skelAnime->limbCount, skelAnime->transitionDrawTbl);
        }
        skelAnime->transCurrentFrame = 1.0f;
        skelAnime->transitionStep = 1.0f / transitionRate;
    } else {
        func_80136C84(skelAnime);
        func_80134600(animationSeg, frame, skelAnime->limbCount, skelAnime->limbDrawTbl);
        skelAnime->transCurrentFrame = 0.0f;
    }

    skelAnime->animCurrentSeg = animationSeg;
    skelAnime->initialFrame = frame;
    skelAnime->animFrameCount = frameCount;
    skelAnime->totalFrames = func_80134724(&animationSeg->genericHeader);
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

// SkelAnime_ChangeAnim
void func_801373E8(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                          f32 frameCount, u8 mode, f32 transitionRate) {
    func_8013722C(skelAnime, animationSeg, playbackSpeed, frame, frameCount, mode, transitionRate, 0);
}

// SkelAnime_ChangeAnimDefaultStop
void func_80137430(SkelAnime* skelAnime, AnimationHeader* animationSeg) {
    func_801373E8(skelAnime, animationSeg, 1.0f, 0.0f, func_80134748(&animationSeg->genericHeader), 2,
                         0.0f);
}

// SkelAnime_ChangeAnimTransitionStop
void func_80137488(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate) {
    func_801373E8(skelAnime, animationSeg, 1.0f, 0, func_80134748(&animationSeg->genericHeader), 2,
                         transitionRate);
}

// SkelAnime_ChangeAnimPlaybackStop
void func_801374E4(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed) {
    func_801373E8(skelAnime, animationSeg, playbackSpeed, 0.0f,
                         func_80134748(&animationSeg->genericHeader), 2, 0.0f);
}

// SkelAnime_ChangeAnimDefaultRepeat
void func_80137540(SkelAnime* skelAnime, AnimationHeader* animationSeg) {
    func_801373E8(skelAnime, animationSeg, 1.0f, 0.0f, func_80134748(&animationSeg->genericHeader), 0,
                         0.0f);
}

// SkelAnime_ChangeAnimTransitionRepeat
void func_80137594(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate) {
    func_801373E8(skelAnime, animationSeg, 1.0f, 0.0f, 0.0f, 0, transitionRate);
}

// SkelAnime_ChangeAnimPlaybackRepeat
void func_801375CC(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed) {
    func_801373E8(skelAnime, animationSeg, playbackSpeed, 0.0f,
                         func_80134748(&animationSeg->genericHeader), 0, 0.0f);
}

// SkelAnime_AnimSetStop
void func_80137624(SkelAnime* skelAnime) {
    skelAnime->mode = 2;
    skelAnime->animFrameCount = skelAnime->totalFrames;
    func_80136C84(skelAnime);
}

// SkelAnime_AnimReverse
void func_80137650(SkelAnime* skelAnime) {
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
        sin = Math_Sins(angle);
        cos = Math_Coss(angle);
        pos->x = x * cos + z * sin;
        pos->z = z * cos - x * sin;
    }

    skelAnime->prevFramePos.x = skelAnime->limbDrawTbl->x;
    skelAnime->limbDrawTbl->x = skelAnime->unk_3E.x;
    skelAnime->prevFramePos.z = skelAnime->limbDrawTbl->z;
    skelAnime->limbDrawTbl->z = skelAnime->unk_3E.z;
    if (skelAnime->flags & ANIM_FLAG_UPDATEXZ) {
        if (skelAnime->flags & ANIM_FLAG_UPDATEY) {
            pos->y = 0.0f;
        } else {
            pos->y = skelAnime->limbDrawTbl->y - skelAnime->prevFramePos.y;
        }
        skelAnime->prevFramePos.y = skelAnime->limbDrawTbl->y;
        skelAnime->limbDrawTbl->y = skelAnime->unk_3E.y;
    } else {
        pos->y = 0.0f;
        skelAnime->prevFramePos.y = skelAnime->limbDrawTbl->y;
    }
    skelAnime->flags &= ~ANIM_FLAG_UPDATEY;
}

s32 func_801378B8(SkelAnime* skelAnime, f32 arg1) {
    return func_80136990(skelAnime, arg1, 1.0f);
}

// SkelAnime_Free
void func_801378E0(SkelAnime* skelAnime, GlobalContext* globalCtx) {
    if (skelAnime->limbDrawTbl != NULL) {
        zelda_free(skelAnime->limbDrawTbl);
    }

    if (skelAnime->transitionDrawTbl != NULL) {
        zelda_free(skelAnime->transitionDrawTbl);
    }
}

// SkelAnime_CopyVec3s
void func_8013792C(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src) {
    _bcopy(src, dst, sizeof(Vec3s) * skelAnime->limbCount);
}
