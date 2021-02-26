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

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA36C0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/EnToto_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/EnToto_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA383C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3930.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA397C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA39C8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3BFC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3C88.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3CC4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3D38.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3DBC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3EC0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3ED4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3EE8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3F2C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3FB0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA3FCC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA402C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA407C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA40D4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4128.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA415C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4204.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA42BC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA43F4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA445C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA44A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA44D4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4530.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA46D8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4740.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA47E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA49A4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4A00.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4B24.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4C0C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4C44.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/func_80BA4CB4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/EnToto_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Toto_0x80BA36C0/EnToto_Draw.asm")
