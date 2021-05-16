#include "z_obj_snowball.h"

#define FLAGS 0x00000000

#define THIS ((ObjSnowball*)thisx)

void ObjSnowball_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Snowball_InitVars = {
    ACTOR_OBJ_SNOWBALL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(ObjSnowball),
    (ActorFunc)ObjSnowball_Init,
    (ActorFunc)ObjSnowball_Destroy,
    (ActorFunc)ObjSnowball_Update,
    (ActorFunc)ObjSnowball_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B02CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B02D58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B02DB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B02E54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B02EE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B030F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B03688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B03A80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B03E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B03FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/ObjSnowball_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/ObjSnowball_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B0457C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B046E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B047C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/ObjSnowball_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/ObjSnowball_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball/func_80B04D34.s")
