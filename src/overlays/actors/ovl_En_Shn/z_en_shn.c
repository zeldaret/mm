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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SHN,
    sizeof(EnShn),
    (ActorFunc)EnShn_Init,
    (ActorFunc)EnShn_Destroy,
    (ActorFunc)EnShn_Update,
    (ActorFunc)EnShn_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6130.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE615C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE61C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE625C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE626C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE63A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE65F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6704.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE68F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE69E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/EnShn_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/EnShn_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/EnShn_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6D40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/func_80AE6D90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Shn_0x80AE6130/EnShn_Draw.asm")
