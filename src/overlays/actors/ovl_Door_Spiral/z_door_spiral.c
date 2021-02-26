#include "z_door_spiral.h"

#define FLAGS 0x00000010

#define THIS ((DoorSpiral*)thisx)

void DoorSpiral_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Door_Spiral_InitVars = {
    ACTOR_DOOR_SPIRAL,
    ACTORTYPE_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorSpiral),
    (ActorFunc)DoorSpiral_Init,
    (ActorFunc)DoorSpiral_Destroy,
    (ActorFunc)DoorSpiral_Update,
    (ActorFunc)DoorSpiral_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2B60.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2B70.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2BF8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2DB0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2E08.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2EA0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A2FF8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/func_809A3098.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Door_Spiral_0x809A2B60/DoorSpiral_Draw.asm")
