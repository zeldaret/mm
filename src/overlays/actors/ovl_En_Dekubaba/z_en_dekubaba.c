#include "z_en_dekubaba.h"

#define FLAGS 0x00000405

#define THIS ((EnDekubaba*)thisx)

void EnDekubaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dekubaba_InitVars = {
    ACTOR_EN_DEKUBABA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(EnDekubaba),
    (ActorFunc)EnDekubaba_Init,
    (ActorFunc)EnDekubaba_Destroy,
    (ActorFunc)EnDekubaba_Update,
    (ActorFunc)EnDekubaba_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B15B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B16BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B18A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B28B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B29C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B37E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B39AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3D74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B4548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B465C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B48FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B49C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B4ABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Draw.s")
