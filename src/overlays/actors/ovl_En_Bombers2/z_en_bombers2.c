#include "z_en_bombers2.h"

#define FLAGS 0x00000009

#define THIS ((EnBombers2*)thisx)

void EnBombers2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombers2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bombers2_InitVars = {
    ACTOR_EN_BOMBERS2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBombers2),
    (ActorFunc)EnBombers2_Init,
    (ActorFunc)EnBombers2_Destroy,
    (ActorFunc)EnBombers2_Update,
    (ActorFunc)EnBombers2_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/EnBombers2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/EnBombers2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C04AAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C04B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C04BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C04D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C04D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C050B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C0520C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/EnBombers2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/func_80C056D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers2/EnBombers2_Draw.s")
