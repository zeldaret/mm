#include "z_en_clear_tag.h"

#define FLAGS 0x00000035

#define THIS ((EnClearTag*)thisx)

void EnClearTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Clear_Tag_InitVars = {
    ACTOR_EN_CLEAR_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnClearTag),
    (ActorFunc)EnClearTag_Init,
    (ActorFunc)EnClearTag_Destroy,
    (ActorFunc)EnClearTag_Update,
    (ActorFunc)EnClearTag_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_80947F60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_809480C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_80948264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_809484EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_809485A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_80948788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_8094899C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_80948A54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/EnClearTag_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/EnClearTag_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_80949288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/EnClearTag_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/EnClearTag_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_809495F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Clear_Tag/func_80949BD4.s")
