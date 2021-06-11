#include "z_obj_hugebombiwa.h"

#define FLAGS 0x00000010

#define THIS ((ObjHugebombiwa*)thisx)

void ObjHugebombiwa_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHugebombiwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHugebombiwa_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHugebombiwa_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hugebombiwa_InitVars = {
    ACTOR_OBJ_HUGEBOMBIWA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBIWA,
    sizeof(ObjHugebombiwa),
    (ActorFunc)ObjHugebombiwa_Init,
    (ActorFunc)ObjHugebombiwa_Destroy,
    (ActorFunc)ObjHugebombiwa_Update,
    (ActorFunc)ObjHugebombiwa_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A53BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A53E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A541F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/ObjHugebombiwa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/ObjHugebombiwa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A54E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A55064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A55310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A55564.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/ObjHugebombiwa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/ObjHugebombiwa_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hugebombiwa/func_80A55B34.s")
