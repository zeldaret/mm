#include "z_en_fu_mato.h"

#define FLAGS 0x00000030

#define THIS ((EnFuMato*)thisx)

void EnFuMato_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFuMato_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFuMato_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFuMato_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fu_Mato_InitVars = {
    ACTOR_EN_FU_MATO,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FU_MATO,
    sizeof(EnFuMato),
    (ActorFunc)EnFuMato_Init,
    (ActorFunc)EnFuMato_Destroy,
    (ActorFunc)EnFuMato_Update,
    (ActorFunc)EnFuMato_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/EnFuMato_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/EnFuMato_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACE4B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACE4C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACE508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACE51C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACE680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACE718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACE850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACEB2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACECFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACEFC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACEFD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACF04C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/EnFuMato_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACF1F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/func_80ACF3F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fu_Mato/EnFuMato_Draw.s")
