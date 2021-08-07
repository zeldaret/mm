#include "global.h"

void* SystemArena_Alloc(u32 arg0) {
    return __osMalloc(&gSystemArena, arg0);
}

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_AllocR.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_Realloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_Free.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_Calloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_AnalyzeArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_CheckArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_InitArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_Cleanup.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/SystemArena_IsInitialized.s")
