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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnScopenuts),
    (ActorFunc)EnScopenuts_Init,
    (ActorFunc)EnScopenuts_Destroy,
    (ActorFunc)EnScopenuts_Update,
    (ActorFunc)EnScopenuts_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCABF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCAC40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCAD64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCAE78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCAF0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCAFA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB078.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB1C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB4DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB52C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB6D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB90C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCB980.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCBA00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCBC60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCBD28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCBF0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCBFFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCC288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCC2AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCC448.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCC828.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCC9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/func_80BCC9E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Scopenuts_0x80BCABF0/EnScopenuts_Draw.asm")
