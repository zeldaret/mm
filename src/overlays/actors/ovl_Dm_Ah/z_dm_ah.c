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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AH,
    sizeof(DmAh),
    (ActorFunc)DmAh_Init,
    (ActorFunc)DmAh_Destroy,
    (ActorFunc)DmAh_Update,
    (ActorFunc)DmAh_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1D410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1D458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1D4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1D6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1D78C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1D7FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1D92C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/DmAh_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/DmAh_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/DmAh_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1DAD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/func_80C1DB24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Ah_0x80C1D410/DmAh_Draw.asm")
