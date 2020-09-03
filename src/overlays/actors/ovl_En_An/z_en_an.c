#include "z_en_an.h"

#define FLAGS 0x00000039

#define THIS ((EnAn*)thisx)

void EnAn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAn_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_An_InitVars = {
    ACTOR_EN_AN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(EnAn),
    (ActorFunc)EnAn_Init,
    (ActorFunc)EnAn_Destroy,
    (ActorFunc)EnAn_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B53840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B539CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B53A7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B53B3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B53BA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B53CE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B53ED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B53F84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54124.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54678.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B546F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54750.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B547C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B5492C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54A94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54BC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54C5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54D18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B54DF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B55180.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B552E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B553AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B554E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B555C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B556F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B557AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B55860.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B55914.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B55D20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B55D98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B55ECC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B55F8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B5600C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56094.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B5611C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B561A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56418.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56744.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56B00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56BC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56CAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56E44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B56EB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B5702C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B572D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B573F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B575BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B57674.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B57718.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B577F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B578F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B57A44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B57B48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/EnAn_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/EnAn_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/EnAn_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B57EE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B57FC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_An_0x80B53840/func_80B580C0.asm")
