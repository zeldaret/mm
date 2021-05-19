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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_80947F60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_809480C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_80948264.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_809484EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_809485A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_80948788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_8094899C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_80948A54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/EnClearTag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/EnClearTag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_80949288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/EnClearTag_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/EnClearTag_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_809495F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Clear_Tag_0x80947F60/func_80949BD4.asm")
