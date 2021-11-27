/*
 * File: z_fbdemo_wipe5.c
 * Overlay: ovl_fbdemo_wipe5
 * Description:
 */

#include "z_fbdemo_wipe5.h"

void* TransitionWipe5_Init(void* thisx);
void TransitionWipe5_Destroy(void* thisx);
void TransitionWipe5_Update(void* thisx, s32 updateRate);
void TransitionWipe5_Draw(void* thisx, Gfx** gfxP);
void TransitionWipe5_Start(void* thisx);
void TransitionWipe5_SetType(void* thisx, s32 type);
void TransitionWipe5_SetColor(void* thisx, u32 color);
void TransitionWipe5_SetEnvColor(void* thisx, u32 color);
s32 TransitionWipe5_IsDone(void* thisx);

#if 0
const TransitionInit TransitionWipe5_InitVars = {
    TransitionWipe5_Init,
    TransitionWipe5_Destroy,
    TransitionWipe5_Update,
    TransitionWipe5_Draw,
    TransitionWipe5_Start,
    TransitionWipe5_SetType,
    TransitionWipe5_SetColor,
    TransitionWipe5_SetEnvColor,
    TransitionWipe5_IsDone,
};

#endif

extern UNK_TYPE D_0F000000;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_Start.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_IsDone.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_SetType.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_SetColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe5/TransitionWipe5_SetEnvColor.s")
