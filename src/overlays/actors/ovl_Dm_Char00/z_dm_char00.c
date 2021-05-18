#include "z_dm_char00.h"

#define FLAGS 0x00000030

#define THIS ((DmChar00*)thisx)

void DmChar00_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Char00_InitVars = {
    ACTOR_DM_CHAR00,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_DELF,
    sizeof(DmChar00),
    (ActorFunc)DmChar00_Init,
    (ActorFunc)DmChar00_Destroy,
    (ActorFunc)DmChar00_Update,
    (ActorFunc)DmChar00_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA561C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA575C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA58CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA59E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5A6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5AF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5CD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA5EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/DmChar00_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/DmChar00_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA62FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA67F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA695C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/DmChar00_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/func_80AA6A6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char00_0x80AA5580/DmChar00_Draw.asm")
