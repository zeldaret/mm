#include "z_en_bigpo.h"

#define FLAGS 0x00001215

#define THIS ((EnBigpo*)thisx)

void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bigpo_InitVars = {
    ACTOR_EN_BIGPO,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_BIGPO,
    sizeof(EnBigpo),
    (ActorFunc)EnBigpo_Init,
    (ActorFunc)EnBigpo_Destroy,
    (ActorFunc)EnBigpo_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/EnBigpo_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/EnBigpo_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61914.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B619B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B619FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61AC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61B38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61CFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61D74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61E9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B61F04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62034.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62154.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B621CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B622E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B623BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B624F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B6259C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B6275C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B627B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62814.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62900.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B629E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62A68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62AD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62B10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62E38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62F10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B62FCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B631F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63264.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B632BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B6330C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B633E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63450.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63474.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B636D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B636E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63758.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B6382C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B6383C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63888.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B638AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B638D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63964.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63980.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63A18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63AC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63C28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63D0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B63D88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/EnBigpo_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B64190.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B641E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B64240.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B64470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B6467C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B64880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B64B08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bigpo_0x80B615E0/func_80B64DFC.asm")
