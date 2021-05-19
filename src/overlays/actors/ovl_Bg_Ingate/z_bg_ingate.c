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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953BEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953EA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953F8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80953F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_809541B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_809542A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_80954340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/func_809543D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/BgIngate_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/BgIngate_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/BgIngate_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ingate_0x80953A90/BgIngate_Draw.asm")
