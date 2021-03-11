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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F30B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F322C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F32A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F33B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F35AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F35D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F374C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F38F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F395C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F39DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3AD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3BD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3C40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3CD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F3DD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F4054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F4108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F4150.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F4270.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F43E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F4414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F5674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F5728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F5994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F5A34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F5A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F5B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F5C98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/EnIn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/EnIn_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/EnIn_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F6334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F64A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/func_808F67F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_In_0x808F30B0/EnIn_Draw.asm")
