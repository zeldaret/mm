/*
 * File: z_fbdemo_wipe1.c
 * Overlay: ovl_fbdemo_wipe1
 * Description:
 */

#include "z_fbdemo_wipe1.h"

void* TransitionWipe1_Init(void* thisx);
void TransitionWipe1_Destroy(void* thisx);
void TransitionWipe1_Update(void* thisx, s32 updateRate);
void TransitionWipe1_Draw(void* thisx, Gfx** gfxP);
void TransitionWipe1_Start(void* thisx);
void TransitionWipe1_SetType(void* thisx, s32 type);
void TransitionWipe1_SetColor(void* thisx, u32 color);
void TransitionWipe1_SetEnvColor(void* thisx, u32 color);
s32 TransitionWipe1_IsDone(void* thisx);

#if 0
const TransitionInit TransitionWipe1_InitVars = {
    TransitionWipe1_Init,
    TransitionWipe1_Destroy,
    TransitionWipe1_Update,
    TransitionWipe1_Draw,
    TransitionWipe1_Start,
    TransitionWipe1_SetType,
    TransitionWipe1_SetColor,
    TransitionWipe1_SetEnvColor,
    TransitionWipe1_IsDone,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_Start.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_IsDone.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_SetType.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_SetColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe1/TransitionWipe1_SetEnvColor.s")
