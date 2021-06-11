#include "z_bg_ingate.h"

#define FLAGS 0x00000030

#define THIS ((BgIngate*)thisx)

void BgIngate_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIngate_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIngate_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIngate_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ingate_InitVars = {
    ACTOR_BG_INGATE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_SICHITAI_OBJ,
    sizeof(BgIngate),
    (ActorFunc)BgIngate_Init,
    (ActorFunc)BgIngate_Destroy,
    (ActorFunc)BgIngate_Update,
    (ActorFunc)BgIngate_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953F8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80953F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_809541B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_809542A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_80954340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/func_809543D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/BgIngate_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/BgIngate_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/BgIngate_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ingate/BgIngate_Draw.s")
