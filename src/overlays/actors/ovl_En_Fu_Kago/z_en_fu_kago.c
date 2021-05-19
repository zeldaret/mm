#include "z_en_fu_kago.h"

#define FLAGS 0x00000030

#define THIS ((EnFuKago*)thisx)

void EnFuKago_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFuKago_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFuKago_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFuKago_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fu_Kago_InitVars = {
    ACTOR_EN_FU_KAGO,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FU_MATO,
    sizeof(EnFuKago),
    (ActorFunc)EnFuKago_Init,
    (ActorFunc)EnFuKago_Destroy,
    (ActorFunc)EnFuKago_Update,
    (ActorFunc)EnFuKago_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80ACF8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80ACF994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80ACF9A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80ACF9DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80ACF9FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80ACFA78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80ACFDAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80AD0028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80AD0274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80AD0288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/func_80AD0340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Draw.asm")
