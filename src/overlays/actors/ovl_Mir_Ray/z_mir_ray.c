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
    (ActorFunc)MirRay_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E26C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E30FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E3984.s")
