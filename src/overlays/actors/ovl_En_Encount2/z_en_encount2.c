#include "z_en_encount2.h"

#define FLAGS 0x00000010

#define THIS ((EnEncount2*)thisx)

void EnEncount2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEncount2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Encount2_InitVars = {
    ACTOR_EN_ENCOUNT2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnEncount2),
    (ActorFunc)EnEncount2_Init,
    (ActorFunc)EnEncount2_Destroy,
    (ActorFunc)EnEncount2_Update,
    (ActorFunc)EnEncount2_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/EnEncount2_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/EnEncount2_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/func_808E16FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/func_808E1714.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/func_808E17C4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/func_808E18A8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/EnEncount2_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/EnEncount2_Draw.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/func_808E1A24.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/func_808E1B4C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Encount2_0x808E1560/func_808E1C9C.asm")
