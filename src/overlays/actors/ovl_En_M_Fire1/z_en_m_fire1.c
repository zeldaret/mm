#include "z_en_m_fire1.h"

#define FLAGS 0x00000000

#define THIS ((EnMFire1*)thisx)

void EnMFire1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMFire1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMFire1_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_M_Fire1_InitVars = {
    ACTOR_EN_M_FIRE1,
    ACTORCAT_MISC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMFire1),
    (ActorFunc)EnMFire1_Init,
    (ActorFunc)EnMFire1_Destroy,
    (ActorFunc)EnMFire1_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Fire1_0x808B5230/EnMFire1_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Fire1_0x808B5230/EnMFire1_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Fire1_0x808B5230/EnMFire1_Update.asm")
