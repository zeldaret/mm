#include "global.h"

void (*sKaleidoScopeUpdateFunc)(GlobalContext* globalCtx);
void (*sKaleidoScopeDrawFunc)(GlobalContext* globalCtx);

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_scope_call/KaleidoScopeCall_LoadPlayer.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_scope_call/KaleidoScopeCall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_scope_call/KaleidoScopeCall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_scope_call/KaleidoScopeCall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_scope_call/KaleidoScopeCall_Draw.s")
