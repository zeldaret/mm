#include "z_en_estone.h"

#define FLAGS 0x00000030

#define THIS ((EnEstone*)thisx)

void EnEstone_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Estone_InitVars = {
    ACTOR_EN_ESTONE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_EG,
    sizeof(EnEstone),
    (ActorFunc)EnEstone_Init,
    (ActorFunc)EnEstone_Destroy,
    (ActorFunc)EnEstone_Update,
    (ActorFunc)EnEstone_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A1DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A9C0.s")
