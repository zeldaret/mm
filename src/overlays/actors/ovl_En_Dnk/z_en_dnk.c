#include "z_en_dnk.h"

#define FLAGS 0x00000009

#define THIS ((EnDnk*)thisx)

void EnDnk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dnk_InitVars = {
    ACTOR_EN_DNK,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDnk),
    (ActorFunc)EnDnk_Init,
    (ActorFunc)EnDnk_Destroy,
    (ActorFunc)EnDnk_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A514F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A515C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A518DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/EnDnk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/EnDnk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/EnDnk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A51FC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A52018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A52074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnk/func_80A52134.s")
