#include "global.h"
#include "z64skin.h"

extern MtxF D_801F5AC0[60];
//char D_80160FC0[0x10];

void func_80137970(MtxF* mtx, SkinVtx* skinVertices, Struct_800A598C* arg2, Vtx* verticesDst, Vec3f* arg4) {
    SkinVtx* skinVtxEntry;
    Vtx* vtx;
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;

    sp5C.x = mtx->mf[3][0];
    sp5C.y = mtx->mf[3][1];
    sp5C.z = mtx->mf[3][2];
    mtx->mf[3][0] = 0.0f;
    mtx->mf[3][1] = 0.0f;
    mtx->mf[3][2] = 0.0f;

    for (skinVtxEntry = skinVertices; skinVtxEntry < &skinVertices[arg2->unk_0]; skinVtxEntry++) {
        vtx = &verticesDst[skinVtxEntry->vtxIndex];

        vtx->n.ob[0] = arg4->x;
        vtx->n.ob[1] = arg4->y;
        vtx->n.ob[2] = arg4->z;

        sp44.x = skinVtxEntry->x;
        sp44.y = skinVtxEntry->y;
        sp44.z = skinVtxEntry->z;
        SkinMatrix_Vec3fMtxFMultXYZ(mtx, &sp44, &sp50);
        vtx->n.n[0] = sp50.x;
        vtx->n.n[1] = sp50.y;
        vtx->n.n[2] = sp50.z;
    }

    mtx->mf[3][0] = sp5C.x;
    mtx->mf[3][1] = sp5C.y;
    mtx->mf[3][2] = sp5C.z;
}

void func_80137B34(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3) {
    s32 temp_1;
    SkinLimb** skeleton;
    SkinLimb* limb;
    SkinAnimatedLimbData* data;
    s32 pad;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    Struct_800A598C* phi_s6;
    SkinAvb* avb;
    s32 pad6;
    s32 temp_a0_2;
    f32 temp_f20;
    SkinVtx* temp_v0;
    Vec3f sp88;
    Vtx* spEC;
    Struct_800A598C_2* temp_s3;
    Vec3f spDC;
    Vec3f spD0;
    Struct_800A598C_2* phi_s0;
    SkinLimb *new_var;
    Struct_800A598C* temp_2;

    OPEN_DISPS(gfxCtx);

    skeleton = (SkinLimb**)Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    new_var = (SkinLimb *) Lib_SegmentedToVirtual(skeleton[limbIndex]);
    data = Lib_SegmentedToVirtual(new_var->limbData);
    temp_2 = (Struct_800A598C*)Lib_SegmentedToVirtual(data->unk_4);

    avb = &skin->avbTbl[limbIndex];

    spEC = avb->buf[avb->index];
    temp_1 = data->unk_2;

    for (phi_s6 = temp_2; phi_s6 < temp_2 + temp_1; phi_s6++) {
        Vec3f spAC;
        Vec3f spA0;

        temp_v0 = (SkinVtx*)Lib_SegmentedToVirtual(phi_s6->unk_8);
        temp_s3 = (Struct_800A598C_2*)Lib_SegmentedToVirtual(phi_s6->unk_C);
        temp_a0_2 = phi_s6->unk_2;

        if (temp_a0_2 == 1) {
            spAC.x = temp_s3[0].x;
            spAC.y = temp_s3[0].y;
            spAC.z = temp_s3[0].z;

            SkinMatrix_Vec3fMtxFMultXYZ(&D_801F5AC0[temp_s3[0].unk_0], &spAC, &spDC);
        } else if (arg3) {
            phi_s0 = &temp_s3[phi_s6->unk_4];

            spA0.x = phi_s0->x;
            spA0.y = phi_s0->y;
            spA0.z = phi_s0->z;
            SkinMatrix_Vec3fMtxFMultXYZ(&D_801F5AC0[phi_s0->unk_0], &spA0, &spDC);
        } else {
            spDC.x = 0.0f;
            spDC.y = 0.0f;
            spDC.z = 0.0f;

            for (phi_s0 = &temp_s3[0]; phi_s0 < &temp_s3[temp_a0_2]; phi_s0++) {
                temp_f20 = phi_s0->scale * 0.01f;

                sp88.x = phi_s0->x;
                sp88.y = phi_s0->y;
                sp88.z = phi_s0->z;
                SkinMatrix_Vec3fMtxFMultXYZ(&D_801F5AC0[phi_s0->unk_0], &sp88, &spD0);
                spDC.x += spD0.x * temp_f20;
                spDC.y += spD0.y * temp_f20;
                spDC.z += spD0.z * temp_f20;
            }
        }

        func_80137970(&D_801F5AC0[temp_s3[phi_s6->unk_4].unk_0], temp_v0, phi_s6, spEC, &spDC);
    }

    gSPSegment(POLY_OPA_DISP++, 0x08, avb->buf[avb->index]);

    avb->index = (avb->index == 0);

    CLOSE_DISPS(gfxCtx);
}

/**
 * Draw a limb of type SKIN_LIMB_TYPE_ANIMATED, of the skeleton `skin` at index `limbIndex`.
 * The vertices of this limb are modified dynamically
 */
void Skin_DrawAnimatedLimb(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3, s32 arg4) {
    SkinLimb** skeleton;
    s32 pad[3];
    SkinAnimatedLimbData* temp_t9;

    OPEN_DISPS(gfxCtx);
    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    temp_t9 = Lib_SegmentedToVirtual(((SkinLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]))->limbData);
    if (!(arg4 & 1)) {
        func_80137B34(gfxCtx, skin, limbIndex, arg3);
    }
    gSPDisplayList(POLY_OPA_DISP++, temp_t9->dlist);
    CLOSE_DISPS(gfxCtx);
}

/**
 * Draw a limb of type SKIN_LIMB_TYPE_NORMAL, of the skeleton `skin` at index `limbIndex`.
 */
void Skin_DrawLimb(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, Gfx* dlistOverride, s32 arg4) {
    Gfx* gfx = dlistOverride;
    SkinLimb** skeleton;

    OPEN_DISPS(gfxCtx);

    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);

    if (dlistOverride == NULL) {
        gfx = ((SkinLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]))->dlist;
    }

    if (gfx != NULL) {
        Mtx* mtx = SkinMatrix_MtxFToNewMtx(gfxCtx, &D_801F5AC0[limbIndex]);

        if (mtx != NULL) {
            gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gfx);
            gSPPopMatrix(POLY_OPA_DISP++, G_MTX_MODELVIEW);
            gDPPipeSync(POLY_OPA_DISP++);
        }
    }

    CLOSE_DISPS(gfxCtx);
}

void Skin_DrawImpl(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw overrideLimbDraw,
                   s32 arg5, s32 arg6, s32 arg7) {
    s32 i;
    SkinLimb** skeleton;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    if (!(arg7 & 1)) {
        func_801388E4(skin, D_801F5AC0, actor, arg5);
    }

    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);

    if (!(arg7 & 2)) {
        Mtx* mtx;

        gSPMatrix(POLY_OPA_DISP++, &gMtxClear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        mtx = SkinMatrix_MtxFToNewMtx(gfxCtx, &skin->mtx);
        if (mtx == NULL) {
            goto close_disps;
        }
        gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    for (i = 0; i < skin->skeletonHeader->limbCount; i++) {
        s32 shouldDraw = true;
        s32 segmentType;

        if (overrideLimbDraw != NULL) {
            shouldDraw = overrideLimbDraw(actor, globalCtx, i, skin);
        }

        segmentType = ((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segmentType;
        if (segmentType == SKIN_LIMB_TYPE_ANIMATED && shouldDraw) {
            Skin_DrawAnimatedLimb(gfxCtx, skin, i, arg6, arg7);
        } else if (segmentType == SKIN_LIMB_TYPE_NORMAL && shouldDraw) {
            Skin_DrawLimb(gfxCtx, skin, i, NULL, arg7);
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(actor, globalCtx, skin);
    }

close_disps:;
    CLOSE_DISPS(gfxCtx);
}

// Skin_Draw... Something?
void func_80138228(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, s32 arg4) {
    Skin_DrawImpl(actor, globalCtx, skin, postLimbDraw, NULL, arg4, false, 0);
}

// Skin_Draw... Something?
void func_80138258(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw overrideLimbDraw,
                   s32 arg5) {
    Skin_DrawImpl(actor, globalCtx, skin, postLimbDraw, overrideLimbDraw, arg5, false, 0);
}

// Skin_Draw... Something?
void func_8013828C(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw overrideLimbDraw,
                   s32 arg5, s32 arg6) {
    Skin_DrawImpl(actor, globalCtx, skin, postLimbDraw, overrideLimbDraw, arg5, arg6, 0);
}

// Skin_Draw?
void func_801382C4(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw overrideLimbDraw,
                   s32 arg5, s32 arg6, s32 arg7) {
    Skin_DrawImpl(actor, globalCtx, skin, postLimbDraw, overrideLimbDraw, arg5, arg6, arg7);
}

void func_80138300(PSkinAwb* skin, s32 joint, Vec3f* arg2, Vec3f* arg3) {
    MtxF sp18;

    SkinMatrix_MtxFMtxFMult(&skin->mtx, &D_801F5AC0[joint], &sp18);
    SkinMatrix_Vec3fMtxFMultXYZ(&sp18, arg2, arg3);
}

void func_8013835C(PSkinAwb* arg0, s32 arg1, s32 arg2, Vec3f* arg3) {
    Vec3f sp24;
    Vtx* temp_v0;

    temp_v0 = &arg0->avbTbl[arg1].buf[arg0->avbTbl->index][arg2];
    sp24.x = temp_v0->v.ob[0];
    sp24.y = temp_v0->v.ob[1];
    sp24.z = temp_v0->v.ob[2];
    SkinMatrix_Vec3fMtxFMultXYZ(&arg0->mtx, &sp24, arg3);
}
