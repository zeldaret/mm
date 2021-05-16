#include "z_obj_um.h"

#define FLAGS 0x00000039

#define THIS ((ObjUm*)thisx)

void ObjUm_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Um_InitVars = {
    ACTOR_OBJ_UM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_UM,
    sizeof(ObjUm),
    (ActorFunc)ObjUm_Init,
    (ActorFunc)ObjUm_Destroy,
    (ActorFunc)ObjUm_Update,
    (ActorFunc)ObjUm_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B77770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B77FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B781DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B783E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78A54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B78EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/ObjUm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/ObjUm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B795A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B797EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7984C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B79FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A2AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A614.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A7AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7A860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7AB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7ABE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7AC94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7AD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7AE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7AEFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7AF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7B154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7B18C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/ObjUm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7B598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7B93C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7BABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/func_80B7BEA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Um/ObjUm_Draw.s")
