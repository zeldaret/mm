#include "z_en_karebaba.h"

#define FLAGS 0x00000005

#define THIS ((EnKarebaba*)thisx)

void EnKarebaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKarebaba_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Karebaba_InitVars = {
    ACTOR_EN_KAREBABA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(EnKarebaba),
    (ActorFunc)EnKarebaba_Init,
    (ActorFunc)EnKarebaba_Destroy,
    (ActorFunc)EnKarebaba_Update,
    (ActorFunc)EnKarebaba_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F13FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F152C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F155C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F15B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F169C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F16FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F190C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1A3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1A58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F1FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F200C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F20FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F21A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F220C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F228C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F238C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F241C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F24F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F254C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/func_808F280C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Karebaba_0x808F1200/EnKarebaba_Draw.asm")
