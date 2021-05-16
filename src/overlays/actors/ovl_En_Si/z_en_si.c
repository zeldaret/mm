#include "z_en_si.h"

#define FLAGS 0x00000201

#define THIS ((EnSi*)thisx)

void EnSi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Si_InitVars = {
    ACTOR_EN_SI,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSi),
    (ActorFunc)EnSi_Init,
    (ActorFunc)EnSi_Destroy,
    (ActorFunc)EnSi_Update,
    (ActorFunc)EnSi_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/func_8098CA20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/func_8098CAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/func_8098CB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/func_8098CBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/EnSi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/EnSi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/EnSi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Si/EnSi_Draw.s")
