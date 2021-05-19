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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C192A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C192B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C193A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1950C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1965C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19688.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1985C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1987C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C199BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C199EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19D48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19E04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19EC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A038.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A6C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Draw.asm")
