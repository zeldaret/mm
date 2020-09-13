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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(EnKarebaba),
    (ActorFunc)EnKarebaba_Init,
    (ActorFunc)EnKarebaba_Destroy,
    (ActorFunc)EnKarebaba_Update,
    (ActorFunc)EnKarebaba_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/EnKarebaba_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/EnKarebaba_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1374.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F13FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F152C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F155C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F15B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F169C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F16FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1878.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F190C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1A3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1A58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1BF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1C84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F1FAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F200C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F20FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F21A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F220C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F228C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F238C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F241C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F24F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F254C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/EnKarebaba_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/func_808F280C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Karebaba_0x808F1200/EnKarebaba_Draw.asm")
