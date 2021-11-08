/*
 * File: z_en_attack_niw.c
 * Overlay: ovl_En_Attack_Niw
 * Description: Attacking cucco
 */

#include "z_en_attack_niw.h"

#define FLAGS 0x00000010

#define THIS ((EnAttackNiw*)thisx)

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80958634(EnAttackNiw* this, GlobalContext* globalCtx);
void func_80958974(EnAttackNiw* this, GlobalContext* globalCtx);
void func_80958BE4(EnAttackNiw* this, GlobalContext* globalCtx);

#if 0
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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80959120[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 0, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80959120[];

extern UNK_TYPE D_060000E8;

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
