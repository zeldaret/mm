#include "z_en_mt_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnMttag*)thisx)

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF4EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF67C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF8EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CF9A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CFA00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CFA54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CFBC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CFC38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CFD98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CFE28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/func_809CFF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/EnMttag_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/EnMttag_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mt_tag_0x809CF350/EnMttag_Update.asm")
