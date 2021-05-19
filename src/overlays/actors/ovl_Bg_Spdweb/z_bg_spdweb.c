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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE068.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE1D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE4C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CE830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CEBC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CEE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/func_809CEEAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spdweb_0x809CDEC0/BgSpdweb_Draw.asm")
