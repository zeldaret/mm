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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmStk),
    (ActorFunc)DmStk_Init,
    (ActorFunc)DmStk_Destroy,
    (ActorFunc)DmStk_Update,
    (ActorFunc)DmStk_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80A9FDB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80A9FE3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80A9FED8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA00CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0100.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0158.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA01C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0264.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0420.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA05F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA066C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA071C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA076C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA09DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0B08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0DA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0E1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA0E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/DmStk_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/DmStk_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA16F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1704.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1714.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA17F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA18D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA192C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1998.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA19EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1A50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1AC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1B9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1C64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA1D1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA26CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA2720.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA27EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/DmStk_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA2B14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA2BC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/func_80AA33A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Stk_0x80A9FDB0/DmStk_Draw.asm")
