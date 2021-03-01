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
    (ActorFunc)EnSb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/EnSb_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/EnSb_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E401C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E40CC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4144.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E41C0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4234.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E42DC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4354.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4458.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E44D4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E45A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4654.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4740.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E47E8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E491C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4984.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/EnSb_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/func_808E4C18.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Sb_0x808E3EF0/EnSb_Draw.asm")
