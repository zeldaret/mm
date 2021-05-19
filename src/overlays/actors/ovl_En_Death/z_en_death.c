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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C54F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C566C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C571C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C589C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C597C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5C0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5F58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C645C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C64DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6620.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C66A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C67C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C682C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C68B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C692C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6C5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C70D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C72AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C74A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C74F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7A30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7AAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7AEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7CFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7DB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7DCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7EDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C84A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C8690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C882C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C8D18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C9160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C9220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C9340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Draw.asm")
