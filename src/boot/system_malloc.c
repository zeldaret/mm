#include "ultra64.h"
#include "global.h"

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Alloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_AllocR.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Realloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Free.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Calloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_AnalyzeArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_CheckArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_InitArena.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_Cleanup.s")

#pragma GLOBAL_ASM("asm/non_matchings/boot/system_malloc/StartHeap_IsInitialized.s")
