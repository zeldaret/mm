#include "z_en_gg.h"

#define FLAGS 0x00000089

#define THIS ((EnGg*)thisx)

void EnGg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gg_InitVars = {
    ACTOR_EN_GG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GG,
    sizeof(EnGg),
    (ActorFunc)EnGg_Init,
    (ActorFunc)EnGg_Destroy,
    (ActorFunc)EnGg_Update,
    (ActorFunc)EnGg_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B34F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B34FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B351A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B352A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B3556C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B357F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B3584C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B358D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B359DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35B24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B35C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B3610C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B363E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B364D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/EnGg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/EnGg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/EnGg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B368B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/func_80B368F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gg/EnGg_Draw.s")
