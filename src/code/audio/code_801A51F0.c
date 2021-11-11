#include "global.h"

char D_801D8E50[] =
    "aa\0AA\0ii\0II\0uu\0UU\0ee\0EE\0oo\0OO\0KA\0GA\0KI\0GI\0KU\0GU\0KE\0GE\0KO\0GO\0SA\0ZA\0SI\0ZI\0SU\0ZU\0SE\0ZE\0SO"
    "\0ZO\0TA\0DA\0TI\0DI\0tu\0TU\0DU\0TE\0DE\0TO\0DO\0NA\0NI\0NU\0NE\0NO\0HA\0BA\0PA\0HI\0BI\0PI\0HU\0BU\0PU\0HE\0BE\0"
    "PE\0HO\0BO\0PO\0MA\0MI\0MU\0ME\0MO\0ya\0YA\0yu\0YU\0yo\0YO\0RA\0RI\0RU\0RE\0RO\0wa\0WA\0WI\0WE\0WO\0NN\0VU\0ka\0ke"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

char D_801D8F70[] = "aa\0AA\0ii\0II\0uu\0UU\0ee\0EE\0oo\0OO\0KA\0GA\0KI\0GI\0KU\0GU\0KE\0GE\0KO\0GO\0SA\0ZA\0SI\0ZI\0SU"
                    "\0ZU\0SE\0ZE\0SO\0ZO\0TA\0DA\0TI\0DI\0tu\0TU\0DU\0TE\0DE\0TO\0DO\0NA\0NI\0NU\0NE\0NO\0HA\0BA\0PA\0"
                    "HI\0BI\0PI\0HU\0BU\0PU\0HE\0BE\0PE\0HO\0BO\0PO\0MA\0MI\0  "
                    "\0MU\0ME\0MO\0ya\0YA\0yu\0YU\0yo\0YO\0RA\0RI\0RU\0RE\0RO\0wa\0WA\0WI\0WE\0WO\0NN\0VU\0ka\0ke\0\0\0"
                    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

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
