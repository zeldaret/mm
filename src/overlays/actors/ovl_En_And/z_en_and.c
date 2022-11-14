/*
 * File: z_en_and.c
 * Overlay: ovl_En_And
 * Description: Anju in Wedding Dress
 */

#include "z_en_and.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAnd*)thisx)

void EnAnd_Init(Actor* thisx, PlayState* play);
void EnAnd_Destroy(Actor* thisx, PlayState* play);
void EnAnd_Update(Actor* thisx, PlayState* play);
void EnAnd_Draw(Actor* thisx, PlayState* play);

void func_80C18C50(EnAnd* this, PlayState* play);

#if 0
ActorInit En_And_InitVars = {
    ACTOR_EN_AND,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AND,
    sizeof(EnAnd),
{EnAnd_Init,
    EnAnd_Destroy,
    EnAnd_Update,
    EnAnd_Draw,
},};

#endif

extern UNK_TYPE D_0600B380;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/func_80C18B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/func_80C18BD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/func_80C18C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/func_80C18ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_And/EnAnd_Draw.s")
