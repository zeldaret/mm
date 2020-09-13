#include "z_obj_visiblock.h"

#define FLAGS 0x00000080

#define THIS ((ObjVisiblock*)thisx)

void ObjVisiblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjVisiblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjVisiblock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Visiblock_InitVars = {
    ACTOR_OBJ_VISIBLOCK,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_VISIBLOCK,
    sizeof(ObjVisiblock),
    (ActorFunc)ObjVisiblock_Init,
    (ActorFunc)ObjVisiblock_Destroy,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjVisiblock_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Visiblock_0x80ADEA70/ObjVisiblock_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Visiblock_0x80ADEA70/ObjVisiblock_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Visiblock_0x80ADEA70/ObjVisiblock_Draw.asm")
