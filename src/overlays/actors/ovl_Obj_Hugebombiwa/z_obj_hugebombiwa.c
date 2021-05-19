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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A53BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A53E60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A541F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54A0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54BF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55B34.asm")
