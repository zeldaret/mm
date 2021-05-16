#include "z_item_etcetera.h"

#define FLAGS 0x00000010

#define THIS ((ItemEtcetera*)thisx)

void ItemEtcetera_Init(Actor* thisx, GlobalContext* globalCtx);
void ItemEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ItemEtcetera_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Item_Etcetera_InitVars = {
    ACTOR_ITEM_ETCETERA,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ItemEtcetera),
    (ActorFunc)ItemEtcetera_Init,
    (ActorFunc)ItemEtcetera_Destroy,
    (ActorFunc)ItemEtcetera_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_8091FEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/ItemEtcetera_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/ItemEtcetera_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_80920044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_8092009C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_809200F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/ItemEtcetera_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_80920164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_809201BC.s")
