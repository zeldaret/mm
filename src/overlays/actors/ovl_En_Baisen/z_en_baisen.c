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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BAI,
    sizeof(EnBaisen),
    (ActorFunc)EnBaisen_Init,
    (ActorFunc)EnBaisen_Destroy,
    (ActorFunc)EnBaisen_Update,
    (ActorFunc)EnBaisen_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/EnBaisen_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/EnBaisen_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE8690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE871C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE87B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE87FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE887C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE895C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE89D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE8AAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/EnBaisen_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/func_80BE8D3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Baisen_0x80BE84F0/EnBaisen_Draw.asm")
