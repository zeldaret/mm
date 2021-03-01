#include "z_en_niw.h"

#define FLAGS 0x00800010

#define THIS ((EnNiw*)thisx)

void EnNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Niw_InitVars = {
    ACTOR_EN_NIW,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnNiw),
    (ActorFunc)EnNiw_Init,
    (ActorFunc)EnNiw_Destroy,
    (ActorFunc)EnNiw_Update,
    (ActorFunc)EnNiw_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891320.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808916B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808917F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891974.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808919E8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891D78.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80891F60.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808920A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892248.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892274.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808922D0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892390.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892414.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808924B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808925F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_8089262C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80892E70.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/EnNiw_Draw.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_80893008.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808930FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Niw_0x80891060/func_808932B0.asm")
