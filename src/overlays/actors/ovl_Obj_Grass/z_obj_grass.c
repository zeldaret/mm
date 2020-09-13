#include "z_obj_grass.h"

#define FLAGS 0x00000030

#define THIS ((ObjGrass*)thisx)

void ObjGrass_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Grass_InitVars = {
    ACTOR_OBJ_GRASS,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(ObjGrass),
    (ActorFunc)ObjGrass_Init,
    (ActorFunc)ObjGrass_Destroy,
    (ActorFunc)ObjGrass_Update,
    (ActorFunc)ObjGrass_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809A9110.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809A91FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809A92D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809A9314.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/ObjGrass_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/ObjGrass_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809A9790.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809A983C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809A9DB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/ObjGrass_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809AA278.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809AA54C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/func_809AA798.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Grass_0x809A9110/ObjGrass_Draw.asm")
