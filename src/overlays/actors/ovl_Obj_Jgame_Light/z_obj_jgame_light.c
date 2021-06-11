#include "z_obj_jgame_light.h"

#define FLAGS 0x00000010

#define THIS ((ObjJgameLight*)thisx)

void ObjJgameLight_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjJgameLight_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Jgame_Light_InitVars = {
    ACTOR_OBJ_JGAME_LIGHT,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SYOKUDAI,
    sizeof(ObjJgameLight),
    (ActorFunc)ObjJgameLight_Init,
    (ActorFunc)ObjJgameLight_Destroy,
    (ActorFunc)ObjJgameLight_Update,
    (ActorFunc)ObjJgameLight_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/func_80C15474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/func_80C156C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/func_80C15718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Jgame_Light/ObjJgameLight_Draw.s")
