#include "z_en_nutsball.h"

#define FLAGS 0x00000010

#define THIS ((EnNutsball*)thisx)

void EnNutsball_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNutsball_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNutsball_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNutsball_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Nutsball_InitVars = {
    ACTOR_EN_NUTSBALL,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnNutsball),
    (ActorFunc)EnNutsball_Init,
    (ActorFunc)EnNutsball_Destroy,
    (ActorFunc)EnNutsball_Update,
    (ActorFunc)EnNutsball_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nutsball_0x80985C40/EnNutsball_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nutsball_0x80985C40/EnNutsball_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nutsball_0x80985C40/func_80985D3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nutsball_0x80985C40/EnNutsball_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Nutsball_0x80985C40/EnNutsball_Draw.asm")
