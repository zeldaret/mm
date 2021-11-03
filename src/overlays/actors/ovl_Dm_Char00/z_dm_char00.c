/*
 * File: z_dm_char00.c
 * Overlay: ovl_Dm_Char00
 * Description: Tatl and Tael (cutscene)
 */

#include "z_dm_char00.h"

#define FLAGS 0x00000030

#define THIS ((DmChar00*)thisx)

void DmChar00_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar00_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA561C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA575C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA58CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA59E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5A6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5CD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA5EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/DmChar00_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/DmChar00_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA62FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA67F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA695C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/DmChar00_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/func_80AA6A6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char00/DmChar00_Draw.s")
