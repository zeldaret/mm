/*
 * File: z_en_encount3.c
 * Overlay: ovl_En_Encount3
 * Description: Garo spawner
 */

#include "z_en_encount3.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnEncount3*)thisx)

void EnEncount3_Init(Actor* thisx, PlayState* play);
void EnEncount3_Destroy(Actor* thisx, PlayState* play);
void EnEncount3_Update(Actor* thisx, PlayState* play);
void EnEncount3_Draw(Actor* thisx, PlayState* play);

void func_809AD084(EnEncount3* this, PlayState* play);
void func_809AD194(EnEncount3* this, PlayState* play);
void func_809AD1EC(EnEncount3* this, PlayState* play);

#if 0
ActorInit En_Encount3_InitVars = {
    /**/ ACTOR_EN_ENCOUNT3,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_BIG_FWALL,
    /**/ sizeof(EnEncount3),
    /**/ EnEncount3_Init,
    /**/ EnEncount3_Destroy,
    /**/ EnEncount3_Update,
    /**/ EnEncount3_Draw,
};

#endif

extern UNK_TYPE D_060009A0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/func_809AD1EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount3/EnEncount3_Draw.s")
