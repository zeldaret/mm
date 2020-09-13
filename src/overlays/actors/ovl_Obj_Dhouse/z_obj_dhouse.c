#include "z_obj_dhouse.h"

#define FLAGS 0x00400010

#define THIS ((ObjDhouse*)thisx)

void ObjDhouse_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDhouse_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDhouse_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDhouse_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Dhouse_InitVars = {
    ACTOR_OBJ_DHOUSE,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_DHOUSE,
    sizeof(ObjDhouse),
    (ActorFunc)ObjDhouse_Init,
    (ActorFunc)ObjDhouse_Destroy,
    (ActorFunc)ObjDhouse_Update,
    (ActorFunc)ObjDhouse_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B12A50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B12A88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B12B38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B12D78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B12E7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B13170.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B13474.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B13724.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B13908.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B1391C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B1392C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B13940.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B139D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B139F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B13C08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dhouse_0x80B12980/func_80B13E40.asm")
