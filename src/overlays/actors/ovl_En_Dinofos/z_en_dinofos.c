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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089A900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089A968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089A9B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089ABF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089AC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089ACEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089AD70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089AE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B100.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B320.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B3D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B6E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B72C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B7B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B8B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B98C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BAC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BB60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BBB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BD28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C0DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C164.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C1F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C2A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C44C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C4F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C56C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C7B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C87C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CA74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CBEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CF00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CF70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D11C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D1E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D42C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D60C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089DC4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089DC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Draw.asm")
