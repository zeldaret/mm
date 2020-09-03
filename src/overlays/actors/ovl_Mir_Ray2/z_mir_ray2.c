#include "z_mir_ray2.h"

#define FLAGS 0x00000030

#define THIS ((MirRay2*)thisx)

void MirRay2_Init(Actor* thisx, GlobalContext* globalCtx);
void MirRay2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MirRay2_Update(Actor* thisx, GlobalContext* globalCtx);
void MirRay2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Mir_Ray2_InitVars = {
    ACTOR_MIR_RAY2,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay2),
    (ActorFunc)MirRay2_Init,
    (ActorFunc)MirRay2_Destroy,
    (ActorFunc)MirRay2_Update,
    (ActorFunc)MirRay2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray2_0x80AF3F70/func_80AF3F70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray2_0x80AF3F70/func_80AF3FE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray2_0x80AF3F70/MirRay2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray2_0x80AF3F70/MirRay2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray2_0x80AF3F70/MirRay2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Mir_Ray2_0x80AF3F70/MirRay2_Draw.asm")
