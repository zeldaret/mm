#include "z_dm_an.h"

#define FLAGS 0x00000009

#define THIS ((DmAn*)thisx)

void DmAn_Init(Actor* thisx, GlobalContext* globalCtx);
void DmAn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmAn_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_An_InitVars = {
    ACTOR_DM_AN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(DmAn),
    (ActorFunc)DmAn_Init,
    (ActorFunc)DmAn_Destroy,
    (ActorFunc)DmAn_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1C410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1C4D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1C5B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1C62C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1C83C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1C8E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1C958.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1CAB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1CC80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/DmAn_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/DmAn_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/DmAn_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1CD80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1CEFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_An_0x80C1C410/func_80C1D0B0.asm")
