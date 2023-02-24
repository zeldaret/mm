/*
 * File: z_en_dnh.c
 * Overlay: ovl_En_Dnh
 * Description: Koume in boat house
 */

#include "z_en_dnh.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDnh*)thisx)

void EnDnh_Init(Actor* thisx, PlayState* play);
void EnDnh_Destroy(Actor* thisx, PlayState* play);
void EnDnh_Update(Actor* thisx, PlayState* play);
void EnDnh_Draw(Actor* thisx, PlayState* play);

void func_80A50F38(EnDnh* this, PlayState* play);
void func_80A50F9C(EnDnh* this, PlayState* play);

#if 0
ActorInit En_Dnh_InitVars = {
    /**/ ACTOR_EN_DNH,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_TRO,
    /**/ sizeof(EnDnh),
    /**/ EnDnh_Init,
    /**/ EnDnh_Destroy,
    /**/ EnDnh_Update,
    /**/ EnDnh_Draw,
};

#endif

extern UNK_TYPE D_06002950;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50D40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50DF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50EC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50F38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A51168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Draw.s")
