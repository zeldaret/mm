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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay3),
    (ActorFunc)MirRay3_Init,
    (ActorFunc)MirRay3_Destroy,
    (ActorFunc)MirRay3_Update,
    (ActorFunc)MirRay3_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E544.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E5F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E7D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/func_80B9E8D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray3_0x80B9E2C0/MirRay3_Draw.asm")
