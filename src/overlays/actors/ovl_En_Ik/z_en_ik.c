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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_IK,
    sizeof(EnIk),
    (ActorFunc)EnIk_Init,
    (ActorFunc)EnIk_Destroy,
    (ActorFunc)EnIk_Update,
    (ActorFunc)EnIk_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/EnIk_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/EnIk_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929BEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929C80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929D04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929E2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929F20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_80929FC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A020.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A124.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A188.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A28C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A33C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A5BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A754.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A8D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092A994.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092AA6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092AB14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092AB50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092ABD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092AC4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092ACFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092ADB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092AE14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092AFB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092AFD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092B03C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092B098.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092B1B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092B46C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/EnIk_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092B900.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092B93C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/func_8092BC6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ik_0x80929910/EnIk_Draw.asm")
