/*
 * File: z_door_spiral.c
 * Overlay: ovl_Door_Spiral
 * Description: Staircase
 */

#include "z_door_spiral.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_hakugin_obj/object_hakugin_obj.h"
#include "objects/object_ikana_obj/object_ikana_obj.h"
#include "objects/object_ikninside_obj/object_ikninside_obj.h"
#include "objects/object_danpei_object/object_danpei_object.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DoorSpiral*)thisx)

void DoorSpiral_Init(Actor* thisx, PlayState* play);
void DoorSpiral_Destroy(Actor* thisx, PlayState* play);
void DoorSpiral_Update(Actor* thisx, PlayState* play);
void DoorSpiral_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Door_Spiral_InitVars = {
    /**/ ACTOR_DOOR_SPIRAL,
    /**/ ACTORCAT_DOOR,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(DoorSpiral),
    /**/ DoorSpiral_Init,
    /**/ DoorSpiral_Destroy,
    /**/ DoorSpiral_Update,
    /**/ DoorSpiral_Draw,
};
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2DB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A3098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Draw.s")
