#include "z_en_maruta.h"

#define FLAGS 0x00000011

#define THIS ((EnMaruta*)thisx)

void EnMaruta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMaruta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMaruta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMaruta_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Maruta_InitVars = {
    ACTOR_EN_MARUTA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_MARUTA,
    sizeof(EnMaruta),
    (ActorFunc)EnMaruta_Init,
    (ActorFunc)EnMaruta_Destroy,
    (ActorFunc)EnMaruta_Update,
    (ActorFunc)EnMaruta_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/EnMaruta_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/EnMaruta_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B372B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B372CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B3738C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B373F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B374B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B374FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B379C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37A14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37B78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37CA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B37EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B38028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B38060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B3828C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/func_80B382E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/EnMaruta_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Maruta/EnMaruta_Draw.s")
