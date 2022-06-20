/*
 * File: z_en_sth2.c
 * Overlay: ovl_En_Sth2
 * Description: Guy waving at the telescope in Termina Field
 */

#include "z_en_sth2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnSth2*)thisx)

void EnSth2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSth2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSth2_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sth2_InitVars = {
    ACTOR_EN_STH2,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSth2),
    (ActorFunc)EnSth2_Init,
    (ActorFunc)EnSth2_Destroy,
    (ActorFunc)EnSth2_Update,
    (ActorFunc)NULL,
};

#endif

extern UNK_TYPE D_060031F8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/EnSth2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/EnSth2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/func_80BF75A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/EnSth2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/func_80BF7688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/func_80BF76AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/func_80BF77AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sth2/func_80BF7814.s")
