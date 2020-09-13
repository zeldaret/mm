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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(EnButte),
    (ActorFunc)EnButte_Init,
    (ActorFunc)EnButte_Destroy,
    (ActorFunc)EnButte_Update,
    (ActorFunc)EnButte_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C0A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C124.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C140.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/EnButte_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/EnButte_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C5EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C6B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C748.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091C794.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091CB68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091CBB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091CF64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091CFB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091D070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/func_8091D090.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/EnButte_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Butte_0x8091C0A0/EnButte_Draw.asm")
