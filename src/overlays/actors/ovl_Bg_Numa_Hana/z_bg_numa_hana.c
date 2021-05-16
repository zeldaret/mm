#include "z_bg_numa_hana.h"

#define FLAGS 0x00000410

#define THIS ((BgNumaHana*)thisx)

void BgNumaHana_Init(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Update(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Numa_Hana_InitVars = {
    ACTOR_BG_NUMA_HANA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_NUMA_OBJ,
    sizeof(BgNumaHana),
    (ActorFunc)BgNumaHana_Init,
    (ActorFunc)BgNumaHana_Destroy,
    (ActorFunc)BgNumaHana_Update,
    (ActorFunc)BgNumaHana_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1A500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1A56C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1A750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AB00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ABD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ABF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ACCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ACE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Draw.s")
