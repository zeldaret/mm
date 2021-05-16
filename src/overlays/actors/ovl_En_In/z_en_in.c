#include "z_en_in.h"

#define FLAGS 0x00000019

#define THIS ((EnIn*)thisx)

void EnIn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_In_InitVars = {
    ACTOR_EN_IN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_IN,
    sizeof(EnIn),
    (ActorFunc)EnIn_Init,
    (ActorFunc)EnIn_Destroy,
    (ActorFunc)EnIn_Update,
    (ActorFunc)EnIn_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F30B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F322C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F32A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F33B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F35AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F35D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F374C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F38F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F395C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F39DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3CD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F3DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F4054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F4108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F4150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F4270.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F43E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F4414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F5674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F5728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F5994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F5A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F5A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F5B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F5C98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/EnIn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/EnIn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/EnIn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F6334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F64A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/func_808F67F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_In/EnIn_Draw.s")
