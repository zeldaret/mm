#include "z_en_kusa2.h"

#define FLAGS 0x00800010

#define THIS ((EnKusa2*)thisx)

void EnKusa2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKusa2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKusa2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKusa2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kusa2_InitVars = {
    ACTOR_EN_KUSA2,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(EnKusa2),
    (ActorFunc)EnKusa2_Init,
    (ActorFunc)EnKusa2_Destroy,
    (ActorFunc)EnKusa2_Update,
    (ActorFunc)EnKusa2_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5B160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5B334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5B3BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5B490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5B508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5B954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BA58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BAFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BB40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BD14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BD94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BDB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BF38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BF84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5BFD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C7F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5C918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5CAD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5CAF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5CB74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5CCD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5CD0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5CF44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/EnKusa2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/EnKusa2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D5F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D6C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D7A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D7C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5D9C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5DC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5DC98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5DE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5DEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E1D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E4BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/EnKusa2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E6F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E80C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/EnKusa2_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5E9B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa2/func_80A5EA48.s")
