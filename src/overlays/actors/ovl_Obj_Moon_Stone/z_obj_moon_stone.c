#include "z_obj_moon_stone.h"

#define FLAGS 0x00100010

#define THIS ((ObjMoonStone*)thisx)

void ObjMoonStone_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMoonStone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMoonStone_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMoonStone_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Moon_Stone_InitVars = {
    ACTOR_OBJ_MOON_STONE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GI_RESERVE00,
    sizeof(ObjMoonStone),
    (ActorFunc)ObjMoonStone_Init,
    (ActorFunc)ObjMoonStone_Destroy,
    (ActorFunc)ObjMoonStone_Update,
    (ActorFunc)ObjMoonStone_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/ObjMoonStone_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/ObjMoonStone_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C0662C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C06640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C066F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C0670C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C0673C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C06768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C0685C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/func_80C06870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/ObjMoonStone_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Moon_Stone/ObjMoonStone_Draw.s")
