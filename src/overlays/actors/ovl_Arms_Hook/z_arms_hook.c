#include "z_arms_hook.h"

#define FLAGS 0x00000030

#define THIS ((ArmsHook*)thisx)

void ArmsHook_Init(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Update(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Arms_Hook_InitVars = {
    ACTOR_ARMS_HOOK,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArmsHook),
    (ActorFunc)ArmsHook_Init,
    (ActorFunc)ArmsHook_Destroy,
    (ActorFunc)ArmsHook_Update,
    (ActorFunc)ArmsHook_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C1030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/ArmsHook_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/ArmsHook_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C10F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C1154.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C1168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C1198.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C11C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C125C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C12A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/ArmsHook_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/ArmsHook_Draw.asm")
