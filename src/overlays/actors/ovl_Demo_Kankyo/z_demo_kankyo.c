#include "z_demo_kankyo.h"

#define FLAGS 0x00000030

#define THIS ((DemoKankyo*)thisx)

void DemoKankyo_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoKankyo_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Demo_Kankyo_InitVars = {
    ACTOR_DEMO_KANKYO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoKankyo),
    (ActorFunc)DemoKankyo_Init,
    (ActorFunc)DemoKankyo_Destroy,
    (ActorFunc)DemoKankyo_Update,
    (ActorFunc)DemoKankyo_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CE450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CE45C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CF06C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CF0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/DemoKankyo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/DemoKankyo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/DemoKankyo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CF970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/func_808CFE04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Demo_Kankyo_0x808CE450/DemoKankyo_Draw.asm")
