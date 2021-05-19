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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EE4E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EE668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/Boss05_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/Boss05_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EECBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EEDD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EEDE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EF9BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EFAB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809EFE50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F00CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F010C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F01CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F02D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F04C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F06B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0A0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0ABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F0B0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/Boss05_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F1050.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F1170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F1284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F12A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F135C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F1404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F1430.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F1464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F14AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/func_809F1550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_05_0x809EE4E0/Boss05_Draw.asm")
