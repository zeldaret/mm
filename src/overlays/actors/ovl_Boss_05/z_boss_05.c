#include "z_boss_05.h"

#define FLAGS 0x00000005

#define THIS ((Boss05*)thisx)

void Boss05_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss05_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss05_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss05_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_05_InitVars = {
    ACTOR_BOSS_05,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BOSS05,
    sizeof(Boss05),
    (ActorFunc)Boss05_Init,
    (ActorFunc)Boss05_Destroy,
    (ActorFunc)Boss05_Update,
    (ActorFunc)Boss05_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EE4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EE668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EECBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EEDD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EEDE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EF9BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EFAB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809EFE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0014.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F00CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F010C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F01CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F02D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F04C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0590.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F06B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0ABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F0B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1050.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F12A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F135C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F14AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/func_809F1550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_05/Boss05_Draw.s")
