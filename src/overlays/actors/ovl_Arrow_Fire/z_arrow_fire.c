#include "z_arrow_fire.h"

#define FLAGS 0x02000010

#define THIS ((ArrowFire*)thisx)

void ArrowFire_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowFire_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowFire_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Arrow_Fire_InitVars = {
    ACTOR_ARROW_FIRE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArrowFire),
    (ActorFunc)ArrowFire_Init,
    (ActorFunc)ArrowFire_Destroy,
    (ActorFunc)ArrowFire_Update,
    (ActorFunc)ArrowFire_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/FireArrow_SetUpdateFunc.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/ArrowFire_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/ArrowFire_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/FireArrow_Update1.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/FireArrow_Lerp.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/FireArrow_Update3.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/FireArrow_Update2.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/ArrowFire_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/func_80920948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Arrow_Fire/ArrowFire_Draw.s")
