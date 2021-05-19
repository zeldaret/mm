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
    (ActorFunc)BgNumaHana_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1A500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1A56C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1A750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/BgNumaHana_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/BgNumaHana_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AA28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AA38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AAE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AB00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1ABD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1ABF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1ACCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1ACE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AE08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/func_80A1AE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/BgNumaHana_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Numa_Hana_0x80A1A500/BgNumaHana_Draw.asm")
