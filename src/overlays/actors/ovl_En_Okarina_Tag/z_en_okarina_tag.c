#include "z_en_okarina_tag.h"

#define FLAGS 0x0A000010

#define THIS ((EnOkarinaTag*)thisx)

void EnOkarinaTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaTag_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Okarina_Tag_InitVars = {
    ACTOR_EN_OKARINA_TAG,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOkarinaTag),
    (ActorFunc)EnOkarinaTag_Init,
    (ActorFunc)EnOkarinaTag_Destroy,
    (ActorFunc)EnOkarinaTag_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okarina_Tag_0x8093E420/EnOkarinaTag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okarina_Tag_0x8093E420/EnOkarinaTag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okarina_Tag_0x8093E420/func_8093E518.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okarina_Tag_0x8093E420/func_8093E68C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okarina_Tag_0x8093E420/EnOkarinaTag_Update.asm")
