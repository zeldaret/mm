#include "z_en_bigpo.h"

#define FLAGS 0x00001215

#define THIS ((EnBigpo*)thisx)

void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bigpo_InitVars = {
    ACTOR_EN_BIGPO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIGPO,
    sizeof(EnBigpo),
    (ActorFunc)EnBigpo_Init,
    (ActorFunc)EnBigpo_Destroy,
    (ActorFunc)EnBigpo_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/EnBigpo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/EnBigpo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B619B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B619FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61D74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B621CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B622E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B623BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B624F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6259C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6275C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B627B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B629E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62B10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B631F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B632BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6330C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B633E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B636D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B636E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6382C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6383C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B638AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B638D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63AC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63D88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/EnBigpo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B641E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6467C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64DFC.s")
