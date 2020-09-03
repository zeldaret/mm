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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_PP,
    sizeof(EnPp),
    (ActorFunc)EnPp_Init,
    (ActorFunc)EnPp_Destroy,
    (ActorFunc)EnPp_Update,
    (ActorFunc)EnPp_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/EnPp_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/EnPp_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1E29C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1E3D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1E5A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1E680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1E778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1E958.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1E970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1EBD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1EC24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1EFFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F0A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F188.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F29C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F4A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F560.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F664.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F6B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F770.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1F940.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1FAD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1FC7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B1FF20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B20030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B202B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B203BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B20668.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/EnPp_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B20E6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/func_80B20F70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pp_0x80B1DEB0/EnPp_Draw.asm")
