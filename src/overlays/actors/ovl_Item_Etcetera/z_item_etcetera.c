/*
 * File: z_item_etcetera.c
 * Overlay: ovl_Item_Etcetera
 * Description: Leftover OoT Collectible Items (bottle, key, Fire Arrow, etc.)
 */

#include "z_item_etcetera.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ItemEtcetera*)thisx)

void ItemEtcetera_Init(Actor* thisx, GlobalContext* globalCtx);
void ItemEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ItemEtcetera_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80920044(ItemEtcetera* this, GlobalContext* globalCtx);

void ItemEtcetera_SetupAction(ItemEtcetera* this, ItemEtceteraActionFunc actionFunc);

#if 0
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

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/ItemEtcetera_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/ItemEtcetera_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/ItemEtcetera_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_80920044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_8092009C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_809200F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/ItemEtcetera_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_80920164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Item_Etcetera/func_809201BC.s")
