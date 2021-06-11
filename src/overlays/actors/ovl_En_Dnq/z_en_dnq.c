#include "z_en_dnq.h"

#define FLAGS 0x00000009

#define THIS ((EnDnq*)thisx)

void EnDnq_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDnq_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dnq_InitVars = {
    ACTOR_EN_DNQ,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNQ,
    sizeof(EnDnq),
    (ActorFunc)EnDnq_Init,
    (ActorFunc)EnDnq_Destroy,
    (ActorFunc)EnDnq_Update,
    (ActorFunc)EnDnq_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A5257C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A526F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52C6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52CF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52D44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A52FB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/func_80A53038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/EnDnq_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/EnDnq_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/EnDnq_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnq/EnDnq_Draw.s")
