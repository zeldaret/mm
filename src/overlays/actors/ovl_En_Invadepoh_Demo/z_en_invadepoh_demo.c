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
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepohDemo),
    (ActorFunc)EnInvadepohDemo_Init,
    (ActorFunc)EnInvadepohDemo_Destroy,
    (ActorFunc)EnInvadepohDemo_Update,
    (ActorFunc)EnInvadepohDemo_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C192A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C192B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19334.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C193A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19454.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19498.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1950C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19548.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19564.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1965C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19688.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19754.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1985C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1987C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C199BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C199EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19AB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19D00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19D48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19E04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19EC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C19F7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A038.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A650.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A6C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/func_80C1A854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Invadepoh_Demo_0x80C192A0/EnInvadepohDemo_Draw.asm")
