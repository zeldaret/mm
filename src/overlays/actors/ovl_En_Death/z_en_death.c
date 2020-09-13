#include "z_en_death.h"

#define FLAGS 0x00001035

#define THIS ((EnDeath*)thisx)

void EnDeath_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDeath_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDeath_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDeath_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Death_InitVars = {
    ACTOR_EN_DEATH,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_DEATH,
    sizeof(EnDeath),
    (ActorFunc)EnDeath_Init,
    (ActorFunc)EnDeath_Destroy,
    (ActorFunc)EnDeath_Update,
    (ActorFunc)EnDeath_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/EnDeath_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/EnDeath_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5310.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5394.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5428.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C54F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C566C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C571C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C589C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C597C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5AB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5C0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5CB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5D6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C5F58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C645C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C64DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C66A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C67C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C682C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C68B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C692C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6A08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6AB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6C5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6CDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6D40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C6F6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C70D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C72AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C74A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C74F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7800.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7888.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7A30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7AAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7AEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7B88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7C88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7CFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7D34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7DB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7DCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7E24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C7EDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/EnDeath_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C84A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C8690.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C882C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C8D18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C9160.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C9220.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/func_808C9340.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Death_0x808C4F80/EnDeath_Draw.asm")
