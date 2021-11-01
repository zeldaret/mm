#include "global.h"


extern MtxF D_801F5AC0[60];
//MtxF D_801F5AC0[60];
//char D_80160FC0[0x10];


void func_80137970(MtxF* mtx, Struct_800A57C0* arg1, Struct_800A598C* arg2, Vtx* arg3, Vec3f* arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137970.s")

void func_800A598C(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137B34.s")

void func_80137EBC(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3, s32 arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137EBC.s")

void func_80137F58(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, Gfx* arg3, s32 arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137F58.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_8013835C.s")
