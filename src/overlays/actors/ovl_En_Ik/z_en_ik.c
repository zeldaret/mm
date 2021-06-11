#include "z_en_ik.h"

#define FLAGS 0x00000405

#define THIS ((EnIk*)thisx)

void EnIk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ik_InitVars = {
    ACTOR_EN_IK,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_IK,
    sizeof(EnIk),
    (ActorFunc)EnIk_Init,
    (ActorFunc)EnIk_Destroy,
    (ActorFunc)EnIk_Update,
    (ActorFunc)EnIk_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A5BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AA6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AB50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092ABD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092ACFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092ADB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AE14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B03C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B46C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B93C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092BC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Draw.s")
