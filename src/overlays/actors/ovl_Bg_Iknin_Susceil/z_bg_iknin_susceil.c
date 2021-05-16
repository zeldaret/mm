#include "z_bg_iknin_susceil.h"

#define FLAGS 0x00000030

#define THIS ((BgIkninSusceil*)thisx)

void BgIkninSusceil_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkninSusceil_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkninSusceil_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkninSusceil_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Iknin_Susceil_InitVars = {
    ACTOR_BG_IKNIN_SUSCEIL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNINSIDE_OBJ,
    sizeof(BgIkninSusceil),
    (ActorFunc)BgIkninSusceil_Init,
    (ActorFunc)BgIkninSusceil_Destroy,
    (ActorFunc)BgIkninSusceil_Update,
    (ActorFunc)BgIkninSusceil_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0A740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0A804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0A838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0A86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0A95C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/BgIkninSusceil_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/BgIkninSusceil_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AB88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0ABA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AC74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AC90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0ACD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0ACE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AD44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AD64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/func_80C0AE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/BgIkninSusceil_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknin_Susceil/BgIkninSusceil_Draw.s")
