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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_UM,
    sizeof(ObjUm),
    (ActorFunc)ObjUm_Init,
    (ActorFunc)ObjUm_Destroy,
    (ActorFunc)ObjUm_Update,
    (ActorFunc)ObjUm_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B77770.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B77FA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B781DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B783E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78764.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78A54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78C18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78D08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78DF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78E2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78E38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78EBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B78EFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/ObjUm_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/ObjUm_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79560.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B795A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79734.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B797EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7984C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79A24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79A50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79BA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79F10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B79FFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A0E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A144.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A1B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A240.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A2AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A394.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A400.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A614.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A7AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7A860.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7AB78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7ABE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7AC94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7AD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7AE58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7AEFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7AF30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7B154.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7B18C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/ObjUm_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7B598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7B93C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7BABC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/func_80B7BEA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Um_0x80B77770/ObjUm_Draw.asm")
