#include "z_en_tubo_trap.h"

#define FLAGS 0x00000000

#define THIS ((EnTuboTrap*)thisx)

void EnTuboTrap_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tubo_Trap_InitVars = {
    ACTOR_EN_TUBO_TRAP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(EnTuboTrap),
    (ActorFunc)EnTuboTrap_Init,
    (ActorFunc)EnTuboTrap_Destroy,
    (ActorFunc)EnTuboTrap_Update,
    (ActorFunc)EnTuboTrap_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/EnTuboTrap_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/EnTuboTrap_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_8093089C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_809308F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_80930B60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_80930DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_80931004.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_80931138.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/func_809311C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/EnTuboTrap_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tubo_Trap_0x809307E0/EnTuboTrap_Draw.asm")
