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

ActorInit Door_Spiral_InitVars = {
    ACTOR_DOOR_SPIRAL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorSpiral),
    (ActorFunc)DoorSpiral_Init,
    (ActorFunc)DoorSpiral_Destroy,
    (ActorFunc)DoorSpiral_Update,
    (ActorFunc)DoorSpiral_Draw,
};

UNK_TYPE D_809A3250[] = {
    0x00000000, 0x00000000, 0x00000000, 0x820C320F, 0x050219E0, 0x0501D980, 0x00000000, 0x820C320F,
    0x06004448, 0x060007A8, 0x00000000, 0x820C320F, 0x060051B8, 0x060014C8, 0x00000000, 0x820C320F,
    0x06009278, 0x06006128, 0x00000000, 0x820C320F, 0x06013EA8, 0x06012B70, 0x00000000, 0x820C320F,
    0x06000EA0, 0x06000590, 0x00000000, 0x820C320F, 0x06002110, 0x060012C0, 0x00000000, 0x820C320F,
};

UNK_TYPE D_809A32D0[] = {
    0x00010000, 0x00030100, 0x01640200, 0x01900400, 0x02030500, 0x01C00700, 0x02360600,
};

UNK_TYPE D_809A32EC[] = {
    0x001B0200, 0x00210300, 0x00160400, 0x00180400, 0x00300500, 0x00560600, 0x001D0600,
};

UNK_TYPE D_809A3308[] = {
    0xC0580001, 0xB0FC0FA0, 0xB1000190, 0x31040190, 0x00000000, 0x00000000,
};

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
