/*
 * File: z_en_river_sound.c
 * Overlay: ovl_En_River_Sound
 * Description:
 */

#include "z_en_river_sound.h"

#define FLAGS 0x00000030

#define THIS ((EnRiverSound*)thisx)

void EnRiverSound_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRiverSound_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRiverSound_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_River_Sound/EnRiverSound_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_River_Sound/EnRiverSound_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_River_Sound/EnRiverSound_Draw.s")
