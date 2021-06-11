#include "z_bg_kin2_bombwall.h"

#define FLAGS 0x10000010

#define THIS ((BgKin2Bombwall*)thisx)

void BgKin2Bombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Kin2_Bombwall_InitVars = {
    ACTOR_BG_KIN2_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Bombwall),
    (ActorFunc)BgKin2Bombwall_Init,
    (ActorFunc)BgKin2Bombwall_Destroy,
    (ActorFunc)BgKin2Bombwall_Update,
    (ActorFunc)BgKin2Bombwall_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E4B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E4CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E5F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/func_80B6E614.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Bombwall/BgKin2Bombwall_Draw.s")
