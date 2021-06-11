#include "z_bg_astr_bombwall.h"

#define FLAGS 0x00000000

#define THIS ((BgAstrBombwall*)thisx)

void BgAstrBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgAstrBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Astr_Bombwall_InitVars = {
    ACTOR_BG_ASTR_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ASTR_OBJ,
    sizeof(BgAstrBombwall),
    (ActorFunc)BgAstrBombwall_Init,
    (ActorFunc)BgAstrBombwall_Destroy,
    (ActorFunc)BgAstrBombwall_Update,
    (ActorFunc)BgAstrBombwall_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C09ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/BgAstrBombwall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/BgAstrBombwall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C0A120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C0A378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C0A38C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C0A400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C0A418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C0A458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/func_80C0A4BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/BgAstrBombwall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall/BgAstrBombwall_Draw.s")
