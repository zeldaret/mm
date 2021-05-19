#include "z_mir_ray.h"

#define FLAGS 0x00000030

#define THIS ((MirRay*)thisx)

void MirRay_Init(Actor* thisx, GlobalContext* globalCtx);
void MirRay_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MirRay_Update(Actor* thisx, GlobalContext* globalCtx);
void MirRay_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Mir_Ray_InitVars = {
    ACTOR_MIR_RAY,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay),
    (ActorFunc)MirRay_Init,
    (ActorFunc)MirRay_Destroy,
    (ActorFunc)MirRay_Update,
    (ActorFunc)MirRay_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/func_808E2600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/func_808E26C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/MirRay_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/MirRay_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/MirRay_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/func_808E2C68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/func_808E2E1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/func_808E2FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/func_808E30FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/MirRay_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray_0x808E2600/func_808E3984.asm")
