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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wind_0x80B23ED0/ObjWind_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wind_0x80B23ED0/ObjWind_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wind_0x80B23ED0/ObjWind_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wind_0x80B23ED0/ObjWind_Draw.asm")
