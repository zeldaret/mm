#include "z_en_invisible_ruppe.h"

#define FLAGS 0x00000000

#define THIS ((EnInvisibleRuppe*)thisx)

void EnInvisibleRuppe_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInvisibleRuppe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInvisibleRuppe_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Invisible_Ruppe_InitVars = {
    ACTOR_EN_INVISIBLE_RUPPE,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvisibleRuppe),
    (ActorFunc)EnInvisibleRuppe_Init,
    (ActorFunc)EnInvisibleRuppe_Destroy,
    (ActorFunc)EnInvisibleRuppe_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invisible_Ruppe_0x80C258A0/func_80C258A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invisible_Ruppe_0x80C258A0/func_80C2590C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invisible_Ruppe_0x80C258A0/func_80C259E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invisible_Ruppe_0x80C258A0/EnInvisibleRuppe_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invisible_Ruppe_0x80C258A0/EnInvisibleRuppe_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invisible_Ruppe_0x80C258A0/EnInvisibleRuppe_Update.asm")
