#include "z_en_vm.h"

#define FLAGS 0x00000405

#define THIS ((EnVm*)thisx)

void EnVm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Vm_InitVars = {
    ACTOR_EN_VM,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_VM,
    sizeof(EnVm),
    (ActorFunc)EnVm_Init,
    (ActorFunc)EnVm_Destroy,
    (ActorFunc)EnVm_Update,
    (ActorFunc)EnVm_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC420.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC5C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCB08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCB50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCBE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCDE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CD020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CD08C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Draw.s")
