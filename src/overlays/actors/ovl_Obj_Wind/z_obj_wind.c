#include "z_obj_wind.h"

#define FLAGS 0x00000010

#define THIS ((ObjWind*)thisx)

void ObjWind_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWind_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWind_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWind_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Wind_InitVars = {
    ACTOR_OBJ_WIND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjWind),
    (ActorFunc)ObjWind_Init,
    (ActorFunc)ObjWind_Destroy,
    (ActorFunc)ObjWind_Update,
    (ActorFunc)ObjWind_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wind/ObjWind_Draw.s")
