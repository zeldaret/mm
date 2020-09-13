#include "z_en_hs2.h"

#define FLAGS 0x00000009

#define THIS ((EnHs2*)thisx)

void EnHs2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHs2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hs2_InitVars = {
    ACTOR_EN_HS2,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHs2),
    (ActorFunc)EnHs2_Init,
    (ActorFunc)EnHs2_Destroy,
    (ActorFunc)EnHs2_Update,
    (ActorFunc)EnHs2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Hs2_0x8098EF60/EnHs2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hs2_0x8098EF60/EnHs2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hs2_0x8098EF60/func_8098EFAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hs2_0x8098EF60/EnHs2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hs2_0x8098EF60/EnHs2_Draw.asm")
