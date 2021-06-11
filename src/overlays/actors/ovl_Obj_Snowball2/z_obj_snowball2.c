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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(ObjSnowball2),
    (ActorFunc)ObjSnowball2_Init,
    (ActorFunc)ObjSnowball2_Destroy,
    (ActorFunc)ObjSnowball2_Update,
    (ActorFunc)ObjSnowball2_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B38E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B38E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B38EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B395C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B395EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39F60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B39FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A0D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A13C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/func_80B3A500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Snowball2/ObjSnowball2_Draw.s")
