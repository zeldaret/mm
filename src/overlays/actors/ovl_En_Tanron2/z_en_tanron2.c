#include "z_en_tanron2.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron2*)thisx)

void EnTanron2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tanron2_InitVars = {
    ACTOR_EN_TANRON2,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(EnTanron2),
    (ActorFunc)EnTanron2_Init,
    (ActorFunc)EnTanron2_Destroy,
    (ActorFunc)EnTanron2_Update,
    (ActorFunc)EnTanron2_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB69C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB69FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6BD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB71C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Draw.s")
