/*
 * File: z_en_sda.c
 * Overlay: ovl_En_Sda
 * Description: Dynamic Shadow for Link
 */

#include "z_en_sda.h"

#define FLAGS 0x00000030

#define THIS ((EnSda*)thisx)

void EnSda_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSda_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSda_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSda_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sda_InitVars = {
    ACTOR_EN_SDA,
    ACTORCAT_BOSS,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSda),
    (ActorFunc)EnSda_Init,
    (ActorFunc)EnSda_Destroy,
    (ActorFunc)EnSda_Update,
    (ActorFunc)EnSda_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sda/EnSda_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sda/EnSda_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sda/EnSda_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sda/EnSda_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sda/func_809469C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sda/func_8094702C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sda/func_80947668.s")
