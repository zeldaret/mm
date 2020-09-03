#include "z_obj_snowball2.h"

#define FLAGS 0x00800000

#define THIS ((ObjSnowball2*)thisx)

void ObjSnowball2_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball2_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Snowball2_InitVars = {
    ACTOR_OBJ_SNOWBALL2,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(ObjSnowball2),
    (ActorFunc)ObjSnowball2_Init,
    (ActorFunc)ObjSnowball2_Destroy,
    (ActorFunc)ObjSnowball2_Update,
    (ActorFunc)ObjSnowball2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B38E20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B38E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B38EFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39108.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B395C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B395EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39638.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39834.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39908.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39B28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39B5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39C78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39C9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39F60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B39FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B3A0D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B3A13C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B3A498.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/func_80B3A500.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Draw.asm")
