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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC52D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC52F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC538C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC53A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC53B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC552C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC55E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC562C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC56D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5738.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC57E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5898.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC58E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC59BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC59EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5CC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC5FE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC60BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/func_80BC617C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Po_Composer_0x80BC4F30/EnPoComposer_Draw.asm")
