#include "z_en_pp.h"

#define FLAGS 0x00000005

#define THIS ((EnPp*)thisx)

void EnPp_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPp_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPp_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPp_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Pp_InitVars = {
    ACTOR_EN_PP,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PP,
    sizeof(EnPp),
    (ActorFunc)EnPp_Init,
    (ActorFunc)EnPp_Destroy,
    (ActorFunc)EnPp_Update,
    (ActorFunc)EnPp_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/EnPp_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/EnPp_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1E29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1E3D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1E5A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1E680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1E778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1E958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1E970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1EBD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1EC24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1EFFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F4A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F6B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1F940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1FAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1FC7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B1FF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B20030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B202B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B203BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B20668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/EnPp_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B20E6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/func_80B20F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pp/EnPp_Draw.s")
