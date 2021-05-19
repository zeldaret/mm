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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/func_8091FEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/ItemEtcetera_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/ItemEtcetera_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/func_80920044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/func_8092009C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/func_809200F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/ItemEtcetera_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/func_80920164.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Item_Etcetera_0x8091FEF0/func_809201BC.asm")
