#include "global.h"

/*
char D_801E0EC0[] = "Error %d\n"
char D_801E0ECC[] = "NAI_VRS:osVoiceClearDictionary %d\n"
char D_801E0EF0[] = "NAI_VRS:dict error! (%d-%d %s)\n"
char D_801E0F10[] = "NAI_VRS:Ina_SetVruGain Error!\n"
char D_801E0F30[] = "NAI_VRS:mask on  %d\n"
char D_801E0F48[] = "NAI_VRS:mask off %d\n"
char D_801E0F60[] = "NAI_VRS:answer No.:%d Dist:%d Warn:%04X Level:%5d SN:%5d (Num:%d)\n"
char D_801E0FA4[] = "NAI_VRS:error !! (ANS_MAX:%d DIST:%d WARNING:%04X LEVEL:%5d SN:%5d)\n"
*/
#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/D_801E0EC0.s")

s32 func_801A51F0(s32 errorCode) {
    switch (errorCode) {
        case CONT_ERR_NO_CONTROLLER:
        case CONT_ERR_CONTRFAIL:
        case CONT_ERR_INVALID:
        case CONT_ERR_DEVICE:
        case CONT_ERR_VOICE_MEMORY:
        case CONT_ERR_VOICE_WORD:
        case CONT_ERR_VOICE_NO_RESPONSE:
            return -1;
        default:
            return 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5228.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5390.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A53DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A53E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A541C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5488.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A54C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A54D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5680.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5808.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5A1C.s")
