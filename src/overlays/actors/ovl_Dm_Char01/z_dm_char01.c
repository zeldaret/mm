/*
 * File: z_dm_char01.c
 * Overlay: ovl_Dm_Char01
 * Description: Woodfall scene objects (temple, water, walls, etc)
 */

#include "z_dm_char01.h"

#define FLAGS 0x02000030

#define THIS ((DmChar01*)thisx)

void DmChar01_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Dm_Char01_InitVars = {
    ACTOR_DM_CHAR01,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MTORIDE,
    sizeof(DmChar01),
    (ActorFunc)DmChar01_Init,
    (ActorFunc)DmChar01_Destroy,
    (ActorFunc)DmChar01_Update,
    (ActorFunc)DmChar01_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AAAAB0[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AAAAB0[];

extern UNK_TYPE D_06009E4C;
extern UNK_TYPE D_0600AA50;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/DmChar01_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/DmChar01_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA8698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA884C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA88A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA892C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA8C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA8F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA8F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA8F2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA9020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA90AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/func_80AA90F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/DmChar01_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char01/DmChar01_Draw.s")
