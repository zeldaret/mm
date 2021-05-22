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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/EnBaisen_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/EnBaisen_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE8690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE871C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE87B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE87FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE887C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE895C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE89D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE8AAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/EnBaisen_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/func_80BE8D3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baisen_0x80BE84F0/EnBaisen_Draw.asm")
