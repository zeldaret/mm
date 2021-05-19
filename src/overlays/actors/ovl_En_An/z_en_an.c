#include "z_en_an.h"

#define FLAGS 0x00000039

#define THIS ((EnAn*)thisx)

void EnAn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAn_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_An_InitVars = {
    ACTOR_EN_AN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(EnAn),
    (ActorFunc)EnAn_Init,
    (ActorFunc)EnAn_Destroy,
    (ActorFunc)EnAn_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B53840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B539CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B53A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B53B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B53BA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B53CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B53ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B53F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B546F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B547C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B5492C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54BC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54C5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54D18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B54DF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B55180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B552E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B553AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B554E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B555C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B556F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B557AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B55860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B55914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B55D20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B55D98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B55ECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B55F8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B5600C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B5611C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B561A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56744.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56B00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56CAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56E44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B56EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B5702C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B572D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B573F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B575BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B57674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B57718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B577F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B578F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B57A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B57B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/EnAn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/EnAn_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/EnAn_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B57EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B57FC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_An_0x80B53840/func_80B580C0.asm")
