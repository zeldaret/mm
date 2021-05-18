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
    (ActorFunc)EnOkuta_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E0F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E2C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E3B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E4FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E52C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E7A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E7E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E8E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086E948.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EAE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EC00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EF14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086EFE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F4B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F4F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F57C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086F8FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_8086FCA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_808700C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_80870254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_808704DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/func_808705C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Okuta_0x8086DE20/EnOkuta_Draw.asm")
