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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/EnJso_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/EnJso_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809ADBC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809ADC7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809ADCB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AE754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AE87C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AE9B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEA08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AECA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AED00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AED54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEDAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEE44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AEEC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF28C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF2F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF3C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF3FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF53C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF76C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF8D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AF99C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFA58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFAF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFC10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809AFE38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/EnJso_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jso_0x809AD8E0/func_809B0BB0.asm")
