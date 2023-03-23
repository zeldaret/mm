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

/*
const ActorInit Door_Spiral_InitVars = {
    ACTOR_DOOR_SPIRAL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorSpiral),
    (ActorFunc)DoorSpiral_Init,
    (ActorFunc)DoorSpiral_Destroy,
    (ActorFunc)DoorSpiral_Update,
    (ActorFunc)DoorSpiral_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A2B60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A2B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A2BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A2DB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A2E08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A2EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A2FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/func_809A3098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Draw.asm")
