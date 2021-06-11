#include "z_en_ru.h"

#define FLAGS 0x00000019

#define THIS ((EnRu*)thisx)

void EnRu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ru_InitVars = {
    ACTOR_EN_RU,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RU2,
    sizeof(EnRu),
    (ActorFunc)EnRu_Init,
    (ActorFunc)EnRu_Destroy,
    (ActorFunc)EnRu_Update,
    (ActorFunc)EnRu_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A389A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38B7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38C70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A38FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/func_80A390F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ru/EnRu_Draw.s")
