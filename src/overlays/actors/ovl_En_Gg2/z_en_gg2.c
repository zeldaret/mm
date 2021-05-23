#include "z_en_gg2.h"

#define FLAGS 0x00000089

#define THIS ((EnGg2*)thisx)

void EnGg2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGg2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGg2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGg2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gg2_InitVars = {
    ACTOR_EN_GG2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GG,
    sizeof(EnGg2),
    (ActorFunc)EnGg2_Init,
    (ActorFunc)EnGg2_Destroy,
    (ActorFunc)EnGg2_Update,
    (ActorFunc)EnGg2_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3AC50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3AC94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3ADD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3AE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3AFB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B05C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B0A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B21C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B4B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B5D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B7E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3B8A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/EnGg2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/EnGg2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/EnGg2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3BD44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/func_80B3BDC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Gg2_0x80B3AC50/EnGg2_Draw.asm")
