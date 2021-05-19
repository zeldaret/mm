#include "z_en_cne_01.h"

#define FLAGS 0x00000019

#define THIS ((EnCne01*)thisx)

void EnCne01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Cne_01_InitVars = {
    ACTOR_EN_CNE_01,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnCne01),
    (ActorFunc)EnCne01_Init,
    (ActorFunc)EnCne01_Destroy,
    (ActorFunc)EnCne01_Update,
    (ActorFunc)EnCne01_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB4A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB5A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB5D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB5FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CBBC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CBCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Draw.asm")
