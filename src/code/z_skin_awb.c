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


#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_8013859C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_80138700.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_801387D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_skin_awb/func_801388E4.s")
