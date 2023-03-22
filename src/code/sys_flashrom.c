#include "global.h"
#include "stack.h"
#include "system_malloc.h"

// extern UNK_TYPE1 D_801FBE10;
// extern UNK_TYPE1 D_801FBE28;
// extern UNK_TYPE1 D_801FBE2C;
// extern UNK_TYPE4 D_801FBE30;
extern STACK(sSysFlashromStack, 0x1000);
extern StackEntry sys_flashromStackEntry;
extern OSThread sys_flashromOSThread;
extern s80185D40 D_801FD008;
extern OSMesg D_801FD034;

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_801857C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_801857D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185864.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185908.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185968.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_801859F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/SysFlashrom_ThreadEntry.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185EC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/sys_flashrom/func_80185F64.s")
