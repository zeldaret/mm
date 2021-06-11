#include "z_en_scopenuts.h"

#define FLAGS 0x00000039

#define THIS ((EnScopenuts*)thisx)

void EnScopenuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopenuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Scopenuts_InitVars = {
    ACTOR_EN_SCOPENUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnScopenuts),
    (ActorFunc)EnScopenuts_Init,
    (ActorFunc)EnScopenuts_Destroy,
    (ActorFunc)EnScopenuts_Update,
    (ActorFunc)EnScopenuts_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCABF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCAC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCAD64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCAE78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCAF0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCAFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB4DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB52C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB90C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCB980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCBA00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCBC60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCBD28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCBF0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCBFFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCC288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCC2AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCC448.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/EnScopenuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/EnScopenuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/EnScopenuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCC828.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCC9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/func_80BCC9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Scopenuts/EnScopenuts_Draw.s")
