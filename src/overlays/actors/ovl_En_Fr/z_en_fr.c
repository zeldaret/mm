/*
 * File: z_en_fr.c
 * Overlay: ovl_En_Fr
 * Description:
 */

#include "z_en_fr.h"

#define FLAGS 0x40000000

#define THIS ((EnFr*)thisx)

void EnFr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFr_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fr_InitVars = {
    ACTOR_EN_FR,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFr),
    (ActorFunc)EnFr_Init,
    (ActorFunc)EnFr_Destroy,
    (ActorFunc)EnFr_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fr/EnFr_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fr/EnFr_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fr/EnFr_Update.s")
