/*
 * File: z_bg_tobira01.c
 * Overlay: ovl_Bg_Tobira01
 * Description: Gate to Goron Shrine
 */

#include "z_bg_tobira01.h"
#include "objects/object_spot11_obj/object_spot11_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgTobira01*)thisx)

void BgTobira01_Init(Actor* thisx, PlayState* play);
void BgTobira01_Destroy(Actor* thisx, PlayState* play);
void BgTobira01_Update(Actor* thisx, PlayState* play);
void BgTobira01_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Bg_Tobira01_InitVars = {
    /**/ ACTOR_BG_TOBIRA01,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_SPOT11_OBJ,
    /**/ sizeof(BgTobira01),
    /**/ BgTobira01_Init,
    /**/ BgTobira01_Destroy,
    /**/ BgTobira01_Update,
    /**/ BgTobira01_Draw,
};
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Tobira01/func_80B12430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Tobira01/BgTobira01_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Tobira01/BgTobira01_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Tobira01/BgTobira01_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Tobira01/BgTobira01_Draw.s")
