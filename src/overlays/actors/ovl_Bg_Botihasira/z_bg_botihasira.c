#include "z_bg_botihasira.h"

#define FLAGS 0x00000000

#define THIS ((BgBotihasira*)thisx)

void BgBotihasira_Init(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Update(Actor* thisx, GlobalContext* globalCtx);
void BgBotihasira_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Botihasira_InitVars = {
    ACTOR_BG_BOTIHASIRA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOTIHASIRA,
    sizeof(BgBotihasira),
    (ActorFunc)BgBotihasira_Init,
    (ActorFunc)BgBotihasira_Destroy,
    (ActorFunc)BgBotihasira_Update,
    (ActorFunc)BgBotihasira_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/func_80B2815C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Botihasira_0x80B28080/BgBotihasira_Draw.asm")
