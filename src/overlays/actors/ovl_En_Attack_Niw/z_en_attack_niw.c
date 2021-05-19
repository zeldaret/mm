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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/EnAttackNiw_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/EnAttackNiw_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/func_80958228.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/func_809585B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/func_80958634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/func_80958974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/func_80958BE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/EnAttackNiw_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/func_80958F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Attack_Niw_0x809580C0/EnAttackNiw_Draw.asm")
