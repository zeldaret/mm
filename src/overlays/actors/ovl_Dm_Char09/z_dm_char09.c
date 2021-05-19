#include "z_dm_char09.h"

#define FLAGS 0x00000030

#define THIS ((DmChar09*)thisx)

void DmChar09_Init(Actor* thisx, GlobalContext* globalCtx);
void DmChar09_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmChar09_Update(Actor* thisx, GlobalContext* globalCtx);
void DmChar09_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Char09_InitVars = {
    ACTOR_DM_CHAR09,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BEE,
    sizeof(DmChar09),
    (ActorFunc)DmChar09_Init,
    (ActorFunc)DmChar09_Destroy,
    (ActorFunc)DmChar09_Update,
    (ActorFunc)DmChar09_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/func_80AB1E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/DmChar09_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/DmChar09_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/func_80AB1FA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/func_80AB1FDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/func_80AB2258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/func_80AB2268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/func_80AB24BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/DmChar09_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/func_80AB25D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Char09_0x80AB1E10/DmChar09_Draw.asm")
