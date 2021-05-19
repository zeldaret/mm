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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCABF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAD64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAE78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAF0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCAFA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB1C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB4DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB52C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB90C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCB980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBA00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBC60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBD28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBF0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCBFFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC2AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC448.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/func_80BCC9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Draw.asm")
