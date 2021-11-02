#include "global.h"
#include "z64skin.h"

extern MtxF D_801F5AC0[60];
//char D_80160FC0[0x10];

void func_80137970(MtxF* mtx, Struct_800A57C0* arg1, Struct_800A598C* arg2, Vtx* arg3, Vec3f* arg4) {
    Struct_800A57C0* phi_s0;
    Vtx* temp_s1;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    Vec3f sp50;
    Vec3f sp44;

    sp5C = mtx->mf[3][0];
    sp60 = mtx->mf[3][1];
    sp64 = mtx->mf[3][2];
    mtx->mf[3][0] = 0.0f;
    mtx->mf[3][1] = 0.0f;
    mtx->mf[3][2] = 0.0f;

    for (phi_s0 = arg1; phi_s0 < &arg1[arg2->unk_0]; phi_s0++) {
        temp_s1 = &arg3[phi_s0->unk_0];
        temp_s1->v.ob[0] = (s16) (s32) arg4->x;
        temp_s1->v.ob[1] = (s16) (s32) arg4->y;
        temp_s1->v.ob[2] = (s16) (s32) arg4->z;
        sp44.x = (f32) phi_s0->unk_6;
        sp44.y = (f32) phi_s0->unk_7;
        sp44.z = (f32) phi_s0->unk_8;
        SkinMatrix_Vec3fMtxFMultXYZ(mtx, &sp44, &sp50);
        temp_s1->v.cn[0] = (u8) (s32) sp50.x;
        temp_s1->v.cn[1] = (u8) (s32) sp50.y;
        temp_s1->v.cn[2] = (u8) (s32) sp50.z;
    }

    mtx->mf[3][0] = sp5C;
    mtx->mf[3][1] = sp60;
    mtx->mf[3][2] = sp64;
}

#ifdef NON_MATCHING
void func_80137B34(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3) {
    s32 temp_1;
    SkinLimb** skeleton;
    SkinLimb* limb;
    Struct_800A5E28* data;
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
    Struct_800A57C0* temp_v0;
    Struct_800A598C_2* temp_s3;
    Vtx* spEC;
    Vec3f sp88;
    Vec3f spDC;
    Vec3f spD0;
    Struct_800A598C_2* phi_s0;
    Struct_800A598C* temp_2;
    Vec3f spA0;
    Vec3f spAC;

    OPEN_DISPS(gfxCtx);

    skeleton = (SkinLimb**)Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    data = Lib_SegmentedToVirtual(((SkinLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]))->segment);
    temp_2 = (Struct_800A598C*)Lib_SegmentedToVirtual(data->unk_4);

    avb = &skin->avbTbl[limbIndex];

    spEC = avb->buf[avb->unk_0];
    temp_1 = data->unk_2;

    for (phi_s6 = temp_2; phi_s6 < temp_2 + temp_1; phi_s6++) {
        temp_v0 = (Struct_800A57C0*)Lib_SegmentedToVirtual(phi_s6->unk_8);
        temp_s3 = (Struct_800A598C_2*)Lib_SegmentedToVirtual(phi_s6->unk_C);
        temp_a0_2 = phi_s6->unk_2;

        if (temp_a0_2 == 1) {
            spAC.x = temp_s3[0].x;
            spAC.y = temp_s3[0].y;
            spAC.z = temp_s3[0].z;

            SkinMatrix_Vec3fMtxFMultXYZ(&D_801F5AC0[temp_s3[0].unk_0], &spAC, &spDC);
        } else if (arg3 != 0) {
            phi_s0 = &temp_s3[phi_s6->unk_4];

            spA0.x = phi_s0->x;
            spA0.y = phi_s0->y;
            spA0.z = phi_s0->z;
            SkinMatrix_Vec3fMtxFMultXYZ(&D_801F5AC0[phi_s0->unk_0], &spA0, &spDC);
        } else {

            spDC.x = spDC.y = spDC.z = 0.0f;

            for (phi_s0 = &temp_s3[0]; phi_s0 < &temp_s3[temp_a0_2]; phi_s0++) {
                temp_f20 = phi_s0->unk_8 * 0.01f;

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
    gSPSegment(POLY_OPA_DISP++, 0x08, avb->buf[avb->unk_0]);

    avb->unk_0 = (avb->unk_0 == 0);

    CLOSE_DISPS(gfxCtx);
}
#else
void func_80137B34(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137B34.s")
#endif

void func_80137EBC(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3, s32 arg4) {
    SkinLimb** skeleton;
    s32 pad[3];
    Struct_800A5E28* temp_t9;

    OPEN_DISPS(gfxCtx);
    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    temp_t9 = Lib_SegmentedToVirtual(((SkinLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]))->segment);
    if (!(arg4 & 1)) {
        func_80137B34(gfxCtx, skin, limbIndex, arg3);
    }
    gSPDisplayList(POLY_OPA_DISP++, temp_t9->unk_8);
    CLOSE_DISPS(gfxCtx);
}

void func_80137F58(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, Gfx* arg3, s32 arg4) {
    Gfx* gfx = arg3;
    SkinLimb** skeleton;

    OPEN_DISPS(gfxCtx);

    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    if (arg3 == NULL) {
        gfx = ((SkinLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]))->segment;
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

#ifdef NON_MATCHING
void func_80138050(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5, s32 arg6, s32 arg7) {
    s32 i;
    SkinLimb** skeleton;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    if ((arg7 & 1) == 0) {
        func_801388E4(skin, &D_801F5AC0[0], actor, arg5);
    }

    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    if ((arg7 & 2) == 0) {
        Mtx* mtx;

        gSPMatrix(POLY_OPA_DISP++, &D_801D1DE0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        mtx = SkinMatrix_MtxFToNewMtx(gfxCtx, &skin->mtx);
        if (mtx != NULL) {
        gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            //goto close_disps;
            goto block_5;
        }
    } else {
block_5:

        for (i = 0; i < skin->skeletonHeader->limbCount; i++) {
            s32 phi_a0 = 1;
            s32 dataType;

            if (arg4 != NULL) {
                phi_a0 = arg4(actor, globalCtx, i, skin);
            }

            dataType = ((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->unk_8;
            if (dataType == 4 && phi_a0 == 1) {
                func_80137EBC(gfxCtx, skin, i, arg6, arg7);
            } else if (dataType == 0xB && phi_a0 == 1) {
                func_80137F58(gfxCtx, skin, i, NULL, arg7);
            }
        }
        if (callback != NULL) {
            callback(actor, globalCtx, skin);
        }
    }

//close_disps:;
    CLOSE_DISPS(gfxCtx);
}
#else
void func_80138050(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5, s32 arg6, s32 arg7);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80138050.s")
#endif

void func_80138228(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, s32 arg4) {
    func_80138050(this, globalCtx, skin, callback, NULL, arg4, 0, 0);
}

void func_80138258(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5) {
    func_80138050(this, globalCtx, skin, callback, arg4, arg5, 0, 0);
}

void func_8013828C(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5, s32 arg6) {
    func_80138050(this, globalCtx, skin, callback, arg4, arg5, arg6, 0);
}

void func_801382C4(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5, s32 arg6, s32 arg7) {
    func_80138050(this, globalCtx, skin, callback, arg4, arg5, arg6, arg7);
}

void func_80138300(PSkinAwb* skin, s32 joint, Vec3f* arg2, Vec3f* arg3) {
    MtxF sp18;

    SkinMatrix_MtxFMtxFMult(&skin->mtx, &D_801F5AC0[joint], &sp18);
    SkinMatrix_Vec3fMtxFMultXYZ(&sp18, arg2, arg3);
}

void func_8013835C(PSkinAwb* arg0, s32 arg1, s32 arg2, Vec3f* arg3) {
    Vec3f sp24;
    Vtx* temp_v0;

    temp_v0 = &arg0->avbTbl[arg1].buf[arg0->avbTbl->unk_0][arg2];
    sp24.x = temp_v0->v.ob[0];
    sp24.y = temp_v0->v.ob[1];
    sp24.z = temp_v0->v.ob[2];
    SkinMatrix_Vec3fMtxFMultXYZ(&arg0->mtx, &sp24, arg3);
}
