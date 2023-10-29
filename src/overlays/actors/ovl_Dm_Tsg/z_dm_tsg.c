/*
 * File: z_dm_tsg.c
 * Overlay: ovl_Dm_Tsg
 * Description: Handles all the masks scrolling by as Link falls in the intro
 */

#include "z_dm_tsg.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmTsg*)thisx)

void DmTsg_Init(Actor* thisx, PlayState* play);
void DmTsg_Destroy(Actor* thisx, PlayState* play);
void DmTsg_Update(Actor* thisx, PlayState* play);
void DmTsg_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Dm_Tsg_InitVars = {
    /**/ ACTOR_DM_TSG,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_OPEN_OBJ,
    /**/ sizeof(DmTsg),
    /**/ DmTsg_Init,
    /**/ DmTsg_Destroy,
    /**/ DmTsg_Update,
    /**/ DmTsg_Draw,
};

#endif

extern UNK_TYPE D_06011458;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tsg/DmTsg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tsg/DmTsg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tsg/DmTsg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Tsg/DmTsg_Draw.s")
