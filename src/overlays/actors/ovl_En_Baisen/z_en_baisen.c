#include "z_en_baisen.h"

#define FLAGS 0x00000009

#define THIS ((EnBaisen*)thisx)

void EnBaisen_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaisen_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaisen_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBaisen_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Baisen_InitVars = {
    ACTOR_EN_BAISEN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BAI,
    sizeof(EnBaisen),
    (ActorFunc)EnBaisen_Init,
    (ActorFunc)EnBaisen_Destroy,
    (ActorFunc)EnBaisen_Update,
    (ActorFunc)EnBaisen_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/EnBaisen_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/EnBaisen_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE8690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE871C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE87B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE87FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE887C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE895C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE89D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE8AAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/EnBaisen_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/func_80BE8D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baisen/EnBaisen_Draw.s")
