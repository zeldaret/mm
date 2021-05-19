#include "z_en_ah.h"

#define FLAGS 0x00000039

#define THIS ((EnAh*)thisx)

void EnAh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ah_InitVars = {
    ACTOR_EN_AH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AH,
    sizeof(EnAh),
    (ActorFunc)EnAh_Init,
    (ActorFunc)EnAh_Destroy,
    (ActorFunc)EnAh_Update,
    (ActorFunc)EnAh_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2A30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2B0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2BA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2BE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2C6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD2FD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD30C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3320.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD33FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD35BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD36B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/EnAh_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/EnAh_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/EnAh_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3AA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/func_80BD3AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ah_0x80BD2A30/EnAh_Draw.asm")
