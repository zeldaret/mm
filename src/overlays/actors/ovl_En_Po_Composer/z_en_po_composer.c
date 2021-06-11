#include "z_en_po_composer.h"

#define FLAGS 0x02100019

#define THIS ((EnPoComposer*)thisx)

void EnPoComposer_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoComposer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoComposer_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoComposer_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Po_Composer_InitVars = {
    ACTOR_EN_PO_COMPOSER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_PO_COMPOSER,
    sizeof(EnPoComposer),
    (ActorFunc)EnPoComposer_Init,
    (ActorFunc)EnPoComposer_Destroy,
    (ActorFunc)EnPoComposer_Update,
    (ActorFunc)EnPoComposer_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/EnPoComposer_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/EnPoComposer_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC52D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC52F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC538C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC53A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC53B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC552C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC55E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC562C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC56D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC57E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5898.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC58E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC59BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC59EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5CC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5D34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC5FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/EnPoComposer_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC60BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/func_80BC617C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Composer/EnPoComposer_Draw.s")
