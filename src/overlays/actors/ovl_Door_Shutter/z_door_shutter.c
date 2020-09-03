#include "z_door_shutter.h"

#define FLAGS 0x00000010

#define THIS ((DoorShutter*)thisx)

void DoorShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Door_Shutter_InitVars = {
    ACTOR_DOOR_SHUTTER,
    ACTORTYPE_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorShutter),
    (ActorFunc)DoorShutter_Init,
    (ActorFunc)DoorShutter_Destroy,
    (ActorFunc)DoorShutter_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A08F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A0900.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A0974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/DoorShutter_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/DoorShutter_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A0D0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A0D90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A0E28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A0F88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1080.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1090.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1340.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1478.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1548.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1618.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1684.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1784.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1884.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1A70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1B48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1C50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/DoorShutter_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1D68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Door_Shutter_0x808A08F0/func_808A1E14.asm")
