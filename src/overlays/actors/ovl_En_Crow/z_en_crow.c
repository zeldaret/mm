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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnCrow),
    (ActorFunc)EnCrow_Init,
    (ActorFunc)EnCrow_Destroy,
    (ActorFunc)EnCrow_Update,
    (ActorFunc)EnCrow_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/EnCrow_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/EnCrow_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099AC58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099AC8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B098.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B0CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B318.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B584.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B6AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B6C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B838.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B8EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099B9E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099BAB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/EnCrow_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099BE48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/func_8099BF20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Crow_0x8099AB30/EnCrow_Draw.asm")
