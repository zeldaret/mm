#include "z_en_jso.h"

#define FLAGS 0x00000015

#define THIS ((EnJso*)thisx)

void EnJso_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJso_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJso_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Jso_InitVars = {
    ACTOR_EN_JSO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_JSO,
    sizeof(EnJso),
    (ActorFunc)EnJso_Init,
    (ActorFunc)EnJso_Destroy,
    (ActorFunc)EnJso_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/EnJso_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/EnJso_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809ADBC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809ADC7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809ADCB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AE754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AE87C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AE9B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AEA08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AECA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AED00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AED54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AEDAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AEE44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AEEC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF2F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF368.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF3C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF3FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF53C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF5F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF76C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF8D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AF99C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AFA58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AFAF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AFC10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809AFE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809B0034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/EnJso_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809B0734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809B0820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809B0B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jso/func_809B0BB0.s")
