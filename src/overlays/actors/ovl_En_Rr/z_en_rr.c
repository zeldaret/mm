#include "z_en_rr.h"

#define FLAGS 0x00000405

#define THIS ((EnRr*)thisx)

void EnRr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rr_InitVars = {
    ACTOR_EN_RR,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RR,
    sizeof(EnRr),
    (ActorFunc)EnRr_Init,
    (ActorFunc)EnRr_Destroy,
    (ActorFunc)EnRr_Update,
    (ActorFunc)EnRr_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/EnRr_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/EnRr_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA01C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA11C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA19C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA3F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA4F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA6B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA7AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FA9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FAA94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FAC80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FAD1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FAE50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FAF94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB1C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB2C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB42C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/func_808FB794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/EnRr_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rr_0x808F9E00/EnRr_Draw.asm")
