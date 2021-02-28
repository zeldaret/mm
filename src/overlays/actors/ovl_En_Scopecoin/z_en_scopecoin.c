#include "z_en_scopecoin.h"

#define FLAGS 0x00000030

#define THIS ((EnScopecoin*)thisx)

void EnScopecoin_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Scopecoin_InitVars = {
    ACTOR_EN_SCOPECOIN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnScopecoin),
    (ActorFunc)EnScopecoin_Init,
    (ActorFunc)EnScopecoin_Destroy,
    (ActorFunc)EnScopecoin_Update,
    (ActorFunc)EnScopecoin_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Scopecoin_0x80BFCFA0/func_80BFCFA0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Scopecoin_0x80BFCFA0/func_80BFCFB8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Scopecoin_0x80BFCFA0/EnScopecoin_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Scopecoin_0x80BFCFA0/EnScopecoin_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Scopecoin_0x80BFCFA0/EnScopecoin_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Scopecoin_0x80BFCFA0/EnScopecoin_Draw.asm")
