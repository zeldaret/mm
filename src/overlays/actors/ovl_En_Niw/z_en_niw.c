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
    (ActorFunc)EnNiw_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/EnNiw_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/EnNiw_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80891320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808916B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808917F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80891974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808919E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80891D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80891F60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808920A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80892248.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80892274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808922D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80892390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80892414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808924B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808925F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_8089262C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/EnNiw_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80892E70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/EnNiw_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_80893008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808930FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Niw/func_808932B0.s")
