#include "z_en_river_sound.h"

#define FLAGS 0x00000030

#define THIS ((EnRiverSound*)thisx)

void EnRiverSound_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRiverSound_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRiverSound_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_River_Sound_InitVars = {
    ACTOR_EN_RIVER_SOUND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnRiverSound),
    (ActorFunc)EnRiverSound_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)EnRiverSound_Update,
    (ActorFunc)EnRiverSound_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_River_Sound_0x808A7E30/EnRiverSound_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_River_Sound_0x808A7E30/EnRiverSound_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_River_Sound_0x808A7E30/EnRiverSound_Draw.asm")
