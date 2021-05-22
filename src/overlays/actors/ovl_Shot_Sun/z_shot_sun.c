#include "z_shot_sun.h"

#define FLAGS 0x00000009

#define THIS ((ShotSun*)thisx)

void ShotSun_Init(Actor* thisx, GlobalContext* globalCtx);
void ShotSun_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ShotSun_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Shot_Sun_InitVars = {
    ACTOR_SHOT_SUN,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ShotSun),
    (ActorFunc)ShotSun_Init,
    (ActorFunc)ShotSun_Destroy,
    (ActorFunc)ShotSun_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Shot_Sun_0x80973640/ShotSun_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Shot_Sun_0x80973640/ShotSun_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Shot_Sun_0x80973640/func_80973740.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Shot_Sun_0x80973640/func_80973804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Shot_Sun_0x80973640/func_809738D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Shot_Sun_0x80973640/func_80973960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Shot_Sun_0x80973640/ShotSun_Update.asm")
