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
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEATH,
    sizeof(EnDeath),
    (ActorFunc)EnDeath_Init,
    (ActorFunc)EnDeath_Destroy,
    (ActorFunc)EnDeath_Update,
    (ActorFunc)EnDeath_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/EnDeath_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/EnDeath_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C54F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C566C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C571C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C589C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C597C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5C0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C5F58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C645C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C64DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C66A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C67C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C682C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C68B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C692C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6C5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C6F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C70D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C72AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C74A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C74F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7AAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7AEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7D34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7EDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/EnDeath_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C84A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C8690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C882C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C8D18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C9160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C9220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C9340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/EnDeath_Draw.s")
