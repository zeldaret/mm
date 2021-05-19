#include "z_en_mm2.h"

#define FLAGS 0x00000010

#define THIS ((EnMm2*)thisx)

void EnMm2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Mm2_InitVars = {
    ACTOR_EN_MM2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMm2),
    (ActorFunc)EnMm2_Init,
    (ActorFunc)EnMm2_Destroy,
    (ActorFunc)EnMm2_Update,
    (ActorFunc)EnMm2_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm2_0x809A2030/EnMm2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm2_0x809A2030/EnMm2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm2_0x809A2030/func_809A2080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm2_0x809A2030/func_809A20FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm2_0x809A2030/EnMm2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm2_0x809A2030/EnMm2_Draw.asm")
