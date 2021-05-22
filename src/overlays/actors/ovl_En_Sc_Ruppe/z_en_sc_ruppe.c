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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/func_80BD6910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/func_80BD697C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/func_80BD6A8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/func_80BD6B18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/EnScRuppe_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/EnScRuppe_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/EnScRuppe_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sc_Ruppe_0x80BD6910/EnScRuppe_Draw.asm")
