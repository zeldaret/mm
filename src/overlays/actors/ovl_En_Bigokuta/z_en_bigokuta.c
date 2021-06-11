#include "z_en_bigokuta.h"

#define FLAGS 0x00000005

#define THIS ((EnBigokuta*)thisx)

void EnBigokuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bigokuta_InitVars = {
    ACTOR_EN_BIGOKUTA,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGOKUTA,
    sizeof(EnBigokuta),
    (ActorFunc)EnBigokuta_Init,
    (ActorFunc)EnBigokuta_Destroy,
    (ActorFunc)EnBigokuta_Update,
    (ActorFunc)EnBigokuta_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC28B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC299C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2C30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC30EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC31EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC33A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC33C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC34A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC35E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC39A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC4204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Draw.s")
