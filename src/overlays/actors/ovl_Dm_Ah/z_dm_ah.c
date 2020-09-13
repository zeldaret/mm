#include "z_dm_ah.h"

#define FLAGS 0x00000009

#define THIS ((DmAh*)thisx)

void DmAh_Init(Actor* thisx, GlobalContext* globalCtx);
void DmAh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmAh_Update(Actor* thisx, GlobalContext* globalCtx);
void DmAh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Ah_InitVars = {
    ACTOR_DM_AH,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_AH,
    sizeof(DmAh),
    (ActorFunc)DmAh_Init,
    (ActorFunc)DmAh_Destroy,
    (ActorFunc)DmAh_Update,
    (ActorFunc)DmAh_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1D410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1D458.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1D4D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1D6E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1D78C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1D7FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1D92C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/DmAh_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/DmAh_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/DmAh_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1DAD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/func_80C1DB24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ah_0x80C1D410/DmAh_Draw.asm")
