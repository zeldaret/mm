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
    (ActorFunc)EnVm_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/EnVm_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/EnVm_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CC420.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CC490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CC5C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CC610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CC788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CC820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CCA10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CCAA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CCB08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CCB50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CCBE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CCCF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CCDE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/EnVm_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CD020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/func_808CD08C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Vm_0x808CC260/EnVm_Draw.asm")
