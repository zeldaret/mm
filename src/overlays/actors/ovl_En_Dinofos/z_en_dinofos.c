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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_DINOFOS,
    sizeof(EnDinofos),
    (ActorFunc)EnDinofos_Init,
    (ActorFunc)EnDinofos_Destroy,
    (ActorFunc)EnDinofos_Update,
    (ActorFunc)EnDinofos_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089A900.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089A968.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089A9B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089ABF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089AC70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089ACEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089AD70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089AE00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B100.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B320.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B3D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B4A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B580.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B6E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B72C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B7B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B834.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B8B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089B98C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089BAC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089BB60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089BBB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089BD28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C024.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C0DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C164.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C1F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C244.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C2A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C44C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C4F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C56C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C724.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C784.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C7B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C87C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089C938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089CA14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089CA74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089CB10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089CBEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089CF00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089CF70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089CFAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089D018.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089D11C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089D1E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089D2E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089D318.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089D42C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089D60C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089DC4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/func_8089DC84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Draw.asm")
