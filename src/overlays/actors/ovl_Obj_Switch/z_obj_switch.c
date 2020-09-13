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
    ACTORTYPE_SWITCH,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(ObjSwitch),
    (ActorFunc)ObjSwitch_Init,
    (ActorFunc)ObjSwitch_Destroy,
    (ActorFunc)ObjSwitch_Update,
    (ActorFunc)ObjSwitch_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093ABD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AC6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093ADA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AE1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AE74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AE88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AEC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AEF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AF1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093AF54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B668.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B6F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B710.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B92C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B940.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B9C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093B9E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BB5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BB70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BBD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BCC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BCDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BD4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BDAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BDC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BE10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BE2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BEF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BF04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BF50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093BF70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C0A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C0B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C138.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C15C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C23C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C250.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C2B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C2D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C3C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C3DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C584.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C888.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C8B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093C99C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093CA80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/func_8093CAC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Switch_0x8093ABD0/ObjSwitch_Draw.asm")
