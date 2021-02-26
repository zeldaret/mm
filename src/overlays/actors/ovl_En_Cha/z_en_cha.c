#include "z_en_cha.h"

#define FLAGS 0x00000000

#define THIS ((EnCha*)thisx)

void EnCha_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCha_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCha_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCha_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Cha_InitVars = {
    ACTOR_EN_CHA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_CHA,
    sizeof(EnCha),
    (ActorFunc)EnCha_Init,
    (ActorFunc)EnCha_Destroy,
    (ActorFunc)EnCha_Update,
    (ActorFunc)EnCha_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Cha_0x80BEB520/EnCha_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Cha_0x80BEB520/EnCha_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Cha_0x80BEB520/func_80BEB5DC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Cha_0x80BEB520/func_80BEB654.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Cha_0x80BEB520/EnCha_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Cha_0x80BEB520/EnCha_Draw.asm")
