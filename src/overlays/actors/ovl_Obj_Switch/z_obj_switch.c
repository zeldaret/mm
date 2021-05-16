#include "z_obj_switch.h"

#define FLAGS 0x00000010

#define THIS ((ObjSwitch*)thisx)

void ObjSwitch_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSwitch_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Switch_InitVars = {
    ACTOR_OBJ_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjSwitch),
    (ActorFunc)ObjSwitch_Init,
    (ActorFunc)ObjSwitch_Destroy,
    (ActorFunc)ObjSwitch_Update,
    (ActorFunc)ObjSwitch_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093ABD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093ADA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AE74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AE88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AEC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AF1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093AF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B6F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B9C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093B9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BB5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BCC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BCDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BD4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BDAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BDC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BE2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BF50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093BF70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C0B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C23C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C2B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C3C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093C99C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093CA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/func_8093CAC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Switch/ObjSwitch_Draw.s")
