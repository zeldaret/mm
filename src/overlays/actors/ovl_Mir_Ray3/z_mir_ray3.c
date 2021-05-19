#include "z_mir_ray3.h"

#define FLAGS 0x00000030

#define THIS ((MirRay3*)thisx)

void MirRay3_Init(Actor* thisx, GlobalContext* globalCtx);
void MirRay3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MirRay3_Update(Actor* thisx, GlobalContext* globalCtx);
void MirRay3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Mir_Ray3_InitVars = {
    ACTOR_MIR_RAY3,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay3),
    (ActorFunc)MirRay3_Init,
    (ActorFunc)MirRay3_Destroy,
    (ActorFunc)MirRay3_Update,
    (ActorFunc)MirRay3_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E5F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E7D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E8D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Draw.asm")
