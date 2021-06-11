#include "z_en_holl.h"

#define FLAGS 0x00000010

#define THIS ((EnHoll*)thisx)

void EnHoll_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHoll_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Holl_InitVars = {
    ACTOR_EN_HOLL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHoll),
    (ActorFunc)EnHoll_Init,
    (ActorFunc)EnHoll_Destroy,
    (ActorFunc)EnHoll_Update,
    (ActorFunc)EnHoll_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_80899960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_808999B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/EnHoll_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/EnHoll_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_80899ACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_80899B88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_80899F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_8089A0C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_8089A238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/func_8089A330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/EnHoll_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Holl/EnHoll_Draw.s")
