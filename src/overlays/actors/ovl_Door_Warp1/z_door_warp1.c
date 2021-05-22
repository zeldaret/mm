#include "z_door_warp1.h"

#define FLAGS 0x00000000

#define THIS ((DoorWarp1*)thisx)

void DoorWarp1_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorWarp1_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Door_Warp1_InitVars = {
    ACTOR_DOOR_WARP1,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_WARP1,
    sizeof(DoorWarp1),
    (ActorFunc)DoorWarp1_Init,
    (ActorFunc)DoorWarp1_Destroy,
    (ActorFunc)DoorWarp1_Update,
    (ActorFunc)DoorWarp1_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B8490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B849C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B8568.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B866C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/DoorWarp1_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/DoorWarp1_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B8924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B8A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B8C48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B8E78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B900C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B90CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B921C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B93A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B94A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B958C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B96A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B96B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B977C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B98A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9BE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9E94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9ED8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808B9FD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BA10C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BA550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BAAF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BABF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/DoorWarp1_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BACCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BAE9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BB4C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BB4F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/DoorWarp1_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Warp1_0x808B8490/func_808BB8D4.asm")
