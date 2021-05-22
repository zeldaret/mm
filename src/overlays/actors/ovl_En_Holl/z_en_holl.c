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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_808999B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/EnHoll_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/EnHoll_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899ACC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_80899F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A0C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/func_8089A330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/EnHoll_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Holl_0x80899960/EnHoll_Draw.asm")
