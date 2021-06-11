#include "z_en_attack_niw.h"

#define FLAGS 0x00000010

#define THIS ((EnAttackNiw*)thisx)

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Attack_Niw_InitVars = {
    ACTOR_EN_ATTACK_NIW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnAttackNiw),
    (ActorFunc)EnAttackNiw_Init,
    (ActorFunc)EnAttackNiw_Destroy,
    (ActorFunc)EnAttackNiw_Update,
    (ActorFunc)EnAttackNiw_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/EnAttackNiw_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/EnAttackNiw_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/func_80958228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/func_809585B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/func_80958634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/func_80958974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/func_80958BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/EnAttackNiw_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/func_80958F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Attack_Niw/EnAttackNiw_Draw.s")
