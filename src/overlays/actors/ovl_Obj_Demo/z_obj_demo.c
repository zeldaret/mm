/*
 * File: z_obj_demo.c
 * Overlay: ovl_Obj_Demo
 * Description:
 */

#include "z_obj_demo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDemo*)thisx)

void ObjDemo_Init(Actor* thisx, PlayState* play);
void ObjDemo_Update(Actor* thisx, PlayState* play);

void func_80983678(ObjDemo* this, PlayState* play);
void func_80983704(ObjDemo* this, PlayState* play);

#if 0
const ActorInit Obj_Demo_InitVars = {
    ACTOR_OBJ_DEMO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjDemo),
    (ActorFunc)ObjDemo_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjDemo_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/ObjDemo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/func_80983634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/func_80983678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/func_80983704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/ObjDemo_Update.s")
