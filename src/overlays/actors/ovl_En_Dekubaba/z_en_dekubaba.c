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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B15B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B16BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1798.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1814.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B18A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B28B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B29C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2C40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2CB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3390.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B37E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B39AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3BE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3D74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B4548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B465C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B48FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B49C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B4ABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Draw.asm")
