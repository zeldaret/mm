#include "z_dm_char07.h"

#define FLAGS 0x00000030

#define THIS ((DmChar07*)thisx)

void DmChar07_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar07_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Char07_InitVars = {
    ACTOR_DM_CHAR07,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MILKBAR,
    sizeof(DmChar07),
    (ActorFunc)DmChar07_Init,
    (ActorFunc)DmChar07_Destroy,
    (ActorFunc)DmChar07_Update,
    (ActorFunc)DmChar07_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char07/func_80AAE9C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char07/DmChar07_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char07/DmChar07_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char07/func_80AAEABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char07/DmChar07_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char07/DmChar07_Draw.s")
