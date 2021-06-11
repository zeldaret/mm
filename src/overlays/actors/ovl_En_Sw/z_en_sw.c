#include "z_en_sw.h"

#define FLAGS 0x00000005

#define THIS ((EnSw*)thisx)

void EnSw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sw_InitVars = {
    ACTOR_EN_SW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSw),
    (ActorFunc)EnSw_Init,
    (ActorFunc)EnSw_Destroy,
    (ActorFunc)EnSw_Update,
    (ActorFunc)EnSw_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D90C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D90F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D91C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D93BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D94D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D99C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9A70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA08C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA3F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA6FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA89C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DAA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DACF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DAEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Draw.s")
