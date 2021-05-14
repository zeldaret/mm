#include <ultra64.h>
#include <global.h>

s16 atans_first_8th(f32 opposite, f32 adjacent) {
    return atan_first_8th_array[(s32) ((opposite / adjacent) * 1024.0f)];
}
//#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8017FEB0/atans_first_8th.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8017FEB0/atans.asm")

f32 atan(f32 opposite, f32 adjacent) {
    return atans(opposite, adjacent) * D_801E01E0;
}
//#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8017FEB0/atan.asm")

s16 Math_FAtan2F(f32 adjacent, f32 opposite) {
    return atans(opposite, adjacent);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8017FEB0/Math_FAtan2F.asm")

f32 atan_flip(f32 adjacent, f32 opposite) {
    return atan(opposite, adjacent);
}
//#pragma GLOBAL_ASM("./asm/non_matchings/code/code_0x8017FEB0/atan_flip.asm")
