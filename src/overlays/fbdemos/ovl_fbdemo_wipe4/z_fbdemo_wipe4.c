/*
 * File: z_fbdemo_wipe4.c
 * Overlay: ovl_fbdemo_wipe4
 * Description:
 */

#include "z_fbdemo_wipe4.h"

void* TransitionWipe4_Init(void* thisx);
void TransitionWipe4_Destroy(void* thisx);
void TransitionWipe4_Update(void* thisx, s32 updateRate);
void TransitionWipe4_Draw(void* thisx, Gfx** gfxP);
void TransitionWipe4_Start(void* thisx);
void TransitionWipe4_SetType(void* thisx, s32 type);
void TransitionWipe4_SetColor(void* thisx, u32 color);
void TransitionWipe4_SetEnvColor(void* thisx, u32 color);
s32 TransitionWipe4_IsDone(void* thisx);

#if 0
const TransitionInit TransitionWipe4_InitVars = {
    TransitionWipe4_Init,
    TransitionWipe4_Destroy,
    TransitionWipe4_Update,
    TransitionWipe4_Draw,
    TransitionWipe4_Start,
    TransitionWipe4_SetType,
    TransitionWipe4_SetColor,
    TransitionWipe4_SetEnvColor,
    TransitionWipe4_IsDone,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_Start.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_IsDone.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_SetType.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_SetColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe4/TransitionWipe4_SetEnvColor.s")
