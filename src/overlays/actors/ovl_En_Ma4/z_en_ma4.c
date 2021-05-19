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
    (ActorFunc)EnMa4_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDD9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/EnMa4_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/EnMa4_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE1C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE6C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEF34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEF8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF0D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF218.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF4A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF51C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF534.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF69C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF774.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF7C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABFCAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABFCD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/EnMa4_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABFD9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABFE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/EnMa4_Draw.asm")
