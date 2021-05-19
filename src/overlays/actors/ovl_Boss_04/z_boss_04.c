#include "z_boss_04.h"

#define FLAGS 0x00000035

#define THIS ((Boss04*)thisx)

void Boss04_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_04_InitVars = {
    ACTOR_BOSS_04,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(Boss04),
    (ActorFunc)Boss04_Init,
    (ActorFunc)Boss04_Destroy,
    (ActorFunc)Boss04_Update,
    (ActorFunc)Boss04_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EC040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EC544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EC568.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECD00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECD18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECEF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECF58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED224.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED2A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED45C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED50C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EDCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EDECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Draw.asm")
