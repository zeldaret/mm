#include "z_en_zob.h"

#define FLAGS 0x00000009

#define THIS ((EnZob*)thisx)

void EnZob_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZob_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zob_InitVars = {
    ACTOR_EN_ZOB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOB,
    sizeof(EnZob),
    (ActorFunc)EnZob_Init,
    (ActorFunc)EnZob_Destroy,
    (ActorFunc)EnZob_Update,
    (ActorFunc)EnZob_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/EnZob_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/EnZob_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9F7E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9F86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FA3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FD24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FDDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80B9FF80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA005C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA00BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA06BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA08E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA09E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0AD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0CF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/EnZob_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/func_80BA0FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zob/EnZob_Draw.s")
