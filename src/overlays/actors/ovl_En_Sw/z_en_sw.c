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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D8940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D8B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D8D60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D8ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D8FC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D90C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D90F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D91C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D93BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D94D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D99C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9A70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9C18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9E44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9F08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808D9F78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DA024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DA08C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DA350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DA3F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DA578.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DA6FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DA89C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DAA60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DACF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DAEB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DB100.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DB25C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DB2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/EnSw_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/EnSw_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/EnSw_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/func_808DB7F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sw_0x808D8940/EnSw_Draw.asm")
