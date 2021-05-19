#include "z_en_sth.h"

#define FLAGS 0x00000009

#define THIS ((EnSth*)thisx)

void EnSth_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sth_InitVars = {
    ACTOR_EN_STH,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSth),
    (ActorFunc)EnSth_Init,
    (ActorFunc)EnSth_Destroy,
    (ActorFunc)EnSth_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/EnSth_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/EnSth_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B6703C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B670A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B671A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B672A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B677BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B678A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67B50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/EnSth_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B680A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B681E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B68310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B6849C.asm")
