#include "z_en_butte.h"

#define FLAGS 0x00000000

#define THIS ((EnButte*)thisx)

void EnButte_Init(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Update(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Butte_InitVars = {
    ACTOR_EN_BUTTE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(EnButte),
    (ActorFunc)EnButte_Init,
    (ActorFunc)EnButte_Destroy,
    (ActorFunc)EnButte_Update,
    (ActorFunc)EnButte_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C0A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C6B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CF64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091D070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091D090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Draw.s")
