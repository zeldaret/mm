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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_FU_MATO,
    sizeof(EnFuKago),
    (ActorFunc)EnFuKago_Init,
    (ActorFunc)EnFuKago_Destroy,
    (ActorFunc)EnFuKago_Update,
    (ActorFunc)EnFuKago_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80ACF8B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80ACF994.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80ACF9A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80ACF9DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80ACF9FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80ACFA78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80ACFDAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80AD0028.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80AD0274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80AD0288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/func_80AD0340.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fu_Kago_0x80ACF780/EnFuKago_Draw.asm")
