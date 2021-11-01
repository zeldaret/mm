#include "global.h"


MtxF D_801F5AC0[60];
//char D_80160FC0[0x10];


void func_80137970(MtxF* mtx, Struct_800A57C0* arg1, Struct_800A598C* arg2, Vtx* arg3, Vec3f* arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137970.s")

void func_800A598C(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137B34.s")

void func_80137EBC(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3, s32 arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137EBC.s")

void func_80137F58(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, Gfx* arg3, s32 arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80137F58.s")

void func_80138050(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5, s32 arg6, s32 arg7);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80138050.s")

void func_80138228(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, s32 arg4);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80138228.s")

void func_80138258(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_80138258.s")

void func_8013828C(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5, s32 arg6);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_8013828C.s")

void func_801382C4(Actor* this, GlobalContext* globalCtx, PSkinAwb* skin, SkinCallback callback, SkinCallback2 arg4,
                   s32 arg5, s32 arg6, s32 arg7);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_801382C4.s")

void func_80138300(PSkinAwb* skin, s32 joint, Vec3f* arg2, Vec3f* arg3) {
    MtxF sp18;

    SkinMatrix_MtxFMtxFMult(&skin->mtx, &D_801F5AC0[joint], &sp18);
    SkinMatrix_Vec3fMtxFMultXYZ(&sp18, arg2, arg3);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin/func_8013835C.s")
