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
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DHOUSE,
    sizeof(ObjDhouse),
    (ActorFunc)ObjDhouse_Init,
    (ActorFunc)ObjDhouse_Destroy,
    (ActorFunc)ObjDhouse_Update,
    (ActorFunc)ObjDhouse_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B12A50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B12A88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B12B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B12D78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B12E7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B13170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B13474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B13724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B13908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B1391C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B1392C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B13940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B139D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B139F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/ObjDhouse_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B13C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dhouse_0x80B12980/func_80B13E40.asm")
