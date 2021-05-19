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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C09ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A38C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/func_80C0A4BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Astr_Bombwall_0x80C09ED0/BgAstrBombwall_Draw.asm")
