#include <ultra64.h>
#include <global.h>

void* ZeldaArena_Malloc(u32 size) {
    void* ptr = __osMalloc(&sZeldaArena, size);

    return ptr;
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_MallocR.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_Realloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_Free.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_Calloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_GetSizes.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_Check.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_Cleanup.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_malloc/ZeldaArena_IsInitialized.asm")
