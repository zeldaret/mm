#include "z_en_bba_01.h"

#define FLAGS 0x00000019

#define THIS ((EnBba01*)thisx)

void EnBba01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bba_01_InitVars = {
    ACTOR_EN_BBA_01,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBba01),
    (ActorFunc)EnBba01_Init,
    (ActorFunc)EnBba01_Destroy,
    (ActorFunc)EnBba01_Update,
    (ActorFunc)EnBba01_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC1D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC270.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC2F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC370.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC3A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC3CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/EnBba01_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/EnBba01_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/EnBba01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC6F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CC984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/func_809CCA5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bba_01_0x809CC060/EnBba01_Draw.asm")
