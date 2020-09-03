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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_RR,
    sizeof(EnRr),
    (ActorFunc)EnRr_Init,
    (ActorFunc)EnRr_Destroy,
    (ActorFunc)EnRr_Update,
    (ActorFunc)EnRr_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/EnRr_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/EnRr_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA01C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA11C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA19C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA238.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA344.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA3F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA4F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA6B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA7AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FA9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FAA94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FAC80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FAD1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FAE50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FAF94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB1C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB2C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB42C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB710.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/func_808FB794.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/EnRr_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rr_0x808F9E00/EnRr_Draw.asm")
