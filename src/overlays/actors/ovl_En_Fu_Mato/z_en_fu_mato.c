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
    (ActorFunc)EnFuMato_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/EnFuMato_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/EnFuMato_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACE4B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACE4C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACE508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACE51C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACE680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACE718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACE850.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACEB2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACECFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACEFC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACEFD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACF04C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/EnFuMato_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACF1F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/func_80ACF3F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fu_Mato_0x80ACE330/EnFuMato_Draw.asm")
