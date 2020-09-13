#include "z_en_sda.h"

#define FLAGS 0x00000030

#define THIS ((EnSda*)thisx)

void EnSda_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSda_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSda_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSda_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sda_InitVars = {
    ACTOR_EN_SDA,
    ACTORTYPE_BOSS,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSda),
    (ActorFunc)EnSda_Init,
    (ActorFunc)EnSda_Destroy,
    (ActorFunc)EnSda_Update,
    (ActorFunc)EnSda_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Sda_0x809468D0/EnSda_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sda_0x809468D0/EnSda_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sda_0x809468D0/EnSda_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sda_0x809468D0/EnSda_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sda_0x809468D0/func_809469C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sda_0x809468D0/func_8094702C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sda_0x809468D0/func_80947668.asm")
