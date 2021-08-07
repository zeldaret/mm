#include "global.h"

void* StartHeap_Alloc(u32 arg0) {
    void* ptr = __osMalloc(&startHeap, arg0);

    if (1) {}

    return ptr;
}

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_AllocR.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Realloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Free.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Calloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_AnalyzeArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_CheckArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_InitArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Cleanup.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_IsInitialized.s")
