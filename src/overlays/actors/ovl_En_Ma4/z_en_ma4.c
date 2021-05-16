#include "z_en_ma4.h"

#define FLAGS 0x02000039

#define THIS ((EnMa4*)thisx)

void EnMa4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ma4_InitVars = {
    ACTOR_EN_MA4,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMa4),
    (ActorFunc)EnMa4_Init,
    (ActorFunc)EnMa4_Destroy,
    (ActorFunc)EnMa4_Update,
    (ActorFunc)EnMa4_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABDCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABDD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABDD9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABDE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/EnMa4_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/EnMa4_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABE1C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABE4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABE560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABE6C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABEB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABEF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABEF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF0D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF4A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF51C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF534.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF69C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABF7C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABFCAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABFCD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/EnMa4_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABFD9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/func_80ABFE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ma4/EnMa4_Draw.s")
