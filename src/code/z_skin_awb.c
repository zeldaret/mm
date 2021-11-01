#include "global.h"

#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_80138410.s")


void func_80138424(GameState* gameState, PSkinAwb* skin, s32 limbIndex) {
    s32 i;
    SkinLimb** skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    Struct_800A5E28* temp_v1 = Lib_SegmentedToVirtual(((SkinLimb*)Lib_SegmentedToVirtual(skeleton[limbIndex]))->segment);
    Struct_800A598C* temp_v0 = Lib_SegmentedToVirtual(temp_v1->unk_4);

    for (i = 0; i < 2; i++) {
        Vtx* temp2 = skin->avbTbl[limbIndex].buf[i];
        Struct_800A598C* phi_s0;
        Struct_800A57C0* temp_s1;

        for (phi_s0 = temp_v0; phi_s0 < temp_v0 + temp_v1->unk_2; phi_s0++) {
            Struct_800A57C0* phi_s1 = Lib_SegmentedToVirtual(phi_s0->unk_8);

            for (temp_s1 = phi_s1; temp_s1 < phi_s1 + phi_s0->unk_0; ) {
                Vtx* temp_t5_3 = &temp2[temp_s1->unk_0];

                temp_s1++;

                temp_t5_3->v.flag = 0;
                temp_t5_3->v.tc[0] = temp_s1[-1].unk_2;
                temp_t5_3->v.tc[1] = temp_s1[-1].unk_4;
                temp_t5_3->v.cn[3] = temp_s1[-1].unk_9;
            }
        }
    }
}


#ifdef NON_MATCHING
void func_8013859C(GlobalContext* globalCtx, PSkinAwb* skin, SkeletonHeader* skeletonHeader,
                   AnimationHeader* animationHeader) {
    s32 limbCount;
    s32 i;
    SkinLimb** skeleton;
    SkeletonHeader* virtSkelHeader = Lib_SegmentedToVirtual(skeletonHeader);

    skin->avbCount = virtSkelHeader->limbCount;
    skin->skeletonHeader = virtSkelHeader;
    limbCount = skin->skeletonHeader->limbCount;

    skeleton = Lib_SegmentedToVirtual(skin->skeletonHeader->segment);
    skin->avbTbl = ZeldaArena_Malloc(limbCount * sizeof(SkinAvb));

    for (i = 0; i < limbCount; i++) {
        SkinAvb* avbEntry = &skin->avbTbl[i];

        if ((((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->unk_8 != 4) || (((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segment == NULL)) {
            avbEntry->unk_0 = 0;

            avbEntry->buf[0] = NULL;
            avbEntry->buf[1] = NULL;
        } else {
            Struct_800A5E28* temp_s1 = Lib_SegmentedToVirtual((((SkinLimb*)Lib_SegmentedToVirtual(skeleton[i]))->segment));

            dummy_label_17759: ;
            if (1) { } if (1) { } if (1) { } if (1) { } if (1) { } 

            avbEntry->unk_0 = 0;
            avbEntry->buf[0] = ZeldaArena_Malloc(temp_s1->unk_0 * sizeof(Vtx));
            if (1) { }
            avbEntry->buf[1] = ZeldaArena_Malloc(temp_s1->unk_0 * sizeof(Vtx));
            if (1) { }

            func_80138424(globalCtx, skin, i);
        }
    }
    SkelAnime_InitSkin(globalCtx, &skin->skelAnime, skeletonHeader, animationHeader);
}
#else

void func_8013859C(GlobalContext* globalCtx, PSkinAwb* skin, SkeletonHeader* skeletonHeader, AnimationHeader* animationHeader);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_8013859C.s")
#endif

void func_80138700(GameState* gameState, PSkinAwb* skin) {
    if (skin->avbTbl != NULL) {
        s32 i;

        for (i = 0; i < skin->avbCount; i++) {
            if (skin->avbTbl[i].buf[0] != 0) {
                ZeldaArena_Free(skin->avbTbl[i].buf[0]);
                skin->avbTbl[i].buf[0] = 0;
            }
            if (skin->avbTbl[i].buf[1] != 0) {
                ZeldaArena_Free(skin->avbTbl[i].buf[1]);
                skin->avbTbl[i].buf[1] = 0;
            }
        }

        if (skin->avbTbl != NULL) {
            ZeldaArena_Free(skin->avbTbl);
        }

        SkelAnime_Free(&skin->skelAnime, gameState);
    }
}

s32 func_801387D4(PSkinAwb* skin, SkinLimb** skeleton, MtxF* mf, u8 parentIndex, u8 limbIndex);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_801387D4.s")

s32 func_801388E4(PSkinAwb* skin, MtxF* arg1, Actor* actor, s32 arg3);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_801388E4.s")
