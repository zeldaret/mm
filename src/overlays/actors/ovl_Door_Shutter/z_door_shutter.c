#include "z_door_shutter.h"

#define FLAGS 0x00000010

#define THIS ((DoorShutter*)thisx)

void DoorShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Door_Shutter_InitVars = {
    ACTOR_DOOR_SHUTTER,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorShutter),
    (ActorFunc)DoorShutter_Init,
    (ActorFunc)DoorShutter_Destroy,
    (ActorFunc)DoorShutter_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A08F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A0900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A0974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/DoorShutter_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/DoorShutter_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A0D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A0D90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A0E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A0F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1A70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/DoorShutter_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1D68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Door_Shutter_0x808A08F0/func_808A1E14.asm")
