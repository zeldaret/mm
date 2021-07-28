#include "z_door_shutter.h"

#define FLAGS 0x00000010

#define THIS ((DoorShutter*)thisx)

void DoorShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808A2248[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};


extern InitChainEntry D_808A2248[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A08F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A0900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A0974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/DoorShutter_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/DoorShutter_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A0D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A0D90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A0E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A0F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1A70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/DoorShutter_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Shutter/func_808A1E14.s")
