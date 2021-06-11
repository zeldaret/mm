#include "z_bg_spdweb.h"

#define FLAGS 0x00000000

#define THIS ((BgSpdweb*)thisx)

void BgSpdweb_Init(Actor* thisx, GlobalContext* globalCtx);
void BgSpdweb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgSpdweb_Update(Actor* thisx, GlobalContext* globalCtx);
void BgSpdweb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Spdweb_InitVars = {
    ACTOR_BG_SPDWEB,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_SPDWEB,
    sizeof(BgSpdweb),
    (ActorFunc)BgSpdweb_Init,
    (ActorFunc)BgSpdweb_Destroy,
    (ActorFunc)BgSpdweb_Update,
    (ActorFunc)BgSpdweb_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/BgSpdweb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/BgSpdweb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CE068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CE15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CE1D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CE234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CE4C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CE830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CEBC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CEE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/func_809CEEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/BgSpdweb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spdweb/BgSpdweb_Draw.s")
