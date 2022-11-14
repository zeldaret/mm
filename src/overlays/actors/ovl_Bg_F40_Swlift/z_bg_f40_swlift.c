/*
 * File: z_bg_f40_swlift.c
 * Overlay: ovl_Bg_F40_Swlift
 * Description: Unused Stone Tower vertically-oscillating platform
 */

#include "z_bg_f40_swlift.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgF40Swlift*)thisx)

void BgF40Swlift_Init(Actor* thisx, PlayState* play);
void BgF40Swlift_Destroy(Actor* thisx, PlayState* play);
void BgF40Swlift_Update(Actor* thisx, PlayState* play);
void BgF40Swlift_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Bg_F40_Swlift_InitVars = {
    ACTOR_BG_F40_SWLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_F40_OBJ,
    sizeof(BgF40Swlift),
{BgF40Swlift_Init,
    BgF40Swlift_Destroy,
    BgF40Swlift_Update,
    BgF40Swlift_Draw,
},};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8096F540[] = {
    ICHAIN_F32(uncullZoneScale, 550, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 5000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_8096F540[];

extern UNK_TYPE D_06003B08;
extern UNK_TYPE D_06003E80;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Swlift/BgF40Swlift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Swlift/BgF40Swlift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Swlift/BgF40Swlift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Swlift/BgF40Swlift_Draw.s")
