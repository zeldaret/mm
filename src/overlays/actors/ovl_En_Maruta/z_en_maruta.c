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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_MARUTA,
    sizeof(EnMaruta),
    (ActorFunc)EnMaruta_Init,
    (ActorFunc)EnMaruta_Destroy,
    (ActorFunc)EnMaruta_Update,
    (ActorFunc)EnMaruta_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/EnMaruta_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/EnMaruta_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B372B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B372CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37364.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B3738C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B373F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37428.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B374B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B374FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37998.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B379C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37A14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37A8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37AA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37B78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37C60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37CA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B37EC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B38028.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B38060.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B3828C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/func_80B382E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/EnMaruta_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Maruta_0x80B37080/EnMaruta_Draw.asm")
