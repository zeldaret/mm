#include "z_en_okuta.h"

#define FLAGS 0x00000005

#define THIS ((EnOkuta*)thisx)

void EnOkuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOkuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOkuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnOkuta_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Okuta_InitVars = {
    ACTOR_EN_OKUTA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_OKUTA,
    sizeof(EnOkuta),
    (ActorFunc)EnOkuta_Init,
    (ActorFunc)EnOkuta_Destroy,
    (ActorFunc)EnOkuta_Update,
    (ActorFunc)EnOkuta_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/EnOkuta_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/EnOkuta_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E0F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E4FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E52C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E7A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E7E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086E948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086EAE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086EC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086EE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086EF14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086EF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086EFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086F2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086F434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086F4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086F4F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086F57C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086F694.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086F8FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_8086FCA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/EnOkuta_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_808700C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_80870254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_808704DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/func_808705C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Okuta/EnOkuta_Draw.s")
