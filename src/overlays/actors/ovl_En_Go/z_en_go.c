#include "z_en_go.h"

#define FLAGS 0x02000019

#define THIS ((EnGo*)thisx)

void EnGo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGo_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Go_InitVars = {
    ACTOR_EN_GO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGo),
    (ActorFunc)EnGo_Init,
    (ActorFunc)EnGo_Destroy,
    (ActorFunc)EnGo_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A10FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A11144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A1143C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A115B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A118F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A11BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A11EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A1203C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A1213C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A121F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A1222C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A122EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A123A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A124A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A124FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A125BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A126BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12B78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12E80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A12FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A131F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A132C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A133A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A13400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A134B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A134F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A13564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A136B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A13728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A137C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A139E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A13B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A13E80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A141D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A1428C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A143A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A1449C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A144F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A145AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A146CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A149B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14EB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A14FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A153FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A15684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A157C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/EnGo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/EnGo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/EnGo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A15B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A15D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A15E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Go/func_80A15FEC.s")
