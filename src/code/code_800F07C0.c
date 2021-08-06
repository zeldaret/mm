#include "global.h"

s32 func_800F07C0(SkelAnime* skelAnime, s16 animIndex) {
    s16 frameCount;
    s32 ret = false;

    if (animIndex >= 0 && animIndex <= 20) {
        ret = true;
        frameCount = D_801BC2A0[animIndex].frameCount;
        if (frameCount < 0) {
            frameCount = SkelAnime_GetFrameCount(&D_801BC2A0[animIndex].animationSeg->common);
        }
        SkelAnime_ChangeAnim(skelAnime, D_801BC2A0[animIndex].animationSeg, D_801BC2A0[animIndex].playbackSpeed,
                             D_801BC2A0[animIndex].frame, frameCount, D_801BC2A0[animIndex].mode,
                             D_801BC2A0[animIndex].transitionRate);
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0888.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0944.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F09B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0FF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F10AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F112C.s")
