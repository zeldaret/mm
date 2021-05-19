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
    (ActorFunc)EnCrow_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099AC58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099AC8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B6AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B8EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B9E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099BAB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099BE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099BF20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Draw.asm")
