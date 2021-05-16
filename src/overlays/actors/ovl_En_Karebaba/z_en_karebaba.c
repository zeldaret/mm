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
    (ActorFunc)EnKarebaba_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/EnKarebaba_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/EnKarebaba_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F13FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F152C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F155C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F15B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F169C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F16FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F190C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1A3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1A58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F1FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F200C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F20FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F21A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F220C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F228C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F238C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F241C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F24F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F254C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/EnKarebaba_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/func_808F280C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Karebaba/EnKarebaba_Draw.s")
