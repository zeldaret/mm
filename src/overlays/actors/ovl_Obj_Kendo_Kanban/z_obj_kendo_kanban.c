#include "z_obj_kendo_kanban.h"

#define FLAGS 0x00000000

#define THIS ((ObjKendoKanban*)thisx)

void ObjKendoKanban_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKendoKanban_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Kendo_Kanban_InitVars = {
    ACTOR_OBJ_KENDO_KANBAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DORA,
    sizeof(ObjKendoKanban),
    (ActorFunc)ObjKendoKanban_Init,
    (ActorFunc)ObjKendoKanban_Destroy,
    (ActorFunc)ObjKendoKanban_Update,
    (ActorFunc)ObjKendoKanban_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/ObjKendoKanban_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/ObjKendoKanban_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B65880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B65894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B658A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B65CE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B65D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B65D68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B65DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B6618C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/func_80B66304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/ObjKendoKanban_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kendo_Kanban/ObjKendoKanban_Draw.s")
