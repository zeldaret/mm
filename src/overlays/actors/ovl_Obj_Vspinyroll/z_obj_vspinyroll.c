#include "z_obj_vspinyroll.h"

#define FLAGS 0x00000010

#define THIS ((ObjVspinyroll*)thisx)

void ObjVspinyroll_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Vspinyroll_InitVars = {
    ACTOR_OBJ_VSPINYROLL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPINYROLL,
    sizeof(ObjVspinyroll),
    (ActorFunc)ObjVspinyroll_Init,
    (ActorFunc)ObjVspinyroll_Destroy,
    (ActorFunc)ObjVspinyroll_Update,
    (ActorFunc)ObjVspinyroll_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C6A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C7E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CB94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CBF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CEC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CEE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CF10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CF4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CFAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3CFE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D0E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D0FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/ObjVspinyroll_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3D2C0.s")
