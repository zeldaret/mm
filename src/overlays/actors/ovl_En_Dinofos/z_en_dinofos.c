#include "z_en_dinofos.h"

#define FLAGS 0x00000435

#define THIS ((EnDinofos*)thisx)

void EnDinofos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dinofos_InitVars = {
    ACTOR_EN_DINOFOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DINOFOS,
    sizeof(EnDinofos),
    (ActorFunc)EnDinofos_Init,
    (ActorFunc)EnDinofos_Destroy,
    (ActorFunc)EnDinofos_Update,
    (ActorFunc)EnDinofos_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/EnDinofos_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/EnDinofos_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089A900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089A968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089A9B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089ABF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089AC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089ACEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089AD70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089AE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B3D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B6E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B72C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B7B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B8B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089B98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089BAC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089BB60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089BBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089BD28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C0DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C1F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C2A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C44C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C4F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C56C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C87C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089C938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089CA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089CA74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089CB10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089CBEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089CF00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089CF70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089CFAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089D018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089D11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089D1E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089D2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089D318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089D42C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089D60C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/EnDinofos_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089DC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/func_8089DC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dinofos/EnDinofos_Draw.s")
