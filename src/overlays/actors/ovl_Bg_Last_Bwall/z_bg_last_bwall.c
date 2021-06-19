#include "z_bg_last_bwall.h"

#define FLAGS 0x00000000

#define THIS ((BgLastBwall*)thisx)

void BgLastBwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLastBwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLastBwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgLastBwall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Last_Bwall_InitVars = {
    ACTOR_BG_LAST_BWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LAST_OBJ,
    sizeof(BgLastBwall),
    (ActorFunc)BgLastBwall_Init,
    (ActorFunc)BgLastBwall_Destroy,
    (ActorFunc)BgLastBwall_Update,
    (ActorFunc)BgLastBwall_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C18240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C184EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C187E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C187F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C1886C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C18884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C188C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/func_80C18928.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Last_Bwall_0x80C18240/BgLastBwall_Draw.asm")
