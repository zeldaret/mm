#include "z_obj_bell.h"

#define FLAGS 0x00000030

#define THIS ((ObjBell*)thisx)

void ObjBell_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBell_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBell_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBell_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Bell_InitVars = {
    ACTOR_OBJ_BELL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_F52_OBJ,
    sizeof(ObjBell),
    (ActorFunc)ObjBell_Init,
    (ActorFunc)ObjBell_Destroy,
    (ActorFunc)ObjBell_Update,
    (ActorFunc)ObjBell_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/func_80A35510.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/func_80A356D8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/func_80A357A8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/func_80A358FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/func_80A359B4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/func_80A35B18.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/func_80A35BD4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/ObjBell_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/ObjBell_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/ObjBell_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Bell_0x80A35510/ObjBell_Draw.asm")
