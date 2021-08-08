#include "z_en_shn.h"

#define FLAGS 0x00000009

#define THIS ((EnShn*)thisx)

void EnShn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnShn_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE69E8(EnShn* this, GlobalContext* globalCtx);
void func_80AE6A64(EnShn* this, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_0600B738;
extern UNK_TYPE D_0600E7D0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE615C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE61C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE625C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE626C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE63A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE65F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE68F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE69E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/func_80AE6D90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Shn/EnShn_Draw.s")
