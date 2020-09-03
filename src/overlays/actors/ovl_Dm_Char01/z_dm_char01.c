#include "z_dm_char01.h"

#define FLAGS 0x02000030

#define THIS ((DmChar01*)thisx)

void DmChar01_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Char01_InitVars = {
    ACTOR_DM_CHAR01,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_MTORIDE,
    sizeof(DmChar01),
    (ActorFunc)DmChar01_Init,
    (ActorFunc)DmChar01_Destroy,
    (ActorFunc)DmChar01_Update,
    (ActorFunc)DmChar01_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/DmChar01_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/DmChar01_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA8698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA884C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA88A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA892C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA8C28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA8F0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA8F1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA8F2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA9020.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA90AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/func_80AA90F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/DmChar01_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Char01_0x80AA81E0/DmChar01_Draw.asm")
