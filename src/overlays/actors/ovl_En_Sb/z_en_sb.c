#include "z_en_sb.h"

#define FLAGS 0x00000005

#define THIS ((EnSb*)thisx)

void EnSb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sb_InitVars = {
    ACTOR_EN_SB,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SB,
    sizeof(EnSb),
    (ActorFunc)EnSb_Init,
    (ActorFunc)EnSb_Destroy,
    (ActorFunc)EnSb_Update,
    (ActorFunc)EnSb_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/EnSb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/EnSb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E401C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E40CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E41C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E42DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E44D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E45A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4654.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E47E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E491C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/EnSb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/func_808E4C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sb/EnSb_Draw.s")
