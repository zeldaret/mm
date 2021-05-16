#include "z_en_crow.h"

#define FLAGS 0x00005005

#define THIS ((EnCrow*)thisx)

void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Crow_InitVars = {
    ACTOR_EN_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnCrow),
    (ActorFunc)EnCrow_Init,
    (ActorFunc)EnCrow_Destroy,
    (ActorFunc)EnCrow_Update,
    (ActorFunc)EnCrow_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099AC58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099AC8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B6AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B6C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099B9E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099BAB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099BE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/func_8099BF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Crow/EnCrow_Draw.s")
