/*
 * File: z_en_okarina_tag.c
 * Overlay: ovl_En_Okarina_Tag
 * Description:
 */

#include "z_en_okarina_tag.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000 | ACTOR_FLAG_8000000)

#define THIS ((EnOkarinaTag*)thisx)

void EnOkarinaTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaTag_Update(Actor* thisx, GlobalContext* globalCtx);

void func_8093E518(EnOkarinaTag* this, GlobalContext* globalCtx);
void func_8093E68C(EnOkarinaTag* this, GlobalContext* globalCtx);

#if 0
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

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okarina_Tag/EnOkarinaTag_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okarina_Tag/EnOkarinaTag_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okarina_Tag/func_8093E518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okarina_Tag/func_8093E68C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okarina_Tag/EnOkarinaTag_Update.s")
