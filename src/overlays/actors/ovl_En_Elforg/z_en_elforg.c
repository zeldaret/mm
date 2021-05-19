#include "z_en_elforg.h"

#define FLAGS 0x00000010

#define THIS ((EnElforg*)thisx)

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Elforg_InitVars = {
    ACTOR_EN_ELFORG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElforg),
    (ActorFunc)EnElforg_Init,
    (ActorFunc)EnElforg_Destroy,
    (ActorFunc)EnElforg_Update,
    (ActorFunc)EnElforg_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACC470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/EnElforg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/EnElforg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACC7E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACC8D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACC934.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACC994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACCAC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACCBB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACCBD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACCC98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACCE4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACCEB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD164.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD1B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD2E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD59C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD6A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD6EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/EnElforg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/func_80ACD878.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Elforg_0x80ACC470/EnElforg_Draw.asm")
