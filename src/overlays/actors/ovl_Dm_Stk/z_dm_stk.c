#include "z_dm_stk.h"

#define FLAGS 0x02000030

#define THIS ((DmStk*)thisx)

void DmStk_Init(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Update(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Stk_InitVars = {
    ACTOR_DM_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmStk),
    (ActorFunc)DmStk_Init,
    (ActorFunc)DmStk_Destroy,
    (ActorFunc)DmStk_Update,
    (ActorFunc)DmStk_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80A9FDB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80A9FE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80A9FED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA00CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA01C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0420.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA05F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA066C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA071C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA076C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA09DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA0E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA16F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA17F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA18D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA192C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA19EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA1D1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA26CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA2720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA27EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA2B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA2BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/func_80AA33A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Stk/DmStk_Draw.s")
