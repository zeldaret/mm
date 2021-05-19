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
    (ActorFunc)DmStk_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80A9FDB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80A9FE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80A9FED8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA00CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0100.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA01C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0264.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0420.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA05F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA066C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA071C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA076C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA09DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0E1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA0E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA16F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA17F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA18D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA192C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA19EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1A50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1AC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA1D1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA26CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA2720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA27EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA2B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA2BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/func_80AA33A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Stk_0x80A9FDB0/DmStk_Draw.asm")
