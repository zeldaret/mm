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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0662C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C06640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C066F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0670C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0673C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C06768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0685C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C06870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Draw.asm")
