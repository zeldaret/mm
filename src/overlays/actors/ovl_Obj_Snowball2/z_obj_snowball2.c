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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B38E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B38E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B38EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39108.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B395C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B395EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39B28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39C9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39F60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B39FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B3A0D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B3A13C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B3A498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/func_80B3A500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Snowball2_0x80B38E20/ObjSnowball2_Draw.asm")
