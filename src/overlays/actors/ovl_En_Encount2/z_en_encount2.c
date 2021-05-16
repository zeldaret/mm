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
    (ActorFunc)EnEncount2_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/EnEncount2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/EnEncount2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/func_808E16FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/func_808E1714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/func_808E17C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/func_808E18A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/EnEncount2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/EnEncount2_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/func_808E1A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/func_808E1B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount2/func_808E1C9C.s")
