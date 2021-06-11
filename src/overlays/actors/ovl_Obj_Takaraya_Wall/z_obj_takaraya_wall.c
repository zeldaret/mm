#include "z_obj_takaraya_wall.h"

#define FLAGS 0x00000030

#define THIS ((ObjTakarayaWall*)thisx)

void ObjTakarayaWall_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTakarayaWall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTakarayaWall_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTakarayaWall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Takaraya_Wall_InitVars = {
    ACTOR_OBJ_TAKARAYA_WALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TAKARAYA_OBJECTS,
    sizeof(ObjTakarayaWall),
    (ActorFunc)ObjTakarayaWall_Init,
    (ActorFunc)ObjTakarayaWall_Destroy,
    (ActorFunc)ObjTakarayaWall_Update,
    (ActorFunc)ObjTakarayaWall_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD92FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/func_80AD9B04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Takaraya_Wall/ObjTakarayaWall_Draw.s")
