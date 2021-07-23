#include "z_en_mt_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnMttag*)thisx)

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Mt_tag_InitVars = {
    ACTOR_EN_MT_TAG,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMttag),
    (ActorFunc)EnMttag_Init,
    (ActorFunc)EnMttag_Destroy,
    (ActorFunc)EnMttag_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CF9A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFA00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFA54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFC38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFD98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFE28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/func_809CFF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/EnMttag_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/EnMttag_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mt_tag/EnMttag_Update.s")
