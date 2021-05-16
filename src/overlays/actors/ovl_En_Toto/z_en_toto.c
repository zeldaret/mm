#include "z_en_toto.h"

#define FLAGS 0x00000009

#define THIS ((EnToto*)thisx)

void EnToto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnToto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnToto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnToto_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Toto_InitVars = {
    ACTOR_EN_TOTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZM,
    sizeof(EnToto),
    (ActorFunc)EnToto_Init,
    (ActorFunc)EnToto_Destroy,
    (ActorFunc)EnToto_Update,
    (ActorFunc)EnToto_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA36C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/EnToto_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/EnToto_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA383C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA397C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA39C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3BFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3DBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3F2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3FB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA3FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA402C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA407C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA40D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA415C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA42BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA43F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA445C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA44A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA44D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA46D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA47E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA49A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4B24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4C0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/func_80BA4CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/EnToto_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Toto/EnToto_Draw.s")
