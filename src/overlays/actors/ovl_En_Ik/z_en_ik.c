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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/EnIk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/EnIk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929B6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929BEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929C80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929F20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_80929FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A28C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A33C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A5BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A8D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092A994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092AA6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092AB14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092AB50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092ABD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092AC4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092ACFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092ADB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092AE14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092AFB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092AFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092B03C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092B098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092B1B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092B46C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/EnIk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092B900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092B93C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/func_8092BC6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ik_0x80929910/EnIk_Draw.asm")
