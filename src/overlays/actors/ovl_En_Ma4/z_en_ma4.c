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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMa4),
    (ActorFunc)EnMa4_Init,
    (ActorFunc)EnMa4_Destroy,
    (ActorFunc)EnMa4_Update,
    (ActorFunc)EnMa4_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABDCA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABDD2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABDD9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABDE60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/EnMa4_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/EnMa4_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABE1C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABE4A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABE560.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABE6C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABEB6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABEF34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABEF8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF0D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF160.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF198.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF218.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF254.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF2FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF4A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF51C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF534.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF69C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF6B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF774.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABF7C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABFCAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABFCD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/EnMa4_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABFD9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/func_80ABFE48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ma4_0x80ABDCA0/EnMa4_Draw.asm")
