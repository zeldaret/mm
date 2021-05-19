#include "z_bg_ikninside.h"

#define FLAGS 0x00000010

#define THIS ((BgIkninside*)thisx)

void BgIkninside_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikninside_InitVars = {
    ACTOR_BG_IKNINSIDE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNINSIDE_OBJ,
    sizeof(BgIkninside),
    (ActorFunc)BgIkninside_Init,
    (ActorFunc)BgIkninside_Destroy,
    (ActorFunc)BgIkninside_Update,
    (ActorFunc)BgIkninside_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikninside_0x80C07110/BgIkninside_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikninside_0x80C07110/BgIkninside_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikninside_0x80C07110/func_80C07220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikninside_0x80C07110/func_80C07230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikninside_0x80C07110/func_80C072D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikninside_0x80C07110/BgIkninside_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikninside_0x80C07110/BgIkninside_Draw.asm")
