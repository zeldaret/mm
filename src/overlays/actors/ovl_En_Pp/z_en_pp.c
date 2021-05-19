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
    (ActorFunc)EnPp_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E3D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E5A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1E970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1EBD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1EC24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1EFFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F29C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F4A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F6B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1F940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1FAD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1FC7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B1FF20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B202B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B203BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20E6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/func_80B20F70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pp_0x80B1DEB0/EnPp_Draw.asm")
