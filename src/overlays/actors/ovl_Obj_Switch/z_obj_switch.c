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
    (ActorFunc)ObjSwitch_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093ABD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AC6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093ADA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AE88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AEC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AF1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093AF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B6F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B92C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B9C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093B9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BB5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BB70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BBD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BCC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BCDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BD4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BDAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BDC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BE2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BF04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BF50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093BF70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C138.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C23C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C2B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C3C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C3DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093C99C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093CA80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/func_8093CAC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Draw.asm")
