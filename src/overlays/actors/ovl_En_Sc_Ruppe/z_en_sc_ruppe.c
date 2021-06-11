#include "z_en_sc_ruppe.h"

#define FLAGS 0x00000030

#define THIS ((EnScRuppe*)thisx)

void EnScRuppe_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScRuppe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScRuppe_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScRuppe_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sc_Ruppe_InitVars = {
    ACTOR_EN_SC_RUPPE,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnScRuppe),
    (ActorFunc)EnScRuppe_Init,
    (ActorFunc)EnScRuppe_Destroy,
    (ActorFunc)EnScRuppe_Update,
    (ActorFunc)EnScRuppe_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD6910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD697C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD6A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD6B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Draw.s")
