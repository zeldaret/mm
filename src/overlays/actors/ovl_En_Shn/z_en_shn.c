#include "z_en_shn.h"

#define FLAGS 0x00000009

#define THIS ((EnShn*)thisx)

void EnShn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Shn_InitVars = {
    ACTOR_EN_SHN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SHN,
    sizeof(EnShn),
    (ActorFunc)EnShn_Init,
    (ActorFunc)EnShn_Destroy,
    (ActorFunc)EnShn_Update,
    (ActorFunc)EnShn_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE615C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE61C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE625C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE626C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE63A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE65F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE68F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE69E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/EnShn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/EnShn_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/EnShn_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/func_80AE6D90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Shn_0x80AE6130/EnShn_Draw.asm")
