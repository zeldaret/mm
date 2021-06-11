#include "z_en_invadepoh_demo.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepohDemo*)thisx)

void EnInvadepohDemo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepohDemo_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Invadepoh_Demo_InitVars = {
    ACTOR_EN_INVADEPOH_DEMO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepohDemo),
    (ActorFunc)EnInvadepohDemo_Init,
    (ActorFunc)EnInvadepohDemo_Destroy,
    (ActorFunc)EnInvadepohDemo_Update,
    (ActorFunc)EnInvadepohDemo_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C192A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C192B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C193A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1950C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1965C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1985C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1987C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C199BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C199EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19E04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C19F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A6C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/func_80C1A854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Invadepoh_Demo/EnInvadepohDemo_Draw.s")
