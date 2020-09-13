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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(ObjSnowball),
    (ActorFunc)ObjSnowball_Init,
    (ActorFunc)ObjSnowball_Destroy,
    (ActorFunc)ObjSnowball_Update,
    (ActorFunc)ObjSnowball_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B02CD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B02D58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B02DB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B02E54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B02EE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B030F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B03688.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B03A80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B03E2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B03FF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04338.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B0457C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04608.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B046E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B047C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04B48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04B60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/ObjSnowball_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball_0x80B02CD0/func_80B04D34.asm")
